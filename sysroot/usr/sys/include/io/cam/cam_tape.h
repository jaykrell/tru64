/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: cam_tape.h,v $
 * Revision 1.1.83.4  2006/07/25  09:32:31  Venkata_Subbareddy
 * 	Added new sysconfig subsystem attribute ctape_preferred_path. Fix for
 * 	QAR# 99611.
 *
 * Revision 1.1.83.3  2006/02/14  09:06:42  Venkata_Subbareddy
 * 	This fix addresses a potential I/O performance bottleneck where the
 * 	tape driver may select the same path for all tape drives in a system
 * 	containing multiple HBAs and multiple tapes.  Now the tape driver can
 * 	assign different paths to different tape drives to improve tape I/O
 * 	performance. Fix for QIP Black & Decker preferred path (QAR# 87242).
 *
 * Revision 1.1.83.2  2004/10/28  20:17:29  Keith_Comeford
 * 	Fixing indentation issues as part of formal review PR 7245
 * 	of the changes for QAR 98260
 * 	[2004/10/28  13:50:51  Keith_Comeford]
 *
 * 	I am adding code that is analogous to that provided for
 * 	qar 97356 (et alia) for the changer. The issue is that
 * 	it is possible for the tape_specific local copies of
 * 	ts_trans and ts_path to be NULLed out by ctape_verify_path
 * 	while an I/O is still in progress. This results in KMF
 * 	in ctape_done or other completion routine. This was more
 * 	common in the changer because of its allowing multiple
 * 	opens to a device, but is still possible in the tape device
 * 	for certain multithreaded applications. Although tapes exposure
 * 	is smaller I have grabbed the code almost in situ. This has been
 * 	done as this code has gotten fairly thorough testing, and
 * 	changes (even simplifications) might introduce deadlocks which
 * 	are the bane of this readers/writers model. This effort is to fix
 * 	qar 98260 which corresponds to ptr 221-2-508.
 * 	[2004/10/15  15:02:16  Keith_Comeford]
 *
 * Revision 1.1.83.1  2003/09/10  18:09:59  Keith_Comeford
 * 	Fixing a typo in the comments
 * 	[2003/08/29  20:54:32  Keith_Comeford]
 *
 * 	I forgot to add that this change is part of the fix for QAR 96567
 * 	[2003/08/28  20:15:50  Keith_Comeford]
 *
 * 	Adding a flag to indicate if the device is capable of handling
 * 	compression.
 * 	[2003/08/14  18:22:29  Keith_Comeford]
 *
 * Revision 1.1.75.2  2002/05/30  23:15:31  Ashoke_Rampuria
 * 	Changes for compiler switch project
 *
 * Revision 1.1.75.1  2002/01/24  18:41:03  Gary_Field
 * 	Added CTAPE_PATH_LOCKED flag bit for ts_state_flags field.
 * 	Removed the CTAPE_OR_RESERVE_STATE macro.
 * 	Added clearing of the CTAPE_RESERVE_CONFLICT_STATE bit
 * 	to the CTAPE_CLOSE macro.
 *
 * Revision 1.1.67.2  2001/10/23  18:40:07  David_Foster
 * 	{** Forced Submit **}
 *
 *  Added path tracking attributes to allow user to see what path
 *  has been selected for use.
 *
 * Revision 1.1.52.2  2000/12/11  20:00:57  Gary_Field
 * 	Added CTAPE_MAX_XFER_IDX for drvr_max_xfer attribute.
 *
 * Revision 1.1.52.1  2000/09/18  20:38:46  Per_Wahlstrom
 * 	Compiler warning
 *
 * Revision 1.1.44.9  2000/06/23  18:28:05  Gary_Field
 * 	Changed CTAPE_PATH_FAIL_LIMIT from 2 to 1. QAR 79942
 *
 * Revision 1.1.44.8  2000/03/29  21:02:27  Peter_Keilty
 * Merge Information:  Visual Merge: User specified tree zincos
 *     User Revision:  ZULUOS:1.1.44.7 Local Ancestor: n/a
 *    Merge Revision:  ZINCOS:1.1.47.5
 *   Common Ancestor:  1.1.47.2
 * 	Merging in Zinc BL4 spin3,4
 *
 * Revision 1.1.47.5  2000/03/24  19:10:53  Gary_Field
 * 	Moved pd_clus_directions from CCMN_SPECIFIC to TAPE_SPECIFIC
 * 	QAR 77341
 * 
 * Revision 1.1.47.4  2000/03/20  20:25:45  Gary_Field
 * 	added
 * 
 * Revision 1.1.44.7  2000/03/03  19:44:12  Carolyn_Briglia
 * 	merge zinc bl4 pass 2
 * 
 * Revision 1.1.47.3  2000/02/17  17:06:29  Jan_Reimers
 * 	Add CCMN_SPECIFIC_ADDR attribute
 * 
 * Revision 1.1.44.6  2000/01/28  21:10:32  Jan_Reimers
 * 	Path ping hooks added
 * 
 * Revision 1.1.44.5  2000/01/24  18:34:06  Jan_Reimers
 * 	Clean up paths from inactive list (QAR 75555)
 * 
 * Revision 1.1.47.2  2000/01/13  22:00:22  Jan_Reimers
 * 	{** Forced Submit **}
 * 	Clean up paths from inactive list (QAR 75555)
 * 	Fixed an argument bug to CCMN_SLEEPUNLOCK
 * 
 * Revision 1.1.44.4  2000/01/13  19:30:11  William_Dallas
 * 	Modified sleep_unlocks so that proper sleep priority
 * 	is passed.
 * 
 * Revision 1.1.44.3  2000/01/03  22:12:07  Jan_Reimers
 * 	Add CONSISTENT_NAME EHM attribute
 * 	merge from zinc bl3
 * 
 * Revision 1.1.47.1  1999/12/15  18:40:38  Jan_Reimers
 * 	Added CONSISTENT_NAME EHM attribute
 * 
 * Revision 1.1.44.2  1999/08/25  17:08:56  Peter_Keilty
 * 	Increment version number of TAPE_SPECIFIC structure.
 * 	[1999/08/23  13:04:21  Peter_Keilty]
 * 	Add variable ts_ccb_wait_cnt to TAPE_SPECIFIC structure.
 * 	Number outstanding CCB allocations, used for serialization
 * 	of allocations.
 * 	[1999/08/19  16:53:29  Peter_Keilty]
 * 
 * Revision 1.1.22.15  1999/07/13  20:47:13  William_Dallas
 * 	Update CTAPE_CLOSE for new args to CCMN_CLR_WAIT_STATE
 * 	[1999/07/12  19:36:38  William_Dallas]
 * 
 * Revision 1.1.22.14  1999/03/19  21:02:18  Jamey_Poirier
 * 	Added attribute for manufacturer (vendor id) and
 * 	removed model (it is now part of the common attribute
 * 	table).
 * 	[1999/03/19  20:15:47  Jamey_Poirier]
 * 
 * Revision 1.1.22.13  1998/12/02  13:54:16  Jan_Reimers
 * 	Increased sizes of some structure members
 * 	[1998/11/24  15:50:03  Jan_Reimers]
 * 
 * Revision 1.1.22.12  1998/11/12  16:55:35  William_Dallas
 * 	Update defines to present Logical Id of device to EHM
 * 	[1998/11/10  19:56:40  William_Dallas]
 * 
 * Revision 1.1.22.11  1998/04/27  19:49:32  Jan_Reimers
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.22.9 **
 * 		** Merge revision:	1.1.22.10 **
 * 	 	** End **
 * 	- Fixed lock problem in CTAPE_CLOSE
 * 	- Added ts_mss_tape_rpt to TAPE_SPECIFIC
 * 	[1998/04/24  18:36:16  Jan_Reimers]
 * 
 * Revision 1.1.22.10  1998/04/17  18:09:43  William_Dallas
 * 	Added defines for EHM reporting
 * 	[1998/04/16  17:10:49  William_Dallas]
 * 
 * Revision 1.1.22.9  1998/03/27  21:24:48  Jan_Reimers
 * 	- Additional EHM information
 * 	- Defines for two new device special file name creation
 * 	- New CTAPE_CLOSE macro used to consolidate code in ctape_close
 * 	[1998/03/26  18:06:38  Jan_Reimers]
 * 
 * Revision 1.1.22.8  1998/01/15  16:35:47  Jan_Reimers
 * 	Merge of the changes from PTCOS_BL11 to PTCOS_BL14 into steel.
 * 	Defined CTAPE_DISINT_STATE for use to disable interrupting of
 * 	tape movement commands.  (CLD SQO100386)
 * 	Added CTAPE_RESET_ERROR_STATE definition.
 * 	[1998/01/15  16:23:41  Jan_Reimers]
 * 
 * Revision 1.1.22.7  1997/10/30  23:00:28  William_Dallas
 * 	Merge from shared sandbox of device access management
 * 	[1997/10/29  23:01:58  William_Dallas]
 * 
 * Revision 1.1.29.2  1997/10/21  17:10:08  William_Dallas
 * 	Added Pathing information for Device Access Management
 * 	[1997/10/21  16:55:45  William_Dallas]
 * 
 * Revision 1.1.22.6  1997/10/09  18:17:01  James_Smart
 * 	Convert CTAPE_xxx flags for ts_flags to use DEV_ definitions so we're
 * 	  in sync w/ api presented by /usr/bin/mt
 * 	[1997/10/08  17:54:54  James_Smart]
 * 
 * Revision 1.1.22.5  1997/10/07  16:59:55  James_Smart
 * 	CAM3 : Rework for CAM3
 * 	       Early merge of PTMIN
 * 	       Changed eei_status definition from long to CAM_EEI_STATUS
 * 	       Added ts_support member and its definitions to TAPE_SPECIFIC
 * 	         structure. TAPE_SPECIFIC_VERS updated to 0x07.
 * 	       Added CTAPE_WARN_PRINTED_STATE
 * 	[1997/10/03  16:33:42  James_Smart]
 * 
 * Revision 1.1.22.4  1997/09/03  17:50:44  Jan_Reimers
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL6:PTCOS_BL10 **
 * 		** Ancestor revision:	1.1.19.5 **
 * 		** Merge revision:	1.1.19.6 **
 * 	 	** End **
 * 	merge of PTmin BL10 changes
 * 	[1997/09/03  17:30:32  Jan_Reimers]
 * 
 * Revision 1.1.19.7  1997/08/28  16:52:06  Jan_Reimers
 * 	Added tape timeout members to TAPE_SPECIFIC structure
 * 	[1997/08/27  13:50:55  Jan_Reimers]
 * 
 * Revision 1.1.19.6  1997/06/19  13:27:00  Jan_Reimers
 * 	Added CTAPE_WARN_PRINTED_STATE definition.
 * 	[1997/06/18  10:50:32  Jan_Reimers]
 * 
 * Revision 1.1.22.3  1997/02/04  18:09:42  Raul_Kacirek
 * 	merge of PTC BL3/BL4 changes
 * 	[1997/02/04  16:22:20  Raul_Kacirek]
 * 
 * Revision 1.1.19.5  1997/01/24  19:51:58  Jan_Reimers
 * 	Added define for CTAPE_SGIO_ENABLED_STATE in ts_state_flags.
 * 	Rearranged some defines for ts_state_flags.
 * 	Added defines for the PDRV_WS drv_spec_flags field.
 * 	[1997/01/21  15:37:59  Jan_Reimers]
 * 
 * Revision 1.1.19.4  1996/12/18  17:34:46  Raul_Kacirek
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.19.2 **
 * 		** Merge revision:	1.1.19.3 **
 * 	 	** End **
 * 	1) Lock structure removed from TAPE_SPECIFIC and PDRV_DEVICE3 locking
 * 	   is used instead. Consequently CTAPE_LOCK, CTAPE_UNLOCK & CTAPE_SLEEPUNLOCK
 * 	   are deleted.
 * 	   !!! TAPE_SPECIFIC_VERS updated to 0x06 !!!
 * 	[1996/12/18  15:32:30  Raul_Kacirek]
 * 
 * Revision 1.1.19.3  1996/11/18  19:14:12  Jan_Reimers
 * 	Updates to the tape specific structure for the Tape Position
 * 	Information project
 * 	[1996/11/08  16:45:31  Jan_Reimers]
 * 
 * Revision 1.1.19.2  1996/10/18  20:31:16  John_Meneghini
 * 	Added support for new MTIOCGET functionality.
 * 	[1996/10/16  21:07:30  John_Meneghini]
 * 
 * Revision 1.1.13.5  1996/01/12  14:26:53  John_Meneghini
 * 	Added more state flags to support Device Reservations and "Async I/Os"
 * 	or I/Os from applications that do I/O with mulitple processes.
 * 	 - CTAPE_RESERVE_CONFLICT_STATE : device state flag (Reservations)
 * 	 - CTAPE_ABORT_QEUEUE_STATE : device state flag (aysnc I/O)
 * 	 CTAPE_RAWASYNC_ABORT()
 * 	    conditionally call the ctape_handle_async_abort() routine to
 * 	    set abort flags and handle buffered I/O errno statuses.
 * 	Also incorporated all changes from design review.
 * 	[1995/12/14  19:23:14  John_Meneghini]
 * 	Added macros and state flags to support Multi-initiator
 * 	     tapes and Device Reservations:
 * 	 - CTAPE_RESERVE_APPLIED_STATE : device state flag.
 * 	 - CTAPE_RESERVE_PENDING_STATE : device state flag.
 * 	 - CTAPE_ABORT_QUEUE_PENDING_STATE : device state flag.
 * 	 CTAPE_PREVIOUS_RESET_CONDITION()
 * 	          binary OR of device state flags (reset).
 * 	 CTAPE_OR_RESERVE_STATE()
 * 	          conditionally set CTAPE_RESERVE_PENDING state.
 * 	 CTAPE_RELEASE_QUEUE3()
 * 	          conditionally aborts peripheral driver queues before
 * 	          releasing the SIM queue.
 * 	[1995/12/05  21:31:03  John_Meneghini]
 * 	Added support for Extented Error Information (DEVGETEEI)
 * 	[1995/10/06  19:46:40  John_Meneghini]
 * 
 * Revision 1.1.13.4  1995/10/19  14:29:21  Jan_Reimers
 * 	Fixed a lint problem with unterminated comments
 * 	[1995/10/13  13:27:33  Jan_Reimers]
 * 
 * Revision 1.1.13.3  1995/08/22  20:22:42  David_Gagne
 * 	Add a lock to the tape specific structure and update the
 * 	macros to use the lock in the tape specific structure.
 * 	Add a SCSI_TRANS structure to the tape-specific structure.
 * 	[1995/08/21  17:57:18  David_Gagne]
 * 
 * Revision 1.1.13.2  1995/04/14  15:33:30  James_Smart
 * 	Added define for CTAPE_BLKG_DEFAULT for default (variable) size
 * 	Blocking.
 * 	[1995/04/11  19:56:39  James_Smart]
 * 
 * Revision 1.1.10.2  1993/07/14  18:16:38  SJ_Lee
 * 	add #ifndef _CAM_TAPE_H_ to avoid multiple inclusion.
 * 	[1993/07/14  18:08:00  SJ_Lee]
 * 
 * Revision 1.1.8.2  1993/05/28  20:02:39  Ritu_Bahl
 * 	Added #define for dens_tbl_entry.
 * 	[1993/05/28  19:52:04  Ritu_Bahl]
 * 
 * Revision 1.1.8.2  1993/05/28  20:02:39  Ritu_Bahl
 * 	Added #define for dens_tbl_entry.
 * 	[1993/05/28  19:52:04  Ritu_Bahl]
 * 
 * Revision 1.1.3.4  1992/06/25  17:47:28  Peter_Schulter
 * 	merged in Silver BL8
 * 	Revision 1.1.3.4  92/06/02  10:56:57  cam_proj_Janet_Schank
 * 	Moved CAM include files from sys to io/cam
 * 	[92/05/13  08:23:56  Janet_Schank]
 * 
 * Revision 1.1.3.4  1992/06/25  17:47:28  Peter_Schulter
 * 	merged in Silver BL8
 * 	Revision 1.1.3.4  92/06/02  10:56:57  cam_proj_Janet_Schank
 * 	Moved CAM include files	from sys to io/cam
 * 	[92/05/13  08:23:56  Janet_Schank]
 * 
 * Revision 1.1.3.3  92/06/03  14:54:39  Peter_Schulter
 * 	merged in Silver BL7
 * 	Revision 1.1.3.3  92/05/07  13:24:27  Thomas_Tierney
 * 	Merged Maria Vella's CAM dev_t expansion work.
 * 	[92/04/21  16:40:13  Thomas_Tierney]
 * 
 * Revision 1.1.3.2  92/03/18  13:41:08  Al_Delorey
 * 	From Silver: AG_BL5
 * 	[92/03/18  12:08:45  Al_Delorey]
 * 
 * Revision 1.1.1.2  92/03/17  15:04:46  devbld_gsf
 * 	First AG_BL5 version.  Moved from Ag baselevel delivery tree.
 * 
 * Revision 1.1.2.4  92/01/31  11:16:19  Janet_Schank
 * 	Made 64bit modifications
 * 	[92/01/31  09:45:42  Janet_Schank]
 * 	Merged in changes from LA.
 * 	[92/01/28  18:05:57  Janet_Schank]
 * 	CAM support added
 * 	[92/01/17  11:16:04  Janet_Schank]
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: cam_tape.h,v $ $Revision: 1.1.83.4 $ (DEC) $Date: 2006/07/25 09:32:31 $
 */

/* ---------------------------------------------------------------------- */

/* cam_tape.h	Version	1.00			Feb. 22, 1991

This file contains all the defines that	the ctz_tape.c driver needs. The
defines	are only for the tape driver (SCSI CAM)	and apply to no	other
CAM SCSI module.

Modification History

	Version		Date		Who	Reason
	1.00		02/22/91	dallas	Created	this module
	1.01		06/19/91	dallas	Added new defines.
	1.02		07/31/91	dallas	Addded structure Version
						numbers	for the	error 
						logger.	Add new	macro's
						for wrapper code.
	1.03		08/30/91	dallas	Added new state	bit for
						loaders. Changed member
						names of ACTION	struct
						to be more consistent.

	1.04		09/13/91	dallas	Added Tried sync state.
						modeule	name change
						from cam_tape_define.h 
						to cam_tape.h

	1.05		09/13/91	dallas	Fixed wrapper macros.
	1.06		11/19/91	dallas	Added new state	bit
						CTAPE_ABORT_IO_STATE.
						This allows us to report
						aborted	ccb's not done
						by tape	driver.
	1.07		12/03/91	dallas	Got rid	of CTAPE_BTOL
						macro and now use 
						CTAPE_INFO for sense info
						bytes..
	1.08		01/27/91	dallas	Added error contol defines
						and expanded the defines
						for check conditions.



*/

#ifndef	_CAM_TAPE_H_
#define	_CAM_TAPE_H_
/* ---------------------------------------------------------------------- */


/* ---------------------------------------------------------------------- */

/* Defines */

/*

The following flags are	used in	the TAPE_SPECIFIC structure in member
ts_state_flags.	The state flags	are used to determine and indicate
certain	states the driver and scsi tape	unit is	in.

*/

#define	CTAPE_NOT_READY_STATE			0x00000001
	/*
	 * Indicates that the unit was opened with the FNDELAY flag and
	 * the unit had	some sort of failure during open but was seen
	 */
#define	CTAPE_UNIT_ATTEN_STATE			0x00000002
	/*
	 * Indicates that a check condition occurred and the sense key
	 * was UNIT ATTENTION. This usually indicates that a media change
	 * has occurred	but could be power up, reset. Either way we must
	 * notice that current tape position is	lost.
	 */
#define	CTAPE_RESET_STATE			0x00000004
	/*
	 * Indicates that we have been notified	of a reset set condition 
	 * on the device or bus.
	 */
#define	CTAPE_RESET_PENDING_STATE		0x00000008
	/*
	 * A reset is pending will get notified	shortly
	 */
#define	CTAPE_OPENED_STATE			0x00000010
	/*
	 * The unit is opened
	 */
#define	CTAPE_DISEOT_STATE			0x00000020
	/*
	 * The user has	requested no notification of end of 
	 * media.
	 */
#define	CTAPE_ABORT_TPPEND_STATE		0x00000040
	/*
	 * For fixed block operations. When a tape mark	is detected
	 * with	nbuf I/O. We abort the queues and this is just and
	 * indication that a tp	mark is	being handled.
	 */
#define	CTAPE_AUTO_DENSITY_VALID_STATE		0x00000080
	/*
	 * This	flag used when a unit atten is noticed during the open
	 * sequence. The CTAPE_UNIT_ATTEN_STATE	flag directs the open
	 * routine to call ctz_auto_density when at beginning of media
	 * the auto density valid flag thell us	that tape density was
	 * determined and for all reads	- read at that density.
	 */
#define	CTAPE_ORPHAN_CMD_STATE			0x00000100
	/* 
	 * This	flag is	set when a  command is orphaned. The 
	 * process does	not wait for completion. Currently the 
	 * only	place where we orphan a	command	is the rewind
	 * on close condition. The next	open of	the device is 
	 * blocked until the bit is cleared.
	 */
#define	CTAPE_POSITION_LOST_STATE		0x00000200
	/*
	 * POSITION is lost due	to command failure.. We	can't
	 * determine where we are on tape anymore. The conditons
	 * that	clear the state	is UNIT_ATTEN and RESET. Also the
	 * mt op's of MTREW,  MTOFFL, MTRETEN.
	 */
#define	CTAPE_TRIED_ONLINE_STATE		0x00000400
	/*
	 * We found the	unit to	be in the NOT READY state. We have
	 * tried to bring the unit online once.	
	 */
#define	CTAPE_SYNC_STATE			0x00000800
	/*
	 * Tried to do synchronous negoiation
	 */

/* 
 * The following states	and macros are used to support both multiple
 * application threads or processes accessing the same device (a/k/a
 * Async I/O), and asynchronous	operations inside of the driver	(i.e.
 * DEVIOCGET, DEVGETINFO, etc.). 
 */
#define	CTAPE_IO_ASYNC_STATE			0x00001000
	/*
	 * We are running with multiple	threads	in async mode.
	 * Enable the Previous Exception mechanism.
	 */
#define	CTAPE_ABORT_QUEUE_STATE			0x00002000
	/*
	 * A Previous Exception	has been encountered.
	 * We are aborting the the I/O queues.
	 */
/*
 * CTAPE_RAWASYNC_ABORT() called after device state change errors.
 *
 * Check to see	if we are running with multiple	application threads or
 * with	Asynchronous I/O.  If we are, then call
 * ctape_handle_async_abort() to handle	the process of cleaning	up and
 * aborting the	queues.
 *
 * Note: This MACRO must be called with	the tape specific lock LOCKED 
 *
 */

#define	CTAPE_RAWASYNC_ABORT(ts, trans,	ccb) {	     \
  if ((ts)->ts_state_flags & CTAPE_IO_ASYNC_STATE) { \
    (void) ctape_handle_async_abort((ccb), (trans)); \
  }						     \
}

#define	CTAPE_ABORT_QUEUE_PENDING_STATE		0x00004000
	/*
	 * Indicates that we are waiting for an	abort queue to be done
	 * before releasing the	SIM QUEUE.  This will insure that
	 * outstanding and/or asynchronous I/Os	in the SIM queue are not
	 * sent	to the device after a Unit Attention is	discovered.
	 */
/* 
 * The CTAPE_RELEASE_QUEUE3 macro will be used to handle frozen	SIM
 * queue conditions inside of the tape driver.	This macro is called
 * from	the context of the CCB originator and is used to
 * 1) guarantee	that outstanding and asynchronious I/Os	do not make it
 *    through the SIM queue after a unit attention has been reported.
 * 2) release the SIM queue from it's frozen state.
 *
 * See ctape_ccb_chkcond() for more information.
 *
 * Note: This MACRO must be called with	the tape specific lock UNLOCKED	
 */

#define	CTAPE_RELEASE_QUEUE3(ts, trans,	ccb)			 \
{								 \
  CCMN_LOCK((CCMN_SPECIFIC *)(trans)->pd_specific);		 \
  if ((ts)->ts_state_flags & CTAPE_ABORT_QUEUE_PENDING_STATE) {	 \
    (ts)->ts_state_flags &= ~CTAPE_ABORT_QUEUE_PENDING_STATE;	 \
    (void) ccmn_abort_que3(trans, 0, (PD_LOCKED	| PD_UNLOCK_ON_EXIT)); \
  }								 \
  else								 \
	CCMN_UNLOCK((CCMN_SPECIFIC *)(trans)->pd_specific);	 \
  CHK_RELEASE_QUEUE3((trans), (ccb));				 \
}

#define	CTAPE_LAST_REC_VALID_STATE		0x00008000
	/* This	state flag is used (together with ts_last_rec_count) to
	 * provide a valid record count	when backing over a filemark.
	 */

#define	CTAPE_SGIO_ENABLED_STATE		0x00010000
	/*
	 * This	bit enables scatter/gather IO processing for
	 * readv/writev	capability.
	 */

#define CTAPE_MTGET_VALID_STATE                 0x00020000
         /* MTIOCGET implementation state flag 
          */

#define	CTAPE_DISINT_STATE			0x00040000
	/*
	 * Disable interrupting	of tape	movement commands
	 */

#define	CTAPE_WARN_PRINTED_STATE		0x00080000
	/*
	 * Only	print "Read case and density..." message once.
	 */

/* The CTAPE_RESERVE_APPLIED_STATE and CTAPE_RESERVE_PENDING_STATE bits
   were removed because they were no longer needed now that the
   AM driver is no longer with us. */
/* Free bits available at: 0x00100000 and 0x00200000 */

#define	CTAPE_RESERVE_CONFLICT_STATE		0x00400000
	/* A Reservation Conflict has been detected on this device. */

/* undefined bit 0x0800000 */

#define	CTAPE_PATH_LOCKED			0x02000000
/*
 * User has requested that the same SCSI bus (path)
 * be used on subsequent opens (so that SCSI reservations
 * won't get messed up).
 */

/*
 * The CTAPE_PREVIOUS_RESET_CONDITION macro defines the	binary state
 * of the device used to determine whether or not destructive media
 * access commands are allowed.
 *
 * Note: This MACRO must be called with	the tape specific lock HELD
 */

#define	CTAPE_PREVIOUS_RESET_CONDITION(state_flags)	\
    ((state_flags) & (CTAPE_RESET_STATE	|		\
		      CTAPE_RESET_PENDING_STATE	|	\
		      CTAPE_POSITION_LOST_STATE))

#define CTAPE_RESET_ERROR_STATE			0x08000000
	/* This flag is set in ctape_async() to let the driver know
	 * that a bus or device reset has occurred, in order to let
	 * ioctls report an error after a bus reset in multi-initiator
	 * environments.
	 */

#define CTAPE_BUS_RECOVERING_STATE		0x10000000
	/* This flag is used in ctape_bus_recover_cb() to signal to the
	 * online routine that we've had to do a BDR or BR to recover
	 * a hung bus.
	 */
#define	CTAPE_LEAST_USED_HBA	0x20000000
	/*
	 * This flag will set when we have got least used HBA. This flag 
	 * will set in ctape_verify_path () and remains under same state 
	 * until close of a device.
	 */
/* ----------------------------------------------------------------------- */

/*

The following flags are	used in	the TAPE_SPECIFIC structure in member
ts_flags. The flags are	used to	determine and indicate certain conditions
of the tape media.

*/

#define	CTAPE_BOM				DEV_BOM		/* 0x00000001 */
	/* Tape	is at Beginning	of Media same as BOT Beginning of Tape
	 */
#define	CTAPE_EOM				DEV_EOM		/* 0x00000002 */
	/* At End of Tape
	 */
#define	CTAPE_OFFLINE				DEV_OFFLINE	/* 0x00000004 */
	/* Indicates the the device is returning a DEVICE not READY
	 * in response to a check condition..Basically means the tape
	 * media is not	loaded or is being loaded.
	 */
#define	CTAPE_WRT_PROT				DEV_WRTLCK	/* 0x00000008 */
	/* Tape	is either Hardware write protectioned or opened	read only
	 */
#define	CTAPE_BLANK				DEV_BLANK	/* 0x00000010 */
	/* Tape	is blank (blank	check)
	 */
#define	CTAPE_WRITTEN				DEV_WRITTEN	/* 0x00000020 */
	/* The tape has	been written this time around.
	 */
#define	CTAPE_CSE				DEV_CSE		/* 0x00000040 */
	/* This	is a short lived flag and will probably	go away
	 * CHECK_IMP
	 */
#define	CTAPE_SOFTERR				DEV_SOFTERR	/* 0x00000080 */
	/* Indicates that a soft error has been	reported by the	tape
	 * unit.
	 */
#define	CTAPE_HARDERR				DEV_HARDERR	/* 0x00000100 */
	/* Hard	error has occurred this	flag can be reported back to 
	 * the user either thru	and ioctl or the user gets notified 
	 * by the buf struct being marked as EIO.
	 */
#define	CTAPE_DONE				DEV_DONE	/* 0x00000200 */
	/* Indicates done
	 */
#define	CTAPE_RETRY				DEV_RETRY	/* 0x00000400 */
	/* Indicates retry
	 */
#define	CTAPE_ERASED				DEV_ERASED	/* 0x00000800 */
	/* The tape has	or is erased.
	 */
#define	CTAPE_RDONLY				DEV_RDONLY	/* 0x00001000 */
	/* NOT USED */
#define	CTAPE_TPMARK				DEV_TAPE_MARK	/* 0x00002000 */
	/* A tape mark has been	detected on a read (can't on writes).
	 */
#define	CTAPE_SHRTREC				DEV_SHORT_REC	/* 0x00004000 */
	/* The user asked for 10k bytes	but the	record on tape is only
	 * 5k, post the	short record flag. next	operation clears it.
	 * Indication is retrieved by the user thru an ioctl.
	 */
#define	CTAPE_TPMARK_PENDING			DEV_TPMRK_PEND	/* 0x00008000 */
	/* Due to fixed	block type tapes a tape	mark can be reported
	 * by the unit after reading valid data	blocks.	We don't want
	 * to post the tpmark back to the user now but on the next read	
	 * sequencial read.
	 */
#define	CTAPE_REWINDING				DEV_REWINDING	/* 0x00010000 */
	/* the unit is rewinding
	 */
#define	CTAPE_RDOPP				DEV_READ_OPP	/* 0x00020000 */
	/* We are reading in the reverse direction.. Not implemented
	 * at this time.
	 */


/* ----------------------------------------------------------------------- */

/*
 * The following flags are used	in the TAPE_SPECIFIC structure in member
 * ts_support. The state flags are used	to determine and indicate
 * certain states the driver and scsi tape unit	is in.
 */

#define	CTAPE_INITIALIZED			0x00000001
	/* 
	 * This	is assumed to be clear when the	TAPE_SPECIFIC
	 * structure is	allocated.  It is set when the device is
	 * opened for the first	time.
	 */

	/*
	 * For the following two, we will always prefer	the long data format.
	 * If we find that the tape drive supports the long data format, then
	 * CTAPE_READ_POS_LONG_SUP will	be set.
	 * In that case, CTAPE_READ_POS_SHORT_SUP will not be set and we will
	 * never use the short version of READ POSITION	for this tape drive.
	 */

#define	CTAPE_READ_POS_SHORT_SUP		0x00000002
	/*
	 * READ	POSITION command with short data format
	 * is supported	by this	tape drive.
	 */

#define	CTAPE_READ_POS_LONG_SUP			0x00000004
	/*
	 * READ	POSITION command with long data	format
	 * is supported	by this	tape drive.
	 */

#define	CTAPE_REP_DEN_SUP			0x00000008
	/*
	 * REPORT DENSITY SUPPORT command is supported.
	 */

#define	CTAPE_COMP_PAGE_SUP			0x00000010
	/*
	 * The devices possesses either mode page 0xf or mode page 0x10
	 * so compression can be supported
	 */

/* Bit definitions for ts_clus_directions/cluster_dev_directions attribute
 * These definitions need to be kept the same as the equivalent
 * ones in cam_changer.h and cdisk.h
 */
#define TS_CLOSED_PATH_MON	0x0001UL	/* PATH monitor across closes	*/
#define TS_FAILED_PATH_MON	0x0002UL	/* PATH monitor on failure	*/
#define TS_REC_FAILED_PATH	0x0004UL	/* Issue BDR / BUS RESET on open */


/* These macros are used to manipulate the counting semaphore in the 
 * tape_specific structure. If you are going to change the values
 * of the ts_trans and ts_path fields (and now ONLY ctape_verify_path 
 * does this) then you must use the ADD_WRITER macro Until such time as
 * the fields have been set and then you can use the REMOVE_WRITER macro.
 * ONLY 1 writer will be permitted, others will block waiting for access.
 * If you are depending on the data staying static (for example issueing an IO
 * that expects path to stay static until completion) then you should invoke 
 * the ADD_READER macro. Readers will block for a writer, but there is
 * no limit (short of the 2**31 -1 count of a signed integer) to the number of
 * simultaneous readers. When a reader finishes (usually after returning from
 * the synchronous IO) they will call the REMOVE_READER macro. 
 * The semaphore can take on 3 basic values negative when a writer is present,
 * 0 when no one is present and positive when a reader (or readers) is present
 * These macros all must be called WITHOUT the TS specific lock held. That 
 * lock will be taken as part of the process of acquiring the semaphore
 * to assure that there is NOT a possibility of a race condition when 
 * incrementing or decrementing the semaphore. The semaphore is initialized 
 * to 0 when the TS is first created.
 */

/* controls number of retries to get a valid path before we give up */
#define CTAPE_MAX_PATH_VERIFY_ATTMPTS 10

/* HBA does not have Active I/O */
#define CTAPE_NO_ACTIVE_IO	0

/* auto wakeup after 30 seconds for mpsleeps in reader/writer functions */
#define CTAPE_RW_SLEEP_TIMEOUT (30 * hz)

/* the two local messages are 48 characters long, so this leaves room
 * for 207 more. If you change either the amount of data output by
 * ctape_error_logger_rw OR the error messages in CTAPE_REMOVE_WRITER
 * or CTAPE_REMOVE_READER this value must change to fit.
 */
#define CTAPE_RW_MAX_MESSAGE_LENGTH 255

/* Add a writer to the pool. You can ONLY have 1 writer at a time 
 * and there must be NO readers. Thus the counting semaphore must == 0
 * to move in and add a writer. Also if we are in a FNODELAY or FNONBLOCK
 * open we may not sleep so if we fail to take the lock stop now and return
 * EWOULDBLOCK in status
 */
#define CTAPE_ADD_WRITER(ts, pd, flags, status)                            \
{                                                                          \
  int done = 0;                                                            \
  int sleep_result;                                                        \
    /* All OK so far */                                                    \
    status = 0;                                                            \
    CCMN_LOCK(pd);                                                         \
    /* Nobody home so just put this writer in the pool */                  \
    if (ts->ts_cache_semaphore == 0 ) {                                    \
	ts->ts_cache_semaphore = -1;                                       \
        CCMN_UNLOCK (pd);                                                  \
    }                                                                      \
    else {                                                                 \
      /* Ok don't sleep but return the EWOULDBLOCK error if we are */      \
      /* an FNDELAY or FNONBLOCK open                              */      \
      if ((flags & (FNDELAY | FNONBLOCK)) != 0 ) {                         \
        status = EWOULDBLOCK;                                              \
        CCMN_UNLOCK (pd);                                                  \
      }                                                                    \
      else { /* Not FNDELAY or FNONBLOCK sleep and try to acquire */       \
        /* OK we have 1 or more readers in or a writer in. Loop sleeping */\
        /* until they have left                                          */\
        /* we have another writer waiting... */                            \
        ts->ts_waiting_writers++;                                          \
        while ((ts->ts_cache_semaphore > 0 || ts->ts_cache_semaphore < 0)&&\
	       (!done)){                                                   \
              CCMN_UNLOCK (pd);                                            \
        /* Sleep with a timeout just to make sure we wake at some point */ \
	      sleep_result = mpsleep(&ts->ts_cache_semaphore, PZERO,       \
                                     "CTAPE_ADD_WRITER sleeping ",         \
                                      CTAPE_RW_SLEEP_TIMEOUT, NULL, 0);    \
	      CCMN_LOCK(pd);                                               \
	      /* see if we got woke up because semaphore is 0 */           \
              if (ts->ts_cache_semaphore == 0 ) {                          \
                done = 1;                                                  \
	        ts->ts_cache_semaphore = -1;                               \
	        /* Decrement the number of waiting writers */              \
                ts->ts_waiting_writers--;                                  \
              }                                                            \
        }                                                                  \
        CCMN_UNLOCK (pd);                                                  \
      }                                                                    \
    }                                                                      \
}
/* Remove the writer from the pool. You can ONLY have 1 writer at a time 
 * and there must be NO readers. Thus the counting semaphore must == -1
 * to move in and remove a writer. Anything else is actually an error 
 * and I will probably just note it in the error files for a normal system
 * but I may want to crash the system in debug mode
 */
#define CTAPE_REMOVE_WRITER(ts, pd)                                      \
{                                                                          \
    CCMN_LOCK(pd);                                                         \
    /* Normal case 1 writer in */                                          \
    if (ts->ts_cache_semaphore == -1) {                                    \
        ts->ts_cache_semaphore = 0;                                        \
        (void)wakeup(&ts->ts_cache_semaphore);                             \
    }                                                                      \
    else {                                                                 \
	/*                                                                 \
	 * Log that we had an unnatural state                              \
	 */                                                                \
	ctape_error_logger_rw(pd, ts, module,                              \
	    "CTAPE_REMOVE_WRITER attempted in invalid state");             \
    }                                                                      \
    CCMN_UNLOCK (pd);                                                      \
}

/* Add a reader to the pool. You can have multiple readers at the same time 
 * but there must be no writers . Thus the counting semaphore must >=0
 * to move in and add a reader
 */
#define CTAPE_ADD_READER(ts, pd)                                          \
{                                                                           \
  int done = 0;                                                             \
  int sleep_result;                                                         \
    CCMN_LOCK(pd);                                                          \
    /* ONLY take the semaphore if there are no writers OR waiting writers */\
    if ((ts->ts_cache_semaphore >= 0) &&                                    \
        ( ts->ts_waiting_writers == 0 )) {                                  \
        ts->ts_cache_semaphore++;                                           \
	CCMN_UNLOCK(pd);                                                    \
    }                                                                       \
    else { /* There is a writer present or one waiting       */             \
           /* sleep and loop waiting for 0 and no waiters    */             \
           /* test for writers coded as !=0 rather than      */             \
           /* > 0 as the compiler complains about that test  */             \
           /* being used on an unsigned value. I really hate */             \
           /* overzealous software                           */             \
       while ( ( ( ts->ts_cache_semaphore < 0 ) ||                          \
		 ( ts->ts_waiting_writers != 0 ) ) &&                       \
	        (!done)){                                                   \
           CCMN_UNLOCK (pd);                                                \
      /* Sleep with a timeout just to make sure we wake at some point */    \
	   sleep_result = mpsleep(&ts->ts_cache_semaphore, PZERO,           \
                                  "CTAPE_ADD_READER sleeping ",             \
                                  CTAPE_RW_SLEEP_TIMEOUT, NULL, 0);         \
	   CCMN_LOCK(pd);                                                   \
	   /* see if we got woke up because semaphore is 0 */               \
           /* NOTE: although you'd think == 0 is the right check its NOT */ \
           /* as another reader may have proceeded during the gap between*/ \
           /* the wake and lock but you still want your increment        */ \
           /* to occur                                                   */ \
           if ( ( ts->ts_cache_semaphore >= 0 ) &&                          \
		( ts->ts_waiting_writers == 0 )) {                          \
               done = 1;                                                    \
	       ts->ts_cache_semaphore++;                                    \
           }                                                                \
       }                                                                    \
       CCMN_UNLOCK (pd);                                                    \
    }                                                                       \
}

/* The difference between this macro and the previous is that this routine
 * does not yield right of way to writers. I.E. If there are readers
 * present and a waiting writer it proceeds. It is intended to be used 
 * by asyncrhonous or completion routines ONLY. The issue is that if
 * a completion routine yields right of way to a writer you can end 
 * up with the I/O not completing so that the IOCTL that caused the I/O
 * never completes and continues to block the writer(s) that is trying to
 * initiate its effort
 */  
#define CTAPE_ADD_READER_CRITICAL(ts, pd)                                  \
{                                                                          \
  int done = 0;                                                            \
  int sleep_result;                                                        \
    CCMN_LOCK(pd);                                                         \
    if (ts->ts_cache_semaphore >= 0) {                                     \
        ts->ts_cache_semaphore++;                                          \
	CCMN_UNLOCK(pd);                                                   \
    }                                                                      \
    else { /* There is a writer present sleep and loop waiting for 0 */    \
       while ((ts->ts_cache_semaphore < 0)  && (!done)){                   \
           CCMN_UNLOCK (pd);                                               \
      /* Sleep with a timeout just to make sure we wake at some point */   \
	   sleep_result = mpsleep(&ts->ts_cache_semaphore, PZERO,          \
                                  "CTAPE_ADD_READER sleeping ",            \
                                  CTAPE_RW_SLEEP_TIMEOUT, NULL, 0);        \
	   CCMN_LOCK(pd);                                                  \
	   /* see if we got woke up because semaphore is 0 */              \
           /* NOTE: although you'd think == 0 is the right check its NOT */\
           /* as another reader may have proceeded during the gap between*/\
           /* the wake and lock but you still want your increment */       \
           /* to occur*/                                                   \
           if (ts->ts_cache_semaphore >= 0 ) {                             \
               done = 1;                                                   \
	       ts->ts_cache_semaphore++;                                   \
           }                                                               \
       }                                                                   \
       CCMN_UNLOCK (pd);                                                   \
    }                                                                      \
}

/* Remove the reader from the pool. You can have Multiple readers at a time 
 * and there must be NO writers. Thus the counting semaphore must >= 1
 * to move in and remove a reader. Anything else is actually an error 
 * and I will note it in the error files for a normal system
 * but I may want to crash the system in debug mode at some point
 */
#define CTAPE_REMOVE_READER(ts, pd)                                        \
{                                                                          \
    CCMN_LOCK(pd);                                                         \
    /* Normal case 1 or more readers in */                                 \
    if (ts->ts_cache_semaphore >= 1) {                                     \
        ts->ts_cache_semaphore--;                                          \
        if (ts->ts_cache_semaphore == 0 ) {                                \
            (void)wakeup(&ts->ts_cache_semaphore);                         \
	}                                                                  \
    }                                                                      \
    else {                                                                 \
	/*                                                                 \
	 * Log that we had an unnatural state                              \
	 */                                                                \
	ctape_error_logger_rw (pd, ts, module,                             \
		   "CTAPE_REMOVE_READER attempted in invalid state");      \
    }                                                                      \
    CCMN_UNLOCK (pd);                                                      \
}
   
/* ----------------------------------------------------------------------- */

/*

Tape Structures	Declarations - Please note all are typedef'd

*/

/* TAPE_SPECIFIC */

/*
 * You must increment the version number if you	change the structure.
 */

typedef	struct tape_specific {
	U32	ts_flags;	/* Tape	flags -	BOM,EOT			*/
	U32	ts_state_flags;	/* STATE - UNIT_ATTEN, RESET etc.	*/
	U32	ts_support;	/* Functions supported by this device	*/
	U32	ts_resid;	/* Last	operation residual count	*/
	U32	ts_block_size;	/* See below for a complete desc.	*/
	U32	ts_density;	/* What	density	are we running at	*/
	long	ts_records;	/* How many records in since last tpmark*/
	long	ts_last_rec_count;
				/* Last	valid record count (before FM)	*/
	long	ts_num_filemarks;/* Number of filemarks */
				/* number of file mark into tape	*/
	U32	ts_snsinfo;	/* Last	Sense Info bytes for MTIOCGET	*/
	U32	ts_snskey;	/* Last	Sense Key for MTIOCGET		*/
	u_long	ts_read_count;	/* Number of reads to device		*/
	u_long	ts_write_count;	/* Number of writes to device		*/
	u_long	ts_read_bytes;	/* Number of bytes read	from device	*/
	u_long	ts_write_bytes;	/* Number of bytes written to device	*/
	u_long	ts_rew_timo;	/* Timeout for REWIND command		*/
	u_long	ts_space_timo;	/* Timeout for SPACE command		*/
	u_long	ts_load_timo;	/* Timeout for LOAD command		*/
	u_long	ts_seod_timo;	/* Timeout for SEOD command		*/
	TRANSLATION
		*ts_trans;	/* TRANSLATION initialized when	device
				   is opened (by ctape_spec_setup)	*/
	PATH	*ts_path;	/* Pointer to the last path used */
        u_int   ts_selected_bus; /* EHM registered value of current bus */
        u_long  ts_selected_target; /* EHM registered value of current target */
        u_long  ts_selected_lun; /* EHM registered value of current LUN */
	CAM_EEI_STATUS
		ts_eei_status;	/* EEI status Quadword			*/
	MSS	*ts_mss_tape_rpt; /* EHM Tape specific reporting */
	u_long	ts_ccb_wait_cnt; /* Number outstanding CCB allocations
				    used for serialization of allocations */
	u_long  ts_clus_directions;     /* Bit field of cluster directions */
        I32     ts_cache_semaphore; /* Counting semaphore used to moderate
				     * access to ts_path and ts_trans. 
				     * Can't safely change them if an 
				     * IO is in flight
				     */
        u_long  ts_waiting_writers; /* A count of the number of writers
                                     * waiting for access to the counting 
                                     * semaphore, This will be used to
                                     * allow joining readers to see if they
                                     * should hold off and let the writers
                                     * through. Without this opens
                                     * could stall for inordinate periods
				     * of time
				     */ 
}TAPE_SPECIFIC;

/*
 * You must increment the version number if you	change the structure.
 */

#define	TAPE_SPECIFIC_VERS	0x0D

/*
 *	The ts_block_size member is used for fixed block tapes like
 *	QIC. Since 9 trk units (variable) commands deal	in bytes and
 *	fixed block units deal in blocks (multiples of 512) we must
 *	know if	we are dealing in bytes	or blocks.. so we record 
 *	what we	are running at in the member so	we can do the right
 *	thing...I HOPE.
*/

/*
 * The ctape_action struct is passed down to the tape action
 * routines to be filled in based on success or	failure	of the
 * command.
 */
typedef	struct ctape_action {
	DCB_SCSIIO	*act_ccb;	/* The ccb that	is returned	*/
	I32		act_ret_error;	/* Error code if any		*/
	U32		act_fatal;	/* Is this considered fatal	*/
	U32		act_ccb_status;	/* The ccb status code		*/
	U32		act_scsi_status;/* The scsi error code		*/
	U32		act_chkcond_error;/* The check condition error	*/
}CTAPE_ACTION; 

/*
 * CTAPE_ACTION	defines
 * action.fatal	flags;
 */
#define	ACT_FAILED		0x00000001	/* This	action has failed */
#define	ACT_RESOURCE		0x00000002	/* Resource problem (memory)*/
#define	ACT_PARAMETER		0x00000004	/* Invalid parameter	*/
#define	ACT_RETRY_EXCEDED	0x00000008	/* Retry the operation count
						 * count has been excede */
#define	ACT_INTERRUPTED		0x00000010	/* Signal interruption	*/

 /* The	dens_tbl_entry struct */

typedef	struct dens_tbl_entry {
	U32		dens_code;   /*	The density code	     */
	U32		den_blocking;	/* The blocking	factor		*/
}DENS_TBL_ENTRY;

/*
 * These are used to create the two default tape device special files.
 */
#define DENS_DEF       0xF
#define DENS_DEF_COMP0 0x8

/*
 * These macros are used to determine if we are using one of the default
 * tape device special file names.
 */
#define	CTAPE_DEF_DEV(devt)						\
		((((devt) >> 1) & 0xF) == DENS_DEF)

#define	CTAPE_DEF_DEV_COMPR0(devt)					\
		((((devt) >> 1) & 0xF) == DENS_DEF_COMP0)

/*
 * defines for the PDRV_WS drv_spec_flags field.
 */

#define	TS_SGIO_PADDING	0x01	/* Fixed block pad allocated */
#define	TS_SGIO_RDWRV	0x02	/* IOvec scatter/gather	list allocated */

/*
 * Retry limit for scsi	status of busy
 */
#define	CTAPE_RETRY_LIMIT	100

/*
 * Defines for the ctape_online	routine.
 */
#define	OPEN_UNIT	0x00000001	/* Go thru full	open		*/
#define	NO_TIME		0x00000002	/* DO wait for full ready time 
					 * of unit 
					 */

#define	CTAPE_MIN_SENSE	0x00000007	/*
					 * Minimun size	of sense
					 * data	we need.
					 */
/* This macro will initialize simple lock for ctape_arr array */
#define	CTAPE_ARR_LOCKINIT	\
		simple_lock_setup(&ctape_arr_lock, ctape_arr_lockinfo)
/* 
 * These macro's used to lock and unlock ctape_arr array to protect 
 * from accessing other threads.
 */
#define	CTAPE_ARR_LOCK		simple_lock(&ctape_arr_lock)
#define	CTAPE_ARR_UNLOCK	simple_unlock(&ctape_arr_lock)

/*
 * CTAPE_REL_MEM will examine an DCB_SCSIIO ccb	to see if
 * the data buffer pointer is non NULL.	If so the macro	will
 * call	ccmn_rel_dbuf with the size to release the memory 
 * back	to the pools.
 */
#define	CTAPE_REL_MEM(c3cb); {						\
    if ( (c3cb)->cam_data_ptr != (u_char *)NULL	) {			\
	ccmn_rel_dbuf( (c3cb)->cam_data_ptr, (c3cb)->cam_dxfer_len );	\
	(c3cb)->cam_data_ptr = (u_char *)NULL;				\
	(c3cb)->cam_dxfer_len =	(U32)NULL;				\
    }									\
}

/*
 * Tapes will report Null's for	density	if the tape
 * is blank or if it has not determined	tape
 * density..
 */
#define	CTAPE_DENS_DEFAULT	0x00

/*
 * A NULL for blocking size will indicate variable Size	blocking.
 */
#define	CTAPE_BLKG_DEFAULT	0x00

/*
 * Index into density table
 */
#define	DEV_TO_DENS_IDX(dev)	(((dev)	>> 1) &	0x7)

/*
 * Maximum I/O size.
 */
#define	CTAPE_MAXPHYS	(16 * (1024 * 1024))	/* 16 meg		*/

/*
 * Our default time out	value for NON read/writes (rewind,space)
 */
#define	CTAPE_DEF_TIMEO	2400	/* 40 MINIUTES */

/*
 * The major numbers for the two cam_tape dev_t	types.
 */
#define	CTAPE_BMAJOR		51
#define	CTAPE_BMAJOR_OLD	9

/*
 * 5 second time
 */
#define	CTAPE_TIME_5	5

/*
 * Whether we sleep in the work	routines 
 * ctape_move_tape(), ctape_load(), etc.
 */
#define	CTAPE_SLEEP	0x00000000
#define	CTAPE_NOSLEEP	0x00000001

/*
 * Success and failure defines
 */
#define	CTAPE_SUCCESS	00
#define	CTAPE_FAIL	-1

/*
 * ERROR reports defines
 */
#define	CTAPE_HARD_ERRS		1
#define	CTAPE_ALL_ERRORS	2

/*
 * Rewind on close bit define
 */
#define	CTAPE_NOREWIND_DEV	0x1

#define	CTAPE_READ		1
#define	CTAPE_WRITE		2  

/*
 * Flags defines for the routines that do tape action.
 * Please NOTE THAT CMD_IMED is	used all over..	Do not
 * define any command flags as 0x01
 */
#define	CMD_IMED	0x1		/* Command immediate modifier	*/

/* 
 * LOAD/UNLOAD
 */
#define	LOAD_CMD_UNLOAD	0x02
#define	LOAD_CMD_LOAD	0x04
#define	LOAD_CMD_RET	0x08
#define	LOAD_CMD_EOT	0x10

/*
 * Defines for what ctape_ccb_chkcond returns
 */
#define	CHK_SENSE_NOT_VALID	0x0001	/* Valid bit is	not set	in sense */
#define	CHK_EOM			0x0002	/* End of media			*/
#define	CHK_FILEMARK		0x0003	/* File	mark detected		*/
#define	CHK_ILI			0x0004	/* Incorrect length		*/
#define	CHK_NOSENSE_BITS	0x0005	/* NOSENSE key and no bits	*/
#define	CHK_RECOVER		0x0006	/* soft	error reported		*/
#define	CHK_NOT_READY		0x0007	/* Device is not ready		*/
#define	CHK_MEDIUM_ERR		0x0008	/* Device reported hard	tape error*/
#define	CHK_HARDWARE		0x0009	/* Hardware error		*/
#define	CHK_ILL_REQ		0x000a	/* Illegal request maynot support cmd*/
#define	CHK_UNIT_ATTEN		0x000b	/* Unit	attention (ready???)	*/
#define	CHK_DATA_PROT		0x000c	/* write protected		*/
#define	CHK_BLANK_CHK		0x000d	/* Blank check erased tape	*/
#define	CHK_VENDOR_SPEC		0x000e	/* Vendor specific (no idea)	*/
#define	CHK_COPY_ABORT		0x000f	/* Copy	cmd aborted		*/
#define	CHK_CMD_ABORTED		0x0010	/* Command has been aborted	*/
#define	CHK_EQUAL		0x0011	/* Search cmd equal		*/
#define	CHK_VOL_OFLOW		0x0012	/* Phys	end of media, data in buf */
#define	CHK_MIS_CMP		0x0013	/* Miscompare src != media	*/
#define	CHK_UNKNOWN_KEY		0x0014	/* Bogus sense key		*/
#define	CHK_CHK_NOSENSE		0x0015	/* Sense Auto sense valid bit 0	*/
#define	CHK_INFORMATIONAL	0x0016	/* Informational message...	*/

/* 
 * The following flags are the Check conditions	that the action	
 * routines are	passed to say what conditions are NOT reported to the
 * error log. An example is auto density determination at unit atten
 * or bom we forward space 1 record on certain tapes if	the tape is 
 * blank it reports medium error. Well it's not	an error so we
 * should not report it.
 */

#define	ERR_EOM			0x00000001	/* EOM			*/
#define	ERR_FILEMARK		0x00000002	/* Filemark		*/
#define	ERR_ILI			0x00000004	/* Illegal lenght	*/
#define	ERR_RECOV		0x00000008	/* Recovered error	*/
#define	ERR_NOT_RDY		0x00000010	/* Not ready		*/
#define	ERR_MEDIUM		0x00000020	/* Medium Error	(hard)	*/
#define	ERR_HARDWARE		0x00000040	/* Hardware error (device)*/
#define	ERR_ILL_REQ		0x00000080	/* Illegal request	*/
#define	ERR_UNIT_ATTEN		0x00000100	/* UNIT	Attention	*/
#define	ERR_DATA_PROT		0x00000200	/* Write protect	*/
#define	ERR_BLANK_CHK		0x00000400	/* Blank check		*/
#define	ERR_VENDOR_SPEC		0x00000800	/* We don't support	*/
#define	ERR_COPY_ABORT		0x00001000	/* Copy	aborted		*/
#define	ERR_CMD_ABORTED		0x00002000	/* Target aborted command*/
#define	ERR_EQUAL		0x00004000	/* Searched data equal	*/
#define	ERR_VOL_OFLOW		0x00008000	/* Volume overflow	*/
#define	ERR_MIS_CMP		0x00010000	/* Miscompare error	*/

#define	CTAPE_INFO(sns,	long_val) {		\
	union	{				\
		unsigned char	c[4];		\
		U32		l;		\
	}tmp;					\
	if( (sns)->valid != NULL){		\
	    tmp.c[3] = (sns)->info_byte3;	\
	    tmp.c[2] = (sns)->info_byte2;	\
	    tmp.c[1] = (sns)->info_byte1;	\
	    tmp.c[0] = (sns)->info_byte0;	\
	    (long_val) = tmp.l;			\
	}					\
	else{					\
	    (long_val) = NULL;			\
	}					\
}

#define	CTAPE_OR_STATE(	pd, flags )					\
{									\
	CCMN_LOCK( (pd)	);						\
	((TAPE_SPECIFIC	*)((pd)->pd_dev_specific))->ts_state_flags |= (flags); \
	CCMN_UNLOCK( (pd) );						\
}

#define	CTAPE_CLR_STATE( pd, flags )					\
{									\
	CCMN_LOCK( (pd)	);						\
	((TAPE_SPECIFIC	*)((pd)->pd_dev_specific))->ts_state_flags	\
			&= ~((U32)(flags));				\
	CCMN_UNLOCK( (pd) );						\
}

#define	CTAPE_OR_FLAGS(	pd, flags )					\
{									\
	CCMN_LOCK( (pd)	);						\
	((TAPE_SPECIFIC	*)((pd)->pd_dev_specific))->ts_flags |=	(flags); \
	CCMN_UNLOCK( (pd) );						\
}

#define	CTAPE_CLR_FLAGS( pd, flags )					\
{									\
	CCMN_LOCK( (pd)	);						\
	((TAPE_SPECIFIC	*)((pd)->pd_dev_specific))->ts_flags &=	~((U32)(flags));\
	CCMN_UNLOCK( (pd) );						\
}

#define	CTAPE_BERROR( buf, count, error	)				\
{									\
	(buf)->b_resid = (count);					\
	(buf)->b_error = (error);					\
	(buf)->b_flags |= B_ERROR;					\
}

#define	CTAPE_NULLCCB_ERR( act_ptr, trans, pd,	mod ) {				\
	CCMN_LOCK( (pd)	);						\
	CAM3_ERROR((mod), "NULL CCB returned", CAM_SOFTWARE,		\
		(CCB_HEADER *)NULL, (trans),				\
		(u_char	*)NULL);					\
	CCMN_UNLOCK( (pd) );						\
	(act_ptr)->act_fatal |=	(ACT_RESOURCE |	ACT_FAILED);		\
	(act_ptr)->act_ret_error = ENOMEM;				\
}

/*
 * This macro will check whether state flag CTAPE_LEAST_USED_HBA is set.
 * If this bit is set and path is not locked then decrement tape usage 
 * count and clear state flag CTAPE_LEAST_USED_HBA. If the state flag
 * CTAPE_PATH_LOCKED is set then clear state flag CTAPE_LEAST_USED_HBA.
 * Here the CTAPE_PATH_LOCKED bit will over ride CTAPE_LEAST_USED_HBA to
 * make sure an application chooses same path when re-open a device. 
 */
#define CTAPE_DECREMENT_HBA_ACTIVE_COUNT				\
	if (ts_spec->ts_state_flags & CTAPE_LEAST_USED_HBA) {		\
		if (!(ts_spec->ts_state_flags & CTAPE_PATH_LOCKED)) {	\
			CTAPE_ARR_LOCK;					\
			ctape_arr[ts_spec->ts_selected_bus]--;		\
			CTAPE_ARR_UNLOCK;				\
		}							\
		ts_spec->ts_state_flags &= ~CTAPE_LEAST_USED_HBA;	\
	}								


/*
 * This macro is used to close out the unit.
 */

#define CTAPE_CLOSE( devt, pdrv_dev, trans, ts_spec, ccmn_flags, lock_flags) { \
	if ((lock_flags) & PD_LOCKED)					\
		CCMN_UNLOCK( (pdrv_dev) );				\
        dealloc_smt((devt));						\
	CCMN_LOCK( (pdrv_dev) );					\
        while(( (pdrv_dev)->pd_drv_state & CCMN_SPECIAL ) != 0 )	\
        {								\
                CCMN_SLEEPUNLOCK( &(pdrv_dev)->pd_drv_state,		\
                        PZERO, (pdrv_dev) );				\
                CCMN_LOCK( (pdrv_dev) );				\
        }								\
	if( (ts_spec->ts_clus_directions & TS_CLOSED_PATH_MON) == 0)	\
		ccmn_stop_path_monitor3( trans , pdrv_dev,		\
				(PD_LOCKED | PD_LOCK_ON_EXIT));		\
	ccmn_cleanup_paths3( (trans), (PD_LOCKED | PD_LOCK_ON_EXIT));   \
        ccmn_release_dev_desc3((trans),(PD_LOCKED | PD_UNLOCK_ON_EXIT));\
        xpt_unit_unlock_exclus( (trans), ctape_reg_nu );		\
	CCMN_LOCK( (pdrv_dev) );					\
        (ts_spec)->ts_state_flags &= ~(CTAPE_OPENED_STATE |		\
				       CTAPE_RESERVE_CONFLICT_STATE);	\
	/*  								\
	 * Here CTAPE_DECREMENT_USAGE_COUNT will make sure tape usage	\ 
	 * count decremented when ever CTAPE_CLOSE called.		\
	 */ 								\
	if (ctape_preferred_path) {					\
		CTAPE_DECREMENT_HBA_ACTIVE_COUNT;		 	\
	}								\
        CCMN_CLR_DRV_STATE( (pdrv_dev), (ccmn_flags),			\
			(PD_LOCKED | ((lock_flags) & PD_LOCK_ON_EXIT)));\
}

/* EHM reporting index defines */
#define CTAPE_REVISION_IDX		 0
#define CTAPE_READ_OPS_IDX		 1
#define CTAPE_WRITE_OPS_IDX		 2
#define CTAPE_READ_BYTES_IDX		 3
#define CTAPE_WRITE_BYTES_IDX		 4
#define CTAPE_CUR_DENSITY_IDX		 5
#define CTAPE_BLOCK_SIZE_IDX		 6
#define CTAPE_RECORDS_IDX		 7
#define CTAPE_FILEMARKS_IDX		 8
#define CTAPE_REW_TIMO_IDX		 9
#define CTAPE_SPACE_TIMO_IDX		10
#define CTAPE_LOAD_TIMO_IDX		11
#define CTAPE_SEOD_TIMO_IDX		12
#define CTAPE_RESID_IDX			13
#define CTAPE_SENSE_INFO_IDX		14
#define CTAPE_SENSE_KEY_IDX		15
#define CTAPE_PD_SOFT_ERR_IDX		16
#define CTAPE_PD_HARD_ERR_IDX		17
#define CTAPE_ACTIVE_PATHS_IDX		18
#define CTAPE_STANDBY_PATHS_IDX		19
#define CTAPE_FAILED_PATHS_IDX		20
#define CTAPE_DONOT_USE_PATHS_IDX	21
#define CTAPE_SELECTED_BUS_IDX          22
#define CTAPE_SELECTED_TARGET_IDX       23
#define CTAPE_SELECTED_LUN_IDX          24
#define CTAPE_PATH_FAIL_LIMIT_IDX	25
#define CTAPE_SUBSYS_ID_IDX		26
#define CTAPE_DEV_VENDOR_ID             27
#define CTAPE_CONSISTENT_NAME           28
#define CTAPE_SPECIFIC_ADDR		29
#define CTAPE_CLUS_DIRS_IDX		30
#define CTAPE_MAX_XFER_IDX		31
/* add index here and increase CTAPE_NUM_EHM_REP */
#define CTAPE_NUM_EHM_REP		32

#define CTAPE_PATH_FAIL_LIMIT	1 /* number of events before we declare
				     this path down */
#endif
