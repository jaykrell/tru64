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
 * @(#)$RCSfile: dec_common.h,v $ $Revision: 1.1.15.2 $ (DEC) $Date: 2002/05/30 23:16:00 $
 */

#ifndef	_DEC_COMMON_INCL_
#define	_DEC_COMMON_INCL_

#ifdef __cplusplus
extern "C" {
#endif


/* ********************************************************************* *
 * 
 *     This header defines common macros, data structures, etc that
 *     are specific to Digital Equipment's CAM implementation.
 *
 *     This header is designed to be used by both Peripheral Drivers
 *     and Digital's XPT implementation.
 * 
 * ********************************************************************* */

#include <io/common/iotypes.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <io/common/devio.h>
#include <io/common/devdriver.h>
#include <sys/malloc.h>
#include <ksm/ksm.h>

#include <io/cam/dec_cam.h>		/* General DEC definitions */
#include <io/cam/cam3.h>		/* CAM3	API */
#include <io/cam/cam1.h>		/* CAM1	API */
#include <io/cam/scsi_all.h>
#include <io/cam/cam_logger.h>
#include <io/cam/cam_errlog.h>

/* ---------------------------------------------------------------------- * 
 *   Some generic Digital-specific utility routines for	cam.
 * ---------------------------------------------------------------------- */

I32		cam_inisr(void);
I32		cam_at_boottime(void);


/* ---------------------------------------------------------------------- * 
 *   Macros for	manipulating port/target/lun values in			  * 
 *     CONNECTION_ID's and TRANSLATION structures			  * 
 * ---------------------------------------------------------------------- */

/* access via TRANSLATION structure */
#define	T_FLAGS(trans)	(trans)->connection_id.conn_flags
#define	T_PORT(trans)	(*(CAM_U32 *)(&(trans)->connection_id.port_id))
#define	T_TARGET(trans)	(*(CAM_U64 *)(trans)->connection_id.addr_spec1)
#define	T_LUN(trans)	(*(CAM_U64 *)(trans)->connection_id.addr_spec2)

/* access via CONNECTION_ID structure */
#define	C_FLAGS(conn)	(conn)->conn_flags
#define	C_PORT(conn)	(*(CAM_U32 *)(&(conn)->port_id))
#define	C_TARGET(conn)	(*(CAM_U64 *)(conn)->addr_spec1)
#define	C_LUN(conn)	(*(CAM_U64 *)(conn)->addr_spec2)


/* ---------------------------------------------------------------------- * 
 *		CAM1/CAM3 interchange macros				  * 
 * ---------------------------------------------------------------------- */

/*
 * CAM3_CCB_HEADER
 * Macro evaluates to TRUE if header structure denotes CAM-3 ccb
 * Argument - pointer to the CCB_HEADER	/ CCB_HEADER3
 */

#define	CAM3_CCB_HEADER(cch)	\
	(((CCB_HEADER *)cch)->cam_func_code == XPT_CAM3_CCB )

/*
 * CAM_HEADER_SIZE
 * Macro returns size of the header (CAM-3 or CAM-1)
 * Argument - pointer to the ccb header
 */

#define	CAM_HEADER_SIZE(cch)	\
    ((CAM3_CCB_HEADER(cch)) ? sizeof(CCB_HEADER3) : sizeof(CCB_HEADER))

/*
 * CAM_GET_CB_PTR
 * Macro returns "cb" as a pointer to the ccb portion following
 * the header ("ccb proper").
 * Arguments: cch  - pointer to the ccb (CCB_HEADER /	CCB_HEADER3)
 *	      cb   - pointer to the CCB proper or CCB body.
 *	      cast - typecast of the ccb proper structure
 */
#define	CAM_GET_CB_PTR(cch, cb,	cast)		\
{						\
    if (CAM3_CCB_HEADER(cch))			\
	(cb) = (cast *)&((CCB_GENERIC3 *)cch)->cam_ccb_body;	\
    else							\
	(cb) = (cast *)&((CCB_GENERIC *)cch)->cam_ccb_body;	\
}

/*
 * CAM_GET_CAM_FLAGS
 * Macro returns the value in the cam_flags field of the CCB header
 * pointed to by cch.
 * Arguments - cch   - pointer to the ccb (CCB_HEADER /	CCB_HEADER3)
 */
#define	CAM_GET_CAM_FLAGS(cch) \
    ( CAM3_CCB_HEADER(cch) ? \
       ((CCB_HEADER3 *)cch)->cam_flags: \
       ((CCB_HEADER *)cch)->cam_flags)	\

/*
 * CAM_SET_CAM_FLAGS
 * Macro ORs the value in "flags" into the cam_flags field
 * in the CCB header pointed to by cch.
 * Arguments - cch   - pointer to the ccb (CCB_HEADER /	CCB_HEADER3)
 *	     - flags - value to OR into the cam_flags field
 */
#define	CAM_SET_CAM_FLAGS(cch, flags) \
{ \
    if (CAM3_CCB_HEADER(cch)) \
       ((CCB_HEADER3 *)cch)->cam_flags |= flags;\
    else \
       ((CCB_HEADER *)cch)->cam_flags |= flags;	\
}

/*
 * CAM_CLR_CAM_FLAGS (complement to CAM_SET_CAM_FLAGS)
 * Macro CLEARs the bit mask specified by the "flags" value
 * by ANDing the existing cam_flags field in the CCB header
 * pointed to by cch, with the NOT of the value "flags".
 * Arguments - cch   - pointer to the ccb (CCB_HEADER /	CCB_HEADER3)
 *	     - flags - value specifying the bits to clear  into the cam_flags field
 */

#define	CAM_CLR_CAM_FLAGS(cch, flags) \
{ \
    if (CAM3_CCB_HEADER(cch)) \
       ((CCB_HEADER3 *)cch)->cam_flags &= ~flags;\
    else \
       ((CCB_HEADER *)cch)->cam_flags &= ~flags; \
}

/* ---------------------------------------------------------------------- * 
 *		General	SMP spin lock					  * 
 * ---------------------------------------------------------------------- */

/*
 * General SMP lock structure with internal storage for	saved IPL.
 * That	enables	transfer of the	lock state in and out of functions.
 * Since we have a circular reference condition	between	pdrv.h
 * and xpt.h defines, we use a conditional.
 */
typedef	struct xpt_lock_data {
    simple_lock_data_t	xpt_lk_data;
    U32			xpt_saveipl;
} XPT_LOCK_DATA;



/*
 * General SMP locking macros
 * !NOTE! Lock pointer argument	must point to
 * the XPT_LOCK_DATA structure.
 */

#define	XPT_INIT_LOCK(lock_ptr,	lk_info_ptr)	\
{						\
	simple_lock_setup(&(lock_ptr)->xpt_lk_data, (lk_info_ptr)); \
}

#define	XPT_TERMINATE_LOCK(lock_ptr)		\
{						\
	simple_lock_terminate(&(lock_ptr)->xpt_lk_data); \
}

#define	XPT_SPINLOCK(lock_ptr)			\
{						\
	simple_lock(&(lock_ptr)->xpt_lk_data);	\
}

#define	XPT_SPINUNLOCK(lock_ptr)		\
{						\
	simple_unlock(&(lock_ptr)->xpt_lk_data);	\
}

#define	XPT_LOCK(lock_ptr)			\
{						\
	U32 spl;				\
	spl = splbio();				\
	XPT_SPINLOCK(lock_ptr)			\
	(lock_ptr)->xpt_saveipl	= spl;		\
}

#define	XPT_UNLOCK(lock_ptr)			\
{						\
	U32 spl;				\
	spl = (lock_ptr)->xpt_saveipl;		\
	XPT_SPINUNLOCK(lock_ptr)		\
	(void)splx(spl);			\
}

/* ---------------------------------------------------------------------- * 
 * Locality context ie. Rad
 * ---------------------------------------------------------------------- */

typedef struct locality_context
{
    U32    rad_id;	/* RAD ID */
    U32    cpu;		/* CPU number  - not used yet */
} LOCALITY_CONTEXT;


/* ---------------------------------------------------------------------- * 
 *		CAM_SCSI_BUS structure					  * 
 * ---------------------------------------------------------------------- */

/*
 * TARGET LUN SCAN SYNCHRONIZATION structure 
 */

typedef struct tl_scan_sync_q {
  struct tl_scan_sync_q *flink; 
  struct tl_scan_sync_q *blink;
} TL_SCAN_SYNC_Q;

typedef struct tl_scan_sync {
  TL_SCAN_SYNC_Q q;        /* MUST BE first item in structure!!! */
  U64 target;                 /* target being scannned */
  U64 lun;                    /* lun being scanned */
  U64 sleepers;               /* number of sleeping threads waiting to scan */
} TL_SCAN_SYNC;

/*
 * "BUS" related information
 */
typedef	struct cam_scsi_bus {
    U64			max_targets;
    U64			max_luns;
    U64			dev_spinup_cnt;
    XPT_LOCK_DATA	cbus_lock;    
    U32			sim_cam_type;	/* cam-1 or cam-3 or ??? */
    U32			sim_type;	/* detail - parallel, ide, fc, ... */
    LOCALITY_CONTEXT    locality_context;
    U32			bus_num;
    U32			edt_flags;
    U32			edt_scan_count;
    U32			reserved;
    void		*tgt_list;	/* target (and luns) attached to bus */
    XPT_LOCK_DATA	edt_lock;
    TL_SCAN_SYNC_Q  edt_scan_sync; /*queue of current edt scans in progress */
                       /* use CBUS_LOCK to synchronize access to this queue */
} CAM_SCSI_BUS;


extern struct lockinfo *cam_bus_li;

#define	INIT_SCSI_BUS_LOCK(cbus)				\
{								\
    XPT_INIT_LOCK( &(cbus)->cbus_lock, cam_bus_li);		\
}

#define	CBUS_SPINLOCK(cbus)					\
{								\
    XPT_SPINLOCK( &(cbus)->cbus_lock );				\
}

#define	CBUS_SPINUNLOCK(cbus)					\
{								\
    XPT_SPINUNLOCK( &(cbus)->cbus_lock );			\
}

#define	CBUS_LOCK(cbus)						\
{								\
    XPT_LOCK( &(cbus)->cbus_lock );				\
}

#define	CBUS_UNLOCK(cbus)					\
{								\
    XPT_UNLOCK( &(cbus)->cbus_lock );				\
}

#define	CBUS_SLEEPUNLOCK( cbus )				\
{								\
    int spl_val = (cbus)->cbus_lock.xpt_saveipl;		\
    assert_wait(((vm_offset_t)(cbus)), 0);			\
    mpsleep((void *)NULL, PRIBIO, "CAM BUS", 0,			\
    	    (void *)(&((cbus)->cbus_lock.xpt_lk_data)),		\
	   (MS_LOCK_NO_RELOCK|MS_LOCK_SIMPLE));			\
    splx(spl_val);						\
}

#define	CBUS_SLEEP( cbus )					\
{								\
    mpsleep((cbus), PRIBIO, "CAM BUS", 0, (void	*)(&((cbus)->cbus_lock)), \
	   (MS_LOCK_NO_RELOCK|MS_LOCK_SIMPLE));			\
}

#define	CBUS_WAKEUP( cbus )					\
{								\
    wakeup((cbus));						\
}

/* ---------------------------------------------------------------------- * 
 * SCSI	I/O Request CCB
 * DCB_SCSIIO &	DCB_SCSIIO3 and	related	ccb body structure CB_SCSIIO
 * ---------------------------------------------------------------------- */

/*
 * CCB body common to CAM-1 & CAM-3 ccb
 */
typedef	struct cb_scsiio
{
    void   *cam_pdrv_ptr;	/* Ptr used by the Peripheral driver	*/
    void   *cam_next_ccb;	/* Ptr to the next CCB for action	*/
    void   *cam_req_map;	/* Ptr for mapping info	on the Req.	*/
    void  (*cam_cbfcnp)();	/* Callback on completion function	*/
    void   *cam_data_ptr;	/* Pointer to the data buf/SG list	*/
    CAM_U32 cam_dxfer_len;	/* Data	xfer length			*/	
    void   *cam_sense_ptr;	/* Pointer to the sense	data buffer	*/
    CAM_U8  cam_sense_len;	/* Num of bytes	in the Autosense buf	*/
    CAM_U8  cam_cdb_len;	/* Number of bytes for the CDB		*/
    CAM_U16 cam_sglist_cnt;	/* Num of scatter gather list entries	*/
    CAM_U32 cam_sort_vu_field;	/* Value used by SIM to	sort on	- CAM-1	*/
				/* Vendor unique field - CAM-3		*/
    CAM_U8  cam_scsi_status;	/* Returned scsi device	status		*/
    CAM_U8  cam_sense_resid;	/* Autosense resid length: 2's comp	*/
    CAM_U8  cam_osd_rsvd1[2];	/* OSD Reserved	field, for alignment	*/
    CAM_S32 cam_resid;		/* Transfer residual length: 2's comp	*/
    CDB_UN  cam_cdb_io;		/* Union for CDB bytes/pointer		*/
    CAM_U32 cam_timeout;	/* Timeout value			*/
    CAM_U8 *cam_msg_ptr;	/* Pointer to the message buffer	*/
    CAM_U16 cam_msgb_len;	/* Num of bytes	in the message buf	*/
    CAM_U16 cam_vu_flags;	/* Vendor unique flags			*/
    CAM_U8  cam_tag_action;	/* What	to do for tag queuing		*/
    CAM_U8  reserved[3];	/* Alignment	*/
} CB_SCSIIO;

/*
 * CAM-1 ccb aligned with CCB_SCSIIO structure
 */
typedef	struct dcb_scsiio
{
    CCB_HEADER cam_ch;		/* Header information fields		*/
    CB_SCSIIO  scsiio_body;
    u_char cam_sim_priv[ SIM_PRIV ]; /*	SIM private data area	*/
} DCB_SCSIIO;

/*
 * CAM-3 ccb aligned with CCB_SCSIIO3 structure
 */
typedef	struct dcb_scsiio3
{
    CCB_HEADER3	cam_ch;		/* Header information fields		*/
    CB_SCSIIO	scsiio_body;
    CAM_U32	cam_tag_id;	/* Tag	ID	*/
    CAM_U32	cam_initiator_id[4]; /*	Initiator ID target operation	*/
    CAM_U32	cam_sim_sense[SIM_SENSE_LEN3]; /* Working area for SIM sense data */
    CAM_U8	cam_sense_buf[SENSE_BUF_LEN3];	/* Sense data buffer	*/
} DCB_SCSIIO3;

/* ---------------------------------------------------------------------- * 
 * Get device type CCB
 * DCB_GETDEV &	DCB_GETDEV3 and	related	ccb body structure CB_SCSIIO
 * ---------------------------------------------------------------------- */

typedef	struct cb_getdev
{
    char  *cam_inq_data;	/* Ptr to the inquiry data space */
    CAM_U8 cam_pd_type;		/* Periph device type from the TLUN */
} CB_GETDEV;

typedef	struct dcb_getdev
{
    CCB_HEADER cam_ch;		/* Header information fields */
    CB_GETDEV  getdev_body;
} DCB_GETDEV;

typedef	struct dcb_getdev3
{
    CCB_HEADER3	cam_ch;		/* Header information fields */
    CB_GETDEV	getdev_body;
} DCB_GETDEV3;

/* ---------------------------------------------------------------------- * 
 * Set Async Callback CCB
 * DCB_SETASYNC	& DCB_SETASYNC3	and related ccb	body structure CB_SCSIIO
 * ---------------------------------------------------------------------- */

typedef	struct cb_setasync
{
    CAM_U32 cam_async_flags;	/* Event enables for Callback resp */
    void (*cam_async_func)();	/* Async Callback function address */
    CAM_U8 *pdrv_buf;		/* Buffer set aside by the Per.	drv */
    CAM_U8 pdrv_buf_len;	/* The size of the buffer */
    void *pdrv_specific_ptr;	/* Pointer to a	driver specific		*/
				/*  structure				*/
} CB_SETASYNC;

typedef	struct dcb_setasync
{
    CCB_HEADER cam_ch;		/* Header information fields */
    CB_SETASYNC	setasync_body;
} DCB_SETASYNC;

typedef	struct dcb_setasync3
{
    CCB_HEADER3	cam_ch;		/* Header information fields */
    CB_SETASYNC	setasync_body;
} DCB_SETASYNC3;

/* ---------------------------------------------------------------------- * 
 * Set Device Type CCB
 * DCB_SETDEV &	DCB_SETDEV3 and	related	ccb body structure CB_SCSIIO
 * ---------------------------------------------------------------------- */

typedef	struct cb_setdev
{
    CAM_U8 cam_dev_type;	/* Val for the dev type	field in EDT */
} CB_SETDEV;

typedef	struct dcb_setdev
{
    CCB_HEADER cam_ch;		/* Header information fields */
    CB_SETASYNC	setdev_body;
} DCB_SETDEV;

typedef	struct dcb_setdev3
{
    CCB_HEADER3	cam_ch;		/* Header information fields */
    CB_SETASYNC	setdev_body;
} DCB_SETDEV3;

/* ---------------------------------------------------------------------- * 
 * Abort XPT request CCB
 * DCB_ABORT & DCB_ABORT3 and related ccb body structure CB_SCSIIO
 * ---------------------------------------------------------------------- */

typedef	struct cb_abort
{
    void *cam_abort_ch;	/* Pointer to the CCB to abort */
} CB_ABORT;

typedef	struct dcb_abort
{
    CCB_HEADER cam_ch;		/* Header information fields */
    CB_SETASYNC	abort_body;
} DCB_ABORT;

typedef	struct dcb_abort3
{
    CCB_HEADER3	cam_ch;		/* Header information fields */
    CB_SETASYNC	abort_body;
} DCB_ABORT3;

/* ---------------------------------------------------------------------- * 
 * Terminate I/O Process Request CCG
 * DCB_TERMIO &	DCB_TERMIO3 and	related	ccb body structure CB_SCSIIO
 * ---------------------------------------------------------------------- */

typedef	struct cb_termio
{
    void *cam_termio_ch;	/* Pointer to the CCB to terminate */
} CB_TERMIO;

typedef	struct dcb_termio
{
    CCB_HEADER cam_ch;		/* Header information fields */
    CB_TERMIO  termio_body;
} DCB_TERMIO;

typedef	struct dcb_termio3
{
    CCB_HEADER3	cam_ch;		/* Header information fields */
    CB_TERMIO	termio_body;
} DCB_TERMIO3;

/* ---------------------------------------------------------------------- * 
 * Get Target Ident type CCB
 * DCB_TARGET_IDENT_VU & DCB_TARGET_IDENT_VU3 and related ccb body
 *   structure CB_TARGET_IDENT_VU
 * ---------------------------------------------------------------------- */

typedef	struct cb_target_ident_vu
{
    char        cam_tgt_ident[ASCIZ_64];
    				/* buffer to contain the null-terminated
				   ascii string representing the target's
				   identifier */
} CB_TARGET_IDENT_VU;

typedef	struct dcb_target_ident_vu
{
    CCB_HEADER cam_ch;		/* Header information fields */
    CB_TARGET_IDENT_VU  tgt_ident_body;
} DCB_TARGET_IDENT_VU;

typedef	struct dcb_target_ident_vu3
{
    CCB_HEADER3	cam_ch;		/* Header information fields */
    CB_TARGET_IDENT_VU	tgt_ident_body;
} DCB_TARGET_IDENT_VU3;

/* ---------------------------------------------------------------------- * 
 * Generic CCB definition
 * Used	only to	make macro CAM_GET_CB_PTR non-specific
 * ---------------------------------------------------------------------- */

typedef	struct ccb_generic
{
    CCB_HEADER	cam_ch;
    void	*cam_ccb_body;
} CCB_GENERIC;

/* now cam_debug can be	included as some basic types have been defined */
/* debug build fails if we include this file here, due to inclusion of
   pdrv.h-> dec_common.h -> cam_debug.h -> pdrv3.h, which needs definition
   defined in pdrv.h 
*/
/*#include <io/cam/cam_debug.h> */

#ifdef __cplusplus
}
#endif

#endif /* _DEC_COMMON_INCL_ */



