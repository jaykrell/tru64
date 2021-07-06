/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: vm_map.h,v $
 * Revision 4.2.71.5  2005/03/23  17:07:42  Thomas_Blinn
 * 	Define and use FAULT_LOCKED() in place of SLOCK_LOCKED().
 * 	[2005/03/17  22:04:16  Thomas_Blinn]
 *
 * 	Add VM_MAP_LOCKING_DEBUG support.  This includes:
 * 	vm_mape_inuse_check() macro to test assertions about VM map entries
 * 	vm_mape_1user_check() macro to test assertions about VM map entries
 * 	for both of the above, verify that the entry is NOT in use (and that
 * 	the map is locked).
 * 	add checks in fault assertion for correct map lock state.
 * 	add a macro for checking that mape map lock is locked.
 * 	add vm_mape_kfault() based on vm_mape_fault() for use
 * 	when map is locked for exclusive access.
 * 	fix SAVE_HINT macro definition to have braces around multiple lines
 * 	of code
 * 	Fix customer escalation QARs 36, 158, 216, 224, 225, and earlier PTR cases
 * 	[2005/03/02  19:07:47  Thomas_Blinn]
 *
 * Revision 4.2.71.2  2003/05/22  17:28:42  Matthew_McGrath
 * 	Add auditing capacity for wire/unwire operations.
 *
 * Revision 4.2.71.1  2002/09/30  20:42:52  Matthew_McGrath
 * Merge Information:  Non-Visual Merge: User specified tree v51asupportos.nightly
 *     User Revision:  wcalphaos_bl6:4.2.65.2 Local Ancestor: n/a
 *    Merge Revision:  v51asupportos_nightly:4.2.69.1
 *   Common Ancestor:  4.2.59.3
 * 	Merge up to v51asupportos.nightly
 *
 * Revision 4.2.69.1  2002/08/26  15:54:10  Matthew_McGrath
 * 	Add defines for the bits in the reserve_address_space tunable.
 * 
 * Revision 4.2.65.2  2002/07/17  18:30:32  Andrew_Moskal
 * 	Make page coloring controls big-page amenable.
 * 
 * Revision 4.2.65.1  2002/01/25  22:02:31  Ross_Knepper
 * 	Add VME_OFFSET() macro because vme_offset is used differently
 * 	for a seg object.
 * 
 * Revision 4.2.59.3  2000/12/08  00:27:21  Ross_Knepper
 * 	Add member vm_color_inc to vm_map, which is used for varying
 * 	the prime-number stride through the color buckets to avoid aliasing.
 * 
 * Revision 4.2.59.2  2000/10/11  14:21:46  Ross_Knepper
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree yankeeos
 *     User Revision:  Ross_Knepper_split_br:4.2.55.1 Local Ancestor:4.2.48.7
 *    Merge Revision:  yankeeos_br:4.2.59.1
 *   Common Ancestor:  4.2.48.7
 * 
 * Revision 4.2.59.1  2000/09/18  20:38:48  Per_Wahlstrom
 * 	Enable vm_map_ops prototypes
 * 
 * Revision 4.2.55.1  2000/09/11  17:54:26  Ross_Knepper
 * 	Change prototypes for u_map_entry_unmap() and vm_map_entry_split()
 * 	to kern_return_t.
 * 
 * Revision 4.2.48.7  1999/12/15  20:10:11  Shashi_Mangalat
 * 	Add support for text segment migration.
 * 	Add prototypes to map entry handler type casts.
 * 
 * Revision 4.2.48.6  1999/05/06  19:35:25  Shashi_Mangalat
 * 	Merge of STEELOS_BL21:STEELOS_BL23
 * 	 Revision 4.2.24.12  1999/03/19  20:06:39  Ernie_Petrides
 * 	 Fix declarations of simple lock fields.
 * 	[1999/05/06  19:29:58  Shashi_Mangalat]
 * 
 * Revision 4.2.48.5  1999/03/09  23:49:39  Shashi_Mangalat
 * 	Merge of STEELOS_BL20:STEELOS_BL21
 * 	 Revision 4.2.24.11  1998/11/25  23:35:14  Shashi_Mangalat
 * 	 VM/NUMA scalability enhancements.
 * 	[1999/03/09  23:44:40  Shashi_Mangalat]
 * 
 * Revision 4.2.48.4  1998/10/05  16:12:47  Shashi_Mangalat
 * 	Merge fix
 * 	[1998/10/05  16:07:53  Shashi_Mangalat]
 * 
 * Revision 4.2.48.3  1998/10/02  19:41:28  Shashi_Mangalat
 * 	Merge of STEELOS_BL16:STEELOS_BL18
 * 	 Revision 4.2.24.10  1998/05/12  18:29:56  Larry_Woodman
 * 	 bmerge PTCOS_BL14:PTEV6OS_BL4
 * 	  Revision 4.2.42.2  1998/03/31  21:16:17  Tony_Bono
 * 	  Merged Ashoke_Rampuria's umc support code to improve
 * 	  performance for specweb and other web type applications.
 * 	[1998/10/02  19:26:05  Shashi_Mangalat]
 * 
 * Revision 4.2.48.2  1998/08/26  12:43:53  James_Woodward
 * 	Merge of numaproj and zulu
 * 	[1998/07/29  20:18:49  James_Woodward]
 * 
 * Revision 4.2.45.3  1998/05/18  21:21:36  Shashi_Mangalat
 * 	Add support for text replication.
 * 	[1998/05/18  20:41:15  Shashi_Mangalat]
 * 
 * Revision 4.2.45.2  1998/05/13  19:42:39  James_Woodward
 * 	add support for multiple lvl1 to pmap
 * 	[1998/05/13  12:04:50  James_Woodward]
 * 
 * Revision 4.2.24.9  1998/02/27  16:31:56  Lee_Schermerhorn
 * 	 Add extern declaration of vm_map_hint_lockinfo for initializing copy
 * 	 maps in u_map_copyin().
 * 	[1998/02/26  20:04:19  Lee_Schermerhorn]
 * 
 * Revision 4.2.24.8  1998/02/23  16:20:28  Lee_Schermerhorn
 * 	Map Entry SkipList: replace linear map entry list with a skiplist
 * 	[1998/02/20  20:32:59  Lee_Schermerhorn]
 * 
 * Revision 4.2.24.7  1997/09/08  22:25:50  Shashi_Mangalat
 * 	Remove unused vm_map_actual_size().
 * 	Merge of PTmin BL10 changes (PTCOS_BL6:PTCOS_BL10).
 * 	 Revision 4.2.30.4  1997/07/26  22:08:38  Shashi_Mangalat
 * 	 Change the boolean argument in mo_copyin() to int and add flag
 * 	 values to allow non-blocking operation.
 * 	 Revision 4.2.30.3  1997/06/17  21:44:35  Shashi_Mangalat
 * 	 Remove unused vm_maximum.  Change color buckets to an array.
 * 	[1997/09/08  21:11:33  Shashi_Mangalat]
 * 
 * Revision 4.2.24.6  1997/04/24  21:32:56  Larry_Woodman
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL3:PTCOS_BL6 **
 * 		** Ancestor revision:	4.2.22.3 **
 * 		** Merge revision:	4.2.30.2 **
 * 	 	** End **
 * 	merge of PTmin BL6 changes
 * 	[1997/04/24  20:32:00  Larry_Woodman]
 * 
 * Revision 4.2.30.2  1997/04/03  15:42:42  Larry_Woodman
 * 	Support for Dynamic Page Coloring and Scalable Task Swapping.
 * 	[1997/04/01  19:39:31  Larry_Woodman]
 * 
 * Revision 4.2.24.5  1997/03/03  15:41:00  Robin_Miller
 * 	Adding common function prototypes.
 * 	Remove protos for vm_msleep(), vm_mwakeup(), vm_msem_init(),
 * 	which no longer exist.
 * 	[1997/03/03  15:10:45  Robin_Miller]
 * 
 * Revision 4.2.24.4  1996/09/14  15:06:52  Shashi_Mangalat
 * 	Make vm_map.vm_nentries unsigned int to remove any ambiguities when
 * 	comparing with similar fields in vm_tune and vm_map_copy structures.
 * 	[1996/09/12  18:30:48  Shashi_Mangalat]
 * 
 * Revision 4.2.24.3  1996/08/14  21:07:41  Jeff_Colburn
 * 	Function prototype cleanup
 * 	[1996/08/13  16:29:26  Jeff_Colburn]
 * 
 * Revision 4.2.24.2  1996/07/24  14:55:06  Jeff_Colburn
 * 	Function prototype work, header definitions
 * 	[1996/07/22  17:47:22  Jeff_Colburn]
 * 
 * Revision 4.2.22.3  1995/11/09  20:15:50  Patrick_ORourke
 * 	Add prototype for vm_map_exit.
 * 	[1995/11/09  14:01:32  Patrick_ORourke]
 * 
 * Revision 4.2.22.2  1995/06/30  11:50:51  Patrick_ORourke
 * 	Merge to latest
 * 	[1995/06/28  20:33:55  Patrick_ORourke]
 * 	Per task swap: Add vm_lazy_map bit to indicate that the map is
 * 	lazily swapped.
 * 	[1995/06/27  14:16:22  Patrick_ORourke]
 * 	Merge to ptos.nightly
 * 	[1995/06/23  18:22:20  Patrick_ORourke]
 * 	Swap structure reorganization
 * 	[1995/06/22  17:18:30  Patrick_ORourke]
 * 
 * Revision 4.2.20.2  1994/10/12  12:44:08  Jeff_Denham
 * 	Add definition of vm_map_lock_try() for use by AIO.
 * 	[1994/10/07  20:05:05  Jeff_Denham]
 * 
 * Revision 4.2.14.7  1994/05/27  18:09:36  Shashi_Mangalat
 * 	Replace as_grow_t with two constants and a default to be used
 * 	as a boolean.
 * 	[1994/05/27  17:12:48  Shashi_Mangalat]
 * 
 * Revision 4.2.14.6  1994/03/02  04:38:09  Shashi_Mangalat
 * 	Changes to allow common interface among kernel and usr maps.  Corrected
 * 	map entry inheritance size to allow all possible values.  Changed
 * 	vme_faults to an int for better performance.
 * 	[1994/03/02  04:25:08  Shashi_Mangalat]
 * 
 * Revision 4.2.14.5  1993/12/16  17:16:26  Shashi_Mangalat
 * 	Merge of Sterling BL8 changes.
 * 	 Changed the extern declaration for vm_map_entry_create.
 * 	 [1993/11/22  23:22:05  Ashoke_Rampuria]
 * 	[1993/12/16  16:40:52  Shashi_Mangalat]
 * 
 * Revision 4.2.14.4  1993/10/07  15:48:53  Shashi_Mangalat
 * 	Merge of Sterling BL6 changes.
 * 	 vm_map_vsize()
 * 	 [1993/08/04  14:45:53  Joe_Martin]
 * 	 Actual segmentation size for ps VSZ.
 * 	 [1993/05/27  04:40:47  Anna_Salzberg]
 * 	 Implement page coloring.
 * 	 [1993/03/29  14:01:39  Larry_Woodman]
 * 	[1993/10/07  15:12:01  Shashi_Mangalat]
 * 
 * Revision 4.2.14.3  1993/08/26  15:06:56  Shashi_Mangalat
 * 	Removed dependancy on UNIX_LOCKS.  Removed unused vm_map_lock_init()
 * 	macro.
 * 	[1993/08/25  20:35:53  Shashi_Mangalat]
 * 
 * Revision 4.2.14.2  1993/05/26  22:18:12  Paula_Long
 * 	submitting the SMP project
 * 	[1993/05/26  06:59:03  Paula_Long]
 * 
 * Revision 4.2.12.2  1993/05/24  12:21:22  James_Woodward
 * 	osf1.2 /kern merge
 * 	[1993/05/12  19:12:30  James_Woodward]
 * 
 * Revision 4.2.4.5  1992/09/29  17:27:50  Joe_Martin
 * 	AG_BL10_4 merge
 * 	Revision 4.2.2.5  92/07/14  15:21:24  John_Gemignani
 * 	Change bitvector defs from long to int
 * 	[92/07/09  15:31:00  John_Gemignani]
 * 
 * Revision 4.2.4.4  92/07/08  16:38:39  Joe_Martin
 * 	merged in Silver BL8_2
 * 	Revision 4.2.2.4  92/06/19  11:02:11  Robert_Picco
 * 	Segmentation code
 * 	[92/06/18  21:08:28  Robert_Picco]
 * 
 * Revision 4.2.4.3  92/06/03  12:49:09  Joe_Martin
 * 	merged in Silver BL7
 * 	Revision 4.2.2.3  92/05/20  09:32:52  Larry_Woodman
 * 	Task pagefault rate measurements.
 * 	[92/05/08  13:54:59  Larry_Woodman]
 * 
 * Revision 4.2.4.2  92/03/18  19:01:15  Al_Delorey
 * 	From Silver: AG_BL5
 * 	[92/03/18  17:49:41  Al_Delorey]
 * 	Modified mape offset to union of offet and seg ptr
 * 	[92/06/02  08:53:11  Robert_Picco]
 * 
 * Revision 4.2.2.2  92/02/26  15:54:51  Charles_Briggs
 * 	UBC merge
 * 	[92/02/23  14:20:43  Charles_Briggs]
 * 	UBC merge.
 * 	[92/02/22  14:55:40  Charles_Briggs]
 * 
 * Revision 4.2  91/09/19  23:07:54  devbld
 * 	Adding ODE Headers
 * 
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: vm_map.h,v $ $Revision: 4.2.71.5 $ (DEC) $Date: 2005/03/23 17:07:42 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
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
 * OSF/1 Release 1.0
 */
/*
 *	File:	vm/vm_map.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Copyright (C) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Virtual memory map module definitions.
 *
 * Contributors:
 *	avie, dlb, mwyoung
 */

#ifndef	_VM_VM_MAP_H_
#define _VM_VM_MAP_H_
#include <mach/vm_attributes.h>

/*
 * tpb - we enable active map locking debug checks in various places
 * including several macros defined here and in vm_umap.h and vm_kmap.h
 * by defining VM_MAP_LOCKING_DEBUG; the value doesn't matter, just 
 * whether it is defined or not.
#define VM_MAP_LOCKING_DEBUG 1
 */

#ifdef __cplusplus
extern "C" {
#endif


#define VM_SKIPLIST 1	/*	enable skiplist */
#define MESL_USE_PCC	1	/* use Alpha Process Cycle Counter for random #s */
#undef MESL_DEBUG 	/* */
#undef MESL_STATS 	/* */

#include <mach/kern_return.h>
#include <mach/boolean.h>
#include <mach/machine/vm_types.h>
#include <mach/vm_prot.h>
#include <mach/vm_inherit.h>
#include <machine/pmap.h>
#include <vm/vm_fault.h>
#include <vm/vm_control.h>
#include <vm/vpage.h>
#include <vm/vm_object.h>
#include <kern/lock.h>
#include <kern/macro_help.h>

/*
 *	Types defined:
 *
 *	vm_map_t		the high-level address map data structure.
 *	vm_map_entry_t		an entry in an address map.
 *	vm_map_copy_t		represents memory copied from an address map,
 *				 used for inter-map copy operations
 */

#ifdef	VM_SKIPLIST
/*
 * Skiplist definitions for vm map entry list maintenance:
 */
#define	MESL_NLEVELS		4	/* Number of levels in vme_skiplist */
#define MESL_BFACTOR		4	/* Branch factor in skip list; */
					   /* must be a power of 2 */
#define MESL_LOG2BF		2	/* log2 of MESL_BFACTOR */
#define MESL_UNUSED		((vm_map_entry_t)-1)
#define	MESL_THRESHOLD 16	/* # map entries before random levels */

typedef struct mesl_path {
  struct vm_map_entry *mesls[MESL_NLEVELS]; /* a mesl search path */
} mesl_spath_t;
#endif	/* VM_SKIPLIST */

typedef union vm_map_object {
	struct vm_object	*vm_object;	/* object object */
	struct vm_map		*sub_map;	/* belongs to another map */
} vm_map_object_t;

#ifndef	VM_SKIPLIST
struct vm_map_links {
	struct vm_map_entry	*prev;		/* previous entry */
	struct vm_map_entry *next;		/* next entry */
	vm_offset_t		start;		/* start address */
	vm_offset_t		end;		/* end address */
};
#else /* VM_SKIPLIST */
/*
 * Note:  In order to replace "next" with "vml_sl_next[0]", had to change 
 * several other places.  If the member had been given a unique name -- e.g., 
 * vml_next -- we could have done it here with a #define.  But, redefining 
 * "next" would not be a good idea...
 *
 * So, changed the names of the vm_map_links members to have vml_ prefix.
 * This will quickly catch any other sources that reference vm_map_links 
 * directly instead of using the access macros.
 *
 * The order of the members has been chosen to keep vml_prev, vml_start,
 * vml_end, and vml_sl_next[0] in a 32byte cache line.  This will maintain
 * the single cache miss per visited entry for the vast majority of entries
 * visited.
 */
struct vm_map_links {
	struct vm_map_entry	*vml_prev;		/* previous entry */
	vm_offset_t		vml_start;		/* start address */
	vm_offset_t		vml_end;		/* end address */
	struct vm_map_entry	*vml_sl_next[MESL_NLEVELS];/* skip list links */
};
#endif /* VM_SKIPLIST */

union vmet {
	vm_offset_t			tvme_offset;	/* offset into object */
	struct seg_map {
		struct vm_seg		*sm_seg;	/* VM segment mapping */
		struct pmap_seg_map	*sm_psm;	/* pmap mapping */
	} tvme_seg;
};

struct vm_map_entry {
	struct vm_map_links	vme_links;	/* links to other entries */
	struct vm_map		*vme_map;	/* map which owns us */
	union vm_map_object	vme_uobject;	/* object I point to */
	union vmet		vmet;
	struct vm_map_entry_ops *vme_ops;	/* Map entry operations */
	struct vpage		vme_vpage;	/* Virtual page information */
						/* Fault locking */
	simple_lock_data_t	vme_faultlock;
	unsigned int		vme_faults;	/* active faults */
	union vmeu {
		struct uvme {			/* User map entry info */
			unsigned int
				uvme_faultwait   : 1,
				uvme_keep_on_exec: 1,
				uvme_inheritance : 2,
				uvme_maxprot     : 3,
				uvme_umc     	 : 1, /* unified mbuf cache */
				uvme_psmmigr     : 1, /* segment migration */
				uvme_psmwait     : 1,
						 : 22;
		} uvme;
		struct kvme {			/* Kernel map entry info */
			unsigned int
				kvme_faultwait: 1,	/* same as above */
				kvme_is_submap: 1,
				kvme_copymap  : 1;
		} kvme;
	} vmeu;
	vm_offset_t		vme_private;	/* Private data for map */
};

typedef struct vm_map_entry	*vm_map_entry_t;

#define	vme_offset		vmet.tvme_offset
#define	vme_seg			vmet.tvme_seg.sm_seg
#define	vme_psm			vmet.tvme_seg.sm_psm
#define	vme_faultwait		vmeu.uvme.uvme_faultwait
#define	vme_psmmigrate		vmeu.uvme.uvme_psmmigr
#define	vme_psmwait		vmeu.uvme.uvme_psmwait
#define	vme_keep_on_exec	vmeu.uvme.uvme_keep_on_exec
#define	vme_inheritance		vmeu.uvme.uvme_inheritance
#define vme_maxprot		vmeu.uvme.uvme_maxprot
#define vme_umc			vmeu.uvme.uvme_umc
#define vme_is_submap		vmeu.kvme.kvme_is_submap
#define vme_copymap		vmeu.kvme.kvme_copymap
#define vme_protection		vme_vpage.vp_prot
#define	vme_kwire		vme_vpage.vp_kwire
#define	vme_plock		vme_vpage.vp_plock

#ifndef	VM_SKIPLIST
#define vme_prev		vme_links.prev
#define vme_next		vme_links.next
#define vme_start		vme_links.start
#define vme_end			vme_links.end
#else	/* VM_SKIPLIST */
#define vme_prev		vme_links.vml_prev
#define vme_next		vme_links.vml_sl_next[0]
#define vme_sl_next		vme_links.vml_sl_next
#define vme_start		vme_links.vml_start
#define vme_end			vme_links.vml_end
#endif	/* VM_SKIPLIST */

#define	vme_object		vme_uobject.vm_object
#define	vme_submap		vme_uobject.sub_map

#define VME_OFFSET(EP)		((EP)->vme_object->ob_type == OT_SEG \
					? 0: (EP)->vme_offset)

#define VM_MAP_ENTRY_NULL	((vm_map_entry_t) 0)

struct vm_color {	/* Page coloring controls */
	short	steps;	/* Iterations remaining within group */
	short	stride; /* Pace through group */
	short	index;  /* Position to examine next within group */
	short	group;  /* GH+1 grouping */
};

struct vm_map {
	struct vm_map_links	vm_links;	/* links to the entries */
	unsigned int		vm_nentries;	/* Number of vme entries */
	unsigned int 				/* Main or submap */
				vm_is_mainmap :1,
				vm_copy_map:1,	/* kernel copy submap */
						/* kernel map entries */
				vm_entries_pageable:1, 
						/* wait for space */
				vm_wait_for_space:1,
				vm_umap:1,	/* user space map */
				vm_lazy_map:1,	/* map swapped lazily? */
#ifndef	VM_SKIPLIST
				:26;
#else	/* VM_SKIPLIST */
	/*
	 * map entry skiplist additions
	 */
				:20,		/* filler */
				vm_mesl_hilevel:6;	/* skip list max active level */
	struct mesl_path	vm_mesl_path;
#endif	/* VM_SKIPLIST */
	vm_map_entry_t		vm_hint;	/* hint for quick lookups */
	simple_lock_data_t	vm_hint_lock;	/* lock for vm_hint storage */
	struct vm_map_ops	*vm_ops;	/* Operations on addr space */
	lock_data_t		vm_lock;	/* Lock for map data */
	vm_size_t		vm_size;	/* virtual size */
	struct pmap		*vm_pmap;	/* Physical map */
	simple_lock_data_t	vm_ref_lock;	/* Lock for vm_ref_count */
	vm_map_entry_t		vm_first_free;	/* First free space hint */
	vm_offset_t		vm_private;	/* Map private information */
	int			vm_ref_count;	/* Reference count */
        int			vm_res_count;   /* Map resident count */
        unsigned int		vm_fault_rate;  /* Pagefaults over time */
        int			vm_pagefaults;  /* Accumulated pagefault */
        unsigned int		vm_faultrate_time; /* Time of last vm_fault_rate update */
	int			pad[7];		/* 32-byte align coloring data */
	struct vm_color		vm_private_colors[4];
	struct vm_color	        vm_shared_colors[4];
};

typedef	struct vm_map * vm_map_t;

#define		VM_MAP_NULL	((vm_map_t) 0)

#ifndef	VM_SKIPLIST
#define	vm_prev			vm_links.prev	
#define	vm_next			vm_links.next
#define vm_min_offset		vm_links.start	/* start of range */
#define vm_max_offset		vm_links.end	/* end of range */
#else	 /* VM_SKIPLIST */
#define	vm_prev			vm_links.vml_prev	
#define	vm_next			vm_links.vml_sl_next[0]
#define vm_min_offset		vm_links.vml_start	/* start of range */
#define vm_max_offset		vm_links.vml_end	/* end of range */
#endif	/* VM_SKIPLIST */


#define vm_map_to_entry(map)	((struct vm_map_entry *) &(map)->vm_links)
#define vm_map_first_entry(map)	((map)->vm_next)
#define vm_map_last_entry(map)	((map)->vm_prev)


typedef struct vm_map_copy {
	struct vm_map_links	vm_links;
	unsigned int		vm_nentries;
	unsigned int 				/* Main or submap */
				vm_is_mainmap :1,
				vm_copy_map:1,	/* kernel copy submap */
						/* kernel map entries */
				vm_entries_pageable:1, 
						/* wait for space */
				vm_wait_for_space:1,
				vm_umap:1,	/* user space map */
				vm_lazy_map:1,	/* map swapped lazily? */
#ifndef	VM_SKIPLIST
				:26;
#else	/* VM_SKIPLIST */
	/*
	 * map entry skiplist additions
	 */
				:20,		/* filler */
				vm_mesl_hilevel:6;	/* skip list max active level */
	struct mesl_path	vm_mesl_path;
	/*
	 * skip list uses hint and hint lock
	 */
	vm_map_entry_t		vm_hint;	/* hint for quick lookups */
	simple_lock_data_t	vm_hint_lock;	/* lock for vm_hint storage */
#endif	/* VM_SKIPLIST */
} *vm_map_copy_t;

#define	VM_MAP_COPY_NULL	((vm_map_copy_t) 0)

#define vm_map_copy_to_map(copy)		\
		((struct vm_map *) copy)
#define vm_map_copy_to_entry(map)		\
		((struct vm_map_entry *) &(map)->vm_links)
#define vm_map_copy_first_entry(map)		\
		((map)->vm_next)
#define vm_map_copy_last_entry(map)		\
		((map)->vm_prev)

/*
 * Reserve space for heap against mmap
 */
#define VM_MAPSPACE_RES		1
#define VM_MAPSPACE_RES_TASO	2

/*
 * Map entry space grow
 */
#define	AS_GROWDOWN	0
#define	AS_GROWUP	1
#define	AS_GROWDEF	AS_GROWUP

/*
 * Dup has to be told the type of copy operation
 * in order to support the Mach like inheritance model.
 */

typedef enum {
	VM_COPYU,				/* UNIX copy technology */
	VM_COPYMSHARE,				/* Mach share */
	VM_COPYMCOPY,				/* Mach copy */
	VM_COPYMNONE,				/* Mach none */
	VM_COPYMDONATE				/* Mach donate */
} vm_copy_t;

/*
 * Map entry copy operations
 */
typedef	enum {
	VME_COPYLOAD,				/* Copy entry was loaded */
	VME_COPYFREE				/* Free a copy map entry */
} vm_copy_op_t;

/*
 * Page color preference 
 */
#define	VM_COLOR_SHARED		0		/* shared pages */
#define	VM_COLOR_PRIVATE	1		/* private pages */

struct vm_control;

struct vm_map_entry_ops {
	int (*me_fault)(vm_map_entry_t, vm_offset_t, vm_size_t, vm_prot_t, 
				vm_fault_t, struct vm_page **);
	int (*me_dup)(vm_map_entry_t, vm_offset_t, vm_size_t,
				vm_map_entry_t, vm_copy_t);
	int (*me_unmap)(vm_map_entry_t, vm_offset_t, vm_size_t);
	int (*me_msync)(vm_map_entry_t, vm_offset_t, vm_size_t, int);
	int (*me_lockop)(vm_map_entry_t, vm_offset_t, vm_size_t, vm_fault_t);
	int (*me_swap)(vm_map_entry_t, int);
	int (*me_core)(vm_map_entry_t, unsigned int, char *, int *);
	int (*me_control)(vm_map_entry_t, vm_offset_t, vm_size_t, vm_control_t, int);
	int (*me_protect)(vm_map_entry_t, vm_offset_t, vm_size_t, vm_prot_t);
	int (*me_check_protect)(vm_map_entry_t, vm_offset_t,
				vm_size_t, vm_prot_t);
	int (*me_cluster)(vm_map_entry_t, vm_offset_t, int, vm_offset_t *,
				vm_offset_t *, struct vm_control *);
	int (*me_copy)(vm_map_entry_t, vm_copy_op_t);
	int (*me_grow)(vm_map_entry_t, vm_prot_t, vm_size_t, boolean_t);
};

#define CAST_MAP_ENTRY_FAULT	(int (*)(vm_map_entry_t, vm_offset_t,	\
				vm_size_t, vm_prot_t, vm_fault_t,	\
				struct vm_page **))
#define CAST_MAP_ENTRY_DUP	(int (*)(vm_map_entry_t, vm_offset_t,	\
				vm_size_t, vm_map_entry_t, vm_copy_t))
#define CAST_MAP_ENTRY_UNMAP	(int (*)(vm_map_entry_t, vm_offset_t,	\
				vm_size_t))
#define CAST_MAP_ENTRY_MSYNC	(int (*)(vm_map_entry_t, vm_offset_t,	\
				vm_size_t, int))
#define CAST_MAP_ENTRY_LOCKOP	(int (*)(vm_map_entry_t, vm_offset_t,	\
				vm_size_t, vm_fault_t))
#define CAST_MAP_ENTRY_SWAP	(int (*)(vm_map_entry_t, int))
#define CAST_MAP_ENTRY_CORE	(int (*)(vm_map_entry_t, unsigned int,	\
				char *, int *))
#define CAST_MAP_ENTRY_CTRL	(int (*)(vm_map_entry_t, vm_offset_t,	\
				vm_size_t, vm_control_t, int))
#define CAST_MAP_ENTRY_PROT	(int (*)(vm_map_entry_t, vm_offset_t,	\
				vm_size_t, vm_prot_t))
#define CAST_MAP_ENTRY_CHECK_PROTECT	(int (*)(vm_map_entry_t,	\
				vm_offset_t, vm_size_t, vm_prot_t))
#define CAST_MAP_ENTRY_KLUST	(int (*)(vm_map_entry_t, vm_offset_t,	\
				int, vm_offset_t *, vm_offset_t *,	\
				struct vm_control *))
#define CAST_MAP_ENTRY_CPOUT	(int (*)(vm_map_entry_t, vm_copy_op_t))
#define CAST_MAP_ENTRY_GROW	(int (*)(vm_map_entry_t, vm_prot_t,	\
				vm_size_t, boolean_t))

typedef struct vm_map_entry_ops * vm_map_entry_ops_t;

#define vme_fault		vme_ops->me_fault
#define vme_dup			vme_ops->me_dup
#define	vme_unmap		vme_ops->me_unmap
#define vme_msync		vme_ops->me_msync
#define vme_lockop		vme_ops->me_lockop
#define vme_swap		vme_ops->me_swap
#define vme_core		vme_ops->me_core
#define vme_control		vme_ops->me_control
#define vme_protect		vme_ops->me_protect
#define vme_check_protect	vme_ops->me_check_protect
#define vme_cluster		vme_ops->me_cluster
#define	vme_copy		vme_ops->me_copy
#define	vme_grow		vme_ops->me_grow

/*
 * copyin flags
 */
#define	COPY_DEFAULT		0		/* default */
#define	COPY_SRC_DESTROY	1		/* destroy source */
#define	COPY_NO_WAIT		2		/* don't block */

/*
 * Map specific operations
 */

struct vm_map_ops {
	int (*mo_deallocate)( vm_map_t map );
	int (*mo_fault)( vm_map_t map, vm_offset_t addr, 
				vm_prot_t fault_type, vm_fault_t wire );
	int (*mo_wire)( vm_map_t map, vm_offset_t start, 
				vm_offset_t end, vm_prot_t prot );
	int (*mo_allocate)( vm_map_t map, vm_object_t object, 
				vm_offset_t offset, vm_offset_t *addr,
				vm_size_t length, boolean_t find_space );
	int (*mo_map_enter)( vm_map_t map, vm_offset_t *address, 
			vm_size_t size, vm_offset_t mask, boolean_t anywhere,
			vm_object_t object, vm_offset_t offset,
			boolean_t needs_copy, vm_prot_t cur_protection,
			vm_prot_t max_protection, vm_inherit_t inheritance );
	int (*mo_protect)( vm_map_t map, vm_offset_t start, vm_offset_t end,
				vm_prot_t prot, boolean_t set_max );
	int (*mo_inherit)( vm_map_t map, vm_offset_t start, vm_offset_t end,
				vm_inherit_t new_inheritance );
	int (*mo_keep_on_exec)( vm_map_t map, vm_offset_t start, 
				vm_offset_t end, boolean_t new_koe );
	int (*mo_exec)( vm_map_t map, vm_offset_t start, vm_offset_t end );
	int (*mo_delete)( vm_map_t map, vm_offset_t start, 
				vm_offset_t end, boolean_t contain );
	boolean_t (*mo_check_protection)( vm_map_t map, vm_offset_t start,
				vm_offset_t end, vm_prot_t prot );
	int (*mo_copy_overwrite)( vm_map_t map, vm_offset_t dst_addr,
				vm_map_copy_t copy, 
				boolean_t interruptible, vm_size_t size );
	int (*mo_copyout)( vm_map_t map, vm_offset_t *dst_addr, 
				vm_map_copy_t copy );
	int (*mo_copyin)( vm_map_t map, vm_offset_t start, vm_size_t len,
				int flags, vm_map_copy_t *copy_result );
	int (*mo_fork)( vm_map_t oldmap, vm_map_t newmap, boolean_t lazy );

};

#define CAST_MAP_DEALLOC 	(int (*)())
#define CAST_MAP_ENTER 		(int (*)())
#define CAST_MAP_INHERIT 	(int (*)())
#define CAST_MAP_KOE 		(int (*)())
#define CAST_MAP_EXEC 		(int (*)())
#define CAST_MAP_CPOVW 		(int (*)())
#define CAST_MAP_CPOUT 		(int (*)())
#define CAST_MAP_CPIN 		(int (*)())
#define CAST_MAP_FORK 		(int (*)())

typedef struct vm_map_ops * vm_map_ops_t;

#define	vm_deallocate_map		vm_ops->mo_deallocate
#define vm_fault_map			vm_ops->mo_fault
#define vm_wire_map			vm_ops->mo_wire
#define vm_allocate_map			vm_ops->mo_allocate
#define	vm_enter_map			vm_ops->mo_map_enter
#define vm_protect_map			vm_ops->mo_protect
#define vm_inherit_map			vm_ops->mo_inherit
#define vm_keep_on_exec_map		vm_ops->mo_keep_on_exec
#define	vm_exec_map			vm_ops->mo_exec
#define vm_delete_map			vm_ops->mo_delete
#define vm_check_protection_map		vm_ops->mo_check_protection
#define vm_copy_overwrite_map		vm_ops->mo_copy_overwrite
#define vm_copyout_map			vm_ops->mo_copyout
#define vm_copyin_map			vm_ops->mo_copyin
#define	vm_fork_map			vm_ops->mo_fork

/* wire audit related definitions */

struct wire_audit_data {
	vm_map_t	map;
	vm_offset_t	va;
	int		npages;
	short		poffset;
	short		wtype;
	vm_offset_t	callpc;
};

typedef struct wire_audit_data *wire_audit_data_t;

void wire_audit(vm_map_t, vm_offset_t, vm_offset_t, int, void *);

#define WA_UNWIRE	0
#define WA_WIRE		1

/*
 *	Macros:		vm_map_lock, etc. [internal use only]
 *	Description:
 *		Perform locking on the data portion of a map.
 */

#define vm_map_lock(map)	lock_write(&(map)->vm_lock)
#define vm_map_unlock(map)	lock_write_done(&(map)->vm_lock)
#define vm_map_lock_read(map)	lock_read(&(map)->vm_lock)
#define vm_map_unlock_read(map)	lock_read_done(&(map)->vm_lock)
#define vm_map_lock_write_to_read(map) \
		lock_write_to_read(&(map)->vm_lock)
#define vm_map_lock_read_to_write(map) \
		(lock_read_to_write(&(map)->vm_lock))
#define vm_map_lock_set_recursive(map) \
		lock_set_recursive(&(map)->vm_lock)
#define vm_map_lock_clear_recursive(map) \
		lock_clear_recursive(&(map)->vm_lock)
#define vm_map_lock_try(map) \
		lock_try_write(&(map)->vm_lock)

#ifdef	VM_SKIPLIST
/*
 * for map entry skiplist search path updates -- use hint lock.
 * see vm_mesl_search()
 */
#define	vm_map_hint_lock(map)	simple_lock(&(map)->vm_hint_lock)
#define	vm_map_hint_unlock(map)	simple_unlock(&(map)->vm_hint_lock)

extern struct lockinfo		*vm_map_hint_lockinfo;
#endif	/* VM_SKIPLIST */

/*
 *	vm_map_entry_{un,}link:
 *
 *	Insert/remove entries from maps (or map copies).
 */
#ifndef	VM_SKIPLIST

#define vm_map_entry_link(map, after_where, entry)		\
		MACRO_BEGIN					\
		(map)->vm_nentries++;				\
		(entry)->vme_prev = (after_where);		\
		(entry)->vme_next = (after_where)->vme_next;	\
		(entry)->vme_prev->vme_next =			\
		 (entry)->vme_next->vme_prev = (entry);		\
		MACRO_END

#define vm_map_entry_unlink(map, entry) 			\
		MACRO_BEGIN 					\
		(map)->vm_nentries--; 				\
		(entry)->vme_next->vme_prev = (entry)->vme_prev;\
		(entry)->vme_prev->vme_next = (entry)->vme_next;\
		MACRO_END

#else	/* VM_SKIPLIST */

#define	vm_map_lookup_entry(map, addr, entry) \
		vm_mesl_search((map), (addr), (entry), NULL, FALSE)

#define vm_map_entry_link(map, after_where, entry)		\
		vm_mesl_insert(map, after_where, entry)

#define vm_map_entry_unlink(map, entry)		\
		vm_mesl_remove(map, entry)

#endif	/* VM_SKIPLIST */

/*
 *	SAVE_HINT:
 *
 *	Saves the specified entry as the hint for
 *	future lookups.  Performs necessary interlocks.
 * tpb -- since a vm_hint is a vm_map_entry_t, that is, a pointer
 *	to a map entry, there is no need to protect the update of
 *	the map hint with a lock; but we would have to remove the
 *	lock and review all the uses of the macro to really clean
 *	this up and that is left for a future revision.  For now,
 *	we put braces around the multiple lines of code so it is
 *	safe to use the macro definition.
 */

#define SAVE_HINT(MAP,VALUE) {					\
		simple_lock(&(MAP)->vm_hint_lock); 		\
		(MAP)->vm_hint = (VALUE); 			\
		simple_unlock(&(MAP)->vm_hint_lock);		\
}

/*
 *	Functions implemented as macros
 */
#define		vm_map_min(map)		((map)->vm_min_offset)
						/* Lowest valid address in
						 * a map */

#define		vm_map_max(map)		((map)->vm_max_offset)
						/* Highest valid address */

#define		vm_map_pmap(map)	((map)->vm_pmap)
						/* Physical map associated
						 * with this address map */
#define		vm_map_vsize(map)	((map)->vm_size)
						/* size of the virtual
						 * address space */
/*
 *	Submap object.  Must be used to create memory to be put
 *	in a submap by vm_map_submap.
 */
extern struct vm_object	*vm_submap_object;

/*
 * Macro to check for multiple faultwaiters, to be used in places that
 * assert vme_faultwait in a map entry (vm_faultwait, vm_mape_kfaultwait).
 * If not doing locking debug, we just no-op the definition.
 */

#ifdef VM_MAP_LOCKING_DEBUG
#define vm_mape_multiple_faultwaiters_check(VME) {				\
extern int vm_mape_multiple_faultwaiters_panic_flag;				\
extern int vm_debugging_print_interval;						\
static long multiple_faultwaiters=0;						\
int _pp;									\
	if ((VME)->vme_faultwait) {						\
		multiple_faultwaiters++;					\
		_pp=vm_debugging_print_interval;				\
		if (_pp>1) _pp=(multiple_faultwaiters%_pp);			\
		if (vm_mape_multiple_faultwaiters_panic_flag) _pp=1;		\
		if (_pp==1) printf(						\
"multiple fault waiters detected at line %d in file %s\n",			\
			__LINE__,__FILE__);					\
		if (vm_mape_multiple_faultwaiters_panic_flag)			\
			panic("multiple fault waiters detected");		\
	}									\
}
#else /* not VM_MAP_LOCKING_DEBUG */
#define vm_mape_multiple_faultwaiters_check(VME)
#endif

/*
 * Increment the fault count.  A positive fault count means that this
 * entry can't be mutated.  
 * It is a likely locking bug if we try to increment the fault count
 * while no one is a lock reader on the map in which this map entry
 * is located.  It makes no rational sense to increment the faults
 * count while there is a mutator holding the exclusive lock on the
 * map in which the map entry is located.  Detect and report these
 * logic errors so that bugs can be found and addressed.
 */

#ifdef VM_MAP_LOCKING_DEBUG

#define vm_mape_fault_check(VME) {							\
extern int vm_debugging_print_interval;							\
extern int vm_mape_fault_check_panic_flag;						\
static long vm_mape_fault_check_lock_logic=0;						\
vm_map_t map;										\
int _pp;										\
	map=((VME)->vme_map);								\
	if (map) if (!lock_readers(&map->vm_lock)) {					\
		vm_mape_fault_check_lock_logic++;					\
		_pp=vm_debugging_print_interval;					\
		if (_pp>1) _pp=vm_mape_fault_check_lock_logic%_pp;			\
		if (vm_mape_fault_check_panic_flag) _pp=1;				\
		if (_pp==1) {								\
			if (lock_holder(&map->vm_lock)) {				\
				printf(							\
"vm_mape_fault: we are lock_holder(&map->vm_lock)\n\tat line %d in file %s\n",		\
				__LINE__,__FILE__);					\
			} else if (lock_locked(&map->vm_lock)) {			\
				printf(							\
"vm_mape_fault: someone has lock_locked(&map->vm_lock)\n\tat line %d in file %s\n",	\
				__LINE__,__FILE__);					\
			} else {							\
				printf(							\
"vm_mape_fault: there are no lock_readers(&map->vm_lock)\n\tat line %d in file %s\n",	\
				__LINE__,__FILE__);					\
			}								\
		if (vm_mape_fault_check_panic_flag) panic(				\
"vm_mape_fault: lock logic assertion failure");						\
		}									\
	}										\
}
#else
#define vm_mape_fault_check(VME)
#endif

#define vm_mape_fault(VME) {						\
	spl_t s=splsched();						\
	simple_lock(&(VME)->vme_faultlock);		 		\
	vm_mape_fault_check(VME);					\
	(VME)->vme_faults++;						\
	simple_unlock(&(VME)->vme_faultlock);				\
	splx(s);							\
}

#ifdef VM_MAP_LOCKING_DEBUG
#define vm_mape_kfault_check(VME) {							\
extern int vm_debugging_print_interval;							\
extern int vm_mape_fault_check_panic_flag;						\
static long vm_mape_fault_check_lock_logic=0;						\
vm_map_t map;										\
int _pp;										\
	map=((VME)->vme_map);								\
	if (map) if (!lock_holder(&map->vm_lock)) {					\
		vm_mape_fault_check_lock_logic++;					\
		_pp=vm_debugging_print_interval;					\
		if (_pp>1) _pp=vm_mape_fault_check_lock_logic%_pp;			\
		if (vm_mape_fault_check_panic_flag) _pp=1;				\
		if (_pp==1) {								\
			printf(								\
"vm_mape_kfault: we are not lock_holder(&map->vm_lock)\n\tat line %d in file %s\n",	\
				__LINE__,__FILE__);					\
			if (vm_mape_fault_check_panic_flag) panic(			\
"vm_mape_kfault: lock logic assertion failure");					\
		}									\
	}										\
}

#define vm_mape_kfault(VME) {						\
	spl_t s=splsched();						\
	simple_lock(&(VME)->vme_faultlock);		 		\
	vm_mape_kfault_check(VME);					\
	(VME)->vme_faults++;						\
	simple_unlock(&(VME)->vme_faultlock);				\
	splx(s);							\
}

#else /* not VM_MAP_LOCKING_DEBUG */
#define vm_mape_kfault(VME) vm_mape_fault(VME)
#endif



/*
 * Fault completion.  Wakeup anybody waiting for this entry.
 * Raise our IPL to splsched() to assure we complete our work
 * including unlocking the simple lock in a timely manner.  
 * Any faultwaiters we wake up need to wait for us to release
 * the simple lock before they can proceed, and if we manage
 * to clear the vme_faults count BEFORE they sleep, and we
 * still have the lock held, they can get us into trouble if
 * we get blocked still holding the lock and they manage to
 * dispose of our map entry (and lock_terminate the lock).  It
 * can (and does) happen if we are interruptible/schedulable.
 */
#define vm_mape_faultdone(VME) {					\
	register int waiters = 0;					\
	spl_t s = splsched();						\
	simple_lock(&(VME)->vme_faultlock);				\
	if (--(VME)->vme_faults == 0 && (VME)->vme_faultwait) {		\
		waiters = 1;						\
		(VME)->vme_faultwait = 0;				\
	} 								\
	simple_unlock(&(VME)->vme_faultlock);				\
	splx(s);							\
	if (waiters) thread_wakeup((vm_offset_t)(VME));			\
}

/*
 * Use vm_mape_map_locked_check to check that a map entry is in a
 * map (points to a map structure, not a null pointer) and that
 * the map is locked for exclusive access.  If the panic flag is
 * set we panic on a violation, otherwise print warning messages
 * and keep going.
 */
#ifdef VM_MAP_LOCKING_DEBUG
#define vm_mape_map_locked_check(VME) {							\
extern int vm_debugging_print_interval;							\
extern int vm_mape_map_locked_check_panic_flag;						\
static long vm_mape_map_locked_check_failed=0;						\
vm_map_t map=((VME)->vme_map);								\
int _pp=0;										\
	if (map) { if (!lock_holder(&map->vm_lock)) _pp=1; } else _pp=1;		\
	if (_pp) {									\
		vm_mape_map_locked_check_failed++;					\
		_pp=vm_debugging_print_interval;					\
		if (_pp>1) _pp=vm_mape_map_locked_check_failed%_pp;			\
		if (vm_mape_map_locked_check_panic_flag) _pp=1;				\
		if (_pp==1) {								\
			if (map) printf(						\
"vm_mape_map_locked_check: we are not lock_holder(&map->vm_lock)\n\tat line %d in file %s\n",	\
				__LINE__,__FILE__);					\
			else printf(							\
"vm_mape_map_locked_check: NULL pointer (VME)->vme_map\n\tat line %d in file %s\n",	\
				__LINE__,__FILE__);					\
		}									\
		if (vm_mape_map_locked_check_panic_flag) panic (			\
"vm_mape_map_locked_check: map not locked or not found");				\
	}										\
}
#else /* not VM_MAP_LOCKING_DEBUG */
#define vm_mape_map_locked_check(VME)
#endif

/*
 * Since SLOCK_LOCKED() doesn't really do what we need in lockmode 0
 * or 1, we will define our own FAULT_LOCKED() macro to directly test
 * the fault lock in a map entry.  If the low order bit is set, the
 * lock is locked (at least on Alpha).  In lockmode 0 or 1 the lock
 * is never really locked, but that's OK on a non-SMP system.
 */

#define FAULT_LOCKED(VME) (((VME)->vme_faultlock)&1)

/*
 * Use the vm_mape_inuse_check to check the state of a map entry.  We
 * should invoke this macro after we *really* get the write lock on
 * the map in which the map entry is contained to verify that it (the
 * map entry) is in a "safe" state, and report on violations.  Provide
 * the ability to set a global variable that will cause panic on any
 * state inconsistency (e.g., map entry still in use, other waiters,
 * someone else holding the map lock).  Typically, the code path up
 * to the point where vm_mape_inuse_check() is invoked will have taken
 * the write lock on the map and then will have invoked vm_faultwait()
 * to assure there are NO FAULTERS active in the map entry.  Since if
 * the map entry is (simple) locked when we get here, that means that
 * someone is presumably using it (e.g., turning off the fault count),
 * we check for that along with other things.
 *
 * Use the vm_mape_1user_check similarly when there should be exactly
 * one user of the map entry, which is yourself.  Works whether you
 * are holding the write lock or not, if it detects a problem it will
 * report whether you were holding the write lock on the map, but not
 * holding the write lock is not considered a problem that needs to be
 * reported if there are no other problems found.
 */

#ifdef VM_MAP_LOCKING_DEBUG
#define vm_mape_inuse_check(VME) { 										\
extern int vm_debugging_print_interval;										\
extern int vm_mape_inuse_check_panic_flag;									\
static long vm_mape_inuse_check_faults=0;									\
static long vm_mape_inuse_check_waiters=0;									\
static long vm_mape_inuse_check_holder=0;									\
static long vm_mape_inuse_check_locked=0;									\
vm_map_t map;													\
unsigned int faults;												\
unsigned int faultwait;												\
unsigned int locked;												\
int _pp=vm_debugging_print_interval;										\
int _pf=0;													\
locked=FAULT_LOCKED(VME);											\
faults=(VME)->vme_faults;											\
faultwait=(VME)->vme_faultwait;											\
if (faults || faultwait || locked) {										\
	if (vm_mape_inuse_check_panic_flag) _pp=1;								\
	if (locked) {												\
		_pf=1;												\
		vm_mape_inuse_check_locked++;									\
		if (_pp) if ((_pp==1) || (vm_mape_inuse_check_locked%_pp==1))					\
			printf(											\
"vm_mape_inuse_check: found LOCKED (VME)->vme_faultlock\n\tat line %d in file %s\n",				\
				__LINE__,__FILE__);								\
	}													\
	if ((VME)->vme_faults || faults) {									\
		_pf=1;												\
		vm_mape_inuse_check_faults++;									\
		if (_pp) if ((_pp==1) || (vm_mape_inuse_check_faults%_pp==1))					\
			printf(											\
"vm_mape_inuse_check: faults = %d at entry, (VME)->vme_faults = %d\n\tat line %d in file %s\n",			\
				faults,(VME)->vme_faults,__LINE__,__FILE__);					\
	}													\
	if ((VME)->vme_faultwait || faultwait) {								\
		_pf=1;												\
		vm_mape_inuse_check_waiters++;									\
		if (_pp) if ((_pp==1) || (vm_mape_inuse_check_waiters%_pp==1))					\
			printf(											\
"vm_mape_inuse_check: faultwait set at entry, (VME)->vme_faultwait = %d\n\tat line %d in file %s\n",		\
				 (VME)->vme_faultwait,__LINE__,__FILE__);					\
	}													\
	if (map=((VME)->vme_map)) if (!lock_holder(&map->vm_lock)) {						\
		_pf=1;												\
		vm_mape_inuse_check_holder++;									\
		if (_pp) if ((_pp==1) || (vm_mape_inuse_check_holder%_pp==1))					\
			printf(											\
"vm_mape_inuse_check: not lock_holder(&((VME)->vme_map)->vm_lock)\n\tat line %d in file %s\n",			\
				__LINE__,__FILE__);								\
	}													\
	if (vm_mape_inuse_check_panic_flag && _pf)								\
			panic("vm_mape_inuse_check: assertion violation detected");				\
	}													\
}
#else /* not VM_MAP_LOCKING_DEBUG */
#define vm_mape_inuse_check(VME)
#endif

/* tpb -- based on vm_mape_inuse_check */

#ifdef VM_MAP_LOCKING_DEBUG
#define vm_mape_1user_check(VME) { 										\
extern int vm_debugging_print_interval;										\
extern int vm_mape_inuse_check_panic_flag;									\
static long vm_mape_1user_check_faults=0;									\
static long vm_mape_1user_check_waiters=0;									\
static long vm_mape_1user_check_holder=0;									\
static long vm_mape_1user_check_locked=0;									\
vm_map_t map;													\
unsigned int faults;												\
unsigned int faultwait;												\
unsigned int locked;												\
int _pp=vm_debugging_print_interval;										\
int _pf=0;													\
locked=FAULT_LOCKED(VME);											\
faults=(VME)->vme_faults;											\
faultwait=(VME)->vme_faultwait;											\
if ((faults != 1) || faultwait || locked) {									\
	if (vm_mape_inuse_check_panic_flag) _pp=1;								\
	if (locked) {												\
		_pf=1;												\
		vm_mape_1user_check_locked++;									\
		if (_pp) if ((_pp==1) || (vm_mape_1user_check_locked%_pp==1))					\
			printf(											\
"vm_mape_1user_check: found LOCKED (VME)->vme_faultlock\n\tat line %d in file %s\n",				\
				__LINE__,__FILE__);								\
	}													\
	if (((VME)->vme_faults != 1) || (faults != 1)) {							\
		_pf=1;												\
		vm_mape_1user_check_faults++;									\
		if (_pp) if ((_pp==1) || (vm_mape_1user_check_faults%_pp==1))					\
			printf(											\
"vm_mape_1user_check: faults = %d at entry, (VME)->vme_faults = %d\n\tat line %d in file %s\n",			\
				faults,(VME)->vme_faults,__LINE__,__FILE__);					\
	}													\
	if ((VME)->vme_faultwait || faultwait) {								\
		_pf=1;												\
		vm_mape_1user_check_waiters++;									\
		if (_pp) if ((_pp==1) || (vm_mape_1user_check_waiters%_pp==1))					\
			printf(											\
"vm_mape_1user_check: faultwait set at entry, (VME)->vme_faultwait = %d\n\tat line %d in file %s\n",		\
				 (VME)->vme_faultwait,__LINE__,__FILE__);					\
	}													\
	if (map=((VME)->vme_map)) if (!lock_holder(&map->vm_lock)) {						\
		_pf=1;												\
		vm_mape_1user_check_holder++;									\
		if (_pp) if ((_pp==1) || (vm_mape_1user_check_holder%_pp==1))					\
			printf(											\
"vm_mape_1user_check: not lock_holder(&((VME)->vme_map)->vm_lock)\n\tat line %d in file %s\n",			\
				__LINE__,__FILE__);								\
	}													\
	if (vm_mape_inuse_check_panic_flag && _pf)								\
			panic("vm_mape_1user_check: assertion violation detected");				\
	}													\
}
#else /* not VM_MAP_LOCKING_DEBUG */
#define vm_mape_1user_check(VME)
#endif

#if defined(_KERNEL) && defined(_USE_KERNEL_PROTOS)
/*
 * Prototypes
 */

struct processor_affinity_group;

/*
 *	Exported procedures that operate on vm_map_t.
 */

extern void		vm_map_init(void);	/* Initialize the module */

extern vm_map_t vm_map_create(pmap_t pmap, vm_offset_t min, vm_offset_t max, boolean_t pageable);

extern vm_map_t		vm_map_fork(vm_map_t, 	/* Create a map in the image*/
			 boolean_t,		 /* of an existing map */
			 struct processor_affinity_group *);

extern void		vm_map_reference(	/* Gain a reference to*/
			 vm_map_t);		/* an existing map */

extern void		vm_map_deallocate(	 /* Lose a reference */
			 vm_map_t);
						 /* Enter a mapping */
extern kern_return_t	vm_map_enter(vm_map_t, vm_offset_t *, vm_size_t,
			 vm_offset_t, boolean_t, struct vm_object *,
			 vm_offset_t, boolean_t, vm_prot_t,
			 vm_prot_t, vm_inherit_t);

extern kern_return_t	vm_map_remove(		 /* Deallocate a region */
			 vm_map_t, vm_offset_t, vm_offset_t);

extern kern_return_t	vm_map_exec(		/* remove all but keep-on-exec
						 * mappings */
			 vm_map_t, vm_offset_t, vm_offset_t);

extern kern_return_t	vm_map_protect(		/* Change protection */
			 vm_map_t, vm_offset_t, vm_offset_t,
			 vm_prot_t, boolean_t);

extern kern_return_t	vm_map_inherit(		/* Change inheritance */
			 vm_map_t, vm_offset_t, vm_offset_t, vm_inherit_t);

extern kern_return_t	vm_map_find(  		/* Old allocation primitive */
			 vm_map_t, struct vm_object *, vm_offset_t, vm_offset_t *,
			 vm_size_t, boolean_t);

extern void		vm_map_print(  		/* Debugging: print a map */
			 vm_map_t, int);

extern void		vm_map_copy_discard(  	/* Discard a copy without*/
		         vm_map_copy_t);		/* using it */

extern void		vm_map_exit(vm_map_t);	/* Delete exiting proc's 
						 * virtual memory */

extern boolean_t
	vm_map_check_protection(vm_map_t, vm_offset_t, vm_offset_t, vm_prot_t);

extern kern_return_t
	vm_map_entry_create(vm_map_t, vm_map_entry_t *),
	vm_map_pageable(vm_map_t map, vm_offset_t start,
			vm_offset_t end, vm_prot_t access_type),
	vm_map_clip_end(vm_map_t, vm_map_entry_t, vm_offset_t),
	vm_map_clip_start(vm_map_t, vm_map_entry_t, vm_offset_t),
	vm_map_machine_attribute(vm_map_t, vm_offset_t, vm_size_t,
			vm_machine_attribute_t, vm_machine_attribute_val_t *),
	vm_map_pageable_orig(vm_map_t, vm_offset_t, vm_offset_t, vm_prot_t),
	vm_map_pageable_work(vm_map_t, vm_offset_t, vm_offset_t, vm_prot_t),
	vm_map_space(vm_map_t, vm_offset_t *, vm_size_t, vm_offset_t,
			u_long, vm_map_entry_t *, vm_map_t *),
	vm_map_swapout(vm_map_t, int *),
	vm_map_copy_overwrite(vm_map_t, vm_offset_t, vm_map_copy_t, boolean_t),
	vm_map_copyin(vm_map_t, vm_offset_t, vm_size_t, boolean_t,
			vm_map_copy_t *),
	vm_map_copyout(vm_map_t, vm_offset_t *, vm_map_copy_t),
	vm_map_delete(vm_map_t, vm_offset_t, vm_offset_t, boolean_t),
	u_map_entry_unmap(vm_map_entry_t, vm_offset_t, vm_size_t),
	vm_map_entry_split(vm_map_t, vm_map_entry_t, vm_offset_t, vm_offset_t),
	vm_map_pageable(vm_map_t, vm_offset_t, vm_offset_t, vm_prot_t);

extern void
	vm_map_entry_coalesce(vm_map_entry_t, vm_map_entry_t),
	vm_map_entry_delete(vm_map_t, vm_map_entry_t),
	vm_map_entry_dispose(vm_map_entry_t);

extern int
	vm_map_swapin(vm_map_t);

#ifdef	VM_SKIPLIST
extern boolean_t vm_mesl_search(vm_map_t, vm_offset_t, vm_map_entry_t *,
		vm_map_entry_t, boolean_t);
extern void vm_mesl_insert(vm_map_t, vm_map_entry_t, vm_map_entry_t);
extern void vm_mesl_remove(vm_map_t, vm_map_entry_t);
#endif	/* VM_SKIPLIST */

#endif /* defined(_KERNEL) && defined(_USE_KERNEL_PROTOS) */

#ifdef __cplusplus
}
#endif

#endif	/* !_VM_VM_MAP_H_ */
