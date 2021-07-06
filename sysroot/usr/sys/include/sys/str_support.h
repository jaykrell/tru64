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
 * @(#)$RCSfile: str_support.h,v $ $Revision: 1.1.11.1 $ (DEC) $Date: 2001/10/29 20:22:01 $
 */
/*
 * (c) Copyright 1990, 1991, 1992 OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.2
 */

#ifndef _STR_SUPPORT_H_
#define _STR_SUPPORT_H_

#include <standards.h>
#include <sys/stream.h>

/* forward decls for C++ */
#ifdef __cplusplus
struct slock;
struct tt_timent;
struct tt_timejob;
struct tt_timetab;
#endif

#if MACH_ASSERT
#define PRIVATE_STATIC static
#else
#define PRIVATE_STATIC
#endif /* MACH_ASSERT */

struct tt_timejob {
#ifndef __cplusplus
	simple_lock_t		tj_lock;	/* copy of main lock pointer
						 * stored in tmtab -- needed
						 * here so that tt_qenable
						 * can work with just a job
						 * pointer.
						 */
#else
	struct slock		*tj_lock;	/* use simple_lock_t base type
						 * and forward struct decl above
						 * so this can be used without
						 * /usr/sys/include access
						 */
#endif
	struct tt_timent	*tj_ent;	/* back pointer to ent */
	struct tt_timejob	*tj_next;	/* next in linked list */
	struct tt_timejob	*tj_prev;	/* prev in linked list */
	void			(*tj_func) __((int, char *));	/* function */
	void			*tj_arg;	/* function argument */
	int			tj_id;		/* arg for untimeout */
	char			tj_inuse;	/* inuse "bit" */
};

struct tt_timent {
	struct tt_timetab	*te_tab;	/* back pointer to table */
	void			(*te_func) __((int, char *));	/* function to call */
	queue_t			*te_q;		/* queue to run on */
	struct tt_timejob	*te_jobs;	/* list of jobs */
};

struct tt_entdesc {
	void			(*ted_func) __((int, char *));	/* function to call */
	int			ted_qtype;	/* read or write queue */
};

/* Values for ted_qtype */
#define TT_TIMEOUT_RQ	1
#define	TT_TIMEOUT_WQ	2

struct tt_tabdesc {
	struct tt_timetab	*tbd_tabs;	/* pool of timetabs */
	int			tbd_entcnt;	/* count of timents */
	struct tt_timent	*tbd_ents;	/* timents */
	struct tt_entdesc	*tbd_entdesc;	/* timent descriptors */
	int			tbd_freesz;	/* size of job freelist */
	struct tt_timejob	*tbd_freelist;	/* job freelist */
	struct tt_timejob	*(*tbd_allocproc) __((int, char *));	/* job allocator */
	void			(*tbd_freeproc) __((int, char *));	/* job free-er */
	char			tbd_alloc_panic; /* panic on alloc. failure? */
	char			tbd_timeout_panic;/* panic on timeout failure?*/
};

struct tt_timetab {
#ifndef __cplusplus
	simple_lock_t		tb_lock;	/* locks this, plus all attached
						 * structures, plus (*tb_ready)
						 */
#else
	struct slock		*tb_lock;
#endif
	struct tt_timent	*tb_timents;	    /* timents */
	unsigned short		tb_entcnt;	    /* number of timents */
	struct tt_timejob	**tb_ready;	    /* put ready job here */

	/* If tb_freelist is true, then the tt_timeout package manages
	 * a fixed pool of jobs (of size tb_freesz).  Otherwise, the 
	 * module/driver must provide routines to allocate and free jobs.
	 */
	struct tt_timejob	*tb_freelist;	    /* free job structs */
	int			tb_freesz;
	struct tt_timejob	*(*tb_allocproc) __((int, char *));  /* proc. to alloc jobs */
	void			(*tb_freeproc) __((int, char *));   /* proc. to free jobs */
	char			tb_alloc_panic;	/* panic on alloc. failure? */
	char			tb_timeout_panic;/* panic on timeout failure? */
};

_BEGIN_CPLUSPLUS
extern int tt_timeout_pending(struct tt_timetab *, int);

PRIVATE_STATIC void tt_free_job(struct tt_timetab *, struct tt_timejob *);

extern int tt_timeout_pending_cnt(struct tt_timetab *, int);

extern int tt_timeout(struct tt_timetab *, int, void *, int);

extern void tt_untimeout(struct tt_timetab *, int, int);

extern void tt_unbufcall(struct tt_timetab *, int, int);

extern void tt_cancel(struct tt_timetab *, int, int, void (*) __((int, char *)));

PRIVATE_STATIC void tt_qenable(struct tt_timejob *);

extern void tt_insert_job(struct tt_timetab *, int, struct tt_timejob *);

PRIVATE_STATIC struct tt_timejob * 
	tt_remove_job(struct tt_timetab *, int, struct tt_timejob *);

PRIVATE_STATIC struct tt_timejob *tt_find_job(struct tt_timetab *, int);

extern struct tt_timejob *tt_alloc_job(struct tt_timetab *);

PRIVATE_STATIC void tt_get_job(struct tt_timejob *, void (**) __((int, char *)), void **arg);

extern int tt_run_jobs(struct tt_timetab *);

extern struct tt_timetab *
tt_init_timetab(        struct tt_tabdesc       *td,
                        int                     unit,
                        queue_t                 *wq,
#ifndef __cplusplus
                        simple_lock_t           lock,
#else
                        struct slock            *lock,
#endif
                        struct tt_timejob       **ready_loc
        );
_END_CPLUSPLUS

#endif /* _STR_SUPPORT_H_ */
