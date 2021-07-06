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
 *	@(#)$RCSfile: ttydev.h,v $ $Revision: 4.2.3.2 $ (DEC) $Date: 1995/12/01 15:15:11 $
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
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */

/*
 *
 * <bsd/sys/ttydev.h - a la 4.xBSD for BSD to AIX porting tools
 *	derived from BSD <sys/ttydev.h>
 * COPYRIGHT 1987 IBM CORP.
 */

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *

 */

/*
 * COMPATABILITY HEADER FILE --
 */
/*
 * Terminal definitions related to underlying hardware.
 */

#ifndef _SYS_TTYDEV_H_
#define	_SYS_TTYDEV_H_

#ifdef _USE_OLD_TTY

/*
 * Mask to clear speed bits
 */

#define CBAUD	0x0000001f

/*
 * Speeds
 */

#define	B0	0x00000000
#define	B50	0x00000001
#define	B75	0x00000002
#define	B110	0x00000003
#define	B134	0x00000004
#define	B150	0x00000005
#define	B200	0x00000006
#define	B300	0x00000007
#define	B600	0x00000008
#define	B1200	0x00000009
#define	B1800	0x0000000a
#define	B2400	0x0000000b
#define	B4800	0x0000000c
#define	B9600	0x0000000d
#define	B19200	0x0000000e
#define	B38400	0x0000000f
#define	B57600	0x00000010
#define	B115200	0x00000011
#define EXTA    B19200
#define EXTB    B38400
#endif /* _USE_OLD_TTY */

#endif	/* _SYS_TTYDEV_H_ */
