/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: i2c.h,v $
 * Revision 1.1.7.1  2004/02/18  20:35:59  Aaron_Biver
 * 	Add flag bit TEMP_THRESHOLD_DONE
 *
 * Revision 1.1.4.2  1999/02/12  21:01:25  Dick_Bagley
 * 	Add support for the LM75 temperature sensor
 * 	(original version of the driver supports only
 * 	the Dallas sensor). Required for the WebBrick
 * 	platform.
 * 	[1999/02/11  20:08:57  Dick_Bagley]
 *
 * Revision 1.1.2.3  1998/06/25  20:58:56  Jim_Hamel
 * 	modifications for Goldrush support
 * 	[1998/06/24  18:42:24  Jim_Hamel]
 * 
 * Revision 1.1.2.2  1998/06/22  21:49:47  Dave_Gerson
 * 	Initial creation.
 * 	[1998/06/22  20:38:35  Dave_Gerson]
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: i2c.h,v $ $Revision: 1.1.7.1 $ (DEC) $Date: 2004/02/18 20:35:59 $
 */

#ifndef __I2C_H__
#define __I2C_H__


/* Mode Definition flags */
#define I2C_DALLAS                              0
#define I2C_LM75                                1

/* Philips I2C Bus Operation Declarations In Support of Environmental Monitoring */

#define I2C_ERROR 			       -1
#define I2C_DEVICE_PRESENT 		        1
#define I2C_DEVICE_NOT_PRESENT 		        0

/* number of bytes to transfer to read the temp sensor */
#define DALLAS_TEMP_SEQUENCE_SIZE               4
#define LM75_TEMP_SEQUENCE_SIZE                 1
#define MAX_TEMP_SEQUENCE_SIZE                  DALLAS_TEMP_SEQUENCE_SIZE

#define TEMPSENSOR_ADDR 			0x9E
#define ENV_FAIL_REG_ADDR     			0x70
#define ENV_FUNC_REG_ADDR     			0x72

/* argument passed into i2c_get_temp */
#define I2C_READ_TEMP                           0
#define I2C_READ_TEMP_THRESHOLD                 1

/* status defines */
#define I2C_FAN_OK 				1
#define I2C_POWER_OK 				1
#define I2C_ERROR_LIMIT 			35

/* i2c kernel measurement thread state support */
#define TEMP_THRESHOLD_DONE			0x1
#define TEMP_DONE				0x2
#define FAN_DONE				0x4
#define POWER_DONE				0x8

#define wait_for_iicfree() \
	if(wait_for_i2cfree()) {\
		lock_done(&i2c_lock);\
		return I2C_ERROR;\
	}

#define wait_for_nointr() \
	if(wait_for_i2c_nointr()){\
		lock_done(&i2c_lock);\
		return I2C_ERROR;\
	}


#endif /* __I2C_H__ */
