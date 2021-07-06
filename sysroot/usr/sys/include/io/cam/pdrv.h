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

#pragma ident "@(#)$RCSfile: pdrv.h,v $ $Revision: 1.1.87.3 $ (DEC) $Date: 2002/05/30 23:16:05 $"
#ifndef _PDRV_
#define _PDRV_

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 *
 *  pdrv.h		Version	1.00
 *
 *  This file contains the common definitions and data structures for the
 *  CAM	peripheral drivers.
 *
 ************************************************************************/

/*
 * CAM3	declarations are included so that older	cam1 files, including
 * this	file, will still compile.
 */
#include <io/common/devio.h>
#include <io/common/devgetinfo.h>
#include <io/common/deveei.h>
#include <io/cam/dec_cam.h>
#include <io/cam/scsi_all.h>
#include <io/cam/cam.h>
#include <io/cam/dec_common.h>
#include <sys/time.h>
#include <sys/buf.h>


/************************************************************************
 *
 * Tagged sections:
 *
 *	Common CAM-1 / CAM-3 and CAM-1 specific	defines
 *
 * :tag01::	Mode Select Table Structure and	other definition
 * :tag05::	Density	Table Structure	definitions
 * :tag10::	Device attribute structure
 * :tag15::	Device Descriptor Structure
 * :tag20::	Peripheral Driver Working Set Definition
 * :tag25::	Peripheral Device Structure - CAM1
 * :tag30::	Specific Info structure
 *
 *	CAM3 defines and structures
 *
 * :tag35::	Error logging flag, tagged queue distribution,
 *		functions entry/exit lock state	flags, drive state flags
 * :tag40::	Common device path structure - CCMN_DEV_PATH
 * :tag45::	CAM-3 common driver structure -	CCMN_SPECIFIC
 * :tag50::	Peripheral Drive Unit Table
 * :tag55::	PDRV_UNIT_INFO structure
 * :tag60::	SCSI registration structure
 * :tag70::	EEI (Extended Error Information) support
 *
 *	CAM-3 macros
 *
 * :tag72::	Macros - return	port, target, lun, SCSI_DID
 *		from TRANSLATION or CONNECTION_ID
 * :tag74::	CAM-1 /	CAM-3 testing and translation
 *
 *	Locking	macros
 *
 * :tag82::	SMP locking macros for the bus structure
 * :tag84::	PDU_UNIT_LOCK/UNLOCK - per-unit	SMP sleep lock.
 * :tag86::	CAM-3 equivalents of the unit locks
 * :tag88::	The IPL	locking	Macros for the unit table structure.
 * :tag90::	The IPL/SMP locking Macros for the buf structure pool.
 * :tag92::	The IPL/SMP locking Macros for the peripheral device structure.
 * :tag94::	CAM-3 Lock macros for ccmn_specific
 * :tag96::	The IPL/SMP locking Macros for the data	buffer allocation.
 *
 *	Misc macros
 *
 * :tag100::	Macros to set, clear and check CCMN_SPECIFIC.pd_drv_state flags.
 * :tag110::	Macros to clear	ccb, release ccb queue
 * :tag120::	DEV_DESC lock macros, defines and misc
 * :tag200::	Prototypes of the pdrv_common.c	routines
 ************************************************************************/

/************************************************************************
 * :tag01::	Mode Select Table Structure and	other definition
 ************************************************************************/
#define	MAX_OPEN_SELS	8	/* Maximum entries in the Mode Select */
				/* Table which is pointed to in	the */
				/* device descriptor table */
typedef	struct modesel_tbl {
	struct ms_entry{
	   u_char  ms_page;	/* Page	number */
	   u_char  *ms_data;	/* Pointer to Mode Select data */
	   u_char  ms_data_len;	/* Mode	Select data length */
	   u_char  ms_ent_sp_pf;/* Save	Page and Page format bits */
				/* BIT 0   1=Save Page,	*/
				/*	   0=Don't Save	Page */
				/* BIT 1  1=SCSI-2, 0=SCSI-1 */
	   u_short ms_mask;	/* device type mask this applies to */
	}ms_entry[MAX_OPEN_SELS];
}MODESEL_TBL;

/*
 * Bit definitions for ms_ent_sp_pf field of mode select table.
 */
#define	MSEL_SAVE_PAGE		0x01	/* Bit set for save page */
#define	MSEL_SCSI2		0x02	/* Bit set for SCSI-2 */

#define	MODESEL_TBL_VERS	0x01	/* Please remember to increase
					 * The version number if you
					 * change the structure.
					 */
/* 
 * define for number of	entries	for stack
 */
#define	CCMN_MAX_ENTRIES	15	

/************************************************************************
 * :tag05::	Density	Table Structure	definitions
 ************************************************************************/
/*
 * Defines for den_flags
 */
#define	DENS_VALID		0x01	/* Is the structure valid	*/
#define	ONE_FM			0x02	/* Write 1 filemark on close QIC */
#define	DENS_SPEED_VALID	0x04	/* Speed setting valid.	Multi speed */
#define	DENS_BUF_VALID		0x08	/* Run in buffered mode	(cache)	*/
#define	DENS_COMPRESS_VALID	0x10	/* Compression code if supported */

#define	MAX_TAPE_DENSITY 8	/* Maximum entries in the density */
				/* table which is pointed to in	the */
				/* device descriptor table */
typedef	struct density_tbl {
	struct density{
	   u_char    den_flags;		/* VALID, ONE_FM etc */
	   u_char    den_density_code;
	   u_char    den_compress_code;	/* Compression code if supported */
	   u_char    den_speed_setting;	/* for this density */
	   u_char    den_buffered_setting;
					/* Buffer control setting */
	   U32	  den_blocking;	/* 0 variable etc. */
	}density[MAX_TAPE_DENSITY];	/* maybe 8 */
}DENSITY_TBL;

#define	DENSITY_TBL_VERS	0x01	/* Please remember to increase
					 * The version number if you
					 * change the structure.
					 */
/************************************************************************
 * :tag10::	Device attribute structure
 ************************************************************************/
/*
 * Device's can	now have arbitrary attributes defined for them.
 * The following structure defines what	an "attribute" is.
 */
typedef	struct device_attribute	{
	char	*attr_name;
	char	*attr_data;
	struct device_attribute	*link;	/* link	to next	attribute for device */
	int		attr_length;
} device_attribute_t;
#define	DEV_ATTRIBUTE	device_attribute_t


/************************************************************************
 * :tag15::	Device Descriptor Structure
 ************************************************************************/
/*
 * There will be a device descriptor structure entry for each
 * specific device supported by	DEC.  A	user may supply	a new
 * entry to the	device descriptor table	by adding it to	cam_data.c and
 * relinking the kernel	or by sending it via an	ioctl()	call
 * (TBD).  The following describes an entry in the device
 * descriptor table:
 */
#define	IDSTRING_SIZE	24	/* Maximum size	of product and vendor ID */
				/* string from inquiry data */
#define	DEV_NAME_SIZE	32	/* Maximum size	of the device name */
#define	VID_STRING_SIZE	8	/* Vendor id size in inquiry data */
#define	PID_STRING_SIZE	16	/* Product id string size in inquiry data */
#define	REV_STRING_SIZE	4	/* Product revision level string size in */

#ifndef	DDR_VID_LENGTH
#define	DDR_VID_LENGTH	VID_STRING_SIZE	+ 1
#define	DDR_PID_LENGTH	PID_STRING_SIZE	+ 1
#define	DDR_REV_LENGTH	REV_STRING_SIZE	+ 1
#endif /* not DDR_VID_LENGTH */

typedef	struct dev_desc	{
#define	DEV_DESC_VERS		0x04	/* Please remember to increase
					 * The version number if you
					 * change the structure.
					 */
	char	dd_pv_name[IDSTRING_SIZE];
				/* Product ID and vendor string	from */
				/* Inquiry data	*/
	u_char	dd_length;	/* Length of dd_pv_name	string */
	char	dd_dev_name[DEV_NAME_SIZE];
				/* Device name string -	see defines */
				/* in devio.h */
	U32	dd_device_type;	/* Bits	0 - 23 contain the device */
				/* class, bits 24-31 contain the */
				/* SCSI	device type */
	struct	pt_info	*dd_def_partition;
				/* Default partition sizes - disks */
	U32	dd_block_size;	/* Block/sector	size  */
	U32	dd_max_record;	/* Maximun transfer size in bytes */
				/* allowed for the device */
	DENSITY_TBL *dd_density_tbl;
				/* Pointer to density table - tapes */
	MODESEL_TBL *dd_modesel_tbl;
				/* Mode	select table pointer - used */
				/* on open and recovery	*/
	U32	dd_flags;	/* Option flags	(NOSYNC,BBR, etc) */
	U32	dd_scsi_optcmds;/* Optional commands supported */
	U32	dd_ready_time;	/* Time	in seconds for powerup dev ready */
	u_short	dd_que_depth;	/* Device queue	depth for devices */
				/* which support command queueing */
	u_char	dd_valid;	/* Indicates which data	length */
				/* fields are valid */
	u_char	dd_inq_len;	/* Inquiry data	length for device */
	u_char	dd_req_sense_len;
				/* Request sense data length for */
				/* this	device */
	U32	dd_ref_count;	/* Number of references	to this	DEV_DESC */
	U32	dd_attribute_cnt;/* number of attributes created by default */
	DEV_ATTRIBUTE	*dd_attributes;
				/* linked list of attributes */
	struct dev_desc	*dd_forw;
	struct dev_desc	*dd_back;
				/* global DEV_DESC list	links */
	char	dd_vid[DDR_VID_LENGTH];
	char	dd_pid[DDR_PID_LENGTH];
	char	dd_rev[DDR_REV_LENGTH];
	U32	dd_sim_type;
	XPT_LOCK_DATA	dd_desc_lk;    
} DEV_DESC;

/* values for dd_sim_type - see SCSI_PROTO_SUBTYPE_XXX defines in cam_types.h */

#define	DTYPE_SHFT	24	/* Number of bytes to shift to	*/
				/* get the SCSI	device type bits */
				/* contained in	the dd_device_type */
				/* field of the	DEV_DESC structure */

/*
 * Maximum number of different devices described in the	CAM descriptor
 * table (cam_devdesc_tab).
 */
#define	MAX_DEVICE_DESC	256	/* DO NOT CHANGE		*/

/*
 * Maximun record/transfer size	in bytes. Used for DEC devices.
 * Most	SCSI tapes can exceed this value and some cannot.
 */
#define	DEC_MAX_REC	((1024 * 1024) * 16)	/* 16 Meg	*/

/*
 * Device disk class defines
 */
#define	SZ_HARD_DISK	0x0001		/* Hard	disks winchesters	*/
#define	SZ_CDROM	0x0002		/* Hard	disks winchesters	*/
#define	SZ_FLOP_3	0x0004		/* Floppy disk 3.5"		*/
#define	SZ_FLOP_5	0x0008		/* Floppy disk 5.25"		*/
#define	SZ_RAID		0x0010		/* RAID	target controller	*/

/*
 * Device tape class defines
 */
#define	SZ_TK_CLASS	0x0001		/* Tk50	tk30 class tapes	*/
#define	SZ_RDAT_CLASS	0x0002		/* RDAT	tlz04 class tapes	*/
#define	SZ_9TRK_CLASS	0x0004		/* 9 track tapes		*/
#define	SZ_QIC_CLASS	0x0008		/* Qic tapes tzk10		*/
#define	SZ_8MM_CLASS	0x0010		/* 8millimeter (exabytes)	*/
#define	SZ_3480_CLASS	0x0020		/* 3480	cartridge class		*/
#define	SZ_LOADER	0x0040		/* Is there a loader tied to	*/
					/* the unit that does not have	*/
					/* a separate id.		*/

/*
 * Defines for no tables.
 */
#define	NO_DENS_TAB	NULL		/* No density table		*/
#define	NO_MODE_TAB	NULL		/* No mode select table		*/

/*
 * Queue depth none (Unit does not support tagged commands)
 */
#define	SZ_NO_QUE	NULL		/* NO Queue (tagged commands	*/

/*
 * No block/sector size
 */
#define	SZ_NO_BLK	NULL		/* No block/sector size		*/

/*
 * Default ready time in seconds for the unit to come ready.
 * Load	tape/rewind, spin disk (dd_ready-time).
 */
#define	SZ_READY_DEF	45		/* 45 SECONDS			*/

/*
 * Optional commands supported by unit (dd_scsi_optcmds)
 */
#define	NO_OPT_CMDS	NULL		/* No optional commands		*/
#define	SZ_RW10		0x00000001	/* Read/write 10 byte cdb's	*/
#define	SZ_PREV_ALLOW	0x00000002	/* Prevent allow media removal	*/
#define	SZ_EXT_RESRV	0x00000004	/* Extent reserve/release	*/
#define	SZ_WR_VERI_PAR	0x00000008	/* Write werify	&parity	chk. for
					 * HSZ10 &15's vendor unique	*/

/* What	bits are left ?	*/
#define	SZ_ADDITIONAL_CMDS						\
	(~(SZ_RW10 | SZ_PREV_ALLOW | SZ_EXT_RESRV | SZ_WR_VERI_PAR))


/*
 * dd_valid defines
 */
#define	DD_REQSNS_VAL	0x01	/* indicates request sense length */
				/* in device descriptor	structure */
				/* is valid */
#define	DD_INQ_VAL	0x02	/* indicates inquiry data length */
				/* in device descriptor	structure */
				/* is valid */
/*
 * dd_flags defines
 */
#define	SZ_NO_FLAGS	0x00000000	/* No flags */
#define	SZ_BBR		0x00000001	/* Device allows bad block */
					/* recovery */
#define	SZ_NOSYNC	0x00000002	/* Device does not allow */
					/* synchronous data transfer */
#define	SZ_DYNAMIC_GEOM	0x00000010	/* Dev sizes can change, */
					/* DYNAMIC Geometry (RAID BOXES	*/
#define	SZ_NO_DISC	0x00000040	/* Device does not */
					/* allow disconnects */
#define	SZ_NO_TAG	0x00000080	/* Device does not allow */
					/* tagged queueing regardless */
					/* of inquiry data */
#define	SZ_REORDER	0x00000100	/* Allow the SIM to reorder CCBs */
#define	SZ_LONG_STO_RETRY 0x00000200	/* Do long select timeout retries */
#define	SZ_DISPERSE_QUE	0x00001000	/* Allow the que depth to be spread */
					/* across all LUNS for a given target */
#define	SZ_NOWIDE	0x00002000	/* Do not do Wide Transfers */
#define	SZ_WCE_CAPABLE	0x00004000	/* Capable of running w/ WCE */
#define	SZ_SPINDOWN_INCAPABLE 0x00008000  /* Incapable of Power	Management */

/* What	bits are left ?	*/
#define	SZ_ADDITIONAL_FLAGS						\
	(~(SZ_BBR | SZ_NOSYNC |	SZ_DYNAMIC_GEOM	| SZ_NO_DISC |		\
	  SZ_NO_TAG | SZ_REORDER | SZ_LONG_STO_RETRY |			\
	  SZ_DISPERSE_QUE | SZ_NOWIDE |	SZ_WCE_CAPABLE |		\
	  SZ_SPINDOWN_INCAPABLE	))


/************************************************************************
 * :tag20::	Peripheral Driver Working Set Definition
 ************************************************************************/

/*
 * Peripheral Driver Working Set Definition
 * The SCSI I/O	CCB will contain a pointer to the peripheral
 * driver working set for the CCB.  This will be used
 * in the following manner:
 */
typedef	  struct      pdrv_ws  {
	struct pdrv_ws	*pws_flink;	/* Linkage of working set CCBs */
	struct pdrv_ws	*pws_blink;	/* that	we have	queued */
	CCB_SCSIIO	*pws_ccb;	/* Pointer to this CCB.	*/
	U32		pws_flags;	/* Generic to driver */
	U32		pws_retry_cnt;	/* Retry count for this	request	*/
	u_char		*pws_pdrv;	/* Pointer to peripheral device	*/
					/* structure */
	u_char		pws_sense_buf[DEC_AUTO_SENSE_SIZE];
					/* Auto	sense buffer */
	struct pdrv_ws	*wait_flink;	/* Linkage of working set CCBs */
	void		*specific;	/* Pointer to the driver's specific
					 * structure */
	u_long		drv_spec_flags;	/* driver specific flags */
	u_long		Reserved[9];	/* Reserved */
} PDRV_WS;

#define	PDRV_WS_VERS		0x04	/* Please remember to increase
					 * The version number if you
					 * change the structure.
					 */
/*
 * Defines for the pws_flags field.
 */
#define	PWS_ACTIVE	0x01
#define	PWS_RETRY	0x02
#define	PWS_RECOVERY	0x04
#define	PWS_ACT_QUE	0x10	/* On the active que		*/
#define	PWS_PEND_QUE	0x20	/* On the pending queue		*/
#define	PWS_ABORT_QUE	0x40	/* On the abort	queue		*/
#define	PWS_2ND_TRY	0x80	/* Second time we've seen this CCB */

#define PWS_NO_DELAY           0x02000000  /* Callback function indicator
                                              not to delay - wakeup owner 
                                              Setting this pws flags allows
                                              a callback rotuine (written for
                                              this feature) to detect that
                                              this is a special request 
                                              and to not store onto recovery
                                              queues etc.  But to pass this
                                              ccb back to the caller (wakeup)
                                              */
#define PWS_IOB_DISCOVERY_CCB  0x04000000 /* Discovery ccb - what features
                                             commands does this device support
                                             used to prevent un-needed entries
                                             in the errors for IO Barriers */
#define	PWS_ASYNC_EXP	0x08000000   /*	For signaling an expected event	*/
#define	PWS_FATAL_ERR	0x40000000   /*	Fatal error on this ccb	give it	up */
#define	PWS_CALLBACK	0x80000000   /*	for signaling CCB returns	*/

/*
 * Forward and backward	link structure.
 */
typedef	struct pd_list {
	PDRV_WS	*flink;
	PDRV_WS	*blink;
} PD_LIST;


/************************************************************************
 * :tag25::	Peripheral Device Structure - CAM1
 ************************************************************************/
/*
 * This	structure will be allocated for	all devices which exist	in
 * the system. It and will be the anchor for the peripheral driver request
 * queue and will also contain the Inquiry data	obtained from a	GET DEVICE
 * TYPE	CCB.
 */
typedef	struct pdrv_device {
#define	PDRV_DEVICE_VERS	0x02	/* Please remember to increase
					 * The version number if you
					 * change the structure.
					 */
	PD_LIST	pd_active_list;	/* Forward active pointer of CCBs */
				/* which have been sent	to the XPT */
	U32	pd_active_ccb;	/* Number of active CCBs on queue */
	U32	pd_que_depth;	/* Tagged queue	depth -	indicates the */
				/* maximum number of commands the unit */
				/* can store internally	*/
	PD_LIST	pd_pend_list;	/* Forward active pointer of pending CCBs */
				/* which have not been sent to the XPT due */
				/* to a	full queue for tagged requests */
	U32	pd_pend_ccb;	/* Number of pending CCBs */
	dev_t	pd_dev;		/* CAM major/minor number */
	u_char	pd_bus;		/* SCSI	controller number */
	u_char	pd_target;	/* SCSI	target id */
	u_char	pd_lun;		/* SCSI	target lun */
	u_char	pd_unit;	/* Unit	number */
	U32	pd_log_unit;	/* Logical Unit	number */
	U32	pd_soft_err;	/* Number of soft errors */
	U32	pd_hard_err;	/* Number of hard errors */
	u_short	pd_soft_err_limit;/* Max no. of	soft errors to report */
	u_short	pd_hard_err_limit;/* Max no. of	hard errors to report */
	int	pd_dkn;		/* Used	for system statistics */
	u_char	pd_recovery_cnt; /* Error Recovery count which can go on in the
				   background Async notification */
	u_char	pd_fatal_rec;	/* Indication that we had fatal	recovery errors	*/
	U32	pd_flags;	/* Specific to peripheral drivers */
	u_char	pd_state;	/* Specific to peripheral drivers - can	*/
				/* be used for recovery	*/
	U32	pd_abort_cnt;	/* Specific to peripheral drivers - can	*/
				/* be used for recovery	*/
	U32	pd_cam_flags;	/* Used	to hold	the default settings */
				/* for the cam_flags field in CCBs */
	u_char	pd_tag_action;	/* Used	to hold	the default settings for */
				/* the cam_tag_action field of the SCSI	*/
				/* I/O CCB */
	u_char	pd_dev_inq[INQLEN];
				/* Inquiry data	obtained from GET */
				/* DEVICE TYPE CCB */
	U32	pd_ms_index;	/* Contains the	current	index into the */
				/* Mode	Select Table when sending Mode */
				/* Select data on first	open */
	DEV_DESC  *pd_dev_desc;	/* Pointer to our device descriptor */
	caddr_t	pd_specific;	/* Pointer to device specific info */
	u_short	pd_spec_size;	/* Size	of device specific info	*/
	caddr_t	pd_sense_ptr;	/* Pointer to the last sense data */
				/* bytes retrieved from	device */
	u_short	pd_sense_len;	/* Length of last sense	data */
	void	(*pd_recov_hand)();
				/* Specific to peripheral drivers - can	*/
				/* be used to point to the recovery */
				/* handler for the device */
	U32 pd_read_count;	/* Number of reads to device */
	U32 pd_write_count;	/* Number of writes to device */
	U32 pd_read_bytes;	/* Number of bytes read	from device */
	U32 pd_write_bytes;	/* Number of bytes written to device */
	dev_t pd_bmajor;	/* Block major number for loadables */
	dev_t pd_cmajor;	/* Char	major number for loadables */
	simple_lock_data_t	pd_lk_device;
				/* SMP lock for	the device */
}  PDRV_DEVICE;


#define	RETRY		1	/* Indicates that we are retrying a SCSI */
				/* I/O CCB which is already on the */
				/* peripheral driver queue */
#define	NOT_RETRY	0	/* Indicates that the CCB is not already */
				/* on the peripheral driver queue */

/************************************************************************
 * :tag50::	Peripheral Drive Unit Table
 ************************************************************************/
/*
 * There is one	unit table array whose size is the
 * maximum number of possible devices given the	maximum	SCSI
 * controllers for the system.	The pu_device field will be
 * filled in with a pointer to a CAM allocated peripheral
 * device structure at first open time of the device.
 */
typedef	struct pdrv_unit_elem {
#define	PDRV_UNIT_ELEM_VERS	0x01	/* Please remember to increase
					 * The version number if you
					 * change the structure.
					 */
	PDRV_DEVICE *pu_device;	/* Pointer to peripheral device	structure */
	u_short	pu_opens;	/* Total number	of opens against unit */
	u_short	pu_config;	/* Indicates whether the device	type */
				/* configured at this address */
	u_char	pu_type;	/* Device type - byte 0	from inquiry data */
	u_char	pu_exclusive;	/* Exclusive use indicator */
} PDRV_UNIT_ELEM;


/************************************************************************
 * :tag55::	PDRV_UNIT_INFO structure
 ************************************************************************/
/*
 * The PDRV_UNIT_INFO struct
 * has been added to allow us to expand	per unit infomation that would
 * be placed in	the PDRV_UNIT_ELEM.  Unfortunately, modifing the
 * PDRV_UNIT_ELEM struct will break binary compatability, defiling DEC
 * OSF1/CAM compatability, add nausea...
 */

typedef	struct pdrv_unit_info {
	lock_data_t lk_pu_open;	/* Open	Unit Lock Structure  */
} PDRV_UNIT_INFO;

/*
 * MAX_UNITS is only used in conjunction with the pdrv_unit_* arrays.
 * The arrays are no longer used except for 3rd party drivers and is
 * maintained for compatibility reasons. The arrays were not expanded
 * for handling > 64 shared busses.
 */
#define	MAX_UNITS	OLD_MAX_BUSSES * NDPS_8 * NLPT_8

/************************************************************************
 * :tag84::	PDU_UNIT_LOCK/UNLOCK - per-unit	SMP sleep lock.
 ************************************************************************/
/*
 * NEW SMP SAFE	locking	macros.	Use these if you want true SMP safety.
 *
 * The PDU_UNIT_LOCK/UNLOCK macro locks	PDRV_UNIT_ELEMs.  Rather than
 * locking the whole table with	a Spin (Simple)	lock, this lock	can be
 * taken on a per-unit basis.  Because this is a Sleep (Complex) lock,
 * it can be held for the duration of the Open operation and provide
 * true	SMP safty.
 */

#define	PDU_INIT_UNIT_LOCK( pdi	)				\
{								\
    ulock_setup((lock_t) &(pdi)->lk_pu_open, cam_pd_unit_li, TRUE); \
}

#define	PDU_UNIT_LOCK( pdi, saveipl )				\
{								\
    saveipl = splbio();						\
    ulock_write((lock_t) &(pdi)->lk_pu_open);			\
}

#define	PDU_UNIT_UNLOCK( pdi, saveipl )				\
{								\
    ulock_done((lock_t)	&(pdi)->lk_pu_open);			\
    (void)splx((saveipl));					\
}

/************************************************************************
 * :tag90::	The IPL/SMP locking Macros for the buf structure pool.
 ************************************************************************/


/*****************************************************************************
 * :tag92::	The IPL/SMP locking Macros for the peripheral device structure.
 *****************************************************************************/

#define	PDRV_INIT_LOCK(	pd )					\
{								\
    usimple_lock_setup(	(simple_lock_t)(&(pd)->pd_lk_device), cam_pd_device_li );	\
}

#define	PDRV_IPLSMP_LOCK( pd, lk_type, saveipl )		\
{								\
    saveipl= splbio();						\
    CAM_SPINLOCK( (simple_lock_t)(&(pd)->pd_lk_device) );	\
}

#define	PDRV_IPLSMP_UNLOCK( pd,	saveipl	)			\
{								\
    CAM_SPINUNLOCK( (simple_lock_t)(&(pd)->pd_lk_device) );	\
    (void)splx(saveipl);					\
}

#define	PDRV_SMP_SLEEP(	chan, pri, pd )				\
    CAM_SLEEP((chan), (pri), (simple_lock_t)(&(pd)->pd_lk_device))	\

#define	PDRV_SMP_SLEEPUNLOCK( chan, pri, pd )			\
    CAM_SLEEP_SPINUNLOCK((chan), (pri),	(simple_lock_t)(&(pd)->pd_lk_device)) \

#define	PDRV_SMP_LOCK( pd )					\
    CAM_SPINLOCK( (simple_lock_t)(&(pd)->pd_lk_device) );	\

#define	PDRV_SMP_UNLOCK( pd )					\
   CAM_SPINUNLOCK( (simple_lock_t)(&(pd)->pd_lk_device)	);	\

#define	PDRV_LOWER_IPL(	spl )					\
    splx( (spl)	);						\

/************************************************************************
 * :tag96::	The IPL/SMP locking Macros for the data	buffer allocation.
 ************************************************************************/

#define	CCMN_DATA_INIT_LOCK()					\
{								\
usimple_lock_setup( (simple_lock_t)&lk_ccmn_data_pool, cam_ccmn_data_pool_li );	\
}

#define	CCMN_DATA_IPLSMP_LOCK( lk_type,	saveipl	)		\
{								\
    saveipl = splbio();						\
    CAM_SPINLOCK( &lk_ccmn_data_pool );				\
}

#define	CCMN_DATA_IPLSMP_UNLOCK( saveipl )			\
{								\
    CAM_SPINUNLOCK( &lk_ccmn_data_pool );			\
    (void)splx((saveipl));					\
}

#define	CCMN_DATA_WAIT(saveipl)					\
{								\
    ccmn_data_alloc.alloc_wait_cnt++;				\
    if(	ccmn_data_alloc.alloc_wait_cnt == 1 ) {			\
	CCMN_DATA_IPLSMP_UNLOCK((saveipl));				\
	ccmn_sched_call((void(*)(void *))ccmn_get_dbuf,	NULL, (2 * hz));\
	CCMN_DATA_IPLSMP_LOCK(LK_RETRY, (saveipl));			\
    }								\
    assert_wait((vm_offset_t)&ccmn_data_alloc.alloc_wait_cnt, FALSE);	\
    CCMN_DATA_IPLSMP_UNLOCK((saveipl));				\
    thread_block();						\
    CCMN_DATA_IPLSMP_LOCK(LK_RETRY, (saveipl));			\
    ccmn_data_alloc.alloc_wait_cnt--;				\
}

/************************************************************************
 * :tag110::	Macros to clear	ccb, release ccb queue
 ************************************************************************/

/*
 * Clear the fields in the CCB which will be filled in on a retry
 * of the CCB.
 */
#define	CLEAR_CCB(ccb)			\
{					\
    (ccb)->cam_ch.cam_status = 0;	\
    (ccb)->cam_scsi_status = 0;		\
    (ccb)->cam_resid = 0;		\
    (ccb)->cam_sense_resid = 0;		\
    ((PDRV_WS *)ccb->cam_pdrv_ptr)->pws_flags &= ~PWS_CALLBACK;	\
}

/*
 * Issue the Release SIM Queue CCB.
 */
#define	RELEASE_QUEUE(pd)  {					\
		CCB_RELSIM *rel_ccb;				\
		rel_ccb	= ccmn_rsq_ccb_bld((pd)->pd_dev, 0L);	\
		ccmn_rel_ccb((CCB_HEADER *)rel_ccb);		\
}								\

/*
 * Issue the Release SIM Queue CCB if the CAM status field of the
 * ccb indicates that the queue	is frozen
 */
#define	CHK_RELEASE_QUEUE(pd, ccb)				\
	if( (ccb)->cam_ch.cam_status & CAM_SIM_QFRZN )	{	\
		RELEASE_QUEUE((pd));				\
		(ccb)->cam_ch.cam_status &= ~CAM_SIM_QFRZN;	\
	}							\

/************************************************************************
 * :tag120::	DEV_DESC lock macros
 ************************************************************************/

#ifdef KERNEL


/* Kernel-callable DDR interfaces */
DEV_DESC *	cam_ddr_get_dev_desc(ALL_INQ_DATA *inqp,
				U32 scsi_devtype, U32 sim_type);
void		cam_ddr_release_dev_desc(DEV_DESC *ddp);
int		ddr_find_attr(DEV_DESC *dp, char *name,	char *buf,
				int buf_len, int *attrlen);

#endif /* KERNEL */


/*
 * The following macros	will obtain information	form the major/minor
 * device number.
 *
 *	GETUNIT()  - returns unit_t  (bits 6 - 19 of dev_t)
 *	GETDEVS()  - returns devs_t  (bits 0 - 5 of dev_t)
 *
 *	----------------------------------------------
 *	| UNIT NUMBER		     | DEV SPECIFIC  |
 *	----------------------------------------------
 * Bits:|19	14|13	    10|9    6|5		    0|
 *	----------------------------------------------
 *	| Bus No. | Target Id |	LUN  | Partition No. |
 *	|	  |	      |	     | or Density    |
 *	----------------------------------------------
 *
 */
#define	BUS_SHIFT		8
#define	NEW_BUS_MASK		0x3F
#define	BUS_MASK		0x3F
#define	DEV_BUS_ID(dev)		(((GETUNIT(dev)) >> BUS_SHIFT) & BUS_MASK)

#define	TARGET_SHIFT		4
#define	TARGET_MASK		0x07	/* change to 0x0F */
#define	DEV_TARGET(dev)		(((GETUNIT(dev)) >> TARGET_SHIFT) & TARGET_MASK)

#define	LUN_SHIFT		0
#define	LUN_MASK		0x07	/* change to 0x0F */
#define	DEV_LUN(dev)		((GETUNIT((dev)) >> LUN_SHIFT) & LUN_MASK)

/*
 * The following lines should be replaced by this line when the	proper
 * number of bits are used to define the unit number:
 * #define DEV_UNIT(dev)		(GETUNIT((dev))	& UNIT_MASK)
 */
#define	UNIT_MASK		0xFF
#define	UNIT_BUS_MASK		0x3F00
#define	UNIT_TARGET_MASK	0x70
#define	UNIT_LUN_MASK		0x7
#define	DEV_UNIT(dev)		( ((GETUNIT((dev)) & UNIT_BUS_MASK) >> 2) \
				| ((GETUNIT((dev)) & UNIT_TARGET_MASK) >> 1) \
				| (GETUNIT((dev)) & UNIT_LUN_MASK) ) \

/*
 * The UBA_UNIT_TO_DEV_UNIT() macro assumes that the argument uses bits	0-2
 * for the lun,	bits 3-5 for target id,	and bits 6-7 for bus number. However,
 * the dev_t breakdown of the unit number protion is bits 0-3 for lun,
 * bits	4-7 for	target id and bits 8-11	for bus	number.	This macro will
 * return the unit number portion of the minor number.
 */
#define	UBA_BUS_MASK		0xFC0	/* bits	6-7 */
#define	UBA_TARGET_MASK		0x38	/* bits	3-5 */
#define	UBA_LUN_MASK		0x7	/* bits	0-2 */
#define	UBA_UNIT_TO_DEV_UNIT(attach)				\
	( ((attach->unit & UBA_BUS_MASK) << 2) \
	| ((attach->unit & UBA_TARGET_MASK) << 1) \
	| (attach->unit	& UBA_LUN_MASK)	)

#define	MAKE_UNIT(bus, target, lun)			\
	((((bus) & BUS_MASK) <<	BUS_SHIFT) |		\
	(((target) & TARGET_MASK) << TARGET_SHIFT) |	\
	(((lun)	& LUN_MASK) << LUN_SHIFT))		\

/*
 * CAM-3 Macros	for logical ids
 */

#define	GET_LOGICAL(x)		GETUNIT((x))

/*
 * Convert address to something	console	needs
 */
#define	ADDR_TO_UNIT(xbus, xtarget, xlun)			\
    DEV_UNIT(((((xbus)&0x3F)<<8) | (((xtarget)&0xF)<<4)	| ((xlun)& 0xF)) << 6)

/*
 * Obtain the unit table entry for this	major/minor device number.
 */
#define	GET_PDRV_UNIT_ELEM(dev)					\
(								\
	&pdrv_unit_table[DEV_UNIT((dev))]			\
)

#define	GET_PDRV_UNIT_INFO(dev)					\
(								\
	&pdrv_unit_info[DEV_UNIT((dev))]			\
)

/*
 * Obtain the peripheral device	structure pointer for this major/minor 
 * device number.
 */
#define	GET_PDRV_PTR(dev)					\
(								\
	pdrv_unit_table[DEV_UNIT((dev))].pu_device		\
)


#define	CCMN_EXCLUSIVE	0x1

#define	DEV_TYPE_MASK	0x1f	/* first byte of inquiry data */

/*
 * The following are the canned	category values	returned from
 * ccmn_ccb_status() for the returned CAM status values.
 */
#define	CAT_INPROG	0	/* The request is in progress */
#define	CAT_CMP		1	/* Request has completed successfully */
#define	CAT_CMP_ERR	2	/* Request has completed with error */
#define	CAT_ABORT	3	/* Request has been aborted or */
				/* terminated */
#define	CAT_BUSY	4	/* CAM is busy */
#define	CAT_NO_DEVICE	5	/* No device at	requested address */
#define	CAT_DEVICE_ERR	6	/* Bus/device problems */
#define	CAT_BAD_AUTO	7	/* Invalid auto	sense data */
#define	CAT_CCB_ERR	8	/* Invalid CCB */
#define	CAT_RESET	9	/* Bus/device has detected a reset */
#define	CAT_SCSI_BUSY	10	/* SCSI	is busy	*/
#define	CAT_UNKNOWN	11	/* Invalid CAM status */

#define	CAT_MUNSA_REJECT 12	/* MUNSA is failing IO after reset */

#define	PROBE_SUCCESS	1	/* Success status during probe process.	*/
#define	PROBE_FAILURE	0	/* Failure status during probe process.	*/

/*
 * !! CAM-1 ONLY !!
 * Get the sense data size for the device by checking whether it is
 * defined in the device descriptor entry.
 * !! CAM-3 ALLOCATION !!
 * is 255 bytes	(SENSE_BUF_LEN3) and sense_len member in ccb must be
 * set to that value.
 */
#define	GET_SENSE_SIZE(pd)				\
	( (pd->pd_dev_desc->dd_valid & DD_REQSNS_VAL)	\
	  ? pd->pd_dev_desc->dd_req_sense_len		\
	  : DEC_AUTO_SENSE_SIZE)			\

/* Retrieve CAM	status from CCB	*/
#define	CAM_STATUS(ccb)		((ccb)->cam_ch.cam_status & CAM_STATUS_MASK)

/*
 * Retrieve sense key from CCB
 */
#define	SENSEKEY(c3cb)	(((ALL_REQ_SNS_DATA *)(c3cb)->cam_sense_ptr)->sns_key)

/*
 * Convert the bytes pointed to	by ptr into a long value.
 */
#define	BTOL(ptr, long_val) {			\
	char *p	= (char	*)(ptr);		\
	union	{				\
		unsigned char	c[4];		\
		U32		l;		\
	}tmp;					\
	tmp.c[3] = *p++;			\
	tmp.c[2] = *p++;			\
	tmp.c[1] = *p++;			\
	tmp.c[0] = *p++;			\
	(long_val) = tmp.l;			\
}

/*
 * Convert long	value to bytes pointed to by ptr
 */
#define	LTOBytes(ptr, long_val)	{		\
	char *p	= (char	*)(ptr);		\
	union	{				\
		unsigned char	c[4];		\
		U32		l;		\
	}tmp;					\
	tmp.l =	long_val;			\
	*p++ = tmp.c[3];			\
	*p++ = tmp.c[2];			\
	*p++ = tmp.c[1];			\
	*p++ = tmp.c[0];			\
}

/************************************************************************
 * :tag200::	Prototypes of the pdrv_common.c	routines
 ************************************************************************/
void		ccmn_init(void);
I32		ccmn_open_unit(dev_t dev, U32 scsi_dev_type, U32 flag,
		    U32	dev_size);
void		ccmn_release_dev_desc(PDRV_DEVICE *pd);
void		ccmn_close_unit(dev_t dev);
U32		ccmn_send_ccb(PDRV_DEVICE *pd, CCB_HEADER *ccb,	u_char retry);
void		ccmn_rem_ccb(PDRV_DEVICE *pd, CCB_SCSIIO *ccb);
void		ccmn_rel_ccb(CCB_HEADER	 *ccb);
U32		ccmn_abort_que(PDRV_DEVICE *pd);
void		ccmn_term_que(PDRV_DEVICE *pd);
CCB_HEADER *	ccmn_get_ccb(dev_t dev,	u_char func_code,
		    U32	cam_flags, u_short ccb_len);
CCB_SCSIIO *	ccmn_io_ccb_bld(dev_t dev, u_char *data_addr,
		    U32	data_len, u_short sense_len, U32 cam_flags,
		    void (*comp_func)(), u_char	tag_action,
		    U32	 timeout_val, struct buf *bp);
CCB_GETDEV *	ccmn_gdev_ccb_bld(dev_t	dev, U32 cam_flags, u_char *inq_addr);
CCB_SETDEV *	ccmn_sdev_ccb_bld(dev_t	dev, U32 cam_flags, U32	dev_type);
CCB_SETASYNC *	ccmn_sasy_ccb_bld(dev_t	dev, U32 cam_flags, U32	async_flags,
		    void (*callb_func)(), u_char *buf, u_char buflen);
CCB_RELSIM *	ccmn_rsq_ccb_bld(dev_t dev, U32	cam_flags);
CCB_PATHINQ *	ccmn_pinq_ccb_bld(dev_t	dev, U32 cam_flags);
CCB_ABORT *	ccmn_abort_ccb_bld(dev_t dev, U32 cam_flags,
		    CCB_HEADER *abort_ccb);
CCB_TERMIO *	ccmn_term_ccb_bld(dev_t	dev, U32 cam_flags,
		    CCB_HEADER *term_ccb);
CCB_RESETDEV *	ccmn_bdr_ccb_bld(dev_t dev, U32	cam_flags);
CCB_RESETBUS *	ccmn_br_ccb_bld(dev_t dev, U32 cam_flags);
CCB_SCSIIO *	ccmn_tur(PDRV_DEVICE *pd, u_short sense_len, U32 cam_flags,
		    void (*comp_func)(), u_char	tag_action, U32	timeout_val);
CCB_SCSIIO *	ccmn_start_unit(PDRV_DEVICE *pd, u_short sense_len,
		    U32	cam_flags, void	(*comp_func)(),	u_char tag_action,
		    U32	timeout_val);
CCB_SCSIIO *	ccmn_mode_select(PDRV_DEVICE *pd, u_short sense_len,
		    U32	cam_flags, void	(*comp_func)(),	u_char tag_action,
		    U32	timeout_val, unsigned ms_index);
U32		ccmn_ccb_status(CCB_HEADER *ccb);
struct buf *	ccmn_get_bp(void);
void		ccmn_rel_bp(struct buf *bp);
int		ccmn_send_ccb_wait(PDRV_DEVICE *pd, CCB_HEADER *ccb,
		    u_char retry, int sleep_pri);
int		ccmn_ccbwait(CCB_SCSIIO	*ccb, int priority);
int		ccmn_SysSpecialCmd(dev_t dev, int cmd, caddr_t data,
		    int	flags, CCB_SCSIIO *ccb,	int sflags);
int		ccmn_DoSpecialCmd( dev_t dev, u_int cmd, caddr_t data,
		    int flags, CCB_SCSIIO *ccb, u_int sflags);
void		ccmn_errlog(char *func_str, char *opt_str,
		    U32	flags, CCB_HEADER *ccb,	dev_t dev,
		    void *unused);
int		ccmn_check_idle(U32 start_unit,	U32 num_units,
		    dev_t cmajor, dev_t	bmajor,	U32 spec_size);
struct controller *	ccmn_find_ctrl(dev_t dev);
struct device *		ccmn_find_device(struct	controller *ctrl, dev_t	dev);
int		ccmn_attach_device(dev_t dev, caddr_t dev_type,
		    caddr_t dev_name);
void		ccmn_disperse_que(dev_t	dev, U32 que_depth);
I32		setup_pdrv_device (CCB_GETDEV *ccb, PDRV_DEVICE	*pd,
		    U32	scsi_dev_type, U32 dev_size, dev_t dev);
void		ccmn_get_devinfo_scsidata(PDRV_DEVICE *pd, device_info_t *devip);
U32		ccmn_scan_lun(dev_t dev);

void	ccmn_rel_ccb (
	CCB_HEADER  *ccb	    /* ccb pointer			*/
	);

struct buf *ccmn_get_bp	(void);

void	ccmn_rel_bp (
	struct buf *bp		    /* strategy	request	struct		*/
	);

void *	ccmn_get_dbuf (
	U32 size		    /* requested buffer	size		*/
	);

void	ccmn_rel_dbuf(
	void *addr,		    /* buffer address			*/
	U32	size		    /* buffer size			*/
	);

U32	ccmn_ccb_status	(
	CCB_HEADER	*ccb	    /* ccb pointer			*/
	);

#ifdef __cplusplus
}
#endif

#endif /* _PDRV_	*/
