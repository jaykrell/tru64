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
 * @(#)$RCSfile: dvdfsnode.h,v $ $Revision: 1.1.7.2 $ (DEC) $Date: 2000/02/10 18:08:04 $
 */
/*
 * The dvdnode is the dvdfs equivalent to ufs's inode. Any similarity
 * is purely coincidental.
 * There is a unique dvdnode allocated for each active file,
 * each current directory, each mounted-on file, text file, and the root.
 * A dvdnode is 'named' by its dev and unique number. (dvdget/dvdfs_node.c)
 */

/*
 * Since the DVDFS is a read-only file system, almost everything
 * in the dvdnode structure is static once a node has been initialized.
 *
 * The one exception is dvd_rdev, which may change due to a device mapping
 * user request.  When a dvd_rdev changes, however, a node is vgone()d.  
 * Anybody holding it open will lose their access (all I/O will then go via 
 * dead_vnops).
 *
 * So, locking is fairly simple:  just hold a reference to the associated 
 * vnode to prevent the deactivation of a node, and you can read the fields
 * as you like.
 */

#ifndef _DVDFSNODE_H_
#define _DVDFSNODE_H_

#include <dvdfs/dvdfs.h>

struct dvdnumber {
	uint	        partstart;	/* start of partition */
	uint		offset;		/* offset (lbn) within partition */
	uint		dno;		/* partstart+offset (unique to fs) */
	ushort		partno;		/* partition number */
};

struct dvdextent {
	uint	        partstart;	/* start of partition */
	uint		offset;		/* offset w/in part of extent start */
	uint		dno;		/* partstart+offset (unique to fs) */
	uint		length;		/* length of extent */
	ushort		partno;		/* partition of extent */
	char		type;		/* ECMA 167 4/14.14.1.1 */
	char		spare[1];	/* to maintain alignment */
};

struct dvdnode {
	struct	dvdnode *dvd_chain[2];  /* hash chain, MUST be first */
	struct	dvdfs *dvd_fs;		/* file sys for this dvdnode */
	struct	vnode *dvd_vnode;	/* vnode associated with this node */
	struct	vnode *dvd_devvp;	/* vnode for block I/O */
	struct	dvdnumber dvd_number;
	u_long	dvd_infolen;		/* size in bytes of dir/file data */
	u_short dvd_flag;		/* copy of icbtag.flags */
	u_short	dvd_mode;		/* file mode and permissions */
	u_short dvd_nlink;
	uid_t   dvd_uid;
	gid_t   dvd_gid;
	time_t  dvd_atime;		/* time last accessed */
        time_t  dvd_mtime;		/* time last modified */
        time_t  dvd_ctime;		/* last time cdnode changed */
	int	dvd_gen;		/* is this uniqueid ? */
	dev_t	dvd_dev;		/* ? device where dvdnode resides */
	dev_t	dvd_rdev;		/* ? device node identity (mapped) */
	dev_t	dvd_ondiskrdev;		/* ? device node identity on disk */
#ifdef	_KERNEL
	lock_data_t	dvd_io_lock;	/* reading file's contents */
	event_t		dvd_iodone;	/* dvdnode is in transit from disk */
	udecl_simple_lock_data(,dvd_incore_lock)
#endif
        struct dvdextent *dvd_enext;    /* continue extents if overflow */
        int     dvd_ecnt;               /* number of extents in file */
        struct  dvdextent dvd_extent;   /* one per extent */
};

#define	dvd_forw		dvd_chain[0]
#define	dvd_back		dvd_chain[1]

/* flags */
#define	INACTIVATING	0x0800		/* dvdnode is being inactivated */
#define	INACTWAIT	0x1000		/* waiting for dvdnode inactivation */
#define	IREADERROR	0x2000		/* disk read for dvdnode failed */
#define	DVDNODE_BADVOL	0x4000		/* node is not on this volume */

/* file modes: bits match those in POSIX & BSD extension definitions */
#define DVDPERM         0000777         /* permission bits */
#define	DVDFMT		0170000		/* type of file */
#define	DVDFIFO		0010000		/* fifo (named pipe) */
#define	DVDFCHR		0020000		/* character special */
#define	DVDFDIR		0040000		/* directory */
#define	DVDFBLK		0060000		/* block special */
#define	DVDFREG		0100000		/* regular */
#define	DVDFLNK		0120000		/* symbolic link */

/* convert permissions (4/14.9.5) to standard mode */
#define DVDOWNER	0x0007		/* low three of low five bits  */
#define DVDGROUP	0x00e0		/* low three of middle five bits */
#define DVDOTHER	0x1c00		/* low three of high five bits */
#define DVD_PTOM(p)	(((p&DVDOTHER)>>4) | ((p&DVDGROUP)>>2) | (p&DVDOWNER))

#define DVD_ISBLK(m) (((m)&DVDFMT) == DVDFBLK)
#define DVD_ISCHR(m) (((m)&DVDFMT) == DVDFCHR)
#define DVD_ISLNK(m) (((m)&DVDFMT) == DVDFLNK)

#define	DVDREAD		0400		/* read, execute permissions */
#define	DVDEXEC		0100

/*
 * This overlays the fid structure (see mount.h)
 * We only get 8 bytes, so save the partno and offset
 * and build a dvdnumber from there.
 */
struct dvdfid {
      u_short dvdfid_len;     /* length of structure */
      u_short dvdfid_pad;     /* force long alignment */
      uint    dvdfid_offset;  /* offset within partition */
      u_short dvdfid_partno;  /* partition number */
      u_short dvdfid_reserved;
};

#ifdef	_KERNEL
#define DVDNODE_LBS(dvdnodep) 2048
/*
 * Convert between inode pointers and vnode pointers
 */

#define VTODVD(vp)	((struct dvdnode *)(vp)->v_data)
#define DVDTOV(dvdp)	((dvdp)->dvd_vnode)

udecl_simple_lock_info(extern, dvdfs_incore_lockinfo)
extern struct lockinfo *dvdfs_inio_lockinfo;

#define	IN_READ_LOCK(dnp)	lock_read(&(dnp)->dvd_io_lock)
#define	IN_READ_UNLOCK(dnp)	lock_read_done(&(dnp)->dvd_io_lock)
#define	IN_IO_LOCK_INIT(dnp)	lock_setup(&(dnp)->dvd_io_lock, \
					   dvdfs_inio_lockinfo, TRUE)
#define	IN_LOCK(dnp)		usimple_lock(&(dnp)->dvd_incore_lock)
#define	IN_UNLOCK(dnp)		usimple_unlock(&(dnp)->dvd_incore_lock)
#define	IN_LOCK_INIT(dnp)	usimple_lock_setup(&(dnp)->dvd_incore_lock, \
						   dvdfs_incore_lockinfo)


#endif

#endif

