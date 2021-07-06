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
 * @(#)$RCSfile: idset.h,v $ $Revision: 1.1.8.1 $ (DEC) $Date: 2002/03/12 20:31:32 $
 */
#ifndef _SYS_IDSET_H
#define _SYS_IDSET_H

/*
 *	File:	idset.h
 *
 *	operations on id sets
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef void *idset_t;

#ifndef SET_CURSOR_INIT
#define SET_CURSOR_INIT		0

#define SET_CURSOR_FIRST	1
#define SET_CURSOR_WRAP		2
#define SET_CURSOR_CONSUME	4
#endif

typedef unsigned int id_cursor_t, *id_cursor_p;

extern int idsetcreate(idset_t *, int);
extern int idsetdestroy(idset_t *);
extern int idsetisvalid(idset_t);

extern int idcountset(idset_t);
extern int idemptyset(idset_t);
extern int idfillset(idset_t);
extern int idaddset(idset_t, int);
extern int iddelset(idset_t, int);

extern int idismember(idset_t, int);
extern int idisemptyset(idset_t);

extern int idorset(idset_t, idset_t, idset_t);
extern int idxorset(idset_t, idset_t, idset_t);
extern int idandset(idset_t, idset_t, idset_t);
extern int iddiffset(idset_t, idset_t, idset_t);
extern int idcopyset(idset_t, idset_t);

extern int id_foreach(idset_t, unsigned int, id_cursor_t *);

extern int idsetmaxvalid(int, idset_t);
#define MAX_RADSET_INDEX	0
#define MAX_CPUSET_INDEX	1

#ifdef __cplusplus
} /* extern "C" */
#endif

#ifdef _KERNEL

#ifndef BITS_PER_LONG
#define BITS_PER_LONG		(sizeof(long) * NBBY)
#endif

/*
 * The number of longs in a idset_t of __n__ elements
 */
#define IDSET_LSIZE(__n__)						\
	(((__n__) + ((BITS_PER_LONG) - 1)) / (BITS_PER_LONG))

/*
 * The maximum number of bits in a idset_t
 */
#define IDSET_NBITS(__n__)	IDSET_LSIZE(__n__) * BITS_PER_LONG

/*
 * Index into the embedded idset_t bits[] array for a given bit __i__
 */
#define IDSET_INDEX(__i__)	((__i__) / BITS_PER_LONG)

/*
 * Magic numbers
 */
#define IDSET_HEADER_LSIZE       1
#define IDSET_HEADER_NBYTES      (IDSET_HEADER_LSIZE * sizeof(long))

#endif /* _KERNEL */

#endif /* _SYS_IDSET_H */
