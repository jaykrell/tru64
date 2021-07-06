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
 *	@(#)$RCSfile: cdfsmount.h,v $ $Revision: 4.3.15.6 $ (DEC) $Date: 1999/02/02 18:20:05 $
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
#include <sys/mount.h>

#ifndef _CDFSMOUNT_
#define	_CDFSMOUNT_

/*
 * Mount structure.
 * One allocated on every mount.
 * Used to find the primary volume descriptor.
 */
struct	cdfsmount {
	int	um_flag;		/* Flags for perm/version... */
	struct	mount *um_mountp;	/* vfs structure for this filesystem */
	dev_t	um_dev;			/* device mounted */
	struct	vnode *um_devvp;	/* vnode for block device mounted */
	struct	vnode *um_rootvp;	/* vnode for root of filesystem */
	struct	fs *um_fs;		/* pointer to pvd */
	struct {
		uid_t	default_uid;	/* default uid if no xar */
		gid_t	default_gid;	/* default gid if no xar */
		mode_t	default_fmode;	/* default file mode if no xar */
		mode_t	default_dmode;	/* default dir mode if no xar */
		int	map_uid_ct;	/* map uid array size */
		map_id	*map_uid;	/* map uid array */
		int	map_gid_ct;	/* map gid array size */
		map_id	*map_gid;	/* map gid array */
	} um_args;
#ifdef	_KERNEL
	udecl_simple_lock_data(,um_lock)/* multiprocessor exclusion */
#endif
};

/*
 * Start of ISO file system
 */
#define	ISO_BBSIZE	32768		/* ISO BootBlock Size */
#define ISO_IDSIZE	5		/* Bytes for ISO ID string */
#define ISO_ID		"CD001"		/* ISO ID String */
#define HSG_ID		"CDROM"		/* HSG ID String */

/*
 * low 5 bits are taken by pan-filesystem flags: RDONLY, SYNCHRONOUS,
 * NOEXEC, NOSUID, NODEV.
 */

#define M_NODEFPERM	0x20		/* No default permissions */
#define M_PRIMARY	0x80		/* Use Primary Vol Desc */
#define	M_EXTENDED_ARGS	0x80000		/* Use extended cdfs_args */
    /* M_NOVERSION is backward compat for old mount commands */
#define M_NOVERSION	0x00040		/* No version,lowercase,drop "." ext */
#define	M_LOWERCASE	0x00100		/* convert to lowercase,drop "." ext */
#define M_DROPVERS	0x00200		/* No version numbers */
#define	M_RRIP		0x00400		/* use RRIP */
#define	M_XCDR		0x00800		/* enforce XCDR name matching */
#define M_DIRSEARCH	0x01000		/* allow dirsearch, if read access */
#define M_DEFUID	0x02000		/* default uid, if no xar */
#define M_DEFGID	0x04000		/* default gid, if no xar */
#define M_DEFFMODE	0x08000		/* default file mode, if no xar */
/* XXX aargh, statfs flags is a short, so we only have
   0xffff flags visible to statfs.  these aren't visible in standard flags,
   only in the cdfs_args.flags field: */
#define M_DEFDMODE	0x10000		/* default dir mode, if no xar */
#define M_MAPUID	0x20000		/* map uid array */
#define M_MAPGID	0x40000		/* map gid array */
#define M_NORRIP	0x100000	/* no Rock Ridge */
#define M_JOLIET	0x200000	/* use joliet */
#define M_NOJOLIET	0x400000	/* no joliet */
#define M_ISO9660	0x800000	/* use iso9660 */
#define M_VERBOSE	0x1000000	/* display verbose messages */
#define RELAX_NAMES(flags) (((flags)&(M_XCDR|M_RRIP)) == 0 && \
			    ((flags)&(M_DROPVERS|M_LOWERCASE)) == (M_DROPVERS|M_LOWERCASE))

#ifdef	_KERNEL

udecl_simple_lock_info(extern, cdfsmount_lockinfo)

#define	CDFSMOUNT_LOCK(nmp)		usimple_lock(&(nmp)->um_lock)
#define	CDFSMOUNT_UNLOCK(nmp)		usimple_unlock(&(nmp)->umlock)
#define	CDFSMOUNT_LOCK_TRY(nmp)		usimple_lock_try(&(nmp)->umlock)
#define	CDFSMOUNT_LOCK_HOLDER(nmp)	SLOCK_HOLDER(&(nmp)->umlock)
#define	CDFSMOUNT_LOCK_INIT(nmp) \
usimple_lock_setup(&(nmp)->umlock, cdfsmount_lockinfo)

/*
 * Convert mount ptr to cdfsmount ptr.
 */

#define VFSTOCDFS(mp)	((struct cdfsmount *)((mp)->m_info))

#endif
#endif /* _CDFS_CDFSMOUNT_ */
