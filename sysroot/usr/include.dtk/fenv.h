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
 * $Log: fenv.h,v $
 * $EndLog$
 */

/*
** NOTE:  This C99-specified header currently provides only
**        stubs for C99-defined functions.  It is not compatible
**        for inclusion with the machine-specific header
**        /usr/include/alpha/fpu.h, which provides similar
**        functionality but not through C99-specified
**        interfaces.  A given compilation should include
**        either fenv.h or fpu.h, but not both.
*/

/*
** ISO/IEC 9899:1999 (E)		(a.k.a. the C99 standard)
**
** The header <fenv.h> declares two types and several macros and
** functions to provide access to the C99 floating-point environment.
** It is designed to support the floating-point exception status flags
** and directed-rounding control modes required by IEC 60559, and
** other similar floating-point state information.
*/

#ifndef _FENV_H
#define _FENV_H 1
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>
        /*
	** NOTE: We have changed the prototype declarations of the
        ** following 7 APIs to return int rather than void as specified
	** in the ISO standard published in December, 1999.  A Technical
	** Corrigendum to the C99 standard is in progress that will
	** correct the standard to specify a return type of int for:
	**   feclearexcept, fegetexceptflag, feraiseexcept, fesetexceptflag,
	**   fegetenv, fesetenv, feupdateenv
	** In all cases, the functions return a zero value to indicate
	** that all actions were successfully carried out, and a non-zero
	** value to indicate that one or more actions failed.  
	*/

/*
** 7.6 Floating-point environment
*/

	/* 
	** A type that represents the floating-point status flags
	** collectively, including any status the implementation
	** associates with the flags.
	*/
typedef unsigned int fexcept_t;

	/* 
	** A type that represents the entire floating-point
	** environment.  The floating-point environment refers
	** collectively to any floating-point status flags and control
	** modes supported by the implementation.
	** 
	** A floating-point status flag is a system variable whose
	** value is set (but never cleared) when a floating-point
	** exception is raised, which occurs as a side effect of
	** exceptional floating-point arithmetic to provide auxiliary
	** information. 
	** 
	** A floating-point control mode is a system variable whose
	** value may be set by the user to affect the subsequent
	** behavior of floating-point arithmetic.
	*/
typedef struct {
  fexcept_t	__fenv_exceptions_raised;
  int		__fenv_rounding_mode;
} fenv_t;

	/*
	** Each of the following floating-point exception macros is
	** defined if and only if the implementation supports that
	** floating-point exception by means of the functions in
	** 7.6.2.  Additional floating-point exception macros
	** beginning with FE_ and an uppercase letter may also be
	** specified by the implementation.
	** 
	** The defined macros expand to integer constant expressions
	** with values such that bitwise ORs of all combinations of
	** the macros result in distinct values.
	**
	** By not defining any of these macros, we are asserting that
	** none of these exceptions are supported by the mechanisms
	** of fenv.h.
	*/
#undef FE_DIVBYZERO
#undef FE_INEXACT
#undef FE_INVALID
#undef FE_OVERFLOW
#undef FE_UNDERFLOW

	/*
	** The following macro is simply the bitwise OR of all
	** floating-point exception macros defined by the
	** implementation.  
	*/
#define FE_ALL_EXCEPT 0

	/*
	** Each of the following rounding direction macros is defined
	** if and only if the implementation supports getting and
	** setting that rounding direction by means of the fegetround
	** and fesetround functions in 7.6.3.  Additional rounding
	** direction macros beginning with FE_ and an uppercase letter
	** may also be specified by the implementation.
	** 
	** The defined macros expand to integer constant expressions
	** whose values are distinct nonnegative values.
	** 
	******************************************************************
	** 
	** NOTE: Pending a more complete and usable implementation,
	** we have removed the temporary support for rounding modes
	** from the previous version of this file.  Since this file
	** defines no FE_* rounding mode macros, none are supported
	** be these API's at this time.
	**
	** It would have been nice to use the values of IEEE rounding
	** modes required by the Tru64 UNIX and OpenVMS Alpha functions
	** read_rnd and write_rnd, which also happen to correspond to
	** the permissible nonnegative values defined for FLT_ROUNDS
	** in <float.h> (FLT_ROUNDS==1).  Unfortunately, the system
	** header /usr/include/alpha/fpu.h already defines exactly
	** the names required for C99 rounding modes, but with different
	** values than those used for those modes in float.h and for
	** values of the standard C FLT_ROUNDS macro.
	**
	** We're stuck with the names in C99, and it's not reasonable
	** to define these macros with different values than they
	** have in fpu.h, even though the current fpu.h is not particularly
	** compatible with the standard-defined fenv.h.
	**
	** We'll probably wind up by mapping between the
	** FE_ values and the FLT_ROUNDS values (which are also the
	** values used by the system's read_rnd and write_rnd routines).
	** But note that since fpu.h does define these FE_ macros,
	** for the time being an application would have to rely on
	** the return results from these functions to determine
	** that the controls were not actually being set.  In a
	** future version, these API's will be able to control the
	** rounding modes using the FE_ names and values defined
	** in fpu.h, and compatibility between fpu.h and fenv.h
	** will need to be worked out since they have very substantial
	** overlap.
	*/

static const int __fenv_FE_to_rnd[] = {0, 3, 1, 2};
static const int __fenv_rnd_to_FE[] = {0, 2, 3, 1};

#define __fenv_default_rounding 2
fenv_t __fenv_Current_Env;

	/*
	** The following macro represents the default floating-point
	** environment -- the one installed at program startup.  It
	** can be used as an argument to the functions in 7.6.4. 
	** 
	** Additional implementation-defined environments, with macro
	** definitions beginning with FE_ and an uppercase letter, and
	** having type "pointer to const-qualified fenv_t", may also
	** be specified by the implementation.
	*/
static const
  fenv_t __fenv_Default_Env = { 0, 0 };
#define FE_DFL_ENV (&__fenv_Default_Env)

/*
** 7.6.1 The FENV_ACCESS pragma
**	#pragma STDC FENV_ACCESS {ON|OFF}
**
**	Minimal implementation, recognized and ignored.
**
** 7.6.2 Floating-point exceptions
**	Minimal implementation.  Since no exceptions are defined, none
**	need be raised.
*/

static 
int feclearexcept( int __excepts ) {
    return -1;
}

static 
int fegetexceptflag( fexcept_t *__flagp, int __excepts ) { 
    return -1;
}

static
int feraiseexcept( int __excepts ) {
    return -1;
}

static
int fesetexceptflag( const fexcept_t *__flagp, int __excepts ) {
    return -1;
}

static
int fetestexcept( int __excepts ) {
  return 0;
}

/*
** 7.6.3 Rounding
*/

static
int fegetround( void ) {
    return -1;
}

static
int fesetround( int __round ) {
    return -1;
}

/*
** 7.6.4 Environment
**	Since no exceptions are defined, there are no floating-point
**	status flags to be set with fesetenv or updated with
**	feupdateenv.   But we do need to handle rounding modes.
*/

static
int fegetenv( fenv_t *__envp ) {
    return -1;
}

static
int feholdexcept( fenv_t *__envp ) {
    return -1;
}

static
int fesetenv( const fenv_t *__envp ) {
    return -1;
}

static
int feupdateenv( const fenv_t *__envp ) {
    return -1;
}


#ifdef __cplusplus
}
#endif
#endif /* _FENV_H */
