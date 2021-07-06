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
 * @(#)$RCSfile: cam.h,v $ $Revision: 1.1.30.2 $ (DEC) $Date: 2000/07/19 20:56:15 $
 */
#ifndef	_CAM_INCL_
#define	_CAM_INCL_

#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------------------------------------------- */

/* General allocation length defines for the CCB structures. */

#define	IOCDBLEN	16	/* Space for the CDB bytes/pointer */
#define	VUHBA		12	/* Vendor Unique HBA length */
#define	SIM_ID		16	/* ASCII string	len for	SIM ID */
#define	HBA_ID		16	/* ASCII string	len for	HBA ID */
#define	SIM_PRIV	56	/* Length of SIM private data area */

/* Structure definitions for the CAM control blocks, CCB's for the
subsystem. */

/*
 * CAM-2 ccb header definition
 *
 * !! Keep cam_flags at	the same offset	in CAM-2 and CAM-3 !!
 * ==========================================================
 */
typedef	struct ccb_header
{
    struct ccb_header *my_addr;	/* The address of this CCB */
    u_short cam_ccb_len;	/* Length of the entire	CCB */
    u_char cam_func_code;	/* XPT function	code */
    u_char cam_status;		/* Returned CAM	subsystem status */
    u_char cam_hrsvd0;		/* Reserved field, for alignment */
    u_char cam_path_id;		/* Path	ID for the request */
    u_char cam_target_id;	/* Target device ID */
    u_char cam_target_lun;	/* Target LUN number */
    U32	cam_flags;		/* Flags for operation of the subsystem	*/
} CCB_HEADER;

/*
 * Union definition for	the CDB	space in the SCSI I/O request CCB
 */
typedef	union cdb_un
{
    u_char *cam_cdb_ptr;		/* Pointer to the CDB bytes to send */
    u_char cam_cdb_bytes[ IOCDBLEN ];	/* Area	for the	CDB to send */
} CDB_UN;

/*
 * Common SCSI functions.
 * Alignment compatible	with CAM-3 protocol
 * ========================================
 */

typedef	struct ccb_scsiio
{
    CCB_HEADER cam_ch;		/* Header information fields */
    u_char *cam_pdrv_ptr;	/* Ptr used by the Peripheral driver */
    CCB_HEADER *cam_next_ccb;	/* Ptr to the next CCB for action */
    u_char *cam_req_map;	/* Ptr for mapping info	on the Req. */
    void (*cam_cbfcnp)();	/* Callback on completion function */
    u_char *cam_data_ptr;	/* Pointer to the data buf/SG list */
    U32	cam_dxfer_len;		/* Data	xfer length */
    u_char *cam_sense_ptr;	/* Pointer to the sense	data buffer */
    u_char cam_sense_len;	/* Num of bytes	in the Autosense buf */
    u_char cam_cdb_len;		/* Number of bytes for the CDB */
    u_short cam_sglist_cnt;	/* Num of scatter gather list entries */
    U32	cam_sort;		/* Value used by SIM to	sort on	*/
    u_char cam_scsi_status;	/* Returned scsi device	status */
    u_char cam_sense_resid;	/* Autosense resid length: 2's comp */
    u_char cam_osd_rsvd1[2];	/* OSD Reserved	field, for alignment */
    I32	cam_resid;		/* Transfer residual length: 2's comp */
    CDB_UN cam_cdb_io;		/* Union for CDB bytes/pointer */
    U32	cam_timeout;		/* Timeout value */
    u_char *cam_msg_ptr;	/* Pointer to the message buffer */
    u_short cam_msgb_len;	/* Num of bytes	in the message buf */
    u_short cam_vu_flags;	/* Vendor unique flags */
    u_char cam_tag_action;	/* What	to do for tag queuing */
    u_char cam_iorsvd0[3];	/* Reserved field, for alignment */
    u_char cam_sim_priv[ SIM_PRIV ];	/* SIM private data area */
} CCB_SCSIIO;

/* Get device type CCB */
typedef	struct ccb_getdev
{
    CCB_HEADER cam_ch;		/* Header information fields */
    char *cam_inq_data;		/* Ptr to the inquiry data space */
    u_char cam_pd_type;		/* Periph device type from the TLUN */
} CCB_GETDEV;

/* Set Async Callback CCB */
typedef	struct ccb_setasync
{
    CCB_HEADER cam_ch;		/* Header information fields */
    U32	cam_async_flags;	/* Event enables for Callback resp */
    void (*cam_async_func)();	/* Async Callback function address */
    u_char *pdrv_buf;		/* Buffer set aside by the Per.	drv */
    u_char pdrv_buf_len;	/* The size of the buffer */
    void *pdrv_specific_ptr;	/* Driver specific pointer */
} CCB_SETASYNC;

typedef	CCB_SETASYNC CCB_SETASYNC_VU;	/* OBSOLETE */

/* Set device type CCB */
typedef	struct ccb_setdev
{
    CCB_HEADER cam_ch;		/* Header information fields */
    u_char cam_dev_type;	/* Val for the dev type	field in EDT */
} CCB_SETDEV;

/* Abort XPT Request CCB */
typedef	struct ccb_abort
{
    CCB_HEADER cam_ch;		/* Header information fields */
    CCB_HEADER *cam_abort_ch;	/* Pointer to the CCB to abort */
} CCB_ABORT;

/* Terminate I/O Process Request CCB */
typedef	struct ccb_termio
{
    CCB_HEADER cam_ch;		/* Header information fields */
    CCB_HEADER *cam_termio_ch;	/* Pointer to the CCB to terminate */
} CCB_TERMIO;

/*
 * Common SCSI functions.
 * Alignment NOT compatible with CAM-3 protocol
 * ============================================
 */

/* Path	inquiry	CCB */
typedef	struct ccb_pathinq
{
    CCB_HEADER cam_ch;		/* Header information fields */
    u_char cam_version_num;	/* Version number for the SIM/HBA */
    u_char cam_hba_inquiry;	/* Mimic of INQ	byte 7 for the HBA */
    u_char cam_target_sprt;	/* Flags for target mode support */
    u_char cam_hba_misc;	/* Misc	HBA feature flags */
    u_short cam_hba_eng_cnt;	/* HBA engine count */
    /*
     * The following 2 fields are vendor unique	and will be changed
     * in CAM-3	(using 2 bytes of the vendor unique area)
     */
    u_char cam_vu_targets;	/* Number of Targets supported.	*/
    u_char cam_vu_lun;		/* Number of LUNs supported */
    u_char cam_vuhba_flags[ VUHBA ];	/* Vendor unique capabilities */
    U32	cam_sim_priv;		/* Size	of SIM private data area */
    U32	cam_async_flags;	/* Event cap. for Async	Callback */
    u_char cam_hpath_id;	/* Highest path	ID in the subsystem */
    u_char cam_initiator_id;	/* ID of the HBA on the	SCSI bus */
    u_char cam_prsvd0;		/* Reserved field, for alignment */
    u_char cam_prsvd1;		/* Reserved field, for alignment */
    char cam_sim_vid[ SIM_ID ];	/* Vendor ID of	the SIM	*/
    char cam_hba_vid[ HBA_ID ];	/* Vendor ID of	the HBA	*/
    u_char *cam_osd_usage;	/* Ptr for the OSD specific area */
} CCB_PATHINQ;

/*
 * Common SCSI functions.
 * Header only;	no other fields
 * ============================
 */

/* NOP type CCB	*/
typedef	struct ccb_noop
{
    CCB_HEADER cam_ch;		/* Header information fields */
} CCB_NOOP;

/* Release SIM Queue CCB */
typedef	struct ccb_relsim
{
    CCB_HEADER cam_ch;		/* Header information fields */
} CCB_RELSIM;

/* Scan	SCSI bus CCB */
typedef	struct ccb_scanbus
{
    CCB_HEADER cam_ch;		/* Header information fields */
} CCB_SCANBUS;


/* Reset SCSI Bus CCB */
typedef	struct ccb_resetbus
{
    CCB_HEADER cam_ch;		/* Header information fields */
} CCB_RESETBUS;

/* Reset SCSI Device CCB */
typedef	struct ccb_resetdev
{
    CCB_HEADER cam_ch;		/* Header information fields */
} CCB_RESETDEV;

/* Reset SCSI LUN CCB */
typedef	struct ccb_resetlun
{
    CCB_HEADER cam_ch;		/* Header information fields */
} CCB_RESETLUN;

/* Scan	Logical	unit CCB */
typedef	struct ccb_scanlun
{
    CCB_HEADER cam_ch;		/* Header information fields */
} CCB_SCANLUN;


/* Target mode structures. */

/* Host	Target Mode Version 1 Enable LUN CCB */
typedef	struct ccb_en_lun
{
    CCB_HEADER cam_ch;			/* Header information fields */
    u_short cam_grp6_len;		/* Group 6 VU CDB length */
    u_short cam_grp7_len;		/* Group 7 VU CDB length */
    u_char *cam_ccb_listptr;		/* Pointer to the target CCB list */
    u_short cam_ccb_listcnt;		/* Count of Target CCBs	in the list */
} CCB_EN_LUN;

/* Enable LUN CCB (HTM V2) */
typedef	struct ccb_enable_lun
{
    CCB_HEADER cam_ch;			/* Header information fields */
    U16	cam_grp6_length;		/* Group 6 Vendor Unique CDB Lengths */
    U16	cam_grp7_length;		/* Group 7 Vendor Unique CDB Lengths */
    u_char *cam_immed_notify_list;	/* Ptr to Immediate Notify CCB list */
    U32	cam_immed_notify_cnt;		/* Number of Immediate Notify CCBs */
    u_char *cam_accept_targ_list;	/* Ptr to Accept Target	I/O CCB	list */
    U32	cam_accept_targ_cnt;		/* Number of Accept Target I/O CCBs */
    u_char cam_sim_priv[ SIM_PRIV ];	/* SIM private data area */
} CCB_ENABLE_LUN;

/* Immediate Notify CCB	*/
typedef	struct ccb_immed_notify
{
    CCB_HEADER cam_ch;			/* Header information fields */
    u_char *cam_pdrv_ptr;		/* Ptr used by the Peripheral driver */
    void (*cam_cbfnot)();	   /* Callback on notification function	*/
    u_char *cam_sense_ptr;		/* Pointer to the sense	data buffer */
    u_char cam_sense_len;		/* Num of bytes	in the Autosense buf */
    u_char cam_init_id;			/* ID of Initiator that	selected */
    U16	cam_seq_id;			/* Sequence Identifier */
    u_char cam_msg_code;		/* Message Code	*/
    u_char cam_msg_args[7];		/* Message Arguments */
} CCB_IMMED_NOTIFY;

/* Notify Acknowledge CCB */
typedef	struct ccb_notify_ack
{
    CCB_HEADER cam_ch;			/* Header information fields */
    U16	cam_seq_id;			/* Sequence Identifier */
    u_char cam_event;			/* Event */
    u_char cam_rsvd;
} CCB_NOTIFY_ACK;

/* Accept Target I/O CCB */
typedef	struct ccb_accept_targ
{
    CCB_HEADER cam_ch;			/* Header information fields */
    u_char *cam_pdrv_ptr;		/* Ptr used by the Peripheral driver */
    CCB_HEADER *cam_next_ccb;		/* Ptr to the next CCB for action */
    u_char *cam_req_map;		/* Ptr for mapping info	on the Req. */
    void (*cam_cbfcnot)();		/* Callback on completion function */
    u_char *cam_data_ptr;		/* Pointer to the data buf/SG list */
    U32	cam_dxfer_len;			/* Data	xfer length */
    u_char *cam_sense_ptr;		/* Pointer to the sense	data buffer */
    u_char cam_sense_len;		/* Num of bytes	in the Autosense buf */
    u_char cam_cdb_len;			/* Number of bytes for the CDB */
    u_short cam_sglist_cnt;		/* Num of scatter gather list entries */
    U32	cam_sort;			/* Value used by SIM to	sort on	*/
    u_char cam_scsi_status;		/* Returned scsi device	status */
    u_char cam_sense_resid;		/* Autosense resid length: 2's comp */
    u_char cam_osd_rsvd1[2];		/* OSD Reserved	field, for alignment */
    I32	cam_resid;			/* Transfer residual length: 2's comp */
    CDB_UN cam_cdb_io;			/* Union for CDB bytes/pointer */
    U32	cam_timeout;			/* Timeout value */
    u_char *cam_msg_ptr;		/* Pointer to the message buffer */
    u_short cam_msgb_len;		/* Num of bytes	in the message buf */
    u_short cam_vu_flags;		/* Vendor unique flags */
    u_char cam_tag_action;		/* What	to do for tag queuing */
    u_char cam_tag_id;			/* Tag ID */
    u_char cam_initiator_id;		/* Initiator ID	*/
    u_char cam_iorsvd0[1];		/* Reserved field, for alignment */
    u_char cam_sim_priv[ SIM_PRIV ];	/* SIM private data area */
} CCB_ACCEPT_TARG;

/* Continue Target I/O CCB */
typedef	CCB_ACCEPT_TARG	CCB_CONT_TARG;

/* HBA engine structures. */

typedef	struct ccb_eng_inq
{
    CCB_HEADER cam_ch;			/* Header information fields */
    u_short cam_eng_num;		/* The number for this inquiry */
    u_char cam_eng_type;		/* Returned engine type	*/
    u_char cam_eng_algo;		/* Returned algorithm type */
    U32	cam_eng_memory;		/* Returned engine memory size */
} CCB_ENG_INQ;

typedef	struct ccb_eng_exec	/* NOTE: must match SCSIIO size	*/
{
    CCB_HEADER cam_ch;			/* Header information fields */
    u_char *cam_pdrv_ptr;		/* Ptr used by the Peripheral driver */
    U32	cam_engrsvd0;		/* Reserved field, for alignment */
    u_char *cam_req_map;		/* Ptr for mapping info	on the Req. */
    void (*cam_cbfcnp)();		/* Callback on completion function */
    u_char *cam_data_ptr;		/* Pointer to the data buf/SG list */
    U32	cam_dxfer_len;		/* Data	xfer length */
    u_char *cam_engdata_ptr;		/* Pointer to the engine buffer	data */
    u_char cam_engrsvd1;		/* Reserved field, for alignment */
    u_char cam_engrsvd2;		/* Reserved field, for alignment */
    u_short cam_sglist_cnt;		/* Num of scatter gather list entries */
    U32	cam_dmax_len;		/* Destination data maximum length */
    U32	cam_dest_len;		/* Destination data length */
    I32	cam_src_resid;			/* Source residual length: 2's comp */
    u_char cam_engrsvd3[12];		/* Reserved field, for alignment */
    U32	cam_timeout;			/* Timeout value */
    U32	cam_engrsvd4;		/* Reserved field, for alignment */
    u_short cam_eng_num;		/* Engine number for this request */
    u_short cam_vu_flags;		/* Vendor unique flags */
    u_char cam_engrsvd5;		/* Reserved field, for alignment */
    u_char cam_engrsvd6[3];		/* Reserved field, for alignment */
    u_char cam_sim_priv[ SIM_PRIV ];	/* SIM private data area */
} CCB_ENG_EXEC;

#define ASCIZ_64		64

typedef struct ccb_target_ident_vu
{
    CCB_HEADER	cam_ch;		/* Header information fields */
    char        cam_tgt_ident[ASCIZ_64];
    				/* buffer to contain the null-terminated
				   ascii string representing the target's
				   identifier */
} CCB_TARGET_IDENT_VU;

/* 
 * Function code for CCB_JUMP_INQ_VU is XPT_JMP_INQ returns and valid
 * CAM_STATUS are: 
 *	CAM_REQ_CMP -	Fields are valid and available for use.
 *	Any other   -   Filds are not valid do not use.
 * Note ONLY CCB_SCSIIO CCB types can use the jump entry point
 */

typedef struct ccb_jump_inq_vu 
{    
    CCB_HEADER  cam_ch;         /* Header information fields */
    U32 	(*cam_jmp_entry)(CCB_HEADER *, void *, void *, void *, void *);	
				/* Sim jump entry point for this b/t/l */
    void	*cam_sim_arg1;		/* SIM's arg1 for this b/t/l */
    void	*cam_sim_arg2;		/* SIM's arg2 for this b/t/l */
    void	*cam_sim_arg3;		/* SIM's arg3 for this b/t/l */
    void	*cam_sim_arg4;		/* SIM's arg4 for this b/t/l */
} CCB_JUMP_INQ_VU;


/* The CAM_SIM_ENTRY definition	is used	to define the entry points for
the SIMs contained in the SCSI CAM subsystem.  Each SIM	file will
contain	a declaration for it's entry.  The address for this entry will
be stored in the cam_conftbl[] array along will	all the	other SIM
entries. */

#define	CAM_SIM_NAME_LEN	32

typedef	struct cam_sim_entry
{
    I32	   (*sim_init)();		/* Pointer to the SIM init routine */
    I32	   (*sim_action)();		/* Pointer to the SIM CCB go routine */
    char   sim_name[CAM_SIM_NAME_LEN];	/* SIM's name for registration */
    I32	   sim_key1;			/* SIM's registration keys */
    I32	   sim_key2;
    I32	   sim_key3;
    I32	   sim_key4;
    void   *vendor;			/* Pointer to a	vendor-specific	data
					   structure, for us, it's the
					   DEC_SIM_ENTRY structure */
} CAM_SIM_ENTRY;

typedef	struct dec_sim_entry
{
    struct bus *busp;			/* Pointer to SIM's bus	structure */
} DEC_SIM_ENTRY;

/* ---------------------------------------------------------------------- */
/* Defines for the SIM/HBA queue actions.  These value are used	in the
SCSI I/O CCB, for the queue action field. [These values	should match the
defines	from some other	include	file for the SCSI message phases.  We may
not need these definitions here. ] */

#define	CAM_SIMPLE_QTAG		0x20		/* Tag for a simple queue */
#define	CAM_HEAD_QTAG		0x21		/* Tag for head	of queue */
#define	CAM_ORDERED_QTAG	0x22		/* Tag for ordered queue */

/* ---------------------------------------------------------------------- */

/* Defines for the timeout field in the	SCSI I/O CCB.  At this time a value
of 0xF-F indicates a infinite timeout.	A value	of 0x0-0 indicates that	the
SIM's default timeout can take effect. */

#define	CAM_TIME_DEFAULT	0x00000000	/* Use SIM default value */
#define	CAM_TIME_INFINITY	0xFFFFFFFF	/* Infinite timeout for	I/O */

/* ---------------------------------------------------------------------- */

/* Defines for the Path	Inquiry	CCB fields. */

#define	XPT_PATH_INQ_ID	0xFF	/* XPT ID for a	Path Inquiry CCB */

#define	CAM_VERSION		0x4C	/* Binary value	for the	current	ver */

#define	PI_MDP_ABLE		0x80	/* Supports MDP	message	*/
#define	PI_WIDE_32		0x40	/* Supports 32 bit wide	SCSI */
#define	PI_WIDE_16		0x20	/* Supports 16 bit wide	SCSI */
#define	PI_SDTR_ABLE		0x10	/* Supports SDTR message */
#define	PI_LINKED_CDB		0x08	/* Supports linked CDBs	*/
#define	PI_TAG_ABLE		0x02	/* Supports tag	queue message */
#define	PI_SOFT_RST		0x01	/* Supports soft reset */

#define	PIT_PROCESSOR		0x80	/* Target mode processor mode */
#define	PIT_PHASE		0x40	/* Target mode phase cog. mode */

#define	PIM_SCANHILO		0x80	/* Bus scans from ID 7 to ID 0 */
#define	PIM_NOREMOVE		0x40	/* Removable dev not included in scan */
#define	PIM_NOINQUIRY		0x20	/* Inquiry data	not kept by XPT	*/

/* ---------------------------------------------------------------------- */

/* Defines for the "event" field in the	CCB_NOTIFY_ACK */
#define	CAM_RESET_CLEARED  0x80	  /* Reset Cleared */

/* ---------------------------------------------------------------------- */

/* Defines for the HBA engine inquiry CCB fields. */

#define	EIT_BUFFER		0x00	/* Engine type:	Buffer memory */
#define	EIT_LOSSLESS		0x01	/* Engine type:	Lossless compression */
#define	EIT_LOSSLY		0x02	/* Engine type:	Lossly compression */
#define	EIT_ENCRYPT		0x03	/* Engine type:	Encryption */

#define	EAD_VUNIQUE		0x00	/* Eng algorithm ID: vendor unique */
#define	EAD_LZ1V1		0x00	/* Eng algorithm ID: LZ1 var. 1*/
#define	EAD_LZ2V1		0x00	/* Eng algorithm ID: LZ2 var. 1*/
#define	EAD_LZ2V2		0x00	/* Eng algorithm ID: LZ2 var. 2*/

/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */

/* Unix	OSD defines and	data structures. */

#define	INQLEN	36		/* Inquiry string length to store. */

#ifndef	CAM_SUCCESS
#define	CAM_SUCCESS	0	/* For signaling general success */
#define	CAM_FAILURE	1	/* For signaling general failure */
#endif

#define	CAM_FALSE	0	/* General purpose flag	value */
#define	CAM_TRUE	1	/* General purpose flag	value */

#define	XPT_CCB_INVALID	-1	/* for signaling a bad CCB to free */

/* General Union for Kernel Space allocation.  Contains	all the	possible CCB
structures.  This union	should never be	used for manipulating CCB's its	only
use is for the allocation and deallocation of raw CCB space. */

typedef	union ccb_size_union
{
    CCB_SCSIIO	     csio;    /* Please	keep this first, for debug/print */
    CCB_GETDEV	     cgd;
    CCB_PATHINQ	     cpi;
    CCB_RELSIM	     crs;
    CCB_SETASYNC     csa;
    CCB_SETDEV	     csd;
    CCB_ABORT	     cab;
    CCB_RESETBUS     crb;
    CCB_RESETDEV     crd;
    CCB_RESETLUN     crl;
    CCB_TERMIO	     ctio;
    CCB_EN_LUN	     cel;
    CCB_ENABLE_LUN   cel2;
    CCB_IMMED_NOTIFY cin;
    CCB_NOTIFY_ACK   cna;
    CCB_ACCEPT_TARG  cat;
    CCB_ENG_INQ	     cei;
    CCB_ENG_EXEC     cee;
    CCB_NOOP	     cno;
    CCB_SCANBUS	     csb;
    CCB_SCANLUN	     csl;
    CCB_SETASYNC_VU  csm;
    CCB_TARGET_IDENT_VU	ctid;
    CCB_JUMP_INQ_VU cjmp_vu;
} CCB_SIZE_UNION;

/* The typedef for the Async callback information.  This structure is used to
store the supplied info	from the Set Async Callback CCB, in the	EDT table
in a linked list structure. */

typedef	struct async_info
{
    struct async_info *cam_async_next;	/* pointer to the next structure */
    U32	cam_event_enable;		/* Event enables for Callback resp */
    void (*cam_async_func)();		/* Async Callback function address */
    U32	cam_async_blen;			/* Length of "information" buffer */
    u_char *cam_async_ptr;		/* Address for the "information	*/
    void *cam_pdrv_specific;		/* PDRV	specific pointer */
    u_char cam_func_code;		/* the function	code */

} ASYNC_INFO;

/* The CAM EDT table contains the device information for all the
devices, SCSI ID and LUN, for all the SCSI busses in the system.  The
table contains a CAM_EDT_ENTRY structure for each device on the	bus.
*/

typedef	struct cam_edt_entry
{
    ASYNC_INFO *cam_ainfo;	/* Async callback list info for	this B/T/L */
    char cam_inq_data[ INQLEN ];/* storage for the inquiry data	*/
} CAM_EDT_ENTRY;


/*
 * !! NOTE !!  Following defines duplicate defines in cam3_scsi.h and are
 * included here for compatibility reason.
 */

#ifndef	CAM_REQ_INPROG
/*
 * Defines for the CAM status field in the CCB header.
 */
#define	CAM_REQ_INPROG		0x00	/* CCB request is in progress */
#define	CAM_REQ_CMP		0x01	/* CCB request completed w/out error */
#define	CAM_REQ_ABORTED		0x02	/* CCB request aborted by the host */
#define	CAM_UA_ABORT		0x03	/* Unable to Abort CCB request */
#define	CAM_REQ_CMP_ERR		0x04	/* CCB request completed with an err */
#define	CAM_BUSY		0x05	/* CAM subsystem is busy */
#define	CAM_REQ_INVALID		0x06	/* CCB request is invalid */
#define	CAM_PATH_INVALID	0x07	/* Path	ID supplied is invalid */
#define	CAM_DEV_NOT_THERE	0x08	/* SCSI	device not installed/there */
#define	CAM_UA_TERMIO		0x09	/* Unable to Terminate I/O CCB req */
#define	CAM_SEL_TIMEOUT		0x0A	/* Target selection timeout */
#define	CAM_CMD_TIMEOUT		0x0B	/* Command timeout */
#define	CAM_MSG_REJECT_REC	0x0D	/* Message reject received */
#define	CAM_SCSI_BUS_RESET	0x0E	/* SCSI	bus reset sent/received	*/
#define	CAM_UNCOR_PARITY	0x0F	/* Uncorrectable parity	err occurred */
#define	CAM_AUTOSENSE_FAIL	0x10	/* Autosense: Request sense cmd	fail */
#define	CAM_NO_HBA		0x11	/* No HBA detected Error */
#define	CAM_DATA_RUN_ERR	0x12	/* Data	overrun/underrun error */
#define	CAM_UNEXP_BUSFREE	0x13	/* Unexpected BUS free */
#define	CAM_SEQUENCE_FAIL	0x14	/* Target bus phase sequence failure */
#define	CAM_CCB_LEN_ERR		0x15	/* CCB length supplied is inadequate */
#define	CAM_PROVIDE_FAIL	0x16	/* Unable to provide requ. capability */
#define	CAM_BDR_SENT		0x17	/* A SCSI BDR msg was sent to target */
#define	CAM_REQ_TERMIO		0x18	/* CCB request terminated by the host */
#define	CAM_HBA_ERR		0x19	/* Unrecoverable host bus adaptor err*/
#define	CAM_BUS_RESET_DENIED	0x1A	/* SCSI	bus reset denied */
#define	CAM_NO_BIND		0x1B	/* Binding lost	or not obtained	*/
#define	CAM_DISCOVERY_INPROG	0x1C	/* Discovery needed or in progress */

#define	CAM_MUNSA_REJECT	0x32	/* MUNSA rejecting device	*/

#define	CAM_IDE			0x33	/* Initiator Detected Error Received */
#define	CAM_RESRC_UNAVAIL	0x34	/* Resource unavailable	*/
#define	CAM_UNACKED_EVENT	0x35	/* Unacknowledged event	by host	*/
#define	CAM_MESSAGE_RECV	0x36	/* Msg received	in Host	Target Mode */
#define	CAM_INVALID_CDB		0x37	/* Invalid CDB recvd in	HT Mode	*/
#define	CAM_LUN_INVALID		0x38	/* LUN supplied	is invalid */
#define	CAM_TID_INVALID		0x39	/* Target ID supplied is invalid */
#define	CAM_FUNC_NOTAVAIL	0x3A	/* The requ. func is not available */
#define	CAM_NO_NEXUS		0x3B	/* Nexus is not	established */
#define	CAM_IID_INVALID		0x3C	/* The initiator ID is invalid */
#define	CAM_CDB_RECVD		0x3D	/* The SCSI CDB	has been received */
#define	CAM_LUN_ALLREADY_ENAB	0x3E	/* LUN already enabled */
#define	CAM_SCSI_BUSY		0x3F	/* SCSI	bus busy */

#define	CAM_SIM_QFRZN		0x40	/* The SIM queue is frozen w/this err */
#define	CAM_AUTOSNS_VALID	0x80	/* Autosense data valid	for target */

#define	CAM_STATUS_MASK		0x3F	/* Mask	bits for just the status # */

#endif

/*
 * !! NOTE !!  Following defines duplicate defines in cam3_scsi.h and are
 * included here for compatibility reason.
 */

#ifndef	XPT_NOOP

/*
 * Defines for the XPT function	codes, Table 8-2 in the	CAM spec.
 */
	/*
	 * Common function commands, 0x00 - 0x0F
	 */
#define	XPT_NOOP	0x00	/* Execute Nothing */
#define	XPT_SCSI_IO	0x01	/* Execute the requested SCSI IO */
#define	XPT_GDEV_TYPE	0x02	/* Get the device type information */
#define	XPT_PATH_INQ	0x03	/* Path	Inquiry	*/
#define	XPT_REL_SIMQ	0x04	/* Release the SIM queue that is frozen	*/
#define	XPT_SASYNC_CB	0x05	/* Set Async callback parameters */
#define	XPT_SDEV_TYPE	0x06	/* Set the device type information */
#define	XPT_SCAN_BUS	0x07	/* Scan	SCSI Bus */

	/*
	 * XPT SCSI control functions, 0x10 - 0x1F
	 */
#define	XPT_ABORT	0x10	/* Abort the selected CCB */
#define	XPT_RESET_BUS	0x11	/* Reset the SCSI bus */
#define	XPT_RESET_DEV	0x12	/* Reset the SCSI device, BDR */
#define	XPT_TERM_IO	0x13	/* Terminate the I/O process */
#define	XPT_SCAN_LUN	0x14	/* Scan	Logical	Unit */
#define	XPT_CAM3_CCB	0x15	/* CAM-3 CCB inidicator	*/
#define	XPT_BIND	0x16	/* Bind	to a Connection	*/
#define	XPT_BIND_QUERY	0x17	/* Query if Bind exist or options */
#define	XPT_BIND_REL	0x18	/* Release your	Bind */
#define XPT_RESET_LUN   0x19	/* Reset Lun */

	/*
	 * HBA engine commands,	0x20 - 0x2F
	 */
#define	XPT_ENG_INQ	0x20	/* HBA engine inquiry */
#define	XPT_ENG_EXEC	0x21	/* HBA execute engine request */

	/*
	 * Target mode commands, 0x30 -	0x3F
	 */
#define	XPT_EN_LUN	 0x30	/* Enable LUN, Target mode support */
#define	XPT_TARGET_IO	 0x31	/* Execute the target IO request */
#define	XPT_ACCEPT_TARG	 0x32	/* Accept Host Target Mode CDB */
#define	XPT_CONT_TARG	 0x33	/* Cont. Host Target I/O Connection */
#define	XPT_IMMED_NOTIFY 0x34	/* Notify Host Target driver of	event*/
#define	XPT_NOTIFY_ACK	 0x35	/* Acknowledgement of event */

#define	XPT_FUNC	 0x7F	/* TEMPLATE */
#define	XPT_VUNIQUE	 0x80	/* All the rest	are vendor unique commands */
#define	XPT_SASYNC_CB3	 0x81	/* Vendor Unique Set Async callback
				   parameters */
#define XPT_TGT_IDENT	 0x82	/* Vendor Unique - Obtain Target Ident */
#define XPT_JMP_INQ	 0x83	/* Vendor Unique - Obtain SIM's entry for b/t/l */
#endif

/*
 * !! NOTE !!  Following defines duplicate defines in cam3_scsi.h and are
 * included here for compatibility reason.
 */

#ifndef	CAM_DIR_RESV

/*
 * Defines for the CAM flags field in the CCB header.
 */

#define	CAM_DIR_RESV	   0x00000000	/* Data	direction (00: reserved) */
#define	CAM_CDB_POINTER	   0x00000001	/* The CDB field contains a pointer */
#define	CAM_QUEUE_ENABLE   0x00000002	/* SIM queue actions are enabled */
#define	CAM_CDB_LINKED	   0x00000004	/* The CCB contains a linked CDB */
#define	CAM_DIS_CALLBACK   0x00000008	/* Disable callback feature */
#define	CAM_SCATTER_VALID  0x00000010	/* Scatter/gather list is valid	*/
#define	CAM_DIS_AUTOSENSE  0x00000020	/* Disable autosense feature */
#define	CAM_DIR_IN	   0x00000040	/* Data	direction (01: DATA IN)	*/
#define	CAM_DIR_OUT	   0x00000080	/* Data	direction (10: DATA OUT) */
#define	CAM_DIR_NONE	   0x000000C0	/* Data	direction (11: no data)	*/
#define	CAM_ENG_SYNC	   0x00000200	/* Flush resid bytes before cmplt */
#define	CAM_SIM_QFRZDIS	   0x00000400	/* Disable the SIM Q frozen state */
#define	CAM_SIM_QFREEZE	   0x00000800	/* Return the SIM Q to frozen state */
#define	CAM_SIM_QHEAD	   0x00001000	/* Place CCB at	the head of SIM	Q */
#define	CAM_DIS_SYNC	   0x00002000	/* Disable sync, go to async */
#define	CAM_INITIATE_SYNC  0x00004000	/* Attempt Sync	data xfer, and SDTR */
#define	CAM_DIS_DISCONNECT 0x00008000	/* Disable disconnect */
#define	CAM_CALLBCK_PHYS   0x00020000	/* Callback func ptr is	physical */
#define	CAM_NXT_CCB_PHYS   0x00040000	/* Next	CCB pointer is physical	*/
#define	CAM_MSG_BUF_PHYS   0x00080000	/* Message buffer ptr is physical */
#define	CAM_SNS_BUF_PHYS   0x00100000	/* Autosense data ptr is physical */
#define	CAM_DATA_PHYS	   0x00200000	/* SG/Buffer data ptrs are physical */
#define	CAM_CDB_PHYS	   0x00400000	/* CDB pointer is physical */
#define	CAM_ENG_SGLIST	   0x00800000	/* The SG list is for the HBA engine */
#define	CAM_DIS_AUTOSRP	   0x01000000	/* Disable autosave/restore ptrs */
#define	CAM_DIS_AUTODISC   0x02000000	/* Disable autodisconnect */
#define	CAM_TGT_CCB_AVAIL  0x04000000	/* Target CCB available	*/
#define	CAM_TGT_PHASE_MODE 0x08000000	/* The SIM will	run in phase mode */
#define	CAM_MSGB_VALID	   0x20000000	/* Message buffer valid	*/
#define	CAM_TERM_IO	   0x20000000	/* Terminate I/O Message supported */
#define	CAM_DISCONNECT	   0x40000000	/* Disc. mandatory after cdb recv */
#define	CAM_STATUS_VALID   0x40000000	/* Status buffer valid */
#define	CAM_DATAB_VALID	   0x80000000	/* Data	buffer valid */
#define	CAM_SEND_STATUS	   0x80000000	/* Send	status after date phase	*/

#endif

/*
 * !! NOTE !!  Following defines duplicate defines in cam3_scsi.h and are
 * included here for compatibility reason.
 */

#ifndef	AC_PORT_ID_REGISTRATION

/*
 * Asynchronous	events opcodes/flags
 * (Asynchronous Callback CCB fields)
 */
#define	AC_PORT_ID_REGISTRATION	0x80000000  /* Indicates Port_ID Registration */
#define	AC_AUTO_BIND_RELEASE	0x1000	    /* Automatic release of Bind */
#define	AC_DISCOV_NEED_TARGET	0x800	    /* Discovery needed	for target */
#define	AC_DISCOV_NEED_PORT	0x400	    /*Discovery	needed for Port_id */
#define	AC_DISCOV_START		0x200	    /* Discovery Process has started */
#define	AC_DISCOV_END		0x100	    /* Discovery Process has ended */
#define	AC_FOUND_DEVICES	0x80	/* New device found */
#define	AC_SIM_DEREGISTER	0x40	/* A loaded SIM	has de-registered */
#define	AC_SIM_REGISTER		0x20	/* A loaded SIM	has registered */
#define	AC_SENT_BDR		0x10	/* A BDR message was sent to target */
#define	AC_SCSI_AEN		0x08	/* A SCSI AEN has been received	*/
#define	AC_UNSOL_RESEL		0x02	/* A unsolicited reselection occurred */
#define	AC_BUS_RESET		0x01	/* A SCSI bus RESET occurred */


#endif

/*
 * !! NOTE !!  Following typedef duplicates typedef in cam3_scsi.h and are
 * included here for compatibility reason.
 */

#ifndef	_SG_ELEM_TYPE

#define	_SG_ELEM_TYPE
/*
 * Typedef for a scatter/gather	list element.
 */

typedef	struct sg_elem
{
    u_char *cam_sg_address;	/* Scatter/Gather address */
    U32	cam_sg_count;		/* Scatter/Gather count	*/
} SG_ELEM;

#endif

#ifdef __cplusplus
}
#endif

#endif /* _CAM_INCL_ */
