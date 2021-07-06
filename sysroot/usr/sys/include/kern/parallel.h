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
 *	@(#)$RCSfile: parallel.h,v $ $Revision: 4.2.11.6 $ (DEC) $Date: 1999/02/09 19:03:14 $
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

#ifndef	_KERN_PARALLEL_H_
#define _KERN_PARALLEL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <rt_preempt.h>

extern int umast_calls;
extern int umast_to_master;
extern int umast_block;
extern int umast_release;
extern int umast_rel_cpu;
extern int umast_rel_block;

extern void unix_master(void);
extern void unix_release(void);
extern void unix_release_force(void);
extern void do_preemption(void);
extern int syscall_on_master(void);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif	/*_KERN_PARALLEL_H_*/
