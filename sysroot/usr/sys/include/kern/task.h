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
 * 
 */
/*	
 *	@(#)$RCSfile: task.h,v $ $Revision: 4.3.76.2 $ (DEC) $Date: 2002/05/22 19:08:46 $
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
 *	File:	task.h
 *	Author:	Avadis Tevanian, Jr.
 *
 *	This file contains the structure definitions for tasks.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/user.h>
#include <sys/proc.h>

#ifdef __cplusplus
}
#endif

#ifndef	_KERN_TASK_H_
#define _KERN_TASK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <mach_emulation.h>
#include <mach_ipc_tcache.h>
#include <mach/boolean.h>
#include <mach/port.h>
#include <mach/time_value.h>
#include <kern/lock.h>
#include <kern/queue.h>
#include <kern/mach_param.h>
#include <kern/kern_obj.h>
#include <kern/kern_set.h>
#include <kern/processor.h>
#include <kern/syscall_emulation.h>
#include <kern/processor.h>
#include <vm/vm_map.h>
#include <procfs/procfs.h>
#include <mach/task_info.h>
#include <kern/host.h>
#include <machine/nxm.h>
#include <kern/rad.h>

/*
 * 2-level scheduling state.
 */

struct nxm_vp_info {
    /* 64-byte alignment */
	simple_lock_data_t	nxm_vp_lock;
	struct thread		*nxm_active_sched;
	struct nxm_sched_state	*nxm_slot_ptr;
	int			nxm_extra_count;
	int			pad1[9];

    /* 64-byte alignment */
	wait_queue_data_t	nxm_vp_wq;
	long			pad2[4];

    /* 64-byte alignment */
	wait_queue_data_t	nxm_extra_wq;
	long			pad3[4];
};

struct nxm_rad_info {
    /* 64-byte alignment */
	unsigned int		nxm_pag_scs_count;
	int			pad1;
	unsigned long		pad2[7];

    /* 64-byte alignment */
	struct nxm_vp_info	nxm_vp[1];
};

struct nxm_task {
    /* 64-byte alignment */
	int 		_nxm_sched_max;		/* max scheduler threads */
	int		_nxm_sched_cnt; 	/* active scheduler threads */
	boolean_t	_nxm_extra_fail;	/* any thread creates fail? */
	int		pad1;
	struct thread	*_nxm_manager;		/* library's manager thread */
	sigset_t	_nxm_signal_upcall; 	/* signals needing upcalls */
        long            _nxm_task_callback;	/* library upcall routine */
        unsigned int	_nxm_task_version;	/* nxm version */
        unsigned short  _nxm_task_uniq_offset;	/* offset to TEB */
	short		pad2;
	int		_nxm_task_quantum;	/* quantum from task attr */
	unsigned int	_nxm_task_flags;	/* per-task NXM flags */
	unsigned long	pad3;

    /* 64-byte alignment */
        vm_offset_t          _nxm_user_cfg_addr;/* user va to config area */
	vm_size_t            _nxm_cfg_size;	/* size of config area */
	vm_size_t            _nxm_share_size;	/* size of shared areas */
        nxm_config_info_t   *_nxm_cfg_ptr;	/* shared config area */
	nxm_slot_state_t    *_nxm_vp_state;	/* slot state in nxm_cfg_ptr */
	struct nxm_shared  **_nxm_share;	/* ptr to shared areas */
	long		     _nxm_pset_event;
	long		     _nxm_save_pset_event;

    /* 64-byte alignment */
	long		     pad4[8];

    /* 64-byte alignment */
	struct nxm_rad_info *_nxm_private[1];	/* per-RAD VP data */
};

#define nxm_sched_max		nxm_state->_nxm_sched_max
#define nxm_sched_cnt  		nxm_state->_nxm_sched_cnt
#define nxm_extra_fail		nxm_state->_nxm_extra_fail
#define nxm_task_callback	nxm_state->_nxm_task_callback
#define nxm_task_version	nxm_state->_nxm_task_version
#define nxm_task_uniq_offset	nxm_state->_nxm_task_uniq_offset
#define nxm_task_quantum	nxm_state->_nxm_task_quantum
#define nxm_manager 		nxm_state->_nxm_manager
#define nxm_signal_upcall 	nxm_state->_nxm_signal_upcall
#define nxm_task_flags		nxm_state->_nxm_task_flags
#define nxm_user_cfg_addr	nxm_state->_nxm_user_cfg_addr
#define nxm_cfg_size		nxm_state->_nxm_cfg_size
#define nxm_share_size		nxm_state->_nxm_share_size
#define nxm_cfg_ptr		nxm_state->_nxm_cfg_ptr
#define nxm_vp_state		nxm_state->_nxm_vp_state
#define nxm_share		nxm_state->_nxm_share
#define nxm_pset_event		nxm_state->_nxm_pset_event
#define nxm_save_pset_event	nxm_state->_nxm_save_pset_event
#define nxm_private		nxm_state->_nxm_private

/*
 * NXM task flag definitions
 */
#define NXM_TASK_CPU_BIND_POLICY	0x00000001
#define NXM_TASK_RAD_BIND_POLICY	0x00000002
#define NXM_TASK_USER_BINDING		0x00000004

/*
 * Conversion macros
 */
#define NXM_INDEX_TO_RAD(__i__)						\
	((__i__) / cpus_per_rad)
#define NXM_INDEX_TO_SLOT(__i__)					\
	((__i__) % cpus_per_rad)

#define NXM_VP_PTR(__task__, __slot__)                                  \
        (__task__)->nxm_private[NXM_INDEX_TO_RAD(__slot__)]->nxm_vp[NXM_INDEX_TO_SLOT(__slot__)].nxm_slot_ptr

#define NXM_VP_INFO_PTR(__task__, __slot__)                             \
        &((__task__)->nxm_private[NXM_INDEX_TO_RAD(__slot__)]->nxm_vp[NXM_INDEX_TO_SLOT(__slot__)])

/*
 * Macro to determine whether task uses two-level scheduling
 */
#define IS_NXM_TASK(__task__)						\
	((__task__)->nxm_state != NULL)

/*
 * Per-VP locking macros
 */
#define NXM_EXTRA_LO_WATERMARK	5
#define NXM_EXTRA_HI_WATERMARK	15

#define NXM_NO_TIMEOUT  	UINT_MAX

#define OBJ_CACHE_MAX		010	/* number of entries in object cache */
#define OBJ_CACHE_MASK		007	/* bit mask for object cache lookup */

/*
 * Task structure definition (one for each address space and file state)
 *
 * Wait events which use task structure addresses:
 *
 *	&task->processor_set	waiting for pset assignment (TA_ASSIGN_WAIT)
 *	&task->procfs.pr_trace_busy	waiting for procfs tracing
 */
struct task {
    /* 64-byte alignment */
	decl_simple_lock_data(,lock)	/* task's lock */
	int		ref_count;	/* number of references to task */
	int		thread_count;	/* number of threads */
	queue_head_t	thread_list;	/* list of threads */
	queue_chain_t	pset_tasks;	/* list of tasks assigned to pset */
	int		suspend_count;	/* internal scheduling only */
	int		user_stop_count; /* outstanding stops */
	int		res_thread_count; /* number of resident threads */
	int		task_flags;	/* miscellaneous flags (see below) */

    /* 64-byte alignment */
	vm_map_t	map;		/* address space description */
	struct nxm_task *nxm_state;	/* pointer to all 2-level state */
	processor_set_t	processor_set;	/* processor set for new threads */
	boolean_t	kernel_vm_space; /* Uses kernel's pmap? */
	boolean_t	active;		/* task has not been terminated */
	int		task_class;	/* scheduling class */
	int		policy;		/* task's scheduling "policy" */
	int		priority;	/* for new threads */
	int		max_priority;	/* max priority for task's threads */
	struct vnode	*proc_vnptr;	/* vnode in procfs if open via /proc */
	struct procfs	procfs;		/* /proc task-specific data */

	int		swap_state;	/* current swap state of task */
	int		swap_request;	/* current swap request of task */
	unsigned	inswap_stamp;	/* time of last inswap */
	unsigned	outswap_stamp;	/* time of last outswap */
	int		working_set;	/* # of pages reclaimed by swapper */
	int 		swap_nswap;	/* # of times this task swapped */
	struct swap_control *task_sc;	/* swap control structure */
	queue_chain_t	task_link;	/* ptr to next task on swap queue */

    /* 64-byte alignment */
	decl_simple_lock_data(,ipc_translation_lock)
	boolean_t	ipc_privilege;	/* Can use kernel resource pools? */
	boolean_t	ipc_active;	/* Can IPC rights be added? */
	queue_head_t	ipc_translations; /* Per-task port naming */
	port_name_t	ipc_next_name;	/* Next local name to use */
	int		ipc_name_conflict_test;	/* Whether conflict possible */
	boolean_t	kernel_ipc_space; /* Uses kernel's port names? */
	port_t		task_self;	/* Port representing the task */
	port_t		task_tself;	/* What the task thinks is task_self */
	port_t		task_notify;	/* Where notifications get sent */
	port_t		exception_port;	/* Where exceptions are sent */
	port_t		bootstrap_port;	/* Port passed on for task startup */
	int		task_class_flags; /* protected by class_lock */
	int		spare1;
	port_t		ipc_ports_registered[TASK_PORT_REGISTER_MAX];

    /* 64-byte alignment */
	struct {
		port_name_t	name;
		kern_obj_t	object;
	} obj_cache[OBJ_CACHE_MAX];	/* Fast object translation cache */

    /* 64-byte alignment */
	nsg_t		*task_nsg;	/* NUMA Scheduling Group */
	queue_chain_t	task_nsg_list;
	ulong_t		task_nsg_flags;	/* set when task is attached to NSG */
	struct	rad	*task_rad;	/* desired home for task */
	int		spare2[6];
};

typedef struct task *task_t;

#define TASK_NULL	((task_t)0)

/* bits in the task_flags field of the task structure */
#define TA_MAY_ASSIGN	0x0001	/* whether pset may be reassigned */
#define TA_ASSIGN_WAIT	0x0002	/* assignment completion wakeup wanted */
#define TA_SWAPPER_SUSP	0x0004	/* task swapper asked task to suspend */
#define TA_SWAPPER_STOP	0x0008	/* task is suspended */
#define TA_RAD_SPILLOVER 0x0080 /* refault on spillover has occured */
#define TA_MAP_OUT	0x00100 /* set when vm map is swapped out for task */
#define	TA_UNSWAPPABLE	0x00200 /* task is set unswappable */

/*
 * NUMA bind/attach request flags for nfork() and numa_syscalls()
 */
#define TASK_NUMA_BIND		0x0001	/* bind all threads to RAD */
#define TASK_NUMA_ATTACH	0x0002	/* attach all threads to RAD */
#define TASK_NUMA_INHERIT	0x0004	/* inherit RAD binding */

/* bits in the task_class_flags field. protected by class_lock */
#define TCF_PID_CLASS	0x0001	/* associated PID is class scheduled */
#define TCF_PID_ROOT	0x0002	/* real UID root PID is class scheduled */

struct super_task {
	struct task task;
	struct proc proc;
	struct utask utask;
};

#define task_to_proc(t)  ((struct proc *)&((struct super_task *)(t))->proc) 
#define task_to_utask(t) ((struct utask *)&((struct super_task *)(t))->utask) 
#define proc_to_task(p)	 ((struct task *)(((char *)(p)) - sizeof(struct task)))
#define proc_to_utask(p) ((struct utask *)(((char *)(p)) + sizeof(struct proc)))
#define utask_to_proc(ut) \
		((struct proc *)(((char *)(ut)) - sizeof(struct proc)))
#define utask_to_task(ut) \
		((struct task *)(((char *)(ut)) - sizeof(struct proc) - \
						  sizeof(struct task)))

typedef	port_t	*task_array_t;

/*
 * This typedef is necessary for the MiG generated interfaces for
 * task-related functions (vm_allocate, etc.) Inside the kernel,
 * the functions take vm_map_t's. The client side uses a task_t
 * (see mach/mach_types.h)
 */
typedef vm_map_t vm_task_t;

/*
 * Describes how a child inherits its parent's address space.
 *
 * 
 *	TI_NONE:        don't use parent's address space
 *	TI_INHERIT:     inherit parent's address space, i.e. COW
 *	TI_VFORK:	use vfork model (lazy swap task).
 */
typedef enum {TI_NONE, TI_INHERIT, TI_VFORK} task_inherit_t;

#ifdef	_KERNEL

#define task_lock(task)		simple_lock(&(task)->lock)
#define task_unlock(task)	simple_unlock(&(task)->lock)
#define task_lock_terminate(task) simple_lock_terminate(&(task)->lock)

#define ipc_task_lock(t)	simple_lock(&(t)->ipc_translation_lock)
#define ipc_task_unlock(t)	simple_unlock(&(t)->ipc_translation_lock)
#define ipc_task_lock_terminate(t) \
			simple_lock_terminate(&(t)->ipc_translation_lock)

/*
 *	Exported routines/macros
 */

extern kern_return_t	task_create_internal(
		task_t		parent_task,
		task_inherit_t	inherit_memory,
		task_t		 child_task,
		struct processor_affinity_group *pag);
extern kern_return_t	task_create(
		task_t		parent_task,
		task_inherit_t	inherit_memory,
		task_t		 child_task);
extern kern_return_t	task_terminate( task_t	task);
extern kern_return_t	task_suspend(task_t task);
extern kern_return_t	task_resume(task_t task);
extern kern_return_t	task_info(
		task_t		task,
		int		flavor,
		task_info_t	task_info_out,	/* pointer to OUT array */
		unsigned int	*task_info_count );	/* IN/OUT */
extern kern_return_t	task_get_special_port(
		task_t		task,
		int		which_port,
		port_t		*port);
extern kern_return_t	task_set_special_port(
		task_t		task,
		int		which_port,
		port_t		port );
extern kern_return_t	task_assign(
		task_t	task,
		processor_set_t	new_pset,
		boolean_t	assign_threads );
extern kern_return_t	task_assign_default(
		task_t		task,
		boolean_t	assign_threads );
/* XXXXX extern kern_return_t
 * task_threads(task_t task, thread_array_t *thread_list, unsigned int *count);
 */ extern kern_return_t	task_threads();

/*
 *	Internal only routines
 */

extern void		task_init(void);
extern void		task_reference( task_t task );
extern void		task_deallocate( task_t task );
extern kern_return_t	task_hold( task_t task );
extern kern_return_t	task_hold_delayed( task_t task );
extern kern_return_t	task_dowait( task_t task, boolean_t must_wait );
extern kern_return_t	task_release( task_t task );
extern kern_return_t	task_halt( task_t task );
extern kern_return_t	task_suspend_nowait( task_t task );
extern kern_return_t	task_suspend_self( boolean_t );
extern task_t		task_alloc(void);
extern void		task_free(task_t);
extern void		task_rad_fl_check(void);
extern task_t	kernel_task;

#endif	/* _KERNEL */

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif	/*_KERN_TASK_H_*/
