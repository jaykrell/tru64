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
 * @(#)$RCSfile: numa_types.h,v $ $Revision: 1.1.18.1 $ (DEC) $Date: 2002/01/10 14:02:01 $
 */

#ifndef	_NUMA_TYPES_H
#define _NUMA_TYPES_H

/*
 *	File:	numa_types.h -- Digital Unix NUMA API Data Types
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <machine/machlimits.h>

#include <sys/idset.h>			/* for idset_t definition */
#include <sys/cpuset.h>			/* for cpuset_t definition */
#include <sys/radset.h>			/* for radset_t definition */

typedef int rad_state_t;		/* Software State of a RAD */

#define	RAD_NONE	(-1)		/* No such RAD or none specified */
#define	RAD_OFFLINE	0		/* RAD is offline, but 'queryable' */
#define	RAD_ONLINE	1		/* RAD is on-line and useable */

#define RAD_INFO_VERSION	1
typedef struct __rad_info {
	int		rinfo_version;	/* revision number */
	radid_t		rinfo_radid;	/* RAD id this info applies to */
	rad_state_t	rinfo_state;	/* software state of this RAD */
	ssize_t		rinfo_physmem;	/* phys mem configured on this RAD */
	ssize_t		rinfo_freemem;	/* free/avail memory on this RAD */
	cpuset_t	rinfo_cpuset;	/* cpus configured on this RAD */
} rad_info_t;

typedef	unsigned int nsgid_t;	/* NUMA Scheduling Group ID */
#define NSG_NONE	(-1)	/* no such NSG exists or none specified */

#ifdef _XOPEN_SOURCE 

typedef struct nsgid_ds {
	struct	ipc_perm	nsg_perm;	/* permissions */
	int			nsg_nattach;	/* number of attachments */
	int			nsg_pad[8];	/* future expansion */
} nsgid_ds_t;

typedef struct __numa_pid_info {
	pid_t		npinfo_pid;	/* Process IDentifier */
	radid_t		npinfo_radid;	/* Home RAD for npinfo_pid */
	nsgid_t		npinfo_nsgid;	/* npinfo_pid NSG id (if any) */
	u_long		npinfo_attrib;	/* npinfo_pid associated attributes */
	u_long		npinfo_pad[10];	/* future development */
} numa_pid_info_t;

/* npinfo_attrib mask bits */
#define NPINFO_RAD_BIND		0x01	/* PID is bound to a RAD */
#define NPINFO_RAD_ATTACH	0x02	/* PID is attached to a RAD */
#define NPINFO_RAD_NO_INHERIT	0x04	/* PID children won't inherit RAD */
#define NPINFO_NSG		0x08	/* PID is a member of an NSG */
#define NPINFO_NSG_NO_INHERIT	0x10	/* PID children won't inherit NSG */

#endif /* _XOPEN_SOURCE */ 

typedef	unsigned long	iopath_t;	/* opaque handle on I/O path */
#define	RAD_NOIOPATH	(-1)		/* no such I/O path exists */


typedef enum rsrctype {
	R_RAD,		/* specify a radset or query all RADs on system */
	R_FILDES,	/* resource is an opened file or device */
	R_PATH,		/* resource is pathname of a file or device */
	R_SHM,		/* resource is a SysV Shared Memory segment */
	R_PID,		/* resource is a process */
	R_MEM,		/* resource is a virtual memory address */
	R_NSG		/* resource is a NUMA Scheduling Group */
} rsrctype_t;

typedef union rsrcdescr {
	radset_t	rd_radset;
	int		rd_fd;
	char		*rd_pathname;
	int		rd_shmid;
	pid_t		rd_pid;
	void		*rd_addr;
	nsgid_t		rd_nsg;
} rsrcdescr_t;

#define RAD_DIST_LOCAL	100		/* local resources <= this value */
#define RAD_DIST_REMOTE	INT_MAX		/* all resources <= this value */

#define RAD_BOUND	1		/* RADs that have bound resources */
#define RAD_NOBOUND	2		/* No resources bound to RADs */

typedef struct numa_attr {
	rsrctype_t	nattr_type;
	rsrcdescr_t	nattr_descr;
	ulong		nattr_distance;
	ulong		nattr_flags;
}numa_attr_t;

typedef enum memalloc_policy {
	MPOL_DIRECTED,		/* allocate on specified RAD */
	MPOL_THREAD,		/* allocate on current thread's "home RAD" */
	MPOL_REPLICATED,	/* replicate local to current processor */
	MPOL_STRIPED,		/* stripe across radset with specified stride*/
	MPOL_INVALID		/* MUST BE LAST for range checking, do not */
				/* use explicit assigments within this enum */
} memalloc_policy_t;
#define	MPOL_NO_MIGRATE	0x100	/* OR'ed with any policy */

#define POLICY_FLAGS		(MPOL_NO_MIGRATE)
#define POLICY_TYPE(_p_)	((_p_)&~POLICY_FLAGS)
#define VALIDATE_POLICY(_p_) \
	((POLICY_TYPE(_p_)< 0 || POLICY_TYPE(_p_)>=MPOL_INVALID) ? MPOL_INVALID:(_p_))

typedef struct memalloc_attr {
	memalloc_policy_t	mattr_policy;	/* the allocation policy */
	radid_t			mattr_rad;	/* the primary/preferred RAD */
	unsigned int		mattr_stride;	/* stride [in pages] */
	unsigned int		mattr_distance;	/* distance to overflow */

	unsigned int		mattr_pagesz;	/* later ;-) */
	unsigned int		__mattr_fill1[3]; /* room to grow & alignment*/

	radset_t		mattr_radset;	/* overflow/stripe set */

	unsigned long		__mattr_fill2[3]; /* room to grow */
} memalloc_attr_t;

/* 
 * optional nmadvise struct - used when the len parameter is negative.
 * N.B., intended for internal library use only
 */

typedef struct nmemalloc_range {
	void	*addr;		/* virtual address */
	size_t	len;		/* length in bytes */
	radid_t	rad;		/* the primary/preferred RAD */
	int	errelem;	/* array element where error occurred */
				/* [in first array element only ] */
	long	pad2;
} nmemalloc_range_t;

/*
 * Flags for rad_assign_pid(), nfork(), nexec(), etc.
 */
#define	RAD_INSIST	0x01	/* request is mandatory */
#define RAD_SMALLMEM	0x02	/* favor RADs with available cpu cycles */
#define RAD_LARGEMEM	0x04	/* favor RADs with available memory */
#define	RAD_WAIT	0x08	/* wait for migration to complete */

#define RAD_MIGRATE	0x10	/* migrate process/thread pages */
#define RAD_NO_MIGRATE	0x20	/* don't migrate process/thread pages */
#define	RAD_NO_INHERIT	0x40	/* children don't inherit RAD bindings */

#define RAD_ATTACH_TO_PARENT	0x100	/* add new proc to parent's NSG */

/*
 * Flags for Shared Memory Ops -- nshmget(), nshmctl(), ...
 * Avoid collision w/ command/flags in sys/ipc.h and sys/shm.h
 */
#define	SHM_MIGRATE	0x101	/* migrate region based on new attributes */
#define SHM_REPLICATE	0x102	/* mark region for replication */
#define SHM_WAIT	0x200	/* wait for migration/replication */
#define SHM_ALL	0x400	/* apply to entire shared memory segment */

/*
 * Flags for NUMA Scheduling Group APIs [leave room for permission bits]
 */
#define	NSG_CREATE	0001000	/* create NSG if it doesn't exist */
#define NSG_EXCL	0002000 /* fail create if already exists */
#define NSG_GETBYPID	0004000	/* nsg key is process id */
#define NSG_CLEANUP	0010000	/* delete NSG when last process removed */

/* 
 * internal book keeping NSG flag bits.
  */
#define NSG_DESTROY_ASSERT	0100000 /* waiting to destroy NSG */
#define NSG_DESTROY_INPROG	0200000 /* NSG destroy in progress */

/*
 * NSG_ flags are shifted versions of RAD_* flags.
 * This is done so as not to collide with the 9 mode/permission bits
 * and to avoid internal IPC flag definitions
 */
#define _NSG_SHIFT	20
#define _RAD_TO_NSG_FLAG(_R_) ((_R_) << _NSG_SHIFT)

#define	NSG_INSIST	_RAD_TO_NSG_FLAG(RAD_INSIST)
#define NSG_SMALLMEM	_RAD_TO_NSG_FLAG(RAD_SMALLMEM)
#define NSG_LARGEMEM	_RAD_TO_NSG_FLAG(RAD_LARGEMEM)
#define	NSG_WAIT	_RAD_TO_NSG_FLAG(RAD_WAIT)

#define	NSG_MIGRATE	_RAD_TO_NSG_FLAG(RAD_MIGRATE)
#define NSG_NO_MIGRATE	_RAD_TO_NSG_FLAG(RAD_NO_MIGRATE)
#define NSG_NO_INHERIT	_RAD_TO_NSG_FLAG(RAD_NO_INHERIT)

/*
 * NSG control operations:
 */
#define NSG_RMID	0x00	/* remove the NSG */
#define NSG_SET		0x01	/* set NSG permissions */
#define NSG_STAT	0x02	/* query NSG status -- see struct nsgid_ds */

#define NSG_GETMEMBERS	0x03	/* get NSG membership roster */

/*
 * VM Troller States
 */
#define VMMT_STATE_DISABLED	-1	/* troller unsupported */
#define VMMT_STATE_RUNNING	0	/* troller running */
#define VMMT_STATE_SWITCHING	1	/* troller starting or stopping */
#define VMMT_STATE_STOPPED	2	/* troller not running */

#endif	/* _NUMA_TYPES_H */
