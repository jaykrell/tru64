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
 * @(#)$RCSfile: dyn_msg_queue.h,v $ $Revision: 1.1.2.3 $ (DEC) $Date: 1999/02/09 19:03:04 $
 */

#ifndef _DYN_MSG_QUEUE_H_
#define _DYN_MSG_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef char * dyn_msgQHT;  /* handle to a message queue */

int
msgq_create(
    dyn_msgQHT *msgQH,      /* out - message queue handle */
    int maxMsgs,        /* in - max message buffers to allocate for queue */
    int maxMsgSize      /* in - max number of bytes per message */
    );

void
msgq_delete(
    dyn_msgQHT msgQH        /* in - message queue handle */
    );

void *
msgq_alloc_msg(
    dyn_msgQHT msgQH        /* in - message queue handle */
    );

void
msgq_free_msg(
    dyn_msgQHT msgQH, /* in - message queue handle */
    void *msg
    );

void
msgq_send_msg(
    dyn_msgQHT msgQH,       /* in - message queue handle */
    void *msg           /* in - message ptr */
    );

void *
msgq_recv_msg(
    dyn_msgQHT msgQH        /* in - message queue handle */
    );

int
msgq_msg_avail(
    dyn_msgQHT msgQH        /* in - message queue handle */
    );

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

