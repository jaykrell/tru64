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
 *	@(#)$RCSfile: xpr.h,v $ $Revision: 4.2.9.4 $ (DEC) $Date: 1999/02/09 19:03:22 $
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
 * Include file for xpr circular buffer silent tracing.  
 *
 */

/*
 * If the kernel flag XPRDEBUG is set, the XPR macro is enabled.  The 
 * macro should be invoked something like the following:
 *	XPR(XPR_SYSCALLS, ("syscall: %d, 0x%x\n", syscallno, arg1);
 * which will expand into the following code:
 *	if (xprflags & XPR_SYSCALLS)
 *		xpr("syscall: %d, 0x%x\n", syscallno, arg1);
 * Xpr will log the pointer to the printf string and up to 6 arguements,
 * along with a timestamp and cpuinfo (for multi-processor systems), into
 * a circular buffer.  The actual printf processing is delayed until after
 * the buffer has been collected.  It is assumed that the text/data segments
 * of the kernel can easily be reconstructed in a post-processor which
 * performs the printf processing.
 *
 * If the XPRDEBUG compilation switch is not set, the XPR macro expands 
 * to nothing.
 */

#ifndef	_KERN_XPR_H_
#define _KERN_XPR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <xpr_debug.h>

#if	XPR_DEBUG

#ifndef	__ASSEMBLER__

extern unsigned long xprflags;
#define XPR(flags,xprargs) if(xprflags&flags) xpr xprargs

#endif	/*__ASSEMBLER__*/

/*
 * flags for message types.
 */
#define XPR_SYSCALLS		(1 << 0)
#define XPR_TRAPS		(1 << 1)
#define XPR_SCHED		(1 << 2)

#define XPR_TCP			(1 << 5)
#define	XPR_PMAP		(1 << 6)
#define XPR_VM_MAP		(1 << 7)
#define XPR_VM_OBJECT		(1 << 8)
#define XPR_VM_OBJECT_CACHE	(1 << 9)
#define XPR_VM_PAGE		(1 << 10)
#define XPR_VM_PAGEOUT		(1 << 11)
#define XPR_MEMORY_OBJECT	(1 << 12)
#define XPR_VM_FAULT		(1 << 13)
#define XPR_INODE_PAGER		(1 << 14)
#define XPR_INODE_PAGER_DATA	(1 << 15)

#else	/*XPR_DEBUG*/
#define XPR(flags,xprargs)
#endif	/*XPR_DEBUG*/

#ifndef	__ASSEMBLER__
struct xprbuf {
	char 	*msg;
	long	arg1,arg2,arg3,arg4,arg5;
	int	timestamp;
	int	cpuinfo;
};
#endif	/*__ASSEMBLER__*/

/*
 * Function prototypes.
 */
extern void  xpr(char *msg, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6);
extern void  xprbootstrap(void);
extern void  xprinit(void);
extern void  xpr_save(struct xprbuf *buffer, int number);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif	/*_KERN_XPR_H_*/
