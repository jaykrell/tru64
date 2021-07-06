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
/*
 * HISTORY
 * $Log: tgmath.h,v $
 * $EndLog$
 */

#ifndef  _TGMATH_H
#define  _TGMATH_H
#include <standards.h>

#include <complex.h>
#include <math.h>

#if !(defined(__DECC) && __DECC_VER >= 60400000 )
#   error "This C99 header <tgmath.h> is not supported by this compiler."
#else

#define acos(__x)       __TGacos(__x)
#define acosh(__x)      __TGacosh(__x)
#define asin(__x)       __TGasin(__x)
#define asinh(__x)      __TGasinh(__x)
#define atan(__x)       __TGatan(__x)
#define atan2(__x,__y)  __TGatan2(__x,__y)
#define atanh(__x)      __TGatanh(__x)
#define carg(__x)       __TGcarg(__x)
#define cbrt(__x)       __TGcbrt(__x)
#define ceil(__x)       __TGceil(__x)
#define cimag(__x)      __TGcimag(__x)
#define conj(__x)       __TGconj(__x)
#define copysign(__x,__y)   __TGcopysign(__x,__y)
#define cos(__x)        __TGcos(__x)
#define cosh(__x)       __TGcosh(__x)
#define cproj(__x)      __TGcproj(__x)
#define creal(__x)      __TGcreal(__x)
#define erf(__x)        __TGerf(__x)
#define erfc(__x)       __TGerfc(__x)
#define exp(__x)        __TGexp(__x)
#define exp2(__x)       __TGexp2(__x)
#define expm1(__x)      __TGexpm1(__x)
#define fabs(__x)       __TGfabs(__x)
#define fdim(__x,__y)   __TGfdim(__x,__y)
#define floor(__x)      __TGfloor(__x)
#define fma(__x,__y,__z)    __TGfma(__x,__y,__z)
#define fmax(__x,__y)   __TGfmax(__x,__y)
#define fmin(__x,__y)   __TGfmin(__x,__y)
#define fmod(__x,__y)   __TGfmod(__x,__y)
#define frexp(__x,__y)  __TGfrexp(__x,__y)
#define hypot(__x,__y)  __TGhypot(__x,__y)
#define ilogb(__x)      __TGilogb(__x)
#define ldexp(__x,__y)  __TGldexp(__x,__y)
#define lgamma(__x)     __TGlgamma(__x)
#define llrint(__x)     __TGllrint(__x)
#define llround(__x)    __TGllround(__x)
#define log(__x)        __TGlog(__x)
#define log10(__x)      __TGlog10(__x)
#define log1p(__x)      __TGlog1p(__x)
#define log2(__x)       __TGlog2(__x)
#define logb(__x)       __TGlogb(__x)
#define lrint(__x)      __TGlrint(__x)
#define lround(__x)     __TGlround(__x)
#define nearbyint(__x)  __TGnearbyint(__x)
#define nextafter(__x,__y)  __TGnextafter(__x,__y)
#define nexttoward(__x,__y) __TGnexttoward(__x,__y)
#define pow(__x,__y)    __TGpow(__x,__y)
#define remainder(__x,__y)  __TGremainder(__x,__y)
#define remquo(__x,__y,__z) __TGremquo(__x,__y,__z)
#define rint(__x)       __TGrint(__x)
#define round(__x)      __TGround(__x)
#define scalbln(__x,__y)    __TGscalbln(__x,__y)
#define scalbn(__x,__y) __TGscalbn(__x,__y)
#define sin(__x)        __TGsin(__x)
#define sinh(__x)       __TGsinh(__x)
#define sqrt(__x)       __TGsqrt(__x)
#define tan(__x)        __TGtan(__x)
#define tanh(__x)       __TGtanh(__x)
#define tgamma(__x)     __TGtgamma(__x)
#define trunc(__x)      __TGtrunc(__x)

#endif /* defined(__DECC) && __DECC_VER >= 60400000 */

#endif /* _TGMATH_H */
