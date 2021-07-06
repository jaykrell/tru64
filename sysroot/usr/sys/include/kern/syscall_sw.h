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
 *	@(#)$RCSfile: syscall_sw.h,v $ $Revision: 4.2.8.3 $ (DEC) $Date: 1997/01/02 18:59:35 $
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

#ifndef	_KERN_SYSCALL_SW_H_
#define _KERN_SYSCALL_SW_H_

#ifndef	ASSEMBLER

/* NOTE: size of this structure is known in locore.s */
typedef struct {
	short		mach_trap_length;
	short		mach_trap_flags;
	int		audparam_indx;
	int		(*mach_trap_function)();
} mach_trap_t;

extern mach_trap_t	mach_trap_table[];
extern int		mach_trap_count;

#ifdef	__digital__
#define MACH_TRAP(name, arg_count, flags, audparam)	\
		{ sizeof(long) * ((arg_count)+1), (flags), (audparam), (int (*)())(name) }
#else
#define MACH_TRAP(name, arg_count, flags, audparam)	\
		{ sizeof(int) * ((arg_count)+1), (flags), (audparam), (name) }
#endif
#define FN1(name,argno,flags,audparam)	MACH_TRAP(name, argno, 1<<flags, audparam)
#define FN(name, argno, audparam)	MACH_TRAP(name, argno, 0, audparam)

typedef struct {
	int		start_port;
	int		end_port;
#ifndef KERNEL
	char		**name_tbl;
#endif
} machipc_tbl_t;

#endif	/* ASSEMBLER */

/*
 *	Flag values (actually bit numbers)
 */

#define ASETJMP		0
#define APSIG		2

/*
 * trap numbers for mach ipc events (syscall_sw.c)
 */
#define MSG_SEND_TRAP       (-20)
#define MSG_RECEIVE_TRAP    (-21)
#define MSG_RPC_TRAP        (-22)

#endif	/* _KERN_SYSCALL_SW_H_ */
