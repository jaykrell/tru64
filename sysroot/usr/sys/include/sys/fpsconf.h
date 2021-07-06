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
 *	@(#)$RCSfile: fpsconf.h,v $ $Revision: 4.2 $ (DEC) $Date: 1991/09/19 22:57:39 $
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
 *	(c) 1984 Copyright	Apunix Computer Services
 *
 * Revision 1.4  85/02/09  11:13:56  phb
 * Added provisions for APSIM to load the correct tmrom file when it starts up.
 * 
 * Revision 1.3  84/10/15  23:52:55  phb
 * Updated for specification of all system dependent paramaters in
 * the fpsconf.h file.
 * 
 * Revision 1.2  84/05/29  00:08:14  phb
 * Added TM4K & TM2K defines.
 * 
 * Revision 1.1  83/12/15  21:03:00  phb
 * Initial revision
 * 
 */

/*
 *	Configuration file for Berkeley 4.2 UNIX
 */

/*
 *	All we do here is turn on all the 4.[12] stuff
 */

#ifndef	_SYS_FPSCONF_H_
#define _SYS_FPSCONF_H_

#define BERK4
#define BSD42
#define FPSRESET

/*
 * We need types.h included when a user program includes fpsreg.h
 */
#define TYPESDOTH

/*====================== Local Changes Begin Here ============================*/

/*
 * Maximum size transfer allowed over the bus.  In the case of a VAX this
 * number is 60K due to limitations of the UBA.  For a PDP-11 or other
 * 16 bit host computers it can probably be 64K.
 */
#define MINPHYS		(60*1024L)	/* from /sys/bio.c: minphys() */

/*
 *	Possible options here are lines:
 *
 *		#define	FPSPARITY
 *			For sites that have the memory parity option.
 *		#define	NEWFORMAT
 *			For vax sites with the vax interface board installed
 *			in the AP (this allows the support of 32 bit integer
 *			transfers with the proper conversion between VAX
 *			and AP format)
 */
#define NEWFORMAT

/*
 *	Most AP's come preset at unibus interrupt level br4, if yours
 *	is different, you'll need to change the line below.
 */
#define SPLHI	spl4()

/*
 *	Here one of the following MUST be defined:
 *
 *		#define TM4K
 *			For sites with 4K of TM ROM (all FPS-5000 series and
 *			most late model AP-120B's and FPS-100's).
 *		#define TM2K
 *			For sites with 2K of TM ROM
 *
 *	The failure to define the correct option will cause various math
 *	library routines to behave strangely (e.g., vsmul).
 */
#define TM4K

/*
 *	The following determines the maximum program source size
 *	that may be installed in your machine.  For the FPS-5000
 *	series this number should be either 16K (FPS 5105, 5110, 5410,
 *	5420, and 5430) or 32K (FPS 5205, 5210, 5310, and 5320), however
 *	older AP-120B's and FPS-100's may have to set this number
 *	as low as 4K or 2K due to wrap around of the program source
 *	memory address logic.
 */
#define MAXPS	(32*1024)

/*
 *	Any path dependencies are here
 */

#define APAL	"/usr/local/bin/apal"
#define APLINK	"/usr/local/bin/aplink"
#define CAPVFC	"/usr/local/bin/capvfc"
#define APVFC	"/usr/local/bin/apvfc"
#define GPAL	"/usr/local/bin/gpal"
#define GPLOAD	"/usr/local/bin/gpload"
#define APLIB	"/usr/local/lib/aplib"
#ifdef	TM4K
#define TMROM	"/usr/local/lib/fpstmrom.4k"
#endif
#ifdef	TM2K
#define TMROM	"/usr/local/lib/fpstmrom.2k"
#endif

/*
 * Where the fps.h file is that has the definition of NFPS (the number
 * of AP's) in it.  FILL IN THE NAME OF YOUR SYSTEM BELOW!!!
 */
#define FPSH	"/sys/SYSTEMNAME/fps.h"

/*
 *	Number of lines actually printed on a line printer page
 *			(for listings)
 */
#ifndef	NLINES
#define NLINES		56
#endif

/*
 *	APSIM Configuration dependent pramaters
 *
 *		Change according to your system and your AP-120B memory sizes
 *		and options.  These only effect the simulator, and since
 *		all memory is simulated by a temporary file it may not be
 *		advisable to increase MDSIZE above 8K even if you actually
 *		have more memory in your AP, or else the temporary files
 *		will be inordinately large.
 */
#define FASTMEM		/* REMOVE IF YOU HAVE STANDARD OR SLOW DATA MEMORY */
#define MDSIZE		8192L	/* default size of main data memory */
#define PSSIZE		1536L	/* default size of program source memory */
#define ROMLOW		04000L	/* low table memory ROM address */
#define ROMHIGH		05000L	/* high table memory ROM address */
#define RAMLOW		010000L	/* low table memory RAM address */
#define RAMHIGH		020000L	/* default high table memory RAM address */

/*
 *  We'd really hate to define these in the standard places just for this
 *  special device so they'll go here instead.
 */
#define SIGFPS	16
#define EFPS	100

#endif	/* _SYS_FPSCONF_H_ */
