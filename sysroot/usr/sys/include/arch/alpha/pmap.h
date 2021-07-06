/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: pmap.h,v $
 * Revision 1.2.154.3  2004/10/12  22:54:02  Joseph_Muldoon
 * 	Fix bug in PA_TO_MID() to allow support for >= 8
 * 	cpus per rad.
 *
 * Revision 1.2.154.2  2003/09/22  20:22:20  Ross_Knepper
 * 	Change layout of pmap_ssm structure to support l3gh.
 *
 * Revision 1.2.154.1  2002/10/16  15:15:13  David_Bernardo
 * 	Add pmap_enter_range_devmap.
 *
 * Revision 1.2.134.10  2002/05/24  16:37:19  David_Bernardo
 * 	Add pt_entry_l2 structure.
 *
 * Revision 1.2.134.9  2002/05/23  05:19:25  Renny_Shen
 * 	Changed "gsm" PMEM type to "shared"
 *
 * Revision 1.2.134.8  2002/03/26  01:11:23  Renny_Shen
 * 	Added flag definitions for pmap_valid_page(), GSM PMAP use type,
 * 	PMR type field in pmr_t and pmr_info, and shared PMR count in
 * 	pmr_rad_entry
 *
 * Revision 1.2.134.7  2002/02/11  23:23:18  David_Bernardo
 * 	Remove pv_flags.
 *
 * Revision 1.2.134.6  2002/01/30  00:02:33  Ernie_Petrides
 * 	Replace "vas_ext_vabits" field with "vas_kseg_shift" field in
 * 	"vas_data" to support booting in 48-bit-KSEG mode of EV7.
 *
 * Revision 1.2.134.5  2002/01/28  21:09:41  Matthew_McGrath
 * 	Added a pv_flags field to the pv_entry to mark an entry as devmap.
 * 	[QAR 91432]
 *
 * Revision 1.2.134.4  2002/01/10  14:02:12  Matthew_McGrath
 * 	Clean up unneeded debugging code from the Marvel support work.
 * 	Added comments for PA_TO_MID.
 *
 * Revision 1.2.134.3  2001/11/27  19:01:27  Matthew_McGrath
 * 	Modified PA_TO_MID to support Marvel
 * 	(Pass 1 Linear, Pass 2 Linear/Interleave are supported)
 *
 * Revision 1.2.134.2  2001/10/24  22:18:41  Rajesh_R
 * 	Add defines for Marvel/EV7 mixed VA mode (48-bit KSEG with
 * 	43-bit SEG0 and SEG1 sign-extended to 48-bits) support and
 *
 * Revision 1.2.134.1  2001/10/03  17:43:50  David_Bernardo
 * 	Removed pv_list_head structure and unused bit definitions
 * 	as part of vm_page restructuring work.  Modified macros
 * 	that used the old pv_list_head.
 *
 * Revision 1.2.124.3  2000/10/26  19:34:26  David_Bernardo
 * 	Fix unnamed union in pmap_seg_map. Add fault-on callback and new
 * 	MMF symbols.
 *
 * Revision 1.2.124.2  2000/10/18  14:34:46  devbld_zko
 * 	Include usr/include/sys/cpuset.h instead of usr/include/kern/cpuset.h.
 *
 * Revision 1.2.124.1  2000/10/18  12:59:06  David_Bernardo
 * 	Add lock and flags used to synchronize segment migration.
 * 
 * Revision 1.2.74.30  2000/06/12  20:33:27  Anton_Verhulst
 * 	Add second int to replicate_text_section() proto.
 * 
 * Revision 1.2.74.29  2000/03/29  17:50:12  Frederick_Canter
 * 	Add extern boolean_t    managed(vm_offset_t);
 * 
 * Revision 1.2.74.28  2000/03/25  00:47:07  Ernie_Petrides
 * 	Replicate "gh_in_use" global variable.
 * 
 * Revision 1.2.74.27  2000/03/24  15:33:22  James_Woodward
 * 	remove the use of cpusets from the pmap.  This showed very
 * 	high cycle times on work loads doing lots of shoot downs and
 * 	context switches.  Also re-arrange pmap to be cache friendly and
 * 	for future > 64 cpu support.  The define PMAP_CPU_MAX controls
 * 	the maximun number of cpus that can be supported.  This is being
 * 	set to 64 for now to remove unneeded loops.
 * 
 * Revision 1.2.74.26  2000/03/16  23:01:14  Shashi_Mangalat
 * 	Changes to support vm_page/pvh merge.
 * 
 * Revision 1.2.74.25  2000/01/31  20:33:59  David_Bernardo
 * 	Remove array of level1_pt's from pmap structure. Remove prototype for
 * 	pmap_get_thread_ptbr. Add mtpr_virbnd and mtpr_sysptbr.
 * 
 * Revision 1.2.74.24  2000/01/27  20:20:37  Ernie_Petrides
 * 	Define vtopte() as a function call into pmap.c for external compiles
 * 	to avoid exporting pmap internals, limit visibility of Selfmap and
 * 	Othermap, and allow for read-mostly globals to be replicated.
 * 
 * Revision 1.2.74.23  2000/01/25  21:59:07  Ross_Knepper
 * 	Merge from ZINCOS.BL3 to ZULUOS.BL8
 * 	[rev. 1.2.103.1  1999/12/23  11:34:12  Liam_Kelleher]
 * 	.Change to pmap_copy_page to handle IO device mapped sources and
 * 	.destination pages correctly (QAR 76155)
 * 	.Changed operation of pmap coproc management to make calls thread
 * 	.safe (QAR 76165)
 * 
 * Revision 1.2.74.22  1999/12/15  20:08:47  Shashi_Mangalat
 * 	Cache align pmap_seg_map structure.
 * 
 * Revision 1.2.74.21  1999/11/18  23:15:16  Shashi_Mangalat
 * 	Merge from ZINCOS_BL1 upto zincos_bl2:
 * 	Add pg_ssm_cow as a synonym of pg_no_lww.
 * 
 * Revision 1.2.74.20  1999/11/01  23:48:16  Shashi_Mangalat
 * 	Make size of free_page_table structure cache aligned.
 * 	Change to get_more_pte_pages() prototype.
 * 
 * Revision 1.2.74.19  1999/10/01  21:36:32  Ernie_Petrides
 * 	Fix erroneous increment of pmap->active_count when context
 * 	switching between multiple threads of the same user task.
 * 
 * Revision 1.2.74.18  1999/09/25  20:44:43  Shashi_Mangalat
 * 	Revise PMAP_SEG_NEXT() macro.
 * 
 * Revision 1.2.74.17  1999/08/19  20:58:21  Shashi_Mangalat
 * 	Convert rad_gh_regions to array type.
 * 	Replace PMEM_LOG with existing PMEM_LOGS.
 * 	[1999/08/18  19:45:55  Shashi_Mangalat]
 * 
 * Revision 1.2.74.16  1999/08/06  16:38:16  James_Woodward
 * 	add function proto for pmap_update_replicated_text().
 * 	[1999/08/06  12:07:56  James_Woodward]
 * 
 * Revision 1.2.74.15  1999/08/05  20:45:17  Shashi_Mangalat
 * 	Replace gh_mads global with gh_in_use.
 * 	[1999/08/04  13:12:16  Shashi_Mangalat]
 * 
 * Revision 1.2.74.14  1999/07/27  21:37:38  Shashi_Mangalat
 * 	Add pmap_get_thread_ptbr() prototype.
 * 	[1999/07/27  19:39:25  Shashi_Mangalat]
 * 
 * Revision 1.2.74.13  1999/07/19  21:49:24  Anton_Verhulst
 * 	Rework for unified (kernel / user) cpusets, radset, idsets.
 * 	[1999/07/19  21:40:17  Anton_Verhulst]
 * 
 * Revision 1.2.74.12  1999/07/15  20:42:34  Shashi_Mangalat
 * 	Add NUMA support for Granularity Hints.
 * 	Add PMEM_LOG physical memory use type.
 * 	[1999/07/12  20:05:26  Shashi_Mangalat]
 * 
 * Revision 1.2.74.11  1999/06/21  14:04:34  James_Woodward
 * 	add rad.h and rad structure
 * 	[1999/06/18  18:22:09  James_Woodward]
 * 
 * Revision 1.2.74.10  1999/05/07  22:25:33  Shashi_Mangalat
 * 	Merge fixes.
 * 	[1999/05/07  22:11:38  Shashi_Mangalat]
 * 
 * Revision 1.2.74.9  1999/05/06  19:35:17  Shashi_Mangalat
 * 	Merge of STEELOS_BL21:STEELOS_BL23
 * 	 Revision 1.2.32.30  1999/04/15  20:41:42  Jeff_Colburn
 * 	 Rename the lw wait bit (pg_lw_wait) in the pte to no lw
 * 	 wiring (pg_no_llw).
 * 	 Revision 1.2.32.29  1999/03/19  20:05:39  Ernie_Petrides
 * 	 Fix declarations of simple lock fields.
 * 	 Revision 1.2.32.28  1999/03/02  23:01:28  Shashi_Mangalat
 * 	 Add prototype for pmap_soft_interleave().
 * 	[1999/05/06  19:29:39  Shashi_Mangalat]
 * 
 * Revision 1.2.74.8  1999/03/10  14:42:15  James_Woodward
 * 	Merge of STEELOS_BL20:STEELOS_BL21
 * 	 Revision 1.2.32.26  1999/01/05  16:11:44  James_Woodward
 * 	clone a version of pmap_resident_extract which doesn't lower ipl
 * 	for use by the dump code.  New routine is named:
 * 	pmap_resident_extract_dump().
 * 	 Revision 1.2.32.25  1998/11/26  17:35:18  Shashi_Mangalat
 * 	Include queue.h and define KSEG_TO_PHYS for kdbx.
 * 	 Revision 1.2.32.24  1998/11/25  23:32:05  Shashi_Mangalat
 * 	VM/NUMA scalability enhancements.
 * 	[1999/03/09  23:44:13  Shashi_Mangalat]
 * 
 * Revision 1.2.74.6  1998/12/08  00:35:33  Shashi_Mangalat
 * 	Merge of STEELOS_BL18:STEELOS_BL20
 * 	 Revision 1.2.32.23  1998/10/21  17:45:29  Ernie_Petrides
 * 	 Add function prototypes for pmap_mmu_setup() and pmap_ssm_protect().
 * 	 Revision 1.2.32.22  1998/09/30  17:21:40  Nitin_Karkhanis
 * 	 Merge of PTEV6OS_BL6:PTEV6OS_BL8
 * 	  Revision 1.2.51.12  1998/09/11  21:06:18  David_Anderson
 * 	  Turn pmr_spare into pmr_tested, to store the highest tested page
 * 	  in each pmr. (QAR 63810)
 * 	[1998/12/08  00:29:39  Shashi_Mangalat]
 * 
 * Revision 1.2.74.5  1998/10/06  16:41:25  Shashi_Mangalat
 * 	Merge fix.
 * 	[1998/10/06  15:14:32  Shashi_Mangalat]
 * 
 * Revision 1.2.74.4  1998/10/02  19:40:58  Shashi_Mangalat
 * 	bmerge -jSTEELOS_BL16:STEELOS_BL18 **
 * 	 Revision 1.2.32.21  1998/07/31  22:51:30  Ernie_Petrides
 * 	 Merge from PTEV6OS_BL6.
 * 	  Revision 1.2.51.11  1998/06/25  20:40:08  Larry_Woodman
 * 	  Add support for EV6 ECO #117, suppressing MB() in tbmiss flow.
 * 	  Revision 1.2.51.10  1998/06/24  18:56:27  Ernie_Petrides
 * 	  Move prototype pte table declarations to pmap.c/pmap_init.c,
 * 	  introduce structures for pmr and vas data, and put external
 * 	  data declarations under _KERNEL ifdef's.
 * 	  Revision 1.2.51.9  1998/04/30  17:56:42  Jeff_Colburn
 * 	  Add simple lock to pv list head.
 * 	  Revision 1.2.51.8  1998/04/21  21:35:02  Shashi_Mangalat
 * 	  Support for enhanced coproc_tbi() interface.
 * 	  Revision 1.2.51.7  1998/04/20  17:20:09  David_Anderson
 * 	  Large memory-hole support for Wildfire.
 * 	  (QAR 60399)
 * 	 Revision 1.2.32.20  1998/05/11  21:57:32  Shashi_Mangalat
 * 	 Merge of PTEV6OS_BL4 (PTCOS_BL14:PTEV6OS_BL4).
 * 	  Revision 1.2.51.6  1998/03/26  21:35:40  Shashi_Mangalat
 * 	  Add PMEM_PMAP and PMEM_GH memory use types.
 * 	[1998/10/02  19:25:21  Shashi_Mangalat]
 * 
 * Revision 1.2.74.3  1998/08/31  11:29:50  James_Woodward
 * 	added queue.h include file so kdbx extension would build
 * 	[1998/08/31  11:26:40  James_Woodward]
 * 
 * Revision 1.2.74.2  1998/08/26  12:34:34  James_Woodward
 * 	Merge of numaproj and zulu
 * 	[1998/07/29  20:12:31  James_Woodward]
 * 
 * Revision 1.2.61.6  1998/07/22  13:48:55  Andrew_Duane
 * 	bmerge -rSTEELOS_BL16 **
 * 	 Revision 1.2.32.19  1998/04/07  12:37:25  Mark_Dewandel
 * 	 Changed pmap->active_on and pmap->new_asn to be type cpuset_t
 * 	 instead of cpumask_t.
 * 	[1998/07/22  13:48:15  Andrew_Duane]
 * 
 * Revision 1.2.61.5  1998/05/18  21:20:49  Shashi_Mangalat
 * 	Make page table cache NUMA aware.
 * 	Add support for replicated text.
 * 	Move mark_for_scavenge() here from vm_exproto.h.
 * 	[1998/05/18  20:40:04  Shashi_Mangalat]
 * 
 * Revision 1.2.61.4  1998/05/13  19:41:08  James_Woodward
 * 	add support for multiple lvl1 to pmap
 * 	[1998/05/13  12:03:17  James_Woodward]
 * 
 * Revision 1.2.61.3  1998/04/24  15:00:55  Andrew_Duane
 * 	Remove obsolete defines START_OF_KERNEL_TEXT and END_OF_BOOT_TEXT.
 * 	[1998/04/24  14:09:59  Andrew_Duane]
 * 	Expand scavenge_list and clean up scavenge code.
 * 	[1998/04/23  18:55:49  Andrew_Duane]
 * 
 * Revision 1.2.61.2  1998/04/09  21:12:36  Shashi_Mangalat
 * 	Add PMEM_PMAP and PMEM_GH memory use types.
 * 	[1998/04/09  19:33:22  Shashi_Mangalat]
 * 
 * Revision 1.2.32.18  1998/02/10  14:51:59  Frederick_Canter
 * 	Port EV6 support forward from pt.ev6 to steel.
 * 	Increase PMAP_MAXASN to 255 for EV6.
 * 	[1998/02/08  15:12:02  Frederick_Canter]
 * 
 * Revision 1.2.32.17  1998/01/19  17:19:04  Jeff_Colburn
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL11:PTCOS_BL14 **
 * 		** Ancestor revision:	1.2.42.2 **
 * 		** Merge revision:	1.2.42.3 **
 * 	 	** End **
 * 	 Revision 1.2.42.3  1997/10/09  23:21:51  Tony_Bono
 * 	 Fix to prevent panic when a page is still lwired while the
 * 	 page is unmapped.
 * 	[1998/01/19  17:07:28  Jeff_Colburn]
 * 
 * Revision 1.2.32.16  1997/11/07  18:34:48  Andrew_Duane
 * 	Cast PHYS_TO_KSEG and KSEG_TO_PHYS arguments to clean up warnings.
 * 	[1997/11/07  13:43:58  Andrew_Duane]
 * 
 * Revision 1.2.32.15  1997/11/06  12:24:59  James_Woodward
 * 	per-processor numa work
 * 	[1997/10/20  19:51:25  James_Woodward]
 * 
 * Revision 1.2.32.14  1997/09/24  21:21:31  Shashi_Mangalat
 * 	Add more prototypes.
 * 	[1997/09/23  16:58:50  Shashi_Mangalat]
 * 
 * Revision 1.2.32.13  1997/07/24  21:53:06  Shashi_Mangalat
 * 	Support for NUMA.
 * 	Also move declaration of pmem_use_array here from pmap.c.
 * 	[1997/07/22  19:49:19  Shashi_Mangalat]
 * 
 * Revision 1.2.32.12  1997/06/05  13:48:05  Mark_Dewandel
 * 	Dynamically allocate latest_asn, asn_wrap_point, and
 * 	asn_wrap_count as well as pmap components asn and
 * 	asn_wrap_count.  Remove all instances of NCPUS and
 * 	add definition NO_SHOOT sentinel value.
 * 	[1997/06/02  20:28:09  Mark_Dewandel]
 * 
 * Revision 1.2.32.11  1997/05/17  03:12:37  Shashi_Mangalat
 * 	Add pmap_remove_wired() prototype.
 * 	[1997/05/16  14:07:58  Shashi_Mangalat]
 * 
 * Revision 1.2.32.10  1997/05/15  20:38:22  Joe_Mario
 * 	BL10 merge cleanup.  Replace uses of _USE_KERNEL_INTRINSICS macro
 * 	with _USE_KERNEL_PROTOS macro.  The kernel intrinsics will be used
 * 	whenever _USE_KERNEL_PROTOS is defined.
 * 	[1997/05/13  21:24:19  Joe_Mario]
 * 
 * Revision 1.2.32.9  1997/04/24  21:32:13  Larry_Woodman
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL3:PTCOS_BL6 **
 * 		** Ancestor revision:	1.2.36.2 **
 * 		** Merge revision:	1.2.42.2 **
 * 	 	** End **
 * 	merge of PTmin BL6 changes
 * 	[1997/04/24  20:30:45  Larry_Woodman]
 * 
 * Revision 1.2.32.8  1997/04/10  19:44:49  Shashi_Mangalat
 * 	Add memory holes support
 * 	[1997/04/09  20:50:49  Shashi_Mangalat]
 * 
 * Revision 1.2.42.2  1997/03/31  16:09:10  Joe_Mario
 * 	Redefine mtpr_tbis(vaddr), mtpr_tbisi(vaddr), mtpr_tbisd(vaddr),
 * 	mtpr_tbia(), and mtpr_tbiap() to be single instruction asms when
 * 	_USE_KERNEL_INTRINSICS is set.
 * 	[1997/03/28  00:48:57  Joe_Mario]
 * 
 * Revision 1.2.32.7  1997/03/04  16:29:03  Robin_Miller
 * 	Add conditionalization for both KERNEL & _KERNEL for
 * 	user space builds (i.e., 'kdbx').
 * 	[1997/03/04  16:24:23  Robin_Miller]
 * 
 * Revision 1.2.32.6  1997/03/03  15:32:16  Robin_Miller
 * 	Add function prototypes.
 * 	Change #ifdef KERNEL to _KERNEL.
 * 	[1997/03/03  14:55:59  Robin_Miller]
 * 
 * Revision 1.2.32.5  1997/01/24  19:22:54  Mark_Dewandel
 * 	Removed preprocessor guards for NCPUS > 1
 * 	[1997/01/24  14:04:03  Mark_Dewandel]
 * 
 * Revision 1.2.32.4  1996/10/28  18:04:45  Patrick_ORourke
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTAOS_BL4:PTBOS_BL3 **
 * 		** Ancestor revision:	1.2.30.3 **
 * 		** Merge revision:	1.2.36.2 **
 * 	 	** End **
 * 	merge of PTB BL3 changes
 * 	Revision 1.2.36.2  1996/09/04  13:38:49  Stephen_Ofsthun
 * 	Add a PMEM_KDEBUG memory use flag for kdebug_bootstrap allocated memory.
 * 	[1996/10/28  17:50:49  Patrick_ORourke]
 * 
 * Revision 1.2.36.2  1996/09/04  13:38:49  Stephen_Ofsthun
 * 	Add a PMEM_KDEBUG memory use flag for kdebug_bootstrap allocated memory.
 * 	[1996/08/29  15:02:19  Stephen_Ofsthun]
 * 
 * Revision 1.2.32.3  1996/08/03  15:16:05  Andrew_Duane
 * 	Removed the sys_space stuff; obsolete.
 * 	[1996/08/01  15:22:12  Andrew_Duane]
 * 
 * Revision 1.2.32.2  1996/07/24  14:52:48  Jeff_Colburn
 * 	Function prototype work, header definitions
 * 	[1996/07/22  17:24:21  Jeff_Colburn]
 * 
 * Revision 1.2.30.3  1996/06/20  19:24:42  Frederick_Canter
 * 	Add #ifdef _KERNEL user code sees KSEG<->PHYS and
 * 	IS_*_VA macros instead of functions.
 * 	[1996/06/20  14:25:35  Frederick_Canter]
 * 
 * Revision 1.2.30.2  1996/06/19  16:16:51  Frederick_Canter
 * 	Change PHYS<->KSEG & IS_*_VA macros to functions, so EV6
 * 	48-bit Virtual Addresses will not break binary compatibility
 * 	for drivers compiled on V4.0a (or later).
 * 	[1996/06/19  12:00:59  Frederick_Canter]
 * 
 * Revision 1.2.20.8  1996/03/05  16:44:52  Shashi_Mangalat
 * 	Merge pg_lw_wire bit and pg_lw_wire_count fields.  Add LW_WIRE_MAX
 * 	constant to detect wire count overflow.
 * 	[1996/02/23  18:56:11  Shashi_Mangalat]
 * 
 * Revision 1.2.20.7  1995/12/18  17:43:25  Shashi_Mangalat
 * 	Add support for segmented shared memory.
 * 	[1995/12/18  00:25:44  Shashi_Mangalat]
 * 
 * Revision 1.2.20.6  1995/10/30  20:24:04  David_Winchell
 * 	Granularity hints.
 * 	[1995/10/30  18:43:45  David_Winchell]
 * 
 * Revision 1.2.20.5  1995/05/23  17:58:09  David_Winchell
 * 	merge of Platinum Lite BL4 changes
 * 	[1995/05/23  17:52:28  David_Winchell]
 * 
 * Revision 1.2.19.4  1995/04/17  20:47:33  Patrick_ORourke
 * 	Reserve unix tables from scavenge area, create START_OF_KERNEL_TEXT
 * 	symbol.
 * 	[1995/04/17  16:09:21  Patrick_ORourke]
 * 
 * Revision 1.2.19.3  1995/03/17  19:11:19  Ashoke_Rampuria
 * 	Added physical memory use type defines and data
 * 	structure.
 * 	[1995/03/17  17:06:04  Ashoke_Rampuria]
 * 
 * Revision 1.2.20.4  1995/03/10  16:19:20  Jie_Yao
 * 	end_of_scavenge is now extern defined
 * 	[1995/03/09  17:37:24  Jie_Yao]
 * 
 * Revision 1.2.20.3  1995/02/28  21:50:22  Ashoke_Rampuria
 * 	merge of Platinum Lite BL1 changes
 * 	revision 1.2.19.2  1995/01/30  19:45:59  Ashoke_Rampuria
 * 	Revision 1.2.19.5  1995/04/24  23:37:07  David_Winchell
 * 	Light weight wiring fields added to the pte.
 * 	[1995/04/24  20:21:45  David_Winchell]
 * 
 * Revision 1.2.20.2  1995/02/10  21:09:31  Andrew_Duane
 * 	Made externs for: proto_kern_ptetab, proto_user_ptetab,
 * 	proto_user_segpte. Made externs for: pv_head_table, pv_list_zone,
 * 	pmap_first_phys, pmap_last_phys. Made externs for: pmap_zone,
 * 	latest_asn, asn_wrap_point, asn_wrap_count.
 * 	[1995/02/09  20:59:50  Andrew_Duane]
 * 
 * Revision 1.2.19.2  1995/01/30  19:45:59  Ashoke_Rampuria
 * 	Removed zone declarations.
 * 	[1995/01/27  20:03:14  Ashoke_Rampuria]
 * 
 * Revision 1.2.15.7  1994/10/17  21:44:39  Shashi_Mangalat
 * 	Add PMAP_KPTE to support selective pte page dumps.
 * 	[1994/10/17  21:42:57  Shashi_Mangalat]
 * 
 * Revision 1.2.15.6  1994/07/14  14:37:59  David_Winchell
 * 	merge of Hardware BL2 changes
 * 	[1994/07/13  20:36:46  David_Winchell]
 * 
 * Revision 1.2.15.5  1994/06/12  20:41:53  David_Winchell
 * 	 Change pmap_context from noop to a call to pmap_activate.
 * 	[1994/06/12  20:22:27  David_Winchell]
 * 
 * Revision 1.2.15.4  1994/06/10  21:02:09  David_Winchell
 * 	     New asn implementation.
 * 	[1994/06/10  19:57:53  David_Winchell]
 * 
 * Revision 1.2.15.3  1994/05/17  18:30:12  Naresh_Dharnidharka
 * 	EV5 and GOLD_BL10 merge
 * 	[1994/05/10  16:44:11  Naresh_Dharnidharka]
 * 
 * Revision 1.2.7.17  1994/05/12  18:00:46  Thomas_Peterson
 * 	Added extern "C" macros around function decls for C++.  Added arg
 * 	types to function decl using __() macro from <standards.h> for
 * 	_NO_PROTO support.
 * 	[1994/04/26  20:49:31  Thomas_Peterson]
 * 
 * Revision 1.2.7.16  1994/04/25  22:38:33  Shashi_Mangalat
 * 	Add PMAP_SEG_SIZE and PMAP_SEG_MASK constants.  Remove ps_reslock
 * 	from pmap_seg structure.  Change ps_loadedpte from short to int.
 * 	[1994/04/25  22:26:46  Shashi_Mangalat]
 * 
 * Revision 1.2.15.2  1994/04/15  14:55:51  Naresh_Dharnidharka
 * 	Merge to BL9.
 * 	[1994/04/01  16:04:53  Naresh_Dharnidharka]
 * 	Increase PMAP_MAXASN to 127 for EV5.
 * 	[1994/03/30  16:06:42  Naresh_Dharnidharka]
 * 
 * Revision 1.2.7.15  1994/04/06  21:59:33  Ernie_Petrides
 * 	Add PMAP_UPDATE() macro to short circuit pmap_update_send() calls
 * 	when (!multicpu) and recode {SET,NEXT,RECYLE}_ASNS in callers.
 * 	[1994/04/06  17:10:28  Ernie_Petrides]
 * 
 * Revision 1.2.7.14  1994/03/03  15:11:26  Ashoke_Rampuria
 * 	Added lw_trans to pmap structure.
 * 	[1994/03/02  19:50:36  Ashoke_Rampuria]
 * 
 * Revision 1.2.7.13  1994/02/28  22:18:57  Ernie_Petrides
 * 	Add count of cross cpu interrupts in pmap_update structure and
 * 	move pmap structure lock to the top of the structure.
 * 	[1994/02/28  20:19:34  Ernie_Petrides]
 * 
 * Revision 1.2.7.12  1994/01/21  23:56:55  Ernie_Petrides
 * 	Revise declarations related to pmap module locking optimizations,
 * 	incorporate use of cpumask_t typedef from cpu.h, remove support
 * 	for disabling REF_BITS, and move NCPUS > 64 check to cpu.c.
 * 	[1994/01/21  04:16:26  Ernie_Petrides]
 * 
 * Revision 1.2.7.11  1994/01/05  22:28:56  Shashi_Mangalat
 * 	Added macro definition of PMAP_PTE.
 * 	[1994/01/05  21:21:17  Shashi_Mangalat]
 * 
 * Revision 1.2.7.10  1993/12/16  17:16:01  Shashi_Mangalat
 * 	Merge of Sterling BL8 changes.
 * 	 Removed declaration of scavenge_info and declared it as extern.
 * 	 [1993/11/02  21:19:43  Ashoke_Rampuria]
 * 	[1993/12/16  16:40:25  Shashi_Mangalat]
 * 
 * Revision 1.2.7.9  1993/11/12  14:44:31  Joe_Martin
 * 	PMAP_SEGMENTATION on (Thanks, Dave); add other_lock field to struct pmap
 * 	[1993/11/11  20:03:14  Joe_Martin]
 * 
 * Revision 1.2.7.8  1993/11/09  14:12:33  Ashoke_Rampuria
 * 	Merged sterling bl7 changes.
 * 	added defines:
 * 	#define PDEVCMD_ONE     PMAP_COPROC_INVALIDATE_STLB
 * 	#define PDEVCMD_ALL     PMAP_COPROC_EXIT
 * 	these were removed in an earlier submit but are still used.
 * 	[1993/10/20  21:48:39  Brett_Sampson]
 * 	Colapsed lwwire and wire bit in pte. Changed defines for shadow tlb
 * 	maintenance.
 * 	[1993/10/19  18:19:58  Ashoke_Rampuria]
 * 	Added support for getrusage system call.
 * 	[1993/09/07  19:29:11  Ashoke_Rampuria]
 * 	put comment line on #endif KERNEL #endif !ASSEMBLER #endif
 * 	_PMAP_MACHINE_ to avoid syntax error when -stdl flag is on.
 * 	[1993/09/15  18:13:41  SJ_Lee]
 * 
 * Revision 1.2.7.7  1993/11/04  22:29:58  Joe_Martin
 * 	struct pmap_update_info
 * 	[1993/11/01  17:13:04  Joe_Martin]
 * 
 * Revision 1.2.7.6  1993/10/27  17:38:53  Shashi_Mangalat
 * 	Modified struct pv_entry for new pte page allocation scheme.
 * 	[1993/10/27  17:37:26  Shashi_Mangalat]
 * 
 * Revision 1.2.7.5  1993/10/11  18:56:02  Shashi_Mangalat
 * 	Merge of Sterling BL6 changes.
 * 	 Merged light-weight wiring changes.
 * 	 [1993/09/03  14:47:53  Ashoke_Rampuria]
 * 	[1993/10/11  18:39:40  Shashi_Mangalat]
 * 
 * Revision 1.2.7.4  1993/06/29  20:50:23  Joe_Martin
 * 	introduce pmap_resident_{stack|text|data}
 * 	[1993/06/29  18:57:03  Joe_Martin]
 * 
 * Revision 1.2.7.3  1993/06/21  15:26:56  Joe_Martin
 * 	support memory scavenging; reorganize for pmap.c-pmap_init.c split.
 * 	[1993/06/21  14:55:39  Joe_Martin]
 * 
 * Revision 1.2.7.2  1993/04/28  23:32:34  Paula_Long
 * 	submitting the SMP project
 * 	[1993/04/28  17:53:36  Paula_Long]
 * 
 * Revision 1.2.5.4  1993/04/19  16:10:54  Joe_Martin
 * 	correct SET_ASN for kernel_pmap
 * 	[1993/04/19  16:09:33  Joe_Martin]
 * 
 * Revision 1.2.5.3  1993/04/16  12:06:16  Paula_Long
 * 	Fixed typo in INVALIDATE_ASNS macro for uni-processor
 * 	variant.
 * 	[1993/04/16  12:04:36  Paula_Long]
 * 
 * Revision 1.2.5.2  1993/04/13  20:37:37  Joe_Martin
 * 	ASN and shootdown support
 * 	[1993/04/13  20:29:20  Joe_Martin]
 * 
 * Revision 1.2.2.18  92/11/09  18:47:49  Ernie_Petrides
 * 	Correct left shifts of type int.
 * 	[92/11/09  18:44:07  Ernie_Petrides]
 * 
 * Revision 1.2.2.17  92/10/16  16:35:17  Ernie_Petrides
 * 	Make MMF_* definitions available to locore.s.
 * 	[92/10/13  18:33:50  Ernie_Petrides]
 * 
 * Revision 1.2.2.16  92/09/29  12:17:35  Joe_Martin
 * 	Create mtpr_tbi* macros calling mtpr_tbi.
 * 	[92/09/23  15:06:36  Joe_Martin]
 * 
 * Revision 1.2.2.15  92/08/18  13:17:02  Joe_Martin
 * 	Merge segment page tables from Bob Picco
 * 	[92/08/18  13:06:16  Joe_Martin]
 * 
 * Revision 1.2.2.14  92/08/14  15:29:49  Joe_Martin
 * 	Make pmap_pageable a no-op as it is with MIPS.
 * 	[92/08/14  15:25:32  Joe_Martin]
 * 
 * Revision 1.2.2.13  92/08/11  14:00:12  Ernie_Petrides
 * 	Replace use of ASN_LIMIT and MAXASN with PMAP_MAXASN.
 * 	[92/08/07  14:34:17  Ernie_Petrides]
 * 
 * Revision 1.2.2.12  92/07/09  09:57:24  Randall_Brown
 * 	Cleanup of ALPHA_FLAMINGO and #ifdef OSFPAL
 * 	[92/07/08  09:27:19  Randall_Brown]
 * 
 * Revision 1.2.2.11  92/07/08  16:37:08  Joe_Martin
 * 	Mirror Silver BL8_2 with pmap_seg* declarations
 * 	[92/07/08  16:30:01  Joe_Martin]
 * 
 * Revision 1.2.2.10  92/07/07  14:52:16  Ernie_Petrides
 * 	Turn on REF_BITS.
 * 	[92/07/07  14:50:45  Ernie_Petrides]
 * 
 * Revision 1.2.2.9  92/06/25  12:41:27  Joe_Martin
 * 	Mirror AG_BL8_1 changes: extern kernel_pmap and active_pmap
 * 	[92/06/25  12:39:58  Joe_Martin]
 * 
 * Revision 1.2.2.8  92/06/04  18:01:58  Ernie_Petrides
 * 	Define a reserved-for-software pte bit to be used to cache the
 * 	machine-independent VM_PROT_EXECUTE permission bit.  Also, remove
 * 	the now-unused alpha_protection() macro.
 * 	[92/06/04  17:51:09  Ernie_Petrides]
 * 
 * Revision 1.2.2.7  92/03/11  20:30:25  Ray_Lanza
 * 	OSFpalcode support using 3.10 compilers
 * 	[92/03/10  09:01:52  Ray_Lanza]
 * 
 * Revision 1.2.2.6  92/03/11  17:24:35  Joe_Martin
 * 	unity_base becomes UNITY_BASE defined in machparam.h
 * 	[92/03/11  17:19:52  Joe_Martin]
 * 
 * Revision 1.2.2.5  92/02/05  16:53:19  Joe_Martin
 * 	PXG support
 * 	[92/02/05  16:52:11  Joe_Martin]
 * 
 * Revision 1.2.2.4  92/01/27  14:43:57  Joe_Martin
 * 	fix "alpha_protection" definition
 * 	[92/01/27  14:43:18  Joe_Martin]
 * 
 * Revision 1.2.2.3  92/01/24  14:24:46  Joe_Martin
 * 	backward compatible fixes for new PAL
 * 	[92/01/24  14:21:26  Joe_Martin]
 * 
 * Revision 1.2.2.2  92/01/20  17:47:55  Joe_Martin
 * 	Fix ASN structure for MP.
 * 	[92/01/20  17:39:05  Joe_Martin]
 * 
 * Revision 1.1.2.5  92/01/10  13:35:48  Joe_Martin
 * 	ASNs
 * 	[92/01/10  13:26:24  Joe_Martin]
 * 
 * Revision 1.1.2.3  91/12/17  11:52:33  Joe_Martin
 * 	#define MMF_* flags, pmap_is_referenced
 * 	[91/12/17  11:51:46  Joe_Martin]
 * 
 * Revision 1.1.2.2  91/12/06  17:56:10  David_Snow
 * 	"Initial version.  File copied from TIN-based Alpha pool."
 * 
 * Revision 1.1.1.2  91/12/06  16:07:35  David_Snow
 * 	Initial version.  File copied from TIN-based Alpha pool.
 * 
 * $EndLog$
 */
/*
 *	@(#)$RCSfile: pmap.h,v $ $Revision: 1.2.154.3 $ (DEC) $Date: 2004/10/12 22:54:02 $
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/*
 *
 *	File:	pmap.h
 *
 *	Alpha version
 *
 *	Machine-dependent structures for the physical map module.
 *
 */

#ifndef	_PMAP_MACHINE_
#define	_PMAP_MACHINE_

#define MMF_READ	0
#define MMF_IFETCH	-1
#define MMF_WRITE	1
#define MMF_PMAPINIT	2 /* used by pmap_bootstrap call to pmap_fault_on */

/* these are used by the fault-on callback mechanism */

#define MMF_TNV      0   /* these 5 values are defined as MMCSR in the SRM */
#define MMF_ACCVIO   1
#define MMF_FOR      2
#define MMF_FOE      3
#define MMF_FOW      4

#define MMF_FOR_M    4  /* these are masks */
#define MMF_FOE_M    8
#define MMF_FOW_M    16

#ifndef	ASSEMBLER
#include <standards.h>
#include <mach/boolean.h>
#include <kern/lock.h>
#include <mach/machine/vm_param.h>
#include <mach/vm_statistics.h>
#include <mach/vm_prot.h>
#include <machine/cpu.h> 
#include <machine/counters.h> 
#include <sys/types.h> 
#include <mach/machine/kern_return.h> 
#include <sys/cpuset.h>
#include <kern/queue.h>

/*
 *	Alpha Page Table Entry.
 */

union pt_entry {
	unsigned long	quadword;	/* for alignment and atomic writes */
	struct {
		unsigned int	_v:1,		/* valid */
				_for:1,		/* fault on read */
				_fow:1,		/* fault on write */
				_foe:1,		/* fault on execute */
				_asm:1,		/* address space match */
				_gh:2,		/* granularity hint */
				_no_mb:1,	/* suppress MB in EV6 tbmiss */
				_prot:8,	/* {K|E|S|U}{R|W}E */
				_exec:1,	/* execute access flag */
				_wire:1,	/* wired */
				_seg:1,		/* shared text segment pte */
				_ssm:1,		/* shared data segment pte */
		                _gh_shared:1,
		                _no_lww:1,	/* inhibit lw wiring */
		                _soft:2,	/* unused software bits */
		                _lw_wire:8,	/* lw wire count.  See */
						 /* LW_WIRE_MAX below */
				_pfn:32;	/* page frame number */
	}		PTE_BITFIELD;
};

#define pg_v		PTE_BITFIELD._v
#define pg_for		PTE_BITFIELD._for
#define pg_fow		PTE_BITFIELD._fow
#define pg_foe		PTE_BITFIELD._foe
#define pg_asm		PTE_BITFIELD._asm
#define pg_gh		PTE_BITFIELD._gh
#define pg_no_mb	PTE_BITFIELD._no_mb
#define pg_prot		PTE_BITFIELD._prot
#define pg_exec		PTE_BITFIELD._exec
#define pg_wire		PTE_BITFIELD._wire
#define pg_seg		PTE_BITFIELD._seg
#define pg_ssm		PTE_BITFIELD._ssm
#define pg_gh_shared	PTE_BITFIELD._gh_shared
#define pg_soft		PTE_BITFIELD._soft
#define pg_lw_wire	PTE_BITFIELD._lw_wire
#define pg_no_lww	PTE_BITFIELD._no_lww
#define pg_ssm_cow	pg_no_lww
#define LW_WIRE_MAX	255
#define pg_pfn		PTE_BITFIELD._pfn

/*
 *      Alpha Level 2 Page Table Entry for SSM
 */

union pt_entry_l2 {
        unsigned long   quadword;       /* for alignment and atomic writes */
        struct {
                unsigned int    _v:1,           /* valid */
                                _for:1,         /* fault on read */
                                _fow:1,         /* fault on write */
                                _foe:1,         /* fault on execute */
                                _asm:1,         /* address space match */
                                _gh:2,          /* granularity hint */
                                _no_mb:1,       /* suppress MB in EV6 tbmiss */
                                _prot:8,        /* {K|E|S|U}{R|W}E */
                                _exec:1,        /* execute access flag */
                                _wire:1,        /* wired */
                                _seg:1,         /* shared text segment pte */
                                _ssm:1,         /* shared data segment pte */
                                _gh_shared:1,
                                _lw_wire:11,    /* count of wired l3 pages*/
                                _pfn:32;        /* page frame number */
        }               L2_PTE_BITFIELD;
};

#define l2_v            L2_PTE_BITFIELD._v
#define l2_for          L2_PTE_BITFIELD._for
#define l2_fow          L2_PTE_BITFIELD._fow
#define l2_foe          L2_PTE_BITFIELD._foe
#define l2_asm          L2_PTE_BITFIELD._asm
#define l2_gh           L2_PTE_BITFIELD._gh
#define l2_no_mb        L2_PTE_BITFIELD._no_mb
#define l2_prot         L2_PTE_BITFIELD._prot
#define l2_exec         L2_PTE_BITFIELD._exec
#define l2_wire         L2_PTE_BITFIELD._wire
#define l2_seg          L2_PTE_BITFIELD._seg
#define l2_ssm          L2_PTE_BITFIELD._ssm
#define l2_gh_shared    L2_PTE_BITFIELD._gh_shared
#define l2_lw_wire      L2_PTE_BITFIELD._lw_wire
#define l2_pfn          L2_PTE_BITFIELD._pfn
#define L2_LW_WIRE_MAX	2047

typedef union pt_entry      pt_entry_t;
typedef union pt_entry_l2   pt_entry_l2_t;

#define	PT_ENTRY_NULL	((pt_entry_t *) 0)

#define NOTaPFN	((unsigned int)0)
/* The lowest address which is not accessible at any page size. */
#define NOTaVA	((vm_offset_t)(1L<<54))

/*
 * Assumptions:
 *	1) Supervisor and executive modes are not used.
 *	2) User mode accessibility implies kernel mode accessibility.
 */
#define PROT_UW		0x33
#define PROT_KW		0x11
#define PROT_NA		0x00
#define PROT_URKW	0x13
#define PROT_UR		0x03
#define PROT_KR		0x01

/* (some) pte fields as quadword masks */
#define PTEQ_MASK_KWE	(1L << 12)
#define PTEQ_MASK_UWE	(1L << 13)
#define PTEQ_MASK_EXEC	(1L << 16)
#define PTEQ_MASK_FLTON	(7L << 1)

#define PTES_PER_PAGE	(ALPHA_PGBYTES / sizeof(pt_entry_t))

#define PTETOPHYS(pte)	alpha_ptob((pte)->pg_pfn)

#define LEVEL1_PT_OFFSET(ADDR) \
	(((vm_offset_t)(ADDR) >> (3 * PGSHIFT - 6)) & (PGOFSET>>3))
#define LEVEL2_PT_OFFSET(ADDR) \
	(((vm_offset_t)(ADDR) >> (2 * PGSHIFT - 3)) & (PGOFSET>>3))
#define LEVEL3_PT_OFFSET(ADDR) (((vm_offset_t)(ADDR) >> PGSHIFT) & (PGOFSET>>3))
#define EQ_LEVEL1_VPN(XADDR, YADDR) \
	((((XADDR) ^ (YADDR)) >> (3 * PGSHIFT - 6)) == 0)
#define EQ_LEVEL2_VPN(XADDR, YADDR) \
	((((XADDR) ^ (YADDR)) >> (2 * PGSHIFT - 3)) == 0)
#define EQ_LEVEL3_VPN(XADDR, YADDR) ((((XADDR) ^ (YADDR)) >> PGSHIFT) == 0)

/*
 * per cpu asn data for the pmap.
 */
struct pmap_asn {
	unsigned long	asn_wrap_count;	    /* wrap count when ASN assigned */
	unsigned int	asn_val;	    /* asn value for the cpu */
	int		pmap_asn_pad1;	    /* padding to be a cache block */
	long		pmap_asn_pad2[6];   /* padding to be a cache block */
};

#define PMAP_CPU_MAX 64		/* must be multiple of 64 */

/*
 *	Pmap proper
 */
struct pmap {
	simple_lock_data_t	other_lock;	/* task mapping window.	*/
	pt_entry_t 		*level1_pt;	/* level 1 page table	*/
	unsigned long           lw_wirings;	/* total lw wirings	*/
	unsigned long           lw_trans;	/* no. of lw_wire trans.*/
	int			(*coproc_tbi)();/* synch with PXG maps  */
	void			*coproc_arg;	/* argument to coproc_tbi */
	struct pmap_statistics	stats;		/* Map statistics.	*/

	/* 64 byte aligned */
	simple_lock_data_t	lock;		/* lock on map		*/
	struct	pmap_asn	*pmap_asn_data; /* cpu asn data */
	int			ref_count;	/* Reference count.	*/
	int			active_count;	/* # cpus active on       */
	unsigned long		active_on[PMAP_CPU_MAX/64]; /* bit per CPU */
	unsigned long		new_asn[PMAP_CPU_MAX/64]; /* asn advance */
	int                     (*faulton)();   /* faulton callback */
	unsigned int            faulton_mask;   /* arg to faulton_callback */
};

typedef struct pmap	*pmap_t;

#define	PMAP_NULL	((pmap_t) 0)
#define	PMAP_PTE	((pmap_t) 1)	/* user pte page mapping */
#define	PMAP_KPTE	((pmap_t) 2)	/* kernel pte page mapping */

#define PMAP_MAXASN	255	/*  TODO: define per-chip (EV5 = 127)? */

/* 
 * PMAP_TEST_PAGE replaces the old test_it boolean parameter for
 * pmap_valid_page(). The bit instructs the rtn to test the page specified.
 * PMAP_TEST_GSM instructs pmap_valid_page to test GSM pages. The default
 * behavior will be to ignore GSM pages and return KERN_PROTECTION_FAILURE.
 */
#define PMAP_TEST_PAGE  0x1
#define PMAP_TEST_GSM   0x2     /* GSM pages are valid pages */

typedef int memory_atom;

struct scavenge_list {
	long		count;
	vm_offset_t	kseg_start;
};
#define N_SCAVENGE_AREAS	3
typedef struct scavenge_list	scavenge_t[N_SCAVENGE_AREAS];	/* scavenged area list */

#ifdef _KERNEL
_BEGIN_CPLUSPLUS
extern void	end_of_boot_text();
_END_CPLUSPLUS
#endif /* _KERNEL */

#define	PMAP_PTEPAGES(MID)	pmap_mad_data.pmd_fpt[MID].fp_pcount

/* physical memory use type */

#define PMEM_HOLE	0
#define PMEM_CONSMEM	1
#define PMEM_KTEXT	2
#define PMEM_KDATA	3
#define PMEM_KBSS	4
#define PMEM_SCAVENGE	5
#define PMEM_UNIXTABLE	6
#define PMEM_STEAL	7
#define PMEM_MANAGED	8
#define PMEM_CFGMGMT	9
#define PMEM_LOCKS	10
#define PMEM_LOGS	11
#define PMEM_VMTABLES	12
#define PMEM_KDEBUG 	13
#define PMEM_PMAP 	14
#define PMEM_GH 	15
#define PMEM_SHARED     16
#define PMEM_USE_NTYPE 	17

#define PMEM_USE_TYPE {	\
        "hole",		\
        "consmem",	\
        "text",		\
        "data",		\
        "bss",		\
        "scavenge",	\
        "unixtable",	\
        "stealmem",	\
        "managed",	\
        "cfgmgmt",	\
        "locks",	\
        "logs",		\
        "vmtables",	\
        "kdebug",	\
        "pmap",		\
        "gh",		\
        "shared",	\
}

#define PMEM_TYPESIZE   17

/*
 * physical memory use structure
 */

struct pmem_use {
	vm_offset_t		start;		/* start addr */
	vm_offset_t		end;		/* end addr */
	int			type;		/* mem use type */
	struct pmem_use 	*next;		/* pointer to next element */
};

typedef struct pmem_use *pmem_use_t;

/*
 * This structure describes a "region" of contiguous memory.  On a typical
 * system this is all of physical memory.  On a system with holes there
 * will be multiple such regions.
 *
 * The start address is an aligned offset into physical memory.  The pmr_shift
 * value is used to index into the table based on physical address.
 *
 * The type indicates if this PMR represents a managed or shared memory region.
 * The size mask is used by pmap_pmr_init to retrieve the PMR size and
 * type from the return value of pmap_region_size.
 */
#define PMR_MANAGED    0x0
#define PMR_SHARED     0x1
typedef struct pmap_memory_region {
	vm_offset_t		pmr_avail;	/* pa of first managed page */
	long			pmr_pages;	/* managed page count */
	struct vm_page	 	*pmr_pp;	/* vm_page/pv head table */
	void 			*pmr_spare0;	/* (struct cache line pad) */
	void 			*pmr_spare1;	/* (struct cache line pad) */
	int 			pmr_type;	/* shared/managed/etc region */
	int 			pmr_vdone;	/* no more pmap_valloc()s */
	vm_offset_t		pmr_base;	/* base phys addr of region */
	vm_size_t		pmr_size;	/* size of memory region */
} pmr_t;

/*
 * Per-RAD physical memory region data,
 * including the pointer to the data itself.
 */
struct pmr_rad_entry {
	int		pmr_count;	/* number of pmrs within the RAD */
	int             pmr_sh_count;   /* number of shared pmrs only */
	vm_size_t	pmr_size;	/* total size of the pmrs in the RAD */
	pmr_t		*pmr_table;	/* base of table of pmrs */
};

/*
 * Physical memory region data (remains constant after boot-up).
 */
struct pmr_data {
	int	pmr_total_count;/* number of physical memory regions */
	int	pmr_shift;	/* phys addr to pmr index shift factor */
	struct pmr_rad_entry
		*pmr_rad_table;	/* pointer to table of pmap_memory_region's */
};

/*
 * Virtual address size data (remains constant after boot-up)
 */
struct vas_data {
	int		vas_nvabits;	/* number of virtual address bits */
	int		vas_kseg_shift;	/* number of variable KSEG bits */
	int		vas_seg0_shift;	/* number of variable SEG0 bits */
	int		vas_seg1_shift;	/* number of variable SEG1 bits */
	vm_offset_t	vas_kseg_base;	/* base address of KSEG segment */
	vm_offset_t	vas_seg1_base;	/* base address of SEG1 segment */
};

/*
 * Page table page accounting.  One for each NUMA region.
 */
typedef struct free_page_table {
	simple_lock_data_t fp_lock;	/* protects the following data */
	vm_offset_t	fp_free;	/* free page list */
	vm_offset_t	fp_sfree;	/* scavenged page list*/
	int		fp_fcount;	/* free count */
	int		fp_scount;	/* scavenged free count */
	int		fp_pcount;	/* total pages (includes scanvenged) */
	int		fp_kernel;	/* in use by kernel */
	int		fp_want;	/* need more pages */
	int		fp_pad0;	/* */
	struct thread	*fp_thread;	/* allocating thread */
	long		fp_pad1;	/* */
} *fpt_t;

typedef struct pmap_quad_info {
	vm_offset_t	pqi_text_start;
	vm_offset_t	pqi_ptbr;
	scavenge_t	pqi_scavenge;
	int		pqi_text_copied;
} *pqi_t;

struct pmap_mad_data {
	boolean_t	numa_system;	/* TRUE if NUMA system */
	int		pmd_numa_nodes;	/* number of NUMA nodes in system */
	int		pmd_numa_shift;	/* PA address to NUMA region index  */
	int		pmd_mri_shift;	/* PA address to memory region index */
	int		pmd_ktext_replicate;
	int		pmd_ktext_writable;
	vm_offset_t	pmd_ktext_size;
	simple_lock_data_t pmd_ktext_repl_lock;
	pqi_t		pmd_pqi;	/* pointer to table of quad info. */
	struct pmap_quad_info		/* quad info for non-NUMA */
			pmd_pqi_data;
	fpt_t		pmd_fpt;	/* pointer to table of page tables */
	struct free_page_table
			pmd_fpt_data;	/* page table info for non-NUMA */
};

/*
 *	Macros
 */

#if defined(KERNEL) || defined(_KERNEL)
/*
 * Macros for accessing the memory descriptor based on physical address.
 */
/*
 * Physical address to memory region index (for holes).  Exported.
 */
#define PA_TO_MRP(pa)	pa_to_mrp(pa)
#define PA_INDEX(pa)	(alpha_btop((pa) - PA_TO_MRP(pa)->pmr_avail))
#define pa_to_pp(pa)	(&(PA_TO_MRP(pa)->pmr_pp[PA_INDEX(pa)]))
#define MANAGED(pa)	((pa) >= avail_start && (pa) < avail_end)
extern boolean_t	managed(vm_offset_t);

#ifdef _BASE_KERNEL_PRIVATE /* see sys/systm.h - kernel binary compatibility */
#define Selfmap		((pt_entry_t *)(SELF_PFN << (3 * PGSHIFT - 6)))
#define vtopte(v)	(&Selfmap[((vm_offset_t)(v) & ADDRESS_MASK) >> PGSHIFT])
#else
#define vtopte(v)	pmap_vtopte((vm_offset_t)(v))
extern pt_entry_t *pmap_vtopte(vm_offset_t);
#endif /* _BASE_KERNEL_PRIVATE */

/*
 * Macros replaced by functions (in pal_lib.s).
 */
#if defined(_USE_KERNEL_PROTOS)

extern vm_offset_t phys_to_kseg(vm_offset_t);
extern vm_offset_t kseg_to_phys(vm_offset_t);

#else /* !defined(_USE_KERNEL_PROTOS) */

extern vm_offset_t phys_to_kseg();
extern vm_offset_t kseg_to_phys();

#endif /* defined(_USE_KERNEL_PROTOS) */

#ifdef	_KERNEL
#define PHYS_TO_KSEG(addr) phys_to_kseg((vm_offset_t)(addr))
#define KSEG_TO_PHYS(addr) kseg_to_phys((vm_offset_t)(addr))
#else
/*
 * Need this for kdbx, which defines KERNEL.  This won't work 48bit va.
 */
#define PHYS_TO_KSEG(addr) ((vm_offset_t)(addr) + UNITY_BASE)
#define KSEG_TO_PHYS(addr) ((vm_offset_t)(addr) - UNITY_BASE)
#endif

#define PMAP_CONTEXT(pmap, new_thread, my_cpu) \
	thread_pcb(new_thread)->pcb_asn = current_pcb()->pcb_asn

#define PMAP_ACTIVATE(pmap, th, my_cpu) pmap_activate(pmap, th, my_cpu)

#define PMAP_DEACTIVATE(pmap, thread, cpu) pmap_deactivate(pmap, thread, cpu)

#define INVALIDATE_ASNS(pmap)						\
	{								\
		int i;							\
		for (i=0; i < PMAP_CPU_MAX/64; i++) {			\
			(pmap)->new_asn[i] = ~((pmap)->active_on[i]);	\
		}							\
	}

#define PMAP_SET_ACTIVE_ON(map,cpu)					\
		(map)->active_on[(cpu) >> 6] |= (1L << ((cpu) & 63))

#define PMAP_SET_ACTIVE_OFF(map,cpu)					\
		(map)->active_on[(cpu) >> 6] &= ~(1L << ((cpu) & 63))

#define PMAP_IS_ACTIVE(map,cpu)						\
		((map)->active_on[(cpu) >> 6] & (1L << ((cpu) & 63)))

#define PMAP_NEED_NEW_ASN(map,cpu)					\
		((map)->new_asn[(cpu) >> 6] & (1L << ((cpu) & 63)))

#define PMAP_CLEAR_NEED_NEW_ASN(map,cpu)				\
		((map)->new_asn[(cpu) >> 6] &= ~(1L << ((cpu) & 63)))

#define PMAP_UPDATE(pmap, addr){					\
	if(!multicpu)                                                   \
         INVALIDATE_ASNS(pmap)                                         \
        else                                                            \
         pmap_update_send((pmap), (addr));                              \
        }
struct pmap_update_info {
	int             from_cpu[2];
	vm_offset_t     addr[2];
	memory_atom	shoot_pending;
	unsigned int	xcpu_intrs;
};

#define NO_SHOOT		-1		/* from_cpu sentinel */

/*
 * There is a unique pmap segment mapping for every process that maps a text
 * segment. All mappings to a segment are linked in a doubly linked list. 
 * Within an address space, the same 8Meg segment maybe mapped for multiple
 * shared libraries (indicated by the reference count).  Access to the
 * structure is implicitly synchronized by upper level locking and/or
 * the lock used to stall access while migration is taking place. 
 */
typedef struct pmap_seg_map {
	int		psm_refcnt; 	/* references */
        union {
	      unsigned int  psm_iflags;  /* migration flags */
	      struct psmflags {
                         unsigned int
	                 psmmigrate : 1,
	                 psmwait    : 1,
		                    : 30;
              } psm_bflags;
        } psm_u;
  	vm_offset_t	psm_va;	 	/* va */
	pmap_t		psm_pmap;	/* pmap */
	struct pmap_seg	*psm_seg;	/* pmap segment for this mapping */
	queue_chain_t	psm_link;	/* link to other mappings */
        simple_lock_data_t psm_lock;    /* Lock for migrate */
	long		psm_pad1; 	/* pad */
} *psm_t;

#define psm_flags	psm_u.psm_iflags
#define psm_migrate     psm_u.psm_bflags.psmmigrate
#define psm_wait        psm_u.psm_bflags.psmwait

#define	PSM_NULL		((psm_t) 0)

typedef struct pmap_seg {
	simple_lock_data_t ps_seglock;		/* Segment lock */
	unsigned int	ps_refcnt;		/* Segment ref count */
	unsigned int	ps_rescnt;		/* Segment resident count */
	unsigned int	ps_mid;			/* MID of this segment */
	unsigned int	ps_loadedpte;		/* Ptes in page table */
	vm_offset_t	ps_pagetable;		/* Page table */
	queue_head_t	ps_psm;			/* list of mappings */
	queue_chain_t	ps_link;		/* link to other pmap segs */
} *pmap_seg_t;
#define	PMAP_SEG_NULL	((pmap_seg_t) 0)

#define	PMAP_SEG_FIRST(Q)	(pmap_seg_t)queue_first(Q)
#define	PMAP_SEG_NEXT(SP)	(pmap_seg_t)queue_next(&(SP)->ps_link)
#define	PMAP_SEG_END(Q, SP)	queue_end(Q, (queue_entry_t)SP)
#define	PMAP_SEG_ENTER(Q, SP)	queue_enter(Q, SP, pmap_seg_t, ps_link);

#define PMAP_PSM_REF(PSM)	(PSM)->psm_refcnt++

/*
 * Support for large SystemV shared memory
 */
#ifdef	ALPHA_VARIABLE_PAGE_SIZE
# not implemented
#else

/*
 * The following supports 8Meg shared data segments.
 */
#define	SSM_SHIFT		23		
#define	SSM_SIZE		(1L << SSM_SHIFT)
#define	SSM_MASK		((SSM_SIZE) - 1)

#define	SSM_ROUND(va)		(((va) + SSM_MASK) & ~SSM_MASK)
#define	SSM_TRUNC(va)		((va) & ~SSM_MASK)
#define	VA_TO_SSM(va)		((va) >> SSM_SHIFT)
#define	SSM_TO_VA(va)		((va) << SSM_SHIFT)
#define	PAGES_PER_SSM		(1L << (SSM_SHIFT - PGSHIFT))

struct pmap_ssm {
	unsigned int		pss_bits;	 /* Bits for locking, etc. */
	unsigned int		pss_rescnt;	 /* Segment resident count */
	unsigned short		pss_size[2];	 /* Size of l3gh bigpage */
	unsigned short		pss_loadedpte[2];/* Ptes in page table */
	vm_offset_t		pss_pagetable[2];/* Page tables */
	struct pv_entry		*pss_pvlist;	 /* list of mappers */
	unsigned int		pss_index[2];	 /* Index into bigpage */
};

/*
 * Page table indexes.
 */
#define	PT_READ	0
#define	PT_RDWR	1

typedef struct pmap_ssm *pmap_ssm_t;
#endif

/*
 *	For each vm_page_t, there is a list of all currently
 *	valid virtual mappings of that page.  An entry is
 *	a pv_entry_t; the lists' heads are in the pv_table.
 *
 *	Rather than maintain separate arrays for lock, modify,
 *	and reference bits, we steal the three low-order bits
 *	of the virtual address field in each list header.  It
 *	works because operations on the virtual address are really
 *	operations on the virtual page number, and the low-order
 *	bits are "noise".
 */

struct pv_entry {
	union {				 /* overlaid with pv_bits (below) */
		vm_offset_t	_pv_va;	 /* va for this mapping */
		struct vm_page	*_pv_pg; /* vm page for this (pte)page */
	} _upv0;
	union {
		pmap_t		_pv_pmap;	/* pmap where mapping lies */
		pmap_seg_t	_pv_seg;	/* segment */
		pmap_ssm_t	_pv_ssm;	/* shared data segment */
	} _upv1;
	struct pv_entry	*pv_next;	/* next pv_entry */
};

#define	pv_va		_upv0._pv_va
#define	pv_pg		_upv0._pv_pg
#define	pv_pmap		_upv1._pv_pmap
#define	pv_seg		_upv1._pv_seg
#define	pv_ssm		_upv1._pv_ssm

#define PV_BIT_MODIFY	2L
#define	PV_BIT_REF	4L

#define PV_BITS		(PV_BIT_MODIFY | PV_BIT_REF)

/*
 * Steal bit 3 of the VA to identify the pv entry as belonging to a segment.
 * We chose 3 because bits 0 thru 2 are being used in the pv head for other
 * purposes.  Also bit 3 will be preserved because it will be treated a part
 * of the VA.  Same for bit 4.
 */

#define PV_DEVMAP	0x00000001L	/* used to identify a devmap'ing */
#define	PV_SEGFLAG	0x00000008L	/* Or'd in pv_va for seg id.     */
#define	PV_SSM		0x00000010L	/* ssm - segmented shared memory */

typedef struct pv_entry *pv_entry_t;
#define	PV_ENTRY_NULL	((pv_entry_t) 0)

/*
 * Data structure used to obtain memory region information from PMAP
 */
typedef struct pmr_info {
	vm_offset_t	pi_base;	/* start address of region */
	vm_offset_t	pi_size;	/* size of region */
	vm_offset_t	pi_avail;	/* start of available memory */
	int		pi_pages;	/* available pages */
	int             pi_type;        /* type of memory region */
} *pmi_t;

/*
 * Granularity Hint Region support
 */

/*
 * Maximum RADs supported
 */
#define	MAX_GH_REGIONS	64

/*
 * Supported page sizes. Order and value are important.
 */
#define GH_LG	0
#define GH_MED	1
#define GH_SM	2
#define GH_PG	3
#define GH_MAX	(GH_PG + 1)

/*
 * This structure desribes a single GH page
 */
typedef struct gh_page {
	vm_offset_t	gp_pa;		/* physical address of buffer */
	vm_size_t	gp_size;	/* page size */
	long		gp_zeroed;	/* buffer is zeroed? */
	struct gh_mad	*gp_mad;	/* MAD this page came from */
	struct gh_page	*gp_next;
	struct gh_page	*gp_prev;
} *gh_page_t;

/*
 * GH page freelist header
 */
typedef struct gh_free {
	gh_page_t	gf_next;	/* next free */
	ulong_t		gf_count;	/* # of free buffers */
} *gh_free_t;

/*
 * This describes a contiguous region of memory.
 */
typedef struct gh_region {
	vm_offset_t 		gr_pfn;		/* starting page frame number */
	vm_offset_t		gr_npf;		/* number of page frames */
	struct gh_region	*gr_next;	/* next region */
} *gh_region_t;

/*
 * The GH memory affinity domain
 */
typedef struct gh_mad {
	int			gm_mid;		/* MAD id */
	int			gm_nreg;	/* number of regions */
	struct gh_region	gm_reg;		/* one region descriptor */
	long			gm_pages;	/* # of pages reserved */
	simple_lock_data_t	gm_lock;	/* protects following fields */ 
	struct gh_free		gm_free[GH_MAX];/* free pages */
	uint_t			gm_bad[GH_MAX];	/* bad page counts */
	simple_lock_data_t	gm_collect_lock;
	int			gm_allocating;
	int			gm_collecting;
	simple_lock_data_t	gm_zeroer_lock;
	int			gm_zeroer_active;
	int			gm_zeroer_waiters;
} *gh_mad_t;

extern uint_t	*rad_gh_regions;
extern uint_t	gh_regions[MAX_GH_REGIONS];

/*
 * Physical address to NUMA region index.
 * Handles both Wildfire and previous and Marvel address layouts.
 * The *_mask values determine which.
 * pa >> numa_shift is the Wildfire and previous version
 * the rest is breaking down the Marvel address layout and interleaving
 */
#define PA_TO_MID(pa) ((((pa >> numa_shift) & numa_shift_mask) | (pa_to_mid_mask & (((pa >> 34) & (0x3 ^ ((pa >> 36) & 0x1))) | ((pa >> 7) & ((pa >> 36) & 0x1))))) >> (pa_to_mid_mask & cpu_to_rad_id_shift))

extern vm_offset_t avail_start;		/* first available physical address */
extern vm_offset_t avail_end;		/* last available physical addr + 1 */
extern vm_offset_t virtual_avail;	/* lowest avail kernel virtual addr */
extern vm_offset_t virtual_end;		/* highest avail kernel virtual addr */


/*
 * Enable segmentation
 */

#define	PMAP_SEGMENTATION	1

#define	PMAP_SEG_SIZE		(PTES_PER_PAGE * ALPHA_PGBYTES)
#define	PMAP_SEG_MASK		((PMAP_SEG_SIZE) - 1)

#define	pmap_seg_lock(SP)	simple_lock(&(SP)->ps_seglock)
#define	pmap_seg_lock_try(SP)	simple_lock_try(&(SP)->ps_seglock)
#define	pmap_seg_unlock(SP)	simple_unlock(&(SP)->ps_seglock)

#define PMAP_COPROC_INVALIDATE_STLB	0
#define PMAP_COPROC_EXIT		1

#define PDEVCMD_ONE     PMAP_COPROC_INVALIDATE_STLB
#define PDEVCMD_ALL     PMAP_COPROC_EXIT

#define ALL_THRESHHOLD	(1<<20)

#define pmap_set_coproc_tbi(pmap, func, arg) \
				pmap_coproc_tbi_setup((pmap), (func), (arg))
#define pmap_clear_coproc_tbi(pmap) \
				pmap_coproc_exit_notify(pmap)

#define pmap_load           pmap_mmu_load
#define pmap_unload         pmap_mmu_unload
#define pmap_tb             pmap_mmu_tb
#define svatophys           pmap_svatophys

#define TB_SYNC_NONE        1
#define TB_SYNC_LOCAL       2
#define TB_SYNC_ALL         4

typedef unsigned int        vm_tbop_t;

#define pmap_pageable(p_map, sva, eva, pageable)
#define	pmap_resident_count(pmap)	((pmap)->stats.resident_count)
#define pmap_resident_text(pmap)	((pmap)->stats.resident_text)
#define pmap_resident_data(pmap)	(pmap_resident_count(pmap)	\
					 - pmap_resident_stack(pmap)	\
					 - pmap_resident_text(pmap))

#define	pmap_phys_address(frame)	((vm_offset_t) (alpha_ptob(frame)))
#define pmap_phys_to_frame(phys)	((int) (alpha_btop(phys)))
#define pmap_copy(dst,src,from,len,to)
#define pmap_update()
#define pmap_kernel()			kernel_pmap

#if defined(_USE_KERNEL_PROTOS)
#define	mtpr_tbis(vaddr)	asm("call_pal 51", 3, vaddr)
#define	mtpr_tbisi(vaddr)	asm("call_pal 51", 1, vaddr)
#define	mtpr_tbisd(vaddr)	asm("call_pal 51", 2, vaddr)
#define	mtpr_tbia()		asm("call_pal 51", -2L)
#define	mtpr_tbiap()		asm("call_pal 51", -1L)
#else
#define	mtpr_tbis(vaddr)	mtpr_tbi(3, vaddr)
#define	mtpr_tbisi(vaddr)	mtpr_tbi(1, vaddr)
#define	mtpr_tbisd(vaddr)	mtpr_tbi(2, vaddr)
#define mtpr_tbia()             mtpr_tbi(-2L, (vm_offset_t)0)
#define mtpr_tbiap()            mtpr_tbi(-1L, (vm_offset_t)0)
#endif /* _USE_KERNEL_PROTOS */

#define	mtpr_virbnd(va)		asm("call_pal 19", va)
#define	mtpr_sysptbr(pfn)	asm("call_pal 20", pfn)

/*
 * Return values from pmap_lw_unwire_new()
 */
#define	LWU_SUCCESS	0
#define	LWU_HW_WIRE	1	/* has upper-level (heavy weight) wirings */
#define	LWU_AMBIGUOUS	2	/* shared pte has upper-level wirings */

/*
 * Indexes into proto_ptepage_ptetab[] (must be consistent with IS_SYS_VA)
 */
#define PT_USER	0	/* pte pages which support user space mappings */
#define PT_KERN	1	/* pte pages which support only kernel mappings */

/*
 * Data structures this module exports
 */
#ifdef _KERNEL
#ifndef REPLICATED
#define REPLICATED
#endif
extern pmap_t kernel_pmap;		/* pointer to the kernel pmap */
extern int free_ptepages_count;		/* number of free pte pages */
extern int nonseg_free_ptepages_count;	/* scavenged free pte pages */
extern int kernel_ptepages_count;	/* number of kernel pte pages */
extern int pmem_use_count;		/* count of pmem_use structures */
extern pmem_use_t pmem_use_head;	/* head of pmem_use linked list */
extern vm_offset_t virtual_avail;	/* lowest avail kernel virtual addr */
extern vm_offset_t virtual_end;		/* highest avail kernel virtual addr */
extern vm_offset_t avail_start;		/* first available physical address */
extern vm_offset_t avail_end;		/* last available physical addr + 1 */
extern REPLICATED int numa_shift;	/* PA address to NUMA region index  */
extern REPLICATED long numa_shift_mask;	/* masks in processor ID bits */
extern REPLICATED long pa_to_mid_mask;	/* masks off unused addr layout bits */
extern REPLICATED int mri_shift;	/* PA address to memory region index */
extern REPLICATED int gh_in_use;	/* granularity hints in-use flag */
extern struct pmap_mad_data pmap_mad_data;
#ifndef PMAP_INIT
extern const struct pmr_data pmr_data;	/* physical memory region data */
#endif /* PMAP_INIT */
extern const struct vas_data vas_data;	/* virtual address size data */
#endif /* _KERNEL */

#if defined(_USE_KERNEL_PROTOS)
/*
 * Prototypes
 */
struct memory_affinity_domain;
struct vm_map;
struct thread;
struct processor_affinity_group;

extern vm_offset_t
	pmap_bootstrap(long, long, vm_offset_t, vm_offset_t *),
	pmap_extract(pmap_t, vm_offset_t),
	pmap_resident_extract(pmap_t, vm_offset_t),
	pmap_resident_extract_dump(pmap_t, vm_offset_t),
	get_more_pte_pages(int, int),
	pmap_gh_vtopfn(pmap_t, vm_offset_t);

extern kern_return_t
	pmap_svatophys(vm_offset_t, vm_offset_t *),
	pmap_mmu_load(vm_offset_t, vm_offset_t, vm_size_t,
			vm_prot_t, vm_tbop_t),
	replicate_text_section(int, int);

extern pt_entry_t
	*pmap_pte(pmap_t, vm_offset_t);

extern boolean_t
	pmap_in_pal_cluster(vm_offset_t, vm_size_t),
	gh_mapper(struct vm_map *, vm_offset_t);

extern void
	end_of_boot_text(),
	pmap_numa_init(void),
	pmap_pagemove(vm_offset_t, vm_offset_t, vm_size_t),
	pmap_add_use(vm_offset_t, vm_offset_t, int),
	pmap_coproc_exit_notify(pmap_t),
	pmap_set_modify(vm_offset_t),
	pmap_zero_page(vm_offset_t),
	pmap_update_km_receive(void),
	pmap_update_um_receive(void),
	pmap_enter_range(pmap_t, vm_offset_t, vm_offset_t,
						vm_size_t, vm_prot_t),
	pmap_enter_range_devmap(pmap_t, vm_offset_t, vm_offset_t,
						vm_size_t, vm_prot_t),
	pmap_mmu_setup(vm_offset_t, vm_size_t),
	pmap_mmu_unload(vm_offset_t, vm_size_t, vm_tbop_t),
	pmap_remove_wired(pmap_t, vm_offset_t, vm_offset_t),
	mark_for_scavenge(int, vm_offset_t, vm_offset_t),
	pmap_update_send(pmap_t, vm_offset_t),
	memory_synch_point(pmap_t),
	pmap_soft_interleave(struct memory_affinity_domain *),
	pmap_update_replicated_text(vm_offset_t, vm_size_t),
	pmap_faulton_callback_setup(pmap_t, int (*func)(), unsigned int );
	
extern int
       pmap_fault_on(vm_offset_t, u_long, u_long, u_long *);

extern int
	pa_to_mid(u_long pa);

/* 
 * Assembler routines used by pmap.c
 */
extern int
	setup_nf_remove_wired_fast(long *, pmap_t *, long **, simple_lock_t *,
		vm_offset_t *, pt_entry_t **, vm_offset_t *,
		vm_size_t *, long **),
	setup_nf_ptefetch(int *, pmap_t *, long **, long *, u_long *);
#endif /* defined(_USE_KERNEL_PROTOS) */
#endif	/* defined(KERNEL) || defined(_KERNEL) */

#endif	/* !ASSEMBLER */
#endif	/* _PMAP_MACHINE_ */
