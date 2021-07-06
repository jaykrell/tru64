/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: ddr_defines.h,v $
 * Revision 1.1.25.2  2004/08/25  17:40:49  Joseph_Szczypek
 *      Fix for QAR 97617: Add DSBL_HIPRIOS_NOSENSE define which
 *      disables HIGH PRIORITY events being handled as NO SENSE.
 *      They will be handled by the PD as UNIT ATTENTIONS.
 *
 * Revision 1.1.25.1  2004/02/25  20:22:50  David_Schroeder
 * 	Fix for QAR 97599 - HSZ80s send ASCQ_LUN_NRDY_MAN on
 * 	controller failback event, this would cause us to
 * 	incorrectly fail the recovery. Added a ddr flag to disable
 * 	this behavior.
 * 	Add definition for DSBL bit to enable XP control port access
 *
 * Revision 1.1.22.1  2001/10/03  20:17:10  Jim_Goddard
 * 	Done as part of the parallel probe backport
 *  * Feature Tag: mo.upk_plat.002.starlight
 *  * Add VPD flag definition to control NILE protocol serial
 *  * number page request.  This is for support of the Compaq
 *  * Proliant Starlight/Starbright storage shelf.
 *  *
 *
 * Revision 1.1.9.1  2000/07/19  20:56:20  William_Dallas
 * 	Added defines that indicate that a BDR is issued for
 * 	an I/O Barrier instead of bus reset.
 *
 * Revision 1.1.4.1  2000/03/06  17:23:45  Jan_Reimers
 * 	Add DSBL_AXRE_BROKEN flag
 *
 * Revision 1.1.2.3  1999/05/28  19:27:37  Jamey_Poirier
 * 	Added a flag for HSZ CCL devices to the control flags.
 * 	[1999/05/28  19:20:26  Jamey_Poirier]
 *
 * Revision 1.1.2.2  1999/03/21  03:34:56  John_Meneghini
 * 	Initial Checkin
 * 	[1999/03/17  18:58:19  John_Meneghini]
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: ddr_defines.h,v $ $Revision: 1.1.25.2 $ (DEC) $Date: 2004/08/25 17:40:49 $
 */
#ifndef _DDR_DEFINES_INCL_
#define _DDR_DEFINES_INCL_

/* ---------------------------------------------------------------------- */

/* Structure definitions used within the ccfg code. */

typedef struct ccfg_vpd_info
{
  unsigned char	lun0_only; /* lun 1+ are broken, so don't even try	*/
  unsigned char	novpd;		/* don't use any vpd page		*/
  unsigned char	use_page;	/* force this specific VPD page		*/
  unsigned char	page_offset;	/*   at this offset for VU SN		*/
  unsigned char	page_length;	/*   and this length (0 = all)		*/
				/* If novpd is set, page_offset/length	*/
				/* are within the standard inq data.	*/
				/* If use_page is set, page_offset/	*/
				/* length are in the specified page	*/
  unsigned char	append_dbtl;	/* Append type/bus/target/lun to VPD	*/
				/*   bit 0 = lun			*/
				/*   bit 1 = target			*/
				/*   bit 2 = bus			*/
				/*   bit 3 = dtype			*/
  unsigned char	control_flags;	/* Various control flags (see below).	*/
  unsigned char reserved0_7;
  unsigned char	sd_version;	/* HSZ minimum version level if version
				   is less than this number use send_diag */
  unsigned char	reserved1_1;
  unsigned char	reserved1_2;
  unsigned char	reserved1_3;
  unsigned char	reserved1_4;
  unsigned char	reserved1_5;
  unsigned char	reserved1_6;
  unsigned char	reserved1_7;
} CCFG_VPD_INFO;

/*
 * Flags for Append "dbtl" Field:
 */
#define VPD_APPEND_LUN		0x01	/* Append target LUN.		*/
#define VPD_APPEND_TARGET	0x02	/* Append target ID.		*/
#define VPD_APPEND_BUS		0x04	/* Append bus number.		*/
#define VPD_APPEND_DTYPE	0x08	/* Append device type.		*/
#define VPD_APPEND_MASK		0x0F	/* Mask of append valid bits.	*/

/*
 * Control Flag Definitions:
 */
#define VPD_REPORT_LUN_DISABLE	0x01	/* Don't issue REPORT LUN cmd.	*/
#define VPD_HSZ_T_O		0x02	/* Use HSZ this/other mapping	*/
#define VPD_START_UNIT_DISABLE  0x04    /* Don't issue START-UNIT cmd.  */
#define VPD_HSZ_CCL             0x08    /* This is an HSZ CCL device.   */
#define VPD_NILE_PROTOCOL	0x10	/* Enable NILE protocol cmds.	*/
#define VPD_XP_CCL              0x20    /* This is an XP CCL device.    */

/* ---------------------------------------------------------------------- */

/* Definitions used with general purpose DSBLflags ddr attribute */

typedef unsigned int DSBL_FLAGS_INFO;

/* DDR attribute "DSBLflags" bit meanings */

#define DSBL_PR_FLAG       0x00000001   /* Disable Persistent Reservations */
#define DSBL_DSKMON_FLAG   0x00000002   /* Disable Disk Monitoring         */
#define DSBL_MUNSA_FLAG    0x00000004   /* Disable MUNSA support           */
#define DSBL_AXRE_BROKEN   0x00000008	/* AWRE/ARRE bits are broken in
					   the device, but they really on  */
#define DSBL_RESET_BARRIER 0x00000010	/* For multi-controller boxes that
					   do not pass bus resets on to 
					   other bus (parallel buses). 
					   Issues a BDR instead of BR	   */
#define DSBL_NRDY_MAN_FAIL 0x00000020   /* This bit disables failing 
                                           recovery immediately on 
                                           ASCQ_LUN_NRDY_MAN so that 
                                           retries can be attempted        */
#define DSBL_HIPRIOS_NOSENSE 0x00000040 /* This bit disables HI PRIORITY
                                           events being handled as NO SENSE.
                                           They will be handled by the PD
                                           as UNIT ATTENTIONS.             */ 
#endif /* _DDR_DEFINES_INC */








