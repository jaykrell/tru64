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
 *	@(#)$RCSfile: fcntl.h,v $ $Revision: 4.2.105.2 $ (DEC) $Date: 2001/11/19 16:50:42 $
 4.2.21.2
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */

/*
 * COMPONENT_NAME: SYSLFS - Logical File System
 *
 * ORIGINS: 27, 3, 26
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _SYS_FCNTL_H_
#define _SYS_FCNTL_H_
#if defined(__cplusplus)
extern "C"
{
#endif

#include <standards.h>
#include <sys/types.h>

/*
 * POSIX requires that certain values be included in fcntl.h and that only
 * these values be present when _POSIX_C_SOURCE is defined >=1.  This header
 * includes all the POSIX required entries.
 */

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 1) 

struct  flock   {
        short   l_type;
        short   l_whence;
        off_t   l_start;
        off_t   l_len;          /* len = 0 means until end of file */
        pid_t   l_pid;
};
/* file segment locking set data type - information passed to system by user */

/* file segment locking types */
#define F_RDLCK 1       /* Read (shared) lock */
#define F_WRLCK 2       /* Write (exclusive) lock */
#define F_UNLCK 8       /* Remove lock(s) */

extern int open __((const char *, int , ...));
extern int creat __((const char *, mode_t ));
extern int fcntl __((int , int ,...));

/* File status flags accessible to open(2) and fcntl(2) */
#define O_NONBLOCK 00000004	/* non-blocking I/O, POSIX style */
#define	O_APPEND   00000010  	/* append (writes guaranteed at the end) */

/* Mask for use with file access modes */
#define O_ACCMODE	3		

/* Flag values accessible to open(2) */
#define	O_RDONLY 00000000
#define	O_WRONLY 00000001
#define	O_RDWR	 00000002
 
/* Flag values accessible only to open(2) */
#define	O_CREAT	 00001000    /*  open with file create (uses third open arg)*/
#define	O_TRUNC	 00002000    /* open with truncation		*/
#define	O_EXCL	 00004000    /* exclusive open			*/
#define O_NOCTTY 00010000    /* POSIX REQUIRED */
#ifdef	_KERNEL
#define	O_DOCLONE 00020000    /* make a cloned device */
#endif
#define O_DRD      00100000	/* restrict usage of DRD via this flag */
#define O_DIRECTIO 00200000	/* Set cache policy for this file to direct IO */
#define O_CACHE    00400000	/* Set cache policy for this file to writeback */
#define O_NOFOLLOW 01000000	/* don't follow symlink on open */

/* File descriptor flags used for fcntl() */
/* POSIX REQUIRED */
#define FD_CLOEXEC      1	/* Close this file during exec */

/* fcntl() requests */
#define	 F_DUPFD	0	/* Duplicate fildes		*/
#define	 F_GETFD	1	/* Get fildes flags		*/
#define	 F_SETFD	2	/* Set fildes flags		*/
#define	 F_GETFL	3	/* Get file flags		*/
#define	 F_SETFL	4	/* Set file flags		*/
#define	 F_GETLK	7	/* Get file lock	POSIX REQUIRED	*/
#define	 F_SETLK	8	/* Set file lock	POSIX REQUIRED	*/
#define	 F_SETLKW	9	/* Set file lock and waitPOSIX REQUIRED	*/

#endif /* _POSIX_C_SOURCE */

/*
 * File locking flags.  First 8 bits for various commands.  Rest
 * are for options to those commands.  Also need to define
 * end of file for file locking.
 */
#ifdef _KERNEL
#define GETFLCK         0x1     /* Get the file lock */
#define SETFLCK         0x2     /* Set the file lock */
#define CLNFLCK         0x4     /* Clean file locks */
#define VNOFLCK         0x8     /* File is locked */

#define RGETFLCK        0x10    /* Remote Get of file lock */
#define RSETFLCK        0x20    /* Remote Set of file lock */

#define SLPFLCK         0x100   /* Wait if blocked */
#define VRDFLCK         0x200   /* Read lock use */
#define VMANFLCK        0x400   /* Mandatory locking */
#define ENFFLCK         0x800   /* Enforcement mode locks */

#define CFS_LOCK_RECOVERY    0x1000 /* CFS file lock recovery */
#define SHADOWFLCK           0x2000 /* CFS client "shadow" lock */
#define CFS_LOCK_RECLAIM     0x4000 /* CFS reclaim of external NFS lock */
#define CFS_NODEDOWN_CLEANUP 0x8000 /* CFS cleanup request on behalf of a */
				    /*     failed client node */
    
#if	defined(__arch32__)
#define MAXEND          0x80000000
#else
#define MAXEND          0x8000000000000000
#endif /* __arch32__ */
#endif /* _KERNEL */


#ifdef _XOPEN_SOURCE 
/* XOPEN REQUIRED  */
#include <sys/seek.h>
#include <sys/mode.h>
#endif  /* _XOPEN_SOURCE */
 
#if defined(_XOPEN_SOURCE) || ( defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L) )
#define O_SYNC		00040000       /* POSIX 1003.1b and xopen */
#define O_DSYNC         02000000       /* POSIX 1003.1b write data integrity */
#define O_RSYNC         04000000       /* POSIX 1003.1b read i/o integrity */
#endif /* _XOPEN_SOURCE || _POSIX_C_SOURCE */

#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)

/* Additional fcntl requests */

#define	 F_GETOWN	5	/* get async I/O owner		*/
#define	 F_SETOWN	6	/* set async I/O owner		*/

#ifdef _OSF_SOURCE

#ifndef _POSIX_C_SOURCE
#ifdef _BSD

/*
 * Flock call.
 */

extern int flock __((int , int ));

#endif   /* _BSD */
#endif   /* !_POSIX_C_SOURCE */

#define LOCK_SH         F_RDLCK       /* shared lock */
#define LOCK_EX         F_WRLCK       /* exclusive lock */
#define LOCK_NB         4             /* don't block when locking */
#define LOCK_UN         F_UNLCK       /* unlock */


/*
 * Flag values accessible to open(2) and fcntl(2)
 */

/* O_NDELAY was defined as O_NONBLOCK.  The two definitions have been
 * seperated but the code has been modified so both flags still exhibit
 * the same behavior.  They will exhibit seperate behaviors in a future
 * release
 */
#define O_DEFER		00000040	/* defered update		*/
#define O_NDELAY	00100000	/* Non-blocking I/O		*/


#define FNDELAY		O_NDELAY
#define	FAPPEND		O_APPEND
#define FASYNC		00100
#define	FCREAT		O_CREAT
#define	FTRUNC		O_TRUNC
#define	FSYNC		O_SYNC
#define	FEXCL		O_EXCL
#define	FNONBLOCK 	O_NONBLOCK
#define FDEFER		O_DEFER
#define FDSYNC          O_DSYNC
#define FRSYNC          O_RSYNC

#ifdef _KERNEL
#define FKERNEL         00200000        /* internal kernel use */
#define FVTEXT          01000000
#define FEXCLFOLLOW    010000000	/* follow symlinks and exclusive open */
#define FCFSRECOVERY  0100000000        /* Open of VBLK during CFS recovery */
#endif


/*
 * These may be AIX only values and should possibly be removed
 */

/* Flag values accessible only to open(2) */
#define	FOPEN		(-1)
#define	FREAD		00001
#define	FWRITE		00002
/*
 * DEC/OSF advisory flags for VOP_FSYNC calls.
 * These flags are additive with FWRITE.
 * Local filesystem types need not necessarily recognize them.
 * These flags are treated as mutually exclusive, and apply
 * to VREG files only.
 */
#define FWRITE_DATA     00004   /* Data blocks only */
#define FWRITE_METADATA 00010   /* Meta-Data blocks only */

#define FMARK           00020           /* mark during gc() */
#define FSHLOCK         00200           /* shared lock present */
#define FEXLOCK         00400           /* exclusive lock present */

/* FFCNTL is all the bits that may be set via fcntl. */
#define	FFCNTL	(FNONBLOCK|FNDELAY|FAPPEND|FSYNC|FDSYNC|FRSYNC|FASYNC) 

/* bits to save after open */
#define FMASK           (FSYNC|FDSYNC|FRSYNC|FASYNC|FAPPEND|FNDELAY|FNONBLOCK|FWRITE|FREAD)
#define FCNTLCANT       (FREAD|FWRITE|FMARK|FDEFER|FSHLOCK|FEXLOCK)

/* fcntl reqs for the lock mngr */
#define F_RGETLK        10      /* Test a remote lock */
#define F_RSETLK        11      /* Set or unlock a remote lock */
#define F_CNVT          12      /* Convert a fhandle to an open fd */
#define F_RSETLKW       13      /* Set or Clear remote lock(Blocking) */

/* additional flag for l_type field of flock structure */
#define F_UNLKSYS  4   /* remove remote locks for a given system */

/* extended file segment locking set data type */
struct eflock {
        short   l_type;         /* F_RDLCK, F_WRLCK, or F_UNLCK */
        short   l_whence;       /* flag to choose starting offset */
        off_t   l_start;        /* relative offset, in bytes */
        off_t   l_len;          /* length, in bytes; 0 means lock to EOF */
        pid_t	l_pid;          /* returned with F_GETLK */
        pid_t	l_rpid;         /* Remote process id wanting this lock */
        int     l_rsys;         /* Remote system id wanting this lock */
	short   l_xxx;		/* grant lock flag in nfssrc4.2 lockd */
        int     l_cb;           /* IP address to callback		*/
};

/* fcntl req for DECsafe Product (for Compaq Use Only) */
#define F_PURGEFS	14	/* Purge locks on fs (for ASE product) */
#define F_PURGENFS      15

#define  F_GETTIMES    16       /* Get file a/m/ctime(s)        */
#define  F_SETTIMES    17       /* Set file a/m/ctime(s)        */
#define  F_RWREFS      18       /* Get open refs                */
#define  F_ADVFS_OP    19       /* AdvFS-specific operations that must */
                                /* work across NFS as well as locally. */

/* AdvFS operation data structure, for F_ADVFS_OP. */
typedef struct {
    ulong version;      /* Structure version */
#define ADVFS_OP_CURR_VERSION 1
    ulong operation;    /* Operation type; example: ADVFS_AW_DATA_LOGGING */
    ulong action;       /* Action to take; example: ADVFS_ACTIVATE */
    ulong info_buf_size;/* Size of info_buf buffer */
    void  *info_buf;    /* Returned info; example: dataSafety setting */
    ulong spare[2];     /* For future expansion */
} advfs_opT;

/* AdvFS operations, for F_ADVFS_OP */
#define ADVFS_AW_DATA_LOGGING 0x1  /* Atomic write data logging */
#define ADVFS_SYNC_WRITE      0x2  /* Forced synchronous writes */

/* AdvFS actions, for F_ADVFS_OP */
#define ADVFS_ACTIVATE        0x1  /* Turn on feature specified by operation  */
#define ADVFS_DEACTIVATE      0x2  /* Turn off feature specified by operation */
#define ADVFS_GET_INFO        0x4  /* Get information about feature specified */
                                   /* by operation */
#define ADVFS_GET_IN_MEM_INFO 0x8  /* Get information about feature specified */
                                   /* by operation.  If in-memory value       */
                                   /* differs from on-disk value, returns     */
                                   /* in-memory value.                        */

/* AdvFS file I/O modes returned by the ADVFS_GET_INFO or
 * ADVFS_GET_IN_MEM_INFO action, for F_ADVFS_OP 
 */
#define ADVFS_ASYNC_IO        0x0  /* Normal, asynchronous I/O */
#define ADVFS_DATA_LOGGING_IO 0x2  /* Atomic write data logging */
#define ADVFS_SYNC_IO         0x3  /* Forced synchronous writes */
#define ADVFS_TEMPORARY_DATA_LOGGING_IO 0x4  /* From "mount -o adl" */

/* fcntl for File system sparseness checking (for Compaq Use Only) */
#define F_GETMAP	21	/* retrieve a file's sparseness map */

/* structures used by F_GETMAP fcntl call */

struct extentmapentry {
	unsigned long offset;
	unsigned long size;
};

struct extentmap {
	unsigned long arraysize;
	unsigned long numextents;
	unsigned long offset;
	struct extentmapentry *extent;
};

/* fcntl commands for signalling CFS about the start/end of the NFS lockd grace period */
#define F_GRACE_START  22
#define F_GRACE_END    23

/* fcntl for File system cache control (for Compaq Use Only) */
#define F_GETCACHEPOLICY 24
#define FCACHE		  0    /* File's cache is filesystem's default */
#define FDIRECTIO	  1    /* File's cache policy is Direct I/O */


/* more fcntl req for DECsafe Product (for Compaq Use Only) */
#define F_PURGESTART	20	/* F_PURGENFS with a struct sockaddr */
#define F_PURGEFINISH	26	/* F_PURGENFS with a struct sockaddr */

#endif	/* _OSF_SOURCE	*/

#endif /* _OSF_SOURCE || _XOPEN_SOURCE_EXTENDED */

#if defined(__cplusplus)
}
#endif
#endif	/* _SYS_FCNTL_H_ */

