/*
 * *****************************************************************
 * *                                                               *
 * *   Copyright 2002 Compaq Information Technologies Group, L.P.  *
 * *                                                               *
 * *   The software contained on this media  is  proprietary  to   *
 * *   and  embodies  the  confidential  technology  of  Compaq    *
 * *   Computer Corporation.  Possession, use,  duplication  or    *
 * *   dissemination of the software and media is authorized only  *
 * *   pursuant to a valid written license from Compaq Computer    *
 * *   Corporation.                                                *
 * *                                                               *
 * *   RESTRICTED RIGHTS LEGEND   Use, duplication, or disclosure  *
 * *   by the U.S. Government is subject to restrictions  as  set  *
 * *   forth in Subparagraph (c)(1)(ii)  of  DFARS  252.227-7013,  *
 * *   or  in  FAR 52.227-19, as applicable.                       *
 * *                                                               *
 * *****************************************************************
 */
/*
 * HISTORY
 */
/*
 * @(#)$RCSfile: cam_sensor.h,v $ $Revision: 1.1.6.1 $ (DEC) $Date: 2001/10/16 19:10:40 $
 */

#ifndef	_CAM_SENSOR_H_
#define	_CAM_SENSOR_H_

/*
 * The following flags are used in the SENSOR_SPECIFIC structure in member
 * cs_state_flags.  The state flags are used to determine and indicate
 * certain states the driver and SCSI sensor unit is in.
 */

#define	SENSOR_NOT_READY_STATE			0x00000001
	/*
	 * Indicates that the unit was opened with the FNDELAY flag and
	 * the unit had	some sort of failure during open but was seen
	 */
#define	SENSOR_UNIT_ATTEN_STATE			0x00000002
	/*
	 * Indicates that a check condition occurred and the sense key
	 * was UNIT ATTENTION. This usually indicates that a media change
	 * has occurred	but could be power up, reset. Either way we must
	 * notice that current sensor position is	lost.
	 */
#define	SENSOR_RESET_STATE			0x00000004
	/*
	 * Indicates that we have been notified	of a reset set condition 
	 * on the device or bus.
	 */
#define	SENSOR_RESET_PENDING_STATE		0x00000008
	/*
	 * A reset is pending will get notified	shortly
	 */
#define	SENSOR_OPENED_STATE			0x00000010
	/*
	 * The unit is opened
	 */
#define SENSOR_EXCLUSIVE_OPEN			0x00000020
	/*
	 * Exclusive open done.
	 */
#define	SENSOR_TRIED_ONLINE_STATE		0x00000400
	/*
	 * We found the	unit to	be in the NOT READY state. We have
	 * tried to bring the unit online once.	
	 */
#define	SENSOR_SYNC_STATE			0x00000800
	/*
	 * Tried to do synchronous negoiation
	 */

/*
 * The SENSOR Reservation States:
 *
 * The following Reservation state flags and macros are	used by	the
 * DEVRCI function to effect the state flows in	the sensor driver.
 */
#define	SENSOR_RESERVE_PENDING_STATE		0x00100000
	/* 
	 * Indicates that we are waiting for a reservation to applied
	 * to the device. 
	 */
#define	SENSOR_RESERVE_APPLIED_STATE		0x00200000
	/* A Reservation has been applied to this device.  */

#define	SENSOR_RESERVE_CONFLICT_STATE		0x00400000
	/* A Reservation Conflict has been detected on this device. */

#define	SENSOR_RESERVATION_STATES (SENSOR_RESERVE_CONFLICT_STATE | \
				   SENSOR_RESERVE_PENDING_STATE  | \
				   SENSOR_RESERVE_APPLIED_STATE)
/*
 * The SENSOR_OR_RESERVE_STATE macro is used to conditionally set the
 * device state	flag indicating	a reservation needs to be applied to the
 * device.  
 *
 * Note: This MACRO must be called with	the sensor specific lock HELD
 */
#define	SENSOR_OR_RESERVE_STATE(state, flags)			\
{								\
  if ((state) &	SENSOR_RESERVE_APPLIED_STATE) {			\
    (state) |= (flags);						\
  }								\
} 

/*
 * The SENSOR_PREVIOUS_RESET_CONDITION macro defines the binary state
 * of the device used to determine whether or not destructive media
 * access commands are allowed.
 *
 * Note: This MACRO must be called with	the sensor specific lock HELD
 */
#define	SENSOR_PREVIOUS_RESET_CONDITION(state_flags)		\
    ((state_flags) & (SENSOR_RESET_STATE		|	\
		      SENSOR_RESET_PENDING_STATE))

#define SENSOR_RESET_ERROR_STATE			0x08000000
	/* This flag is set in sensor_async() to let the driver know
	 * that a bus or device reset has occurred, in order to let
	 * ioctls report an error after a bus reset in multi-initiator
	 * environments (i.e. in ASE, when the RESERVE command has
	 * eaten the Unit Attention signal).
	 */

/* ----------------------------------------------------------------------- */

/*
 * The following flags are used in the SENSOR_SPECIFIC structure in member
 * cs_flags.  The flags are used to determine and indicate certain conditions
 * of the sensor media.
 */
#define	SENSOR_OFFLINE			DEV_OFFLINE	/* 0x00000004 */
	/* Indicates the the device is returning a DEVICE not READY
	 * in response to a check condition.  Basically means the sensor
	 * media is not	loaded or is being loaded.
	 */
#define	SENSOR_SOFTERR			DEV_SOFTERR	/* 0x00000080 */
	/* Indicates that a soft error has been	reported by the	sensor
	 * unit.
	 */
#define	SENSOR_HARDERR			DEV_HARDERR	/* 0x00000100 */
	/* Hard	error has occurred this	flag can be reported back to 
	 * the user either thru	and ioctl or the user gets notified 
	 * by the buf struct being marked as EIO.
	 */
#define	SENSOR_DONE			DEV_DONE	/* 0x00000200 */
	/* Indicates done
	 */
#define	SENSOR_RETRY			DEV_RETRY	/* 0x00000400 */
	/* Indicates retry
	 */

/* ----------------------------------------------------------------------- */

typedef struct cam_env_callout_parameters {
    CCMN_SPECIFIC *ecp_pd;	/* Pointer to common pd structure.	*/
    int	ecp_sensor_type;	/* Type of sensor to check.		*/
    ulong ecp_sensor_status;	/* Last sensor status reported.		*/
} cam_env_callout_parameters_t;

/*
 * Sensor Specific Data Structure:
 */
typedef	struct sensor_specific {
    U32		cs_flags;	/* Sensor flags.			*/
    U32		cs_state_flags;	/* STATE - UNIT_ATTEN, RESET etc.	*/
    U32		cs_resid;	/* Last	operation residual count.	*/
    U32		cs_snsinfo;	/* Last	sense information bytes.	*/
    CAM_U8	cs_snskey;	/* Last	Sense Key.			*/
    TRANSLATION	*cs_trans;	/* TRANSLATION initialized when	device	*/
				/*   is opened (by sensor_spec_setup).	*/
    PATH	*cs_path;	/* The path translation pointer.	*/
    CAM_EEI_STATUS cs_eei_status; /* The EEI status quadword.		*/
    /*
     * Fields to support environmental monitoring subsystem.
     */
    struct env_sensor_access_group *cs_access_group;
    struct env_sensor_info *cs_sensor_info[ENV_SENSOR_TYPE_MAX-1];

} SENSOR_SPECIFIC;

/*
 * You must increment the version number if you	change the structure.
 */
#define	SENSOR_SPECIFIC_VERS	1	/* Sensor specific version.	*/

/*
 * The sensor_action struct is passed down to the sensor action
 * routines to be filled in based on success or	failure	of the
 * command.
 */
typedef	struct sensor_action {
	DCB_SCSIIO	*act_ccb;	/* The ccb that	is returned	*/
	I32		act_ret_error;	/* Error code if any		*/
	U32		act_fatal;	/* Is this considered fatal	*/
	U32		act_ccb_status;	/* The ccb status code		*/
	U32		act_scsi_status;/* The scsi error code		*/
	U32		act_chkcond_error;/* The check condition error	*/
} SENSOR_ACTION; 

/*
 * SENSOR_ACTION defines
 * action.fatal	flags;
 */
#define	ACT_FAILED		0x00000001	/* This	action has failed */
#define	ACT_RESOURCE		0x00000002	/* Resource problem (memory)*/
#define	ACT_PARAMETER		0x00000004	/* Invalid parameter	*/
#define	ACT_RETRY_EXCEDED	0x00000008	/* Retry the operation count
						 * count has been excede */
#define	ACT_INTERRUPTED		0x00000010	/* Signal interruption	*/

#define	SENSOR_RETRY_LIMIT	100	/* Retries for SCSI_BUSY status. */
#define	SENSOR_MIN_SENSE	14	/* Minimun size	of sense needed. */
#define SENSOR_RETRIES		2	/* Maximum times commands retried */
#define SENSOR_TIME_DEF		30	/* Default SCSI I/O CCB timeout. */

/*
 * Whether we sleep in the work	routines 
 * sensor_move_sensor(), sensor_load(), etc.
 */
#define	SENSOR_SLEEP	0x00000000
#define	SENSOR_NOSLEEP	0x00000001

/*
 * Defines for what sensor_ccb_chkcond returns
 */
#define	CHK_SENSE_NOT_VALID	0x0001	/* Valid bit is	not set	in sense */
#define	CHK_EOM			0x0002	/* End of media			*/
#define	CHK_FILEMARK		0x0003	/* File	mark detected		*/
#define	CHK_ILI			0x0004	/* Incorrect length		*/
#define	CHK_NOSENSE_BITS	0x0005	/* NOSENSE key and no bits	*/
#define	CHK_RECOVER		0x0006	/* soft	error reported		*/
#define	CHK_NOT_READY		0x0007	/* Device is not ready		*/
#define	CHK_MEDIUM_ERR		0x0008	/* Device reported hard	sensor error*/
#define	CHK_HARDWARE		0x0009	/* Hardware error		*/
#define	CHK_ILL_REQ		0x000a	/* Illegal request maynot support cmd*/
#define	CHK_UNIT_ATTEN		0x000b	/* Unit	attention (ready???)	*/
#define	CHK_DATA_PROT		0x000c	/* write protected		*/
#define	CHK_BLANK_CHK		0x000d	/* Blank check erased sensor	*/
#define	CHK_VENDOR_SPEC		0x000e	/* Vendor specific (no idea)	*/
#define	CHK_COPY_ABORT		0x000f	/* Copy	cmd aborted		*/
#define	CHK_CMD_ABORTED		0x0010	/* Command has been aborted	*/
#define	CHK_EQUAL		0x0011	/* Search cmd equal		*/
#define	CHK_VOL_OFLOW		0x0012	/* Phys	end of media, data in buf */
#define	CHK_MIS_CMP		0x0013	/* Miscompare src != media	*/
#define	CHK_UNKNOWN_KEY		0x0014	/* Bogus sense key		*/
#define	CHK_CHK_NOSENSE		0x0015	/* Sense Auto sense valid bit 0	*/
#define	CHK_INFORMATIONAL	0x0016	/* Informational message...	*/

#define	SENSOR_INFO(sns, long_val) {		\
	union	{				\
		unsigned char	c[4];		\
		U32		l;		\
	}tmp;					\
	if( (sns)->valid != NULL){		\
	    tmp.c[3] = (sns)->info_byte3;	\
	    tmp.c[2] = (sns)->info_byte2;	\
	    tmp.c[1] = (sns)->info_byte1;	\
	    tmp.c[0] = (sns)->info_byte0;	\
	    (long_val) = tmp.l;			\
	}					\
	else{					\
	    (long_val) = NULL;			\
	}					\
}

#define	SENSOR_OR_STATE( pd, flags )					\
{									\
	CCMN_LOCK( (pd)	);						\
	((SENSOR_SPECIFIC *)((pd)->pd_dev_specific))->cs_state_flags |= (flags); \
	CCMN_UNLOCK( (pd) );						\
}

#define	SENSOR_CLR_STATE( pd, flags )					\
{									\
	CCMN_LOCK( (pd)	);						\
	((SENSOR_SPECIFIC *)((pd)->pd_dev_specific))->cs_state_flags	\
			&= ~((U32)(flags));				\
	CCMN_UNLOCK( (pd) );						\
}

#define	SENSOR_OR_FLAGS(pd, flags )					\
{									\
	CCMN_LOCK( (pd)	);						\
	((SENSOR_SPECIFIC *)((pd)->pd_dev_specific))->cs_flags |= (flags); \
	CCMN_UNLOCK( (pd) );						\
}

#define	SENSOR_CLR_FLAGS( pd, flags )					\
{									\
	CCMN_LOCK( (pd)	);						\
	((SENSOR_SPECIFIC *)((pd)->pd_dev_specific))->cs_flags &= ~((U32)(flags));\
	CCMN_UNLOCK( (pd) );						\
}

#define	SENSOR_BERROR( buf, count, error )				\
{									\
	(buf)->b_resid = (count);					\
	(buf)->b_error = (error);					\
	(buf)->b_flags |= B_ERROR;					\
}

#define	SENSOR_NULLCCB_ERR( act_ptr, pd, mod, trans ) {			\
	CCMN_LOCK( (pd)	);						\
	CAM3_ERROR(mod, "NULL CCB returned", CAM_SOFTWARE,		\
		 (CCB_HEADER *)NULL, trans, (CAM_U8 *)NULL);		\
	CCMN_UNLOCK( (pd) );						\
	(act_ptr)->act_fatal |=	(ACT_RESOURCE |	ACT_FAILED);		\
	(act_ptr)->act_ret_error = ENOMEM;				\
}

#define SENSOR_PATH_FAIL_LIMIT	1 /* number of events before we declare
				     this path down */
/*
 * Check whether we have the minimum required sense data bytes.
 */
#define CHECK_SENSE_RESID(c3cb)					\
  ( ((c3cb)->cam_sense_len - (c3cb)->cam_sense_resid) >= SENSOR_MIN_SENSE )

#define PD_NO_DEVICE	0x01	/* Device didn't respond to TUR but was */
				/* opened anyway */
#define PD_ONLINE	0x02	/* Device responded to TUR */
#define PD_REC_INPROG	0x04	/* Recovery in progress */

#define IO_CONT		0	/* Leave request on queue and return */
#define IO_DONE		1	/* Request completed sucessfully */
#define IO_FAILURE	2	/* Request completed with error */
#define IO_RETRY	3	/* Request must be retried */
#define IO_RECOVER	4	/* Start recovery before retry */

#define GET_CS(tr) \
    ((SENSOR_SPECIFIC *)((CCMN_SPECIFIC *)(tr->pd_specific))->pd_dev_specific)

#endif /* !_CAM_SENSOR_H_ */
