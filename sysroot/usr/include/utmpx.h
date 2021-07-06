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
 * @(#)$RCSfile: utmpx.h,v $ $Revision: 1.1.6.5 $ (DEC) $Date: 1999/02/05 17:54:52 $
 */
#ifndef _UTMPX_H_
#define _UTMPX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>

#include <sys/types.h>  /* for pid_t, time_t */
#include <sys/time.h>
#include <utmp_common.h>    /* for common definitions */

#if defined (__V40_OBJ_COMPAT)
#define __UT_TMP_NAMESIZE     32
#define __UT_TMP_HOSTSIZE     64
#else
#define __UT_TMP_NAMESIZE     __UT_NAMESIZE
#define __UT_TMP_HOSTSIZE     __UT_HOSTSIZE
#endif

/*
 * Structure of utmpx.
 */
struct utmpx {
        char    ut_user[__UT_TMP_NAMESIZE]; /* User login name */
        char    ut_id[14];              /* /etc/inittab id- IDENT_LEN in init */
        char    ut_line[__UT_LINESIZE]; /* device name (console, lnxx) */
        short   ut_type;                /* type of entry */
        pid_t   ut_pid;                 /* process id */
        struct  {
            short	ut_termination;	/* Process termination status */
            short	ut_exit;	/* Process exit status */
        } ut_exit;			/* The exit status of a process
					 * marked as DEAD_PROCESS.
					 */
        struct 	timeval ut_tv;		/* Time entry was made */
        char	ut_host[__UT_TMP_HOSTSIZE];	/* host name same as MAXHOSTNAMELEN */
};

/* 
 * The following gives compatibility to code that was built/linked against
 * a V4.0* system. Since then, the size of the username and the host name
 * have changed to larger values.
 */
#define __UTR(__dname__) __dname__
#ifndef _LIBC_POLLUTION_H_
#if !defined(__V40_OBJ_COMPAT)
#ifdef __DECC
#pragma extern_prefix "_E"
#else
#define getutxent()         _Egetutxent()
#define getutxid(__a)       _Egetutxid(__a)
#define getutxline(__a)     _Egetutxline(__a)
#define pututxline(__a)     _Epututxline(__a)
#undef  __UTR
#define __UTR(__dname__) _E##__dname__
#endif /* __DECC */
#endif /* __V40_OBJ_COMPAT */
#endif /* ! _LIBC_POLLUTION_H */

extern struct utmpx     *__UTR(getutxent)	__((void));
extern struct utmpx     *__UTR(getutxid)	__((const struct utmpx *));
extern struct utmpx     *__UTR(getutxline) 	__((const struct utmpx *));
extern struct utmpx     *__UTR(pututxline)	__((const struct utmpx *));

#if !defined(_LIBC_POLLUTION_H_) && !defined(__V40_OBJ_COMPAT) && defined(__DECC)
#pragma extern_prefix ""
#endif
#undef __UTR

extern void             setutxent __((void));
extern void             endutxent __((void));

#ifdef __cplusplus
}
#endif

#endif  /* _UTMPX_H_ */


