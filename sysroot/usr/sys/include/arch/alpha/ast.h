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
 * @(#)$RCSfile: ast.h,v $ $Revision: 1.1.10.1 $ (DEC) $Date: 2000/01/27 20:16:21 $
 */

#ifndef _MACHINE_AST_H_
#define _MACHINE_AST_H_

#ifdef __cplusplus
extern "C" {
#endif

#define AST_SCHED_KERNEL	0x40
#define AST_SCHED_USER		0x80

#ifdef _KERNEL
#ifndef ASSEMBLER

#include <rt_preempt.h>
#include <machine/pcb.h>

#ifndef REPLICATED
#define REPLICATED
#endif

extern REPLICATED int rt_preempt_enabled;

#define ast_context(thread, cpu) \
	thread_pcb(thread)->pcb_ast.flags.need_ast = (thread)->ast

#define ast_propagate(thread, cpu) \
	get_sp()->pcb.pcb_ast.flags.need_ast |= (thread)->ast

#define ast_needed(cpu) \
	(get_sp()->pcb.pcb_ast.flags.need_ast)

#define sched_kernel_astoff() \
	get_sp()->pcb.pcb_ast.flags.need_ast &= ~AST_SCHED_KERNEL

#define sched_aston() \
	get_sp()->pcb.pcb_ast.flags.need_ast |= \
		(rt_preempt_enabled ? \
			(AST_SCHED_USER | AST_SCHED_KERNEL) : AST_SCHED_USER)

#define aston() \
	get_sp()->pcb.pcb_ast.flags.need_ast |= 1

#define sched_kernel_ast_needed() \
	(get_sp()->pcb.pcb_ast.flags.need_ast & AST_SCHED_KERNEL)

#define sched_ast_needed() \
	(get_sp()->pcb.pcb_ast.flags.need_ast & \
					(AST_SCHED_KERNEL | AST_SCHED_USER))

#define astoff() \
	get_sp()->pcb.pcb_ast.flags.need_ast = 0

#endif /* ASSEMBLER */
#endif /* _KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* _MACHINE_AST_H_ */
