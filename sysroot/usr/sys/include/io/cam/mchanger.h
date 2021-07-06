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
 * @(#)$RCSfile: mchanger.h,v $ $Revision: 1.1.15.1 $ (DEC) $Date: 2002/01/24 18:41:05 $
 */
#if !defined(MCHANGER_INCLUDE)
#define MCHANGER_INCLUDE 1

/* DEVGETEEI ioctl, until it's included in deveei.h. */
#ifndef DEVGETEEI
#define DEVGETEEI	_IOWR('v', 101, DEV_EEI_STATUS)
#endif


/* Special ioctl's for SCSI MEDIA CHANGERS */
#define SCSI_INIT_ELEMENT	_IO('p', 128)
#define SCSI_POSITION_ELEMENT 	_IOW('p', 129, struct move_params)
#define SCSI_MOVE_MEDIUM 	_IOW('p', 130, struct move_params)
#define SCSI_EXCHANGE_MEDIUM 	_IOW('p', 131, struct move_params)
#define SCSI_READ_ELEMENT 	_IOW('p', 132, struct reades_params)
#define SCSI_RESERVE_ELEMENT 	_IOW('p', 133, struct reserve_params)
#define SCSI_RELEASE_ELEMENT 	_IOW('p', 134, struct release_params)
#define SCSI_LOG_SENSE		_IOW('p', 135, struct log_sense_params)
#define SCSI_REQUEST_VOLUME_ELEMENT_ADDRESS _IOW('p',136,struct voladdr_params)
#define SCSI_SEND_VOLUME_TAG	_IOW('p', 137, struct voltag_params)
/* !!!!BINCOMP The 136 in the following ioctl is a duplicate
 * and should be changed to 138, but it could break binary compatibility
 * so I'm leaving it for now. GAF.
 */
#define SCSI_INIT_ELEMENT_10	_IO('p', 136)
#define SCSI_MEDIA_CHANGER_OP	_IOW('p',139, struct mc_media_op)

/* mc_op codes for the SCSI_MEDIA_CHANGER_OP ioctl */
#define MC_INIT_ELEMENT				1
#define MC_INIT_ELEMENT_10			2
#define MC_POSITION_ELEMENT			3
#define MC_MOVE_MEDIUM				4
#define MC_EXCHANGE_MEDIUM			5
#define MC_READ_ELEMENT				6
#define MC_RESERVE_ELEMENT			7
#define MC_RELEASE_ELEMENT			9
#define MC_LOG_SENSE				10
#define MC_REQUEST_VOLUME_ELEMENT_ADDRESS	11
#define MC_SEND_VOLUME_TAG			12
#define MC_SET_TIMEOUTS				13
#define MC_GET_TIMEOUTS				14
#define MC_ALLOW_REMOVAL			15
#define MC_PREVENT_REMOVAL			16

struct mc_media_op {
	short mc_op;
	caddr_t mc_param;
};

/* Vendor Specific Extensions */
#define ODET_RDY_IOD  _IOW('p', 145, struct odetics_rdy_iod)

/* Generic SCSI passthrough ioctl */
#define SCSI_MC_GENERIC         _IOWR('p', 146, struct mc_generic)

/* ioctl to allow the user to tell us not to get
 *   a new path on each open.
 */
#define SCSI_MC_PATH_CONTROL	_IOW('p', 147, int)

#define MC_UNLOCK_CURRENT_PATH	0
#define MC_LOCK_CURRENT_PATH	1


/*
 * Medium Changer Element Type Codes:
 */
#define EDB_ALL			0
#define EDB_TRANSPORT		1
#define EDB_STORAGE		2
#define EDB_IMPORT_EXPORT	3
#define EDB_DATA_TRANSFER	4

/*
 * Defined Send Volume Action Codes:
 */
#define	TRANS_SRCH_ALL_DEFINDED_TAGS			0x0
#define	TRANS_SRCH_ONLY_PRIMARY_TAGS			0x1
#define	TRANS_SRCH_ONLY_ALTERNATE_TAGS			0x2

#define	TRANS_SRCH_ALL_DEFINDED_TAGS_IGNORE_SEQ		0x4
#define	TRANS_SRCH_ONLY_PRIMARY_TAGS_IGNORE_SEQ		0x5
#define	TRANS_SRCH_ONLY_ALTERNATE_TAGS_IGNORE_SEQ	0x6

#define	ASSERT_PRIMARY_TAG				0x8
#define ASSERT_ALTERNATE_TAG				0x9
#define REPLACE_PRIMARY_TAG				0xA
#define RELACE_ALTERNATE_TAG				0xB
#define UNDEFINE_PRIMARY_TAG				0xC
#define UNDEFINE_ALTERNATE_TAG				0xD

/*
 * POSITION, MOVE and EXCHANGE parameters:
 */
struct move_params {
	short	teaddr;		/* Transport Element Address */
	short	seaddr;		/* Source Element Address */
	short	fdeaddr;	/* First Dest. Address */
	short	sdeaddr;	/* Second Dest. Address */
        u_char	mp_inv1	: 1;	/* Invert Bit */
        u_char	mp_inv2 : 1;	/* Invert Bit */
        u_char		: 6;	/* Reserved */
};

/* READ ELEMENT STATUS parameters */
struct reades_params {
        u_char	etype:4;	/* Element Type Code		      */
        u_char	voltag:1;	/* Volume Tag			      */
        u_char		:3;	/* reserved			      */
        short	seaddr;		/* Starting Element Address           */
        short	numelm;		/* Number of Elements                 */
	caddr_t	readesp_addr;	/* Address to place data              */
	int 	readesp_length;	/* Length of readesp_addr  	      */
        u_char  segflg;          /* readesp_addr address segment       */
};

/* READ ELEMENT STATUS Data Header */
typedef struct reades_dthdr {
        u_char	feaddr1;	/* First Element Address (MSB)        */
        u_char	feaddr0;	/* First Element Address (LSB)        */
        u_char	numelm1;	/* Number of Elements (MSB)           */
        u_char	numelm0;	/* Number of Elements (LSB)           */
        u_char		:8;	/* Reserved			      */
        u_char	repcnt2;	/* Report Byte Count Available (MSB)  */
        u_char	repcnt1;	/* Report Byte Count Available        */
        u_char	repcnt0;	/* Report Count Available (LSB)	      */
} reades_dthdr_t;

/*
 * READ ELEMENT STATUS page header
 */
typedef struct reades_pghdr {
	u_char	etype;			/* Element Type Code		      */
        u_char		:6;	/* Reserved			      */
	u_char	avoltag:1;		/* Alternate Volume Tag		      */
	u_char	pvoltag:1;		/* Primary Volume Tag		      */
	u_char	declen1;		/* Element Descriptor Length	      */
	u_char	declen0;		/* Element Descriptor Length (LSB)    */
        u_char		:8;	/* Reserved			      */
	u_char	deccnt2;		/* Descriptor Byte Count Avail. (MSB) */
	u_char	deccnt1;		/* Descriptor Byte Count Avail.       */
	u_char	deccnt0;		/* Descriptor Byte Count Avail. (LSB) */
} reades_pghdr_t ;

/*
 * READ ELEMENT STATUS Element Descriptor Block (Generic Form!):
 */
struct reades_edb {
	u_char	eaddr1;		/* Element Address (MSB)              */
	u_char	eaddr0;		/* Element Address (LSB)              */
	u_char	full:1;		/* Full				      */
        u_char	impexp:1;	/* Import/Export		      */
        u_char	except:1;	/* Exception			      */
        u_char	access:1;	/* Access			      */
        u_char	exenab:1;	/* Export Enabled		      */
        u_char	imenab:1;	/* Import Enabled		      */
        u_char		:2;	/* Reserved			      */
        u_char		:8;	/* Reserved			      */
        u_char	asc;		/* Additional Sense Code	      */
        u_char	ascq;		/* Additional Sense Code Qualifier    */
        u_char	lun:3;		/* Logical Unit Number		      */
        u_char		:1;	/* Reserved			      */
        u_char	luvalid:1;	/* LUN Valid			      */
        u_char	idvalid:1;	/* SCSI ID Valid		      */
        u_char		:1;	/* Reserved			      */
        u_char	notbus:1;	/* Element not on Autochanger Bus     */
        u_char	scsiid;		/* SCS Bus Address		      */
        u_char	sublun;		/* Sub-Logical Unit Number	      */
        u_char		:6;	/* Reserved			      */
        u_char	invert:1;	/* Inverted			      */
        u_char	svalid:1;	/* Source Valid			      */
	u_char	seaddr1;	/* Source Element Address (MSB)       */
	u_char	seaddr0;	/* Source Element Address (LSB)       */
	u_char	pvinfo[36];	/* Primary Volume Tag Info            */
	u_char	avinfo[36];	/* Alternate Volume Tag Info          */
	u_char	rsvd[4];	/* Reserved                           */
};

/* ------------------------------------------------------------------------- */

/*
 * Element Assignment Address Information.
 */
typedef struct element_info {
	u_short  transport;		/* Transport Element Address.	  */
	u_short  num_transports;	/* Number of Transport Elements.  */
	u_short  first_storage;		/* First Storage Element Address. */
	u_short  num_storage;		/* Number of Storage Elements.    */
	u_short  import_export;		/* First Import Export Address.   */
	u_short  num_import_exports;	/* Number Import Export Elements. */
	u_short  first_data_trans;	/* First Data Transfer Address.   */
	u_short  num_data_trans;	/* Number Data Transfer Elements. */
} element_info_t;

#define ELEMENT_DESC_SIZE		16
#define ELEMENT_DESC_TAG_SIZE		88
/*
 * Data Transfer Element Descriptor:
 */
typedef struct data_transport_desc {
	u_char	element_addr[2];	/* Element address.	       [0-1] */
	u_char				/* 				 [2] */
		Full	: 1,		/* Transport is full.		(b0) */
			: 1,		/* Reserved.			(b1) */
		Except	: 1,		/* Exception (abnormal state).	(b2) */
		Access	: 1,		/* Access by MT allowed.	(b3) */
			: 4;		/* Reserved.			(b4) */
	u_char		: 8;		/* Reserved.			 [3] */
	u_char	asc;			/* Additional sense code	 [4] */
	u_char	ascq;			/*	...	and qualifier.	 [5] */
	u_char				/*				 [6] */
		lun	: 3,		/* Logical unit number.		(b0) */
			: 1,		/* Reserved.			(b3) */
		LUValid	: 1,		/* LUN field valid.		(b4) */
		IDValid	: 1,		/* SCSI Bus ID field valid.	(b5) */
			: 1,		/* Reserved.			(b6) */
		NotBus	: 1;		/* Library/changer on same bus.	(b7) */
	u_char	SCSI_BusId;		/* SCSI bus address.		 [7] */
	u_char	rsvd;			/* Reserved.		         [8] */
	u_char		: 6,		/* Reserved.			 [9] */
		Invert	: 1,		/* Media inverted.		(b6) */
		SValid	: 1;		/* Storage element valid.	(b7) */
	u_char	src_saddr[2];		/* Source storage address.   [10-11] */
	u_char	primary_tag[36];	/* Primary volume tag.	     [12-47] */
	u_char	alternate_tag[36];	/* Alternate volume tag.     [48-83] */
	u_char	rsvd1[4];		/* Reserved.		     [84-87] */
	/* --> Any additional fields are vendor unique! <--	     [88-nn] */
#if 0
	/*
	 * Without volume tag information, i.e. VolTag = 0 in CDB, the
	 * reserved and vendor bytes get moved up (combined for simplicity).
	 */
	u_char	rsvd1[4];		/* Reserved.		     [12-15] */
	/* --> Any additional fields are vendor unique! <--	     [16-nn] */
#endif
} data_transfer_desc_t;

/*
 * Import Export Element Descriptor:
 */
typedef struct import_export_desc {
	u_char	element_addr[2];	/* Element address.	       [0-1] */
	u_char				/* 				 [2] */
		Full	: 1,		/* Transport is full.		(b0) */
		ImpExp	: 1,		/* Import/export (1 = Operator)	(b1) */
		Except	: 1,		/* Exception (abnormal state).	(b2) */
		Access	: 1,		/* Access by MT allowed.	(b3) */
		ExEnab	: 1,		/* Export media from changer.	(b4) */
		InEnab	: 1,		/* Import media to changer.	(b4) */
			: 2;		/* Reserved.			(b6) */
	u_char		: 8;		/* Reserved.			 [3] */
	u_char	asc;			/* Additional sense code	 [4] */
	u_char	ascq;			/*	...	and qualifier.	 [5] */
	u_char	rsvd[3];		/* Reserved.		       [6-8] */
	u_char		: 6,		/* Reserved.			 [9] */
		Invert	: 1,		/* Media inverted.		(b6) */
		SValid	: 1;		/* Storage element valid.	(b7) */
	u_char	src_saddr[2];		/* Source storage address.   [10-11] */
	u_char	primary_tag[36];	/* Primary volume tag.	     [12-47] */
	u_char	alternate_tag[36];	/* Alternate volume tag.     [48-83] */
	u_char	rsvd1[4];		/* Reserved.		     [84-87] */
	/* --> Any additional fields are vendor unique! <--	     [88-nn] */
#if 0
	/*
	 * Without volume tag information, i.e. VolTag = 0 in CDB, the
	 * reserved and vendor bytes get moved up (combined for simplicity).
	 */
	u_char	rsvd1[4];		/* Reserved.		     [12-15] */
	/* --> Any additional fields are vendor unique! <--	     [16-nn] */
#endif
} import_export_desc_t;

/*
 * Medium Transport Element Descriptor:
 */
typedef struct transport_desc {
	u_char	element_addr[2];	/* Element address.	       [0-1] */
	u_char				/* 				 [2] */
		Full	: 1,		/* Transport is full.		(b0) */
			: 1,		/* Reserved.			(b1) */
		Except	: 1,		/* Exception (abnormal state).	(b2) */
			: 5;		/* Reserved.			(b3) */
	u_char		: 8;		/* Reserved.			 [3] */
	u_char	asc;			/* Additional sense code	 [4] */
	u_char	ascq;			/*	...	and qualifier.	 [5] */
	u_char	rsvd[3];		/* Reserved.		       [6-8] */
	u_char		: 6,		/* Reserved.			 [9] */
		Invert	: 1,		/* Media inverted.		(b6) */
		SValid	: 1;		/* Storage element valid.	(b7) */
	u_char	src_saddr[2];		/* Source storage address.   [10-11] */
	u_char	primary_tag[36];	/* Primary volume tag.	     [12-47] */
	u_char	alternate_tag[36];	/* Alternate volume tag.     [48-83] */
	u_char	rsvd1[4];		/* Reserved.		     [84-87] */
	/* --> Any additional fields are vendor unique! <--	     [88-nn] */
#if 0
	/*
	 * Without volume tag information, i.e. VolTag = 0 in CDB, the
	 * reserved and vendor bytes get moved up (combined for simplicity).
	 */
	u_char	rsvd1[4];		/* Reserved.		     [12-15] */
	/* --> Any additional fields are vendor unique! <--	     [16-nn] */
#endif
} transport_desc_t;

/*
 * Storage Element Descriptor:
 */
typedef struct storage_desc {
	u_char	element_addr[2];	/* Element address.	       [0-1] */
	u_char				/* 				 [2] */
		Full	: 1,		/* Transport is full.		(b0) */
			: 1,		/* Reserved.			(b1) */
		Except	: 1,		/* Exception (abnormal state).	(b2) */
		Access	: 1,		/* Access by MT allowed.	(b3) */
			: 4;		/* Reserved.			(b4) */
	u_char		: 8;		/* Reserved.			 [3] */
	u_char	asc;			/* Additional sense code	 [4] */
	u_char	ascq;			/*	...	and qualifier.	 [5] */
	u_char	rsvd[3];		/* Reserved.		       [6-8] */
	u_char		: 6,		/* Reserved.			 [9] */
		Invert	: 1,		/* Media inverted.		(b6) */
		SValid	: 1;		/* Storage element valid.	(b7) */
	u_char	src_saddr[2];		/* Source storage address.   [10-11] */
	u_char	primary_tag[36];	/* Primary volume tag.	     [12-47] */
	u_char	alternate_tag[36];	/* Alternate volume tag.     [48-83] */
	u_char	rsvd1[4];		/* Reserved.		     [84-87] */
	/* --> Any additional fields are vendor unique! <--	     [88-nn] */
#if 0
	/*
	 * Without volume tag information, i.e. VolTag = 0 in CDB, the
	 * reserved and vendor bytes get moved up (combined for simplicity).
	 */
	u_char	rsvd1[4];		/* Reserved.		     [12-15] */
	/* --> Any additional fields are vendor unique! <--	     [16-nn] */
#endif
} storage_desc_t;

/* ------------------------------------------------------------------------- */

/* RESERVE/RELEASE ELEMENT parameters */
struct reserve_params {
        u_char	resvid;		/* Reservation ID 		      */
	u_char	tparty_valid;
	short	tid;
	short	element_list_length;
	caddr_t element_list;
};

struct release_params {
        u_char	resvid;		/* Reservation ID 		      */
	u_char	all_elements;
	u_char	tparty_valid;
	short	tid;
};

/*  Element List Descriptor */
struct element_list_descriptor {
	u_char	:8;		/* Reserved			      */
	u_char	:8;		/* Reserved			      */
	u_char	numelm1;	/* Number of Elements (MSB)	      */
	u_char	numelm0;	/* Number of Elements (MSB)	      */
	u_char	elmaddr1;	/* Element Address (MSB)	      */
	u_char	elmaddr0;	/* Element Address (LSB)	      */
};

struct voladdr_params {
	u_char	etype;		/* Element Type Code	*/
	u_char	voltag;		/* Report Volume Tag Information (boolean) */
	short	eaddr;		/* Element Address	*/
        short	numelm;		/* Number of Elements	*/
	int 	length;		/* Length of buff addr	*/
	caddr_t	buf;		/* Buffer for volume address information */
};

struct voladdr_hdr_fmt {
	u_char	feaddr1;	/* First Element Address	(MSB) */
	u_char	feaddr0;	/* First Element Address	(LSB) */
        u_char	numelm1;	/* Number of Elements	*/
        u_char	numelm0;	/* Number of Elements	*/
	u_char	action :5;	/* Send Action Code	*/
	u_char	       :3;	/* Reserved */
        u_char	repcnt2;	/* Report Byte Count Available (MSB)  */
        u_char	repcnt1;	/* Report Byte Count Available        */
        u_char	repcnt0;	/* Report Count Available (LSB)	      */
};

struct volume_element_status_page {
	u_char etype;
	u_char	:6;
	u_char  avoltag:1;
	u_char	pvoltag:1;
	u_char  elength1;
	u_char  elength0;
	u_char	:8;
	u_char	bcount2;
	u_char	bcount1;
	u_char	bcount0;
};

struct volume_storage_descriptor {
	u_char eaddr1;
	u_char eaddr0;
	u_char full:1;
	u_char rsvd:1;
	u_char excpt:1;
	u_char access:1;
	u_char :4;
	u_char :8;
	u_char asc;
	u_char ascq;
	u_char :8;
	u_char :8;
	u_char :8;
	u_char :6;
	u_char invert:1;
	u_char svalid:1;
	u_char seaddr1;
	u_char seaddr0;
	u_char pvoldata[36];
	u_char reserved[4];
};

struct voltag_params {
	u_char	etype;		/* Element Type Code	*/
	u_char	action;		/* Send Action Code	*/
	short	eaddr;		/* Element Address	*/
	short	plength;	/* Parameter List Length */
	caddr_t buf;		/* Buffer for tag parameter information */
};

struct voltag_param_fmt {
	u_char vol_id[32];
	short reserved0;
	short min_vol_seq;
	short reserved1;
	short max_vol_seq;
};

/* !!!! GAF The following structure should be modified
 * as shown in the #if in a future major version of Tru64.
 * This can only be changed at a major version because it
 * will break source code compatibility for any application using it.
 */

#if 0
 /* Structure that provides info to build a LOG SENSE CDB */
struct log_sense_info {
	u_char	pgcode;		/* The page to send/get   */
	int	length; 	/* The length to send/get  */
	int	param_ptr;	/* Parameter code to start with */
	caddr_t	addr;		/* Address of data buffer */
};

struct log_sense_param_hdr {
	u_char	param_code1;	/* The parameter code (MSB) */
      	u_char	param_code0;	/* The parameter code (LSB) */
        u_char	param_cont;	/* Parameter control byte   */
	u_char	param_len;  	/* The total length of parameter - 3  */
};

struct log_sense_pg_hdr {
	u_char pgcode;	/* Page Number */
	u_char mbz: 8;	/* Reserved (0)	*/
	u_char pg_len1;	/* Number of Bytes that follow (MSB)	*/
	u_char pg_len0;	/* Number of Bytes that follow (LSB)	*/
};

#else
struct log_sense_params {
	u_char	pgcode;  /* The pages to send/get   */
	int	length;  /* The length to send/get  */
	caddr_t	param;
	caddr_t	addr;	/* Address of data (pages)  */
};

struct log_sense_header {
	u_char pgnum;	/* Page Number */
	u_char mbz: 8;	/* Reserved (0)	*/
	u_char bytes1;	/* Number of Bytes that follow (MSB)	*/
	u_char bytes0;	/* Number of Bytes that follow (LSB)	*/
};
#endif

struct element_addr_page {
	u_char pgcode : 6;
	u_char  : 1;
	u_char ps : 1;
	u_char pglength;
	u_char transport_addr1;
	u_char transport_addr0;
	u_char transport_num1;
	u_char transport_num0;
	u_char storage_addr1;
	u_char storage_addr0;
	u_char storage_num1;
	u_char storage_num0;
	u_char import_export_addr1;
	u_char import_export_addr0;
	u_char import_export_num1;
	u_char import_export_num0;
	u_char data_transfer_addr1;
	u_char data_transfer_addr0;
	u_char data_transfer_num1;
	u_char data_transfer_num0;
	u_char :8;
	u_char :8;
};

struct device_capabilities_page {
	u_char pagecode :6,
		: 1,
		ps : 1;
	u_char	plength;
	u_char	stor_mt :1, stor_st :1, stor_ie	:1, stor_dt :1, :4;
	u_char	:8;
	u_char	mt_move_mt :1, mt_move_st :1, mt_move_ie :1, mt_move_dt :1, :4;
	u_char	st_move_mt :1, st_move_st :1, st_move_ie :1, st_move_dt :1, :4;
	u_char	ie_move_mt :1, ie_move_st :1, ie_move_ie :1, ie_move_dt :1, :4;
	u_char	dt_move_mt :1, dt_move_st :1, dt_move_ie :1, dt_move_dt :1, :4;
	u_char	:8;
	u_char	:8;
	u_char	:8;
	u_char	:8;
	u_char	mt_exch_mt :1, mt_exch_st :1, mt_exch_ie :1, mt_exch_dt :1, :4;
	u_char	st_exch_mt :1, st_exch_st :1, st_exch_ie :1, st_exch_dt :1, :4;
	u_char	ie_exch_mt :1, ie_exch_st :1, ie_exch_ie :1, ie_exch_dt :1, :4;
	u_char	dt_exch_mt :1, dt_exch_st :1, dt_exch_ie :1, dt_exch_dt :1, :4;
	};

/*
 * Media changer timeout table.
 */
struct changer_timeouts {
	u_long ct_init_tmo;		/* Initialize element timeout */
	u_long ct_read_status_tmo;	/* Read element status timeout */
	u_long ct_move_tmo;		/* Move medium timeout */
	u_long ct_exchange_tmo;		/* Exchange medium timeout */
	u_long ct_position_tmo;		/* Position to element timeout */
	u_long ct_prevent_allow_tmo;	/* Prevent/allow timeout */
	u_long ct_reserve_tmo;		/* Reserve timeout */
	u_long ct_release_tmo;		/* Release timeout */
	u_long ct_request_volume_tmo;	/* Request volume element address */
	u_long ct_send_volume_tmo;	/* Send volume tag timeout */
};

#ifdef KERNEL
extern struct changer_timeouts changer_default_timeouts;
extern struct changer_timeouts exb120_timeouts;
extern struct changer_timeouts magnum_timeouts;
#endif

struct	changer_range		/* for generic geometry */
{
	short ports;
	short drives;
	short slots;
	short transports;
};

struct	changer_move		/* for generic transfer */
{
	short drive;		/* port or drive number (0=port) */
	short volume;		/* volume selector (slot*2+side) */
};

struct	changer_state		/* for generic status */
{
	char mode;		/* over-loaded with first 8 */
				/* bits of access structure */
	unsigned type:7,	/* 0=device, 1=storage slot */
	 	 side:1;	/* orientation in storage */
	short slot;		/* slot or device(0=port) */
};

struct access_state		/* status bits & codes */
{
	unsigned char :2,
	in:1,		/* import enabled */
	out:1,		/* export enabled */
	real:1,		/* element exists */
	fault:1,	/* in fault state */
	entry:1,	/* in entry state */
	full:1,		/* element filled */
	:8,
	code:8,		/* add sense code */
	more:8;		/* code qualifier */
};

/*
 * Fields marked with @ need to be filled in by caller
 * Fields marked with % will be filled in by driver.
 *
 * After the call, your data buffer will contain any data received from
 * the device and your sense_data buffer will contain SENSE DATA
 * bytes if the cdb_status field contains a 0x02 (CHECK_CONDITION).
 * For SCSI commands that transfer no data (e.g. TEST UNIT READY),
 * set flags = 0x00 and data_size = 0;
  * This interface can pass through any SCSI command except the following:
 * REQUEST SENSE
 * Further command restrictions may be imposed in the future,
 * if they present problems for the other drivers.
 */
struct mc_generic {
  unsigned int  flags;		/* See MC_GEN_PASS_XX defs below @   */
  void          *cdb;           /* SCSI command data block[or TM func] @   */
  unsigned int  cdb_size;       /* CDB size-  6,10,12 or 16       @   */
  unsigned int  cdb_status;     /* command completion SCSI status   % */
  void          *data;          /* user data buffer               @   */
  unsigned int  data_size;      /* size of user data buffer       @   */
  unsigned int  data_xfer;      /* amount of data transferred       % */
  void          *sense_data;    /* buffer to receive sense data   @   */
  unsigned int  sense_size;     /* size of sense buffer           @   */
  unsigned int  sense_xfer;     /* amount of sense data returned    % */
  unsigned int  timeout;        /* command timeout in seconds     @   */
  unsigned int  cam_status;     /* CAM status from CAM layer        % */
};

#define	MC_GEN_PASS_DIRMASK	0x01
#define	MC_GEN_PASS_READ	0
#define	MC_GEN_PASS_WRITE	1

/* Setting this bit in the flags field of the mc_generic struct
 * changes the meaning of the cdb field to one of the
 * Task Management Functions below.
 */
#define	MC_GEN_PASS_TMF_MODE	0x04

#define MC_GEN_TARGET_RESET_CURRENT_PATH	0x10
#define MC_GEN_TARGET_RESET_ALL_PATHS		0x11
#define MC_GEN_LUN_RESET_CURRENT_PATH		0x20
#define MC_GEN_LUN_RESET_ALL_PATHS		0x21

/* Please refrain from using the following defines in new code
 * they are only left here for backward compatibility.
 */
#define	MC_G_WRITE	MC_GEN_PASS_WRITE
#define	MC_G_READ	MC_GEN_PASS_READ
#define MC_G_CAM_STATUS 2       /* Not used. Left here for source compat. */

/* vendor specific */

struct odetics_rdy_iod
{
	short port_address;
};

#endif /* !defined(MCHANGER_INCLUDE) */

