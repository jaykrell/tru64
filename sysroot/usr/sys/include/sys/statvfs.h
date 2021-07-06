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
 * @(#)$RCSfile: statvfs.h,v $ $Revision: 1.1.12.1 $ (DEC) $Date: 1999/11/30 13:53:11 $
 */

#ifndef _SYS_STATVFS_H
#define _SYS_STATVFS_H

#include <standards.h>
#include <sys/types.h>

/*
 * Structure returned by statvfs.
 */

#ifdef _XOPEN_SOURCE_EXTENDED
#define	ST_FSTYPSZ	16
#else
#define	FSTYPSZ	16
#endif /* _XOPEN_SOURCE_EXTENDED */

#if _XOPEN_SOURCE>=500          /* see the "standards" man page */
#define __FSBLKCNT_T fsblkcnt_t
#define __FSFILCNT_T fsfilcnt_t
#else   /* _XOPEN_SOURCE<500 */
#define __FSBLKCNT_T unsigned long
#define __FSFILCNT_T unsigned long
#endif  /* _XOPEN_SOURCE>=500 */

typedef struct statvfs {
	unsigned long	f_bsize;		/* prefered file system block size */
	unsigned long	f_frsize;		/* fundamental file system block size */
	__FSBLKCNT_T	f_blocks;		/* total # of blocks of f_frsize on fs */
	__FSBLKCNT_T	f_bfree;		/* total # of free blocks of f_frsize */
	__FSBLKCNT_T	f_bavail;		/* # of free blocks avail to non-superuser */
	__FSFILCNT_T	f_files;		/* total # of file nodes (inodes) */
	__FSFILCNT_T	f_ffree;		/* total # of free file nodes */
	__FSFILCNT_T	f_favail;		/* # of free nodes avail to non-superuser */
	unsigned long	f_fsid;			/* file system id */
#ifdef _XOPEN_SOURCE_EXTENDED
	char	f_basetype[ST_FSTYPSZ];		/* target fs type name, null-terminated */
#else
	char	f_basetype[FSTYPSZ];		/* target fs type name, null-terminated */
#endif /* _XOPEN_SOURCE_EXTENDED */
	unsigned long	f_flag;			/* bit-mask of flags */
	unsigned long	f_namemax;		/* maximum file name length */
	char	f_fstr[32];			/* filesystem-specific string */
} statvfs_t;

/*
 * Flag definitions.
 */

#define	ST_RDONLY	0x01	/* read-only file system */
#define	ST_NOSUID	0x02	/* does not support setuid/setgid semantics */

#ifndef _KERNEL

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__cplusplus) || defined(__STDC__)
int statvfs(const char *, struct statvfs *);
int fstatvfs(int, struct statvfs *);
#endif

#ifdef __cplusplus
}
#endif

#endif	/* _KERNEL */

#endif	/* _SYS_STATVFS_H */
