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
 * @(#)$RCSfile: ffmmount.h,v $ $Revision: 1.1.15.2 $ (DEC) $Date: 1999/02/02 18:20:07 $
 */
/*
 * (c) Copyright 1990, 1991, 1992 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */
/*
 * OSF/1 1.1
 */
#ifndef _FFM_FFMMOUNT_
#define	_FFM_FFMMOUNT_

#include <sys/secdefines.h>
#ifdef	_KERNEL
#include <kern/lock.h>
#endif

/*
 * Mount structure.
 * One allocated on every mount.
 */
struct	ffmmount {
	struct	mount *fm_mountp;	/* vfs structure for this filesystem */
	struct	vnode *fm_vp;		/* vnode for file mounted */
	int	fm_flags;		/* flags */
};

#ifdef	_KERNEL
#define FFM_RDONLY 0x00000004		/* mount is read-only */
/*
 * Convert mount ptr to ffmmount ptr.
 */
#define VFSTOFFM(mp)	((struct ffmmount *)((mp)->m_info))

struct ffm_node {       /* a file-on-file vnode */
  struct vnode *fn_vnode;
  struct vnode *fn_shadow;
  struct ffmmount *fmp;
};

#define VTOF(vp)	((struct ffm_node *)(vp)->v_data)

#if SEC_FSCHANGE
extern struct vnsecops ffm_secops;
#endif /* SEC_FSCHANGE */

#endif /* _KERNEL */

#endif /* _FFM_FFMMOUNT_ */
