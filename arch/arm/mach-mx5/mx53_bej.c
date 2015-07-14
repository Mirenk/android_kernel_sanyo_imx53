/*
 * Copyright (C) 2011 SanyoCE  All Rights Reserved.
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
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/pm.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/init.h>
#include <linux/input.h>
#include <linux/nodemask.h>
#include <linux/clk.h>
#include <linux/platform_device.h>
#include <linux/fsl_devices.h>
#include <linux/spi/spi.h>
#include <linux/i2c.h>
#include <linux/i2c/mpr.h>
#include <linux/ata.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/map.h>
#include <linux/mtd/partitions.h>
#include <linux/regulator/consumer.h>
#include <linux/android_pmem.h>
#include <linux/usb/android_composite.h>
#include <linux/usb/f_accessory.h>
#include <linux/pmic_external.h>
#include <linux/pmic_status.h>
#include <linux/ipu.h>
#include <linux/mxcfb.h>
#include <linux/pwm_backlight.h>
#include <linux/fec.h>
#include <linux/ahci_platform.h>
#include <linux/gpio_keys.h>
#include <linux/mfd/da9052/da9052.h>
#include <mach/common.h>
#include <mach/hardware.h>
#include <asm/irq.h>
#include <asm/setup.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/time.h>
#include <asm/mach/keypad.h>
#include <linux/spi/flash.h>
#include <mach/memory.h>
#include <mach/gpio.h>
#include <mach/mmc.h>
#include <mach/mxc_dvfs.h>
#include <mach/iomux-mx53.h>
#include <mach/i2c.h>
#include <mach/mxc_iim.h>
#include <mach/mxc_rfkill.h>
#include <mach/check_fuse.h>
#include <linux/powerkey.h>
//--- Sanyo CE Add
#include <linux/i2c/rohm_bu21023.h>
//--- Sanyo CE Add

#include "crm_regs.h"
#include "devices.h"
#include "usb.h"
#include "pmic.h"

/*評価ボードの場合はこのデファインを有効にしてビルドすること*/
//#define EVABOARD


/*!
 * @file mach-mx5/mx53_bej.c
 *
 * @brief This file contains MX53 bej board specific initialization routines.
 *
 * @ingroup MSL_MX53
 */

/* MX53 BEJ GPIO PIN configurations */
//--- GPIO1 ----//
#define MX53_BEJ_JTAG_DE_B			(0*32 + 2)	/* GPIO1_2 */
#define MX53_BEJ_SATA_CLK_GPEN		(0*32 + 4)	/* GPIO1_4 */
#define MX53_BEJ_PMIC_FAULT			(0*32 + 5)	/* GPIO1_5 */
#define MX53_BEJ_SYS_ON_OFF_CTL		(0*32 + 7)	/* GPIO1_7 */
#define MX53_BEJ_PMIC_ON_OFF_REQ	(0*32 + 8)	/* GPIO1_8 */
#define MX53_BEJ_WATCHDOG_B			(0*32 + 9)	/* GPIO1_9 */

#ifndef EVABOARD
#define MX53_BEJ_TP150			(0*32 + 22)	/* GPIO1_22 */
#define MX53_BEJ_TP158			(0*32 + 23)	/* GPIO1_23 */
#define MX53_BEJ_TP159			(0*32 + 24)	/* GPIO1_24 */
#define MX53_BEJ_TP157			(0*32 + 25)	/* GPIO1_25 */
#define MX53_BEJ_TP163			(0*32 + 26)	/* GPIO1_26 */
#define MX53_BEJ_TP162			(0*32 + 27)	/* GPIO1_27 */
#define MX53_BEJ_TP161			(0*32 + 28)	/* GPIO1_28 */
#define MX53_BEJ_TP167			(0*32 + 29)	/* GPIO1_29 */
#define MX53_BEJ_TP166			(0*32 + 30)	/* GPIO1_30 */
#define MX53_BEJ_TP137			(0*32 + 31)	/* GPIO1_31 */
#endif

//--- GPIO2 ----//
#define MX53_BEJ_FEC_INT			(1*32 + 4)	/* GPIO2_4 */
#define MX53_BEJ_HEADPHONE_DET		(1*32 + 5)	/* GPIO2_5 */
#define MX53_BEJ_LCD_RESET			(1*32 + 6)	/* GPIO2_6 */
#define MX53_BEJ_eMMC_RESET			(1*32 + 7)	/* GPIO2_7 */
#define MX53_BEJ_KEY_HOME			(1*32 + 12)	/* GPIO2_12 */
#define MX53_BEJ_KEY_RETAN			(1*32 + 13)	/* GPIO2_13 */
#define MX53_BEJ_KEY_VOL_DOWN		(1*32 + 14)	/* GPIO2_14 */
#define MX53_BEJ_KEY_VOL_UP			(1*32 + 15)	/* GPIO2_15 */
#define MX53_BEJ_FEC_PWR_EN			(1*32 + 16)	/* GPIO_2_16 */
#define MX53_BEJ_LID_OPN_CLS_SW		(1*32 + 23)	/* GPIO_2_23 */
#define MX53_BEJ_MIS_INPUT			(1*32 + 24)	/* GPIO_2_24 */ 
#define MX53_BEJ_TP135				(1*32 + 25)	/* GPIO_2_25 */
#define MX53_BEJ_TP129				(1*32 + 26)	/* GPIO_2_26 */
#define MX53_BEJ_TP127				(1*32 + 31)	/* GPIO_2_31 */

//--- GPIO3 ----//
#define MX53_BEJ_WiFi_BT_PWR_EN		(2*32 + 10)	/* GPIO_3_10 */
#define MX53_BEJ_RECOVERY_MODE_SW	(2*32 + 11)	/* GPIO_3_11 */
#define MX53_BEJ_USB_OTG_OC			(2*32 + 12)	/* GPIO_3_12 */
#define MX53_BEJ_SD1_CD				(2*32 + 13)	/* GPIO_3_13 */
#define MX53_BEJ_USB_HUB_RESET_B	(2*32 + 14)	/* GPIO_3_14 */
#define MX53_BEJ_eCOMPASS_INT		(2*32 + 15)	/* GPIO_3_15 */
#define MX53_BEJ_TP116				(2*32 + 19)	/* GPIO_3_19 */
#define MX53_BEJ_LCD_PWR_EN			(2*32 + 20)	/* GPIO_3_20 */
#define MX53_BEJ_TP126				(2*32 + 21)	/* GPIO_3_21 */
#define MX53_BEJ_ALS_INT			(2*32 + 22)	/* GPIO_3_22 */
#define MX53_BEJ_CSPI1_RST			(2*32 + 23)	/* GPIO_3_23 */
#define MX53_BEJ_TP122				(2*32 + 24)	/* GPIO_3_24 */
#define MX53_BEJ_TP121				(2*32 + 25)	/* GPIO_3_25 */
#define MX53_BEJ_TP120				(2*32 + 26)	/* GPIO_3_26 */
#define MX53_BEJ_TP119				(2*32 + 27)	/* GPIO_3_27 */
#define MX53_BEJ_LCD_5V_ON			(2*32 + 28)	/* GPIO_3_28 */
#define MX53_BEJ_HSMIC_DET			(2*32 + 29)	/* GPIO_3_29 */
#define MX53_BEJ_CHRG_OR_CMOS		(2*32 + 30)	/* GPIO_3_30 */
#define MX53_BEJ_TP142				(2*32 + 31)	/* GPIO_3_31 */

//--- GPIO4 ----//
#define MX53_BEJ_REST_OUT_MX53		(3*32 + 0)	/* GPIO_4_0 */
#define MX53_BEJ_TP123				(3*32 + 1)	/* GPIO_4_1 */
#define MX53_BEJ_CHA_ISET			(3*32 + 2)	/* GPIO_4_2 */
#define MX53_BEJ_TP128				(3*32 + 3)	/* GPIO_4_3 */
#define MX53_BEJ_TP140				(3*32 + 4)	/* GPIO_4_4 */
#define MX53_BEJ_WATCHDOG_TEST		(3*32 + 5)	/* GPIO_4_5 */
#define MX53_BEJ_DCDC3V3_BB_EN_MX5	(3*32 + 10)	/* GPIO_4_10 */
#define MX53_BEJ_SD1_WP				(3*32 + 11)	/* GPIO_4_11 */
#define MX53_BEJ_DCDC5V_BB_EN		(3*32 + 14)	/* GPIO_4_14 */
#define MX53_BEJ_WLAN_RST			(3*32 + 15)	/* GPIO_4_15 */
#define MX53_BEJ_LCD_BL_EN			(3*32 + 20)	/* GPIO_4_20 */

//--- GPIO5 ----//
#define MX53_BEJ_TP134				(4*32 + 0)	/* GPIO_5_0 */
#define MX53_BEJ_AUD_AMP_STBY_B		(4*32 + 2)	/* GPIO_5_2 */
#define MX53_BEJ_TOUCH_INT			(4*32 + 4)	/* GPIO_5_4 */
#define MX53_BEJ_CSIO_PWN0			(4*32 + 20)	/* GPIO_5_20 */
#define MX53_BEJ_OSC_CKIH1_EN		(4*32 + 22)	/* GPIO_5_22 */
#define MX53_BEJ_ACCL_INT1_IN		(4*32 + 23)	/* GPIO_5_23 */
#define MX53_BEJ_ACCL_INT2_IN		(4*32 + 24)	/* GPIO_5_24 */
#define MX53_BEJ_CSI0_RST0			(4*32 + 25)	/* GPIO_5_25 */

//--- GPIO6 ----//
#define MX53_BEJ_TP125				(5*32 + 6)	/* GPIO_6_6 */
#define MX53_BEJ_TP118				(5*32 + 14)	/* GPIO_6_14 */
#define MX53_BEJ_TP146				(5*32 + 15)	/* GPIO_6_15 */
#define MX53_BEJ_TP147				(5*32 + 16)	/* GPIO_6_16 */
#define MX53_BEJ_AC_IN				(5*32 + 17)	/* GPIO_6_17 */
#define MX53_BEJ_PWR_GOOD			(5*32 + 18)	/* GPIO_6_18 */

//--- GPIO7 ----//
#define MX53_BEJ_TP138				(6*32 + 0)	/* GPIO_7_0 */
#define MX53_BEJ_NFL_WP				(6*32 + 1)	/* GPIO_7_1 */
#define MX53_BEJ_TP139				(6*32 + 2)	/* GPIO_7_2 */
#define MX53_BEJ_KEY_MENU			(6*32 + 3)	/* GPIO_7_3 */
#define MX53_BEJ_FEC_RST			(6*32 + 6)	/* GPIO_7_6 */
#define MX53_BEJ_USER_DEG_CHG_NONE	(6*32 + 7)	/* GPIO_7_7 */
#define MX53_BEJ_USB_OTG_PWR_EN		(6*32 + 8)	/* GPIO_7_8 */
#define MX53_BEJ_DEVELOP_MODE_SW	(6*32 + 9)	/* GPIO_7_9 */
#define MX53_BEJ_CABC_EN1			(6*32 + 10)	/* GPIO_7_10 */
#define MX53_BEJ_PMIC_INT			(6*32 + 11)	/* GPIO_7_11 */
#define MX53_BEJ_TP141				(6*32 + 12)	/* GPIO_7_12 */
#define MX53_BEJ_TOUCH_RESETB		(6*32 + 13)	/* GPIO_7_13 */

#define MX53_OFFSET					(0x20000000)
#define TZIC_WAKEUP0_OFFSET         (0x0E00)
#define TZIC_WAKEUP1_OFFSET         (0x0E04)
#define TZIC_WAKEUP2_OFFSET         (0x0E08)
#define TZIC_WAKEUP3_OFFSET         (0x0E0C)
#define GPIO7_0_11_IRQ_BIT			(0x1<<11)

extern int __init mx53_bej_init_da9052(void);
extern void pm_i2c_init(u32 base_addr);

//Reset状態から変更のないものも含めてほぼ全ピンを設定
static iomux_v3_cfg_t mx53_bej_pads[] = {
	/* EIM_OE TP135 */
	MX53_PAD_EIM_OE__GPIO2_25,
	/* EIM_WAIT TP134 */
	MX53_PAD_EIM_WAIT__GPIO5_0,
	/* EIM_BCLK */
	/* EIM_LBA */
	MX53_PAD_EIM_LBA__EMI_WEIM_LBA,
	/* EIM_RW TP129 */
	MX53_PAD_EIM_RW__GPIO2_26,
	/* EIM_EB0 */
	MX53_PAD_EIM_EB0__EMI_WEIM_EB_0,
	/* EIM_EB1 */
	MX53_PAD_EIM_EB1__EMI_WEIM_EB_1,
	/* EIM_EB2 CSPI1_CS0 */
	MX53_PAD_EIM_EB2__ECSPI1_SS0,
	/* EIM_EB3 TP127 */
	MX53_PAD_EIM_EB3__GPIO2_31,
#ifdef EVABOARD
	/* EIM_CS0 LID_OPN_CLS_SW */
	MX53_PAD_EIM_CS0__GPIO2_23,
	/* EIM_CS1 EIM_DA0 間違い*/
	MX53_PAD_EIM_CS1__GPIO2_24,
#else
	/* EIM_CS0 */
	/* EIM_CS1 */
#endif
	/* EIM_A16 */
	MX53_PAD_EIM_A16__EMI_WEIM_A_16,
	/* EIM_A17 */
	MX53_PAD_EIM_A17__EMI_WEIM_A_17,
	/* EIM_A18 */
	MX53_PAD_EIM_A18__EMI_WEIM_A_18,
	/* EIM_A19 */
	MX53_PAD_EIM_A19__EMI_WEIM_A_19,
	/* EIM_A20 */
	MX53_PAD_EIM_A20__EMI_WEIM_A_20,
	/* EIM_A21 */
	MX53_PAD_EIM_A21__EMI_WEIM_A_21,
	/* EIM_A22 FEC_PWR_EN */
	MX53_PAD_EIM_A22__GPIO2_16,
	/* EIM_A23 TP125 */
	MX53_PAD_EIM_A23__GPIO6_6,
	/* EIM_A24 TOUCH_INT */
	MX53_PAD_EIM_A24__GPIO5_4,
	/* EIM_A25 AUD_AMP_STBY_B */
	MX53_PAD_EIM_A25__GPIO5_2,

	/* EIM_D16 CSPI1_CLK */
	MX53_PAD_EIM_D16__ECSPI1_SCLK,
	/* EIM_D17 CSPI1_MISO */
	MX53_PAD_EIM_D17__ECSPI1_MISO,
	/* EIM_D18 CSPI1_MOSI */
	MX53_PAD_EIM_D18__ECSPI1_MOSI,
	/* EIM_D19 TP116 */
	MX53_PAD_EIM_D19__GPIO3_19,
	/* EIM_D20 LCD_PWR_EN */
	MX53_PAD_EIM_D20__GPIO3_20,
	/* EIM_D21 TP126 */
	MX53_PAD_EIM_D21__GPIO3_21,
	/* EIM_D22 ALS_INT */
	MX53_PAD_EIM_D22__GPIO3_22,
	/* EIM_D23 CSPI1_RST */
	MX53_PAD_EIM_D23__GPIO3_23,
	/* EIM_D24 TP122 */
	MX53_PAD_EIM_D24__GPIO3_24,
	/* EIM_D25 TP121 */
	MX53_PAD_EIM_D25__GPIO3_25,
	/* EIM_D26 TP120 */
	MX53_PAD_EIM_D26__GPIO3_26,
	/* EIM_D27 TP119 */
	MX53_PAD_EIM_D27__GPIO3_27,
	/* EIM_D28 LCD_5V_ON */
	MX53_PAD_EIM_D28__GPIO3_28,
	/* EIM_D29 HSMIC_DET */
	MX53_PAD_EIM_D29__GPIO3_29,
	/* EIM_D30 CHARGER_NOW_OR_CMOS_RUN */
	MX53_PAD_EIM_D30__GPIO3_30,
	/* EIM_D31 TP142 */
	MX53_PAD_EIM_D31__GPIO3_31,
	/* EIM_DA0 NFLD0 */
	MX53_PAD_EIM_DA0__EMI_NAND_WEIM_DA_0,
	/* EIM_DA1 NFLD1 */
	MX53_PAD_EIM_DA1__EMI_NAND_WEIM_DA_1,
	/* EIM_DA2 NFLD2 */
	MX53_PAD_EIM_DA2__EMI_NAND_WEIM_DA_2,
	/* EIM_DA3 NFLD3 */
	MX53_PAD_EIM_DA3__EMI_NAND_WEIM_DA_3,
	/* EIM_DA4 NFLD4 */
	MX53_PAD_EIM_DA4__EMI_NAND_WEIM_DA_4,
	/* EIM_DA5 NFLD5 */
	MX53_PAD_EIM_DA5__EMI_NAND_WEIM_DA_5,
	/* EIM_DA6 NFLD6 */
	MX53_PAD_EIM_DA6__EMI_NAND_WEIM_DA_6,
	/* EIM_DA7 NFLD7 */
	MX53_PAD_EIM_DA7__EMI_NAND_WEIM_DA_7,
	/* EIM_DA8 NFLD8 */
	MX53_PAD_EIM_DA8__EMI_NAND_WEIM_DA_8,
	/* EIM_DA9 NFLD9 */
	MX53_PAD_EIM_DA9__EMI_NAND_WEIM_DA_9,
	/* EIM_DA10 WiFi_BT_PWR_EN */
	MX53_PAD_EIM_DA10__GPIO3_10,
	/* EIM_DA11 RECOVERY_MODE_SW */
	MX53_PAD_EIM_DA11__GPIO3_11,
	/* EIM_DA12 USB_OTG_OC */
	MX53_PAD_EIM_DA12__GPIO3_12,
	/* EIM_DA13 SD1_CD */
	MX53_PAD_EIM_DA13__GPIO3_13,
	/* EIM_DA14 USB_HUB_RESET_B */
	MX53_PAD_EIM_DA14__GPIO3_14,
	/* EIM_DA15 eCOMPASS_INT */
	MX53_PAD_EIM_DA15__GPIO3_15,
	/* NANDF_WE_B NFLWR */
	MX53_PAD_NANDF_WE_B__EMI_NANDF_WE_B,
	/* NANDF_RE_B NFLRD */
	MX53_PAD_NANDF_RE_B__EMI_NANDF_RE_B,
	/* NANDF_ALE */
	MX53_PAD_NANDF_ALE__EMI_NANDF_ALE,
	/* NANDF_CLE */
	MX53_PAD_NANDF_CLE__EMI_NANDF_CLE,
	/* NANDF_WP_B NFLREADY */
	MX53_PAD_NANDF_WP_B__EMI_NANDF_WP_B,
	/* NANDF_RB0 NANDF_RB */
	MX53_PAD_NANDF_RB0__EMI_NANDF_RB_0,
	/* NANDF_CS0 NFLCS0 */
	MX53_PAD_NANDF_CS0__EMI_NANDF_CS_0,
	/* NANDF_CS1 TP118 */
	MX53_PAD_NANDF_CS1__GPIO6_14,
	/* NANDF_CS2 TP146 */
	MX53_PAD_NANDF_CS2__GPIO6_15,
	/* NANDF_CS3 TP147 */
	MX53_PAD_NANDF_CS3__GPIO6_16,

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
	/* CSI0_VSYNC */
	MX53_PAD_CSI0_VSYNC__IPU_CSI0_VSYNC,
	/* CSI0_PIXCLK */
	MX53_PAD_CSI0_PIXCLK__IPU_CSI0_PIXCLK,
	/* CSI0_MCLK CSI0_HSYNC */
	MX53_PAD_CSI0_MCLK__IPU_CSI0_HSYNC,
	/* CSI0_DATA_EN CSIO_PWN0 */
	MX53_PAD_CSI0_DATA_EN__GPIO5_20,

	/* DI0_PIN2 LCD_HSYNC */
	MX53_PAD_DI0_PIN2__IPU_DI0_PIN2,
	/* DI0_PIN3 LCD_VSYNC */
	MX53_PAD_DI0_PIN3__IPU_DI0_PIN3,
	/* DI0_PIN4 LCD_BL_EN */
	MX53_PAD_DI0_PIN4__GPIO4_20,
	/* DI0_PIN15 LCD_DE */
	MX53_PAD_DI0_PIN15__IPU_DI0_PIN15,

	/* LPD0 */
	MX53_PAD_DISP0_DAT0__IPU_DISP0_DAT_0,
	/* LPD1 */
	MX53_PAD_DISP0_DAT1__IPU_DISP0_DAT_1,
	/* LPD2 */
	MX53_PAD_DISP0_DAT2__IPU_DISP0_DAT_2,
	/* LPD3 */
	MX53_PAD_DISP0_DAT3__IPU_DISP0_DAT_3,
	/* LPD4 */
	MX53_PAD_DISP0_DAT4__IPU_DISP0_DAT_4,
	/* LPD5 */
	MX53_PAD_DISP0_DAT5__IPU_DISP0_DAT_5,
	/* LPD6 */
	MX53_PAD_DISP0_DAT6__IPU_DISP0_DAT_6,
	/* LPD7 */
	MX53_PAD_DISP0_DAT7__IPU_DISP0_DAT_7,
	/* LPD8 */
	MX53_PAD_DISP0_DAT8__IPU_DISP0_DAT_8,
	/* LPD9 */
	MX53_PAD_DISP0_DAT9__IPU_DISP0_DAT_9,
	/* LPD10 */
	MX53_PAD_DISP0_DAT10__IPU_DISP0_DAT_10,
	/* LPD11 */
	MX53_PAD_DISP0_DAT11__IPU_DISP0_DAT_11,
	/* LPD12 */
	MX53_PAD_DISP0_DAT12__IPU_DISP0_DAT_12,
	/* LPD13 */
	MX53_PAD_DISP0_DAT13__IPU_DISP0_DAT_13,
	/* LPD14 */
	MX53_PAD_DISP0_DAT14__IPU_DISP0_DAT_14,
	/* LPD15 */
	MX53_PAD_DISP0_DAT15__IPU_DISP0_DAT_15,
	/* LPD16 */
	MX53_PAD_DISP0_DAT16__IPU_DISP0_DAT_16,
	/* LPD17 */
	MX53_PAD_DISP0_DAT17__IPU_DISP0_DAT_17,
	/* LPD18 */
	MX53_PAD_DISP0_DAT18__IPU_DISP0_DAT_18,
	/* LPD19 */
	MX53_PAD_DISP0_DAT19__IPU_DISP0_DAT_19,
	/* LPD20 */
	MX53_PAD_DISP0_DAT20__IPU_DISP0_DAT_20,
	/* LPD21 */
	MX53_PAD_DISP0_DAT21__IPU_DISP0_DAT_21,
	/* LPD22 */
	MX53_PAD_DISP0_DAT22__IPU_DISP0_DAT_22,
	/* LPD23 */
	MX53_PAD_DISP0_DAT23__IPU_DISP0_DAT_23,
	/* DI0_DISP_CLK LCD_DOTCLK */
	MX53_PAD_DI0_DISP_CLK__IPU_DI0_DISP_CLK,

#ifdef EVABOARD
	/* FEC_MDC */
	MX53_PAD_FEC_MDC__FEC_MDC,
	/* FEC_MDIO */
	MX53_PAD_FEC_MDIO__FEC_MDIO,
	/* FEC_CRS_DV */
	MX53_PAD_FEC_CRS_DV__FEC_RX_DV,
	/* FEC_REF_CLK_CPU */
	MX53_PAD_FEC_REF_CLK__FEC_TX_CLK,
	/* FEC_RX_ER */
	MX53_PAD_FEC_RX_ER__FEC_RX_ER,
	/* FEC_TXEN */
	MX53_PAD_FEC_TX_EN__FEC_TX_EN,
	/* FEC_RXD0 */
	MX53_PAD_FEC_RXD0__FEC_RDATA_0,
	/* FEC_RXD1 */
	MX53_PAD_FEC_RXD1__FEC_RDATA_1,
	/* FEC_TXD0 */
	MX53_PAD_FEC_TXD0__FEC_TDATA_0,
	/* FEC_TXD1 */
	MX53_PAD_FEC_TXD1__FEC_TDATA_1,
#else
	/* FEC_MDC */
	MX53_PAD_FEC_MDC__GPIO1_31,
	/* FEC_MDIO */
	MX53_PAD_FEC_MDIO__GPIO1_22,
	/* FEC_CRS_DV */
	MX53_PAD_FEC_CRS_DV__GPIO1_25,
	/* FEC_REF_CLK_CPU */
	MX53_PAD_FEC_REF_CLK__GPIO1_23,
	/* FEC_RX_ER */
	MX53_PAD_FEC_RX_ER__GPIO1_24,
	/* FEC_TXEN */
	MX53_PAD_FEC_TX_EN__GPIO1_28,
	/* FEC_RXD0 */
	MX53_PAD_FEC_RXD0__GPIO1_27,
	/* FEC_RXD1 */
	MX53_PAD_FEC_RXD1__GPIO1_26,
	/* FEC_TXD0 */
	MX53_PAD_FEC_TXD0__GPIO1_30,
	/* FEC_TXD1 */
	MX53_PAD_FEC_TXD1__GPIO1_29,
#endif

	/* KEY_COL0 I2S_SCLK */
	MX53_PAD_KEY_COL0__AUDMUX_AUD5_TXC,
	/* KEY_ROW0 I2S_DOUT */
	MX53_PAD_KEY_ROW0__AUDMUX_AUD5_TXD,
	/* KEY_COL1 I2S_LRCLK */
	MX53_PAD_KEY_COL1__AUDMUX_AUD5_TXFS,
	/* KEY_ROW1 I2S_DIN */
	MX53_PAD_KEY_ROW1__AUDMUX_AUD5_RXD,
	/* KEY_COL2 DCDC3V3_BB_EN_MX53 */
	MX53_PAD_KEY_COL2__GPIO4_10,
	/* KEY_ROW2 SD1_WP */
	MX53_PAD_KEY_ROW2__GPIO4_11,
	/* KEY_COL3 I2C2_SCL */
	MX53_PAD_KEY_COL3__I2C2_SCL,
	/* KEY_ROW3 I2C2_SDA */
	MX53_PAD_KEY_ROW3__I2C2_SDA,
	/* KEY_COL4 DCDC5V5_BB_EN */
	MX53_PAD_KEY_COL4__GPIO4_14,
	/* KEY_ROW4 WLAN_RST */
	MX53_PAD_KEY_ROW4__GPIO4_15,
	/* SD1_CMD */
	MX53_PAD_SD1_CMD__ESDHC1_CMD,
	/* SD1_CLK */
	MX53_PAD_SD1_CLK__ESDHC1_CLK,
	/* SD1_DATA0 */
	MX53_PAD_SD1_DATA0__ESDHC1_DAT0,
	/* SD1_DATA1 */
	MX53_PAD_SD1_DATA1__ESDHC1_DAT1,
	/* SD1_DATA2 */
	MX53_PAD_SD1_DATA2__ESDHC1_DAT2,
	/* SD1_DATA3 */
	MX53_PAD_SD1_DATA3__ESDHC1_DAT3,
	/* SD2_CMD */
	MX53_PAD_SD2_CMD__ESDHC2_CMD,
	/* SD2_CLK */
	MX53_PAD_SD2_CLK__ESDHC2_CLK,
	/* SD2_DATA0 */
	MX53_PAD_SD2_DATA0__ESDHC2_DAT0,
	/* SD2_DATA1 */
	MX53_PAD_SD2_DATA1__ESDHC2_DAT1,
	/* SD2_DATA2 */
	MX53_PAD_SD2_DATA2__ESDHC2_DAT2,
	/* SD2_DATA3 */
	MX53_PAD_SD2_DATA3__ESDHC2_DAT3,

	/* PATA_BUFFER_EN NFL_#WP */
	MX53_PAD_PATA_BUFFER_EN__GPIO7_1,
	/* PATA_CS_0 DEVELOP_MODE_SW */
	MX53_PAD_PATA_CS_0__GPIO7_9,
	/* PATA_CS_1 CABC_EN1 */
	MX53_PAD_PATA_CS_1__GPIO7_10,
	/* PATA_DA_0 FEC_nRST */
	MX53_PAD_PATA_DA_0__GPIO7_6,
	/* PATA_DA_1 USER_DEBUG_OR_CHARGER_DONE */
	MX53_PAD_PATA_DA_1__GPIO7_7,
	/* PATA_DA_2 USB_OTG_PWR_EN */
	MX53_PAD_PATA_DA_2__GPIO7_8,
	/* PATA_DATA0 SD3_DATA4 */
	MX53_PAD_PATA_DATA0__ESDHC3_DAT4,
	/* PATA_DATA1 SD3_DATA5 */
	MX53_PAD_PATA_DATA1__ESDHC3_DAT5,
	/* PATA_DATA2 SD3_DATA6 */
	MX53_PAD_PATA_DATA2__ESDHC3_DAT6,
	/* PATA_DATA3 SD3_DATA7 */
	MX53_PAD_PATA_DATA3__ESDHC3_DAT7,
	/* PATA_DATA4 FEC_nINT */
	MX53_PAD_PATA_DATA4__GPIO2_4,
	/* PATA_DATA5 HEADPHONE_DET */
	MX53_PAD_PATA_DATA5__GPIO2_5,
	/* PATA_DATA6 LCD_RESET */
	MX53_PAD_PATA_DATA6__GPIO2_6,
	/* PATA_DATA7 eMMC_RESET */
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
	MX53_PAD_PATA_DATA12__GPIO2_12_BEJ,
	/* PATA_DATA13 KEY_RETAN */
	MX53_PAD_PATA_DATA13__GPIO2_13_BEJ,
	/* PATA_DATA14 KEY_VOL- */
	MX53_PAD_PATA_DATA14__GPIO2_14_BEJ,
	/* PATA_DATA15 KEY_VOL+ */
	MX53_PAD_PATA_DATA15__GPIO2_15_BEJ,
	/* PATA_DIOR KEY_MENU */
	MX53_PAD_PATA_DIOR__GPIO7_3_BEJ,
	/* PATA_DIOW AC_IN */
	MX53_PAD_PATA_DIOW__GPIO6_17,
	/* PATA_DMACK PWR_GOOD */
	MX53_PAD_PATA_DMACK__GPIO6_18,
	/* PATA_DMARQ TP138 */
	MX53_PAD_PATA_DMARQ__GPIO7_0,
	/* PATA_INTRQ TP139 */
	MX53_PAD_PATA_INTRQ__GPIO7_2,
	/* PATA_IORDY SD3_CLK */
	MX53_PAD_PATA_IORDY__ESDHC3_CLK,
	/* PATA_RESET_B SD3_CMD */
	MX53_PAD_PATA_RESET_B__ESDHC3_CMD,

	/* GPIO_0 (CLK0) */
//	MX53_PAD_GPIO_0__CCM_CLKO,
	MX53_PAD_GPIO_0__CCM_SSI_EXT1_CLK,
	/* GPIO_1 LED_PWM */
	MX53_PAD_GPIO_1__PWM2_PWMO,
	/* GPIO_2 JTAG_DE_B */
	MX53_PAD_GPIO_2__GPIO1_2,
	/* GPIO_3 I2C3_SCL */
	MX53_PAD_GPIO_3__I2C3_SCL,
	/* GPIO_4 SATA_CLK_GPEN */
	MX53_PAD_GPIO_4__GPIO1_4,
	/* GPIO_5 PMIC_FAULT */
	MX53_PAD_GPIO_5__GPIO1_5,
	/* GPIO_6 I2C3_SDA */
	MX53_PAD_GPIO_6__I2C3_SDA,
	/* GPIO_7 SYS_ON_OFF_CTL */
	MX53_PAD_GPIO_7__GPIO1_7,
	/* GPIO_8 PMIC_ON_OFF_REQ */
	MX53_PAD_GPIO_8__GPIO1_8,
#if 0
	/* GPIO_9 WDOG1_WDOG_B */
	MX53_PAD_GPIO_9__WDOG1_WDOG_B,
#else
	MX53_PAD_GPIO_9__GPIO1_9,
#endif
	/* GPIO_10 REST_OUT_MX53 */
	MX53_PAD_GPIO_10__GPIO4_0,
	/* GPIO_11 TP_123 */
	MX53_PAD_GPIO_11__GPIO4_1,
	/* GPIO_12 CHA_ISET */
	MX53_PAD_GPIO_12__GPIO4_2,
	/* GPIO_13 TP128 */
	MX53_PAD_GPIO_13__GPIO4_3,
	/* GPIO_14 TP140 */
	MX53_PAD_GPIO_14__GPIO4_4,
	/* GPIO_16 PMIC_INT */
	MX53_PAD_GPIO_16__GPIO7_11,
	/* GPIO_17 TP141 */
	MX53_PAD_GPIO_17__GPIO7_12,
	/* GPIO_18 TOUCH_RESETB */
	MX53_PAD_GPIO_18__GPIO7_13,
	/* GPIO_19 WATCHDOG_TEST */
	MX53_PAD_GPIO_19__GPIO4_5,
	/* LVDS0_TX3_P */
	MX53_PAD_LVDS0_TX3_P__LDB_LVDS0_TX3,
	/* LVDS0_CLK_P */
	MX53_PAD_LVDS0_CLK_P__LDB_LVDS0_CLK,
	/* LVDS0_TX2_P */
	MX53_PAD_LVDS0_TX2_P__LDB_LVDS0_TX2,
	/* LVDS0_TX1_P */
	MX53_PAD_LVDS0_TX1_P__LDB_LVDS0_TX1,
	/* LVDS0_TX0_P */
	MX53_PAD_LVDS0_TX0_P__LDB_LVDS0_TX0,
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
};

static void smd_da9053_irq_wakeup_only_fixup(void)
{
	void __iomem *tzic_base;
	tzic_base = ioremap(MX53_TZIC_BASE_ADDR, SZ_4K);
	if (NULL == tzic_base) {
		pr_err("fail to map MX53_TZIC_BASE_ADDR\n");
		return;
	}
	__raw_writel(0, tzic_base + TZIC_WAKEUP0_OFFSET);
	__raw_writel(0, tzic_base + TZIC_WAKEUP1_OFFSET);
	__raw_writel(0, tzic_base + TZIC_WAKEUP2_OFFSET);
	/* only enable irq wakeup for da9053 */
	__raw_writel(GPIO7_0_11_IRQ_BIT, tzic_base + TZIC_WAKEUP3_OFFSET);
	iounmap(tzic_base);
//	pr_info("only da9053 irq is wakeup-enabled\n");
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

static struct fb_videomode video_modes[] = {
	{
	 /* 800x480 @ 57 Hz , pixel clk @ 27MHz */
	 "CLAA-WVGA", 57, 800, 480, 37037, 40, 60, 10, 10, 20, 10,
	 FB_SYNC_CLK_LAT_FALL,
	 FB_VMODE_NONINTERLACED,
	 0,},
	{
	/* 800x480 @ 60 Hz , pixel clk @ 32MHz */
	"SEIKO-WVGA", 60, 800, 480, 29850, 89, 164, 23, 10, 10, 10,
	FB_SYNC_CLK_LAT_FALL,
	FB_VMODE_NONINTERLACED,
	0,},
	{
	/* 1600x1200 @ 60 Hz 162M pixel clk*/
	"UXGA", 60, 1600, 1200, 6172,
	304, 64,
	1, 46,
	192, 3,
	FB_SYNC_HOR_HIGH_ACT|FB_SYNC_VERT_HIGH_ACT,
	FB_VMODE_NONINTERLACED,
	0,},
};

static struct platform_pwm_backlight_data mxc_pwm_backlight_data = {
	.pwm_id = 1,
	.max_brightness = 100,
	.dft_brightness = 30,
	.pwm_period_ns = 50000,
};

extern void mx5_ipu_reset(void);
static struct mxc_ipu_config mxc_ipu_data = {
	.rev = 3,
	.reset = mx5_ipu_reset,
};

extern void mx5_vpu_reset(void);
static struct mxc_vpu_platform_data mxc_vpu_data = {
	.iram_enable = true,
	.iram_size = 0x14000,
	.reset = mx5_vpu_reset,
};

static struct fec_platform_data fec_data = {
	.phy = PHY_INTERFACE_MODE_RMII,
};


static struct mxc_spi_master mxcspi1_data = {
	.maxchipselect = 4,
	.spi_version = 23,
	.chipselect_active = NULL,
	.chipselect_inactive = NULL,
};

static struct mxc_dvfs_platform_data dvfs_core_data = {
	.reg_id = "DA9052_BUCK_CORE",
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

static struct mxc_bus_freq_platform_data bus_freq_data = {
	.gp_reg_id = "DA9052_BUCK_CORE",
	.lp_reg_id = "DA9052_BUCK_PRO",
};

static struct tve_platform_data tve_data = {
	.dac_reg = "DA9052_LDO7",
};

static struct ldb_platform_data ldb_data = {
	.ext_ref = 1,
	.boot_enable = MXC_LDBDI1,
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

static struct mxc_iim_data iim_data = {
	.bank_start = MXC_IIM_MX53_BANK_START_ADDR,
	.bank_end   = MXC_IIM_MX53_BANK_END_ADDR,
	.enable_fuse = mxc_iim_enable_fuse,
	.disable_fuse = mxc_iim_disable_fuse,
};

static struct resource mxcfb_resources[] = {
	{
	 .flags = IORESOURCE_MEM,
	 },
	{
	 .flags = IORESOURCE_MEM,
	 },
	{
	 .flags = IORESOURCE_MEM,
	 },
};

static struct mxc_fb_platform_data fb_data[] = {
	{
	 .interface_pix_fmt = IPU_PIX_FMT_RGB24,
	 .mode_str = "1024x768M-16@60",
	 .mode = video_modes,
	 .num_modes = ARRAY_SIZE(video_modes),
	 },
	{
//	 .interface_pix_fmt = IPU_PIX_FMT_RGB666,
	 .interface_pix_fmt = IPU_PIX_FMT_RGB24,
	 .mode_str = "XGA",
	 .mode = video_modes,
	 .num_modes = ARRAY_SIZE(video_modes),
	 },
};

#if 0
void mx53_bej_lcd_power_en(int on)
{
	if (!machine_is_mx53_bej())
		return;

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
	if (!machine_is_mx53_bej())
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
	if (!machine_is_mx53_bej())
		return;

	if(on)
	{
		gpio_set_value(MX53_BEJ_LCD_5V_ON, 1);
	}
	else
	{
		gpio_set_value(MX53_BEJ_LCD_5V_ON, 0);
	}
}
EXPORT_SYMBOL(mx53_bej_lcd_5v_ctl);

void mx53_bej_lcd_reset_ctl(int on)
{
	if (!machine_is_mx53_bej())
		return;

	if(on)
	{
		gpio_set_value(MX53_BEJ_LCD_RESET, 1);
	}
	else
	{
		gpio_set_value(MX53_BEJ_LCD_RESET, 0);
	}
}
EXPORT_SYMBOL(mx53_bej_lcd_reset_ctl);
#endif

extern int primary_di;
static int __init mxc_init_fb(void)
{
	if (!machine_is_mx53_bej())
		return 0;

	/*for smd board, set default display as LDB*/
	if (primary_di < 0)
		primary_di = 1;

	if (primary_di) {
		printk(KERN_INFO "DI1 is primary\n");
		/* DI1 -> DP-BG channel: */
		mxc_fb_devices[1].num_resources = 1;
		mxc_fb_devices[1].resource = &mxcfb_resources[0];
		mxc_register_device(&mxc_fb_devices[1], &fb_data[1]);

		/* DI0 -> DC channel: */
		mxc_register_device(&mxc_fb_devices[0], &fb_data[0]);
	} else {
		printk(KERN_INFO "DI0 is primary\n");

		/* DI0 -> DP-BG channel: */
		mxc_fb_devices[0].num_resources = ARRAY_SIZE(mxcfb_resources);
		mxc_fb_devices[0].resource = mxcfb_resources;
		mxc_register_device(&mxc_fb_devices[0], &fb_data[0]);

		/* DI1 -> DC channel: */
		mxc_register_device(&mxc_fb_devices[1], &fb_data[1]);
	}

	/*
	 * DI0/1 DP-FG channel:
	 */
	mxc_fb_devices[2].num_resources = 1;
	mxc_fb_devices[2].resource = &mxcfb_resources[2];
	mxc_register_device(&mxc_fb_devices[2], NULL);

	return 0;
}
device_initcall(mxc_init_fb);

static struct imxi2c_platform_data mxci2c_data = {
       .bitrate = 100000,
};

static struct mxc_camera_platform_data camera_data = {
	.analog_regulator = "DA9052_LDO7",
	.core_regulator = "DA9052_LDO9",
	.mclk = 24000000,
	.csi = 0,
};

static struct mxc_lightsensor_platform_data ls_data = {
	.rext = 700,	/* calibration: 499K->700K */
};

static struct i2c_board_info mxc_i2c0_board_info[] __initdata = {
	{
	.type = "mma8451",
	.addr = 0x1C,
	 },
#if 0
	{
	.type = "ov5642",
	.addr = 0x3C,
	.platform_data = (void *)&camera_data,
	 },
#endif
#if 1
	{
	.type = "rnss2e1",
	.addr = 0x30,
	.platform_data = (void *)&camera_data,
	 },
#endif
};

static struct i2c_board_info mxc_i2c1_board_info[] __initdata = {
	{
	 .type = "sgtl5000-i2c",
	 .addr = 0x0a,
	 },
	{
	.type = "mag3110",
	.addr = 0x0e,
	.irq = gpio_to_irq(MX53_BEJ_eCOMPASS_INT),
	},
};

#if defined(CONFIG_KEYBOARD_GPIO) || defined(CONFIG_KEYBOARD_GPIO_MODULE)
#define GPIO_BUTTON(gpio_num, ev_code, act_low, descr, wake)	\
{								\
	.gpio		= gpio_num,				\
	.type		= EV_KEY,				\
	.code		= ev_code,				\
	.active_low	= act_low,				\
	.desc		= "btn " descr,				\
	.wakeup		= wake,					\
}

static struct gpio_keys_button bej_buttons[] = {
	GPIO_BUTTON(MX53_BEJ_KEY_VOL_UP, KEY_VOLUMEUP, 1, "volume-up", 0),
	GPIO_BUTTON(MX53_BEJ_KEY_VOL_DOWN, KEY_VOLUMEDOWN, 1, "volume-down", 0),

	GPIO_BUTTON(MX53_BEJ_KEY_RETAN, KEY_BACK, 1, "back", 0),
	GPIO_BUTTON(MX53_BEJ_KEY_HOME, KEY_HOME, 1, "home", 0),
	GPIO_BUTTON(MX53_BEJ_KEY_MENU, KEY_MENU, 1, "menu", 0),
};

static struct gpio_keys_platform_data bej_button_data = {
	.buttons	= bej_buttons,
	.nbuttons	= ARRAY_SIZE(bej_buttons),
};

static struct platform_device bej_button_device = {
	.name		= "gpio-keys",
	.id		= -1,
	.num_resources  = 0,
	.dev		= {
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

static struct i2c_board_info mxc_i2c2_board_info[] __initdata = {
};

#if defined(CONFIG_MTD_MXC_M25P80) || defined(CONFIG_MTD_MXC_M25P80_MODULE)
static struct mtd_partition m25p32_partitions[] = {
	{
	.name = "bootloader",
	.offset = 0,
	.size = 0x00040000,
	},
	{
	.name = "kernel",
	.offset = MTDPART_OFS_APPEND,
	.size = MTDPART_SIZ_FULL,
	},
};

static struct flash_platform_data m25p32_spi_flash_data = {
	.name = "m25p32",
	.parts = m25p32_partitions,
	.nr_parts = ARRAY_SIZE(m25p32_partitions),
	.type = "m25p32",
};
#endif

static struct spi_board_info m25p32_spi1_board_info[] __initdata = {
#if defined(CONFIG_MTD_MXC_M25P80) || defined(CONFIG_MTD_MXC_M25P80_MODULE)
	{
		/* the modalias must be the same as spi device driver name */
		.modalias = "m25p32",           /* Name of spi_driver for this device */
		.max_speed_hz = 20000000,       /* max spi SCK clock speed in HZ */
		.bus_num = 1,                   /* Framework bus number */
		.chip_select = 1,               /* Framework chip select. */
		.platform_data = &m25p32_spi_flash_data,
	}
#endif
};

static void spi_device_init(void)
{
	spi_register_board_info(m25p32_spi1_board_info,
				ARRAY_SIZE(m25p32_spi1_board_info));
}

static void mx53_gpio_usbotg_driver_vbus(bool on)
{
	if (on)
		gpio_set_value(MX53_BEJ_USB_OTG_PWR_EN, 0);
	else
		gpio_set_value(MX53_BEJ_USB_OTG_PWR_EN, 1);
}

static int sdhc_write_protect(struct device *dev)
{
	int ret = 0;

	if (to_platform_device(dev)->id == 0)
		ret = gpio_get_value(MX53_BEJ_SD1_WP);

	return ret;
}

static unsigned int sdhc_get_card_det_status(struct device *dev)
{
	int ret = 0;

	if (to_platform_device(dev)->id == 0)
		ret = gpio_get_value(MX53_BEJ_SD1_CD);

	return ret;
}

static struct mxc_mmc_platform_data mmc1_data = {
	.ocr_mask = MMC_VDD_27_28 | MMC_VDD_28_29 | MMC_VDD_29_30
		| MMC_VDD_31_32,
	.caps = MMC_CAP_4_BIT_DATA,
	.min_clk = 400000,
	.max_clk = 50000000,
	.card_inserted_state = 0,
	.status = sdhc_get_card_det_status,
	.wp_status = sdhc_write_protect,
	.clock_mmc = "esdhc_clk",
	.power_mmc = NULL,
};

static struct mxc_mmc_platform_data mmc2_data = {
	.ocr_mask = MMC_VDD_27_28 | MMC_VDD_28_29 | MMC_VDD_29_30
		| MMC_VDD_31_32,
	.caps = MMC_CAP_4_BIT_DATA,
	.min_clk = 400000,
	.max_clk = 50000000,
	.card_inserted_state = 1,
	.clock_mmc = "esdhc_clk",
	.power_mmc = NULL,
};

static struct mxc_mmc_platform_data mmc3_data = {
	.ocr_mask = MMC_VDD_27_28 | MMC_VDD_28_29 | MMC_VDD_29_30
		| MMC_VDD_31_32,
	.caps = MMC_CAP_4_BIT_DATA | MMC_CAP_8_BIT_DATA | MMC_CAP_DATA_DDR,
	.min_clk = 400000,
	.max_clk = 50000000,
	.card_inserted_state = 1,
	.clock_mmc = "esdhc_clk",
};


static int mxc_sgtl5000_amp_enable(int enable)
{
	gpio_request(MX53_BEJ_AUD_AMP_STBY_B, "amp-standby");
	if (enable)
		gpio_direction_output(MX53_BEJ_AUD_AMP_STBY_B, 1);
	else
		gpio_direction_output(MX53_BEJ_AUD_AMP_STBY_B, 0);
	gpio_free(MX53_BEJ_AUD_AMP_STBY_B);

	return 0;
}

static int headphone_det_status(void)
{
	return (gpio_get_value(MX53_BEJ_HEADPHONE_DET) == 0);
}

static int mxc_sgtl5000_init(void);

static struct mxc_audio_platform_data sgtl5000_data = {
	.ssi_num = 1,
	.src_port = 2,
	.ext_port = 5,
	.hp_irq = gpio_to_irq(MX53_BEJ_HEADPHONE_DET),
	.hp_status = headphone_det_status,
	.amp_enable = mxc_sgtl5000_amp_enable,
	.init = mxc_sgtl5000_init,
	.ext_ram_rx = 1,
};

static int mxc_sgtl5000_init(void)
{
	sgtl5000_data.sysclk = 22579200;
	return 0;
}

static struct platform_device mxc_sgtl5000_device = {
	.name = "imx-3stack-sgtl5000",
};

static struct android_pmem_platform_data android_pmem_data = {
	.name = "pmem_adsp",
	.size = SZ_64M,
	.cached = 1,
};

static struct android_pmem_platform_data android_pmem_gpu_data = {
	.name = "pmem_gpu",
	.size = SZ_64M,
	.cached = 1,
};

static char *usb_functions_ums[] = {
	"usb_mass_storage",
};

static char *usb_functions_ums_adb[] = {
	"usb_mass_storage",
	"adb",
};

static char *usb_functions_rndis[] = {
	"rndis",
};

static char *usb_functions_rndis_adb[] = {
	"rndis",
	"adb",
};

static char *usb_functions_accessory[] = {
	"accessory",
};

static char *usb_functions_accessory_adb[] = {
	"accessory",
	"adb",
};

static char *usb_functions_all[] = {
	"usb_mass_storage",
	"adb",
	"rndis",
	"accessory",
};

static struct android_usb_product usb_products[] = {
	{
		.product_id	= 0x0c01,
		.num_functions	= ARRAY_SIZE(usb_functions_ums),
		.functions	= usb_functions_ums,
	},
	{
		.product_id	= 0x0c02,
		.num_functions	= ARRAY_SIZE(usb_functions_ums_adb),
		.functions	= usb_functions_ums_adb,
	},
	{
		.product_id	= 0x0c10,
		.num_functions	= ARRAY_SIZE(usb_functions_rndis),
		.functions	= usb_functions_rndis,
	},
	{
		.vendor_id	= USB_ACCESSORY_VENDOR_ID,
		.product_id	= USB_ACCESSORY_PRODUCT_ID,
		.num_functions	= ARRAY_SIZE(usb_functions_accessory),
		.functions	= usb_functions_accessory,
	},
	{
		.vendor_id	= USB_ACCESSORY_VENDOR_ID,
		.product_id	= USB_ACCESSORY_ADB_PRODUCT_ID,
		.num_functions	= ARRAY_SIZE(usb_functions_accessory_adb),
		.functions	= usb_functions_accessory_adb,
	},
};

static struct usb_mass_storage_platform_data mass_storage_data = {
	.nluns		= 3,
	.vendor		= "Freescale",
	.product	= "MX53 SMD Android",
	.release	= 0x0100,
};

static struct usb_ether_platform_data rndis_data = {
	.vendorID	= 0x15a2,
	.vendorDescr	= "Freescale",
};

static struct android_usb_platform_data android_usb_data = {
	.vendor_id      = 0x15a2,
	.product_id     = 0x0c01,
	.version        = 0x0100,
	.product_name   = "MX53 SMD Android",
	.manufacturer_name = "Freescale",
	.num_products = ARRAY_SIZE(usb_products),
	.products = usb_products,
	.num_functions = ARRAY_SIZE(usb_functions_all),
	.functions = usb_functions_all,
};

static struct mxc_asrc_platform_data mxc_asrc_data = {
	.channel_bits = 4,
	.clk_map_ver = 2,
};

static struct mxc_spdif_platform_data mxc_spdif_data = {
	.spdif_tx = 1,
	.spdif_rx = 0,
	.spdif_clk_44100 = 0,	/* Souce from CKIH1 for 44.1K */
	/* Source from CCM spdif_clk (24M) for 48k and 32k
	 * It's not accurate
	 */
	.spdif_clk_48000 = 1,
	.spdif_clkid = 0,
	.spdif_clk = NULL,	/* spdif bus clk */
};

static struct mxc_audio_platform_data spdif_audio_data = {
	.ext_ram_tx = 1,
};

static struct platform_device mxc_spdif_audio_device = {
	.name = "imx-spdif-audio-device",
};

#if defined(CONFIG_BATTERY_MAX17085) || defined(CONFIG_BATTERY_MAX17085_MODULE)
static struct resource smd_batt_resource[] = {
	{
	.flags = IORESOURCE_IO,
	.name = "pwr-good",
	.start = MX53_BEJ_PWR_GOOD,
	.end = MX53_BEJ_PWR_GOOD,
	},
	{
	.flags = IORESOURCE_IO,
	.name = "ac-in",
	.start = MX53_BEJ_AC_IN,
	.end = MX53_BEJ_AC_IN,
	},
	{
	.flags = IORESOURCE_IO,
	.name = "charge-now",
	.start = MX53_BEJ_CHRG_OR_CMOS,
	.end = MX53_BEJ_CHRG_OR_CMOS,
	},
	{
	.flags = IORESOURCE_IO,
	.name = "charge-done",
	.start = MX53_BEJ_USER_DEG_CHG_NONE,
	.end = MX53_BEJ_USER_DEG_CHG_NONE,
	},
};

static struct platform_device smd_battery_device = {
	.name           = "max17085_bat",
	.resource	= smd_batt_resource,
	.num_resources  = ARRAY_SIZE(smd_batt_resource),
};

static void __init smd_add_device_battery(void)
{
	platform_device_register(&smd_battery_device);
}
#else
static void __init smd_add_device_battery(void)
{
}
#endif

/*!
 * Board specific fixup function. It is called by \b setup_arch() in
 * setup.c file very early on during kernel starts. It allows the user to
 * statically fill in the proper values for the passed-in parameters. None of
 * the parameters is used currently.
 *
 * @param  desc         pointer to \b struct \b machine_desc
 * @param  tags         pointer to \b struct \b tag
 * @param  cmdline      pointer to the command line
 * @param  mi           pointer to \b struct \b meminfo
 */
static void __init fixup_mxc_board(struct machine_desc *desc, struct tag *tags,
				   char **cmdline, struct meminfo *mi)
{
	struct tag *t;
	struct tag *mem_tag = 0;
	int total_mem = SZ_1G;
	int left_mem = 0;
	int gpu_mem = SZ_128M;
	int fb_mem = SZ_32M;
	char *str;

	mxc_set_cpu_type(MXC_CPU_MX53);

	for_each_tag(mem_tag, tags) {
		if (mem_tag->hdr.tag == ATAG_MEM) {
			total_mem = mem_tag->u.mem.size;
			break;
		}
	}

	for_each_tag(t, tags) {
		if (t->hdr.tag == ATAG_CMDLINE) {
			str = t->u.cmdline.cmdline;
			str = strstr(str, "mem=");
			if (str != NULL) {
				str += 4;
				left_mem = memparse(str, &str);
			}

			str = t->u.cmdline.cmdline;
			str = strstr(str, "gpu_nommu");
			if (str != NULL)
				gpu_data.enable_mmu = 0;

			str = t->u.cmdline.cmdline;
			str = strstr(str, "gpu_memory=");
			if (str != NULL) {
				str += 11;
				gpu_mem = memparse(str, &str);
			}

			break;
		}
	}

	if (gpu_data.enable_mmu)
		gpu_mem = 0;

	if (left_mem == 0 || left_mem > total_mem)
		left_mem = total_mem - gpu_mem - fb_mem;

	if (mem_tag) {
		fb_mem = total_mem - left_mem - gpu_mem;
		if (fb_mem < 0) {
			gpu_mem = total_mem - left_mem;
			fb_mem = 0;
		}
		mem_tag->u.mem.size = left_mem;

		/*reserve memory for gpu*/
		if (!gpu_data.enable_mmu) {
			gpu_device.resource[5].start =
				mem_tag->u.mem.start + left_mem;
			gpu_device.resource[5].end =
				gpu_device.resource[5].start + gpu_mem - 1;
		}
#if defined(CONFIG_FB_MXC_SYNC_PANEL) || \
	defined(CONFIG_FB_MXC_SYNC_PANEL_MODULE)
		if (fb_mem) {
			mxcfb_resources[0].start =
				gpu_data.enable_mmu ?
				mem_tag->u.mem.start + left_mem :
				gpu_device.resource[5].end + 1;
			mxcfb_resources[0].end =
				mxcfb_resources[0].start + fb_mem - 1;
		} else {
			mxcfb_resources[0].start = 0;
			mxcfb_resources[0].end = 0;
		}
#endif
	}
}

static void __init mx53_bej_io_init(void)
{
	mxc_iomux_v3_setup_multiple_pads(mx53_bej_pads,
					ARRAY_SIZE(mx53_bej_pads));

	/* SD1 CD */
	gpio_request(MX53_BEJ_SD1_CD, "sd1-cd");
	gpio_direction_input(MX53_BEJ_SD1_CD);
	/* SD1 WP */
	gpio_request(MX53_BEJ_SD1_WP, "sd1-wp");
	gpio_direction_input(MX53_BEJ_SD1_WP);

	/* reset FEC PHY */
	gpio_request(MX53_BEJ_FEC_RST, "fec-rst");
	gpio_direction_output(MX53_BEJ_FEC_RST, 0);
#ifdef EVABOARD
	gpio_set_value(MX53_BEJ_FEC_RST, 0);
	msleep(1);
	gpio_set_value(MX53_BEJ_FEC_RST, 1);
#endif

	/*FEC ポートを汎用ピンに設定*/
#ifndef EVABOARD
	gpio_request(MX53_BEJ_TP150, "tp150");
	gpio_direction_output(MX53_BEJ_TP150, 0);
	gpio_request(MX53_BEJ_TP158, "tp158");
	gpio_direction_output(MX53_BEJ_TP158, 0);
	gpio_request(MX53_BEJ_TP159, "tp159");
	gpio_direction_output(MX53_BEJ_TP159, 0);
	gpio_request(MX53_BEJ_TP157, "tp157");
	gpio_direction_output(MX53_BEJ_TP157, 0);
	gpio_request(MX53_BEJ_TP163, "tp163");
	gpio_direction_output(MX53_BEJ_TP163, 0);
	gpio_request(MX53_BEJ_TP162, "tp162");
	gpio_direction_output(MX53_BEJ_TP162, 0);
	gpio_request(MX53_BEJ_TP161, "tp161");
	gpio_direction_output(MX53_BEJ_TP161, 0);
	gpio_request(MX53_BEJ_TP167, "tp167");
	gpio_direction_output(MX53_BEJ_TP167, 0);
	gpio_request(MX53_BEJ_TP166, "tp166");
	gpio_direction_output(MX53_BEJ_TP166, 0);
	gpio_request(MX53_BEJ_TP137, "tp137");
	gpio_direction_output(MX53_BEJ_TP137, 0);
#endif

	/* headphone_det_b */
	gpio_request(MX53_BEJ_HEADPHONE_DET, "headphone-det");
	gpio_direction_input(MX53_BEJ_HEADPHONE_DET);

	/* USB PWR enable */
	gpio_request(MX53_BEJ_USB_OTG_PWR_EN, "usb-pwr");
	gpio_direction_output(MX53_BEJ_USB_OTG_PWR_EN, 0);

	/* Enable OSC_CKIH1_EN for audio */
	gpio_request(MX53_BEJ_OSC_CKIH1_EN, "osc-en");
	gpio_direction_output(MX53_BEJ_OSC_CKIH1_EN, 1);
	gpio_set_value(MX53_BEJ_OSC_CKIH1_EN, 1);

	/* Enable WiFi/BT Power*/
	gpio_request(MX53_BEJ_WiFi_BT_PWR_EN, "bt-wifi-pwren");
	gpio_direction_output(MX53_BEJ_WiFi_BT_PWR_EN, 0);
	mdelay(10);
	gpio_direction_output(MX53_BEJ_WiFi_BT_PWR_EN, 1);

	/* WiFi Power up sequence */
	gpio_request(MX53_BEJ_WLAN_RST, "wifi-rst");
	gpio_direction_output(MX53_BEJ_WLAN_RST, 0);
	mdelay(10);
	gpio_set_value(MX53_BEJ_WLAN_RST, 1);

	/* battery */
	gpio_request(MX53_BEJ_AC_IN, "ac-in");
	gpio_direction_input(MX53_BEJ_AC_IN);
	gpio_request(MX53_BEJ_PWR_GOOD, "pwr-good");
	gpio_direction_input(MX53_BEJ_PWR_GOOD);
	gpio_request(MX53_BEJ_CHRG_OR_CMOS, "charger now");
	gpio_direction_output(MX53_BEJ_CHRG_OR_CMOS, 0);
	gpio_request(MX53_BEJ_USER_DEG_CHG_NONE, "charger done");
	gpio_direction_output(MX53_BEJ_USER_DEG_CHG_NONE, 0);

	gpio_request(MX53_BEJ_eMMC_RESET, "eMMC-rst");
	gpio_direction_output(MX53_BEJ_eMMC_RESET, 1);

/*未実装*/
	/* ambient light sensor */
	gpio_request(MX53_BEJ_ALS_INT, "als int");
#ifdef EVABOARD
	gpio_direction_input(MX53_BEJ_ALS_INT);
#else
	gpio_direction_output(MX53_BEJ_ALS_INT, 0);
#endif
	/* mag3110 magnetometer sensor */
	gpio_request(MX53_BEJ_eCOMPASS_INT, "ecompass int");
	gpio_direction_input(MX53_BEJ_eCOMPASS_INT);

	gpio_request(MX53_BEJ_TP135, "tp135");
	gpio_direction_output(MX53_BEJ_TP135, 0);

	gpio_request(MX53_BEJ_TP134, "tp134");
	gpio_direction_output(MX53_BEJ_TP134, 0);

	gpio_request(MX53_BEJ_TP129, "tp129");
	gpio_direction_output(MX53_BEJ_TP129, 0);

	gpio_request(MX53_BEJ_TP116, "tp116");
	gpio_direction_output(MX53_BEJ_TP116, 0);

	gpio_request(MX53_BEJ_TP122, "tp122");
	gpio_direction_output(MX53_BEJ_TP122, 0);

	gpio_request(MX53_BEJ_TP121, "tp121");
	gpio_direction_output(MX53_BEJ_TP121, 0);

	gpio_request(MX53_BEJ_TP127, "tp127");
	gpio_direction_output(MX53_BEJ_TP127, 0);

	gpio_request(MX53_BEJ_CSPI1_RST, "cispi1_rst");
	gpio_direction_output(MX53_BEJ_CSPI1_RST, 0);

#ifdef EVABOARD
	gpio_request(MX53_BEJ_LID_OPN_CLS_SW, "lid_open");
	gpio_direction_input(MX53_BEJ_LID_OPN_CLS_SW);
#endif

#ifdef EVABOARD
	gpio_request(MX53_BEJ_MIS_INPUT, "mistake");
	gpio_direction_input(MX53_BEJ_MIS_INPUT);
#endif

	gpio_request(MX53_BEJ_TP125, "tp125");
	gpio_direction_output(MX53_BEJ_TP125, 0);

	gpio_request(MX53_BEJ_TP126, "tp126");
	gpio_direction_output(MX53_BEJ_TP126, 0);

	gpio_request(MX53_BEJ_TP120, "tp120");
	gpio_direction_output(MX53_BEJ_TP120, 0);

	gpio_request(MX53_BEJ_TP119, "tp119");
	gpio_direction_output(MX53_BEJ_TP119, 0);

	gpio_request(MX53_BEJ_LCD_5V_ON, "lcd_5V_on");
	gpio_direction_output(MX53_BEJ_LCD_5V_ON, 0);

	gpio_request(MX53_BEJ_HSMIC_DET, "hsmic_det");
	gpio_direction_input(MX53_BEJ_HSMIC_DET);

	gpio_request(MX53_BEJ_TP142, "tp142");
	gpio_direction_output(MX53_BEJ_TP142, 0);

	gpio_request(MX53_BEJ_RECOVERY_MODE_SW, "recover_sw");
	gpio_direction_input(MX53_BEJ_RECOVERY_MODE_SW);

	gpio_request(MX53_BEJ_USB_OTG_OC, "otg_oc");
#ifdef EVABOARD
	gpio_direction_input(MX53_BEJ_USB_OTG_OC);
#else
	gpio_direction_output(MX53_BEJ_USB_OTG_OC, 0);
#endif

	gpio_request(MX53_BEJ_USB_HUB_RESET_B, "hub_reset");
	gpio_direction_output(MX53_BEJ_USB_HUB_RESET_B, 0);

	gpio_request(MX53_BEJ_TP118, "tp118");
	gpio_direction_output(MX53_BEJ_TP118, 0);

	gpio_request(MX53_BEJ_TP146, "tp146");
	gpio_direction_output(MX53_BEJ_TP146, 0);

	gpio_request(MX53_BEJ_TP147, "tp147");
	gpio_direction_output(MX53_BEJ_TP147, 0);

	gpio_request(MX53_BEJ_CSIO_PWN0, "csi0_pwn0");
	gpio_direction_output(MX53_BEJ_CSIO_PWN0, 0);

	gpio_request(MX53_BEJ_ACCL_INT1_IN, "accl_init1");
	gpio_direction_input(MX53_BEJ_ACCL_INT1_IN);

	gpio_request(MX53_BEJ_ACCL_INT2_IN, "accl_init2");
	gpio_direction_input(MX53_BEJ_ACCL_INT2_IN);

	gpio_request(MX53_BEJ_CSI0_RST0, "csi0_rst0");
	gpio_direction_output(MX53_BEJ_CSI0_RST0, 0);

	gpio_request(MX53_BEJ_TP138, "tp138");
	gpio_direction_output(MX53_BEJ_TP138, 0);

	gpio_request(MX53_BEJ_DEVELOP_MODE_SW, "develop_sw");
	gpio_direction_input(MX53_BEJ_DEVELOP_MODE_SW);

	gpio_request(MX53_BEJ_CABC_EN1, "cabc_en1");
	gpio_direction_output(MX53_BEJ_CABC_EN1, 0);

	gpio_request(MX53_BEJ_HEADPHONE_DET, "headphone_det");
	gpio_direction_input(MX53_BEJ_HEADPHONE_DET);

	gpio_request(MX53_BEJ_LCD_RESET, "lcd_reset");
	gpio_direction_output(MX53_BEJ_LCD_RESET, 0);

	gpio_request(MX53_BEJ_TP139, "tp139");
	gpio_direction_output(MX53_BEJ_TP139, 0);

	gpio_request(MX53_BEJ_JTAG_DE_B, "jtag_de");
	gpio_direction_output(MX53_BEJ_JTAG_DE_B, 0);

	gpio_request(MX53_BEJ_SATA_CLK_GPEN, "sata_clk");
	gpio_direction_output(MX53_BEJ_SATA_CLK_GPEN, 0);

	gpio_request(MX53_BEJ_TP123, "tp123");
	gpio_direction_output(MX53_BEJ_TP123, 0);

	gpio_request(MX53_BEJ_TP128, "tp128");
	gpio_direction_output(MX53_BEJ_TP128, 0);

	gpio_request(MX53_BEJ_TP140, "tp140");
	gpio_direction_output(MX53_BEJ_TP140, 0);

	gpio_request(MX53_BEJ_TP141, "tp141");
	gpio_direction_output(MX53_BEJ_TP141, 0);

	gpio_request(MX53_BEJ_TOUCH_INT, "rohm_int");
	gpio_direction_input(MX53_BEJ_TOUCH_INT);

	gpio_request(MX53_BEJ_TOUCH_RESETB, "rohm_reset");
	gpio_direction_output(MX53_BEJ_TOUCH_RESETB, 0);

#if 0 //GPIO_19と共有なので削除
	gpio_request(MX53_BEJ_DRV_BLU, "drv_blu");
	gpio_direction_output(MX53_BEJ_DRV_BLU, 0);
#endif

	gpio_request(MX53_BEJ_HSMIC_DET, "hsmic_det");
	gpio_direction_input(MX53_BEJ_HSMIC_DET);

	gpio_request(MX53_BEJ_CHA_ISET, "cha_iset");
	gpio_direction_output(MX53_BEJ_CHA_ISET, 0);

	gpio_request(MX53_BEJ_SATA_CLK_GPEN, "sata_clk_en");
	gpio_direction_output(MX53_BEJ_SATA_CLK_GPEN, 0);

	gpio_request(MX53_BEJ_REST_OUT_MX53, "reset_out");/*未使用*/
	gpio_direction_output(MX53_BEJ_REST_OUT_MX53, 0);

	gpio_request(MX53_BEJ_PMIC_FAULT, "pmic_fault");
	gpio_direction_input(MX53_BEJ_PMIC_FAULT);

	gpio_request(MX53_BEJ_LCD_BL_EN, "bl_en");
	gpio_direction_output(MX53_BEJ_LCD_BL_EN, 0);

	/*LCD起動シーケンス*/
	gpio_request(MX53_BEJ_LCD_PWR_EN, "lcd-pwr-en");
	gpio_direction_output(MX53_BEJ_LCD_PWR_EN, 1);
//	msleep(1);
	gpio_request(MX53_BEJ_LCD_RESET, "lcd_reset");
	gpio_direction_output(MX53_BEJ_LCD_RESET, 1);

	gpio_request(MX53_BEJ_WATCHDOG_B, "watchdog");
	gpio_direction_output(MX53_BEJ_WATCHDOG_B, 1);

	gpio_request(MX53_BEJ_WATCHDOG_TEST, "watchdog_test");
	gpio_direction_output(MX53_BEJ_WATCHDOG_TEST, 1);

	/*HOME,BACK,MENU,VOL+-各キーは、キードライバで初期化される*/
}

#if 0
void mx53_bej_csi0_rst(int value)
{
	if (!machine_is_mx53_bej())
		return;
	if(value)
	{
		gpio_set_value(MX53_BEJ_CSI0_RST0, 1);
	}
	else
	{
		gpio_set_value(MX53_BEJ_CSI0_RST0, 0);
	}
}
EXPORT_SYMBOL(mx53_bej_csi0_rst);

void mx53_bej_watchdog_en(int on)
{
	if (!machine_is_mx53_bej())
		return;
	if(on)
	{
		gpio_set_value(MX53_BEJ_WATCHDOG_B, 1);
		gpio_set_value(MX53_BEJ_WATCHDOG_TEST, 1);
	}
	else
	{
		gpio_set_value(MX53_BEJ_WATCHDOG_B, 0);
		gpio_set_value(MX53_BEJ_WATCHDOG_TEST, 0);
	}
}
EXPORT_SYMBOL(mx53_bej_watchdog_en);

void mx53_bej_wifi_power_en(int on)
{
	if (!machine_is_mx53_bej())
		return;

	if(on)
	{
		gpio_set_value(MX53_BEJ_WiFi_BT_PWR_EN, 1);
	}
	else
	{
		gpio_set_value(MX53_BEJ_WiFi_BT_PWR_EN, 0);
	}
}
EXPORT_SYMBOL(mx53_bej_wifi_power_en);

void mx53_bej_wifi_reset_en(int on)
{
	if (!machine_is_mx53_bej())
		return;

	if(on)
	{
		gpio_set_value(MX53_BEJ_WLAN_RST, 1);
	}
	else
	{
		gpio_set_value(MX53_BEJ_WLAN_RST, 0);
	}
}
EXPORT_SYMBOL(mx53_bej_wifi_reset_en);
#endif

unsigned get_lcd_power_port_bej(void)
{
	return MX53_BEJ_LCD_PWR_EN;
}
unsigned get_lcd_bl_port_bej(void)
{
	return MX53_BEJ_LCD_BL_EN;
}

unsigned get_lcd_5v_port_bej(void)
{
	return MX53_BEJ_LCD_5V_ON;
}

unsigned get_lcd_reset_port_bej(void)
{
	return MX53_BEJ_LCD_RESET;
}

unsigned get_csi0_rst_port_bej(void)
{
	return MX53_BEJ_CSI0_RST0;
}

unsigned get_watchdog_port_bej(void)
{
	return MX53_BEJ_WATCHDOG_B;
}

unsigned get_watchdog_test_port_bej(void)
{
	return MX53_BEJ_WATCHDOG_TEST;
}

unsigned get_wifi_power_port_bej(void)
{
	return MX53_BEJ_WiFi_BT_PWR_EN;
}

unsigned get_wifi_reset_port_bej(void)
{
	return MX53_BEJ_WLAN_RST;
}

extern void da9053_set_ldo3_voltage(void);

/*!
 * Board specific initialization.
 */
static void __init mxc_board_init(void)
{
	mxc_ipu_data.di_clk[0] = clk_get(NULL, "ipu_di0_clk");
	mxc_ipu_data.di_clk[1] = clk_get(NULL, "ipu_di1_clk");
	mxc_ipu_data.csi_clk[0] = clk_get(NULL, "ssi_ext1_clk");
	/*
	 *ssi_ext1_clk was enbled in arch/arm/mach-mx5/clock.c, and it was kept
	 *open to provide clock for audio codec on i.Mx53 Quickstart, but MX53
	 *BEJ board have no needs to do that, so we close it here
	 */
	clk_disable(mxc_ipu_data.csi_clk[0]);
	mxc_spdif_data.spdif_core_clk = clk_get(NULL, "spdif_xtal_clk");
	clk_put(mxc_spdif_data.spdif_core_clk);

	mxcsdhc1_device.resource[2].start = gpio_to_irq(MX53_BEJ_SD1_CD);
	mxcsdhc1_device.resource[2].end = gpio_to_irq(MX53_BEJ_SD1_CD);

	mxc_cpu_common_init();
	mx53_bej_io_init();

	/* power off by sending shutdown command to da9053*/
	pm_power_off = da9053_power_off;
	mxc_register_device(&mxc_dma_device, NULL);
	mxc_register_device(&mxc_wdt_device, NULL);
	mxc_register_device(&mxcspi1_device, &mxcspi1_data);
	mxc_register_device(&mxci2c_devices[0], &mxci2c_data);
	mxc_register_device(&mxci2c_devices[1], &mxci2c_data);
	mxc_register_device(&mxci2c_devices[2], &mxci2c_data);
	mx53_bej_init_da9052();

	mxc_register_device(&mxc_rtc_device, NULL);
	mxc_register_device(&mxc_ipu_device, &mxc_ipu_data);
	mxc_register_device(&mxc_ldb_device, &ldb_data);
	mxc_register_device(&mxc_tve_device, &tve_data);
	if (!mxc_fuse_get_vpu_status())
		mxc_register_device(&mxcvpu_device, &mxc_vpu_data);
	if (!mxc_fuse_get_gpu_status())
		mxc_register_device(&gpu_device, &gpu_data);
	mxc_register_device(&mxcscc_device, NULL);
	mxc_register_device(&pm_device, &smd_pm_data);
	mxc_register_device(&mxc_dvfs_core_device, &dvfs_core_data);
	mxc_register_device(&busfreq_device, &bus_freq_data);
	mxc_register_device(&mxc_iim_device, &iim_data);
	mxc_register_device(&mxc_pwm2_device, NULL);
	mxc_register_device(&mxc_pwm1_backlight_device, &mxc_pwm_backlight_data);
	/* Register mmc3(eMMC) first, make it's device number be 0 to
	 * avoid device number change by hotplug in SD(mmc1) card */
	mxc_register_device(&mxcsdhc3_device, &mmc3_data);
	mxc_register_device(&mxcsdhc1_device, &mmc1_data);
	mxc_register_device(&mxcsdhc2_device, &mmc2_data);
//	mxc_register_device(&mxc_ssi1_device, NULL);
	mxc_register_device(&mxc_ssi2_device, NULL);
//	mxc_register_device(&mxc_alsa_spdif_device, &mxc_spdif_data);
	mxc_register_device(&mxc_android_pmem_device, &android_pmem_data);
	mxc_register_device(&mxc_android_pmem_gpu_device,
				&android_pmem_gpu_data);
	mxc_register_device(&usb_mass_storage_device, &mass_storage_data);
	mxc_register_device(&usb_rndis_device, &rndis_data);
	mxc_register_device(&android_usb_device, &android_usb_data);
//	mxc_register_device(&ahci_fsl_device, &sata_data);

	gpio_request(MX53_BEJ_DCDC3V3_BB_EN_MX5, "dcdc3v3-bb-en-mx5");
	gpio_direction_output(MX53_BEJ_DCDC3V3_BB_EN_MX5, 1);
	gpio_request(MX53_BEJ_DCDC5V_BB_EN, "dcdc5v-bb-en");
	gpio_direction_output(MX53_BEJ_DCDC5V_BB_EN, 1);

#ifdef EVABOARD
	mxc_register_device(&mxc_fec_device, &fec_data);
#endif
	mxc_register_device(&mxc_ptp_device, NULL);
	/* ASRC is only available for MX53 TO2.0 */
	if (mx53_revision() >= IMX_CHIP_REVISION_2_0) {
		mxc_asrc_data.asrc_core_clk = clk_get(NULL, "asrc_clk");
		clk_put(mxc_asrc_data.asrc_core_clk);
		mxc_asrc_data.asrc_audio_clk = clk_get(NULL, "asrc_serial_clk");
		clk_put(mxc_asrc_data.asrc_audio_clk);
		mxc_register_device(&mxc_asrc_device, &mxc_asrc_data);
	}

	spi_device_init();

	i2c_register_board_info(0, mxc_i2c0_board_info,
				ARRAY_SIZE(mxc_i2c0_board_info));
	i2c_register_board_info(1, mxc_i2c1_board_info,
				ARRAY_SIZE(mxc_i2c1_board_info));
	i2c_register_board_info(2, mxc_i2c2_board_info,
				ARRAY_SIZE(mxc_i2c2_board_info));

	sgtl5000_data.ext_ram_clk = clk_get(NULL, "emi_fast_clk");
	clk_put(sgtl5000_data.ext_ram_clk);
	mxc_register_device(&mxc_sgtl5000_device, &sgtl5000_data);

#if 0
	spdif_audio_data.ext_ram_clk = clk_get(NULL, "emi_fast_clk");
	clk_put(spdif_audio_data.ext_ram_clk);
	mxc_register_device(&mxc_spdif_audio_device, &spdif_audio_data);
#endif

	mx5_set_otghost_vbus_func(mx53_gpio_usbotg_driver_vbus);
	mx5_usb_dr_init();
	mx5_usbh1_init();
	mxc_register_device(&mxc_v4l2_device, NULL);
	mxc_register_device(&mxc_v4l2out_device, NULL);

	smd_add_device_buttons();
//	mxc_register_device(&mxc_powerkey_device, &pwrkey_data);
//	smd_add_device_battery();/**/
	pm_i2c_init(I2C1_BASE_ADDR - MX53_OFFSET);
}

static void __init mx53_smd_timer_init(void)
{
	struct clk *uart_clk;

	mx53_clocks_init(32768, 24000000, 22579200, 0);

	uart_clk = clk_get_sys("mxcintuart.0", NULL);
	early_console_setup(MX53_BASE_ADDR(UART1_BASE_ADDR), uart_clk);
}

static struct sys_timer mxc_timer = {
	.init	= mx53_smd_timer_init,
};

#define TRIPLE_1080P_SIZE	(1920*ALIGN(1080, 128)*2*3)
static void __init fixup_android_board(struct machine_desc *desc, struct tag *tags,
				   char **cmdline, struct meminfo *mi)
{
	char *str;
	struct tag *t, *mem_tag = 0;
	int reserve_2ndisp = 1;
	int total_mem = SZ_1G;
	int left_mem = 0;
	int gpu_mem = SZ_64M;
	int fb0_mem = 0, fb_mem = ALIGN(TRIPLE_1080P_SIZE, SZ_1M);
	int pmem_gpu_size = android_pmem_gpu_data.size;
	int pmem_adsp_size = android_pmem_data.size;

	mxc_set_cpu_type(MXC_CPU_MX53);

	/* get fbmem= and gpu_memory= from cmdline */
	for_each_tag(t, tags) {
		if (t->hdr.tag == ATAG_CMDLINE) {
			str = t->u.cmdline.cmdline;
			str = strstr(str, "fbmem=");
			if (str != NULL) {
				str += 6;
				fb0_mem = memparse(str, &str);
			}

			str = t->u.cmdline.cmdline;
			str = strstr(str, "gpu_memory=");
			if (str != NULL) {
				str += 11;
				gpu_mem = memparse(str, &str);
			}

			str = t->u.cmdline.cmdline;
			str = strstr(str, "pmem=");
			if (str != NULL) {
				str += 5;
				pmem_gpu_size = memparse(str, &str);
				android_pmem_gpu_data.size = pmem_gpu_size;
				if (*str == ',') {
					str++;
					pmem_adsp_size = memparse(str, &str);
					android_pmem_data.size = pmem_adsp_size;
				}
			}

			str = t->u.cmdline.cmdline;
			if (strstr(str, "di0_primary"))
				reserve_2ndisp = 0;
			break;
		}
	}

	/* get total memory from TAGS */
	for_each_tag(t, tags) {
		if (t->hdr.tag == ATAG_MEM)
			if (!mem_tag ||
				(t->u.mem.size != 0 && mem_tag &&
				mem_tag->u.mem.start < t->u.mem.start))
				mem_tag = t;
	}

	total_mem = mem_tag->u.mem.size;
	left_mem = total_mem - gpu_mem
		- fb_mem * (reserve_2ndisp ? 2 : 1) - fb0_mem
		- pmem_gpu_size - pmem_adsp_size;

	if (left_mem <= 0)
		panic("No enough left memory for kernel!");

	if (mem_tag) {
		int start;

		android_pmem_data.start = mem_tag->u.mem.start
				+ left_mem + gpu_mem + pmem_gpu_size;
		android_pmem_gpu_data.start = mem_tag->u.mem.start
				+ left_mem + gpu_mem;
		mem_tag->u.mem.size = left_mem;

		/*reserve memory for gpu*/
		if (!gpu_data.enable_mmu) {
			gpu_device.resource[5].start =
				mem_tag->u.mem.start + left_mem;
			gpu_device.resource[5].end =
				gpu_device.resource[5].start + gpu_mem - 1;
		}

		if (reserve_2ndisp) {
			mxcfb_resources[1].start =
				android_pmem_data.start + android_pmem_data.size;
			mxcfb_resources[1].end =
				mxcfb_resources[1].start + fb_mem - 1;
			start = mxcfb_resources[1].end + 1;
		} else {
			start = android_pmem_data.start + android_pmem_data.size;
		}

		mxcfb_resources[2].start = start;
		mxcfb_resources[2].end = start + fb_mem - 1;
		if (fb0_mem) {
			mxcfb_resources[0].start =
				mxcfb_resources[2].end + 1;
			mxcfb_resources[0].end =
				mxcfb_resources[0].start + fb0_mem - 1;
		}
	}
}

/*
 * The following uses standard kernel macros define in arch.h in order to
 * initialize __mach_desc_MX53_BEJ data structure.
 */
MACHINE_START(MX53_BEJ, "Freescale MX53 BEJ Board")
	/* Maintainer: Freescale Semiconductor, Inc. */
#ifdef CONFIG_ANDROID_PMEM
	.fixup = fixup_android_board,
#else
	.fixup = fixup_mxc_board,
#endif
	.map_io = mx5_map_io,
	.init_irq = mx5_init_irq,
	.init_machine = mxc_board_init,
	.timer = &mxc_timer,
MACHINE_END
