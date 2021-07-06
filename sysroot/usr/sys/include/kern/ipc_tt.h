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
 *	@(#)$RCSfile: ipc_tt.h,v $ $Revision: 4.2.15.5 $ (DEC) $Date: 1999/03/30 15:22:21 $
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
/*
 * OSF/1 Release 1.0
 */

#ifndef	_KERN_IPC_TT_H_
#define _KERN_IPC_TT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <mach/mach_types.h>
#include <mach/boolean.h>

extern kern_return_t ipc_task_init(task_t, task_t);
extern void ipc_task_enable(task_t);
extern void ipc_task_disable(task_t);
extern void ipc_task_terminate(task_t);

extern kern_return_t ipc_thread_init(thread_t);
extern void ipc_thread_enable(thread_t);
extern void ipc_thread_disable(thread_t);
extern void ipc_thread_terminate(thread_t);

extern boolean_t task_secure(task_t);

#if	MACH_KM
extern void ipc_monitor_init(monitor_t);
extern void ipc_monitor_enable(monitor_t);
extern void ipc_monitor_disable(monitor_t);
extern void ipc_monitor_terminate(monitor_t);
#endif	/* MACH_KM */

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif	/* _KERN_IPC_TT_H_ */
