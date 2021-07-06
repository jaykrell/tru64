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
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * HISTORY
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * math-hdr
 *
 */
/* @(#)math.h   1.25  com/inc,3.1,9013 3/13/90 11:37:37 */
/*
 * COMPONENT_NAME: (math.h) math header file
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1988, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef  _MATH_H_
#define  _MATH_H_
#include <standards.h>

/*
 *      The ANSI standard requires that certain values be in math.h.
 *      It also requires that if _ANSI_C_SOURCE is defined then ONLY these
 *      values are present.
 *
 *      This header includes all the ANSI required entries. In addition
 *      other entries for the XIX system are included.
 *
 */

/*
 *      ANSI required entries in math.h
 *
 */
#ifdef _ANSI_C_SOURCE

/* GNUC requires headers for the single-precision funcs */
/* Intrinsics should have full function prototypes */

#if defined(__cplusplus)
extern "C"
{
#endif

extern  double acos __((double ));
extern  double asin __((double ));
extern  double atan __I((double ));
extern  double atan2 __I((double ,double ));
extern  double ceil __I((double ));
extern  double cos __I((double ));
extern  double cosh __((double ));
extern  double exp __((double ));
extern  double fabs __I((double ));
extern  double floor __I((double ));
extern  double fmod __((double , double ));
extern  double frexp __((double , int *));
extern  double ldexp __((double , int ));
extern  double log __((double ));
extern  double log10 __((double ));
extern  double modf __((double , double *));
extern  double pow __((double , double ));
extern  double sin __I((double ));
extern  double sinh __((double ));
extern  double sqrt __((double ));
extern  double tan __((double ));
extern  double tanh __((double ));
/*
 * Single precision ANSI C functions.
 */
extern float acosf ( float );
extern float asinf ( float );
extern float atanf ( float );
extern float atan2f ( float, float );
extern float ceilf ( float );
extern float cosf ( float );
extern float coshf ( float );
extern float expf ( float );
extern float fabsf ( float );
extern float floorf ( float );
extern float fmodf ( float, float );
extern float frexpf ( float, int * );
extern float ldexpf ( float, int );
extern float logf ( float );
extern float log10f ( float );
extern float modff ( float, float * );
extern float powf ( float, float );
extern float sinf ( float );
extern float sinhf ( float );
extern float sqrtf ( float );
extern float tanf ( float );
extern float tanhf ( float );

#if defined(__cplusplus)
}
#endif

#ifdef _INTRINSICS
#pragma intrinsic(cos,sin)
#pragma intrinsic(cosf,sinf)
#ifndef fabs
#pragma intrinsic(fabs)
#endif
#pragma intrinsic(atan,atanf)
#pragma intrinsic(atan2,atan2f)
#pragma intrinsic(ceil,ceilf)
#pragma intrinsic(floor,floorf)
#endif

#ifdef __KAP
#pragma _KAP no side effects (acos)
#pragma _KAP no side effects (asin)
#pragma _KAP no side effects (atan)
#pragma _KAP no side effects (atan2)
#pragma _KAP no side effects (ceil)
#pragma _KAP no side effects (cos)
#pragma _KAP no side effects (cosh)
#pragma _KAP no side effects (exp)
#pragma _KAP no side effects (fabs)
#pragma _KAP no side effects (floor)
#pragma _KAP no side effects (fmod)
#pragma _KAP no side effects (frexp)
#pragma _KAP no side effects (ldexp)
#pragma _KAP no side effects (log)
#pragma _KAP no side effects (log10)
#pragma _KAP no side effects (modf)
#pragma _KAP no side effects (pow)
#pragma _KAP no side effects (sin)
#pragma _KAP no side effects (sinh)
#pragma _KAP no side effects (sqrt)
#pragma _KAP no side effects (tan)
#pragma _KAP no side effects (tanh)

#pragma _KAP no side effects (acosf)
#pragma _KAP no side effects (asinf)
#pragma _KAP no side effects (atanf)
#pragma _KAP no side effects (atan2f)
#pragma _KAP no side effects (ceilf)
#pragma _KAP no side effects (cosf)
#pragma _KAP no side effects (coshf)
#pragma _KAP no side effects (expf)
#pragma _KAP no side effects (fabsf)
#pragma _KAP no side effects (floorf)
#pragma _KAP no side effects (fmodf)
#pragma _KAP no side effects (frexpf)
#pragma _KAP no side effects (ldexpf)
#pragma _KAP no side effects (logf)
#pragma _KAP no side effects (log10f)
#pragma _KAP no side effects (modff)
#pragma _KAP no side effects (powf)
#pragma _KAP no side effects (sinf)
#pragma _KAP no side effects (sinhf)
#pragma _KAP no side effects (sqrtf)
#pragma _KAP no side effects (tanf)
#pragma _KAP no side effects (tanhf)
#endif /* __KAP */
#endif /*_ANSI_C_SOURCE */

/*
 *
 * The following function prototypes define functions available in the
 * XIX system but not required by the ANSI standard. They will not be
 * included in _ANSI_C_SOURCE is defined (strict ANSI conformance).
 *
 */

#ifdef _XOPEN_SOURCE

extern int signgam;

#if defined(__cplusplus)
extern "C"
{
#endif
extern double   erf __((double ));
extern double   erfc __((double ));
extern double   gamma __((double ));
extern double   hypot __((double ,double ));
extern int      isnan __(( double ));
extern double   j0 __((double ));
extern double   j1 __((double ));
extern double   jn __((int, double ));
extern double   lgamma __((double ));
extern double   y0 __((double ));
extern double   y1 __((double ));
extern double   yn __((int , double ));

/*
 * Single precision XOPEN functions. 
 */
#ifdef _OSF_SOURCE	/* Not defined in XPG4 */
extern float erfcf  ( float );
extern float erff  ( float );
extern float gammaf  ( float );
extern float hypotf  ( float, float );
extern int   isnanf  ( float );
extern float j0f  ( float );
extern float j1f  ( float );
extern float jnf  ( int, float );
extern float lgammaf  ( float );
extern float y0f ( float );
extern float y1f ( float );
extern float ynf ( int, float );
#endif

#if defined(__cplusplus)
}
#endif

#ifdef __KAP
#pragma _KAP no side effects (hypot)
#endif /* __KAP */

#endif /* _XOPEN_SOURCE */


#ifdef _OSF_SOURCE

#include <stdlib.h>

#if (defined(ultrix) || defined(__ULTRIX) || defined (__ultrix))
#    define   scalb ldexp
#endif

#endif /* _OSF_SOURCE */ 

#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED) 

#if defined(__cplusplus)
extern "C"
{
#endif

/* same prototypes in _OSF_SOURCE and _XOPEN_SOURCE_EXTENDED */

extern double   acosh __((double ));
extern double   asinh __((double ));
extern double   atanh __((double ));
extern double   cbrt __((double ));
extern double   expm1 __((double ));
extern double   log1p __((double ));
extern double   logb __(( double ));
extern double   nextafter __((double, double ));
extern double   remainder __((double, double ));
extern double   rint __((double ));

#ifdef _XOPEN_SOURCE_EXTENDED

/* different in Spec1170 */
extern double   scalb __(( double , double ));

/* additional in Spec1170 */
extern int ilogb __((double ));

#else   /* not _XOPEN_SOURCE_EXTENDED but _OSF_SOURCE */

extern double   cabs __(( double, double ));
extern double   copysign __((double , double ));
extern double   drem __((double , double ));

#if !(defined(ultrix) || defined(__ULTRIX) || defined (__ultrix))
extern double   scalb __(( double , double ));
#endif
extern int      finite __(( double ));

/*
 * Single precision Digital functions. 
 */
extern float acoshf ( float );
extern float asinhf ( float );
extern float atanhf ( float );
extern float cabsf ( float, float );
extern float cbrtf ( float );
extern float copysignf ( float, float );
extern float dremf ( float, float );
extern float expm1f ( float );
extern float log1pf ( float );
extern float logbf ( float );
extern float nextafterf ( float, float );
extern float remainderf ( float, float );
extern float rintf ( float );
extern float scalbf ( float, float );
extern int finitef ( float );

/*
 * Additional Digital functions
 */
extern double acosd __(( double ));
extern double asind __(( double ));
extern double atand __I(( double ));
extern double atand2 __I(( double, double ));
extern double cosd __I(( double ));
extern double cot __(( double ));
extern double cotd __(( double ));
extern double log2 __(( double ));
extern double nint __(( double ));
extern double powi __(( double, int ));
extern double sind __I(( double ));
extern double tand __(( double ));
extern double trunc __(( double ));

extern float acosdf ( float );
extern float asindf ( float );
extern float atand2f ( float, float );
extern float atandf ( float );
extern float cosdf ( float );
extern float cotdf ( float );
extern float cotf ( float );
extern float log2f ( float );
extern float nintf ( float );
extern float powif ( float, int );
extern float sindf ( float );
extern float tandf ( float );
extern float truncf ( float );

extern int fp_class __(( double ));
extern int fp_classf ( float );
extern int itrunc __(( double ));
extern int powii __(( int, int ));
extern unsigned int uitrunc __(( double ));
extern int unordered __(( double, double ));
extern int unorderedf ( float, float );

#if !(__X_FLOAT)
/*
 * Alias the long double interfaces if we are compiling -real8.
 */
#define	acosl(__x)	acos(__x)
#define	asinl(__x)	asin(__x)
#define	atanl(__x)	atan(__x)
#define	atan2l(__x,__y)	atan2(__x,__y)
#define	ceill(__x)	ceil(__x)
#define	cosl(__x)	cos(__x)
#define	coshl(__x)	cosh(__x)
#define	expl(__x)	exp(__x)
#define	fabsl(__x)	fabs(__x)
#define	floorl(__x)	floor(__x)
#define	fmodl(__x,__y)	fmod(__x,__y)
#define	frexpl(__x,__y)	frexp(__x,__y)
#define	ldexpl(__x,__y)	ldexp(__x,__y)
#define	logl(__x)	log(__x)
#define	log10l(__x)	log10(__x)
#define	modfl(__x,__y)	modf(__x,__y)
#define	powl(__x,__y)	pow(__x,__y)
#define	sinl(__x)	sin(__x)
#define	sinhl(__x)	sinh(__x)
#define	sqrtl(__x)	sqrt(__x)
#define	tanl(__x)	tan(__x)
#define	tanhl(__x)	tanh(__x)
#define	erfl(__x)	erf(__x)
#define	erfcl(__x)	erfc(__x)
#define	gammal(__x)	gamma(__x)
#define	hypotl(__x,__y)	hypot(__x,__y)
#define	isnanl(__x)	isnan(__x)
#define	j0l(__x)	j0(__x)
#define	j1l(__x)	j1(__x)
#define	jnl(__x,__y)	jn(__x,__y)
#define	lgammal(__x)	lgamma(__x)
#define	y0l(__x)	y0(__x)
#define	y1l(__x)	y1(__x)
#define	ynl(__x,__y)	yn(__x,__y)
#define	acoshl(__x)		acosh(__x)
#define	asinhl(__x)		asinh(__x)
#define	atanhl(__x)		atanh(__x)
#define	cbrtl(__x)		cbrt(__x)
#define	expm1l(__x)		expm1(__x)
#define	log1pl(__x)		log1p(__x)
#define	logbl(__x)		logb(__x)
#define	nextafterl(__x,__y)	nextafter(__x,__y)
#define	rintl(__x)		rint(__x)
#define	copysignl(__x,__y)	copysign(__x,__y)
#define	dreml(__x,__y)		drem(__x,__y)
#if !(defined(ultrix) || defined(__ULTRIX) || defined(__ultrix))
#define	scalbl(__x,__y)		scalb(__x,__y)
#endif
#define	finitel(__x)		finite(__x)
#define	acosdl(__x)		acosd(__x)
#define	asindl(__x)		asind(__x)
#define	atandl(__x)		atand(__x)
#define	atand2l(__x,__y)	atand2(__x,__y)
#define	cosdl(__x)		cosd(__x)
#define	cotl(__x)		cot(__x)
#define	cotdl(__x)		cotd(__x)
#define	log2l(__x)		log2(__x)
#define	nintl(__x)		nint(__x)
#define	powil(__x,__y)		powi(__x,__y)
#define	sindl(__x)		sind(__x)
#define	tandl(__x)		tand(__x)
#define	truncl(__x)		trunc(__x)
#define	fp_classl(__x)		fp_class(__x)
#define	unorderedl(__x,__y)	unordered(__x,__y)
#else	/* REAL8 */
long double acosl __((long double));
long double asinl __((long double));
long double atanl __((long double));
long double atan2l __((long double, long double));
long double ceill __((long double));
long double cosl __((long double));
long double coshl __((long double));
long double expl __((long double));
long double fabsl __((long double));
long double floorl __((long double));
long double fmodl __((long double, long double));
long double frexpl __((long double, int *));
long double ldexpl __((long double, int));
long double logl __((long double));
long double log10l __((long double));
long double modfl __((long double, long double *));
long double powl __((long double, long double));
long double sinl __((long double));
long double sinhl __((long double));
long double sqrtl __((long double));
long double tanl __((long double));
long double tanhl __((long double));
long double erfl __((long double));
long double erfcl __((long double));
long double gammal __((long double));
long double hypotl __((long double, long double));
int isnanl __((long double));
long double j0l __((long double));
long double j1l __((long double));
long double jnl __((int, long double));
long double lgammal __((long double));
long double y0l __((long double));
long double y1l __((long double));
long double ynl __((int, long double));
long double acoshl __((long double));
long double asinhl __((long double));
long double atanhl __((long double));
long double cbrtl __((long double));
long double expm1l __((long double));
long double log1pl __((long double));
long double logbl __((long double));
long double nextafterl __((long double, long double));
long double rintl __((long double));
long double copysignl __((long double, long double));
long double dreml __((long double, long double));
long double scalbl __((long double, long double));
int finitel __((long double));
long double acosdl __((long double));
long double asindl __((long double));
long double atandl __((long double));
long double atand2l __((long double, long double));
long double cosdl __((long double));
long double cotl __((long double));
long double cotdl __((long double));
long double log2l __((long double));
long double nintl __((long double));
long double powil __((long double, int));
long double sindl __((long double));
long double tandl __((long double));
long double truncl __((long double));
int fp_classl __((long double));
int unorderedl __((long double, long double));

#ifdef	__KAP
#pragma	_KAP no side effects (acosl)
#pragma	_KAP no side effects (asinl)
#pragma	_KAP no side effects (atanl)
#pragma	_KAP no side effects (atan2l)
#pragma	_KAP no side effects (ceill)
#pragma	_KAP no side effects (cosl)
#pragma	_KAP no side effects (coshl)
#pragma	_KAP no side effects (expl)
#pragma	_KAP no side effects (fabsl)
#pragma	_KAP no side effects (floorl)
#pragma	_KAP no side effects (fmodl)
#pragma	_KAP no side effects (frexpl)
#pragma	_KAP no side effects (ldexpl)
#pragma	_KAP no side effects (logl)
#pragma	_KAP no side effects (log10l)
#pragma	_KAP no side effects (modfl)
#pragma	_KAP no side effects (powl)
#pragma	_KAP no side effects (sinl)
#pragma	_KAP no side effects (sinhl)
#pragma	_KAP no side effects (sqrtl)
#pragma	_KAP no side effects (tanl)
#pragma	_KAP no side effects (tanhl)
#pragma	_KAP no side effects (hypotl)
#endif	/* __KAP */

#endif /* _REAL8 */


#ifdef _INTRINSICS
#pragma intrinsic(atand, atand2)
#pragma intrinsic(cosd, sind)
#endif

#endif  /* _XOPEN_SOURCE_EXTENDED */

#if defined(__cplusplus)
}
#endif

#ifdef __KAP
#pragma _KAP no side effects (cabs)
#pragma _KAP no side effects (cabsf)
#endif /* __KAP */

#define _ABS(x) ((x) < 0 ? -(x) : (x))
#define _REDUCE(TYPE, X, XN, C1, C2)    { \
        double x1 = (double)(TYPE)X, x2 = X - x1; \
        X = x1 - (XN) * (C1); X += x2; X -= (XN) * (C2); }
#define _POLY1(x, c)    ((c)[0] * (x) + (c)[1])
#define _POLY2(x, c)    (_POLY1((x), (c)) * (x) + (c)[2])
#define _POLY3(x, c)    (_POLY2((x), (c)) * (x) + (c)[3])
#define _POLY4(x, c)    (_POLY3((x), (c)) * (x) + (c)[4])
#define _POLY5(x, c)    (_POLY4((x), (c)) * (x) + (c)[5])
#define _POLY6(x, c)    (_POLY5((x), (c)) * (x) + (c)[6])
#define _POLY7(x, c)    (_POLY6((x), (c)) * (x) + (c)[7])
#define _POLY8(x, c)    (_POLY7((x), (c)) * (x) + (c)[8])
#define _POLY9(x, c)    (_POLY8((x), (c)) * (x) + (c)[9])


#ifdef _OSF_SOURCE 

struct exception {
	int type;
	char *name;
	double arg1;
	double arg2;
	double retval;
};

#define 	DOMAIN		01
#define		SING		02
#define		OVERFLOW	03
#define		UNDERFLOW	04
#define		TLOSS		05
#define		PLOSS		06

#endif /* _OSF_SOURCE */ 

#ifdef _FASTMATH
#if defined(__DECC)  && __DECC_VER >= 60400000
/*
 * Fast math routines are intrinsics in Compaq C
 * and C++ V6.4 or later.
 */
#else
/*
 * FAST Floating Point
 */
extern double F_acos __(( double ));
extern double F_asin __(( double ));
extern double F_atan __(( double ));
extern double F_atan2 __(( double, double ));
extern double F_cos __(( double ));
extern double F_cosd __(( double ));
extern double F_exp __(( double ));
extern double F_hypot __(( double, double ));
extern double F_log __(( double ));
extern double F_log10 __(( double ));
extern double F_pow __(( double, double ));
extern double F_sin __(( double ));
extern double F_sind __(( double ));
extern double F_sqrt __(( double ));
extern double F_tan __(( double ));
/*
 * FAST Floating Point single precision
 */
extern float F_acosf ( float );
extern float F_asinf ( float );
extern float F_atan2f ( float, float );
extern float F_atanf ( float );
extern float F_cosf ( float );
extern float F_cosdf ( float );
extern float F_expf ( float );
extern float F_hypotf ( float, float );
extern float F_log10f ( float );
extern float F_logf ( float );
extern float F_powf ( float, float );
extern float F_sinf ( float );
extern float F_sindf ( float );
extern float F_sqrtf ( float );
extern float F_tanf ( float );

#define acos	F_acos
#define asin	F_asin
#define atan	F_atan
#define atan2	F_atan2
#define cos	F_cos
#define cosd	F_cosd
#define exp	F_exp
#define hypot	F_hypot
#define log	F_log
#define log10	F_log10
#define pow	F_pow
#define sin	F_sin
#define sind	F_sind
#define sqrt	F_sqrt
#define tan	F_tan
#define acosf	F_acosf
#define asinf	F_asinf
#define atan2f	F_atan2f
#define atanf	F_atanf
#define cosf	F_cosf
#define cosdf	F_cosdf
#define expf	F_expf
#define hypotf	F_hypotf
#define log10f	F_log10f
#define logf	F_logf
#define powf	F_powf
#define sinf	F_sinf
#define sindf	F_sindf
#define sqrtf	F_sqrtf
#define tanf	F_tanf
#endif /* __DECC && __DECC_VER >= 60400000 */
#endif /* _FASTMATH */
#endif /* _OSF_SOURCE || _XOPEN_SOURCE_EXTENDED */

/* N.B.  This FILE must be catenated with a machine-dependent file  ${MACHINE}/math.h
   with ends with #endif for _MATH_H_ feature-test
*/
/*
 * HISTORY
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */

/*
 * COMPONENT_NAME: (math.h) math header file
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1988, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 *      ANSI required entries in math.h
 *
 */
#ifdef _ANSI_C_SOURCE

#if defined(_IEEE_FP)
extern  unsigned   int __DINFINITY[2];
#	define HUGE_VAL (*((double *) (__DINFINITY)))
#else
#	define HUGE_VAL 1.797693134862315708e308
#endif

#endif /*_ANSI_C_SOURCE */

/*
 *
 * The following function prototypes define functions available in the
 * XIX system but not required by the ANSI standard. They will not be
 * included in _ANSI_C_SOURCE is defined (strict ANSI conformance).
 *
 */

#ifdef _XOPEN_SOURCE

/*
 *      Useful mathmatical constants:
 *
 * M_E          - e
 * M_LOG2E      - log2(e)
 * M_LOG10E     - log10(e)
 * M_LN2        - ln(2)
 * M_LN10       - ln(10)
 * M_PI         - pi
 * M_PI_2       - pi/2
 * M_PI_4       - pi/4
 * M_1_PI       - 1/pi
 * M_2_PI       - 2/pi
 * M_2_SQRTPI   - 2/sqrt(pi)
 * M_SQRT2      - sqrt(2)
 * M_SQRT1_2    - 1/sqrt(2)
*/

#define M_E        2.7182818284590452354E0  /*Hex  2^ 0 * 1.5bf0a8b145769 */
#define M_LOG2E    1.4426950408889634074E0  /*Hex  2^ 0 * 1.71547652B82FE */
#define M_LOG10E   4.3429448190325182765E-1 /*Hex  2^-2 * 1.BCB7B1526E50E */
#define M_LN2      6.9314718055994530942E-1 /*Hex  2^-1 * 1.62E42FEFA39EF */
#define M_LN10     2.3025850929940456840E0  /*Hex  2^ 1 * 1.26bb1bbb55516 */
#define M_PI       3.1415926535897932385E0  /*Hex  2^ 1 * 1.921FB54442D18 */
#define M_PI_2     1.5707963267948966192E0  /*Hex  2^ 0 * 1.921FB54442D18 */
#define M_PI_4     7.8539816339744830962E-1 /*Hex  2^-1 * 1.921FB54442D18 */
#define M_1_PI     3.1830988618379067154E-1 /*Hex  2^-2 * 1.45f306dc9c883 */
#define M_2_PI     6.3661977236758134308E-1 /*Hex  2^-1 * 1.45f306dc9c883 */
#define M_2_SQRTPI 1.1283791670955125739E0  /*Hex  2^ 0 * 1.20dd750429b6d */
#define M_SQRT2    1.4142135623730950488E0  /*Hex  2^ 0 * 1.6A09E667F3BCD */
#define M_SQRT1_2  7.0710678118654752440E-1 /*Hex  2^-1 * 1.6a09e667f3bcd */


#ifndef _MAXFLOAT
#define _MAXFLOAT
#define MAXFLOAT            ((float)3.40282346638528860e+38)
#endif

#endif /* _XOPEN_SOURCE */

#ifdef _OSF_SOURCE

/*
 *      Useful mathmatical constants:
 *
 * HUGE         - +infinity if ieee, else max_double
 * M_2PI        - 2*pi
 *
 */
#if defined(_IEEE_FP)
#   define HUGE 1.8e308
#else
#	define HUGE 1.797693134862315708e308
#endif
#define M_2PI      6.2831853071795864769E0  /*Hex  2^ 2 * 1.921FB54442D18 */

/* This is the nearest number to the cube root of MAXDOUBLE that   */
/*      doesn't cause the cube of it to overflow.                  */
/* In double precision hex this constant is: 554428a2 f98d728a     */
#define CUBRTHUGE      5.6438030941223618e102
#define INV_CUBRTHUGE  1.7718548704178434e-103

#endif /* _OSF_SOURCE */
#endif /* _MATH_H_ */

