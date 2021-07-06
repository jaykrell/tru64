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
 * $Log: inttypes.h,v $
 * $EndLog$
 */

#ifndef	_C99INTTYPES_H
#define	_C99INTTYPES_H 1
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>

/* Do two completely different things, depending on whether
 * or not C99 functionality is enabled.
 */
#if (defined(_OSF_SOURCE) && defined(__STDC_VERSION__)          \
                          && __STDC_VERSION__ >= 199901L)  ||   \
    (defined(_ISO_C_SOURCE) && _ISO_C_SOURCE  >= 199901L)

/* C99 version */
#include <stdint.h>

/* functions for manipulating greatest-width integers */

/* Similar to ldiv_t in <stdlib.h> */
typedef struct imaxdiv_t 
{
  long int quot;	/* quotient                     */
  long int rem;		/* remainder                    */
} imaxdiv_t;


imaxdiv_t imaxdiv(intmax_t __numer, intmax_t __denom);
intmax_t  imaxabs(intmax_t __j);

/*
** functions for converting numeric character strings to
** greatest-width integers
*/

intmax_t  strtoimax(const char * /*restrict*/ __nptr,
		    char ** /*restrict*/ __endptr, int __base);

uintmax_t strtoumax(const char * /*restrict*/ __nptr,
		    char ** /*restrict*/ __endptr, int __base);

/*
** The wcstoimax and wcstoumax functions are equivalent to
** the  wcstol, wcstoll, wcstoul, and wcstoull functions except
** that the initial portion of the wide string is converted  to
** intmax_t and uintmax_t representation, respectively.
*/

/*
** These need the underlying type of wchar_t, but cannot include
** other headers to get and use it, since this header is not allowed
** to declare that identifier.
*/
#ifndef __WCHAR_T_LEN
#    define __WCHAR_T_LEN 4
#endif

#if __WCHAR_T_LEN == 1
    typedef unsigned char __inttypes_wchar_t;
#elif __WCHAR_T_LEN == 2
    typedef unsigned short __inttypes_wchar_t;
#else
    typedef unsigned int  __inttypes_wchar_t;
#endif /* __WCHAR_T_LEN == ?? */

intmax_t wcstoimax(const __inttypes_wchar_t * /*restrict*/ __nptr,
		   __inttypes_wchar_t ** /*restrict*/ __endptr, int __base);

uintmax_t wcstoumax(const __inttypes_wchar_t * /*restrict*/ __nptr,
		    __inttypes_wchar_t ** /*restrict*/ __endptr, int __base);


#if !defined(__cplusplus) || defined(__STDC_FORMAT_MACROS)

/* begin - fprintf macros for signed integers */
#define PRId8		"d"
#define PRId16		"d"
#define PRId32		"d"
#define PRId64		"ld"

#define PRIdLEAST8	"d"
#define PRIdLEAST16	"d"
#define PRIdLEAST32	"d"
#define PRIdLEAST64	"ld"

#define PRIdFAST8	"d"
#define PRIdFAST16	"d"
#define PRIdFAST32	"d"
#define PRIdFAST64	"ld"

#define PRIdMAX		"ld"
#define PRIdPTR		"ld"

#define PRIi8		"i"
#define PRIi16		"i"
#define PRIi32		"i"
#define PRIi64		"li"

#define PRIiLEAST8	"i"
#define PRIiLEAST16	"i"
#define PRIiLEAST32	"i"
#define PRIiLEAST64	"li"

#define PRIiFAST8	"i"
#define PRIiFAST16	"i"
#define PRIiFAST32	"i"
#define PRIiFAST64	"li"

#define PRIiMAX		"li"
#define PRIiPTR		"li"

/*  end  - fprintf macros for signed integers */

/* begin - fprintf macros for unsigned integers */

#define PRIo8		"o"
#define PRIo16		"o"
#define PRIo32		"o"
#define PRIo64		"lo"

#define PRIoLEAST8	"o"
#define PRIoLEAST16	"o"
#define PRIoLEAST32	"o"
#define PRIoLEAST64	"lo"

#define PRIoFAST8	"o"
#define PRIoFAST16	"o"
#define PRIoFAST32	"o"
#define PRIoFAST64	"lo"

#define PRIoMAX		"o"
#define PRIoPTR		"lo"

#define PRIu8		"u"
#define PRIu16		"u"
#define PRIu32		"u"
#define PRIu64		"lu"

#define PRIuLEAST8	"u"
#define PRIuLEAST16	"u"
#define PRIuLEAST32	"u"
#define PRIuLEAST64	"lu"

#define PRIuFAST8	"u"
#define PRIuFAST16	"u"
#define PRIuFAST32	"u"
#define PRIuFAST64	"lu"

#define PRIuMAX		"lu"
#define PRIuPTR		"lu"

#define PRIx8		"x"
#define PRIx16		"x"
#define PRIx32		"x"
#define PRIx64		"lx"

#define PRIxLEAST8	"x"
#define PRIxLEAST16	"x"
#define PRIxLEAST32	"x"
#define PRIxLEAST64	"lx"

#define PRIxFAST8	"x"
#define PRIxFAST16	"x"
#define PRIxFAST32	"x"
#define PRIxFAST64	"lx"

#define PRIxMAX		"lx"
#define PRIxPTR		"lx"

#define PRIX8		"X"
#define PRIX16		"X"
#define PRIX32		"X"
#define PRIX64		"X"

#define PRIXLEAST8	"X"
#define PRIXLEAST16	"X"
#define PRIXLEAST32	"X"
#define PRIXLEAST64	"lX"

#define PRIXFAST8	"X"
#define PRIXFAST16	"X"
#define PRIXFAST32	"X"
#define PRIXFAST64	"lX"

#define PRIXMAX		"lX"
#define PRIXPTR		"lX"

/*  end  - fprintf macros for unsigned integers */


/* begin - fscanf macros for signed integers */

#define SCNd8		"d"
#define SCNd16		"d"
#define SCNd32		"d"
#define SCNd64		"ld"

#define SCNdLEAST8	"d"
#define SCNdLEAST16	"d"
#define SCNdLEAST32	"d"
#define SCNdLEAST64	"ld"

#define SCNdFAST8	"d"
#define SCNdFAST16	"d"
#define SCNdFAST32	"d"
#define SCNdFAST64	"ld"

#define SCNdMAX		"ld"
#define SCNdPTR		"ld"

#define SCNi8		"i"
#define SCNi16		"i"
#define SCNi32		"i"
#define SCNi64		"li"

#define SCNiLEAST8	"i"
#define SCNiLEAST16	"i"
#define SCNiLEAST32	"i"
#define SCNiLEAST64	"li"

#define SCNiFAST8	"i"
#define SCNiFAST16	"i"
#define SCNiFAST32	"i"
#define SCNiFAST64	"li"

#define SCNiMAX		"li"
#define SCNiPTR		"li"

/*  end  - fscanf macros for signed integers */

/* begin - fscanf macros for unsigned integers */

#define SCNo8		"o"
#define SCNo16		"o"
#define SCNo32		"o"
#define SCNo64		"lo"

#define SCNoLEAST8	"o"
#define SCNoLEAST16	"o"
#define SCNoLEAST32	"o"
#define SCNoLEAST64	"lo"

#define SCNoFAST8	"o"
#define SCNoFAST16	"o"
#define SCNoFAST32	"o"
#define SCNoFAST64	"lo"

#define SCNoMAX		"lo"
#define SCNoPTR		"lo"

#define SCNu8		"u"
#define SCNu16		"u"
#define SCNu32		"u"
#define SCNu64		"lu"

#define SCNuLEAST8	"u"
#define SCNuLEAST16	"u"
#define SCNuLEAST32	"u"
#define SCNuLEAST64	"lu"

#define SCNuFAST8	"u"
#define SCNuFAST16	"u"
#define SCNuFAST32	"u"
#define SCNuFAST64	"lu"

#define SCNuMAX		"lu"
#define SCNuPTR		"lu"

#define SCNx8		"x"
#define SCNx16		"x"
#define SCNx32		"x"
#define SCNx64		"lx"

#define SCNxLEAST8	"x"
#define SCNxLEAST16	"x"
#define SCNxLEAST32	"x"
#define SCNxLEAST64	"lx"

#define SCNxFAST8	"x"
#define SCNxFAST16	"x"
#define SCNxFAST32	"x"
#define SCNxFAST64	"lx"

#define SCNxMAX		"lx"
#define SCNxPTR		"lx"

/*  end  - fscanf macros for unsigned integers */

#endif  /* __STDC_FORMAT_MACROS */

#else
/* Without C99 features enabled, just give the existing base
 * system inttypes.h header, if any.
 */
#include_next <inttypes.h>
#endif /* _OSF_SOURCE && __STDC_VERSION__ || _ISO_C_SOURCE */

#ifdef __cplusplus
}
#endif
#endif	/* _C99INTTYPES_H */
