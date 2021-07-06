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
 *	@(#)$RCSfile: s5ino.h,v $ $Revision: 4.2.9.2 $ (DEC) $Date: 1999/08/16 20:09:37 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */


#ifndef	_S5_INO_H_
#define _S5_INO_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

/* Inode structure as it appears on a disk block. */

struct s5dinode
{
	ushort_t  di_mode;	/* mode and type of file */
	short	  di_nlink;    	/* number of links to file */
	ushort_t  di_uid;      	/* owner's user id */
	ushort_t  di_gid;      	/* owner's group id */
#ifdef __arch64__
	long	di_size;	/*  8: number of bytes in file */
#else
	quad	di_qsize;	/*  8: number of bytes in file */
#endif
	char  	di_addr[40];	/* disk block addresses */
	time_t	di_atime;   	/* time last accessed */
	time_t	di_mtime;   	/* time last modified */
	time_t	di_ctime;   	/* time created */
};

/*
 * the 40 address bytes:
 *	39 used; 13 addresses
 *	of 3 bytes each.
 */
#ifdef __cplusplus
}
#endif
#endif	/* _S5_INO_H */
