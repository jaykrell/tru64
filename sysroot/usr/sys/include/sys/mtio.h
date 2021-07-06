/*
 * @DEC_COPYRIGHT@
 */
/*
 ***************************************************************************
 *                     !!!!! NOTE !!!!!
 * 
 * THIS FILE IS INCLUDED BY THE DECNSR PRODUCT.  PLEASE DO NOT CHANGE THE 
 * INTERFACES WITHIN IT WITHOUT NOTIFYING THE DECNSR GROUP!
 *
 ***************************************************************************
 */

/*
 * HISTORY
 * $Log: mtio.h,v $
 * Revision 4.2.33.1  2002/10/10  20:37:47  Fred_Knight
 * 	Merge reserve/release/tur defines from v5.1a.
 *
 * Revision 4.2.15.5  1998/09/01  19:13:35  Jan_Reimers
 * 	Added structures mtrdposs, mtrdposl, mtrdpos for MTIOCRDPOS ioctl
 * 	Added MTSEEK and MTSEEKDS definitions for MTIOCTOP command
 * 	[1998/08/14  13:53:05  Jan_Reimers]
 *
 * Revision 4.2.15.4  1998/03/25  20:47:51  Jan_Reimers
 * 	Changed the default tape device special file names
 * 	[1998/03/24  21:43:44  Jan_Reimers]
 * 
 * Revision 4.2.15.3  1998/01/15  20:08:23  Anton_Verhulst
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL11:PTCOS_BL14 **
 * 		** Ancestor revision:	4.2.13.4 **
 * 		** Merge revision:	4.2.13.5 **
 * 	 	** End **
 * 	[1998/01/15  20:06:42  Anton_Verhulst]
 * 
 * Revision 4.2.13.5  1997/09/30  18:12:10  Jan_Reimers
 * 	Added MTDISINT and MTENAINT ioctl call definitions
 * 	[1997/09/29  19:51:07  Jan_Reimers]
 * 
 * Revision 4.2.13.4  1997/08/18  14:10:56  Jan_Reimers
 * 	Added comment for DECNSR group
 * 	[1997/08/13  18:26:09  Jan_Reimers]
 * 
 * Revision 4.2.15.2  1997/02/07  19:32:27  John_Flanagan
 * 	Pull in PTmin BL4 version needed for merge
 * 	[1997/02/07  18:40:45  John_Flanagan]
 * 
 * Revision 4.2.13.3  1997/01/24  19:52:05  Jan_Reimers
 * 	Added MTENASGIO and MTDISSGIO
 * 	[1997/01/13  21:40:10  Jan_Reimers]
 * 
 * Revision 4.2.13.2  1996/10/18  20:32:17  John_Meneghini
 * 	Tape Positioning project:
 * 	  Extensions to mtget struct
 * 	    - changed residual count from short to an u_int
 * 	    - added file number element
 * 	    - added block number element
 * 	    - added Extended Error Information element
 * 	[1996/10/16  21:03:24  John_Meneghini]
 * 
 * Revision 4.2.7.2  1995/10/19  14:29:34  Jan_Reimers
 * 	Fixed a lint problem with unterminated comments
 * 	[1995/10/13  13:27:47  Jan_Reimers]
 * 
 * Revision 4.2.3.4  1992/06/03  13:45:14  Paul_Hansen
 * 	Merged in Silver BL7
 * 	[92/06/03  13:35:37  Paul_Hansen]
 * 
 * Revision 4.2.3.3  92/03/18  22:25:36  Shashi_Mangalat
 * 	Merged in Silver BL5
 * 	Merged in changes from LA. CAM support added [Janet_Schank]
 * 	[92/03/18  22:11:00  Shashi_Mangalat]
 * 
 * Revision 4.2.3.2  92/01/28  18:39:27  Shashi_Mangalat
 * 	Merged in Silver BL3
 * 	[92/01/28  18:20:12  Shashi_Mangalat]
 * 
 * 	Merge from ODE/TIN: revision 3.5.9.2
 * 	date: 91/11/14 15:51:21;  author: devrcs;  state: Exp;  lines added/del: 2/2
 * 	sccs rev: 3.6;  orig date: 91/11/05 15:12:13;  orig author: burns
 * 	Cleaned up comments.
 * 	[91/12/05  11:53:29  William_Burns]
 * 
 * Revision 4.2.1.2  92/01/24  18:15:22  devbld_gsf
 * 	First AG_BL3 version. Moved from AG baselevel delivery tree.
 * 
 * Revision 4.2  91/09/19  22:59:04  devbld
 * 	Adding ODE Headers
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: mtio.h,v $ $Revision: 4.2.33.1 $ (DEC) $Date: 2002/10/10 20:37:47 $
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
 * derived from mtio.h	2.2	(ULTRIX/OSF)	1/15/91
 */
/*
 * mtio.h
 *
 * Modification History:
 *
 * 18-Jun-91	Tom Tierney
 *	Added norewind, first unit, high density default tape device
 *	(DEFTAPE_NH).
 *
 * 12-Jan-91	Fred Canter
 *
 *	Changed default tape device (DEFTAPE) to rmt0h.
 *
 */


/*
 * Copyright (C) 1988,1989 Encore Computer Corporation.  All Rights Reserved
 *
 * Property of Encore Computer Corporation.
 * This software is made available solely pursuant to the terms of
 * a software license agreement which governs its use. Unauthorized
 * duplication, distribution or sale are strictly prohibited.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *

 */
/*
 * Structures and definitions for mag tape io control commands
 */

#ifndef	_SYS_MTIO_H_
#define _SYS_MTIO_H_

#include <sys/types.h>
#include <sys/deveei.h>

/* Structure for MTIOCTOP ioctl - mag tape operation command */
struct	mtop	{
	short	mt_op;			/* Operations defined below	*/
	daddr_t mt_count;		/* How many of them		*/
};

/* Structure for MTIOCGET ioctl - mag tape get status command */
struct	mtget	{
	short	mt_type;		/* Type of device defined below */
	short	mt_dsreg;		/* ``drive status'' register	*/
	short	mt_erreg;		/* ``error'' register		*/
	u_int	mt_resid;		/* Residual count		*/
	long	mt_fileno;		/* file number */
	long	mt_blkno;		/* block number */
	DEV_EEI_STATUS eei;             /* Extended Error Information */
};

/*
 * The following two structures are the user definitions used for the
 * READ POSITION command.
 */
struct	mtrdposs {	/* short data format */
	u_char			:1,	/* unused			*/
		perr		:1,	/* Position overflow error	*/
		bpu		:1,	/* Block position unknown	*/
				:1,	/* unused			*/
		bycu		:1,	/* Byte count unknown		*/
		bcu		:1,	/* Block count unknown		*/
		eop		:1,	/* End of partition		*/
		bop		:1;	/* Beginning of partition	*/
	u_int	first_blk;		/* First block location		*/
	u_int	last_blk;		/* Last block location		*/
	u_int	num_blks;		/* Number of blocks in buffer 	*/
	u_int	num_bytes;		/* Number of bytes in buffer 	*/
};

struct	mtrdposl {	/* long data format */
	u_char			:2,	/* unused			*/
		bpu		:1,	/* Block position unknown	*/
		mpu		:1,	/* Mark position unknown	*/
				:2,	/* unused			*/
		eop		:1,	/* End of partition		*/
		bop		:1;	/* Beginning of partition	*/
	u_long	blk_num;		/* Block number			*/
	u_long	file_num;		/* File number			*/
};

/*
 * Structure for MTIOCRDPOS ioctl - READ POSITION command
 * The first u_char is used to provide input to the tape driver on the
 * type of command the application is requesting.
 */
struct mtrdpos {
	u_char	long_format	:1,	/* long data format		*/
		dev_specific	:1,	/* device specific address (BT)	*/
				:6;	/* unused			*/
	union {
		struct mtrdposs s;
		struct mtrdposl l;
	} un;
};

/* Basic definitions common to various tape drivers */
#define b_repcnt	b_bcount		/* Repeat count 	*/
/*  #define b_command	b_resid		 	Command value NOTE: in buf.h */
#define SSEEK		0x01			/* Seeking		*/
#define SIO		0x02			/* Doing sequential i/o */
#define SCOM		0x03			/* Sending control cmd. */
#define SREW		0x04			/* Sending drive rewnd. */
#define SERASE		0x05			/* Erase interrec. gap	*/
#define SERASED 	0x06			/* Erased interrec. gap */
#define MASKREG(r)	((r) & 0xffff)		/* Register mask	*/
#define INF		(daddr_t)1000000L	/* Invalid block number */
#define DISEOT		0x01			/* Disable EOT code	*/
#define DBSIZE		0x20			/* Dump blocksize (32)	*/
#define PHYS(a,b)	((b)((int)(a)&0x7fffffff)) /* Physical dump dev.*/

#define REWIND_DEV	0x00		/* Rewind device		*/
#define NO_REWIND	0x01		/* No rewind device		*/
#define DENS_MASK	0x06		/* Mask off the density bits	*/
#define LOW_DENS	0x00		/* Low density			*/
#define MED_DENS	0x04		/* Medium density		*/
#define HI_DENS		0x02		/* High density			*/
#define AUX_DENS	0x06		/* Auxiliary density		*/
#define MTLR		(LOW_DENS|REWIND_DEV)	/* Low density/Rewind        */
#define MTMR		(MED_DENS|REWIND_DEV)	/* Medium density/Rewind     */
#define MTHR		(HI_DENS|REWIND_DEV)	/* High density/Rewind       */
#define MTAR		(AUX_DENS|REWIND_DEV)	/* Auxiliary density/Rewind  */
#define MTLN		(LOW_DENS|NO_REWIND)	/* Low density/Norewind      */ 
#define MTMN		(MED_DENS|NO_REWIND)	/* Medium density/Norewind   */
#define MTHN		(HI_DENS|NO_REWIND)	/* High density/Norewind     */
#define MTAN		(AUX_DENS|NO_REWIND)	/* Auxiliary density/Rewind  */
#define MTX0		0x00			/* eXperimental 0 -historical*/
#define MTX1		0x01			/* eXperimental 1 -historical*/

/* Tape operation definitions for operation word (mt_op) */
#define MTWEOF		0x00		/* Write end-of-file record	*/
#define MTFSF		0x01		/* Forward space file		*/
#define MTBSF		0x02		/* Backward space file		*/
#define MTFSR		0x03		/* Forward space record 	*/
#define MTBSR		0x04		/* Backward space record	*/
#define MTREW		0x05		/* Rewind			*/
#define MTOFFL		0x06		/* Rewind and unload tape	*/
#define MTNOP		0x07		/* No operation 		*/
#define MTCACHE 	0x08		/* Enable tmscp caching 	*/
#define MTNOCACHE	0x09		/* Disable tmscp caching	*/
#define MTCSE		0x0a		/* Clear serious exception	*/
#define MTCLX		0x0b		/* Clear hard/soft-ware problem */
#define MTCLS		0x0c		/* Clear subsystem		*/
#define MTENAEOT	0x0d		/* Enable default eot code	*/
#define MTDISEOT	0x0e		/* Disable default eot code	*/
#define MTFLUSH		0x0f		/* Flush controller write cache */
#define MTGTON		0x10		/* Turn on gapless TBC tm32	*/
#define MTGTOFF		0x11		/* Torn off gapless mode	*/
#define MTRETEN		0x12		/* Retension command qic like	*/
#define MTSEOD		0x13		/* Space to end of recorded data */
#define MTERASE		0x14		/* Erase tape command.		*/
#define MTONLINE	0x15		/* Load a tape opposite of MTOFFL*/
#define MTLOAD		0x16		/* Issue a load tape		*/
#define MTUNLOAD	0x17		/* Issue an unload tape		*/
#define MTENASGIO	0x18		/* Enable scatter/gather IO	*/
#define MTDISSGIO	0x19		/* Disable scatter/gather IO	*/
#define MTDISINT        0x1a            /* Disable interrupting tape movement */
#define MTENAINT        0x1b            /* Enable interrupting tape movement */
#define MTSEEK          0x1c            /* LOCATE command		*/
#define MTSEEKDS        0x1d            /* LOCATE command (device specific) */
#define MTRESERVE	0x1e		/* SCSI-2 reserve		*/
#define MTRELEASE	0x1f		/* SCSI-2 release		*/
#define MTREADY		0x20		/* TUR command			*/

/* Get status definitions for device type word (mt_type) */
#define MT_ISTS 	0x01		/* ts11/ts05/tu80		*/
#define MT_ISHT 	0x02		/* tm03/te16/tu45/tu77		*/
#define MT_ISTM 	0x03		/* tm11/te10			*/
#define MT_ISMT 	0x04		/* tm78/tu78			*/
#define MT_ISUT 	0x05		/* tu45 			*/
#define MT_ISTMSCP	0x06		/* All tmscp tape drives	*/
#define MT_ISST		0x07		/* TZK50 on VS2000/MV2000	*/
#define MT_ISSCSI	0x08		/* SCSI tapes (TZK50 & TZ30)	*/

/* Default tape device definitions for programs */

#ifndef	KERNEL
#define DEFTAPE		"/dev/tape/tape0_d1"  /* 1st tape, rewind, high dens. */
#define DEFTAPE_NH	"/dev/ntape/tape0_d1" /* 1st tape, norew., high dens. */
#define DEFTAPE_RM	"/dev/tape/tape0_d2"  /* 1st tape, rewind, med. dens. */
#define DEFTAPE_RH	"/dev/tape/tape0_d1"  /* 1st tape, rewind, high dens. */
#define DEFTAPE_NL	"/dev/ntape/tape0_d0" /* 1st tape, norew., low dens.  */
#define DEFTAPE_NM	"/dev/ntape/tape0_d2" /* 1st tape, norew., med. dens. */
#endif /* KERNEL */
#endif /* _SYS_MTIO_H_ */
