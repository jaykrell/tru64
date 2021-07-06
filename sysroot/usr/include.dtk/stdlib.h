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

#ifndef _C99STDLIB_H
#define _C99STDLIB_H 1
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>

#include_next <stdlib.h>

#if (defined(_OSF_SOURCE) && defined(__STDC_VERSION__)          \
                          && __STDC_VERSION__ >= 199901L)  ||   \
    (defined(_ISO_C_SOURCE) && _ISO_C_SOURCE  >= 199901L)

    extern void _Exit ( int );

    extern long long int atoll(const char *__nptr);

    extern float strtof(
		const char * /*restrict*/ __nptr,
		char ** /*restrict*/ __endptr);

    extern long double strtold(
		const char * /*restrict*/ __nptr,
		char ** /*restrict*/ __endptr);

    extern long long int strtoll(
		const char * /*restrict*/ __nptr,
    		char ** /*restrict*/ __endptr,
    		int __base);

    extern unsigned long long int strtoull(
    		const char * /*restrict*/ __nptr,
    		char ** /*restrict*/ __endptr,
    		int __base);

    extern long long int llabs(long long int __j);

    typedef struct lldiv_t {		/* struct returned from lldiv */
        long long int quot;		/* quotient                   */
        long long int rem; } lldiv_t;	/* remainder                  */

    extern lldiv_t lldiv(
		long long int __numer,
		long long int __denom);

#endif /* _OSF_SOURCE && __STDC_VERSION__ || _ISO_C_SOURCE */
 
#ifdef __cplusplus
}
#endif
#endif	/* _C99STDLIB_H */
