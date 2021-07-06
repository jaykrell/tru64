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
 *	@(#)$RCSfile: proc.h,v $ $Revision: 4.3.134.2 $ (DEC) $Date: 2002/01/29 20:33:32 $
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
 * Copyright (c) 1982, 1986, 1989  Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 */

#ifndef _SYS_USER_H_
#ifndef ASSEMBLER
#include <sys/user.h>
#endif
#endif

#ifndef	_SYS_PROC_H_
#define _SYS_PROC_H_
#ifdef __cplusplus
extern "C" {
#endif

#ifndef ASSEMBLER
#include <mach/boolean.h>
#include <sys/time.h>
#include <sys/types.h>
#include <kern/lock.h>
#include <kern/queue.h>
#include <kern/event.h>
#include <sys/rt_limits.h>		  /* #if RT, used for psx4 timers*/
#include <sys/siginfo.h>
#include <sys/unix_defs.h>

#if defined (__cplusplus)
struct pgrp;
struct thread;
struct psx4_tblock_struct;
struct sigacthdr;
#endif

/*
 * One structure allocated per session.
 */
struct session {
	udecl_simple_lock_data(, s_lock)
	int	s_count;	/* ref cnt; pgrps in session */
	pid_t	s_id;		/* session ID */
	struct	pgrp *s_pgrps;	/* list of pgrp's in session */
	struct	vnode *s_ttyvp;	/* vnode of controlling terminal */
	udecl_simple_lock_data(, s_fpgrp_lock)
	struct	pgrp **s_fpgrpp;/* pointer to foreground pgrp pointer */
	struct	proc *s_leader;	/* session leader */
	short	s_id_gen;	/* sid generation number */
};


/*
 * One structure allocated per process group.
 */
struct pgrp {
	udecl_simple_lock_data(, pg_ref_lock)
	u_int	pg_refcnt;		/* reference count */
	struct	proc	*pg_mem;	/* pointer to pgrp members */
	struct	session	*pg_session;	/* pointer to session */
	struct	pgrp	*pg_sessnxt;	/* next pgrp in session */
	struct	pgrp	*pg_hforw;	/* forward link in hash bucket */
	udecl_lock_data(, pg_lock)
	pid_t	pg_id;			/* pgrp id */
	u_int	pg_jobc;		/* # procs qualifying pgrp for
					 * job control */
};


/*
 * One structure allocated per process id.
 */
struct pid_entry {
	pid_t		pe_pid;		/* process id */
	unsigned short	pe_gen;		/* pid generation */
	unsigned char	pe_ibn;		/* pid incr bit number */
	unsigned char	pe_flag;	/* miscellaneous flags */
	struct proc	*pe_proc;	/* associated process */
	struct pid_entry *pe_link;	/* pid free list link */
	udecl_simple_lock_data(, pe_lock) /* lock for pid_entry */
};

#define PE_PGRP		0x01		/* pid is the pgrp leader */
#define PE_SESS		0x02		/* pid is session leader */

#define PID_GENERATION(p) ((p)->p_pe->pe_gen)


/*
 * One structure allocated per active process.
 *
 * Wait events which use proc structure addresses:
 *
 *	&p->p_refcnt		waiting to initiate exit (SWEXIT)
 *	&p->p_forkcnt		waiting for fork (p_end_thread)
 */
struct proc {
    /* 64-byte alignment */
	struct pid_entry *p_pe;
	int	p_flag;
	int	p_nice;		/* nice for cpu usage */
	pid_t	p_pid;		/* unique process id */
	pid_t	p_ppid;		/* process id of parent */
	uid_t	p_ruid;		/* real user id */
	gid_t	p_rgid;		/* real group id */
	uid_t	p_svuid;	/* saved effective user id */
	gid_t	p_svgid;	/* saved effective group id */
	struct 	pgrp *p_pgrp;	/* pointer to process group */
	struct	ucred *p_rcred;	/* user credentials (uid, gid, etc) */
	size_t	p_maxrss;	/* copy of u.u_limit[MAXRSS] */

    /* 64-byte alignment */
	int	p_stat;
	u_int	p_refcnt;	/* reference count */
	sigset_t p_sig;		/* signals pending to this process */
	sigset_t p_gsig;	/* group signals pending to this process */
	sigset_t p_sigignore;	/* signals being ignored */
	sigset_t p_sigcatch;	/* signals being caught by user */
	sigset_t p_siginfo;	/* signals expecting siginfo delivery */
	sigset_t p_sigwaitmask;	/* summary signals threads are waiting for */
	sigset_t p_sigrestart;	/* restart flags */

    /* 64-byte alignment */
	queue_head_t p_sigqueue;/* queue of sigqueue structs */
	queue_head_t p_sigwaitq;/* queue of waiting threads structs */
	queue_head_t p_sigauxq; /* queue of reserved sigqueue structs */
	struct sigacthdr *p_sigact; /* ptr to dynamic sigactions */
	struct sigaction *p_sigcache; /* last handler used */

    /* 64-byte alignment */
	queue_head_t p_strsigs;	/* Streams signals from I_SETSIG */
	int	p_sigqcnt;	/* number of signals queued */
	boolean_t p_sig_wait;	/* indication to suspend */


	int	spare1;
	u_int	p_forkcnt;	/* forks in progress */
	u_int	p_xstat;	/* exit information */
	int	p_wcode;	/* wait code to explain contents of p_xstat */
	struct	rusage *p_ru;	/* rusage holding exit information */
	struct thread *p_end_thread;	/* XXX Which thread is exiting?
					   XXX That thread does no signal
					   XXX processing, other threads
					   XXX must suspend. */
#define PROC_SIZE_OF_PERSISTENT_STATE sizeof(simple_lock_data_t)+ \
					sizeof(struct event)

/* START of persistent state while on task free list */
	udecl_simple_lock_data(, p_lock) /* lock for proc */

    /* 64-byte alignment */
	struct	event	p_block_event;	/* used by pid_block/unblock */
/* END of  persistent state while on task free list */
	struct psx4_tblock_struct *p_psx4_timer; /* POSIX.4 timer array ptr */
	struct vnode *p_tracep;	/* trace to vnode */
	int	p_trcf;		/* set if process is ptrace'd */
	uid_t	p_auid;		/* audit id */
	long	p_habitat;	/* habitat flag for process */

    /* 64-byte alignment */
	udecl_lock_data(, proc_relation_lock) /* controls chain of children */
	struct	proc *p_pptr;	/* pointer to process structure of parent */
	struct	proc *p_cptr;	/* pointer to youngest living child */
	struct	proc *p_osptr;	/* pointer to older sibling processes */
	struct	proc *p_ysptr;	/* pointer to younger siblings */
	struct  proc *p_pgrpprv;/* pointer to prev process in process group */
#define p_session p_pgrp->pg_session
#define p_pgid	p_pgrp->pg_id
	struct	proc *p_pgrpnxt; /* pointer to next process in process group */
	queue_chain_t p_uidlinks; /* uid hash table links */
	queue_chain_t p_gidlinks; /* gid hash table links */

    /* 64-byte alignment */
	volatile int p_realtimer_flags;	/* used to control timer */
#define		REALTIMER_CPU		0xff
#define 	REALTIMER_COE		0x100	/* clear p_realtimer on exec */
#define		REALTIMER_ACTIVE 	0x200	/* timeout is active */
#define		REALTIMER_ABORT 	0x400	/* abort timeout */
	int		p_aio_free;	/* next free aio result block */
	udecl_simple_lock_data(, p_timer_lock) /* protects realtimer */
	struct itimerval p_timer[3];


    /* 64-byte alignment */
#ifdef _KERNEL
	struct queue_entry p_aio_completion; /* aio completion queue */
#else
	long		p_aio_completion[2];
#endif /* _KERNEL */
	int	p_spare; 	/* unused */ 
	int	p_multichannelwait; /* set if pid block feature in use */
	u_int	p_aiocount;	/* outstanding aio requests */
	int	p_uac;		/* unaligned access control flags AND */
				/* instruction emulation control flags */
	void 	*p_aiogp;	/* ptr to aio group state */
	struct thread *p_ptrace_thread;	/* thread currently handling ptrace */
#ifdef _KERNEL
	aio_result_t	p_aio_rb;	/* aio result block kernel address */
#else
	long		spare2;
#endif /* _KERNEL */
	vm_offset_t	p_aio_user;	/* aio result block user address */
};

/* stat codes */
/*
 *	MACH uses only NULL, SRUN, SZOMB, and SSTOP.
 */
#define SSLEEP	1		/* awaiting an event */
#define SWAIT	2		/* (abandoned state) */
#define SRUN	3		/* running */
#define SIDL	4		/* intermediate state in process creation */
#define SZOMB	5		/* intermediate state in process termination */
#define SSTOP	6		/* process being traced */

/* flag codes */
#define SLOAD	0x00000001	/* in core */
#define SSYS	0x00000002	/* swapper or pager process */
#define SLOMAP	0x00000004	/* process allowed to use low virt memory */
#define SWNOTASK \
		0x00000010  	/* thread waiting on notask to be set */
#define SNOTASK	0x00000040	/* process completed exit */
#define SWWAIT	0x00000080	/* thread is removing zombie */
#define SOMASK	0x00000200	/* restore old mask after taking signal */
#define SWEXIT	0x00000400	/* working on exiting */
#define SPHYSIO	0x00000800	/* doing physical i/o */
#define SVFORK	0x00001000	/* process resulted from vfork() */
#define SPAGV	0x00008000	/* init data space on demand, from vnode */
#define SSEQL	0x00010000	/* user warned of sequential vm behavior */
#define SUANOM	0x00020000	/* user warned of random vm behavior */
#define SCONTIGN \
		0x00040000	/* process is ignoring SIGCONT */
#define S1170	0X00080000	/* using Spec 1170 signal behaviors */
#define SLOGIN  0x00400000      /* mark process as a login for Capacity Limitation */
#define SCTTY	0x00800000	/* has a controlling terminal */
#define SXONLY	0x02000000	/* process image read protected	*/
#define SSIGEXIT \
		0x04000000	/* process wants notice of child signal exit */
#define SSWPKIL 0x10000000      /* process killed due to lack of swap space */
#define	SNOCLDWAIT \
		0x20000000	/* no SIGCHLD when children die */
#define	SNOCLDSTOP \
		0x40000000	/* no SIGCHLD when children stop */
#define SEXEC	0x80000000	/* process called exec */

#endif /* ASSEMBLER */

/* p_uac UAC & IEC codes */
#define UAC_BITMASK    0x00000007       /* Mask for valid UAC bits */
#define UAC_NOPRINT    0x00000001       /* Don't report unaligned fixups */
#define UAC_NOFIX      0x00000002       /* Don't fix unaligned errors */
#define UAC_SIGBUS     0x00000004       /* Notify unaligned trap by SIGBUS */

#define IEC_BITMASK    0x78000000	/* Mask for valid IEC bits */
#define IEC_NOFAT      0x08000000	/* Don't do fat binary fixups */
#define IEC_VERBOSE    0x10000000	/* Report ALL emulations not just 1st */
#define IEC_NOPRINT    0x20000000	/* Don't report instruction emulation */
#define IEC_NOEMUL     0x40000000	/* Don't emulate new instructions, */
					/* (OPDEC exception then KILL!) */
#define IEC_RSVD       0x80000000	/* Reserved to Digital; DO NOT USE */

#ifndef ASSEMBLER
#ifdef	_KERNEL

/*
 * LOCKS FOR MP SYNCHRONIZATION
 *
 * This table describes all process-related locks present in
 * the kernel.  Each entry gives the name of the lock, its type
 * and scope, and what data it covers.  In order to permit
 * multiple locks to be taken simultaneously with no risk of
 * deadlock, a formal ordering is imposed on the acquisition
 * of these locks:  they must be acquired in their order of
 * appearance in lockinfo.c (reading from top to bottom).
 * This ordering is enforced in lock mode 4.
 *
 *        Name           Type       Scope                 Covers
 * ============================================================================
 * pgrphash_lock         r/w       global      pgrphash table
 *
 * proc_relation_lock    r/w       per-proc 	proc members
 *                                               p_cptr,
 *                                    		it's childrens p_osptr, p_ysptr
 *
 * pg_lock               r/w      per-pgrp     proc member
 *                                               p_pgrpnxt,
 *                                             all pgrp members *except*
 *                                               pg_sessnxt, pg_refcnt
 *
 * gidhash_lock         simple     global      gidhash table buckets,
 *                                              proc member p_gidlinks
 *
 * uidhash_lock         simple     global      uidhash table buckets,
 *                                               proc member p_uidlinks
 *
 * ruidhash_lock        simple     global      ruidhash table buckets,
 *
 * pid_lock             simple     global      pidtab table
 *
 * p_lock		simple     per-proc    proc members
 *                                               p_sig,
 *                                               p_trcf, p_sigwaitmask
 *						 p_siginfo, p_sigqueue
 *                                               p_sigignore, p_sigcatch,
 *                                               p_stopsig, p_ptrace_thread
 *                                               p_end_thread, p_sig_wait,
 *						 p_forkcnt, p_sigact,
 *						 p_sigcache, p_sigqcnt
 *						 p_sigwaitq, p_sigauxq
 *                                             utask members
 *                                               uu_rlimit
 *                                               uu_sigcatch,
 *						 uu_exitp
 *                                             np_uthread member
 *                                               uu_sig, uu_sigqueue
 *					       uthread members
 *					         uu_curinfo
 *                                               uu_oldmask,
 *						 uu_sflags, uu_sigstack
 *					       all proc members not
 *                                             mentioned elsewhere
 *
 *
 * s_lock               simple   per-session   all session members
 *                                             pgrp member
 *                                               pg_sessnxt
 *
 * p_timer_lock         simple    per-proc     proc members
 *                                               p_timer, p_realtimer_flags,
 *                                               p_psx4_timer
 *
 * s_fpgrp_lock		simple   per-session   destination of session
 *						 member s_fpgrpp.
 *
 * pg_ref_lock          simple    per-pgrp     prgp member
 *                                               pg_refcnt
 *
 * Further notes:
 *
 * Lock pg_lock protects the proc member list of a pgrp.
 *
 * p_nice writes are protected by the task lock; reads are not protected.
 * Since p_nice is per process, recalculating thread priorities (schedcpu,
 * donice) is done on all threads for the process making the task lock
 * a good choice for protection.
 */

/*
 * GLOBAL LOCKS FOR MP SYNCHRONIZATION
 */

/*
 * Synchronization lock for process sibling relationships
 */
udecl_lock_info(extern, proc_relation_lockinfo)
#define PROCREL_READ_LOCK(p)	ulock_read(&(p)->proc_relation_lock)
#define PROCREL_WRITE_LOCK(p)	ulock_write(&(p)->proc_relation_lock)
#define PROCREL_UNLOCK(p)	ulock_done(&(p)->proc_relation_lock)
#define PROCREL_LOCK_INIT(p)	ulock_setup(&(p)->proc_relation_lock, \
						proc_relation_lockinfo, TRUE)
#define PROCREL_LOCK_TERMINATE(p) ulock_terminate(&(p)->proc_relation_lock)

/*
 * Hash table list head protected by a simple lock
 */
struct ht_list {
	simple_lock_data_t	ht_lock;
	queue_head_t		ht_head;
	long			pad;
};

struct ruid_hash_entry {
	uid_t			r_ruid;		/* ruid key value */
	boolean_t		r_nxm_blocked;	/* nxm idle thd is blocked */
	long			r_task_count;	/* # tasks for this r_ruid */
	long			r_thread_count;	/* # threads for this r_ruid */
	queue_chain_t		r_links;	/* ruid hash links */
};

typedef struct ruid_hash_entry ruid_hash_entry_t;
typedef struct ruid_hash_entry *ruid_hash_entry_p;

extern ruid_hash_entry_p get_ruid_entry(uid_t ruid, struct ht_list *hp);
boolean_t uid_count_update(struct proc *p,
			   long task_count,
			   long thread_count,
			   ruid_hash_entry_p newp,
			   boolean_t no_alloc);
extern void uid_count(uid_t ruid, long *task_count, long *thread_count);
extern ruid_hash_entry_p alloc_ruid_hash_entry(void);

#define IDHASH_LOCK(__hp)	usimple_lock(&(__hp)->ht_lock)
#define IDHASH_UNLOCK(__hp)	usimple_unlock(&(__hp)->ht_lock)

/*
 * Lock / unlock the two hash lists given by the arguments.
 * Enforce a locking hierarchy whereby the lowest hash bucket
 * address dictates the order.  If the arguments represent
 * the same hash chain, just lock / unlock that chain.
 */
#define IDHASH_LOCK2(__hp1, __hp2) \
	MACRO_BEGIN \
	if (__hp1 < __hp2) { \
		IDHASH_LOCK(__hp1); \
		IDHASH_LOCK(__hp2); \
	} else if (__hp1 > __hp2) { \
		IDHASH_LOCK(__hp2); \
		IDHASH_LOCK(__hp1); \
	} else { \
		IDHASH_LOCK(__hp1); \
	} \
	MACRO_END

#define IDHASH_UNLOCK2(__hp1, __hp2) \
	MACRO_BEGIN \
	if (__hp1 < __hp2) { \
		IDHASH_UNLOCK(__hp2); \
		IDHASH_UNLOCK(__hp1); \
	} else if (__hp1 > __hp2) { \
		IDHASH_UNLOCK(__hp1); \
		IDHASH_UNLOCK(__hp2); \
	} else { \
		IDHASH_UNLOCK(__hp1); \
	} \
	MACRO_END

udecl_simple_lock_info(extern, uidhash_lockinfo)
#define UIDHASH_LOCK_INIT(__hp)	usimple_lock_setup(&(__hp)->ht_lock, \
						uidhash_lockinfo)

udecl_simple_lock_info(extern, ruidhash_lockinfo)
#define RUIDHASH_LOCK_INIT(__hp)	usimple_lock_setup(&(__hp)->ht_lock, \
						ruidhash_lockinfo)

udecl_simple_lock_info(extern, gidhash_lockinfo)
#define GIDHASH_LOCK_INIT(__hp)	usimple_lock_setup(&(__hp)->ht_lock, \
						gidhash_lockinfo)

extern lock_data_t pgrphash_lock;		/* for pgrp hash table */
extern struct lockinfo *pgrphash_lockinfo;
#define PGRPHASH_READ_LOCK()	lock_read(&pgrphash_lock)
#define PGRPHASH_WRITE_LOCK()	lock_write(&pgrphash_lock)
#define PGRPHASH_TRY_WRITE_LOCK()	lock_try_write(&pgrphash_lock)
#define PGRPHASH_UNLOCK()	lock_done(&pgrphash_lock)
#define PGRPHASH_LOCK_INIT()	lock_setup(&pgrphash_lock, \
						pgrphash_lockinfo, TRUE)

/*
 * PER-STRUCT LOCKS FOR MP SYNCHRONIZATION
 */

/*
 * Multiprocessor exclusion to a proc data structure.
 * Procs are annoying but must be kept around for backwards
 * compatibility.
 */
udecl_lock_info(extern, proc_lockinfo)
#define	PROC_LOCK_TRY(p)	usimple_lock_try(&(p)->p_lock)
#define	PROC_LOCK(p)		usimple_lock(&(p)->p_lock)
#define	PROC_UNLOCK(p)		usimple_unlock(&(p)->p_lock)
#define PROC_LOCK_ADDR(p)	usimple_lock_addr((p)->p_lock)
#define PROC_LOCK_INIT(p)	usimple_lock_setup(&(p)->p_lock, proc_lockinfo)
#define PROC_LOCK_TERMINATE(p)	usimple_lock_terminate(&(p)->p_lock)

#define PID_ENTRY_LOCK(pe)	usimple_lock(&(pe)->pe_lock)
#define PID_ENTRY_UNLOCK(pe)	usimple_unlock(&(pe)->pe_lock)

#define	PROC_INTR_VAR(v)
#define PROC_INTR_LOCK(p, s)	PROC_LOCK(p)
#define PROC_INTR_UNLOCK(p, s)	PROC_UNLOCK(p)

/*
 * The proc timer lock must always be held at splhigh and must be higher
 * than the time lock in the locking hierarchy.
 */
udecl_simple_lock_info(extern, proc_timer_lockinfo)
#define	PROC_TIMER_LOCK(p)	usimple_lock(&(p)->p_timer_lock)
#define	PROC_TIMER_UNLOCK(p)	usimple_unlock(&(p)->p_timer_lock)
#define	PROC_TIMER_LOCK_INIT(p) \
		usimple_lock_setup(&(p)->p_timer_lock, proc_timer_lockinfo)
#define	PROC_TIMER_LOCK_TERMINATE(p) \
		usimple_lock_terminate(&(p)->p_timer_lock)

/*
 * Interface to other struct-specific locks.
 */
udecl_simple_lock_info(extern, sess_lockinfo)
#define	SESS_LOCK(s)		usimple_lock(&(s)->s_lock)
#define	SESS_UNLOCK(s)		usimple_unlock(&(s)->s_lock)
#define	SESS_LOCK_INIT(s)	usimple_lock_setup(&(s)->s_lock, sess_lockinfo)
#define	SESS_LOCK_TERMINATE(s)	usimple_lock_terminate(&(s)->s_lock)

udecl_simple_lock_info(extern, sess_fpgrp_lockinfo)
#define	SESS_FPGRP_LOCK(s)	usimple_lock(&(s)->s_fpgrp_lock)
#define	SESS_FPGRP_UNLOCK(s)	usimple_unlock(&(s)->s_fpgrp_lock)
#define	SESS_FPGRP_LOCK_INIT(s) \
		usimple_lock_setup(&(s)->s_fpgrp_lock, sess_fpgrp_lockinfo)
#define	SESS_FPGRP_LOCK_TERMINATE(s) \
		usimple_lock_terminate(&(s)->s_fpgrp_lock)

udecl_lock_info(extern, pgrp_lockinfo)
#define	PGRP_READ_LOCK(pg)	ulock_read(&(pg)->pg_lock)
#define	PGRP_WRITE_LOCK(pg)	ulock_write(&(pg)->pg_lock)
#define	PGRP_WRITE_TO_READ(pg)	ulock_write_to_read(&(pg)->pg_lock)
#define	PGRP_UNLOCK(pg)		ulock_done(&(pg)->pg_lock)
#define	PGRP_WRITE_TO_READ_UNLOCK(pg)	lockmode == 0 ? (void)0 : pg_write_to_read_unlock((pg))
#define	PGRP_WRITE_UNLOCK(pg)	lockmode == 0 ? (void)0 : pg_write_unlock((pg))
#define PGRP_TRY_WRITE_LOCK(pg)	ulock_try_write(&(pg)->pg_lock)
#define PGRP_TRY_READ_LOCK(pg)	ulock_try_read(&(pg)->pg_lock)
#define	PGRP_LOCK_INIT(pg)	ulock_setup(&(pg)->pg_lock, pgrp_lockinfo,TRUE)
#define	PGRP_LOCK_TERMINATE(pg)	ulock_terminate(&(pg)->pg_lock)

udecl_simple_lock_info(extern, pgrp_refcnt_lockinfo)
#define PGRP_REFCNT_LOCK(pg)	usimple_lock(&(pg)->pg_ref_lock)
#define PGRP_REFCNT_UNLOCK(pg)	usimple_unlock(&(pg)->pg_ref_lock)
#define PGRP_REFCNT_LOCK_INIT(pg) \
		usimple_lock_setup(&(pg)->pg_ref_lock, pgrp_refcnt_lockinfo)
#define PGRP_REFCNT_LOCK_TERMINATE(pg) \
		usimple_lock_terminate(&(pg)->pg_ref_lock)

#include <kern/macro_help.h>

/*
 *	The signal lock is really just a flag to show whether the
 *	process is suspending for job control or tracing by ptrace
 *	or /proc. On entry to issig() and psig(), a thread checks
 *      the state of p_sig_wait (the "signal lock") with the
 *	sig_wait_check() macro. If the signal lock is set or the
 *	process appears to exiting or exec'ing (p_end_thread set),
 *	the thread attempts to comply with the stop request. Later on,
 *	if the thread takes a signal that must cause the process to
 *	stop, it sets p_sig_wait under the proc lock to prevent any
 *	other thread from entering. All such state transisitions occur
 *	under the proc lock, so that no other thread can enter signal
 *	processing until the thread already there selects its signal
 *	to process.
 *
 *	Unlocked (p_sig_wait = 0 && p_end_thread == 0)  simple lock.
 *	Waiting (p_sig_wait != 0) - Drop proc_lock after acquiring it, and
 *		call thread_block().  Thread that set the lock to
 *		wait has done a task_suspend().
 *	Exiting (p_end_thread != 0) - The thread in p_end_thread is going to
 *		call exit()/exec(). If we're not that thread, permanently stop
 *		in favor of that thread. If we're that thread, immediately
 *		bail out (no signal processing is permitted once we're
 *		committed to exit) and indicate that signals should not be
 *		processed. If we have been asked to halt, bail out and
 *		indicate that signals should be processed (to clean up any
 *		saved state).
 *
 *	The logic for this is in the sig_lock_or_return macro.
 */

/*
 *	Try to grab signal lock.  If we are already exiting,
 *	execute 'false_return'.  If some other thread is exiting,
 *	block.  If we must halt, execute 'true_return'.
 *
 *	Must be called with proc lock held; returns the same way.
 */
#define sig_lock_or_return(p, false_return, true_return)	\
MACRO_BEGIN							\
	while ((p)->p_sig_wait || (p)->p_end_thread) {		\
	    if ((p)->p_end_thread) {				\
		if (current_thread() == (p)->p_end_thread) {	\
		    /* Already exiting - no signals. */	\
		    PROC_UNLOCK(p);				\
		    false_return;				\
		} else {					\
		    thread_t thread = current_thread();		\
		    spl_t s;					\
		    /* Another thread has called exit */	\
		    /* or exec - stop (until terminate request*/\
		    /* or restarted). Set the flag to allow us*/\
		    /* to undo this hold if an exec() fails. */	\
		    s = splsched();				\
		    thread_lock(thread);			\
		    thread->flags |= TF_EXEC;			\
		    thread_unlock(thread);			\
		    (void) splx(s);				\
		    thread_hold(thread);			\
		}						\
	    } else {						\
		thread_t thread = current_thread();		\
		if (!(thread->state & (TH_SUSP|TH_WAIT)) &&	\
		     (thread->timer_set == TIMER_FALSE))	\
			assert_wait_mesg_timo(			\
				(vm_offset_t)&(p)->p_sig_wait,	\
				FALSE, "sigwait", hz/2);	\
	    }							\
	    PROC_UNLOCK(p);					\
	    thread_block();					\
	    if (thread_should_halt(current_thread())) {		\
		/* Terminate request - clean up. */		\
		true_return;					\
	    }							\
	    PROC_LOCK(p);					\
	}							\
MACRO_END

/*
 * wait_check: see whether it is safe to do signal processing,
 * with proc already locked
 */
#define sig_wait_check(p, false_return, true_return)		\
MACRO_BEGIN							\
	sig_lock_or_return((p), false_return, true_return);	\
MACRO_END

/*
 * wait_lock/unlock: prevent/allow other threads from processing signals
 */
#define sig_wait_lock(p)	(p)->p_sig_wait = TRUE;

#define sig_wait_unlock(p)					\
MACRO_BEGIN							\
			(p)->p_sig_wait = FALSE;		\
			thread_wakeup((vm_offset_t)&(p)->p_sig_wait);	\
MACRO_END

/*
 * thread_ex_exit() also shuts down all other threads except the
 * current one. If task_halt fails, then cooperate with any attempt
 * to halt this thread. After this, the lock must be reacquired via a
 * full sig_lock.
 *
 * Called with process locked; returns unlocked with task suspended.
 */
#define thread_ex_exit(p)					\
MACRO_BEGIN							\
	PROC_LOCK(p);						\
	(p)->p_end_thread = current_thread();			\
	(p)->p_sig_wait = FALSE;				\
	thread_wakeup((vm_offset_t)&(p)->p_sig_wait);		\
	PROC_UNLOCK(p);						\
	while (task_halt(current_task()) != KERN_SUCCESS) {	\
		PROC_LOCK(p);					\
		(p)->p_end_thread = THREAD_NULL;		\
		PROC_UNLOCK(p);					\
		while (thread_should_halt(current_thread())) {	\
			thread_halt_self();			\
		}						\
		PROC_LOCK(p);					\
	        sig_lock_or_return(p, return, return);		\
		(p)->p_end_thread = current_thread();		\
		PROC_UNLOCK(p);					\
	}							\
	/* All threads halted except ours, make sure p_end_thread*/\
	/* is pointing to our thread.  Note no locks needed...*/\
	(p)->p_end_thread = current_thread();			\
MACRO_END

/*
 * thread_ex_exit_2() is similar to the above thread_ex_exit() except   
 * this macro uses return statements that return zero
 */
#define thread_ex_exit_2(p)					\
MACRO_BEGIN							\
	PROC_LOCK(p);						\
	(p)->p_end_thread = current_thread();			\
	(p)->p_sig_wait = FALSE;				\
	thread_wakeup((vm_offset_t)&(p)->p_sig_wait);		\
	PROC_UNLOCK(p);						\
	while (task_halt(current_task()) != KERN_SUCCESS) {	\
		PROC_LOCK(p);					\
		(p)->p_end_thread = THREAD_NULL;		\
		PROC_UNLOCK(p);					\
		while (thread_should_halt(current_thread())) {	\
			thread_halt_self();			\
		}						\
		PROC_LOCK(p);					\
	        sig_lock_or_return(p, return(0), return(0));	\
		(p)->p_end_thread = current_thread();		\
		PROC_UNLOCK(p);					\
	}							\
	/* All threads halted except ours, make sure p_end_thread*/\
	/* is pointing to our thread.  Note no locks needed...*/\
	(p)->p_end_thread = current_thread();			\
MACRO_END
#endif	/* _KERNEL */

#define PGRPHSZ		128
#define PGRPHASH(pid)	((pid) & (PGRPHSZ - 1))

#define UIDHSZ		128
#define UIDHASH(uid)	((uid) & (UIDHSZ - 1))

#define GIDHSZ		128
#define GIDHASH(gid)	((gid) & (GIDHSZ - 1))

#define MAX_PER_LIST                            8

#define MIN_HASHSZ                              128
#define MAX_HASHSZ                              2048

extern unsigned long hash_sz;

#define IDHASH(id)	((id) & (hash_sz - 1))

#ifdef	_KERNEL

struct _kill_data_t {
	uid_t           kd_p_ruid;      /* u.u_procp->p_ruid */
	gid_t        	kd_p_rgid;      /* for compat to u.u_procp->p_rgid */
	pid_t		kd_p_pid;	/* u.u_procp->p_pid */
    	pid_t       	kd_pg_id;          /* for compat to u.u_procp->p_pgid */
	struct session *kd_pg_session; 	/* for compat to u.u_procp->p_session */
	pid_t		kd_s_id;	/* u.u_procp->p_session->s_id */
	uid_t		kd_p_cr_uid;	/* u.u_procp->p_rcred->cr_uid */
	uid_t       	kd_p_rcr_uid;   /* For compat to u.u_procp->p_rcred->cr_uid */
	short		kd_s_id_gen;	/* generation number for session */
	int		kd_rev;		/* revision of struct */
	ulong		kd_spare[8];	/* spare space for growth */
#ifdef SEC_ARCH
	privvec_t       kd_si_epriv;    /* SIP->si_epriv */
#endif
};

typedef struct _kill_data_t kill_data_t;

void copy_kill_data_in(struct proc *, kill_data_t *);
int kill_common(kill_data_t *, pid_t, int);

extern int npid;	/* number of pid_entry structs in initial pidtab */
extern pid_t PID_RSRVD;	/* tcgetpgrp() result when no foreground pgrp */
extern struct ht_list	*uidhash;
extern struct ht_list	*gidhash;
extern struct pgrp	*pgrphash[PGRPHSZ];

#define NQS	32		/* 32 run queues */

#define	PROC_NULL	((struct proc *)0)
#define	PID_NULL	((struct pid_entry *)0)

/*
 * Pid's which are less than zero are out of range.
 * All other values are potentially valid, even if they
 * are cluster PIDs on a foreign node. The pfind() call
 * will handle those. PID_INVALID is used to check for
 * EINVAL in most PID-related system calls.
 *
 * In some cases, wait4/kill, negative pids are process group ids.  These
 * cases are handled appropriately.  The second half of this macro becomes
 * a no-op if PID_MAX is maximal for its type.  Note that the first half
 * of this macro is always evaluated because a pid_t must be a signed type.
 */
#define	PID_INVALID(pid) ((pid_t)(pid) < 0)


/*
 * Check cluster fields: nodeid and sequence number.
 * Should check for PID_INVALID first.
 */
extern int memberid, memberseq;

extern boolean_t pid_islocal(pid_t);
extern boolean_t pid_goodseq(pid_t);
extern boolean_t is_kernel_pid(pid_t);
extern boolean_t is_init_pid(pid_t);

#define PID_ISLOCAL(pid) pid_islocal(pid)  /* Is this PID on this node? */
#define PID_GOODSEQ(pid) pid_goodseq(pid)  /* Is node at the right seq#? */
#define IS_KERNEL_PID(pid) is_kernel_pid(pid) /* is this pid kernel task */
#define IS_INIT_PID(pid)  is_init_pid(pid)   /* is this pid the init task */

/*
 * Caller must ensure that pg_session, s_leader don't change.
 * p is always current proc.
 */
#define SESS_LEADER(p)	((p)->p_pgrp->pg_session->s_leader == (p))

/*
 * Caller must lock p to ensure consistent snapshot of state.
 */
#define PROC_ACTIVE(p)	((p)->p_stat != 0 && (p)->p_stat != SZOMB && \
			!((p)->p_flag & SWEXIT))

#define P_REF_LOCKED(p)	((!PROC_ACTIVE((p))) ? 0 : ++(p)->p_refcnt)	
#define P_REF		proc_ref
#define P_UNREF		proc_unref
#define PG_REF		pgrp_ref
#define PG_UNREF	pgrp_unref

/*
 * Declarations/prototypes for "process-related" kernel functions:
 */

struct processor_set;
struct processor_affinity_group;

/*
 * Functions in kern_exit.c:
 */
extern	int	exit(register struct proc *p, int rv);
#ifdef	COMPAT_43
extern	int	waitf(register struct proc *q, void *args, long retval[]);
#endif
extern void proc_delete(struct proc *);
extern void proc_release_pid(struct proc *);

/*
 * Functions in kern_prot.c:
 */
extern	void	uidadd(struct proc *, uid_t);
extern	void	gidadd(struct proc *, uid_t);
extern	void	idrm(struct proc *);

/*
 * Functions in kern_fork.c:
 */
extern	int	fork1(struct proc *, void *, int, long *, boolean_t);
extern	struct thread *
		newproc(struct proc *, struct pid_entry *,
			boolean_t, struct processor_set *,
			struct processor_affinity_group *);
extern	void	uarea_init(struct thread *th);
extern	void	uarea_zero(struct thread *th);
extern	void	utask_lock_init(struct utask *utaskp);

/*
 * Functions in kern_proc.c:
 */
extern	int		inferior(struct proc *p);
extern	boolean_t	thread_ex_check(struct proc *p);
extern	void		thread_ex_end(struct proc *p, int);
extern	boolean_t	thread_fork_check(struct proc *p);
extern	void		thread_fork_end(struct proc *p);
extern	struct pid_entry *pid_alloc(void);
extern	void		pid_free(struct pid_entry *pe);
extern	int		pid_free_count(void);
extern	int		pid_inuse_count(void);
extern	int		pid_total_count(void);
extern	int		pid_table_bounds(int table_index,
				struct pid_entry **start_p,
				struct pid_entry **end_p);
extern	struct proc	*pe_to_locked_proc(struct pid_entry *);
extern	struct proc	*proc_find_by_vpi(int index);
extern	struct pid_entry *pe_find_by_pid(pid_t pid);
extern	struct proc	*proc_find_by_pid(pid_t pid);
extern	struct proc	*proc_find_by_pid_nolock(pid_t pid);
extern	struct proc 	*pfind(pid_t pid);
extern	int		proc_ref(struct proc *p);
extern	void		proc_unref(struct proc *p);
extern	struct		pgrp *pgfind(pid_t pgid);
extern	int		pgrp_ref(struct pgrp *pg);
extern	int		pgrp_unref(struct pgrp *pg);
extern	int		pgmv(struct proc *p, pid_t pgid, int mksess);
extern	void		pgrm(struct proc *p);
extern	void		pgdelete(struct pgrp *pgrp);
extern	void		fixjobc(struct proc *,struct pgrp *,int,struct proc *);
extern	int		expand_pidtab(int target);
extern	int		active_procs(void);
extern	struct proc 	*get_parent(struct proc *p);
extern	pid_t		get_next_used_pid(pid_t pid);
#if	MACH_KDB || BSD_KDB
extern	void		proc_print(struct proc *p);
extern	void		pgrp_print(struct pgrp *pgrp);
#endif

/*
 * Functions defined in kern_sig.c
 */
extern	void	siginit(struct proc *);
extern	void	execsigs(struct proc *);
extern	void	gsignal(pid_t, int);
extern	int	psignal_internal(struct proc *, int, int, k_siginfo_t *);
extern	void	pgsignal_inthread(struct pgrp *, int, int);
extern	void	pgsignal_inthread_locked(struct pgrp *, int, int);
extern	void	pgsignal_inthread_self(struct pgrp *, int, int);
extern	void	psignal_inthread(struct proc *, int);
extern	int	checksig(struct proc *, struct np_uthread *);
extern	int	issig(void);
extern	void	psig(int);
extern	int	core(int);
extern	int	cansignal(struct proc *, struct proc *, int);
extern	void	sendsig(sig_t, long, sigset_t, k_siginfo_t *, int);
extern	void	table_sigdata(struct proc *, sigset_t *, sigset_t *,
			      sigset_t *);
extern	void	procfs_sigdata(struct sigaction *, struct proc *, int, int);
extern	void	fakeu_sigdata(struct user *, struct proc *);
extern	void	sigexit(struct proc *, int);
extern	int	sigdisp_fork(struct proc *, struct proc *,
			     struct sigacthdr *, int);

#if	PSIGNAL_THREAD
extern	sig_event_t *psignal_indirect_alloc(void);
extern	void	psignal_indirect_free(sig_event_t *);
extern	void	psignal_indirect_post(struct proc *, int, k_siginfo_t *,
				      int, sig_event_t *);
extern	void	psignal_indirect(struct proc *, int, k_siginfo_t *);
extern	void	psignal_indirect_info(struct proc *, int, k_siginfo_t *);
extern	void	pgsignal_indirect(struct pgrp *, int, int);
extern	void	psignal_thread(void);
#endif

/*
 * Functions from bsd/mach_signal.c
 */
extern	void	thread_psignal(struct thread *, long, k_siginfo_t *);

/*
 * Functions from bsd/kern_sigqueue.c
 */
extern void sigq_enqueue_head(queue_t q, sigqueue_t qp);
extern void sigq_enqueue_tail(queue_t q, sigqueue_t qp);
extern sigqueue_t sigq_find_next_sig(queue_t, sigqueue_t, int);
extern int sigq_remove_all(queue_t, int, struct thread *);
extern void sigq_credit_ast(void);
extern void sigq_credit_sender(sigqueue_t);
extern int sigq_only_one(queue_t, int);
extern void sigqueue_requeue(queue_t, sigqueue_t *);
extern int sigq_abort(struct proc *, sigqueue_t);
extern sigqueue_t sigq_reclaim(struct proc *, sigqueue_t);

/*
 * Functions from vm/vm_unix.c
 */
extern struct thread *procdup(struct proc *, struct proc *, boolean_t,
				struct processor_set *,
				struct processor_affinity_group *);

extern void session_release(struct session *);
/*
 * Internal kernel define to turn on multi-channel wait support
 */
#define MULTI_CHANNEL_WAIT_ENABLED 
#endif	/* _KERNEL */
#endif	/* ASSEMBLER */

/*
 * flags for pid_block() call
 */
#define	PID_BLOCK_MULTI_CHANNEL_WAIT 0x10

/*
 * types for pid_unblock call
 */
#define	PID_BLOCK_PIDUNBLOCK	0x10U
#define	PID_BLOCK_RDG		0x20U
#define	PID_BLOCK_AIO		0x40U

#define PID_BLOCK_TYPE_FIELD	0xf0U

#ifdef __cplusplus
}
#endif
#endif	/* _SYS_PROC_H_ */

