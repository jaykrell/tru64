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

#ifndef _SYS_PROCSET_H
#define _SYS_PROCSET_H

#include <sys/types.h>

#ifdef _XOPEN_SOURCE_EXTENDED
#define _XSE(_id_) _##_id_
#else
#define _XSE(_id_) _id_
#endif

/*
 * This is the set of operators which can be applied to two sets of
 * processes to create a new set of processes.
 */
#if defined (_OSF_SOURCE) || !defined (_XOPEN_SOURCE_EXTENDED)
typedef enum idop {
#else
typedef enum {
#endif
	_XSE(POP_DIFF),	/* Set difference.  The processes which are in
			 * the left set and not in the right set.
			 */

	_XSE(POP_AND),	/* Set intersection.  The processes which are
			 * in both the left and right sets.
			 */

	_XSE(POP_OR),	/* Set union.  The processes which are in
			 * either the left or the right sets (or
			 * both).
			 */

	_XSE(POP_XOR)	/* Set exclusive or.  The processes which are
			 * in either the left or right sets but not in
			 * both.
			 */

#ifdef _KERNEL
	, POP_ANY	/*
			 * Internal use only.
			 */
#endif
} _XSE(idop_t);

/*
 * This is the set of legal values for an identifier type.  An idtype
 * and id together define a set of processes.
 */
#if defined (_OSF_SOURCE) || !defined (_XOPEN_SOURCE_EXTENDED)
typedef enum idtype {
#else
typedef enum {
#endif
	P_PID,	/* process id type */
	P_PPID,	/* parent process id type */
	P_PGID,	/* process group (job control group) id type */
	P_SID,	/* session id type */
	P_CID,	/* scheduling class id type */
	P_UID,	/* user id type */
	P_GID,	/* group id type */
	P_ALL	/* all processes */
} idtype_t;

/*
 * This structure is used to create a set of processes.  The set is
 * created by applying the operator to the two sets of processes
 * defined by this structure
 */
#ifndef _XOPEN_SOURCE_EXTENDED
typedef struct procset {
	idop_t p_op;		/* The operator to apply to the
				 * two sets (left and right) described
				 * below.
				 */

	idtype_t p_lidtype;	/* The id type for the left set. */
	id_t p_lid;		/* The id for the left set. */

	idtype_t p_ridtype;	/* The id type of for right set. */
	id_t p_rid;		/* The id of the right set. */
} procset_t;
#endif /* _XOPEN_SOURCE_EXTENDED */

#ifdef _OSF_SOURCE
/*
 * Use this macro to initialize a procset_t structure.
 */
#define	setprocset(psp, op, ltype, lid, rtype, rid) \
			(psp)->p_op		= (op); \
			(psp)->p_lidtype	= (ltype); \
			(psp)->p_lid		= (lid); \
			(psp)->p_ridtype	= (rtype); \
			(psp)->p_rid		= (rid);
#endif

#ifdef _KERNEL
#define P_INITPID  1
#define P_INITUID  0
#define P_INITPGID 0

extern int procset_check();
extern int procset_selected();
extern id_t procset_getid();
#endif

#endif	/* _SYS_PROCSET_H */
