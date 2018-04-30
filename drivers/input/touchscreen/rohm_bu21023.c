/* drivers/input/touchscreen/rohm_bu21023.c
 *
 * ROHM BU21023 touchscreen driver
 *
 * Copyright (C) 2010 ROHM SEMICONDUCTOR Co. Ltd.
 *
 * Author: CT Cheng <ct.cheng@rohm.com.tw>
 *
 * Modify: SPI -> IIC, Polling -> Interrupt, Add Filter, by Tracy Wen <tracy-wen@rohm.com.cn> 
 *
 * Firmware version: ver33, without manual calibration
 */

#include <linux/module.h>
#include <linux/delay.h>
#include <linux/hrtimer.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include <asm/irq.h>
#include <linux/platform_device.h>
#include <linux/i2c/rohm_bu21023.h>

#include <linux/slab.h>
#include "bu21023_37_i005_120720.h"

//ROHM setting
#define TOUCH_SCREEN_SETTING

#ifdef TOUCH_SCREEN_SETTING
#define ROHM_TS_ABS_X_MIN 	0
#define ROHM_TS_ABS_X_MAX 	1024
#define ROHM_TS_ABS_Y_MIN 	0
#define ROHM_TS_ABS_Y_MAX 	1200
#define DISP_X_MAX 1024
#define DISP_Y_MAX 1600
#define SW_AVG
//#define	FILTER_2
#endif

/* Print the coordinate of touch point in the debug console */

//#define SHOW_TOUCH_POINT
#define TWO_COUNT 10 //15
#define ONE_COUNT 5	  //10
#define KEY_COUNT 10
#define DELTA_X 100
#define DELTA_Y 160
#define STEP_DIFF 0x10
#define TIMER_NS  10000000	//report rate 1/10000000=100Hz	
#define TIMER_NS1	10000000	//report rate 1/１0000000=100Hz	
//#define TIMER_NS1	40000000	//report rate 1/50000000=100Hz	
//#define TIMER_NS1	100000000	//report rate 1/100000000=10Hz
#define Y_MAX_DEC	0xFFFF
/********************************************/


#ifdef SW_AVG

/* Size of Moving Average buffer array */
#define BUFF_ARRAY  16

#define DISTANCE_X 32
#define DISTANCE_Y 32
#define AVG_BOUND_X 16
#define AVG_BOUND_Y 16
#define S_DISTANCE_X 6
#define S_DISTANCE_Y 6
#define S_AVG_BOUND_X 4
#define S_AVG_BOUND_Y 4

/* skip times of moving average when touch starting */
#define SKIP_AVG_1 5
#define SKIP_AVG_2 5
#endif


struct touch_point
{
	unsigned int x;
	unsigned int y;

#ifdef SW_AVG
	unsigned int buff_x[BUFF_ARRAY];
	unsigned int buff_y[BUFF_ARRAY];
	unsigned char buff_cnt;
	/* Previous coordinate of touch point after moving average calculating */
	unsigned int old_avg_x;
	unsigned int old_avg_y;
#endif


};

struct touch_point tp1, tp2;

static u8 finger_count_0 = 0;	//from 0 to 1
static u8 finger_count_1 = 0;	//from 2 to 1
static u8 finger_count_2 = 0;	//from 0/1 to 2
static u8 key_count = 0;
static u8 error_flg_1 = 0;
static u8 error_flg_2 = 0;
static u8 finger =0;
static u16 x1_old = 0;
static u16 y1_old = 0;
static u16 x2_old = 0;
static u16 y2_old = 0;

/********************************************/

static struct workqueue_struct *rohm_wq;

struct rohm_ts_data 
{
	uint16_t addr;
	struct i2c_client *client;
	struct input_dev *input_dev;
	int use_irq;
	struct hrtimer timer;
	struct work_struct  work;
	uint32_t flags;
	int (*power)(int on);
	int suspend;
};


//---- Sanyo CE
//#define SHOW_DEBUG
//#define SHOW_REG
#define TOUCH_CALIB
#define CMD_REG_BYTE_READ		0x01
#define CMD_REG_WRITE				0x03
#define CMD_IRQ_DISABLE			0x05
#define CMD_IRQ_ENABLE				0x09
#define CMD_PRM_READ					0x10
#define CMD_PRM_WRITE				0x30
#define TS_NAME								"mts"
static int TS_MAJOR;
static struct rohm_ts_data *ts;				//タッチパネル：タッチ座標用
static struct input_dev *ts_key;
/* /sys/module/rohm_bu21023/parameters/calibrationからｷｬﾘﾌﾞﾚｰｼｮﾝ係数取得に変更 */
#define TWO_FINGER_NOP_MAX  5		//1点タッチから２点タッチに変わった直後の座標を無視する最大値
#define ONE_FINGER_NOP_MAX  20	//2点タッチ移動中に１点タッチが来た時にその座標を無視する最大値
static int two_finger_cunt = 0; 	//1点タッチから２点タッチに変わった直後の座標を無視するためのカウンタ
static int two_one_finger = 0;		//2点タッチ移動中に１点タッチが来た時にその座標を無視するためのカウンタ
static int bf_finger = 0;					//前回のタッチ状態
static int old_finger=0;
static int key_sts[5] = {0,0,0,0,0};		//キーの押下状態を示す

static s32 calibration[9];					//画面とタッチパネルのキャリブレーション用パラメータ

module_param_array(calibration, int, NULL, S_IRUGO | S_IWUSR);
static int		TP_XY_GET = 1;

static int 	rohm_ts_check_int(void);
static void rohm_ts_touch_check(void);
//--- 座標補正計算
static void Calib_Calc(struct touch_point *stp) {

	struct touch_point dtp;

	dtp.x = 0;
	dtp.y = 0;
	if( calibration[6] == 0 ) {
		return;		//補正係数なし
	}
	if( stp->x > 0 ) {
		dtp.x = ((calibration[0] * stp->x) +
			(calibration[1] * stp->y) +
				calibration[2]
					) / calibration[6];
	}
	if( stp->y > 0 ) {
		dtp.y = ((calibration[3] * stp->x) +
			(calibration[4] * stp->y) +
				calibration[5]
				) / calibration[6];
	}

	if( dtp.y >= 0x8000 ) {		//負の値の時の処理(unsignedのため正数となるが。。。。)
		dtp.y = ( Y_MAX_DEC - dtp.y ) + (ROHM_TS_ABS_Y_MAX/2); 
	}

	dtp.y = dtp.y * (ROHM_TS_ABS_Y_MAX/ calibration[8] );

	stp->x = dtp.x;
	stp->y = dtp.y;

}

//---- Sanyo CE





#ifdef SW_AVG

//-----------------------------------------------------------------------------
//
//Coord_Avg
//
//-----------------------------------------------------------------------------
static void Coord_Avg(struct touch_point *tp)
{

	unsigned long temp_x = 0, temp_y = 0, temp_n = 0;
	unsigned int i;
	////////////////////////////////////////
	// X1,Y1 Moving Avg
	////////////////////////////////////////
	if((tp->x != 0) && (tp->y != 0))
	{						   			  				  				
		if(tp->buff_cnt >= SKIP_AVG_1)
		{  
		
			if(((abs(tp->buff_x[0] - tp->x) > DISTANCE_X) && (abs(tp->buff_y[0] - tp->y) > DISTANCE_Y)) ||
			   ((abs(tp->buff_x[0] - tp->x) > S_DISTANCE_X) && (abs(tp->buff_y[0] - tp->y) < S_DISTANCE_Y)) ||
			   ((abs(tp->buff_x[0] - tp->x) < S_DISTANCE_X) && (abs(tp->buff_y[0] - tp->y) > S_DISTANCE_Y)) ||
			   (((tp->old_avg_x != 0) && (abs(tp->old_avg_x - tp->x) > AVG_BOUND_X)) && 
			   ( (tp->old_avg_y != 0) && (abs(tp->old_avg_y - tp->y) > AVG_BOUND_Y))) ||
			   (((tp->old_avg_x != 0) && (abs(tp->old_avg_x - tp->x) > S_AVG_BOUND_X)) && 
			   ( (tp->old_avg_y != 0) && (abs(tp->old_avg_y - tp->y) < S_AVG_BOUND_Y)))||
			   (((tp->old_avg_x != 0) && (abs(tp->old_avg_x - tp->x) < S_AVG_BOUND_X)) && 
			   ( (tp->old_avg_y != 0) && (abs(tp->old_avg_y - tp->y) > S_AVG_BOUND_Y))))
			{
				for (i = 0; i < tp->buff_cnt; i++)
				{
					tp->buff_x[tp->buff_cnt - i] = tp->buff_x[tp->buff_cnt - i - 1];
					tp->buff_y[tp->buff_cnt - i] = tp->buff_y[tp->buff_cnt - i - 1];
				}
				tp->buff_x[0] = tp->x;
				tp->buff_y[0] = tp->y;

				temp_x = 0; temp_y = 0; temp_n = 0;

				for (i = 0; i <= tp->buff_cnt; i++)
				{
					temp_x += ((unsigned long) (tp->buff_x[i] * (tp->buff_cnt - i + 1)));
					temp_y += ((unsigned long) (tp->buff_y[i] * (tp->buff_cnt - i + 1)));
					temp_n += (unsigned long) (tp->buff_cnt - i + 1);
				}			
				tp->x = temp_x / temp_n;
				tp->y = temp_y / temp_n;
		
				tp->old_avg_x = tp->x;
				tp->old_avg_y = tp->y;  	
				if(tp->buff_cnt < (BUFF_ARRAY-1))
					tp->buff_cnt++;
			}
			else 
			{	  
				tp->x = tp->old_avg_x;
				tp->y = tp->old_avg_y;	
			} 
		}
		else
		{
			for (i = 0; i < tp->buff_cnt; i++)
			{
				tp->buff_x[tp->buff_cnt - i] = tp->buff_x[tp->buff_cnt - i - 1];
				tp->buff_y[tp->buff_cnt - i] = tp->buff_y[tp->buff_cnt - i - 1];
			}	
			tp->buff_x[0] = tp->x;
			tp->buff_y[0] = tp->y;
			if(tp->buff_cnt < (BUFF_ARRAY-1))
				tp->buff_cnt++;
			tp->old_avg_x = tp->x;
			tp->old_avg_y = tp->y;
			tp->x = 0;
			tp->y = 0;	
		}
	}//End/ of "if((x1 != 0) && (y1 != 0))"
	else 
	{
		tp->buff_cnt = 0;
#if 0
		if((tp->buff_x[0] != 0) && (tp->buff_y[0] != 0))
		{
			tp->x = tp->buff_x[0];
			tp->y = tp->buff_y[0];
		}
		else
		{

			tp->x = 0;
			tp->y = 0;
		}
#else
		tp->x = 0;
		tp->y = 0;
#endif
		tp->buff_x[0] = 0;
		tp->buff_y[0] = 0;
		tp->old_avg_x = 0;
		tp->old_avg_y = 0;
	}


}
#endif

//------------------------------------------
// 再キャリブレーション
// (パネルタッチ解除時に要求がある場合)
//------------------------------------------
static int 	rohm_ts_check_int() {
	int ret;
	int i;

	ret = i2c_smbus_read_byte_data(ts->client, 0x29);
	if((ret & 3 )  !=0 ) return 0;			//Touch & GESTURE  MULTI:OFF&TOUCH:OFF


	if((ret & 4 )  ==0 ) return 0;			//Touch & GESTURE  CALIB_REQ:OFF

#ifdef SHOW_TOUCH_POINT		
	printk("BU21023  Re-Calibration Start!!\n");
#endif

	i2c_smbus_write_byte_data(ts->client, 0x65, 0x21);		//TEST1  DAC_SEL:ON & EN_ADIN_ON
	i2c_smbus_write_byte_data(ts->client, 0x42, 0x00);		//FORCE_INT   FRC_CAL:OFF

	for (i=0;i<10;i++)		//Wait 10mse
		{udelay(1000);}

	i2c_smbus_write_byte_data(ts->client, 0x42, 0x01);		//FORCE_INT   FRC_CAL:ON

	for (i=0;i<10;i++)		//Wait 10mse
		{udelay(1000);}

	i2c_smbus_write_byte_data(ts->client, 0x42, 0x00);		//FORCE_INT   FRC_CAL:OFF

	for (i=0;i<10;i++)		//Wait 10mse
		{udelay(1000);}

	ret = i2c_smbus_read_byte_data(ts->client, 0x29);

//#ifdef SHOW_TOUCH_POINT		
	printk("BU21023  Re-Calibration  Request On!!  Result Status:%x\n",ret);
//#endif

//	if( ( ret & 0x0C )  != 0 )
//		i2c_smbus_write_byte_data(ts->client, 0x65, 0x01);

	// 割り込みクリア
	i2c_smbus_write_byte_data(ts->client, 0x3E, 0xFF);		//INT_CLR
	return 1;
}

//---- Sanyo CE タッチパネル上のソフトキーのイベントをあげる

/**
 * キーコード変換処理（ソフトキー用デバイスファイルをOPEN)
 *
 * @param  
 * @return 成功(0)/失敗(-1)
 */
static int keyfile_open( )
{
	int ret;

	ts_key = input_allocate_device();
	if (ts_key == NULL) 
	{
		ret = -ENOMEM;
		printk(KERN_ERR "Rohm_ts_probe: Failed to allocate input device Key\n");
		goto L_end;
	}
	ts_key->name = "Rohm-CTP-BU21023GUL-Key";
	set_bit(EV_SYN, ts_key->evbit);
	set_bit(EV_KEY, ts_key->evbit);
	set_bit(KEY_VOLUMEUP, ts_key->keybit);				//音量＋
	set_bit(KEY_VOLUMEDOWN, ts_key->keybit);		//音量-
	set_bit(KEY_HOME, ts_key->keybit);						//ホーム
	set_bit(KEY_BACK, ts_key->keybit);							//戻る
	set_bit(KEY_MENU, ts_key->keybit);						//メニュー
	ret = input_register_device(ts_key);
	if(ret) 
	{
		printk(KERN_ERR "==>: Unable to register %s input device\n", ts->input_dev->name);
		ret = -ENOMEM;
		goto L_end;
	}

	return 0;

//エラー終了
L_end:

	return ret;
}

//指定されたキーコードを送出する
static void rohm_ts_set_btn( int btn , int mode) {
	int key_code[5] = {KEY_VOLUMEUP,KEY_VOLUMEDOWN,KEY_HOME,KEY_BACK,KEY_MENU};		//送信キーコード

	input_event(ts_key, EV_KEY, key_code[btn], mode);
	input_sync(ts_key);
//	printk("Return Key Code:%2d Press:%2d\n",key_code[btn],mode );
}

//指定座標の位置にキーがあるか確認しキーコードを出力
static void rohm_ts_touchkey(int *px, int *py) {
	int key_xs[5] = {910,770,480,270,50};
	int key_xe[5] = {970,830,540,330,110 };
	int i;
	int j;
	int key_now_sts[5] = {0,0,0,0,0};

	for(i=0; i<2; i++) {
		py[i] = py[i] / 2;		//Y座標を半分に


		if ( py[i] <= 610 )		continue;	//ソフトキーの範囲外なので次へ

		for(j=0; j<5; j++) {	//押されている位置の確認
			if(( key_xs[j] <= px[i] ) && ( px[i] <= key_xe[j])) {
//-- Sanyo CE
//		printk("Get [%d ] Key:%d\n", i,j);
//-- Sanyo CE
				key_now_sts[j] = 1;	//キーが押された
				break;
			}
		}
	}

	for(i=0; i<5;i++) {
		if( key_sts[i] != key_now_sts[i] ) {					//キーの状態に変化あり
			rohm_ts_set_btn( i, key_now_sts[i] );		//ボタンを現在の状態に設定
			key_sts[i] = key_now_sts[i];						//現在の状態をセット
		}
	}

	return;

}



//取得座標がソフトキーかの確認
static void rohm_ts_touch_check() {
	int tpx[2];
	int tpy[2];
	int key_flg = 0;

	//1点目の座標
	tpx[0]=tp1.x;
	tpy[0]=tp1.y;

	//2点目の座標
	tpx[1]=tp2.x;
	tpy[1]=tp2.y;

	//タッチしたエリアがソフトキーエリアか
	//ソフトキーエリアならば、その座標をクリアする
	if( tp1.y >= ROHM_TS_ABS_Y_MAX ) {
		tp1.x = 0;
		tp1.y = 0;
		key_flg = 1;
	}

	if( tp2.y >= ROHM_TS_ABS_Y_MAX ) {
		tp2.x = 0;
		tp2.y = 0;
		key_flg = 1;
	}

//-- Sanyo CE
//	printk("Get Touch:TP1.x:%4d	TP1.y:%4d	TP2.x:%4d	TP2.y:%4d	Touch:%d\n", tp1.x, tp1.y,tp2.x,tp2.y,finger);
//-- Sanyo CE

	if(( tp1.x > 0 ) && ( tp1.y > 0 )) {
		if(( tp2.x > 0 ) && ( tp2.y > 0 )) {
			finger = 2;							//画面エリアに２点タッチあり
		} else {
			finger = 1;							//画面エリアに１点タッチあり
		}
	} else if(( tp2.x > 0 ) && ( tp2.y > 0 )) {
		finger = 1;								//画面エリアに１点タッチあり
		tp1.x = tp2.x;							//２点目の座標を１点目に移動
		tp1.y = tp2.y;
		tp2.x = 0;
		tp1.x = 0;
	} else {									//画面タッチなし
		if(( bf_finger == 1) || ( bf_finger == 2 )) {	//前回 １ or 2点タッチ
			finger = 0;							//画面タッチ解除
		} else if(key_flg==1) {		//１ or ２点キーのエリアをタッチしている
			finger = 3;							//画面タッチはなにもしない
		} else {
			finger = 4;							//画面タッチはなにもしない
		}
	}

//-- Sanyo CE
//	printk("Set Touch:TP1.x:%4d	TP1.y:%4d	TP2.x:%4d	TP2.y:%4d	Touch:%d\n", tp1.x, tp1.y,tp2.x,tp2.y,finger);
//-- Sanyo CE

	rohm_ts_touchkey(tpx,tpy);		//ソフトキーの変化を確認

}

//---- Sanyo CE タッチパネル上のソフトキーのイベントをあげる

static void rohm_ts_work_func(struct work_struct *work)
{
	//define ouput data start
	//unsigned int finger = 0 ;
	unsigned int touch = 0 ;
 	unsigned int gesture = 0 ;
	unsigned int report = 0;

 	//end of define data
	int ret;
	int bad_data = 0;
	struct i2c_msg msg[2];
	uint8_t buf[10];
	struct rohm_ts_data *ts = container_of(work, struct rohm_ts_data, work);

	int diff_x;
	int diff_y;
	int ofs_sub_x;
	int ofs_sub_y;
	int ofs_x_arry[8] = {0,50,60,70,80,90,100,100};

	if(ts->suspend == 1)
	{
		i2c_smbus_write_byte_data(ts->client, 0x3E, 0xFF);
		hrtimer_cancel(&ts->timer);
		return;
	}

	
//--- Sanyo CE
#ifdef TOUCH_CALIB
	rohm_ts_check_int();		//再キャリブレーション要求の確認
#endif
//--- Sanyo CE

	//1'nd data
	msg[0].addr = ts->client->addr;				//For BUMV21018MWV test only
	msg[0].flags = 0;
	msg[0].len = 1;
	msg[0].buf = buf;

	buf[0] = 0x20;  //I2C slave address

	msg[1].addr = ts->client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].len = sizeof(buf);
	msg[1].buf = buf;
	ret = i2c_transfer(ts->client->adapter, msg, 2);


	if (ret < 0) 
	{
		bad_data = 1;
		goto done;
	} 

	bad_data = 0;

	/*XY coordinate */
	tp1.x = buf[1] | ((uint16_t)buf[0] << 2); 
	tp1.y = buf[3] | ((uint16_t)buf[2] << 2);
	tp2.x = buf[5] | ((uint16_t)buf[4] << 2); 
	tp2.y = buf[7] | ((uint16_t)buf[6] << 2);

	touch = buf[8];
	gesture = buf[9];

//#ifdef SHOW_TOUCH_POINT		
//		if( bf_finger == 1)
//			printk("Get Touch:TP1.x:%4d	TP1.y:%4d	TP2.x:%4d	TP2.y:%4d	Touch:%d Gesture:%d\n", tp1.x, tp1.y,tp2.x,tp2.y,touch,gesture);
//#endif

	if( ( (tp1.y > 0) && (tp1.x > 0) ) && ( (tp2.y>0) && (tp2.x>0) ) )
	{

//------------ Sanyo CE
		finger = 2;
		if((tp1.x==tp1.y) && (tp2.x==tp2.y) && (tp1.x=tp2.x)) {
			goto Step1;
		}
		if( two_finger_cunt < (TWO_FINGER_NOP_MAX) ) {		
			//２点タッチ直後の座標データは無視する(値が安定しないため)
			two_finger_cunt++;
			goto Step1;
		} 

#ifdef SW_AVG	//５回取得した平均座標を使用する
		Coord_Avg(&tp1);
		Coord_Avg(&tp2);
		if( tp1.buff_cnt < SKIP_AVG_1 ) {	//平均値がでるまでは0となるので座標を無視する。
			goto Step1;
		}
		if( (tp1.x == 0) && (tp1.y==0) && (tp2.x==0) && (tp2.y==0)) goto Step1;
//		printk("Avg Touch:TP1.x:%4d	TP1.y:%4d	TP2.x:%4d	TP2.y:%4d\n", tp1.x, tp1.y,tp2.x,tp2.y);
#endif

		//座標移動量の比較用変数初期化。
		if( old_finger != 2 ) {
			x1_old = 0;
			y1_old = 0;
			x2_old = 0;
			y2_old = 0;
		}
			
		//２点間の距離を保存
		old_finger = 2;

		diff_x = abs(tp1.x - tp2.x);	//X軸方向の２点間の距離	
		diff_y = abs(tp1.y - tp2.y);	//Y軸方向の２点間の距離

//		ofs_sub_x = ofs_x_arry[ diff_x / 150];
//		ofs_sub_y = (200 * diff_y) / 850;
		if( diff_x < 300 ) {
			ofs_sub_x=0;
		} else {
			ofs_sub_x=70;
		}
		if(diff_y < 120 )
			ofs_sub_y=00;
		else if(diff_y < 170 )
			ofs_sub_y=10;
		else if(diff_y < 190 )
			ofs_sub_y=20;
		else if(diff_y < 210 )
			ofs_sub_y=30;
		else if(diff_y < 230 )
			ofs_sub_y=40;
		else if(diff_y < 250 )
			ofs_sub_y=50;
		else if(diff_y < 390 )
			ofs_sub_y=60;
		else if(diff_y < 500 )
			ofs_sub_y=70;
		else if(diff_y < 650 )
			ofs_sub_y=80;
		else
			ofs_sub_y=90;

		if( tp1.x < tp2.x ) {
			tp1.x += ofs_sub_x;
			tp2.x -= ofs_sub_x;
		} else if( tp1.x > tp2.x ) {
			tp1.x -= ofs_sub_x;
			tp2.x += ofs_sub_x;
		}

		if( tp1.y < tp2.y ) {
			tp1.y += ofs_sub_y;
			tp2.y -= ofs_sub_y;
		} else if ( tp1.y > tp2.y ) {
			tp1.y -= ofs_sub_y;
			tp2.y += ofs_sub_y;
		}
//		printk("\nofs Touch:TP1.x:%4d	TP1.y:%4d DIFX:%04d DIFY:%04d\n", ofs_sub_x,ofs_sub_y,diff_x,diff_y);
//		printk("of1 Touch:TP1.x:%4d	TP1.y:%4d	TP2.x:%4d	TP2.y:%4d\n", tp1.x, tp1.y,tp2.x,tp2.y);

		//移動量が少ないときは座標を変化させない
		if( (abs(tp1.x-x1_old) <= STEP_DIFF  )  && ( abs(tp1.y-y1_old) <= STEP_DIFF ) ){
				tp1.x = x1_old;
				tp1.y = y1_old;
		} else if( (abs(tp1.x-x1_old) > STEP_DIFF )  && ( abs(tp1.y-y1_old) <= STEP_DIFF ) ){
				tp1.y = y1_old;	
				x1_old = tp1.x;
		} else if( (abs(tp1.x-x1_old) <= STEP_DIFF  )  && ( abs(tp1.y-y1_old) > STEP_DIFF ) ){
			tp1.x = x1_old;
			y1_old = tp1.y;
		} else {
			x1_old = tp1.x;
			y1_old = tp1.y;
		}

		if( (abs(tp2.x-x2_old) <= STEP_DIFF  )  && ( abs(tp2.y-y2_old) <= STEP_DIFF ) ){
			tp2.x = x2_old;
			tp2.y = y2_old;
		} else if( (abs(tp2.x-x2_old) > STEP_DIFF )  && ( abs(tp2.y-y2_old) <= STEP_DIFF ) ){
			tp2.y = y2_old;	
			x2_old = tp2.x;
		} else if( (abs(tp2.x-x2_old) <= STEP_DIFF  )  && ( abs(tp2.y-y2_old) > STEP_DIFF ) ){
			tp2.x = x2_old;
			y2_old = tp2.y;
		} else {
			x2_old = tp2.x;
			y2_old = tp2.y;
		}

//		printk("DIF Touch:TP1.x:%4d	TP1.y:%4d	TP2.x:%4d	TP2.y:%4d\n", tp1.x, tp1.y,tp2.x,tp2.y);

//------------ Sanyo CE

	} else if ( ( (tp1.y>0)&&(tp1.x>0) ) || ( (tp2.y>0)&& (tp2.x>0) ) ) {

		if(( old_finger == 2) && (  two_one_finger <= ONE_FINGER_NOP_MAX )) {		
			// 前回２点タッチの場合には、10ポイント分のデータを無視する(指が移動中に瞬間離れた場合があるため)
			two_one_finger ++;
			goto Step1;
		}

//--- Sanyo CE
		old_finger = 1;
//--- Sanyo CE

		if((tp2.x != 0) && (tp2.y != 0)) {
			tp1.x = tp2.x;
			tp1.y = tp2.y;
			tp2.x = 0;
			tp2.y = 0;
		}

		finger = 1;
	} else {	
		finger = 0;	
		error_flg_1 = 0;
		error_flg_2 = 0;
		finger_count_0 = 0;
		finger_count_1 = 0;
		finger_count_2 = 0;
//--- Sanyo CE
#ifdef SW_AVG	
		Coord_Avg(&tp1);
		Coord_Avg(&tp2);
#endif
		old_finger = 0;
//--- Sanyo CE
	}

//#ifdef SHOW_TOUCH_POINT		
//		printk("Touch:TP1.x:%d	TP1.y:%d	TP2.x:%d	TP2.y:%d	Touch:%d\n", tp1.x, tp1.y,tp2.x,tp2.y,finger);
//#endif
//--- Sanyo CE
	if (!ts->use_irq) {
		if( (bf_finger ==0) && ( finger==0) )  goto Step1;
	}

	Calib_Calc(&tp1);		//タッチポイント１の座標をキャリブレーション
	Calib_Calc(&tp2);		//タッチポイント２の座標をキャリブレーション


//-- Sanyo CE

	rohm_ts_touch_check();	//ソフトキーの更新処理
//---- Sanyo CE
	if(( tp1.x < 0 ) || (tp1.y < 0)) goto Step1;     //座標が負の時はあげない
	if(( tp2.x < 0 ) || (tp2.y < 0)) goto Step1;		//変換座標が負の時は上げない
	if( tp1.x >= 0x8000 ) goto Step1;     //座標が負の時はあげない
	if( tp2.x >= 0x8000 ) goto Step1;		//変換座標が負の時は上げない
//---- Sanyo CE

	if(finger == 0)
	{
		input_report_abs(ts->input_dev, ABS_MT_TOUCH_MAJOR, 0);
		input_report_abs(ts->input_dev, ABS_TOOL_WIDTH, 0); // 0 touch_width,File system do judge this register

		input_report_key(ts->input_dev, BTN_TOUCH, finger);  // finger  num   0, 1, 2
		input_report_key(ts->input_dev, BTN_2, finger > 1); // finger2 state 0, 0, 1
		report = 0;
		input_sync(ts->input_dev);   // up load data
		key_count = 0;
	} else if (finger == 1) {
		input_report_abs(ts->input_dev, ABS_MT_TOUCH_MAJOR, 3);	
		input_report_abs(ts->input_dev, ABS_MT_POSITION_X, tp1.x);
		input_report_abs(ts->input_dev, ABS_MT_POSITION_Y, tp1.y);
		input_mt_sync(ts->input_dev);

		input_report_abs(ts->input_dev, ABS_TOOL_WIDTH, 0); // 0 touch_width,File system do judge this register
		input_report_key(ts->input_dev, BTN_TOUCH, finger);  // finger  num   0, 1, 2
		input_report_key(ts->input_dev, BTN_2, finger > 1); // finger2 state 0, 0, 1
		input_sync(ts->input_dev);   // up load data  
		report = 1;  
	} else if(finger == 2) {
		input_report_abs(ts->input_dev, ABS_MT_TOUCH_MAJOR, 3);	
		input_report_abs(ts->input_dev, ABS_MT_POSITION_X, tp1.x);
		input_report_abs(ts->input_dev, ABS_MT_POSITION_Y, tp1.y);
		input_mt_sync(ts->input_dev);
		input_report_abs(ts->input_dev, ABS_MT_TOUCH_MAJOR, 3);
		input_report_abs(ts->input_dev, ABS_MT_POSITION_X, tp2.x);
		input_report_abs(ts->input_dev, ABS_MT_POSITION_Y, tp2.y);
		input_mt_sync(ts->input_dev);

		input_report_abs(ts->input_dev, ABS_TOOL_WIDTH, 0); // 0 touch_width,File system do judge this register
		input_report_key(ts->input_dev, BTN_TOUCH, finger);  // finger  num   0, 1, 2
		input_report_key(ts->input_dev, BTN_2, finger > 1); // finger2 state 0, 0, 1
		input_sync(ts->input_dev);   // up load data   
		report = 2;					   
	} else if( finger == 4 ) {	//キーがリリースされた
		finger = 0;
	}

//#ifdef SHOW_TOUCH_POINT		
//		printk("Up  Touch:TP1.x:%4d	TP1.y:%4d	TP2.x:%4d	TP2.y:%4d	Touch:%d\n\n", tp1.x, tp1.y,tp2.x,tp2.y,finger);
//#endif

	//=== Sanyo CE
Step1:
	if( finger != 2 )	two_finger_cunt = 0;
	if( old_finger != 2)	two_one_finger = 0; 		
	bf_finger = finger;
	//=== Sanyo CE




	if (finger)
	{
//--- Sanyo CE
#if 0
			hrtimer_start(&ts->timer, ktime_set(0, TIMER_NS), HRTIMER_MODE_REL);			
				//report rate 1/10000000=100Hz
#else
			if( old_finger != 2 ) {
				hrtimer_start(&ts->timer, ktime_set(0, TIMER_NS), HRTIMER_MODE_REL);		
				//report rate 1/10000000=100Hz
			} else {
				hrtimer_start(&ts->timer, ktime_set(0, TIMER_NS1), HRTIMER_MODE_REL);		
				//report rate 1/10000000=100Hz
			}
#endif
//--- Sanyo CE
	} else {
//-- Sanyo CE
#if 0
	// Clear all Interrupt
		i2c_smbus_write_byte_data(ts->client, 0x3E, 0xFF);
		hrtimer_cancel(&ts->timer);

#else
		i2c_smbus_write_byte_data(ts->client, 0x3E, 0xFF);
		if (!ts->use_irq) 
		{
			if(TP_XY_GET == 1)
				hrtimer_start(&ts->timer, ktime_set(0, TIMER_NS), HRTIMER_MODE_REL);			//report rate 1/10000000=100Hz
			else
				hrtimer_cancel(&ts->timer);
		} else {
			hrtimer_cancel(&ts->timer);
		}

//-- Sanyo CE

//-- Sanyo CE
#if 0
		if (ts->use_irq)
			enable_irq(ts->client->irq);
#endif
//-- Sanyo CE
	}
#endif
	return;
done:
	;

}

static enum hrtimer_restart rohm_ts_timer_func(struct hrtimer *timer)
{
	struct rohm_ts_data *ts = container_of(timer, struct rohm_ts_data, timer);
	queue_work(rohm_wq, &ts->work);
	//hrtimer_start(&ts->timer, ktime_set(0, TIMER_NS), HRTIMER_MODE_REL);			//report rate 1/12500000=80Hz
	return HRTIMER_NORESTART;
}

static irqreturn_t rohm_ts_irq_handler(int irq, void *dev_id)
{
	struct rohm_ts_data *ts = dev_id;

//	printk("Rohm_ts_irq_handler irq:%d\n",ts->client->irq); 
//--- Sanyo CE
#if 0
	disable_irq(ts->client->irq);
	queue_work(rohm_wq, &ts->work);
#else
	queue_work(rohm_wq, &ts->work);
#endif
//---- Sanyo CE
#ifdef SHOW_DEBUG
//	printk("Rohm_ts_irq_handler End\n"); 
#endif
//---- Sanyo CE
	return IRQ_HANDLED;
}

#ifdef CONFIG_PM
static int rohm_ts_suspend(struct i2c_client *client, pm_message_t state)
{
	int i;

	printk(KERN_ERR "ROHM BU21023 rohm_ts_suspend Wake Down!!!\n");

	ts->suspend = 1;

	i2c_smbus_write_byte_data(client, 0x40, 0x01);	//SYSTEN X_SLP_POW:ON X_SLP_CPU:OFF  待機状態2へ

	for( i = 0; i < 30; i++ )
		{ udelay(1000 ); }

	i2c_smbus_write_byte_data(client, 0x40, 0x00);	//SYSTEN X_SLP_POW:ON X_SLP_CPU:OFF  待機状態1へ
	return 0;
}

static int rohm_ts_resume(struct i2c_client *client)
{
	int i;

	i2c_smbus_write_byte_data(client, 0x40, 0x01);	//SYSTEN X_SLP_POW:ON X_SLP_CPU:OFF  待機状態2へ

	for( i = 0; i < 30; i++ )
		{ udelay(1000 ); }

	i2c_smbus_write_byte_data(client, 0x40, 0x03);	//SYSTEN X_SLP_POW:ON X_SLP_CPU:ON センシング状態へ

	ts->suspend = 0;

	printk(KERN_ERR "ROHM BU21023 rohm_ts_resume Wake Up!!!\n");
	
	return 0;
}
#else
#define rohm_ts_suspend NULL
#define rohm_ts_resume  NULL
#endif

static int rohm_ts_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
//-- Sanyo CE
//	struct rohm_ts_data *ts;
//-- Sanyo CE
	int ret = 0;
	struct ROHM_I2C_platform_data *pdata;
	int i;
	int offset = 0;
	int block;
	int bytes;


#ifdef SHOW_DEBUG
	printk(KERN_ERR "ROHM BU21023 rohm_ts_probe!!\n");
#endif
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) 
	{
		printk(KERN_ERR "Rohm_ts_probe: need I2C_FUNC_I2C\n");
		ret = -ENODEV;
		goto err_check_functionality_failed;
	}

	ts = kzalloc(sizeof(*ts), GFP_KERNEL);
	if (ts == NULL) 
	{
		ret = -ENOMEM;
		goto err_alloc_data_failed;
	}
	INIT_WORK(&ts->work, rohm_ts_work_func);
	ts->client = client;
	i2c_set_clientdata(client, ts);
	pdata = client->dev.platform_data;
	if (pdata)
		ts->power = pdata->power;
	if (ts->power) 
	{
		ret = ts->power(1);
		if (ret < 0) 
		{
			printk(KERN_ERR "Rohm_ts_probe power on failed\n");
			goto err_power_failed;
		}
	}
	ts->suspend = 0;
	//end of default setting

	//Download 



	////////////////////////////////////////////////////////////////////////
	// Init BU21023
	////////////////////////////////////////////////////////////////////////
	// Wait 200usec for Reset
	udelay(200);

//---- Sanyo CE パワーONシーケンスに準ずるために追加
	//analog power on
	i2c_smbus_write_byte_data(ts->client, 0x40, 0x01);	//SYSTEN X_SLP_POW:ON

	// Wait 200msec for Reset
	udelay(200);

	// Clear all Interrupt
 	  i2c_smbus_write_byte_data(ts->client, 0x3D, 0xFE);		//INT_MASK
	  i2c_smbus_write_byte_data(ts->client, 0x3E, 0xFF);		//INT_CLR
//---- Sanyo CE パワーONシーケンスに準ずるために追加


#ifdef TOUCH_SCREEN_SETTING
	//common setting 
	i2c_smbus_write_byte_data(ts->client, 0x30, 0x4E);	//CMN_SETUP1  
	i2c_smbus_write_byte_data(ts->client, 0x31, 0x00);	//CMN_SETUP2
//	i2c_smbus_write_byte_data(ts->client, 0x32, 0x43);	//CMN_SETUP3		0x43->disable INTVL	 enable->MULTI  enable->SLEEP
	i2c_smbus_write_byte_data(ts->client, 0x32, 0x42);	//CMN_SETUP3		0x42->disable INTVL	 enable->MULTI  disable->SLEEP
//	i2c_smbus_write_byte_data(ts->client, 0x32, 0x48);	//CMN_SETUP3		0x49->enable INTVL	disable->MULTI  disable->SLEEP
//	i2c_smbus_write_byte_data(ts->client, 0x32, 0x49);	//CMN_SETUP3		0x49->enable INTVL	disable->MULTI  enable->SLEEP
//	i2c_smbus_write_byte_data(ts->client, 0x32, 0x4B);	//CMN_SETUP3		0x4B->enable INTVL	 enable->MULTI  enable->SLEEP
	//timing setting
	i2c_smbus_write_byte_data(ts->client,  0x33, 0x00);	//INTVL_TIME	0x00->sample period 10ms	
	i2c_smbus_write_byte_data(ts->client,  0x50, 0x00);	//PRM_CPU_FREQ
	i2c_smbus_write_byte_data(ts->client,  0x60, 0x08);	//PRM_AD_CTRL
	i2c_smbus_write_byte_data(ts->client,  0x61, 0x0A);	//PRM_WAIT_AD
	i2c_smbus_write_byte_data(ts->client,  0x57, 0xF0);	//PRM_SWOFF_TIME
	//panel setting
//	i2c_smbus_write_byte_data(ts->client,  0x63, 0x0C);	//EVR_X
//	i2c_smbus_write_byte_data(ts->client,  0x64, 0x0C);	//EVR_Y
	i2c_smbus_write_byte_data(ts->client,  0x63, 0x10);	//EVR_X
	i2c_smbus_write_byte_data(ts->client,  0x64, 0x08);	//EVR_Y
	i2c_smbus_write_byte_data(ts->client,  0x34, 0x7F);	//STEP_X	
	i2c_smbus_write_byte_data(ts->client,  0x35, 0x7F);	//STEP_Y
	i2c_smbus_write_byte_data(ts->client,  0x3A, 0x70);	///TH_DET_TOUCH
	i2c_smbus_write_byte_data(ts->client,  0x3B, 0x16);	//TH_DET_GESTURE
	i2c_smbus_write_byte_data(ts->client,  0x38, 0x04);	//OFS_X
	i2c_smbus_write_byte_data(ts->client,  0x39, 0x04);	//OFS_Y
	i2c_smbus_write_byte_data(ts->client,  0x68, 0x00);	//CALIB_REG1
	i2c_smbus_write_byte_data(ts->client,  0x69, 0x00);	//CALIB_REG2
	i2c_smbus_write_byte_data(ts->client,  0x6A, 0x00);	//CALIB_REG3
	i2c_smbus_write_byte_data(ts->client,  0x53, 0xFF);	//TH_SLEEP_IN

	//fixed value setting
	i2c_smbus_write_byte_data(ts->client,  0x52, 0x00);	//PRM_B_OFS
//-- 設定値を元に戻す
	i2c_smbus_write_byte_data(ts->client,  0x56, 0xF0);	//EVR_XY
//---	i2c_smbus_write_byte_data(ts->client,  0x56, 0x08);	//EVR_XY
	i2c_smbus_write_byte_data(ts->client,  0x62, 0x0F);	//SWCONT
	i2c_smbus_write_byte_data(ts->client,  0x65, 0x01);	//TEST1
#endif

	//analog power on
	i2c_smbus_write_byte_data(ts->client, 0x40, 0x01);	//SYSTEN X_SLP_POW:ON

	// Wait 100usec for Power-on
	udelay(100);

	// Beginning address setting of program memory for host download

	i2c_smbus_write_byte_data(ts->client, 0x70, 0x00);
	i2c_smbus_write_byte_data(ts->client, 0x71, 0x00);

#ifdef SHOW_DEBUG
	// Download firmware to BU21020
	printk("BU21023 firmware download starts!\n");
#endif

	block = CODESIZE / 32;
	bytes = CODESIZE % 32;
	
	for(i = 0; i < block; i++)
	{
		offset = i * 32;
		i2c_smbus_write_i2c_block_data(ts->client, 0x72, 32, &program[offset]);
	}

	offset = block * 32;
	for(i = 0; i < bytes; i++)
	{
		i2c_smbus_write_byte_data(ts->client, 0x72, program[offset + i]);
	}

#ifdef SHOW_DEBUG
	printk("BU21023 firmware download is completed!\n");
	// Download path setting
#endif

	i2c_smbus_write_byte_data(ts->client, 0x3E, 0xFF);		//INT_CLR

	// Coordinate Offset, MAF, CAF
//-- Sanyo CE
//	i2c_smbus_write_byte_data(ts->client,  0x60, 0x04);
//-- Sanyo CE
	  //i2c_smbus_write_byte_data(ts->client,  0x3B, 0x01);//disable CAF
	  //i2c_smbus_write_byte_data(ts->client,  0x3B, 0x09);//disable CAF, MAF in single touch
	  //i2c_smbus_write_byte_data(ts->client,  0x3B, 0x07);//enable CAF and offset

//--Sanyo CE---- キャリブレーションした結果を反映
#if 1
	i2c_smbus_write_byte_data(ts->client, 0x31, 0x0C);	//CMN_SETUP2
	i2c_smbus_write_byte_data(ts->client, 0x34, 0x91);	//STEP_X	
	i2c_smbus_write_byte_data(ts->client, 0x35, 0x58);	//STEP_Y
	i2c_smbus_write_byte_data(ts->client, 0x38, 0x08);	//OFS_X
	i2c_smbus_write_byte_data(ts->client, 0x39, 0x0C);	//OFS_Y
	i2c_smbus_write_byte_data(ts->client, 0x3A, 0x8A);	///TH_DET_TOUCH
	i2c_smbus_write_byte_data(ts->client, 0x63, 0xE2);	//EVR_X
	i2c_smbus_write_byte_data(ts->client, 0x64, 0xD6);	//EVR_Y
	i2c_smbus_write_byte_data(ts->client, 0x68, 0x3A);	//CALIB_REG1
	i2c_smbus_write_byte_data(ts->client, 0x69, 0x50);	//CALIB_REG2
	i2c_smbus_write_byte_data(ts->client, 0x6A, 0x6F);	//CALIB_REG3
#endif
//--Sanyo CE---- キャリブレーションした結果を反映

//---- Sanyo CE パワーONシーケンスに準ずるために追加
	// Wait 100usec
	udelay(100);

	// Clear all Interrupt
 	  i2c_smbus_write_byte_data(ts->client, 0x3D, 0xFE);		//INT_MASK
	  i2c_smbus_write_byte_data(ts->client, 0x3E, 0xFF);		//INT_CLR
//---- Sanyo CE パワーONシーケンスに準ずるために追加

	// CPU power on
	  i2c_smbus_write_byte_data(ts->client, 0x40, 0x03);	//SYSTEN X_SLP_POW:ON X_SLP_CPU:ON

	// Clear all Interrupt
 	  i2c_smbus_write_byte_data(ts->client, 0x3D, 0xFE);		//INT_MASK
#ifdef SHOW_DEBUG
	  printk("BU21023 reg0x2A = 0x%x\n",i2c_smbus_read_byte_data(ts->client, 0x2A));
#endif
	  i2c_smbus_write_byte_data(ts->client, 0x3E, 0xFF);		//INT_CLR

	for (i=0;i<30;i++)		//Wait 30mse
	{udelay(1000);}

#ifdef SHOW_DEBUG
	//check Error 
 	printk("BU21023 reg0x2B = 0x%x\n",i2c_smbus_read_byte_data(ts->client, 0x2B));
	printk("BU21023 reg0x31 = 0x%x\n",i2c_smbus_read_byte_data(ts->client, 0x31));

	//check Panel Setting
 	printk("BU21023 reg0x63 = 0x%x\n",i2c_smbus_read_byte_data(ts->client, 0x63));
	printk("BU21023 reg0x64 = 0x%x\n",i2c_smbus_read_byte_data(ts->client, 0x64));
	printk("BU21023 reg0x34 = 0x%x\n",i2c_smbus_read_byte_data(ts->client, 0x34));
	printk("BU21023 reg0x35 = 0x%x\n",i2c_smbus_read_byte_data(ts->client, 0x35));
	printk("BU21023 reg0x36 = 0x%x\n",i2c_smbus_read_byte_data(ts->client, 0x36));
	printk("BU21023 reg0x37 = 0x%x\n\n",i2c_smbus_read_byte_data(ts->client, 0x37));

	//check Touch Threshold
 	printk("BU21023 reg0x18 = 0x%x\n",i2c_smbus_read_byte_data(ts->client, 0x18));
	printk("BU21023 reg0x3A = 0x%x\n",i2c_smbus_read_byte_data(ts->client, 0x3A));
	printk("BU21023 reg0x56 = 0x%x\n\n",i2c_smbus_read_byte_data(ts->client, 0x56));

	//check DAC
	printk("BU21023 reg0x65 = 0x%x\n",i2c_smbus_read_byte_data(ts->client, 0x65));
	printk("BU21023 reg0x6B = 0x%x\n",i2c_smbus_read_byte_data(ts->client, 0x6B));
	printk("BU21023 reg0x6C = 0x%x\n\n",i2c_smbus_read_byte_data(ts->client, 0x6C));	
#endif
// 	i2c_smbus_write_byte_data(ts->client,  0x65, 0x11);
//	printk("BU21023 reg0x65 = 0x%x\n",i2c_smbus_read_byte_data(ts->client, 0x65));
//	printk("BU21023 reg0x6B = 0x%x\n",i2c_smbus_read_byte_data(ts->client, 0x6B));
//	printk("BU21023 reg0x6C = 0x%x\n\n",i2c_smbus_read_byte_data(ts->client, 0x6C));
 	i2c_smbus_write_byte_data(ts->client,  0x65, 0x01);



#ifdef SHOW_DEBUG
	// Clear all Interrupt
 	printk("BU21023 reg0x2A = 0x%x\n",i2c_smbus_read_byte_data(ts->client, 0x2A));
#endif

	i2c_smbus_write_byte_data(ts->client, 0x3E, 0xFF);
	// Init end
	////////////////////////////////////////////////////////////////////////


	ts->input_dev = input_allocate_device();
	if (ts->input_dev == NULL) 
	{
		ret = -ENOMEM;
		printk(KERN_ERR "Rohm_ts_probe: Failed to allocate input device\n");
		goto err_input_dev_alloc_failed;
	}
	ts->input_dev->name = "Rohm-CTP-BU21023GUL";
	set_bit(EV_SYN, ts->input_dev->evbit);
	set_bit(EV_KEY, ts->input_dev->evbit);
	set_bit(KEY_EXIT, ts->input_dev->keybit);
	set_bit(BTN_TOUCH, ts->input_dev->keybit);
	set_bit(BTN_2, ts->input_dev->keybit);
	set_bit(EV_ABS, ts->input_dev->evbit);
#ifdef SHOW_DEBUG
	printk("Rohm_ts_probe: --------------------setting ready\n");
#endif

	////////////////////////////////////////////////////////////////////////////
	input_set_abs_params(ts->input_dev, ABS_MT_POSITION_X, ROHM_TS_ABS_X_MIN, ROHM_TS_ABS_X_MAX, 0, 0);
	input_set_abs_params(ts->input_dev, ABS_MT_POSITION_Y, ROHM_TS_ABS_Y_MIN, ROHM_TS_ABS_Y_MAX, 0, 0);
	input_set_abs_params(ts->input_dev, ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0);
//	input_set_abs_params(ts->input_dev, ABS_MT_WIDTH_MAJOR, 0, 15, 0, 0);
	////////////////////////////////////////////////////////////////////////////

	input_set_abs_params(ts->input_dev, ABS_X,ROHM_TS_ABS_X_MIN, ROHM_TS_ABS_X_MAX, 0, 0);
	input_set_abs_params(ts->input_dev, ABS_Y,ROHM_TS_ABS_Y_MIN, ROHM_TS_ABS_Y_MAX, 0, 0);
	input_set_abs_params(ts->input_dev, ABS_PRESSURE, 0, 1550, 0, 0);  //1550  two point
	input_set_abs_params(ts->input_dev, ABS_TOOL_WIDTH, 0, 15, 0, 0); 	//15   two point
	input_set_abs_params(ts->input_dev, ABS_HAT0X, ROHM_TS_ABS_X_MIN, ROHM_TS_ABS_X_MAX, 0, 0);
	input_set_abs_params(ts->input_dev, ABS_HAT0Y, ROHM_TS_ABS_Y_MIN, ROHM_TS_ABS_Y_MAX, 0, 0);

	ret = input_register_device(ts->input_dev);
	if(ret) 
	{
		printk(KERN_ERR "==>: Unable to register %s input device\n", ts->input_dev->name);
		goto err_input_register_device_failed;
	}

//--- Sanyo CE
	if( keyfile_open( ) < 0 )		//ソフトキー用デバイスファイルOPEN
	{
		goto err_input_register_device_failed;
	}
//--- Sanyo CE

	if(client->irq) 
	{
		//ret = request_irq(client->irq, rohm_ts_irq_handler, IRQF_TRIGGER_LOW, client->name, ts);  	
		ret = request_irq(client->irq, rohm_ts_irq_handler, IRQF_TRIGGER_FALLING, client->name, ts);  	
		//Trigger status used IRQF_TRIGGER_FALLING ; ref \linux\interrupt.h
		// IRQF_TRIGGER_NONE	
		// IRQF_TRIGGER_RISING	
		// IRQF_TRIGGER_FALLING	
		// IRQF_TRIGGER_HIGH
		// IRQF_TRIGGER_LOW
		// IRQF_TRIGGER_PROBE
		/////////////////////////////

		printk("Request IRQ:%d Failed==>ret : %d\n", client->irq,ret);
		if (ret == 0) 
		{
			ts->use_irq = 1;	//1 : interrupt mode/0 : polling mode
		//free_irq(client->irq, ts);
		}
		else 
		{
			ts->use_irq = 0;	//1 set 1 : interrupt mode/0 : polling mode
			//dev_err(&client->dev, "request_irq failed\n");
		}	
	}
//--- Sanyo CE
#if 0
	if (!ts->use_irq) 
	{
		hrtimer_init(&ts->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
		ts->timer.function = rohm_ts_timer_func;
		hrtimer_start(&ts->timer, ktime_set(1, 0), HRTIMER_MODE_REL);
	} 
		//timer init
	hrtimer_init(&ts->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	ts->timer.function = rohm_ts_timer_func;
#else
	if (!ts->use_irq) 
	{
		hrtimer_init(&ts->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
		ts->timer.function = rohm_ts_timer_func;
		hrtimer_start(&ts->timer, ktime_set(1, 0), HRTIMER_MODE_REL);
		TP_XY_GET = 1;
	} else {
		//timer init
		hrtimer_init(&ts->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
		ts->timer.function = rohm_ts_timer_func;
		TP_XY_GET = 0;
	}

#endif
//--- Sanyo CE

	printk(KERN_INFO "Rohm ==>:Touchscreen Up %s in %s mode\n", ts->input_dev->name, ts->use_irq ? "interrupt" : "polling");

	return 0;

err_input_register_device_failed:
	input_free_device(ts->input_dev);

err_input_dev_alloc_failed:
	//err_detect_failed:
err_power_failed:
	kfree(ts);
err_alloc_data_failed:
err_check_functionality_failed:
	return ret;
}

static int rohm_ts_remove(struct i2c_client *client)
{
	struct rohm_ts_data *ts = i2c_get_clientdata(client);
	if (ts->use_irq)
		free_irq(client->irq, ts);
	else
		hrtimer_cancel(&ts->timer);
	input_unregister_device(ts->input_dev);
	kfree(ts);
	return 0;
}

//--- Sanyo CE Add
static int rohm_ts_ioctl(struct file *file, unsigned int cmd, void *arg)
{
	int 		ret = 0;
	u8		*buf = arg;
	int		*ibuf = arg;
	s32		result=0;	
	struct i2c_client *client = ts->client;
	int i;
	
#ifdef SHOW_REG
	printk("rohm_ts_command() Call\n");
#endif


	switch( cmd ) {
		case CMD_REG_BYTE_READ:
			if( buf[0] > 0x80 ) {		/* Invalid argument */
#ifdef SHOW_REG
			printk("Invalid Register Address :0x%02x\n",buf[0]);
#endif
				ret = -EINVAL;
				goto ioctl_end;
			}

#ifdef SHOW_REG
				printk("Commnd:BYTE Read Reg:0x%02x\n",buf[0]);
#endif
			if((result = i2c_smbus_read_byte_data(client, buf[0])) < 0 ) 
				ret = result;
			else {
				buf[0] = result;
#ifdef SHOW_REG
				printk("Commnd:BYTE Read Value:0x%02x\n",buf[0]);
#endif
			}
			break;

		case CMD_REG_WRITE:
			if((buf[0] < 0x30) || (buf[0] > 0x72) ) {		/* Invalid argument */
#ifdef SHOW_REG
				printk("Write Command Invalid Register Address :0x%02x\n",buf[0]);
#endif
				ret = -EINVAL;
				goto ioctl_end;
			}
#ifdef SHOW_REG
			printk("Commnd:Write Reg:0x%02x Value:0x%02x\n",buf[0],buf[1]);
#endif	
			if( (result = i2c_smbus_write_byte_data(client, buf[0], buf[1])) < 0 )
				ret = result;
			break;

		case CMD_IRQ_DISABLE:
#ifdef SHOW_REG
			printk("Commnd:disable_irq Set Start!!\n");
#endif
			if (ts->use_irq) {
				disable_irq(ts->client->irq);			//割り込み禁止
 	 			 i2c_smbus_write_byte_data(ts->client, 0x3D, 0xFF);
			} else {
				TP_XY_GET = 0;
				hrtimer_cancel(&ts->timer);			//タイマー停止
			}
#ifdef SHOW_REG
			printk("Commnd:disable_irq Set End!!\n");
#endif
			break;

		case CMD_IRQ_ENABLE:
#ifdef SHOW_REG
			printk("Commnd:enable_irq Set Start\n");
#endif
			if (ts->use_irq) {
 				enable_irq(ts->client->irq);			//割り込み有効
 	 	 		i2c_smbus_write_byte_data(ts->client, 0x3D, 0xFE);
			} else {
				hrtimer_start(&ts->timer, ktime_set(1, 0), HRTIMER_MODE_REL);	//タイマー開始
				TP_XY_GET = 1;
			}
			i2c_smbus_write_byte_data(ts->client, 0x3E, 0xFF);
#ifdef SHOW_REG
			printk("Commnd:enable_irq Set End\n");
#endif
			break;

		case CMD_PRM_WRITE:
#ifdef SHOW_REG
				printk("Commnd:Parm Write\n");
#endif
				for( i=0;  i<9; i++) {
					calibration[i] = ibuf[i];
				}
#ifdef SHOW_REG
				for( i=0;  i<9; i++) {
					printk("Commnd:Parm Write i:%d param src: %d dis:%d\n",i,ibuf[i],calibration[i] );
				}
#endif

			break;

		case CMD_PRM_READ:
#ifdef SHOW_REG
				printk("Commnd:Parm Read\n");
#endif
			for( i=0;  i<9; i++) {
				ibuf[i] = calibration[i];
			}
			break;

		default:
			ret = -EIO;				//
	}

ioctl_end:
#ifdef SHOW_REG
	printk("rohm_ts_command() Call End Return Status:%d\n",ret);
#endif
	return ret;
}

static const struct file_operations ts_fops = {
	.owner					= THIS_MODULE,
	.unlocked_ioctl	= rohm_ts_ioctl,
};
//--- Sanyo CE Add

static const struct i2c_device_id rohm_ts_id[] = 
{
	{ ROHM_I2C_NAME, 0 },
	{ }
};

static struct i2c_driver rohm_ts_driver = 
{
	.probe		= rohm_ts_probe,
	.remove		= rohm_ts_remove,
	.suspend	= rohm_ts_suspend,
	.resume		= rohm_ts_resume,
	.id_table	= rohm_ts_id,
	.driver = {
		.name	= ROHM_I2C_NAME,
	},
};

static struct class *ts_dev_class;

static int __devinit rohm_ts_init(void)
{
#if 0
	printk("ROHM BU21018 rohm_ts_init \n");
	rohm_wq = create_singlethread_workqueue("rohm_wq");
	if (!rohm_wq)
	{
		printk( "BU21018 create_singlethread_workqueue ERROR!!\n");
		return -ENOMEM;
	}	
	return i2c_add_driver(&rohm_ts_driver);
#else
	int res;

#ifdef SHOW_DEBUG
	printk("ROHM BU21018 rohm_ts_init \n");
#endif

	TS_MAJOR = register_chrdev(0, TS_NAME, &ts_fops);
	if (TS_MAJOR<0) {
		printk(KERN_ERR "%s: Driver Initialisation failed\n", __FILE__);
		res = TS_MAJOR;
		goto out;
	}

	printk("/dev/mts  MAJOR:%d\n",TS_MAJOR);

	ts_dev_class = class_create(THIS_MODULE, "ts-dev");
	if (IS_ERR(ts_dev_class)) {
		res = PTR_ERR(ts_dev_class);
		goto out_unreg_chrdev;
	}

	/* register this i2c device with the driver core */
	if( device_create(ts_dev_class, NULL,
					 MKDEV(TS_MAJOR, 0), NULL, "mts") == NULL ) {
		res = -1;
		goto out_unreg_class; ;
	}





	rohm_wq = create_singlethread_workqueue("rohm_wq");
	if (!rohm_wq)
	{
		printk( "BU21018 create_singlethread_workqueue ERROR!!\n");
		res = -ENOMEM;
		goto out_destroy;
	}

	if( (res = i2c_add_driver(&rohm_ts_driver)) < 0 ) goto out_destroy; 

	printk("ROHM BU21018 rohm_ts_init Success \n");
	return res;

out_destroy:
	device_destroy(ts_dev_class, MKDEV(TS_MAJOR, 0));

out_unreg_class:
	class_destroy(ts_dev_class);
out_unreg_chrdev:
	unregister_chrdev(TS_MAJOR, TS_NAME);
out:
	printk("ROHM BU21018 rohm_ts_init Fail \n");
	return res;
#endif
}

static void __exit rohm_ts_exit(void)
{
	i2c_del_driver(&rohm_ts_driver);
	if (rohm_wq)
		destroy_workqueue(rohm_wq);
//--- Sanyo CE
	class_destroy(ts_dev_class);
	unregister_chrdev(TS_MAJOR, TS_NAME);
//--- Sanyo CE
}

module_init(rohm_ts_init);
module_exit(rohm_ts_exit);

MODULE_DESCRIPTION("Rohm Touchscreen Driver");
MODULE_LICENSE("GPL");

