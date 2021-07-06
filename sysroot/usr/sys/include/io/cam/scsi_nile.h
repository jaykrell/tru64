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
 * @(#)$RCSfile: scsi_nile.h,v $ $Revision: 1.1.6.2 $ (DEC) $Date: 2002/01/08 21:48:41 $
 */
#ifndef _SCSI_NILE_
#define _SCSI_NILE_

/* ---------------------------------------------------------------------- */

/* scsi_nile.h

   Contains all the structures and defines for the Nile procotol
   used by the Proliant Starlight/Starbright Storage Shelf.
*/

/* ---------------------------------------------------------------------- */

/* 
 * The Receive CDB:
 */
typedef struct nile_receive_cdb {
	u_char	opcode;			/* Operation Code.		[0] */
	u_char		: 5,		/* Reserved.			[1] */
		lun	: 3;		/* Logical Unit Number.		    */
	u_char		: 8;		/* Reserved.			[2] */
	u_char	page_code;		/* Page code.			[3] */
	u_char	alloc_length;		/* Allocation Length.		[4] */
	u_char	link	: 1,		/* Link.			[5] */
		flag	: 1,		/* Flag.			    */
			: 4,		/* Reserved.			    */
		vendor	: 2;		/* Vendor Unique.		    */
} nile_receive_cdb_t;

/*
 * The RECEIVE Opcode:
 */
#define NILE_RECEIVE_OP	0x08

/* ---------------------------------------------------------------------- */

/* 
 * The Send CDB:
 */
typedef struct nile_send_cdb {
	u_char	opcode;			/* Operation Code.		[0] */
	u_char		: 5,		/* Reserved.			[1] */
		lun	: 3;		/* Logical Unit Number.		    */
	u_char		: 8;		/* Reserved.			[2] */
	u_char	page_code;		/* Page code.			[3] */
	u_char	alloc_length;		/* Allocation Length.		[4] */
	u_char	link	: 1,		/* Link.			[5] */
		flag	: 1,		/* Flag.			    */
			: 4,		/* Reserved.			    */
		vendor	: 2;		/* Vendor Unique.		    */
} nile_send_cdb_t;

/*
 * The SEND Opcode:
 */
#define NILE_SEND_OP	0x0a

/* ---------------------------------------------------------------------- */

/*
 * Supported Page Codes:
 */
#define NILE_DEVICE_PAGE_START	  0x00	/* Start of device slot pages.	*/
#define NILE_DEVICE_PAGE_END	  0x7F	/* End of device slot pages.	*/
#define NILE_GLOBAL_INDICTOR_PAGE 0x80	/* The Global Indicator Page.	*/
#define NILE_ALARM_PAGE		  0x81	/* The Alarm Page.		*/
#define NILE_FAULT_SIMULATOR_PAGE 0x88	/* The Fault Simulator Page.	*/
#define NILE_I2C_PASSTHRU_PAGE	  0x90	/* The I2C Pass-though Page.	*/
#define NILE_CHASSIS_SERIAL_PAGE  0x93	/* The Chassis Serial Number.	*/
#define NILE_LCD_DISPLAY_PAGE	  0x98	/* The LCD Display Text Page.	*/
#define NILE_MSG_BUT_STATUS_PAGE  0x99	/* Message & Button Status Page	*/
#define NILE_MESSAGE_DELETE_PAGE  0x99	/* Message Delete Page (WRITE).	*/

/*
 * Common Page Header:
 */
typedef struct nile_page_header {
	u_char	page_code;		/* The page code.		*/
	u_char	page_length;		/* The page length (n - 1).	*/
} nile_page_format_t;

/*
 * Alarm Page:
 */
typedef struct nile_alarm_page {
	struct nile_page_header phdr;	/* The page header.		*/
	u_char	BitAlarm	: 1,	/* Set if bit alarms are set.	*/
		DltAlarm	: 1,	/* Set if delta alarms set.	*/
				: 5,	/* Reserved.			*/
		Alarm		: 1;	/* One of Alarm bits is set.	*/
	u_char	Fan		: 1,	/* Fan failure.			*/
		Temp		: 1,	/* One of Temp Status bits set.	*/
				: 1,	/* Reserved.			*/
		Pwr		: 1,	/* Redundant power supply fault	*/
				: 2,	/* Reserved.			*/
		SE		: 1,	/* Single-Ended mode.		*/
				: 1;	/* Reserved.			*/
	u_char	FanDlt		: 1,	/* Signifies fan bit change.	*/
		TempDlt		: 1,	/* Signifies temp bit change.	*/
				: 1,	/* Reserved.			*/
		PwrDlt		: 1,	/* Signifies power bit change.	*/
				: 2,	/* Reserved Delta.		*/
		SEDlt		: 1,	/* Signifies SE bit change.	*/
		ButtonDlt	: 1;	/* Signifies button bit change.	*/
	u_char	Temp0		: 1,	/* Warning over temp condition.	*/
		Temp1		: 1,	/* Critical over temp condition	*/
				: 6;	/* Reserved.			*/
	u_char			: 8;	/* Reserved Status.		*/
	u_char	FanV		: 1,	/* Fan sense hardware present.	*/
		TempV		: 1,	/* Temp sense hardware present.	*/
				: 1,	/* Reserved.			*/
		PwrV		: 1,	/* Redundant power supp present	*/
				: 2,	/* Reserved Valid Bits.		*/
		SEV		: 1,	/* Single-end hardware present.	*/
		ButtonV		: 1;	/* LCD Module is installed.	*/
} nile_alarm_page_t;

/*
 * Fault Simulator Page:
 */
typedef struct nile_fault_simulator_page {
	struct nile_page_header phdr;	/* The page header.		*/
	u_char			: 8;	/* Reserved.			*/
	u_char	Fan		: 1,	/* Simulate a Fan failure.	*/
		Temp		: 1,	/* Simulate over temp condition	*/
				: 1,	/* Reserved.			*/
		Pwr		: 1,	/* Redundant power supply fail.	*/
				: 4;	/* Reserved Bit Alarms.		*/
	u_char			: 8;	/* Reserved.			*/
	u_char	Temp0		: 1,	/* Warning over temp condition.	*/
		Temp1		: 1,	/* Critical over temp condition	*/
				: 6;	/* Reserved Temp Status.	*/
	u_char	reserved[2];		/* Reserved.			*/
} nile_fault_simulator_page_t;

/*
 * Chassis Serial Number Page:
 */
typedef struct nile_chassis_serial_page {
	struct nile_page_header phdr;	/* The page header.		*/
	u_char	chassis_serial[24];	/* Chassis Serial Number.	*/
	u_char	reserved[6];		/* Reserved.			*/
} nile_chassis_serial_page_t;

/*
 * Notes:
 *	The OwnerId must be a value between 2 - 0xFE.
 *	Owner ID's 0 and 1 are reserved for backplane cintrollers.
 *	Tags 0 - 0x0F are reserved for backplane controllers.
 *	Priorities are 0 - 255 with 255 being the highest.
 *
 *	Note: The default "Compaq StorageWorks Enclosure" uses
 * priority 1, so priority 0 is not very useful :-)
 */
/*
 * LCD Display Text Page:
 */
typedef struct nile_display_text_page {
	struct nile_page_header phdr;	/* The page header.		*/
	u_char	OwnerID;		/* Message owner ID.		*/
	u_char	MessageTag;		/* Message tag (0-0xf reserved)	*/
	u_char	MessagePriority;	/* Message priority.		*/
	u_char	MessageText[79];	/* Message text (up to 79).	*/
} nile_display_text_page_t;

#define NILE_DISPLAY_HDR_LEN	(sizeof(nile_page_format_t) + 3)

/*
 * Message and Button Status (READ):
 */
typedef struct nile_message_status_page {
	struct nile_page_header phdr;	/* The page header.		*/
	u_char	OwnerID;		/* Message owner ID.		*/
	u_char	MessageTag;		/* The message tag.		*/
	u_char	MessagePriority;	/* The message priority.	*/
	u_char	ButtonPressed;		/* Button pressed indicator.	*/
	u_char	ButtonReleased;		/* Button released indicator.	*/
	u_char	ButtonHeldDown;		/* Button heklp down indicator.	*/
	u_char	OwnerIDQueued;		/* Owner ID in queue.		*/
	u_char	MessageTagQueued;	/* The message tag in queue.	*/
	u_char	MessagePriorityQueued;	/* The message priority queued.	*/
} nile_message_status_page_t;

/*
 * Message Delete (WRITE):
 */
typedef struct nile_message_delete_page {
	struct nile_page_header phdr;	/* The page header.		*/
	u_char	OwnerID;		/* Message owner ID.		*/
	u_char	MessageTag;		/* The message tag.		*/
	u_char	reserved[4];		/* Reserved.			*/
} nile_message_delete_page_t;

/*
 * Device Slot Page:
 */
typedef struct nile_device_slot_page {
	struct nile_page_header phdr;	/* The page header.		*/
	u_char	Installed	: 1,	/* Device tray installed.	*/
		Delta		: 1,	/* Signifies Installed changed.	*/
		Wide		: 1,	/* Wide device tray installed.	*/
				: 4,	/* Reserved.			*/
		NotSup		: 1;	/* Device slot not present.	*/
	u_char	ActivityIndicator;	/* Activity indicator value.	*/
	u_char	OnlineIndicator;	/* On-line indicator value.	*/
	u_char	ServiceIndicator;	/* Service indicator value.	*/
	u_char	reserved[2];		/* Reserved.			*/
} nile_device_slot_page_t;

#endif /* _SCSI_NILE_ */
