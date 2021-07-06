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
 * 
 */
/*	
 *	@(#)$RCSfile: mount.h,v $ $Revision: 4.3.231.4 $ (DEC) $Date: 2002/05/16 14:03:29 $	
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
 * Copyright (C) 1988,1989 Encore Computer Corporation.  All Rights Reserved
 *
 * Property of Encore Computer Corporation.
 * This software is made available solely pursuant to the terms of
 * a software license agreement which governs its use. Unauthorized
 * duplication, distribution or sale are strictly prohibited.
 *
 */
/*
 * Copyright (c) 1989 The Regents of the University of California.
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

#ifndef	_SYS_MOUNT_H_
#define _SYS_MOUNT_H_

#include <standards.h>
#include <sys/types.h>
#include <sys/unix_defs.h>
#include <kern/lock.h>
#include <sys/secdefines.h>
#if	SEC_ARCH
#include <sys/security.h>
#endif 
#ifdef	_KERNEL
#include <ser_compat.h>
#endif

#if defined(_KERNEL) && defined(__V40_OBJ_COMPAT)
#  undef __V40_OBJ_COMPAT  /* The kernel is always built with _F64_ support */
#endif

#ifndef _KERNEL
#if defined(_NO_PROTO) || defined(__SVID__)
extern int mount();
extern int umount();
#else /* _NO_PROTO || __SVID__ */
_BEGIN_CPLUSPLUS
extern int mount( int, char *, u_long, caddr_t );
extern int umount( char *, int );
extern int sync2( uint, char * );
_END_CPLUSPLUS
#endif /* _NO_PROTO */
#endif /* _KERNEL */

/*
 * File system types.
 *
 * WARNING:
 *	These constants serve as indexes for the filesystem name in the
 *	mnt_names[] array in sys/fs_types.h.  Any changes to these
 *	constants should be reflected in the definition of the mnt_names[]
 *	array in this file so that the filesystem name is always indexed
 *	by the associated constant.
 */
#define	MOUNT_NONE	0
#define	MOUNT_UFS	1
#define	MOUNT_NFS	2
#define MOUNT_MFS	3
#define	MOUNT_PC	4
#define MOUNT_S5FS	5
#define MOUNT_CDFS	6
#define MOUNT_DFS       7         /* DCE DFS */
#define MOUNT_EFS       8         /* DCE Episode FS */
#define MOUNT_PROCFS	9
#define	MOUNT_MSFS	10
#define MOUNT_FFM       11
#define MOUNT_FDFS	12	/* Generic file system type */
#define MOUNT_ADDON	13
#define MOUNT_NFS3	14	/* NFS v3 */
#define MOUNT_CFS	15	/* Cluster File System */
#define MOUNT_CSPEC	16	/* Cluster Spec File System */
#define MOUNT_DVDFS	17
#define MOUNT_AUTOFS	18
#define MOUNT_MAXTYPE	18
#define MOUNT_NUMTYPES	(MOUNT_MAXTYPE+1)


#define MNAMELEN 90	/* length of buffer for returned name */

typedef quad fsid_t;	/* file system id type */

/*
 * File identifier (fid).
 * These are unique per filesystem on a single machine.
 * There is a length restriction imposed by the NFS version 2 file handle size
 * of 32 bytes. It is possible to extend this restriction with NFS version 3
 * where file handles can reach 64 byte sizes.
 * There is, as yet, no support for extended fids.
 *
 * Work backwards from the V2 restriction:
 */

/*
 * Size of an NFS fhandle (V2) in bytes
 */
#define	NFS_FHSIZE	32

/*
 * File access handle
 * This structure is the DEC/OSF NFS server representation of a file.
 * It is handed out by a server for the client to use in further
 * file transactions. It must contain a file system ID and two fids.
 */

/*
 * This struct is only used to find the maximum size of the data field in the
 * fhandle structure below.
 */
struct nfsfhsize {
	fsid_t	f1;
	u_short	f2;
	u_short	f3;
	char	f4[4];
	u_short	f5;
	u_short	f6;
	char	f7[4];
};

/* Warning!    
 *      NFS_FHMAXDATA   MUST! be a multiple of 4 bytes (32 bits)
 * This allows fs code that gets a fid_t pointer to stuff ints without
 * getting unaligned access traps.
 */
#define	NFS_FHMAXDATA	((NFS_FHSIZE - sizeof (struct nfsfhsize) + 8) / 2)

struct fid {
	u_short		fid_len;		 /* length of data in bytes */
	u_short		fid_reserved;		 /* force 32 bit alignment */
	char		fid_data[NFS_FHMAXDATA]; /* data (variable length) */
	/* MUST END ON A 4-byte BOUNDARY */
};

typedef struct fid fid_t;

struct svcfh{
	fsid_t	fh_fsid; /* filesystem id */
	fid_t   fh_fid;  /* Id of file */
	fid_t   fh_efid; /* Id of export granting directory */
};

struct nfssvcfh {
	union nfssvcfh_u {
		struct	svcfh svcfh_i;
		u_char	data[NFS_FHSIZE];
	} svcfh_u;
};

typedef struct nfssvcfh fhandle_t;

#define	fh_fsid	svcfh_u.svcfh_i.fh_fsid
#define	fh_fid	svcfh_u.svcfh_i.fh_fid	
#define	fh_efid	svcfh_u.svcfh_i.fh_efid
#define	fh_data svcfh_u.data

/* fid support stuff */
#define fsid_equal(fsid1,fsid2) \
(bcmp((caddr_t)(fsid1), (caddr_t)(fsid2), sizeof(fsid_t))==0)  

#define fid_equal(fid1,fid2) \
((fid1)->fid_len == (fid2)->fid_len &&\
bcmp(&(fid1)->fid_reserved, &(fid2)->fid_reserved, (fid1)->fid_len - sizeof(short))==0)

#define fid_copy(fid1,fid2) \
if ((fid1)->fid_len > sizeof(fid_t) || (fid1)->fid_len < 2*sizeof(short) )\
	panic("improper fid size");\
bcopy((caddr_t)(fid1), (caddr_t)(fid2), (fid1)->fid_len);

#define fsid_copy(fsid1,fsid2) \
bcopy((caddr_t)(fsid1), (caddr_t)(fsid2), sizeof(fsid_t))  

#define fsid_print(fs) \
printf("%x,%x\n", *(int *)(fs), *((int *)(fs)+1))

#define fid_print(fid) \
if ((fid)) { \
int i; \
printf("len %d, reserved %x, data", (fid)->fid_len, (fid)->fid_reserved); \
for (i = 0; i < NFS_FHMAXDATA; i++)  \
	printf(" %x",(fid)->fid_data[i]); \
printf("\n"); \
} else printf("can not print null fid\n");

/*
 * Arguments to mount UFS
 */
struct ufs_args {
        char    *fspec;         /* block special device to mount */
        int     exflags;        /* export related flags */
        uid_t   exroot;         /* mapping for root uid */
};

/*
 * Arguments to mount AdvFS (via mount(2))
 */
struct advfs_args {
        char		*fspec;         /* block special device to mount */
	int		exflags;        /* export related flags */
        uid_t		exroot;         /* mapping for root uid */
	unsigned int	fsid;		/* Potential file set id/dev */
};

typedef struct map_id {
	ushort  old_id; /* 16b value */
	uid_t   new_id; /* 32b value */
} map_id;

#define	CDFS_EXTENDED_ARGS_VERSION	1

/*
 * Arguments to mount CDFS
 */
struct cdfs_args {
        char    *fspec;         /* block special device to mount */
        int     exflags;        /* export related flags */
        uid_t   exroot;         /* mapping for root uid */
	int	flags;		/* CDFS mount options */
	int	version;	/* M_EXTENDED_ARGS: version of struct */
	uid_t	default_uid;	/* M_DEFUID: default uid if no xar */
	gid_t	default_gid;	/* M_DEFGID: default gid if no xar */
	mode_t	default_fmode;	/* M_DEFFMODE: default file mode if no xar */
	mode_t	default_dmode;	/* M_DEFDMODE: default dir mode if no xar */
	int	map_uid_ct;	/* M_MAPUID: #map_uids */
	map_id	*map_uid;	/* ptr to map_uid 2D array */
	int	map_gid_ct;	/* M_MAPGID: #map_gids */
	map_id	*map_gid;	/* ptr to map_gid 2D array */
};

/*
 * Arguments to mount DVDFS
 */
struct dvdfs_args {
        char    *fspec;         /* block special device to mount */
        uint_t  exflags;        /* export related flags */
        uid_t   exroot;         /* mapping for root uid */
};

/*
 * Arguments to mount System V file system
 */
struct s5fs_args {
        char    *fspec;         /* block special device to mount */
        int     exflags;        /* export related flags */
        uid_t   exroot;         /* mapping for root uid */
};

/*
 * Arguments to mount MFS
 */
struct mfs_args {
        char    *name;          /* name to export for statfs */
        caddr_t base;           /* base address of file system in memory */
        long    size;           /* size of file system */
};

/*
 * Arguments to mount /proc file system
 */
struct procfs_args {
        char    *fspec;         /* block special device to mount */
        int     exflags;        /* export related flags */
        uid_t   exroot;         /* mapping for root uid */
};

/* Arguments for file-on-file mount */
struct ffm_args {
	int   ffm_flags;                      /* operational flags */
	union {
	    char    *ffm_pname;             /* pathname to mount */
	    int     ffm_fdesc;              /* file descriptor to mount */
        } f_un;
};

#define ffm_pathname f_un.ffm_pname     /* shorthand */
#define ffm_filedesc f_un.ffm_fdesc     /* shorthand */

#define FFM_FD          0x000000001     /* file descriptor supplied */
#define FFM_CLONE       0x000000002     /* clone should be performed */

#define AUTOFS_MAP_LENGTH 60
#define AUTOFS_OPT_LENGTH 60
#define AUTOFS_DIR_LENGTH 90

struct autofs_args {
	unsigned int	autofs_direct  : 1;
	unsigned int	autofs_symlink : 1;
	unsigned int	autofs_symlen  : 16;		/* <= MAXPATHLEN */
	unsigned int    autofs_compressed : 1;
	unsigned int	autofs_zero    : 13;
	char		autofs_map[AUTOFS_MAP_LENGTH];
	char		autofs_opt[AUTOFS_OPT_LENGTH];
	char            autofs_mapkey[AUTOFS_DIR_LENGTH];
	char *		autofs_symtarget;		/* Symlink target path*/
};

/*
 * This structure must be no more than 80 bytes for binary compatibility.
 * The map name can be found in f_mntfromnane.
 */
struct autofs_mi_args {
	int	autofs_direct;
	char	autofs_opt[AUTOFS_OPT_LENGTH];
};


/*
 * File Handle (32 bytes for version 2), variable up to 1024 for version 3
 */
union nfsv2fh {
        fhandle_t       fh_generic;
        u_char          fh_bytes[32];
};
typedef union nfsv2fh nfsv2fh_t;

/* forward decls for ANSI & C++ */
struct sockaddr_in;
struct pathcnf;

/*
 * Arguments to mount NFS
 */
struct nfs_args {
        struct sockaddr_in      *addr;          /* file server address */
        caddr_t 		fh;		/* File handle to be mounted */
        int                     flags;          /* flags */
        int                     wsize;          /* write size in bytes */
        int                     rsize;          /* read size in bytes */
        int                     timeo;          /* initial timeout in .1 secs */
        int                     retrans;        /* times to retry send */
	int                     maxtimo;        /* retransmission timeout */
        char                    *hostname;      /* server's name */
        int                     acregmin;       /* min secs for file attrcache*/
        int                     acregmax;       /* max secs for file attrcache*/
        int                     acdirmin;       /* min secs for dir attrcache */
        int                     acdirmax;       /* max secs for dir attrcache */
        char                    *netname;       /* server's netname */
	struct pathcnf		*pathconf;	/* static pathconf kludge */
};

/*
 * NFS mount option flags
 */
#define NFSMNT_SOFT     0x001   /* soft mount (hard is default) */
#define NFSMNT_WSIZE    0x002   /* set write size */
#define NFSMNT_RSIZE    0x004   /* set read size */
#define NFSMNT_TIMEO    0x008   /* set initial timeout */
#define NFSMNT_RETRANS  0x010   /* set number of request retrys */
#define NFSMNT_HOSTNAME 0x020   /* set hostname for error printf */
#define NFSMNT_INT      0x040   /* allow interrupts on hard mount */
#define NFSMNT_NOCONN   0x080   /* no connect on mount - any responder */
#define NFSMNT_NOAC     0x0100  /* don't cache attributes */
#define NFSMNT_ACREGMIN 0x0200  /* set min seconds for file attr cache  */
#define NFSMNT_ACREGMAX 0x0400  /* set max seconds for file attr cache  */
#define NFSMNT_ACDIRMIN 0x0800  /* set min seconds for dir attr cache   */
#define NFSMNT_ACDIRMAX 0x01000 /* set max seconds for dir attr cache   */
#define NFSMNT_NOCTO    0x02000  /* don't freshen attributes on open */
#define NFSMNT_POSIX	0x04000	/* static pathconf kludge info */
#define NFSMNT_AUTO	0x08000	/* automount file system */
#define NFSMNT_SEC      0x010000 /* MLS+ secure mount */
#define NFSMNT_TCP	0x020000 /* TCP transport, not UDP */
#define NFSMNT_PROPLIST 0x040000 /* allow property list operations */
#define NFSMNT_CLUSTER  0x080000 /* mount occurring in a cluster */
#define NFSMNT_MAXTIMO  0x0100000 /* retransmission timeout */
#define NFSMNT_AUTOFS	0x0200000 /* automounted by AutoFS file system */
#define NFSMNT_AUTOMNT	0x0400000 /* automounted by automount */

/*                   
 * MSFS - mountinfo
 */                  
                                                               /* msfs */
struct msfs_id {                                               /* msfs */
    int id1;                                                   /* msfs */
    int id2;                                                   /* msfs */
    int tag;                                                   /* msfs */
};                                                             /* msfs */
                                                               /* msfs */
struct msfs_args {                                             /* msfs */
    struct msfs_id id;                                         /* msfs */
};                                                             /* msfs */

/*
 * file system statistics
 */

union mount_info {		/* mount options */
	struct ufs_args ufs_args;
	struct nfs_args nfs_args;
	struct mfs_args mfs_args;
	struct cdfs_args cdfs_args;
	struct dvdfs_args dvdfs_args;
	struct procfs_args procfs_args;
        struct msfs_args msfs_args;                     /* msfs */
	struct ffm_args ffm_args;			/* ffm */
	struct autofs_mi_args autofs_args;		/* autofs */
};


/*
 * mount argument stacks
 */

typedef struct mount_xargs_stack*   mount_xargs_stack_t;

typedef struct mount_xargs {
	int       mnt_type;
	u_long    mnt_flag;
	caddr_t   data;
} mount_xargs_t;

/* import id of an empty stack */
#define MOUNT_XARGS_EMPTY_IMPORTID   (0L)

extern int
mount_xargs_export( mount_xargs_stack_t xargs,
                    u_long*             pimportid );

extern int
mount_xargs_free( mount_xargs_stack_t* pxargs );

extern int
mount_xargs_import( mount_xargs_stack_t* pxargs,
                    u_long               importid );

extern int
mount_xargs_push( mount_xargs_stack_t* pxargs,
                  int                  mnt_type,
                  u_long               mnt_flag,
                  caddr_t              data,
                  int                  datasz );

extern int
mount_xargs_top( mount_xargs_stack_t xargs,
                 mount_xargs_t*      mnt_args );


/*
 * extra non-filesystem-specific arguments
 */

/* argument types */
#define MOUNT_XBASE   10000   /* should be above MOUNT_NUMTYPES */

#define MOUNT_XCFS    (MOUNT_XBASE + 1)  /* extra CFS arguments */



/*
 * statfs structure.
 */

#define __F64_STATFS \
        short   f_type;                 /* type of filesystem (see below) */ \
        short   f_flags;                /* copy of mount flags & M_VISFLAGMASK */ \
        int     f_retired1;                                                  \
        int     f_retired2;                                                  \
        int     f_retired3;                                                  \
        int     f_retired4;                                                  \
        int     f_retired5;                                                  \
        int     f_retired6;                                                  \
        int     f_retired7;                                                  \
        fsid_t  f_fsid;                 /* file system id */                 \
        u_short f_namemax;              /* maximum filename length;statvfs*/ \
        short   f_reserved1;            /* spare or grow f_namemax later */  \
        int     f_spare[8];             /* spare for later */                \
        char    f_retired8[90];                                              \
        char    f_retired9[90];                                              \
        union mount_info mount_info;    /* mount options */                  \
        u_long  f_flags2;               /* extended f_flags field */         \
        long    f_spare2[14];           /* spare for later */                \
        long    f_fsize;                /* fundamental fs block size */      \
        long    f_bsize;                /* optimal transfer block size */    \
        long    f_blocks;               /* total data blocks in fs, note: */ \
                                        /*    may not represent fs size. */  \
        long    f_bfree;                /* free blocks in fs */              \
        long    f_bavail;               /* free blocks avail to non-root */  \
                                        /*    Note: value is allowed to be*/ \
                                        /*          negative on file sys */  \
                                        /*          that reserve space */    \
                                        /*          for super user only. */  \
                                        /*          UFS for example. */      \
        long    f_files;                /* total file nodes in fs */         \
        long    f_ffree;                /* free file nodes in fs */          \
        char    f_mntonname[MAXPATHLEN];                                     \
        char    f_mntfromname[MAXPATHLEN];


#define __PRE_F64_STATFS \
        short   f_type;                 /* type of filesystem (see below) */ \
        short   f_flags;                /* copy of mount flags */            \
        int     f_fsize;                /* fundamental fs block size */      \
        int     f_bsize;                /* optimal transfer block size */    \
        int     f_blocks;               /* total data blocks in fs, note: */ \
                                        /*    may not represent fs size. */  \
        int     f_bfree;                /* free blocks in fs */              \
        int     f_bavail;               /* free blocks avail to non-root */  \
                                        /*    Note: value is allowed to be*/ \
                                        /*          negative on file sys */  \
                                        /*          that reserve space */    \
                                        /*          for super user only. */  \
                                        /*          UFS for example. */      \
        int     f_files;                /* total file nodes in fs */         \
        int     f_ffree;                /* free file nodes in fs */          \
        fsid_t  f_fsid;                 /* file system id */                 \
        u_short f_namemax;              /* maximum filename length;statvfs*/ \
        short   f_reserved1;            /* spare or grow f_namemax later */  \
        int     f_spare[8];             /* spare for later */                \
        char    f_mntonname[MNAMELEN];  /* directory on which mounted */     \
        char    f_mntfromname[MNAMELEN];/* mounted filesystem */             \
        union mount_info mount_info;    /* mount options */


#if ! defined(__V40_OBJ_COMPAT)
  struct statfs {               
        __F64_STATFS
  };
#else /* __V40_OBJ_COMPAT */
  struct statfs {               
        __PRE_F64_STATFS        /* Old V4.0 Compatible statfs structure */
  };
#endif /* __V40_OBJ_COMPAT */


#if defined(_KERNEL)
  struct __pre_F64_statfs {             
        __PRE_F64_STATFS /* supports backward compatibility in kernel builds */
  };
#endif /* _KERNEL */


/*
 * The following comments are for kernel developers.  Users should refer to
 * the statfs man page and Digital UNIX documentation for proper use of the
 * statfs functions. 
 *
 * Transparently to users, rename any references to statfs(), fstatfs(),
 * getfsstat(), getmntinfo() and getmntinfo_r() so that they call the
 * _F64_xxx() versions of these routines.  The _F64_xxx() versions return
 * the larger statfs structure.  This should be transparent to the user. 
 * Users should _NOT_ reference the _F64_xxx() names directly.  Users should
 * call statfs(), fstatfs(), getfsstat(), getmntinfo() and getmntinfo_r() as
 * usual and allow this mount.h header file to perform the necessary
 * function renaming.  This will allow user code to remain portable. 
 */
#define __F64(__dname__) __dname__      /* default to a no-op */
#define __F64__(__args__) ()            /* default K&R style func prototypes */
#if defined(_KERNEL)
# if defined(__V40_OBJ_COMPAT)
#    error "__V40_OBJ_COMPAT must NOT be defined if _KERNEL defined"
# endif /* __V40_OBJ_COMPAT */
#else /* ! _KERNEL */
/*
 * Determine if ANSI C or K&R style function prototypes are to be used.
 */
# if ! defined(_NO_PROTO) && ! defined(__SVID__)
#   undef  __F64__
#   define __F64__(__args__) __args__
#   define __F64_CPLUSPLUS
    _BEGIN_CPLUSPLUS
# endif /* _NO_PROTO || __SVID__ */
/*
 * The user can ask (via __V40_OBJ_COMPAT) that this module be compiled so
 * that the statfs structure and the statfs(), fstatfs(), getfsstat(),
 * getmntinfo() and getmntinfo_r() routines used will be compatible with old
 * object modules and libraries generated on Digital UNIX V4.0 (or earlier).
 * This is useful when old object modules and libraries are linked with
 * newly compiled object modules _AND_ there is a need to pass statfs
 * structures between these modules.  Otherwise using __V40_OBJ_COMPAT is
 * not recommended. 
 *
 * If __V40_OBJ_COMPAT is defined, then skip the next section.
 */
# if ! defined(__V40_OBJ_COMPAT)
  /*
   * Rename statfs(), fstatfs(), getfsstat(), getmntinfo() and
   * getmntinfo_r() to the _F64_xxx() family.
   *
   * NOTE:  libc does its own renaming and inside the kernel the renaming 
   *        is not needed.
   */
# if ! defined(_LIBC_POLLUTION_H_) && ! defined(_KERNEL)
#     if defined(__DECC)
        /* 
         * While extern_prefix "_F64_" is in effect, all function prototypes
         * the DECC compiler sees will be marked so that any future uses of
         * that function during this compile will generate a call that has
         * "_F64_" as a prefix to its name.
         */ 
#       pragma extern_prefix "_F64_"
#     else /* ! __DECC */
        /* 
         * Renaming for compilers that do not support the extern_prefix
         * pragma.  Where 'inline' is supported, use it to allow the 2 and 3
         * argument forms of statfs() and fstatfs().  Use a static jacket
         * for other compilers. 
         */
#       if defined(_NO_PROTO)
#         define __F64_NO_PROTO static
#       elif defined(__cplusplus)
#         define __F64_USE_JACKET inline
#       elif defined(__GNUC__)
#         define __F64_USE_JACKET __inline__ static
#       else
#         define __F64_USE_JACKET static
#       endif

#       define getfsstat(__a,__b,__c)        _F64_getfsstat(__a,__b,__c)
#       define getmntinfo(__a,__b)           _F64_getmntinfo(__a,__b)
#       define getmntinfo_r(__a,__b,__c,__d) _F64_getmntinfo_r(__a,__b,__c,__d)
#       undef  __F64
#       define __F64(__dname__) _F64_##__dname__ /* prefix _F64_ to func name */
#     endif /* __DECC */
#   endif /* _LIBC_POLLUTION_H_ */
# endif /* ! __V40_OBJ_COMPAT */
/*
 * Define the function prototypes for statfs(), fstatfs(), getfsstat(),
 * getmntinfo() and getmntinfo_r().  The __F64__((...)) macro is use to
 * control whether ANSI C or K&R style function prototypes are declared. 
 */
  extern int __F64(statfs)    __F64__((char *, struct statfs *, ...));
  extern int __F64(fstatfs)   __F64__((int, struct statfs *, ...));
  extern int __F64(getfsstat) __F64__((struct statfs[], long, int));

# ifdef _OSF_SOURCE
    extern int __F64(getmntinfo)   __F64__((struct statfs **,int));
    extern int __F64(getmntinfo_r) __F64__((struct statfs **,int,int *,int *));
# else /* ! _OSF_SOURCE */
    extern int __F64(getmntinfo)   __F64__(());
    extern int __F64(getmntinfo_r) __F64__(());
# endif /* _OSF_SOURCE */

# if defined(__F64_USE_JACKET)
    __F64_USE_JACKET int statfs(char *__a, struct statfs *__b, ...) {
      return(_F64_statfs(__a,__b));
    }
    __F64_USE_JACKET int fstatfs(int __a, struct statfs *__b, ...) {
      return(_F64_fstatfs(__a,__b));
    }
#   undef __F64_USE_JACKET
# endif /* __F64_USE_JACKET */

# if defined(__F64_NO_PROTO)
    __F64_NO_PROTO int statfs(__a,__b) char *__a; struct statfs *__b; {
      return(_F64_statfs(__a,__b));
    }
    __F64_NO_PROTO int fstatfs(__a,__b) int __a; struct statfs *__b; {
      return(_F64_fstatfs(__a,__b));
    }
#   undef __F64_NO_PROTO
# endif /* __F64_NO_PROTO */
/*
 * clean up
 */
# if defined(__DECC)
#   pragma extern_prefix ""     /* do not mark any more function prototypes */
# endif /* __DECC */
# if defined(__F64_CPLUSPLUS)
    _END_CPLUSPLUS
#   undef __F64_CPLUSPLUS
# endif /* __F64_CPLUSPLUS */
#endif /* _KERNEL */
#undef __F64
#undef __F64__


/*
 * Limit on length of pathname arguments for mounting
 *
*/
#define MAX_MNT_PATHLEN MNAMELEN

/*
 *  statfs as used within the mount structure.
 */
struct nstatfs {
        short   f_type;                 /* type of filesystem (see below) */
        short   f_flags;                /* copy of mount flags & M_VISFLAGMASK */
        long    f_fsize;                /* fundamental filesystem block size */
        long    f_bsize;                /* optimal transfer block size */
        long    f_blocks;               /* total data blocks in fs, note: */
                                        /*    may not represent fs size. */
        long    f_bfree;                /* free blocks in fs */
        long    f_bavail;               /* free blocks avail to non-root */
                                        /*    Note: value is allowed to be*/
                                        /*          negative on file sys */
                                        /*          that reserve space */
                                        /*          for super user only. */
                                        /*          UFS for example. */
        long    f_files;                /* total file nodes in fs */
        long    f_ffree;                /* free file nodes in fs */
        fsid_t  f_fsid;                 /* file system id */
        u_long  f_flags2;               /* extended f_flags field */
        u_short f_namemax;              /* maximum filename length (statvfs) */
        short   f_reserved1;            /* spare or grow f_namemax later */
        int     f_spare2;               /* spare int for later */
        long    f_spare[1];             /* for use later -- must be longs */
        char    *f_mntonname;           /* pointer to directory mounted on */
        char    *f_mntfromname;         /* pointer to mounted filesystem */
        union mount_info mount_info;    /* mount options */     
};


/* forward decls for ANSI & C++ */
struct vfsops;
struct mount;
struct vnode;
struct nameidata;

/*
 * Structure per mounted file system.
 * Each mounted file system has an array of
 * operations and an instance record.
 * The file systems are put on a doubly linked list.
 */
struct mount {
	udecl_simple_lock_data(,m_lock)		/* multiprocessor exclusion */
	u_long		m_flag;			/* flags */
	int		m_funnel;		/* serial code compatibility */
	struct mount	*m_nxt;			/* next in mount list */
	struct mount	*m_prev;		/* prev in mount list */
	struct vfsops	*m_op;			/* operations on fs */
	struct vnode	*m_vnodecovered;	/* vnode we mounted on */
	struct vnode	*m_mounth;		/* list of vnodes this mount */
	udecl_simple_lock_data(,m_vlist_lock)	/* protect vnode list */
	uid_t		m_exroot;		/* exported mapping for uid 0 */
	uid_t		m_uid;			/* uid that performed mount */
	struct nstatfs	m_stat;			/* cache of stats (getfsstat) */
	qaddr_t		m_info;			/* private data */
	/* information used to control NFS server console error messages */
	struct {
		int n_noexport;	/* # of no export messages */
		int last_noexport;	/* secs. since last no export msg */
		int n_stalefh;	/* # of stale fh messages */
		int last_stalefh;	/* secs. since last stale fh msg */
	} m_nfs_errmsginfo;
#if	SEC_ARCH
	tag_t		m_tag[SEC_TAG_COUNT];	/* for unlabeled filesystems */
#endif
	lock_data_t	m_unmount_lock;		/* pathname/unmount synch */
	/* m_lbolt, m_iocntr, m_iocnt_max protected by MOUNT_THROTTLE_LOCK */
	udecl_simple_lock_data(,m_throttle_lock)/* multiprocessor exclusion */
	long	m_lbolt;	/* used for I/O completion sampling */
	u_int	m_iocntr;	/* used for I/O completion sampling */
	u_int	m_iocnt_max;	/* # requests at which I/O throttling starts */
	/* m_iocnt modified atomically */
	u_int	m_iocnt;	/* # outstanding I/O requests (currently ufs) */
	u_int	m_blksynccnt;	/* # blocked msync and fsync requests */
};

/*
 * Mask of flags that are visible in statfs.f_flags and statfs.f_flags2.
 * The f_flags2 field is a superset of the f_flags field.
 */
#define	M_VISFLAGMASK	0x0000ffff
#define	M_VISFLAGMASK2	0x0000ffff0000ffff

/*
 * Mount flags (mount m_flag)
 */
#define	M_RDONLY	0x00000001	/* read only filesystem */
#define	M_SYNCHRONOUS	0x00000002	/* file system written synchronously */
#define	M_NOEXEC	0x00000004	/* can't exec from filesystem */
#define	M_NOSUID	0x00000008	/* don't honor setuid bits on fs */

#define	M_NODEV		0x00000010	/* don't interpret special files */
#define	M_DIRECTIO	0x00000020	/* mount fs in direct I/O mode */
#define	M_NOATIMES	0x00000040	/* don't update access time on read */
#define	M_SMSYNC2	0x00000080	/* smoothsync policy of restarting age period
					   on each page modification */
#define	M_EXPORTED	0x00000100	/* file system is exported */
#define	M_EXRDONLY	0x00000200	/* exported read only */
#define	M_MLSD		0x00000400	/* fs uses multi-level secure dirs */
#define	M_SECURE	0x00000800	/* file system is labeled */

#define	M_LOCAL		0x00001000	/* filesystem is stored locally */
#define	M_QUOTA		0x00002000	/* quotas are enabled on filesystem */
#define	M_GRPID		0x00004000	/* new files get parent dir's group */
#define	M_THROTTLE	0x00008000	/* apply throttle to delayed I/O */

#define	M_UPDATE	0x00010000	/* not a real mount, just an update */
#define	M_MPBUSY	0x00020000	/* sync/unmount in progress */
#define	M_FMOUNT	0x00040000	/* forcibly mount, even if not clean */
#define	M_MSFS_MOUNT	0x00080000	/* advfs mounting or rm/addvol active */

#if MACH
#define	M_SWAP_NEVER	0x00100000	/* never swap here */
#endif /* MACH */
#define	M_IOERROR	0x00200000	/* I/O error */
#define	M_PRECIOUS	0x00400000	/* tell unmount to not deallocate */
#define	M_NEWRDDIR	0x00800000	/* uses new readdir style */

#define	M_MPWANT	0x01000000	/* someone waiting for busy vfs */
#define	M_DUAL  	0x02000000	/* dual mount of split mirror */
#define	M_CFSONTOP	0x04000000	/* CFS is stacked on top of this fs */
#define	M_FAILOVER      0x08000000      /* CFS mount failover */

#define	M_LOCAL_ROOT    0x10000000      /* local root mount */
#define	M_GLOBAL_ROOT   0x20000000      /* CFS global root mount */
#define	M_THROTTLED	0x40000000	/* I/O throttle active */
#define M_GLROOT_OTHER  0x80000000      /* mount of non root fset */
                                        /* in cluster_root domain */

#define	M_DELAYED	0x0000000100000000	/* delay metadata update */
#define	M_FSPART	0x0000000200000000      /* cluster fs partitioning */
#define	M_ADL		0x0000000400000000      /* AdvFS atomic data logging */
#define	M_EXTENDFS	0x0001000000000000	/* extend filesystem size */

/*
 * mount argument stacks
 */
#define M_NEEDXARGS	0x0000001000000000	/* arg stack required */
#define M_HAVEXARGS	0x0000002000000000	/* arg stack provided */
/*
 * NFS exported flags (exportfsdata).
 */
/* M_EXPORTED and M_EXRDONLY are used here and in m_flags */
#define	M_EXRDMOSTLY    0x00000400      /* exported ro to most */
#define	M_EXPUBLIC	0x00000800	/* exported for WebNFS public access */
#define	M_EXPUBINDEX	0x00001000	/* WebNFS access with index */

/* 
 * SVR3 and SVID-3 flags
 */
#define MS_DATA		0x000000020	/* called with 6 arguments */
#define MS_RDONLY	M_RDONLY
#define MS_NOSUID	M_NOSUID
#define MS_REMOUNT	M_UPDATE

/*
 *  Filesystem freeze flags
 */
#define FS_Q_FREEZE     0x0000000000000001      /* Freeze/quiesce the filesytem */
#define FS_Q_QUERY      0x0000000000000002      /* Query if filesytem frozen    */

/* 
 * Maximum length of a filesystem name within the vfssw table.
 */
#define MAX_VFSOPS_FSNAME  16

struct vfsops_with_fsname {
	struct vfsops  *vops_ptr;
	char   fsname[MAX_VFSOPS_FSNAME];
};

/*
 * Used with mount system call to determine specific index of a filesystem
 * name within the vfssw table.
 */
struct vfsops_fsname_args {
	char  fsname[MAX_VFSOPS_FSNAME];
	int   ret_index;
};


/*
 * Operations supported on mounted file system.
 */
struct vfsops {
	int	(*vfs_mount) __((struct mount *, char *, caddr_t, struct nameidata *));
	int	(*vfs_start) __((struct mount *, int flags));
	int	(*vfs_unmount) __((struct mount *, int));
	int	(*vfs_root) __((struct mount *, struct vnode **));
	int	(*vfs_quotactl) __((struct mount *, int, uid_t, caddr_t));
	int	(*vfs_statfs) __((struct mount *));
	int	(*vfs_sync) __((struct mount *, int));
	int	(*vfs_fhtovp) __((struct mount *, struct fid *, struct vnode **));
	int	(*vfs_vptofh) __((struct vnode *, struct fid *));
	int	(*vfs_init) __((void));
	int	(*vfs_mountroot) __((struct mount *, struct vnode **));
	int	(*vfs_swapvp) __((void));
	int	(*vfs_smoothsync) __((struct mount *, u_int, u_int));
};

#ifdef	_KERNEL

#if SER_COMPAT
#define	MOUNT_FUNNEL(mp)	((mp)->m_funnel)
#else
#define	MOUNT_FUNNEL(mp)	(0)
#endif

#define _VFSOP_(f,mp,args,ret)						\
MACRO_BEGIN								\
	if (!MOUNT_FUNNEL(mp)) {					\
		(ret) = (*(mp)->m_op->f)args;				\
	} else {							\
		unix_master();						\
		(ret) = (*(mp)->m_op->f)args;				\
		unix_release();						\
	}								\
MACRO_END

#define	_VFSOPV_(f,vp,args,ret)						\
MACRO_BEGIN								\
	if (!MOUNT_FUNNEL((vp)->v_mount)) {				\
		(ret) = (*((vp)->v_mount->m_op->f))args;		\
	} else {							\
		unix_master();						\
		(ret) = (*((vp)->v_mount->m_op->f))args;		\
		unix_release();						\
	}								\
MACRO_END

#define VFS_MOUNT(M,P,D,N,r)		_VFSOP_(vfs_mount,(M),((M),(P),(D),(N)),(r))
#define	VFS_START(MP,FL,r)		_VFSOP_(vfs_start,(MP),((MP),(FL)),(r))
#define	VFS_UNMOUNT(MP,F,r)		_VFSOP_(vfs_unmount,(MP),((MP),(F)),(r))
#define	VFS_ROOT(MP,VPP,r)		_VFSOP_(vfs_root,(MP),((MP),(VPP)),(r))
#define	VFS_QUOTACTL(MP,C,U,A,r)	_VFSOP_(vfs_quotactl,(MP),((MP),(C),(U),(A)),r)
#define	VFS_STATFS(MP,r)		_VFSOP_(vfs_statfs,(MP),(MP),(r))
#define	VFS_SYNC(MP,WF,r)		_VFSOP_(vfs_sync,(MP),((MP),(WF)),(r))
#define	VFS_FHTOVP(MP,FP,VP,r)		_VFSOP_(vfs_fhtovp,(MP),((MP),(FP),(VP)),(r))
#define	VFS_VPTOFH(VP,FIDP,r)		_VFSOPV_(vfs_vptofh,(VP),((VP),(FIDP)),(r))
#define	VFS_MOUNTROOT(MP,VPP,r)		_VFSOP_(vfs_mountroot,(MP),((MP),(VPP)),(r))
#define	VFS_SWAPVP(MP,VPP,r)		_VFSOP_(vfs_swapvp,(MP),((MP),(VPP)),(r))
#define VFS_SMOOTHSYNC(MP,AGE,FLAG,r)	_VFSOP_(vfs_smoothsync,(MP),((MP),(AGE),(FLAG)),(r))

#endif	/* _KERNEL */

/*
 * forcibly flags for vfs_umount().
 * waitfor flags to vfs_sync() and getfsstat()
 */
#define MNT_FORCE	0x1
#define MNT_NOFORCE	0x2
#define MNT_SKIPSYSTEM	0x4

/*
 * autofsmount(8) actually wants to unmount an
 * autofs pseudo mountpt.
 */
#define MNT_AUTOFS      0x8

#define MNT_WAIT	0x1
#define MNT_NOWAIT	0x2

/*
 * sync2 and smoothsync flags, and I/O throttle support
 */
#define SYNC_SYNCPOLICY		0x0001	/* flush all dirty buffers */
#define SYNC_SMOOTHSYNCPOLICY	0x0002	/* flush all dirty buffers which are
					   not under smoothsync control */
#ifdef	_KERNEL
#define SMSYNC_PERIOD		0x0001
#define SMSYNC_HALFPERIOD	0x0002
#define SMSYNC_LATCH		0x0004
#define SMSYNC_SLOW		0x0008
#define SMSYNC_LOWATERFLUSH	0x0010

#define M_IOCNT_DECR(mp)	(atomic_decl(&mp->m_iocnt))
#define M_IOCNT_INCR(mp)	(atomic_incl(&mp->m_iocnt))
#define MNT_IO_LOWATER(mp)	(mp->m_iocnt<<1 <= mp->m_iocnt_max)
#define MNT_IO_THRESHOLD(mp)	(mp && mp->m_iocnt_max && \
				 mp->m_iocnt >= mp->m_iocnt_max)
#endif	/* _KERNEL */

#ifdef	_KERNEL
/*
 * Mount structure locking constraints.
 *	Field		Constraint
 *	-----		----------
 *	m_nxt		mountlist_lock
 *	m_prev		mountlist_lock
 *	m_op		m_lock
 *	m_vnodecovered	read-only?	XXX
 *	m_mounth	m_vlist_lock
 *	m_flag		m_lock
 *	m_exroot	m_lock
 *	m_stat		m_lock
 *	m_info		read-only
 *	m_lbolt		m_throttle_lock
 *	m_iocntr	m_throttle_lock
 *	m_iocnt_max	m_throttle_lock
 *	m_iocnt		modified atomically
 #ifdef SEC_ARCH
 *	m_tag		read_only!
 #endif
 *	m_blksynccnt	modified atomically
 *
 * Additional mount synchronization constraints.  [XXX]
 */

/*
 * The mount lock protects the contents of the mount structure from
 * other processors.  Only needed for NCPUS > 1.
 */
udecl_simple_lock_info(extern, mount_lockinfo)
#define	MOUNT_LOCK(mp)		usimple_lock(&(mp)->m_lock)
#define	MOUNT_UNLOCK(mp)	usimple_unlock(&(mp)->m_lock)
#define	MOUNT_LOCK_INIT(mp)	usimple_lock_setup(&(mp)->m_lock,mount_lockinfo)
#define	MOUNT_LOCK_HOLDER(mp)	SLOCK_HOLDER(&(mp)->m_lock)

/*
 * The mount_throttle lock protects mount structure fields used for I/O
 * throttling.  These fields are modified primarily in biodone, which 
 * cannot take the mount lock.
 */
udecl_simple_lock_info(extern, mount_throttle_lockinfo)
#define	MOUNT_THROTTLE_LOCK(mp)		usimple_lock(&(mp)->m_throttle_lock)
#define	MOUNT_THROTTLE_UNLOCK(mp)	usimple_unlock(&(mp)->m_throttle_lock)
#define	MOUNT_THROTTLE_LOCK_INIT(mp)	\
	usimple_lock_setup(&(mp)->m_throttle_lock,mount_throttle_lockinfo)

/*
 * The mount vnode list lock guards the list of vnodes associated
 * with a mount point.  Only needed for NCPUS > 1.
 */
udecl_simple_lock_info(extern, mount_vlist_lockinfo)
#define	MOUNT_VLIST_LOCK(mp)	usimple_lock(&(mp)->m_vlist_lock)
#define	MOUNT_VLIST_UNLOCK(mp)	usimple_unlock(&(mp)->m_vlist_lock)
#define	MOUNT_VLIST_LOCK_INIT(mp) usimple_lock_setup(&(mp)->m_vlist_lock,\
						     mount_vlist_lockinfo)

/*
 * The unmount lock synchronizes pathname translation (crossing
 * of mount points) with filesystem unmounting.  It is acquired for
 * reading by namei() and getvfs(), and acquired for writing by
 * unmount().
 * NOTE: these could be optimized for the root FS (to do nothing)
 *	 since the root cannot be unmounted.
 */

extern struct lockinfo *unmount_lockinfo;
#define	UNMOUNT_TRY_READ(mp)      lock_try_read_assert(&(mp)->m_unmount_lock)
#define	UNMOUNT_TRY_READ_NOSLP(mp) lock_try_read(&(mp)->m_unmount_lock)
#define	UNMOUNT_WRITE_LOCK(mp)	  lock_write(&(mp)->m_unmount_lock)
#define UNMOUNT_TRY_WRITE_LOCK(mp) lock_try_write(&(mp)->m_unmount_lock)
#define	UNMOUNT_WRITE_UNLOCK(mp)  lock_write_done(&(mp)->m_unmount_lock)
#define	UNMOUNT_READ_UNLOCK(mp)	  lock_read_done(&(mp)->m_unmount_lock)
#define	UNMOUNT_LOCK_INIT(mp)	  lock_setup(&(mp)->m_unmount_lock,\
					   unmount_lockinfo, TRUE)

/*
 * Mount list lock operations.
 */
udecl_simple_lock_info(extern, mountlist_lockinfo)
#define	MOUNTLIST_LOCK()	usimple_lock(&mountlist_lock)
#define	MOUNTLIST_UNLOCK()	usimple_unlock(&mountlist_lock)
#define	MOUNTLIST_LOCK_INIT()	usimple_lock_setup(&mountlist_lock,\
						  mountlist_lockinfo)

/*
 * Lock operations on the vfssw.  Used for addition/deletion of
 * file systems.
 */
extern struct lockinfo *vfssw_lockinfo;

#define VFSSW_READ_LOCK()	lock_read(&vfssw_lock);
#define VFSSW_WRITE_LOCK()	lock_write(&vfssw_lock);
#define VFSSW_WRITE_UNLOCK()	lock_done(&vfssw_lock);
#define VFSSW_READ_UNLOCK()	lock_done(&vfssw_lock);
#define VFSSW_LOCK_INIT()	lock_setup(&vfssw_lock, vfssw_lockinfo, TRUE)


#define NULLMOUNT	((struct mount *) 0)
#define DEADMOUNT	(&dead_mount)

/*
 * exported vnode operations and globals
 */
_BEGIN_CPLUSPLUS
extern void	vfs_remove();                        /* remove a vfs from mount list */
extern struct	mount *getvfs __((fsid_t *));        /* return vfs given fsid */
extern struct	mount *findvfs __((fsid_t *));       /* return vfs, no lock  */
extern int	vfs_busy __((struct mount *, int));  /* mark filesystem busy */
extern void	vfs_unbusy __((struct mount *));     /* mark filesystem not busy */
extern struct	mount *rootfs;		/* ptr to root mount structure */
extern struct	mount dead_mount; 	/* dead mount structure */
extern struct	vfsops_with_fsname vfssw[]; /* mount filesystem type switch */
extern lock_data_t vfssw_lock;		/* guard vfssw */
udecl_simple_lock_data(extern,mountlist_lock)	/* guard mount list */
_END_CPLUSPLUS

extern int	nmount;			/* number of ufs mount structs */
extern int      nmount_max;             /* number of entries in mount_zone */

/*
 * mount argument stacks
 */

typedef struct kmount_xargs_stack*   kmount_xargs_stack_t;

typedef struct kmount_xargs {
	int       mnt_type;
	int       datasz;
	u_long    mnt_flag;
	caddr_t   data;
} kmount_xargs_t;

extern int
kmount_xargs_free( kmount_xargs_stack_t* pxargs );

extern int
kmount_xargs_get( kmount_xargs_stack_t* pxargs,
                  int                   mnt_type,
                  u_long                mnt_flag,
                  caddr_t               data );

extern int
kmount_xargs_pop( kmount_xargs_stack_t xargs,
                  kmount_xargs_t*      mnt_args );


#endif /* _KERNEL */
#endif /* _SYS_MOUNT_H_ */


