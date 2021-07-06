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
 *	@(#)$RCSfile: ipc_basics.h,v $ $Revision: 4.2.7.2 $ (DEC) $Date: 1996/08/14 21:06:45 $
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

#ifndef	_KERN_IPC_BASICS_H_
#define _KERN_IPC_BASICS_H_

#include <kern/kern_msg.h>
#include <kern/kern_port.h>
#include <kern/task.h>
#include <mach/message.h>

extern void send_notification(task_t, int, port_name_t);
extern void send_complex_notification(kern_port_t, int, int, kern_port_t);

extern kern_msg_t mach_msg(kern_msg_t);
extern msg_return_t msg_queue(kern_msg_t, msg_option_t, msg_timeout_t);

extern msg_return_t msg_send(msg_header_t *, msg_option_t, msg_timeout_t);
extern msg_return_t msg_send_from_kernel(msg_header_t *, msg_option_t, msg_timeout_t);
extern msg_return_t msg_receive(msg_header_t *, msg_option_t, msg_timeout_t);
extern msg_return_t msg_rpc(msg_header_t *, msg_option_t, msg_size_t, msg_timeout_t, msg_timeout_t);

extern msg_return_t msg_send_trap(msg_header_t *, msg_option_t, msg_size_t, msg_timeout_t);
extern msg_return_t msg_receive_trap(msg_header_t *, msg_option_t, msg_size_t, port_name_t,msg_timeout_t);
extern msg_return_t msg_rpc_trap(msg_header_t *, msg_option_t, msg_size_t, msg_size_t, msg_timeout_t, msg_timeout_t);

#endif	/*_KERN_IPC_BASICS_H_*/
