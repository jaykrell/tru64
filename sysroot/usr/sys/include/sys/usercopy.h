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
 * @(#)$RCSfile: usercopy.h,v $ $Revision: 1.1.10.4 $ (DEC) $Date: 1999/03/26 21:58:42 $
 */
/*
 * (c) Copyright 1990, 1991, 1992 OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.2
 */
/*
 * File:	sys/usercopy.h
 *
 * Purpose:	This file provides the interface definitions for the routines
 *		that copy data between user space and kernel space for the 
 *		currently executing task. These routines are implemented in
 *		machine-dependent code, but invoked from both machine-dependent
 *		and machine-independent routines.
 */

#ifndef _SYS_USERCOPY_H_
#define _SYS_USERCOPY_H_

#ifndef _KERNEL
#error This is a kernel-internal file, and defines kernel-internal functions.
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

/*
 * Routines:	copyin/copyout
 * Purpose:	Copy data between user and kernel space
 *
 * Arguments:
 *	src	location to fetch data from
 *	dst	location to store data into
 *	len	number of bytes to transfer
 *
 * Return value:
 *	0	success
 *	EFAULT	inaccessible or invalid user-space address
 *
 * Notes:
 *	These routines have no alignment restrictions in either user space
 *	or kernel space.
 */
extern int copyin(void *user_src, void *kernel_dst, size_t len);
extern int copyout(void *kernel_src, void *user_dst, size_t len);
extern int copyin_try(void *user_src, void *kernel_dst, size_t len);
extern int copyout_try(void *kernel_src, void *user_dst, size_t len);
extern int copyin_poll(void *user_src, void *kernel_dst, long elements);
extern int copyout_poll(void *kernel_src, void *user_dst, long elements);

/* uzero() zeros user space (like a copyout() from a zeroed kernel buffer) */
extern int uzero(void *user_dst, size_t len);


/*
 * Routines:	copyinstr/copyoutstr
 * Purpose:	Copy NULL-terminated strings in and out of the kernel.
 * 
 * Arguments:
 *	src	starting address of source string.
 *	dest	starting address of destination buffer.
 *	maxlength	maximum number of bytes to be transferred, including
 *		NULL termination byte.
 *	lengthcopied 	actual number of bytes transferred, including NULL
 *		termination byte.
 *
 * Return value:
 *	0	success
 *	EFAULT	inaccessible or invalid user-space address
 *	ENAMETOOLONG string exceeded the maxlength value. Note that in this case,
 *		*lengthcopied bytes have been transferred, but the resulting
 *		string is not NULL-terminated.
 */
extern int copyinstr(
		void  *user_src,
		void  *kernel_dest,
		int    maxlength,
		int   *lengthcopied);
extern int copyoutstr(
		void  *kernel_src,
		void  *user_dest,
		int    maxlength,
		int   *lengthcopied);
/*
 * Routines:	fubyte/fuword/subyte/suword:
 * Purpose:	Fetch or store a data item to/from user data space.
 * 
 * Routines:	fuibyte/fuiword/suibyte/suiword:
 * Purpose:	Fetch or store a data item to/from user data space.
 *
 * On systems that do not distinguish between instruction and data space,
 * the two sets of routines are completely interchangeable.
 *
 * The return value of the fetch functions is the data item from the user
 * address space. A -1 is returned on error. In the case of fuword() and
 * fuiword(), this restricts the range of values that may be retrieved by
 * this routine, since it is not possible to distinguish between the error
 * return and an equivalent retrieved value. Since fuword is used to fetch
 * pointers from user space, this effectively invalidates (caddr_t)-1 as a
 * pointer. [Note that the system interfaces to mmap() and sbrk() cause the
 * same problem.]
 *
 * The return value of the store functions is a 0 for success, or
 * -1 on failure.
 */
extern int fubyte(void   *user_src);
extern int fuibyte(void  *user_src);
extern int fuword(void   *user_src);
extern int fuiword(void  *user_src);

extern int subyte(void   *user_dest, int data);
extern int suibyte(void  *user_dest, int data);
extern int suword(void   *user_dest, int data);
extern int suiword(void  *user_dest, int data);

#ifdef __cplusplus
}
#endif

#endif /* _SYS_USERCOPY_H_ */
