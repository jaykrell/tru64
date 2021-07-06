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
 * @(#)$RCSfile: sar.h,v $ $Revision: 1.1.6.4 $ (DEC) $Date: 1997/11/06 12:26:11 $
 */

#ifndef _SVR4_SAR_H_
#define _SVR4_SAR_H_

struct sar_data {
	/* for sar -c support, and other system stuff */
	long ts_devintr;
	long ts_passrel;
	long ts_syscalls;
	long ts_sysread;
	long ts_syswrite;
	long ts_sysexec;
	long ts_sysfork;
	long ts_sysvfork;
	long ts_readch;
	long ts_writech;
	long ts_tasksw;
	long ts_threadsw;
	long ts_xcpusched;

	/* for sar -a support */
	long tf_iget;
	long tf_namei;
	long tf_dirblk;

	/* for sar -b support */
	long ts_bread;
	long ts_bwrite;
	long ts_lread;
	long ts_lwrite;
	long ts_phread;
	long ts_phwrite;

	/* for sar -k support */
	long sar_kmem_fail;

	/* for sar -v support */
	long tbl_proc_ov;
	long tbl_inod_ov;
	long tbl_file_ov;

	long pg_v_pgpgin;
	long pg_v_sftlock;
	long pg_v_pgout;
	long pg_v_dfree;
	long pg_v_scan;
	long pg_v_s5ifp;
};


#ifdef	_KERNEL

#include <rt_preempt.h>
#include <machine/cpu.h>


/*
 * sar_update: adds val to the sarcntr entry for this cpu.
 * If toggle_preempt is true, preemption is disabled for the updates.
 * Values for toggle_preempt are known at compile time, so the tests
 * are removed.
 */
#define sar_update(sarcntr, val, toggle_preempt)			\
MACRO_BEGIN								\
	if (toggle_preempt) {						\
		preemption_off();					\
		current_sar()->sarcntr += (val);			\
		preemption_on();					\
	} else {							\
		current_sar()->sarcntr += (val);			\
	}								\
MACRO_END

/* for sar -q support */
extern long sar_runocc, sar_runqueue;

#endif /* _KERNEL */
#endif /* _SVR4_SAR_H_ */
