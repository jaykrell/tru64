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
 *	@(#)$RCSfile: strstat.h,v $ $Revision: 4.2.3.2 $ (DEC) $Date: 1993/08/18 21:32:39 $
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
/** Copyright (c) 1989  Mentat Inc.
 ** strstat.h 1.1, last change 8/8/89
 **/

#ifndef	_SRTSTAT_H
#define	_SRTSTAT_H

/* module statistics structure */
struct	module_stat {
	long	ms_pcnt;	/* count of calls to put proc */
	long	ms_scnt;	/* count of calls to service proc */
	long	ms_ocnt;	/* count of calls to open proc */
	long	ms_ccnt;	/* count of calls to close proc */
	long	ms_acnt;	/* count of calls to admin proc */
	char	* ms_xptr;	/* pointer to private statistics */
	short	ms_xsize;	/* length of private statistics buffer */
};
#endif
