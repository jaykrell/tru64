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
 * @(#)$RCSfile: sim_htm.h,v $ $Revision: 1.1.7.2 $ (DEC) $Date: 1999/01/28 16:53:11 $
 */

#ifndef _SIM_HTM_
#define _SIM_HTM_

typedef struct list_type {
    struct list_type *flink;
    struct list_type *blink;
} LIST_TYPE;

typedef struct sim_htm_nexus {
#define SIM_HTM_NEXUS_VERS 1

     /*
      * targ_event_head and tail keep track to the FIFO of TARGET EVENT
      * MESSAGES which have not been processed because no IMMEDIATE
      * NOTIFY CCBs were available.  These must be the first two fields
      * of the SIMPORT_HTL_NEXUS struct.
      */
     LIST_TYPE *targ_event_head;
     LIST_TYPE *targ_event_tail;
     LIST_TYPE *targ_event_waiting_carriers;

     /*
      * Accept_recovery_list is used to maintain the
      * list of accept CCBs which will be issued to the adapter
      * when an enable LUN is performed during adapter crash
      * recovery.
      */
     LIST_TYPE *accept_recovery_list;

     /*
      * Copy of the Enable LUN CCB.  This information will be
      * used during error recovery.  Re_enable_lun is used to
      * store the CCB which is used to re-enable a LUN.
      */
     CCB_ENABLE_LUN ccb_enable_lun;
     CCB_ENABLE_LUN *re_enable_lun;

     /*
      * This are single-linked list
      */
     LIST_TYPE *immed_notify_free;	/* This is the list of available
					 * immediate notify CCBs. */
     LIST_TYPE *immed_notify_used;
     SIM_SOFTC *sim_sc;			/* Pointer to SIM_SOFTC */
     U32 lun;				/* LUN Nexus is associated to */
     U32 flags;
#define HTM_ENABLED       	0x001
#define BDR_IN_PROGRESS		0x004
#define BUS_RESET_IN_PROGRESS	0x008
#define DISABLE_IN_PROGRESS	0x010
#define ENABLE_IN_PROGRESS	0x020
#define CRASH_RECOV_IN_PROGRESS	0x040	/* Crash recovery - need to send the
					 * enable LUN */
#define CRASH_RECOV_COMPLETED	0x080   /* Crash recovery - waiting for 
					 * enable LUN response */

    simple_lock_data_t	htl_lock;	/* resource list lock */

} SIM_HTM_NEXUS;


#define SIM_GET_HTM_NEXUS(sim_sc, lun) \
    (sim_sc)->htm_nexus == NULL ? NULL : (sim_sc)->htm_nexus[(lun)]

/*
 * HTM_LIST_ADD() and HTM_LIST_DEL() assume NULL terminated lists.
 * They assume that "elem" contains flink and blink pointers.
 */
#define HTM_LIST_ADD(elem, list);					\
    (elem)->flink = (list);						\
    if ((list) != NULL) (list)->blink = (elem);				\
    (list) = (elem);
#define HTM_LIST_DEL(elem, list);					\
    if ((elem) == (list)) (list) = (elem)->flink;			\
    else (elem)->blink->flink = (elem)->flink;

#endif /* _SIM_HTM_ */
