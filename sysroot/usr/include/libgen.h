/*
 * *****************************************************************
 * *                                                               *
 * *   Copyright 2002 Compaq Information Technologies Group, L.P.  *
 * *                                                               *
 * *   The software contained on this media  is  proprietary  to   *
 * *   and  embodies  the  confidential  technology  of  Compaq    *
 * *   Computer Corporation.  Possession, use,  duplication  or    *
 * *   dissemination of the software and media is authorized only  *
 * *   pursuant to a valid written license from Compaq Computer    *
 * *   Corporation.                                                *
 * *                                                               *
 * *   RESTRICTED RIGHTS LEGEND   Use, duplication, or disclosure  *
 * *   by the U.S. Government is subject to restrictions  as  set  *
 * *   forth in Subparagraph (c)(1)(ii)  of  DFARS  252.227-7013,  *
 * *   or  in  FAR 52.227-19, as applicable.                       *
 * *                                                               *
 * *****************************************************************
 */
/*
 * HISTORY
 */
/*
 * @(#)$RCSfile: libgen.h,v $ $Revision: 1.1.6.3 $ (DEC) $Date: 1996/10/16 18:58:55 $
 */

/* Spec1170 - definitions for pattern matching functions */

#ifndef _LIBGEN_H_
#define _LIBGEN_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>


#ifdef _XOPEN_SOURCE_EXTENDED

extern char      *__loc1;     /* Used by regex() to report pattern location */

extern char    *regcmp __((const char  * , ...));

/* declaration & renaming block for basename() & dirname() */
#ifndef _LIBC_POLLUTION_H_
#ifdef __DECC
#pragma extern_prefix "_E"
#else
#define basename(__a) _Ebasename(__a)
#define dirname(__a) _Edirname(__a)
#endif
#endif /* !_LIBC_POLLUTION_H_ */
extern char    * __R(basename) __((char  *));
extern char    * __R(dirname) __((char  *));
#ifndef _LIBC_POLLUTION_H_
#ifdef __DECC
#pragma extern_prefix ""
#endif
#endif /* !_LIBC_POLLUTION_H_ */

extern char    *regex __((const char  * , const char  * , ...));

#endif /* _XOPEN_SOURCE_EXTENDED */

extern char    * __R(basename) __((char  *));
extern char    * __R(dirname) __((char  *));

#ifdef __cplusplus
}
#endif
#endif   /* _LIBGEN_H_ */
