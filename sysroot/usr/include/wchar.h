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
 *	@(#)$RCSfile: wchar.h,v $ $Revision: 4.2.35.1 $ (DEC) $Date: 2001/09/11 15:17:09 $
 */ 
/*
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */
/*
 * OSF/1 1.2
 */
/* 1.5  com/inc/wchar.h, 9123320, bos320 5/16/91 09:44:57 */
/*
 * COMPONENT_NAME: (LIBCNLS) Standard C Library National Language Support
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
 */

#ifndef _WCHAR_H_
#define _WCHAR_H_

#ifdef __cplusplus
  extern "C" {
#endif

#include <standards.h>
#include <sys/types.h>
#include <stdio.h>
#include <time.h>

/*
 * UNIX 98 does not allow inclusion of this header file, and instead
 * requires that these typedefs (wctype_t & wint_t) be defined internally.
 */
#if (_XOPEN_SOURCE < 500)
# include <wctype.h>
#else
# ifndef _WCTYPE_T
#  define _WCTYPE_T
   typedef unsigned int wctype_t;
# endif
#endif /* XOPEN_SOURCE < 500 */

#ifndef WCHAR_MAX
# define WCHAR_MAX	((wchar_t)~0)
#endif

#if (_XOPEN_SOURCE >= 500) || defined(_OSF_SOURCE) || (__STDC_VERSION__ == 199409)
# ifndef WCHAR_MIN
#  define WCHAR_MIN	0
# endif
#endif

#ifndef _WINT_T
# define _WINT_T
  typedef unsigned int wint_t;         /* Wide character */
#endif

#ifndef WEOF
# define WEOF	(wint_t)(-1)
#endif /* WEOF */

#ifndef _MBSTATE_T
# define _MBSTATE_T
  typedef struct {
    void	*__hdr;		/* pointer to _LC_object_t */
    void	*__attrobj;	/* pointer to attribute object */
    void	*__state;	/* currently unused state flag */
  } mbstate_t;
#endif

/* ----------- PROTOTYPES ------------ */

/*
 * The following are the function prototypes as defined by the specification
 * Compile flags are added to identify and select prototypes that have 
 * changes from one specification level to another.
 */
#if (_XOPEN_SOURCE >= 500 ) || defined(_OSF_SOURCE) || (__STDC_VERSION__ == 199409)
 extern wint_t	btowc		__((int));
 extern int	fwprintf	__((FILE *, const wchar_t *, ...));
 extern int	fwscanf		__((FILE *, const wchar_t *, ...));
#endif /* _XOPEN_SOURCE || _OSF_SOURCE || __STDC_VERSION__ */
/*
 * The location of these definitions differs between XOPEN and ISO specs
 * The prototype should match those in the wctypes.h file.
 * Guard flags protect against multiple extern definitions, just in case.
 */
#if (_XOPEN_SOURCE >= 500)
extern int	iswalnum 	__((wint_t));
extern int	iswalpha 	__((wint_t));
extern int	iswcntrl 	__((wint_t));
extern int	iswdigit 	__((wint_t));
extern int	iswgraph 	__((wint_t));
extern int	iswlower 	__((wint_t));
extern int	iswprint 	__((wint_t));
extern int	iswpunct 	__((wint_t));
extern int	iswspace 	__((wint_t));
extern int	iswupper 	__((wint_t));
extern int	iswxdigit 	__((wint_t));
extern int	iswctype 	__((wint_t, wctype_t));
#endif /* XOPEN_SOURCE >= 500 */
extern wint_t	fgetwc		__((FILE *));
extern wchar_t *fgetws		__((wchar_t *, int, FILE *));
#if (_XOPEN_SOURCE >= 500) || (__STDC_VERSION__ == 199409)
 extern wint_t	fputwc		__((wchar_t,FILE *));
#else
 extern wint_t	fputwc		__((wint_t,FILE *));
#endif /* _XOPEN_SOURCE !! __STDC_VERSION */
extern int	fputws		__((const wchar_t *, FILE *));
#if (_XOPEN_SOURCE >= 500) || (__STDC_VERSION__ == 199409)
 extern int	fwide		__((FILE *, int)); 
#endif /* _XOPEN_SOURCE !! __STDC_VERSION */
extern wint_t	getwc		__((FILE *));
extern wint_t	getwchar	__((void));
#if (_XOPEN_SOURCE >= 500 ) || defined(_OSF_SOURCE) || (__STDC_VERSION__ == 199409)
 extern int	mbsinit		__((const mbstate_t *));
 extern size_t	mbrlen		__((const char *, size_t, mbstate_t *));
 extern size_t	mbrtowc		__((wchar_t *, const char *, size_t, mbstate_t *));
 extern size_t	mbsrtowcs	__((wchar_t *, const char **, size_t, mbstate_t *));
#endif /* _XOPEN_SOURCE || _OSF_SOURCE || __STDC_VERSION__ */
#if (_XOPEN_SOURCE >= 500) || (__STDC_VERSION__ == 199409)
 extern wint_t	putwc		__((wchar_t, FILE *));
 extern wint_t	putwchar	__((wchar_t));
#else 
 extern wint_t	putwc		__((wint_t, FILE *));
 extern wint_t	putwchar	__((wint_t));
#endif /* _XOPEN_SOURCE || __STDC_VERSION */
#if (_XOPEN_SOURCE >= 500 ) || defined(_OSF_SOURCE) || (__STDC_VERSION__ == 199409)
 extern int	swprintf	__((wchar_t *, size_t, const wchar_t *, ...));
 extern int	swscanf		__((const wchar_t *, const wchar_t *, ...));
#endif /* _XOPEN_SOURCE || _OSF_SOURCE || __STDC_VERSION__ */
/*
 * The location of these definitions differs between XOPEN and ISO specs
 * The prototype should match those in the wctypes.h file.
 * Guard flags protect against multiple extern definitions, just in case.
 */
#if (_XOPEN_SOURCE >= 500)
extern wint_t	towlower 	__((wint_t));
extern wint_t	towupper 	__((wint_t));
#endif	/* XOPEN_SOURCE >= 500 */
extern wint_t	ungetwc		__((wint_t, FILE *));
#if (_XOPEN_SOURCE >= 500 ) || defined(_OSF_SOURCE) || (__STDC_VERSION__ == 199409)
 extern int	vfwprintf	__((FILE *, const wchar_t *, va_list));
 extern int	vwprintf	__((const wchar_t *, va_list));
 extern int	vswprintf	__((wchar_t *, size_t, const wchar_t *, va_list));
 extern size_t	wcrtomb		__((char *, wchar_t, mbstate_t *));
#endif /* _XOPEN_SOURCE || _OSF_SOURCE || __STDC_VERSION__ */
#if ((_ISO_C_SOURCE>=19990L) || defined(_OSF_SOURCE)) && !defined(_LIBC_POLLUTION_H_)
  extern long double wcstold	__((const wchar_t *, wchar_t **));
#endif /* (_ISO_C_SOURCE || _OSF_SOURCE) && ! _LIBC_POLLUTION_H */
extern wchar_t *wcscat		__((wchar_t *, const wchar_t *));
extern wchar_t *wcschr		__((const wchar_t *, wchar_t));
extern int	wcscmp		__((const wchar_t *, const wchar_t *));
extern int	wcscoll		__((const wchar_t *, const wchar_t *));
extern wchar_t *wcscpy		__((wchar_t *, const wchar_t *));
extern size_t	wcscspn		__((const wchar_t *, const wchar_t *));

#if (_XOPEN_SOURCE >= 500) || (__STDC_VERSION__ == 199409)

 extern size_t __wcsftime_unix98	__((wchar_t *, size_t, const wchar_t *, const struct tm *)); 
#define wcsftime_isoc(__a, __b, __c, __d) __wcsftime_unix98(__a, __b, __c, __d) 
/*
 * rename, with an extern_prefix, the wcsftime interface
 * This is required since the interface changes between the 
 * different XOPEN_SOURCE versions
 */
# ifndef _LIBC_POLLUTION_H_ 
#  ifdef __DECC 
#   pragma extern_prefix "_E" 
#  else
#   define wcsftime(__a, __b, __c, __d) _Ewcsftime (__a,__b,__c,__d) 
#  endif /* __DECC */ 
# endif /* !_LIBC_POLLUTION_H_ */ 

 extern size_t	__R5C94(wcsftime)	__((wchar_t *, size_t, const wchar_t *, const struct tm *)); 

# if !defined(_LIBC_POLLUTION_H_) && defined(__DECC) 
#  pragma extern_prefix "" 
# endif /* !_LIBC_POLLUTION_H_ && __DECC */ 
 /* end extern_prefix section */

#else 
 extern size_t	wcsftime	__((wchar_t *, size_t, const char *, const struct tm *)); 
#endif /* _XOPEN_SOURCE || __STDC_VERSION */

extern size_t	wcslen		__((const wchar_t *));
extern wchar_t *wcsncat		__((wchar_t *, const wchar_t *, size_t));
extern int	wcsncmp		__((const wchar_t *, const wchar_t *, size_t));
extern wchar_t *wcsncpy		__((wchar_t *, const wchar_t *, size_t));
extern wchar_t *wcspbrk		__((const wchar_t *, const wchar_t *));
extern wchar_t *wcsrchr		__((const wchar_t *, wchar_t));
#if (_XOPEN_SOURCE >= 500 ) || defined(_OSF_SOURCE) || (__STDC_VERSION__ == 199409)
 extern size_t	wcsrtombs	__((char *, const wchar_t **, size_t, mbstate_t *));
#endif /* _XOPEN_SOURCE || _OSF_SOURCE || __STDC_VERSION__ */
extern size_t	wcsspn		__((const wchar_t *, const wchar_t *));
#if (_XOPEN_SOURCE >= 500 ) || defined(_OSF_SOURCE) || (__STDC_VERSION__ == 199409)
 extern wchar_t *wcsstr		__((const wchar_t *, const wchar_t *));
#endif /* _XOPEN_SOURCE || _OSF_SOURCE || __STDC_VERSION__ */
extern double	wcstod		__((const wchar_t *, wchar_t **));

#if (_XOPEN_SOURCE >= 500) || (__STDC_VERSION__ == 199409)
/*
 * rename, with an extern_prefix, the wcstok interface
 * This is required since the interface changes between the 
 * different XOPEN_SOURCE versions
 */
# ifndef _LIBC_POLLUTION_H_ 
#  ifdef __DECC 
#   pragma extern_prefix "_E" 
#  else
#   define wcstok(__a, __b, __c) _Ewcstok (__a,__b,__c) 
#  endif /* __DECC */ 
# endif /* !_LIBC_POLLUTION_H_ */ 

  extern wchar_t *__R5C94(wcstok)	__((wchar_t *, const wchar_t *, wchar_t **)); 

# if !defined(_LIBC_POLLUTION_H_) && defined(__DECC) 
#  pragma extern_prefix "" 
# endif /* !_LIBC_POLLUTION_H_ && __DECC */ 
  /* end extern_prefix section */

  extern wchar_t *wcstok_r	__((wchar_t *, const wchar_t *, wchar_t **)); 

/* prototypes that were outdated with X/OPEN V5 and STDC */ 
#else 
  extern wchar_t *wcstok	__((wchar_t *, const wchar_t *)); 
# if defined(_REENTRANT) || defined(_THREAD_SAFE) /* reentrant interface */ 
   extern wchar_t *wcstok_r	__((wchar_t *, const wchar_t *, wchar_t **)); 
# endif /* _REENTRANT || _THREAD_SAFE */ 
#endif /* _XOPEN_SOURCE || __STDC_VERSION */

extern long int	wcstol		__((const wchar_t *, wchar_t **, int));
extern unsigned long int wcstoul	__((const wchar_t *, wchar_t **, int));
extern wchar_t *wcswcs		__((const wchar_t *, const wchar_t *));
extern int	wcswidth	__((const wchar_t *, size_t));
extern size_t	wcsxfrm		__((wchar_t *, const wchar_t *, size_t));
#if (_XOPEN_SOURCE >= 500 ) || defined(_OSF_SOURCE) || (__STDC_VERSION__ == 199409)
 extern int	wctob		__((wint_t));
#endif /* _XOPEN_SOURCE || _OSF_SOURCE || __STDC_VERSION__ */
/*
 * The location of this extern differs between XOPEN and ISO specs
 * The prototype should match those in the wctypes.h file.
 * Guard flags protect against multiple extern definitions, just in case.
 */
#if (_XOPEN_SOURCE >= 500)
#if defined(_XOPEN_SOURCE_EXTENDED) || (__STDC_VERSION__ == 199409)
 extern wctype_t	wctype	__((const char *));
#else
 extern wctype_t	wctype	__((char *));
#endif /* _XOPEN_SOURCE_EXTENDED */
#endif	/* XOPEN_SOURCE >= 500 */
extern int	wcwidth		__((const wchar_t));
#if (_XOPEN_SOURCE >= 500 ) || defined(_OSF_SOURCE) || (__STDC_VERSION__ == 199409)
 extern wchar_t *wmemchr		__((const wchar_t *, wchar_t, size_t));
 extern int	wmemcmp		__((const wchar_t *, const wchar_t *, size_t));
 extern wchar_t *wmemcpy		__((wchar_t *, const wchar_t *, size_t));
 extern wchar_t *wmemmove	__((wchar_t *, const wchar_t *, size_t));
 extern wchar_t *wmemset		__((wchar_t *, wchar_t, size_t));
 extern int	wprintf		__((const wchar_t *, ...));
 extern int	wscanf		__((const wchar_t *, ...));
#endif /* _XOPEN_SOURCE || _OSF_SOURCE || __STDC_VERSION__ */

/* ----------- END OF PROTOTYPES ------------- */

#ifdef _LIBC_POLLUTION_H_
# ifdef getwchar
#  undef getwchar
# endif /* getwchar */
# ifdef putwchar
#  undef putwchar
# endif /* putwchar */
#endif /* _LIBC_POLLUTION_H_ */

/*
 * This must follow the prototype definitions to avoid 
 * creating multiply defined function prototypes.
 */
#define getwchar()	getwc(stdin)
#define putwchar(c)	putwc(c, stdout)

#ifdef __cplusplus
 }
#endif
#endif /* _WCHAR_H_ */






