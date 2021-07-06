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
 * @(#)$RCSfile: types.h,v $ $Revision: 4.3.74.1 $ (DEC) $Date: 2002/01/29 21:19:58 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.2
 */
/*
 * COMPONENT_NAME: type declaration header file
 *
 * ORIGIN: IBM, ATT, BSD
 *
 * Copyright International Business Machines Corp. 1985, 1988
 * All Rights Reserved
 * Licensed Material - Property of IBM
 *
 * RESTRICTED RIGHTS LEGEND
 * Use, Duplication or Disclosure by the Government is subject to
 * restrictions as set forth in paragraph (b)(3)(B) of the Rights in
 * Technical Data and Computer Software clause in DAR 7-104.9(a).
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *      (#)types.h     7.1 (Berkeley) 6/4/86
 */

#ifndef _SYS_TYPES_H_
#define _SYS_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>

#if !defined(__LANGUAGE_ASSEMBLY__) && !defined(LOCORE)

#ifdef   _ANSI_C_SOURCE
/*
 * ANSI C required typedefs
 */

#ifndef _PTRDIFF_T
#define _PTRDIFF_T
typedef signed long     ptrdiff_t;
#endif

#ifndef _WCHAR_T
#define _WCHAR_T

#ifndef __WCHAR_T_LEN
#    define __WCHAR_T_LEN 4
#endif

#if __WCHAR_T_LEN == 1
    typedef unsigned char wchar_t;
#elif __WCHAR_T_LEN == 2
    typedef unsigned short wchar_t;
#else
    typedef unsigned int  wchar_t;
#endif /* __WCHAR_T_LEN == ?? */

#endif /* _WCHAR_T */

#ifndef _WCTYPE_T
#define _WCTYPE_T
typedef unsigned int wctype_t;
#endif

#ifndef _FPOS_T
#define _FPOS_T
typedef long            fpos_t;
#endif

/* time_t declaration moved to <time_t.h> */
#include <time_t.h>

#ifndef _CLOCK_T
#define _CLOCK_T
typedef int             clock_t;
#endif

#ifndef _SIZE_T
#define _SIZE_T
# ifndef __VMS
typedef unsigned long   size_t;
# else	/* __VMS */
# define __SIZE_T 1
typedef unsigned int   size_t;
# endif /* __VMS */
#endif /* _SIZE_T */

#endif   /* _ANSI_C_SOURCE */

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 1) 

#ifndef _SSIZE_T
#define _SSIZE_T
typedef long                    ssize_t; /* Required for ISO/IEC 9945-1:1990 */
#endif

/*
 * shorthand type definitions for unsigned storage classes
 */
typedef	unsigned char	uchar_t;
typedef	unsigned short	ushort_t;
typedef	unsigned int	uint_t;
typedef unsigned long	ulong_t;
typedef	volatile unsigned char	vuchar_t;
typedef	volatile unsigned short	vushort_t;
typedef	volatile unsigned int	vuint_t;
typedef volatile unsigned long	vulong_t;

#ifdef _OSF_SOURCE

#ifdef	__alpha
typedef	struct	{ long r[1]; } *physadr_t;
/*
 * WARNING:
 * this must match the definition of kernel jmpbuf's in machine/reg.h
 */
typedef	struct	label_t	{
	long	val[10];
} label_t;
#endif	/* __alpha */

#ifdef	__ia64__
typedef	struct	{ long r[1]; } *physadr_t;
/*
 * WARNING:
 * this must match the definition of kernel jmpbuf's in machine/reg.h
 * this is an initial cut, meant to enable building of user space
 * commands.  it needs to be examined during the actual port.
 */
typedef	struct	label_t	{
	long	val[61];
} label_t;
#endif	/* __ia64__ */

#ifdef __intel__
/*
 * WARNING:
 * this must match the definition of kernel jmpbuf's in machine/reg.h
 */
typedef	struct	{ long r[1]; } *physadr_t;
typedef	struct	label_t	{
	int	val[14];
} label_t;
#endif	/* __intel__ */


#ifdef	__mips__
typedef	struct	{ int r[1]; } *physadr_t;
/*
 * WARNING:
 * this must match the definition of kernel jmpbuf's in machine/pcb.h
 */
typedef	struct	label_t	{
	long	val[12];
} label_t;
#endif	/* __mips__ */

#if	defined(__vax__) || defined(__ns32000__) || defined(__i386__)
typedef	struct	{ int r[1]; } *physadr_t;
typedef	struct	label_t	{
	int	val[14];
} label_t;
#endif	/* defined(__vax__) || defined(__ns32000__) || defined(__i386__) */

#ifdef	__ibmrt__
typedef	struct	{ int r[1]; } *physadr_t;
typedef	struct	label_t	{
	int	val[16];
} label_t;
#endif	/* __ibmrt__ */

#if	defined(__mc68000__) || defined(__mc68000)
typedef struct  { short r[1]; } *physadr_t;
typedef struct  label_t {
        int     val[13];
} label_t;
#endif	/* __mc68000__ */

#ifdef __sparc__
typedef struct  { int r[1]; } *physadr_t;
typedef struct label_t {
        int     val[2];
} label_t;
#endif	/* __sparc__ */

#endif /* _OSF_SOURCE */

typedef int		level_t;
typedef	int		daddr_t;	/* disk address */
typedef long		daddr64_t;	/* 64 bit disk address */
typedef	char *		caddr_t;	/* "core" (i.e. memory) address */
typedef long *		qaddr_t;        /* should be typedef quad * qaddr_t; */
typedef char *          addr_t;
typedef	uint_t		ino_t;		/* inode number (filesystem) */
typedef short		cnt_t;
typedef int		dev_t;		/* device number (major+minor) */
typedef	int		chan_t;		/* channel number (minor's minor) */


#ifdef  _KERNEL
typedef ulong_t  off_t;			/* unsigned long file offset */
typedef long	loff_t;			/* signed long file offset */
#else   /* _KERNEL */
typedef long    off_t;			/* file offset */
#endif  /* _KERNEL */

typedef long t_scalar_t;
typedef unsigned long t_uscalar_t;

#if _XOPEN_SOURCE>=500
typedef long blksize_t;
typedef long blkcnt_t;
#ifndef	_CLOCKID_T
#define	_CLOCKID_T
typedef int clockid_t;
#endif	/* _CLOCKID_T */
typedef unsigned long fsblkcnt_t;
typedef unsigned long fsfilcnt_t;
typedef int suseconds_t;
#endif	/* XSH5 */

typedef unsigned long	rlim_t;		/* resource limit */
typedef	int		paddr_t;
typedef	ushort_t	nlink_t;

#ifndef _KEY_T
#define _KEY_T
typedef int    		key_t;		/* ipc key type */
#endif

#ifndef _MODE_T
#define _MODE_T
typedef	uint_t		mode_t;		/* file mode */
#endif

#ifndef _UID_T
#define _UID_T
#ifdef _XOPEN_SOURCE_EXTENDED
typedef int             uid_t;          /* user ID */
#else
typedef uint_t		uid_t;		/* user ID */
#endif
#endif

#ifndef _GID_T
#define _GID_T
typedef uint_t		gid_t;		/* group ID */
#endif

#ifndef _MID_T
#define _MID_T
typedef	void *		mid_t;		/* module ID	*/
#endif

#ifndef _PID_T
#define _PID_T
typedef	int		pid_t;		/* process ID */
#ifdef _OSF_SOURCE
typedef union cpid {			/* cluster process ID */
	struct {
		unsigned int pid:19;	/* actual pid (ref: PID_MAX) */
		unsigned int nodeid:8;	/* cluster node # */
		unsigned int seqnum:4;	/* cluster node sequence # */
		unsigned int signbit:1;	/* sign bit; unused */
	} cluster_fields;
	pid_t ipid;			/* complete 31-bit value */
} cpid_t;
#define tcr_pid cluster_fields.pid
#define tcr_node cluster_fields.nodeid
#define tcr_seq cluster_fields.seqnum
#endif	/* _OSF_SOURCE */
#endif

typedef char		slab_t[12];	/* security label */

typedef ulong_t		shmatt_t;	/* for shmid_ds.shm_nattach */
typedef ulong_t		msgqnum_t;	/* for msqid_ds.msg_qnum */
typedef ulong_t		msglen_t;	/* for msqid_ds.msg_qbytes */

#ifndef _WINT_T
#define _WINT_T
        typedef unsigned int wint_t;         /* Wide character */
#endif

/* typedef for signal mask */
#ifndef _SIGSET_T
#define _SIGSET_T
#ifndef __VMS
#ifdef __arch32__
typedef quad sigset_t;
#else /* __arch32__ */
typedef unsigned long 	sigset_t;
#endif /* __arch32__ */
#else /* __VMS */
#if __VMS_VER >= 70000000
#ifndef ____SIGSET_T
#define ____SIGSET_T 1
typedef struct {unsigned int _set[2];} __sigset_t;
typedef __sigset_t sigset_t;
#endif /* ____SIGSET_T*/
#endif /*  __VMS_VER >= 70000000 */
#endif /* __VMS */
#endif /* _SIGSET_T */

/* typedefs for POSIX 1003.1c */
#if _POSIX_C_SOURCE >= 199506L

#ifndef __VMS
/* For VMS, ignore these pthread definitions and use the ones in pthread.h */
# if defined (_PTHREAD_CORE_BUILD_) || defined (_CMA_CORE_BUILD_) || defined(_TIS_CORE_BUILD_)
#  define _Pfield(_arg_)	_arg_
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   define _Pfield(_arg_)	__##_arg_
#  else
#   define _Pfield(_arg_)	__/**/_arg_
#  endif
# endif

typedef struct __pthread_attr_t {
    long		_Pfield(valid);
    char*		_Pfield(name);
    unsigned long	_Pfield(arg);
    unsigned long	_Pfield(reserved)[19];
} pthread_attr_t;

typedef struct __pthread_mutexattr_t {
    long		_Pfield(valid);
    unsigned long	_Pfield(reserved)[15];
} pthread_mutexattr_t;

typedef struct __pthread_condattr_t {
    long		_Pfield(valid);
    unsigned long	_Pfield(reserved)[13];
} pthread_condattr_t;

typedef struct __pthread_rwlockattr_t {
    long		_Pfield(valid);
    unsigned long	_Pfield(reserved)[15];
} pthread_rwlockattr_t;

# ifdef _OSF_SOURCE	/* These symbols aren't portable */
#  define PTHREAD_TEB_VERSION 2			/* Current version */
#  define PTHREAD_TEB_SIZE \
     ((size_t)((char *)&((__pthreadTeb_p)0L)->_Pfield(home_rad) \
     - (char *)0L)) + sizeof (void *)
#  define PTHREAD_TEB_EFLG_USER		0x01	/* User thread */
#  define PTHREAD_TEB_EFLG_INITIAL	0x02	/* Process initial thread */

#  define PTHREAD_TEB_CREATOR_PTHREAD	1	/* Created by 1003.1c API */
#  define PTHREAD_TEB_CREATOR_CMA	2	/* Created by CMA API */
#  define PTHREAD_TEB_CREATOR_D4	3	/* Created by Draft 4 API */
#  define PTHREAD_TEB_CREATOR_D4EXC	4	/* Created by D4-Exception API */
# endif

/*
 * Thread Environment Block (TEB).
 *
 * NOTE: Modification of any field in a thread's TEB structure will result in
 * undefined behavior. Fields that are commented as "RESERVED" are
 * undocumented and unsupported, and the contents or meaning may change at any
 * time. The "per_kt_area" field is reserved entirely for use by DECthreads
 * and the operating system kernel: it contains undefined, undocumented,
 * unsupported, and volatile data of unspecified type.
 *
 * Each public field is documented with a comment that begins with the TEB
 * version in which the field was created or documented. If the TEB "version"
 * has a value lower than version in which the field became accessible, do not
 * depend upon the value of that field.
 */

typedef struct __pthreadTeb_tag {
    void*		_Pfield(reserved1);	/* RESERVED */
    void*		_Pfield(reserved2);	/* RESERVED */
    unsigned short	_Pfield(size);	  	/* V1: size of TEB */
    unsigned char	_Pfield(version);	/* TEB Version (see above) */
    unsigned char	_Pfield(reserved3);	/* RESERVED */
    unsigned char	_Pfield(external);	/* V1: PTHREAD_TEB_EFLG_ flgs */
    unsigned char	_Pfield(reserved4)[2];	/* RESERVED */
    unsigned char	_Pfield(creator);	/* V1: PTHREAD_TEB_CREATOR_* */
    unsigned long	_Pfield(sequence);	/* V0: thread sequence # */
    unsigned long	_Pfield(reserved5)[2];	/* RESERVED */
    void*		_Pfield(per_kt_area);	/* RESERVED */
    void*		_Pfield(stack_base);	/* V0: initial SP */
    void*		_Pfield(stack_reserve);	/* V0: reserved stack */
    void*		_Pfield(stack_yellow);	/* V0: stack yellow zone */
    void*		_Pfield(stack_guard);	/* V0: stack guard zone */
    unsigned long	_Pfield(stack_size);	/* V0: usable stack size */
    void**		_Pfield(tsd_values);	/* V0: TSD array (void *) */
    unsigned long	_Pfield(tsd_count);	/* V0: TSD array size */
    unsigned int	_Pfield(reserved6);	/* RESERVED */
    unsigned int	_Pfield(reserved7);	/* RESERVED */
    unsigned int	_Pfield(thread_flags);	/* RESERVED */
    int			_Pfield(thd_errno);	/* V1: thread's errno */
    void*		_Pfield(stack_hiwater); /* V1: lowest known SP */
    unsigned long	_Pfield(home_rad);	/* V2: thread's home RAD */
} __pthreadTeb_t, *__pthreadTeb_p;

#define _PTHREAD_NEW_TEB			/* Namespace-clean TEB types */

/*
 * The only official or supported mechanism to find the TEB of a thread is for
 * code within that thread to execute the "rduniq" call_pal instruction. The
 * following typedef of pthread_t, as a pointer to a TEB, is an unsupported
 * artifact of the current implementation, and will be changed in the future.
 * No correct code may reference a TEB through a pthread_t value.
 */
typedef __pthreadTeb_p pthread_t;

#ifdef _OSF_SOURCE
typedef __pthreadTeb_t pthreadTeb_t;
typedef __pthreadTeb_p pthreadTeb_p;
#endif

typedef struct __pthread_mutex_t {
    unsigned int	_Pfield(lock);
    unsigned int	_Pfield(valid);
    char*		_Pfield(name);
    unsigned int	_Pfield(arg);
    unsigned int	_Pfield(depth);
    unsigned long	_Pfield(sequence);
    unsigned long	_Pfield(owner);
    void*		_Pfield(block);
} pthread_mutex_t;

typedef struct __pthread_cond_t {
    unsigned int	_Pfield(state);
    unsigned int	_Pfield(valid);
    char*		_Pfield(name);
    unsigned int	_Pfield(arg);
    unsigned int	_Pfield(reserved1);
    unsigned long	_Pfield(sequence);
    void*		_Pfield(block);
} pthread_cond_t;

typedef struct __pthread_rwlock_t {
    unsigned int	_Pfield(valid);
    unsigned int	_Pfield(flags);
    char*		_Pfield(name);
    unsigned int	_Pfield(arg);
    unsigned int	_Pfield(readers);
    unsigned int	_Pfield(rwaits);
    unsigned int	_Pfield(wwaits);
    unsigned long	_Pfield(sequence);
    unsigned long	_Pfield(wrid);
    void*		_Pfield(block);
    unsigned long	_Pfield(reserved1);
} pthread_rwlock_t;

typedef unsigned int	pthread_key_t;

typedef struct __pthread_once_t {
    long	_Pfield(state);
    long	_Pfield(reserved)[10];
} pthread_once_t;

#endif /* __VMS */
#endif /* _POSIX_C_SOURCE >= 199506L */

#ifndef _KERNEL
/*
 * name conflict.
 *              /kernel/kern typedefs timer_t to something else.
 *              The file isn't exported.
 */
typedef long            timer_t;        /* timer id for _POSIX_C_SOURCE */
#endif /* !defined(_KERNEL) */

#else /* _POSIX_C_SOURCE && _POSIX_C_SOURCE >= 1 */
#ifndef __LANGUAGE_PASCAL__
typedef char *  __caddr_t;
#endif /* __LANGUAGE_PASCAL__ */

#endif /* _POSIX_C_SOURCE && _POSIX_C_SOURCE >= 1 */

#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)
#ifdef _OSF_SOURCE

#ifndef NULL
#define	NULL	0L
#endif

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

#ifndef _KERNEL
typedef void (*sig_t) __((int,void (*)(int)));
#else
typedef void (*sig_t) __((int));
#endif

#ifndef	_CPUID_T
#define _CPUID_T
typedef	unsigned int cpuid_t;
#define CPU_NONE	(-1)	/* no such cpu exists or none specified */
#endif  /* _CPUID_T */

#endif /* _OSF_SOURCE */

/*
 * The following type is for various kinds of identifiers.  The
 * actual type must be the same for all since some system calls
 * (such as sigsend) take arguments that may be any of these
 * types.  The enumeration type idtype_t defined in sys/procset.h
 * is used to indicate what type of id is being specified.
 */
typedef pid_t		id_t;		/* A process id,	*/
					/* process group id,	*/
					/* session id, 		*/
					/* scheduling class id,	*/
					/* user id, or group id.*/
typedef unsigned int	useconds_t;	/* time in microseconds */

#ifdef _OSF_SOURCE
#define	P_MYID	(-1)	/* a usually illegal value for IDs, but specifying
			   whatever the value is for my process */

/*
 * Types used by dev_t annotation macros (see below)
 */
typedef uint_t	major_t;      /* major device number   */
typedef uint_t	minor_t;      /* minor device number   */
typedef uint_t	devs_t;       /* device-specific info  */
typedef uint_t	unit_t;       /* unit number of device */

/*
 * Basic system types and major/minor device constructing/busting macros.
 */
#define major(x)	((major_t)  (((dev_t)(x)>>20)&07777))
#define minor(x)	((minor_t)  ((dev_t)(x)&03777777))
#define makedev(x,y)	((dev_t)    (((major_t)(x)<<20) | (minor_t)(y)))

/*
 * Disk/Tape (SCSI/CAM - DSA) specific dev_t annotations macros.
 */
#define MAKEMINOR(u,d)  ((minor_t)  (((unit_t)(u)<<6) |(devs_t)(d)))
#define GETUNIT(dev)	((unit_t)   (minor(dev)>>6)&037777)
#define GETDEVS(dev)	((devs_t)   (minor(dev))&077)
#define MAKECAMMINOR(u,d) ((minor_t) MAKEMINOR((((u&0770)<<5)|((u&07)<<4)),d))
#define GETCAMUNIT(x)   ((unit_t) (((GETUNIT(x))>>5)&0770)|((GETUNIT(x)>>4)&07))
#define GETCAMTARG(x)   ((unit_t) ((x >> 3)&07))
#define GETREUNIT(x)	((unit_t) ((x)&07))

#include <mach/machine/vm_types.h>

/*
 * shorthand type definitions for unsigned storage classes
 */
typedef	uchar_t		uchar;
typedef	ushort_t	ushort;
typedef	uint_t		uint;
typedef ulong_t		ulong;

typedef	physadr_t	physadr;

/* typedefs for BSD unsigned things */
typedef	uchar_t		u_char;
typedef	ushort_t 	u_short;
typedef	uint_t		u_int;
typedef	ulong_t		u_long;
typedef	vuchar_t	vu_char;
typedef	vushort_t 	vu_short;
typedef	vuint_t		vu_int;
typedef	vulong_t	vu_long;

#ifdef  _KERNEL
typedef struct  _quad { u_int val[2]; } quad;
#else   /* _KERNEL */
typedef struct  _quad { int val[2]; } quad;
#endif  /* _KERNEL */

typedef	long	swblk_t;
typedef u_long	fixpt_t;

#include <sys/select.h>

#endif   /* _OSF_SOURCE */

/* required for Spec1170 compliance */

typedef unsigned char sa_family_t;

/* Spec 1170 says in_addr_t is unsigned integral of exactly 32 bits */
typedef	unsigned int	in_addr_t;
/* Spec 1170 says in_port_t is unsigned integral of exactly 16 bits */
typedef	unsigned short	in_port_t;

#endif   /* _OSF_SOURCE || _XOPEN_SOURCE_EXTENDED */

#ifdef _KERNEL
#include <sys/systm.h> /* pragmatic approach to global kernel visibility */
#endif /* _KERNEL */

#endif /* !__LANGUAGE_ASSEMBLY__ && !LOCORE */

#ifdef __cplusplus
}
#endif

#endif /* _SYS_TYPES_H_ */
