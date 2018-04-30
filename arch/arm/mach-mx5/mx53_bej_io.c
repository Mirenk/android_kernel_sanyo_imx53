/*
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

#include <linux/types.h>
#include <linux/input.h>
#include <asm/mach-types.h>
#include <mach/gpio.h>

extern unsigned get_lcd_power_port_bej(void);
extern unsigned get_lcd_bl_port_bej(void);
extern unsigned get_lcd_5v_port_bej(void);
extern unsigned get_lcd_reset_port_bej(void);
extern unsigned get_csi0_rst_port_bej(void);
extern unsigned get_watchdog_port_bej(void);
extern unsigned get_watchdog_test_port_bej(void);
extern unsigned get_wifi_power_port_bej(void);
extern unsigned get_wifi_reset_port_bej(void);

#ifdef CONFIG_MACH_MX53_BEJ2
extern unsigned get_lcd_power_port_bej2(void);
extern unsigned get_lcd_bl_port_bej2(void);
//extern unsigned get_lcd_5v_port_bej2(void);
//extern unsigned get_lcd_reset_port_bej2(void);
extern unsigned get_csi0_rst_port_bej2(void);
extern unsigned get_watchdog_port_bej2(void);
extern unsigned get_watchdog_test_port_bej2(void);
extern unsigned get_wifi_power_port_bej2(void);
extern unsigned get_wifi_reset_port_bej2(void);
#endif

#define MX53_BEJ_LCD_PWR_EN			(2*32 + 20)	/* GPIO_3_20 */
#define MX53_BEJ_LCD_BL_EN			(3*32 + 20)	/* GPIO_4_20 */

void mx53_bej_lcd_power_en(int on)
{
	unsigned port;

#ifdef CONFIG_MACH_MX53_BEJ2
		port = get_lcd_power_port_bej2();
#endif

	if(on)
	{
		gpio_set_value(MX53_BEJ_LCD_PWR_EN, 1);
	}
	else
	{
		gpio_set_value(MX53_BEJ_LCD_PWR_EN, 0);
	}
}
EXPORT_SYMBOL(mx53_bej_lcd_power_en);


void mx53_bej_lcd_bl_en(int on)
{
	unsigned port;

	if (machine_is_mx53_bej())
	{
		port = get_lcd_bl_port_bej();
	}
	else if (machine_is_mx53_bej2())
	{
		port = get_lcd_bl_port_bej2();
	}
	else
		return;

	if(on)
	{
		gpio_set_value(MX53_BEJ_LCD_BL_EN, 1);
	}
	else
	{
		gpio_set_value(MX53_BEJ_LCD_BL_EN, 0);
	}
}
EXPORT_SYMBOL(mx53_bej_lcd_bl_en);

void mx53_bej_lcd_5v_ctl(int on)
{
	unsigned port;

	if (machine_is_mx53_bej())
	{
		port = get_lcd_5v_port_bej();
	}
	else if (machine_is_mx53_bej2())
	{
//		port = get_lcd_5v_port_bej2();
		return;
	}
	else
		return;

	if(on)
	{
		gpio_set_value(port, 1);
	}
	else
	{
		gpio_set_value(port, 0);
	}
}
EXPORT_SYMBOL(mx53_bej_lcd_5v_ctl);

void mx53_bej_lcd_reset_ctl(int on)
{
	unsigned port;

	if (machine_is_mx53_bej())
	{
		port = get_lcd_reset_port_bej();
	}
	else if (machine_is_mx53_bej2())
	{
//		port = get_lcd_reset_port_bej2();
		return;
	}
	else
		return;

	if(on)
	{
		gpio_set_value(port, 1);
	}
	else
	{
		gpio_set_value(port, 0);
	}
}
EXPORT_SYMBOL(mx53_bej_lcd_reset_ctl);

void mx53_bej_csi0_rst(int on)
{
	unsigned port;

	if (machine_is_mx53_bej())
	{
		port = get_csi0_rst_port_bej();
	}
	else if (machine_is_mx53_bej2())
	{
		port = get_csi0_rst_port_bej2();
	}
	else
		return;

	if(on)
	{
		gpio_set_value(port, 1);
	}
	else
	{
		gpio_set_value(port, 0);
	}
}
EXPORT_SYMBOL(mx53_bej_csi0_rst);

void mx53_bej_watchdog_en(int on)
{
	unsigned port;
	unsigned port2;

	if (machine_is_mx53_bej())
	{
		port = get_watchdog_port_bej();
		port2 = get_watchdog_test_port_bej();
	}
	else if (machine_is_mx53_bej2())
	{
		port = get_watchdog_port_bej2();
		port2 = get_watchdog_test_port_bej2();
	}
	else
		return;

	if(on)
	{
		gpio_set_value(port, 1);
		gpio_set_value(port2, 1);
	}
	else
	{
		gpio_set_value(port, 0);
		gpio_set_value(port2, 0);
	}
}
EXPORT_SYMBOL(mx53_bej_watchdog_en);

void mx53_bej_wifi_power_en(int on)
{
	unsigned port;

	if (machine_is_mx53_bej())
	{
		port = get_wifi_power_port_bej();
	}
	else if (machine_is_mx53_bej2())
	{
		port = get_wifi_power_port_bej2();
	}
	else
		return;

	if(on)
	{
		gpio_set_value(port, 1);
	}
	else
	{
		gpio_set_value(port, 0);
	}
}
EXPORT_SYMBOL(mx53_bej_wifi_power_en);

void mx53_bej_wifi_reset_en(int on)
{
	unsigned port;

	if (machine_is_mx53_bej())
	{
		port = get_wifi_reset_port_bej();
	}
	else if (machine_is_mx53_bej2())
	{
		port = get_wifi_reset_port_bej2();
	}
	else
		return;

	if(on)
	{
		gpio_set_value(port, 1);
	}
	else
	{
		gpio_set_value(port, 0);
	}
}
EXPORT_SYMBOL(mx53_bej_wifi_reset_en);
