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
 * @(#)$RCSfile: u_mape_ssm.h,v $ $Revision: 1.1.13.2 $ (DEC) $Date: 2002/02/11 23:23:32 $
 */

#ifndef	__VM_U_MAPE_SSM_H__
#define	__VM_U_MAPE_SSM_H__
/*
 * Segmented Shared Memory
 *
 * System V shared memory support for large shared regions.
 * Implemented using shared segments (8Meg) and shared pagetables.
 */

/*
 * Describes a single segment.
 */
struct shared_segment {
	struct pmap_ssm		ss_pmap;	/* pmap info */
	decl_simple_lock_data  	(,ss_lock)	/* protects anon array */
	struct vm_anon		**ss_anon;	/* anons */
};
typedef struct shared_segment *shared_segment_t;

/*
 * The Segmented Shared Memory object.  All pages are linked to the
 * pagelist in object common.
 */
struct vm_ssm_object {
	struct vm_object	ssm_object;	/* object common */
	struct shmid_internal	*ssm_sp;	/* System V info */
	struct shared_segment	*ssm_seg;	/* segment array */
	int			ssm_flags;	/* flags */
	unsigned int		ssm_rswap;	/* reserved swap */
	unsigned int		ssm_wire_count;	/* object wire count */
	void			*ssm_pshared;	/* pshared state */
	struct vpage 		ssm_prot;	/* shared mem protections */
	struct vpage 		*ssm_vpage;	/* per-page protections */
};

typedef struct vm_ssm_object *vm_ssm_object_t;

#define	ssm_refcnt	ssm_object.ob_ref_count
#define	ssm_rescnt	ssm_object.ob_res_count
#define	ssm_size	ssm_object.ob_size		/* actual size */
#define ssm_protection  ssm_prot.vp_prot

/*
 * Used for anon array allocation.  ss_anon pointer is overloaded during
 * allocation.  Assumes memory is allocated long/quad aligned.
 */
#define	AA_ALLOC	0x1L
#define	AA_WAIT		0x2L
#define	AA_MASK		0x3L

/*
 * Used for anon allocation.  The anon pointer in anon array is overloaded
 * during allocation.
 */
#define	AN_LOCKED	0x1L
#define	AN_WAIT		0x2L
#define	AN_MASK		0x3L
#define AN_PTR(APP)	(vm_anon_t)(*(ulong *)(APP) & ~AN_MASK)
#define SET_AN_PTR(APP,AP)	\
	*(APP) = (vm_anon_t)((ulong)(AP) | (*(ulong *)(APP) & AN_MASK));

/*
 * Since a single wire bit is not sufficient to track VM_WIRE/VM_LOCK  
 * on a shared pte, the vm_page's pg_wire_count is split to count them
 * seperately.
 */
struct pg_ssm_wire {
	union {
		struct {
			unsigned int	_wire:8,
					_lock:8;
		} _wl;
		unsigned int		_bits:16;
	} _uwl;
};

#define	ssm_wire		_uwl._wl._wire
#define	ssm_lock		_uwl._wl._lock
#define	ssm_bits		_uwl._bits

/*
 * Prototypes
 */
extern void
	ssm_page_insert(struct vm_object *, struct vm_page *);
extern kern_return_t
	u_ssm_allocate(vm_size_t, vm_object_t *),
	u_ssm_unmap(struct vm_map_entry *, vm_offset_t, vm_size_t);

#endif	/* __VM_U_MAPE_SSM_H__ */
