/*
 * *****************************************************************
 * *                                                               *
 * *    Copyright 2001 Compaq Computer Corporation                 *
 * *                                                               *
 * *    Compaq and the Compaq logo Registered in U.S. Patent       *
 * *    and Trademark Office.                                      *
 * *                                                               *
 * *    Confidential computer software. Valid license from Compaq  *
 * *    required for possession, use or copying. Consistent with   *
 * *    FAR 12.211 and 12.212, Commercial Computer Software,       *
 * *    Computer Software Documentation, and Technical Data for    *
 * *    Commercial Items are licensed to the U.S. Government       *
 * *    under vendors standard commercial license.                 *
 * *                                                               *
 * *****************************************************************
 */

#ifndef _C99MATH_H
#define _C99MATH_H 1
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>

#if (defined(_OSF_SOURCE) && defined(__STDC_VERSION__)          \
                          && __STDC_VERSION__ >= 199901L)  ||   \
    (defined(_ISO_C_SOURCE) && _ISO_C_SOURCE  >= 199901L)
/*  C99 stuff
*/
typedef float  float_t;
typedef double double_t;

/*
**  C99 function prototypes
*/
extern long double acosl(long double __x);
extern long double asinl(long double __x);
extern long double atanl(long double __x);
extern long double atan2l(long double __y, long double __x);
extern long double cosl(long double __x);
extern long double sinl(long double __x);
extern long double tanl(long double __x);
extern long double asinhl(long double __x);
extern long double atanhl(long double __x);
extern long double coshl(long double __x);
extern long double sinhl(long double __x);
extern long double tanhl(long double __x);
extern long double expl(long double __x);

extern double exp2(double __x);
extern float exp2f(float __x);
extern long double exp2l(long double __x);

extern long double expm1l(long double __x);
extern long double frexpl(long double __value, int *__exp);

extern int ilogb(double __x);
extern int ilogbf(float __x);
extern int ilogbl(long double __x);

/*
** FP_ILOGB0:	The value returned by ilogb(x) if x is zero.
** FP_ILOGBNAN:	The value returned by ilogb(x) if x is NaN.
** INT_MAX:	The value returned by ilogb(x) if x is infinite.
*/
#define FP_ILOGB0 (-2147483647-1)
#define FP_ILOGBNAN (-2147483647-1)

extern long double ldexpl(long double __x, int __exp);
extern long double logl(long double __x);
extern long double log10l(long double __x);
extern long double log1pl(long double __x);
extern long double log2l(long double __x);
extern long double logbl(long double __x);
extern long double modfl(long double __value, long double *__iptr);

extern double scalbn(double __x, int __n);
extern float scalbnf(float __x, int __n);
extern long double scalbnl(long double __x, int __n);
extern double scalbln(double __x, long int __n);
extern float scalblnf(float __x, long int __n);
extern long double scalblnl(long double __x, long int __n);

extern long double cbrtl(long double __x);
extern long double hypotl(long double __x, long double __y);
extern long double fabsl(long double __x);
extern long double powl(long double __x, long double __y);
extern long double sqrtl(long double __x);
extern long double erfl(long double __x);
extern long double erfcl(long double __x);
extern long double lgammal(long double __x);

extern double tgamma(double __x);
extern float tgammaf(float __x);
extern long double tgammal(long double __x);

extern long double ceill(long double __x);
extern long double floorl(long double __x);

extern double nearbyint(double __x);
extern float nearbyintf(float __x);
extern long double nearbyintl(long double __x);

extern long double rintl(long double __x);

extern long int lrint(double __x);
extern long int lrintf(float __x);
extern long int lrintl(long double __x);
extern long long int llrint(double __x);
extern long long int llrintf(float __x);
extern long long int llrintl(long double __x);

extern double round(double __x);
extern float roundf(float __x);
extern long double roundl(long double __x);

extern long int lround(double __x);
extern long int lroundf(float __x);
extern long int lroundl(long double __x);
extern long long int llround(double __x);
extern long long int llroundf(float __x);
extern long long int llroundl(long double __x);

extern long double truncl(long double __x);
extern long double fmodl(long double __x, long double __y);
extern long double remainderl(long double __x, long double __y);

extern double remquo(double __x, double __y, int *__quo);
extern float remquof(float __x, float __y, int *__quo);
extern long double remquol(long double __x, long double __y, int *__quo);

extern long double copysignl(long double __x, long double __y);

extern double nan(const char *__tagp);
extern float nanf(const char *__tagp);
extern long double nanl(const char *__tagp);

extern long double nextafterl(long double __x, long double __y);

extern double nexttoward(double __x, long double __y);
extern float nexttowardf(float __x, long double __y);
extern long double nexttowardl(long double __x, long double __y);

extern double fdim(double __x, double __y);
extern float fdimf(float __x, float __y);
extern long double fdiml(long double __x, long double __y);

extern double fmax(double __x, double __y);
extern float fmaxf(float __x, float __y);
extern long double fmaxl(long double __x, long double __y);

extern double fmin(double __x, double __y);
extern float fminf(float __x, float __y);
extern long double fminl(long double __x, long double __y);

extern double fma(double __x, double __y, double __z);
extern float fmaf(float __x, float __y, float __z);
extern long double fmal(long double __x, long double __y, long double __z);

#endif /* _OSF_SOURCE && __STDC_VERSION__ || _ISO_C_SOURCE */

#if defined(_COMPLEX_H_) || \
    (defined(_OSF_SOURCE) && defined(__STDC_VERSION__)          \
                          && __STDC_VERSION__ >= 199901L)  ||   \
    (defined(_ISO_C_SOURCE) && _ISO_C_SOURCE  >= 199901L)
/*
** User included <complex.h> or asked for C99 functionality, so disable
** the quirky cabs and cabsf declarations that get made in math.h using
** two doubles to compensate for lack of type _Complex.
*/
#  define _MATH_H_NO_CABS_DECLARED 1
#  define cabs  __obsolete_cabs
#  define cabsf __obsolete_cabsf
#else
/* Record the fact that math.h will declare cabs and cabsf incorrectly. */
#  define _MATH_H_CABS_DECLARED 1
#endif

/* Remember whether _FASTMATH was defined, and undefine it. */
#ifdef _FASTMATH
#  define __FASTMATH_SET
#  undef _FASTMATH
#endif

/* Get the system's normal math.h definitions */

#include_next <math.h>

/* If _FASTMATH was defined, redefine it and make all math routines
 * known to have fastmath implementations intrinsic.  Disable complaints
 * about pragma intrinsic in case base system's math.h is a little
 * different, and/or development compiler doesn't have all of these.
 */
#ifdef __FASTMATH_SET
#  define _FASTMATH 1
#  undef __FASTMATH_SET
#  pragma __message __save
#  pragma __message __disable(__unkintrin, __intundfun)
#  pragma intrinsic (acos)
#  pragma intrinsic (acosf)
#  pragma intrinsic (asin)
#  pragma intrinsic (asinf)
#  pragma intrinsic (atan)
#  pragma intrinsic (atan2)
#  pragma intrinsic (atan2f)
#  pragma intrinsic (atanf)
#  pragma intrinsic (cos)
#  pragma intrinsic (cosf)
#  pragma intrinsic (exp)
#  pragma intrinsic (expf)
#  pragma intrinsic (log)
#  pragma intrinsic (log10)
#  pragma intrinsic (log10f)
#  pragma intrinsic (logf)
#  pragma intrinsic (pow)
#  pragma intrinsic (powf)
#  pragma intrinsic (sin)
#  pragma intrinsic (sinf)
#  pragma intrinsic (sqrt)
#  pragma intrinsic (sqrtf)
#  pragma intrinsic (tan)
#  pragma intrinsic (tanf)
/* Some extensions not in formal standards */
#  if defined(_OSF_SOURCE)
#    pragma intrinsic (cosd)
#    pragma intrinsic (cosdf)
#    pragma intrinsic (hypot)
#    pragma intrinsic (hypotf)
#    pragma intrinsic (sind)
#    pragma intrinsic (sindf)
#  endif
#  pragma __message __restore
#endif	/* __FASTMATH_SET */

#ifdef _MATH_H_NO_CABS_DECLARED
/*
** Undo the #defines we made to prevent cabs and cabsf from
** getting declared in the base system math.h.
*/
#   undef cabs
#   undef cabsf
#endif

#if (defined(_OSF_SOURCE) && defined(__STDC_VERSION__)          \
                          && __STDC_VERSION__ >= 199901L)  ||   \
    (defined(_ISO_C_SOURCE) && _ISO_C_SOURCE  >= 199901L)
/*
** Additional definitions in <math.h> that are required by C99.
*/
    /*
    ** C89:
    **	The macro HUGE_VAL expands to a positive double expression,
    **	not necessarily representable as a float. (HUGE_VAL can be
    **	positive infinity in an implementation that supports
    **	infinities.) 
    **
    **	[A positive double expression may not be usable in an
    **	initializer for an object with static storage duration.]
    **
    ** C99:
    **	The macro HUGE_VAL expands to a positive double constant
    **	expression, not necessarily representable as a float.  The
    **	macros HUGE_VALF, and HUGE_VALL are respectively float and
    **	long double analogs of HUGE_VAL. (HUGE_VAL, HUGE_VALF, and
    **	HUGE_VALL can be positive infinity in an implementation that
    **	supports infinities.) 
    **
    **	The macro INFINITY expands to a constant expression of type
    **	float representing positive or unsigned infinity, if
    **	available; else to a positive constant of type float that
    **	overflows at translation time.
    **
    **	The macro NAN is defined if and only if the implementation
    **	supports quiet NaNs for the float type.  It expands to a
    **	constant expression of type float representing a quiet NaN.
    **
    **	[A double, float, or long double constant expression MAY be
    **	used in an initializer for an object with static storage
    **	duration.]
    **
    **	NOTE: This implementation defines the _IEEE_FP macro when ieee
    **	Infinities and NaNs are supported.
    */
#ifdef HUGE_VAL
#undef HUGE_VAL
#endif

#if defined(_IEEE_FP)
    /*
    ** This implementation provides the following named
    ** constants for use in IEEE floating-point mode:
    ** 
    ** __decc_float_ieee_Infinity		7F800000
    ** __decc_float_ieee_NaN			FFE00000
    ** __decc_double_ieee_Infinity		7FF00000...
    ** __decc_double_ieee_NaN			FFF80000...
    ** __decc_long_double_ieee_Infinity		7FFF0000...
    ** __decc_long_double_ieee_NaN		FFFF8000...
    */
#   define HUGE_VAL __decc_double_ieee_Infinity
#   define HUGE_VALF __decc_float_ieee_Infinity
#   define INFINITY __decc_float_ieee_Infinity
#   define NAN __decc_float_ieee_NaN
#else
#   define HUGE_VAL 1.797693134862315708e+308
#   define HUGE_VALF 3.4028234663852886e+38F
#   define INFINITY 3.4e+39F	/* overflows */
#endif

#if __X_FLOAT
#   if defined(_IEEE_FP)
#       define HUGE_VALL __decc_long_double_ieee_Infinity
#   else
#       define HUGE_VALL 1.1897314953572317e+4932L
#   endif
#else
#   define HUGE_VALL HUGE_VAL
#endif

    /*
    ** The macros FP_INFINITE, FP_NAN, FP_NORMAL, FP_SUBNORMAL and
    ** FP_ZERO are for number classification.  They represent
    ** mutually exclusive kinds of floating-point values.  They
    ** expand to integer constant expressions with distinct values.
    */
#define FP_INFINITE	1
#define FP_NAN		2
#define FP_NORMAL	3
#define FP_SUBNORMAL	4
#define FP_ZERO		5

static int __fpclassifyf(float __x);
static int __fpclassifyd(double __x);
static int __fpclassifyl(long double __x);

    /*
    ** int fpclassify (real-floating x);
    ** 
    ** The fpclassify macro classifies its argument value as NaN,
    ** infinite, normal, subnormal, zero or into another
    ** implementation-defined category.  First, an argument
    ** represented in a format wider than its semantic type is
    ** converted to its semantic type.  Then classification is based
    ** on the type of the argument.
    ** 
    ** The fpclassify macro returns the value of the number
    ** classification macro appropriate to the value of its argument. 
    */
#define fpclassify(x) \
    ((sizeof(x) == sizeof(float))  ? __fpclassifyf(x) :\
     (sizeof(x) == sizeof(double)) ? __fpclassifyd(x) :\
     				     __fpclassifyl(x))
    /*
    ** int isfinite(real-floating x);
    **
    ** The isfinite macro determines whether its argument has a
    ** finite value (zero, subnormal, or normal, and not infinite or
    ** NaN).  First, an argument represented in a format wider than
    ** its semantic type is converted to its semantic type.  Then
    ** determination is based on the type of the argument. 
    ** 
    ** The isfinite macro returns a nonzero value if and only if its
    ** argument has a finite value.
    */
#define isfinite(x) \
    (!(fpclassify(x) == FP_INFINITE || fpclassify(x) == FP_NAN))

    /*
    ** int isinf(real-floating x);
    **
    ** The isinf macro determines whether its argument has a
    ** infinite value (positive or negative).  First, an argument
    ** represented in a format wider than its semantic type is
    ** converted to its semantic type.  Then determination is based
    ** on the type of the argument. 
    ** 
    ** The isinf macro returns a nonzero value if and only if its
    ** argument has an infinite value.
    */
#define isinf(x) \
    (fpclassify(x) == FP_INFINITE)

    /*
    ** int isnan(real-floating x);
    ** 
    ** The isnan macro determines whether its argument value is a
    ** NaN.  First, an argument represented in a format wider than
    ** its semantic type is converted to its semantic type.  Then
    ** determination is based on the type of the argument.
    ** 
    ** The isnan macro returns a nonzero value if and only if its
    ** argument has a NaN value.
    */
#define isnan(x) \
    (fpclassify(x) == FP_NAN)

    /*
    ** int isnormal(real-floating x);
    **
    ** The isnormal macro determines whether its argument is normal
    ** (neither zero, subnormal, infinite nor NaN).  First, an argument
    ** represented in a format wider than its semantic type is
    ** converted to its semantic type.  Then determination is based
    ** on the type of the argument. 
    ** 
    ** The isnormal macro returns a nonzero value if and only if its
    ** argument has a normal value.
    */
#define isnormal(x)  \
    (fpclassify(x) == FP_NORMAL)

static int __signbitf(float __x);
static int __signbitd(double __x);
static int __signbitl(long double __x);

     /*
     ** int signbit(real-floating x);
     **
     ** The signbit macro determines whether the sign of its argument
     ** is negative.  (The signbit macro reports the sign of all
     ** values, including infinities, zeros, and NaNs.)
     */
#define signbit(x) \
    ((sizeof(x) == sizeof(float))  ? __signbitf(x) :\
     (sizeof(x) == sizeof(double)) ? __signbitd(x) :\
     				     __signbitl(x))

static __inline int __fpclassifyf(float __x)
{
    union {
	float 	__fp32;
	struct __fformat {
	    unsigned int __fraction_lo:16;
	    unsigned int __fraction_hi:7;
	    unsigned int __exponent:8;
	    unsigned int __sign:1;
        }	__fp32_pieces;
    }   __fpval;
    unsigned int __fraction;

    __fpval.__fp32 = __x;
    __fraction = __fpval.__fp32_pieces.__fraction_lo |
	__fpval.__fp32_pieces.__fraction_hi;
    if( __fpval.__fp32_pieces.__exponent == ((1<<8)-1) ) {
	if( __fraction == 0 )
	    return FP_INFINITE;
	else
	    return FP_NAN;
    } else
    if( __fpval.__fp32_pieces.__exponent == 0 ) {
	if( __fraction == 0 )
	    return FP_ZERO;
	else
	    return FP_SUBNORMAL;
    }
    return FP_NORMAL;
}

static __inline int __fpclassifyd(double __x) {
    union {
        double	__fp64;
        struct __dformat {
	    unsigned int __fraction_lo;
    	    unsigned int __fraction_mid:16;
    	    unsigned int __fraction_hi:4;
    	    unsigned int __exponent:11;
    	    unsigned int __sign:1;
        }	__fp64_pieces;
    }   __fpval;
    unsigned int __fraction;

    __fpval.__fp64 = __x;
    __fraction = __fpval.__fp64_pieces.__fraction_lo |
	__fpval.__fp64_pieces.__fraction_mid |
	__fpval.__fp64_pieces.__fraction_hi;
    if( __fpval.__fp64_pieces.__exponent == ((1<<11)-1) ) {
	if( __fraction == 0 )
	    return FP_INFINITE;
	else
	    return FP_NAN;
    } else
    if( __fpval.__fp64_pieces.__exponent == 0 ) {
	if( __fraction == 0 )
	    return FP_ZERO;
	else
	    return FP_SUBNORMAL;
    }
    return FP_NORMAL;
}

static __inline int __fpclassifyl(long double __x) {
    union  {
        long double	__fp128;
        struct __ldformat {
	    unsigned int __fraction_lo;
    	    unsigned int __fraction_midlo;
    	    unsigned int __fraction_midhi;
    	    unsigned int __fraction_hi:16;
    	    unsigned int __exponent:15;
    	    unsigned int __sign:1;
        }	__fp128_pieces;
    }   __fpval;
    unsigned int __fraction;

    __fpval.__fp128 = __x;
    __fraction = __fpval.__fp128_pieces.__fraction_lo |
	__fpval.__fp128_pieces.__fraction_midlo |
	__fpval.__fp128_pieces.__fraction_midhi |
	__fpval.__fp128_pieces.__fraction_hi;
    if( __fpval.__fp128_pieces.__exponent == ((1<<15)-1) ) {
	if( __fraction == 0 )
	    return FP_INFINITE;
	else
	    return FP_NAN;
    } else
    if( __fpval.__fp128_pieces.__exponent == 0 ) {
	if( __fraction == 0 )
	    return FP_ZERO;
	else
	    return FP_SUBNORMAL;
    }
    return FP_NORMAL;
}

static __inline int __signbitf(float __x)
{
    union {
	float 	__fp32;
	struct __fformat {
	    unsigned int __fraction_lo:16;
	    unsigned int __fraction_hi:7;
	    unsigned int __exponent:8;
	    unsigned int __sign:1;
        }	__fp32_pieces;
    }   __fpval;

    __fpval.__fp32 = __x;
    return __fpval.__fp32_pieces.__sign;
}

static __inline int __signbitd(double __x) {
    union {
        double	__fp64;
        struct __dformat {
	    unsigned int __fraction_lo;
    	    unsigned int __fraction_mid:16;
    	    unsigned int __fraction_hi:4;
    	    unsigned int __exponent:11;
    	    unsigned int __sign:1;
        }	__fp64_pieces;
    }   __fpval;

    __fpval.__fp64 = __x;
    return __fpval.__fp64_pieces.__sign;
}

static __inline int __signbitl(long double __x) {
    union  {
        long double	__fp128;
        struct __ldformat {
	    unsigned int __fraction_lo;
    	    unsigned int __fraction_midlo;
    	    unsigned int __fraction_midhi;
    	    unsigned int __fraction_hi:16;
    	    unsigned int __exponent:15;
    	    unsigned int __sign:1;
        }	__fp128_pieces;
    }   __fpval;

    __fpval.__fp128 = __x;
    return __fpval.__fp128_pieces.__sign;
}

#endif /* _OSF_SOURCE && __STDC_VERSION__ || _ISO_C_SOURCE */

#ifdef __cplusplus
}
#endif
#endif	/* _C99MATH_H */
