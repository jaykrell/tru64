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
 * 
 * HINT: set tabstops to 4
 *
 */

/*
 * HISTORY
 */
/*
 * @(#)$RCSfile: i2o_bs.h,v $ $Revision: 1.1.37.3 $ (DEC) $Date: 2001/11/26 17:49:31 $
 */


/*----------------------------------------------------------------------------*
 *  This file contains I2O Block Storage driver specific definitions
 *----------------------------------------------------------------------------*/

#ifndef _I2O_BS_H_
#define _I2O_BS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <ksm/ksm.h>
#include <sys/table.h>
#include <io/i2o/i2omsg.h>
#include <io/common/iotypes.h>

/*
 ********************* Define for use during debug *************************
 */

#ifdef I2O_BS_DEBUG

/* debugging printf classes */
#define D_CFG           0x00010000      /* config messages */
#define D_REPLY         0x00020000      /* reply messages */
#define D_DRVR          0x00800000      /* Device Driver messages */
#define D_MEM           0x01000000      /* Memory Management msgs */
#define D_MISC          0x02000000      /* Misc messages */
#define	D_RESET			0x04000000		/* Reset processing */
#define D_CLASS_MASK    0xFFFF0000

#define D_NONE          0x00000000
#define D_NOTABLE       0x00000001
#define D_ERROR         0x00000002
#define D_TRACE         0x00000004
#define D_INFO          0x00000100
#define D_INFO1         0x00000200
#define D_INFO2         0x00000400
#define D_INFO3         0x00000800
#define D_ENTRY         0x00001000
#define D_EXIT          0x00002000
#define D_CASE_MASK     0x0000FFFF

#define D_ALL           (0xFFFFFFFF)

/*
 * print the message only if the classes match and if the case matches
 */
#define Printf(a,b)                                                 \
    if (((i2o_bs_debug & D_CLASS_MASK) & ((a) & D_CLASS_MASK)) &&       \
        ((i2o_bs_debug & D_CASE_MASK) & ((a) & D_CASE_MASK)))           \
            printf b

#else

#define Printf(a,b)

#endif /* I2O_BS_DEBUG */


#define I2O_BS_MODULE(name) static char *module = name



/*--------------------------------------------------------------------------
 *  DEVICE DRIVER CONFIGURATION       
 *--------------------------------------------------------------------------*/


/* This value indicates a devsw failure */
#define NO_DEV                          -1

/* These are defines for indicating message type - r/w */
#define READ							1
#define WRITE							0

/* 
 * Defines for buses supported by the driver.
 *  #define I2O_BS_PARENT_BUS               "i2o"
 *  #define I2O_BS_PARENT_BUSTYPE           BUS_I2O
 */
#define I2O_BS_PARENT_BUS               DRIVER_WILDNAME

/*
 * Name of our subsystem
 */
#define I2O_BS_SUBSYS_NAME              "i2o_bs"

/*
 * Defines for Probe 
 */
#define PROBE_SUCCESS                   1
#define PROBE_FAIL                      0

#define SUCCESS                         0
#define FAILURE                         1


/*--------------------------------------------------------------------------*
 *     Miscellaneous
 *--------------------------------------------------------------------------*/

/*
 * Determine if an address is in user space
 */
#define IS_USER_SPACE(addr)		(!IS_SYS_VA((vm_offset_t)(addr)))

/*
 * Hmmm - pick a max transfer size - any will do 
 */
/* this is temporarily limited to 4MB - needs to be fixed - QAR90561 - SOZMEN */
#define I2O_BS_MAX_XFRLEN			(4 * 1024 * 1024)		/*4MB*/

/*
 * Max dma transfer size
 * Simple s/g elements have a 24 bit DMA counter
 */
#define I2O_BS_DMA_MAX_COUNT  		0x00FFFFFF

/*
 * Convert block count to byte count
 */
#define I2O_BLK_2_BYTE(blk_num, blk_size)		\
	((blk_num) * (blk_size))	

/*
 * Additional I2O Messaging definitions
 */
typedef struct i2o_bs_param_op_list {
    I2O_PARAM_OPERATIONS_LIST_HEADER		hdr;
    I2O_PARAM_OPERATION_SPECIFIC_TEMPLATE	template;
} I2O_BS_PARAM_OP_LIST;

typedef struct i2o_bs_device_info_result_list {
    I2O_PARAM_RESULTS_LIST_HEADER			hdr;
	I2O_BSA_DEVICE_INFO_SCALAR				dev_info;
} I2O_BS_DEVICE_INFO_RESULT_LIST;

typedef struct i2o_bs_operational_control_result_list {
    I2O_PARAM_RESULTS_LIST_HEADER			hdr;
	I2O_BSA_OPERATIONAL_CONTROL_SCALAR		op_info;
} I2O_BS_OPERATIONAL_CONTROL_RESULT_LIST;


/*--------------------------------------------------------------------------*
 *     Basic "Job" structure
 *--------------------------------------------------------------------------*/

#define I2O_BS_RQST_VERSION           1 

typedef struct i2o_bs_rqst {
    /* generic queue for this request */
    queue_chain_t        queue_link;

	/*
	 * Note: rqst_state must be a 32-bit quantity, aligned on a longword
	 * boundary, since the allocation mechanism depends on atomicity
	 * (== 32 bits on Alpha).
	 */
    U32                 rqst_state;         /* execution state */

	/* i2o request message */
	I2O_MESSAGE_FRAME *i2o_request;

    /* i2o reply message for this request */
    I2O_SINGLE_REPLY_MESSAGE_FRAME *i2o_reply;

    /* dma handle for request */
    dma_handle_t        dma_handle;

    /* callback and callback arg for submitter */
    void                (*callback)(void *arg, struct i2o_bs_rqst *rqst);
    void                *callback_arg;

    /* hardware instance and original request context */
	I2O_TRANSACTION_CONTEXT	tc;
    struct i2o_bs_softc *bs_softc;
    struct buf          *bp;
    caddr_t				buff_addr;
    U32					buff_len;
    U32					dir;
    U32					phys_blknum;
    U32					flags;		    
	U32					num_sg;
    U32                 error;              /* completion status */
    int                 residual;           /* # bytes not transfered */

	/* timeout handling */
	u_int				timeout;			/* in seconds, counting down */
	int					retries;

	/* Time stamps for SAR statistics */
	long				start_time;
	long				pending_delta;
} I2O_BS_RQST;

/* values for rqst_state */
#define RQST_FREE	                0x00
#define RQST_PENDING                0x01
#define RQST_ACTIVE                 0x02
#define	RQST_COMPLETED				0x03

/* Default value for per-device request pool size. */
#define I2O_BS_RQST_POOL_SIZE	64

/*
 * The mapping between rqst and Transaction Context is as follows.  The
 * top 17 bits of the TC pick out a device (softc); the remaining 15 bits
 * index into the rqst array for that softc.
 */
#define	I2O_BS_TC_2_SOFTC(_sc,_tc) \
	{ (_sc) = i2o_bs_tc_2_softc((_tc) >> 15); }

/*--------------------------------------------------------------------------*
 *     Support structures for handling "reply" messages in a thread
 *--------------------------------------------------------------------------*/

/*
 * Each device instance will have its own thread to process reply and
 * asynchronous (event) messages. This is so we don't have to do this
 * processing in the context of the i2o subsystem, which may be calling
 * us in the context of an interrupt handler.
 *
 * Each device will have an input queue of message events. The reply/async
 * routine invoked by the i2o subsystem will place the message into the
 * event list and wake up the thread. The thread will remove the message
 * from the event and complete processing.
 */

#define EVENT_TYPE_REPLY		0x0000
#define EVENT_TYPE_ASYNC		0x0001
typedef struct i2o_bs_event {
	U32			type;
	i2o_msg_t	msg;
} i2o_bs_event_t;


/*--------------------------------------------------------------------------*
 *     Basic "Instance" structure (e.g. one per device)
 *--------------------------------------------------------------------------*/


#define I2O_BS_SOFTC_VERSION           3 

/*
 * A structure per each "i2o bs device" that maintains the device's "state".
 */
typedef struct i2o_bs_softc {
	/*
	 * Link for hash chain.  This needs to be first in the softc,
	 * since various routines assume that a pointer to the hash link
	 * can be converted into a pointer to the softc.
	 */
    queue_chain_t        hash_link;

    /* general housekeeping for driver */
    U32                 version;
    U32                 instance;

    /* topology handles */
    struct controller   *ctlr;
    struct device       *device;

    /* i2o handle for our "device/tid" */
    i2o_handle_t        tid_handle;
    u_int		        ic;
	u_int				abort_ic;

	/* lock for list-overflow handling */
    decl_simple_lock_data( ,softc_lock)

	/* pool of request structures for this device, and lock therefor */
	struct i2o_bs_rqst **rqst_pool;
    decl_simple_lock_data( ,rqst_pool_lock)

	/* Read-Write spinlock for synchronizing IOP resets */
	rws_lock_t reset_lock;

	uint next_rqst;
	uint num_rqsts;
	
	/* our device number ( IOP and TID ) */
	dev_t				dev;

    /* various device state values */
    ulong               flags;
    U32                 raw_part_opens;
    U32                 blk_part_opens;
    U32                 label_writeable;
    U32                 media_changes;
    U32                 soft_err_cnt;
    U32                 hard_err_cnt;
	int					recovering;
	int					reset_done;

    /* per-instance reply processing and timer threads */
    thread_t            reply_thread;
    U32                 reply_thread_shutdown;
	thread_t			timer_thread;
    U32                 timer_thread_shutdown;

	/* message event ring */
	U32					ring_head;
	U32					ring_tail;
	i2o_bs_event_t		*event_q;

	/* list of bufs waiting for a free rqst */
	struct buf *		bp_wait_list;

	/* list of rqsts pending completion of a reset */
	queue_head_t		pending_queue;

    DEVGEOMST           geometry;
    struct disklabel    label;
    U32					device_state;
	U32					device_capability;

	/* seconds to wait to declare an I/O timed out */
	u_int				timeout;

	/* Data needed for Steel - device naming, hwc, stats, etc... */
	MSS					*i2o_bs_mss;
	MSS					*ri_mss;
	MSS					*mss_hwm_rpt;
	void				*i2o_bs_current_values;
	void				*ri_current_values;
	void				*i2o_bs_dev_handle;
	void				*ri_dev_handle;
	long				i2o_bs_hardware_id;
	long				ri_hardware_id;
	int					ri_access;
	U32					ri_openpart;
	U32					new_openpart;
	U32					old_openpart;
	char				*ri_unique_name;
	char				*i2o_bs_unique_name;
	U32					ri_read_count;
	U32					ri_write_count;
	U32					ri_read_bytes;
	U32					ri_write_bytes;
	int					ri_diskstat_i;
	int					devind;		/* device index used in unique naming */
	struct tbl_dkinfo	ri_stats;
	ulong			rqst_wait;
} I2O_BS_SOFTC;

/*
 * Default value, in seconds, for request timeout interval, if the IOP
 * doesn't tell us.
 */
#define	I2O_BS_TIMEOUT_DEFAULT	180		/* 3 minutes */

/* Period (seconds) at which timeout thread wakes up. */
#define	I2O_BS_TIMER_INTERVAL	10		/* 10 seconds */

/* Number of times to retry commands that time out */
#define	I2O_BS_RETRY_COUNT	2


/* some defines for I2O_BS_SOFTC->flags */
#define READ_ONLY       0x00001
#define OPEN_IN_PROG	0x00002	   /* single thread opens around readlabel */


/*
 * Bit format for minor number -- specific to this driver.
 *
 * This info is maintained via a persistent database, so that
 * the same device number will always refer to the same storage
 * set, throughout the life of that storage set.
 *
 *   Bits 
 *     19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
 *   +-------------------------------------------------------------+
 *   | X X X|       IOP #  |    Storage Set #    | X X X |Partition|
 *   +-------------------------------------------------------------+
 *
 * Note: finder currently looks at only 4096 device numbers for "ri"
 * type devices, so we've limited IOP# to (0 .. 31).  If you need to
 * increase this number, you'll also need to increase the loop limit
 * in finder (which will slow finder down).
 *
 */
#define PART_MASK                       0x7
#define PART_SHIFT                      6
#define GET_PARTITION(dev)              (getminor(dev) & PART_MASK)
#define GET_DEVICENUM(dev)              (getminor(dev) >> PART_SHIFT)
#define	MAKE_DEVICENUM(iop,devind)		((iop) << 7 | (devind))

#define	I2O_BS_MAX_IOPS					32
#define	I2O_BS_MAX_IOP_DEVS				128


/*--------------------------------------------------------------------------*
 *     "Instance" Management structure (e.g. how we find all our devices)
 *--------------------------------------------------------------------------*/
/*
 * We can't keep a full table to translate IOP/TID to softc, since that
 * would have 2^17 entries.  So, we use a hash, and resolve collisions
 * with simple chaining.
 *
 * The hash function is based on (limited) experience.  We've seen that
 * block-storage TID values tend to cluster, differing only in the lower
 * bits.  We add in the IOP number for the upper bits of the hashed value.
 *
 * Note that the shifts and masks in the hash expression are interrelated
 * with the hash table size.  If you change one, please change the other.
 */
#define	I2O_BS_HASH_TABLE_SIZE	256
#define	I2O_BS_HASH(_dn)	\
	((((getminor(_dn) & 0xc0000) >> 12) + (getminor(_dn) & 0x3ffc0) >> 6) % \
		I2O_BS_HASH_TABLE_SIZE)

#define	I2O_BS_DEV_2_SOFTC(_sc,_dn)	\
	{ \
		I2O_BS_SOFTC *_p; \
		(_sc) = NULL; \
		for(_p = (I2O_BS_SOFTC *) \
		  i2o_bs_softc_hash_table[I2O_BS_HASH(_dn)].next; \
			_p != (I2O_BS_SOFTC *) \
				&i2o_bs_softc_hash_table[I2O_BS_HASH(_dn)]; \
			_p = (i2o_bs_softc *)(_p->hash_link.next)) { \
			if( _p->dev == (_dn)) { \
				(_sc) = _p; \
				break; \
			}\
		}\
	}

/*--------------------------------------------------------------------------*
 *     Definitions for persistent configuration database
 *--------------------------------------------------------------------------*/
#define	I2O_BS_DB_NAME			"/etc/i2o_bs.db"
#define	I2O_BS_DB_BKUP_NAME		"/etc/i2o_bs.db.bak"
#define	I2O_BS_DB_SIGNATURE		0x27753563
#define	I2O_BS_DB_VERSION			1

typedef struct i2o_bs_db_hdr {
	U32	signature;
	U32 version;
} I2O_BS_DB_HDR;

typedef	struct i2o_bs_iop_data {
	queue_chain_t		iop_link;
    queue_head_t        tid_list;
	int iop_num;
} I2O_BS_IOP_DATA;

typedef struct i2o_bs_tid_data {
	queue_chain_t		tid_link;
	int					tid;
	int					devind;
} I2O_BS_TID_DATA;

typedef	struct i2o_bs_db_entry {
	int	iop_num;
	int	tid;
	int devind;
	int fill;
} I2O_BS_DB_ENTRY;


/*--------------------------------------------------------------------------*
 *     Miscellaneous Macro Definitions (queues, locks, etc)
 *--------------------------------------------------------------------------*/


/* *************************
 * Queuing Macros
 * ************************* */

#define INIT_QUEUE(qhead)                                       \
    (qhead)->next = (qhead)->prev = (qhead)

#define NONEMPTY_QUEUE(qhead)                                   \
    ((qhead)->next != (qhead))

#define EMPTY_QUEUE(qhead)                                      \
    ((qhead)->next == (qhead))

#define QUEUE_HEAD(qhead, typeptr, TYPE, Q)                     \
    {                                                           \
    TYPE                *tmp;                                   \
    tmp = (TYPE *)(qhead)->next;                                \
    (typeptr)->Q.next       = (queue_entry_t)tmp;               \
    (typeptr)->Q.prev       = (qhead);                          \
    if (tmp != (TYPE *)(qhead))                                 \
        tmp->Q.prev         = (queue_entry_t)(typeptr);         \
    else                                                        \
        (qhead)->prev       = (queue_entry_t)(typeptr);         \
    (qhead)->next           = (queue_entry_t)(typeptr);         \
    }

#define QUEUE_TAIL(qhead, typeptr, TYPE, Q)                     \
    {                                                           \
    TYPE                *tmp;                                   \
    tmp = (TYPE *)(qhead)->prev;                                \
    (typeptr)->Q.next       = (qhead);                          \
    (typeptr)->Q.prev       = (queue_entry_t)tmp;               \
    if (tmp != (TYPE *)(qhead))                                 \
        tmp->Q.next         = (queue_entry_t)(typeptr);         \
    else                                                        \
        (qhead)->next       = (queue_entry_t)(typeptr);         \
    (qhead)->prev           = (queue_entry_t)(typeptr);         \
    }

#define DEQUEUE_SELF(qhead, typeptr, TYPE, Q)                   \
    {                                                           \
    TYPE        *next, *prev;                                   \
    next    = (TYPE *)(typeptr)->Q.next;                        \
    prev    = (TYPE *)(typeptr)->Q.prev;                        \
    if (next != (TYPE *)(qhead))                                \
        next->Q.prev    = (queue_entry_t)prev;                  \
    else                                                        \
        (qhead)->prev   = (queue_entry_t)prev;                  \
    if (prev != (TYPE *)(qhead))                                \
        prev->Q.next    = (queue_entry_t)next;                  \
    else                                                        \
        (qhead)->next   = (queue_entry_t)next;                  \
    }

#define DEQUEUE_HEAD(qhead, typeptr, TYPE, Q)                   \
    {                                                           \
    TYPE            *next;                                      \
    (typeptr) = (TYPE *)(qhead)->next;                          \
    if ((typeptr) != (TYPE *)(qhead)) {                         \
        next = (TYPE *)(typeptr)->Q.next;                       \
        if (next != (TYPE *)(qhead))                            \
            next->Q.prev    = (qhead);                          \
        else                                                    \
            (qhead)->prev   = (qhead);                          \
        (qhead)->next   = (queue_entry_t)next;                  \
    } else {                                                    \
        (typeptr) = (TYPE *)NULL;                               \
    }                                                           \
    }


/*
 * Macros for i2o_bs_rqst_t->queue
 */
#define QUEUE_RQST_HEAD(qhead, rqst)                         \
    QUEUE_HEAD((qhead), (rqst), i2o_bs_rqst_t, queue)
#define QUEUE_RQST_TAIL(qhead, rqst)                         \
    QUEUE_TAIL((qhead), (rqst), i2o_bs_rqst_t, queue)
#define DEQUEUE_RQST_SELF(qhead, rqst)                       \
    DEQUEUE_SELF((qhead), (rqst), i2o_bs_rqst_t, queue)
#define DEQUEUE_RQST_HEAD(qhead, rqst)                       \
    DEQUEUE_HEAD((qhead), (rqst), i2o_bs_rqst_t, queue)


/* *************************
 * Locking Macros
 * ************************* */

/*
 * We've got the following locks:
 *
 *	. one global module lock for administrative functions (e.g., reading/
 *	  writing of persistent database);
 *
 *	. one lock per softc for list overflow and other softc-specific functions;
 *
 *	. one lock per softc, for managing that softc's request-structure list.
 *
 */

/*
 * global module lock macros
 */
#define INIT_MODULE_LOCK()                                          \
		simple_lock_setup(&i2o_bs_module_lock, i2o_bs_module_lockinfo)
#define LOCK_MODULE()                                               \
		{ simple_lock(&i2o_bs_module_lock); }
#define UNLOCK_MODULE()                                             \
		{ simple_unlock(&i2o_bs_module_lock); }
#define LOCK_MODULE_SPL(_spl)                                          \
		{ (_spl) = splbio(); simple_lock(&i2o_bs_module_lock); }
#define UNLOCK_MODULE_SPL(_spl)                                        \
		{ simple_unlock(&i2o_bs_module_lock); splx(_spl); }

/*
 * I2O_BS_SOFTC lock macros
 */
#define INIT_I2O_SOFTC_LOCK(_sc)                               \
    simple_lock_setup(&(_sc)->softc_lock, i2o_bs_softc_lockinfo)

#define LOCK_I2O_SOFTC(_sc)                                    \
    { simple_lock(&(_sc)->softc_lock); }

#define UNLOCK_I2O_SOFTC(_sc)                                  \
    { simple_unlock(&(_sc)->softc_lock); }

#define LOCK_I2O_SOFTC_SPL(_spl, _sc)                             \
    { (_spl) = splbio(); simple_lock(&(_sc)->softc_lock); }

#define UNLOCK_I2O_SOFTC_SPL(_spl, _sc)                           \
    { simple_unlock(&(_sc)->softc_lock); splx(_spl); }

/*
 * softc rqst pool lock macros
 */
#define INIT_RQST_POOL_LOCK(_sc)                               			\
    simple_lock_setup(&(_sc)->rqst_pool_lock, i2o_bs_rqst_pool_lockinfo)

#define LOCK_RQST_POOL(_sc)                               			\
    { simple_lock(&(_sc)->rqst_pool_lock); }

#define UNLOCK_RQST_POOL(_sc)                             			\
    { simple_unlock(&(_sc)->rqst_pool_lock); }

#define LOCK_RQST_POOL_SPL(_spl,_sc)                          			\
    { (_spl) = splbio(); simple_lock(&(_sc)->rqst_pool_lock); }

#define UNLOCK_RQST_POOL_SPL(_spl,_sc)                        			\
    { simple_unlock(&(_sc)->rqst_pool_lock); splx(_spl); }

/*
 * softc reset read/write lock macros
 */
#define	LOCK_RESET_READ_SPL(_spl,_sc)					\
	{ (_spl) = splbio(); rws_read_lock((_sc)->reset_lock); }

#define	UNLOCK_RESET_READ_SPL(_spl,_sc)					\
	{ rws_read_unlock((_sc)->reset_lock); splx(_spl); }

#define	LOCK_RESET_WRITE_SPL(_spl,_sc)					\
	{ (_spl) = splbio(); rws_write_lock((_sc)->reset_lock); }

#define	UNLOCK_RESET_WRITE_SPL(_spl,_sc)				\
	{ rws_write_unlock((_sc)->reset_lock); splx(_spl); }

/*
 * RI STATISTICS MACROS
 *
 * This timeline diagram illustrates the meaning of the time-related
 * statistics that are kept for the I2O_BS (ri devices) driver.
 *
 *      S1      S2      S3      S4      C1      C3      C2      C4      Idle
 *      |       |       |       |       |       |       |       |       |
 *      |<---------------t1------------>|       |       |       |       |
 *      |       |<-------------t2---------------------->|       |       |
 *      |       |       |<-----------t3-------->|       |       |       |
 *      |       |       |       |<--p4->|<---------t4---------->|       |
 *      |       |       |       |       |       |       |       |       |
 *      |<------------------di_time---------------------------->|       |
 *      |       |       |       |       |       |       |       |       |
 *      +-------+-------+-------+-------+-------+-------+-------+-------+-> t
 *
 *      S1 = start I/O #1       C1 = complete I/O #1
 *      S2 = start I/O #2       C2 = complete I/O #2
 *      S3 = start I/O #3       C3 = complete I/O #3
 *      S4 = start I/O #4       C4 = complete I/O #4
 *      t1,t2,t3,t4 = time on the active queue
 *               p4 = time on the pending queue
 *                    (this example suggests maximum queue size = 3)
 *
 *      di_avserv = (t1+t2+t3+t4) = total i/o time spent in active queue
 *      di_avwait = p4 = total i/o time spent in the pending queue
 *      di_avque  = current number of outstanding i/o requests
 *      di_xfer   = total number of completed i/o requests
 *      di_wds    = total number of 64-bit longwords transferred
 *      di_time   = (C4-S1) = total time disk was busy with i/o
 *
 *      Idle      = (Idle-C4) = disk is idle, with no i/o outstanding
 *
 * (I2O_BS_RQST *)rqst          pointer to the basic job structure 
 * (I2O_BS_SOFTC *)bs_softc     pointer to I2O_BS_SOFTC struct
 */
#define CURRENT_USEC(t, t_usec) {                               \
    extern struct timeval time;                                 \
    TIME_READ(t);                                               \
    t_usec = t.tv_sec * 1000000L + t.tv_usec;                   \
}
/*
 * The start time is stored in the rqst structure for all
 * commands that have enough resources to get initiated.
 * When there are no resourses available (ie. no rqst) the
 * start time gets stored in the buf structure.  
 */
#define RI_STATS_START(rqst, bs_softc) {                    \
    struct timeval now;                                     \
    long now_usec;                                          \
                                                            \
	if (rqst->start_time == 0L) {                           \
   	   	CURRENT_USEC(now, now_usec);                        \
      	rqst->start_time = now_usec;                        \
        bs_softc->ri_stats.di_num_req_initiated++;          \
        if (bs_softc->ri_stats.di_avque++ == 0L)            \
           	bs_softc->ri_stats.di_initial_busy = now_usec;  \
   	}                                                       \
}
/*
 * The "di_avwait" field will have the pending_delta quantity added in
 * RI_STATS_FINISH.  This macro assumes that once a rqst is moved from
 * the wait_list (pending queue) to the active queue, it will not move
 * back to the wait_list.  We know that during IOP resets a rqst can
 * move to the pending, but the frequency is minimal and the amount of
 * time is negligible.
 *
 * If this working set's start_time is not NULL, we can assume that the
 * i/o was timestamped by RI_STATS_START.  Otherwise, the timestamp is
 * saved in the buf structure (pending status).
 */
#define RI_STATS_PENDING(rqst,buf) {                            \
    struct timeval now;                                         \
    long now_usec;                                              \
																\
	if (rqst->start_time == 0L)									\
		rqst->start_time = buf->b_driver_un_2.timevalue;		\
                                                                \
    if (rqst->start_time > 0L) {                                \
        CURRENT_USEC(now, now_usec);                            \
        rqst->pending_delta = (now_usec - rqst->start_time);     \
    }                                                           \
}
/*
 * "Busy time": di_time contains the cumulative amount of non-idle time
 * (in usec) that a disk is busy servicing i/o requests (see the timeline
 * diagram above).  Note that the RI_STATS_FINISH macro does not wait for
 * the outstanding i/o count to drop to zero before adding another time
 * delta.  Instead, we cumulatively add the delta between the current time
 * "now_usec" and the previous i/o finish "di_initial_busy", then reset
 * di_initial_busy to the current time.
 */
#define RI_STATS_FINISH(rqst, bs_softc, bytes) {                           \
    struct timeval now;                                                    \
    long now_usec;                                                         \
    long delta;                                                            \
                                                                           \
    if (rqst->start_time > 0L) {                                           \
        CURRENT_USEC(now, now_usec);                                       \
        delta = (now_usec - rqst->start_time) - rqst->pending_delta;       \
        bs_softc->ri_stats.di_avserv += delta;       /* += service time */ \
        bs_softc->ri_stats.di_num_req_completed++;                         \
        if (bs_softc->ri_stats.di_avque > 0L)                              \
            bs_softc->ri_stats.di_avque--;           /* decr queue count */\
        delta = now_usec - bs_softc->ri_stats.di_initial_busy;             \
        bs_softc->ri_stats.di_time += delta;         /* += busy time */    \
        bs_softc->ri_stats.di_initial_busy = now_usec;/* reset busy start */    \
        if (rqst->pending_delta != 0L) {         /* pending time? */       \
            bs_softc->ri_stats.di_pxfer++;                                 \
            bs_softc->ri_stats.di_avwait += rqst->pending_delta;           \
        }                                                                  \
        bs_softc->ri_stats.di_xfer++;                /* incr xfer count */ \
        bs_softc->ri_stats.di_wds += bytes >> 6;     /* += byte count */   \
    }                                                                      \
}

/*
 * Define HWC reporting indicies
 */
#define RI_READ_OPS_IDX         0
#define RI_WRITE_OPS_IDX        1
#define RI_XFER_IDX             2
#define RI_AVSERV_IDX           3
#define RI_PXFER_IDX            4
#define RI_AVWAIT_IDX           5
#define RI_RBYTES_IDX           6
#define RI_WBYTES_IDX           7
#define RI_TID_IDX              8
#define RI_NUM_HWM_REP          9



#ifdef __cplusplus
}
#endif

#endif  /* _I2O_BS_H_ */


