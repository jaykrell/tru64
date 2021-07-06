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
/* $Header: /share/buffer/build/rcs.dsk1/os/src/usr/include/alpha/stdarg.h,v 1.2.13.3 1998/07/17 13:15:36 Arvind_Jagannath Exp $ */
/*      @(#)stdarg.h    1.1     */

#ifndef _STDARG_H
#define _STDARG_H

#include <standards.h>

#ifdef _ANSI_C_SOURCE

#include <va_list.h>		/* defines va_list */

#ifdef _OSF_SOURCE
#define va_dcl long va_alist;
#endif /* _OSF_SOURCE */

#define va_start(list, parmN) __builtin_va_start(list, parmN, 1)
#define va_end(list) ((void)0)
#if defined(__LINT)
#define va_arg(list, mode) \
                (*(mode *)(((list)._offset += ((int)sizeof(mode) + 7) & -8)))
#else
#define va_arg(list, mode) \
	(*((__builtin_isfloat(mode) && sizeof(mode) > sizeof(double)) ? \
	   *(((list)._offset += ((int)sizeof(mode *) + 7) & -8), \
	     (mode **)( ((char *)(list)._a0) + (list)._offset - \
		(((int)sizeof(mode *) + 7) & -8))) : \
	   (((list)._offset += ((int)sizeof(mode) + 7) & -8), \
	    (mode *)( ((char *)(list)._a0) + (list)._offset - \
		     ((__builtin_isfloat(mode) && (list)._offset <= (6 * 8)) ? \
		      (6 * 8) + 8 : ((int)sizeof(mode) + 7) & -8)))))

#endif
#endif /* _ANSI_C_SOURCE */
#endif /* _STDARG_H */
