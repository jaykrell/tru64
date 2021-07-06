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
 * @(#)$RCSfile: pt.h,v $ $Revision: 1.1.10.2 $ (DEC) $Date: 1997/03/03 15:38:30 $
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/* 
 * derived from fudge.xper.h	2.1	(ULTRIX/OSF)	12/3/90
 */

#ifndef _COMMON_PT_H_
#define _COMMON_PT_H_

#ifndef PT_MAGIC
#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#define PT_MAGIC	0x032957	/* Partition magic number */
#define PT_VALID	1		/* Indicates if struct is valid */
 
/*
 * Structure that is used to determine the partitioning of the disk.
 * It's location is at the end of the superblock area.
 * The reason for both the cylinder offset and block offset
 * is that some of the disk drivers (most notably the uda 
 * driver) require the block offset rather than the cyl.
 * offset.
 */
struct pt {
	int	pt_magic;	/* magic no. indicating part. info exits */
	int	pt_valid;	/* set by driver if pt is current */
	struct  pt_info {
		int	pi_nblocks;	/* no. of sectors for the partition */
		daddr_t	pi_blkoff;	/* block offset for start of part. */
	} pt_part[8];
};

#if defined(_KERNEL) && defined(_USE_KERNEL_PROTOS)
extern int rsblk(void (*strategy)(struct buf *bp), dev_t dev, struct pt *pt);
#endif /* defined(_KERNEL) && defined(_USE_KERNEL_PROTOS) */

#ifdef __cplusplus
}
#endif
#endif /* PT_MAGIC */

#endif /* _COMMON_PT_H_ */
