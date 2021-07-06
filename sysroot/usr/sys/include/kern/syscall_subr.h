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
 *	@(#)$RCSfile: syscall_subr.h,v $ $Revision: 4.2.33.1 $ (DEC) $Date: 1999/11/03 18:40:16 $
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
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */

#ifndef	_KERN_SYSCALL_SUBR_H_
#define _KERN_SYSCALL_SUBR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <mach_emulation.h>
#include <mach_sctimes.h>

#include <mach/port.h>
#include <mach/kern_return.h>

#include <mach/boolean.h>
#include <mach/machine/vm_types.h>

struct vm_stack;

extern	port_t		task_by_pid();
extern	kern_return_t	init_process();

extern int	swtch();
extern boolean_t	swtch_pri(int);
extern int	semop_fast(long, long, long, long);
extern int	thread_switch();

extern int	map_fd();

extern kern_return_t lw_wire(vm_offset_t, u_long, u_long *);
extern kern_return_t lw_unwire(thread_t);
extern kern_return_t lw_syscall();

extern kern_return_t nxm_task_init();
extern kern_return_t nxm_sched_thread();
extern kern_return_t nxm_idle();
extern kern_return_t nxm_wakeup_idle();
extern kern_return_t nxm_set_pthid();
extern kern_return_t nxm_thread_kill();
extern kern_return_t nxm_thread_block();
extern kern_return_t nxm_thread_wakeup();
extern kern_return_t nxm_resched();
extern kern_return_t stack_create(struct vm_stack *);
extern kern_return_t nxm_set_cancel();
extern kern_return_t nxm_thread_create();
extern kern_return_t nxm_get_state();
extern kern_return_t nxm_signal_check();
extern kern_return_t nxm_thread_suspend();
extern kern_return_t nxm_thread_resume();
extern kern_return_t nxm_thread_destroy();
extern kern_return_t nxm_get_binding();
extern kern_return_t nxm_set_binding();

extern kern_return_t nxm_block();
extern kern_return_t nxm_unblock();

extern kern_return_t nxm_pshared_init();
extern kern_return_t nxm_pshared_block();
extern kern_return_t nxm_pshared_unblock();
extern kern_return_t nxm_pshared_destroy();
extern kern_return_t nxm_swtch_pri();


#if	MACH_EMULATION
extern int	htg_unix_syscall();
#endif	

#if	MACH_SCTIMES
extern kern_return_t mach_sctimes_0();
extern kern_return_t mach_sctimes_1();
extern kern_return_t mach_sctimes_2();
extern kern_return_t mach_sctimes_3();
extern kern_return_t mach_sctimes_4();
extern kern_return_t mach_sctimes_5();
extern kern_return_t mach_sctimes_6();
extern kern_return_t mach_sctimes_7();
extern kern_return_t mach_sctimes_8();
extern kern_return_t mach_sctimes_9();
extern kern_return_t mach_sctimes_10();
extern kern_return_t mach_sctimes_11();
extern kern_return_t mach_sctimes_port_alloc_dealloc();
#endif	

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif	/* _KERN_SYSCALL_SUBR_H_ */
