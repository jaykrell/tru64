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
 * @(#)$RCSfile: dvdfsmount.h,v $ $Revision: 1.1.7.1 $ (DEC) $Date: 2000/01/21 15:35:33 $
 */
#ifndef _DVDFSMOUNT_
#define	_DVDFSMOUNT_


/*
 * Mount structure.
 * One allocated on every mount.
 * Used to find the primary volume descriptor.
 */

struct	dvdfsmount {
	struct	mount *dm_mountp;	/* vfs structure for this filesystem */
	dev_t	dm_dev;			/* device mounted */
	struct	vnode *dm_devvp;	/* vnode for block device mounted */
	struct	vnode *dm_rootvp;	/* vnode for root of filesystem */
	struct	dvdfs *dm_fs;		/* pointer to pvd */
#ifdef	_KERNEL
	udecl_simple_lock_data(,dm_lock)/* multiprocessor exclusion */
#endif
};


#ifdef	_KERNEL

/*
 * Convert mount ptr to dvdfsmount ptr.
 */

#define VFSTODVDFS(mp)	((struct dvdfsmount *)((mp)->m_info))

#endif
#endif

