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
 *	@(#)$RCSfile: mach_error.h,v $ $Revision: 4.2.3.4 $ (DEC) $Date: 1998/07/16 14:40:15 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */ 

#ifndef	_LIB_MACH_ERROR_H_
#define	_LIB_MACH_ERROR_H_	1

#ifdef __cplusplus
extern "C" {
#endif

#include <mach/error.h>

char		*mach_error_string(
/*
 *	Returns a string appropriate to the error argument given
 */
	mach_error_t error_value
				);

void		mach_error(
/*
 *	Prints an appropriate message on the standard error stream
 */
	char 		*str,
	mach_error_t	error_value
				);

char		*mach_error_type(
/*
 *	Returns a string with the error system, subsystem and code
*/
	mach_error_t	error_value
				);

#ifdef __cplusplus
}
#endif

#endif	/* _LIB_MACH_ERROR_H_ */
