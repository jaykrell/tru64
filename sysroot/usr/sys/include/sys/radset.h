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
 * @(#)$RCSfile: radset.h,v $ $Revision: 1.1.6.2 $ (DEC) $Date: 2000/10/18 14:33:25 $
 */

#ifndef _SYS_RADSET_H_
#define _SYS_RADSET_H_

/*
 *	File:	radset.h
 *
 *	operations on Resource Affinity Group sets
 */

#include <sys/idset.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void *radset_t;
typedef int radid_t;
typedef id_cursor_t rad_cursor_t;

extern int radsetcreate(radset_t *);
extern int radsetdestroy(radset_t *);
extern int radsetisvalid(radset_t);

extern int radcountset(radset_t);
extern int rademptyset(radset_t);
extern int radfillset(radset_t);
extern int radaddset(radset_t, int);
extern int raddelset(radset_t, int);

extern int radismember(radset_t, int);
extern int radisemptyset(radset_t);

extern int radorset(radset_t, radset_t, radset_t);
extern int radxorset(radset_t, radset_t, radset_t);
extern int radandset(radset_t, radset_t, radset_t);
extern int raddiffset(radset_t, radset_t, radset_t);
extern int radcopyset(radset_t, radset_t);

extern int rad_foreach(radset_t, unsigned int, rad_cursor_t *);

#ifdef __cplusplus
} /* extern "C" */
#endif

/*
 * Return TRUE if id is the only member in set.
 */
#define radismember_excl(__set__, __radid__)			\
	(radismember(__set__, __radid__) && (radcountset(__set__) == 1))

#ifdef _KERNEL
/*
 * The number of valid bits in a radset_t (power of 2)
 */
#define RAD_NBITS		nrads

/*
 * The number of longs in a radset_t of RAD_NBITS elements
 */
#define RADSET_LSIZE    ((RAD_NBITS + ((BITS_PER_LONG) - 1)) / (BITS_PER_LONG))

#define RADSET_STRUCT_LSIZE (RADSET_LSIZE + IDSET_HEADER_LSIZE)

#define RADSET_STRUCT_NBYTES ((RADSET_LSIZE+IDSET_HEADER_LSIZE) * sizeof(long))

extern void	radsetinit(radset_t);
#endif	/* _KERNEL */

#endif /* _SYS_RADSET_H_ */
