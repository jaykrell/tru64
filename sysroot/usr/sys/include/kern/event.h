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
 *	@(#)$RCSfile: event.h,v $ $Revision: 4.2.20.1 $ (DEC) $Date: 2001/09/21 13:16:30 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/* 
 * Mach Operating System
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * Copyright (C) 1988,1989 Encore Computer Corporation.  All Rights Reserved
 *
 * Property of Encore Computer Corporation.
 * This software is made available solely pursuant to the terms of
 * a software license agreement which governs its use. Unauthorized
 * duplication, distribution or sale are strictly prohibited.
 *
 */

#ifndef	_KERN_EVENT_H_
#define	_KERN_EVENT_H_

#ifdef _KERNEL
#include <kern/queue.h>
#endif

#include <kern/lock.h>

struct event {
	decl_simple_lock_data(,ev_slock)/* lock protecting event structure */
#ifdef _KERNEL
	queue_head_t	ev_head;		/* wait queue head */
#else
	void		*next;
	void		*prev;
#endif
	unsigned int ev_event;		/* posted flag (event_post caller) */
	unsigned int ev_waiter;		/* wait flag (wait pc) */
};

typedef struct event event_t;

#ifdef	_KERNEL

/*
 * Prototypes and macros for exported functions in the event package.
 */

decl_simple_lock_info(extern, event_lockinfo)

#define event_init(evp)			/* initialize event structure */\
MACRO_BEGIN				\
	queue_init((&(evp)->ev_head));	\
	(evp)->ev_event = 0;		\
	(evp)->ev_waiter = 0;		\
	simple_lock_setup(&(evp)->ev_slock, event_lockinfo);\
MACRO_END

#define event_clear(evp)		\
MACRO_BEGIN				\
	(evp)->ev_event = 0;		\
	(evp)->ev_waiter = 0;		\
MACRO_END

#define event_posted(evp) 	(evp)->ev_event

#define event_terminate(evp)		/* terminate use of event structure */\
MACRO_BEGIN				\
	simple_lock_terminate(&(evp)->ev_slock);\
MACRO_END

extern void event_post(event_t *);	/* post event and wakeup waiters */
extern int event_wait(event_t *, boolean_t, int); /* wait for event */

extern int c_event_signal_wait(event_t *);	/* request wakeup  */
extern void c_event_post(event_t *);		/* post event has happened */
extern int c_event_wait(event_t *,int, int);	/* wait on counter event */


#define event_wait_tmo event_wait
extern void event_post_type(event_t *, unsigned int);	
extern int event_wait_type(event_t *, boolean_t, int, unsigned int *); 
#endif	/* _KERNEL */
#endif	/* _KERN_EVENT_H_ */
