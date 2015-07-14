/*
 * da9052 LED module declarations.
 *
 * Copyright(c) 2009 Dialog Semiconductor Ltd.
 * Copyright (C) 2012 Sanyo Ltd..
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#ifndef __LINUX_MFD_DA9052_LED_H
#define __LINUX_MFD_DA9052_LED_H

struct da9052_led_platform_data {
#define DA9052_LED_4			4
#define DA9052_LED_5			5
#ifdef CONFIG_MACH_MX53_BEJ2
#define DA9052_LED_6			6
#define DA9052_LED_7			7
#endif
#define DA9052_LED_MAX			2
	int id;
	const char *name;
	const char *default_trigger;
};

struct da9052_leds_platform_data {
	int num_leds;
	struct da9052_led_platform_data *led;
};

#ifdef CONFIG_MACH_MX53_BEJ2
#if 0
#define LED1110_ON 0x22
#define LED1110_OFF 0xaa
#define LED10_ON 0xa2
#define LED11_ON 0x2a
#define LED10_BLINK 0xae
#else
#define LED1110_ON 0x22
#define LED1110_OFF 0xaa
#define LED10_ON 0x2a
#define LED11_ON 0xa3
#define LED10_BLINK 0xea
#endif
//#define CONFIG_LED_SDTEST
#endif

#endif /* __LINUX_MFD_DA9052_LED_H */
