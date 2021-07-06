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
 *	@(#)$RCSfile: kern_msg.h,v $ $Revision: 4.3.13.2 $ (DEC) $Date: 1999/03/26 22:47:34 $
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
 * File:	kern_msg.h
 * Purpose:
 *	Kernel internal message structure.
 */

#ifndef	_KERN_KERN_MSG_H_
#define _KERN_KERN_MSG_H_

#include <mach/message.h>
#include <kern/queue.h>

/*
 *  boolean_t needed for C++ to compile
 */
#include <mach/boolean.h>
/* 
 * Note: kmsg_header must be the last element in kern_msg.  The mig places
 * other structures and possibly the actual message at after kmsg_header.
 *
 */
typedef struct kern_msg {
		queue_chain_t		queue_head;	/* must be first */
		struct port_hash *	sender_entry;
		boolean_t		kernel_message;
		msg_header_t		kmsg_header;
} *kern_msg_t;

#define		KERN_MSG_NULL	((kern_msg_t) 0)

#endif	/* _KERN_KERN_MSG_H_ */
