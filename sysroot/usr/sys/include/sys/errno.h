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
 *	@(#)$RCSfile: errno.h,v $ $Revision: 4.2.30.1 $ (DEC) $Date: 2000/10/12 17:14:10 $
 */ 
/*
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */
/*
 * OSF/1 1.2
 */
/* @(#)errno.h	1.16  com/inc/sys,3.1,8943 10/23/89 18:36:36 */
/*
 * COMPONENT_NAME: errno.h
 *                                                                    
 *
 * Copyright International Business Machines Corp. 1985, 1989
 * All Rights Reserved
 * Licensed Material - Property of IBM
 *
 */                                                                   

#ifndef _SYS_ERRNO_H_
#define _SYS_ERRNO_H_
#include <standards.h>

/*
 *
 *      The ANSI, POSIX, and XOPEN standards require that certain values be
 *	in errno.h.  The standards allow additional macro definitions,
 *      beginning with an E and an uppercase letter.
 *
 *      This header includes all the ANSI, POSIX, and XOPEN required entries.  
 *
 */
 
#if defined(_ANSI_C_SOURCE) || defined(__LANGUAGE_ASSEMBLY__)
/*
 * Error codes
 */

#ifndef	_KERNEL

#ifdef	__LANGUAGE_ASSEMBLY__

.extern errno 4

#else
/*
 * Per thread errno is provided by the threads provider. 
 */
#ifdef	__cplusplus
extern "C" {
#endif	/* __cplusplus */

extern int *_errno __((void));
extern int _Geterrno __((void));
extern int _Seterrno __((int));

#ifdef _OSF_SOURCE
extern int __geterrno __((void));
#if defined(_TIS_OS_) || defined(_TIS_INCLUDE) || defined(_THREAD_SAFE)
extern void __seterrno __((int));
#else
extern int __seterrno __((int));
#endif /*_TIS_OS_  || _TIS_INCLUDE || _THREAD_SAFE */
#endif /*_OSF_SOURCE*/

#ifdef	_REENTRANT
#define errno	(*_errno())
#else
extern int errno;
#endif	/* _REENTRANT */

#ifdef	__cplusplus
}
#endif	/* __cplusplus */

#endif	/* __LANGUAGE_ASSEMBLY__ */

#endif  /* !_KERNEL */


#define ESUCCESS        0               /* Successful */
#define EPERM		1		/* Not owner */
#define ENOENT		2		/* No such file or directory */
#define ESRCH		3		/* No such process */
#define EINTR		4		/* Interrupted system call */
#define EIO		5		/* I/O error */
#define ENXIO		6		/* No such device or address */
#define E2BIG		7		/* Arg list too long */
#define ENOEXEC		8		/* Exec format error */
#define EBADF		9		/* Bad file number */
#define ECHILD		10		/* No children */
#define EDEADLK		11		/* Operation would cause deadlock */
#define ENOMEM		12		/* Not enough core */
#define EACCES		13		/* Permission denied */
#define EFAULT		14		/* Bad address */
#define ENOTBLK		15		/* Block device required */
#define EBUSY		16		/* Mount device busy */
#define EEXIST		17		/* File exists */
#define EXDEV		18		/* Cross-device link */
#define ENODEV		19		/* No such device */
#define ENOTDIR		20		/* Not a directory*/
#define EISDIR		21		/* Is a directory */
#define EINVAL		22		/* Invalid argument */
#define ENFILE		23		/* File table overflow */
#define EMFILE		24		/* Too many open files */
#define ENOTTY		25		/* Not a typewriter */
#define ETXTBSY		26		/* Text file busy */
#define EFBIG		27		/* File too large */
#define ENOSPC		28		/* No space left on device */
#define ESPIPE		29		/* Illegal seek */
#define EROFS		30		/* Read-only file system */
#define EMLINK		31		/* Too many links */
#define EPIPE		32		/* Broken pipe */

/* math software */
#define EDOM		33		/* Argument too large */
#define ERANGE		34		/* Result too large */
			/* STREAMS: packet size of of configured range */

/* non-blocking and interrupt i/o */
#define EWOULDBLOCK	35		/* Operation would block */
#define EAGAIN		EWOULDBLOCK	/* ditto */
#define EINPROGRESS	36		/* Operation now in progress */
#define EALREADY	37		/* Operation already in progress */

/* ipc/network software */

	/* argument errors */
#define ENOTSOCK	38		/* Socket operation on non-socket */
#define EDESTADDRREQ	39		/* Destination address required */
#define EMSGSIZE	40		/* Message too long */
#define EPROTOTYPE	41		/* Protocol wrong type for socket */
#define ENOPROTOOPT	42		/* Protocol not available */
#define EPROTONOSUPPORT	43		/* Protocol not supported */
#define ESOCKTNOSUPPORT	44		/* Socket type not supported */
#define EOPNOTSUPP	45		/* Operation not supported on socket */
#define EPFNOSUPPORT	46		/* Protocol family not supported */
#define EAFNOSUPPORT	47		/* Address family not supported by protocol family */
#define EADDRINUSE	48		/* Address already in use */
#define EADDRNOTAVAIL	49		/* Can't assign requested address */

	/* operational errors */
#define ENETDOWN	50		/* Network is down */
#define ENETUNREACH	51		/* Network is unreachable */
#define ENETRESET	52		/* Network dropped connection on reset */
#define ECONNABORTED	53		/* Software caused connection abort */
#define ECONNRESET	54		/* Connection reset by peer */
#define ENOBUFS		55		/* No buffer space available */
#define EISCONN		56		/* Socket is already connected */
#define ENOTCONN	57		/* Socket is not connected */
#define ESHUTDOWN	58		/* Can't send after socket shutdown */
#define ETOOMANYREFS	59		/* Too many references: can't splice */
#define ETIMEDOUT	60		/* Connection timed out */
#define ECONNREFUSED	61		/* Connection refused */

	/* */
#define ELOOP		62		/* Too many levels of symbolic links */
#define ENAMETOOLONG	63		/* File name too long */

/* should be rearranged */
#define EHOSTDOWN	64		/* Host is down */
#define EHOSTUNREACH	65		/* No route to host */
#define ENOTEMPTY	66		/* Directory not empty */

/* quotas & mush */
#define EPROCLIM	67		/* Too many processes */
#define EUSERS		68		/* Too many users */
#define EDQUOT		69		/* Disc quota exceeded */

/*
 *  NFS errors.
 */
#define ESTALE		70		/* Stale NFS file handle */
#define EREMOTE		71		/* Too many levels of remote in path */
#define EBADRPC		72		/* RPC struct is bad */
#define ERPCMISMATCH	73		/* RPC version wrong */
#define EPROGUNAVAIL	74		/* RPC prog. not avail */
#define EPROGMISMATCH	75		/* Program version wrong */
#define EPROCUNAVAIL	76		/* Bad procedure for program */

#define ENOLCK		77		/* No locks available */
#define ENOSYS		78		/* Function not implemented */

#define	EFTYPE		79		/* Inappropriate file type or format */

/* Sys V IPC errors */
#define ENOMSG		80		/* No msg matches receive request */
#define EIDRM		81		/* Msg queue id has been removed */

/* STREAMS */

#define	ENOSR		82		/* Out of STREAMS resources */
#define	ETIME		83		/* System call timed out */
#define	EBADMSG		84		/* Next message has wrong type */
#define EPROTO		85		/* STREAMS protocol error */
#define ENODATA		86		/* No message on stream head read q */
#define ENOSTR		87		/* fd not associated with a stream */
/* Not visible outside kernel */
#define ECLONEME	88		/* Tells open to clone the device */

/* Filesystem */

#define	EDIRTY		89		/* Mounting a dirty fs w/o force */

/* Loader errors */

#define	EDUPPKG		90		/* duplicate package name on install */
#define	EVERSION	91		/* version number mismatch */
#define	ENOPKG		92		/* unresolved package name */
#define	ENOSYM		93		/* unresolved symbol name */

#define ECANCELED	94		/* operation canceled */
#define EFAIL		95		/* cannot start operation */
#define EINPROG		97		/* operation (now) in progress */
#define EMTIMERS	98		/* too many timers */
#define ENOTSUP		99		/* function not implemented */
#define EAIO		100		/* internal AIO operation complete */

/* Spec1170 errors */

#if defined(_XOPEN_SOURCE_EXTENDED) || defined(_LIBC_POLLUTION_H_) || defined(_KERNEL)

#define EMULTIHOP		101		/* Reserved */
#define ENOLINK			102		/* Reserved */
#define EOVERFLOW		103		/* Value too large to be */
						/*   stored in data type */

#endif  /* _XOPEN_SOURCE_EXTENDED || _KERNEL */

/* BSD 4.3 RENO */
#define EILSEQ          116     /* Invalid wide character */

#ifdef _KERNEL
/* pseudo-errors returned inside kernel to modify return to process */
#define	ERESTART	(-1)		/* restart syscall */
#define	EJUSTRETURN	(-2)		/* don't modify regs, just return */
#define EEMULATE	(-3)		/* EJUSTRETURN + emulation */
#endif

/* Internal Disk/Block Device error codes */
/*
 * These error codes are used in the b_error field of the struct buf,
 * and should never be seen outside the kernel. EMEDIA is returned by
 * a disk driver to indicate a hard ECC error, or similar disk media
 * failure. The caller uses this to distinguish media failures (which
 * it may wish to relocate or otherwise correct) from drive offline 
 * or other problems that would be futile to retry or attempt to correct.
 * The b_resid field should indicate the data successfully transferred
 * before the error occurred.
 * The filesystem always converts this to EIO before returning to user space.
 * ESOFT indicates a correctable error occurred: the data transfer 
 * occurred correctly, but an ECC error was encountered. The caller
 * may choose to take corrective action based on this indication.
 * ERELOCATED is a 'success' code indicating that a defect relocation
 * request was performed successfully.
 */
#define	ESOFT		123
#define	EMEDIA		124
#define	ERELOCATED	125

#ifdef _KERNEL
/* pseudo-errors used by CFS quota suppport - never seen outside kernel */
#define	E_USROKAY_GRPOKAY	1000
#define	E_USROKAY_GRPSOFT	1001
#define	E_USROKAY_GRPHARD	1002
#define	E_USRSOFT_GRPOKAY	1003
#define	E_USRSOFT_GRPSOFT	1004
#define	E_USRSOFT_GRPHARD	1005
#define	E_USRHARD_GRPOKAY	1006
#define	E_USRHARD_GRPSOFT	1007
#define	E_USRHARD_GRPHARD	1008
#endif

#endif /* _ANSI_C_SOURCE */

#if defined(_OSF_SOURCE) && !defined(_KERNEL)

#ifdef	__cplusplus
extern "C" {
#endif	/* __cplusplus */

extern void perror __((const char *));
extern char *sys_errlist[];
extern int sys_nerr;

#ifdef	__cplusplus
}
#endif	/* __cplusplus */

#endif	/* defined(_OSF_SOURCE) && !defined(_KERNEL) */

#endif /* _SYS_ERRNO_H_ */
