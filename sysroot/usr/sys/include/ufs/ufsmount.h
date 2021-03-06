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
 *	@(#)$RCSfile: ufsmount.h,v $ $Revision: 4.2.14.2 $ (DEC) $Date: 1999/07/08 14:29:34 $
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
/*
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
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

#include <sys/types.h>
#include <ufs/quota.h>

#ifndef _UFS_UFSMOUNT_
#define	_UFS_UFSMOUNT_

#ifdef	_KERNEL
#include <kern/lock.h>
#endif

/*
 * Mount structure.
 * One allocated on every mount.
 * Used to find the super block.
 */
struct	ufsmount {
	struct	mount *um_mountp;	/* vfs structure for this filesystem */
	dev_t	um_dev;			/* device mounted */
	struct	vnode *um_devvp;	/* vnode for block device mounted */
	struct	vnode *um_rootvp;	/* vnode for root of filesystem */
	struct	fs *um_fs;		/* pointer to superblock */
	struct	vnode *um_quotas[MAXQUOTAS]; /* pointer to quota files */
	struct	ucred *um_cred[MAXQUOTAS]; /* cred for access to quota file */
	time_t	um_btime[MAXQUOTAS];	/* block quota time limit */
	time_t	um_itime[MAXQUOTAS];	/* inode quota time limit */
	char	um_qflags[MAXQUOTAS];	/* quota specific flags, see below */
	char	um_qsync;		/* qsync in progress */
#ifdef	_KERNEL
	decl_simple_lock_data(,um_qsync_lock) /* protect um_qsync */
	lock_data_t	um_lock;	/* quota read/write lock */
	u_long	um_max_clusterio;	/* max cluster io size this um_dev */
#endif
	int	um_full_time;		/* last time fs full msg logged */
};

#define LOG_FULL_MSG(ump)					\
(								\
  ((ump->um_full_time == 0) ||					\
   (time.tv_sec - ump->um_full_time >= fs_full_threshold))	\
	? (ump->um_full_time = time.tv_sec) : 0			\
)

#define	QTF_OPENING	0x01		/* Q_QUOTAON in progress */
#define QTF_CLOSING	0x02		/* Q_QUOTAOFF in progress */

#ifdef	_KERNEL
/*
 * Convert mount ptr to ufsmount ptr.
 */
#define VFSTOUFS(mp)	((struct ufsmount *)((mp)->m_info))
#define MAX_UFSMOUNTS   1000

#if	QUOTA
/*
 * Quota locking strategy.
 *
 * Ufsmount quota lock.  Dquot lock.  Dqhead hash chain locks.
 * Dqfree lock.  IQUOTA, IQUOTING, IQUOTWAIT.			XXX
 */

extern struct lockinfo *umpq_lockinfo;
#define	UMPQ_READ_LOCK(ump)	lock_read(&(ump)->um_lock)
#define	UMPQ_READ_UNLOCK(ump)	lock_read_done(&(ump)->um_lock)
#define	UMPQ_WRITE_LOCK(ump)	lock_write(&(ump)->um_lock)
#define	UMPQ_WRITE_UNLOCK(ump)	lock_write_done(&(ump)->um_lock)
#define	UMPQ_LOCK_RECURSIVE(ump) lock_set_recursive(&(ump)->um_lock)
#define	UMPQ_LOCK_UNRECURSIVE(ump) lock_clear_recursive(&(ump)->um_lock)
#define	UMPQ_LOCK_INIT(ump)	lock_setup(&(ump)->um_lock, umpq_lockinfo,TRUE)

#define	UMPQ_WRITE_HOLDER(ump)	LOCK_HOLDER(&(ump)->um_lock)
#define	UMPQ_READ_HOLDER(ump)	LOCK_READERS(&(ump)->um_lock)

decl_simple_lock_info(extern, ump_qsync_lockinfo)
#define	UMPQ_SYNC_LOCK(ump)	simple_lock(&(ump)->um_qsync_lock)
#define	UMPQ_SYNC_UNLOCK(ump)	simple_unlock(&(ump)->um_qsync_lock)
#define	UMPQ_SYNC_LOCK_INIT(ump) simple_lock_setup(&(ump)->um_qsync_lock,\
						   ump_qsync_lockinfo)

#endif	/* QUOTA */
/*
 * mount table
 */
extern struct ufsmount	*mounttab;

/*
 * Exported by UFS
 */
struct vnode *ufs_getrootvp(struct mount *);

/*
 * Unix mount table lock operations.  The only operation
 * on the mounttab requiring synchronization is allocation
 * of entries in the table for mount structures.  Thus, the
 * lock only needs to be held for a brief period of time.
 */
udecl_simple_lock_data(extern, mounttab_lock);
udecl_simple_lock_info(extern, mounttab_lockinfo);

#define MOUNTTAB_LOCK()		usimple_lock(&mounttab_lock);
#define MOUNTTAB_UNLOCK()	usimple_unlock(&mounttab_lock);
#define MOUNTTAB_LOCK_INIT()	usimple_lock_setup(&mounttab_lock,\
					           mounttab_lockinfo);
#endif

#endif /* _UFS_UFSMOUNT_ */
