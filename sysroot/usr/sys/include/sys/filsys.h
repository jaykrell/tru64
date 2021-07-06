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
 *	@(#)$RCSfile: filsys.h,v $ $Revision: 4.2.8.2 $ (DEC) $Date: 1999/08/16 20:09:39 $
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
 *	filsys.h	4.3	81/03/03	
 */
/*
 * Structure of the super-block
 */

#ifndef	_SYS_FILSYS_H_
#define _SYS_FILSYS_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#define BSIZE	(1024)		/* 1024-byte block file system */
#ifndef NICFREE
#define NICFREE	178		/* 1024-byte block file system */
#endif
#define NICINOD	100		/* 1024-byte block file system */
#define SUPERB	((daddr_t)1)	/* block number of the super block */

struct	filsys
{
	unsigned short s_isize;		/* size in blocks of i-list */
	daddr_t	s_fsize;   		/* size in blocks of entire volume */
	short	s_nfree;   		/* number of addresses in s_free */
	daddr_t	s_free[NICFREE];	/* free block list */
	short	s_ninode;  		/* number of i-nodes in s_inode */
	ushort_t s_inode[NICINOD];	/* free i-node list */
	char   	s_flock;   		/* lock during free list manipulation */
	char   	s_ilock;   		/* lock during i-list manipulation */
	char   	s_xfmod;    		/* (was) super block modified flag */
	char   	s_xronly;   		/* (was) mounted read-only flag */
	time_t 	s_time;    		/* last super block update */
	daddr_t	s_tfree;   		/* total free blocks*/
	ushort_t s_tinode;  		/* total free inodes */
	short	s_dinfo[2];		/* interleave stuff */
#define s_m	s_dinfo[0]
#define s_n	s_dinfo[1]
	char   	s_fsmnt[12];		/* ordinary file mounted on */
	/* end not maintained */
	ushort_t s_lasti;		/* start place for circular search */
        ushort_t s_nbehind;		/* est # free inodes before s_lasti */
};

struct fblk
{
	int    	df_nfree;
	daddr_t	df_free[NICFREE];
};

typedef	struct fblk *FBLKP;

#ifdef __cplusplus
}
#endif
#endif	/* _SYS_FILSYS_H_ */
