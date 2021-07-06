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
 * @(#)$RCSfile: sched_prim.h,v $ $Revision: 4.2.20.1 $ (DEC) $Date: 2002/05/06 17:51:24 $
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

#ifndef	_KERN_SCHED_PRIM_H_
#define _KERN_SCHED_PRIM_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 *	Scheduling primitive definitions file
 */

#include <kern/thread.h>	/* for thread_t */

/*
 *	Possible results of assert_wait - returned in
 *	current_thread()->wait_result.
 */
#define THREAD_AWAKENED		0		/* normal wakeup */
#define THREAD_TIMED_OUT	1		/* timeout expired */
#define THREAD_INTERRUPTED	2		/* interrupted by clear_wait */
#define THREAD_SHOULD_TERMINATE	3		/* thread should terminate */
#define THREAD_RESTART		4		/* restart operation entirely */

/*
 *	Exported interface to sched_prim.c 
 */
#ifdef _KERNEL
extern void	thread_timeout(void *);
extern void	sched_init(void);
extern void	assert_wait_mesg_head(
			vm_offset_t,	/* event */
			boolean_t,	/* interruptible */
			const char *);	/* mesg */
extern void	assert_wait_mesg_timo(
			vm_offset_t,	/* event */
			boolean_t,	/* interruptible */
			const char *,	/* mesg */
			int);		/* time */
extern void	assert_wait_mesg(
			vm_offset_t,	/* event */
			boolean_t,	/* interruptible */
			const char *);	/* mesg */
extern void	thread_sleep(
			vm_offset_t,	/* event */
			simple_lock_t,	/* lock */
			boolean_t);	/* interruptible */
extern void	thread_wakeup(
			vm_offset_t);	/* event */
extern thread_t thread_wakeup_and_hold(
			vm_offset_t,	/* event */
			spl_t *);	/* *spl */	
extern void	thread_go_and_switch_now(
			thread_t,	/* thread */
			spl_t,		/* spl */
			boolean_t);	/* switch_now */
extern int	thread_wakeup_prim(
			vm_offset_t,	/* event */
			boolean_t,	/* one_thread */
			int);		/* result */

extern int	wakeup_prim_result(
			wait_queue_t,	/* wait queue pointer */
			void *,		/* lock to free */
			long,		/* flags */
			long,		/* number of threads to wake */
			int);		/* result */

extern void	thread_list_wakeup(queue_t, spl_t , int);

extern int	thread_wakeup_hi(
			vm_offset_t,	/* event */
			int);		/* wakeup result */
extern void	thread_block(void);
extern void	thread_set_timeout(int);
extern void	thread_set_timeout_long(long);
extern void	clear_wait(
			thread_t,	/* thread */
			int,		/* result */
			boolean_t);	/* interrupt_only */

extern void	thread_run(
			thread_t);	/* new_thread */
extern void	thread_setrun(
			thread_t,	/* thread */ 
			boolean_t);	/* may_preempt */
extern int	compute_priority(
			thread_t,	/* thread */
			boolean_t);	/* may reschedule */

extern void	thread_preempt(
			thread_t,	/* thread */
			boolean_t);	/* may suspend */
extern int	thread_preempt_any(
			boolean_t);	/* may suspend */
extern void	thread_bind(
			thread_t,	/* thread */
			processor_t);	/* processor */

/*
 *	Routines defined as macros
 */

#define	wakeup_prim(w,x,y)	wakeup_prim_result(w,x,y,0,THREAD_AWAKENED)

#define wakeup_prim_n(w,x,y,z)	wakeup_prim_result(w,x,y,z,THREAD_AWAKENED)

#define thread_wakeup(x)						\
		thread_wakeup_prim((x), FALSE, THREAD_AWAKENED)
#define thread_wakeup_with_result(x, z)					\
		thread_wakeup_prim((x), FALSE, (z))
#define thread_wakeup_one(x)						\
		thread_wakeup_prim((x), TRUE, THREAD_AWAKENED)

#define thread_wakeup_high(x)						\
		thread_wakeup_hi((x), THREAD_AWAKENED)

#define assert_wait(ev,int)						\
		assert_wait_mesg(ev, int, (const char *) 0)

#define thread_go(thread,s)		thread_go_and_switch_now(thread,s,FALSE)
#define thread_go_and_switch(thread,s)	thread_go_and_switch_now(thread,s,TRUE)

#define PREEMPT_CHECK(thread)						\
MACRO_BEGIN								\
{									\
	if ((((volatile unsigned long)lbolt) - (thread->th_rq_enter))   \
					> min_quantum) {		\
		thread_preempt(thread, FALSE);				\
	}								\
}									\
MACRO_END

#endif /* _KERNEL */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _KERN_SCHED_PRIM_H_ */
