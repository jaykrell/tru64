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
 * @(#)$RCSfile: proplist.h,v $ $Revision: 1.1.8.1 $ (DEC) $Date: 2000/12/12 21:16:31 $
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * Copyright (c) 1989 The Regents of the University of California.
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

#ifndef _SYS_PROPLIST_H_
#define	_SYS_PROPLIST_H_

#include <sys/types.h>
#include <sys/param.h>
#include <sys/mount.h>

struct proplistname_args {
	u_int	pl_mask;
	u_int	pl_numnames;
	char	**pl_names;
};

struct proplist_buf {
	u_int	pl_entrysize;	/* Integer aligned */
	u_int	pl_flags;	/* Defined below */
	u_int	pl_namelen;	/* Including Null byte */
	u_int	pl_valuelen;
	char	pl_name[1];
	char	pl_value[1];	/* Integer aligned */
};

#define PROPLIST_NAME_MAX	255
#define PROPLIST_NUM_MAX	127

struct proplist_head {
	u_int	pl_entrysize;	/* Longword aligned */
	u_int	pl_flags;	/* Defined below */
	u_int	pl_namelen;	/* Including Null byte */
	u_int	pl_valuelen;
	char	pl_name[PROPLIST_NAME_MAX + 1];
};

#define PROPLIST_ALLIGN(pl_len) \
	(((pl_len) + 7) &~ 7)

#define SIZEOF_PROPLIST_HEAD (sizeof(struct proplist_head) - \
	(PROPLIST_NAME_MAX + 1))

#define SIZEOF_PROPLIST_ENTRY(pl_namelen, pl_valuelen) \
	((SIZEOF_PROPLIST_HEAD) + PROPLIST_ALLIGN(pl_namelen) + \
	 PROPLIST_ALLIGN(pl_valuelen))

/*
 * Values for Property list entry flag
 */
#define PLE_PROPAGATE_ON_COPY		0x1	   /* cp(1) will copy entry
						      by default */
#define PLE_FLAG_MASK			0x1	   /* Valid flag values */
#define PLE_FLAG_ALL			0xffffffff /* All flag value */

/*
 * System call multiplexer values
 */
#define SET_PROPLIST_SYSCALL	0x1
struct setargs {
	char *path;
	long follow;
	long nbytes;
	char *buf;
};

#define FSET_PROPLIST_SYSCALL	0x2
struct fsetargs {
	long fd;
	long nbytes;
	char *buf;
};

#define GET_PROPLIST_SYSCALL	0x3
struct getargs {
	char *path;
	long follow;
	struct proplistname_args *name_args;
	long nbytes;
	char *buf;
	int *min_buf_size;
};

#define FGET_PROPLIST_SYSCALL	0x4
struct fgetargs {
	long fd;
	struct proplistname_args *name_args;
	long nbytes;
	char *buf;
	int *min_buf_size;
};

#define DEL_PROPLIST_SYSCALL	0x5
struct delargs {
	char *path;
	long follow;
	struct proplistname_args *name_args;
};

#define FDEL_PROPLIST_SYSCALL	0x6
struct fdelargs {
	long fd;
	struct proplistname_args *name_args;
};

/* 
 * The following should only be used by the NFS proplist 
 * functionality.  This sets up pseudo proplist syscall 
 * structures for manipulating proplists based on NFS file 
 * handles.  The functionality is actually implemented in 
 * the security(SEC_EPROPLIST) code instead of the
 * proplist syscall code.
 */

#define HSET_PROPLIST_SYSCALL	0x7
struct hsetargs {
	fhandle_t fh;
	long nbytes;
	char *buf;
};

#define HGET_PROPLIST_SYSCALL	0x8
struct hgetargs {
	fhandle_t fh;
	struct proplistname_args *name_args;
	long nbytes;
	char *buf;
	int *min_buf_size;
};

#define HDEL_PROPLIST_SYSCALL	0x9
struct hdelargs {
	fhandle_t fh;
	struct proplistname_args *name_args;
};

#ifndef _KERNEL

_BEGIN_CPLUSPLUS
extern int getproplist __((char *, int, struct proplistname_args *, int, char *, int *));
extern int fgetproplist __((int, struct proplistname_args *, int, char *, int *));

extern int setproplist __((char *, int, int, char *));
extern int fsetproplist __((int, int, char *));

extern int delproplist __((char *, int, struct proplistname_args *));
extern int fdelproplist __((int, struct proplistname_args *));

extern int sizeof_proplist_entry __((char *, int));
extern int add_proplist_entry __((char *, int, int, char *, char **));
extern int get_proplist_entry __((char **, int **, int **, char **, char **));
_END_CPLUSPLUS

#endif /* KERNEL */

#endif	/* _SYS_PROPLIST_H_ */
