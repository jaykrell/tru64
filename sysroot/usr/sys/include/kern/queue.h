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
 *	@(#)$RCSfile: queue.h,v $ $Revision: 4.2.12.2 $ (DEC) $Date: 1997/03/03 15:40:20 $
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
 * Copyright (C) 1988,1989 Encore Computer Corporation.  All Rights Reserved
 *
 * Property of Encore Computer Corporation.
 * This software is made available solely pursuant to the terms of
 * a software license agreement which governs its use. Unauthorized
 * duplication, distribution or sale are strictly prohibited.
 *
 */
/*
 *	File:	queue.h
 *
 *	Type definitions for generic queues.
 */

#ifndef	_KERN_QUEUE_H_
#define _KERN_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif
/*
 *	Queue of abstract objects.  Queue is maintained
 *	within that object.
 *
 *	Supports fast removal from within the queue.
 *
 *	How to declare a queue of elements of type "foo_t":
 *		In the "*foo_t" type, you must have a field of
 *		type "queue_chain_t" to hold together this queue.
 *		There may be more than one chain through a
 *		"foo_t", for use by different queues.
 *
 *		Declare the queue as a "queue_t" type.
 *
 *		Elements of the queue (of type "foo_t", that is)
 *		are referred to by reference, and cast to type
 *		"queue_entry_t" within this module.
 */

/*
 *	A generic doubly-linked list (queue).
 */

struct queue_entry {
	struct queue_entry	*next;		/* next element */
	struct queue_entry	*prev;		/* previous element */
};

typedef struct queue_entry	*queue_t;
typedef	struct queue_entry	queue_head_t;
typedef	struct queue_entry	queue_chain_t;
typedef	struct queue_entry	*queue_entry_t;

#ifdef	_KERNEL

#include <mach/machine/vm_types.h>
#include <kern/spl.h>
#include <kern/lock.h>
#include <kern/macro_help.h>

/*
 *	enqueue puts "elt" on the "queue".
 *	dequeue returns the first element in the "queue".
 */

#define enqueue(queue,elt)	enqueue_tail(queue, elt)
#define dequeue(queue)		dequeue_head(queue)

#if defined(_USE_KERNEL_PROTOS)

extern void enqueue_head(void * que, queue_entry_t elt);
extern void enqueue_tail(void * que, queue_entry_t elt);
extern queue_entry_t dequeue_head(void * que);
extern queue_entry_t dequeue_tail(void * que);
extern void insque(struct queue_entry *entry, struct queue_entry *pred);
extern void remque(struct queue_entry *entry);
extern void reminsque(struct queue_entry *entry, struct queue_entry *pred);


#else /* !defined(_USE_KERNEL_PROTOS) */

extern void		enqueue_head();
extern void		enqueue_tail();
extern queue_entry_t	dequeue_head();
extern queue_entry_t	dequeue_tail();
extern void		insque();
extern void		remque();
extern void		reminsque();

#endif /* defined(_USE_KERNEL_PROTOS) */


/*
 *	Macro:		queue_init
 *	Function:
 *		Initialize the given queue.
 *	Header:
 *		void queue_init(q)
 *			queue_t		q;	// MODIFIED
 */
#define queue_init(q)	((q)->next = (q)->prev = q)

/*
 *	Macro:		queue_first
 *	Function:
 *		Returns the first entry in the queue,
 *	Header:
 *		queue_entry_t queue_first(q)
 *			queue_t	q;		// IN 
 */
#define queue_first(q)	((q)->next)

/*
 *	Macro:		queue_next
 *	Header:
 *		queue_entry_t queue_next(qc)
 *			queue_t qc;
 */
#define queue_next(qc)	((qc)->next)

/*
 *	Macro:		queue_end
 *	Header:
 *		boolean_t queue_end(q, qe)
 *			queue_t q;
 *			queue_entry_t qe;
 */
#define queue_end(q, qe)	((q) == (qe))

#define queue_empty(q)		queue_end((q), queue_first(q))

/*
 *	Macro:		queue_enter
 *	Header:
 *		void queue_enter(q, elt, type, field)
 *			queue_t q;
 *			<type> elt;
 *			<type> is what's in our queue
 *			<field> is the chain field in (*<type>)
 */
#define queue_enter(head, elt, type, field)			\
MACRO_BEGIN							\
	if (queue_empty((head))) {				\
		(head)->next = (queue_entry_t) elt;		\
		(head)->prev = (queue_entry_t) elt;		\
		(elt)->field.next = head;			\
		(elt)->field.prev = head;			\
	}							\
	else {							\
		register queue_entry_t prev;			\
								\
		prev = (head)->prev;				\
		(elt)->field.prev = prev;			\
		(elt)->field.next = head;			\
		(head)->prev = (queue_entry_t)(elt);		\
		((type)prev)->field.next = (queue_entry_t)(elt);\
	}							\
MACRO_END

/*
 *	Macro:		queue_field [internal use only]
 *	Function:
 *		Find the queue_chain_t (or queue_t) for the
 *		given element (thing) in the given queue (head)
 */
#define queue_field(head, thing, type, field)			\
		(((head) == (thing)) ? (head) : &((type)(thing))->field)

/*
 *	Macro:		queue_remove
 *	Header:
 *		void queue_remove(q, qe, type, field)
 *			arguments as in queue_enter
 */
#define queue_remove(head, elt, type, field)			\
MACRO_BEGIN							\
	register queue_entry_t	next, prev;			\
								\
	next = (elt)->field.next;				\
	prev = (elt)->field.prev;				\
								\
	queue_field((head), next, type, field)->prev = prev;	\
	queue_field((head), prev, type, field)->next = next;	\
MACRO_END

/*
 *	Macro:		queue_assign
 */
#define queue_assign(to, from, type, field)			\
MACRO_BEGIN							\
	((type)((from)->prev))->field.next = (to);		\
	((type)((from)->next))->field.prev = (to);		\
	*to = *from;						\
MACRO_END

#define queue_remove_first(h, e, t, f)				\
MACRO_BEGIN							\
	e = (t) queue_first((h));				\
	queue_remove((h), (e), t, f);				\
MACRO_END

#define queue_remove_last(h, e, t, f)				\
MACRO_BEGIN							\
	e = (t) queue_last((h));				\
	queue_remove((h), (e), t, f);				\
MACRO_END

/*
 *	Macro:		queue_enter_first
 *	Header:
 *		void queue_enter_first(q, elt, type, field)
 *			queue_t q;
 *			<type> elt;
 *			<type> is what's in our queue
 *			<field> is the chain field in (*<type>)
 */
#define queue_enter_first(head, elt, type, field)		\
MACRO_BEGIN							\
	if (queue_empty((head))) {				\
		(head)->next = (queue_entry_t) elt;		\
		(head)->prev = (queue_entry_t) elt;		\
		(elt)->field.next = head;			\
		(elt)->field.prev = head;			\
	}							\
	else {							\
		register queue_entry_t next;			\
								\
		next = (head)->next;				\
		(elt)->field.prev = head;			\
		(elt)->field.next = next;			\
		(head)->next = (queue_entry_t)(elt);		\
		((type)next)->field.prev = (queue_entry_t)(elt);\
	}							\
MACRO_END

/*
 *	Macro:		queue_last
 *	Function:
 *		Returns the last entry in the queue,
 *	Header:
 *		queue_entry_t queue_last(q)
 *			queue_t	q;		// IN
 */
#define queue_last(q)	((q)->prev)

/*
 *	Macro:		queue_prev
 *	Header:
 *		queue_entry_t queue_prev(qc)
 *			queue_t qc;
 */
#define queue_prev(qc)	((qc)->prev)

/*
 *	Macro:		queue_entry_to_base
 *	Function:	calculates pointer to structure containing queue_entry
 */
#define queue_entry_to_base(qe, type, field) \
	((type *)((char *)(qe) - (int)&((type *)0)->field))

/*
 *	Define macros for queues with locks.
 */
struct mpqueue_head {
	struct queue_entry	head;		/* header for queue */
	decl_simple_lock_data(,lock)		/* lock for queue */
};

typedef struct mpqueue_head	mpqueue_head_t;

#define round_mpq(size)		(size)

#define mpqueue_init(q)						\
MACRO_BEGIN							\
	decl_simple_lock_info(extern,mpqueue_lockinfo)		\
	queue_init(&(q)->head);					\
	simple_lock_setup(&(q)->lock, mpqueue_lockinfo);	\
MACRO_END

#define mpqueue_terminate(q)	simple_lock_terminate(&(q)->lock)

#define mpenqueue_tail(q, elt)					\
MACRO_BEGIN							\
	simple_lock(&(q)->lock);				\
	enqueue_tail(&(q)->head, elt);				\
	simple_unlock(&(q)->lock);				\
MACRO_END

#define mpdequeue_head(q, elt)					\
MACRO_BEGIN							\
	simple_lock(&(q)->lock);				\
	if (queue_empty(&(q)->head))				\
		*(elt) = 0;					\
	else							\
		*(elt) = dequeue_head(&(q)->head);		\
	simple_unlock(&(q)->lock);				\
MACRO_END

#ifdef lint
#define QWAIT	ALWAYS
#define QNOWAIT	NEVER
#else
#define QWAIT	1
#define QNOWAIT	0
#endif
#define mpdequeue1(q, elt, wait)				\
MACRO_BEGIN							\
	for (;;) {						\
		register int s = splhigh();			\
		simple_lock(&(q)->lock);			\
		if (queue_empty(&(q)->head))			\
			if (wait) {				\
				assert_wait((vm_offset_t) (q), FALSE);	\
				simple_unlock(&(q)->lock);	\
				splx(s);			\
				thread_block();			\
				continue;			\
			} else					\
				*(elt) = 0;			\
		else						\
			*((caddr_t *)elt) = (caddr_t)dequeue_head(&(q)->head); \
		simple_unlock(&(q)->lock);			\
		splx(s);					\
		break;						\
	}							\
MACRO_END

#define mpenqueue1(q, elt)					\
MACRO_BEGIN							\
	register int empty = 0;					\
	register int s = splhigh();				\
	simple_lock (&(q)->lock);				\
	if (queue_empty(&(q)->head)) ++empty;			\
	enqueue_tail(&(q)->head, (elt));			\
	simple_unlock (&(q)->lock);				\
	splx(s);						\
	if (empty) thread_wakeup((vm_offset_t)(q));		\
MACRO_END

#endif	/* _KERNEL */
#ifdef __cplusplus
}
#endif
#endif	/* _KERN_QUEUE_H_ */
