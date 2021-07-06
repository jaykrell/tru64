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
 * @(#)$RCSfile: dec_xpt.h,v $ $Revision: 1.1.9.2 $ (DEC) $Date: 2001/04/04 17:37:07 $
 */

#ifndef _DEC_XPT_INCL_
#define _DEC_XPT_INCL_
#ifdef __cplusplus
extern "C" {
#endif

/* ********************************************************************* *
 * 
 *     This header includes common data structures and prototypes
 *     for use by our XPT implementation.
 * 
 * ********************************************************************* */

#include <io/cam/dec_common.h>
#include <io/common/kds.h>
#include <io/cam/camdb.h>
#include <io/cam/xpt3.h>
#include <io/cam/xpt.h>
#include <ksm/ksm.h>


/* ************************************************
 *   SIM entry point registry
 * ************************************************ */

/*
 * this structure is the basic registery element built whenever
 * a sim registers it's entry points with CAM.
 */
typedef struct {
    SIM_ENTRY3		xse_sim_entry;
    DEC_SIM_ENTRY3	xse_dec_entry;
    CAM_SCSI_BUS	xse_cbus;
} XPT_SIM_ENTRY;


/*
 * We'll keep an array of pointers to sim entries. To make this scale 
 * we'll maintain a 2 level table. The lowest level will contain an
 * array of pointers to sim entries. The array will contain CAM_XSE_TBL_INCR
 * elements. The pointers will be set as each pathid attaches. The
 * highest (initial) level will also be an array, but will contain
 * pointers to the lower level chunks. The first lower element table
 * will be allocated, and as the pathid numbers grow, subsequent
 * element tables will be allocated. Thus, we waste minimal table space.
 *
 * For example, with CAM_XSE_TBL_INCR=2:
 *
 *   cam_xse_tbl -> element 0  ->  pathid 0 sim entry ptr
 *                                 pathid 1 sim entry ptr
 *                  element 1  ->  pathid 2 sim entry ptr
 *                                 pathid 3 sim entry ptr
 *                  element 2  ->  NULL
 *                  ...
 *
 * The number of sim entry elements to be supported is maintained by
 * the global variable cam_xse_max_tblsz. This variable will default to
 * the value of CAM_XSE_DEFAULT_TBLSZ.
 *
 */

/* number of sim entries per table element */
#define CAM_XSE_TBL_INCR		8

/* for now, set the default to support 256 sim entries */
#define CAM_XSE_DEFAULT_TBLSZ		256


/*
 * this macro obtains the sim entry from the xse table.
 * We should be able to avoid locks on access, with locks being
 * used only update of this table entry. Thus, the sim must account
 * for a call to it's entry points (just shortly) after deregistering
 * from this table (although extremely unlikely).
 */
#define GET_SIM_ENTRY(sim_entry, pathid)				\
    { 									\
    if ((pathid) < cam_xse_tblsz) {					\
	if (cam_xse_tbl[(pathid)/CAM_XSE_TBL_INCR]) {			\
	    (sim_entry) = (cam_xse_tbl[(pathid)/CAM_XSE_TBL_INCR])	\
				[(pathid) % CAM_XSE_TBL_INCR];		\
	} else								\
	    (sim_entry) = (XPT_SIM_ENTRY *)NULL;			\
    } else								\
	(sim_entry) = (XPT_SIM_ENTRY *)NULL;				\
    }


/*
 * Macros for locking the sim entry registration table
 */

/* lock w/ no spl */
#define LOCK_XSE()		XPT_SPINLOCK(&cam_conf_ctrl.smp_lock)
#define UNLOCK_XSE()		XPT_SPINUNLOCK(&cam_conf_ctrl.smp_lock)

/* lock w/ spl */
#define LOCK_XSE_SPL()		XPT_LOCK(&cam_conf_ctrl.smp_lock)
#define UNLOCK_XSE_SPL()	XPT_UNLOCK(&cam_conf_ctrl.smp_lock)


/* ********************************************************************** *
 *   Common macros to search the PD specific structures in a SCSI_DID
 * ********************************************************************** */

#define XPT_GET_PD_SPECIFIC(did, pd_reg_num, specp)		\
{								\
	PD_SPEC_INFO *sinfo;					\
	(specp) = (CAM_VOID_OFFSET)NULL;			\
	sinfo = (did)->pd_spec_list.pd_spec_flink;		\
	while (sinfo != &(did)->pd_spec_list) {			\
	    if (sinfo->spec_reg_no == (pd_reg_num)){		\
		(specp) = sinfo->spec_ptr;			\
		break;						\
	    }							\
    	    sinfo = sinfo->pd_spec_flink;			\
    	}							\
}

#define XPT_GET_PD_SPECINFO(did, pd_reg_num, speci)		\
{								\
	PD_SPEC_INFO *sinfo;					\
	(speci) = (PD_SPEC_INFO *)NULL;				\
	sinfo = (did)->pd_spec_list.pd_spec_flink;		\
	while (sinfo != &(did)->pd_spec_list) {			\
	    if (sinfo->spec_reg_no == (pd_reg_num)){		\
		(speci) = sinfo;				\
		break;						\
	    }							\
    	    sinfo = sinfo->pd_spec_flink;			\
    	}							\
}


/* ********************************************************************** *
 *   EDT Locking Macros
 * ********************************************************************** */

#define EDT_INIT_LOCK( ep )				\
{							\
    XPT_INIT_LOCK( &(ep)->edt_lock, cam_c_edt_li );	\
}							

#define EDT_SPINLOCK( ep )				\
{							\
    XPT_SPINLOCK( &(ep)->edt_lock );			\
}							

#define EDT_SPINUNLOCK( ep )				\
{							\
    XPT_SPINUNLOCK( &(ep)->edt_lock );			\
}							

#define EDT_LOCK( ep )					\
{							\
    XPT_LOCK( &(ep)->edt_lock );			\
}							

#define EDT_UNLOCK( ep )				\
{							\
    XPT_UNLOCK( &(ep)->edt_lock );			\
}
 
#define EDT_SLEEPLOCK( chan, pri, ep )  				\
{                                                       \
    int s = (ep)->edt_lock.xpt_saveipl;                 \
    mpsleep((void *)(chan), (pri), "EDT sleep", 0,		\
	    (void *)&((ep)->edt_lock), MS_LOCK_SIMPLE);	    \
    (ep)->edt_lock.xpt_saveipl = s;                     \
}

/* ********************************************************************** *
 *    Async Callback execution flags
 * ********************************************************************** */

/*
 * Flags used by the XPT and CDrv async handling code.  Each EDT structure
 * contains a flags field.  This flag is used by the XPT to inform the CDrv
 * that an Async Callback is in progress and that the async links can not
 * be disturbed.
 */

#define ASYNC_CB_INPROG	0x00000001	/* Used by the XPT async call code */
#define ASYNC_CB_REGISTERED 0x00000002  /* Used by ccfg_free_lun_edt() */


/* ********************************************************************** *
 *    LAST BUT NOT LEAST, PULL IN THE XPT EXTERNAL DECLARATIONS           *
 * ********************************************************************** */

#include <io/cam/dec_xpt_extern.h>


#ifdef __cplusplus
}
#endif
#endif /* _DEC_XPT_INCL_ */

