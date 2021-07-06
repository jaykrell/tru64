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
 * @(#)$RCSfile: class.h,v $ $Revision: 1.1.21.1 $ (DEC) $Date: 2001/10/25 16:52:20 $
 */

#ifndef _SYS_CLASS_H_
#define _SYS_CLASS_H_

/* temporary stuff that will probably live in apar_types.h */
typedef int apar_t;
#define APAR_SYSTEM		0
#define APAR_NONE		-1
/* end of temp stuff */

typedef struct partition_handle *class_apar_handle_t;

#define MAX_NUM_PARTITIONS	100
#define MAX_NUM_CLASSES		100
#define MAX_NUM_MEMBERS		2500

/*
 * class_scheduler_status codes.
 */
#define CL_STATE_DISABLED		0
#define CL_STATE_ENABLED		1

/* 
 * State info passed to the kernel periodically (bit mask).
 */
#define CL_STATE_DFLT_CLASS_INUSE	2
#define CL_STATE_ENFORCE_WHEN_IDLE	4

#define CLASS_DEFAULT_INDEX 	1

/*
 * class_scheduler event notification codes (mask).
 */
#define	CLASS_SCHED_EVENT_NONE	0x0
#define	CLASS_SCHED_EVENT_RGID	0x1
#define	CLASS_SCHED_EVENT_RUID	0x2
#define	CLASS_SCHED_EVENT_PSET	0x4
#define	CLASS_SCHED_EVENT_ADD	0x8
#define	CLASS_SCHED_EVENT_DEL   0x10
#define	CLASS_SCHED_EVENT_ALL	(CLASS_SCHED_EVENT_RGID | \
				 CLASS_SCHED_EVENT_RUID | \
				 CLASS_SCHED_EVENT_PSET | \
				 CLASS_SCHED_EVENT_ADD  | \
				 CLASS_SCHED_EVENT_DEL)

/*
 * classcntl() opcodes.
 */

#define CL_OP_ENABLE		0
#define CL_OP_DISABLE		1
#define CL_OP_GET_CLASS_LIST	2
#define CL_OP_ADD_TO_CLASS	3
#define CL_OP_DEL_FROM_CLASS	4
#define CL_OP_SET_CLASS_LIST	5
#define CL_OP_DAEMON_ALIVE	6
#define CL_OP_GET_PARTITION	7
#define CL_OP_IS_ENABLED	8
#define CL_OP_GET_PID_CLASS	9
#define CL_OP_ROOT_IN_CLASS	10

/* 
 * class member type codes.
 */
#define CL_TYPE_RESERVED	0
#define CL_TYPE_GID		1
#define CL_TYPE_UID		2
#define CL_TYPE_UNUSED		3
#define CL_TYPE_ALL		4
#define CL_TYPE_PGRP		5
#define CL_TYPE_SESS		6
#define CL_TYPE_PID		7
#define CL_TYPE_HIGHEST		7

struct class_cpu_list {
	int class_clock_ticks;
	int class_percent;
};

#ifndef _KERNEL

#include <sys/msg.h>
#include <sys/sem.h>

#define DBASE_NAME_LEN		80
#define CLASS_NAME_LEN		20
#define AVAIL			0

/*
 * default configuration values.
 */
#define DEFAULT_CLASS_IN_USE	0
#define DEFAULT_IDLE_ENFORCE	1
#define DEFAULT_DAEMON_RATE	1

#define CLASS_DEFAULT_FILE_BASE	"/etc/class/part."
#define CLASS_DEFAULT_FILE_NAME	"/etc/class/part.default"
#define CLASS_FILE_ID		'a'
#define CLASS_DAEMON_NAME	"/usr/sbin/class_daemon"
#define CLASS_DAEMON		"class_daemon"

#define CLASS_PARTITION_DIR	"/etc/class"

#define CLASS_AVAIL   "available"
#define CLASS_DEFAULT "default"
 
struct class_member {
	short 	type;		/* group, user, session etc. */
	short	external;	/* entry made by other than the admin program */
	int 	id;
	int	next_member;
	int	prev_member;
};
 
struct class_member_info {
	short 	type;		/* group, user, session etc. */
	int 	id;
};

/*
 * For class_change() or class_create() the union represents the resource
 * percentage available.  For statistical purposes, the union represents
 * the percentage of the resource actually being consumed.
 */ 
struct resource_limits {
	int	cpu_target_percent;	/* input only */
	union {				/* output only */
		int actual_percent;
		int available_percent;
	} cpu;

	int	mem_target_percent;	/* input only */
	union {				/* output only */
		int actual_percent;
		int available_percent;
	} mem;

	int	io_target_percent;	/* input only */
	union {				/* output only */
		int actual_percent;
		int available_percent;
	} io;

	int	net_target_percent;	/* input only */
	union {				/* output only */
		int actual_percent;
		int available_percent;
	} net;
	
	long	future_expansion[10];
};

/*
 * Specify these values in xxx_target if class scheduling for
 * resource xxx is not desired or 1f no changes are requested.
 */
#define CLASS_RESOURCE_SCHED_DISABLED	-1
#define CLASS_RESOURCE_NO_CHANGE	-2

struct class_param {
	char	name[CLASS_NAME_LEN];
	struct	resource_limits limits;
	int	num_members;
	int	first_member;
	int	last_member;
	int	future_expansion[6];
};

struct class_info {
	char	name[CLASS_NAME_LEN];
	struct	resource_limits limits;
	int	num_members;
};

/*
 * This is the main database that resides on disk and in shared memory.
 * Items marked "++" have meaning in memory only.
 */
#define VERSION 1

struct partition_dbase {
	int version;
	int part_id;			/* ++ */
	int sem_id;			/* ++ */
	short space_for_rent[3];
	int database_modified;		/* ++ */
	int future_expansion[10];
	int database_configured;
	int default_class_in_use;	/* configuration parameter */
	int daemon_rate;		/* configuration parameter */
        int enforce_when_idle;		/* configuration parameter */
        int first_class_in_use;
	int last_class_in_use;
	int first_member_empty;
	int last_member_empty;
	char dbase_name[DBASE_NAME_LEN];
	struct class_param	class[MAX_NUM_CLASSES];
	struct class_member	member[MAX_NUM_MEMBERS];
};

struct partition_handle {
	struct partition_dbase *shared_dbase;
	struct partition_dbase local_copy;
};

/* ask_yes_no() return codes */
#define ANSWER_NO		0
#define ANSWER_YES		1
#define ANSWER_UNCHANGED	2

/* class_xxx option codes (bit mask) */
#define OPT_DONT_FORCE		1
#define OPT_FORCE		2
#define OPT_EXTERNAL		4

/* library (libclass) function prototypes */

int 	class_add(class_apar_handle_t, char *, int, int, int);
int	class_change(class_apar_handle_t, char *, struct resource_limits *);
int	class_change_name(class_apar_handle_t, char *, char *);
int 	class_close(class_apar_handle_t);
int 	class_configure(class_apar_handle_t, int, int, int);
int	class_create(class_apar_handle_t, char *, struct resource_limits *);
int	class_database_modified(class_apar_handle_t);
int	class_database_name(class_apar_handle_t, char *);
int	class_delete(class_apar_handle_t, char *, int, int);
int	class_destroy(class_apar_handle_t, char *, int);
int	class_disable(class_apar_handle_t);
int	class_empty(class_apar_handle_t, char *);
int	class_enable(class_apar_handle_t);
int	class_get_classes(class_apar_handle_t, struct class_info *);
int	class_get_class_members(class_apar_handle_t,char *,struct class_member_info*);
int	class_get_config_stats(class_apar_handle_t, int *, int *, int *);
int	class_index_to_name(class_apar_handle_t, int, char *);
int	class_list_partition_ids(apar_t *, int *);
int 	class_load_database(class_apar_handle_t, char *, int);
int	class_open(apar_t, class_apar_handle_t *);
int	class_restore_database(class_apar_handle_t);
int 	class_save_database(class_apar_handle_t, char *);
int	class_scheduling_enabled(apar_t);
void	class_database_lock(class_apar_handle_t);
void	class_database_unlock(class_apar_handle_t);
void	class_error(char *, int);
void	class_notify_kernel(class_apar_handle_t, int);

/*
 * error codes
 * Must begin with 1 in order to match libclass_msg.h.
 */

#define CLASS_SUCCESS			1
#define CLASS_FILE_FAILURE		2
#define CLASS_SHARED_MEM_FAILURE	3
#define CLASS_SEMAPHORE_FAILURE		4
#define CLASS_MEM_ALLOC_FAILURE		5
#define CLASS_CLASS_NOT_EXIST		6
#define CLASS_CLASS_NOT_EMPTY		7
#define CLASS_MEMBER_ALREADY_IN_CLASS	8
#define CLASS_MEMBER_IN_OTHER_CLASS	9
#define CLASS_MEMBER_NOT_IN_CLASS	10
#define CLASS_NO_SPACE			11
#define CLASS_TOO_HIGH_PERCENT		12
#define CLASS_INVAL_PERCENT		13
#define CLASS_NAME_IN_USE		14
#define CLASS_NAME_INVALID		15
#define CLASS_ALREADY_ENABLED		16
#define CLASS_NOT_ENABLED		17
#define CLASS_DAEMON_FAIL		18
#define CLASS_INVAL_RESOURCE_TYPE	19
#define CLASS_NOT_SUSER			20
#define CLASS_DEFAULT_CONFIGURED	21
#define CLASS_RESERVED			22
#define CLASS_DEFAULT_CLASS_OP		23
#define CLASS_DATABASE_MODIFIED		24
#define CLASS_NAME_TOO_LONG		25
#define CLASS_INVAL_PARTITION		26
#define CLASS_UNKNOWN_ERROR		27
#define CLASS_LAST_ERROR		28	/* must be highest number */

/* 
 * For I18N, also add new error strings to libclass/libclass.msg.
 * The order and offset is important!
 */
#ifdef LOAD_IN_LIBCLASS_ONLY
char *class_err_string[] = {
 {"dummy"},
 {"success"},					/* CLASS_SUCCESS */
 {"database access"},				/* CLASS_FILE_FAILURE */
 {"allocate or attach to shared memory"},	/* CLASS_SHARED_MEM_FAILURE */
 {"allocate or access semaphore"},		/* CLASS_SEMAPHORE_FAILURE */
 {"malloc failure"},				/* CLASS_MEM_ALLOC_FAILURE */
 {"class does not exist"},			/* CLASS_CLASS_NOT_EXIST */
 {"class not empty"},				/* CLASS_CLASS_NOT_EMPTY */
 {"member already in class"},		/* CLASS_MEMBER_ALREADY_IN_CLASS */
 {"member in other class"},			/* CLASS_MEMBER_IN_OTHER_CLASS*/
 {"member not in class"},			/* CLASS_MEMBER_NOT_IN_CLASS */
 {"no more members or classes available"},	/* CLASS_NO_SPACE */
 {"requested percentage too high"},		/* CLASS_TOO_HIGH_PERCENT */
 {"requested percentage invalid"},		/* CLASS_INVAL_PERCENT */
 {"class name already in use"}, 		/* CLASS_NAME_IN_USE */
 {"non ascii input argument"}, 			/* CLASS_NAME_INVALID */
 {"class scheduling already enabled"}, 		/* CLASS_ALREADY_ENABLED */
 {"class scheduling not enabled"}, 		/* CLASS_NOT_ENABLED */
 {"class scheduling daemon failed to start"},	/* CLASS_DAEMON_FAIL */
 {"invalid resource type (cpu,i/o,mem,net)"},	/* CLASS_INVAL_RESOURCE_TYPE */
 {"not super user - permission denied"},	/* CLASS_NOT_SUSER */
 {"Database created with default configuration"},/* CLASS_DEFAULT_CONFIGURED */
 {"unused"},					/* CLASS_RESERVED2 */
 {"operation on default class not allowed"},	/* CLASS_DEFAULT_CLASS_OP */
 {"database modified and not saved"},		/* CLASS_DATABASE_MODIFIED */
 {"name too long"},				/* CLASS_NAME_TOO_LONG */
 {"invalid partition id"},			/* CLASS_INVAL_PARTITION */
 {"unknown error"},				/* CLASS_UNKNOWN_ERROR */
};
#endif /* LOAD_IN_LIBCLASS_ONLY */

#endif /* !_KERNEL */

#ifdef _KERNEL
extern decl_simple_lock_data(, class_lock)

struct class_cpu_resource {
	struct class_cpu_list cpu_list[MAX_NUM_CLASSES];
	int cpu_borrow_list[MAX_NUM_CLASSES];
	int cpu_borrow_list_in_use;
};
struct class_non_cpu_resource {
	int target_percent[MAX_NUM_CLASSES];
	int actual_percent[MAX_NUM_CLASSES];
};

struct class_sched {
	int class_enforce_when_idle;
	int class_reset_value;
	int class_daemon_pid;
	int class_scheduler_notify;
	int class_last_index_used;
	int class_daemon_not_responding;
	queue_head_t class_queue;
	struct class_cpu_resource class_cpu_resource;
	struct class_non_cpu_resource class_io_resource;
	struct class_non_cpu_resource class_mem_resource;
	struct class_non_cpu_resource class_net_resource;
};

#define CLASS_CPU_DEBIT(thread, prc)					\
do {									\
	/* avoid task dereferences if class in thread is not set */	\
	if ((thread)->th_class) {					\
		int class;						\
									\
		/* must use class in task to avoid reassignment race */	\
		class = (thread)->task->task_class;			\
		if (class &&						\
		    atomic_decl(&(prc)->processor_set->class_sched->	\
				class_cpu_resource.cpu_list[class].	\
				class_clock_ticks) <= 1)		\
			thread_ast_set((thread), AST_CLASS_SCHED);	\
	}								\
} while (0)

#endif /* _KERNEL */

#endif /* _SYS_CLASS_H_ */
