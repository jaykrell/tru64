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
 *	@(#)$RCSfile: slu.h,v $ $Revision: 1.1.5.1 $ (DEC) $Date: 2000/09/26 17:56:44 $
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
 * derived from slu.h	4.1	(ULTRIX)	8/9/90
 */

/*
 *
 * Modification history
 *
 *   4-Jul-90	Randall Brown
 *		Created file.
 */

#ifndef _TC_SLU_H_
#define _TC_SLU_H_

#ifndef __cplusplus

struct slu {
    int	(*mouse_init)();
    int	(*mouse_putc)();
    int (*mouse_getc)();
    int	(*kbd_init)();
    int	(*kbd_putc)();
    int (*kbd_getc)();
    int (*slu_putc)();		/* put char out serial line unit */
    struct tty *slu_tty;
};

extern struct slu slu;

#endif /* __cplusplus */

#endif
