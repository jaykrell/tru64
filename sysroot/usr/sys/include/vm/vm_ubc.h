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
 * 
 * 
 */
/*
 * @(#)$RCSfile: vm_ubc.h,v $ $Revision: 1.1.86.9 $ (DEC) $Date: 2002/07/10 21:43:43 $
 */

#ifndef	_VM_VM_UBC_H_
#define	_VM_VM_UBC_H_

#include <vm/vm_page.h>
#include <vm/vm_object.h>

/*
 * File system private data.
 */
union vfs_private {
	struct vnode    *vp;	/* backing vnode */
        struct bfAccess *ap;    /* access structure for AdvFS files */
};
typedef union vfs_private *vfs_private_t;

/*
 * This object describes ubc pages.
 */
typedef struct vm_ubc_object	*vm_ubc_object_t;

struct vm_ubc_object {
	struct vm_object	vu_object;	/* Object common part */
	struct vfs_ubcops	*vu_ops;	/* VFS operations */
	union vfs_private	vu_vfp;		/* VFS private pointer */
	struct vm_page		*vu_cleanpl;	/* Clean page list */
	struct vm_page		*vu_cleanwpl;	/* Clean wired page list */
	struct vm_page		*vu_dirtywpl;	/* Dirty wired page list */
	int			vu_wirecnt;	/* Wired pages */
	int			vu_nsequential;	/* Number of contig lastpage */
	vm_offset_t		vu_loffset;	/* Last offset allocated */
	unsigned int		vu_stamp;	/* Allocation stamp */
	unsigned int		vu_txtref;	/* text references */
	unsigned int		vu_flags;	/* flags */
	unsigned int		vu_reserved0;	/* */
	simple_lock_data_t	vu_seglock;	/* Segment list lock */
	struct vm_seg		*vu_seglist;	/* Segment list */
	void			*vu_pshared;	/* state for pshared objects */
	unsigned int		vu_dirtypages;	/* dirty page count */
	unsigned int		vu_putpages;	/* putpage called count */
						/* ++ before call -- after */
	unsigned int		*vu_pgs_permad;	/* ptr to array of per mad pg cnts */
	vm_ubc_object_t		vu_backobject;	/* backing obj for this obj */
};

#define	VM_UBC_OBJECT_NULL	(vm_ubc_object_t)0
#define	vu_dirtypl		vu_object.ob_memq
#define vu_orefcnt		vu_object.ob_ref_count
#define vu_npages		vu_object.ob_resident_pages
#define vu_noutput		vu_object.ob_res_count
#define vu_oflags		vu_object.ob_flags
#define vu_bigpg		vu_object.ob_bigpg
#define vu_vp			vu_vfp.vp
#define vu_ap                   vu_vfp.ap

/*
 * UBC object specific flags
 */
#define UBC_REPL	 0x01	/* replicate pages */
#define UBC_NOREPL	 0x02	/* do not replicate pages */
#define UBC_NOFLUSH	 0x04	/* page cannot be flushed by UBC */
#define UBC_PUTPAGE_WAIT 0x08	/* waiting on putpages count is zero */
#define UBC_TXTREF_WAIT	 0x10	/* waiting for vu_txtref to go to zero */

/*
 * Forward declarations of data structures for prototypes
 */
struct	ucred;
struct	vm_policy;

/* UBC to VFS callbacks */
struct vfs_ubcops {
	int	(*vfs_refer)(vm_ubc_object_t);
	int	(*vfs_release)(vm_ubc_object_t);
	int	(*vfs_getpage)(vm_ubc_object_t, vm_offset_t, vm_size_t,
			       vm_prot_t *, struct vm_page **, int,
			       struct vm_policy *, int, struct ucred *);
	int	(*vfs_putpage)(vm_ubc_object_t, struct vm_page **, int, int,
			       struct ucred *);
	int	(*vfs_write_check)(vm_ubc_object_t, struct vm_page *);
	int	(*vfs_objtovp)(vm_ubc_object_t, struct vnode **);
	int	(*vfs_setpgstamp)(vm_page_t, unsigned int);
        int     (*vfs_fs_cleanup)(vm_offset_t opfs);
        int     (*vfs_fs_replicate) (vm_page_t pp);
	int	(*vfs_iothreshold)(vm_ubc_object_t, unsigned int);
        int     (*vfs_fs_metadata_put) (vm_ubc_object_t, int);
};

typedef struct vfs_ubcops *vfs_ubcops_t;

#define _FSOP_(f,obj,arg,r)			\
MACRO_BEGIN					\
	if (!((obj)->vu_oflags & OB_FUNNEL)) {	\
		(r) = (*((obj)->vu_ops->f))arg;	\
	} else {				\
		unix_master();			\
		(r) = (*((obj)->vu_ops->f))arg;	\
		unix_release();			\
	}					\
MACRO_END

#define FSOP_REF(obj)	(*((obj)->vu_ops->vfs_refer))(obj)

#define FSOP_RELE(obj)	(*((obj)->vu_ops->vfs_release))(obj)

#define FSOP_GETPAGE(obj, off, l, pt, pl, n, vp, rw, cr, r)	\
	_FSOP_(vfs_getpage,obj,(obj,off,l,pt,pl,n,vp,rw,cr),r)

#define FSOP_PUTPAGE(obj, pl, n, f, cr, r)	\
	_FSOP_(vfs_putpage,obj,(obj,pl,n,f,cr),r)

#define FSOP_WRITE_CHECK(obj, pp)	\
        (((obj)->vu_flags & UBC_NOFLUSH) ?  0 : 1)

#define FSOP_OBJTOVP(obj, vpp)	(*((obj)->vu_ops->vfs_objtovp))((obj),(vpp))

#define FSOP_SETPGSTAMP(pp, tick)					\
	(*(((vm_ubc_object_t)(pp)->pg_object)->vu_ops->vfs_setpgstamp))	\
		((pp),(tick))

/* Filesystem cleanup of any memory stored in the page private field. */
#define FSOP_FS_CLEANUP(obj, opfs) \
        if (*(((vm_ubc_object_t)(obj))->vu_ops->vfs_fs_cleanup)) \
            (*(((vm_ubc_object_t)(obj))->vu_ops->vfs_fs_cleanup))((opfs))

#define FSOP_FS_REPLICATE(obj, opfs) \
        (*(((vm_ubc_object_t)(obj))->vu_ops->vfs_fs_replicate))? \
        (*(((vm_ubc_object_t)(obj))->vu_ops->vfs_fs_replicate))((opfs)):\
        (0)

/*
 * Check underlying fs logic for device threshold.
 * 1 : at or above threshold.  0 : below threshold, or no support for throttle.
 */
#define FSOP_IOTHRESHOLD(obj, flag) \
	((*((obj)->vu_ops->vfs_iothreshold)) ? \
		(*((obj)->vu_ops->vfs_iothreshold))((obj),(flag)) : 0)
#define IO_THROTTLE	1
#define IO_VM		2

#define FSOP_FS_METADATA_PUT(obj, pages) \
        if (*(((vm_ubc_object_t)(obj))->vu_ops->vfs_fs_metadata_put)) \
            (*(((vm_ubc_object_t)(obj))->vu_ops->vfs_fs_metadata_put))( \
		(obj), (pages))

#define UBC_OBJECT_WAIT(obj)    					\
MACRO_BEGIN								\
	vm_object_lock(obj);						\
	while ((obj)->vu_noutput) {					\
		(obj)->vu_oflags |= OB_UBCWAIT;				\
		assert_wait_mesg((vm_offset_t)&(obj)->vu_noutput,	\
				 FALSE, "ubcwait");			\
		vm_object_unlock(obj);					\
		thread_block();						\
		vm_object_lock(obj);					\
	}								\
	vm_object_unlock(obj);						\
MACRO_END

#define UBC_OBJECT_WAKEUP(obj)    					\
MACRO_BEGIN								\
	vm_object_lock(obj);						\
	assert((obj)->vu_noutput > 0);					\
	(obj)->vu_noutput--;						\
	if (!(obj)->vu_noutput && ((obj)->vu_oflags & OB_UBCWAIT)) {	\
		(obj)->vu_oflags &= ~OB_UBCWAIT;			\
		vm_object_unlock(obj);					\
		thread_wakeup((vm_offset_t)&(obj)->vu_noutput);		\
	} else								\
		vm_object_unlock(obj);					\
MACRO_END

#define UBC_OBJECT_PUTPAGE_WAKEUP(obj)  				\
MACRO_BEGIN								\
	assert((obj)->vu_putpages > 0);					\
	(obj)->vu_putpages--;						\
	if (!(obj)->vu_putpages && ((obj)->vu_flags & UBC_PUTPAGE_WAIT)) {\
		(obj)->vu_flags &= ~UBC_PUTPAGE_WAIT;			\
		thread_wakeup((vm_offset_t)&(obj)->vu_putpages);	\
	} 								\
MACRO_END

#define UBC_OBJECT_PREVENT_FLUSH(obj)                                   \
MACRO_BEGIN                                                             \
        vm_object_lock(obj);                                            \
        (obj)->vu_flags |= UBC_NOFLUSH;                                 \
        vm_object_unlock(obj);                                          \
MACRO_END

#define UBC_OBJECT_ALLOW_FLUSH(obj)                                     \
MACRO_BEGIN                                                             \
        vm_object_lock(obj);                                            \
        (obj)->vu_flags &= ~UBC_NOFLUSH;                                \
        vm_object_unlock(obj);                                          \
MACRO_END

#ifdef	KERNEL
#include <machine/vm_ubc.h>

#ifndef	ubc_load
extern int ubc_load(struct vm_page *, vm_offset_t, vm_size_t);
#endif

#ifndef	ubc_unload
extern int ubc_unload(struct vm_page *, vm_offset_t, vm_size_t);
#endif

#ifndef	ubc_kmem_alloc
extern int ubc_kmem_alloc(struct vm_page *);
#endif

#ifndef ubc_kmem_free
extern int ubc_kmem_free(struct vm_page *);
#endif

#ifndef ubc_kmem_cache
extern boolean_t ubc_kmem_cache(struct vm_page *);
#endif

#ifndef ubc_page_zero
extern void ubc_page_zero(struct vm_page *, vm_offset_t, vm_size_t);
#endif

/*
 * ubc_kluster operation flags for hold condition
 */

#define	UBC_HNONE	0x0			/* Don't hold pages */
#define	UBC_HBCP	0x1			/* Hold before center page */
#define	UBC_HACP	0x2			/* Hold after center page */
#define	UBC_HALL	(UBC_HBCP|UBC_HACP)	/* Hold all pages */

#define	ubc_page_wait(PP)						\
MACRO_BEGIN								\
	vm_object_t	obj;						\
	vm_object_lock(obj = (PP)->pg_object);				\
	while ((PP)->pg_busy) {						\
		(PP)->pg_wait = 1;					\
		assert_wait_mesg((vm_offset_t)(PP), FALSE, "pg_wait");	\
		vm_object_unlock(obj);					\
		thread_block();						\
		vm_object_lock(obj);					\
	}								\
	vm_object_unlock(obj);						\
MACRO_END

#define	ubc_page_hold(PP) {				\
	vm_object_lock((PP)->pg_object);		\
	VM_PAGE_HOLD_INCR(PP, FALSE);			\
	vm_object_unlock((PP)->pg_object);		\
}

/*
 * Prototypes
 */
struct ubc_control;
struct memory_affinity_domain;
struct vm_map_entry;

extern struct vm_page
	*ubc_dirty_kluster(vm_ubc_object_t, struct vm_page *,
			   vm_offset_t, vm_size_t, int, boolean_t, int *),
	*ubc_kluster(vm_ubc_object_t, struct vm_page *,
			     vm_offset_t, vm_size_t, int, int, int *),
	*ubc_written_kluster(vm_ubc_object_t, struct vm_page *, int, int);
extern vm_ubc_object_t
	ubc_object_allocate(vfs_private_t, vfs_ubcops_t, int),
	get_ubc_bobject(struct vm_map_entry *);
extern struct buf
	*ubc_bufget(void);
extern struct buf
	*ubc_bufalloc(struct vm_page *, int, int, int, int);
extern void
	ubc_buffree(struct buf *),
	ubc_page_release(struct vm_page *, int),
	ubc_object_free(vm_ubc_object_t),
	ubc_page_lookup(vm_ubc_object_t, vm_offset_t, struct vm_page **),
	ubc_page_dirty(struct vm_page *, int),
	ubc_count_dirty(vm_ubc_object_t, vm_offset_t *, vm_size_t *),
	ubc_page_busy(struct vm_page *, int, boolean_t),
	u_vp_text_ref(vm_ubc_object_t),
	u_vp_text_rele(vm_ubc_object_t),
	ubc_init(void),
	ubc_domain_init(struct memory_affinity_domain *);
extern int		
	ubc_sync_iodone(struct buf *),
	ubc_invalidate(vm_ubc_object_t, vm_offset_t, vm_size_t, int),
	ubc_lookup(vm_ubc_object_t, vm_offset_t, vm_size_t, vm_size_t,
			struct vm_page **, int *, struct vm_policy *),
	ubc_page_alloc(vm_ubc_object_t, vm_offset_t, vm_size_t, vm_size_t,
			struct vm_page **, int *, struct vm_policy *),
	ubc_check_mod(vm_ubc_object_t),
	ubc_msync(vm_ubc_object_t, vm_offset_t, vm_size_t, int),
	ubc_flush_dirty(vm_ubc_object_t, int),
	ubc_flush_dirty_age(vm_ubc_object_t, int, u_int),
	ubc_free_memory(struct vm_page *),
	ubc_wire(struct vm_page **, int, int),
	ubc_unwire(struct vm_page **, int, boolean_t, boolean_t),
	ubc_get_bigpg_size(vm_ubc_object_t, vm_offset_t, int),
	ubc_page_stealer(struct ubc_control *, int, vm_ubc_object_t);

extern boolean_t
	ubc_incore(vm_ubc_object_t, vm_offset_t, vm_size_t);
 
extern int
	umc_page_stealer(struct ubc_control *, int),
 	umc_lru_count;
extern void
	ubc_backobject_add(vm_ubc_object_t, vm_ubc_object_t),
	ubc_backobject_remove(vm_ubc_object_t),
	umc_page_release(vm_page_t),
	ubc_page_wait_locked(vm_page_t, vm_ubc_object_t, boolean_t),
	ubc_bigpg_downgrade(vm_ubc_object_t, vm_offset_t, int);
extern kern_return_t
	ubc_breakup_all(vm_ubc_object_t, vm_offset_t, int);


/* prototype, flags and return values for ubc_fs_page_get() */

extern int ubc_fs_page_get(struct vm_page **, struct vm_ubc_object *,
                           unsigned long, void *, unsigned long);

/* input flags
 *   note: READHOLD and WRITEHOLD are defined this way for consistency
 *         with B_READ and B_WRITE because on a ubc_lookup the B_READ flag
 *         determines which ubc reference counter is incremented and on
 *         ubc_page_release the same flag must be passed to ensure a
 *         matching decrement of that reference counter.
 */
#define UBC_GET_UBC_FLAGS  0x0000ffff  /* reserved for ubc definition */
#define UBC_GET_RES_FLAGS  0xffff0000  /* spare reserved wrapper */

#define UBC_GET_WRITE            0x00  /* must match B_WRITE */
#define UBC_GET_READ             0x01  /* must match B_READ */
#define UBC_GET_HOLD             0x02
#define UBC_GET_READHOLD         (UBC_GET_HOLD | UBC_GET_READ)   /* == 0x03 */
#define UBC_GET_WRITEHOLD        (UBC_GET_HOLD | UBC_GET_WRITE)  /* == 0x02 */
#define UBC_GET_BUSY             0x04
#define UBC_GET_KEEPDIRTY        0x08
#define UBC_GET_HAVEHOLD         0x10
#define UBC_GET_MAKECLEAN        0x20
/* return values */
#define UBC_GET_SUCCESS          0
#define UBC_GET_NOT_CACHED       0x01
#define UBC_GET_WAIT_EXCHANGE    0x02
#define UBC_GET_IS_BUSY          0x04
#define UBC_GET_NOT_DIRTY        0x08
#define UBC_GET_VM_PROTECT       0x10

extern void ubc_fs_page_wait(struct vm_page *, simple_lock_t);

#endif	/* KERNEL */
#endif	/* !_VM_VM_UBC_H_ */

