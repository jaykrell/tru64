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
 * @(#)$RCSfile: vm_pagelru.h,v $ $Revision: 1.1.34.1 $ (DEC) $Date: 2001/11/16 20:15:19 $
 */
#ifndef	_VM_VM_PAGELRU_H_
#define	_VM_VM_PAGELRU_H_ 1

#ifdef	KERNEL
#define vm_page_lock_queues(vc)		simple_lock(&vc->vm_queue_lock)
#define vm_page_unlock_queues(vc)	simple_unlock(&vc->vm_queue_lock)

/*
 * The following lock macros are used to prevent users of vm_queue_lock
 * from holding it too long.  This is not a strict and fool proof mechanism.
 * The intention is to alleviate the current lock timeout situation.
 * A global flag is set every time a the lock is requested.  This is to be
 * inspected while traversing the queues and appropriate actions taken to
 * release the lock.  Currently used when freeing and unwiring a page and
 * checked by the pageout daemon while deactivating active pages.
 */

#define vm_page_lock_queues_want(vc)		\
MACRO_BEGIN					\
	vc->vm_queue_lock_want = 1;		\
	simple_lock(&vc->vm_queue_lock);	\
MACRO_END

#define vm_page_lock_queues_done(vc)		\
MACRO_BEGIN					\
	vc->vm_queue_lock_want = 0;		\
	simple_unlock(&vc->vm_queue_lock);	\
MACRO_END

/*
 * Page queue states
 */

#define	PG_NOQUEUE	0x0
#define	PG_ACTIVE	0x1
#define	PG_INACTIVE	0x2
#define	PG_STATE	0x3
#define	pg_state(PP)	((PP)->pg_reserved & PG_STATE)
#define	pg_clearstate(PP)						\
	((PP)->pg_reserved &= ~PG_STATE)
#define	pg_setstate(PP,STATE)						\
	(PP)->pg_reserved = ((PP)->pg_reserved & ~PG_STATE) | STATE

/*
 * Other reserved bits
 */

#define	PG_PREWRITE	0x4			/* Page being pre-written  */
#define	PG_PREWRITTEN	0x8			/* Page pre-written once */
#define KERNEL_PAGE	0x10			/* Used to inhibit hashing
						 * and reclaiming kernel
						 * pages from the free 
						 * list.
						 */


#define VM_PAGE_QUEUES_REMOVE(VC, PG)				\
MACRO_BEGIN							\
	if (pg_state(PG) == PG_ACTIVE) {			\
		pgl_remove(VC->vm_queue_active,(PG),p);		\
		VC->vm_active_count -=				\
			bigpg_data[(PG)->pg_size].basepcnt;	\
	}							\
								\
	if (pg_state(PG) == PG_INACTIVE) {			\
		pgl_remove(VC->vm_queue_inactive,(PG),p);	\
		VC->vm_inactive_count -=			\
			bigpg_data[(PG)->pg_size].basepcnt;	\
	}							\
	pg_clearstate(PG);					\
MACRO_END

struct vm_control;

#define total_wired_pages(M)	((M)->md_vm.vm_wiredpages +	\
				 (M)->md_vm.vm_contig_count +	\
				 (M)->md_vm.vm_rmwiredpages +	\
				 (M)->md_ubc.ubc_wiredpages +	\
				 (M)->md_malloc.m_cnt	+	\
				 PMAP_PTEPAGES((M)->md_mid))

#define	HARD_SWAP_CONDITION(VC)	((VC)->vm_free_count < (VC)->vm_free_hardswap)

/*
 * Prototpes
 */
struct vm_page;
struct vm_object;

extern int
	vm_pageout_abort(struct vm_page *),
	vm_pageout_activate(struct vm_page *, boolean_t),
	vm_page_wire_free(struct vm_page *);

extern boolean_t
	vm_pageout_remove(struct vm_page *, boolean_t, boolean_t),
	wire_check(struct vm_page *);

extern kern_return_t
	vm_page_ssm_wire(vm_page_t, boolean_t, int);

extern void
	vm_page_insert_bucket(struct vm_page *, struct vm_object *,
				vm_offset_t),
	vm_page_clean_abort(struct vm_page *),
	vm_cpu_callback(long, long, long, int),
	vm_page_ssm_unwire(vm_page_t, boolean_t, boolean_t, int);

#endif	/* KERNEL */
#endif	/* !_VM_VM_PAGELRU_H_ */
