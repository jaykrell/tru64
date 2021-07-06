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
 *	@(#)$RCSfile: uio.h,v $ $Revision: 4.2.31.1 $ (DEC) $Date: 2002/01/29 21:20:00 $
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
 * Copyright (c) 1982, 1986 The Regents of the University of California.
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

#ifndef	_SYS_UIO_H_
#define _SYS_UIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>
#include <sys/types.h>
#ifdef _OSF_SOURCE
#include <sys/limits.h>
#endif

#if !defined(__V40_OBJ_COMPAT) && !defined(_SVID3_COMPAT)
struct iovec {
#ifdef	_KERNEL
	caddr_t	iov_base;
#else
	void   *iov_base;
#endif	/* _KERNEL */
	size_t	iov_len;
};

struct __Oiovec {
#else
struct iovec {
#endif /* !__V40_OBJ_COMPAT && !_SVID3_COMPAT */
	caddr_t	iov_base;
	int	iov_len;
};
typedef struct iovec	iovec_t;

#ifdef _OSF_SOURCE

enum	uio_rw { UIO_READ, UIO_WRITE, UIO_AIORW };
typedef enum uio_rw uio_rw_t;

/*
 * Segment flag values.
 */
enum	uio_seg {
	UIO_USERSPACE,		/* from user data space */
	UIO_SYSSPACE,		/* from system space */
	UIO_USERISPACE,		/* from user I space */
	UIO_PHYSSPACE,		/* from physical address space */
	UIO_TNCICSSPACE		/* from TNC ICS space */
};

#if !defined(__V40_OBJ_COMPAT) && !defined(_SVID3_COMPAT)
struct uio {
	struct	iovec *uio_iov;
#ifndef __VMS
	off_t	uio_offset;
#else	/* __VMS */
	off64_t uio_offset;
#endif	/* __VMS */
	int	uio_iovcnt;
	ssize_t	uio_resid;
	enum	uio_seg uio_segflg;
	enum	uio_rw uio_rw;
	/*
	 * The next two fields were added to support DDI/DKI interfaces.
	 */
	int	uio_fmode;	/* File mode flags. Drivers can't set this */
	daddr_t	uio_limit;	/* Max. blk. offset for file. Drivers can't
				   set this */
	void	*uio_drv_handle;
};

struct __Ouio {
#else
struct uio {
#endif /* !__V40_OBJ_COMPAT && !_SVID3_COMPAT */
	struct	iovec *uio_iov;
#ifndef __VMS
	off_t	uio_offset;
#else	/* __VMS */
	off64_t uio_offset;
#endif	/* __VMS */
	int	uio_iovcnt;
	int	uio_resid;
	enum	uio_seg uio_segflg;
	enum	uio_rw uio_rw;
	/*
	 * The next two fields were added to support DDI/DKI interfaces.
	 */
	int	uio_fmode;	/* File mode flags. Drivers can't set this */
	daddr_t	uio_limit;	/* Max. blk. offset for file. Drivers can't
				   set this */
	void	*uio_drv_handle;
};
typedef struct uio	uio_t;

 /*
  * Limits
  */
#define UIO_MAXIOV	IOV_MAX
#define UIO_SMALLIOV	8		/* 8 on stack, else malloc */

#endif /* _OSF_SOURCE */

#if defined(_KERNEL)
#if defined(_USE_KERNEL_PROTOS)

extern int uiomove_try(void *cp, long n, struct uio *uio);
extern int uiomove(void *cp, long n, struct uio *uio);
extern int ureadc(long c, struct uio *uio);
extern int uwritec(struct uio *uio);

#endif /* defined(_USE_KERNEL_PROTOS) */
#else /* !defined(_KERNEL) */

#ifndef __VMS
#if !defined(__V40_OBJ_COMPAT) && !defined(_LIBC_POLLUTION_H_) && !defined(_SVID3_COMPAT)
#ifdef __DECC
#pragma extern_prefix "_E"
#else
#define readv(__a,__b,__c) _Ereadv(__a,__b,__c)
#define writev(__a,__b,__c) _Ewritev(__a,__b,__c)
#endif
#endif /* !__V40_OBJ_COMPAT && !_LIBC_POLLUTION_H_ && !_SVID3_COMPAT */
#endif	/* __VMS */

#if !defined(__V40_OBJ_COMPAT) && !defined(_SVID3_COMPAT)
#ifdef _NO_PROTO
extern ssize_t readv();
extern ssize_t writev();
#else
extern ssize_t readv(int, const struct iovec *, int);
extern ssize_t writev(int, const struct iovec *, int);
#endif
#else
extern ssize_t readv __((int, struct iovec *, int));
extern ssize_t writev __((int, struct iovec *, int));
#endif /* !__V40_OBJ_COMPAT && !_SVID3_COMPAT */

#ifndef __VMS
#if !defined(__V40_OBJ_COMPAT) && !defined(_LIBC_POLLUTION_H_) && !defined(_SVID3_COMPAT) && defined(__DECC)
#pragma extern_prefix ""
#endif /* __V40_OBJ_COMPAT && !_LIBC_POLLUTION_H_ && !_SVID3_COMPAT && __DECC*/
#endif	/* __VMS */

#endif	/* defined(_KERNEL) */

#ifdef __cplusplus
}
#endif
#endif	/* _SYS_UIO_H_ */
