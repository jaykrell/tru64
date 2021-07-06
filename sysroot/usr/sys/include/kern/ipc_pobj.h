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
 *	@(#)$RCSfile: ipc_pobj.h,v $ $Revision: 4.2.9.5 $ (DEC) $Date: 1997/08/04 11:47:05 $
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

#ifndef	_KERN_IPC_POBJ_H_
#define _KERN_IPC_POBJ_H_

#include <kern/host.h>
#include <mach/port.h>
#include <kern/port_object.h>
#include <kern/processor.h>
#include <kern/task.h>
#include <kern/thread.h>
#include <vm/vm_map.h>

extern task_t convert_port_to_task(port_t);
extern thread_t convert_port_to_thread(port_t);
extern vm_map_t convert_port_to_map(port_t);
extern port_t convert_task_to_port(task_t);
extern port_t convert_thread_to_port(thread_t);

extern host_t convert_port_to_host(port_t);
extern host_priv_t convert_port_to_host_priv(port_t);
extern processor_t convert_port_to_processor(port_t);
extern processor_set_t convert_port_to_pset(port_t);
extern processor_set_t convert_port_to_pset_name(port_t);
extern port_t convert_host_to_port(host_t);
extern port_t convert_processor_to_port(processor_t);
extern port_t convert_pset_to_port(processor_set_t);
extern port_t convert_pset_name_to_port(processor_set_t);
extern port_name_t convert_thread_to_uport(thread_t);
extern thread_t convert_uport_to_thread(task_t, port_name_t, boolean_t);

#endif	/*_KERN_IPC_POBJ_H_*/
