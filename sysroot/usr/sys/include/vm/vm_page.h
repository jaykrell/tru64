/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: vm_page.h,v $
 * Revision 4.2.76.5  2004/05/07  22:31:50  Jason_Hennessey
 * 	Introduce fixes for simultaneous promoters of ubc bigpages
 * 	97689
 *
 * Revision 4.2.76.4  2004/03/09  21:16:18  Jeffrey_Cilley
 * 	Added vm_bigpg_lock_gh and vm_bigpg_unlock_gh prototypes.
 * 	QAR 97689.
 *
 * Revision 4.2.76.3  2003/10/09  22:07:20  Jeffrey_Cilley
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree v51bsupportos
 *     User Revision:  Jeffrey_Cilley_newubc_br:4.2.77.1 Local Ancestor:4.2.76.1
 *    Merge Revision:  v51bsupportos_br:4.2.76.2
 *   Common Ancestor:  4.2.76.1
 * 	[2003/10/09  22:01:11  Jeffrey_Cilley]
 *
 * 	Add definition for ENFORCE_PAGE_LINK_CHECKS_l
 * 	[2003/10/03  20:28:57  Jeffrey_Cilley]
 *
 * Revision 4.2.76.2  2003/09/22  20:22:34  Ross_Knepper
 * 	Add new map entry parameter to vm_map_ssm_bigpg().  It
 * 	is needed to calculate the range for l3gh.
 * 
 * Revision 4.2.76.1  2003/04/29  15:09:39  Ross_Knepper
 * 	Add prototype for vm_ubc_pg_alloc() to support a different
 * 	allocation policy for the UBC which is more friendly toward
 * 	overflowing to remote MADs.
 * 
 * Revision 4.2.65.18  2002/07/24  13:46:02  Jeffrey_Cilley
 *      Rearranged vm_page structure.  Made pv_bits an integer.  The UBC
 *      uses the vm_object lock to protect the page structure.  The VM side
 *      uses the pg_lock to protect the pv_bits field.  If pv_bits shares
 *      an integer with another value, it can cause word tear problems.
 * 
 * Revision 4.2.65.17  2002/07/17  18:30:34  Andrew_Moskal
 * 	Correct vm_page field alignment.
 * 	In VP_TO_BIGPG and VP_TO_PVP, use embedded mid value.
 * 
 * Revision 4.2.65.16  2002/07/16  19:42:39  Renny_Shen
 * 	Removed assumption that the first PMR is managed memory
 * 	from the VP_TO_BIGPG and VP_TO_PVP macros
 * 
 * Revision 4.2.65.15  2002/07/10  21:39:54  Ross_Knepper
 * 	Add vm_page.pg_lru bit.  Rearrange pg_size and pg_dnext/pg_dprev
 * 	for better cache performance.
 * 
 * Revision 4.2.65.14  2002/06/04  14:49:28  Ross_Knepper
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree wcalphaos
 *     User Revision:  Ross_Knepper_rdwr_br:4.2.70.1 Local Ancestor:4.2.65.11
 *    Merge Revision:  wcalphaos_br:4.2.65.13
 *   Common Ancestor:  4.2.65.11
 * 	Fix typo in type for pg_dnext.
 * 
 * Revision 4.2.65.13  2002/06/03  22:01:00  Ross_Knepper
 * Merge Information:  Visual Merge: User specified default merge the submit tree wcalphaos
 *     User Revision:  Ross_Knepper_rdwr_br:4.2.70.1 Local Ancestor:4.2.65.11
 *    Merge Revision:  wcalphaos_br:4.2.65.12
 *   Common Ancestor:  4.2.65.11
 * 	[2002/06/03  22:00:57  Ross_Knepper]
 * 	Move pg_lnext,pg_lprev down into second cache block in vm_page.
 * 	Add code to BUSY and HOLD macros for pg_writebusy, pg_nreaders,
 * 	and pg_nwriters.
 * 	[2002/06/03  22:00:12  Ross_Knepper]
 * 
 * Revision 4.2.65.12  2002/06/03  21:05:58  Peter_Keilty
 * 	Add mid to page structure.
 * 	Move object and offset into first cache block.
 * 
 * Revision 4.2.70.1  2002/06/03  18:42:52  Peter_Keilty
 * 	Add mid to page structure.
 * 	Move object and offset into first cache block.
 * 
 * Revision 4.2.65.11  2002/04/01  20:57:46  Ross_Knepper
 * 	Change prototype for vm_seg_bigpg_info_alloc() to
 * 	vm_ubc_bigpg_info_alloc().
 * 	Changed prototype for vm_bigpg_downgrade() to
 * 	vm_bigpg_downgrade_common() and added macros
 * 	vm_bigpg_downgrade() and vm_bigpg_downgrade_nowait().
 * 
 * Revision 4.2.65.10  2002/03/27  14:05:29  David_Bernardo
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree wcalphaos
 *     User Revision:  David_Bernardo_wcalphaos_nightly_br:4.2.72.1 Local Ancestor:4.2.65.8
 *    Merge Revision:  wcalphaos_br:4.2.65.9
 *   Common Ancestor:  4.2.65.8
 * 	[2002/03/26  15:10:38  David_Bernardo]
 * 	Fix syntax in pgl_insert_tail and pgl_insert so that the check for
 * 	"p" pointers works with all compiler settings.
 * 	[2002/03/26  15:08:48  David_Bernardo]
 * 
 * Revision 4.2.65.9  2002/03/26  01:48:15  Renny_Shen
 * 	Added prototype for vm_gsm_page_tester()
 * 
 * Revision 4.2.65.8  2002/03/05  21:42:40  David_Bernardo
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree wcalphaos
 *     User Revision:  David_Bernardo_wcalphaos_nightly_br:4.2.73.1 Local Ancestor:4.2.65.6
 *    Merge Revision:  wcalphaos_br:4.2.65.7
 *   Common Ancestor:  4.2.65.6
 * 	[2002/03/05  20:23:20  David_Bernardo]
 * 	Restore embedded pv_entry in the vm_page structure.
 * 	[2002/03/05  19:40:36  David_Bernardo]
 * 
 * Revision 4.2.65.7  2002/03/05  19:39:37  Julie_Dewandel
 * 	Removed extern declaration of vm_page_color_bucket_count
 * 	since this variable is no longer used by the kernel.
 * 
 * Revision 4.2.65.6  2002/02/19  18:34:04  David_Bernardo
 * 	Move bpg_siblings and bpg_size to fix word tearing problems. QAR 92050.
 * 
 * Revision 4.2.65.5  2002/01/28  21:17:46  Matthew_McGrath
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree wcalphaos
 *     User Revision:  Matthew_McGrath_QAR91432_br:4.2.74.1 Local Ancestor:4.2.65.3
 *    Merge Revision:  wcalphaos_br:4.2.65.4
 *   Common Ancestor:  4.2.65.3
 * 
 * Revision 4.2.65.4  2002/01/25  22:02:33  Ross_Knepper
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree Ross_Knepper:SharedBP
 *     User Revision:  Ross_Knepper_sbp_br:4.2.74.1 Local Ancestor:4.2.65.3
 *    Merge Revision:  Ross_Knepper_SharedBP_br:4.2.71.7
 *   Common Ancestor:  4.2.65.3
 * 	[2002/01/11  18:49:44  Ross_Knepper]
 * 	Add new vm_page bit pg_promotion for ubc.
 * 	Add several new prototypes: vm_bigpage_copy,
 * 	vm_seg_bigpg_info_alloc, vm_bigpg_set_busy, vm_bigpg_set_empty.
 * 	[2002/01/11  15:58:57  Ross_Knepper]
 * 	[2002/01/11  18:50:22  Ross_Knepper]
 * 	Added prototype for vm_pageget_fault
 * 	Modified prototype for vm_map_seg_bigpg again :-)
 * 	Distinguish big (vs base) page wait.
 * 	[2002/01/11  15:34:43  David_Bernardo]
 * 	Changed prototype for vm_map_seg_bigpg
 * 	[2001/12/18  18:02:02  Julie_Dewandel]
 * 	Added the PG_HOLDRES flag.
 * 	[2001/12/17  17:58:11  Greg_Bellows]
 * 	Fix conditionals in VALIDATE_SIBLINGS.
 * 	[2001/12/14  18:57:03  Andrew_Moskal]
 * 	Added PG_FILLARRAY flag, used by vm_anon_page_alloc.
 * 	Adjusted vm_map_bigpg prototype for new argument list.
 * 	[2001/12/13  21:23:16  Greg_Bellows]
 * 	Add big page aware pg_busy abstractions, VM_PAGE_(SET/CLEAR)_BUSY, to
 * 	facilitate bpg_busy management and trapping invalid transitions.
 * 	[2001/12/11  20:16:05  Andrew_Moskal]
 * 	Added function prototypes for new routines
 * 	[2001/12/04  21:04:36  Julie_Dewandel]
 * 
 * Revision 4.2.74.1  2002/01/24  14:22:24  Matthew_McGrath
 * 	Moved the pg_pvlist pointer within the vm_page structure to keep it
 * 	from being zeroed in a VM_PAGE_CLEAR.  This allows devmap entries
 * 	to survive when other, unrelated mappings are eliminated.  [QAR 91432]
 * 
 * Revision 4.2.65.3  2001/11/16  20:15:16  Ross_Knepper
 * 	Modified macros to follow new naming conventions.
 * 	[2001/11/14  18:12:18  Julie_Dewandel]
 * 	Add VALIDATE_SIBLINGS and VALIDATE_PAGEALIGNED.
 * 	[2001/11/13  17:58:47  Andrew_Moskal]
 * 	Added pg_bpp field to vm_page structure and added
 * 	some more bigpage macros
 * 	[2001/11/13  15:34:30  Julie_Dewandel]
 * 
 * Revision 4.2.65.2  2001/11/01  22:40:50  Ross_Knepper
 * 	Big pages infrastructure
 * 
 * Revision 4.2.67.6  2001/10/31  19:55:24  David_Bernardo
 * 	Make the size and mask fields in bigpg_data unsigned long.
 * 
 * Revision 4.2.67.5  2001/10/30  16:05:54  David_Bernardo
 * 	Update bigpage macros for new pmr layout.
 * 
 * Revision 4.2.67.4  2001/10/26  15:54:37  Ross_Knepper
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree Ross_Knepper:bp
 *     User Revision:  Ross_Knepper_sbp_br:4.2.68.1 Local Ancestor:4.2.67.2
 *    Merge Revision:  Ross_Knepper_bp_br:4.2.67.3
 *   Common Ancestor:  4.2.67.2
 * 	Add a bpg_abort bit to bigpage structure for use in swap.
 * 
 * Revision 4.2.67.3  2001/10/25  13:03:23  Andrew_Moskal
 * 	Add VALIDATE_PRIMARY.
 * 	Change return type of vm_bigpg_hold to boolean_t.
 * 
 * Revision 4.2.67.2  2001/10/23  12:59:29  Andrew_Moskal
 * 	Make VM_PAGE_HOLD_(INCR/DECR) and VM_PAGE_RELEASE big-page aware.
 * 	Add big-page aware VM_PAGE_WAIT_COMMON.  Make VM_PAGE_WAIT and
 * 	VM_PAGE_WAIT_LOCKED jackets around VM_PAGE_WAIT_COMMON.  VM_PAGE_WAIT
 * 	replaces vm_page_wait; alias vm_page_wait to it.  VM_PAGE_WAIT_LOCKED
 * 	obseletes the versions of such in u_mape_anon.c and u_mape_ssm.c.
 * 
 * Revision 4.2.67.1  2001/10/19  15:13:02  David_Bernardo
 * 	Increase size of vm_page structure, add new locks. Promote all fields
 * 	to ints. Added bigpage macros. Added new fields.
 * 
 * Revision 4.2.65.1  2001/10/03  17:44:41  David_Bernardo
 * 	Added pg_invrepl bit to vm_page structure.  It is used to mark
 * 	replicate pages that are currently being invalidated and should not
 * 	be used.
 * 	In the vm_page structure, moved the pg_bad bit to its own
 * 	private word since updates to it were not synchronized with
 * 	updates to other bits in that same word [QAR 89504].
 * 	Add pg_hold abstractions, VM_PAGE_HOLD_(INCR/DECR), to facilitate
 * 	trapping invalid transitions.
 * 	Major restructure of the vm_page structure along with
 * 	the addition of bigpage data structures and definitions.
 * 	Added assertion checking when adding and removing vm_page structures
 * 	from linked lists. Link fields are now cleared on removal.
 * 
 * Revision 4.2.57.2  2000/12/08  00:27:22  Ross_Knepper
 * 	Add a new flag to pass into vm_pg_free(), NEW_PAGE.  This
 * 	parameter is passed from vm_page_create() when new pages are
 * 	added to the system.
 * 
 * Revision 4.2.57.1  2000/09/06  12:56:39  Greg_Bellows
 * Merge Information:  Non-Visual Merge: User specified tree ericos.nightly
 *     User Revision:  yankeeos_nightly:4.2.44.10 Local Ancestor: n/a
 *    Merge Revision:  ericos_nightly:4.2.54.1
 *   Common Ancestor:  4.2.44.10
 * 
 * Revision 4.2.54.1  2000/07/07  17:40:11  Greg_Bellows
 * 	Added pg_exempt bit to vm_page structure.  This bit indicates
 * 	whether a page is allocated to an exempt region or not.
 * 
 * Revision 4.2.44.10  2000/03/16  23:03:13  Shashi_Mangalat
 * 	Changes to support vm_page/pvh merge.
 * 
 * Revision 4.2.44.9  2000/01/12  22:57:46  Dean_Gagne
 * 	For error survivability project, convert 64bit pg_phys_addr to 32bit
 * 	pg_page_pfn and 32bit flags field.  Change all accesses to pg_phys_addr
 * 	to use the page_to_phys macro.
 * 
 * Revision 4.2.44.8  1999/08/16  22:19:23  Stephen_Corbin
 * 	Support for per-MAD Object/Offset Hash Queues.
 * 	[1999/08/16  22:06:59  Stephen_Corbin]
 * 
 * Revision 4.2.44.7  1999/08/05  20:47:14  Shashi_Mangalat
 * 	Remove include of vm_perf.h.
 * 	[1999/08/04  13:23:19  Shashi_Mangalat]
 * 
 * Revision 4.2.44.6  1999/05/06  19:35:27  Shashi_Mangalat
 * 	Merge of STEELOS_BL21:STEELOS_BL23
 * 	 Revision 4.2.26.8  1999/03/19  20:06:40  Ernie_Petrides
 * 	 Fix declarations of simple lock fields.
 * 	[1999/05/06  19:30:01  Shashi_Mangalat]
 * 
 * Revision 4.2.44.5  1999/05/03  19:28:49  David_Anderson
 * 	Add vm_policy argument to vm_page_alloc() and vm_zeroed_page_alloc().
 * 	[1999/04/30  13:43:30  David_Anderson]
 * 
 * Revision 4.2.44.4  1999/03/09  23:49:40  Shashi_Mangalat
 * 	Merge of STEELOS_BL20:STEELOS_BL21
 * 	 Revision 4.2.26.7  1998/12/16  20:45:03  David_Anderson
 * 	 Added VM_PAGE_TESTED and VM_PAGE_UNTESTED states for boot time
 * 	 memory allocations. (QAR 66337)
 * 	 Revision 4.2.26.6  1998/11/25  23:35:18  Shashi_Mangalat
 * 	 VM/NUMA scalability enhancements.
 * 	[1999/03/09  23:44:43  Shashi_Mangalat]
 * 
 * Revision 4.2.44.3  1998/10/22  20:05:39  Nitin_Karkhanis
 * 	NUMA Support: Swap objects are now hashed into separate hash
 * 	buckets. Delete prototype for vm_page_hash_remove. This
 * 	function has been replaced by function vm_swap_hash_remove.
 * 	[1998/09/29  15:48:53  Nitin_Karkhanis]
 * 
 * Revision 4.2.44.2  1998/08/26  12:44:00  James_Woodward
 * 	Merge of numaproj and zulu
 * 	[1998/07/29  20:18:53  James_Woodward]
 * 
 * Revision 4.2.39.4  1998/07/22  14:31:22  Shashi_Mangalat
 * 	Merge of NUMAPROJ with STEELOS_BL16.
 * 	[1998/07/22  14:17:12  Shashi_Mangalat]
 * 
 * Revision 4.2.39.3  1998/07/08  15:42:05  Shashi_Mangalat
 * 	Modify vm_page_lookup() for supporting page replication.
 * 	[1998/07/08  14:10:53  Shashi_Mangalat]
 * 
 * Revision 4.2.26.5  1998/04/17  13:47:32  Jeff_Colburn
 * 	Remove reference to vm_page_queue_free which no longer exists.
 * 	[1998/04/15  13:17:32  Jeff_Colburn]
 * 
 * Revision 4.2.39.2  1998/04/09  21:14:54  Shashi_Mangalat
 * 	Add support for per-mad (Memory Affinity Domain) freelist.
 * 	[1998/04/09  19:37:30  Shashi_Mangalat]
 * 
 * Revision 4.2.26.4  1997/08/19  20:58:46  Patrick_ORourke
 * 	Remove pkva, no longer needed.
 * 	[1997/08/19  16:17:38  Patrick_ORourke]
 * 
 * Revision 4.2.26.3  1997/04/10  19:45:19  Shashi_Mangalat
 * 	Add memory holes support
 * 	[1997/04/09  20:51:22  Shashi_Mangalat]
 * 
 * Revision 4.2.26.2  1996/05/01  18:03:54  Larry_Woodman
 * 	Merge from bravos.bl2
 * 	[1996/05/01  17:39:08  Larry_Woodman]
 * 
 * Revision 4.2.22.4  1996/03/10  15:38:22  Ray_Lanza
 * 	Merge of Platinum BL8 to BL11 pass 1 changes
 * 	[1996/03/10  15:20:50  Ray_Lanza]
 * 
 * Revision 4.2.11.7  1996/01/30  21:52:55  Patrick_ORourke
 * 	Put back pg_pkva (removed in swap submit).
 * 	[1996/01/30  18:46:38  Patrick_ORourke]
 * 
 * Revision 4.2.22.3  1995/11/10  23:44:16  Ray_Lanza
 * 	Merge of PTOS BL8
 * 	[1995/11/10  23:26:53  Ray_Lanza]
 * 
 * Revision 4.2.22.2  1995/10/25  20:02:18  Ray_Lanza
 * 	Initial __alpha conditional evaluation and changes
 * 	[1995/10/25  19:32:08  Ray_Lanza]
 * 
 * Revision 4.2.11.6  1995/08/30  17:53:25  Shashi_Mangalat
 * 	Change single global vm_page_lock to a hashed lock table to reduce
 * 	contention.
 * 	[1995/08/29  21:28:54  Shashi_Mangalat]
 * 
 * Revision 4.2.11.5  1995/06/30  11:50:59  Patrick_ORourke
 * 	Merge to latest
 * 	[1995/06/28  20:34:08  Patrick_ORourke]
 * 	Merge to ptos.nightly
 * 	[1995/06/23  18:22:44  Patrick_ORourke]
 * 	Swap structure reorganization
 * 	[1995/06/22  17:18:45  Patrick_ORourke]
 * 
 * Revision 4.2.11.4  1995/05/24  15:15:33  Ashoke_Rampuria
 * 	Merged with bl4 of ptlite.
 * 	Revision 4.2.13.4  1995/04/25  20:00:14  Ashoke_Rampuria
 * 	Replaced pg_app in vm_page structure with pg_pkva.
 * 	[1995/04/25  18:36:18  Ashoke_Rampuria]
 * 	Revision 4.2.13.3  1995/03/17  19:11:44  Ashoke_Rampuria
 * 	Included vm_perf.h. Removed extern for vm_page_wire_count.
 * 	[1995/03/17  17:07:43  Ashoke_Rampuria]
 * 
 * Revision 4.2.11.3  1995/02/28  21:50:58  Ashoke_Rampuria
 * 	merge of Platinum Lite BL1 changes
 * 
 * Revision 4.2.13.2  1995/01/30  19:51:45  Ashoke_Rampuria
 * 	Removed include for zalloc.h.
 * 	[1995/01/27  21:49:46  Ashoke_Rampuria]
 * 
 * Revision 4.2.11.2  1994/12/16  15:37:00  Ashoke_Rampuria
 * 	Declare vm_page_array as extern.
 * 	[1994/12/15  18:47:48  Ashoke_Rampuria]
 * 
 * Revision 4.2.7.5  1994/02/10  19:58:59  Ernie_Petrides
 * 	Remove UNIX_LOCKS dependency.
 * 	[1994/02/10  16:20:22  Ernie_Petrides]
 * 
 * Revision 4.2.7.4  1993/10/22  21:52:49  Shashi_Mangalat
 * 	Modified pg_hold from an 8 bit field to an int as it doesn't save any
 * 	space and will save access time on alpha.
 * 	[1993/10/22  21:05:25  Shashi_Mangalat]
 * 
 * Revision 4.2.7.3  1993/08/06  23:08:45  Shashi_Mangalat
 * 	Change calls to usimple_*() to the correct simple_*() routines.
 * 	[1993/08/06  22:29:52  Shashi_Mangalat]
 * 
 * Revision 4.2.7.2  1993/05/28  19:31:13  Shashi_Mangalat
 * 	Fixed vm_free_check_po() debug macro from panicing the system.
 * 	[1993/05/28  19:03:35  Shashi_Mangalat]
 * 
 * Revision 4.2.4.5  1992/12/11  15:39:21  Robert_McGuirk
 * 	Add support for zeroed page allocator.
 * 	[92/12/11  14:22:42  Robert_McGuirk]
 * 
 * Revision 4.2.4.4  92/06/16  06:08:49  Ron_Widyono
 * 	Fix problem with turning UNIX_LOCKS on with no NCPUS>0 or RT_PREEMPT.
 * 	[92/06/16  06:00:54  Ron_Widyono]
 * 
 * Revision 4.2.4.3  92/05/05  13:22:00  Al_Delorey
 * 	From Silver: AG_BL6_4
 * 	[92/05/05  13:21:29  Al_Delorey]
 * 
 * Revision 4.2.5.2  92/05/05  10:06:21  devbld_gsf
 * 	First AG_BL6_4 version.  Moved from Ag baselevel delivery tree.
 * 
 * Revision 4.2.2.3  92/04/24  09:32:26  Robert_Picco
 * 	Dirty Page Prewrite exported interfaces
 * 	[92/04/16  09:39:46  Robert_Picco]
 * 
 * Revision 4.2.2.2  92/02/26  15:55:23  Charles_Briggs
 * 	UBC merge
 * 	[92/02/23  14:23:37  Charles_Briggs]
 * 	UBC merge.
 * 	[92/02/22  15:11:22  Charles_Briggs]
 * 
 * Revision 4.2  91/09/19  23:08:07  devbld
 * 	Adding ODE Headers
 * 
 * 
 * $EndLog$
 * 
 */
/*	
 *	@(#)$RCSfile: vm_page.h,v $ $Revision: 4.2.76.5 $ (DEC) $Date: 2004/05/07 22:31:50 $
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
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */
/*
 *	File:	vm/vm_page.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Copyright (C) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Resident memory system definitions.
 */

#ifndef	_VM_VM_PAGE_H_
#define _VM_VM_PAGE_H_

#include <mach/boolean.h>
#include <mach/vm_prot.h>
#include <mach/vm_param.h>
#include <kern/macro_help.h>
#include <vm/vm_anonpage.h>
#include <vm/vm_vppage.h>
#include <kern/lock.h>
#include <machine/vmparam.h>
#include <kern/rad.h>
#include <vm/vm_numa.h>

struct vm_object;
struct vm_numa_policy;
typedef struct vm_bigpage vm_bigpage_t;

#define	VM_MAXPIO	4
#define	VM_PAGE_PRIVATE	2		/* size of private info */

struct vm_page {
	struct vm_page	*pg_pnext,	/* resident page management */
			*pg_pprev;
	struct vm_page  *pg_onext,	/* all pages in same object */
			*pg_oprev;	
	struct	vm_page	*pg_hnext,	/* Hash byte object offset */
			*pg_hprev;
	struct vm_object
			*pg_object;	/* which object am I in */
	vm_offset_t	pg_offset;	/* offset in object */

	/* 64-byte cache block boundary */

	struct	vm_page	*pg_lnext,	/* UBC lru */
			*pg_lprev;
				
        unsigned int	pg_wire_count;  /* page wire count */
        unsigned int
                        pg_free:1,      /* page is on free list  */
                        pg_busy:1,      /* page is in busy  */
                        pg_wait:1,      /* someone is waiting for page */
                        pg_error:1,     /* an error was detected */
                        pg_dirty:1,     /* page must be cleaned */
                        pg_zeroed:1,    /* page has been zeroed */
                        pg_exempt:1,    /* page is in exempt region */
			pg_empty:1,	/* page has not been initialized */
	                pg_invrepl:1,   /* replicate page being invalidated */
			pg_malloc:1,	/* page is owned by contig_malloc */
			pg_gsm:1,	/* page is part of a GSM region */
			pg_promotion:1,	/* page is becoming a big page */
			pg_writebusy:1,	/* base is busy because of a write */
			pg_lru:1,	/* page is on the LRU */
			pg_unused:18;	/* bits available for future use */
	unsigned short	pg_reserved;    /* reserved for paging subsystem */
	unsigned short	pg_iocnt;	/* I/O transfer against page */
        unsigned int    pg_hold;        /*
                                         * reason page can't be touched
                                         * manipulated by paging subsystem.
				         */
	unsigned int	pg_nreaders;	/* # of readers of this page */
	unsigned int	pg_nwriters;	/* # of writers of this page */
	unsigned int	pg_size;	/* page size represented as a gh */
	unsigned int	pg_pvbits;	/* ref and mod bits for pv entries
					 * VM uses the pg_lock to protect
					 * this field.  The UBC modifies the
					 * page structure under a different
					 * lock. NOTE: This can cause a word
					 * tear problem.
					 */
        union {                         /* object pager specific info */
                struct vm_anonpage _apg;/* anonymous memory pages */
                struct vm_vppage  _vppg;/* vnode memory pages */
                vm_offset_t             /* must be = to max size of above */
                        _pg_private[VM_PAGE_PRIVATE];
        } _upg;

	/* 64-byte cache block boundary */

	unsigned short	pg_dnext,	/* indices of dirty pages in bigpage */
			pg_dprev;
        unsigned int    pg_page_pfn;    /* page frame number */
	unsigned int	pg_mid;		/* mid the page is in */
	unsigned int	pg_bad;		/* denotes a bad page */

	/*
	 * Physical to Virtual ("pv") mappings information for this page.
	 * The next 3 fields have the same layout as a pv_entry, don't
	 * change them unless you also change the pv_entry structure.
	 */
	vm_offset_t	pg_va;		/* va for this mapping */
	pmap_t		pg_pmap;	/* pmap/pmap_seg/pmap_ssm for this mapping */
	struct pv_entry	*pg_pvnext;	/* ptr to next pv_entry */

	simple_lock_data_t    
			pg_lock;	/* lock for vm_page */
	simple_lock_data_t    
			pg_ubc_lock;	/* lock for ubc */
	vm_bigpage_t   *pg_bpp;		/* bigpage structure for this page */
};

typedef struct vm_page	*vm_page_t;

#define pg_private 	_upg._pg_private

#define VM_PAGE_NULL	((vm_page_t) 0)
#define VM_PAGE_EMPTY	((vm_page_t) 1)

#ifdef	_KERNEL

/*
 *			  B I G   P A G E S
 *
 *   Data structure definitions and function prototypes for the 
 *   Variable Page Size project follow.
 */

/*
 * Big page macros
 */

#define VP_TO_BIGPG(PP, SIZE, BPP)				\
MACRO_BEGIN							\
	vm_page_array_t	_vpa;					\
	vm_offset_t	_pa, _start;				\
	long		_offset;				\
	int		_ii, _mgd_i, _mid;			\
	pmr_t		*_mrp;					\
	(BPP) = 0;						\
	if (((SIZE) > 0) && ((SIZE) < NUM_BIGPG_SIZES)) {	\
	   _pa = page_to_phys(PP) & ~bigpg_data[SIZE].mask;	\
	   _mid = (PP)->pg_mid;					\
           _mrp = pmr_data.pmr_rad_table[_mid].pmr_table;	\
           for (_ii = 0, _mgd_i = 0;				\
		_ii < pmr_data.pmr_rad_table[_mid].pmr_count;	\
		_ii++) {					\
                if((_pa >= _mrp->pmr_base) &&			\
                   (_pa < _mrp->pmr_base + _mrp->pmr_size)) {	\
                        break;					\
                }						\
            	if(_mrp->pmr_type == PMR_MANAGED)		\
            		_mgd_i++;				\
                _mrp++;						\
           }							\
           _vpa = &rad_id_to_rad(_mid)->rad_mad->md_vpa[_mgd_i];\
	   if (_vpa->va_bigpg) {				\
	       _start = _vpa->va_start & ~bigpg_data[1].mask;	\
	       _offset = _pa - _start;				\
	       if (_offset >= 0)				\
	       (BPP) = &_vpa->va_bigpg[atop(_offset) >>		\
		       bigpg_data[1].pageshift];		\
           }							\
	}							\
MACRO_END

/*
 * This macro is a shortcut version of the preceeding one. This
 * macro takes a vm_page and returns a pointer to the vm_bigpage 
 * structure.  The vm_page structure passed in does not have to
 * be the primary.
 */
#define VP_TO_BPP(PP, BPP)					\
MACRO_BEGIN							\
	vm_page_t	_primary;				\
        VP_TO_PRIMARY(PP,_primary);				\
	(BPP) = _primary->pg_bpp;				\
MACRO_END

#define VP_TO_PVP(PP, SIZE, PVP)				\
MACRO_BEGIN							\
	vm_offset_t	_pa;					\
	vm_page_array_t	_vpa;					\
	long		_offset;				\
	int		_ii, _mgd_i=0, _mid;			\
	pmr_t		*_mrp;					\
	_pa = page_to_phys(PP) & ~bigpg_data[SIZE].mask;	\
	_mid = (PP)->pg_mid;					\
        _mrp = pmr_data.pmr_rad_table[_mid].pmr_table;		\
        for (_ii = 0;						\
             _ii < pmr_data.pmr_rad_table[_mid].pmr_count;	\
	     _ii++) {						\
             if ((_pa >= _mrp->pmr_base) &&		        \
                 (_pa < _mrp->pmr_base + _mrp->pmr_size)) {	\
                        break;                                  \
            }							\
            if(_mrp->pmr_type == PMR_MANAGED)			\
            	_mgd_i++;					\
	    _mrp++;						\
	}							\
        _vpa = &rad_id_to_rad(_mid)->rad_mad->md_vpa[_mgd_i];	\
	_offset = _pa - _vpa->va_start;				\
	(PVP) = 0;						\
	if (_offset >= 0)					\
	    (PVP) = &_vpa->va_vmp[atop(_offset)];		\
MACRO_END

/*
 * This macro is a shortcut version of the preceeding one. This
 * macro can be used if you know that PP is part of a big page.
 */
#define VP_TO_PRIMARY(PP, PRIMARY)                              \
MACRO_BEGIN							\
        vm_offset_t     _ndx;                                   \
        _ndx = (PP)->pg_page_pfn &                              \
               (bigpg_data[(PP)->pg_size].mask >> PAGE_SHIFT);  \
        (PRIMARY) = (PP) - _ndx;                                  \
MACRO_END

/*
 * The following macro takes a pointer to a vm_page structure and
 * returns both the primary for that page and a pointer to the 
 * bigpage structure for that page.  Page size is determined by 
 * looking at the pg_size field.
 */
#define GET_BIGPG_STRUCTS(PP, PVP, BPP)				\
MACRO_BEGIN							\
	VP_TO_PRIMARY(PP, PVP);					\
	(BPP) = (PVP)->pg_bpp;					\
MACRO_END


#define	VM_BIGPAGE_CHECK	1

#if	VM_BIGPAGE_CHECK

/*
 *  Ensure the specified value is a base page size multiple.
 */
#define VALIDATE_PAGEALIGNED(VALUE)					\
MACRO_BEGIN								\
	if ((VALUE) & PAGE_MASK) {					\
		printf("non-page aligned value %P\n", (VALUE));	\
		panic("non-page aligned value");			\
	}								\
MACRO_END

/*
 *  Ensure the specified page structure is the primary page
 *  structure for the aggregate page.
 */
#define VALIDATE_PRIMARY(PP)					\
MACRO_BEGIN							\
	vm_page_t	_ppp;					\
								\
	VP_TO_PRIMARY(PP, _ppp);				\
	if ((PP) != _ppp) {					\
		printf("non-primary vm_page %P\n", (PP));	\
		panic("non-primary vm_page structure");		\
	}							\
MACRO_END

/*
 *  Ensure the set of consecutive pages starting with the
 *  specified page are all siblings of the same big page.
 */
#define VALIDATE_SIBLINGS(PP, COUNT)					\
MACRO_BEGIN								\
	if ((COUNT) > 1) {						\
	    if (!(PP)->pg_size ||					\
	        ((((PP)->pg_page_pfn &					\
		   (bigpg_data[(PP)->pg_size].mask >> PAGE_SHIFT)) +	\
	          (COUNT) - 1) >= bigpg_data[(PP)->pg_size].basepcnt)) { \
		printf("non-sibling pages, vm_page %P, count %d\n",	\
		       (PP), (COUNT));					\
		panic("non-sibling pages");				\
	    }								\
	} else if ((COUNT) != 1) {					\
		printf("invalid sibling count %d\n", (COUNT));		\
		panic("invalid sibling count");				\
	}								\
MACRO_END

#else	/* VM_BIGPAGE_CHECK */

#define VALIDATE_PAGEALIGNED(VALUE)

#define VALIDATE_PRIMARY(PP)

#define VALIDATE_SIBLINGS(PP, COUNT)

#endif	/* VM_BIGPAGE_CHECK */

/* 
 * The vm_bigpage data structure contains information about the big page
 * it represents, as specified by the bpg_size field.  All fields in this 
 * structure represent a count of the number of base pages within the big 
 * page that have the attribute specified. 
 * 
 * Note: there will be one of these structures allocated for each 
 * minimum sized big page in the system.
 */
struct vm_bigpage {
	simple_lock_data_t	
			bpg_lock;	/* simple lock */
	unsigned int	bpg_wired;	/* user or kernel (not lw wired) */
	unsigned int	bpg_mapped;	/* # pages mapped somewhere */
	unsigned int	bpg_busy;	/* # pages with pg_busy set */
	unsigned int	bpg_hold;	/* # pages with pg_hold set */
	unsigned int	bpg_dirty;	/* # pages with pg_dirty set */
	unsigned int  
			bpg_contains_bad:1, /* at least 1 base page is bad */
			bpg_wait:1,	/* there are waiters for this page */
			bpg_error:1,	/* at least 1 base pg had IO errors */
			bpg_abort:1,	/* need to abort the IO transaction */
			bpg_pad:28;	/* for future growth */
	unsigned int	bpg_pfn;	/* page frame for bigpage start */
	unsigned int	bpg_size;	/* size of this big page */
	unsigned int	bpg_siblings[3];/* free state of each sibling page */
	unsigned short	bpg_dhead,	/* start and end of dirty list */
			bpg_dtail;
	unsigned int	bpg_pad2[2];	/* pad to 64 bytes */

};
/*
 * The bigpage_data data structure contains information for each valid 
 * granularity hint ('gh') value for a given CPU architecture.  This
 * data structure is used to create an array which is indexed by the
 * 'gh' value.  If the default values specified in kern/const_data.c 
 * are not correct, they are rewritten during system boot.
 */
typedef struct bigpage_data {
    unsigned long size;		/* page size in bytes */
    unsigned long mask;		/* mask of insignificant addr bits */
    unsigned int pageshift;	/* shift to get # base size pages in page */
    unsigned int basepcnt;	/* # base size pages in page */
    unsigned int indexcnt;	/* # of pages of gh=1 in page */
    unsigned int sibcnt;	/* # of pages of (gh-1) size in page */
} bigpage_data_t;

#define	NUM_BIGPG_SIZES	4		/* Only 4 page sizes for Alpha */

/* The following array is defined in const_data.c */
extern REPLICATED bigpage_data_t bigpg_data[];

/*
 * Some definitions dependent upon the bigpg_data array:
 */
#define BASE_PGSIZE             (bigpg_data[0].size)
#define BASE_PGALIGN(VA)        ((VA) & ~bigpg_data[0].mask)

#define BIGPG_MINSIZE           (bigpg_data[1].size)
#define BIGPG_MINMASK           (bigpg_data[1].mask)
#define BIGPG_MINALIGN(VA)      ((VA) & ~BIGPG_MINMASK)

#define BIGPG_MAXMASK           (bigpg_data[NUM_BIGPG_SIZES-1].mask)
#define BIGPG_MAXSIZE           (bigpg_data[NUM_BIGPG_SIZES-1].size)

/*
 * The following value represents the default amount of memory that
 * should be maintained on each of the bigpage free lists.  Coalescing
 * to the next larger page size won't be done if the amount of memory
 * consumed by free pages on the list is below this value.
 */
#define VM_BIGPG_THRESH_DEFAULT (2 * get_cache_size(master_cpu))

/*
 * Debug macros for bigpages
 */
#define BPINFO		0x01
#define BPALLOC		0x02
#define GHLOCK		0x04
#define BPFAULT		0x08
#define BPPMAP		0x10
#define BPDEBUG(flags,msg)	{		\
	if (bpdebug & (flags)) printf msg;	\
}

extern int bpdebug;

#define BP_ASSERT(STMT)				\
MACRO_BEGIN					\
	if (!(STMT))				\
		panic("Bigpage Assert Failure");\
MACRO_END


/*
 * ------------------- End of Bigpage Info ------------------
 */


/*
 * Flags to vm_pg_alloc()/vm_bigpg_alloc()/vm_alloc_obj_page()
 */
#define PG_NOSTEAL      0x00    /* don't reclaim clean pages */
#define PG_STEAL        0x01    /* okay to reclaim clean pages */
#define PG_ZERO         0x02    /* need zeroed page */
#define PG_WAITOK       0x04    /* wait for the specified page */
#define PG_SIZE_INSIST  0x08    /* must get page size specified */
#define PG_MID_INSIST   0x10    /* must get page on specified mid */
#define PG_LOCKED	0x20	/* lock is held on function call */

/*
 * Additional flags passed exclusively to anon allocation routines.
 */
#define PG_FILLARRAY	0x1000	/* allocate anon and fill anon array 
				   on page alloc */
#define PG_HOLDRES	0x2000	/* mark page held when found resident */

#define VM_PG_ALLOC()	\
	vm_pg_alloc(VM_COLOR_PRIVATE, VM_POLICY_NULL, PG_STEAL)
#define VM_PAGE_LOOKUP(OBJ, OFF) \
	vm_page_lookup((vm_object_t)OBJ, OFF, MID_ANY)

#define VM_PAGE_UNTESTED  ((vm_offset_t)0xfeeddeafbabebeef)
#define VM_PAGE_TESTED    ((vm_offset_t)0)

/*
 * Flags to vm_pg_free()
 */
#define NEW_PAGE	-2	/* a new page introduced to the system */
#define PRE_HASH	-1	/* already present in the hash table */
#define DONT_HASH	0	/* do not insert "" */
#define INS_HASH	1	/* insert */

/*
 *	Each pageable resident page falls into one of three lists:
 *
 *	free	
 *		Available for allocation now.
 *	inactive
 *		Not referenced in any map, but still has an
 *		object/offset-page mapping, and may be dirty.
 *		This is the list of pages that should be
 *		paged out next.
 *	active
 *		A list of pages which have been placed in
 *		at least one physical map.  This list is
 *		ordered, in LRU-like fashion.
 */

extern int	vm_managed_pages;		/* managed page count */

#define	page_to_phys(PP)	alpha_ptob((PP)->pg_page_pfn)
#define vm_page_to_phys(PAGE)	page_to_phys(PAGE)

#undef BUCKET_COUNTS	/* turning this on takes up lots of memory space */

#ifdef BUCKET_COUNTS
#define ZERO_BUCKET_COUNT(bkp)	(bkp)->bk_count = 0
#define INC_BUCKET_COUNT(bkp)	(bkp)->bk_count++
#define DEC_BUCKET_COUNT(bkp)	(bkp)->bk_count--
#else
#define ZERO_BUCKET_COUNT(bkp)
#define INC_BUCKET_COUNT(bkp)
#define DEC_BUCKET_COUNT(bkp)
#endif

/*
 * vm_page_hash:
 *
 * Distributes the object/offset key pair among hash buckets.
 *
 * NOTE: To get a good hash function, the bucket count should be a power of two.
 *
 * The vm_page_lookup() routine, which provides for fast (virtual memory
 * object, offset) to page lookup, employs the following hash table.  The
 * vm_page_{insert,remove} routines install and remove associations in the
 * table.  [This table is often called the virtual-to-physical, or VP,
 * table.]
 */
typedef struct vm_page_bucket {
	simple_lock_data_t	bk_lock;
	vm_page_t		bk_pages;
#ifdef BUCKET_COUNTS
	long			bk_count;
#endif
} vm_page_bucket_t;

#define	VM_PAGE_LOCK(PP, S) 						\
MACRO_BEGIN								\
	S = splvm();							\
	simple_lock(&(PP)->pg_lock);					\
MACRO_END

#define	VM_PAGE_UNLOCK(PP, S) 						\
MACRO_BEGIN								\
	simple_unlock(&(PP)->pg_lock);					\
	splx(S);							\
MACRO_END

/*
 * Force building with pg_hold checking enabled.
 */
#define VM_PAGE_HOLD_CHECK	1

/*
 * A hold on a page typically signifies activity for a context autonomous to
 * memory management's immediate control.  The vm_page structure pg_hold field
 * tracks the number of such contexts.  A non-zero value indicates that the
 * associated page must remain resident.  It informs the paging subsystem
 * that the page is not to be freed.  Moreover, the page should be left on
 * the active list.
 *
 * The application and subsequent release of a hold constitute complimentary
 * actions that transpire in balanced pairs.  Outside the scope of vm_page
 * structure (re-)initialization, these actions should be accomplished by
 * respectively incrementing and decrementing the count.  VM_PAGE_HOLD_INCR
 * and VM_PAGE_HOLD_DECR facilitate performing these operations with/without
 * added consistency checks.  Simply setting the count to 1 or 0 requires
 * absolute assurance of a known state.  Blindly assuming such can lead to
 * count inconsistencies that will likely yield a crash.
 *
 * If the page being held/unheld is part of a big-page and this is/was the
 * first/last hold on the page, then the bpg_hold field within the associated
 * vm_bigpage structure is incremented/decremeted accordingly.  VM_PAGE_HOLD_INC
 * and VM_PAGE_HOLD_DECR facilitate performing these operations with/without
 * added consistency checks.
 *
 * The PAGE_UNHELD parameter facilitates validating state when added checks
 * are enabled.  Support for such relies upon the compiler's optimization
 * abilities to suppress superfluous code generation when the parameter
 * constitutes a compile-time FALSE.  If the performance of a read-modify-write
 * memory reference (incrementing/decrementing) vs a write only reference (=)
 * is a concern, the PAGE_UNHELD parameter could be used to generate a direct
 * assignment rather than an increment/decrement for the non-debug known
 * state case.
 *	
 * Note: With respect to maintaining residency, holding a page differs from
 *       wiring a page, in that the latter effectively hides the page from
 *       the paging subsystem, whereas the former does not.
 */

#if	VM_PAGE_HOLD_CHECK

#define VM_PAGE_HOLD_INCR(PP,PAGE_UNHELD)			\
MACRO_BEGIN							\
if (PAGE_UNHELD) {						\
	if ((PP)->pg_hold) {					\
		printf("vm_page %P is already held\n", PP);	\
		panic("pg_hold - page already held");		\
	}							\
}								\
	if (!(PP)->pg_hold && (PP)->pg_size) {			\
		vm_bigpage_t	*_bpp;				\
								\
		VP_TO_BPP(PP, _bpp);				\
		_bpp->bpg_hold++;				\
		if (_bpp->bpg_hold >				\
		    bigpg_data[(PP)->pg_size].basepcnt) {	\
			printf("vm_page %P vm_bigpage %P "	\
			       "hold count exceeded\n",		\
			       PP, _bpp);			\
			panic("bpg_hold - count exceeded");	\
		}						\
	}							\
	(PP)->pg_hold++;					\
MACRO_END

#define VM_PAGE_HOLD_DECR(PP,PAGE_UNHELD)			\
MACRO_BEGIN							\
	if (!(PP)->pg_hold) {					\
		printf("vm_page %P hold count underflow\n",PP);\
		panic("pg_hold - underflow");			\
	}							\
	(PP)->pg_hold--;					\
	if ((PP)->pg_hold == 0 && ((PP)->pg_nwriters || (PP)->pg_nreaders)) { \
		printf("bad nreader/nwriter count pp=%P\n", PP);\
		panic("hold is zero but readers+writers != 0");	\
	}							\
if (PAGE_UNHELD) {						\
	if ((PP)->pg_hold) {					\
		printf("vm_page %P is still held\n", PP);	\
		panic("pg_hold - page still held");		\
	}							\
}								\
	if (!(PP)->pg_hold && (PP)->pg_size) {			\
		vm_bigpage_t	*_bpp;				\
								\
		VP_TO_BPP(PP, _bpp);				\
		if (!_bpp->bpg_hold) {				\
			printf("vm_page %P vm_bigpage %P "	\
			       "hold count underflow\n",	\
			       PP, _bpp);			\
			panic("bpg_hold - underflow");		\
		}						\
		_bpp->bpg_hold--;				\
	}							\
MACRO_END

#else	/*VM_PAGE_HOLD_CHECK */

#define VM_PAGE_HOLD_INCR(PP,PAGE_UNHELD)			\
MACRO_BEGIN							\
	if (!(PP)->pg_hold && (PP)->pg_size) {			\
		vm_bigpage_t	*_bpp;				\
								\
		VP_TO_BPP(PP, _bpp);				\
		_bpp->bpg_hold++;				\
	}							\
	(PP)->pg_hold++						\
MACRO_END

#define VM_PAGE_HOLD_DECR(PP,PAGE_UNHELD)			\
MACRO_BEGIN							\
	(PP)->pg_hold--;					\
	if (!(PP)->pg_hold && (PP)->pg_size) {			\
		vm_bigpage_t	*_bpp;				\
								\
		VP_TO_BPP(PP, _bpp);				\
		_bpp->bpg_hold--;				\
	}							\
MACRO_END

#endif	/* VM_PAGE_HOLD_CHECK */

#define	VM_PAGE_RELEASE(PP)				\
MACRO_BEGIN						\
	spl_t		_s;				\
	vm_page_t	_ppp;				\
							\
	VP_TO_PRIMARY(PP, _ppp);			\
	VM_PAGE_LOCK(_ppp, _s);				\
	VM_PAGE_HOLD_DECR(PP, FALSE);			\
	VM_PAGE_UNLOCK(_ppp, _s);			\
MACRO_END

/*
 * Force building with pg_busy/bpg_busy checking enabled.
 */
#define VM_PAGE_BUSY_CHECK	1

/*
 * The vm_page structure pg_busy flag signifies the page is in transition.
 * The setting and subsequent clearing of busy constitute complimentary
 * actions that typically indicate initiation/completion of I/O activity
 * against the page.
 *
 * The (single-bit) exclusive nature of the flag constrains usage to only
 * one execution context at any given instance.  To prevent uncoordinated
 * interaction failures, ignoring current state and blindly setting or
 * clearing busy requires absolute assurance of a known context.
 *
 * If the page is part of a big-page, then the bpg_busy field within the
 * associated vm_bigpage structure is incremented/decremeted accordingly.
 * VM_PAGE_SET_BUSY and VM_PAGE_CLEAR_BUSY facilitate performing these
 * operations with/without added consistency checks.
 *
 * The IGNORE_STATE parameter facilitates skipping state validation when
 * added checks are enabled.  Support for such relies upon the compilier's
 * optimization abilities to suppress superfluous code generation when the
 * parameter constitutes a compile-time constant; state enforcement when
 * TRUE and conditional manipulation when FALSE (the typical case).
 */

#if	VM_PAGE_BUSY_CHECK

#define VM_PAGE_SET_BUSY(PP,IGNORE_STATE)			\
MACRO_BEGIN							\
if (!(IGNORE_STATE)) {						\
	if ((PP)->pg_busy) {					\
		printf("vm_page %P is already busy\n", PP);	\
		panic("pg_busy - page already busy");		\
	}							\
	if ((PP)->pg_writebusy) {				\
		printf("vm_page %P is already writebusy\n", PP);\
		panic("pg_busy - page already writebusy");	\
	}							\
}								\
if ((IGNORE_STATE) ? !(PP)->pg_busy : TRUE) {			\
	if ((PP)->pg_size) {					\
		vm_bigpage_t	*_bpp;				\
								\
		VP_TO_BPP(PP, _bpp);				\
		_bpp->bpg_busy++;				\
		if (_bpp->bpg_busy >				\
		    bigpg_data[(PP)->pg_size].basepcnt) {	\
			printf("vm_page %P vm_bigpage %P "	\
			       "busy count overflow\n",		\
			       PP, _bpp);			\
			panic("bpg_busy - overflow");		\
		}						\
	}							\
	(PP)->pg_busy = TRUE;					\
}								\
MACRO_END

#define VM_PAGE_CLEAR_BUSY(PP,IGNORE_STATE)			\
MACRO_BEGIN							\
if (!(IGNORE_STATE)) {						\
	if (!(PP)->pg_busy) {					\
		printf("vm_page %P is not busy\n",PP);		\
		panic("pg_busy - page is not busy");		\
	}							\
}								\
if ((IGNORE_STATE) ? (PP)->pg_busy : TRUE) {			\
	(PP)->pg_busy = FALSE;					\
	(PP)->pg_writebusy = FALSE;				\
	if ((PP)->pg_size) {					\
		vm_bigpage_t	*_bpp;				\
								\
		VP_TO_BPP(PP, _bpp);				\
		if (!_bpp->bpg_busy) {				\
			printf("vm_page %P vm_bigpage %P "	\
			       "busy count underflow\n",	\
			       PP, _bpp);			\
			panic("bpg_busy - underflow");		\
		}						\
		_bpp->bpg_busy--;				\
	}							\
}								\
MACRO_END

#else	/*VM_PAGE_BUSY_CHECK */

#define VM_PAGE_SET_BUSY(PP,IGNORE_STATE)			\
MACRO_BEGIN							\
	if (!(PP)->pg_busy) {					\
		if ((PP)->pg_size) {				\
			vm_bigpage_t	*_bpp;			\
								\
			VP_TO_BPP(PP, _bpp);			\
			_bpp->bpg_busy++;			\
		}						\
		(PP)->pg_busy = TRUE;				\
	}							\
MACRO_END

#define VM_PAGE_CLEAR_BUSY(PP,IGNORE_STATE)			\
MACRO_BEGIN							\
	if ((PP)-pg_busy) {					\
		(PP)->pg_busy = FALSE;				\
		(PP)->pg_writebusy = FALSE;			\
		if ((PP)->pg_size) {				\
			vm_bigpage_t	*_bpp;			\
								\
			VP_TO_BPP(PP, _bpp);			\
			_bpp->bpg_busy--;			\
		}						\
	}							\
MACRO_END

#endif	/* VM_PAGE_BUSY_CHECK */

#if	VM_FREE_CHECK

#define	vm_free_check_pp(PP) if ((PP)->pg_free)	panic("vm_free_check: ");

#define	vm_free_check_po(PG,FLD) 					\
		if (&((struct vm_page *) 0)->pg_pnext == 		\
			&((struct vm_page *) 0)->pg_/**/FLD/**/next) {	\
			if ((PG)->pg_pnext) vm_free_check_pp((PG)->pg_pnext);\
			if ((PG)->pg_pprev) vm_free_check_pp((PG)->pg_pprev);\
		}

#else
#define	vm_free_check_pp(PP)
#define	vm_free_check_po(PG,FLD)
#endif	/* VM_FREE_CHECK */

/*
 * The vm_page structure pg_busy field indicates the respective page is in
 * transition.  VM_PAGE_WAIT and VM_PAGE_WAIT_LOCKED facilitate waiting for
 * the condition to clear.  The only difference between the two is locking
 * strategy.  The former locks the page context upon entry, the latter assumes
 * the page context has already been locked.  They are implemented as jackets
 * around a common core, VM_PAGE_WAIT_COMMON.  The LOCK parameter makes this
 * feasible.  It relies upon the compiler's optimization abilities to suppress
 * superfluous code generation when the parameter constitutes a compile-time
 * FALSE.
 *
 * It is assumed that the caller has has asserted a hold against the page.  
 * Otherwise the page may be gone by the time the thread is scheduled to run.
 *
 */
#define VM_PAGE_WAIT_COMMON(PP,S,LOCK)				\
MACRO_BEGIN							\
	vm_page_t	_ppp;					\
								\
	VP_TO_PRIMARY(PP, _ppp);				\
if (LOCK) {							\
	VM_PAGE_LOCK(_ppp, S);					\
}								\
	if ((PP)->pg_size) {					\
		vm_bigpage_t	*_bpp;				\
								\
		VP_TO_BPP(PP, _bpp);				\
		while (_bpp->bpg_busy) {			\
			_bpp->bpg_wait = 1;			\
			assert_wait_mesg((vm_offset_t)_bpp,	\
					 FALSE, "bpg_wait");	\
			VM_PAGE_UNLOCK(_ppp, S);		\
			thread_block();				\
			VM_PAGE_LOCK(_ppp, S);			\
		}						\
	}  else {						\
		while ((PP)->pg_busy) {				\
			(PP)->pg_wait = 1;			\
			assert_wait_mesg((vm_offset_t)(PP),	\
					 FALSE, "pg_wait");	\
			VM_PAGE_UNLOCK(_ppp, S);		\
			thread_block();				\
			VM_PAGE_LOCK(_ppp, S);			\
		}						\
	}							\
if (LOCK) {							\
	VM_PAGE_UNLOCK(_ppp,S);					\
}								\
MACRO_END

#define VM_PAGE_WAIT_LOCKED(PP,S)				\
MACRO_BEGIN							\
	VM_PAGE_WAIT_COMMON(PP, S, FALSE);			\
MACRO_END

#define	VM_PAGE_WAIT(PP)					\
MACRO_BEGIN							\
	spl_t	_s;						\
								\
	VM_PAGE_WAIT_COMMON(PP, _s, TRUE);			\
MACRO_END

#define	vm_page_wait(PP) VM_PAGE_WAIT(PP)

#define ENFORCE_PAGE_LINK_CHECKS_p 0
#define ENFORCE_PAGE_LINK_CHECKS_o 1
#define ENFORCE_PAGE_LINK_CHECKS_h 1
#define ENFORCE_PAGE_LINK_CHECKS_l 0

#define pgl_insert_tail(Q,PP,FLD) 					\
MACRO_BEGIN								\
	vm_free_check_pp(PP);						\
        if ((ENFORCE_PAGE_LINK_CHECKS_##FLD) &&				\
	    (((PP)->pg_##FLD##next != VM_PAGE_NULL) ||			\
	     ((PP)->pg_##FLD##prev != VM_PAGE_NULL)))			\
		panic("pgl_insert_tail: links not null");		\
	if ((Q) == VM_PAGE_NULL) {					\
		(Q) = (PP);						\
		(PP)->pg_##FLD##next = 					\
			(PP)->pg_##FLD##prev = (PP);			\
	}								\
	else {								\
		register vm_page_t PG;					\
		PG = (Q);						\
		vm_free_check_pp(PG);					\
		vm_free_check_po(PG,FLD);				\
		PG->pg_##FLD##prev->pg_##FLD##next = (PP);		\
		(PP)->pg_##FLD##prev = PG->pg_##FLD##prev;		\
		PG->pg_##FLD##prev = (PP);				\
		(PP)->pg_##FLD##next = PG;				\
	}								\
MACRO_END

#define pgl_insert(Q,PP,FLD) 						\
MACRO_BEGIN								\
	vm_free_check_pp(PP);						\
        if ((ENFORCE_PAGE_LINK_CHECKS_##FLD) &&				\
	    (((PP)->pg_##FLD##next != VM_PAGE_NULL) ||			\
	     ((PP)->pg_##FLD##prev != VM_PAGE_NULL)))			\
		panic("pgl_insert: links not null");			\
	if ((Q) == VM_PAGE_NULL) {					\
		(Q) = (PP);						\
		(PP)->pg_##FLD##next = 					\
			(PP)->pg_##FLD##prev = (PP);			\
	}								\
	else {								\
		register vm_page_t PG;					\
		PG = (Q);						\
		vm_free_check_pp(PG);					\
		vm_free_check_po(PG,FLD);				\
		PG->pg_##FLD##prev->pg_##FLD##next = (PP);		\
		(PP)->pg_##FLD##prev = PG->pg_##FLD##prev;		\
		PG->pg_##FLD##prev = (PP);				\
		(PP)->pg_##FLD##next = PG;				\
		(Q) = (PP);						\
	}								\
MACRO_END

#define pgl_remove(Q,PP,FLD) 						\
MACRO_BEGIN								\
	vm_free_check_pp(PP);						\
	if ((Q) == VM_PAGE_NULL)					\
	    panic("pgl_remove: remove from empty Q");			\
	if ((PP)->pg_##FLD##next == (PP))  (Q) = VM_PAGE_NULL;		\
	else {								\
		if ((Q) == (PP)) (Q) = (PP)->pg_##FLD##next;		\
		vm_free_check_po(PP,FLD);				\
		(PP)->pg_##FLD##next->pg_##FLD##prev =			\
			(PP)->pg_##FLD##prev;				\
		(PP)->pg_##FLD##prev->pg_##FLD##next =			\
			(PP)->pg_##FLD##next;				\
	}								\
	(PP)->pg_##FLD##next = (PP)->pg_##FLD##prev = VM_PAGE_NULL;	\
MACRO_END

#define	VM_PAGE_CHECK(PP)

/*
 * Prototypes
 */
struct vm_control;
struct vm_policy;
struct memory_affinity_domain;

#define vm_bigpg_downgrade(obj, offset, new_gh)		\
        vm_bigpg_downgrade_common(obj, offset, new_gh, PG_WAITOK);

#define vm_bigpg_downgrade_nowait(obj, offset, new_gh)		\
        vm_bigpg_downgrade_common(obj, offset, new_gh, 0);



extern vm_page_t
	vm_page_lookup(struct vm_object *, vm_offset_t, int),
	vm_page_alloc(struct vm_object *, vm_offset_t, struct vm_policy *),
	vm_zeroed_page_alloc(struct vm_object *, vm_offset_t, 
		struct vm_policy *),
	vm_page_clean(vm_page_t),
	vm_pg_alloc(int, struct vm_policy *, int),
	vm_zeroed_pg_alloc(int, boolean_t),
	vm_page_remove_repl(struct vm_object *, vm_offset_t),
	vm_bigpg_alloc(int, struct vm_policy *, int, int),
	vm_ubc_pg_alloc(struct vm_policy *, int),
        vm_pageget_fault(vm_page_t, vm_offset_t);

extern void
	vm_domain_init(struct memory_affinity_domain *),
	vm_page_clean_done(vm_page_t),
	vm_page_clear(vm_page_t),
	vm_page_free(vm_page_t),
	vm_pg_free(vm_page_t, int),
	vm_zeroed_pg_free(vm_page_t),
	vm_page_activate(vm_page_t),
	vm_page_deactivate(vm_page_t, spl_t),
	vm_page_rename(vm_page_t, struct vm_object *, vm_offset_t),
	vm_page_remove(vm_page_t),
	vm_page_copy(vm_page_t, vm_page_t),
	vm_bigpage_copy(vm_page_t, vm_page_t),
	vm_page_wire(vm_page_t, boolean_t),
	vm_page_unwire(vm_page_t, boolean_t),
	vm_set_page_size(vm_size_t),
	vm_page_free_dump_pages(void),
	vm_page_stealer(struct vm_control *),
	vm_page_sched(struct vm_control *),
	vm_wait(struct vm_policy *),
	vm_page_tester(struct vm_control *),
	vm_gsm_page_tester(void),
	vm_page_remove_bucket(vm_page_t),
	vm_page_release(vm_page_t);

extern boolean_t
	vm_wait_expire(struct vm_policy *),
	vm_page_hold(vm_page_t);

/*
 * Function prototypes for all big page related functions follow
 */
extern void
        vm_bigpg_info_alloc(vm_map_entry_t),
        vm_ubc_bigpg_info_alloc(struct vm_seg *),
        vm_bigpg_info_grow(vm_map_entry_t, vm_size_t, boolean_t),
        vm_bigpg_info_clone(struct vm_object *, struct vm_object *),
        vm_bigpg_info_free(struct vm_object *),
        vm_bigpg_clear_busy(vm_page_t),
        vm_bigpg_set_busy(vm_page_t),
	vm_bigpg_set_empty(vm_page_t),
        vm_bigpg_release(vm_page_t),
        vm_bigpg_downgrade_common(struct vm_object *, vm_offset_t, 
				  unsigned char, int),
        vm_map_bigpg(vm_map_entry_t, vm_offset_t, vm_page_t, int,
		     vm_prot_t, boolean_t, vm_prot_t),
        vm_map_seg_bigpg(pmap_t, pmap_seg_t, vm_offset_t, vm_page_t, int),
	vm_bigpg_unlock_gh(struct vm_object *, vm_offset_t);
extern boolean_t
	vm_bigpg_hold(vm_page_t);
extern vm_page_t
        vm_bigpg_alloc(int, struct vm_policy *, int, int),
        vm_alloc_obj_page(struct vm_object *, vm_offset_t, int, int);
extern kern_return_t
        vm_map_ssm_bigpg(pmap_t, pmap_ssm_t, vm_offset_t, vm_page_t, 
			 vm_prot_t, vm_prot_t, struct vpage *, int,
			 vm_map_entry_t);
extern unsigned char
	get_bigpg_size(struct vm_object *, vm_offset_t);
extern int
	vm_bigpg_lock_gh(struct vm_object *, vm_offset_t),
	vm_same_bigpg(vm_page_t, vm_page_t);

#endif	/* _KERNEL */
#endif	/* !_VM_VM_PAGE_H_ */
