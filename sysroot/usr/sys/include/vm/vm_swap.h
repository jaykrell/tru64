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
 * @(#)$RCSfile: vm_swap.h,v $ $Revision: 1.1.39.4 $ (DEC) $Date: 2002/04/30 17:31:22 $
 */
#ifndef	__VM_SWAP__
#define __VM_SWAP__
#include <sys/vp_swap.h>
#include <sys/unix_defs.h>
#include <kern/lock.h>
#include <vm/vm_map.h>
#include <kern/macro_help.h>

/*
 * swap arguments for swapon
 */

#define MS_NONE		0x0000
#define	MS_PREFER	0x0001

struct vm_swap {
	struct vm_swap		*vs_fl,		/* forward and */
				*vs_bl;		/* backward link */
	decl_simple_lock_data(,	vs_lock)	/* Lookup and allocation lock */
	int			vs_oshift;	/* Object shift */
	int			vs_swapsize;	/* Space size */
	int			vs_freespace;	/* Free space */
	int			vs_flags;       /* Flags */
	struct vps_info		vs_vinfo;	/* from VOP_SWAP open */
	struct vm_swap_object	*vs_object;	/* swap object */
	char			*vs_path;	/* pathname of swap file */
	unsigned long		*vs_bitmap;	/* swap allocation bitmap */
	unsigned long		*vs_free;	/* free hint in bitmap */
};
typedef	struct vm_swap	*vm_swap_t;
#define	VM_SWAP_NULL	((vm_swap_t)0)

#define	vs_vp		vs_vinfo.vps_vp
#define	vs_rvp		vs_vinfo.vps_rvp
#define	vs_dev		vs_vinfo.vps_dev
#define	vs_shift	vs_vinfo.vps_shift

struct vm_swap_object {
	struct vm_object sw_object;		/* Object common part */
	struct vm_swap 	*sw_sp;			/* Pointer to vm_swap */
};
typedef	struct vm_swap_object	*vm_swap_object_t;

/*
 * Swap hash buckets.
 */
struct vm_page_bucket;				/* Forward declaration */
struct vm_swap_buckets_control {
        struct vm_page_bucket	*buckets;
        int			count;
        int			hash_mask;
};
typedef struct vm_swap_buckets_control  *vm_swap_buckets_cntl_t;


/*
 * Swap flags
 */

#define	VS_ENABLED	0x01			/* Swapping enabled */


#ifdef	_KERNEL

extern int		vm_swap_written;	/* Total pages out */
extern vm_size_t	vm_swap_free;		/* Space available */
extern vm_size_t	vm_swap_total;		/* total space */
extern vm_size_t	vm_swap_borrowed;	/* Temporary swap space */
extern boolean_t	vm_swap_overcommit;
extern int 	 	vm_swap_lock_wait_time;
extern vm_swap_t	vm_swap_circular;	/* Next swap device to use */
extern struct vm_swap_object
			vm_swap_lazy_object;


decl_simple_lock_data(extern, vm_swap_space_lock)
decl_simple_lock_data(extern, vm_swap_circular_lock)

#define	swap_space_free(SZ) {				\
	simple_lock(&vm_swap_space_lock);		\
	if (vm_swap_overcommit)                         \
                vm_swap_borrowed -= (SZ);         	\
	else						\
		vm_swap_free += (SZ);			\
	simple_unlock(&vm_swap_space_lock);		\
}

#define	swap_space_alloc(SZ, RET) {			\
	simple_lock(&vm_swap_space_lock);		\
	if (vm_swap_overcommit) {			\
		vm_swap_borrowed += (SZ);		\
		RET = TRUE;				\
	} else if (RET = ((SZ) <= vm_swap_free))	\
		vm_swap_free -= (SZ); 			\
	simple_unlock(&vm_swap_space_lock);		\
}

struct vm_swap_list {
	decl_simple_lock_data(, vsl_lock)
	int			vsl_flags;
	int			vsl_rcount;
	struct vm_swap		*vsl_head;
};

extern	struct vm_swap_list	vm_swap_list;

#define	VSL_WRITE	1
#define	VSL_WANTWRITE	2

#define	swap_read_lock()	do {			\
	simple_lock(&vm_swap_list.vsl_lock);		\
	while (vm_swap_list.vsl_flags) {		\
		register int i;				\
		simple_unlock(&vm_swap_list.vsl_lock);	\
		for (i = vm_swap_lock_wait_time;	\
		     i && vm_swap_list.vsl_flags;	\
		     i--);				\
		simple_lock(&vm_swap_list.vsl_lock);	\
	}						\
	vm_swap_list.vsl_rcount++;	 		\
	simple_unlock(&vm_swap_list.vsl_lock);		\
} while(0)

#define	swap_write_lock()	do {					\
	simple_lock(&vm_swap_list.vsl_lock);				\
	while (vm_swap_list.vsl_rcount || vm_swap_list.vsl_flags) {	\
		vm_swap_list.vsl_flags |= VSL_WANTWRITE;		\
		assert_wait_mesg((vm_offset_t)&vm_swap_list,		\
				 FALSE, "swaplock");			\
		simple_unlock(&vm_swap_list.vsl_lock);			\
		thread_block();						\
		simple_lock(&vm_swap_list.vsl_lock);			\
	}								\
	vm_swap_list.vsl_flags = VSL_WRITE;				\
	simple_unlock(&vm_swap_list.vsl_lock);				\
} while(0)

#define	swap_read_unlock()	do {				\
	simple_lock(&vm_swap_list.vsl_lock);			\
	vm_swap_list.vsl_rcount--;	 			\
	if (vm_swap_list.vsl_rcount == 0 &&			\
	    vm_swap_list.vsl_flags & VSL_WANTWRITE) {		\
		vm_swap_list.vsl_flags = 0;			\
		simple_unlock(&vm_swap_list.vsl_lock);		\
		thread_wakeup((vm_offset_t)&vm_swap_list);	\
	} else							\
		simple_unlock(&vm_swap_list.vsl_lock);		\
} while(0)

#define	swap_write_unlock()	do {				\
	simple_lock(&vm_swap_list.vsl_lock);			\
	if (vm_swap_list.vsl_flags & VSL_WANTWRITE)		\
		thread_wakeup((vm_offset_t)&vm_swap_list);	\
	vm_swap_list.vsl_flags = 0;				\
	simple_unlock(&vm_swap_list.vsl_lock);			\
} while(0)

#define swap_vslock(VS)		simple_lock(&((VS)->vs_lock))
#define	swap_vsunlock(VS) 	simple_unlock(&((VS)->vs_lock))

/*
 * Prototpes
 */
struct vm_page;
struct vm_anon;
struct vm_anon_object;

extern boolean_t
	swap_reserve(struct vm_anon_object *, vm_size_t),
	swap_lazy_alloc(struct vm_page *, vm_swap_t);

extern vm_swap_t*
	swap_alloc(boolean_t, vm_swap_t, struct vm_page *);

extern void
	swap_release(struct vm_anon_object *, vm_size_t),
	swap_free(struct vm_anon *, boolean_t),
	swap_warn(boolean_t),
	vm_swap_write(struct vm_page *),
	vm_swap_io(struct vm_page **, int, int),
	vm_swap_sort_add(struct vm_page **, struct vm_page *),
	vm_swap_hash_init(int),
	vm_swap_insert_hash(struct vm_page *, vm_swap_object_t, vm_offset_t),
	vm_swap_remove_hash(struct vm_page *, vm_swap_object_t, vm_offset_t);

extern int
	vm_swapon(caddr_t, int, long, long, enum uio_seg);

#endif	/* KERNEL */
#endif	/* !__VM_SWAP__ */
