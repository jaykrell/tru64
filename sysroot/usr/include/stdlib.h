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
 *	@(#)$RCSfile: stdlib.h,v $ $Revision: 4.3.53.1 $ (DEC) $Date: 2002/05/03 13:29:01 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * COMPONENT_NAME: stdlib.h
 *
 * Copyright International Business Machines Corp. 1985, 1988
 * All Rights Reserved
 * Licensed Material - Property of IBM
 *
 * RESTRICTED RIGHTS LEGEND
 * Use, Duplication or Disclosure by the Government is subject to
 * restrictions as set forth in paragraph (b)(3)(B) of the Rights in
 * Technical Data and Computer Software clause in DAR 7-104.9(a).
 */                                                                   

#ifndef _STDLIB_H_
#define _STDLIB_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>

/*
 *
 *      The ANSI standard requires that certain values be in stdlib.h.
 *      It also requires if _ANSI_C_SOURCE is defined then ONLY these
 *      values are present. This header includes all the ANSI required entries.
 *
 */
#ifdef _ANSI_C_SOURCE

/*
 *      The following 3 definitions are included in <sys/types.h>.  They are
 *      also included here to comply with ANSI standards.
 */

#ifndef NULL
#define NULL    0L
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long  size_t;
#endif

/*
 * The following ifndef must ALWAYS be present since c++ may use _WCHAR_T
 * to prevent the header from trying to make a macro out of a c++ keyword.
 */
#ifndef _WCHAR_T
#define _WCHAR_T

#ifndef __WCHAR_T_LEN
#    define __WCHAR_T_LEN 4
#endif

#if __WCHAR_T_LEN == 1
    typedef unsigned char wchar_t;
#elif __WCHAR_T_LEN == 2
    typedef unsigned short wchar_t;
#else
    typedef unsigned int  wchar_t;
#endif /* __WCHAR_T_LEN == ?? */

#endif /* _WCHAR_T */

typedef struct
#ifdef _OSF_SOURCE
	 div_t  
#endif
		{			/* struct returned from div	*/
	int quot;			/* quotient			*/
	int rem; } div_t;			/* remainder			*/

typedef struct 
#ifdef _OSF_SOURCE
	ldiv_t  
#endif
			{		/* struct returned from ldiv	*/
	long int quot;			/* quotient			*/
	long int rem; } ldiv_t;		/* remainder			*/

#define EXIT_FAILURE   (1)		/* exit function failure	*/
#define EXIT_SUCCESS	0		/* exit function success	*/

#ifdef _BSD
#define RAND_MAX	2147483647	/* max value returned by rand	*/
#else
#define RAND_MAX	32767		/* max value returned by rand	*/
#endif

/* Some header files define abs. If defined, undef to prevent syntax error */
#ifdef abs				
#undef abs
#endif

#define MB_CUR_MAX	__getmbcurmax()	/* max bytes in multibyte char	*/
extern int __getmbcurmax __((void));

/**********
** Functions that are methods
**********/
extern int	mblen __((const char *, size_t));
extern size_t	mbstowcs __((wchar_t *, const char *, size_t));
extern int	mbtowc __((wchar_t *, const char *, size_t));
extern size_t	wcstombs __((char *, const wchar_t *, size_t));
extern int	wctomb __((char *, wchar_t));
#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)
#ifdef _OSF_SOURCE
extern int	rpmatch __((const char *));
#endif
extern void 	*valloc __((size_t ));
#endif /*_OSF_SOURCE || _XOPEN_SOURCE_EXTENDED */

extern double 	atof __((const char *));
extern int 	atoi __((const char *));
extern long int atol __((const char *));
extern double 	strtod __((const char *, char **));
extern float	strtof __((const char *, char **));
extern long int strtol __((const char *, char **, int ));
extern long double    strtold __((const char *, char **));
extern unsigned long int strtoul __((const char *, char **, int ));
extern int 	rand __((void));
extern void	srand __((unsigned int ));
extern void 	*calloc __((size_t , size_t ));
extern void	free __((void *));
extern void	*malloc __((size_t ));
extern void 	*realloc __((void *, size_t ));
#ifdef _XOPEN_SOURCE_EXTENDED
#include <sys/wait.h>
#endif

#if defined(_XOPEN_SOURCE_EXTENDED) || defined(_OSF_SOURCE)

/* declaration & renaming block for a64l(), l64a(), and ttyslot() */
#if defined(_XOPEN_SOURCE_EXTENDED) && !defined( _LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix "_E"
#else
#define a64l(__a) _Ea64l(__a)
#define l64a(__a) _El64a(__a)
#define ttyslot() _Ettyslot()
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */
extern long	__R(a64l) __((const char *));
extern char	* __R(l64a) __((long));
extern int	__R(ttyslot) __((void));
#if defined(_XOPEN_SOURCE_EXTENDED) && !defined( _LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix ""
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */

extern char	*ptsname __((int));
#if     defined(_REENTRANT) || defined(_THREADSAFE)
extern int ptsname_r __((int, char *, int));
#endif /* _REENTRANT) || _THREADSAFE */
#endif /* _XOPEN_SOURCE_EXTENDED || _OSF_SOURCE */

#ifdef _OSF_SOURCE

#if	defined(_REENTRANT) || defined(_THREADSAFE)
/* declaration & renaming block for l64a_r() */
#if defined(_XOPEN_SOURCE_EXTENDED) && !defined( _LIBC_POLLUTION_H_)
#define l64a_r(__a,__b,__c) _El64a_r(__a,__b,__c)
#endif
extern int	__R(l64a_r) __((long, char *, int));
#endif	/* _REENTRANT || _THREADSAFE */

#endif /* _OSF_SOURCE */

extern void	abort __((void));
extern int	atexit __((void (*)(void)));
extern void	exit __((int ));
extern char	*getenv __((const char *));
extern int 	system __((const char *));
extern void 	*bsearch __((const void *, const void *, size_t , size_t , int(*)(const void *, const void *)));
extern void 	qsort __((void *, size_t , size_t ,int(*)(const void *, const void *)));
extern int 	abs __I((int ));
extern div_t	div __((int , int ));
extern long int	labs __I((long int ));
extern ldiv_t 	ldiv __((long int , long int ));

#ifdef _BSD
/*
 * The following prototypes are included to provide support
 * for legacy applications that require BSD 4.3 interfaces.
 *
 * NEW DEVELOPMENT USE OF THESE INTERFACES IS DISCOURAGED!!
 */
extern int	setenv	 __((const char *, const char *, int));
extern void	unsetenv __((const char *));
#endif /* _BSD */

#if _POSIX_C_SOURCE>=199506L

#ifndef	_LIBC_POLLUTION_H_
#ifdef	__DECC
#pragma extern_prefix "_P"
#else
#define	rand_r(__a) _Prand_r(__a)
#endif
#endif	/* _LIBC_POLLUTION_H_ */
extern int	__P_C(rand_r) __((unsigned int *));
#ifndef	_LIBC_POLLUTION_H_
#ifdef	__DECC
#pragma	extern_prefix ""
#endif	/* __DECC */
#endif	/* _LIBC_POLLUTION_H_ */

#else	/* P1003.1c */

#if defined(_REENTRANT) || defined(_THREAD_SAFE)
extern int	rand_r __((unsigned int *, int *));
#endif

#endif	/* P1003.1c */

#ifdef _INTRINSICS
extern int 	abs(int);
extern long int	labs(long int);
#pragma intrinsic(abs, labs)
#endif
#endif /*_ANSI_C_SOURCE */

#ifdef _XOPEN_SOURCE

#if defined(_REENTRANT) || defined(_THREAD_SAFE)
struct drand48_data {
	unsigned	x[3];		/* 48 bit integer value */
	unsigned	a[3];		/* mutiplier value */
	unsigned	c;		/* addend value */
	unsigned short	lastx[3];	/* previous value of Xi */
	int		init;		/* initialize ? */
};
#endif	/* _REENTRANT || _THREAD_SAFE */

extern double	drand48 __((void));
extern double	erand48 __((unsigned short []));
extern long	jrand48 __((unsigned short []));
extern void	lcong48 __((unsigned short []));
extern long	lrand48 __((void));
extern long	mrand48 __((void));
extern long	nrand48 __((unsigned short []));
extern unsigned short *seed48 __((unsigned short []));
extern void	srand48 __((long));
#if (_XOPEN_SOURCE >= 500)
extern int 	putenv __((char *));
#else
extern int 	putenv __((const char *));
#endif /* XOPEN_SOURCE */
extern void	setkey __((const char *));

#if defined(_REENTRANT) || defined(_THREAD_SAFE)
extern int	drand48_r __((struct drand48_data *, double *));
extern int	erand48_r __((unsigned short [],struct drand48_data *,double*));
extern int	lrand48_r __((struct drand48_data *, long *));
extern int	mrand48_r __((struct drand48_data *, long *));
extern int	srand48_r __((long, struct drand48_data *));
extern int	seed48_r __((unsigned short [], struct drand48_data *));
extern int	lcong48_r __((unsigned short [], struct drand48_data *));
extern int	nrand48_r __((unsigned short [], struct drand48_data *, long*));
extern int	jrand48_r __((unsigned short [], struct drand48_data *, long*));
#endif	/* _REENTRANT || _THREAD_SAFE */

#endif  /* _XOPEN_SOURCE */

#ifdef __MATH__
#    define abs(j)          __abs(j)
#    define labs(j)         __labs(j)
#endif /* ifdef __MATH__ */

/*
 * Definition of functions and structures used by the thread-safe
 * random_r() functions.
 */
#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)

extern char	*initstate __((unsigned int, char *, size_t));
extern char	*setstate __((const char *));
extern int	grantpt __((int));
extern int	getsubopt __((char **, char *const *, char **));
#ifdef _XOPEN_SOURCE_EXTENDED
extern long	random __((void));
extern void	srandom __((unsigned int));
#else
extern int	random __((void));
extern int	srandom __((unsigned int));
#endif
extern char 	*realpath __((const char *, char *));
extern int	unlockpt __((int));


#if defined(_REENTRANT) || defined(_THREAD_SAFE)
#include <random.h>
#endif	/* _REENTRANT || _THREAD_SAFE */

#endif /* _OSF_SOURCE */

#ifdef _AES_SOURCE

/* optarg, optind, and opterr declared in stdlib (AES) and stdio (XPG3) */
#include <getopt.h>

extern int 	clearenv __((void));
extern char 	*getpass __((const char *));

#endif  /* _AES_SOURCE */

#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)
extern char 	*mktemp __((char *));
extern int 	mkstemp __((char *));
#endif /* _OSF_SOURCE || _XOPEN_SOURCE_EXTENDED */

#ifdef _XOPEN_SOURCE_EXTENDED
#if (_XOPEN_SOURCE_EXTENDED+0 == 600)
#ifndef _TU_XSE600
#define _TU_XSE600
#endif /* !_TU_XSE600 */
#endif /* _XOPEN_SOURCE_EXTENDED == 600 */
#endif /* _XOPEN_SOURCE_EXTENDED */

#if defined(_OSF_SOURCE) || defined(_TU_XSE600)
extern char	*mkdtemp __((char *));
#endif /* _OSF_SOURCE || _TU_XSE600 */

#if defined(_OSF_SOURCE)
extern int	mkstemps __((char *, int));
#endif /* _OSF_SOURCE */

/*
 *
 *   The following function prototypes are not defined for programs
 *   that are adhering to strict ANSI conformance, but are included
 *   for floating point support.
 *
 */

#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)
#include <sys/types.h>
char	*ecvt __((double, int, int *, int *));
char	*fcvt __((double, int, int *, int *));
char	*gcvt __((double, int, char *));
#if defined(_REENTRANT) || defined(_THREAD_SAFE)
int	ecvt_r __((double, int, int *, int *, char *, int));
int	fcvt_r __((double, int, int *, int *, char *, int));
#endif	/* _REENTRANT || _THREAD_SAFE */

#endif /* _OSF_SOURCE || defined(_XOPEN_SOURCE_EXTENDED) */
#ifdef __cplusplus
}
#endif
#endif /* _STDLIB_H_ */
