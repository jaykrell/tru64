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
 * @(#)$RCSfile: pfm.h,v $ $Revision: 1.1.6.6 $ (DEC) $Date: 2000/03/24 22:35:28 $
 */
#ifndef _PFM_H_
#define _PFM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <sys/pfcntr.h>

/*
 * Current state of the PFM driver on each CPU.
 *
 * If opened in mode PCNTOPENONE, each pfmstate[cpu#] is independent.
 *
 * If opened in mode PCNTOPENEACH , the fields marked "PERCPU" below
 * are collected separately for each CPU, in pfmstate[cpu#].
 * All other fields are GLOBAL, can use any pfmstate if needed.
 *
 * If opened in mode PCNTOPENALL, there are two cases:
 *    If NUMA, behave like PCNTOPENEACH, each CPU independently
 *    counts and reads pfm_samples; other counters
 *    (pfm_counters, pfm_ipl) are aggregated into pfmstate[0].
 *    If not NUMA, use pfmstate[0] to aggregate everything.
 */
struct pfmstate {
	/* NOTE: pfm_counter and pfm_cycles make a struct pfcntr */
	ulong	pfm_cycles;		/* proc cycle counter	PERCPU */
	ulong	pfm_counter[3];		/* counters		PERCPU */
	ulong	pfm_old_cycles;		/* last PCC value	PERCPU */
	ulong	pfm_iccsr;		/* last state we set	*/
	addr_range_t pfm_addrs;		/* profile address range */
	uint	*pfm_samples;		/* PC samples		PERCPU */
	ulong	pfm_buffsize;		/* size of this pfm_samples */
	ulong	pfm_ipl[9];		/* ipl histogram	PERCPU */
	int	pfm_state;		/* state flag		*/
	int	pfm_disabled;		/* 0, 1, 2, or 3 (ev5 goes to 7) */
	ulong	pfm_pad[2];		/* round up to multiple of 64 */
};

#ifdef _KERNEL

/*
 * The mode the PFM driver is opened in.
 * One of: 0, PCNTOPENALL, or PCNTOPENEACH
 * If 0, each CPU is opening PCNTOPENONE mode
 */
extern int pfm_open_mode;
extern int pfm_profme_mode;

extern struct pfmstate *pfmstate;

extern struct addr_range *pfm_use_ra_p;	/* Base of array of address_ranges */
extern int pfm_n_use_ra;		/* Number in use at the moment */

extern long wrperfmon(ulong, ulong);

extern void pfmintr(ulong, ulong, ulong, ulong, ulong *);
extern void pfmhalt(void);
extern void (*get_pfmintr_func(void))();
extern void set_pfmintr_func(void (*)());

#endif /* _KERNEL */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _PFM_H_ */
