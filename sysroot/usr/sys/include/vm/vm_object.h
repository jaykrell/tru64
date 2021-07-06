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
 *	@(#)$RCSfile: vm_object.h,v $ $Revision: 4.2.77.9 $ (DEC) $Date: 2002/07/10 21:39:52 $
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
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */
/*
 *	File:	vm_object.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Copyright (C) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Virtual memory object module definitions.
 *
 */
#ifndef	_VM_VM_OBJECT_H_
#define	_VM_VM_OBJECT_H_
#include <sys/types.h>
#include <mach/kern_return.h>
#include <mach/boolean.h>
#include <mach/machine/vm_types.h>
#include <kern/lock.h>

struct bigpage_info;

/*
 *	The common part of all VM objects
 *
 */
struct vm_object {
	struct bigpage_info	*ob_bigpg;	/* Big page data for obj */
	simple_lock_data_t	ob_lock;	/* lock to protect common */
	struct vm_object_ops	*ob_ops;	/* Object Operations */
	struct vm_object	*ob_aux_obj;	/* Auxiliary object */
	int			ob_ref_count;	/* Number of references */
	int 			ob_res_count;	/* Object resident count */
	vm_size_t		ob_size;	/* Size of object */
	int 			ob_resident_pages;/* Page in ob_memq list */
	ushort			ob_flags;	/* Flags */
	ushort			ob_type;	/* Object type */
	struct vm_policy	*ob_policy;	/* NUMA policy data */
	struct vm_page		*ob_memq;	/* Resident memory */
};

typedef struct vm_object	*vm_object_t;
#define VM_OBJECT_NULL		((vm_object_t) 0)

/*
 * Big Pages Data Structures
 */

/*
 * The bigpage_info structure contains primarily the gh_layout array, each 
 * element of which represents 64 KB of the object (or whatever size a gh 
 * value of 1 gets you). The "num_elem" field tells how many elements are 
 * in the array.
 *
 * The value in an array element is a gh value. If the value is a negative 
 * number, it means the big page represented by that element (and any 
 * subsequent elements if the abs(gh) is > 1) is LOCKED.
 *
 * Normally this array is unique to an object and not shared with another
 * object.  However, for COW cases this is not true, therefore there is a
 * reference count field.
 *
 * The gh_layout array is computed based on a specific starting VA for the
 * object. That VA is saved in the structure in case there is another
 * mapper of this object which has a different starting VA.
 */

typedef struct bigpage_info {
	simple_lock_data_t	gh_lock;	/* lock for this structure */
	int			gh_refcnt;	/* # of refs on this struct */
	int			gh_users;	/* # of users of gh_layout */
	int			gh_flags;	/* wait flags for gh_layout */
	int			num_elem;	/* size of gh_layout array */
	int			num_bigp;	/* # elem specifying bigpgs */
	vm_offset_t		ref_va;		/* start va for array */
	vm_offset_t		min_size;	/* min size obj must be */
	unsigned char	       *gh_layout;	/* pgsize to get (gh units) */
} bigpage_info_t;

/*
 * The following are bit values that the bigpage_info "gh_flags" field
 * can have. If they are set, it means someone is waiting on the
 * associated wait channel.
 */
#define	GH_X_WANTED	0x01	/* waiting on eXclusive access to gh array */
#define	GH_X_USER	0x02	/* has eXclusive access to gh array */
#define GH_WAITERS	0x04	/* waiting on shared access to gh array */

/*
 * A gh_layout element is a character (8 bits).  The top two bits 
 * indicate whether the element is locked and whether someone is
 * waiting for access to the locked element.
 */
#define GH_LOCKED		0x80
#define GH_WAIT			0x40
#define GH_LAYOUT_MASK		(GH_LOCKED | GH_WAIT)

/*
 * The following macro locks the gh_layout array at index I. If the
 * array is locked, this thread will block waiting for it to become
 * available.
 */
#define GH_LAYOUT_LOCK(BPI,I) 						\
MACRO_BEGIN								\
    while (TRUE) {							\
        simple_lock(&(BPI)->gh_lock);					\
	while ((BPI)->gh_flags & (GH_X_WANTED | GH_X_USER)) {		\
	    (BPI)->gh_flags |= GH_WAITERS;				\
	    assert_wait_mesg((vm_offset_t)&(BPI)->gh_users, FALSE,	\
		  	     "gh_user");				\
  	    simple_unlock(&(BPI)->gh_lock);				\
	    thread_block();						\
	    simple_lock(&(BPI)->gh_lock);				\
        }								\
        if ((BPI)->gh_layout[I] & GH_LOCKED) {				\
            (BPI)->gh_layout[I] |= GH_WAIT;				\
	    assert_wait_mesg((vm_offset_t)&(BPI)->gh_layout[I], FALSE,	\
			     "gh_wait");				\
	    simple_unlock(&(BPI)->gh_lock);				\
            thread_block();						\
        }								\
        else {								\
            (BPI)->gh_layout[I] |= GH_LOCKED;				\
	    (BPI)->gh_users ++;						\
            simple_unlock(&(BPI)->gh_lock);				\
	    break;							\
	}								\
    }									\
MACRO_END

/*
 * The following macro unlocks the gh_layout array at index I. If 
 * there are any waiters, they are awakened.
 */
#define GH_LAYOUT_UNLOCK(BPI,I) 					\
MACRO_BEGIN								\
    boolean_t _waiters;							\
    boolean_t _x_waiters = FALSE;					\
									\
    simple_lock(&(BPI)->gh_lock);					\
    _waiters = (BPI)->gh_layout[I] & GH_WAIT;				\
    (BPI)->gh_layout[I] &= ~GH_LAYOUT_MASK;				\
    (BPI)->gh_users --;							\
    if (((BPI)->gh_users == 0) && ((BPI)->gh_flags & GH_X_WANTED)) {	\
        (BPI)->gh_flags &= ~GH_X_WANTED;				\
	_x_waiters = TRUE;						\
    }									\
    simple_unlock(&(BPI)->gh_lock);					\
    if (_x_waiters)							\
	thread_wakeup((vm_offset_t)&(BPI)->gh_flags);			\
    if (_waiters)							\
	thread_wakeup((vm_offset_t)&(BPI)->gh_layout[I]);		\
MACRO_END

/*
 * The following macro returns the index in the gh_layout array
 * corresponding to the object offset passed in.
 */
#define OBJOFF_TO_LAYOUT_NDX(BPI,OFF)					\
	((((BPI)->ref_va & BIGPG_MINMASK) + BASE_PGALIGN(OFF)) /	\
	 BIGPG_MINSIZE)

/*
 * The following macro is passed an offset into an object ("OFF"),
 * along with a pointer to the object ("OBJ").  A page size ("GH")
 * which is supplied is used to locate the start of a page of that
 * size containing the specified offset.
 *
 * The offset ("BIGSTART") corresponding to the start of that bigpage
 * is returned.  
 */
#define GET_BIGPG_START(OBJ,OFF,GH,BIGSTART)				\
MACRO_BEGIN								\
        bigpage_info_t *_bpi = ((vm_object_t)(OBJ))->ob_bigpg;		\
        if (_bpi)							\
		(BIGSTART) = ((_bpi->ref_va + BASE_PGALIGN(OFF)) &	\
			      ~bigpg_data[GH].mask) - _bpi->ref_va;	\
        else								\
		(BIGSTART) = BASE_PGALIGN(OFF);				\
MACRO_END

/*
 * Granularity Hints
 */

#define GH_UNALLOCATED 0
#define GH_ALLOCATED 1
#define GH_ALLOCATION_IN_PROGRESS 2
#define GH_FAILED 3
#define GH_RW	0
#define GH_R	1

/* mapping state */

struct l2ptes {
	void *ptes[2];
};

struct vm_granhint {
	simple_lock_data_t	vg_mapping_lock;
	vm_offset_t		vg_phys_buffs;
	struct l2ptes		*vg_ptes;
	u_long			vg_size;
	u_long			vg_phys_mem_state;
	u_long			vg_mapping_l3_shared;
	u_long			vg_mapping_waiters;
	long			vg_waiters;
	u_long			vg_att_warning;
};

struct vm_granhint_stats {
	u_long total_mappers;
	u_long shared_mappers;
	u_long unshared_mappers;
	u_long total_unmappers;
	u_long shared_unmappers;
	u_long unshared_unmappers;
	u_long unaligned_mappers;
	u_long access_violations;
	u_long unaligned_size_requests;
	u_long unaligned_attachers;
	u_long wired_bypass;
	u_long wired_returns;
};

#ifdef	GH_STATS
extern simple_lock_data_t gh_stats_lock;

#define INC_GH_STATS(FLD)                \
          simple_lock(&gh_stats_lock);     \
          gh_stats./**/FLD/**/++;         \
          simple_unlock(&gh_stats_lock);
#else
#define INC_GH_STATS(FLD)
#endif

#define GH_SEG_SIZE	0x800000
#define LARGE_PAGE_SIZE	0x400000
#define MED_PAGE_SIZE	0x80000
#define SMALL_PAGE_SIZE	0x10000
#define GH_ALIGNED_8MEG(a) (a == (a  & ~(GH_SEG_SIZE - 1)))
#define GH_ALIGNED_4MEG(a) (a == (a  & ~(LARGE_PAGE_SIZE - 1)))


/*
 * Flags field of object
 */

#define	OB_SWAPON	    0x0001	/* Object swapping enabled */
#define	OB_SWAP		    0x0002	/* Object is being swapped */
#define	OB_SWAPWAIT	    0x0004	/* Waiting for swap to complete */
#define	OB_CHANGE	    0x0008	/* Object change taking place */
#define	OB_CHANGEWAIT	    0x0010	/* Waiting for change to complete */
#define	OB_SEMWAIT	    0x0020	/* Semaphore wait */
#define	OB_SEGALLOC	    0x0040	/* A segment is being allocated */
#define	OB_SEGWAIT	    0x0080	/* Waiting for seg alloc to complete */
#define OB_DO_NOT_COALESCE  0x0100      /* Don't coalesce this object */
#define	OB_UBCWAIT	    0x0200	/* Waiting write completion in UBC */
#define OB_RM_EXISTING	    0x0400	/* RM existing object */
#define OB_GRAN_HINT 	    0x0800	/* Granularity hint object */
					/* unused bits */
#define OB_IOERROR	    0x1000	/* If an I/O error occured
					 * during async flush. */
#define OB_BIGPAGES	    0x2000	/* Big pages can be used for object */
#define OB_NOBIGPAGES	    0x4000	/* Object cannout use big pages */
#define	OB_FUNNEL	    0x8000	/* operations are funneled */

/*
 * Object address plus this offset for wakeup address
 */

#define	OB_WSWAP	0x0
#define	OB_WCHANGE	0x1
#define	OB_WSEM		0x2

#define	vm_object_wait(OBJ,WHY) {					\
	while (((vm_object_t)(OBJ))->ob_flags & OB_##WHY) {		\
		assert_wait_mesg(vm_object_sleep_addr(OBJ,WHY),		\
				 FALSE, "objwait");			\
		((vm_object_t)(OBJ))->ob_flags |= OB_##WHY##WAIT;	\
		vm_object_unlock((vm_object_t)(OBJ));			\
		thread_block();						\
		vm_object_lock((vm_object_t)(OBJ));			\
	}								\
}

#define	vm_object_assert_wait(OBJ,WHY,INTERRUPT) {			\
	assert_wait_mesg(vm_object_sleep_addr(OBJ,WHY), INTERRUPT, "objwait");\
	((vm_object_t)(OBJ))->ob_flags |= OB_##WHY##WAIT;		\
}

#define	vm_object_sleep_addr(OBJ,WHY)					\
	((vm_offset_t)(OBJ) + OB_W##WHY)

#define	vm_object_wakeup(OBJ,WHY)					\
	if (((vm_object_t)(OBJ))->ob_flags & OB_##WHY##WAIT) {	\
		thread_wakeup(vm_object_sleep_addr(OBJ, WHY));		\
		((vm_object_t) (OBJ))->ob_flags ^= OB_##WHY##WAIT;	\
	}

/*
 * Object control operations used for control functions.
 */

typedef enum {
	VMOC_NOOP, 			/* No operation */
	VMOC_MSYNC,			/* Sync memory cache with backstore */
	VMOC_PAGELOCK,			/* Lock the page */
	VMOC_PAGEUNLOCK,		/* Unlock the page */
	VMOC_FREE			/* Free the pages */
	} vm_ocontrol_t;

/*
 * Object page control operations
 */

#define VMOP_WRITE	0x00		/* Page was faulted with VM_PROT_WRITE*/
#define	VMOP_RELEASE	0x01		/* Release a hold on the page */
#define	VMOP_LOCK	0x02		/* Lock the page */
#define	VMOP_UNLOCK	0x04		/* Unlock the page */
#define VMOP_READ	0x08		/* Page was faulted with VM_PROT_READ */

/*
 * For prototypes.
 */
struct vm_policy;

/*
 * Object operations called by map map entry fault handles when there
 * is a backing object.  Without a backing object, the handle should 
 * know how to call the call the object management functions explictly.
 * To avoid polluting the kernel with numerous common operations handles
 * when object(s) don't require a handle or any special action, the vm_object.c
 * module exports routines with the naming convention:
 *
 *	vm_ops_##name##def
 */
struct vm_object_ops {
	boolean_t	(*ops_lock_try)(vm_object_t, struct vm_page *);
	void		(*ops_unlock)(vm_object_t, struct vm_page *);
	void		(*ops_reference)(vm_object_t);
	void		(*ops_deallocate)(vm_object_t);
	int		(*ops_pagein)(vm_object_t, vm_offset_t, vm_size_t,
				struct vm_policy *,
				struct vm_page **, int, vm_prot_t *);
	int		(*ops_pageout)(vm_object_t, struct vm_page *,
				vm_size_t);
	int		(*ops_swap)(vm_object_t, int *);
	int 		(*ops_control)(vm_object_t, vm_offset_t, int,
				vm_ocontrol_t, int);
	int		(*ops_pagectl)(vm_object_t, struct vm_page **,
				int, int);
	kern_return_t	(*ops_pagesteal)(vm_object_t, struct vm_page *);
	int		(*ops_pagewrite)(vm_object_t, struct vm_page *);
};

/*
 * Type casts to make compiler happy for place holder functions.
 */
#define CAST_LOCK_TRY	(boolean_t (*)(vm_object_t, struct vm_page *))
#define CAST_UNLOCK	(void (*)(vm_object_t, struct vm_page *))
#define CAST_REFERENCE	(void (*)(vm_object_t))
#define CAST_DEALLOCATE	(void (*)(vm_object_t))
#define CAST_PAGEIN	(int (*)(vm_object_t, vm_offset_t, vm_size_t,	\
			struct vm_policy *, struct vm_page **, int,	\
			vm_prot_t *))
#define CAST_PAGEOUT	(int (*)(vm_object_t, struct vm_page *, vm_size_t))
#define CAST_SWAP	(int (*)(vm_object_t, int *))
#define CAST_CONTROL	(int (*)(vm_object_t, vm_offset_t, int,		\
			vm_ocontrol_t, int))
#define CAST_PAGECTL	(int (*)(vm_object_t, struct vm_page **,	\
			int, int))
#define CAST_PAGESTEAL	(int (*)(vm_object_t, struct vm_page *))
#define CAST_PAGEWRITE	(int (*)(vm_object_t, struct vm_page *))

#define OOP_PAGEWRITE(OBJ, PP)						\
	(*((vm_object_t)(OBJ))->ob_ops->ops_pagewrite)(OBJ, PP)

#define	OOP_LOCK_TRY(OBJ, PP)						\
	(*((vm_object_t)(OBJ))->ob_ops->ops_lock_try)(OBJ, PP)

#define OOP_UNLOCK(OBJ, PP)						\
	(*((vm_object_t)(OBJ))->ob_ops->ops_unlock)(OBJ, PP)

#define	OOP_REFERENCE(OBJ)						\
	(*((vm_object_t)(OBJ))->ob_ops->ops_reference)(OBJ)

#define OOP_DEALLOCATE(OBJ)						\
	(*((vm_object_t)(OBJ))->ob_ops->ops_deallocate)(OBJ)

#define	OOP_PAGEIN(OBJ, OFFSET, SIZE, VMP, PGLIST, PSIZE, PROT)		\
	(*((vm_object_t)(OBJ))->ob_ops->ops_pagein)			\
	(OBJ, OFFSET, SIZE, VMP, PGLIST, PSIZE, PROT)

#define OOP_PAGEOUT(OBJ, PP, SIZE)					\
	(*((vm_object_t)(OBJ))->ob_ops->ops_pageout)(OBJ, PP, SIZE)

#define	OOP_SWAP(OBJ,PAGES)						\
	(*((vm_object_t)(OBJ))->ob_ops->ops_swap)(OBJ, PAGES)

#define	OOP_CONTROL(OBJ, OFFSET, SIZE, CONTROL, FLAG)			\
	(*((vm_object_t)(OBJ))->ob_ops->ops_control)			\
		(OBJ, OFFSET, SIZE, CONTROL, FLAG)
	
#define OOP_PAGECTL(OBJ, PLIST, PLS, FLAGS)				\
	(*((vm_object_t)(OBJ))->ob_ops->ops_pagectl)			\
		(OBJ, PLIST, PLS, FLAGS)

#define OOP_PAGESTEAL(OBJ, PP)						\
	(*((vm_object_t)(OBJ))->ob_ops->ops_pagesteal)(OBJ, PP)	

#define OOP_PAGEWRITE(OBJ, PP)						\
	(*((vm_object_t)(OBJ))->ob_ops->ops_pagewrite)(OBJ, PP)

/*
 * A small amount of informationn is exported to the module
 * vm_object.c by each object type.  The is done thru an
 * object configuration structure.
 */

struct vm_object_config {
						/* 
						 * object private allocation 
						 * this is optional
						 */
	kern_return_t		(*oc_allocate)(vm_object_t, caddr_t);
						/* object termination 
						 * this is optional
						 * ob_ref_count == 1
						 * the termination handle
						 * does the actual free of
						 * the object structure.
						 */
	void			(*oc_terminate)(vm_object_t);
	vm_size_t		oc_osize;	/* Size of object struct */
	struct vm_object_ops	*oc_ops;	/* pointer to op handles */
	struct vm_map_entry_ops	*oc_mape;	/* map entry operations */
};


/*
 * Object types
 */
#define	OT_NULL		0x00	/* No actions supported */
#define	OT_UBC		0x01	/* File sytem shared vnode */
#define	OT_ANON		0x02	/* Anonymous memory */
#define	OT_SWAP		0x03	/* Swap object */
#define	OT_DEVMAP	0x04	/* Memory mapped device */
#define	OT_KERNEL	0x05	/* Non-paged kernel */
#define	OT_PKERNEL	0x06	/* Pageable kernel */
#define	OT_SHM		0x07	/* System V shared memory */
#define	OT_SEG		0x08	/* Segment address space */
#define	OT_RM_K_RCV	0x09	/* Reflective memory, kernel receive */
#define	OT_RM_K_TRANS	0x0a	/* Reflective memory, kernel transmit */
#define	OT_RM_U_RCV	0x0b	/* Reflective memory, user receive */
#define	OT_RM_U_TRANS	0x0c	/* Reflective memory, user transmit */
#define	OT_RM_U_DUAL	0x0d	/* Reflective memory, user dual window */
#define	OT_RM_K_DUAL	0x0e	/* Reflective memory, kernel dual window */
#define	OT_SSM		0x0f	/* System V shared memory, segmented */
#define	OT_STACK	0x10	/* stack region */
#define OT_ZKERNEL	0x11	/* Kernel ZFOD memory */
#define	OT_LAST		0x12	/* Maximum */

#define	vm_object_type(OBJ)	((vm_object_t)(OBJ))->ob_type
#define ismmaper(entry)							\
	(vm_object_type(entry->vme_object) == OT_UBC)                 

#ifdef	KERNEL

/*
 *	Object locking macros for object
 *	common part (with and without debugging).
 */
#define vm_object_lock_init(OBJECT)					\
	simple_lock_setup(&((vm_object_t)(OBJECT))->ob_lock, vm_object_lockinfo)
#define vm_object_lock(OBJECT)						\
	simple_lock(&((vm_object_t)(OBJECT))->ob_lock)
#define vm_object_unlock(OBJECT)					\
	simple_unlock(&((vm_object_t)(OBJECT))->ob_lock)
#define vm_object_lock_try(OBJECT)					\
	simple_lock_try(&((vm_object_t)(OBJECT))->ob_lock)

/*
 * Old functions now implemented as macros
 */

#define vm_object_reference(OBJ) 	OOP_REFERENCE(OBJ)
#define vm_object_deallocate(OBJ)	OOP_DEALLOCATE(OBJ)
#define vm_object_swapon(OBJ) 					\
	((vm_object_t)(OBJ))->ob_flags |= OB_SWAPON

extern struct vm_object_config *vm_object_config[];
#define vm_object_to_vmeops(OBJ)				\
	vm_object_config[((vm_object_t)(OBJ))->ob_type]->oc_mape
	
extern vm_object_t	nkernel_object, pkernel_object,
	    kernel_object, zkernel_object;
extern struct lockinfo	*vm_object_lockinfo;

/*
 * Prototypes
 */
struct vm_policy;

extern kern_return_t
	vm_object_allocate(int, vm_size_t, caddr_t, vm_object_t *),
	vm_object_swapout(vm_object_t, int *);

extern void
	vm_ops_reference_def(vm_object_t),
	vm_ops_deallocate_def(vm_object_t),
	vm_object_init(void),
	vm_object_free(vm_object_t),
	vm_object_swapoff(vm_object_t),
	vm_object_swapin(vm_object_t);

extern int
	vm_ops_pagein_def(void),
	vm_ops_swap_def(vm_object_t, int *),
	vm_ops_pageout_def(vm_object_t, vm_offset_t, vm_size_t);

#endif	/* KERNEL */
#endif /* !_VM_VM_OBJECT_H_ */
