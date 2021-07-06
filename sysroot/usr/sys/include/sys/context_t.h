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
 * @(#)$RCSfile: context_t.h,v $ $Revision: 1.1.4.1 $ (DEC) $Date: 2000/01/14 14:34:37 $
 */

#ifndef _SYS_CONTEXT_T_H
#define _SYS_CONTEXT_T_H
#if defined(__cplusplus)
extern "C"
{
#endif

#include <sys/types.h>

/* defines the machine dependent sigcontext structure */
#include <machine/context.h>

/* 
 * The structure stack_t is redefined here as in signalmisc.h,  
 * as inclusion of signalmisc.h here for this structure         
 * creates namespace problems in XSH5. 
 */

#ifndef _STACK_T
#define _STACK_T
#if defined(__LANGUAGE_C__) || defined(__cplusplus)

#if defined(_OSF_SOURCE) || ( defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L) ) || defined(_XOPEN_SOURCE_EXTENDED)

#ifndef _XOPEN_SOURCE_EXTENDED
typedef struct  sigaltstack {
        caddr_t ss_sp;                  /* signal stack pointer */
#else
typedef struct {
        void    *ss_sp;                 /* signal stack pointer */
#endif
        int     ss_flags;               /* current status */
        size_t  ss_size;                /* size of stack - 0 if unknown */
} stack_t;
#endif /*_OSF_SOURCE || _POSIX_C_SOURCE || _XOPEN_SOURCE_EXTENDED */

#endif /* (__LANGUAGE_C__) || defined(__cplusplus) */
#endif /* _STACK_T */

#if !defined (_XOPEN_SOURCE_EXTENDED) || defined (_OSF_SOURCE)
typedef struct sigcontext mcontext_t;
#else
typedef struct _sigcontext mcontext_t;
#endif

#if !defined (_XOPEN_SOURCE_EXTENDED) || defined (_OSF_SOURCE)
typedef struct ucontext {
#else
typedef struct _ucontext {
#endif
  unsigned long		uc_flags;
#if !defined (_XOPEN_SOURCE_EXTENDED) || defined (_OSF_SOURCE)
  struct ucontext	*uc_link;
#else
  struct _ucontext	*uc_link;
#endif
  sigset_t		uc_sigmask;
  stack_t		uc_stack;
  mcontext_t		uc_mcontext;
  long			uc_filler[5];	/* pad structure to 512 bytes */
} ucontext_t;

#if defined(__cplusplus)
}
#endif
#endif /* _SYS_CONTEXT_T_H */
