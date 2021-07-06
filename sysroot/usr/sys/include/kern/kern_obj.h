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
 *	@(#)$RCSfile: kern_obj.h,v $ $Revision: 4.2.6.4 $ (DEC) $Date: 1993/08/31 20:58:01 $
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
 * Common fields for dynamically managed kernel objects
 * for which tasks have capabilities.
 *
 */

#ifndef	_KERN_KERN_OBJ_H_
#define _KERN_KERN_OBJ_H_

#include <mach/boolean.h>
#include <kern/lock.h>
#include <kern/queue.h>
#include <kern/assert.h>
#include <kern/macro_help.h>

typedef struct kern_obj {
	decl_simple_lock_data(,obj_data_lock)
	boolean_t obj_in_use;
	int obj_references;
	void (*obj_free_func)();
	queue_head_t obj_translations;
} *kern_obj_t;

#define KERN_OBJ_NULL		((kern_obj_t) 0)
#define KERN_OBJ_INVALID	((kern_obj_t) -1)

#define obj_lock(obj) 						\
MACRO_BEGIN							\
	simple_lock(&(obj)->obj_data_lock);			\
	assert((obj)->obj_references > 0);			\
MACRO_END

#define obj_lock_try(obj)	simple_lock_try(&(obj)->obj_data_lock)

#define obj_unlock(obj) 					\
MACRO_BEGIN							\
	assert((obj)->obj_references > 0);			\
	simple_unlock(&(obj)->obj_data_lock);			\
MACRO_END

#define obj_check_unlock(obj) 					\
MACRO_BEGIN							\
	if ((obj)->obj_references <= 0)				\
		obj_free(obj);					\
	else							\
		simple_unlock(&(obj)->obj_data_lock);		\
MACRO_END

#define obj_free(obj) 	 					\
MACRO_BEGIN							\
	assert(!(obj)->obj_in_use);				\
	assert((obj)->obj_references == 0);			\
	assert(queue_empty(&(obj)->obj_translations));		\
	simple_unlock(&(obj)->obj_data_lock);			\
	(*(obj)->obj_free_func)(obj);				\
MACRO_END

#define obj_reference(obj) 					\
MACRO_BEGIN							\
	obj_lock(obj);						\
	(obj)->obj_references++; 				\
	obj_unlock(obj);					\
MACRO_END

#define obj_release(obj) 					\
MACRO_BEGIN							\
	obj_lock(obj); 						\
	(obj)->obj_references--;				\
	obj_check_unlock(obj);					\
MACRO_END

#endif	/*_KERN_KERN_OBJ_H_*/
