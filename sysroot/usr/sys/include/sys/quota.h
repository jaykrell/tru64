/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: quota.h,v $
 * Revision 4.2.10.1  2005/01/18  22:55:58  Charles_Katz
 * 	Add QUOTA_ID_MAX defined as "UID_MAX + 1" to be used
 * 	as a loop terminator to quota programs to include the
 * 	id for "nfs user nobody" but not anything beyond that.
 * 	(CLD QXCM1000198076)
 *
 * Revision 4.2.8.1  2000/10/12  17:14:11  Mike_Milicia
 * 	CFS quota support : Feature tag : y4.cfs.003.quota
 * 	Add new "_*_INT" quota functions used by CFS.
 *
 * Revision 4.2.5.3  1997/10/09  21:53:10  Richard_Morris
 * 	Pad struct dQBlk64 to 64 bytes to avoid having quotas that span pages.
 * 	QAR 55789.
 * 	[1997/10/09  21:40:14  Richard_Morris]
 *
 * Revision 4.2.5.2  1997/08/19  15:30:54  Richard_Morris
 * 	New include file with support for 8 byte quotas.
 * 	[1997/08/14  15:36:40  Richard_Morris]
 * 
 * Revision 4.2  1991/09/19  22:59:32  devbld
 * 	Adding ODE Headers
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: quota.h,v $ $Revision: 4.2.10.1 $ (DEC) $Date: 2005/01/18 22:55:58 $
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

#ifndef	_QUOTA_H_
#define	_QUOTA_H_

#include <ufs/quota.h>

/*
 * Used for parameters to cluster quota callouts.
 */
#define	SOFTQUOTA	0	
#define	HARDQUOTA	1	

/*
 * The following structures define the format of the disk quota file
 * (as it appears on disk) - the file is an array of these structures
 * indexed by user or group number.  The dQBlk32 structure is used by
 * the GETQUOTA, SETQUOTA, and SETUSE quotactl commands.  The dQBlk64
 * structure is used by the GETQUOTA64, SETQUOTA64, and SETUSE64 
 * quotactl commands.  For more info see the quotactl man page.
 */
struct  dQBlk32 {
        u_int   dqb_bhardlimit; /* absolute limit on disk blks alloc */
        u_int   dqb_bsoftlimit; /* preferred limit on disk blks */
        u_int   dqb_curblocks;  /* current block count */
        u_int   dqb_ihardlimit; /* maximum # allocated inodes + 1 */
        u_int   dqb_isoftlimit; /* preferred inode limit */
        u_int   dqb_curinodes;  /* current # allocated inodes */
        time_t  dqb_btime;      /* time limit for excessive disk use */
        time_t  dqb_itime;      /* time limit for excessive files */
};

/*  
 * This structure is padded to 64 bytes.  The size of this structure
 * should be a power of 2 so that an even number of these structures
 * will fit in a page.  Otherwise, the code to manage any of these
 * structures that cross page boundaries will be inefficient.
 */
struct  dQBlk64 {
        u_long  dqb_bhardlimit; /* absolute limit on disk blks alloc */
        u_long  dqb_bsoftlimit; /* preferred limit on disk blks */
        u_long  dqb_curblocks;  /* current block count */
        u_int   dqb_ihardlimit; /* maximum # allocated inodes + 1 */
        u_int   dqb_isoftlimit; /* preferred inode limit */
        u_int   dqb_curinodes;  /* current # allocated inodes */
        u_int   dqb_unused1;    /* pad structure */
        time_t  dqb_btime;      /* time limit for excessive disk use */
        u_int   dqb_unused2;    /* pad structure */
        time_t  dqb_itime;      /* time limit for excessive files */
        u_int   dqb_unused3;    /* pad structure */
        u_long  dqb_unused4;    /* pad structure to 64 bytes */
};

#define Q_QUOTAINFO             0x0700    /* get quota info */
#define Q_GETQUOTA64            0x0800    /* get 8 byte limits and usage */
#define Q_SETQUOTA64            0x0900    /* set 8 byte limits and usage */
#define Q_SETUSE64              0x0A00    /* set 8 byte usage */

#ifdef _KERNEL
/* Internal kernel functions used by CFS in a cluster */
#define Q_DQGETQUOTA64          0x0B00    /* Only used by cfs_dqget() */
#define Q_INT         		0x8000    /* Marks kernel-only functions */

#define Q_QUOTAINFO_INT		(Q_QUOTAINFO    | Q_INT) /* get quota info */
#define Q_GETQUOTA64_INT	(Q_GETQUOTA64   | Q_INT) /* get 8 byte limits/usage */
#define Q_DQGETQUOTA64_INT      (Q_DQGETQUOTA64 | Q_INT) /* Only used by cfs_dqget() */
#define Q_SETQUOTA64_INT	(Q_SETQUOTA64   | Q_INT) /* set 8 byte limits/usage */
#define Q_SETUSE64_INT		(Q_SETUSE64     | Q_INT) /* set 8 byte usage */

#endif

#define QUOTA32                 4         /* indicates 4 bytes quotas */
#define QUOTA64                 8         /* indicates 8 bytes quotas */
#define QUOTA32_MAX             0x0ffffffffL

#define QSTS_QUOTA_ON           0x0001    /* some quota type is active */
#define QSTS_USR_QUOTA_MT       0x0004    /* maintaining user quotas */
#define QSTS_GRP_QUOTA_MT       0x0008    /* maintaining group quotas */
#define QSTS_USR_QUOTA_EN       0x0010    /* enforcing user quotas */
#define QSTS_GRP_QUOTA_EN       0x0020    /* enforcing group quotas */
#define QSTS_LARGE_LIMITS       0x0400    /* set for 8 byte quota fields */
/* 
 * Add QUOTA_ID_MAX defined as "UID_MAX + 1" to be used as a loop
 * terminator to allow quota programs to include the id for 
 * "nfs user nobody" but not UINT_MAX (note UID_MAX + 1 is equivalent
 * to UINT_MAX - 1).
 * UINT_MAX is 0xffffffff which equals 4294967295 (2^32 - 1, equivalent to -1),
 * this isn't a legitimate uid. The highest uid is "user nobody"
 * 0xfffffffe (UINT_MAX - 1, UID_MAX + 1) which equals 4294967294 (2^32 - 2, 
 * equivalent to -2).
 * For historical reasons, UID_MAX is defined as UINT_MAX - 2. If quota 
 * programs stop after UID_MAX they won't include "user nobody". But they
 * must also stop immediately after that one because otherwise larger numbers
 * will have mistakened meaning (note that numbers larger than 2^32 will be
 * truncated when they enter the kernel). This definition is not placed
 * in sys/limits.h because of strict POSIX conventions.
 */

#define QUOTA_ID_MAX		(UID_MAX + 1) /* nfs' user nobody */
#endif	/* _QUOTA_H_ */
