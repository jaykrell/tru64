/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: rnode.h,v $
 * Revision 1.1.59.2  2003/08/27  19:46:11  Paul_Park
 * 	QAR 96719 [BCGML0JS3]:
 * 	Reuse redundant r_vnode to store long fileid.
 *
 * Revision 1.1.59.1  2002/10/11  18:30:20  Brett_Heath_Wlaz
 * Merge Information:  Non-Visual Merge: User specified tree v51asupportos.nightly
 *     User Revision:  wcalphaos_bl6:1.1.55.2 Local Ancestor: n/a
 *    Merge Revision:  v51asupportos_nightly:1.1.57.2
 *   Common Ancestor:  1.1.57.1
 * 	Merge up to v51asupport.nightly
 *
 * Revision 1.1.57.2  2002/08/07  15:29:12  Paul_Park
 * 	QAR 90064: Add RCOMMITTING and RCOMMITWAIT flags.
 * 
 * Revision 1.1.55.2  2001/12/19  21:02:17  Paul_Park
 * 	Forward port of wildcatos-229-werme:
 * 	Changes to handle some rnode union overlays and related
 * 	cache-friendly changes.  (QAR 83899)
 * 
 * Revision 1.1.55.1  2001/12/10  23:19:57  Paul_Park
 * 	Merge NFS client changes from wildcatos:
 * 	QAR 86314: Add RMMAPPED flag.
 * 
 * Revision 1.1.44.2  1999/08/18  23:32:57  Martin_Lund
 * 	Large I/O support for NFSV3 client.
 * 	[1999/08/18  20:52:41  Martin_Lund]
 * 
 * Revision 1.1.24.5  1999/03/16  10:00:31  John_Carr
 * 	Declare mntinfo tag.
 * 	[1999/03/11  19:00:02  John_Carr]
 * 
 * Revision 1.1.24.4  1998/03/20  20:01:13  Martin_Lund
 * 	Added readdir cookie verifier to rnode.  QAR 52177.
 * 	[1998/03/20  19:59:31  Martin_Lund]
 * 
 * Revision 1.1.24.3  1997/03/27  17:58:07  Eric_Werme
 * 	Add rnode cells to track atime and mtime updates to specfs and fifo
 * 	files.  QAR 51038
 * 	[1997/03/25  18:38:26  Eric_Werme]
 * 
 * Revision 1.1.24.2  1997/01/14  18:31:51  Martin_Lund
 * 	NFS client Steel scalability (st.nfs.003.client_scalability)
 * 	 - removed rnode_table_lock
 * 	[1997/01/13  16:02:05  Martin_Lund]
 * 
 * Revision 1.1.17.5  1995/12/16  23:46:59  Eric_Werme
 * 	Define function prototype for nfs3_getfattr3().  (QAR 37174)
 * 	[1995/12/16  23:25:33  Eric_Werme]
 * 
 * Revision 1.1.17.4  1995/09/22  21:09:13  Aju_John
 * 	Added r_lockcount field to keep
 * 	track of the locks on a rnode. Clear
 * 	RNOCACHE flag when the count drops
 * 	to zero. Fixes QAR 34958.
 * 	[1995/09/11  20:08:08  Aju_John]
 * 
 * Revision 1.1.17.3  1995/06/01  00:28:26  Diane_Lebel
 * 	Got rid of fields that are no longer used (r_owner and r_count).
 * 	Added complex lock r_rwlock to synchronize directory mods.
 * 	[1995/05/30  23:28:32  Diane_Lebel]
 * 
 * Revision 1.1.17.2  1995/04/28  20:14:57  Diane_Lebel
 * 	Added SMP locks.
 * 	[1995/04/27  23:07:36  Diane_Lebel]
 * 
 * Revision 1.1.13.2  1994/09/09  22:03:14  Diane_Lebel
 * 	Got rid of unused fields in rnode.
 * 	[1994/09/06  00:12:55  Diane_Lebel]
 * 	Fixed RLOCK macro.  Should be looking at thread address instead
 * 	of pid for identifying owner.
 * 	[1994/09/01  23:02:45  Diane_Lebel]
 * 
 * Revision 1.1.9.9  1994/04/25  18:16:55  Timothy_Burke
 * 	Cosmetically changed RLOCK.
 * 	[1994/04/15  20:48:11  Timothy_Burke]
 * 
 * Revision 1.1.9.8  1993/11/30  01:35:47  Diane_Lebel
 * 	Added write verifier and write verifier sequence number to rnode for
 * 	NFSv3 reliable async writes.
 * 	[1993/11/24  02:56:24  Diane_Lebel]
 * 
 * Revision 1.1.9.7  1993/09/14  22:46:59  Diane_Lebel
 * 	Added support for NFSv3.  Changed rnode and supporting macros.
 * 	Added access cache and Sun's new symlink cache.
 * 	[1993/09/13  04:06:42  Diane_Lebel]
 * 
 * Revision 1.1.9.6  1993/09/07  21:27:28  Eric_Werme
 * 	Convert nfsv2fh_t to filehandle_t for NFS V3 support.
 * 	[1993/09/07  20:47:17  Eric_Werme]
 * 
 * Revision 1.1.9.5  1993/08/27  20:45:39  James_Woodward
 * 	allocate proc/task/utask and thread/np_uthread together
 * 	[1993/08/25  11:54:48  James_Woodward]
 * 
 * Revision 1.1.9.4  1993/08/26  14:29:29  Timothy_Burke
 * 	Sterling to gold merge.
 * 	Revision 1.1.7.2  1993/03/30  22:28:18  Eric_Werme
 * 	Add caching for symbolic links.
 * 	[1993/03/29  16:04:36  Eric_Werme]
 * 
 * Revision 1.1.9.3  1993/07/02  17:39:31  James_Woodward
 * 	osf12 merge
 * 	[1993/06/24  13:00:53  James_Woodward]
 * 
 * Revision 1.1.9.2  1993/06/11  16:44:07  Anton_Verhulst
 * 	Use ppidtab instead of proc.
 * 	[1993/06/08  22:31:12  Anton_Verhulst]
 * 
 * Revision 1.1.3.4  1992/06/03  15:48:45  Benoy_Desouza
 * 	merged in Silver BL7
 * 	Ansify endif.
 * 	[92/05/21  12:01:36  William_Burns]
 * 
 * Revision 1.1.3.3  92/03/21  10:50:08  Benoy_Desouza
 * 	64 bit changes to ONC code
 * 	[92/03/21  10:49:43  Benoy_Desouza]
 * 
 * Revision 1.1.3.2  92/03/18  17:56:21  Al_Delorey
 * 	From Silver: AG_BL5
 * 	[92/03/18  16:25:34  Al_Delorey]
 * 	From UBC reference port
 * 	[92/02/19  14:49:10  Charles_Briggs]
 * 
 * Revision 1.1.1.2  92/03/17  16:41:48  devbld_gsf
 * 	First AG_BL5 version.  Moved from Ag baselevel delivery tree.
 * 
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: rnode.h,v $ $Revision: 1.1.59.2 $ (DEC) $Date: 2003/08/27 19:46:11 $
 */
/*	@(#)rnode.h	1.5 90/07/02 NFSSRC4.1 from 1.27 89/12/13 SMI 	*/
/*	Copyright (C) 1988, Sun Microsystems Inc. */

#ifndef _nfs_rnode_h
#define _nfs_rnode_h

typedef struct access_cache {
        uint32 known;
        uint32 allowed;
	struct ucred *cred;
	struct access_cache *next;
} access_cache;

#define NFS_FHANDLE_LEN 64

typedef struct nfs_fhandle {
        int fh_len;
        char fh_buf[NFS_FHANDLE_LEN];
} nfs_fhandle;


/*
 * Remote file information structure.
 * The rnode is the "inode" for remote files.  It contains all the
 * information necessary to handle remote file on the client side.
 *
 * Note on file sizes:  we keep two file sizes in the rnode: the size
 * according to the client (r_size) and the size according to the server
 * (r_attr.va_size).   They can differ because we modify r_size during a
 * write system call (nfs_rdwr), before the write request goes over the
 * wire (before the file is actually modified on the server).  If an OTW
 * request occurs before the cached data is written to the server the file
 * size returned from the server (r_attr.va_size) may not match r_size. 
 * r_size is the one we use, in general.  r_attr->va_size is only used to
 * determine whether or not our cached data is valid.
 *
 * Rnodes immediately follow vnodes and therefore probably don't start on
 * a cache line.  Therefore, we put the simple lock in the middle of some
 * of the data it protects.  That forces some of the data to share the
 * cache line that holds the lock.
 */
struct rnode {
	struct rnode	*r_hash;	/* 8: rnode hash chain */
	unsigned long	r_xfileid;	/* 8: long fileid */
	struct timeval	r_attrtime;	/* 8: time attributes become invalid */
	struct nameidata *r_ndp;	/* 8: unlink information */
	access_cache    *r_acc;         /* 8: cache of access results */

	struct ucred	*r_cred;	/* 8: current credentials */
	u_long		r_size;		/* 8: client's view of file size */
	udecl_simple_lock_data(, r_statelock) /* 8: protects rnode contents */
	u_short		r_flags;	/* 2: flags, see below */
	u_short		r_lockcount;	/* 2: lock count */
	u_int		r_error;	/* 4: async write error */
	union {				/*    use unions to conserve space */
	    struct {			/* 32: regular file: I/O info */
		daddr_t ru_lastr;	/* last block read */
		daddr_t ru_lastra;	/* last readahead block */
		off_t ru_delayoff;	/* starting offset of write cluster */
		writeverf3 ru_wrverf;	/* rtned on WRITE and COMMIT */
		int ru_delaylen;	/* current length of write cluster */
		int ru_wrverfseq;	/* sequence number of write r_verf */
	    } ru_reg;
	    struct {			/* 12: symbolic link: cached response */
		char *contents;		/* contents of the symbolic link */
		int len;		/* length of the contents */
	    } ru_lnk;
	    struct {			/* 16: directory info */
		off_t ru_diroff;	/* last offset read */
		cookieverf3 ru_cookie;	/* readdir* cookie */
	    } ru_dir;
	    struct {			/* 16: Special file: time stamps */
		struct timeval ru_atime; /* special device access time */
		struct timeval ru_mtime; /* special device modify time */
	    } ru_spec;
	} r_u;
	struct vattr	r_attr;		/* 96: cached vnode attributes */
	lock_data_t     r_rwlock;       /* 48: serializes dir mods */
	nfs_fhandle	r_fh;		/* 68: file handle */
};

/* N.B.  All accesses to r_u must include a check for the proper file type! */
#define r_delayoff	r_u.ru_reg.ru_delayoff
#define r_wrverf	r_u.ru_reg.ru_wrverf
#define r_delaylen	r_u.ru_reg.ru_delaylen
#define r_wrverfseq	r_u.ru_reg.ru_wrverfseq
#define r_lastr		r_u.ru_reg.ru_lastr
#define r_lastra	r_u.ru_reg.ru_lastra

#define r_symlink	r_u.ru_lnk

#define r_diroff	r_u.ru_dir.ru_diroff
#define r_ckverf	r_u.ru_dir.ru_cookie

#define r_atime		r_u.ru_spec.ru_atime
#define r_mtime		r_u.ru_spec.ru_mtime

/*
 * Flags in r_flags
 */
#define	RFLUSH		0x04		/* data flush in progress */
#define	REOF		0x08		/* EOF encountered on read */
#define	RDIRTY		0x10		/* dirty pages from write operation */
#define RNOCACHE	0x20		/* don't cache read and write blocks */
#define RACC		0x40		/* Need to update access time */
#define RUPD		0x80		/* Need to update modify time */
#define RCHG		0x100		/* Placeholder for attr change time */
#define RTIMESYNC	0x200		/* Set while updating time attributes */
#define	RMMAPPED	0x1000		/* file is mmap()ed */
#define	RCOMMITTING	0x2000		/* file being committed */
#define	RCOMMITWAIT	0x4000		/* somebody waiting to commit */
udecl_simple_lock_info(extern, rnode_state_lockinfo)
extern struct lockinfo *rnode_rw_lockinfo;

/*
 * Convert between vnode and rnode
 */
#define roffsetof(s_name, s_member) \
	((size_t)((char *)&((s_name *)0L)->s_member - (char *)0L))
#define	rtov(rp)	((struct vnode *)((char *) rp - roffsetof(struct vnode, v_data[0])))
#define	vtor(vp)	((struct rnode *)((vp)->v_data))

#define VTOFH(vp)       (RTOFH(vtor(vp)))
#define vtofh(vp)       (RTOFH(vtor(vp)))
#define RTOFH(rp)       ((fhandle_t *)(((rp)->r_fh.fh_buf)))
#define rtofh(rp)       ((fhandle_t *)(((rp)->r_fh.fh_buf)))

#define VTOFH3(vp)      (RTOFH3(vtor(vp)))
#define RTOFH3(rp)      ((nfs_fh3 *)(&(rp)->r_fh))

#ifdef _KERNEL
_BEGIN_CPLUSPLUS
struct mntinfo;
int nfs3_getfattr3(struct mntinfo *, nfs_fh3 *, fattr3 *, struct ucred *);
_END_CPLUSPLUS
#endif

#endif
