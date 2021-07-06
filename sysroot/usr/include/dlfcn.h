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
 * @(#)$RCSfile: dlfcn.h,v $ $Revision: 1.1.22.1 $ (DEC) $Date: 2001/09/11 18:30:28 $
 */
/*
 * dlfcn.h
 * Interface to dlopen(), dlclose(), dlsym(), dlerror().
 *
 */

/*
 * Values for 'mode' argument in dlopen().
 *
 */
#ifndef _DLFCN_H_
#define _DLFCN_H_

#include <standards.h>

#define RTLD_LAZY		1
#define RTLD_NOW		2
#define	RTLD_GLOBAL		4
#define	RTLD_LOCAL		8
#define RTLD_NEXT               (void *)-1L

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_XOPEN_SOURCE) || defined(__EXTENSIONS__)
typedef struct _dinfo {
    char *   dli_fname;       /* Filename containing address */
    void *   dli_fbase;       /* Base address for the containing object */
    char *   dli_sname;       /* Ptr to symbol name nearest to specified addr */
    void *   dli_saddr;       /* Actual addr of the above symbol */
} Dl_info;

extern int              dladdr __((void *, Dl_info *));

#endif 

extern void	*dlopen __((const char *, int ));
extern void	*dlsym __((void *, const char *));
extern char	*dlerror __((void));
extern int	 dlclose __((void *));

#ifdef __cplusplus
}
#endif

/*
 * Interface to rld via unsupported __rld_libdl_interface() call.
 *
 */
#define _LIBDL_RLD_DLOPEN	1
#define _LIBDL_RLD_DLCLOSE	2
#define _LIBDL_RLD_DLSYM	3
#define _LIBDL_RLD_DLERROR	4

#endif /* _DLFCN_H_ */
