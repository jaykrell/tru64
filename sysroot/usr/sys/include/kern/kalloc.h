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
 *	@(#)$RCSfile: kalloc.h,v $ $Revision: 4.2.7.1 $ (DEC) $Date: 2002/01/29 21:23:42 $
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

#ifndef	_KERN_KALLOC_H_
#define _KERN_KALLOC_H_

#include <sys/param.h>
#include <sys/malloc.h>

#ifndef __VMS
#define kalloc(size) malloc((u_long)(size),BUCKETINDEX(size),M_KALLOC,M_WAITOK)
#define kget(size)   malloc((u_long)(size),BUCKETINDEX(size),M_KALLOC,M_NOWAIT)
#define kfree(p,size) free((void *)(p),M_KALLOC)
#else
#define kalloc(size) inet$malloc((u_long)(size),M_KALLOC,M_WAITOK)
#define kget(size)   inet$malloc((u_long)(size),M_KALLOC,M_NOWAIT)
#define kfree(p,size) inet$free((void *)(p))
#endif  /* __VMS */

#endif	/* _KERN_KALLOC_H_ */
