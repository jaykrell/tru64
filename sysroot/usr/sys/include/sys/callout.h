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
 *	@(#)$RCSfile: callout.h,v $ $Revision: 4.2.19.3 $ (DEC) $Date: 2000/03/24 11:40:18 $
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
/*
 * OSF/1 Release 1.0
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *

 */

#ifndef	_SYS_CALLOUT_H_
#define _SYS_CALLOUT_H_

#include <sys/types.h>

/*
 * The callout structure is for
 * a routine arranging
 * to be called by the clock interrupt
 * (clock.c) with a specified argument,
 * in a specified amount of time.
 * Used, for example, to time tab
 * delays on typewriters.
 */

#ifndef	KERNEL
struct	callout {
	long c_time;		/* lbolt time to expire */
	caddr_t	c_arg;		/* argument to routine */
	int	(*c_func)();	/* routine */
	struct	callout *c_next;
};

#else 

#include <kern/lock.h>
#include <sys/time.h>
#include <kern/queue.h>

struct	callout {
	union {
		unsigned long c_ticks;
		struct timeval c_tv;
	} c_u;

	caddr_t	c_arg;		/* argument to routine */
	void	(*c_func)(void *);	/* routine */

	struct callout *c_next;	 /* time ordered hash queue */
	struct callout *c_prev;	

	struct callout *e_next;	 /* func/event hash queue */
	struct callout *e_prev;	
	int		c_cpu;
};


#define c_time c_u.c_ticks
#define c_abs_time c_u.c_tv

#define CALLOUT_MASTER          1
#define CALLOUT_TYPE            2
#define CALLOUT_TYPE_MO         (CALLOUT_TYPE|CALLOUT_MASTER)
#define ABS_CALLOUT_TYPE        4
#define ABS_CALLOUT_TYPE_MO     (ABS_CALLOUT_TYPE|CALLOUT_MASTER)
#define CALLOUT_SHUTDOWN	0x20
#define CALLOUT_NEW_MASTER	0x40
#define	CALLOUT_NOMALLOC	0x80

extern struct callout *callfree, *callout, calltodo;
extern int ncallout;
decl_simple_lock_data(extern,callout_lock)

/* Function prototypes */
void callout_init(int cpunum);

#endif	/* KERNEL */
#endif	/* _SYS_CALLOUT_H_ */
