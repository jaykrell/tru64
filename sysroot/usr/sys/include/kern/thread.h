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
 * @(#)$RCSfile: thread.h,v $ $Revision: 4.3.134.2 $ (DEC) $Date: 2002/01/29 20:33:29 $
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
 *	File:	thread.h
 *	Author:	Avadis Tevanian, Jr.
 *
 *	This file contains the structure definitions for threads.
 */

#ifndef _SYS_USER_H_
#include <sys/user.h>
#endif

#ifndef	_KERN_THREAD_H_
#define _KERN_THREAD_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef	_KERNEL
#include <mach_host.h>
#endif	/* _KERNEL */

#include <mach/policy.h>
#include <mach/port.h>
#include <mach/message.h>
#include <mach/boolean.h>
#include <mach/machine/vm_types.h>
#include <kern/ast.h>
#include <kern/event.h>
#include <kern/queue.h>
#include <kern/processor.h>
#include <kern/task.h>
#include <kern/timer.h>
#include <kern/lock.h>
#include <kern/sched.h>
#include <sys/cpuset.h>
#include <kern/thread_modes.h>
#include <kern/kern_msg.h>
#include <kern/processor.h>
#include <machine/thread.h>
#include <machine/pcb.h>
#include <vm/vm_object.h>
#include <procfs/procfs.h>

/*
 * Affinity enumeration type definition
 */
typedef enum affinity_type {
	TH_BIND_NONE,
	TH_PROCESSOR_BIND,
	TH_RAD_BIND,
	TH_RAD_ATTACH
} affinity_t;

/*
 * Affinity descriptor definition
 */
struct affinity_desc {
	affinity_t		which;
	int			funnel_depth;
	void			*ptr;
};

typedef struct affinity_desc affinity_desc_t;
typedef struct affinity_desc *affinity_desc_p;


/*
 * Thread structure definition (one for each runnable context)
 *
 * Wait events which use thread structure addresses:
 *
 *	&thread->suspend_count	waiting for thread halt (TF_WAKE_ACTIVE)
 *	&thread->th_pag		waiting for pag assignment (TF_ASSIGN_WAIT)
 *	&thread->nxm_flags	nxm thread events (NXM_WAKEUP in nxm_flags)
 *	&thread->swap_state	swapin (TH_SW_MAKE_UNSWAPPABLE in swap_state)
 */
struct thread {
    /* 64-byte-aligned section of highly contested mostly locked data */
	decl_simple_lock_data(,lock)	/* thread structure lock */
	int		state;		/* thread state (see below) */
	int		flags;		/* thread flags (see below) */
	boolean_t	interruptible;	/* interruptible wait? */
	int		th_psusp_count;	/* suspend prevention count */
	vm_offset_t	wait_event;	/* event we are waiting on */
	char		*wait_mesg;	/* wait message string ptr */
	unsigned int	wait_type;	/* wait queue type code */
	kern_return_t	wait_result;	/* code for outcome of wait */
	unsigned int	sleep_stamp;	/* last time in TH_WAIT state */
	int		timer_set;	/* timeout set on wait w/cpuid */
	int		nxm_flags;	/* flags for 2-level scheduler */
	int		lock_count;	/* number of complex locks acquired */

    /* 64-byte-aligned section of read-mostly (rarely modified) data */
	task_t		task;		/* Task to which I belong */
	pmap_t		pmap;		/* pamp for this thread */
	struct stack_layout *stack;	/* pointer to stack/pcb/uthread */
	struct memory_affinity_domain *th_mad;	   /* current memory home */
	struct processor_affinity_group *th_pag;   /* current scheduling home */
	struct lock_read_rec_list *lock_recread_list;
	affinity_desc_t	sched_binding;

    /* 64-byte-aligned section containing counts and scheduling data */
	int		ref_count;	/* number of references to me */
	int		suspend_count;	/* internal use only */
	int		user_stop_count; /* outstanding stops */
	int		swap_state;	/* swap state (or unswappable flag) */
	unsigned int	max_priority;	/* maximum priority */
	int		depress_priority_cpu; /* cpu timeout queued to */
	long		time_remaining;	/* for psx 4 clocks and timers */
	int		ast;		/* ast's needed -- see ast.h */
	int		th_class;	/* index into class_list array */
	boolean_t	vm_privilege;	/* can use reserved memory? */
	int		policy;		/* scheduling policy */
	unsigned int	priority;	/* thread's priority */
	int		depress_priority; /* depressed from this priority */
	unsigned int	sched_pri;	/* scheduled (computed) priority */
	unsigned int	sched_stamp;	/* last time priority was updated */

    /* 64-byte-aligned section of scheduling and timing data */
	unsigned long	sched_usage;	/* load-weighted cpu usage [sched] */
	unsigned long	sched_delta;	/* weighted cpu usage since update */
	unsigned int	cpu_usage;	/* exp. decaying cpu usage [%cpu] */
	unsigned int	cpu_delta;	/* cpu usage since last update */
	int		th_quantum;	/* thread's calculated quantum */
	int		rmng_quantum;	/* remaining quantum for RR */
	timer_data_t	user_timer;	/* user mode timer */
	timer_data_t	system_timer;	/* system mode timer */
	timer_save_data_t user_timer_save; /* saved user timer value */
	timer_save_data_t system_timer_save; /* saved sys timer value */

    /* 64-byte-aligned section of data used during context switches */
	queue_chain_t	links;		/* current run queue links */
	run_queue_t	runq;		/* pointer to thread's run queue */
	processor_t	last_processor;	/* processor this thread last ran on */
	unsigned long	last_run_stamp;	/* time when switched off processor */
	int		wakeup_in_progress; /* removed from wait queue flag */
	int		th_start_time;	/* sched_tick when thread created */
	long		th_rq_enter;	/* time put on runqueue */
	long		th_rq_wait_sum;	/* sum of rq wait time */

    /* 64-byte-aligned section containing linked list pointers */
	queue_chain_t	thread_list;	/* links for all threads in task */
	queue_chain_t	class_links;	/* links for all threads in s.c. */
	queue_chain_t	pag_threads;	/* links for all threads in pag */
	queue_chain_t	sigwaitq;	/* queue links for sigwaiting */

    /* 64-byte-aligned section containing IPC-related data */
	decl_simple_lock_data(,ipc_state_lock) /* Locks most IPC fields */
	msg_return_t	ipc_state;	/* Operation state after awakening */
	boolean_t	ipc_kernel;	/* ipc buffer in kernel space */
	union {
		msg_size_t msize;	/* Maximum size of msg to receive */
		kern_msg_t kmsg;	/* Message that was received */
	} ipc_data;
	port_name_t	local_name;	/* quick pick port name */
	port_t		thread_self;	/* Port representing this thread */
	port_t		thread_reply;	/* Initial reply port for RPCs */
	port_name_t	reply_port;	/* See kern/mig_support.c. */
	port_name_t	kern_reply_port;/* ... ditto ... */

    /* 64-byte-aligned section boundary */	
	port_t		exception_port;

	struct t_procfs t_procfs;	/* /proc thread-specific data */
	vm_offset_t	lw_va;		/* lw_wire va */
	unsigned long	lw_pages;	/* lw_wire no. pages */
	int		speculative_state; /* speculative execution state */
	int		nxm_slot;	/* cpu index if nxm thread */
	struct nxm_sched_state *nxm_sptr; /* sched state if nxm thread */
	int		lock_hierarchy;	/* highest lock hierarchy level */
	int		lock_unordered;	/* mixed hierarchy in lock_addr */
	lock_t		*lock_addr;	/* pointers to locks acquired */

    /* 64-byte-aligned section boundary */	

	simple_lock_data_t *nxm_lockp;	/* pointer to per-thread nxm lock */
	decl_simple_lock_data(,nxm_thread_lock) /* NXM bound thread lock */
	struct nxm_vp_info *nxm_vip;	/* pointer to kernel per-VP info */
	queue_chain_t	th_specop_link; /* chain used to record in flight ops */
	struct rad 	*th_rad;	/* desired RAD to run in */
	unsigned int 	th_migrate_stamp; /* time in seconds of last migrate */
	unsigned int	th_sem_val_wait; /* value sysV semaphore waiting on */
#ifdef	CONFIG_PLUGIN_SCHED_OFF
	long		pad2;	
#else	/* CONFIG_PLUGIN_SCHED_OFF */
	void		*plugin_data;	/* private data for plugin schedulers */
#endif	/* CONFIG_PLUGIN_SCHED_OFF */
};

typedef struct thread *thread_t;

#define THREAD_NULL	((thread_t)0)

/* thread state bits */
#define TH_WAIT		0x01	/* thread is queued for waiting */
#define TH_SUSP		0x02	/* thread has been asked to stop */
#define TH_RUN		0x04	/* thread is running or on runq */
#define TH_SWAPPED	0x08	/* thread is swapped out */
#define TH_IDLE		0x10	/* thread is an idle thread */

/* thread flags */
#define TF_KERNEL_VM	0x0001	/* th->task->kernel_vm_space */
#define TF_INHERIT_BNDG	0x0002	/* inherit processor bindings */
#define TF_WAKE_ACTIVE	0x0004	/* thread halt was requested */
#define TF_PSX4_SLEEP	0x0008	/* psx4 sleep w/oitvp active */
#define TF_SHUTDOWN	0x0010	/* thread suspended by cpu shtudown */
#define TF_EXEC		0x0020	/* thread suspended by exit/exec */
#define TF_CLASS_SUSP	0x0040	/* thread is class suspended */
#define TF_PSUSP	0x0080	/* thread can't be suspended */
#define TF_ACTIVE	0x0100	/* how alive is the thread */
#define TF_HALTED	0x0200	/* halted at clean point? */
#define TF_MAY_ASSIGN	0x0400	/* whether pset may be reassigned */
#define TF_ASSIGN_WAIT	0x0800	/* assignment completion wakeup wanted */
#define TF_SWAPPER_WAKEUP       0x1000
#define TF_MIGRATER	0x2000  /* in process of migrating another task */

/* thread wait_type values */
#define TH_OLD_WAIT	0	/* hash-based wait event */
#define TH_NEW_WAIT	1	/* local wait queue */
#define TH_LOCK_WAIT	2	/* complex lock wait queue */

/* value for "timer_set" field when no timer is active */
#define TIMER_FALSE	-1

/* thread speculative_state bits */
#define	TH_SPEC_SEGV	1	/* thread expects a segv fault */
#define	TH_SPEC_BUS	2	/* thread expects a bus fault */
#define	TH_SPEC_FPE	4	/* thread expects a floating point fault */

/* thread nxm_state bits */
#define NXM_IDLE	0x1	/* idle with no sched context */
#define NXM_SCHED	0x2	/* sched context valid */
#define NXM_NOSCHED	0x4	/* no sched context valid */
#define NXM_BLOCKED	0x8	/* blocked NXM thread */
#define NXM_BIND_ME	0x10	/* I'm special, sooo special! */
#define NXM_BOUND	0x20	/* user thread bound to kernel thread */
#define NXM_EXEC	0x40	/* exec in progress */
#define NXM_RESCHED	0x80	/* force resched */
/*			0x100	   used to be NXM_RIP -- no longer used */
#define NXM_SIGEV	0x200	/* signal event pending */
#define NXM_MANAGER	0x400	/* thread is a manager */
#define NXM_WAKEUP	0x800	/* thread wakeup is pending */
#define NXM_SUSPEND	0x1000	/* library suspend in effect */
#define NXM_RESUME_POSTED 0x2000 /* resume posted against unsuspended thread */

struct super_thread {
	struct thread thread;
	struct np_uthread np_uthread;
};

#define thread_to_np_uthread(th) (&((struct super_thread *)(th))->np_uthread)

typedef	port_t	*thread_array_t;	/* XXX compensate for MiG */

#ifdef	_KERNEL

extern thread_t *idle_thread_ptrs;

/*
 *	User routines
 */

extern kern_return_t	thread_create(
				task_t		parent_task,
				thread_t	*child_thread);
extern kern_return_t	thread_terminate(thread_t thread);
extern kern_return_t	thread_suspend(thread_t thread);
extern kern_return_t	thread_resume(thread_t	thread);
extern kern_return_t	thread_abort(thread_t	thread);

extern kern_return_t	thread_get_special_port(
				thread_t	thread,
				int		which_port,
				port_t		*port);
extern kern_return_t	thread_set_special_port(
				thread_t	thread,
				int		which_port,
				port_t		port);
extern kern_return_t	thread_assign(
				thread_t	thread,
				processor_set_t	new_pset);
extern kern_return_t	thread_assign_default(thread_t	thread);

#if 0	/* notyet */
extern kern_return_t	thread_get_state(
				thread_t	thread,
				int		flavor,
		/* XXXXX */	thread_state_t	old_state,
				unsigned int	*old_state_count);
extern kern_return_t	thread_set_state(
				thread_t		thread,
				int			flavor,
		/* XXXXX */	thread_state_t		new_state,
				unsigned int		new_state_count);
extern kern_return_t	thread_info(
				thread_t		thread,
				int			flavor,
		/* XXXXX */	thread_info_t		thread_info_out,
				unsigned int		*thread_info_count);
#else
extern kern_return_t	thread_get_state();
extern kern_return_t	thread_set_state();
extern kern_return_t	thread_info();
#endif


/*
 *	Kernel-only routines
 */

extern void		thread_init(void);
extern void		thread_reference(thread_t thread);
extern void		thread_deallocate(thread_t thread);
extern void		thread_hold(thread_t thread);
extern void		thread_hold_delayed(thread_t thread);
extern kern_return_t	thread_dowait(
				thread_t	thread,
				boolean_t	must_halt);
extern void		thread_release(thread_t thread);
extern void		thread_swappable(
				thread_t	thread,
				boolean_t	is_swappable);
extern void		thread_force_terminate(thread_t thread);
extern kern_return_t	thread_halt(
				thread_t	thread,
				boolean_t	must_halt);
extern void		thread_halt_self(void);
extern thread_t		kernel_thread(task_t task, void (*start)());
extern thread_t		kernel_isrthread(task_t, void (*)(), int);
extern thread_t		kernel_isrthread_w_arg(task_t, void (*)(), void *, int);
extern thread_t		kernel_thread_w_arg(task_t, void (*)(), void *);
extern thread_t		rad_kernel_isrthread(void (*)(), void *, int, int);
extern thread_t		rad_kernel_thread(void (*)(), void *, int, int);
extern void		thread_doexception(
				thread_t	thread,
				unsigned long	exception,
				unsigned long	code,
				unsigned long	subcode);
extern void		reaper_thread(int rad_id);
extern void		pcb_init(thread_t thread, pag_t);
extern boolean_t    	thread_is_stopped(thread_t);
extern void		thread_set_binding(thread_t th,
					   affinity_t bind_type,
					   void *target,
					   boolean_t inherit);

#if	MACH_HOST
extern void		thread_freeze(thread_t thread);
extern kern_return_t	thread_doassign(
				thread_t	thread,
				processor_set_t	new_pset,
				boolean_t	release_freeze);
extern void		thread_unfreeze(thread_t thread);
#endif

#if defined(_USE_KERNEL_PROTOS)

extern void pcb_terminate(struct thread *thread);
extern void pcb_synch(thread_t thread);
extern void pcb_fixup(struct thread *thread);
extern void initial_context(thread_t thread);
extern void thread_start(thread_t thread, void (*start)(void), long mode, void *arg);
extern kern_return_t thread_setstatus(thread_t thread, long flavor,
				thread_state_t tstate, unsigned long count);
extern kern_return_t thread_getstatus(thread_t thread, long flavor,
				thread_state_t tstate, unsigned int *count);
extern kern_return_t thread_create_internal(task_t, thread_t *, boolean_t,
					processor_set_t, pag_t);
extern void thread_dup(thread_t parent, thread_t child);
extern void cr_threadinit(thread_t);

#endif /* defined(_USE_KERNEL_PROTOS) */

/*
 *	Macro-defined routines
 */

#define thread_pcb(th)		(&(th)->stack->pcb)

#define thread_lock(th)		simple_lock(&(th)->lock)
#define thread_unlock(th)	simple_unlock(&(th)->lock)
#define thread_lock_terminate(th) simple_lock_terminate(&(th)->lock)

#define thread_should_halt(th) \
	((th)->ast & (AST_SCHED_USER|AST_HALT|AST_TERMINATE|AST_SUSPEND|AST_SIGEXIT))

#define ipc_thread_lock(th)	simple_lock(&(th)->ipc_state_lock)
#define ipc_thread_unlock(th)	simple_unlock(&(th)->ipc_state_lock)
#define ipc_thread_lock_terminate(th) \
				simple_lock_terminate(&(th)->ipc_state_lock)

/*
 * Machine-specific implementations of the current thread macro
 * designate this by defining CURRENT_THREAD.
 */
#ifndef	CURRENT_THREAD
#define current_thread()	(processor_ptr[cpu_number()]->active_thread)
#define current_task()		(current_thread()->task)
#endif

/*
 * NXM lock macros
 */
#define NXM_LOCK(__th__)						\
	simple_lock((__th__)->nxm_lockp)

#define NXM_UNLOCK(__th__)						\
	simple_unlock((__th__)->nxm_lockp)

/*
 * Provide the processor_t/rad_t to which the thread is bound only if
 * the thread is assigned CPU/RAD affinity.
 */
#define GET_BOUND_PROCESSOR(__th__)					\
	(((__th__)->sched_binding.which == TH_PROCESSOR_BIND) ?	\
	(__th__)->sched_binding.ptr : NULL)

/*
 * Obtain the type from an affinity descriptor
 */
#define THREAD_BINDING_TYPE(__th__)	((__th__)->sched_binding.which)

/*
 * Determine whether the thread has been assigned processor or RAD
 * affinity.
 */
#define THREAD_IS_BOUND(__th__)						\
	(THREAD_BINDING_TYPE((__th__)) != TH_BIND_NONE)

/*
 * Macros used to access the funnel depth in an affinity descriptor
 */
#define THREAD_IS_FUNNELED(__th__)					\
	((__th__)->sched_binding.funnel_depth != 0)

#define INCREMENT_FUNNEL_DEPTH(__th__)					\
	++(__th__)->sched_binding.funnel_depth

#define DECREMENT_FUNNEL_DEPTH(__th__)					\
	--(__th__)->sched_binding.funnel_depth

#define CLEAR_FUNNEL_DEPTH(__th__)					\
MACRO_BEGIN								\
	(__th__)->sched_binding.funnel_depth = 0;			\
MACRO_END

/*
 * Obtain the processor_t to which the thread is bound while also
 * considering whether the thread is funneled.  Use this macro when
 * performing scheduling/dispatching functions.
 */
#define GET_THREAD_BINDING(__th__)					\
	(THREAD_IS_FUNNELED(__th__) ? master_processor :		\
		GET_BOUND_PROCESSOR(__th__))

/* 
 * Return the number of threads bound to the specified processsor.
 */
#define GET_PROCESSOR_NUM_BOUND_THREADS(__processor__)			\
	(__processor__)->thread_affinity_count

/*
 * Copy only the binding information from an affinity descriptor.  Never
 * inherit the funnel depth from another thread.
 */
#define COPY_SCHED_BINDING(__from__, __to__)				\
MACRO_BEGIN								\
    thread_set_binding((__to__), (__from__)->sched_binding.which,	\
                       (__from__)->sched_binding.ptr, FALSE);		\
    (__to__)->sched_binding.funnel_depth = 0;				\
MACRO_END

/*
 * Macros to perform CPU/RAD bind/attach operations
 */
#define THREAD_BIND_TO_CPU(__th__, __cpu__, __inherit__)		\
MACRO_BEGIN								\
    thread_set_binding((__th__), TH_PROCESSOR_BIND, (__cpu__),		\
                       (__inherit__));					\
MACRO_END

#define THREAD_BIND_TO_RAD(__th__, __radset__, __inherit__)		\
MACRO_BEGIN								\
    thread_set_binding((__th__), TH_RAD_BIND, (__radset__),		\
                       (__inherit__));					\
MACRO_END

#define THREAD_ATTACH_TO_RAD(__th__, __radset__, __inherit__)		\
MACRO_BEGIN								\
    thread_set_binding((__th__), TH_RAD_ATTACH, (__radset__),		\
                       (__inherit__));					\
MACRO_END

#define THREAD_CLEAR_BINDING(__th__)					\
MACRO_BEGIN								\
    thread_set_binding((__th__), TH_BIND_NONE, NULL, FALSE);		\
MACRO_END

#include <kern/sched_prim.h>

/*
 * Kernel thread-specific data definitions and function prototypes
 */
typedef int tsd_key_t, *tsd_key_p;

#define TSD_SUCCESS     0
#define TSD_FAILURE     -1

void tsd_init(void);
int tsd_key_create(tsd_key_p keyp);
int tsd_key_destroy(tsd_key_t key);
int tsd_register_callback(tsd_key_t key, void (*callback)(void *));
int tsd_setspecific(tsd_key_t key, void *val);
void *tsd_getspecific(tsd_key_t key);

#define TH_SUSPEND_OFF() current_thread()->th_psusp_count++
#define TH_SUSPEND_ON() current_thread()->th_psusp_count--

#endif	/* _KERNEL */

#ifdef __cplusplus
}
#endif
#endif	/* _KERN_THREAD_H_ */
