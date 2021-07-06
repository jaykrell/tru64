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
 *	@(#)$RCSfile: zalloc.h,v $ $Revision: 4.2.12.3 $ (DEC) $Date: 1999/02/02 19:48:06 $
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
 *	File:	zalloc.h
 *	Author:	Avadis Tevanian, Jr.
 *	Copyright (C) 1985, Avadis Tevanian, Jr.
 *
 */

#ifndef	_KERN_ZALLOC_H_
#define _KERN_ZALLOC_H_

#include <standards.h>
#include <mach/machine/vm_types.h>
#include <kern/lock.h>
#include <kern/queue.h>
#include <kern/macro_help.h>


/*
 *	A zone is a collection of fixed size blocks for which there
 *	is fast allocation/deallocation access.  Kernel routines can
 *	use zones to manage data structures dynamically, creating a zone
 *	for each type of data structure to be managed.
 *
 */

typedef struct zone {
	vm_size_t	elem_size;	/* size of an element */
	char		*zone_name;	/* a name for the zone */
} *zone_t;

#define		ZONE_NULL	((zone_t) 0)
/*
 * Item definitions for zone_change:
 */
#define Z_WAITING	0x1	/* is thread waiting for expansion? */
#define Z_DOING_ALLOC	0x2	/* doing memory allocation */
#define Z_EXHAUST	0x4	/* Make zone exhaustible	*/
#define Z_COLLECT	0x8	/* Make zone collectable	*/
#define Z_PAGEABLE	0x10	/* Make zone pageable		*/
#define Z_EXPAND	0x20	/* Make zone expandable		*/
#define	Z_FOREIGN	0x40	/* Allow collectable zone to contain foreign */
				/* (not allocated via zalloc) elements. */


_BEGIN_CPLUSPLUS
extern vm_offset_t	zalloc(zone_t zone);
extern zone_t		zinit(vm_size_t size, vm_size_t max,
				vm_size_t alloc, char *name);
extern void		zfree(zone_t zone, vm_offset_t elem);
_END_CPLUSPLUS

#define ZFREE(zone, element)            \
MACRO_BEGIN                             \
        zfree(zone, element);           \
MACRO_END

#define ZALLOC(zone, ret, type)                 \
MACRO_BEGIN                                     \
                (ret) = (type)zalloc(zone);     \
MACRO_END

#endif	/*_KERN_ZALLOC_H_*/
