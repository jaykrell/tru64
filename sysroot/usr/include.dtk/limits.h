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

#ifndef _C99LIMITS_H
#define _C99LIMITS_H 1
#include <standards.h>

#include_next <limits.h>

#if (defined(_OSF_SOURCE) && defined(__STDC_VERSION__)          \
                          && __STDC_VERSION__ >= 199901L)  ||   \
    (defined(_ISO_C_SOURCE) && _ISO_C_SOURCE  >= 199901L)
/* max value for a long long int - 263-1 */
#define LLONG_MAX     9223372036854775807

/* min value for a long long int -(263-1) */
#define LLONG_MIN     (-LLONG_MAX-1)

/* max value for an unsigned long long int -  2**64-1 */
#define ULLONG_MAX    18446744073709551615U

#endif /* _OSF_SOURCE && __STDC_VERSION__ || _ISO_C_SOURCE */

#endif	/* _C99LIMITS_H */
