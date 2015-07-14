/*
 * Copyright (C) 2010-2011 Freescale Semiconductor, Inc. All Rights Reserved.
 *
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
#include <linux/string.h>
#include <linux/kernel.h>

int __initdata primary_di = { -1 };
static int __init di1_setup(char *__unused)
{
	primary_di = 1;
	return 1;
}
__setup("di1_primary", di1_setup);

static int __init di0_setup(char *__unused)
{
	primary_di = 0;
	return 1;
}
__setup("di0_primary", di0_setup);

int __initdata lcdif_sel_lcd = { 0 };
int __initdata lcd_seiko_on_j12 = { 0 };
static int __init lcd_setup(char *str)
{
	int s, ret;
	unsigned long sel;
	char *opt;

	s = *str;
	if (s == '=') {

		str++;
		while ((opt = strsep(&str, ",")) != NULL) {
			if (!*opt)
				continue;

			ret = strict_strtoul(opt, 0, &sel);
			if (ret == 0 && sel != 0) {
				lcdif_sel_lcd = sel;
				continue;
			}

			if (!strncmp(opt, "j12", 3)) {
				lcd_seiko_on_j12 = 1;
				continue;
			}
		}

		return 1;
	} else
		return 0;
}
__setup("lcd", lcd_setup);

#ifdef CONFIG_MACH_MX53_BEJ2
char __initdata serial_no[17];
static int __init serialno_setup(char *str)
{
	int i;
	int ret = 0;
	char s;

	s = *str;
	if (s == '=') {
		str++;
		for(i = 0; i < 16;i++)
		{
			if(str[i] == 0)
			{
				break;
			}

			if((('0' <= str[i]) && (str[i] <= '9')) || (('a' <= str[i]) && (str[i] <= 'z')) || (('A' <= str[i]) && (str[i] <= 'Z')) || (str[i] == '_'))
			{
				serial_no[i] = str[i];
			}
			else
			{
				ret = 1;
				break;
			}
		}
		serial_no[16] = 0;

		if(ret)
		{
			memcpy(serial_no,"0123456789ABCDEF",16);
		}

		return 1;
	}
	else
	{
		return 0;
	}
}
__setup("androidboot.serialno", serialno_setup);
#endif
