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
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */

/*
 *	File:	alpha/thread_status.h
 *
 *	This file contains the structure definitions for the thread
 *	state as applied to alpha processors.
 *
 */

#ifndef _MACH_ALPHA_THREAD_STATE_H_
#define _MACH_ALPHA_THREAD_STATE_H_

#ifndef __LANGUAGE_ASSEMBLY__

/*
 *	Two basic structures are defined:
 *
 *	alpha_thread_state	this is the structure that is exported
 *				to user threads for use in status/mutate
 *				calls.  This structure should never
 *				change.
 *
 *	alpha_saved_state	this structure corresponds to the state
 *				of the user registers as saved on the
 *				stack upon kernel entry.  This structure
 *				has unfortunately been exported as part
 *				of the nxm_upcall structure, and thus
 *				it must be not changed in the future.
 *
 *	Other definitions (flavors) cover alternate register sets as
 *	needed.  For instance, for the FP coprocessor.
 */

#define ALPHA_THREAD_STATE	(1)
#define ALPHA_FLOAT_STATE	(2)

struct alpha_thread_state {
	long	r0;		/* v0	return value		*/
	long	r1;		/* t0	callee saved 0		*/
	long	r2;		/* t1	callee saved 1		*/
	long	r3;		/* t2	callee saved 2		*/
	long	r4;		/* t3	callee saved 3		*/
	long	r5;		/* t4	callee saved 4		*/
	long	r6;		/* t5	callee saved 5		*/
	long	r7;		/* t6	callee saved 6		*/
	long	r8;		/* t7	callee saved 7		*/
	long	r9;		/* s0	caller saved 0		*/
	long	r10;		/* s1	caller saved 1		*/
	long	r11;		/* s2	caller saved 2		*/
	long	r12;		/* s3	caller saved 3		*/
	long	r13;		/* s4	caller saved 4		*/
	long	r14;		/* s5	caller saved 5		*/
	long	r15;		/* s6/fp caller saved 6		*/
	long	r16;		/* a0	argument register 0	*/
	long	r17;		/* a1	argument register 1	*/
	long	r18;		/* a2	argument register 2	*/
	long	r19;		/* a3	argument register 3	*/
	long	r20;		/* a4	argument register 4	*/
	long	r21;		/* a5	argument register 5	*/
	long	r22;		/* t8	callee saved 8		*/
	long	r23;		/* t9	callee saved 9		*/
	long	r24;		/* t10	callee saved 10		*/
	long	r25;		/* t11	callee saved 11		*/
	long	r26;		/* ra	return address		*/
	long	r27;		/* t12	callee saved 12		*/
	long	r28;		/* at	assembler temp		*/
	long	r29;		/* gp	global pointer		*/
	long	r30;		/* sp	stack pointer		*/
	long	pc;		/* user-mode PC			*/
	long	ps;		/* processor status		*/
};

#define ALPHA_THREAD_STATE_COUNT \
		(sizeof(struct alpha_thread_state) / sizeof(long))


struct alpha_float_state {
	long	r0;		/* general floating point registers */
	long	r1;
	long	r2;
	long	r3;
	long	r4;
	long	r5;
	long	r6;
	long	r7;
	long	r8;
	long	r9;
	long	r10;
	long	r11;
	long	r12;
	long	r13;
	long	r14;
	long	r15;
	long	r16;
	long	r17;
	long	r18;
	long	r19;
	long	r20;
	long	r21;
	long	r22;
	long	r23;
	long	r24;
	long	r25;
	long	r26;
	long	r27;
	long	r28;
	long	r29;
	long	r30;
	long	r31;
};

#define ALPHA_FLOAT_STATE_COUNT \
		(sizeof(struct alpha_float_state) / sizeof(long))

/*
 *  BEWARE this layout.  The reason for this is two-fold:
 *
 *  1) alpha has a hardware-generated exception frame which
 *  means the order of saved registers is not the same as
 *  the numeric order.
 *
 *  2) pcb.c actually references some stuff using fields defined
 *  here.  The most troublesome one is in thread_dup(), which makes
 *  certain assumptions about the contents of "r2", "r3", and "r7".
 */
struct alpha_saved_state {
	long	r0;		/* v0	return value		*/
	long	r1;		/* t0	callee saved 0		*/
	long	r2;		/* t1	callee saved 1		*/
	long	r3;		/* t2	callee saved 2		*/
	long	r4;		/* t3	callee saved 3		*/
	long	r5;		/* t4	callee saved 4		*/
	long	r6;		/* t5	callee saved 5		*/
	long	r7;		/* t6	callee saved 6		*/
	long	r8;		/* t7	callee saved 7		*/
	long	r9;		/* s0	caller saved 0		*/
	long	r10;		/* s1	caller saved 1		*/
	long	r11;		/* s2	caller saved 2		*/
	long	r12;		/* s3	caller saved 3		*/
	long	r13;		/* s4	caller saved 4		*/
	long	r14;		/* s5	caller saved 5		*/
	long	r15;		/* s6/fp caller saved 6		*/
	long	r19;		/* a3	argument register 3	*/
	long	r20;		/* a4	argument register 4	*/
	long	r21;		/* a5	argument register 5	*/
	long	r22;		/* t8	callee saved 8		*/
	long	r23;		/* t9	callee saved 9		*/
	long	r24;		/* t10	callee saved 10		*/
	long	r25;		/* t11	callee saved 11		*/
	long	r26;		/* ra	return address		*/
	long	r27;		/* t12	callee saved 12		*/
	long	r28;		/* at	assembler temp		*/
	long	r30;		/* sp	stack pointer		*/
	long	ps;		/* processor status		*/
	long	pc;		/* user-mode PC			*/
	long	r29;		/* gp	global pointer		*/
	long	r16;		/* a0	argument register 0	*/
	long	r17;		/* a1	argument register 1	*/
	long	r18;		/* a2	argument register 2	*/
};

/*
 * The following interfaces allow access to user register values
 * saved in the initial exception frame upon entry into the kernel.
 * Note that the real exception frame format has been decoupled from
 * the alpha_saved_state structure due to the latter's inclusion in
 * the nxm_upcall structure (and hence its user space visibility).
 */
#ifdef _KERNEL
#ifdef _BASE_KERNEL_PRIVATE /* see sys/systm.h - kernel binary compatibility */
#define USER_REGS(th)	((long *)((char *)&(th)->stack->pcb - EF_SIZE))
#define USER_REG(rx)	(((long *)((char *)&get_sp()->pcb - EF_SIZE))[rx])
#else
struct thread;
extern long *user_regs_base(struct thread *);
extern long *user_reg_addr(int);
#define USER_REGS(th)	(user_regs_base(th))
#define USER_REG(rx)	(*user_reg_addr(rx))
#endif /* _BASE_KERNEL_PRIVATE */
#endif /* _KERNEL */

#endif /* __LANGUAGE_ASSEMBLY__ */

/*
 * The following definitions can be used to index into an array of
 * long's according to the register position within an alpha_saved_state
 * structure.  They can also be used (x*8) from within assembly language.
 *
 * (Note: the EF_* definitions in <machine/reg.h> have been changed.)
 */
#define SS_V0	0		/* r0: return address	*/
#define SS_T0	1		/* r1: caller saved 0	*/
#define SS_T1	2		/* r2: caller saved 1	*/
#define SS_T2	3		/* r3: caller saved 2	*/
#define SS_T3	4		/* r4: caller saved 3	*/
#define SS_T4	5		/* r5: caller saved 4	*/
#define SS_T5	6		/* r6: caller saved 5	*/
#define SS_T6	7		/* r7: caller saved 6	*/
#define SS_T7	8		/* r8: caller saved 7	*/
#define SS_S0	9		/* r9: callee saved 0	*/
#define SS_S1	10		/* r10: callee saved 1	*/
#define SS_S2	11		/* r11: callee saved 2	*/
#define SS_S3	12		/* r12: callee saved 3	*/
#define SS_S4	13		/* r13: callee saved 4	*/
#define SS_S5	14		/* r14: callee saved 5	*/
#define SS_S6	15		/* r15:	callee saved 6	*/
#define SS_A3	16		/* r19: argument 3	*/
#define SS_A4	17		/* r20: argument 4	*/
#define SS_A5	18		/* r21: argument 5	*/
#define SS_T8	19		/* r22: caller saved 8	*/
#define SS_T9	20		/* r23: caller saved 9	*/
#define SS_T10	21		/* r24: caller saved 10	*/
#define SS_T11	22		/* r25: caller saved 11	*/
#define SS_RA	23		/* r26: return address	*/
#define SS_T12	24		/* r27: caller saved 12	*/
#define SS_AT	25		/* r28: assembler temp	*/
#define SS_SP	26		/* r30: stack pointer	*/
#define SS_PS	27		/* processor status 	*/
#define SS_PC	28		/* program counter	*/
#define SS_GP	29		/* r29: global pointer	*/
#define SS_A0	30		/* r16: argument 0	*/
#define SS_A1	31		/* r17: argument 1	*/
#define SS_A2	32		/* r18: argument 2	*/
#define SS_SIZE	(33*8)	/* size in bytes of alpha_saved_state frame */

#endif /* _MACH_ALPHA_THREAD_STATE_H_ */
