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
 *	@(#)$RCSfile: ipc_prims.h,v $ $Revision: 4.2.3.4 $ (DEC) $Date: 1999/03/30 15:22:18 $
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
 * OSF/1 Release 1.0
 */

#ifndef	_KERN_IPC_PRIMS_H_
#define _KERN_IPC_PRIMS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <mach/kern_return.h>
#include <mach/boolean.h>
#include <kern/ipc_hash.h>
#include <kern/macro_help.h>
#include <kern/msg_queue.h>
#include <mach/mach_types.h>
extern port_hash_t obj_entry_find(task_t, kern_obj_t);
extern port_hash_t obj_entry_lookup(task_t, port_name_t);
extern void obj_entry_change(task_t, kern_obj_t, port_hash_t, port_name_t, port_name_t);
extern void obj_entry_remove(task_t, kern_obj_t, port_hash_t);
extern void obj_entry_dealloc(kern_obj_t, port_hash_t);
extern void obj_entry_destroy(task_t, kern_obj_t, port_hash_t);
extern void obj_entry_insert(port_hash_t, task_t, kern_obj_t, port_name_t, port_type_t);
extern void obj_entry_create(port_hash_t, task_t, kern_obj_t, int);
extern port_hash_t obj_entry_make(task_t, kern_obj_t, boolean_t);

extern kern_return_t obj_alloc();
extern void obj_destroy_rights(kern_obj_t);

#define task_check_name(task, name)	\
		(obj_entry_lookup((task), (name)) != PORT_HASH_NULL)

#define task_check_rights(task, obj)	\
		(obj_entry_find((task), (obj)) != PORT_HASH_NULL)

extern void msg_queue_changed(msg_queue_t *, msg_return_t);

/*
 * extern void
 * obj_entry_lookup_macro(task, name, entry, notfound)
 *	task_t task;
 *	port_name_t name;
 *	port_hash_t &entry;
 *	code notfound;
 *
 * The task must be locked.  Upon normal return, the by-reference
 * parameter "entry" points to the translation entry found.
 * If no entry is found, the "notfound" code (which should be a
 * single complete statement) is executed; it should return/goto.
 */

#define obj_entry_lookup_macro(_task, name, entry, notfound) 		\
MACRO_BEGIN								\
	register port_hash_bucket_t *bucket;				\
									\
	bucket = &TL_table[port_hash_TL((_task), (name))];		\
	bucket_lock(bucket);						\
	(entry) = (port_hash_t) queue_first(&bucket->head);		\
									\
	for (;;) {							\
		if (queue_end(&bucket->head, (queue_entry_t) (entry))) {\
			bucket_unlock(bucket);				\
			notfound					\
		}							\
									\
		if (((entry)->task == (_task)) &&			\
		    ((entry)->local_name == (name))) {			\
			bucket_unlock(bucket);				\
			break;						\
		}							\
									\
		ipc_event(bucket_misses);				\
		(entry) = (port_hash_t) queue_next(&(entry)->TL_chain);	\
	}								\
MACRO_END

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif	/* _KERN_IPC_PRIMS_H_ */
