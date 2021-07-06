/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: cam_changer.h,v $
 * Revision 1.1.24.2  2004/07/02  14:33:58  Keith_Comeford
 * 	There is still the issue of blocking on an FNDELAY/FNONBLOCK open
 * 	make CHANGER_ADD_WRITER so that if it fails to get the lock
 * 	on the first pass we fail with an EWOULDBLOCK error so that
 * 	changer_open can properly honor the users FNDELAY?FNONBLOCK
 * 	request
 * 	[2004/05/14  18:28:53  Keith_Comeford]
 *
 * 	Adding assorted Rework from the formal review. The two biggest changes
 * 	are 1) Make sure that Writers have right of way in the add_reader/
 * 	add_writer code . This is to keep from having a writer indefinitely
 * 	stalled and to avoid long stalls on opens which are known to annoy
 * 	users. 2) Add a variant of the add_reader code that ignores right
 * 	of way. This is needed for those routines which complete an io
 * 	(e.g. changer_done) Otherwise you could end up in a deadlock waiting
 * 	to complete an io which can't complete because it's yielding right of
 * 	way to the open (who is going to end up sending a TUR to see if
 * 	the hardware's alive).
 * 	[2004/05/07  18:22:52  Keith_Comeford]
 *
 * 	I had a bug in my initial counting semaphore code that could end up
 * 	with an undercount. This needless to say lead to deadlocks, but
 * 	is now corrected.
 * 	[2004/04/16  17:55:37  Keith_Comeford]
 *
 * 	I'm adding a counting semaphore to the changer_specific
 * 	structure (driving it to V3) This will be used to control
 * 	when changer_verify_paths may run. This routine itself may
 * 	cause IO to happen (via CCMN3_PING) That MUST NOT happen when a
 * 	long io is in progress or paths get marked failed when they shouldn't
 * 	and the fields for cs_trans and cs_path can end up NULL when
 * 	they shouldn't be
 * 	[2004/02/06  18:30:43  Keith_Comeford]
 *
 * Revision 1.1.24.1  2003/02/27  19:20:05  Keith_Comeford
 * 	Add a new EHM index for the manufacturer id and increment
 * 	the CHANGER_NUM_EHM_REP constant
 *
 * Revision 1.1.17.2  2002/05/30  23:15:10  Ashoke_Rampuria
 * 	Changes for compiler switch project
 *
 * Revision 1.1.17.1  2002/01/24  18:41:01  Gary_Field
 * 	Added CHANGER_PATH_LOCKED flag bit for cs_state_flags field.
 *
 * Revision 1.1.6.3  2000/12/11  20:00:50  Gary_Field
 * 	Added CHANGER_MAX_XFER_IDX for drvr_max_xfer attribute.
 *
 * Revision 1.1.6.2  2000/11/02  20:20:04  Ernie_Petrides
 * 	Move CAMD_CHANGER from cam_changer.h to cam_debug.h.
 *
 * Revision 1.1.6.1  2000/10/26  17:22:00  Raul_Kacirek
 * 	QAR 81531 - kernel build fails with CAMDEBUG defined
 *
 * Revision 1.1.4.4  2000/06/23  18:27:54  Gary_Field
 * 	Changed CHANGER_PATH_FAIL_LIMIT from 2 to 1.
 *
 * Revision 1.1.4.3  2000/03/29  21:01:45  Peter_Keilty
 * 	Merging in Zinc BL4 spin3,4
 * 	Because of changes to pdrv3.h involving the moving of
 * 	pd_clus_directions from CCMN_SPECIFIC to driver specific,
 * 	changer also had to be modified - PMK.
 *
 * Revision 1.1.4.2  2000/03/03  19:43:28  Carolyn_Briglia
 * 	merge zinc bl4 pass 2
 * 	merge -from 1.1.2.4 -upto 1.1.2.5
 *
 * Revision 1.1.2.5  2000/02/17  17:06:27  Jan_Reimers
 *      Add CCMN_SPECIFIC_ADDR attribute
 *
 * Revision 1.1.4.1  2000/01/28  21:10:11  Jan_Reimers
 * 	Path ping hooks added
 *
 * Revision 1.1.2.4  2000/01/13  21:45:33  Jan_Reimers
 * 	Clean up paths from inactive list (QAR 75555)
 * 	Fixed an argument bug to CCMN_SLEEPUNLOCK
 *
 * Revision 1.1.2.3  1999/12/15  18:40:15  Jan_Reimers
 * 	Added CONSISTENT_NAME EHM attribute
 *
 * Revision 1.1.2.2  1999/08/25  12:43:30  Jan_Reimers
 * 	Initial changer driver checkin into Base OS
 * 	[1999/08/05  15:19:15  Jan_Reimers]
 *
 * Revision 1.1.2.4  1999/07/14  13:51:04  Jan_Reimers
 * 	Update CHANGER_CLOSE for new args to CCMN_CLR_DRV_STATE
 * 
 * Revision 1.1.2.3  1999/07/08  13:51:04  Mark_Bokhan
 * 	Remove duplicate model definition, CHANGER_MODEL_IDX from EHM
 * 	reporting indicies. "model" is already in the first MSS as part
 * 	of the common tape attributes.
 * 
 * Revision 1.1.2.2  1999/06/14  13:51:04  Debra_Graham
 * 	Revision 1.1.1.2  1999/05/21  22:17:07  Debra_Graham
 * 	     Initial version of Steel media changer driver.
 * 	[1999/06/14  13:50:41  Debra_Graham]
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: cam_changer.h,v $ $Revision: 1.1.24.2 $ (DEC) $Date: 2004/07/02 14:33:58 $
 */

#ifndef	_CAM_CHANGER_H_
#define	_CAM_CHANGER_H_

/* controls number of retries to get a valid path before we give up */
#define CHANGER_MAX_PATH_VERIFY_ATTMPTS 10

/*
 * Controls vendor unique functions for Odetics medium changer.
 */
#define TL820	1

/*
 * The following flags are used in the CHANGER_SPECIFIC structure in member
 * cs_state_flags.  The state flags are used to determine and indicate
 * certain states the driver and SCSI changer unit is in.
 */

#define	CHANGER_NOT_READY_STATE			0x00000001
	/*
	 * Indicates that the unit was opened with the FNDELAY flag and
	 * the unit had	some sort of failure during open but was seen
	 */
#define	CHANGER_UNIT_ATTEN_STATE		0x00000002
	/*
	 * Indicates that a check condition occurred and the sense key
	 * was UNIT ATTENTION. This usually indicates that a media change
	 * has occurred	but could be power up, reset. Either way we must
	 * notice that current changer position is	lost.
	 */
#define	CHANGER_RESET_STATE			0x00000004
	/*
	 * Indicates that we have been notified	of a reset set condition 
	 * on the device or bus.
	 */
#define	CHANGER_RESET_PENDING_STATE		0x00000008
	/*
	 * A reset is pending will get notified	shortly
	 */
#define	CHANGER_OPENED_STATE			0x00000010
	/*
	 * The unit is opened
	 */
#define CHANGER_EXCLUSIVE_OPEN			0x00000020
	/*
	 * Exclusive open done.
	 */
#define	CHANGER_TRIED_ONLINE_STATE		0x00000400
	/*
	 * We found the	unit to	be in the NOT READY state. We have
	 * tried to bring the unit online once.	
	 */
#define	CHANGER_SYNC_STATE			0x00000800
	/*
	 * Tried to do synchronous negotiation
	 */

/* 
 * The CHANGER_RELEASE_QUEUE3 macro will be used to handle frozen SIM
 * queue conditions inside of the changer driver. This macro is called
 * from	the context of the CCB originator and is used to:
 *
 * 1) guarantee	that outstanding and asynchronious I/Os	do not make it
 *    through the SIM queue after a unit attention has been reported.
 * 2) release the SIM queue from it's frozen state.
 *
 * See changer_ccb_chkcond() for more information.
 *
 * Note: This MACRO must be called with	the changer specific lock UNLOCKED	
 */
#define	CHANGER_RELEASE_QUEUE3(cs, trans, ccb)			 \
{								 \
    CHK_RELEASE_QUEUE3((trans), (ccb));				 \
}

#define XPT_GET_LOG(trans_ptr)		xpt_get_logical_id(trans_ptr)

/*
 * The CHANGER Reservation States:
 */

/* The CHANGER_RESERVE_APPLIED_STATE and CHANGER_RESERVE_PENDING_STATE bits
   were removed because they were no longer needed now that the
   AM driver is no longer with us. */
/* Free bit available at: 			0x00200000 */

#define	CHANGER_RESERVE_CONFLICT_STATE		0x00400000
	/* A Reservation Conflict has been detected on this device. */

/* Undefined bit 0x800000 */

#define	CHANGER_PATH_LOCKED			0x02000000
/*
 * User has requested that the same SCSI bus (path)
 * be used on subsequent opens (so that SCSI reservations
 * won't get messed up).
 */
/*
 * The CHANGER_PREVIOUS_RESET_CONDITION macro defines the binary state
 * of the device used to determine whether or not destructive media
 * access commands are allowed.
 *
 * Note: This MACRO must be called with	the changer specific lock HELD
 */
#define	CHANGER_PREVIOUS_RESET_CONDITION(state_flags)		\
    ((state_flags) & (CHANGER_RESET_STATE		|	\
		      CHANGER_RESET_PENDING_STATE))

#define CHANGER_RESET_ERROR_STATE			0x08000000
	/* This flag is set in changer_async() to let the driver know
	 * that a bus or device reset has occurred, in order to let
	 * ioctls report an error after a bus reset in multi-initiator
	 * environments (i.e. in ASE, when the RESERVE command has
	 * eaten the Unit Attention signal).
	 */

/* ----------------------------------------------------------------------- */

/*
 * The following flags are used in the CHANGER_SPECIFIC structure in member
 * cs_flags.  The flags are used to determine and indicate certain conditions
 * of the changer media.
 */
#define	CHANGER_OFFLINE				DEV_OFFLINE	/* 0x00000004 */
	/* Indicates the the device is returning a DEVICE not READY
	 * in response to a check condition.  Basically means the changer
	 * media is not	loaded or is being loaded.
	 */
#define	CHANGER_SOFTERR				DEV_SOFTERR	/* 0x00000080 */
	/* Indicates that a soft error has been	reported by the	changer
	 * unit.
	 */
#define	CHANGER_HARDERR				DEV_HARDERR	/* 0x00000100 */
	/* Hard	error has occurred this	flag can be reported back to 
	 * the user either thru	and ioctl or the user gets notified 
	 * by the buf struct being marked as EIO.
	 */
#define	CHANGER_DONE				DEV_DONE	/* 0x00000200 */
	/* Indicates done
	 */
#define	CHANGER_RETRY				DEV_RETRY	/* 0x00000400 */
	/* Indicates retry
	 */

/* ----------------------------------------------------------------------- */

/*
 * The following flags are used	in the CHANGER_SPECIFIC structure in member
 * cs_support. The state flags are used	to determine and indicate
 * certain states the driver and scsi changer unit	is in.
 */
#define	CHANGER_INITIALIZED			0x00000001
	/* 
	 * This	is assumed to be clear when the	CHANGER_SPECIFIC
	 * structure is	allocated.  It is set when the device is
	 * opened for the first	time.
	 */

/* ----------------------------------------------------------------------- */

/* Bit definitions for cs_clus_directions/cluster_dev_directions attribute
 * These definitions must be kept the same as the equivalent
 * ones in cam_tape.h and cdisk.h
 */
#define CS_CLOSED_PATH_MON      0x0001L /* PATH monitor across closes   */
#define CS_FAILED_PATH_MON      0x0002L /* PATH monitor on failure      */
#define CS_REC_FAILED_PATH      0x0004L /* Issue BDR / BUS RESET on open */

/* These macros are used to manipulate the counting semaphore in the 
 * changer_specific structure. If you are going to change the values
 * of the cs_trans and cs_path fields (and now ONLY changer_verify_path 
 * does this) then you must use the ADD_WRITER macro Until such time as
 * the fields have been set and then you can use the REMOVE_WRITER macro.
 * ONLY 1 writer will be permitted, others will block waiting for access.
 * If you are depending on the data staying static (for example issueing an IO
 * that expects path to stay static until completion) then you should invoke 
 * the ADD_READER macro. Readers will block for a writer, but there is
 * no limit (short of the 2**31 -1 count of a signed integer) to the number of
 * simultaneous readers. When a reader finishes (usually in the 
 * changer_complete routine ) they will call the REMOVE_READER macro. 
 * The semaphore can take on 3 basic values negative when a writer is present,
 * 0 when no one is present and positive when a reader (or readers) is present
 * These macros all must be called WITHOUT the CS specific lock held. That 
 * lock will be taken as part of the process of acquiring the semaphore
 * to assure that there is NOT a possibility of a race condition when 
 * incrementing or decrementing the semaphore. The semaphore is initialized 
 * to 0 when the CS is first created.
 */

/* auto wakeup after 30 seconds for mpsleeps in reader/writer functions */
#define CHANGER_RW_SLEEP_TIMEOUT (30 * hz)

/* the two local messages are 48 characters long, so this leaves room
 * for 207 more. If you change either the amout of data output by
 * changer_error_logger_rw OR the error messages in CHANGER_REMOVE_WRITER
 * or CHANGER_REMOVE_READER this value must change to fit.
 */
#define CHANGER_RW_MAX_MESSAGE_LENGTH 255

/* Add a writer to the pool. You can ONLY have 1 writer at a time 
 * and there must be NO readers. Thus the counting semaphore must == 0
 * to move in and add a writer. Also if we are in a FNODELAY or FNONBLOCK
 * open we may not sleep so if we fail to take the lock stop now and return
 * EWOULDBLOCK in status
 */
#define CHANGER_ADD_WRITER(cs, pd, flags, status)                          \
{                                                                          \
  int done = 0;                                                            \
  int sleep_result;                                                        \
    /* All OK so far */                                                    \
    status = 0;                                                            \
    CCMN_LOCK(pd);                                                         \
    /* Nobody home so just put this writer in the pool */                  \
    if (cs->cs_cache_semaphore == 0 ) {                                    \
	cs->cs_cache_semaphore = -1;                                       \
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
        cs->cs_waiting_writers++;                                          \
        while ((cs->cs_cache_semaphore > 0 || cs->cs_cache_semaphore < 0)&&\
	       (!done)){                                                   \
              CCMN_UNLOCK (pd);                                            \
        /* Sleep with a timeout just to make sure we wake at some point */ \
	      sleep_result = mpsleep(&cs->cs_cache_semaphore, PZERO,       \
                                     "CHANGER_ADD_WRITER sleeping ",       \
                                      CHANGER_RW_SLEEP_TIMEOUT, NULL, 0);  \
	      CCMN_LOCK(pd);                                               \
	      /* see if we got woke up because semaphore is 0 */           \
              if (cs->cs_cache_semaphore == 0 ) {                          \
                done = 1;                                                  \
	        cs->cs_cache_semaphore = -1;                               \
	        /* Decrement the number of waiting writers */              \
                cs->cs_waiting_writers--;                                  \
            }                                                              \
      }                                                                    \
      CCMN_UNLOCK (pd);                                                    \
    }                                                                      \
  }                                                                        \
}
/* Remove the writer from the pool. You can ONLY have 1 writer at a time 
 * and there must be NO readers. Thus the counting semaphore must == -1
 * to move in and remove a writer. Anything else is actually an error 
 * and I will probably just note it in the error files for a normal system
 * but I may want to crash the system in debug mode
 */
#define CHANGER_REMOVE_WRITER(cs, pd)                                      \
{                                                                          \
    CCMN_LOCK(pd);                                                         \
    /* Normal case 1 writer in */                                          \
    if (cs->cs_cache_semaphore == -1) {                                    \
        cs->cs_cache_semaphore = 0;                                        \
        (void)wakeup(&cs->cs_cache_semaphore);                             \
    }                                                                      \
    else {                                                                 \
	/*                                                                 \
	 * Log that we had an unnatural state                              \
	 */                                                                \
	changer_error_logger_rw(pd, cs, module,                            \
	    "CHANGER_REMOVE_WRITER attempted in invalid state");           \
    }                                                                      \
    CCMN_UNLOCK (pd);                                                      \
}

/* Add a reader to the pool. You can have multiple readers at the same time 
 * but there must be no writers . Thus the counting semaphore must >=0
 * to move in and add a reader
 */
#define CHANGER_ADD_READER(cs, pd)                                          \
{                                                                           \
  int done = 0;                                                             \
  int sleep_result;                                                         \
    CCMN_LOCK(pd);                                                          \
    /* ONLY take the semaphore if there are no writers OR waiting writers */\
    if ((cs->cs_cache_semaphore >= 0) &&                                    \
        ( cs->cs_waiting_writers == 0 )) {                                  \
        cs->cs_cache_semaphore++;                                           \
	CCMN_UNLOCK(pd);                                                    \
    }                                                                       \
    else { /* There is a writer present or one waiting       */             \
           /* sleep and loop waiting for 0 and no waiters    */             \
           /* test for writers coded as !=0 rather than      */             \
           /* > 0 as the compiler complains about that test  */             \
           /* being used on an unsigned value. I really hate */             \
           /* overzealous software                           */             \
       while ( ( (cs->cs_cache_semaphore < 0) ||                            \
		 ( cs->cs_waiting_writers != 0 ) ) &&                       \
	        (!done)){                                                   \
           CCMN_UNLOCK (pd);                                                \
      /* Sleep with a timeout just to make sure we wake at some point */    \
	   sleep_result = mpsleep(&cs->cs_cache_semaphore, PZERO,           \
                                  "CHANGER_ADD_READER sleeping ",           \
                                  CHANGER_RW_SLEEP_TIMEOUT, NULL, 0);       \
	   CCMN_LOCK(pd);                                                   \
	   /* see if we got woke up because semaphore is 0 */               \
           /* NOTE: although you'd think == 0 is the right check its NOT */ \
           /* as another reader may have proceeded during the gap between*/ \
           /* the wake and lock but you still want your increment        */ \
           /* to occur                                                   */ \
           if ( ( cs->cs_cache_semaphore >= 0 ) &&                          \
		( cs->cs_waiting_writers == 0 )) {                          \
               done = 1;                                                    \
	       cs->cs_cache_semaphore++;                                    \
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
#define CHANGER_ADD_READER_CRITICAL(cs, pd)                                \
{                                                                          \
  int done = 0;                                                            \
  int sleep_result;                                                        \
    CCMN_LOCK(pd);                                                         \
    if (cs->cs_cache_semaphore >= 0) {                                     \
        cs->cs_cache_semaphore++;                                          \
	CCMN_UNLOCK(pd);                                                   \
    }                                                                      \
    else { /* There is a writer present sleep and loop waiting for 0 */    \
       while ((cs->cs_cache_semaphore < 0)  && (!done)){                   \
           CCMN_UNLOCK (pd);                                               \
      /* Sleep with a timeout just to make sure we wake at some point */   \
	   sleep_result = mpsleep(&cs->cs_cache_semaphore, PZERO,          \
                                  "CHANGER_ADD_READER sleeping ",          \
                                  CHANGER_RW_SLEEP_TIMEOUT, NULL, 0);      \
	   CCMN_LOCK(pd);                                                  \
	   /* see if we got woke up because semaphore is 0 */              \
           /* NOTE: although you'd think == 0 is the right check its NOT */\
           /* as another reader may have proceeded during the gap between*/\
           /* the wake and lock but you still want your increment */       \
           /* to occur*/                                                   \
           if (cs->cs_cache_semaphore >= 0 ) {                             \
               done = 1;                                                   \
	       cs->cs_cache_semaphore++;                                   \
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
#define CHANGER_REMOVE_READER(cs, pd)                                      \
{                                                                          \
    CCMN_LOCK(pd);                                                         \
    /* Normal case 1 or more readers in */                                 \
    if (cs->cs_cache_semaphore >= 1) {                                     \
        cs->cs_cache_semaphore--;                                          \
        if (cs->cs_cache_semaphore == 0 ) {                                \
            (void)wakeup(&cs->cs_cache_semaphore);                         \
	}                                                                  \
    }                                                                      \
    else {                                                                 \
	/*                                                                 \
	 * Log that we had an unnatural state                              \
	 */                                                                \
	changer_error_logger_rw (pd, cs, module,                           \
		   "CHANGER_REMOVE_READER attempted in invalid state");    \
    }                                                                      \
    CCMN_UNLOCK (pd);                                                      \
}

/*
 *
 * Changer Structures Declarations:
 */
typedef	struct changer_specific {
    U32		cs_flags;	/* Changer flags.			*/
    U32		cs_state_flags;	/* STATE - UNIT_ATTEN, RESET etc.	*/
    U32		cs_support;	/* Functions supported by this device.	*/
    U32		cs_resid;	/* Last	operation residual count.	*/
    U32		cs_snsinfo;	/* Last	sense information bytes.	*/
    CAM_U8	cs_snskey;	/* Last	Sense Key.			*/
    TRANSLATION	*cs_trans;	/* TRANSLATION initialized when	device	*/
				/*   is opened (by changer_spec_setup).	*/
    PATH	*cs_path;	/* Pointer to the path structure being used */
    CAM_EEI_STATUS cs_eei_status; /* The EEI status quadword.		*/
    MSS		*cs_mss_changer_rpt; /* EHM Changer specific reporting.	*/
    struct changer_timeouts cs_timeouts; /* Command timeout table.	*/
    u_long	cs_clus_directions;  /* Bit field of cluster directions */
    I32         cs_cache_semaphore; /* Counting semaphore used to moderate
				     * access to cs_path and cs_trans. 
				     * Can't safely change them if an 
				     * IO is in flight
				     */
    u_long      cs_waiting_writers; /* A count of the number of writers
                                     * waiting for access to the counting 
                                     * semaphore, This will be used to
                                     * allow joining readers to see if they
                                     * should hold off and let the writers
                                     * through. Without this opens
                                     * could stall for inordinate periods
				     * of time
				     */ 
} CHANGER_SPECIFIC;

/*
 * You must increment the version number if you	change the structure.
 */
#define	CHANGER_SPECIFIC_VERS	0x3	/* Changer specific version.	*/

/*
 * The changer_action struct is passed down to the changer action
 * routines to be filled in based on success or	failure	of the
 * command.
 */
typedef	struct changer_action {
	DCB_SCSIIO	*act_ccb;	/* The ccb that	is returned	*/
	I32		act_ret_error;	/* Error code if any		*/
	U32		act_fatal;	/* Is this considered fatal	*/
	U32		act_ccb_status;	/* The ccb status code		*/
	U32		act_scsi_status;/* The scsi error code		*/
	U32		act_chkcond_error;/* The check condition error	*/
} CHANGER_ACTION; 

/*
 * CHANGER_ACTION defines
 * action.fatal	flags;
 */
#define	ACT_FAILED		0x00000001	/* This	action has failed */
#define	ACT_RESOURCE		0x00000002	/* Resource problem (memory)*/
#define	ACT_PARAMETER		0x00000004	/* Invalid parameter	*/
#define	ACT_RETRY_EXCEDED	0x00000008	/* Retry the operation count
						 * count has been excede */
#define	ACT_INTERRUPTED		0x00000010	/* Signal interruption	*/

/*
 * Retry limit for SCSI	status of busy:
 */
#define	CHANGER_RETRY_LIMIT	100

/*
 * Defines for the changer_online routine.
 */
#define	OPEN_UNIT	0x00000001	/* Go thru full	open		*/
#define	NO_TIME		0x00000002	/* DO wait for full ready time 
					 * of unit 
					 */

#define	CHANGER_MIN_SENSE	14	/*
					 * Minimun size	of sense
					 * data	we need.
					 */
/*
 * CHANGER_REL_MEM will examine an DCB_SCSIIO ccb to see if
 * the data buffer pointer is non NULL.	If so the macro	will
 * call	ccmn_rel_dbuf with the size to release the memory 
 * back	to the pools.
 */
#define	CHANGER_REL_MEM(c3cb); {					\
    if ( (c3cb)->cam_data_ptr != (u_char *)NULL	) {			\
	ccmn_rel_dbuf( (c3cb)->cam_data_ptr, (c3cb)->cam_dxfer_len );	\
	(c3cb)->cam_data_ptr = (u_char *)NULL;				\
	(c3cb)->cam_dxfer_len =	(U32)NULL;				\
    }									\
}

#define CHANGER_TIME_DEF	((u_long)SIM_DEFAULT_TIMEOUT)
#define CHANGER_RETRIES (2)	/* Maximum times commands retried */

/*
 * Whether we sleep in the work	routines 
 * changer_move_changer(), changer_load(), etc.
 */
#define	CHANGER_SLEEP	0x00000000
#define	CHANGER_NOSLEEP	0x00000001

/*
 * Success and failure defines
 */
#define	CHANGER_SUCCESS		00
#define	CHANGER_FAIL		-1

/*
 * ERROR reports defines
 */
#define	CHANGER_HARD_ERRS	1
#define	CHANGER_ALL_ERRORS	2

/*
 * Flags defines for the routines that do changer action.
 * Please NOTE THAT CMD_IMED is	used all over..	Do not
 * define any command flags as 0x01
 */
#define	CMD_IMED	0x1		/* Command immediate modifier	*/

/*
 * Defines for what changer_ccb_chkcond returns
 */
#define	CHK_SENSE_NOT_VALID	0x0001	/* Valid bit is	not set	in sense */
#define	CHK_EOM			0x0002	/* End of media			*/
#define	CHK_FILEMARK		0x0003	/* File	mark detected		*/
#define	CHK_ILI			0x0004	/* Incorrect length		*/
#define	CHK_NOSENSE_BITS	0x0005	/* NOSENSE key and no bits	*/
#define	CHK_RECOVER		0x0006	/* soft	error reported		*/
#define	CHK_NOT_READY		0x0007	/* Device is not ready		*/
#define	CHK_MEDIUM_ERR		0x0008	/* Device reported hard	changer error*/
#define	CHK_HARDWARE		0x0009	/* Hardware error		*/
#define	CHK_ILL_REQ		0x000a	/* Illegal request maynot support cmd*/
#define	CHK_UNIT_ATTEN		0x000b	/* Unit	attention (ready???)	*/
#define	CHK_DATA_PROT		0x000c	/* write protected		*/
#define	CHK_BLANK_CHK		0x000d	/* Blank check erased changer	*/
#define	CHK_VENDOR_SPEC		0x000e	/* Vendor specific (no idea)	*/
#define	CHK_COPY_ABORT		0x000f	/* Copy	cmd aborted		*/
#define	CHK_CMD_ABORTED		0x0010	/* Command has been aborted	*/
#define	CHK_EQUAL		0x0011	/* Search cmd equal		*/
#define	CHK_VOL_OFLOW		0x0012	/* Phys	end of media, data in buf */
#define	CHK_MIS_CMP		0x0013	/* Miscompare src != media	*/
#define	CHK_UNKNOWN_KEY		0x0014	/* Bogus sense key		*/
#define	CHK_CHK_NOSENSE		0x0015	/* Sense Auto sense valid bit 0	*/
#define	CHK_INFORMATIONAL	0x0016	/* Informational message...	*/

#define	CHANGER_INFO(sns, long_val) {		\
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

#define	CHANGER_OR_STATE( pd, flags )					\
{									\
	CCMN_LOCK( (pd)	);						\
	((CHANGER_SPECIFIC *)((pd)->pd_dev_specific))->cs_state_flags |= (flags); \
	CCMN_UNLOCK( (pd) );						\
}

#define	CHANGER_CLR_STATE( pd, flags )					\
{									\
	CCMN_LOCK( (pd)	);						\
	((CHANGER_SPECIFIC *)((pd)->pd_dev_specific))->cs_state_flags	\
			&= ~((U32)(flags));				\
	CCMN_UNLOCK( (pd) );						\
}

#define	CHANGER_OR_FLAGS(pd, flags )					\
{									\
	CCMN_LOCK( (pd)	);						\
	((CHANGER_SPECIFIC *)((pd)->pd_dev_specific))->cs_flags |= (flags); \
	CCMN_UNLOCK( (pd) );						\
}

#define	CHANGER_CLR_FLAGS( pd, flags )					\
{									\
	CCMN_LOCK( (pd)	);						\
	((CHANGER_SPECIFIC *)((pd)->pd_dev_specific))->cs_flags &= ~((U32)(flags));\
	CCMN_UNLOCK( (pd) );						\
}

#define	CHANGER_BERROR( buf, count, error )				\
{									\
	(buf)->b_resid = (count);					\
	(buf)->b_error = (error);					\
	(buf)->b_flags |= B_ERROR;					\
}

#define	CHANGER_NULLCCB_ERR( act_ptr, trans, pd, mod ) {			\
	CCMN_LOCK( (pd)	);						\
	CAM3_ERROR((mod), "NULL CCB returned", CAM_SOFTWARE,		\
		(CCB_HEADER *)NULL, (trans),				\
		(u_char	*)NULL);					\
	CCMN_UNLOCK( (pd) );						\
	(act_ptr)->act_fatal |=	(ACT_RESOURCE |	ACT_FAILED);		\
	(act_ptr)->act_ret_error = ENOMEM;				\
}

/*
 * This macro is used to close out the unit.
 */

#define CHANGER_CLOSE( devt, pdrv_dev, trans, cs_spec, ccmn_flags, lock_flags) { \
	if ((lock_flags) & PD_LOCKED)					\
		CCMN_UNLOCK( (pdrv_dev) );				\
	CCMN_LOCK( (pdrv_dev) );					\
        while(( (pdrv_dev)->pd_drv_state & CCMN_SPECIAL ) != 0 )	\
        {								\
                CCMN_SLEEPUNLOCK( &(pdrv_dev)->pd_drv_state,		\
                        PZERO, (pdrv_dev) );				\
                CCMN_LOCK( (pdrv_dev) );				\
        }								\
	if( (cs_spec->cs_clus_directions & CS_CLOSED_PATH_MON) == 0)	\
		ccmn_stop_path_monitor3( trans , pdrv_dev,		\
				(PD_LOCKED | PD_LOCK_ON_EXIT));		\
	ccmn_cleanup_paths3( (trans), (PD_LOCKED | PD_UNLOCK_ON_EXIT));	\
        ccmn_release_dev_desc3((trans), (PD_UNLOCKED | PD_UNLOCK_ON_EXIT)); \
        xpt_unit_unlock_exclus( (trans), changer_reg_nu );		\
	CCMN_LOCK( (pdrv_dev) );					\
        (cs_spec)->cs_state_flags &= ~(CHANGER_OPENED_STATE |		\
				       CHANGER_RESERVE_CONFLICT_STATE |	\
   				       CHANGER_EXCLUSIVE_OPEN);		\
        CCMN_CLR_DRV_STATE( (pdrv_dev), (ccmn_flags),			\
		(PD_LOCKED | ((lock_flags) & PD_LOCK_ON_EXIT)));	\
}

/* EHM reporting index defines */
#define CHANGER_REVISION_IDX		 0
#define CHANGER_RESID_IDX		 1
#define CHANGER_SENSE_INFO_IDX		 2
#define CHANGER_SENSE_KEY_IDX		 3
#define CHANGER_PD_SOFT_ERR_IDX		 4
#define CHANGER_PD_HARD_ERR_IDX		 5
#define CHANGER_ACTIVE_PATHS_IDX	 6
#define CHANGER_STANDBY_PATHS_IDX	 7
#define CHANGER_FAILED_PATHS_IDX	 8
#define CHANGER_DONOT_USE_PATHS_IDX	 9
#define CHANGER_PATH_FAIL_LIMIT_IDX	10
#define CHANGER_SUBSYS_ID_IDX		11
#define CHANGER_CONSISTENT_NAME		12
#define CHANGER_SPECIFIC_ADDR		13
#define CHANGER_CLUS_DIRS_IDX		14
#define CHANGER_MAX_XFER_IDX		15
#define CHANGER_MANUFACTURER_ID_IDX     16
/* add index here and increase CHANGER_NUM_EHM_REP */
#define CHANGER_NUM_EHM_REP		17

#define CHANGER_PATH_FAIL_LIMIT	1 /* number of events before we declare
				     this path down */

#define NEEDED_SENSE_BYTES	14	/* the minimum number of sense */
					/* bytes needed to determine */
					/* the reason for Check Cond */
/*
 * Check whether we have the minimum required sense data bytes.
 */
#define CHECK_SENSE_RESID(c3cb)					\
( ((c3cb)->cam_sense_len - (c3cb)->cam_sense_resid) 		\
	>= NEEDED_SENSE_BYTES )

#define PD_NO_DEVICE    0x01    /* Device didn't respond to TUR but was */
				/* opened anyway */
#define PD_ONLINE       0x02    /* Device responded to TUR */
#define PD_REC_INPROG	0x04    /* Recovery in progress */

#define IO_CONT         0       /* Leave request on queue and return */
#define IO_DONE         1       /* Request completed sucessfully */
#define IO_FAILURE      2       /* Request completed with error */
#define IO_RETRY        3       /* Request must be retried */
#define IO_RECOVER      4       /* Start recovery before retry */

/* 
 * Max # of init_element cmds to issue to get the device ready.
 */
#define MAX_INIT_ELEM_FOR_READY	2

#define GET_CS(tr) \
    ((CHANGER_SPECIFIC *)((CCMN_SPECIFIC *)(tr->pd_specific))->pd_dev_specific)

/*
 * NOTE: changer_timeouts are defined as u_long in mchanger.h,
 *       but these really should be defined as "int"'s.
 */
#define GET_INIT_TIMEOUT(tr) \
        (int)(GET_CS(tr)->cs_timeouts.ct_init_tmo)
#define GET_READ_STATUS_TIMEOUT(tr) \
	(int)(GET_CS(tr)->cs_timeouts.ct_read_status_tmo)
#define GET_MOVE_TIMEOUT(tr) \
	(int)(GET_CS(tr)->cs_timeouts.ct_move_tmo)
#define GET_EXCHANGE_TIMEOUT(tr) \
	(int)(GET_CS(tr)->cs_timeouts.ct_exchange_tmo)
#define GET_POSITION_TIMEOUT(tr) \
	(int)(GET_CS(tr)->cs_timeouts.ct_position_tmo)
#define GET_PREVENT_ALLOW_TIMEOUT(tr) \
	(int)(GET_CS(tr)->cs_timeouts.ct_prevent_allow_tmo)
#define GET_REQUEST_VOLUME_TIMEOUT(tr) \
	(int)(GET_CS(tr)->cs_timeouts.ct_request_volume_tmo)
#define GET_SEND_VOLUME_TIMEOUT(tr) \
	(int)(GET_CS(tr)->cs_timeouts.ct_send_volume_tmo)
#define GET_RESERVE_TIMEOUT(tr) \
	(int)(GET_CS(tr)->cs_timeouts.ct_reserve_tmo)
#define GET_RELEASE_TIMEOUT(tr) \
	(int)(GET_CS(tr)->cs_timeouts.ct_release_tmo)

#define GET_READY_TIME(pd) \
	(((pd)->pd_dev_desc->dd_ready_time > 0) ? \
	 (pd)->pd_dev_desc->dd_ready_time : SZ_READY_DEF)

#endif /* _CAM_CHANGER_H_ */
