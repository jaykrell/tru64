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
 *	@(#)$RCSfile: ipc_copyin.h,v $ $Revision: 4.2.7.4 $ (DEC) $Date: 1999/03/30 15:22:14 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */

#ifndef	_KERN_IPC_COPYIN_H_
#define _KERN_IPC_COPYIN_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <kern/kern_port.h>
#include <mach/mach_types.h>
#include <mach/boolean.h>
#include <mach/message.h>
#include <kern/kern_msg.h>

extern void port_clear_receiver(kern_port_t, task_t);

extern void port_copyin_receive_own(task_t, kern_port_t);

extern boolean_t object_copyin(task_t, port_name_t, u_int, boolean_t, kern_obj_t *);
extern boolean_t object_copyin_from_kernel(task_t, port_name_t, u_int, boolean_t, kern_obj_t *);
extern boolean_t object_copyin_cache(task_t, port_name_t, kern_obj_t *);

extern msg_return_t msg_copyin(task_t, msg_header_t *, msg_size_t, kern_msg_t *, boolean_t);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif	/*_KERN_IPC_COPYIN_H_*/

