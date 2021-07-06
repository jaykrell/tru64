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
 * @(#)$RCSfile: pmap_lw.h,v $ $Revision: 1.1.38.1 $ (DEC) $Date: 2001/11/16 16:23:45 $
 */

#ifndef _PMAP_LW_H_
#define _PMAP_LW_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>
#include <machine/pmap.h>

#define	LWW_MASK 0x20000L
#define VALID_MASK 0x1L
#define SEG_MASK 0x40000L
#define VM_FULL_WIRE 0x8000000000000000

extern void lw_init __((void));

#ifdef _KERNEL
struct	pmap;
union	pt_entry;

extern int
	pmap_lw_wire(struct pmap *, vm_offset_t, int, u_long *, u_long),
	pmap_lw_unwire(struct pmap *, vm_offset_t, int),
	pmap_lw_unwire_helper(union pt_entry *, union pt_entry *),
	setup_nf_lw_wire_new(void),
	setup_nf_lw_unwire_new(void),
	pmap_lw_check_modify(void),
	pmap_lw_wire_ass(vm_offset_t, int, vm_offset_t),
	pmap_lw_unwire_ass(struct thread *);

extern vm_offset_t
	pmap_remove_wired_fast(struct pmap *, vm_offset_t, vm_offset_t);

extern boolean_t
	pmap_lw_unwire_new(struct pmap *, vm_offset_t, long, u_long *,
			boolean_t);

extern long
	pmap_lw_wire_new(pmap_t, vm_offset_t, long, int *, vm_prot_t),
	pmap_gh_lw_wire(pmap_t, vm_offset_t, long, vm_fault_t);

extern void
	pmap_get_pfns(struct pmap *, vm_offset_t, int, u_long *),
	pmap_lw_clear_modify(void),
	pmap_lw_set_modify(void),
	pmap_lw_dec(struct pmap *),
	pmap_lw_inc(struct pmap *);

extern kern_return_t
	pmap_lw_unwire_other_map(struct pmap *, vm_offset_t, int);

extern unsigned long
	pmap_get_lw_trans(struct pmap *);
#endif

#ifdef __cplusplus
}
#endif
#endif /* _PMAP_LW_H_ */
