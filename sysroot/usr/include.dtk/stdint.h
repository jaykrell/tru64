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
 * $Log: stdint.h,v $
 * $EndLog$
 */

#ifndef	_STDINT_H
#define	_STDINT_H
#include <standards.h>


#ifndef __BIT_TYPES_DEFINED__
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;
#endif

typedef long int intptr_t;
typedef unsigned long int uintptr_t;

typedef signed long   intmax_t;
typedef unsigned long uintmax_t;

typedef signed char   int_least8_t;
typedef unsigned char uint_least8_t;

typedef signed short   int_least16_t;
typedef unsigned short uint_least16_t;

typedef signed int   int_least32_t;
typedef unsigned int uint_least32_t;

typedef signed long   int_least64_t;
typedef unsigned long uint_least64_t;

typedef signed int  int_fast8_t;
typedef unsigned int uint_fast8_t;

typedef signed int   int_fast16_t;
typedef unsigned int uint_fast16_t;

typedef signed int   int_fast32_t;
typedef unsigned int uint_fast32_t;

typedef signed long  int_fast64_t;
typedef unsigned long uint_fast64_t;


#if !defined(__cplusplus) ||  defined(__STDC_CONSTANT_MACROS)

/*
** Note we cannot #include <limits.h> or <wchar.h>, since this
** would cause other names to be defined that are not defined
** by stdint.h.  Instead of inventing a lower-level file that
** doesn't pollute the namespace to be used by all of these files,
** we just duplicate the constants here where needed.
*/
/* 
** Integer constants having the value specified by its
** argument and the type intmax_t or untmax_t
*/
#define INTMAX_C(_val)	_val ## L
#define UINTMAX_C(_val)	_val ## UL

#define INT8_C(_val)	((int_least8_t)_val)
#define UINT8_C(_val)	((uint_least8_t)_val)
#define INT16_C(_val)	((int_least16_t)_val)
#define UINT16_C(_val)	((uint_least16_t)_val)
#define INT32_C(_val)	_val
#define UINT32_C(_val)	_val ## U
#define INT64_C(_val)	_val ## L
#define UINT64_C(_val)	_val ## UL

#endif	/* !__cplusplus || __STDC_CONSTANT_MACROS */

#if !defined(__cplusplus) || defined(__STDC_LIMIT_MACROS)

/* See also <machine/machlimits.h> */

/* Limits of exact-width integer types */
#define INT8_MAX	127
#define INT16_MAX	32767
#define INT32_MAX	2147483647
#define INT64_MAX	9223372036854775807

#define INT8_MIN	(-INT8_MAX-1)
#define INT16_MIN	(-INT16_MAX-1)
#define INT32_MIN	(-INT32_MAX-1)
#define INT64_MIN	(-INT64_MAX-1)

#define UINT8_MAX	255U
#define UINT16_MAX	65535U
#define UINT32_MAX	4294967295U
#define UINT64_MAX	18446744073709551615U

/* Limits of minimum-width integer types */
#define INT_LEAST8_MAX	INT8_MAX
#define INT_LEAST16_MAX	INT16_MAX
#define INT_LEAST32_MAX	INT32_MAX
#define INT_LEAST64_MAX	INT64_MAX

#define INT_LEAST8_MIN	(-INT_LEAST8_MAX-1)
#define INT_LEAST16_MIN	(-INT_LEAST16_MAX-1)
#define INT_LEAST32_MIN	(-INT_LEAST32_MAX-1)
#define INT_LEAST64_MIN	(-INT_LEAST64_MAX-1)

#define UINT_LEAST8_MAX	 UINT8_MAX
#define UINT_LEAST16_MAX UINT16_MAX
#define UINT_LEAST32_MAX UINT32_MAX
#define UINT_LEAST64_MAX UINT64_MAX

/* Limits of fastest minimum-width integer types */
#define INT_FAST8_MAX	INT8_MAX
#define INT_FAST16_MAX	INT16_MAX
#define INT_FAST32_MAX	INT32_MAX
#define INT_FAST64_MAX	INT64_MAX

#define INT_FAST8_MIN	(-INT_FAST8_MAX-1)
#define INT_FAST16_MIN	(-INT_FAST16_MAX-1)
#define INT_FAST32_MIN  (-INT_FAST32_MAX-1)
#define INT_FAST64_MIN  (-INT_FAST64_MAX-1)

#define UINT_FAST8_MAX	UINT8_MAX
#define UINT_FAST16_MAX	UINT16_MAX
#define UINT_FAST32_MAX	UINT32_MAX
#define UINT_FAST64_MAX	UINT64_MAX

/* Limits of integer types capable of holding object pointers */
#define INTPTR_MAX	INT64_MAX
#define INTPTR_MIN	(-INTPTR_MAX-1)
#define UINTPTR_MAX	UINT64_MAX

/* Limits of greatest-width integer types */
#define INTMAX_MAX	INT64_MAX
#define INTMAX_MIN	(-INTMAX_MAX-1)
#define UINTMAX_MAX	UINT64_MAX

/* Limits of other integer types */
#define PTRDIFF_MAX	INTPTR_MAX
#define PTRDIFF_MIN	INTPTR_MIN

/* limits of sig_atomic_t (see <machine/signal.h> ) */
#define SIG_ATOMIC_MAX	INT32_MAX
#define SIG_ATOMIC_MIN	INT32_MIN

/* Limit of size_t (see <sys/types.h> */
#define SIZE_MAX	UINTPTR_MAX

/* Limits of wchar_t and wint_t (see <wchar.h>) */
#define WCHAR_MIN	0

/* defined in <wchar.h> */
#ifndef WCHAR_MAX
#define WCHAR_MAX	UINT32_MAX
#endif

#define WINT_MIN	0
#define WINT_MAX	UINT32_MAX

#endif  /* !__cplusplus || __STDC_LIMIT_MACROS */

#endif	/* _STDINT_H */
