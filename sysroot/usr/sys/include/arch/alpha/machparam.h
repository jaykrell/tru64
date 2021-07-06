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
 * @(#)$RCSfile: machparam.h,v $ $Revision: 1.2.21.4 $ (DEC) $Date: 2000/01/31 20:33:37 $
 */

#ifndef _MACHINE_MACHPARAM_H_
#define _MACHINE_MACHPARAM_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef BYTE_ORDER
#ifndef ASSEMBLER
#include <machine/endian.h>
#endif
#endif

#include <machine/machlimits.h>

/*
 * Machine-dependent constants for alpha.
 */
#define	MACHINE		"alpha"

#define CLSIZELOG2	0
#define CLSIZE		(1<<CLSIZELOG2)

#define KVSTART_PFN	(-254L)
#define OTHER_PFN	(-255L)
#define SELF_PFN	(-256L)

#ifdef _KERNEL
#include <machine/pmap.h>
#else /* _KERNEL */
#ifndef _PMAP_MACHINE_
typedef long pt_entry_t;
#endif
#endif /* _KERNEL */

#if defined(__LANGUAGE_C__) || defined(__cplusplus)

/*
 * KERNEL_PARAMETERS is intended to be a general repository for
 * frequently accessed data.  The structure is at most 32 KB mapped at
 * 0xffff ffff ffff 8000.  Accesses to quadwords in this range require
 * a single instruction, "ldq/stq rx, offset(r31)".
 */

struct kernel_parameters {
	struct vm_parameters {
		long nbpg;
		long pgofset;
		long pgshift;
		long nvabits;
		unsigned long seg1_base;
		unsigned long unity_base;
		unsigned long address_mask;
	} vm;
};

#ifdef ALPHA_VARIABLE_PAGE_SIZE
/*
 * Presently, KERNEL_PARAMETERS is used only by the memory management
 * subsystem, and all the values are derived from the page size.
 * Until there is more than one Alpha page size, these values can be
 * computed at compiletime, and KERNEL_PARAMETERS doesn't exist.
 */

#define KERNEL_PARAMETERS ((struct kernel_parameters *)(-1L << 15))

#define NBPG		(KERNEL_PARAMETERS->vm.nbpg)
#define PGOFSET		(KERNEL_PARAMETERS->vm.pgofset)
#define PGSHIFT		(KERNEL_PARAMETERS->vm.pgshift)
#define NVABITS		(KERNEL_PARAMETERS->vm.nvabits)
#define SEG1_BASE	(KERNEL_PARAMETERS->vm.seg1_base)
#define UNITY_BASE	(KERNEL_PARAMETERS->vm.unity_base)
#define ADDRESS_MASK	(KERNEL_PARAMETERS->vm.address_mask)

/*
 * init_vm_parameters is invoked by pmap_bootstrap.  If
 * KERNEL_PARAMETERS is expanded to include data not dependent on page
 * size, and this happens before the appearance of variable size
 * pages, then this macro must move outside the scope of "#ifdef
 * ALPHA_VARIABLE_PAGE_SIZE..."
 */
#define init_vm_parameters(page_shift, ext_va_size, page_table) if (1) {       \
	long _PGSHIFT = (page_shift);					       \
	long _NBPG = 1L << _PGSHIFT;					       \
	long _PGOFSET = _NBPG - 1;					       \
	long _NVABITS = 4 * _PGSHIFT - 9 + (ext_va_size);		       \
	long _INTRA_PAGE_OFFSET = (long)KERNEL_PARAMETERS & _PGOFSET;	       \
	struct kernel_parameters *_PARAM;				       \
									       \
	_PARAM = (struct kernel_parameters *)				       \
		    (map_bootspace(NEXT_VA(), next_pfn(), PROT_KW)	       \
		     + _INTRA_PAGE_OFFSET /* non-zero for 64KB pages */ );     \
	bzero((char*)_PARAM - _INTRA_PAGE_OFFSET, _NBPG);		       \
	(page_table)[level3_vpn(KERNEL_PARAMETERS)] = *BOOT_vtopte(_PARAM);    \
	_PARAM->vm.nbpg = _NBPG;					       \
	_PARAM->vm.pgofset = _PGOFSET;					       \
	_PARAM->vm.pgshift = _PGSHIFT;					       \
	_PARAM->vm.nvabits = _NVABITS;					       \
	_PARAM->vm.seg1_base = (unsigned long)(-1L << (_NVABITS - 2));	       \
	_PARAM->vm.unity_base = (unsigned long)(-2L << (_NVABITS - 2));	       \
	_PARAM->vm.address_mask = (unsigned long)((1L << _NVABITS) - 1L);      \
} else

#else /* !ALPHA_VARIABLE_PAGE_SIZE, i.e. 8KB PAGES */

#define KERNEL_PARAMETERS ((vm_offset_t)0) /* used to catch HWRPB overrun */

#define PGSHIFT		13
#define NBPG		(1L<<PGSHIFT)
#define PGOFSET		(NBPG - 1)
#define NVABITS		(4 * PGSHIFT - 9)
#define SEG1_BASE	((unsigned long)(-1L << (NVABITS - 2)))
#define UNITY_BASE	((unsigned long)(-2L << (NVABITS - 2)))
#define ADDRESS_MASK	((unsigned long)((1L << NVABITS) - 1L))
#define Kernel_virtual_start_32bit_console ((vm_offset_t)0xffffffff80000000UL)
#define Kernel_virtual_start ((vm_offset_t)(KVSTART_PFN << (3 * PGSHIFT - 6)))

#define init_vm_parameters(page_shift, ext_va_size, page_table)

#endif /* ALPHA_VARIABLE_PAGE_SIZE */

#ifdef _KERNEL

#define DELAY(n)	microdelay(n)
#define SYNCDELAY(n,x)	alpha_delay(n, (int)(x))

#ifdef _USE_KERNEL_PROTOS

extern void draina(void);
extern void microdelay(int microseconds);
extern void alpha_delay(int microseconds, int data_dependency);
extern long alpha_timer(u_long delay, u_long base);

/*
 * Macros replaced by functions (in pal_lib.s).
 */
extern int is_seg0_va(unsigned long va);
extern int is_sys_va(unsigned long va);
extern int is_kseg_va(unsigned long va);
extern int is_seg1_va(unsigned long va);

#else

extern int is_seg0_va();
extern int is_sys_va();
extern int is_kseg_va();
extern int is_seg1_va();

#endif /* _USE_KERNEL_PROTOS */

#define IS_SEG0_VA(va)	is_seg0_va(va)
#define IS_SYS_VA(va)	is_sys_va(va)
#define IS_KSEG_VA(va)	is_kseg_va(va)
#define IS_SEG1_VA(va)	is_seg1_va(va)

#else

#define IS_SEG0_VA(x)	(((long)(x) >> (NVABITS - 1)) == 0L)
#define IS_SYS_VA(x)	(((long)(x) >> (NVABITS - 1)) == -1L)
#define IS_KSEG_VA(x)	(((long)(x) >> (NVABITS - 2)) == -2L)
#define IS_SEG1_VA(x)	(((long)(x) >> (NVABITS - 2)) == -1L)

#endif /* _KERNEL */

#endif /* __LANGUAGE_C__ || __cplusplus */

#define	SSIZE		CLSIZE		/* initial stack size/NBPG */
#define	SINCR		CLSIZE		/* increment of stack/NBPG */

#define UPAGECNT	CLSIZE		/* u-area size in pages */
#define KSTKPGS		CLSIZE		/* kernel stack size in pages */
#define	UPAGES		(UPAGECNT+KSTKPGS)

#define	KERNELSTACK	0xffffffffffff8000UL /* top of kernel boot stack */

/*
 * Some macros for units conversion
 */
/* Core clicks to segments and vice versa */
#define	ctos(x)	(x)
#define	stoc(x)	(x)

/* Core clicks to disk blocks */
#define	DBSHIFT		9		/* LOG2(Disk block size) */
#define	ctod(x)	((x)<<(PGSHIFT-DBSHIFT))
#define	dtoc(x)	((unsigned)(x)>>(PGSHIFT-DBSHIFT))
#define	dtob(x)	((x)<<DBSHIFT)

/* clicks to bytes */
#define	ctob(x)	((x)<<PGSHIFT)

/* bytes to clicks */
#define	btoc(x)	(((unsigned long)(x)+PGOFSET)>>PGSHIFT)

/*
 * Macros to decode processor status word.
 */
#define	USERMODE(ps)	(((ps) & PSL_CURMOD) == PSL_CURMOD)
#define	BASEPRI(ps)	(((ps) & PSL_IPL) == PSL_IPL_LOW)

#ifdef __cplusplus
}
#endif

#endif /* _MACHINE_MACHPARAM_H_ */
