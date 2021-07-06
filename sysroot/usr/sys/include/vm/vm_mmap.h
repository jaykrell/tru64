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
 * @(#)$RCSfile: vm_mmap.h,v $ $Revision: 1.1.7.2 $ (DEC) $Date: 1998/12/03 15:33:14 $
 */
#ifndef	__VM_MMAP__
#define	__VM_MMAP__ 1
#include <sys/types.h>
#include <sys/mman.h>

struct vp_mmap_args {
	dev_t 		a_dev;
	int 		(*a_mapfunc)();
	vm_offset_t	a_offset;
	vm_offset_t	*a_vaddr;
	vm_size_t	a_size;
	vm_prot_t	a_prot;
	vm_prot_t	a_maxprot;
	int		a_flags;
};

extern void u_dev_permit_zero_page_at_0(dev_t, vm_offset_t, struct vm_map *);

#endif	/* !__VM_MMAP__ */
