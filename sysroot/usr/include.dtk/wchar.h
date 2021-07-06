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

#ifndef _C99WCHAR_H
#define _C99WCHAR_H 1
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>

/*
 * All the #if expressions in the base system <wchar.h> that reference
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

#include_next <wchar.h>

#if defined(__decc_stdc_199901)
#  undef  __decc_stdc_199901
#  undef  __STDC_VERSION__
#  define __STDC_VERSION__ 199901L
#endif

#if (defined(_OSF_SOURCE) && defined(__STDC_VERSION__)          \
                          && __STDC_VERSION__ >= 199901L)  ||   \
    (defined(_ISO_C_SOURCE) && _ISO_C_SOURCE  >= 199901L)

extern float wcstof(
		const wchar_t * /*restrict*/ __nptr, 
                wchar_t ** /*restrict*/ __endptr);
extern long double wcstold(
		const wchar_t * /*restrict*/ __nptr,
		wchar_t ** /*restrict*/ __endptr);

extern long long int wcstoll(
		const wchar_t * /*restrict*/ __nptr,
		wchar_t ** /*restrict*/ __endptr,
		int __base);
extern unsigned long long int wcstoull(
		const wchar_t * /*restrict*/ __nptr,
		wchar_t ** /*restrict*/ __endptr,
		int __base);

/*
** Base system wchar.h up through Wildcat includes stdio.h, which
** declares FILE, and the DTK stdio.h makes sure __VA_LIST__
** is appropriately defined.  So we can use those names here.
*/
extern int vfwscanf(
		FILE * /*restrict*/ __stream,
		const wchar_t * /*restrict*/ __format,
		__VA_LIST__ __arg);

extern int vswscanf(
		const wchar_t * /*restrict*/ __s,
		const wchar_t * /*restrict*/ __format,
		__VA_LIST__ __arg);

extern int vwscanf(
		const wchar_t * /*restrict*/ __format,
		__VA_LIST__ __arg);
extern int wprintf(
		const wchar_t * /*restrict*/ __format,
		...);
extern int wscanf(
		const wchar_t * /*restrict*/ __format,
		...);
#endif /* _OSF_SOURCE && __STDC_VERSION__ || _ISO_C_SOURCE */


#ifdef __cplusplus
}
#endif
#endif	/* _C99WCHAR_H */
