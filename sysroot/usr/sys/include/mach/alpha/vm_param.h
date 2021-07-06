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
 * @(#)$RCSfile: vm_param.h,v $ $Revision: 1.2.13.2 $ (DEC) $Date: 2000/04/06 14:43:06 $
 */

/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */

/*
 *	File:	alpha/vm_param.h
 *
 *	Alpha machine-dependent virtual memory parameters.
 *	Most declarations are preceeded by ALPHA_ (or alpha_)
 *	because only Alpha specific code should be using
 *	them.
 *
 */

#ifndef	_MACH_ALPHA_VM_PARAM_H_
#define _MACH_ALPHA_VM_PARAM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define BYTE_SIZE	8	/* byte size in bits */

#define ALPHA_PGBYTES	8192	/* bytes per alpha page */
#define ALPHA_PGSHIFT	13	/* number of bits to shift for pages */

#define PAGE_SIZE_FIXED		/* enable constant page size definitions */
#define PAGE_SIZE	((vm_size_t)ALPHA_PGBYTES)
#define PAGE_MASK	((vm_size_t)ALPHA_PGBYTES - 1)
#define PAGE_SHIFT	(ALPHA_PGSHIFT)

/*
 *	Convert bytes to pages and convert pages to bytes.
 *	No rounding is used.
 */

#define alpha_btop(x)		(((unsigned long)(x)) >> ALPHA_PGSHIFT)
#define alpha_ptob(x)		(((unsigned long)(x)) << ALPHA_PGSHIFT)

/*
 *	Round off or truncate to the nearest page.  These will work
 *	for either addresses or counts.  (i.e. 1 byte rounds to 1 page
 *	bytes.
 */

#define alpha_round_page(x)	((((unsigned long)(x)) + ALPHA_PGBYTES - 1) & \
					~(ALPHA_PGBYTES-1))
#define alpha_trunc_page(x)	(((unsigned long)(x)) & ~(ALPHA_PGBYTES-1))

/*
 * User level addressability
 */
#define VM_MIN_ADDRESS	((vm_offset_t)0x10000)
#define VM_MAX_ADDRESS	((vm_offset_t)(~UNITY_BASE + 1))

/*
 * These are the bounds of the kernel heap.
 */

#define VM_MIN_KERNEL_ADDRESS	vm_min_kernel_address
#define VM_MAX_KERNEL_ADDRESS	vm_max_kernel_address

#define KERNEL_STACK_SIZE			(4*ALPHA_PGBYTES)

#ifndef ASSEMBLER
#ifdef _KERNEL

extern unsigned long vm_min_kernel_address;
extern unsigned long vm_max_kernel_address;
extern long real_kernelstack_size;

/* prototype & #pragma intrinsic for asm() moved to arch/alpha/kintrinsics.h */

#define get_current_sp() \
	((struct stack_layout *)asm("bis %sp,%sp,%v0"))
#define get_sp() \
	((struct stack_layout *)asm("bic %sp,%a0,%v0", KERNEL_STACK_SIZE - 1))

#endif /* _KERNEL */
#endif /* ASSEMBLER */

/*
 *	Conversion between ALPHA pages and VM pages
 */

#define trunc_alpha_to_vm(p)	(atop(trunc_page(alpha_ptob(p))))
#define round_alpha_to_vm(p)	(atop(round_page(alpha_ptob(p))))
#define vm_to_alpha(p)		(alpha_btop(ptoa(p)))

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _MACH_ALPHA_VM_PARAM_H_ */
