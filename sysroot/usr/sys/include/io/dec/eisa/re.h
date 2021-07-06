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
 * @(#)$RCSfile: re.h,v $ $Revision: 1.1.28.1 $ (DEC) $Date: 2000/10/16 19:24:55 $
 */

#ifndef _RE_H_
#define _RE_H_

#include <sys/table.h>
#include <io/common/iotypes.h>

/* 
 * Struct definitions
 */

/*
 * The RE Specific Struct
 */
typedef struct re_specific {
    struct buf *rs_bufhd;       /* Anchor for requests which come 	*/
				/* into strategy that cannot be 	*/
				/* started due to resources 		*/
    U32 rs_unit_reported;	/* Is this unit config'ed in the cntrl	*/
    U32 rs_block_size;		/* Units block size			*/
    U32 rs_tot_size;		/* Units total block count		*/
    u_char rs_status;		/* Device status			*/
    u_char rs_raid_level;	/* The raid label			*/
    struct pt rs_pt;            /* Partition structure 			*/
    U32 rs_wlabel;           	/* Write enable label 			*/
    struct disklabel rs_label;	/* The label				*/
    char *rs_unique_name;	/* Unique name for hardware mgmt        */
    int rs_access;		/* hardware mgmt access attribute       */
    MSS	*rs_mss;		/* Pointer to MSS for hardware mgmt	*/
    void *rs_dev_handle;	/* hardware management handle		*/
    long rs_hardware_id;	/* hardware ID for this device		*/
}RE_SPECIFIC;


typedef struct xd_list {
	PD_WS *flink;
	PD_WS *blink;
}XD_LIST;


/*
 * The RE Device Struct
 */
typedef struct re_device {
    XD_LIST re_active;		/* Forward active pointer of cmds sent	*/
    U32 re_num_act;		/* Number of cmds sent			*/
    U32 re_dev;			/* major/minor number 			*/
    U32 re_ctrl;		/* Controller number			*/
    U32 re_unit;		/* Unit Number				*/
    U32 re_log_unit;		/* Our Logical Unit Number		*/
    U32 re_soft_errs;		/* Number of Soft errors		*/
    U32 re_hard_errs;		/* Number of Hard errors		*/
    U32 re_flags;		/* Specific to peripheral drivers	*/
    U32 re_state;		/* Specific to peripheral drivers	*/
    RE_SPECIFIC *re_specific;	/* Pointer to device specific info 	*/
    u_short re_spec_size;   	/* Size of device specific info 	*/
    U32 re_openpart;         	/* Bit mask of open parts 		*/
    U32 re_bopenpart;        	/* No of block opens 			*/
    U32 re_copenpart;        	/* No of char opens 			*/
    U32 re_old_openpart;        /* Bit mask of open parts old dev name  */
    U32 re_new_openpart;        /* Bit mask of open parts new dev name  */
    U32 re_cp_openpart;         /* Bit mask of open parts cp dev name   */
    U32 re_read_count;      	/* Number of reads to device 		*/
    U32 re_write_count;    	/* Number of writes to device 		*/
    U32 re_read_bytes;     	/* Number of bytes read from device 	*/
    U32 re_write_bytes;     	/* Number of bytes written to device 	*/
    int re_diskstat_i;		/* hwc diskstat index to this device	*/
    struct tbl_dkinfo re_stats;	/* Used for disk statistics             */
    dev_t re_bmajor;        	/* Block major number for loadables 	*/
    dev_t re_cmajor;        	/* Char major number for loadables 	*/
    simple_lock_data_t re_device_lk;/* The lock struct			*/
}RE_DEVICE;

/*
 * RE_DEVICE FLAGS
 */
#define RE_ONLINE	0x00000001	/* Device is online		*/
#define RE_OFFLINE	0x00000002	/* Device is offline		*/
#define RE_NODEVICE	0x00000004	/* No device			*/
#define RE_OPENRAW	0x00000008	/* Open raw			*/
#define RE_BEING_DELETED 0x0000010	/* Device is being deleted by hwm */


/*
 * The Unit Table element struct
 */
typedef struct re_table_elem {
    RE_DEVICE *el_device;	/* Ptr to device struct			*/
    U32 el_flags;		/* Flags opening closing modifing	*/
    U32 el_opens;		/* Opens against device			*/
    U16 el_type;		/* Device type disk tape etc.		*/
    u_char el_excluse;		/* Exclusive use indicator		*/
    simple_lock_data_t el_elem_lk;/* The lock struct                    */
}RE_TABLE_ELEM;

/*
 * el_flags
 */
#define EL_OPENING	0x0000001	/* Opening unit			*/
#define EL_CLOSING	0x0000002	/* Closing unit			*/
#define EL_WAITING	0x0000004	/* Something is waiting on prev	*/


#define RE_CLR_OPENING( ute )						\
{									\
    (ute)->el_flags &= ~EL_OPENING;					\
    wakeup(&rte->el_flags);						\
}
#define RE_CLR_CLOSING( ute )						\
{									\
    (ute)->el_flags &= ~EL_CLOSING;					\
    wakeup(&ute->el_flags);						\
}

/*
 * Flags for re_open_unit()
 */
#define RE_EXCLUSIVE		0x000000001
#define RE_SEMI_EXCLUSIVE	0x000000002
/*
 * Reserved			0x000000004
 *				0x000000008
 */
#define	RE_DO_PART		0x000000010	/* Do partition acct */
#define RE_FORCE		0x000000020	/* Force open if no device */

#define MINOR_SPEC_SHFT 6
#define UNIT_CTRL_MASK  0x7	/* Max number of units/controller */
#define CNTRL_SHIFT	0x3	/* SHIFTS down over unit	*/

/* New minor number format for Pluto II has changed the number
 * of bits in the controller field from 11 to 7.  
 * Number of controllers supported has increased from 6 to 8.
 */
#define CNTRL_MASK      0x7F    /* Controller field mask */
#define UNIT_MASK	0x3FF   /* Controller & unit field mask */
				/* needed to mask off new control */
				/* port bits */

/*
 * The upper 2 bits of the minor number are now used to indicate
 * control functions on the device
 */
#define XCR_CONTROL_PORT 0x1	/* control port define */
#define CONTROL_PORT_SHIFT 0x12 /* shift to 2 upper minor number bits */
#define CONTROL_PORT_MASK 0x3   /* 2 bit field */

/*
 * Check the dev passed to open/close/ioclt/r/w/strategy
 * Control port dev is on valid on open/close/ioctl calls
 */
#define CHECK_DEV_TYPE(dev)						\
	(((minor(dev)) >> CONTROL_PORT_SHIFT) & CONTROL_PORT_MASK)

#define RE_UNIT_TO_DEV(xxunit)	((xxunit) << MINOR_SPEC_SHFT)

/*
 * Convert a device struct unit number to a controller
 * and unit number
 * 
 * Need to mask off new control port bits...
 */
#define RE_DEV_TO_UNIT(dev) 		(GETUNIT(dev)) & UNIT_MASK

#define RE_DEV_CTRL_UNIT(dev)	(((GETUNIT(dev)) & UNIT_MASK) & 0x7)

#define GET_UBA_DEV(attach) makedev( 0, (RE_UNIT_TO_DEV((attach)->unit)))


#define RE_UNIT_TO_CNTRL(dev)						\
	(((RE_DEV_TO_UNIT(dev)) >> CNTRL_SHIFT) & CNTRL_MASK)

#define GET_RE_DEVICE(dev) re_unit_table[(GETUNIT(dev)) & UNIT_MASK].el_device


#define RE_GET_TAB_ELEM( dev )					\
	(RE_TABLE_ELEM *)&re_unit_table[(GETUNIT(dev)) & UNIT_MASK]

#define RE_GET_PART( dev )	((GETDEVS(dev)) & 0x03F)


/*
 * Lock Macros
 */

/*
 * locking macros.
 */
#define RE_LOCK_IT(lk, flags) usimple_lock((lk))
#define RE_UNLOCK_IT(lk) usimple_unlock((lk))
#define RE_SLEEP_UNLOCK_IT(chan, pri, lk) \
    mpsleep(chan, pri, "Zzzzzz", 0, (void *)lk, (MS_LOCK_NO_RELOCK|MS_LOCK_SIMPLE))
/* HW2
#define RE_LOCK_IT(lk, flags)
#define RE_UNLOCK_IT(lk)
#define RE_SLEEP_UNLOCK_IT(chan, pri, lk)				\
	mpsleep(chan, pri, "Zzzzzz", 0, (void *)0, 0)
*/

#define RE_TABLE_LK_INIT( ute )						\
{									\
    usimple_lock_setup( (simple_lock_t )&((ute)->el_elem_lk), re_table_li ); \
}

#define RE_ELEM_LK( ute, lk_type, saveipl )				\
{									\
	saveipl= splbio();						\
	RE_LOCK_IT( (simple_lock_t )&((ute)->el_elem_lk), (lk_type) );	\
}

#define RE_ELEM_UNLK( ute, saveipl )					\
{									\
	RE_UNLOCK_IT( (simple_lock_t )&((ute)->el_elem_lk) );		\
	(void)splx(saveipl);						\
}

#define RE_ELEM_SLEEPUNLOCK( chan, pri, ute )				\
	RE_SLEEP_UNLOCK_IT((chan), (pri), (simple_lock_t )&((ute)->el_elem_lk));	\
    
    


#define RE_INIT_LOCK( rpd )						\
{ 									\
    usimple_lock_setup((simple_lock_t )&((rpd)->re_device_lk), re_device_li ); \
}

#define RE_LK_DEVICE( rpd, lk_type, saveipl )				\
{									\
    (saveipl) = splbio();						\
    RE_LOCK_IT(((simple_lock_t)&(rpd)->re_device_lk), (lk_type));	\
}

#define RE_UNLK_DEVICE( rpd, saveipl )					\
{									\
	RE_UNLOCK_IT((simple_lock_t )&((rpd)->re_device_lk) );		\
	(void)splx(saveipl);						\
}

#define RE_SMP_SLEEPUNLOCK( chan, pri, rpd )				\
    RE_SLEEP_UNLOCK_IT((chan),(pri),(simple_lock_t )&((rpd)->re_device_lk)); 

#define RE_SMP_LOCK( rpd )						\
{									\
	RE_LOCK_IT( (simple_lock_t )&((rpd)->re_device_lk), LK_RETRY );	\
}

#define RE_LOWER_IPL( spl )						\
{									\
	splx( (spl) );							\
}


/*
 * Allocate a communication struct
 */
#define XCR_ALLOC_COM()		re_alloc_com()

/*
 * Free a a communication struct
 */
#define XCR_FREE_COM( comm )		re_free_com((comm))
    

/*
 * do generic setup of the com blk
 * args XCR_COM *, RE_DEVICE *, &completion function
 */
#define RE_SETUP_COM(comm,pdrv,done)					\
{									\
    (comm)->xcr_cntrl = (pdrv)->re_ctrl;				\
    (comm)->xcr_unit = (pdrv)->re_unit;					\
    (comm)->xcr_cbfcnp = (done);					\
    (comm)->xcr_pdrv_ws->rws_device = (u_char *)pdrv;			\
    (comm)->xcr_complete = 0;						\
}

/*
 * set up a local transfer using the XCR_COM area for data storage
 * Args XCR_COM *, struct buf *, transfer len.
 */
#define RE_COM_XFR_LOC( comm, buf, len )				\
{									\
    (comm)->xcr_bp = buf;						\
    (comm)->xcr_dxfer_len = len;					\
    (comm)->xcr_resid = 0;						\
    (comm)->xcr_flags |= XCR_LOC_DATA_BUF;				\
    (comm)->xcr_data_ptr = (u_char *)(comm)->xcr_cmd_data;		\
}

#define RE_DIRECTXFR_COM( comm, buf, len )				\
{									\
    (comm)->xcr_bp = (struct buf *)NULL;				\
    (comm)->xcr_dxfer_len = len;					\
    (comm)->xcr_resid = 0;						\
    (comm)->xcr_flags |= XCR_SPEC_CMD;					\
    (comm)->xcr_data_ptr = (u_char *)(buf);				\
}

#define RE_DIRECTSCSI_COM( comm, buf, len )				\
{									\
    (comm)->xcr_bp = (struct buf *)NULL;				\
    (comm)->xcr_dxfer_len = len;					\
    (comm)->xcr_resid = 0;						\
    (comm)->xcr_flags |= (XCR_SPEC_CMD | XCR_SCSI_CMD);			\
    (comm)->xcr_data_ptr = (u_char *)(buf);				\
}

#define RE_COM_XFRSG_BP(comm, scat, num_scat , buf, len)		\
{									\
    (comm)->xcr_bp = (buf);						\
    (comm)->xcr_dxfer_len = (len);					\
    (comm)->xcr_data_ptr = (u_char *)scat;				\
    (comm)->xcr_sg_num = (num_scat);					\
    (comm)->xcr_resid = 0;						\
    (comm)->xcr_flags |= XCR_SCATTER_BUF;				\
}

#define RE_COM_XFR_BP(comm, bp)						\
{									\
    (comm)->xcr_bp = (bp);						\
    (comm)->xcr_data_ptr = (u_char *)(bp)->b_un.b_addr;			\
    (comm)->xcr_dxfer_len = (bp)->b_bcount;				\
    (comm)->xcr_resid = 0;						\
    (comm)->xcr_flags |= XCR_BUF;					\
}
    

/* 
 * Fill in CMD info
 * Args XCR_COM *, CMD, Timeout seconds, block number
 */

#define RE_CMD(comm, cmd, timo, blk, flags)				\
{									\
    (comm)->xcr_command = cmd;						\
    (comm)->xcr_timeout = timo;						\
    (comm)->xcr_blk_nu = blk;						\
    (comm)->xcr_flags |= flags;						\
}

#define RE_CLEAR_COM( com )						\
{									\
    (com)->xcr_status = 0;						\
    (com)->xcr_adap_status = 0;						\
    (com)->xcr_complete = 0;						\
    (com)->xcr_resid = 0;						\
}
/*
 * Increase the timeout value since Mylex states that they will service
 * requests within 60 seconds.
 */
#define RE_IOTIME	60	/* I/O timeout value */
#define RE_DEF_TIMO	60	/* Non I/O timeout value */

/*
 * Insert into tail of active queue and ++ the active count
 * MUST BE DONE locked....
 */
#define RE_INSERT_Q( comm, pdrv )					\
    enqueue_tail((queue_t)&(pdrv)->re_active,				\
			(queue_entry_t)(comm)->xcr_pdrv_ws);		\
    (pdrv)->re_num_act++;

/*
 * Remove for the upper driver queues
 * Args XCR_COM * , RE_DEVICE *
 */
#define RE_REMOVE_Q( comm, pdrv )					\
    remque((struct queue_entry *)(comm)->xcr_pdrv_ws);			\
    (pdrv)->re_num_act--;


#define RE_IO_STRATEGY_ERR(bp, err) {		\
    bp->b_flags |= B_ERROR;			\
    bp->b_resid = bp->b_bcount;			\
    bp->b_error = err;				\
    (void) biodone(bp);				\
}

	

/*
 * Insert into tail of queue (tracking ) as send it on down
 * Args XCR_COM *, RE_DEVICE *
 */
#define RE_SEND_CMD( comm, pdrv, ret_stat)				\
{									\
    int spl_sav;							\
    RE_LK_DEVICE( (pdrv),(LK_RETRY), (spl_sav));			\
    if ((comm)->xcr_command == XCR_READ ||                              \
        (comm)->xcr_command == XCR_WRITE)                               \
        RE_STATS_START((comm)->xcr_pdrv_ws, (pdrv));                    \
    (void)RE_INSERT_Q((comm),(pdrv));					\
    RE_UNLK_DEVICE((pdrv), (spl_sav));					\
    *ret_stat = xcr_action((comm));					\
}


#define MAX_UNITS_CNTRL 8	/* Max number of systems drives per cntrl */
#define RE_NUM_PARTITIONS 8	/* Number of disk partitons		  */
/*
 * Status definitions for re_sysunit_info 
 */

#define RS_ONLINE	0x3 	/* No drives down in set		*/
#define RS_CRITICAL	0x4	/* A drive down in the set		*/
#define RS_OFFLINE	0xff	/* Configed unit but dead.		*/

/* 
 * Information returned per unit for the Get system drive info cmd
 */
typedef struct re_sysunit_info {
    U32 su_size;	    /* SIZE in sectors			*/
    u_char su_status; 	    /* 03h = ONLINE, 04h = CRITICAL, 0FFh=OFFLINE */
    u_char su_raidlevel;    /* RAID Level of device			*/
    U16 su_reserved;
}RE_SYSUNIT_INFO;

/*
 * Info returned for all drives for Get system drive info cmd
 */
typedef struct re_sysdrvs_info {
    RE_SYSUNIT_INFO sd_drvs[MAX_UNITS_CNTRL];
}RE_SYSDRVS_INFO;

/* 
 * Default partition size struct 
 */
typedef struct re_size {
	int          nblocks;
	daddr_t      blkoff;
}RE_DEF_SIZE;

/* defines for re_complete() */
#define	RE_IO_FAILURE	0x1
#define	RE_IO_DONE	0x2
#define RE_IO_RETRY	0x3


/*
 * Since the unit doesn't retrun any geometry info we must make it
 * up.. These are the defines to do so.
 */
#define RE_MAXHEADS 128		/* HEADS */
#define RE_SECPTRK  32		/* Sectors per track */
#define RE_SECSIZE  512		/* Number of bytes per sector */

/*
 * Since scatter gather is not on all machines
 * Max ioctl io size is 8k
 */
#define MAX_IOCTL_IO (1024 * 8)

/*
 * RE STATISTICS MACROS
 * 
 * This timeline diagram illustrates the meaning of the time-related
 * statistics that are kept for the RE driver.
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
 * (PD_WS *)pws         pointer to peripheral driver working set
 * (RE_DEVICE *)rpd     pointer to re_device struct
 */
#define CURRENT_USEC(t, t_usec) {                               \
    extern struct timeval time;                                 \
    TIME_READ(t);                                               \
    t_usec = t.tv_sec * 1000000L + t.tv_usec;                   \
}
#define RE_STATS_START(pws, rpd) {                              \
    struct timeval now;                                         \
    long now_usec;                                              \
                                                                \
    if (pws->start_time == 0L) {                                \
        CURRENT_USEC(now, now_usec);                            \
        pws->start_time = now_usec;                             \
        rpd->re_stats.di_num_req_initiated++;                   \
        if (rpd->re_stats.di_avque++ == 0L)                     \
            rpd->re_stats.di_initial_busy = now_usec;           \
    }                                                           \
}
/*
 * The "di_avwait" field will have the pending_delta quantity added in
 * RE_STATS_FINISH. Unlike CAM requests, all RE requests spend a non-zero
 * amount of time in the pending queue because all RE requests originate
 * from the pending queue.
 *
 * If this working set's start_time is not NULL, we can assume that the
 * i/o was timestamped by RE_STATS_START.
 */
#define RE_STATS_PENDING(pws) {                                 \
    struct timeval now;                                         \
    long now_usec;                                              \
                                                                \
    if (pws->start_time > 0L) {                                 \
        CURRENT_USEC(now, now_usec);                            \
        pws->pending_delta = (now_usec - pws->start_time);      \
    }                                                           \
}
/*
 * "Busy time": di_time contains the cumulative amount of non-idle time
 * (in usec) that a disk is busy servicing i/o requests (see the timeline
 * diagram above).  Note that the RE_STATS_FINISH macro does not wait for
 * the outstanding i/o count to drop to zero before adding another time
 * delta.  Instead, we cumulatively add the delta between the current time
 * "now_usec" and the previous i/o finish "di_initial_busy", then reset
 * di_initial_busy to the current time.
 */
#define RE_STATS_FINISH(pws, rpd, bytes) {                              \
    struct timeval now;                                                 \
    long now_usec;                                                      \
    long delta;                                                         \
                                                                        \
    if (pws->start_time > 0L) {                                         \
        CURRENT_USEC(now, now_usec);                                    \
        delta = (now_usec - pws->start_time) - pws->pending_delta;      \
        rpd->re_stats.di_avserv += delta;       /* += service time */   \
        rpd->re_stats.di_num_req_completed++;                           \
        if (rpd->re_stats.di_avque > 0L)                                \
            rpd->re_stats.di_avque--;           /* decr queue count */  \
        delta = now_usec - rpd->re_stats.di_initial_busy;               \
        rpd->re_stats.di_time += delta;         /* += busy time */      \
        rpd->re_stats.di_initial_busy = now_usec;/* reset busy start */ \
        if (pws->pending_delta != 0L) {         /* pending time? */     \
            rpd->re_stats.di_pxfer++;                                   \
            rpd->re_stats.di_avwait += pws->pending_delta;              \
        }                                                               \
        rpd->re_stats.di_xfer++;                /* incr xfer count */   \
        rpd->re_stats.di_wds += bytes >> 6;     /* += byte count */     \
    }                                                                   \
}

/*
 * Define EHM reporting indicies
 */
#define RE_READ_OPS_IDX		0
#define RE_WRITE_OPS_IDX	1
#define RE_XFER_IDX		2
#define RE_AVSERV_IDX		3
#define RE_PXFER_IDX		4
#define RE_AVWAIT_IDX		5
#define RE_RBYTES_IDX		6
#define RE_WBYTES_IDX		7
#define RE_NUM_EHM_REP		8

/*
 * RAID device name prefix for EHM registration
 */
#define RAID_DEVNAME_PREFIX "RAID-ctlr-"

#endif /* _RE_H_ */
