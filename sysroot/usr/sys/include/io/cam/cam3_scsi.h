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
 * @(#)$RCSfile: cam3_scsi.h,v $ $Revision: 1.1.25.2 $ (DEC) $Date: 2001/11/01 20:48:43 $
 */
#ifndef	_CAM3_SCSI_INCL_
#define	_CAM3_SCSI_INCL_

/*
 * Protocol type
 */
#define	SCSI_PROTOCOL	0x1	/* SCSI	protocol number	*/

/*
 * Protocol subtypes
 *
 * NOTE: The sim_type value used in the DEV_DESC data structure and DDR
 *   is especially dependent on the following values. Do Not change these
 *   values lightly, or devices may no longer work correctly (as the DDR
 *   record no longer matches them).
 *   Keep the values for these as single bits in case we want to
 *   make sim_type a bit-field in the future.
 */
#define SCSI_PROTO_SUBTYPE_PARALLEL	0x0	/* older SCSI-2 parallel */
#define SCSI_PROTO_SUBTYPE_IDE		0x1	/* IDE disks & ATAPI */
#define SCSI_PROTO_SUBTYPE_FCP		0x2	/* FC storage */
#define SCSI_PROTO_SUBTYPE_SBP		0x4	/* 1394 storage */
#define SCSI_PROTO_SUBTYPE_SPI		0x8	/* newer SCSI-3 parallel */
#define SCSI_PROTO_SUBTYPE_SA           0x10    /* Smart Array storage */

/*
 * General allocation length defines for the CCB structures.
 */
#define	IOCDBLEN3	  16	/* Space for the CDB bytes/pointer		*/
#define	SENSE_BUF_LEN3	 255	/* Length of sense data	buffer (bytes)		*/
#define	SIM_SENSE_LEN3	  16	/* Space for SIM sense data retrieval (CAM_U32)	*/

/*
 * Defines for the CAM status field in the CCB header.
 */
#ifndef	CAM_REQ_INPROG

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
#define	XPT_BIND	0x16	/*Bind to a Connection */
#define	XPT_BIND_QUERY	0x17	/* Query if Bind exist or options */
#define	XPT_BIND_REL	0x18	/* Release your	Bind */
#define	XPT_RESET_LUN	0x19	/* Reset the SCSI LUN */

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
#define XPT_JMP_INQ      0x83   /* Vendor Unique - Obtain SIM's entry for b/t/l */
#endif

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

#ifndef	AC_PORT_ID_REGISTRATION

/*
 * Asynchronous	events opcodes/flags
 * (Asynchronous Callback CCB fields)
 */
#define	AC_PORT_ID_REGISTRATION	0x80000000  /* Indicates Port_ID Registration */
#define AC_BUS_SCAN_DONE        0x2000      /* callback (one time) when bus scanned */
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

#ifndef	_SG_ELEM_TYPE

#define	_SG_ELEM_TYPE
/*
 * Typedef for a scatter/gather	list element.
 */

typedef	struct sg_elem
{
    CAM_U8 *cam_sg_address;	/* Scatter/Gather address */
    CAM_U32 cam_sg_count;	/* Scatter/Gather count	*/
} SG_ELEM;

#endif

/*
 * CAM-3 ccb header definition
 *
 * !! Keep cam_flags at	the same offset	in CAM-2 and CAM-3 !!
 * ==========================================================
 */

#define	CCB_HEADER3_DEFINED

typedef	struct ccb_header3 {

    struct ccb_header3 *my_addr; /* The	address	of this	CCB	*/
    CAM_U16 cam_ccb_len;	/* Length of the entire	ccb	*/
    CAM_U8  cam_func_code;	/* XPT function	code (CAM-3 CCB	Identifier) */
    CAM_U8  cam_status;		/* Returned CAM	subsystem status	    */
    CAM_U32 cam_logical_id;	/* The assigned	Logical	ID of the device.   */
    CAM_U32 cam_flags;		/* Flags for operation of the subsystem	    */
    CAM_U32 cam3_func_code;	/* The actual function code for	a CAM-3	ccb */
    CAM_U32 cam_protocol;	/* The protocol	number - SCSI, NETWORK,	ATA, etc. */
    CONNECTION_ID cam_connectid;/* SCSI addressing information */
    CAM_U32 cam_sim_generation;	/* Generation number returned by BIND CCB	   */
    CAM_VOID_OFFSET cam_sim_bhandle; /*	SIM Bind handle	returned by the	BIND CCB   */
    CAM_U8  *cam_xpt_ptr;	/* Pointer to the XPT assigned driver workspace	   */
    CAM_U8  *cam_pdrv_ptr;	/* Pointer to the driver assigned driver workspace */
    CAM_U8  *cam_sim_ptr;	/* Pointer to the SIM assigned SIM workspace	   */
    CAM_U32 cam_pdrv_len;	/* The length of the driver workspace	*/
    CAM_U32 cam_sim_len;	/* The length of the SIM workspace	*/

} CCB_HEADER3;


/*
 * Union definition for	the CDB	space in the SCSI I/O request CCB
 */
typedef	union cdb_un3
{
    CAM_U8 *cam_cdb_ptr;		/* Pointer to the CDB bytes to send */
    CAM_U8 cam_cdb_bytes[IOCDBLEN3];	/* Area	for the	CDB to send */
} CDB_UN3;

/*
 * Generic CCB definition
 * Used	only to	make macro CAM_GET_CB_PTR non-specific
 */
typedef	struct ccb_generic3
{
    CCB_HEADER3	cam_ch;
    void	*cam_ccb_body;
} CCB_GENERIC3;

/*
 * Common SCSI functions.
 * Alignment compatible	with CAM-1 protocol
 * ========================================
 */

/*
 * SCSI	I/O Request CCB
 */

typedef	struct ccb_scsiio3
{
    CCB_HEADER3	cam_ch;		/* Header information fields */
    CAM_VOID_OFFSET cam_vu_ptr;	/* Ptr used by the Peripheral driver */
    CCB_HEADER3	*cam_next_ccb;	/* Ptr to the next CCB for action */
    CAM_VOID_OFFSET cam_req_map; /* Ptr	for mapping info on the	Req. */
    CAM_VOID (*cam_cbfcnp)();	/* Callback on completion function */
    CAM_U8 *cam_data_ptr;	/* Pointer to the data buf/SG list */
    CAM_U32 cam_dxfer_len;	/* Data	xfer length */
    u_char *cam_sense_ptr;	/* Pointer to the sense	data buffer */
    CAM_U8  cam_sense_len;	/* Num of bytes	in the Autosense buf	*/	  
    CAM_U8  cam_cdb_len;	/* Number of bytes for the CDB */
    CAM_U16 cam_sglist_cnt;	/* Num of scatter gather list entries */
    CAM_U32 cam_vu_field;	/* Vendor unique field */
    CAM_U8  cam_scsi_status;	/* Returned scsi device	status */
    CAM_U8  cam_sense_resid;	/* Autosense resid length: 2's comp	*/	 
    CAM_U16 cam_reserved2;	/* alignment	*/
    CAM_S32 cam_resid;		/* Transfer residual length: 2's comp */
    CDB_UN3 cam_cdb_io;		/* Union for CDB bytes/pointer */
    CAM_U32 cam_timeout;	/* Timeout value */
    CAM_U8 *cam_msg_ptr;	/* Pointer to the message buffer */
    CAM_U16 cam_msgb_len;	/* Num of bytes	in the message buf */
    CAM_U16 cam_vu_flags;	/* Vendor unique flags */
    CAM_U8  cam_tag_action;	/* What	to do for tag queuing */
    CAM_U8  reserved[3];
    CAM_U32 cam_tag_id;		/* Tag	ID	*/
    CAM_U32 cam_initiator_id[4]; /* Initiator ID target	operation */
    CAM_U32 cam_sim_sense[SIM_SENSE_LEN3]; /* Working area for SIM sense data retrieval	*/
    CAM_U8 cam_sense_buf[SENSE_BUF_LEN3];  /* Sense data buffer	*/
} CCB_SCSIIO3;

/*
 * Get device type CCB
 */
typedef	struct ccb_getdev3
{
    CCB_HEADER3	cam_ch;		/* Header information fields */
    char *cam_inq_data;		/* Pointer to the inquiry data space */
    CAM_U8 cam_pd_type;		/* Peripheral device type from the TLUN	*/
} CCB_GETDEV3;

/*
 * Set Async Callback CCB
 */
typedef	struct ccb_setasync3
{
    CCB_HEADER3	cam_ch;		/* Header information fields */
    CAM_U32 cam_async_flags;	/* Event enables for Callback resp */
    CAM_VOID (*cam_async_func)(); /* Async Callback function address */
    CAM_U8 *pdrv_buf;		/* Buffer set aside by the Per.	drv */
    CAM_U8 pdrv_buf_len;	/* The size of the buffer */
    void *pdrv_specific_ptr;	/* Driver specific pointer */
} CCB_SETASYNC3;

/*
 * Set device type CCB
 */
typedef	struct ccb_setdev3
{
    CCB_HEADER3	cam_ch;		/* Header information fields */
    CAM_U8 cam_dev_type;	/* Valid for the device	type field in EDT */
} CCB_SETDEV3;

/*
 * Abort XPT Request CCB
 */
typedef	struct ccb_abort3
{
    CCB_HEADER3	cam_ch;		/* Header information fields */
    CCB_HEADER3	*cam_abort_ch;	/* Pointer to the CCB to abort */
} CCB_ABORT3;

/*
 * Terminate I/O Process Request CCB
 */
typedef	struct ccb_termio3
{
    CCB_HEADER3	cam_ch;		/* Header information fields */
    CCB_HEADER3	*cam_termio_ch;	/* Pointer to the CCB to terminate */
} CCB_TERMIO3;

/*
 * Common SCSI functions.
 * Alignment NOT compatible with CAM-1 protocol
 * ============================================
 */

typedef	struct ccb_pathinq3
{
CCB_HEADER3 cam_ch;		/* Header information fields */
char   cam_version_num[ASCIZ_32]; /* ASCII NULL	terminated string Version number */
char cam_interconnect[ASCIZ_32];  /* ASCII NULL	terminated string Interconnect */
				  /* protocol type (e.g., SIP, FCP) */
CAM_U32	cam_ha_inquiry;		/* Mimic of INQ	byte 7 for the HA */
CAM_U32	cam_target_sprt;	/* Flags for target mode support */
CAM_U32	cam_ha_misc;		/* Misc	HA feature flags */
CAM_U32	cam_ha_eng_cnt;		/* HA engine count */
CAM_U32	cam_max_targ_addr[4];	/* Maximum SCSI	target address */
CAM_U32	cam_max_lun_addr[4];	/* Maximum SCSI	LUN address */
CAM_U8	cam_vuha_flags[16];	/* Vendor unique capabilities */
CAM_U32	cam_async_flags;	/* Event cap. for Async	Callback */
CAM_U32	cam_hpath_id;		/* Highest path	ID in the subsystem */
CAM_U32	cam_initiator_id[4];	/* ID of the HA	on the SCSI bus	*/
CAM_U32	cam_prsvd0;		/* Reserved field, for alignment */
char	cam_sim_vid[ASCIZ_32];	/* Vendor ID of	the SIM	*/
char	cam_ha_vid[ASCIZ_32];	/* Vendor ID of	the HA */
CAM_U8 *cam_osd_usage;		/* Ptr for the OSD specific area */
} CCB_PATHINQ3;

typedef	struct ccb_bind3
{
    CCB_HEADER3	cam_ch;		/* CCB_HEADER3 information fields */
    CAM_U32 cam_bind_ops;	/* Operational attributes */
    CAM_U32 cam_pdrv_reg;	/* The requesters driver registration number */
} CCB_BIND3;

typedef	struct ccb_bind_release3
{
    CCB_HEADER3	cam_ch;		/* CCB_HEADER3 information fields */
    CAM_U32 cam_bind_ops;	/* Operational attributes */
    CAM_U32 cam_pdrv_reg;	/* The requesters driver registration number */
} CCB_BIND_RELEASE3;

typedef	struct ccb_bind_query3
{
    CCB_HEADER3	cam_ch;		/* CCB_HEADER3 information fields */
    CAM_U32 cam_bind_ops;	/* Operational attributes */
    CAM_U32 cam_pdrv_reg;	/* The requesters driver registration number */
} CCB_BIND_QUERY3;

typedef	struct ccb_relsim3
{
    CCB_HEADER3	cam_ch;		/* Header information fields */
    CAM_U32 cam_frzn_cnt;	/* Current freeze count	*/
} CCB_RELSIM3;

#define ASCIZ_64		64

typedef struct ccb_target_ident_vu3
{
    CCB_HEADER3	cam_ch;		/* Header information fields */
    char        cam_tgt_ident[ASCIZ_64];
    				/* buffer to contain the null-terminated
				   ascii string representing the target's
				   identifier */
} CCB_TARGET_IDENT_VU3;

/*
 * Common SCSI functions.
 * Header only;	no other fields
 * ============================
 */
typedef	struct ccb_noop3
{
    CCB_HEADER3	cam_ch;		/* CCB_HEADER3 information fields */
} CCB_NOOP3;

typedef	struct ccb_scanbus3
{
    CCB_HEADER3	cam_ch;		/* Header information fields */
} CCB_SCANBUS3;

typedef	struct ccb_scanlun3
{
    CCB_HEADER3	cam_ch;		/* Header information fields */
} CCB_SCANLUN3;

typedef	struct ccb_resetbus3
{
    CCB_HEADER3	cam_ch;		/* Header information fields */
} CCB_RESETBUS3;

typedef	struct ccb_resetdev3
{
    CCB_HEADER3	cam_ch;		/* Header information fields */
} CCB_RESETDEV3;

typedef	struct ccb_resetlun3
{
    CCB_HEADER3	cam_ch;		/* Header information fields */
} CCB_RESETLUN3;

/*
 * General Union for Kernel Space allocation.  Contains	all the	possible CCB
 * structures.	This union should never	be used	for manipulating CCB's its only
 * use is for the allocation and deallocation of raw CCB space.
 */
union ccb_size_union3
{
    CCB_SCSIIO3		csio;	 /* Please keep	this first, for	debug/print */
    CCB_NOOP3		cno;
    CCB_BIND3		cbind;
    CCB_BIND_RELEASE3	cbind_rel;
    CCB_BIND_QUERY3	cbind_query;
    CCB_GETDEV3		cgd;
    CCB_PATHINQ3	cpi;
    CCB_RELSIM3		crs;
    CCB_SCANBUS3	csb;
    CCB_SCANLUN3	csl;
    CCB_SETASYNC3	csa;
    CCB_SETDEV3		csd;	/* !! To be removed from CAM-3 !! */
    CCB_ABORT3		cab;
    CCB_RESETBUS3	crb;
    CCB_RESETDEV3	crd;
    CCB_RESETLUN3	crl;
    CCB_TERMIO3		ctio;
    CCB_TARGET_IDENT_VU3    ctid;
};

#define	CCB_SIZE_UNION3		\
    ((sizeof(union ccb_size_union3) + 7) & (~7))

#endif	/* _CAM3_SCSI_INCL_  */

