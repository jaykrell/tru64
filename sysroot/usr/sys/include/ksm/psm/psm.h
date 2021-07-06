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
 * @(#)$RCSfile: psm.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 2000/01/27 19:41:49 $
 */

#ifndef	_PSM_H_
#define	_PSM_H_

#include <ksm/ksm.h>

#ifdef __cplusplus
extern "C" {
#endif

#define	PSM_NAME	"process"		/* name of this KSM set */
#define	PSM_VERS	1			/* version of this KSM set */

#define	PSM_ATTR_CNT	7			/* includes the "NULL" entry */

#define	PSM_CATLEN	KSM_CAT_NAME_SIZE	/* length of a KSM category */
#define	PSM_MEMLEN	32			/* length of a member name */
#define	PSM_STATELEN	32			/* length of state field */
#define	PSM_ARGVLEN	168			/* length of command line */

#define	PSM_KSM_SETOP	KSM_OP_PRIV_SET_MIN	/* all PSM set operations */

#define	PSM_SETVERS		1		/* PSM set operation version */
#define	PSM_SETOP_CATGET	1		/* PSMop: get categories */
#define	PSM_SETOP_CATADD	2		/* PSMop: add category */
#define	PSM_SETOP_CATREM	3		/* PSMop: remove category */
#define	PSM_SETOP_MEMGET	4		/* PSMop: get members */
#define	PSM_SETOP_MEMADD	5		/* PSMop: add member */
#define	PSM_SETOP_MEMREM	6		/* PSMop: remove member */

#define	PSM_FL_EXIT		0x1		/* flag: process has exited */
#define	PSM_FL_ARGTRUNC		0x2		/* flag: mrs_argv[] truncated */

#define	PSM_ST_STARTED		"running"	/* state: running */
#define	PSM_ST_EXITED		"exited"	/* state: exited */

/* defined flags for PSM Attribute "psm_debug" */
#define	PSM_OPT_DEBUG_PSM	0x01		/* debug: PSM module */
#define	PSM_OPT_DEBUG_PROC	0x02		/* debug: PSM proc ops */
#define	PSM_OPT_DEBUG_EVM	0x04		/* debug: PSM evm ops */
#define	PSM_OPT_DEBUG_SET	0x10		/* debug: PSM set ops */
#define	PSM_OPT_DEBUG_CAT	0x20		/* debug: PSM category ops */
#define	PSM_OPT_DEBUG_MEM	0x40		/* debug: PSM member ops */
#define	PSM_OPT_DEBUG_MISC	0x80		/* debug: PSM misc ops */

/* defined flags for PSM Attribute "psm_noevm" */
#define	PSM_OPT_NOEVM_SET	0x01		/* noevm: no add/rem set */
#define	PSM_OPT_NOEVM_CAT	0x02		/* noevm: no add/rem category */
#define	PSM_OPT_NOEVM_MEM	0x04		/* noevm: no add/rem member */
#define	PSM_OPT_NOEVM_EXMEM	0x08		/* noevm: no exit member */

typedef struct psm_setreq_s {
	unsigned short	srq_vers;		/* PSM_SETVERS */
	unsigned short	srq_op;			/* PSM_SETOP_* */
	unsigned int	srq_pid;		/* target process id or 0 */
	char		srq_cat[PSM_CATLEN];	/* target category or NUL */
} psm_setreq_t;

typedef struct psm_catrsp_s {
	unsigned int	crs_listidx;		/* category number in list */
	unsigned int	crs_listcnt;		/* total categories in list */
	unsigned int	crs_total;		/* total matching categories */
	unsigned int	crs_memcnt;		/* number of members */
	char		crs_cat[PSM_CATLEN];	/* category name */
} psm_catrsp_t;

typedef struct psm_memrsp_s {
	unsigned int	mrs_listidx;		/* member number in list */
	unsigned int	mrs_listcnt;		/* total members in list */
	unsigned int	mrs_total;		/* total matching members */
	unsigned int	mrs_pid;		/* process id */
	unsigned int	mrs_exitcode;		/* exit status code */
	unsigned int	mrs_flags;		/* process flags (PSM_FL_*) */
	char		mrs_name[PSM_MEMLEN];	/* unique name of member */
	char		mrs_state[PSM_STATELEN];/* state ("running", etc.) */
	char		mrs_argv[PSM_ARGVLEN];	/* saved argv */
} psm_memrsp_t;

#ifdef	_KERNEL

/*
 * Macros to check various PSM Attribute options.
 */
#define	PSM_OPT_DEBUG(fl)	((psm_debug & (fl)) != 0)
#define	PSM_OPT_NOEVM(fl)	((psm_noevm & (fl)) != 0)

/*
 * Define some memory allocation and deallocation macros.
 */
#define	PSM_MALLOC(addr, type, size) \
	MALLOC(addr, type, size, M_KTABLE, M_WAITOK)
#define	PSM_MALLOCZ(addr, type, size) \
	MALLOC(addr, type, size, M_KTABLE, M_WAITOK|M_ZERO)
#define	PSM_FREE(addr) \
	FREE(addr, M_KTABLE)

/*
 * Lock macros
 */
#define	PSM_MKLOCK(l)	lock_setup(&(l)->lock, psm_set_lockinfo, TRUE)
#define	PSM_RDLOCK(l)	lock_read(&(l)->lock)
#define	PSM_WRLOCK(l)	lock_write(&(l)->lock)
#define	PSM_UNLOCK(l)	lock_done(&(l)->lock)
#define	PSM_RMLOCK(l)	lock_terminate(&(l)->lock)

/*
 * Event types (passed to psm_evm() and psm_evmset()).
 */
typedef enum {
	PsmEvm_SetAdd,				/* add "process" set */
	PsmEvm_SetRem,				/* remove "process" set */
	PsmEvm_CatAdd,				/* add category */
	PsmEvm_CatRem,				/* remove category */
	PsmEvm_MemAdd,				/* add member (instance) */
	PsmEvm_MemRem,				/* remove member (instance) */
	PsmEvm_MemExit				/* member (instance) exited */
} PsmEvm_t;

/*
 * Prototypes
 */
#ifdef	_USE_KERNEL_PROTOS
extern	int		psm_set_add(void);
extern	int		psm_set_rem(void);
extern	int		psm_cat_get(const char *, caddr_t, size_t);
extern	int		psm_cat_add(const char *);
extern	int		psm_cat_rem(const char *);
extern	int		psm_mem_get(const char *, pid_t, caddr_t, size_t);
extern	int		psm_mem_add(const char *, pid_t);
extern	int		psm_mem_rem(const char *, pid_t);

extern	int		psm_proc_get(pid_t *, char *, int *);
extern	unsigned int	psm_proc_exitcode(void);
extern	int		psm_proc_reg(pid_t pid);
extern	int		psm_proc_unreg(pid_t pid);
extern	pid_t		psm_proc_mypid();

extern	int		psm_evmset(PsmEvm_t);
extern	int		psm_evm(PsmEvm_t, const char *, pid_t, unsigned int);
#endif	/* _USE_KERNEL_PROTOS */

#endif	/* _KERNEL */

#ifdef __cplusplus
}
#endif

#endif	/* _PSM_H_ */
