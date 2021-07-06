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
 * @(#)$RCSfile: types.h,v $ $Revision: 1.1.27.2 $ (DEC) $Date: 1998/07/24 14:01:47 $
 */
/*	@(#)types.h	1.6 90/07/19 4.1NFSSRC SMI	*/

/* 
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 *      @(#)types.h 1.20 88/02/08 SMI      
 */


/*
 * Rpc additions to <sys/types.h>
 */

#ifndef	__rpc_types_h
#define	__rpc_types_h

#include <sys/types.h>
#include <sys/malloc.h>


#define	bool_t	int
#define	enum_t	int
#define __dontcare__	-1

#ifndef FALSE
#	define	FALSE	(0)
#endif

#ifndef TRUE
#	define	TRUE	(1)
#endif

#ifndef NULL
#	define NULL 0
#endif

#ifdef sun
typedef u_longlong_t uint64;

typedef longlong_t int64;

typedef u_long uint32;

typedef long int32;

#endif /* sun */
/*
 * this file should really be conditionalized on __arch64__  and
 * __arch32__ but .......
 * 
 */
#if defined ( __intel__ ) && defined ( __arch32__ )

typedef long long longlong_t;
typedef unsigned long long u_longlong_t;
typedef u_longlong_t uint64;
typedef longlong_t int64;
typedef u_int uint32;
typedef int int32;

#elif defined ( __intel__ ) && defined ( __arch64__ )

typedef u_long uint64;
typedef u_long u_longlong_t;

typedef long int64;
typedef long longlong_t;

typedef u_int uint32;
typedef int int32;

#endif

#ifdef mips

typedef union {
	u_long l[2];
	double d;
} u_longlong_t;

typedef union {
	long l[2];
	double d;
} longlong_t;

typedef u_longlong_t uint64;

typedef longlong_t int64;

typedef u_long uint32;

typedef long int32;

#endif /* mips */

#ifdef __arch64__
typedef u_long uint64;
typedef u_long u_longlong_t;

typedef long int64;
typedef long longlong_t;

typedef u_int uint32;

typedef int int32;
#endif /* __arch64__ */

#ifndef	KERNEL
extern char *malloc();
#define	mem_alloc(bsize)	malloc(bsize)
#define	mem_free(ptr, bsize)	free(ptr)
#else
extern char *kalloc();
#define	kmem_alloc(bsize)	malloc((u_long)(bsize), -1, M_NFS, M_WAITOK)
#define	kmem_free(ptr, bsize)	free((void *)(ptr), M_NFS)
#define	mem_alloc(bsize)	malloc((u_long)(bsize), -1, M_NFS, M_WAITOK)
#define	mem_free(ptr, bsize)	free((void *)(ptr), M_NFS)
#endif

#ifndef _TIME_
#include <sys/time.h>
#endif

#endif	/* !__rpc_types_h */
