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
 *	@(#)$RCSfile: namei.h,v $ $Revision: 4.2.89.1 $ (DEC) $Date: 2002/02/01 00:35:32 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * Copyright (C) 1988,1989 Encore Computer Corporation.  All Rights Reserved
 *
 * Property of Encore Computer Corporation.
 * This software is made available solely pursuant to the terms of
 * a software license agreement which governs its use. Unauthorized
 * duplication, distribution or sale are strictly prohibited.
 *
 */
/*
 * Copyright (c) 1985, 1989 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef	_SYS_NAMEI_H_
#define _SYS_NAMEI_H_

#include <sys/types.h>
#include <sys/uio.h>
#include <ufs/dir.h>
#include <s5fs/s5dir.h>
#ifdef	_KERNEL
#include <sys/unix_defs.h>
#endif

/*
 * Encapsulation of namei parameters.
 * One of these is located in the u. area to
 * minimize space allocated on the kernel stack.
 */

/*
 * There is often a delay between creating an in-core inode representing
 * an object and actually filling in all of the relevant information.
 * For example, a symbolic link is created by creating an inode and then
 * writing the link name into a disk block or (multimax) into the inode
 * itself.  These operations are separate for non-UNIX_LOCKS implementations
 * but under UNIX_LOCKS the relevant initial data is passed down to the routine
 * creating the inode, so that the new inode becomes visible to the world
 * in an atomic fashion.
 */

/* forward declarations as required for C++ */
#ifdef __cplusplus
struct vnode;
struct ucred;
#endif

struct nameidata {
		/* arguments to namei and related context: */
	caddr_t	ni_dirp;		/* pathname pointer */
	enum	uio_seg ni_segflg;	/* location of pathname */
	int	ni_nameiop;		/* see below */
#if	MACH
	struct	utask_nd *ni_utnd;	/* utask nameidata structure */
#define ni_cdir	ni_utnd->utnd_cdir
#define ni_rdir	ni_utnd->utnd_rdir
#else
	struct	vnode *ni_cdir;		/* current directory */
	struct	vnode *ni_rdir;		/* root directory, if not normal root */
#endif
	struct	ucred *ni_cred;		/* credentials */

		/* shared between namei, lookup routines and commit routines: */
	caddr_t	ni_pnbuf;		/* pathname buffer */
	char	*ni_ptr;		/* current location in pathname */
	char	*ni_next;		/* next location in pathname */
	u_int	ni_pathlen;		/* remaining chars in path */
	int	ni_nchtimestamp;	/* for name cache enters */
	u_long	ni_hash;		/* hash value of current component */
	short	ni_namelen;		/* length of current component */
	short	ni_loopcnt;		/* count of symlinks encountered */
	char	ni_makeentry;		/* 1 => add entry to name cache */
	char	ni_isdotdot;		/* 1 => current component name is .. */

		/* results: */
	struct	vnode *ni_vp;		/* vnode of result */
	struct	vnode *ni_dvp;		/* vnode of intermediate directory */
	union {
		struct	ufs_od_dirent ni_ufsdirent; /* ufs final component name */
		struct	gpdirect ni_gpfsdent; /* general purpose final name */
		struct  dirent ni_gendirent; /* final component name */
	} ni_dir;

		/* side effects: */
	/* BEGIN UFS SPECIFIC */
	off_t	ni_endoff;		/* end of useful directory contents */
	struct ndirinfo {		/* saved info for new dir entry */
		struct	iovec nd_iovec;		/* pointed to by ni_iov */
		struct	uio nd_uio;		/* directory I/O parameters */
	} ni_nd;
	/* END UFS SPECIFIC */

	long	ni_dirstamp;		/* for directories */
	u_long	ni_vpid;		/* capability of result's vnode */
	int     (*ni_lookup)(struct vnode *, struct nameidata *);         /* special dce dfs lookup function */
	long    ni_xid;                 /* CFS transaction id for exactly-once */
};

#define	ni_iovec	ni_nd.nd_iovec
#define	ni_base		ni_nd.nd_iovec.iov_base
#define ni_hint         ni_nd.nd_iovec.iov_base
#define	ni_count	ni_nd.nd_iovec.iov_len
#define	ni_uioseg	ni_nd.nd_uio.uio_segflg
#define	ni_iov		ni_nd.nd_uio.uio_iov
#define	ni_iovcnt	ni_nd.nd_uio.uio_iovcnt
#define	ni_offset	ni_nd.nd_uio.uio_offset
#define	ni_resid	ni_nd.nd_uio.uio_resid
#define	ni_rw		ni_nd.nd_uio.uio_rw
#define	ni_uio		ni_nd.nd_uio
#define ni_dent		ni_dir.ni_gendirent
#define ni_gpdent	ni_dir.ni_gpfsdent
#define ni_ufsdent	ni_dir.ni_ufsdirent

#ifdef	_KERNEL
/*
 * namei operations and modifiers
 */
#define LOOKUP		0x0000	/* perform name lookup only */
#define CREATE		0x0001	/* setup for file creation */
#define DELETE		0x0002	/* setup for file deletion */
#define	RENAME		0x0003	/* setup for file renaming */
#define	OPFLAG		0x0003	/* mask for operation */
#define	WANTPARENT	0x0010	/* want parent vnode returned unlocked */
#define NOCACHE		0x0020	/* name must not be left in cache */
#define FOLLOW		0x0040	/* follow symbolic links */
#define NOFOLLOW	0x0000	/* don't follow symbolic links (pseudo) */
#define	NOCROSSMOUNT	0x0080	/* do not cross mount points */
#define	REMOTE		0x0100	/* lookup for remote filesystem servers */
#define	HASBUF		0x0200	/* has preallocated pathname buffer */
#define	STRIPSLASH	0x0400	/* has preallocated pathname buffer */
#define	SKIPACCESS	0x0800	/* don't do access (VEXEC) on current vp */
#define VTAGLOOKUP  0x2000  /* version tag lookup */
#if	SEC_MAC
#define	MLDCREATE	0x4000	/* creating mld subdirectory */
#endif
#define SPECLOOKUP      0x8000  /* special dce dfs lookup function */
#define BADDIRSTAMP	0x10000	/* ni_dirstamp is invalid */

/*
 * Namei hints used for CFS performance.
 * These are ORed into ni_nameiop.
 */
#define LOOKUP_STAT	0x00020000	/* lookup for stat (getattr coming) */
#define LOOKUP_ORD	0x00040000	/* open for read is coming */
#define LOOKUP_OWR	0x00080000	/* open for write is coming */
#define LOOKUP_OCREAT	0x00100000	/* VOP_CREATE is coming */
#define FSHIPPED	0x00200000	/* operation has been func shipped */
#define LOOKUP_CLMNT	0x00400000	/* cluster mount is coming */
#define FILE_OPEN	0x00800000	/* active references to this file
					 * exist (ie, file is open from one or
					 * more cluster members)
					 */
#define	LOOKUP_MOUNT	0x01000000	/* lookup for mount/unmount */
#define	LOOKUP_SYMLINK	0x02000000	/* lookup for symlink create */

#define LOOKUP_AUDMOD	0x04000000	/* lookup is for an auditable
					 *modification op to the parent dir
					 *such as unlink, rename, etc. */  
#endif	/* _KERNEL */

/*
 * This structure describes the elements in the cache of recent
 * names looked up by namei.
 */

#define	NCHNAMLEN	31	/* maximum name segment length we bother with */
#define	NCHSIZE		15	/* fixed namecache size for each nchash chain */
#define GNNCHSIZE	13	/* fixed negative namecache size for each
				   gnnchash chain */
#define	NCH_NULL	((struct nchash *) 0)

struct	namecache {
	u_long	nc_vpid;		/* capability number of nc_vp */
	struct	vnode *nc_vp;		/* vnode the name refers to */
	u_long  nc_time;		/* last cache activity time */
	u_long	nc_dvpid;		/* capability number of nc_dvp */

	char	nc_nlen;		/* length of name */
	char	nc_name[NCHNAMLEN];	/* segment name */
	/* 64 byte alignment */
};

#ifdef	_KERNEL

/* A portion of hash value that was calculated in namei() and parent vnode
 * generation no. is saved in nchentry to speed up searching for a match in
 * cache_enter() and cache_lookup() by avoid D-cache miss of actual
 * namecache entry: For example, in the best case, we only need nchash[]
 * (1 cache block) if no match exist; when a match exist, then we need
 * 1 cache block of nchash[] and a namecache entry (1 cache block) at best */

struct nchentry {	/* 4 byte long */
	char	index;	/* index into namecache entry, 
			   0..(nchsize-1) is valid */	/* Bit 0 to 7 */
	char	dvpid;	/* defined in DVPIDMASK */	/* bit 8 to 15 */
	u_short	nchash;	/* defined in HASHMASK */	/* bit 16 to 31 */
};

/* Namei cache hash chain header */
struct nchash {			/* Per processor namei cache */
	short	emptyslot;	/* 0..(NCHSIZE-1) is valid: if NCHSIZE, no
				   empty slot avail.; recycle using recycleslot */
	short	recycleslot;	/* 0..(NCHSIZE/2) is valid
				   indicate next entry to be recycled */

	struct nchentry	nch_entry[NCHSIZE];
	/* This is a heap of height of 4 (complete binary tree)
	 * The root of the heap has the MRU entry and its children has 
	 * less or equal nc_time */

	/* 64 byte alignment */
};

/* Global negative namei cache hash chain header */
/* Using the same nchentry and namecache structure */
struct gnnchash {
	udecl_simple_lock_data(, gnnch_lock)
	short	emptyslot;	/* 0..(GNNCHSIZE-1) is valid. If GNNCHSIZE,
				   no empty slot is available; recycle using
				   recycleslot */
	short	recycleslot;	/* 0..(GNNCHSZE/2) is valid. indicates next
				   entry to be recycled */

	struct 	nchentry gnnch_entry[GNNCHSIZE];
	/* This is a heap of height of 4 (incomplete binary tree) */

	/* 64 byte alignment */
};

#define MINNCHSZ 64
extern REPLICATED int	nchsize;
extern REPLICATED int	nchsz;
extern u_long		nextvnodeid;
#endif

/*
 * Stats on usefulness of namei caches (one per cpu).
 */
struct	nchstats {
	u_long	ncs_goodhits;		/* Good hit, positive */
	u_long	ncs_neghits;		/* Good hit, negative */
	u_long	ncs_badhits;		/* Bad hit, must drop (RENAME/DELETE)*/
	u_long	ncs_falsehits;		/* Bad hit, v_id mismatch */
	u_long	ncs_miss;		/* Miss, no entry found in cache */
	u_long	ncs_long;		/* Miss, name too long for cache */
	u_long	ncs_badtimehits;	/* Bad hit, nache_valid_time expiry */
	u_long	ncs_collisions;		/* Collisions inserting new entries */
	u_long	ncs_unequaldups;	/* On insert, found invalid entry */
	u_long	ncs_newentry;		/* new entry with no dup */
	u_long	ncs_newnegentry;	/* negative entry inserted */
	u_long	ncs_gnn_hit;		/* negative hit in gnnchash list */
	u_long	ncs_gnn_miss;		/* bogus local negative hit */
	u_long	ncs_gnn_badhits;	/* remove gnnchash entry */
	u_long	ncs_gnn_collision;	/* duplicate gnn entry */
	u_long	ncs_pad[1];		/* Future expansion. */
};

/*
 * Flags to checkdir when proposing to add a name
 * or remove a name from a directory.
 */
#define ADD	0x1
#define DEL	0x2
#define RNM	0x4

/*
 *	cdsl {memb} member specific definitions
 */

#define MEMB_VAR "{memb}"	/* member specific cdsl variable   */
#define MEMBER_VAL "member"	/* member specific cdsl value      */
				/* gets appended with the memberid */
#define MEMBER_VAR_LEN 7	/* length of the "{memb}" string */
#define MEMBER_VAL_LEN 10	/* maximum length of the member# string */

/*
 *      cdsl {implver} member specific definitions
 */

#define IMPLVER_VAR "{implver}"    /* member specific cdsl variable   */
#define IMPLVER_EV6 "ev6"          /* ev6 variant */
#define IMPLVER_GENERIC "generic"  /* generic variant */

#define IMPLVER_VAR_LEN 10        /* length of the "{implver}" string */
#define IMPLVER_VAL_LEN 9         /* maximum length of replacement string */


#endif	/* _SYS_NAMEI_H_ */

