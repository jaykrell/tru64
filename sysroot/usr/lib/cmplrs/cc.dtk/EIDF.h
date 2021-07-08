/*
**
** This file will be quiely compiled before the first line of source as if it
** were: 
**
** #ifdef _EXTERNAL_INTRINSICS
**	#include <standards.h>
**	#include "EIDF.h"
** #endif
**
** This file has a known checksum and cannot be modified; however, the user is
** free to define another intrinsic scope in which these external intrinsics may
** be deleted and redefined or new ones added.
** 
** #pragma intrinsic scope_begin
** #pragma intrinsic scope_end
**	These directives define the bounds of an intrinsic scope. Each function
**	declared in intrinsic scope defines the name of an external_intrinsic
**	and specifies the return type and arg types for its known_func_signature.
**	The function declaration is NOT entered into the compilers symbol table.
**
**	Pragmas defining linkage and/or assertions for the external_intrinsic
**	must follow.  They are applied when the external_intrinsic is
**	transformed. 
** 
**	Once an external_intrinsic, Fn, is defined it can be specified in the
**	directives:
**		#pragma intrinsic (Fn)
**		#pragma function (Fn)
**
**	It must be explicitly enabled in order to be recognized and transformed.
**
** #pragma intrinsic delete *
** #pragma intrinsic delete (Fn1[,Fn2]...)
**	These directives are only recognized in intrinsic scope.  They allow all
**	or a select few previously defined external_intrinsic functions to be
**	deleted. Since external_intrinsic functions are recognized by name
**	and call signature, they must be deleted before they can be redefined.
**
** #pragma intrinsic recognize (Fn1[,Fn2]...)
**	This directive is only recognized in intrinsic scope.  It allows
**	previously defined external_intrinsic functions to be recognized and
**	transformed by default. The -intrinsics option determines when it can be
**	recognized and the optimization level determines when it can be
**	transformed, just like the internal intrinsic memcpy.
**
** #pragma intrinsic transform (Fn1[,Fn2]...) when <keywords>
**	This directive is only recognized in intrinsic scope.  It uses
**	<keywords> to specify additional command line options that are required
**	in order to transform the intrinsic functions listed, and are
**	one or more of:
**
**	    preempt_module		(-preempt module)
**	    assume_nomath_errno		(-assume nomath_errno)
**	    non_ansi_mode		(neither -std1 nor -c99)
**	    c99_mode			(-c99)
**
**	seperated by whitespace.
*/

#pragma intrinsic scope_begin

/*
** EIDF.osf -- External Intrinsic Definition File for Tru64 UNIX
**
** The function declarations and pragmas in this file provide information for
** the compiler only. Each function declared in intrinsic scope defines the name
** of an external_intrinsic and specifies the return type and arg types for its
** known_func_signature.  Pragmas define linkage and assertions for the
** external_intrinsic and indicate when it will be recognized and transformed.
** This information does not interact with the users program unless and until
** the intrinsic function is enabled and the users program calls it.
** 
** All C99 functions are declared.  A subset of these functions are already
** defined as internal intrinsics.  Their declarations have been commented out
** to avoid conflicts.
**
** 1. The typedef names __intrinsic_size_t, __any_pointer, __alt_ret_ptr_void,
**    __alt_ret_ptr_char, and __alt_ret_ptr_wchar_t receive special handling by
**    the compiler. 
**    
** 2. Structs and pointers to structs are acceptable as args and return types if
**    the struct from the actual function prototype has members when the
**    intrinsic is called. 
**
** 3. The -nocpp command line option is suppressed while the External
**    Intrinsic Definition File is compiled so that the intrinsics may
**    be conditionally defined.
*/

#pragma required_pointer_size save
#pragma required_pointer_size system_default

/*
** >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
** Functions added by C99 are defined as external_intrinsics only if
** we are compiling in a mode which accepts the full C99 standard or
** the user has defined _ISO_C_SOURCE to include all C99 functions.
*/
#define _EIDF_C99_STUFF 0

#if defined(_OSF_SOURCE) && defined(__STDC_VERSION__)
#  if __STDC_VERSION__ >= 199901L
#    undef _EIDF_C99_STUFF
#    define _EIDF_C99_STUFF 1
#  endif
#elif defined(_ISO_C_SOURCE)
#  if _ISO_C_SOURCE >= 199901L
#    undef _EIDF_C99_STUFF
#    define _EIDF_C99_STUFF 1
#  endif
#endif

/*
** Always define _EIDF_XOPEN_SOURCE as a number.
*/
#ifndef _XOPEN_SOURCE
#  define _EIDF_XOPEN_SOURCE 0
#else
#  if _XOPEN_SOURCE+0==0
#    ifdef _XOPEN_SOURCE_EXTENDED
#      define _EIDF_XOPEN_SOURCE 420
#    else
#      define _EIDF_XOPEN_SOURCE 400
#    endif
#  else
#    define _EIDF_XOPEN_SOURCE _XOPEN_SOURCE
#  endif
#endif
/*
** <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

struct __defined_in_header;

/********************************/
/*	#include <assert.h>	*/
/********************************/

/********************************/
/*	#include <complex.h>	*/
/********************************/

#if _EIDF_C99_STUFF
double  _Complex 		cacos (double  _Complex);
float  _Complex 	cacosf (float  _Complex);
long double  _Complex 	cacosl (long double  _Complex);
double  _Complex 		casin (double  _Complex);
float  _Complex 	casinf (float  _Complex);
long double  _Complex 	casinl (long double  _Complex);
double  _Complex 		catan (double  _Complex);
float  _Complex 	catanf (float  _Complex);
long double  _Complex 	catanl (long double  _Complex);
double  _Complex 		ccos (double  _Complex);
float  _Complex 	ccosf (float  _Complex);
long double  _Complex 	ccosl (long double  _Complex);
double  _Complex 		csin (double  _Complex);
float  _Complex 	csinf (float  _Complex);
long double  _Complex 	csinl (long double  _Complex);
double  _Complex 		ctan (double  _Complex);
float  _Complex 	ctanf (float  _Complex);
long double  _Complex 	ctanl (long double  _Complex);
double  _Complex 		cacosh (double  _Complex);
float  _Complex 	cacoshf (float  _Complex);
long double  _Complex 	cacoshl (long double  _Complex);
double  _Complex 		casinh (double  _Complex);
float  _Complex 	casinhf (float  _Complex);
long double  _Complex 	casinhl (long double  _Complex);
double  _Complex 		catanh (double  _Complex);
float  _Complex 	catanhf (float  _Complex);
long double  _Complex 	catanhl (long double  _Complex);
double  _Complex 		ccosh (double  _Complex);
float  _Complex 	ccoshf (float  _Complex);
long double  _Complex 	ccoshl (long double  _Complex);
double  _Complex 		csinh (double  _Complex);
float  _Complex 	csinhf (float  _Complex);
long double  _Complex 	csinhl (long double  _Complex);
double  _Complex 		ctanh (double  _Complex);
float  _Complex 	ctanhf (float  _Complex);
long double  _Complex 	ctanhl (long double  _Complex);
double  _Complex 		cexp (double  _Complex);
float  _Complex 	cexpf (float  _Complex);
long double  _Complex 	cexpl (long double  _Complex);
double  _Complex 		clog (double  _Complex);
float  _Complex 	clogf (float  _Complex);
long double  _Complex 	clogl (long double  _Complex);
double				cabs (double  _Complex);
float			cabsf (float  _Complex);
long double		cabsl (long double  _Complex);
double  _Complex 		cpow (double  _Complex, double  _Complex);
float  _Complex 	cpowf (float  _Complex, float  _Complex);
long double  _Complex 	cpowl (long double _Complex, long double _Complex);
double  _Complex 		csqrt (double  _Complex);
float  _Complex 	csqrtf (float  _Complex);
long double  _Complex 	csqrtl (long double  _Complex);
double				carg (double  _Complex);
float			cargf (float  _Complex);
long double		cargl (long double  _Complex);
double				cimag (double  _Complex);
float			cimagf (float  _Complex);
long double		cimagl (long double  _Complex);
double  _Complex 		conj (double  _Complex);
float  _Complex 	conjf (float  _Complex);
long double  _Complex 	conjl (long double  _Complex);
double  _Complex 		cproj (double  _Complex);
float  _Complex 	cprojf (float  _Complex);
long double  _Complex 	cprojl (long double  _Complex);
double				creal (double  _Complex);
float			crealf (float  _Complex);
long double		creall (long double  _Complex);
#pragma assert func_attrs(cacos, cacosf, cacosl, casin, casinf, casinl, \
    catan, catanf, catanl, ccos, ccosf, ccosl, csin, csinf, csinl, \
    ctan, ctanf, ctanl, cacosh, cacoshf, cacoshl, casinh, casinhf, casinhl, \
    catanh, catanhf, catanhl, ccosh, ccoshf, ccoshl, csinh, csinhf, csinhl, \
    ctanh, ctanhf, ctanhl, cexp, cexpf, cexpl, clog, clogf, clogl, \
    cabs, cabsf, cabsl, cpow, cpowf, cpowl, csqrt, csqrtf, csqrtl, \
    carg, cargf, cargl, cimag, cimagf, cimagl, conj, conjf, conjl, \
    cproj, cprojf, cprojl, creal, crealf, creall) \
    nocalls_back nostate noeffects file_scope_vars(none)
#pragma intrinsic recognize (cacos, cacosf, cacosl, casin, casinf, casinl, \
    catan, catanf, catanl, ccos, ccosf, ccosl, csin, csinf, csinl, \
    ctan, ctanf, ctanl, cacosh, cacoshf, cacoshl, casinh, casinhf, casinhl, \
    catanh, catanhf, catanhl, ccosh, ccoshf, ccoshl, csinh, csinhf, csinhl, \
    ctanh, ctanhf, ctanhl, cexp, cexpf, cexpl, clog, clogf, clogl, \
    cabs, cabsf, cabsl, cpow, cpowf, cpowl, csqrt, csqrtf, csqrtl, \
    carg, cargf, cargl, cimag, cimagf, cimagl, conj, conjf, conjl, \
    cproj, cprojf, cprojl, creal, crealf, creall)
#pragma intrinsic transform (cacos, cacosf, cacosl, casin, casinf, casinl, \
    catan, catanf, catanl, ccos, ccosf, ccosl, csin, csinf, csinl, \
    ctan, ctanf, ctanl, cacosh, cacoshf, cacoshl, casinh, casinhf, casinhl, \
    catanh, catanhf, catanhl, ccosh, ccoshf, ccoshl, csinh, csinhf, csinhl, \
    ctanh, ctanhf, ctanhl, cexp, cexpf, cexpl, clog, clogf, clogl, \
    cabs, cabsf, cabsl, cpow, cpowf, cpowl, csqrt, csqrtf, csqrtl, \
    carg, cargf, cargl, cimag, cimagf, cimagl, conj, conjf, conjl, \
    cproj, cprojf, cprojl, creal, crealf, creall) \
    when non_ansi_mode c99_mode
#endif	/* _EIDF_C99_STUFF */

/********************************/
/*	#include <ctype.h>	*/
/********************************/

#ifdef _ANSI_C_SOURCE
int	isalnum  ( int );
int	isalpha  ( int );
int	iscntrl  ( int );
int	isdigit  ( int );
int	isgraph  ( int );
int	islower  ( int );
int	isprint  ( int );
int	ispunct  ( int );
int	isspace  ( int );
int	isupper  ( int );
int	isxdigit ( int );
int	tolower  ( int );
int	toupper  ( int );
#pragma assert func_attrs(isalnum, isalpha, iscntrl, isdigit, isgraph, \
    islower, isprint, ispunct, isspace, isupper, isxdigit, tolower, toupper) \
    nocalls_back nostate noeffects file_scope_vars(none)
#pragma intrinsic recognize(isalnum, isalpha, iscntrl, isdigit, isgraph, \
    islower, isprint, ispunct, isspace, isupper, isxdigit, tolower, toupper)

#if _EIDF_C99_STUFF
int	isblank  ( int );
#pragma assert func_attrs(isblank) \
    nocalls_back nostate noeffects file_scope_vars(none)
#pragma intrinsic recognize(isblank)
#pragma intrinsic transform (isblank) when non_ansi_mode c99_mode
#endif	/* _EIDF_C99_STUFF */
#endif	/* _ANSI_C_SOURCE */

/********************************/
/*	#include <errno.h>	*/
/********************************/

/********************************/
/*	#include <fenv.h>	*/
/********************************/

#if _EIDF_C99_STUFF
/* <<< hold until static => extern
typedef unsigned int __fexcept_t;
typedef struct __defined_in_header __fenv_t;

static int	feclearexcept  ( int  );
static int 	fegetexceptflag  ( __fexcept_t *, int );
static int 	feraiseexcept  ( int );
static int 	fesetexceptflag  ( const __fexcept_t *, int );
static int 	fetestexcept  ( int );
static int 	fegetround  ( void );
static int 	fesetround  ( int );
static int 	fegetenv  ( __fenv_t * );
static int 	feholdexcept  ( __fenv_t * );
static int 	fesetenv  ( const __fenv_t * );
static int 	feupdateenv  ( const __fenv_t * );
#pragma assert func_attrs(feclearexcept, fegetexceptflag, feraiseexcept, \
    fesetexceptflag, fetestexcept, fegetround, fesetround, fegetenv, \
    feholdexcept, fesetenv, feupdateenv) \
    nocalls_back
#pragma intrinsic recognize(feclearexcept, fegetexceptflag, feraiseexcept, \
    fesetexceptflag, fetestexcept, fegetround, fesetround, fegetenv, \
    feholdexcept, fesetenv, feupdateenv)
#pragma intrinsic transform (feclearexcept, fegetexceptflag, feraiseexcept, \
    fesetexceptflag, fetestexcept, fegetround, fesetround, fegetenv, \
    feholdexcept, fesetenv, feupdateenv) \
    when non_ansi_mode c99_mode
>>> hold until static => extern */
#endif	/* _EIDF_C99_STUFF */

/********************************/
/*	#include <float.h>	*/
/********************************/

/********************************/
/*	#include <inttypes.h>	*/
/********************************/

/********************************/
/*	#include <iso646.h>	*/
/********************************/

/********************************/
/*	#include <limits.h>	*/
/********************************/

/********************************/
/*	#include <locale.h>	*/
/********************************/

typedef struct __defined_in_header __lconv;

char *		setlocale  ( int , const char * );
__lconv *	localeconv  ( void );
#pragma assert func_attrs(setlocale, localeconv) nocalls_back
#pragma intrinsic recognize(setlocale, localeconv)

/********************************/
/*	#include <math.h>	*/
/********************************/

#ifdef _ANSI_C_SOURCE
/* <<< internal intrinsics
double 			acos  ( double );
float 		acosf  ( float );
long double	acosl(long double);
double 			asin  ( double );
float 		asinf  ( float );
long double 	asinl(long double);
double 			atan  ( double );
float 		atanf  ( float );
long double 	atanl(long double);
double 			atan2  ( double , double );
float 		atan2f  ( float , float );
long double 	atan2l(long double, long double);
double 			cos  ( double );
float 		cosf  ( float );
long double 	cosl(long double);
double 			sin  ( double );
float 		sinf  ( float );
long double 	sinl(long double);
double 			tan  ( double );
float 		tanf  ( float );
long double 	tanl(long double);
#pragma assert func_attrs(acos, acosf, acosl, asin, asinf, asinl, atan, atanf, atanl, \
    atan2, atan2f, atan2l, cos, cosf, cosl, sin, sinf, sinl, tan, tanf, tanl) \
    nocalls_back nostate noeffects
#pragma intrinsic recognize(acos, acosf, acosl, asin, asinf, asinl, atan, atanf, atanl, \
    atan2, atan2f, atan2l, cos, cosf, cosl, sin, sinf, sinl, tan, tanf, tanl)
#pragma intrinsic transform(acos, acosf, acosl, asin, asinf, asinl, atan2, atan2f, atan2l) \
    when assume_nomath_errno
>>> internal intrinsics */
#endif	/* _ANSI_C_SOURCE */

#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)
double   		acosh  ( double );
float 		acoshf  ( float );
long double 	acoshl  ( long double );
double   		asinh  ( double );
float 		asinhf  ( float );
long double 	asinhl(long double);
double   		atanh  ( double );
float 		atanhf  ( float );
long double 	atanhl(long double);
#pragma assert func_attrs(acosh, acoshf, acoshl, asinh, asinhf, asinhl, atanh, atanhf, atanhl) \
    nocalls_back nostate noeffects
#pragma intrinsic recognize(acosh, acoshf, acoshl, asinh, asinhf, asinhl, atanh, atanhf, atanhl)
#pragma intrinsic transform(acosh, acoshf, acoshl, atanh, atanhf, atanhl) \
    when assume_nomath_errno
#pragma intrinsic transform(acosh, acoshf, acoshl, asinh, asinhf, asinhl, atanh, atanhf, atanhl) \
    when non_ansi_mode c99_mode
#endif	/* defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED) */

#ifdef _ANSI_C_SOURCE
/* <<< internal intrinsics
double 			cosh  ( double );
float 		coshf  ( float );
long double 	coshl(long double);
double 			sinh  ( double );
float 		sinhf  ( float );
long double 	sinhl(long double);
double 			tanh  ( double );
float 		tanhf  ( float );
long double 	tanhl(long double);
double 			exp  ( double );
float 		expf  ( float );
long double 	expl(long double);
#pragma assert func_attrs(cosh, coshf, coshl, sinh, sinhf, sinhl, tanh, tanhf, tanhl, exp, expf, expl) \
    nocalls_back nostate noeffects
#pragma intrinsic recognize(cosh, coshf, coshl, sinh, sinhf, sinhl, tanh, tanhf, tanhl, exp, expf, expl)
#pragma intrinsic transform(cosh, coshf, coshl, sinh, sinhf, sinhl, exp, expf, expl) \
    when assume_nomath_errno
>>> internal intrinsics */

double 			frexp  ( double , int * );
float 		frexpf  ( float , int * );
long double 	frexpl(long double, int *);
double 			ldexp  ( double , int );
float 		ldexpf  ( float , int );
long double 	ldexpl(long double, int);
#pragma assert func_attrs(frexp, frexpf, frexpl, \
    ldexp, ldexpf, ldexpl) \
    nocalls_back nostate noeffects
#pragma intrinsic recognize(frexp, frexpf, frexpl, \
    ldexp, ldexpf, ldexpl)
#pragma intrinsic transform(ldexp, ldexpf, ldexpl) \
    when assume_nomath_errno
#endif	/* _ANSI_C_SOURCE */

#if _EIDF_C99_STUFF
double 			exp2(double);
float 		exp2f(float);
long double 	exp2l(long double);
#pragma assert func_attrs(exp2, exp2f, exp2l) \
    nocalls_back nostate noeffects
#pragma intrinsic recognize(exp2, exp2f, exp2l)
#pragma intrinsic transform(exp2, exp2f, exp2l) \
    when assume_nomath_errno
#pragma intrinsic transform(exp2, exp2f, exp2l) \
    when non_ansi_mode c99_mode
#endif	/* _EIDF_C99_STUFF */

#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)
double   		expm1  ( double );
float 		expm1f  ( float );
long double 	expm1l(long double);
#pragma assert func_attrs(expm1, expm1f, expm1l) \
    nocalls_back nostate noeffects
#pragma intrinsic recognize(expm1, expm1f, expm1l)
#pragma intrinsic transform(expm1, expm1f, expm1l) \
    when assume_nomath_errno
#endif	/* defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED) */

#if defined(_XOPEN_SOURCE_EXTENDED) || _EIDF_C99_STUFF
int 			ilogb(double);
int 		ilogbf(float);
int 		ilogbl(long double);
#pragma assert func_attrs(ilogb, ilogbf, ilogbl) \
    nocalls_back nostate noeffects
#pragma intrinsic recognize(ilogb, ilogbf, ilogbl)
#pragma intrinsic transform(ilogb, ilogbf, ilogbl) \
    when assume_nomath_errno
#endif	/* defined(_XOPEN_SOURCE_EXTENDED) || _EIDF_C99_STUFF */

#ifdef _ANSI_C_SOURCE
/* <<< internal intrinsics
double 			log  ( double );
float 		logf  ( float );
long double 	logl(long double);
double 			log10  ( double );
float 		log10f  ( float );
long double 	log10l(long double);
#pragma assert func_attrs(log, logf, logl, log10, log10f, log10l) \
    nocalls_back nostate noeffects
#pragma intrinsic recognize(log, logf, logl, log10, log10f, log10l)
#pragma intrinsic transform(log, logf, logl, log10, log10f, log10l) \
    when assume_nomath_errno
>>> internal intrinsics */
#endif	/* _ANSI_C_SOURCE */

#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)
double   		log1p  ( double );
float 		log1pf  ( float );
long double 	log1pl(long double);
#pragma assert func_attrs(log1p, log1pf, log1pl) \
    nocalls_back nostate noeffects
#pragma intrinsic recognize(log1p, log1pf, log1pl)
#pragma intrinsic transform(log1p, log1pf, log1pl) \
    when assume_nomath_errno
#pragma intrinsic transform(log1p, log1pf, log1pl) \
    when non_ansi_mode c99_mode
#endif	/* defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED) */

#ifdef _OSF_SOURCE
/* <<< internal intrinsics
double 			log2  ( double );
float 		log2f  ( float );
long double 	log2l(long double);
#pragma assert func_attrs(log2, log2f, log2l) \
    nocalls_back nostate noeffects
#pragma intrinsic recognize(log2, log2f, log2l)
#pragma intrinsic transform(log2, log2f, log2l) \
    when non_ansi_mode c99_mode
#pragma intrinsic transform(log2, log2f, log2l) \
    when assume_nomath_errno
>>> internal intrinsics */
#endif	/* _OSF_SOURCE */

#ifdef _ANSI_C_SOURCE
double 			modf  ( double , double * );
float 		modff  ( float , float * );
long double 	modfl(long double, long double *);
#pragma assert func_attrs(modf, modff, modfl) \
    nocalls_back nostate noeffects
#pragma intrinsic recognize(modf, modff, modfl)
#endif	/* _ANSI_C_SOURCE */

#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)
double   		logb  ( double );
float 		logbf  ( float );
long double 	logbl(long double);
double			cbrt  ( double );
float 		cbrtf  ( float );
long double 	cbrtl(long double);
#pragma assert func_attrs(logb, logbf, logbl, cbrt, cbrtf, cbrtl) \
    nocalls_back nostate noeffects
#pragma intrinsic recognize(logb, logbf, logbl, cbrt, cbrtf, cbrtl)
#pragma intrinsic transform(logb, logbf, logbl) \
    when assume_nomath_errno
#pragma intrinsic transform(logb, logbf, logbl, cbrt, cbrtf, cbrtl) \
    when non_ansi_mode c99_mode
#endif	/* defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED) */

#if _EIDF_C99_STUFF
double 			scalbn(double, int);
float 		scalbnf(float, int);
long double 	scalbnl(long double, int);
double 			scalbln(double, long int);
float 		scalblnf(float, long int);
long double 	scalblnl(long double, long int);
#pragma assert func_attrs(scalbn, scalbnf, scalbnl, scalbln, scalblnf, scalblnl) \
    nocalls_back nostate noeffects
#pragma intrinsic recognize(scalbn, scalbnf, scalbnl, scalbln, scalblnf, scalblnl)
#pragma intrinsic transform(scalbn, scalbnf, scalbnl, scalbln, scalblnf, scalblnl) \
    when assume_nomath_errno
#pragma intrinsic transform(scalbn, scalbnf, scalbnl, scalbln, scalblnf, scalblnl) \
    when non_ansi_mode c99_mode
#endif	/* _EIDF_C99_STUFF */

#ifdef _ANSI_C_SOURCE
/* <<< internal intrinsics
double 			fabs  ( double );
float 		fabsf  ( float );
long double 	fabsl(long double);
#pragma assert func_attrs(fabs, fabsf, fabsl) \
    nocalls_back nostate noeffects
#pragma intrinsic recognize(fabs, fabsf, fabsl)
>>> internal intrinsics */
#endif	/* _ANSI_C_SOURCE */

#if _EIDF_XOPEN_SOURCE > 0
double			hypot  ( double , double );
float 		hypotf   ( float , float );
long double 	hypotl(long double, long double);
#pragma assert func_attrs(hypot, hypotf, hypotl) \
    nocalls_back nostate noeffects
#pragma intrinsic recognize(hypot, hypotf, hypotl)
#pragma intrinsic transform(hypot, hypotf, hypotl) \
    when assume_nomath_errno
#endif	/* _EIDF_XOPEN_SOURCE > 0 */

#ifdef _ANSI_C_SOURCE
/* <<< internal intrinsics
double 			pow  ( double , double );
float 		powf  ( float , float );
long double 	powl(long double, long double);
double 			sqrt  ( double );
float 		sqrtf  ( float );
long double 	sqrtl(long double);
#pragma assert func_attrs(pow, powf, powl, sqrt, sqrtf, sqrtl) \
    nocalls_back nostate noeffects
#pragma intrinsic recognize(pow, powf, powl, sqrt, sqrtf, sqrtl)
#pragma intrinsic transform(pow, powf, powl, sqrt, sqrtf, sqrtl) \
    when assume_nomath_errno
>>> internal intrinsics */
#endif	/* _ANSI_C_SOURCE */

#if _EIDF_C99_STUFF
double   		erf  ( double );
float 		erff   ( float );
long double 	erfl(long double);
double   		erfc  ( double );
float 		erfcf   ( float );
long double 	erfcl(long double);
double			lgamma  ( double );
float 		lgammaf   ( float );
long double 	lgammal(long double);
double 			tgamma(double);
float 		tgammaf(float);
long double 	tgammal(long double);
#pragma assert func_attrs(erf, erff, erfl, erfc, erfcf, erfcl, lgamma, lgammaf, lgammal, \
    tgamma, tgammaf, tgammal) \
    nocalls_back nostate noeffects
#pragma intrinsic recognize(erf, erff, erfl, erfc, erfcf, erfcl, lgamma, lgammaf, lgammal, \
    tgamma, tgammaf, tgammal)
#pragma intrinsic transform(erfc, erfcf, erfcl, lgamma, lgammaf, lgammal, tgamma, tgammaf, tgammal) \
    when assume_nomath_errno
#pragma intrinsic transform(erf, erff, erfl, erfc, erfcf, erfcl, lgamma, lgammaf, lgammal, \
    tgamma, tgammaf, tgammal) \
    when non_ansi_mode c99_mode
#endif	/* _EIDF_C99_STUFF */

#ifdef _ANSI_C_SOURCE
/* <<< internal intrinsics
double 			ceil  ( double );
float 		ceilf  ( float );
long double 	ceill(long double);
double 			floor  ( double );
float 		floorf  ( float );
long double 	floorl(long double);
#pragma assert func_attrs(ceil, ceilf, ceill, floor, floorf, floorl) \
    nocalls_back nostate noeffects
#pragma intrinsic recognize(ceil, ceilf, ceill, floor, floorf, floorl)
>>> internal intrinsics */

double 			fmod  ( double , double );
float 		fmodf  ( float , float );
long double 	fmodl(long double, long double);
#pragma assert func_attrs(fmod, fmodf, fmodl) \
    nocalls_back nostate noeffects
#pragma intrinsic recognize(fmod, fmodf, fmodl)
#pragma intrinsic transform(fmod, fmodf, fmodl) \
    when assume_nomath_errno
#endif	/* _ANSI_C_SOURCE */

#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)
double			rint  ( double );
float 		rintf  ( float );
long double 	rintl(long double);
double			remainder  ( double , double );
float 		remainderf  ( float , float );
long double 	remainderl(long double, long double);
double			nextafter  ( double , double );
float 		nextafterf  ( float , float );
long double 	nextafterl(long double, long double);
#pragma assert func_attrs(rint, rintf, rintl, remainder, remainderf, remainderl, \
    nextafter, nextafterf, nextafterl) \
    nocalls_back nostate noeffects
#pragma intrinsic recognize(rint, rintf, rintl, remainder, remainderf, remainderl, \
    nextafter, nextafterf, nextafterl)
#pragma intrinsic transform(nextafter, nextafterf, nextafterl) \
    when assume_nomath_errno
#pragma intrinsic transform(rint, rintf, rintl, remainder, remainderf, remainderl, \
    nextafter, nextafterf, nextafterl) \
    when non_ansi_mode c99_mode
#endif	/* defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED) */

#if _EIDF_C99_STUFF
double 			nearbyint(double);
float 		nearbyintf(float);
long double 	nearbyintl(long double);
long int 		lrint(double);
long int 	lrintf(float);
long int 	lrintl(long double);
long long int 		llrint(double);
long long int 	llrintf(float);
long long int 	llrintl(long double);
double 			round(double);
float 		roundf(float);
long double 	roundl(long double);
long int 		lround(double);
long int 	lroundf(float);
long int 	lroundl(long double);
long long int 		llround(double);
long long int 	llroundf(float);
long long int 	llroundl(long double);
double 			remquo(double, double, int *);
float 		remquof(float, float, int *);
long double 	remquol(long double, long double, int *);
double 			nan(const char *);
float 		nanf(const char *);
long double 	nanl(const char *);
double 			nexttoward(double, long double);
float 		nexttowardf(float, long double);
long double 	nexttowardl(long double, long double);
double 			fdim(double, double);
float 		fdimf(float, float);
long double 	fdiml(long double, long double);
double 			fmax(double, double);
float 		fmaxf(float, float);
long double 	fmaxl(long double, long double);
double 			fmin(double, double);
float 		fminf(float, float);
long double 	fminl(long double, long double);
double 			fma(double, double, double);
float 		fmaf(float, float, float);
long double 	fmal(long double, long double, long double);
#pragma assert func_attrs(nearbyint, nearbyintf, nearbyintl, \
    lrint, lrintf, lrintl, llrint, llrintf, llrintl, round, roundf, roundl, \
    lround, lroundf, lroundl, llround, llroundf, llroundl, \
    remquo, remquof, remquol, nan, nanf, nanl, \
    nexttoward, nexttowardf, nexttowardl, fdim, fdimf, fdiml, fmax, fmaxf, fmaxl, \
    fmin, fminf, fminl, fma, fmaf, fmal) \
    nocalls_back nostate noeffects
#pragma intrinsic recognize(nearbyint, nearbyintf, nearbyintl, \
    lrint, lrintf, lrintl, llrint, llrintf, llrintl, round, roundf, roundl, \
    lround, lroundf, lroundl, llround, llroundf, llroundl, \
    remquo, remquof, remquol, nan, nanf, nanl, \
    nexttoward, nexttowardf, nexttowardl, fdim, fdimf, fdiml, fmax, fmaxf, fmaxl, \
    fmin, fminf, fminl, fma, fmaf, fmal)
#pragma intrinsic transform(lrint, lrintf, lrintl, llrint, llrintf, llrintl, \
    lround, lroundf, lroundl, llround, llroundf, llroundl, \
    nexttoward, nexttowardf, nexttowardl, fdim, fdimf, fdiml) \
    when assume_nomath_errno
#pragma intrinsic transform(nearbyint, nearbyintf, nearbyintl, \
    lrint, lrintf, lrintl, llrint, llrintf, llrintl, round, roundf, roundl, \
    lround, lroundf, lroundl, llround, llroundf, llroundl, \
    remquo, remquof, remquol, nan, nanf, nanl, \
    nexttoward, nexttowardf, nexttowardl, fdim, fdimf, fdiml, fmax, fmaxf, fmaxl, \
    fmin, fminf, fminl, fma, fmaf, fmal) \
    when non_ansi_mode c99_mode
#endif	/* _EIDF_C99_STUFF */

#ifdef _OSF_SOURCE
double			copysign  ( double , double );
float 		copysignf  ( float , float );
long double	copysignl(long double, long double);
double 			trunc  ( double );
float 		truncf  ( float );
long double 	truncl(long double);
#pragma assert func_attrs(trunc, truncf, truncl, copysign, copysignf, copysignl) \
    nocalls_back nostate noeffects
#pragma intrinsic recognize(trunc, truncf, truncl, copysign, copysignf, copysignl)
#pragma intrinsic transform(trunc, truncf, truncl, copysign, copysignf, copysignl) \
    when non_ansi_mode c99_mode
#endif	/* _OSF_SOURCE */

/********************************/
/*	#include <setjmp.h>	*/
/********************************/

typedef	void * __any_pointer;

/* <<< internal intrinsics
int	setjmp  ( __any_pointer );
#pragma assert func_attrs(setjmp) nocalls_back nostate noeffects file_scope_vars(none)
#pragma intrinsic recognize(setjmp)
>>> internal intrinsics */

void	longjmp  ( __any_pointer , int );
#pragma assert func_attrs(longjmp) \
    nocalls_back nostate noeffects file_scope_vars(none) noreturn
#pragma intrinsic recognize(longjmp)

/********************************/
/*	#include <signal.h>	*/
/********************************/

__any_pointer signal ( int , __any_pointer );
int raise  ( int );
#pragma assert func_attrs(signal) \
	nocalls_back nostate noeffects file_scope_vars(none)
#pragma assert func_attrs(raise) \
	file_scope_vars(none)
#pragma intrinsic recognize(signal,raise)

/********************************/
/*	#include <stdarg.h>	*/
/********************************/

typedef struct __defined_in_header __va_list;

/********************************/
/*	#include <stdbool.h>	*/
/********************************/

/********************************/
/*	#include <stddef.h>	*/
/********************************/

/********************************/
/*	#include <stdint.h>	*/
/********************************/

/********************************/
/*	#include <stdio.h>	*/
/********************************/

typedef unsigned long	__intrinsic_size_t;
typedef struct __defined_in_header __FILE;
#if (_EIDF_XOPEN_SOURCE >= 500)
  typedef struct __defined_in_header __fpos_t;
#else
  typedef long __fpos_t;
#endif

#ifdef _ANSI_C_SOURCE
int		remove  ( const char * );
int		rename  ( const char * , const char * );
__FILE *	tmpfile  ( void );
char *		tmpnam  ( char * );
int 		fclose  ( __FILE * );
int 		fflush  ( __FILE * );
__FILE *	fopen  ( const char * , const char * );
__FILE *	freopen  ( const char * , const char * , __FILE * );
void 		setbuf  ( __FILE * , char * );
int 		setvbuf  ( __FILE * , char * , int , __intrinsic_size_t );
#pragma assert func_attrs(remove, rename, tmpfile, tmpnam, fclose, fflush, \
    fopen, freopen, setbuf, setvbuf) \
    nocalls_back
#pragma intrinsic recognize(remove, rename, tmpfile, tmpnam, fclose, fflush, \
    fopen, freopen, setbuf, setvbuf)

/* <<< internal intrinsics
int		fprintf  ( __FILE * , const char * , ... );
int		fscanf  ( __FILE * , const char * , ... );
int		printf  ( const char * , ... );
int		scanf  ( const char * , ... );
int		sprintf  ( char * , const char * , ... );
int		sscanf  ( const char * , const char * , ... );

#pragma assert func_attrs(printf) format(printf,1,2)
#pragma assert func_attrs(scanf) format(scanf,1,2)
#pragma assert func_attrs(fprintf,sprintf) format(printf,2,3)
#pragma assert func_attrs(fscanf,sscanf) format(scanf,2,3)
#pragma assert func_attrs(fprintf, fscanf, printf, scanf, \
    sprintf, sscanf) \
    nocalls_back
#pragma intrinsic recognize(fprintf, fscanf, printf, scanf, \
    sprintf, sscanf)
#pragma intrinsic transform(fprintf, fscanf, printf, scanf, \
    sprintf, sscanf) \
    when preempt_module
>>> internal intrinsics */
#endif	/* _ANSI_C_SOURCE */

#if defined(_OSF_SOURCE) || _EIDF_XOPEN_SOURCE >= 500
/* <<< internal intrinsics
int		snprintf  ( char * , __intrinsic_size_t , const char * , ... );

#pragma assert func_attrs(snprintf) format(printf,3,4)
#pragma assert func_attrs(snprintf) \
    nocalls_back
#pragma intrinsic recognize(snprintf)
#pragma intrinsic transform(snprintf) \
    when preempt_module
#pragma intrinsic transform(snprintf) \
    when non_ansi_mode c99_mode
>>> internal intrinsics */
#endif	/* defined(_OSF_SOURCE) || _EIDF_XOPEN_SOURCE >= 500 */

#ifdef _ANSI_C_SOURCE
int		vfprintf  ( __FILE * , const char * , __va_list );
int		vprintf  ( const char * , __va_list );
int		vsprintf  ( char * , const char * , __va_list );

#pragma assert func_attrs(vprintf) format(printf,1,0)
#pragma assert func_attrs(vfprintf,vsprintf) format(printf,2,0)
#pragma assert func_attrs(vfprintf, vprintf, vsprintf) \
    nocalls_back
#pragma intrinsic recognize(vfprintf, vprintf, vsprintf)
#endif	/* _ANSI_C_SOURCE */

#if defined(_OSF_SOURCE) || _EIDF_XOPEN_SOURCE >= 500
int		vsnprintf  ( char *, __intrinsic_size_t, const char *, __va_list );

#pragma assert func_attrs(vsnprintf) format(printf,3,0)

#pragma assert func_attrs(vsnprintf) \
    nocalls_back
#pragma intrinsic recognize(vsnprintf)
#pragma intrinsic transform(vsnprintf) \
    when non_ansi_mode c99_mode
#endif	/* defined(_OSF_SOURCE) || _EIDF_XOPEN_SOURCE >= 500 */

#if _EIDF_C99_STUFF
int		vfscanf  ( __FILE *, const char *, __va_list );
int		vscanf  ( const char *,  __va_list );
int		vsscanf  ( const char *, const char *, __va_list );

#pragma assert func_attrs(vscanf) format(scanf,1,0)
#pragma assert func_attrs(vfscanf,vsscanf) format(scanf,2,0)

#pragma assert func_attrs(vfscanf, vscanf, vsscanf) \
    nocalls_back
#pragma intrinsic recognize(vfscanf, vscanf, vsscanf)
#pragma intrinsic transform(vfscanf, vscanf, vsscanf) \
    when non_ansi_mode c99_mode
#endif	/* _EIDF_C99_STUFF */

#ifdef _ANSI_C_SOURCE
int 		fgetc  ( __FILE * );
char *		fgets  ( char * , int , __FILE * );
int 		fputc  ( int , __FILE * );
int 		fputs  ( const char * , __FILE * );
int 		getc  ( __FILE * );
int 		getchar  ( void );
char *		gets  ( char * );
int 		putc  ( int , __FILE * );
int 		putchar  ( int );
int 		puts  ( const char * );
int		ungetc  ( int , __FILE * );
__intrinsic_size_t	fread  ( void * , __intrinsic_size_t , __intrinsic_size_t , __FILE * );
__intrinsic_size_t	fwrite  ( const void * , __intrinsic_size_t , __intrinsic_size_t , __FILE * );
int		fgetpos  ( __FILE * , __fpos_t * );
int 		fseek  ( __FILE * , long , int );
int		fsetpos  ( __FILE * , const __fpos_t * );
long		ftell  ( __FILE * );
void		rewind  ( __FILE * );
void 		clearerr  ( __FILE * );
int 		feof  ( __FILE * );
int 		ferror  ( __FILE * );
void 		perror  ( const char * );
#pragma assert func_attrs(fgetc, fgets, fputc, fputs, getc, getchar, gets, putc, putchar, \
    puts, ungetc, fread, fwrite, fgetpos, fseek, fsetpos, ftell, rewind, \
    clearerr, feof, ferror, perror) \
    nocalls_back
#pragma intrinsic recognize(fgetc, fgets, fputc, fputs, getc, getchar, gets, putc, putchar, \
    puts, ungetc, fread, fwrite, fgetpos, fseek, fsetpos, ftell, rewind, \
    clearerr, feof, ferror, perror)
#endif	/* _ANSI_C_SOURCE */

/********************************/
/*	#include <stdlib.h>	*/
/********************************/

typedef unsigned int	__wchar_t;
typedef struct __defined_in_header __div_t;
typedef struct __defined_in_header __ldiv_t;
typedef struct __defined_in_header __lldiv_t;

double 			atof  ( const char * );
int 			atoi  ( const char * );
long int 		atol  ( const char * );
double 			strtod  ( const char * , char ** );
long int 		strtol  ( const char * , char ** , int );
int 			rand  ( void );
void			srand  ( unsigned int );
#pragma assert func_attrs(atof, atoi, atol, strtod, strtol) \
    nocalls_back nostate noeffects file_scope_vars(none)
#pragma assert func_attrs(rand, srand) \
    nocalls_back noeffects file_scope_vars(none)
#pragma intrinsic recognize(atof, atoi, atol, strtod, strtol, rand, srand)

#if _EIDF_C99_STUFF
long long int		atoll  (const char * );
float			strtof  ( const char * , char ** );
long double		strtold  ( const char * , char ** );
long long int 		strtoll  ( const char *, char **, int );
unsigned long int 	strtoul  ( const char * , char ** , int );
unsigned long long int 	strtoull  ( const char *, char **, int );
#pragma assert func_attrs(atoll, strtof, strtold, strtoll, strtoul, strtoull) \
    nocalls_back nostate noeffects file_scope_vars(none)
#pragma intrinsic recognize(atoll, strtof, strtold, strtoll, strtoul, strtoull)
#pragma intrinsic transform(atoll, strtof, strtold, strtoll, strtoul, strtoull) \
    when non_ansi_mode c99_mode
#endif	/* _EIDF_C99_STUFF */

/* <<< internal intrinsics
void *			calloc  ( __intrinsic_size_t , __intrinsic_size_t );
#pragma assert func_attrs(calloc) \
    nocalls_back nostate noeffects file_scope_vars(none)
#pragma intrinsic recognize(calloc)
#pragma intrinsic transform(calloc) \
    when preempt_module
>>> internal intrinsics */

void			free  ( void * );
#pragma assert func_attrs(free) \
    nocalls_back nostate noeffects file_scope_vars(none)
#pragma intrinsic recognize(free)

/* <<< internal intrinsics
void *			malloc  ( __intrinsic_size_t );
void *			realloc  ( void * , __intrinsic_size_t );
void			abort  ( void );
#pragma assert func_attrs(malloc, realloc, abort) \
    nocalls_back nostate noeffects file_scope_vars(none)
#pragma assert func_attrs(abort) \
    noreturn
#pragma intrinsic recognize(malloc, realloc, abort)
#pragma intrinsic transform(malloc, realloc, abort) \
    when preempt_module
>>> internal intrinsics */

int			atexit  ( void ( * ) ( void ) );
#pragma assert func_attrs(atexit) \
    nocalls_back nostate noeffects file_scope_vars(none)
#pragma intrinsic recognize(atexit)

/* <<< internal intrinsics
void			exit  ( int );
#pragma assert func_attrs(exit) \
    nocalls_back nostate noeffects file_scope_vars(none) noreturn
#pragma intrinsic recognize(exit)
#pragma intrinsic transform(exit) \
    when preempt_module
>>> internal intrinsics */

void			_Exit  ( int );
char *			getenv  ( const char * );
int 			system  ( const char * );
void *			bsearch  ( const void *, const void *, __intrinsic_size_t, __intrinsic_size_t, __any_pointer );
void 			qsort  ( void *, __intrinsic_size_t, __intrinsic_size_t , __any_pointer );
#pragma assert func_attrs(_Exit, getenv, system, bsearch, qsort) \
    nocalls_back nostate noeffects file_scope_vars(none)
#pragma assert func_attrs(_Exit) \
    noreturn
#pragma intrinsic recognize(_Exit, getenv, system, bsearch, qsort)

/* <<< internal intrinsics
int 			abs  ( int );
long int		labs  ( long int );
#pragma assert func_attrs(abs, labs) \
    nocalls_back nostate noeffects file_scope_vars(none)
#pragma intrinsic recognize(abs, labs)
>>> internal intrinsics */

__div_t			div  ( int , int );
__ldiv_t 		ldiv  ( long int , long int );
int			mblen  ( const char * , __intrinsic_size_t );
int			mbtowc  ( __wchar_t * , const char * , __intrinsic_size_t );
int			wctomb  ( char * , __wchar_t );
__intrinsic_size_t	mbstowcs  ( __wchar_t * , const char * , __intrinsic_size_t );
__intrinsic_size_t	wcstombs  ( char * , const __wchar_t * , __intrinsic_size_t );
#pragma assert func_attrs(div, ldiv, mblen, mbtowc, wctomb, mbstowcs, wcstombs) \
    nocalls_back nostate noeffects file_scope_vars(none)
#pragma intrinsic recognize(div, ldiv, mblen, mbtowc, wctomb, mbstowcs, wcstombs)

#if _EIDF_C99_STUFF
long long int 		llabs  ( long long int );
__lldiv_t 		lldiv  ( long long int, long long int );
#pragma assert func_attrs(llabs, lldiv) \
    nocalls_back nostate noeffects file_scope_vars(none)
#pragma intrinsic recognize(llabs, lldiv)
#pragma intrinsic transform(llabs, lldiv) \
    when non_ansi_mode c99_mode
#endif	/* _EIDF_C99_STUFF */

/********************************/
/*	#include <string.h>	*/
/********************************/

typedef void *	__alt_ret_ptr_void;
typedef void *	__alt_ret_ptr_char;

#ifdef _ANSI_C_SOURCE
/* <<< internal intrinsics
__alt_ret_ptr_void	memcpy  ( __alt_ret_ptr_void , const void * , __intrinsic_size_t );
__alt_ret_ptr_void	memmove  ( __alt_ret_ptr_void , const void * , __intrinsic_size_t );
__alt_ret_ptr_char	strcpy  ( __alt_ret_ptr_char, const char * );
#pragma assert func_attrs(memcpy, memmove, strcpy) \
    nocalls_back nostate noeffects file_scope_vars(none)
#pragma intrinsic recognize(memcpy, memmove, strcpy)
>>> internal intrinsics */

__alt_ret_ptr_char	strncpy  ( __alt_ret_ptr_char , const char * , __intrinsic_size_t );
__alt_ret_ptr_char	strcat  ( __alt_ret_ptr_char, const char * );
__alt_ret_ptr_char	strncat  ( __alt_ret_ptr_char, const char * , __intrinsic_size_t );
int 	       		memcmp  ( const void * , const void * , __intrinsic_size_t );
int	       		strcmp  ( const char * , const char * );
int	       		strcoll  ( const char * , const char * );
int			strncmp  ( const char * , const char * , __intrinsic_size_t );
__intrinsic_size_t	strxfrm  ( char * , const char * , __intrinsic_size_t );
void *	       		memchr  ( const void * , int , __intrinsic_size_t );
char *	       		strchr  ( const char * , int );
__intrinsic_size_t 	strcspn  ( const char * , const char * );
char *	       		strpbrk  ( const char * , const char * );
char *	       		strrchr  ( const char * , int );
__intrinsic_size_t	strspn  ( const char * , const char * );
char *	       		strstr  ( const char * , const char * );
char *	       		strtok  ( char * , const char * );
#pragma assert func_attrs(strncpy, strcat, strncat, memcmp, strcmp, strcoll, \
    strncmp, strxfrm, memchr, strchr, strcspn, strpbrk, strrchr, strspn, strstr) \
    nocalls_back nostate noeffects file_scope_vars(none)
#pragma assert func_attrs(strtok) \
    nocalls_back noeffects file_scope_vars(none)
#pragma intrinsic recognize(strncpy, strcat, strncat, memcmp, strcmp, strcoll, \
    strncmp, strxfrm, memchr, strchr, strcspn, strpbrk, strrchr, strspn, strstr, strtok)

/* <<< internal intrinsics
__alt_ret_ptr_void	memset  ( __alt_ret_ptr_void , int , __intrinsic_size_t );
#pragma assert func_attrs(memset) \
    nocalls_back nostate noeffects file_scope_vars(none)
#pragma intrinsic recognize(memset)
>>> internal intrinsics */

char *	       		strerror  ( int );
#pragma assert func_attrs(strerror) \
    nocalls_back nostate noeffects file_scope_vars(none)
#pragma intrinsic recognize(strerror)

/* <<< internal intrinsics
__intrinsic_size_t	strlen  ( const char * );
#pragma assert func_attrs(strlen) \
    nocalls_back nostate noeffects file_scope_vars(none)
#pragma intrinsic recognize(strlen)
>>> internal intrinsics */
#endif	/* _ANSI_C_SOURCE */

/********************************/
/*	#include <tgmath.h>	*/
/********************************/

/********************************/
/*	#include <time.h>	*/
/********************************/

#ifdef _ANSI_C_SOURCE
typedef struct __defined_in_header __tm;
typedef int	__time_t;
typedef int	__clock_t;

__clock_t      	clock  ( void );
double	       	difftime  ( __time_t , __time_t );
__time_t       	mktime  ( __tm * );
__time_t       	time  ( __time_t * );
char *	       	asctime  ( const __tm * );
char *	       	ctime  ( const __time_t * );
__tm *	       	gmtime  ( const __time_t * );
__tm *	       	localtime  ( const __time_t * );
__intrinsic_size_t	strftime  ( char * , __intrinsic_size_t , const char * , const __tm * );
#pragma assert func_attrs(clock, difftime, mktime, time, asctime, ctime, \
    gmtime, localtime, strftime) \
    nocalls_back nostate noeffects file_scope_vars(none)
#pragma intrinsic recognize(clock, difftime, mktime, time, asctime, ctime, \
    gmtime, localtime, strftime)
#endif	/* _ANSI_C_SOURCE */

/********************************/
/*	#include <wchar.h>	*/
/********************************/

#if _EIDF_C99_STUFF
typedef struct __defined_in_header __mbstate_t;
typedef unsigned int 	__wint_t;          
typedef void *	__alt_ret_ptr_wchar_t;

int			fwprintf  ( __FILE * , const __wchar_t * , ... );
int			fwscanf  ( __FILE * , const __wchar_t * , ... );
int			swprintf  ( __wchar_t * , __intrinsic_size_t , const __wchar_t * , ... );
int			swscanf  ( const __wchar_t * , const __wchar_t * , ... );
int			vfwprintf  ( __FILE * , const __wchar_t * , __va_list );
int 			vfwscanf  ( __FILE *, const __wchar_t *, __va_list );
int			vswprintf  ( __wchar_t * , __intrinsic_size_t , const __wchar_t * , __va_list );
int 			vswscanf  ( const __wchar_t *, const __wchar_t *, __va_list );
int			vwprintf  ( const __wchar_t * , __va_list );
int 			vwscanf  ( const __wchar_t *, __va_list );
int			wprintf  ( const __wchar_t * , ... );
int			wscanf  ( const __wchar_t * , ... );
__wint_t	       	fgetwc  ( __FILE * );
__wchar_t *		fgetws  ( __wchar_t * , int , __FILE * );
__wint_t	       	fputwc  ( __wint_t , __FILE * );
int			fputws  ( const __wchar_t * , __FILE * );
int			fwide  ( __FILE *, int );
__wint_t	       	getwc  ( __FILE * );
__wint_t	       	getwchar  ( void );
__wint_t	       	putwc  ( __wint_t , __FILE * );
__wint_t	       	putwchar  ( __wint_t );
__wint_t	       	ungetwc  ( __wint_t , __FILE * );
double			wcstod  ( const __wchar_t * , __wchar_t ** );
float 			wcstof  ( const __wchar_t *, __wchar_t ** );
long double 		wcstold  ( const __wchar_t *, __wchar_t ** );
long int		wcstol  ( const __wchar_t * , __wchar_t * * , int );
long long int 		wcstoll  ( const __wchar_t *, __wchar_t **, int );
unsigned long int 	wcstoul  ( const __wchar_t * , __wchar_t ** , int );
unsigned long long int	wcstoull  ( const __wchar_t *, __wchar_t **, int );
__alt_ret_ptr_wchar_t	wcscpy  ( __alt_ret_ptr_wchar_t , const __wchar_t * );
__alt_ret_ptr_wchar_t	wcsncpy  ( __alt_ret_ptr_wchar_t , const __wchar_t * , __intrinsic_size_t );
__alt_ret_ptr_wchar_t	wmemcpy  ( __alt_ret_ptr_wchar_t , const __wchar_t * , __intrinsic_size_t );
__alt_ret_ptr_wchar_t	wmemmove  ( __alt_ret_ptr_wchar_t , const __wchar_t * , __intrinsic_size_t );
__alt_ret_ptr_wchar_t	wcscat  ( __alt_ret_ptr_wchar_t , const __wchar_t * );
__alt_ret_ptr_wchar_t	wcsncat  ( __alt_ret_ptr_wchar_t , const __wchar_t * , __intrinsic_size_t );
int			wcscmp  ( const __wchar_t * , const __wchar_t * );
int			wcscoll  ( const __wchar_t * , const __wchar_t * );
int			wcsncmp  ( const __wchar_t * , const __wchar_t * , __intrinsic_size_t );
__intrinsic_size_t	wcsxfrm  ( __wchar_t * , const __wchar_t * , __intrinsic_size_t );
int			wmemcmp  ( const __wchar_t * , const __wchar_t * , __intrinsic_size_t );
__wchar_t	*      	wcschr  ( const __wchar_t * , __wchar_t );
__intrinsic_size_t	wcscspn  ( const __wchar_t * , const __wchar_t * );
__wchar_t	*      	wcspbrk  ( const __wchar_t * , const __wchar_t * );
__wchar_t	*      	wcsrchr  ( const __wchar_t * , __wchar_t );
__intrinsic_size_t	wcsspn  ( const __wchar_t * , const __wchar_t * );
__wchar_t *		wcsstr  ( const __wchar_t * , const __wchar_t * );
__wchar_t	*      	wmemchr  ( const __wchar_t * , __wchar_t , __intrinsic_size_t );
__intrinsic_size_t     	wcslen  ( const __wchar_t * );
__alt_ret_ptr_wchar_t	wmemset  ( __alt_ret_ptr_wchar_t , __wchar_t , __intrinsic_size_t );
__wint_t		btowc  ( int );
int			wctob  ( __wint_t );
int			mbsinit  ( const __mbstate_t * );
__intrinsic_size_t	mbrlen  ( const char * , __intrinsic_size_t , __mbstate_t * );
__intrinsic_size_t	mbrtowc  ( __wchar_t * , const char * , __intrinsic_size_t , __mbstate_t * );
__intrinsic_size_t	wcrtomb  ( char * , __wchar_t , __mbstate_t * );
__intrinsic_size_t	mbsrtowcs  ( __wchar_t * , const char * * , __intrinsic_size_t , __mbstate_t * );
__intrinsic_size_t	wcsrtombs  ( char * , const __wchar_t * * , __intrinsic_size_t , __mbstate_t * );
#pragma assert func_attrs(fwprintf, fwscanf, swprintf, swscanf, vfwprintf, \
    vfwscanf, vswprintf, vswscanf, vwprintf, vwscanf, wprintf, wscanf, \
    fgetwc, fgetws, fputwc, fputws, fwide, getwc, getwchar, putwc, putwchar, \
    ungetwc) \
    nocalls_back
#pragma assert func_attrs(wcstod, wcstof, wcstold, wcstol, wcstoll, wcstoul, \
    wcstoull, wcscpy, wcsncpy, wmemcpy, wmemmove, wcscat, wcsncat, wcscmp, \
    wcscoll, wcsncmp, wcsxfrm, wmemcmp, wcschr, wcscspn, wcspbrk, wcsrchr, \
    wcsspn, wcsstr, wmemchr, wcslen, wmemset, btowc, wctob) \
    nocalls_back nostate noeffects file_scope_vars(none)
#pragma assert func_attrs(mbsinit, mbrlen, mbrtowc, wcrtomb, mbsrtowcs, wcsrtombs) \
    nocalls_back noeffects file_scope_vars(none)
#pragma intrinsic recognize(fwprintf, fwscanf, swprintf, swscanf, vfwprintf, \
    vfwscanf, vswprintf, vswscanf, vwprintf, vwscanf, wprintf, wscanf, fgetwc, \
    fgetws, fputwc, fputws, fwide, getwc, getwchar, putwc, putwchar, ungetwc, \
    wcstod, wcstof, wcstold, wcstol, wcstoll, wcstoul, wcstoull, wcscpy, \
    wcsncpy, wmemcpy, wmemmove, wcscat, wcsncat, wcscmp, wcscoll, wcsncmp, \
    wcsxfrm, wmemcmp, wcschr, wcscspn, wcspbrk, wcsrchr, wcsspn, wcsstr, \
    wmemchr, wcslen, wmemset, btowc, wctob, mbsinit, mbrlen, mbrtowc, \
    wcrtomb, mbsrtowcs, wcsrtombs)
#pragma intrinsic transform(fwprintf, fwscanf, swprintf, swscanf, vfwprintf, \
    vfwscanf, vswprintf, vswscanf, vwprintf, vwscanf, wprintf, wscanf, fgetwc, \
    fgetws, fputwc, fputws, fwide, getwc, getwchar, putwc, putwchar, ungetwc, \
    wcstod, wcstof, wcstold, wcstol, wcstoll, wcstoul, wcstoull, wcscpy, \
    wcsncpy, wmemcpy, wmemmove, wcscat, wcsncat, wcscmp, wcscoll, wcsncmp, \
    wcsxfrm, wmemcmp, wcschr, wcscspn, wcspbrk, wcsrchr, wcsspn, wcsstr, \
    wmemchr, wcslen, wmemset, btowc, wctob, mbsinit, mbrlen, mbrtowc, \
    wcrtomb, mbsrtowcs, wcsrtombs) \
    when non_ansi_mode c99_mode

#if 0
/* Interface changes between different XOPEN_SOURCE versions */
__wchar_t	*      	wcstok  ( __wchar_t * , const __wchar_t * );
__intrinsic_size_t	wcsftime  ( __wchar_t * , __intrinsic_size_t , const __wchar_t * , const __tm * );
#pragma assert func_attrs(wcsftime) \
    nocalls_back nostate noeffects file_scope_vars(none)
#pragma assert func_attrs(wcstok) \
    nocalls_back noeffects file_scope_vars(none)
#pragma intrinsic recognize(wcstok, wcsftime)
#pragma intrinsic transform(wcstok, wcsftime) \
    when non_ansi_mode c99_mode
#endif

#endif	/* _EIDF_C99_STUFF */

/********************************/
/*	#include <wctype.h>	*/
/********************************/
#if _EIDF_C99_STUFF
typedef unsigned long __wctrans_t;
typedef unsigned int __wctype_t;

int		iswalnum  ( __wint_t );
int		iswalpha  ( __wint_t );
int		iswblank  ( __wint_t );
int		iswcntrl  ( __wint_t );
int		iswdigit  ( __wint_t );
int		iswgraph  ( __wint_t );
int		iswlower  ( __wint_t );
int		iswprint  ( __wint_t );
int		iswpunct  ( __wint_t );
int		iswspace  ( __wint_t );
int		iswupper  ( __wint_t );
int		iswxdigit  ( __wint_t );
int		iswctype  ( __wint_t , __wctype_t );
__wctype_t	wctype  ( const char * );
__wint_t	towlower  ( __wint_t );
__wint_t	towupper  ( __wint_t );
__wint_t    	towctrans  ( __wint_t, __wctrans_t );
__wctrans_t 	wctrans  ( const char * );
#pragma assert func_attrs(iswalnum, iswalpha, iswblank, iswcntrl, iswdigit, \
    iswgraph, iswlower, iswprint, iswpunct, iswspace, iswupper, iswxdigit, \
    iswctype, wctype, towlower, towupper, towctrans, wctrans) \
    nocalls_back nostate noeffects file_scope_vars(none)
#pragma intrinsic recognize(iswalnum, iswalpha, iswblank, iswcntrl, iswdigit, \
    iswgraph, iswlower, iswprint, iswpunct, iswspace, iswupper, iswxdigit, \
    iswctype, wctype, towlower, towupper, towctrans, wctrans)
#pragma intrinsic transform(iswalnum, iswalpha, iswblank, iswcntrl, iswdigit, \
    iswgraph, iswlower, iswprint, iswpunct, iswspace, iswupper, iswxdigit, \
    iswctype, wctype, towlower, towupper, towctrans, wctrans) \
    when non_ansi_mode c99_mode
#endif	/* _EIDF_C99_STUFF */

#pragma required_pointer_size restore

/*
** The scope_end pragma, below, designates the end of the External
** Intrinsic Definition File and must be on the last line.
*/
#pragma intrinsic scope_end
