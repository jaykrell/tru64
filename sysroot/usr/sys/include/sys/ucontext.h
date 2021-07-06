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
 * @(#)$RCSfile: ucontext.h,v $ $Revision: 1.1.12.1 $ (DEC) $Date: 2000/01/14 14:34:50 $
 */

#ifndef _SYS_UCONTEXT_H
#define _SYS_UCONTEXT_H
#if defined(__cplusplus)
extern "C"
{
#endif

# if  !defined (_XOPEN_SOURCE) || (_XOPEN_SOURCE < 500)
#include <sys/signalmisc.h>
#include <sys/timemisc.h>
#endif /* !_XOPEN_SOURCE || _XOPEN_SOURCE<500 */

#ifdef _OSF_SOURCE
#include <sys/user.h>
#endif

/* defines the mcontext_t and ucontext_t types */
#include <sys/context_t.h>

#if defined (_OSF_SOURCE) || defined (_XOPEN_SOURCE_EXTENDED)

/* These are new functions required for Spec1170 */
extern int getcontext __((ucontext_t *));
extern int setcontext __((const ucontext_t *));
extern void makecontext __((ucontext_t *, void (*)(void), int, ...));
extern int swapcontext __((ucontext_t *, const ucontext_t *));

#endif /* defined (_OSF_SOURCE) || defined (_XOPEN_SOURCE_EXTENDED) */

#if defined(__cplusplus)
}
#endif
#endif /* _SYS_UCONTEXT_H */
