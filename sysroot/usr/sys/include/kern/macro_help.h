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
 *	@(#)$RCSfile: macro_help.h,v $ $Revision: 4.2 $ (DEC) $Date: 1991/09/19 22:26:10 $
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
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */
/*
 *	File:	kern/macro_help.h
 *
 *	Provide help in making lint-free macro routines
 *
 */

#ifndef	_KERN_MACRO_HELP_H_
#define _KERN_MACRO_HELP_H_

#include <mach/boolean.h>

#ifdef	lint
boolean_t	NEVER;
boolean_t	ALWAYS;
#else	/* lint */
#define		NEVER		FALSE
#define		ALWAYS		TRUE
#endif	/* lint */

#define		MACRO_BEGIN	do {
#define		MACRO_END	} while (NEVER)

#define		MACRO_RETURN	if (ALWAYS) return

#endif	/* _KERN_MACRO_HELP_H_ */
