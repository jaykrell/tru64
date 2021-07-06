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
 *	@(#)$RCSfile: policy.h,v $ $Revision: 4.2.9.2 $ (DEC) $Date: 1997/03/12 19:32:14 $
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
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */

#ifndef	_MACH_POLICY_H_
#define _MACH_POLICY_H_

/*
 *	mach/policy.h
 *
 *	Definitions for scheduling policy.
 */

#ifdef _KERNEL
#include <rt_sched.h>
#endif /* _KERNEL */

/*
 *	Policy definitions.  Policies must be powers of 2.
 */
#define	POLICY_TIMESHARE	1
#define POLICY_FIXEDPRI		2
#define POLICY_FIFO		4
#define POLICY_RR		8
#define POLICY_LAST		8

#define	POLICY_SVID_RT		16

#if RT_SCHED
#define invalid_policy(policy)				\
  (((policy & ~POLICY_SVID_RT) != POLICY_TIMESHARE)	\
   && ((policy & ~POLICY_SVID_RT) != POLICY_FIXEDPRI)	\
   && ((policy & ~POLICY_SVID_RT) != POLICY_FIFO)	\
   && ((policy & ~POLICY_SVID_RT) != POLICY_RR))
#else /* RT_SCHED */
#define invalid_policy(policy)	(((policy) <= 0) || ((policy) > POLICY_LAST))
#endif /* RT_SCHED */

#if RT_SCHED
/*
 * The POSIX Realtime scheduling
 * functions are accessed through the getpriority and setpriority system
 * calls.
 *
 * PRIO_WHICH is a mask which peels off the basic mode flags.  Modes are
 * PRIO_PROCESS, PRIO_PGRP, PRIO_USER, and PRIO_POSIX.  The first three are
 * part of the standard {get|set}priority interface.  The last indicates that
 * absolute POSIX priorities are being used.
 */
#define PRIO_WHICH      0xFF
#define PRIO_POSIX	8

/*
 * PRIO_POLICY is a mask for a policy field within the "which" parameter.
 * PRIO_POLICY_SHIFT is used to shift the policy over so that it can be
 * passed to the kernel policy routines.  Note that this overloaded interface
 * cannot support 32 distinct scheduling policies.  At best it can support
 * 24.
 */
#define PRIO_POLICY		0xFFFFFF00
#define PRIO_POLICY_SHIFT	8

/*
 * PRIO_POLICY_* constants are used to specify policies accross the overloaded
 * interface.
 */
#define PRIO_POLICY_OTHER	(POLICY_TIMESHARE<<PRIO_POLICY_SHIFT)
#define PRIO_POLICY_RR		(POLICY_RR<<PRIO_POLICY_SHIFT)
#define PRIO_POLICY_FIFO	(POLICY_FIFO<<PRIO_POLICY_SHIFT)
#define PRIO_POLICY_FIXED	(POLICY_FIXEDPRI<<PRIO_POLICY_SHIFT)

#endif /* RT_SCHED */

#endif /* _MACH_POLICY_H_ */
