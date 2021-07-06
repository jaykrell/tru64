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
 *	@(#)$RCSfile: mig_user_hack.h,v $ $Revision: 4.2.5.2 $ (DEC) $Date: 1993/05/26 22:07:19 $
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
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */

#ifndef	_KERN_MIG_USER_HACK_H_
#define _KERN_MIG_USER_HACK_H_

/*
 * This file is meant to be imported with
 *	uimport <kern/mig_user_hack.h>;
 * by those interfaces for which the kernel (but not builtin tasks)
 * is the client.  See memory_object.defs and memory_object_default.defs.
 * It has the hackery necessary to make Mig-generated user-side stubs
 * usable by the kernel.
 *
 * The uimport places a
 *	#include <kern/mig_user_hack.h>
 * in the generated header file for the interface, so any file which
 * includes the interface header file will get these definitions,
 * not just the user stub file like we really want.
 */
#include <kern/ipc_basics.h>

#define msg_send			msg_send_from_kernel
#define msg_rpc				msg_rpc_from_kernel
#define mig_get_reply_port		kern_get_reply_port
#define mig_dealloc_reply_port		kern_dealloc_reply_port

#endif	/*_KERN_MIG_USER_HACK_H_*/
