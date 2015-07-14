/*
 * Copyright (C) 2011 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright (C) 2012 Sanyo Ltd..  All Rights Reserved.
 */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/err.h>
#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/io.h>
#include <linux/clk.h>
#include <linux/mfd/da9052/reg.h>
#include <linux/mfd/da9052/da9052.h>
#include <linux/mfd/da9052/led.h>

#include <asm/mach-types.h>
#include <mach/hardware.h>
#include <mach/i2c.h>
#include "pmic.h"

/** Defines ********************************************************************
*******************************************************************************/
/* have to hard-code the preset voltage here for they share the register
as the normal setting on Da9053 */
/* preset buck core to 850 mv */
#define BUCKCORE_SUSPEND_PRESET 0xCE
/* preset buck core to 950 mv */
#define BUCKPRO_SUSPEND_PRESET 0xD2
/* preset ldo6 to 1200 mv */
#define LDO6_SUSPEND_PRESET 0xC0
/* preset ldo10 to 1200 mv */
#define iLDO10_SUSPEND_PRESET 0xC0
/* set VUSB 2V5 active during suspend */
#define BUCKPERI_SUSPEND_SW_STEP 0x50
/* restore VUSB 2V5 active after suspend */
#define BUCKPERI_RESTORE_SW_STEP 0x55
/* restore VUSB 2V5 power supply after suspend */
#define SUPPLY_RESTORE_VPERISW_EN 0x20
#define CONF_BIT 0x80

#define DA9053_SLEEP_DELAY 0x1f
#define DA9052_CONTROLC_SMD_SET 0x62
#define DA9052_GPIO0809_SMD_SET 0x18
#define DA9052_ID1415_SMD_SET   0x1
#define DA9052_GPI9_IRQ_MASK    0x2

static u8 volt_settings[DA9052_LDO10_REG - DA9052_BUCKCORE_REG + 1];
extern int pm_i2c_imx_xfer(struct i2c_msg *msgs, int num);
extern void clear_bej2_suspend_state(void);
static u8 mask_reg[3];
static u8 ldo5;

#define I2C_BUG_WORKAROUND

#ifdef I2C_BUG_WORKAROUND
#define I2C_DUMMY_REG	0xFF

#define ADCIN4_HIGH_VALUE 0x80

static inline int da9052_is_i2c_reg_safe(unsigned char reg)
{
	const char safe_table[256] = {
		[DA9052_STATUSA_REG] = 1,
		[DA9052_STATUSB_REG] = 1,
		[DA9052_STATUSC_REG] = 1,
		[DA9052_STATUSD_REG] = 1,
		[DA9052_EVENTA_REG] = 1,
		[DA9052_EVENTB_REG] = 1,
		[DA9052_EVENTC_REG] = 1,
		[DA9052_EVENTD_REG] = 1,
		[DA9052_ADCRESL_REG] = 1,
		[DA9052_ADCRESH_REG] = 1,
		[DA9052_VDDRES_REG] = 1,
		[DA9052_ICHGAV_REG] = 1,
		[DA9052_TBATRES_REG] = 1,
		[DA9052_ADCIN4RES_REG] = 1,
		[DA9052_ADCIN5RES_REG] = 1,
		[DA9052_ADCIN6RES_REG] = 1,
		[DA9052_TJUNCRES_REG] = 1,
		[DA9052_TSIXMSB_REG] = 1,
		[DA9052_TSIYMSB_REG] = 1,
		[DA9052_TSILSB_REG] = 1,
		[DA9052_TSIZMSB_REG] = 1,
		[I2C_DUMMY_REG] = 1,	/* Dummy reg must be a save reg */
	};

	return safe_table[reg];
}
#endif

static void pm_da9053_read_reg(u8 reg, u8 *value)
{
	unsigned char buf[2] = {0, 0};
#ifdef I2C_BUG_WORKAROUND
	unsigned char buf_flush[2] = {I2C_DUMMY_REG, 0xff};
	struct i2c_msg i2cmsg[3];
#else
	struct i2c_msg i2cmsg[2];
#endif
	buf[0] = reg;
	i2cmsg[0].addr  = 0x48 ;
	i2cmsg[0].len   = 1;
	i2cmsg[0].buf   = &buf[0];

	i2cmsg[0].flags = 0;

	i2cmsg[1].addr  = 0x48 ;
	i2cmsg[1].len   = 1;
	i2cmsg[1].buf   = &buf[1];

	i2cmsg[1].flags = I2C_M_RD;

	pm_i2c_imx_xfer(i2cmsg, 2);
	*value = buf[1];

#ifdef I2C_BUG_WORKAROUND
	/* Test, whether register to be accessed needs to be flushed */
	if (!da9052_is_i2c_reg_safe(reg)) {
		i2cmsg[2].addr  = 0x48 ;
		i2cmsg[2].len   = 1;
		i2cmsg[2].buf   = &buf_flush[0];
		i2cmsg[2].flags = 0;
		pm_i2c_imx_xfer(&i2cmsg[2], 1);
	}
#endif
}

static void pm_da9053_write_reg(u8 reg, u8 value)
{
#ifdef I2C_BUG_WORKAROUND
	unsigned char buf[4] = {0, 0 , I2C_DUMMY_REG , 0xff};
#else
	unsigned char buf[2] = {0, 0};
#endif
	struct i2c_msg i2cmsg[2];
	buf[0] = reg;
	buf[1] = value;
	i2cmsg[0].addr  = 0x48 ;
	i2cmsg[0].len   = 2;
	i2cmsg[0].buf   = &buf[0];
	i2cmsg[0].flags = 0;

#ifdef I2C_BUG_WORKAROUND
	/* Test, whether register to be accessed needs to be flushed */
	if (!da9052_is_i2c_reg_safe(reg)) {
		i2cmsg[0].len = 4;
	}
#endif

	pm_i2c_imx_xfer(i2cmsg, 1);
}

static void pm_da9053_preset_voltage(void)
{
	u8 reg, data;
	for (reg = DA9052_BUCKCORE_REG;
		reg <= DA9052_LDO10_REG; reg++) {
		pm_da9053_read_reg(reg, &data);
		volt_settings[reg - DA9052_BUCKCORE_REG] = data;
		data |= CONF_BIT;
		pm_da9053_write_reg(reg, data);
	}
	pm_da9053_write_reg(DA9052_BUCKCORE_REG, BUCKCORE_SUSPEND_PRESET);
	pm_da9053_write_reg(DA9052_BUCKPRO_REG, BUCKPRO_SUSPEND_PRESET);
#if 1
	pm_da9053_write_reg(DA9052_BUCKMEM_REG, 0xD7);
	pm_da9053_write_reg(DA9052_BUCKPERI_REG, 0xFE);

	pm_da9053_write_reg(DA9052_LDO2_REG, 0xDC);
	pm_da9053_write_reg(DA9052_LDO3_REG, 0xFB);
	pm_da9053_write_reg(DA9052_LDO4_REG, 0xEA);
	pm_da9053_write_reg(DA9052_LDO5_REG, 0xE8);
	pm_da9053_write_reg(DA9052_LDO6_REG, 0xC2);
	pm_da9053_write_reg(DA9052_LDO7_REG, 0xE8);
	pm_da9053_write_reg(DA9052_LDO8_REG, 0xCC);
	pm_da9053_write_reg(DA9052_LDO9_REG, 0xC5);
	pm_da9053_write_reg(DA9052_LDO10_REG, 0xC2);
#else
	pm_da9053_write_reg(DA9052_LDO6_REG, LDO6_SUSPEND_PRESET);
	pm_da9053_write_reg(DA9052_LDO10_REG, iLDO10_SUSPEND_PRESET);
	pm_da9053_write_reg(DA9052_ID1213_REG, BUCKPERI_SUSPEND_SW_STEP);
#endif
}

#if 0
static void pm_da9053_dump(int start, int end)
{
	u8 reg, data;
	for (reg = start; reg <= end; reg++) {
		pm_da9053_read_reg(reg, &data);
		pr_info("reg %u = 0x%2x\n",
			reg, data);
	}
}
#endif

extern int da9052_led6_status(void);

static void led_setting(u8 value)
{
	if(value >= ADCIN4_HIGH_VALUE)
	{
		if(da9052_led6_status())
		{
			if((da9052_led6_status() >> 1) & 0x03)//blink
			{
				pm_da9053_write_reg(DA9052_GPIO1011_REG, LED10_BLINK);
			}
			else
			{
				pm_da9053_write_reg(DA9052_GPIO1011_REG, LED10_ON);
			}
		}
		else
		{
			pm_da9053_write_reg(DA9052_GPIO1011_REG, LED1110_ON);
		}
	}
	else
	{
		if(da9052_led6_status())
		{
			if((da9052_led6_status() >> 1) & 0x03)//blink
			{
				pm_da9053_write_reg(DA9052_GPIO1011_REG, LED10_BLINK);
			}
			else
			{
				pm_da9053_write_reg(DA9052_GPIO1011_REG, LED10_ON);
			}
		}
		else
		{
			pm_da9053_write_reg(DA9052_GPIO1011_REG, LED1110_OFF);
		}
	}
}

#define DA9052_CHARGING 2
extern int da9052_get_bat_status(void);
//extern int get_da9052_batvoltage(void);
#define DA9052_NOCHARGER 1
extern int da9052_get_bat_charger_type(void);
extern int check_charge_check_count(void);
extern void clear_charge_check_count(void);
extern int da9052_get_bat_status_low_battery(void);
extern void da9052_bat_status_low_battery_clear(void);

int da9053_suspend_cmd_sw(void)
{
	unsigned char buf[2] = {0, 0};
	struct clk *i2c_clk;
	u8 data,data_adcin4;
	buf[0] = 29;

	i2c_clk = clk_get(NULL, "i2c_clk");
	if (IS_ERR(i2c_clk)) {
		pr_err("unable to get i2c clk\n");
		return PTR_ERR(i2c_clk);
	}
	clk_enable(i2c_clk);

	pm_da9053_read_reg(DA9052_VDDRES_REG, &data);
//	if(data <= 0x5E)//3.252V
	if(data <= 0x66)//3.3V
	{
printk("DA9052_CONTROLB_REG 0xba\n");
		pm_da9053_write_reg(DA9052_CONTROLB_REG, 0xba);
		while(1);
	}
	else
	{
		pm_da9053_read_reg(DA9052_IRQMASKA_REG, &mask_reg[0]);
		pm_da9053_read_reg(DA9052_IRQMASKB_REG, &mask_reg[1]);
		pm_da9053_read_reg(DA9052_IRQMASKC_REG, &mask_reg[2]);

//		pm_da9053_write_reg(DA9052_VDDMON_REG, 0x5E);//3.252V
		pm_da9053_write_reg(DA9052_VDDMON_REG, 0x66);//3.3V

		pm_da9053_write_reg(DA9052_IRQMASKA_REG, 0xEF);

		if (!machine_is_mx53_bej2())
		{
			pm_da9053_read_reg(DA9052_EVENTA_REG, &data);
			pm_da9053_write_reg(DA9052_EVENTA_REG, data);
			pm_da9053_write_reg(DA9052_IRQMASKB_REG, 0xFE);
			pm_da9053_read_reg(DA9052_EVENTB_REG, &data);
			pm_da9053_write_reg(DA9052_EVENTB_REG, data);
			pm_da9053_write_reg(DA9052_IRQMASKC_REG, 0xff);
			pm_da9053_read_reg(DA9052_EVENTC_REG, &data);
			pm_da9053_write_reg(DA9052_EVENTC_REG, data);
		}
		else
		{
			pm_da9053_read_reg(DA9052_EVENTA_REG, &data);
			pm_da9053_write_reg(DA9052_EVENTA_REG, data);

			pm_da9053_read_reg(DA9052_ADCIN4RES_REG, &data_adcin4);
			if(data_adcin4 > ADCIN4_HIGH_VALUE)//USB ON
			{
				pm_da9053_write_reg(DA9052_AUTO4HIGH_REG, 0xff);
				pm_da9053_write_reg(DA9052_AUTO4LOW_REG, 0x40);
			}
			else
			{
				pm_da9053_write_reg(DA9052_AUTO4HIGH_REG, 0x80);
				pm_da9053_write_reg(DA9052_AUTO4LOW_REG, 0x00);
			}

			/*サスペンドしてからACを挿すとステータスが充電中ではないので点かない。*/
			/*上位側の点灯基準を電圧に変えたのでそれと同じ制御とする。*/
//			if(da9052_get_bat_status() == DA9052_CHARGING)
//			if(get_da9052_batvoltage() <= 4200)

			if(data_adcin4 > ADCIN4_HIGH_VALUE)//USB ON
			{
				if(da9052_get_bat_charger_type() == DA9052_NOCHARGER) /*ac off->ac on*/
				{
					da9052_bat_status_low_battery_clear();
					led_setting(data_adcin4);
				}
				else if((da9052_get_bat_status() != DA9052_CHARGING) && check_charge_check_count())/*ac on not charge->suspend*/
				{
					led_setting(0);
				}
				else
				{
					led_setting(data_adcin4);
				}
			}
			else
			{
				clear_charge_check_count();
				if(da9052_get_bat_status_low_battery() == 0)
				{
					led_setting(0);
				}
			}

			pm_da9053_read_reg(DA9052_ICHGAV_REG, &data);
			if(data < 0x19)
			{
				pm_da9053_write_reg(DA9052_IRQMASKB_REG, 0xFE);//ONKEY
			}
			else
			{
	printk("CHG_END Wait\n");
				pm_da9053_write_reg(DA9052_IRQMASKB_REG, 0xF6);//CHG_END,ONKEY
			}
			pm_da9053_read_reg(DA9052_EVENTB_REG, &data);
			pm_da9053_write_reg(DA9052_EVENTB_REG, data);
			/*Low Battryで起こすための閾値*/
			pm_da9053_write_reg(DA9052_AUTO6HIGH_REG, 0xff);
			pm_da9053_write_reg(DA9052_AUTO6LOW_REG, 0xb3);/*暫定値*/
			pm_da9053_read_reg(DA9052_ADCIN6RES_REG, &data);
			if((data > 0xb3) && (data_adcin4 < ADCIN4_HIGH_VALUE))
			{
	printk("DA9052_ADCIN6RES_REG %02x\n",data);
				pm_da9053_write_reg(DA9052_IRQMASKC_REG, 0xfa);
			}
			else
			{
				if((data <= 0xb3) && (data_adcin4 < ADCIN4_HIGH_VALUE))
				{
	printk("Low Battery\n");
					pm_da9053_write_reg(DA9052_GPIO1011_REG, LED11_ON);
				}
				pm_da9053_write_reg(DA9052_IRQMASKC_REG, 0xfe);
			}

			pm_da9053_read_reg(DA9052_EVENTC_REG, &data);
			pm_da9053_write_reg(DA9052_EVENTC_REG, data);

			pm_da9053_read_reg(DA9052_LDO5_REG, &ldo5);
			pm_da9053_write_reg(DA9052_LDO5_REG, ldo5 & 0x3f);

			pm_da9053_write_reg(DA9052_BATCHG_REG, 0xe0);
//			pm_da9053_write_reg(DA9052_ISET_REG, 0xfb);
		}
	}
	clk_disable(i2c_clk);
	clk_put(i2c_clk);
	return 0;
}

int da9053_suspend_cmd_hw(void)
{
	unsigned char buf[2] = {0, 0};
	struct clk *i2c_clk;
	u8 data;
	buf[0] = 29;

	i2c_clk = clk_get(NULL, "i2c_clk");
	if (IS_ERR(i2c_clk)) {
		pr_err("unable to get i2c clk\n");
		return PTR_ERR(i2c_clk);
	}
	clk_enable(i2c_clk);

	pm_da9053_preset_voltage();
	pm_da9053_write_reg(DA9052_CONTROLC_REG,
				DA9052_CONTROLC_SMD_SET);

	pm_da9053_read_reg(DA9052_ID01_REG, &data);
	data &= ~(DA9052_ID01_DEFSUPPLY | DA9052_ID01_nRESMODE);
	pm_da9053_write_reg(DA9052_ID01_REG, data);

	pm_da9053_write_reg(DA9052_GPIO0809_REG,
			DA9052_GPIO0809_SMD_SET);
	pm_da9053_read_reg(DA9052_IRQMASKD_REG, &data);
	data |= DA9052_GPI9_IRQ_MASK;
	pm_da9053_write_reg(DA9052_IRQMASKD_REG, data);

	pm_da9053_read_reg(DA9052_ID1415_REG, &data);
	data &= 0xf0;
	data |= DA9052_ID1415_SMD_SET;
	pm_da9053_write_reg(DA9052_ID1415_REG, data);

	pm_da9053_write_reg(DA9052_SEQTIMER_REG, 0);
	/* pm_da9053_write_reg(DA9052_SEQB_REG, 0x1f); */

	clk_disable(i2c_clk);
	clk_put(i2c_clk);
	return 0;
}

int da9053_restore_volt_settings(void)
{
	u8 data,data_alarm;
	struct clk *i2c_clk;

	i2c_clk = clk_get(NULL, "i2c_clk");
	if (IS_ERR(i2c_clk)) {
		pr_err("unable to get i2c clk\n");
		return PTR_ERR(i2c_clk);
	}
	clk_enable(i2c_clk);

	pm_da9053_write_reg(DA9052_BATCHG_REG, 0xd0);
//	pm_da9053_write_reg(DA9052_ISET_REG, 0xf7);
	pm_da9053_write_reg(DA9052_LDO5_REG, ldo5);

	pm_da9053_write_reg(DA9052_IRQMASKA_REG, mask_reg[0]);
	pm_da9053_write_reg(DA9052_IRQMASKB_REG, (mask_reg[1] & ~DA9052_IRQMASKB_MNONKEY));
	pm_da9053_write_reg(DA9052_IRQMASKC_REG, mask_reg[2]);

	pm_da9053_read_reg(DA9052_EVENTA_REG, &data);
	if(data & DA9052_EVENTA_EVDDLOW)
	{
		pm_da9053_write_reg(DA9052_CONTROLB_REG, 0xba);
		while(1);
	}

	pm_da9053_write_reg(DA9052_EVENTA_REG, data);

	if (!machine_is_mx53_bej2())
	{
		pm_da9053_read_reg(DA9052_EVENTB_REG, &data);
		pm_da9053_write_reg(DA9052_EVENTB_REG, (data & ~DA9052_EVENTB_ENONKEY));
		pm_da9053_read_reg(DA9052_EVENTC_REG, &data);
		pm_da9053_write_reg(DA9052_EVENTC_REG, data);
	}
	else
	{
		pm_da9053_read_reg(DA9052_EVENTB_REG, &data);
	printk("DA9052_EVENTB_REG %02x\n",data);
		pm_da9053_write_reg(DA9052_EVENTB_REG, (data & ~DA9052_EVENTB_ENONKEY));
		pm_da9053_read_reg(DA9052_STATUSB_REG, &data);
		if(data & DA9052_STATUSB_CHGEND)
		{
	printk("DA9052_STATUSB_REG %02x\n",data);
			if(da9052_led6_status())
			{
				pm_da9053_write_reg(DA9052_GPIO1011_REG, LED10_ON);
			}
			else
			{
				pm_da9053_write_reg(DA9052_GPIO1011_REG, LED1110_OFF);
			}
		}

		pm_da9053_read_reg(DA9052_ADCIN4RES_REG, &data_alarm);
	printk("DA9052_ADCIN4RES_REG %02x\n",data_alarm);

		pm_da9053_read_reg(DA9052_EVENTC_REG, &data);
	printk("DA9052_EVENTC_REG %02x\n",data);
	#if 0
		if(data & DA9052_EVENTC_EGPI0)
		{
	printk("DA9052_EVENTC_EGPI0 %02x\n",data);
			led_setting(data_alarm);
		}
	#endif

		if((data & DA9052_EVENTC_EGPI2) && (data_alarm < ADCIN4_HIGH_VALUE))/*LowBatteryが優先なつもり*/
		{
	printk("DA9052_EVENTC_EGPI2\n");
			pm_da9053_read_reg(DA9052_ADCIN6RES_REG, &data_alarm);
	printk("DA9052_ADCIN6RES_REG %02x\n",data_alarm);
			pm_da9053_write_reg(DA9052_GPIO1011_REG, LED11_ON);
		}

		pm_da9053_write_reg(DA9052_EVENTC_REG, data);
	}
	
	clear_bej2_suspend_state();

	clk_disable(i2c_clk);
	clk_put(i2c_clk);
	return 0;
}
