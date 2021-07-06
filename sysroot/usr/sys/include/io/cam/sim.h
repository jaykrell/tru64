/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: sim.h,v $
 * Revision 1.1.102.1  2002/10/08  20:41:41  Bruce_Hansen
 * Merge Information:  Non-Visual Merge: User specified tree v51asupportos.nightly
 *     User Revision:  v51bsupportos_nightly:1.1.95.2 Local Ancestor: n/a
 *    Merge Revision:  v51asupportos_nightly:1.1.98.2
 *   Common Ancestor:  1.1.98.1
 * 	Merge up to v51asupport.nightly
 *
 * Revision 1.1.98.2  2002/09/23  17:23:54  Steve_Feeley
 * 	QAR 94943. Add SIM_LOG_EXPRESS flag. This is used in
 * 	conjunction with SIM_LOG_PRISEVERE or SIM_LOG_PRIHIGH
 * 	to allow writing binlog entries during boot.
 * 
 * Revision 1.1.98.1  2002/08/05  19:33:45  Bob_Breau
 * 	Backport from wcalphaos
 * 	***
 * 	The following modification has been backported:
 * 	Revision 1.1.95.2  2002/02/11  19:53:42  Tom_Miller
 * 	     Fix for QAR 91462, used part of cam_reserved to hold spl
 * 	     for holding lock while calling ss_perform_timeout through ss_abort.
 * 	***
 * 	The following modification has NOT been backported:
 * 	Revision 1.1.95.1  2001/11/01  14:45:36  Michael_Gilmore
 * 	     Add greater than 64 bus support
 * 	***
 * 
 * Revision 1.1.95.2  2002/02/11  19:53:42  Tom_Miller
 * 	Fix for QAR 91462, used part of cam_reserved to hold spl
 * 	for holding lock while calling ss_perform_timeout through ss_abort.
 * 
 * Revision 1.1.95.1  2001/11/01  14:45:36  Michael_Gilmore
 * 	Add greater than 64 bus support
 * 
 * Revision 1.1.91.1  2000/03/14  17:21:04  Tom_Miller
 * Add SZ_IN_USE flag in SWS.
 * 
 * Revision 1.1.46.12  1998/09/17  16:34:41  David_Cerrone
 * 	Create SZ_HTM_READY flag in sws (used as a semaphore to
 * 	prevent use of an HTM accept until it's really ready).
 * 	[1998/08/26  20:32:23  David_Cerrone]
 * 
 * Revision 1.1.46.11  1997/11/21  16:33:26  Raul_Kacirek
 * 	Removed SIM_SOFTC member rsp_more_to_do.
 * 	[1997/11/21  16:28:41  Raul_Kacirek]
 * 
 * Revision 1.1.46.10  1997/09/03  16:15:37  Fred_Knight
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL6:PTCOS_BL10 **
 * 		** Ancestor revision:	1.1.52.2 **
 * 		** Merge revision:	1.1.52.4 **
 * 	 	** End **
 * 	[1997/09/03  16:05:08  Fred_Knight]
 * 
 * Revision 1.1.46.9  1997/08/20  15:27:05  Fred_Knight
 * 	Correct compiler warnings (target mode functions are void).
 * 	[1997/08/15  21:57:01  Fred_Knight]
 * 
 * Revision 1.1.46.8  1997/07/03  15:46:23  Raul_Kacirek
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit -visual **
 * 		** Ancestor revision:	1.1.46.5 **
 * 		** Merge revision:	1.1.46.7 **
 * 	 	** End **
 * 	Removed inclusion of the <kern/thread.h>
 * 	Redefined "thread_t" members in SIM_SOFTC to "void *"
 * 	[1997/07/03  15:40:52  Raul_Kacirek]
 * 
 * Revision 1.1.46.7  1997/07/02  21:51:07  Raul_Kacirek
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit -visual **
 * 		** Ancestor revision:	1.1.46.5 **
 * 		** Merge revision:	1.1.46.6 **
 * 	 	** End **
 * 	Added conditional inclusion of the header <kern/thread.h>
 * 	[1997/07/02  21:38:39  Raul_Kacirek]
 * 
 * Revision 1.1.46.6  1997/07/01  20:29:33  Raul_Kacirek
 * 	Modifications for threaded interrupt processing.
 * 	!NOTE! 3 new members in SIM_SOFTC (normal_intr, error_intr, special_intr).
 * 	[1997/07/01  19:18:43  Raul_Kacirek]
 * 
 * Revision 1.1.46.5  1997/05/14  19:41:15  Dick_Bagley
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit -visual **
 * 		** Ancestor revision:	1.1.46.3 **
 * 		** Merge revision:	1.1.46.4 **
 * 	 	** End **
 * 	Further modifications for HSZ70 failover support.
 * 	Reclaimed cam_reserved field of sim_softc. Now used
 * 	as a per-channel signal for the ss_timeout_thread
 * 	wakeup/block calls. Added definition for sim_softc
 * 	flag SZ_TMO_THREAD_RUNNING.
 * 	[1997/05/13  13:37:06  Dick_Bagley]
 * 
 * Revision 1.1.52.4  1997/05/13  19:26:34  Dick_Bagley
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit -visual **
 * 		** Ancestor revision:	1.1.52.2 **
 * 		** Merge revision:	1.1.52.3 **
 * 	 	** End **
 * 	Further modifications for HSZ70 failover support.
 * 	Reclaimed cam_reserved field of sim_softc. Now used
 * 	as a per-channel signal for the ss_timeout_thread
 * 	wakeup/block calls. Added definition for sim_softc
 * 	flag SZ_TMO_THREAD_RUNNING.
 * 	[1997/05/13  13:14:15  Dick_Bagley]
 * 
 * Revision 1.1.52.3  1997/04/22  21:39:10  Fred_Knight
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTBOS_BL4:PTHW1OS_BL3 **
 * 		** Ancestor revision:	1.1.40.2 **
 * 		** Merge revision:	1.1.48.2 **
 * 	 	** End **
 * 	[1997/04/22  21:28:40  Fred_Knight]
 * 
 * Revision 1.1.46.4  1997/04/21  19:41:08  Robin_Miller
 * 	merge of PTmin BL6 changes
 * 	[1997/04/21  19:16:59  Robin_Miller]
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL3:PTCOS_BL6 **
 * 		** Ancestor revision:	1.1.40.2 **
 * 		** Merge revision:	1.1.52.2 **
 * 	 	** End **
 * 	[1997/04/21  19:09:48  Robin_Miller]
 * 
 * Revision 1.1.52.2  1997/04/03  20:16:53  Dick_Bagley
 * 	Added flag definition to disable logging of abort
 * 	completion (required for support of HSZ failover
 * 	on Qlogic).
 * 	[1997/03/31  16:20:58  Dick_Bagley]
 * 
 * Revision 1.1.46.3  1997/03/03  15:36:01  Robin_Miller
 * 	Added C++ begin/end declarator block.
 * 	Removed old (useless) ULTRIX modification history.
 * 	Added casts to queue functions to resolve compiler warnings
 * 	resulting from common kernel function prototypes.
 * 	[1997/03/03  15:02:22  Robin_Miller]
 * 
 * Revision 1.1.48.2  1997/01/10  00:26:30  Fred_Knight
 * 	Add SZ_SIM_DISABLED flag for removable adapters (such as ATA
 * 	disk card devices).
 * 	[1997/01/09  21:39:35  Fred_Knight]
 * 
 * Revision 1.1.46.2  1996/10/15  18:03:33  Carolyn_Briglia
 * 	Changed SIM_SOFTC to rev 6; added hba_path_inq()
 * 	[1996/10/11  20:32:12  Carolyn_Briglia]
 * 
 * Revision 1.1.40.2  1996/04/08  15:22:19  Dick_Bagley
 * 	HW6 to PTHW1 merge
 * 	[1996/04/08  14:28:09  Dick_Bagley]
 * 
 * Revision 1.1.35.4  1996/01/16  20:53:51  Mike_Larson
 * 	Add SZ_TARGET_MODE_PENDING SIM_SOFTC flag.
 * 	[1996/01/16  13:59:27  Mike_Larson]
 * 
 * Revision 1.1.35.3  1995/08/22  20:23:25  David_Gagne
 * 	Adapt SIM_SM to support 64 busses.
 * 	Dev Nmg: conversion of SIM_SOFTC nexus array to dynamic array.
 * 	Dev Nmg: conversion of EDT array to dynamic array (& #tgts, #luns/tgt).
 * 	    (as such, NDPS and NLPT references are no longer needed).
 * 	[1995/08/21  17:58:03  David_Gagne]
 * 
 * Revision 1.1.36.2  1995/07/11  01:48:19  Janet_Schank
 * 	Added support for Host Target Mode.
 * 	[1995/07/10  12:39:42  Janet_Schank]
 * 
 * Revision 1.1.35.2  1995/07/05  15:16:09  James_Smart
 * 	Bumped SIM_SOFTC rev to 4 - added max_targets and max_luns to struct
 * 	[1995/07/04  11:35:15  James_Smart]
 * 
 * Revision 1.1.26.2  1994/12/19  16:39:18  Janet_Schank
 * 	Added dma_load and dma_unload functions to be
 * 	used by the pool allocator.
 * 	[1994/12/12  19:50:57  Janet_Schank]
 * 
 * Revision 1.1.14.9  1994/06/17  18:44:05  John_Meneghini
 * 	Added new softc flag SZ_SELTO_RESET_SEEN (previously in sim_94.c).
 * 	[1994/06/14  14:35:30  John_Meneghini]
 * 
 * Revision 1.1.14.8  1994/02/16  19:02:30  John_Meneghini
 * 	Added hba_targ_enable Handle to SIM_SOFTC - Now at rev 3
 * 	[1994/02/15  19:13:22  John_Meneghini]
 * 
 * Revision 1.1.14.7  1994/01/10  16:32:18  Theresa_Chin
 * 	Modified Lock macros used with SIM resource pool structures to
 * 	conform to new locking mech. in GOLD.
 * 	Added SIM resource pool control structure and the master pool header
 * 	structure definitions.  Added macros for simple lock management and
 * 	queue management.
 * 	[1993/12/22  20:03:30  Theresa_Chin]
 * 
 * Revision 1.1.14.6  1993/12/17  19:14:46  Brian_Nadeau
 * 	Merge of Sterling BL8 changes
 * 	[1993/12/17  19:02:30  Brian_Nadeau]
 * 
 * Revision 1.1.11.6  1993/11/23  21:54:51  Maria_Vella
 * 	Move target mode defines from nexus flags to softc structure flags.
 * 	[1993/11/17  18:56:18  Maria_Vella]
 * 
 * Revision 1.1.14.5  1993/11/09  16:40:57  Brian_Nadeau
 * 	Merge changes from Sterling BL7 into Gold.
 * 	[1993/11/08  19:38:01  Brian_Nadeau]
 * 
 * Revision 1.1.11.5  1993/10/06  13:44:51  Robin_Miller
 * 	Fix for QAR 13134:
 * 	Changed SIM working set field tmo_arg from U32 to "void *" since
 * 	this field gets used as a pointer (64 bits on Alpha).
 * 	[1993/10/06  13:12:01  Robin_Miller]
 * 
 * Revision 1.1.14.4  1993/09/23  19:26:15  Ernie_Petrides
 * 	Remove extraneous semicolons in locking macro definitions.
 * 	[1993/09/23  13:40:32  Ernie_Petrides]
 * 
 * Revision 1.1.14.3  1993/09/21  20:47:23  Randall_Brown
 * 	Merge of Maint + Sterling HW Support to Gold [Brian Nadeau]
 * 	[1993/09/15  15:39:01  Randall_Brown]
 * 
 * Revision 1.1.11.4  1993/09/07  20:39:20  Maria_Vella
 * 	Added bit SZ_TARG_CAPABLE for the softc flags field which is set on probe
 * 	to indicate that the SIM/HBA can support target mode.
 * 	[1993/09/03  18:12:40  Maria_Vella]
 * 	Added defines for the flags field of the NEXUS structure for target mode.
 * 	[1993/08/31  14:14:27  Maria_Vella]
 * 
 * Revision 1.1.14.2  1993/08/25  15:18:40  Brian_Nadeau
 * 	Initial changes for goldos (SMP)
 * 	[1993/08/24  22:55:06  Brian_Nadeau]
 * 
 * Revision 1.1.11.3  1993/08/06  21:52:15  William_Dallas
 * 	Changed freeze count from int to U32
 * 	[1993/08/06  21:30:57  William_Dallas]
 * 
 * Revision 1.1.11.2  1993/07/27  17:52:49  William_Dallas
 * 	Merged Fred Knights Tag Queuing changes in.
 * 	[1993/07/27  13:39:36  William_Dallas]
 * 
 * Revision 1.1.3.8  1992/12/11  15:02:05  cam_proj_Maria_Vella
 * 	Added timeout bit definition SZ_CMD_TIMEOUT in the SIM_WS flag to
 * 	indicate a timeout had occurred.
 * 	[92/11/25  11:35:15  Kuo_Hsieh]
 * 
 * Revision 1.1.3.7  92/11/06  15:18:21  cam_proj_Maria_Vella
 * 	Changed the SIM_SCHED_ISR because the state machine no longer
 * 	operates as a thread. Done for performance.
 * 	[92/10/30  17:17:38  William_Dallas]
 * 
 * Revision 1.1.3.6  92/06/25  17:49:45  Peter_Schulter
 * 	merged in Silver BL8
 * 	Revision 1.1.3.5  92/06/02  11:21:05  cam_proj_Janet_Schank
 * 	Removed all "BOP" macros.  Added "scheduler" dependent function
 * 	hooks (for XZA).
 * 	[92/05/26  13:00:34  Janet_Schank]
 * 
 * Revision 1.1.3.5  92/05/05  17:56:55  Peter_Schulter
 * 	merged in Silver BL6_4
 * 	Revision 1.1.5.5  92/04/15  12:33:44  Janet_Schank
 * 	Uped the UERF version of NEXUS to 2.
 * 	[92/04/15  10:23:31  Janet_Schank]
 * 	Revision 1.1.5.4  92/04/15  10:14:53  Janet_Schank
 * 	Reduced the size of SIM_LOG_SIZE from 1024 to 25.
 * 	[92/04/15  10:13:40  Janet_Schank]
 * 	Revision 1.1.5.3  92/04/13  15:30:06  Janet_Schank
 * 	Added I/O reordering fields to SIM_WS and NEXUS structs.
 * 	[92/04/13  15:07:42  Janet_Schank]
 * 	Revision 1.1.5.2  92/03/30  09:00:49  Janet_Schank
 * 	Changed the sizes of the Q-s in the SIM_WS structure to be smaller.
 * 	This allows the SIM_SOFTC to be logged, now that it is smaller.
 * 	[92/03/30  08:59:57  Janet_Schank]
 * 
 * Revision 1.1.3.4  92/04/14  15:27:54  Peter_Schulter
 * 	merged in Silver BL5
 * 	Revision 1.1.5.4  92/03/10  10:06:40  Janet_Schank
 * 	Changed hba_data to be U_WORD for Alpha
 * 	[92/03/10  09:58:26  Janet_Schank]
 * 	Revision 1.1.5.3  92/03/05  09:49:40  Janet_Schank
 * 	Added a functional queue to the SIM_SOFTC.
 * 	[92/03/05  09:39:44  Janet_Schank]
 * 	Revision 1.1.5.2  92/03/03  08:14:32  Janet_Schank
 * 	Turned off functional queue logging.
 * 	[92/03/03  08:04:49  Janet_Schank]
 * 	Increased the functional queue size.
 * 	[92/03/03  08:01:32  Janet_Schank]
 * 
 * Revision 1.1.3.3  92/04/02  12:47:17  Peter_Schulter
 * 	Changed hba_data in SIM_WS from U32 to long for Alpha.
 * 	[92/04/02  12:46:39  Peter_Schulter]
 * 
 * Revision 1.1.3.2  92/03/18  13:44:17  Al_Delorey
 * 	From Silver: AG_BL5
 * 	[92/03/18  12:21:33  Al_Delorey]
 * 	Added bdr_sws to SIM_SOFTC struct for bus device resets.
 * 	[92/02/26  11:45:32  Janet_Schank]
 * 	Made 64bit modifications
 * 	[92/01/31  09:48:48  Janet_Schank]
 * 	Merged in changes from LA.
 * 	[92/01/28  18:07:39  Janet_Schank]
 * 	CAM support added
 * 	[92/01/17  11:17:36  Janet_Schank]
 * 
 * Revision 1.1.1.2  92/03/17  15:09:06  devbld_gsf
 * 	First AG_BL5 version.  Moved from Ag baselevel delivery tree.
 * 
 * Revision 1.1.3.2  92/02/27  16:03:11  cam_proj_Janet_Schank
 * 	"bsubmitted from shared SB"
 * 
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: sim.h,v $ $Revision: 1.1.102.1 $ (DEC) $Date: 2002/10/08 20:41:41 $
 */
#ifndef _SIM_
#define _SIM_
#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------------------------------------------- */

/* sim.h		Version 1.30			Jan. 10, 1992 */

/*  This file contains the definitions and data structures needed by
    the CAM SIM related files.
*/
/* ---------------------------------------------------------------------- */

/*
 * Define to turn on SIM functional queues.
 */
/*
#define SIM_FUNCQ_ON
*/

/*
 * Queue sizes
 */
#define SIM_MAX_MSGIQ	16
#define SIM_MAX_PHASEQ	32
#define SIM_MAX_MSGOQ	26
#define SIM_MAX_FUNCQ   256
#define SM_QUEUE_SZ	16

/*
 * Maximum number of times we will try to abort an I/O before we
 * will perform a SCSI bus reset.
 */
#define SIM_MAX_ABORT_CNT	0x3

/*
 * HBA specific data area within the SIM_WS.
 */
#define SIM_HBA_DATA	4	/* in bytes */

/*
 * Maximum number of tags per ATA (active tag array).
 */
#define SIM_MAX_TAG	256

/*
 * Number of entries in the SIM common error log header.
 */
#define SIM_LOG_SIZE	((U32)25)

/*
 * SIM error log defines.
 */
#define SIM_LOG_SIM_SOFTC		((U32)0x00000001)
#define SIM_LOG_IT_NEXUS		((U32)0x00000002)
#define SIM_LOG_NEXUS			((U32)0x00000004)
#define SIM_LOG_SIM_WS			((U32)0x00000008)
#define SIM_LOG_TAG_ELEMENT		((U32)0x00000010)
#define SIM_LOG_DME_STRUCT		((U32)0x00000020)
#define SIM_LOG_SIM_SM_DATA		((U32)0x00000040)
#define SIM_LOG_SIM_SM			((U32)0x00000080)
#define SIM_LOG_HBA_DME			((U32)0x00000100)
#define SIM_LOG_HBA_CSR			((U32)0x00000200)
#define SIM_LOG_HBA_SOFTC		((U32)0x00000400)
#define SIM_LOG_HBA_INTR		((U32)0x00000800)
#define SIM_LOG_FOLLOW_LINKS		((U32)0x00001000)
#define SIM_LOG_UNUSED			((U32)0x00002000)
#define SIM_LOG_NOLOG			((U32)0x00004000)
#define SIM_LOG_PRISEVERE		((U32)0x00008000)
#define SIM_LOG_PRIHIGH			((U32)0x00010000)
#define SIM_LOG_PRILOW			((U32)0x00020000)
#define SIM_LOG_EXPRESS			((U32)0x00040000)
#define SIM_LOG_ALL_SIM_SOFTC						\
    (SIM_LOG_SIM_SOFTC | SIM_LOG_TAG_ELEMENT | SIM_LOG_DME_STRUCT |	\
     SIM_LOG_FOLLOW_LINKS)
#define SIM_LOG_ALL_NEXUS						\
    (SIM_LOG_NEXUS | SIM_LOG_TAG_ELEMENT | SIM_LOG_FOLLOW_LINKS )
#define SIM_LOG_ALL_SIM_WS						\
    (SIM_LOG_SIM_WS | SIM_LOG_NEXUS | SIM_LOG_IT_NEXUS | SIM_LOG_SIM_SOFTC | \
     SIM_LOG_FOLLOW_LINKS | SIM_LOG_TAG_ELEMENT | SIM_LOG_DME_STRUCT)

/*
 * Bit defines for the "error_recovery" field of SIM_SOFTC and SIM_WS.
 */
#define ERR_BUS_RESET	 ((U32)0x00000001)/* bus reset recovery		*/
#define ERR_PARITY	 ((U32)0x00000002)/* parity error recovery	*/
#define ERR_MSGIN_PE	 ((U32)0x00000004)/* A parity error occurred on a *
					   * message in byte.		*/
#define ERR_DATAIN_PE	 ((U32)0x00000008)/* A parity error occurred on a *
					   * data in byte.		*/
#define ERR_STATUS_PE	 ((U32)0x00000010)/* A parity error occurred on a *
					   * status byte.		*/
#define ERR_PHASE	 ((U32)0x00000020)/* The target performed an	*
					   * invalid phase sequence	*/
#define ERR_MSG_REJ	 ((U32)0x00000040)/* The target rejected an	*
					   * essential message.		*/
#define ERR_TIMEOUT	 ((U32)0x00000080)/* The SIM_WS is in the process *
					   * of being timed out.	*/
#define ERR_ABORT_REJECTED \
    			 ((U32)0x00000100)/* Set if ABORT message was	*
					   * rejected by the target.	*/
#define ERR_UNKNOWN	 ((U32)0x00000200)/* An error of unknown cause	*
					   * has occured.		*/
#define ERR_DATA_RUN	 ((U32)0x00000400)/* A data over/under run has	*
					   * occured.			*/
#define ERR_ABORT_TAG_REJECTED \
			 ((U32)0x00000800)/* Set if ABORT TAG message was*
					   * rejected by the target.	*/

/*
 * Flags used for the TAG_ELEMENT structure.
 */
#define SZ_TAG_ELEMENT_INUSE	0x0001	/* This element is in use */

/*
 * "Flags" field for the SIM_SOFTC.
 */
#define SZ_TRYING_SELECT ((U32)0x00000001)/* Currently attempting to 	*
					   * select a target.		*/
#define SZ_RESELECTED	 ((U32)0x00000002)/* Controller has been reselected*/
#define SZ_WIDE_XFER	 ((U32)0x00000004)/* Set by the HBA init function*
					   * to notifiy the other modules*
					   * that WIDE xfers are allowed */
#define SZ_POLL_MODE	 ((U32)0x00000008)/* Poll for interrupts	 */
#define SZ_TARG_CAPABLE  ((U32)0x00000040)/* Set in probe if the HBA can*/
                                          /* support target mode operations*/
#define SZ_TARGET_MODE_PENDING ((U32)0x00000080)
                                          /* SIM94 target mode pending flag */
#define SZ_SIM_DISABLED	 ((U32)0x00000100)/* Sim can't currently be used */
#define SZ_TARGET_MODE   ((U32)0x00010000)/* The SIM is operating in    *
                                           * target mode.               */
#define SZ_SELTO_RESET_SEEN ((U32)0x00020000)
                                          /* Set if a Bus Reset has been done
					     after an abitration timeout */
#define SZ_SIM_DEAD	 ((U32)0x00040000) /* Set if the SIM/HBA is dead */
#define SZ_RESET_IN_PROG ((U32)0x00080000) /* The SIM/HBA is being reset */
#define SZ_TMO_THREAD_RUNNING ((U32)0x00100000)
                                          /* Command timeout thread has
                                             been successfully started */

/*
 * "Flags" bits for the IT_NEXUS.
 */
#define SZ_SYNC_CLEAR	 ((U32)0x00000001)/* Renegotiate sync with a zero*
					   * offset and period		*/
#define SZ_SYNC_NEEDED	 ((U32)0x00000002)/* Negotiate for sync transfers */
#define SZ_SYNC		 ((U32)0x00000004)/* The device is set-up for 	*
					   * sync xfers			*/
#define SZ_SYNC_NEG	 ((U32)0x00000008)/* The device is negotiating a*
					   * sync set-up 		*/
#define SZ_VALID_REQSNS	 ((U32)0x00000010)/* The request sense data is val */

/*
 * "Flags" bits for the NEXUS.
 */
#define SZ_NO_DISCON	 ((U32)0x00000001)/* The device can't disconnect */
#define SZ_NOTUSED_BIT1	 ((U32)0x00000002)/* bit 1 is not used - it was  *
					   * the old FROZEN bit		*/
#define SZ_CONT_LINK	 ((U32)0x00000004)/* Continue the active linked	*
					   * command.			*/
#define SZ_UNTAGGED	 ((U32)0x00000008)/* Set if the current active	*
					   * request is untagged.	*/
#define SZ_TARG_DEF	 ((U32)0x00000010)/* Set if the NEXUS is set	*
					   * with target mode defaults	*/
#define SZ_PROCESSOR	 ((U32)0x00000020)/* Set if the NEXUS is setup	*
					   * for processor mode		*/
#define SZ_HTM		 ((U32)0x00000040)/* Set if the NEXUS is setup	*
					   * for Host Target Mode mode	*/
#define SZ_TARG_DISABLE_LUN ((U32)0x00000100)  
					  /*Disable of targ lun pending*/ 
#define SZ_DEVICE_SEEN   ((U32)0x80000000)/* Set if we've seen the device */

#define DISABLE_LUN_RETRY	5	  /* Retry count for disable LUN */

/*
 * "Flags" bits for the SIM_WS.
 */
#define SZ_ABORT_NEEDED  ((U32)0x00000001)/* Perform an abort on this 	*
					   * request. 			*/
#define SZ_ABORT_INPROG  ((U32)0x00000002)/* An abort has been initiated*
					   * on this request.		*/
#define SZ_TERMIO_NEEDED ((U32)0x00000004)/* Perform a terminate I/O on *
					   * this request. 		*/
#define SZ_TERMIO_INPROG ((U32)0x00000008)/* A termio has been initiated*
					   * on this request.		*/
#define SZ_TAGGED	 ((U32)0x00000040)/* This request is tagged. 	*/
#define SZ_TAG_PENDING	 ((U32)0x00000080)/* This request is tagged, but*
					   * a tag was not assigned.  Try*
					   * to assign a tag.		*/
#define SZ_RESCHED	 ((U32)0x00000100)/* Reschedule this request.	*/
#define SZ_NO_DME	 ((U32)0x00000200)/* Don't use the DME machine	*
					   * to move data during data in*
					   * and out phases.		*/
#define SZ_CMD_CMPLT	 ((U32)0x00000400)/* The command has completed.	*/
#define SZ_DEVRS_INPROG	 ((U32)0x00000800)/* A device reset is in progress*/
#define SZ_DME_ACTIVE	 ((U32)0x00001000)/* The DME is currently active*/
#define SZ_INIT_RECOVERY ((U32)0x00002000)/* A init recovery message was*
					   * received.			*/
#define SZ_AS_INPROG	 ((U32)0x00004000)/* Autosense is in progress on  *
					   * this CCB.			*/
#define SZ_RDP_NEEDED	 ((U32)0x00008000)/* Before transferring any more*
					   * data, perform a DME_RESTORE*
					   * to restore the data pointer.*/
#define SZ_TARGET_MODE	 ((U32)0x00010000)/* The SIM is operating in 	*
					   * target mode.		*/
#define SZ_EXP_BUS_FREE	 ((U32)0x00020000)/* The SIM should expect a bus*
					   * free phase to occure.	*/
#define SZ_ABORT_TAG_INPROG ((U32)0x00040000)/* An abort tag has been	*
					      * initiated on this request.*/
#define SZ_CMD_TIMEOUT ((U32)0x00080000)  /* A timeout has occurred */ 
#define SZ_HTM_READY   ((U32)0x00100000)  /* This SWS is now ready for */
                                          /* the HTM code to use.      */
#define SZ_IN_USE      ((U32)0x00200000)  /* This SWS in now in use  */

/*
 * "errors_logged" bits for the SIM_WS.
 */
#define SZ_ERRLOG_DATAIN	0x0001	/* Logged an error on datain phase */
#define SZ_ERRLOG_MSGIN		0x0002	/* Logged an error on msgin phase */
#define SZ_ERRLOG_CMDTMO	0x0004	/* Logged an error on cmd timeout */
#define SZ_ERRLOG_NOLOG_ABORTS 	0x0008	/* Suppress logging of abort completion*/

/*
 * Now call it directly.  
 */
#define SIM_SCHED_ISR() scsiisr()

/*
 * Forward structure declarations.  This will allow the use of the
 * structure as a pointer before the structure is defined.
 */
struct sim_softc;
struct nexus;
struct sim_ws;
struct sim_sm;
struct sim_sm_data;

/*
 * Initiator/Target nexus information.
 *
 * If this structure is changed, up the IT_NEXUS_VERS number.
 */
typedef struct it_nexus {
#define IT_NEXUS_VERS 1
    struct sim_ws *flink;
    struct sim_ws *blink;
    short sync_offset;		/* sync offset value for this device	*/
    short sync_period;		/* sync period value for this device	*/
    U32 flags;		/* sync state 				*/

    /*
     * Request sense info, for target mode.
     */
    ALL_REQ_SNS_DATA *reqsns_data;

    /*
     * Inquiry data, for target mode.
     */
    ALL_INQ_DATA *inq_data;

} IT_NEXUS;

/*
 * TAG_ELEMENT -
 *
 * There is one TAG_ELEMENT for each tag in the CAM subsystem.
 * The Active Tag Array which is allocated during initialization is
 * is an array of TAG_ELEMENTS. The Active Tag Array (ATA) is used
 * during the allocation and deallocation of SIM Tags as well as allows
 * the SIM to map from a tag value to a sim_ws address.
 *
 * If this structure is changed, up the TAG_ELEMENT_VERS number.
 */
typedef struct tag_element {
#define TAG_ELEMENT_VERS 1
  struct tag_element *flink;
  struct sim_ws *sim_ws;/* Address of sim_ws or blink */
  I32 tag;		/* Tag value for this tag (usually equal to index) */
  I32 flags;		/* Is this element in use?, etc. */
} TAG_ELEMENT;

/*
 * The SIM_WS ("SIM Working Set") structure is the per I/O request
 * structure, used by the SIM. The SIM_WS contains the per I/O variables
 * used by the SIM during the execution of a CAM CCB.  This structure
 * has been defined within the nexus structure to allow use with
 * DBX.
 *
 * If this structure is changed, up the SIM_WS_VERS number.
 */
typedef struct sim_ws {
#define SIM_WS_VERS 2
    struct sim_ws *flink;	/* forward link				*/
    struct sim_ws *blink;	/* backward link			*/
    U32 cntlr;		/* logical controller number of this HBA*/
    U32 targid;		/* target identifier			*/
    U32 lun;			/* logical unit identifier		*/
    U32 cam_status;		/* set to request aborted, active, 	*
			 	 * inactive, etc.			*/
    U32 tag;			/* set to tag if command queuing is	*
			 	 * used, set to -1 if tag pending	*/
    U32 seq_num;		/* Sequence number assigned by SIMX in  *
 				 * sim_action for CAM_SCSIIO requests   */
    U32 time_stamp;		/* Time stamp of when SIM_WS is put     *
				 * on the NEXUS list                    */
    struct nexus *nexus;	/* Points to the I_T_L NEXUS structure	*/
    IT_NEXUS *it_nexus;		/* Points to the I_T Nexus struct	*/
    struct sim_softc *sim_sc;	/* Points to the sim_softc structure	*
				 * associated with the controller that	*
				 * this target/lun resides on.		*/
    CCB_SCSIIO *ccb;		/* Points to the ccb which this request	*
				 * represents.				*/
    U32 phase_sum;		/* Bit description of phases which have	*
				 * occurred				*/
    I32 flags;			/* miscellaneous flags, includes tag	*
				 * flags, termio flag.			*/
    I32 cam_flags;		/* copied from the CCB for rapid access	*/
    U32 error_recovery;	/* Use bits defined above to determine	*
				 * error type.				*/
    U32 recovery_status;	/* What has been done to recover from	*
				 * an error.				*/
    void (*as_callback)();	/* Temporary holder for callback routine*
				 * used during autosense.		*/
    CCB_SCSIIO *as_ccb;		/* Temporary holder for the CCB during	*
				 * autosense.				*/
    void (*tmo_fn)();		/* function pointer to a routine which	*
				 * will be called when a time-out	*
				 * occurs.				*/
    void *tmo_arg;		/* Argument passed to the timeout	*
				 * function when it is called.  	*/
    SIM_TARG_WS targ_ws;	/* Working set used during target mode	*/
    struct sim_ws *linked_ws;
				/* Used for linked commands.	 	*/
    struct timeval time;	/* Time structure used by the SIM timer */
    CIR_Q msgoutq;		/* Circular queue used for message out	*/
    CIR_Q msginq;		/* Circular queue used for message in	*/
    CIR_Q phaseq;		/* Circular queue used for phases	*/

    u_char msgoutq_buf[SIM_MAX_MSGOQ];
				/* Buffer for msgout queue		*/
    u_char msginq_buf[SIM_MAX_MSGIQ];
				/* Buffer for msgin queue		*/
    u_char phaseq_buf[SIM_MAX_PHASEQ];
				/* Buffer for phase queue.		*/
    u_char msgout_sent;		/* Number of message out bytes sent	*
				 * from current sequence.		*/
    u_char scsi_status;		/* set to SZ_STAT_ code defines		*/
	
    u_short errors_logged;	/* Used to allow an error which repeats	*
				 * to only be logged once.		*/

    /*
     * SIM_HBA specific data.
     */
    U_WORD hba_data[SIM_HBA_DATA];
	
    /*
     * Error counts.
     */
    U32 abort_cnt;		/* number of times we have tried to	*
				 * abort this I/O.			*/
    U32 lostarb;		/* count kept for number of lost	*
				 * arbitrations				*/
    /*
     * Data transfer information. Separate structures are kept for the
     * different bus phases. This allows for modified data pointers and
     * message rejects without any loss of information.
     */
    DME_DESCRIPTOR msgin_xfer;
    DME_DESCRIPTOR msgout_xfer;
    DME_DESCRIPTOR command_xfer;
    DME_DESCRIPTOR data_xfer;
    DME_DESCRIPTOR status_xfer;

    /*
     * If non-zero, used to sort on.
     */
    U32 cam_sort;

    /*
     * Priority level used to insert this SIM_WS into the NEXUS queue.
     */
    u_short cam_priority;

#ifdef SIM_FUNCQ_ON
    CIR_Q funcq;                /* Circular queue used for func flow    */
    char *funcq_buf[SIM_MAX_FUNCQ];
#endif

} SIM_WS;

/*
 * Initiator/Target/Lun NEXUS information.
 *
 * If this structure is modified, up the NEXUS_VERS number.
 */
typedef struct nexus {
#define NEXUS_VERS 4
    SIM_WS *flink;		/* Pointer to the first WS in NEXUS Q	*/
    SIM_WS *blink;		/* Pointer to the last WS in NEXUS Q	*/

    struct nexus *nexus_flink;	/* Pointer to next active nexus.	*/
    struct nexus *nexus_blink;	/* Pointer to previous active nexus.	*/

    U64 tgtid;			/* Target id of this nexus */
    U64 lun;			/* Lun of this nexus */

    /*
     * Per targ/lun information.
     */
    short termio_pend_cnt;	/* number of requests related to this	*
				 * structure which must be terminated.	*/
    short abort_pend_cnt;   	/* number of requests related to this	*
			     	 * structure which must be aborted.	*/
    U32 flags;		/* misc. flags. Used to determine if	*
				 * the device can disconnect		*
				 * if frozen, if device needs to	*
				 * be aborted, if target's tagged queue	*
				 * is full, if active non-tagged	*/
    TAG_ELEMENT *ata;           /* Pointer to the active tag array      */
    TAG_ELEMENT *ata_list;      /* Pointer to the head of the ATA linked*
                                 * list.                                */
    U32 sws_count;		/* Number of SIM_WS's associated with	*
				 * this NEXUS.				*/

    /*
     * Error logging information.
     */
    U32 parity_cnt;		/* number of parity errors which have	*
				 * occurred.				*/
    /*
     * Sorting fpointers, and counters.
     */
    SIM_WS *curr_list;
    U32 curr_cnt;
    U32 curr_time;		/* Time stamp of oldest SIM_WS on list */
    SIM_WS *next_list;
    U32 next_cnt;
    U32 next_time;		/* Time stamp of oldest SIM_WS on list */
    SIM_WS *as_simws_ptr;	/* autosense sim working set pointer	*/
    int freeze_count;		/* Freeze counter for tags		*/

} NEXUS;

/*
 * One SIM_SOFTC structure is used by each controller.
 *
 * If this structure is modified, up the SIM_SOFTC_VERS number.
 */
typedef struct sim_softc {
#define SIM_SOFTC_VERS 7
	void *reg;		/* address of the hba's register set	*/
	void *rambuf;		/* address of hba's rambuffer (may not	*
				 * be used)				*/
	void *dmaeng;		/* address of DMA engine register set   */
	void	*normal_intr;	/* Threads ....		  */
	void	*error_intr;	/*	... for interrupt ...		*/
	void	*special_intr;  /*		... processing		*/
	void *ifchip1;		/* future expansion			*/
	U16 scsiid;		/* SCSI id for this HBA			*/
	U8 path_inq_flags;	/* Flags to pass back in path inq	*/
	U8 cam_version_num;	/* Version to pass back in path inq     */
	U32 cntlr;		/* logical controller number of this HBA*/
	SIM_WS *active_io;	/* set to NULL if no active I/O,	*
				 * otherwise points to active SIM_WS	*/
	U32 sync_offset;	/* max. sync offset for this HBA	*/
	U32 sync_period;	/* max. sync period for this HBA	*/
	U32 max_tag;		/* maximum number of tags for this	*
				 * controller				*/
	U32 flags;		/* misc. flags, i.e. SZ_TRYING_SELECT	*/
	U64 max_targets;	/* maximum number of targets supported  */
	U64 max_luns;		/* maximum number of luns/tgt supported */
        TAG_ELEMENT *ata;	/* Pointer to the Active Tag Array.     *
				 * This pointer is here for debug only  */
	TAG_ELEMENT *ata_list;  /* Pointer to head of ATA list.         * 
				 * This pointer is here for debug only  */
	DME_STRUCT *dme;	/* The structure is used to support DME.*
				 * This is a ptr to a structure to allow*
				 * different DME engines to be handled	*
				 * consistently.			*/
	U32 simx_init;	/* Flag used to track state of SIM XPT 	*/
	U32 sims_init;	/* Flag used to track state of SIM SCHED*/
	U32 simh_init;	/* Flag used to track state of SIM HBA 	*/
	U32 simd_init;	/* Flag used to track state of SIM DME 	*/

	/*
	 * HBA specific pointers
	 */
	void *hba_sc;		/* pointer to HBA specific softc	*
				 * structure				*/
	U32 (*hba_init)();	/* initialize the HBA			*/
	U32 (*hba_go)();	/* function to start a command off	*
				 * within the hba.			*/
	U32 (*hba_sm)();	/* HBA specific state machine		*/
	U32 (*hba_bus_reset)();
				/* function to generate a SCSI bus	*
				 * reset				*/
	U32 (*hba_send_msg)();
				/* send a message byte			*/
	U32 (*hba_xfer_info)();
				/* transfer info without the use of the	*
				 * DME					*/
	U32 (*hba_sel_msgout)();
				/* arbitrate, select, and go to message	*
				 * out					*/
	U32 (*hba_msgout_pend)();
				/* request a message out phase		*/
	U32 (*hba_msgout_clear)();
				/* release the ATN line			*/
	U32 (*hba_msg_accept)();
				/* accept the message byte last read	*/
	U32 (*hba_setup_sync)();
				/* setup the HBA for specified sync	*
				 * offset and period.			*/
	U32 (*hba_discard_data)();
				/* throw away one byte coming in from	*
				 * the SCSI bus.			*/
	U32 (*hba_chip_reset)();
	                        /* used to reset hba hardware */
	U32 (*hba_path_inq)();  
				/* obtain the path inquiry data		*/

	/*
	 * Functions which are dependent on the Scheduler being used.
	 */
	U32 (*sched_start)();	/* setup the given SIM_WS with messages *
				 * and anything else needed to begin    *
				 * the I/O.			        */
	U32 (*sched_run_sm)();	/* Calls or schedules the state machine */
	U32 (*sched_abort)();	/* perform a SCSI abort operation	*/
	U32 (*sched_termio)();	/* perform a SCSI terminate I/O         */
	U32 (*sched_bdr)();	/* perform a bus device reset		*/

	/*
	 * Target mode routines (CAM HTM V1).
	 */
	void (*hba_targ_cmd_cmplt)();
	void (*hba_targ_recv_cmd)();
	void (*hba_targ_send_msg)();
	void (*hba_targ_disconnect)();
	void (*hba_targ_recv_msg)();
	U32 (*hba_targ_enable)();   /* Used to enable/disable target mode
				       operation on intelligent SCSI 
				       HBAs & controllers */

	/*
	 * Host Target Mode routines (CAM HTM V2).
	 */
	I32 (*hba_htm_enable)();
	I32 (*hba_htm_accept)();
	I32 (*hba_htm_continue)();
	I32 (*hba_htm_immed_notify)();
	I32 (*hba_htm_notify_ack)();

	U32 error_recovery;	/* Use bits defined above to determine	*
				 * error type.				*/

	/*
	 * Device reset, abort, and terminate I/O flags.  Device reset
	 * over-rides aborts and terminate I/O requests.  Abort over-rides
	 * terminate I/O.
	 */
	U32 device_reset_needed;
				/* each bit in device_reset_needed	*
				 * corresponds to a target.  A target's	*
				 * bit set means that a device reset	*
				 * needs to be performed on that target.*/
	U32 device_reset_inprog;
				/* A device reset is currently in	*
				 * progress for the associated target	*
				 * with its bit set.			*/
	short abort_pend_cnt;	/* number of requests related to this	*
				 * structure which must be aborted.	*/
	short termio_pend_cnt;	/* number of terminate I/O requests	*
				 * pending for this controller.		*/
	/*
	 * Control structures which define the sim and hba interface.
	 * This is the I_T_L Nexus information.
	 *
	 * The older 2-dimensional array ([tgt][lun]) is replaced by a
	 * couple of arrays. nexus_hd points to an array of ptrs,
	 * 1 element for each possible target (the number of which for this
	 * sim is in "max_targets"). The pointer for the target points to an
	 * array of pointers to actual NEXUS structures, 1 for each
	 * possible lun (the number of which for this sim is in "max_luns").
	 * Thus:
	 *
	 * nexus_hd 
	 *  |
	 *  |   +---------------+       +--------------+     +-------------+
	 *  +-> | tgt0 NEXUS ** | ----> | lun0 NEXUS * | --> | t0l0 NEXUS  |
	 *      +---------------+       +--------------+     +-------------+
	 *      | tgt1 NEXUS ** | -+    | lun1 NEXUS * | -+
	 *      +---------------+  |    +--------------+  |  +-------------+
	 *      |      ...      |  |    |     ...      |  +> | t0l1 NEXUS  |
	 *      +---------------+  |    +--------------+     +-------------+
	 *                         |                    
	 *                         |    +--------------+
	 *                         +--> | lun0 NEXUS * |
	 *                              +--------------+
	 *                              | lun1 NEXUS * |
	 *                              +--------------+
	 *                              |     ...      |
	 *                              +--------------+
	 *                             
	 * The sim must allocate the appropriate arrays when attaching.
	 * A tgt or lun ptr may be null if the device does not exist.
	 */
	NEXUS ***nexus_hd;
				/* The nexus structure is the head of	*
				 * the linked list used to store the	*
				 * active and pending requests for a T/L*/

	/*
	 * Control information for the I_T Nexus.  Currently only
	 * sync info is kept here.
	 *
	 * The older array is now replaced with an array of pointers to
	 * IT_NEXUS's, 1 element for each possible target (the number of
	 * which for this sim is in "max_targets").
	 *
	 * The sim must allocate the appropriate array when attaching.
	 * A tgt ptr may be null if the device does not exist.
	 */
	IT_NEXUS **it_nexus_hd;

	/*
	 * Pointer to LUN based array used by the Host Target Mode
	 * Functions (HTM).
	 */
	void **htm_nexus;

	/*
	 * Temporary SIM_WS.  Used during the reselection process and
	 * during error procedures.
	 *
	 * SIM must allocate this if it needs one.
	 */
	SIM_WS *tmp_ws;

	/*
	 * NEXUS list information used by the scheduler.
	 */
	NEXUS nexus_list;
	NEXUS *next_nexus;
	U32 nexus_cnt;

	/*
	 * Error logging information.
	 */
	U32 err_recov_cnt;   /* used by error recovery routines	*/
	U32 bus_reset_count;	/* Count of bus resets for this contrl	*/

	/*
	 * Path Inquiry flags for targ mode
	 */
	U8 cam_target_sprt;

	/*
	 * Thread signal for ss_timeout_thread.
	 */
	U8 ss_tmo_signal;	/* formerly cam_reserved for alignment */
        U8 ss_abort_spl;    /* location to save spl before calling ss_abort */
                        /* was part of cam_reserved[] */
	U8 cam_reserved[1];	/* keep things aligned, reduced to 1 element */

	/*
	 * Location to store the uba_ctlr * and csr from the probe call.
	 * Version 1.15
	 */

	void * um_probe;
	caddr_t	csr_probe;

	/*
	 * SIM_WS used for bus device resets.
	 */
	SIM_WS bdr_sws;

	/*
	 * Two lock structures will be used.  reg_lk will be used when
	 * any HBA registers (reg) are accessed. softc_lk will be used
	 * for all other fields within SIM_SOFTC.  If both locks are
	 * needed, softc_lk must be obtained before reg_lk.
	 */
	simple_lock_data_t softc_lk;
	simple_lock_data_t reg_lk;

	volatile u_long rsp_flags;	/* spo_isr_thread() flags	*/
	/*
	 *  This contains the active interrupt context.
         */
	struct sim_sm_data *active_interrupt_context;

#ifdef SIM_FUNCQ_ON
	/*
	 * SIM_SOFTC functional queue.  This must stay at the
	 * bottom of the structure.
	 */
	CIR_Q funcq;                /* Circular queue used for func flow    */
	char *funcq_buf[SIM_MAX_FUNCQ];
#endif

} SIM_SOFTC;

/*
 * Structures used by the SIM State machine.  The SIM_SM_DATA structure
 * contains a pointer to the HBA specific interrupt data and a pointer to
 * the corresponding SIM_WS.  This information will be placed on the
 * State Machine's queue by the HBA's interrupt handler.  It will then
 * be removed by the State Machine's soft interrupt handler, scsiisr(),
 * and passed to the HBA specific state machine handler.  The structure
 * SIM_SM is used by the state machine for communication with other layers
 * and to maintain its own private data.
 *
 * If this structure is modified, increment the SIM_SM_DATA_VERS number.
 */
typedef struct sim_sm_data {
#define SIM_SM_DATA_VERS 1
    u_char *hba_intr;
    SIM_SOFTC *sim_sc;
} SIM_SM_DATA;

/*
 * Defines associated with SIM_SM structure
 * If SIM_MAX_PATHS is modified, up the SIM_SM_VERS number.
 */

#define SIM_MAX_PATHS   256     /* Max number of paths supported        */

#define SIM_MASK_WORDS  ( (SIM_MAX_PATHS + 63) / 64 )   /* 256 paths    */
#define SIM_MASK_BITS   64
#define SIM_MASK_SHIFT  6

/*
 * Bitmask structure for <bus reset> and <waiting_io> flagging per bus
 */
typedef struct sim_big_mask {
    U64 mask[SIM_MASK_WORDS];
} SIM_BIG_MASK;

/*
 * Macros to operate on SIM_BIG_MASK structure
 *
 *      Set bit
 */
#define SET_BIG_MASK_BIT(big_mask, bit)					\
{									\
    int   bit_index = (bit & (SIM_MASK_BITS -1));			\
    (big_mask)->mask[bit >> SIM_MASK_SHIFT] |= (1UL << bit_index);        \
}

/*
 *      Clear bit
 */
#define CLEAR_BIG_MASK_BIT(big_mask, bit)				\
{									\
    int   bit_index = (bit & (SIM_MASK_BITS -1));			\
    (big_mask)->mask[bit >> SIM_MASK_SHIFT] &= ~(1UL << bit_index);       \
}

/*
 *      Test bit
 *      Macro returns 0 if tested bit is not set
 */
#define TEST_BIG_MASK_BIT(big_mask, bit, ret)				\
{									\
    int   bit_index = (bit & (SIM_MASK_BITS -1));			\
    ret = ((big_mask)->mask[bit >> SIM_MASK_SHIFT] & (1UL << bit_index) != 0); \
}

/*
 *      Find 1st (lowest) bit set
 *      Macro returns position of the 1st bit set
 *      or -1 if no bits are set in the SIM_LONG_MASK
 */
#define FIND_FIRST_BIG_MASK_BIT(big_mask, retval)	\
{							\
    int   i, bit = 0;					\
							\
    U64 *mask = (big_mask);				\
							\
    retval = -1;					\
    for (i = 0; i < SIM_MASK_WORDS; i++) {		\
        if (*mask != 0) {				\
            U64 tmask = *mask;				\
            while (!(tmask & 1)) {                      \
                bit++;                                  \
                tmask >>= 1;                            \
            }                                           \
            retval = bit;                               \
            break;                                      \
        }                                               \
        bit += SIM_MASK_BITS;                           \
        mask++;                                         \
    }                                                   \
}

/*
 * If this structure is modified, increment the SIM_SM_VERS number.
 */
typedef struct sim_sm {
#define SIM_SM_VERS 2
    U32 sm_active;
    U32 sm_queue_sz;
    U32 bus_reset_flag;		/* Set if any controller saw a bus reset */
    U32 waiting_io_flag;	/* Set if any controller has io waiting  */
    /*
     * If a controller detects a bus reset, the controller should set
     * its bit in "bus_reset."
     */
    SIM_BIG_MASK bus_reset;

    /*
     * If a controller has an IO waiting to be started, it should
     * set its bit in "waiting_io."
     */
    SIM_BIG_MASK waiting_io;
    CIR_Q sm_queue;
    SIM_SM_DATA *sm_data;
    simple_lock_data_t sm_lk;
} SIM_SM;

/*
 * SMP lock and unlock the SIM_SOFTC structure (all but the "reg" field).
 */
#define SIM_SOFTC_LOCK_INIT(sc) {					\
    usimple_lock_setup( &((sc)->softc_lk), cam_softc_li );		\
}
#define SIM_SOFTC_LOCK(s, sc) {						\
    s = splbio();							\
    CAM_SPINLOCK( &((sc)->softc_lk) );					\
}
#define SIM_SOFTC_UNLOCK(s, sc) {					\
    CAM_SPINUNLOCK( &((sc)->softc_lk) );				\
    splx(s);								\
}

/*
 * SMP lock and unlock the SIM_SOFTC "reg" field.
 *
 * These locks seem to only be used in sim_94
 *
 */

#define SIM_REG_LOCK_INIT(sc) {						\
    usimple_lock_setup( &((sc)->reg_lk), cam_reg_li );			\
}
#define SIM_REG_LOCK(s, sc) {						\
    s = splbio();							\
    CAM_SPINLOCK( &((sc)->reg_lk) );					\
}
#define SIM_REG_UNLOCK(s, sc) {						\
    CAM_SPINUNLOCK( &((sc)->reg_lk) );					\
    splx(s);								\
}

/*
 * SMP lock and unlock the SIM_SM
 */
#define SIM_SM_LOCK_INIT(sm) {						\
    usimple_lock_setup( &((sm)->sm_lk), cam_sm_li );			\
}
#define SIM_SM_LOCK(s, sm) {						\
    s = splbio();							\
    CAM_SPINLOCK( &((sm)->sm_lk) );					\
}
#define SIM_SM_UNLOCK(s, sm) {						\
    CAM_SPINUNLOCK( &((sm)->sm_lk) );					\
    splx(s);								\
}

/*
 * CAM_SIM_PRIV -
 *
 * This structure describes the overlay for the SIM private data space in
 * the SCSI I/O CCB.
 * 
 * Note: at this time the SIM private data is about 50 bytes long.  Make sure
 * that this structure does not go over that. 
 *
 * If this structure is modified, increment the CAM_SIM_PRIV_VERS number.
 */

#define DEC_VALID	0xDEC00DEC	/* Magic # for the valid field */

typedef struct cam_sim_priv {
#define CAM_SIM_PRIV_VERS 1
    SIM_WS *sim_ws;			/* pointer to this I/O's working set */
    U32 valid;			/* indicates that sim_ws is valid */
} CAM_SIM_PRIV;



/*
 * Generic resource pool control structure -
 *
 * The following is the definition for a generic resource pool control structure.
 * Each type of resource can be queued off of one of these generic pool control
 * structure.  A master resource pool header is also defined to link all
 * resource pool control structures together.  Each resource type is categorized
 * by the size of the resource and its type value.  
 */

typedef struct sim_pool_ctrl {

#define SIM_POOL_CTRL_VERS	1

    void	*flink;			/* forward link to resource buffers	*/
    void	*blink;			/* backward link			*/
    struct sim_pool_ctrl *pool_flink;	/* forward link to next resource pool	*/
    struct sim_pool_ctrl *pool_blink;	/* backward link 			*/
    SIM_SOFTC	*sim_sc;		/* pointer to the associated SIM_SOFTC  */

    U32		resource_size;		/* byte size of this resource type	*/ 
    U32		resource_type;		/* type of the resource			*/
    U32		initial_poolsize;	/* initial amount to allocate 		*/
    U32		low_mark;		/* low watermark for this pool		*/
    U32		inc_size;		/* increment size for this pool		*/
    U32		num_total;		/* current total of allocated resource	*/
    U32		num_free;		/* # of currently free resource buffers */
    U32		flags;			/* pool status flag                     */
    U32         (*dma_load)();          /* called to load needed DMA resources  */
    U32         (*dma_unload)();        /* called to unload any DMA resources   */
    simple_lock_data_t pool_lock;	/* lock for this resource pool		*/
} SIM_POOL_CTRL;


typedef struct sim_pool_queue {
    SIM_POOL_CTRL	*flink;		/* head for resource pools linked list	*/
    SIM_POOL_CTRL	*blink;		/* tail for resource pools linked list	*/
    simple_lock_data_t lock_qhead;	/* lock for this queue header struct.   */
} SIM_POOL_QUEUE;

/*
 * resource pool type values
 */
#define SIM_CARRIER	1		/* SIMport carrier			*/
#define SIM_BSM		2		/* SIMport Buffer Segment Map		*/

/*
 * pool status flag defines
 */
#define SIM_POOL_UPDIP		0x00000001	/* signal a pool update in progress */
#define SIM_POOL_ALLOC_THREAD	0x00000002	/* the pool alloc thread is running */
#define SIM_POOL_ALLOC_CALLED	0x00000004	/* pool allocation has been called  */
#define SIM_POOL_ALLOC_NEEDED	0x00000008	/* need to allocate more buffers    */

/*
 * return status value from pool allocation routine
 */
#define SIM_ISR_CONTEXT		-1	/* called in interrupt context	*/

 
/*
 * SMP simple lock and unlock macros.  The init macro must be modified
 * for GOLD release since it is changed to "simple_lock_setup".
 */
#define SIM_LOCK_INIT(lock, lockinfo) usimple_lock_setup ( &lock, lockinfo )

#define SIM_LOCK(lock) CAM_SPINLOCK ( &lock )
#define SIM_UNLOCK(lock) CAM_SPINUNLOCK ( &lock )

#define SIM_IPL_LOCK(lock, s) {		\
        s = splbio();				\
	CAM_SPINLOCK ( &lock );			\
}

#define SIM_IPL_UNLOCK(lock, s) {		\
        CAM_SPINUNLOCK ( &lock );		\
	splx(s);				\
}

#if defined(_KERNEL)

#include <kern/queue.h>

/*
 * Macros for inserting and removing queue elements
 */
#define SIM_INSERT(que_elem, queue)				\
	insque((struct queue_entry *)(que_elem), (struct queue_entry *)(queue))

#define SIM_REMOVE(que_elem) remque((struct queue_entry *)(que_elem))

#define SIM_INSERT_TAIL(que_elem, queue)			\
	enqueue_tail((queue_t)(queue), (queue_entry_t)(que_elem))

#define SIM_REMOVE_HEAD(queue) dequeue_head((queue_t)(queue))

#endif /* defined(_KERNEL) */

#ifdef __cplusplus
}
#endif
#endif /* _SIM_ */
