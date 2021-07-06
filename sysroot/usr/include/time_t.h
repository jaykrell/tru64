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
 * @(#)$RCSfile: time_t.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1998/12/02 20:42:53 $
 */

#ifndef _TIME_T_H_
#define _TIME_T_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <standards.h>

typedef int             time_t;

#ifdef _TIME64_T
typedef long            time64_t;

/* set max/min values for 64bit->32bit bounds checking */
#define _MINTIME32 (~0L<<((sizeof(time_t)*8)-1))
#define _MAXTIME32 ~(_MINTIME32)

/* macros to convert different size time_t's */

/* void TIMET32TO64(time_t, time64_t) */
#define TIMET32TO64(__timet32, __timet64) \
        (__timet64 = (time64_t)__timet32, 0 )

/* int TIMET64TO32(time64_t, time_t)
 * returns 1 if over/under-flow occurs during conversion, 0 otherwise */
#define TIMET64TO32(__timet64, __timet32) ( \
 	__timet32 = (time_t)__timet64, \
	((__timet64 > _MAXTIME32) || (__timet64 < _MINTIME32)) )
#endif /* _TIME64_T */

#ifdef __cplusplus
}
#endif
#endif /* _TIME_T_H_ */
