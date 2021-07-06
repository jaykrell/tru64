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
 * @(#)$RCSfile: addrconf.h,v $ $Revision: 1.2.11.2 $ (DEC) $Date: 1997/01/03 19:30:10 $
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */

#ifndef _ALPHA_ADDRCONF_H_
#define _ALPHA_ADDRCONF_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <sys/addrconf.h>

struct addressconf addressconf[AC_N_AREAS] = {

	{ (caddr_t)0x120000000,   AC_UPWARD|AC_FIXED },   /* AC_TEXT */
	{ (caddr_t)0x140000000,   AC_UPWARD|AC_FIXED },   /* AC_DATA */
	{ (caddr_t)0x140000000,   AC_UPWARD|AC_FLOAT },   /* AC_BSS */
	{ (caddr_t)0x11fffe000,   AC_DOWNWARD|AC_FIXED }, /* AC_STACK */
	{ (caddr_t)0x3ff80000000, AC_UPWARD|AC_FIXED },   /* AC_LDR_TEXT */
	{ (caddr_t)0x3ffc0000000, AC_UPWARD|AC_FLOAT },   /* AC_LDR_DATA */
	{ (caddr_t)0x3ffc0000000, AC_UPWARD|AC_FLOAT },   /* AC_LDR_BSS */
	{ (caddr_t)0x3ff00000000, AC_UPWARD|AC_FIXED },   /* AC_LDR_PRIV */
	{ (caddr_t)0x3ff10000000, AC_UPWARD|AC_FIXED },   /* AC_LDR_GLB */
	{ (caddr_t)0x3ff80000000, AC_UPWARD|AC_FIXED },   /* AC_LDR_PRELOAD */
	{ (caddr_t)0x120000000,   AC_UPWARD|AC_FLOAT },   /* AC_MMAP_TEXT */
	{ (caddr_t)0x20000000000, AC_UPWARD|AC_FLOAT },   /* AC_MMAP_DATA */
	{ (caddr_t)0x20000000000, AC_UPWARD|AC_FLOAT },   /* AC_MMAP_BSS */
	/*
	 * This specifies the start of the address region for a per-thread
	 * stack.  This is not necessarily the base of the stack.
	 */
	{ (caddr_t)0x20000000000, AC_DOWNWARD|AC_FLOAT }, /* AC_MMAP_STACK */
};

#ifdef __cplusplus
}
#endif
#endif /* _ALPHA_ADDRCONF_H_ */
