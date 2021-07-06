/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: cam_logger.h,v $
 * Revision 1.1.60.1  2002/10/08  20:41:40  Bruce_Hansen
 * Merge Information:  Non-Visual Merge: User specified tree v51asupportos.nightly
 *     User Revision:  v51bsupportos_nightly:1.1.55.3 Local Ancestor: n/a
 *    Merge Revision:  v51asupportos_nightly:1.1.53.4
 *   Common Ancestor:  1.1.53.3
 * 	Merge up to v51asupport.nightly
 *
 * Revision 1.1.53.4  2002/09/23  17:23:53  Steve_Feeley
 * 	QAR 94943. Add CAM_ERR_EXPRESS flag. This is used in
 * 	conjunction with SIM_LOG_PRISEVERE or SIM_LOG_PRIHIGH
 * 	to allow writing binlog entries during boot.
 * 
 * Revision 1.1.53.3  2002/08/05  19:33:01  Bob_Breau
 * 	Backport from wcalphaos
 * 	***
 * 	The following modification has been backported:
 * 	 Revision 1.1.55.3  2002/05/30  23:15:18  Ashoke_Rampuria
 * 	      Changes for compiler switch project
 * 	***
 * 
 * Revision 1.1.55.3  2002/05/30  23:15:18  Ashoke_Rampuria
 * 	Changes for compiler switch project
 * 
 * Revision 1.1.55.2  2002/01/29  22:30:15  Matt_Oquist
 * 	Added prototype for cam_logger3() interface to resolve problems
 * 	incurred when the hardware id was added to the parameter list for
 * 	cam_logger().  The cam_logger() prototype was restored to its
 * 	former state, with no hardware id in the parameter list.
 * 
 * Revision 1.1.53.2  2002/01/23  15:05:54  Matt_Oquist
 * 	Added prototype for cam_logger3() interface to resolve problems
 * 	incurred when the hardware id was added to the parameter list for
 * 	cam_logger().  The cam_logger() prototype was restored to its
 * 	former state, with no hardware id in the parameter list.
 * 
 * Revision 1.1.55.1  2001/11/01  20:48:50  Cheryl_Deleo
 * 	Merge of v51asupportos-127-deleo which provides
 * 	support for V1.0 of the CISS (Smart Array) driver.
 * 
 * Revision 1.1.53.1  2001/10/01  14:47:27  Cheryl_Deleo
 * 	Add CISS (Smart Array) controller class, subsystem,
 * 	and frame.
 * 
 * Revision 1.1.36.2  2001/02/27  18:49:56  Dennis_Paradis
 * 	Added AHA_CHIM driver error logging support.
 * 
 * Revision 1.1.36.1  2000/11/09  22:36:41  Carolyn_Briglia
 * 	cpu hotswap support
 * 
 * Revision 1.1.34.1  2000/11/09  18:42:50  Mark_Bokhan
 * Merge Information:  Non-Visual Join Merge: Join_add
 *     User Revision:  yankeeos_nightly:1.1.25.6
 *        Join Merge:  From:1.1.25.6_Upto:1.1.33.1
 * 
 * Revision 1.1.33.1  2000/10/16  19:56:52  Mark_Bokhan
 * 	Add hardware ID to CAM binlog entries.  This enables enhanced
 * 	analysis capabilities by accurately tracking CAM/SCSI devices.
 * 
 * Revision 1.1.25.6  1998/10/02  19:22:31  Fred_Knight
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTEV6OS_BL6:PTEV6OS_BL8 **
 * 		** Ancestor revision:	1.1.27.3 **
 * 		** Merge revision:	1.1.27.4 **
 * 	 	** End **
 * 	[1998/10/02  19:16:31  Fred_Knight]
 * 
 * Revision 1.1.25.5  1998/08/05  19:08:32  Fred_Knight
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTEV6OS_BL4:PTEV6OS_BL6 **
 * 		** Ancestor revision:	1.1.22.2 **
 * 		** Merge revision:	1.1.27.3 **
 * 	 	** End **
 * 	[1998/08/05  17:53:46  Fred_Knight]
 * 
 * Revision 1.1.27.4  1998/07/23  13:23:17  Fred_Knight
 * 	Define isp values so those adapters don't look like disk errors
 * 	(which are 0) when they should really be adapter errors.
 * 	[1998/07/22  15:56:28  Fred_Knight]
 * 
 * Revision 1.1.27.3  1998/06/25  18:30:44  Rama_Karedla
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.22.2 **
 * 		** Merge revision:	1.1.27.2 **
 * 	 	** End **
 * 	     Added ENT_SIMITI_REG definition for ITI driver
 * 	[1998/06/23  23:50:09  Rama_Karedla]
 * 	Add itpsa error type defines.
 * 	[1998/04/30  21:03:16  Rama_Karedla]
 * 
 * Revision 1.1.27.2  1998/05/01  19:38:43  Rama_Karedla
 * 	Add itpsa error type defines.
 * 	[1998/04/30  21:03:16  Rama_Karedla]
 * 
 * Revision 1.1.25.4  1997/09/08  23:27:02  Robin_Miller
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL6:PTCOS_BL10 **
 * 		** Ancestor revision:	1.1.14.3 **
 * 		** Merge revision:	1.1.22.2 **
 * 	 	** End **
 * 	merge of PTmin BL10 changes
 * 	[1997/09/08  23:22:58  Robin_Miller]
 * 
 * Revision 1.1.25.3  1997/03/03  15:34:01  Robin_Miller
 * 	Added function prototype for cam_logger().
 * 	Remove old ULTRIX modification history.
 * 	Add C++ begin/end declartions blocks.
 * 	[1997/03/03  14:58:44  Robin_Miller]
 * 
 * Revision 1.1.25.2  1997/02/11  15:08:27  Jan_Reimers
 * 	include binlog.h and define CAM_ERR_PKT in terms of what is already
 * 	defined in binlog.h (QAR 48521)
 * 	[1997/01/31  15:24:13  Jan_Reimers]
 * 
 * Revision 1.1.22.2  1997/01/10  00:21:36  Fred_Knight
 * 	Add ATA/EIDE sim.
 * 	[1997/01/09  21:38:02  Fred_Knight]
 * 
 * Revision 1.1.14.3  1994/02/25  21:22:20  Stuart_Hollander
 * 	merge agoshw2 bl3 to gold
 * 	Revision 1.1.16.2  1994/02/02  13:53:40  John_Gallant
 * 	Added PCI SIOP (NCR 53C810) error log definitions.
 * 	[1994/01/20  15:51:37  John_Gallant]
 * 
 * Revision 1.1.14.2  1994/01/10  16:32:16  Theresa_Chin
 * 	Modified TZA specific definitions to SIMport common ones.
 * 	[1993/12/03  15:41:07  Theresa_Chin]
 * 
 * Revision 1.1.10.3  1993/08/13  20:46:54  Kuo_Hsieh
 * 	Added TZA adapter specific error support.
 * 	[1993/07/07  22:09:03  Kuo_Hsieh]
 * 
 * Revision 1.1.10.2  1993/06/24  22:36:53  Randall_Brown
 * 	Submit of AGOSHW pool into Sterling
 * 	[1993/06/24  21:18:45  Randall_Brown]
 * 
 * Revision 1.1.5.5  1993/05/24  19:19:57  Theresa_Chin
 * 	Added support for AHA1740 adapter HBA driver.
 * 	[1993/05/21  18:10:40  Theresa_Chin]
 * 
 * Revision 1.1.5.4  1993/01/06  15:33:26  Timothy_Burke
 * 	Jensen BL9 to BL11 merge.
 * 	[93/01/06  15:31:50  Timothy_Burke]
 * 
 * Revision 1.1.3.4  92/11/19  17:15:26  John_Gallant
 * 	The TCDS DME defines have been added.
 * 	[92/11/19  16:07:43  John_Gallant]
 * 
 * Revision 1.1.5.3  92/11/17  09:32:33  Paul_Grist
 * 	Re-submit correct file with aha support
 * 	[92/11/17  09:31:11  Paul_Grist]
 * 
 * Revision 1.1.5.2  92/11/16  16:27:56  Paul_Grist
 * 	submit for jtw - Add aha support (adaptech 1742 eisa)
 * 	[92/11/16  15:56:02  Paul_Grist]
 * 
 * Revision 1.1.3.3  92/06/26  16:45:03  Jim_Campbell
 * 	Silver BL8_1 mirror: move alpha-ize header from sys to io/cam
 * 	[92/06/26  15:24:23  Jim_Campbell]
 * 
 * Revision 1.1.3.5  92/04/17  12:01:54  Ronald_Hegli
 * 	Added XZA-specific error entry define's for LASER/Ruby.
 * 	[92/04/17  12:01:05  Ronald_Hegli]
 * 
 * Revision 1.1.3.2  92/03/18  18:44:00  Al_Delorey
 * 	From Silver: AG_BL5
 * 	[92/03/18  16:54:45  Al_Delorey]
 * 	Made 64bit modifications
 * 	[92/01/31  10:03:55  Janet_Schank]
 * 	Merged in changes from LA.
 * 	[92/01/28  18:10:57  Janet_Schank]
 * 	Added CAM support
 * 	[92/01/17  15:25:26  Janet_Schank]
 * 
 * Revision 1.1.1.2  92/03/17  16:18:41  devbld_gsf
 * 	First AG_BL5 version.  Moved from Ag baselevel delivery tree.
 * 
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: cam_logger.h,v $ $Revision: 1.1.60.1 $ (DEC) $Date: 2002/10/08 20:41:40 $
 */
#ifndef _CAM_LOGGER_
#define _CAM_LOGGER_

/* ---------------------------------------------------------------------- */
 
/* cam_logger.h		Version 1.05			Nov. 15, 1991

This file contains all the defines that the CAM sub-system uses to log
errors. 

*/

#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------------------------------------------- */

/* Include Files	*/
#include <dec/binlog/binlog.h>

/* ---------------------------------------------------------------------- */


/* Structure definitions	*/

/*
 * The error entry struct describes a data type (string, sii regs
 * sim working set struct etc). There can be multiple error entries 
 * per packet.
 */
typedef struct cam_err_entry {
    U32		ent_type;	/* String, TAPE_SPECIFIC, CCB, etc */
    U32		ent_size; 	/* Size of the data (CCB, TAPE_SEPC)*/
    U32		ent_total_size; /* To preserve alignment (uerf) */
    U32		ent_vers;	/* Version number of type.	*/
    void	*ent_data;	/* Pointer to whatever string etc */
    U32		ent_pri;	/* FULL or Brief uerf output	*/
}CAM_ERR_ENTRY;


/*
 * The cam error header contains all the data need by uerf to determine
 * that this is a cam error log packet.
 */

typedef struct cam_err_hdr {
    u_short	hdr_type;		/* Packet type - CAM_ERR_PKT	*/
    U32		hdr_size;		/* Filled in by cam_logger 	*/
    u_char	hdr_class;		/* Sub system class Tape, disk,
					 * sii_dme , etc..
					 */
    U32		hdr_subsystem;		/* 
					 * Mostly for controller type
					 * But the current errloger uses
					 * disk tape etc if no controller
					 * is known.. So what we will do
					 * is dup the disk and tape types
					 * in the lower number 0 - 1f and
					 * the controllers asc sii 5380
					 * etc can use the uppers.
					 */
    U32		hdr_entries;		/* Number of error entries in list*/
    CAM_ERR_ENTRY *hdr_list;		/* Pointer to list of error entries*/
    U32		hdr_pri;		/* Error logger priority.	*/
}CAM_ERR_HDR;


/* ---------------------------------------------------------------------- */

/*
 * General purpose define for no Error logger value.
 */

#define NO_ERRVAL	-1


/* Defines for CAM_ERR_HDR	*/

/* 
 * CAM_ERR_HDR.hdr_type defines	
 * There is only 1 type CAM_ERR_PKT. This tells an application reading
 * the binary error log, such as uerf or DECevent, that a CAM
 * error or informational packet is in the log.
 */
#define CAM_ERR_PKT	ELCT_CAM_ERRPKT	/* Defined in binlog.h */

/*
 * CAM_ERR_HDR.hdr_class defines.
 * This field id's which part of cam detected the error...
 * Tape, disk, dme, sim_sii etc. Please note that 0 - 1F  are
 * reserved for SCSI devices..........
 */

#define CLASS_DISK ALL_DTYPE_DIRECT		/* 0x00			*/
#define CLASS_TAPE ALL_DTYPE_SEQUENTIAL		/* 0x01			*/
#define CLASS_PRINTER ALL_DTYPE_PRINTER		/* 0x02			*/
#define CLASS_PROCESSOR ALL_DTYPE_PROCESSOR	/* 0x03			*/
#define CLASS_WORM ALL_DTYPE_WORM      		/* 0x04			*/
#define CLASS_RODIRECT ALL_DTYPE_RODIRECT 	/* 0x05			*/
#define CLASS_SCANNER ALL_DTYPE_SCANNER 	/* 0x06			*/
#define CLASS_OPTICAL ALL_DTYPE_OPTICAL		/* 0x07			*/
#define CLASS_MEDIA_CHANGER ALL_DTYPE_CHANGER  	/* 0x08			*/
#define CLASS_COMM ALL_DTYPE_COMM    		/* 0x09			*/
#define CLASS_UNKNOWN ALL_DTYPE_NONE   		/* 0x1f			*/
#define CLASS_SIM94			0x20	/* ASC (94) controller	*/
#define CLASS_SII			0x21	/* SII Chip		*/
#define CLASS_DEC_SIM			0x22	/* DEC SIM error	*/
#define CLASS_XPT			0x23	/* CAM Transport layer  */
#define CLASS_CCFG			0x24	/* CAM Config layer     */
#define CLASS_KZQ			0x25    /* KZQ controller       */
#define CLASS_DME			0x26	/* CAM DME layer	*/
/* ADD your classes here	*/
#define CLASS_SIOP			0x30	/* Cobra SIOP controllers */
#define CLASS_XZA			0x31	/* LASER/Ruby XZA/SCSI	  */
#define CLASS_AHA			0x32	/* AHA 1740A controllers  */
#define CLASS_SIMPORT                   0x33    /* SIMPORT adapter	  */
#define CLASS_TZA                       0x34    /* TurboChannel TZA/SCSI  */
#define	CLASS_SIMATA			0x35	/* ATA/EIDE adapter	  */
#define	CLASS_SIMITI			0x36	/* ITI adapters		  */
#define CLASS_SIMISP			0x37	/* ISP adapter errors	  */
#define CLASS_AHA_CHIM			0x38	/* AHA_CHIM adapters      */
#define CLASS_CISS                      0x39    /* CISS adapters/ctrlrs   */


/*
 * CAM_ERR_HDR.hdr_subsystem
 */
#define SUBSYS_DISK ALL_DTYPE_DIRECT		/* 0x00			*/
#define SUBSYS_TAPE ALL_DTYPE_SEQUENTIAL	/* 0x01			*/
#define SUBSYS_PRINTER ALL_DTYPE_PRINTER	/* 0x02			*/
#define SUBSYS_PROCESSOR ALL_DTYPE_PROCESSOR	/* 0x03			*/
#define SUBSYS_WORM ALL_DTYPE_WORM      	/* 0x04			*/
#define SUBSYS_RODIRECT ALL_DTYPE_RODIRECT 	/* 0x05			*/
#define SUBSYS_SCANNER ALL_DTYPE_SCANNER 	/* 0x06			*/
#define SUBSYS_OPTICAL ALL_DTYPE_OPTICAL	/* 0x07			*/
#define SUBSYS_MEDIA_CHANGER ALL_DTYPE_CHANGER  /* 0x08			*/
#define SUBSYS_COMM ALL_DTYPE_COMM    		/* 0x09			*/
#define SUBSYS_UNKNOWN ALL_DTYPE_NONE   	/* 0x1f			*/
#define SUBSYS_SIM94			0x20	/* ASC (94) controller	*/
#define SUBSYS_SII			0x21	/* SII Chip		*/
#define SUBSYS_DEC_SIM			0x22	/* DEC SIM error	*/
#define SUBSYS_XPT			0x23	/* CAM Transport layer  */
#define SUBSYS_CCFG			0x24	/* CAM Config layer     */
#define SUBSYS_KZQ			0x25    /* KZQ controller       */
#define SUBSYS_3MIN_DME			0x26    /* CAM IOASIC/DMA DME	*/
#define SUBSYS_TCDS_DME			0x27    /* CAM TCDS/DMA DME	*/
/* ADD  5380 HERE */
#define SUBSYS_SIOP                     0x30    /* SIOP controllers     */
#define SUBSYS_XZA			0x31	/* LASER/Ruby XZA/SCSI 	*/
#define SUBSYS_AHA                      0x32    /* AHA 1740A controller */
#define SUBSYS_SIMPORT                  0x33    /* SIMPORT adapter      */
#define SUBSYS_TZA                      0x34    /* TurboChannel TZA/SCSI*/
#define	SUBSYS_SIMATA			0x35	/* ATA/EIDE sim adapter	*/
#define	SUBSYS_SIMITI			0x36	/* ITI adapters		*/
#define SUBSYS_SIMISP			0x37	/* ISP adapter errors	*/
#define SUBSYS_AHA_CHIM			0x38	/* AHA_CHIM adapter     */
#define SUBSYS_CISS                     0x39    /* CISS adapters/ctrlrs */


/* 
 * CAM_ERR_HDR.hdr_pri defines....
 * The Priority define is how we allocate and report the error event.
 * CAM_ERR_SEVERE - nasty panics, controller parity errors, no recovery.
 * CAM_ERR_HIGH - Hard errors, but recovery
 * CAM_ERR_LOW - Informational messages.
 * CAM_ERR_EXPRESS - Write error log when binlog is not ready i.e. boot. 
 */

#define CAM_ERR_SEVERE	EL_PRISEVERE
#define CAM_ERR_HIGH	EL_PRIHIGH
#define CAM_ERR_LOW	EL_PRILOW
#define CAM_ERR_EXPRESS ((U32)0x00040000)  /* value equal to SIM_LOG_EXPRESS */ 

/*
 * CAM_ERR_ENTRY defines
 */

/*
 * CAM_ERR_ENTRY.ent_type defines
 */
/* CCB types */
#define ENT_CCB_NOOP		XPT_NOOP	/* 0x00			*/
#define ENT_CCB_SCSIIO		XPT_SCSI_IO	/* 0x01			*/
#define ENT_CCB_GETDEV  	XPT_GDEV_TYPE	/* 0x02			*/
#define ENT_CCB_PATHINQ 	XPT_PATH_INQ	/* 0x03			*/
#define ENT_CCB_RELSIM		XPT_REL_SIMQ	/* 0x04			*/
#define ENT_CCB_SETASYNC	XPT_SASYNC_CB	/* 0x05			*/
#define ENT_CCB_SETDEV		XPT_SDEV_TYPE	/* 0x06			*/
#define ENT_CCB_ABORT		XPT_ABORT	/* 0x10 		*/
#define ENT_CCB_RESETBUS	XPT_RESET_BUS	/* 0x11			*/
#define ENT_CCB_RESETDEV	XPT_RESET_DEV	/* 0x12			*/
#define ENT_CCB_TERMIO		XPT_TERM_IO	/* 0x13			*/
#define ENT_CCB_ENG_INQ		XPT_ENG_INQ	/* 0x20			*/
#define ENT_CCB_ENG_EXEC	XPT_ENG_EXEC	/* 0x21			*/
#define ENT_CCB_EN_LUN		XPT_EN_LUN	/* 0x30			*/
#define ENT_CCB_TARGET_IO	XPT_TARGET_IO	/* 0x31			*/
/* 0x00 - 0xff for defined and future of ccb's */



/* 
 * There can be multiple types of strings.... This will allow the error
 * log formatter to make the output look nice.
 */
#define STR_START		0x00000100	/* Start string range	*/
#define ENT_STRING		0x00000100	/* Generic string	*/
#define ENT_STR_DEV		0x00000101	/* Device name string	*/
#define ENT_STR_MODULE		0x00000102	/* Module name string	*/
/*
 * ERROR type string hard soft software etc.
 */
#define ENT_STR_SOFTWARE_ERROR	0x00000103	/* Software error	*/
#define ENT_STR_HARD_ERROR	0x00000104	/* Hardware error	*/
#define ENT_STR_SOFT_ERROR	0x00000105	/* Soft error (recovered)*/
#define ENT_STR_INFOR_ERROR	0x00000106	/* Informational error	*/
#define ENT_STR_UNKNOWN_ERROR	0x00000107	/* Unknown error type	*/

#define STR_END			0x000001ff	/* END string range	*/
/* 108 - 1ff reserved for further expansion.	*/

#define ENT_SIMSII_REG		0x00000200	/* SII registers	*/
#define ENT_SIM94_REG		0x00000201	/* ASC registers	*/
#define ENT_SIMKZQ_REG		0x00000202      /* struct SIMKZQ_REGS   */
#define ENT_XZA_REG		0x00000203	/* XZA error-related regs */
#define ENT_DME_PHYADDR		0x00000204	/* IOASIC DME phys addr	*/
#define ENT_SIMITI_REG          0x00000205      /* ITI Registers        */
/* 206 - 2ff reserved for further expansion	*/

#define ENT_SENSE_DATA		0x00000300	/* Sense Data		*/
#define ENT_SCSI_STAT		0x00000301	/* SCSI Status		*/
/* 302 - 3ff reserved for further expansion	*/

/* Structure defines........ */
#define ENT_PDRV_WS		0x00000400	/* struct PDRV_WS 	*/
#define ENT_TAPE_SPECIFIC	0x00000401	/* TAPE_SPECIFIC struct */
#define ENT_DISK_SPECIFIC	0x00000402	/* DISK_SPECIFIC struct */
#define ENT_PDRV_DEVICE		0x00000403	/* PDRV_DEVICE struct	*/
#define ENT_BUF_BP		0x00000404	/* struct buf (buf.h)	*/
#define ENT_SII_INTR		0x00000405	/* struct SII_INTR	*/
#define ENT_SIMSII_SOFTC	0x00000406	/* struct SIMSII_SOFTC	*/
#define ENT_SCATTER_ELEMENT	0x00000407	/* struct SIMSII_SOFTC	*/
#define ENT_SEGMENT_BUFFER	0x00000408	/* struct SEGMENT_BUFFER*/
#define ENT_SEGMENT_ELEMENT	0x00000409	/* struct SEGMENT_ELEMENT*/
#define ENT_DME_DESCRIPTOR	0x0000040a	/* struct DME_DESCRIPTOR */
#define ENT_DME_STRUCT		0x0000040b	/* struct DME_STRUCT	*/
#define ENT_DME_PMAX_STRUCT	0x0000040c	/* struct DME_PMAX_STRUCT*/
#define ENT_IT_NEXUS		0x0000040d	/* struct IT_NEXUS	*/
#define ENT_SIM_WS		0x0000040e	/* struct SIM_WS	*/
#define ENT_NEXUS		0x0000040f	/* struct nexus		*/
#define ENT_SIM_SOFTC		0x00000410	/* struct SIM_SOFTC	*/
#define ENT_SIM_SM_DATA		0x00000411	/* struct SIM_SM_DATA	*/
#define ENT_SIM_SM		0x00000412	/* struct SIM_SM	*/
#define ENT_TAG_ELEMENT		0x00000413	/* struct TAG_ELEMENT	*/
#define ENT_SIM94_INTR		0x00000414	/* struct SIM94_INTR	*/
#define ENT_SIM94_SOFTC		0x00000415	/* struct SIM94_SOFTC	*/
#define ENT_CIR_Q		0x00000416	/* struct CIR_Q 	*/
#define ENT_HBA_DME_CONTROL	0x00000417	/* struct HBA_DME_CONTROL*/
#define ENT_XPT_WS		0x00000418	/* struct XPT_WS	*/
#define ENT_XPT_CTRL		0x00000419	/* struct XPT_CTRL	*/
#define ENT_DEC_CAM_PKT		0x0000041a	/* struct DEC_CAM_PKT	*/
#define ENT_CCFG_CTRL		0x0000041b	/* struct CCFG_CTRL	*/
#define ENT_CCFG_QHEAD		0x0000041c	/* struct CCFG_QHEAD	*/
#define ENT_EDT			0x0000041d	/* struct EDT		*/
#define ENT_XPT_QHEAD		0x0000041e	/* struct XPT_QHEAD	*/
#define ENT_CCFG_CONFTBL	0x0000041f	/* struct CAM CONF_TBL  */
#define ENT_KZQ_INTR		0x00000420      /* struct KZQ_INTR      */
#define ENT_SIMKZQ_SOFTC	0x00000421      /* struct SIMKZQ_SOFTC  */
#define ENT_DMA_WSET		0x00000422	/* struct DME DMA_WSET	*/
#define ENT_DME_DAT		0x00000423	/* struct DME DAT_ELEM	*/
#define ENT_DME_ATTCH		0x00000424	/* struct DME DAT_ATTCH	*/
/* Add your own here....... */
#define ENT_SIOP_SCRIPTHOST     0x00000430      /* SIOP scripthost      */
#define ENT_SIOP_SIOPJOB        0x00000431      /* SIOP siopjob         */
#define ENT_XZA_SOFTC		0x00000432	/* XZA softc 		*/
#define ENT_XZA_CHAN		0x00000433	/* XZA chan		*/
#define ENT_AHA_SOFTC           0x00000434      /* AHA softc            */
#define ENT_AHA_JOB             0x00000435      /* AHA JOB              */
#define ENT_SIMPORT_SOFTC       0x00000436      /* SIMPORT softc        */
#define ENT_SIMPORT_WS          0x00000437      /* SIMPORT working set  */
#define ENT_SIMPORT_REGS        0x00000438      /* SIMPORT registers    */
#define ENT_PSIOP_HOSTADDR	0x00000439	/* PCI SIOP host addr	*/
#define	ENT_SIMATA_SOFTC	0x0000043a	/* ATA/EIDE softc	*/
#define	ENT_SIMITI_SOFTC	0x0000043b	/* ITPSA softc struct	*/
#define ENT_AHA_CHIM_IOB	0x0000043c	/* AHA_CHIM OSMIOB      */
#define ENT_AHA_CHIM_FRAME	0x0000043d	/* AHA_CHIM Frame	*/
#define ENT_AHA_CHIM_TARGET	0x0000043e	/* AHA_CHIM TARGET	*/
#define ENT_CISS_FRAME          0x0000043f      /* CISS Frame           */


#define ENT_STRUCT_UNKNOWN	0xffffffff	/* Unknown structure 	*/



/*
 * CAM_ERR_ENTRY.ent_pri
 * Defines whether you always want to see when you run uerf or
 * only when you do a full error report
 */

#define PRI_BRIEF_REPORT	0x00000001
#define PRI_FULL_REPORT		0x00000002


/*
 * The peripherial drivers error types...
 */
#define CAM_INFORMATIONAL	0x00000001	/* Informational message */
#define CAM_SOFTERR		0x00000002	/* Soft error		 */
#define CAM_HARDERR		0x00000004	/* Hard error		 */
#define CAM_SOFTWARE		0x00000008	/* Software detected 	 */
#define CAM_DUMP_ALL		0x00000010	/* Dump all structures	 */

#if defined(_KERNEL) && defined(_USE_KERNEL_PROTOS)
extern void cam_logger(CAM_ERR_HDR *cam_err_hdr, char bus, 
		       char target, char lun);
extern void cam_logger3(CAM_ERR_HDR *cam_err_hdr, long hw_id,
		       char bus, char target, char lun);
#endif /* defined(_KERNEL) && defined(_USE_KERNEL_PROTOS) */

#ifdef __cplusplus
}
#endif
#endif /* _CAM_LOGGER_ */
