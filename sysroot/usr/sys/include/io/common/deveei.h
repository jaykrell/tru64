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

#ifndef _DEVEEI_H_
#define _DEVEEI_H_

/*
 ***************************************************************************
 *                     !!!!! NOTE !!!!!
 * 
 * THIS FILE IS INCLUDED BY THE DECNSR PRODUCT.  PLEASE DO NOT CHANGE THE 
 * INTERFACES WITHIN IT WITHOUT NOTIFYING THE DECNSR GROUP!
 *
 ***************************************************************************
 */

/*
 * HISTORY
 */
/*
 * @(#)$RCSfile: deveei.h,v $ $Revision: 1.1.28.1 $ (DEC) $Date: 2001/12/05 21:00:32 $
 */

/*********************************************************************

EEI stands for `Extended Error Information' and the following
information describes what EEI is and how it should be used.

EEI Overview -

 The EEI structure is designed to provide two levels of information.
 At the first level an abstract EEI status is provided while, at the
 second level, through the use of the EEI Extended information flags,
 the unabstracted architecture specific error information is provided.
 It should be noted that not every EEI status has architecture
 specific information associated with it.  An example of this is the
 EEI_RESERVE_PENDING status.  This status represents a generic
 software conditions in the state of the device driver; with no
 associated architecture specific information.  Because of this the
 EEI status should always be considered as the primary status and
 should always be interrogated first.  The architecture specific
 information is only provided as additional information and is only
 valid if the corresponding EEI flag (e.g. EEI_CAM_DATA_VALID) is set.

The EEI Status -

 EEI status values are assigned in order of increasing priority --
 a higher numbered status indicates a more significant error.  Typically,
 pre-processing errors (e.g. invalid parameters) are assigned the lowest
 priorities, followed by device-related errors (e.g. timeout), then
 controller or driver errors, and finally device availability errors
 (e.g. no such device).

EEI Status Recording -

 EEI statuses are recorded whenever an I/O or device related error
 occurs by device drivers which implement the EEI mechanism.  Upon
 encountering an error, the device driver categorizes and translates
 the error into an EEI status value.  Then, if no previous EEI status
 of a greater (higher) value has been recorded, the device driver
 records the EEI status in its internal EEI status state structure.
 Any associated architecture specific information maintained by the
 device driver may also be recorded.  Once this information is recorded,
 the device driver continues and the I/O is rundown its normal path,
 usually resulting in an errno value returned to the application.

 When recording EEI status information the device driver will use the
 EEI status `order of precedence' to determine what information to
 save.  The EEI Precedence Ordering Table (eei_PrecendenceTable[])
 will determine the EEI status precedence.  An EEI status farther
 down in this table will always replace an event higher in the table.

  eei_PrecedenceTable[] = {
	/- Success Status -/
	EEI_SUCCESS,		/- EEI Success status == EEI_NO_STATUS  -/
	EEI_DEVSOFT_FAILURE,	/- Device medium error (soft error)     -/

	/- Informational Status -/
	EEI_BBR_DONE,		/- Bad Block Replacement performed      -/
        EEI_UNCATEGORIZED,	/- Uncategorized, use CAM/SCSI status   -/
	EEI_DEVSTATE_FAILURE,	/- Device inoperable (needs initialize) -/

	/- Retriable Errors -/
	EEI_CNTBUSY_FAILURE,	/- HBA/Controller Busy (retriable)      -/
	EEI_DEVBUSY_FAILURE,	/- Device is busy (retriable)           -/

	/- Software Errors -/
	EEI_INVALID_PARAM,	/- Invalid software parameter provided  -/
	EEI_ADVFS_DMN_PANIC,	/- AdvFS domain panic			-/
	EEI_MALLOC_FAILURE,	/- Memory allocation failed             -/
	EEI_CXALLOC_FAILURE,	/- Shared Device allocation failed      -/
				/- Means: cannot open busy tape device  -/
	EEI_TAPE_POS_LOST,	/- Tape position lost                   -/
	EEI_GROSSSW_FAILURE,	/- Gross internal software error        -/

	/- Hardware Errors -/
	EEI_DEVBIO_FAILURE,	/- Device/bus I/O error (retriable)     -/
	EEI_DEVREQ_FAILURE,	/- Device request illegal/unsupported   -/
	EEI_DEVHARD_FAILURE,	/- Device hardware error (hard error)   -/
	EEI_ABORTIO_FAILURE,	/- Abort/Timed out I/O occured          -/
	EEI_CNTRLR_FAILURE,	/- HBA/Controller failure (hard error)  -/

	/- Availability Errors -/
	EEI_MUNSA_REJECT,	/- DRD rejected this device		-/
	EEI_RESERVE_PENDING,	/- Shared Device Re-reserve pending     -/
	EEI_DEVPATH_RESET,	/- Device/bus reset occured             -/
	EEI_DEVPATH_CONFLICT,	/- Device access denied (path conflict) -/
	EEI_DEVPATH_FAILURE	/- Device not there (powered off?)      -/
  };

EEI Persistence -

 A device driver may supply an ioctl interface in order for applications to 
 obtain EEI information. For example, the CAM tape driver uses the MTIOCGET 
 ioctl interface to provide EEI information to applications.  The device
 driver will not clear or replace EEI status until the (MTIOCGET) ioctl is 
 called.  This means that the EEI status is persistent in the device driver 
 until the next (MTIOCGET) ioctl call.  

 In this way, the EEI status information recorded inside of the device 
 driver is guaranteed to be persistent between close and open. This is done
 so that out of band or asynchronous events can be detected by calling
 the ioctl interface. For example, a call to open with the O_NDELAY flag
 can uncover a Not Ready condition in the device but still return a
 successful status.  Other examples include errors detected during a close
 sequence or third party bus resets between close and open.

 In order to 1) uncover out of band errors and 2) clear the device
 driver's internal EEI status information, applications should invoke the
 ioctl immediately after opening the device.  It is the duty of the consumer 
 to clear or initialize the recorded EEI status presented via the ioctl
 interface.   For example, applications which use the information supplied
 by the CAM tape driver via the EEI mechanism should call MTIOCGET
 immediately after opening the device.

***************************************************************************/
 
/*
 * EEI error statuses
 */

#define EEI_SUCCESS          0x0000  /* EEI Success status                   */

#define EEI_NO_STATUS        0x0000  /* No EEI status available              */

#define EEI_UNCATEGORIZED    0x0100  /* Uncategorized, use CAM/SCSI status   */
#define EEI_INVALID_PARAM    0x0200  /* Invalid software parameter provided  */
#define EEI_ADVFS_DMN_PANIC  0x0300  /* AdvFS domain panic                   */	
#define EEI_MALLOC_FAILURE   0x0400  /* Memory allocation failed             */
#define EEI_CNTBUSY_FAILURE  0x0600  /* HBA/Controller Busy (retriable)      */
#define EEI_GROSSSW_FAILURE  0x0800  /* Gross internal software error        */

#define EEI_BBR_DONE         0x2000  /* Bad Block Replacement performed      */
#define EEI_DEVBUSY_FAILURE  0x2200  /* Device is busy (retriable)           */
#define EEI_DEVBIO_FAILURE   0x2400  /* Device/bus I/O error (retriable)     */
#define EEI_DEVSOFT_FAILURE  0x2600  /* Device medium error (soft error)     */
#define EEI_TAPE_POS_LOST    0x2800  /* Tape position lost                   */
#define EEI_DEVREQ_FAILURE   0x2A00  /* Device request illegal/unsupported  */

#define EEI_DEVSTATE_FAILURE 0x3200  /* Device inoperable (needs initialize) */
#define EEI_DEVHARD_FAILURE  0x3400  /* Device hardware error (hard error)   */
#define EEI_ABORTIO_FAILURE  0x3600  /* Abort/Timed out I/O occured          */

#define EEI_CNTRLR_FAILURE   0x4200  /* HBA/Controller failure (retriable)   */
#define EEI_CXALLOC_FAILURE  0x4400  /* Shared Device allocation failed      */
#define EEI_MUNSA_REJECT     0x5100  /* Shared Device Re-reserve pending     */
#define EEI_RESERVE_PENDING  0x5200  /* Shared Device Re-reserve pending     */

#define EEI_DEVPATH_FAILURE  0x6200  /* Device not there (powered off?)      */
#define EEI_DEVPATH_RESET    0x6400  /* Device/bus reset occured             */
#define EEI_DEVPATH_CONFLICT 0x7200  /* Device access denied (path conflict) */

/* 
 * EEI AM Event Flags; common definitions with the ASE/Clusters AM
 * driver; provided to recapitulate EEI status values into AM driver 
 * `Event Type' masks.
 */

#define EEI_AM_PATH_FAILURE        0x01  /* eq. EEI_DEVPATH_FAILURE         */
#define EEI_AM_RESERVATION_RESET   0x02  /* eq. EEI_DEVPATH_RESET           */ 
#define EEI_AM_RESERVATION_FAILURE 0x04  /* eq. EEI_DEVPATH_CONFLICT        */
#define	EEI_AM_SOFT_DEV_ERROR      0x08	 /* eq. EEI_DEVSOFT_FAILURE         */
#define	EEI_AM_HARD_DEV_ERROR	   0x10	 /* eq. EEI_DEVHARD_FAILURE         */

/*
 * Extended information flags; provided for consumers who wish to
 * examine architecture specific data.
 */

#define EEI_ARCH_FLAGS_MSK  0xFF000000  /* 8 bits reserved for arch flags */
#define EEI_CAM_DATA_VALID  0x01000000  /* Extended CAM data valid        */

#define EEI_CAM_FLAGS_MSK      0x000F  /* 4 bits reserved to CAM flags */
#define EEI_CAM_STATUS_VALID   0x0001  /* CAM status is valid          */
#define EEI_SCSI_STATUS_VALID  0x0002  /* SCSI status is valid         */
#define EEI_SCSI_SENSE_VALID   0x0004  /* SCSI Sense data is valid     */

/*
 * EEI DEVEEI status structure
 */

/* Be sure to change EEI_VERSION when the dev_eei_status struct is revised */

#define EEI_VERSION        0x02  
#define EEI_ARCH_DATA_LEN   512

typedef struct dev_eei_status {
    long version;               /* RW : Version 2                    */
    u_int status;               /* RO : return EEI status            */
    u_int flags;                /* RO : returned extended info flags */
    union {
        struct {                    /* RO : CAM/SCSI-specific data    */
            u_int cam_status;              
            u_int scsi_status;             
	    u_char scsi_sense[EEI_ARCH_DATA_LEN - (sizeof(int)*2)];
        } cam;
        u_char data[EEI_ARCH_DATA_LEN];    /* RO : "Unknown" architecture */
    } arch;
} DEV_EEI_STATUS;

#endif /* not _DEVEEI_H_ */








