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
 *	@(#)$RCSfile: ctype.h,v $ $Revision: 4.2.13.3 $ (DEC) $Date: 1995/09/07 17:38:51 $
 */ 
/*
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */
/*
 * OSF/1 1.2
 */
/*
 * COMPONENT_NAME: (LIBCGEN) Standard C Library General Functions
 *
 * FUNCTIONS: 
 *
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1989, 1991
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 * 
 * 1.29  com/inc/ctype.h, libcchr, bos320, 9132320 7/26/91 10:30:13
 */
#ifndef _CTYPE_H_
#define _CTYPE_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>


#ifdef _ANSI_C_SOURCE
#   define _ISALPHA	0x001
#   define _ISALNUM	0x002
#   define _ISBLANK     0x004
#   define _ISCNTRL	0x008
#   define _ISDIGIT	0x010
#   define _ISGRAPH	0x020
#   define _ISLOWER	0x040
#   define _ISPRINT	0x080
#   define _ISPUNCT	0x100
#   define _ISSPACE	0x200
#   define _ISUPPER	0x400
#   define _ISXDIGIT	0x800

/*
 * Number of character classes defined above
 */
#define _NUM_CLASSES	12

extern int	isalpha __((int));
extern int	isalnum __((int));
extern int	iscntrl __((int));
extern int	isdigit __((int));
extern int	isgraph __((int));
extern int	islower __((int));
extern int	isprint __((int));
extern int	ispunct __((int));
extern int	isspace __((int));
extern int	isupper __((int));
extern int	isxdigit __((int));
extern int	toupper __((int));
extern int	tolower __((int));

#endif /* ifdef _ANSI_C_SOURCE */

#ifdef _XOPEN_SOURCE

extern int	isascii __((int));
extern int	toascii __((int));

extern int	(_toupper) __((int));
extern int	(_tolower) __((int));

#if defined(_OSF_SOURCE)
#include <sys/types.h>
#endif

#endif /* _XOPEN_SOURCE */

#if defined(_OSF_SOURCE)

#include <sys/localedef.h>

#define isalpha(c)	_ISMACRO(c,_ISALPHA)
#define isupper(c)	_ISMACRO(c,_ISUPPER)
#define islower(c)	_ISMACRO(c,_ISLOWER)
#define isdigit(c)	_ISMACRO(c,_ISDIGIT)
#define isxdigit(c)	_ISMACRO(c,_ISXDIGIT)
#define isspace(c)	_ISMACRO(c,_ISSPACE)
#define ispunct(c)	_ISMACRO(c,_ISPUNCT)
#define isalnum(c)	_ISMACRO(c,_ISALNUM)
#define isprint(c)	_ISMACRO(c,_ISPRINT)
#define isgraph(c)	_ISMACRO(c,_ISGRAPH)
#define iscntrl(c)	_ISMACRO(c,_ISCNTRL)

#define toupper(c)	_TOUPPER(c)
#define tolower(c)	_TOLOWER(c)

#endif /* _OSF_SOURCE */

#if !defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE)
#define _toupper toupper
#define _tolower tolower

#define isascii(c)	(!((int)(c) & ~0177))
#define toascii(c)	((int)(c) & 0177)
#endif /* _POSIX_C_SOURCE || _XOPEN_SOURCE */

#ifdef __cplusplus
}
#endif
#endif /* _CTYPE_H_ */
