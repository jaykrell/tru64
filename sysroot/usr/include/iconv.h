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
 * 
 */
/*	
 *	@(#)$RCSfile: iconv.h,v $ $Revision: 1.1.9.4 $ (DEC) $Date: 2001/01/10 21:35:52 $
 */
/*
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */
/*
 * OSF/1 1.2
 */
/*
 *
 * COMPONENT_NAME: (LIBICONV)
 *
 * FUNCTIONS:
 *
 *
 * (C) COPYRIGHT International Business Machines Corp. 1991
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 * 
 * 1.3  com/lib/iconv/xpg_iconv.h, libiconv, bos320, 9143320i 10/22/91 16:58:57
 */

/*
 *	iconv.h
 */

#ifndef	_ICONV_H
#define	_ICONV_H


#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long size_t;
#endif

/*
 *	definition of iconv_t type.
 */

typedef struct	__iconv_rec	*iconv_t;

#ifdef _OSF_SOURCE
#include <sys/types.h>
#include <sys/localedef.h>

struct	__iconv_rec	{
	_LC_object_t	hdr;
	iconv_t	(*open)(const char *, const char *);
	size_t	(*exec)(iconv_t, char **, size_t *,
			char **, size_t *);
	void	(*close)(iconv_t);
};



typedef struct _LC_core_iconv_type	_LC_core_iconv_t;
struct _LC_core_iconv_type {

	_LC_object_t  hdr;

	/* implementation initialization */
	_LC_core_iconv_t	*(*init)();
	size_t	(*exec)();
	void	(*close)();
};

#define _LC_ICONV     10

/* typedef unsigned int	CCSID; */ /* USED ANYWHERE? */

#endif /* _OSF_SOURCE */

/*
 *	methods.
 */

#if defined(__cplusplus)
extern "C" {
#endif
extern iconv_t	iconv_open(const char *, const char *);
/*
 * provide backward compatible prototype for iconv arguments
 */
#if defined(_XOPEN_SOURCE) && !defined(_LIBC_POLLUTION_H_)

extern size_t	iconv(iconv_t, char **, size_t *, char **, size_t *);

#else /* XOPEN_SOURCE */

extern size_t	iconv(iconv_t, const char **, size_t *, char **, size_t *);

#endif /* _XOPEN_SOURCE && !_LIBC_POLLUTION_H_ */

extern int 	iconv_close(iconv_t);
#if defined(__cplusplus)
}
#endif

#endif	/* _ICONV_H */
