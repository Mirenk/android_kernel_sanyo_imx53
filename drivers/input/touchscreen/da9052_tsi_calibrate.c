/*
 * da9052_tsi_calibrate.c  --  TSI Calibration driver for Dialog DA9052
 *
 * Copyright(c) 2009 Dialog Semiconductor Ltd.
 *
 * Author: Dialog Semiconductor Ltd <dchen@diasemi.com>
 *
 *  This program is free software; you can redistribute  it and/or modify it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 */

#include <linux/mfd/da9052/tsi.h>

static struct Calib_xform_matrix_t xform = {
		.An = DA9052_TSI_CALIB_AN,
		.Bn = DA9052_TSI_CALIB_BN,
		.Cn = DA9052_TSI_CALIB_CN,
		.Dn = DA9052_TSI_CALIB_DN,
		.En = DA9052_TSI_CALIB_EN,
		.Fn = DA9052_TSI_CALIB_FN,
		.Divider = DA9052_TSI_CALIB_DIVIDER
};

/***** Sanyo CE Add Start *****/
/* /sys/module/da9052-tsi/parameters/calibrationからｷｬﾘﾌﾞﾚｰｼｮﾝ係数取得に変更 */
extern s32 calibration[9];




static int da9052_tsi_calib_data_set()
{
	if( calibration[6] == 0 ) return FALSE;	//補正係数なし
//---- Sanyo CE
//printk("Calibration info a:%d b:%d c:%d d:%d e:%d f:%d s:%d W:%d H:%d\n" ,calibration[0] ,calibration[1] ,calibration[2] ,calibration[3] ,calibration[4] ,calibration[5] ,calibration[6] ,calibration[7] ,calibration[8]);
//---- Sanyo CE
	xform.An = calibration[0];
	xform.Bn = calibration[1];
	xform.Cn = calibration[2];
	xform.Dn = calibration[3];
	xform.En = calibration[4];
	xform.Fn = calibration[5];
	xform.Divider = calibration[6];
	return TRUE;
}
/***** Sanyo CE Add End *****/

static struct calib_cfg_t calib = {
	.calibrate_flag = TSI_USE_CALIBRATION,
};

struct calib_cfg_t *get_calib_config(void)
{
	return &calib;
}

ssize_t da9052_tsi_set_calib_matrix(struct da9052_tsi_data *displayPtr,
				struct da9052_tsi_data *screenPtr)
{

	int  retValue = SUCCESS ;

	xform.Divider = ((screenPtr[0].x - screenPtr[1].x)
			* (screenPtr[1].y - screenPtr[2].y))
			- ((screenPtr[1].x - screenPtr[2].x)
			* (screenPtr[0].y - screenPtr[1].y));

	if (xform.Divider == 0)
		retValue = -FAILURE;
	else	{
		xform.An = ((displayPtr[0].x - displayPtr[1].x)
			* (screenPtr[1].y - screenPtr[2].y))
			- ((displayPtr[1].x - displayPtr[2].x)
			* (screenPtr[0].y - screenPtr[1].y));

		xform.Bn = ((displayPtr[1].x - displayPtr[2].x)
			* (screenPtr[0].x - screenPtr[1].x))
			- ((screenPtr[1].x - screenPtr[2].x)
			* (displayPtr[0].x - displayPtr[1].x));

		 xform.Cn = (displayPtr[0].x * xform.Divider)
			- (screenPtr[0].x * xform.An)
			- (screenPtr[0].y * xform.Bn);

		xform.Dn = ((displayPtr[0].y - displayPtr[1].y)
			* (screenPtr[1].y - screenPtr[2].y))
			- ((displayPtr[1].y - displayPtr[2].y)
			* (screenPtr[0].y - screenPtr[1].y));

		xform.En = ((displayPtr[1].y - displayPtr[2].y)
			* (screenPtr[0].x - screenPtr[1].x))
			- ((screenPtr[1].x - screenPtr[2].x)
			* (displayPtr[0].y - displayPtr[1].y));

		xform.Fn = (displayPtr[0].y * xform.Divider)
			- (screenPtr[0].x * xform.Dn)
			- (screenPtr[0].y * xform.En);
	}

	return retValue;
}

ssize_t da9052_tsi_get_calib_display_point(struct da9052_tsi_data *displayPtr)
{
	int  retValue = TRUE;

/***** Sanyo CE Modify Start *****/
	#if 1
	struct da9052_tsi_cal_data {
	 	s32	x;
		s32	y;
		s32	z;
	};

	struct da9052_tsi_cal_data screen_coord;

	#else
	struct da9052_tsi_data screen_coord;
	#endif
/***** Sanyo CE Modify End *****/
/***** Sanyo CE Add Start *****/
	if (da9052_tsi_calib_data_set() == FALSE )		//補正係数セット
			 return retValue;								//補正係数がないのでそのまま返す
/***** Sanyo CE Add End *****/

/***** Sanyo CE Modify Start *****/
	#if 0
	screen_coord = *displayPtr;
	#else
	screen_coord.x = displayPtr->x;
	screen_coord.y = displayPtr->y;
	screen_coord.z = displayPtr->z;
	#endif
/***** Sanyo CE Modify End *****/

	if (xform.Divider != 0)	{
		displayPtr->x = ((xform.An * screen_coord.x) +
			(xform.Bn * screen_coord.y) +
				xform.Cn
			) / xform.Divider;

	displayPtr->y = ((xform.Dn * screen_coord.x) +
			(xform.En * screen_coord.y) +
				xform.Fn
			) / xform.Divider;
/***** Sanyo CE Modify Start *****/
			displayPtr->y = displayPtr->y * calibration[7]  / calibration[8] ;
/***** Sanyo CE Modify End *****/
	} else
		retValue = FALSE;

#if DA9052_TSI_CALIB_DATA_PROFILING
	printk("C\tX\t%4d\tY\t%4d\n",
					displayPtr->x,
					displayPtr->y);
#endif
	return retValue;
}
