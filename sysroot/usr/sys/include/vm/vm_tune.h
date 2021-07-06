/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: vm_tune.h,v $
 * Revision 1.1.55.4  2004/06/01  18:22:03  Jason_Hennessey
 * 	Add "ubc_wakeup_waiters" tunable (QAR 97470)
 *
 * Revision 1.1.55.3  2003/10/09  22:07:22  Jeffrey_Cilley
 * Merge Information:  Visual Merge: User specified default merge the submit tree v51bsupportos
 *     User Revision:  Jeffrey_Cilley_newubc_br:1.1.56.1 Local Ancestor:1.1.48.5
 *    Merge Revision:  v51bsupportos_br:1.1.55.2
 *   Common Ancestor:  1.1.48.5
 * 	[2003/10/09  22:03:21  Jeffrey_Cilley]
 *
 * 	Add new ubc tunables.
 * 	[2003/10/03  20:39:08  Jeffrey_Cilley]
 *
 * Revision 1.1.55.2  2003/06/19  13:26:47  Matthew_McGrath
 * 	Add tuneable vm_bigpg_factor.
 * 
 * Revision 1.1.55.1  2003/04/29  15:09:41  Ross_Knepper
 * 	Add tuneable ubc_overflow to support overflowing
 * 	to remote MADs.  Change default value of vm_ubcseqstartpercent
 * 	from 50 to 80.
 * 
 * Revision 1.1.48.5  2002/07/16  19:47:15  Renny_Shen
 * 	Added usage comments for gsm_enabled tunable
 * 
 * Revision 1.1.48.4  2002/07/10  21:39:59  Ross_Knepper
 * 	Add new sysconfig variable ubc_strict_rw_ordering.
 * 
 * Revision 1.1.48.3  2002/04/24  13:20:33  David_Bernardo
 * 	Add reserve_address_space.
 * 
 * Revision 1.1.48.2  2002/03/26  00:41:22  Renny_Shen
 * 	Added tunable to enable GSM
 * 
 * Revision 1.1.48.1  2001/10/03  17:44:50  David_Bernardo
 * 	Added tunables for bigpages project.
 * 
 * Revision 1.1.42.3  2001/04/10  20:24:05  Peter_Keilty
 * 	QAR-85016 S AIM7 REGRESSED
 * 	Changed UBCDIRTYPERCENT to 40, now that there is a dirty lru
 * 	finding dirty pages is very deterministic. The old 10 percent
 * 	value is to low, causing excess IO.
 * 	Changed UBCPGTOSCANCNT to 2000, increase the page scan count.
 * 
 * Revision 1.1.42.2  2000/12/07  21:54:28  Peter_Keilty
 * 	PMK: Acxiom IPMT-BCGMA0M0S, QAR-83215
 * 	Add new UBC tunables and define defaults.
 * 	vt_ubc_dirty_metadata_pcnt - Max. % of dirty metadata ubcpages
 * 	before pushing.
 * 	vt_ubc_pgfree_cnt - LRU page free count.
 * 	vt_ubc_pgtoscan_cnt - LRU page scan count.
 * 	vt_ubc_trylock_cnt -	Try lock count.
 * 	vt_ubc_kluster_cnt -	Page klustering count.
 * 	vt_ubc_objstartpercent - Start trim object percent.
 * 
 * Revision 1.1.42.1  2000/10/19  19:19:04  Julie_Dewandel
 * 	Added color_bucket_count hidden tunable to allow
 * 	control over number of buckets used for page coloring.
 * 
 * Revision 1.1.33.9  2000/04/20  21:58:35  Frederick_Canter
 * 	Add vm_troll_interval hidden tunable so memory troller
 * 	can be reconfigured and restarted after a fatal error.
 * 
 * Revision 1.1.33.8  2000/03/16  23:03:28  Shashi_Mangalat
 * 	Move VM_STACK_FREE_TARGET here from vm_numa.h.
 * 
 * Revision 1.1.33.7  2000/03/16  16:32:22  Frederick_Canter
 * 	Modify vm_tune data structure for memory troller support.
 * 
 * Revision 1.1.33.6  2000/01/28  21:16:45  Ross_Knepper
 * 	Add tuneable parameter stack_free_target
 * 	[2000/01/27  22:49:17  Ross_Knepper]
 * 
 * Revision 1.1.33.4  1999/12/29  22:49:58  Dean_Gagne
 * 	Merge of ZincOS.BL3 -> to ZuluOS.BL8
 * 	Define vt_ubc_deactivate_ticks in vm_tune.
 * 
 * Revision 1.1.33.3  1999/05/06  19:35:27  Shashi_Mangalat
 * 	Merge of STEELOS_BL21:STEELOS_BL23
 * 	 Revision 1.1.25.8  1999/03/26  19:55:47  Stephen_Corbin
 * 	 New UBC tunable - per file dirty page limits
 * 	 Revision 1.1.25.7  1999/03/25  23:03:15  Shashi_Mangalat
 * 	 Merge of PTFCOS_BL5:PTFCOS_BL6: add vm_private_color.
 * 	 Revision 1.1.25.6  1999/02/15  14:42:20  Shashi_Mangalat
 * 	 Add switch to enable/disable yellow zone on default stack.
 * 	[1999/05/06  19:30:03  Shashi_Mangalat]
 * 
 * Revision 1.1.33.2  1999/03/11  01:57:57  Shashi_Mangalat
 * 	Fix merge problems.
 * 	[1999/03/11  01:51:07  Shashi_Mangalat]
 * 
 * Revision 1.1.25.5  1998/11/25  23:35:28  Shashi_Mangalat
 * 	VM/NUMA scalability enhancements.
 * 	[1998/11/16  23:19:38  Shashi_Mangalat]
 * 
 * Revision 1.1.25.4  1997/09/22  20:49:55  Jeff_Denham
 * 	Push max mapentries up for better thread support and large
 * 	default max virtual address space.
 * 	[1997/09/18  20:46:47  Jeff_Denham]
 * 
 * Revision 1.1.25.3  1997/03/15  14:16:26  Shashi_Mangalat
 * 	Remove the following unused fields:
 * 	vt_maxvas, vt_maxwire, vt_heappercent, vt_anonklshift,
 * 	vt_anonklpages, vt_zone_size, vt_kentry_zone_size.
 * 	[1997/03/13  20:43:50  Shashi_Mangalat]
 * 
 * Revision 1.1.25.2  1996/05/01  18:04:20  Larry_Woodman
 * 	Merge from bravos.bl2
 * 	[1996/05/01  17:39:26  Larry_Woodman]
 * 
 * Revision 1.1.23.2  1995/10/31  23:06:52  Ray_Lanza
 * 	Changed macro concatenation to ansi style for gnuc
 * 	[1995/10/31  17:59:53  Ray_Lanza]
 * 
 * Revision 1.1.20.3  1995/03/15  22:26:07  Ashoke_Rampuria
 * 	Set back mapentries limit to 200.
 * 	[1995/03/15  21:37:17  Ashoke_Rampuria]
 * 
 * Revision 1.1.20.2  1995/03/13  21:33:23  Ashoke_Rampuria
 * 	Temporarily increase mapentries limit to 1024.
 * 	[1995/03/13  21:28:50  Ashoke_Rampuria]
 * 
 * Revision 1.1.18.4  1994/02/02  23:23:22  Ernie_Petrides
 * 	Change default zone map size to enable scaling with available memory.
 * 	[1994/02/02  22:24:43  Ernie_Petrides]
 * 
 * Revision 1.1.18.3  1993/10/07  15:49:34  Shashi_Mangalat
 * 	Merge of Sterling BL6 changes.
 * 	 Reduce the minimum outswapped time to 1 tick.
 * 	 [1993/08/19  18:26:55  Larry_Woodman]
 * 	 STERLING perofrmance work.
 * 	 [1993/08/06  19:48:58  Larry_Woodman]
 * 	 Make segmentation configurable.
 * 	 [1993/04/22  11:32:46  Anna_Salzberg]
 * 	 Disable pagein clustering for performance improvement.
 * 	 [93/02/15  14:06:21  Anna_Salzberg]
 * 	[1993/10/07  15:15:37  Shashi_Mangalat]
 * 
 * Revision 1.1.18.2  1993/09/03  20:59:16  Anton_Verhulst
 * 	Changed shorts and chars to ints so that /osf_param could handle
 * 	them more easily.
 * 	[1993/09/01  16:11:18  Anton_Verhulst]
 * 
 * Revision 1.1.3.10  92/10/13  15:06:01  Joe_Martin
 * 	AG_BL10_6 merge
 * 	Revision 1.1.2.8  92/09/25  15:27:42  Marian_Macartney
 * 	Increase VPAGEMAX to 16K
 * 	[92/09/25  15:26:56  Marian_Macartney]
 * 	Revision 1.1.2.7  92/09/16  14:06:11  Marian_Macartney
 * 	Added vm_tune parameter SYSWIREDPERCENT
 * 	[92/09/16  14:05:04  Marian_Macartney]
 * 
 * Revision 1.1.3.9  92/10/08  13:07:38  Robert_McGuirk
 * 	Increase the default values for zone_size and kentry_zone_size.
 * 	[92/10/08  13:06:15  Robert_McGuirk]
 * 
 * Revision 1.1.3.8  92/08/14  14:35:58  Ernie_Petrides
 * 	Increase default VPAGEMAX value to cover 128M of address space.
 * 	[92/08/10  16:51:36  Ernie_Petrides]
 * 
 * Revision 1.1.3.7  92/08/04  12:28:12  Joe_Martin
 * 	merged in Silver BL9_1
 * 	Revision 1.1.4.2  92/07/14  10:07:45  Ashoke_Rampuria
 * 
 * Revision 1.1.2.6  92/07/14  10:17:45  Ashoke_Rampuria
 * 	Added zone_size and kentry_zone_size to vm_tune.
 * 	[92/07/13  14:21:08  Ashoke_Rampuria]
 * 
 * Revision 1.1.3.6  92/07/08  16:39:26  Joe_Martin
 * 	merged in Silver BL8_2
 * 	Revision 1.1.2.5  92/06/15  15:23:38  Marian_Macartney
 * 	Increase MAXVAS default value
 * 	[92/06/15  15:17:31  Marian_Macartney]
 * 
 * Revision 1.1.3.5  92/06/03  12:49:21  Joe_Martin
 * 	merged in Silver BL7
 * 	Revision 1.1.2.4  92/05/21  13:27:07  Marian_Macartney
 * 	Make vm_tune parameters configurable
 * 	[92/05/21  12:51:19  Marian_Macartney]
 * 
 * Revision 1.1.3.3  92/04/14  14:01:06  Joe_Martin
 * 	AG_BL6 merge
 * 	Revision 1.1.2.3  92/03/26  11:46:00  Robert_Picco
 * 	bug fix
 * 	[92/03/24  10:09:07  Robert_Picco]
 * 	Revision 1.1.2.2  92/02/26  15:56:34  Charles_Briggs
 * 	[92/04/14  13:53:40  Joe_Martin]
 * 
 * Revision 1.1.3.2  92/03/19  08:55:36  Al_Delorey
 * 	From Silver: AG_BL5
 * 	[92/03/18  18:33:34  Al_Delorey]
 * 	UBC merge.
 * 	[92/02/22  14:53:22  Charles_Briggs]
 * 
 * Revision 1.1.1.2  92/03/17  17:10:47  devbld_gsf
 * 	First AG_BL5 version.  Moved from Ag baselevel delivery tree.
 * 
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: vm_tune.h,v $ $Revision: 1.1.55.4 $ (DEC) $Date: 2004/06/01 18:22:03 $
 */
#ifndef	__VM_TUNE__
#define	__VM_TUNE__

struct vm_tune {
	unsigned int	vt_vm_cowfaults;	/* Copy point */
	unsigned int	vt_vm_segmentation;	/* Segmentation on or off */ 
	unsigned int	vt_vm_seg_cache_max;	/* max segments to cache */
	unsigned int	vt_vm_ffl;		/* fault off free list */
	unsigned int	vt_vm_syncswapbuffers;	/* synchronous swap buffers */
	unsigned int	vt_vm_asyncswapbuffers;	/* asynchronous swap buffers */
	unsigned long 	vt_vm_csubmapsize;	/* Size of kernel copy map */
	unsigned long	vt_vm_clustermap;	/* ckluster dup map size */
	unsigned long	vt_vm_clustersize;	/* max cluster bp size */
	unsigned int	vt_vm_syswiredpercent;	/* max pct of wired memory
						 * (system-wide) */
	unsigned int	vt_vm_troll_percent;	/* memory troller control */
	unsigned int	vt_vm_troll_error_wait;	/* machine check wait time */
	unsigned int	vt_vm_troll_pfntick;	/* max pages trolled per tick */
	unsigned int	vt_vm_troll_interval;	/* troller on/off switch */
	unsigned long	vt_vm_swap_rcluster;	/* read cluster size */
	unsigned long	vt_vm_swap_wcluster;	/* write cluster size */
	unsigned int	vt_vm_swap_eager;	/* eager swap on or off */ 
	unsigned int	vt_vm_free_reserved;
	unsigned int	vt_vm_free_min;
	unsigned int	vt_vm_free_target;
	unsigned int	vt_vm_free_optimal;
	unsigned int	vt_vm_prewrite_target;
	unsigned int	vt_vm_free_swap;
	unsigned int	vt_vm_free_hardswap;
	unsigned int	vt_vm_page_lock_count;
	unsigned int	vt_vm_private_cache_percent;
	unsigned int	vt_vm_private_text;
	unsigned int	vt_vm_replicate_text;	/* replicate user text */
	unsigned int	vt_vm_private_color;
	unsigned int	vt_vm_color_bucket_count;
	unsigned int	vt_vm_enable_yzone;	/* enable stack yellow zone */
	unsigned int	vt_vm_stack_free_target;
	unsigned int    vt_vm_bigpg_enabled;	/* big switch for big pages */
	unsigned int	vt_vm_bigpg_anon;	/* enable big pgs for ANON */
	unsigned int	vt_vm_bigpg_seg;	/* enable big pgs for SEG */
	unsigned int	vt_vm_bigpg_shm;	/* enable big pgs for SHM */
	unsigned int	vt_vm_bigpg_ssm;	/* enable big pgs for SSM */
	unsigned int	vt_vm_bigpg_stack;	/* enable big pgs for STACK */
	unsigned int	vt_vm_bigpg_thresh;	/* MB of memory per list;
						   0 = system decides */
	unsigned int	vt_ubc_pagesteal;	/* Steal vnode clean list */
	unsigned int	vt_ubc_dirtypercent;	/* Min. dirty for write ahead */
	unsigned int	vt_ubc_dirty_wra;	/* Maximum write ahead I/Os */
	unsigned int	vt_ubc_dirty_seconds;	/* How often to flush */
	unsigned int	vt_ubc_dirty_metadata_pcnt;/* Max. % of dirty metadata*/
						/* ubcpages before pushing */
	unsigned int	vt_ubc_pgfree_cnt;	/* LRU page free count */
	unsigned int	vt_ubc_pgtoscan_cnt;	/* LRU page scan count */
	unsigned int	vt_ubc_trylock_cnt;	/* Try lock count */
	unsigned int	vt_ubc_kluster_cnt;	/* Page klustering count */
	unsigned int	vt_ubc_objstartpercent;	/* Start trim object percent */
	unsigned int	vt_ubc_seqstartpercent;	/* Start ubcseqpercent */
	unsigned int	vt_ubc_seqpercent;	/* Sequential allocation */
	unsigned int	vt_ubc_buffers;		/* UBC I/O buffers */
	unsigned int	vt_ubc_minpercent;	/* Minimum UBC */
	unsigned int	vt_ubc_maxpercent;	/* Maximum UBC */
	unsigned int	vt_ubc_borrowpercent;	/* VM may borrow above this */
	unsigned int	vt_ubc_ffl;		/* fault off free list */
	unsigned int	vt_ubc_filemaxdirtypages; /* max dirty pages per file */
	unsigned int	vt_ubc_deactivate_ticks;/* how long will we hold */
						/* ubc_lru_lock. */
	unsigned int	vt_ubc_strict_rw_ordering; /* whether to wait for */
						/* read-after-write busy */
	unsigned int	vt_swap_inswappedmin;	/* minimum inswapped ticks */
	unsigned int	vt_swap_aggressive;	/* aggressive task swapping */
	unsigned int	vt_rss_enforce;		/* RSS enforce */
	unsigned int	vt_rss_block_target;	/* RSS block target */
	unsigned int	vt_rss_wakeup_target;	/* RSS wakeup target */
	unsigned int	vt_vm_boost_pager_priority; /* boost pageout thread prioirty */
	unsigned int    vt_vm_gsm_enabled;      /* Enable global shared mem */
                                                /* 0 - always disabled      */
                                                /* 1 - platform can enable  */
                                                /* 2 - always enabled       */
	unsigned int	vt_vm_reserve_address_space; /* Enable reserve space checking */
        unsigned int    vt_ubc_overflow;        /* Overflow to other RADs? */
        unsigned int    vt_vm_bigpg_factor;     /* bigpage alloc. factor */
        unsigned int    vt_vm_l3gh_anon;        /* enable l3gh for ANON */
        unsigned int    vt_vm_l3gh_shm;         /* enable l3gh for SHM */
        unsigned int    vt_vm_l3gh_ssm;         /* enable l3gh for SSM */
	unsigned int	vt_ubc_prewrite_mult;   /* affects how early we start
						 * stealing clean pages from
						 * our own object. */
	unsigned int	vt_ubc_approx_low_pcnt; /* low watermark for ubc
						 * approximation code. */
	unsigned int    vt_ubc_approx_high_pcnt;/* high watermark for ubc
						 * approximation code. */
	unsigned int	vt_ubc_pgscan_drop_lock_cnt;	/* determines how
						* often lock is dropped
						* while scanning lru. */
	unsigned int	vt_ubc_scan_pglock_cnt;	/* how many pages can be
						 * locked while scanning
						 * lru. */
	unsigned int	vt_ubc_wake_waiters;	/* # of seconds max to
						 * wait in ubc_page_alloc()
						 */
};

#define	vm_tune_compare(VALUE,FIELD,ROP) ((VALUE) ROP vm_tune.vt_##FIELD)
#define	vm_tune_value(FIELD)	vm_tune._##FIELD

#define	VM_TUNE(FIELD)		vm_tune.vt_vm_##FIELD
#define	UBC_TUNE(FIELD)		vm_tune.vt_ubc_##FIELD
#define	SWAP_TUNE(FIELD)	vm_tune.vt_swap_##FIELD
#define	RSS_TUNE(FIELD)		vm_tune.vt_rss_##FIELD

extern struct vm_tune vm_tune;

/*
 * Define system defaults.  These can be overridden in <machine/vmparam.h>
 */

#ifndef COWFAULTS
#define COWFAULTS		(4)		/*Copy point */
#endif

#ifndef MAPENTRIES
#define MAPENTRIES		(32*1024)   	/*Maximum map entries */
#endif

#ifndef MAXVAS
#define MAXVAS 			(1L<<32)	/*Maximum VAS for user maps */
#endif

#ifndef VPAGEMAX
#define VPAGEMAX		(16*1024)	/*Maximum vpage for umap*/
#endif

#ifndef SEGMENTATION 
#define SEGMENTATION		(1)	/*Segmentation on or off*/
#endif

#ifndef SEGCACHEMAX 
#define SEGCACHEMAX		(50)	/*Max segments to cache*/
#endif

#ifndef CSUBMAPSIZE
#define CSUBMAPSIZE		(1024*1024)	/*Size of kernel copy map*/
#endif

#ifndef SYNCSWAPBUFFERS
#define SYNCSWAPBUFFERS		(128)	/*synchronous swap buffers*/
#endif

#ifndef ASYNCSWAPBUFFERS
#define ASYNCSWAPBUFFERS	(4)   /* asynchronous swap buffers*/
#endif

#ifndef CLUSTERMAP
#define CLUSTERMAP		(1024*1024*1) /*Cluster dup map size*/
#endif

#ifndef CLUSTERSIZE
#define CLUSTERSIZE		(1024*64)	/*Max cluster dup per bp */
#endif

#ifndef SYSWIREDPERCENT
#define SYSWIREDPERCENT		(80) /*max pct of wired memory system-wide*/
#endif

#ifndef	READIO_CLUSTER
#define	READIO_CLUSTER		(16*1024) /* read cluster size */
#endif

#ifndef	WRITEIO_CLUSTER
#define	WRITEIO_CLUSTER		(32*1024) /* write cluster size */
#endif

#ifndef	VM_FREE_RESERVED
#define	VM_FREE_RESERVED	10
#endif

#ifndef	VM_FREE_MIN
#define	VM_FREE_MIN		(VM_FREE_RESERVED*2)
#endif

#ifndef	VM_FREE_TARGET
#define	VM_FREE_TARGET		128
#endif

#ifndef	VM_FREE_OPTIMAL
#define	VM_FREE_OPTIMAL		(VM_FREE_MIN + (VM_FREE_TARGET - VM_FREE_MIN)/2)
#endif

#ifndef	VM_PREWRITE_TARGET
#define	VM_PREWRITE_TARGET	(VM_FREE_TARGET*2)
#endif

#ifndef	VM_FREE_SWAP
#define	VM_FREE_SWAP		VM_FREE_OPTIMAL
#endif

#ifndef	VM_FREE_HARDSWAP
#define	VM_FREE_HARDSWAP	(VM_FREE_TARGET*16)
#endif

#ifndef	VM_PAGE_LOCK_COUNT
#define	VM_PAGE_LOCK_COUNT	64
#endif

#ifndef	VM_PRIVATE_TEXT
#define	VM_PRIVATE_TEXT		0
#endif

#ifndef	VM_PRIVATE_CACHE_PCNT
#define	VM_PRIVATE_CACHE_PCNT	0
#endif

#ifndef	VM_PAGEOUT_BURST
#define	VM_PAGEOUT_BURST	(20)
#endif

#ifndef	VM_INACTIVE_TGT_LO
#define	VM_INACTIVE_TGT_LO(C)	(((C) * 1) / 3)
#endif

#ifndef VM_INACTIVE_TGT_HI
#define VM_INACTIVE_TGT_HI(C)	(((C) * 2) / 3)
#endif

#ifndef	VM_SCAN_RATE
#define	VM_SCAN_RATE		200
#endif

#ifndef	VM_SCHED_TICKS
#define	VM_SCHED_TICKS		4		/* 250 milliseconds */
#endif

#ifndef	VM_STACK_FREE_TARGET
#define VM_STACK_FREE_TARGET	5
#endif

#ifndef UBCPAGESTEAL
#define UBCPAGESTEAL		(24)	/*Steal vnode clean list*/
#endif

#ifndef UBCDIRTYPERCENT
#define UBCDIRTYPERCENT		(40)	/*Percent dirty push value*/
#endif

#ifndef UBCMAXDIRTYWRITES
#define UBCMAXDIRTYWRITES	(5)	/*Max dirty writes*/
#endif

#ifndef UBCBORROWPERCENT
#define UBCBORROWPERCENT	(20)	/*ubc borrow limit*/
#endif

#ifndef UBCDIRTYSECONDS
#define UBCDIRTYSECONDS		(1)	/*How often to flush*/
#endif

#ifndef UBCDIRTYMETADATAPCNT
#define UBCDIRTYMETADATAPCNT	(70)	/*Max dirty metadata percent */
#endif

#ifndef UBCPAGEFREECNT
#define UBCPAGEFREECNT		(5)	/*Max LRU pages tofree ubc_page_alloc */
#endif

#ifndef UBCPGTOSCANCNT
#define UBCPGTOSCANCNT		(2000)	/*Max pages toscan ubc_page_alloc */
#endif

#ifndef UBCTRYLOCKCNT
#define UBCTRYLOCKCNT		(10)	/*Max try lock count */
#endif

#ifndef UBCKLUSTERCNT
#define UBCKLUSTERCNT		(32)	/*Max kluster count*/
#endif

#ifndef UBCOBJSTARTPERCENT
#define UBCOBJSTARTPERCENT	(10)	/*Start trim obj percent */
#endif

#ifndef UBCSEQSTARTPERCENT
#define UBCSEQSTARTPERCENT	(80)	/*Start ubcseqpercent */
#endif

#ifndef UBCSEQPERCENT
#define UBCSEQPERCENT		(10)	/*Sequential allocation*/
#endif

#ifndef UBCBUFFERS
#define UBCBUFFERS		(256)	/*ubc buffers*/
#endif

#ifndef UBCMINPERCENT
#define UBCMINPERCENT		(10)	/*Minimum UBC */
#endif

#ifndef UBCMAXPERCENT
#define UBCMAXPERCENT		(100)	/*Maximum UBC*/
#endif

#ifndef UBCFILEMAXDIRTYPAGES
#define UBCFILEMAXDIRTYPAGES	(-1)	/* max UBC pages dirty per file */
#endif

#ifndef INSWAPPEDMIN
#define INSWAPPEDMIN		(1)	/* minimum inswapped ticks */
#endif

#ifndef UBCPREWRITEMULT
#define UBCPREWRITEMULT         (2)     /* prewrite multiplier in 
                                         * ubc_rem_excess */
#endif

#ifndef UBC_APPROX_LOW_PCNT     
#define UBC_APPROX_LOW_PCNT     (60)    /* low watermark percent in 
                                         * ubc approximation */
#endif

#ifndef UBC_APPROX_HIGH_PCNT
#define UBC_APPROX_HIGH_PCNT    (10)    /* high watermark percent in
                                         * ubc approximation */
#endif

#ifndef UBC_PGSCAN_DROP_LOCK_CNT
#define UBC_PGSCAN_DROP_LOCK_CNT	(10) /* Number of pages to queue
					      * before dropping lock. */
#endif

#ifndef UBC_SCAN_PGLOCK_CNT	
#define UBC_SCAN_PGLOCK_CNT	(3)  	/* max # of pages locked while
					 * scanning. */
#endif

#ifndef UBC_SCAN_PGLOCK_MAX		/* upper bound of 	*/
#define UBC_SCAN_PGLOCK_MAX	(5)	/* UBC_SCAN_PGLOCK_CNT	*/

#endif

#endif	/* !__VM_TUNE__ */

