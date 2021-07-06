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
 * @(#)$RCSfile: tspriocntl.h,v $ $Revision: 1.1.4.3 $ (DEC) $Date: 1993/10/11 18:30:07 $
 */

#ifndef _SYS_TSPRIOCNTL_H_
#define _SYS_TSPRIOCNTL_H_

#define TS_NOCHANGE (-32768)

typedef struct
{
	short ts_maxupri;	/* Limits of user priority range. */
} tsinfo_t;

typedef struct
{
	short ts_uprilim;	/* Time-Sharing user priority limit */
	short ts_upri;		/* Time-Sharing user priority */
} tsparms_t;

#endif /* ifndef _SYS_TSPRIOCNTL_H_ */
