/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: vm_umap.h,v $
 * Revision 1.1.46.5  2005/03/23  17:07:46  Thomas_Blinn
 * 	Use FAULT_LOCKED() instead of SLOCK_LOCKED() in faultlock check.
 * 	[2005/03/17  22:04:25  Thomas_Blinn]
 *
 * 	In vm_faultwait() definition, check for multiple fault waiters
 * 	on the same map entry.  Since fault waiters are modifiers, any
 * 	case of more than one waiter on the same map entry is a likely
 * 	race condition just waiting to bury some change or otherwise
 * 	trash the state of the map.  Parallelled by a change in the
 * 	kernel map specific vm_mape_kfaultwait() definition.
 * 	In vm_faultwait() definition, use vm_mape_map_locked_check(VME)
 * 	from vm_map.h to implement the "map is locked" check.
 * 	In vm_faultwait() definition, make sure that no one is holding
 * 	the simple lock in the map entry before we proceed; we want to
 * 	not just make sure the fault count is zero, but that there are
 * 	no references on the entry, including an active simple lock.
 * 	Fix customer escalation QARs 36, 158, 216, 224, 225, and earlier PTR cases
 * 	[2005/03/02  19:07:50  Thomas_Blinn]
 *
 * Revision 1.1.46.2  2003/01/06  20:29:16  Matthew_McGrath
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree v51bsupportos
 *     User Revision:  Matthew_McGrath_execdata_br:1.1.47.1 Local Ancestor:1.1.43.2
 *    Merge Revision:  v51bsupportos_br:1.1.46.1
 *   Common Ancestor:  1.1.43.2
 * 	[2003/01/06  19:31:53  Matthew_McGrath]
 *
 * 	Add defines for the bits in executable_data, prototype for
 * 	u_protections_check.  [QAR 94136]
 * 	[2002/12/18  21:40:35  Matthew_McGrath]
 *
 * Revision 1.1.46.1  2002/10/08  18:18:28  Matthew_McGrath
 * Merge Information:  Non-Visual Merge: User specified tree v51asupportos.nightly
 *     User Revision:  wcalphaos_bl6:1.1.43.2 Local Ancestor: n/a
 *    Merge Revision:  v51asupportos_nightly:1.1.41.3
 *   Common Ancestor:  1.1.41.2
 * 	Merge up to v51asupportos.nightly
 * 
 * Revision 1.1.41.3  2002/09/24  16:59:16  Brett_Heath_Wlaz
 * Introduced UM_LOCK_FUTURE_ALL flag for QAR 93866
 * 
 * Revision 1.1.41.2  2002/06/19  12:39:31  Greg_Bellows
 * 	Added logic to vm_mape_faultwait to allow us to breakout early
 * 	if we have covered the object's possible address space.
 * 	QAR 93003
 * 
 * Revision 1.1.43.2  2002/05/13  17:45:46  Greg_Bellows
 * 	Added logic to vm_mape_faultwait to allow us to breakout early
 * 	if we have covered the object's possible address space.
 * 	QAR 93003
 * 
 * Revision 1.1.43.1  2002/02/15  16:35:37  David_Bernardo
 * 	Add new macros.
 * 
 * Revision 1.1.41.1  2002/01/14  17:20:41  William_Braswell
 * 	added cast to vm_mape_faultwait to elminate
 * 	compiler warning/error
 * 	[2002/01/14  16:41:19  William_Braswell]
 * 	renamed vm_mape_faultwait to vm_faultwait and
 * 	created new vm_mape_faultwait to deal with anon
 * 	objects that have multiple map entries for the
 * 	same object.
 * 	CLD: LU_G01229
 * 	[2001/12/18  21:07:31  William_Braswell]
 * 
 * Revision 1.1.22.3  1999/11/01  23:49:30  Shashi_Mangalat
 * 	Add u_map_is_locked() prototype.
 * 
 * Revision 1.1.22.2  1999/06/22  21:22:09  Nitin_Karkhanis
 * 	o The um_lock_future and um_unload_all bits in the
 * 	  u_map_private structure have been deleted and
 * 	  replaced with a flags field that contains three
 * 	  lock future masks (for READ, WRITE, and EXEC). These
 * 	  bits allow for finer control of the types of future
 * 	  mappings that should be locked into memory. The
 * 	  memcntl() MCL_FUTURE_SELECTIVE work done for Lycos,
 * 	  Inc. (see QAR 54976) takes advantage of these mask
 * 	  values.
 * 	  The um_unload_all bit that was part of the
 * 	  u_map_private structure was also removed and replaced
 * 	  with a mask value (UM_UNLOAD_ALL) that resides within
 * 	  the new flags field.
 * 	o Add prototype for lock_future(), the routine address
 * 	  space creation routines are to call when determining
 * 	  whether the newly created address space should be
 * 	  locked into memory.
 * 	[1999/06/21  20:42:45  Nitin_Karkhanis]
 * 
 * Revision 1.1.13.8  1999/02/02  19:48:28  Shashi_Mangalat
 * 	Remove extraneous semicolons.
 * 	[1999/01/29  20:51:49  Shashi_Mangalat]
 * 
 * Revision 1.1.13.7  1998/11/25  23:35:33  Shashi_Mangalat
 * 	Remove VPAGEMAX limit.
 * 	VM/NUMA scalability enhancements.
 * 	[1998/11/24  21:00:17  Shashi_Mangalat]
 * 
 * Revision 1.1.13.6  1998/10/06  18:03:16  David_Anderson
 * 	Extern u_map_actual_size() function.
 * 	[1998/10/05  14:41:48  David_Anderson]
 * 
 * Revision 1.1.13.5  1997/09/24  21:22:52  Shashi_Mangalat
 * 	Add prototype for u_map_grow_actual().
 * 	[1997/09/23  17:13:43  Shashi_Mangalat]
 * 
 * Revision 1.1.13.4  1997/09/08  22:25:54  Shashi_Mangalat
 * 	Merge of PTmin BL10 changes (PTCOS_BL6:PTCOS_BL10).
 * 	 Revision 1.1.16.2  1997/06/17  21:44:44  Shashi_Mangalat
 * 	 Add um_actual_size.  task_info() will use um_actual_size instead of
 * 	 calling vm_map_actual_size() to aoid waiting for the map lock.
 * 	 Remove unnecessary um_lock since the member fields are now protected
 * 	 by the map lock.  Re-arranged fields to remove padding (saves 32bytes).
 * 	[1997/09/08  21:11:43  Shashi_Mangalat]
 * 
 * Revision 1.1.13.3  1997/03/03  15:41:01  Robin_Miller
 * 	Adding common function prototypes.
 * 	Changed #ifdef KERNEL to _KERNEL.
 * 	[1997/03/03  15:10:50  Robin_Miller]
 * 
 * Revision 1.1.13.2  1996/08/20  18:27:36  Shashi_Mangalat
 * 	Remove unused um_maxwired and um_wired from u_map_private structure.
 * 	[1996/08/14  21:56:58  Shashi_Mangalat]
 * 
 * Revision 1.1.11.2  1995/06/30  12:32:05  Patrick_ORourke
 * 	Add prototype for u_map_is_wired.
 * 	[1995/06/29  20:27:46  Patrick_ORourke]
 * 
 * Revision 1.1.9.2  1994/12/12  18:20:36  Larry_Woodman
 * 	Reset the vme_faultwait in vm_mape_faultwait before going to sleep.
 * 	This prevents missed wakeups when multiple callers enter with the
 * 	map read locked.
 * 	[1994/12/08  14:59:35  Larry_Woodman]
 * 
 * Revision 1.1.7.4  1994/03/02  04:38:56  Shashi_Mangalat
 * 	Modified to use common vm_mape_fault() and vm_mape_faultdone() macros.
 * 	[1994/03/02  04:25:42  Shashi_Mangalat]
 * 
 * Revision 1.1.7.3  1994/01/18  22:16:37  Shashi_Mangalat
 * 	Modified call to mpsleep() from vm_mape_faultlock() to assert_wait.
 * 	Do wakeup after unlocking faultlock.
 * 	[1994/01/13  21:18:47  Shashi_Mangalat]
 * 
 * Revision 1.1.7.2  1993/08/26  15:08:31  Shashi_Mangalat
 * 	Removed dependancy on UNIX_LOCKS.  Renamed lock field from um_resource
 * 	to um_lock.
 * 	[1993/08/25  20:37:04  Shashi_Mangalat]
 * 
 * Revision 1.1.3.4  1992/07/08  16:39:59  Joe_Martin
 * 	merged in Silver BL8_2
 * 	Revision 1.1.2.4  92/06/19  11:02:41  Robert_Picco
 * 	Segmentation code
 * 	[92/06/18  21:09:13  Robert_Picco]
 * 
 * Revision 1.1.3.3  92/04/14  14:01:25  Joe_Martin
 * 	AG_BL6 merge
 * 	Revision 1.1.2.3  92/03/10  09:58:43  Ronald_Widyono
 * 	bmerge with AG
 * 	[92/03/09  23:44:00  Ronald_Widyono]
 * 	Remove UNIX_LOCKS conditional.  simple_lock_addr() handles everything
 * 	[92/03/04  16:11:33  Ronald_Widyono]
 * 	Use simple_lock_addr() macro when passing simple lock addresses.
 * 	Fixes broken RT kernel build.
 * 	[92/03/03  02:21:15  Ronald_Widyono]
 * 	Revision 1.1.2.2  92/02/26  15:56:48  Charles_Briggs
 * 	[92/04/14  13:54:01  Joe_Martin]
 * 
 * Revision 1.1.3.2  92/03/19  08:56:01  Al_Delorey
 * 	From Silver: AG_BL5
 * 	[92/03/18  18:35:28  Al_Delorey]
 * 	UBC merge.
 * 	[92/02/22  14:52:40  Charles_Briggs]
 * 
 * Revision 1.1.1.2  92/03/17  17:11:30  devbld_gsf
 * 	First AG_BL5 version.  Moved from Ag baselevel delivery tree.
 * 
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: vm_umap.h,v $ $Revision: 1.1.46.5 $ (DEC) $Date: 2005/03/23 17:07:46 $
 */
#ifndef	__VM_UMAP__
#define	__VM_UMAP__ 1

#ifdef __cplusplus
extern "C" {
#endif

#include <kern/lock.h>
#include <vm/vm_vlock.h>
#include <sys/mman.h>

/* bit definitions for executable_data */
#define VM_ED_SUIDROOT	0x1
#define VM_ED_SUIDANY	0x2
#define VM_ED_ROOT	0x4
#define VM_ED_ANY	0x8
#define VM_ED_FAIL	0x10
#define VM_ED_MSG	0x20

/*
 * user mode private map structure
 * The following members can change after creation, and are protected
 * by the map lock:
 * 
 * 	um_actual_size
 * 	um_lock_future
 * 	um_unload_all
 * 	um_vlock
 */

struct u_map_private {
	vm_size_t		um_maxvas;	/* Maximum VAS allowed */
	vm_size_t		um_maxrss;	/* Maximum rss allowed */
	vm_size_t		um_rss;		/* Resident pages in map */
	vm_size_t		um_actual_size;	/* actual size */
	unsigned long		um_flags;
	struct vm_vlock		*um_vlock;	/* Virtual space lock by K */
};
typedef	struct u_map_private	*u_map_private_t;
/*
 * Bit masks for um_flags field
 */
#define UM_LOCK_FUTURE_READ     0x1             /* lock future R pages */
#define UM_LOCK_FUTURE_WRITE    0x2             /* lock future W pages */
#define UM_LOCK_FUTURE_EXEC     0x4             /* lock future E pages */
#define UM_LOCK_FUTURE_ALL      0x8             /* lock all future pages */
#define UM_UNLOAD_ALL           0x100           /* unloading all address sp */

/*
 * The code that makes use of these bits assume
 * that the user-level API bit definitions match
 * those defined in the u_map_private structure.
 * The follow conditionals verify that the
 * definitions are consistent.
 */

#if UM_LOCK_FUTURE_READ != PROT_READ
#error	"UM_LOCK_FUTURE_READ != PROT_READ, check definitions"
#endif	/* UM_LOCK_FUTURE_READ != PROT_READ */

#if UM_LOCK_FUTURE_WRITE != PROT_WRITE
#error	"UM_LOCK_FUTURE_WRITE != PROT_WRITE, check definitions"
#endif	/* UM_LOCK_FUTURE_WRITE != PROT_WRITE */

#if UM_LOCK_FUTURE_EXEC != PROT_EXEC
#error	"UM_LOCK_FUTURE_EXEC != PROT_EXEC, check definitions"
#endif	/* UM_LOCK_FUTURE_EXEC != PROT_EXEC */

#define UM_LOCK_FUTURE          (UM_LOCK_FUTURE_READ | UM_LOCK_FUTURE_WRITE \
                                | UM_LOCK_FUTURE_EXEC)
#define UM_LOCK_FUTURE_TEXT     (UM_LOCK_FUTURE_READ | UM_LOCK_FUTURE_EXEC)
#define UM_LOCK_FUTURE_DATA     (UM_LOCK_FUTURE_READ | UM_LOCK_FUTURE_WRITE)

extern vm_size_t u_map_actual_size(vm_map_t);

#define	vm_mape_lockaddr(VME) simple_lock_addr((VME)->vme_faultlock)

#define OBJECT_START_VA(ep) ((unsigned long)(ep->vme_start - (long)ep->vme_offset))
#define OBJECT_END_VA(ep) ((unsigned long)(OBJECT_START_VA(ep) + ep->vme_object->ob_size))

#define VA_TO_OFFSET(ep,va) (va - OBJECT_START_VA(ep))
#define OFFSET_TO_VA(ep,off) (off + OBJECT_START_VA(ep))

#define VA_ABOVE_OBJECT(ep,va) ((unsigned long)va >= OBJECT_END_VA(ep)) 
#define VA_BELOW_OBJECT(ep,va) ((unsigned long)va < OBJECT_START_VA(ep))
#define VA_TOUCHES_OBJECT(ep,va) (!VA_ABOVE_OBJECT(ep, va) && !VA_BELOW_OBJECT(ep, va))

#define VA_ABOVE_MAPE(ep,va) ((unsigned long)va >= ep->vme_end)
#define VA_BELOW_MAPE(ep,va) ((unsigned long)va < ep->vme_start)
#define VA_TOUCHES_MAPE(ep,va) (!VA_ABOVE_MAPE(ep, va) && !VA_BELOW_MAPE(ep, va))

/*
 * The vm_mape_faultwait is called by a thread that has the address map
 * exclusive/write locked.  The thread goes to sleep on the fault lock
 * until the vme_faults count goes to zero.
 *
 * If the object type is ANON and it has a ref count of more than one then
 * it may mean that we have multiple map entries mapping the object.  In this
 * case it is necessary to wait on each of their fault counts.  Of course,
 * the greater than one ref count could simply mean that there is more than
 * one process using the object.  In this case it is not necessary to parse
 * through all the map entries to find ones to wait on, which can be expensive.
 *
 * The code does the following:
 * If we are ANON and have a ref count > 1
 * 	1) Check if the current map entry covers the entire object.  If so,
 * 	   we don't need to do the other stuff, so simply check this map
 * 	   entry and get out.
 * 	2) Otherwise, starting at the first map entry in the map, search for
 * 	   ones that belong to the target object.  On the first one, save the
 * 	   last possible VA covered by the object, this will allow early exit.
 * 	   Now, for every map entry mapping a portion of the object, wait for
 * 	   its fault count to go to 0.  If we reach the point where the next
 * 	   map entry's starting VA is outside the calculated endva then we are
 * 	   done.  
 *
 * NOTE:
 * 	The worse case scenario is we have to traverse all the map entries.
 */
#define vm_mape_faultwait(VME) {					\
	vm_map_t	map = (VME)->vme_map;				\
	vm_object_t	obj = (VME)->vme_object;			\
	int		refcnt = obj->ob_ref_count;			\
	if (obj->ob_type == OT_ANON && refcnt > 1) {			\
		if (obj->ob_size <= ((VME)->vme_end - (VME)->vme_start)) { \
			vm_faultwait(VME);				\
		}							\
		else {							\
			vm_map_entry_t tmpvme = vm_map_first_entry(map);\
			vm_offset_t endva = 0L;				\
			while (tmpvme != (vm_map_entry_t)map) {		\
				if (tmpvme->vme_object == obj) {	\
					if (!endva)			\
					    endva = tmpvme->vme_start + \
						    obj->ob_size;	\
					vm_faultwait(tmpvme);		\
					if (tmpvme->vme_end > endva)	\
						break;			\
				}					\
				tmpvme = tmpvme->vme_next;		\
			}						\
		}							\
	}								\
	else								\
	    vm_faultwait(VME);						\
}

/*
 * Make sure that no one is referencing this map entry, either by
 * having incremented the vme_faults or by holding the simple lock
 * on the vme_faultlock; if the lock is held on entry, wait for it
 * to be released before proceeding.  The the locker has cleared
 * the vme_faults but is still holding the lock and we dispose of
 * the map entry, they will "mcs unlock" panic when they try to
 * release the lock that has been terminated.
 */

#define vm_faultwait(VME) {							\
	vm_mape_map_locked_check(VME);						\
	if ((VME)->vme_faults) {						\
		simple_lock(&(VME)->vme_faultlock);				\
		if ((VME)->vme_faults) {					\
			do {							\
				vm_mape_multiple_faultwaiters_check(VME);	\
				(VME)->vme_faultwait = 1;			\
				assert_wait_mesg((vm_offset_t)(VME),		\
					  FALSE, "vm_faultwait");		\
				simple_unlock(&(VME)->vme_faultlock);		\
				thread_block();					\
				simple_lock(&(VME)->vme_faultlock);		\
			} while ((VME)->vme_faults);				\
		}								\
		simple_unlock(&(VME)->vme_faultlock);				\
	} else {								\
		while (FAULT_LOCKED(VME))					\
			thread_preempt(current_thread(), FALSE);		\
		if ((VME)->vme_faults) panic("vm_faultwait: (VME)->vme_faults not zero");	\
		}								\
}

/*
 * Described return states from u_map_is_wired, see function for definitions.
 */
typedef enum { UMAP_NOCHG, UMAP_KWIRED, UMAP_UWIRED, UMAP_NOWIRED } u_mapwire_t;

#ifdef	_KERNEL
#if defined(_USE_KERNEL_PROTOS)
/*
 * forward declaration for ANSI & C++
 */
struct vnode;

extern boolean_t
	lock_future(vm_map_entry_t, vm_map_t),
	u_map_entry_delete_check(struct vm_map *, vm_map_entry_t, 
			vm_offset_t, vm_offset_t),
	u_map_entry_clip_check(struct vm_map *, vm_map_entry_t,
			vm_offset_t, vm_offset_t),
	u_map_check_protection(struct vm_map *, vm_offset_t,
			vm_offset_t, vm_prot_t),
	u_map_is_locked(struct vm_map *, vm_offset_t, vm_offset_t);

u_mapwire_t
	u_map_is_wired(vm_map_entry_t, vm_offset_t, vm_offset_t, vm_prot_t);

extern void
	u_map_grow_actual(struct vm_map *, vm_size_t),
	u_map_free_vas(struct vm_map *, vm_size_t, vm_size_t),
	u_map_init(void);

extern int
	u_dev_create(struct vm_map *, struct vnode *, vm_offset_t),
	u_map_copy_overwrite(struct vm_map *, vm_offset_t,
			struct vm_map_copy *, boolean_t, vm_size_t),
	u_map_copyin(struct vm_map *, vm_offset_t, vm_size_t,
			boolean_t, struct vm_map_copy **),
	u_map_copyout(struct vm_map *, vm_offset_t *, struct vm_map_copy *),
	u_map_entry_split(struct vm_map_entry *, vm_offset_t, vm_size_t);

extern kern_return_t
	u_map_allocate(struct vm_map *, struct vm_object *, vm_offset_t,
			vm_offset_t *, vm_size_t, boolean_t),
	u_map_control(struct vm_map *, vm_offset_t, vm_offset_t,
			vm_control_t, int),
	u_map_create(struct vm_map *),
	u_map_fault(struct vm_map *, vm_offset_t, vm_prot_t, vm_fault_t),
	u_map_grow_vas(struct vm_map *, vm_size_t, vm_size_t),
	u_map_protect(struct vm_map *, vm_offset_t, vm_offset_t,
			vm_prot_t, boolean_t),
	u_map_delete(struct vm_map *, vm_offset_t, vm_offset_t, boolean_t),
	u_map_enter(struct vm_map *, vm_offset_t *, vm_size_t, vm_offset_t,
			boolean_t, struct vm_object *, vm_offset_t, boolean_t,
			vm_prot_t, vm_prot_t, vm_inherit_t),
	u_map_grow(struct vm_map *, struct vm_object *, vm_offset_t,
			vm_offset_t *, vm_size_t, boolean_t, boolean_t),
	u_map_lockvas(struct vm_map *, vm_offset_t, vm_offset_t, int),
	u_protections_check(vm_prot_t *, char *);

#endif /* defined(_USE_KERNEL_PROTOS) */
#endif	/* _KERNEL */

#ifdef __cplusplus
}
#endif
#endif /* !__VM_UMAP__ */
