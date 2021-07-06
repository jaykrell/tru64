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
/*	@(#)asm.h	9.4	(ULTRIX)	11/29/90 */

/* ------------------------------------------------------------------ */
/* | Copyright Unpublished, MIPS Computer Systems, Inc.  All Rights | */
/* | Reserved.  This software contains proprietary and confidential | */
/* | information of MIPS and its suppliers.  Use, disclosure or     | */
/* | reproduction is prohibited without the prior express written   | */
/* | consent of MIPS.                                               | */
/* ------------------------------------------------------------------ */
/*  asm.h 4.2 */

/*
 * asm.h -- cpp definitions for assembler files
 */

#include <machine/pal.h>

/*
 * Notes on putting entry pt and frame info into symbol table for debuggers
 *
 *	.ent	name,lex-level	# name is entry pt, lex-level is 0 for c
 * name:			# actual entry point
 *	.frame	fp,framesize,saved_pc_reg
 *				# fp -- register which is pointer to base
 *				#	of previous frame, debuggers are special
 *				#	cased if "sp" to add "framesize"
 *				#	(sp is usually used)
 *				# framesize -- size of frame
 *				#	the expression:
 *				#		new_sp + framesize == old_sp
 *				#	should be true
 *				# saved_pc_reg -- either a register which
 *				#	contains callers pc or $31, if $31
 *				#	saved pc is assumed to be in
 *				#	(fp)+framesize-40
 *
 * Notes on .mask directives
 *
 *	.mask	SAVEDMASK,offset
 *
 *				# Saved mask is a constant with a bit for
 *				# each register that is actually saved in the
 *				# mask.  The bit that represents the `zero'
 *				# register is used to denote an exception
 *				# frame (all registers saved).
 *
 *				# offset is described as the offset from the
 *				# virtual frame pointer to the register save
 *				# area.
 *				#
 *
 * Notes regarding multiple entry points: Use "LEAF" for the first (main)
 * entry point and "XLEAF" for alternate (additional) entry points. The
 * "XLEAF"s must be nested within a "LEAF" and a ".end".
 * LEAF(copyseg)		# declare main entry point
 * XLEAF(copypage)		# declare alternate entry point
 */
/*
 * Added alternate LEAF for name space pollution cleanup in libc
 * and OLDLEAF for libc modules which need both
 */
/*
 * LEAF -- declare leaf routine
 */
#ifndef _NAME_SPACE_WEAK_STRONG
#define LEAF(x)						\
	.align	4;					\
	.globl	x;					\
	.ent	x,0;					\
	.frame	sp,0,ra;				\
x:
#ifdef _KERNEL
#define LEAF2(x,y)					\
	.align	4;					\
	.globl	x;					\
	.globl	y;					\
	.ent	x,0;					\
	.aent	y,0;					\
	.frame	sp,0,ra;				\
y:;							\
x:
#endif /* _KERNEL */
#else
#define	LEAF(x)         				\
	.align	4;					\
	.globl	__/**/x;	       			\
	.ent	__/**/x,0;	       			\
	.weakext x,__/**/x;				\
__/**/x:;                                               \
	.frame	sp,0,ra
#define	OLDLEAF(x)         				\
	.align	4;					\
        .globl  x;                                      \
        .ent    x,0;                                    \
x:;                                                     \
        .frame  sp,0,ra
#define	WEAK_LEAF(x,y)         				\
	.align	4;					\
	.globl	x;                                      \
	.ent	x,0;                                    \
	.weakext y,x;                                   \
x:;                                                     \
	.frame	sp,0,ra
#endif /* _NAME_SPACE_WEAK_STRONG */

/*
 * XLEAF -- declare alternate entry to leaf routine
 */
#define	XLEAF(x)					\
	.align	4;					\
	.globl	x;					\
	.aent	x,0;					\
x:

/*
 * VECTOR -- declare exception routine entry
 */
#if defined(_KERNEL) || defined(_EXCEPTION_FRAME)
#define	VECTOR(x, regmask)				\
	.align	4;					\
	.globl	x;					\
	.ent	x,0;					\
	.frame	sp,EF_SIZE,zero;			\
	.mask	M_EXCFRM|(regmask),-(EF_SIZE-(EF_RA*8));\
x:
#endif /* _KERNEL || _EXCEPTION_FRAME */

/*
 * Added alternate NESTED for name space pollution cleanup in libc
 * and OLDNESTED for libc modules which need both
 */
/*
 * NESTED -- declare nested routine entry point
 */
#ifndef _NAME_SPACE_WEAK_STRONG
#define	NESTED(x, fsize, rpc)				\
	.align	4;					\
	.globl	x;					\
	.ent	x,0;					\
x:;							\
	.frame	sp,fsize,rpc
#else
#define	NESTED(x, fsize, rpc)				\
	.align	4;					\
	.globl	__/**/x;	       			\
	.ent	__/**/x,0;	       			\
	.weakext x,__/**/x;				\
__/**/x:;                                               \
	.frame	sp,fsize,rpc
#define	OLDNESTED(x, fsize, rpc)			\
	.align	4;					\
	.globl	x;					\
	.ent	x,0;					\
x:;							\
	.frame	sp,fsize,rpc
#endif /* _NAME_SPACE_WEAK_STRONG */

/*
 * XNESTED -- declare alternate entry point to nested routine
 */
#define	XNESTED(x)					\
	.align	4;					\
	.globl	x;					\
	.aent	x,0;					\
x:

/*
 * END -- mark end of procedure
 */
#define	END(proc)					\
	.end	proc
/*
 * IMPORT -- import external symbol
 */
#define	IMPORT(sym, size)				\
	.extern	sym,size

/*
 * ABS -- declare absolute symbol
 */
#define	ABS(x, y)					\
	.globl	x;					\
x	=	y

/*
 * EXPORT -- export definition of symbol
 */
#define	EXPORT(x)					\
	.globl	x;					\
x:

/*
 * BSS -- allocate space in bss
 */
#define	BSS(x,y)		\
	.comm	x,y

/*
 * LBSS -- allocate static space in bss
 */
#define	LBSS(x,y)		\
	.lcomm	x,y

#define CHMK()						\
	.set	noat;					\
	call_pal PAL_callsys;				\
	.set	at

/*
 * SYSCALL -- standard system call sequence
 * The kernel expects arguments to be passed with the normal C calling
 * sequence.  v0 should contain the system call number.  On return from
 * the kernel mode, a3 will be 0 to indicate no error and non-zero to
 * indicate an error; if an error occurred v0 will contain an errno.
 * if the kernel return an error, setup a valid gp and jmp to _cerror
 */
#ifdef	HABITAT_INDEX
#define	SYSCALL(x)					\
LEAF(x);						\
	ldiq	v0, (HABITAT_NSTD_CALL(x) - HABITAT_BASE) | HABITAT_INDEX; \
	CHMK();						\
	beq	a3,9f;					\
	br	gp,127f;					\
127:							\
	ldgp	gp,0(gp);				\
	jmp	zero,_cerror;				\
9:
#else
#define	SYSCALL(x)					\
LEAF(x);						\
	ldiq	v0,SYS_/**/x;				\
	CHMK();						\
	beq	a3,9f;					\
	br	gp,127f;					\
127:							\
	ldgp	gp,0(gp);				\
	jmp	zero,_cerror;				\
9:
#endif	/* HABITAT_INDEX */
/*
 * PSEUDO -- system call sequence for syscalls that are variations of other
 * system calls
 */
#define	PSEUDO(x,y)					\
LEAF(x);						\
	ldiq	v0,SYS_/**/y;				\
	CHMK()						\

#define	CALL(y)						\
	jsr	ra,y;					\
	ldgp	gp,0(ra)

#define	RET						\
	ret	zero,(ra),1

/*
 * SYSCALL_X_TO_Y -- to support syscalls that need to be defined with the
 * old syscall name for backwards compatability and linking, but need to
 * reference a new kernel syscall name.
 */
#define SYSCALL_X_TO_Y(x,y)				\
LEAF(x);						\
	ldiq    v0,SYS_/**/y;				\
	CHMK();						\
	beq     a3,9f;					\
	br      gp,127f;				\
127:							\
	ldgp    gp,0(gp);				\
	jmp     zero,_cerror;				\
9:

/*
 * The following macros reserve the usage of the local label '9'
 */
#define	MESG(msg)					\
	.rdata;						\
9:	.asciiz	msg;					\
	.text

#define	PRINTF(msg)					\
	lda	a0,9f;					\
	jsr	ra,printf;				\
	ldgp	gp,0(ra);				\
	MESG(msg)

#define	PUTMSG(msg)					\
	lda	a0, 9f;					\
	jsr	ra,putstr;				\
	ldgp	gp,0(ra);				\
	MESG(msg)

/*
 * register mask bit definitions
 */
#define	M_V0		0x00000001
#define	M_T0		0x00000002
#define	M_T1		0x00000004
#define	M_T2		0x00000008
#define	M_T3		0x00000010
#define	M_T4		0x00000020
#define	M_T5		0x00000040
#define	M_T6		0x00000080
#define	M_T7		0x00000100
#define	M_S0		0x00000200
#define	M_S1		0x00000400
#define	M_S2		0x00000800
#define	M_S3		0x00001000
#define	M_S4		0x00002000
#define	M_S5		0x00004000
#define	M_S6		0x00008000
#define	M_A0		0x00010000
#define	M_A1		0x00020000
#define	M_A2		0x00040000
#define	M_A3		0x00080000
#define	M_A4		0x00100000
#define	M_A5		0x00200000
#define	M_T8		0x00400000
#define	M_T9		0x00800000
#define	M_T10		0x01000000
#define	M_T11		0x02000000
#define	M_RA		0x04000000
#define	M_T12		0x08000000
#define	M_AT		0x10000000
#define M_GP		0x20000000
#define	M_SP		0x40000000
#define	M_EXCFRM	0x80000000
