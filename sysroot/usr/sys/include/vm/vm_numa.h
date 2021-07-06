/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: vm_numa.h,v $
 * Revision 1.1.42.5  2004/07/30  14:04:52  Aaron_Biver
 * 	QAR 97930: Add new memory troller state VMMT_INIT_PENDING
 * 	[2004/06/11  17:20:47  Aaron_Biver]
 *
 * Revision 1.1.47.1  2004/05/26  16:11:00  Aaron_Biver
 * 	Add new defines for memory troller debug.
 *
 * Revision 1.1.42.4  2003/10/09  22:07:19  Jeffrey_Cilley
 * Merge Information:  Visual Merge: User specified default merge the submit tree v51bsupportos
 *     User Revision:  Jeffrey_Cilley_newubc_br:1.1.46.1 Local Ancestor:1.1.35.11
 *    Merge Revision:  v51bsupportos_br:1.1.42.3
 *   Common Ancestor:  1.1.35.11
 * 	[2003/10/09  22:00:21  Jeffrey_Cilley]
 *
 * 	Change ubc_control structure to support new UBC design.
 * 	[2003/10/03  20:27:18  Jeffrey_Cilley]
 *
 * Revision 1.1.42.3  2003/06/19  13:26:43  Matthew_McGrath
 * 	Add vm_bigpg_factor to the vm_control structure.
 * 
 * Revision 1.1.42.2  2003/06/09  20:10:59  Matthew_McGrath
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree v51bsupportos
 *     User Revision:  Matthew_McGrath_radpgc_br:1.1.43.1 Local Ancestor:1.1.35.11
 *    Merge Revision:  v51bsupportos_br:1.1.42.1
 *   Common Ancestor:  1.1.35.11
 * 	[2003/06/09  20:10:54  Matthew_McGrath]
 * 	Add va_nobucket field to vm_page_array to note the first page not
 * 	added to the vm_page_array.  Add prototype for vm_mad_page_init.
 * 	[2003/06/02  20:21:24  Matthew_McGrath]
 * 
 * Revision 1.1.42.1  2003/04/29  15:09:38  Ross_Knepper
 * 	Add ubc_control member ubc_overflow, specifying whether to overflow
 * 	large file allocation to remote MADs.
 * 
 * Revision 1.1.35.11  2002/07/16  19:47:14  Renny_Shen
 * 	Removed assumption that the first PMR is managed memory
 * 	from PA_TO_VP macro.
 * 
 * Revision 1.1.35.10  2002/07/10  21:39:51  Ross_Knepper
 * 	Change usage of ubc_control.ubc_lru_count to be dirty-only.
 * 
 * Revision 1.1.35.9  2002/06/03  21:05:57  Peter_Keilty
 * 	Modified macro PAGE_TO_MID, mid now in page struct.
 * 
 * Revision 1.1.35.8  2002/03/26  01:47:36  Renny_Shen
 * 	Modified PA_TO_VP() macro to look in the GSM MAD array
 * 	for the vpa on shared memory regions.
 * 
 * Revision 1.1.35.7  2002/02/19  18:16:37  Ross_Knepper
 * 	Add macro UC_TO_MAD().
 * 
 * Revision 1.1.35.6  2002/01/24  23:11:19  Rajesh_R
 * 	Update memory troller comments (only) for Marvel.
 * 	Added VMMT_MCHK_SYS_MAPOUT1 define for Marvel.
 * 	Added VMMT_MCHK_MARVEL_CBOX define for Marvel.
 * 	Changes by Fred Canter.
 * 
 * Revision 1.1.35.5  2002/01/10  14:02:04  Matthew_McGrath
 * 	Added troll_reg_pass to the vm_troll_reg structure to provide
 * 	an accounting of troller laps through memory.  [ECP 1702]
 * 
 * Revision 1.1.35.4  2001/11/27  21:34:33  Ross_Knepper
 * 	Remove prototype for vme_dontneed_pages.
 * 
 * Revision 1.1.35.3  2001/10/31  20:36:29  Matthew_McGrath
 * 	Added struct vm_troll_reg to describe a trollable region.
 * 	Added a pointer to a circular list of these structs to the
 * 	vm_troll_ctrl struct.  This allows the troller to support
 * 	memory holes and thus Marvel.
 * 
 * Revision 1.1.35.2  2001/10/24  22:19:43  Rajesh_R
 * 	Marvel support changes
 * 
 * Revision 1.1.35.1  2001/10/03  17:44:38  David_Bernardo
 * 	Added bigpage fields to the vm_control structure.  Removed
 * 	the following fields since they are no longer used: vm_ffl,
 * 	vm_cache_free, vm_private_cache, and vm_private_color.
 * 	Made the color bucket array multi-dimensional since there
 * 	is a color bucket array for each free list if bigpages are
 * 	enabled.
 * 
 * Revision 1.1.17.10  2001/02/05  18:44:56  Kevin_Harty
 * 	QAR 84908 pass a structure into mapol_to_vmpol and use it to
 *           correctly interpret numa memory allocation attributes.
 *           change call to mapol_to_vmpol() to pass a structure.
 * 	QAR 84911 Add prototype for vmpol_to_mpol.
 * 
 * Revision 1.1.17.9  2001/01/23  14:41:56  Lee_Schermerhorn
 * 	QAR84345:  Modified type of start/end in vm_policy to be signed type [long]
 *            to handle stack objects' negative offsets. Also fixes 84634.
 * 	QAR84148:  Change prototype of vmpol_find() to take a 3rd arg -- a pointer
 *            to a vm_policy structure.  vmpol_find() will copy any policy
 *            it finds if the ptr is non-null.
 * 
 * Revision 1.1.17.8  2001/01/04  18:13:33  Peter_Keilty
 * 	QAR-84285 NFS LOOPBACK MOUNTS HANG IN THE UBC
 * 	Change the handling of dirty NFS (loopback) pages back to NO putpage
 * 	durning the page allocation. This is issue will be address in the
 * 	next release in coordination with NFS.
 * 
 * Revision 1.1.17.7  2000/12/12  22:13:07  Peter_Keilty
 * 	Fix QAR-84134
 * 	Added clean lru lock, active scan indicator and lastscan lbolt to
 * 	the ubc_control.
 * 
 * Revision 1.1.17.6  2000/12/07  21:53:45  Peter_Keilty
 * 	PMK: Acxiom IPMT-BCGMA0M0S, QAR-83215, 83552
 * 	Add ubc_putpgcnt to ubc_control structure.
 * 	[2000/12/06  14:55:19  Peter_Keilty]
 * 	PMK: Acxiom IPMT-BCGMA0M0S, QAR-83215, 83552
 * 	Add separate clean page lru to ubc_control. Performance improvement
 * 	while stealing clean pages from LRU. Fix hang from QAR-83552.
 * 	Also add putpage list queue and waitque for new putpage thread.
 * 	Removes NFS loopback recursion issue, we don't leave dirty NFS
 * 	pages on LRU anymore.
 * 	[2000/12/01  18:31:23  Peter_Keilty]
 * 	PMK: Acxiom IPMT-BCGMA0M0S, QAR-83215
 * 	Add tunable variables to the ubc_control, ubc_pgfree_cnt,
 * 	ubc_pgtoscan_cnt, ubc_trylock_cnt, ubc_obj_maxpcnt, ubc_kluster_cnt.
 * 	Add putpage list and thread control ubc_putactive.
 * 	[2000/11/14  16:21:03  Peter_Keilty]
 * 
 * Revision 1.1.17.5  2000/11/11  01:41:42  Ernie_Petrides
 * 	Merge v51supportos-89-gertner from Zulu PK2 revision 1.1.22.3.
 * 
 * Revision 1.1.22.3  2000/11/07  20:36:43  Peter_Keilty
 * 	PMK: Acxiom IPMT-BCGMA0M0S
 * 	Add separate METADATA lru and lastscan variable to ubc_control.
 * 
 * Revision 1.1.22.2  2000/10/27  15:32:51  Ilya_Gertner
 * 	UBC buffers use all memory w Oracle create table space.
 * 	METADATA lru changes.
 * 
 * Revision 1.1.17.4  2000/10/23  20:53:57  Lee_Schermerhorn
 * 	Changed parameters to vmpolicy_add() and added prototype for
 * 	vmpolicy_cleanup().
 * 
 * Revision 1.1.17.3  2000/10/18  19:04:28  Frederick_Canter
 * 	Remove VMMT_MAX_MAD and convert troll_mad_mask to a radset.
 * 	So, the troller can support more than 64 RADs.
 * 	Add new vm_troll_initialized state (VMMT_COLD).
 * 
 * Revision 1.1.17.2  2000/09/14  12:13:31  Frederick_Canter
 * 	Define VMMT_MCHK_SYS_RESERVED to reserve code 31 for
 * 	use in arch/alpha/hal/wfcpu.c.
 * 
 * Revision 1.1.17.1  2000/09/06  12:56:38  Greg_Bellows
 * Merge Information:  Non-Visual Merge: User specified tree ericos.nightly
 *     User Revision:  yankeeos_nightly:1.1.4.32 Local Ancestor: n/a
 *    Merge Revision:  ericos_nightly:1.1.14.1
 *   Common Ancestor:  1.1.4.31
 * 
 * Revision 1.1.14.1  2000/07/07  17:40:09  Greg_Bellows
 * 	Added exempt memory base pointer and counter to vm_control.
 * 
 * Revision 1.1.4.32  2000/06/21  21:05:08  Lee_Schermerhorn
 * 	1) Modify vmpolicy_add() prototype to handle error return.
 * 	2) Rename vm_policy member vm_pad to vm_refcnt for reference
 *     counting policies
 * 	3) Modify COMPARE_VPOL() to correctly [?] compare radsets or
 *    stripe maps
 * 
 * Revision 1.1.4.31  2000/05/22  18:46:34  Anton_Verhulst
 * 	Add SC_TO_MAD.
 * 
 * Revision 1.1.4.30  2000/04/20  21:58:28  Frederick_Canter
 * 	Rearrange vm_troll_ctrl structure for better cache
 * 	locality. Added #defines to replace hardwired constants.
 * 	Moved extern variable & function declarations to vm_numa.h.
 * 	Added troll_wait_lim & troll_wait_cnt machine check waits.
 * 	Renamed troll_cur_mad to troll_cur_mid for correctness.
 * 
 * Revision 1.1.4.29  2000/03/29  17:50:13  Frederick_Canter
 * 	Add #define VMMT_MCHK_SYS_MAPOUT to memory troller #defines.
 * 
 * Revision 1.1.4.28  2000/03/25  20:04:34  Shashi_Mangalat
 * 	Add support for user specified overflow set.
 * 
 * Revision 1.1.4.27  2000/03/22  21:03:40  Stephen_Corbin
 * 	Add vmpol_free and vmpolicy_smap_create prototypes.
 * 
 * Revision 1.1.4.26  2000/03/16  23:03:12  Shashi_Mangalat
 * 	Changes to support vm_page/pvh merge and local wait channel.
 * 	Also, move VM_STACK_FREE_TARGET to vm_tune.h.
 * 
 * Revision 1.1.4.25  2000/03/16  16:32:13  Frederick_Canter
 * 	Extend vm_mad_t (VM MAD structure) for memory troller.
 * 
 * Revision 1.1.4.24  2000/03/09  23:35:01  Stephen_Corbin
 * 	Fixed a bug in COMPARE_VPOL.  Added function prototypes.
 * 
 * Revision 1.1.4.23  2000/02/24  22:16:15  Shashi_Mangalat
 * 	Add VM_POLICY_MID_SI() macro which returns stripe index also.
 * 
 * Revision 1.1.4.22  2000/02/07  20:04:34  Stephen_Corbin
 * 	Fix VM_POLICY_MID macro.  Remove VM_POLICY_VC macro.
 * 	Add VM_POLICY_POL macro.
 * 
 * Revision 1.1.4.21  2000/01/28  21:16:42  Ross_Knepper
 * 	Insert #define VM_STACK_FREE_TARGET (from vm_resident.c).
 * 	[2000/01/27  22:49:10  Ross_Knepper]
 * 
 * Revision 1.1.4.20  2000/01/27  20:28:04  Ernie_Petrides
 * 	Add prototype for mapol_to_vmpol().
 * 
 * Revision 1.1.4.19  2000/01/12  22:57:45  Dean_Gagne
 * 	For the error survivability project, change all references to
 * 	pg_phys_addr to use the page_to_phys macro.
 * 
 * Revision 1.1.4.18  1999/12/22  21:59:28  Shashi_Mangalat
 * 	Add striped memory allocation support.
 * 
 * Revision 1.1.4.17  1999/11/23  21:38:57  Stephen_Corbin
 * 	Implementation of nmadvise for anonymous memory.
 * 
 * Revision 1.1.4.16  1999/11/01  23:49:20  Shashi_Mangalat
 * 	Cache align swap_control and domain structures.
 * 
 * Revision 1.1.4.15  1999/09/25  20:44:55  Shashi_Mangalat
 * 	Change MID_TO_MAD() to return NULL if MAD is not allocated.
 * 
 * Revision 1.1.4.14  1999/08/16  22:19:23  Stephen_Corbin
 * 	Support for per-MAD Object/Offset Hash Queues.
 * 	[1999/08/16  22:06:56  Stephen_Corbin]
 * 
 * Revision 1.1.4.13  1999/08/05  20:47:13  Shashi_Mangalat
 * 	Make max. kmemreserve/kmempriv per-RAD.
 * 	Streamline UBC control structure.
 * 	Cache align data structures.
 * 	[1999/08/04  13:19:53  Shashi_Mangalat]
 * 
 * Revision 1.1.4.12  1999/07/19  21:50:31  Anton_Verhulst
 * 	idset_p becomes radset_t.
 * 	[1999/07/19  21:45:12  Anton_Verhulst]
 * 
 * Revision 1.1.4.11  1999/07/14  19:45:40  James_Woodward
 * 	remove u_mad from thread structure and use u_rad pointer.
 * 	[1999/07/12  18:48:39  James_Woodward]
 * 
 * Revision 1.1.4.10  1999/06/21  19:27:43  David_Anderson
 * 	Changed vm_policy's vp_mid_set type from idset_t to idset_p.
 * 	Added VM_POLICY_PREF(), VM_POLICY_DIRECT(), VM_POLICY_MID(),
 * 	VM_POLICY_TYPE(), VM_POLICY_MAD() and VM_POLICY_VC() macros.
 * 	[1999/06/21  15:18:55  David_Anderson]
 * 
 * Revision 1.1.4.9  1999/06/21  14:06:10  James_Woodward
 * 	add rad.h and rad structure
 * 	[1999/06/17  12:20:11  James_Woodward]
 * 
 * Revision 1.1.4.8  1999/06/14  13:58:02  Jeff_Colburn
 * 	Add fields to store scan depth, etc in the UBC control
 * 	structure.  These fields are used by the new UBC paging
 * 	thread.
 * 	[1999/06/04  21:46:58  Jeff_Colburn]
 * 
 * Revision 1.1.4.7  1999/05/25  19:54:38  James_Woodward
 * 	change CURRENT_MAD, and CURRENT_MID to assume u.u_mad always set.
 * 	[1999/05/25  15:14:07  James_Woodward]
 * 
 * Revision 1.1.4.6  1999/05/07  11:55:35  James_Woodward
 * 	fix to merge of steelbl23 pass 3.
 * 	[1999/05/07  11:49:06  James_Woodward]
 * 
 * Revision 1.1.4.5  1999/05/06  19:35:26  Shashi_Mangalat
 * 	Merge of STEELOS_BL21:STEELOS_BL23
 * 	 Revision 1.1.7.5  1999/03/25  23:03:13  Shashi_Mangalat
 * 	 Merge of PTFCOS_BL5:PTFCOS_BL6: add vm_private_color.
 * 	 Revision 1.1.7.4  1999/03/19  20:06:40  Ernie_Petrides
 * 	 Add some padding in the memory_affinity_domain and vm_control
 * 	 structures to help improve cache line locality, fix declarations
 * 	 of simple lock fields, and revise references to processor_mad field.
 * 	[1999/05/06  19:30:00  Shashi_Mangalat]
 * 
 * Revision 1.1.4.4  1999/05/03  19:28:48  David_Anderson
 * 	Moved global kernel stack queue data to per-MAD vm_control structures.
 * 	[1999/04/30  15:33:01  David_Anderson]
 * 
 * Revision 1.1.4.3  1999/03/09  23:49:39  Shashi_Mangalat
 * 	Merge of STEELOS_BL21
 * 	 VM/NUMA scalability enhancements.
 * 	[1999/03/09  23:44:41  Shashi_Mangalat]
 * 
 * Revision 1.1.4.2  1998/08/26  12:43:56  James_Woodward
 * 	Merge of numaproj and zulu
 * 	[1998/07/29  20:18:51  James_Woodward]
 * 
 * Revision 1.1.2.5  1998/07/08  15:42:04  Shashi_Mangalat
 * 	Add RID_ANY.
 * 	[1998/07/08  14:10:50  Shashi_Mangalat]
 * 
 * Revision 1.1.2.4  1998/05/18  21:21:37  Shashi_Mangalat
 * 	Add CURRENT_RID().
 * 	[1998/05/18  20:41:18  Shashi_Mangalat]
 * 
 * Revision 1.1.2.3  1998/04/20  21:45:52  Shashi_Mangalat
 * 	Move default policy to mad.
 * 	[1998/04/20  21:32:39  Shashi_Mangalat]
 * 
 * Revision 1.1.2.2  1998/04/09  21:14:49  Shashi_Mangalat
 * 	NUMA support.
 * 	[1998/04/09  20:24:46  Shashi_Mangalat]
 * 
 * 
 * $EndLog$
 * 
 * 
 * 
 * 
 */
/*
 * @(#)$RCSfile: vm_numa.h,v $ $Revision: 1.1.42.5 $ (DEC) $Date: 2004/07/30 14:04:52 $
 */
#ifndef	_VM_VM_NUMA_H_
#define	_VM_VM_NUMA_H_

#include <vm/vm_gsm.h>

#ifdef	_KERNEL
/*
 * The Memory Affinity Domain (MAD) and associated structures.  A MAD is a set
 * of physical memory pages associated with a NUMA region (or Application
 * Resource Partition)
 */

#ifdef _BASE_KERNEL_PRIVATE /* see sys/systm.h - kernel binary compatibility */
/*
 * Access to the structures and macros defined in this header file is
 * limited to BaseOS components only.  Layered products or other applications
 * should not be including this file, since the definitions may change
 * across releases.
 */

/*
 * VM controlling data for a Memory Affinity Domain
 */
typedef struct vm_control {
    /* 64-byte alignment */
	simple_lock_data_t vm_queue_lock;	/* active/inactive queues lock*/
	struct vm_page	*vm_queue_active;	/* active memory queue */
	struct vm_page	*vm_queue_inactive;	/* inactive memory queue */
	uint_t		vm_active_count;	/* #pages active */
	uint_t		vm_inactive_count;	/* #pages inactive */
	boolean_t     	vm_deactivating;	/* populating inactive list */
	uint_t     	vm_deact_burst;		/* max pages to deactivate */
	uint_t		vm_deact_ticks;		/* deactivate timeout */
	uint_t		vm_wiredpages;		/* wired pages */
	uint_t		vm_queue_lock_want;	/* lock wanted */
	uint_t		vm_sched_ticks;		/* vm_mem_sched() interval */
	uint_t		vm_sched_timeout;	/* timeout = hz/ticks */
	uint_t		vm_primary;		/* timeout primary cpu */

    /* 64-byte alignment */
	uint_t		vm_pageout_burst;	/* max pageout I/O */
	uint_t		vm_prewrite_target;	/* prewrite threshold */
	uint_t		vm_free_optimal;	/* threshold for task swap */
	uint_t     	vm_free_swap;		/* threshold task swap */
	uint_t     	vm_free_hardswap;	/* stop anon swap above this */
	boolean_t	vm_vps_failed;		/* page stealer failed */
	uint_t		vm_vps_fail_stamp;	/* inactive stamp when failed */
	uint_t		vm_vps_inact_stamp;	/* inactive list update stamp */
	uint_t		vm_zfree_count;		/* # zeroed pages free */
	uint_t		vm_zfree_wanted;	/* wants zeroed pages */
	uint_t		vm_cluster;		
	int		vm_private_text;
	long		spare1[2];

    /* 64-byte alignment */
	simple_lock_data_t vm_free_lock;	/* free list lock */
	uint_t		vm_free_count;		/* #pages free */
	uint_t		vm_free_reserved;	/* #pages reserved for pageout*/
	uint_t		vm_free_target;		/* #pages we want free? */
	uint_t		vm_free_min;		/* When to wakeup pageout */
	uint_t		vm_free_wanted;		/* wants free pages */

	uint_t		vm_bigpg_free_thresh[3];/* don't coalesce below this */
	uint_t		vm_bigpg_free_count[4]; /* # free of each page size */

	struct wait_queue
			*vm_wait_q;		/* local wait channel */

    /* 64-byte alignment */
	ulong_t		vm_lfree_ave;		/* long term free average */
	ulong_t		vm_sfree_ave;		/* short term free average */
	ulong_t		vm_pagecleanrecs;	/* VM page clean reclaims */
	int		vm_wired_pcnt;		/* percentage wired pages */
	int		spare3;
	ulong_t		vm_rmwiredpages;	/* RM wired pages */
	struct vm_page	*vm_contig_pages;	/* contig_malloc pages */
	ulong_t		vm_contig_count;	/* "" page count */
	long		spare4;

    /* 64-byte alignment */
	int		vm_cowfaults;		/* Copy point */
	int		vm_maxrss;
	uint_t		vm_rss_block_target;	/* RSS management */
	uint_t		vm_rss_wakeup_target;
	int		vm_rss_blocked;
	int		vm_contig_state;	/* contig malloc state */
	struct vm_page	*vm_queue_untested;	/* untested pages */
	struct vm_page	*vm_queue_bad;		/* bad pages, if any */
	struct vm_page	*vm_queue_dump;		/* holds crash dump */
	uint_t		vm_managed;		/* managed page count */
	uint_t 		vm_bad_count;		/* # bad pages */
	long		spare5;

    /* 64-byte alignment */
	simple_lock_data_t vm_swap_io_lock;	/* */
	int 		vm_swap_async_iocount;	/* oustanding I/O */
	int 		vm_swap_async_iomax;	/* MAX */
	int 		vm_swap_async_want;	/* want buffer */
	int 		vm_swap_sync_iocount;	/* oustanding I/O */
	int 		vm_swap_sync_iomax;	/* MAX */
	int 		vm_swap_sync_want;	/* want buffer */
	int 		vm_swap_rcluster;	/* read cluster size */
	int 		vm_swap_wcluster;	/* write " */
	vm_size_t	vm_swap_pgl_size;	/* write " */
	struct vm_page_bucket
			*vm_swap_hash;		/* swap Object/Offset hash */
	uint_t		vm_swap_hash_count;	/* "" table size */
	uint_t		vm_swap_hash_mask;	/* "" mask */

    /* 64-byte alignment */
	boolean_t	vm_segmentation;	/* segmentation enabled? */
	int 		vm_seg_cache_max;	/* */
	vm_offset_t	vm_seg_start;		/* */
	vm_offset_t	vm_seg_end;		/* */
	vm_offset_t	vm_seg_size;		/* */
	vm_offset_t	vm_seg_mask;		/* */
	boolean_t	vm_swap_eager;		/* eager swap enabled? */
	int		spare6;
	struct thread	*vm_pageout_thread;	/* pageout thread */
	long		spare7;

    /* 64-byte alignment */
	simple_lock_data_t vm_stack_queue_lock; /* kernel stack queue lock */
	queue_head_t    vm_stack_queue;		/* kernel stack queue head */
	int             vm_stack_free_count;    /* current free stack pages */
	int             vm_stack_free_target;   /* desired free stack pages */
	int             vm_need_stack_wakeup;   /* threads waiting for stack */
	int		spare8;
	struct vm_page	*vm_exempt_pages;	/* exempt pages pointer */
	ulong_t		vm_exempt_count;	/* exempt pages count   */
	long		spare9[1];

    /* 64-byte alignment */
	uint_t		vm_bigpg_enabled;	/* bigp enabled for system? */
	uint_t		vm_bigpg_anon;		/* bigp enabled for anon? */
	uint_t		vm_bigpg_seg;		/* bigp enabled for seg? */
	uint_t		vm_bigpg_shm;		/* bigp enabled for shm? */
	uint_t		vm_bigpg_ssm;		/* bigp enabled for ssm? */
	uint_t		vm_bigpg_stack;		/* bigp enabled for stack? */
	uint_t		vm_bigpg_factor;	/* setting for gh factor */
	uint_t		vm_l3gh_anon;		/* l3gh enabled for anon? */
	uint_t		vm_l3gh_shm;		/* l3gh enabled for shm? */
	uint_t		vm_l3gh_ssm;		/* l3gh enabled for ssm? */
	ulong_t		spare10[3];
} *vm_cntl_t;

/*
 * Malloc controlling data.
 */
typedef struct malloc_control {
	struct kmembuckets	*m_buckets;	/* kmem buckets */
	struct thread		*m_thread;	/* GC thread */
	long			m_bwait;	/* bit mask of bucket waits */
	uint_t			m_mid;		/* MAD  id */
	uint_t			pad1[9];

    /* 64-byte alignment */
	simple_lock_data_t	m_lock;		/* protects following fields */
	struct ksegpage		*m_rpages;	/* reserve pages */
	int			m_rcnt;		/* reserve page count */
	int			m_maxrcnt;	/* max. reserve page count */
	struct ksegpage		*m_ppages;	/* privilege pages */
	int			m_pcnt;		/* privilege page count */
	int			m_maxpcnt;	/* max. privilege page count */
	struct ksegpage		*m_pages;	/* all pages */
	int			m_cnt;		/* total page count */
	int			pad2[3];
} *m_cntl_t;

/*
 * UBC controlling data
 */
typedef struct ubc_control {
    /* 64-byte alignment */
	simple_lock_data_t 
			ubc_lru_lock;		/* active queues lock*/
	simple_lock_data_t 
			ubc_pages_lock;
	struct vm_page	*ubc_actlru;		/* Active lru list */
	int		ubc_pages;		/* Total pages used UBC */
	int		ubc_wiredpages;		/* Total wired pages */
	int		ubc_actlru_cnt;		/* #pages in act list */
	int		ubc_actscan;		/* scanning active pgs */
	int		ubc_lru_scan;		/* lru scan length */
	int		ubc_pg_locked;		/* max # pages locked at once*/
	int		ubc_overflow;		/* overflow to remote RADs? */
	int		ubc_kluster_cnt;	/* max #pages to kluster */
	long		ubc_act_lastscan;	/* lbolt */

    /* 64-byte alignment */
	simple_lock_data_t 
		ubc_inactlru_lock;		/* inactive queues lock */
	struct vm_page  *ubc_inactlru;		/* Inactive lru list */
	struct vm_page	*ubc_inactive_scan_pgptr;/* current scan position */
	int	ubc_inactlru_cnt;		/* #pages in inact list */
	int	ubc_inactscan;			/* scanning inactive pgs */
	long	ubc_inact_lastscan;		/* lbolt */
	int	ubc_borrowlimit;
	int	ubc_seqdrain;			/* Sequential drain threshold */
	int	ubc_seqpercent;
	int	ubc_pagesteal;			/* steal clean pages */
	int	ubc_pgfree_cnt;			/* #pages to free/steal */
	int	ubc_pgtoscan_cnt;		/* #pages to scan free/steal */

    /* 64-byte alignment */
	int	ubc_trylock_cnt;		/* # lock tries of object */
	int	ubc_obj_maxpcnt;		/* max pages before push */  
	int	ubc_cache_free;
	int	ubc_ffl;
	int	ubc_maxpages;
	int	ubc_minpages;
	int	ubc_prewritemult;
	int	ubc_approxlow;
	int	ubc_approxhigh;
	int	ubc_busy_cnt;
	int	ubc_dirty_metadata_count;
	int	ubc_dirty_metadata_pcnt;
	int	ubc_lru_lock_want;
	int	ubc_free_waiters;
	int	pad2[2];

    /* 64-byte alignment */
	simple_lock_data_t 
		ubc_dirty_lock;			/* Overloaded */
	int	ubc_dirty_pages;		/* total dirty pages in ubc */
	int	ubc_iocount;			/* outstanding I/O */
	int	ubc_buffers;			/* io limit for purging */
	int	ubc_dirty_min;			/* minimum dirty pages */
	int	ubc_dirty_wra;
	int	ubc_dirty_pcnt;			/* max pages to examine */
	boolean_t	
		ubc_active;			/* ubc is cleaning up */
	int	ubc_purge_burst;
	int	ubc_purge_shortage;
	int	ubc_purge_scandepth;
	struct thread
		*ubc_purge_thread;
	int	ubc_dirty_seconds;
	int	ubc_deactivating; 
} *ubc_cntl_t;

typedef struct swap_control {
	/*
	 * Task swapper data
	 */
	simple_lock_data_t sc_qlock;
	queue_head_t	sc_iq;			/* inswapped queue */
	queue_head_t	sc_owq;			/* outswap work queue */
	int		sc_icnt;		/* inswapped count */
	int		sc_owcnt;		/* outswapped work count */
	struct thread	*sc_ithread;		/* inswap thread */
	long		pad0;

    /* 64-byte alignment */
	queue_head_t	sc_oq;			/* outswapped queue */
	queue_head_t	sc_iwq;			/* inswap work queue */
	int		sc_ocnt;		/* outswapped count */
	int		sc_iwcnt;		/* inswap work count */
	struct thread	*sc_othread;		/* outswap thread */
	boolean_t	sc_active;		/* swapper active */
	int		sc_pad;			/* */
	int		sc_aggr;		/* aggressive swap */
	int		sc_iticks;		/* inswap ticks */

    /* 64-byte alignment */
	ulong_t		sc_iswaps;		/* #of inswaps */
	ulong_t		sc_oswaps;		/* #of outswaps */

	/*
	 * Thread swapper data
	 */
	simple_lock_data_t sc_t_qlock;
	queue_head_t	sc_t_iq;		/* inswap queue */
	struct thread	*sc_t_ithread;		/* inswap thread */
	boolean_t	sc_t_active;		/* swapper active */
	long		pad1;
} *swap_cntl_t;

/*
 * Object/Offset Hash Queue
 */
typedef struct vm_page_oohq {
	struct vm_page_bucket	*vm_oo_buckets;		/* array of queues */
	int			vm_oo_hash_mask;
	int			vm_oo_bucket_count;	/* # of queues */
} vm_page_oohq_t;

extern vm_page_oohq_t		vm_page_oohq;		/* global o/o queue */

#define	VM_MAD_BUCKETS		1		/* corbin XXX test code */

#if defined(VM_MAD_BUCKETS)

extern int			vm_page_mad_buckets;	/* sysconfig param */

#define vm_page_buckets		md_page_oohq.vm_oo_buckets
#define vm_page_hash_mask	md_page_oohq.vm_oo_hash_mask
#define vm_page_bucket_count	md_page_oohq.vm_oo_bucket_count
#define vm_page_hash(mid, object, offset)		\
	((((unsigned)object>>3)+(unsigned)atop(offset))	\
	 & (MID_TO_MAD(mid)->vm_page_hash_mask))

#else	/* !VM_MAD_BUCKETS */

#define vm_page_buckets		vm_page_oohq.vm_oo_buckets
#define vm_page_hash_mask	vm_page_oohq.vm_oo_hash_mask
#define vm_page_bucket_count	vm_page_oohq.vm_oo_bucket_count
#define vm_page_hash(object, offset) 			\
	((((unsigned)object>>3)+(unsigned)atop(offset))	\
	 & (vm_page_hash_mask))

#endif	/* VM_MAD_BUCKETS */


/*
 * Distinguished MIDs
 */
#define	MID_LOCAL	-1	/* MID unspecified */
#define	MID_INVALID	-2	/* invalid MID */
#define	MID_NOMEM	-3	/* no-existent memory on MID */
#define	MID_ANY		-4	/* any MID */

/*
 * VM page allocation is controlled by a policy selected by the caller.
 */
typedef enum {
	VM_PAGE_LOCAL,	/* try to allocate from local memory region */
	VM_PAGE_PREF,	/* try to allocate from specified region */
	VM_PAGE_DIRECT,	/* allocate from specified region only */
	VM_PAGE_STRIPED	/* allocate across MADs in vp_radset */
} vm_pol_t;

/*
 * vm_policy:  specifies NUMA allocation policy for range of an object.
 *
 * These structs are maintained in a linked list anchored in the object,
 * by vmpol_insert().
 *
 * Note:  start/end are 'long' rather than 'vm_offset_t' because stack
 *        objects can use negative offsets.
 */
typedef struct vm_policy {
	struct vm_policy	*vp_next;	/* linked list ptr */
	struct vm_policy	*vp_prev;	/* linked list ptr */
	long			vp_start;	/* start offset of range, */
						/* page aligned down */
	long			vp_end;		/* end offset of range, */
						/* page aligned up */
	vm_pol_t		vp_policy;	/* allocation policy */
	union uvp1 {
		uint_t		uvp_mid;	/* mid to allocate from */
		uint_t		uvp_nstripes;	/* number of stripes to use */
	} vp_u1;
	int			vp_stride;	/* stripe length */
	int			vp_refcnt;	/* reference count */
	union uvp2 {
		radset_t	uvp_radset;	/* set of memory regions ids */
		int		*uvp_smap;	/* stripe map */
	} vp_u2;
	vm_offset_t		vp_offset;	/* stripe allocation offset */
    /* 64-byte alignment */
} *vm_policy_t;

#define vp_mid		vp_u1.uvp_mid
#define vp_nstripes	vp_u1.uvp_nstripes
#define vp_radset	vp_u2.uvp_radset
#define vp_smap		vp_u2.uvp_smap

#define COMPARE_VPOL(v1,v2) (((v1)->vp_policy == (v2)->vp_policy) &&	\
			     ((v1)->vp_mid    == (v2)->vp_mid) &&	\
			     ((v1)->vp_stride == (v2)->vp_stride) &&	\
			     __vmpolicy_equiv_sets(v1, v2))

typedef struct vm_page_array {
	vm_offset_t		va_start;	/* pa of first managed page */
	int			va_pages;	/* # managed pages */
	int			va_pad1;	/* */
	struct vm_page		*va_vmp;	/* vm page array */
	struct vm_page		*va_tested;	/* highest tested page */
	struct vm_bigpage	*va_bigpg;	/* bigpage state array */
	vm_offset_t		va_nobucket;	/* pa of first managed page
						 * never on a colorbucket */
	long			va_pad2[2];	/* */
    /* 64-byte alignment */
} *vm_page_array_t;

/*
 * VM memory troller status values.
 */
typedef enum {
	VM_TROLL_INACTIVE,
	VM_TROLL_ACTIVE,
	VM_TROLL_CONTINUE,
	VM_TROLL_BAD_PAGE_FOUND,
	VM_TROLL_BAD_PAGE_WAIT
} vm_troll_status_t;

#define	VM_TROLL_PA_VALID	1

/* Conditional compile for VM memory troller debug code.
 * Used by: vm_pagelru.c, vm_resident.c, arch/alpha/hal/wfcpu.c,
 *	    arch/alpha/hal/marvel_cpu.c.
 */
/*#define VMMT_DEBUG_BASE*/
/*#define VMMT_DEBUG*/

#ifdef VMMT_DEBUG 


/*
 * The following exists to insert errors into the memory troller.  It
 * consists of a variable which contains a bitmask where each bit
 * represents a possible error to insert, a set of bits, and some
 * macros to abstract the reading/writing of the bitmask variable.
 *
 * It can be set or cleared from kernel code, or possibly from a
 * sysconfig variable (if one is implemented).
 *
 * Possible values so far are:
 *
 *   VMMT_FAIL_SETCREATE	
 *	This tests the memory troller's ability to handle things
 *	gracefully when {rad,cpu}setcreate() calls fail.  The failure
 *	is actually inserted in vmmt_set_rad() (right after
 *	radsetcreate() and cpusetcreate() are called).  The number of
 *	times it will fail is finite, and is controlled by a local
 *	variable at the point of failure.  Once it has failed enough
 *	times, it will continue normally, and the failure counter will
 *	be reset for future operations.
 *
 * 
 */

/* Variable */
extern u_long vmmt_insert_failure_mask;

/* 
 * Macros to abstract the fact that this is a 64-bit bitmask.  This
 * way, if we ever outgrow it or feel a need to change the
 * implementation, we can change it without changing the interface.
 */

/* Check to see if a subset of bits is set */
#define VMMT_FORCE_FAIL_CHECK(x) (vmmt_insert_failure_mask &   (x))

/* Set a subset of bits */
#define VMMT_FORCE_FAIL_SET(x)   (vmmt_insert_failure_mask |=  (x))

/* Clear a subset of bits */
#define VMMT_FORCE_FAIL_CLEAR(x) (vmmt_insert_failure_mask &= ~(x))

#else

#define VMMT_FORCE_FAIL_CHECK(x)
#define VMMT_FORCE_FAIL_SET(x) 
#define VMMT_FORCE_FAIL_CLEAR(x) 

#endif

/* Error insertion bits */
#define VMMT_FAIL_SETCREATE  0x0000000000000001UL  /* QAR 97930 force failures
						    * in calls to *setcreate()*/


/*
 * VM memory troller control structure, constants, and externs.
 */
#define VMMT_PFN_TICK		64	/* default number of PFNs per tick */

extern int vm_troll_error_wait;
extern int vm_troll_interval;

extern int vm_troll_initialized;	/* vm_troll_initialized states        */
#define VMMT_RUNNING		1	/* troller is configured and running  */
#define VMMT_STOPPING		0	/* vm_primary CPU(s) went off-line    */
#define VMMT_RECONFIG		2	/* troller needs to be reconfigured   */
#define VMMT_COLD		-1	/* delay start until troller init'ed */
#define VMMT_INIT_PENDING	3	/* Initialization is in progress      */

#define	VMMT_TROLL_PERCENT	4	/* default troll_percent setting      */

					/* vm_troller_start() arguments       */
#define VMMT_START		0	/* cold start or restart after stop   */
#define VMMT_RESTART		1	/* restart, vm_primary going off-line */

struct vm_troll_reg {
	struct vm_troll_reg *troll_reg_next;
					/* pointer to the next region; these
					 * form a circular list */
	unsigned int troll_reg_pfnbase;	/* First PFN of the troll_region */
	unsigned int troll_reg_pfns;	/* # of PFNs in the troll_region */
};

struct vm_troll_ctrl {			/* All elements are per-MAD	    */
    long		troll_pass;	/* # of completed passes of this MAD*/
    long		pad;
					/* VMMT_DEBUG_ALWAYS                */
    int			troll_db_okay;	/* # of pages OKAY to troll	    */
    int			troll_db_troll;	/* # of pages actually trolled      */
    int			troll_db_skip;	/* # of pages skipped (PAL owned)   */
    int			troll_db_outr;	/* # of out of range pages          */
    long		troll_db_rpcc;	/* # of cycles to troll a page      */
    struct vm_troll_reg	*troll_regions; /* pointer into a circular list of
					 * trollable regions		    */
    struct vm_troll_reg	*troll_first_reg;/*First of the list of trollable
					 * regions			    */
    unsigned int	troll_numregs;	/* # of trollable regions in the MAD*/
    int			troll_tpc_sync;	/* synchronize troll_percent change */
					/* 64-byte alignment		    */
    unsigned long	troll_physaddr;	/* DBE memory address + valid bit   */
    unsigned int	troll_pfn;	/* PFN currently being trolled      */
    unsigned int	troll_pfncnt;	/* count of PFNs trolled (so far)   */
    unsigned int	troll_percent;	/* copy of vm_troll_percent tunable */
    unsigned int	troll_pfntick;	/* PFN tick, to smooth troll rate   */
    unsigned int	troll_quantity;	/* # of PFNs to troll per interval  */
    vm_troll_status_t	troll_status;	/* current trolling status	    */
    unsigned long	troll_ret_pc;	/* longjmp PC - vm_memory_troller() */
    unsigned int	troll_wait_lim;	/* max # of Usec to wait for MCHK   */
    unsigned int	troll_wait_cnt;	/* # of Usec waited for MCHK	    */
    int			troll_num_mads;	/* # of MADs managed by vm_primary  */
    int			troll_cur_mid;	/* # number of current active MAD   */
    radset_t		troll_radset;	/* IDs MADs managed by vm_primary   */
};

/*
 * VM memory troller <=> hardware platform machine check handling
 * interface definitions. The platform's machine check handler calls
 * troll_active_query() with one of these types as the first argument.
 * Machine check delivery is messy (to say the least) on Wildfire. There
 * can be as many as four machine checks associated with one uncorrectable
 * memory error. They can be delivered to the boot CPU and/or secondaries.
 * There is no machine check delivery ordering guarantee. Hopefully, the
 * next platform will have more deterministic machine check delivery ;-)
 * If a platform only delivers one machine check, then it will need to
 * call troll_active_query() [VMMT_MCHK_PROCESSOR or a new mc_type] to
 * force the troller into the VM_TROLL_BAD_PAGE_WAIT state.
 *
 * See arch/alpha/hal/{wfcpu.c,marvel_cpu.c} for usage of these #defines.
 */

/* Synchronous processor detected machine check. This occurs when a load
 * instruction fills the cache from memory and a uncorrectable error occurs.
 * The machine check is dismissed if caused by the troller.
 */
#define VMMT_MCHK_PROCESSOR	0L

/* Asynchronous system detected machine check (reported by system hardware,
 * usually the memory controller). On Wildfire these are delivered to the
 * boot CPU (but that may not be true on future platforms). This machine
 * check contains the memory address (which is used to determine if the
 * machine check was caused by the troller and can be dismissed).
 */
#define VMMT_MCHK_SYS_MEM	1L

/* Asynchronous system detected machine check (reported by system hardware,
 * on wildfire these come from the Hswitch and/or GP). These may not occur
 * on future platforms (or existing bus-based platforms). This error type
 * is deliered to the boot CPU on Wildfire (but, that may not be the case
 * on future systems). These errors may be bundled with a VMMT_MCHK_SYS_MEM
 * machine check by the PALcode or may be delivered as separate machine
 * checks. This type error is also dismissed if caused by the troller.
 */
#define VMMT_MCHK_SYS_HSL	2L
#define VMMT_MCHK_SYS_GPL	3L	/* not passed to troll_active_query */

/* Asynchronous system detected machine check with no error bits set.
 * On Wildfire, these can occur as a side effect of trolling, due to
 * error state changing between the time PAL dispatches the machine
 * check and the OS reads the error CSRs. It's safe to dismiss these.
 */
#define VMMT_MCHK_SYS_EMPTY	4L	/* not passed to troll_active_query */

/*
 * Indicates a uncorrectable memory machine check occured with a memory
 * address of a page that is completely mapped out, meaning:
 *	The page's bit is cleared in the console's PFN bitmap.
 *	The page is marked bad in it's vm_page structure.
 *	The page is on the MAD's bad page queue (vm_queue_bad).
 */
#define VMMT_MCHK_SYS_MAPOUT	5L	/* not passed to troll_active_query */
#define VMMT_MCHK_SYS_MAPOUT1	6L	/* variant needed for Marvel */

/* Synchronous processor detected machine check. This occurs when a load
 * instruction fills the cache from memory and a uncorrectable error occurs.
 * The machine check is dismissed if resulted from trolling.
 * Marvel specific variant of VMMT_MCHK_PROCESSOR.
 */
#define VMMT_MCHK_MARVEL_CBOX	7L

/*
 * RESERVED: see arch/alpha/hal/{wfcpu.c,marvel_cpu.c}
 */
#define VMMT_MCHK_SYS_RESERVED	31L

/*
 * A domain may have more than one contiguous memory region if there are
 * holes.  Therefore, the color buckets and the vm_page arrays are two
 * dimensional.
 */
typedef struct memory_affinity_domain {
    /* 64-byte alignment */
	int			md_type;	/* type of MAD */
	uint_t			md_mid;		/* MID */
	radset_t		md_radset;	/* overflow set */
	cpuset_t		md_cpu_set;	/* cpus in this MAD */
	struct vm_page		***md_vmc;	/* color buckets */
	unsigned long		md_color_mask;	/* "" mask */
	vm_page_array_t		md_vpa;		/* vm_page arrays */
	int			md_nreg;	/* # of "" */
	int			md_domain_init;	/* domain initialized */
	char			pad1[8];
    /* 64-byte alignment */
	struct vm_control	md_vm;		/* VM data */
	struct malloc_control	md_malloc;	/* malloc data */
	struct ubc_control	md_ubc;		/* UBC data */
	struct swap_control	md_swap;	/* swapper data */
	vm_page_oohq_t		md_page_oohq;	/* obj/off hash queue */
	long			pad2[6];	/* pad out the alignment */
    /* 64-byte alignment */
	struct vm_troll_ctrl	md_troll;	/* memory troller ctrl struct */
    /* 64-byte alignment */
} *vm_mad_t;

/* Memory troller externs (must be after vm_mad_t declared). */
extern void		vm_memory_troller(void);
extern void		adjust_troll_quantity(vm_mad_t);
extern vm_mad_t		vmmt_get_mad(int);
extern void		vmmt_set_mad(void);
extern void		vmmt_shutdown_mads(vm_mad_t mad);

/*
 * Type of MAD
 */
#define	MD_NUMA	0		/* NUMA */
#define	MD_ARP	1		/* Application Resource Partition */

/*
 * All NUMA domains are linked into the vm_mads array.  The size of the array
 * is given by numa_nodes.  There may be empty slots, where there is no memory.
 * Dynamically allocated domains (partitions) are not in this table.
 */

/*
 * NUMA VM policies can be passed in any of three manners:
 *
 *  1. A pointer to a properly initialized vm_policy structure.
 *  2. VM_POLICY_NULL, which will cause the default policy, or local NUMA
 *     region to be used.
 *  3. Either of the two shorthand macro "codes", VM_POLICY_PREF() or
 *     VM_POLICY_DIRECT(), both of which take a mid as an argument.
 *
 *  Since most in-kernel vm_policy type requests are either VM_PAGE_LOCAL,
 *  VM_PAGE_PREF or VM_PAGE_DIRECT, the use of either VM_POLICY_NULL or the
 *  shorthand macro codes alleviates the responsibility of the caller to be
 *  cognizant of the details of the vm_policy structure, as well as having to
 *  allocate, populate and maintain a vm_policy structure.
 *
 *  Regardless of which format is used, the consumer function can in turn
 *  pass the code or pointer to one of several other macros to extract the
 *  policy type, mid, or pointers to the appropriate memory_affinity domain
 *  vm_control structures:
 *
 *  1. VM_POLICY_MID() returns the mid.
 *  2. VM_POLICY_POL() returns the policy.
 *  3. VM_POLICY_TYPE() returns the select type: VM_PAGE_LOCAL, VM_PAGE_PREF,
 *     VM_PAGE_DIRECT or VM_PAGE_STRIPED.
 */

#define	VM_POLICY_NULL	(vm_policy_t)0		/* use default policy */

/*
 * TRUE if policy parameter is a "shorthand" code.
 * Depends on all policy struct addresses being kernel VAs -- i.e.,  <0
 */
#define VM_POLICY_CODE(policy)   ((policy) && !((long)(policy) < 0))
#define VM_POLICY_CODE_SHIFT (32)  /* policy in upper 32 bits, mid in lower */

/*
 * TRUE if a parameter is a policy structure.
 * Depends on all policy struct addresses being kernel VAs -- i.e.,  <0
 */
#define VM_POLICY_POLICY(policy)   ((policy) && ((long)(policy) < 0))

/*
 * Macros to construct "shorthand" policy codes
 */
#define VM_POLICY_PREF(mid) \
  (vm_policy_t)(((long)VM_PAGE_PREF << VM_POLICY_CODE_SHIFT) | (mid))
#define VM_POLICY_DIRECT(mid) \
  (vm_policy_t)(((long)VM_PAGE_DIRECT << VM_POLICY_CODE_SHIFT) | (mid))

/*
 * Extract policy from structure, if non-null, else return default
 */
#define VM_POLICY_POL(VP)						\
	((VP) ? (VP)->vp_policy : VM_PAGE_LOCAL)	

/*
 * Extract policy from structure or code, if non-null, else default
 */
#define VM_POLICY_TYPE(policy) \
  (VM_POLICY_CODE(policy) ? (vm_pol_t)((long)policy >> VM_POLICY_CODE_SHIFT) : \
  VM_POLICY_POL(policy))

/*
 * Extract MID [assign to I] from policy P
 *
 * Note that, for striped policy, the stripe index is calculated relative
 * to the start of the policy range by the following macro:
 */
#define _VM_POLICY_STRIPE_INDEX(P) \
   ((atop((P)->vp_offset - (P)->vp_start)/(P)->vp_stride)%(P)->vp_nstripes)

#define VM_POLICY_MID(I, P)						\
MACRO_BEGIN								\
	if (VM_POLICY_CODE(P))						\
		I = (int)(P); /* low order doubleword of code */	\
	else if (P) {							\
		if ((P)->vp_policy == VM_PAGE_LOCAL)			\
			I = CURRENT_MID();				\
		else if ((P)->vp_policy <= VM_PAGE_DIRECT)		\
			I = (P)->vp_mid;				\
		else if ((P)->vp_policy == VM_PAGE_STRIPED) {		\
			I = _VM_POLICY_STRIPE_INDEX(P);			\
			I = (P)->vp_smap[I];				\
		} else {						\
			printf("%s:%d: bad policy in %P\n",		\
					__FILE__, __LINE__, P);		\
			panic("VM_POLICY_MID");				\
		}							\
	} else								\
		I = CURRENT_MID();					\
MACRO_END

/*
 * Retrieve MID, stripe index and radset from policy
 */
#define VM_POLICY_GET_ATTR(P, I, SI, RS)				\
MACRO_BEGIN								\
	SI = -1;							\
	RS = 0;								\
	if (VM_POLICY_CODE(P))	 					\
		I = (int)(P);						\
	else if (P) {							\
		if ((P)->vp_policy == VM_PAGE_LOCAL)			\
			I = CURRENT_MID();				\
		else if ((P)->vp_policy <= VM_PAGE_DIRECT)		\
			I = (P)->vp_mid;				\
		else if ((P)->vp_policy == VM_PAGE_STRIPED) {		\
			SI = _VM_POLICY_STRIPE_INDEX(P);		\
			I = (P)->vp_smap[SI];				\
		} else {						\
			printf("%s:%d: bad policy in %P\n",		\
					__FILE__, __LINE__, P);		\
			panic("VM_POLICY_MID");				\
		}							\
		/* not applicable to STRIPED policy */			\
		RS = (P)->vp_radset;					\
	} else								\
		I = CURRENT_MID();					\
	if (!RS) 							\
		RS = CURRENT_MAD()->md_radset;				\
MACRO_END

#define	VM_MAD_NULL	(vm_mad_t)0		/* use default policy */

#define PA_TO_VP(PA, VP)					\
MACRO_BEGIN							\
	vm_page_array_t	vpa;					\
	int i, mgd_i, mid = PA_TO_MID(PA);			\
	pmr_t *mrp = pmr_data.pmr_rad_table[mid].pmr_table;	\
	for(i=0, mgd_i=0; i < pmr_data.pmr_rad_table[mid].pmr_count; i++) {	\
		if((PA >= mrp->pmr_base) &&			\
		   (PA < mrp->pmr_base + mrp->pmr_size)) {	\
			break;					\
		}						\
                if(mrp->pmr_type == PMR_MANAGED)                \
	 		mgd_i++;				\
		mrp++;						\
	}							\
	if(mrp->pmr_type == PMR_SHARED) {             		\
          extern gsm_mad_t gsm_mad_array;                       \
                                                                \
          if( (gsm_mad_array) &&                                \
              (vpa = gsm_mad_array[GSM_PA_TO_CPU(mrp->pmr_base)].gsm_vpa) ) \
            VP = &vpa->va_vmp[atop((PA) - vpa->va_start)];      \
          else                                                  \
            VP = 0;                                             \
	} else {                                       		\
	  vpa = &rad_id_to_rad(mid)->rad_mad->md_vpa[mgd_i];    \
	  VP = &vpa->va_vmp[atop((PA) - vpa->va_start)];	\
        }                                                       \
MACRO_END

#define	PAGE_TO_MID(PP)	((PP)->pg_mid)

/*
 * Returns the memory domain associated with the vm page.
 */
#define	PAGE_TO_MAD(PP)	rad_id_to_rad(PAGE_TO_MID(PP))->rad_mad

#define	MID_TO_MAD(MID)	(rad_id_to_rad(MID)? rad_id_to_rad(MID)->rad_mad: 0)
#define	MID_TO_VC(MID)	(&rad_id_to_rad(MID)->rad_mad->md_vm)
#define	MID_TO_UC(MID)	(&rad_id_to_rad(MID)->rad_mad->md_ubc)
#define	MID_TO_MC(MID)	(&rad_id_to_rad(MID)->rad_mad->md_malloc)
#define	MID_TO_SC(MID)	(&rad_id_to_rad(MID)->rad_mad->md_swap)

/*
 * Returns the control structure pointers associated with the vm page.
 *
 * [Note: access to global vm_mads[] could further be refined to avoid
 *  remote access, if necessary]
 */
#define	PAGE_TO_VC(PP)	(&rad_id_to_rad(PAGE_TO_MID(PP))->rad_mad->md_vm)
#define	PAGE_TO_UC(PP)	(&rad_id_to_rad(PAGE_TO_MID(PP))->rad_mad->md_ubc)
#define	PAGE_TO_MC(PP)	(&rad_id_to_rad(PAGE_TO_MID(PP))->rad_mad->md_malloc)

#if defined(VM_MAD_BUCKETS)

#define MID_TO_BUCKET(MID,OBJ,OFF) \
	(&MID_TO_MAD(MID)->vm_page_buckets[vm_page_hash(MID,OBJ,OFF)])
#define PAGE_TO_BUCKET(PP,OBJ,OFF) \
	(&PAGE_TO_MAD(PP)->vm_page_buckets[vm_page_hash(PAGE_TO_MID(PP),OBJ,OFF)])

#else	/* ! VM_MAD_BUCKETS */

#define MID_TO_BUCKET(MID,OBJ,OFF) \
	(&vm_page_buckets[vm_page_hash(OBJ,OFF)])
#define PAGE_TO_BUCKET(PP,OBJ,OFF) \
	(&vm_page_buckets[vm_page_hash(OBJ,OFF)])

#endif	/* VM_MAD_BUCKETS */


#define	MC_TO_VC(MC)	\
	(&((vm_mad_t)((long)MC - (long)&((vm_mad_t)0)->md_malloc))->md_vm)
#define	SC_TO_VC(SC)	\
	(&((vm_mad_t)((long)SC - (long)&((vm_mad_t)0)->md_swap))->md_vm)
#define	SC_TO_MAD(SC)	\
	((vm_mad_t)((long)SC - (long)&((vm_mad_t)0)->md_swap))
#define	VC_TO_SC(VC)	\
	(&((vm_mad_t)((long)VC - (long)&((vm_mad_t)0)->md_vm))->md_swap)
#define	VC_TO_UC(VC)	\
	(&((vm_mad_t)((long)VC - (long)&((vm_mad_t)0)->md_vm))->md_ubc)
#define	VC_TO_MAD(VC)	\
	((vm_mad_t)((long)VC - (long)&((vm_mad_t)0)->md_vm))
#define	UC_TO_MAD(UC)	\
	((vm_mad_t)((long)UC - (long)&((vm_mad_t)0)->md_ubc))

#define	CURRENT_MID()	(AT_INTR_LVL() ?  u.processor->processor_mad->md_mid \
						    : u.u_rad->rad_id)

#define	CURRENT_MAD()	(AT_INTR_LVL() ?  u.processor->processor_mad 	   \
						    : u.u_rad->rad_mad)

/*
 * Returns the control structure pointers associated with the current domain
 */
#define	CURRENT_VC()	(&CURRENT_MAD()->md_vm)
#define	CURRENT_UC()	(&CURRENT_MAD()->md_ubc)
#define	CURRENT_MC()	(&CURRENT_MAD()->md_malloc)
#define	CURRENT_SC()	(&CURRENT_MAD()->md_swap)

#define	VC_FREE_LOCK(VC, S)			\
MACRO_BEGIN					\
	S = splhigh();				\
	simple_lock(&(VC)->vm_free_lock);	\
MACRO_END

#define	VC_FREE_UNLOCK(VC, S)			\
MACRO_BEGIN					\
	simple_unlock(&(VC)->vm_free_lock);	\
	splx(S);				\
MACRO_END

/*
 * Prototypes
 */
struct vm_object;
struct vm_map;
struct vm_map_entry;
enum memalloc_policy;
struct memalloc_attr;

extern void vm_mad_init(int);
extern void vmpol_insert(struct vm_object *, vm_policy_t, vm_policy_t *);
extern void vm_page_oohq_init(int);
extern int mattr_copyin(void *, struct memalloc_attr *);
extern enum memalloc_policy vmpol_to_mapol(vm_pol_t);
extern vm_pol_t mapol_to_vmpol(struct memalloc_attr *);
extern vm_policy_t vmpol_find(struct vm_object *, vm_offset_t, vm_policy_t);
extern kern_return_t vmpolicy_add(struct vm_map_entry *, vm_offset_t,
                      vm_offset_t, struct memalloc_attr *, int, void **);
extern void vmpolicy_cleanup(void *);
extern kern_return_t vmpolicy_smap_create(vm_policy_t);
extern boolean_t __vmpolicy_equiv_sets(vm_policy_t, vm_policy_t);
extern void vmpol_free(vm_policy_t);
extern void vm_mad_page_init(vm_mad_t);

#endif	/* _BASE_KERNEL_PRIVATE */
#endif	/* _KERNEL */

#endif	/* _VM_VM_NUMA_H_ */
