/*
 *  max17058_battery.c
 *  ModelGauge IC for 1 cell Li+ battery
 *
 *  Copyright (C) 2012 Sanyo Ltd..
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/mutex.h>
#include <linux/err.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/power_supply.h>
#include <linux/slab.h>

//#define DEBUG
//#define DEBUG2

#define ADC
//#define ADC_DEBUG

//#define TESTMODE
//#define TESTMODEDEBUG

#define MAX17058_VCELL_REG	0x02
#define MAX17058_SOC_REG	0x04
#define MAX17058_MODE_REG	0x06
#define MAX17058_VERSION_REG	0x08
#define MAX17058_CONFIG_REG	0x0C
#define MAX17058_OCV_REG	0x0E
#define MAX17058_MODEL_REG	0x40

#define MAX17058_DELAY		1000

struct max17058_chip {
	struct i2c_client		*client;
	struct delayed_work		work;
	int vcell;
	int soc;
	u16 ocv;
};

static struct max17058_chip chip_st;

static u8 model_data[64] =
{
	0xAC,0x20,0xB6,0x20,0xB8,0x90,0xB9,0xB0,
	0xBB,0xB0,0xBD,0x10,0xBE,0xA0,0xC0,0x40,
	0xC2,0x30,0xC4,0x20,0xC5,0xB0,0xC8,0x50,
	0xC9,0x10,0xC9,0xB0,0xCC,0x30,0xD0,0x30,
	0x01,0xB0,0x13,0xD0,0x2E,0xF0,0x14,0xF0,
	0x08,0xB0,0x3A,0xF0,0x27,0xD0,0x30,0xC0,
	0x16,0x70,0x2D,0x40,0x0C,0x10,0x30,0x00,
	0x2C,0x10,0x22,0x30,0x14,0x00,0x14,0x00,
};
#define OCVtest 55856
#define SOCCheckA 248
#define SOCCheckB 250
#define RCOMP0 107
#define TempCoUp -45
#define TempCoDown -295
#define ALART_SETTING (17 | (1 << 5))

extern s32 da9052_get_battery_temp(void);

static int max17058_write_buf_data(struct i2c_client *client, u8 reg, u8 *buf,int size)
{
	struct i2c_adapter *adapter = to_i2c_adapter(client->dev.parent);
	struct i2c_msg i2cmsg;
	int ret = 0;
	u8 data_buf[65];

	if(size > 64)
	{
		return -1;
	}

	data_buf[0] = reg;
	memcpy(&data_buf[1] ,buf ,size);

	i2cmsg.addr  = client->addr;
	i2cmsg.len   = size + 1;
	i2cmsg.buf   = data_buf;
	i2cmsg.flags = 0;

	/* Start the i2c transfer by calling host i2c driver function */
	ret = i2c_transfer(adapter, &i2cmsg, 1);
	if (ret < 0) {
		dev_info(&client->dev,
			 "%s: i2c_transfer failed!!!\n", __func__);
		return ret;
	}

	return 0;
}

static int max17058_write_reg(struct i2c_client *client, u8 reg, u16 value)
{
	s32 ret;
	u8 buf[2];

	buf[0] = value >> 8;
	buf[1] = value & 0x00ff;

#ifdef DEBUG
	printk("write reg %02x,data %02x%02x\n",reg,buf[0],buf[1]);
#endif
	ret = i2c_smbus_write_i2c_block_data(client, reg, 2 ,buf);

	if (ret < 0)
		dev_err(&client->dev, "%s: err %d\n", __func__, ret);

	return ret;
}

static u16 max17058_read_reg(struct i2c_client *client, u8 reg)
{
	s32 ret;
	u8 buf[2];

	ret = i2c_smbus_read_i2c_block_data(client, reg, 2, buf);
	if (ret < 0)
		dev_err(&client->dev, "%s: err %d\n", __func__, ret);

	return (((u16)buf[0] << 8) | buf[1]);
}

static void max17058_get_vcell(struct i2c_client *client)
{
	struct max17058_chip *chip = i2c_get_clientdata(client);
	u16 reg;

	reg = max17058_read_reg(client, MAX17058_VCELL_REG);

	chip->vcell = (u32)reg * 78125 / 1000 / 1000;

#ifdef DEBUG2
	printk("vcell %04x %dmv\n",reg,chip->vcell);
#endif
}

#ifdef ADC
int max17058_get_vcell_external(void)
{
	u16 reg;

	reg = max17058_read_reg(chip_st.client, MAX17058_VCELL_REG);

	chip_st.vcell = (u32)reg * 78125 / 1000 / 1000;

#ifdef ADC_DEBUG
	printk("vcell %04x %dmv\n",reg,chip_st.vcell);
#endif

	return chip_st.vcell;
}
#endif

static void max17058_get_soc(struct i2c_client *client)
{
	struct max17058_chip *chip = i2c_get_clientdata(client);
	u16 reg;

	reg = max17058_read_reg(client, MAX17058_SOC_REG);

	chip->soc = reg / 512;

#ifdef DEBUG2
	printk("soc %04x %d%%\n",reg ,chip->soc);
#endif

}

#ifdef TESTMODE
int max17058_get_soc_external(void)
{
	u16 reg;

	if(chip_st.client == NULL)
	{
		return 100;
	}

	reg = max17058_read_reg(chip_st.client, MAX17058_SOC_REG);

	chip_st.soc = reg / 512;

#ifdef TESTMODEDEBUG
	printk("soc %04x %d%%\n",reg ,chip_st.soc);
#endif
	return chip_st.soc;
}
#endif

static void rcomp_update(struct i2c_client *client,int temp)
{
	int rcomp;

	if(temp > 20)
	{
		rcomp = RCOMP0 + ((temp - 20) * TempCoUp / 100);
	}
	else if(temp < 20)
	{
		rcomp = RCOMP0 + ((temp - 20) * TempCoDown / 100);
	}
	else
	{
		rcomp = RCOMP0;
	}

	if(rcomp > 0xff)
	{
		rcomp = 0xff;
	}
	else if(rcomp < 0)
	{
		rcomp = 0;
	}

	max17058_write_reg(client, MAX17058_CONFIG_REG, rcomp << 8 | ALART_SETTING);
}

int get_max17058_soc(void)
{
	return chip_st.soc;
}

static void max17058_work(struct work_struct *work)
{
	struct max17058_chip *chip;
	int temp;

	chip = container_of(work, struct max17058_chip, work.work);

	max17058_get_vcell(chip->client);
	max17058_get_soc(chip->client);
	temp = da9052_get_battery_temp() / 1000;
#ifdef DEBUG
	printk("temp = %d\n",temp);
#endif
	rcomp_update(chip->client,temp);

	schedule_delayed_work(&chip->work, MAX17058_DELAY);
}

extern int da9052_get_ac_status(void);

static int __devinit max17058_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = to_i2c_adapter(client->dev.parent);
	struct max17058_chip *chip;
	u16 test_ocv,test_soc;
	int ret;
	int temp;
	u16 reg;
	int loaded_model = 0;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_I2C_BLOCK))
		return -EIO;

#if 0
	chip = kzalloc(sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;
#endif

	chip = &chip_st;
	chip->client = client;

	i2c_set_clientdata(client, chip);

//#ifdef DEBUG
	reg = max17058_read_reg(client, MAX17058_VERSION_REG);
	printk("max17058 version %04x\n",reg);
//#endif

#ifdef TESTMODE
	return 0;
#endif

#ifdef DEBUG
	max17058_get_soc(client);

	chip->ocv = max17058_read_reg(client, MAX17058_OCV_REG);
	printk("max17058 ocv %04x\n",chip->ocv);
#endif
	/* Unlock Model Access */
	ret = max17058_write_reg(client, 0x3E,0x4a57);
	/* Read OCV */
	chip->ocv = max17058_read_reg(client, MAX17058_OCV_REG);
#ifdef DEBUG
	printk("max17058 ocv %04x\n",chip->ocv);
#endif

	msleep(150);

	/* Write OCV */
	ret = max17058_write_reg(client, MAX17058_OCV_REG,OCVtest);
	ret = max17058_write_reg(client, 0x3E, 0x0000); //Send lock command

	msleep(150);

	test_soc = max17058_read_reg(client, MAX17058_SOC_REG);

#ifdef DEBUG
	printk("test_soc %04x\n",test_soc);
#endif
	if((test_soc >> 8) >= SOCCheckA && (test_soc >> 8) <= SOCCheckB)
	{
		printk("model was loaded\n");
		loaded_model = 1;
	}
	else
	{
		printk("model was NOT loaded\n");

		do
		{
			ret = max17058_write_reg(client, 0xFE, 0x5400); //Send POR command
			ret = max17058_write_reg(client, 0x3E, 0x4a57); //Send Unlock command
			test_ocv = max17058_read_reg(client, MAX17058_OCV_REG);
		} while(test_ocv == 0xffff);

#ifdef DEBUG
		printk("max17058 test_ocv %04x\n",chip->ocv);
#endif

		/* Write the Model */
		ret = max17058_write_buf_data(client,MAX17058_MODEL_REG , model_data ,sizeof(model_data));

		msleep(150);

		/* Write OCV */
		ret = max17058_write_reg(client, MAX17058_OCV_REG,OCVtest);
		ret = max17058_write_reg(client, 0x3E, 0x0000); //Send lock command

		msleep(150);

		test_soc = max17058_read_reg(client, MAX17058_SOC_REG);

#ifdef DEBUG
		printk("test_soc %04x\n",test_soc);
#endif
		if((test_soc >> 8) >= SOCCheckA && (test_soc >> 8) <= SOCCheckB)
		{
			printk("model was loaded successfully\n");
		}
		else
		{
			printk("model was NOT loaded successfully\n");
		}
	}

	ret = max17058_write_reg(client, 0x3E, 0x4a57); //Send Unlock command
	/* Write OCV */
	ret = max17058_write_reg(client, MAX17058_OCV_REG,chip->ocv);

	ret = max17058_write_reg(client, MAX17058_CONFIG_REG, RCOMP0 << 8 | ALART_SETTING);

	ret = max17058_write_reg(client, 0x3E, 0x0000); //Send lock command

	msleep(150);

	temp = da9052_get_battery_temp() / 1000;
#ifdef DEBUG
	printk("temp = %d\n",temp);
#endif
	rcomp_update(client,temp);
#ifndef ADC
	max17058_get_soc(client);

	INIT_DELAYED_WORK_DEFERRABLE(&chip->work, max17058_work);
	schedule_delayed_work(&chip->work, MAX17058_DELAY);
#endif

	return 0;
}

static int __devexit max17058_remove(struct i2c_client *client)
{
#ifndef ADC
	struct max17058_chip *chip = i2c_get_clientdata(client);

	cancel_delayed_work(&chip->work);
//	kfree(chip);
#endif
	return 0;
}

#ifdef CONFIG_PM

static int max17058_suspend(struct i2c_client *client,
		pm_message_t state)
{
#ifndef ADC
	struct max17058_chip *chip = i2c_get_clientdata(client);

	cancel_delayed_work(&chip->work);
#endif
	return 0;
}

static int max17058_resume(struct i2c_client *client)
{
#ifndef ADC
	struct max17058_chip *chip = i2c_get_clientdata(client);

	max17058_get_soc(client);
	schedule_delayed_work(&chip->work, MAX17058_DELAY);
#endif
	return 0;
}

#else

#define max17058_suspend NULL
#define max17058_resume NULL

#endif /* CONFIG_PM */

static const struct i2c_device_id max17058_id[] = {
	{ "max17058", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, max17058_id);

static struct i2c_driver max17058_i2c_driver = {
	.driver	= {
		.name	= "max17058",
	},
	.probe		= max17058_probe,
	.remove		= __devexit_p(max17058_remove),
	.suspend	= max17058_suspend,
	.resume		= max17058_resume,
	.id_table	= max17058_id,
};

static int __init max17058_init(void)
{
	return i2c_add_driver(&max17058_i2c_driver);
}
module_init(max17058_init);

static void __exit max17058_exit(void)
{
	i2c_del_driver(&max17058_i2c_driver);
}
module_exit(max17058_exit);

MODULE_AUTHOR("Sanyo Ltd..");
MODULE_DESCRIPTION("MAX17058 ModelGauge");
MODULE_LICENSE("GPL");
