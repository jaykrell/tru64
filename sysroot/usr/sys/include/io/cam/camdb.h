/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: camdb.h,v $
 * Revision 1.1.22.1  2002/10/04  12:03:39  Mike_Zaharee
 * 	Merge of v51asupportos-725-zaharee, 1.1.13.1 -> 1.1.18.1 delta.
 * 	Add probe and async callback count fields to flags in SCSI_DID.
 * 	QAR 91730.
 *
 * Revision 1.1.13.1  1999/10/14  14:25:08  Jamey_Poirier
 * 	Modified the SCSI_PATH structure to include eight bits
 * 	for the peripheral qualifier and device type.
 *
 * Revision 1.1.8.13  1998/08/17  17:46:09  James_Smart
 * 	Convert scsi path state to a bitmask
 * 	[1998/08/14  16:02:07  James_Smart]
 *
 * Revision 1.1.8.12  1998/05/21  19:08:01  Raul_Kacirek
 * 	Converted SCSI_DID locks to XPT locks.
 * 	[1998/05/21  19:00:20  Raul_Kacirek]
 * 
 * Revision 1.1.8.11  1998/04/22  20:06:10  James_Smart
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.8.8 **
 * 		** Merge revision:	1.1.8.10 **
 * 	 	** End **
 * 	Add scsimgr to camdb function code SCSI_FC_SET_WWID, to support
 * 	  user-settable wwid's.
 * 	Update DID->being_deleted to be 2 bits to be able to specify
 * 	  hard/soft deletion.
 * 	[1998/04/21  21:06:46  James_Smart]
 * 
 * 	Bump SCSI Database Version
 * 	Update WWID type definitions as per VMS/CONSOLE/UNIX discussions.
 * 	  This adds support for the new IEEE registered extended, etc values.
 * 	Add user_wwid_kds_ptr to the SCSI_DID to support user-specified
 * 	  WWID values.
 * 	[1998/04/17  21:15:01  James_Smart]
 * 
 * Revision 1.1.8.10  1998/04/14  18:52:21  Jamey_Poirier
 * 	Added lock flags for SCSI_DID.
 * 	[1998/04/08  22:19:32  Jamey_Poirier]
 * 
 * Revision 1.1.8.9  1998/04/07  14:51:34  Raul_Kacirek
 * 	Fixed SCSI_DID_UNLOCK to extract SPL (from lock data) prior to unlocking
 * 	[1998/04/07  14:46:01  Raul_Kacirek]
 * 
 * Revision 1.1.8.8  1998/03/02  22:40:50  Fred_Knight
 * 	Add HSZ this/other structures for new HSZ wwid type.
 * 	[1998/03/02  20:38:10  Fred_Knight]
 * 
 * Revision 1.1.8.7  1997/10/29  21:26:05  Jamey_Poirier
 * 	Modified the SCSI_DID locking mechanism to raise the IPL when taking
 * 	out a lock, and lower it again when unlocked.  This prevents
 * 	a device interrupt from being delivered and taking out a PDrv lock
 * 	with a lower priority lock held.
 * 	[1997/10/29  15:39:40  Jamey_Poirier]
 * 
 * Revision 1.1.8.6  1997/10/07  17:00:00  James_Smart
 * 	CAM3 : Rework for CAM3
 * 	[1997/10/03  16:50:28  James_Smart]
 * 
 * Revision 1.1.8.5  1997/08/15  17:52:00  Fred_Knight
 * 	Add version field and start deleting obsolete functions
 * 	[1997/08/14  15:54:33  Fred_Knight]
 * 
 * Revision 1.1.8.4  1997/07/21  20:34:55  James_Smart
 * 	Bug fixes from additional testing
 * 	[1997/07/21  20:01:44  James_Smart]
 * 
 * 	Add new per unit info (from the old EDT), and the new WWID
 * 	to scsi_did.
 * 	[1997/07/17  19:08:18  James_Smart]
 * 
 * Revision 1.1.8.3  1997/03/03  15:34:41  Robin_Miller
 * 	Adding function prototype declarations.
 * 	[1997/03/03  14:59:52  Robin_Miller]
 * 
 * Revision 1.1.9.2  1996/12/18  17:31:29  Raul_Kacirek
 * 	Tag RK01 - Modification to speed-up translation from physical
 * 	to logical device ID.
 * 	[1996/12/18  15:32:38  Raul_Kacirek]
 * 
 * Revision 1.1.8.2  1996/11/22  21:33:55  Raul_Kacirek
 * 	Tag RK01 - Modification to speed-up translation from physical
 * 	to logical device ID.
 * 
 * 	Tag RK01 - modification to speed-up nexus translation to DID
 * 	[1996/11/15  18:52:33  Raul_Kacirek]
 * 
 * Revision 1.1.3.5  1995/12/20  18:44:15  David_Gagne
 * 	Remove unused scsi_did fields.
 * 	Rename the opens field in the scsi_did to tot_opens.
 * 	Add prototype for the camdb_checkpaths routine.
 * 	Re-define the initialization point for the cam_ptr field.
 * 	[1995/12/18  20:28:56  David_Gagne]
 * 
 * Revision 1.1.3.4  1995/11/10  22:06:03  David_Gagne
 * 	Add the scan all buses request.
 * 	[1995/11/09  19:51:24  David_Gagne]
 * 
 * Revision 1.1.3.3  1995/08/22  20:22:46  David_Gagne
 * 	Added the prototype for camdb_addpath_k.
 * 	Added current path and starting path pointers in SCSI_DID.
 * 	Add the driver-specific request.
 * 	Add the get information request.
 * 	Change the bus and target fields in SCSI_REQ2 to (u_)longs.
 * 	Add camdb_reinit to the prototype declarations.
 * 	[1995/08/21  17:57:26  David_Gagne]
 * 
 * Revision 1.1.3.2  1995/07/05  15:15:06  James_Smart
 * 	Initial creation.
 * 	[1995/07/04  11:34:13  James_Smart]
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: camdb.h,v $ $Revision: 1.1.22.1 $ (DEC) $Date: 2002/10/04 12:03:39 $
 */

#ifndef _CAM_DB_INCL_
#define _CAM_DB_INCL_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The type of data structure (a field in the data structure header) is a
 * numeric value.  The values that can be placed in this field for the SCSI
 * database data structures are described next.
 */

#define SCSI_DS_SCSI		0x01	/* Main SCSI data structure */
#define SCSI_DS_DIDDB		0x02	/* SCSI device ID database d.s. */
#define SCSI_DS_PATH		0x03	/* SCSI path data structure */
#define SCSI_DS_WWID		0x04	/* SCSI WWID structure */
#define SCSI_DS_MAX		0x05	/* Maximum SCSI ds number */

/*
 * The translation of the device ID (which is retrieved from the minor
 * number of the dev_t) needs to be quick.  To make it quick, we will have
 * an array of device ID data structures.  But since we may need 0 to 1000s
 * of these, we will have a two tiered array design.  There will be an
 * array of pointers in the SCSI database data structure.  These pointers
 * will each point to an array of device ID data structures.  The following
 * constant is used to define the size of the second level array.
 */

/*
 * ******************************* WARNING *****************************
 * the value of SCSI_DID_PER_ARR must *ALWAYS* be a power of 2
 * ******************************* WARNING *****************************
 */
#define SCSI_DID_PER_ARR	8	/* Number of SCSI_DID data
					   structures in each array */
#define SCSI_DID_ARR_SHF	3	/* Number of bits to shift down 
					 * The 2's power that equals
					 * SCSI_DID_PER_ARR */


/* ---------------------------------------------------------------------- */

/*
 * SCSI path data structure.  This data structure will store a physical
 * address of a SCSI device.  The physical address of a SCSI device is its
 * bus number, target number, and LUN.
 *
 * For some devices, there may be multiple paths.  If so, multiple of these
 * path data structures will be available for that device.
 *
 * Note: 
 *  For KDS use - we link the SCSI_PATH as a child of the SCSI_DIDDB
 *  structure. KDS says we must have DS_PTR records for a child, which then
 *  points to a DS_HDR in the actual structure. We cheat to consolidate some
 *  space in this preallocated SCSI_PATH. We use a DS_HDR, which has a DS_PTR
 *  structure in the beginning of it. We have the SCSI_DIDDB use the offset
 *  to this embedded DS_PTR structure - and link all additional paths via the
 *  DS_PTR structure. This way, KDS saves/creates the SCSI_DID as part of
 *  the SCSI_DIDDB structure (and each SCSI_DID has 1 embedded path),  and
 *  will create/save each additional path off of the DS_PTR peer queue in the
 *  embedded path structure.
 */
typedef struct scsi_path
{
  DS_HDR            path_hdr;           /* KDS Data structure header */
  u_long            bus;                /* SCSI bus number           */
  u_long            target;             /* Target number on bus      */
  u_long            lun;                /* SCSI logical unit number  */
  u_int             state : 8,          /* state/validity flags      */
                    pqual : 8,          /* path peripheral qualifier */
                    spare : 16;         /* reserved                  */
  struct scsi_did  *did;                /* Device at this path       */
  struct scsi_path *next_tgt;           /* tgt linked list for CAM_SCSI_BUS */
  struct scsi_path *next_lun;           /* lun linked list for CAM_SCSI_BUS */
} SCSI_PATH;

/* bitmask values for SCSI_PATH->state */
#define SCSI_PATH_UNKNOWN		0
#define SCSI_PATH_VALID			1
#define SCSI_PATH_STALE			2
#define SCSI_PATH_BEING_PROBED		4

/* ----------------------------------------------------------------------- */

/*
 * WWID Type Definitions:
 */
#define SCSI_WWID_IEEE_REGEXT	    0x01  /* Page 0x83, ID type 3, NAA 0110 */
#define SCSI_WWID_IEEE_REG	    0x02  /* Page 0x83, ID type 3, NAA 0101 */
#define SCSI_WWID_PG83TY1_VID	    0x03  /* Page 0x83, ID type 1 */
#define SCSI_WWID_PG80_SERIALNO	    0x04  /* Page 0x80 S/N */
#define SCSI_WWID_INQ_SERIALNO	    0x05  /* Inquiry derived S/N */
#define SCSI_WWID_TGT_IDENT	    0x06  /* Adapter's Target Identifier */
#define SCSI_WWID_BTL		    0x07  /* Bus/Target/Lun */
#define SCSI_WWID_DEC_UNIQUE	    0x08  /* DEC Unique Algorithm */
#define SCSI_WWID_HSZ_THISOTHER	    0x09  /* HSZ Unique Algorithm */
#define SCSI_WWID_IEEE48_V_EXT	    0x0A  /* Page 0x83, ID type 3, NAA 0010 */
#define SCSI_WWID_IEEE48_0_EXT	    0x0B  /* Page 0x83, ID type 3, NAA 0001 */
#define SCSI_WWID_IEEE_EUI64	    0x0C  /* Page 0x83, ID type 2 */
#define SCSI_WWID_USER_SPEC_ID	    0xFF  /* User-specified Identifier */

/*
 * Base header for all types 
 */
typedef struct wwid_hdr {
	u_int		len   : 20,	/* length of WWID data (not incl hdr) */
			ascii :  1,	/* ascii data flag */
			rsvd  :  3,     /* reserved location for "flags" */
			type  :  8;	/* WWID type */
} wwid_hdr_t;


/*
 * structure for:
 *    SCSI_WWID_IEEE_REGEXT
 */
typedef struct wwid_p83_ieee128 {
	wwid_hdr_t	hdr;
	u_char		ieee[16];
} wwid_p83_ieee128_t;


/*
 * structure for:
 *    SCSI_WWID_IEEE_REG
 *    SCSI_WWID_IEEE48_V_EXT
 *    SCSI_WWID_IEEE48_0_EXT
 *    SCSI_WWID_IEEE_EUI64
 */
typedef struct wwid_p83_ieee64 {
	wwid_hdr_t	hdr;
	u_char		ieee[8];
} wwid_p83_ieee64_t;

/*
 * structure for:
 *    SCSI_WWID_PG83TY1_VID
 */
typedef struct wwid_p83_vendor {
	wwid_hdr_t	hdr;
	u_char		pid[16];
	u_char		ieee[248];      /* variable size */
} wwid_p83_vendor_t;

/*
 * structure for:
 *    SCSI_WWID_PG80_SERIALNO
 *    SCSI_WWID_INQ_SERIALNO
 */
typedef struct wwid_serial_num {
	wwid_hdr_t	hdr;
	u_char		vid[8];
	u_char		pid[16];
	u_char		sn[248];        /* variable size */
} wwid_serial_num_t;

/*
 * structure for:
 *    SCSI_WWID_TGT_IDENT
 */
typedef struct wwid_tgt_ident {
	wwid_hdr_t	hdr;
	u_char		vid[8];
	u_char		pid[16];
	u_char		dev_type[4];
	u_char		lun_no[7];
	u_char		ident[128];     /* variable size */
} wwid_tgt_ident_t;

/*
 * structure for:
 *    SCSI_WWID_BTL
 */
typedef struct wwid_btl {
	wwid_hdr_t	hdr;
	u_char		vid[8];
	u_char		pid[16];
	u_char		dev_type[4];
	u_char		bus_no[4];
	u_char		target_no[6];
	u_char		lun_no[6];
} wwid_btl_t;
    
/*
 * structure for:
 *    SCSI_WWID_DEC_UNIQUE
 */
typedef struct wwid_dec_unique {
	wwid_hdr_t	hdr;
	u_char		vid[8];
	u_char		pid[16];
	u_char		unique_id[248];     /* variable size */
} wwid_dec_unique_t;

/*
 * structure for:
 *    SCSI_WWID_HSZ_THISOTHER
 */
typedef struct wwid_hsz_this_other {
	wwid_hdr_t	hdr;
	u_char		vid[8];
	u_char		pid[16];
	u_char		sn[20];
	u_char		dev_type[4];
	u_char		target_no[6];
	u_char		lun_no[6];
} wwid_hsz_this_other_t;


/*
 * structure for:
 *    SCSI_WWID_USER_SPEC_ID
 */
typedef struct wwid_user_specified {
	wwid_hdr_t	hdr;
	u_char		unique_id[256];     /* variable size */
} wwid_user_specified_t;


typedef union wwid {
	wwid_hdr_t		hdr;
	wwid_p83_ieee128_t	ieee128;
	wwid_p83_ieee64_t	ieee64;
	wwid_p83_vendor_t	vendor;
	wwid_serial_num_t	serialno;
	wwid_tgt_ident_t	tgt_ident;
	wwid_btl_t		physaddr;
	wwid_dec_unique_t	dec_unique;
	wwid_hsz_this_other_t	hszsn;
	wwid_user_specified_t	user_spec;
} wwid_t;

/*
 * The DS_HDR will be used by KDS to indicate the variable length size
 * of the wwid data, etc.
 *
 * When generating the WWID, we'll create the wwid string once and save
 * the resulting string length. However, to cut down on redundant data,
 * we will not keep the wwid string around.
 */
typedef struct scsi_wwid_hdr {
	DS_HDR		kds_hdr;	/* KDS SCSI_WWID info */
	U32		wwid_strlen;	/* string length for wwid */
} SCSI_WWID_HDR;

/*
 * Note: we fully define the data structure here.
 *
 * HOWEVER, the way we use this structure internally is that we rarely
 * allocate a "whole" structure - we only allocate enough memory to
 * contain the SCSI_WWID_HDR and the number of bytes to cover the amount
 * of valid information in the wwid_data.
 *
 * SO.. be careful when accessing the udi_wwid structure. If you don't
 * carefully pay attention to the wwid_t type and length fields, you
 * could walk off the end of allocated memory for the SCSI_WWID structure.
 */
typedef struct scsi_wwid {
	SCSI_WWID_HDR	hdr;
	wwid_t		wwid_data;
} SCSI_WWID;


/* ---------------------------------------------------------------------- */

/*
 * The xpt maintains a set of pd-specific data structures that are
 * allocated for a device.
 */
typedef struct pd_spec_info {
    struct  pd_spec_info *pd_spec_flink;	/* Pointer to next */
    struct  pd_spec_info *pd_spec_blink;	/* Pointer to prev. */
    u_int   spec_reg_no;	/* The drivers registration number */
    u_int   spec_size;		/* Size of driver specific struct */
    void    *spec_ptr;		/* Pointer to driver specific struct */
    void    (*spec_release)(CAM_U32 lid, CAM_VOID *spec_ptr, CAM_U32 flags);
} PD_SPEC_INFO;

/* ----------------------------------------------------------------------- */

/*
 * Device ID data structure.  This data structure will store the information
 * required to translate a SCSI device ID (which is retrieved from the minor
 * number of a dev_t) to a SCSI physical address (bus, target, lun); also
 * known as a path.  This translation information must be preserved across
 * boots so that the device special files (which hold the dev_t value) will
 * continue to function across boots.
 *
 * There may be multiple paths that can be used to access a device.  This
 * structure allows for the multiple paths to be available.  For each device
 * ID, there is a primary path and zero to many alternate paths.
 *
 * Note that this data structure does not contain the standard database
 * header (DS_HDR).  This is because this data structure will be contained
 * within a larger data structure.  And that larger data structure will
 * contain the standard database header.
 *
 * Certain fields are only valid at certain times.  The validity of the
 * fields are explained in the comments below.
 */

typedef struct scsi_did
{

  /*
   * The following fields are always valid.  When the database is copied
   * from the file, the assigned flag is the only flag that is valid, all
   * other flags are cleared (set to zero).
   */

  union {
    u_int rflags;			/* Run-time flags */
    struct {
      unsigned assigned  : 1;		/* This device ID is assigned */
      unsigned dev_found : 1;		/* A device was found */
      unsigned pd_spec_alloc : 1;	/* Allocating a PD spec structure */
      unsigned being_deleted : 2;	/* Trying to delete this DID */
    } rflags_st;
    struct {
      unsigned char filler[2];          /* pad */
      unsigned char async_count;        /* outstanding async callbacks */
      unsigned char probe_count;        /* outstanding probe operations */
    } rflags_counts;
  } rflags_un;

  u_int			device_id;	/* Device ID */
  XPT_LOCK_DATA 	did_lock;	/* Lock structure for this did */

  PD_SPEC_INFO		pd_spec_list;	/* PD-specific data structs */

  /*
   * The following fields are only valid if assigned = 1.  These fields are
   * owned by camdb.  The xpt/common software may read these fields; but
   * may not write to them.
   */

  u_int			dev_type;	/* Type of device (current) */
  u_int			dev_subtype;	/* SubType of device (current) */
  u_int			num_path;	/* Number of paths in the list */
  SCSI_PATH		pathq;		/* List of paths, the first (which
					   is embedded) is the primary */

  u_int			pd_lockowner;	/* PD which has the exclusive lock */
  u_int			reserved[11];	/* Reserved for expansion */

#if defined(_KERNEL)
  CAM_EDT_ENTRY		*edt_entry;	/* pointer to old EDT entry */   
#else
  char			*edt_entry;	/* but it's only for the kernel */
#endif

  DS_PTR		wwid_kds_ptr;	   /* Unique ID info */
  DS_PTR		user_wwid_kds_ptr; /* User-specified Unique ID info */
} SCSI_DID;

/* 
 * Lock flags for working with SCSI_DID 
 */
#define DID_LOCKED         1  /* DID locked at entry   */
#define DID_UNLOCKED       0  /* DID unlocked at entry */
#define DID_LOCK_ON_EXIT   2  /* Lock DID on exit      */
#define DID_UNLOCK_ON_EXIT 0  /* Unlock DID on exit    */

/* dev_subtype values */
#define SCSI_DEV_FLOPPY     0x01	/* Device is a floppy */

/*
 * Tear down PD spec pointers, unregister from EHM but do not erase the
 * information in the SCSI_DID structure.
 */
#define SCSI_DID_SOFT_DELETE 0x0001 
/*
 * The device is being removed completely.  Erase the SCSI_DID upon
 * completion.
 */
#define SCSI_DID_HARD_DELETE 0x0002


/*
 * locking macros for SCSI_DID
 */
#define INIT_SCSI_DID_LOCK( scsi_did )                      	\
{								\
    XPT_INIT_LOCK( &(scsi_did)->did_lock, scsi_did_li );	\
}

#define SCSI_DID_LOCK( scsi_did )     		\
{						\
    XPT_LOCK( &(scsi_did)->did_lock );		\
}

#define SCSI_DID_UNLOCK( scsi_did )		\
{						\
    XPT_UNLOCK( &(scsi_did)->did_lock );	\
}

/* ---------------------------------------------------------------------- */

/*
 * Device ID array data structure.  This data structure is an array of
 * device ID structures.  The first instance of this array will be for
 * device IDs 0 through 63.  The second instance of this array will be
 * for device IDs 64 through 127.  The cam sub-system will allocate a new
 * device ID array when all the existing arrays are full and another
 * device needs to be included in the database.
 *
 * These arrays are used to hold the information about a SCSI device.
 * The information in these arrays is what is used to translate a SCSI
 * device ID (which is retrieved from the minor number of a dev_t) to a
 * SCSI physical address (bus, target, lun); also known as a path.  This
 * translation information must be preserved across boots so that the
 * device special files (which hold the dev_t value) will continue to
 * function across boots.
 *
 * If there are multiple paths that can be used to access a device, this
 * structure allows for the multiple paths to be available.  For each device
 * ID, there is a primary path and zero to many alternate paths.
 *
 * Note that this data structure does not contain the standard database
 * header (DS_HDR).  This is because this data structure will be contained
 * within a larger data structure.  And that larger data structure will
 * contain the standard database header.
 */

typedef struct scsi_didarr
{
  SCSI_DID				/* Array of device IDs */
         did[SCSI_DID_PER_ARR];
} SCSI_DIDARR;

/* RK01
 * To facilitate fast translation from physical to logical ID additional
 * structure is defined. Structure points to SCSI_PATH record based on
 * T_L nexus. One table exists for each possible SCSI bus. Pointers to
 * SCSI_PATH_PTR_TABLE are stored in global array camdb_TL_ptr_table.
 * SCSI_PATH_PTR_TABLE is allocated dynamically for each existing SCSI bus
 * in the system.
 */

#define CAMDB_TARGETS	 8
#define CAMDB_LUNS	 8
#define CAMDB_BUSSES	64

typedef struct scsi_path_ptr_table {
    SCSI_PATH	*did_ptr[CAMDB_TARGETS][CAMDB_LUNS];
} SCSI_PATH_PTR_TABLE;

/* ---------------------------------------------------------------------- */

/*
 * Device ID database data structure.  This data structure will contain the
 * device ID array data structure.  And it will also include the standard
 * database header and an array of pointers (one for the path pointer in
 * each device ID entry in the device ID array).
 *
 * The device ID array and this structure are separately defined because
 * the device ID array (within this data structure) will be pointed to by
 * an array.  This is done for quick access to the device entries.
 * However, since these device ID arrays still need to be in the on-disk
 * database, we need to also have a standard database header.  So this
 * data structure is the real data structure; it is the one that will
 * exist in the on-disk database and will exist in the in-memory database.
 * But the array (SCSI_DIDARR) data structure that is embedded within this
 * data structure will NOT be accessed through this data structure.
 * Instead, the array will be accessed through the array of pointers.
 *
 * A series of picture is supplied for an easier explanation.
 *
 * When the database is brought in from the disk and connected together to
 * form the in-memory database, it will look like the following.  For this
 * example, there are two SCSI_DIDDB data structures in this database.  We
 * could have many of these data structures, but at this time in this
 * example we only have two.  These two SCSI_DIDDB data structures (at this
 * time) are in a linked list that starts at the scsi_ptr_diddb field of
 * the SCSI database.  Remember that the SCSI_DIDDB data structures each
 * have a SCSI_DIDARR data structure embedded in them.
 *
 *         SCSI_DATABASE
 *         +--------+
 *         |        |
 *         |        |
 *         |        |
 *         |        |           SCSI_DIDDB
 *  scsi_ptr_diddb ----------->+-----------+          SCSI_DIDDB
 *         |        |          |   ----------------->+-----------+
 *         |        |          |           |         |     0     |
 *         |        |          |SCSI_DIDARR|         |           |
 *         |        |          |           |         |SCSI_DIDARR|
 *         +--------+          |           |         |           |
 *                             +-----------+         |           |
 *                                                   +-----------+
 *
 * After the in-memory database has been connected (as shown above), the
 * SCSI database code will further initialize the database.  Part of this
 * initialization is to allocate and initialize an array of pointers to
 * each of the SCSI_DIDARR structures that are in each of the SCSI_DIDDB
 * data structures.  This is done for quick access to these arrays.  Once
 * this initialization is done, the database will look like the following.
 *
 *         SCSI_DATABASE
 *         +--------+
 *         |        |
 *         |        |
 *         |        |
 *         |        |           SCSI_DIDDB
 *  scsi_ptr_diddb ----------->+-----------+          SCSI_DIDDB
 *         |        |          |   ----------------->+-----------+
 *         |        |          |           |         |     0     |
 *         |        |   +----->|SCSI_DIDARR|         |           |
 *         +--------+   |      |           |   +---->|SCSI_DIDARR|
 *                      |      |           |   |     |           |
 *                      |      +-----------+   |     |           |
 * camdb_didarr_ptr     |                      |     +-----------+
 *         +--------+   |                      |
 *     [0] |    --------+                      |
 *     [1] |    -------------------------------+
 *     [2] |    0   |
 *         |   etc  |
 *         |        |
 *         +--------+
 *
 * The SCSI database code will need to get to an entry in the correct
 * SCSI_DIDARR data structure quickly and often.  So the SCSI database code
 * will use the camdb_didarr_ptr array to get the correct SCSI_DIDARR
 * structure.  The linked list of SCSI_DIDDB structures will not be used
 * by the SCSI database code very often.
 */

typedef struct scsi_diddb
{
  DS_HDR did_hdr;			/* Data structure header */
  int    path_off[SCSI_DID_PER_ARR];	/* Offset to the path pointer in
					   each SCSI_DID entry */
  int    wwid_off[SCSI_DID_PER_ARR];	/* Offset to the wwid pointer in
					   each SCSI_DID entry */
  int    user_wwid_off[SCSI_DID_PER_ARR];/* Offset to the wwid pointer in
					   each SCSI_DID entry */
  SCSI_DIDARR	didarr;			/* Array of device IDs */
} SCSI_DIDDB;

/* ---------------------------------------------------------------------- */

/*
 * SCSI database data structure.  There will only be one of these data
 * structures in memory (or in the on-disk copy of the database) at any
 * given time.  This is the main SCSI data structure.  From this one data
 * structure, the entire SCSI database can be reached.
 */

typedef struct scsi_database
{
#define SCSIDB_VERSION		3	/* version/format # of database */

  DS_HDR scsi_hdr;			/* Data structure header */
  u_int  scsi_off_didarr2;		/* Offset to scsi_ptr_didarr */
  u_int  scsi_off_prvt;			/* Offset to scsi_ptr_prvt */
  u_int  scsi_prvt_flags;		/* Flags for the SCSI manager */
  u_int  version;			/* Database version number */
  DS_PTR scsi_ptr_diddb;		/* List of SCSI_DIDDB structures; to
					   preserve the device IDs used in
					   the minor numbers */
  DS_PTR scsi_ptr_prvt;			/* List of SCSI manager private data
					   structures */
} SCSI_DATABASE;

/* ---------------------------------------------------------------------- */

/*
 * This section described which fields in the SCSI request data structures
 * are initialized by the SCSI Utility (U) and the SCSI Database (D).
 *
 *             0       flags
 *             1       d_id    d_sflags   d_type   num_paths ppath   apath
 *             2       bus     target
 *             3       ds_num  ptr_num                       ds
 *             4       devt    drv_op
 *             type
 * -----------------------------------------------------------------------
 * GETINFO     0       D
 * ADDDEV      1       D       U          U        U         U       U
 * DELDEV      1       U                  U
 * ADDPATH     1       U                           U                 U
 * DELPATH     1       U                           U                 U
 * SCANALL     2
 * SCANBUS     2       U
 * SCAN_B_T    2       U       U
 * SCAN_B_T_L  2       U       U
 * REFRESH_ALL 2       U       
 * REFRESH_BUS 2       U
 * REFRESH_LID 2       U
 * MVLID       3       U                  U
 * SET_WWID    2       U
 */

/* ---------------------------------------------------------------------- */

/*
 * SCSI datbase request function codes.  These function codes will be used
 * by the SCSI management utility when making requests to the SCSI kernel
 * database.
 */

#define SCSI_FC_GETINFO		0	/* Get information */
#define SCSI_FC_ADDDEV		1	/* Add a device */
#define SCSI_FC_DELDEV		2	/* Delete a device */
#define SCSI_FC_ADDPATH		3	/* Add an alternate path */
#define SCSI_FC_DELPATH		4	/* Delete an alternate path */
#define SCSI_FC_SCANALL		5	/* Scan all buses */
#define SCSI_FC_SCANBUS		6	/* Scan a bus */
#define SCSI_FC_SCAN_B_T	7	/* Scan an address */
#define SCSI_FC_SCAN_B_T_L	8	/* Scan an address */
#define SCSI_FC_PRINT		9	/* Scan an address */
#define SCSI_FC_MVLID           10      /* Move logical ID */
#define SCSI_FC_REFRESH_ALL     11      /* Refresh all paths */
#define SCSI_FC_REFRESH_BUS     12      /* Refresh paths on bus */
#define SCSI_FC_REFRESH_LID     13      /* Refresh paths on a device (lid) */
#define SCSI_FC_SET_WWID	14	/* Set user-settable wwid */

#define SCSI_FC_MAX		14	/* Maximum legal function code */

/* ---------------------------------------------------------------------- */

/*
 * SCSI request data structures.  These data structures will be used to pass
 * information between the SCSI kernel database and the SCSI management
 * utility.  There are multiple data structure formats here for the different
 * types of requests.
 */

typedef struct scsi_req0
{
  KDS_REQ kdsreq;			/* KDS generic fields */
  int flags;				/* Flags */
  int spare1;				/* Reserved for future (init to 0) */
  int spare2;				/* Reserved for future (init to 0) */
  int spare3;				/* Reserved for future (init to 0) */
  int spare4;				/* Reserved for future (init to 0) */
  int spare5;				/* Reserved for future (init to 0) */
} SCSI_REQ0;

/*
 * These are the flag values for scsi_req0.flags.
 */

#define SCSI_GI_INITED		1	/* CAM is initialized */
#define SCSI_GI_OOMODE		2	/* Running in old-only mode */
#define SCSI_GI_DBPRIM		4	/* Database read from primary file */
#define SCSI_GI_DBBACK		8	/* Database read from backup file */

typedef struct scsi_req1
{
  KDS_REQ kdsreq;			/* KDS generic fields */
  int d_id;				/* Device ID */
  int d_sflags;				/* Device special flags */
  int d_type;				/* Device type (0 to 15) */
  int num_paths;			/* Number of paths specified */
  int spare4;				/* Reserved for future (init to 0) */
  int spare5;				/* Reserved for future (init to 0) */
} SCSI_REQ1;

typedef struct scsi_req2
{
  KDS_REQ kdsreq;			/* KDS generic fields */
  long   d_id;                          /* Device ID */
  long   bus;				/* Bus number */
  u_long target;			/* Target number */
  u_long lun;				/* Lun number */
  U32    change;			/* topology change indicator */
  int    spare4;			/* Reserved for future (init to 0) */
  int    spare5;			/* Reserved for future (init to 0) */
} SCSI_REQ2;

typedef struct scsi_req3
{
  KDS_REQ kdsreq;                       /* KDS generic fields */
  int id_original;                      /* Destination logical ID */
  int id_new;                           /* Source logical ID */
  int d_type;                           /* Devices type (0 to 15) */
  int spare4;                           /* Reserved for future (init to 0) */
} SCSI_REQ3;



#ifdef __cplusplus
}
#endif


#endif /* _CAM_DB_INCL_ */



