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
 * @(#)$RCSfile: vm_kmap.h,v $ $Revision: 1.1.15.6 $ (DEC) $Date: 1999/12/22 21:59:23 $
 */
#ifndef	__VM_KMAP__
#define	__VM_KMAP__ 1

/*
 * The kernel fault wait strategy is unlike that for the U maps and C maps.
 * It would be hazardous to hold a map write lock waiting for faults to
 * complete.  For that matter it could result in a deadlock.  Instead for
 * the kernel we let write lock synchronize themselves at the map level.
 * A write lock proceeds to operate until it encounters a map entry with
 * fault activity.  The operation releases the map write lock while holding
 * the map entry fault lock.  It indicates its desire to modify the map
 * entry by updating the entry's wait field.  Other writers who progress
 * to this map entry will do the same if their intent of crossing the
 * map entry is anything other than list traversal.  All operations are in a 
 * retry mode.  A finishing faulter checks to see if the wait bit is set.  It
 * does so with the entry fault lock taken.  If there are writers waiting
 * on the entry, then they are all awakened and race to acquire the write
 * lock once again.  All map entry routines are passed the entry with the
 * fault lock taken and the map write locked.  The handle should release the
 * map write lock as quickly as possibly to enable other map activity 
 * to proceed.
 *
 * All write map entry operation handles have a fault lock acquired for
 * them and the map is passed write locked.  This is true because the
 * entry faultlock couldn't have been acquired if there was any fault
 * activity.  The entry operation is assumed to release the map write
 * lock before engaging in any activity which could suspend the thread
 * executing the code.  When the operation completes the fault lock is
 * released by the upper level map operation routine.
 *
 * The vm_mape_faultwait() is called by a thread that has the address
 * map write locked.  Pagefaults always precede map modification
 * requests; such as protection, deletion and wiring.
 */
#define vm_mape_kfaultwait(VME,RETRY) {					\
	if ((VME)->vme_faults) {					\
		simple_lock(&(VME)->vme_faultlock);			\
		if ((VME)->vme_faults) {				\
			vm_map_unlock((VME)->vme_map);			\
			(VME)->vme_faultwait = 1;			\
			assert_wait((vm_offset_t) (VME), FALSE);	\
			simple_unlock(&(VME)->vme_faultlock);		\
			thread_block();					\
			RETRY;						\
		} else							\
			simple_unlock(&(VME)->vme_faultlock);		\
	}								\
}

/*
 * Prototypes
 */
struct vm_map;
struct vm_map_entry;
struct vm_object;
struct vm_map_entry_ops;
struct vm_policy;

extern struct vm_map_entry *
	k_map_insert(struct vm_map *, struct vm_map_entry_ops *,
		struct vm_object *, vm_offset_t, vm_offset_t, vm_offset_t,
		vm_prot_t, struct vm_map_entry *);
extern kern_return_t
	k_map_allocate_va(struct vm_map *, struct vm_object *, vm_offset_t *,
		vm_size_t, boolean_t),
	k_map_deallocate_va(struct vm_map *, vm_offset_t, vm_size_t),
	k_map_delete(struct vm_map *, vm_offset_t, vm_offset_t, boolean_t),
	k_map_submap(struct vm_map *, vm_offset_t *, vm_offset_t *, vm_size_t,
		struct vm_map *),
	k_map_create(struct vm_map *),
	k_map_allocate_nonpaged(struct vm_map *, struct vm_object *,
			vm_offset_t *, vm_size_t, vm_prot_t, int, vm_size_t, 
		        struct vm_policy *),
	k_map_allocate_paged(struct vm_map *, struct vm_object *, vm_offset_t *,
			vm_size_t, vm_prot_t, boolean_t, struct vm_policy *);

extern int k_mem_allocate(vm_map_t, vm_offset_t, vm_size_t, struct vm_policy *);

extern boolean_t
	k_invalid_checkprot(struct vm_map_entry *, vm_offset_t, vm_size_t,
		vm_prot_t);

extern vm_offset_t
	stack_alloc(int),
	vm_alloc_kva(size_t);

extern void
	k_mape_op_bad(void),
	stack_free(vm_offset_t);

#endif /* !__VM_KMAP__ */
