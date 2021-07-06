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
 * @(#)$RCSfile: ccfg.h,v $ $Revision: 1.1.35.2 $ (DEC) $Date: 2001/11/26 14:03:49 $
 */
#ifndef _CCFG_INCL_
#define _CCFG_INCL_

#include <io/cam/ddr_defines.h>

/* ---------------------------------------------------------------------- */

/* ccfg.h		Version 1.08			Nov. 16, 1991 */

/*  This file contains the definitions and data structures for the 
    configuration driver module, CDrv, in the CAM subsystem.
*/

/* ---------------------------------------------------------------------- */

/* Misc defines used within the CDrv code. */

/* ---------------------------------------------------------------------- */

/* The CDrv control structure is used for various functions w/in the CDrv.
   It contains module wide flags for the scanning process */

#define CCFG_INQ_SENSE_LEN	36
typedef struct ccfg_ctrl
{
    U32			ccfg_flags;	/* controlling flags */
    XPT_LOCK_DATA	c_lk_ctrl;	/* for locking on the control struct */
} CCFG_CTRL;

#define CCFG_CTRL_VERS	3	/* please incr if CCFG_CTRL changes */

/*
 * defines for parallel probing of all scsi/fibre channel busses
 */

typedef enum { BUS_SCAN, DECLARE_DEVICES } CCFG_THREAD_TYPE;

/* synchronization structure */
typedef struct ccfg_scan_thread_ctrl {
  U32 count;
  simple_lock_data_t  lock;
} CCFG_SCAN_THREAD_CTRL;

/* ccfg_probe_thread_params structure */
typedef struct ccfg_probe_thread_params {
  struct ccfg_probe_thread_params *next;
  U32 bus;                 /* bus to probe */
  struct controller *ctlr; /* controller for bus */
  XPT_SIM_ENTRY *xse;      /* for this HBA */
  int isthread;            /* non-zero if running as a thread */
  U32 next_target;         /* next target to scan */
  U32 max_target;          /* max target to scan */
  U32 threads;             /* number of threads on this bus */
  U32 sim_type;            /* type of sim */
  CCFG_THREAD_TYPE thread_type; /* if thread is for scanning or device delcaration */
} CCFG_PROBE_THREAD_PARAMS;

/*
 * Structure to sychronize access to calling camdb_devreg
 * Use LOCK_CCFG_SCAN_THREADS & UNLOCK_CCFG_SCAN_THREADS
 * for synchronized access to this
 */
typedef struct ccfg_one_thrd_sync {
    U32          count; /* number of owners/waiters */
    queue_head_t q_head; /* queue head of waiters */
} CCFG_ONE_THRD_SYNC;

/* initialization of probe lock */
#define INIT_CAM_SCAN_THREAD_LOCK                       \
{                                                       \
		simple_lock_init( &ccfg_scan_threads.lock);     \
		ccfg_scan_threads.count = 0;                    \
}

/* lock ccfg_scan_thread struct */
#define LOCK_CCFG_SCAN_THREADS(S)             \
{                                             \
  S = splbio();                               \
  simple_lock(&ccfg_scan_threads.lock);	      \
}

/* unlock ccfg_scan_thread struct */
#define UNLOCK_CCFG_SCAN_THREADS(S)           \
{                                             \
  simple_unlock(&ccfg_scan_threads.lock);	  \
  splx(S);								      \
}

/* increment number of probe threads */
#define INCREMENT_CAM_SCAN_THREAD_COUNT        \
{											   \
        atomic_incl( &ccfg_scan_threads.count); \
}

/* decrement number of probe threads, sets current */
/* count in passed param */
#define DECREMENT_CAM_SCAN_THREAD_COUNT( COUNT )\
{												\
        COUNT = (atomic_decl(&ccfg_scan_threads.count) -1);  \
}


/* The IPL/SMP locking Macros for the control structure. */

#define CTRL_INIT_LOCK( cp )				\
{							\
    XPT_INIT_LOCK( &(cp)->c_lk_ctrl, cam_c_ctrl_li );	\
}

#define CTRL_SPINLOCK( cp )			\
{						\
    XPT_SPINLOCK ( &(cp)->c_lk_ctrl );		\
}

#define CTRL_SPINUNLOCK( cp )			\
{						\
    XPT_SPINUNLOCK ( &(cp)->c_lk_ctrl );	\
}

#define CTRL_LOCK( cp )			\
{					\
    XPT_LOCK ( &(cp)->c_lk_ctrl );	\
}

#define CTRL_UNLOCK( cp )		\
{					\
    XPT_UNLOCK ( &(cp)->c_lk_ctrl );	\
}

/*
 * Macro CCFG_WAITSET_CTRL_STATE
 * Arguments:
 *	ccfg_ctrl	- pointer to CCFG_CTRL structure
 *      waitflags       - wait until these flags are cleared
 *	setflags	- flags to be set in .ccfg_flags
 */
#define	CCFG_WAITSET_CTRL_STATE( ccfg_ctrl, waitflags, setflags)  \
{								  \
    int spl = splbio();						  \
    CTRL_SPINLOCK((ccfg_ctrl));			                  \
    while((ccfg_ctrl)->ccfg_flags & (waitflags) ) {               \
	assert_wait(((vm_offset_t)(ccfg_ctrl)), 0);		  \
	mpsleep((void *)NULL, 0, "WAIT CTRL STATE", 0,		  \
		(void *)(&((ccfg_ctrl)->c_lk_ctrl.xpt_lk_data)),  \
		(MS_LOCK_NO_RELOCK | MS_LOCK_SIMPLE));		  \
	CTRL_SPINLOCK((ccfg_ctrl));				  \
    }	                                                          \
    (ccfg_ctrl)->ccfg_flags |= setflags;                          \
    CTRL_SPINUNLOCK((ccfg_ctrl));				  \
    splx(spl);							  \
}

/*
 * Macro CCFG_CLR_CTRL_STATE
 * Arguments:
 *	ccfg_ctrl	- pointer to CCFG_CTRL structure
 *	flags		- flag to be cleared in .ccfg_flags
 */
#define CCFG_CLR_CTRL_STATE( ccfg_ctrl, flags)			\
{								\
    CTRL_LOCK((ccfg_ctrl));					\
    (ccfg_ctrl)->ccfg_flags &= ~(flags);			\
    CTRL_UNLOCK((ccfg_ctrl));				\
    wakeup( (char *)(ccfg_ctrl));				\
}

/* ---------------------------------------------------------------------- */

/* The CDrv Queue Header structure.  This structure contains a PDrv
working set structure and a lock structure.  The PDrv working set is used
to allow the Q walking code to use a consistant pointer for the queue. */

typedef struct ccfg_queue_head
{
    PDRV3_WS qws;		/* the Q head working set */
    XPT_LOCK_DATA c_lk_qhead;	/* for locking on the control struct */
} CCFG_QUEUE_HEAD;

/* The IPL/SMP locking Macros for the Q Head structure. */

#define QHEAD_INIT_LOCK( qp )					\
{								\
    XPT_INIT_LOCK( &(qp)->c_lk_qhead, cam_c_qhead_li );		\
}

#define QHEAD_SPINLOCK( qp )					\
{								\
    XPT_SPINLOCK( &(qp)->c_lk_qhead );				\
}								

#define QHEAD_SPINUNLOCK( qp )					\
{								\
    XPT_SPINUNLOCK( &(qp)->c_lk_qhead );			\
}								

#define QHEAD_LOCK( qp )					\
{								\
    XPT_LOCK( &(qp)->c_lk_qhead );				\
}								

#define QHEAD_UNLOCK( qp )					\
{								\
    XPT_UNLOCK( &(qp)->c_lk_qhead );				\
}								

#define QHEAD_SLEEPUNLOCK( chan, pri, qp )			\
{								\
    int spl_val = (qp)->c_lk_qhead.xpt_saveipl;			\
    assert_wait(((vm_offset_t)(chan)), ((pri) & PCATCH));	\
    mpsleep((void *)NULL, (pri), "Zzzzzz", 0,			\
		(void *)&((qp)->c_lk_qhead.xpt_lk_data),	\
		(MS_LOCK_NO_RELOCK | MS_LOCK_SIMPLE));		\
    splx (spl_val);						\
}


/* ---------------------------------------------------------------------- */


extern CCFG_CTRL ccfg_ctrl;

/* Flags used by the CDrv in it's module control structure flags field.  The
control structure contains the working area for the EDT scanning. */

#define INQ_INPROG	0x00000010	/* signal an INQUIRY I/O in prog. */
#define EDT_INDELETE    0x00000020      /* signal a delete in progress    */
#define EDT_INREPLACE   0x00000040      /* signal a replace in progress   */
#define EDT_EXCLUSIVE   0xffffffff      /* signal exclusive operation, no
					   other operations can be on-going. */

/* Flags used by the CDrv in the PDrv working set flags field.  These
flags are an overlay of the bits used by the PDrv.  The CDrv is only
using the the same working set defined by the PDrv, there is no attempt
to use all the possible bit settings. */
/* TODO: Should use same flags as peripheral drivers!!! */
#define CCB_RECEIVED	0x00000100	/* simple signal flag from callback */
#define ISSUE_WAKEUP	0x00000200	/* the CDrv is sleeping on the WSET */

#define ABORT_SENT	0x00010000	/* timeout code has sent an ABORT */
#define RESET_SENT	0x00020000	/* timeout code has sent a BUS RESET */

#define NO_SDTR		0x00100000	/* Try the CCB w/out SDTR enabled */
#define CCFG_RETRY	0x00800000	/* This CCB is in RETRY state */

/* ---------------------------------------------------------------------- */

/* Scanning arguments for the CDrv scanning code, ccfg_edtscan(). */

#define EDT_FULLSCAN	0x00		/* Scan all Targets and Luns*/
#define EDT_TGTSCAN	0x01		/* Scan all Luns on a target */
#define EDT_SINGLESCAN	0x02		/* Scan a specific Target/Lun */


/* ---------------------------------------------------------------------- */

/* Defines for the Delaying/Loop code. */

#define WAIT_DELAY	1000		/* delay # for 1 msec */
#define WAIT_DELAY_LOOP	2000		/* loop # for 2 seconds */
#define WAIT_RESET_LOOP 250		/* loop # for 250 msec */

#define WAIT_PRIORITY	0

#endif /* _CCFG_INCL_ */







