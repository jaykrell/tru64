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
 * @(#)$RCSfile: timemisc.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2000/01/14 14:34:46 $
 */
/*
 * *****************************************************************
 * *                                                               *
 * *    Copyright (c) Digital Equipment Corporation, 1991, 1999    *
 * *                                                               *
 * *   All Rights Reserved.  Unpublished rights  reserved  under   *
 * *   the copyright laws of the United States.                    *
 * *                                                               *
 * *   The software contained on this media  is  proprietary  to   *
 * *   and  embodies  the  confidential  technology  of  Digital   *
 * *   Equipment Corporation.  Possession, use,  duplication  or   *
 * *   dissemination of the software and media is authorized only  *
 * *   pursuant to a valid written license from Digital Equipment  *
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
 * @(#)$RCSfile: timemisc.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2000/01/14 14:34:46 $
 */

#ifndef _SYS_TIMEMISC_H
#define _SYS_TIMEMISC_H
#if defined(__cplusplus)
extern "C"
{
#endif

#include <sys/types.h>

#if defined(__LANGUAGE_C__) || defined(__cplusplus)

#if defined(_OSF_SOURCE) || ( defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L) )
typedef struct timespec {
        time_t  tv_sec;         /* seconds */
        long    tv_nsec;        /* nanoseconds */
} timespec_t;

#ifdef  _OSF_SOURCE
/*
 * Internal profiling arguments.
 */
struct uuprof {                 /* profile arguments */
        short           *pr_base;       /* buffer base */
        unsigned long   pr_size;        /* buffer size */
        unsigned long   pr_off;         /* pc offset */
        unsigned long   pr_scale;       /* pc scaling */
};
#endif  /* _OSF_SOURCE */
#endif /* _OSF_SOURCE || _POSIX_C_SOURCE */

#endif /* __LANGUAGE_C__ || __cplusplus */

#if defined(__cplusplus)
}
#endif
#endif /* _SYS_TIMEMISC_H */
