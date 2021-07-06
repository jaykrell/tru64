/*
 * ********************************************************************************
 * *                                                                              *
 * *    Copyright 2002 Compaq Information Technologies Group, L.P.                *
 * *                                                                              *
 * *    Compaq and the Compaq logo are trademarks of Compaq Information           *
 * *    Technologies Group, L.P. in the U.S. and/or other countries.              *
 * *                                                                              *
 * *    Confidential computer software. Valid license from Compaq required for    *
 * *    possession, use or copying. Consistent with FAR 12.211 and 12.212,        *
 * *    Commercial Computer Software, Computer Software Documentation, and        *
 * *    Technical Data for Commercial Items are licensed to the U.S. Government   *
 * *    under vendor's standard commercial license.                               *
 * *                                                                              *
 * ********************************************************************************
 */

#ifndef _C99WCTYPE_H
#define _C99WCTYPE_H 1
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>

/*
 * All the #if expressions in the base system <wctype.h> that reference
 * __STDC_VERSION__ use the expression (__STDC_VERSION__ == 199409).
 * Temporarily redefine __STDC_VERSION__ when (__STDC_VERSION__ == 199901L). 
 */

#if defined(__STDC_VERSION__)
#  if __STDC_VERSION__ == 199901L
#    define __decc_stdc_199901
#    undef  __STDC_VERSION__
#    define __STDC_VERSION__ 199409
#  elif __STDC_VERSION__ != 199409
#    error __STDC_VERSION__ has a value that is not recognized.
#  endif
#endif

#include_next <wctype.h>

#if defined(__decc_stdc_199901)
#  undef  __decc_stdc_199901
#  undef  __STDC_VERSION__
#  define __STDC_VERSION__ 199901L
#endif

#ifdef __cplusplus
}
#endif
#endif	/* _C99WCTYPE_H */
