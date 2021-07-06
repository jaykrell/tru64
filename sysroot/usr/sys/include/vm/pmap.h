/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: pmap.h,v $
 * Revision 4.3.72.3  2003/09/22  20:22:28  Ross_Knepper
 * 	Add prototypes for l3gh.
 *
 * Revision 4.3.72.2  2003/03/05  19:08:41  Ross_Knepper
 * 	Make pmap_remove_lev2() return int.
 *
 * Revision 4.3.72.1  2002/10/16  15:15:16  David_Bernardo
 * 	Add prototype for pmap_move_all.
 *
 * Revision 4.3.54.11  2002/05/24  16:37:20  David_Bernardo
 * 	Add prototype for pmap_is_mine_lw_wired.
 *
 * Revision 4.3.54.10  2002/05/10  17:48:23  Anton_Verhulst
 * 	Remove unused PAG argument from pmap_fix().
 *
 * Revision 4.3.54.9  2002/03/27  15:22:32  David_Bernardo
 * 	Added prototype for pmap_get_page_size.
 *
 * Revision 4.3.54.8  2002/03/26  01:32:21  Renny_Shen
 * 	Changed parameter for pmap_valid_page(). Added
 * 	pmap_sh_regions() macro to return the number of
 * 	shared memory regions in a RAD.
 *
 * Revision 4.3.54.7  2002/02/14  20:55:05  Julie_Dewandel
 * 	Removed parameter from pmap_ssm_invalidate prototype
 *
 * Revision 4.3.54.6  2002/02/11  23:23:24  David_Bernardo
 * 	Add prototype for pmap_check_fp_waiters.
 * 	Add prototype for pmap_release_fp_waiters.
 * 	Removed prototype for unused pmap_ssm_protect_bigpage.
 *
 * Revision 4.3.54.5  2002/01/28  21:17:45  Matthew_McGrath
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree wcalphaos
 *     User Revision:  Matthew_McGrath_QAR91432_br:4.3.60.1 Local Ancestor:4.3.54.3
 *    Merge Revision:  wcalphaos_br:4.3.54.4
 *   Common Ancestor:  4.3.54.3
 *
 * Revision 4.3.54.4  2002/01/25  22:02:14  Ross_Knepper
 * 	add pmap_wire.
 * 
 * Revision 4.3.60.1  2002/01/24  14:22:15  Matthew_McGrath
 * 	Added a pair of defines for use in masking the flags out of the flags
 * 	field added to pmap_enter/pmap_enter_bigpage.  [QAR 91432]
 * 
 * Revision 4.3.54.3  2001/11/16  20:15:09  Ross_Knepper
 * 	Add prototypes for pmap_protect_bigpage, pmap_ssm_protect_bigpage,
 * 	pmap_ssm_invalidate.
 * 
 * Revision 4.3.54.2  2001/11/01  22:40:40  Ross_Knepper
 * 	Big pages infrastructure
 * 
 * Revision 4.3.56.1  2001/10/19  15:12:58  David_Bernardo
 * 	Add new bigpage related prototypes.
 * 
 * Revision 4.3.54.1  2001/10/03  17:44:17  David_Bernardo
 * 	Changed function prototype for pmap_pvh_init.
 * 	Fixed compiler warning.
 * 
 * Revision 4.3.45.3  2001/02/08  14:59:27  Julie_Dewandel
 * 	Added function prototype for pmap_remove_wired and
 * 	pmap_remove_not_wired
 * 
 * Revision 4.3.45.2  2000/11/03  16:10:49  Greg_Bellows
 * 	Change pmap_mark_page_bad prototype to include a return status
 * 	of kern_return_t.
 * 
 * Revision 4.3.45.1  2000/10/18  21:04:08  Ernie_Petrides
 * 	Add prototype for vtop().
 * 
 * Revision 4.3.25.14  2000/03/16  23:02:48  Shashi_Mangalat
 * 	Changes to support vm_page/pvh merge.
 * 
 * Revision 4.3.25.13  2000/02/07  20:01:37  Stephen_Corbin
 * 	Add pmap_ssm_mapped prototype.
 * 
 * Revision 4.3.25.12  2000/01/31  20:34:08  David_Bernardo
 * 	Add pmap_start_cpt prototype.
 * 
 * Revision 4.3.25.11  1999/12/22  21:58:39  Shashi_Mangalat
 * 	Add pmap_map_io() prototype.
 * 
 * Revision 4.3.25.10  1999/12/15  20:09:48  Shashi_Mangalat
 * 	Add pmap_seg_migrate() and pmap_seg_mapped() prototypes.
 * 
 * Revision 4.3.25.9  1999/11/18  23:15:19  Shashi_Mangalat
 * 	Fix previous merge.
 * 
 * Revision 4.3.25.8  1999/11/17  22:07:31  Stephen_Corbin
 * 	Merge from zincos_bl2:
 * 	Update pmap_is_lw_wired() proto.
 * 	Add pmap_seg_remove() prototype.
 * 
 * Revision 4.3.25.7  1999/10/08  16:08:42  Shashi_Mangalat
 * 	Merge from ZINCOS_BL1:
 * 	rev 4.3.41.2  1999/08/16  20:07:40  Shashi_Mangalat
 * 	. Add flags argument to pmap_valloc() and define PV_NOZERO.
 * 
 * Revision 4.3.25.6  1999/08/05  20:46:56  Shashi_Mangalat
 * 	Remove include of thread.h.
 * 	[1999/08/04  13:16:08  Shashi_Mangalat]
 * 
 * Revision 4.3.25.5  1999/05/06  19:35:21  Shashi_Mangalat
 * 	Merge of STEELOS_BL21:STEELOS_BL23
 * 	 Revision 4.3.19.8  1999/02/09  19:04:01  Ken_Block
 * 	 Make header C++ compliant.
 * 	 Revision 4.3.19.7  1999/02/02  19:48:19  Shashi_Mangalat
 * 	 Remove extraneous semicolons.
 * 	 Add pmap_secondary_cache_size() prototype.
 * 	[1999/05/06  19:29:47  Shashi_Mangalat]
 * 
 * Revision 4.3.25.4  1999/03/09  23:49:36  Shashi_Mangalat
 * 	Merge of STEELOS_BL20:STEELOS_BL21
 * 	 Revision 4.3.19.6  1998/12/04  21:53:41  Shashi_Mangalat
 * 	 Change pmap_mad_size() proto to match new definition.
 * 	 Revision 4.3.19.5  1998/12/01  20:07:24  James_Woodward
 * 	 add system_memory_synch_point and task_memory_synch_point prototype.
 * 	 Revision 4.3.19.4  1998/11/25  23:34:44  Shashi_Mangalat
 * 	 Add pmap_ssm_protect() prototype.
 * 	 VM/NUMA scalability enhancements.
 * 	[1999/03/09  23:44:34  Shashi_Mangalat]
 * 
 * Revision 4.3.25.3  1998/12/08  00:56:57  Shashi_Mangalat
 * 	Steel bl20 merge:
 * 	Add pmap_set_tested() and pmap_highest_free() protos.
 * 	[1998/12/08  00:54:37  Shashi_Mangalat]
 * 
 * Revision 4.3.25.2  1998/08/26  12:42:49  James_Woodward
 * 	Merge of numaproj and zulu
 * 	[1998/07/29  20:18:03  James_Woodward]
 * 
 * Revision 4.3.22.4  1998/05/18  21:21:26  Shashi_Mangalat
 * 	Move some prototypes here from vm_exproto.h.
 * 	[1998/05/18  20:40:53  Shashi_Mangalat]
 * 
 * Revision 4.3.22.3  1998/05/13  19:42:27  James_Woodward
 * 	add support for multiple lvl1 to pmap
 * 	[1998/05/13  12:04:40  James_Woodward]
 * 
 * Revision 4.3.22.2  1998/04/09  21:13:59  Shashi_Mangalat
 * 	Add pmap_ssm_protect() prototype.
 * 	[1998/04/09  19:36:37  Shashi_Mangalat]
 * 
 * Revision 4.3.19.3  1998/02/24  19:59:58  David_Anderson
 * 	Added pmap_in_pal_cluster() prototype.
 * 	[1998/02/23  18:24:42  David_Anderson]
 * 
 * Revision 4.3.19.2  1996/08/14  21:07:35  Jeff_Colburn
 * 	Function prototype cleanup
 * 	[1996/08/14  20:34:26  Jeff_Colburn]
 * 	Function prototype cleanup
 * 	[1996/08/13  16:29:08  Jeff_Colburn]
 * 
 * Revision 4.3.17.2  1995/12/15  16:30:44  Ashoke_Rampuria
 * 	Changed return type for pmap_copy_on_write.
 * 	[1995/12/14  23:24:42  Ashoke_Rampuria]
 * 
 * Revision 4.3.10.3  1993/10/07  15:47:52  Shashi_Mangalat
 * 	Merge of Sterling BL6 changes.
 * 	 Merged light-weight wiring changes.
 * 	 [1993/09/03  15:50:24  Ashoke_Rampuria]
 * 	[1993/10/07  15:06:58  Shashi_Mangalat]
 * 
 * Revision 4.3.10.2  1993/04/28  23:57:55  Paula_Long
 * 	submitting the SMP project
 * 	[1993/04/28  18:42:36  Paula_Long]
 * 
 * Revision 4.3.8.3  1993/04/13  20:37:56  Joe_Martin
 * 	change the test of PMAP_SEGMENTATION
 * 	[1993/04/13  20:29:55  Joe_Martin]
 * 
 * Revision 4.3.8.2  1993/03/26  12:02:16  James_Woodward
 * 	Merge of MP and RT kernels.
 * 	[1993/03/18  18:46:46  James_Woodward]
 * 
 * Revision 4.3.4.3  1992/07/08  16:37:27  Joe_Martin
 * 	merged in Silver BL8_2
 * 	Revision 4.2.2.3  92/06/19  11:01:42  Robert_Picco
 * 	Segmentation code
 * 	[92/06/18  21:07:51  Robert_Picco]
 * 
 * Revision 4.3.4.2  92/03/20  13:56:36  Joe_Martin
 * 	merged in Silver BL5
 * 	Revision 4.2.2.2  92/02/26  15:52:45  Charles_Briggs
 * 	UBC merge
 * 	[92/02/23  14:32:30  Charles_Briggs]
 * 	UBC merge.
 * 	[92/02/23  09:53:33  Charles_Briggs]
 * 
 * Revision 4.3  92/01/15  02:15:01  devbld_gsf
 * 	Baselevel alpha_bl002
 * 
 * Revision 4.2.2.2  91/12/09  13:13:59  Joe_Martin
 * 	merged tin-based Alpha vers
 * 	[91/12/09  13:13:15  Joe_Martin]
 * 
 * Revision 4.2  91/09/19  23:07:18  devbld
 * 	Adding ODE Headers
 * 
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: pmap.h,v $ $Revision: 4.3.72.3 $ (DEC) $Date: 2003/09/22 20:22:28 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
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
 *	File:	vm/pmap.h
 *	Author:	Avadis Tevanian, Jr.
 *
 *	Copyright (C) 1985, Avadis Tevanian, Jr.
 *
 *	Machine address mapping definitions -- machine-independent
 *	section.  [For machine-dependent section, see "machine/pmap.h".]
 *
 *	Revision History:
 *
 * 8-Apr-91	Ron Widyono
 *	Delay inclusion of sys/preempt.h (for RT_PREEMPT) to avoid circular
 *	include file problem.
 *
 */

#ifndef	_VM_PMAP_H_
#define _VM_PMAP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <mach/machine/vm_types.h>
#include <mach/boolean.h>
#include <mach/kern_return.h>
#include <mach/vm_prot.h>

#define	PV_NOZERO	1	/* for pmap_valloc(); don't zero memory */

/*
 * for pmap_enter
 */

#define WIRE_FLAG	0x1L
#define DEVMAP_FLAG	0x2L

/*
 *	The following is a description of the interface to the
 *	machine-dependent "physical map" data structure.  The module
 *	must provide a "pmap_t" data type that represents the
 *	set of valid virtual-to-physical addresses for one user
 *	address space.  [The kernel address space is represented
 *	by a distinguished "pmap_t".]  The routines described manage
 *	this type, install and update virtual-to-physical mappings,
 *	and perform operations on physical addresses common to
 *	many address spaces.
 */

struct thread;
struct processor_affinity_group;
struct vm_map;
struct pmap;
struct pmap_ssm;
struct pmr_info;
struct vm_page;
struct memory_affinity_domain;
union pt_entry;
typedef	unsigned int vm_tbop_t;

/*
 *	Routines used for initialization.
 */

extern void		pmap_init(void);	/* Initialization,
						 * after kernel runs
						 * in virtual memory.
						 */
extern vm_offset_t	pmap_map(vm_offset_t, vm_offset_t, vm_offset_t, int);
						/* Enter a range of
						 * mappings.
						 */

extern void	pmap_seg_init(vm_offset_t *, vm_offset_t *,
				vm_size_t *, vm_offset_t *);

extern void	pmap_start_cpt(void);

/*
 *	Routines to manage the physical map data structure.
 */
extern struct pmap	*pmap_create(vm_size_t,		 /* Create a pmap_t. */
				struct processor_affinity_group *);	
#ifndef	pmap_kernel
extern struct pmap	*pmap_kernel();		/* Return the kernel's pmap_t */
#endif	/* pmap_kernel */
extern void		pmap_reference(struct pmap *);	/* Gain a reference. */
extern void		pmap_destroy(struct pmap *);	/* Release a reference. */

extern void		pmap_enter(struct pmap *, vm_offset_t, vm_offset_t,
				vm_prot_t, boolean_t,
				vm_prot_t);  /*Enter a mapping */
extern void		pmap_enter_bigpage(struct pmap *, vm_offset_t,
				vm_offset_t, vm_prot_t, int, vm_prot_t, int,
				vm_offset_t,
				vm_offset_t); /* Enter many more mappings*/
extern kern_return_t	pmap_map_io(vm_offset_t, vm_size_t, vm_offset_t,
				vm_prot_t, vm_tbop_t);


/*
 *	Routines that operate on ranges of virtual addresses.
 */
extern void		pmap_remove(struct pmap *, vm_offset_t, vm_offset_t);
						/* Remove mappings. */
extern void		pmap_remove_wired(struct pmap *, vm_offset_t, 
					vm_offset_t);
extern kern_return_t	pmap_remove_not_wired(struct pmap *, vm_offset_t, 
					vm_offset_t);		
extern void		pmap_protect(struct pmap *, vm_offset_t, vm_offset_t,
					vm_prot_t); /* Change protections. */
extern kern_return_t	pmap_ssm_protect(struct pmap_ssm *, vm_prot_t,
					vm_prot_t, vm_offset_t, vm_size_t);
extern void		pmap_protect_bigpage(struct pmap *, vm_offset_t, vm_offset_t,
					     vm_prot_t); 
extern void		pmap_invalidate_bigpage(struct pmap *, vm_offset_t, int);
extern kern_return_t	pmap_ssm_invalidate(struct pmap_ssm *, vm_offset_t, 
					    vm_size_t);

/*
 *	Routines to set up hardware state for physical maps to be used.
 */
extern void		pmap_activate(struct pmap *, struct thread *, int);	
						/* Prepare pmap_t to run
						 * on a given processor.
						 */
extern void		pmap_deactivate(struct pmap *, struct thread *, int);	
						/* Release pmap_t from
						 * use on processor.
						 */


/*
 *	Routines that operate on physical addresses.
 */
extern kern_return_t	pmap_page_protect(vm_offset_t, vm_prot_t);	
						/* Restrict access to page. */
extern kern_return_t	pmap_copy_on_write(vm_offset_t);	
						/* Remove write privilege. */
extern boolean_t	pmap_valid_page(vm_offset_t, ulong);	
						/* Is physical address
						 * valid and usable by
						 * machine-independent
						 * VM system?  Used only
						 * at startup.
						 */
extern kern_return_t	pmap_mark_page_bad(vm_offset_t);	

extern vm_size_t	pmap_get_page_size(vm_offset_t);

extern kern_return_t	pmap_move_all(vm_offset_t, vm_offset_t, boolean_t);

/*
 *	Routines to manage reference/modify bits based on
 *	physical addresses, simulating them if not provided
 *	by the hardware.
 */
extern void		pmap_clear_reference(vm_offset_t);	
						/* Clear reference bit */
#ifndef	pmap_is_referenced
extern boolean_t	pmap_is_referenced(vm_offset_t);	
						/* Return reference bit */
#endif	/* pmap_is_referenced */

extern void
	pmap_clear_modify(vm_offset_t),	/* Clear modify bit */
	pmap_clear_refmod(vm_offset_t);	/* Clear modify and reference bits */

extern boolean_t
	pmap_is_modified(vm_offset_t);	/* Return modify bit */


/*
 *	Statistics routines
 */
extern void		pmap_statistics();	/* Return statistics */

#ifndef	pmap_resident_count
extern int		pmap_resident_count();
#endif	/* pmap_resident_count */

/*
 *	Sundry required routines
 */
extern boolean_t	pmap_access(struct pmap *, vm_offset_t);		
						/* Is virtual address valid? */

#ifndef	pmap_update
extern void		pmap_update();		/* Bring maps up to date */
#endif	/* pmap_update */
extern void		pmap_collect(struct vm_map *);		
						/* Perform garbage
						 * collection, if any
						 */

extern void		pmap_change_wiring(struct pmap *, vm_offset_t, boolean_t);	
extern void		pmap_wire(struct pmap *, vm_offset_t, vm_size_t);

						/* Specify pageability */
#ifndef	pmap_phys_address
extern vm_offset_t	pmap_phys_address();	/* Transform address
						 * returned by device
						 * driver mapping function
						 * to physical address
						 * known to this module.
						 */
#endif	/* pmap_phys_address */

#ifndef	pmap_phys_to_frame
extern int		pmap_phys_to_frame();	/* Inverse of
						 * pmap_phys_address,
						 * for use by device driver
						 * mapping function in
						 * machine-independent
						 * pseudo-devices.
						 */

#endif	/* pmap_phys_to_frame */

/*
 *	Optional routines
 */
#ifndef	pmap_copy
extern void		pmap_copy();		/* Copy range of
						 * mappings, if desired.
						 */
#endif	/* pmap_copy */
#ifndef	vtop
extern vm_offset_t	vtop(struct proc *, vm_offset_t);
#endif	/* vtop */

/*
 * The machine/pmap.h include file must export PMAP_SEGMENTATION for
 * the upper level to have access to the low level pmap functions.
 */

#if	PMAP_SEGMENTATION
extern struct pmap_seg
	*pmap_seg_alloc(int),
	*pmap_seg_find(queue_t, simple_lock_t);
extern struct pmap_seg_map
	*pmap_seg_load(struct pmap *, struct pmap_seg *, vm_offset_t);
extern void
	pmap_seg_destroy(queue_t),
	pmap_seg_enter(struct pmap *, struct pmap_seg *, vm_offset_t, vm_offset_t, vm_prot_t),
	pmap_seg_enter_bigpage(struct pmap *, struct pmap_seg *, vm_offset_t, vm_offset_t, vm_prot_t, int),
	pmap_seg_unload(struct pmap_seg_map *),
	pmap_seg_remove(queue_t, vm_offset_t, vm_size_t),
	pmap_seg_migrate(struct pmap_seg_map *, struct pmap_seg *);

extern boolean_t
	pmap_seg_mapped(struct pmap *, vm_offset_t);

#else
#define	pmap_seg_destroy(PSEG)
#define	pmap_seg_alloc(PPSEG) 						\
	((*PPSEG) = (struct pmap_seg *) 0, KERN_INVALID_ADDRESS)
#define	pmap_seg_load(PMAP, PSEG, START)
#define	pmap_seg_unload(PMAP, PSEG, START)
#define	pmap_seg_enter(PMAP, PSEG, ADDR, PHYS, PROT)
#endif	/* !PMAP_SEGMENTATION */

#define pmap_sh_regions(mid) (pmr_data.pmr_rad_table[mid].pmr_sh_count)

extern void
	pmap_unload(),
	pmap_region_info(int, int, struct pmr_info *),
	pmap_valloc_done(int, int, struct pmr_info *),
	pmap_pvh_init(struct vm_page *, int, int),
	pmap_copy_page(vm_offset_t, vm_offset_t),
	*pmap_valloc(int, int, vm_size_t, vm_size_t, int);

extern int
	pmap_regions(int);

extern kern_return_t
	pmap_load(),
	pmap_dup(struct pmap *, vm_offset_t, vm_size_t, vm_offset_t,
			vm_prot_t, vm_tbop_t);

#ifndef	dump_memory_dump_setup
extern	void
	dump_memory_dump_setup(int, int);
#endif
#ifndef	dump_page_holds_memory_dump
extern	int
	dump_page_holds_memory_dump(vm_offset_t, vm_offset_t *, vm_offset_t *);
#endif

#ifndef	pmap_fix
struct processor_affinity_group;
extern boolean_t
	pmap_fix(struct pmap *, vm_offset_t);
#endif

extern boolean_t
	pmap_coproc_page_is_busy(struct pmap *, vm_offset_t, vm_size_t);

extern boolean_t
	pmap_is_lw_wired(struct pmap *, vm_offset_t, vm_offset_t),
	pmap_is_mine_lw_wired(struct pmap *, vm_offset_t, vm_offset_t),
	pmap_remove_wired_med(struct pmap *, vm_offset_t, vm_offset_t),
	pmap_verify_free(vm_offset_t),
	pmap_ssm_mapped(struct pmap_ssm *, vm_offset_t),
	pmap_check_fp_waiters(int),
	pmap_release_fp_waiters(int);

extern int
	pmap_clrmod_fow(vm_offset_t),
	pmap_ssm_unmap(struct pmap *, struct pmap_ssm *, vm_offset_t,boolean_t),
	pmap_is_tb_range(struct pmap *, vm_offset_t);

extern void
	pmap_read_lev2(struct pmap *, vm_offset_t, vm_size_t, union pt_entry *),
	pmap_write_lev2(struct pmap *, vm_offset_t, vm_size_t, union pt_entry *),
	pmap_release_l3(union pt_entry *, u_long),
	pmap_ssm_alloc(struct pmap_ssm *),
	pmap_ssm_destroy(struct pmap_ssm *),
	pmap_ssm_wire(struct pmap_ssm *, int),
	pmap_ssm_unwire(struct pmap_ssm *, int),
	pmap_mad_init(int),
	system_memory_synch_point(void),
	task_memory_synch_point(void);

extern kern_return_t
	pmap_remove_lev2(struct pmap *, vm_offset_t, vm_size_t),
	pmap_ssm_enter(struct pmap *, struct pmap_ssm *, vm_offset_t,
		vm_offset_t, vm_prot_t, vm_prot_t, vm_prot_t, boolean_t),
	pmap_ssm_enter_bigpage(struct pmap *, struct pmap_ssm *,
		vm_offset_t, vm_offset_t, vm_prot_t, vm_prot_t, vm_prot_t,
		boolean_t, int, vm_offset_t, vm_offset_t);

extern vm_size_t
	pmap_mad_size(int),
	pmap_secondary_cache_size(void);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif	/* _VM_PMAP_H_ */
