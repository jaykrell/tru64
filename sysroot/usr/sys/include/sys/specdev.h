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
 *	@(#)$RCSfile: specdev.h,v $ $Revision: 4.2.50.1 $ (DEC) $Date: 2001/09/21 13:16:42 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */

#ifndef _SYS_SPECDEV_H_
#define	_SYS_SPECDEV_H_

#ifdef	_KERNEL
/*
 * This file contains data structures that deal with special files and
 * aliases for special files.  Whenever a special file is activated
 * (via pathname translation), a struct specinfo is allocated to hold
 * device file-specific information.  An alias (struct specalias) is a 
 * structure that associates all vnodes for a given open device.  They 
 * are required because it is possible for more than one special file to 
 * represent the same device. 
 */
#include <kern/queue.h>

/*
 * This structure is allocated when a vnode for a special file is created
 * during pathname translation. 
 * Locking:
 * 	All fields in this structure are protected by the spec hashchain
 *	lock for the device.
 * NOTE:
 *	See IMPORTANT NOTE below about alignment of si_rdev.
 */

struct specinfo {
	dev_t		 si_rdev;
	struct vnode	 *si_nextalias;		/* next vnode on alias list */
	struct vnode	 *si_shadowvp;		/* shadow vnode for VBLK */
	struct specalias *si_alias;		/* our alias structure */
};

/*
 * This structure is allocated when a device is opened (after pathname
 * translation.  It serves as an alias for multiple vnodes referencing the
 * same device.  If it is a block device, it has an associated vnode that
 * is used for operation involving the buffer cache (read, write, close).
 */

struct specalias {
	dev_t		sa_rdev;
	int		sa_opencount;   /* count of opens in progress */
	u_long		sa_flag;	/* Alias state. See flags below. */
	enum vtype 	sa_type;	/* type of alias (VCHR, VBLK) */
	long		sa_usecount;	/* Count of valid device opens */
	struct vnode	*sa_vlist;	/* Head of vnode alias list */
	struct vnode 	*sa_vnode;	/* Shadow vnode, if VBLK only. */
	struct specalias *sa_next;	/* next struct on hash chain */
	void            *sa_private;    /* private pointer for spec ops */
	queue_head_t    sa_thread_list; /* chain of threads with in flight ops */
};

/*
 * Data structures for aliasing special vnodes
 */

struct spechash {
	udecl_simple_lock_data(,sh_lock)	/* a spin lock */
	struct specalias *sh_alias;		/* the hash chain */
};

#define v_rdev v_specinfo->si_rdev

/*
 * this is where the attributes are stored for
 * specfs vnodes
 */
struct spec_node {
	struct vnode *sn_vnode;
	struct vattr sn_vattr;
	void * fmp;
};

#define VTOS(vp)	((struct spec_node *)(vp)->v_data)
/*
 * flags for struct specinfo
 *	an in-progress revoke/clearalias will set SA_GOING|SA_REVOKE,
 *	when the clearalias is complete, the SA_GOING is removed;
 *	this is used to detect in-progress revoke of a device.
 */
#define SA_MOUNTED	0x0001	/* file system mounted here */
#define SA_CLOSING	0x0002	/* close in progress */
#define SA_GOING	0x0004	/* clearalias/revoke in progress */
#define SA_WAIT		0x0008	/* someone waiting on one of above */
#define SA_REVOKE	0x0010	/* revoke completed for this specalias */
#define SA_OPENING	0x0020  /* opening in progress */
#define SA_PRIVATE_DEV	0x0040  /* private vnode that can't be revoked */

/*
 * Flags passed to setmount.
 */
#define SM_MOUNTED	0x0001		/* check to see if device is mounted */
#define SM_OPEN		0x0002		/* check to see if device is open */
#define SM_SETMOUNT	0x0004		/* mark the device as mounted */
#define SM_CLEARMOUNT	0x0008		/* clear the mounted flag on device */


#define MINSPECHSZ	16
extern int spechsz;
extern struct spechash *speclisth;
extern int	setmount();		/* manipulate mount-related aliases */

#define SPEC_DONTOPEN 00040000   /* dont open cloned device */

#define SPECHASH(rdev)		(((rdev>>5)+(rdev))&(spechsz-1))
#define SPECHASH_LOCK(sh)	usimple_lock(&sh->sh_lock)
#define SPECHASH_UNLOCK(sh)	usimple_unlock(&sh->sh_lock)

#define SPEC_STATS		/* Track specfs stats */
#ifdef SPEC_STATS

/*
 * These are low-frequency stats (vague).  If this changes,
 * they should be moved to a per-processor structure.
 */
struct spec_stats {
	u_int	clearalias_racers;
	u_int	clearalias_vxlock_fails;
	u_int	clearalias_vget_fails;
	u_int	clearalias_list_len;	/* Longest alias list ever cleared. */
	u_int	clearalias_not_on_alias_list;
	u_int	clearalias_vop_revoke_fails;
	u_int	revoke_ufs_iupdat_deflections;
	u_int	spec_reclaim_deflections;
};
extern struct spec_stats spec_stats;

#define SPEC_STAT_INC(field)	spec_stats.field++

#else

#define SPEC_STAT_INC(field)

#endif /* SPEC_STATS */

#endif	/* _KERNEL */
#endif	/* _SYS_SPECDEV_H_ */
