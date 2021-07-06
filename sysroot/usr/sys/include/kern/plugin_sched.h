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
 * @(#)$RCSfile: plugin_sched.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 2000/11/02 17:43:33 $
 */
/*
 * Aurema Pty. Limited has provided specific written authorization to
 * Compaq Computer Corporation to include the source material found
 * in this file in the Tru64 UNIX product.  Possession and use of this
 * material is authorized by Compaq Computer Corporation to licensed
 * users of the Tru64 UNIX binary or source product.  No other right
 * to use this source material is implied by possession thereof.
 */

/*
 * This computer program is a proprietary trade secret of  Aurema Pty. Limited.
 * Possession and use of this program shall be strictly in accordance with a
 * license agreement between the user and Aurema Pty. Limited.  Receipt and
 * possession of this program does not convey any rights to divulge, reproduce,
 * or allow others to use it without specific written authorization of Aurema
 * Pty. Limited.
 *
 * Copyright 2000, an unpublished work by Aurema Pty. Limited.  All rights
 * reserved.
 */

#ifndef	_TRU64_PLUGIN_SCHED_H
#define	_TRU64_PLUGIN_SCHED_H

#include <kern/thread.h>

typedef void (*plugin_sched_void_t)(thread_t);
typedef int (*plugin_sched_int_t)(thread_t);
typedef void (*plugin_sched_pri_t)(thread_t, int);

/*
 * Pointers to functions defined in a plugin scheduler module. Initialised by
 * a call to install_plugin_sched() from the module. See below for a
 * description of each callback.
 */
extern const plugin_sched_void_t plugin_sched_receive_ticks;
extern const plugin_sched_void_t plugin_sched_new_thread;
extern const plugin_sched_void_t plugin_sched_thread_exiting;
extern const plugin_sched_int_t plugin_sched_get_priority;
extern const plugin_sched_pri_t plugin_sched_prio_change;
extern const plugin_sched_pri_t plugin_sched_rt_prio_change;

/*
 * Atomic variables used to keep track of how many calls to each class of
 * plugin scheduler functions are in progress. 'new' applies to new_thread(),
 * 'exit' to exit_thread() and 'other' to all the other functions.
 */
extern long plugin_sched_new_ref_cnt;
extern long plugin_sched_exit_ref_cnt;
extern long plugin_sched_other_ref_cnt;

/*
 * Macros for atomically incrementing/decrementing the call counts on the
 * plugin scheduler's functions. Used on every call so that calls executing
 * at module unload time are allowed to finish, after which the module can
 * be safely unloaded.
 */
#define	PLUGIN_SCHED_NEW_REF()		atomic_incl(&plugin_sched_new_ref_cnt)
#define	PLUGIN_SCHED_NEW_UNREF()	atomic_decl(&plugin_sched_new_ref_cnt)
#define	PLUGIN_SCHED_EXIT_REF()		atomic_incl(&plugin_sched_exit_ref_cnt)
#define	PLUGIN_SCHED_EXIT_UNREF()	atomic_decl(&plugin_sched_exit_ref_cnt)
#define	PLUGIN_SCHED_OTHER_REF()	atomic_incl(&plugin_sched_other_ref_cnt)
#define	PLUGIN_SCHED_OTHER_UNREF()	atomic_decl(&plugin_sched_other_ref_cnt)

/*
 * The macro used to invoke a plugin scheduler function. All calls will ignore
 * the idle task.
 */
#define	PLUGIN_SCHED_CALL(thread, func, type, FNCLASS)			\
	MACRO_BEGIN							\
	plugin_sched_ ## type ## _t	plugin_sched_fn;		\
									\
	if ((plugin_sched_fn = plugin_sched_ ## func ) &&		\
	    !IS_KERNEL_PID((task_to_proc(thread->task))->p_pid)) {	\
		PLUGIN_SCHED_ ## FNCLASS ## _REF();			\
		(*plugin_sched_fn)(thread);				\
		PLUGIN_SCHED_ ## FNCLASS ## _UNREF();			\
	}								\
	MACRO_END

/*
 * The data structure passed by a kernel module to install_plugin_sched(),
 * to initialise the corresponding global variables above. Upon successful 
 * registration, the functions pointed to in this struct will be called at 
 * relevant points in the code if they are not NULL.
 */
typedef struct plugin_sched {
	/*
	 * The version number of the plugin scheduler interface
	 */
	int			version;
	/*
	 * A boolean indicating whether scheduling is to be performed (ie.
	 * whether get_priority() and receive_ticks() will be called).
	 */
	int			do_scheduling;
	/*
	 * This function is called when a thread has finished its current
	 * quantum or is about to be switched out. The CPU ticks used by this
	 * thread are accounted for and its time quantum is reset.
	 */
	plugin_sched_void_t	receive_ticks;
	/*
	 * Called when a new thread enters the system.
	 */
	plugin_sched_void_t	new_thread;
	/*
	 * Called when a thread exits the system.
	 */
	plugin_sched_void_t	thread_exiting;
	/*
	 * Called when a POLICY_TIMESHARE thread has its priority changed
	 * via nice or priocntl.
	 */
	plugin_sched_pri_t	prio_change;
	/*
	 * Called when a real-time thread has its priority changed.
	 */
	plugin_sched_pri_t	rt_prio_change;
	/*
	 * Called to calculate the thread's priority.
	 */
	plugin_sched_int_t	get_priority;
	/*
	 * Called during plugin scheduler installation to initialise the
	 * private data of all existing threads on the system.
	 */
	plugin_sched_void_t	init_existing_thread;
	/*
	 * Called during plugin scheduler uninstallation to clean up the
	 * private data of all existing threads on the system.
	 */
	plugin_sched_void_t	deinit_thread;
	/*
	 * The name of the plugin scheduler being installed.
	 */
	char			*name;
} plugin_sched_t;

/*
 * Error codes for install_plugin_sched()
 */
#define	PLUGIN_SCHED_INVAL_STRUCT	-1
#define	PLUGIN_SCHED_ALREADY_INSTD	-2
#define	PLUGIN_SCHED_VERSION_MISMATCH	-3

extern void plugin_sched_init(void);
extern int install_plugin_sched(plugin_sched_t *);
extern int deinstall_plugin_sched(void);
extern int plugin_sched_get_scheduling(void);
extern void plugin_sched_set_scheduling(int);

#endif	/* _TRU64_PLUGIN_SCHED_H */

