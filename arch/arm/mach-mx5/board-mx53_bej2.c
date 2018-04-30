/*
 * Copyright (C) 2011-2013 Freescale Semiconductor, Inc. All Rights Reserved.
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
#include <linux/clk.h>
#include <linux/fec.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/i2c.h>
#include <linux/i2c/mpr121_touchkey.h>
#include <linux/fsl_devices.h>
#include <linux/ahci_platform.h>
#include <linux/regulator/consumer.h>
#ifdef CONFIG_ANDROID_PMEM
#include <linux/android_pmem.h>
#endif
#ifdef CONFIG_ION
#include <linux/ion.h>
#endif
#include <linux/pwm_backlight.h>
#include <linux/mxcfb.h>
#include <linux/ipu.h>
#include <linux/spi/spi.h>
#include <linux/spi/flash.h>
#include <linux/mfd/da9052/da9052.h>

#include <linux/mtd/mtd.h>
#include <linux/mtd/map.h>
#include <linux/mtd/partitions.h>
#include <linux/memblock.h>

#include <mach/common.h>
#include <mach/hardware.h>
#include <mach/ipu-v3.h>
#include <mach/imx-uart.h>
#include <mach/iomux-mx53.h>
#include <mach/ahci_sata.h>
#include <mach/imx_rfkill.h>
#include <mach/mxc_asrc.h>
#include <mach/mxc_dvfs.h>
#include <mach/check_fuse.h>

#include <linux/i2c/rohm_bu21023.h> /* bej board */

#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/time.h>
#include <asm/setup.h>

#include "crm_regs.h"
#include "devices-imx53.h"
#include "devices.h"
#include "usb.h"
#include "pmic.h"

/* MX53 BEJ2 GPIO PIN configurations */
//--- GPIO1 ---//
#define MX53_BEJ_PWM	IMX_GPIO_NR(1, 1)
#define MX53_BEJ_JTAG_DE_B	IMX_GPIO_NR(1, 2)
#define MX53_BEJ_SYS_UP_CPU	IMX_GPIO_NR(1, 4)
#define MX53_BEJ_PMIC_FAULT	IMX_GPIO_NR(1, 5)
#define MX53_BEJ_SYS_ON_OFF_CTL	IMX_GPIO_NR(1, 7)
#define MX53_BEJ_PMIC_ON_OFF_REQ	IMX_GPIO_NR(1, 8)
#define MX53_BEJ_WATCHDOG_B	IMX_GPIO_NR(1, 9)

#define MX53_BEJ_OPEN1	IMX_GPIO_NR(1, 22)
#define MX53_BEJ_OPEN2	IMX_GPIO_NR(1, 23)
#define MX53_BEJ_OPEN3	IMX_GPIO_NR(1, 24)
#define MX53_BEJ_OPEN4	IMX_GPIO_NR(1, 25)
#define MX53_BEJ_OPEN5	IMX_GPIO_NR(1, 26)
#define MX53_BEJ_OPEN6	IMX_GPIO_NR(1, 27)
#define MX53_BEJ_OPEN7	IMX_GPIO_NR(1, 28)
#define MX53_BEJ_OPEN8	IMX_GPIO_NR(1, 29)
#define MX53_BEJ_OPEN9	IMX_GPIO_NR(1, 30)
#define MX53_BEJ_OPEN10	IMX_GPIO_NR(1, 31)

//--- GPIO2 ---///
#define MX53_BEJ_OPEN11	IMX_GPIO_NR(2, 4)
#define MX53_BEJ_HEADPHONE_DET	IMX_GPIO_NR(2, 5)
#define MX53_BEJ_TP44	IMX_GPIO_NR(2, 6)
#define MX53_BEJ_OPEN12	IMX_GPIO_NR(2, 7)
#define MX53_BEJ_KEY_HOME	IMX_GPIO_NR(2, 12)
#define MX53_BEJ_KEY_RETAN	IMX_GPIO_NR(2, 13)
#define MX53_BEJ_KEY_VOL_DOWN		IMX_GPIO_NR(2, 14)
#define MX53_BEJ_KEY_VOL_UP		IMX_GPIO_NR(2, 15)
#define MX53_BEJ_NANDBOOT	IMX_GPIO_NR(2, 16)
#define MX53_BEJ_OPEN13	IMX_GPIO_NR(2, 17)
#define MX53_BEJ_OPEN14	IMX_GPIO_NR(2, 18)
#define MX53_BEJ_OPEN15	IMX_GPIO_NR(2, 19)
#define MX53_BEJ_OPEN16	IMX_GPIO_NR(2, 20)
#define MX53_BEJ_OPEN17	IMX_GPIO_NR(2, 21)
#define MX53_BEJ_OPEN18	IMX_GPIO_NR(2, 22)
#define MX53_BEJ_TP22	IMX_GPIO_NR(2, 23)
#define MX53_BEJ_TP8	IMX_GPIO_NR(2, 24)
#define MX53_BEJ_TP3	IMX_GPIO_NR(2, 25)
#define MX53_BEJ_TP6	IMX_GPIO_NR(2, 26)
#define MX53_BEJ_OPEN19	IMX_GPIO_NR(2, 27)
#define MX53_BEJ_OPEN20	IMX_GPIO_NR(2, 28)
#define MX53_BEJ_OPEN21	IMX_GPIO_NR(2, 29)
#define MX53_BEJ_OPEN22	IMX_GPIO_NR(2, 30)
#define MX53_BEJ_TP7	IMX_GPIO_NR(2, 31)

//--- GPIO3 ---//
#define MX53_BEJ_OPEN23	IMX_GPIO_NR(3, 0)
#define MX53_BEJ_OPEN24	IMX_GPIO_NR(3, 1)
#define MX53_BEJ_OPEN25	IMX_GPIO_NR(3, 2)
#define MX53_BEJ_OPEN26	IMX_GPIO_NR(3, 3)
#define MX53_BEJ_OPEN27	IMX_GPIO_NR(3, 4)
#define MX53_BEJ_OPEN28	IMX_GPIO_NR(3, 5)
#define MX53_BEJ_OPEN29	IMX_GPIO_NR(3, 6)
#define MX53_BEJ_OPEN30	IMX_GPIO_NR(3, 7)
#define MX53_BEJ_OPEN31	IMX_GPIO_NR(3, 8)
#define MX53_BEJ_OPEN32	IMX_GPIO_NR(3, 9)
#define MX53_BEJ_WiFi_BT_PWR_EN	IMX_GPIO_NR(3, 10)
#define MX53_BEJ_RECOVERY_MODE_SW	IMX_GPIO_NR(3, 11)
#define MX53_BEJ_TP24	IMX_GPIO_NR(3, 12)
#define MX53_BEJ_SD1_CD         IMX_GPIO_NR(3, 13)
#define MX53_BEJ_TP25	IMX_GPIO_NR(3, 14)
#define MX53_BEJ_OPEN33	IMX_GPIO_NR(3, 15)
#define MX53_BEJ_OPEN34	IMX_GPIO_NR(3, 16)
#define MX53_BEJ_OPEN35	IMX_GPIO_NR(3, 17)
#define MX53_BEJ_OPEN36	IMX_GPIO_NR(3, 18)
#define MX53_BEJ_TP10	IMX_GPIO_NR(3, 19)
#define MX53_BEJ_LCD_PWR_EN	IMX_GPIO_NR(3, 20)
#define MX53_BEJ_TP11	IMX_GPIO_NR(3, 21)
#define MX53_BEJ_OPEN37	IMX_GPIO_NR(3, 22)
#define MX53_BEJ_OPEN38	IMX_GPIO_NR(3, 23)
#define MX53_BEJ_TP12	IMX_GPIO_NR(3, 24)
#define MX53_BEJ_TP13	IMX_GPIO_NR(3, 25)
#define MX53_BEJ_TP14	IMX_GPIO_NR(3, 26)
#define MX53_BEJ_OPEN39	IMX_GPIO_NR(3, 27)
#define MX53_BEJ_TP113	IMX_GPIO_NR(3, 28)
#define MX53_BEJ_OPEN40	IMX_GPIO_NR(3, 29)
#define MX53_BEJ_CHRG_OR_CMOS	IMX_GPIO_NR(3, 30)
#define MX53_BEJ_OPEN41	IMX_GPIO_NR(3, 31)

//--- GPIO4 ---///
#define MX53_BEJ_OPEN42	IMX_GPIO_NR(4, 0)
#define MX53_BEJ_OPEN43	IMX_GPIO_NR(4, 1)
#define MX53_BEJ_OPEN44	IMX_GPIO_NR(4, 2)
#define MX53_BEJ_OPEN45	IMX_GPIO_NR(4, 3)
#define MX53_BEJ_OPEN46	IMX_GPIO_NR(4, 4)
#define MX53_BEJ_WATCHDOG_TEST	IMX_GPIO_NR(4, 5)
#define MX53_BEJ_TP26	IMX_GPIO_NR(4, 10)
#define MX53_BEJ_SD1_WP         IMX_GPIO_NR(4, 11)
#define MX53_BEJ_TP27	IMX_GPIO_NR(4, 14)
#define MX53_BEJ_WLAN_RST	IMX_GPIO_NR(4, 15)
#define MX53_BEJ_OPEN48	IMX_GPIO_NR(4, 16)
#define MX53_BEJ_OPEN49	IMX_GPIO_NR(4, 17)
#define MX53_BEJ_OPEN50	IMX_GPIO_NR(4, 18)
#define MX53_BEJ_OPEN51	IMX_GPIO_NR(4, 19)
#define MX53_BEJ_LCD_BL_EN	IMX_GPIO_NR(4, 20)
#define MX53_BEJ_OPEN52	IMX_GPIO_NR(4, 21)
#define MX53_BEJ_OPEN53	IMX_GPIO_NR(4, 22)
#define MX53_BEJ_OPEN54	IMX_GPIO_NR(4, 23)
#define MX53_BEJ_OPEN55	IMX_GPIO_NR(4, 24)
#define MX53_BEJ_OPEN56	IMX_GPIO_NR(4, 25)
#define MX53_BEJ_OPEN57	IMX_GPIO_NR(4, 26)
#define MX53_BEJ_OPEN58	IMX_GPIO_NR(4, 27)
#define MX53_BEJ_OPEN59	IMX_GPIO_NR(4, 28)
#define MX53_BEJ_OPEN60	IMX_GPIO_NR(4, 29)
#define MX53_BEJ_OPEN61	IMX_GPIO_NR(4, 30)
#define MX53_BEJ_OPEN62	IMX_GPIO_NR(4, 31)

//--- GPIO5 ---//
#define MX53_BEJ_TP4   IMX_GPIO_NR(5, 0)
#define MX53_BEJ_AUD_AMP_STBY_B  IMX_GPIO_NR(5, 2)
#define MX53_BEJ_OPEN63	IMX_GPIO_NR(5, 4)
#define MX53_BEJ_OPEN64	IMX_GPIO_NR(5, 5)
#define MX53_BEJ_OPEN65	IMX_GPIO_NR(5, 6)
#define MX53_BEJ_OPEN66	IMX_GPIO_NR(5, 7)
#define MX53_BEJ_OPEN67	IMX_GPIO_NR(5, 8)
#define MX53_BEJ_OPEN68	IMX_GPIO_NR(5, 9)
#define MX53_BEJ_OPEN69	IMX_GPIO_NR(5, 10)
#define MX53_BEJ_OPEN70	IMX_GPIO_NR(5, 11)
#define MX53_BEJ_OPEN71	IMX_GPIO_NR(5, 12)
#define MX53_BEJ_OPEN72	IMX_GPIO_NR(5, 13)
#define MX53_BEJ_OPEN73	IMX_GPIO_NR(5, 14)
#define MX53_BEJ_OPEN74	IMX_GPIO_NR(5, 15)
#define MX53_BEJ_OPEN75	IMX_GPIO_NR(5, 16)
#define MX53_BEJ_OPEN76	IMX_GPIO_NR(5, 17)
#define MX53_BEJ_CSI0_PWN0	IMX_GPIO_NR(5, 20)
#define MX53_BEJ_OSC_CKIH1_EN	IMX_GPIO_NR(5, 22)
#define MX53_BEJ_ACCL_INT1_IN	IMX_GPIO_NR(5, 23)
#define MX53_BEJ_ACCL_INT2_IN	IMX_GPIO_NR(5, 24)
#define MX53_BEJ_CSI0_RST0	IMX_GPIO_NR(5, 25)

//--- GPIO6 ---//
#define MX53_BEJ_TP9	IMX_GPIO_NR(6, 6)
#define MX53_BEJ_OPEN77	IMX_GPIO_NR(6, 7)
#define MX53_BEJ_OPEN78	IMX_GPIO_NR(6, 8)
#define MX53_BEJ_OPEN79       IMX_GPIO_NR(6, 9)
#define MX53_BEJ_OPEN80       IMX_GPIO_NR(6, 10)
#define MX53_BEJ_OPEN81	IMX_GPIO_NR(6, 11)
#define MX53_BEJ_OPEN82	IMX_GPIO_NR(6, 12)
#define MX53_BEJ_OPEN83	IMX_GPIO_NR(6, 13)
#define MX53_BEJ_LED1	IMX_GPIO_NR(6, 14)
#define MX53_BEJ_LED2	IMX_GPIO_NR(6, 15)
#define MX53_BEJ_LED3	IMX_GPIO_NR(6, 16)
#define MX53_BEJ_KEY_SEARCH		IMX_GPIO_NR(6, 17)
#define MX53_BEJ_TP39	IMX_GPIO_NR(6, 18)

//--- GPIO7 ---//
#define MX53_BEJ_TOUCH_RESETB	IMX_GPIO_NR(7, 0)
#define MX53_BEJ_OPEN84	IMX_GPIO_NR(7, 1)
#define MX53_BEJ_TOUCH_INT	IMX_GPIO_NR(7, 2)
#define MX53_BEJ_KEY_MENU	IMX_GPIO_NR(7, 3)
#define MX53_BEJ_OPEN85		IMX_GPIO_NR(7, 6)
#define MX53_BEJ_WIFI_32K_EN	IMX_GPIO_NR(7, 7)
#define MX53_BEJ_CAME_EN	IMX_GPIO_NR(7, 8)
#define MX53_BEJ_DEVELOP_MODE_SW	IMX_GPIO_NR(7, 9)
#define MX53_BEJ_OPEN86	IMX_GPIO_NR(7, 10)
#define MX53_BEJ_PMIC_INT	IMX_GPIO_NR(7, 11)
#define MX53_BEJ_BAT_ALART	IMX_GPIO_NR(7, 12)
#define MX53_BEJ_OPEN88	IMX_GPIO_NR(7, 13)

#define MX53_OFFSET	(0x20000000)
#define TZIC_WAKEUP0_OFFSET	0x0E00
#define TZIC_WAKEUP1_OFFSET	0x0E04
#define TZIC_WAKEUP2_OFFSET	0x0E08
#define TZIC_WAKEUP3_OFFSET	0x0E0C
#define GPIO7_0_11_IRQ_BIT	(0x1<<11)

/* bej board */
#define SRTC_LPCR	0x10	/* LP Control Reg */
#define SRTC_LPCR_WAE	(1 << 4)	/* lp wakeup alarm enable */
#define SRTC_LPCR_ALP	(1 << 7) /* lp alarm flag */

void __init early_console_setup(unsigned long base, struct clk *clk);
static struct clk *sata_clk, *sata_ref_clk;
static int fs_in_sdcard;

#ifdef CONFIG_ANDROID_PMEM
extern struct platform_device mxc_android_pmem_device;
extern struct platform_device mxc_android_pmem_gpu_device;
#endif

extern char *lp_reg_id;
extern char *gp_reg_id;
extern void mx5_cpu_regulator_init(void);
extern int mx53_bej_init_da9052(void);

static iomux_v3_cfg_t mx53_bej_pads[] = {
		/* GPIO_19 WATCHDOG_TEST */
		MX53_PAD_GPIO_19__GPIO4_5,

		/* KEY_COL0 I2S_SCLK */
		MX53_PAD_KEY_COL0__AUDMUX_AUD5_TXC,
		/* KEY_ROW0 I2S_DOUT */
		MX53_PAD_KEY_ROW0__AUDMUX_AUD5_TXD,
		/* KEY_COL1 I2S_LRCLK */
		MX53_PAD_KEY_COL1__AUDMUX_AUD5_TXFS,
		/* KEY_ROW1 I2S_DIN */
		MX53_PAD_KEY_ROW1__AUDMUX_AUD5_RXD,
		/* KEY_COL2 TP26 */
		MX53_PAD_KEY_COL2__GPIO4_10,
		/* KEY_ROW2 open */
		MX53_PAD_KEY_ROW2__GPIO4_11,
		/* KEY_COL3 I2C2_SCL */
		MX53_PAD_KEY_COL3__I2C2_SCL,
		/* KEY_ROW3 I2C2_SDA */
		MX53_PAD_KEY_ROW3__I2C2_SDA,
		/* KEY_COL4 TP27 */
		MX53_PAD_KEY_COL4__GPIO4_14,
		/* KEY_ROW4 WLAN_RST */
		MX53_PAD_KEY_ROW4__GPIO4_15,

		/* DI0_DISP_CLK open */
		MX53_PAD_DI0_DISP_CLK__GPIO4_16,
		/* DI0_PIN2 open */
		MX53_PAD_DI0_PIN2__GPIO4_18,
		/* DI0_PIN3 open */
		MX53_PAD_DI0_PIN3__GPIO4_19,
		/* DI0_PIN4 LCD_BL_EN */
		MX53_PAD_DI0_PIN4__GPIO4_20,
		/* DI0_PIN15 open */
		MX53_PAD_DI0_PIN15__GPIO4_17,

		/* LPD0 open */
		MX53_PAD_DISP0_DAT0__GPIO4_21,
		/* LPD1 open */
		MX53_PAD_DISP0_DAT1__GPIO4_22,
		/* LPD2 open */
		MX53_PAD_DISP0_DAT2__GPIO4_23,
		/* LPD3 open */
		MX53_PAD_DISP0_DAT3__GPIO4_24,
		/* LPD4 open */
		MX53_PAD_DISP0_DAT4__GPIO4_25,
		/* LPD5 open */
		MX53_PAD_DISP0_DAT5__GPIO4_26,
		/* LPD6 open */
		MX53_PAD_DISP0_DAT6__GPIO4_27,
		/* LPD7 open */
		MX53_PAD_DISP0_DAT7__GPIO4_28,
		/* LPD8 open */
		MX53_PAD_DISP0_DAT8__GPIO4_29,
		/* LPD9 open */
		MX53_PAD_DISP0_DAT9__GPIO4_30,
		/* LPD10 open */
		MX53_PAD_DISP0_DAT10__GPIO4_31,
		/* LPD11 open */
		MX53_PAD_DISP0_DAT11__GPIO5_5,
		/* LPD12 open */
		MX53_PAD_DISP0_DAT12__GPIO5_6,
		/* LPD13 open */
		MX53_PAD_DISP0_DAT13__GPIO5_7,
		/* LPD14 open */
		MX53_PAD_DISP0_DAT14__GPIO5_8,
		/* LPD15 open */
		MX53_PAD_DISP0_DAT15__GPIO5_9,
		/* LPD16 open */
		MX53_PAD_DISP0_DAT16__GPIO5_10,
		/* LPD17 open */
		MX53_PAD_DISP0_DAT17__GPIO5_11,
		/* LPD18 open */
		MX53_PAD_DISP0_DAT18__GPIO5_12,
		/* LPD19 open */
		MX53_PAD_DISP0_DAT19__GPIO5_13,
		/* LPD20 open */
		MX53_PAD_DISP0_DAT20__GPIO5_14,
		/* LPD21 open */
		MX53_PAD_DISP0_DAT21__GPIO5_15,
		/* LPD22 open */
		MX53_PAD_DISP0_DAT22__GPIO5_16,
		/* LPD23 open */
		MX53_PAD_DISP0_DAT23__GPIO5_17,

		/* CSI0_PIXCLK */
		MX53_PAD_CSI0_PIXCLK__IPU_CSI0_PIXCLK,
		/* CSI0_MCLK CSI0_HSYNC */
		MX53_PAD_CSI0_MCLK__IPU_CSI0_HSYNC,
		/* CSI0_DATA_EN CSIO_PWN0 */
		MX53_PAD_CSI0_DATA_EN__GPIO5_20,
		/* CSI0_VSYNC */
		MX53_PAD_CSI0_VSYNC__IPU_CSI0_VSYNC,
		/* CSI0_DAT4 OSC_CKIH1_EN */
		MX53_PAD_CSI0_DAT4__GPIO5_22,
		/* CSI0_DAT5 ACCL_INT1_IN */
		MX53_PAD_CSI0_DAT5__GPIO5_23,
		/* CSI0_DAT6 ACCL_INT2_IN */
		MX53_PAD_CSI0_DAT6__GPIO5_24,
		/* CSI0_DAT7 CSI0_RST0 */
		MX53_PAD_CSI0_DAT7__GPIO5_25,
		/* CSI0_DAT8 I2C1_SDA */
		MX53_PAD_CSI0_DAT8__I2C1_SDA,
		/* CSI0_DAT9 I2C1_SCL */
		MX53_PAD_CSI0_DAT9__I2C1_SCL,
		/* CSI0_DAT10 UART1_TXD */
		MX53_PAD_CSI0_DAT10__UART1_TXD_MUX,
		/* CSI0_DAT11 UART1_RXD */
		MX53_PAD_CSI0_DAT11__UART1_RXD_MUX,
		/* CSI0_DAT12 */
		MX53_PAD_CSI0_DAT12__IPU_CSI0_D_12,
		/* CSI0_DAT13 */
		MX53_PAD_CSI0_DAT13__IPU_CSI0_D_13,
		/* CSI0_DAT14 */
		MX53_PAD_CSI0_DAT14__IPU_CSI0_D_14,
		/* CSI0_DAT15 */
		MX53_PAD_CSI0_DAT15__IPU_CSI0_D_15,
		/* CSI0_DAT16 */
		MX53_PAD_CSI0_DAT16__IPU_CSI0_D_16,
		/* CSI0_DAT17 */
		MX53_PAD_CSI0_DAT17__IPU_CSI0_D_17,
		/* CSI0_DAT18 */
		MX53_PAD_CSI0_DAT18__IPU_CSI0_D_18,
		/* CSI0_DAT19 */
		MX53_PAD_CSI0_DAT19__IPU_CSI0_D_19,

		/* EIM_A25 AUD_AMP_STBY_B */
		MX53_PAD_EIM_A25__GPIO5_2,
		/* EIM_EB2 open */
		MX53_PAD_EIM_EB2__GPIO2_30,
		/* EIM_D16 open */
		MX53_PAD_EIM_D16__GPIO3_16,
		/* EIM_D17 open */
		MX53_PAD_EIM_D17__GPIO3_17,
		/* EIM_D18 open */
		MX53_PAD_EIM_D18__GPIO3_18,
		/* EIM_D19 TP10 */
		MX53_PAD_EIM_D19__GPIO3_19,
		/* EIM_D20 LCD_PWR_EN */
		MX53_PAD_EIM_D20__GPIO3_20,
		/* EIM_D21 TP11 */
		MX53_PAD_EIM_D21__GPIO3_21,
		/* EIM_D22 open */
		MX53_PAD_EIM_D22__GPIO3_22,
		/* EIM_D23 open */
		MX53_PAD_EIM_D23__GPIO3_23,
		/* EIM_EB3 TP7 */
		MX53_PAD_EIM_EB3__GPIO2_31,
		/* EIM_D24 TP12 */
		MX53_PAD_EIM_D24__GPIO3_24,
		/* EIM_D25 TP13 */
		MX53_PAD_EIM_D25__GPIO3_25,
		/* EIM_D26 TP14 */
		MX53_PAD_EIM_D26__GPIO3_26,
		/* EIM_D27 open */
		MX53_PAD_EIM_D27__GPIO3_27,
		/* EIM_D28 TP113 */
		MX53_PAD_EIM_D28__GPIO3_28,
		/* EIM_D29 open */
		MX53_PAD_EIM_D29__GPIO3_29,
		/* EIM_D30 CHARGER_NOW_OR_CMOS_RUN */
		MX53_PAD_EIM_D30__GPIO3_30,
		/* EIM_D31 open */
		MX53_PAD_EIM_D31__GPIO3_31,
		/* EIM_A24 open */
		MX53_PAD_EIM_A24__GPIO5_4,
		/* EIM_A23 TP9 */
		MX53_PAD_EIM_A23__GPIO6_6,
		/* EIM_A22 NAND_BOOT */
		MX53_PAD_EIM_A22__GPIO2_16,
		/* EIM_A21 */
		MX53_PAD_EIM_A21__GPIO2_17,
		/* EIM_A20 */
		MX53_PAD_EIM_A20__GPIO2_18,
		/* EIM_A19 */
		MX53_PAD_EIM_A19__GPIO2_19,
		/* EIM_A18 */
		MX53_PAD_EIM_A18__GPIO2_20,
		/* EIM_A17 */
		MX53_PAD_EIM_A17__GPIO2_21,
		/* EIM_A16 */
		MX53_PAD_EIM_A16__GPIO2_22,
		/* EIM_CS0 TP22 */
		MX53_PAD_EIM_CS0__GPIO2_23,
		/* EIM_CS1 TP8*/
		MX53_PAD_EIM_CS1__GPIO2_24,
		/* EIM_OE TP3 */
		MX53_PAD_EIM_OE__GPIO2_25,
		/* EIM_RW TP6 */
		MX53_PAD_EIM_RW__GPIO2_26,
		/* EIM_LBA */
		MX53_PAD_EIM_LBA__GPIO2_27,
		/* EIM_EB0 */
		MX53_PAD_EIM_EB0__GPIO2_28,
		/* EIM_EB1 */
		MX53_PAD_EIM_EB1__GPIO2_29,
		/* EIM_DA0 NFLD0 */
		MX53_PAD_EIM_DA0__GPIO3_0,
		/* EIM_DA1 NFLD1 */
		MX53_PAD_EIM_DA1__GPIO3_1,
		/* EIM_DA2 NFLD2 */
		MX53_PAD_EIM_DA2__GPIO3_2,
		/* EIM_DA3 NFLD3 */
		MX53_PAD_EIM_DA3__GPIO3_3,
		/* EIM_DA4 NFLD4 */
		MX53_PAD_EIM_DA4__GPIO3_4,
		/* EIM_DA5 NFLD5 */
		MX53_PAD_EIM_DA5__GPIO3_5,
		/* EIM_DA6 NFLD6 */
		MX53_PAD_EIM_DA6__GPIO3_6,
		/* EIM_DA7 NFLD7 */
		MX53_PAD_EIM_DA7__GPIO3_7,
		/* EIM_DA8 NFLD8 */
		MX53_PAD_EIM_DA8__GPIO3_8,
		/* EIM_DA9 NFLD9 */
		MX53_PAD_EIM_DA9__GPIO3_9,
		/* EIM_DA10 WiFi_BT_PWR_EN */
		MX53_PAD_EIM_DA10__GPIO3_10,
		/* EIM_DA11 RECOVERY_MODE_SW */
		MX53_PAD_EIM_DA11__GPIO3_11,
		/* EIM_DA12 TP24 */
		MX53_PAD_EIM_DA12__GPIO3_12,
		/* EIM_DA13 SD1_CD */
		MX53_PAD_EIM_DA13__GPIO3_13,
		/* EIM_DA14 TP25 */
		MX53_PAD_EIM_DA14__GPIO3_14,
		/* EIM_DA15 open */
		MX53_PAD_EIM_DA15__GPIO3_15,
		/* NANDF_WE_B open */
		MX53_PAD_NANDF_WE_B__GPIO6_12,
		/* NANDF_RE_B TP18 */
		MX53_PAD_NANDF_RE_B__GPIO6_13,
		/* EIM_WAIT TP4 */
		MX53_PAD_EIM_WAIT__GPIO5_0,

		/* LVDS1_TX3_P */
		MX53_PAD_LVDS1_TX3_P__LDB_LVDS1_TX3,
		/* LVDS1_TX2_P */
		MX53_PAD_LVDS1_TX2_P__LDB_LVDS1_TX2,
		/* LVDS1_CLK_P */
		MX53_PAD_LVDS1_CLK_P__LDB_LVDS1_CLK,
		/* LVDS1_TX1_P */
		MX53_PAD_LVDS1_TX1_P__LDB_LVDS1_TX1,
		/* LVDS1_TX0_P */
		MX53_PAD_LVDS1_TX0_P__LDB_LVDS1_TX0,

		/* LVDS0_TX3_P */
		MX53_PAD_LVDS0_TX3_P__GPIO7_22,
		/* LVDS0_CLK_P */
		MX53_PAD_LVDS0_CLK_P__GPIO7_24,
		/* LVDS0_TX2_P */
		MX53_PAD_LVDS0_TX2_P__GPIO7_26,
		/* LVDS0_TX1_P */
		MX53_PAD_LVDS0_TX1_P__GPIO7_28,
		/* LVDS0_TX0_P */
		MX53_PAD_LVDS0_TX0_P__GPIO7_30,

		/* GPIO_10 open */
		/* GPIO_10 open->32KOUT */
		MX53_PAD_GPIO_10__OSC32k_32K_OUT,
		/* GPIO_11 open */
		MX53_PAD_GPIO_11__GPIO4_1,
		/* GPIO_12 open */
		MX53_PAD_GPIO_12__GPIO4_2,
		/* GPIO_13 open */
		MX53_PAD_GPIO_13__GPIO4_3,
		/* GPIO_14 open */
		MX53_PAD_GPIO_14__GPIO4_4,

		/* NANDF_CLE */
		MX53_PAD_NANDF_CLE__GPIO6_7,
		/* NANDF_ALE */
		MX53_PAD_NANDF_ALE__GPIO6_8,
		/* NANDF_WP_B */
		MX53_PAD_NANDF_WP_B__GPIO6_9,
		/* NANDF_RB0 */
		MX53_PAD_NANDF_RB0__GPIO6_10,
		/* NANDF_CS0 */
		MX53_PAD_NANDF_CS0__GPIO6_11,
		/* NANDF_CS1 LED1 */
		MX53_PAD_NANDF_CS1__GPIO6_14,
		/* NANDF_CS2 LED2 */
		MX53_PAD_NANDF_CS2__GPIO6_15,
		/* NANDF_CS3 LED3 */
		MX53_PAD_NANDF_CS3__GPIO6_16,

		/* FEC_MDIO */
		MX53_PAD_FEC_MDIO__GPIO1_22,
		/* FEC_REF_CLK_CPU */
		MX53_PAD_FEC_REF_CLK__GPIO1_23,
		/* FEC_RX_ER */
		MX53_PAD_FEC_RX_ER__GPIO1_24,
		/* FEC_CRS_DV */
		MX53_PAD_FEC_CRS_DV__GPIO1_25,
		/* FEC_RXD1 */
		MX53_PAD_FEC_RXD1__GPIO1_26,
		/* FEC_RXD0 */
		MX53_PAD_FEC_RXD0__GPIO1_27,
		/* FEC_TXEN */
		MX53_PAD_FEC_TX_EN__GPIO1_28,
		/* FEC_TXD1 */
		MX53_PAD_FEC_TXD1__GPIO1_29,
		/* FEC_TXD0 */
		MX53_PAD_FEC_TXD0__GPIO1_30,
		/* FEC_MDC */
		MX53_PAD_FEC_MDC__GPIO1_31,

		/* PATA_DIOW KEY_SEARCH */
		MX53_PAD_PATA_DIOW__GPIO6_17,
		/* PATA_DMACK TP39 */
		MX53_PAD_PATA_DMACK__GPIO6_18,
		/* PATA_DMARQ TOUCH_RESETB */
		MX53_PAD_PATA_DMARQ__GPIO7_0,
		/* PATA_BUFFER_EN open */
		MX53_PAD_PATA_BUFFER_EN__GPIO7_1,
		/* PATA_INTRQ TOUCH_INT */
		MX53_PAD_PATA_INTRQ__GPIO7_2,
		/* PATA_DIOR KEY_MENU */
		MX53_PAD_PATA_DIOR__GPIO7_3,
		/* PATA_RESET_B SD3_CMD */
		MX53_PAD_PATA_RESET_B__ESDHC3_CMD,
		/* PATA_IORDY SD3_CLK */
		MX53_PAD_PATA_IORDY__ESDHC3_CLK,
		/* PATA_CS_0 DEVELOP_MODE_SW */
		MX53_PAD_PATA_CS_0__GPIO7_9,
		/* PATA_CS_1 open */
		MX53_PAD_PATA_CS_1__GPIO7_10,
		/* PATA_DA_0 open */
		MX53_PAD_PATA_DA_0__GPIO7_6,
		/* PATA_DA_1 WIFI_32K_EN */
		MX53_PAD_PATA_DA_1__GPIO7_7,
		/* PATA_DA_2 CAME_EN */
		MX53_PAD_PATA_DA_2__GPIO7_8,
		/* PATA_DATA0 SD3_DATA4 */
		MX53_PAD_PATA_DATA0__ESDHC3_DAT4,
		/* PATA_DATA1 SD3_DATA5 */
		MX53_PAD_PATA_DATA1__ESDHC3_DAT5,
		/* PATA_DATA2 SD3_DATA6 */
		MX53_PAD_PATA_DATA2__ESDHC3_DAT6,
		/* PATA_DATA3 SD3_DATA7 */
		MX53_PAD_PATA_DATA3__ESDHC3_DAT7,
		/* PATA_DATA4 open */
		MX53_PAD_PATA_DATA4__GPIO2_4,
		/* PATA_DATA5 HEADPHONE_DET */
		MX53_PAD_PATA_DATA5__GPIO2_5,
		/* PATA_DATA6 TP44 */
		MX53_PAD_PATA_DATA6__GPIO2_6,
		/* PATA_DATA7 open */
		MX53_PAD_PATA_DATA7__GPIO2_7,
		/* PATA_DATA8 SD3_DATA0 */
		MX53_PAD_PATA_DATA8__ESDHC3_DAT0,
		/* PATA_DATA9 SD3_DATA1 */
		MX53_PAD_PATA_DATA9__ESDHC3_DAT1,
		/* PATA_DATA10 SD3_DATA2 */
		MX53_PAD_PATA_DATA10__ESDHC3_DAT2,
		/* PATA_DATA11 SD3_DATA3 */
		MX53_PAD_PATA_DATA11__ESDHC3_DAT3,
		/* PATA_DATA12 KEY_HOME */
		MX53_PAD_PATA_DATA12__GPIO2_12,
		/* PATA_DATA13 KEY_RETAN */
		MX53_PAD_PATA_DATA13__GPIO2_13,
		/* PATA_DATA14 KEY_VOL- */
		MX53_PAD_PATA_DATA14__GPIO2_14,
		/* PATA_DATA15 KEY_VOL+ */
		MX53_PAD_PATA_DATA15__GPIO2_15,

		/* SD1_DATA0 */
		MX53_PAD_SD1_DATA0__ESDHC1_DAT0,
		/* SD1_DATA1 */
		MX53_PAD_SD1_DATA1__ESDHC1_DAT1,
		/* SD1_CMD */
		MX53_PAD_SD1_CMD__ESDHC1_CMD,
		/* SD1_DATA2 */
		MX53_PAD_SD1_DATA2__ESDHC1_DAT2,
		/* SD1_CLK */
		MX53_PAD_SD1_CLK__ESDHC1_CLK,
		/* SD1_DATA3 */
		MX53_PAD_SD1_DATA3__ESDHC1_DAT3,
		/* SD2_CLK */
		MX53_PAD_SD2_CLK__ESDHC2_CLK,
		/* SD2_CMD */
		MX53_PAD_SD2_CMD__ESDHC2_CMD,
		/* SD2_DATA3 */
		MX53_PAD_SD2_DATA3__ESDHC2_DAT3,
		/* SD2_DATA2 */
		MX53_PAD_SD2_DATA2__ESDHC2_DAT2,
		/* SD2_DATA1 */
		MX53_PAD_SD2_DATA1__ESDHC2_DAT1,
		/* SD2_DATA0 */
		MX53_PAD_SD2_DATA0__ESDHC2_DAT0,

		/* GPIO_0 (CLK0) */
		MX53_PAD_GPIO_0__CCM_SSI_EXT1_CLK,
		/* GPIO_1 LED_PWM */
		MX53_PAD_GPIO_1__PWM2_PWMO,
		/* GPIO_2 JTAG_DE_B */
		MX53_PAD_GPIO_2__GPIO1_2,
		/* GPIO_3 I2C3_SCL */
		MX53_PAD_GPIO_3__I2C3_SCL,
		/* GPIO_4 SYS_UP_CPU */
		MX53_PAD_GPIO_4__GPIO1_4,
		/* GPIO_5 PMIC_FAULT */
		MX53_PAD_GPIO_5__GPIO1_5,
		/* GPIO_6 I2C3_SDA */
		MX53_PAD_GPIO_6__I2C3_SDA,
		/* GPIO_7 SYS_ON_OFF_CTL */
		MX53_PAD_GPIO_7__GPIO1_7,
		/* GPIO_8 PMIC_ON_OFF_REQ */
		MX53_PAD_GPIO_8__GPIO1_8,
		/* GPIO_9 WDOG1_WDOG_B */
		MX53_PAD_GPIO_9__GPIO1_9,
		/* GPIO_16 PMIC_INT */
		MX53_PAD_GPIO_16__GPIO7_11,
		/* GPIO_17 open */
		MX53_PAD_GPIO_17__GPIO7_12_BEJ,
		/* GPIO_18 open */
		MX53_PAD_GPIO_18__GPIO7_13,
};

#if defined(CONFIG_KEYBOARD_GPIO) || defined(CONFIG_KEYBOARD_GPIO_MODULE)
#define GPIO_BUTTON(gpio_num, ev_code, act_low, descr, wake, debounce_ms) \
{                                                               \
	.gpio           = gpio_num,                             \
	.type           = EV_KEY,                               \
	.code           = ev_code,                              \
	.active_low     = act_low,                              \
	.desc           = "btn " descr,                         \
	.wakeup         = wake,                                 \
	.debounce_interval = debounce_ms,                       \
}

static struct gpio_keys_button bej_buttons[] = {
	GPIO_BUTTON(MX53_BEJ_DEVELOP_MODE_SW, KEY_BACK, 0, "back", 0, 0),
	GPIO_BUTTON(MX53_BEJ_RECOVERY_MODE_SW, KEY_MENU, 0, "menu", 0, 0),
};

static struct gpio_keys_platform_data bej_button_data = {
	.buttons        = bej_buttons,
	.nbuttons       = ARRAY_SIZE(bej_buttons),
};

static struct platform_device bej_button_device = {
	.name           = "gpio-keys",
	.id             = -1,
	.num_resources  = 0,
	.dev            = {
		.platform_data = &bej_button_data,
		}
};

static void __init smd_add_device_buttons(void)
{
	platform_device_register(&bej_button_device);
}
#else
static void __init smd_add_device_buttons(void) {}
#endif

static const struct imxuart_platform_data mx53_bej_uart_data __initconst = {
	.flags = IMXUART_HAVE_RTSCTS,
	.dma_req_rx = MX53_DMA_REQ_UART3_RX,
	.dma_req_tx = MX53_DMA_REQ_UART3_TX,
};

static inline void mx53_bej_init_uart(void)
{
	imx53_add_imx_uart(0, NULL);
	imx53_add_imx_uart(1, NULL);
	imx53_add_imx_uart(2, &mx53_bej_uart_data);
}

static const struct imxi2c_platform_data mx53_bej_i2c_data __initconst = {
	.bitrate = 200000,
};

extern void __iomem *tzic_base;
void __iomem *srtc_base;
unsigned long lp_cr;

static void smd_da9053_irq_wakeup_only_fixup(void)
{
	if (NULL == tzic_base) {
		pr_err("fail to map MX53_TZIC_BASE_ADDR\n");
		return;
	}

	srtc_base = ioremap(MX53_SRTC_BASE_ADDR - MX53_OFFSET, 0x40);
	if (NULL == srtc_base) {
		pr_err("fail to map MX53_SRTC_BASE_ADDR\n");
		iounmap(tzic_base);
		return;
	}

	lp_cr = __raw_readl(srtc_base + SRTC_LPCR);
	if(lp_cr & (SRTC_LPCR_ALP | SRTC_LPCR_WAE))
	{
		__raw_writel(1 << MX53_INT_SRTC_NTZ, tzic_base + TZIC_WAKEUP0_OFFSET);
	}
	else
	{
			__raw_writel(0, tzic_base + TZIC_WAKEUP0_OFFSET);
	}
	__raw_writel(0, tzic_base + TZIC_WAKEUP1_OFFSET);
	__raw_writel(0, tzic_base + TZIC_WAKEUP2_OFFSET);
	/* only enable irq wakeup for da9053 */
	__raw_writel(GPIO7_0_11_IRQ_BIT, tzic_base + TZIC_WAKEUP3_OFFSET);
}

static void smd_suspend_enter(void)
{
	da9053_suspend_cmd_sw();
	smd_da9053_irq_wakeup_only_fixup();
}

static void smd_suspend_exit(void)
{
	da9053_restore_volt_settings();
}

static struct mxc_pm_platform_data smd_pm_data = {
	.suspend_enter = smd_suspend_enter,
	.suspend_exit = smd_suspend_exit,
};

/* SDIO Card Slot */
static const struct esdhc_platform_data mx53_bej_sd1_data __initconst = {
	.cd_gpio = MX53_BEJ_SD1_CD,
	.wp_gpio = MX53_BEJ_SD1_WP,
	.keep_power_at_suspend = 1,
	.delay_line = 0,
	.cd_type = ESDHC_CD_CONTROLLER,
};

/* SDIO Wifi */
static const struct esdhc_platform_data mx53_bej_sd2_data __initconst = {
	.always_present = 1,
	.keep_power_at_suspend = 1,
	.delay_line = 0,
	.cd_type = ESDHC_CD_PERMANENT,
};

/* SDIO Internal eMMC */
static const struct esdhc_platform_data mx53_bej_sd3_data __initconst = {
	.always_present = 1,
	.keep_power_at_suspend = 1,
	.support_8bit = 1,
	.delay_line = 0,
	.cd_type = ESDHC_CD_PERMANENT,
};

static int bej2_pwdn_enable(int enable)
{
//	printk("camera bej2_pwdn_enable %d\n",enable);
	if(enable)
	{
		gpio_set_value(MX53_BEJ_CSI0_PWN0, 1);
	}
	else
	{
		gpio_set_value(MX53_BEJ_CSI0_PWN0, 0);
	}
	return 0;
}

#if 0
static void mx53_bej_csi0_io_init(void)
{
	struct clk *clk;
	uint32_t freq = 0;

	clk = clk_get(NULL, "ssi_ext1_clk");
	if (clk) {
		freq = clk_round_rate(clk, 24000000);
		clk_set_rate(clk, freq);
		clk_enable(clk);
	} else
		printk(KERN_DEBUG "Failed to get ssi_ext1_clk\n");

	/* Camera reset */
	gpio_request(MX53_BEJ_CSI0_RST, "cam-reset");
	gpio_direction_output(MX53_BEJ_CSI0_RST, 1);

	/* Camera power down */
	gpio_request(MX53_BEJ_CSI0_PWN, "cam-pwdn");
	gpio_direction_output(MX53_BEJ_CSI0_PWN, 1);
	mx53_bej_csi0_cam_powerdown(1);
	msleep(5);
	mx53_bej_csi0_cam_powerdown(0);
	msleep(5);
	gpio_set_value(MX53_BEJ_CSI0_RST, 0);
	msleep(1);
	gpio_set_value(MX53_BEJ_CSI0_RST, 1);
	msleep(5);
	mx53_bej_csi0_cam_powerdown(1);
}
#endif

static struct fsl_mxc_camera_platform_data camera_data = {
	.mclk = 24000000,
//	.mclk_source = 0,
	.csi = 0,
//	.io_init = mx53_bej_csi0_io_init,
//	.pwdn = mx53_bej_csi0_cam_powerdown,
	.pwdn = bej2_pwdn_enable,
};
/*
static struct fsl_mxc_capture_platform_data capture_data = {
	.csi = 0,
	.ipu = 0,
	.mclk_source = 0,
	.is_mipi = 0,
};
*/
static struct fsl_mxc_lightsensor_platform_data ls_data = {
	.rext = 700,    /* calibration: 499K->700K */
};

static int mma8452_position = 4;

static struct i2c_board_info mxc_i2c0_board_info[] __initdata = {
	{
		I2C_BOARD_INFO("mma8452", 0x1c),
		.platform_data = (void *)&mma8452_position,
	},
	{
		I2C_BOARD_INFO("rnss2e1", 0x30),
		.platform_data = (void *)&camera_data,
	},
	{
		I2C_BOARD_INFO("sr200pc20", 0x20),
		.platform_data = (void *)&camera_data,
	},
	{
		I2C_BOARD_INFO("max17058", 0x36),
	},

};

static struct i2c_board_info mxc_i2c1_board_info[] __initdata = {
	{
		I2C_BOARD_INFO("sgtl5000", 0x0a)
	},
};

/*
static int mx53_bej_spi_cs[] = {
	MX53_BEJ_ECSPI1_CS0,
	MX53_BEJ_ECSPI1_CS1,
};
*/

static struct spi_imx_master mx53_bej_spi_data = {
	.chipselect = NULL,
	.num_chipselect = NULL,
};

static void mxc_iim_enable_fuse(void)
{
	u32 reg;
	if (!ccm_base)
		return;
	/* enable fuse blown */
	reg = readl(ccm_base + 0x64);
	reg |= 0x10;
	writel(reg, ccm_base + 0x64);
}

static void mxc_iim_disable_fuse(void)
{
	u32 reg;
	if (!ccm_base)
		return;
	/* enable fuse blown */
	reg = readl(ccm_base + 0x64);
	reg &= ~0x10;
	writel(reg, ccm_base + 0x64);
}


static struct mxc_iim_platform_data iim_data = {
	.bank_start = MXC_IIM_MX53_BANK_START_ADDR,
	.bank_end   = MXC_IIM_MX53_BANK_END_ADDR,
	.enable_fuse = mxc_iim_enable_fuse,
	.disable_fuse = mxc_iim_disable_fuse,
};

/*
static void sii9022_hdmi_reset(void)
{
	gpio_set_value(MX53_BEJ_HDMI_RESET_B, 0);
	msleep(10);
	gpio_set_value(MX53_BEJ_HDMI_RESET_B, 1);
	msleep(10);
}

static struct fsl_mxc_lcd_platform_data sii902x_hdmi_data = {
	.reset = sii9022_hdmi_reset,
	.analog_reg = "DA9052_LDO2",
};
*/
#ifdef CONFIG_ANDROID_PMEM
static struct android_pmem_platform_data android_pmem_data = {
	.name = "pmem_adsp",
	.size = SZ_64M,
	.cached = 0,
};

static struct android_pmem_platform_data android_pmem_gpu_data = {
	.name = "pmem_gpu",
	.size = SZ_64M,
	.cached = 1,
};
#endif

#ifdef CONFIG_ION
#define	ION_VPU	0
#define	ION_GPU	1
static struct ion_platform_data imx_ion_data = {
	.nr = 2,
	.heaps = {
		{
		.id = ION_VPU,
		.type = ION_HEAP_TYPE_CARVEOUT,
		.name = "vpu_ion",
		.size = SZ_64M,
		},
		{
		.id = ION_GPU,
		.type = ION_HEAP_TYPE_CARVEOUT,
		.name = "gpu_ion",
		.size = SZ_64M,
		},
	},
};
#endif

static struct i2c_board_info mxc_i2c2_board_info[] __initdata = {
	{
		I2C_BOARD_INFO(ROHM_I2C_NAME, ROHM_I2C_Address),
		.irq  = gpio_to_irq(MX53_BEJ_TOUCH_INT),
	},
};

static void mx53_bej_usbotg_vbus(bool on)
{
#if 0
	if (on)
		gpio_set_value(MX53_BEJ_OTG_VBUS, 1);
	else
		gpio_set_value(MX53_BEJ_OTG_VBUS, 0);
#endif
}

static void __init mx53_bej_init_usb(void)
{
//	int ret = 0;
/*
	imx_otg_base = MX53_IO_ADDRESS(MX53_OTG_BASE_ADDR);
	ret = gpio_request(MX53_BEJ_OTG_VBUS, "usb-pwr");
	if (ret) {
		printk(KERN_ERR"failed to get GPIO SMD_OTG_VBUS: %d\n", ret);
		return;
	}*/
//	gpio_direction_output(MX53_BEJ_OTG_VBUS, 0);

//	mx5_set_otghost_vbus_func(mx53_bej_usbotg_vbus);
	mx5_usb_dr_init();
//	mx5_usbh1_init();
}

static struct mxc_audio_platform_data smd_audio_data;

static int smd_sgtl5000_init(void)
{
	smd_audio_data.sysclk = 22579200;

	/* Enable OSC_CKIH1_EN for audio */
	gpio_request(MX53_BEJ_OSC_CKIH1_EN, "osc-en");
	gpio_direction_output(MX53_BEJ_OSC_CKIH1_EN, 1);
	return 0;
}

static int smd_sgtl5000_amp_enable(int enable)
{
	gpio_request(MX53_BEJ_AUD_AMP_STBY_B, "amp-standby");
	if (enable)
		gpio_direction_output(MX53_BEJ_AUD_AMP_STBY_B, 1);
	else
		gpio_direction_output(MX53_BEJ_AUD_AMP_STBY_B, 0);
	gpio_free(MX53_BEJ_AUD_AMP_STBY_B);
	return 0;
}

static struct mxc_audio_platform_data smd_audio_data = {
	.ssi_num = 1,
	.src_port = 2,
	.ext_port = 5,
	.init = smd_sgtl5000_init,
	.amp_enable = smd_sgtl5000_amp_enable,
	.hp_gpio = MX53_BEJ_HEADPHONE_DET,
	.hp_active_low = 1,
};

static struct platform_device smd_audio_device = {
	.name = "imx-sgtl5000",
};

static struct imx_ssi_platform_data smd_ssi_pdata = {
	.flags = IMX_SSI_DMA | IMX_SSI_SYN,
};

static struct fsl_mxc_lcd_platform_data lcdif_data = {
	.ipu_id = 0,
	.disp_id = 0,
	.default_ifmt = IPU_PIX_FMT_RGB565,
};

static struct imx_asrc_platform_data imx_asrc_data = {
	.channel_bits = 4,
	.clk_map_ver = 2,
};

static struct ipuv3_fb_platform_data smd_fb_data[] = {
	{
	.disp_dev = "ldb",
	.interface_pix_fmt = IPU_PIX_FMT_RGB24,
	.mode_str = "WSVGA",
	.default_bpp = 32,
	.int_clk = false,
	.late_init = false,
	.panel_width_mm = 203,
	.panel_height_mm = 152,
	}, {
	.disp_dev = "sii902x_hdmi",
	.interface_pix_fmt = IPU_PIX_FMT_RGB24,
	.mode_str = "1024x768M-32@60",
	.default_bpp = 32,
	.int_clk = false,
	.late_init = false,
	},
};

static struct imx_ipuv3_platform_data ipu_data = {
	.rev = 3,
	.csi_clk[0] = "ssi_ext1_clk",
	.bypass_reset = false,
};

static struct platform_pwm_backlight_data mxc_pwm_backlight_data = {
	.pwm_id = 1,
	.max_brightness = 248,
	.dft_brightness = 128,
	.pwm_period_ns = 50000,
};

static struct mxc_gpu_platform_data mx53_bej_gpu_pdata __initdata = {
	.enable_mmu = 0,
};

static struct fsl_mxc_ldb_platform_data ldb_data = {
	.ipu_id = 0,
	.disp_id = 1,
	.ext_ref = 1,
	.mode = LDB_SIN1,
};

#if 0
static struct mxc_spdif_platform_data mxc_spdif_data = {
	.spdif_tx = 1,
	.spdif_rx = 0,
	.spdif_clk_44100 = 0,	/* Souce from CKIH1 for 44.1K */
	/* Source from CCM spdif_clk (24M) for 48k and 32k
	 * It's not accurate
	 */
	.spdif_clk_48000 = 1,
	.spdif_div_44100 = 8,
	.spdif_div_48000 = 8,
	.spdif_div_32000 = 12,
	.spdif_rx_clk = 0,	/* rx clk from spdif stream */
	.spdif_clk = NULL,	/* spdif bus clk */
};
#endif

static struct mxc_dvfs_platform_data smd_dvfs_core_data = {
	.reg_id = "cpu_vddgp",
	.clk1_id = "cpu_clk",
	.clk2_id = "gpc_dvfs_clk",
	.gpc_cntr_offset = MXC_GPC_CNTR_OFFSET,
	.gpc_vcr_offset = MXC_GPC_VCR_OFFSET,
	.ccm_cdcr_offset = MXC_CCM_CDCR_OFFSET,
	.ccm_cacrr_offset = MXC_CCM_CACRR_OFFSET,
	.ccm_cdhipr_offset = MXC_CCM_CDHIPR_OFFSET,
	.prediv_mask = 0x1F800,
	.prediv_offset = 11,
	.prediv_val = 3,
	.div3ck_mask = 0xE0000000,
	.div3ck_offset = 29,
	.div3ck_val = 2,
	.emac_val = 0x08,
	.upthr_val = 25,
	.dnthr_val = 9,
	.pncthr_val = 33,
	.upcnt_val = 10,
	.dncnt_val = 10,
	.delay_time = 30,
};

static struct mxc_regulator_platform_data smd_regulator_data = {
	.cpu_reg_id = "cpu_vddgp",
};

extern struct imx_mxc_gpu_data imx53_gpu_data;

static void __init fixup_mxc_board(struct machine_desc *desc, struct tag *tags,
				   char **cmdline, struct meminfo *mi)
{
	char *str;
	struct tag *t;
	int i = 0;

	for_each_tag(t, tags) {
		if (t->hdr.tag == ATAG_CMDLINE) {
#ifdef CONFIG_ANDROID_PMEM
			str = t->u.cmdline.cmdline;
			str = strstr(str, "pmem=");
			if (str != NULL) {
				str += 5;
				android_pmem_gpu_data.size =
						memparse(str, &str);
				if (*str == ',') {
					str++;
					android_pmem_data.size =
						memparse(str, &str);
				}
			}
#endif
#ifdef CONFIG_ION
			str = t->u.cmdline.cmdline;
			str = strstr(str, "ion=");
			if (str != NULL) {
				str += 4;
				imx_ion_data.heaps[ION_GPU].size =
						memparse(str, &str);
				if (*str == ',') {
					str++;
					imx_ion_data.heaps[ION_VPU].size =
						memparse(str, &str);
				}
			}
#endif

			str = t->u.cmdline.cmdline;
			str = strstr(str, "fbmem=");
			if (str != NULL) {
				str += 6;
				smd_fb_data[i++].res_size[0] =
						memparse(str, &str);
				while (*str == ',' &&
					i < ARRAY_SIZE(smd_fb_data)) {
					str++;
					smd_fb_data[i++].res_size[0] =
						memparse(str, &str);
				}
			}

			str = t->u.cmdline.cmdline;
			str = strstr(str, "gpu_memory=");
			if (str != NULL) {
				str += 11;
				imx53_gpu_data.gmem_reserved_size =
						memparse(str, &str);
			}

			str = t->u.cmdline.cmdline;
			str = strstr(str, "fs_sdcard=");
			if (str != NULL) {
				str += 10;
				fs_in_sdcard = memparse(str, &str);
			}
			break;
		}
	}
}

static int __init mx53_bej_power_init(void)
{
	/* cpu get regulator needs to be in lateinit so that
	   regulator list gets updated for i2c da9052 regulators */
	mx5_cpu_regulator_init();

	pm_power_off = da9053_power_off;

	return 0;
}
late_initcall(mx53_bej_power_init);

#ifdef CONFIG_ANDROID_RAM_CONSOLE
static struct resource ram_console_resource = {
	.name = "android ram console",
	.flags = IORESOURCE_MEM,
};

static struct platform_device android_ram_console = {
	.name = "ram_console",
	.num_resources = 1,
	.resource = &ram_console_resource,
};

static int __init imx5x_add_ram_console(void)
{
	return platform_device_register(&android_ram_console);
}
#else
#define imx5x_add_ram_console() do {} while (0)
#endif

static void __init mx53_bej_io_init(void)
{
	mxc_iomux_v3_setup_multiple_pads(mx53_bej_pads,
					ARRAY_SIZE(mx53_bej_pads));

//--- GPIO1 ----//
/* MX53_BEJ_JTAG_DE_B		 GPIO1_2 */
	gpio_request(MX53_BEJ_JTAG_DE_B, "jtag_de");
	gpio_direction_output(MX53_BEJ_JTAG_DE_B, 0);

/* MX53_BEJ_SYS_UP_CPU		 GPIO1_4 */
	gpio_request(MX53_BEJ_SYS_UP_CPU, "sys_up_led");
	gpio_direction_output(MX53_BEJ_SYS_UP_CPU, 0);

/* MX53_BEJ_PMIC_FAULT		 GPIO1_5 */
	gpio_request(MX53_BEJ_PMIC_FAULT, "pmic_fault");
	gpio_direction_input(MX53_BEJ_PMIC_FAULT);

/* MX53_BEJ_SYS_ON_OFF_CTL	 GPIO1_7 */
	gpio_request(MX53_BEJ_SYS_ON_OFF_CTL, "sys_on_off_ctl");
	gpio_direction_output(MX53_BEJ_SYS_ON_OFF_CTL, 0);

/* MX53_BEJ_PMIC_ON_OFF_REQ	 GPIO1_8 */
	gpio_request(MX53_BEJ_PMIC_ON_OFF_REQ, "pmic_on_off");
	gpio_direction_input(MX53_BEJ_PMIC_ON_OFF_REQ);

/* MX53_BEJ_OPEN1		 GPIO1_22 */
	gpio_request(MX53_BEJ_OPEN1, "open1");
	gpio_direction_output(MX53_BEJ_OPEN1, 0);

/* MX53_BEJ_OPEN2		 GPIO1_23 */
	gpio_request(MX53_BEJ_OPEN2, "open2");
	gpio_direction_output(MX53_BEJ_OPEN2, 0);

/* MX53_BEJ_OPEN3		 GPIO1_24 */
	gpio_request(MX53_BEJ_OPEN3, "open3");
	gpio_direction_output(MX53_BEJ_OPEN3, 0);

/* MX53_BEJ_OPEN4		 GPIO1_25 */
	gpio_request(MX53_BEJ_OPEN4, "open4");
	gpio_direction_output(MX53_BEJ_OPEN4, 0);

/* MX53_BEJ_OPEN5		 GPIO1_26 */
	gpio_request(MX53_BEJ_OPEN5, "open5");
	gpio_direction_output(MX53_BEJ_OPEN5, 0);

/* MX53_BEJ_OPEN6		 GPIO1_27 */
	gpio_request(MX53_BEJ_OPEN6, "open6");
	gpio_direction_output(MX53_BEJ_OPEN6, 0);

/* MX53_BEJ_OPEN7		 GPIO1_28 */
	gpio_request(MX53_BEJ_OPEN7, "open7");
	gpio_direction_output(MX53_BEJ_OPEN7, 0);

/* MX53_BEJ_OPEN8		 GPIO1_29 */
	gpio_request(MX53_BEJ_OPEN8, "open8");
	gpio_direction_output(MX53_BEJ_OPEN8, 0);

/* MX53_BEJ_OPEN9		 GPIO1_30 */
	gpio_request(MX53_BEJ_OPEN9, "open9");
	gpio_direction_output(MX53_BEJ_OPEN9, 0);

/* MX53_BEJ_OPEN10		 GPIO1_31 */
	gpio_request(MX53_BEJ_OPEN10, "open10");
	gpio_direction_output(MX53_BEJ_OPEN10, 0);

//--- GPIO2 ----//
/* MX53_BEJ_OPEN11			GPIO_2_4 */
	gpio_request(MX53_BEJ_OPEN11, "open11");
	gpio_direction_output(MX53_BEJ_OPEN11, 0);

/* MX53_BEJ_HEADPHONE_DET	GPIO_2_5 */
	gpio_request(MX53_BEJ_HEADPHONE_DET, "head_det");
	gpio_direction_input(MX53_BEJ_HEADPHONE_DET);

/* MX53_BEJ_TP44			GPIO_2_6 */
	gpio_request(MX53_BEJ_TP44, "tp44");
	gpio_direction_output(MX53_BEJ_TP44, 0);

/* MX53_BEJ_OPEN12			GPIO_2_7 */
	gpio_request(MX53_BEJ_OPEN12, "open12");
	gpio_direction_output(MX53_BEJ_OPEN12, 0);

/* MX53_BEJ_NANDBOOT		GPIO_2_16 */
	gpio_request(MX53_BEJ_NANDBOOT, "nandboot");
	gpio_direction_output(MX53_BEJ_NANDBOOT, 0);

/* MX53_BEJ_OPEN13			GPIO_2_17 */
	gpio_request(MX53_BEJ_OPEN13, "open13");
	gpio_direction_output(MX53_BEJ_OPEN13, 0);

/* MX53_BEJ_OPEN14			GPIO_2_18 */
	gpio_request(MX53_BEJ_OPEN14, "open14");
	gpio_direction_output(MX53_BEJ_OPEN14, 0);

/* MX53_BEJ_OPEN15			GPIO_2_19 */
	gpio_request(MX53_BEJ_OPEN15, "open15");
	gpio_direction_output(MX53_BEJ_OPEN15, 0);

/* MX53_BEJ_OPEN16			GPIO_2_20 */
	gpio_request(MX53_BEJ_OPEN16, "open16");
	gpio_direction_output(MX53_BEJ_OPEN16, 0);

/* MX53_BEJ_OPEN17			GPIO_2_21 */
	gpio_request(MX53_BEJ_OPEN17, "open17");
	gpio_direction_output(MX53_BEJ_OPEN17, 0);

/* MX53_BEJ_OPEN18			GPIO_2_22 */
	gpio_request(MX53_BEJ_OPEN18, "open18");
	gpio_direction_output(MX53_BEJ_OPEN18, 0);

/* MX53_BEJ_TP22			GPIO_2_23 */
	gpio_request(MX53_BEJ_TP22, "tp22");
	gpio_direction_output(MX53_BEJ_TP22, 0);

/* MX53_BEJ_TP8				GPIO_2_24 */
	gpio_request(MX53_BEJ_TP8, "tp6");
	gpio_direction_output(MX53_BEJ_TP8, 0);

/* MX53_BEJ_TP3				GPIO_2_25 */
	gpio_request(MX53_BEJ_TP3, "tp3");
	gpio_direction_output(MX53_BEJ_TP3, 0);

/* MX53_BEJ_TP6				GPIO_2_26 */
	gpio_request(MX53_BEJ_TP6, "tp6");
	gpio_direction_output(MX53_BEJ_TP6, 0);

/* MX53_BEJ_OPEN19			GPIO_2_27 */
	gpio_request(MX53_BEJ_OPEN19, "open19");
	gpio_direction_output(MX53_BEJ_OPEN19, 0);

/* MX53_BEJ_OPEN20			GPIO_2_28 */
	gpio_request(MX53_BEJ_OPEN20, "open20");
	gpio_direction_output(MX53_BEJ_OPEN20, 0);

/* MX53_BEJ_OPEN21			GPIO_2_29 */
	gpio_request(MX53_BEJ_OPEN21, "open21");
	gpio_direction_output(MX53_BEJ_OPEN21, 0);

/* MX53_BEJ_OPEN22			GPIO_2_20 */
	gpio_request(MX53_BEJ_OPEN22, "open22");
	gpio_direction_output(MX53_BEJ_OPEN22, 0);

/* MX53_BEJ_TP7				GPIO_2_31 */
	gpio_request(MX53_BEJ_TP7, "tp7");
	gpio_direction_output(MX53_BEJ_TP7, 0);

//--- GPIO3 ----//
/* MX53_BEJ_OPEN23				GPIO_3_0 */
	gpio_request(MX53_BEJ_OPEN23, "open23");
	gpio_direction_output(MX53_BEJ_OPEN23, 0);

/* MX53_BEJ_OPEN24				GPIO_3_1 */
	gpio_request(MX53_BEJ_OPEN24, "open24");
	gpio_direction_output(MX53_BEJ_OPEN24, 0);

/* MX53_BEJ_OPEN25				GPIO_3_2 */
	gpio_request(MX53_BEJ_OPEN25, "open25");
	gpio_direction_output(MX53_BEJ_OPEN25, 0);

/* MX53_BEJ_OPEN26				GPIO_3_3 */
	gpio_request(MX53_BEJ_OPEN26, "open26");
	gpio_direction_output(MX53_BEJ_OPEN26, 0);

/* MX53_BEJ_OPEN27				GPIO_3_4 */
	gpio_request(MX53_BEJ_OPEN27, "open27");
	gpio_direction_output(MX53_BEJ_OPEN27, 0);

/* MX53_BEJ_OPEN28				GPIO_3_5 */
	gpio_request(MX53_BEJ_OPEN28, "open28");
	gpio_direction_output(MX53_BEJ_OPEN28, 0);

/* MX53_BEJ_OPEN29				GPIO_3_6 */
	gpio_request(MX53_BEJ_OPEN29, "open29");
	gpio_direction_output(MX53_BEJ_OPEN29, 0);

/* MX53_BEJ_OPEN30				GPIO_3_7 */
	gpio_request(MX53_BEJ_OPEN30, "open30");
	gpio_direction_output(MX53_BEJ_OPEN30, 0);

/* MX53_BEJ_OPEN31				GPIO_3_8 */
	gpio_request(MX53_BEJ_OPEN31, "open31");
	gpio_direction_output(MX53_BEJ_OPEN31, 0);

/* MX53_BEJ_OPEN32				GPIO_3_9 */
	gpio_request(MX53_BEJ_OPEN32, "open32");
	gpio_direction_output(MX53_BEJ_OPEN32, 0);

#ifdef EVABOARD
/* MX53_BEJ_RECOVERY_MODE_SW	GPIO_3_11 */
	gpio_request(MX53_BEJ_RECOVERY_MODE_SW, "recover_sw");
	gpio_direction_output(MX53_BEJ_RECOVERY_MODE_SW, 0);
#endif

/* MX53_BEJ_TP24				GPIO_3_12 */
	gpio_request(MX53_BEJ_TP24, "tp24");
	gpio_direction_output(MX53_BEJ_TP24, 0);

/* MX53_BEJ_SD1_CD				GPIO_3_13 */
	gpio_request(MX53_BEJ_SD1_CD, "sd1_cd");
	gpio_direction_input(MX53_BEJ_SD1_CD);

/* MX53_BEJ_TP25				GPIO_3_14 */
	gpio_request(MX53_BEJ_TP25, "tp25");
	gpio_direction_output(MX53_BEJ_TP25, 0);

/* MX53_BEJ_OPEN33				GPIO_3_15 */
	gpio_request(MX53_BEJ_OPEN33, "open33");
	gpio_direction_output(MX53_BEJ_OPEN33, 0);

/* MX53_BEJ_OPEN34				GPIO_3_16 */
	gpio_request(MX53_BEJ_OPEN34, "open34");
	gpio_direction_output(MX53_BEJ_OPEN34, 0);

/* MX53_BEJ_OPEN35				GPIO_3_17 */
	gpio_request(MX53_BEJ_OPEN35, "open35");
	gpio_direction_output(MX53_BEJ_OPEN35, 0);

/* MX53_BEJ_OPEN36				GPIO_3_18 */
	gpio_request(MX53_BEJ_OPEN36, "open36");
	gpio_direction_output(MX53_BEJ_OPEN36, 0);

/* MX53_BEJ_TP10				GPIO_3_19 */
	gpio_request(MX53_BEJ_TP10, "tp10");
	gpio_direction_output(MX53_BEJ_TP10, 0);

/* MX53_BEJ_TP11				GPIO_3_21 */
	gpio_request(MX53_BEJ_TP11, "tp11");
	gpio_direction_output(MX53_BEJ_TP11, 0);

/* MX53_BEJ_OPEN37				GPIO_3_22 */
	gpio_request(MX53_BEJ_OPEN37, "open37");
	gpio_direction_output(MX53_BEJ_OPEN37, 0);

/* MX53_BEJ_OPEN38				GPIO_3_23 */
	gpio_request(MX53_BEJ_OPEN38, "open38");
	gpio_direction_output(MX53_BEJ_OPEN38, 0);

/* MX53_BEJ_TP12				GPIO_3_24 */
	gpio_request(MX53_BEJ_TP12, "tp12");
//	gpio_direction_output(MX53_BEJ_TP12, 0);
	gpio_direction_input(MX53_BEJ_TP12);

/* MX53_BEJ_TP13				GPIO_3_25 */
	gpio_request(MX53_BEJ_TP13, "tp13");
	gpio_direction_output(MX53_BEJ_TP13, 0);

/* MX53_BEJ_TP14				GPIO_3_26 */
	gpio_request(MX53_BEJ_TP14, "tp14");
	gpio_direction_output(MX53_BEJ_TP14, 0);

/* MX53_BEJ_OPEN39				GPIO_3_27 */
	gpio_request(MX53_BEJ_OPEN39, "open39");
	gpio_direction_output(MX53_BEJ_OPEN39, 0);

/* MX53_BEJ_TP113				GPIO_3_28 */
	gpio_request(MX53_BEJ_TP113, "tp113");
	gpio_direction_output(MX53_BEJ_TP113, 0);

/* MX53_BEJ_OPEN40				GPIO_3_29 */
	gpio_request(MX53_BEJ_OPEN40, "open40");
	gpio_direction_output(MX53_BEJ_OPEN40, 0);

/* MX53_BEJ_CHRG_OR_CMOS		GPIO_3_30 */
	gpio_request(MX53_BEJ_CHRG_OR_CMOS, "chrg_cmos");
	gpio_direction_output(MX53_BEJ_CHRG_OR_CMOS, 0);

/* MX53_BEJ_OPEN41				GPIO_3_31 */
	gpio_request(MX53_BEJ_OPEN41, "open41");
	gpio_direction_output(MX53_BEJ_OPEN41, 0);

/* MX53_BEJ_OPEN43			GPIO_4_1 */
	gpio_request(MX53_BEJ_OPEN43, "open43");
	gpio_direction_output(MX53_BEJ_OPEN43, 0);

/* MX53_BEJ_OPEN44			GPIO_4_2 */
	gpio_request(MX53_BEJ_OPEN44, "open44");
	gpio_direction_output(MX53_BEJ_OPEN44, 0);

/* MX53_BEJ_OPEN45			GPIO_4_3 */
	gpio_request(MX53_BEJ_OPEN45, "open45");
	gpio_direction_output(MX53_BEJ_OPEN45, 0);

/* MX53_BEJ_OPEN46			GPIO_4_4 */
	gpio_request(MX53_BEJ_OPEN46, "open46");
	gpio_direction_output(MX53_BEJ_OPEN46, 0);

/* MX53_BEJ_TP26			GPIO_4_10 */
	gpio_request(MX53_BEJ_TP26, "tp26");
	gpio_direction_output(MX53_BEJ_TP26, 0);

/* MX53_BEJ_SD1_WP			GPIO_4_11 */
	gpio_request(MX53_BEJ_SD1_WP, "sd1_wp");
	gpio_direction_input(MX53_BEJ_SD1_WP);

/* MX53_BEJ_TP27			GPIO_4_14 */
	gpio_request(MX53_BEJ_TP27, "tp27");
	gpio_direction_output(MX53_BEJ_TP27, 0);

/* MX53_BEJ_OPEN48			GPIO_4_16 */
	gpio_request(MX53_BEJ_OPEN48, "open48");
	gpio_direction_output(MX53_BEJ_OPEN48, 0);

/* MX53_BEJ_OPEN49			GPIO_4_17 */
	gpio_request(MX53_BEJ_OPEN49, "open49");
	gpio_direction_output(MX53_BEJ_OPEN49, 0);

/* MX53_BEJ_OPEN50			GPIO_4_18 */
	gpio_request(MX53_BEJ_OPEN50, "open50");
	gpio_direction_output(MX53_BEJ_OPEN50, 0);

/* MX53_BEJ_OPEN51			GPIO_4_19 */
	gpio_request(MX53_BEJ_OPEN51, "open51");
	gpio_direction_output(MX53_BEJ_OPEN51, 0);

/* MX53_BEJ_OPEN52			GPIO_4_21 */
	gpio_request(MX53_BEJ_OPEN52, "open52");
	gpio_direction_output(MX53_BEJ_OPEN52, 0);

/* MX53_BEJ_OPEN53			GPIO_4_22 */
	gpio_request(MX53_BEJ_OPEN53, "open53");
	gpio_direction_output(MX53_BEJ_OPEN53, 0);

/* MX53_BEJ_OPEN54			GPIO_4_23 */
	gpio_request(MX53_BEJ_OPEN54, "open54");
	gpio_direction_output(MX53_BEJ_OPEN54, 0);

/* MX53_BEJ_OPEN55			GPIO_4_24 */
	gpio_request(MX53_BEJ_OPEN55, "open55");
	gpio_direction_output(MX53_BEJ_OPEN55, 0);

/* MX53_BEJ_OPEN56			GPIO_4_25 */
	gpio_request(MX53_BEJ_OPEN56, "open56");
	gpio_direction_output(MX53_BEJ_OPEN56, 0);

/* MX53_BEJ_OPEN57			GPIO_4_26 */
	gpio_request(MX53_BEJ_OPEN57, "open57");
	gpio_direction_output(MX53_BEJ_OPEN57, 0);

/* MX53_BEJ_OPEN58			GPIO_4_27 */
	gpio_request(MX53_BEJ_OPEN58, "open58");
	gpio_direction_output(MX53_BEJ_OPEN58, 0);

/* MX53_BEJ_OPEN59			GPIO_4_28 */
	gpio_request(MX53_BEJ_OPEN59, "open59");
	gpio_direction_output(MX53_BEJ_OPEN59, 0);

/* MX53_BEJ_OPEN60			GPIO_4_29 */
	gpio_request(MX53_BEJ_OPEN60, "open60");
	gpio_direction_output(MX53_BEJ_OPEN60, 0);

/* MX53_BEJ_OPEN61			GPIO_4_30 */
	gpio_request(MX53_BEJ_OPEN61, "open61");
	gpio_direction_output(MX53_BEJ_OPEN61, 0);

/* MX53_BEJ_OPEN62			GPIO_4_31 */
	gpio_request(MX53_BEJ_OPEN62, "open62");
	gpio_direction_output(MX53_BEJ_OPEN62, 0);

//--- GPIO5 ----//
/* MX53_BEJ_TP4				GPIO_5_0 */
	gpio_request(MX53_BEJ_TP4, "tp4");
	gpio_direction_output(MX53_BEJ_TP4, 0);

/* MX53_BEJ_AUD_AMP_STBY_B	GPIO_5_2 */
	gpio_request(MX53_BEJ_AUD_AMP_STBY_B, "amp_stby");
	gpio_direction_output(MX53_BEJ_AUD_AMP_STBY_B, 0);

/* MX53_BEJ_OPEN63			GPIO_5_4 */
	gpio_request(MX53_BEJ_OPEN63, "open63");
	gpio_direction_output(MX53_BEJ_OPEN63, 0);

/* MX53_BEJ_OPEN64			GPIO_5_5 */
	gpio_request(MX53_BEJ_OPEN64, "open64");
	gpio_direction_output(MX53_BEJ_OPEN64, 0);

/* MX53_BEJ_OPEN65			GPIO_5_6 */
	gpio_request(MX53_BEJ_OPEN65, "open65");
	gpio_direction_output(MX53_BEJ_OPEN65, 0);

/* MX53_BEJ_OPEN66			GPIO_5_7 */
	gpio_request(MX53_BEJ_OPEN66, "open66");
	gpio_direction_output(MX53_BEJ_OPEN66, 0);

/* MX53_BEJ_OPEN67			GPIO_5_8 */
	gpio_request(MX53_BEJ_OPEN67, "open67");
	gpio_direction_output(MX53_BEJ_OPEN67, 0);

/* MX53_BEJ_OPEN68			GPIO_5_9 */
	gpio_request(MX53_BEJ_OPEN68, "open68");
	gpio_direction_output(MX53_BEJ_OPEN68, 0);

/* MX53_BEJ_OPEN69			GPIO_5_10 */
	gpio_request(MX53_BEJ_OPEN69, "open69");
	gpio_direction_output(MX53_BEJ_OPEN69, 0);

/* MX53_BEJ_OPEN70			GPIO_5_11 */
	gpio_request(MX53_BEJ_OPEN70, "open70");
	gpio_direction_output(MX53_BEJ_OPEN70, 0);

/* MX53_BEJ_OPEN71			GPIO_5_12 */
	gpio_request(MX53_BEJ_OPEN71, "open71");
	gpio_direction_output(MX53_BEJ_OPEN71, 0);

/* MX53_BEJ_OPEN72			GPIO_5_13 */
	gpio_request(MX53_BEJ_OPEN72, "open72");
	gpio_direction_output(MX53_BEJ_OPEN72, 0);

/* MX53_BEJ_OPEN73			GPIO_5_14 */
	gpio_request(MX53_BEJ_OPEN73, "open73");
	gpio_direction_output(MX53_BEJ_OPEN73, 0);

/* MX53_BEJ_OPEN74			GPIO_5_15 */
	gpio_request(MX53_BEJ_OPEN74, "open74");
	gpio_direction_output(MX53_BEJ_OPEN74, 0);

/* MX53_BEJ_OPEN75			GPIO_5_16 */
	gpio_request(MX53_BEJ_OPEN75, "open75");
	gpio_direction_output(MX53_BEJ_OPEN75, 0);

/* MX53_BEJ_OPEN76			GPIO_5_17 */
	gpio_request(MX53_BEJ_OPEN76, "open76");
	gpio_direction_output(MX53_BEJ_OPEN76, 0);

/* MX53_BEJ_CSI0_PWN0		GPIO_5_20 */
	gpio_request(MX53_BEJ_CSI0_PWN0, "cis0_pwdn");
	gpio_direction_output(MX53_BEJ_CSI0_PWN0, 1);

/* MX53_BEJ_OSC_CKIH1_EN	GPIO_5_22 */
	gpio_request(MX53_BEJ_OSC_CKIH1_EN, "ckih_en");
	gpio_direction_output(MX53_BEJ_OSC_CKIH1_EN, 0);

/* MX53_BEJ_ACCL_INT1_IN	GPIO_5_23 */
	gpio_request(MX53_BEJ_ACCL_INT1_IN, "accl_int1");
	gpio_direction_input(MX53_BEJ_ACCL_INT1_IN);

/* MX53_BEJ_ACCL_INT2_IN	GPIO_5_24 */
	gpio_request(MX53_BEJ_ACCL_INT2_IN, "accl_int2");
	gpio_direction_input(MX53_BEJ_ACCL_INT2_IN);

/* MX53_BEJ_CSI0_RST0		GPIO_5_25 */
	gpio_request(MX53_BEJ_CSI0_RST0, "cis0_rst");
	gpio_direction_output(MX53_BEJ_CSI0_RST0, 1);


//--- GPIO6 ----//
/* MX53_BEJ_TP9				GPIO_6_6 */
	gpio_request(MX53_BEJ_TP9, "tp9");
	gpio_direction_output(MX53_BEJ_TP9, 0);

/* MX53_BEJ_OPEN77			GPIO_6_7 */
	gpio_request(MX53_BEJ_OPEN77, "open77");
	gpio_direction_output(MX53_BEJ_OPEN77, 0);

/* MX53_BEJ_OPEN78			GPIO_6_8 */
	gpio_request(MX53_BEJ_OPEN78, "open78");
	gpio_direction_output(MX53_BEJ_OPEN78, 0);

/* MX53_BEJ_OPEN79			GPIO_6_9 */
	gpio_request(MX53_BEJ_OPEN79, "open79");
	gpio_direction_output(MX53_BEJ_OPEN79, 0);

/* MX53_BEJ_OPEN80			GPIO_6_10 */
	gpio_request(MX53_BEJ_OPEN80, "open80");
	gpio_direction_output(MX53_BEJ_OPEN80, 0);

/* MX53_BEJ_OPEN81			GPIO_6_11 */
	gpio_request(MX53_BEJ_OPEN81, "open81");
	gpio_direction_output(MX53_BEJ_OPEN81, 0);

/* MX53_BEJ_OPEN82			GPIO_6_12 */
	gpio_request(MX53_BEJ_OPEN82, "open82");
	gpio_direction_output(MX53_BEJ_OPEN82, 0);

/* MX53_BEJ_OPEN83			GPIO_6_13 */
	gpio_request(MX53_BEJ_OPEN83, "open83");
	gpio_direction_output(MX53_BEJ_OPEN83, 0);

/* MX53_BEJ_LED1			GPIO_6_14 */
	gpio_request(MX53_BEJ_LED1, "led1");
	gpio_direction_output(MX53_BEJ_LED1, 0);

/* MX53_BEJ_LED2			GPIO_6_15 */
	gpio_request(MX53_BEJ_LED2, "led2");
	gpio_direction_output(MX53_BEJ_LED2, 0);

/* MX53_BEJ_LED3			GPIO_6_16 */
	gpio_request(MX53_BEJ_LED3, "led3");
	gpio_direction_output(MX53_BEJ_LED3, 0);

/* MX53_BEJ_TP39			GPIO_6_18 */
	gpio_request(MX53_BEJ_TP39, "tp39");
	gpio_direction_output(MX53_BEJ_TP39, 0);


//--- GPIO7 ----//
/* MX53_BEJ_TOUCH_RESETB		GPIO_7_0 */
	gpio_request(MX53_BEJ_TOUCH_RESETB, "touch_rst");
//--- Sanyo CE
	gpio_direction_output(MX53_BEJ_TOUCH_RESETB, 0);
	msleep(10);
	gpio_direction_output(MX53_BEJ_TOUCH_RESETB, 1);
//--- Sanyo CE

/* MX53_BEJ_OPEN84				GPIO_7_1 */
	gpio_request(MX53_BEJ_OPEN84, "open84");
	gpio_direction_output(MX53_BEJ_OPEN84, 0);

/* MX53_BEJ_TOUCH_INT			GPIO_7_2 */
	gpio_request(MX53_BEJ_TOUCH_INT, "touch_int");
	gpio_direction_input(MX53_BEJ_TOUCH_INT);

/* MX53_BEJ_OPEN85				GPIO_7_6 */
	gpio_request(MX53_BEJ_OPEN85, "open85");
	gpio_direction_output(MX53_BEJ_OPEN85, 0);

/* MX53_BEJ_CAME_EN				GPIO_7_8 */
	gpio_request(MX53_BEJ_CAME_EN, "came_en");
	gpio_direction_output(MX53_BEJ_CAME_EN, 0);

#ifdef EVABOARD
/* MX53_BEJ_DEVELOP_MODE_SW		GPIO_7_9 */
	gpio_request(MX53_BEJ_DEVELOP_MODE_SW, "dev_sw");
	gpio_direction_output(MX53_BEJ_DEVELOP_MODE_SW, 0);
#endif

/* MX53_BEJ_OPEN86				GPIO_7_10 */
	gpio_request(MX53_BEJ_OPEN86, "open86");
	gpio_direction_output(MX53_BEJ_OPEN86, 0);

/* MX53_BEJ_PMIC_INT			GPIO_7_11 */
	gpio_request(MX53_BEJ_PMIC_INT, "pmic_int");
	gpio_direction_input(MX53_BEJ_PMIC_INT);

	gpio_request(MX53_BEJ_BAT_ALART, "bat_alart");
	gpio_direction_input(MX53_BEJ_BAT_ALART);

/* MX53_BEJ_OPEN88				GPIO_7_13 */
	gpio_request(MX53_BEJ_OPEN88, "open88");
	gpio_direction_output(MX53_BEJ_OPEN88, 0);

/* MX53_BEJ_LCD_BL_EN */
	gpio_request(MX53_BEJ_LCD_BL_EN, "bl_en");
	gpio_direction_output(MX53_BEJ_LCD_BL_EN, 0);

	msleep(100);

/* MX53_BEJ_LCD_PWR_EN */
	/*LCD起動シーケンス*/
	gpio_request(MX53_BEJ_LCD_PWR_EN, "lcd-pwr-en");
#ifdef MFG
	gpio_direction_output(MX53_BEJ_LCD_PWR_EN, 0);
#else
	gpio_direction_output(MX53_BEJ_LCD_PWR_EN, 1);
#endif

//	gpio_request(MX53_BEJ_LCD_RESET, "lcd_reset");
//	gpio_direction_output(MX53_BEJ_LCD_RESET, 1);

/* MX53_BEJ_WATCHDOG_B */
	gpio_request(MX53_BEJ_WATCHDOG_B, "watchdog");
	gpio_direction_output(MX53_BEJ_WATCHDOG_B, 1);

/* MX53_BEJ_WATCHDOG_TEST */
	gpio_request(MX53_BEJ_WATCHDOG_TEST, "watchdog_test");
	gpio_direction_output(MX53_BEJ_WATCHDOG_TEST, 1);

/* MX53_BEJ_WLAN_RST		GPIO_4_15 */
	gpio_request(MX53_BEJ_WLAN_RST, "wlan_rst");
	gpio_direction_output(MX53_BEJ_WLAN_RST, 0);

/* MX53_BEJ_WIFI_32K_EN			GPIO_7_7 */
	gpio_request(MX53_BEJ_WIFI_32K_EN, "wifi_32k");
	gpio_direction_output(MX53_BEJ_WIFI_32K_EN, 1);

/* MX53_BEJ_WiFi_BT_PWR_EN		GPIO_3_10 */
	gpio_request(MX53_BEJ_WiFi_BT_PWR_EN, "wifi_pwr");
	gpio_direction_output(MX53_BEJ_WiFi_BT_PWR_EN, 0);

	msleep(100);

/* MX53_BEJ_WIFI_32K_EN			GPIO_7_7 */
	gpio_direction_output(MX53_BEJ_WIFI_32K_EN, 0);
	msleep(310);
	gpio_request(MX53_BEJ_WiFi_BT_PWR_EN, "wifi_pwr");
	gpio_direction_output(MX53_BEJ_WiFi_BT_PWR_EN, 1);
	msleep(10);
	gpio_request(MX53_BEJ_WLAN_RST, "wlan_rst");
	gpio_direction_output(MX53_BEJ_WLAN_RST, 1);

#ifdef EVABOARD
	/*HOME,BACK,MENU,VOL+-,SEARCH各キーは、キードライバで初期化される*/
#else
	gpio_request(MX53_BEJ_KEY_VOL_UP, "volume-up");
	gpio_direction_output(MX53_BEJ_KEY_VOL_UP, 0);
	gpio_request(MX53_BEJ_KEY_VOL_DOWN, "volume-down");
	gpio_direction_output(MX53_BEJ_KEY_VOL_DOWN, 0);
	gpio_request(MX53_BEJ_KEY_RETAN, "back");
	gpio_direction_output(MX53_BEJ_KEY_RETAN, 0);
	gpio_request(MX53_BEJ_KEY_HOME, "home");
	gpio_direction_output(MX53_BEJ_KEY_HOME, 0);
	gpio_request(MX53_BEJ_KEY_MENU, "menu");
	gpio_direction_output(MX53_BEJ_KEY_MENU, 0);
	gpio_request(MX53_BEJ_KEY_SEARCH, "search");
	gpio_direction_output(MX53_BEJ_KEY_SEARCH, 0);
#endif
}

static void __init mx53_bej_board_init(void)
{
	int i;

	mx53_bej_io_init();

	gp_reg_id = smd_regulator_data.cpu_reg_id;
	lp_reg_id = smd_regulator_data.vcc_reg_id;

	mx53_bej_init_uart();
	imx5x_add_ram_console();
	mxc_register_device(&mxc_pm_device, &smd_pm_data);
//	imx53_add_fec(&mx53_bej_fec_data);
	imx53_add_imx2_wdt(0, NULL);
	imx53_add_srtc();
	imx53_add_imx_i2c(0, &mx53_bej_i2c_data);
	imx53_add_imx_i2c(1, &mx53_bej_i2c_data);
	imx53_add_imx_i2c(2, &mx53_bej_i2c_data);
	imx53_add_ecspi(0, &mx53_bej_spi_data);

	imx53_add_ipuv3(0, &ipu_data);
	for (i = 0; i < ARRAY_SIZE(smd_fb_data); i++)
		imx53_add_ipuv3fb(i, &smd_fb_data[i]);
	imx53_add_lcdif(&lcdif_data);
	if (!mxc_fuse_get_vpu_status())
		imx53_add_vpu();
	imx53_add_ldb(&ldb_data);
	imx53_add_v4l2_output(0);
//	imx53_add_v4l2_capture(0, &capture_data);


	/*
	 * Disable HannStar touch panel CABC function,
	 * this function turns the panel's backlight automatically
	 * according to the content shown on the panel which
	 * may cause annoying unstable backlight issue.
	 */
//	gpio_request(MX53_BEJ_CABC_EN0, "cabc-en0");
//	gpio_direction_output(MX53_BEJ_CABC_EN0, 0);
//	gpio_request(MX53_BEJ_CABC_EN1, "cabc-en1");
//	gpio_direction_output(MX53_SMD_CABC_EN1, 0);

	imx53_add_mxc_pwm(1);
	imx53_add_mxc_pwm_backlight(0, &mxc_pwm_backlight_data);

	if (fs_in_sdcard == 1) {
		imx53_add_sdhci_esdhc_imx(0, &mx53_bej_sd1_data);
		imx53_add_sdhci_esdhc_imx(1, &mx53_bej_sd2_data);
		imx53_add_sdhci_esdhc_imx(2, &mx53_bej_sd3_data);
	} else {
		imx53_add_sdhci_esdhc_imx(2, &mx53_bej_sd3_data);
		imx53_add_sdhci_esdhc_imx(1, &mx53_bej_sd2_data);
		imx53_add_sdhci_esdhc_imx(0, &mx53_bej_sd1_data);
	}

//	imx53_add_ahci(0, &mx53_bej_sata_data);
	mxc_register_device(&imx_ahci_device_hwmon, NULL);
	mx53_bej_init_usb();
	imx_asrc_data.asrc_core_clk = clk_get(NULL, "asrc_clk");
	imx_asrc_data.asrc_audio_clk = clk_get(NULL, "asrc_serial_clk");
	imx53_add_asrc(&imx_asrc_data);

	imx53_add_iim(&iim_data);
	smd_add_device_buttons();

	mx53_bej_init_da9052();

//	spi_device_init();

	i2c_register_board_info(0, mxc_i2c0_board_info,
				ARRAY_SIZE(mxc_i2c0_board_info));
	i2c_register_board_info(1, mxc_i2c1_board_info,
				ARRAY_SIZE(mxc_i2c1_board_info));
	i2c_register_board_info(2, mxc_i2c2_board_info,
				ARRAY_SIZE(mxc_i2c2_board_info));

//	mxc_register_device(&imx_bt_rfkill, &imx_bt_rfkill_data);

	imx53_add_imx_ssi(1, &smd_ssi_pdata);

	mxc_register_device(&smd_audio_device, &smd_audio_data);

//	mxc_spdif_data.spdif_core_clk = clk_get(NULL, "spdif_xtal_clk");
//	clk_put(mxc_spdif_data.spdif_core_clk);
//	imx53_add_spdif(&mxc_spdif_data);
	imx53_add_spdif_dai();
	imx53_add_spdif_audio_device();

#ifdef CONFIG_ANDROID_PMEM
	mxc_register_device(&mxc_android_pmem_device, &android_pmem_data);
	mxc_register_device(&mxc_android_pmem_gpu_device,
				&android_pmem_gpu_data);
#endif
#ifdef CONFIG_ION
	imx53_add_ion(0, &imx_ion_data,
		sizeof(imx_ion_data) + (imx_ion_data.nr * sizeof(struct ion_platform_heap)));
#endif

	/*GPU*/
	if (mx53_revision() >= IMX_CHIP_REVISION_2_0)
		mx53_bej_gpu_pdata.z160_revision = 1;
	else
		mx53_bej_gpu_pdata.z160_revision = 0;

	if (!mxc_fuse_get_gpu_status())
		imx53_add_mxc_gpu(&mx53_bej_gpu_pdata);

	/* this call required to release SCC RAM partition held by ROM
	  * during boot, even if SCC2 driver is not part of the image
	  */
	imx53_add_mxc_scc2();
//	smd_add_device_battery();
	pm_i2c_init(MX53_I2C1_BASE_ADDR);

	imx53_add_dvfs_core(&smd_dvfs_core_data);
	imx53_add_busfreq();
}

unsigned get_lcd_power_port_bej2(void)
{
	return MX53_BEJ_LCD_PWR_EN;
}
unsigned get_lcd_bl_port_bej2(void)
{
	return MX53_BEJ_LCD_BL_EN;
}

//unsigned get_lcd_5v_port_bej2(void)
//unsigned get_lcd_reset_port_bej2(void)

unsigned get_csi0_rst_port_bej2(void)
{
	return MX53_BEJ_CSI0_RST0;
}

unsigned get_watchdog_port_bej2(void)
{
	return MX53_BEJ_WATCHDOG_B;
}

unsigned get_watchdog_test_port_bej2(void)
{
	return MX53_BEJ_WATCHDOG_TEST;
}

unsigned get_wifi_power_port_bej2(void)
{
	return MX53_BEJ_WiFi_BT_PWR_EN;
}

unsigned get_wifi_reset_port_bej2(void)
{
	return MX53_BEJ_WLAN_RST;
}

extern void da9053_set_ldo3_voltage(void);

int get_board_rev_bej2(void)
{
	int port;

	port = gpio_get_value(MX53_BEJ_TP12);

	if(port)
	{
		printk("board rev 0\n");
		return 0;
	}
	else
	{
		printk("board rev 1\n");
		return 1;
	}
}

static void __init mx53_bej_timer_init(void)
{
	struct clk *uart_clk;

	mx53_clocks_init(32768, 24000000, 22579200, 0);

	uart_clk = clk_get_sys("imx-uart.0", NULL);
	early_console_setup(MX53_UART1_BASE_ADDR, uart_clk);
}

static struct sys_timer mx53_bej_timer = {
	.init	= mx53_bej_timer_init,
};

#define SZ_TRIPLE_1080P	ALIGN((1920*ALIGN(1080, 128)*2*3), SZ_4K)
static void __init mx53_bej_reserve(void)
{
	phys_addr_t phys;
	int i;

#ifdef CONFIG_ANDROID_RAM_CONSOLE
	phys = memblock_alloc(SZ_1M, SZ_4K);
	memblock_remove(phys, SZ_1M);
	ram_console_resource.start = phys;
	ram_console_resource.end   = phys + SZ_1M - 1;
#endif

	if (imx53_gpu_data.gmem_reserved_size) {
		phys = memblock_alloc(imx53_gpu_data.gmem_reserved_size,
					   SZ_4K);
		memblock_remove(phys, imx53_gpu_data.gmem_reserved_size);
		imx53_gpu_data.gmem_reserved_base = phys;
	}
#ifdef CONFIG_ANDROID_PMEM
	if (android_pmem_data.size) {
		phys = memblock_alloc(android_pmem_data.size, SZ_4K);
		memblock_remove(phys, android_pmem_data.size);
		android_pmem_data.start = phys;
	}

	if (android_pmem_gpu_data.size) {
		phys = memblock_alloc(android_pmem_gpu_data.size, SZ_4K);
		memblock_remove(phys, android_pmem_gpu_data.size);
		android_pmem_gpu_data.start = phys;
	}
#endif
#ifdef CONFIG_ION
	if (imx_ion_data.heaps[ION_VPU].size) {
		phys = memblock_alloc(imx_ion_data.heaps[ION_VPU].size, SZ_4K);
		memblock_remove(phys, imx_ion_data.heaps[ION_VPU].size);
		imx_ion_data.heaps[ION_VPU].base = phys;
	}

	if (imx_ion_data.heaps[ION_GPU].size) {
		phys = memblock_alloc(imx_ion_data.heaps[ION_GPU].size, SZ_4K);
		memblock_remove(phys, imx_ion_data.heaps[ION_GPU].size);
		imx_ion_data.heaps[ION_GPU].base = phys;
	}
#endif

	for (i = 0; i < ARRAY_SIZE(smd_fb_data); i++)
		if (smd_fb_data[i].res_size[0]) {
			/* reserve for background buffer */
			phys = memblock_alloc(smd_fb_data[i].res_size[0],
						SZ_4K);
			memblock_remove(phys, smd_fb_data[i].res_size[0]);
			smd_fb_data[i].res_base[0] = phys;

			/* reserve for overlay buffer */
			phys = memblock_alloc(SZ_TRIPLE_1080P, SZ_4K);
			memblock_remove(phys, SZ_TRIPLE_1080P);
			smd_fb_data[i].res_base[1] = phys;
			smd_fb_data[i].res_size[1] = SZ_TRIPLE_1080P;
		}
}

/*
 * The following uses standard kernel macros define in arch.h in order to
 * initialize __mach_desc_MX53_SMD data structure.
 */
MACHINE_START(MX53_BEJ2, "Freescale iMX53 BEJ2 Board")
	/* Maintainer: Freescale Semiconductor, Inc. */
	.fixup = fixup_mxc_board,
	.map_io = mx53_map_io,
	.init_early = imx53_init_early,
	.init_irq = mx53_init_irq,
	.timer = &mx53_bej_timer,
	.init_machine = mx53_bej_board_init,
	.reserve = mx53_bej_reserve,
MACHINE_END
