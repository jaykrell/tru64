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
 * @(#)$RCSfile: cam1.h,v $ $Revision: 1.1.6.2 $ (DEC) $Date: 1999/07/30 19:25:53 $
 */

#ifndef _CAM1_INCL_
#define _CAM1_INCL_

#ifdef __cplusplus
extern "C" {
#endif

/* ********************************************************************* *
 * 
 *     This header defines all data structures and prototypes
 *     for the CAM1 API.
 * 
 * ********************************************************************* */

#include <io/common/iotypes.h>
#include <sys/types.h>

#include <io/cam/cam.h>


/******************************************************
   CAM1 XPT function prototypes --
       Callable by Peripheral drivers
 ******************************************************/


I32             xpt_init(
			void);

CCB_HEADER *	xpt_ccb_alloc(
			void);

CCB_HEADER *	xpt_ccb_alloc_nowait(
			void);

void		xpt_ccb_free(
			CCB_HEADER *cch);

U32		xpt_action(
			CCB_HEADER *ccb);


/******************************************************
   CAM3 XPT function prototypes --
       Callable by SIM's
 ******************************************************/

I32		xpt_bus_register(
			CAM_SIM_ENTRY *cse);

I32		xpt_bus_deregister(
			I32 path_id);

I32		xpt_async(
			I32 opcode, I32 path_id, I32 target_id,
			I32 lun, char *buffer_ptr, I32 data_cnt);

typedef void (*PREQUE_CALLBACK)(void *, void *);

void 		xpt_workthread_preque (
		    int rad_id, void *arg1, void *arg2, PREQUE_CALLBACK func);

#ifdef CCB_HEADER3_DEFINED
void		xpt_callback(
			CCB_HEADER3 *ccb);
#else
void		xpt_callback(
			CCB_HEADER *ccb);
#endif


#ifdef __cplusplus
}
#endif

#endif /* _CAM1_INCL_ */


