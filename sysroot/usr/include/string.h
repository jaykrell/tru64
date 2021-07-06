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
 *	@(#)$RCSfile: string.h,v $ $Revision: 4.3.24.1 $ (DEC) $Date: 2000/10/30 17:57:43 $
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


/*
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _STRING_H_
#define _STRING_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>
#include <sys/types.h>

/*
 *
 *      The ANSI standard requires that certain values be in string.h.
 *      It also requires that ONLY these values are present.
 *      However, this file defines other useful values. If you wish to comply
 *	strictly to the standard and not have this file define these other
 *	values, define the macro _ANSI_C_SOURCE.
 *
 */

#ifdef   _ANSI_C_SOURCE

/*
 *      The following definitions (NULL, size_t) are included in <sys/types.h>.
 *      They are also included here to comply with ANSI standards.
 */

#ifndef NULL
#define NULL    0L
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long   size_t;
#endif

#ifdef	_NONSTD_TYPES
extern char	*memchr __((const void *, int , size_t ));
extern char	*memcpy __I((void *, const void *, size_t ));
extern char	*memset __I((void *, int , size_t ));
extern int	strcspn __((const char *, const char *));
extern int	strlen __I((const char *));
extern int	strspn __((const char *, const char *));
#else
extern void	*memchr __((const void *, int , size_t ));
extern void	*memcpy __I((void *, const void *, size_t ));
extern void	*memset __I((void *, int , size_t ));
extern size_t 	strcspn __((const char *, const char *));
extern size_t	strlen __I((const char *));
extern size_t	strspn __((const char *, const char *));
#endif	/* _NONSTD_TYPES */


extern void 	*memmove __I((void *, const void *, size_t ));
extern char 	*strcpy __I((char *, const char *));
extern char 	*strncpy __((char *, const char *, size_t ));
extern char 	*strcat __((char *, const char *));
extern char	*strncat __((char *, const char *, size_t ));
extern int 	memcmp __((const void *, const void *,size_t ));
extern int	strcmp __((const char *, const char *));
extern int	strcoll __((const char *, const char *));
extern int	strncmp __((const char *,const char *,size_t ));
extern size_t 	strxfrm __((char *, const char *, size_t ));
extern char	*strchr __((const char *, int ));
extern char	*strpbrk __((const char *, const char *));
extern char	*strrchr __((const char *, int ));
extern char	*strstr __((const char *, const char *));
extern char 	*strtok __((char *, const char *));
extern char 	*strerror __((int));
#if defined(_REENTRANT) || defined(_THREAD_SAFE)
		/* _POSIX_REENTRANT_FUNCTIONS */
extern int	strerror_r __((int, char *, int));
#endif
extern char 	*strtok_r __((char *, const char *, char **)); 

#ifdef _INTRINSICS
#pragma intrinsic(strcpy,strlen,memcpy,memmove,memset)
#endif
#endif /*_ANSI_C_SOURCE */

#ifdef	_XOPEN_SOURCE

#ifdef	_NONSTD_TYPES
extern char	*memccpy();
extern int	memvalid();
#else
extern void	*memccpy __((void *, const void *, int , size_t ));
extern int      memvalid __((void *, size_t, int));
#endif	/* _NONSTD_TYPES */

#endif	/* _XOPEN_SOURCE */


#ifdef _AES_SOURCE

#ifndef __SVID__
extern void swab __((const void *, void *, ssize_t));
#endif

#endif  /* _AES_SOURCE */

#if defined(_XOPEN_SOURCE_EXTENDED) || defined(_OSF_SOURCE)
extern char *strdup __((const char *));
#endif

#ifdef _OSF_SOURCE

/* pick up bcmp, bcopy, bzero, ffs, index, rindex, strcasecmp */
/* and strncasecmp from <strings.h> */
#include <strings.h>

/* declaration & renaming block for basename() & dirname() */
#if defined(_XOPEN_SOURCE_EXTENDED) && !defined(_LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix "_E"
#else
#define basename(__a) _Ebasename(__a)
#define dirname(__a) _Edirname(__a)
#endif
#endif  /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */
extern char    * __R(basename) __((char  *));
extern char    * __R(dirname) __((char  *));
#if defined(_XOPEN_SOURCE_EXTENDED) && !defined(_LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix ""
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */

#if defined(_REENTRANT) || defined(_THREAD_SAFE)

/* declaration & renaming block for dirname_r() */
#if defined(_XOPEN_SOURCE_EXTENDED) && !defined(_LIBC_POLLUTION_H_)
#define dirname_r(__a,__b,__c) _Edirname_r(__a,__b,__c)
#endif
extern int  __R(dirname_r)  __((char *, char *, int));

#endif  /* _REENTRANT || _THREAD_SAFE */

#endif /* _OSF_SOURCE */

#ifdef __cplusplus
}
#endif
#endif /* _STRING_H_ */
