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
 * @(#)$RCSfile: nxm.h,v $ $Revision: 1.1.67.4 $ (DEC) $Date: 1995/06/15 16:26:16
 $
 */
#ifndef _ALPHA_NXM_H
#define _ALPHA_NXM_H
#if defined(__cplusplus)
extern "C"
{
#endif

#include <sys/types.h>

#if !defined(__LANGUAGE_ASSEMBLY__) && !defined(ASSEMBLER)
#include <kern/queue.h>
#include <mach/thread_status.h>
#include <sys/signal.h>
#include <sys/resource.h>
#include <sys/habitat.h>

/*
 * Out-of-line user thread state. The kernel can access this
 * when needed, but only the pointer to it (ushared_state.nws)
 * lives in the shared state.
 */
struct nxm_pth_state {
	u_long 		fpregs[32];
	u_long 		fpcr;	/* WARNING... must follow the fpregs!!! */
	stack_t		altstack;
	struct uuprof 	prof;
	struct 	nxm_ieee_state {
		long	ieee_fp_control;	/* floating point state */
		long	ieee_set_state_at_signal;
		long	ieee_fp_control_at_signal;
		long	ieee_fpcr_at_signal;
	} nxm_ieee_state;
	int		sigforce;
	int		stack_event;
	long		pad[9];
};

#ifdef _KERNEL

/*
 * Returns TRUE if the specified thread is an unbound nxm thread.
 */
#define NXM_UNBOUND(__th__) 						\
	((__th__)->nxm_flags && !((__th__)->nxm_flags & NXM_BOUND))

#define NXM_IEEE_STATE_COPYIN()						\
MACRO_BEGIN								\
	if (NXM_UNBOUND(current_thread())) {				\
		int nofault_save;					\
		struct pcb *pcb = current_pcb();			\
		nofault_save = pcb->pcb_nofault;			\
		if (copyin(&u.u_pthid->nxm_ieee_state, 			\
			   &u.u_ieee_fp_control, 			\
			    sizeof(struct nxm_ieee_state))) {		\
			pcb->pcb_nofault = nofault_save;		\
			sigexit(u.u_procp, SIGSEGV);			\
		}							\
		pcb->pcb_nofault = nofault_save;			\
	}								\
MACRO_END

#define NXM_IEEE_STATE_COPYOUT()					\
MACRO_BEGIN								\
	if (NXM_UNBOUND(current_thread())) {				\
		int nofault_save;					\
		struct pcb *pcb = current_pcb();			\
		nofault_save = pcb->pcb_nofault;			\
		if (copyout(&u.u_ieee_fp_control, 			\
			    &u.u_pthid->nxm_ieee_state, 		\
			    sizeof(struct nxm_ieee_state))) {		\
			pcb->pcb_nofault = nofault_save;		\
			sigexit(u.u_procp, SIGSEGV);			\
		}							\
		pcb->pcb_nofault = nofault_save;			\
	}								\
MACRO_END
#endif /* _KERNEL */

/*
 * Context-switched shared-state structure. This data is shared
 * directly between the running user thread and the kernel.
 * This state is context-switched by the user thread library.
 *
 * Each kernel thread has storage for this same data.
 */
struct ushared_state {
	sigset_t 	sigmask;	/* thread signal mask */
	sigset_t 	sig;		/* thread pending mask */
	struct 		nxm_pth_state *pth_id; /* out-of-line state */
	int		flags;		/* shared flags */
#define US_SIGSTACK	0x1		/* thread called sigaltstack */
#define US_ONSTACK	0x2		/* thread is running on altstack */
#define US_PROFILE	0x4		/* thread called profil */
#define US_SYSCALL	0x8		/* thread in syscall */
#define US_TRAP		0x10		/* thread has trapped */
#define US_YELLOW	0x20		/* thread has mellowed yellow  */
#define US_YZONE	0x40		/* thread has zoned out */
#define US_FP_OWNED	0x80		/* thread used floating point */

	int		cancel_state;	/* thread's cancelation state */
#define US_CANCEL	  0x1		/* cancel pending */
#define US_NOCANCEL	  0X2		/* synch cancel disabled */
#define US_SYS_NOCANCEL	  0x4		/* syscall cancel disabled */
#define US_ASYNC_NOCANCEL 0x8		/* asynch cancel disabled */
#define US_CANCEL_BITS	(US_NOCANCEL|US_SYS_NOCANCEL|US_ASYNC_NOCANCEL)
#define US_CANCEL_MASK	(US_CANCEL|US_NOCANCEL|US_SYS_NOCANCEL| \
			 US_ASYNC_NOCANCEL)

	/*
	 * These are semi-shared. They are always visible to
	 * the kernel but are never context-switched by the library.
	 */
	int		nxm_ssig;	/* scheduler's synchronous signals */
	int		reserved1;
	long		nxm_active;	/* scheduler active */
	long		reserved2;
};

/*
 * Upcall frame structure. The kernel builds this frame on the
 * stack and its address on an upcall. This same structure can be
 * used for saving/restoring user thread state on library context
 * switches.
 */
struct  nxm_upcall {
	int	usaved;				/* u_state is valid */
	int	pad;
	struct	ushared_state u_state;		/* shared state */
	struct 	alpha_saved_state reg_state;	/* register state */
};

#define UPCALL_HDR_SIZE \
	(sizeof(struct nxm_upcall) - sizeof(struct alpha_saved_state))

/*
 * Shared state structure. The ushared_state portion is context-switch
 * when new user threads are scheduled. The remainder of the structure
 * is shared state bewteen the kernel and the library scheduler. It is
 * never owned by the user thread.
 */
typedef enum nxm_wake_vals {
	NXM_SCHED_IDLE,
	NXM_SCHED_ACTIVE,
	NXM_SCHED_PENDING
} nxm_wake_val_t;

/*
 * Access macros to obtain the scheduler wake state and slot
 * number for a specified VP
 */
#define NXM_WAKE_STATE_MASK	0x0003

#define NXM_GET_WAKE_STATE(__vp__)					\
	((__vp__)->nxm_bits & NXM_WAKE_STATE_MASK)

#define NXM_SET_WAKE_STATE(__vp__, __state__)				\
MACRO_BEGIN								\
	(__vp__)->nxm_bits = (__state__) |				\
		((__vp__)->nxm_bits & ~NXM_WAKE_STATE_MASK);		\
MACRO_END

#define NXM_SLOTNUM_MASK	0x1fff

#define NXM_GET_SLOTNUM(__vp__)						\
	(((__vp__)->nxm_bits >> 16) & NXM_SLOTNUM_MASK)

#define NXM_SET_SLOTNUM(__vp__, __slot__)				\
MACRO_BEGIN								\
	(__vp__)->nxm_bits = ((__slot__) << 16) |			\
		((__vp__)->nxm_bits & ~(NXM_SLOTNUM_MASK << 16));	\
MACRO_END

struct nxm_sched_state {
	struct		ushared_state nxm_u;	/* state own by user thread */
	unsigned int	nxm_bits;		/* scheduler state / slot */
	int		nxm_quantum;		/* quantum count-down value */
	int		nxm_set_quantum;	/* quantum reset value */
	int		nxm_sysevent;		/* syscall state */
	struct		nxm_upcall *nxm_uc_ret;	/* stack ptr of null thread */
	void		*nxm_tid;		/* scheduler's thread id */
	long		nxm_va;			/* page fault address */
	struct 		nxm_pth_state *nxm_pthid; /* id of null thread */
	unsigned int	nxm_bound_slot_count;	/* # thds bound to VP slot */
	int		pad1;
	long		pad2[2];
};

/*
 * Shared struct allocated by nxm_task_init(). Visible to both kernel
 * and threads library.
 */
struct nxm_shared {
	long nxm_callback;		/* address of upcall routine */
	unsigned int nxm_version;	/* version number */
	unsigned short nxm_uniq_offset;	/* correction factor for TEB */
	unsigned short pad1;
	unsigned int nxm_bound_rad_count; /* # thds bound to RAD */
	int pad2;
	long pad3;			/* future growth */
	struct nxm_sched_state nxm_ss[1]; /* array of shared areas */
};

/*
 * VP slot states
 */
typedef enum {
	NXM_SLOT_AVAIL,
	NXM_SLOT_BOUND,
	NXM_SLOT_UNBOUND,
	NXM_SLOT_EMPTY
} nxm_slot_state_t;

/*
 * nxm_config_info: Shared read-only RAD/processor configuration
 * structure allocated by nxm_task_init().
 */
struct nxm_config_info {
	int nxm_nslots_per_rad;		/* max number of VP slots per RAD */
	int nxm_nrads;			/* max number of RADs */
	nxm_slot_state_t *nxm_slot_state; /* per-VP slot state */
	struct nxm_shared *nxm_rad[1];	/* per-RAD shared areas */
};

typedef struct nxm_config_info nxm_config_info_t;
typedef struct nxm_config_info *nxm_config_info_p;

/*
 * nxm_action: desriptor for pseudo-upcall.
 */
typedef struct nxm_action {
#define NXM_ACTION_NONE		0
#define NXM_ACTION_SIGNAL	1
#define NXM_ACTION_SIGEV	2
#define NXM_ACTION_SIGFORCE	3
#define NXM_ACTION_PSET_ADJUST	4
	long	nxm_action_type;
	void	*nxm_action_data;
	long	space[6];
} *nxm_action_t;

/*
 * Structure to report blocking events.
 * (Stop complaints about ulong bit fields.)
 */
#ifdef __DECC
#ifndef _KERNEL
#pragma message disable bitnotint
#endif
#endif /* __DECC */

typedef struct nxm_block_event {
	union {
		struct {
			unsigned long 	_nxm_event_flags:3;
#define NXM_BLOCK_FAULT		0x1	/* blocked on fault/trap event */
#define NXM_BLOCK_SYSCALL	0x2	/* blocked in a syscalls */
#define NXM_BLOCKED_PENDING	0x4	/* blocked with pending signal */
			unsigned long	_nxm_event_habitat:4;
			unsigned long	_nxm_event_syscall:9;
			unsigned long	_nxm_event_kid:48;
		} _nxm_event_s;
		unsigned long _nxm_event_total;
	} _nxm_event_un;
} nxm_event_t;


#ifdef __DECC
#ifndef _KERNEL
#pragma message enable bitnotint
#endif
#endif /* __DECC */

#define nxm_event _nxm_event_un._nxm_event_total
#define nxm_event_flags _nxm_event_un._nxm_event_s._nxm_event_flags
#define nxm_event_habitat _nxm_event_un._nxm_event_s._nxm_event_habitat
#define nxm_event_syscall _nxm_event_un._nxm_event_s._nxm_event_syscall
#define nxm_event_kid _nxm_event_un._nxm_event_s._nxm_event_kid

/*
 * Thread type flags.
 */
#define NXM_TYPE_SCS		0x0
#define NXM_TYPE_VP		0x1
#define NXM_TYPE_MANAGER	0x2

/*
 * Thread signal flags.
 */
#define NXM_SIGNAL_EXPLICIT	0x0
#define NXM_SIGNAL_INHERIT	0x1

/*
 * Bit definitions for 'flags' argument to nxm_resched()
 */
#define NXM_RESCHED_TID			0L
#define NXM_RESCHED_SLOT		1L

/*
 * Task init flags
 */
#define NXM_TASK_INIT_SCS	0x0001		/* initial thread is SCS */
#define NXM_TASK_INIT_VP	0x0002		/* initial thread is VP */
#define NXM_TASK_BIND_TO_CPU	0x0004		/* bind VP to CPU */
#define NXM_TASK_BIND_TO_RAD	0x0008		/* bind VP to RAD */

typedef struct nxm_task_attr {
	long nxm_callback;
	unsigned int nxm_version;
	unsigned short nxm_uniq_offset;
        unsigned short flags;
	int nxm_quantum;
	int pad1;
	long pad2;
} nxm_task_attr_t, *nxm_task_attr_p;

/*
 * Shared thread attributes.
 */
typedef struct nxm_thread_attr {
	int version;
	int type;
	int cancel_flags;
	int priority;
	int policy;
	int signal_type;
        void *pthid;
	sigset_t sigmask;
	struct {
		long pc;
		long sp;
		long a0;
	} registers;
	long pad2[2];
} nxm_thread_attr_t, *nxm_thread_attr_p;

#if _POSIX_C_SOURCE >= 199506L
typedef struct nxm_sigev_action {
	void         	(*nxm_sigev_func) __((sigval_t));
	sigval_t	nxm_sigev_argument;
} *nxm_sigev_action_t;
#endif

/*
 * Pshared synchronization structures.
 */
/*
 * PSHARED syncrhonization objects.
 */
typedef enum {
	PSHARED_BAD,
	PSHARED_MUTEX,
	PSHARED_CV,
	PSHARED_RWL
} pshared_type_t;

#ifdef __DECC
#ifndef _KERNEL
#pragma message disable bitnotint
#endif
#endif /* __DECC */

typedef struct nxm_pshared_lock {
	union {
		long	_lock_state;
		struct {
			unsigned long    _lock_bit:1;
			unsigned long    _waiters:63;
		} _mutex_s;
		struct {
			unsigned long   _write_lock:1;
			unsigned long	_write_waiters:31;
			unsigned long   _readers_waiting:1;
			unsigned long	_read_lockers:31;
		} _rwl_s;
	} _lock_state_un;
} nxm_pshared_lock_t, *nxm_pshared_lock_p;

#ifdef __DECC
#ifndef _KERNEL
#pragma message enable bitnotint
#endif
#endif /* __DECC */

/*
 * The whole lock field for easy assignment.
 */
#define nxm_lock_state		_lock_state_un._lock_state

/*
 * The fields used for mutex operations.
 */
#define nxm_mutex_lock		_lock_state_un._mutex_s._lock_bit
#define nxm_mutex_waiters	_lock_state_un._mutex_s._waiters

/*
 * The fields used for readers/write-lock operations.
 */
#define nxm_write_lock		_lock_state_un._rwl_s._write_lock
#define nxm_write_waiters	_lock_state_un._rwl_s._write_waiters
#define nxm_readers_waiting	_lock_state_un._rwl_s._readers_waiting
#define nxm_readers		_lock_state_un._rwl_s._read_lockers

#define PSHARED_RWM_LOCK	0x0
#define PSHARED_RWM_UNLOCK	0x0
#define PSHARED_RWM_TRY		0x1
#define PSHARED_RWM_READ	0x2
#define PSHARED_RWM_WRITE	0x4

#define PSHARED_CV_WAIT		0x0
#define PSHARED_CV_SIGNAL	0x0
#define PSHARED_CV_BROADCAST	0x1

#define PSHARED_MOD_ABSTIME	0x1	/* same as TIMER_ABSTIME */
#define PSHARED_MOD_FASTPATH	0x2	/* try a fast lock first */
#define PSHARED_MOD_RECURSIVE	0x4	/* recursive mutex */
#define PSHARED_MOD_ERRORCHECK  0x8	/* error check mutex */

typedef struct nxm_pshared_data_tag {
	unsigned char   type;
	unsigned char   op;
	unsigned short  offset;
	unsigned int    modifiers;
} nxm_pshared_data_t, *nxm_pshared_data_p;

typedef enum {
	PSHARED_HOLDER_BAD,
	PSHARED_HOLDER_MUTEX,
	PSHARED_HOLDER_READ,
	PSHARED_HOLDER_WRITE,
	PSHARED_HOLDER_MUTEXWAIT,
	PSHARED_HOLDER_READWAIT,
	PSHARED_HOLDER_WRITEWAIT,
	PSHARED_HOLDER_CONDWAIT
} pshared_holder_t;

typedef struct nxm_pshared_owner {
	pid_t		 owner_pid;
	pshared_holder_t owner_type;
#ifdef _KERNEL
	void		 *owner_id;
#else
	pthread_t	owner_id;
#endif
} pshared_owner_t,  *pshared_owner_p;

typedef struct nxm_pshared_waiter {
	long		waiter_count;
	vm_offset_t	object_address;
	long		filler[4];
	pshared_owner_t waiter_list;
} pshared_waiter_t,  *pshared_waiter_p;

#define PSHARED_WAITER_HSIZE \
	(sizeof(pshared_waiter_t) - sizeof(pshared_owner_t))

typedef struct nxm_pshared_debugdata {
	vm_offset_t	object_address;
	pshared_type_t	object_type;
	int		waiter_count;
	int		recursion_count;
	pshared_owner_t	owner;
	long		filler[4];
} pshared_debug_t, *pshared_debug_p;

/*
 * Used only for speculative execution to pass exception data from trap()
 * to nxm_upcall().
 */
struct spec_trap_args {
	u_long trap_a0;
	u_long trap_a1;
	u_long trap_a2;
};

#ifdef _KERNEL
/*
 * Deal with per-thread pending signal masks atomically.
 */
extern sigaddset_atomic(sigset_t *, int);
extern sigadelset_atomic(sigset_t *, int);

#define nxm_sigaddset(__th__,__maskaddr__, __sig__) \
	if (NXM_UNBOUND(__th__))  \
		sigaddset_atomic((__maskaddr__), (__sig__)); \
	else \
		sigaddset((__maskaddr__), (__sig__));
	
#define nxm_sigdelset(__th__, __maskaddr__, __sig__) \
	if (NXM_UNBOUND(__th__))  \
		sigdelset_atomic((__maskaddr__), (__sig__)); \
	else \
		sigdelset((__maskaddr__), (__sig__));

/*
 * Deal with per-thread bit fields atomically.
 */
#include <machine/builtins.h>
#define nxm_flag_set(__flagaddr__, __flag__) \
		__ATOMIC_OR_LONG((__flagaddr__), (__flag__))
#define nxm_flag_clear(__flagaddr__, __flag__) \
		__ATOMIC_AND_LONG((__flagaddr__), ~(__flag__))

typedef struct interrupt_state {
	sigset_t is_sigmask;
	int	 is_cancel;
} interrupt_state_t;


#define sigint_off(_mask_, _saved_state_)				\
{									\
	sigset_t tset;							\
	TH_SUSPEND_OFF();						\
	tset = (_mask_);						\
	sigsetsum(&tset, u.u_sigmask);					\
	(_saved_state_).is_sigmask = u.u_sigmask;			\
	u.u_sigmask = tset;						\
	(_saved_state_).is_cancel = u.u_cancel_state & US_NOCANCEL;	\
	nxm_flag_set(&u.u_cancel_state, US_NOCANCEL);			\
}

#define sigint_on(_saved_state_)					\
	TH_SUSPEND_ON();						\
	u.u_sigmask = (_saved_state_).is_sigmask;			\
	if (!((_saved_state_).is_cancel))				\
		nxm_flag_clear(&u.u_cancel_state, US_NOCANCEL);

#define NXM_TEB(__pthid__, __task__)					\
		((unsigned long) (__pthid__) - 				\
		 (unsigned long) (__task__)->nxm_task_uniq_offset)


#define NXM_EXTRA_TIMEOUT 	20

#endif /* _KERNEL */
#endif  /* __ASSEMBLER__ */

#define NXM_VERSION_V50		300001
#define NXM_VERSION_V51		301003			/* 3.1.3 */
#define NXM_VERSION_V51_1	301004 
#define NXM_VERSION		NXM_VERSION_V51_1 

/*
 * Non-signal signals.
 */
#define NXM_THREAD_CANCEL	0x7afababa	/* cancel thread */
#define NXM_THREAD_STACK	0x7abafafa	/* stack overflow */

/*
 * Suspend types.
 */
#define NXM_SUSPEND_NOCOUNT	0x1
#define NXM_SUSPEND_COUNT	0x2
#define NXM_SUSPEND_FORCE	0x4

/*
 * Thread kill target types.
 */
#define NXM_KILL_UNBOUND	0x1
#define NXM_KILL_BOUND		0x2

/*
 * Flags to guide saving restoring state.
 */
#define NXM_SHARED_SAVED	0x1	/* must restore shared state */
#define NXM_FAST_RESTORE	0x2	/* full restore not required */
#define NXM_FP_ACTIVE		0x4	/* fp registers are live */
#define NXM_UPCALL_FRAME	0x10   	/* signature for stack peekers */
#define NXM_STACK_UNBLOCK	0x20    /* stack overflow on unblock */

/*
 * Upcall operation codes. Passed as 1st arg to the upcall routine
 * to define the scheduler event.
 *
 * Events detected by the kernel: 1-100 reserved.
 */
#define NXM_QUANTUM_EXPIRE		1 /* quantum expired */
#define	NXM_SCHED_THREAD_UT_BLOCKED	2 /* thread blocked in kernel */
#define	NXM_THREAD_UNBLOCK_NO_SID 	3 /* thread unblocked no sched id */
#define NXM_SIGNAL_BLOCKED		4 /* current thread have blocked sig */
#define NXM_SPECULATIVE_EXECUTION	5 /* call user spec-exec handler */
#define	NXM_THREAD_INTERRUPTED 		6 /* sched/bound thread interrupted */
#define	NXM_VP_RESCHED 			7 /* vp should reenter scheduler */
#define NXM_GENTRAP_HANDLER		8 /* call user gentrap handler */
#define NXM_STACK_OVERFLOW		9 /* yellow zone notification */
#define NXM_FB_FIXUP		       10 /* fixup FBs */
#define NXM_VP_UNBOUND		       11 /* vp became unbound */

#ifndef _KERNEL
#define	_thread_self		13
#define _block			24
#define _unblock		25
#define _thread_destroy		29
#define _thread_create		32
#define _task_init 		33
#define _idle 			35
#define _wakeup_idle 		36
#define _set_pthid 		37
#define _thread_kill 		38
#define _thread_block 		39
#define _thread_wakeup 		40
#define _get_binding		42
#define _resched 		44
#define _set_cancel 		45
#define _set_binding		46
#define _stack_create		47
#define _get_state		48
#define _thread_suspend		49
#define _thread_resume		50
#define _signal_check		51
#define _pshared_init   	63
#define _pshared_block  	64
#define _pshared_unblock 	65
#define _pshared_destroy 	66
#define _switch_pri		67
#endif

#if defined(__cplusplus)
}
#endif
#endif /* _ALPHA_NXM_H */
