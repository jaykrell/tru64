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
 * @(#)$RCSfile: lock.h,v $ $Revision: 4.2.61.1 $ (DEC) $Date: 2002/01/29 21:18:23 $
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
 *	File:	kern/lock.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *	Copyright (C) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Locking primitives definitions
 */

#ifndef	_KERN_LOCK_H_
#define _KERN_LOCK_H_

#ifdef __cplusplus
extern "C" {
#endif


/*
 *	A simple spin lock.
 */
typedef unsigned long simple_lock_data_t; /* lock state is machine-dependent */
typedef unsigned long *simple_lock_t;  /* this is a pointer to a simple lock */
struct slock { unsigned long sl_data; }; /* obsolete, use simple_lock_data_t */

#define decl_simple_lock_data(class,name) class simple_lock_data_t name;

#ifdef _KERNEL 
#include <kern/queue.h>
#endif

/*
 * reader/writer spin lock structure.  Provides multiple readers/one
 * writer fuctionality with a busy wait.  Structure is layed out to
 * be cache friendly.
 */
#define RWS_BLOCK_SIZE_SHIFT	6
#define RWS_BLOCK_STRIDE	((1 << RWS_BLOCK_SIZE_SHIFT) \
				 / sizeof(simple_lock_data_t))
struct rws_lock {
	simple_lock_data_t rws_writer_mutex[RWS_BLOCK_STRIDE];
	simple_lock_data_t rws_reader_mutex[1][RWS_BLOCK_STRIDE];
};

typedef struct rws_lock *rws_lock_t;

/*
 *	The general lock structure.  Provides for multiple readers,
 *	upgrading from read to write, and sleeping until the lock
 *	can be gained.
 *
 *	On some (many) architectures, assembly language code in the inline
 *	program fiddles the lock structures.  It must be changed in concert
 *	with the structure layout.
 */

/* forward decl for ANSI & C++ */
struct thread;

struct lock {
	simple_lock_data_t l_lock;	/* simple lock for atomicity control */
#ifdef _KERNEL
	queue_head_t	l_head;		/* wait queue head */
#else
	void		*next;
	void		*prev;
#endif
	unsigned int	l_caller;	/* half of calling pc of locker */
	int		l_wait_writers; /* number of waiting writers */
	int		l_readers;	/* number of accepted readers */
	unsigned char	l_flags;	/* lock state flags (see below) */
	unsigned char	l_lifms;	/* lockinfo flags and minspl level */
	unsigned short	l_info;		/* lockinfo structure table index */
	struct thread	*l_lastlocker;	/* thread that was last granted lock */
};

/* bit definitions for l_flags field */
#define LF_RECWRITE	  0x07	/* recursive write count */
#define LF_WRITE	  0x20	/* locked for writing or writer is waiting */
#define LF_READ_SLEEPING  0x40	/* thread is suspended on read lock */

typedef struct lock	lock_data_t;
typedef struct lock	*lock_t;


/*
 *	Definitions and data structures used by lock debugging logic.
 */

#define MAX_LOCK	32	/* max complex lock nesting level */
#define MAX_SLOCK	32	/* max simple lock nesting level */

struct slock_debug {
	simple_lock_t sd_addr[MAX_SLOCK]; /* addr of simple lock structure */
	unsigned long sd_time[MAX_SLOCK]; /* time stamp at lock acquisition */
};

struct lockinfo {
	char		*li_name;	/* arbitrary name of class */
	int		li_count;	/* number of lock instances */
	int		li_flgspl;	/* class flags and minspl level */
};

#define LOCKINFO_SHIFT	4		/* log2(sizeof(struct lockinfo)) */

#define LI_SPLMASK	0x07		/* required minimum spl level mask */
#define	LI_RWS		0x08		/* reader/writer spin lock type */
#define LI_ORDERED	0x10		/* ordering exists within a class */
#define LI_ORDNEXT	0x20		/* ordering exists thru next class */
#define LI_DOHIER	0x40		/* hierarchy checking is enabled */
#define LI_VALID	0x80		/* lock is properly initialized */
#define LI_PROBE	0x1000		/* set lock to probe mode, note */
					/* this bit is not mirrored     */
					/* lock flags field.	        */

struct lockstats {
	unsigned long	ls_tries;	/* number of acquisition attempts */
	unsigned long	ls_reads;	/* number of acquisitions for read */
	unsigned long	ls_trmax;	/* max time held or number of rdrs */
	unsigned long	ls_misses;	/* number of attempts which missed */
	unsigned long	ls_sleeps;	/* number of thread blocks incurred */
	unsigned long	ls_waitmax;	/* max time spent waiting on a lock */
	unsigned long	ls_waitmin;	/* min time spent waiting on a lock */
	unsigned long	ls_waitsum;	/* total time spent waiting on locks */
};

/* structure to hold pointer and counts for recursive read locks held
 * by a thread.
 */
struct lock_read_rec_list {
	struct lock *l;		/* pointer to read lock held recrusive. */
	int rec_count;		/* count of recursive depth */
};

#define LOCKSTATS_SHIFT	6		/* log2(sizeof(struct lockstats)) */

#define NQLCKS_MAX	MAX_SLOCK	/* max number of queue entries */
#define QLCKS_INDEX	(NQLCKS_MAX-1)*(sizeof(struct qlock)) /* initial lock queue index */
#define SIMPLE_LOCKS	0
#define MCS_LOCKS	1

struct qlock {
	simple_lock_data_t	*ql_lock;	/* pointer to the simple lock */
	unsigned long		ql_caller; 	/* pc following lock call */
	struct	qlock		*ql_nextWaiter;	/* qlock of next cpu in line */
	unsigned int		ql_tail;	/* tail code for this entry */
	volatile unsigned int	ql_wait;	/* wait synchronization flag */
	simple_lock_data_t	ql_data; 	/* saved simple lock data */
	unsigned long		ql_spare[3]; 	/* pad to 64 bytes */
};

typedef struct qlock	queue_lock_data_t;
typedef struct qlock	*qlock_p;

#ifdef _KERNEL

#include <rt_preempt.h>
#include <mach_ldebug.h>
#include <mach/boolean.h>

#ifndef __VMS  
#define MACH_SLOCKS	1
#endif /* __VMS */

#if MACH_SLOCKS

#define simple_lock_init(l)	simple_lock_setup((l), (struct lockinfo *)0)
extern void		simple_lock_setup(simple_lock_t, struct lockinfo *);
extern void		simple_lock_terminate(simple_lock_t);
extern void		simple_lock(simple_lock_t);
extern void		simple_unlock(simple_lock_t);
extern boolean_t	simple_lock_try(simple_lock_t);
extern boolean_t	simple_lock_locked(simple_lock_t);
extern boolean_t	simple_lock_holder(simple_lock_t);
extern rws_lock_t	rws_alloc(struct lockinfo *, int );
extern void		rws_free(rws_lock_t);
extern void		rws_read_lock(rws_lock_t);
extern boolean_t	rws_read_lock_try(rws_lock_t);
extern void		rws_read_unlock(rws_lock_t);
extern void		rws_write_lock(rws_lock_t);
extern void		rws_write_unlock(rws_lock_t);

#define decl_rws_lock_info(name)		struct lockinfo *name
#define decl_simple_lock_info(class,name)	class struct lockinfo *name;
#define simple_lock_addr(name)			(&(name))

#else /* MACH_SLOCKS */

#define simple_lock_init(l)
#define simple_lock_setup(l,i)
#define simple_lock_terminate(l)
#define simple_lock(l)
#define simple_unlock(l)
#define simple_lock_try(l)		(1)	/* always succeeds */
#define simple_lock_locked(l)		(1)	/* always succeeds */
#define simple_lock_holder(l)		(1)	/* always succeeds */

#define rws_alloc(i,s)			((rws_lock_t)0)
#define rws_free(l)
#define rws_read_lock(l)
#define rws_read_lock_try(l)		(1)	/* always succeeds */
#define rws_read_unlock(l)
#define rws_write_lock(l)
#define rws_write_unlock(l)


#define decl_simple_lock_info(class,name)
#define simple_lock_addr(name)			((simple_lock_t)0)

#endif /* MACH_SLOCKS */

#define SLOCK_LOCKED(l)	simple_lock_locked(l)
#define SLOCK_HOLDER(l)	simple_lock_holder(l)

/* Sleep locks must work even if no multiprocessing */

#define lock_read_done(l)	lock_done(l)
#define lock_write_done(l)	lock_done(l)
#define lock_init(l,cs)		lock_setup((l), (struct lockinfo *)0, (cs))
#define lock_init2(l,cs,t)	lock_setup((l), (struct lockinfo *)0, (cs))

#define	lock_read_done_recursive(l) lock_done(l);

#define lock_read_recursive(l)						\
MACRO_BEGIN								\
	lock_read(l);							\
	(void) lock_read_recursive_add_lock(l, TRUE);			\
MACRO_END


#define lock_read_recursive_try(l) 					\
			(lock_try_read(l) ? 				\
				lock_read_recursive_add_lock(l,FALSE) : \
				    FALSE)

extern boolean_t	lock_read_recursive_add_lock(lock_t, boolean_t);
extern void		lock_setup(lock_t, struct lockinfo *, boolean_t);
extern void		lock_terminate(lock_t);
extern void		lock_write(lock_t);
extern int		lock_write_interruptible(lock_t, int);
extern void		lock_read(lock_t);
extern void		lock_done(lock_t);
extern boolean_t	lock_read_to_write(lock_t);
extern void		lock_write_to_read(lock_t);
extern boolean_t	lock_try_write(lock_t);
extern boolean_t	lock_try_read(lock_t);
extern boolean_t	lock_try_read_to_write(lock_t);
extern boolean_t	lock_try_write_assert(lock_t);
extern boolean_t	lock_try_read_assert(lock_t);
extern void		lock_set_recursive(lock_t);
extern void		lock_clear_recursive(lock_t);
extern void		lock_adopt(lock_t, struct thread *);
extern void		lock_disown(lock_t, struct thread *);
extern boolean_t	lock_readers(lock_t);
extern boolean_t	lock_locked(lock_t);
extern boolean_t	lock_holder(lock_t);
extern boolean_t        lock_recursive_try(lock_t);
extern void		lock_done_clear_recursive(lock_t);
extern int		lock_bootstrap(unsigned long);
extern int		lock_islocked(lock_t);


#if MACH_LDEBUG

#include <kern/assert.h>

#define LOCK_READERS(l)		lock_readers(l)
#define LOCK_LOCKED(l)		lock_locked(l)
#define LOCK_HOLDER(l)		lock_holder(l)
#define LASSERT(clause)		if (check_locks) ASSERT(clause)

#else /* MACH_LDEBUG */

#define LOCK_READERS(l)		(1)
#define LOCK_LOCKED(l)		(1)
#define LOCK_HOLDER(l)		(1)
#define LASSERT(clause)

#endif /* MACH_LDEBUG */

#define LOCK_ADOPT(l,th)	if (check_locks) lock_adopt((l), (th))
#define LOCK_DISOWN(l,th)	if (check_locks) lock_disown((l), (th))

#ifndef REPLICATED
#define REPLICATED
#endif

extern REPLICATED long lockmode; /* mode of locking primitives (0-4) */
extern REPLICATED int check_locks; /* lock debugging checks enabled */

extern long locktype; 		   /* type of locking method (0-1) */
extern int lockinfo_bootstrap(struct lockinfo *);
#endif /* _KERNEL */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _KERN_LOCK_H_ */
