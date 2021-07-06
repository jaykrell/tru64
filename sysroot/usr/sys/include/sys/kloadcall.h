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
 *	@(#)$RCSfile: kloadcall.h,v $ $Revision: 4.2.9.3 $ (DEC) $Date: 1998/10/20 19:03:21 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */

#ifndef _SYS_KLOADCALL_H_
#define _SYS_KLOADCALL_H_
/*
 * Operation Code for kloadcall(2)
 */

#define	KLC_VM_ALLOCATE		1
#define	KLC_VM_DEALLOCATE	2
#define	KLC_VM_READ		3
#define	KLC_VM_WRITE		4
#define	KLC_VM_PROTECT		5
#define	KLC_VM_ALLOCATE_WIRED	6

#define	KLC_CALL_FUNCTION	100

#ifdef __digital__
#define KLC_SET_STATE		101
#define KLC_GET_BOOTLINK_SYMTAB	102
#endif

#endif
