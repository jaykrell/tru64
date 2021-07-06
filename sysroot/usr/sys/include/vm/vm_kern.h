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
 *	@(#)$RCSfile: vm_kern.h,v $ $Revision: 4.2.25.7 $ (DEC) $Date: 2000/04/05 13:05:48 $
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
/*
 *	File:	vm/vm_kern.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Copyright (C) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Kernel memory management definitions.
 *
 *	Revision History:
 *
 * 8-Apr-91	Ron Widyono
 *	Delay inclusion of sys/preempt.h (for RT_PREEMPT) to avoid circular
 *	include file problem.
 *
 */

#ifndef	_VM_VM_KERN_H_
#define _VM_VM_KERN_H_
#include <mach/kern_return.h>
#include <sys/types.h>

/*
 * flag values for kernel memory allocation routines
 */
#define	KMA_HERE	0x01	/* base address given, else "anywhere" */
#define	KMA_NOPAGEWAIT	0x02	/* don't wait for pages if unavailable */
#define	KMA_NOZEROFILL	0x04	/* don't need zero-filled memory */
#define KMA_TIMEDWAIT	0x08	/* don't wait forever for memory */

extern struct vm_map		*kernel_map;
extern struct vm_map		*kernel_pageable_map;
extern struct vm_map		*kernel_copy_map;

extern vm_offset_t	vm_kern_zero_page;	/* A page full of nothing */

/* Flags for VM use */

#define VM_MAP_SPACE_ANYWHERE   1
#define VM_MAP_SPACE_RM         2

/*
 * Prototypes
 */
struct vm_map;

extern void
	kmem_init(vm_offset_t, vm_offset_t),
	init_zero_page(void),
	kmem_stack_free(vm_offset_t),
	kmem_free(struct vm_map *, vm_offset_t, vm_size_t),
	k_mark_guard_page(vm_offset_t offset);

extern vm_offset_t
	kmem_alloc(struct vm_map *, vm_size_t);

extern struct vm_map
	*kmem_suballoc(struct vm_map *, vm_offset_t *,
			 vm_offset_t *, vm_size_t, boolean_t),
	*kmem_csuballoc(struct vm_map *, vm_offset_t *, 
			 vm_offset_t *, vm_size_t);
                                               
#endif	/* _VM_VM_KERN_H_ */
