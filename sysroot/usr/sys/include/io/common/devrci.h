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
#ifndef _DEVRCI_H_
#define _DEVRCI_H_

#ifdef __cplusplus
extern "C" {
#endif

#pragma ident "@(#)$RCSfile: devrci.h,v $ $Revision: 1.1.20.1 $ (DEC) $Date: 2001/09/13 13:08:30 $"

#include <sys/types.h>
#include <io/common/deveei.h>


/* 
 * The working set space definition
 */
typedef  struct iob_working_set {
    void *ptr[16];
} IOB_WORKING_SET;


/* 
 * The IOB_REQUEST struct
 */

typedef  struct iob_request {
    struct iob_request *iob_flink;    /* Forward linkage only for  
                                         service for enqueue into 
                                         IOB_REQUEST QUEUE */
    struct iob_request *iob_blink;    /* backward linkage only for 
                                         service for enqueue into 
                                         IOB_REQUEST QUEUE */
    int    opcode;                    /* Operation Code  - set by caller */
#define IOB_REG         0x1           /* Register with device and reserve */
#define IOB_PREEMPT     0x2           /* Currently not used by DRD */
#define IOB_GET_KEYS    0x3           /* Get Keys */
#define IOB_BARRIER     0x4           /* Blow away another nodes Register */
#define IOB_ABORT_REQ   0x5           /* Abort a current IOB Request 
                                         needs pointer to original IOB_REQ 
                                         structure */
#define IOB_REG_EXCLUS 0x6            /* Register exclusive use Not used 
                                         by disks - Tapes and changers only */
    dev_t  devt;                      /* Devices dev_t  set by caller*/
    void *drvhandle;	              /* Devices drvhandle if available non null, 
                                         null if not - set by caller */
    void (*iob_cbfcnp)();             /* Callback on completion function - 
                                         set by caller */
    struct iob_request *iob_req_abort;/* pointer to the IOB_REQUEST to abort */
    ulong   node_key;                 /* This instance (node/os) key for 
                                         IOB_REG, IOB_PREEMPT and IOB_PREEMPT
                                         set by caller */
    ulong  *key_list;                 /* Key list for  IOB_GET_KEYS and
                                         IOB_BARRIER - set by caller */
    int    key_cnt;                   /* Key list size - set by caller*/
    int    key_cnt_return;            /* Number of valid keys return in list */
    int    keys_not_reported;         /* for the opcode IOB_GET_KEYS
                                         the field shall be non zero if the 
                                         caller did not provide enough area
                                         for all keys - set by service */
    int    iobreq_status;             /* Completion status of request - 
                                         set by service */
    short  eei;                       /* EEI status output - after an error -
                                         Set by service  */
    time_t bdr_time;                  /* time that a bdr was issued - set by 
                                         service */
    int flags;                        /* Functional Flags -  set by caller */
#define IOB_FL_NORESET 0x1            /* functional modifier for IOB_BARRIER */
#define IOB_FL_NOPRES  0x2            /* functional modifier for IOB_BARRIER */
    u_int barrier_reset_type;         /* type of barrier if not PR - set by 
                                         service */
#define BARRIER_BUS_RESET    0x00000001 /* Bus reset type */
#define BARRIER_TARGET_RESET 0x00000002 /* Target reset */
#define BARRIER_LUN_RESET    0x00000004 /* Lun reset */
    IOB_WORKING_SET   issuer_ws;      /* Working set for the issuer (DRD) */
    IOB_WORKING_SET   service_ws;     /* Working set for the service (CAM) */
}IOB_REQUEST;

#ifdef __cplusplus
}
#endif
#endif /* not _DEVRCI_H_ */
