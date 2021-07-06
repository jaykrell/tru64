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
 * @(#)$RCSfile: cam3.h,v $ $Revision: 1.1.6.3 $ (DEC) $Date: 1999/08/13 12:21:57 $
 */

#ifndef _CAM3_INCL_
#define _CAM3_INCL_

#ifdef __cplusplus
extern "C" {
#endif

/* ********************************************************************* *
 * 
 *     This header defines all data structures and prototypes
 *     for the CAM3 API.
 * 
 * ********************************************************************* */

#include <io/cam/cam_types.h>
#include <io/cam/cam3_scsi.h>

/******************************************************
   CAM-3 status return by the CAM3 xpt functions
  
   Note: CAM_SUCCESS defined as 0 in cam.h
         CAM_FAILURE defined as 1 in cam.h
 ******************************************************/
#ifndef CAM_SUCCESS
#define	CAM_SUCCESS		0
#define CAM_FAILURE		1
#endif

#define CAM_INVAL_PROTOCOL	1
#define CAM_DEVICE_NOT_ATTACHED	2
#define CAM_NO_MEMORY		3
#define CAM_INVAL_PDREGNUM	4
#define CAM_NOT_FOUND		5
#define CAM_INVALID_ARGS	6
#define CAM_INVALID_SZ		7


/******************************************************
   Flags for CAM3 XPT calls
 ******************************************************/

#define XPT_WAITOK		1
#define XPT_BZERO		2


/******************************************************
   Flags for PD spec_release calls
 ******************************************************/

#define SPEC_RELEASE_SOFT	0
#define SPEC_RELEASE_HARD	1


/******************************************************
   CAM3 XPT function prototypes --
       Callable by Peripheral drivers
 ******************************************************/

CAM_U32		xpt_get_logical_id(
			TRANSLATION	*trans);

CAM_U32		xpt_get_phys_attrib(
			TRANSLATION	*trans);

CAM_U32		xpt_get_connections(
			CONNECTIONS	*connect);

CAM_BOOLEAN	xpt_isr(void);

CAM_U32		xpt_alloc_pd_specific(
			TRANSLATION	*trans,
			CAM_U32		(*spec_init)(TRANSLATION *),
			CAM_VOID	(*spec_release)(CAM_U32 lid,
						       CAM_VOID *spec_ptr,
						       CAM_U32 flags),
			CAM_U32		size);

CAM_U32		xpt_get_pd_specific(
			TRANSLATION	*trans);

CAM_U32		xpt_dealloc_pd_specific(
			TRANSLATION	*trans);

CAM_VM_OFFSET	xpt_mem_alloc(
			CAM_U32 size,
			CAM_U32 flags);

CAM_VM_OFFSET	xpt_mem_alloc_rad(
			CAM_U32 size,
			CAM_U32 flags,
			CAM_U32 rad_id);

CAM_VOID	xpt_mem_free(
			CAM_VM_OFFSET addr);

CCB_HEADER3 *	xpt_ccb_alloc3(
			CAM_U32 flags);

CCB_HEADER3 *	xpt_ccb_alloc3_rad(
			CAM_U32 flags,
			CAM_U32 rad_id);

CAM_VOID	xpt_ccb_free3(
			CCB_HEADER3 *cch);

CAM_U32		xpt_action3(
			CCB_HEADER3 *cch);

CAM_U32		xpt_pdrv_reg(
			CAM_S8 *name,
			CAM_U32 ws_size);

CAM_VOID	xpt_pdrv_unreg(
			CAM_U32 pdrv_reg_num);

CAM_U32		xpt_unit_lock_exclus(
			TRANSLATION *trans,
			CAM_U32 pdrv_reg_num);

CAM_U32		xpt_unit_unlock_exclus(
			TRANSLATION *trans,
			CAM_U32 pdrv_reg_num);

CAM_VOID	xpt_bcopy(
			CAM_VM_OFFSET src,
			CAM_VM_OFFSET dest,
			CAM_U32 len);

CAM_VOID	xpt_bzero(
			CAM_VM_OFFSET addr,
			CAM_U32 len);

CAM_U32		xpt_get_unique_id(
			TRANSLATION	*trans,
			CAM_S8		*buffer,
			CAM_U32		buffer_len);

CAM_U32		xpt_lid_from_unique_id(
			CAM_U32		*logical_id,
			CAM_S8		*buffer);


/* Vendor unique routine */
CAM_U32		xpt_get_unique_phys_id(
			TRANSLATION	*trans,
			CAM_S8		*buffer,
			CAM_U32		buffer_len);



/******************************************************
   CAM3 XPT function prototypes --
       Callable by SIM's
 ******************************************************/

CAM_U32		xpt_bus_register3(
			SIM_ENTRY3 *sim_entry);

CAM_U32		xpt_bus_deregister3(
			CAM_U32 port_id);

CAM_VOID	xpt_callback(
			CCB_HEADER3 *cch);

typedef void (*PREQUE_CALLBACK)(void *, void *);

CAM_VOID	xpt_workthread_que (
		    int rad_id, PREQUE_CALLBACK func, void *arg1, void *arg2);

/******************************************************
	XPT3 function prototypes - yet to be done
 ------------------------------------------------------

void		xpt_lock_init(
			CAM_VOID_OFFSET lock
			CAM_U8 lock_level);

void		xpt_lock(CAM_VOID_OFFSET lock);

void		xpt_unlock(CAM_VOID_OFFSET lock);

CAM_PM_OFFSET	xpt_virt_to_phys(
			CAM_VM_OFFSET addr,
			CAM_MAP *cam_map);

CAM_U32		xpt_page_size(
			CAM_VM_OFFSET addr,
			CAM_MAP *cam_map);

void		xpt_copy_to_phys(
			CAM_VM_OFFSET virt_src,
			CAM_PM_OFFSET phys_dest,
			CAM_U32 len);

void		xpt_que_init(
			XPT_QUEHEAD *qhead);

void		xpt_insque(
			XPT_QUEHEAD *data,
			XPT_QUEHEAD *que_element);

void		xpt_remque(
			XPT_QUEHEAD *data);

void		xpt_insque_head(
			XPT_QUEHEAD *data,
			XPT_QUEHEAD *qhead);

XPT_QUEHEAD *	xpt_remque_head(
			XPT_QUEHEAD *qhead);

void		xpt_insque_tail(
			XPT_QUEHEAD *data,
			XPT_QUEHEAD *qhead);

XPT_QUEHEAD *	xpt_remque_tail(
			XPT_QUEHEAD *qhead);

void		xpt_sleep(
			CAM_VM_OFFSET channel);

void		xpt_wakeup(
			CAM_VM_OFFSET channel);

void		xpt_async3(....);

 ******************************************************/

#ifdef __cplusplus
}
#endif

#endif /* _CAM3_INCL_ */


