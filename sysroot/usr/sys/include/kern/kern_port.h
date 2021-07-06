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
 *	@(#)$RCSfile: kern_port.h,v $ $Revision: 4.2.9.2 $ (DEC) $Date: 1996/08/14 21:07:12 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * Kernel internal structure associated with a port.
 *
 */

#ifndef	_KERN_KERN_PORT_H_
#define _KERN_KERN_PORT_H_

#include <mach/port.h>
#include <kern/kern_obj.h>
#include <kern/msg_queue.h>
#include <kern/queue.h>
#include <kern/port_object.h>
#include <kern/kern_set.h>

typedef struct kern_port {
	struct kern_obj port_obj;

	struct task	*port_receiver;
				/* Task holding receive rights */
	port_name_t	port_receiver_name;
				/* Receiver's local name for port */
	struct kern_port *port_backup;
				/* "Send rights" to a backup port */

	int		port_message_count;
				/* Optimistic number of queued messages */
	int		port_backlog;
				/* Queue limit before blocking */
	msg_queue_t	port_messages;
				/* Queued messages, if not in set */
	port_object_t	port_object;
				/* Kernel object I represent */

	kern_set_t	port_set;
				/* The set I belong to (else NULL) */
	queue_chain_t	port_brothers;
				/* List of all members of that set */
	boolean_t	kernel_reply_port;
				/* TRUE if reply prot for kernel RPC */
        boolean_t       privilege;
} port_data_t, *kern_port_t;

#define port_data_lock		port_obj.obj_data_lock
#define port_in_use		port_obj.obj_in_use
#define port_references		port_obj.obj_references
#define port_free_func		port_obj.obj_free_func
#define port_translations	port_obj.obj_translations

#define KERN_PORT_NULL		((kern_port_t)0)

#define port_lock(port)		obj_lock(&(port)->port_obj)
#define port_lock_try(port)	obj_lock_try(&(port)->port_obj)
#define port_unlock(port)	obj_unlock(&(port)->port_obj)
#define port_check_unlock(port)	obj_check_unlock(&(port)->port_obj)
#define port_free(port)		obj_free(&(port)->port_obj)
#define port_reference(port)	obj_reference(&(port)->port_obj)
#define port_release(port)	obj_release(&(port)->port_obj)

#endif	/* _KERN_KERN_PORT_H_ */
