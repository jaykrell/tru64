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
 * @(#)$RCSfile: vm_perf.h,v $ $Revision: 1.1.26.4 $ (DEC) $Date: 1999/12/15 20:10:14 $
 */
#ifndef	_VM_VM_PERF_H_
#define	_VM_VM_PERF_H_ 1

#ifdef	_KERNEL

typedef	unsigned long vpf_t;

/*
 * per-cpu statistics
 */
typedef struct vm_perf {
	int   vp_cpu;			/* cpu id */
	int   vp_ticks;			/* accumulated ticks */
	vpf_t vp_v_faults;		/* VM All page faults */
	vpf_t vp_v_kfaults;		/* VM Kernel page faults */
	vpf_t vp_v_cowcopy;		/* VM Optimized COW faults */
	vpf_t vp_v_kzfod;		/* VM Kernel zero filled on demand */
	vpf_t vp_v_pagesteal;		/* VM page steals */
	vpf_t vp_v_prewrites;		/* VM pre-writes */
	vpf_t vp_v_anon_prewrites;	/* VM "" anon */
	vpf_t vp_v_swap_prewrites;	/* VM "" anon */
	vpf_t vp_v_cleanrecs;		/* VM clean reclaims */
	vpf_t vp_v_swaprecs;		/* VM Swap write reclaims */
	vpf_t vp_v_lmsteal;		/* VM Low Mem. steal */
	vpf_t vp_v_lmstealwins;		/* VM Low Mem. steal wins */
	vpf_t vp_v_ffl;			/* VM faults from free list */
	vpf_t vp_v_pout_scan;		/* VM vm_pageout_scan calls */
	vpf_t vp_v_pout_pagescan;	/* VM pages scanned */
	vpf_t vp_v_pout_call;		/* VM pageout calls */
	vpf_t vp_v_pout;		/* VM successful pageouts */
	vpf_t vp_v_pout_target;		/* VM vm target met */
	vpf_t vp_v_pout_burst;		/* VM vm I/O met */
	vpf_t vp_v_act_scans;		/* VM active pages examined */
	vpf_t vp_v_act_moves;		/* VM active pages deactivated */
	vpf_t vp_v_lock_fails;		/* VM failed oop lock tries */
	vpf_t vp_v_migrations;		/* VM page migrations */

	vpf_t vp_u_allocscans;		/* UBC page alloc LRU scans */
	vpf_t vp_u_alloceol;		/* UBC "" end-of-LRU reached */
	vpf_t vp_u_allocpush;		/* UBC "" pushed page */
	vpf_t vp_u_allocstole;		/* UBC "" stole page */
	vpf_t vp_u_allocseq;		/* UBC "" seq drain attempts */
	vpf_t vp_u_wacalls;		/* UBC write ahead calls */
	vpf_t vp_u_wascans;		/* UBC "" scans */
	vpf_t vp_u_waeol;		/* UBC "" end-of-LRU */
	vpf_t vp_u_prges;		/* UBC ubc_mem_purges */
	vpf_t vp_u_prgscans;		/* UBC "" LRU scans */
	vpf_t vp_u_prgeol;		/* UBC "" end-of-LRU */
	vpf_t vp_u_prgburst;		/* UBC "" I/O target met */
	vpf_t vp_u_prgfree;		/* UBC "" pages freed */
	vpf_t vp_u_mmapfree;	 	/* UBC mmaped page freed */
	vpf_t vp_u_wdeny;		/* UBC FS denied writes */
	vpf_t vp_u_hardsteals;		/* UBC hardsteals */
	vpf_t vp_u_stealscans;		/* UBC pagesteal scans */
	vpf_t vp_u_dirtywra;		/* UBC dirty write aheads */
	vpf_t vp_u_reclaim;		/* UBC page reclaims */
	vpf_t vp_u_pagesteal;		/* UBC page steals */
	vpf_t vp_u_lookups;		/* UBC lookup tries */
	vpf_t vp_u_lookuphits;		/* UBC lookup hits */
	vpf_t vp_u_ffl;			/* UBC fault from free list */
	vpf_t vp_u_lmsteal;		/* UBC low mem steal */
	vpf_t vp_u_lmstealwins;		/* UBC low mem steal wins */
	vpf_t vp_u_seqdrain;		/* UBC sequential drains */

	/*
	 * events in last second
	 */
	vpf_t vp_lv_cowfaults;		/* VM Cow part of all faults */
	vpf_t vp_lv_zfod;		/* VM User zero filled on demand */
	vpf_t vp_lv_iowrites;		/* VM I/O writes */
	vpf_t vp_lv_pgwrites;		/* VM Page writes */
	vpf_t vp_lv_ioreads;		/* VM I/O reads */
	vpf_t vp_lv_pgreads;		/* VM Page reads */
	vpf_t vp_lv_reactivate;		/* VM Pageout system reactivate */
	vpf_t vp_lu_reactivate;		/* UBC referenced LRU page */
	vpf_t vp_lu_alloc;		/* UBC memory demand of ubc */
	vpf_t vp_lu_iowrites;		/* UBC I/O issued */
	vpf_t vp_lu_pgwrites;		/* UBC pages written */

	/*
	 * computed 5 second average
	 */
	vpf_t vp_cv_cowfaults;		/* VM Cow part of all faults */
	vpf_t vp_cv_zfod;		/* VM User zero filled on demand */
	vpf_t vp_cv_iowrites;		/* VM I/O writes */
	vpf_t vp_cv_pgwrites;		/* VM Page writes */
	vpf_t vp_cv_ioreads;		/* VM I/O reads */
	vpf_t vp_cv_pgreads;		/* VM Page reads */
	vpf_t vp_cv_reactivate;		/* VM Pageout system reactivate */
	vpf_t vp_cu_reactivate;		/* UBC referenced LRU page */
	vpf_t vp_cu_alloc;		/* UBC memory demand of ubc */
	vpf_t vp_cu_iowrites;		/* UBC I/O issued */
	vpf_t vp_cu_pgwrites;		/* UBC pages written */

	/*
	 * totals
	 */
	vpf_t vp_tv_cowfaults;		/* VM Cow part of all faults */
	vpf_t vp_tv_zfod;		/* VM User zero filled on demand */
	vpf_t vp_tv_iowrites;		/* VM I/O writes */
	vpf_t vp_tv_pgwrites;		/* VM Page writes */
	vpf_t vp_tv_ioreads;		/* VM I/O reads */
	vpf_t vp_tv_pgreads;		/* VM Page reads */
	vpf_t vp_tv_reactivate;		/* VM Pageout system reactivate */
	vpf_t vp_tu_reactivate;		/* UBC referenced LRU page */
	vpf_t vp_tu_alloc;		/* UBC memory demand of ubc */
	vpf_t vp_tu_iowrites;		/* UBC I/O issued */
	vpf_t vp_tu_pgwrites;		/* UBC pages written */
} *vm_perf_t;

#define	VM_PERF(P)		((vm_perf_t)processor_ptr[P]->vm_perf)
#define CURRENT_VM_PERF()	((vm_perf_t)current_processor()->vm_perf)

#define	VPF_V_INC(F)		CURRENT_VM_PERF()->vp_v_##F++
#define	VPF_U_INC(F)		CURRENT_VM_PERF()->vp_u_##F++
#define	VPF_LV_INC(F)		CURRENT_VM_PERF()->vp_lv_##F++
#define	VPF_LU_INC(F)		CURRENT_VM_PERF()->vp_lu_##F++
#define	VPF_LV_ADD(F, C)	CURRENT_VM_PERF()->vp_lv_##F+= C
#define	VPF_LU_ADD(F, C)	CURRENT_VM_PERF()->vp_lu_##F+= C
#define	VPF_CV(P, F)		(processor_ptr[P]? VM_PERF(P)->vp_cv_##F: 0)
#define	VPF_CU(P, F)		(processor_ptr[P]? VM_PERF(P)->vp_cu_##F: 0)

#endif	/* _KERNEL */
#endif	/* !_VM_VM_PERF_H_ */
