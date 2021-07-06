/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: nfs.h,v $
 * Revision 4.3.91.4  2003/09/11  18:34:29  Paul_Park
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree v51bsupportos
 *     User Revision:  Paul_Park_xdrcksum_br:4.3.97.1 Local Ancestor:4.3.91.2
 *    Merge Revision:  v51bsupportos_br:4.3.91.3
 *   Common Ancestor:  4.3.91.2
 *
 * Revision 4.3.91.3  2003/08/27  19:46:05  Paul_Park
 * 	QAR 96719 [BCGML0JS3]:
 * 	Add typedef for nfs_va_fileid_t (type of va_fileid).
 * 	Add prototype for nfs3_fileid_map.
 * 
 * Revision 4.3.97.1  2003/07/25  12:34:27  Paul_Park
 * 	QAR 96804: Add nfs_{read,write}_pgcksum
 * 
 * Revision 4.3.91.2  2003/05/21  18:03:36  Paul_Park
 * 	QAR 96015: Change rfind footprint.
 * 
 * Revision 4.3.91.1  2003/02/10  16:22:25  Paul_Park
 * 	QAR 95547: Take a bit of nfs_readdata->size for a bit flag.
 * 
 * Revision 4.3.77.2  2001/11/01  20:47:05  Eric_Werme
 * 	Port wildcat 4.3.70.3  2001/05/08  23:02:17  Paul_Park
 * 	QAR 86377 [TKTB30117]: Move common remote read ok definitions here.
 *  *
 * 	Port wildcat 4.3.70.1  2001/03/29  22:13:54  Paul_Park
 * 	QAR 86314: Add prototype for nfs_purge_pages.
 * 
 * Revision 4.3.77.1  2001/10/01  14:27:41  Piyanai_Saowarattitada
 * 	Forward merge from wildcatos-738-ppark to fix
 * 	QAR 74519: Overlay e_{root,write}addrs vector with a pointer to a
 * 	vector.  Allows backward binary compatibility and expansion beyond
 * 	256 hosts.
 * 	[2001/09/25  16:00:34  Piyanai_Saowarattitada]
 * 
 * Revision 4.3.67.2  2000/09/13  22:12:43  Paul_Park
 * 	Add definition of RFS3_NPROC
 * 
 * Revision 4.3.67.1  2000/09/01  01:08:33  Paul_Park
 * 	Update prototypes for nfs_purge_caches() and nfs_cache_wcc_data().
 * 
 * Revision 4.3.61.3  2000/04/10  17:36:43  Anthony_Zlotek
 * 	Eliminate CFS-specifc "purged" argument from nfs_attrcache_va(),
 * 	nfs3_attrcache(), and nfs_attrcache().
 * 
 * Revision 4.3.61.2  2000/02/18  23:29:26  Piyanai_Saowarattitada
 * 	Add third argument, dfm_flag, to sattr3_to_vattr() as an
 * 	indication to set default file mode qar 75085.
 * 
 * Revision 4.3.61.1  2000/01/19  16:35:17  Eric_Werme
 * 	Merge to nightly.
 * 	[2000/01/18  18:22:24  Eric_Werme]
 * 	Move some server-only data to new file nfs_svc.h  (NUMA server changes)
 * 	[2000/01/14  21:20:21  Eric_Werme]
 * 
 * Revision 4.3.56.4  1999/11/23  19:31:23  Piyanai_Saowarattitada
 * 	Add TRAP_CORRUPTED_DIRENT define for QAR 71448.
 * 
 * Revision 4.3.56.3  1999/08/19  17:07:22  Martin_Lund
 * 	Include vm_param.h for PAGE_SHIFT.
 * 	[1999/08/19  16:51:53  Martin_Lund]
 * 
 * Revision 4.3.56.2  1999/08/18  23:32:34  Martin_Lund
 * 	Large I/O support for NFSv3 client.
 * 	[1999/08/18  20:51:41  Martin_Lund]
 * 
 * Revision 4.3.39.15  1999/04/23  15:08:29  John_Carr
 * 	Take iovec structure out of nfsrrok structure.  QAR 70835.
 * 	[1999/04/21  10:05:22  John_Carr]
 * 
 * Revision 4.3.39.14  1999/03/17  11:38:03  John_Carr
 * 	Only include <sys/vfs_proto.h> in kernel.
 * 	[1999/03/17  10:16:25  John_Carr]
 * 
 * Revision 4.3.39.13  1999/03/16  10:00:21  John_Carr
 * 	Add prototypes.
 * 	[1999/03/11  18:58:48  John_Carr]
 * 
 * Revision 4.3.39.12  1999/01/19  19:39:32  Eric_Werme
 * 	Merge PtFC BL3: Rev 4.3.54.2
 * 	[1999/01/16  20:37:55  Eric_Werme]
 * 
 * Revision 4.3.39.11  1998/11/18  16:54:16  Steve_Dickson
 * 	Merged in the following chagned from tcr4os pool
 * 	  Added third argument to nfs3_attrcache which is used to keep
 * 	  CFS caches synchronized. QAR 58157
 * 	  [1998/09/16  18:48:02  Steve_Dickson]
 * 	 Synchronize CFS attr, access, and data caches with NFS caches.
 * 	  QAR 58157
 * 	  [1998/09/03  18:58:51  Martin_Lund]
 * 	[1998/11/18  16:40:34  Steve_Dickson]
 * 
 * Revision 4.3.54.2  1998/09/25  14:47:14  Eric_Werme
 * 	Extend READDIRPLUS3resok to support pre-xdrred data. (QAR 62581)
 * 	[1998/09/21  21:02:42  Eric_Werme]
 * 
 * Revision 4.3.39.10  1998/09/04  18:05:30  Martin_Lund
 * 	Synchronize CFS attr, access, and data caches with
 * 	NFS caches.  QAR 58157
 * 	[1998/09/03  20:30:46  Martin_Lund]
 * 
 * Revision 4.3.39.9  1998/08/25  23:19:39  Dave_King
 * 	- Remove nfid definition.
 * 	- Move rnodehash table struct and lock defines here.
 * 	[1998/08/20  14:08:55  Dave_King]
 * 
 * Revision 4.3.39.8  1998/07/16  22:08:24  Carolyn_Hurley
 * 	Add NFS_MAXTIMO, Changed the MAXTIMO defined
 * 	in nfs_subr.c to be a nfs mount option.
 * 	Alcatel ECP EALC6003
 * 	[1998/07/09  19:28:38  Carolyn_Hurley]
 * 
 * Revision 4.3.39.7  1997/09/16  18:56:25  Carolyn_Hurley
 * 	Fixed prototypes for xdr_writeverf3,
 * 	xdr_cookieverf3 and xdr_createverf3 to
 * 	match definitions.  (QAR 52860)
 * 	[1997/08/27  14:15:12  Carolyn_Hurley]
 * 
 * Revision 4.3.39.6  1997/06/18  15:35:44  Dave_King
 * 	Added nfid structure for use with nfs_vptofh().
 * 	[1997/06/02  15:52:44  Dave_King]
 * 
 * Revision 4.3.39.5  1997/05/07  10:26:59  Carolyn_Hurley
 * 	Include exaddrlist as part of the exaddrtbl, need for mountd.
 * 	[1997/05/06  18:12:48  Carolyn_Hurley]
 * 
 * Revision 4.3.39.4  1997/05/05  13:44:02  Carolyn_Hurley
 * 	NFS server Steel scalability (part of st.nfs.04.server_scalability):
 * 	Changed struct exaddrlist to exaddrtbl and added hash table info for
 * 	export host root and write lists.
 * 	[1997/05/01  17:31:46  Carolyn_Hurley]
 * 
 * Revision 4.3.39.3  1997/02/11  15:25:52  Eric_Werme
 * 	NFS server Steel scalability (part of st.nfs.04.server_scalability):
 * 	Discard export list pointer, add mount struct pointer.
 * 	[1997/02/07  18:45:24  Eric_Werme]
 * 
 * Revision 4.3.39.2  1997/01/15  21:34:29  Carolyn_Hurley
 * 	Added read3data and NFS3_MAXDATA
 * 	32K server read/write enhancements. (QAR 49053)
 * 	[1997/01/14  16:30:01  Carolyn_Hurley]
 * 
 * Revision 4.3.26.9  1995/12/05  18:44:21  Eric_Werme
 * 	Silence lint, wholly lint.
 * 	No one's calm, fires burn bright.
 * 	[1995/12/05  18:35:22  Eric_Werme]
 * 
 * Revision 4.3.26.8  1995/06/30  20:41:01  Arti_Kumar
 * 	Add EXPORTFS_CHECK define
 * 	[1995/06/30  18:07:30  Arti_Kumar]
 * 
 * Revision 4.3.26.7  1995/06/27  21:02:31  Eric_Werme
 * 	Need lock terminate macro for client handle list entries.
 * 	[1995/06/27  18:01:02  Eric_Werme]
 * 
 * Revision 4.3.26.6  1995/06/15  17:06:49  Larry_Scott
 * 	add comments for sideband service routines in list of service routines
 * 	[1995/06/13  21:46:59  Larry_Scott]
 * 
 * Revision 4.3.26.5  1995/04/28  20:14:01  Diane_Lebel
 * 	Changed args to nfs_purge_caches for SMP client.
 * 	[1995/04/27  23:32:50  Diane_Lebel]
 * 
 * Revision 4.3.26.4  1995/04/24  21:04:37  Eric_Werme
 * 	Add prototype for chtabfree().
 * 	Change export lock to take a list head structure argument.
 * 	Change chlist lock to be a simple lock.
 * 	Add tslist lock.
 * 	[1995/04/24  18:24:24  Eric_Werme]
 * 
 * Revision 4.3.26.3  1995/03/18  23:44:41  Arti_Kumar
 * 	bmerge to latest
 * 	[1995/03/18  23:39:09  Arti_Kumar]
 * 	try it once again
 * 	[1995/03/17  23:15:33  Arti_Kumar]
 * 	bci again
 * 	[1995/03/17  22:21:56  Arti_Kumar]
 * 	Changes after code review
 * 	[1995/03/08  23:16:16  Arti_Kumar]
 * 	Add RFS_XXXPROPLIST and RFS3_NPROC defines for property list support
 * 	Ric: Add function prototypes for chtabget, chtabfree, CHLIST_LOCK declarations
 * 	[1995/02/21  01:37:40  Arti_Kumar]
 * 
 * Revision 4.3.26.2  1995/03/07  23:11:09  David_Sloat
 * 	Added #define NFS_MAXASYNCDAEMON    64
 * 	QAR 30596
 * 	[1995/03/07  20:48:36  David_Sloat]
 * 
 * Revision 4.3.23.2  1994/08/25  15:25:28  James_Woodward
 * 	replace multisocket code with lightweight requeue. cleanup locks.
 * 	[1994/08/24  15:39:52  James_Woodward]
 * 
 * Revision 4.3.14.13  1994/06/14  15:20:21  Eric_Werme
 * 	Add definitions for chtabhead_lock.
 * 	[1994/06/13  19:43:47  Eric_Werme]
 * 
 * Revision 4.3.14.12  1994/04/16  02:42:19  Paula_Long
 * 	Updated locks to use lockinfo,(still no heirarchy or spl checking)
 * 	[1994/04/10  23:37:32  Paula_Long]
 * 
 * Revision 4.3.14.11  1994/04/08  19:58:05  Eric_Werme
 * 	1) Add xdr/mbuf support.
 * 	2) Add locks for V3 write gathering.
 * 	[1994/04/07  19:47:58  Eric_Werme]
 * 
 * Revision 4.3.14.10  1994/03/29  18:19:52  Thomas_Peterson
 * 	Fixes for ANSI & C++
 * 	[1994/03/17  22:06:01  Thomas_Peterson]
 * 
 * Revision 4.3.14.9  1994/02/14  18:12:24  Timothy_Burke
 * 	Removed nfs_lbolt_lock.
 * 	[1994/02/14  13:54:23  Timothy_Burke]
 * 
 * Revision 4.3.14.8  1993/10/29  16:15:47  Timothy_Burke
 * 	Added nfs_sv_active_lock.
 * 	[1993/10/27  16:54:35  Timothy_Burke]
 * 
 * Revision 4.3.14.7  1993/09/24  17:06:40  John_Kohl
 * 	change dirents to be either new or old, not both
 * 	[1993/09/23  19:49:27  John_Kohl]
 * 	changes for new readdir code
 * 	[1993/09/21  19:57:32  John_Kohl]
 * 	kernel dirent changes
 * 	[1993/08/25  16:53:54  John_Kohl]
 * 
 * Revision 4.3.14.6  1993/09/14  22:46:14  Diane_Lebel
 * 	More NFSv3 related changes.
 * 	[1993/09/13  04:05:24  Diane_Lebel]
 * 
 * Revision 4.3.14.5  1993/09/07  21:25:50  Eric_Werme
 * 	Add support for NFS V3.
 * 	[1993/09/07  20:40:08  Eric_Werme]
 * 
 * Revision 4.3.14.4  1993/08/26  14:26:52  Timothy_Burke
 * 	Sterling to Gold merge.
 * 	Revision 4.3.10.4  1993/06/29  18:53:14  SJ_Lee
 * 	add #ifndef _NFS_HEADER_ to avoid multiple inclusion.
 * 	[1993/06/29  18:49:41  SJ_Lee]
 * 	Revision 4.3.10.3  1993/06/09  12:43:18  Eric_Werme
 * 	Fix lint complaints.
 * 	[1993/06/09  12:39:55  Eric_Werme]
 * 	Revision 4.3.10.2  1993/05/28  01:05:57  Diane_Lebel
 * 	Changes to exports related structures for new options.
 * 	[1993/05/26  00:00:59  Diane_Lebel]
 * 	Revision 4.3.8.2  1993/03/15  11:55:33  Eric_Werme
 * 	Add include of sys/mount.h, since many readers don't include it.
 * 	[1993/03/11  15:41:40  Eric_Werme]
 * 
 * Revision 4.3.14.3  1993/08/18  16:41:47  Timothy_Burke
 * 	Moved NFS server lock macros here so that the locks can
 * 	be init'ed in nfs_hooks.c while the locks are used in
 * 	nfs_server.c (and a few other files).
 * 	[1993/08/17  14:38:11  Timothy_Burke]
 * 
 * Revision 4.3.14.2  1993/08/06  14:38:45  Timothy_Burke
 * 	Merge prior to submit.
 * 	[1993/08/06  14:29:27  Timothy_Burke]
 * 	Added SMP lock for exports list.
 * 	[1993/08/05  18:27:00  Timothy_Burke]
 * 
 * Revision 4.3.4.5  1992/11/25  15:18:11  Stephen_Strange
 * 	Move MAXNFSDS definition in from nfs_server.c for availability
 * 	to nfsd.c
 * 	[92/11/20  17:06:02  Stephen_Strange]
 * 
 * Revision 4.3.4.4  92/11/03  17:54:41  Chet_Juszczak
 * 	NFS server performance work
 * 	[92/11/03  17:27:14  Chet_Juszczak]
 * 
 * Revision 4.3.4.3  92/10/14  14:19:46  Benoy_Desouza
 * 	Merged in Silver BL10_6
 * 	Delete cj_in_addr
 * 	[92/09/14  10:13:38  Eric_Werme]
 * 
 * Revision 4.3.4.2  92/03/20  15:10:58  Benoy_Desouza
 * 	Merged in Silver BL5
 * 	[92/03/20  15:10:21  Benoy_Desouza]
 * 
 * Revision 4.2.2.2  92/02/26  15:41:39  Charles_Briggs
 * 	fixed cj_in_addr
 * 	[92/02/25  12:55:43  Charles_Briggs]
 * 	Pool merge
 * 	[92/02/23  12:39:41  Charles_Briggs]
 * 	Pool merge
 * 	[92/02/23  12:36:30  Charles_Briggs]
 * 	Replaced OSF version with ONC.
 * 	[92/02/19  10:42:15  Charles_Briggs]
 * 
 * Revision 4.2  91/09/19  22:50:09  devbld
 * 	Adding ODE Headers
 * 
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: nfs.h,v $ $Revision: 4.3.91.4 $ (DEC) $Date: 2003/09/11 18:34:29 $
 */ 
/*
 */
#ifndef __NFS_HEADER__
#define __NFS_HEADER__

#include <standards.h>
#include <sys/mount.h>		/* Need for nfsv2fh define */
#include <sys/socket.h>		/* Needed for exaddrtbl defines */
#include <sys/errno.h>		/* Needed for error macros */
#ifdef _KERNEL
#include <sys/vfs_proto.h>
#endif
#include <rpc/types.h>		/* Needed for bool_t */
#include <rpc/xdr.h>		/* Needed for XDR */
#include <mach/machine/vm_param.h>	/* Needed for PAGE_SHIFT */

/*
 * remote file service numbers
 */
#define	NFS_PROGRAM	((u_long)100003)
#define	NFS_VERSMIN	((u_long)2)
#define	NFS_VERSMAX	((u_long)3)
#define	NFS_VERSION	((u_long)2)
#define	NFS_PORT	2049

/* Maximum size of data portion of a remote request */
#define	NFS_MAXDATA	8192
#define	NFS3_MAXDATA	65536 		/* MAX data transfer size */
#define	NFS_MAXREADDIR	NFS_MAXDATA	/* Max. size of directory read */
#define	NFS_MAXNAMLEN	255
#define	NFS_MAXPATHLEN	1024
#define NFS_FABLKSIZE	512		/* CJXXX: for na_blocks */
#define NFS3_MAXUDPSIZE 49152 		/* MAX UDP transfer size */

/* 
 * 	Set transfer size dependent on mount point protocol 
 */
#define nfs3tsize(x)    (x ? NFS3_MAXDATA : NFS3_MAXUDPSIZE) /* tcp or udp */

/*
 * Rpc retransmission parameters
 */
#define	NFS_TIMEO	11	/* initial timeout in tenths of a sec. */
#define	NFS_RETRIES	4	/* times to retry request */
#define	NFS_MAXTIMO	20	/* Maximum retransmission backoff in secs. */

/* Maximum number of concurrent nfs daemons */
#define MAXNFSDS	128

/* Maximum number of asynchronous write nfs daemons */
#define NFS_MAXASYNCDAEMON	64

/*
 * Error status
 * Should include all possible net errors.
 * For now we just cast errno into an enum nfsstat.
 */
enum nfsstat {
	NFS_OK = 0,			/* no error */
	NFSERR_PERM=EPERM,		/* Not owner */
	NFSERR_NOENT=ENOENT,		/* No such file or directory */
	NFSERR_IO=EIO,			/* I/O error */
	NFSERR_NXIO=ENXIO,		/* No such device or address */
	NFSERR_ACCES=EACCES,		/* Permission denied */
	NFSERR_EXIST=EEXIST,		/* File exists */
	NFSERR_NODEV=ENODEV,		/* No such device */
	NFSERR_NOTDIR=ENOTDIR,		/* Not a directory */
	NFSERR_ISDIR=EISDIR,		/* Is a directory */
	NFSERR_FBIG=EFBIG,		/* File too large */
	NFSERR_NOSPC=ENOSPC,		/* No space left on device */
	NFSERR_ROFS=EROFS,		/* Read-only file system */
	NFSERR_NAMETOOLONG=ENAMETOOLONG,/* File name too long */
	NFSERR_NOTEMPTY=ENOTEMPTY,	/* Directory not empty */
	NFSERR_DQUOT=EDQUOT,		/* Disc quota exceeded */
	NFSERR_STALE=ESTALE,		/* Stale NFS file handle */
	NFSERR_WFLUSH			/* write cache flushed */
};

#define	puterrno(error)		((enum nfsstat)error)
#define	geterrno(status)	((int)status)

/*
 * File types
 */
enum nfsftype {
	NFNON,
	NFREG,		/* regular file */
	NFDIR,		/* directory */
	NFBLK,		/* block special */
	NFCHR,		/* character special */
	NFLNK		/* symbolic link */
};
/*
 * Special kludge for fifos (named pipes)  [to adhere to NFS Protocol Spec]
 *
 * VFIFO is not in the protocol spec (VNON will be replaced by VFIFO)
 * so the over-the-wire representation is VCHR with a '-1' device number.
 *
 * NOTE: This kludge becomes unnecessary with the Protocol Revision,
 *       but it may be necessary to support it (backwards compatibility).
 */

/* CJXXX */
#define	S_IFMT		0170000		/* type of file */
#define S_IFCHR		0020000		/* character special */

#define NFS_FIFO_TYPE   NFCHR
#define NFS_FIFO_MODE   S_IFCHR
#define NFS_FIFO_DEV    ((unsigned) ~0)

/* identify fifo in nfs attributes */
#define NA_ISFIFO(NA)	(((NA)->na_type == NFS_FIFO_TYPE) && \
			    ((NA)->na_rdev == NFS_FIFO_DEV))

/* set fifo in nfs attributes */
#define NA_SETFIFO(NA)	{ \
			(NA)->na_type = NFS_FIFO_TYPE; \
			(NA)->na_rdev = NFS_FIFO_DEV; \
			(NA)->na_mode = ((NA)->na_mode&~S_IFMT)|NFS_FIFO_MODE; \
			}

/* 
 *  Prevent infinite loop in the case in which dirent struct
 *  was, somehow, corrupted and zeroed out. qar 71448. Set error status,
 *  EOF and then return.
 */
#define TRAP_CORRUPTED_DIRENT(reclen)				\
	(reclen == 0 || (reclen & (sizeof(ino_t)-1)))

/* forward decl for ANSI & C++ */
struct mbuf;
struct buf;
struct dirent;
struct chtab;

/*
 * Common read definitions.  Shared between V2 and V3 read.
 */

struct nfs_readdata {
	struct vnode	*data_vp; /* vnode assoc. with buffer */
	struct iovec 	iov[(NFS3_MAXDATA >> PAGE_SHIFT) + 1];
	void		*data_pg[(NFS3_MAXDATA >> PAGE_SHIFT) + 1];
	unsigned	size:31;
	unsigned	buffers:1;
};

struct nfs_rrokinfo {
	int	(*func)(struct nfs_rrokinfo *rip);
	int	done;
	struct nfs_readdata *rrokp;
};

#ifdef	_KERNEL
_BEGIN_CPLUSPLUS
/*
 * Common routines for handling rrok
 */
int nfs_rrokfree(struct nfs_rrokinfo *rip);
void nfs_rrokwakeup(caddr_t addr, u_int size, struct nfs_rrokinfo *rip);
int nfs_read_pgcksum(struct mbuf *m, int size);
_END_CPLUSPLUS
#endif	/* _KERNEL */

/*
 * Arguments to remote write and writecache
 */
struct nfswriteargs {
	fhandle_t	wa_fhandle;	/* handle for file */
	u_int		wa_begoff;	/* beginning byte offset in file */
	u_int		wa_offset;	/* current byte offset in file */
	u_int		wa_totcount;	/* total write cnt (to this offset) */
	u_int		wa_count;	/* size of this write */
	int		wa_dupbusy;	/* wg processing a busy write */
	char		*wa_data;	/* data to write (up to NFS_MAXDATA) */
	struct mbuf	*wa_mbuf;	/* mbuf containing data */
};

/*
 * File attributes
 */
struct nfsfattr {
	enum nfsftype	na_type;	/* file type */
	u_int		na_mode;	/* protection mode bits */
	u_int		na_nlink;	/* # hard links */
	u_int		na_uid;		/* owner user id */
	u_int		na_gid;		/* owner group id */
	u_int		na_size;	/* file size in bytes */
	u_int		na_blocksize;	/* preferred block size */
	u_int		na_rdev;	/* special device # */
	u_int		na_blocks;	/* Kb of disk used by file */
	u_int		na_fsid;	/* device # */
	u_int		na_nodeid;	/* inode # */
	struct timeval	na_atime;	/* time of last access */
	struct timeval	na_mtime;	/* time of last modification */
	struct timeval	na_ctime;	/* time of last change */
};

#define n2v_type(x)	(NA_ISFIFO(x) ? VFIFO : (enum vtype)((x)->na_type))
#define n2v_rdev(x)	(NA_ISFIFO(x) ? 0 : (x)->na_rdev)

/*
 * Arguments to remote read
 */
struct nfsreadargs {
	fhandle_t	ra_fhandle;	/* handle for file */
	u_int		ra_offset;	/* byte offset in file */
	u_int		ra_count;	/* immediate read count */
	u_int		ra_totcount;	/* total read cnt (from this offset) */
};

/*
 * Status OK portion of remote read reply
 */
struct nfsrrok {
	struct nfsfattr	rrok_attr;	/* attributes, need for pagin */
	struct nfs_readdata rrok_rddata; /* Common structure */
	char		*rrok_data;	/* buffer */
	u_int		rrok_count;	/* bytes of data */
};

/*
 * Reply from remote read
 */
struct nfsrdresult {
	enum nfsstat	rr_status;	    	/* status of read */
	union {
		struct nfsrrok	rr_ok_u;	/* attributes */
		                                /*  (needed for pagin) */
	} rr_u;
};
#define	rr_ok		rr_u.rr_ok_u
#define	rr_attr		rr_u.rr_ok_u.rrok_attr
#define	rr_count	rr_u.rr_ok_u.rrok_count
#define	rr_data		rr_u.rr_ok_u.rrok_data
#define	rr_rddata	rr_u.rr_ok_u.rrok_rddata

/*
 * File attributes which can be set
 */
struct nfssattr {
	u_int		sa_mode;	/* protection mode bits */
	u_int		sa_uid;		/* owner user id */
	u_int		sa_gid;		/* owner group id */
	u_int		sa_size;	/* file size in bytes */
	struct timeval	sa_atime;	/* time of last access */
	struct timeval	sa_mtime;	/* time of last modification */
};


/*
 * Reply status with file attributes
 */
struct nfsattrstat {
	enum nfsstat	ns_status;		/* reply status */
	union {
		struct nfsfattr ns_attr_u;	/* NFS_OK: file attributes */
	} ns_u;
};
#define	ns_attr	ns_u.ns_attr_u


/*
 * NFS_OK part of read sym link reply union
 */
struct nfssrok {
	u_int	srok_count;	/* size of string */
	char	*srok_data;	/* string (up to NFS_MAXPATHLEN bytes) */
};

/*
 * Result of reading symbolic link
 */
struct nfsrdlnres {
	enum nfsstat	rl_status;		/* status of symlink read */
	union {
		struct nfssrok	rl_srok_u;	/* name of linked to */
	} rl_u;
};
#define	rl_srok		rl_u.rl_srok_u
#define	rl_count	rl_u.rl_srok_u.srok_count
#define	rl_data		rl_u.rl_srok_u.srok_data


/*
 * Arguments to readdir
 */
struct nfsrddirargs {
	fhandle_t	rda_fh;		/* directory handle */
	u_int		rda_offset;	/* offset in directory (opaque) */
	u_int		rda_count;	/* number of directory bytes to read */
};

/*
 * NFS_OK part of readdir result
 */
struct nfsrdok {
	u_int	rdok_offset;		/* next offset (opaque) */
	u_int	rdok_size;		/* size in bytes of entries */
	bool_t	rdok_eof;		/* true if last entry is in result */
	struct dirent *rdok_entries;	/* variable number of entries */
};

/*
 * Readdir result
 */
struct nfsrddirres {
	u_int		rd_bufsize;	/* client request size (not xdr'ed) */
 	u_int		rd_origreqsize;	/* client request size */
	enum nfsstat	rd_status;
	union {
		struct nfsrdok rd_rdok_u;
	} rd_u;
};
#define	rd_rdok		rd_u.rd_rdok_u
#define	rd_offset	rd_u.rd_rdok_u.rdok_offset
#define	rd_size		rd_u.rd_rdok_u.rdok_size
#define	rd_eof		rd_u.rd_rdok_u.rdok_eof
#define	rd_entries	rd_u.rd_rdok_u.rdok_entries


/*
 * Arguments for directory operations
 */
struct nfsdiropargs {
	fhandle_t	da_fhandle;	/* directory file handle */
	char		*da_name;	/* name (up to MAXNAMLEN bytes) */
	int		da_len;		/* length of name */
};

/*
 * NFS_OK part of directory operation result
 */
struct  nfsdrok {
	fhandle_t	drok_fhandle;	/* result file handle */
	struct nfsfattr	drok_attr;	/* result file attributes */
};

/*
 * Results from directory operation
 */
struct  nfsdiropres {
	enum nfsstat	dr_status;	/* result status */
	union {
		struct  nfsdrok	dr_drok_u;	/* NFS_OK result */
	} dr_u;
};
#define	dr_drok		dr_u.dr_drok_u
#define	dr_fhandle	dr_u.dr_drok_u.drok_fhandle
#define	dr_attr		dr_u.dr_drok_u.drok_attr

/*
 * arguments to setattr
 */
struct nfssaargs {
	fhandle_t	saa_fh;		/* fhandle of file to be set */
	struct nfssattr	saa_sa;		/* new attributes */
};

/*
 * arguments to create and mkdir
 */
struct nfscreatargs {
	struct nfsdiropargs	ca_da;	/* file name to create and parent dir */
	struct nfssattr		ca_sa;	/* initial attributes */
};

/*
 * arguments to link
 */
struct nfslinkargs {
	fhandle_t		la_from;	/* old file */
	struct nfsdiropargs	la_to;		/* new file and parent dir */
};

/*
 * arguments to rename
 */
struct nfsrnmargs {
	struct nfsdiropargs rna_from;	/* old file and parent dir */
	struct nfsdiropargs rna_to;	/* new file and parent dir */
};

/*
 * arguments to symlink
 */
struct nfsslargs {
	struct nfsdiropargs	sla_from;	/* old file and parent dir */
	char			*sla_tnm;	/* new name */
	struct nfssattr		sla_sa;		/* attributes */
};

/*
 * NFS_OK part of statfs operation
 */
struct nfsstatfsok {
	u_int fsok_tsize;	/* preferred transfer size in bytes */
	u_int fsok_bsize;	/* fundamental file system block size */
	u_int fsok_blocks;	/* total blocks in file system */
	u_int fsok_bfree;	/* free blocks in fs */
	u_int fsok_bavail;	/* free blocks avail to non-superuser */
};

/*
 * Results of statfs operation
 */
struct nfsstatfs {
	enum nfsstat	fs_status;	/* result status */
	union {
		struct	nfsstatfsok fs_fsok_u;	/* NFS_OK result */
	} fs_u;
};
#define	fs_fsok		fs_u.fs_fsok_u
#define	fs_tsize	fs_u.fs_fsok_u.fsok_tsize
#define fs_bsize	fs_u.fs_fsok_u.fsok_bsize
#define	fs_blocks	fs_u.fs_fsok_u.fsok_blocks
#define	fs_bfree	fs_u.fs_fsok_u.fsok_bfree
#define	fs_bavail	fs_u.fs_fsok_u.fsok_bavail

/*
 * XDR routines for handling structures defined above
 */

_BEGIN_CPLUSPLUS
bool_t xdr_attrstat __((XDR *, struct nfsattrstat *));
bool_t xdr_creatargs __((XDR *, struct nfscreatargs *));
bool_t xdr_diropargs __((XDR *, struct nfsdiropargs *));
bool_t xdr_diropres __((XDR *, struct nfsdiropres *));
bool_t xdr_drok __((XDR *, struct nfsdrok *));
bool_t xdr_fattr __((XDR *, struct nfsfattr *));
bool_t xdr_fhandle __((XDR *, fhandle_t *));
bool_t xdr_linkargs __((XDR *, struct nfslinkargs *));
bool_t xdr_rddirargs __((XDR *, struct nfsrddirargs *));
bool_t xdr_put_old_rddirres __((XDR *, struct nfsrddirres *));
bool_t xdr_putrddirres __((XDR *, struct nfsrddirres *));
bool_t xdr_getrddirres __((XDR *, struct nfsrddirres *));
bool_t xdr_new_getrddirres __((XDR *, struct nfsrddirres *));
bool_t xdr_rdlnres __((XDR *, struct nfsrdlnres *));
bool_t xdr_rdresult __((XDR *, struct nfsrdresult *));
bool_t xdr_readargs __((XDR *, struct nfsreadargs *));
bool_t xdr_rnmargs __((XDR *, struct nfsrnmargs *));
bool_t xdr_rrok __((XDR *, struct nfsrrok *));
bool_t xdr_saargs __((XDR *, struct nfssaargs *));
bool_t xdr_sattr __((XDR *, struct nfssattr *));
bool_t xdr_slargs __((XDR *, struct nfsslargs *));
bool_t xdr_srok __((XDR *, struct nfssrok *));
bool_t xdr_timeval __((XDR *, struct timeval *));
bool_t xdr_writeargs __((XDR *, struct nfswriteargs *));
bool_t xdr_statfs __((XDR *, struct nfsstatfs *));
_END_CPLUSPLUS

/*
 * Remote file service routines
 */
/* V2 */
#define	RFS_NULL	0
#define	RFS_GETATTR	1
#define	RFS_SETATTR	2
#define	RFS_ROOT	3
#define	RFS_LOOKUP	4
#define	RFS_READLINK	5
#define	RFS_READ	6
#define	RFS_WRITECACHE	7
#define	RFS_WRITE	8
#define	RFS_CREATE	9
#define	RFS_REMOVE	10
#define	RFS_RENAME	11
#define	RFS_LINK	12
#define	RFS_SYMLINK	13
#define	RFS_MKDIR	14
#define	RFS_RMDIR	15
#define	RFS_READDIR	16
#define	RFS_STATFS	17
#define	RFS_NPROC	18
/* NOTE: nfs sideband property list support service routines follow
   nfs service routines here and in timer_type and caller_type tables
*/
#define RFS_NULLPROPLIST 19
#define RFS_GETPROPLIST 20
#define RFS_SETPROPLIST 21
#define RFS_DELPROPLIST 22

/* V3 */
#define RFS3_NULL 0
#define RFS3_GETATTR 1
#define RFS3_SETATTR 2
#define RFS3_LOOKUP 3
#define RFS3_ACCESS 4
#define RFS3_READLINK 5
#define RFS3_READ 6
#define RFS3_WRITE 7
#define RFS3_CREATE 8
#define RFS3_MKDIR 9
#define RFS3_SYMLINK 10
#define RFS3_MKNOD 11
#define RFS3_REMOVE 12
#define RFS3_RMDIR 13
#define RFS3_RENAME 14
#define RFS3_LINK 15
#define RFS3_READDIR 16
#define RFS3_READDIRPLUS 17
#define RFS3_FSSTAT 18
#define RFS3_FSINFO 19
#define RFS3_PATHCONF 20
#define RFS3_COMMIT 21
#define RFS3_NPROC 22
/* NOTE: nfs sideband property list support service routines follow
   nfs service routines here and in timer_type and caller_type tables
*/
#define RFS3_NULLPROPLIST 22
#define RFS3_GETPROPLIST 23
#define RFS3_SETPROPLIST 24
#define RFS3_DELPROPLIST 25

/*
 * exported vfs flags.
 */
#define EXPORTFS_CREATE	0x01		/* create a new export record */
#define EXPORTFS_REMOVE	0x02		/* remove an old export record */
#define EXPORTFS_READ	0x03		/* read an old export record */
#define EXPORTFS_CHECK  0x04            /* check if a file is exported */
#define	EXPORTFS_LISTPTR	0x100	/* host list pointer used */

#define EXMAXADDRS 256			/* max in inline structure */

struct exaddrlist {
	unsigned naddrs;		/* number of addresses */
	struct sockaddr *addrvec;	/* pointer to array of addresses */
};

struct exaddrtbl {
	struct exaddrlist list;
	struct sockaddr **table;	/* hash table of addresses */
	u_int tblsize;			/* Size of hash table a fibinocci no. */
	u_int fib_prev;			/* Previous fibinocci #, used in hash */
};

struct exportfsaddrlist {
        unsigned naddrs;
        struct sockaddr addrvec[EXMAXADDRS];
};

/*
 * Need to make sure that this structure is packed for backward binary
 * compatibility.  The compiler wants to align the root/write address
 * unions on 8-byte boundaries, which unfortunately injects an extra 4
 * bytes.
 */
#if	defined(__arch64__) && defined(__DECC)
#pragma member_alignment	save
#pragma	nomember_alignment
#endif	/* __arch64__ && __DECC */
union exportaddrlist {
	struct exportfsaddrlist eau_avector;
	struct exaddrlist eau_alist;
};
#if	defined(__arch64__) && defined(__DECC)
#pragma member_alignment	restore
#endif	/* __arch64__ && __DECC */

struct exportfsdata {
	/* these match the values that can be accessed via stat() in stat.h */
	dev_t	e_dev;		/* ID of device containing a directory*/
	ino_t	e_ino;		/* File serial number */
        uint_t  e_gen;		/* file generation number */
	char    e_path[MAXPATHLEN];
	int     e_flags;
	uid_t   e_rootmap;
	uid_t   e_anon;
	union exportaddrlist eu_rootaddrs;
	union exportaddrlist eu_writeaddrs;
	int	e_more;
};

#ifdef _KERNEL
struct kexport {
	int	e_flags;
	fsid_t	e_fsid;
	fid_t	e_fid;
	uid_t   e_rootmap;
	uid_t	e_anon;
	int	e_pathlen;
	char	*e_path;
        struct exaddrtbl e_rootaddrs;
	struct exaddrtbl e_writeaddrs;
	struct mount	*e_mount;
	/* These match the values that can be accessed via stat() in stat.h.
	 * We only hang on to these so that we can return these values to 
	 * the user level programs (mountd) that need them.
	 */
	dev_t	e_dev;		/* ID of device containing a directory*/
	ino_t	e_ino;		/* File serial number */
        uint_t  e_gen;          /* file generation number */
};

#define EXPORT_SIZE	(sizeof(struct kexport))
#else				/* _KERNEL */
#define	e_rootaddrs	eu_rootaddrs.eau_avector
#define	e_writeaddrs	eu_writeaddrs.eau_avector
#endif				/* _KERNEL */

#ifdef _KERNEL
_BEGIN_CPLUSPLUS

/* Foward declarations of structure tags.  */
struct mntinfo;
struct nfs_fh3;
struct fattr3;
struct sattr3;
struct rnode;
struct rnodehash;
struct wcc_data;
struct vfs;
struct propattr;
struct nfs_fhandle;

/*	function defs for NFS kernel */
void	nfs_purge_pages(struct vnode *, off_t, size_t);
void	nfs_purge_caches(struct vnode *, u_int, u_int, u_int);
int	nfs_cache_check(struct vnode *, struct timeval, struct timeval, off_t);
void	nattr_to_vattr(struct vnode *, struct nfsfattr *, struct vattr *);
void	vattr_to_sattr(struct vattr *, struct nfssattr *);
#ifdef __DECC
void	vattr_to_sattr3(struct vattr *__restrict vap, struct sattr3 *__restrict sa);
#else
void	vattr_to_sattr3(struct vattr *vap, struct sattr3 *sa);
#endif
void	setdiropargs(struct nfsdiropargs *, struct nameidata *);
void	rinactive(struct rnode *);
void	nfs_attrcache(struct vnode *, struct nfsfattr *);
void	nfs_attrcache_va(struct vnode *, struct vattr *);
void	vattr_to_nattr(struct vattr *, struct nfsfattr *);
void	sattr_to_vattr(struct nfssattr *, struct vattr *);
void	rp_rmhash(struct rnode *);
void	rp_addfree(struct rnode *);
struct chtab *chtabget(u_int, u_int, u_int, int);
void	chtabfree(struct chtab *);

void	rflush(struct vfs *);
void	rinval(struct mount *);
int	rtablehash(struct nfs_fhandle *fh);
struct rnode *rfind(struct rnodehash *, struct nfs_fhandle *, struct mount *);

void	nfs_mount_release(struct mount *mp, struct vnode *vp, struct mntinfo *mi, int mountfailure);

/* nfs_vnodeops.c */
void	sync_vp(struct vnode *);
int	copy_proplist(/* PROPGETres *res, struct uio *uiop, int *min_buf_size*/);
int	nfsspec_timesync(struct vnode *vp);

void nfs_perror(int error, char *fmt, ...);
void nfs_cmn_err(int error, int level, char *fmt, ...);

int	nfs_getattr_otw(struct vnode *vp, struct vattr *vap, struct ucred *cred);
int	nfs3_getattr_otw(struct vnode *vp, struct vattr *vap, struct ucred *cred);
int	nfsgetattr(struct vnode *vp, struct vattr *vap, struct ucred *cred);
int	nfs3getattr(struct vnode *vp, struct vattr *vap, struct ucred *cr);

void	nfs_purge_access_cache(struct vnode *vp);
int	nfs_validate_caches(struct vnode *, struct ucred *);
int	nfs3_validate_caches(struct vnode *, struct ucred *);
struct vnode *makenfsnode(fhandle_t *fh, struct nfsfattr *attr, struct mount *mp);
struct vnode *makenfs3node(struct nfs_fh3 *fh, struct fattr3 *attr, struct mount *mp);

void	nfs3_cache_wcc_data(struct vnode *, struct wcc_data *, int);

int	build_proplist(struct propattr **pbuf, struct uio *uiop, int *numentries, int *size);

int	talk_to_proplistd(struct mntinfo *mi, int which, xdrproc_t xdrargs,
			  caddr_t argsp, xdrproc_t xdrres, caddr_t resp,
			  struct ucred *cred);
int	talk_to_portmap(struct mntinfo *);

int	neg_cache_enter(struct nameidata *ndp, int in_error);
int	neg_cache_lookup(struct nameidata *ndp);
int	neg_cache_purge(struct mount *mp);

int	newnum(void);
void	newname(char *);
u_int	setdirmode(struct vnode *, u_int);
gid_t	setdirgid(struct vnode *);

_END_CPLUSPLUS

#endif	/* _KERNEL */

/*
 * V3 - Version 3 declarations and definitions.
 */

#define NFS3_FHSIZE 64
#define	NFS3_COOKIEVERFSIZE 8
#define	NFS3_CREATEVERFSIZE 8
#define	NFS3_WRITEVERFSIZE 8

typedef char *filename3;

typedef char *nfspath3;

typedef uint64 fileid3;

typedef uint64 cookie3;

typedef uint32 uid3;

typedef uint32 gid3;

typedef uint64 size3;

typedef uint64 offset3;

typedef uint32 mode3;

typedef uint32 count3;

typedef char cookieverf3[NFS3_COOKIEVERFSIZE];

typedef char createverf3[NFS3_CREATEVERFSIZE];

typedef char writeverf3[NFS3_WRITEVERFSIZE];

struct nfs_fh3 {
	u_int fh3_length;
	union nfs_fh3_u {
		struct nfs_fh3_i {
			struct nfssvcfh	fh3_i;
		} nfs_fh3_i;
		u_char	data[NFS3_FHSIZE];
	} fh3_u;
};
#define	fh3_fsid	fh3_u.nfs_fh3_i.fh3_i.fh_fsid
#define	fh3_fid		fh3_u.nfs_fh3_i.fh3_i.fh_fid
#define	fh3_efid	fh3_u.nfs_fh3_i.fh3_i.fh_efid
typedef struct nfs_fh3 nfs_fh3;

struct diropargs3 {
	nfs_fh3 dir;
	filename3 name;
};
typedef struct diropargs3 diropargs3;

struct nfstime3 {
	uint32 seconds;
	uint32 nseconds;
};
typedef struct nfstime3 nfstime3;

struct specdata3 {
	uint32 specdata1;
	uint32 specdata2;
};
typedef struct specdata3 specdata3;

enum nfsstat3 {
	NFS3_OK = 0,
	NFS3ERR_PERM = 1,
	NFS3ERR_NOENT = 2,
	NFS3ERR_IO = 5,
	NFS3ERR_NXIO = 6,
	NFS3ERR_ACCES = 13,
	NFS3ERR_EXIST = 17,
	NFS3ERR_XDEV = 18,
	NFS3ERR_NODEV = 19,
	NFS3ERR_NOTDIR = 20,
	NFS3ERR_ISDIR = 21,
	NFS3ERR_INVAL = 22,
	NFS3ERR_FBIG = 27,
	NFS3ERR_NOSPC = 28,
	NFS3ERR_ROFS = 30,
	NFS3ERR_MLINK = 31,
	NFS3ERR_NAMETOOLONG = 63,
	NFS3ERR_NOTEMPTY = 66,
	NFS3ERR_DQUOT = 69,
	NFS3ERR_STALE = 70,
	NFS3ERR_REMOTE = 71,
	NFS3ERR_BADHANDLE = 10001,
	NFS3ERR_NOT_SYNC = 10002,
	NFS3ERR_BAD_COOKIE = 10003,
	NFS3ERR_NOTSUPP = 10004,
	NFS3ERR_TOOSMALL = 10005,
	NFS3ERR_SERVERFAULT = 10006,
	NFS3ERR_BADTYPE = 10007,
	NFS3ERR_JUKEBOX = 10008
};
typedef enum nfsstat3 nfsstat3;

enum ftype3 {
	NF3REG = 1,
	NF3DIR = 2,
	NF3BLK = 3,
	NF3CHR = 4,
	NF3LNK = 5,
	NF3SOCK = 6,
	NF3FIFO = 7
};
typedef enum ftype3 ftype3;

struct fattr3 {
	ftype3 type;
	mode3 mode;
	uint32 nlink;
	uid3 uid;
	gid3 gid;
	size3 size;
	size3 used;
	specdata3 rdev;
	uint64 fsid;
	fileid3 fileid;
	nfstime3 atime;
	nfstime3 mtime;
	nfstime3 ctime;
};
typedef struct fattr3 fattr3;

struct post_op_attr {
	bool_t attributes;
	fattr3 attr;
};
typedef struct post_op_attr post_op_attr;

struct wcc_attr {
	size3 size;
	nfstime3 mtime;
	nfstime3 ctime;
};
typedef struct wcc_attr wcc_attr;

struct pre_op_attr {
	bool_t attributes;
	wcc_attr attr;
};
typedef struct pre_op_attr pre_op_attr;

struct wcc_data {
	pre_op_attr before;
	post_op_attr after;
};
typedef struct wcc_data wcc_data;

struct post_op_fh3 {
	bool_t handle_follows;
	nfs_fh3 handle;
};
typedef struct post_op_fh3 post_op_fh3;

enum time_how {
	DONT_CHANGE = 0,
	SET_TO_SERVER_TIME = 1,
	SET_TO_CLIENT_TIME = 2
};
typedef enum time_how time_how;

struct set_mode3 {
	bool_t set_it;
	mode3 mode;
};
typedef struct set_mode3 set_mode3;

struct set_uid3 {
	bool_t set_it;
	uid3 uid;
};
typedef struct set_uid3 set_uid3;

struct set_gid3 {
	bool_t set_it;
	gid3 gid;
};
typedef struct set_gid3 set_gid3;

struct set_size3 {
	bool_t set_it;
	size3 size;
};
typedef struct set_size3 set_size3;

struct set_atime {
	time_how set_it;
	nfstime3 atime;
};
typedef struct set_atime set_atime;

struct set_mtime {
	time_how set_it;
	nfstime3 mtime;
};
typedef struct set_mtime set_mtime;

struct sattr3 {
	set_mode3 mode;
	set_uid3 uid;
	set_gid3 gid;
	set_size3 size;
	set_atime atime;
	set_mtime mtime;
};
typedef struct sattr3 sattr3;

/*
 * A couple of defines to make resok and resfail look like the
 * correct things in a response type independent manner.
 */
#define	resok	res_u.ok
#define	resfail	res_u.fail

struct GETATTR3args {
	nfs_fh3 object;
};
typedef struct GETATTR3args GETATTR3args;

struct GETATTR3resok {
	fattr3 obj_attributes;
};
typedef struct GETATTR3resok GETATTR3resok;

struct GETATTR3res {
	nfsstat3 status;
	union {
		GETATTR3resok ok;
	} res_u;
};
typedef struct GETATTR3res GETATTR3res;

struct sattrguard3 {
	bool_t check;
	nfstime3 obj_ctime;
};
typedef struct sattrguard3 sattrguard3;

struct SETATTR3args {
	nfs_fh3 object;
	sattr3 new_attributes;
	sattrguard3 guard;
};
typedef struct SETATTR3args SETATTR3args;

struct SETATTR3resok {
	wcc_data obj_wcc;
};
typedef struct SETATTR3resok SETATTR3resok;

struct SETATTR3resfail {
	wcc_data obj_wcc;
};
typedef struct SETATTR3resfail SETATTR3resfail;

struct SETATTR3res {
	nfsstat3 status;
	union {
		SETATTR3resok ok;
		SETATTR3resfail fail;
	} res_u;
};
typedef struct SETATTR3res SETATTR3res;

struct LOOKUP3args {
	diropargs3 what;
};
typedef struct LOOKUP3args LOOKUP3args;

struct LOOKUP3resok {
	nfs_fh3 object;
	post_op_attr obj_attributes;
	post_op_attr dir_attributes;
};
typedef struct LOOKUP3resok LOOKUP3resok;

struct LOOKUP3resfail {
	post_op_attr dir_attributes;
};
typedef struct LOOKUP3resfail LOOKUP3resfail;

struct LOOKUP3res {
	nfsstat3 status;
	union {
		LOOKUP3resok ok;
		LOOKUP3resfail fail;
	} res_u;
};
typedef struct LOOKUP3res LOOKUP3res;

struct ACCESS3args {
	nfs_fh3 object;
	uint32 access;
};
typedef struct ACCESS3args ACCESS3args;
#define	ACCESS3_READ 0x1
#define	ACCESS3_LOOKUP 0x2
#define	ACCESS3_MODIFY 0x4
#define	ACCESS3_EXTEND 0x8
#define	ACCESS3_DELETE 0x10
#define	ACCESS3_EXECUTE 0x20

struct ACCESS3resok {
	post_op_attr obj_attributes;
	uint32 access;
};
typedef struct ACCESS3resok ACCESS3resok;

struct ACCESS3resfail {
	post_op_attr obj_attributes;
};
typedef struct ACCESS3resfail ACCESS3resfail;

struct ACCESS3res {
	nfsstat3 status;
	union {
		ACCESS3resok ok;
		ACCESS3resfail fail;
	} res_u;
};
typedef struct ACCESS3res ACCESS3res;

struct READLINK3args {
	nfs_fh3 symlink;
};
typedef struct READLINK3args READLINK3args;

struct READLINK3resok {
	post_op_attr symlink_attributes;
	nfspath3 data;
};
typedef struct READLINK3resok READLINK3resok;

struct READLINK3resfail {
	post_op_attr symlink_attributes;
};
typedef struct READLINK3resfail READLINK3resfail;

struct READLINK3res {
	nfsstat3 status;
	union {
		READLINK3resok ok;
		READLINK3resfail fail;
	} res_u;
};
typedef struct READLINK3res READLINK3res;

struct READ3args {
	nfs_fh3 file;
	offset3 offset;
	count3 count;
};
typedef struct READ3args READ3args;

struct READ3resok {
	post_op_attr file_attributes;
	count3 count;
	bool_t eof;
	struct nfs_readdata data;
};
typedef struct READ3resok READ3resok;

struct READ3resfail {
	post_op_attr file_attributes;
};
typedef struct READ3resfail READ3resfail;

struct READ3res {
	nfsstat3 status;
	union {
		READ3resok ok;
		READ3resfail fail;
	} res_u;
};
typedef struct READ3res READ3res;

enum stable_how {
	UNSTABLE = 0,
	DATA_SYNC = 1,
	FILE_SYNC = 2
};
typedef enum stable_how stable_how;

struct write3data {
	struct vnode    *data_vp;
	struct iovec    iov[1];
	struct buf      *data_bp[1];
	u_int 		size;
};

struct WRITE3args {
	nfs_fh3 file;
	offset3 offset;
	count3 count;
	stable_how stable;
	struct {
		u_int data_len;
		char *data_val;
		struct mbuf *data_mbuf;	
		struct write3data wdata;
	} data;
	int dupbusy;	/* Local data */
};
typedef struct WRITE3args WRITE3args;

struct WRITE3resok {
	wcc_data file_wcc;
	count3 count;
	stable_how committed;
	writeverf3 verf;
};
typedef struct WRITE3resok WRITE3resok;

struct WRITE3resfail {
	wcc_data file_wcc;
};
typedef struct WRITE3resfail WRITE3resfail;

struct WRITE3res {
	nfsstat3 status;
	union {
		WRITE3resok ok;
		WRITE3resfail fail;
	} res_u;
};
typedef struct WRITE3res WRITE3res;

enum createmode3 {
	UNCHECKED = 0,
	GUARDED = 1,
	EXCLUSIVE = 2
};
typedef enum createmode3 createmode3;

struct createhow3 {
	createmode3 mode;
	union {
		sattr3 obj_attributes;
		createverf3 verf;
	} createhow3_u;
};
typedef struct createhow3 createhow3;

struct CREATE3args {
	diropargs3 where;
	createhow3 how;
};
typedef struct CREATE3args CREATE3args;

struct CREATE3resok {
	post_op_fh3 obj;
	post_op_attr obj_attributes;
	wcc_data dir_wcc;
};
typedef struct CREATE3resok CREATE3resok;

struct CREATE3resfail {
	wcc_data dir_wcc;
};
typedef struct CREATE3resfail CREATE3resfail;

struct CREATE3res {
	nfsstat3 status;
	union {
		CREATE3resok ok;
		CREATE3resfail fail;
	} res_u;
};
typedef struct CREATE3res CREATE3res;

struct MKDIR3args {
	diropargs3 where;
	sattr3 attributes;
};
typedef struct MKDIR3args MKDIR3args;

struct MKDIR3resok {
	post_op_fh3 obj;
	post_op_attr obj_attributes;
	wcc_data dir_wcc;
};
typedef struct MKDIR3resok MKDIR3resok;

struct MKDIR3resfail {
	wcc_data dir_wcc;
};
typedef struct MKDIR3resfail MKDIR3resfail;

struct MKDIR3res {
	nfsstat3 status;
	union {
		MKDIR3resok ok;
		MKDIR3resfail fail;
	} res_u;
};
typedef struct MKDIR3res MKDIR3res;

struct symlinkdata3 {
	sattr3 symlink_attributes;
	nfspath3 symlink_data;
};
typedef struct symlinkdata3 symlinkdata3;

struct SYMLINK3args {
	diropargs3 where;
	symlinkdata3 symlink;
};
typedef struct SYMLINK3args SYMLINK3args;

struct SYMLINK3resok {
	post_op_fh3 obj;
	post_op_attr obj_attributes;
	wcc_data dir_wcc;
};
typedef struct SYMLINK3resok SYMLINK3resok;

struct SYMLINK3resfail {
	wcc_data dir_wcc;
};
typedef struct SYMLINK3resfail SYMLINK3resfail;

struct SYMLINK3res {
	nfsstat3 status;
	union {
		SYMLINK3resok ok;
		SYMLINK3resfail fail;
	} res_u;
};
typedef struct SYMLINK3res SYMLINK3res;

struct devicedata3 {
	sattr3 dev_attributes;
	specdata3 spec;
};
typedef struct devicedata3 devicedata3;

struct mknoddata3 {
	ftype3 type;
	union {
		devicedata3 device;
		sattr3 pipe_attributes;
	} mknoddata3_u;
};
typedef struct mknoddata3 mknoddata3;

struct MKNOD3args {
	diropargs3 where;
	mknoddata3 what;
};
typedef struct MKNOD3args MKNOD3args;

struct MKNOD3resok {
	post_op_fh3 obj;
	post_op_attr obj_attributes;
	wcc_data dir_wcc;
};
typedef struct MKNOD3resok MKNOD3resok;

struct MKNOD3resfail {
	wcc_data dir_wcc;
};
typedef struct MKNOD3resfail MKNOD3resfail;

struct MKNOD3res {
	nfsstat3 status;
	union {
		MKNOD3resok ok;
		MKNOD3resfail fail;
	} res_u;
};
typedef struct MKNOD3res MKNOD3res;

struct REMOVE3args {
	diropargs3 object;
};
typedef struct REMOVE3args REMOVE3args;

struct REMOVE3resok {
	wcc_data dir_wcc;
};
typedef struct REMOVE3resok REMOVE3resok;

struct REMOVE3resfail {
	wcc_data dir_wcc;
};
typedef struct REMOVE3resfail REMOVE3resfail;

struct REMOVE3res {
	nfsstat3 status;
	union {
		REMOVE3resok ok;
		REMOVE3resfail fail;
	} res_u;
};
typedef struct REMOVE3res REMOVE3res;

struct RMDIR3args {
	diropargs3 object;
};
typedef struct RMDIR3args RMDIR3args;

struct RMDIR3resok {
	wcc_data dir_wcc;
};
typedef struct RMDIR3resok RMDIR3resok;

struct RMDIR3resfail {
	wcc_data dir_wcc;
};
typedef struct RMDIR3resfail RMDIR3resfail;

struct RMDIR3res {
	nfsstat3 status;
	union {
		RMDIR3resok ok;
		RMDIR3resfail fail;
	} res_u;
};
typedef struct RMDIR3res RMDIR3res;

struct RENAME3args {
	diropargs3 from;
	diropargs3 to;
};
typedef struct RENAME3args RENAME3args;

struct RENAME3resok {
	wcc_data fromdir_wcc;
	wcc_data todir_wcc;
};
typedef struct RENAME3resok RENAME3resok;

struct RENAME3resfail {
	wcc_data fromdir_wcc;
	wcc_data todir_wcc;
};
typedef struct RENAME3resfail RENAME3resfail;

struct RENAME3res {
	nfsstat3 status;
	union {
		RENAME3resok ok;
		RENAME3resfail fail;
	} res_u;
};
typedef struct RENAME3res RENAME3res;

struct LINK3args {
	nfs_fh3 file;
	diropargs3 link;
};
typedef struct LINK3args LINK3args;

struct LINK3resok {
	post_op_attr file_attributes;
	wcc_data linkdir_wcc;
};
typedef struct LINK3resok LINK3resok;

struct LINK3resfail {
	post_op_attr file_attributes;
	wcc_data linkdir_wcc;
};
typedef struct LINK3resfail LINK3resfail;

struct LINK3res {
	nfsstat3 status;
	union {
		LINK3resok ok;
		LINK3resfail fail;
	} res_u;
};
typedef struct LINK3res LINK3res;

struct READDIR3args {
	nfs_fh3 dir;
	cookie3 cookie;
	cookieverf3 cookieverf;
	count3 count;
};
typedef struct READDIR3args READDIR3args;

struct entry3 {
	fileid3 fileid;
	filename3 name;
	cookie3 cookie;
	struct entry3 *nextentry;
};
typedef struct entry3 entry3;

struct dirlist3 {
	entry3 *entries;
	bool_t eof;
};
typedef struct dirlist3 dirlist3;

struct READDIR3resok {
	post_op_attr dir_attributes;
	cookieverf3 cookieverf;
	dirlist3 reply;
	u_int size;
	u_int count;
	cookie3 cookie;
	/* CJXXX: "extra" stuff not encoded/decoded */
	off_t offset;		/* Dir offset of first entry if server, last
				 * entry if client.
				 */
	caddr_t buffer;		/* Address of buffer we need to free. */
	u_int buffersize;	/* Size of same */
};
typedef struct READDIR3resok READDIR3resok;

struct READDIR3resfail {
	post_op_attr dir_attributes;
};
typedef struct READDIR3resfail READDIR3resfail;

struct READDIR3res {
	nfsstat3 status;
	union {
		READDIR3resok ok;
		READDIR3resfail fail;
	} res_u;
};
typedef struct READDIR3res READDIR3res;

struct READDIRPLUS3args {
	nfs_fh3 dir;
	cookie3 cookie;
	cookieverf3 cookieverf;
	count3 dircount;
	count3 maxcount;
};
typedef struct READDIRPLUS3args READDIRPLUS3args;

struct entryplus3 {
	fileid3 fileid;
	filename3 name;
	cookie3 cookie;
	post_op_attr name_attributes;
	post_op_fh3 name_handle;
	struct entryplus3 *nextentry;
};
typedef struct entryplus3 entryplus3;

struct dirlistplus3 {
	entryplus3 *entries;
	bool_t eof;
};
typedef struct dirlistplus3 dirlistplus3;

struct READDIRPLUS3resok {
	post_op_attr dir_attributes;
	cookieverf3 cookieverf;
	dirlistplus3 reply;
	u_int size;
	u_int count;
	u_int maxcount;
	caddr_t xdr_data;	/* Pre-XDRed data ripe to send */
	u_int xdr_size;		/* Size of above */
	/* CJXXX: "extra" stuff not encoded/decoded */
	off_t offset;		/* Dir offset of first entry if server, last
				 * entry if client.
				 */
};
typedef struct READDIRPLUS3resok READDIRPLUS3resok;

struct READDIRPLUS3resfail {
	post_op_attr dir_attributes;
};
typedef struct READDIRPLUS3resfail READDIRPLUS3resfail;

struct READDIRPLUS3res {
	nfsstat3 status;
	union {
		READDIRPLUS3resok ok;
		READDIRPLUS3resfail fail;
	} res_u;
};
typedef struct READDIRPLUS3res READDIRPLUS3res;

struct FSSTAT3args {
	nfs_fh3 fsroot;
};
typedef struct FSSTAT3args FSSTAT3args;

struct FSSTAT3resok {
	post_op_attr obj_attributes;
	size3 tbytes;
	size3 fbytes;
	size3 abytes;
	size3 tfiles;
	size3 ffiles;
	size3 afiles;
	uint32 invarsec;
};
typedef struct FSSTAT3resok FSSTAT3resok;

struct FSSTAT3resfail {
	post_op_attr obj_attributes;
};
typedef struct FSSTAT3resfail FSSTAT3resfail;

struct FSSTAT3res {
	nfsstat3 status;
	union {
		FSSTAT3resok ok;
		FSSTAT3resfail fail;
	} res_u;
};
typedef struct FSSTAT3res FSSTAT3res;

struct FSINFO3args {
	nfs_fh3 fsroot;
};
typedef struct FSINFO3args FSINFO3args;

struct FSINFO3resok {
	post_op_attr obj_attributes;
	uint32 rtmax;
	uint32 rtpref;
	uint32 rtmult;
	uint32 wtmax;
	uint32 wtpref;
	uint32 wtmult;
	uint32 dtpref;
	size3 maxfilesize;
	nfstime3 time_delta;
	uint32 properties;
};
typedef struct FSINFO3resok FSINFO3resok;

struct FSINFO3resfail {
	post_op_attr obj_attributes;
};
typedef struct FSINFO3resfail FSINFO3resfail;
#define	FSF3_LINK 0x1
#define	FSF3_SYMLINK 0x2
#define	FSF3_HOMOGENEOUS 0x8
#define	FSF3_CANSETTIME 0x10

struct FSINFO3res {
	nfsstat3 status;
	union {
		FSINFO3resok ok;
		FSINFO3resfail fail;
	} res_u;
};
typedef struct FSINFO3res FSINFO3res;

struct PATHCONF3args {
	nfs_fh3 object;
};
typedef struct PATHCONF3args PATHCONF3args;

struct PATHCONF3resok {
	post_op_attr obj_attributes;
	uint32 link_max;
	uint32 name_max;
	bool_t no_trunc;
	bool_t chown_restricted;
	bool_t case_insensitive;
	bool_t case_preserving;
};
typedef struct PATHCONF3resok PATHCONF3resok;

struct PATHCONF3resfail {
	post_op_attr obj_attributes;
};
typedef struct PATHCONF3resfail PATHCONF3resfail;

struct PATHCONF3res {
	nfsstat3 status;
	union {
		PATHCONF3resok ok;
		PATHCONF3resfail fail;
	} res_u;
};
typedef struct PATHCONF3res PATHCONF3res;

struct COMMIT3args {
	nfs_fh3 file;
	offset3 offset;
	count3 count;
};
typedef struct COMMIT3args COMMIT3args;

struct COMMIT3resok {
	wcc_data file_wcc;
	writeverf3 verf;
};
typedef struct COMMIT3resok COMMIT3resok;

struct COMMIT3resfail {
	wcc_data file_wcc;
};
typedef struct COMMIT3resfail COMMIT3resfail;

struct COMMIT3res {
	nfsstat3 status;
	union {
		COMMIT3resok ok;
		COMMIT3resfail fail;
	} res_u;
};
typedef struct COMMIT3res COMMIT3res;

_BEGIN_CPLUSPLUS
#define	NFS3_PROGRAM ((u_long)100003)
#define	NFS_V3 ((u_long)3)
#define	NFSPROC3_NULL ((u_long)0)
extern  void * nfsproc3_null_3();
#define	NFSPROC3_GETATTR ((u_long)1)
extern  GETATTR3res * nfsproc3_getattr_3();
#define	NFSPROC3_SETATTR ((u_long)2)
extern  SETATTR3res * nfsproc3_setattr_3();
#define	NFSPROC3_LOOKUP ((u_long)3)
extern  LOOKUP3res * nfsproc3_lookup_3();
#define	NFSPROC3_ACCESS ((u_long)4)
extern  ACCESS3res * nfsproc3_access_3();
#define	NFSPROC3_READLINK ((u_long)5)
extern  READLINK3res * nfsproc3_readlink_3();
#define	NFSPROC3_READ ((u_long)6)
extern  READ3res * nfsproc3_read_3();
#define	NFSPROC3_WRITE ((u_long)7)
extern  WRITE3res * nfsproc3_write_3();
#define	NFSPROC3_CREATE ((u_long)8)
extern  CREATE3res * nfsproc3_create_3();
#define	NFSPROC3_MKDIR ((u_long)9)
extern  MKDIR3res * nfsproc3_mkdir_3();
#define	NFSPROC3_SYMLINK ((u_long)10)
extern  SYMLINK3res * nfsproc3_symlink_3();
#define	NFSPROC3_MKNOD ((u_long)11)
extern  MKNOD3res * nfsproc3_mknod_3();
#define	NFSPROC3_REMOVE ((u_long)12)
extern  REMOVE3res * nfsproc3_remove_3();
#define	NFSPROC3_RMDIR ((u_long)13)
extern  RMDIR3res * nfsproc3_rmdir_3();
#define	NFSPROC3_RENAME ((u_long)14)
extern  RENAME3res * nfsproc3_rename_3();
#define	NFSPROC3_LINK ((u_long)15)
extern  LINK3res * nfsproc3_link_3();
#define	NFSPROC3_READDIR ((u_long)16)
extern  READDIR3res * nfsproc3_readdir_3();
#define	NFSPROC3_READDIRPLUS ((u_long)17)
extern  READDIRPLUS3res * nfsproc3_readdirplus_3();
#define	NFSPROC3_FSSTAT ((u_long)18)
extern  FSSTAT3res * nfsproc3_fsstat_3();
#define	NFSPROC3_FSINFO ((u_long)19)
extern  FSINFO3res * nfsproc3_fsinfo_3();
#define	NFSPROC3_PATHCONF ((u_long)20)
extern  PATHCONF3res * nfsproc3_pathconf_3();
#define	NFSPROC3_COMMIT ((u_long)21)
extern  COMMIT3res * nfsproc3_commit_3();
_END_CPLUSPLUS

#ifdef _KERNEL

/* the xdr functions */
_BEGIN_CPLUSPLUS
bool_t xdr_uint64 __((XDR *, uint64 *));
bool_t xdr_int64 __((XDR *, int64 *));
bool_t xdr_uint32 __((XDR *, uint32 *));
bool_t xdr_int32 __((XDR *, int32 *));
bool_t xdr_filename3 __((XDR *, filename3 *));
bool_t xdr_nfspath3 __((XDR *, nfspath3 *));
bool_t xdr_fileid3 __((XDR *, fileid3 *));
bool_t xdr_cookie3 __((XDR *, cookie3 *));
bool_t xdr_uid3 __((XDR *, uid3 *));
bool_t xdr_gid3 __((XDR *, gid3 *));
bool_t xdr_size3 __((XDR *, size3 *));
bool_t xdr_offset3 __((XDR *, offset3 *));
bool_t xdr_mode3 __((XDR *, mode3 *));
bool_t xdr_count3 __((XDR *, count3 *));
bool_t xdr_cookieverf3 __((XDR *, cookieverf3));
bool_t xdr_createverf3 __((XDR *, createverf3));
bool_t xdr_writeverf3 __((XDR *, writeverf3));
bool_t xdr_nfs_fh3 __((XDR *, nfs_fh3 *));
bool_t xdr_diropargs3 __((XDR *, diropargs3 *));
bool_t xdr_nfstime3 __((XDR *, nfstime3 *));
bool_t xdr_specdata3 __((XDR *, specdata3 *));
bool_t xdr_nfsstat3 __((XDR *, nfsstat3 *));
bool_t xdr_ftype3 __((XDR *, ftype3 *));
bool_t xdr_fattr3 __((XDR *, fattr3 *));
bool_t xdr_post_op_attr __((XDR *, post_op_attr *));
bool_t xdr_wcc_attr __((XDR *, wcc_attr *));
bool_t xdr_pre_op_attr __((XDR *, pre_op_attr *));
bool_t xdr_wcc_data __((XDR *, wcc_data *));
bool_t xdr_post_op_fh3 __((XDR *, post_op_fh3 *));
bool_t xdr_time_how __((XDR *, time_how *));
bool_t xdr_set_mode3 __((XDR *, set_mode3 *));
bool_t xdr_set_uid3 __((XDR *, set_uid3 *));
bool_t xdr_set_gid3 __((XDR *, set_gid3 *));
bool_t xdr_set_size3 __((XDR *, set_size3 *));
bool_t xdr_set_atime __((XDR *, set_atime *));
bool_t xdr_set_mtime __((XDR *, set_mtime *));
bool_t xdr_sattr3 __((XDR *, sattr3 *));
bool_t xdr_GETATTR3args __((XDR *, GETATTR3args *));
bool_t xdr_GETATTR3resok __((XDR *, GETATTR3resok *));
bool_t xdr_GETATTR3res __((XDR *, GETATTR3res *));
bool_t xdr_sattrguard3 __((XDR *, sattrguard3 *));
bool_t xdr_SETATTR3args __((XDR *, SETATTR3args *));
bool_t xdr_SETATTR3resok __((XDR *, SETATTR3resok *));
bool_t xdr_SETATTR3resfail __((XDR *, SETATTR3resfail *));
bool_t xdr_SETATTR3res __((XDR *, SETATTR3res *));
bool_t xdr_LOOKUP3args __((XDR *, LOOKUP3args *));
bool_t xdr_LOOKUP3resok __((XDR *, LOOKUP3resok *));
bool_t xdr_LOOKUP3resfail __((XDR *, LOOKUP3resfail *));
bool_t xdr_LOOKUP3res __((XDR *, LOOKUP3res *));
bool_t xdr_ACCESS3args __((XDR *, ACCESS3args *));
bool_t xdr_ACCESS3resok __((XDR *, ACCESS3resok *));
bool_t xdr_ACCESS3resfail __((XDR *, ACCESS3resfail *));
bool_t xdr_ACCESS3res __((XDR *, ACCESS3res *));
bool_t xdr_READLINK3args __((XDR *, READLINK3args *));
bool_t xdr_READLINK3resok __((XDR *, READLINK3resok *));
bool_t xdr_READLINK3resfail __((XDR *, READLINK3resfail *));
bool_t xdr_READLINK3res __((XDR *, READLINK3res *));
bool_t xdr_READ3args __((XDR *, READ3args *));
bool_t xdr_READ3resok __((XDR *, READ3resok *));
bool_t xdr_READ3resfail __((XDR *, READ3resfail *));
bool_t xdr_READ3res __((XDR *, READ3res *));
bool_t xdr_stable_how __((XDR *, stable_how *));
bool_t xdr_WRITE3args __((XDR *, WRITE3args *));
bool_t xdr_WRITE3resok __((XDR *, WRITE3resok *));
bool_t xdr_WRITE3resfail __((XDR *, WRITE3resfail *));
bool_t xdr_WRITE3res __((XDR *, WRITE3res *));
bool_t xdr_createmode3 __((XDR *, createmode3 *));
bool_t xdr_createhow3 __((XDR *, createhow3 *));
bool_t xdr_CREATE3args __((XDR *, CREATE3args *));
bool_t xdr_CREATE3resok __((XDR *, CREATE3resok *));
bool_t xdr_CREATE3resfail __((XDR *, CREATE3resfail *));
bool_t xdr_CREATE3res __((XDR *, CREATE3res *));
bool_t xdr_MKDIR3args __((XDR *, MKDIR3args *));
bool_t xdr_MKDIR3resok __((XDR *, MKDIR3resok *));
bool_t xdr_MKDIR3resfail __((XDR *, MKDIR3resfail *));
bool_t xdr_MKDIR3res __((XDR *, MKDIR3res *));
bool_t xdr_symlinkdata3 __((XDR *, symlinkdata3 *));
bool_t xdr_SYMLINK3args __((XDR *, SYMLINK3args *));
bool_t xdr_SYMLINK3resok __((XDR *, SYMLINK3resok *));
bool_t xdr_SYMLINK3resfail __((XDR *, SYMLINK3resfail *));
bool_t xdr_SYMLINK3res __((XDR *, SYMLINK3res *));
bool_t xdr_devicedata3 __((XDR *, devicedata3 *));
bool_t xdr_mknoddata3 __((XDR *, mknoddata3 *));
bool_t xdr_MKNOD3args __((XDR *, MKNOD3args *));
bool_t xdr_MKNOD3resok __((XDR *, MKNOD3resok *));
bool_t xdr_MKNOD3resfail __((XDR *, MKNOD3resfail *));
bool_t xdr_MKNOD3res __((XDR *, MKNOD3res *));
bool_t xdr_REMOVE3args __((XDR *, REMOVE3args *));
bool_t xdr_REMOVE3resok __((XDR *, REMOVE3resok *));
bool_t xdr_REMOVE3resfail __((XDR *, REMOVE3resfail *));
bool_t xdr_REMOVE3res __((XDR *, REMOVE3res *));
bool_t xdr_RMDIR3args __((XDR *, RMDIR3args *));
bool_t xdr_RMDIR3resok __((XDR *, RMDIR3resok *));
bool_t xdr_RMDIR3resfail __((XDR *, RMDIR3resfail *));
bool_t xdr_RMDIR3res __((XDR *, RMDIR3res *));
bool_t xdr_RENAME3args __((XDR *, RENAME3args *));
bool_t xdr_RENAME3resok __((XDR *, RENAME3resok *));
bool_t xdr_RENAME3resfail __((XDR *, RENAME3resfail *));
bool_t xdr_RENAME3res __((XDR *, RENAME3res *));
bool_t xdr_LINK3args __((XDR *, LINK3args *));
bool_t xdr_LINK3resok __((XDR *, LINK3resok *));
bool_t xdr_LINK3resfail __((XDR *, LINK3resfail *));
bool_t xdr_LINK3res __((XDR *, LINK3res *));
bool_t xdr_READDIR3args __((XDR *, READDIR3args *));
bool_t xdr_entry3 __((XDR *, entry3 *));
bool_t xdr_dirlist3 __((XDR *, dirlist3 *));
bool_t xdr_READDIR3resok __((XDR *, READDIR3resok *));
bool_t xdr_READDIR3resok_new __((XDR *, READDIR3resok *));
bool_t xdr_READDIR3resfail __((XDR *, READDIR3resfail *));
bool_t xdr_READDIR3res __((XDR *, READDIR3res *));
bool_t xdr_READDIR3res_new __((XDR *, READDIR3res *));
bool_t xdr_READDIRPLUS3args __((XDR *, READDIRPLUS3args *));
bool_t xdr_entryplus3 __((XDR *, entryplus3 *));
bool_t xdr_dirlistplus3 __((XDR *, dirlistplus3 *));
bool_t xdr_READDIRPLUS3resok __((XDR *, READDIRPLUS3resok *));
bool_t xdr_READDIRPLUS3resok_new __((XDR *, READDIRPLUS3resok *));
bool_t xdr_READDIRPLUS3resfail __((XDR *, READDIRPLUS3resfail *));
bool_t xdr_READDIRPLUS3res __((XDR *, READDIRPLUS3res *));
bool_t xdr_READDIRPLUS3res_new __((XDR *, READDIRPLUS3res *));
bool_t xdr_FSSTAT3args __((XDR *, FSSTAT3args *));
bool_t xdr_FSSTAT3resok __((XDR *, FSSTAT3resok *));
bool_t xdr_FSSTAT3resfail __((XDR *, FSSTAT3resfail *));
bool_t xdr_FSSTAT3res __((XDR *, FSSTAT3res *));
bool_t xdr_FSINFO3args __((XDR *, FSINFO3args *));
bool_t xdr_FSINFO3resok __((XDR *, FSINFO3resok *));
bool_t xdr_FSINFO3resfail __((XDR *, FSINFO3resfail *));
bool_t xdr_FSINFO3res __((XDR *, FSINFO3res *));
bool_t xdr_PATHCONF3args __((XDR *, PATHCONF3args *));
bool_t xdr_PATHCONF3resok __((XDR *, PATHCONF3resok *));
bool_t xdr_PATHCONF3resfail __((XDR *, PATHCONF3resfail *));
bool_t xdr_PATHCONF3res __((XDR *, PATHCONF3res *));
bool_t xdr_COMMIT3args __((XDR *, COMMIT3args *));
bool_t xdr_COMMIT3resok __((XDR *, COMMIT3resok *));
bool_t xdr_COMMIT3resfail __((XDR *, COMMIT3resfail *));
bool_t xdr_COMMIT3res __((XDR *, COMMIT3res *));

/*
 * See nfs_client.c:nfs3_fileid_map for more comments.
 *
 * This typedef is for the type of vattr.va_fileid and ino_t (both ints now)
 */
typedef int nfs_va_fileid_t;
nfs_va_fileid_t nfs3_fileid_map(struct vnode *, fileid3);
fileid3 nfs3_fileid_unmap(struct vnode *);
#define	NFS3_FILEID_MARK_BITS	1
#define	NFS3_FILEID_KEEP_BITS	((sizeof(nfs_va_fileid_t) * 8) -	\
				 NFS3_FILEID_MARK_BITS)
#define	NFS3_FILEID_KEEP_MASK	((1L << NFS3_FILEID_KEEP_BITS) - 1)
#define	NFS3_FILEID_MARK_MASK	(((1L << (NFS3_FILEID_KEEP_BITS +	\
					  NFS3_FILEID_MARK_BITS)) - 1) &\
				 ~NFS3_FILEID_KEEP_MASK)
#define	NFS3_FILEID_MAP(_id)	(((_id) >> NFS3_FILEID_KEEP_BITS) ? 	      \
				 (nfs_va_fileid_t) (((_id) & 		      \
						     NFS3_FILEID_KEEP_MASK) | \
						    NFS3_FILEID_MARK_MASK) :  \
				 (nfs_va_fileid_t) (_id))

int sattr3_to_vattr(struct sattr3 *, struct vattr *, bool_t);
enum nfsstat3 puterrno3(int);
int geterrno3(enum nfsstat3);
void setdiropargs3(struct diropargs3 *, struct nameidata *);
#ifdef __DECC
void fattr3_to_vattr(struct vnode *, fattr3 *__restrict, struct vattr *__restrict);
#else
void fattr3_to_vattr(struct vnode *, fattr3 *, struct vattr *);
#endif
void nfs3_attrcache(struct vnode *, struct fattr3 *);
int nfs3_cache_check(struct vnode *, struct wcc_attr *);
int nfs3_cache_check_fattr3(struct vnode *, struct fattr3 *);
void nfs3_cache_post_op_attr(struct vnode *, post_op_attr *);

int	rfscall(struct mntinfo *mi, int which, xdrproc_t xdrargs, caddr_t argsp, xdrproc_t xdrres, caddr_t resp, struct ucred *cred);
int	rfs3call(struct mntinfo *mi, int which, xdrproc_t xdrargs, caddr_t argsp, xdrproc_t xdrres, caddr_t resp, struct ucred *cred, enum nfsstat3 *statusp);

/*
 * Write handling.
 */
void nfs3_xmitdone(caddr_t addr, u_int size, struct buf *bp);
int nfs_write_pgcksum(struct mbuf *m, int size);
_END_CPLUSPLUS

/*
 * Definitions for macros used to manipulate the SMP locks for the 
 * NFS subsystem.  They are placed in this file because the locks are
 * frequently accessed in more than one file.  The most common example is
 * that most of the locks are init'ed in nfs_hooks.c and then taken out
 * and released in nfs_server.c for example.
 */
/* SMP locking of exports list */
udecl_simple_lock_data(extern, nfs_export_lock)
udecl_simple_lock_info(extern, nfs_export_lockinfo)

#define NFS_EXPORT_LOCKINIT()     usimple_lock_setup(&nfs_export_lock,\
						  nfs_export_lockinfo)
#define NFS_EXPORT_LOCK()     usimple_lock(&nfs_export_lock)
#define NFS_EXPORT_UNLOCK()   usimple_unlock(&nfs_export_lock)

udecl_simple_lock_data(extern, nfs_rrok_lock)
udecl_simple_lock_info(extern, nfs_rrok_lockinfo)
#define NFS_RROK_LOCKINIT()     usimple_lock_setup(&nfs_rrok_lock, nfs_rrok_lockinfo)
#define NFS_RROK_LOCK()     usimple_lock(&nfs_rrok_lock)
#define NFS_RROK_UNLOCK()   usimple_unlock(&nfs_rrok_lock)

udecl_simple_lock_data(extern, nfs_w3ok_lock)
udecl_simple_lock_info(extern, nfs_w3ok_lockinfo)
#define NFS_W3OK_LOCKINIT() usimple_lock_setup(&nfs_w3ok_lock, nfs_w3ok_lockinfo)
#define NFS_W3OK_LOCK()     usimple_lock(&nfs_w3ok_lock)
#define NFS_W3OK_UNLOCK()   usimple_unlock(&nfs_w3ok_lock)

udecl_lock_data(extern, chtabhead_lock)
udecl_lock_info(extern, chtabhead_lockinfo)
#define CHTABHEAD_LOCKINIT()	\
		ulock_setup(&chtabhead_lock, chtabhead_lockinfo, TRUE)
#define CHTABHEAD_READ_LOCK()	ulock_read(&chtabhead_lock)
#define CHTABHEAD_WRITE_LOCK()	ulock_write(&chtabhead_lock)
#define	CHTABHEAD_UNLOCK() 	ulock_done(&chtabhead_lock)

udecl_simple_lock_info(extern, chlist_lockinfo)
#define CHLIST_LOCKINIT(chdp)	\
		usimple_lock_setup(&(chdp)->ch_lock, chlist_lockinfo)
#define CHLIST_LOCK(chdp)	usimple_lock(&(chdp)->ch_lock)
#define	CHLIST_UNLOCK(chdp) 	usimple_unlock(&(chdp)->ch_lock)
#define CHLIST_LOCKTERMINATE(chdp) usimple_lock_terminate(&(chdp)->ch_lock)

udecl_simple_lock_data(extern, nfs_tslist_lock)
udecl_simple_lock_info(extern, nfs_tslist_lockinfo)
#define TSLIST_LOCKINIT()     usimple_lock_setup(&nfs_tslist_lock, nfs_tslist_lockinfo)
#define TSLIST_LOCK()     usimple_lock(&nfs_tslist_lock)
#define TSLIST_UNLOCK()   usimple_unlock(&nfs_tslist_lock)

/*
 * Rnodehash struct, lock defines:
 */
struct rnodehash {
	udecl_simple_lock_data(,rn_lock)
	struct rnode * rn_hash;
};
extern struct rnodehash *rtable;	/* The rnode hash table */

udecl_simple_lock_info(extern, rnodehash_lockinfo)
#define RNODEHASH_LOCK_INIT(rn) usimple_lock_setup( &rn->rn_lock, \
							rnodehash_lockinfo)
#define RNODEHASH_LOCK(rn) usimple_lock( &rn->rn_lock)
#define RNODEHASH_UNLOCK(rn) usimple_unlock( &rn->rn_lock)

#endif	/* _KERNEL */

#endif /* !__NFS_HEADER__ */

