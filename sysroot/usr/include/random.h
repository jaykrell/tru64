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
 *	@(#)$RCSfile: random.h,v $ $Revision: 4.2.10.4 $ (DEC) $Date: 1998/06/23 18:01:54 $
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
 * defintions for the reentrant versions of random()
 */
#ifndef	_RANDOM_H_
#define	_RANDOM_H_

#include <standards.h>
#include <sys/types.h>

/*
 * random_r.h
 *
 * Include file for thread-safe version of random.
 */

 typedef struct random_data {
 	int	*fptr;
	int	*rptr;
	int	*state;
	int	rand_type;
	int	rand_deg;
	int	rand_sep;
	int	*end_ptr;
} RANDOMD;

/* functions */

#ifdef __cplusplus
extern "C" {
#endif
extern	int	srandom_r __((unsigned, RANDOMD *));
extern	int	initstate_r __((unsigned, char *, size_t, char **, RANDOMD *));
extern	int	setstate_r __((const char *, char **, RANDOMD *));
extern	int	random_r __((int *, RANDOMD *));
#ifdef __cplusplus
}
#endif

#endif	/* _RANDOM_H_ */
