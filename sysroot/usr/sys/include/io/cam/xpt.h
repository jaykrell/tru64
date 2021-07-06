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
 * @(#)$RCSfile: xpt.h,v $ $Revision: 1.1.42.1 $ (DEC) $Date: 2001/10/03 20:17:18 $
 */
#ifndef _XPT_INCL_
#define _XPT_INCL_
#ifdef _cplusplus
extern "C" {
#endif

#include <sys/processor.h>
#include <sys/sysconfig.h>
#include <io/cam/cam_debug.h>
#include <io/cam/sim_target.h>
#include <io/cam/sim_cirq.h>
#include <io/cam/dme.h>
#include <io/cam/sim.h>
#include <io/cam/dec_pdrv.h>
#include <kern/sched.h>

/****************************************************
 *
 * CAM Version supported by XPT.
 *
 *    CHANGE HERE AS NEWER VERSIONS OF THE CAM SPEC
 *    ARE SUPPORTED BY THE XPT.
 *
 ****************************************************/

#define XPT_CAM_VERSION "CAM-3 WD R2"


/****************************************************
	compiler switches
 ****************************************************/

#define XPT_DEBUG		0		/* Debug code enabled if 1 */

/*
 * cam xpt memory (de)allocation
 */

#define XPT_MALLOC(address,type,size) \
  MALLOC_VAR( (address), type, (size), M_KTABLE, M_WAITOK|M_ZERO )

#define XPT_MFREE(address) \
  FREE( (address), M_KTABLE )

/*
 * Macro CAM_INISR returns CPU spacific flag signalling an interrupt state
 */

#define CAM_INISR  ( AT_INTR_LVL() )

/*
 * The XPT working set.
 * This data structure is used by the XPT layer to keep free and busy
 * CCB structures w/in the allocation pool.
 * Free allocated CCB packets are distributed per CPU and queued
 * to XPT_WS headers. We expect ewentually to be able to return the ccb
 * to the queue of the CPU (or adapter) from which it was taken.
 * For that reason, structure XPT_WS contains "owner" member that will
 * be used eventually by the xpt_ccb_free().
 */

typedef struct xpt_ws
{

#define XPT_WS_VERS	4	/* please incr if XPT_WS changes */

    struct xpt_ws   *x_flink;	/* forward pointer in the chain */
    struct xpt_ws   *x_blink;	/* backward pointer in the chain */
    void            *xpt_ccb;	/* pointer to the CCB */
    U32              xpt_flags;	/* flags for the status of this CCB */
    U32              owner;	/* Entity that owns the packet   */
    LOCALITY_CONTEXT locality_context;
    void            *xpt_cback_hdr;
} XPT_WS;

/*
 * Working set queue headers per CPU
 * Used both for active sets comming from SIM layer and attached
 * to the structure XPT_COMPLETE_QUE and for free working sets,
 * maintained at the structure XPT_ALLOC_QUE
 */
typedef struct xpt_ws_hdr {
    void	 *flink;
    void	 *blink;
    volatile I32  count;  	/* Count of queued working sets */
    U32           pkt_size;	/* Allocation size of the ccb data packet */
    XPT_LOCK_DATA smp_lock;
} XPT_WS_HDR;

/*
 * List of free working sets for use in the interrupt context
 */
typedef struct xpt_free_ws_hdr {
    void	  *flink;		/* Forward WS link	*/
    void	  *blink;		/* Backward WS link	*/
    XPT_LOCK_DATA smp_lock;
    int		  used;			/* Count of used buffers */
#define XPT_FREE_ISR_WS	5		/* reserved WS per CPU	*/
} XPT_FREE_WS_HDR;

/*
 * XPT Callback thread structures
 */
typedef void (*PREQUE_CALLBACK)(void *, void *);
typedef struct xpt_preque_entry XPT_PREQUE_ENTRY;
typedef struct xpt_preque_entry {
    XPT_PREQUE_ENTRY *flink;
    XPT_PREQUE_ENTRY *blink;
    void             *arg1;
    void             *arg2;
    PREQUE_CALLBACK   func_callback;
} XPT_PREQUE_ENTRY;

/* Forward refernece */
typedef struct xpt_callback_hdr xpt_callback_hdr_t;

typedef struct xpt_cback_que {		/* Cache block aligned */
    XPT_LOCK_DATA       smp_lock;	/* XPT_LOCK_DATA is padded to 16  */
    XPT_WS             *ws_flink;
    XPT_WS             *ws_blink;
    U32			present;	/* Thread present */  		
#define XPT_CBACK_PRESENT    0x1	/* TRUE or FALSE */
    U32                 running;	/* Running flag ONLY TRUE or FALSE */
#define XPT_CBACK_BLOCKED    0x0	/* Callback thread block */
#define XPT_CBACK_RUNNING    0x1	/* Callback thread run */
    U32			ws_added;	/* New work supplied	*/
    U32                 count;		/* Queued working set count */
    xpt_callback_hdr_t *callback_hdr;
    struct thread      *thread;		/* Thread handle when initialized */

/* new cache block */
    XPT_LOCK_DATA       preque_lock;	/* XPT_LOCK_DATA is padded to 16 */
    XPT_PREQUE_ENTRY   *preque_flink;
    XPT_PREQUE_ENTRY   *preque_blink;
    U32                 preque_count;	/* Queued prequeue count */
    U32                 work_count;	/* Working count of ws & preque */
    U32                 preque_maxcnt;	/* Max prequeued count */
    U32                 preque_avg_depth;/* Avg preque depth */
    U32                 preque_ios;	/* Number of times prequeued called */
    U32                 pad1;		/* Pad */
    U64                 preque_run_total;/* Running total of preque count */

/* new cache block - pad */
    struct wait_queue   waitque;	/* Localized thread wait queue (32bytes)*/
    U32                 maxcnt;		/* Max  queued working sets */
    U32                 avg_depth;	/* Avg ws que depth */
    U32                 ios;		/* Number of times callback called */
    U32                 pad2;		/* Pad */
    U64                 run_total;	/* Running total of ws count */
    U64			pad3;  		/* Pad */
} XPT_CBACK_QUE;

typedef struct xpt_callback_hdr {
    xpt_callback_hdr_t *flink;
    xpt_callback_hdr_t *blink;
    XPT_LOCK_DATA       smp_lock;	/* XPT_LOCK_DATA is padded to 16  */
    I32		        rad_id;
    I32	 		initialized;
    I32			active_count; 	/* active callback threads/queues */
    I32	 		thread_maint;
    U32			index_mask;
    I32			pad2[3];  		
    /* Cache block align */
#define XPT_CB_QUE_THREADS_MAX	4	/* Per Rad */
    XPT_CBACK_QUE       cb_que_array[XPT_CB_QUE_THREADS_MAX]; 
} XPT_CALLBACK_HDR;

/* 
 * Per RAD xpt_callback_hdr list 
 */
typedef struct xpt_callback_hdr_list {
    XPT_LOCK_DATA     smp_lock;       /* XPT_LOCK_DATA is padded to 16  */
    XPT_CALLBACK_HDR *flink;
    XPT_CALLBACK_HDR *blink;
} XPT_CALLBACK_HDR_LIST;

/*
 * Async Event queue element 
 */
typedef struct xpt_async_event {
    struct xpt_async_event     *flink;
    struct xpt_async_event     *blink;
    I32				opcode;
    I32				path_id;
    I32				tgt;
    I32				lun;
    char *			buffer;
    I32				buffer_len;
} XPT_ASYNC_EVENT;

/*
 * Async Event queue structure 
 */
typedef struct xpt_async_event_que {
    XPT_ASYNC_EVENT	*flink;
    XPT_ASYNC_EVENT	*blink;
    XPT_ASYNC_EVENT	*d_flink; /* list of async events currently dispatched*/
    XPT_ASYNC_EVENT	*d_blink;
    XPT_LOCK_DATA	smp_lock;
    U32 entry_count; /* number of current async events on queue*/
    U32 thread_count; /* number of async threads */
    U32 active_count; /* number of active async threads */
} XPT_ASYNC_EVENT_QUE;

typedef struct xpt_bus_scan_sync {
  XPT_LOCK_DATA lock;
  int sleep;
} XPT_BUS_SCAN_SYNC;

typedef struct xpt_bus_scan_done {
  void (*cb_func)(); /* callback function */
  XPT_BUS_SCAN_SYNC *sync;
} XPT_BUS_SCAN_DONE;

/* ---------------------------------------------------------------------- */

/* The XPT control structure is used for various functions w/in the XPT.
It is the common locking point for the cam_conftbl[] accesses.	Because the
cam_conftbl[] is not a "static" sized structure it can not be included in
a structure declaration.  So a seperate data structure is needed to contain
the misc flags/locks used with the cam_conftbl[]. */

typedef struct xpt_ctrl
{
    XPT_LOCK_DATA smp_lock;	/* for locking on the control struct */
    U32 xconf_flags;		/* controlling flags */
} XPT_CTRL;


/* ---------------------------------------------------------------------- */

/*
 * This is the declaration for the header/CCB packet resource controlled
 * by the XPT.  This structure contains the three headers used by the XPT,
 * PDrvss, and the SIMs, followed by the CCB space.  It is expected that
 * accesses to this structure will be used via casting the XPT header
 * pointer and some form of address arithmetic using the CCB pointers.
 * 
 * Note:  It is MANDATORY that the XPT working set be at the start of
 *   the packet. Within the CAM code this knowledge is used in changing
 *   pointers by the routines that deal with the CCB pool.
 *
 * Note:  It is MANDATORY that the SIM working set (SIM_WS) be just before
 *   the CCB. Within the SIM layer this knowledge is used to determine
 *   the SIM_WS pointer.
 */

typedef struct dec_cam_pkt
{
    XPT_WS	xws;		/* XPT working set */
    union {
        PDRV_WS    pws_1;	/* PDrv working set */
        PDRV3_WS   pws_3;	/* PDrv working set */
    }		pws;
    SIM_WS	sws;		/* SIM working set */
    CCB_SIZE_UNION ccb_un;	/* The CCB union for all CCBs */
} DEC_CAM_PKT;


/* ---------------------------------------------------------------------- */

/*
 * Peripheral driver access flags for a device.
 */

#define XPT_SHARED	0x00		/* Not exclusive (bit 0 is 0) */
#define XPT_EXCLUSIVE	0x01		/* Driver wants exclusive use */

/*
 * Priority of the cam callback routine.  It must be higher than the kds
 * callback so that the cam callback is called after the kds callback.
 */

#define XPT_PRIORITY	KDS_PRIORITY + 100

/* ---------------------------------------------------------------------- */

#define ASYNC_WILDCARD	-1		/* wildcard value in async callback */
/*
	NOT USED
#define XPT_ISR_CONTEXT  2		/* signal a call in interrupt context */

/*
 * The flags for callback thread management
 * ========================================
 */

#define XPT_FREE        0x1     /* a free packet for use */
#define XPT_BUSY        0x2     /* a busy packet in use */

/*
 * Other CCB management macros
 */

/* following macro assumes ccb is after xpt ws in the DEC_CAM_PKT structure */
#define XPT_GET_WS_ADDR( ch ) 				\
    (XPT_WS *)((vm_offset_t)(ch) - 			\
     ((vm_offset_t)(&((DEC_CAM_PKT *)0)->ccb_un) -	\
     (vm_offset_t)(&((DEC_CAM_PKT *)0)->xws)))

#define XPT_WAIT( q_ptr, spl )			\
{						\
    thread_t thread = current_thread();		\
    assert_wait((vm_offset_t)(q_ptr), FALSE);	\
    splx (spl);					\
    thread_block();				\
}

#define assert_wait_head(ev,int)		\
    assert_wait_mesg_head(ev, int, (const char *) 0)


#define XPT_WAIT_HEAD( q_ptr, spl )		\
{						\
    thread_t thread = current_thread();		\
    assert_wait_head((vm_offset_t)(q_ptr), FALSE); \
    splx (spl);					\
    thread_block();				\
}


/****************************************************
		Debug insert/remove macros
 ****************************************************/

#if !XPT_DEBUG

#define XPT_WS_REMOVE(xpt_ptr)				\
{							\
	remque((void *)(xpt_ptr));			\
}

#define XPT_WS_INSERT(xpt_ptr, where)			\
{							\
	insque((void *)(xpt_ptr), (void *)(where));	\
}

#else

#define XPT_WS_REMOVE(xpt_ptr)				\
{							\
	xpt_remque((void *)(xpt_ptr));			\
}

#define XPT_WS_INSERT(xpt_ptr, where)			\
{							\
	xpt_insque((void *)(xpt_ptr), (void *)(where)); \
}

#endif  /* XPT_DEBUG  */


#ifdef __cplusplus
}
#endif

/******************************************************
	XPT function prototypes
 ******************************************************/


int
cam_configure(
	cfg_op_t op,
	cfg_attr_t *indata,
	size_t indatalen,
	cfg_attr_t *outdata,
	size_t outdatalen);

void
cam_callback(void);

I32
xpt_init(void);

CCB_HEADER *
xpt_ccb_alloc(void);
CCB_HEADER *
xpt_ccb_alloc_nowait(void);

CCB_HEADER *
xpt_ccb_alloc_rad(int rad_id);
CCB_HEADER *
xpt_ccb_alloc_nowait_rad(int rad_id);


void
xpt_ccb_free(CCB_HEADER *ccb);

U32
xpt_action(CCB_HEADER *ccb);

I32
xpt_initialize(void);

I32
xpt_bus_register(CAM_SIM_ENTRY *cse);

I32
xpt_bus_deregister(I32 path_id);

I32
xpt_async(
    I32 opcode,
    I32 path_id,
    I32 target_id,
    I32 lun,
    char *buffer_ptr,
    I32 data_cnt);

I32
cam_inisr(void);

I32
cam_at_boottime(void);

void
xpt_callback_thread(void *);

void
scsiisr_init(void);

void
xpt_workthread_preque (int rad_id, void *arg1, void *arg2, PREQUE_CALLBACK func);

#ifdef CCB_HEADER3_DEFINED
void
xpt_callback (CCB_HEADER3 *cch);
#else
void
xpt_callback (CCB_HEADER *cch);
#endif


#endif /* _XPT_INCL_ */

