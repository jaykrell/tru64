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
 * @(#)$RCSfile: scsi_status.h,v $ $Revision: 1.1.7.2 $ (DEC) $Date: 1997/06/02 20:55:54 $
 */
#ifndef _SCSISTATUS_
#define _SCSISTATUS_

/* ---------------------------------------------------------------------- */

/* scsi_status.h	Version 1.02			Dec. 16, 1991 */

/*  This file contains the definitions as described in the SCSI-II spec,
    chapter six.

Modification History

	Version	  Date		Who	Reason

	1.00	11/09/90	janet	Created this file.
	1.01	03/26/91	janet	Changed name of file from scsi_chap6.h
	1.02	12/16/91	janet	Added SCSI_STAT_RESERVED define.
*/

/*
 * SCSI Status defines:
 */
#define SCSI_STAT_GOOD			0x00
#define SCSI_STAT_CHECK_CONDITION	0x02
#define SCSI_STAT_CONDITION_MET		0x04
#define SCSI_STAT_BUSY			0x08
#define SCSI_STAT_INTERMEDIATE		0x10
#define SCSI_STAT_INTER_COND_MET	0x14
#define SCSI_STAT_RESERVATION_CONFLICT	0x18
#define SCSI_STAT_COMMAND_TERMINATED	0x22
#define SCSI_STAT_QUEUE_FULL		0x28
#define SCSI_STAT_ACA_ACTIVE		0x30

/*
 * SCSI Status reserved bits.
 */
#define SCSI_STAT_RESERVED		0xc1

#endif /* _SCSISTATUS_ */
