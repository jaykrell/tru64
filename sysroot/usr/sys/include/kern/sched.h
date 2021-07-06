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
 *	@(#)$RCSfile: sched.h,v $ $Revision: 4.2.22.8 $ (DEC) $Date: 2000/05/22 18:46:33 $
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
 *	File:	sched.h
 *	Author:	Avadis Tevanian, Jr.
 *	Copyright (C) 1985, Avadis Tevanian, Jr.
 *
 *	Header file for scheduler.
 */

#ifndef	_KERN_SCHED_H_
#define _KERN_SCHED_H_

#ifndef	ASSEMBLER

#include <sys/limits.h>
#include <kern/queue.h>
#include <kern/lock.h>

#ifdef	_KERNEL

#include <rt_sched_rq.h>
#include <simple_clock.h>
#include <stat_time.h>
#include <kern/macro_help.h>
#include <sys/numa_types.h>

#if	STAT_TIME

/*
 *	Statistical timing uses microseconds as timer units.  18 bit shift
 *	yields priorities.  PRI_SHIFT_2 isn't needed.
 */
#define PRI_SHIFT	18

#else	/*STAT_TIME*/

/*
 *	Otherwise machine provides shift(s) based on time units it uses.
 */
#include <machine/sched_param.h>

#endif	/* STAT_TIME */

#endif	/* _KERNEL */

/* 
 * Use NRQS_MAX to specify the number of queue headers in the runq structure.
 * Use NRQS to specify the number of queue headers being used.  This will allow
 * compilation of data structures which accomodate 64 run queues, while
 * permitting the scheduler code to use only the first 32 queue headers.
 */
#define NRQS_MAX 64

#ifdef	_KERNEL

#if RT_SCHED_RQ
/*
 * If the run queue extensions are enabled, use all NRQS_MAX queues.
 * Otherwise, only use NRQS queues.  The data structures always leave
 * space for NRQS_MAX queues, but the priority calculations and user
 * parameter checks use NRQS.  This allows us to have compatible
 * data structures while still being able to configure the number of
 * run queues we use.
 *
 * Probably this should be simplified once we decide how many queues we
 * want to have.
 */
#define NRQS	NRQS_MAX
#else /* RT_SCHED_RQ */
#define NRQS	32			/* 32 run queues per cpu */
#endif /* RT_SCHED_RQ */

/*
 * Provide an adjustment value, so that interfaces which need to be consistent
 * based on NRQS_MAX, regardless of the value of NRQS, can do so.  This is
 * used in thread_info (src/kernel/kern/thread.c) to return priority values.
 */
#define NRQS_ADJUST (NRQS_MAX - NRQS)

#endif	/* _KERNEL */

/*
 * The run_queue_bitmask structure is a mask where each bit represents the
 * state of one run queue header.  If the run queue is empty, the bit is 0,
 * if the run queue is nonempty, the bit is 1.  This is made a struct so that
 * there is some level of data opaqueness -- a machine with 64-bit integers
 * could change the definition of bits within the structure.
 */
struct run_queue_bitmask {
	unsigned long		bits[(NRQS_MAX + (LONG_BIT -1)) / LONG_BIT];
};

struct run_queue {
	decl_simple_lock_data(,	lock)		/* one lock for all queues */
	unsigned int		low;		/* low queue value */
	int			count;		/* count of threads runnable */
	long			spare;		/* for queue head alignment */
#ifdef __arch32__
	struct run_queue_bitmask mask;		/* for fast lookup */
#else
	long			mask;		/* for fast lookup */
#endif
	queue_head_t		runq[NRQS_MAX];	/* one for each priority */
};

typedef struct run_queue	*run_queue_t;

#define RUN_QUEUE_NULL	((run_queue_t) 0)


struct wait_queue {
	decl_simple_lock_data(,	wq_lock)
	queue_head_t		wq_head;
	void			*wq_unused;
};

typedef struct wait_queue	wait_queue_data_t;
typedef struct wait_queue 	*wait_queue_t;

#ifdef	_KERNEL
extern void wait_queue_setup(wait_queue_t);
extern void wait_queue_terminate(wait_queue_t);
extern void assert_wait_prim(wait_queue_t, boolean_t, const char *);
extern int sleep_prim(wait_queue_t, int, char *, int, void *, long);

#define csw_needed(thread, processor) ((thread)->state & TH_SUSP ||	\
	((processor)->first_quantum == FALSE &&				\
	(((processor)->runq.low <= (thread)->sched_pri) ||		\
	((processor)->processor_pag->pag_runq.low <= (thread)->sched_pri))))


/*
 *	Scheduler routines.
 */

extern struct run_queue	*rem_runq();

#ifndef REPLICATED
#define REPLICATED
#endif

extern REPLICATED int min_quantum;	/* implies max context switch rate */

/*
 *	Default base priorities for threads.
 *
 *  RT_SCHED:	Always define these, and always use the constants in the
 *		routines which previously had hardcoded priority values.
 *		Eventually, we may want to make some of these values
 *		configurable.
 */
/*
 * Default base priorities for system and user threads.
 */
#define BASEPRI_SYSTEM (NRQS - 26)
#define BASEPRI_USER (NRQS - 20)

/*
 * Base priorities for lowest priority thread and highest priority non-realtime
 * (system) thread.
 */
#define BASEPRI_LOWEST (NRQS - 1)
#define BASEPRI_HIGHEST (NRQS - 32)

/*
 * Base priorities for specific kernel threads.
 */
#define BASEPRI_ACCTWATCH (NRQS - 22)
#define BASEPRI_SOFTCLOCK (NRQS - 32)
#define BASEPRI_PSIGNAL (NRQS - 22)

/*
 *	Macro to check for invalid priorities.
 */

#define invalid_pri(pri) (((unsigned int) pri) >= NRQS)

/*
 * Macro to check for invalid POSIX priorities.  This will stay simple as long
 * as the priority ranges for all the policies are the same, and the POSIX
 * range has the same boundaries as the internal range.
 */
#define rt_sched_invalid_posix_pri(policy,pri) invalid_pri(pri)

/*
 *	Shift structures for holding update shifts.  Actual computation
 *	is  usage = (usage >> shift1) +/- (usage >> abs(shift2))  where the
 *	+/- is determined by the sign of shift 2.
 */
struct shift {
	int	shift1;
	int	shift2;
};

typedef	struct shift	*shift_t, shift_data_t;

/*
 *	sched_tick increments once a second.  Used to age priorities.
 */

extern unsigned	sched_tick;

#define SCHED_SCALE	128
#define SCHED_SHIFT	7

/*
 *	thread_timer_delta macro takes care of both thread timers.
 */

#define thread_timer_delta(thread)  				\
MACRO_BEGIN							\
	register long	delta;					\
								\
	delta = 0;						\
	TIMER_DELTA((thread)->system_timer,			\
		(thread)->system_timer_save, delta);		\
	TIMER_DELTA((thread)->user_timer,			\
		(thread)->user_timer_save, delta);		\
	(thread)->cpu_delta += delta;				\
	(thread)->sched_delta += delta * 			\
			(thread)->th_pag->pag_sched_load;	\
MACRO_END

#if	SIMPLE_CLOCK
/*
 *	sched_usec is an exponential average of number of microseconds
 *	in a second for clock drift compensation.
 */
extern int	sched_usec;
#endif /* SIMPLE_CLOCK */

/*
 * Run Queue Bitmask Operations.
 *
 * These are defined as macros so that future 64-bit machines can use simpler
 * mechanisms.  Note that this code and the data structures are not optimized
 * for 64-bit machines, but the code ought to compile and run.
 */
#ifdef __arch32__
#define RT_SCHED_RUNQ_BIT_VALUE(mask,pri) \
  (((struct run_queue_bitmask *)(mask))->bits[(pri)/LONG_BIT] \
   >> ((pri)%LONG_BIT) & 1)
#define RT_SCHED_CLEAR_RUNQ_BIT(mask,pri)				\
	MACRO_BEGIN							\
	((struct run_queue_bitmask *)(mask))->bits[(pri)/LONG_BIT]	\
  			&= ~(1L << ((pri)%LONG_BIT));			\
	MACRO_END

#define RT_SCHED_SET_RUNQ_BIT(mask,pri)					\
	MACRO_BEGIN							\
	((struct run_queue_bitmask *)(mask))->bits[(pri)/LONG_BIT]	\
			|= 1L << ((pri)%LONG_BIT);			\
	MACRO_END
#else
#define RT_SCHED_RUNQ_BIT_VALUE(mask,pri) ((*mask) & (1L << (pri))) 

#define RT_SCHED_CLEAR_RUNQ_BIT(mask,pri) (*mask) &= (~(1L << (pri)))

#define RT_SCHED_SET_RUNQ_BIT(mask,pri) (*mask) |= (1L << (pri))
#endif
    
extern int find_first_runq_bit_set();

/*
 * Returns TRUE if policy/prio pair is legal; FALSE if illegal.
 */
#define user_sched_check(__pol__, __pri__) 				\
        (__pol__) == POLICY_TIMESHARE || (__pol__) == POLICY_RR ? 	\
             	((__pri__) < BASEPRI_USER ? 0 : 1) :			\
	     		((__pri__) <= BASEPRI_USER ? 0 : 1) 		\

/*
 * NUMA Scheduling Group structure and prototypes.
 */

typedef struct numa_scheduling_group {
	queue_chain_t		nsg_all_list;
	queue_head_t		nsg_member_list;
	simple_lock_data_t	nsg_member_lock;
	nsgid_ds_t		nsg_attrib;
	int			nsg_ref_count;
	radid_t			nsg_radid;
} nsg_t;

/* used only from numa_syscalls.c and numa_nsgops.c */
int	nsg_init(key_t key, ulong_t flags, long *retval);
int	nsg_destroy(nsgid_t nsgid, long *retval);
int	nsg_attach_pid(nsgid_t nsgid, pid_t pid, ulong_t flags, long *retval);
int	nsg_detach_pid(pid_t pid, long *retval);
int	nsg_get(nsgid_t nsgid, nsgid_ds_t *attrib, long *retval);
int	nsg_get_nsg(nsgid_t *nsgidlist, int numnsgs, long *retval);
int	nsg_get_pid(nsgid_t nsgid, pid_t *pidlist, int numpids, long *retval);
int	nsg_set(nsgid_t nsgid, nsgid_ds_t *attrib, long *retval);

int	nsg_add_proc(nsg_t *nsg, struct proc *p, ulong_t flags);
int	nsg_proc_exit(struct proc *p);
void	nsg_unref(nsg_t *nsg);
void	nsg_unref_member_locked(nsg_t *nsg);
int	nsg_ref(nsg_t *nsg);
int	nsg_ref_member_locked(nsg_t *nsg);
nsg_t *	nsg_find_by_nsgid(nsgid_t nsgid);
nsg_t *	nsg_find_by_pid(pid_t pid);

#endif	/* _KERNEL */
#endif	/* !ASSEMBLER */
#endif	/*_KERN_SCHED_H_*/
