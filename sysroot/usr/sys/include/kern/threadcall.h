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
 *	@(#)$RCSfile: threadcall.h,v $ $Revision: 4.2.5.3 $ (DEC) $Date: 1999/02/09 19:03:20 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * Header file for general-purpose thread callout routines.
 * (see threadcall.c)
 */
#ifndef _KERN_THREADCALL_H_
#define _KERN_THREADCALL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <kern/lock.h>

struct thread_call {
	struct thread_call *tc_next;
	void	(*tc_func)();
	void	*tc_arg;
};
typedef struct thread_call thread_call_t;

struct thread_callq {
	decl_simple_lock_data(,tcq_lock)
	thread_call_t *tcq_head;
	thread_call_t *tcq_tail;
	int	tcq_threadcall_size;
};
typedef struct thread_callq thread_callq_t;

extern boolean_t thread_call(thread_callq_t *tcq, void (*func)(), void *arg);
extern boolean_t thread_call_one(thread_callq_t *tcq, void (*func)(), void *arg);
extern void thread_call_create(thread_callq_t *tcq, int ncallthreads);
extern void thread_call_add(thread_callq_t *tcq, int ncallthreads);
extern void thread_call_alloc(thread_callq_t *tcq, int nthreadcalls);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif	/* _KERN_THREADCALL_H_ */
