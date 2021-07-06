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
 * @(#)$RCSfile: xpt3.h,v $ $Revision: 1.1.6.2 $ (DEC) $Date: 1999/07/30 19:31:09 $
 */

#ifndef _XPT3_INCL_
#define _XPT3_INCL_

#ifdef __cplusplus
extern "C" {
#endif

#include <io/cam/cam_types.h>
#include <io/cam/cam3_scsi.h>
#include <io/cam/xpt.h>

/*
 * Compiler switch(es)
 */


/*
 * Default working set sizes for intial ccb allocation
 */

#define XPT_PDRV_DEFAULT_WS_SIZE	0x100
#define XPT_SIM_DEFAULT_WS_SIZE		0x100

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

typedef struct xpt_ws3
{

#define XPT_WS3_VERS	1		/* please incr if XPT_WS changes */

    struct xpt_ws      *flink;		/* forward pointer in the chain */
    struct xpt_ws      *blink;		/* backward pointer in the chain */
    CCB_HEADER3        *xpt_ccb;	/* pointer to the CCB */
    CAM_U32             xpt_flags;	/* flags for the status of this CCB */
    CAM_U32             owner;		/* Entity that owns the packet   */
    LOCALITY_CONTEXT    locality_context;/* Locality context ie. rad */
    xpt_callback_hdr_t *xpt_cback_hdr;
} XPT_WS3;


/*
 * This is the declaration for the CAM-3 header/CCB packet resource controlled
 * by the XPT.  This structure contains the three headers (or their pointers)
 * used by the XPT,PDrvs, and the SIMs, followed by the CCB space.
 * It is expected that accesses to this structure will be used via casting the
 * XPT header pointer andsome form of address arithmetic using the CCB pointers.
 *
 * Note:  It is MANDATORY that the XPT working set be at the start of the packet.
 * Within the CAM code this knowledge is used in changing pointers by the
 * routines that deal with the CCB pool.
 *
 * Note:  It is MANDATORY that the pointer to SIM working set (SIM_WS) be
 * just before the CCB.  Within the SIM layer this knowledge is used to extract
 * the SIM_WS pointer.
 *
 * Note:  PDrv and SIM working buffers are tacked to the end of ccb union and their
 * size is based on the highest size used by any driver and/on adapter that
 * registered since the boot. In order to ensule proper alignment of the working
 * sets, ccb union is defined as a byte buffer rounded up to the 8 byte size
 */

typedef struct dec_cam3_pkt
{
    XPT_WS3      xws;		/* XPT working set */
    void	*pws;		/* Points to PDrv working set */
    void	*sws;		/* Points to SIM working set */
    CAM_U8 ccb_un[CCB_SIZE_UNION3]; /* The CCB union for all CCBs */
} DEC_CAM3_PKT;

/*
 * General queue header
 */
typedef struct xpt_quehead {
    struct xpt_quehead	*flink;
    struct xpt_quehead	*blink;
} XPT_QUEHEAD;

/*
 * CAM-3 XPT macros
 * ================
 */
/*
 * Compile switch XPT_INLINE_ENA controls whether macros
 * will generate inline expansion or call a function. Switch
 * is mostly included for testing the functions and DEC-UNIX
 * code is expected to use the inline expansion for the sake
 * of the performance.
 */

#define XPT_INLINE_ENA		1

#if XPT_INLINE_ENA

#define XPT_ISR	( AT_INTR_LVL() )

#define XPT_MEM_ALLOC(size, flags) \
    ( CAM_VM_OFFSET )cam_zalloc(size)

#define XPT_MEM_FREE( addr )	\
    FREE((caddr_t)addr, M_DEVBUF)

#define XPT_QUE_INIT(qhead)	\
{				\
    (qhead)->flink = (qhead);	\
    (qhead)->blink = (qhead);	\
}

#define XPT_INSQUE(data, que_element)		\
{						\
    (data)->flink = (que_element)->flink;	\
    (data)->flink->blink = (data);		\
    (data)->blink = (que_element);		\
    (que_element)->flink = (data);		\
}

#define XPT_REMQUE(data)			\
{						\
    (data)->blink->flink = (data)->flink;	\
    (data)->flink->blink = (data)->blink;	\
}

#define XPT_INSQUE_HEAD(data, qhead)	\
{					\
    (data)->flink = (qhead)->flink;     \
    (data)->flink->blink = (data);	\
    (data)->blink = (qhead);		\
    (qhead)->flink = (data);		\
}

#define XPT_REMQUE_HEAD(data, qhead)	\
{					\
    (data) = (qhead)->flink;		\
    if ((data) != (qhead)) {		\
	(qhead)->flink = (data)->flink;	\
	(data)->flink->blink = (qhead);	\
    }					\
    else				\
	(data) = (XPT_QUEHEAD *)NULL;	\
}

#define XPT_INSQUE_TAIL(data, qhead)	\
{					\
    (data)->blink = (qhead)->blink;     \
    (data)->blink->flink = (data);	\
    (data)->flink = (qhead);		\
    (qhead)->blink = (data);		\
}

#define XPT_REMQUE_TAIL(data, qhead)	\
{					\
    (data) = (qhead)->blink;		\
    if ((data) != (qhead)) {		\
	(qhead)->blink = (data)->blink;	\
	(data)->blink->flink = (qhead);	\
    }					\
    else				\
	(data) = (XPT_QUEHEAD *)NULL;	\
}

#define XPT_SLEEP(channel)		\
{					\
    assert_wait ((vm_offset_t)channel, FALSE); \
    thread_block();			\
}

#define XPT_WAKEUP(channel)	   \
{					\
    thread_wakeup((vm_offset_t)channel); \
}

#else	/* If inline expansion disabled	*/
	/* ============================ */

#define XPT_ISR	(xpt_isr())

#define XPT_MEM_ALLOC(size)	\
    xpt_mem_alloc(size, 0)

#define XPT_MEM_FREE( addr )	\
    xpt_mem_free(addr)

#define XPT_QUE_INIT(qhead)	\
    xpt_que_init(qhead)

#define XPT_INSQUE(data, que_element)	\
    xpt_insque(data, que_element)

#define XPT_REMQUE(data)		\
    xpt_remque(data)

#define XPT_INSQUE_HEAD(data, qhead)	\
    xpt_insque_head(data, qhead)

#define XPT_REMQUE_HEAD(data, qhead)	\
    data = xpt_remque_head(qhead)

#define XPT_INSQUE_TAIL(data, qhead)	\
    xpt_insque_tail(data, qhead)

#define XPT_REMQUE_TAIL(data, qhead)	\
    data = xpt_remque_tail(qhead)

#define XPT_SLEEP(channel)		\
    xpt_sleep(channel)

#define XPT_WAKEUP(channel)		\
    xpt_wakeup(channel)

#endif  /* End of inline expansion conditional */

#ifdef __cplusplus
}
#endif

#endif /* _XPT3_INCL_ */

