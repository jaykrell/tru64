/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: systm.h,v $
 * Revision 4.3.48.2  2003/12/09  20:23:35  Jason_Hennessey
 * 	Add prototype for new routine uprintf_safe(). Case BCSMP01GD
 * 	[2003/12/08  20:19:25  Jason_Hennessey]
 *
 * Revision 4.3.48.1  2002/10/02  20:20:12  Bjorn_Engberg
 * Merge Information:  Visual Merge: User specified tree v51asupportos.nightly
 *     User Revision:  v51bsupportos_nightly:4.3.38.4 Local Ancestor: n/a
 *    Merge Revision:  v51asupportos_nightly:4.3.43.2
 *   Common Ancestor:  4.3.43.1
 * 	Merged with v51asupportos-773-bjorn (Rev. 4.3.43.2).
 *
 * Revision 4.3.43.2  2002/09/23  15:39:09  Bjorn_Engberg
 * 	Added atomic_excl() and atomic_excq() macros, they are
 * 	needed to fix problem with NUMA Disk Statistics,
 * 	QARs 85057 and 93713.
 * 
 * Revision 4.3.38.4  2002/02/18  20:50:05  Rajesh_R
 * 	Marvel cleanup.
 * 
 * Revision 4.3.38.3  2002/01/29  21:19:56  Geraldine_Harter
 * 	Add VMS code changes needed to facilitate porting TCP/IP to VMS.
 * 
 * Revision 4.3.38.2  2001/10/24  22:19:42  Rajesh_R
 * 	Change first argument of intrsetvec() from u_short to
 * 	u_int (Marvel needs larger SCB vector space).
 * 	Add PRE_PANICPRINT flag for Marvel.
 * 
 * Revision 4.3.38.1  2001/09/21  13:16:43  James_Woodward
 * 	Add function prototypes for hzto() and hzto_long().
 * 
 * Revision 4.3.34.2  2000/10/25  21:59:30  Ernie_Petrides
 * 	Fix "cm_syscall" function pointer declaration and remove cm_xxx()
 * 	function declarations that are duplicates from <sys/kern_compat.h>.
 * 
 * Revision 4.3.34.1  2000/09/06  19:36:26  David_Gagne
 * 	Add CPU hot swap support:
 * 	[2000/08/30  18:20:44  Anton_Verhulst]
 * 	Add prototype for write_const_data_nosynch().
 * 
 * Revision 4.3.26.10  2000/05/15  13:46:34  Pam_Gaudette
 * 	Added definitions for hostname reader/writer spin
 * 	locks and replicated hostname data.
 * 
 * Revision 4.3.26.9  2000/03/25  00:47:36  Ernie_Petrides
 * 	Compress sysent structure to 16 bytes.
 * 
 * Revision 4.3.26.8  2000/01/27  20:27:17  Ernie_Petrides
 * 	Allow for replication of read-mostly global variables and
 * 	move function prototypes here from sys/common_protos.h.
 * 
 * Revision 4.3.26.7  1999/11/30  12:55:09  James_Woodward
 * 	Make nsysent const.
 * 
 * Revision 4.3.26.6  1999/11/16  20:21:43  Ernie_Petrides
 * 	Rename header file containing _BASE_KERNEL_PRIVATE definition.
 * 
 * Revision 4.3.26.5  1999/11/04  22:12:25  Ernie_Petrides
 * 	Put include of boolean.h back under _KERNEL ifdef.
 * 
 * Revision 4.3.26.4  1999/11/03  22:44:09  Ernie_Petrides
 * 	Move includes of common_protos.h, usercopy.h, spl.h, builtins.h,
 * 	and kintrinsics.h to this file and implement mechanism for defining
 * 	_BASE_KERNEL_PRIVATE during the compilation of kernel objects in
 * 	the BINARY directory.
 * 
 * Revision 4.3.26.3  1999/05/06  19:11:12  James_Woodward
 * 	steel bl23 pass 3 merge
 * 	[1999/05/06  18:32:40  James_Woodward]
 * 
 * Revision 4.3.28.2  1999/01/28  17:06:41  Anton_Verhulst
 * 	Add stutting_down.
 * 	[1999/01/28  16:44:04  Anton_Verhulst]
 * 
 * Revision 4.3.26.2  1998/08/26  12:41:38  James_Woodward
 * 	Merge of numaproj and zulu
 * 	[1998/07/29  20:17:19  James_Woodward]
 * 
 * Revision 4.3.22.2  1998/05/07  18:32:34  Andrew_Duane
 * 	Make sysent constant (for NUMA replicated text).
 * 	[1998/05/07  18:31:42  Andrew_Duane]
 * 
 * Revision 4.3.18.2  1994/12/15  22:05:03  Jeff_Denham
 * 	Add a CM_DYNAMIC flag to help out dynamic habitats. The CM_STATIC
 * 	flag should make this flag unnecessary, but we're working around
 * 	an architectural shortcoming here.
 * 	[1994/12/12  22:23:46  Jeff_Denham]
 * 
 * Revision 4.3.14.6  1994/05/12  18:02:05  Thomas_Peterson
 * 	Fixes required for ANSI/C++.  Fully prototyped functions & function
 * 	pointers.  Added C++ macros.  Added forward struct decls.
 * 	[1994/04/15  21:42:40  Thomas_Peterson]
 * 
 * Revision 4.3.14.5  1993/12/14  16:57:46  Ernie_Petrides
 * 	Modify sysent structure for syscall() rework.
 * 	[1993/12/12  02:44:33  Ernie_Petrides]
 * 
 * Revision 4.3.14.4  1993/10/12  13:11:11  James_Woodward
 * 	merge of Sterling BL6 changes
 * 	[1993/10/12  12:50:49  James_Woodward]
 * 
 * Revision 4.3.14.3  1993/09/15  20:28:50  Larry_Scott
 * 	start of security merge
 * 	[1993/09/15  20:07:54  Larry_Scott]
 * 
 * Revision 4.3.14.2  1993/06/11  17:02:08  Anton_Verhulst
 * 	Remove obsolete mpid global.
 * 	[1993/06/08  18:47:01  Anton_Verhulst]
 * 
 * Revision 4.3.4.5  1992/09/29  16:50:12  Anton_Verhulst
 * 	Merged in AG_BL10_4.
 * 	[92/09/29  16:37:56  Anton_Verhulst]
 * 
 * Revision 4.3.4.4  92/09/11  17:31:44  Anton_Verhulst
 * 	Change boothowto from int to long.
 * 	[92/09/11  17:25:13  Anton_Verhulst]
 * 
 * Revision 4.3.4.3  92/04/15  14:13:06  Shashi_Mangalat
 * 	Merged in Silver BL6.
 * 	Integrated svid3, svr4, soe2 habita ts into base.
 * 	  [92/03/27  19:09:28  Peter_Lega]
 * 	Add cm_valid struct, increase max habitats to 16, remove sysbase
 * 	  Change ULT_BIN to ULTBIN.
 * 	  [92/03/06  19:07:27  Philip_Cameron]
 * 	[92/04/15  13:27:28  Shashi_Mangalat]
 * 
 * Revision 4.3.4.2  92/03/18  22:26:51  Shashi_Mangalat
 * 	Merged in Silver BL5
 * 	Added vector of statically linked modules. Add information
 * 	  for support of loadable compatability modules and loadable
 * 	  habitats.  [Philip_Cameron]
 * 	[92/03/18  22:12:09  Shashi_Mangalat]
 * 
 * Revision 4.3  92/01/15  02:12:40  devbld_gsf
 * 	Baselevel alpha_bl002
 * 
 * Revision 4.2.2.2  91/12/07  16:52:28  Jay_Estabrook
 * 	merge ALPHA with SILVER via ODE
 * 	[91/12/07  16:39:27  Jay_Estabrook]
 * 	Added vector of statically linked modules.
 * 	[92/02/05  10:24:28  Philip_Cameron]
 * 	Add information for support of loadable compatability modules and
 * 	loadable habitats.
 * 	[92/01/10  15:45:58  Philip_Cameron]
 * 
 * Revision 4.2  91/09/19  23:00:48  devbld
 * 	Adding ODE Headers
 * 
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: systm.h,v $ $Revision: 4.3.48.2 $ (DEC) $Date: 2003/12/09 20:23:35 $
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
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 */

#ifndef	_SYS_SYSTM_H_
#define _SYS_SYSTM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

struct proc;
struct filehdr;

/*
 * Structure of the system-entry table
 *
 * NOTE: sizeof(struct sysent) is known to be 16 bytes in locore.s
 */
#define NUMSYSCALLARGS 6
struct sysent {
	int	(*sy_call) __((struct proc *, ...)); /* syscall handler */
	unsigned char sy_info;		/* holds number of args and flags */
	unsigned char aud_param[NUMSYSCALLARGS+1];
					/* audit encodings (see audit.h) */
};
#ifdef _KERNEL
#define SY_NARG(sysentp) ((sysentp)->sy_info & 0x0f)
#endif /* _KERNEL */

/*
 * Compatability module control block
 */
#define MAXCOMPATNAMSZ  16
#define MAXSTANZANAMSZ  16
#define MAXREVSZ	16
struct compat_mod {
	struct compat_mod *cm_next;		/* next in chain	*/
	char		cm_name[MAXCOMPATNAMSZ];/* name of this module	*/
	char		cm_ld_name[MAXSTANZANAMSZ];/* name stanza for module */
	char		cm_rev[MAXREVSZ];	/* revision in ascii	*/
	int		cm_revision;		/* revision number	*/
	int		(*cm_configure) __((int, ...));	/* config entry	*/
	struct compat_mod *(*cm_recognizer) __((struct filehdr *, ...));
	struct sysent	*(*cm_syscall) __((long)); /* sysent func	*/
	char		**call_name;		/* list of func names	*/
	int		cm_habitat;		/* habitat number	*/
	int		cm_base;		/* first sysent number	*/
	int		cm_nsysent;		/* number of sys calls	*/
	int		cm_refcount;		/* reference count	*/
	int		cm_totalcount;		/* usage count		*/
	int		cm_skipcount;		/* skip count		*/
	int		cm_nsyscalls;		/* number of traced svcs*/
	int		cm_flags;		/* control flags	*/
	unsigned int	*cm_auditmask;		/* module auditmask	*/
	int		*cm_stats;		/* statistics vector	*/
	char		*cm_trace;		/* Trace flag vector	*/
};
/* valid module names */
#define ULTBIN		"Ultrix4.2"
/* valid revisions */
#define ULT42V11	0x0101	/* 1.1 */
#define ULT42V11A	"1.1"
/* cm_flags */
#define	CM_DEBUG	1
#define CM_TRACE	2
#define CM_STATIC	4	/* can't unload this module */
#define CM_CONFIG	8	/* module is configured */
#define CM_DYNAMIC	0x10	/* module is dynamic */
#define CM_TRACE_THIS	0x100	/* trace this call */

/*
 * Habitats and static modules
 *	MAXHABITATS is the maximum habitat number that is currently supported.
 *	MAXSTATICMODS is the maximum number of statically linked modules.
 */
#define MAXHABITATS	16
#define MAXSTATICMODS	16

/*
 * Validity checking struct
 *	Each valid name and revision is listed
 */
struct cm_valid {
	char	*cm_name;	/* valid name ..... */
	int	cm_rev;		/* .... and revision */
};

/*
 * Compatability module data for cfgmgr query command.
 *	This passes back trace information for one syscall at a time
 */
struct compat_query {
	int	next;		/* next non-zero count */
	int	svc;		/* svc being queried */
	int	count;		/* number of calls */
	int	trace;		/* trace flag */
	char	name[32];	/* name of the system call */
};

/*
 * Compatability module data for cfgmgr operate command.
 *	This passes trace and debug instructions
 */
struct compat_operate {
	int	on_flgs;	/* flags that are being truned on */
	int	off_flgs;	/* flags that are being turned off */
	int	skip;		/* skip count */
	char	svc[32];	/* trace svc name */
};

/*
 * This is the major # of FDFS filesystem used by
 * io/common/conf.c (must be visible outside kernel).
 */
#define FDFS_MAJOR	12


#ifdef _KERNEL

/*
 * Everything below here is only relevant to the compilation of objects
 * which comprise the kernel (including device drivers, file systems,
 * and other kernel layered products).
 */

#include <mach/boolean.h>

#define FORCE_CONST_READ(type, name) \
				(*(type volatile *)(&name))
#define FORCE_CONST_WRITE(type, name, value) \
				(*(type volatile *)(&name) = (value))


/*
 * Miscellaneous kernel global variables
 */

#ifndef REPLICATED
#define REPLICATED
#endif

extern char	version[];		/* system version */
extern dev_t	rootdev;		/* device of the root */
extern struct vnode *rootvp;		/* vnode of root filesystem */
extern dev_t	dumpdev;		/* device to take dumps on */
extern daddr_t	dumplo;			/* offset into dumpdev */
extern int	maxmem;			/* actual max memory per process */
extern int	physmem;		/* physical memory on this CPU */
extern const int nsysent;		/* size of standard syscall table */
extern const struct sysent sysent[];	/* system call table */

extern char	*panicstr;		/* system panic string */
extern long	boothowto;		/* reboot flags, from console subsys */
extern u_long	bootdev;		/* boot dev, from bootstrap subsys */
extern int	selwait;
extern int	shutting_down;
extern int	printstate;

/*
 * State bits for the kernel global "printstate"
 */
#define PROMPRINT	0x1	/* only print available is thru PROM */
#define CONSPRINT	0x2	/* print thru console driver is available */
#define MEMPRINT	0x4	/* print to errlog is available */
#define PANICPRINT	0x8	/* panic in progress, print to screen */
#define PRE_PANICPRINT	0x10	/* ensure printf's make it to the screen */

/*
 * Things related to time and clock interrupts
 */
extern REPLICATED int hz;	/* frequency of system clock interrupts */
extern REPLICATED int tick;	/* number of microseconds per clock tick */
extern REPLICATED int fixtick;	/* adjustment per second: (1000000 % hz) */
extern int	phz;		/* frequency of possible alternate clock */
extern long	lbolt;		/* count of clock interrupts since boot */
extern struct	timeval time;	/* time as secs/usecs since 1/1/1970 UTC */
extern struct	timeval boottime; /* time when system was booted */
extern struct	timezone tz;	/* time zone information */

#define LSCALE	1000		/* scaling for "fixed point" arithmetic */
extern long	avenrun[3];
extern long	mach_factor[3];

/*
 * Things related to cpu availability
 */
extern REPLICATED int ncpus;      /* highest available cpu number plus one */
extern REPLICATED int first_cpu;  /* lowest available cpu number */
extern REPLICATED int multicpu;   /* set before configuring secondary cpus */
extern REPLICATED int boot_cpu;   /* the cpu number of the boot cpu */
extern REPLICATED int master_cpu; /* the cpu number of the master cpu */
extern REPLICATED int master_cpuid; /* whami register value of master cpu */
extern REPLICATED int cpus_in_box;  /* number of cpus present in the system */
extern REPLICATED int cpu_slots;    /* the number of cpu slots in the system */
extern REPLICATED boolean_t numa_system; /* flag set if system is NUMA */

/*
 * The following macro is for avoidance of loop-hoisting compiler
 * optimizations in top-level functions implementing kernel threads
 * if the "const" type qualifier on "ncpus" is ever made visible to
 * all compilation units.
 */
#define volatile_ncpus		(*(volatile int *)&ncpus)

/*
 * Lock protecting hostname, hostid, domainname and uname variables
 */
extern	rws_lock_t	hostname_lock;
#define HOSTNAME_LOCKINIT()	hostname_lock=rws_alloc(hostname_lockinfo,0)
#define	HOSTNAME_LOCK()		rws_read_lock(hostname_lock)
#define	HOSTNAME_UNLOCK()	rws_read_unlock(hostname_lock)
#define	HOSTNAME_WRITE_LOCK()	rws_write_lock(hostname_lock)
#define	HOSTNAME_WRITE_UNLOCK()	rws_write_unlock(hostname_lock)

extern REPLICATED int	hostid;
extern REPLICATED char	hostname[];
extern REPLICATED int	hostnamelen;
extern REPLICATED char	domainname[];
extern REPLICATED int	domainnamelen;


/*
 * Kernel function prototypes
 */

/*VARARGS1*/
extern void printf(char *fmt, ...);
extern void aprintf(char *fmt, ...);
extern void dprintf(char *fmt, ...);
extern int uprintf(char *fmt, ...);
extern int uprintf_safe(char *fmt, ...);
extern int sprintf(char *buf, char *fmt, ...);
extern int sprintf2(char *buf, char *end, char *fmt, ...);
extern void log(int level, char *fmt, ...);
extern void putchar(int c);

extern void panic(char *s);
extern int pre_panic(void);
extern void tablefull(char *tab);
extern void xcpu_puts_ipir(void);
extern void xcpu_panic_ipir(void);

extern int mpsleep(void *chan, int pri, char *wmesg, int timo, void *lockp,
		   long flags);
extern void wakeup(void *chan);
extern void wakeup_one(void *chan);
extern int hzto(struct timeval *);
extern long hzto_long(struct timeval *, struct timeval *);
extern void timeout(void (*func)(void *arg), void *arg, int t);
extern int timeout_cpu(void (*func)(), void *arg, long t, int type);
extern int untimeout(void (*func)(void *arg), void *arg);
extern int untimeout_cpu(void (*func)(), void *arg, int cpu, int type,
					void *rem);
extern int event_timeout(int (*func)(), void *arg, int seconds);

extern size_t strlen(const char *string);
extern int strcmp(const char *string1, const char *string2);
extern int strncmp(const char *string1, const char *string2, int length);
extern char *strcat(char *destination, const char *source);
extern char *strcpy(char *destination, const char *source);
extern char *strncpy(char *destination, const char *source, int length);
extern int copystr(const char *src, char *dst, u_int maxlen, u_int *lencopied);

extern void bcopy(void *source, void *destination, size_t length);
extern void qcopy(void *source, void *destination, size_t length);
extern void blkcpy(void *source, void *destination, size_t length);
extern int eblkcpy(void *source, void *destination, size_t length);
extern void bzero(void *destination, size_t length);
extern void qzero(void *destination, size_t length);
extern void blkclr(void *destination, size_t length);
extern void *memcpy(void *destination, const void *source, size_t length);
extern int bcmp(const void *string1, const void *string2,  size_t length);
#ifndef __VMS
#define bcopy6(_src, _dest) memcpy((_dest), (_src), 6)
#else /* __VMS */
#define bcopy6(_src,_dest) bcopy(_src,_dest,6)
#define memcpy(_dest,_src,_len) bcopy(_src,_dest,_len)
#pragma intrinsic (bcopy,bzero,strlen)
#endif /* __VMS */
extern void write_const_data(void *, const void *, size_t);
extern void write_const_data_nosynch(void *, const void *, size_t);

extern int lsb(unsigned long);
extern int msb(unsigned long);
extern void preemption_on(void);
extern void preemption_off(void);
extern void stray(u_long, u_long);
typedef void (*HANDLER)(unsigned long, unsigned long);
extern void intrsetvec(u_int, HANDLER, u_long);

extern void mb_smp_only(void);
#ifndef __VMS
extern unsigned short in_checksum(vm_offset_t, vm_size_t, unsigned short);
#else /* __VMS */
extern unsigned short in_checksum(vm_offset_t, int, unsigned short);
#endif /* __VMS */

#ifndef __VMS
#ifdef __DECC
#define atomic_incq(x)		__ATOMIC_INCREMENT_QUAD(x)
#define atomic_incl(x)		__ATOMIC_INCREMENT_LONG(x)
#define atomic_decq(x)		__ATOMIC_DECREMENT_QUAD(x)
#define atomic_decl(x)		__ATOMIC_DECREMENT_LONG(x)
#define atomic_addl(x,y)	__ATOMIC_ADD_LONG(x,y)
#define atomic_addq(x,y)	__ATOMIC_ADD_QUAD(x,y)
#define atomic_excl(x,y)	__ATOMIC_EXCH_LONG(x,y)
#define atomic_excq(x,y)	__ATOMIC_EXCH_QUAD(x,y)
#else /* __DECC */
extern int atomic_addl(int *, int);
extern int atomic_incl(int *);
extern int atomic_decl(int *);
extern int atomic_excl(int *, int);
extern unsigned long atomic_addq(unsigned long *, unsigned long);
extern unsigned long atomic_incq(unsigned long *);
extern unsigned long atomic_decq(unsigned long *);
extern unsigned long atomic_excq(unsigned long *, unsigned long);
#endif /* __DECC */
#else /* __VMS */
#ifdef __VAX
extern int __ATOMIC_ADD_LONG(int *, int);
extern int __ATOMIC_INCREMENT_LONG(int *);
extern int __ATOMIC_DECREMENT_LONG(int *);
#endif	/* __VAX */
#define atomic_incl(x)		(unsigned int) __ATOMIC_INCREMENT_LONG((int *)(x))
#define atomic_decl(x)		(unsigned int) __ATOMIC_DECREMENT_LONG((int *)(x))
#define atomic_addl(x,y)	(unsigned int) __ATOMIC_ADD_LONG((int *)(x),(y))
extern unsigned long atomic_addq(unsigned long *, unsigned long);
extern unsigned long atomic_incq(unsigned long *);
extern unsigned long atomic_decq(unsigned long *);
extern int clear_bit_l(int, long *);
extern int test_and_set_l(int, long *);
#endif /* __VMS */

#include <sys/usercopy.h>

extern caddr_t	calloc __((long));

/*
 * Compatability module support
 */
extern struct compat_mod *habitats[MAXHABITATS];
extern struct cm_valid cm_valid[]; /* valid modules */
extern void (*cm_static[MAXSTATICMODS]) __((void));

#ifdef lint /* casts to keep lint happy */
#define insque(q,p)	_insque((caddr_t)(q), (caddr_t)(p))
#define remque(q)	_remque((caddr_t)(q))
#endif /* lint */


/*
 * Define some compiler intrinsics, either through true intrinsics or
 * through asm() statements.  Note that it is essential that all kernel
 * objects be compiled with the machine-dependent kintrisincs.h visible
 * in order to enforce pragmas which are required for correct compilation.
 */
#include <machine/spl.h>
#include <machine/builtins.h>
#include <machine/kintrinsics.h>


/*
 * _BASE_KERNEL_PRIVATE
 *
 * This identifier has been created to distiguish between internal builds
 * of the base kernel and the compilations of kernel components (such as
 * device drivers, file systems, and layered products) of external third
 * parties.  This provides a mechanism for "hiding kernel internals" in
 * system header files so that certain "hidden" data structures and macro
 * definitions can be changed in minor releases without impacting kernel
 * binary compatibility.  (The use of this mechanism in no way impacts
 * application binary compatibility.)  Any person or group who thwarts
 * the logic below and enables the definition of _BASE_KERNEL_PRIVATE
 * in the building of their kernel components risks the malfunction of
 * those kernel objects if used with any future major or minor release
 * of the base kernel.
 *
 * Please use the line with the "#ifdef _BASE_KERNEL_PRIVATE ..." below
 * as a template when introducing the relevant conditional compilation
 * in system header files to appropriately document this issue.
 */
#ifdef _BASE_KERNEL_PRIVATE /* see sys/systm.h - kernel binary compatibility */
#error Do not define _BASE_KERNEL_PRIVATE (see <sys/systm.h> for more details).
#undef _BASE_KERNEL_PRIVATE
#else
#if defined(IDENT) && defined(BINARY)
#if IDENT == 1 && BINARY == 1
#undef BINARY
#define BINARY 2
#if IDENT == BINARY
/* the following defines _BASE_KERNEL_PRIVATE for internal builds in BINARY */
#include <internal.h>
#if _BASE_KERNEL_PRIVATE == 0
#undef _BASE_KERNEL_PRIVATE
#endif /* _BASE_KERNEL_PRIVATE == 0 */
#endif /* IDENT == BINARY */
#endif /* IDENT == 1 && BINARY == 1 */
#endif /* defined(IDENT) && defined(BINARY) */
#endif /* _BASE_KERNEL_PRIVATE */

#endif /* _KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* _SYS_SYSTM_H_ */
