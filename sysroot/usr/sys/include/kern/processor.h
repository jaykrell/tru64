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
 *	@(#)$RCSfile: processor.h,v $ $Revision: 4.3.72.13 $ (DEC) $Date: 2002/06/02 02:06:31 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */

/*
 *	processor.h:	Processor and processor-set definitions.
 *
 */

#ifndef	_KERN_PROCESSOR_H_
#define	_KERN_PROCESSOR_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 *	Data structures for managing processors and sets of processors.
 */

#include <mach/boolean.h>
#include <sys/types.h>
#include <sys/lwc.h>
#include <kern/lock.h>
#include <mach/policy.h>
#include <mach/port.h>
#include <kern/queue.h>
#include <kern/sched.h>
#include <sys/callout.h>
#include <mach/kern_return.h>
#include <sys/malloc.h>
#include <sys/namei.h>
#include <sys/vnode.h>
#include <sys/random.h>
#include <sys/audit.h>

#ifdef _KERNEL
#include <sys/cpuset.h>
#include <sys/class.h>
#endif /* _KERNEL */

#ifdef __cplusplus
struct task;
#endif

#ifdef _KERNEL
#include <machine/pmap.h>

struct pag_load {
	int	pl_pag_id;
	long	pl_pag_load;	

};

struct processor_set {
	simple_lock_data_t	lock;		/* lock for everything else */
	boolean_t		empty;		/* true if no processors */
	int			ref_count;	/* structure ref count */
	boolean_t		active;		/* is pset in use */
	int			task_count;	/* number of tasks */
	queue_head_t		tasks;		/* tasks in this set */
	queue_chain_t		all_psets;	/* link for all_psets */
	queue_head_t		pag_list;	/* list pset affinity groups */
	port_t			pset_self;	/* port for operations */
	port_t			pset_name_self;	/* port for information */
	unsigned int		max_priority;	/* maximum priority */
	int			policies;	/* bit vector for policies */
	int			pset_id;	/* unique identifier */
	int			state;		/* e.g., exclusive access */
	struct task		*task;		/* task with excl. access */
	struct timeval		pset_create_time; /* creation time */
	simple_lock_data_t	class_lock;
	struct class_sched	*class_sched;	/* class scheduler data */
	struct pag_load		*pag_load_sorted;
	long			pad[19];
};

typedef	struct processor_set *processor_set_t;
typedef port_t *processor_set_array_t;

#define MAX_CPUS_PER_RAD 32

struct processor_affinity_group {
    /* 64-byte alignment */
	long			pag_spare0;
	long			pag_sched_load;	/* load avg for scheduler */
	long			pag_mach_factor;/* mach_factor */
	long			pag_load_average;/* load_average */
	struct memory_affinity_domain
				*pag_mad;	/* memory affinity */
	int			pag_ref_count;	/* structure ref count */
	int			pag_thread_count;/* number of threads */
	queue_head_t		pag_threads;	/* threads in this */

    /* 64-byte alignment */
	int			pag_id;		/* affinity group number */
	int			pag_set_quantum;/* current default quantum */
	processor_set_t		pag_pset;	/* pset sd belongs to */
	queue_chain_t		pag_list;	/* link for pag in pset */
	queue_head_t		pag_processors;	/* all processors here */
	cpuset_t		pag_processor_mask;/* mask of all processors */
	int			pag_processor_count;/* number of processors */
	int			pag_controlling_cpu; /*controlling cpu for pag*/

    /* 64-byte alignment */
	simple_lock_data_t	pag_idle_lock;	/* lock for below */
	int			pag_idle_count;	/* number of processors */
	int			pag_spare;
	queue_head_t		pag_idle_queue;	/* idle processors */
	struct run_queue	pag_runq;	/* runq for this set */

    /* 64-byte alignment */
	int			pag_sar_runqueue;
	int			pag_spare1;
	long			pag_idle_avg;	/* 5 second average idle time */
	long			pag_cur_load;   /* last second load avg */
	int			remote_cnt;	
	int			spare4;
	long			remote_load_average;
	long			spare5[3];

    /* 64-byte alignment */
	struct processor *pag_processor_list[MAX_CPUS_PER_RAD];

    /* 64 byte alignment */
	long	send_cnt;	/* count of threads migrated off pag */
	long	last_sender; 	/* time stamp of last migrate off pag */
	long	recv_cnt;	/* count of thread migrated to pag */
	long	last_receiver;	/* time stamp of last migrate to pag */
	int	out_of_balance; /* load avg is lower then desired for pset */
	int	spare6;
	long 	pag_desired_load; 
	long	spare7[2];	

};

typedef	struct processor_affinity_group *pag_t;


#define PAG_NULL		(pag_t) 0
#define PROCESSOR_SET_NULL	(processor_set_t)0
#define PROCESSOR_SET_NAME_NULL	(processor_set_t)0

#endif /* _KERNEL */

struct processor_stats {
	int local_hot_dispatch;		/* dispatch off local runq + hot */
	int local_warm_dispatch;
	int local_cold_dispatch;
	int global_hot_dispatch;
	int global_warm_dispatch;
	int global_cold_dispatch;
	int idle_hot_dispatch;
	int idle_warm_dispatch;
	int idle_cold_dispatch;
	int load_balance_steals;	/* steals because of load balance */
	int load_balance_steals_trys;	/* attempts to steal for load balance */
	int load_balance_idle_steals;	/* steals while idle */
	int same_thread_count;		/* false context switches */
	int remote;
	int processor_spare2;
	int processor_spare3;
};

#ifdef _KERNEL
#include <sys/time.h>
#include <sys/sysaio.h>
#include <svr4/sar.h>
#include <mach/machine.h>

#define VM_PERF_MAX	128	/* space for vm perf stats */
#define INETSTATS_MAX	256	/* space for the inet stats */

#define NFSSTATS_MAX	120	/* space for NFS client stats */
#define RFSSTATS_MAX	192	/* space for NFS server stats */
#define RPCSTATS_MAX	72	/* space for RPC stats */
				/* 120+192+72 == 384, or 3KB */
#define	SCHED_MAX_DISTANCE 63	/* maximum number of hops to schedule over */

struct processor {
    /* 64-byte alignment */
	struct thread	*active_thread;
	int		slot_num;	/* machine-independent slot number */
	int		restart_pset_id; /* processor set to restart on */
	int		latest_asn;
	int		asn_wrap_point;
	unsigned long	asn_wrap_count;
	int		cpu_slowdown_enabled;	
	int		ticks_to_skip;	/* # of clock ticks to skip */
	queue_chain_t	processor_rad_queue;
	long		sema;

    /* 64-byte alignment */
	int		ip_interrupt_req; /*inter-processor interrupt request*/
	int		thread_affinity_count; /* number of bound threads */
	struct pmap_update_info pmap_update;
	volatile unsigned long rt_psignal_data;
	int		rt_defer;
	int		rt_sent;
	int		it_lost_tick_cnt;
	char		pad1[4];

    /* 64-byte alignment */
	long		cpu_ticks[CPU_STATE_MAX];
	long		p_lbolt;
	int		rt_cnt;
	int		int_cnt;
	int		load_cnt;
	int		idle_cnt;

    /* 64-byte alignment */
	simple_lock_data_t callout_lock; /* lock for below */
	struct		callout	*calltodo;
	struct		callout *abs_calltodo;
	long		callout_lbolt;	
	struct		callout *callfree;
	int		ncallfree;
	int		prc_flags;
	queue_head_t	psignal_queue;
	struct		callout	*rt_calltodo[6]; /* spl 6 work requeuing */
	struct timeval	start_stop_time; /* processor start/stop time */
	struct timeval	pset_assign_time; /* assigned to pset time */

    /* 64-byte alignment */
	struct thread	*idle_thread;	/* this processor's idle thread */
	processor_set_t	processor_set;	/* processor set pointer */
	pag_t		processor_pag;	/* processor affinity group */
	struct memory_affinity_domain *processor_mad; /* memory affinity */
	queue_chain_t	processors;	/* links in processor set list */
	struct rad	*processor_rad;
	int		processor_rad_logical_index; /* cpu # within the rad */
	int		unused;

    /* 64-byte alignment */
	unsigned int	sched_tick;	/* timestamp for last priority recalc */
	int		quantum;	/* quantum for current thread */
	int		first_quantum;	/* first quantum in succession */
	int		out_of_balance;	/* set if below balance point */
	long		desired_load;
	long		load_avg;	/* average run queue depth */
	long		rt_load_avg;	/* average bound rt load */
	long		int_load_avg;	/* average interrupt load */
	long		idle_avg;	/* average idle time */
	long		cur_load_avg;	/* average for last second */

    /* 64-byte alignment */
	simple_lock_data_t lock;
	struct thread	*next_thread;	/* next thread to run if dispatched */
	queue_chain_t	processor_queue; /* idle/assign/shutdown queue link */
	int		state;		/* processor state (see below) */
	int		bio_wait_state;	/* waiting for I/O */
	processor_set_t processor_set_next; /* next set of assignment */
	port_t		processor_self;	/* port for operations */
	port_t		processor_name_self; /* port for information */

    /* 64-byte alignment -- offset 512 from top of structure */
	struct machine_slot m;
	struct buf	*ubc_iodone_buf;
	struct buf	*swap_iodone_buf;
	struct buf	*MsfsIodoneBuf;
	struct buf	*cludrd_iodone_buf;
	void            *clucfs_stats;   /* statistics for cfs */
	u_long		cpu_clock_rate_raw;
	int		cpu_clock_rate_mhz;
	int		pad2;
	vm_size_t	num_cache_bytes;
	long		proc_type;
	pag_t		processor_helper_pag;
	char		pad3[32];

    /* 64-byte alignment */
	volatile u_char	*prfbuftab[8];		/* xcpu printf request table */

	struct timeval	pcc_time;
	long		pcc_pcc;
	long		pcc_delta_t;
	long		pcc_divisor;
	long		microset_calls;
	long		pcc_upper_limit;
	long		pcc_lower_limit;
	long		spare4;

    /* 64-byte alignment -- system-correctable error (sce) handling */
	long		sce_period;
	long		sce_last;
	long		sce_first;
	long		sce_threshold;
	long		sce_warn;
	long		sce_count;
	long		spare7;
	long		spare8;

    /* 64-byte alignment -- processor-correctable error (pce) handling */
	long		pce_period;
	long		pce_last;
	long		pce_first;
	long		pce_threshold;
	long		pce_warn;
	long		pce_count;
	long		mces_state;

	struct stack_layout *restart_stack;	/* cpu's boot/restart stack */

    /* 64-byte alignment */
	int		*numa_dist_hoptab;	/* hop table indexed by radid */
	radid_t		*numa_dist_radtab;	/* rad table ordered by dist */
	int		one_entry_hoptab;	/* used only when nrads == 1 */
	radid_t		one_entry_radtab;	/* used only when nrads == 1 */
	int		p_sched_dist;
	int		p_sched_cpu_migrate_switch;
	struct run_queue runq;			/* processor's local runq */

    /* 64-byte alignment -- offset 2K from top of structure */
	struct percpukmembuckets *kmem_ptr[128];

    /* 64-byte alignment -- offset 3K from top of structure */
	struct sar_data sar;

    /* 64-byte alignment */
	struct processor_stats pstats;		/* stats on runq activities */

    /* 64-byte alignment */
	struct nchstats nchstats;		/* name cache stats */

    /* 64-byte alignment */
	struct vnode_stats vnode_stats;		/* vnode table stats */

    /* 64-byte alignment */
	long		kmemtypetblp[M_LAST_KL_COMP];
	void		*ocla_ptr;		/* OCLA state information (opaque) */

    /* 64-byte alignment -- offset 5K from top of structure */
	long		vm_perf[VM_PERF_MAX];	/* vm performance data */

    /* 64-byte alignment -- offset 6K from top of structure */
	unsigned long	inetstats[INETSTATS_MAX]; /* inet stat structs */

    /* 64-byte alignment -- offset 8K from top of structure, 3 K long */
	unsigned long	nfsstats[NFSSTATS_MAX]; /* NFS stat structs */
	unsigned long	rfsstats[RFSSTATS_MAX];
	unsigned long	rpcstats[RPCSTATS_MAX];

    /* 64-byte alignment -- offset 11K from top of structure */
	struct nchash	*nchash;		/* replicated nameicache */
	struct namecache *namecache;		/* namecache entry array */
	int		nchash_valid;		/* Is nchash table expired? */
	char		pad7[44];

    /* 64-byte alignment */
	queue_lock_data_t lockq[NQLCKS_MAX];	/* processor's lock queue */

    /* 64-byte alignment */
       /* ran_batch and one of ran_do_XXX_hook and ran_XXX_state will be
	* accessed together on each XXX interrupt
	*/
       struct random_batch_queue *ran_batch;           /* /dev/random incoming entropy */
       boolean_t                 ran_do_net_hook;      /* network ether_input() packet */
       struct random_timer_state ran_net_state;        /* history for entropy estimate for network */
       boolean_t                 ran_do_blkdev_hook;   /* disk-like devices biodone() */
       struct random_timer_state ran_blkdev_state;     /* history for entropy estimate for blkdev */
       boolean_t                 ran_do_keyboard_hook; /* keyboard scan code/state */
       struct random_timer_state ran_keyboard_state;   /* history for entropy estimate for keyboard */
       boolean_t                 ran_do_mouse_hook;    /* mouse buttons/motion */
       struct random_timer_state ran_mouse_state;      /* history for entropy estimate for mouse */
       /*
	*  ran_prime, ran_second, and ran_sthread are only set here if they are
	* configured per-CPU; they could each also be configured per-RAD
	* (in struct rad) or PER-System (in global variables).
	*
	* These pointers are used seldom and could be moved to another cache block.
	*/
       struct random_entropy_store *ran_prime;         /* primary entropy pool -- data moves from batch_queue to here */
       struct random_entropy_store *ran_second;        /* secondary entropy pool -- data moves from primary to here */
       struct thread               *ran_sthread;       /* thread to migrate entropy from primary to secondary */
       int pad8[8];		                       /* pad to 64-byte boundary */

    /* 64-byte alignment */
#ifdef DEBUG_RANDOM_TIMINGS
       struct random_stats         ran_time;           /* some statistics (multiple of 64-bytes) */
#else
       unsigned long pad9[sizeof(struct random_stats)/sizeof(unsigned long)]; /* avoid struct processor size change */
#endif

    /* 64 byte alignment */
	long dist_counter[SCHED_MAX_DISTANCE+1];

    /* 64-byte alignment -- audit (aud) subsystem */
	struct audit_per_processor aud;		/* buffer & statistics data */

    /* 64 byte alignment */

};

typedef struct processor *processor_t;
typedef port_t *processor_array_t;

#define PROCESSOR_NULL		(processor_t)0
#define PROCESSOR_NAME_NULL	(processor_t)0

#endif /* _KERNEL */

/*
 *	NOTE: The processor->processor_set link is needed in one of the
 *	scheduler's critical paths.  [Figure out where to look for another
 *	thread to run on this processor.]  It is accessed without locking.
 *	The following access protocol controls this field.
 *
 *	Read from own processor - just read.
 *	Read from another processor - lock processor structure during read.
 *	Write from own processor - lock processor structure during write.
 *	Write from another processor - NOT PERMITTED.
 *
 */

/*
 *	Processor state locking:
 *
 *	Values for the processor state are defined below.  If the processor
 *	is off-line or being shutdown, then it is only necessary to lock
 *	the processor to change its state.  Otherwise it is only necessary
 *	to lock its processor set's idle_lock.  Scheduler code will
 *	typically lock only the idle_lock, but processor manipulation code
 *	will often lock both.
 */

#define PROCESSOR_OFF_LINE	0	/* Not in system */
#define	PROCESSOR_RUNNING	1	/* Running normally */
#define	PROCESSOR_IDLE		2	/* idle */
#define PROCESSOR_DISPATCHING	3	/* dispatching (idle -> running) */
#define	PROCESSOR_ASSIGN	4	/* Assignment is changing */
#define PROCESSOR_SHUTDOWN	5	/* Being shutdown */

#ifdef	_KERNEL

extern struct processor_set		default_pset;
extern struct processor_affinity_group	default_pag;

/*
 *	Chain of all processor sets.
 */
extern queue_head_t		all_psets;
extern int			all_psets_count;
decl_simple_lock_data(extern, all_psets_lock)

#ifndef REPLICATED
#define REPLICATED
#endif

/*
 *	Pointer to the master processor structure
 */
extern struct processor * REPLICATED master_processor;

/*
 *	Use processor ptr array to find current processor's data structure.
 *	This replaces a multiplication (index into processor_array) with
 *	an array lookup and a memory reference.  It also allows us to save
 *	space if processor numbering gets too sparse.
 */
extern struct processor ** REPLICATED processor_ptr;

#define cpu_to_processor(i)	(processor_ptr[i])	
#define cpu_to_machine_slot(i)	(cpu_to_processor(i) ? \
				 &cpu_to_processor(i)->m : NULL)	
#define cpu_to_sar(i)		(cpu_to_processor(i) ? \
				 &cpu_to_processor(i)->sar : NULL)
#define current_processor_set()	(current_processor()->processor_set)

#define LIVE_CPU_P(cpu_no, prc) /* note that "prc" is assigned in here */ \
	((prc = cpu_to_processor(cpu_no)) != PROCESSOR_NULL && \
	 (prc)->state != PROCESSOR_OFF_LINE && \
	 (prc)->state != PROCESSOR_SHUTDOWN)

/* Useful lock macros */

#define	pset_lock(pset)		simple_lock(&(pset)->lock)
#define pset_unlock(pset)	simple_unlock(&(pset)->lock)

#define processor_lock(pr)	simple_lock(&(pr)->lock)
#define processor_unlock(pr)	simple_unlock(&(pr)->lock)

#define load_avg(avg,last)  ((((avg)<<2) + (last) + ((avg) < (last)  ? 4:0))/5)

#define mark_bio_wait							\
	myprocessor = current_processor();				\
	__ATOMIC_INCREMENT_LONG(&myprocessor->bio_wait_state)

#define unmark_bio_wait							\
	__ATOMIC_DECREMENT_LONG(&myprocessor->bio_wait_state)

#define get_cpu_mhz(cpunum)						\
	(cpu_to_processor(cpunum)->cpu_clock_rate_mhz)
#define get_cpu_clock_rate(cpunum)					\
	(cpu_to_processor(cpunum)->cpu_clock_rate_raw)
#define get_processor_mhz(processor)        ((processor)->cpu_clock_rate_mhz)
#define get_processor_clock_rate(processor) ((processor)->cpu_clock_rate_raw)
#define get_cpu_type(cpunum)						\
	(cpu_to_processor(cpunum)->proc_type)
#define get_processor_type(processor) ((processor)->proc_type)

extern void cpu_up(int);
extern void cpu_down(int);

extern kern_return_t processor_assign(processor_t, processor_set_t, boolean_t);
extern kern_return_t processor_shutdown(processor_t);

extern void pset_sys_bootstrap(void);
extern void pset_init(processor_set_t);
extern void processor_init(processor_t, int, int);
extern int pset_remove_processor(processor_set_t, processor_t);
extern int pset_add_processor(processor_set_t, pag_t, processor_t);
extern void pset_remove_task(processor_set_t, struct task *);
extern int pset_add_task(processor_set_t, struct task *);
extern void pset_remove_thread(processor_set_t, struct thread *);
extern int pset_add_thread(processor_set_t, struct thread *);
extern void pset_deallocate(processor_set_t);
extern int pset_reference(processor_set_t);
extern int quantum_set(pag_t);
extern void numa_lb_thread(void);
extern void numa_mover(void);
extern void numa_move_current_thread(struct thread *, int);
extern int set_cpu_speed_and_type(int);
extern vm_size_t get_cache_size(int);
extern void pag_assign_pset(processor_set_t, pag_t);
extern void pag_init(pag_t);
extern void pag_remove_thread(pag_t, struct thread *);
extern void pag_add_thread(pag_t, struct thread *);
extern void pag_move_thread(pag_t, pag_t, struct thread *, boolean_t,
			    boolean_t);
extern void pag_deallocate(pag_t, boolean_t);
extern void pag_terminate(pag_t);
extern void pag_reference(pag_t, int);
extern pag_t pset_get_least_loaded_radid(processor_set_t, radset_t);
extern pag_t pset_get_least_loaded_pag(processor_set_t);
extern pag_t get_pag(processor_set_t, int);
extern pag_t get_cpu_pag(processor_set_t, int);
extern pag_t get_rid_pag(processor_set_t, int);
extern int cpu_to_rad_cost(int cpuid, radid_t radid);
extern void processor_mcs_init(processor_t, int);

struct check_state_arg {
	int	cpunum;
	int	state;
};

extern int processor_check_state(struct check_state_arg *);

/*
 * processor_flags 
 */
#define NEED_EHM_CPU_ONLINE     1
#define NEED_EHM_CPU_OFFLINE    2

/*
 * flags used by interrupt_distribute()
 */
#define FIRST_CPU_IN_RAD	0	/* controlling cpu added */
#define CPU_OFFLINE		1	/* CPU being shutdown */
#define PRIMARY_SWITCH		2	/* primary processor being changed */
#define INTR_QUERY		3	/* specified processors taking intrs? */
#define LOAD_BALANCE		4	/* load balance interrupts */
#endif	/* _KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* _KERN_PROCESSOR_H_ */
