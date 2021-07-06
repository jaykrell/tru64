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
 * @(#)$RCSfile: task_swap.h,v $ $Revision: 1.1.37.1 $ (DEC) $Date: 2001/11/08 14:28:21 $
 */
/*	
 *	@(#)task_swap.h	3.2	(ULTRIX/OSF)	11/20/91
 */ 
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
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/*
 *	File:   kern/task_swap.h
 *	Declarations of thread swap_states and swapping routines.
 */

/*
 *	Swap states for threads.
 */

#ifndef	_KERN_TASK_SWAP_H_
#define	_KERN_TASK_SWAP_H_

#ifdef __cplusplus
extern "C" {
#endif

/* task swap_state values */
#define TASK_NOT_QUEUED		0x00
#define TASK_INSWAPPED		0x01
#define TASK_OUTSWAPPED		0x02
#define TASK_COMING_IN		0x03
#define TASK_GOING_OUT		0x04

/* task swap_request values */
#define TASK_ALL_SET		0x01
#define TASK_WANTS_IN		0x02


#define EXCESSIVE_FAULTRATE(task_fault_rate, average_fault_rate)        \
                (task_fault_rate > average_fault_rate)

#define THREAD_TASK_SWAPPABLE(time_sleeping)    \
                (sched_tick - time_sleeping > 2)

#define THREAD_LONGTIME_SLEEPER(time_sleeping)    \
                (sched_tick - time_sleeping > 30)

/*
 * Prototypes
 */
struct vm_control;
struct swap_control;
struct task;
struct thread;
struct memory_affinity_domain;

extern void
	task_swapper_init(struct memory_affinity_domain *),
	task_swap_domain_init(struct memory_affinity_domain *),
	make_task_unswappable(struct task *, boolean_t),
	task_swapper_timeout(struct vm_control *);

extern kern_return_t
	task_swapin(struct task *);

boolean_t 
	task_swapin_request(struct task *, int);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif	/* _KERN_TASK_SWAP_H_ */
