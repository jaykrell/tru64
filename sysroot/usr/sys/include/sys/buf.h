/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: buf.h,v $
 * Revision 4.3.106.2  2004/10/06  17:05:32  David_Schroeder
 * 	Add BH_FAIL_FAST and BH_FAIL_RETRY defines for LSM fast fail project.
 *
 * Revision 4.3.106.1  2003/06/05  14:45:56  Keith_Comeford
 * 	Add nostrategy prototype, this is recovering a fix from srequest
 *      wildcatos-846-pelle to fix QAR 84400
 *
 * Revision 4.3.90.1  2001/09/20  21:23:38  Anthony_Zlotek
 * 	Add B_RECYCLING (by overloading B_BAD) for use when recycling
 * 	CFS vnodes.
 *
 * Revision 4.3.79.2  2000/10/18  12:49:40  James_Woodward
 * 	Add BX_CDEV to avoid bdev lookup in IO map layer
 *
 * Revision 4.3.79.1  2000/07/18  18:22:36  Anton_Verhulst
 * 	Replace u_int with uint_t to fix compile errors with _XOPEN_SOURCE.
 * 
 * Revision 4.3.68.6  2000/01/21  22:12:49  William_Dallas
 * Merge Information
 *     Merge Revision:  ZULUOS:4.3.68.5
 *     User  Revision:  William_Dallas_zulu_br:4.3.72.1
 *    Common Ancestor:  4.3.68.4
 * 	[2000/01/21  22:12:14  William_Dallas]
 * 	Added semi-colan to reserved area of struct buf to fix warnings.
 * 	[2000/01/21  20:43:41  William_Dallas]
 * 
 * Revision 4.3.68.4  2000/01/13  19:31:04  William_Dallas
 * 	Added storgage in struct buf for I/O Stats (Feed back for file systems),
 * 	added drv_handle storage and padded out to next memory bucket.
 * 
 * Revision 4.3.68.3  1999/12/15  19:21:41  John_Steinman
 * 	Re-casted struct buf element b_lblkno and b_blkno to daddr64_t
 * 	to support future 64 bit block addressing.
 * 
 * Revision 4.3.68.2  1999/08/16  20:09:38  Bill_Rowell
 * 	QAR 63843
 * 	Changed the type of bhd_stamp from u_long to ulong_t.
 * 	u_long is not supported by POSIX standard.
 * 	[1999/08/16  20:09:21  Bill_Rowell]
 * 
 * Revision 4.3.31.18  1999/03/26  21:58:41  Ernie_Petrides
 * 	Change clrbuf() macro to use bzero().
 * 	[1999/03/26  04:24:19  Ernie_Petrides]
 * 
 * Revision 4.3.31.17  1999/03/02  17:42:50  Andrew_Duane
 * 	Merge from PTFCOS_BL5.
 * 	[1999/03/02  17:38:52  Andrew_Duane]
 * 
 * Revision 4.3.31.16  1999/01/27  19:31:19  Bob_Harris
 * 	Remove directio_offset from the buf structure.
 * 	[1999/01/22  20:08:03  Bob_Harris]
 * 	QAR 67535
 * 	Add a #define to associate b_directio_offset with the buf structure
 * 	b_driver_un_1.directio_offset field.  We needed a way to pass the
 * 	Direct I/O byte offset to the msfs_strategy() routine so that the
 * 	uio.uio_offset could be properly initialized.
 * 	b_driver_un_1 was not being used by the Direct I/O strategy routine
 * 	and it was 64 bits wide, so it made an ideal place to stuff the
 * 	uio_offset value.
 * 	[1999/01/20  21:01:29  Bob_Harris]
 * 
 * Revision 4.3.61.3  1999/01/14  17:42:26  John_Meneghini
 * 	Bug fix QAR 66941 - backport steelos B_XFLAGS mechanism
 * 	[1999/01/13  19:55:51  John_Meneghini]
 * 
 * Revision 4.3.61.2  1998/08/26  20:58:30  John_Meneghini
 * 	EEI support: added b_eei field to bp.
 * 	[1998/08/24  18:52:27  John_Meneghini]
 * 
 * Revision 4.3.31.15  1998/08/18  21:02:25  Per_Wahlstrom
 * 	Add BX_LAYERED_IO flag for clusters
 * 	[1998/06/18  21:19:58  Per_Wahlstrom]
 * 
 * Revision 4.3.31.14  1998/03/10  23:52:08  Diane_Lebel
 * 	Replaced B_WRITEV (unused) with B_JUSTFLUSH for CFS.
 * 	[1998/03/10  23:50:44  Diane_Lebel]
 * 
 * Revision 4.3.31.13  1998/02/10  20:53:29  David_Gagne
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	4.3.31.11 **
 * 		** Merge revision:	4.3.31.12 **
 * 	 	** End **
 * 	Add fields and flag bits to the buf structure to support
 * 	dev_t restoration.
 * 	[1998/02/06  22:08:31  David_Gagne]
 * 
 * Revision 4.3.31.12  1998/02/10  19:18:39  Janice_Chang
 * 	Use only one b_hint for all AdvFS metadata.  QAR 58113.
 * 	[1998/02/09  15:00:04  Janice_Chang]
 * 
 * Revision 4.3.31.11  1997/12/09  14:44:39  Jim_Beltz
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rSTEELOS;PTCOS_BL11;<> **
 * 		** Ancestor revision:	4.3.31.9 **
 * 		** Merge revision:	4.3.31.10 **
 * 	 	** End **
 * 	[1997/12/02  14:00:42  Jim_Beltz]
 * 	Back out the change for qar 55951: Remove define for B_SAME_VOP.
 * 	[1997/11/12  20:43:17  Jim_Beltz]
 * 
 * Revision 4.3.31.10  1997/12/01  19:29:19  Mike_Milicia
 * 	Restructure getnewvnode/vgone to handle failures of recycle attempts
 * 	[1997/12/01  19:13:21  Mike_Milicia]
 * 
 * Revision 4.3.35.5  1997/11/11  16:47:19  Jim_Beltz
 * 	Back out the change for qar 55951: Remove define for B_SAME_VOP.
 * 	(qar 55656).
 * 	[1997/11/10  15:06:28  Jim_Beltz]
 * 
 * Revision 4.3.35.4  1997/09/29  21:09:43  Janice_Chang
 * 	Add BH_ADVFS_METADATA hint for caching AdvFS metadata only
 * 	to presto.  Backport of steel prmetaonly work.
 * 	[1997/09/25  19:33:34  Janice_Chang]
 * 
 * Revision 4.3.31.9  1997/09/04  19:30:21  James_Woodward
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL6:PTCOS_BL10 **
 * 		** Ancestor revision:	4.3.35.2 **
 * 		** Merge revision:	4.3.35.3 **
 * 	 	** End **
 * 	merge of PTmin BL10 changes
 * 	[1997/09/04  13:42:44  James_Woodward]
 * 
 * Revision 4.3.31.8  1997/08/15  21:09:29  Janice_Chang
 * 	Added b_hints values for AdvFS metadata files.
 * 	[1997/08/11  14:56:36  Janice_Chang]
 * 
 * Revision 4.3.35.3  1997/07/29  16:53:34  Janice_Chang
 * 	Added B_SAME_VOP define for use with ubc_page_alloc()
 * 	and msfs_putpage().
 * 	[1997/07/24  21:56:47  Janice_Chang]
 * 
 * Revision 4.3.31.7  1997/06/18  15:37:01  Dave_King
 * 	Added new B_DATAONLY flag to match IO_DATAONLY flag.
 * 	[1997/06/02  15:59:35  Dave_King]
 * 
 * Revision 4.3.31.6  1997/03/03  15:40:26  Robin_Miller
 * 	Added function prototypes.
 * 	[1997/03/03  15:09:15  Robin_Miller]
 * 
 * Revision 4.3.31.5  1997/02/19  19:01:39  Carolyn_Briglia
 * 	EEI (Extended Error Information) added b_eei member to struct buf
 * 	[1997/02/12  20:08:09  Carolyn_Briglia]
 * 
 * Revision 4.3.31.4  1997/02/07  21:47:41  John_Flanagan
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rPTCOS_BL4 **
 * 		** Ancestor revision:	4.3.24.4 **
 * 		** Merge revision:	4.3.35.2 **
 * 	 	** End **
 * 	Pull in PTmin BL4 version needed for merge
 * 	[1997/02/07  21:46:13  John_Flanagan]
 * 
 * Revision 4.3.35.2  1997/01/24  19:52:04  Jan_Reimers
 * 	Added B_SGIO flag to b_flags
 * 	[1997/01/13  21:40:06  Jan_Reimers]
 * 
 * Revision 4.3.31.2  1996/05/01  14:34:52  Larry_Woodman
 * 	Merge brom bravos.bl2
 * 	[1996/05/01  14:27:12  Larry_Woodman]
 * 
 * Revision 4.3.27.2  1995/10/25  19:59:57  Ray_Lanza
 * 	Initial __alpha conditional evaluation and changes
 * 	[1995/10/25  19:29:38  Ray_Lanza]
 * 
 * Revision 4.3.24.4  1995/01/25  18:50:51  Thomas_Peterson
 * 	Added extern "C" block around header for C++.  Added several
 * 	#include's and forward struct declarations to make header
 * 	self-describing.
 * 	[1995/01/17  21:10:45  Thomas_Peterson]
 * 
 * Revision 4.3.22.2  1994/09/12  17:33:18  Chet_Juszczak
 * 	Add struct buf b_hints member.
 * 	[1994/09/12  14:16:23  Chet_Juszczak]
 * 
 * Revision 4.3.11.9  1994/04/25  18:16:59  Timothy_Burke
 * 	Merged to nightly.
 * 	[1994/04/22  18:14:09  Timothy_Burke]
 * 	Added B_ACTIVE to b_flags field.
 * 	[1994/04/12  18:06:19  Timothy_Burke]
 * 
 * Revision 4.3.11.8  1994/04/16  02:44:09  Paula_Long
 * 	Updated locks to use lockinfo,(still no heirarchy or spl checking)
 * 	[1994/04/10  23:39:42  Paula_Long]
 * 
 * Revision 4.3.11.7  1994/01/07  18:27:54  Thomas_Peterson
 * 	Merge of C++ specific changes forward from Sterling BL9 to Gold BL8.
 * 	Revision 4.3.13.3  1993/12/15  22:11:37  Thomas_Peterson
 * 	   Added extern "C" blocks around function decls as required for C++.
 * 	   [1993/12/13  16:27:51  Thomas_Peterson]
 * 	[1994/01/03  20:19:09  Thomas_Peterson]
 * 
 * Revision 4.3.11.6  1993/12/01  20:20:08  Ernie_Petrides
 * 	Make BUF_GIVE_AWAY() and BUF_ACCEPT() independent of MACH_LDEBUG.
 * 	[1993/12/01  18:53:27  Ernie_Petrides]
 * 
 * Revision 4.3.11.5  1993/11/23  14:36:53  Timothy_Burke
 * 	Added BUF_LOCK_TERMINATE.
 * 	[1993/11/22  15:04:02  Timothy_Burke]
 * 
 * Revision 4.3.11.4  1993/09/09  19:32:58  Stan_Luke
 * 	pre-merge Sterling.
 * 	[1993/09/09  19:21:11  Stan_Luke]
 * 
 * Revision 4.3.11.3  1993/06/21  23:18:34  Ernie_Petrides
 * 	Rework references to obsolete lock fields.
 * 	[1993/06/21  22:15:28  Ernie_Petrides]
 * 
 * Revision 4.3.13.2  1993/05/21  20:40:43  Mark_Parenti
 * 	Add new fields for DDI/DKI compatibility.
 * 	[1993/05/21  20:31:25  Mark_Parenti]
 * 
 * Revision 4.3.11.2  1993/04/28  23:53:38  Paula_Long
 * 	submitting the SMP project
 * 	[1993/04/28  18:31:37  Paula_Long]
 * 
 * Revision 4.3.8.3  1993/03/26  18:43:49  Stan_Luke
 * 	OSF/1.2 and SMP merge-up of vfs:  slight mod to BUFHASH macro.
 * 	[1993/03/26  18:41:49  Stan_Luke]
 * 	Temporarily removed extern dcl for minphys, physio and biodone;
 * 	     because of mismatch.
 * 	[1993/03/04  21:44:04  Stan_Luke]
 * 	SMP-osf/1.2 merge-up for vfs:  buffer hash algorithm slightly modified.
 * 	[1993/03/04  14:19:01  Stan_Luke]
 * 
 * Revision 4.3.8.2  1993/03/26  12:14:04  James_Woodward
 * 	first cut at rt+MP
 * 	[1993/03/25  20:25:15  James_Woodward]
 * 
 * Revision 4.3.4.3  92/09/11  17:31:37  Anton_Verhulst
 * 	Cnage nbuf and bufpages to longs.
 * 	[92/09/11  17:22:08  Anton_Verhulst]
 * 
 * Revision 4.3.4.2  92/03/18  22:24:47  Shashi_Mangalat
 * 	Merged in Silver BL5
 * 	UBC merge. [Charles_Briggs]
 * 	[92/03/18  22:04:06  Shashi_Mangalat]
 * 
 * Revision 4.3  92/01/15  02:09:23  devbld_gsf
 * 	Baselevel alpha_bl002
 * 
 * Revision 4.2.2.2  91/12/07  16:49:16  Jay_Estabrook
 * 	merge ALPHA to SILVER via ODE
 * 	[91/12/07  16:21:46  Jay_Estabrook]
 * 
 * Revision 4.2  91/09/19  22:56:43  devbld
 * 	Adding ODE Headers
 * 
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: buf.h,v $ $Revision: 4.3.106.2 $ (DEC) $Date: 2004/10/06 17:05:32 $
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
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *

 */
/*
 *	sys/buf.h
 *
 *	Revision History:
 *
 * 6-Apr-91	Ron Widyono
 *	Buffer lock handoff scheme needs RT_PREEMPT case to keep lock counts
 *	consistent and valid.
 *
 */

#ifndef	_SYS_BUF_H_
#define _SYS_BUF_H_
#ifdef __cplusplus
extern "C" {
#endif

#ifdef	_KERNEL
#include <rt_preempt.h>
#endif

#include <sys/types.h>
#include <s5fs/s5ino.h>
#include <sys/filsys.h>
#ifdef	_KERNEL
#include <sys/unix_defs.h>
#include <kern/event.h>
#include <kern/lock.h>
#endif

/*
 * The header for buffers in the buffer pool and otherwise used
 * to describe a block i/o request is given here.  The routines
 * which manipulate these things are given in vfs/vfs_bio.c.
 *
 * Each buffer in the pool is usually doubly linked into 2 lists:
 * hashed into a chain by <vnode,blkno> so it can be located in the cache,
 * and (usually) on (one of several) queues.  These lists are circular and
 * doubly linked for easy removal.
 *
 * There are currently three queues for buffers:
 *	one for buffers which must be kept permanently (super blocks)
 * 	one for buffers containing ``useful'' information (the cache)
 *	one for buffers containing ``non-useful'' information
 *		(and empty buffers, pushed onto the front)
 * The latter two queues contain the buffers which are available for
 * reallocation, are kept in lru order.  When not on one of these queues,
 * the buffers are ``checked out'' to drivers which use the available list
 * pointers to keep track of them in their i/o active queues.
 */

/* forward declarations required for C++ */
#ifdef __cplusplus
struct buf;
struct fs;
struct csum;
struct cg;
struct dinode;
struct proc;
struct vm_page;
struct vnode;
struct ucred;
#endif

/*
 * Bufhd structures used at the head of the hashed buffer queues.
 * We only need three words for these, so this abbreviated
 * definition saves some space.
 */
struct bufhd
{
	int	b_flags;		/* see defines below */
	struct	buf *b_forw, *b_back;	/* fwd/bkwd pointer in chain */
	ulong_t	bhd_stamp;		/* time stamp for hash chain */
#ifdef	_KERNEL
	udecl_simple_lock_data(,bhd_lock) /* hash chain spin lock */
#endif
};

struct b_iostats {
	uint_t	devqlen;		/* Maintained by caller */
	uint_t	acttime;		/* Number of usecs I/O active */
	uint_t	pendtime;		/* Number of usecs I/O inactive */
					/* Note total outstanding time is
					   acttime + pendtime */
	uint_t	flags;			/* Flags (e.g.,request priority boost) */
	uint_t	reserved1[4];		/* RESERVED for future stats */
};

/* b_iostats.flags defines */
#define	I_O_BOOST		0x1	/* Try to give request a boost */

struct buf
{
	int	b_flags;		/* too much goes here to describe */
	int	b_hints;		/* Hints for pseudo devices */
	struct	buf *b_forw, *b_back;	/* hash chain (2 way street) */
	struct	buf *av_forw, *av_back;	/* position on free list if not BUSY */
	struct	buf *b_blockf, **b_blockb;/* associated vnode */
#define	b_actf	av_forw			/* alternate names for driver queue */
#define	b_actl	av_back			/*    head - isn't history wonderful */
	int	b_bcount;		/* transfer count */
#define	b_active b_bcount		/* driver queue head: drive active */
	int	b_bufsize;		/* size of allocated buffer */
#define	b_pager	b_bufsize
	short	b_error;		/* returned after I/O */
	short	b_eei;			/* returned after I/O */
	dev_t	b_dev;			/* major+minor device name */
#define	b_edev  b_dev			/* SVR4 name for 32 bit major&minor */
	union {
	    caddr_t b_addr;		/* low order core address */
	    int	*b_words;		/* words for clearing */
	    struct fs *b_fs;		/* superblocks */
	    struct filsys *b_s5fs;      /* System V fs suberblock */
	    struct csum *b_cs;		/* superblock summary information */
	    struct cg *b_cg;		/* cylinder group block */
	    struct dinode *b_dino;	/* ilist */
	    struct s5dinode *b_s5dino;	/* s5 ilist */
	    daddr_t *b_daddr;		/* indirect block */
	} b_un;
	daddr64_t	b_lblkno;	/* logical block number */
	daddr64_t	b_blkno;	/* block # on device */
	int	b_resid;		/* words not transferred after error */
#define b_errcnt b_resid		/* while i/o in progress: # retries */
#define	b_cylin	b_resid			/* while on disk q: cylinder #	*/
	struct  proc *b_proc;		/* proc doing physical or swap I/O */
	struct 	buf *b_hash_chain;	/* head of hash chain owning buffer */
	void	(*b_iodone)(struct buf *); /* function called by iodone */
	struct	vm_page *b_pagelist;	/* pages associated with buffer */
	struct	vnode *b_vp;		/* vnode for dev */
	struct	vnode *b_rvp;		/* vnode buffer is associated with */
	struct	ucred *b_rcred;		/* ref to read credentials */
	struct	ucred *b_wcred;		/* ref to write credendtials */
	int	b_dirtyoff;		/* offset in buffer of dirty region */
	int	b_dirtyend;		/* offset of end of dirty region */
	union	{	/* these fields reserved _solely_ for device driver */
		long	longvalue;
		void	*pointvalue;
		daddr_t	diskaddr;
		time_t	timevalue;
	} b_driver_un_1, b_driver_un_2;
#ifdef	_KERNEL
/* 
 * 	DDI/DKI compatibility
 */
	unsigned long	b_reltime;	/* Previous release time */
	char		b_oerror;	/* Old one byte I/O error code */
	short		b_xflags;	/* extended flags field (16 bits),
					   valid only if B_XFLAGS is set in
					   b_flags */
	dev_t		b_orig_dev;	/* original devt, restore in biodone,
					   valid only if BX_RESTORE_DEV is
					   set */
	lock_data_t	b_lock;		/* mutual exclusion buffer lock */
	event_t	b_iocomplete;		/* guard vnode while i/o in progress */
	void *b_drv_handle; 		/* Driver handle obtained from under
					   laying dev driver extracted from
					   vnode */
	struct b_iostats b_iostats;	/* Driver times for I/O	*/
	u_char		reserved_pad[120]; /* Reserved for future expansion */
#endif
};

/* values of b_hints */

#define BH_REG_DATA	0x1
#define BH_DIRECTORY 	0x2
#define BH_INODE	0x4
#define BH_INDIRECT	0x8
#define BH_ADVFS_METADATA 0x10
#define BH_FAIL_FAST    0x20
#define BH_FAIL_RETRY   0x40


/*
 * Following #ifdefs/#defines are for compatibility with other naming schemes
 * long-term, they should be moved into the driver(s) that use them.
 */
#ifdef __digital__
	/* SCSI command in progress */
	/* The fields below are just aliases */
#define b_command	b_driver_un_1.longvalue
#define b_gid		b_driver_un_1.longvalue
#endif

#ifdef exl
	/* added the missing fields for System V driver (SCSI) --- csy */
        /* physical sector of disk request */
#define b_sector	b_driver_un_1.diskaddr
	/* request start time */
#define b_start		b_driver_un_2.timevalue
#endif

#define BQUEUES		4		/* number of free buffer queues */

#define BQ_LOCKED	0		/* super-blocks &c */
#define BQ_LRU		1		/* lru, useful buffers */
#define BQ_AGE		2		/* rubbish */
#define BQ_EMPTY	3		/* buffer headers with no memory */

#define	MINBUFHSZ	16		/* minimum size of bufhash */

#ifdef	_KERNEL
extern int	bufhsz;			/* size of buffer cache hash table */
#define RND		(MAXBSIZE/DEV_BSIZE)
#define BBITS(bn)	((unsigned int)(bn) / RND)
#define VBITS(vp)	((unsigned int)(vp) >> 9)
#define BUFHASH(dvp, dblkno)	\
	((struct buf *)&bufhash[(VBITS(dvp)+BBITS(dblkno))&(bufhsz-1)])

extern struct	buf *buf;	/* the buffer pool itself */
extern char	*buffers;
extern long	nbuf;		/* number of buffer headers */
extern long	bufpages;	/* number of memory pages in the buffer pool */

extern struct	bufhd *bufhash;		/* heads of hash lists */
extern struct	buf bfreelist[BQUEUES];	/* heads of available lists */

#if defined(_USE_KERNEL_PROTOS)

#include <sys/uio.h>

extern struct buf *getblk(struct vnode *vp, daddr64_t blkno, int size);
extern struct buf *geteblk(int size);
extern struct buf *getnewbuf(void);

extern void biodone(struct buf *bp);
extern int biowait(struct buf *bp);
extern void bioreset(struct buf *bp);
extern void minphys(struct buf *bp);
extern int physio(void (*strat)(struct buf *bp),
			struct buf *bp,
			dev_t dev, int rw,
			void (*mincnt)(struct buf *bp),
			struct uio *uio);
extern int nostrategy(struct buf *);

#else /* !defined(_USE_KERNEL_PROTOS) */

extern struct buf *getblk();
extern struct buf *geteblk();
extern struct buf *getnewbuf();
extern unsigned minphys();
extern int nostrategy();

#endif /* defined(_USE_KERNEL_PROTOS) */
#endif	/* _KERNEL */

/*
 * These flags are kept in b_flags.
 *
 * NOTE:
 *	The following flags are provided purely for backward 
 *	compatibility with code (drivers, mostly) that
 *	expect them to be around.  We'd like them to go away:
 *		B_BUSY, B_DONE, B_WANTED
 */
#define B_WRITE		0x00000000	/* non-read pseudo-flag */
#define B_READ		0x00000001	/* read when I/O occurs */
#define B_ERROR		0x00000002	/* transaction aborted */
#define B_BUSY		0x00000004	/* not on av_forw/back list */
#define B_PHYS		0x00000008	/* physical IO */
#define B_WANTED	0x00000010	/* issue wakeup when BUSY goes off */
#define B_AGE		0x00000020	/* delayed write for correct aging */
#define B_ASYNC		0x00000040	/* don't wait for I/O completion */
#define B_DELWRI	0x00000080	/* write at exit of avail list */
#define B_TAPE		0x00000100	/* this is a magtape (no bdwrite) */
#define B_REMAPPED	0x00000200	/* for bp_mapin and bp_mapout */
#define	B_FREE		0x00000400	/* used by ubc to free page */
#define	B_SWAP		0x00000800	/* swap I/O */
#define	B_UBC		0x00001000	/* UBC I/O */
#define	B_DIRTY		0x00002000	/* UBC has page marked dirty */
#define	B_DONE		0x00004000	/* Done with I/O */
#define B_CACHE		0x00008000	/* did bread find us in the cache ? */
#define B_INVAL		0x00010000	/* does not contain valid info  */
#define B_LOCKED	0x00020000	/* locked in core (not reusable) */
#define B_HEAD		0x00040000	/* a buffer header, not a buffer */
#define B_USELESS	0x00080000	/* cache, but at low priority */
#define B_BAD		0x00100000	/* bad block revectoring in progress */
#define B_XFLAGS	0x00200000	/* b_xflags field is valid */
#define	B_RAW		0x00400000	/* set by physio for raw transfers */
#define	B_NOCACHE	0x00800000	/* do not cache block after use */
#define	B_CHKERRORS	0x01000000	/* error if flush cannot be done 
					   successfully without blocking */
#define	B_JUSTFLUSH     0x02000000	/* just flush to server - used by CFS */
#define	B_HWRELOC	0x04000000	/* relocate/rewrite block */
#define B_WANTFREE	0x08000000	/* want buffer from freelist */
#define	B_MSYNC		0x10000000	/* mmap msync request */
#define B_ACTIVE	0x20000000	/* driver specific flag */
#define B_SGIO		0x40000000	/* scatter/gather IO flag */
#define B_DATAONLY	0x80000000	/* synchronously write data(IO_DATAONLY) */

/*
 * OSF/1 has defined flags for both the b_flags of the buf structure
 * and d_flags of the bdevsw structure (e.g. B_TAPE) in this include file.
 * Follow tradition and put bdevsw flag indicating driver uses DDI/DKI
 * standard here.
*/

#define B_DDIDKI	0x20000000	

/*
 * Flag used by CFS to detect vnode recycling by getnewvnode()
 */
#define B_RECYCLING	B_BAD

#define	BUF_NULL	(struct buf *)0
#define BHASH_NULL	(struct buf *)0

/*
 * These flags are kept in b_xflags.
 *
 * NOTE:
 *	The b_xflags field is only valid if the B_XFLAGS bit is set in the
 *	b_flags field.
 */
#define BX_RESTORE_DEV	0x00000001	/* restore the b_dev field from the
					   b_orig_dev field in biodone */
#define BX_LAYERED_IO   0x00000002      /* Call b_iodone routine very early
					 * in biodone routine.
					 * Bit used in e.g. clusters.
					 */
#define BX_CDEV		0x00000004	/* do cdev look-up at map layer */

#ifdef	_KERNEL
#include <kern/macro_help.h>

/*
 * Insq/Remq for the buffer hash lists.
 */
#define	bremhash(bp) \
MACRO_BEGIN \
	(bp)->b_back->b_forw = (bp)->b_forw; \
	(bp)->b_forw->b_back = (bp)->b_back; \
	(bp)->b_hash_chain = BHASH_NULL; \
MACRO_END
#define	binshash(bp, dp) \
MACRO_BEGIN \
	(bp)->b_forw = (dp)->b_forw; \
	(bp)->b_back = (dp); \
	(bp)->b_hash_chain = (dp); \
	(dp)->b_forw->b_back = (bp); \
	(dp)->b_forw = (bp); \
	(BHASH_STAMP(dp))++; \
MACRO_END

/*
 * Insq/Remq for the buffer free lists.
 */

#define bremfree(bp)						\
MACRO_BEGIN							\
	(bp)->av_back->av_forw = (bp)->av_forw;			\
	(bp)->av_forw->av_back = (bp)->av_back;			\
	(bp)->av_forw = NULL;					\
	(bp)->av_back = NULL;					\
MACRO_END

#define binsheadfree(bp, dp)					\
MACRO_BEGIN							\
	(dp)->av_forw->av_back = (bp);				\
	(bp)->av_forw = (dp)->av_forw;				\
	(dp)->av_forw = (bp);					\
	(bp)->av_back = (dp);					\
MACRO_END

#define binstailfree(bp, dp)					\
MACRO_BEGIN							\
	(dp)->av_back->av_forw = (bp);				\
	(bp)->av_back = (dp)->av_back;				\
	(dp)->av_back = (bp);					\
	(bp)->av_forw = (dp);					\
MACRO_END

#define iodone	biodone
#define iowait	biowait

/*
 * Zero out a buffer's data portion.
 */
#define clrbuf(bp)						\
MACRO_BEGIN							\
	bzero((bp)->b_un.b_addr, (size_t)(bp)->b_bcount);	\
	(bp)->b_resid = 0;					\
MACRO_END
#define B_CLRBUF	0x1	/* request allocated buffer be cleared */
#define B_SYNC		0x2	/* do all allocations synchronously */

typedef struct bufhd bufhd_t;

/*
 * There are a couple of places outside of the buffer cache code
 * (in ../vfs/vfs_bio.c) that use buffer locks, and many places
 * that make assertions about the states of buffer locks, so these
 * definitions must be public.
 */

extern struct lockinfo *buf_lockinfo;
#define BUF_LOCKINIT(bp)	lock_setup(&(bp)->b_lock, buf_lockinfo, TRUE)
#define BUF_LOCK_TERMINATE(bp)	lock_terminate(&(bp)->b_lock)

#define	BUF_LOCK(bp)						\
MACRO_BEGIN							\
	int s = splbio();					\
	lock_write(&(bp)->b_lock);				\
	(bp)->b_flags |= B_BUSY;				\
	splx(s);						\
MACRO_END

#define	BUF_UNLOCK(bp)						\
MACRO_BEGIN							\
	int s = splbio();					\
	(bp)->b_flags &= ~B_BUSY;				\
	lock_write_done(&(bp)->b_lock);				\
	splx(s);						\
MACRO_END

#define BUF_LOCK_TRY(bp, ret)					\
MACRO_BEGIN							\
	int s = splbio();					\
	if (ret = lock_try_write(&(bp)->b_lock)) 		\
		(bp)->b_flags |= B_BUSY;			\
	splx(s);						\
MACRO_END

/*
 * Note: be careful using the macro BUF_LOCKED(), which will indicate
 * if the lock is currently locked by any thread.  Specifically, it
 * does not indicate whether the current thread is the lock holder.
 */
#define	BUF_LOCKED(bp)	(LOCK_LOCKED(&(bp)->b_lock))

/*
 * Asynchronous I/O presents problems for the lock checking package.
 * The sequence of events is:
 *	fetch the buffer, locking it
 *	start the I/O
 *	current thread goes about its business
 *	an innocent victim thread inherits the buffer in interrupt
 *		context and brelse's it during I/O completion,
 *		releasing the buffer's lock.
 *
 * Convincing the lock checking package not to complain during
 * this process is a bit tricky.  Here are some of the problems.
 *
 * Failing to give away ownership of the buffer lock when
 * issuing the I/O request causes problems should the current
 * thread at some future time issue another request for the
 * same buffer it originally asked to read-ahead.  The lock
 * checking package will complain about a deadlock. (waiting for self)
 *
 * The solution requires two steps.  The thread initiating the I/O
 * gives the ownership of the lock away to a fake thread, biodone_ldebug.
 * The 'thread' that receives the buffer accepts the ownership of the lock
 * to itself, using BUF_ACCEPT.
 *
 * This scheme eliminates races in the ownership handoff, but strategy
 * routines are no longer allowed to assert that they own asynchronous
 * I/O buffers. They can assert that the buffer is locked, that they
 * own synchronous buffers, or that the "fake thread" owns asynchronous
 * buffers.
 */

extern char biodone_ldebug;

#define	BUF_LOCK_THREAD(bp)	(LOCK_THREAD(&(bp)->b_lock))
#define	BUF_LOCK_OWNER(bp)	(LOCK_OWNER(&(bp)->b_lock))
#define	BUF_LOCK_HOLDER(bp)	(LOCK_HOLDER(&(bp)->b_lock))
#define BUF_IS_LOCKED(bp)	(!LOCK_READERS(&(bp)->b_lock) && \
				 LOCK_LOCKED(&(bp)->b_lock))
/*
 * BUF_GIVE_AWAY(bp): give away ownership of an asynchronous
 * I/O request buffer.
 */
#define	BUF_GIVE_AWAY(bp)					\
MACRO_BEGIN							\
	if (check_locks) {					\
		int s = splbio();				\
		LOCK_DISOWN(&(bp)->b_lock, (struct thread *)&biodone_ldebug);\
		splx(s);					\
	}							\
MACRO_END

/*
 * BUF_ACCEPT(bp): accept an asynchronous I/O buffer that was
 * previously given away.
 */
#define	BUF_ACCEPT(bp)						\
MACRO_BEGIN							\
	if (check_locks) {					\
		int s = splbio();				\
		LOCK_ADOPT(&(bp)->b_lock, (struct thread *)&biodone_ldebug);\
		splx(s);					\
	}							\
MACRO_END

#endif	/* _KERNEL */
#ifdef __cplusplus
}
#endif
#endif	/* _SYS_BUF_H_ */


