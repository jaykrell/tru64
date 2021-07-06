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
 * @(#)$RCSfile: vm_anon.h,v $ $Revision: 1.1.85.6 $ (DEC) $Date: 2002/05/03 18:21:58 $
 */
#ifndef _VM_VM_ANON_H_
#define	_VM_VM_ANON_H_
#include <sys/unix_defs.h>
#include <kern/lock.h>
#include <vm/vm_debug.h>
#include <vm/vm_page.h>
#include <machine/vmparam.h>

struct vm_anon_object {
    struct vm_object	ao_object;	/* Object common part */
    unsigned int 	ao_flags;	/* Flags for anon memory */
    unsigned int	ao_ranon;	/* Reserved swap for object */
    vm_offset_t		ao_rbase;	/* Relative base for pages */
    struct vm_object	*ao_bobject;	/* Object backed by if any */
    vm_offset_t		ao_boffset;	/* Offset of backing object */
    struct vm_anon	**ao_anons;	/* Array of anon pointers */
    simple_lock_data_t	ao_lbitslock;	/* Synchronize bitmap access */
    unsigned long	*ao_albits;	/* Bits to lock anon anons */
    unsigned long	ao_wanted;	/* # threads waiting for pages */
    void		*ao_pshared;	/* state for pshared objects */
    simple_lock_data_t	ao_rsslock;	/* Synchronize RSS page queue access */
    /* The following is valid only if AF_PEERMEM is set in ao_flags */
    vm_map_t		ao_originalmap;	/* Original owner's map ** see Note */
};

typedef	struct vm_anon_object *vm_anon_object_t;

/*
 * Note on ao_originalmap (ONLY used for Cray Intra-Node SHMEM support):
 *
 * This field is set to the map of the process which really owns the memory. 
 * The memory is owned by one process, but mapped into the address space of 
 * one or more "peer" processes.  The anon object representing the memory is 
 * shared by all mappers, including the true owner.
 *
 * If the original owner goes away, this field does not get changed. 
 * This means the pointer will be stale since the map it is referring
 * to will no longer be valid. This should not cause a problem, however,
 * since the field is never dereferenced but is only used in comparisons.
 */

/*
 * This structure describes a SystemV shared memory object
 */
struct vm_shm_object {
    struct vm_anon_object	so_anon_object;	/* Anon portion of object */
    struct shmid_internal	*so_sp;		/* SystemV specific structure */
    unsigned int		so_wire_count;	/* object wire count */
};

typedef struct vm_shm_object *vm_shm_object_t;

#define	ao_size		ao_object.ob_size
#define	ao_refcnt	ao_object.ob_ref_count
#define ao_rescnt	ao_object.ob_res_count
#define ao_oflags	ao_object.ob_flags
#define ao_policy	ao_object.ob_policy
#define ao_bigpg	ao_object.ob_bigpg

#define so_refcnt	so_anon_object.ao_object.ob_ref_count
#define so_rescnt	so_anon_object.ao_object.ob_res_count
#define so_flag		so_anon_object.ao_flags
#define so_size		so_anon_object.ao_object.ob_size
#define so_bobject	so_anon_object.ao_bobject
#define so_anons	so_anon_object.ao_anons
#define so_ranon	so_anon_object.ao_ranon
#define so_oflags	so_anon_object.ao_object.ob_flags
#define so_lbitslock	so_anon_object.ao_lbitslock
#define so_albits	so_anon_object.ao_albits
#define so_wanted	so_anon_object.ao_wanted

/*
 * anon object flags
 */
#define	AF_PRIVATE	0x01			/* private anon */
#define	AF_SHARED	0x02			/* shared anon */
#define	AF_HOLES	0x04			/* anon array has holes */
#define	AF_SWAPPED	0x08			/* swapped out */
#define AF_LAZY		0x10			/* object swapped lazily? */
#define AF_TEXT		0x20			/* maps text */
#define AF_VIRTANON	0x40			/* Virtual anon array? */
#define AF_PEERMEM	0x80			/* Maps peer process' memory */
#define AF_DEFAULTSTACK	0x100			/* obj is default stack? */

/* RSS page queue lock */
#define ANON_RSS_LOCK(aop)	simple_lock(&aop->ao_rsslock)
#define ANON_RSS_LOCK_TRY(aop)	simple_lock_try(&aop->ao_rsslock)
#define ANON_RSS_UNLOCK(aop)	simple_unlock(&aop->ao_rsslock)

/*
 * Defines / macros for msync clusters
 */
#define ANON_MSYNC_CLPAGES	1024
#define ANON_MSYNC_CLSIZE	(ANON_MSYNC_CLPAGES * PAGE_SIZE)
#define ANON_MSYNC_CLMASK	(ANON_MSYNC_CLSIZE - 1)

#define round_anon_msync_cluster(x) \
	((vm_offset_t) ((((vm_offset_t)(x)) + ANON_MSYNC_CLMASK) & ~ANON_MSYNC_CLMASK))

#define trunc_anon_msync_cluster(x) \
	((vm_offset_t) (((vm_offset_t)(x)) & ~ANON_MSYNC_CLMASK))
	    
/*
 * Defines / macros for page clusters...
 */
#define ANON_CLPAGES	16
#define ANON_CLSIZE	(ANON_CLPAGES * PAGE_SIZE)
#define ANON_CLMASK	(ANON_CLSIZE - 1)

#define round_anon_cluster(x) \
	((vm_offset_t) ((((vm_offset_t)(x)) + ANON_CLMASK) & ~ANON_CLMASK))

#define trunc_anon_cluster(x) \
	((vm_offset_t) (((vm_offset_t)(x)) & ~ANON_CLMASK))
	    
/*
 * Macros to manage anon object bitmap...
 */

/*
 * Set bit for corresponding index
 */
#define anon_set(bm, i)					\
MACRO_BEGIN						\
	unsigned long bindex = i >> LOG2BPQUAD;		\
	unsigned long mask = 1L << (i & (BPQUAD-1));	\
	bm[bindex] |= mask;				\
MACRO_END

/*
 * Clear bit for corresponding index
 */
#define anon_clear(bm, i)				\
MACRO_BEGIN						\
	unsigned long bindex = i >> LOG2BPQUAD;		\
	unsigned long mask = 1L << (i & (BPQUAD-1));	\
	bm[bindex] &= ~mask;				\
MACRO_END

/*
 * Test if bit at corresponding index is set
 */
#define anon_isset(bm, i)				\
(((unsigned long *)(bm))[(i >> LOG2BPQUAD)] & (1L << (i & (BPQUAD-1))))


/*
 * Return an indication of whether or not an anon entry is valid, ie
 * has been instantiated.  For now we simply call pmap_extract() because
 * we don't page out the anon array.  If we decide to page out the anon
 * array we would have to see if anon array was paged out or was never
 * mapped.
 */
#define	   ANON_VALID(AP) (pmap_extract(kernel_pmap, (vm_offset_t)AP) != 0L)

/*
 * vm_anon records where a page has been placed on swap storage.
 * The low bit of the first quadword is used for locking, which
 * is set when unlocked.  
 */
struct vm_anon {
	union {
		struct vm_page		*an_page; /* Page hint for anon */
		struct vm_swap_object	*an_swap; /* swap when paged out */
		long			an_lock;  /* only low bit is used */
	} an_un;
	unsigned int	an_refcnt:24,	/* Anon references */
			an_cowfaults:7,	/* Runtime hueristic */
			an_haspage:1;	/* whether an_un is page */
	unsigned int	an_spfn;	/* offset into swap in units of page */
};

typedef	struct vm_anon	*vm_anon_t;

#define	VM_ANON_NULL	((vm_anon_t)0)

#define	an_page		an_un.an_page
#define	an_swap		an_un.an_swap
#define	an_lock		an_un.an_lock
#define	an_hasswap	an_spfn

/*
 * Macros to obtain page/swap without locking
 */
#define	AN_PAGE(AP)	((struct vm_page *)((AP)->an_lock & ~1L))
#define	AN_SWAP(AP)	((struct vm_swap_object *)((AP)->an_lock & ~1L))

/*
 * Kernel anons are used for kernel pageable memory.  Since they are stored
 * in a hash we need a bit more information than user's.
 */
struct vm_kanon {
	struct vm_anon	kan_anon;	/* The typical anon stuff */
	vm_offset_t	kan_offset;	/* Offset within kernel map */
	struct vm_kanon	*kan_next;	/* Next kanon on this hash bucket */
};

typedef struct vm_kanon	*vm_kanon_t;

/*
 * Macros to derive swap offsets from anon and page pointers.
 */
#define	AN_SOFF(ap)	ptoa((ap)->an_spfn)
#define	PG_SOFF(pp)	ptoa((pp)->pg_anon->an_spfn)
#define	PG_SPFN(pp)	(pp)->pg_anon->an_spfn


#define	ANON_REFMAX	0xffffff
#define	ANON_COWMAX	0x7f

#ifdef	KERNEL

/*
 * On MP machines concurrent anon updates are serialized by a spin lock. 
 * Using a simple lock for each anon structure would be very wasteful. 
 * Instead, the low bit of the first quadword is overloaded to be the lock
 * bit.  This is possible since the pointer is quadword aligned and the lower
 * bits are unused.  The lock bit is set in the unlocked state and cleared in
 * the locked state.  This allows access to the an_page and an_swap members
 * under the lock without any additional masking.  Care should be taken when
 * accessing the an_page and an_swap members without the lock.  The AN_PAGE()
 * and AN_SWAP() macros above are provided for this purpose.
 */
#ifdef	ANON_LOCK_DEBUG
extern void alog(vm_anon_t, int, void *);

#define	a_lock_init(AP)		(_a_lock_init(AP), alog(AP, 0, 0))
#define	a_lock(AP)		(_a_lock(AP), alog(AP, 1, 0))
#define	a_lock_try(AP)		(_a_lock_try(AP)? (alog(AP, 2, (void *)1), 1): \
						  (alog(AP, 2, (void *)0), 0)) 
#define	a_unlock(AP)		(alog(AP, 3, 0), _a_unlock(AP))
#define	a_unlock_data(AP, D)	(alog(AP, 4, D), _a_unlock_data(AP, D))
#else
#define	a_lock_init(AP)		_a_lock_init(AP)
#define	a_lock(AP)		_a_lock(AP)
#define	a_lock_try(AP)		_a_lock_try(AP)
#define	a_unlock(AP)		_a_unlock(AP)
#define	a_unlock_data(AP, D)	_a_unlock_data(AP, D)
#endif

#define a_lock_range(APP, APCNT)		\
MACRO_BEGIN					\
	int	_i;				\
	for (_i = 0; _i < APCNT; _i++)		\
	     a_lock(APP[_i]);			\
MACRO_END

#define a_unlock_range(APP, APCNT)		\
MACRO_BEGIN					\
	int	  _i;				\
	for (_i = 0; _i < APCNT; _i++)		\
	     a_unlock(APP[_i]);			\
MACRO_END

/*
 * Prototypes
 */
struct vm_map_entry;
struct vm_page;
struct vm_object;
struct vm_swap_object;
struct vm_control;
struct vm_policy;

extern void
	a_lock_bigpg(struct vm_page*),
	a_unlock_bigpg(struct vm_page*),
	anon_init(void),
	anon_kpage_alloc(vm_anon_t, struct vm_policy *),
	vm_anon_page_free(vm_anon_t, boolean_t),
	anon_free(vm_anon_t, boolean_t),
	anon_kfree(vm_kanon_t),
	anon_getpage(vm_anon_object_t, vm_offset_t,
		     struct vm_map_entry *, vm_offset_t,
		     struct vm_page **, int, vm_anon_t),
	vm_kanon_insert(vm_kanon_t, vm_offset_t),
	anon_remap(vm_offset_t, vm_offset_t, vm_size_t),
	u_anon_lock(vm_anon_object_t, vm_offset_t, vm_size_t),
	u_anon_lock_wait(vm_anon_object_t, vm_offset_t, vm_size_t),
	u_anon_unlock(vm_anon_object_t, vm_offset_t, vm_size_t),
	u_anon_oop_unlock(struct vm_object *, struct vm_page *),
	u_anon_oop_deallocate(struct vm_object *),
	u_anon_oop_reference(struct vm_object *),
	u_anon_oop_bad(void),
	u_anon_swap(struct vm_map_entry *, int),
	u_shm_exit(struct vm_map *),
	u_shm_fixup_counts(struct vm_object *),
	_a_lock_init(vm_anon_t),
	_a_lock(vm_anon_t),
	_a_unlock(vm_anon_t),
	_a_unlock_data(vm_anon_t, void *);

extern vm_anon_t
	anon_allocate(void),
	anon_appage_alloc(vm_anon_object_t, vm_offset_t),
	anon_cowpage_alloc(vm_anon_object_t, vm_offset_t, vm_anon_t),
	anon_pagezero_alloc(vm_anon_object_t,	vm_offset_t),
	vm_kanon_lookup(vm_offset_t, boolean_t);

extern struct vm_page
	*vm_anon_page_alloc(vm_anon_object_t, vm_offset_t, vm_anon_t **, int);

extern int
	u_anon_allocate(vm_size_t, boolean_t, boolean_t, struct vm_object **),
	u_anon_create(struct vm_map *, struct vm_object *, vm_offset_t),
	u_anon_cluster(struct vm_map_entry *, vm_offset_t, int,
			vm_offset_t *, vm_offset_t *, struct vm_control *),
	u_anon_dup(struct vm_map_entry *, vm_offset_t, vm_size_t,
		 	struct vm_map_entry *, vm_copy_t),
	u_anon_free(vm_anon_object_t, vm_offset_t, vm_offset_t, boolean_t),
	u_anon_unwire(struct vm_map_entry *, vm_offset_t, vm_size_t, boolean_t),
	u_anon_unmap(struct vm_map_entry *, vm_offset_t, vm_size_t),
	u_anon_msync(struct vm_map_entry *, vm_offset_t, vm_size_t, int),
	u_anon_lockop(struct vm_map_entry *, vm_offset_t, vm_size_t,
			vm_fault_t),
	u_anon_core(struct vm_map_entry *, unsigned, char *, int *),
	u_anon_control(struct vm_map_entry *, vm_offset_t, vm_size_t,
			vm_control_t, int),
	u_anon_copy(struct vm_map_entry *, vm_copy_op_t),
	u_anon_grow(struct vm_map_entry *, vm_prot_t, vm_size_t, boolean_t),
	u_anon_oop_pagectl(struct vm_object *, struct vm_page **, int, int),
	u_anon_oop_pageout(struct vm_object *, struct vm_page *, vm_size_t),
	u_anon_oop_pagewrite(struct vm_object *, struct vm_page *),
	u_anon_oop_swapout(struct vm_object *, int *),
	u_anon_protect(struct vm_map_entry *, vm_offset_t, vm_size_t,
			vm_prot_t),
	anon_shrink(vm_anon_object_t, vm_size_t, boolean_t),
	u_shm_allocate(vm_size_t, struct vm_object **, boolean_t);

extern boolean_t
	anon_valid(vm_anon_t *),
	u_anon_check_protect(struct vm_map_entry *, vm_offset_t,
			vm_size_t, vm_prot_t),
	u_anon_oop_lock_try(struct vm_object *, struct vm_page *),
	_a_lock_try(vm_anon_t);

extern kern_return_t
	anon_delete(vm_anon_object_t),
	anon_grow(vm_anon_object_t, vm_size_t, boolean_t),
	anon_object_allocate(struct vm_map *, vm_anon_object_t *, vm_size_t),
	anon_dup(vm_copy_t, vm_map_entry_t, vm_offset_t, vm_size_t,
		 vm_map_entry_t, vm_anon_object_t),
	u_anon_init(struct vm_object *, caddr_t),
	u_anon_fault(struct vm_map_entry *, vm_offset_t, vm_size_t, vm_prot_t,
		     vm_fault_t, struct vm_page **),
	u_anon_oop_pagesteal(struct vm_object *, struct vm_page *),
	u_shm_unmap(struct vm_map_entry *, vm_offset_t, vm_size_t),
	anon_dontneed(vm_map_entry_t ep, vm_offset_t addr, vm_offset_t size);

#endif	/* KERNEL */
#endif /* !_VM_VM_ANON_H_ */
