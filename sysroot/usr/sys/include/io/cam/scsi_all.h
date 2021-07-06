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
 * @(#)$RCSfile: scsi_all.h,v $ $Revision: 1.1.62.3 $ (DEC) $Date: 2002/05/30 23:16:13 $
 */
#ifndef _SCSI_ALL_
#define _SCSI_ALL_

/* ---------------------------------------------------------------------- */

/* scsi_all.h		Version 1.00			Feb. 25, 1991 
*/

/* ---------------------------------------------------------------------- */
/* Include files. */

/*
 * You will need to include sys/h/types.h for this header file
 */

/* ---------------------------------------------------------------------- */

/*
 * GENERIC DEFINES FOR MODULES
 */

/* 
 * The size of our maximum out going data page for mode selects
 * OUR minimum data buffer is 512
 */
#define	ALL_MAX_PAGE_SIZE	256 

/* ---------------------------------------------------------------------- */

/* 
 *  The CHANGE DEFINITION command defines
 */


/*
 * CHANGE DEFINITION CDB 10 byte
 */

typedef struct all_change_def_cdb10 {
	u_char	opcode;		/* OPcode = 0X40			*/
	u_char		:5,	/* 5 bits reservered			*/
		lun	:3;	/* Logical unit number			*/
	u_char	save	:1,	/* Save control bit			*/
			:7;	/* 7 bits reserved			*/
	u_char	def_parm:7,	/* Definition parameter			*/
	                :1;	/* 1 bit reserved			*/
	u_char		:8;	/* Reserved byte			*/
	u_char		:8;	/* Reserved byte			*/
	u_char		:8;	/* Reserved byte			*/
	u_char		:8;	/* Reserved byte			*/
	u_char	param_ln;	/* Parameter data length		*/
	u_char	control;	/* Control				*/
}ALL_CHANGE_DEF_CDB10;

#define	ALL_CHANGE_USE_CURRENT	0x0	/* Use current definitions	*/
#define	ALL_CHANGE_USE_SCSI2	0x3	/* Use SCSI2 definitions	*/
#define	ALL_CHANGE_USE_SCSI3	0x4	/* Use SCSI3 definitions	*/
#define	ALL_CHANGE_USE_DEFAULTS	0x3f	/* Use mfgr default definitions	*/

/*
 * Opcode define for change definition
 */
#define ALL_CHANGE_DEF10_OP	0X40	/* The opcode			*/


/* ---------------------------------------------------------------------- */

/* 
 *  The COMPARE command defines
 */


/*
 * COMPARE CDB 10 byte
 */

typedef struct all_compare_cdb10 {
	u_char	opcode;		/* OPcode = 0X39			*/
	u_char	pad	:1,	/* Padding				*/
	    		:4,	/* 4 bits reservered			*/
		lun	:3;	/* Logical unit number			*/
	u_char		:8;	/* Reserved byte			*/
	u_char	param_len2;	/* Parameter length (MSB).		*/
	u_char	param_len1;	/* Parameter length (MID).		*/
	u_char	param_len0;	/* Parameter length (LSB).		*/
	u_char		:8;	/* Reserved byte			*/
	u_char		:8;	/* Reserved byte			*/
	u_char		:8;	/* Reserved byte			*/
	u_char	control;	/* Control				*/
}ALL_COMPARE_CDB10;


/*
 * Opcode define for compare
 */
#define ALL_COMPARE10_OP	0X39	/* The opcode			*/


/* ---------------------------------------------------------------------- */

/* 
 *  The COPY command defines
 */


/*
 * COPY CDB 6 byte
 */

typedef struct all_copy_cdb {
	u_char	opcode;		/* OPcode = 0X18			*/
	u_char	pad	:1,	/* Padding				*/
	    		:4,	/* 4 bits reservered			*/
		lun	:3;	/* Logical unit number			*/
	u_char	param_len2;	/* Parameter length (MSB).		*/
	u_char	param_len1;	/* Parameter length (MID).		*/
	u_char	param_len0;	/* Parameter length (LSB).		*/
	u_char	control;	/* Control				*/
}ALL_COPY_CDB;


/*
 * Opcode define for compare
 */
#define ALL_COPY_OP		0X18	/* The opcode			*/


/* ---------------------------------------------------------------------- */

/* 
 *  The COPY AND VERIFY command defines
 */


/*
 * COPY AND VERIFY CDB 10 byte
 */

typedef struct all_copy_and_verify_cdb10 {
	u_char	opcode;		/* OPcode = 0X3a			*/
	u_char	pad	:1,	/* Padding				*/
	    	bytchk	:1,	/* Byte check bit			*/
	    		:3,	/* 3 bits reservered			*/
		lun	:3;	/* Logical unit number			*/
	u_char	param_len2;	/* Parameter length (MSB).		*/
	u_char	param_len1;	/* Parameter length (MID).		*/
	u_char	param_len0;	/* Parameter length (LSB).		*/
	u_char		:8;	/* Reserved byte			*/
	u_char		:8;	/* Reserved byte			*/
	u_char		:8;	/* Reserved byte			*/
	u_char	control;	/* Control				*/
}ALL_COPY_AND_VERIFY_CDB10;


/*
 * Opcode define for compare
 */
#define ALL_COPY_AND_VERIFY10_OP	0X3a	/* The opcode		*/


/* ---------------------------------------------------------------------- */


/* 
 *  The INQUIRY command defines
 */


/*
 * INQUIRY CDB 6 byte
 */

typedef struct all_inq_cdb {
	u_char	opcode;		/* OPcode = 0X12			*/
	u_char	evpd	:1,	/* Enable vital product data bit	*/
		cmddt	:1,	/* Command support data			*/
			:3,	/* 3 bits resevered			*/
		lun	:3;	/* Logical unit number			*/
	u_char	page;		/* Page code				*/
	u_char		:8;	/* Byte reserved			*/
	u_char  alloc_len;	/* Allocation length			*/
	u_char	control;	/* Control byte				*/
}ALL_INQ_CDB;


/*
 * Opcode define for inquiry
 */
#define ALL_INQ_OP	0X12	/* The opcode				*/



/* 
 * Standard inquiry data format 
 */

typedef struct all_inq_data {
	u_char	dtype	: 5,	/* Peripheral device type.	[0] */
		pqual	: 3;	/* Peripheral qualifier.	    */
	u_char	dmodify	: 7,	/* Device type modifier.	[1] */
		rmb	: 1;	/* Removable media.		    */
	u_char	ansi	: 3,	/* ANSI version.		[2] */
		ecma	: 3,	/* ECMA version.		    */
		iso	: 2;	/* ISO version.			    */
	u_char	rdf	: 4,	/* Response data format.	[3] */
			: 1,	/* Reserved.			    */
		normaca	: 1,	/* Normal ACA supported		    */
		trmiop	: 1,	/* Terminate I/O process	    */
		aenc	: 1;	/* Async Notification of events	    */
	u_char	addlen;		/* Additional length.		[4] */
	u_char		: 8;	/* Reserved.			[5] */
	u_char	addr16	: 1,	/* support of 16 bit addresses	[6] */
		addr32	: 1,	/* support of 32 bit addresses	    */
		ackreqq	: 1,	/* Q cable req/ack supported	    */
		mchngr	: 1,	/* Media changer attached	    */
		multip	: 1,	/* Multi-ported device		    */
		vendspc	: 1,	/* Vendor specific		    */
		encserv	: 1,	/* Enclosure Services present	    */
			: 1;	/* Reserved.			    */
	u_char	sftre	: 1,	/* Soft reset 1 = yes		[7] */
		cmdque	: 1,	/* Command queuing		    */
		trandis	: 1,	/* Transfer disable supported	    */
		linked	: 1,	/* Linked command support	    */
		sync	: 1,	/* Synchronous data transfers	    */
		wbus16	: 1, 	/* support of 16 bit data transfers */
		wbus32	: 1,	/* support of 32 bit data transfers */
		reladdr : 1;	/* Relative addressing support	    */
	u_char	vid[8];		/* Vendor ID.		     [8-15] */
	u_char	pid[16];	/* Product ID.		    [16-31] */
	u_char	revlevel[4];	/* Revision level.	    [32-35] */
}ALL_INQ_DATA;

#define ALL_INQ_ALL_PAGES	0x00	/* Supported vital product data	*/
#define ALL_INQ_SERIAL_PAGE	0x80	/* Unit serial number page.	*/
#define ALL_INQ_IMPOPR_PAGE	0x81	/* Implemented opr defs page.	*/
#define ALL_INQ_ASCOPR_PAGE	0x82	/* ASCII operating defs page.	*/
#define ALL_INQ_DEVICE_PAGE	0x83	/* Device Identification page.	*/

typedef struct all_inq_vpd_data {
	u_char  dtype	: 5,	/* Peripheral device type.	[0] */
		pqual	: 3;	/* Peripheral qualifier.	    */
	u_char  p_code;		/* Page code			[1] */
	u_char  reserved;	/* Reserved			[2] */
	u_char  p_length;	/* Page length			[3] */
	u_char  p_data[255-4];	/* VPD data fields	    [4-255] */
}ALL_INQ_VPD_DATA;




/* 
 * Defines for what comes back from the inquiry command.
 */

typedef struct all_inq_vpd_hd {
	u_char	dtype	: 5,	/* Peripheral device type.	[0] */
		pqual	: 3;	/* Peripheral qualifier.	    */
	u_char	p_code;		/* Page code			[1] */
	u_char	reserved;	/* Reserved			[2] */
	u_char	p_length;	/* Page length			[3] */
				/* data follows			    */
}ALL_INQ_VPD_HD;

typedef struct all_inq_vpd_ascii_hd {
	u_char	dtype	: 5,	/* Peripheral device type.	[0] */
		pqual	: 3;	/* Peripheral qualifier.	    */
	u_char	p_code;		/* Page code			[1] */
	u_char	reserved;	/* Reserved			[2] */
	u_char	p_length;	/* Page length			[3] */
	u_char	a_length;	/* Ascii length			[4] */
				/* data follows			    */
}ALL_INQ_VPD_ASCII_HD;

typedef	struct all_inq_cmddt_hd {
	u_char	dtype	: 5,	/* Peripheral device type.	[0] */
		pqual	: 3;	/* Peripheral qualifier.	    */
	u_char	support	: 3,	/* Support values		[1] */
			: 5;	/* Reserved			    */
	u_char	ansi	: 3,	/* ANSI version.		[2] */
		ecma	: 3,	/* ECMA version.		    */
		iso	: 2;	/* ISO version.			    */
	u_char		: 8;	/* Reserved.			[3] */
	u_char		: 8;	/* Reserved.			[4] */
	u_char	cdb_size;	/* size of CDB.			[5] */
				/* data follows			    */
}ALL_INQ_CMDDT_HD;

typedef struct all_ident_descriptor_hd {
	u_char	code_set :4,	/* code set			[0] */
			:4;	/* reserved			    */
	u_char	ident	:4,	/* identifier type		[1] */
			:4;	/* reserved			    */
	u_char		:8;	/* reserved			[2] */
	u_char	ident_length;	/* length of identifier		[3] */
				/* data follows			    */
}ALL_IDENT_DESCRIPTOR_HD;

/*
 * Support values
 */
#define ALL_CMDDT_NOT_AVAIL	0x0	/* cmddt data not available	*/
#define ALL_CMDDT_NOT_SUPP	0x1	/* command not supported	*/
#define ALL_CMDDT_SUPP_STD	0x3	/* command supported as per std	*/
#define ALL_CMDDT_SUPP_VU	0x5	/* supported but vendor unique	*/

/*
 * code set values
 */
#define	ALL_IDENT_IS_BINARY	0x1	/* the ident is binary data	*/
#define ALL_IDENT_IS_ASCII	0x2	/* the ident is acsii data	*/

/*
 * identifier type
 */
#define	ALL_IDENT_VS		0x0	/* ident is vendor specific	*/
#define	ALL_IDENT_V_UNIQUE	0x1	/* ident is VID+vendor unique	*/
#define	ALL_IDENT_IEEE		0x2	/* ident is EUI-64 compliant	*/
#define ALL_IDENT_FCPH		0x3	/* ident is FC-PH-64 compliant	*/


/*
 * Defined Peripheral Quailifiers: ALL_INQ_DATA.pqual field
 */
	/* Device is connected.					*/
#define ALL_PQUAL_CONN				0x0	

	/* Device is NOT connected			.	*/
#define ALL_PQUAL_NOT_CONN			0x1	

	/* No physical device support.				*/
#define ALL_PQUAL_NO_PHYS			0x3	

	/* Vendor specific peripheral.				*/
#define ALL_PQUAL_VENDOR_SPEC			0x4	


/*
 * Defined Device Types: ALL_INQ_DATA.dtype field
 */
#define	ALL_DTYPE_DIRECT	0x00	/* Direct access.		*/
#define	ALL_DTYPE_SEQUENTIAL	0x01	/* Sequential access.		*/
#define	ALL_DTYPE_PRINTER	0x02	/* Printer.			*/
#define	ALL_DTYPE_PROCESSOR	0x03	/* Processor.			*/
#define	ALL_DTYPE_WORM		0x04	/* Write-Once/Read Many.	*/
#define	ALL_DTYPE_RODIRECT	0x05	/* Read-Only direct access.	*/
#define	ALL_DTYPE_SCANNER	0x06	/* Scanner.			*/
#define	ALL_DTYPE_OPTICAL	0x07	/* Optical.			*/
#define	ALL_DTYPE_CHANGER	0x08	/* Changer.			*/
#define ALL_DTYPE_COMM		0x09	/* Communications Device	*/
#define ALL_DTYPE_PREPRESS_0	0x0A	/* Graphics pre-press device.	*/
#define ALL_DTYPE_PREPRESS_1	0x0B	/* Graphics pre-press device.	*/
#define ALL_DTYPE_RAID		0x0C	/* Array controller device.	*/
#define ALL_DTYPE_ENCSERV	0x0D	/* Enclosure Service device.	*/
#define	ALL_DTYPE_NONE		0x1F	/* Device type is NONE(unknown) */

/* 
 * The ANSI-Approved version field.
 */
#define ALL_LEVEL_0		0x0
#define ALL_SCSI1		0x1
#define ALL_SCSI2		0x2
#define ALL_SCSI3		0x3

/* 
 * The removabled media bit ALL_INQ_DATA.rmb field
 */
#define ALL_RMB			0x1	/* Is the device/media removable */


/*
 * Defined Response Data Formats: ALL_INQ_DATA.rdf field
 */
#define	ALL_RDF_SCSI1		0x00
#define	ALL_RDF_CCS		0x01
#define	ALL_RDF_SCSI2		0x02

	/* Support of TERMINATE of I/O process ALL_INQ_DATA.trmiop	*/
#define ALL_TERMIOP		0x1	

	/* support of async event notification	ALL_INQ_DATA.aenc	*/
#define ALL_ASYNC_NOTICE		0x1


/*
 * The following bit defines tell us what features the unit offers
 * like synchronous data transfers, 32 bit data transfers, and the 
 * in-law bit where if the bit is on their address is YOURS
 */

	/* Soft reset or hard			SIP only	*/
#define ALL_SOFTRESET		0x1

	/* Command queuing		*/
#define ALL_CMD_QUE		0x1

	/* Linked Commands		*/
#define ALL_LINKED		0x1	

	/* Synchronous data transfers		SIP only	*/
#define ALL_SYNC		0x1

	/* 16 bit data transfers		SIP only	*/
#define ALL_WBUS16		0x1

	/* 32 bit transfers			SIP only	*/
#define ALL_WBUS32		0x1

	/* Relative Addressing		*/
#define ALL_RELATIVE_ADDR	0x1

	/* Normal ACA			*/
#define	ALL_NORMAL_ACA		0x1

	/* 16 bit wide SCSI addresses		SIP only	*/
#define	ALL_WADDR16		0x1

	/* 32 bit wide SCSI addresses		SIP only	*/
#define ALL_WADDR32		0x1

	/* req and ack on Q cable		SIP only	*/
#define	ALL_ACKQREQQ		0x1

	/* Media changer attached	*/
#define	ALL_MEDIA_CHANGER	0x1

	/* Multi Ported Device		*/
#define	ALL_MULTI_PORTED	0x1

	/* Transfer Disable supported	*/
#define	ALL_TRANSFER_DISABLE	0x1

	/* Command support data valid	*/
#define	ALL_CMDDT_VALID		0x1

	/* Supported as per standard	*/
#define	ALL_STANDARD_OP		0x1

	/* Supported as vendor unique	*/
#define	ALL_VENDOR_UNIQUE_OP	0x1





/* ---------------------------------------------------------------------- */

/*
 * Mode select/sense defines
 */


/*
 * The mode select CDB 6 bytes.
 */
typedef struct all_mode_sel_cdb6 {
	u_char	opcode;		/* 15 hex 				*/
	u_char	sp	: 1,	/* Save parameters			*/
			: 3, 	/* 3 bits reserved			*/
		pf	: 1,	/* Page format-true conforms to scsi 2	*/
		lun	: 3;	/* logical unit number			*/
	u_char		: 8;	/* Reserved byte			*/
	u_char		: 8;	/* Reserved byte			*/
	u_char	param_len;	/* parameter list length		*/
	u_char	control;	/* The control byte			*/
}ALL_MODE_SEL_CDB6;

/* 
 * The 6 byte mode select op code
 */
#define ALL_MODE_SEL6_OP	0x15


/*
 * The mode select CDB 10 bytes.
 */

typedef struct all_mode_sel_cdb10 {
	u_char	opcode;		/* 55 hex 				*/
	u_char	sp	: 1,	/* Save parameters			*/
			: 3, 	/* 3 bits resevred			*/
		pf	: 1,	/* Page format-true conforms to scsi 2	*/
		lun	: 3;	/* logical unit number			*/
	u_char		: 8;	/* Reserved byte			*/
	u_char		: 8;	/* Reserved byte			*/
	u_char		: 8;	/* Reserved byte			*/
	u_char		: 8;	/* Reserved byte			*/
	u_char		: 8;	/* Reserved byte			*/
	u_char	param_len1;	/* MSB parameter list length		*/
	u_char	param_len0;	/* LSB parameter list length		*/
	u_char	control;	/* The control byte			*/
}ALL_MODE_SEL_CDB10;

/* 
 * The 10 byte mode select op code
 */
#define ALL_MODE_SEL10_OP	0x55

/*
 * The mode sense CDB 6 bytes.
 */

typedef struct all_mode_sense_cdb6 {
	u_char	opcode;		/* 1a hex 			[0]	*/
	u_char		: 3,	/* 3 bits reserved		[1]	*/
		dbd	: 1, 	/* Disable block descriptors		*/
			: 1,	/* 1 bit reserved			*/
		lun	: 3;	/* logical unit number			*/
	u_char	page_code : 6,	/* page you want to retrieve	[2]	*/
		pc	: 2;	/* page control field			*/
	u_char		: 8;	/* Reserved byte		[3]	*/
	u_char	alloc_len;	/* Allocation length		[4]	*/
	u_char	control;	/* The control byte		[5]	*/
}ALL_MODE_SENSE_CDB6;

/* 
 * The 6 byte mode sense op code
 */
#define ALL_MODE_SENSE6_OP	0x1A

/*
 * The mode sense CDB 10 bytes.
 */

typedef struct all_mode_sense_cdb10 {
	u_char	opcode;		/* 5a hex 			[0]	*/
	u_char		: 3,	/* 3 bits reserved		[1]	*/
		dbd	: 1, 	/* Disable block descriptors		*/
			: 1,	/* 1 bit reserved			*/
		lun	: 3;	/* logical unit number			*/
	u_char	page_code : 6,	/* page you want to retrieve	[2]	*/
		pc	: 2;	/* page control field			*/
	u_char		: 8;	/* Reserved byte		[3]	*/
	u_char		: 8;	/* Reserved byte		[4]	*/
	u_char		: 8;	/* Reserved byte		[5]	*/
	u_char		: 8;	/* Reserved byte		[6]	*/
	u_char	alloc_len1;	/* MSB Allocation length	[7]	*/
	u_char	alloc_len0;	/* LSB Allocation length	[8]	*/
	u_char	control;	/* The control byte		[9]	*/
}ALL_MODE_SENSE_CDB10;

/* 
 * The 10 byte mode sense op code
 */
#define ALL_MODE_SENSE10_OP	0x5A



/* 
 * Values for Page Control field. (mode pages PCFM)
 */
#define ALL_PCFM_CURRENT	0x0	/* Return current mode select parms */
#define ALL_PCFM_CHANGEABLE	0x1	/*   ""  changeable ""   ""    "" */
#define ALL_PCFM_DEFAULT	0x2	/*   ""   default   ""   ""    "" */
#define ALL_PCFM_SAVED		0x3	/*   ""   saved     ""   ""    "" */




/* ---------------------------------------------------------------------- */

/*
 * PERSISTENT RESERVE IN/OUT Commands
 */
typedef struct all_prin_cdb {
	u_char	opcode;			/* 5e hex Operation code	[0] */
	u_char	action	:5,		/* Action			[1] */
			:3;		/* Reserved			    */
	u_char		:8;		/* Reserved			[2] */
	u_char		:8;		/* Reserved			[3] */
	u_char		:8;		/* Reserved			[4] */
	u_char		:8;		/* Reserved			[5] */
	u_char		:8;		/* Reserved			[6] */
	u_char	alloc_len1;		/* Allocation length (MSB).	[7] */
	u_char	alloc_len0;		/* Allocation length (LSB).	[8] */
	u_char	control;		/* Control byte.		[9] */
}ALL_PRIN_CDB;

#define ALL_PRIN_OP			0x5e

/*
 * PRIN action codes
 */
#define ALL_PRIN_READ_KEYS		0x0	/* Read registered keys	*/
#define	ALL_PRIN_READ_RESERVATIONS	0x1	/* Read current reservations */

typedef	struct all_prin_header {
	u_char	generation3;		/* MSB of generation number	[0] */
	u_char	generation2;		/* MID of generation number	[1] */
	u_char	generation1;		/* MID of generation number	[2] */
	u_char	generation0;		/* LSB of generation number	[3] */
	u_char	add_length3;		/* MSB of additional length	[4] */
	u_char	add_length2;		/* MID of additional length	[5] */
	u_char	add_length1;		/* MID of additional length	[6] */
	u_char	add_length0;		/* LSB of additional length	[7] */
}ALL_PRIN_HEADER;


typedef struct all_prinout_key {
	u_char	key7;			/* MSB of reservation key value	[0] */
	u_char	key6;			/*				[1] */
	u_char	key5;			/*				[2] */
	u_char	key4;			/*				[3] */
	u_char	key3;			/*				[4] */
	u_char	key2;			/*				[5] */
	u_char	key1;			/*				[6] */
	u_char	key0;			/* LSB of reservation key value	[7] */
}ALL_PRINOUT_KEY;

/*
 * Macro to get key_count (PRIN READ KEYS)
 * Takes address of add_length3 and a variable
 */
#define ALL_GET_KEY_CNT(addlen_ptr, key_count)                    \
{                                                                 \
    u_char *tmp_ptr = (u_char *)(addlen_ptr);                     \
    key_count |= ((u_int)(*tmp_ptr)) << 24;                       \
    ++tmp_ptr;                                                    \
    key_count |= ((u_int)(*tmp_ptr)) << 16;                       \
    ++tmp_ptr;                                                    \
    key_count |= ((u_int)(*tmp_ptr)) << 8;                        \
    ++tmp_ptr;                                                    \
    key_count |= (u_int)(*tmp_ptr);                               \
    if((key_count) != 0){                                          \
        (key_count) = (key_count)/sizeof(ALL_PRINOUT_KEY);        \
    }                                                             \
}

/*
 * Macro to convert ulong Big endian key to little endian key
 * Key gotten from the device.
 */
#define ALL_CONVERT_KEY_TO_LITTLE( big, little )                  \
{                                                                 \
    u_char *temp_ptr = (u_char *)big;                             \
    (*little)  = (u_long )((*temp_ptr) & 0xff) << 56;             \
    ++temp_ptr;                                                   \
    (*little)  |= (u_long )((*temp_ptr) & 0xff) << 48;            \
    ++temp_ptr;                                                   \
    (*little)  |= (u_long )((*temp_ptr) & 0xff) << 40;            \
    ++temp_ptr;                                                   \
    (*little)  |= (u_long )((*temp_ptr) & 0xff) << 32;            \
    ++temp_ptr;                                                   \
    (*little)  |= (u_long )((*temp_ptr) & 0xff) << 24;            \
    ++temp_ptr;                                                   \
    (*little)  |= (u_long )((*temp_ptr) & 0xff) << 16;            \
    ++temp_ptr;                                                   \
    (*little)  |= (u_long )((*temp_ptr) & 0xff) << 8;             \
    ++temp_ptr;                                                   \
    (*little)  |= (u_long )(*temp_ptr) & 0xff;                    \
}

typedef	struct	all_prin_descriptor {
	ALL_PRINOUT_KEY	key;		/* 8 byte key value	      [0-7] */
	u_char	address3;		/* MSB of first block of	[8] */
	u_char	address2;		/*	  extent, or		[9] */
	u_char	address1;		/*	  element address	[10] */
	u_char	address0;		/* LSB of ...			[11] */
	u_char		:8;		/* Reserved			[12] */
	u_char	type	:4,		/* Type				[13] */
		scope	:4;		/* Scope			     */
	u_char	extent_len1;		/* Extent length (MSB).		[14] */
	u_char	extent_len0;		/* Extent length (LSB).		[15] */
}ALL_PRIN_DESCRIPTOR;


typedef struct all_prout_cdb {
	u_char	opcode;			/* 5f hex Operation code	[0] */
	u_char	action	:5,		/* Action			[1] */
			:3;		/* Reserved			    */
	u_char	type	:4,		/* Type				[2] */
		scope	:4;		/* Scope			    */
	u_char		:8;		/* Reserved			[3] */
	u_char		:8;		/* Reserved			[4] */
	u_char		:8;		/* Reserved			[5] */
	u_char		:8;		/* Reserved			[6] */
	u_char	param_len1;		/* Parameter list length (MSB).	[7] */
	u_char	param_len0;		/* Parameter list length (LSB).	[8] */
	u_char	control;		/* Control byte.		[9] */
}ALL_PROUT_CDB;

#define ALL_PROUT_OP			0x5f

/*
 * PROUT action codes
 */
#define ALL_PROUT_REGISTER	0x0	/* Register a key		   */
#define ALL_PROUT_RESERVE	0x1	/* Create a reservation		   */
#define ALL_PROUT_RELEASE	0x2	/* Release a reservation	   */
#define ALL_PROUT_CLEAR		0x3	/* Clear all keys & reserves	   */
#define ALL_PROUT_PREEMPT	0x4	/* Take another initiators reserve */
#define ALL_PROUT_PREEMPT_CLR	0x5	/* PREEMPT and clear their stuff   */
#define ALL_PROUT_REGISTER_IGNORE 0x6 /* Register and Ignore existing 
                                         key */

/*
 * PROUT type codes
 */
#define ALL_PROUT_READ_SHARED	0x0	/* share read, no writers	   */
#define ALL_PROUT_WRITE_EXC	0x1	/* share read, me only writer	   */
#define ALL_PROUT_READ_EXC	0x2	/* me only read, share write	   */
#define ALL_PROUT_BOTH_EXC	0x3	/* me only read, me only write	   */
#define ALL_PROUT_BOTH_SHARED	0x4	/* share read, share write	   */
#define ALL_PROUT_WRITE_EXC_RO	0x5	/* share read, exc write reg only  */
#define ALL_PROUT_BOTH_EXC_RO	0x6	/* both exclusive registered only  */

/*
 * PROUT scope codes
 */
#define ALL_PROUT_LU		0x0	/* Applies to full logical unit	    */
#define ALL_PROUT_EXTENT	0x1	/* Applies to specified extent	    */
#define ALL_PROUT_ELEMENT	0x2	/* Applies to specified element	    */

typedef	struct	all_prout_parameters {
	ALL_PRINOUT_KEY	cmd;		/* 8 byte key value	      [0-7] */
	ALL_PRINOUT_KEY	change;		/* 8 byte key value	     [8-15] */
	u_char	address3;		/* MSB of first block of	[16] */
	u_char	address2;		/*	  extent, or		[17] */
	u_char	address1;		/*	  element address	[18] */
	u_char	address0;		/* LSB of ...			[19] */
	u_char	aptpl	:1,		/* Persist through power loss	[20] */
			:7;		/* Reserved			     */
	u_char		:8;		/* Reserved			[21] */
	u_char	extent_len1;		/* Extent length (MSB).		[22] */
	u_char	extent_len0;		/* Extent length (LSB).		[23] */
}ALL_PROUT_PARAMETERS;


/*
 * Macro to convert ulong little endian key to big endian key
 * Key going to device
 */
#define ALL_CONVERT_KEY_TO_BIG( little, big)                      \
{                                                                 \
    u_char *temp_ptr = (u_char *)little;                          \
    (*big)  = (u_long )((*temp_ptr) & 0xff) << 56;                \
    ++temp_ptr;                                                   \
    (*big)  |= (u_long )((*temp_ptr) & 0xff) << 48;               \
    ++temp_ptr;                                                   \
    (*big)  |= (u_long )((*temp_ptr) & 0xff) << 40;               \
    ++temp_ptr;                                                   \
    (*big)  |= (u_long )((*temp_ptr) & 0xff) << 32;               \
    ++temp_ptr;                                                   \
    (*big)  |= (u_long )((*temp_ptr) & 0xff) << 24;               \
    ++temp_ptr;                                                   \
    (*big)  |= (u_long )((*temp_ptr) & 0xff) << 16;               \
    ++temp_ptr;                                                   \
    (*big)  |= (u_long )((*temp_ptr) & 0xff) << 8;                \
    ++temp_ptr;                                                   \
    (*big)  |= (u_long )(*temp_ptr) & 0xff;                       \
}
    



/* ---------------------------------------------------------------------- */

/*
 * PREVENT ALLOW MEDIUM REMOVAL Command
 */
typedef struct all_prevent_allow_cdb {
	u_char	opcode;			/* 1e hex Operation code	[0] */
	u_char		:8;		/* Reserved.			[1] */
	u_char		:8;		/* Reserved.			[2] */
	u_char		:8;		/* Reserved.			[3] */
	u_char	prevent	:1,		/* Prevent transport bit.	[4] */
		mchngr	:1,		/* Prevent changer bit.		    */
			:6;		/* Reserved.			    */
	u_char	control;		/* Control byte.		[5] */
}ALL_PREVENT_ALLOW_CDB;

#define ALL_PREVENT_ALLOW_OP		0x1e

/*
 * Allow/Prevent Medium Removal Parameters:
 *	This may apply to the data transport or to the medium changer
 *	(if the mchngr bit in INQ data is set).
 */
#define ALL_ALLOW_REMOVAL	0	/* Allow removal		*/
#define ALL_PREVENT_REMOVAL	1	/* Prevent removal		*/




/* ---------------------------------------------------------------------- */

/*
 * RECEIVE DIAGNOSTIC RESULT Command
 */
typedef struct all_receive_diagnostic_cdb {
	u_char	opcode;			/* 1c hex Operation Code.	[0] */
	u_char	pcv	: 1,		/* Page code valid.		[1] */
			: 4,		/* Reserved.			    */
		lun	: 3;		/* Logical Unit Number.		    */
	u_char	page	: 8;		/* Page code.			[2] */
	u_char	alloc_len1;		/* Allocation length (MSB).	[3] */
	u_char	alloc_len0;		/* Allocation length (LSB).	[4] */
	u_char	link	: 1,		/* Link.			[5] */
		flag	: 1,		/* Flag.			    */
		naca	: 1,		/* Normal ACA.			    */
			: 3,		/* Reserved.			    */
		vendor	: 2;		/* Vendor Unique.		    */
} ALL_RECEIVE_DIAGNOSTIC_CDB;

#define ALL_RECEIVE_DIAGNOSTIC_OP	0x1C

typedef struct all_diagnostic_pg_hd {
	u_char	page;			/* Page code.			[0] */
	u_char		: 8;		/* reserved			[1] */
	u_char	len1;			/* MSB of page length		[2] */
	u_char	len0;			/* LSB of page length		[3] */
					/* data goes here		    */
}ALL_DIAGNOSTIC_PG_HD;



/* ---------------------------------------------------------------------- */

/*
 * REPORT LUN OPERATION
 */

typedef struct all_report_luns {
	u_char	opcode;			/* opcode = 0xa0		[0] */
	u_char			:8;     /* reserved			[1] */
	u_char			:8;     /* reserved			[2] */
	u_char			:8;     /* reserved			[3] */
	u_char			:8;     /* reserved			[4] */
	u_char			:8;     /* reserved			[5] */
	u_char	alloc_len3;		/* Allocation list length MSB	[6] */
	u_char	alloc_len2;		/* Allocation list length MID	[7] */
	u_char	alloc_len1;		/* Allocation list length MID	[8] */
	u_char	alloc_len0;		/* Allocation list length LSB	[9] */
	u_char			:8;     /* reserved			[10] */
	u_char	control;		/* Control byte			[11] */
}ALL_REPORT_LUNS;

/*
 * Release 10 opcode
 */
#define ALL_REPORT_LUNS_OP	0xa0


typedef struct all_report_luns_header {
	u_char	list_len3;		/* MSB of lun list length	[0] */
	u_char	list_len2;		/* MID of lun list length	[1] */
	u_char	list_len1;		/* MID of lun list length	[2] */
	u_char	list_len0;		/* LSB of lun list length	[3] */
	u_char			:8;     /* reserved			[4] */
	u_char			:8;     /* reserved			[5] */
	u_char			:8;     /* reserved			[6] */
	u_char			:8;     /* reserved			[7] */
}ALL_REPORT_LUNS_HEADER;

/*
 * See the structure definition for "all_long_id" below for the lun
 * list entries (the 8 byte lun numbers).
 */



/* ---------------------------------------------------------------------- */

/* 
 * REQUEST SENSE structs and defines
 */

/* 
 * Request sense 6 byte cdb
 */


typedef struct all_req_sense_cdb6 {
	u_char	opcode;		/* 0x03 hex 			[0]	*/
	u_char		: 5,	/* 5 bits reserved		[1]	*/
		lun	: 3;	/* logical unit number			*/
	u_char		: 8;	/* Reserved byte		[2]	*/
	u_char		: 8;	/* Reserved byte		[3]	*/
	u_char	alloc_len;	/* Allocation length		[4]	*/
	u_char	control;	/* The control byte		[5]	*/
}ALL_REQ_SENSE_CDB6;

/* 
 * The 6 byte request sense op code
 */
#define ALL_REQ_SENSE6_OP	0x03

/* 
 * The sense key specific structures for request sense data.
 * sense key specific area has certain formats which are defined
 * for sense sense keys or cmds
 */

/* 
 * The sense specific for illegal request
 */
typedef struct all_sks_ill_req {
	u_char	bit_pointer	:3,	/* bit in error of the byte	*/
		bpv		:1, 	/* bit pointer field valid	*/
				:2,	/* 2 bits reserved		*/
		c_or_d		:1,	/* error is in cmd or data	*/
		sksv		:1;	/* sense key specific valid	*/
	u_char	field_ptr1;		/* MSB of field pointer		*/
	u_char	field_ptr0;		/* LSB of field pointer		*/
}ALL_SKS_ILL_REQ;

/* 
 * The sense specific for Recovered, hardware, medium erros
 */
typedef struct all_sks_retry_cnt {
	u_char			:7,	/* 7 bits reserved		*/
		sksv		:1;	/* sense key specific valid	*/
	u_char	retry_cnt1;		/* MSB retry count 		*/
	u_char	retry_cnt0;		/* LSB retry count		*/
}ALL_SKS_RETRY_CNT;

/* 
 * The sense key of NOT READY and formating unit with the immed bit
 */
typedef struct all_sks_prog_cnt {
	u_char			:7,	/* 7 bits reserved		*/
		sksv		:1;	/* sense key specific valid	*/
	u_char	progress1;		/* MSB of progress count 	*/
	u_char	progress0;		/* LSB of progress count	*/
}ALL_SKS_PROG_CNT;

/* 
 * The sense key of NOT READY reporting with Reason Code
 */
typedef struct all_sks_reason_code {
	u_char	reason_code	:4,	/* Reason Code			*/
		nrrv		:1,	/* Not Ready Reason code Valid	*/
				:2,	/* 2 bits reserved	 	*/
		sksv		:1;	/* Sense Key Specific Valid	*/
	u_char	progress1;		/* MSB of progress count 	*/
	u_char	progress0;		/* LSB of progress count	*/
}ALL_SKS_REASON_CODE;

/*
 * HSG/V NOT READY Reason codes
 */
#define REASON_INOPERATIVE	1
#define REASON_UNAVAIL		2
#define REASON_NORMAL		3
#define REASON_BACKOFF		4

/* 
 * The request sense data struct (whats returned to us)
 * NON scatter/gather
 */

#define ADDL_SENSE_LENGTH	(64-18)	/* Additional request sense.	*/

typedef struct all_req_sns_data {
	u_char	error_code	:7,	/* the error code 70h/71h	[0] */
		valid		:1;	/* The valid bit		    */
	u_char	segment;		/* the segment number		[1] */
	u_char	sns_key		:4,	/* sense key			[2] */
				:1,	/* bit reserved			    */
		ili		:1,	/* illegal length indicator	    */
		eom		:1,	/* End of media			    */
		filemark	:1;	/* file mark			    */
	u_char	info_byte3;		/* MSB of information field	[3] */
	u_char	info_byte2;		/* byte 2 of information field	[4] */
	u_char	info_byte1;		/* byte 1 of information field	[5] */
	u_char	info_byte0;		/* LSB of information field	[6] */
	u_char	addition_len;		/* additional sense length	[7] */
	u_char	cmd_specific3;		/* MSB of command specific info	[8] */
	u_char	cmd_specific2;		/* byte 2 of command specific info [9]*/
	u_char	cmd_specific1;		/* byte 3 of command specific info   */
	u_char	cmd_specific0;		/* LSB of command specific info	[11] */
	u_char	asc;			/* additional sense code	[12] */
	u_char	asq;			/* additional sense code qual	[13] */
	u_char	fru;			/* field replacement unit	[14] */
	union	{
		ALL_SKS_ILL_REQ		sks_ill_req;
		ALL_SKS_RETRY_CNT	sks_retry_cnt;
		ALL_SKS_PROG_CNT	sks_prog_cnt;
		}sense_specific;
	union	{
#if defined( KERNEL )
		u_char	auto_sns[DEC_AUTO_SENSE_SIZE];
		/*
		 * ALL_MAX_PAGE_SIZE makes this structure too large
		 * to fit in the allocation length (8-bit) field.  But for
		 * kernel mode, we have to leave it as until we figure out
		 * the ramifications of changing it.
		 */
		/* Make sure the whole thing isn't over 255 for now. */
		u_char	other_sns[ALL_MAX_PAGE_SIZE-(15+3)-1];
#else /* defined( KERNEL ) */
		u_char	auto_sns[ADDL_SENSE_LENGTH];
		u_char	other_sns[ADDL_SENSE_LENGTH];
#endif /* defined( KERNEL ) */
		}additional_sense;
}ALL_REQ_SNS_DATA;

/* 
 * The request sense data struct (whats returned to us)
 * Scatter/gather
 */

typedef struct all_req_sns_data_gather {
	u_char	error_code	:7,	/* the error code 70h/71h	[0] */
		valid		:1;	/* The valid bit		    */
	u_char	segment;		/* the segment number		[1] */
	u_char	sns_key		:4,	/* sense key			[2] */
				:1,	/* bit reserved			    */
		ili		:1,	/* illegal length indicator	    */
		eom		:1,	/* End of media			    */
		filemark	:1;	/* file mark			    */
	u_char	info_byte3;		/* MSB of information field	[3] */
	u_char	info_byte2;		/* byte 2 of information field	[4] */
	u_char	info_byte1;		/* byte 1 of information field	[5] */
	u_char	info_byte0;		/* LSB of information field	[6] */
	u_char	addition_len;		/* additional sense length	[7] */
	u_char	cmd_specific3;		/* MSB of command specific info	[8] */
	u_char	cmd_specific2;		/* byte 2 of command specific info [9]*/
	u_char	cmd_specific1;		/* byte 1 of command specific info   */
	u_char	cmd_specific0;		/* LSB of command specific info	[11] */
	u_char	asc;			/* additional sense code	[12] */
	u_char	asq;			/* additional sense code qual	[13] */
	u_char	fru;			/* field replacement unit	[14] */
	union	{
		ALL_SKS_ILL_REQ		sks_ill_req;
		ALL_SKS_RETRY_CNT	sks_retry_cnt;
		ALL_SKS_PROG_CNT	sks_prog_cnt;
		}sense_specific;
	union	{
		u_char	*auto_sns;
		u_char	*other_sns;
		}additional_sense;
}ALL_REQ_SNS_DATA_GATHER;

/*
 * The error code defines
 */
#define	ALL_IMED_ERR_CODE	0x70	/* Noticed this cmd		*/
#define ALL_DEFER_ERR_CODE	0x71	/* Previous cmd had error (good */
#define ALL_VENDOR_SPECIFIC	0x7f	/* Vendor specific sense data.	*/

/* 
 * The sense keys
 */
#define ALL_NO_SENSE		0x00	/* No sense key info. check eom */
#define ALL_RECOVER_ERR		0x01	/* Recovered error (soft)	*/
#define ALL_NOT_READY		0x02	/* Device not readay		*/
#define ALL_MEDIUM_ERR		0x03	/* Medium error data bad	*/
#define ALL_HARDWARE_ERR	0x04	/* Device had some so of error	*/
#define ALL_ILLEGAL_REQ		0x05	/* Gave the unit bogus cmd/data	*/
#define ALL_UNIT_ATTEN		0x06	/* Unit Attention		*/
#define ALL_DATA_PROTECT	0x07	/* Write protected unit		*/
#define ALL_BLANK_CHECK		0x08	/* Blank media at this point	*/
#define ALL_VENDOR_SPEC		0x09	/* Vendor specific 		*/
#define ALL_COPY_ABORT		0x0a	/* copy,compare,etc had error	*/
#define ALL_ABORTED_CMD		0x0b	/* Target aborted cmd		*/
#define ALL_EQUAL		0x0c	/* search has found match	*/
#define ALL_VOL_OVERFLOW	0x0d	/* Volume overflow		*/
#define ALL_MISCOMPARE		0x0e	/* source didn't match media	*/




/* 
 * The additional sense codes and qualifiers are defined at the
 * end of this module.
 */




/* ---------------------------------------------------------------------- */

/*
 * RESERVE and RELEASE commands
 */

/*
 * Reserve cdb 6 bytes
 */
typedef struct all_reserve_cdb6 {
	u_char	opcode;			/* 0x16				[0] */
	u_char	extent		:1,	/* Extended release (optional)	[1] */
		third_dev_id	:3,	/* Third party dev id		    */
		third_pat	:1,	/* Third party bit		    */
		lun		:3;	/* Logical unit number		    */
	u_char	resrv_id;		/* reservation ID		[2] */
	u_char	extent_len1;		/* MSB of Extented list length	[3] */
	u_char	extent_len0;		/* LSB of Extented list length	[4] */
	u_char	control;		/* Control byte			[5] */
}ALL_RESERVE_CDB6;

/*
 * Reserve 6 opcode
 */
#define ALL_RESERVE6_OP		0x16


/*
 * Reserve cdb 10 bytes
 */
typedef struct all_reserve_cdb10 {
	u_char	opcode;			/* 0x56				[0] */
	u_char	extent		:1,	/* Extended release (optional)	[1] */
		long_id		:1,	/* Long id ( over 255 )		    */
				:2,	/* reserved			    */
		third_pat	:1,	/* Third party bit		    */
				:3;	/* reserved			    */
	u_char	resrv_id;		/* reservation ID		[2] */
	u_char	third_pat_id;		/* third party ID (upto 255)	[3] */
	u_char			:8;     /* reserved			[4] */
	u_char			:8;     /* reserved			[5] */
	u_char			:8;     /* reserved			[6] */
	u_char	param_len1;		/* MSB of parameter list length	[7] */
	u_char	param_len0;		/* LSB of parameter list length	[8] */
	u_char	control;		/* Control byte			[9] */
}ALL_RESERVE_CDB10;

/*
 * Reserve 10 opcode
 */
#define ALL_RESERVE10_OP	0x56

/*
 * The Extended list (format of)
 */
typedef struct all_extend_format {
	u_char	resrv_type	:2,	/* reservation type		*/
		reladr		:1,	/* Relative address bit		*/
				:5;	/* 5 bits reserved		*/
	u_char	num_blocks2;		/* MSB of number of blocks	*/
	u_char	num_blocks1;		/* MID of number of blocks	*/
	u_char	num_blocks0;		/* LOW of number of blocks	*/
	u_char	lbn3;			/* MSB of logical block address */
	u_char	lbn2;			/* MID HIGH of logical block addr*/
	u_char	lbn1;			/* MID LOW of logical block addr*/
	u_char	lbn0;			/* LSB of logical block addr	*/
}ALL_EXTEND_FORMAT;

/*
 * Defines for reservation type PLEASE NOTE OCTAL
 */
#define ALL_RESRV_RD_SHARE      00
#define ALL_RESRV_WRT_EXCLUS    01
#define ALL_RESRV_RD_EXCLUS     02
#define ALL_RESRV_EXCLUS        03


/*
 * Release cdb 6 bytes
 */
typedef struct all_release_cdb6 {
	u_char	opcode;			/* 0x17				[0] */
	u_char	extent		:1,	/* Extended release (optional)	[1] */
		third_dev_id	:3,	/* Third party dev id		    */
		third_pat	:1,	/* Third party bit		    */
		lun		:3;	/* Logical unit number		    */
	u_char  resrv_id;		/* reservation ID		[2] */
	u_char			:8;	/* reserved			[3] */
	u_char			:8;	/* reserved			[4] */
	u_char	control;		/* Control byte			[5] */
}ALL_RELEASE_CDB6;

/*
 * Release 6 opcode
 */
#define ALL_RELEASE6_OP		0x17


/*
 * Release cdb 10 bytes
 */
typedef struct all_release_cdb10 {
	u_char	opcode;			/* 0x57				[0] */
	u_char	extent		:1,	/* Extended release (optional)	[1] */
		long_id		:1,	/* Long id ( over 255 )		    */
				:2,	/* reserved			    */
		third_pat	:1,	/* Third party bit		    */
				:3;	/* reserved			    */
	u_char  resrv_id;		/* reservation ID		[2] */
	u_char	third_pat_id;		/* third party ID (upto 255)	[3] */
	u_char			:8;     /* reserved			[4] */
	u_char			:8;	/* reserved			[5] */
	u_char			:8;	/* reserved			[6] */
	u_char	param_len1;		/* MSB of parameter list length	[7] */
	u_char	param_len0;		/* LSB of parameter list length	[8] */
	u_char	control;		/* Control byte			[9] */
}ALL_RELEASE_CDB10;

/*
 * Release 10 opcode
 */
#define ALL_RELEASE10_OP	0x57

typedef struct all_long_id {
	u_char	long_id7;		/* MSB of the			[0] */
	u_char	long_id6;		/*    full 8 byte		[1] */
	u_char	long_id5;		/*	id value.		[2] */
	u_char	long_id4;		/*				[3] */
	u_char	long_id3;		/*				[4] */
	u_char	long_id2;		/*				[5] */
	u_char	long_id1;		/*				[6] */
	u_char	long_id0;		/* LSB of the value		[7] */
}ALL_LONG_ID;





/* ---------------------------------------------------------------------- */

/*
 * LOG SELECT and SENSE
 */

/* 
 * LOG select command cdb 10 bytes
 */
typedef struct all_log_sel_cdb10 {
	u_char	opcode;			/* 0x4c				*/
	u_char	sp		:1,	/* Save parameters		*/
		pcr		:1,	/* Parameter code reset		*/
				:3,	/* 3 bits reserved		*/
		lun		:3;	/* Logical unit number		*/
	u_char			:6,	/* 6 bits reserved		*/
		pc		:2;	/* Page control field		*/
	u_char			:8;	/* Reserved			*/
	u_char			:8;	/* Reserved			*/
	u_char			:8;	/* Reserved			*/
	u_char			:8;	/* Reserved			*/
	u_char	param_len1;		/* MSB Parameter list length	*/
	u_char	param_len0;		/* LSB Parameter list length	*/
	u_char	control;		/* Control byte			*/
}ALL_LOG_SEL_CDB10;

/* 
 * LOG select opcode define
 */
#define ALL_LOG_SEL_OP		0x4c


/*
 * Page control field defines for LOG command (PCFL) in octal.
 */
#define ALL_PCFL_CURR_THRES	00	/* Current threshold values	*/
#define ALL_PCFL_CURR_CUMU	01	/* Current cumulative values	*/
#define ALL_PCFL_DEF_THRES	02	/* Default threshold values	*/
#define ALL_PCFL_DEF_CUMU	03	/* Default cumulative values	*/


/* 
 * LOG sense command cdb 10 bytes
 */
typedef struct all_log_sns_cdb10 {
	u_char	opcode;			/* 0x4d				*/
	u_char	sp		:1,	/* Save parameters		*/
		ppc		:1,	/* Parameter pointer control	*/
				:3,	/* 3 bits reserved		*/
		lun		:3;	/* Logical unit number		*/
	u_char	pg_code		:6,	/* Page code			*/
		pc		:2;	/* Page control field		*/
	u_char			:8;	/* Reserved			*/
	u_char			:8;	/* Reserved			*/
	u_char	param_ptr1;		/* MSB Parameter pointer	*/
	u_char	param_ptr0;		/* LSB Parameter pointer	*/
	u_char	alloc_len1;		/* MSB Allocation length	*/
	u_char	alloc_len0;		/* LSB Allocation length	*/
	u_char	control;		/* Control byte			*/
}ALL_LOG_SNS_CDB10;


/* 
 * LOG sense opcode define
 */
#define ALL_LOG_SNS_OP		0x4d




/* ---------------------------------------------------------------------- */

/* 
 * LOG parameter pages
 */

/*
 * Log page header
 */
typedef struct all_log_pg_hd {
	u_char	page_code	:6,	/* The page code		*/
				:2;	/* 2 bits reserved		*/
	u_char			:8;	/* Reserved			*/
	u_char	page_len1;		/* MSB of page length		*/
	u_char	page_len0;		/* LSB of page length		*/
}ALL_LOG_PG_HD;

/* 
 * LOG parameter format  NON scatter gather
 */
typedef struct all_log_fmt {
	u_char	param_code1;		/* MSB of parameter code	*/
	u_char	param_code0;		/* LSB of parameter code	*/
	u_char	lp		:1,	/* List parameters		*/
		lbin		:1,	/* list contains binary		*/
		tmc		:2,	/* Threshold met criteria	*/
		etc		:1,	/* Enable threshold criteria	*/
		tsd		:1,	/* Target save disable		*/
		ds		:1,	/* Disable save			*/
		du		:1;	/* Disable update		*/
	u_char	param_len;		/* Parameter length 		*/
	u_char	param_data[ALL_MAX_PAGE_SIZE - 4];
}ALL_LOG_FMT;


/* 
 * LOG PARAMETER PAGE  SCATTER/GATHER
 */
typedef struct all_log_param_pg_gather {
	ALL_LOG_PG_HD	pg_head;	/* Page header			*/
	ALL_LOG_FMT	**log_param;	/* list of pointer to parameters*/
}ALL_LOG_PARAM_PG_GATHER;



/* 
 * LOG PAGE CODE DEFINES 
 */
#define ALL_PGL_SUPPT		0x00	/* Supported Log pages		*/
#define ALL_PGL_RUNS		0x01	/* Over/under runs		*/
#define ALL_PGL_WRT		0x02	/* Error counters write		*/
#define ALL_PGL_READ		0x03	/* Error counters read		*/
#define ALL_PGL_READ_REV	0x04	/* Error counters read reverse	*/
#define ALL_PGL_VERIFY		0x05	/* Error counters verify	*/
#define ALL_PGL_MEDIUM		0x06	/* NON medium errors		*/
#define ALL_PGL_LASTN		0x07	/* Last n errors		*/
#define ALL_PGL_LASTN_DEF	0x0b	/* Last n deferred errors	*/

/* 
 *  Buffer over-run/under run counters page code 0x01
 */
typedef struct all_log_run_pg {
	u_char			:8;	/* Reserved			*/
	u_char	type		:1,	/* Buffer under or over runs	*/
		cause		:4,	/* Cause for over/under runs	*/
		cnt_basis	:3;	/* Count basis (how counted)	*/
}ALL_LOG_RUN_PG;

/*
 * TMC (Threshold Met Criteria) meanings
 */
#define	ALL_TMC_ALL	0x0	/* every update of cumulative value	*/
#define	ALL_TMC_EQ	0x1	/* cumulative value == threshold value	*/
#define	ALL_TMC_NE	0x2	/* cumulative value != threshold value	*/
#define	ALL_TMC_GT	0x3	/* comulative value > threshold value	*/

/* 
 * Cause field defines
 */
#define ALL_CAUSE_UNDEF		0x0	/* Cause undefined		*/
#define ALL_CAUSE_BBSY		0x01	/* SCSI BUS BUSY		*/
#define ALL_CAUSE_TRANS		0x02	/* Transfer rate to slow	*/

/*
 * Count basis field
 */
#define ALL_BASIS_UNDEFINED	0x0	/* Basis undefined		*/
#define	ALL_BASIS_PER_CMD	0x1	/* Per command			*/
#define	ALL_BASIS_PER_RECON	0x2	/* Per failed reconnect		*/
#define	ALL_BASIS_PER_TIME	0x3	/* Per unit time		*/

/*
 * Parameter codes for error counter pages
 */
#define ALL_LOG_NO_DELAY	0x0	/* corrections with no delay	   */
#define	ALL_LOG_WITH_DELAY	0x1	/* corrections with possible delay */
#define	ALL_LOG_TOTAL		0x2	/* Total (rereads/rewrites)	   */
#define	ALL_LOG_TOTAL_CORR	0x3	/* Total errors corrected	   */
#define	ALL_LOG_TOTAL_TIME_CORR	0x4	/* # times correction was invoked  */
#define	ALL_LOG_BYTES		0x5	/* # of bytes processed		   */
#define	ALL_LOG_TOTAL_UNCORR	0x6	/* # of uncorrected errors	   */




/* ---------------------------------------------------------------------- */

/* 
 * MODE Parameter defines
 */
/*
 * Definitions for CCS/SCSI-2 Devices.
 */



/*
 * Since we need to place all the page codes some where for easy 
 * reference they are here. But for each of the device specific 
 * information please refer to the .h file that deal with that 
 * device type. EXAMPLE sequence devices (tapes) see scsi_sequential.h 
 * Follows scsi 2 spec chapters.  
 */

		/* Values for Page Code field. */
/* Defined in chapters 8,9		0x01	   Error recovery page.	*/ 
#define ALL_PGM_DISCO_RECO		0x02	/* Disconnect/reconnect	*/
/* Defined in chapters 8		0x03	   Direct access format */
/* Defined in chapters 8		0x04	   Disk geometry page.	*/
/* Defined in chapters 8		0x05	   Flexible disk page.	*/
/* Defined in chapters			0x06				*/
/* Defined in chapters 8		0x07	   Verify error recovery*/
/* Defined in chapters 8		0x08	   Cache control page.  */
#define ALL_PGM_PERIPH_DEVICE		0x09	/* Peripheral Dev page  */
#define ALL_PGM_CONTROL_MODE		0x0A	/* Control Mode page	*/
/* Defined in chapters 8		0x0B	   Supported medium	*/
/* Defined in chapters 8		0x0C	   NOTCH and PARTITION	*/
/* Defined in chapters			0x0D	   Device parameters.   */
/* Defined in chapters 13		0x0E	   Audio control page.  */
/* Defined in chapters 9		0x10	   Device Configuration */
/* Defined in chapters 9		0x11	   Medium Partition pg1 */
/* Defined in chapters 9		0x12	   Medium Partition pg2 */
/* Defined in chapters 9		0x13	   Medium Partition pg3	*/
/* Defined in chapters 9		0x14	   Medium Partition pg4 */
#define	ALL_PGM_POWER			0x1A	/* Power condition	*/
#define	ALL_PGM_INFO_EXCEPTION		0x1C	/* Information exception*/
/* Defined in chapters ?????		0x25	   DEC specific page.   */
/* Defined in chapters ?????		0x38	   Read-ahead control   */



/* 
 * The mode parameter header, 6 byte cdb
 */
typedef struct all_mode_head6 {
	u_char	mode_len;	/* The length of the mode head 		*/
	u_char	medium_type;	/* The medium type			*/
	u_char	device_spec;	/* The device specific byte		*/
	u_char	blk_desc_len;	/* The length of the descriptor block	*/
}ALL_MODE_HEAD6;

/* 
 * The mode parameter header, 10 byte cdb
 */
typedef struct all_mode_head10 {
	u_char	mode_len1;	/* The length of the mode head MSB	*/
	u_char	mode_len0;	/* The length of the mode head LSB	*/
	u_char	medium_type;	/* The medium type			*/
	u_char	device_spec;	/* The device specific byte		*/
	u_char		:8;	/* Byte reserved			*/	
	u_char		:8;	/* Byte reserved			*/	
	u_char	blk_desc_len1;	/* Length of the descriptor block MSB	*/
	u_char	blk_desc_len0;	/* Length of the descriptor block LSB	*/
}ALL_MODE_HEAD10;


/* 
 * The Block Descriptor for both 6 and 10 byte MODE PARAMETERS.
 */

typedef struct all_mode_desc {
	u_char	density_code;	/* The density code Tapes		*/
	u_char	num_blocks2;	/* MSB of number of blocks 		*/
	u_char	num_blocks1;	/* Middle of number of blocks		*/
	u_char	num_blocks0;	/* LSB of number of blocks		*/
	u_char		:8;	/* reserved				*/
	u_char	block_len2;	/* MSB of block length			*/
	u_char	block_len1;	/* Middle of block length		*/
	u_char	block_len0;	/* LSB of block length			*/
}ALL_MODE_DESC;


/* 
 * The actual data structure for all the mode select data.
 */

/*
 * For a mode parameter list 6 byte cdb NON scatter/gather
 */

typedef struct all_mode_data6 {
	ALL_MODE_HEAD6		sel_head;	/* The header		*/
	ALL_MODE_DESC		sel_desc;	/* The descriptor piece	*/
	u_char	page_data[ALL_MAX_PAGE_SIZE - (sizeof(ALL_MODE_HEAD6) +
		sizeof(ALL_MODE_DESC) )];	/* Page data area	*/
}ALL_MODE_DATA6;


/*
 * For a mode parameter list 6 byte cdb scatter/gather
 */

typedef struct all_mode_data6_gather {
	ALL_MODE_HEAD6		*sel_head;	/* The header		*/
	ALL_MODE_DESC		*sel_desc;	/* The descriptor piece	*/
	u_char			*page_data;	/* Page data area	*/
}ALL_MODE_DATA6_GATHER;

/*
 * For a mode parameter list 10 byte cdb NON scatter/gather
 */
typedef struct all_mode_data10 {
	ALL_MODE_HEAD10		sel_head;	/* The header		*/
	ALL_MODE_DESC		sel_desc;	/* The descriptor piece	*/
	u_char	page_data[ALL_MAX_PAGE_SIZE];	/* Page data area	*/
}ALL_MODE_DATA10;



/*
 * For a mode parameter list 10 byte cdb scatter/gather
 */
typedef struct all_mode_data10_gather{
	ALL_MODE_HEAD10		*sel_head;	/* The header		*/
	ALL_MODE_DESC		*sel_desc;	/* The descriptor piece	*/
	u_char			*page_data;	/* Page data area	*/
}ALL_MODE_DATA10_GATHER;


/*
 * The mode page header
 */
typedef struct all_mode_pg_hd {
	u_char	page_code	: 6,	/* define page function */
		reserved	: 1,
		ps		: 1;	/* Page savable. */
	u_char	page_length;		/* length of current page */
}ALL_MODE_PG_HD;


/*
 * The pages defined in chapter 7
 */


/*
 * Page 0x2 - Disconnect / Reconnect Control Parameters:
 */
typedef struct all_disc_reco_pg {
	ALL_MODE_PG_HD	page_header;	/* The page header	*/
	u_char		buf_full_ratio;		/* data ready for xfer	*/
	u_char		buf_empty_ratio;	/* free space for writes */
	u_char		bus_inact_limit1;	/* maximum wasted time	*/
	u_char		bus_inact_limit0;
	u_char		discon_time_limit1;	/* minimum time for	*/
	u_char		discon_time_limit0;	/*  each disconnection	*/
	u_char		con_time_limit1;	/* max time of a single	*/
	u_char		con_time_limit_0;	/*  connection		*/
	u_char		max_burst_size1;	/* max number of blocks	*/
	u_char		max_burst_size0;	/*  per connection	*/
	u_char		dtdc	:3,		/* data transfer discon cntl*/ 
			dimm	:1,		/* Disconnect immediate	*/
			fastat	:1,		/* fair arb on message	*/
			fawrt	:1,		/* fair arb on write	*/
			fard	:1,		/* fair arb on read	*/
			emdp	:1;		/* enable MDP messages	*/
	u_char			:8;		/* Reserved		*/
	u_char		first_burst_size1;	/* first burst size msb	*/
	u_char		first_burst_size0;	/* first burst size lsb	*/
}ALL_DISC_RECO_PG;

/*
 * defines for the dtdc field.
 */
#define ALL_DISCON		0x00 /* Disconnects allowed 	  	*/
#define	ALL_NO_DISCON_DATA	0x01 /* Don't disconnect until data done */
#define ALL_NO_DISCON_CMD	0x03 /* Don't disconnect until cmd done	*/




/*
 * Page 0x9 - The device peripheral page
 */
typedef struct all_periph_dev_pg {
	ALL_MODE_PG_HD	page_header;
	u_char	interface_id1;	/* The interface identifier msb		*/
	u_char	interfave_id0;	/* The interface identifier lsb		*/
	u_char		:8;	/* reserved				*/
	u_char		:8;	/* reserved				*/
	u_char		:8;	/* reserved				*/
	u_char		:8;	/* reserved				*/
	u_char	vendor_specific[ALL_MAX_PAGE_SIZE - 8]; /* Total max 
						page size is 256	*/
}ALL_PERIPH_DEV_PG;





/* 
 * Page 0xA - The Control mode page 
 */
typedef struct all_control_pg {
	ALL_MODE_PG_HD	page_header;
	u_char	rlec	:1,	/* report log exception			*/
	      	gltsd	:1,	/* global log save disabled		*/
	      		:6;	/* reserved				*/
	u_char	dque	:1,	/* Disable tag queuing 1 = true		*/
		qerr	:1,	/* queue management error		*/
			:2,	/* reserved				*/
		que_algo :4;	/* Queue algorithm Modifier		*/
	u_char	eaenp	:1,	/* Async error notification enable	*/
		uaaenp	:1,	/* Async unit atten notification enable	*/
		raenp	:1,	/* Async unit ready notification enable	*/
		swp	:1,	/* S/W write protect			*/
			:1,	/* Reserved				*/
			:1,	/* Reserved				*/
		rac	:1,	/* do CC not busy during long CA	*/
		eeca	:1;	/* Extended contingent allegiance enable*/
	u_char		:8;	/* reserved				*/
	u_char	aen_holdoff1;	/* MSB in milliseconds to hold off async*/
	u_char	aen_holdoff0;	/* LSB in milliseconds to hold off async*/
	u_char	busy_timeout1;	/* MSB in 100 milliseconds to stay busy	*/
	u_char	busy_timeout0;	/* LSB in 100 milliseconds to stay busy	*/
	u_char		:8;	/* reserved				*/
	u_char		:8;	/* reserved				*/
}ALL_CONTROL_PG;

/*
 * que_algo modifiers
 */
#define ALL_QUEUE_RESTRICT	0x0	/* restricted reordering	*/
#define	ALL_QUEUE_NORESTRICT	0x1	/* unrestricted reordering	*/


/* 
 * Page 0x1A - The Power Condition mode page 
 */
typedef struct all_power_condition_pg {
	ALL_MODE_PG_HD	page_header;
	u_char		:8;	/* reserved				*/
	u_char	standby	:1,	/* Standby mode				*/
		idle	:1,	/* Idle mode				*/
			:6;	/* reserved				*/
	u_char	idle_time3;	/* MSB of time in 100 milliseconds	*/
	u_char	idle_time2;	/*   before the device			*/
	u_char	idle_time1;	/*     will enter the idle		*/
	u_char	idle_time0;	/*        state.			*/
	u_char	standby_time3;	/* MSB of time in 100 milliseconds	*/
	u_char	standby_time2;	/*   before the device			*/
	u_char	standby_time1;	/*     will enter the standby		*/
	u_char	standby_time0;	/*        state.			*/
}ALL_POWER_CONDITION_PG;



/* 
 * Page 0x1C - The Information Exception mode page 
 */
typedef struct all_info_exception_pg {
	ALL_MODE_PG_HD	page_header;
	u_char	logerr	:1,	/* log informational exceptions		*/
			:1,	/* Reserved				*/
		test	:1,	/* force a failure at next interval	*/
		dexcpt	:1,	/* disable exception reporting		*/
			:3,
		perform	:1;  	/* 1 = performance over reporting	*/
				/* 0 = reporting over performance	*/
	u_char	mrie	:4,	/* Method of reporting			*/
			:4;	/* Reserved				*/
	u_char	inter_timer3;	/* MSB of time in 100 milliseconds	*/
	u_char	inter_timer2;	/*   before the device			*/
	u_char	inter_timer1;	/*     will report any informational	*/
	u_char	inter_timer0;	/*        exceptions.			*/
	u_char	report_count3;	/* MSB of the number			*/
	u_char	report_count2;	/*   of times the device		*/
	u_char	report_count1;	/*     will report any informational	*/
	u_char	report_count0;	/*        exceptions.			*/
}ALL_INFO_EXCEPTION_PG;

/*
 * Methods of reporting informational exceptions
 */
#define	ALL_INFO_NONE	0x0	/* no reporting of informational exceptions */
#define ALL_INFO_AEN	0x1	/* use AEN (with recovered error)	    */
#define	ALL_INFO_UA	0x2	/* use Unit Attention			    */
#define	ALL_INFO_CGRE	0x3	/* Conditional Generate Recovered Error	    */
#define	ALL_INFO_UGRE	0x4	/* Unconditional Generate Recovered Error   */
#define ALL_INFO_NOSENSE 0x5	/* Use NO Sense				    */
#define	ALL_INFO_REQ	0x6	/* only report when requested		    */




/* ---------------------------------------------------------------------- */

/* 
 * SEND DIAGNOSTIC Command
 */
typedef struct all_send_diagnostic_cdb {
	u_char	opcode;			/* 0x1d Operation Code.		[0] */
	u_char	control	: 5,		/* Diagnostic control bits.	[1] */
		lun	: 3;		/* Logical Unit Number.		    */
	u_char		: 8;		/* Reserved.			[2] */
	u_char	param_len1;		/* Parameter length (MSB).	[3] */
	u_char	param_len0;		/* Parameter length (LSB).	[4] */
	u_char	link	: 1,		/* Link.			[5] */
		flag	: 1,		/* Flag.			    */
		naca	: 1,		/* Normal ACA.			    */
			: 3,		/* Reserved.			    */
		vendor	: 2;		/* Vendor Unique.		    */
} ALL_SEND_DIAGNOSTIC_CDB;

#define ALL_SEND_DIAGNOSTIC_OP	0x1D

/* ---------------------------------------------------------------------- */

/*
 * Test unit ready
 */
typedef struct all_tur_cdb {
	u_char	opcode;		/* OPcode = 0X00			*/
	u_char		:5,	/* 5 Bits reserved			*/
		lun	:3;	/* LUN					*/
	u_char		:8;	/* Reserved				*/
	u_char		:8;	/* Reserved				*/
	u_char		:8;	/* Reserved				*/
	u_char	control;	/* Control byte				*/
}ALL_TUR_CDB;


/*
 * Opcode define for test unit ready
 */
#define ALL_TUR_OP	0X00	/* The opcode				*/

/* ---------------------------------------------------------------------- */


/*
 * The defines and marco for the asc and asq fields
 * in the return data from a request sense
 */

/*
 * This macro takes a pointer to the sense data, and a u_short.
 * With the pointer it make sure that the additional sense
 * length is large enought to contain the asc and asq fields.
 * The the asc field goes to the high byte and asq to the low.
 */

#define ASCQ_TO_USHORT(sns_data,ascq); { \
    union { \
	unsigned char c[2]; \
	unsigned short l; \
    }tmp; \
    if(((ALL_REQ_SNS_DATA *)(sns_data))->addition_len < 4) { \
	(ascq) = 0; \
    } \
    else { \
    	tmp.c[0] = ((ALL_REQ_SNS_DATA *)(sns_data))->asq; \
    	tmp.c[1] = ((ALL_REQ_SNS_DATA *)(sns_data))->asc; \
	(ascq) = tmp.l; \
    } \
}
	

#define	ASCQ_NO_ADDITIONAL	0x0000 
			/* NO Additional Sense Information */

#define	ASCQ_FILEMARK		0x0001 
			/* Filemark detected */

#define ASCQ_EOPM		0x0002 
			/* End of partition/medium detected */

#define	ASCQ_SETMARK	 	0x0003 
			/* Setmark detected */

#define	ASCQ_BOPM	 	0x0004 
			/* Begining of partition/medium detected */

#define	ASCQ_EOD	 	0x0005 
			/* End of data detected */

#define	ASCQ_IO_TERM	 	0x0006 
			/* I/O process terminated */
	
#define	ASCQ_AUDIO_INPROG 	0x0011 
			/* Audio play operation in progress */

#define	ASCQ_AUDIO_PAUSED	0x0012 
			/* Audio play operation paused */

#define	ASCQ_AUDIO_SUCCESS	0x0013 
#define	ASCQ_AUDIO_SUCC   	ASCQ_AUDIO_SUCCESS	/* for compatibility */ 
			/* Audio play operation successfully completed */

#define	ASCQ_AUDIO_ERR		0x0014 
			/* Audio play operation stopped due to error */

#define	ASCQ_AUDIO_NO_STAT 	0x0015 
			/* No current audio status to return */

#define	ASCQ_OP_IN_PROGRESS	0x0016
			/* Operation in progress */

#define	ASCQ_CLEANING_REQ 	0x0017 
			/* Cleaning requested */

#define	ASCQ_NO_IDX_SEC		0x0100 
			/* No index/sector signal */

#define	ASCQ_NO_SEEK_CMP 	0x0200 
			/* No seek complete */

#define	ASCQ_WRT_FLT		0x0300 
			/* Device write fault */
	
#define	ASCQ_NO_WRT_CURR 	0x0301 
			/* NO write current */

#define	ASCQ_EXCESS_WRT_ERR	0x0302 
			/* Excessive write errors */

#define	ASCQ_LUN_NRDY_STAT	0x0400 
			/* LUN Not ready, cause not reportable */

#define	ASCQ_LUN_NRDY_INPROG	0x0401 
			/* LUN Is in process of becoming ready */

#define	ASCQ_LUN_NRDY_INIT	0x0402 
			/* LUN Not ready, init command required */

#define	ASCQ_LUN_NRDY_MAN	0x0403 
			/* LUN Not ready, manual intervention required */

#define	ASCQ_LUN_NRDY_FMT 	0x0404 
			/* LUN Not ready, format inprogress */

#define	ASCQ_LUN_NRDY_RBLD 	0x0405 
			/* LUN Not ready, rebuild in progress */

#define	ASCQ_LUN_NRDY_RECALC 	0x0406 
			/* LUN Not ready, recalculation in progress */

#define	ASCQ_LUN_NRDY_OPERAT 	0x0407 
			/* LUN Not ready, operation in progress */

#define	ASCQ_LUN_NRDY_LONGW 	0x0408 
			/* LUN Not ready, Long write in progress */

#define	ASCQ_LUN_NO_SEL		0x0500 
			/* LUN does not respond to selection */

#define	ASCQ_NO_REF_POS		0x0600 
			/* No reference position found */

#define	ASCQ_MULTI_SEL		0x0700 
			/* Multiple devices selected */

#define	ASCQ_LUN_COMM_FLT	0x0800 
			/* LUN communication failure */

#define	ASCQ_LUN_COMM_TIMO	0x0801 
			/* LUN communication timeout */

#define	ASCQ_LUN_COMM_PARITY	0x0802 
			/* LUN communication parity error */

#define	ASCQ_LUN_COMM_CRC	0x0803 
			/* LUN communication CRC error (Ultra-DMA/32) */

#define	ASCQ_TRK_FOL_ERR	0x0900 
			/* Track following error */

#define	ASCQ_TRK_SERVO		0x0901 
			/* Tracking servo failure */

#define	ASCQ_FOCUS_SERVO	0x0902 
			/* Focus servo failure */

#define	ASCQ_SPINDLE_SERVO	0x0903 
			/* Spindle servo failure */

#define	ASCQ_HEAD_SELECT	0x0904 
			/* Head select fault */

#define	ASCQ_ERR_LOG_OVF	0x0a00 
			/* Error log overflow */

#define	ASCQ_WARNING		0x0b00 
			/* Warning */

#define	ASCQ_TEMP_EXCEEDED	0x0b01 
			/* Warning - Temperature exceeded */

#define	ASCQ_ENCLOSURE_DEGRADED	0x0b02 
			/* Warning - Enclosure degraded */

#define	ASCQ_WRT_ERR		0x0c00 
			/* Write error */

#define	ASCQ_WRT_RECV_REALL 	0x0c01 
			/* Write error recovered with auto reallocation */

#define	ASCQ_WRT_REALL_FTL 	0x0c02 
			/* Write error - auto reallocation failed */

#define	ASCQ_WRT_REC_REASS 	0x0c03 
			/* Write error - recommend reassignment */

#define	ASCQ_COMP_MISCOMPARE 	0x0c04 
			/* Compression check miscompare error */

#define	ASCQ_DATA_EXPANDED 	0x0c05 
			/* Data expansion occured during compression */

#define	ASCQ_NOT_COMPRESSED 	0x0c06 
			/* Block not compressable */

#define	ASCQ_WRT_ERR_REC_NEEDED	0x0c07 
			/* Write error - recovery needed */

#define	ASCQ_WRT_ERR_REC_FAIL	0x0c08 
			/* Write error - recovery failed */

#define	ASCQ_WRT_ERR_NO_STREAM	0x0c09 
			/* Write error - loss of streaming */

#define	ASCQ_WRT_ERR_PAD_ADDED	0x0c0a 
			/* Write error - padding blocks added */

#define	ASCQ_ID_CRC_ECC_ERR	0x1000 
			/* ID, CRC, or ECC error */

#define	ASCQ_UNRECV_RD_ERR	0x1100 
			/* Unrecoverable read error */

#define	ASCQ_RD_RETRIES_EXH	0x1101 
			/* Read retries exhausted */
	
#define	ASCQ_ERR_TO_LONG	0x1102 
			/* Error to long to correct */

#define	ASCQ_MULTI_RD_ERR	0x1103 
			/* Multiple read errors */

#define	ASCQ_RD_ERR_REALL_FLT	0x1104 
			/* Unrecovered read error - auto reallocation failed */

#define	ASCQ_L_EC_UNCORR	0x1105 
			/* L-EC Uncorrectable error */

#define	ASCQ_CIRC_UNCORR 	0x1106 
			/* CIRC Unrecovered error */

#define	ASCQ_DATA_RESYNC_ERR	0x1107 
			/* Data resynchronization error */

#define	ASCQ_INCOMP_BLK_RD	0x1108 
			/* Incomplete block read */

#define	ASCQ_NO_GAP		0x1109 
			/* No gap found */

#define	ASCQ_MISCORR_ERR	0x110a 
			/* Miscorrected error */

#define	ASCQ_UNRECV_RD_REC_REASS 0x110b 
			/* Unrecovered read error - recommend reassignment */

#define	ASCQ_UNRECV_RD_REC_REWRT 0x110c 
			/* Unrecovered read error - recommend rewrite data */

#define	ASCQ_DECOMPRESS_ERR	0x110d 
			/* De-compression CRC error */

#define	ASCQ_NOT_DECOMPRESSED	0x110e 
			/* cannot decompressing using declared algorithm */

#define	ASCQ_NO_UPC_EAN_NUMBER	0x110f 
			/* Error reading UPC/EAN number */

#define	ASCQ_ERR_ON_ISRC_NUMBER	0x1110 
			/* Error reading ISRC number */

#define	ASCQ_ERR_LOST_STREAMING	0x1111 
			/* Read error - loss of streaming */

#define	ASCQ_ADDR_MK_ID		0x1200 
			/* Address mark not found for ID field */

#define	ASCQ_ADDR_MK_DATA 	0x1300 
			/* Address mark not found for DATA field */

#define	ASCQ_REC_ENTITY_NFND	0x1400 
			/* Recorded entity not found */

#define	ASCQ_REC_NFND 		0x1401 
			/* Record not found */

#define	ASCQ_FS_MARK_NFND	0x1402 
			/* Filemark or setmark not found */

#define	ASCQ_EOD_NFND 		0x1403 
			/* End of data not found */

#define	ASCQ_BLK_SEQ_ERR	 0x1404 
			/* Block Sequence error */

#define	ASCQ_RECNF_REC_REASS	 0x1405 
			/* Record not found - recommend reassignment */

#define	ASCQ_RECNF_DATA_REASS	 0x1406 
			/* Record not found - data auto-reallocated */

#define	ASCQ_RAN_POS_ERR	 0x1500 
			/* Random Positioning error */

#define	ASCQ_MECH_POS_ERR	 0x1501 
			/* Mechanical positioning error */

#define	ASCQ_POS_ERR_RD		 0x1502 
			/* Positioning error detected by read of medium */

#define	ASCQ_DATA_SYNC_MARK	 0x1600 
			/* Data synchronization MARK error */

#define	ASCQ_SYNC_REWRITTEN	0x1601 
			/* Data Synch error - data rewritten */

#define	ASCQ_SYNC_REC_REWRITE	 0x1602 
			/* Data Synch error - Recommend rewrite */

#define	ASCQ_SYNC_REASS		 0x1603 
			/* Data Synch error - Auto reallocated */

#define	ASCQ_SYNC_REC_REASS	 0x1604 
			/* Data Synch error - recommend reassignment */

#define	ASCQ_RECV_NO_ECC	 0x1700 
			/* Recovered data with no error correction */

#define	ASCQ_RECV_RETRIES	 0x1701 
			/* Recovered data with retries */

#define	ASCQ_RECV_POS_OFF	 0x1702 
			/* Recovered data with positive head offset */

#define	ASCQ_RECV_NEG_OFF	 0x1703 
			/* Recovered data with negative head offset */

#define	ASCQ_RECV_CIRC	 	0x1704 
			/* Recovered data with retries and/or CIRC applied */

#define	ASCQ_RECV_PREV_SEC	0x1705 
			/* Recovered data using previous sector */

#define	ASCQ_RECV_REASS		0x1706 
			/* Recovered data without ECC - Data auto reallocated */

#define	ASCQ_RECV_REC_REASS 	0x1707 
			/* Recovered data without ECC - recommend reassign */

#define	ASCQ_RECV_REC_REWRITE 	0x1708 
			/* Recovered data without ECC - recommend rewrite */

#define	ASCQ_RECV_REWRITTEN 	0x1709 
			/* Recovered data without ECC - data rewritten */

#define	ASCQ_RECV_ECC	 	0x1800 
			/* Recovered data with error correction applied */

#define	ASCQ_RECV_ECC_RETRIES 	0x1801 
			/* Recovered data with ECC Applied and retries */

#define	ASCQ_RECV_DATA_REASS	0x1802 
			/* Recovered data - Data auto reallocated */

#define	ASCQ_RECV_DATA_CIRC	0x1803 
			/* Recovered data with CIRC */

#define	ASCQ_RECV_LEC		0x1804 
			/* Recovered data with LEC */

#define	ASCQ_RECV_DATA_REC_REASS 0x1805 
			/* Recovered data - recommend reassignment */

#define	ASCQ_RECV_DATA_REC_REWRITE 0x1806 
		       /* Recovered data - recommend rewrite */

#define	ASCQ_RECV_DATA_REWRITTEN 0x1807 
		       /* Recovered data - data rewritten */

#define	ASCQ_DEFECT_ERR		0x1900 
			/* Defect list error */

#define	ASCQ_DEFECT_NAVAIL	0x1901 
			/* Defect list not available */

#define	ASCQ_DEFECT_PRIM_ERR	0x1902 
			/* Defect list error in primary list */

#define	ASCQ_DEFECT_GROWN_ERR	0x1903 
			/* Defect list error in grown list */

#define	ASCQ_PARAM_LEN_ERR	0x1a00 
			/* Parameter list length error */

#define	ASCQ_SYNC_TRAN_ERR	0x1b00 
			/* Synchronous data transfer error */

#define	ASCQ_DEFECT_NFND	0x1c00 
			/* Defect list not found */
	
#define	ASCQ_DEFECT_PRIM_NFND	0x1c01 
			/* Primary defect list not found */

#define	ASCQ_DEFECT_GROWN_NFND	0x1c02 
			/* Grown defect list not found */

#define	ASCQ_MISCMP_VERI	0x1d00 
			/* Miscompare during verify */

#define	ASCQ_RECV_ID_ECC	0x1e00 
			/* Recovered ID with ECC correction */

#define	ASCQ_PARTIAL_DEFECT	0x1f00 
			/* Partial defect list transfer */

#define	ASCQ_INVAL_CMD_OP	0x2000 
			/* Invaild command operation code */

#define	ASCQ_LBN_RANGE		0x2100
			/* LBN out of range */

#define	ASCQ_INVAL_ELEM		0x2101 
			/* Invalid element address */

#define	ASCQ_ILL_FUNC		0x2200 
			/* Illegal function ( USE 20 00, 24 00 or 26 00) */

#define	ASCQ_INVAL_FLD_CDB	0x2400 
			/* Invalid field in CDB */

#define	ASCQ_LUN_NSUP		0x2500 
			/* LUN not supported */

#define	ASCQ_INVAL_FLD_PARAM	0x2600 
			/* Invalid field in parameter list */

#define	ASCQ_PARAM_NSUP		0x2601 
			/* Parameter not supported */

#define	ASCQ_PARAM_VAL_INV 	0x2602 
			/* Parameter value invalid */

#define	ASCQ_THRES_PARAM_NSUP	0x2603 
			/* Threshold parameters not supported */

#define	ASCQ_ILL_P_RELEASE	0x2604 
			/* Invalid release of active persistent reservation */

#define	ASCQ_WRT_PROT		0x2700 
			/* Write protected */

#define	ASCQ_HW_WRT_PROT	0x2701 
			/* Hardware write protected */

#define	ASCQ_SW_WRT_PROT	0x2702 
			/* Logical unit software write protected */

#define	ASCQ_ASSOC_WRT_PROT	0x2703 
			/* Associated write protected */

#define	ASCQ_PERSIST_WRT_PROT	0x2704 
			/* Persistent write protected */

#define	ASCQ_PERM_WRT_PROT	0x2705 
			/* Permanent write protected */

#define	ASCQ_NRDY_TO_RDY 	0x2800 
		/* Not ready to ready transistion (medium may have changed) */

#define	ASCQ_IMP_EXP_ACCESS 	0x2801 
			/* import or export element accessed */

#define	ASCQ_PON_RESET		0x2900 
			/* Power on, reset, bus device reset occurred */
	
#define	ASCQ_POWER_ON		0x2901 
			/* Power on occured */
	
#define	ASCQ_BUS_RESET		0x2902 
			/* Bus Reset occured */
	
#define	ASCQ_BDR_RESET		0x2903 
			/* BDR occured */
	
#define	ASCQ_FIRMWARE_REBOOT	0x2904 
			/* Device internal reset */
	
#define	ASCQ_PARAM_CHG		0x2a00 
			/* Parameters changed */

#define	ASCQ_MODE_PARAM_CHG	0x2a01 
			/* Mode parameters changed */

#define	ASCQ_LOG_PARAM_CHG	0x2a02 
			/* Log parameters changed */

#define	ASCQ_PREEMPTED_RESERVES	0x2a03 
			/* reservations preempted */

#define	ASCQ_CPY_NO_DISC	0x2b00 
			/* Copy can't execute since host can't disconnect */

#define	ASCQ_CMD_SEQ_ERR	0x2c00 
			/* Commnad sequence error */

#define	ASCQ_TOO_MANY_WINS	0x2c01 
			/* Too many window specified */

#define	ASCQ_INVAL_COMP_WINS	0x2c02 
			/* Invalid combination of windows specified */

#define	ASCQ_NOT_EMPTY		0x2c03 
			/* Current program area is not empty */

#define	ASCQ_IS_EMPTY		0x2c04 
			/* Current program area is empty */

#define	ASCQ_OVR_WRT_UPD	0x2d00 
			/* Overwrite error on update in place */

#define	ASCQ_CMDS_CLEARED	0x2f00 
			/* Commands cleared by another initiator */

#define	ASCQ_INCOMPAT_MEDIA	0x3000 
			/* Incompatible medium installed */

#define	ASCQ_UNKNW_FMT	 	0x3001 
			/* Cannot read medium - unknown format */

#define	ASCQ_INCOMPAT_FMT	0x3002 
			/* Cannot read medium - incompatible format */
	
#define	ASCQ_CLEAN_CART		0x3003 
			/* Cleaning cartridge installed */

#define	ASCQ_RO_UNKNW_FMT	0x3004 
			/* Cannot write medium - unknown format */

#define	ASCQ_RO_INCOMPAT_FMT	0x3005 
			/* Canot write medium - incompatible format */

#define	ASCQ_NOFMT_INCOMPAT_MEDIA 0x3006 
			/* Cannot format medium - incompatible media */

#define	ASCQ_CLEAN_FAILED	0x3007 
			/* Cleaning failure */

#define	ASCQ_AP_CODE_MISMATCH	0x3008 
			/* Cannot write - application code mismatch */

#define	ASCQ_NO_APPEND		0x3009 
			/* current session not fixated for append */

#define	ASCQ_FMT_CORRUPT	0x3100 
			/* Medium format corrupted */

#define	ASCQ_FMT_FAILED		0x3101 
			/* Format command failed */

#define	ASCQ_NO_DEFECT_SPARE	0x3200 
			/* No defect spare location available */

#define	ASCQ_DEFECT_UPDATE_FAIL	0x3201 
			/* Defect list update failure */

#define	ASCQ_TAPE_LEN_ERR	0x3300 
			/* Tape length error */

#define	ASCQ_ENCLOSURE_FAIL	0x3400 
			/* Enclosure failure */

#define	ASCQ_ENCLOS_SERV_FAIL	0x3500 
			/* Enclosure services failure */

#define	ASCQ_ENCLOS_UNSUP_FUNC	0x3501 
			/* Unsupported enclosure function */

#define	ASCQ_ENCLOS_SERV_UNAVAIL 0x3502 
			/* Enclosure services unavailable */

#define	ASCQ_ENCLOS_SERV_XFER_FAIL 0x3503 
			/* Enclosure services transfer failure */

#define	ASCQ_ENCLOS_SERV_XFER_NO 0x3504 
			/* Enclosure services transfer refused */

#define	ASCQ_INK_RIB_ERR	0x3600 
			/* Ribbon, ink or toner failure */

#define	ASCQ_RND_PARAM		0x3700 
			/* Rounded parameter */

#define	ASCQ_SAVE_PARAM_NSUP	0x3900 
			/* Saving parameters not supported */

#define	ASCQ_MEDIA_NPRES	0x3a00 
			/* Medium not present */

#define	ASCQ_MEDIA_NPRES_CLOSE	0x3a01 
			/* Medium not present - tray closed */

#define	ASCQ_MEDIA_NPRES_OPEN	0x3a02 
			/* Medium not present - tray open */

#define	ASCQ_SEQ_POS_ERR	0x3b00 
			/* Sequential postioning error */

#define	ASCQ_POS_BOM_ERR	0x3b01 
			/* Tape position error at Begining of media */

#define	ASCQ_POS_EOM_ERR	0x3b02 
			/* Tape position error at End of media */

#define	ASCQ_VERT_FORM_NRDY	0x3b03 
			/* Tape or electronic vertical forms unit not ready */

#define	ASCQ_SLEW_FLT		0x3b04 
			/* Slew failure */

#define	ASCQ_PAPER_JAM		0x3b05 
			/* Paper jAM */

#define	ASCQ_FAIL_TFORM		0x3b06 
			/* Failed to sense top of form */

#define	ASCQ_FAIL_BFORM		0x3b07 
			/* Failed to sense bottom of form */

#define	ASCQ_REPOS_ERR		0x3b08 
			/* Reposition error */

#define	ASCQ_RD_PAST_EOM	0x3b09 
			/* Read past end of medium */

#define	ASCQ_RD_PAST_BOM	0x3b0a 
			/* Read past beginning of medium */

#define	ASCQ_POS_PAST_EOM	0x3b0b 
			/* Position past end of medium */

#define	ASCQ_POS_PAST_BOM	0x3b0c 
			/* Position past beginning of medium */

#define	ASCQ_MEDIA_DEST_EMP	0x3b0d 
			/* Medium destination element empty */

#define	ASCQ_MEDIA_SRC_EMP	0x3b0e 
			/* Medium source element empty */

#define	ASCQ_MEDIA_AT_END	0x3b0f 
			/* End of medium reached */

#define	ASCQ_MAG_NO_ACCESS	0x3b11 
			/* Medium magazine not accessible */

#define	ASCQ_MAG_REMOVED	0x3b12 
			/* Medium magazine removed */

#define	ASCQ_MAG_INSERTED	0x3b13 
			/* Medium magazine inserted */

#define	ASCQ_MAG_LOCKED		0x3b14 
			/* Medium magazine locked */

#define	ASCQ_MAG_UNLOCKED	0x3b15 
			/* Medium magazine unlocked */

#define	ASCQ_INVAL_BIT_IDMSG	0x3d00 
			/* Invalid bits in identify message */

#define	ASCQ_LUN_NSELF_CONF	0x3e00 
			/* Logical unit has not self configured yet */

#define	ASCQ_LUN_FAILED		0x3e01 
			/* Logical unit failure */

#define	ASCQ_LUN_TIMED_OUT	0x3e02 
			/* Timeout on logical unit  */

#define	ASCQ_TARGET_OP_CHG	0x3f00 
			/* Target operating conditions have changed */

#define	ASCQ_MICRO_CODE_CHG	0x3f01 
			/* Micro code has changed */

#define	ASCQ_CHG_OP_DEF		0x3f02 
			/* Changed operating definition */

#define	ASCQ_INQ_CHG		0x3f03 
			/* Inquiry data has changed */

#define	ASCQ_RAM_FLT		0x4000 
			/* Ram failure (should use 40 nn) */

			/*	0x40nn
			 * diagnostic failure on component nn 80h-ffh) */

#define	ASCQ_DATA_PATH_FLT	0x4100 
			/* Data path failure (should use 40 nn) */

#define	ASCQ_PON_SELFT_FLT	0x4200 
			/* Power on or self test failure (should use 40 nn) */

#define	ASCQ_MSG_ERR		0x4300 
			/* Message error */

#define	ASCQ_INT_TARGET_FLT	0x4400 
			/* Internal target failure */

#define	ASCQ_SEL_RSEL_FLT	0x4500 
			/* Select or reselect failure */

#define	ASCQ_UNSUCC_SRESET	0x4600 
			/* Unsuccessful soft reset */

#define	ASCQ_SCSI_PARITY_ERR	0x4700 
			/* SCSI parity error */

#define	ASCQ_INITOR_ERR_MSG	0x4800 
			/* Initiator detected error message recieved */

#define	ASCQ_INVAL_MSG_ERR	0x4900 
			/* Invalid message error */

#define	ASCQ_CMD_PHASE_ERR	0x4a00 
			/* Command phase error */

#define	ASCQ_DATA_PHASE_ERR	0x4b00 
			/* Data phase error */

#define	ASCQ_LUN_STEST_FLT	0x4c00 
			/* LUN failed self-configuration */

			/*	0x4dnn
			 * tagged overlapped commands (nn = queue tag) */

#define	ASCQ_OVRL_CMDS_AMPT	0x4e00 
			/* Overlapped Commands attemped */

#define	ASCQ_WRT_APPEND_ERR	0x5000 
			/* Write append error */

#define	ASCQ_WRT_APPEND_POS_ERR	0x5001 
			/* Write append position error */

#define	ASCQ_POS_ERR_TIME	0x5002 
			/* Position error related to timing */

#define	ASCQ_ERASE_FLT		0x5100 
			/* Erase failure */

#define	ASCQ_CART_FLT		0x5200 
			/* Cartridge fault */

#define	ASCQ_MEDIA_LD_EJ_FLT	0x5300 
			/* Media load or eject failure */

#define	ASCQ_TAPE_UNLD_FLT	0x5301 
			/* Unload tape failure */

#define	ASCQ_MEDIA_PREVNT	0x5302 
			/* Medium removal prevented */

#define	ASCQ_SCSI_HOST_FLT	0x5400 
			/* SCSI to host system interface failure */
	
#define	ASCQ_SYS_RESRC_FLT	0x5500 
			/* System resource failure */

#define	ASCQ_SYS_BUFFER_FULL	0x5501 
			/* System buffer full */

#define	ASCQ_UNRECV_TAB_CONT	0x5700 
			/* Unable to recover table of contents */

#define	ASCQ_GEN_NEXIST		0x5800 
			/* Generation does not exist */

#define	ASCQ_UPDT_BLK_RD	0x5900 
			/* Updated block read */

#define	ASCQ_OPR_REQ_STATE	0x5a00 
			/* Operator request or state change input */

#define	ASCQ_OPR_MEDIA_RM_REQ	0x5a01 
			/* Operator medium removal request */

#define	ASCQ_OPR_SEL_WRT_PROT	0x5a02 
			/* Operator selected write protect */

#define	ASCQ_OPR_SEL_WRT	0x5a03 
			/* Operator selected write permit */

#define	ASCQ_LOG_EXCEPT		0x5b00 
			/* Log exception */

#define	ASCQ_THRES_MET		0x5b01 
			/* Threshold condition met */

#define	ASCQ_LOG_CNT_MAX	0x5b02 
			/* Log counter at maximum */

#define	ASCQ_LOG_LIST_CODES	0x5b03 
			/* Log list codes exhausted */

#define	ASCQ_RPL_STAT_CHG	0x5c00 
			/* RPL status change */

#define	ASCQ_SPINDLES_SYNC	0x5c01 
			/* Spindles synchronized */

#define	ASCQ_SPINDLES_NSYNC	0x5c02 
			/* Spindles not synchronized */

#define	ASCQ_PREDICT_FAILURE	0x5d00
			/* Failure prediction threshold exceeded */

#define	ASCQ_PREDICT_FAILURE_FALSE 0x5dff
			/* Failure prediction threshold exceeded (false) */

#define	ASCQ_LOW_POWER		0x5e00
			/* Low power condition on */

#define	ASCQ_IDLE_BY_TIMER	0x5e01
			/* Idle condition activated by timer */

#define	ASCQ_STANDBY_BY_TIMER	0x5e02
			/* Standby condition activated by timer */

#define	ASCQ_IDLE_BY_CMD	0x5e03
			/* Idle condition activated by command */

#define	ASCQ_STANDBY_BY_CMD	0x5e04
			/* Standby condition activated by command */

#define	ASCQ_LAMP_FLT		0x6000 
			/* Lamp failure */

#define	ASCQ_VID_ACQ_ERR	0x6100 
			/* Video acquistion error */

#define	ASCQ_UNA_ACQ_VID	0x6101 
			/* Unable to aquire video */

#define	ASCQ_OUT_FOCUS		0x6102 
			/* Out of focus */

#define	ASCQ_SCAN_HD_POS_ERR	0x6200 
			/* Scan head position error */

#define	ASCQ_END_USER_AREA	0x6300 
			/* End of user area encountered on this track */

#define	ASCQ_PACKET_NOT_FIT	0x6301 
			/* Packet does not fit in available space */

#define	ASCQ_ILL_MODE_TRK	0x6400 
			/* Illegal mode for this track */
	
#define	ASCQ_ILL_PACKET_SIZE	0x6401 
			/* Invalid packet size */
	
#define	ASCQ_VOLTAGE_FAULT	0x6500 
			/* Voltage fault */

#define	ASCQ_FEEDER_COVER_UP	0x6600
			/* Automatic document feeder cover up */

#define	ASCQ_FEEDER_LIFT_UP	0x6601
			/* Automatic document feeder lift up */

#define	ASCQ_JAM_IN_FEEDER	0x6602
			/* Document jam in automatic document feeder */

#define	ASCQ_MISSFEED_IN_FEEDER	0x6603
			/* Document miss feed in automatic document feeder */

#define	ASCQ_CONFIG_FAILURE	0x6700
			/* Configuration failure */

#define	ASCQ_NGLUN_CONFIG_FAIL	0x6701
			/* Configuration of incapable logical units failed */

#define	ASCQ_ADD_LUN_FAILED	0x6702
			/* Add logical unit failed */

#define	ASCQ_MOD_LUN_FAILED	0x6703
			/* Modification of logical unit failed */

#define	ASCQ_EXC_LUN_FAILED	0x6704
			/* Exchange of logical unit failed */

#define	ASCQ_REM_LUN_FAILED	0x6705
			/* Remove of logical unit failed */

#define	ASCQ_ATT_LUN_FAILED	0x6706
			/* Attachment of logical unit failed */

#define	ASCQ_CREATE_LUN_FAILED	0x6707
			/* Creation of logical unit failed */

#define	ASCQ_LUN_NOT_CONFIGED	0x6800
			/* Logical unit not configured */

#define	ASCQ_DATA_LOSS_ON_LUN	0x6900
			/* Data loss on logical unit */

#define	ASCQ_MULTI_LUN_FAILURE	0x6901
			/* Multiple logical unit failures */

#define	ASCQ_RAID_PARITY_MISMATCH 0x6902
			/* Parity/data mismatch */

#define	ASCQ_INFORM_SEE_LOG	0x6a00
			/* Informational, refer to log */

#define	ASCQ_STATE_CHANGED	0x6b00
			/* State change has occurred */

#define	ASCQ_RAID_GOT_BETTER	0x6b01
			/* Redundancy level got better */

#define	ASCQ_RAID_GOT_WORSE	0x6b02
			/* Redundancy level got worse */

#define	ASCQ_REBUILD_FAILED	0x6c00
			/* Rebuild failure occured */

#define	ASCQ_RECALC_FAILED	0x6d00
			/* Recalculation failure occured */

#define	ASCQ_CMD_TO_LUN_FAILED	0x6e00
			/* Command to logical unit failed */

			/*	0x70nn
			 * Decompression exception short algorithm id of nn */

#define	ASCQ_DECOMPRESS_EXCPT	0x7100
			/* Decompression exception long algorithm id */

#define	ASCQ_FIXATION_ERR	0x7200
			/* Session fixation error */

#define	ASCQ_FIXATION_ERR_IN	0x7201
			/* Session fixation error writing lead-in */

#define	ASCQ_FIXATION_ERR_OUT	0x7202
			/* Session fixation error writing lead-out */

#define	ASCQ_FIXATION_ERR_INCOMPLETE 0x7203
			/* Session fixation error incomplete track in session */

#define	ASCQ_BAD_RESERVED_TRACK	0x7204
			/* Empty or partially written reserved track */

#define	ASCQ_CD_CTRL_ERR	0x7300
			/* CD control error */

#define	ASCQ_CALIB_NEAR_FULL	0x7301
			/* Power calibration area almost full */

#define	ASCQ_CALIB_IS_FULL	0x7302
			/* Power calibration area is full */

#define	ASCQ_CALIB_ERROR	0x7303
			/* Power calibration area error */

#define	ASCQ_PROG_AREA_FAIL	0x7304
			/* Program memory area update failure */

#define	ASCQ_PROG_AREA_FULL	0x7305
			/* Program memory area is full */


/* ---------------------------------------------------------------------- */

/*
 * READ / WRITE BUFFER Buffer Header:
 */
typedef struct all_buffer_header {
	u_char	reserved;		/* Reserved.			[0] */
	u_char	buffer_capacity2;	/* Buffer capacity (MSB).	[1] */
	u_char	buffer_capacity1;	/* Buffer capacity (MID).	[2] */
	u_char	buffer_capacity0;	/* Buffer capacity (LSB).	[3] */
} ALL_BUFFER_HEADER;

/* ---------------------------------------------------------------------- */

/* 
 * READ BUFFER Command
 */
typedef struct all_read_buffer_cdb {
	u_char	opcode;			/* Operation Code.		[0] */
	u_char	mode	: 3,		/* Mode field.			[1] */
			: 2,		/* Reserved.			    */
		lun	: 3;		/* Logical Unit Number.		    */
	u_char	id;			/* Buffer ID.			[2] */
	u_char	offset2;		/* Buffer offset (MSB).		[3] */
	u_char	offset1;		/* Buffer offset (MID).		[4] */
	u_char	offset0;		/* Buffer offset (LSB).		[5] */
	u_char	alloc_len2;		/* Allocation length (MSB).	[6] */
	u_char	alloc_len1;		/* Allocation length (MID).	[7] */
	u_char	alloc_len0;		/* Allocation length (LSB).	[8] */
	u_char	link	: 1,		/* Link.			[9] */
		flag	: 1,		/* Flag.			    */
		naca	: 1,		/* Normal ACA.			    */
			: 3,		/* Reserved.			    */
		vendor	: 2;		/* Vendor Unique.		    */
} ALL_READ_BUFFER_CDB;

#define ALL_READ_BUFFER_OP	0x3C

/*
 * Define READ BUFFER Mode Field Definitions:
 */
#define ALL_RDBUF_COMBINED_HEADER	0x00
#define ALL_RDBUF_VENDOR_SPECIFIC	0x01
#define ALL_RDBUF_READ_DATA		0x02
#define ALL_RDBUF_DESCRIPTOR		0x03

/* ---------------------------------------------------------------------- */

/* 
 * WRITE BUFFER Command
 */
typedef struct all_write_buffer_cdb {
	u_char	opcode;			/* Operation Code.		[0] */
	u_char	mode	: 3,		/* Mode field.			[1] */
			: 2,		/* Reserved.			    */
		lun	: 3;		/* Logical Unit Number.		    */
	u_char	id;			/* Buffer ID.			[2] */
	u_char	offset2;		/* Buffer offset (MSB).		[3] */
	u_char	offset1;		/* Buffer offset (MID).		[4] */
	u_char	offset0;		/* Buffer offset (LSB).		[5] */
	u_char	param_len2;		/* Parameter length (MSB).	[6] */
	u_char	param_len1;		/* Parameter length (MID).	[7] */
	u_char	param_len0;		/* Parameter length (LSB).	[8] */
	u_char	link	: 1,		/* Link.			[9] */
		flag	: 1,		/* Flag.			    */
		naca	: 1,		/* Normal ACA.			    */
			: 3,		/* Reserved.			    */
		vendor	: 2;		/* Vendor Unique.		    */
} ALL_WRITE_BUFFER_CDB;

#define ALL_WRITE_BUFFER_OP	0x3B

/*
 * Define WRITE BUFFER Mode Field Definitions:
 */
#define ALL_WTBUF_COMBINED_HEADER	0x00
#define ALL_WTBUF_VENDOR_SPECIFIC	0x01
#define ALL_WTBUF_WRITE_DATA		0x02
#define ALL_WTBUF_DOWNLOAD_MICROCODE	0x04
#define ALL_WTBUF_DOWNLOAD_SAVE		0x05
#define ALL_WTBUF_DOWNLOAD_WOFFSET	0x06
#define ALL_WTBUF_DOWNLOAD_SAVE_WOFFSET	0x07

/* ---------------------------------------------------------------------- */

/*
 * SCSI-3 Report Changeable Device Identifier command.
 */

typedef struct all_rpt_chgbl_devid {
	u_char	opcode;		/* opcode = 0xEB/0xEC		[0] */
	u_char		:8;     /* reserved			[1] */
	u_char		:8;     /* reserved			[2] */
	u_char		:8;     /* reserved			[2] */
	u_char		:8;     /* reserved			[3] */
	u_char		:8;     /* reserved			[4] */
	u_char		:8;     /* reserved			[5] */
	u_char	alloc_len1;	/* Allocation list length MSB	[6] */
	u_char	alloc_len0;	/* Allocation list length LSB	[7] */
	u_char	control;	/* Control byte			[8] */
}ALL_RPT_CHGBL_DEVID;

/*
 * Report Device Identifier opcode
 */
#define ALL_WR_CHGBL_DEVID		0xEB
#define ALL_RD_CHGBL_DEVID		0xEC


typedef struct all_rpt_chgbl_devid_data {
	u_char		:8;     /* reserved			[0] */
	u_char		:8;     /* reserved			[1] */
	u_char	valid:1,	/* response valid		[2] */
	             :7;	/* reserved 			[2] */
	u_char	ident_len;	/* # bytes in identifier 	[3] */
	u_char	ident[251];	/* identifier data */
	u_char		:8;     /* pad for alignment */
}ALL_RPT_CHGBL_DEVID_DATA;


/* ---------------------------------------------------------------------- */

#endif /* _SCSI_ALL_ */

