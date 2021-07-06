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

#ifndef _MACHINE_COREREGS_H_
#define _MACHINE_COREREGS_H_

#include <sys/types.h>
#include <machine/alpha_ptrace.h>	/* defines NFP_REGS */

/*
 * Layout of general purpose and floating point registers in core files
 */

#define CF_V0	0		/* r0: return address	*/
#define CF_T0	1		/* r1: caller saved 0	*/
#define CF_T1	2		/* r2: caller saved 1	*/
#define CF_T2	3		/* r3: caller saved 2	*/
#define CF_T3	4		/* r4: caller saved 3	*/
#define CF_T4	5		/* r5: caller saved 4	*/
#define CF_T5	6		/* r6: caller saved 5	*/
#define CF_T6	7		/* r7: caller saved 6	*/
#define CF_T7	8		/* r8: caller saved 7	*/
#define CF_S0	9		/* r9: callee saved 0	*/
#define CF_S1	10		/* r10: callee saved 1	*/
#define CF_S2	11		/* r11: callee saved 2	*/
#define CF_S3	12		/* r12: callee saved 3	*/
#define CF_S4	13		/* r13: callee saved 4	*/
#define CF_S5	14		/* r14: callee saved 5	*/
#define CF_S6	15		/* r15:	callee saved 6	*/
#define CF_A3	16		/* r19: argument 3	*/
#define CF_A4	17		/* r20: argument 4	*/
#define CF_A5	18		/* r21: argument 5	*/
#define CF_T8	19		/* r22: caller saved 8	*/
#define CF_T9	20		/* r23: caller saved 9	*/
#define CF_T10	21		/* r24: caller saved 10	*/
#define CF_T11	22		/* r25: caller saved 11	*/
#define CF_RA	23		/* r26: return address	*/
#define CF_T12	24		/* r27: caller saved 12	*/
#define CF_AT	25		/* r28: assembler temp	*/
#define CF_SP	26		/* r30: stack pointer	*/
#define CF_PS	27		/* processor status 	*/
#define CF_PC	28		/* program counter	*/
#define CF_GP	29		/* r29: global pointer	*/
#define CF_A0	30		/* r16: argument 0	*/
#define CF_A1	31		/* r17: argument 1	*/
#define CF_A2	32		/* r18: argument 2	*/

#define NCF_REGS 33	/* number of exception frame registers in core file */

struct core_regs {
	ulong_t ef_regs[NCF_REGS];	/* exception frame regs */
	ulong_t fp_regs[NFP_REGS];	/* floating point regs */
	ulong_t fp_fpcr;		/* fp control reg */
};

#endif /* _MACHINE_COREREGS_H_ */
