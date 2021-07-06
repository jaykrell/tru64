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
 *	@(#)$RCSfile: vm_user.h,v $ $Revision: 4.2.6.2 $ (DEC) $Date: 1996/08/14 21:07:51 $
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
 *	File:	vm/vm_user.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Copyright (C) 1986, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Declarations of user-visible virtual address space
 *	management functionality.
 */

#ifndef	_VM_VM_USER_H_
#define _VM_VM_USER_H_

#include <mach/kern_return.h>
#include <mach/mach_types.h>
#include <mach/machine/vm_types.h>
#include <vm/vm_map.h>


extern kern_return_t	vm_allocate(vm_map_t, vm_offset_t *, vm_size_t, boolean_t);

extern kern_return_t	vm_deallocate(vm_map_t, u_long, vm_size_t);
extern kern_return_t	vm_inherit(vm_map_t, vm_offset_t, vm_size_t, vm_inherit_t);
extern kern_return_t	vm_protect(vm_map_t, vm_offset_t, vm_size_t, boolean_t, vm_prot_t);
extern kern_return_t	vm_statistics(vm_map_t, vm_statistics_data_t *);
extern kern_return_t	vm_read(vm_map_t, u_long, vm_size_t, u_long *, u_int *);
extern kern_return_t	vm_write(vm_map_t, u_long, u_long, u_int);
extern kern_return_t	vm_copy(vm_map_t, u_long, vm_size_t, u_long);
extern kern_return_t	vm_map(vm_map_t, vm_offset_t *, vm_size_t, vm_offset_t, boolean_t,
				memory_object_t, vm_offset_t, boolean_t, vm_prot_t,
				vm_prot_t, vm_inherit_t);

#endif	/* _VM_VM_USER_H_ */
