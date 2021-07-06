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
 * @(#)$RCSfile: scsi_changer.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1998/10/14 16:55:35 $
 */
#if !defined(SCSI_CHANGER_INCLUDE)
#define	SCSI_CHANGER_INCLUDE	1

/*
 * Media Changer Command Parameter Definitions:
 */
#define CHGR_DEFAULT_TIMEOUT	10	/* Default command timeout.	*/

/*
 * Prevent/Allow Medium Removal Parameters:
 */
#define CHGR_ALLOW_REMOVAL	0	/* Allow medium removal.	*/
#define CHGR_PREVENT_REMOVAL	1	/* Prevent medium removal.	*/

/*
 * Mode Pages for Medium Changer Devices:
 */
#define CHGR_DEVICE_CAP_PG 0x1f
#define CHGR_ELEMENT_ADDR_PG 0x1d
#define CHGR_TRANSPORT_GEOM_PG 0x1e

/*
 * SCSI Operation Codes for Medium-Changer Devices.
 */
#define CHGR_CHANGE_DEFINITION_OP		0x40
#define CHGR_EXCHANGE_MEDIUM_OP			0xA6
#define CHGR_INITIALIZE_ELEMENT_STATUS_OP	0x07
#define CHGR_INQUIRY_OP				0x12
#define CHGR_LOG_SELECT_OP			0x4C
#define CHGR_LOG_SENSE_OP			0x4D
#define CHGR_MODE_SELECT_6_OP			0x15
#define CHGR_MODE_SELECT_10_OP			0x55
#define CHGR_MODE_SENSE_6_OP			0x1A
#define CHGR_MODE_SENSE_10_OP			0x5A
#define CHGR_MOVE_MEDIUM_OP			0xA5
#define CHGR_POSITION_TO_ELEMENT_OP		0x2B
#define CHGR_PREVENT_ALLOW_REMOVAL_OP		0x1E
#define CHGR_READ_BUFFER_OP			0x3C
#define CHGR_READ_ELEMENT_STATUS_OP		0xB8
#define CHGR_RECEIVE_DIAGNOSTIC_OP		0x1C
#define CHGR_RELEASE_OP				0x17
#define CHGR_REQUEST_VOLUME_ELEMENT_ADDRESS_OP	0xB5
#define CHGR_REQUEST_SENSE_OP			0x03
#define CHGR_RESERVE_OP				0x16
#define CHGR_REZERO_UNIT_OP			0x01
#define CHGR_SEND_DIAGNOSTIC_OP			0x1D
#define CHGR_SEND_VOLUME_TAG_OP			0xB6
#define CHGR_TEST_UNIT_READY_OP			0x00
#define CHGR_WRITE_BUFFER_OP			0x3B

/*  Media Changer Commands */

/* INITIALIZE ELEMENT STATUS Command */
struct InitElementStatus_CDB {
	u_char	opcode;		/* Operation Code.		[0] */
	u_char		:5;	/* Reserved			      */
	u_char	lun:3;		/* Logical Unit Number		      */
	u_char		:8;	/* Reserved			      */
	u_char		:8;	/* Reserved			      */
	u_char		:8;	/* Reserved			      */
	u_char	link:1;		/* Link				      */
	u_char	flag:1;		/* Flag				      */
	u_char		:4;	/* Reserved			      */
	u_char	mbz:2;		/* Must be Zero			      */
};

/* POSITION TO ELEMENT Command */
struct PositionToElement_CDB {
	u_char	opcode;		/* Operation Code.		[0] */
	u_char		:5;	/* Reserved			      */
	u_char	lun:3;		/* Logical Unit Number		      */
	u_char	teaddr1;	/* Transport Element Address (MSB)    */
	u_char	teaddr0;	/* Transport Element Address (LSB)    */
	u_char	deaddr1;	/* Destination Element Address (MSB)  */
	u_char	deaddr0;	/* Destination Element Address (LSB)  */
	u_char	rsvd1[2];	/* Reserved			      */
	u_char	invert:1;	/* Invert			      */
	u_char		:7;	/* Reserved			      */
	u_char	link:1;		/* Link				      */
	u_char	flag:1;		/* Flag				      */
	u_char		:4;	/* Reserved			      */
	u_char	mbz:2;		/* Must be Zero			      */
};

/* MOVE MEDIUM Command */
struct MoveMedium_CDB {
	u_char	opcode;		/* Operation Code.		[0] */
	u_char		:5;	/* Reserved			      */
	u_char	lun:3;		/* Logical Unit Number		      */
	u_char	teaddr1;	/* Transport Element Address (MSB)    */
	u_char	teaddr0;	/* Transport Element Address (LSB)    */
	u_char	seaddr1;	/* Source Element Address (MSB)       */
	u_char	seaddr0;	/* Source Element Address (LSB)       */
	u_char	deaddr1;	/* Destination Element Address (MSB)  */
	u_char	deaddr0;	/* Destination Element Address (LSB)  */
	u_char	rsvd1[2];	/* Reserved			      */
	u_char	invert:1;	/* Invert			      */
	u_char		:7;	/* Reserved			      */
	u_char	link:1;		/* Link				      */
	u_char	flag:1;		/* Flag				      */
	u_char		:4;	/* Reserved			      */
	u_char	mbz:2;		/* Must be Zero			      */
};

/* READ ELEMENT STATUS Command */
struct ReadElementStatus_CDB {
	u_char	opcode;		/* Operation Code.		[0] */
	u_char	etype:4;	/* Element Type Code		      */
	u_char	voltag:1;	/* Volume Tag			      */
	u_char	lun:3;		/* Logical Unit Number		      */
	u_char	seaddr1;	/* Starting Element Address (MSB)     */
	u_char	seaddr0;	/* Starting Element Address (LSB)     */
	u_char	numelm1;	/* Number of Elements (MSB)           */
	u_char	numelm0;	/* Number of Elements (LSB)           */
	u_char		:8;	/* Reserved			      */
	u_char	alclen2;	/* Allocation Length (MSB)	      */
	u_char	alclen1;	/* Allocation Length 		      */
	u_char	alclen0;	/* Allocation Length (LSB)	      */
	u_char		:8;	/* Reserved			      */
	u_char	link:1;		/* Link				      */
	u_char	flag:1;		/* Flag				      */
	u_char		:4;	/* Reserved			      */
	u_char	mbz:2;		/* Must be Zero			      */
};

/* EXCHANGE MEDIUM Command */
struct ExchangeMedium_CDB {
	u_char	opcode;		/* Operation Code.		[0] */
	u_char		:5;	/* Reserved			      */
	u_char	lun:3;		/* Logical Unit Number		      */
	u_char	teaddr1;	/* Transport Element Address (MSB)    */
	u_char	teaddr0;	/* Transport Element Address (LSB)    */
	u_char	seaddr1;	/* Source Element Address (MSB)       */
	u_char	seaddr0;	/* Source Element Address (LSB)       */
	u_char	fdeaddr1;	/* First Destination Address (MSB)    */
	u_char	fdeaddr0;	/* First Destination Address (LSB)    */
	u_char	sdeaddr1;	/* Second Destination Address (MSB)   */
	u_char	sdeaddr0;	/* Second Destination Address (LSB)   */
	u_char	inv1:1;	        /* Invert First Destination	      */
	u_char	inv2:1;	        /* Invert Second Destination	      */
	u_char		:6;	/* Reserved			      */
	u_char	link:1;		/* Link				      */
	u_char	flag:1;		/* Flag				      */
	u_char		:4;	/* Reserved			      */
	u_char	mbz:2;		/* Must be Zero			      */
};

/* RESERVE UNIT Command */
struct ReserveElement_CDB {
	u_char	opcode;		/* Operation Code.		[0] */
	u_char	element:1;	/* Element Reservation/Release	      */
	u_char	thrdpdev:3;	/* Third Party Device		      */
	u_char	thrdp:1;	/* Third Party			      */
	u_char	lun:3;		/* Logical Unit Number		      */
	u_char	resvid;		/* Reservation ID		      */
	u_char	ellen1;		/* Element List Length (MSB)	      */
	u_char	ellen0;		/* Element List Length (LSB)	      */
	u_char		:8;	/* Reserved			      */
};

/* RELEASE UNIT Command */
struct ReleaseElement_CDB {
	u_char	opcode;		/* Operation Code.		[0] */
	u_char	element:1;	/* Element Reservation/Release	      */
	u_char	thrdpdev:3;	/* Third Party Device		      */
	u_char	thrdp:1;	/* Third Party			      */
	u_char	lun:3;		/* Logical Unit Number		      */
	u_char	resvid;		/* Reservation ID		      */
	u_char  	:8;	/* Reserved			      */
	u_char  	:8;	/* Reserved			      */
	u_char		:8;	/* Must be Zero			      */
};

/* Request Volume Element Address Command */
struct RequestVolumeElementAddress_CDB {
	u_char	opcode;		/* Operation Code.		[0] */
	u_char	etype:4;	/* Element Type			*/
	u_char	voltag:1;	/* Volume Tag			      */
	u_char	lun:3;		/* Logical Unit Number		      */
	u_char	eaddr1;		/* Element Address (MSB)       */
	u_char	eaddr0;		/* Element Address (LSB)       */
	u_char	numelm1;	/* Number of Elements (MSB)           */
	u_char	numelm0;	/* Number of Elements (LSB)           */
	u_char  	:8;	/* Reserved			      */
	u_char	alclen2;	/* Allocation Length (MSB)	      */
	u_char	alclen1;	/* Allocation Length 		      */
	u_char	alclen0;	/* Allocation Length (LSB)	      */
	u_char  	:8;	/* Reserved			      */
	u_char		:8;	/* Must be Zero			      */
};

/* Send Volume Tag Command */
struct SendVolumeTag_CDB {
	u_char	opcode;		/* Operation Code.		[0] */
	u_char	etype:4;	/* Element Type			*/
	u_char  	:1;	/* Reserved			      */
	u_char	lun:3;		/* Logical Unit Number		      */
	u_char	eaddr1;		/* Element Address (MSB)       */
	u_char	eaddr0;		/* Element Address (LSB)       */
	u_char  	:8;	/* Reserved			      */
	u_char	action :5;	/* Send Action Code		*/
	u_char		:3;	/* Reserved			      */
	u_char  	:8;	/* Reserved			      */
	u_char  	:8;	/* Reserved			      */
	u_char	plength1;	/* Parameter List Length (MSB)	*/
	u_char	plength0;	/* Parameter List Length (LSB)	*/
	u_char  	:8;	/* Reserved			      */
	u_char		:8;	/* Must be Zero			      */
};

/* LOG SENSE */
struct LogSense_CDB {
	u_char	opcode;		/* Operation Code.		[0] */
	u_char	    : 5;	/* Reserved (0)			*/
	u_char	lun : 3;	/* Logical Unit Number		*/
	u_char pgcode:6;	/* Page Code			*/
	u_char	: 2;		/* Reserved (0)			*/
	u_char	: 8;		/* Reserved (0)			*/
	u_char	: 8;		/* Reserved (0)			*/
	u_char paramp1;		/* Parameter Pointer (MSB)	*/
	u_char paramp0;		/* Parameter Pointer (LSB)	*/
	u_char alloclen1;	/* Allocation Lenght (MSB)	*/
	u_char alloclen0;	/* Allocation Lenght (LSB)	*/
	u_char	:8;		/* Must be Zero			*/
};

	/* Vendor Specific CDBs */

/* INITIALIZE ELEMENT STATUS 10 Command */
struct InitElementStatus_10_CDB {
	u_char	opcode;		/* Operation Code.		[0] */
	u_char  range   :1;	/* Address field type		      */
	u_char		:4;	/* Reserved			      */
	u_char	lun:3;		/* Logical Unit Number		      */
	u_char  eaddr_lsb;
	u_char	eaddr_msb;
	u_char		:8;	/* Reserved			      */
	u_char		:8;	/* Reserved			      */
	u_char  elements_lsb;
	u_char	elements_msb;
	u_char		:8;	/* Reserved			      */
	u_char	link:1;		/* Link				      */
	u_char	flag:1;		/* Flag				      */
	u_char		:4;	/* Reserved			      */
	u_char	mbz:2;		/* Must be Zero			      */
};

struct OdeticsRdyIod_CDB {
	u_char	opcode;		/* Operation Code.		[0] */
	u_char	    : 5;	/* Reserved (0)			*/
	u_char	lun : 3;	/* Logical Unit Number		*/
	u_char	eaddr1;		/* Element Address (MSB)       */
	u_char	eaddr0;		/* Element Address (LSB)       */
	u_char  	:8;	/* Reserved			      */
	u_char		:8;	/* Must be Zero			      */
};

#define CHGR_ODETICS_RDY_IOD_OP	0xDE

#endif /* !defined(SCSI_CHANGER_INCLUDE) */
