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
 *	@(#)$RCSfile: vnode.h,v $ $Revision: 4.3.223.3 $ (DEC) $Date: 2002/01/29 21:20:03 $
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
 * Copyright (c) 1989 The Regents of the University of California.
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

#ifndef _SYS_VNODE_H_
#define	_SYS_VNODE_H_
#include <standards.h>
_BEGIN_CPLUSPLUS

#ifdef  _KERNEL
#include <kern/assert.h>
#endif
#include <sys/sp_attr.h>

#include <sys/time.h>           /* for timeval struct */

#include <sys/mount.h>
#if 0
#include <sys/secdefines.h>
#endif
#include <machine/endian.h>
#include <sys/unix_defs.h>
#ifndef _NO_PROTO
#include <mach/vm_prot.h>       /* for vm_prot_t typedef */
#include <mach/memory_object.h> /* for memory_object_t typedef */
#include <sys/time.h>           /* for timeval struct */
#endif
#if	SEC_FSCHANGE
#include <sys/security.h>
#endif
#ifdef	_KERNEL
#include <sys/vp_swap.h>
#include <kern/parallel.h>	/* unix_master() */
#else
#ifndef _NO_PROTO
typedef enum {VPS_OPEN, VPS_CLOSE, VPS_MAP} vp_swap_op_t;
#endif
#endif

/*
 * The vnode is the focus of all file activity in UNIX.
 * There is a unique vnode allocated for each active file,
 * each current directory, each mounted-on file, text file, and the root.
 */

/*
 * vnode types. VNON means no type.
 */
enum vtype 	{ VNON, VREG, VDIR, VBLK, VCHR, VLNK, VSOCK, VFIFO, VBAD };
typedef enum vtype	vtype_t;

/*
 * Vnode tag types.
 * These are for the benefit of external programs only (e.g., pstat)
 * and should NEVER be inspected inside the kernel.
 */

enum vtagtype { VT_NON, VT_UFS, VT_NFS, VT_MFS, VT_S5FS, VT_CDFS, VT_DFS,
		VT_EFS, VT_PRFS, VT_MSFS, VT_FFM, VT_FDFS, VT_ADDON,
		VT_CFS, VT_CSPECFS, VT_DVDFS, VT_AUTOFS
};


/*
 * This defines the maximum size of the private data area
 * permitted for any file system type.  Vn_maxprivate is
 * set early in the boot sequence based on the largest
 * filesystem-specific representation.  The actual size
 * of a vnode will depend on vn_maxprivate at run-time.
 */
extern int	vn_maxprivate;

/* forward declarations for ANSI & C++ */
struct eflock;
struct socket;
struct specinfo;
struct fifonode;
struct namecache;
struct nameidata;
struct nchash;
struct vm_object;
struct vm_ubc_object;
struct vnodeops;
struct buf;
struct ucred;
struct uio;
struct vattr;
struct vm_map;
struct vm_page;
struct mount;
struct vm_map_entry;

#ifdef __VMS
struct file;
#endif  /* __VMS */

struct vnode {
	udecl_simple_lock_data(,v_lock)		/* multiprocessor exclusion */
	u_int		v_flag;			/* vnode flags (see below) */
	uint_t		v_usecount;		/* reference count of users */
	u_int		v_aux_lockers;		/* Semaphore, zero if free */
	u_short		v_shlockc;		/* count of shared locks */
	u_short		v_exlockc;		/* count of exclusive locks */
	off_t		v_lastr;		/* last read (read-ahead) */
	u_long		v_id;			/* capability identifier */
	enum vtype	v_type;			/* vnode type */
	enum vtagtype	v_tag;			/* type of underlying data */
	struct mount	*v_mount;		/* ptr to vfs we are in */
	struct mount	*v_mountedhere;		/* ptr to mounted vfs */
	struct vnodeops	*v_op;			/* vnode operations */
	struct vnode	*v_freef;		/* vnode freelist forward */
	struct vnode	**v_freeb;		/* vnode freelist back */
	struct vnode	*v_mountf;		/* vnode mountlist forward */
	struct vnode	**v_mountb;		/* vnode mountlist back */
	udecl_simple_lock_data(,v_buflists_lock)/* protect clean/dirty blkhd */
	struct buf	*v_cleanblkhd;		/* clean blocklist head */
	struct buf	*v_dirtyblkhd;		/* dirty blocklist head */
	u_int		v_ncache_time;		/* last cache activity time */
	u_int		v_free_time;		/* time on vnode free_list */
	udecl_simple_lock_data(,v_output_lock)	/* protect numoutput, outflag */
	int		v_numoutput;		/* num of writes in progress */
	u_int		v_outflag;		/* output flags */
	u_int		v_cache_lookup_refs;	/* dnlc/vdealloc protection */
	u_int		v_rdcnt;		/* count of readers */
	u_int		v_wrcnt;		/* count of writers */
	u_int		v_dirtyblkcnt;		/* dirty block count */
	u_int		v_dirtyblkpush;		/* blocks to push per smsync cycle */
	union {
		struct socket	*vu_socket;	/* unix ipc (VSOCK) */
		struct specinfo	*vu_specinfo;	/* device specinfo structure */
		struct fifonode	*vu_fifonode;	/* pipe and fifo structure */
	} v_un;
	struct vm_ubc_object *v_object;		/* VM object for vnode */
	secinfo_t     *v_secattr;
#if SEC_FSCHANGE
	struct vnsecops	*v_secop;		/* vnode security operations */
#endif
	void *v_drv_handle;			/* Driver handle */
	long  v_bsize;				/* for blk io spec_read & 
						   spec_write */
#ifdef __VMS
	/*
	 * OPENVMS specific fields relating to VNODEs.
	 */
	fhandle_t       v_openvms_fhandle;	/* File handle of this vnode */
#define v_openvms_fsid v_openvms_fhandle.fh_fsid
#define v_openvms_efid v_openvms_fhandle.fh_efid
#define v_openvms_fid  v_openvms_fhandle.fh_fid
	unsigned long  v_openvms_pindex;	/* Process index of accessor */
	unsigned long  v_openvms_channel;	/* Channel number of access */
	char * v_openvms_timerq[2];		/* Queue of this VNODE within timer */
	unsigned long  v_openvms_timer;		/* Expiration (access) timer */
#endif  /* __VMS */

	char v_data[1];				/* placeholder, private data */
};
typedef struct vnode vnode_t;

/*
 * Note: size of the vnode structure can be reduced by combining the
 * v_buflists_lock with v_output_lock. However, lock contention will
 * increase marginally.
 */
#define v_socket v_un.vu_socket
#define v_specinfo v_un.vu_specinfo
#define v_fifonode v_un.vu_fifonode

/*
 * vnode flags.
 */
#define	VROOT		0x0001	/* root of its file system */
#define	VTEXT		0x0002	/* obsolete (was pure text prototype flag) */
#define	VXLOCK		0x0004	/* vnode is locked to change underlying type */
#define	VXWANT		0x0008	/* process is waiting for vnode */
#define	VEXLOCK		0x0010	/* exclusive lock */
#define	VSHLOCK		0x0020	/* shared lock */
#define	VLWAIT		0x0040	/* proc is waiting on shared or excl. lock */
#define VCLONE		0x0080  /* vnode is a clone */
#define	VMOUNTPOINT	0x0100  /* file system mounted here (or will be soon) */
#define	VINACTIVATING	0x0200  /* vrele underway */
#define VFLOCK		0x0400	/* vnode is locked for first fifo open */
#define VFWAIT		0x0800	/* waiting for fifo open */
#define	VSYSTEM		0x1000	/* vnode being used by kernel */
#define VENF_LOCK       0x2000  /* mandatory file locking enabled */
#define VLOCKS          0x4000  /* fcntl file locks on file */
#define	VSWAP		0x8000	/* swapping on this vnode */
#define	VCOBJECT     	0x10000 /* creating vnode object */
#define	VCWAIT		0x20000 /* waiting for creation to complete */
#define V_PRIVATE       0x40000 /* private DFS vnode; don't place on free chain */
#define V_CONVERTED     0x80000 /* vnode converted for VFS+ usage */
#define V_AUD_VALID	0x100000 /* V_AUD_{DE}SELECT bits are valid */
#define VIOERROR	0x200000 /* Write error */
#define V_DELAYED	0x400000 /* device vnode, mounted M_DELAYED */
#define V_AUD_SELECT	0x800000 /* select object for auditing */
#define V_AUD_DESELECT	0x1000000 /* bypass data access auditing */
#define VDIRECTIO	0x2000000 /* by-pass the buffer cache */
#define VMMAPPED	0x4000000 /* file has been mmapped */
#define	VREVOKED	0x8000000 /* Vnode has been revoked by clearalias */
#define VMLD		0x10000000 /* vnode is a multilevel directory */
#define VXENIX		0x20000000 /* xenix file locks on file */
#define VDUP		0x40000000 /* duplicate on open(); for FDFS */
#define VCOVERED	0x80000000 /* CFS: Vnode is covered */

/*
 * vnode output flags
 */
#define	VOUTWAIT	0x0001	 /* waiting for output to complete */

#ifdef _KERNEL
/*
 * Vnode table statistics.
 */
struct vnode_stats {
	u_long	vn_allocations;		/* number of vnode MALLOCs */
	u_long	vn_recycled;		/* number of vnodes recycled */ 
	u_long	vn_getnewcalls;		/* number of calls to getnewvnode */
	u_long	vn_getlock;		/* getnewvnode hitting lock or VXLOCK */
	u_long	vn_vgetcalls;		/* total calls to vgetm */
	u_long	vn_vgetfree;		/* calls to vgetm accessing free list */
	u_long	vn_freecalls;		/* total number put on free list */
	u_long	vn_failget;		/* failed getnewvnode calls */
	u_long	vn_waitvxlock;		/* VXLOCK hit in wait_for_vxlock */
	u_long	vn_inactivating;	/* vget found VINACTIVATING */
	u_long	vn_transitioning;	/* vgetm_nowait VXLOCK|VINACTIVATING */
	u_long	vn_prim_deallocs;	/* # primary deallocs (getnewvnode) */
	u_long	vn_sec_deallocs;	/* # secondary deallocs (vdealloc) */
	u_long	vn_failed_prim_deallocs;/* primary deallocation failures  */
	u_long	vn_failed_sec_deallocs;	/* secondary deallocation failures */
	u_long	vn_pad[9];		/* pad out to 192 bytes for expansion */
};
/*
 * Vnode stats are tracked on a per CPU basis.
 * The table(TBL_VNODESTATS) syscall reports system wide stats.
 */
#ifndef __VMS
#define	VSTAT(field)	current_processor()->vnode_stats.field
#else /* __VMS */
#define	VSTAT(field)	openvms_vnode_stats.field
extern struct vnode_stats openvms_vnode_stats;
#endif /* __VMS */

#endif /* _KERNEL */

/*
 * Operations on vnodes.
 */
struct vnodeops {
	int	(*vn_lookup) __((struct vnode *, struct nameidata *));
	int	(*vn_create) __((struct nameidata *, struct vattr *));
	int	(*vn_mknod) __((struct nameidata *, struct vattr *, struct ucred *));
	int	(*vn_open) __((struct vnode **, int, struct ucred *));
	int	(*vn_close) __((struct vnode *, int, struct ucred *));
#ifndef __VMS
	int	(*vn_access) __((struct vnode *, int, struct ucred *));
	int	(*vn_getattr) __((struct vnode *, struct vattr *, struct ucred *));
#else /* __VMS */
	int	(*vn_access_vms) __((struct vnode *, int, struct ucred *, int *));
	int	(*vn_getattr_vms) __((struct vnode *, struct vattr *, struct ucred *, fhandle_t *));
#endif /* __VMS */
	int	(*vn_setattr) __((struct vnode *, struct vattr *, struct ucred *));
#ifndef __VMS
	int	(*vn_read) __((struct vnode *, struct uio *, int, struct ucred *));
	int	(*vn_write) __((struct vnode *, struct uio *, int, struct ucred *));
#else /* __VMS */
	int	(*vn_read_vms) __((struct vnode *, struct uio *, int, struct ucred *, fhandle_t *));
	int	(*vn_write_vms) __((struct vnode *, struct uio *, int, struct ucred *, fhandle_t *));
#endif /* __VMS */
	int	(*vn_ioctl) __((struct vnode *, int, caddr_t, int, struct ucred *, int *));
#ifdef __digital__
	int     (*vn_select) __((struct vnode *, int *, int *, int, struct ucred *));
#else
	int	(*vn_select) __((struct vnode *, short *, short *, int, struct ucred *));
#endif
	int	(*vn_mmap) __((struct vnode *, vm_offset_t, struct vm_map *, vm_offset_t *,
                               vm_size_t, vm_prot_t, vm_prot_t, int, struct ucred *));
	int	(*vn_fsync) __((struct vnode *, int, struct ucred *, int));
	int	(*vn_seek) __((struct vnode *, off_t, off_t, struct ucred *));
	int	(*vn_remove) __((struct nameidata *));
	int	(*vn_link) __((struct vnode *, struct nameidata *));
	int	(*vn_rename) __((struct nameidata *, struct nameidata *));
	int	(*vn_mkdir) __((struct nameidata *, struct vattr *));
	int	(*vn_rmdir) __((struct nameidata *));
	int	(*vn_symlink) __((struct nameidata *, struct vattr *, char *));
#ifndef __VMS
	int	(*vn_readdir) __((struct vnode *, struct uio *, struct ucred *, int *));
#else /* __VMS */
	int	(*vn_readdir_vms) __((struct vnode *, struct uio *, struct ucred *, unsigned long *, int *));
#endif /* __VMS */
	int	(*vn_readlink) __((struct vnode *, struct uio *, struct ucred *));
	int	(*vn_abortop) __((struct nameidata *));
	int	(*vn_inactive) __((struct vnode *));
	int	(*vn_reclaim) __((struct vnode *, int));
	int	(*vn_bmap) __((struct vnode *, daddr_t, struct vnode **, daddr_t *));
	int	(*vn_strategy) __((struct buf *));
	int	(*vn_print) __((struct vnode *));
	int	(*vn_pgrd) __((struct vnode *, struct uio *, struct ucred *));
	int	(*vn_pgwr) __((struct vnode *, struct uio *, struct ucred *,
                               memory_object_t, vm_offset_t));
	int	(*vn_swap) __((struct vnode *, vp_swap_op_t, vm_offset_t, struct ucred *));
	int	(*vn_bread) __((struct vnode *, off_t, struct buf **, struct ucred *));
	int	(*vn_brelse) __((struct vnode *, struct buf *));
	int	(*vn_lockctl) __((struct vnode *, struct eflock *, int, struct ucred *, pid_t, off_t));
	int	(*vn_syncdata) __((struct vnode *, int, vm_offset_t, vm_size_t, struct ucred *));
	int	(*vn_lock) __((struct vnode *, int, struct ucred *));
	int	(*vn_unlock) __((struct vnode *, int, struct ucred *));
	int	(*vn_getproplist) __((struct vnode *, char **, struct uio *, int *, int,
                                      struct ucred *));
	int	(*vn_setproplist) __((struct vnode *, struct uio *, struct ucred *));
	int	(*vn_delproplist) __((struct vnode *, char **, int, struct ucred *, long));
 	int	(*vn_pathconf) __((struct vnode *, int, long *));
};

/*
 * Invoking a vnode operation implies funnelling when SER_COMPAT
 * is turned on.  When KTRACE is defined, then record trace points
 * before and after the call.
 */

#ifdef KTRACE
#define VcallKT(f) kern_trace(602, (long) &((struct vnodeops *) 0)->f, 0, 0, 0)
#define VdoneKT    kern_trace(603, 0, 0, 0, 0)
#else
#define VcallKT(f)
#define VdoneKT
#endif

#ifndef __VMS
#define	_VOP_(f,v,arg,r)						\
MACRO_BEGIN								\
	VcallKT(f);							\
	if (!MOUNT_FUNNEL((v)->v_mount)) {				\
		(r) = (*((v)->v_op->f))arg;				\
	} else {							\
		unix_master();						\
		(r) = (*((v)->v_op->f))arg;				\
		unix_release();						\
	}								\
	VdoneKT;							\
MACRO_END
#else /* __VMS */
#define	_VOP_(f,v,arg,r)						\
MACRO_BEGIN								\
	(r) = (*((v)->v_op->f))arg;					\
MACRO_END
#endif /* __VMS */

/* Macros to call the vnode ops */
#define	VOP_LOOKUP(v,n,r)	_VOP_(vn_lookup,(v),((v),(n)),(r))
#define	VOP_CREATE(n,a,r)	_VOP_(vn_create,(n)->ni_dvp,((n),(a)),(r))
#define	VOP_MKNOD(n,a,c,r)	_VOP_(vn_mknod,(n)->ni_dvp,((n),(a),(c)),(r))
#define	VOP_OPEN(vpp,f,c,r)	_VOP_(vn_open,(*vpp),((vpp),(f),(c)),(r))
#define	VOP_CLOSE(v,f,c,r)	_VOP_(vn_close,(v),((v),(f),(c)),(r))
#ifndef __VMS
#define	VOP_ACCESS(v,f,c,r)	_VOP_(vn_access,(v),((v),(f),(c)),(r))
#define	VOP_GETATTR(v,a,c,r)	_VOP_(vn_getattr,(v),((v),(a),(c)),(r))
#else /* __VMS */
#define VOP_ACCESS_VMS(v,f,c,o,r) _VOP_(vn_access_vms,(v),((v),(f),(c),(o)),(r))
#define	VOP_GETATTR_VMS(v,a,c,f,r) _VOP_(vn_getattr_vms,(v),((v),(a),(c),(f)),(r))
#endif /* __VMS */
#define	VOP_SETATTR(v,a,c,r)	_VOP_(vn_setattr,(v),((v),(a),(c)),(r))
#ifndef __VMS
#define	VOP_READ(v,u,i,c,r)	_VOP_(vn_read,(v),((v),(u),(i),(c)),(r))
#define	VOP_WRITE(v,u,i,c,r)	_VOP_(vn_write,(v),((v),(u),(i),(c)),(r))
#else /* __VMS */
#define	VOP_READ_VMS(v,u,i,c,f,r)	_VOP_(vn_read_vms,(v),((v),(u),(i),(c),(f)),(r))
#define	VOP_WRITE_VMS(v,u,i,c,f,si,sop,r)	_VOP_(vn_write_vms,(v),((v),(u),(i),(c),(f),(si),(sop)),(r))
#endif /* __VMS */
#define	VOP_IOCTL(v,o,d,f,c,r,rv) _VOP_(vn_ioctl,(v),((v),(o),(d),(f),(c),(rv)),(r))
#define	VOP_SELECT(v,e,r,s,c,x)	_VOP_(vn_select,(v),((v),(e),(r),(s),(c)),(x))
#define	VOP_MMAP(v,o,m,a,l,p,mp,f,c,r)				\
		_VOP_(vn_mmap,(v),((v),(o),(m),(a),(l),(p),(mp),(f),(c)),r)
#define	VOP_FSYNC(v,f,c,w,r)	_VOP_(vn_fsync,(v),((v),(f),(c),(w)),(r))
#define	VOP_SEEK(v,p,o,w,r)	_VOP_(vn_seek,(v),((v),(p),(o),(w)),(r))
#define	VOP_REMOVE(n,r)		_VOP_(vn_remove,(n)->ni_dvp,((n)),(r))
#define	VOP_LINK(v,n,r)		_VOP_(vn_link,(n)->ni_dvp,((v),(n)),(r))
#define	VOP_RENAME(s,t,r)	_VOP_(vn_rename,(s)->ni_dvp,((s),(t)),(r))
#define	VOP_MKDIR(n,a,r)	_VOP_(vn_mkdir,(n)->ni_dvp,((n),(a)),(r))
#define	VOP_RMDIR(n,r)		_VOP_(vn_rmdir,(n)->ni_dvp,((n)),(r))
#define	VOP_SYMLINK(n,a,m,r)	_VOP_(vn_symlink,(n)->ni_dvp,((n),(a),(m)),(r))
#ifndef __VMS
#define	VOP_READDIR(v,u,c,e,r)	_VOP_(vn_readdir,(v),((v),(u),(c),(e)),(r))
#else /* __VMS */
#define	VOP_READDIR_VMS(v,u,c,cv,e,r) _VOP_(vn_readdir_vms,(v),((v),(u),(c),(cv),(e)),(r))
#endif /* __VMS */
#define	VOP_READLINK(v,u,c,r)	_VOP_(vn_readlink,(v),((v),(u),(c)),(r))
#define	VOP_ABORTOP(n,r)	_VOP_(vn_abortop,(n)->ni_dvp,((n)),(r))
#define	VOP_INACTIVE(v,r)	_VOP_(vn_inactive,(v),((v)),(r))
#define	VOP_RECLAIM(v,f,r)	_VOP_(vn_reclaim,(v),((v),(f)),(r))
#define	VOP_BMAP(v,s,p,n,r)	_VOP_(vn_bmap,(v),((v),(s),(p),(n)),(r))
#define	VOP_STRATEGY(b,r)	_VOP_(vn_strategy,(b)->b_vp,((b)),(r))
#define	VOP_PRINT(v,r)		_VOP_(vn_print,(v),((v)),(r))
#define	VOP_PGRD(v,u,c,r)	_VOP_(vn_pgrd,(v),((v),(u),(c)),(r))
#define	VOP_PGWR(v,u,c,p,o,r)	_VOP_(vn_pgwr,(v),((v),(u),(c),(p),(o)),(r))
#define	VOP_SWAP(v,o,a,c,r)	_VOP_(vn_swap,(v),((v),(o),(a),(c)),r)
#define	VOP_BREAD(v,l,b,c,r)	_VOP_(vn_bread,(v),((v),(l),(b),(c)),r)
#define	VOP_BRELSE(v,b,r)	_VOP_(vn_brelse,(v),((v),(b)),r)
#define VOP_LOCKCTL(v,l,cm,cr,p,o,r) \
	_VOP_(vn_lockctl,(v),((v),(l),(cm),(cr),(p),(o)),(r))
#define VOP_SYNCDATA(v,f,o,l,c,r) \
	_VOP_(vn_syncdata,(v),((v),(f),(o),(l),(c)),(r))
#define VOP_LOCK(v,f,c,r)	_VOP_(vn_lock,(v),((v),(f),(c)),r)
#define VOP_UNLOCK(v,f,c,r)	_VOP_(vn_unlock,(v),((v),(f),(c)),r)
#define VOP_GETPROPLIST(v,n,u,min_buf_size,f,c,r)                   \
	_VOP_(vn_getproplist,(v),((v),(n),(u),(min_buf_size),(f),(c)),r)
#define VOP_SETPROPLIST(v,u,c,r)                                    \
	_VOP_(vn_setproplist,(v),((v),(u),(c)),r)
#define VOP_DELPROPLIST(v,n,f,c,x,r)					\
	_VOP_(vn_delproplist,(v),((v),(n),(f),(c),(x)),r)
#define	VOP_PATHCONF(v,i,rv,r) _VOP_(vn_pathconf,(v),((v),(i),(rv)),(r))

/*
 * flags for ioflag
 */
#define IO_UNIT		0x01		/* do I/O as atomic unit */
#define IO_APPEND	0x02		/* append write to end */
#define IO_SYNC		0x04		/* do I/O synchronously */
#define IO_NODELOCKED	0x08		/* underlying node already locked */
#define	IO_NDELAY	0x10		/* FNDELAY flag set in file table */
#define IO_TRUNC        0x20            /* file is being truncated */
#define	IO_NONBLOCK	0x80		/* FNONBLOCK flag set in file table */
#define IO_RSYNC        0x100           /* POSIX1003.1b -read i/o integrity */
#define IO_DSYNC        0x200           /* POSIX1003.1b -write data integrity*/
                                        /* note that IO_DATAONLY is defined */
	                                /* (below) to be IO_DSYNC */
#define	IO_NOSTATUPDATE	0x400		/* Don't update mtime and ctime on a
					   write.  Used by CFS.  */

#define IO_DMAPI_INVIS  0x800           /* Invisible I/O operation
                                         * (no timestamp update) for
                                         * CAE DMAPI spec.
                                         */

/*
 * DEC/OSF advisory flags for VOP_WRITE calls.
 * These flags are additive to other ioflag values.
 * Local filesystem types need not necessarily recognize them.
 */
#define	IO_DATAONLY	IO_DSYNC	/* synchronously write data only */
                                        /* (no metadata) for IO_SYNC write */
                                        /* request (additive with IO_SYNC). */
                                        /* Since IO_DATAONLY is functionally */
                                        /* same as POSIX 1003.1b IO_DSYNC, */
                                        /* define it to be IO_DSYNC. */
#define IO_DELAYDATA	0x40		/* delay data write as long as */
                                        /* possible for async write request */
                                        /* (additive with "IO_ASYNC", which */
                                        /*  is 0x0). */ 

#define IO_CFS_QUOTA_IGNORE	0x1000	/* Force pfs write to succeed regardless */
					/* of quota limits.                      */

/*
 * Vnode attributes.  A field value of VNOVAL
 * represents a field whose value is unavailable
 * (getattr) or which is not to be changed (setattr).
 *
 * The field va_rawmode is used only for object creation, and will be
 * VNOVAL unless va_mode has had the cmask applied.
 */
struct vattr {
	int		va_mask;        /* bit-mask of attributes */
	enum vtype	va_type;	/* vnode type (for create) */
	u_short		va_mode;	/* files access mode and type */
	nlink_t		va_nlink;	/* number of references to file */
	uid_t		va_uid;		/* owner user id */
	gid_t		va_gid;		/* owner group id */
	int		va_fsid;	/* file system id (dev for now) */
	int		va_fileid;	/* file id */
	u_short		va_rawmode;	/* va_mode before cmask is applied */
#if __arch32__
	unsigned long long va_qsize;	/* file size in bytes */
#else /* __arch32__ */
	u_long		va_qsize;	/* file size in bytes */
#endif /* __arch32__ */
	int		va_blocksize;	/* blocksize preferred for i/o */
	struct timeval	va_atime;	/* time of last access */
	struct timeval	va_mtime;	/* time of last modification */
	struct timeval	va_ctime;	/* time file changed */
	u_int		va_gen;		/* generation number of file */
	u_int		va_flags;	/* flags defined for file */
	dev_t		va_rdev;	/* device special file represents */
#if __arch32__
	unsigned long long va_qbytes;	/* bytes of disk space held by file */
#else /* __arch32__ */
	u_long		va_qbytes;	/* bytes of disk space held by file */
#endif /* __arch32__ */
	union {
		char	*vau_symlink;	/* name of symlink to be created */
		char	*vau_socket;	/* address of socket (XX make void *) */
	} va_un;
#ifdef __VMS
	unsigned long	va_openvms_uic;	/* OPENVMS file owner's UIC */
#endif /* __VMS */
};
typedef struct vattr vattr_t;

#define va_symlink      va_un.vau_symlink
#define va_socket       va_un.vau_socket

/*
 * On 32 bit systems we'll deal with this by using long long
 */
#if __digital__
#define	va_size		va_qsize
#define	va_bytes	va_qbytes
#else
#if	BYTE_ORDER == LITTLE_ENDIAN
#define	va_size		va_qsize.val[0]
#define	va_size_rsv	va_qsize.val[1]
#define	va_bytes	va_qbytes.val[0]
#define	va_bytes_rsv	va_qbytes.val[1]
#else
#define	va_size		va_qsize.val[1]
#define	va_size_rsv	va_qsize.val[0]
#define	va_bytes	va_qbytes.val[1]
#define	va_bytes_rsv	va_qbytes.val[0]
#endif
#endif

/*
 * Attributes of interest to the caller of setattr or getattr.
 */
#define AT_TYPE         0x0001
#define AT_MODE         0x0002
#define AT_UID          0x0004
#define AT_GID          0x0008
#define AT_FSID         0x0010
#define AT_NODEID       0x0020
#define AT_NLINK        0x0040
#define AT_SIZE         0x0080
#define AT_ATIME        0x0100
#define AT_MTIME        0x0200
#define AT_CTIME        0x0400
#define AT_RDEV         0x0800
#define AT_BLKSIZE      0x1000
#define AT_NBLOCKS      0x2000
#define AT_VCODE        0x4000

#define AT_ALL          (AT_TYPE|AT_MODE|AT_UID|AT_GID|AT_FSID|AT_NODEID|\
                        AT_NLINK|AT_SIZE|AT_ATIME|AT_MTIME|AT_CTIME|\
                        AT_RDEV|AT_BLKSIZE|AT_NBLOCKS|AT_VCODE)

#define AT_STAT         (AT_MODE|AT_UID|AT_GID|AT_FSID|AT_NODEID|AT_NLINK|\
                        AT_SIZE|AT_ATIME|AT_MTIME|AT_CTIME|AT_RDEV)

#define AT_TIMES        (AT_ATIME|AT_MTIME|AT_CTIME)

#define AT_NOSET        (AT_NLINK|AT_RDEV|AT_FSID|AT_NODEID|AT_TYPE|\
                        AT_BLKSIZE|AT_NBLOCKS|AT_VCODE)

/*
 *  Modes.
 */
#define	VSUID	04000		/* set user id on execution */
#define	VSGID	02000		/* set group id on execution */
#define	VSVTX	01000		/* save swapped text even after use */
#define VREAD   00400
#define VWRITE  00200
#define VEXEC   00100

#define MODEMASK        07777   /* mode bits plus permission bits */
#define PERMMASK        00777   /* permission bits */

#if	SEC_FSCHANGE

#define	VHASSECOPS(vp)	((vp)->v_secop)
#define	VSECURE(vp)	((vp)->v_mount->m_flag & M_SECURE)

#if 	SEC_MAC
#define	VMLSD(vp)	((vp)->v_mount->m_flag & M_MLSD)
#endif

struct vnsecops {
	int	(*vn_getsecattr) __((struct vnode *, struct vsecattr *, struct ucred *));
	int	(*vn_setsecattr) __((struct vnode *, struct vsecattr *, struct ucred *));
	int	(*vn_dirempty) __((struct vnode *, struct vsecattr *, struct ucred *));
};

#define	VOP_GETSECATTR(v,a,c,r)	(r) = (*((v)->v_secop->vn_getsecattr))((v),(a),(c))
#define	VOP_SETSECATTR(v,a,c,r)	(r) = (*((v)->v_secop->vn_setsecattr))((v),(a),(c))
#define	VOP_DIREMPTY(v,p,c,r)	(r) = (*((v)->v_secop->vn_dirempty))((v),(p),(c))

struct vsecattr {
	u_int		vsa_valid;	/* which fields are valid (see below) */
	u_char		vsa_policy;	/* policy index for vsa_tag */
	u_char		vsa_tagnum;	/* policy-relative tag index */
	struct vnode	*vsa_parent;	/* parent vnode for tag changes */
	tag_t		vsa_tags[SEC_TAG_COUNT];	/* tag pool */
	privvec_t	vsa_gpriv;	/* granted privileges */
	privvec_t	vsa_ppriv;	/* potential privileges */
	u_int		vsa_type_flags;	/* type flags (MLD, 2 person, etc.) */
	uid_t		vsa_uid;	/* POSIX ACL uid(result of tag change)*/
	gid_t		vsa_gid;	/* POSIX ACL group ID (ditto) */
	mode_t		vsa_mode;	/* POSIX ACL mode (ditto) */
};
#define	vsa_tag	vsa_tags[0]
#define	vsa_child vsa_parent

/* Flag values for vsa_valid field */
#define	VSA_TAG		0x0001
#define	VSA_GPRIV	0x0002
#define	VSA_PPRIV	0x0004
#define	VSA_TYPE_FLAGS	0x0008
#define	VSA_ALLTAGS	0x0010
/*
 * POSIX ACL
 */
#define VSA_UID		0x0020
#define VSA_GID		0x0040
#define VSA_MODE	0x0080
/*
 * Directory Entry SL/IL changes.
 */
#define VSA_FILENAME	0x0100

#endif	/* SEC_FSCHANGE */

/*
 * Token indicating no attribute value yet assigned
 */
#ifdef __arch32__
#define VNOVAL	((unsigned long)0xfffffff)
#else /* __arch32__ */
#define VNOVAL	((unsigned long)0xffffffffffffffff)
#if defined(__VMS) && defined(__VAX)
#define VNOVAL32 ((unsigned long)0xffffffff)
#define VNOVAL64 ((unsigned long)0xffffffffffffffff)
#endif /* __VMS && __VAX */
#endif /* __arch32__ */
#ifdef	_KERNEL
/*
 * Vnode locking constraints.
 *	Field			Comment
 *	-----			-------
 *	v_flag			v_lock
 *	v_usecount		v_lock
 *	v_shlockc		v_lock
 *	v_exlockc		v_lock
 *	v_lastr			v_lock
 *	v_id			v_lock
 *	v_mount			read-only?	XXX
 *	v_op			v_lock
 *	v_freef			v_free_lock
 *	v_freeb			v_free_lock
 *	v_mountf		m_vlist_lock
 *	v_mountb		m_vlist_lock
 *	v_cleanblkhd		v_buflists_lock
 *	v_dirtyblkhd		v_buflists_lock
 *	v_numoutput		v_output_lock
 *	v_outflag		v_output_lock
 *	v_type			v_lock
 *	v_mountedhere		v_lock + VMOUNTPOINT (r/o except for funmnt)
 *	vu_socket		v_lock  -- only valid for VSOCK.
 * The next two fields are only valid for device special types (VCHR, VBLK)
 *	vu_nextalias		speclist hashchain lock
 *	v_rdev			v_lock
 *	v_tag			v_lock
 *	v_rdcnt			v_lock
 *	v_wrcnt			v_lock
 *	v_dirytblkcnt		v_buflists_lock
 *	v_dirtyblkpush		v_buflists_lock
 *	v_vm_info		read-only
 *	v_*			v_aux_lock (see note below)
 *
 * Special privileges are accorded unparallelized filesystem types,
 * as follows.  Manipulation of globally used fields (e.g. lists) is
 * not allowed by the filesystem, and is done under lock in the proper
 * places.  The private fields are not subject to locking, since when
 * the filesystem is running, it is guaranteed to be funnelled onto the
 * master processor.  It is, however, still subject to normal races, for
 * example, any operation that can sleep may need to provide its own
 * synchronization.
 *
 * The following additional synchronization requirements apply.
 * If a filesystem wishes to gain a reference on a vnode, it must use
 * one of the following interfaces:
 *	vget() -- if there is no guarantee of current references on the
 *		  vnode, and it could be invalid.  This call can sleep,
 *		  and if it returns a non-zero value, the vnode should
 *		  not be referenced again, as it may be gone.  This
 *		  interface takes an unlocked vnode as its argument.
 *	vget_nowait() -- similar to vget(), but will not sleep if the
 *		  vnode is busy (VXLOCK is set), but will return a
 *		  non-zero value immediately.  This interface should
 *		  be used carefully.  It takes the vnode locked.
 *      vget_cache() --
 *      vget_cache_nowait() --
 *                These two macros indicate that the vgetm call is
 *                made after a cache_lookup() call. Decrements the 
 *                count on the cache_lookup done indicator, which is
 *                used to determine if a vnode can be deallocated.
 *                All vnodes that were looked up using cache_lookup
 *                are returned back to the free_list.
 *	VREF() -- simply locks the vnode, increments its v_usecount, and
 *		  unlocks it.  This is used when existing references
 *		  indicate that that vnode is guaranteed to be valid.
 *
 * Notes on vnode recycling and circular calls:  
 *
 * When a vnode's last reference is released, in vrele(), the filesystem's 
 * vn_inactive() function is called.   Some filesystems may wish to
 * explicitly call vgone() on an inactive vnode.  Vgone(), which calls
 * vclean() to clean out the vnode(), can result in calling back into
 * the filesystem code, via its vn_close(), vn_inactive(), or vn_reclaim()
 * functions.  If the vnode is in the midst of vrele(), only the
 * vn_reclaim() function will be called, since the VINACTIVATING flag
 * will prevent what is essentially a circular call sequence.  It is
 * necessary to call the vn_reclaim() function to dissociate the vnode
 * from the filesystem-specific node in all cases.  Therefore, special
 * care must be taken by the vn_inactive(), vn_reclaim(), and vn_close()
 * functions to be sure that a circular calling sequence will not 
 * cause a deadlock, if, for example, the vn_reclaim() function requires
 * a lock held by the vn_inactive() function.
 * The UFS filesystem has examples of this type of behavior, since it
 * calls vgone() is several contexts.
 *
 * Another problem is that the interface, getnewvnode(), may result in
 * calling vgone(), which, if called on a node of the same filesystem
 * type, will result in calling back into the filesystem.  It is
 * expected that getnewvnode() will be called while holding few, if any
 * resources, and if so, the filesystem must be prepared to have its
 * vn_inactive(), vn_close(), and vn_reclaim() functions called in the
 * context of getnewvnode().
 *
 * Note about v_aux_lock. This general purpose sleep lock is supplied
 * for use by any kernel subsystem for its own exclusion needs (e.g.
 * between NFS server daemons). It is NOT to be used as an exclusion
 * mechanism between non-cooperating subsystems. *NO* lock semantics
 * should be assumed.
 */

/*
 * The vnode lock protects the contents of the vnode structure;
 * its only purpose is multiprocessor exclusion.  Long-term locking
 * is a privilege reserved for the filesystem-specific layers.
 */
udecl_simple_lock_info(extern,vnode_lockinfo)
#define	VN_LOCK(vp)		usimple_lock(&(vp)->v_lock)
#define	VN_UNLOCK(vp)		usimple_unlock(&(vp)->v_lock)
#define	VN_LOCK_TRY(vp)		usimple_lock_try(&(vp)->v_lock)
#define	VN_LOCK_INIT(vp)	usimple_lock_setup(&(vp)->v_lock,vnode_lockinfo)
#define	VN_LOCK_TERMINATE(vp)	usimple_lock_terminate(&(vp)->v_lock)
#define	VN_LOCK_HOLDER(vp)	SLOCK_HOLDER(&(vp)->v_lock)

/*
 * The vnode buffer lists lock protects both the clean and dirty
 * buffer lists in the vnode.
 */
udecl_simple_lock_info(extern,buflists_lockinfo)
#define	VN_BUFLISTS_LOCK(vp)	usimple_lock(&(vp)->v_buflists_lock)
#define	VN_BUFLISTS_UNLOCK(vp)	usimple_unlock(&(vp)->v_buflists_lock)
#define	VN_BUFLISTS_LOCK_INIT(vp) \
	usimple_lock_setup(&(vp)->v_buflists_lock, buflists_lockinfo)

/*
 * The vnode output lock protects the number of writes in progress and
 * the output flags.
 */
udecl_simple_lock_info(extern, vnode_output_lockinfo)
#define	VN_OUTPUT_LOCK(vp)	usimple_lock(&(vp)->v_output_lock)
#define	VN_OUTPUT_UNLOCK(vp)	usimple_unlock(&(vp)->v_output_lock)
#define	VN_OUTPUT_LOCK_INIT(vp) \
	 usimple_lock_setup(&(vp)->v_output_lock, vnode_output_lockinfo)

/*
 * The vnode auxiliary lock provides general purpose vnode exclusion.
 * *NO* lock semantics should be assumed.
 * This was implemented as a complex lock, but to reduce struct vnode
 * size, this has been redone as just a counter.  Only VN_WRITE_LOCK
 * and VN_WRITE_UNLOCK survive, which is fine, as that's all that's used!
 */
#define	VN_WRITE_LOCK(vp)						\
MACRO_BEGIN								\
	VN_LOCK(vp);							\
	if ((vp)->v_aux_lockers++) {					\
		assert_wait_mesg((vm_offset_t)&(vp)->v_aux_lockers,	\
				 FALSE, "vn_aux");			\
		VN_UNLOCK(vp);						\
		thread_block();						\
	} else								\
		VN_UNLOCK(vp);						\
MACRO_END

#define	VN_WRITE_UNLOCK(vp)						\
MACRO_BEGIN								\
	u_int wake;							\
									\
	VN_LOCK(vp);							\
	wake = --(vp)->v_aux_lockers;					\
	VN_UNLOCK(vp);							\
	if (wake)							\
		thread_wakeup_one((vm_offset_t)&(vp)->v_aux_lockers);	\
MACRO_END


#define	VN_AUX_LOCK_INIT(vp)  ; 


/*
 *  Macros to protect a vnode from deallocation when v_usecount is zero.
 */

udecl_simple_lock_data(extern, vn_dealloc_cache_lookup_ref)

#define	CACHE_LOOKUP_REF(vp)						\
MACRO_BEGIN								\
	usimple_lock(&vn_dealloc_cache_lookup_ref);			\
	(vp)->v_cache_lookup_refs++;					\
	usimple_unlock(&vn_dealloc_cache_lookup_ref);			\
MACRO_END

#define	CACHE_LOOKUP_RELE(vp)						\
MACRO_BEGIN								\
	usimple_lock(&vn_dealloc_cache_lookup_ref);			\
	(vp)->v_cache_lookup_refs--;					\
	usimple_unlock(&vn_dealloc_cache_lookup_ref);			\
MACRO_END


/*
 * public vnode manipulation functions
 */

enum vnuio_rw { VNUIO_READ, VNUIO_WRITE, VNUIO_READNESTED, VNUIO_WRITENESTED };


extern int vn_open __((struct nameidata *, int, int));			   /* open vnode */
extern int vn_rdwr __((enum vnuio_rw, struct vnode *, caddr_t, int,
                       off_t, enum uio_seg, int, struct ucred *, int *));  /* read or write vnode */
extern int vn_close __((struct vnode *, int, struct ucred *));             /* close vnode */
extern int getnewvnode __((enum vtagtype, struct vnodeops *,
                           struct vnode **));                              /* allocate a new vnode */
extern struct vnode *shadowvnode __((struct vnode *));                     /* get shadow vnode for block device */
extern int bdevvp __((dev_t, struct vnode **));                            /* allocate a new special dev vnode */
extern int makealias __((struct vnode *));                                 /* make special device aliases */
extern int makealias2 __((struct vnode *, u_long));                        /* make special device aliases flaged SA_OPENING */
extern int specalloc __((struct vnode *, dev_t));                          /* allocate specinfo structure */
extern int vgetm __((struct vnode *, int));                                /* get reference to a vnode */
extern void vrele __((struct vnode *));                                    /* release vnode */
extern int vgone __((struct vnode *, int, struct vnodeops *));             /* completely recycle vnode */
extern void clearalias __((struct vnode *, struct vnodeops *));            /* recycle vnode and all its aliases */
extern int vn_pathconf __((struct vnode *, int, long *)); 

/*
 * Args passed to vgone to modify behavior.
 *
 * Note that these flags are also passed to the VOP_RECLAIM
 * function associated with a vnode via vgone, therefore must be
 * unique wrt all flags passed to vn_reclaim (clearalias).
 * Currently, VX_REVOKE is only passed to vn_reclaim via clearalias.
 *
 * Revoke-type reclaims could (should?) be implemented as a distinct
 * VOP, instead of piggybacking reclaim.  This could be useful to 
 * generic (VFS-layer) forced unmount implementations.
 */
#define VX_NOSLEEP      0x0000
#define VX_SLEEP        0x0001
#define VX_INACTIVE     0x0002	/* vnode is not active (e.g. ref'd) */
#define VX_DOCLOSE      0x0004	/* vclean: close active files */
#define VX_CHKERRORS    0x0008	/* vgone() returns error and preserves
					   dirty data if cannot flush */
#define VX_REVOKE       0x0010	/* This is a revoke-type reclaim */
#define VX_CFS_RECOVERY 0x0020	/* Used when vgone()'ing inactive vnodes
				   with no dirty data as first step in
				   CFS recovery. */
#define VX_RECYCLING    0x0040	/* recycling vnode from getnewvnode() */

/*
 * Arg passed to wait_for_vxlock to indicate whether or not to set VXLOCK
 * Note: be aware that spec_vnops.c/clearalias() calls wait_for_vxlock().
 */
#define VX_NOLOCK       0
#define VX_LOCK         1

/*
 * Flags to various vnode functions.
 */
#define	SKIPSYSTEM	0x0001		/* vflush: skip VSYSTEM vnodes */
#define	FORCECLOSE	0x0002		/* vflush: force file closure */

/*
 * Macro for determining if a vnode has any dirty data.  This is used
 * in filesytem sync routines to avoid vget/vrele calls on the vnode,
 * preventing undesired (sync related) vnode freelist LRU updates. 
 * Allowing sync to vget/vrele clean, unreferenced vnodes effectively
 * thwarts the vnode deallocation logic.
 *
 * CAREFUL - dirty data is managed by the underlying filesystem.  Various
 * filesystem types manage data differently, and their dirty data cannot
 * be detected by a common mechanism such as this macro (slight misnomer).
 * This macro is for CFS only.
 */
#define VFS_DATACLEAN(vp)					\
	(							\
	  (							\
	    ((vp)->v_type != VREG) && (!(vp)->v_dirtyblkhd)	\
	  )							\
	  ||							\
	  (							\
	    ((vp)->v_type == VREG) &&				\
	    (!(vp)->v_object || 				\
	      (							\
		!(vp)->v_object->vu_dirtypl &&			\
		!(vp)->v_object->vu_dirtywpl			\
	      )							\
	    )							\
	  )							\
	)

/*
 * Synchronization notes:
 * Vgone and vgetm will return a 1 if the vnode had VXLOCK set, 0 if it
 * did not.  In the case of a vnode with VXLOCK set, neither routine will
 * successfully complete, and will wait for the lock to clear, depending
 * upon the arguments passed.
 *
 * Four flavors of vget (all return 0 if you get the reference):
 *
 * All 4 types are summarized in the table below:
 *
 *      cache  wait     X
 *      =================
 *	0      0      = 0  #define vget_nowait()  	vgetm(vp, X)
 *	0      1      = 1  #define vget()               vgetm(vp, X) wait
 *	1      0      = 2  #define vget_cache_nowait()  vgetm(vp, X)
 *	1      1      = 3  #define vget_cache()         vgetm(vp, X) wait
 *  
 *	vget(vp) -- sleep on VXLOCK; always gets the reference.
 *	vget_nowait(vp) -- do not sleep on VXLOCK; return 1 immediately if set.
 */
#define vget(vp)	vgetm(vp, 1)	/* get reference, sleep on VXLOCK */
#define vget_nowait(vp)	vgetm(vp, 0)	/* if VXLOCK set, return 1, no ref. */
/*
 * The cache version of the above calls are called after a cache_lookup()
 * call. This helps during vnode deallocation to determine if there are
 * any pending references to a vnode. If for some reason, vget_cache*() 
 * cannot be called after cache_lookup(), please call vget_abort()
 */
#define vget_cache(vp)  vgetm(vp, 3)    /* vget after cache_lookup() call */
#define vget_cache_nowait(vp)  vgetm(vp, 2) /* vget_nowait after cache_lookup*/

/*
 * Inline references for non-debug kernels
 */
#if	MACH_ASSERT
extern void vref __((struct vnode *));			/* increase reference to a vnode */
extern void vattr_null __((struct vattr *));		/* set attributes to null */
#define	VREF(vp)	vref(vp)	/* increase reference to a vnode */
#define VATTR_NULL(vap) vattr_null(vap) /* initialize a vattr structure */

#else	/* MACH_ASSERT */

/*
 * The initial transition of a vnode's v_usecount from 0 => 1
 * MUST be handled by the vget* macros (aka vgetm).  Otherwise,
 * the vnode will not be removed from the vnode freelist, and
 * vrele processing will panic.  The v_usecount == 0 check here will
 * catch offenders upfront.
 */
#define VREF(vp)						\
MACRO_BEGIN							\
	VN_LOCK(vp);						\
	if ((vp)->v_usecount++ == 0)				\
		panic("VREF: Invalid v_usecount transition");	\
	VN_UNLOCK(vp);						\
MACRO_END

#define VATTR_NULL(vap) *(vap) = va_null /* initialize a vattr structure */
#define vattr_null(vap) VATTR_NULL(vap);

#endif	/* MACH_ASSERT */

#define	VUNREF(vp)	vrele(vp)	 /* decrease reference to a vnode */
#define NULLVP	((struct vnode *)0)


/*
 * Global vnode data.
 */
extern	struct vnode *rootdir;		/* root (i.e. "/") vnode */

extern	int nvnode;			/* number of slots in the table */
extern	struct vattr va_null;		/* predefined null vattr structure */

#endif	/* _KERNEL */

_END_CPLUSPLUS

#endif	/* _SYS_VNODE_H_ */

