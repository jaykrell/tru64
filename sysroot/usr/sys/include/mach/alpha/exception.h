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

#ifndef	_MACH_ALPHA_EXCEPTION_H_
#define	_MACH_ALPHA_EXCEPTION_H_

/*
 * Codes and subcodes for Alpha exceptions.
 */

/* 
 *	Codes to go with EXC_SOFTWARE
 */
#define	EXC_ALPHA_SOFT_STK	0x10003L
#define	EXC_ALPHA_SOFT_SEGV	0x10004L
#define EXC_ALPHA_INST_TRAP	0x10005L

/*
 *	EXC_BREAKPOINT subcodes
 */
#define	EXC_ALPHA_BPT			1L
#define EXC_ALPHA_TRACE			2L

#endif	/* _MACH_ALPHA_EXCEPTION_H_ */
