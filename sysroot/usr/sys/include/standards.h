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
 *	@(#)$RCSfile: standards.h,v $ $Revision: 4.2.44.1 $ (DEC) $Date: 2001/09/11 15:17:07 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * standards.h
 *
 *	Modification History:
 *
 * 11-Apr-91	Peter H. Smith
 *	If _POSIX_4SOURCE is defined, define _POSIX_SOURCE if it isn't
 *      already defined.
 *
 * 01-Apr-91	Fred Canter
 *	MIPS C 2.20+, changes for -std
 *
 */

/*
 * COMPONENT_NAME: standards.h
 *                                                                    
 * ORIGIN: IBM
 *
 * Copyright International Business Machines Corp. 1988
 * All Rights Reserved
 * Licensed Material - Property of IBM
 *
 * RESTRICTED RIGHTS LEGEND
 * Use, Duplication or Disclosure by the Government is subject to
 * restrictions as set forth in paragraph (b)(3)(B) of the Rights in
 * Technical Data and Computer Software clause in DAR 7-104.9(a).
 */                                                                   
#ifndef _STANDARDS_H_
#define _STANDARDS_H_

/* 
 * For compatibility until _POSIX_4SOURCE is retired in the next
 * release.  If user defines obsolete symbol _POSIX_4SOURCE and if 
 * _POSIX_C_SOURCE is not defined, define _POSIX_C_SOURCE to be 199309L
 * (obsolete _POSIX_4SOURCE symbol maps to POSIX 1003.1b standard from 1993).
 * Also define _POSIX_SOURCE in the presence of _POSIX_4SOURCE.
 */

#ifdef _POSIX_4SOURCE
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif 
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE
#endif 
#endif /* _POSIX_4SOURCE */

/*
 * If user defines _POSIX_SOURCE and if _POSIX_C_SOURCE is not defined, 
 * define _POSIX_C_SOURCE to be 1.  (_POSIX_SOURCE maps to the POSIX 1003.1 
 * standard from 1990).
 */ 

#if !defined(_POSIX_C_SOURCE) && defined(_POSIX_SOURCE)
#define _POSIX_C_SOURCE 1
#endif

#ifdef	_XOPEN_SOURCE
#if	_XOPEN_SOURCE+0==0
#undef	_XOPEN_SOURCE
#define	_XOPEN_SOURCE	400
#elif	_XOPEN_SOURCE>=420
#ifndef	_XOPEN_SOURCE_EXTENDED
#define	_XOPEN_SOURCE_EXTENDED
#endif
#endif
#endif

/* _XOPEN_SOURCE_EXTENDED requires _XOPEN_SOURCE be defined to at least 420 */
/*
 * If user defines _POSIX_PII and if _POSIX_PII_SOCKET is not defined, 
 * define it.  If user defines _POSIX_PII_SOCKET and if _POSIX_PII is
 * not defined, define _POSIX_PII to be 199703L.  _POSIX_PII_SOCKET
 * maps to the POSIX 1003.1g/D6.6 standard from 1997.
 */ 

#if defined(_POSIX_PII) && !defined(_POSIX_PII_SOCKET)
#define _POSIX_PII_SOCKET
#endif
#if defined(_POSIX_PII_SOCKET) && !defined(_POSIX_PII)
#define _POSIX_PII 199703L
#endif



#ifdef	_XOPEN_SOURCE_EXTENDED
#ifdef	_XOPEN_SOURCE
#if	_XOPEN_SOURCE+0<420
#undef	_XOPEN_SOURCE
#define	_XOPEN_SOURCE	420
#endif
#else
#define	_XOPEN_SOURCE	420
#endif
#endif

/* _AES_SOURCE require _XOPEN_SOURCE */

#ifdef	_AES_SOURCE
#ifndef	_XOPEN_SOURCE
#define	_XOPEN_SOURCE	400
#endif
#endif

/* 
 * _XOPEN_SOURCE requires _POSIX_C_SOURCE 
 * _XOPEN_SOURCE requires _POSIX_SOURCE for backwards compatibility
 *
 * If _POSIX_C_SOURCE is not defined, define to 1990 standard signified
 * by the value 1, unless _XOPEN_SOURCE is set to a value >= XSH5.  The
 * latter value indicates a need for at least P1003.1C support.
 */

#ifdef	_XOPEN_SOURCE
#if	_XOPEN_SOURCE>=500
#ifdef	_POSIX_C_SOURCE
#if	_POSIX_C_SOURCE+0<199506L
#undef	_POSIX_C_SOURCE
#define	_POSIX_C_SOURCE	199506L
#endif
#else
#define	_POSIX_C_SOURCE	199506L
#endif
#endif
#ifndef	_POSIX_SOURCE
#define	_POSIX_SOURCE	1
#endif
#ifndef	_POSIX_C_SOURCE
#define	_POSIX_C_SOURCE	1
#endif
#endif

/* _POSIX_C_SOURCE requires _ANSI_C_SOURCE */

#ifdef _POSIX_C_SOURCE
#ifndef	_ANSI_C_SOURCE
#define	_ANSI_C_SOURCE
#endif
#endif

#ifdef _ISO_C_SOURCE
# ifndef	_ANSI_C_SOURCE
#  define	_ANSI_C_SOURCE
# endif /* _ANSI_C_SOURCE */
/* if _ISO_C_SOURCE is defined but has no value, set to default */
# if	_ISO_C_SOURCE+0==0
#  undef	_ISO_C_SOURCE
#  define	_ISO_C_SOURCE	1
# endif 
#else	/* set _ISO_C_SOURCE to default if _ANSI_C_SOURCE is defined */
# ifdef	_ANSI_C_SOURCE
#    define	_ISO_C_SOURCE	1
# endif /* _ANSI_C_SOURCE */
#endif /* ! _ISO_C_SOURCE */

/*
 * If nothing was specified select a set of defaults (if anything above was set
 * then _ANSI_C_SOURCE will be set, so simplify the if below).
 */

#if (!defined(_ANSI_C_SOURCE)) && (!defined(__LANGUAGE_ASSEMBLY__))
#ifdef	_DEC_XPG
#define	_XOPEN_SOURCE_EXTENDED
#define	_XOPEN_SOURCE	500
#else
#ifdef	_DEC_XPG4R2
#define	_XOPEN_SOURCE_EXTENDED
#define	_XOPEN_SOURCE	420
#else
#define	_XOPEN_SOURCE	400
#endif
#endif
/* Set historical default environment. */
#define _AES_SOURCE
#if	defined(_PTHREAD_USE_D4)||defined(PTHREAD_USE_D4)
/* P1003.4a/D4 interface compatibility */
#define	_POSIX_C_SOURCE	199309L
#else
/* default to P1003.1c */
#define _POSIX_C_SOURCE 199506L
#endif	/* _PTHREAD_USE_D4 */
/* _XOPEN_SOURCE compatibility */
#define _POSIX_SOURCE
/* P1003.4 obsolete symbol compatibility */
#define _POSIX_4SOURCE
#define _ANSI_C_SOURCE
/* default value for _ISO_C_SOURCE if nothing specified above */
#define _ISO_C_SOURCE 1
#ifndef	_OSF_SOURCE
#define _OSF_SOURCE
#endif
#endif /* (!defined(_ANSI_C_SOURCE)) && (!defined(__LANGUAGE_ASSEMBLY__)) */

#ifdef __LANGUAGE_ASSEMBLY__
#define _OSF_SOURCE
#endif

/* macros to simplify C++ ifdef blocks */
#ifdef __cplusplus
#ifndef _BEGIN_CPLUSPLUS
#define _BEGIN_CPLUSPLUS extern "C" {
#endif
#ifndef _END_CPLUSPLUS
#define _END_CPLUSPLUS }
#endif
#else
#ifndef _BEGIN_CPLUSPLUS
#define _BEGIN_CPLUSPLUS
#endif
#ifndef _END_CPLUSPLUS
#define _END_CPLUSPLUS
#endif
#endif

/* automation for non ANSI compilers */
/*
 * GNU and MIPS C compilers define __STDC__ differently.
 *	MIPS: -std0 = undefined, -std = 0, -std1 = 1
 *	GNU:  -traditional = undefined, otherwise = 1
 */
#ifdef __GNUC__

#if !__STDC__
#ifndef _NO_PROTO
#define _NO_PROTO
#endif
#ifndef _NONSTD_TYPES
#define _NONSTD_TYPES
#endif
#endif

#else	/* !__GNUC__ */

#if !defined(__STDC__) && !defined(__cplusplus)
#ifndef _NO_PROTO
#define _NO_PROTO
#endif
#ifndef _NONSTD_TYPES
#define _NONSTD_TYPES
#endif
#endif

#if defined(__cplusplus) && !defined(__LANGUAGE_C__)
#define __LANGUAGE_C__
#endif

#endif	/* __GNUC__ */

/* support for older C++ compilers that define __unix instead */
#if defined(__cplusplus) && defined(__unix)
#ifndef __unix__
#define __unix__
#endif
#endif

#ifdef _NO_PROTO
#define __(__args__)	()
#else /* _NO_PROTO */
#define __(__args__)	__args__
#endif /* _NO_PROTO */

/* Intrinsic prototype macro. This should be used for intrinsic */
/* functions that are prototyped in the standard header files.  */
/* Note that when compiled -D_INTRINSICS, we always want to     */
/* expand to full prototypes to provide argument type checking. */
#if defined(_NO_PROTO) && !defined(_INTRINSICS)
#define __I(__args__)	()
#else
#define __I(__args__)	__args__
#endif

/* ISO C99 declaration renaming for changed prototype support */
/* #pragma extern_prefix handles this for DECC */
#if (_ISO_C_SOURCE>=19990L) && !defined(_LIBC_POLLUTION_H_) && !defined(__DECC)
#define __C99(__dname__) _C##__dname__
#else
#define __C99(__dname__) __dname__
#endif /* _ISO_C_SOURCE>=19990L && !_LIBC_POLLUTION_H_ && !__DECC */

/* UNIX98 declaration renaming for changed prototype support */
/* #pragma extern_prefix handles this for DECC */
#if (_XOPEN_SOURCE >=500) && !defined(_LIBC_POLLUTION_H_) && !defined(__DECC)
#define __R500(__dname__) _E##__dname__
#else
#define __R500(__dname__) __dname__
#endif /* _XOPEN_SOURCE>=500 && !_LIBC_POLLUTION_H_ && !__DECC */

/* spec1170 (XPG4.2 or later) declaration renaming for _NO_PROTO () support */
/* #pragma extern_prefix handles this for DECC */
#if defined(_XOPEN_SOURCE_EXTENDED) && !defined(_LIBC_POLLUTION_H_) && !defined(__DECC)
#define __R(__dname__) _E##__dname__
#else
#define __R(__dname__) __dname__
#endif /* (_XOPEN_SOURCE_EXTENDED) && !_LIBC_POLLUTION_H_ && !__DECC */

/* Combination XPG5 or later **OR** ISO C 1994 release (wide character 
 * support enabled)  declaration renaming for _NO_PROTO () support */
/* #pragma extern_prefix handles this for DECC */
#if (_XOPEN_SOURCE >= 500 || __STDC_VERSION__ == 199409) && !defined(_LIBC_POLLUTION_H_) && !defined(__DECC)
#define __R5C94(__dname__) _E##__dname__
#else
#define __R5C94(__dname__) __dname__
#endif /* (_XOPEN_SOURCE >= 500 || __STDC_VERSION__ == 199409) && !_LIBC_POLLUTION_H_ && !__DECC */

/* __V40_OBJ_COMPAT declaration renaming for _NO_PROTO () support */
/* #pragma extern_prefix handles this for DECC */
#if !defined(__V40_OBJ_COMPAT) && !defined(_LIBC_POLLUTION_H_) && !defined (__DECC)
#define __V40_OC(__dname__) _E##__dname__
#else
#define __V40_OC(__dname__) __dname__
#endif /* !__V40_OBJ_COMPAT && !_LIBC_POLLUTION_H_ && !__DECC */

/* POSIX 1003.1g declaration renaming for _NO_PROTO () support */
/* #pragma extern_prefix handles this for DECC */
#if defined(_POSIX_PII) && !defined(_LIBC_POLLUTION_H_) && !defined(__DECC)
#define __PII(__dname__) _P##__dname__
/* POSIX Sockets also need the XOPEN flavors of a few things */
#define __PIIX(__dname__) _E##__dname__
#else
#define __PII(__dname__) __dname__
#define __PIIX(__dname__) __dname__
#endif /* _POSIX_PII && !_LIBC_POLLUTION_H_ && !__DECC */

/* POSIX P1003.1C declaration renaming for _NO_PROTO support */
/* #pragma extern_prefix handles this for DECC */
#if _POSIX_C_SOURCE>=199506L && !defined(_LIBC_POLLUTION_H_) && !defined(__DECC)
#define	__P_C(__dname__)	_P##__dname__
#else
#define	__P_C(__dname__)	__dname__
#endif

#if defined(__LANGUAGE_PASCAL__)
#undef _AES_SOURCE
#undef _XOPEN_SOURCE_EXTENDED
#undef _XOPEN_SOURCE
#undef _POSIX_SOURCE
#undef _POSIX_C_SOURCE
#undef _POSIX_PII
#undef _POSIX_PII_SOCKET
#undef _ANSI_C_SOURCE
#undef _OSF_SOURCE
#endif /* __LANGUAGE_PASCAL__ */

#endif /* _STANDARDS_H_ */
