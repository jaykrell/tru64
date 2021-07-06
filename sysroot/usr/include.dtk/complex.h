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
 * $Log: complex.h,v $
 * $EndLog$
 */

#ifndef _COMPLEX_H_
#define _COMPLEX_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>

#define complex _Complex

/*
 * Do not #define _Complex_I in compiler modes that expand macros
 * recursively.  These modes will complain about absence of
 * type _Complex anyhow - we do not want them to complain about
 * infinite macro recursion...
 */
#if !(defined(__VAXC) ||  (defined(__GNUC__) && !__STDC__))
#define _Complex_I _Complex_I
#endif

#define	I _Complex_I

extern double complex		cacos (double complex __z);
extern float complex		cacosf (float complex __z);
extern long double complex	cacosl (long double complex __z);
extern double complex		casin (double complex __z);
extern float complex		casinf (float complex __z);
extern long double complex	casinl (long double complex __z);
extern double complex		catan (double complex __z);
extern float complex		catanf (float complex __z);
extern long double complex	catanl (long double complex __z);
extern double complex		ccos (double complex __z);
extern float complex		ccosf (float complex __z);
extern long double complex	ccosl (long double complex __z);
extern double complex		csin (double complex __z);
extern float complex		csinf (float complex __z);
extern long double complex	csinl (long double complex __z);
extern double complex		ctan (double complex __z);
extern float complex		ctanf (float complex __z);
extern long double complex	ctanl (long double complex __z);
extern double complex		cacosh (double complex __z);
extern float complex		cacoshf (float complex __z);
extern long double complex	cacoshl (long double complex __z);
extern double complex		casinh (double complex __z);
extern float complex		casinhf (float complex __z);
extern long double complex	casinhl (long double complex __z);
extern double complex		catanh (double complex __z);
extern float complex		catanhf (float complex __z);
extern long double complex	catanhl (long double complex __z);
extern double complex		ccosh (double complex __z);
extern float complex		ccoshf (float complex __z);
extern long double complex	ccoshl (long double complex __z);
extern double complex		csinh (double complex __z);
extern float complex		csinhf (float complex __z);
extern long double complex	csinhl (long double complex __z);
extern double complex		ctanh (double complex __z);
extern float complex		ctanhf (float complex __z);
extern long double complex	ctanhl (long double complex __z);
extern double complex		cexp (double complex __z);
extern float complex		cexpf (float complex __z);
extern long double complex	cexpl (long double complex __z);
extern double complex		clog (double complex __z);
extern float complex		clogf (float complex __z);
extern long double complex	clogl (long double complex __z);
extern double complex		cpow (double complex __x, double complex __y);
extern float complex		cpowf (float complex __x, float complex __y);
extern long double complex	cpowl (long double complex __x,
				       long double complex __y);
extern double complex		csqrt (double complex __z);
extern float complex		csqrtf (float complex __z);
extern long double complex	csqrtl (long double complex __z);
extern double			carg (double complex __z);
extern float			cargf (float complex __z);
extern long double		cargl (long double complex __z);

#ifdef _MATH_H_CABS_DECLARED
#pragma message ("<math.h> may have made incompatible declarations for "  \
                 "cabs() and cabsf().  To get the correct c99 complex "   \
                 "declarations for these functions, you must either "     \
                 "#include <complex.h> before <math.h>, or compile with " \
                 "options that enable C99 library features.")
#else
extern double			cabs (double complex __z);
extern float			cabsf (float complex __z);
#endif

extern long double		cabsl (long double complex __z);
extern double			cimag (double complex __z);
extern float			cimagf (float complex __z);
extern long double		cimagl (long double complex __z);
extern double complex		conj (double complex __z);
extern float complex		conjf (float complex __z);
extern long double complex	conjl (long double complex __z);
extern double complex		cproj (double complex __z);
extern float complex		cprojf (float complex __z);
extern long double complex	cprojl (long double complex __z);
extern double			creal (double complex __z);
extern float			crealf (float complex __z);
extern long double		creall (long double complex __z);

#ifdef __cplusplus
}
#endif
#endif /* _COMPLEX_H_ */
