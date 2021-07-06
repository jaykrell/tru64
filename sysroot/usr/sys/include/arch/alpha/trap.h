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
 * @(#)$RCSfile: trap.h,v $ $Revision: 1.2.12.1 $ (DEC) $Date: 1999/11/03 22:41:45 $
 */

#ifndef _MACHINE_TRAP_H_
#define _MACHINE_TRAP_H_

#ifdef __cplusplus
extern "C" {
#endif

#define USERFAULT	0x1		/* flag to note user/kernel	*/
#define T_ARITH		0x10		/* Arithmentic			*/
#define T_MMANG		0x20		/* memory management faults	*/
#define T_ALIGN		0x30		/* unaligned access faults	*/
#define T_IFAULT	0x40		/* Instruction faults		*/
#define T_AST		0x50		/* Asynchronous System Trap	*/

#define T_IFAULT_BPT	0		/* Break point trap		*/
#define T_IFAULT_BUGCK	1		/* Bug Check			*/
#define T_IFAULT_GENT	2		/* Gen trap			*/
#define T_IFAULT_FEN	3		/* Floating point enable	*/
#define T_IFAULT_OPDEC	4		/* Opcode reserved to DEC	*/
#define T_IFAULT_ILLOP	5		/* illegal operand		*/

#define T_MMANG_TNV	0		/* Translation not valid	*/
#define T_MMANG_ACV	1		/* Access Violation		*/
#define T_MMANG_FOR	2		/* Fault on Read		*/
#define T_MMANG_FOE	3		/* Fault on Execute		*/
#define T_MMANG_FOW	4		/* Fault on Write		*/

/*
 * Flags for the nofault handler.  0 means no fault is expected.
 */
#define NF_BADADDR		1	/* badaddr, wbadaddr */
#define NF_COPYIO		2	/* copyin, copyout */
#define NF_ADDUPC		3	/* addupc */
#define NF_FSUMEM		4	/* fubyte, subyte, fuword, suword */
#define NF_USERACC		5	/* useracc */
#define NF_SOFTFP		6	/* softfp */
#define NF_REVID		7	/* revision ids */
#define NF_COPYSTR		8	/* copyinstr, copyoutstr */
#define NF_SOFTFPI		9	/* fp instr fetch */
#define NF_SIGRETURN_COPYIN	10	/* copyin errors for sigreturn */
#define NF_SENDSIG_COPYOUT	11	/* copy out errors for sendsig */
#define NF_LWERR		12	/* faults in pmap_lw_wire */
#define NF_LW_UNERR		13	/* faults in pmap_lw_unwire */
#define NF_LW_UNERR_ASS		14	/* faults in pmap_lw_unwire */
#define NF_LWERR_ASS		15
#define NF_PTEFETCH		16	/* pmap_fault_on() */
#define NF_LW_UNERR_OTHER_MAP	17	/* faults in pmap_lw_unwire_other_map */
#define NF_COPYIO_TRY		18	/* copyin_try */
#define NF_DART			19	/* DART hook */
#define NF_NXM_UPCALL		20	/* used by nxm_upcall */
#define NF_NEW_LW_ERR		21
#define NF_NEW_LW_UN_ERR	22
#define NF_REMOVE_WIRED_FAST	23
#define NF_NENTRIES		24

#ifdef __cplusplus
}
#endif

#endif /* _MACHINE_TRAP_H_ */
