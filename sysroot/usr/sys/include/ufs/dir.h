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
 *	@(#)dir.h	9.3	(ULTRIX/OSF)	10/23/91
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * Copyright (c) 1982, 1986, 1989 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *

 */

#ifndef	_UFS_DIR_H_
#define _UFS_DIR_H_

#include <sys/types.h>
#include <sys/param.h>		/* for DEV_BSIZE */

/*
 * A directory consists of some number of blocks of DIRBLKSIZ
 * bytes, where DIRBLKSIZ is chosen such that it can be transferred
 * to disk in a single atomic operation (e.g. 512 bytes on most machines).
 *
 * Each DIRBLKSIZ byte block contains some number of directory entry
 * structures, which are of variable length.  Each directory entry has
 * a struct direct at the front of it, containing its inode number,
 * the length of the entry, and the length of the name contained in
 * the entry.  These are followed by the name padded to a 4 byte boundary
 * with null bytes.  All names are guaranteed null terminated.
 * The maximum length of a name in a directory is MAXNAMLEN.
 *
 * The macro DIRSIZ(dp) gives the amount of space required to represent
 * a directory entry.  Free space in a directory is represented by
 * entries which have dp->d_reclen > DIRSIZ(dp).  All DIRBLKSIZ bytes
 * in a directory block are claimed by the directory entries.  This
 * usually results in the last entry in a directory having a large
 * dp->d_reclen.  When entries are deleted from a directory, the
 * space is returned to the previous entry in the same directory
 * block by increasing its dp->d_reclen.  If the first entry of
 * a directory block is free, then its dp->d_ino is set to 0.
 * Entries other than the first in a directory do not normally have
 * dp->d_ino set to 0.
 */
#define DIRBLKSIZ	DEV_BSIZE

#ifdef _KERNEL
/*
 * Template for manipulating directories.
 * Should use struct direct's, but the name field
 * is MAXNAMLEN - 1, and this just won't do.
 */
struct dirtemplate {
	u_int	dot_ino;
	short	dot_reclen;
	short	dot_namlen;
	char	dot_name[4];		/* must be multiple of 4 */
	u_int	dotdot_ino;
	short	dotdot_reclen;
	short	dotdot_namlen;
	char	dotdot_name[4];		/* ditto */
};


#if SEC_MAC
#include <sys/security.h>	/* For tag_t */

/* template with sensitivity label and information label*/
struct mlsd_dirtemplate {
	ino_t		dot_ino;
	short		dot_reclen;
	short		dot_namlen;
	char		dot_name[4];		/* must be multiple of 4 */
	tag_t		dot_sl;			/* sensitivity tag */
	tag_t		dot_il;			/* info label  tag */
	ino_t		dotdot_ino;
	short		dotdot_reclen;
	short		dotdot_namlen;
	char		dotdot_name[4];		/* ditto */
	tag_t		dotdot_sl;		/* sensitivity tag */
	tag_t		dotdot_il;		/* info label  tag */
};

/*
 * The size of the tag array for multi-level security directories.
 * The format of the directory is based off of this.
 * Note that this is the same for ILB/non-ILB systems.  i.e. there
 * is only one format of MLSD directories.
 */
#define MLSD_NUMTAGS	2

/*
 * Subscripts for directory entry tag array.
 * The Sensitivity label comes first, followed by the Information label.
 */
#define MLSD_SL		0
#define MLSD_IL		1

/*
 * The MLSD_DIRSIZ macro gives the minimum record length which will hold
 * the extended directory entry.  This requires the amount of space in 
 * struct dirent without the d_name field, plus enough space for the 
 * name with a terminating null byte (dp->d_namlen+1), plus the entries'
 * SL and IL tag, rounded up to a 4 byte boundary.
 * XXX The "256" below (the size of d_name) is subject to compiler alignment.
 */
#define MLSD_TAG_OFFSET(dp) ((int) (sizeof(struct dirent) - 256) + \
				   (((dp)->d_namlen+1 + 3) &~ 3))

#define MLSD_DIRSIZ(dp)	(MLSD_TAG_OFFSET(dp) + (sizeof(tag_t) * MLSD_NUMTAGS))
		
#define MLSD_DIR_TO_TAG(dp) ((tag_t *) ((char *)(dp) + MLSD_TAG_OFFSET(dp)))

#endif /* SEC_MAC */
#endif /* _KERNEL */

#include <dirent.h>

/* on-disk dirent: to help avoid confusion */
struct ufs_od_dirent {
    struct dirent dent;
};

#define ODIRSIZ(odp) DIRSIZ(&(odp)->dent)

#define od_ino	dent.d_ino
#define	od_reclen	dent.d_reclen
#define	od_namlen	dent.d_namlen
#define	od_name	dent.d_name
#define	od_fileno	dent.d_fileno

#endif	/* _UFS_DIR_H_ */
