/*
 * Copyright (c) 2012 SANYO Consumer Electronics Co., Ltd.
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
//--------------------------------------------------------------------------
//
//新カメラモジュール用パラメータ関連ヘッダファイル
//
//--------------------------------------------------------------------------
# define DEBUG

enum rnss2e1_mode {
	rnss2e1_mode_MIN = 0,
	rnss2e1_mode_QVGA_320_240   = 0,		//SCE Add
	rnss2e1_mode_VGA_640_480    = 1,		//SCE Add
	rnss2e1_mode_SVGA_800_600   = 2,		
	rnss2e1_mode_XGA_1024_768   = 3,		//SCE Add
	rnss2e1_mode_HD_1280_720    = 4,		//SCE Add
	rnss2e1_mode_UXGA_1600_1200 = 5,		//SCE Add
	rnss2e1_mode_MAX = 5
};

enum rnss2e1_frame_rate {
	rnss2e1_15_fps,
	rnss2e1_30_fps,
};

struct reg_value {
	u8 u8RegAddr;
	u8 u8Val;
	u8 u8Mask;
	u32 u32Delay_ms;
};

struct rnss2e1_mode_info {
	enum rnss2e1_mode mode;
	u32 width;
	u32 height;
	struct reg_value *init_data_ptr;
	u32 init_data_size;
};


enum rnss2e1_effect_mode {
	rnss2e1_effect_mode_none = 0,
	rnss2e1_effect_mode_mono = 1,
	rnss2e1_effect_mode_negative = 2,
	rnss2e1_effect_mode_solarize = 3,
	rnss2e1_effect_mode_sepia = 4,
	rnss2e1_effect_mode_posterize = 5,
	rnss2e1_effect_mode_whiteboard = 6,
	rnss2e1_effect_mode_blackboard = 7,
	rnss2e1_effect_mode_aqua = 8,
	rnss2e1_effect_mode_MAX = 8,
};


enum rnss2e1_wb_mode {
	rnss2e1_wb_mode_auto = 0,
	rnss2e1_wb_mode_incandescent = 1,
	rnss2e1_wb_mode_fluorescent = 2,
	rnss2e1_wb_mode_warm_fluorescent = 3,
	rnss2e1_wb_mode_daylight = 4,
	rnss2e1_wb_mode_cloudy_daylight = 5,
	rnss2e1_wb_mode_twilight = 6,
	rnss2e1_wb_mode_shade = 7,
	rnss2e1_wb_mode_MAX = 7
};


enum rnss2e1_scene_mode {
	rnss2e1_scene_mode_auto = 0,
	rnss2e1_scene_mode_sports = 1,
	rnss2e1_scene_mode_portrait = 2,
	rnss2e1_scene_mode_landscape = 3,
	rnss2e1_scene_mode_naightportrait = 4,
	rnss2e1_scene_mode_night = 5,
	rnss2e1_scene_mode_theatre = 6,
	rnss2e1_scene_mode_beach = 7,
	rnss2e1_scene_mode_snow = 8,
	rnss2e1_scene_mode_sunset = 9,
	rnss2e1_scene_mode_steadyphoto = 10,
	rnss2e1_scene_mode_fireworks = 11,
	rnss2e1_scene_mode_patry = 12,
	rnss2e1_scene_mode_candlelight = 13,
	rnss2e1_scene_mode_MAX = 13,
};

struct rnss2e1_reg_info {
#ifdef DEBUG
	u32 mode;							//動作モード
#endif
	struct reg_value *init_data_ptr;	//パラメータのポインタ
	u32 init_data_size;					//パラメータのサイズ
};


/*!
 * Maintains the information on the current state of the sesor.
 */
struct sensor {
	const struct rnss2e1_platform_data *platform_data;
	struct v4l2_int_device *v4l2_int_device;
	struct i2c_client *i2c_client;
	struct v4l2_pix_format pix;
	struct v4l2_captureparm streamcap;
	bool on;

	/* control settings */
	int brightness;
	int hue;
	int contrast;
	int saturation;
	int red;
	int green;
	int blue;
	int ae_mode;

	u32 mclk;
	int csi;
} rnss2e1_data;

static struct reg_value rnss2e1_rotate_none[] = {
	{0xFD, 0x00 , 0 , 0},//dummy
};

static struct reg_value rnss2e1_rotate_vert_flip[] = {
	{0xFD, 0x00 , 0 , 0},//dummy
};

static struct reg_value rnss2e1_rotate_horiz_flip[] = {
	{0xFD, 0x00 , 0 , 0},//dummy
};

static struct reg_value rnss2e1_rotate_180[] = {
	{0xFD, 0x00 , 0 , 0},//dummy
};

//Color effect Table

static struct reg_value rnss2e1_setting_color_effect_none[] = {
	{0xFD, 0x02, 0, 0},
	{0x62, 0x00, 0, 0},
};

static struct reg_value rnss2e1_setting_color_effect_mono[] = {
	{0xFD, 0x02, 0, 0},
	{0x63, 0x80, 0, 0},
	{0x64, 0x80, 0, 0},
	{0x62, 0x20, 0, 0},
};

static struct reg_value rnss2e1_setting_color_effect_sepia[] = {
	{0xFD, 0x02, 0, 0},
	{0x63, 0xA4, 0, 0},
	{0x64, 0x52, 0, 0},
	{0x62, 0x10, 0, 0},
};

static struct reg_value rnss2e1_setting_color_effect_gray_neg[] = {
	{0xFD, 0x02, 0, 0},
	{0x62, 0x08, 0, 0},
};

static struct reg_value rnss2e1_setting_color_effect_aqua[] = {
	{0xFD, 0x02, 0, 0},
	{0x63, 0x52, 0, 0},
	{0x64, 0xA4, 0, 0},
	{0x62, 0x10, 0, 0},
};

static struct rnss2e1_reg_info rnss2e1_effect_data[rnss2e1_effect_mode_MAX+1] = {
	{//effect none
#ifdef DEBUG
		rnss2e1_effect_mode_none,
#endif
		rnss2e1_setting_color_effect_none,
		ARRAY_SIZE(rnss2e1_setting_color_effect_none)
	},
	{//effect mono
#ifdef DEBUG
		rnss2e1_effect_mode_mono,
#endif
		rnss2e1_setting_color_effect_mono,
		ARRAY_SIZE(rnss2e1_setting_color_effect_mono)
	},
	{//effect negative
#ifdef DEBUG
		rnss2e1_effect_mode_negative,
#endif
		rnss2e1_setting_color_effect_gray_neg,
		ARRAY_SIZE(rnss2e1_setting_color_effect_gray_neg)
	},
	{//effect Solarize
#ifdef DEBUG
		rnss2e1_effect_mode_solarize,
#endif
		0x00, 0
	},
	{// effect sepia
#ifdef DEBUG
		rnss2e1_effect_mode_sepia,
#endif
		rnss2e1_setting_color_effect_sepia,
		ARRAY_SIZE(rnss2e1_setting_color_effect_sepia)
	},
	{//effect Posterize
#ifdef DEBUG
			rnss2e1_effect_mode_posterize,
#endif
		0x00, 0
	},
	{//effect WhiteBoard
#ifdef DEBUG
		rnss2e1_effect_mode_whiteboard,
#endif
		0x00, 0
	},
	{//effect BlackBoard
#ifdef DEBUG
		rnss2e1_effect_mode_blackboard,
#endif
		0x00, 0
	},
	{//effect aqua
#ifdef DEBUG
		rnss2e1_effect_mode_aqua,
#endif
		rnss2e1_setting_color_effect_aqua,
		ARRAY_SIZE(rnss2e1_setting_color_effect_aqua)
	},
};

//White Balance Table
//オート
static struct reg_value rnss2e1_setting_whitebalance_auto[] = {
	{0xFD, 0x03, 0, 0},
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy

	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
};

//白熱灯
static struct reg_value rnss2e1_setting_whitebalance_incandescent[] = {
	{0xFD, 0x03, 0, 0},
	{0x20, 0x8F, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x7F, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xC2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xB2, 0, 0},   //# 323 bgain_bot_dummy

	{0x00, 0x8F, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x7F, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xC2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xB2, 0, 0},   //# 303 bgain_bot_outdoor
};

//昼光
static struct reg_value rnss2e1_setting_whitebalance_daylight[] = {
	{0xFD, 0x03, 0, 0},
	{0x20, 0xC6, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0xA8, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x90, 0, 0},   //# 323 bgain_bot_dummy

	{0x00, 0xC6, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0xA8, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x90, 0, 0},   //# 303 bgain_bot_outdoor
};

//蛍光灯
static struct reg_value rnss2e1_setting_whitebalance_fluorescent[] = {
	{0xFD, 0x03, 0, 0},
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy

	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
};

//曇り
static struct reg_value rnss2e1_setting_whitebalance_cludy[] = {
	{0xFD, 0x03, 0, 0},
	{0x20, 0xDC, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0xCC, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0x75, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x65, 0, 0},   //# 323 bgain_bot_dummy

	{0x00, 0xDC, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0xCC, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0x75, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x65, 0, 0},   //# 303 bgain_bot_outdoor
};

static struct rnss2e1_reg_info rnss2e1_whitebalance_data[rnss2e1_wb_mode_MAX+1] = {
	{//オート
#ifdef DEBUG
		rnss2e1_wb_mode_auto,
#endif
		rnss2e1_setting_whitebalance_auto,
		ARRAY_SIZE(rnss2e1_setting_whitebalance_auto)
	},
	{//白熱灯
#ifdef DEBUG
		rnss2e1_wb_mode_incandescent,
#endif
		rnss2e1_setting_whitebalance_incandescent,
		ARRAY_SIZE(rnss2e1_setting_whitebalance_incandescent)
	},
	{//蛍光灯
#ifdef DEBUG
		rnss2e1_wb_mode_fluorescent,
#endif
		rnss2e1_setting_whitebalance_fluorescent,
		ARRAY_SIZE(rnss2e1_setting_whitebalance_fluorescent)
	},
	{//暖かい色の蛍光灯
#ifdef DEBUG
		rnss2e1_wb_mode_warm_fluorescent,
#endif
		0x00, 0
	},
	{//昼光
#ifdef DEBUG
		rnss2e1_wb_mode_daylight,
#endif
		rnss2e1_setting_whitebalance_daylight,
		ARRAY_SIZE(rnss2e1_setting_whitebalance_daylight)
	},
	{//曇り
#ifdef DEBUG
		rnss2e1_wb_mode_cloudy_daylight,
#endif
		rnss2e1_setting_whitebalance_cludy,
		ARRAY_SIZE(rnss2e1_setting_whitebalance_cludy)
	},
	{//夕暮れ
#ifdef DEBUG
		rnss2e1_wb_mode_twilight,
#endif
		0x00, 0
	},
	{//日陰
#ifdef DEBUG
		rnss2e1_wb_mode_shade,
#endif
		0x00, 0
	}
};

//シーン設定
//========== 設定レジスタ値 ==========
// ***** オート *****
//# RNSS2E1 SCENE [AUTO]
//#
static struct reg_value rnss2e1_setting_scene_Auto_A[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x64, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x64, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [AUTO]
//#
static struct reg_value rnss2e1_setting_scene_Auto_B[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC7, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC7, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [AUTO]
//#
static struct reg_value rnss2e1_setting_scene_Auto_C[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x9F, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x9F, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [AUTO]
//#
static struct reg_value rnss2e1_setting_scene_Auto_D[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x7A, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x7A, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [AUTO]
//#
static struct reg_value rnss2e1_setting_scene_Auto_E[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC2, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC2, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

// ***** スポーツ *****
//# RNSS2E1 SCENE [SPORT]
//#
static struct reg_value rnss2e1_setting_scene_Sport_A[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x64, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x64, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x8E, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x8E, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x7F, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x4B, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x8E, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x8E, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x7F, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x4B, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [SPORT]
//#
static struct reg_value rnss2e1_setting_scene_Sport_B[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC7, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC7, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x8E, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x8E, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x7F, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x4B, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x8E, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x8E, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x7F, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x4B, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [SPORT]
//#
static struct reg_value rnss2e1_setting_scene_Sport_C[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x9F, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x9F, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x8E, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x8E, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x7F, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x4B, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x8E, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x8E, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x7F, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x4B, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [SPORT]
//#
static struct reg_value rnss2e1_setting_scene_Sport_D[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x7A, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x7A, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x8E, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x8E, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x7F, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x4B, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x8E, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x8E, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x7F, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x4B, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [SPORT]
//#
static struct reg_value rnss2e1_setting_scene_Sport_E[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC2, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC2, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x8E, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x8E, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x7F, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x4B, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x8E, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x8E, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x7F, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x4B, 0, 0},   //# 2DB sat_v_s4
};


// ***** ポートレイト *****
//# RNSS2E1 SCENE [PORTRAIT]
//#
static struct reg_value rnss2e1_setting_scene_Portrait_A[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x64, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x64, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x50, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x80, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x90, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x80, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x90, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x8C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x84, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x8C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x84, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [PORTRAIT]
//#
static struct reg_value rnss2e1_setting_scene_Portrait_B[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC7, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC7, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x50, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x80, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x90, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x80, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x90, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x8C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x84, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x8C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x84, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [PORTRAIT]
//#
static struct reg_value rnss2e1_setting_scene_Portrait_C[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x9F, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x9F, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x50, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x80, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x90, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x80, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x90, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x8C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x84, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x8C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x84, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [PORTRAIT]
//#
static struct reg_value rnss2e1_setting_scene_Portrait_D[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x7A, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x7A, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x50, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x80, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x90, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x80, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x90, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x8C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x84, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x8C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x84, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [PORTRAIT]
//#
static struct reg_value rnss2e1_setting_scene_Portrait_E[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC2, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC2, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x50, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x80, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x90, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x80, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x90, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x8C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x84, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x8C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x84, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};


// ***** 風景 *****
//# RNSS2E1 SCENE [LANDSCAPE]
//#
static struct reg_value rnss2e1_setting_scene_Landscape_A[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x64, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x64, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x50, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x68, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x68, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x3E, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x29, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x29, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x29, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x29, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x29, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [LANDSCAPE]
//#
static struct reg_value rnss2e1_setting_scene_Landscape_B[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC7, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC7, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x50, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},

	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x68, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x68, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x3E, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x29, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x29, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x29, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x29, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x29, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [LANDSCAPE]
//#
static struct reg_value rnss2e1_setting_scene_Landscape_C[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x9F, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x9F, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x50, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x68, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x68, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x3E, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x29, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x29, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x29, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x29, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x29, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [LANDSCAPE]
//#
static struct reg_value rnss2e1_setting_scene_Landscape_D[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x7A, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x7A, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x50, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x68, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x68, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x3E, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x29, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x29, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x29, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x29, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x29, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [LANDSCAPE]
//#
static struct reg_value rnss2e1_setting_scene_Landscape_E[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC2, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC2, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x50, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x68, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x68, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x3E, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x29, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x29, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x29, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x29, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x29, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

// ***** 夜景 *****
//# RNSS2E1 SCENE [NIGHT]
//#
static struct reg_value rnss2e1_setting_scene_Night_A[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x64, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x64, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x80, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x68, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x78, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x68, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x78, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x74, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x6C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x74, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x6C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [NIGHT]
//#
static struct reg_value rnss2e1_setting_scene_Night_B[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC7, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC7, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x80, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x68, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x78, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x68, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x78, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x74, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x6C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x74, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x6C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [NIGHT]
//#
static struct reg_value rnss2e1_setting_scene_Night_C[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x9F, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x9F, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x80, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x68, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x78, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x68, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x78, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x74, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x6C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x74, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x6C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [NIGHT]
//#
static struct reg_value rnss2e1_setting_scene_Night_D[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x7A, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x7A, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x80, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x68, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x78, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x68, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x78, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x74, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x6C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x74, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x6C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [NIGHT]
//#
static struct reg_value rnss2e1_setting_scene_Night_E[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC2, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC2, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x80, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x68, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x78, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x68, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x78, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x74, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x6C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x74, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x6C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};


// ***** ナイトスナップ *****
//# RNSS2E1 SCENE [NIGHTSNAP]
//#
static struct reg_value rnss2e1_setting_scene_NightSnap_A[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x64, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x64, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x50, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [NIGHTSNAP]
//#
static struct reg_value rnss2e1_setting_scene_NightSnap_B[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC7, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC7, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x50, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [NIGHTSNAP]
//#
static struct reg_value rnss2e1_setting_scene_NightSnap_C[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x9F, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x9F, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x50, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [NIGHTSNAP]
//#
static struct reg_value rnss2e1_setting_scene_NightSnap_D[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x7A, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x7A, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x50, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [NIGHTSNAP]
//#
static struct reg_value rnss2e1_setting_scene_NightSnap_E[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC2, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC2, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x50, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};


// ***** シアター *****
//# RNSS2E1 SCENE [THEATER]
//#
static struct reg_value rnss2e1_setting_scene_Theater_A[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x64, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x64, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x70, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x80, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x70, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x80, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x7C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x74, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x7C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x74, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0xA1, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0xA1, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x90, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x55, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0xA1, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0xA1, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x90, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x55, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [THEATER]
//#
static struct reg_value rnss2e1_setting_scene_Theater_B[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC7, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC7, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x70, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x80, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x70, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x80, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x7C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x74, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x7C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x74, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0xA1, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0xA1, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x90, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x55, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0xA1, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0xA1, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x90, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x55, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [THEATER]
//#
static struct reg_value rnss2e1_setting_scene_Theater_C[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x9F, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x9F, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x70, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x80, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x70, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x80, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x7C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x74, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x7C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x74, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0xA1, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0xA1, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x90, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x55, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0xA1, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0xA1, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x90, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x55, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [THEATER]
//#
static struct reg_value rnss2e1_setting_scene_Theater_D[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x7A, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x7A, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x70, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x80, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x70, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x80, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x7C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x74, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x7C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x74, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0xA1, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0xA1, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x90, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x55, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0xA1, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0xA1, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x90, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x55, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [THEATER]
//#
static struct reg_value rnss2e1_setting_scene_Theater_E[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC2, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC2, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x70, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x80, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x70, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x80, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x7C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x74, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x7C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x74, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0xA1, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0xA1, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x90, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x55, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0xA1, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0xA1, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x90, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x55, 0, 0},   //# 2DB sat_v_s4
};

// ***** ビーチ *****
//# RNSS2E1 SCENE [BEACH]
//#
static struct reg_value rnss2e1_setting_scene_Beach_A[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x64, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x64, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x50, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x80, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x90, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x80, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x90, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x8C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x84, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x8C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x84, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xC6, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0xA8, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x90, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xC6, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0xA8, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x90, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [BEACH]
//#
static struct reg_value rnss2e1_setting_scene_Beach_B[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC7, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC7, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x50, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x80, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x90, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x80, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x90, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x8C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x84, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x8C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x84, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xC6, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0xA8, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x90, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xC6, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0xA8, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x90, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [BEACH]
//#
static struct reg_value rnss2e1_setting_scene_Beach_C[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x9F, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x9F, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x50, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x80, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x90, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x80, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x90, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x8C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x84, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x8C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x84, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xC6, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0xA8, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x90, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xC6, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0xA8, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x90, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [BEACH]
//#
static struct reg_value rnss2e1_setting_scene_Beach_D[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x7A, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x7A, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x50, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x80, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x90, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x80, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x90, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x8C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x84, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x8C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x84, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xC6, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0xA8, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x90, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xC6, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0xA8, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x90, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [BEACH]
//#
static struct reg_value rnss2e1_setting_scene_Beach_E[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC2, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC2, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x50, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x80, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x90, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x80, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x90, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x8C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x84, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x8C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x84, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xC6, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0xA8, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x90, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xC6, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0xA8, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x90, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};


// ***** スノー *****
//# RNSS2E1 SCENE [SNOW]
//#
static struct reg_value rnss2e1_setting_scene_Snow_A[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x64, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x64, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x88, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x98, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x88, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x98, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x94, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x8C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x94, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x8C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x68, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x68, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x3E, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x29, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x29, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x29, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x29, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x29, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [SNOW]
//#
static struct reg_value rnss2e1_setting_scene_Snow_B[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC7, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC7, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x88, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x98, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x88, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x98, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x94, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x8C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x94, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x8C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x68, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x68, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x3E, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x29, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x29, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x29, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x29, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x29, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [SNOW]
//#
static struct reg_value rnss2e1_setting_scene_Snow_C[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x9F, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x9F, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x88, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x98, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x88, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x98, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x94, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x8C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x94, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x8C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x68, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x68, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x3E, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x29, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x29, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x29, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x29, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x29, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [SNOW]
//#
static struct reg_value rnss2e1_setting_scene_Snow_D[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x7A, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x7A, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x88, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x98, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x88, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x98, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x94, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x8C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x94, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x8C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x68, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x68, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x3E, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x29, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x29, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x29, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x29, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x29, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [SNOW]
//#
static struct reg_value rnss2e1_setting_scene_Snow_E[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC2, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC2, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x88, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x98, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x88, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x98, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x94, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x8C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x94, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x8C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x68, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x68, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x3E, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x29, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x29, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x29, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x29, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x29, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};


// ***** 夕焼け *****
//# RNSS2E1 SCENE [SUNSET]
//#
static struct reg_value rnss2e1_setting_scene_Sunset_A[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x64, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x64, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xC6, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0xA8, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x90, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xC6, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0xA8, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x90, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x38, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x38, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x21, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x16, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x16, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x16, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x16, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x16, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0xA1, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0xA1, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x90, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x55, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0xA1, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0xA1, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x90, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x55, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [SUNSET]
//#
static struct reg_value rnss2e1_setting_scene_Sunset_B[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC7, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC7, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xC6, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0xA8, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x90, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xC6, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0xA8, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x90, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x38, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x38, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x21, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x16, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x16, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x16, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x16, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x16, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0xA1, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0xA1, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x90, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x55, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0xA1, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0xA1, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x90, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x55, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [SUNSET]
//#
static struct reg_value rnss2e1_setting_scene_Sunset_C[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x9F, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x9F, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xC6, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0xA8, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x90, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xC6, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0xA8, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x90, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x38, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x38, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x21, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x16, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x16, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x16, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x16, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x16, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0xA1, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0xA1, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x90, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x55, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0xA1, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0xA1, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x90, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x55, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [SUNSET]
//#
static struct reg_value rnss2e1_setting_scene_Sunset_D[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x7A, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x7A, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xC6, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0xA8, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x90, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xC6, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0xA8, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x90, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x38, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x38, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x21, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x16, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x16, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x16, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x16, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x16, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0xA1, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0xA1, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x90, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x55, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0xA1, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0xA1, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x90, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x55, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [SUNSET]
//#
static struct reg_value rnss2e1_setting_scene_Sunset_E[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC2, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC2, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xC6, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0xA8, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x90, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xC6, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0xA8, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x90, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x38, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x38, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x21, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x16, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x16, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x16, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x16, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x16, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0xA1, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0xA1, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x90, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x55, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0xA1, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0xA1, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x90, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x55, 0, 0},   //# 2DB sat_v_s4
};



// ***** 手振れ補正 *****
#if 1
//QR Code読込み用としてオートモードに設定を追加した設定となっている
//# RNSS2E1 SCENE [ACTION]
//#
static struct reg_value rnss2e1_setting_scene_Action_A[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x64, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x64, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
//# for QR Code Read
	{0xFD, 0x03, 0, 0},
	{0xE9, 0xFF, 0, 0}, //# 3E9 sharp_fac_pos_nr
	{0xED, 0xFF, 0, 0}, //# 3ED sharp_fac_neg_nr
	{0xFD, 0x02, 0, 0},
	{0x34, 0xE7, 0, 0}, //# 234 NR
	{0xFD, 0x03, 0, 0},
	{0xDE, 0x0B, 0, 0}, //# 3DE raw_denoise_en_nr
	{0xFD, 0x02, 0, 0},
	{0xDE, 0xB0, 0, 0}, //# 2DE Contrast kl
	{0xFD, 0x02, 0, 0},
	{0x33, 0x0F, 0, 0}, //# 233 lsc_bpc_en
};

//# RNSS2E1 SCENE [ACTION]
//#
static struct reg_value rnss2e1_setting_scene_Action_B[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC7, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC7, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
//# for QR Code Read
	{0xFD, 0x03, 0, 0},
	{0xE9, 0xFF, 0, 0}, //# 3E9 sharp_fac_pos_nr
	{0xED, 0xFF, 0, 0}, //# 3ED sharp_fac_neg_nr
	{0xFD, 0x02, 0, 0},
	{0x34, 0xE7, 0, 0}, //# 234 NR
	{0xFD, 0x03, 0, 0},
	{0xDE, 0x0B, 0, 0}, //# 3DE raw_denoise_en_nr
	{0xFD, 0x02, 0, 0},
	{0xDE, 0xB0, 0, 0}, //# 2DE Contrast kl
	{0xFD, 0x02, 0, 0},
	{0x33, 0x0F, 0, 0}, //# 233 lsc_bpc_en
};

//# RNSS2E1 SCENE [ACTION]
//#
static struct reg_value rnss2e1_setting_scene_Action_C[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x9F, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x9F, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
//# for QR Code Read
	{0xFD, 0x03, 0, 0},
	{0xE9, 0xFF, 0, 0}, //# 3E9 sharp_fac_pos_nr
	{0xED, 0xFF, 0, 0}, //# 3ED sharp_fac_neg_nr
	{0xFD, 0x02, 0, 0},
	{0x34, 0xE7, 0, 0}, //# 234 NR
	{0xFD, 0x03, 0, 0},
	{0xDE, 0x0B, 0, 0}, //# 3DE raw_denoise_en_nr
	{0xFD, 0x02, 0, 0},
	{0xDE, 0xB0, 0, 0}, //# 2DE Contrast kl
	{0xFD, 0x02, 0, 0},
	{0x33, 0x0F, 0, 0}, //# 233 lsc_bpc_en
};

//# RNSS2E1 SCENE [ACTION]
//#
static struct reg_value rnss2e1_setting_scene_Action_D[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x7A, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x7A, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
//# for QR Code Read
	{0xFD, 0x03, 0, 0},
	{0xE9, 0xFF, 0, 0}, //# 3E9 sharp_fac_pos_nr
	{0xED, 0xFF, 0, 0}, //# 3ED sharp_fac_neg_nr
	{0xFD, 0x02, 0, 0},
	{0x34, 0xE7, 0, 0}, //# 234 NR
	{0xFD, 0x03, 0, 0},
	{0xDE, 0x0B, 0, 0}, //# 3DE raw_denoise_en_nr
	{0xFD, 0x02, 0, 0},
	{0xDE, 0xB0, 0, 0}, //# 2DE Contrast kl
	{0xFD, 0x02, 0, 0},
	{0x33, 0x0F, 0, 0}, //# 233 lsc_bpc_en
};

//# RNSS2E1 SCENE [ACTION]
//#
static struct reg_value rnss2e1_setting_scene_Action_E[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC2, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC2, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
//# for QR Code Read
	{0xFD, 0x03, 0, 0},
	{0xE9, 0xFF, 0, 0}, //# 3E9 sharp_fac_pos_nr
	{0xED, 0xFF, 0, 0}, //# 3ED sharp_fac_neg_nr
	{0xFD, 0x02, 0, 0},
	{0x34, 0xE7, 0, 0}, //# 234 NR
	{0xFD, 0x03, 0, 0},
	{0xDE, 0x0B, 0, 0}, //# 3DE raw_denoise_en_nr
	{0xFD, 0x02, 0, 0},
	{0xDE, 0xB0, 0, 0}, //# 2DE Contrast kl
	{0xFD, 0x02, 0, 0},
	{0x33, 0x0F, 0, 0}, //# 233 lsc_bpc_en
};

#else
// ***** 手振れ補正 *****
//# RNSS2E1 SCENE [ACTION]
//#
static struct reg_value rnss2e1_setting_scene_Action_A[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x64, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x64, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x70, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x80, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x70, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x80, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x7C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x74, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x7C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x74, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0xA1, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0xA1, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x90, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x55, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0xA1, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0xA1, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x90, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x55, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [ACTION]
//#
static struct reg_value rnss2e1_setting_scene_Action_B[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC7, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC7, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x70, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x80, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x70, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x80, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x7C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x74, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x7C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x74, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0xA1, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0xA1, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x90, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x55, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0xA1, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0xA1, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x90, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x55, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [ACTION]
//#
static struct reg_value rnss2e1_setting_scene_Action_C[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x9F, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x9F, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x70, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x80, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x70, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x80, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x7C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x74, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x7C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x74, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0xA1, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0xA1, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x90, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x55, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0xA1, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0xA1, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x90, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x55, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [ACTION]
//#
static struct reg_value rnss2e1_setting_scene_Action_D[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x7A, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x7A, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x70, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x80, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x70, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x80, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x7C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x74, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x7C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x74, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0xA1, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0xA1, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x90, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x55, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0xA1, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0xA1, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x90, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x55, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [ACTION]
//#
static struct reg_value rnss2e1_setting_scene_Action_E[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC2, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC2, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x70, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x80, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x70, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x80, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x7C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x74, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x7C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x74, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0xA1, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0xA1, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x90, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x55, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0xA1, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0xA1, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x90, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x55, 0, 0},   //# 2DB sat_v_s4
};



#endif

// ***** 花火 *****
//# RNSS2E1 SCENE [FIREWORKS]
//#
static struct reg_value rnss2e1_setting_scene_Fireworks_A[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x64, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x64, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x80, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x70, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x80, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x70, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x80, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x7C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x74, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x7C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x74, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [FIREWORKS]
//#
static struct reg_value rnss2e1_setting_scene_Fireworks_B[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC7, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC7, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x80, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x70, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x80, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x70, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x80, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x7C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x74, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x7C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x74, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [FIREWORKS]
//#
static struct reg_value rnss2e1_setting_scene_Fireworks_C[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x9F, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x9F, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x80, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x70, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x80, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x70, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x80, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x7C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x74, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x7C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x74, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [FIREWORKS]
//#
static struct reg_value rnss2e1_setting_scene_Fireworks_D[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x7A, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x7A, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x80, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x70, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x80, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x70, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x80, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x7C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x74, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x7C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x74, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [FIREWORKS]
//#
static struct reg_value rnss2e1_setting_scene_Fireworks_E[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC2, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC2, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0x80, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x70, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x80, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x70, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x80, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x7C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x74, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x7C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x74, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};



// ***** パーティー *****
//# RNSS2E1 SCENE [PARTY]
//#
static struct reg_value rnss2e1_setting_scene_Party_A[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x64, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x64, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x70, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x80, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x70, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x80, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x7C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x74, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x7C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x74, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0xA1, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0xA1, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x90, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x55, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0xA1, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0xA1, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x90, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x55, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [PARTY]
static struct reg_value rnss2e1_setting_scene_Party_B[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC7, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC7, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x70, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x80, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x70, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x80, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x7C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x74, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x7C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x74, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0xA1, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0xA1, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x90, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x55, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0xA1, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0xA1, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x90, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x55, 0, 0},   //# 2DB sat_v_s4
};
//#

//# RNSS2E1 SCENE [PARTY]
//#
static struct reg_value rnss2e1_setting_scene_Party_C[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x9F, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x9F, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x70, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x80, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x70, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x80, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x7C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x74, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x7C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x74, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0xA1, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0xA1, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x90, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x55, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0xA1, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0xA1, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x90, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x55, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [PARTY]
//#
static struct reg_value rnss2e1_setting_scene_Party_D[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x7A, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x7A, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x70, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x80, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x70, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x80, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x7C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x74, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x7C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x74, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0xA1, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0xA1, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x90, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x55, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0xA1, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0xA1, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x90, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x55, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [PARTY]
//#
static struct reg_value rnss2e1_setting_scene_Party_E[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC2, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC2, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x70, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x80, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x70, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x80, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x7C, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x74, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x7C, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x74, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0xA1, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0xA1, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x90, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x55, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0xA1, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0xA1, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x90, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x55, 0, 0},   //# 2DB sat_v_s4
};


// ***** キャンドルライト *****
//# RNSS2E1 SCENE [CANDLELIGHT]
//#
static struct reg_value rnss2e1_setting_scene_Candle_A[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x64, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x64, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [CANDLELIGHT]
//#
static struct reg_value rnss2e1_setting_scene_Candle_B[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC7, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC7, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [CANDLELIGHT]
//#
static struct reg_value rnss2e1_setting_scene_Candle_C[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x9F, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x9F, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [CANDLELIGHT]
//#
static struct reg_value rnss2e1_setting_scene_Candle_D[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0x7A, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0x7A, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};

//# RNSS2E1 SCENE [CANDLELIGHT]
//#
static struct reg_value rnss2e1_setting_scene_Candle_E[] = {
	{0xFD, 0x02, 0, 0},
	{0xF0, 0xC2, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 ABF_exp_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x07, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x98, 0xC2, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_ourdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x00, 0x9E, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x8E, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xB2, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0xA2, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0x9E, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x8E, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xB2, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0xA2, 0, 0},   //# 323 bgain_bot_dummy
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
//#
	{0xFD, 0x02, 0, 0},
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
};



static struct rnss2e1_reg_info rnss2e1_scene_data[14][5] = {
	//オート
	{
			{// Type A0
#ifdef DEBUG
				(rnss2e1_scene_mode_auto * 10 ) + 0,
#endif
				rnss2e1_setting_scene_Auto_A,
				ARRAY_SIZE(rnss2e1_setting_scene_Auto_A)
			},
			{// Type B
#ifdef DEBUG
				(rnss2e1_scene_mode_auto * 10 ) + 1,
#endif
				rnss2e1_setting_scene_Auto_B,
				ARRAY_SIZE(rnss2e1_setting_scene_Auto_B)
			},
			{// Type C
#ifdef DEBUG
				(rnss2e1_scene_mode_auto * 10 ) + 2,
#endif
				rnss2e1_setting_scene_Auto_C,
				ARRAY_SIZE(rnss2e1_setting_scene_Auto_C)
			},
			{// Type D
#ifdef DEBUG
				(rnss2e1_scene_mode_auto * 10 ) + 3,
#endif
				rnss2e1_setting_scene_Auto_D,
				ARRAY_SIZE(rnss2e1_setting_scene_Auto_D)
			},
			{// Type E
#ifdef DEBUG
				(rnss2e1_scene_mode_auto * 10 ) + 4,
#endif
				rnss2e1_setting_scene_Auto_E,
				ARRAY_SIZE(rnss2e1_setting_scene_Auto_E)
			},
	},
	//スポーツ
	{
			{// Type A0
#ifdef DEBUG
				(rnss2e1_scene_mode_sports * 10 ) + 0,
#endif
				rnss2e1_setting_scene_Sport_A,
				ARRAY_SIZE(rnss2e1_setting_scene_Sport_A)
			},
			{// Type B
#ifdef DEBUG
				(rnss2e1_scene_mode_sports * 10 ) + 1,
#endif
				rnss2e1_setting_scene_Sport_B,
				ARRAY_SIZE(rnss2e1_setting_scene_Sport_B)
			},
			{// Type C
#ifdef DEBUG
				(rnss2e1_scene_mode_sports * 10 ) + 2,
#endif
				rnss2e1_setting_scene_Sport_C,
				ARRAY_SIZE(rnss2e1_setting_scene_Sport_C)
			},
			{// Type D
#ifdef DEBUG
				(rnss2e1_scene_mode_sports * 10 ) + 3,
#endif
				rnss2e1_setting_scene_Sport_D,
				ARRAY_SIZE(rnss2e1_setting_scene_Sport_D)
			},
			{// Type E
#ifdef DEBUG
				(rnss2e1_scene_mode_sports * 10 ) + 4,
#endif
				rnss2e1_setting_scene_Sport_E,
				ARRAY_SIZE(rnss2e1_setting_scene_Sport_E)
			},
	},
	//ポートレイト
	{
			{// Type A0
#ifdef DEBUG
				(rnss2e1_scene_mode_portrait * 10 ) + 0,
#endif
				rnss2e1_setting_scene_Portrait_A,
				ARRAY_SIZE(rnss2e1_setting_scene_Portrait_A)
			},
			{// Type B
#ifdef DEBUG
				(rnss2e1_scene_mode_portrait * 10 ) + 1,
#endif
				rnss2e1_setting_scene_Portrait_B,
				ARRAY_SIZE(rnss2e1_setting_scene_Portrait_B)
			},
			{// Type C
#ifdef DEBUG
				(rnss2e1_scene_mode_portrait * 10 ) + 2,
#endif
				rnss2e1_setting_scene_Portrait_C,
				ARRAY_SIZE(rnss2e1_setting_scene_Portrait_C)
			},
			{// Type D
#ifdef DEBUG
				(rnss2e1_scene_mode_portrait * 10 ) + 3,
#endif
				rnss2e1_setting_scene_Portrait_D,
				ARRAY_SIZE(rnss2e1_setting_scene_Portrait_D)
			},
			{// Type E
#ifdef DEBUG
				(rnss2e1_scene_mode_portrait * 10 ) + 4,
#endif
				rnss2e1_setting_scene_Portrait_E,
				ARRAY_SIZE(rnss2e1_setting_scene_Portrait_E)
			},
	},
	//風景
	{
			{// Type A0
#ifdef DEBUG
				(rnss2e1_scene_mode_landscape * 10) + 0,
#endif
				rnss2e1_setting_scene_Landscape_A,
				ARRAY_SIZE(rnss2e1_setting_scene_Landscape_A)
			},
			{// Type B
#ifdef DEBUG
				(rnss2e1_scene_mode_landscape * 10 ) + 1,
#endif
				rnss2e1_setting_scene_Landscape_B,
				ARRAY_SIZE(rnss2e1_setting_scene_Landscape_B)
			},
			{// Type C
#ifdef DEBUG
				(rnss2e1_scene_mode_landscape * 10 ) + 2,
#endif
				rnss2e1_setting_scene_Landscape_C,
				ARRAY_SIZE(rnss2e1_setting_scene_Landscape_C)
			},
			{// Type D
#ifdef DEBUG
				(rnss2e1_scene_mode_landscape * 10 ) + 3,
#endif
				rnss2e1_setting_scene_Landscape_D,
				ARRAY_SIZE(rnss2e1_setting_scene_Landscape_D)
			},
			{// Type E
#ifdef DEBUG
				(rnss2e1_scene_mode_landscape * 10 ) + 4,
#endif
				rnss2e1_setting_scene_Landscape_E,
				ARRAY_SIZE(rnss2e1_setting_scene_Landscape_E)
			},
	},
	//夜景
	{
			{// Type A0
#ifdef DEBUG
				(rnss2e1_scene_mode_naightportrait * 10 ) + 0,
#endif
				rnss2e1_setting_scene_Night_A,
				ARRAY_SIZE(rnss2e1_setting_scene_Night_A)
			},
			{// Type B
#ifdef DEBUG
				(rnss2e1_scene_mode_naightportrait * 10 ) + 1,
#endif
				rnss2e1_setting_scene_Night_B,
				ARRAY_SIZE(rnss2e1_setting_scene_Night_B)
			},
			{// Type C
#ifdef DEBUG
				(rnss2e1_scene_mode_naightportrait * 10 ) + 2,
#endif
				rnss2e1_setting_scene_Night_C,
				ARRAY_SIZE(rnss2e1_setting_scene_Night_C)
			},
			{// Type D
#ifdef DEBUG
				(rnss2e1_scene_mode_naightportrait * 10 ) + 3,
#endif
				rnss2e1_setting_scene_Night_D,
				ARRAY_SIZE(rnss2e1_setting_scene_Night_D)
			},
			{// Type E
#ifdef DEBUG
				(rnss2e1_scene_mode_naightportrait * 10 ) + 4,
#endif
				rnss2e1_setting_scene_Night_E,
				ARRAY_SIZE(rnss2e1_setting_scene_Night_E)
			},
	},
	//ナイトスナップ
	{
			{// Type A0
#ifdef DEBUG
				(rnss2e1_scene_mode_night * 10 ) + 0,
#endif
				rnss2e1_setting_scene_NightSnap_A,
				ARRAY_SIZE(rnss2e1_setting_scene_NightSnap_A)
			},
			{// Type B
#ifdef DEBUG
				(rnss2e1_scene_mode_night * 10 ) + 1,
#endif
				rnss2e1_setting_scene_NightSnap_B,
				ARRAY_SIZE(rnss2e1_setting_scene_NightSnap_B)
			},
			{// Type C
#ifdef DEBUG
				(rnss2e1_scene_mode_night * 10 ) + 2,
#endif
				rnss2e1_setting_scene_NightSnap_C,
				ARRAY_SIZE(rnss2e1_setting_scene_NightSnap_C)
			},
			{// Type D
#ifdef DEBUG
				(rnss2e1_scene_mode_night * 10 ) + 3,
#endif
				rnss2e1_setting_scene_NightSnap_D,
				ARRAY_SIZE(rnss2e1_setting_scene_NightSnap_D)
			},
			{// Type E
#ifdef DEBUG
				(rnss2e1_scene_mode_night * 10 ) + 4,
#endif
				rnss2e1_setting_scene_NightSnap_E,
				ARRAY_SIZE(rnss2e1_setting_scene_NightSnap_E)
			},
	},
	//シアター
	{
			{// Type A0
#ifdef DEBUG
				(rnss2e1_scene_mode_theatre * 10 ) + 0,
#endif
				rnss2e1_setting_scene_Theater_A,
				ARRAY_SIZE(rnss2e1_setting_scene_Theater_A)
			},
			{// Type B
#ifdef DEBUG
				(rnss2e1_scene_mode_theatre * 10 ) + 1,
#endif
				rnss2e1_setting_scene_Theater_B,
				ARRAY_SIZE(rnss2e1_setting_scene_Theater_B)
			},
			{// Type C
#ifdef DEBUG
				(rnss2e1_scene_mode_theatre * 10 ) + 2,
#endif
				rnss2e1_setting_scene_Theater_C,
				ARRAY_SIZE(rnss2e1_setting_scene_Theater_C)
			},
			{// Type D
#ifdef DEBUG
				(rnss2e1_scene_mode_theatre * 10 ) + 3,
#endif
				rnss2e1_setting_scene_Theater_D,
				ARRAY_SIZE(rnss2e1_setting_scene_Theater_D)
			},
			{// Type E
#ifdef DEBUG
				(rnss2e1_scene_mode_theatre * 10 ) + 4,
#endif
				rnss2e1_setting_scene_Theater_E,
				ARRAY_SIZE(rnss2e1_setting_scene_Theater_E)
			},
	},
	//ビーチ
	{
			{// Type A0
#ifdef DEBUG
				(rnss2e1_scene_mode_beach * 10 ) + 0,
#endif
				rnss2e1_setting_scene_Beach_A,
				ARRAY_SIZE(rnss2e1_setting_scene_Beach_A)
			},
			{// Type B
#ifdef DEBUG
				(rnss2e1_scene_mode_beach * 10 ) + 1,
#endif
				rnss2e1_setting_scene_Beach_B,
				ARRAY_SIZE(rnss2e1_setting_scene_Beach_B)
			},
			{// Type C
#ifdef DEBUG
				(rnss2e1_scene_mode_beach * 10 ) + 2,
#endif
				rnss2e1_setting_scene_Beach_C,
				ARRAY_SIZE(rnss2e1_setting_scene_Beach_C)
			},
			{// Type D
#ifdef DEBUG
				(rnss2e1_scene_mode_beach * 10 ) + 3,
#endif
				rnss2e1_setting_scene_Beach_D,
				ARRAY_SIZE(rnss2e1_setting_scene_Beach_D)
			},
			{// Type E
#ifdef DEBUG
				(rnss2e1_scene_mode_beach * 10 ) + 4,
#endif
				rnss2e1_setting_scene_Beach_E,
				ARRAY_SIZE(rnss2e1_setting_scene_Beach_E)
			},
	},
	//スノー
	{
			{// Type A0
#ifdef DEBUG
				(rnss2e1_scene_mode_snow * 10 ) + 0,
#endif
				rnss2e1_setting_scene_Snow_A,
				ARRAY_SIZE(rnss2e1_setting_scene_Snow_A)
			},
			{// Type B
#ifdef DEBUG
				(rnss2e1_scene_mode_snow * 10 ) + 1,
#endif
				rnss2e1_setting_scene_Snow_B,
				ARRAY_SIZE(rnss2e1_setting_scene_Snow_B)
			},
			{// Type C
#ifdef DEBUG
				(rnss2e1_scene_mode_snow * 10 ) + 2,
#endif
				rnss2e1_setting_scene_Snow_C,
				ARRAY_SIZE(rnss2e1_setting_scene_Snow_C)
			},
			{// Type D
#ifdef DEBUG
				(rnss2e1_scene_mode_snow * 10 ) + 3,
#endif
				rnss2e1_setting_scene_Snow_D,
				ARRAY_SIZE(rnss2e1_setting_scene_Snow_D)
			},
			{// Type E
#ifdef DEBUG
				(rnss2e1_scene_mode_snow * 10 ) + 4,
#endif
				rnss2e1_setting_scene_Snow_E,
				ARRAY_SIZE(rnss2e1_setting_scene_Snow_E)
			},
	},
	//夕焼け
	{
			{// Type A0
#ifdef DEBUG
				(rnss2e1_scene_mode_sunset * 10 ) + 0,
#endif
				rnss2e1_setting_scene_Sunset_A,
				ARRAY_SIZE(rnss2e1_setting_scene_Sunset_A)
			},
			{// Type B
#ifdef DEBUG
				(rnss2e1_scene_mode_sunset * 10 ) + 1,
#endif
				rnss2e1_setting_scene_Sunset_B,
				ARRAY_SIZE(rnss2e1_setting_scene_Sunset_B)
			},
			{// Type C
#ifdef DEBUG
				(rnss2e1_scene_mode_sunset * 10 ) + 2,
#endif
				rnss2e1_setting_scene_Sunset_C,
				ARRAY_SIZE(rnss2e1_setting_scene_Sunset_C)
			},
			{// Type D
#ifdef DEBUG
				(rnss2e1_scene_mode_sunset * 10 ) + 3,
#endif
				rnss2e1_setting_scene_Sunset_D,
				ARRAY_SIZE(rnss2e1_setting_scene_Sunset_D)
			},
			{// Type E
#ifdef DEBUG
				(rnss2e1_scene_mode_sunset * 10 ) + 4,
#endif
				rnss2e1_setting_scene_Sunset_E,
				ARRAY_SIZE(rnss2e1_setting_scene_Sunset_E)
			},
	},
	//手振れ補正
	{
			{// Type A0
#ifdef DEBUG
				(rnss2e1_scene_mode_steadyphoto * 10 ) + 0,
#endif
				rnss2e1_setting_scene_Action_A,
				ARRAY_SIZE(rnss2e1_setting_scene_Action_A)
			},
			{// Type B
#ifdef DEBUG
				(rnss2e1_scene_mode_steadyphoto * 10 ) + 1,
#endif
				rnss2e1_setting_scene_Action_B,
				ARRAY_SIZE(rnss2e1_setting_scene_Action_B)
			},
			{// Type C
#ifdef DEBUG
				(rnss2e1_scene_mode_steadyphoto * 10 ) + 2,
#endif
				rnss2e1_setting_scene_Action_C,
				ARRAY_SIZE(rnss2e1_setting_scene_Action_C)
			},
			{// Type D
#ifdef DEBUG
				(rnss2e1_scene_mode_steadyphoto * 10 ) + 3,
#endif
				rnss2e1_setting_scene_Action_D,
				ARRAY_SIZE(rnss2e1_setting_scene_Action_D)
			},
			{// Type E
#ifdef DEBUG
				(rnss2e1_scene_mode_steadyphoto * 10 ) + 4,
#endif
				rnss2e1_setting_scene_Action_E,
				ARRAY_SIZE(rnss2e1_setting_scene_Action_E)
			},
	},
	//花火
	{
			{// Type A0
#ifdef DEBUG
				(rnss2e1_scene_mode_fireworks * 10 ) + 0,
#endif
				rnss2e1_setting_scene_Fireworks_A,
				ARRAY_SIZE(rnss2e1_setting_scene_Fireworks_A)
			},
			{// Type B
#ifdef DEBUG
				(rnss2e1_scene_mode_fireworks * 10 ) + 1,
#endif
				rnss2e1_setting_scene_Fireworks_B,
				ARRAY_SIZE(rnss2e1_setting_scene_Fireworks_B)
			},
			{// Type C
#ifdef DEBUG
				(rnss2e1_scene_mode_fireworks * 10 ) + 2,
#endif
				rnss2e1_setting_scene_Fireworks_C,
				ARRAY_SIZE(rnss2e1_setting_scene_Fireworks_C)
			},
			{// Type D
#ifdef DEBUG
				(rnss2e1_scene_mode_fireworks * 10 ) + 3,
#endif
				rnss2e1_setting_scene_Fireworks_D,
				ARRAY_SIZE(rnss2e1_setting_scene_Fireworks_D)
			},
			{// Type E
#ifdef DEBUG
				(rnss2e1_scene_mode_fireworks * 10 ) + 4,
#endif
				rnss2e1_setting_scene_Fireworks_E,
				ARRAY_SIZE(rnss2e1_setting_scene_Fireworks_E)
			},
	},
	//パーティ
	{
			{// Type A0
#ifdef DEBUG
				(rnss2e1_scene_mode_patry * 10 ) + 0,
#endif
				rnss2e1_setting_scene_Party_A,
				ARRAY_SIZE(rnss2e1_setting_scene_Party_A)
			},
			{// Type B
#ifdef DEBUG
				(rnss2e1_scene_mode_patry * 10 ) + 1,
#endif
				rnss2e1_setting_scene_Party_B,
				ARRAY_SIZE(rnss2e1_setting_scene_Party_B)
			},
			{// Type C
#ifdef DEBUG
				(rnss2e1_scene_mode_patry * 10 ) + 2,
#endif
				rnss2e1_setting_scene_Party_C,
				ARRAY_SIZE(rnss2e1_setting_scene_Party_C)
			},
			{// Type D
#ifdef DEBUG
				(rnss2e1_scene_mode_patry * 10 ) + 3,
#endif
				rnss2e1_setting_scene_Party_D,
				ARRAY_SIZE(rnss2e1_setting_scene_Party_D)
			},
			{// Type E
#ifdef DEBUG
				(rnss2e1_scene_mode_patry * 10 ) + 4,
#endif
				rnss2e1_setting_scene_Party_E,
				ARRAY_SIZE(rnss2e1_setting_scene_Party_E)
			},
	},
	//キャンドル
	{
			{// Type A0
#ifdef DEBUG
				(rnss2e1_scene_mode_candlelight * 10 ) + 0,
#endif
				rnss2e1_setting_scene_Candle_A,
				ARRAY_SIZE(rnss2e1_setting_scene_Candle_A)
			},
			{// Type B
#ifdef DEBUG
				(rnss2e1_scene_mode_candlelight * 10 ) + 1,
#endif
				rnss2e1_setting_scene_Candle_B,
				ARRAY_SIZE(rnss2e1_setting_scene_Candle_B)
			},
			{// Type C
#ifdef DEBUG
				(rnss2e1_scene_mode_candlelight * 10 ) + 2,
#endif
				rnss2e1_setting_scene_Candle_C,
				ARRAY_SIZE(rnss2e1_setting_scene_Candle_C)
			},
			{// Type D
#ifdef DEBUG
				(rnss2e1_scene_mode_candlelight * 10 ) + 3,
#endif
				rnss2e1_setting_scene_Candle_D,
				ARRAY_SIZE(rnss2e1_setting_scene_Candle_D)
			},
			{// Type E
#ifdef DEBUG
				(rnss2e1_scene_mode_candlelight * 10 ) + 4,
#endif
				rnss2e1_setting_scene_Candle_E,
				ARRAY_SIZE(rnss2e1_setting_scene_Candle_E)
			},
	}
};

//---- Zoom設定
//# RNSS2E1 SCALE QVGA x1
//#
static struct reg_value rnss2e1_Zoom_QVGA_x100[] = {
	{0xFD, 0x03, 0, 0},
	{0x06, 0x00, 0, 0},   //# 306 ratio_row[9:8]
	{0x07, 0x50, 0, 0},   //# 307 ratio_row[7:0]
	{0x08, 0x00, 0, 0},   //# 308 ratio_col[9:8]
	{0x09, 0x50, 0, 0},   //# 308 ratio_col[7:0]
	{0x0E, 0x01, 0, 0},   //# 30E resize_en

	{0xFD, 0x02, 0, 0},
	{0x47, 0x00, 0, 0},   //# 247 v_start_3msb
	{0x48, 0x00, 0, 0},   //# 248 v_start_8lsb
	{0x49, 0x02, 0, 0},   //# 249 v_size_3msb
	{0x4A, 0x58, 0, 0},   //# 24A v_size_8lsb
	{0x4B, 0x00, 0, 0},   //# 24B h_start_3msb
	{0x4C, 0x00, 0, 0},   //# 24C h_start_8lsb
	{0x4D, 0x03, 0, 0},   //# 24D h_size_3msb
	{0x4E, 0x20, 0, 0},   //# 24E h_size_8lsb
};

//# RNSS2E1 SCALE QVGA x1.25
//#
static struct reg_value rnss2e1_Zoom_QVGA_x125[] = {
	{0xFD, 0x03, 0, 0},
	{0x06, 0x00, 0, 0},   //# 306 ratio_row[9:8]
	{0x07, 0x40, 0, 0},   //# 307 ratio_row[7:0]
	{0x08, 0x00, 0, 0},   //# 308 ratio_col[9:8]
	{0x09, 0x40, 0, 0},   //# 309 ratio_col[7:0]
	{0x0E, 0x01, 0, 0},   //# 30E resize_en

	{0xFD, 0x02, 0, 0},
	{0x47, 0x00, 0, 0},   //# 247 v_start_3msb
	{0x48, 0x3C, 0, 0},   //# 248 v_start_8lsb
	{0x49, 0x01, 0, 0},   //# 249 v_size_3msb
	{0x4A, 0xE0, 0, 0},   //# 24A v_size_8lsb
	{0x4B, 0x00, 0, 0},   //# 24B h_start_3msb
	{0x4C, 0x50, 0, 0},   //# 24C h_start_8lsb
	{0x4D, 0x02, 0, 0},   //# 24D h_size_3msb
	{0x4E, 0x80, 0, 0},   //# 24E h_size_8lsb
};

//# RNSS2E1 SCALE QVGA x1.5
//#
static struct reg_value rnss2e1_Zoom_QVGA_x150[] = {
	{0xFD, 0x03, 0, 0},
	{0x06, 0x00, 0, 0},   //# 106 ratio_row[9:8]
	{0x07, 0x35, 0, 0},   //# 107 ratio_row[7:0]
	{0x08, 0x00, 0, 0},   //# 108 ratio_col[9:8]
	{0x09, 0x35, 0, 0},   //# 109 ratio_col[7:0]
	{0x0E, 0x01, 0, 0},   //# 10E resize_en

	{0xFD, 0x02, 0, 0},
	{0x47, 0x00, 0, 0},   //# 047 v_start_3msb
	{0x48, 0x65, 0, 0},   //# 048 v_start_8lsb
	{0x49, 0x01, 0, 0},   //# 049 v_size_3msb
	{0x4A, 0x8D, 0, 0},   //# 04A v_size_8lsb
	{0x4B, 0x00, 0, 0},   //# 04B h_start_3msb
	{0x4C, 0x87, 0, 0},   //# 04C h_start_8lsb
	{0x4D, 0x02, 0, 0},   //# 04D h_size_3msb
	{0x4E, 0x12, 0, 0},   //# 04E h_size_8lsb
};

//# RNSS2E1 SCALE QVGA x2.0
//#
static struct reg_value rnss2e1_Zoom_QVGA_x200[] = {
	{0xFD, 0x03, 0, 0},
	{0x06, 0x00, 0, 0},   //# 106 ratio_row[9:8]
	{0x07, 0x28, 0, 0},   //# 107 ratio_row[7:0]
	{0x08, 0x00, 0, 0},   //# 108 ratio_col[9:8]
	{0x09, 0x28, 0, 0},   //# 109 ratio_col[7:0]
	{0x0E, 0x01, 0, 0},   //# 10E resize_en

	{0xFD, 0x02, 0, 0},
	{0x47, 0x00, 0, 0},   //# 047 v_start_3msb
	{0x48, 0x96, 0, 0},   //# 048 v_start_8lsb
	{0x49, 0x01, 0, 0},   //# 049 v_size_3msb
	{0x4A, 0x2C, 0, 0},   //# 04A v_size_8lsb
	{0x4B, 0x00, 0, 0},   //# 04B h_start_3msb
	{0x4C, 0xC8, 0, 0},   //# 04C h_start_8lsb
	{0x4D, 0x01, 0, 0},   //# 04D h_size_3msb
	{0x4E, 0x90, 0, 0},   //# 04E h_size_8lsb

};

//# RNSS2E1 SCALE QVGA x2.5 -> 2.42
//#
static struct reg_value rnss2e1_Zoom_QVGA_x250[] = {
	{0xFD, 0x03, 0, 0},
	{0x06, 0x00, 0, 0},   //# 106 ratio_row[9:8]
	{0x07, 0x21, 0, 0},   //# 107 ratio_row[7:0]
	{0x08, 0x00, 0, 0},   //# 108 ratio_col[9:8]
	{0x09, 0x21, 0, 0},   //# 109 ratio_col[7:0]
	{0x0E, 0x01, 0, 0},   //# 10E resize_en

	{0xFD, 0x02, 0, 0},
	{0x47, 0x00, 0, 0},   //# 047 v_start_3msb
	{0x48, 0xB0, 0, 0},   //# 048 v_start_8lsb
	{0x49, 0x00, 0, 0},   //# 049 v_size_3msb
	{0x4A, 0xF7, 0, 0},   //# 04A v_size_8lsb
	{0x4B, 0x00, 0, 0},   //# 04B h_start_3msb
	{0x4C, 0xEB, 0, 0},   //# 04C h_start_8lsb
	{0x4D, 0x01, 0, 0},   //# 04D h_size_3msb
	{0x4E, 0x4A, 0, 0},   //# 04E h_size_8lsb
};

//# RNSS2E1 SCALE VGA x1.0
//#
static struct reg_value rnss2e1_Zoom_VGA_x100[] = {
	{0xFD, 0x03, 0, 0},
	{0x06, 0x00, 0, 0},   //# 306 ratio_row[9:8]
	{0x07, 0x28, 0, 0},   //# 307 ratio_row[7:0]
	{0x08, 0x00, 0, 0},   //# 308 ratio_col[9:8]
	{0x09, 0x28, 0, 0},   //# 309 ratio_col[7:0]
	{0x0E, 0x01, 0, 0},   //# 30E resize_en

	{0xFD, 0x02, 0, 0},
	{0x47, 0x00, 0, 0},   //# 247 v_start_3msb
	{0x48, 0x00, 0, 0},   //# 248 v_start_8lsb
	{0x49, 0x02, 0, 0},   //# 249 v_size_3msb
	{0x4A, 0x58, 0, 0},   //# 24A v_size_8lsb
	{0x4B, 0x00, 0, 0},   //# 24B h_start_3msb
	{0x4C, 0x00, 0, 0},   //# 24C h_start_8lsb
	{0x4D, 0x03, 0, 0},   //# 24D h_size_3msb
	{0x4E, 0x20, 0, 0},   //# 24E h_size_8lsb
};

//# RNSS2E1 SCALE VGA x1.25 -> 1.21
//#
static struct reg_value rnss2e1_Zoom_VGA_x125[] = {
	{0xFD, 0x03, 0, 0},
	{0x06, 0x00, 0, 0},   //# 306 ratio_row[9:8]
	{0x07, 0x21, 0, 0},   //# 307 ratio_row[7:0]
	{0x08, 0x00, 0, 0},   //# 308 ratio_col[9:8]
	{0x09, 0x21, 0, 0},   //# 309 ratio_col[7:0]
	{0x0E, 0x01, 0, 0},   //# 30E resize_en

	{0xFD, 0x02, 0, 0},
	{0x47, 0x00, 0, 0},   //# 247 v_start_3msb
	{0x48, 0x34, 0, 0},   //# 248 v_start_8lsb
	{0x49, 0x01, 0, 0},   //# 249 v_size_3msb
	{0x4A, 0xEF, 0, 0},   //# 24A v_size_8lsb
	{0x4B, 0x00, 0, 0},   //# 24B h_start_3msb
	{0x4C, 0x46, 0, 0},   //# 24C h_start_8lsb
	{0x4D, 0x02, 0, 0},   //# 24D h_size_3msb
	{0x4E, 0x94, 0, 0},   //# 24E h_size_8lsb
};

static struct rnss2e1_reg_info rnss2e1_zoom_data[6][5] = {
	//QVGA
	{
		{// x1.0
#ifdef DEBUG
			0x00,
#endif
			rnss2e1_Zoom_QVGA_x100,
			ARRAY_SIZE(rnss2e1_Zoom_QVGA_x100)
		},
		{// x1.25
#ifdef DEBUG
			0x01,
#endif
			rnss2e1_Zoom_QVGA_x125,
			ARRAY_SIZE(rnss2e1_Zoom_QVGA_x125)
		},
		{// x1.50
#ifdef DEBUG
			0x02,
#endif
			rnss2e1_Zoom_QVGA_x150,
			ARRAY_SIZE(rnss2e1_Zoom_QVGA_x150)
		},
		{// x2.0
#ifdef DEBUG
			0x03,
#endif
			rnss2e1_Zoom_QVGA_x200,
			ARRAY_SIZE(rnss2e1_Zoom_QVGA_x200)
		},
		{// x2.5
#ifdef DEBUG
			0x04,
#endif
			rnss2e1_Zoom_QVGA_x250,
			ARRAY_SIZE(rnss2e1_Zoom_QVGA_x250)
		},
	},

	//VGA
	{
		{// x1.0
#ifdef DEBUG
			0x10,
#endif
			rnss2e1_Zoom_VGA_x100,
			ARRAY_SIZE(rnss2e1_Zoom_VGA_x100)
		},
		{// x1.25
#ifdef DEBUG
			0x11,
#endif
			rnss2e1_Zoom_VGA_x125,
			ARRAY_SIZE(rnss2e1_Zoom_VGA_x125)
		},
		{// x1.50
#ifdef DEBUG
			0x12,
#endif
			0x00,0
		},
		{// x2.0
#ifdef DEBUG
			0x13,
#endif
			0x00,0
		},
		{// x2.5
#ifdef DEBUG
			0x14,
#endif
			0x00,0
		},
	},

	//SVGA
	{
		{// x1.0
#ifdef DEBUG
			0x20,
#endif
			0x00,0
		},
		{// x1.25
#ifdef DEBUG
			0x21,
#endif
			0x00,0
		},
		{// x1.50
#ifdef DEBUG
			0x22,
#endif
			0x00,0
		},
		{// x2.0
#ifdef DEBUG
			0x23,
#endif
			0x00,0
		},
		{// x2.5
#ifdef DEBUG
			0x24,
#endif
			0x00,0
		},
	},

	//XGA
	{
		{// x1.0
#ifdef DEBUG
			0x30,
#endif
			0x00,0
		},
		{// x1.25
#ifdef DEBUG
			0x31,
#endif
			0x00,0
		},
		{// x1.50
#ifdef DEBUG
			0x32,
#endif
			0x00,0
		},
		{// x2.0
#ifdef DEBUG
			0x33,
#endif
			0x00,0
		},
		{// x2.5
#ifdef DEBUG
			0x34,
#endif
			0x00,0
		},
	},

	//HD
	{
		{// x1.0
#ifdef DEBUG
			0x40,
#endif
			0x00,0
		},
		{// x1.25
#ifdef DEBUG
			0x41,
#endif
			0x00,0
		},
		{// x1.50
#ifdef DEBUG
			0x42,
#endif
			0x00,0
		},
		{// x2.0
#ifdef DEBUG
			0x43,
#endif
			0x00,0
		},
		{// x2.5
#ifdef DEBUG
			0x44,
#endif
			0x00,0
		},
	},

	//UVGA
	{
		{// x1.0
#ifdef DEBUG
			0x50,
#endif
			0x00,0
		},
		{// x1.25
#ifdef DEBUG
			0x51,
#endif
			0x00,0
		},
		{// x1.50
#ifdef DEBUG
			0x52,
#endif
			0x00,0
		},
		{// x2.0
#ifdef DEBUG
			0x53,
#endif
			0x00,0
		},
		{// x2.5
#ifdef DEBUG
			0x54,
#endif
			0x00,0
		},
	},
};


//----- QVGA -------
static struct reg_value rnss2e1_setting_15fps_QVGA_320_240[] = {
	{0xFD, 0x02, 0, 0},
	{0x36, 0x00, 0, 0},   //# 236 buf_outmode2
//#
	{0xFD, 0x00, 0, 0},
	{0x10, 0x3F, 0, 0},   //# 010 clk_mode
	{0x11, 0x40, 0, 0},   //# 011 pclk_inv,pclk_gate_en,pclk_ctrl,isp_clk_ctrl
	{0x20, 0x02, 0, 0},   //# 020 ds_data,out_end_high8,out_end_low2,out_ens
	{0x21, 0x03, 0, 0},   //# 021 pe_hvp,pe_data,ds_s,buf_dis_s,buf_dis_d
//#
	{0xFD, 0x01, 0, 0},
//	{0x03, 0x00, 0, 0},   //# 103 buf_exp_5msb
//	{0x04, 0x0C, 0, 0},   //# 104 buf_exp_8lsb
	{0x03, 0x01, 0, 0},   //# 103 buf_exp_5msb(1002)
	{0x04, 0x2C, 0, 0},   //# 104 buf_exp_8lsb(1002)
	{0x09, 0x00, 0, 0},   //# 109 hblank_4msb
	{0x0A, 0x4E, 0, 0},   //# 10A hblank_8lsb
//#
	{0xFD, 0x00, 0, 0},
	{0x0E, 0x40, 0, 0},   //# 00E pd
//#
	{0xFD, 0x01, 0, 0},
	{0x0E, 0x00, 0, 0},   //# 10E p0
	{0x0F, 0x18, 0, 0},   //# 10F p1
	{0x10, 0x10, 0, 0},   //# 110 p2
	{0x11, 0x03, 0, 0},   //# 111 p3
	{0x12, 0x18, 0, 0},   //# 112 p4
	{0x13, 0x10, 0, 0},   //# 113 p5
	{0x14, 0x15, 0, 0},   //# 114 p6
	{0x15, 0x01, 0, 0},   //# 115 p7
	{0x16, 0x02, 0, 0},   //# 116 p8
	{0x17, 0x10, 0, 0},   //# 117 p9
	{0x18, 0x00, 0, 0},   //# 118 p10_2msb
	{0x19, 0x1A, 0, 0},   //# 119 p10_8lsb
	{0x1A, 0x00, 0, 0},   //# 11A p11_2msb
	{0x1B, 0x1C, 0, 0},   //# 11B p11_8lsb
	{0x50, 0x00, 0, 0},   //# 150 p12_2msb
	{0x51, 0x1D, 0, 0},   //# 151 p12_8lsb
	{0x52, 0x15, 0, 0},   //# 152 P13
	{0x2A, 0x02, 0, 0},   //# 12A p16
	{0x53, 0x00, 0, 0},   //# 153 p17_2msb
	{0x54, 0x11, 0, 0},   //# 154 p17_8lsb
	{0x55, 0x12, 0, 0},   //# 155 p18
	{0x56, 0x02, 0, 0},   //# 156 p19
	{0x57, 0x02, 0, 0},   //# 157 p20
	{0x58, 0x00, 0, 0},   //# 158 p21
//#
	{0xFD, 0x00, 0, 0},
	{0x12, 0x04, 0, 0},   //# 012 pll_bias_ctl,pll_delay
	{0x13, 0x04, 0, 0},   //# 013 mipi_pattern_en,pll_test_en,mipi_en
	{0x14, 0x00, 0, 0},   //# 014 pclk_gate,timer_clk_gate,dclk_gate
	{0x15, 0x00, 0, 0},   //# 015 pclk_pha_adj
//#
	{0xFD, 0x01, 0, 0},
//	{0x1C, 0x5C, 0, 0},   //# 11C two_timing_en,FPN_33ms_X,pwd_asp_timing_sel,Channel-timing
	{0x1C, 0x7C, 0, 0},   //# 11C two_timing_en,FPN_33ms_X,pwd_asp_timing_sel,Channel-timing
	{0x21, 0x44, 0, 0},   //# 121 adc_vcm_opin_ctl,adc_vcm_opin_c,col_clk_delay
	{0x22, 0x04, 0, 0},   //# 122 pga_bias_ctl,col_ctrl
	{0x25, 0x00, 0, 0},   //# 125 adc_range_ctl,adc_vcm_ctl,asp_delay
	{0x26, 0x26, 0, 0},   //# 126 adc_dig_offset,sw_delay
	{0x27, 0x6D, 0, 0},   //# 127 delay,black_en,adc_dref_cal,adc_g2x_en,adc_offset_en
	{0x2B, 0x66, 0, 0},   //# 12B adc_offset_ctl_buf_up,adc_offset_ctl_buf_dn
	{0x2C, 0x3F, 0, 0},   //# 12C strobe_en,bl_da
	{0x2D, 0x40, 0, 0},   //# 12D adc_bias_stage,adc_bias_vref
	{0x2E, 0x0D, 0, 0},   //# 12E dout_sel,strobe_sel
//	{0x40, 0xF0, 0, 0},   //# 140 vfpn_bpc_en,vfpn_minus_en
	{0x40, 0xF3, 0, 0},   //# 140 vfpn_bpc_en,vfpn_minus_en
	{0x41, 0x60, 0, 0},   //# 141 vfpn_bpc_th_x1
	{0x42, 0x50, 0, 0},   //# 142 vfpn_bpc_th_x2
	{0x43, 0x28, 0, 0},   //# 143 vfpn_bpc_in_x1
	{0x44, 0x28, 0, 0},   //# 144 vfpn_bpc_in_x2
//	{0x45, 0x0C, 0, 0},   //# 145 vfpn_delta
//	{0x45, 0x06, 0, 0},   //# 145 vfpn_delta(0830)
	{0x45, 0x00, 0, 0},   //# 145 vfpn_delta(0921)
	{0x31, 0x14, 0, 0},   //# 131 buf_comm_ctrl
//#
	{0xFD, 0x02, 0, 0},
	{0x35, 0x40, 0, 0},   //# 235 buf_outmode1
	{0x31, 0x10, 0, 0},   //# 231 digital_gain
	{0x47, 0x00, 0, 0},   //# 247 v_start_3msb
	{0x48, 0x00, 0, 0},   //# 248 v_start_8lsb
	{0x49, 0x02, 0, 0},   //# 249 v_size_3msb
	{0x4A, 0x58, 0, 0},   //# 24A v_size_8lsb
	{0x4B, 0x00, 0, 0},   //# 24B h_start_3msb
	{0x4C, 0x00, 0, 0},   //# 24C h_start_8lsb
	{0x4D, 0x03, 0, 0},   //# 24D h_size_3msb
	{0x4E, 0x20, 0, 0},   //# 24E h_size_8lsb
//	{0x65, 0x08, 0, 0},   //# 265 blue_suboffset
//	{0x66, 0x06, 0, 0},   //# 266 red_suboffset
//	{0x67, 0x07, 0, 0},   //# 267 gr_suboffset
//	{0x68, 0x07, 0, 0},   //# 268 gb_suboffset
//	{0x65, 0x09, 0, 0},   //# 265 blue_suboffset(0830)
//	{0x66, 0x07, 0, 0},   //# 266 red_suboffset(0830)
//	{0x67, 0x08, 0, 0},   //# 267 gr_suboffset(0830)
//	{0x68, 0x08, 0, 0},   //# 268 gb_suboffset(0830)
	{0x65, 0x0F, 0, 0},   //# 265 blue_suboffset(0921)
	{0x66, 0x0D, 0, 0},   //# 266 red_suboffset(0921)
	{0x67, 0x0E, 0, 0},   //# 267 gr_suboffset(0921)
	{0x68, 0x0E, 0, 0},   //# 268 gb_suboffset(0921)
	{0x5F, 0x02, 0, 0},   //# 25F demo_gain_order,bayer_order
	{0x32, 0x00, 0, 0},   //# 232 auto_mode
	{0x33, 0xEF, 0, 0},   //# 233 lsc_bpc_en
	{0xA4, 0xFF, 0, 0},   //# 2A4 lsc_gain_max
//#
	{0xFD, 0x03, 0, 0},
	{0x66, 0x19, 0, 0},   //# 366 Lsc_rsy_u
	{0x6A, 0x1B, 0, 0},   //# 36A Lsc_gsy_u
	{0x6E, 0x14, 0, 0},   //# 36E Lsc_bsy_u
	{0x67, 0x19, 0, 0},   //# 367 Lsc_rsy_d
	{0x6B, 0x12, 0, 0},   //# 36B Lsc_gsy_d
	{0x6F, 0x14, 0, 0},   //# 36F Lsc_bsy_d
	{0x64, 0x1D, 0, 0},   //# 364 Lsc_rsx_l
	{0x68, 0x18, 0, 0},   //# 368 Lsc_gsx_l
	{0x6C, 0x14, 0, 0},   //# 36C Lsc_bsx_l
	{0x65, 0x15, 0, 0},   //# 365 Lsc_rsx_r
	{0x69, 0x12, 0, 0},   //# 369 Lsc_gsx_r
	{0x6D, 0x0E, 0, 0},   //# 36D Lsc_bsx_r
	{0xB8, 0x08, 0, 0},   //# 3B8 Lsc_rxy_lu
	{0xBC, 0x08, 0, 0},   //# 3BC Lsc_gxy_lu
	{0xC0, 0x08, 0, 0},   //# 3C0 Lsc_bxy_lu
	{0xB9, 0x08, 0, 0},   //# 3B9 Lsc_rxy_ru
	{0xBD, 0x08, 0, 0},   //# 3BD Lsc_gxy_ru
	{0xC1, 0x08, 0, 0},   //# 3C1 Lsc_bxy_ru
	{0xBA, 0x08, 0, 0},   //# 3BA Lsc_rxy_ld
	{0xBE, 0x08, 0, 0},   //# 3BE Lsc_gxy_ld
	{0xC2, 0x08, 0, 0},   //# 3C2 Lsc_bxy_ld
	{0xBB, 0x08, 0, 0},   //# 3BB Lsc_rxy_rd
	{0xBF, 0x08, 0, 0},   //# 3BF Lsc_gxy_rd
	{0xC3, 0x08, 0, 0},   //# 3C3 Lsc_bxy_rd
//#
	{0xFD, 0x02, 0, 0},
	{0x51, 0x00, 0, 0},   //# 251 bpc_vt_outdoor
	{0x52, 0x00, 0, 0},   //# 252 bpc_vt_normal
	{0x53, 0x00, 0, 0},   //# 253 bpc_vt_low_light
	{0x54, 0x00, 0, 0},   //# 254 bpc_wt_eff
	{0x55, 0xFF, 0, 0},   //# 255 bpc_dt_eff
//	{0x45, 0x00, 0, 0},   //# 245 bpc_range_ratio_outdoor,pc_range_ratio_nr
//	{0x46, 0x09, 0, 0},   //# 246 bpc_range_ratio_dummy,bpc_range_ratio_low
	{0x45, 0x13, 0, 0},   //# 245 bpc_range_ratio_outdoor,pc_range_ratio_nr (1001)
	{0x46, 0x49, 0, 0},   //# 246 bpc_range_ratio_dummy,bpc_range_ratio_low (1001)
	{0x69, 0x00, 0, 0},   //# 269 bpc_range_thr_outdoor
	{0x6A, 0x00, 0, 0},   //# 26A bpc_range_thr_nr
	{0x6B, 0x00, 0, 0},   //# 26B bpc_range_thr_dummy
	{0x6C, 0x00, 0, 0},   //# 26C bpc_range_thr_low
//#
	{0xFD, 0x03, 0, 0},
	{0xDE, 0x0F, 0, 0},   //# 3DE raw_denoise_en_outdoor,raw_denoise_en_nr,raw_denoise_en_dummy,raw_denoise_en_low
//#
	{0xFD, 0x02, 0, 0},
	{0x57, 0x04, 0, 0},   //# 257 raw_dif_thr_outdoor
	{0x58, 0x04, 0, 0},   //# 258 raw_dif_thr_normal
	{0x56, 0x0A, 0, 0},   //# 256 raw_dif_thr_dummy
	{0x59, 0x08, 0, 0},   //# 259 raw_dif_thr_low_light
	{0x4F, 0xE0, 0, 0},   //# 24F raw_gf_fac_outdoor
	{0xC3, 0xE0, 0, 0},   //# 2C3 raw_gf_fac_indoor
	{0x3F, 0xC0, 0, 0},   //# 23F raw_gf_fac_dummy
	{0x42, 0x40, 0, 0},   //# 242 raw_gf_fac_low
	{0x5A, 0xE0, 0, 0},   //# 25A raw_rb_fac_outdoor
	{0xC4, 0xE0, 0, 0},   //# 2C4 raw_rb_fac_indoor
	{0x43, 0xC0, 0, 0},   //# 243 raw_rb_fac_dummy
	{0xAD, 0x40, 0, 0},   //# 2AD raw_rb_fac_low
	{0xC2, 0x15, 0, 0},   //# 2C2 gf_ratiok_fac
//#
	{0xFD, 0x03, 0, 0},
	{0x50, 0x00, 0, 0},   //# 350 raw_grgb_thr_outdoor
	{0x51, 0x00, 0, 0},   //# 351 raw_grgb_thr_normal
	{0x52, 0x08, 0, 0},   //# 352 raw_grgb_thr_dummy
	{0x53, 0x08, 0, 0},   //# 353 raw_grgb_thr_low
//#
	{0xFD, 0x02, 0, 0},
	{0xB6, 0xE0, 0, 0},   //# 2B6 raw_gflt_fac_outdoor
	{0xB7, 0xC0, 0, 0},   //# 2B7 raw_gflt_fac_nr
	{0xB8, 0xA0, 0, 0},   //# 2B8 raw_gflt_fac_dummy
	{0xB9, 0x20, 0, 0},   //# 2B9 raw_gflt_fac_low
//#
	{0xFD, 0x03, 0, 0},
	{0x11, 0x1F, 0, 0},   //# 311 rg_dif_th
	{0x12, 0x1F, 0, 0},   //# 312 bg_dif_th
	{0x16, 0x1C, 0, 0},   //# 316 rgb_limit
	{0x18, 0x00, 0, 0},   //# 318 br_offset_f
	{0x19, 0x00, 0, 0},   //# 319 br_offset
	{0x1B, 0x80, 0, 0},   //# 31B rg_base
	{0x1A, 0x80, 0, 0},   //# 31A bg_base
	{0x43, 0x80, 0, 0},   //# 343 channel_sel,test_awb
	{0x1E, 0x17, 0, 0},   //# 31E wb_fine_gain_step,wb_rough_gain_step
	{0x1F, 0x19, 0, 0},   //# 31F wb_dif_fine_th,wb_dif_rough_th
//	{0x28, 0xA5, 0, 0},   //# 328 buf_rgain
//	{0x29, 0x99, 0, 0},   //# 329 buf_bgain
	{0x28, 0x9B, 0, 0},   //# 328 buf_rgain(1001)
	{0x29, 0xAB, 0, 0},   //# 329 buf_bgain(1001)
//#
	{0xFD, 0x02, 0, 0},
	{0xE7, 0x03, 0, 0},   //# 2E7 reg_renew
	{0xE7, 0x00, 0, 0},   //# 2E7 reg_renew
//#
	{0xFD, 0x03, 0, 0},
	{0x2A, 0xF0, 0, 0},   //# 32A y_top_th
	{0x2B, 0x10, 0, 0},   //# 32B y_bot_th
	{0x2E, 0x04, 0, 0},   //# 32E rg_limit_log
	{0x2F, 0x16, 0, 0},   //# 32F bg_limit_log
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x80, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x80, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0x83, 0x70, 0, 0},   //# 383 skin_num_th
	{0x13, 0x43, 0, 0},   //# 313 awb_grey_en,awb_skin_en
	{0x24, 0x06, 0, 0},   //# 324 short_exp_th
	{0x25, 0x80, 0, 0},   //# 325 sp_rg_base
	{0x26, 0x80, 0, 0},   //# 326 sp_bg_base
	{0x35, 0xB2, 0, 0},   //# 335 d65_rg_bot
	{0x36, 0xCA, 0, 0},   //# 336 d65_rg_top
//	{0x37, 0x7C, 0, 0},   //# 337 d65_bg_bot
	{0x37, 0x73, 0, 0},   //# 337 d65_bg_bot(1001)
	{0x38, 0x94, 0, 0},   //# 338 d65_bg_top
//	{0x31, 0x7B, 0, 0},   //# 331 f_rg_bot
//	{0x32, 0x93, 0, 0},   //# 332 f_rg_top
//	{0x33, 0xAE, 0, 0},   //# 333 f_bg_bot
//	{0x34, 0xC6, 0, 0},   //# 334 f_bg_top
	{0x31, 0x60, 0, 0},   //# 331 f_rg_bot(1010)
	{0x32, 0x98, 0, 0},   //# 332 f_rg_top(1010)
	{0x33, 0xA8, 0, 0},   //# 333 f_bg_bot(1010)
	{0x34, 0xD8, 0, 0},   //# 334 f_bg_top(1010)
	{0x3D, 0x9C, 0, 0},   //# 33D cwf_rg_bot
	{0x3E, 0xB4, 0, 0},   //# 33E cwf_rg_top
	{0x3F, 0xA4, 0, 0},   //# 33F cwf_bg_bot
	{0x40, 0xBC, 0, 0},   //# 340 cwf_bg_top
	{0x39, 0x8A, 0, 0},   //# 339 tl84_rg_bot
	{0x3A, 0xA2, 0, 0},   //# 33A tl84_rg_top
	{0x3B, 0x9E, 0, 0},   //# 33B tl84_bg_bot
	{0x3C, 0xB6, 0, 0},   //# 33C tl84_bg_top
	{0xA0, 0xA6, 0, 0},   //# 3A0 c00_eff1_8lsb
	{0xA1, 0xCD, 0, 0},   //# 3A1 c01_eff1_8lsb
	{0xA2, 0x0C, 0, 0},   //# 3A2 c02_eff1_8lsb
	{0xA3, 0x06, 0, 0},   //# 3A3 c10_eff1_8lsb
	{0xA4, 0x8C, 0, 0},   //# 3A4 c11_eff1_8lsb
	{0xA5, 0xED, 0, 0},   //# 3A5 c12_eff1_8lsb
	{0xA6, 0x00, 0, 0},   //# 3A6 c20_eff1_8lsb
	{0xA7, 0xE7, 0, 0},   //# 3A7 c21_eff1_8lsb
	{0xA8, 0x99, 0, 0},   //# 3A8 c22_eff1_8lsb
	{0xA9, 0x0C, 0, 0},   //# 3A9 c02_eff1_2msb,c01_eff1_2msb,c00_eff1_2msb
	{0xAA, 0x30, 0, 0},   //# 3AA c12_eff1_2msb,c11_eff1_2msb,c10_eff1_2msb
	{0xAB, 0x0C, 0, 0},   //# 3AB c22_eff1_2msb,c21_eff1_2msb,c20_eff1_2msb
	{0xAC, 0x8C, 0, 0},   //# 3AC c00_eff2_8lsb
	{0xAD, 0xF4, 0, 0},   //# 3AD c01_eff2_8lsb
	{0xAE, 0x00, 0, 0},   //# 3AE c02_eff2_8lsb
	{0xAF, 0xFA, 0, 0},   //# 3AF c10_eff2_8lsb
	{0xB0, 0x8C, 0, 0},   //# 3B0 c11_eff2_8lsb
	{0xB1, 0xFA, 0, 0},   //# 3B1 c12_eff2_8lsb
	{0xB2, 0x0C, 0, 0},   //# 3B2 c20_eff2_8lsb
	{0xB3, 0xF4, 0, 0},   //# 3B3 c21_eff2_8lsb
	{0xB4, 0x80, 0, 0},   //# 3B4 c22_eff2_8lsb
	{0xB5, 0x0C, 0, 0},   //# 3B5 c02_eff2_2msb,c01_eff2_2msb,c00_eff2_2msb
	{0xB6, 0x33, 0, 0},   //# 3B6 c12_eff2_2msb,c11_eff2_2msb,c10_eff2_2msb
	{0xB7, 0x0C, 0, 0},   //# 3B7 c22_eff2_2msb,c21_eff2_2msb,c20_eff2_2msb
//#
	{0xFD, 0x02, 0, 0},
	{0xBF, 0x01, 0, 0},   //# 2BF autosa_en
	{0xBE, 0xAA, 0, 0},   //# 2BE u_v_th
	{0xC0, 0xFF, 0, 0},   //# 2C0 y_p_th
	{0xC1, 0xFF, 0, 0},   //# 2C1 y_mean_th
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
	{0x8B, 0x00, 0, 0},   //# 28B gamma_pt0
	{0x8C, 0x0F, 0, 0},   //# 28C gamma_pt1
	{0x8D, 0x1F, 0, 0},   //# 28D gamma_pt2
	{0x8E, 0x3C, 0, 0},   //# 28E gamma_pt3
	{0x8F, 0x67, 0, 0},   //# 28F gamma_pt4
	{0x90, 0x85, 0, 0},   //# 290 gamma_pt5
	{0x91, 0x99, 0, 0},   //# 291 gamma_pt6
	{0x92, 0xA8, 0, 0},   //# 292 gamma_pt7
	{0x93, 0xB5, 0, 0},   //# 293 gamma_pt8
	{0x94, 0xBE, 0, 0},   //# 294 gamma_pt9
	{0x95, 0xC8, 0, 0},   //# 295 gamma_pt10
	{0x96, 0xD1, 0, 0},   //# 296 gamma_pt11
	{0x97, 0xD9, 0, 0},   //# 297 gamma_pt12
	{0x98, 0xE0, 0, 0},   //# 298 gamma_pt13
	{0x99, 0xE8, 0, 0},   //# 299 gamma_pt14
	{0x9A, 0xED, 0, 0},   //# 29A gamma_pt15
	{0x9B, 0xF3, 0, 0},   //# 29B gamma_pt16
//#
	{0xFD, 0x03, 0, 0},
	{0x8D, 0xF9, 0, 0},   //# 38D gamma_pt17
	{0x8E, 0xFF, 0, 0},   //# 38E gamma_pt18
//#
	{0xFD, 0x02, 0, 0},
	{0x78, 0x00, 0, 0},   //# 278 gamma_pt2_0
	{0x79, 0x0F, 0, 0},   //# 279 gamma_pt2_1
	{0x7A, 0x1F, 0, 0},   //# 27A gamma_pt2_2
	{0x7B, 0x3C, 0, 0},   //# 27B gamma_pt2_3
	{0x7C, 0x67, 0, 0},   //# 27C gamma_pt2_4
	{0x7D, 0x85, 0, 0},   //# 27D gamma_pt2_5
	{0x7E, 0x99, 0, 0},   //# 27E gamma_p2_6
	{0x7F, 0xA8, 0, 0},   //# 27F gamma_pt2_7
	{0x80, 0xB5, 0, 0},   //# 280 gamma_pt2_8
	{0x81, 0xBE, 0, 0},   //# 281 gamma_pt2_9
	{0x82, 0xC8, 0, 0},   //# 282 gamma_pt2_10
	{0x83, 0xD1, 0, 0},   //# 283 gamma_pt2_11
	{0x84, 0xD9, 0, 0},   //# 284 gamma_pt2_12
	{0x85, 0xE0, 0, 0},   //# 285 gamma_pt2_13
	{0x86, 0xE8, 0, 0},   //# 286 gamma_pt2_14
	{0x87, 0xED, 0, 0},   //# 287 gamma_pt2_15
	{0x88, 0xF3, 0, 0},   //# 288 gamma_pt2_16
	{0x89, 0xF9, 0, 0},   //# 289 gamma_pt2_17
	{0x8A, 0xFF, 0, 0},   //# 28A gamma_pt2_18
//#
	{0xFD, 0x03, 0, 0},
	{0x96, 0x46, 0, 0},   //# 396 ae time thr1
	{0x97, 0x28, 0, 0},   //# 397 ae time thr2
	{0x9F, 0x0A, 0, 0},   //# 39F gma_ratiok_fac
//#
	{0xFD, 0x02, 0, 0},
	{0xF4, 0x0B, 0, 0},   //# 2F4 lum_fcase_en,lum_down_en,outdoor_mode_en,mean_mode_reg
	{0xF0, 0x64, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 exp_min_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
	{0x95, 0x20, 0, 0},   //# 395 rpc_min_indr
	{0x98, 0x64, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_outdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x9C, 0x32, 0, 0},   //# 39C rpc_max_outdr
	{0x9D, 0x20, 0, 0},   //# 39D rpc_min_outdr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x55, 0x11, 0, 0},   //# 355 weight_w2,weight_w1
	{0x56, 0x11, 0, 0},   //# 356 weight_w4,weight_w3
//	{0x57, 0x03, 0, 0},   //# 357 weight_w5
	{0x57, 0x01, 0, 0},   //# 357 weight_w5(1001)
//#
	{0xFD, 0x02, 0, 0},
	{0xE0, 0x3E, 0, 0},   //# 2E0 rpc_1base_max
	{0xE1, 0x26, 0, 0},   //# 2E1 rpc_2base_max
	{0xE2, 0x2A, 0, 0},   //# 2E2 rpc_3base_max
	{0xE3, 0x26, 0, 0},   //# 2E3 rpc_4base_max
	{0xE4, 0x26, 0, 0},   //# 2E4 rpc_5base_max
	{0xE5, 0x24, 0, 0},   //# 2E5 rpc_6base_max
	{0xE6, 0x24, 0, 0},   //# 2E6 rpc_7base_max
	{0xE8, 0x22, 0, 0},   //# 2E8 rpc_8base_max
	{0xE9, 0x22, 0, 0},   //# 2E9 rpc_9base_max
	{0xEA, 0x22, 0, 0},   //# 2EA rpc_10base_max
	{0xEB, 0x20, 0, 0},   //# 2EB rpc_11base_max
	{0xF5, 0x20, 0, 0},   //# 2F5 rpc_12base_max
	{0xF6, 0x20, 0, 0},   //# 2F6 rpc_13base_max
	{0xF3, 0x03, 0, 0},   //# 2F3 uv_dif_en_outdoor,uv_dif_en_nr,uv_dif_en_dummy,uv_dif_en_low
	{0xB0, 0x00, 0, 0},   //# 2B0 uv_dif_gain_outdoor,uv_dif_gain_nr
	{0xB1, 0x12, 0, 0},   //# 2B1 uv_dif_gain_dummy,uv_dif_gain_low
//#
	{0xFD, 0x03, 0, 0},
	{0xDF, 0x0F, 0, 0},   //# 3DF sharpness
	{0xE7, 0x08, 0, 0},   //# 3E7 raw_sharp_range_base
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
	{0x70, 0x73, 0, 0},   //# 370 aec_gw_en,gw_uv_dif_en,gw_detect_en,gw_step
	{0x7B, 0x40, 0, 0},   //# 37B gw_mean_th
	{0x71, 0x2F, 0, 0},   //# 371 k_up
	{0x72, 0x0D, 0, 0},   //# 372 k_low
	{0x73, 0x0A, 0, 0},   //# 373 b_up
	{0x74, 0x2A, 0, 0},   //# 374 b_low
	{0x75, 0x04, 0, 0},   //# 375 uv_low_th
	{0x76, 0x20, 0, 0},   //# 376 y_low_th
	{0x77, 0x32, 0, 0},   //# 377 u_top
	{0x78, 0x00, 0, 0},   //# 378 u_bot
	{0x79, 0x28, 0, 0},   //# 379 v_top
	{0x7A, 0x00, 0, 0},   //# 37A v_bot
	{0x7C, 0x70, 0, 0},   //# 37C gw_offset
	{0x7D, 0x90, 0, 0},   //# 37D gw_y_bot
	{0x7E, 0xEF, 0, 0},   //# 37E gw_y_top
	{0x7F, 0x04, 0, 0},   //# 37F gw_uv_radius
	{0x80, 0x40, 0, 0},   //# 380 uv_fix_dat
	{0x81, 0x20, 0, 0},   //# 381 y_offset_th
	{0x8F, 0x12, 0, 0},   //# 38F wt_th
	{0xCE, 0xD0, 0, 0},   //# 3CE exp_heq_dummy[7:0]
	{0xCF, 0x07, 0, 0},   //# 3CF exp_heq_dummy[12:8]
	{0xCD, 0x30, 0, 0},   //# 3CD rpc_heq_dummy
	{0xCA, 0x68, 0, 0},   //# 3CA mean_dummy_low
	{0xCB, 0x88, 0, 0},   //# 3CB mean_low_dummy
	{0xD0, 0xD0, 0, 0},   //# 3D0 exp_heq_low[7:0]
	{0xD1, 0x07, 0, 0},   //# 3D1 exp_heq_low[12:8]
	{0xCC, 0xC0, 0, 0},   //# 3CC rpc_heq_low
	{0xD5, 0x80, 0, 0},   //# 3D5 mean_nr_dummy
	{0xD6, 0x90, 0, 0},   //# 3D6 mean_dummy_nr
	{0xD7, 0x61, 0, 0},   //# 3D7 exp_nr_outd_8lsb
	{0xD8, 0x00, 0, 0},   //# 3D8 exp_nr_outd_5hsb
	{0xD9, 0x64, 0, 0},   //# 3D9 exp_outd_nr_8lsb
	{0xDA, 0x00, 0, 0},   //# 3DA exp_outd_nr_5hsb
//#
	{0xFD, 0x02, 0, 0},
	{0xB2, 0x30, 0, 0},   //# 2B2 lum_limit
	{0xB3, 0x18, 0, 0},   //# 2B3 lum_set
	{0xB4, 0x60, 0, 0},   //# 2B4 black_vt
	{0xB5, 0x70, 0, 0},   //# 2B5 white_vt
	{0xCB, 0x00, 0, 0},   //# 2CB rg_clip_ga_outdoor
	{0xCC, 0x02, 0, 0},   //# 2CC rg_clip_ga_nr
	{0xCD, 0x05, 0, 0},   //# 2CD rg_clip_ga_dummy
	{0xCE, 0x08, 0, 0},   //# 2CE rg_clip_ga_low
	{0xCF, 0x00, 0, 0},   //# 2CF bg_clip_ga_outdoor
	{0xD0, 0x02, 0, 0},   //# 2D0 bg_clip_ga_nr
//#
	{0xFD, 0x03, 0, 0},
	{0x10, 0x05, 0, 0},   //# 310 bg_clip_ga_dummy
	{0x14, 0x08, 0, 0},   //# 314 bg_clip_ga_low
//#
	{0xFD, 0x02, 0, 0},
	{0x5B, 0x00, 0, 0},   //# 25B cnr_thr_outdoor
	{0x61, 0x08, 0, 0},   //# 261 cnr_thr_nr
	{0x77, 0x40, 0, 0},   //# 277 cnr_thr_dummy
	{0xCA, 0x60, 0, 0},   //# 2CA cnr_thr_low
//	{0xAB, 0x10, 0, 0},   //# 2AB ynr_thr_outdoor
	{0xAB, 0x00, 0, 0},   //# 2AB ynr_thr_outdoor(1001)
	{0xAC, 0x10, 0, 0},   //# 2AC ynr_thr_nr
	{0xAE, 0x60, 0, 0},   //# 2AE ynr_thr_dummy
	{0xAF, 0x40, 0, 0},   //# 2AF ynr_thr_low
	{0x60, 0x01, 0, 0},   //# 260 bpc_vt_dummy
	{0x70, 0x0A, 0, 0},   //# 270 Bpc_v
	{0x76, 0x00, 0, 0},   //# 276 blacklevelin
	{0xC5, 0x60, 0, 0},   //# 2C5 raw_gflt_fac_indoor
	{0xDC, 0x00, 0, 0},   //# 2DC buf_heq_offset
	{0xDD, 0x80, 0, 0},   //# 2DD ku
	{0xDE, 0x90, 0, 0},   //# 2DE kl
//#
	{0xFD, 0x03, 0, 0},
	{0x06, 0x00, 0, 0},   //# 306 ratio_row[9:8]
	{0x07, 0x50, 0, 0},   //# 307 ratio_row[7:0]
	{0x08, 0x00, 0, 0},   //# 308 ratio_col[9:8]
	{0x09, 0x50, 0, 0},   //# 309 ratio_col[7:0]
	{0x0A, 0x00, 0, 0},   //# 30A scalerownum[10:8]
	{0x0B, 0xF0, 0, 0},   //# 30B scalerownum[7:0]
	{0x0C, 0x01, 0, 0},   //# 30C scalecolnum[10:8]
	{0x0D, 0x40, 0, 0},   //# 30D scalecolnum[7:0]
	{0x0E, 0x01, 0, 0},   //# 30E resize_en
	{0x1C, 0xBA, 0, 0},   //# 31C f_limit_b
	{0x1D, 0x87, 0, 0},   //# 31D f_limit_r
	{0x41, 0x00, 0, 0},   //# 341 grgb_top_high_bit
	{0x42, 0x00, 0, 0},   //# 342 grgb_bot_high_bit
	{0x44, 0x0F, 0, 0},   //# 344 wb_num_th_light_s
	{0x4C, 0x48, 0, 0},   //# 34C raw_adt_fac_outdoor
	{0x4D, 0x48, 0, 0},   //# 34D raw_adt_fac_normal
	{0x4E, 0x48, 0, 0},   //# 34E raw_adt_fac_dummy
	{0x4F, 0x48, 0, 0},   //# 34F raw_adt_fac_low
	{0xC6, 0x40, 0, 0},   //# 3C6 pre_grgain
	{0xC7, 0x40, 0, 0},   //# 3C7 pre_rgain
	{0xC8, 0x40, 0, 0},   //# 3C8 pre_gbgain
	{0xC9, 0x40, 0, 0},   //# 3C9 pre_bgain
	{0xE2, 0x40, 0, 0},   //# 3E2 raw_sharp_y_base
	{0xE3, 0x10, 0, 0},   //# 3E3 raw_sharp_y_min
	{0xE4, 0xE0, 0, 0},   //# 3E4 raw_sharp_y_max
	{0xE5, 0x30, 0, 0},   //# 3E5 raw_sharp_rangek_neg
	{0xE6, 0x20, 0, 0},   //# 3E6 raw_sharp_rangek_pos
//#
	{0xFD, 0x02, 0, 0},
	{0x32, 0x0D, 0, 0},   //# 232 auto_mode
	{0x33, 0xEF, 0, 0},   //# 233 lsc_bpc_en
	{0x34, 0xFF, 0, 0},   //# 234 buf_isp_mode
	{0xFB, 0x00, 0, 0},   //# 2FB blackgain_en,bl_bpc_en,abl
	{0x36, 0x00, 0, 0},   //# 236 buf_outmode2
};

static struct reg_value rnss2e1_setting_30fps_QVGA_320_240[] = {
	{0xFD, 0x02, 0, 0},
	{0x36, 0x00, 0, 0},   //# 236 buf_outmode2
//#
	{0xFD, 0x00, 0, 0},
	{0x10, 0x1F, 0, 0},   //# 010 clk_mode
	{0x11, 0x40, 0, 0},   //# 011 pclk_inv,pclk_gate_en,pclk_ctrl,isp_clk_ctrl
	{0x20, 0x02, 0, 0},   //# 020 ds_data,out_end_high8,out_end_low2,out_ens
	{0x21, 0x03, 0, 0},   //# 021 pe_hvp,pe_data,ds_s,buf_dis_s,buf_dis_d
//#
	{0xFD, 0x01, 0, 0},
//	{0x03, 0x00, 0, 0},   //# 103 buf_exp_5msb
//	{0x04, 0x18, 0, 0},   //# 104 buf_exp_8lsb
	{0x03, 0x01, 0, 0},   //# 103 buf_exp_5msb
	{0x04, 0x8E, 0, 0},   //# 104 buf_exp_8lsb
	{0x09, 0x00, 0, 0},   //# 109 hblank_4msb
	{0x0A, 0x4E, 0, 0},   //# 10A hblank_8lsb
//#
	{0xFD, 0x00, 0, 0},
	{0x0E, 0x40, 0, 0},   //# 00E pd
//#
	{0xFD, 0x01, 0, 0},
	{0x0E, 0x00, 0, 0},   //# 10E p0
	{0x0F, 0x18, 0, 0},   //# 10F p1
	{0x10, 0x10, 0, 0},   //# 110 p2
	{0x11, 0x03, 0, 0},   //# 111 p3
	{0x12, 0x18, 0, 0},   //# 112 p4
	{0x13, 0x10, 0, 0},   //# 113 p5
	{0x14, 0x15, 0, 0},   //# 114 p6
	{0x15, 0x01, 0, 0},   //# 115 p7
	{0x16, 0x02, 0, 0},   //# 116 p8
	{0x17, 0x10, 0, 0},   //# 117 p9
	{0x18, 0x00, 0, 0},   //# 118 p10_2msb
	{0x19, 0x1A, 0, 0},   //# 119 p10_8lsb
	{0x1A, 0x00, 0, 0},   //# 11A p11_2msb
	{0x1B, 0x1C, 0, 0},   //# 11B p11_8lsb
	{0x50, 0x00, 0, 0},   //# 150 p12_2msb
	{0x51, 0x1D, 0, 0},   //# 151 p12_8lsb
	{0x52, 0x15, 0, 0},   //# 152 P13
	{0x2A, 0x02, 0, 0},   //# 12A p16
	{0x53, 0x00, 0, 0},   //# 153 p17_2msb
	{0x54, 0x11, 0, 0},   //# 154 p17_8lsb
	{0x55, 0x12, 0, 0},   //# 155 p18
	{0x56, 0x02, 0, 0},   //# 156 p19
	{0x57, 0x02, 0, 0},   //# 157 p20
	{0x58, 0x00, 0, 0},   //# 158 p21
//#
	{0xFD, 0x00, 0, 0},
	{0x12, 0x04, 0, 0},   //# 012 pll_bias_ctl,pll_delay
	{0x13, 0x04, 0, 0},   //# 013 mipi_pattern_en,pll_test_en,mipi_en
	{0x14, 0x00, 0, 0},   //# 014 pclk_gate,timer_clk_gate,dclk_gate
	{0x15, 0x00, 0, 0},   //# 015 pclk_pha_adj
//#
	{0xFD, 0x01, 0, 0},
//	{0x1C, 0x5C, 0, 0},   //# 11C two_timing_en,FPN_33ms_X,pwd_asp_timing_sel,Channel-timing
	{0x1C, 0x7C, 0, 0},   //# 11C two_timing_en,FPN_33ms_X,pwd_asp_timing_sel,Channel-timing
	{0x21, 0x44, 0, 0},   //# 121 adc_vcm_opin_ctl,adc_vcm_opin_c,col_clk_delay
	{0x22, 0x04, 0, 0},   //# 122 pga_bias_ctl,col_ctrl
	{0x25, 0x00, 0, 0},   //# 125 adc_range_ctl,adc_vcm_ctl,asp_delay
	{0x26, 0x26, 0, 0},   //# 126 adc_dig_offset,sw_delay
	{0x27, 0x6D, 0, 0},   //# 127 delay,black_en,adc_dref_cal,adc_g2x_en,adc_offset_en
	{0x2B, 0x66, 0, 0},   //# 12B adc_offset_ctl_buf_up,adc_offset_ctl_buf_dn
	{0x2C, 0x3F, 0, 0},   //# 12C strobe_en,bl_da
	{0x2D, 0x40, 0, 0},   //# 12D adc_bias_stage,adc_bias_vref
	{0x2E, 0x0D, 0, 0},   //# 12E dout_sel,strobe_sel
//	{0x40, 0xF0, 0, 0},   //# 140 vfpn_bpc_en,vfpn_minus_en
	{0x40, 0xF3, 0, 0},   //# 140 vfpn_bpc_en,vfpn_minus_en
	{0x41, 0x60, 0, 0},   //# 141 vfpn_bpc_th_x1
	{0x42, 0x50, 0, 0},   //# 142 vfpn_bpc_th_x2
	{0x43, 0x28, 0, 0},   //# 143 vfpn_bpc_in_x1
	{0x44, 0x28, 0, 0},   //# 144 vfpn_bpc_in_x2
//	{0x45, 0x0C, 0, 0},   //# 145 vfpn_delta
//	{0x45, 0x06, 0, 0},   //# 145 vfpn_delta(0830)
	{0x45, 0x00, 0, 0},   //# 145 vfpn_delta(0921)
	{0x31, 0x14, 0, 0},   //# 131 buf_comm_ctrl
//#
	{0xFD, 0x02, 0, 0},
	{0x35, 0x40, 0, 0},   //# 235 buf_outmode1
	{0x31, 0x10, 0, 0},   //# 231 digital_gain
	{0x47, 0x00, 0, 0},   //# 247 v_start_3msb
	{0x48, 0x00, 0, 0},   //# 248 v_start_8lsb
	{0x49, 0x02, 0, 0},   //# 249 v_size_3msb
	{0x4A, 0x58, 0, 0},   //# 24A v_size_8lsb
	{0x4B, 0x00, 0, 0},   //# 24B h_start_3msb
	{0x4C, 0x00, 0, 0},   //# 24C h_start_8lsb
	{0x4D, 0x03, 0, 0},   //# 24D h_size_3msb
	{0x4E, 0x20, 0, 0},   //# 24E h_size_8lsb
//	{0x65, 0x08, 0, 0},   //# 265 blue_suboffset
//	{0x66, 0x06, 0, 0},   //# 266 red_suboffset
//	{0x67, 0x07, 0, 0},   //# 267 gr_suboffset
//	{0x68, 0x07, 0, 0},   //# 268 gb_suboffset
//	{0x65, 0x09, 0, 0},   //# 265 blue_suboffset(0830)
//	{0x66, 0x07, 0, 0},   //# 266 red_suboffset(0830)
//	{0x67, 0x08, 0, 0},   //# 267 gr_suboffset(0830)
//	{0x68, 0x08, 0, 0},   //# 268 gb_suboffset(0830)
	{0x65, 0x0F, 0, 0},   //# 265 blue_suboffset(0921)
	{0x66, 0x0D, 0, 0},   //# 266 red_suboffset(0921)
	{0x67, 0x0E, 0, 0},   //# 267 gr_suboffset(0921)
	{0x68, 0x0E, 0, 0},   //# 268 gb_suboffset(0921)
	{0x5F, 0x02, 0, 0},   //# 25F demo_gain_order,bayer_order
	{0x32, 0x00, 0, 0},   //# 232 auto_mode
	{0x33, 0xEF, 0, 0},   //# 233 lsc_bpc_en
	{0xA4, 0xFF, 0, 0},   //# 2A4 lsc_gain_max
//#
	{0xFD, 0x03, 0, 0},
	{0x66, 0x19, 0, 0},   //# 366 Lsc_rsy_u
	{0x6A, 0x1B, 0, 0},   //# 36A Lsc_gsy_u
	{0x6E, 0x14, 0, 0},   //# 36E Lsc_bsy_u
	{0x67, 0x19, 0, 0},   //# 367 Lsc_rsy_d
	{0x6B, 0x12, 0, 0},   //# 36B Lsc_gsy_d
	{0x6F, 0x14, 0, 0},   //# 36F Lsc_bsy_d
	{0x64, 0x1D, 0, 0},   //# 364 Lsc_rsx_l
	{0x68, 0x18, 0, 0},   //# 368 Lsc_gsx_l
	{0x6C, 0x14, 0, 0},   //# 36C Lsc_bsx_l
	{0x65, 0x15, 0, 0},   //# 365 Lsc_rsx_r
	{0x69, 0x12, 0, 0},   //# 369 Lsc_gsx_r
	{0x6D, 0x0E, 0, 0},   //# 36D Lsc_bsx_r
	{0xB8, 0x08, 0, 0},   //# 3B8 Lsc_rxy_lu
	{0xBC, 0x08, 0, 0},   //# 3BC Lsc_gxy_lu
	{0xC0, 0x08, 0, 0},   //# 3C0 Lsc_bxy_lu
	{0xB9, 0x08, 0, 0},   //# 3B9 Lsc_rxy_ru
	{0xBD, 0x08, 0, 0},   //# 3BD Lsc_gxy_ru
	{0xC1, 0x08, 0, 0},   //# 3C1 Lsc_bxy_ru
	{0xBA, 0x08, 0, 0},   //# 3BA Lsc_rxy_ld
	{0xBE, 0x08, 0, 0},   //# 3BE Lsc_gxy_ld
	{0xC2, 0x08, 0, 0},   //# 3C2 Lsc_bxy_ld
	{0xBB, 0x08, 0, 0},   //# 3BB Lsc_rxy_rd
	{0xBF, 0x08, 0, 0},   //# 3BF Lsc_gxy_rd
	{0xC3, 0x08, 0, 0},   //# 3C3 Lsc_bxy_rd
//#
	{0xFD, 0x02, 0, 0},
	{0x51, 0x00, 0, 0},   //# 251 bpc_vt_outdoor
	{0x52, 0x00, 0, 0},   //# 252 bpc_vt_normal
	{0x53, 0x00, 0, 0},   //# 253 bpc_vt_low_light
	{0x54, 0x00, 0, 0},   //# 254 bpc_wt_eff
	{0x55, 0xFF, 0, 0},   //# 255 bpc_dt_eff
//	{0x45, 0x00, 0, 0},   //# 245 bpc_range_ratio_outdoor,pc_range_ratio_nr
//	{0x46, 0x09, 0, 0},   //# 246 bpc_range_ratio_dummy,bpc_range_ratio_low
	{0x45, 0x13, 0, 0},   //# 245 bpc_range_ratio_outdoor,pc_range_ratio_nr (1001)
	{0x46, 0x49, 0, 0},   //# 246 bpc_range_ratio_dummy,bpc_range_ratio_low (1001)
	{0x69, 0x00, 0, 0},   //# 269 bpc_range_thr_outdoor
	{0x6A, 0x00, 0, 0},   //# 26A bpc_range_thr_nr
	{0x6B, 0x00, 0, 0},   //# 26B bpc_range_thr_dummy
	{0x6C, 0x00, 0, 0},   //# 26C bpc_range_thr_low
//#
	{0xFD, 0x03, 0, 0},
	{0xDE, 0x0F, 0, 0},   //# 3DE raw_denoise_en_outdoor,raw_denoise_en_nr,raw_denoise_en_dummy,raw_denoise_en_low
//#
	{0xFD, 0x02, 0, 0},
	{0x57, 0x04, 0, 0},   //# 257 raw_dif_thr_outdoor
	{0x58, 0x04, 0, 0},   //# 258 raw_dif_thr_normal
	{0x56, 0x0A, 0, 0},   //# 256 raw_dif_thr_dummy
	{0x59, 0x08, 0, 0},   //# 259 raw_dif_thr_low_light
	{0x4F, 0xE0, 0, 0},   //# 24F raw_gf_fac_outdoor
	{0xC3, 0xE0, 0, 0},   //# 2C3 raw_gf_fac_indoor
	{0x3F, 0xC0, 0, 0},   //# 23F raw_gf_fac_dummy
	{0x42, 0x40, 0, 0},   //# 242 raw_gf_fac_low
	{0x5A, 0xE0, 0, 0},   //# 25A raw_rb_fac_outdoor
	{0xC4, 0xE0, 0, 0},   //# 2C4 raw_rb_fac_indoor
	{0x43, 0xC0, 0, 0},   //# 243 raw_rb_fac_dummy
	{0xAD, 0x40, 0, 0},   //# 2AD raw_rb_fac_low
	{0xC2, 0x15, 0, 0},   //# 2C2 gf_ratiok_fac
//#
	{0xFD, 0x03, 0, 0},
	{0x50, 0x00, 0, 0},   //# 350 raw_grgb_thr_outdoor
	{0x51, 0x00, 0, 0},   //# 351 raw_grgb_thr_normal
	{0x52, 0x08, 0, 0},   //# 352 raw_grgb_thr_dummy
	{0x53, 0x08, 0, 0},   //# 353 raw_grgb_thr_low
//#
	{0xFD, 0x02, 0, 0},
	{0xB6, 0xE0, 0, 0},   //# 2B6 raw_gflt_fac_outdoor
	{0xB7, 0xC0, 0, 0},   //# 2B7 raw_gflt_fac_nr
	{0xB8, 0xA0, 0, 0},   //# 2B8 raw_gflt_fac_dummy
	{0xB9, 0x20, 0, 0},   //# 2B9 raw_gflt_fac_low
//#
	{0xFD, 0x03, 0, 0},
	{0x11, 0x1F, 0, 0},   //# 311 rg_dif_th
	{0x12, 0x1F, 0, 0},   //# 312 bg_dif_th
	{0x16, 0x1C, 0, 0},   //# 316 rgb_limit
	{0x18, 0x00, 0, 0},   //# 318 br_offset_f
	{0x19, 0x00, 0, 0},   //# 319 br_offset
	{0x1B, 0x80, 0, 0},   //# 31B rg_base
	{0x1A, 0x80, 0, 0},   //# 31A bg_base
	{0x43, 0x80, 0, 0},   //# 343 channel_sel,test_awb
	{0x1E, 0x17, 0, 0},   //# 31E wb_fine_gain_step,wb_rough_gain_step
	{0x1F, 0x19, 0, 0},   //# 31F wb_dif_fine_th,wb_dif_rough_th
//	{0x28, 0xA7, 0, 0},   //# 328 buf_rgain
//	{0x29, 0x98, 0, 0},   //# 329 buf_bgain
	{0x28, 0x9B, 0, 0},   //# 328 buf_rgain(1001)
	{0x29, 0xAB, 0, 0},   //# 329 buf_bgain(1001)
//#
	{0xFD, 0x02, 0, 0},
	{0xE7, 0x03, 0, 0},   //# 2E7 reg_renew
	{0xE7, 0x00, 0, 0},   //# 2E7 reg_renew
//#
	{0xFD, 0x03, 0, 0},
	{0x2A, 0xF0, 0, 0},   //# 32A y_top_th
	{0x2B, 0x10, 0, 0},   //# 32B y_bot_th
	{0x2E, 0x04, 0, 0},   //# 32E rg_limit_log
	{0x2F, 0x16, 0, 0},   //# 32F bg_limit_log
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x80, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x80, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0x83, 0x70, 0, 0},   //# 383 skin_num_th
	{0x13, 0x43, 0, 0},   //# 313 awb_grey_en,awb_skin_en
	{0x24, 0x06, 0, 0},   //# 324 short_exp_th
	{0x25, 0x80, 0, 0},   //# 325 sp_rg_base
	{0x26, 0x80, 0, 0},   //# 326 sp_bg_base
	{0x35, 0xB2, 0, 0},   //# 335 d65_rg_bot
	{0x36, 0xCA, 0, 0},   //# 336 d65_rg_top
//	{0x37, 0x7C, 0, 0},   //# 337 d65_bg_bot
	{0x37, 0x73, 0, 0},   //# 337 d65_bg_bot(1001)
	{0x38, 0x94, 0, 0},   //# 338 d65_bg_top
//	{0x31, 0x7B, 0, 0},   //# 331 f_rg_bot
//	{0x32, 0x93, 0, 0},   //# 332 f_rg_top
//	{0x33, 0xAE, 0, 0},   //# 333 f_bg_bot
//	{0x34, 0xC6, 0, 0},   //# 334 f_bg_top
	{0x31, 0x60, 0, 0},   //# 331 f_rg_bot(1010)
	{0x32, 0x98, 0, 0},   //# 332 f_rg_top(1010)
	{0x33, 0xA8, 0, 0},   //# 333 f_bg_bot(1010)
	{0x34, 0xD8, 0, 0},   //# 334 f_bg_top(1010)
	{0x3D, 0x9C, 0, 0},   //# 33D cwf_rg_bot
	{0x3E, 0xB4, 0, 0},   //# 33E cwf_rg_top
	{0x3F, 0xA4, 0, 0},   //# 33F cwf_bg_bot
	{0x40, 0xBC, 0, 0},   //# 340 cwf_bg_top
	{0x39, 0x8A, 0, 0},   //# 339 tl84_rg_bot
	{0x3A, 0xA2, 0, 0},   //# 33A tl84_rg_top
	{0x3B, 0x9E, 0, 0},   //# 33B tl84_bg_bot
	{0x3C, 0xB6, 0, 0},   //# 33C tl84_bg_top
	{0xA0, 0xA6, 0, 0},   //# 3A0 c00_eff1_8lsb
	{0xA1, 0xCD, 0, 0},   //# 3A1 c01_eff1_8lsb
	{0xA2, 0x0C, 0, 0},   //# 3A2 c02_eff1_8lsb
	{0xA3, 0x06, 0, 0},   //# 3A3 c10_eff1_8lsb
	{0xA4, 0x8C, 0, 0},   //# 3A4 c11_eff1_8lsb
	{0xA5, 0xED, 0, 0},   //# 3A5 c12_eff1_8lsb
	{0xA6, 0x00, 0, 0},   //# 3A6 c20_eff1_8lsb
	{0xA7, 0xE7, 0, 0},   //# 3A7 c21_eff1_8lsb
	{0xA8, 0x99, 0, 0},   //# 3A8 c22_eff1_8lsb
	{0xA9, 0x0C, 0, 0},   //# 3A9 c02_eff1_2msb,c01_eff1_2msb,c00_eff1_2msb
	{0xAA, 0x30, 0, 0},   //# 3AA c12_eff1_2msb,c11_eff1_2msb,c10_eff1_2msb
	{0xAB, 0x0C, 0, 0},   //# 3AB c22_eff1_2msb,c21_eff1_2msb,c20_eff1_2msb
	{0xAC, 0x8C, 0, 0},   //# 3AC c00_eff2_8lsb
	{0xAD, 0xF4, 0, 0},   //# 3AD c01_eff2_8lsb
	{0xAE, 0x00, 0, 0},   //# 3AE c02_eff2_8lsb
	{0xAF, 0xFA, 0, 0},   //# 3AF c10_eff2_8lsb
	{0xB0, 0x8C, 0, 0},   //# 3B0 c11_eff2_8lsb
	{0xB1, 0xFA, 0, 0},   //# 3B1 c12_eff2_8lsb
	{0xB2, 0x0C, 0, 0},   //# 3B2 c20_eff2_8lsb
	{0xB3, 0xF4, 0, 0},   //# 3B3 c21_eff2_8lsb
	{0xB4, 0x80, 0, 0},   //# 3B4 c22_eff2_8lsb
	{0xB5, 0x0C, 0, 0},   //# 3B5 c02_eff2_2msb,c01_eff2_2msb,c00_eff2_2msb
	{0xB6, 0x33, 0, 0},   //# 3B6 c12_eff2_2msb,c11_eff2_2msb,c10_eff2_2msb
	{0xB7, 0x0C, 0, 0},   //# 3B7 c22_eff2_2msb,c21_eff2_2msb,c20_eff2_2msb
//#
	{0xFD, 0x02, 0, 0},
	{0xBF, 0x01, 0, 0},   //# 2BF autosa_en
	{0xBE, 0xAA, 0, 0},   //# 2BE u_v_th
	{0xC0, 0xFF, 0, 0},   //# 2C0 y_p_th
	{0xC1, 0xFF, 0, 0},   //# 2C1 y_mean_th
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
	{0x8B, 0x00, 0, 0},   //# 28B gamma_pt0
	{0x8C, 0x0F, 0, 0},   //# 28C gamma_pt1
	{0x8D, 0x1F, 0, 0},   //# 28D gamma_pt2
	{0x8E, 0x3C, 0, 0},   //# 28E gamma_pt3
	{0x8F, 0x67, 0, 0},   //# 28F gamma_pt4
	{0x90, 0x85, 0, 0},   //# 290 gamma_pt5
	{0x91, 0x99, 0, 0},   //# 291 gamma_pt6
	{0x92, 0xA8, 0, 0},   //# 292 gamma_pt7
	{0x93, 0xB5, 0, 0},   //# 293 gamma_pt8
	{0x94, 0xBE, 0, 0},   //# 294 gamma_pt9
	{0x95, 0xC8, 0, 0},   //# 295 gamma_pt10
	{0x96, 0xD1, 0, 0},   //# 296 gamma_pt11
	{0x97, 0xD9, 0, 0},   //# 297 gamma_pt12
	{0x98, 0xE0, 0, 0},   //# 298 gamma_pt13
	{0x99, 0xE8, 0, 0},   //# 299 gamma_pt14
	{0x9A, 0xED, 0, 0},   //# 29A gamma_pt15
	{0x9B, 0xF3, 0, 0},   //# 29B gamma_pt16
//#
	{0xFD, 0x03, 0, 0},
	{0x8D, 0xF9, 0, 0},   //# 38D gamma_pt17
	{0x8E, 0xFF, 0, 0},   //# 38E gamma_pt18
//#
	{0xFD, 0x02, 0, 0},
	{0x78, 0x00, 0, 0},   //# 278 gamma_pt2_0
	{0x79, 0x0F, 0, 0},   //# 279 gamma_pt2_1
	{0x7A, 0x1F, 0, 0},   //# 27A gamma_pt2_2
	{0x7B, 0x3C, 0, 0},   //# 27B gamma_pt2_3
	{0x7C, 0x67, 0, 0},   //# 27C gamma_pt2_4
	{0x7D, 0x85, 0, 0},   //# 27D gamma_pt2_5
	{0x7E, 0x99, 0, 0},   //# 27E gamma_p2_6
	{0x7F, 0xA8, 0, 0},   //# 27F gamma_pt2_7
	{0x80, 0xB5, 0, 0},   //# 280 gamma_pt2_8
	{0x81, 0xBE, 0, 0},   //# 281 gamma_pt2_9
	{0x82, 0xC8, 0, 0},   //# 282 gamma_pt2_10
	{0x83, 0xD1, 0, 0},   //# 283 gamma_pt2_11
	{0x84, 0xD9, 0, 0},   //# 284 gamma_pt2_12
	{0x85, 0xE0, 0, 0},   //# 285 gamma_pt2_13
	{0x86, 0xE8, 0, 0},   //# 286 gamma_pt2_14
	{0x87, 0xED, 0, 0},   //# 287 gamma_pt2_15
	{0x88, 0xF3, 0, 0},   //# 288 gamma_pt2_16
	{0x89, 0xF9, 0, 0},   //# 289 gamma_pt2_17
	{0x8A, 0xFF, 0, 0},   //# 28A gamma_pt2_18
//#
	{0xFD, 0x03, 0, 0},
	{0x96, 0x46, 0, 0},   //# 396 ae time thr1
	{0x97, 0x28, 0, 0},   //# 397 ae time thr2
	{0x9F, 0x0A, 0, 0},   //# 39F gma_ratiok_fac
//#
	{0xFD, 0x02, 0, 0},
	{0xF4, 0x0B, 0, 0},   //# 2F4 lum_fcase_en,lum_down_en,outdoor_mode_en,mean_mode_reg
	{0xF0, 0xC7, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 exp_min_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
	{0x95, 0x20, 0, 0},   //# 395 rpc_min_indr
	{0x98, 0xC7, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_outdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x9C, 0x32, 0, 0},   //# 39C rpc_max_outdr
	{0x9D, 0x20, 0, 0},   //# 39D rpc_min_outdr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x55, 0x11, 0, 0},   //# 355 weight_w2,weight_w1
	{0x56, 0x11, 0, 0},   //# 356 weight_w4,weight_w3
//	{0x57, 0x03, 0, 0},   //# 357 weight_w5
	{0x57, 0x01, 0, 0},   //# 357 weight_w5(1001)
//#
	{0xFD, 0x02, 0, 0},
	{0xE0, 0x3E, 0, 0},   //# 2E0 rpc_1base_max
	{0xE1, 0x26, 0, 0},   //# 2E1 rpc_2base_max
	{0xE2, 0x2A, 0, 0},   //# 2E2 rpc_3base_max
	{0xE3, 0x26, 0, 0},   //# 2E3 rpc_4base_max
	{0xE4, 0x26, 0, 0},   //# 2E4 rpc_5base_max
	{0xE5, 0x24, 0, 0},   //# 2E5 rpc_6base_max
	{0xE6, 0x24, 0, 0},   //# 2E6 rpc_7base_max
	{0xE8, 0x22, 0, 0},   //# 2E8 rpc_8base_max
	{0xE9, 0x22, 0, 0},   //# 2E9 rpc_9base_max
	{0xEA, 0x22, 0, 0},   //# 2EA rpc_10base_max
	{0xEB, 0x20, 0, 0},   //# 2EB rpc_11base_max
	{0xF5, 0x20, 0, 0},   //# 2F5 rpc_12base_max
	{0xF6, 0x20, 0, 0},   //# 2F6 rpc_13base_max
	{0xF3, 0x03, 0, 0},   //# 2F3 uv_dif_en_outdoor,uv_dif_en_nr,uv_dif_en_dummy,uv_dif_en_low
	{0xB0, 0x00, 0, 0},   //# 2B0 uv_dif_gain_outdoor,uv_dif_gain_nr
	{0xB1, 0x12, 0, 0},   //# 2B1 uv_dif_gain_dummy,uv_dif_gain_low
//#
	{0xFD, 0x03, 0, 0},
	{0xDF, 0x0F, 0, 0},   //# 3DF sharpness
	{0xE7, 0x08, 0, 0},   //# 3E7 raw_sharp_range_base
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
	{0x70, 0x73, 0, 0},   //# 370 aec_gw_en,gw_uv_dif_en,gw_detect_en,gw_step
	{0x7B, 0x40, 0, 0},   //# 37B gw_mean_th
	{0x71, 0x2F, 0, 0},   //# 371 k_up
	{0x72, 0x0D, 0, 0},   //# 372 k_low
	{0x73, 0x0A, 0, 0},   //# 373 b_up
	{0x74, 0x2A, 0, 0},   //# 374 b_low
	{0x75, 0x04, 0, 0},   //# 375 uv_low_th
	{0x76, 0x20, 0, 0},   //# 376 y_low_th
	{0x77, 0x32, 0, 0},   //# 377 u_top
	{0x78, 0x00, 0, 0},   //# 378 u_bot
	{0x79, 0x28, 0, 0},   //# 379 v_top
	{0x7A, 0x00, 0, 0},   //# 37A v_bot
	{0x7C, 0x70, 0, 0},   //# 37C gw_offset
	{0x7D, 0x90, 0, 0},   //# 37D gw_y_bot
	{0x7E, 0xEF, 0, 0},   //# 37E gw_y_top
	{0x7F, 0x04, 0, 0},   //# 37F gw_uv_radius
	{0x80, 0x40, 0, 0},   //# 380 uv_fix_dat
	{0x81, 0x20, 0, 0},   //# 381 y_offset_th
	{0x8F, 0x12, 0, 0},   //# 38F wt_th
	{0xCE, 0x8C, 0, 0},   //# 3CE exp_heq_dummy[7:0]
	{0xCF, 0x0F, 0, 0},   //# 3CF exp_heq_dummy[12:8]
	{0xCD, 0x30, 0, 0},   //# 3CD rpc_heq_dummy
	{0xCA, 0x68, 0, 0},   //# 3CA mean_dummy_low
	{0xCB, 0x88, 0, 0},   //# 3CB mean_low_dummy
	{0xD0, 0x8C, 0, 0},   //# 3D0 exp_heq_low[7:0]
	{0xD1, 0x0F, 0, 0},   //# 3D1 exp_heq_low[12:8]
	{0xCC, 0xC0, 0, 0},   //# 3CC rpc_heq_low
	{0xD5, 0x80, 0, 0},   //# 3D5 mean_nr_dummy
	{0xD6, 0x90, 0, 0},   //# 3D6 mean_dummy_nr
	{0xD7, 0xC4, 0, 0},   //# 3D7 exp_nr_outd_8lsb
	{0xD8, 0x00, 0, 0},   //# 3D8 exp_nr_outd_5hsb
	{0xD9, 0xC7, 0, 0},   //# 3D9 exp_outd_nr_8lsb
	{0xDA, 0x00, 0, 0},   //# 3DA exp_outd_nr_5hsb
//#
	{0xFD, 0x02, 0, 0},
	{0xB2, 0x30, 0, 0},   //# 2B2 lum_limit
	{0xB3, 0x18, 0, 0},   //# 2B3 lum_set
	{0xB4, 0x60, 0, 0},   //# 2B4 black_vt
	{0xB5, 0x70, 0, 0},   //# 2B5 white_vt
	{0xCB, 0x00, 0, 0},   //# 2CB rg_clip_ga_outdoor
	{0xCC, 0x02, 0, 0},   //# 2CC rg_clip_ga_nr
	{0xCD, 0x05, 0, 0},   //# 2CD rg_clip_ga_dummy
	{0xCE, 0x08, 0, 0},   //# 2CE rg_clip_ga_low
	{0xCF, 0x00, 0, 0},   //# 2CF bg_clip_ga_outdoor
	{0xD0, 0x02, 0, 0},   //# 2D0 bg_clip_ga_nr
//#
	{0xFD, 0x03, 0, 0},
	{0x10, 0x05, 0, 0},   //# 310 bg_clip_ga_dummy
	{0x14, 0x08, 0, 0},   //# 314 bg_clip_ga_low
//#
	{0xFD, 0x02, 0, 0},
	{0x5B, 0x00, 0, 0},   //# 25B cnr_thr_outdoor
	{0x61, 0x08, 0, 0},   //# 261 cnr_thr_nr
	{0x77, 0x40, 0, 0},   //# 277 cnr_thr_dummy
	{0xCA, 0x60, 0, 0},   //# 2CA cnr_thr_low
//	{0xAB, 0x10, 0, 0},   //# 2AB ynr_thr_outdoor
	{0xAB, 0x00, 0, 0},   //# 2AB ynr_thr_outdoor(1001)
	{0xAC, 0x10, 0, 0},   //# 2AC ynr_thr_nr
	{0xAE, 0x60, 0, 0},   //# 2AE ynr_thr_dummy
	{0xAF, 0x40, 0, 0},   //# 2AF ynr_thr_low
	{0x60, 0x01, 0, 0},   //# 260 bpc_vt_dummy
	{0x70, 0x0A, 0, 0},   //# 270 Bpc_v
	{0x76, 0x00, 0, 0},   //# 276 blacklevelin
	{0xC5, 0x60, 0, 0},   //# 2C5 raw_gflt_fac_indoor
	{0xDC, 0x00, 0, 0},   //# 2DC buf_heq_offset
	{0xDD, 0x80, 0, 0},   //# 2DD ku
	{0xDE, 0x90, 0, 0},   //# 2DE kl
//#
	{0xFD, 0x03, 0, 0},
	{0x06, 0x00, 0, 0},   //# 306 ratio_row[9:8]
	{0x07, 0x50, 0, 0},   //# 307 ratio_row[7:0]
	{0x08, 0x00, 0, 0},   //# 308 ratio_col[9:8]
	{0x09, 0x50, 0, 0},   //# 309 ratio_col[7:0]
	{0x0A, 0x00, 0, 0},   //# 30A scalerownum[10:8]
	{0x0B, 0xF0, 0, 0},   //# 30B scalerownum[7:0]
	{0x0C, 0x01, 0, 0},   //# 30C scalecolnum[10:8]
	{0x0D, 0x40, 0, 0},   //# 30D scalecolnum[7:0]
	{0x0E, 0x01, 0, 0},   //# 30E resize_en
	{0x1C, 0xBA, 0, 0},   //# 31C f_limit_b
	{0x1D, 0x87, 0, 0},   //# 31D f_limit_r
	{0x41, 0x00, 0, 0},   //# 341 grgb_top_high_bit
	{0x42, 0x00, 0, 0},   //# 342 grgb_bot_high_bit
	{0x44, 0x0F, 0, 0},   //# 344 wb_num_th_light_s
	{0x4C, 0x48, 0, 0},   //# 34C raw_adt_fac_outdoor
	{0x4D, 0x48, 0, 0},   //# 34D raw_adt_fac_normal
	{0x4E, 0x48, 0, 0},   //# 34E raw_adt_fac_dummy
	{0x4F, 0x48, 0, 0},   //# 34F raw_adt_fac_low
	{0xC6, 0x40, 0, 0},   //# 3C6 pre_grgain
	{0xC7, 0x40, 0, 0},   //# 3C7 pre_rgain
	{0xC8, 0x40, 0, 0},   //# 3C8 pre_gbgain
	{0xC9, 0x40, 0, 0},   //# 3C9 pre_bgain
	{0xE2, 0x40, 0, 0},   //# 3E2 raw_sharp_y_base
	{0xE3, 0x10, 0, 0},   //# 3E3 raw_sharp_y_min
	{0xE4, 0xE0, 0, 0},   //# 3E4 raw_sharp_y_max
	{0xE5, 0x30, 0, 0},   //# 3E5 raw_sharp_rangek_neg
	{0xE6, 0x20, 0, 0},   //# 3E6 raw_sharp_rangek_pos
//#
	{0xFD, 0x02, 0, 0},
	{0x32, 0x0D, 0, 0},   //# 232 auto_mode
	{0x33, 0xEF, 0, 0},   //# 233 lsc_bpc_en
	{0x34, 0xFF, 0, 0},   //# 234 buf_isp_mode
	{0xFB, 0x00, 0, 0},   //# 2FB blackgain_en,bl_bpc_en,abl
	{0x36, 0x00, 0, 0},   //# 236 buf_outmode2
};

//----- VGA -------
static struct reg_value rnss2e1_setting_15fps_VGA_640_480[] = {
	{0xFD, 0x02, 0, 0},
	{0x36, 0x00, 0, 0},   //# 236 buf_outmode2
//#
	{0xFD, 0x00, 0, 0},
	{0x10, 0x3F, 0, 0},   //# 010 clk_mode
	{0x11, 0x40, 0, 0},   //# 011 pclk_inv,pclk_gate_en,pclk_ctrl,isp_clk_ctrl
	{0x20, 0x02, 0, 0},   //# 020 ds_data,out_end_high8,out_end_low2,out_ens
	{0x21, 0x03, 0, 0},   //# 021 pe_hvp,pe_data,ds_s,buf_dis_s,buf_dis_d
//#
	{0xFD, 0x01, 0, 0},
	{0x03, 0x01, 0, 0},   //# 103 buf_exp_5msb
//	{0x04, 0x90, 0, 0},   //# 104 buf_exp_8lsb
	{0x04, 0x2C, 0, 0},   //# 104 buf_exp_8lsb(1001)
	{0x09, 0x00, 0, 0},   //# 109 hblank_4msb
	{0x0A, 0x4E, 0, 0},   //# 10A hblank_8lsb
//#
	{0xFD, 0x00, 0, 0},
	{0x0E, 0x40, 0, 0},   //# 00E pd
//#
	{0xFD, 0x01, 0, 0},
	{0x0E, 0x00, 0, 0},   //# 10E p0
	{0x0F, 0x18, 0, 0},   //# 10F p1
	{0x10, 0x10, 0, 0},   //# 110 p2
	{0x11, 0x03, 0, 0},   //# 111 p3
	{0x12, 0x18, 0, 0},   //# 112 p4
	{0x13, 0x10, 0, 0},   //# 113 p5
	{0x14, 0x15, 0, 0},   //# 114 p6
	{0x15, 0x01, 0, 0},   //# 115 p7
	{0x16, 0x02, 0, 0},   //# 116 p8
	{0x17, 0x10, 0, 0},   //# 117 p9
	{0x18, 0x00, 0, 0},   //# 118 p10_2msb
	{0x19, 0x1A, 0, 0},   //# 119 p10_8lsb
	{0x1A, 0x00, 0, 0},   //# 11A p11_2msb
	{0x1B, 0x1C, 0, 0},   //# 11B p11_8lsb
	{0x50, 0x00, 0, 0},   //# 150 p12_2msb
	{0x51, 0x1D, 0, 0},   //# 151 p12_8lsb
	{0x52, 0x15, 0, 0},   //# 152 P13
	{0x2A, 0x02, 0, 0},   //# 12A p16
	{0x53, 0x00, 0, 0},   //# 153 p17_2msb
	{0x54, 0x11, 0, 0},   //# 154 p17_8lsb
	{0x55, 0x12, 0, 0},   //# 155 p18
	{0x56, 0x02, 0, 0},   //# 156 p19
	{0x57, 0x02, 0, 0},   //# 157 p20
	{0x58, 0x00, 0, 0},   //# 158 p21
//#
	{0xFD, 0x00, 0, 0},
	{0x12, 0x04, 0, 0},   //# 012 pll_bias_ctl,pll_delay
	{0x13, 0x04, 0, 0},   //# 013 mipi_pattern_en,pll_test_en,mipi_en
	{0x14, 0x00, 0, 0},   //# 014 pclk_gate,timer_clk_gate,dclk_gate
	{0x15, 0x00, 0, 0},   //# 015 pclk_pha_adj
//#
	{0xFD, 0x01, 0, 0},
//	{0x1C, 0x5C, 0, 0},   //# 11C two_timing_en,FPN_33ms_X,pwd_asp_timing_sel,Channel-timing
	{0x1C, 0x7C, 0, 0},   //# 11C two_timing_en,FPN_33ms_X,pwd_asp_timing_sel,Channel-timing
	{0x21, 0x44, 0, 0},   //# 121 adc_vcm_opin_ctl,adc_vcm_opin_c,col_clk_delay
	{0x22, 0x04, 0, 0},   //# 122 pga_bias_ctl,col_ctrl
	{0x25, 0x00, 0, 0},   //# 125 adc_range_ctl,adc_vcm_ctl,asp_delay
	{0x26, 0x26, 0, 0},   //# 126 adc_dig_offset,sw_delay
	{0x27, 0x6D, 0, 0},   //# 127 delay,black_en,adc_dref_cal,adc_g2x_en,adc_offset_en
	{0x2B, 0x66, 0, 0},   //# 12B adc_offset_ctl_buf_up,adc_offset_ctl_buf_dn
	{0x2C, 0x3F, 0, 0},   //# 12C strobe_en,bl_da
	{0x2D, 0x40, 0, 0},   //# 12D adc_bias_stage,adc_bias_vref
	{0x2E, 0x0D, 0, 0},   //# 12E dout_sel,strobe_sel
//	{0x40, 0xF0, 0, 0},   //# 140 vfpn_bpc_en,vfpn_minus_en
	{0x40, 0xF3, 0, 0},   //# 140 vfpn_bpc_en,vfpn_minus_en
	{0x41, 0x60, 0, 0},   //# 141 vfpn_bpc_th_x1
	{0x42, 0x50, 0, 0},   //# 142 vfpn_bpc_th_x2
	{0x43, 0x28, 0, 0},   //# 143 vfpn_bpc_in_x1
	{0x44, 0x28, 0, 0},   //# 144 vfpn_bpc_in_x2
//	{0x45, 0x0C, 0, 0},   //# 145 vfpn_delta
//	{0x45, 0x06, 0, 0},   //# 145 vfpn_delta(0830)
	{0x45, 0x00, 0, 0},   //# 145 vfpn_delta(0921)
	{0x31, 0x14, 0, 0},   //# 131 buf_comm_ctrl
//#
	{0xFD, 0x02, 0, 0},
	{0x35, 0x40, 0, 0},   //# 235 buf_outmode1
	{0x31, 0x10, 0, 0},   //# 231 digital_gain
	{0x47, 0x00, 0, 0},   //# 247 v_start_3msb
	{0x48, 0x00, 0, 0},   //# 248 v_start_8lsb
	{0x49, 0x02, 0, 0},   //# 249 v_size_3msb
	{0x4A, 0x58, 0, 0},   //# 24A v_size_8lsb
	{0x4B, 0x00, 0, 0},   //# 24B h_start_3msb
	{0x4C, 0x00, 0, 0},   //# 24C h_start_8lsb
	{0x4D, 0x03, 0, 0},   //# 24D h_size_3msb
	{0x4E, 0x20, 0, 0},   //# 24E h_size_8lsb
//	{0x65, 0x08, 0, 0},   //# 265 blue_suboffset
//	{0x66, 0x06, 0, 0},   //# 266 red_suboffset
//	{0x67, 0x07, 0, 0},   //# 267 gr_suboffset
//	{0x68, 0x07, 0, 0},   //# 268 gb_suboffset
//	{0x65, 0x09, 0, 0},   //# 265 blue_suboffset(0830)
//	{0x66, 0x07, 0, 0},   //# 266 red_suboffset(0830)
//	{0x67, 0x08, 0, 0},   //# 267 gr_suboffset(0830)
//	{0x68, 0x08, 0, 0},   //# 268 gb_suboffset(0830)
	{0x65, 0x0F, 0, 0},   //# 265 blue_suboffset(0921)
	{0x66, 0x0D, 0, 0},   //# 266 red_suboffset(0921)
	{0x67, 0x0E, 0, 0},   //# 267 gr_suboffset(0921)
	{0x68, 0x0E, 0, 0},   //# 268 gb_suboffset(0921)
	{0x5F, 0x02, 0, 0},   //# 25F demo_gain_order,bayer_order
	{0x32, 0x00, 0, 0},   //# 232 auto_mode
	{0x33, 0xEF, 0, 0},   //# 233 lsc_bpc_en
	{0xA4, 0xFF, 0, 0},   //# 2A4 lsc_gain_max
//#
	{0xFD, 0x03, 0, 0},
	{0x66, 0x19, 0, 0},   //# 366 Lsc_rsy_u
	{0x6A, 0x1B, 0, 0},   //# 36A Lsc_gsy_u
	{0x6E, 0x14, 0, 0},   //# 36E Lsc_bsy_u
	{0x67, 0x19, 0, 0},   //# 367 Lsc_rsy_d
	{0x6B, 0x12, 0, 0},   //# 36B Lsc_gsy_d
	{0x6F, 0x14, 0, 0},   //# 36F Lsc_bsy_d
	{0x64, 0x1D, 0, 0},   //# 364 Lsc_rsx_l
	{0x68, 0x18, 0, 0},   //# 368 Lsc_gsx_l
	{0x6C, 0x14, 0, 0},   //# 36C Lsc_bsx_l
	{0x65, 0x15, 0, 0},   //# 365 Lsc_rsx_r
	{0x69, 0x12, 0, 0},   //# 369 Lsc_gsx_r
	{0x6D, 0x0E, 0, 0},   //# 36D Lsc_bsx_r
	{0xB8, 0x08, 0, 0},   //# 3B8 Lsc_rxy_lu
	{0xBC, 0x08, 0, 0},   //# 3BC Lsc_gxy_lu
	{0xC0, 0x08, 0, 0},   //# 3C0 Lsc_bxy_lu
	{0xB9, 0x08, 0, 0},   //# 3B9 Lsc_rxy_ru
	{0xBD, 0x08, 0, 0},   //# 3BD Lsc_gxy_ru
	{0xC1, 0x08, 0, 0},   //# 3C1 Lsc_bxy_ru
	{0xBA, 0x08, 0, 0},   //# 3BA Lsc_rxy_ld
	{0xBE, 0x08, 0, 0},   //# 3BE Lsc_gxy_ld
	{0xC2, 0x08, 0, 0},   //# 3C2 Lsc_bxy_ld
	{0xBB, 0x08, 0, 0},   //# 3BB Lsc_rxy_rd
	{0xBF, 0x08, 0, 0},   //# 3BF Lsc_gxy_rd
	{0xC3, 0x08, 0, 0},   //# 3C3 Lsc_bxy_rd
//#
	{0xFD, 0x02, 0, 0},
	{0x51, 0x00, 0, 0},   //# 251 bpc_vt_outdoor
	{0x52, 0x00, 0, 0},   //# 252 bpc_vt_normal
	{0x53, 0x00, 0, 0},   //# 253 bpc_vt_low_light
	{0x54, 0x00, 0, 0},   //# 254 bpc_wt_eff
	{0x55, 0xFF, 0, 0},   //# 255 bpc_dt_eff
//	{0x45, 0x00, 0, 0},   //# 245 bpc_range_ratio_outdoor,pc_range_ratio_nr
//	{0x46, 0x09, 0, 0},   //# 246 bpc_range_ratio_dummy,bpc_range_ratio_low
	{0x45, 0x13, 0, 0},   //# 245 bpc_range_ratio_outdoor,pc_range_ratio_nr (1001)
	{0x46, 0x49, 0, 0},   //# 246 bpc_range_ratio_dummy,bpc_range_ratio_low (1001)
	{0x69, 0x00, 0, 0},   //# 269 bpc_range_thr_outdoor
	{0x6A, 0x00, 0, 0},   //# 26A bpc_range_thr_nr
	{0x6B, 0x00, 0, 0},   //# 26B bpc_range_thr_dummy
	{0x6C, 0x00, 0, 0},   //# 26C bpc_range_thr_low
//#
	{0xFD, 0x03, 0, 0},
	{0xDE, 0x0F, 0, 0},   //# 3DE raw_denoise_en_outdoor,raw_denoise_en_nr,raw_denoise_en_dummy,raw_denoise_en_low
//#
	{0xFD, 0x02, 0, 0},
	{0x57, 0x04, 0, 0},   //# 257 raw_dif_thr_outdoor
	{0x58, 0x04, 0, 0},   //# 258 raw_dif_thr_normal
	{0x56, 0x0A, 0, 0},   //# 256 raw_dif_thr_dummy
	{0x59, 0x08, 0, 0},   //# 259 raw_dif_thr_low_light
	{0x4F, 0xE0, 0, 0},   //# 24F raw_gf_fac_outdoor
	{0xC3, 0xE0, 0, 0},   //# 2C3 raw_gf_fac_indoor
	{0x3F, 0xC0, 0, 0},   //# 23F raw_gf_fac_dummy
	{0x42, 0x40, 0, 0},   //# 242 raw_gf_fac_low
	{0x5A, 0xE0, 0, 0},   //# 25A raw_rb_fac_outdoor
	{0xC4, 0xE0, 0, 0},   //# 2C4 raw_rb_fac_indoor
	{0x43, 0xC0, 0, 0},   //# 243 raw_rb_fac_dummy
	{0xAD, 0x40, 0, 0},   //# 2AD raw_rb_fac_low
	{0xC2, 0x15, 0, 0},   //# 2C2 gf_ratiok_fac
//#
	{0xFD, 0x03, 0, 0},
	{0x50, 0x00, 0, 0},   //# 350 raw_grgb_thr_outdoor
	{0x51, 0x00, 0, 0},   //# 351 raw_grgb_thr_normal
	{0x52, 0x08, 0, 0},   //# 352 raw_grgb_thr_dummy
	{0x53, 0x08, 0, 0},   //# 353 raw_grgb_thr_low
//#
	{0xFD, 0x02, 0, 0},
	{0xB6, 0xE0, 0, 0},   //# 2B6 raw_gflt_fac_outdoor
	{0xB7, 0xC0, 0, 0},   //# 2B7 raw_gflt_fac_nr
	{0xB8, 0xA0, 0, 0},   //# 2B8 raw_gflt_fac_dummy
	{0xB9, 0x20, 0, 0},   //# 2B9 raw_gflt_fac_low
//#
	{0xFD, 0x03, 0, 0},
	{0x11, 0x1F, 0, 0},   //# 311 rg_dif_th
	{0x12, 0x1F, 0, 0},   //# 312 bg_dif_th
	{0x16, 0x1C, 0, 0},   //# 316 rgb_limit
	{0x18, 0x00, 0, 0},   //# 318 br_offset_f
	{0x19, 0x00, 0, 0},   //# 319 br_offset
	{0x1B, 0x80, 0, 0},   //# 31B rg_base
	{0x1A, 0x80, 0, 0},   //# 31A bg_base
	{0x43, 0x80, 0, 0},   //# 343 channel_sel,test_awb
	{0x1E, 0x17, 0, 0},   //# 31E wb_fine_gain_step,wb_rough_gain_step
	{0x1F, 0x19, 0, 0},   //# 31F wb_dif_fine_th,wb_dif_rough_th
//	{0x28, 0x9B, 0, 0},   //# 328 buf_rgain
//	{0x29, 0xA0, 0, 0},   //# 329 buf_bgain
	{0x28, 0xA2, 0, 0},   //# 328 buf_rgain(1001)
	{0x29, 0xA4, 0, 0},   //# 329 buf_bgain(1001)
//#
	{0xFD, 0x02, 0, 0},
	{0xE7, 0x03, 0, 0},   //# 2E7 reg_renew
	{0xE7, 0x00, 0, 0},   //# 2E7 reg_renew
//#
	{0xFD, 0x03, 0, 0},
	{0x2A, 0xF0, 0, 0},   //# 32A y_top_th
	{0x2B, 0x10, 0, 0},   //# 32B y_bot_th
	{0x2E, 0x04, 0, 0},   //# 32E rg_limit_log
	{0x2F, 0x16, 0, 0},   //# 32F bg_limit_log
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x80, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x80, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0x83, 0x70, 0, 0},   //# 383 skin_num_th
	{0x13, 0x43, 0, 0},   //# 313 awb_grey_en,awb_skin_en
	{0x24, 0x06, 0, 0},   //# 324 short_exp_th
	{0x25, 0x80, 0, 0},   //# 325 sp_rg_base
	{0x26, 0x80, 0, 0},   //# 326 sp_bg_base
	{0x35, 0xB2, 0, 0},   //# 335 d65_rg_bot
	{0x36, 0xCA, 0, 0},   //# 336 d65_rg_top
//	{0x37, 0x7C, 0, 0},   //# 337 d65_bg_bot
	{0x37, 0x73, 0, 0},   //# 337 d65_bg_bot(1001)
	{0x38, 0x94, 0, 0},   //# 338 d65_bg_top
//	{0x31, 0x7B, 0, 0},   //# 331 f_rg_bot
//	{0x32, 0x93, 0, 0},   //# 332 f_rg_top
//	{0x33, 0xAE, 0, 0},   //# 333 f_bg_bot
//	{0x34, 0xC6, 0, 0},   //# 334 f_bg_top
	{0x31, 0x60, 0, 0},   //# 331 f_rg_bot(1010)
	{0x32, 0x98, 0, 0},   //# 332 f_rg_top(1010)
	{0x33, 0xA8, 0, 0},   //# 333 f_bg_bot(1010)
	{0x34, 0xD8, 0, 0},   //# 334 f_bg_top(1010)
	{0x3D, 0x9C, 0, 0},   //# 33D cwf_rg_bot
	{0x3E, 0xB4, 0, 0},   //# 33E cwf_rg_top
	{0x3F, 0xA4, 0, 0},   //# 33F cwf_bg_bot
	{0x40, 0xBC, 0, 0},   //# 340 cwf_bg_top
	{0x39, 0x8A, 0, 0},   //# 339 tl84_rg_bot
	{0x3A, 0xA2, 0, 0},   //# 33A tl84_rg_top
	{0x3B, 0x9E, 0, 0},   //# 33B tl84_bg_bot
	{0x3C, 0xB6, 0, 0},   //# 33C tl84_bg_top
	{0xA0, 0xA6, 0, 0},   //# 3A0 c00_eff1_8lsb
	{0xA1, 0xCD, 0, 0},   //# 3A1 c01_eff1_8lsb
	{0xA2, 0x0C, 0, 0},   //# 3A2 c02_eff1_8lsb
	{0xA3, 0x06, 0, 0},   //# 3A3 c10_eff1_8lsb
	{0xA4, 0x8C, 0, 0},   //# 3A4 c11_eff1_8lsb
	{0xA5, 0xED, 0, 0},   //# 3A5 c12_eff1_8lsb
	{0xA6, 0x00, 0, 0},   //# 3A6 c20_eff1_8lsb
	{0xA7, 0xE7, 0, 0},   //# 3A7 c21_eff1_8lsb
	{0xA8, 0x99, 0, 0},   //# 3A8 c22_eff1_8lsb
	{0xA9, 0x0C, 0, 0},   //# 3A9 c02_eff1_2msb,c01_eff1_2msb,c00_eff1_2msb
	{0xAA, 0x30, 0, 0},   //# 3AA c12_eff1_2msb,c11_eff1_2msb,c10_eff1_2msb
	{0xAB, 0x0C, 0, 0},   //# 3AB c22_eff1_2msb,c21_eff1_2msb,c20_eff1_2msb
	{0xAC, 0x8C, 0, 0},   //# 3AC c00_eff2_8lsb
	{0xAD, 0xF4, 0, 0},   //# 3AD c01_eff2_8lsb
	{0xAE, 0x00, 0, 0},   //# 3AE c02_eff2_8lsb
	{0xAF, 0xFA, 0, 0},   //# 3AF c10_eff2_8lsb
	{0xB0, 0x8C, 0, 0},   //# 3B0 c11_eff2_8lsb
	{0xB1, 0xFA, 0, 0},   //# 3B1 c12_eff2_8lsb
	{0xB2, 0x0C, 0, 0},   //# 3B2 c20_eff2_8lsb
	{0xB3, 0xF4, 0, 0},   //# 3B3 c21_eff2_8lsb
	{0xB4, 0x80, 0, 0},   //# 3B4 c22_eff2_8lsb
	{0xB5, 0x0C, 0, 0},   //# 3B5 c02_eff2_2msb,c01_eff2_2msb,c00_eff2_2msb
	{0xB6, 0x33, 0, 0},   //# 3B6 c12_eff2_2msb,c11_eff2_2msb,c10_eff2_2msb
	{0xB7, 0x0C, 0, 0},   //# 3B7 c22_eff2_2msb,c21_eff2_2msb,c20_eff2_2msb
//#
	{0xFD, 0x02, 0, 0},
	{0xBF, 0x01, 0, 0},   //# 2BF autosa_en
	{0xBE, 0xAA, 0, 0},   //# 2BE u_v_th
	{0xC0, 0xFF, 0, 0},   //# 2C0 y_p_th
	{0xC1, 0xFF, 0, 0},   //# 2C1 y_mean_th
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
	{0x8B, 0x00, 0, 0},   //# 28B gamma_pt0
	{0x8C, 0x0F, 0, 0},   //# 28C gamma_pt1
	{0x8D, 0x1F, 0, 0},   //# 28D gamma_pt2
	{0x8E, 0x3C, 0, 0},   //# 28E gamma_pt3
	{0x8F, 0x67, 0, 0},   //# 28F gamma_pt4
	{0x90, 0x85, 0, 0},   //# 290 gamma_pt5
	{0x91, 0x99, 0, 0},   //# 291 gamma_pt6
	{0x92, 0xA8, 0, 0},   //# 292 gamma_pt7
	{0x93, 0xB5, 0, 0},   //# 293 gamma_pt8
	{0x94, 0xBE, 0, 0},   //# 294 gamma_pt9
	{0x95, 0xC8, 0, 0},   //# 295 gamma_pt10
	{0x96, 0xD1, 0, 0},   //# 296 gamma_pt11
	{0x97, 0xD9, 0, 0},   //# 297 gamma_pt12
	{0x98, 0xE0, 0, 0},   //# 298 gamma_pt13
	{0x99, 0xE8, 0, 0},   //# 299 gamma_pt14
	{0x9A, 0xED, 0, 0},   //# 29A gamma_pt15
	{0x9B, 0xF3, 0, 0},   //# 29B gamma_pt16
//#
	{0xFD, 0x03, 0, 0},
	{0x8D, 0xF9, 0, 0},   //# 38D gamma_pt17
	{0x8E, 0xFF, 0, 0},   //# 38E gamma_pt18
//#
	{0xFD, 0x02, 0, 0},
	{0x78, 0x00, 0, 0},   //# 278 gamma_pt2_0
	{0x79, 0x0F, 0, 0},   //# 279 gamma_pt2_1
	{0x7A, 0x1F, 0, 0},   //# 27A gamma_pt2_2
	{0x7B, 0x3C, 0, 0},   //# 27B gamma_pt2_3
	{0x7C, 0x67, 0, 0},   //# 27C gamma_pt2_4
	{0x7D, 0x85, 0, 0},   //# 27D gamma_pt2_5
	{0x7E, 0x99, 0, 0},   //# 27E gamma_p2_6
	{0x7F, 0xA8, 0, 0},   //# 27F gamma_pt2_7
	{0x80, 0xB5, 0, 0},   //# 280 gamma_pt2_8
	{0x81, 0xBE, 0, 0},   //# 281 gamma_pt2_9
	{0x82, 0xC8, 0, 0},   //# 282 gamma_pt2_10
	{0x83, 0xD1, 0, 0},   //# 283 gamma_pt2_11
	{0x84, 0xD9, 0, 0},   //# 284 gamma_pt2_12
	{0x85, 0xE0, 0, 0},   //# 285 gamma_pt2_13
	{0x86, 0xE8, 0, 0},   //# 286 gamma_pt2_14
	{0x87, 0xED, 0, 0},   //# 287 gamma_pt2_15
	{0x88, 0xF3, 0, 0},   //# 288 gamma_pt2_16
	{0x89, 0xF9, 0, 0},   //# 289 gamma_pt2_17
	{0x8A, 0xFF, 0, 0},   //# 28A gamma_pt2_18
//#
	{0xFD, 0x03, 0, 0},
	{0x96, 0x46, 0, 0},   //# 396 ae time thr1
	{0x97, 0x28, 0, 0},   //# 397 ae time thr2
	{0x9F, 0x0A, 0, 0},   //# 39F gma_ratiok_fac
//#
	{0xFD, 0x02, 0, 0},
	{0xF4, 0x0B, 0, 0},   //# 2F4 lum_fcase_en,lum_down_en,outdoor_mode_en,mean_mode_reg
	{0xF0, 0x64, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 exp_min_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
	{0x95, 0x20, 0, 0},   //# 395 rpc_min_indr
	{0x98, 0x64, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_outdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x9C, 0x32, 0, 0},   //# 39C rpc_max_outdr
	{0x9D, 0x20, 0, 0},   //# 39D rpc_min_outdr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x55, 0x11, 0, 0},   //# 355 weight_w2,weight_w1
	{0x56, 0x11, 0, 0},   //# 356 weight_w4,weight_w3
//	{0x57, 0x03, 0, 0},   //# 357 weight_w5
	{0x57, 0x01, 0, 0},   //# 357 weight_w5(1001)
//#
	{0xFD, 0x02, 0, 0},
	{0xE0, 0x3E, 0, 0},   //# 2E0 rpc_1base_max
	{0xE1, 0x26, 0, 0},   //# 2E1 rpc_2base_max
	{0xE2, 0x2A, 0, 0},   //# 2E2 rpc_3base_max
	{0xE3, 0x26, 0, 0},   //# 2E3 rpc_4base_max
	{0xE4, 0x26, 0, 0},   //# 2E4 rpc_5base_max
	{0xE5, 0x24, 0, 0},   //# 2E5 rpc_6base_max
	{0xE6, 0x24, 0, 0},   //# 2E6 rpc_7base_max
	{0xE8, 0x22, 0, 0},   //# 2E8 rpc_8base_max
	{0xE9, 0x22, 0, 0},   //# 2E9 rpc_9base_max
	{0xEA, 0x22, 0, 0},   //# 2EA rpc_10base_max
	{0xEB, 0x20, 0, 0},   //# 2EB rpc_11base_max
	{0xF5, 0x20, 0, 0},   //# 2F5 rpc_12base_max
	{0xF6, 0x20, 0, 0},   //# 2F6 rpc_13base_max
	{0xF3, 0x03, 0, 0},   //# 2F3 uv_dif_en_outdoor,uv_dif_en_nr,uv_dif_en_dummy,uv_dif_en_low
	{0xB0, 0x00, 0, 0},   //# 2B0 uv_dif_gain_outdoor,uv_dif_gain_nr
	{0xB1, 0x12, 0, 0},   //# 2B1 uv_dif_gain_dummy,uv_dif_gain_low
//#
	{0xFD, 0x03, 0, 0},
	{0xDF, 0x0F, 0, 0},   //# 3DF sharpness
	{0xE7, 0x08, 0, 0},   //# 3E7 raw_sharp_range_base
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
	{0x70, 0x73, 0, 0},   //# 370 aec_gw_en,gw_uv_dif_en,gw_detect_en,gw_step
	{0x7B, 0x40, 0, 0},   //# 37B gw_mean_th
	{0x71, 0x2F, 0, 0},   //# 371 k_up
	{0x72, 0x0D, 0, 0},   //# 372 k_low
	{0x73, 0x0A, 0, 0},   //# 373 b_up
	{0x74, 0x2A, 0, 0},   //# 374 b_low
	{0x75, 0x04, 0, 0},   //# 375 uv_low_th
	{0x76, 0x20, 0, 0},   //# 376 y_low_th
	{0x77, 0x32, 0, 0},   //# 377 u_top
	{0x78, 0x00, 0, 0},   //# 378 u_bot
	{0x79, 0x28, 0, 0},   //# 379 v_top
	{0x7A, 0x00, 0, 0},   //# 37A v_bot
	{0x7C, 0x70, 0, 0},   //# 37C gw_offset
	{0x7D, 0x90, 0, 0},   //# 37D gw_y_bot
	{0x7E, 0xEF, 0, 0},   //# 37E gw_y_top
	{0x7F, 0x04, 0, 0},   //# 37F gw_uv_radius
	{0x80, 0x40, 0, 0},   //# 380 uv_fix_dat
	{0x81, 0x20, 0, 0},   //# 381 y_offset_th
	{0x8F, 0x12, 0, 0},   //# 38F wt_th
	{0xCE, 0xD0, 0, 0},   //# 3CE exp_heq_dummy[7:0]
	{0xCF, 0x07, 0, 0},   //# 3CF exp_heq_dummy[12:8]
	{0xCD, 0x30, 0, 0},   //# 3CD rpc_heq_dummy
	{0xCA, 0x68, 0, 0},   //# 3CA mean_dummy_low
	{0xCB, 0x88, 0, 0},   //# 3CB mean_low_dummy
	{0xD0, 0xD0, 0, 0},   //# 3D0 exp_heq_low[7:0]
	{0xD1, 0x07, 0, 0},   //# 3D1 exp_heq_low[12:8]
	{0xCC, 0xC0, 0, 0},   //# 3CC rpc_heq_low
	{0xD5, 0x80, 0, 0},   //# 3D5 mean_nr_dummy
	{0xD6, 0x90, 0, 0},   //# 3D6 mean_dummy_nr
	{0xD7, 0x61, 0, 0},   //# 3D7 exp_nr_outd_8lsb
	{0xD8, 0x00, 0, 0},   //# 3D8 exp_nr_outd_5hsb
	{0xD9, 0x64, 0, 0},   //# 3D9 exp_outd_nr_8lsb
	{0xDA, 0x00, 0, 0},   //# 3DA exp_outd_nr_5hsb
//#
	{0xFD, 0x02, 0, 0},
	{0xB2, 0x30, 0, 0},   //# 2B2 lum_limit
	{0xB3, 0x18, 0, 0},   //# 2B3 lum_set
	{0xB4, 0x60, 0, 0},   //# 2B4 black_vt
	{0xB5, 0x70, 0, 0},   //# 2B5 white_vt
	{0xCB, 0x00, 0, 0},   //# 2CB rg_clip_ga_outdoor
	{0xCC, 0x02, 0, 0},   //# 2CC rg_clip_ga_nr
	{0xCD, 0x05, 0, 0},   //# 2CD rg_clip_ga_dummy
	{0xCE, 0x08, 0, 0},   //# 2CE rg_clip_ga_low
	{0xCF, 0x00, 0, 0},   //# 2CF bg_clip_ga_outdoor
	{0xD0, 0x02, 0, 0},   //# 2D0 bg_clip_ga_nr
//#
	{0xFD, 0x03, 0, 0},
	{0x10, 0x05, 0, 0},   //# 310 bg_clip_ga_dummy
	{0x14, 0x08, 0, 0},   //# 314 bg_clip_ga_low
//#
	{0xFD, 0x02, 0, 0},
	{0x5B, 0x00, 0, 0},   //# 25B cnr_thr_outdoor
	{0x61, 0x08, 0, 0},   //# 261 cnr_thr_nr
	{0x77, 0x40, 0, 0},   //# 277 cnr_thr_dummy
	{0xCA, 0x60, 0, 0},   //# 2CA cnr_thr_low
//	{0xAB, 0x10, 0, 0},   //# 2AB ynr_thr_outdoor
	{0xAB, 0x00, 0, 0},   //# 2AB ynr_thr_outdoor(1001)
	{0xAC, 0x10, 0, 0},   //# 2AC ynr_thr_nr
	{0xAE, 0x60, 0, 0},   //# 2AE ynr_thr_dummy
	{0xAF, 0x40, 0, 0},   //# 2AF ynr_thr_low
	{0x60, 0x01, 0, 0},   //# 260 bpc_vt_dummy
	{0x70, 0x0A, 0, 0},   //# 270 Bpc_v
	{0x76, 0x00, 0, 0},   //# 276 blacklevelin
	{0xC5, 0x60, 0, 0},   //# 2C5 raw_gflt_fac_indoor
	{0xDC, 0x00, 0, 0},   //# 2DC buf_heq_offset
	{0xDD, 0x80, 0, 0},   //# 2DD ku
	{0xDE, 0x90, 0, 0},   //# 2DE kl
//#
	{0xFD, 0x03, 0, 0},
	{0x06, 0x00, 0, 0},   //# 306 ratio_row[9:8]
	{0x07, 0x28, 0, 0},   //# 307 ratio_row[7:0]
	{0x08, 0x00, 0, 0},   //# 308 ratio_col[9:8]
	{0x09, 0x28, 0, 0},   //# 309 ratio_col[7:0]
	{0x0A, 0x01, 0, 0},   //# 30A scalerownum[10:8]
	{0x0B, 0xE0, 0, 0},   //# 30B scalerownum[7:0]
	{0x0C, 0x02, 0, 0},   //# 30C scalecolnum[10:8]
	{0x0D, 0x80, 0, 0},   //# 30D scalecolnum[7:0]
	{0x0E, 0x01, 0, 0},   //# 30E resize_en
	{0x1C, 0xBA, 0, 0},   //# 31C f_limit_b
	{0x1D, 0x87, 0, 0},   //# 31D f_limit_r
	{0x41, 0x00, 0, 0},   //# 341 grgb_top_high_bit
	{0x42, 0x00, 0, 0},   //# 342 grgb_bot_high_bit
	{0x44, 0x0F, 0, 0},   //# 344 wb_num_th_light_s
	{0x4C, 0x48, 0, 0},   //# 34C raw_adt_fac_outdoor
	{0x4D, 0x48, 0, 0},   //# 34D raw_adt_fac_normal
	{0x4E, 0x48, 0, 0},   //# 34E raw_adt_fac_dummy
	{0x4F, 0x48, 0, 0},   //# 34F raw_adt_fac_low
	{0xC6, 0x40, 0, 0},   //# 3C6 pre_grgain
	{0xC7, 0x40, 0, 0},   //# 3C7 pre_rgain
	{0xC8, 0x40, 0, 0},   //# 3C8 pre_gbgain
	{0xC9, 0x40, 0, 0},   //# 3C9 pre_bgain
	{0xE2, 0x40, 0, 0},   //# 3E2 raw_sharp_y_base
	{0xE3, 0x10, 0, 0},   //# 3E3 raw_sharp_y_min
	{0xE4, 0xE0, 0, 0},   //# 3E4 raw_sharp_y_max
	{0xE5, 0x30, 0, 0},   //# 3E5 raw_sharp_rangek_neg
	{0xE6, 0x20, 0, 0},   //# 3E6 raw_sharp_rangek_pos
//#
	{0xFD, 0x02, 0, 0},
	{0x32, 0x0D, 0, 0},   //# 232 auto_mode
	{0x33, 0xEF, 0, 0},   //# 233 lsc_bpc_en
	{0x34, 0xFF, 0, 0},   //# 234 buf_isp_mode
	{0xFB, 0x00, 0, 0},   //# 2FB blackgain_en,bl_bpc_en,abl
	{0x36, 0x00, 0, 0},   //# 236 buf_outmode2
};

static struct reg_value rnss2e1_setting_30fps_VGA_640_480[] = {
	{0xFD, 0x02, 0, 0},
	{0x36, 0x00, 0, 0},   //# 236 buf_outmode2
//#
	{0xFD, 0x00, 0, 0},
	{0x10, 0x1F, 0, 0},   //# 010 clk_mode
	{0x11, 0x40, 0, 0},   //# 011 pclk_inv,pclk_gate_en,pclk_ctrl,isp_clk_ctrl
	{0x20, 0x02, 0, 0},   //# 020 ds_data,out_end_high8,out_end_low2,out_ens
	{0x21, 0x03, 0, 0},   //# 021 pe_hvp,pe_data,ds_s,buf_dis_s,buf_dis_d
//#
	{0xFD, 0x01, 0, 0},
//	{0x03, 0x03, 0, 0},   //# 103 buf_exp_5msb
//	{0x04, 0xE3, 0, 0},   //# 104 buf_exp_8lsb
	{0x03, 0x02, 0, 0},   //# 103 buf_exp_5msb
	{0x04, 0x55, 0, 0},   //# 104 buf_exp_8lsb
	{0x09, 0x00, 0, 0},   //# 109 hblank_4msb
	{0x0A, 0x4E, 0, 0},   //# 10A hblank_8lsb
//#
	{0xFD, 0x00, 0, 0},
	{0x0E, 0x40, 0, 0},   //# 00E pd
//#
	{0xFD, 0x01, 0, 0},
	{0x0E, 0x00, 0, 0},   //# 10E p0
	{0x0F, 0x18, 0, 0},   //# 10F p1
	{0x10, 0x10, 0, 0},   //# 110 p2
	{0x11, 0x03, 0, 0},   //# 111 p3
	{0x12, 0x18, 0, 0},   //# 112 p4
	{0x13, 0x10, 0, 0},   //# 113 p5
	{0x14, 0x15, 0, 0},   //# 114 p6
	{0x15, 0x01, 0, 0},   //# 115 p7
	{0x16, 0x02, 0, 0},   //# 116 p8
	{0x17, 0x10, 0, 0},   //# 117 p9
	{0x18, 0x00, 0, 0},   //# 118 p10_2msb
	{0x19, 0x1A, 0, 0},   //# 119 p10_8lsb
	{0x1A, 0x00, 0, 0},   //# 11A p11_2msb
	{0x1B, 0x1C, 0, 0},   //# 11B p11_8lsb
	{0x50, 0x00, 0, 0},   //# 150 p12_2msb
	{0x51, 0x1D, 0, 0},   //# 151 p12_8lsb
	{0x52, 0x15, 0, 0},   //# 152 P13
	{0x2A, 0x02, 0, 0},   //# 12A p16
	{0x53, 0x00, 0, 0},   //# 153 p17_2msb
	{0x54, 0x11, 0, 0},   //# 154 p17_8lsb
	{0x55, 0x12, 0, 0},   //# 155 p18
	{0x56, 0x02, 0, 0},   //# 156 p19
	{0x57, 0x02, 0, 0},   //# 157 p20
	{0x58, 0x00, 0, 0},   //# 158 p21
//#
	{0xFD, 0x00, 0, 0},
	{0x12, 0x04, 0, 0},   //# 012 pll_bias_ctl,pll_delay
	{0x13, 0x04, 0, 0},   //# 013 mipi_pattern_en,pll_test_en,mipi_en
	{0x14, 0x00, 0, 0},   //# 014 pclk_gate,timer_clk_gate,dclk_gate
	{0x15, 0x00, 0, 0},   //# 015 pclk_pha_adj
//#
	{0xFD, 0x01, 0, 0},
//	{0x1C, 0x5C, 0, 0},   //# 11C two_timing_en,FPN_33ms_X,pwd_asp_timing_sel,Channel-timing
	{0x1C, 0x7C, 0, 0},   //# 11C two_timing_en,FPN_33ms_X,pwd_asp_timing_sel,Channel-timing
	{0x21, 0x44, 0, 0},   //# 121 adc_vcm_opin_ctl,adc_vcm_opin_c,col_clk_delay
	{0x22, 0x04, 0, 0},   //# 122 pga_bias_ctl,col_ctrl
	{0x25, 0x00, 0, 0},   //# 125 adc_range_ctl,adc_vcm_ctl,asp_delay
	{0x26, 0x26, 0, 0},   //# 126 adc_dig_offset,sw_delay
	{0x27, 0x6D, 0, 0},   //# 127 delay,black_en,adc_dref_cal,adc_g2x_en,adc_offset_en
	{0x2B, 0x66, 0, 0},   //# 12B adc_offset_ctl_buf_up,adc_offset_ctl_buf_dn
	{0x2C, 0x3F, 0, 0},   //# 12C strobe_en,bl_da
	{0x2D, 0x40, 0, 0},   //# 12D adc_bias_stage,adc_bias_vref
	{0x2E, 0x0D, 0, 0},   //# 12E dout_sel,strobe_sel
//	{0x40, 0xF0, 0, 0},   //# 140 vfpn_bpc_en,vfpn_minus_en
	{0x40, 0xF3, 0, 0},   //# 140 vfpn_bpc_en,vfpn_minus_en
	{0x41, 0x60, 0, 0},   //# 141 vfpn_bpc_th_x1
	{0x42, 0x50, 0, 0},   //# 142 vfpn_bpc_th_x2
	{0x43, 0x28, 0, 0},   //# 143 vfpn_bpc_in_x1
	{0x44, 0x28, 0, 0},   //# 144 vfpn_bpc_in_x2
//	{0x45, 0x0C, 0, 0},   //# 145 vfpn_delta
//	{0x45, 0x06, 0, 0},   //# 145 vfpn_delta(0830)
	{0x45, 0x00, 0, 0},   //# 145 vfpn_delta(0921)
	{0x31, 0x14, 0, 0},   //# 131 buf_comm_ctrl
//#
	{0xFD, 0x02, 0, 0},
	{0x35, 0x40, 0, 0},   //# 235 buf_outmode1
	{0x31, 0x10, 0, 0},   //# 231 digital_gain
	{0x47, 0x00, 0, 0},   //# 247 v_start_3msb
	{0x48, 0x00, 0, 0},   //# 248 v_start_8lsb
	{0x49, 0x02, 0, 0},   //# 249 v_size_3msb
	{0x4A, 0x58, 0, 0},   //# 24A v_size_8lsb
	{0x4B, 0x00, 0, 0},   //# 24B h_start_3msb
	{0x4C, 0x00, 0, 0},   //# 24C h_start_8lsb
	{0x4D, 0x03, 0, 0},   //# 24D h_size_3msb
	{0x4E, 0x20, 0, 0},   //# 24E h_size_8lsb
//	{0x65, 0x08, 0, 0},   //# 265 blue_suboffset
//	{0x66, 0x06, 0, 0},   //# 266 red_suboffset
//	{0x67, 0x07, 0, 0},   //# 267 gr_suboffset
//	{0x68, 0x07, 0, 0},   //# 268 gb_suboffset
//	{0x65, 0x09, 0, 0},   //# 265 blue_suboffset(0830)
//	{0x66, 0x07, 0, 0},   //# 266 red_suboffset(0830)
//	{0x67, 0x08, 0, 0},   //# 267 gr_suboffset(0830)
//	{0x68, 0x08, 0, 0},   //# 268 gb_suboffset(0830)
	{0x65, 0x0F, 0, 0},   //# 265 blue_suboffset(0921)
	{0x66, 0x0D, 0, 0},   //# 266 red_suboffset(0921)
	{0x67, 0x0E, 0, 0},   //# 267 gr_suboffset(0921)
	{0x68, 0x0E, 0, 0},   //# 268 gb_suboffset(0921)
	{0x5F, 0x02, 0, 0},   //# 25F demo_gain_order,bayer_order
	{0x32, 0x00, 0, 0},   //# 232 auto_mode
	{0x33, 0xEF, 0, 0},   //# 233 lsc_bpc_en
	{0xA4, 0xFF, 0, 0},   //# 2A4 lsc_gain_max
//#
	{0xFD, 0x03, 0, 0},
	{0x66, 0x19, 0, 0},   //# 366 Lsc_rsy_u
	{0x6A, 0x1B, 0, 0},   //# 36A Lsc_gsy_u
	{0x6E, 0x14, 0, 0},   //# 36E Lsc_bsy_u
	{0x67, 0x19, 0, 0},   //# 367 Lsc_rsy_d
	{0x6B, 0x12, 0, 0},   //# 36B Lsc_gsy_d
	{0x6F, 0x14, 0, 0},   //# 36F Lsc_bsy_d
	{0x64, 0x1D, 0, 0},   //# 364 Lsc_rsx_l
	{0x68, 0x18, 0, 0},   //# 368 Lsc_gsx_l
	{0x6C, 0x14, 0, 0},   //# 36C Lsc_bsx_l
	{0x65, 0x15, 0, 0},   //# 365 Lsc_rsx_r
	{0x69, 0x12, 0, 0},   //# 369 Lsc_gsx_r
	{0x6D, 0x0E, 0, 0},   //# 36D Lsc_bsx_r
	{0xB8, 0x08, 0, 0},   //# 3B8 Lsc_rxy_lu
	{0xBC, 0x08, 0, 0},   //# 3BC Lsc_gxy_lu
	{0xC0, 0x08, 0, 0},   //# 3C0 Lsc_bxy_lu
	{0xB9 ,0x08, 0, 0},  //# 3B9 Lsc_rxy_ru
	{0xBD, 0x08, 0, 0},   //# 3BD Lsc_gxy_ru
	{0xC1, 0x08, 0, 0},   //# 3C1 Lsc_bxy_ru
	{0xBA, 0x08, 0, 0},   //# 3BA Lsc_rxy_ld
	{0xBE, 0x08, 0, 0},   //# 3BE Lsc_gxy_ld
	{0xC2, 0x08, 0, 0},   //# 3C2 Lsc_bxy_ld
	{0xBB, 0x08, 0, 0},   //# 3BB Lsc_rxy_rd
	{0xBF, 0x08, 0, 0},   //# 3BF Lsc_gxy_rd
	{0xC3, 0x08, 0, 0},   //# 3C3 Lsc_bxy_rd
//#
	{0xFD, 0x02, 0, 0},
	{0x51, 0x00, 0, 0},   //# 251 bpc_vt_outdoor
	{0x52, 0x00, 0, 0},   //# 252 bpc_vt_normal
	{0x53, 0x00, 0, 0},   //# 253 bpc_vt_low_light
	{0x54, 0x00, 0, 0},   //# 254 bpc_wt_eff
	{0x55, 0xFF, 0, 0},   //# 255 bpc_dt_eff
//	{0x45, 0x00, 0, 0},   //# 245 bpc_range_ratio_outdoor,pc_range_ratio_nr
//	{0x46, 0x09, 0, 0},   //# 246 bpc_range_ratio_dummy,bpc_range_ratio_low
	{0x45, 0x13, 0, 0},   //# 245 bpc_range_ratio_outdoor,pc_range_ratio_nr (1001)
	{0x46, 0x49, 0, 0},   //# 246 bpc_range_ratio_dummy,bpc_range_ratio_low (1001)
	{0x69, 0x00, 0, 0},   //# 269 bpc_range_thr_outdoor
	{0x6A, 0x00, 0, 0},   //# 26A bpc_range_thr_nr
	{0x6B, 0x00, 0, 0},   //# 26B bpc_range_thr_dummy
	{0x6C, 0x00, 0, 0},   //# 26C bpc_range_thr_low
//#
	{0xFD, 0x03, 0, 0},
	{0xDE, 0x0F, 0, 0},   //# 3DE raw_denoise_en_outdoor,raw_denoise_en_nr,raw_denoise_en_dummy,raw_denoise_en_low
//#
	{0xFD, 0x02, 0, 0},
	{0x57, 0x04, 0, 0},   //# 257 raw_dif_thr_outdoor
	{0x58, 0x04, 0, 0},   //# 258 raw_dif_thr_normal
	{0x56, 0x0A, 0, 0},   //# 256 raw_dif_thr_dummy
	{0x59, 0x08, 0, 0},   //# 259 raw_dif_thr_low_light
	{0x4F, 0xE0, 0, 0},   //# 24F raw_gf_fac_outdoor
	{0xC3, 0xE0, 0, 0},   //# 2C3 raw_gf_fac_indoor
	{0x3F, 0xC0, 0, 0},   //# 23F raw_gf_fac_dummy
	{0x42, 0x40, 0, 0},   //# 242 raw_gf_fac_low
	{0x5A, 0xE0, 0, 0},   //# 25A raw_rb_fac_outdoor
	{0xC4, 0xE0, 0, 0},   //# 2C4 raw_rb_fac_indoor
	{0x43, 0xC0, 0, 0},   //# 243 raw_rb_fac_dummy
	{0xAD, 0x40, 0, 0},   //# 2AD raw_rb_fac_low
	{0xC2, 0x15, 0, 0},   //# 2C2 gf_ratiok_fac
//#
	{0xFD, 0x03, 0, 0},
	{0x50, 0x00, 0, 0},   //# 350 raw_grgb_thr_outdoor
	{0x51, 0x00, 0, 0},   //# 351 raw_grgb_thr_normal
	{0x52, 0x08, 0, 0},   //# 352 raw_grgb_thr_dummy
	{0x53, 0x08, 0, 0},   //# 353 raw_grgb_thr_low
//#
	{0xFD, 0x02, 0, 0},
	{0xB6, 0xE0, 0, 0},   //# 2B6 raw_gflt_fac_outdoor
	{0xB7, 0xC0, 0, 0},   //# 2B7 raw_gflt_fac_nr
	{0xB8, 0xA0, 0, 0},   //# 2B8 raw_gflt_fac_dummy
	{0xB9, 0x20, 0, 0},   //# 2B9 raw_gflt_fac_low
//#
	{0xFD, 0x03, 0, 0},
	{0x11, 0x1F, 0, 0},   //# 311 rg_dif_th
	{0x12, 0x1F, 0, 0},   //# 312 bg_dif_th
	{0x16, 0x1C, 0, 0},   //# 316 rgb_limit
	{0x18, 0x00, 0, 0},   //# 318 br_offset_f
	{0x19, 0x00, 0, 0},   //# 319 br_offset
	{0x1B, 0x80, 0, 0},   //# 31B rg_base
	{0x1A, 0x80, 0, 0},   //# 31A bg_base
	{0x43, 0x80, 0, 0},   //# 343 channel_sel,test_awb
	{0x1E, 0x17, 0, 0},   //# 31E wb_fine_gain_step,wb_rough_gain_step
	{0x1F, 0x19, 0, 0},   //# 31F wb_dif_fine_th,wb_dif_rough_th
//	{0x28, 0x9C, 0, 0},   //# 328 buf_rgain
//	{0x29, 0xA2, 0, 0},   //# 329 buf_bgain
	{0x28, 0xA1, 0, 0},   //# 328 buf_rgain(1001)
	{0x29, 0xA6, 0, 0},   //# 329 buf_bgain(1001)
//#
	{0xFD, 0x02, 0, 0},
	{0xE7, 0x03, 0, 0},   //# 2E7 reg_renew
	{0xE7, 0x00, 0, 0},   //# 2E7 reg_renew
//#
	{0xFD, 0x03, 0, 0},
	{0x2A, 0xF0, 0, 0},   //# 32A y_top_th
	{0x2B, 0x10, 0, 0},   //# 32B y_bot_th
	{0x2E, 0x04, 0, 0},   //# 32E rg_limit_log
	{0x2F, 0x16, 0, 0},   //# 32F bg_limit_log
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x80, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x80, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0x83, 0x70, 0, 0},   //# 383 skin_num_th
	{0x13, 0x43, 0, 0},   //# 313 awb_grey_en,awb_skin_en
	{0x24, 0x06, 0, 0},   //# 324 short_exp_th
	{0x25, 0x80, 0, 0},   //# 325 sp_rg_base
	{0x26, 0x80, 0, 0},   //# 326 sp_bg_base
	{0x35, 0xB2, 0, 0},   //# 335 d65_rg_bot
	{0x36, 0xCA, 0, 0},   //# 336 d65_rg_top
//	{0x37, 0x7C, 0, 0},   //# 337 d65_bg_bot
	{0x37, 0x73, 0, 0},   //# 337 d65_bg_bot(1001)
	{0x38, 0x94, 0, 0},   //# 338 d65_bg_top
//	{0x31, 0x7B, 0, 0},   //# 331 f_rg_bot
//	{0x32, 0x93, 0, 0},   //# 332 f_rg_top
//	{0x33, 0xAE, 0, 0},   //# 333 f_bg_bot
//	{0x34, 0xC6, 0, 0},   //# 334 f_bg_top
	{0x31, 0x60, 0, 0},   //# 331 f_rg_bot(1010)
	{0x32, 0x98, 0, 0},   //# 332 f_rg_top(1010)
	{0x33, 0xA8, 0, 0},   //# 333 f_bg_bot(1010)
	{0x34, 0xD8, 0, 0},   //# 334 f_bg_top(1010)
	{0x3D, 0x9C, 0, 0},   //# 33D cwf_rg_bot
	{0x3E, 0xB4, 0, 0},   //# 33E cwf_rg_top
	{0x3F, 0xA4, 0, 0},   //# 33F cwf_bg_bot
	{0x40, 0xBC, 0, 0},   //# 340 cwf_bg_top
	{0x39, 0x8A, 0, 0},   //# 339 tl84_rg_bot
	{0x3A, 0xA2, 0, 0},   //# 33A tl84_rg_top
	{0x3B, 0x9E, 0, 0},   //# 33B tl84_bg_bot
	{0x3C, 0xB6, 0, 0},   //# 33C tl84_bg_top
	{0xA0, 0xA6, 0, 0},   //# 3A0 c00_eff1_8lsb
	{0xA1, 0xCD, 0, 0},   //# 3A1 c01_eff1_8lsb
	{0xA2, 0x0C, 0, 0},   //# 3A2 c02_eff1_8lsb
	{0xA3, 0x06, 0, 0},   //# 3A3 c10_eff1_8lsb
	{0xA4, 0x8C, 0, 0},   //# 3A4 c11_eff1_8lsb
	{0xA5, 0xED, 0, 0},   //# 3A5 c12_eff1_8lsb
	{0xA6, 0x00, 0, 0},   //# 3A6 c20_eff1_8lsb
	{0xA7, 0xE7, 0, 0},   //# 3A7 c21_eff1_8lsb
	{0xA8, 0x99, 0, 0},   //# 3A8 c22_eff1_8lsb
	{0xA9, 0x0C, 0, 0},   //# 3A9 c02_eff1_2msb,c01_eff1_2msb,c00_eff1_2msb
	{0xAA, 0x30, 0, 0},   //# 3AA c12_eff1_2msb,c11_eff1_2msb,c10_eff1_2msb
	{0xAB, 0x0C, 0, 0},   //# 3AB c22_eff1_2msb,c21_eff1_2msb,c20_eff1_2msb
	{0xAC, 0x8C, 0, 0},   //# 3AC c00_eff2_8lsb
	{0xAD, 0xF4, 0, 0},   //# 3AD c01_eff2_8lsb
	{0xAE, 0x00, 0, 0},   //# 3AE c02_eff2_8lsb
	{0xAF, 0xFA, 0, 0},   //# 3AF c10_eff2_8lsb
	{0xB0, 0x8C, 0, 0},   //# 3B0 c11_eff2_8lsb
	{0xB1, 0xFA, 0, 0},   //# 3B1 c12_eff2_8lsb
	{0xB2, 0x0C, 0, 0},   //# 3B2 c20_eff2_8lsb
	{0xB3, 0xF4, 0, 0},   //# 3B3 c21_eff2_8lsb
	{0xB4, 0x80, 0, 0},   //# 3B4 c22_eff2_8lsb
	{0xB5, 0x0C, 0, 0},   //# 3B5 c02_eff2_2msb,c01_eff2_2msb,c00_eff2_2msb
	{0xB6, 0x33, 0, 0},   //# 3B6 c12_eff2_2msb,c11_eff2_2msb,c10_eff2_2msb
	{0xB7, 0x0C, 0, 0},   //# 3B7 c22_eff2_2msb,c21_eff2_2msb,c20_eff2_2msb
//#
	{0xFD, 0x02, 0, 0},
	{0xBF, 0x01, 0, 0},   //# 2BF autosa_en
	{0xBE, 0xAA, 0, 0},   //# 2BE u_v_th
	{0xC0, 0xFF, 0, 0},   //# 2C0 y_p_th
	{0xC1, 0xFF, 0, 0},   //# 2C1 y_mean_th
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
	{0x8B, 0x00, 0, 0},   //# 28B gamma_pt0
	{0x8C, 0x0F, 0, 0},   //# 28C gamma_pt1
	{0x8D, 0x1F, 0, 0},   //# 28D gamma_pt2
	{0x8E, 0x3C, 0, 0},   //# 28E gamma_pt3
	{0x8F, 0x67, 0, 0},   //# 28F gamma_pt4
	{0x90, 0x85, 0, 0},   //# 290 gamma_pt5
	{0x91, 0x99, 0, 0},   //# 291 gamma_pt6
	{0x92, 0xA8, 0, 0},   //# 292 gamma_pt7
	{0x93, 0xB5, 0, 0},   //# 293 gamma_pt8
	{0x94, 0xBE, 0, 0},   //# 294 gamma_pt9
	{0x95, 0xC8, 0, 0},   //# 295 gamma_pt10
	{0x96, 0xD1, 0, 0},   //# 296 gamma_pt11
	{0x97, 0xD9, 0, 0},   //# 297 gamma_pt12
	{0x98, 0xE0, 0, 0},   //# 298 gamma_pt13
	{0x99, 0xE8, 0, 0},   //# 299 gamma_pt14
	{0x9A, 0xED, 0, 0},   //# 29A gamma_pt15
	{0x9B, 0xF3, 0, 0},   //# 29B gamma_pt16
//#
	{0xFD, 0x03, 0, 0},
	{0x8D, 0xF9, 0, 0},   //# 38D gamma_pt17
	{0x8E, 0xFF, 0, 0},   //# 38E gamma_pt18
//#
	{0xFD, 0x02, 0, 0},
	{0x78, 0x00, 0, 0},   //# 278 gamma_pt2_0
	{0x79, 0x0F, 0, 0},   //# 279 gamma_pt2_1
	{0x7A, 0x1F, 0, 0},   //# 27A gamma_pt2_2
	{0x7B, 0x3C, 0, 0},   //# 27B gamma_pt2_3
	{0x7C, 0x67, 0, 0},   //# 27C gamma_pt2_4
	{0x7D, 0x85, 0, 0},   //# 27D gamma_pt2_5
	{0x7E, 0x99, 0, 0},   //# 27E gamma_p2_6
	{0x7F, 0xA8, 0, 0},   //# 27F gamma_pt2_7
	{0x80, 0xB5, 0, 0},   //# 280 gamma_pt2_8
	{0x81, 0xBE, 0, 0},   //# 281 gamma_pt2_9
	{0x82, 0xC8, 0, 0},   //# 282 gamma_pt2_10
	{0x83, 0xD1, 0, 0},   //# 283 gamma_pt2_11
	{0x84, 0xD9, 0, 0},   //# 284 gamma_pt2_12
	{0x85, 0xE0, 0, 0},   //# 285 gamma_pt2_13
	{0x86, 0xE8, 0, 0},   //# 286 gamma_pt2_14
	{0x87, 0xED, 0, 0},   //# 287 gamma_pt2_15
	{0x88, 0xF3, 0, 0},   //# 288 gamma_pt2_16
	{0x89, 0xF9, 0, 0},   //# 289 gamma_pt2_17
	{0x8A, 0xFF, 0, 0},   //# 28A gamma_pt2_18
//#
	{0xFD, 0x03, 0, 0},
	{0x96, 0x46, 0, 0},   //# 396 ae time thr1
	{0x97, 0x28, 0, 0},   //# 397 ae time thr2
	{0x9F, 0x0A, 0, 0},   //# 39F gma_ratiok_fac
//#
	{0xFD, 0x02, 0, 0},
	{0xF4, 0x0B, 0, 0},   //# 2F4 lum_fcase_en,lum_down_en,outdoor_mode_en,mean_mode_reg
	{0xF0, 0xC7, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 exp_min_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
	{0x95, 0x20, 0, 0},   //# 395 rpc_min_indr
	{0x98, 0xC7, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_outdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x9C, 0x32, 0, 0},   //# 39C rpc_max_outdr
	{0x9D, 0x20, 0, 0},   //# 39D rpc_min_outdr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x55, 0x11, 0, 0},   //# 355 weight_w2,weight_w1
	{0x56, 0x11, 0, 0},   //# 356 weight_w4,weight_w3
//	{0x57, 0x03, 0, 0},   //# 357 weight_w5
	{0x57, 0x01, 0, 0},   //# 357 weight_w5(1001)
//#
	{0xFD, 0x02, 0, 0},
	{0xE0, 0x3E, 0, 0},   //# 2E0 rpc_1base_max
	{0xE1, 0x26, 0, 0},   //# 2E1 rpc_2base_max
	{0xE2, 0x2A, 0, 0},   //# 2E2 rpc_3base_max
	{0xE3, 0x26, 0, 0},   //# 2E3 rpc_4base_max
	{0xE4, 0x26, 0, 0},   //# 2E4 rpc_5base_max
	{0xE5, 0x24, 0, 0},   //# 2E5 rpc_6base_max
	{0xE6, 0x24, 0, 0},   //# 2E6 rpc_7base_max
	{0xE8, 0x22, 0, 0},   //# 2E8 rpc_8base_max
	{0xE9, 0x22, 0, 0},   //# 2E9 rpc_9base_max
	{0xEA, 0x22, 0, 0},   //# 2EA rpc_10base_max
	{0xEB, 0x20, 0, 0},   //# 2EB rpc_11base_max
	{0xF5, 0x20, 0, 0},   //# 2F5 rpc_12base_max
	{0xF6, 0x20, 0, 0},   //# 2F6 rpc_13base_max
	{0xF3, 0x03, 0, 0},   //# 2F3 uv_dif_en_outdoor,uv_dif_en_nr,uv_dif_en_dummy,uv_dif_en_low
	{0xB0, 0x00, 0, 0},   //# 2B0 uv_dif_gain_outdoor,uv_dif_gain_nr
	{0xB1, 0x12, 0, 0},   //# 2B1 uv_dif_gain_dummy,uv_dif_gain_low
//#
	{0xFD, 0x03, 0, 0},
	{0xDF, 0x0F, 0, 0},   //# 3DF sharpness
	{0xE7, 0x08, 0, 0},   //# 3E7 raw_sharp_range_base
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
	{0x70, 0x73, 0, 0},   //# 370 aec_gw_en,gw_uv_dif_en,gw_detect_en,gw_step
	{0x7B, 0x40, 0, 0},   //# 37B gw_mean_th
	{0x71, 0x2F, 0, 0},   //# 371 k_up
	{0x72, 0x0D, 0, 0},   //# 372 k_low
	{0x73, 0x0A, 0, 0},   //# 373 b_up
	{0x74, 0x2A, 0, 0},   //# 374 b_low
	{0x75, 0x04, 0, 0},   //# 375 uv_low_th
	{0x76, 0x20, 0, 0},   //# 376 y_low_th
	{0x77, 0x32, 0, 0},   //# 377 u_top
	{0x78, 0x00, 0, 0},   //# 378 u_bot
	{0x79, 0x28, 0, 0},   //# 379 v_top
	{0x7A, 0x00, 0, 0},   //# 37A v_bot
	{0x7C, 0x70, 0, 0},   //# 37C gw_offset
	{0x7D, 0x90, 0, 0},   //# 37D gw_y_bot
	{0x7E, 0xEF, 0, 0},   //# 37E gw_y_top
	{0x7F, 0x04, 0, 0},   //# 37F gw_uv_radius
	{0x80, 0x40, 0, 0},   //# 380 uv_fix_dat
	{0x81, 0x20, 0, 0},   //# 381 y_offset_th
	{0x8F, 0x12, 0, 0},   //# 38F wt_th
	{0xCE, 0x8C, 0, 0},   //# 3CE exp_heq_dummy[7:0]
	{0xCF, 0x0F, 0, 0},   //# 3CF exp_heq_dummy[12:8]
	{0xCD, 0x30, 0, 0},   //# 3CD rpc_heq_dummy
	{0xCA, 0x68, 0, 0},   //# 3CA mean_dummy_low
	{0xCB, 0x88, 0, 0},   //# 3CB mean_low_dummy
	{0xD0, 0x8C, 0, 0},   //# 3D0 exp_heq_low[7:0]
	{0xD1, 0x0F, 0, 0},   //# 3D1 exp_heq_low[12:8]
	{0xCC, 0xC0, 0, 0},   //# 3CC rpc_heq_low
	{0xD5, 0x80, 0, 0},   //# 3D5 mean_nr_dummy
	{0xD6, 0x90, 0, 0},   //# 3D6 mean_dummy_nr
	{0xD7, 0xC4, 0, 0},   //# 3D7 exp_nr_outd_8lsb
	{0xD8, 0x00, 0, 0},   //# 3D8 exp_nr_outd_5hsb
	{0xD9, 0xC7, 0, 0},   //# 3D9 exp_outd_nr_8lsb
	{0xDA, 0x00, 0, 0},   //# 3DA exp_outd_nr_5hsb
//#
	{0xFD, 0x02, 0, 0},
	{0xB2, 0x30, 0, 0},   //# 2B2 lum_limit
	{0xB3, 0x18, 0, 0},   //# 2B3 lum_set
	{0xB4, 0x60, 0, 0},   //# 2B4 black_vt
	{0xB5, 0x70, 0, 0},   //# 2B5 white_vt
	{0xCB, 0x00, 0, 0},   //# 2CB rg_clip_ga_outdoor
	{0xCC, 0x02, 0, 0},   //# 2CC rg_clip_ga_nr
	{0xCD, 0x05, 0, 0},   //# 2CD rg_clip_ga_dummy
	{0xCE, 0x08, 0, 0},   //# 2CE rg_clip_ga_low
	{0xCF, 0x00, 0, 0},   //# 2CF bg_clip_ga_outdoor
	{0xD0, 0x02, 0, 0},   //# 2D0 bg_clip_ga_nr
//#
	{0xFD, 0x03, 0, 0},
	{0x10, 0x05, 0, 0},   //# 310 bg_clip_ga_dummy
	{0x14, 0x08, 0, 0},   //# 314 bg_clip_ga_low
//#
	{0xFD, 0x02, 0, 0},
	{0x5B, 0x00, 0, 0},   //# 25B cnr_thr_outdoor
	{0x61, 0x08, 0, 0},   //# 261 cnr_thr_nr
	{0x77, 0x40, 0, 0},   //# 277 cnr_thr_dummy
	{0xCA, 0x60, 0, 0},   //# 2CA cnr_thr_low
//	{0xAB, 0x10, 0, 0},   //# 2AB ynr_thr_outdoor
	{0xAB, 0x00, 0, 0},   //# 2AB ynr_thr_outdoor(1001)
	{0xAC, 0x10, 0, 0},   //# 2AC ynr_thr_nr
	{0xAE, 0x60, 0, 0},   //# 2AE ynr_thr_dummy
	{0xAF, 0x40, 0, 0},   //# 2AF ynr_thr_low
	{0x60, 0x01, 0, 0},   //# 260 bpc_vt_dummy
	{0x70, 0x0A, 0, 0},   //# 270 Bpc_v
	{0x76, 0x00, 0, 0},   //# 276 blacklevelin
	{0xC5, 0x60, 0, 0},   //# 2C5 raw_gflt_fac_indoor
	{0xDC, 0x00, 0, 0},   //# 2DC buf_heq_offset
	{0xDD, 0x80, 0, 0},   //# 2DD ku
	{0xDE, 0x90, 0, 0},   //# 2DE kl
//#
	{0xFD, 0x03, 0, 0},
	{0x06, 0x00, 0, 0},   //# 306 ratio_row[9:8]
	{0x07, 0x28, 0, 0},   //# 307 ratio_row[7:0]
	{0x08, 0x00, 0, 0},   //# 308 ratio_col[9:8]
	{0x09, 0x28, 0, 0},   //# 309 ratio_col[7:0]
	{0x0A, 0x01, 0, 0},   //# 30A scalerownum[10:8]
	{0x0B, 0xE0, 0, 0},   //# 30B scalerownum[7:0]
	{0x0C, 0x02, 0, 0},   //# 30C scalecolnum[10:8]
	{0x0D, 0x80, 0, 0},   //# 30D scalecolnum[7:0]
	{0x0E, 0x01, 0, 0},   //# 30E resize_en
	{0x1C, 0xBA, 0, 0},   //# 31C f_limit_b
	{0x1D, 0x87, 0, 0},   //# 31D f_limit_r
	{0x41, 0x00, 0, 0},   //# 341 grgb_top_high_bit
	{0x42, 0x00, 0, 0},   //# 342 grgb_bot_high_bit
	{0x44, 0x0F, 0, 0},   //# 344 wb_num_th_light_s
	{0x4C, 0x48, 0, 0},   //# 34C raw_adt_fac_outdoor
	{0x4D, 0x48, 0, 0},   //# 34D raw_adt_fac_normal
	{0x4E, 0x48, 0, 0},   //# 34E raw_adt_fac_dummy
	{0x4F, 0x48, 0, 0},   //# 34F raw_adt_fac_low
	{0xC6, 0x40, 0, 0},   //# 3C6 pre_grgain
	{0xC7, 0x40, 0, 0},   //# 3C7 pre_rgain
	{0xC8, 0x40, 0, 0},   //# 3C8 pre_gbgain
	{0xC9, 0x40, 0, 0},   //# 3C9 pre_bgain
	{0xE2, 0x40, 0, 0},   //# 3E2 raw_sharp_y_base
	{0xE3, 0x10, 0, 0},   //# 3E3 raw_sharp_y_min
	{0xE4, 0xE0, 0, 0},   //# 3E4 raw_sharp_y_max
	{0xE5, 0x30, 0, 0},   //# 3E5 raw_sharp_rangek_neg
	{0xE6, 0x20, 0, 0},   //# 3E6 raw_sharp_rangek_pos
//#
	{0xFD, 0x02, 0, 0},
	{0x32, 0x0D, 0, 0},   //# 232 auto_mode
	{0x33, 0xEF, 0, 0},   //# 233 lsc_bpc_en
	{0x34, 0xFF, 0, 0},   //# 234 buf_isp_mode
	{0xFB, 0x00, 0, 0},   //# 2FB blackgain_en,bl_bpc_en,abl
	{0x36, 0x00, 0, 0},   //# 236 buf_outmode2
};

//----- SVGA -------
static struct reg_value rnss2e1_setting_15fps_SVGA_800_600[] = {
	{0xFD, 0x02, 0, 0},
	{0x36, 0x00, 0, 0},   //# 236 buf_outmode2
//#
	{0xFD, 0x00, 0, 0},
	{0x10, 0x3F, 0, 0},   //# 010 clk_mode
	{0x11, 0x40, 0, 0},   //# 011 pclk_inv,pclk_gate_en,pclk_ctrl,isp_clk_ctrl
	{0x20, 0x02, 0, 0},   //# 020 ds_data,out_end_high8,out_end_low2,out_ens
	{0x21, 0x03, 0, 0},   //# 021 pe_hvp,pe_data,ds_s,buf_dis_s,buf_dis_d
//#
	{0xFD, 0x01, 0, 0},
	{0x03, 0x01, 0, 0},   //# 103 buf_exp_5msb
//	{0x04, 0x90, 0, 0},   //# 104 buf_exp_8lsb
	{0x04, 0x2C, 0, 0},   //# 104 buf_exp_8lsb(1002)
	{0x09, 0x00, 0, 0},   //# 109 hblank_4msb
	{0x0A, 0x4E, 0, 0},   //# 10A hblank_8lsb
//#
	{0xFD, 0x00, 0, 0},
	{0x0E, 0x40, 0, 0},   //# 00E pd
//#
	{0xFD, 0x01, 0, 0},
	{0x0E, 0x00, 0, 0},   //# 10E p0
	{0x0F, 0x18, 0, 0},   //# 10F p1
	{0x10, 0x10, 0, 0},   //# 110 p2
	{0x11, 0x03, 0, 0},   //# 111 p3
	{0x12, 0x18, 0, 0},   //# 112 p4
	{0x13, 0x10, 0, 0},   //# 113 p5
	{0x14, 0x15, 0, 0},   //# 114 p6
	{0x15, 0x01, 0, 0},   //# 115 p7
	{0x16, 0x02, 0, 0},   //# 116 p8
	{0x17, 0x10, 0, 0},   //# 117 p9
	{0x18, 0x00, 0, 0},   //# 118 p10_2msb
	{0x19, 0x1A, 0, 0},   //# 119 p10_8lsb
	{0x1A, 0x00, 0, 0},   //# 11A p11_2msb
	{0x1B, 0x1C, 0, 0},   //# 11B p11_8lsb
	{0x50, 0x00, 0, 0},   //# 150 p12_2msb
	{0x51, 0x1D, 0, 0},   //# 151 p12_8lsb
	{0x52, 0x15, 0, 0},   //# 152 P13
	{0x2A, 0x02, 0, 0},   //# 12A p16
	{0x53, 0x00, 0, 0},   //# 153 p17_2msb
	{0x54, 0x11, 0, 0},   //# 154 p17_8lsb
	{0x55, 0x12, 0, 0},   //# 155 p18
	{0x56, 0x02, 0, 0},   //# 156 p19
	{0x57, 0x02, 0, 0},   //# 157 p20
	{0x58, 0x00, 0, 0},   //# 158 p21
//#
	{0xFD, 0x00, 0, 0},
	{0x12, 0x04, 0, 0},   //# 012 pll_bias_ctl,pll_delay
	{0x13, 0x04, 0, 0},   //# 013 mipi_pattern_en,pll_test_en,mipi_en
	{0x14, 0x00, 0, 0},   //# 014 pclk_gate,timer_clk_gate,dclk_gate
	{0x15, 0x00, 0, 0},   //# 015 pclk_pha_adj
//#
	{0xFD, 0x01, 0, 0},
//	{0x1C, 0x5C, 0, 0},   //# 11C two_timing_en,FPN_33ms_X,pwd_asp_timing_sel,Channel-timing
	{0x1C, 0x7C, 0, 0},   //# 11C two_timing_en,FPN_33ms_X,pwd_asp_timing_sel,Channel-timing
	{0x21, 0x44, 0, 0},   //# 121 adc_vcm_opin_ctl,adc_vcm_opin_c,col_clk_delay
	{0x22, 0x04, 0, 0},   //# 122 pga_bias_ctl,col_ctrl
	{0x25, 0x00, 0, 0},   //# 125 adc_range_ctl,adc_vcm_ctl,asp_delay
	{0x26, 0x26, 0, 0},   //# 126 adc_dig_offset,sw_delay
	{0x27, 0x6D, 0, 0},   //# 127 delay,black_en,adc_dref_cal,adc_g2x_en,adc_offset_en
	{0x2B, 0x66, 0, 0},   //# 12B adc_offset_ctl_buf_up,adc_offset_ctl_buf_dn
	{0x2C, 0x3F, 0, 0},   //# 12C strobe_en,bl_da
	{0x2D, 0x40, 0, 0},   //# 12D adc_bias_stage,adc_bias_vref
	{0x2E, 0x0D, 0, 0},   //# 12E dout_sel,strobe_sel
//	{0x40, 0xF0, 0, 0},   //# 140 vfpn_bpc_en,vfpn_minus_en
	{0x40, 0xF3, 0, 0},   //# 140 vfpn_bpc_en,vfpn_minus_en
	{0x41, 0x60, 0, 0},   //# 141 vfpn_bpc_th_x1
	{0x42, 0x50, 0, 0},   //# 142 vfpn_bpc_th_x2
	{0x43, 0x28, 0, 0},   //# 143 vfpn_bpc_in_x1
	{0x44, 0x28, 0, 0},   //# 144 vfpn_bpc_in_x2
//	{0x45, 0x0C, 0, 0},   //# 145 vfpn_delta
//	{0x45, 0x06, 0, 0},   //# 145 vfpn_delta(0830)
	{0x45, 0x00, 0, 0},   //# 145 vfpn_delta(0921)
	{0x31, 0x14, 0, 0},   //# 131 buf_comm_ctrl
//#
	{0xFD, 0x02, 0, 0},
	{0x35, 0x40, 0, 0},   //# 235 buf_outmode1
	{0x31, 0x10, 0, 0},   //# 231 digital_gain
	{0x47, 0x00, 0, 0},   //# 247 v_start_3msb
	{0x48, 0x00, 0, 0},   //# 248 v_start_8lsb
	{0x49, 0x02, 0, 0},   //# 249 v_size_3msb
	{0x4A, 0x58, 0, 0},   //# 24A v_size_8lsb
	{0x4B, 0x00, 0, 0},   //# 24B h_start_3msb
	{0x4C, 0x00, 0, 0},   //# 24C h_start_8lsb
	{0x4D, 0x03, 0, 0},   //# 24D h_size_3msb
	{0x4E, 0x20, 0, 0},   //# 24E h_size_8lsb
//	{0x65, 0x08, 0, 0},   //# 265 blue_suboffset
//	{0x66, 0x06, 0, 0},   //# 266 red_suboffset
//	{0x67, 0x07, 0, 0},   //# 267 gr_suboffset
//	{0x68, 0x07, 0, 0},   //# 268 gb_suboffset
//	{0x65, 0x09, 0, 0},   //# 265 blue_suboffset(0830)
//	{0x66, 0x07, 0, 0},   //# 266 red_suboffset(0830)
//	{0x67, 0x08, 0, 0},   //# 267 gr_suboffset(0830)
//	{0x68, 0x08, 0, 0},   //# 268 gb_suboffset(0830)
	{0x65, 0x0F, 0, 0},   //# 265 blue_suboffset(0921)
	{0x66, 0x0D, 0, 0},   //# 266 red_suboffset(0921)
	{0x67, 0x0E, 0, 0},   //# 267 gr_suboffset(0921)
	{0x68, 0x0E, 0, 0},   //# 268 gb_suboffset(0921)
	{0x5F, 0x02, 0, 0},   //# 25F demo_gain_order,bayer_order
	{0x32, 0x00, 0, 0},   //# 232 auto_mode
	{0x33, 0xEF, 0, 0},   //# 233 lsc_bpc_en
	{0xA4, 0xFF, 0, 0},   //# 2A4 lsc_gain_max
//#
	{0xFD, 0x03, 0, 0},
	{0x66, 0x19, 0, 0},   //# 366 Lsc_rsy_u
	{0x6A, 0x1B, 0, 0},   //# 36A Lsc_gsy_u
	{0x6E, 0x14, 0, 0},   //# 36E Lsc_bsy_u
	{0x67, 0x19, 0, 0},   //# 367 Lsc_rsy_d
	{0x6B, 0x12, 0, 0},   //# 36B Lsc_gsy_d
	{0x6F, 0x14, 0, 0},   //# 36F Lsc_bsy_d
	{0x64, 0x1D, 0, 0},   //# 364 Lsc_rsx_l
	{0x68, 0x18, 0, 0},   //# 368 Lsc_gsx_l
	{0x6C, 0x14, 0, 0},   //# 36C Lsc_bsx_l
	{0x65, 0x15, 0, 0},   //# 365 Lsc_rsx_r
	{0x69, 0x12, 0, 0},   //# 369 Lsc_gsx_r
	{0x6D, 0x0E, 0, 0},   //# 36D Lsc_bsx_r
	{0xB8, 0x08, 0, 0},   //# 3B8 Lsc_rxy_lu
	{0xBC, 0x08, 0, 0},   //# 3BC Lsc_gxy_lu
	{0xC0, 0x08, 0, 0},   //# 3C0 Lsc_bxy_lu
	{0xB9, 0x08, 0, 0},   //# 3B9 Lsc_rxy_ru
	{0xBD, 0x08, 0, 0},   //# 3BD Lsc_gxy_ru
	{0xC1, 0x08, 0, 0},   //# 3C1 Lsc_bxy_ru
	{0xBA, 0x08, 0, 0},   //# 3BA Lsc_rxy_ld
	{0xBE, 0x08, 0, 0},   //# 3BE Lsc_gxy_ld
	{0xC2, 0x08, 0, 0},   //# 3C2 Lsc_bxy_ld
	{0xBB, 0x08, 0, 0},   //# 3BB Lsc_rxy_rd
	{0xBF, 0x08, 0, 0},   //# 3BF Lsc_gxy_rd
	{0xC3, 0x08, 0, 0},   //# 3C3 Lsc_bxy_rd
//#
	{0xFD, 0x02, 0, 0},
	{0x51, 0x00, 0, 0},   //# 251 bpc_vt_outdoor
	{0x52, 0x00, 0, 0},   //# 252 bpc_vt_normal
	{0x53, 0x00, 0, 0},   //# 253 bpc_vt_low_light
	{0x54, 0x00, 0, 0},   //# 254 bpc_wt_eff
	{0x55, 0xFF, 0, 0},   //# 255 bpc_dt_eff
//	{0x45, 0x00, 0, 0},   //# 245 bpc_range_ratio_outdoor,pc_range_ratio_nr
//	{0x46, 0x09, 0, 0},   //# 246 bpc_range_ratio_dummy,bpc_range_ratio_low
	{0x45, 0x13, 0, 0},   //# 245 bpc_range_ratio_outdoor,pc_range_ratio_nr (1001)
	{0x46, 0x49, 0, 0},   //# 246 bpc_range_ratio_dummy,bpc_range_ratio_low (1001)
	{0x69, 0x00, 0, 0},   //# 269 bpc_range_thr_outdoor
	{0x6A, 0x00, 0, 0},   //# 26A bpc_range_thr_nr
	{0x6B, 0x00, 0, 0},   //# 26B bpc_range_thr_dummy
	{0x6C, 0x00, 0, 0},   //# 26C bpc_range_thr_low
//#
	{0xFD, 0x03, 0, 0},
	{0xDE, 0x0F, 0, 0},   //# 3DE raw_denoise_en_outdoor,raw_denoise_en_nr,raw_denoise_en_dummy,raw_denoise_en_low
//#
	{0xFD, 0x02, 0, 0},
	{0x57, 0x04, 0, 0},   //# 257 raw_dif_thr_outdoor
	{0x58, 0x04, 0, 0},   //# 258 raw_dif_thr_normal
	{0x56, 0x0A, 0, 0},   //# 256 raw_dif_thr_dummy
	{0x59, 0x08, 0, 0},   //# 259 raw_dif_thr_low_light
	{0x4F, 0xE0, 0, 0},   //# 24F raw_gf_fac_outdoor
	{0xC3, 0xE0, 0, 0},   //# 2C3 raw_gf_fac_indoor
	{0x3F, 0xC0, 0, 0},   //# 23F raw_gf_fac_dummy
	{0x42, 0x40, 0, 0},   //# 242 raw_gf_fac_low
	{0x5A, 0xE0, 0, 0},   //# 25A raw_rb_fac_outdoor
	{0xC4, 0xE0, 0, 0},   //# 2C4 raw_rb_fac_indoor
	{0x43, 0xC0, 0, 0},   //# 243 raw_rb_fac_dummy
	{0xAD, 0x40, 0, 0},   //# 2AD raw_rb_fac_low
	{0xC2, 0x15, 0, 0},   //# 2C2 gf_ratiok_fac
//#
	{0xFD, 0x03, 0, 0},
	{0x50, 0x00, 0, 0},   //# 350 raw_grgb_thr_outdoor
	{0x51, 0x00, 0, 0},   //# 351 raw_grgb_thr_normal
	{0x52, 0x08, 0, 0},   //# 352 raw_grgb_thr_dummy
	{0x53, 0x08, 0, 0},   //# 353 raw_grgb_thr_low
//#
	{0xFD, 0x02, 0, 0},
	{0xB6, 0xE0, 0, 0},   //# 2B6 raw_gflt_fac_outdoor
	{0xB7, 0xC0, 0, 0},   //# 2B7 raw_gflt_fac_nr
	{0xB8, 0xA0, 0, 0},   //# 2B8 raw_gflt_fac_dummy
	{0xB9, 0x20, 0, 0},   //# 2B9 raw_gflt_fac_low
//#
	{0xFD, 0x03, 0, 0},
	{0x11, 0x1F, 0, 0},   //# 311 rg_dif_th
	{0x12, 0x1F, 0, 0},   //# 312 bg_dif_th
	{0x16, 0x1C, 0, 0},   //# 316 rgb_limit
	{0x18, 0x00, 0, 0},   //# 318 br_offset_f
	{0x19, 0x00, 0, 0},   //# 319 br_offset
	{0x1B, 0x80, 0, 0},   //# 31B rg_base
	{0x1A, 0x80, 0, 0},   //# 31A bg_base
	{0x43, 0x80, 0, 0},   //# 343 channel_sel,test_awb
	{0x1E, 0x17, 0, 0},   //# 31E wb_fine_gain_step,wb_rough_gain_step
	{0x1F, 0x19, 0, 0},   //# 31F wb_dif_fine_th,wb_dif_rough_th
//	{0x28, 0x9B, 0, 0},   //# 328 buf_rgain
//	{0x29, 0xA1, 0, 0},   //# 329 buf_bgain
	{0x28, 0x9C, 0, 0},   //# 328 buf_rgain(1002)
	{0x29, 0xAA, 0, 0},   //# 329 buf_bgain(1002)
//#
	{0xFD, 0x02, 0, 0},
	{0xE7, 0x03, 0, 0},   //# 2E7 reg_renew
	{0xE7, 0x00, 0, 0},   //# 2E7 reg_renew
//#
	{0xFD, 0x03, 0, 0},
	{0x2A, 0xF0, 0, 0},   //# 32A y_top_th
	{0x2B, 0x10, 0, 0},   //# 32B y_bot_th
	{0x2E, 0x04, 0, 0},   //# 32E rg_limit_log
	{0x2F, 0x16, 0, 0},   //# 32F bg_limit_log
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x80, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x80, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0x83, 0x70, 0, 0},   //# 383 skin_num_th
	{0x13, 0x43, 0, 0},   //# 313 awb_grey_en,awb_skin_en
	{0x24, 0x06, 0, 0},   //# 324 short_exp_th
	{0x25, 0x80, 0, 0},   //# 325 sp_rg_base
	{0x26, 0x80, 0, 0},   //# 326 sp_bg_base
	{0x35, 0xB2, 0, 0},   //# 335 d65_rg_bot
	{0x36, 0xCA, 0, 0},   //# 336 d65_rg_top
//	{0x37, 0x7C, 0, 0},   //# 337 d65_bg_bot
	{0x37, 0x73, 0, 0},   //# 337 d65_bg_bot(1001)
	{0x38, 0x94, 0, 0},   //# 338 d65_bg_top
//	{0x31, 0x7B, 0, 0},   //# 331 f_rg_bot
//	{0x32, 0x93, 0, 0},   //# 332 f_rg_top
//	{0x33, 0xAE, 0, 0},   //# 333 f_bg_bot
//	{0x34, 0xC6, 0, 0},   //# 334 f_bg_top
	{0x31, 0x60, 0, 0},   //# 331 f_rg_bot(1010)
	{0x32, 0x98, 0, 0},   //# 332 f_rg_top(1010)
	{0x33, 0xA8, 0, 0},   //# 333 f_bg_bot(1010)
	{0x34, 0xD8, 0, 0},   //# 334 f_bg_top(1010)
	{0x3D, 0x9C, 0, 0},   //# 33D cwf_rg_bot
	{0x3E, 0xB4, 0, 0},   //# 33E cwf_rg_top
	{0x3F, 0xA4, 0, 0},   //# 33F cwf_bg_bot
	{0x40, 0xBC, 0, 0},   //# 340 cwf_bg_top
	{0x39, 0x8A, 0, 0},   //# 339 tl84_rg_bot
	{0x3A, 0xA2, 0, 0},   //# 33A tl84_rg_top
	{0x3B, 0x9E, 0, 0},   //# 33B tl84_bg_bot
	{0x3C, 0xB6, 0, 0},   //# 33C tl84_bg_top
	{0xA0, 0xA6, 0, 0},   //# 3A0 c00_eff1_8lsb
	{0xA1, 0xCD, 0, 0},   //# 3A1 c01_eff1_8lsb
	{0xA2, 0x0C, 0, 0},   //# 3A2 c02_eff1_8lsb
	{0xA3, 0x06, 0, 0},   //# 3A3 c10_eff1_8lsb
	{0xA4, 0x8C, 0, 0},   //# 3A4 c11_eff1_8lsb
	{0xA5, 0xED, 0, 0},   //# 3A5 c12_eff1_8lsb
	{0xA6, 0x00, 0, 0},   //# 3A6 c20_eff1_8lsb
	{0xA7, 0xE7, 0, 0},   //# 3A7 c21_eff1_8lsb
	{0xA8, 0x99, 0, 0},   //# 3A8 c22_eff1_8lsb
	{0xA9, 0x0C, 0, 0},   //# 3A9 c02_eff1_2msb,c01_eff1_2msb,c00_eff1_2msb
	{0xAA, 0x30, 0, 0},   //# 3AA c12_eff1_2msb,c11_eff1_2msb,c10_eff1_2msb
	{0xAB, 0x0C, 0, 0},   //# 3AB c22_eff1_2msb,c21_eff1_2msb,c20_eff1_2msb
	{0xAC, 0x8C, 0, 0},   //# 3AC c00_eff2_8lsb
	{0xAD, 0xF4, 0, 0},   //# 3AD c01_eff2_8lsb
	{0xAE, 0x00, 0, 0},   //# 3AE c02_eff2_8lsb
	{0xAF, 0xFA, 0, 0},   //# 3AF c10_eff2_8lsb
	{0xB0, 0x8C, 0, 0},   //# 3B0 c11_eff2_8lsb
	{0xB1, 0xFA, 0, 0},   //# 3B1 c12_eff2_8lsb
	{0xB2, 0x0C, 0, 0},   //# 3B2 c20_eff2_8lsb
	{0xB3, 0xF4, 0, 0},   //# 3B3 c21_eff2_8lsb
	{0xB4, 0x80, 0, 0},   //# 3B4 c22_eff2_8lsb
	{0xB5, 0x0C, 0, 0},   //# 3B5 c02_eff2_2msb,c01_eff2_2msb,c00_eff2_2msb
	{0xB6, 0x33, 0, 0},   //# 3B6 c12_eff2_2msb,c11_eff2_2msb,c10_eff2_2msb
	{0xB7, 0x0C, 0, 0},   //# 3B7 c22_eff2_2msb,c21_eff2_2msb,c20_eff2_2msb
//#
	{0xFD, 0x02, 0, 0},
	{0xBF, 0x01, 0, 0},   //# 2BF autosa_en
	{0xBE, 0xAA, 0, 0},   //# 2BE u_v_th
	{0xC0, 0xFF, 0, 0},   //# 2C0 y_p_th
	{0xC1, 0xFF, 0, 0},   //# 2C1 y_mean_th
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
	{0x8B, 0x00, 0, 0},   //# 28B gamma_pt0
	{0x8C, 0x0F, 0, 0},   //# 28C gamma_pt1
	{0x8D, 0x1F, 0, 0},   //# 28D gamma_pt2
	{0x8E, 0x3C, 0, 0},   //# 28E gamma_pt3
	{0x8F, 0x67, 0, 0},   //# 28F gamma_pt4
	{0x90, 0x85, 0, 0},   //# 290 gamma_pt5
	{0x91, 0x99, 0, 0},   //# 291 gamma_pt6
	{0x92, 0xA8, 0, 0},   //# 292 gamma_pt7
	{0x93, 0xB5, 0, 0},   //# 293 gamma_pt8
	{0x94, 0xBE, 0, 0},   //# 294 gamma_pt9
	{0x95, 0xC8, 0, 0},   //# 295 gamma_pt10
	{0x96, 0xD1, 0, 0},   //# 296 gamma_pt11
	{0x97, 0xD9, 0, 0},   //# 297 gamma_pt12
	{0x98, 0xE0, 0, 0},   //# 298 gamma_pt13
	{0x99, 0xE8, 0, 0},   //# 299 gamma_pt14
	{0x9A, 0xED, 0, 0},   //# 29A gamma_pt15
	{0x9B, 0xF3, 0, 0},   //# 29B gamma_pt16
//#
	{0xFD, 0x03, 0, 0},
	{0x8D, 0xF9, 0, 0},   //# 38D gamma_pt17
	{0x8E, 0xFF, 0, 0},   //# 38E gamma_pt18
//#
	{0xFD, 0x02, 0, 0},
	{0x78, 0x00, 0, 0},   //# 278 gamma_pt2_0
	{0x79, 0x0F, 0, 0},   //# 279 gamma_pt2_1
	{0x7A, 0x1F, 0, 0},   //# 27A gamma_pt2_2
	{0x7B, 0x3C, 0, 0},   //# 27B gamma_pt2_3
	{0x7C, 0x67, 0, 0},   //# 27C gamma_pt2_4
	{0x7D, 0x85, 0, 0},   //# 27D gamma_pt2_5
	{0x7E, 0x99, 0, 0},   //# 27E gamma_p2_6
	{0x7F, 0xA8, 0, 0},   //# 27F gamma_pt2_7
	{0x80, 0xB5, 0, 0},   //# 280 gamma_pt2_8
	{0x81, 0xBE, 0, 0},   //# 281 gamma_pt2_9
	{0x82, 0xC8, 0, 0},   //# 282 gamma_pt2_10
	{0x83, 0xD1, 0, 0},   //# 283 gamma_pt2_11
	{0x84, 0xD9, 0, 0},   //# 284 gamma_pt2_12
	{0x85, 0xE0, 0, 0},   //# 285 gamma_pt2_13
	{0x86, 0xE8, 0, 0},   //# 286 gamma_pt2_14
	{0x87, 0xED, 0, 0},   //# 287 gamma_pt2_15
	{0x88, 0xF3, 0, 0},   //# 288 gamma_pt2_16
	{0x89, 0xF9, 0, 0},   //# 289 gamma_pt2_17
	{0x8A, 0xFF, 0, 0},   //# 28A gamma_pt2_18
//#
	{0xFD, 0x03, 0, 0},
	{0x96, 0x46, 0, 0},   //# 396 ae time thr1
	{0x97, 0x28, 0, 0},   //# 397 ae time thr2
	{0x9F, 0x0A, 0, 0},   //# 39F gma_ratiok_fac
//#
	{0xFD, 0x02, 0, 0},
	{0xF4, 0x0B, 0, 0},   //# 2F4 lum_fcase_en,lum_down_en,outdoor_mode_en,mean_mode_reg
	{0xF0, 0x64, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 exp_min_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
	{0x95, 0x20, 0, 0},   //# 395 rpc_min_indr
	{0x98, 0x64, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_outdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x9C, 0x32, 0, 0},   //# 39C rpc_max_outdr
	{0x9D, 0x20, 0, 0},   //# 39D rpc_min_outdr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x55, 0x11, 0, 0},   //# 355 weight_w2,weight_w1
	{0x56, 0x11, 0, 0},   //# 356 weight_w4,weight_w3
//	{0x57, 0x03, 0, 0},   //# 357 weight_w5
	{0x57, 0x01, 0, 0},   //# 357 weight_w5(1001)
//#
	{0xFD, 0x02, 0, 0},
	{0xE0, 0x3E, 0, 0},   //# 2E0 rpc_1base_max
	{0xE1, 0x26, 0, 0},   //# 2E1 rpc_2base_max
	{0xE2, 0x2A, 0, 0},   //# 2E2 rpc_3base_max
	{0xE3, 0x26, 0, 0},   //# 2E3 rpc_4base_max
	{0xE4, 0x26, 0, 0},   //# 2E4 rpc_5base_max
	{0xE5, 0x24, 0, 0},   //# 2E5 rpc_6base_max
	{0xE6, 0x24, 0, 0},   //# 2E6 rpc_7base_max
	{0xE8, 0x22, 0, 0},   //# 2E8 rpc_8base_max
	{0xE9, 0x22, 0, 0},   //# 2E9 rpc_9base_max
	{0xEA, 0x22, 0, 0},   //# 2EA rpc_10base_max
	{0xEB, 0x20, 0, 0},   //# 2EB rpc_11base_max
	{0xF5, 0x20, 0, 0},   //# 2F5 rpc_12base_max
	{0xF6, 0x20, 0, 0},   //# 2F6 rpc_13base_max
	{0xF3, 0x03, 0, 0},   //# 2F3 uv_dif_en_outdoor,uv_dif_en_nr,uv_dif_en_dummy,uv_dif_en_low
	{0xB0, 0x00, 0, 0},   //# 2B0 uv_dif_gain_outdoor,uv_dif_gain_nr
	{0xB1, 0x12, 0, 0},   //# 2B1 uv_dif_gain_dummy,uv_dif_gain_low
//#
	{0xFD, 0x03, 0, 0},
	{0xDF, 0x0F, 0, 0},   //# 3DF sharpness
	{0xE7, 0x08, 0, 0},   //# 3E7 raw_sharp_range_base
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
	{0x70, 0x73, 0, 0},   //# 370 aec_gw_en,gw_uv_dif_en,gw_detect_en,gw_step
	{0x7B, 0x40, 0, 0},   //# 37B gw_mean_th
	{0x71, 0x2F, 0, 0},   //# 371 k_up
	{0x72, 0x0D, 0, 0},   //# 372 k_low
	{0x73, 0x0A, 0, 0},   //# 373 b_up
	{0x74, 0x2A, 0, 0},   //# 374 b_low
	{0x75, 0x04, 0, 0},   //# 375 uv_low_th
	{0x76, 0x20, 0, 0},   //# 376 y_low_th
	{0x77, 0x32, 0, 0},   //# 377 u_top
	{0x78, 0x00, 0, 0},   //# 378 u_bot
	{0x79, 0x28, 0, 0},   //# 379 v_top
	{0x7A, 0x00, 0, 0},   //# 37A v_bot
	{0x7C, 0x70, 0, 0},   //# 37C gw_offset
	{0x7D, 0x90, 0, 0},   //# 37D gw_y_bot
	{0x7E, 0xEF, 0, 0},   //# 37E gw_y_top
	{0x7F, 0x04, 0, 0},   //# 37F gw_uv_radius
	{0x80, 0x40, 0, 0},   //# 380 uv_fix_dat
	{0x81, 0x20, 0, 0},   //# 381 y_offset_th
	{0x8F, 0x12, 0, 0},   //# 38F wt_th
	{0xCE, 0xD0, 0, 0},   //# 3CE exp_heq_dummy[7:0]
	{0xCF, 0x07, 0, 0},   //# 3CF exp_heq_dummy[12:8]
	{0xCD, 0x30, 0, 0},   //# 3CD rpc_heq_dummy
	{0xCA, 0x68, 0, 0},   //# 3CA mean_dummy_low
	{0xCB, 0x88, 0, 0},   //# 3CB mean_low_dummy
	{0xD0, 0xD0, 0, 0},   //# 3D0 exp_heq_low[7:0]
	{0xD1, 0x07, 0, 0},   //# 3D1 exp_heq_low[12:8]
	{0xCC, 0xC0, 0, 0},   //# 3CC rpc_heq_low
	{0xD5, 0x80, 0, 0},   //# 3D5 mean_nr_dummy
	{0xD6, 0x90, 0, 0},   //# 3D6 mean_dummy_nr
	{0xD7, 0x61, 0, 0},   //# 3D7 exp_nr_outd_8lsb
	{0xD8, 0x00, 0, 0},   //# 3D8 exp_nr_outd_5hsb
	{0xD9, 0x64, 0, 0},   //# 3D9 exp_outd_nr_8lsb
	{0xDA, 0x00, 0, 0},   //# 3DA exp_outd_nr_5hsb
//#
	{0xFD, 0x02, 0, 0},
	{0xB2, 0x30, 0, 0},   //# 2B2 lum_limit
	{0xB3, 0x18, 0, 0},   //# 2B3 lum_set
	{0xB4, 0x60, 0, 0},   //# 2B4 black_vt
	{0xB5, 0x70, 0, 0},   //# 2B5 white_vt
	{0xCB, 0x00, 0, 0},   //# 2CB rg_clip_ga_outdoor
	{0xCC, 0x02, 0, 0},   //# 2CC rg_clip_ga_nr
	{0xCD, 0x05, 0, 0},   //# 2CD rg_clip_ga_dummy
	{0xCE, 0x08, 0, 0},   //# 2CE rg_clip_ga_low
	{0xCF, 0x00, 0, 0},   //# 2CF bg_clip_ga_outdoor
	{0xD0, 0x02, 0, 0},   //# 2D0 bg_clip_ga_nr
//#
	{0xFD, 0x03, 0, 0},
	{0x10, 0x05, 0, 0},   //# 310 bg_clip_ga_dummy
	{0x14, 0x08, 0, 0},   //# 314 bg_clip_ga_low
//#
	{0xFD, 0x02, 0, 0},
	{0x5B, 0x00, 0, 0},   //# 25B cnr_thr_outdoor
	{0x61, 0x08, 0, 0},   //# 261 cnr_thr_nr
	{0x77, 0x40, 0, 0},   //# 277 cnr_thr_dummy
	{0xCA, 0x60, 0, 0},   //# 2CA cnr_thr_low
//	{0xAB, 0x10, 0, 0},   //# 2AB ynr_thr_outdoor
	{0xAB, 0x00, 0, 0},   //# 2AB ynr_thr_outdoor(1001)
	{0xAC, 0x10, 0, 0},   //# 2AC ynr_thr_nr
	{0xAE, 0x60, 0, 0},   //# 2AE ynr_thr_dummy
	{0xAF, 0x40, 0, 0},   //# 2AF ynr_thr_low
	{0x60, 0x01, 0, 0},   //# 260 bpc_vt_dummy
	{0x70, 0x0A, 0, 0},   //# 270 Bpc_v
	{0x76, 0x00, 0, 0},   //# 276 blacklevelin
	{0xC5, 0x60, 0, 0},   //# 2C5 raw_gflt_fac_indoor
	{0xDC, 0x00, 0, 0},   //# 2DC buf_heq_offset
	{0xDD, 0x80, 0, 0},   //# 2DD ku
	{0xDE, 0x90, 0, 0},   //# 2DE kl
//#
	{0xFD, 0x03, 0, 0},
	{0x06, 0x00, 0, 0},   //# 306 ratio_row[9:8]
	{0x07, 0x20, 0, 0},   //# 307 ratio_row[7:0]
	{0x08, 0x00, 0, 0},   //# 308 ratio_col[9:8]
	{0x09, 0x20, 0, 0},   //# 309 ratio_col[7:0]
	{0x0A, 0x02, 0, 0},   //# 30A scalerownum[10:8]
	{0x0B, 0x58, 0, 0},   //# 30B scalerownum[7:0]
	{0x0C, 0x03, 0, 0},   //# 30C scalecolnum[10:8]
	{0x0D, 0x20, 0, 0},   //# 30D scalecolnum[7:0]
	{0x0E, 0x00, 0, 0},   //# 30E resize_en
	{0x1C, 0xBA, 0, 0},   //# 31C f_limit_b
	{0x1D, 0x87, 0, 0},   //# 31D f_limit_r
	{0x41, 0x00, 0, 0},   //# 341 grgb_top_high_bit
	{0x42, 0x00, 0, 0},   //# 342 grgb_bot_high_bit
	{0x44, 0x0F, 0, 0},   //# 344 wb_num_th_light_s
	{0x4C, 0x48, 0, 0},   //# 34C raw_adt_fac_outdoor
	{0x4D, 0x48, 0, 0},   //# 34D raw_adt_fac_normal
	{0x4E, 0x48, 0, 0},   //# 34E raw_adt_fac_dummy
	{0x4F, 0x48, 0, 0},   //# 34F raw_adt_fac_low
	{0xC6, 0x40, 0, 0},   //# 3C6 pre_grgain
	{0xC7, 0x40, 0, 0},   //# 3C7 pre_rgain
	{0xC8, 0x40, 0, 0},   //# 3C8 pre_gbgain
	{0xC9, 0x40, 0, 0},   //# 3C9 pre_bgain
	{0xE2, 0x40, 0, 0},   //# 3E2 raw_sharp_y_base
	{0xE3, 0x10, 0, 0},   //# 3E3 raw_sharp_y_min
	{0xE4, 0xE0, 0, 0},   //# 3E4 raw_sharp_y_max
	{0xE5, 0x30, 0, 0},   //# 3E5 raw_sharp_rangek_neg
	{0xE6, 0x20, 0, 0},   //# 3E6 raw_sharp_rangek_pos
//#
	{0xFD, 0x02, 0, 0},
	{0x32, 0x0D, 0, 0},   //# 232 auto_mode
	{0x33, 0xEF, 0, 0},   //# 233 lsc_bpc_en
	{0x34, 0xFF, 0, 0},   //# 234 buf_isp_mode
	{0xFB, 0x00, 0, 0},   //# 2FB blackgain_en,bl_bpc_en,abl
	{0x36, 0x00, 0, 0},   //# 236 buf_outmode2
};

static struct reg_value rnss2e1_setting_30fps_SVGA_800_600[] = {
	{0xFD, 0x02, 0, 0},
	{0x36, 0x00, 0, 0},   //# 236 buf_outmode2
//#
	{0xFD, 0x00, 0, 0},
	{0x10, 0x1F, 0, 0},   //# 010 clk_mode
	{0x11, 0x40, 0, 0},   //# 011 pclk_inv,pclk_gate_en,pclk_ctrl,isp_clk_ctrl
	{0x20, 0x02, 0, 0},   //# 020 ds_data,out_end_high8,out_end_low2,out_ens
	{0x21, 0x03, 0, 0},   //# 021 pe_hvp,pe_data,ds_s,buf_dis_s,buf_dis_d
//#
	{0xFD, 0x01, 0, 0},
	{0x03, 0x02, 0, 0},   //# 103 buf_exp_5msb
	{0x04, 0x55, 0, 0},   //# 104 buf_exp_8lsb
	{0x09, 0x00, 0, 0},   //# 109 hblank_4msb
	{0x0A, 0x4E, 0, 0},   //# 10A hblank_8lsb
//#
	{0xFD, 0x00, 0, 0},
	{0x0E, 0x40, 0, 0},   //# 00E pd
//#
	{0xFD, 0x01, 0, 0},
	{0x0E, 0x00, 0, 0},   //# 10E p0
	{0x0F, 0x18, 0, 0},   //# 10F p1
	{0x10, 0x10, 0, 0},   //# 110 p2
	{0x11, 0x03, 0, 0},   //# 111 p3
	{0x12, 0x18, 0, 0},   //# 112 p4
	{0x13, 0x10, 0, 0},   //# 113 p5
	{0x14, 0x15, 0, 0},   //# 114 p6
	{0x15, 0x01, 0, 0},   //# 115 p7
	{0x16, 0x02, 0, 0},   //# 116 p8
	{0x17, 0x10, 0, 0},   //# 117 p9
	{0x18, 0x00, 0, 0},   //# 118 p10_2msb
	{0x19, 0x1A, 0, 0},   //# 119 p10_8lsb
	{0x1A, 0x00, 0, 0},   //# 11A p11_2msb
	{0x1B, 0x1C, 0, 0},   //# 11B p11_8lsb
	{0x50, 0x00, 0, 0},   //# 150 p12_2msb
	{0x51, 0x1D, 0, 0},   //# 151 p12_8lsb
	{0x52, 0x15, 0, 0},   //# 152 P13
	{0x2A, 0x02, 0, 0},   //# 12A p16
	{0x53, 0x00, 0, 0},   //# 153 p17_2msb
	{0x54, 0x11, 0, 0},   //# 154 p17_8lsb
	{0x55, 0x12, 0, 0},   //# 155 p18
	{0x56, 0x02, 0, 0},   //# 156 p19
	{0x57, 0x02, 0, 0},   //# 157 p20
	{0x58, 0x00, 0, 0},   //# 158 p21
//#
	{0xFD, 0x00, 0, 0},
	{0x12, 0x04, 0, 0},   //# 012 pll_bias_ctl,pll_delay
	{0x13, 0x04, 0, 0},   //# 013 mipi_pattern_en,pll_test_en,mipi_en
	{0x14, 0x00, 0, 0},   //# 014 pclk_gate,timer_clk_gate,dclk_gate
	{0x15, 0x00, 0, 0},   //# 015 pclk_pha_adj
//#
	{0xFD, 0x01, 0, 0},
//	{0x1C, 0x5C, 0, 0},   //# 11C two_timing_en,FPN_33ms_X,pwd_asp_timing_sel,Channel-timing
	{0x1C, 0x7C, 0, 0},   //# 11C two_timing_en,FPN_33ms_X,pwd_asp_timing_sel,Channel-timing
	{0x21, 0x44, 0, 0},   //# 121 adc_vcm_opin_ctl,adc_vcm_opin_c,col_clk_delay
	{0x22, 0x04, 0, 0},   //# 122 pga_bias_ctl,col_ctrl
	{0x25, 0x00, 0, 0},   //# 125 adc_range_ctl,adc_vcm_ctl,asp_delay
	{0x26, 0x26, 0, 0},   //# 126 adc_dig_offset,sw_delay
	{0x27, 0x6D, 0, 0},   //# 127 delay,black_en,adc_dref_cal,adc_g2x_en,adc_offset_en
	{0x2B, 0x66, 0, 0},   //# 12B adc_offset_ctl_buf_up,adc_offset_ctl_buf_dn
	{0x2C, 0x3F, 0, 0},   //# 12C strobe_en,bl_da
	{0x2D, 0x40, 0, 0},   //# 12D adc_bias_stage,adc_bias_vref
	{0x2E, 0x0D, 0, 0},   //# 12E dout_sel,strobe_sel
//	{0x40, 0xF0, 0, 0},   //# 140 vfpn_bpc_en,vfpn_minus_en
	{0x40, 0xF3, 0, 0},   //# 140 vfpn_bpc_en,vfpn_minus_en
	{0x41, 0x60, 0, 0},   //# 141 vfpn_bpc_th_x1
	{0x42, 0x50, 0, 0},   //# 142 vfpn_bpc_th_x2
	{0x43, 0x28, 0, 0},   //# 143 vfpn_bpc_in_x1
	{0x44, 0x28, 0, 0},   //# 144 vfpn_bpc_in_x2
//	{0x45, 0x0C, 0, 0},   //# 145 vfpn_delta
//	{0x45, 0x06, 0, 0},   //# 145 vfpn_delta(0830)
	{0x45, 0x00, 0, 0},   //# 145 vfpn_delta(0921)
	{0x31, 0x14, 0, 0},   //# 131 buf_comm_ctrl
//#
	{0xFD, 0x02, 0, 0},
	{0x35, 0x40, 0, 0},   //# 235 buf_outmode1
	{0x31, 0x10, 0, 0},   //# 231 digital_gain
	{0x47, 0x00, 0, 0},   //# 247 v_start_3msb
	{0x48, 0x00, 0, 0},   //# 248 v_start_8lsb
	{0x49, 0x04, 0, 0},   //# 249 v_size_3msb
	{0x4A, 0xB0, 0, 0},   //# 24A v_size_8lsb
	{0x4B, 0x00, 0, 0},   //# 24B h_start_3msb
	{0x4C, 0x00, 0, 0},   //# 24C h_start_8lsb
	{0x4D, 0x06, 0, 0},   //# 24D h_size_3msb
	{0x4E, 0x40, 0, 0},   //# 24E h_size_8lsb
//	{0x65, 0x08, 0, 0},   //# 265 blue_suboffset
//	{0x66, 0x06, 0, 0},   //# 266 red_suboffset
//	{0x67, 0x07, 0, 0},   //# 267 gr_suboffset
//	{0x68, 0x07, 0, 0},   //# 268 gb_suboffset
//	{0x65, 0x09, 0, 0},   //# 265 blue_suboffset(0830)
//	{0x66, 0x07, 0, 0},   //# 266 red_suboffset(0830)
//	{0x67, 0x08, 0, 0},   //# 267 gr_suboffset(0830)
//	{0x68, 0x08, 0, 0},   //# 268 gb_suboffset(0830)
	{0x65, 0x0F, 0, 0},   //# 265 blue_suboffset(0921)
	{0x66, 0x0D, 0, 0},   //# 266 red_suboffset(0921)
	{0x67, 0x0E, 0, 0},   //# 267 gr_suboffset(0921)
	{0x68, 0x0E, 0, 0},   //# 268 gb_suboffset(0921)
	{0x5F, 0x02, 0, 0},   //# 25F demo_gain_order,bayer_order
	{0x32, 0x00, 0, 0},   //# 232 auto_mode
	{0x33, 0xEF, 0, 0},   //# 233 lsc_bpc_en
	{0xA4, 0xFF, 0, 0},   //# 2A4 lsc_gain_max
//#
	{0xFD, 0x03, 0, 0},
	{0x66, 0x19, 0, 0},   //# 366 Lsc_rsy_u
	{0x6A, 0x1B, 0, 0},   //# 36A Lsc_gsy_u
	{0x6E, 0x14, 0, 0},   //# 36E Lsc_bsy_u
	{0x67, 0x19, 0, 0},   //# 367 Lsc_rsy_d
	{0x6B, 0x12, 0, 0},   //# 36B Lsc_gsy_d
	{0x6F, 0x14, 0, 0},   //# 36F Lsc_bsy_d
	{0x64, 0x1D, 0, 0},   //# 364 Lsc_rsx_l
	{0x68, 0x18, 0, 0},   //# 368 Lsc_gsx_l
	{0x6C, 0x14, 0, 0},   //# 36C Lsc_bsx_l
	{0x65, 0x15, 0, 0},   //# 365 Lsc_rsx_r
	{0x69, 0x12, 0, 0},   //# 369 Lsc_gsx_r
	{0x6D, 0x0E, 0, 0},   //# 36D Lsc_bsx_r
	{0xB8, 0x08, 0, 0},   //# 3B8 Lsc_rxy_lu
	{0xBC, 0x08, 0, 0},   //# 3BC Lsc_gxy_lu
	{0xC0, 0x08, 0, 0},   //# 3C0 Lsc_bxy_lu
	{0xB9, 0x08, 0, 0},   //# 3B9 Lsc_rxy_ru
	{0xBD, 0x08, 0, 0},   //# 3BD Lsc_gxy_ru
	{0xC1, 0x08, 0, 0},   //# 3C1 Lsc_bxy_ru
	{0xBA, 0x08, 0, 0},   //# 3BA Lsc_rxy_ld
	{0xBE, 0x08, 0, 0},   //# 3BE Lsc_gxy_ld
	{0xC2, 0x08, 0, 0},   //# 3C2 Lsc_bxy_ld
	{0xBB, 0x08, 0, 0},   //# 3BB Lsc_rxy_rd
	{0xBF, 0x08, 0, 0},   //# 3BF Lsc_gxy_rd
	{0xC3, 0x08, 0, 0},   //# 3C3 Lsc_bxy_rd
//#
	{0xFD, 0x02, 0, 0},
	{0x51, 0x00, 0, 0},   //# 251 bpc_vt_outdoor
	{0x52, 0x00, 0, 0},   //# 252 bpc_vt_normal
	{0x53, 0x00, 0, 0},   //# 253 bpc_vt_low_light
	{0x54, 0x00, 0, 0},   //# 254 bpc_wt_eff
	{0x55, 0xFF, 0, 0},   //# 255 bpc_dt_eff
//	{0x45, 0x00, 0, 0},   //# 245 bpc_range_ratio_outdoor,pc_range_ratio_nr
//	{0x46, 0x09, 0, 0},   //# 246 bpc_range_ratio_dummy,bpc_range_ratio_low
	{0x45, 0x13, 0, 0},   //# 245 bpc_range_ratio_outdoor,pc_range_ratio_nr (1001)
	{0x46, 0x49, 0, 0},   //# 246 bpc_range_ratio_dummy,bpc_range_ratio_low (1001)
	{0x69, 0x00, 0, 0},   //# 269 bpc_range_thr_outdoor
	{0x6A, 0x00, 0, 0},   //# 26A bpc_range_thr_nr
	{0x6B, 0x00, 0, 0},   //# 26B bpc_range_thr_dummy
	{0x6C, 0x00, 0, 0},   //# 26C bpc_range_thr_low
//#
	{0xFD, 0x03, 0, 0},
	{0xDE, 0x0F, 0, 0},   //# 3DE raw_denoise_en_outdoor,raw_denoise_en_nr,raw_denoise_en_dummy,raw_denoise_en_low
//#
	{0xFD, 0x02, 0, 0},
	{0x57, 0x04, 0, 0},   //# 257 raw_dif_thr_outdoor
	{0x58, 0x04, 0, 0},   //# 258 raw_dif_thr_normal
	{0x56, 0x0A, 0, 0},   //# 256 raw_dif_thr_dummy
	{0x59, 0x08, 0, 0},   //# 259 raw_dif_thr_low_light
	{0x4F, 0xE0, 0, 0},   //# 24F raw_gf_fac_outdoor
	{0xC3, 0xE0, 0, 0},   //# 2C3 raw_gf_fac_indoor
	{0x3F, 0xC0, 0, 0},   //# 23F raw_gf_fac_dummy
	{0x42, 0x40, 0, 0},   //# 242 raw_gf_fac_low
	{0x5A, 0xE0, 0, 0},   //# 25A raw_rb_fac_outdoor
	{0xC4, 0xE0, 0, 0},   //# 2C4 raw_rb_fac_indoor
	{0x43, 0xC0, 0, 0},   //# 243 raw_rb_fac_dummy
	{0xAD, 0x40, 0, 0},   //# 2AD raw_rb_fac_low
	{0xC2, 0x15, 0, 0},   //# 2C2 gf_ratiok_fac
//#
	{0xFD, 0x03, 0, 0},
	{0x50, 0x00, 0, 0},   //# 350 raw_grgb_thr_outdoor
	{0x51, 0x00, 0, 0},   //# 351 raw_grgb_thr_normal
	{0x52, 0x08, 0, 0},   //# 352 raw_grgb_thr_dummy
	{0x53, 0x08, 0, 0},   //# 353 raw_grgb_thr_low
//#
	{0xFD, 0x02, 0, 0},
	{0xB6, 0xE0, 0, 0},   //# 2B6 raw_gflt_fac_outdoor
	{0xB7, 0xC0, 0, 0},   //# 2B7 raw_gflt_fac_nr
	{0xB8, 0xA0, 0, 0},   //# 2B8 raw_gflt_fac_dummy
	{0xB9, 0x20, 0, 0},   //# 2B9 raw_gflt_fac_low
//#
	{0xFD, 0x03, 0, 0},
	{0x11, 0x1F, 0, 0},   //# 311 rg_dif_th
	{0x12, 0x1F, 0, 0},   //# 312 bg_dif_th
	{0x16, 0x1C, 0, 0},   //# 316 rgb_limit
	{0x18, 0x00, 0, 0},   //# 318 br_offset_f
	{0x19, 0x00, 0, 0},   //# 319 br_offset
	{0x1B, 0x80, 0, 0},   //# 31B rg_base
	{0x1A, 0x80, 0, 0},   //# 31A bg_base
	{0x43, 0x80, 0, 0},   //# 343 channel_sel,test_awb
	{0x1E, 0x17, 0, 0},   //# 31E wb_fine_gain_step,wb_rough_gain_step
	{0x1F, 0x19, 0, 0},   //# 31F wb_dif_fine_th,wb_dif_rough_th
//	{0x28, 0x9D, 0, 0},   //# 328 buf_rgain
//	{0x29, 0xA2, 0, 0},   //# 329 buf_bgain
	{0x28, 0x9E, 0, 0},   //# 328 buf_rgain(1001)
	{0x29, 0xAC, 0, 0},   //# 329 buf_bgain(1001)
//#
	{0xFD, 0x02, 0, 0},
	{0xE7, 0x03, 0, 0},   //# 2E7 reg_renew
	{0xE7, 0x00, 0, 0},   //# 2E7 reg_renew
//#
	{0xFD, 0x03, 0, 0},
	{0x2A, 0xF0, 0, 0},   //# 32A y_top_th
	{0x2B, 0x10, 0, 0},   //# 32B y_bot_th
	{0x2E, 0x04, 0, 0},   //# 32E rg_limit_log
	{0x2F, 0x16, 0, 0},   //# 32F bg_limit_log
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x80, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x80, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0x83, 0x70, 0, 0},   //# 383 skin_num_th
	{0x13, 0x43, 0, 0},   //# 313 awb_grey_en,awb_skin_en
	{0x24, 0x06, 0, 0},   //# 324 short_exp_th
	{0x25, 0x80, 0, 0},   //# 325 sp_rg_base
	{0x26, 0x80, 0, 0},   //# 326 sp_bg_base
	{0x35, 0xB2, 0, 0},   //# 335 d65_rg_bot
	{0x36, 0xCA, 0, 0},   //# 336 d65_rg_top
//	{0x37, 0x7C, 0, 0},   //# 337 d65_bg_bot
	{0x37, 0x73, 0, 0},   //# 337 d65_bg_bot(1001)
	{0x38, 0x94, 0, 0},   //# 338 d65_bg_top
//	{0x31, 0x7B, 0, 0},   //# 331 f_rg_bot
//	{0x32, 0x93, 0, 0},   //# 332 f_rg_top
//	{0x33, 0xAE, 0, 0},   //# 333 f_bg_bot
//	{0x34, 0xC6, 0, 0},   //# 334 f_bg_top
	{0x31, 0x60, 0, 0},   //# 331 f_rg_bot(1010)
	{0x32, 0x98, 0, 0},   //# 332 f_rg_top(1010)
	{0x33, 0xA8, 0, 0},   //# 333 f_bg_bot(1010)
	{0x34, 0xD8, 0, 0},   //# 334 f_bg_top(1010)
	{0x3D, 0x9C, 0, 0},   //# 33D cwf_rg_bot
	{0x3E, 0xB4, 0, 0},   //# 33E cwf_rg_top
	{0x3F, 0xA4, 0, 0},   //# 33F cwf_bg_bot
	{0x40, 0xBC, 0, 0},   //# 340 cwf_bg_top
	{0x39, 0x8A, 0, 0},   //# 339 tl84_rg_bot
	{0x3A, 0xA2, 0, 0},   //# 33A tl84_rg_top
	{0x3B, 0x9E, 0, 0},   //# 33B tl84_bg_bot
	{0x3C, 0xB6, 0, 0},   //# 33C tl84_bg_top
	{0xA0, 0xA6, 0, 0},   //# 3A0 c00_eff1_8lsb
	{0xA1, 0xCD, 0, 0},   //# 3A1 c01_eff1_8lsb
	{0xA2, 0x0C, 0, 0},   //# 3A2 c02_eff1_8lsb
	{0xA3, 0x06, 0, 0},   //# 3A3 c10_eff1_8lsb
	{0xA4, 0x8C, 0, 0},   //# 3A4 c11_eff1_8lsb
	{0xA5, 0xED, 0, 0},   //# 3A5 c12_eff1_8lsb
	{0xA6, 0x00, 0, 0},   //# 3A6 c20_eff1_8lsb
	{0xA7, 0xE7, 0, 0},   //# 3A7 c21_eff1_8lsb
	{0xA8, 0x99, 0, 0},   //# 3A8 c22_eff1_8lsb
	{0xA9, 0x0C, 0, 0},   //# 3A9 c02_eff1_2msb,c01_eff1_2msb,c00_eff1_2msb
	{0xAA, 0x30, 0, 0},   //# 3AA c12_eff1_2msb,c11_eff1_2msb,c10_eff1_2msb
	{0xAB, 0x0C, 0, 0},   //# 3AB c22_eff1_2msb,c21_eff1_2msb,c20_eff1_2msb
	{0xAC, 0x8C, 0, 0},   //# 3AC c00_eff2_8lsb
	{0xAD, 0xF4, 0, 0},   //# 3AD c01_eff2_8lsb
	{0xAE, 0x00, 0, 0},   //# 3AE c02_eff2_8lsb
	{0xAF, 0xFA, 0, 0},   //# 3AF c10_eff2_8lsb
	{0xB0, 0x8C, 0, 0},   //# 3B0 c11_eff2_8lsb
	{0xB1, 0xFA, 0, 0},   //# 3B1 c12_eff2_8lsb
	{0xB2, 0x0C, 0, 0},   //# 3B2 c20_eff2_8lsb
	{0xB3, 0xF4, 0, 0},   //# 3B3 c21_eff2_8lsb
	{0xB4, 0x80, 0, 0},   //# 3B4 c22_eff2_8lsb
	{0xB5, 0x0C, 0, 0},   //# 3B5 c02_eff2_2msb,c01_eff2_2msb,c00_eff2_2msb
	{0xB6, 0x33, 0, 0},   //# 3B6 c12_eff2_2msb,c11_eff2_2msb,c10_eff2_2msb
	{0xB7, 0x0C, 0, 0},   //# 3B7 c22_eff2_2msb,c21_eff2_2msb,c20_eff2_2msb
//#
	{0xFD, 0x02, 0, 0},
	{0xBF, 0x01, 0, 0},   //# 2BF autosa_en
	{0xBE, 0xAA, 0, 0},   //# 2BE u_v_th
	{0xC0, 0xFF, 0, 0},   //# 2C0 y_p_th
	{0xC1, 0xFF, 0, 0},   //# 2C1 y_mean_th
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
	{0x8B, 0x00, 0, 0},   //# 28B gamma_pt0
	{0x8C, 0x0F, 0, 0},   //# 28C gamma_pt1
	{0x8D, 0x1F, 0, 0},   //# 28D gamma_pt2
	{0x8E, 0x3C, 0, 0},   //# 28E gamma_pt3
	{0x8F, 0x67, 0, 0},   //# 28F gamma_pt4
	{0x90, 0x85, 0, 0},   //# 290 gamma_pt5
	{0x91, 0x99, 0, 0},   //# 291 gamma_pt6
	{0x92, 0xA8, 0, 0},   //# 292 gamma_pt7
	{0x93, 0xB5, 0, 0},   //# 293 gamma_pt8
	{0x94, 0xBE, 0, 0},   //# 294 gamma_pt9
	{0x95, 0xC8, 0, 0},   //# 295 gamma_pt10
	{0x96, 0xD1, 0, 0},   //# 296 gamma_pt11
	{0x97, 0xD9, 0, 0},   //# 297 gamma_pt12
	{0x98, 0xE0, 0, 0},   //# 298 gamma_pt13
	{0x99, 0xE8, 0, 0},   //# 299 gamma_pt14
	{0x9A, 0xED, 0, 0},   //# 29A gamma_pt15
	{0x9B, 0xF3, 0, 0},   //# 29B gamma_pt16
//#
	{0xFD, 0x03, 0, 0},
	{0x8D, 0xF9, 0, 0},   //# 38D gamma_pt17
	{0x8E, 0xFF, 0, 0},   //# 38E gamma_pt18
//#
	{0xFD, 0x02, 0, 0},
	{0x78, 0x00, 0, 0},   //# 278 gamma_pt2_0
	{0x79, 0x0F, 0, 0},   //# 279 gamma_pt2_1
	{0x7A, 0x1F, 0, 0},   //# 27A gamma_pt2_2
	{0x7B, 0x3C, 0, 0},   //# 27B gamma_pt2_3
	{0x7C, 0x67, 0, 0},   //# 27C gamma_pt2_4
	{0x7D, 0x85, 0, 0},   //# 27D gamma_pt2_5
	{0x7E, 0x99, 0, 0},   //# 27E gamma_p2_6
	{0x7F, 0xA8, 0, 0},   //# 27F gamma_pt2_7
	{0x80, 0xB5, 0, 0},   //# 280 gamma_pt2_8
	{0x81, 0xBE, 0, 0},   //# 281 gamma_pt2_9
	{0x82, 0xC8, 0, 0},   //# 282 gamma_pt2_10
	{0x83, 0xD1, 0, 0},   //# 283 gamma_pt2_11
	{0x84, 0xD9, 0, 0},   //# 284 gamma_pt2_12
	{0x85, 0xE0, 0, 0},   //# 285 gamma_pt2_13
	{0x86, 0xE8, 0, 0},   //# 286 gamma_pt2_14
	{0x87, 0xED, 0, 0},   //# 287 gamma_pt2_15
	{0x88, 0xF3, 0, 0},   //# 288 gamma_pt2_16
	{0x89, 0xF9, 0, 0},   //# 289 gamma_pt2_17
	{0x8A, 0xFF, 0, 0},   //# 28A gamma_pt2_18
//#
	{0xFD, 0x03, 0, 0},
	{0x96, 0x46, 0, 0},   //# 396 ae time thr1
	{0x97, 0x28, 0, 0},   //# 397 ae time thr2
	{0x9F, 0x0A, 0, 0},   //# 39F gma_ratiok_fac
//#
	{0xFD, 0x02, 0, 0},
	{0xF4, 0x0B, 0, 0},   //# 2F4 lum_fcase_en,lum_down_en,outdoor_mode_en,mean_mode_reg
	{0xF0, 0xC7, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 exp_min_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
	{0x95, 0x20, 0, 0},   //# 395 rpc_min_indr
	{0x98, 0xC7, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_outdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x9C, 0x32, 0, 0},   //# 39C rpc_max_outdr
	{0x9D, 0x20, 0, 0},   //# 39D rpc_min_outdr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x55, 0x11, 0, 0},   //# 355 weight_w2,weight_w1
	{0x56, 0x11, 0, 0},   //# 356 weight_w4,weight_w3
//	{0x57, 0x03, 0, 0},   //# 357 weight_w5
	{0x57, 0x01, 0, 0},   //# 357 weight_w5(1001)
//#
	{0xFD, 0x02, 0, 0},
	{0xE0, 0x3E, 0, 0},   //# 2E0 rpc_1base_max
	{0xE1, 0x26, 0, 0},   //# 2E1 rpc_2base_max
	{0xE2, 0x2A, 0, 0},   //# 2E2 rpc_3base_max
	{0xE3, 0x26, 0, 0},   //# 2E3 rpc_4base_max
	{0xE4, 0x26, 0, 0},   //# 2E4 rpc_5base_max
	{0xE5, 0x24, 0, 0},   //# 2E5 rpc_6base_max
	{0xE6, 0x24, 0, 0},   //# 2E6 rpc_7base_max
	{0xE8, 0x22, 0, 0},   //# 2E8 rpc_8base_max
	{0xE9, 0x22, 0, 0},   //# 2E9 rpc_9base_max
	{0xEA, 0x22, 0, 0},   //# 2EA rpc_10base_max
	{0xEB, 0x20, 0, 0},   //# 2EB rpc_11base_max
	{0xF5, 0x20, 0, 0},   //# 2F5 rpc_12base_max
	{0xF6, 0x20, 0, 0},   //# 2F6 rpc_13base_max
	{0xF3, 0x03, 0, 0},   //# 2F3 uv_dif_en_outdoor,uv_dif_en_nr,uv_dif_en_dummy,uv_dif_en_low
	{0xB0, 0x00, 0, 0},   //# 2B0 uv_dif_gain_outdoor,uv_dif_gain_nr
	{0xB1, 0x12, 0, 0},   //# 2B1 uv_dif_gain_dummy,uv_dif_gain_low
//#
	{0xFD, 0x03, 0, 0},
	{0xDF, 0x0F, 0, 0},   //# 3DF sharpness
	{0xE7, 0x08, 0, 0},   //# 3E7 raw_sharp_range_base
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
	{0x70, 0x73, 0, 0},   //# 370 aec_gw_en,gw_uv_dif_en,gw_detect_en,gw_step
	{0x7B, 0x40, 0, 0},   //# 37B gw_mean_th
	{0x71, 0x2F, 0, 0},   //# 371 k_up
	{0x72, 0x0D, 0, 0},   //# 372 k_low
	{0x73, 0x0A, 0, 0},   //# 373 b_up
	{0x74, 0x2A, 0, 0},   //# 374 b_low
	{0x75, 0x04, 0, 0},   //# 375 uv_low_th
	{0x76, 0x20, 0, 0},   //# 376 y_low_th
	{0x77, 0x32, 0, 0},   //# 377 u_top
	{0x78, 0x00, 0, 0},   //# 378 u_bot
	{0x79, 0x28, 0, 0},   //# 379 v_top
	{0x7A, 0x00, 0, 0},   //# 37A v_bot
	{0x7C, 0x70, 0, 0},   //# 37C gw_offset
	{0x7D, 0x90, 0, 0},   //# 37D gw_y_bot
	{0x7E, 0xEF, 0, 0},   //# 37E gw_y_top
	{0x7F, 0x04, 0, 0},   //# 37F gw_uv_radius
	{0x80, 0x40, 0, 0},   //# 380 uv_fix_dat
	{0x81, 0x20, 0, 0},   //# 381 y_offset_th
	{0x8F, 0x12, 0, 0},   //# 38F wt_th
	{0xCE, 0x8C, 0, 0},   //# 3CE exp_heq_dummy[7:0]
	{0xCF, 0x0F, 0, 0},   //# 3CF exp_heq_dummy[12:8]
	{0xCD, 0x30, 0, 0},   //# 3CD rpc_heq_dummy
	{0xCA, 0x68, 0, 0},   //# 3CA mean_dummy_low
	{0xCB, 0x88, 0, 0},   //# 3CB mean_low_dummy
	{0xD0, 0x8C, 0, 0},   //# 3D0 exp_heq_low[7:0]
	{0xD1, 0x0F, 0, 0},   //# 3D1 exp_heq_low[12:8]
	{0xCC, 0xC0, 0, 0},   //# 3CC rpc_heq_low
	{0xD5, 0x80, 0, 0},   //# 3D5 mean_nr_dummy
	{0xD6, 0x90, 0, 0},   //# 3D6 mean_dummy_nr
	{0xD7, 0xC4, 0, 0},   //# 3D7 exp_nr_outd_8lsb
	{0xD8, 0x00, 0, 0},   //# 3D8 exp_nr_outd_5hsb
	{0xD9, 0xC7, 0, 0},   //# 3D9 exp_outd_nr_8lsb
	{0xDA, 0x00, 0, 0},   //# 3DA exp_outd_nr_5hsb
//#
	{0xFD, 0x02, 0, 0},
	{0xB2, 0x30, 0, 0},   //# 2B2 lum_limit
	{0xB3, 0x18, 0, 0},   //# 2B3 lum_set
	{0xB4, 0x60, 0, 0},   //# 2B4 black_vt
	{0xB5, 0x70, 0, 0},   //# 2B5 white_vt
	{0xCB, 0x00, 0, 0},   //# 2CB rg_clip_ga_outdoor
	{0xCC, 0x02, 0, 0},   //# 2CC rg_clip_ga_nr
	{0xCD, 0x05, 0, 0},   //# 2CD rg_clip_ga_dummy
	{0xCE, 0x08, 0, 0},   //# 2CE rg_clip_ga_low
	{0xCF, 0x00, 0, 0},   //# 2CF bg_clip_ga_outdoor
	{0xD0, 0x02, 0, 0},   //# 2D0 bg_clip_ga_nr
//#
	{0xFD, 0x03, 0, 0},
	{0x10, 0x05, 0, 0},   //# 310 bg_clip_ga_dummy
	{0x14, 0x08, 0, 0},   //# 314 bg_clip_ga_low
//#
	{0xFD, 0x02, 0, 0},
	{0x5B, 0x00, 0, 0},   //# 25B cnr_thr_outdoor
	{0x61, 0x08, 0, 0},   //# 261 cnr_thr_nr
	{0x77, 0x40, 0, 0},   //# 277 cnr_thr_dummy
	{0xCA, 0x60, 0, 0},   //# 2CA cnr_thr_low
//	{0xAB, 0x10, 0, 0},   //# 2AB ynr_thr_outdoor
	{0xAB, 0x00, 0, 0},   //# 2AB ynr_thr_outdoor(1001)
	{0xAC, 0x10, 0, 0},   //# 2AC ynr_thr_nr
	{0xAE, 0x60, 0, 0},   //# 2AE ynr_thr_dummy
	{0xAF, 0x40, 0, 0},   //# 2AF ynr_thr_low
	{0x60, 0x01, 0, 0},   //# 260 bpc_vt_dummy
	{0x70, 0x0A, 0, 0},   //# 270 Bpc_v
	{0x76, 0x00, 0, 0},   //# 276 blacklevelin
	{0xC5, 0x60, 0, 0},   //# 2C5 raw_gflt_fac_indoor
	{0xDC, 0x00, 0, 0},   //# 2DC buf_heq_offset
	{0xDD, 0x80, 0, 0},   //# 2DD ku
	{0xDE, 0x90, 0, 0},   //# 2DE kl
//#
	{0xFD, 0x03, 0, 0},
	{0x06, 0x00, 0, 0},   //# 306 ratio_row[9:8]
	{0x07, 0x25, 0, 0},   //# 307 ratio_row[7:0]
	{0x08, 0x00, 0, 0},   //# 308 ratio_col[9:8]
	{0x09, 0x28, 0, 0},   //# 309 ratio_col[7:0]
	{0x0A, 0x04, 0, 0},   //# 30A scalerownum[10:8]
	{0x0B, 0x00, 0, 0},   //# 30B scalerownum[7:0]
	{0x0C, 0x05, 0, 0},   //# 30C scalecolnum[10:8]
	{0x0D, 0x00, 0, 0},   //# 30D scalecolnum[7:0]
	{0x0E, 0x00, 0, 0},   //# 30E resize_en
	{0x1C, 0xBA, 0, 0},   //# 31C f_limit_b
	{0x1D, 0x87, 0, 0},   //# 31D f_limit_r
	{0x41, 0x00, 0, 0},   //# 341 grgb_top_high_bit
	{0x42, 0x00, 0, 0},   //# 342 grgb_bot_high_bit
	{0x44, 0x0F, 0, 0},   //# 344 wb_num_th_light_s
	{0x4C, 0x48, 0, 0},   //# 34C raw_adt_fac_outdoor
	{0x4D, 0x48, 0, 0},   //# 34D raw_adt_fac_normal
	{0x4E, 0x48, 0, 0},   //# 34E raw_adt_fac_dummy
	{0x4F, 0x48, 0, 0},   //# 34F raw_adt_fac_low
	{0xC6, 0x40, 0, 0},   //# 3C6 pre_grgain
	{0xC7, 0x40, 0, 0},   //# 3C7 pre_rgain
	{0xC8, 0x40, 0, 0},   //# 3C8 pre_gbgain
	{0xC9, 0x40, 0, 0},   //# 3C9 pre_bgain
	{0xE2, 0x40, 0, 0},   //# 3E2 raw_sharp_y_base
	{0xE3, 0x10, 0, 0},   //# 3E3 raw_sharp_y_min
	{0xE4, 0xE0, 0, 0},   //# 3E4 raw_sharp_y_max
	{0xE5, 0x30, 0, 0},   //# 3E5 raw_sharp_rangek_neg
	{0xE6, 0x20, 0, 0},   //# 3E6 raw_sharp_rangek_pos
//#
	{0xFD, 0x02, 0, 0},
	{0x32, 0x0D, 0, 0},   //# 232 auto_mode
	{0x33, 0xEF, 0, 0},   //# 233 lsc_bpc_en
	{0x34, 0xFF, 0, 0},   //# 234 buf_isp_mode
	{0xFB, 0x00, 0, 0},   //# 2FB blackgain_en,bl_bpc_en,abl
	{0x36, 0x00, 0, 0},   //# 236 buf_outmode2
};


//----- XGA -------
static struct reg_value rnss2e1_setting_12fps_XGA_1024_768[] = {
	{0xFD, 0x02, 0, 0},
	{0x36, 0x00, 0, 0},   //# 236 buf_outmode2
//#
	{0xFD, 0x00, 0, 0},
	{0x10, 0x1E, 0, 0},   //# 010 clk_mode
	{0x11, 0x40, 0, 0},   //# 011 pclk_inv,pclk_gate_en,pclk_ctrl,isp_clk_ctrl
//	{0x20, 0x02, 0, 0},   //# 020 ds_data,out_end_high8,out_end_low2,out_ens
	{0x20, 0x0A, 0, 0},   //# 020 ds_data,out_end_high8,out_end_low2,out_ens
	{0x21, 0x01, 0, 0},   //# 021 pe_hvp,pe_data,ds_s,buf_dis_s,buf_dis_d
//#
	{0xFD, 0x01, 0, 0},
	{0x03, 0x01, 0, 0},   //# 103 buf_exp_5msb
	{0x04, 0x6E, 0, 0},   //# 104 buf_exp_8lsb
	{0x09, 0x00, 0, 0},   //# 109 hblank_4msb
	{0x0A, 0x53, 0, 0},   //# 10A hblank_8lsb
//#
	{0xFD, 0x00, 0, 0},
	{0x0E, 0x40, 0, 0},   //# 00E pd
//#
	{0xFD, 0x01, 0, 0},
	{0x0E, 0x00, 0, 0},   //# 10E p0
	{0x0F, 0x18, 0, 0},   //# 10F p1
	{0x10, 0x10, 0, 0},   //# 110 p2
	{0x11, 0x03, 0, 0},   //# 111 p3
	{0x12, 0x18, 0, 0},   //# 112 p4
	{0x13, 0x10, 0, 0},   //# 113 p5
	{0x14, 0x15, 0, 0},   //# 114 p6
	{0x15, 0x01, 0, 0},   //# 115 p7
	{0x16, 0x02, 0, 0},   //# 116 p8
	{0x17, 0x10, 0, 0},   //# 117 p9
	{0x18, 0x00, 0, 0},   //# 118 p10_2msb
	{0x19, 0x1A, 0, 0},   //# 119 p10_8lsb
	{0x1A, 0x00, 0, 0},   //# 11A p11_2msb
	{0x1B, 0x1C, 0, 0},   //# 11B p11_8lsb
	{0x50, 0x00, 0, 0},   //# 150 p12_2msb
	{0x51, 0x1D, 0, 0},   //# 151 p12_8lsb
	{0x52, 0x15, 0, 0},   //# 152 P13
	{0x2A, 0x02, 0, 0},   //# 12A p16
	{0x53, 0x00, 0, 0},   //# 153 p17_2msb
	{0x54, 0x11, 0, 0},   //# 154 p17_8lsb
	{0x55, 0x12, 0, 0},   //# 155 p18
	{0x56, 0x02, 0, 0},   //# 156 p19
	{0x57, 0x02, 0, 0},   //# 157 p20
	{0x58, 0x00, 0, 0},   //# 158 p21
//#
	{0xFD, 0x00, 0, 0},
	{0x12, 0x04, 0, 0},   //# 012 pll_bias_ctl,pll_delay
	{0x13, 0x04, 0, 0},   //# 013 mipi_pattern_en,pll_test_en,mipi_en
	{0x14, 0x00, 0, 0},   //# 014 pclk_gate,timer_clk_gate,dclk_gate
	{0x15, 0x00, 0, 0},   //# 015 pclk_pha_adj
//#
	{0xFD, 0x01, 0, 0},
	{0x1C, 0x7C, 0, 0},   //# 11C 
	{0x21, 0x44, 0, 0},   //# 121 adc_vcm_opin_ctl,adc_vcm_opin_c,col_clk_delay
	{0x22, 0x04, 0, 0},   //# 122 pga_bias_ctl,col_ctrl
	{0x25, 0x00, 0, 0},   //# 125 adc_range_ctl,adc_vcm_ctl,asp_delay
	{0x26, 0x26, 0, 0},   //# 126 adc_dig_offset,sw_delay
	{0x27, 0x6F, 0, 0},   //# 127 
	{0x2B, 0x33, 0, 0},   //# 12B adc_offset_ctl_buf_up,adc_offset_ctl_buf_dn
	{0x2C, 0x3E, 0, 0},   //# 12C strobe_en,bl_da
	{0x2D, 0x45, 0, 0},   //# 12D adc_bias_stage,adc_bias_vref
	{0x2E, 0x0C, 0, 0},   //# 12E dout_sel,strobe_sel
	{0x40, 0xF1, 0, 0},   //# 140 vfpn_bpc_en,vfpn_minus_en
	{0x41, 0x30, 0, 0},   //# 141 vfpn_bpc_th_x1
	{0x42, 0x30, 0, 0},   //# 142 vfpn_bpc_th_x2
	{0x43, 0x20, 0, 0},   //# 143 vfpn_bpc_in_x1
	{0x44, 0x20, 0, 0},   //# 144 vfpn_bpc_in_x2
	{0x45, 0x0F, 0, 0},   //# 145 vfpn_delta
	{0x31, 0x10, 0, 0},   //# 131 buf_comm_ctrl
//#
	{0xFD, 0x02, 0, 0},
	{0x35, 0x40, 0, 0},   //# 235 buf_outmode1
	{0x31, 0x10, 0, 0},   //# 231 digital_gain
	{0x47, 0x00, 0, 0},   //# 247 v_start_3msb
	{0x48, 0xD8, 0, 0},   //# 248 v_start_8lsb
	{0x49, 0x03, 0, 0},   //# 249 v_size_3msb
	{0x4A, 0x00, 0, 0},   //# 24A v_size_8lsb
	{0x4B, 0x01, 0, 0},   //# 24B h_start_3msb
	{0x4C, 0x20, 0, 0},   //# 24C h_start_8lsb
	{0x4D, 0x04, 0, 0},   //# 24D h_size_3msb
	{0x4E, 0x00, 0, 0},   //# 24E h_size_8lsb
	{0x65, 0x12, 0, 0},   //# 265 blue_suboffset
	{0x66, 0x12, 0, 0},   //# 266 red_suboffset
	{0x67, 0x12, 0, 0},   //# 267 gr_suboffset
	{0x68, 0x12, 0, 0},   //# 268 gb_suboffset
	{0x5F, 0x02, 0, 0},   //# 25F demo_gain_order,bayer_order
	{0x32, 0x00, 0, 0},   //# 232 auto_mode
	{0x33, 0xEF, 0, 0},   //# 233 lsc_bpc_en
	{0xA4, 0xFF, 0, 0},   //# 2A4 lsc_gain_max
//#
	{0xFD, 0x03, 0, 0},
	{0x66, 0x1C, 0, 0},   //# 366 Lsc_rsy_u
	{0x6A, 0x1A, 0, 0},   //# 36A Lsc_gsy_u
	{0x6E, 0x1A, 0, 0},   //# 36E Lsc_bsy_u
	{0x67, 0x16, 0, 0},   //# 367 Lsc_rsy_d
	{0x6B, 0x16, 0, 0},   //# 36B Lsc_gsy_d
	{0x6F, 0x1C, 0, 0},   //# 36F Lsc_bsy_d
	{0x64, 0x0F, 0, 0},   //# 364 Lsc_rsx_l
	{0x68, 0x0C, 0, 0},   //# 368 Lsc_gsx_l
	{0x6C, 0x0C, 0, 0},   //# 36C Lsc_bsx_l
	{0x65, 0x0D, 0, 0},   //# 365 Lsc_rsx_r
	{0x69, 0x0D, 0, 0},   //# 369 Lsc_gsx_r
	{0x6D, 0x0C, 0, 0},   //# 36D Lsc_bsx_r
	{0xB8, 0xF8, 0, 0},   //# 3B8 Lsc_rxy_lu
	{0xBC, 0xF8, 0, 0},   //# 3BC Lsc_gxy_lu
	{0xC0, 0xF8, 0, 0},   //# 3C0 Lsc_bxy_lu
	{0xB9, 0xFE, 0, 0},   //# 3B9 Lsc_rxy_ru
	{0xBD, 0xFE, 0, 0},   //# 3BD Lsc_gxy_ru
	{0xC1, 0xFE, 0, 0},   //# 3C1 Lsc_bxy_ru
	{0xBA, 0x00, 0, 0},   //# 3BA Lsc_rxy_ld
	{0xBE, 0x00, 0, 0},   //# 3BE Lsc_gxy_ld
	{0xC2, 0x08, 0, 0},   //# 3C2 Lsc_bxy_ld
	{0xBB, 0x00, 0, 0},   //# 3BB Lsc_rxy_rd
	{0xBF, 0xF8, 0, 0},   //# 3BF Lsc_gxy_rd
	{0xC3, 0x00, 0, 0},   //# 3C3 Lsc_bxy_rd
//#
	{0xFD, 0x02, 0, 0},
	{0x51, 0x00, 0, 0},   //# 251 bpc_vt_outdoor
	{0x52, 0x00, 0, 0},   //# 252 bpc_vt_normal
	{0x53, 0x00, 0, 0},   //# 253 bpc_vt_low_light
	{0x54, 0x00, 0, 0},   //# 254 bpc_wt_eff
	{0x55, 0xFF, 0, 0},   //# 255 bpc_dt_eff
//	{0x45, 0x00, 0, 0},   //# 245 bpc_range_ratio_outdoor,pc_range_ratio_nr
//	{0x46, 0x09, 0, 0},   //# 246 bpc_range_ratio_dummy,bpc_range_ratio_low
	{0x45, 0x13, 0, 0},   //# 245 bpc_range_ratio_outdoor,pc_range_ratio_nr (1001)
	{0x46, 0x49, 0, 0},   //# 246 bpc_range_ratio_dummy,bpc_range_ratio_low (1001)
	{0x69, 0x00, 0, 0},   //# 269 bpc_range_thr_outdoor
	{0x6A, 0x00, 0, 0},   //# 26A bpc_range_thr_nr
	{0x6B, 0x00, 0, 0},   //# 26B bpc_range_thr_dummy
	{0x6C, 0x00, 0, 0},   //# 26C bpc_range_thr_low
//#
	{0xFD, 0x03, 0, 0},
	{0xDE, 0x0F, 0, 0},   //# 3DE raw_denoise_en_outdoor,raw_denoise_en_nr,raw_denoise_en_dummy,raw_denoise_en_low
//#
	{0xFD, 0x02, 0, 0},
	{0x57, 0x06, 0, 0},   //# 257 raw_dif_thr_outdoor
	{0x58, 0x06, 0, 0},   //# 258 raw_dif_thr_normal
	{0x56, 0x0A, 0, 0},   //# 256 raw_dif_thr_dummy
	{0x59, 0x10, 0, 0},   //# 259 raw_dif_thr_low_light
	{0x4F, 0xE0, 0, 0},   //# 24F raw_gf_fac_outdoor
	{0xC3, 0x60, 0, 0},   //# 2C3 raw_gf_fac_indoor
	{0x3F, 0x40, 0, 0},   //# 23F raw_gf_fac_dummy
	{0x42, 0x40, 0, 0},   //# 242 raw_gf_fac_low
	{0x5A, 0xC0, 0, 0},   //# 25A raw_rb_fac_outdoor
	{0xC4, 0x60, 0, 0},   //# 2C4 raw_rb_fac_indoor
	{0x43, 0x40, 0, 0},   //# 243 raw_rb_fac_dummy
	{0xAD, 0x40, 0, 0},   //# 2AD raw_rb_fac_low
	{0xC2, 0x15, 0, 0},   //# 2C2 gf_ratiok_fac
//#
	{0xFD, 0x03, 0, 0},
	{0x50, 0x03, 0, 0},   //# 350 raw_grgb_thr_outdoor
	{0x51, 0x06, 0, 0},   //# 351 raw_grgb_thr_normal
	{0x52, 0x0A, 0, 0},   //# 352 raw_grgb_thr_dummy
	{0x53, 0x10, 0, 0},   //# 353 raw_grgb_thr_low
//#
	{0xFD, 0x02, 0, 0},
	{0xB6, 0xC0, 0, 0},   //# 2B6 raw_gflt_fac_outdoor
	{0xB7, 0x60, 0, 0},   //# 2B7 raw_gflt_fac_nr
	{0xB8, 0x40, 0, 0},   //# 2B8 raw_gflt_fac_dummy
	{0xB9, 0x20, 0, 0},   //# 2B9 raw_gflt_fac_low
//#
	{0xFD, 0x03, 0, 0},
	{0x11, 0x1F, 0, 0},   //# 311 rg_dif_th
	{0x12, 0x1F, 0, 0},   //# 312 bg_dif_th
	{0x16, 0x1C, 0, 0},   //# 316 rgb_limit
	{0x18, 0x00, 0, 0},   //# 318 br_offset_f
	{0x19, 0x00, 0, 0},   //# 319 br_offset
	{0x1B, 0xA3, 0, 0},   //# 31B rg_base
	{0x1A, 0x9A, 0, 0},   //# 31A bg_base
	{0x1E, 0x27, 0, 0},   //# 31E wb_fine_gain_step,wb_rough_gain_step
	{0x1F, 0x29, 0, 0},   //# 31F wb_dif_fine_th,wb_dif_rough_th
	{0x28, 0xBF, 0, 0},   //# 328 buf_rgain
	{0x29, 0x7A, 0, 0},   //# 329 buf_bgain
//#
	{0xFD, 0x02, 0, 0},
	{0xE7, 0x03, 0, 0},   //# 2E7 reg_renew
	{0xE7, 0x00, 0, 0},   //# 2E7 reg_renew
//#
	{0xFD, 0x03, 0, 0},
	{0x2A, 0xF0, 0, 0},   //# 32A y_top_th
	{0x2B, 0x10, 0, 0},   //# 32B y_bot_th
	{0x2E, 0x0D, 0, 0},   //# 32E rg_limit_log
	{0x2F, 0x0D, 0, 0},   //# 32F bg_limit_log
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x60, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x60, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0x83, 0x70, 0, 0},   //# 383 skin_num_th
	{0x13, 0x43, 0, 0},   //# 313 awb_grey_en,awb_skin_en
	{0x24, 0x06, 0, 0},   //# 324 
	{0x25, 0x80, 0, 0},   //# 325 
	{0x26, 0x80, 0, 0},   //# 326 
	{0x35, 0xAC, 0, 0},   //# 335 d65_rg_bot
	{0x36, 0xCC, 0, 0},   //# 336 d65_rg_top
//	{0x37, 0x7C, 0, 0},   //# 337 d65_bg_bot
	{0x37, 0x73, 0, 0},   //# 337 d65_bg_bot(1001)
	{0x38, 0x88, 0, 0},   //# 338 d65_bg_top
//	{0x31, 0x7B, 0, 0},   //# 331 f_rg_bot
//	{0x32, 0x93, 0, 0},   //# 332 f_rg_top
//	{0x33, 0xAE, 0, 0},   //# 333 f_bg_bot
//	{0x34, 0xC6, 0, 0},   //# 334 f_bg_top
	{0x31, 0x60, 0, 0},   //# 331 f_rg_bot(1010)
	{0x32, 0x98, 0, 0},   //# 332 f_rg_top(1010)
	{0x33, 0xA8, 0, 0},   //# 333 f_bg_bot(1010)
	{0x34, 0xD8, 0, 0},   //# 334 f_bg_top(1010)
	{0x3D, 0x98, 0, 0},   //# 33D cwf_rg_bot
	{0x3E, 0xB8, 0, 0},   //# 33E cwf_rg_top
	{0x3F, 0x93, 0, 0},   //# 33F cwf_bg_bot
	{0x40, 0xB3, 0, 0},   //# 340 cwf_bg_top
	{0x39, 0x82, 0, 0},   //# 339 tl84_rg_bot
	{0x3A, 0xA2, 0, 0},   //# 33A tl84_rg_top
	{0x3B, 0x8B, 0, 0},   //# 33B tl84_bg_bot
	{0x3C, 0xAB, 0, 0},   //# 33C tl84_bg_top
	{0xA0, 0xB8, 0, 0},   //# 3A0 c00_eff1_8lsb
	{0xA1, 0xD5, 0, 0},   //# 3A1 c01_eff1_8lsb
	{0xA2, 0xF2, 0, 0},   //# 3A2 c02_eff1_8lsb
	{0xA3, 0xE8, 0, 0},   //# 3A3 c10_eff1_8lsb
	{0xA4, 0x95, 0, 0},   //# 3A4 c11_eff1_8lsb
	{0xA5, 0x03, 0, 0},   //# 3A5 c12_eff1_8lsb
	{0xA6, 0xF2, 0, 0},   //# 3A6 c20_eff1_8lsb
	{0xA7, 0xC4, 0, 0},   //# 3A7 c21_eff1_8lsb
	{0xA8, 0xCA, 0, 0},   //# 3A8 c22_eff1_8lsb
	{0xA9, 0x3C, 0, 0},   //# 3A9 c02_eff1_2msb,c01_eff1_2msb,c00_eff1_2msb
	{0xAA, 0x03, 0, 0},   //# 3AA c12_eff1_2msb,c11_eff1_2msb,c10_eff1_2msb
	{0xAB, 0x0F, 0, 0},   //# 3AB c22_eff1_2msb,c21_eff1_2msb,c20_eff1_2msb
	{0xAC, 0xB8, 0, 0},   //# 3AC c00_eff2_8lsb
	{0xAD, 0xD5, 0, 0},   //# 3AD c01_eff2_8lsb
	{0xAE, 0xF2, 0, 0},   //# 3AE c02_eff2_8lsb
	{0xAF, 0xE8, 0, 0},   //# 3AF c10_eff2_8lsb
	{0xB0, 0x95, 0, 0},   //# 3B0 c11_eff2_8lsb
	{0xB1, 0x03, 0, 0},   //# 3B1 c12_eff2_8lsb
	{0xB2, 0xF2, 0, 0},   //# 3B2 c20_eff2_8lsb
	{0xB3, 0xC4, 0, 0},   //# 3B3 c21_eff2_8lsb
	{0xB4, 0xCA, 0, 0},   //# 3B4 c22_eff2_8lsb
	{0xB5, 0x3C, 0, 0},   //# 3B5 c02_eff2_2msb,c01_eff2_2msb,c00_eff2_2msb
	{0xB6, 0x03, 0, 0},   //# 3B6 c12_eff2_2msb,c11_eff2_2msb,c10_eff2_2msb
	{0xB7, 0x0F, 0, 0},   //# 3B7 c22_eff2_2msb,c21_eff2_2msb,c20_eff2_2msb
//#
	{0xFD, 0x02, 0, 0},
	{0xBF, 0x01, 0, 0},   //# 2BF autosa_en
	{0xBE, 0xAA, 0, 0},   //# 2BE u_v_th
	{0xC0, 0xB0, 0, 0},   //# 2C0 y_p_th
	{0xC1, 0xF0, 0, 0},   //# 2C1 y_mean_th
	{0xD3, 0x70, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x60, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x60, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x60, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x60, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x58, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x58, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x58, 0, 0},   //# 2DB sat_v_s4
	{0x8B, 0x00, 0, 0},   //# 28B gamma_pt0
	{0x8C, 0x14, 0, 0},   //# 28C gamma_pt1
	{0x8D, 0x24, 0, 0},   //# 28D gamma_pt2
	{0x8E, 0x3A, 0, 0},   //# 28E gamma_pt3
	{0x8F, 0x59, 0, 0},   //# 28F gamma_pt4
	{0x90, 0x6F, 0, 0},   //# 290 gamma_pt5
	{0x91, 0x84, 0, 0},   //# 291 gamma_pt6
	{0x92, 0x95, 0, 0},   //# 292 gamma_pt7
	{0x93, 0xA3, 0, 0},   //# 293 gamma_pt8
	{0x94, 0xB1, 0, 0},   //# 294 gamma_pt9
	{0x95, 0xBE, 0, 0},   //# 295 gamma_pt10
	{0x96, 0xC7, 0, 0},   //# 296 gamma_pt11
	{0x97, 0xD1, 0, 0},   //# 297 gamma_pt12
	{0x98, 0xD9, 0, 0},   //# 298 gamma_pt13
	{0x99, 0xE1, 0, 0},   //# 299 gamma_pt14
	{0x9A, 0xE9, 0, 0},   //# 29A gamma_pt15
	{0x9B, 0xF1, 0, 0},   //# 29B gamma_pt16
//#
	{0xFD, 0x03, 0, 0},
	{0x8D, 0xF9, 0, 0},   //# 38D gamma_pt17
	{0x8E, 0xFF, 0, 0},   //# 38E gamma_pt18
//#
	{0xFD, 0x02, 0, 0},
	{0x78, 0x00, 0, 0},   //# 278 gamma_pt2_0
	{0x79, 0x0B, 0, 0},   //# 279 gamma_pt2_1
	{0x7A, 0x16, 0, 0},   //# 27A gamma_pt2_2
	{0x7B, 0x2D, 0, 0},   //# 27B gamma_pt2_3
	{0x7C, 0x4F, 0, 0},   //# 27C gamma_pt2_4
	{0x7D, 0x6A, 0, 0},   //# 27D gamma_pt2_5
	{0x7E ,0x82, 0, 0},  //# 27E gamma_p2_6
	{0x7F, 0x95, 0, 0},   //# 27F gamma_pt2_7
	{0x80, 0xA5, 0, 0},   //# 280 gamma_pt2_8
	{0x81, 0xB3, 0, 0},   //# 281 gamma_pt2_9
	{0x82, 0xC0, 0, 0},   //# 282 gamma_pt2_10
	{0x83, 0xCB, 0, 0},   //# 283 gamma_pt2_11
	{0x84, 0xD5, 0, 0},   //# 284 gamma_pt2_12
	{0x85, 0xDF, 0, 0},   //# 285 gamma_pt2_13
	{0x86, 0xE8, 0, 0},   //# 286 gamma_pt2_14
	{0x87, 0xEF, 0, 0},   //# 287 gamma_pt2_15
	{0x88, 0xF6, 0, 0},   //# 288 gamma_pt2_16
	{0x89, 0xFB, 0, 0},   //# 289 gamma_pt2_17
	{0x8A, 0xFF, 0, 0},   //# 28A gamma_pt2_18
//#
	{0xFD, 0x03, 0, 0},
	{0x96, 0x46, 0, 0},   //# 396 ae time thr1
	{0x97, 0x28, 0, 0},   //# 397 ae time thr2
	{0x9F, 0x0A, 0, 0},   //# 39F gma_ratiok_fac
//#
	{0xFD, 0x02, 0, 0},
	{0xF4, 0x0B, 0, 0},   //# 2F4 lum_fcase_en,lum_down_en,outdoor_mode_en,mean_mode_reg
	{0xF0, 0x9F, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 exp_min_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x94, 0xF8, 0, 0},   //# 394 rpc_max_indr
	{0x95, 0x1A, 0, 0},   //# 395 rpc_min_indr
	{0x98, 0x9F, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_outdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x9C, 0x32, 0, 0},   //# 39C rpc_max_outdr
	{0x9D, 0x1A, 0, 0},   //# 39D rpc_min_outdr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x74, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x84, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x65, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x78, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x80, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x78, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x74, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x6A, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x55, 0x11, 0, 0},   //# 355 weight_w2,weight_w1
	{0x56, 0x11, 0, 0},   //# 356 weight_w4,weight_w3
//	{0x57, 0x03, 0, 0},   //# 357 weight_w5
	{0x57, 0x01, 0, 0},   //# 357 weight_w5(1001)
//#
	{0xFD, 0x02, 0, 0},
	{0xE0, 0x32, 0, 0},   //# 2E0 rpc_1base_max
	{0xE1, 0x26, 0, 0},   //# 2E1 rpc_2base_max
	{0xE2, 0x22, 0, 0},   //# 2E2 rpc_3base_max
	{0xE3, 0x1E, 0, 0},   //# 2E3 rpc_4base_max
	{0xE4, 0x1E, 0, 0},   //# 2E4 rpc_5base_max
	{0xE5, 0x1D, 0, 0},   //# 2E5 rpc_6base_max
	{0xE6, 0x1D, 0, 0},   //# 2E6 rpc_7base_max
	{0xE8, 0x1B, 0, 0},   //# 2E8 rpc_8base_max
	{0xE9, 0x1B, 0, 0},   //# 2E9 rpc_9base_max
	{0xEA, 0x1B, 0, 0},   //# 2EA rpc_10base_max
	{0xEB, 0x1A, 0, 0},   //# 2EB rpc_11base_max
	{0xF5, 0x1A, 0, 0},   //# 2F5 rpc_12base_max
	{0xF6, 0x1A, 0, 0},   //# 2F6 rpc_13base_max
	{0xF3, 0x03, 0, 0},   //# 2F3 uv_dif_en_outdoor,uv_dif_en_nr,uv_dif_en_dummy,uv_dif_en_low
	{0xB0, 0x00, 0, 0},   //# 2B0 uv_dif_gain_outdoor,uv_dif_gain_nr
	{0xB1, 0x12, 0, 0},   //# 2B1 uv_dif_gain_dummy,uv_dif_gain_low
//#
	{0xFD, 0x03, 0, 0},
	{0xDF, 0x0F, 0, 0},   //# 3DF sharpness
	{0xE7, 0x18, 0, 0},   //# 3E7 raw_sharp_range_base
	{0xE8, 0x20, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x20, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x20, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
	{0x70, 0x76, 0, 0},   //# 370 aec_gw_en,gw_uv_dif_en,gw_detect_en,gw_step
	{0x7B, 0x40, 0, 0},   //# 37B gw_mean_th
	{0x71, 0x2F, 0, 0},   //# 371 k_up
	{0x72, 0x0D, 0, 0},   //# 372 k_low
	{0x73, 0x0A, 0, 0},   //# 373 b_up
	{0x74, 0x2A, 0, 0},   //# 374 b_low
	{0x75, 0x04, 0, 0},   //# 375 uv_low_th
	{0x76, 0x20, 0, 0},   //# 376 y_low_th
	{0x77, 0x32, 0, 0},   //# 377 u_top
	{0x78, 0x00, 0, 0},   //# 378 u_bot
	{0x79, 0x28, 0, 0},   //# 379 v_top
	{0x7A, 0x00, 0, 0},   //# 37A v_bot
	{0x7C, 0x70, 0, 0},   //# 37C gw_offset
	{0x7D, 0x40, 0, 0},   //# 37D gw_y_bot
	{0x7E, 0xEF, 0, 0},   //# 37E gw_y_top
	{0x7F, 0x05, 0, 0},   //# 37F gw_uv_radius
	{0x80, 0x2F, 0, 0},   //# 380 uv_fix_dat
	{0x81, 0x20, 0, 0},   //# 381 y_offset_th
	{0x8F, 0x12, 0, 0},   //# 38F wt_th
	{0xCE, 0x78, 0, 0},   //# 3CE exp_heq_dummy[7:0]
	{0xCF, 0x05, 0, 0},   //# 3CF exp_heq_dummy[12:8]
	{0xCD, 0x60, 0, 0},   //# 3CD rpc_heq_dummy
	{0xCA, 0x30, 0, 0},   //# 3CA mean_dummy_low
	{0xCB, 0x50, 0, 0},   //# 3CB mean_low_dummy
	{0xD0, 0x78, 0, 0},   //# 3D0 exp_heq_low[7:0]
	{0xD1, 0x05, 0, 0},   //# 3D1 exp_heq_low[12:8]
	{0xCC, 0xC0, 0, 0},   //# 3CC rpc_heq_low
	{0xD5, 0x80, 0, 0},   //# 3D5 mean_nr_dummy
	{0xD6, 0x90, 0, 0},   //# 3D6 mean_dummy_nr
	{0xD7, 0x8B, 0, 0},   //# 3D7 exp_nr_outd_8lsb
	{0xD8, 0x00, 0, 0},   //# 3D8 exp_nr_outd_5hsb
	{0xD9, 0x8D, 0, 0},   //# 3D9 exp_outd_nr_8lsb
	{0xDA, 0x00, 0, 0},   //# 3DA exp_outd_nr_5hsb
//#
	{0xFD, 0x02, 0, 0},
	{0xB2, 0x10, 0, 0},   //# 2B2 lum_limit
	{0xB3, 0x18, 0, 0},   //# 2B3 lum_set
	{0xB4, 0x30, 0, 0},   //# 2B4 black_vt
	{0xB5, 0x50, 0, 0},   //# 2B5 white_vt
	{0xCB, 0x00, 0, 0},   //# 2CB rg_clip_ga_outdoor
	{0xCC, 0x02, 0, 0},   //# 2CC rg_clip_ga_nr
	{0xCD, 0x05, 0, 0},   //# 2CD rg_clip_ga_dummy
	{0xCE, 0x08, 0, 0},   //# 2CE rg_clip_ga_low
	{0xCF, 0x00, 0, 0},   //# 2CF bg_clip_ga_outdoor
	{0xD0, 0x02, 0, 0},   //# 2D0 bg_clip_ga_nr
//#
	{0xFD, 0x03, 0, 0},
	{0x10, 0x05, 0, 0},   //# 310 bg_clip_ga_dummy
	{0x14, 0x08, 0, 0},   //# 314 bg_clip_ga_low
//#
	{0xFD, 0x02, 0, 0},
	{0x5B, 0x00, 0, 0},   //# 25B cnr_thr_outdoor
	{0x61, 0x20, 0, 0},   //# 261 cnr_thr_nr
	{0x77, 0x40, 0, 0},   //# 277 cnr_thr_dummy
	{0xCA, 0x50, 0, 0},   //# 2CA cnr_thr_low
//	{0xAB, 0x10, 0, 0},   //# 2AB ynr_thr_outdoor
	{0xAB, 0x00, 0, 0},   //# 2AB ynr_thr_outdoor(1001)
	{0xAC, 0x02, 0, 0},   //# 2AC 
	{0xAE, 0x08, 0, 0},   //# 2AE 
	{0xAF, 0x10, 0, 0},   //# 2AF 
	{0x60, 0x01, 0, 0},   //# 260 bpc_vt_dummy
	{0x70, 0x0A, 0, 0},   //# 270 Bpc_v
	{0x76, 0x00, 0, 0},   //# 276 blacklevelin
	{0xC5, 0x60, 0, 0},   //# 2C5 raw_gflt_fac_indoor
	{0xDC, 0xF8, 0, 0},   //# 2DC buf_heq_offset
	{0xDD, 0x88, 0, 0},   //# 2DD ku
	{0xDE, 0x80, 0, 0},   //# 2DE kl
//#
	{0xFD, 0x03, 0, 0},
	{0x06, 0x00, 0, 0},   //# 306 ratio_row[9:8]
	{0x07, 0x20, 0, 0},   //# 307 ratio_row[7:0]
	{0x08, 0x00, 0, 0},   //# 308 ratio_col[9:8]
	{0x09, 0x20, 0, 0},   //# 309 ratio_col[7:0]
	{0x0A, 0x03, 0, 0},   //# 30A scalerownum[10:8]
	{0x0B, 0x00, 0, 0},   //# 30B scalerownum[7:0]
	{0x0C, 0x04, 0, 0},   //# 30C scalecolnum[10:8]
	{0x0D, 0x00, 0, 0},   //# 30D scalecolnum[7:0]
	{0x0E, 0x00, 0, 0},   //# 30E resize_en
	{0x1C, 0xB0, 0, 0},   //# 31C f_limit_b
	{0x1D, 0x85, 0, 0},   //# 31D f_limit_r
	{0x41, 0x00, 0, 0},   //# 341 grgb_top_high_bit
	{0x42, 0x00, 0, 0},   //# 342 grgb_bot_high_bit
	{0x44, 0x0F, 0, 0},   //# 344 wb_num_th_light_s
	{0x4C, 0x48, 0, 0},   //# 34C raw_adt_fac_outdoor
	{0x4D, 0x48, 0, 0},   //# 34D raw_adt_fac_normal
	{0x4E, 0x48, 0, 0},   //# 34E raw_adt_fac_dummy
	{0x4F, 0x48, 0, 0},   //# 34F raw_adt_fac_low
	{0xC6, 0x40, 0, 0},   //# 3C6 pre_grgain
	{0xC7, 0x40, 0, 0},   //# 3C7 pre_rgain
	{0xC8, 0x40, 0, 0},   //# 3C8 pre_gbgain
	{0xC9, 0x40, 0, 0},   //# 3C9 pre_bgain
	{0xE2, 0x40, 0, 0},   //# 3E2 raw_sharp_y_base
	{0xE3, 0x10, 0, 0},   //# 3E3 raw_sharp_y_min
	{0xE4, 0xE0, 0, 0},   //# 3E4 raw_sharp_y_max
	{0xE5, 0x30, 0, 0},   //# 3E5 raw_sharp_rangek_neg
	{0xE6, 0x20, 0, 0},   //# 3E6 raw_sharp_rangek_pos
//#
	{0xFD, 0x02, 0, 0},
	{0x32, 0x1D, 0, 0},   //# 232 auto_mode
	{0x33, 0xEF, 0, 0},   //# 233 lsc_bpc_en
	{0x34, 0x3E, 0, 0},   //# 234 buf_isp_mode
	{0xFB, 0x03, 0, 0},   //# 2FB blackgain_en,bl_bpc_en,abl
	{0x36, 0x00, 0, 0},   //# 236 buf_outmode2
};

//----- HD -------
static struct reg_value rnss2e1_setting_15fps_HD_1280_720[] = {
	{0xFD, 0x02, 0, 0},
	{0x36, 0x00, 0, 0},   //# 236 buf_outmode2
//#
	{0xFD, 0x00, 0, 0},
	{0x10, 0x1F, 0, 0},   //# 010 clk_mode
	{0x11, 0x40, 0, 0},   //# 011 pclk_inv,pclk_gate_en,pclk_ctrl,isp_clk_ctrl
//	{0x20, 0x02, 0, 0},   //# 020 ds_data,out_end_high8,out_end_low2,out_ens
	{0x20, 0x0A, 0, 0},   //# 020 ds_data,out_end_high8,out_end_low2,out_ens (Sanyo CE)
	{0x21, 0x03, 0, 0},   //# 021 pe_hvp,pe_data,ds_s,buf_dis_s,buf_dis_d
//#
	{0xFD, 0x01, 0, 0},
//	{0x03, 0x00, 0, 0},   //# 103 buf_exp_5msb
//	{0x04, 0x0C, 0, 0},   //# 104 buf_exp_8lsb
	{0x03, 0x01, 0, 0},   //# 103 buf_exp_5msb
	{0x04, 0x6E, 0, 0},   //# 104 buf_exp_8lsb
	{0x09, 0x00, 0, 0},   //# 109 hblank_4msb
	{0x0A, 0xDB, 0, 0},   //# 10A hblank_8lsb
//#
	{0xFD, 0x00, 0, 0},
	{0x0E, 0x40, 0, 0},   //# 00E pd
//#
	{0xFD, 0x01, 0, 0},
	{0x0E, 0x00, 0, 0},   //# 10E p0
	{0x0F, 0x18, 0, 0},   //# 10F p1
	{0x10, 0x10, 0, 0},   //# 110 p2
	{0x11, 0x03, 0, 0},   //# 111 p3
	{0x12, 0x18, 0, 0},   //# 112 p4
	{0x13, 0x10, 0, 0},   //# 113 p5
	{0x14, 0x15, 0, 0},   //# 114 p6
	{0x15, 0x01, 0, 0},   //# 115 p7
	{0x16, 0x02, 0, 0},   //# 116 p8
	{0x17, 0x10, 0, 0},   //# 117 p9
	{0x18, 0x00, 0, 0},   //# 118 p10_2msb
	{0x19, 0x1A, 0, 0},   //# 119 p10_8lsb
	{0x1A, 0x00, 0, 0},   //# 11A p11_2msb
	{0x1B, 0x1C, 0, 0},   //# 11B p11_8lsb
	{0x50, 0x00, 0, 0},   //# 150 p12_2msb
	{0x51, 0x1D, 0, 0},   //# 151 p12_8lsb
	{0x52, 0x15, 0, 0},   //# 152 P13
	{0x2A, 0x02, 0, 0},   //# 12A p16
	{0x53, 0x00, 0, 0},   //# 153 p17_2msb
	{0x54, 0x11, 0, 0},   //# 154 p17_8lsb
	{0x55, 0x12, 0, 0},   //# 155 p18
	{0x56, 0x02, 0, 0},   //# 156 p19
	{0x57, 0x02, 0, 0},   //# 157 p20
	{0x58, 0x00, 0, 0},   //# 158 p21
//#
	{0xFD, 0x00, 0, 0},
	{0x12, 0x04, 0, 0},   //# 012 pll_bias_ctl,pll_delay
	{0x13, 0x04, 0, 0},   //# 013 mipi_pattern_en,pll_test_en,mipi_en
	{0x14, 0x00, 0, 0},   //# 014 pclk_gate,timer_clk_gate,dclk_gate
	{0x15, 0x00, 0, 0},   //# 015 pclk_pha_adj
//#
	{0xFD, 0x01, 0, 0},
	{0x1C, 0x5C, 0, 0},   //# 11C two_timing_en,FPN_33ms_X,pwd_asp_timing_sel,Channel-timing
	{0x21, 0x44, 0, 0},   //# 121 adc_vcm_opin_ctl,adc_vcm_opin_c,col_clk_delay
	{0x22, 0x04, 0, 0},   //# 122 pga_bias_ctl,col_ctrl
	{0x25, 0x00, 0, 0},   //# 125 adc_range_ctl,adc_vcm_ctl,asp_delay
	{0x26, 0x26, 0, 0},   //# 126 adc_dig_offset,sw_delay
	{0x27, 0x6D, 0, 0},   //# 127 delay,black_en,adc_dref_cal,adc_g2x_en,adc_offset_en
	{0x2B, 0x66, 0, 0},   //# 12B adc_offset_ctl_buf_up,adc_offset_ctl_buf_dn
	{0x2C, 0x3F, 0, 0},   //# 12C strobe_en,bl_da
	{0x2D, 0x40, 0, 0},   //# 12D adc_bias_stage,adc_bias_vref
	{0x2E, 0x0D, 0, 0},   //# 12E dout_sel,strobe_sel
//	{0x40, 0xF0, 0, 0},   //# 140 vfpn_bpc_en,vfpn_minus_en
	{0x40, 0xF3, 0, 0},   //# 140 vfpn_bpc_en,vfpn_minus_en
	{0x41, 0x60, 0, 0},   //# 141 vfpn_bpc_th_x1
	{0x42, 0x50, 0, 0},   //# 142 vfpn_bpc_th_x2
	{0x43, 0x28, 0, 0},   //# 143 vfpn_bpc_in_x1
	{0x44, 0x28, 0, 0},   //# 144 vfpn_bpc_in_x2
//	{0x45, 0x0C, 0, 0},   //# 145 vfpn_delta
//	{0x45, 0x06, 0, 0},   //# 145 vfpn_delta(0830)
	{0x45, 0x00, 0, 0},   //# 145 vfpn_delta(0921)
	{0x31, 0x11, 0, 0},   //# 131 buf_comm_ctrl
//#
	{0xFD, 0x02, 0, 0},
	{0x35, 0x40, 0, 0},   //# 235 buf_outmode1
	{0x31, 0x10, 0, 0},   //# 231 digital_gain
	{0x47, 0x00, 0, 0},   //# 247 v_start_3msb
	{0x48, 0x00, 0, 0},   //# 248 v_start_8lsb
	{0x49, 0x04, 0, 0},   //# 249 v_size_3msb
	{0x4A, 0xB0, 0, 0},   //# 24A v_size_8lsb
	{0x4B, 0x00, 0, 0},   //# 24B h_start_3msb
	{0x4C, 0x00, 0, 0},   //# 24C h_start_8lsb
	{0x4D, 0x06, 0, 0},   //# 24D h_size_3msb
	{0x4E, 0x40, 0, 0},   //# 24E h_size_8lsb
//	{0x65, 0x08, 0, 0},   //# 265 blue_suboffset
//	{0x66, 0x06, 0, 0},   //# 266 red_suboffset
//	{0x67, 0x07, 0, 0},   //# 267 gr_suboffset
//	{0x68, 0x07, 0, 0},   //# 268 gb_suboffset
//	{0x65, 0x09, 0, 0},   //# 265 blue_suboffset(0830)
//	{0x66, 0x07, 0, 0},   //# 266 red_suboffset(0830)
//	{0x67, 0x08, 0, 0},   //# 267 gr_suboffset(0830)
//	{0x68, 0x08, 0, 0},   //# 268 gb_suboffset(0830)
	{0x65, 0x0F, 0, 0},   //# 265 blue_suboffset(0921)
	{0x66, 0x0D, 0, 0},   //# 266 red_suboffset(0921)
	{0x67, 0x0E, 0, 0},   //# 268 gb_suboffset(0921)
	{0x68, 0x0E, 0, 0},   //# 268 gb_suboffset(0921)
	{0x5F, 0x02, 0, 0},   //# 25F demo_gain_order,bayer_order
	{0x32, 0x00, 0, 0},   //# 232 auto_mode
	{0x33, 0xEF, 0, 0},   //# 233 lsc_bpc_en
	{0xA4, 0xFF, 0, 0},   //# 2A4 lsc_gain_max
//#
	{0xFD, 0x03, 0, 0},
	{0x66, 0x19, 0, 0},   //# 366 Lsc_rsy_u
	{0x6A, 0x1B, 0, 0},   //# 36A Lsc_gsy_u
	{0x6E, 0x14, 0, 0},   //# 36E Lsc_bsy_u
	{0x67, 0x19, 0, 0},   //# 367 Lsc_rsy_d
	{0x6B, 0x12, 0, 0},   //# 36B Lsc_gsy_d
	{0x6F, 0x14, 0, 0},   //# 36F Lsc_bsy_d
	{0x64, 0x1D, 0, 0},   //# 364 Lsc_rsx_l
	{0x68, 0x18, 0, 0},   //# 368 Lsc_gsx_l
	{0x6C, 0x14, 0, 0},   //# 36C Lsc_bsx_l
	{0x65, 0x15, 0, 0},   //# 365 Lsc_rsx_r
	{0x69, 0x12, 0, 0},   //# 369 Lsc_gsx_r
	{0x6D, 0x0E, 0, 0},   //# 36D Lsc_bsx_r
	{0xB8, 0x08, 0, 0},   //# 3B8 Lsc_rxy_lu
	{0xBC, 0x08, 0, 0},   //# 3BC Lsc_gxy_lu
	{0xC0, 0x08, 0, 0},   //# 3C0 Lsc_bxy_lu
	{0xB9, 0x08, 0, 0},   //# 3B9 Lsc_rxy_ru
	{0xBD, 0x08, 0, 0},   //# 3BD Lsc_gxy_ru
	{0xC1, 0x08, 0, 0},   //# 3C1 Lsc_bxy_ru
	{0xBA, 0x08, 0, 0},   //# 3BA Lsc_rxy_ld
	{0xBE, 0x08, 0, 0},   //# 3BE Lsc_gxy_ld
	{0xC2, 0x08, 0, 0},   //# 3C2 Lsc_bxy_ld
	{0xBB, 0x08, 0, 0},   //# 3BB Lsc_rxy_rd
	{0xBF, 0x08, 0, 0},   //# 3BF Lsc_gxy_rd
	{0xC3, 0x08, 0, 0},   //# 3C3 Lsc_bxy_rd
//#
	{0xFD, 0x02, 0, 0},
	{0x51, 0x00, 0, 0},   //# 251 bpc_vt_outdoor
	{0x52, 0x00, 0, 0},   //# 252 bpc_vt_normal
	{0x53, 0x00, 0, 0},   //# 253 bpc_vt_low_light
	{0x54, 0x00, 0, 0},   //# 254 bpc_wt_eff
	{0x55, 0xFF, 0, 0},   //# 255 bpc_dt_eff
//	{0x45, 0x00, 0, 0},   //# 245 bpc_range_ratio_outdoor,pc_range_ratio_nr
//	{0x46, 0x09, 0, 0},   //# 246 bpc_range_ratio_dummy,bpc_range_ratio_low
	{0x45, 0x13, 0, 0},   //# 245 bpc_range_ratio_outdoor,pc_range_ratio_nr (1001)
	{0x46, 0x49, 0, 0},   //# 246 bpc_range_ratio_dummy,bpc_range_ratio_low (1001)
	{0x69, 0x00, 0, 0},   //# 269 bpc_range_thr_outdoor
	{0x6A, 0x00, 0, 0},   //# 26A bpc_range_thr_nr
	{0x6B, 0x00, 0, 0},   //# 26B bpc_range_thr_dummy
	{0x6C, 0x00, 0, 0},   //# 26C bpc_range_thr_low
//#
	{0xFD, 0x03, 0, 0},
	{0xDE, 0x0F, 0, 0},   //# 3DE raw_denoise_en_outdoor,raw_denoise_en_nr,raw_denoise_en_dummy,raw_denoise_en_low
//#
	{0xFD, 0x02, 0, 0},
	{0x57, 0x04, 0, 0},   //# 257 raw_dif_thr_outdoor
	{0x58, 0x04, 0, 0},   //# 258 raw_dif_thr_normal
	{0x56, 0x0A, 0, 0},   //# 256 raw_dif_thr_dummy
	{0x59, 0x08, 0, 0},   //# 259 raw_dif_thr_low_light
	{0x4F, 0xE0, 0, 0},   //# 24F raw_gf_fac_outdoor
	{0xC3, 0xE0, 0, 0},   //# 2C3 raw_gf_fac_indoor
	{0x3F, 0xC0, 0, 0},   //# 23F raw_gf_fac_dummy
	{0x42, 0x40, 0, 0},   //# 242 raw_gf_fac_low
	{0x5A, 0xE0, 0, 0},   //# 25A raw_rb_fac_outdoor
	{0xC4, 0xE0, 0, 0},   //# 2C4 raw_rb_fac_indoor
	{0x43, 0xC0, 0, 0},   //# 243 raw_rb_fac_dummy
	{0xAD, 0x40, 0, 0},   //# 2AD raw_rb_fac_low
	{0xC2, 0x15, 0, 0},   //# 2C2 gf_ratiok_fac
//#
	{0xFD, 0x03, 0, 0},
	{0x50, 0x00, 0, 0},   //# 350 raw_grgb_thr_outdoor
	{0x51, 0x00, 0, 0},   //# 351 raw_grgb_thr_normal
	{0x52, 0x08, 0, 0},   //# 352 raw_grgb_thr_dummy
	{0x53, 0x08, 0, 0},   //# 353 raw_grgb_thr_low
//#
	{0xFD, 0x02, 0, 0},
	{0xB6, 0xE0, 0, 0},   //# 2B6 raw_gflt_fac_outdoor
	{0xB7, 0xC0, 0, 0},   //# 2B7 raw_gflt_fac_nr
	{0xB8, 0xA0, 0, 0},   //# 2B8 raw_gflt_fac_dummy
	{0xB9, 0x20, 0, 0},   //# 2B9 raw_gflt_fac_low
//#
	{0xFD, 0x03, 0, 0},
	{0x11, 0x1F, 0, 0},   //# 311 rg_dif_th
	{0x12, 0x1F, 0, 0},   //# 312 bg_dif_th
	{0x16, 0x1C, 0, 0},   //# 316 rgb_limit
	{0x18, 0x00, 0, 0},   //# 318 br_offset_f
	{0x19, 0x00, 0, 0},   //# 319 br_offset
	{0x1B, 0x80, 0, 0},   //# 31B rg_base	{0x1A, 0x80, 0, 0},   //# 31A bg_base
	{0x43, 0x80, 0, 0},   //# 343 channel_sel,test_awb
	{0x1E, 0x17, 0, 0},   //# 31E wb_fine_gain_step,wb_rough_gain_step
	{0x1F, 0x19, 0, 0},   //# 31F wb_dif_fine_th,wb_dif_rough_th
//	{0x28, 0xA6, 0, 0},   //# 328 buf_rgain
//	{0x29, 0x98, 0, 0},   //# 329 buf_bgain
	{0x28, 0x9D, 0, 0},   //# 328 buf_rgain(1001)
	{0x29, 0xAD, 0, 0},   //# 329 buf_bgain(1001)
//#
	{0xFD, 0x02, 0, 0},
	{0xE7, 0x03, 0, 0},   //# 2E7 reg_renew
	{0xE7, 0x00, 0, 0},   //# 2E7 reg_renew
//#
	{0xFD, 0x03, 0, 0},
	{0x2A, 0xF0, 0, 0},   //# 32A y_top_th
	{0x2B, 0x10, 0, 0},   //# 32B y_bot_th
	{0x2E, 0x04, 0, 0},   //# 32E rg_limit_log
	{0x2F, 0x16, 0, 0},   //# 32F bg_limit_log
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x80, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x80, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0x83, 0x70, 0, 0},   //# 383 skin_num_th
	{0x13, 0x43, 0, 0},   //# 313 awb_grey_en,awb_skin_en
	{0x24, 0x06, 0, 0},   //# 324 short_exp_th
	{0x25, 0x80, 0, 0},   //# 325 sp_rg_base
	{0x26, 0x80, 0, 0},   //# 326 sp_bg_base
	{0x35, 0xB2, 0, 0},   //# 335 d65_rg_bot
	{0x36, 0xCA, 0, 0},   //# 336 d65_rg_top
//	{0x37, 0x7C, 0, 0},   //# 337 d65_bg_bot
	{0x37, 0x73, 0, 0},   //# 337 d65_bg_bot(1001)
	{0x38, 0x94, 0, 0},   //# 338 d65_bg_top
//	{0x31, 0x7B, 0, 0},   //# 331 f_rg_bot
//	{0x32, 0x93, 0, 0},   //# 332 f_rg_top
//	{0x33, 0xAE, 0, 0},   //# 333 f_bg_bot
//	{0x34, 0xC6, 0, 0},   //# 334 f_bg_top
	{0x31, 0x60, 0, 0},   //# 331 f_rg_bot(1010)
	{0x32, 0x98, 0, 0},   //# 332 f_rg_top(1010)
	{0x33, 0xA8, 0, 0},   //# 333 f_bg_bot(1010)
	{0x34, 0xD8, 0, 0},   //# 334 f_bg_top(1010)
	{0x3D, 0x9C, 0, 0},   //# 33D cwf_rg_bot
	{0x3E, 0xB4, 0, 0},   //# 33E cwf_rg_top
	{0x3F, 0xA4, 0, 0},   //# 33F cwf_bg_bot
	{0x40, 0xBC, 0, 0},   //# 340 cwf_bg_top
	{0x39, 0x8A, 0, 0},   //# 339 tl84_rg_bot
	{0x3A, 0xA2, 0, 0},   //# 33A tl84_rg_top
	{0x3B, 0x9E, 0, 0},   //# 33B tl84_bg_bot
	{0x3C, 0xB6, 0, 0},   //# 33C tl84_bg_top
	{0xA0, 0xA6, 0, 0},   //# 3A0 c00_eff1_8lsb
	{0xA1, 0xCD, 0, 0},   //# 3A1 c01_eff1_8lsb
	{0xA2, 0x0C, 0, 0},   //# 3A2 c02_eff1_8lsb
	{0xA3, 0x06, 0, 0},   //# 3A3 c10_eff1_8lsb
	{0xA4, 0x8C, 0, 0},   //# 3A4 c11_eff1_8lsb
	{0xA5, 0xED, 0, 0},   //# 3A5 c12_eff1_8lsb
	{0xA6, 0x00, 0, 0},   //# 3A6 c20_eff1_8lsb
	{0xA7, 0xE7, 0, 0},   //# 3A7 c21_eff1_8lsb
	{0xA8, 0x99, 0, 0},   //# 3A8 c22_eff1_8lsb
	{0xA9, 0x0C, 0, 0},   //# 3A9 c02_eff1_2msb,c01_eff1_2msb,c00_eff1_2msb
	{0xAA, 0x30, 0, 0},   //# 3AA c12_eff1_2msb,c11_eff1_2msb,c10_eff1_2msb
	{0xAB, 0x0C, 0, 0},   //# 3AB c22_eff1_2msb,c21_eff1_2msb,c20_eff1_2msb
	{0xAC, 0x8C, 0, 0},   //# 3AC c00_eff2_8lsb
	{0xAD, 0xF4, 0, 0},   //# 3AD c01_eff2_8lsb
	{0xAE, 0x00, 0, 0},   //# 3AE c02_eff2_8lsb
	{0xAF, 0xFA, 0, 0},   //# 3AF c10_eff2_8lsb
	{0xB0, 0x8C, 0, 0},   //# 3B0 c11_eff2_8lsb
	{0xB1, 0xFA, 0, 0},   //# 3B1 c12_eff2_8lsb
	{0xB2, 0x0C, 0, 0},   //# 3B2 c20_eff2_8lsb
	{0xB3, 0xF4, 0, 0},   //# 3B3 c21_eff2_8lsb
	{0xB4, 0x80, 0, 0},   //# 3B4 c22_eff2_8lsb
	{0xB5, 0x0C, 0, 0},   //# 3B5 c02_eff2_2msb,c01_eff2_2msb,c00_eff2_2msb
	{0xB6, 0x33, 0, 0},   //# 3B6 c12_eff2_2msb,c11_eff2_2msb,c10_eff2_2msb
	{0xB7, 0x0C, 0, 0},   //# 3B7 c22_eff2_2msb,c21_eff2_2msb,c20_eff2_2msb
//#
	{0xFD, 0x02, 0, 0},
	{0xBF, 0x01, 0, 0},   //# 2BF autosa_en
	{0xBE, 0xAA, 0, 0},   //# 2BE u_v_th
	{0xC0, 0xFF, 0, 0},   //# 2C0 y_p_th
	{0xC1, 0xFF, 0, 0},   //# 2C1 y_mean_th
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
	{0x8B, 0x00, 0, 0},   //# 28B gamma_pt0
	{0x8C, 0x0F, 0, 0},   //# 28C gamma_pt1
	{0x8D, 0x1F, 0, 0},   //# 28D gamma_pt2
	{0x8E, 0x3C, 0, 0},   //# 28E gamma_pt3
	{0x8F, 0x67, 0, 0},   //# 28F gamma_pt4
	{0x90, 0x85, 0, 0},   //# 290 gamma_pt5
	{0x91, 0x99, 0, 0},   //# 291 gamma_pt6
	{0x92, 0xA8, 0, 0},   //# 292 gamma_pt7
	{0x93, 0xB5, 0, 0},   //# 293 gamma_pt8
	{0x94, 0xBE, 0, 0},   //# 294 gamma_pt9
	{0x95, 0xC8, 0, 0},   //# 295 gamma_pt10
	{0x96, 0xD1, 0, 0},   //# 296 gamma_pt11
	{0x97, 0xD9, 0, 0},   //# 297 gamma_pt12
	{0x98, 0xE0, 0, 0},   //# 298 gamma_pt13
	{0x99, 0xE8, 0, 0},   //# 299 gamma_pt14
	{0x9A, 0xED, 0, 0},   //# 29A gamma_pt15
	{0x9B, 0xF3, 0, 0},   //# 29B gamma_pt16
//#
	{0xFD, 0x03, 0, 0},
	{0x8D, 0xF9, 0, 0},   //# 38D gamma_pt17
	{0x8E, 0xFF, 0, 0},   //# 38E gamma_pt18
//#
	{0xFD, 0x02, 0, 0},
	{0x78, 0x00, 0, 0},   //# 278 gamma_pt2_0
	{0x79, 0x0F, 0, 0},   //# 279 gamma_pt2_1
	{0x7A, 0x1F, 0, 0},   //# 27A gamma_pt2_2
	{0x7B, 0x3C, 0, 0},   //# 27B gamma_pt2_3
	{0x7C, 0x67, 0, 0},   //# 27C gamma_pt2_4
	{0x7D, 0x85, 0, 0},   //# 27D gamma_pt2_5
	{0x7E, 0x99, 0, 0},   //# 27E gamma_p2_6
	{0x7F, 0xA8, 0, 0},   //# 27F gamma_pt2_7
	{0x80, 0xB5, 0, 0},   //# 280 gamma_pt2_8
	{0x81, 0xBE, 0, 0},   //# 281 gamma_pt2_9
	{0x82, 0xC8, 0, 0},   //# 282 gamma_pt2_10
	{0x83, 0xD1, 0, 0},   //# 283 gamma_pt2_11
	{0x84, 0xD9, 0, 0},   //# 284 gamma_pt2_12
	{0x85, 0xE0, 0, 0},   //# 285 gamma_pt2_13
	{0x86, 0xE8, 0, 0},   //# 286 gamma_pt2_14
	{0x87, 0xED, 0, 0},   //# 287 gamma_pt2_15
	{0x88, 0xF3, 0, 0},   //# 288 gamma_pt2_16
	{0x89, 0xF9, 0, 0},   //# 289 gamma_pt2_17
	{0x8A, 0xFF, 0, 0},   //# 28A gamma_pt2_18
//#
	{0xFD, 0x03, 0, 0},
	{0x96, 0x46, 0, 0},   //# 396 ae time thr1
	{0x97, 0x28, 0, 0},   //# 397 ae time thr2
	{0x9F, 0x0A, 0, 0},   //# 39F gma_ratiok_fac
//#
	{0xFD, 0x02, 0, 0},
	{0xF4, 0x0B, 0, 0},   //# 2F4 lum_fcase_en,lum_down_en,outdoor_mode_en,mean_mode_reg
	{0xF0, 0x7A, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 exp_min_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
	{0x95, 0x20, 0, 0},   //# 395 rpc_min_indr
	{0x98, 0x7A, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_outdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x9C, 0x32, 0, 0},   //# 39C rpc_max_outdr
	{0x9D, 0x20, 0, 0},   //# 39D rpc_min_outdr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x55, 0x11, 0, 0},   //# 355 weight_w2,weight_w1
	{0x56, 0x11, 0, 0},   //# 356 weight_w4,weight_w3
//	{0x57, 0x03, 0, 0},   //# 357 weight_w5
	{0x57, 0x01, 0, 0},   //# 357 weight_w5(1001)
//#
	{0xFD, 0x02, 0, 0},
	{0xE0, 0x3E, 0, 0},   //# 2E0 rpc_1base_max
	{0xE1, 0x26, 0, 0},   //# 2E1 rpc_2base_max
	{0xE2, 0x2A, 0, 0},   //# 2E2 rpc_3base_max
	{0xE3, 0x26, 0, 0},   //# 2E3 rpc_4base_max
	{0xE4, 0x26, 0, 0},   //# 2E4 rpc_5base_max
	{0xE5, 0x24, 0, 0},   //# 2E5 rpc_6base_max
	{0xE6, 0x24, 0, 0},   //# 2E6 rpc_7base_max
	{0xE8, 0x22, 0, 0},   //# 2E8 rpc_8base_max
	{0xE9, 0x22, 0, 0},   //# 2E9 rpc_9base_max
	{0xEA, 0x22, 0, 0},   //# 2EA rpc_10base_max
	{0xEB, 0x20, 0, 0},   //# 2EB rpc_11base_max
	{0xF5, 0x20, 0, 0},   //# 2F5 rpc_12base_max
	{0xF6, 0x20, 0, 0},   //# 2F6 rpc_13base_max
	{0xF3, 0x03, 0, 0},   //# 2F3 uv_dif_en_outdoor,uv_dif_en_nr,uv_dif_en_dummy,uv_dif_en_low
	{0xB0, 0x00, 0, 0},   //# 2B0 uv_dif_gain_outdoor,uv_dif_gain_nr
	{0xB1, 0x12, 0, 0},   //# 2B1 uv_dif_gain_dummy,uv_dif_gain_low
//#
	{0xFD, 0x03, 0, 0},
	{0xDF, 0x0F, 0, 0},   //# 3DF sharpness
	{0xE7, 0x08, 0, 0},   //# 3E7 raw_sharp_range_base
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
	{0x70, 0x73, 0, 0},   //# 370 aec_gw_en,gw_uv_dif_en,gw_detect_en,gw_step
	{0x7B, 0x40, 0, 0},   //# 37B gw_mean_th
	{0x71, 0x2F, 0, 0},   //# 371 k_up
	{0x72, 0x0D, 0, 0},   //# 372 k_low
	{0x73, 0x0A, 0, 0},   //# 373 b_up
	{0x74, 0x2A, 0, 0},   //# 374 b_low
	{0x75, 0x04, 0, 0},   //# 375 uv_low_th
	{0x76, 0x20, 0, 0},   //# 376 y_low_th
	{0x77, 0x32, 0, 0},   //# 377 u_top
	{0x78, 0x00, 0, 0},   //# 378 u_bot
	{0x79, 0x28, 0, 0},   //# 379 v_top
	{0x7A, 0x00, 0, 0},   //# 37A v_bot
	{0x7C, 0x70, 0, 0},   //# 37C gw_offset
	{0x7D, 0x90, 0, 0},   //# 37D gw_y_bot
	{0x7E, 0xEF, 0, 0},   //# 37E gw_y_top
	{0x7F, 0x04, 0, 0},   //# 37F gw_uv_radius
	{0x80, 0x40, 0, 0},   //# 380 uv_fix_dat
	{0x81, 0x20, 0, 0},   //# 381 y_offset_th
	{0x8F, 0x12, 0, 0},   //# 38F wt_th
	{0xCE, 0x88, 0, 0},   //# 3CE exp_heq_dummy[7:0]
	{0xCF, 0x09, 0, 0},   //# 3CF exp_heq_dummy[12:8]
	{0xCD, 0x30, 0, 0},   //# 3CD rpc_heq_dummy
	{0xCA, 0x68, 0, 0},   //# 3CA mean_dummy_low
	{0xCB, 0x88, 0, 0},   //# 3CB mean_low_dummy
	{0xD0, 0x88, 0, 0},   //# 3D0 exp_heq_low[7:0]
	{0xD1, 0x09, 0, 0},   //# 3D1 exp_heq_low[12:8]
	{0xCC, 0xC0, 0, 0},   //# 3CC rpc_heq_low
	{0xD5, 0x80, 0, 0},   //# 3D5 mean_nr_dummy
	{0xD6, 0x90, 0, 0},   //# 3D6 mean_dummy_nr
	{0xD7, 0x77, 0, 0},   //# 3D7 exp_nr_outd_8lsb
	{0xD8, 0x00, 0, 0},   //# 3D8 exp_nr_outd_5hsb
	{0xD9, 0x7A, 0, 0},   //# 3D9 exp_outd_nr_8lsb
	{0xDA, 0x00, 0, 0},   //# 3DA exp_outd_nr_5hsb
//#
	{0xFD, 0x02, 0, 0},
	{0xB2, 0x30, 0, 0},   //# 2B2 lum_limit
	{0xB3, 0x18, 0, 0},   //# 2B3 lum_set
	{0xB4, 0x60, 0, 0},   //# 2B4 black_vt
	{0xB5, 0x70, 0, 0},   //# 2B5 white_vt
	{0xCB, 0x00, 0, 0},   //# 2CB rg_clip_ga_outdoor
	{0xCC, 0x02, 0, 0},   //# 2CC rg_clip_ga_nr
	{0xCD, 0x05, 0, 0},   //# 2CD rg_clip_ga_dummy
	{0xCE, 0x08, 0, 0},   //# 2CE rg_clip_ga_low
	{0xCF, 0x00, 0, 0},   //# 2CF bg_clip_ga_outdoor
	{0xD0, 0x02, 0, 0},   //# 2D0 bg_clip_ga_nr
//#
	{0xFD, 0x03, 0, 0},
	{0x10, 0x05, 0, 0},   //# 310 bg_clip_ga_dummy
	{0x14, 0x08, 0, 0},   //# 314 bg_clip_ga_low
//#
	{0xFD, 0x02, 0, 0},
	{0x5B, 0x00, 0, 0},   //# 25B cnr_thr_outdoor
	{0x61, 0x08, 0, 0},   //# 261 cnr_thr_nr
	{0x77, 0x40, 0, 0},   //# 277 cnr_thr_dummy
	{0xCA, 0x60, 0, 0},   //# 2CA cnr_thr_low
//	{0xAB, 0x10, 0, 0},   //# 2AB ynr_thr_outdoor
	{0xAB, 0x00, 0, 0},   //# 2AB ynr_thr_outdoor(1001)
	{0xAC, 0x10, 0, 0},   //# 2AC ynr_thr_nr
	{0xAE, 0x60, 0, 0},   //# 2AE ynr_thr_dummy
	{0xAF, 0x40, 0, 0},   //# 2AF ynr_thr_low
	{0x60, 0x01, 0, 0},   //# 260 bpc_vt_dummy
	{0x70, 0x0A, 0, 0},   //# 270 Bpc_v
	{0x76, 0x00, 0, 0},   //# 276 blacklevelin
	{0xC5, 0x60, 0, 0},   //# 2C5 raw_gflt_fac_indoor
	{0xDC, 0x00, 0, 0},   //# 2DC buf_heq_offset
	{0xDD, 0x80, 0, 0},   //# 2DD ku
	{0xDE, 0x90, 0, 0},   //# 2DE kl
//#
	{0xFD, 0x03, 0, 0},
	{0x06, 0x00, 0, 0},   //# 306 ratio_row[9:8]
	{0x07, 0x25, 0, 0},   //# 307 ratio_row[7:0]
	{0x08, 0x00, 0, 0},   //# 308 ratio_col[9:8]
	{0x09, 0x28, 0, 0},   //# 309 ratio_col[7:0]
	{0x0A, 0x04, 0, 0},   //# 30A scalerownum[10:8]
	{0x0B, 0x00, 0, 0},   //# 30B scalerownum[7:0]
	{0x0C, 0x05, 0, 0},   //# 30C scalecolnum[10:8]
	{0x0D, 0x00, 0, 0},   //# 30D scalecolnum[7:0]
	{0x0E, 0x00, 0, 0},   //# 30E resize_en
	{0x1C, 0xBA, 0, 0},   //# 31C f_limit_b
	{0x1D, 0x87, 0, 0},   //# 31D f_limit_r
	{0x41, 0x00, 0, 0},   //# 341 grgb_top_high_bit
	{0x42, 0x00, 0, 0},   //# 342 grgb_bot_high_bit
	{0x44, 0x0F, 0, 0},   //# 344 wb_num_th_light_s
	{0x4C, 0x48, 0, 0},   //# 34C raw_adt_fac_outdoor
	{0x4D, 0x48, 0, 0},   //# 34D raw_adt_fac_normal
	{0x4E, 0x48, 0, 0},   //# 34E raw_adt_fac_dummy
	{0x4F, 0x48, 0, 0},   //# 34F raw_adt_fac_low
	{0xC6, 0x40, 0, 0},   //# 3C6 pre_grgain
	{0xC7, 0x40, 0, 0},   //# 3C7 pre_rgain
	{0xC8, 0x40, 0, 0},   //# 3C8 pre_gbgain
	{0xC9, 0x40, 0, 0},   //# 3C9 pre_bgain
	{0xE2, 0x40, 0, 0},   //# 3E2 raw_sharp_y_base
	{0xE3, 0x10, 0, 0},   //# 3E3 raw_sharp_y_min
	{0xE4, 0xE0, 0, 0},   //# 3E4 raw_sharp_y_max
	{0xE5, 0x30, 0, 0},   //# 3E5 raw_sharp_rangek_neg
	{0xE6, 0x20, 0, 0},   //# 3E6 raw_sharp_rangek_pos
//#
	{0xFD, 0x02, 0, 0},
	{0x32, 0x0D, 0, 0},   //# 232 auto_mode
	{0x33, 0xEF, 0, 0},   //# 233 lsc_bpc_en
	{0x34, 0xFF, 0, 0},   //# 234 buf_isp_mode
	{0xFB, 0x00, 0, 0},   //# 2FB blackgain_en,bl_bpc_en,abl
	{0x36, 0x00, 0, 0},   //# 236 buf_outmode2
};

static struct reg_value rnss2e1_setting_24fps_HD_1280_720[] = {
	{0xFD, 0x02, 0, 0},
	{0x36, 0x00, 0, 0},   //# 236 buf_outmode2
//#
	{0xFD, 0x00, 0, 0},
	{0x10, 0x1E, 0, 0},   //# 010 clk_mode
	{0x11, 0x40, 0, 0},   //# 011 pclk_inv,pclk_gate_en,pclk_ctrl,isp_clk_ctrl
//	{0x20, 0x02, 0, 0},   //# 020 ds_data,out_end_high8,out_end_low2,out_ens
	{0x20, 0x0A, 0, 0},   //# 020 ds_data,out_end_high8,out_end_low2,out_ens
	{0x21, 0x03, 0, 0},   //# 021 pe_hvp,pe_data,ds_s,buf_dis_s,buf_dis_d
//#
	{0xFD, 0x01, 0, 0},
//	{0x03, 0x00, 0, 0},   //# 103 buf_exp_5msb
//	{0x04, 0x16, 0, 0},   //# 104 buf_exp_8lsb
	{0x03, 0x02, 0, 0},   //# 103 buf_exp_5msb
	{0x04, 0x46, 0, 0},   //# 104 buf_exp_8lsb
	{0x09, 0x00, 0, 0},   //# 109 hblank_4msb
	{0x0A, 0x3C, 0, 0},   //# 10A hblank_8lsb
//#
	{0xFD, 0x00, 0, 0},
	{0x0E, 0x40, 0, 0},   //# 00E pd
//#
	{0xFD, 0x01, 0, 0},
	{0x0E, 0x00, 0, 0},   //# 10E p0
	{0x0F, 0x18, 0, 0},   //# 10F p1
	{0x10, 0x10, 0, 0},   //# 110 p2
	{0x11, 0x03, 0, 0},   //# 111 p3
	{0x12, 0x18, 0, 0},   //# 112 p4
	{0x13, 0x10, 0, 0},   //# 113 p5
	{0x14, 0x15, 0, 0},   //# 114 p6
	{0x15, 0x01, 0, 0},   //# 115 p7
	{0x16, 0x02, 0, 0},   //# 116 p8
	{0x17, 0x10, 0, 0},   //# 117 p9
	{0x18, 0x00, 0, 0},   //# 118 p10_2msb
	{0x19, 0x1A, 0, 0},   //# 119 p10_8lsb
	{0x1A, 0x00, 0, 0},   //# 11A p11_2msb
	{0x1B, 0x1C, 0, 0},   //# 11B p11_8lsb
	{0x50, 0x00, 0, 0},   //# 150 p12_2msb
	{0x51, 0x1D, 0, 0},   //# 151 p12_8lsb
	{0x52, 0x15, 0, 0},   //# 152 P13
	{0x2A, 0x02, 0, 0},   //# 12A p16
	{0x53, 0x00, 0, 0},   //# 153 p17_2msb
	{0x54, 0x11, 0, 0},   //# 154 p17_8lsb
	{0x55, 0x12, 0, 0},   //# 155 p18
	{0x56, 0x02, 0, 0},   //# 156 p19
	{0x57, 0x02, 0, 0},   //# 157 p20
	{0x58, 0x00, 0, 0},   //# 158 p21
//#
	{0xFD, 0x00, 0, 0},
	{0x12, 0x04, 0, 0},   //# 012 pll_bias_ctl,pll_delay
	{0x13, 0x04, 0, 0},   //# 013 mipi_pattern_en,pll_test_en,mipi_en
	{0x14, 0x00, 0, 0},   //# 014 pclk_gate,timer_clk_gate,dclk_gate
	{0x15, 0x00, 0, 0},   //# 015 pclk_pha_adj
//#
	{0xFD, 0x01, 0, 0},
	{0x1C, 0x5C, 0, 0},   //# 11C two_timing_en,FPN_33ms_X,pwd_asp_timing_sel,Channel-timing
	{0x21, 0x44, 0, 0},   //# 121 adc_vcm_opin_ctl,adc_vcm_opin_c,col_clk_delay
	{0x22, 0x04, 0, 0},   //# 122 pga_bias_ctl,col_ctrl
	{0x25, 0x00, 0, 0},   //# 125 adc_range_ctl,adc_vcm_ctl,asp_delay
	{0x26, 0x26, 0, 0},   //# 126 adc_dig_offset,sw_delay
	{0x27, 0x6D, 0, 0},   //# 127 delay,black_en,adc_dref_cal,adc_g2x_en,adc_offset_en
	{0x2B, 0x66, 0, 0},   //# 12B adc_offset_ctl_buf_up,adc_offset_ctl_buf_dn
	{0x2C, 0x3F, 0, 0},   //# 12C strobe_en,bl_da
	{0x2D, 0x40, 0, 0},   //# 12D adc_bias_stage,adc_bias_vref
	{0x2E, 0x0D, 0, 0},   //# 12E dout_sel,strobe_sel
//	{0x40, 0xF0, 0, 0},   //# 140 vfpn_bpc_en,vfpn_minus_en
	{0x40, 0xF3, 0, 0},   //# 140 vfpn_bpc_en,vfpn_minus_en
	{0x41, 0x60, 0, 0},   //# 141 vfpn_bpc_th_x1
	{0x42, 0x50, 0, 0},   //# 142 vfpn_bpc_th_x2
	{0x43, 0x28, 0, 0},   //# 143 vfpn_bpc_in_x1
	{0x44, 0x28, 0, 0},   //# 144 vfpn_bpc_in_x2
//	{0x45, 0x0C, 0, 0},   //# 145 vfpn_delta
//	{0x45, 0x06, 0, 0},   //# 145 vfpn_delta(0830)
	{0x45, 0x00, 0, 0},   //# 145 vfpn_delta(0921)
	{0x31, 0x11, 0, 0},   //# 131 buf_comm_ctrl
//#
	{0xFD, 0x02, 0, 0},
	{0x35, 0x40, 0, 0},   //# 235 buf_outmode1
	{0x31, 0x10, 0, 0},   //# 231 digital_gain
	{0x47, 0x00, 0, 0},   //# 247 v_start_3msb
	{0x48, 0x00, 0, 0},   //# 248 v_start_8lsb
	{0x49, 0x04, 0, 0},   //# 249 v_size_3msb
	{0x4A, 0xB0, 0, 0},   //# 24A v_size_8lsb
	{0x4B, 0x00, 0, 0},   //# 24B h_start_3msb
	{0x4C, 0x00, 0, 0},   //# 24C h_start_8lsb
	{0x4D, 0x06, 0, 0},   //# 24D h_size_3msb
	{0x4E, 0x40, 0, 0},   //# 24E h_size_8lsb
//	{0x65, 0x08, 0, 0},   //# 265 blue_suboffset
//	{0x66, 0x06, 0, 0},   //# 266 red_suboffset
//	{0x67, 0x07, 0, 0},   //# 267 gr_suboffset
//	{0x68, 0x07, 0, 0},   //# 268 gb_suboffset
//	{0x65, 0x09, 0, 0},   //# 265 blue_suboffset(0830)
//	{0x66, 0x07, 0, 0},   //# 266 red_suboffset(0830)
//	{0x67, 0x08, 0, 0},   //# 267 gr_suboffset(0830)
//	{0x68, 0x08, 0, 0},   //# 268 gb_suboffset(0830)
	{0x65, 0x0F, 0, 0},   //# 265 blue_suboffset(0921)
	{0x66, 0x0D, 0, 0},   //# 266 red_suboffset(0921)
	{0x67, 0x0E, 0, 0},   //# 267 gr_suboffset(0921)
	{0x68, 0x0E, 0, 0},   //# 268 gb_suboffset(0921)
	{0x5F, 0x02, 0, 0},   //# 25F demo_gain_order,bayer_order
	{0x32, 0x00, 0, 0},   //# 232 auto_mode
	{0x33, 0xEF, 0, 0},   //# 233 lsc_bpc_en
	{0xA4, 0xFF, 0, 0},   //# 2A4 lsc_gain_max
//#
	{0xFD, 0x03, 0, 0},
	{0x66, 0x19, 0, 0},   //# 366 Lsc_rsy_u
	{0x6A, 0x1B, 0, 0},   //# 36A Lsc_gsy_u
	{0x6E, 0x14, 0, 0},   //# 36E Lsc_bsy_u
	{0x67, 0x19, 0, 0},   //# 367 Lsc_rsy_d
	{0x6B, 0x12, 0, 0},   //# 36B Lsc_gsy_d
	{0x6F, 0x14, 0, 0},   //# 36F Lsc_bsy_d
	{0x64, 0x1D, 0, 0},   //# 364 Lsc_rsx_l
	{0x68, 0x18, 0, 0},   //# 368 Lsc_gsx_l
	{0x6C, 0x14, 0, 0},   //# 36C Lsc_bsx_l
	{0x65, 0x15, 0, 0},   //# 365 Lsc_rsx_r
	{0x69, 0x12, 0, 0},   //# 369 Lsc_gsx_r
	{0x6D, 0x0E, 0, 0},   //# 36D Lsc_bsx_r
	{0xB8, 0x08, 0, 0},   //# 3B8 Lsc_rxy_lu
	{0xBC, 0x08, 0, 0},   //# 3BC Lsc_gxy_lu
	{0xC0, 0x08, 0, 0},   //# 3C0 Lsc_bxy_lu
	{0xB9, 0x08, 0, 0},   //# 3B9 Lsc_rxy_ru
	{0xBD, 0x08, 0, 0},   //# 3BD Lsc_gxy_ru
	{0xC1, 0x08, 0, 0},   //# 3C1 Lsc_bxy_ru
	{0xBA, 0x08, 0, 0},   //# 3BA Lsc_rxy_ld
	{0xBE, 0x08, 0, 0},   //# 3BE Lsc_gxy_ld
	{0xC2, 0x08, 0, 0},   //# 3C2 Lsc_bxy_ld
	{0xBB, 0x08, 0, 0},   //# 3BB Lsc_rxy_rd
	{0xBF, 0x08, 0, 0},   //# 3BF Lsc_gxy_rd
	{0xC3, 0x08, 0, 0},   //# 3C3 Lsc_bxy_rd
//#
	{0xFD, 0x02, 0, 0},
	{0x51, 0x00, 0, 0},   //# 251 bpc_vt_outdoor
	{0x52, 0x00, 0, 0},   //# 252 bpc_vt_normal
	{0x53, 0x00, 0, 0},   //# 253 bpc_vt_low_light
	{0x54, 0x00, 0, 0},   //# 254 bpc_wt_eff
	{0x55, 0xFF, 0, 0},   //# 255 bpc_dt_eff
//	{0x45, 0x00, 0, 0},   //# 245 bpc_range_ratio_outdoor,pc_range_ratio_nr
//	{0x46, 0x09, 0, 0},   //# 246 bpc_range_ratio_dummy,bpc_range_ratio_low
	{0x45, 0x13, 0, 0},   //# 245 bpc_range_ratio_outdoor,pc_range_ratio_nr (1001)
	{0x46, 0x49, 0, 0},   //# 246 bpc_range_ratio_dummy,bpc_range_ratio_low (1001)
	{0x69, 0x00, 0, 0},   //# 269 bpc_range_thr_outdoor
	{0x6A, 0x00, 0, 0},   //# 26A bpc_range_thr_nr
	{0x6B, 0x00, 0, 0},   //# 26B bpc_range_thr_dummy
	{0x6C, 0x00, 0, 0},   //# 26C bpc_range_thr_low
//#
	{0xFD, 0x03, 0, 0},
	{0xDE, 0x0F, 0, 0},   //# 3DE raw_denoise_en_outdoor,raw_denoise_en_nr,raw_denoise_en_dummy,raw_denoise_en_low
//#
	{0xFD, 0x02, 0, 0},
	{0x57, 0x04, 0, 0},   //# 257 raw_dif_thr_outdoor
	{0x58, 0x04, 0, 0},   //# 258 raw_dif_thr_normal
	{0x56, 0x0A, 0, 0},   //# 256 raw_dif_thr_dummy
	{0x59, 0x08, 0, 0},   //# 259 raw_dif_thr_low_light
	{0x4F, 0xE0, 0, 0},   //# 24F raw_gf_fac_outdoor
	{0xC3, 0xE0, 0, 0},   //# 2C3 raw_gf_fac_indoor
	{0x3F, 0xC0, 0, 0},   //# 23F raw_gf_fac_dummy
	{0x42, 0x40, 0, 0},   //# 242 raw_gf_fac_low
	{0x5A, 0xE0, 0, 0},   //# 25A raw_rb_fac_outdoor
	{0xC4, 0xE0, 0, 0},   //# 2C4 raw_rb_fac_indoor
	{0x43, 0xC0, 0, 0},   //# 243 raw_rb_fac_dummy
	{0xAD, 0x40, 0, 0},   //# 2AD raw_rb_fac_low
	{0xC2, 0x15, 0, 0},   //# 2C2 gf_ratiok_fac

//#
	{0xFD, 0x03, 0, 0},
	{0x50, 0x00, 0, 0},   //# 350 raw_grgb_thr_outdoor
	{0x51, 0x00, 0, 0},   //# 351 raw_grgb_thr_normal
	{0x52, 0x08, 0, 0},   //# 352 raw_grgb_thr_dummy
	{0x53, 0x08, 0, 0},   //# 353 raw_grgb_thr_low
//#
	{0xFD, 0x02, 0, 0},
	{0xB6, 0xE0, 0, 0},   //# 2B6 raw_gflt_fac_outdoor
	{0xB7, 0xC0, 0, 0},   //# 2B7 raw_gflt_fac_nr
	{0xB8, 0xA0, 0, 0},   //# 2B8 raw_gflt_fac_dummy
	{0xB9, 0x20, 0, 0},   //# 2B9 raw_gflt_fac_low
//#
	{0xFD, 0x03, 0, 0},
	{0x11, 0x1F, 0, 0},   //# 311 rg_dif_th
	{0x12, 0x1F, 0, 0},   //# 312 bg_dif_th
	{0x16, 0x1C, 0, 0},   //# 316 rgb_limit
	{0x18, 0x00, 0, 0},   //# 318 br_offset_f
	{0x19, 0x00, 0, 0},   //# 319 br_offset
	{0x1B, 0x80, 0, 0},   //# 31B rg_base
	{0x1A, 0x80, 0, 0},   //# 31A bg_base
	{0x43, 0x80, 0, 0},   //# 343 channel_sel,test_awb
	{0x1E, 0x17, 0, 0},   //# 31E wb_fine_gain_step,wb_rough_gain_step
	{0x1F, 0x19, 0, 0},   //# 31F wb_dif_fine_th,wb_dif_rough_th
//	{0x28, 0xA7, 0, 0},   //# 328 buf_rgain
//	{0x29, 0x97, 0, 0},   //# 329 buf_bgain
	{0x28, 0x9D, 0, 0},   //# 328 buf_rgain
	{0x29, 0xB0, 0, 0},   //# 329 buf_bgain
//#
	{0xFD, 0x02, 0, 0},
	{0xE7, 0x03, 0, 0},   //# 2E7 reg_renew
	{0xE7, 0x00, 0, 0},   //# 2E7 reg_renew
//#
	{0xFD, 0x03, 0, 0},
	{0x2A, 0xF0, 0, 0},   //# 32A y_top_th
	{0x2B, 0x10, 0, 0},   //# 32B y_bot_th
	{0x2E, 0x04, 0, 0},   //# 32E rg_limit_log
	{0x2F, 0x16, 0, 0},   //# 32F bg_limit_log
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x80, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x80, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0x83, 0x70, 0, 0},   //# 383 skin_num_th
	{0x13, 0x43, 0, 0},   //# 313 awb_grey_en,awb_skin_en
	{0x24, 0x06, 0, 0},   //# 324 short_exp_th
	{0x25, 0x80, 0, 0},   //# 325 sp_rg_base
	{0x26, 0x80, 0, 0},   //# 326 sp_bg_base
	{0x35, 0xB2, 0, 0},   //# 335 d65_rg_bot
	{0x36, 0xCA, 0, 0},   //# 336 d65_rg_top
//	{0x37, 0x7C, 0, 0},   //# 337 d65_bg_bot
	{0x37, 0x73, 0, 0},   //# 337 d65_bg_bot(1001)
	{0x38, 0x94, 0, 0},   //# 338 d65_bg_top
//	{0x31, 0x7B, 0, 0},   //# 331 f_rg_bot
//	{0x32, 0x93, 0, 0},   //# 332 f_rg_top
//	{0x33, 0xAE, 0, 0},   //# 333 f_bg_bot
//	{0x34, 0xC6, 0, 0},   //# 334 f_bg_top
	{0x31, 0x60, 0, 0},   //# 331 f_rg_bot(1010)
	{0x32, 0x98, 0, 0},   //# 332 f_rg_top(1010)
	{0x33, 0xA8, 0, 0},   //# 333 f_bg_bot(1010)
	{0x34, 0xD8, 0, 0},   //# 334 f_bg_top(1010)
	{0x3D, 0x9C, 0, 0},   //# 33D cwf_rg_bot
	{0x3E, 0xB4, 0, 0},   //# 33E cwf_rg_top
	{0x3F, 0xA4, 0, 0},   //# 33F cwf_bg_bot
	{0x40, 0xBC, 0, 0},   //# 340 cwf_bg_top
	{0x39, 0x8A, 0, 0},   //# 339 tl84_rg_bot
	{0x3A, 0xA2, 0, 0},   //# 33A tl84_rg_top
	{0x3B, 0x9E, 0, 0},   //# 33B tl84_bg_bot
	{0x3C, 0xB6, 0, 0},   //# 33C tl84_bg_top
	{0xA0, 0xA6, 0, 0},   //# 3A0 c00_eff1_8lsb
	{0xA1, 0xCD, 0, 0},   //# 3A1 c01_eff1_8lsb
	{0xA2, 0x0C, 0, 0},   //# 3A2 c02_eff1_8lsb
	{0xA3, 0x06, 0, 0},   //# 3A3 c10_eff1_8lsb
	{0xA4, 0x8C, 0, 0},   //# 3A4 c11_eff1_8lsb
	{0xA5, 0xED, 0, 0},   //# 3A5 c12_eff1_8lsb
	{0xA6, 0x00, 0, 0},   //# 3A6 c20_eff1_8lsb
	{0xA7, 0xE7, 0, 0},   //# 3A7 c21_eff1_8lsb
	{0xA8, 0x99, 0, 0},   //# 3A8 c22_eff1_8lsb
	{0xA9, 0x0C, 0, 0},   //# 3A9 c02_eff1_2msb,c01_eff1_2msb,c00_eff1_2msb
	{0xAA, 0x30, 0, 0},   //# 3AA c12_eff1_2msb,c11_eff1_2msb,c10_eff1_2msb
	{0xAB, 0x0C, 0, 0},   //# 3AB c22_eff1_2msb,c21_eff1_2msb,c20_eff1_2msb
	{0xAC, 0x8C, 0, 0},   //# 3AC c00_eff2_8lsb
	{0xAD, 0xF4, 0, 0},   //# 3AD c01_eff2_8lsb
	{0xAE, 0x00, 0, 0},   //# 3AE c02_eff2_8lsb
	{0xAF, 0xFA, 0, 0},   //# 3AF c10_eff2_8lsb
	{0xB0, 0x8C, 0, 0},   //# 3B0 c11_eff2_8lsb
	{0xB1, 0xFA, 0, 0},   //# 3B1 c12_eff2_8lsb
	{0xB2, 0x0C, 0, 0},   //# 3B2 c20_eff2_8lsb
	{0xB3, 0xF4, 0, 0},   //# 3B3 c21_eff2_8lsb
	{0xB4, 0x80, 0, 0},   //# 3B4 c22_eff2_8lsb
	{0xB5, 0x0C, 0, 0},   //# 3B5 c02_eff2_2msb,c01_eff2_2msb,c00_eff2_2msb
	{0xB6, 0x33, 0, 0},   //# 3B6 c12_eff2_2msb,c11_eff2_2msb,c10_eff2_2msb
	{0xB7, 0x0C, 0, 0},   //# 3B7 c22_eff2_2msb,c21_eff2_2msb,c20_eff2_2msb
//#
	{0xFD, 0x02, 0, 0},
	{0xBF, 0x01, 0, 0},   //# 2BF autosa_en
	{0xBE, 0xAA, 0, 0},   //# 2BE u_v_th
	{0xC0, 0xFF, 0, 0},   //# 2C0 y_p_th
	{0xC1, 0xFF, 0, 0},   //# 2C1 y_mean_th
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
	{0x8B, 0x00, 0, 0},   //# 28B gamma_pt0
	{0x8C, 0x0F, 0, 0},   //# 28C gamma_pt1
	{0x8D, 0x1F, 0, 0},   //# 28D gamma_pt2
	{0x8E, 0x3C, 0, 0},   //# 28E gamma_pt3
	{0x8F, 0x67, 0, 0},   //# 28F gamma_pt4
	{0x90, 0x85, 0, 0},   //# 290 gamma_pt5
	{0x91, 0x99, 0, 0},   //# 291 gamma_pt6
	{0x92, 0xA8, 0, 0},   //# 292 gamma_pt7
	{0x93, 0xB5, 0, 0},   //# 293 gamma_pt8
	{0x94, 0xBE, 0, 0},   //# 294 gamma_pt9
	{0x95, 0xC8, 0, 0},   //# 295 gamma_pt10
	{0x96, 0xD1, 0, 0},   //# 296 gamma_pt11
	{0x97, 0xD9, 0, 0},   //# 297 gamma_pt12
	{0x98, 0xE0, 0, 0},   //# 298 gamma_pt13
	{0x99, 0xE8, 0, 0},   //# 299 gamma_pt14
	{0x9A, 0xED, 0, 0},   //# 29A gamma_pt15
	{0x9B, 0xF3, 0, 0},   //# 29B gamma_pt16
//#
	{0xFD, 0x03, 0, 0},
	{0x8D, 0xF9, 0, 0},   //# 38D gamma_pt17
	{0x8E, 0xFF, 0, 0},   //# 38E gamma_pt18
//#
	{0xFD, 0x02, 0, 0},
	{0x78, 0x00, 0, 0},   //# 278 gamma_pt2_0
	{0x79, 0x0F, 0, 0},   //# 279 gamma_pt2_1
	{0x7A, 0x1F, 0, 0},   //# 27A gamma_pt2_2
	{0x7B, 0x3C, 0, 0},   //# 27B gamma_pt2_3
	{0x7C, 0x67, 0, 0},   //# 27C gamma_pt2_4
	{0x7D, 0x85, 0, 0},   //# 27D gamma_pt2_5
	{0x7E, 0x99, 0, 0},   //# 27E gamma_p2_6
	{0x7F, 0xA8, 0, 0},   //# 27F gamma_pt2_7
	{0x80, 0xB5, 0, 0},   //# 280 gamma_pt2_8
	{0x81, 0xBE, 0, 0},   //# 281 gamma_pt2_9
	{0x82, 0xC8, 0, 0},   //# 282 gamma_pt2_10
	{0x83, 0xD1, 0, 0},   //# 283 gamma_pt2_11
	{0x84, 0xD9, 0, 0},   //# 284 gamma_pt2_12
	{0x85, 0xE0, 0, 0},   //# 285 gamma_pt2_13
	{0x86, 0xE8, 0, 0},   //# 286 gamma_pt2_14
	{0x87, 0xED, 0, 0},   //# 287 gamma_pt2_15
	{0x88, 0xF3, 0, 0},   //# 288 gamma_pt2_16
	{0x89, 0xF9, 0, 0},   //# 289 gamma_pt2_17
	{0x8A, 0xFF, 0, 0},   //# 28A gamma_pt2_18
//#
	{0xFD, 0x03, 0, 0},
	{0x96, 0x46, 0, 0},   //# 396 ae time thr1
	{0x97, 0x28, 0, 0},   //# 397 ae time thr2
	{0x9F, 0x0A, 0, 0},   //# 39F gma_ratiok_fac
//#
	{0xFD, 0x02, 0, 0},
	{0xF4, 0x0B, 0, 0},   //# 2F4 lum_fcase_en,lum_down_en,outdoor_mode_en,mean_mode_reg
	{0xF0, 0xC2, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 exp_min_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
	{0x95, 0x20, 0, 0},   //# 395 rpc_min_indr
	{0x98, 0xC2, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_outdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x9C, 0x32, 0, 0},   //# 39C rpc_max_outdr
	{0x9D, 0x20, 0, 0},   //# 39D rpc_min_outdr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x55, 0x11, 0, 0},   //# 355 weight_w2,weight_w1
	{0x56, 0x11, 0, 0},   //# 356 weight_w4,weight_w3
//	{0x57, 0x03, 0, 0},   //# 357 weight_w5
	{0x57, 0x01, 0, 0},   //# 357 weight_w5(1001)
//#
	{0xFD, 0x02, 0, 0},
	{0xE0, 0x3E, 0, 0},   //# 2E0 rpc_1base_max
	{0xE1, 0x26, 0, 0},   //# 2E1 rpc_2base_max
	{0xE2, 0x2A, 0, 0},   //# 2E2 rpc_3base_max
	{0xE3, 0x26, 0, 0},   //# 2E3 rpc_4base_max
	{0xE4, 0x26, 0, 0},   //# 2E4 rpc_5base_max
	{0xE5, 0x24, 0, 0},   //# 2E5 rpc_6base_max
	{0xE6, 0x24, 0, 0},   //# 2E6 rpc_7base_max
	{0xE8, 0x22, 0, 0},   //# 2E8 rpc_8base_max
	{0xE9, 0x22, 0, 0},   //# 2E9 rpc_9base_max
	{0xEA, 0x22, 0, 0},   //# 2EA rpc_10base_max
	{0xEB, 0x20, 0, 0},   //# 2EB rpc_11base_max
	{0xF5, 0x20, 0, 0},   //# 2F5 rpc_12base_max
	{0xF6, 0x20, 0, 0},   //# 2F6 rpc_13base_max
	{0xF3, 0x03, 0, 0},   //# 2F3 uv_dif_en_outdoor,uv_dif_en_nr,uv_dif_en_dummy,uv_dif_en_low
	{0xB0, 0x00, 0, 0},   //# 2B0 uv_dif_gain_outdoor,uv_dif_gain_nr
	{0xB1, 0x12, 0, 0},   //# 2B1 uv_dif_gain_dummy,uv_dif_gain_low
//#
	{0xFD, 0x03, 0, 0},
	{0xDF, 0x0F, 0, 0},   //# 3DF sharpness
	{0xE7, 0x08, 0, 0},   //# 3E7 raw_sharp_range_base
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
	{0x70, 0x73, 0, 0},   //# 370 aec_gw_en,gw_uv_dif_en,gw_detect_en,gw_step
	{0x7B, 0x40, 0, 0},   //# 37B gw_mean_th
	{0x71, 0x2F, 0, 0},   //# 371 k_up
	{0x72, 0x0D, 0, 0},   //# 372 k_low
	{0x73, 0x0A, 0, 0},   //# 373 b_up
	{0x74, 0x2A, 0, 0},   //# 374 b_low
	{0x75, 0x04, 0, 0},   //# 375 uv_low_th
	{0x76, 0x20, 0, 0},   //# 376 y_low_th
	{0x77, 0x32, 0, 0},   //# 377 u_top
	{0x78, 0x00, 0, 0},   //# 378 u_bot
	{0x79, 0x28, 0, 0},   //# 379 v_top
	{0x7A, 0x00, 0, 0},   //# 37A v_bot
	{0x7C, 0x70, 0, 0},   //# 37C gw_offset
	{0x7D, 0x90, 0, 0},   //# 37D gw_y_bot
	{0x7E, 0xEF, 0, 0},   //# 37E gw_y_top
	{0x7F, 0x04, 0, 0},   //# 37F gw_uv_radius
	{0x80, 0x40, 0, 0},   //# 380 uv_fix_dat
	{0x81, 0x20, 0, 0},   //# 381 y_offset_th
	{0x8F, 0x12, 0, 0},   //# 38F wt_th
	{0xCE, 0x28, 0, 0},   //# 3CE exp_heq_dummy[7:0]
	{0xCF, 0x0F, 0, 0},   //# 3CF exp_heq_dummy[12:8]
	{0xCD, 0x30, 0, 0},   //# 3CD rpc_heq_dummy
	{0xCA, 0x68, 0, 0},   //# 3CA mean_dummy_low
	{0xCB, 0x88, 0, 0},   //# 3CB mean_low_dummy
	{0xD0, 0x28, 0, 0},   //# 3D0 exp_heq_low[7:0]
	{0xD1, 0x0F, 0, 0},   //# 3D1 exp_heq_low[12:8]
	{0xCC, 0xC0, 0, 0},   //# 3CC rpc_heq_low
	{0xD5, 0x80, 0, 0},   //# 3D5 mean_nr_dummy
	{0xD6, 0x90, 0, 0},   //# 3D6 mean_dummy_nr
	{0xD7, 0xBF, 0, 0},   //# 3D7 exp_nr_outd_8lsb
	{0xD8, 0x00, 0, 0},   //# 3D8 exp_nr_outd_5hsb
	{0xD9, 0xC2, 0, 0},   //# 3D9 exp_outd_nr_8lsb
	{0xDA, 0x00, 0, 0},   //# 3DA exp_outd_nr_5hsb
//#
	{0xFD, 0x02, 0, 0},
	{0xB2, 0x30, 0, 0},   //# 2B2 lum_limit
	{0xB3, 0x18, 0, 0},   //# 2B3 lum_set
	{0xB4, 0x60, 0, 0},   //# 2B4 black_vt
	{0xB5, 0x70, 0, 0},   //# 2B5 white_vt
	{0xCB, 0x00, 0, 0},   //# 2CB rg_clip_ga_outdoor
	{0xCC, 0x02, 0, 0},   //# 2CC rg_clip_ga_nr
	{0xCD, 0x05, 0, 0},   //# 2CD rg_clip_ga_dummy
	{0xCE, 0x08, 0, 0},   //# 2CE rg_clip_ga_low
	{0xCF, 0x00, 0, 0},   //# 2CF bg_clip_ga_outdoor
	{0xD0, 0x02, 0, 0},   //# 2D0 bg_clip_ga_nr
//#
	{0xFD, 0x03, 0, 0},
	{0x10, 0x05, 0, 0},   //# 310 bg_clip_ga_dummy
	{0x14, 0x08, 0, 0},   //# 314 bg_clip_ga_low
//#
	{0xFD, 0x02, 0, 0},
	{0x5B, 0x00, 0, 0},   //# 25B cnr_thr_outdoor
	{0x61, 0x08, 0, 0},   //# 261 cnr_thr_nr
	{0x77, 0x40, 0, 0},   //# 277 cnr_thr_dummy
	{0xCA, 0x60, 0, 0},   //# 2CA cnr_thr_low
//	{0xAB, 0x10, 0, 0},   //# 2AB ynr_thr_outdoor
	{0xAB, 0x00, 0, 0},   //# 2AB ynr_thr_outdoor(1001)
	{0xAC, 0x10, 0, 0},   //# 2AC ynr_thr_nr
	{0xAE, 0x60, 0, 0},   //# 2AE ynr_thr_dummy
	{0xAF, 0x40, 0, 0},   //# 2AF ynr_thr_low
	{0x60, 0x01, 0, 0},   //# 260 bpc_vt_dummy
	{0x70, 0x0A, 0, 0},   //# 270 Bpc_v
	{0x76, 0x00, 0, 0},   //# 276 blacklevelin
	{0xC5, 0x60, 0, 0},   //# 2C5 raw_gflt_fac_indoor
	{0xDC, 0x00, 0, 0},   //# 2DC buf_heq_offset
	{0xDD, 0x80, 0, 0},   //# 2DD ku
	{0xDE, 0x90, 0, 0},   //# 2DE kl
//#
	{0xFD, 0x03, 0, 0},
	{0x06, 0x00, 0, 0},   //# 306 ratio_row[9:8]
	{0x07, 0x25, 0, 0},   //# 307 ratio_row[7:0]
	{0x08, 0x00, 0, 0},   //# 308 ratio_col[9:8]
	{0x09, 0x28, 0, 0},   //# 309 ratio_col[7:0]
	{0x0A, 0x04, 0, 0},   //# 30A scalerownum[10:8]
	{0x0B, 0x00, 0, 0},   //# 30B scalerownum[7:0]
	{0x0C, 0x05, 0, 0},   //# 30C scalecolnum[10:8]
	{0x0D, 0x00, 0, 0},   //# 30D scalecolnum[7:0]
	{0x0E, 0x00, 0, 0},   //# 30E resize_en
	{0x1C, 0xBA, 0, 0},   //# 31C f_limit_b
	{0x1D, 0x87, 0, 0},   //# 31D f_limit_r
	{0x41, 0x00, 0, 0},   //# 341 grgb_top_high_bit
	{0x42, 0x00, 0, 0},   //# 342 grgb_bot_high_bit
	{0x44, 0x0F, 0, 0},   //# 344 wb_num_th_light_s
	{0x4C, 0x48, 0, 0},   //# 34C raw_adt_fac_outdoor
	{0x4D, 0x48, 0, 0},   //# 34D raw_adt_fac_normal
	{0x4E, 0x48, 0, 0},   //# 34E raw_adt_fac_dummy
	{0x4F, 0x48, 0, 0},   //# 34F raw_adt_fac_low
	{0xC6, 0x40, 0, 0},   //# 3C6 pre_grgain
	{0xC7, 0x40, 0, 0},   //# 3C7 pre_rgain
	{0xC8, 0x40, 0, 0},   //# 3C8 pre_gbgain
	{0xC9, 0x40, 0, 0},   //# 3C9 pre_bgain
	{0xE2, 0x40, 0, 0},   //# 3E2 raw_sharp_y_base
	{0xE3, 0x10, 0, 0},   //# 3E3 raw_sharp_y_min
	{0xE4, 0xE0, 0, 0},   //# 3E4 raw_sharp_y_max
	{0xE5, 0x30, 0, 0},   //# 3E5 raw_sharp_rangek_neg
	{0xE6, 0x20, 0, 0},   //# 3E6 raw_sharp_rangek_pos
//#
	{0xFD, 0x02, 0, 0},
	{0x32, 0x0D, 0, 0},   //# 232 auto_mode
	{0x33, 0xEF, 0, 0},   //# 233 lsc_bpc_en
	{0x34, 0xFF, 0, 0},   //# 234 buf_isp_mode
	{0xFB, 0x00, 0, 0},   //# 2FB blackgain_en,bl_bpc_en,abl
	{0x36, 0x00, 0, 0},   //# 236 buf_outmode2
};

//----- UXGA -------
static struct reg_value rnss2e1_setting_12fps_UXGA_1600_1200[] = {
	{0xFD, 0x02, 0, 0},
	{0x36, 0x00, 0, 0},   //# 236 buf_outmode2
//#
	{0xFD, 0x00, 0, 0},
	{0x10, 0x1E, 0, 0},   //# 010 clk_mode
	{0x11, 0x40, 0, 0},   //# 011 pclk_inv,pclk_gate_en,pclk_ctrl,isp_clk_ctrl
//	{0x20, 0x02, 0, 0},   //# 020 ds_data,out_end_high8,out_end_low2,out_ens
	{0x20, 0x0A, 0, 0},   //# 020 ds_data,out_end_high8,out_end_low2,out_ens
	{0x21, 0x03, 0, 0},   //# 021 pe_hvp,pe_data,ds_s,buf_dis_s,buf_dis_d
//#
	{0xFD, 0x01, 0, 0},
//	{0x03, 0x03, 0, 0},   //# 103 buf_exp_5msb
//	{0x04, 0xBA, 0, 0},   //# 104 buf_exp_8lsb
	{0x03, 0x02, 0, 0},   //# 103 buf_exp_5msb
	{0x04, 0x7C, 0, 0},   //# 104 buf_exp_8lsb
	{0x09, 0x00, 0, 0},   //# 109 hblank_4msb
	{0x0A, 0x53, 0, 0},   //# 10A hblank_8lsb
//#
	{0xFD, 0x00, 0, 0},
	{0x0E, 0x40, 0, 0},   //# 00E pd
//#
	{0xFD, 0x01, 0, 0},
	{0x0E, 0x00, 0, 0},   //# 10E p0
	{0x0F, 0x18, 0, 0},   //# 10F p1
	{0x10, 0x10, 0, 0},   //# 110 p2
	{0x11, 0x03, 0, 0},   //# 111 p3
	{0x12, 0x18, 0, 0},   //# 112 p4
	{0x13, 0x10, 0, 0},   //# 113 p5
	{0x14, 0x15, 0, 0},   //# 114 p6
	{0x15, 0x01, 0, 0},   //# 115 p7
	{0x16, 0x02, 0, 0},   //# 116 p8
	{0x17, 0x10, 0, 0},   //# 117 p9
	{0x18, 0x00, 0, 0},   //# 118 p10_2msb
	{0x19, 0x1A, 0, 0},   //# 119 p10_8lsb
	{0x1A, 0x00, 0, 0},   //# 11A p11_2msb
	{0x1B, 0x1C, 0, 0},   //# 11B p11_8lsb
	{0x50, 0x00, 0, 0},   //# 150 p12_2msb
	{0x51, 0x1D, 0, 0},   //# 151 p12_8lsb
	{0x52, 0x15, 0, 0},   //# 152 P13
	{0x2A, 0x02, 0, 0},   //# 12A p16
	{0x53, 0x00, 0, 0},   //# 153 p17_2msb
	{0x54, 0x11, 0, 0},   //# 154 p17_8lsb
	{0x55, 0x12, 0, 0},   //# 155 p18
	{0x56, 0x02, 0, 0},   //# 156 p19
	{0x57, 0x02, 0, 0},   //# 157 p20
	{0x58, 0x00, 0, 0},   //# 158 p21
//#
	{0xFD, 0x00, 0, 0},
	{0x12, 0x04, 0, 0},   //# 012 pll_bias_ctl,pll_delay
	{0x13, 0x04, 0, 0},   //# 013 mipi_pattern_en,pll_test_en,mipi_en
	{0x14, 0x00, 0, 0},   //# 014 pclk_gate,timer_clk_gate,dclk_gate
	{0x15, 0x00, 0, 0},   //# 015 pclk_pha_adj
//#
	{0xFD, 0x01, 0, 0},
	{0x1C, 0x7C, 0, 0},   //# 11C two_timing_en,FPN_33ms_X,pwd_asp_timing_sel,Channel-timing
	{0x21, 0x44, 0, 0},   //# 121 adc_vcm_opin_ctl,adc_vcm_opin_c,col_clk_delay
	{0x22, 0x04, 0, 0},   //# 122 pga_bias_ctl,col_ctrl
	{0x25, 0x00, 0, 0},   //# 125 adc_range_ctl,adc_vcm_ctl,asp_delay
	{0x26, 0x26, 0, 0},   //# 126 adc_dig_offset,sw_delay
	{0x27, 0x6D, 0, 0},   //# 127 delay,black_en,adc_dref_cal,adc_g2x_en,adc_offset_en
	{0x2B, 0x66, 0, 0},   //# 12B adc_offset_ctl_buf_up,adc_offset_ctl_buf_dn
	{0x2C, 0x3F, 0, 0},   //# 12C strobe_en,bl_da
	{0x2D, 0x40, 0, 0},   //# 12D adc_bias_stage,adc_bias_vref
	{0x2E, 0x0D, 0, 0},   //# 12E dout_sel,strobe_sel
//	{0x40, 0xF0, 0, 0},   //# 140 vfpn_bpc_en,vfpn_minus_en
	{0x40, 0xF3, 0, 0},   //# 140 vfpn_bpc_en,vfpn_minus_en
	{0x41, 0x60, 0, 0},   //# 141 vfpn_bpc_th_x1
	{0x42, 0x50, 0, 0},   //# 142 vfpn_bpc_th_x2
	{0x43, 0x28, 0, 0},   //# 143 vfpn_bpc_in_x1
	{0x44, 0x28, 0, 0},   //# 144 vfpn_bpc_in_x2
//	{0x45, 0x0C, 0, 0},   //# 145 vfpn_delta
//	{0x45, 0x06, 0, 0},   //# 145 vfpn_delta(0830)
	{0x45, 0x00, 0, 0},   //# 145 vfpn_delta(0921)
	{0x31, 0x10, 0, 0},   //# 131 buf_comm_ctrl
//#
	{0xFD, 0x02, 0, 0},
	{0x35, 0x40, 0, 0},   //# 235 buf_outmode1
	{0x31, 0x10, 0, 0},   //# 231 digital_gain
	{0x47, 0x00, 0, 0},   //# 247 v_start_3msb
	{0x48, 0x00, 0, 0},   //# 248 v_start_8lsb
	{0x49, 0x04, 0, 0},   //# 249 v_size_3msb
	{0x4A, 0xB0, 0, 0},   //# 24A v_size_8lsb
	{0x4B, 0x00, 0, 0},   //# 24B h_start_3msb
	{0x4C, 0x00, 0, 0},   //# 24C h_start_8lsb
	{0x4D, 0x06, 0, 0},   //# 24D h_size_3msb
	{0x4E, 0x40, 0, 0},   //# 24E h_size_8lsb
//	{0x65, 0x08, 0, 0},   //# 265 blue_suboffset
//	{0x66, 0x06, 0, 0},   //# 266 red_suboffset
//	{0x67, 0x07, 0, 0},   //# 267 gr_suboffset
//	{0x68, 0x07, 0, 0},   //# 268 gb_suboffset
//	{0x65, 0x09, 0, 0},   //# 265 blue_suboffset(0830)
//	{0x66, 0x07, 0, 0},   //# 266 red_suboffset(0830)
//	{0x67, 0x08, 0, 0},   //# 267 gr_suboffset(0830)
//	{0x68, 0x08, 0, 0},   //# 268 gb_suboffset(0830)
	{0x65, 0x0F, 0, 0},   //# 265 blue_suboffset(0921)
	{0x66, 0x0D, 0, 0},   //# 266 red_suboffset(0921)
	{0x67, 0x0E, 0, 0},   //# 267 gr_suboffset(0921)
	{0x68, 0x0E, 0, 0},   //# 268 gb_suboffset(0921)
	{0x5F, 0x02, 0, 0},   //# 25F demo_gain_order,bayer_order
	{0x32, 0x00, 0, 0},   //# 232 auto_mode
	{0x33, 0xEF, 0, 0},   //# 233 lsc_bpc_en
	{0xA4, 0xFF, 0, 0},   //# 2A4 lsc_gain_max
//#
	{0xFD, 0x03, 0, 0},
	{0x66, 0x19, 0, 0},   //# 366 Lsc_rsy_u
	{0x6A, 0x1B, 0, 0},   //# 36A Lsc_gsy_u
	{0x6E, 0x14, 0, 0},   //# 36E Lsc_bsy_u
	{0x67, 0x19, 0, 0},   //# 367 Lsc_rsy_d
	{0x6B, 0x12, 0, 0},   //# 36B Lsc_gsy_d
	{0x6F, 0x14, 0, 0},   //# 36F Lsc_bsy_d
	{0x64, 0x1D, 0, 0},   //# 364 Lsc_rsx_l
	{0x68, 0x18, 0, 0},   //# 368 Lsc_gsx_l
	{0x6C, 0x14, 0, 0},   //# 36C Lsc_bsx_l
	{0x65, 0x15, 0, 0},   //# 365 Lsc_rsx_r
	{0x69, 0x12, 0, 0},   //# 369 Lsc_gsx_r
	{0x6D, 0x0E, 0, 0},   //# 36D Lsc_bsx_r
	{0xB8, 0x08, 0, 0},   //# 3B8 Lsc_rxy_lu
	{0xBC, 0x08, 0, 0},   //# 3BC Lsc_gxy_lu
	{0xC0, 0x08, 0, 0},   //# 3C0 Lsc_bxy_lu
	{0xB9, 0x08, 0, 0},   //# 3B9 Lsc_rxy_ru
	{0xBD, 0x08, 0, 0},   //# 3BD Lsc_gxy_ru
	{0xC1, 0x08, 0, 0},   //# 3C1 Lsc_bxy_ru
	{0xBA, 0x08, 0, 0},   //# 3BA Lsc_rxy_ld
	{0xBE, 0x08, 0, 0},   //# 3BE Lsc_gxy_ld
	{0xC2, 0x08, 0, 0},   //# 3C2 Lsc_bxy_ld
	{0xBB, 0x08, 0, 0},   //# 3BB Lsc_rxy_rd
	{0xBF, 0x08, 0, 0},   //# 3BF Lsc_gxy_rd
	{0xC3, 0x08, 0, 0},   //# 3C3 Lsc_bxy_rd
//#
	{0xFD, 0x02, 0, 0},
	{0x51, 0x00, 0, 0},   //# 251 bpc_vt_outdoor
	{0x52, 0x00, 0, 0},   //# 252 bpc_vt_normal
	{0x53, 0x00, 0, 0},   //# 253 bpc_vt_low_light
	{0x54, 0x00, 0, 0},   //# 254 bpc_wt_eff
	{0x55, 0xFF, 0, 0},   //# 255 bpc_dt_eff
//	{0x45, 0x00, 0, 0},   //# 245 bpc_range_ratio_outdoor,pc_range_ratio_nr
//	{0x46, 0x09, 0, 0},   //# 246 bpc_range_ratio_dummy,bpc_range_ratio_low
	{0x45, 0x13, 0, 0},   //# 245 bpc_range_ratio_outdoor,pc_range_ratio_nr (1001)
	{0x46, 0x49, 0, 0},   //# 246 bpc_range_ratio_dummy,bpc_range_ratio_low (1001)
	{0x69, 0x00, 0, 0},   //# 269 bpc_range_thr_outdoor
	{0x6A, 0x00, 0, 0},   //# 26A bpc_range_thr_nr
	{0x6B, 0x00, 0, 0},   //# 26B bpc_range_thr_dummy
	{0x6C, 0x00, 0, 0},   //# 26C bpc_range_thr_low
//#
	{0xFD, 0x03, 0, 0},
	{0xDE, 0x0F, 0, 0},   //# 3DE raw_denoise_en_outdoor,raw_denoise_en_nr,raw_denoise_en_dummy,raw_denoise_en_low
//#
	{0xFD, 0x02, 0, 0},
	{0x57, 0x04, 0, 0},   //# 257 raw_dif_thr_outdoor
	{0x58, 0x04, 0, 0},   //# 258 raw_dif_thr_normal
	{0x56, 0x0A, 0, 0},   //# 256 raw_dif_thr_dummy
	{0x59, 0x08, 0, 0},   //# 259 raw_dif_thr_low_light
	{0x4F, 0xE0, 0, 0},   //# 24F raw_gf_fac_outdoor
	{0xC3, 0xE0, 0, 0},   //# 2C3 raw_gf_fac_indoor
	{0x3F, 0xC0, 0, 0},   //# 23F raw_gf_fac_dummy
	{0x42, 0x40, 0, 0},   //# 242 raw_gf_fac_low
	{0x5A, 0xE0, 0, 0},   //# 25A raw_rb_fac_outdoor
	{0xC4, 0xE0, 0, 0},   //# 2C4 raw_rb_fac_indoor
	{0x43, 0xC0, 0, 0},   //# 243 raw_rb_fac_dummy
	{0xAD, 0x40, 0, 0},   //# 2AD raw_rb_fac_low
	{0xC2, 0x15, 0, 0},   //# 2C2 gf_ratiok_fac
//#
	{0xFD, 0x03, 0, 0},
	{0x50, 0x00, 0, 0},   //# 350 raw_grgb_thr_outdoor
	{0x51, 0x00, 0, 0},   //# 351 raw_grgb_thr_normal
	{0x52, 0x08, 0, 0},   //# 352 raw_grgb_thr_dummy
	{0x53, 0x08, 0, 0},   //# 353 raw_grgb_thr_low
//#
	{0xFD, 0x02, 0, 0},
	{0xB6, 0xE0, 0, 0},   //# 2B6 raw_gflt_fac_outdoor
	{0xB7, 0xC0, 0, 0},   //# 2B7 raw_gflt_fac_nr
	{0xB8, 0xA0, 0, 0},   //# 2B8 raw_gflt_fac_dummy
	{0xB9, 0x20, 0, 0},   //# 2B9 raw_gflt_fac_low
//#
	{0xFD, 0x03, 0, 0},
	{0x11, 0x1F, 0, 0},   //# 311 rg_dif_th
	{0x12, 0x1F, 0, 0},   //# 312 bg_dif_th
	{0x16, 0x1C, 0, 0},   //# 316 rgb_limit
	{0x18, 0x00, 0, 0},   //# 318 br_offset_f
	{0x19, 0x00, 0, 0},   //# 319 br_offset
	{0x1B, 0x80, 0, 0},   //# 31B rg_base
	{0x1A, 0x80, 0, 0},   //# 31A bg_base
	{0x43, 0x80, 0, 0},   //# 343 channel_sel,test_awb
	{0x1E, 0x17, 0, 0},   //# 31E wb_fine_gain_step,wb_rough_gain_step
	{0x1F, 0x19, 0, 0},   //# 31F wb_dif_fine_th,wb_dif_rough_th
//	{0x28, 0x9E, 0, 0},   //# 328 buf_rgain
//	{0x29, 0xA2, 0, 0},   //# 329 buf_bgain
	{0x28, 0x9D, 0, 0},   //# 328 buf_rgain(1001)
	{0x29, 0xA9, 0, 0},   //# 329 buf_bgain(1001)
//#
	{0xFD, 0x02, 0, 0},
	{0xE7, 0x03, 0, 0},   //# 2E7 reg_renew
	{0xE7, 0x00, 0, 0},   //# 2E7 reg_renew
//#
	{0xFD, 0x03, 0, 0},
	{0x2A, 0xF0, 0, 0},   //# 32A y_top_th
	{0x2B, 0x10, 0, 0},   //# 32B y_bot_th
	{0x2E, 0x04, 0, 0},   //# 32E rg_limit_log
	{0x2F, 0x16, 0, 0},   //# 32F bg_limit_log
	{0x00, 0xE0, 0, 0},   //# 300 rgain_top_outdoor
	{0x01, 0x80, 0, 0},   //# 301 rgain_bot_outdoor
	{0x02, 0xE0, 0, 0},   //# 302 bgain_top_outdoor
	{0x03, 0x80, 0, 0},   //# 303 bgain_bot_outdoor
	{0x20, 0xE0, 0, 0},   //# 320 rgain_top_dummy
	{0x21, 0x60, 0, 0},   //# 321 rgain_bot_dummy
	{0x22, 0xE0, 0, 0},   //# 322 bgain_top_dummy
	{0x23, 0x60, 0, 0},   //# 323 bgain_bot_dummy
	{0x83, 0x70, 0, 0},   //# 383 skin_num_th
	{0x13, 0x43, 0, 0},   //# 313 awb_grey_en,awb_skin_en
	{0x24, 0x06, 0, 0},   //# 324 short_exp_th
	{0x25, 0x80, 0, 0},   //# 325 sp_rg_base
	{0x26, 0x80, 0, 0},   //# 326 sp_bg_base
	{0x35, 0xB2, 0, 0},   //# 335 d65_rg_bot
	{0x36, 0xCA, 0, 0},   //# 336 d65_rg_top
//	{0x37, 0x7C, 0, 0},   //# 337 d65_bg_bot
	{0x37, 0x73, 0, 0},   //# 337 d65_bg_bot(1001)
	{0x38, 0x94, 0, 0},   //# 338 d65_bg_top
//	{0x31, 0x7B, 0, 0},   //# 331 f_rg_bot
//	{0x32, 0x93, 0, 0},   //# 332 f_rg_top
//	{0x33, 0xAE, 0, 0},   //# 333 f_bg_bot
//	{0x34, 0xC6, 0, 0},   //# 334 f_bg_top
	{0x31, 0x60, 0, 0},   //# 331 f_rg_bot(1010)
	{0x32, 0x98, 0, 0},   //# 332 f_rg_top(1010)
	{0x33, 0xA8, 0, 0},   //# 333 f_bg_bot(1010)
	{0x34, 0xD8, 0, 0},   //# 334 f_bg_top(1010)
	{0x3D, 0x9C, 0, 0},   //# 33D cwf_rg_bot
	{0x3E, 0xB4, 0, 0},   //# 33E cwf_rg_top
	{0x3F, 0xA4, 0, 0},   //# 33F cwf_bg_bot
	{0x40, 0xBC, 0, 0},   //# 340 cwf_bg_top
	{0x39, 0x8A, 0, 0},   //# 339 tl84_rg_bot
	{0x3A, 0xA2, 0, 0},   //# 33A tl84_rg_top
	{0x3B, 0x9E, 0, 0},   //# 33B tl84_bg_bot
	{0x3C, 0xB6, 0, 0},   //# 33C tl84_bg_top
	{0xA0, 0xA6, 0, 0},   //# 3A0 c00_eff1_8lsb
	{0xA1, 0xCD, 0, 0},   //# 3A1 c01_eff1_8lsb
	{0xA2, 0x0C, 0, 0},   //# 3A2 c02_eff1_8lsb
	{0xA3, 0x06, 0, 0},   //# 3A3 c10_eff1_8lsb
	{0xA4, 0x8C, 0, 0},   //# 3A4 c11_eff1_8lsb
	{0xA5, 0xED, 0, 0},   //# 3A5 c12_eff1_8lsb
	{0xA6, 0x00, 0, 0},   //# 3A6 c20_eff1_8lsb
	{0xA7, 0xE7, 0, 0},   //# 3A7 c21_eff1_8lsb
	{0xA8, 0x99, 0, 0},   //# 3A8 c22_eff1_8lsb
	{0xA9, 0x0C, 0, 0},   //# 3A9 c02_eff1_2msb,c01_eff1_2msb,c00_eff1_2msb
	{0xAA, 0x30, 0, 0},   //# 3AA c12_eff1_2msb,c11_eff1_2msb,c10_eff1_2msb
	{0xAB, 0x0C, 0, 0},   //# 3AB c22_eff1_2msb,c21_eff1_2msb,c20_eff1_2msb
	{0xAC, 0x8C, 0, 0},   //# 3AC c00_eff2_8lsb
	{0xAD, 0xF4, 0, 0},   //# 3AD c01_eff2_8lsb
	{0xAE, 0x00, 0, 0},   //# 3AE c02_eff2_8lsb
	{0xAF, 0xFA, 0, 0},   //# 3AF c10_eff2_8lsb
	{0xB0, 0x8C, 0, 0},   //# 3B0 c11_eff2_8lsb
	{0xB1, 0xFA, 0, 0},   //# 3B1 c12_eff2_8lsb
	{0xB2, 0x0C, 0, 0},   //# 3B2 c20_eff2_8lsb
	{0xB3, 0xF4, 0, 0},   //# 3B3 c21_eff2_8lsb
	{0xB4, 0x80, 0, 0},   //# 3B4 c22_eff2_8lsb
	{0xB5, 0x0C, 0, 0},   //# 3B5 c02_eff2_2msb,c01_eff2_2msb,c00_eff2_2msb
	{0xB6, 0x33, 0, 0},   //# 3B6 c12_eff2_2msb,c11_eff2_2msb,c10_eff2_2msb
	{0xB7, 0x0C, 0, 0},   //# 3B7 c22_eff2_2msb,c21_eff2_2msb,c20_eff2_2msb
//#
	{0xFD, 0x02, 0, 0},
	{0xBF, 0x01, 0, 0},   //# 2BF autosa_en
	{0xBE, 0xAA, 0, 0},   //# 2BE u_v_th
	{0xC0, 0xFF, 0, 0},   //# 2C0 y_p_th
	{0xC1, 0xFF, 0, 0},   //# 2C1 y_mean_th
	{0xD3, 0x98, 0, 0},   //# 2D3 sat_u_s1
	{0xD4, 0x98, 0, 0},   //# 2D4 sat_u_s2
	{0xD6, 0x88, 0, 0},   //# 2D6 sat_u_s3
	{0xD7, 0x50, 0, 0},   //# 2D7 sat_u_s4
	{0xD8, 0x98, 0, 0},   //# 2D8 sat_v_s1
	{0xD9, 0x98, 0, 0},   //# 2D9 sat_v_s2
	{0xDA, 0x88, 0, 0},   //# 2DA sat_v_s3
	{0xDB, 0x50, 0, 0},   //# 2DB sat_v_s4
	{0x8B, 0x00, 0, 0},   //# 28B gamma_pt0
	{0x8C, 0x0F, 0, 0},   //# 28C gamma_pt1
	{0x8D, 0x1F, 0, 0},   //# 28D gamma_pt2
	{0x8E, 0x3C, 0, 0},   //# 28E gamma_pt3
	{0x8F, 0x67, 0, 0},   //# 28F gamma_pt4
	{0x90, 0x85, 0, 0},   //# 290 gamma_pt5
	{0x91, 0x99, 0, 0},   //# 291 gamma_pt6
	{0x92, 0xA8, 0, 0},   //# 292 gamma_pt7
	{0x93, 0xB5, 0, 0},   //# 293 gamma_pt8
	{0x94, 0xBE, 0, 0},   //# 294 gamma_pt9
	{0x95, 0xC8, 0, 0},   //# 295 gamma_pt10
	{0x96, 0xD1, 0, 0},   //# 296 gamma_pt11
	{0x97, 0xD9, 0, 0},   //# 297 gamma_pt12
	{0x98, 0xE0, 0, 0},   //# 298 gamma_pt13
	{0x99, 0xE8, 0, 0},   //# 299 gamma_pt14
	{0x9A, 0xED, 0, 0},   //# 29A gamma_pt15
	{0x9B, 0xF3, 0, 0},   //# 29B gamma_pt16
//#
	{0xFD, 0x03, 0, 0},
	{0x8D, 0xF9, 0, 0},   //# 38D gamma_pt17
	{0x8E, 0xFF, 0, 0},   //# 38E gamma_pt18
//#
	{0xFD, 0x02, 0, 0},
	{0x78, 0x00, 0, 0},   //# 278 gamma_pt2_0
	{0x79, 0x0F, 0, 0},   //# 279 gamma_pt2_1
	{0x7A, 0x1F, 0, 0},   //# 27A gamma_pt2_2
	{0x7B, 0x3C, 0, 0},   //# 27B gamma_pt2_3
	{0x7C, 0x67, 0, 0},   //# 27C gamma_pt2_4
	{0x7D, 0x85, 0, 0},   //# 27D gamma_pt2_5
	{0x7E, 0x99, 0, 0},   //# 27E gamma_p2_6
	{0x7F, 0xA8, 0, 0},   //# 27F gamma_pt2_7
	{0x80, 0xB5, 0, 0},   //# 280 gamma_pt2_8
	{0x81, 0xBE, 0, 0},   //# 281 gamma_pt2_9
	{0x82, 0xC8, 0, 0},   //# 282 gamma_pt2_10
	{0x83, 0xD1, 0, 0},   //# 283 gamma_pt2_11
	{0x84, 0xD9, 0, 0},   //# 284 gamma_pt2_12
	{0x85, 0xE0, 0, 0},   //# 285 gamma_pt2_13
	{0x86, 0xE8, 0, 0},   //# 286 gamma_pt2_14
	{0x87, 0xED, 0, 0},   //# 287 gamma_pt2_15
	{0x88, 0xF3, 0, 0},   //# 288 gamma_pt2_16
	{0x89, 0xF9, 0, 0},   //# 289 gamma_pt2_17
	{0x8A, 0xFF, 0, 0},   //# 28A gamma_pt2_18
//#
	{0xFD, 0x03, 0, 0},
	{0x96, 0x46, 0, 0},   //# 396 ae time thr1
	{0x97, 0x28, 0, 0},   //# 397 ae time thr2
	{0x9F, 0x0A, 0, 0},   //# 39F gma_ratiok_fac
//#
	{0xFD, 0x02, 0, 0},
	{0xF4, 0x0B, 0, 0},   //# 2F4 lum_fcase_en,lum_down_en,outdoor_mode_en,mean_mode_reg
	{0xF0, 0x9F, 0, 0},   //# 2F0 ABF_exp_base_8lsb
	{0xF1, 0x00, 0, 0},   //# 2F1 exp_min_base_msb
//#
	{0xFD, 0x03, 0, 0},
	{0x90, 0x14, 0, 0},   //# 390 exp_max_indr
	{0x92, 0x01, 0, 0},   //# 392 exp_min_indr
	{0x94, 0xC0, 0, 0},   //# 394 rpc_max_indr
	{0x95, 0x20, 0, 0},   //# 395 rpc_min_indr
	{0x98, 0x9F, 0, 0},   //# 398 exp_max_outdr[7:0]
	{0x99, 0x00, 0, 0},   //# 399 exp_max_outdr[12:8]
	{0x9A, 0x01, 0, 0},   //# 39A exp_min_outdr[7:0]
	{0x9B, 0x00, 0, 0},   //# 39B exp_min_outdr[12:8]
	{0x9C, 0x32, 0, 0},   //# 39C rpc_max_outdr
	{0x9D, 0x20, 0, 0},   //# 39D rpc_min_outdr
//#
	{0xFD, 0x02, 0, 0},
	{0xEC, 0x78, 0, 0},   //# 2EC lum_low_thd_indr_hd
	{0xED, 0x88, 0, 0},   //# 2ED lum_up_thd_indr_hd
	{0xEE, 0x78, 0, 0},   //# 2EE lum_low_thd_outdr_hd
	{0xEF, 0x88, 0, 0},   //# 2EF lum_up_thd_outdr_hd
	{0xF7, 0x84, 0, 0},   //# 2F7 lum_up_thd_indr
	{0xF8, 0x7C, 0, 0},   //# 2F8 lum_low_thd_indr
	{0xF9, 0x84, 0, 0},   //# 2F9 lum_up_thd_outdr
	{0xFA, 0x7C, 0, 0},   //# 2FA lum_low_thd_outdr
//#
	{0xFD, 0x03, 0, 0},
	{0x55, 0x11, 0, 0},   //# 355 weight_w2,weight_w1
	{0x56, 0x11, 0, 0},   //# 356 weight_w4,weight_w3
//	{0x57, 0x03, 0, 0},   //# 357 weight_w5
	{0x57, 0x01, 0, 0},   //# 357 weight_w5(1001)
//#
	{0xFD, 0x02, 0, 0},
	{0xE0, 0x3E, 0, 0},   //# 2E0 rpc_1base_max
	{0xE1, 0x26, 0, 0},   //# 2E1 rpc_2base_max
	{0xE2, 0x2A, 0, 0},   //# 2E2 rpc_3base_max
	{0xE3, 0x26, 0, 0},   //# 2E3 rpc_4base_max
	{0xE4, 0x26, 0, 0},   //# 2E4 rpc_5base_max
	{0xE5, 0x24, 0, 0},   //# 2E5 rpc_6base_max
	{0xE6, 0x24, 0, 0},   //# 2E6 rpc_7base_max
	{0xE8, 0x22, 0, 0},   //# 2E8 rpc_8base_max
	{0xE9, 0x22, 0, 0},   //# 2E9 rpc_9base_max
	{0xEA, 0x22, 0, 0},   //# 2EA rpc_10base_max
	{0xEB, 0x20, 0, 0},   //# 2EB rpc_11base_max
	{0xF5, 0x20, 0, 0},   //# 2F5 rpc_12base_max
	{0xF6, 0x20, 0, 0},   //# 2F6 rpc_13base_max
	{0xF3, 0x03, 0, 0},   //# 2F3 uv_dif_en_outdoor,uv_dif_en_nr,uv_dif_en_dummy,uv_dif_en_low
	{0xB0, 0x00, 0, 0},   //# 2B0 uv_dif_gain_outdoor,uv_dif_gain_nr
	{0xB1, 0x12, 0, 0},   //# 2B1 uv_dif_gain_dummy,uv_dif_gain_low
//#
	{0xFD, 0x03, 0, 0},
	{0xDF, 0x0F, 0, 0},   //# 3DF sharpness
	{0xE7, 0x08, 0, 0},   //# 3E7 raw_sharp_range_base
	{0xE8, 0x50, 0, 0},   //# 3E8 sharp_fac_pos_outdoor
	{0xE9, 0x50, 0, 0},   //# 3E9 sharp_fac_pos_nr
	{0xEA, 0x30, 0, 0},   //# 3EA sharp_fac_pos_dummy
	{0xEB, 0x20, 0, 0},   //# 3EB sharp_fac_pos_low
	{0xEC, 0x20, 0, 0},   //# 3EC sharp_fac_neg_outdoor
	{0xED, 0x20, 0, 0},   //# 3ED sharp_fac_neg_nr
	{0xEF, 0x20, 0, 0},   //# 3EF sharp_fac_neg_dummy
	{0xF0, 0x20, 0, 0},   //# 3F0 sharp_fac_neg_low
	{0x70, 0x73, 0, 0},   //# 370 aec_gw_en,gw_uv_dif_en,gw_detect_en,gw_step
	{0x7B, 0x40, 0, 0},   //# 37B gw_mean_th
	{0x71, 0x2F, 0, 0},   //# 371 k_up
	{0x72, 0x0D, 0, 0},   //# 372 k_low
	{0x73, 0x0A, 0, 0},   //# 373 b_up
	{0x74, 0x2A, 0, 0},   //# 374 b_low
	{0x75, 0x04, 0, 0},   //# 375 uv_low_th
	{0x76, 0x20, 0, 0},   //# 376 y_low_th
	{0x77, 0x32, 0, 0},   //# 377 u_top
	{0x78, 0x00, 0, 0},   //# 378 u_bot
	{0x79, 0x28, 0, 0},   //# 379 v_top
	{0x7A, 0x00, 0, 0},   //# 37A v_bot
	{0x7C, 0x70, 0, 0},   //# 37C gw_offset
	{0x7D, 0x90, 0, 0},   //# 37D gw_y_bot
	{0x7E, 0xEF, 0, 0},   //# 37E gw_y_top
	{0x7F, 0x04, 0, 0},   //# 37F gw_uv_radius
	{0x80, 0x40, 0, 0},   //# 380 uv_fix_dat
	{0x81, 0x20, 0, 0},   //# 381 y_offset_th
	{0x8F, 0x12, 0, 0},   //# 38F wt_th
	{0xCE, 0x6C, 0, 0},   //# 3CE exp_heq_dummy[7:0]
	{0xCF, 0x0C, 0, 0},   //# 3CF exp_heq_dummy[12:8]
	{0xCD, 0x30, 0, 0},   //# 3CD rpc_heq_dummy
	{0xCA, 0x68, 0, 0},   //# 3CA mean_dummy_low
	{0xCB, 0x88, 0, 0},   //# 3CB mean_low_dummy
	{0xD0, 0x6C, 0, 0},   //# 3D0 exp_heq_low[7:0]
	{0xD1, 0x0C, 0, 0},   //# 3D1 exp_heq_low[12:8]
	{0xCC, 0xC0, 0, 0},   //# 3CC rpc_heq_low
	{0xD5, 0x80, 0, 0},   //# 3D5 mean_nr_dummy
	{0xD6, 0x90, 0, 0},   //# 3D6 mean_dummy_nr
	{0xD7, 0x9C, 0, 0},   //# 3D7 exp_nr_outd_8lsb
	{0xD8, 0x00, 0, 0},   //# 3D8 exp_nr_outd_5hsb
	{0xD9, 0x9F, 0, 0},   //# 3D9 exp_outd_nr_8lsb
	{0xDA, 0x00, 0, 0},   //# 3DA exp_outd_nr_5hsb
//#
	{0xFD, 0x02, 0, 0},
	{0xB2, 0x30, 0, 0},   //# 2B2 lum_limit
	{0xB3, 0x18, 0, 0},   //# 2B3 lum_set
	{0xB4, 0x60, 0, 0},   //# 2B4 black_vt
	{0xB5, 0x70, 0, 0},   //# 2B5 white_vt
	{0xCB, 0x00, 0, 0},   //# 2CB rg_clip_ga_outdoor
	{0xCC, 0x02, 0, 0},   //# 2CC rg_clip_ga_nr
	{0xCD, 0x05, 0, 0},   //# 2CD rg_clip_ga_dummy
	{0xCE, 0x08, 0, 0},   //# 2CE rg_clip_ga_low
	{0xCF, 0x00, 0, 0},   //# 2CF bg_clip_ga_outdoor
	{0xD0, 0x02, 0, 0},   //# 2D0 bg_clip_ga_nr
//#
	{0xFD, 0x03, 0, 0},
	{0x10, 0x05, 0, 0},   //# 310 bg_clip_ga_dummy
	{0x14, 0x08, 0, 0},   //# 314 bg_clip_ga_low
//#
	{0xFD, 0x02, 0, 0},
	{0x5B, 0x00, 0, 0},   //# 25B cnr_thr_outdoor
	{0x61, 0x08, 0, 0},   //# 261 cnr_thr_nr
	{0x77, 0x40, 0, 0},   //# 277 cnr_thr_dummy
	{0xCA, 0x60, 0, 0},   //# 2CA cnr_thr_low
//	{0xAB, 0x10, 0, 0},   //# 2AB ynr_thr_outdoor
	{0xAB, 0x00, 0, 0},   //# 2AB ynr_thr_outdoor(1001)
	{0xAC, 0x10, 0, 0},   //# 2AC ynr_thr_nr
	{0xAE, 0x60, 0, 0},   //# 2AE ynr_thr_dummy
	{0xAF, 0x40, 0, 0},   //# 2AF ynr_thr_low
	{0x60, 0x01, 0, 0},   //# 260 bpc_vt_dummy
	{0x70, 0x0A, 0, 0},   //# 270 Bpc_v
	{0x76, 0x00, 0, 0},   //# 276 blacklevelin
	{0xC5, 0x60, 0, 0},   //# 2C5 raw_gflt_fac_indoor
	{0xDC, 0x00, 0, 0},   //# 2DC buf_heq_offset
	{0xDD, 0x80, 0, 0},   //# 2DD ku
	{0xDE, 0x90, 0, 0},   //# 2DE kl
//#
	{0xFD, 0x03, 0, 0},
	{0x06, 0x00, 0, 0},   //# 306 ratio_row[9:8]
	{0x07, 0x25, 0, 0},   //# 307 ratio_row[7:0]
	{0x08, 0x00, 0, 0},   //# 308 ratio_col[9:8]
	{0x09, 0x28, 0, 0},   //# 309 ratio_col[7:0]
	{0x0A, 0x04, 0, 0},   //# 30A scalerownum[10:8]
	{0x0B, 0x00, 0, 0},   //# 30B scalerownum[7:0]
	{0x0C, 0x05, 0, 0},   //# 30C scalecolnum[10:8]
	{0x0D, 0x00, 0, 0},   //# 30D scalecolnum[7:0]
	{0x0E, 0x00, 0, 0},   //# 30E resize_en
	{0x1C, 0xBA, 0, 0},   //# 31C f_limit_b
	{0x1D, 0x87, 0, 0},   //# 31D f_limit_r
	{0x41, 0x00, 0, 0},   //# 341 grgb_top_high_bit
	{0x42, 0x00, 0, 0},   //# 342 grgb_bot_high_bit
	{0x44, 0x0F, 0, 0},   //# 344 wb_num_th_light_s
	{0x4C, 0x48, 0, 0},   //# 34C raw_adt_fac_outdoor
	{0x4D, 0x48, 0, 0},   //# 34D raw_adt_fac_normal
	{0x4E, 0x48, 0, 0},   //# 34E raw_adt_fac_dummy
	{0x4F, 0x48, 0, 0},   //# 34F raw_adt_fac_low
	{0xC6, 0x40, 0, 0},   //# 3C6 pre_grgain
	{0xC7, 0x40, 0, 0},   //# 3C7 pre_rgain
	{0xC8, 0x40, 0, 0},   //# 3C8 pre_gbgain
	{0xC9, 0x40, 0, 0},   //# 3C9 pre_bgain
	{0xE2, 0x40, 0, 0},   //# 3E2 raw_sharp_y_base
	{0xE3, 0x10, 0, 0},   //# 3E3 raw_sharp_y_min
	{0xE4, 0xE0, 0, 0},   //# 3E4 raw_sharp_y_max
	{0xE5, 0x30, 0, 0},   //# 3E5 raw_sharp_rangek_neg
	{0xE6, 0x20, 0, 0},   //# 3E6 raw_sharp_rangek_pos
//#
	{0xFD, 0x02, 0, 0},
	{0x32, 0x0D, 0, 0},   //# 232 auto_mode
	{0x33, 0xEF, 0, 0},   //# 233 lsc_bpc_en
	{0x34, 0xFF, 0, 0},   //# 234 buf_isp_mode
	{0xFB, 0x00, 0, 0},   //# 2FB blackgain_en,bl_bpc_en,abl
	{0x36, 0x00, 0, 0},   //# 236 buf_outmode2
};

static struct rnss2e1_mode_info rnss2e1_mode_info_data[2][rnss2e1_mode_MAX + 1] = {
	{
		{rnss2e1_mode_QVGA_320_240, 320, 240,
		rnss2e1_setting_15fps_QVGA_320_240,
		ARRAY_SIZE(rnss2e1_setting_15fps_QVGA_320_240)},

		{rnss2e1_mode_VGA_640_480, 640, 480,
		rnss2e1_setting_15fps_VGA_640_480,
		ARRAY_SIZE(rnss2e1_setting_15fps_VGA_640_480)},

		{rnss2e1_mode_SVGA_800_600, 800, 600,
		rnss2e1_setting_15fps_SVGA_800_600,
		ARRAY_SIZE(rnss2e1_setting_15fps_SVGA_800_600)},

		{rnss2e1_mode_XGA_1024_768, 1024, 768,
		rnss2e1_setting_12fps_XGA_1024_768,
		ARRAY_SIZE(rnss2e1_setting_12fps_XGA_1024_768)},

		{rnss2e1_mode_HD_1280_720, 1280, 720,
		rnss2e1_setting_15fps_HD_1280_720,
		ARRAY_SIZE(rnss2e1_setting_15fps_HD_1280_720)},

		{rnss2e1_mode_UXGA_1600_1200, 1600, 1200,
		rnss2e1_setting_12fps_UXGA_1600_1200,
		ARRAY_SIZE(rnss2e1_setting_12fps_UXGA_1600_1200)},
	},
	{
		{rnss2e1_mode_QVGA_320_240, 320, 240,
		rnss2e1_setting_30fps_QVGA_320_240,
		ARRAY_SIZE(rnss2e1_setting_30fps_QVGA_320_240)},

		{rnss2e1_mode_VGA_640_480, 640, 480,
		rnss2e1_setting_30fps_VGA_640_480,
		ARRAY_SIZE(rnss2e1_setting_30fps_VGA_640_480)},

		{rnss2e1_mode_SVGA_800_600, 800, 600,
		rnss2e1_setting_30fps_SVGA_800_600,
		ARRAY_SIZE(rnss2e1_setting_30fps_SVGA_800_600)},

		{rnss2e1_mode_XGA_1024_768, 1024, 768,
		0x00,
		0x00},

		{rnss2e1_mode_HD_1280_720, 1280, 720,
		rnss2e1_setting_24fps_HD_1280_720,
		ARRAY_SIZE(rnss2e1_setting_24fps_HD_1280_720)},

		{rnss2e1_mode_UXGA_1600_1200, 1600, 1200,
		0x00,
		0x00},
	}
};

