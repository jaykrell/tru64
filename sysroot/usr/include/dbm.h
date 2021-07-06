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
 *	@(#)$RCSfile: dbm.h,v $ $Revision: 4.2.6.2 $ (DEC) $Date: 1994/01/07 18:31:27 $
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

#ifndef _DBM_H_
#define _DBM_H_

#ifndef NULL
/*
 * this is lunacy, we no longer use it (and never should have
 * unconditionally defined it), but, this whole file is for
 * backwards compatability - someone may rely on this.
 */
#define	NULL	0L
#endif

#include <ndbm.h>

_BEGIN_CPLUSPLUS
#ifdef _NO_PROTO
datum	fetch();
datum	firstkey();
datum	nextkey();
long	forder();
#else
extern datum	fetch(datum);
extern datum	firstkey(void);
extern datum	nextkey(datum);
extern long	forder(datum);
#endif	/* _NO_PROTO */

#if 0
datum	makdatum();
datum	firsthash();
long	calchash();
long	hashinc();
#endif
_END_CPLUSPLUS

#endif /* _DBM_H_ */
