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
 * @(#)$RCSfile: u_mape_seg.h,v $ $Revision: 1.1.30.1 $ (DEC) $Date: 2002/01/25 22:02:21 $
 */
#ifndef	__U_MAPE_SEG__
#define	__U_MAPE_SEG__ 1

struct vm_seg_object {
	struct vm_object
			sego_object;		/* Object common part */
	struct vm_seg_object
			*sego_cfl, *sego_cbl;	/* Cached queue */
	vm_offset_t	sego_segbase;		/* Virtual address base */
	queue_head_t	sego_pmap;		/* queue of pmap segs */
	int		sego_flags;		/* Flags */
	int		sego_nseg;		/* Number of segments */
	struct vm_seg	*sego_seglist;		/* Segments attached */
};

#define	sego_size	sego_object.ob_size
#define	sego_ref_count	sego_object.ob_ref_count
#define	sego_res_count	sego_object.ob_res_count
#define sego_oflags	sego_object.ob_flags

#define	OSEG_LLOCK	0x01			/* Lookup lock */
#define OSEG_LWANT	0x02			/* Want lookup lock */
#define	OSEG_FIXED	0x04			/* Mapped by a fixed request */
#define	OSEG_CACHED	0x08			/* On cached list */
#define	OSEG_ERROR	0x10			/* Release on error */
#define	OSEG_REPL	0x20			/* replicate segment */

typedef	struct vm_seg_object	*vm_seg_object_t;
#define	VM_SEG_OBJECT_NULL	(vm_seg_object_t) 0


enum seg_ret {SEG_CONFLICT, SEG_LOADED, SEG_EMPTY};

struct vm_seg {					/* Segments in the global obj */
	struct vm_seg	*seg_vnext;		/* vop segments */
	struct vm_seg	*seg_onext;		/* seg object segment on */
	struct vm_seg_object
			*seg_obj;		/* Segment object */
	vm_offset_t	seg_start;		/* Starting offset of seg */
	vm_offset_t	seg_size;		/* Size of this seg */
	struct vm_ubc_object
			*seg_vop;		/* Object backing seg */
	vm_offset_t	seg_offset;		/* Offset into bobject */
	vm_prot_t	seg_prot;		/* Segment protection */
	int		seg_ref_count;		/* references */
};

typedef struct vm_seg	*vm_seg_t;
#define	VM_SEG_NULL	(vm_seg_t) 0

extern vm_size_t	u_seg_mask;
#define	round_seg(VA)	(((VA) + u_seg_mask) & ~u_seg_mask)
#define	trunc_seg(VA)	((VA) & ~u_seg_mask)

/*
 * Prototypes
 */
struct vm_map;
struct vm_map_entry;
struct vm_control;
struct vm_ubc_object;
struct vp_mmap_args;

extern void
	u_seg_init(void),
	u_seg_vm_init(struct vm_control *),
	u_seg_cache_clear(struct vm_ubc_object *),
	u_seg_uncache_vnode(struct vm_ubc_object *);

extern int
	u_seg_bad_addr(struct vm_map_entry *, vm_offset_t, vm_size_t);

extern kern_return_t
	u_seg_create(struct vm_map *, struct vm_ubc_object *,
		struct vp_mmap_args *);

#endif	/* __U_MAPE_SEG__ */
