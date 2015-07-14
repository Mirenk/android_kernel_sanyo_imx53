/*
 * Copyright(c) 2009 Dialog Semiconductor Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * da9052-i2c.c: I2C SSC (Synchronous Serial Communication) driver for DA9052
 */

#include <linux/device.h>
#include <linux/mfd/core.h>
#include <linux/i2c.h>
#include <linux/mfd/da9052/da9052.h>
#include <linux/mfd/da9052/reg.h>

#include <linux/semaphore.h>

#ifdef CONFIG_MACH_MX53_BEJ2
extern int da9052_regulator_flag;
extern int get_bej2_suspend_state(void);
#define BEJ2_DA9052_I2C_SUSPENDSTATUS_ERR	222
#endif

static struct da9052 *da9052_i2c;

static struct mutex i2c_lock;

static int shutdown;

#define I2C_CONNECTED 0

#define I2C_BUG_WORKAROUND
//#define BEJ2_I2C_SUSPEND_STATE_LOG

static int da9052_i2c_is_connected(void)
{

        struct da9052_ssc_msg msg;
	int retries = 5, ret = 0;

        //printk("Entered da9052_i2c_is_connected.............\n");

        msg.addr = DA9052_INTERFACE_REG;
	/* Retries added fro Customer !! */
	do {
		 /* Test spi connectivity by performing read of the GPIO_0-1 register */
	        if ( 0 != da9052_i2c_read(da9052_i2c, &msg)) {
                	printk("da9052_i2c_is_connected - i2c read failed.............\n");
                	ret = -1;
       		 }
        	else {
               		printk("da9052_i2c_is_connected - i2c read success..............\n");
                	ret = 0;
        	}
		
	} while (ret != 0 && retries--);

/*
       
        if ( 0 != da9052_i2c_read(da9052_i2c, &msg)) {
                printk("da9052_i2c_is_connected - i2c read failed.............\n");
                return -1;
        }
        else {
               printk("da9052_i2c_is_connected - i2c read success..............\n");
                return 0;
        }
*/
	return ret;
}

static int __devinit da9052_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter;
 	// printk("\n\tEntered da9052_i2c_is_probe.............\n");

	mutex_init(&i2c_lock);
	shutdown = 0;
        da9052_i2c = kzalloc(sizeof(struct da9052), GFP_KERNEL);

        if (!da9052_i2c)
                return -ENOMEM;

	/* Get the bus driver handler */
	adapter = to_i2c_adapter(client->dev.parent);

	/* Check i2c bus driver supports byte data transfer */
	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_info(&client->dev,\
		"Error in %s:i2c_check_functionality\n", __func__);
		return -ENODEV;;
	}

	/* Store handle to i2c client */
	da9052_i2c->i2c_client = client;
	da9052_i2c->irq = client->irq;

	da9052_i2c->dev = &client->dev;

	/* Initialize i2c data structure here*/
	da9052_i2c->adapter = adapter;

	/* host i2c driver looks only first 7 bits for the slave address */
	da9052_i2c->slave_addr = DA9052_I2C_ADDR >> 1;

	/* Store the i2c client data */
	i2c_set_clientdata(client, da9052_i2c);

	 /* Validate I2C connectivity */
        if ( I2C_CONNECTED  == da9052_i2c_is_connected()) {
		/* Enable Repeated Write Mode permanently */
		const struct da9052_ssc_msg ctrl_msg = 
			{DA9052_CONTROLB_REG, DA9052_CONTROLB_WRITEMODE};
		if (da9052_i2c_write(da9052_i2c, &ctrl_msg) < 0) {
			dev_info(&da9052_i2c->i2c_client->dev,
				 "%s: repeated mode not set!!\n", __func__);
			return -ENODEV;
		}

                /* I2C is connected */
                da9052_i2c->connecting_device = I2C;
                if( 0!= da9052_ssc_init(da9052_i2c) )
                        return -ENODEV;
        }
        else {
                return -ENODEV;
        }

        //printk("Exiting da9052_i2c_probe.....\n");

	return 0;
}

static int da9052_i2c_remove(struct i2c_client *client)
{

	struct da9052 *da9052 = i2c_get_clientdata(client);

	mutex_destroy(&i2c_lock);

	mfd_remove_devices(da9052->dev);
	kfree(da9052);
	return 0;
}

#ifdef I2C_BUG_WORKAROUND
#define I2C_DUMMY_REG	0xFF
const unsigned char i2c_flush_data[] = {I2C_DUMMY_REG, 0xFF};

#if 1	/* Enable safe register addresses checking */
/* DLG TODO: Add read only registers here (they are not affected with write) */
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
#else
static inline int da9052_is_i2c_reg_safe(unsigned char reg)
{
	return 0;
}
#endif
#endif

int da9052_i2c_write(struct da9052 *da9052, struct da9052_ssc_msg *msg)
{
	struct i2c_msg i2cmsg;
	unsigned char buf[4];
	int ret = 0;

	mutex_lock(&i2c_lock);

	if(shutdown)
	{
		printk("da9052_i2c_write after shutdown\n");
mutex_unlock(&i2c_lock);
		return 0;
	}
	
#ifdef CONFIG_MACH_MX53_BEJ2
	if(get_bej2_suspend_state() && da9052_regulator_flag == 0)
	{
#ifdef BEJ2_I2C_SUSPEND_STATE_LOG
		printk("da9052_i2c_write after suspend\n");
#endif
mutex_unlock(&i2c_lock);
		return -BEJ2_DA9052_I2C_SUSPENDSTATUS_ERR;
	}
#endif

	if((msg->addr == DA9052_CONTROLB_REG) && (msg->data & DA9052_CONTROLB_SHUTDOWN))
	{
		printk("da9052_i2c_write shutdown\n");
		shutdown = 1;
//		return 0;
	}

	/*Construct a i2c msg for a da9052 driver ssc message request */
	i2cmsg.addr  = da9052->slave_addr;
	i2cmsg.buf   = buf;
	i2cmsg.flags = 0;
	i2cmsg.len   = 2;

	/* Copy the ssc msg and additional data to flush chip I2C registers */
	buf[0] = msg->addr;
	buf[1] = msg->data;

#ifdef I2C_BUG_WORKAROUND
	/* Test, whether register to be accessed needs to be flushed */
	if (!da9052_is_i2c_reg_safe(msg->addr)) {
		i2cmsg.len   = 4;
		buf[2] = i2c_flush_data[0];
		buf[3] = i2c_flush_data[1];
	}
#endif
	/* Start the i2c transfer by calling host i2c driver function */
	ret = i2c_transfer(da9052->adapter, &i2cmsg, 1);
	if (ret < 0) {
		dev_info(&da9052->i2c_client->dev,
			 "%s: i2c_transfer failed!!!\n", __func__);
mutex_unlock(&i2c_lock);
		return ret;
	}
mutex_unlock(&i2c_lock);
	return 0;
}

int da9052_i2c_read(struct da9052 *da9052, struct da9052_ssc_msg *msg)
{
	unsigned char buf[2] = {0, 0};
	struct i2c_msg i2cmsg[3];
	int ret = 0;

	mutex_lock(&i2c_lock);

	if(shutdown)
	{
		printk("da9052_i2c_read after shutdown\n");
mutex_unlock(&i2c_lock);
		return 0;
	}
	
#ifdef CONFIG_MACH_MX53_BEJ2
	if(get_bej2_suspend_state() && da9052_regulator_flag == 0)
	{
#ifdef BEJ2_I2C_SUSPEND_STATE_LOG
		printk("da9052_i2c_read after suspend\n");
#endif
mutex_unlock(&i2c_lock);
		return -BEJ2_DA9052_I2C_SUSPENDSTATUS_ERR;
	}
#endif

	/* Copy SSC Msg to local character buffer */
	buf[0] = msg->addr;

	/*Construct a i2c msg for a da9052 driver ssc message request */
	i2cmsg[0].addr  = da9052->slave_addr ;
	i2cmsg[0].len   = 1;
	i2cmsg[0].buf   = &buf[0];
	i2cmsg[0].flags = 0;

	/*Construct a i2c msg for a da9052 driver ssc message request */
	i2cmsg[1].addr  = da9052->slave_addr ;
	i2cmsg[1].len   = 1;
	i2cmsg[1].buf   = &buf[1];
	i2cmsg[1].flags = I2C_M_RD;
	
	/* Standard read transfer */
	ret = i2c_transfer(da9052->adapter, i2cmsg, 2);

#ifdef I2C_BUG_WORKAROUND
	/* Test, whether register to be accessed needs to be flushed */
	if (!da9052_is_i2c_reg_safe(msg->addr)) {
		i2cmsg[2].addr = da9052->slave_addr;
		i2cmsg[2].len = 2;
		i2cmsg[2].flags = 0;		/* Write operation */
		/* i2c_flush_data is only to read from */
		i2cmsg[2].buf = (unsigned char *)i2c_flush_data;

		/* Read transfer with additional flush write */
		ret = i2c_transfer(da9052->adapter, &i2cmsg[2], 1);
	}
#endif

	if (ret < 0) {
		dev_info(&da9052->i2c_client->dev,
			 "%s: i2c_transfer failed!!!\n", __func__);
mutex_unlock(&i2c_lock);
	return ret;
	}

	msg->data = buf[1];
mutex_unlock(&i2c_lock);
	return 0;
}

int da9052_i2c_write_many(struct da9052 *da9052,
	struct da9052_ssc_msg *sscmsg, int msg_no)
{
	struct i2c_msg i2cmsg;
	int ret = 0;
	int cnt;
	unsigned char *data_ptr;
#ifdef I2C_BUG_WORKAROUND
	unsigned char data_buf[2*MAX_READ_WRITE_CNT + 2];
#else
	unsigned char data_buf[2*MAX_READ_WRITE_CNT];
#endif
	
	BUG_ON(msg_no < 0);
	BUG_ON(msg_no >= MAX_READ_WRITE_CNT);
/*
	printk(KERN_CRIT "D9053: %s: write %d messages starting from %hhu reg\n", 
	       __func__, msg_no, sscmsg->addr);
*/

	mutex_lock(&i2c_lock);

	if(shutdown)
	{
		printk("da9052_i2c_write_many after shutdown\n");
mutex_unlock(&i2c_lock);
		return 0;
	}
	
#ifdef CONFIG_MACH_MX53_BEJ2
	if(get_bej2_suspend_state() && da9052_regulator_flag == 0)
	{
#ifdef BEJ2_I2C_SUSPEND_STATE_LOG
		printk("da9052_i2c_write_many after suspend\n");
#endif
mutex_unlock(&i2c_lock);
		return -BEJ2_DA9052_I2C_SUSPENDSTATUS_ERR;
	}
#endif

	/* Construct a i2c msg for REPEATED WRITE */
	i2cmsg.addr  = da9052->slave_addr ;
	i2cmsg.len   = 2*msg_no;
	i2cmsg.buf   = data_buf;
	i2cmsg.flags = 0;
	
	for (data_ptr = data_buf, cnt = msg_no; cnt; cnt--) {
		*(data_ptr++) = sscmsg->addr;
		*(data_ptr++) = sscmsg->data;
		sscmsg++;
	}
#ifdef I2C_BUG_WORKAROUND
	/* Test, whether last register to be accessed needs to be flushed */
	if (msg_no != 0 && !da9052_is_i2c_reg_safe(sscmsg[-1].addr)) {
		i2cmsg.len += 2;
		*(data_ptr++) = i2c_flush_data[0];
		*data_ptr = i2c_flush_data[1];
	}
#endif

	/* Start the i2c transfer by calling host i2c driver function */
	ret = i2c_transfer(da9052->adapter, &i2cmsg, 1);
	if (ret < 0) {
		dev_info(&da9052->i2c_client->dev,
			 "%s: i2c_transfer failed!!!\n", __func__);
mutex_unlock(&i2c_lock);
		return ret;
	}
mutex_unlock(&i2c_lock);

	return 0;
}

int da9052_i2c_read_many(struct da9052 *da9052,
	struct da9052_ssc_msg *sscmsg, int msg_no)
{
	struct i2c_msg i2cmsg[2];
	unsigned char data_buf[MAX_READ_WRITE_CNT];
	int ret = 0;
	int expected_addr = 0xFF;
	int cnt;

	BUG_ON(msg_no < 0);
	BUG_ON(msg_no >= MAX_READ_WRITE_CNT);
/*
	printk(KERN_CRIT "D9053: %s: read %d messages starting from %hhu reg\n", 
	       __func__, msg_no, sscmsg->addr);
*/

	mutex_lock(&i2c_lock);

	if(shutdown)
	{
		printk("da9052_i2c_read_many after shutdown\n");
mutex_unlock(&i2c_lock);
		return 0;
	}
	
#ifdef CONFIG_MACH_MX53_BEJ2
	if(get_bej2_suspend_state() && da9052_regulator_flag == 0)
	{
#ifdef BEJ2_I2C_SUSPEND_STATE_LOG
		printk("da9052_i2c_read_many after suspend\n");
#endif
mutex_unlock(&i2c_lock);
		return -BEJ2_DA9052_I2C_SUSPENDSTATUS_ERR;
	}
#endif

	/* Construct a i2c msgs for a da9052 driver ssc message request */
	cnt = 0;
	do {
		/* Build messages for read transaction */
		i2cmsg[0].addr  = da9052->slave_addr;
		i2cmsg[0].buf   = &sscmsg[cnt].addr;
		i2cmsg[0].flags = 0;
		i2cmsg[0].len   = 1;
		i2cmsg[1].addr  = da9052->slave_addr;
		i2cmsg[1].buf   = &data_buf[cnt];
		i2cmsg[1].flags = I2C_M_RD;
		/* Grab consecutive register reads into one message */
		for (i2cmsg[1].len = 0, expected_addr = sscmsg[cnt].addr;
			(cnt < msg_no) && (sscmsg[cnt].addr == expected_addr);
			cnt++, expected_addr++)
		{
			i2cmsg[1].len++;
		}
		
		/* Perform read transaction */
		ret = i2c_transfer(da9052->adapter, i2cmsg, 2);
		if (ret < 0) {
			dev_info(&da9052->i2c_client->dev,
				 "%s: i2c_transfer failed!!!\n", __func__);
mutex_unlock(&i2c_lock);
			return ret;
		}
	} while (cnt < msg_no);

#ifdef I2C_BUG_WORKAROUND
	/* Test, whether last register to be accessed needs to be flushed */
	if (!da9052_is_i2c_reg_safe(sscmsg[msg_no-1].addr)) {
		i2cmsg[0].addr  = da9052->slave_addr;
		i2cmsg[0].len   = 2;
		i2cmsg[0].flags = 0;	 /* Write operation */
		/* i2c_flush_data is only to read from */
		i2cmsg[0].buf   = (unsigned char *)i2c_flush_data;

		ret = i2c_transfer(da9052->adapter, i2cmsg, 1);
		if (ret < 0) {
			dev_info(&da9052->i2c_client->dev,
				 "%s: i2c_transfer failed!!!\n", __func__);
mutex_unlock(&i2c_lock);
			return ret;
		}
	}
#endif

	for (cnt = 0; cnt < msg_no; cnt++) sscmsg[cnt].data = data_buf[cnt];
mutex_unlock(&i2c_lock);
	return 0;
}

static struct i2c_device_id da9052_ssc_id[] = {
	{ DA9052_SSC_I2C_DEVICE_NAME, 0},
	{}
};

static struct i2c_driver da9052_i2c_driver =  {
	.driver = {
		.name	= DA9052_SSC_I2C_DEVICE_NAME,
		.owner	= THIS_MODULE,
	},
	.probe	= da9052_i2c_probe,
	.remove	= da9052_i2c_remove,
	.id_table	= da9052_ssc_id,
};

static int __init da9052_i2c_init(void)
{
        int ret = 0;
       // printk("\n\nEntered da9052_i2c_init................\n\n");
        ret = i2c_add_driver(&da9052_i2c_driver);
        if (ret != 0) {
                printk(KERN_ERR "Unable to register %s\n", DA9052_SSC_I2C_DEVICE_NAME);
                return ret;
        }
        return 0;
}
subsys_initcall(da9052_i2c_init);

static void  __exit da9052_i2c_exit(void)
{
        i2c_del_driver(&da9052_i2c_driver);
}
module_exit(da9052_i2c_exit);

MODULE_AUTHOR("Dialog Semiconductor Ltd <dchen@diasemi.com>");
MODULE_DESCRIPTION("I2C driver for Dialog DA9052 PMIC");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DA9052_SSC_I2C_DEVICE_NAME);
