/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: param.h,v $
 * Revision 4.3.40.3  2008/10/23  17:27:45  Vikram_Auradkar
 * 	QAR 100586
 * 	Defined UNIX98_LIBC, which reserves a bit in std_unix98. The bit is used to
 * 	switch behavior of some libc routines to comply with standards.
 *
 * Revision 4.3.40.2  2006/01/26  15:24:55  Sriram_Venkataramanan
 * 	Fix for QAR 99131: Standards violation in poll(). Defined
 * 	macros for the bit-fields in the tunable kernel variable
 * 	std_unix98.
 *
 * Revision 4.3.40.1  2005/02/01  16:49:48  Thomas_Blinn
 * 	Fix the PSUSP comment to can NOT be suspended since that
 * 	is what the code actually implements.  Clarify how the
 * 	PCATCH flag really works.
 *
 * Revision 4.3.36.2  2000/09/28  16:40:10  Kevin_Harty
 * 	add _XOPEN_SOURCE ifdef for unix 98 branding
 *
 * Revision 4.3.36.1  2000/08/17  17:15:26  Andrew_Duane
 * 	Remove obsolete SEMMNS
 *
 * Revision 4.3.33.1  2000/03/02  16:23:06  James_Woodward
 * 	added MS_WAKE_HIGHEST flags for wakeup_prim_result().
 *
 * Revision 4.3.28.10  1999/02/24  16:41:51  Brett_Sampson
 * 	sync up with current nightly sources
 * 	[1999/02/23  21:55:21  Brett_Sampson]
 *
 * 	fix problems building amd booting with MACH_ASSERT turned on
 * 	[1999/02/23  19:23:31  Brett_Sampson]
 *
 * Revision 4.3.28.9  1998/12/04  21:04:52  Brian_Haley
 * 	Changed MAXHOSTNAMELEN to 256 (qars 45628, 59570).
 * 	[1998/12/03  20:48:13  Brian_Haley]
 * 
 * Revision 4.3.28.8  1998/11/24  21:44:30  Larry_Scott
 * 	 	** Merge Information **
 * 		** Command used:	bmerge **
 * 		** Ancestor revision:	4.3.28.6 **
 * 		** Merge revision:	4.3.28.7 **
 * 	 	** End **
 * 	merge forward to BL20
 * 	[1998/11/09  19:42:50  Larry_Scott]
 * 
 * 	Move advfs-specific smoothsync-support code into msfs/ms_privates.h.
 * 	[1998/11/09  18:44:36  Larry_Scott]
 * 
 * Revision 4.3.28.7  1998/10/08  19:37:36  James_Woodward
 * 	add mpsleep flag to support local wait channels
 * 	[1998/10/06  13:42:45  James_Woodward]
 * 
 * Revision 4.3.28.6  1997/10/22  13:27:30  Lee_Schermerhorn
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL10:PTCOS_BL11 -visual **
 * 		** Ancestor revision:	4.3.26.3 **
 * 		** Merge revision:	4.3.26.4 **
 * 	 	** End **
 * 	merge of PTmin BL11 changes
 * 	[1997/10/21  22:06:58  Lee_Schermerhorn]
 * 
 * Revision 4.3.26.4  1997/08/28  18:59:37  Janice_Chang
 * 	Add rounddown macro. QAR 52817.
 * 	[1997/08/26  21:02:47  Janice_Chang]
 * 
 * Revision 4.3.28.5  1997/05/28  22:39:29  Larry_Scott
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	4.3.28.3 **
 * 		** Merge revision:	4.3.28.4 **
 * 	 	** End **
 * 	add smoothsync support
 * 	[1997/05/27  15:54:33  Larry_Scott]
 * 
 * Revision 4.3.28.4  1997/05/27  12:49:43  Eric_Werme
 * 	Increase MAXBSIZE from 8192 to 65536 to permit larger UFSes.
 * 	[1997/05/27  12:35:05  Eric_Werme]
 * 
 * Revision 4.3.28.3  1997/04/23  19:08:27  Andrew_Duane
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL3:PTCOS_BL6 -visual **
 * 		** Ancestor revision:	4.3.16.3 **
 * 		** Merge revision:	4.3.26.3 **
 * 	 	** End **
 * 	merge of PTmin BL6 changes
 * 	[1997/04/23  18:41:51  Andrew_Duane]
 * 
 * Revision 4.3.28.2  1997/04/11  22:20:39  Mike_Lempriere
 * 	Upped MAXSYMLINKS (QAR 33344) and per:
 * 	Filesystem Configurable Limits Functional Specification
 * 	http://www.zk3.dec.com/filesystem/unixfs/steel/limits_spec_1.2.html
 * 	[1997/04/05  01:38:01  Mike_Lempriere]
 * 
 * Revision 4.3.26.3  1997/01/24  20:35:22  Janice_Chang
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	4.3.16.3 **
 * 		** Merge revision:	4.3.26.2 **
 * 	 	** End **
 * 	Add NEW_OPEN_MAX_SYSTEM for extended descriptor functionality.
 * 	[1997/01/23  16:36:08  Janice_Chang]
 * 
 * Revision 4.3.26.2  1997/01/24  19:47:13  Janice_Chang
 * 	Remove MAX_VNODES define.
 * 	[1997/01/16  14:08:14  Janice_Chang]
 * 
 * Revision 4.3.16.3  1995/02/13  21:00:04  Thomas_Peterson
 * 	Surrounded #define BSD with #ifndef BSD to avoid warnings
 * 	when this is defined elsewhere (Makefiles).
 * 	[1995/02/06  21:21:31  Thomas_Peterson]
 * 
 * Revision 4.3.16.2  1994/12/16  15:36:53  Ashoke_Rampuria
 * 	Removed MAXALLOCSAVE.
 * 	[1994/12/15  18:44:59  Ashoke_Rampuria]
 * 
 * Revision 4.3.11.10  1994/02/04  07:57:20  Tim_Hoskins
 * 	merge of Sterling BL9 changes
 * 	[1994/02/04  07:18:44  Tim_Hoskins]
 * 
 * Revision 4.3.11.9  1994/01/21  23:36:49  Aju_John
 * 	dynamic vnode alloc-dealloc changes
 * 	[1994/01/21  21:51:42  Aju_John]
 * 
 * Revision 4.3.11.8  1993/12/16  20:59:09  Jeff_Denham
 * 	Sterling BL8 merge.
 * 	[1993/12/16  20:18:45  Jeff_Denham]
 * 
 * Revision 4.3.9.6  1993/12/09  21:04:48  Aju_John
 * 	put () around MAXPATHLEN definition
 * 	[1993/12/09  21:02:11  Aju_John]
 * 
 * Revision 4.3.11.7  1993/11/05  06:29:20  Tim_Hoskins
 * 	merge of Sterling BL7 changes
 * 	[1993/11/05  05:53:40  Tim_Hoskins]
 * 
 * Revision 4.3.9.5  1993/11/02  16:19:19  Aju_John
 * 	changed PATH_MAX to 1023, MAXPATHLEN to PATH_MAX+1
 * 	[1993/11/02  16:11:11  Aju_John]
 * 
 * Revision 4.3.9.4  1993/10/19  18:32:53  Dave_Gerson
 * 	Changed value of MAXINTERP to PATH_MAX + 2 to support
 * 	longer pathnames of shell interpreters in shell scripts.
 * 	[1993/10/18  21:02:27  Dave_Gerson]
 * 
 * Revision 4.3.11.6  1993/10/08  00:32:23  Ernie_Petrides
 * 	merge of Sterling BL6 changes
 * 	[1993/10/08  00:21:29  Ernie_Petrides]
 * 
 * Revision 4.3.11.5  1993/09/23  17:43:13  Aju_John
 * 	adding dynamic file/vnode structures
 * 	[1993/09/23  16:06:11  Aju_John]
 * 
 * Revision 4.3.11.4  1993/08/18  21:30:10  Peter_Schulter
 * 	SVR4 Compatable STREAMS infrastructure premerge
 * 	[1993/08/18  18:21:40  Peter_Schulter]
 * 
 * Revision 4.3.11.3  1993/07/02  17:40:11  James_Woodward
 * 	merge osf1.2 signals
 * 	[1993/07/02  16:54:26  James_Woodward]
 * 
 * 	osf12 merge
 * 	[1993/06/24  13:01:40  James_Woodward]
 * 
 * Revision 4.3.9.3  1993/06/23  20:47:32  Anna_Salzberg
 * 	Support swap devices > 2GB.
 * 	[1993/06/22  18:13:52  Anna_Salzberg]
 * 
 * Revision 4.3.11.2  1993/06/11  17:00:57  Anton_Verhulst
 * 	Add PRIV_USER macro.
 * 	[1993/06/08  19:02:23  Anton_Verhulst]
 * 
 * Revision 4.3.9.2  1993/05/12  19:02:43  Peter_Schulter
 * 	Check in for submit to minor pool
 * 	[1993/05/12  16:14:20  Peter_Schulter]
 * 
 * Revision 4.3.7.2  1993/03/15  14:12:03  Mary_Walker
 * 	moved PIPSIZ to sys/param.h
 * 	[1993/03/15  14:10:48  Mary_Walker]
 * 
 * Revision 4.3.3.5  1992/10/30  18:06:05  Paul_Hansen
 * 	Changed cast of bytes in btodb from unsigned to unsigned long.
 * 	[92/10/30  18:05:08  Paul_Hansen]
 * 
 * Revision 4.3.3.4  92/08/21  16:44:32  Jay_Estabrook
 * 	define NULL as 0L
 * 	[92/08/21  16:43:50  Jay_Estabrook]
 * 
 * Revision 4.3.3.3  92/04/15  14:09:30  Shashi_Mangalat
 * 	Merged in Silver BL6.
 * 	Added support for per-process configurable file descriptor
 * 	  limits through setrlimit syscall.  [Diane_Lebel]
 * 	Merge w/ag.latest. [Stephen_Strange]
 * 	Increased NMOUNTS from 20 to 128 to allow up to 128 ufs mounts.
 * 	  This hard limit should eventually be eliminated by implementing
 * 	  dynamic allocation of the ufs mount table.  [Stephen_Strange]
 * 	[92/04/15  13:19:26  Shashi_Mangalat]
 * 
 * Revision 4.3.3.2  92/01/28  18:40:02  Shashi_Mangalat
 * 	Merged in Silver BL3
 * 	[92/01/28  18:20:23  Shashi_Mangalat]
 * 
 * Revision 4.3.1.2  92/01/24  18:15:29  devbld_gsf
 * 	First AG_BL3 version. Moved from AG baselevel delivery tree.
 * 
 * Revision 4.3  92/01/15  02:11:52  devbld_gsf
 * 	Baselevel alpha_bl002
 * 
 * Revision 4.2.2.2  91/12/07  16:51:50  Jay_Estabrook
 * 	merge ALPHA with SILVER via ODE
 * 	[91/12/07  16:37:23  Jay_Estabrook]
 * 	Merge from ODE/TIN: revision 3.5.9.2
 * 	date: 91/11/14 15:41:53;  author: devrcs;  state: Exp;  lines added/del: 38/4
 * 	sccs rev: 3.6;  orig date: 91/11/04 16:45:52;  orig author: fred
 * 	Fred Canter - config cleanup.
 * 	[91/12/04  11:13:32  William_Burns]
 * 
 * Revision 4.2  91/09/19  22:59:12  devbld
 * 	Adding ODE Headers
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: param.h,v $ $Revision: 4.3.40.3 $ (DEC) $Date: 2008/10/23 17:27:45 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * Copyright (C) 1988,1989 Encore Computer Corporation.  All Rights Reserved
 *
 * Property of Encore Computer Corporation.
 * This software is made available solely pursuant to the terms of
 * a software license agreement which governs its use. Unauthorized
 * duplication, distribution or sale are strictly prohibited.
 *
 */
/*
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 */

/*
 * Modification History
 *
 * 27-Oct-91	Fred Canter
 *		Make all SYSV IPC definitions configurable.
 *
 * 6-June-1991	Brian Stevens
 *		Removed static initialization of MAXUPRC so that its
 *		value can be picked up from the config file.
 */

#ifndef	_SYS_PARAM_H_
#define _SYS_PARAM_H_

#ifndef BSD
#define BSD	198911		/* system version (year & month) */
#endif
#define BSD4_3  1

#ifdef _KERNEL
#include <mach_assert.h>
#endif
#include <sys/types.h>
#include <sys/limits.h>
#include <machine/machparam.h>

/*
 * Machine-independent constants
 */
#define NMOUNT	128		/* number of mountable file systems */
/* NMOUNT must be <= 255 unless c_mdev (cmap.h) is expanded */
#define MSWAPX	NMOUNT		/* pseudo mount table index for swapdev */
/*
 * The default number of per-process file descriptors is configurable.
 * The getdtablesize(2) system call or the sysconf(3) interface should be 
 * used to obtain the current limit.  OPEN_MAX_SOFT is the per-process
 * limit by default.  The system admin can change it via param.c.  A user
 * process can also change its limit with setrlimit(2) but is bounded by 
 * its hard limit (OPEN_MAX_HARD by default).  OPEN_MAX_SYSTEM is the 
 * absolute high water mark that the system admin can configure.  64 is
 * the low water mark.
 *
 * NEW_OPEN_MAX_SYSTEM is the limit of file descriptors available if
 * the utask fd_newmax field is turned on (through setsysinfo()).
 */
#define NEW_OPEN_MAX_SYSTEM 65536
#define OPEN_MAX_SYSTEM 4096
#define OPEN_MAX_HARD   4096
#define OPEN_MAX_SOFT   4096
#define	NOFILE	64		/* max open files per process - OBSOLETE */
#ifndef MIN_FREE_VNODES
#define MIN_FREE_VNODES 150             /* for buffer cache performance */
#endif
#ifndef VNODE_AGE
#define VNODE_AGE 120 /* (sec) ok to dealloc vnodes older than vnode_age*/
#endif

/*
 * The following are bits within the std_unix98 kernel variable (except for
 * STD_UNIX98_ALL). These bits are used to switch between the default behavior
 * and the behavior required by standards test suites (like UNIX98). This is
 * used in those cases where the default behavior does not match the behavior
 * required by the standards test suites.
*/
#define STD_UNIX98_ALL		0x1	/* If std_unix98 is set to 1, then all
					 * the bits in std_unix98 are set to 1.
					 * This allows the user to conveniently 
					 * enable standard compliant behavior of
					 * all the functions represented by the
					 * bits in std_unix98.
					 * Note that STD_UNIX98_ALL does not
					 * represent a bit-field, but a value that
					 * can to be assigned to std_unix98.
					 */
#define UNIX98_POLLWRBAND	0x2	/* Switches poll() to standard */
#define UNIX98_WAITPID		0x4	/* Switches waitpid(2) to standard */
#define UNIX98_LIBC		0x8	/* Makes some libc routines Unix98 compliant */

#define MAXLINK LINK_MAX		/* ??? */
#define	CANBSIZ	MAX_CANON		/* max size of typewriter line */
#define	NCARGS	(ARG_MAX + (2 * PATH_MAX))
				/* # characters in exec arglist */
#define	MAXINTERP	(PATH_MAX + 2)	/* maximum interpreter file name length */
#define NGROUPS	NGROUPS_MAX	/* max number groups */
#define MAXHOSTNAMELEN	256	/* maximum hostname size */

#define NOGROUP	65535		/* marker for empty group set member */

# if !defined (_XOPEN_SOURCE) || (_XOPEN_SOURCE < 500)
#if	(PIPE_BUF * 2) < 4096		/* sys/syslimits.h */
/* If PIPSIZ is set to < 4096 experience shows that many applications
 * deadlock. Note that PIPE_BUF is the write atomicity limit. */
#define	PIPSIZ	4096
#else
#define	PIPSIZ	(PIPE_BUF * 2)
#endif
#endif /* !_XOPEN_SOURCE || _XOPEN_SOURCE<500 */

/*
 * Priorities
 */
#define PSWP	0
#define PINOD	10
#define PRIBIO	20
#define PVFS	22
#define PRIUBA	24
#define PZERO	25
#define PPIPE	26
#define PWAIT	30
#define PLOCK	35
#define PSLEP	40
#define PUSER	50
#define PMASK	0177
#define PRIZERO	0	/* The kernel version of NZERO */
/*
 * Flags for use with sleep_prim() and its friends that call it.
 *
 * PCATCH implies interruptible sleep; the thread may be awakened
 * without the "awaited" event occurring.
 *
 * PSUSP implies the thread can NOT be asynchronously suspended
 * while waiting; also implies PCATCH for interruptible sleep.
 *
 * These two flags are intended primarily for system call code
 * streams; the POSIX standards require that when a user space
 * signal is pending, or certain other conditions apply, that
 * the signal handling should be done immediately, not after a
 * normal return from system call context.  The return values
 * EINTR or ERESTART will only be returned from sleep_prim()
 * and its friends if PCATCH or PSUSP or both are specified.
 *
 * These return values are ONLY indicative of whether a system
 * call code path should be aborted prematurely.   They do not
 * reflect whether a wait_result value of THREAD_INTERRUPTED or
 * THREAD_SHOULD_TERMINATE or THREAD_RESTART has been set.  In
 * some cases, they can be returned without the "sleep" routine
 * ever waiting for the specified event.  The EINTR or ERESTART
 * return values are set when a system call is being cancelled, 
 * or when the thread has been terminated with an AST that implies
 * the thread should halt, a NXM_THREAD_CANCEL, or a pending user
 * space signal (or more than one).
 *
 * Callers of sleep_prim() and friends should check the return
 * value, and if a timeout or interrupt occurs must handle that
 * result correctly.  They must also check the wait_result.  A
 * wait_result other than the normal wakeup THREAD_AWAKENED may
 * or may not be indicative of any problem.  It may be because
 * the process is exiting, for example, or because a timer was
 * set at some earlier point and finally got delivered.  There
 * is no simple way to always do the right thing, and you must
 * be prepared for all the eventualities.  Careful attention to
 * recording correct state information in data structures that
 * are shared between the waiting thread and the thread that is
 * going to wake it upon successful completion is critical.  If
 * you are not in a system call code path or can not safely be
 * interrupted in the middle of what your code is doing, then
 * do NOT use PCATCH or PSUSP.  If you DO run interruptibly, 
 * you MUST look at the return value from the "sleep" routine
 * to see if your operation should be interrupted.  If you get
 * a EINTR or ERESTART return value it means you should return
 * that value to your caller immediately and not attempt to go
 * back into the "sleep" routine to wait for completion of the
 * event.
 */
#define PCATCH	0400
#define PSUSP	01000

/*
 * Signals
 */
#if	!(defined(LOCORE) && defined(ibmrt))
#include <sys/signal.h>
#endif	/* !(defined(LOCORE) && defined(ibmrt)) */

#ifdef	_KERNEL
/*
 * Constants passed to mpsleep, the MP-safe sleep function.
 */
#define MS_LOCK_TYPE		0x00ff		/* mask for lock type field */
#define MS_LOCK_SIMPLE		0x0001		/* simple lock */
#define MS_LOCK_READ		0x0002		/* read lock */
#define MS_LOCK_WRITE		0x0004		/* write lock */
#define MS_LOCK_ON_ERROR	0x0100		/* lock on error return */
#define MS_LOCK_NO_RELOCK	0x0200		/* don't reacquire lock  */
#define MS_WAIT_HASH		0x0400		/* hash event */
#define MS_WAKE_HIGHEST		0x0800		/* wake highest pri threads */

/*
 * Non-assertion macros for sleep and tsleep.  MP-safe versions.
 */
#define sleep(chan, pri) (void) mpsleep(chan, pri, "Zzzzzz", 0, (void *)NULL, 0)
#define tsleep(chan, pri, wmesg, timo) \
	mpsleep(chan, pri, wmesg, timo, (void *) NULL, 0)
#endif	/* _KERNEL */

/*
 * Machine type dependent parameters.
 */

#define NBPW	sizeof(long)	/* sizeof (char *) */

#ifndef NULL
#define	NULL	0L
#endif	/* NULL */
#define CMASK	022		/* default mask for file creation */
#define NODEV	(dev_t)(-1)

/*
 * Clustering of hardware pages on machines with ridiculously small
 * page sizes is done here.  The paging subsystem deals with units of
 * CLSIZE pte's describing NBPG (from machine/machparam.h) pages each.
 *
 * NOTE: SSIZE, SINCR and UPAGES must be multiples of CLSIZE
 */
#define CLBYTES		(CLSIZE*NBPG)
#define CLOFSET		(CLSIZE*NBPG-1)	/* for clusters, like PGOFSET */
#define claligned(x)	((((int)(x))&CLOFSET)==0)
#define CLOFF		CLOFSET
#define CLSHIFT		(PGSHIFT+CLSIZELOG2)

#if	CLSIZE==1
#define clbase(i)	(i)
#define clrnd(i)	(i)
#else
/* give the base virtual address (first of CLSIZE) */
#define clbase(i)	((i) &~ (CLSIZE-1))
/* round a number of clicks up to a whole cluster */
#define clrnd(i)	(((i) + (CLSIZE-1)) &~ (CLSIZE-1))
#endif

/* CBLOCK is the size of a clist block, must be power of 2 */
#define CBLOCK	64
#define CBQSIZE	(CBLOCK/NBBY)	/* quote bytes/cblock - can do better */
#define	CBSIZE	(CBLOCK - sizeof(struct cblock *) - CBQSIZE) /* data chars/clist */
#define CROUND	(CBLOCK - 1)				/* clist rounding */

/* System V IPC definitions */
/* Note: these defaults can be overridden from the kernel config file */

/* messages */
#ifndef MSGMAX
#define MSGMAX   8192
#endif
#ifndef	MSGMNB
#define MSGMNB   16384
#endif
#ifndef	MSGMNI
#define MSGMNI   50
#endif
#ifndef	MSGTQL
#define MSGTQL   40
#endif

/* semaphores */
#ifndef	SEMMNI
#define SEMMNI   10
#endif
#ifndef	SEMMSL
#define SEMMSL   25
#endif
#ifndef	SEMOPM
#define SEMOPM   10
#endif
#ifndef	SEMUME
#define SEMUME   10
#endif
#ifndef	SEMVMX
#define SEMVMX   32767
#endif
#ifndef	SEMAEM
#define SEMAEM   16384
#endif

/* shared memory (defaults increased for ULTRIX/SQL) */
#ifndef	SHMMIN
#define SHMMIN	 1
#endif
#ifndef	SHMMAX
#define SHMMAX	 (4*1024*1024)	/* OSF default is (128*1024) */
#endif
#ifndef	SHMMNI
#define SHMMNI	 100
#endif
#ifndef	SHMSEG
#define SHMSEG	 32		/* OSF default is 6 */
#endif

/*
 * File system parameters and macros.
 *
 * The file system is made out of blocks of at most MAXBSIZE units,
 * with smaller units (fragments) only in the last direct block.
 * MAXBSIZE primarily determines the size of buffers in the buffer
 * pool. It may be made larger without any effect on existing
 * file systems; however making it smaller make make some file
 * systems unmountable.
 *
 * Note that the blocked devices are assumed to have DEV_BSIZE
 * "sectors" and that fragments must be some multiple of this size.
 * Block devices are read in BLKDEV_IOSIZE units. This number must
 * be a power of two and in the range of
 *	DEV_BSIZE <= BLKDEV_IOSIZE <= MAXBSIZE
 * This size has no effect upon the file system, but is usually set
 * to the block size of the root file system, so as to maximize the
 * speed of ``fsck''.
 */
#define MAXBSIZE	65536
#if	defined(exl) || defined(__hp_osf)
#define DEV_BSIZE	1024
#define DEV_BSHIFT	10
#else	/* exl || hp_osf */
#define DEV_BSIZE	512
#define DEV_BSHIFT	9		/* log2(DEV_BSIZE) */
#endif	/* exl || hp_osf */
#define BLKDEV_IOSIZE	2048
#define MAXFRAG 	8

#define btodb(bytes)	 		/* calculates (bytes / DEV_BSIZE) */ \
	((unsigned long)(bytes) >> DEV_BSHIFT)
#define dbtob(db)			/* calculates (db * DEV_BSIZE) */ \
	((unsigned long)(db) << DEV_BSHIFT)

/*******
*
*  UBSIZE is the value that commands and libs will use to present 
*  file/blocks to the user. It is now set to 1k blocksize.
*
*******/

#define UBSIZE	1024
#define UBSHIFT 10	/* LOG2(UBSIZE) */

/*
 * MAXPATHLEN defines the longest permissable path length
 * after expanding symbolic links. It is used to allocate
 * a temporary buffer from the buffer pool in which to do the
 * name expansion, hence should be a power of two, and must
 * be less than or equal to MAXBSIZE.
 * MAXSYMLINKS defines the maximum number of symbolic links
 * that may be expanded in a path name. It should be set high
 * enough to allow all legitimate uses, but halt infinite loops
 * reasonably quickly.
 */
#define	MAXPATHLEN	(PATH_MAX+1)
#define MAXSYMLINKS	64

/*
 * bit map related macros
 */

#define setbit(a,i)	(*(((char *)(a)) + ((i)/NBBY)) |= 1<<((i)%NBBY))
#define clrbit(a,i)	(*(((char *)(a)) + ((i)/NBBY)) &= ~(1<<((i)%NBBY)))
#define isset(a,i)	(*(((char *)(a)) + ((i)/NBBY)) & (1<<((i)%NBBY)))
#define isclr(a,i)      ((*(((char *)(a)) + ((i)/NBBY)) & (1<<((i)%NBBY))) == 0)

#if	!defined(vax) && !defined(i386)
#define _bit_set(i,a)   setbit(a,i)
#define _bit_clear(i,a)	clrbit(a,i)
#define _bit_tst(i,a)	isset(a,i)
#endif	/* !defined(vax) && !defined(i386) */


/*
 * Macros for fast min/max.
 */
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

/*
 * Macros for counting and rounding.
 */
#ifndef	howmany
#define howmany(x, y)	(((x)+((y)-1))/(y))
#endif
#define roundup(x, y)	((((x)+((y)-1))/(y))*(y))
#define rounddown(x,y)  (((x)/(y))*(y))
#define powerof2(x)	((((x)-1)&(x))==0)

#ifdef  _KERNEL
/*
 * Macro to replace redundant SEC_BASE code.
 */
#if	SEC_BASE
#define PRIV_SUSER(cr,acflag,priv,code,retcode,error)   \
	((error) = !privileged((priv),(code)) ? (retcode) : 0)
#else
#define PRIV_SUSER(cr,acflag,priv,code,retcode,error)   \
	((error) = suser((cr),(acflag)))
#endif
#endif

/*
 * Scale factor for scaled integers used to count %cpu time and load avgs.
 *
 * The number of CPU `tick's that map to a unique `%age' can be expressed
 * by the formula (1 / (2 ^ (FSHIFT - 11))).  The maximum load average that
 * can be calculated (assuming 32 bits) can be closely approximated using
 * the formula (2 ^ (2 * (16 - FSHIFT))) for (FSHIFT < 15).
 *
 * For the scheduler to maintain a 1:1 mapping of CPU `tick' to `%age',
 * FSHIFT must be at least 11; this gives us a maximum load avg of ~1024.
 */
#define	FSHIFT	11		/* bits to right of fixed binary point */
#define FSCALE	(1<<FSHIFT)

#define MAXDOMNAMELEN	256		/* maximum domain name length */

#endif	/* _SYS_PARAM_H_ */
