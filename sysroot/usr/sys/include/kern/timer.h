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
 *	@(#)$RCSfile: timer.h,v $ $Revision: 4.2.7.6 $ (DEC) $Date: 1999/02/09 19:03:21 $
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

#ifndef	_KERN_TIMER_H_
#define _KERN_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stat_time.h>

#include <kern/macro_help.h>

#if	STAT_TIME
/*
 *	Statistical timer definitions - use microseconds in timer, seconds
 *	in high unit field.  No adjustment needed to convert to time_value_t
 *	as a result.  Service timers once an hour.
 */

#define TIMER_RATE	1000000
#define TIMER_HIGH_UNIT	TIMER_RATE
#undef	TIMER_ADJUST

#else	/* STAT_TIME */
/*
 *	Machine dependent definitions based on hardware support.
 */

#include <machine/timer.h>

#endif	/* STAT_TIME */
#ifdef	__arch64__

typedef	long	timer_data_t;
typedef long	*timer_t;
typedef long	timer_save_data_t;
typedef long	*timer_save_t;

#else /* __arch64__ */
/*
 *	Definitions for accurate timers.  high_bits_check is a copy of
 *	high_bits that allows reader to verify that values read are ok.
 */
struct timer {
	unsigned	low_bits;
	unsigned	high_bits;
	unsigned	high_bits_check;
	unsigned	tstamp;
};

typedef struct timer		timer_data_t;
typedef	struct timer		*timer_t;

/*
 *	Mask to check if low_bits is in danger of overflowing
 */

#define	TIMER_LOW_FULL	0x80000000

/*
 *	save structure for timer readings.  This is used to save timer
 *	readings for elapsed time computations.
 */

struct timer_save {
	unsigned	low;
	unsigned	high;
};

typedef struct timer_save	timer_save_data_t, *timer_save_t;
#endif /* __arch64__ */

/*
 *	Kernel timers and current timer array.  [Exported]
 */

extern timer_t		*current_timer;
extern timer_data_t	*kernel_timer;

/*
 *	Exported kernel interface to timers
 */

#if	STAT_TIME
#define start_timer(timer)
#define timer_switch(timer)
#else	/* STAT_TIME */
extern void timer_switch(timer_t new_timer);
extern void start_timer(timer_t timer);
#endif	/* STAT_TIME */


#include <mach/time_value.h>

extern void init_timers(void);
extern void compute_mach_factor(void);
extern void timer_read(timer_t, time_value_t *);
extern void thread_read_times(struct thread *, time_value_t *, time_value_t *);
extern unsigned int timer_delta(timer_t, timer_save_t);


#if	STAT_TIME
#ifdef	__arch64__


#define timer_bump(timer, usec)		*timer += usec
				
#else /* __arch64__ */
/*
 *	Macro to bump timer values.
 */	
#define timer_bump(timer, usec)					\
MACRO_BEGIN							\
	(timer)->low_bits += usec;				\
	if ((timer)->low_bits & TIMER_LOW_FULL) {		\
		timer_normalize(timer);				\
	}							\
MACRO_END
#endif /* __arch64__ */

#else	/* STAT_TIME */
/*
 *	Exported hardware interface to timers
 */
extern void	time_trap_uentry(unsigned int);
extern void	time_trap_uexit(unsigned int);
extern timer_t	time_int_entry(unsigned int, timer_t);
extern void	time_int_exit(unsigned int, timer_t);
#endif	/* STAT_TIME */

/*
 *	TIMER_DELTA finds the difference between a timer and a saved value,
 *	and updates the saved value.
 */

#ifdef	__arch64__
#define TIMER_DELTA(timer, save, result)   			\
		result = result + timer - save;			\
		save = timer;					
 
#else /* __arch64__ */
#define TIMER_DELTA(timer, save, result)			\
MACRO_BEGIN							\
	register unsigned	temp;				\
								\
	temp = (timer).low_bits;				\
	if ((save).high != (timer).high_bits) {			\
		result += timer_delta(&(timer), &(save));	\
	}							\
	else {							\
		result += temp - (save).low;			\
		(save).low = temp;				\
	}							\
MACRO_END
#endif /* __arch64__ */

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif	/* _KERN_TIMER_H_ */
