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
 * @(#)$RCSfile: cpu.h,v $ $Revision: 1.2.82.4 $ (DEC) $Date: 2002/03/28 20:34:37 $
 */

#ifndef	_MACHINE_CPU_H_
#define	_MACHINE_CPU_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ASSEMBLER

typedef unsigned long cpumask_t; /* bit mask of cpus (NCPUS must be <= 64) */

#ifdef _KERNEL

#include <mach/alpha/vm_param.h>

/*
 * The GET_CALLER macro declares a local variable and assigns to it the
 * address of the instruction in the calling function which invoked the
 * current function.  It must be used at the very beginning of the body
 * of a function, specifically, before any code path could overwrite the
 * value in the return address register (by making a function call).
 */
#define GET_CALLER(caller) void *caller = (void *)asm("subq %ra,4,%v0")

/*
 * The PATCH_CALLER_xxxx(caller) macros overwrite the "bsr" in the calling
 * function with one of the Alpha instruction models in locore.s, taking
 * care of imb() and replicated text issues.  Note that the "caller" macro
 * argument should be declared/assigned with GET_CALLER(), and that any
 * function containing a PATCH_CALLER_xxxx() macro must never be invoked
 * indirectly though a function pointer ("jsr"), must never be in-lined,
 * and must never be directly branched to via a "tail call".
 */
#define PATCH_CALLER_NOOP(caller) write_instruction((caller), alpha_noop)
#define PATCH_CALLER_RET0(caller) write_instruction((caller), alpha_retval_0)
#define PATCH_CALLER_RET1(caller) write_instruction((caller), alpha_retval_1)
extern unsigned int alpha_noop, alpha_retval_0, alpha_retval_1;

#define cause_ast_check(cpu)	intrpt_cpu((cpu), IPI_SCHED)

extern void halt(void);
extern void cpu_shutdown(void);
extern void intrpt_cpu(int, int);
extern unsigned long alpha_io_bit(unsigned long);

#endif /* _KERNEL */

#endif /* !ASSEMBLER */

/*
 * IP interrupt bit numbers
 */
#define IPI_PANIC	0	/* panic */
#define IPI_KM_TLBSHOOT	1	/* kernel map TLB shootdown */
#define IPI_SCHED	2	/* cause resched */
#define IPI_PRINTF	3	/* printf from secondary */
#define IPI_HALT	4	/* halt secondary */
#define IPI_KDEBUG	5	/* kdebug breakpoint */
#define IPI_PFM		6	/* performance monitor request */
#define IPI_PCC		7	/* microsecond timing pcc synch */
#define IPI_UM_TLBSHOOT	8	/* User map TLB shootdown */
#define	IPI_HOLD	9	/* hold a cpu until released */
#define IPI_IMB		10	/* flush icache */
#define IPI_SIGNAL	11	/* remote signal */
#define IPI_MPFM	12	/* marvel_pfm request */
#define IPI_OCLA	13	/* EV7 OCLA management */

/* MCES Register bit defines per ECO's #45/#51 */
#define MCES_MCK 0x1	/* Clear machine check flag */
#define MCES_SCE 0x2	/* Clear system corrected error flag */
#define MCES_PCE 0x4	/* Clear processor correct error flag */
#define MCES_DPC 0x8	/* Disable processor corrected error reporting */
#define MCES_DSC 0x10	/* Disable system corrected error reporting */
#define MCES_DISABLE	(MCES_DPC|MCES_DSC)	/* Disable both PCE/SCE */

#ifdef __cplusplus
}
#endif

#endif /* _MACHINE_CPU_H_ */
