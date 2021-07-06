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
/* @(#)$RCSfile: utmp.h,v $ $Revision: 4.2.11.7 $ (OSF) $Date: 1998/12/03 22:27:43 $ */
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	utmp.h	5.1 (Berkeley) 5/30/85
 */
#ifndef _UTMP_H_
#define _UTMP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>

#define UTMP_FILE       "/var/adm/utmp"
#define WTMP_FILE       "/var/adm/wtmp"

#include <sys/types.h>	/* for pid_t, time_t */
#include <sys/time.h>
#include <utmp_common.h>    /* for common definitions */

/*
 * Structure of utmp and wtmp files.
 *
 * Assuming these numbers is unwise.
 */

#define ut_name ut_user 		/* compatability */

#if defined (__V40_OBJ_COMPAT)
#define __UT_TMP_NAMESIZE     32
#define __UT_TMP_HOSTSIZE     64
#else
#define __UT_TMP_NAMESIZE     __UT_NAMESIZE
#define __UT_TMP_HOSTSIZE     __UT_HOSTSIZE
#define ut_time               ut_tv.tv_sec    /* backwards compatibility */
#endif


struct utmp {
	char	ut_user[__UT_TMP_NAMESIZE];	/* User login name */
	char	ut_id[14];		        /* /etc/inittab id- IDENT_LEN in init */
	char	ut_line[__UT_LINESIZE];	/* device name (console, lnxx) */
	short	ut_type; 		        /* type of entry */
	pid_t	ut_pid;			        /* process id */
	struct exit_status {
	    short	e_termination;	/* Process termination status */
	    short	e_exit;		/* Process exit status */
	} ut_exit;			/* The exit status of a process
					 * marked as DEAD_PROCESS.
					 */
#if defined (__V40_OBJ_COMPAT)
	time_t	ut_time;		/* 32 bit time entry was made Prior to V5.0*/
#else
	struct	__ut_timeval ut_tv;	/* time entry was made Unix95 V5.0 forward */
#endif
	char	ut_host[__UT_TMP_HOSTSIZE];	/*host name same as MAXHOSTNAMELEN */
};


/* Definitions for ut_type are included in utmp_common.h	*/

/*	Special strings or formats used in the "ut_line" field when	*/
/*	accounting for something other than a process.			*/
/*	No string for the ut_line field can be more than 11 chars +	*/
/*	a NULL in length.						*/

#define RUNLVL_MSG      "run-level %c"
#define	BOOT_MSG	"system boot"
#define	OTIME_MSG	"old time"
#define	NTIME_MSG	"new time"

/*
 * Return codes for wtmp_search() in libpset.
 */
#define	WTMP_FILE_OPEN_FAILED		-1
#define	WTMP_PSR_TIME_RETURNED		1
#define	WTMP_BOOT_TIME_RETURNED		2
#define	WTMP_FILE_CORRUPT		3


#define __UTR(__dname__) __dname__
#ifndef _LIBC_POLLUTION_H_
#if !defined(__V40_OBJ_COMPAT)
#   if defined(__DECC)
#     pragma extern_prefix "_E"
#   else  /* ! __DECC */
#     define getutent()     _Egetutent()     
#     define getutid(__u)   _Egetutid(__u)     
#     define getutline(__u) _Egetutline(__u)     
#     define pututline(__u) _Epututline(__u)     
#     undef  __UTR
#     define __UTR(__dname__) _E##__dname__
#   endif /* __DECC */
#endif /* __V40_OBJ_COMPAT_ */
#endif /* ! _LIBC_POLLUTION_H */

extern struct utmp	*__UTR(getutent)  __((void));
extern struct utmp	*__UTR(getutid)   __((const struct utmp *));
extern struct utmp	*__UTR(getutline) __((const struct utmp *));
extern struct utmp	*__UTR(pututline) __((const struct utmp *));

#if defined(__DECC)
#  pragma extern_prefix ""
#endif /* __DECC */

extern void		setutent __((void));
extern void		endutent __((void));
extern void		utmpname __((char *));

#if defined(_REENTRANT) || defined(_THREAD_SAFE)

struct utmp_data {
	int		ut_fd;
	long		loc_utmp;
	struct utmp	ubuf;
};

#ifndef _LIBC_POLLUTION_H_
#if !defined(__V40_OBJ_COMPAT)
#   if defined(__DECC)
#     pragma extern_prefix "_E"
#   else  /* ! __DECC */
#     define getutent_r(__p, __d)       _Egetutent_r(__p, __d)     
#     define getutid_r(__u,__p, __d)    _Egetutid_r(__u, __p, __d)     
#     define getutline_r(__u,__p, __d)  _Egetutline_r(__u, __p, __d)     
#     define pututline_r(__u,__d)       _Epututline_r(__u, __d)     
#     define setutent_r(__d)            _Esetutent_r(__d)
#     define endutent_r(__d)            _Eendutent_r(__d)
#   endif   /* __DECC */
#endif      /* __V40_OBJ_COMPAT_ */
#endif /* ! _LIBC_POLLUTION_H */

extern int  __UTR(getutent_r)   __((struct utmp **, struct utmp_data *));
extern int  __UTR(getutid_r)    __((struct utmp *, struct utmp **, struct utmp_data *));
extern int  __UTR(getutline_r)  __((struct utmp *, struct utmp **, struct utmp_data *));
extern int  __UTR(pututline_r)  __((struct utmp *, struct utmp_data *));
extern void __UTR(setutent_r)   __((struct utmp_data *));
extern void __UTR(endutent_r)   __((struct utmp_data *));

#if defined(__DECC)
#  pragma extern_prefix ""
#endif /* __DECC */

#endif	/* _REENTRANT || _THREAD_SAFE */
#undef __UTR

#ifdef __cplusplus
}
#endif

#endif  /* _UTMP_H_ */
