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
 *	@(#)$RCSfile: dk.h,v $ $Revision: 4.3.15.4 $ (DEC) $Date: 1999/01/13 18:35:20 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 */

#ifndef	_SYS_DK_H_
#define _SYS_DK_H_

/* dk.h
 *
 * Modification History
 *
 * 20-Nov-91	Tom Tierney
 *	Modified DK_NDRIVE to support up to 256 disk units.
 *
 */ 
 
/*
 * Instrumentation
 */

/* need to match defines in mach/machine.h CPU_STATE_* */
#define CPUSTATES	5
#define CP_USER		0
#define CP_NICE		1
#define CP_SYS		2
#define CP_IDLE		3
#define CP_WAIT		4

#ifdef	KERNEL

/*
 * GET_NOW_TIME returns current time in usecs.
 * It uses external (struct timeval)time instead of a subroutine call.
 * !NOTE! Actual granularity is >> usec
 */
#define GET_NOW_TIME(t, t_usec)			\
{						\
extern struct timeval time;			\
    TIME_READ (t);				\
    t_usec = t.tv_sec * 1000000L + t.tv_usec;	\
}

#define CAM_INITIAL_STATS(now_usec, ds)					\
	if ((ds != (DISK_SPECIFIC *)NULL) &&				\
	    (ds->ds_flags & DS_ONLINE)) {				\
		ds->ds_stats.di_initial_busy = now_usec;		\
		ds->ds_stats.di_avque++;				\
	}

#define FD_INITIAL_STATS(now_usec, fd)					\
	if (fd != (struct fd_class *)NULL) {				\
	    struct device *devp = fd->fd_devp;				\
	    struct tbl_dkinfo *stp = (struct tbl_dkinfo *)devp->dstats;	\
									\
	    if (stp != (struct tbl_dkinfo *)NULL) {						\
		stp->di_initial_busy = now_usec;			\
		stp->di_avque++;					\
	    }								\
	}

#define MSCP_INITIAL_STATS(now_usec, devp)				\
	if (devp != (struct device *)NULL) {				\
	    struct tbl_dkinfo *stp = (struct tbl_dkinfo *)devp->dstats;	\
									\
	    if (stp != (struct tbl_dkinfo *)NULL) {			\
		stp->di_initial_busy = now_usec;			\
		stp->di_avque++;					\
	    }								\
	}

#define RE_INITIAL_STATS(now_usec, rpd)					\
	if (rpd != (RE_DEVICE *) NULL) {				\
		rpd->re_stats.di_initial_busy = now_usec;		\
		rpd->re_stats.di_avque++;				\
	}

#define I2O_BS_INITIAL_STATS(now_usec, bs_softc)			\
	if (bs_softc != (I2O_BS_SOFTC *) NULL) {			\
		int	index = (int) bs_softc->dkn_num;		\
									\
		if (index != -1) {					\
			if (dk_ref_cnt[index]++ == 0) {			\
				dk_initial_busy[index] = now_usec;	\
			}						\
									\
			dk_avque[index]++;				\
		}							\
	}

/*
 * This timeline diagram illustrates the meaning of the time-related
 * statistics that are kept for the CAM disk driver.
 * 
 *	S1      S2      S3      C1      C3      C2
 *	|<-----------t1-------->|       |       |
 *	|       |<---------t2------------------>|
 *	|       |       |<------t3----->|       |
 * 
 *	S1 = start I/O #1	C1 = complete I/O #1
 *	S2 = start I/O #2	C2 = complete I/O #2
 *	S3 = start I/O #3	C3 = complete I/O #3
 * 
 *	di_avserv = (t1+t2+t3) = additive time to complete all i/o
 *	di_avque  = current number of outstanding i/o requests
 *	di_xfer   = total number of completed i/o requests
 *	di_wds    = total number of 64-bit longwords transferred
 */
#define CAM_COMPLETE_STATS(bcount, ds)					\
	if ((ds != (DISK_SPECIFIC *)NULL) &&				\
	    (ds->ds_flags & DS_ONLINE)) {				\
		struct tbl_dkinfo *stp = &ds->ds_stats;			\
		struct timeval now;					\
		long now_usec;						\
		long initial_busy;					\
									\
		if (stp->di_avque > 0L) {				\
			GET_NOW_TIME(now, now_usec)			\
									\
			initial_busy = stp->di_initial_busy;		\
			stp->di_avserv += (now_usec - initial_busy);	\
			stp->di_avque--;				\
			stp->di_xfer++;					\
			stp->di_wds += bcount >> 6;			\
		}							\
	}

#define FD_COMPLETE_STATS(devp)						\
   	if (devp != (struct device *)NULL) {				\
	    struct tbl_dkinfo *stp = (struct tbl_dkinfo *)devp->dstats;	\
	    struct timeval now;						\
	    long now_usec;						\
	    long initial_busy;						\
									\
	    if ((stp != NULL) && (stp->di_avque > 0L)) {		\
		GET_NOW_TIME(now, now_usec)				\
									\
		initial_busy= stp->di_initial_busy;			\
		stp->di_avserv += (now_usec - initial_busy);		\
		stp->di_avque--;					\
		stp->di_xfer++;						\
		stp->di_wds += scp->cur_bp->b_bcount >> 6;		\
	    }								\
	}

/*
 * In MSCP, di_xfer and di_wds are set prior to MSCP_INITIAL_STATS
 */
#define MSCP_COMPLETE_STATS(devp)					\
        if (devp != (struct device *) NULL) {				\
	    struct tbl_dkinfo *stp = (struct tbl_dkinfo *)devp->dstats;	\
	    struct timeval now;						\
	    long now_usec;						\
	    long initial_busy;						\
									\
	    if ((stp != NULL) && (stp->di_avque > 0L)) {		\
		GET_NOW_TIME(now, now_usec)				\
									\
		initial_busy = stp->di_initial_busy;			\
		stp->di_avserv += (now_usec - initial_busy);		\
		stp->di_avque--;					\
	    }								\
        }

#define RE_COMPLETE_STATS(bcount, rpd)					\
	if (rpd != (RE_DEVICE *) NULL) {				\
		struct tbl_dkinfo *stp = &rpd->re_stats;		\
		struct timeval now;					\
		long now_usec;						\
		long initial_busy;					\
									\
		if (stp->di_avque > 0L) {				\
			GET_NOW_TIME(now, now_usec)			\
									\
			initial_busy = stp->di_initial_busy;		\
			stp->di_avserv += (now_usec - initial_busy);	\
			stp->di_avque--;				\
			stp->di_xfer++;					\
			stp->di_wds += bcount>>3;			\
		}							\
	}

#define I2O_BS_COMPLETE_STATS(now, now_usec, initial_busy, bs_softc)	\
        if (bs_softc != (I2O_BS_SOFTC *) NULL) {			\
		int	index = (int) bs_softc->dkn_num;		\
									\
		if (index != -1) {					\
			if (dk_ref_cnt[index] > 0L) {			\
				GET_NOW_TIME(now, now_usec)		\
									\
				initial_busy =				\
				dk_initial_busy[index];			\
				dk_time_dev_busy_serv[index]		\
				+=					\
				now_usec - initial_busy;		\
									\
				if (--dk_ref_cnt[index] > 0L) {		\
					dk_initial_busy[index]		\
				=					\
				now_usec;				\
				}					\
									\
				dk_avque[index]--;			\
			}						\
		}							\
        }
/*******SAR STATS******/

extern long	tk_nin;
extern long	tk_nout;
extern int      tk_cancc;
extern int      tk_rawcc;

#endif	/* KERNEL */
#endif	/* _SYS_DK_H_ */
