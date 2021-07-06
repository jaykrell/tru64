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
 *	@(#)$RCSfile: flock.h,v $ $Revision: 4.3.33.1 $ (DEC) $Date: 2000/04/11 13:08:14 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */

#ifndef	_SYS_FLOCK_H
#define	_SYS_FLOCK_H
#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/vnode.h>
#include <sys/unix_defs.h>
#include <kern/lock.h>

/* forward struct decls for C++ */
#ifdef __cplusplus
struct flino;
#endif

struct blkpids {
	pid_t   blkpid;		/* pid of blocker */
	pid_t   blkrpid;	/* remote pid of blocker */
	u_int	blkrsys;	/* remote system of blocker */
	struct blkpids *next;
};
	
/*
 * file locking structure (connected to file table entry)
 *
 * Locking constraints on the filock structure.
 * 	Field			Comment
 *	-----			-------
 *	set			FICHAIN_LOCK (from flip field)
 *	stat			FICHAIN_LOCK
 *	prev			FICHAIN_LOCK
 *	next			FICHAIN_LOCK
 *	flip			read-only
 */
struct filock {
	struct	eflock set;	 /* contains type, start, and length */
	struct	filock *prev;
	struct	filock *next;
	struct	flino  *flip;	 /* back pointer to chain we are on */
#ifndef __cplusplus
	int 	class;		 /* Class of lock (FILE, LOCKMGR, or IO) */
#else
	int 	fclass;	       	 /* "class is reserved work in C++ */
#endif
	struct	vnode *vp;	 /* Pointer to vnode - need on sleeplck
				    and klm grant chains */
	struct blkpids *blkpids; /* Pointer to list of pids blocking the
				    lock.  Only used on sleep chain. */
};

/*
 * table to associate files with chain of locks
 *
 * Locking constraints for the flino structure.
 *	Field			Comment
 *	-----			-------
 *	vp			read-only
 *	fl_refcnt		flino_lock
 *	fl_flck			fi_chain_lock
 *	prev			FIDS_LOCK (global lock)
 *	next			FIDS_LOCK (global lock)
 *
 * The FIDS_LOCK cannot be taken while holding the flino_lock
 */
struct flino {
	udecl_simple_lock_data(, flino_lock)
	int		fl_refcnt;	/* # procs referencing flino */
	struct flino	*next;
	struct flino	*prev;
	lock_data_t	fichain_lock;	/* lock to protect fl_flck chain */
	struct filock	*fl_flck;	/* head of list of this file's locks */
	struct vnode	*vp;		/* vnode address for the file */
};

/*
 * file and record locking configuration structure
 * record and file use totals may overflow
 *
 * Locking constraints for the flockinfo structure.
 *	Field		Comment
 *	-----		-------
 *	recs		read-only
 *	fils		read-only
 *	reccnt		flckinfo_lock
 *	filcnt		flckinfo_lock
 *	rectot		flckinfo_lock
 *	filtot		flckinfo_lock
 */
struct flckinfo {
	int recmax;	/* max number of records locked at one time on system */
	int filmax;	/* max number of files locked at one time on system */
	int reccnt;	/* number of records currently in use */
	int filcnt;	/* number of file headers currently in use */
	int rectot;	/* number of records used since system boot */
	int filtot;	/* number of file headers used since system boot */
	udecl_simple_lock_data(, flckinfo_lock)
};

#ifdef	_KERNEL

extern struct flckinfo	flckinfo;

/*  Lock classes, determines how they are treated when they are unlocked. */
#define FILE_LOCK       0       /* Generic class no special treatment */
#define IO_LOCK         1       /* Indicates I/O waiting to complete */
#define LOCKMGR         2       /* Indicates lock manager lock */

udecl_simple_lock_info(extern, flckinfo_lockinfo)
#define	FLCKINFO_LOCK(f)	usimple_lock(&(f)->flckinfo_lock)
#define	FLCKINFO_UNLOCK(f)	usimple_unlock(&(f)->flckinfo_lock)
#define	FLCKINFO_LOCKINIT(f)	usimple_lock_setup(&(f)->flckinfo_lock,\
						   flckinfo_lockinfo)

udecl_simple_lock_info(extern, flino_lockinfo)
#define	FLINO_LOCK(f)		usimple_lock(&(f)->flino_lock)
#define	FLINO_UNLOCK(f)		usimple_unlock(&(f)->flino_lock)
#define	FLINO_LOCKINIT(f)	usimple_lock_setup(&(f)->flino_lock, \
						   flino_lockinfo)
extern struct lockinfo *fichain_lockinfo;

extern void             lock_write_nonfifo(lock_t);
extern void             lock_done_nonfifo(lock_t);

#define	FICHAIN_LOCKINIT(l)	lock_setup(&(l)->fichain_lock,\
					   fichain_lockinfo, TRUE)
#define FICHAIN_LOCK(l)         lock_write_nonfifo(&(l)->fichain_lock)
#define FICHAIN_UNLOCK(l)       lock_done_nonfifo(&(l)->fichain_lock)
#define	FICHAIN_LOCK_HOLDER(l)	LOCK_HOLDER(&(l)->fichain_lock)


udecl_simple_lock_data(extern, fids_lock)
#define	FIDS_LOCK()		usimple_lock(&fids_lock)
#define	FIDS_UNLOCK()		usimple_unlock(&fids_lock)

extern struct flino sleeplcks;
#define SLEEPLCK_LOCK()		lock_write_nonfifo(&sleeplcks.fichain_lock)
#define SLEEPLCK_UNLOCK()	lock_done_nonfifo(&sleeplcks.fichain_lock)
#define SLEEPLCK_LOCK_HOLDER()	LOCK_HOLDER(&sleeplcks.fichain_lock) 

extern struct flino grantlcks;					
#define GRANTLCK_LOCK()		lock_write_nonfifo(&grantlcks.fichain_lock)
#define GRANTLCK_UNLOCK()	lock_done_nonfifo(&grantlcks.fichain_lock)
#define GRANTLCK_LOCK_HOLDER()	LOCK_HOLDER(&grantlcks.fichain_lock)

extern struct flino klmlcks;
#define KLMLCK_LOCK()		lock_write_nonfifo(&klmlcks.fichain_lock)
#define KLMLCK_UNLOCK()		lock_done_nonfifo(&klmlcks.fichain_lock)
#define KLMLCK_LOCK_HOLDER()	LOCK_HOLDER(&klmlcks.fichain_lock)

#endif	/* _KERNEL */

#define GRANT_LOCK_FLAG 0xf             /* flag in eld.l_xxx */

#ifdef __cplusplus
}
#endif
#endif	/* _SYS_FLOCK_H */
