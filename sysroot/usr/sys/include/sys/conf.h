/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: conf.h,v $
 * Revision 4.4.37.1  2005/11/22  23:23:23  Keith_Martin
 * 	Add an ifndef within struct dsent to allow including this file in
 * 	a C++ program.  In C++, private is a reserved word.
 * 	WFM3210529364-323.
 *
 * Revision 4.4.31.1  2002/05/30  23:16:43  Ashoke_Rampuria
 * 	Changes for compiler switch project
 *
 * Revision 4.4.29.3  2000/01/27  20:27:16  Ernie_Petrides
 * 	Allow for replication of "nblkdev" and "nchrdev".
 *
 * Revision 4.4.29.2  1998/08/26  12:41:27  James_Woodward
 * 	Merge of numaproj and zulu
 * 	[1998/07/29  20:17:10  James_Woodward]
 *
 * Revision 4.4.27.2  1998/05/12  17:14:07  Andrew_Duane
 * 	Make devsw tables "const" to replicate them for NUMA.
 * 	[1998/05/08  12:32:07  Andrew_Duane]
 * 
 * Revision 4.4.25.3  1998/02/19  22:24:54  David_Gagne
 * 	Add a new flag for reserved device switch table entries.
 * 	[1998/02/19  21:46:14  David_Gagne]
 * 
 * Revision 4.4.25.2  1996/04/30  18:32:09  Jeff_Denham
 * 	Merge from bravos.bl2
 * 	[1996/04/30  15:37:06  Jeff_Denham]
 * 
 * Revision 4.4.21.3  1996/03/10  15:37:35  Ray_Lanza
 * 	Merge of Platinum BL8 to BL11 pass 1 changes
 * 	[1996/03/10  15:19:21  Ray_Lanza]
 * 
 * Revision 4.4.23.2  1995/11/14  19:00:42  David_Gagne
 * 	Create a devsw entry with fields for both b and c.
 * 	[1995/11/13  23:43:06  David_Gagne]
 * 
 * Revision 4.4.21.2  1995/10/31  23:06:42  Ray_Lanza
 * 	Changed macro concatenation to ansi style
 * 	[1995/10/31  22:52:06  Ray_Lanza]
 * 
 * Revision 4.4.15.11  1994/04/16  02:44:12  Paula_Long
 * 	Merged with latest revision
 * 	[1994/04/12  09:09:25  Paula_Long]
 * 
 * 	Updated locks to use lockinfo,(still no heirarchy or spl checking)
 * 	[1994/04/10  23:39:47  Paula_Long]
 * 
 * Revision 4.4.15.10  1994/04/11  21:07:04  Mark_Parenti
 * 	Move define of DEV_FUNNEL to this file. This makes is consistent
 * 	with DEV_FUNNEL_NULL and allows loadable drivers to use the define
 * 	in their devsw entries.
 * 	[1994/04/08  14:21:32  Mark_Parenti]
 * 
 * Revision 4.4.15.9  1994/02/04  07:57:17  Tim_Hoskins
 * 	merge of Sterling BL9 changes
 * 	[1994/02/04  07:43:36  Tim_Hoskins]
 * 
 * Revision 4.4.15.8  1994/01/07  18:28:03  Thomas_Peterson
 * 	Merge of C++ specific changes forward from Sterling BL9 to Gold BL8.
 * 
 * 	Revision 4.4.16.5  1993/12/15  22:11:39  Thomas_Peterson
 * 	   Added forward decl for struct tty as required for C++.
 * 	   [1993/12/09  20:26:54  Thomas_Peterson]
 * 	[1994/01/03  20:25:22  Thomas_Peterson]
 * 
 * Revision 4.4.16.6  1993/12/21  20:43:36  SJ_Lee
 * 	Move DEV_FUNNEL_NULL here.
 * 	[1993/12/20  19:51:33  SJ_Lee]
 * 
 * Revision 4.4.15.7  1993/12/14  16:57:39  Ernie_Petrides
 * 	Optimize funneling checks.
 * 	[1993/12/12  02:44:17  Ernie_Petrides]
 * 
 * Revision 4.4.15.6  1993/11/05  06:29:04  Tim_Hoskins
 * 	merge of Sterling BL7 changes
 * 	[1993/11/05  06:08:08  Tim_Hoskins]
 * 
 * Revision 4.4.15.5  1993/10/14  18:51:54  James_Woodward
 * 	save off funnel bit value at start of device operation
 * 	[1993/10/14  18:44:14  James_Woodward]
 * 
 * Revision 4.4.16.4  1993/09/21  22:14:57  SJ_Lee
 * 	change BDEVSW_IOCTL(m,d,c,d1,f,r,c,p,rv) to
 * 	BDEVSW_IOCTL(m,d,c,d1,f,r,e,p,rv)
 * 	to fix a compiling error when _std flag is on.
 * 	[1993/09/13  20:28:39  SJ_Lee]
 * 
 * Revision 4.4.15.4  1993/09/09  19:33:02  Stan_Luke
 * 	pre-merge Sterling.
 * 	[1993/09/09  19:23:51  Stan_Luke]
 * 
 * Revision 4.4.15.3  1993/08/18  21:28:55  Peter_Schulter
 * 	SVR4 Compatable STREAMS infrastructure premerge
 * 	[1993/08/18  18:21:00  Peter_Schulter]
 * 
 * Revision 4.4.16.3  1993/05/12  19:01:49  Peter_Schulter
 * 	Check in for submit to minor pool
 * 	[1993/05/12  16:11:38  Peter_Schulter]
 * 
 * Revision 4.4.10.3  1993/05/11  03:44:44  Ronald_Menner
 * 	merge to Sterling BL2+
 * 	[1993/05/11  03:17:17  Ronald_Menner]
 * 
 * Revision 4.4.16.2  1993/05/03  20:59:25  Mark_Parenti
 * 	Add new fields for DDI/DKI compatibility.
 * 	[1993/04/30  15:58:02  Mark_Parenti]
 * 
 * Revision 4.4.15.2  1993/04/28  23:53:50  Paula_Long
 * 	submitting the SMP project
 * 	[1993/04/28  18:32:10  Paula_Long]
 * 
 * Revision 4.4.12.2  1993/03/26  12:01:58  James_Woodward
 * 	first cut at rt+MP
 * 	[1993/03/25  20:25:22  James_Woodward]
 * 
 * Revision 4.4.10.2  1993/03/10  21:39:25  Peter_Schulter
 * 	First pass at R4 STREAMS Alpha port
 * 	[1993/03/10  21:34:23  Peter_Schulter]
 * 
 * Revision 4.4.3.6  1992/06/29  10:07:04  Pete_Snider
 * 	Added in missing fields, mode, username, user, groupname, and group,
 * 	for Assign_table and Assign_entry.
 * 	[92/06/29  10:05:48  Pete_Snider]
 * 
 * Revision 4.4.3.5  92/06/03  13:43:58  Paul_Hansen
 * 	Merged in Silver BL7
 * 	[92/06/03  13:34:51  Paul_Hansen]
 * 
 * Revision 4.4.3.4  92/04/17  14:25:39  Andrew_Duane
 * 	Changed major and minor fields in Assign_entry and Assign_table structs  to
 * 	ae_major/at_major and ae_minor/at_minor to avoid #defines for major/minor
 * 	[92/04/17  14:25:00  Andrew_Duane]
 * 
 * Revision 4.4.3.3  92/04/15  14:06:58  Shashi_Mangalat
 * 	Merged in Silver BL6.
 * 	Correct ifdef of Assign_table and Assign_entry.
 * 	  Add define and typedef's needed by assign_table in conf.c and by the new
 * 	  getsysinfo calls to retrieve info from this table
 * 	  [Debra_Haeck]
 * 	Removed conditional compilation of d_funnel in bdevsw and
 * 	  cdevsw struct. Always include the field.
 * 	  [Timothy_Burke]
 * 	Fix broken RT Kernel build. Include kern/parallel.h because
 * 	  unix_master/release is being used.
 * 	  [Ronald_Widyono]
 * 	[92/04/15  13:14:27  Shashi_Mangalat]
 * 
 * Revision 4.4.3.2  92/01/28  18:37:17  Shashi_Mangalat
 * 	Merged in Silver BL3
 * 	[92/01/28  18:12:41  Shashi_Mangalat]
 * 
 * Revision 4.4.1.2  92/01/24  18:14:21  devbld_gsf
 * 	First AG_BL3 version. Moved from AG baselevel delivery tree.
 * 
 * Revision 4.4  92/01/15  02:09:36  devbld_gsf
 * 	Baselevel alpha_bl002
 * 
 * Revision 4.3.2.2  91/12/07  16:49:26  Jay_Estabrook
 * 	merge ALPHA with SILVER via ODE
 * 	[91/12/07  16:22:26  Jay_Estabrook]
 * 
 * Revision 4.3  91/11/26  11:12:49  devbld_zk3
 * 	Baselevel AG_BL0
 * 
 * Revision 4.2.2.2  91/10/25  14:49:35  William_Burns
 * 	Merge from ODE/TIN: revision 3.2.9.2
 * 	date: 91/10/22 20:06:24;  author: devrcs;  state: Exp;  lines added/del: 24/4
 * 	sccs rev: 3.4;  orig date: 91/10/08 14:58:40;  orig author: plong
 * 	  Realtime extension
 * 	[91/10/25  12:47:52  William_Burns]
 * 
 * Revision 4.2  91/09/19  22:57:05  devbld
 * 	Adding ODE Headers
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: conf.h,v $ $Revision: 4.4.37.1 $ (DEC) $Date: 2005/11/22 23:23:23 $
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
 * conf.h
 *
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 */

#ifndef	_SYS_CONF_H_
#define _SYS_CONF_H_

#ifdef	_KERNEL
#ifndef REPLICATED
#define REPLICATED
#endif
#include <sys/unix_defs.h>
#endif
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/buf.h>
#include <io/common/devdriver.h>

/*
 * Declaration of block device
 * switch. Each entry (row) is
 * the only link between the
 * main unix code and the driver.
 * The initialization of the

 * device switches is in the
 * file conf.c.
 */

struct bdevsw
{
	int	(*d_open)();
	int	(*d_close)();
	int	(*d_strategy)();
	int	(*d_dump)();
	int	(*d_psize)();
	int	d_flags;
	int	(*d_ioctl)();
	int 	d_funnel;	/* serial code compatibility */
};

#ifdef _KERNEL
extern const struct bdevsw bdevsw[];
extern REPLICATED int nblkdev;	/* number of entries in bdevsw[] */
#endif /* _KERNEL */

/* forward declaration required for C++ */
#ifdef __cplusplus
struct tty;
#endif

struct cdevsw
{
	int	(*d_open)();
	int	(*d_close)();
	int	(*d_read)();
	int	(*d_write)();
	int	(*d_ioctl)();
	int	(*d_stop)();
	int	(*d_reset)();
	struct tty *d_ttys;
	int	(*d_select)();
	int	(*d_mmap)();
	int 	d_funnel;	/* serial code compatibility */
	int	(*d_segmap)();		/* xxx_segmap() entry point */
	int	d_flags;		/* if (C_DDIDKI), driver follows
					   SVR4 DDI/DKI interfaces*/
};

/*
 * Flag definitions for d_flags field of cdevsw
 */
#define C_DDIDKI	0x10000000

/*
 * Definitions for d_funnel field of devsw
 */
#define DEV_FUNNEL_NULL  NULL
#define DEV_FUNNEL	 1 


#ifdef _KERNEL
extern const struct cdevsw cdevsw[];
extern REPLICATED int nchrdev;	/* number of entries in cdevsw[] */
#endif /* _KERNEL */

/*
 * Declaration of a device switch entry.  This entry is the only link
 * between the main unix code and the driver.  Each entry can be used
 * for access to the driver by both block and character device special
 * files (dev_t values).  If the driver doesn't support access by both
 * block and character, then the driver must perform the appropriate
 * check in the open routine and return an error for the devices it
 * does not support.
 */

struct dsent
{
  int  (*d_open    )(dev_t dev, int flag, int fmt);
  int  (*d_close   )(dev_t dev, int flag, int fmt);
  void (*d_strategy)(struct buf *bp);
  int  (*d_read    )(dev_t dev, struct uio *uio);
  int  (*d_write   )(dev_t dev, struct uio *uio);
  int  (*d_ioctl   )(dev_t dev, uint cmd, caddr_t data, int flag);
  int  (*d_dump    )(struct dump_request *);
  int  (*d_psize   )(dev_t dev);
  int  (*d_stop    )(struct tty *tp, int flag);
  int  (*d_reset   )(int flag);
  int  (*d_select  )(dev_t dev, short *events, short *revents,
#ifndef __cplusplus
			int scanning, void *private);
#else
			int scanning, void *sprivate);
#endif
  int (*d_mmap     )(dev_t dev, off_t offset, int prot);
  int (*d_segmap   )(dev_t dev, off_t off, void *map, caddr_t* addr,
                       off_t offset, unsigned int i,
                       unsigned int j, unsigned int k, struct ucred* cred);
  struct tty *d_ttys;
  int d_funnel;
  int d_bflags;
  int d_cflags;
};

/*
 * tty line control switch.
 */

struct linesw
{
	int	(*l_open)();
	int	(*l_close)();
	int	(*l_read)();
	int	(*l_write)();
	int	(*l_ioctl)();
	int	(*l_rint)();
	int	(*l_rend)();
	int	(*l_meta)();
	int	(*l_start)();
	int	(*l_modem)();
};

/*
 * Swap device information
 */
struct swdevt
{
        dev_t   sw_dev;
        int     sw_freed;
        int     sw_nblks;
        int     sw_type;
        int	*sw_gnodeptr;       /* gnode pointer */
        int	(*sw_strat)( /* bp */ );
        int	sw_priority;
	int	sw_nio;
 };
#define sw_gptr                 sw_gnodeptr
#define sw_pri                  sw_priority

#ifdef	_KERNEL
extern struct	linesw linesw[];
#endif

#ifdef	_KERNEL
#include <ser_compat.h>
#include <rt_preempt.h>
#include <kern/lock.h>
#include <kern/parallel.h>

/*
 * Character and Block Device Switch Locking definition.
 *
 * A device switch lock guards a particular entry in a
 * device switch table; these locks are used by the
 * driver open routines.  Note that these locks have
 * nothing to do with synchronizing the drivers themselves;
 * they guard the use of entries in the devsw arrays.
 */
typedef struct dswlock {
        lock_data_t     dsw_lock;               /* devsw entry r/w lock */
        int             dsw_flags;              /* devsw entry status flags */
} dswlock_t;

/*
 * Parallel device switch lock arrays, one entry
 * for each entry in cdevsw and bdevsw.
 */
extern dswlock_t cdevlock[];                    /* cdevsw lock structure */
extern dswlock_t bdevlock[];                    /* bdevsw lock structure */

extern struct lockinfo *bdev_lockinfo;
extern struct lockinfo *cdev_lockinfo;

						/* dsw flag defines */
#define DSW_INUSE	0x0001			/* table entry is in use */
#define DSW_RESERVED	0x0002			/* table entry is reserved */

						/* Lock macros for open() */
#define CDEVSW_READ_LOCK(maj)		lock_read(&(cdevlock[maj].dsw_lock))
#define CDEVSW_WRITE_LOCK(maj)		lock_write(&(cdevlock[maj].dsw_lock))
#define CDEVSW_READ_UNLOCK(maj)		lock_done(&(cdevlock[maj].dsw_lock))
#define CDEVSW_WRITE_UNLOCK(maj)	lock_done(&(cdevlock[maj].dsw_lock))
#define BDEVSW_READ_LOCK(maj)		lock_read(&(bdevlock[maj].dsw_lock))
#define BDEVSW_WRITE_LOCK(maj)		lock_write(&(bdevlock[maj].dsw_lock))
#define BDEVSW_WRITE_UNLOCK(maj)	lock_done(&(bdevlock[maj].dsw_lock))
#define BDEVSW_READ_UNLOCK(maj)		lock_done(&(bdevlock[maj].dsw_lock))
#define CDEVSW_LOCK_INIT(maj)		\
		lock_setup(&(cdevlock[maj].dsw_lock),cdev_lockinfo, TRUE)
#define BDEVSW_LOCK_INIT(maj)		\
		lock_setup(&(bdevlock[maj].dsw_lock),bdev_lockinfo, TRUE)

#define PASTE(a,b) a##b

/*
 * The following macros hide the use of funneling from most kernel code.
 */

#if SER_COMPAT || RT_PREEMPT
#define	DEVSW_FUNNEL(sw,maj)	(PASTE(sw,devsw)[(maj)].d_funnel)
#else
#define	DEVSW_FUNNEL(sw,maj)	(0)
#endif

#define	_DVC_(sw,f,maj,args,ret)					\
MACRO_BEGIN								\
	if (!DEVSW_FUNNEL(sw,maj)) {					\
		(ret) = (*PASTE(sw,devsw)[(maj)].PASTE(d_,f))args;	\
	} else {							\
		unix_master();						\
		(ret) = (*PASTE(sw,devsw)[(maj)].PASTE(d_,f))args;	\
		unix_release();						\
	}								\
MACRO_END

#define	_DVC_OPT_(sw,f,maj,args,ret)					\
MACRO_BEGIN								\
	if (PASTE(sw,devsw)[(maj)].PASTE(d_,f)) {			\
		if (!DEVSW_FUNNEL(sw,maj)) {				\
			(ret) = (*PASTE(sw,devsw)[(maj)].PASTE(d_,f))args;\
		} else {						\
			unix_master();					\
			(ret) = (*PASTE(sw,devsw)[(maj)].PASTE(d_,f))args;\
			unix_release();					\
		}							\
	} else {							\
  		(ret) = -1;						\
	}								\
MACRO_END

/*
 * These macros were developed to have a single interface for the cdevsw
 * and the bdevsw in code, but easily adding funneling.
 *
 * They are all called with 'similar' arguments:
 *	(major device #, arg1, arg2, ..., result)
 * where:
 *	result will be set to the return value of the b/cdevsw call.
 *	arg[12...] is the list of arguments to be passed into the call.
 *
 * Special-case open macros to use devsw locking to synchronize with 
 * dynamic installation of drivers.
 */

#define	BDEVSW_OPEN(maj,dev,mode,flag,ret,cred,priv)			\
MACRO_BEGIN								\
	BDEVSW_READ_LOCK(maj);						\
	_DVC_(b,open,maj,(dev,mode,flag,cred,priv),ret);		\
	BDEVSW_READ_UNLOCK(maj);					\
MACRO_END
#define	BDEVSW_CLOSE(m,d,f,f2,r,c,p)	_DVC_(b,close,m,(d,f,f2,c,p),r)
#define	BDEVSW_STRATEGY(m,bp,r)		_DVC_(b,strategy,m,(bp),r)
#define	BDEVSW_DUMP(m,d,lo,s,bl,f,r)	_DVC_(b,dump,m,(d,lo,s,bl,f),r)
#define	BDEVSW_PSIZE(m,d,r)		_DVC_OPT_(b,psize,m,(d),r)
#define	BDEVSW_IOCTL(m,d,c,d1,f,r,e,p,rv) \
					_DVC_(b,ioctl,m,(d,c,d1,f,e,p,rv),r)
#define	BDEVSW_FLAGS(m,r)		(r) = bdevsw[(m)].d_flags

/*
 * In OSF/1, a pointer to a ucred block is passed all the way through
 * to all the spec_xxx() functions, but not to the device specific
 * entry points.  This pointer must be passed to the open, close, read,
 * write and ioctl entry points of block drivers that follow the DDI/DKI
 * interfaces.
 */

#define	BDEVSW_DDI_OPEN(maj,dev,mode,flag,up,ret)			\
MACRO_BEGIN								\
	BDEVSW_READ_LOCK(maj);						\
	_DVC_(b,open,maj,(&dev,mode,flag,up),ret);			\
	BDEVSW_READ_UNLOCK(maj);					\
MACRO_END
#define	BDEVSW_DDI_CLOSE(m,d,f,f2,up,r)	_DVC_(b,close,m,(d,f,f2,up),r)
#define	BDEVSW_DDI_IOCTL(m,d,c,d1,f,up,rp,r) \
					_DVC_(b,ioctl,m,(d,c,d1,f,up,rp),r)

#define	CDEVSW_OPEN(maj,dev,mode,flag,newdev,ret,cred,priv)		\
MACRO_BEGIN								\
	CDEVSW_READ_LOCK(maj);						\
	_DVC_(c,open,maj,(dev,mode,flag,newdev,cred,priv),ret);		\
	CDEVSW_READ_UNLOCK(maj);					\
MACRO_END
#define	CDEVSW_CLOSE(m,d,f,mo,r,cr,p)	_DVC_(c,close,m,(d,f,mo,cr,p),r)
#define	CDEVSW_READ(m,d,u,f,r,p)	_DVC_(c,read,m,(d,u,f,p),r)
#define	CDEVSW_WRITE(m,d,u,f,r,p)	_DVC_(c,write,m,(d,u,f,p),r)
#define	CDEVSW_IOCTL(m,d,com,t,f,r,cr,p,rv) \
					_DVC_(c,ioctl,m,(d,com,t,f,cr,p,rv),r)
#define	CDEVSW_STOP(m,t,w,r)		_DVC_(c,stop,m,(t,w),r)
#define	CDEVSW_RESET(m,i,r)		_DVC_(c,reset,m,(i),r)
#define	CDEVSW_SELECT(m,d,e,re,s,r,p)	_DVC_(c,select,m,(d,e,re,s,p),r)
#define	CDEVSW_MMAP(m,d,o,p,r)		_DVC_(c,mmap,m,(d,o,p),r)
#define	CDEVSW_FLAGS(maj,r)		(r) = cdevsw[(maj)].d_flags
#define	CDEVSW_TTYS(maj,min,r)		(r) = cdevsw[(maj)].d_ttys + (min)

/*
 * In OSF/1, a pointer to a ucred block is passed all the way through
 * to all the spec_xxx() functions, but not to the device specific
 * entry points.  This pointer must be passed to the open, close, read,
 * write, ioctl and segmap entry points of character drivers that follow
 * the DDI/DKI interfaces.
 */

#define	CDEVSW_DDI_OPEN(maj,dev,mode,flag,up,ret)		        \
MACRO_BEGIN								\
	CDEVSW_READ_LOCK(maj);						\
	_DVC_(c,open,maj,(&dev,mode,flag,up),ret);			\
	CDEVSW_READ_UNLOCK(maj);					\
MACRO_END
#define	CDEVSW_DDI_CLOSE(m,d,f,mo,up,r)	_DVC_(c,close,m,(d,f,mo,up),r)
#define	CDEVSW_DDI_READ(m,d,u,up,r)	_DVC_(c,read,m,(d,u,up),r)
#define	CDEVSW_DDI_WRITE(m,d,u,up,r)	_DVC_(c,write,m,(d,u,up),r)
#define	CDEVSW_DDI_IOCTL(m,d,com,t,f,up,rp,r) \
					_DVC_(c,ioctl,m,(d,com,t,f,up,rp),r)
#define CDEVSW_DDI_SELECT(m,d,ev,a,rv,up,r) \
					_DVC_(c,select,m,(d,ev,a,rv,up),r)
#define	CDEVSW_SEGMAP(m,d,o,as,ad,l,p,mp,f,up,r) \
				_DVC_(c,segmap,m,(d,o,as,ad,l,p,mp,f,up),r)
#endif	/* _KERNEL */

/* size of ascii strings within the assign_table */
#define	ANAMELEN	80

/* struct that is returned to caller as a result of a getsyscall with op =
 * GSI_STATIC_NXT or GSI_STATIC_DEF
 */
typedef	struct	aentry {
	char	config_name[ANAMELEN];
	char	bc[2];
	int	mode;
	char	username[ANAMELEN];
	uid_t	user;
	char	groupname[ANAMELEN];
	gid_t	group;
	char	dirname[ANAMELEN];
	int	ae_major;
	int	ae_minor;
	char	dev_name[ANAMELEN];
} Assign_entry;

/* struct of assign table as it is really stored in conf.c */
typedef struct atable {
	char	config_name[ANAMELEN];
	char	bc[2];
	int     mode;
	char    username[ANAMELEN];
	uid_t   user;
	char    groupname[ANAMELEN];
	gid_t   group;
	char	dirname[ANAMELEN];
	int	at_major;
	int	*at_minor;
	char	*dev_name;
} Assign_table;

extern int nodev( ... );
extern int nulldev( ... ); 
extern void nodev_strategy( ... );
extern void nulldev_strategy( ... ); 


#endif	/* _SYS_CONF_H_ */
