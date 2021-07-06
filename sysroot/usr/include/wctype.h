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
 *	@(#)$RCSfile: wctype.h,v $ $Revision: 1.1.11.2 $ (DEC) $Date: 2000/01/26 23:08:48 $
 */ 

#ifndef _WCTYPE_H_
#define _WCTYPE_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <standards.h>
#include <sys/types.h>
#include <stdio.h>

#if (_XOPEN_SOURCE < 500)
# ifndef _WCTYPE_T
#  define _WCTYPE_T
   typedef unsigned int wctype_t;
# endif

# ifndef _WINT_T
#  define _WINT_T
   typedef unsigned int wint_t;         /* Wide character */
# endif
#else
/*
 * UNIX 98 moved the definition of wctype_t and wint_t to wchar.h
 */
# include <wchar.h>
#endif /* XOPEN_SOURCE < 500 */

#ifndef _WCTRANS_T
# define _WCTRANS_T
  typedef unsigned long wctrans_t;
#endif

#ifndef WEOF
# define WEOF	(wint_t)(-1)
#endif /* WEOF */

/* ------------ PROTOTYPES ------------- */

/*
 * The location of these definitions differs between XOPEN and ISO specs
 * The prototypes should match those in the wchar.h file.
 * Guard flags protect against multiple extern definitions, just in case.
 */
#if (_XOPEN_SOURCE < 500)
extern int	iswalnum __((wint_t));
extern int	iswalpha __((wint_t));
extern int	iswcntrl __((wint_t));
extern int	iswdigit __((wint_t));
extern int	iswgraph __((wint_t));
extern int	iswlower __((wint_t));
extern int	iswprint __((wint_t));
extern int	iswpunct __((wint_t));
extern int	iswspace __((wint_t));
extern int	iswupper __((wint_t));
extern int	iswxdigit __((wint_t));
extern int	iswctype __((wint_t, wctype_t));
#endif /* _XOPEN_SOURCE <500 */

#if (_XOPEN_SOURCE >= 500) || defined(_OSF_SOURCE) || (__STDC_VERSION__ == 199409)
 extern wint_t	towctrans __((wint_t, wctrans_t));
#endif

#if (_XOPEN_SOURCE < 500)
extern wint_t	towlower __((wint_t));
extern wint_t	towupper __((wint_t));
#endif /* XOPEN_SOURCE < 500 */

#if (_XOPEN_SOURCE >= 500) || defined(_OSF_SOURCE) || (__STDC_VERSION__ == 199409)
 extern wctrans_t	wctrans __((const char *));
#endif

#if defined(_XOPEN_SOURCE_EXTENDED) || (__STDC_VERSION__ == 199409)
 extern wctype_t	wctype __((const char *));
#else 
# if (_XOPEN_SOURCE < 500)
   extern wctype_t	wctype __((char *));
# endif /* XOPEN_SOURCE < 500 */
#endif /* _XOPEN_SOURCE_EXTENDED */

/* -------------- END OF PROTOTYPES --------------- */

#if defined(_OSF_SOURCE) && !defined(__cplusplus)
# include <ctype.h>
# define iswalnum(c)	_ISWMACRO(c,_ISALNUM)
# define iswalpha(c)	_ISWMACRO(c,_ISALPHA)
# define iswcntrl(c)	_ISWMACRO(c,_ISCNTRL)
# define iswdigit(c)	_ISWMACRO(c,_ISDIGIT)
# define iswgraph(c)	_ISWMACRO(c,_ISGRAPH)
# define iswlower(c)	_ISWMACRO(c,_ISLOWER)
# define iswprint(c)	_ISWMACRO(c,_ISPRINT)
# define iswpunct(c)	_ISWMACRO(c,_ISPUNCT)
# define iswspace(c)	_ISWMACRO(c,_ISSPACE)
# define iswupper(c)	_ISWMACRO(c,_ISUPPER)
# define iswxdigit(c)	_ISWMACRO(c,_ISXDIGIT)

# ifndef towupper
#  define towupper(c)	_TOWUPPER(c)
# endif
# ifndef towlower
#  define towlower(c)	_TOWLOWER(c)
# endif
#endif /* _OSF_SOURCE && !__cplusplus */

#ifdef __cplusplus
 }
#endif
#endif /* _WCTYPE_H_ */
