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
 * @(#)$RCSfile: scsi_processor.h,v $ $Revision: 1.1.9.1 $ (DEC) $Date: 2002/01/08 21:48:42 $
 */

#ifndef _SCSI_PROC_
#define _SCSI_PROC_

/* ---------------------------------------------------------------------- */

/* scsi_processor.h

   Contains all the structures and defines for the SCSI II spec,
   chapter 11, processor devices.
*/

/* ---------------------------------------------------------------------- */

/* 
 * Receive defines.
 */

/* 
 * The receive cdb 6 bytes
 */
typedef struct proc_receive_cdb {
	u_char	opcode;		/* 0x08					*/
	u_char		:5,	/* 5 bits reservered			*/
		lun	:3;	/* Logical unit number			*/
	u_char	alloc_len2;	/* Parameter length (MSB).		*/
	u_char	alloc_len1;	/* Parameter length (MID).		*/
	u_char	alloc_len0;	/* Parameter length (LSB).		*/
	u_char	control;	/* Control byte				*/
}PROC_RECEIVE_CDB;

/*
 * The opcode for receive
 */
#define PROC_RECEIVE_OP	0x08

/* ---------------------------------------------------------------------- */

/* 
 * Send defines.
 */

/* 
 * The send cdb 6 bytes
 */
typedef struct proc_send_cdb {
	u_char	opcode;		/* 0x0a					  */
	u_char	aen	:1,	/* Indicates normal (AEN/AER) data format */
			:4,	/* 4 bits reserveed			  */
		lun	:3;	/* Logical unit number			  */
	u_char	alloc_len2;	/* Parameter length (MSB).		  */
	u_char	alloc_len1;	/* Parameter length (MID).		  */
	u_char	alloc_len0;	/* Parameter length (LSB).		  */
	u_char	control;	/* Control byte				  */
}PROC_SEND_CDB;

/*
 * The opcode for send
 */
#define PROC_SEND_OP	0x0a

/*
 * From scsi-2
 */
typedef struct proc_send_aen {
	u_char	luntrn	:3,	/* logical unit number			*/
			:2,	/* reserved				*/
		luntar	:1,	/* luntrn is valid			*/
			:2;	/* reserved				*/
	u_char		:8;	/* reserved				*/
	u_char		:8;	/* reserved				*/
	u_char		:8;	/* reserved				*/
	u_char	data[64];	/* sense data bytes			*/
}PROC_SEND_AEN;

/*
 * From scsi-3
 */
typedef	struct	proc_send_aer {
	u_char		:7,	/* reserved				*/
		scsi3	:1;	/* Use ARE (not AEN) format		*/
	u_char		:8;	/* reserved				*/
	u_char		:8;	/* reserved				*/
	u_char		:8;	/* reserved				*/
	u_char	lun7;		/* MSB of scsi3 lun number		*/
	u_char	lun6;		/*  MID of scsi3 lun number		*/
	u_char	lun5;		/*  MID of scsi3 lun number		*/
	u_char	lun4;		/*  MID of scsi3 lun number		*/
	u_char	lun3;		/*  MID of scsi3 lun number		*/
	u_char	lun2;		/*  MID of scsi3 lun number		*/
	u_char	lun1;		/*  MID of scsi3 lun number		*/
	u_char	lun0;		/* LSB of scsi3 lun number		*/
	u_char	data[64];	/* sense data bytes			*/
}PROC_SEND_AER;

#endif /* _SCSI_PROC_ */
