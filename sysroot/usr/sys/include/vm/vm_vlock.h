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
 * @(#)$RCSfile: vm_vlock.h,v $ $Revision: 1.1.17.2 $ (DEC) $Date: 1999/08/05 20:47:28 $
 */
#ifndef	__VM_VLOCK__
#define	__VM_VLOCK__ 1

/*
 * Support of kernel lock of user address space.
 * We don't want to pollute the user space mappings
 * with locks held by the kernel to do physical I/O.
 * Instead we maintain a list of virtual space locked.
 * Also we don't release empty lock space until we
 * scan and its above some limit.  This will work if
 * the u-map uses a common set of VAS locations to do
 * I/O.
 */ 

struct vm_vlock {
	struct vm_vlock *vl_next;	/* Next link */
	struct vm_vlock *vl_prev;	/* Back pointer */
	vm_offset_t vl_start;		/* Beginning */
	vm_offset_t vl_end;		/* Last exclusive */
	unsigned short vl_count;	/* Locks held */
};

#define	VL_GET_NONE	0	/* no upper level wirings */
#define	VL_GET_FOUND	1	/* upper level wirings present */
#define	VL_GET_LOCKED	2	/* wirings present, map locked */

#ifdef	_KERNEL
struct vm_map;
struct vm_map_entry;

extern kern_return_t	vl_wire(struct vm_map_entry *, vm_offset_t,
				vm_offset_t, vm_prot_t);
extern kern_return_t	vl_unwire(struct vm_map_entry *, vm_offset_t,
				vm_offset_t);
extern boolean_t	vl_kwire(struct vm_map *, vm_offset_t, vm_offset_t);
extern void		vl_remove(struct vm_map *);
extern int		vl_get_wirings(struct vm_map *, vm_offset_t, long,
				       unsigned long *);

#endif	/* KERNEL */

#endif	/* !__VM_VLOCK */
