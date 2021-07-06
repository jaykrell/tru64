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
 *	@(#)$RCSfile: mp.h,v $ $Revision: 4.2.10.2 $ (DEC) $Date: 1997/07/08 18:15:58 $
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
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *

 */


#ifndef _MP_H_
#define _MP_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <standards.h>
#ifndef BYTE_ORDER
#include <sys/types.h>
#include <machine/endian.h>
#endif

#include <stdio.h>

#define MINT struct mint
MINT
{	int len;
	short *val;
};

#define FREE(x) {if(x.len!=0) {free((void *)x.val); x.len=0;}}

#ifndef DBG
#define shfree(u) free((void *)u)
#else
#define shfree(u) { if(dbg) fprintf(stderr, "free %o\n", u); free((void *)u);}
extern int dbg;
#endif /* DBG */

#if     BYTE_ORDER == BIG_ENDIAN
struct half
{       short high;
        short low;
};
#else
struct half
{       short low;
        short high;
};
#endif /* BYTE_ORDER */

/* Function prototypes and type defintion for libmp */

typedef union {
	long xx;
	struct half yy;
	} SUM_UNION;

extern  void gcd __((MINT *,MINT *,MINT *));
extern  void invert __((MINT *, MINT *, MINT *));
extern  void m_add __((MINT *,MINT *,MINT *));
extern  void madd __((MINT *,MINT *,MINT *));
extern  void m_sub __((MINT *,MINT *,MINT *));
extern  void msub __((MINT *,MINT *,MINT *));
extern  void mdiv __((MINT *,MINT *,MINT *,MINT *));
extern int m_dsb __((int, int, short *, short *));
extern int m_trq __((int, int, int, int, int));
extern  void m_div __((MINT *,MINT *,MINT *,MINT *));
extern int m_in __((MINT *, int, FILE *));
extern  void m_out __((MINT *, int, FILE *));
extern  void sdiv __((MINT *, short, MINT *, short *));
extern  void s_div __((MINT *, short, MINT *, short *));
extern int min __((MINT *));
extern int omin __((MINT *));
extern  void mout __((MINT *));
extern  void omout __((MINT *));
extern  void fmout __((MINT *, FILE *));
extern int fmin __((MINT *, FILE *));
extern int msqrt __((MINT *,MINT *,MINT *));
extern  void mult __((MINT *,MINT *,MINT *));
extern  void m_mult __((MINT *,MINT *,MINT *));
extern  void tradd __((int *, SUM_UNION *, long));
extern  void pow __((MINT *,MINT *,MINT *,MINT *));
extern  void rpow __((MINT *, int ,MINT *));
extern  void move __((MINT *,MINT *));
extern  void dummy __((void));
extern  void fatal __((char *));
extern  void xfree __((MINT *));
extern  void mcan __((MINT *));
extern int mcmp __((MINT *,MINT *));

extern MINT *itom __((short));
extern short *xalloc __((int, char *));

#ifdef lint
extern xv_oid;
#define VOID xv_oid =
#else
#define VOID
#endif

#ifdef __cplusplus
}
#endif
#endif /* _MP_H_ */
