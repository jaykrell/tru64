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
 * @(#)$RCSfile: mman.h,v $ $Revision: 1.1.6.4 $ (DEC) $Date: 1999/02/09 19:03:44 $
 */
/*
 *  Module Name:
 *	mman.h
 *
 *  Description:
 *	header file for SVR4 memcntl() system call
 */

#ifndef _SYS_SVR4_MMAN_H
#define _SYS_SVR4_MMAN_H

#ifdef __cplusplus
extern "C" {
#endif

/* 
 * page lock status  structure is used to save status of
 * the pages locked or unlocked, in a given address space .
 */

struct pg_lk_stat {
	struct pg_lk_stat *st_next;	/* list of next set of pages */
	int st_size;			/* Size of this list 	  */
	char st_flag[1];		/* Status, if locked/unlocked */
};

extern struct pg_lk_stat * save_pgstat(vm_map_entry_t, caddr_t, size_t);
void  undo_lockop(vm_map_entry_t, caddr_t, size_t, struct pg_lk_stat *, int);

/* The st_flag takes one of the following values */

#define LOCKED  1
#define UNLOCKED  2

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif	/* _SYS_SVR4_MMAN_H */
