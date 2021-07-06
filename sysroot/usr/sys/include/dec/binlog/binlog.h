/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: binlog.h,v $
 * Revision 1.1.46.1  2003/05/20  18:02:16  Andrew_Duane
 * 	Add ELCT_EV7_QBOX
 *
 * Revision 1.1.41.2  2001/11/27  18:23:02  Jem_Treadwell
 * Merge Information:  Non-Visual Merge: User specified revision 1.1.43.1
 *     User Revision:  wcalphaos_br:1.1.41.1 Local Ancestor: n/a
 *    Merge Revision:  1.1.43.1
 *   Common Ancestor:  1.1.37.1
 * 	Merge from yankee IPK to wcalpha
 *
 * Revision 1.1.43.1  2001/10/29  21:58:46  Jem_Treadwell
 * Merge Information:  Non-Visual Merge: User specified revision 1.1.39.1
 *     User Revision:  yankeeos_bl9:1.1.37.1 Local Ancestor: n/a
 *    Merge Revision:  1.1.39.1
 *   Common Ancestor:  1.1.37.1
 * 	Backport QARs 86249 & 90094 from wildcat to yankee IPK
 * 
 * Revision 1.1.41.1  2001/10/24  22:19:08  Rajesh_R
 * 	Add major numbers for Marvel 0x6a0/0x6b0 machine checks.
 * 
 * Revision 1.1.39.1  2001/05/23  21:01:55  Jem_Treadwell
 * 	Replace ELCT_DBLERRHLT with ELCT_SYSCONSOLE, and add ELCT_EMX_ERRPKT.
 * 
 * Revision 1.1.37.1  1999/12/15  21:37:30  Jem_Treadwell
 * 	Added prototype for binlog_alloc_evm
 * 
 * Revision 1.1.35.1  1999/10/04  20:40:11  Stuart_Hollander
 * 	merge from ptwild bl1 to bl4
 * 
 * Revision 1.1.33.2  1999/08/23  14:40:31  Cheryl_Deleo
 * 	Added a hardware event define for the StorageWorks Command Console (SWCC) to
 * 	help differentiate logs generated from SWCC versus the I2O driver.
 * 	[1999/08/19  19:54:14  Cheryl_Deleo]
 * 
 * Revision 1.1.11.9  1999/02/04  19:34:19  Mark_Bokhan
 * 	Add bus, target and lun fields to ceh_rhdr (QAR 68001)
 * 	[1999/02/03  21:14:51  Mark_Bokhan]
 * 
 * Revision 1.1.11.8  1999/01/20  19:54:55  Jin_Chen
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTEV6OS_BL8:PTFCOS_BL3 **
 * 		** Ancestor revision:	1.1.14.4 **
 * 		** Merge revision:	1.1.25.5 **
 * 	 	** End **
 * 	[1999/01/20  19:50:13  Jin_Chen]
 * 
 * Revision 1.1.11.7  1998/11/17  15:23:29  Mark_Bokhan
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.11.5 **
 * 		** Merge revision:	1.1.11.6 **
 * 	 	** End **
 * 	Add EL_CAM_WIDE for expanded subid_unitnum definition.
 * 	[1998/11/13  18:27:28  Mark_Bokhan]
 * 
 * Revision 1.1.25.5  1998/10/30  18:04:56  Mike_Winiarski
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit -visual **
 * 		** Ancestor revision:	1.1.25.3 **
 * 		** Merge revision:	1.1.25.4 **
 * 	 	** End **
 * 	Added new major event types (el_sub_id.subid_class) for
 * 	     Double Error Halt
 * 	     (Un)correctable Environmentals
 * 	     Correctables Reporting Disabled
 * 	[1998/10/29  17:22:23  Mike_Winiarski]
 * 
 * Revision 1.1.25.4  1998/10/30  17:33:14  Dan_Duval
 * 	add packet type for I2O block-storage errors
 * 	[1998/10/28  20:12:36  Dan_Duval]
 * 
 * Revision 1.1.11.6  1998/10/28  18:17:38  Mark_Bokhan
 * 	Fix QAR 64946: -std1 build warnings.
 * 	[1998/10/23  12:50:16  Mark_Bokhan]
 * 
 * Revision 1.1.25.3  1998/10/22  13:19:18  Mark_Bokhan
 * 	Fix -std1 build warnings.
 * 	[1998/10/19  19:30:47  Mark_Bokhan]
 * 
 * Revision 1.1.11.5  1998/10/05  14:00:12  Mark_Bokhan
 * 	Add Common Errlog Header definitions.  This new Errlog Header has a
 * 	common format across the three major operating systems: Digital UNIX,
 * 	OpenVMS and Digital's Windows NT.
 * 	[1998/09/29  18:17:50  Mark_Bokhan]
 * 
 * Revision 1.1.11.4  1998/02/20  23:58:12  Andrew_Duane
 * 	binlog_hdrinit is void, not int.
 * 	[1998/02/11  19:17:25  Andrew_Duane]
 * 
 * Revision 1.1.11.3  1997/09/03  14:49:17  Jin_Chen
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL6:PTCOS_BL10 **
 * 		** Ancestor revision:	1.1.9.2 **
 * 		** Merge revision:	1.1.14.4 **
 * 	 	** End **
 * 	merge of PTmin BL10 changes
 * 	[1997/09/03  14:10:38  Jin_Chen]
 * 
 * Revision 1.1.14.4  1997/05/30  18:36:50  Janet_Schank
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.14.3 **
 * 		** Merge revision:	1.1.14.3 **
 * 	 	** End **
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rPTCOS;PTHW1OS_BL3;<> **
 * 		** Ancestor revision:	1.1.14.2 **
 * 		** Merge revision:	1.1.14.3 **
 * 	 	** End **
 * 	[1997/05/30  12:07:23  Janet_Schank]
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rPTCOS;PTHW1OS_BL3;<> **
 * 		** Ancestor revision:	1.1.9.2 **
 * 		** Merge revision:	1.1.14.2 **
 * 	 	** End **
 * 	[1997/05/27  12:36:53  Janet_Schank]
 * 	Added ELMSGT_FILTER define which will be used by the
 * 	"filter" error logger.
 * 	[1997/05/14  15:05:49  Janet_Schank]
 * 
 * Revision 1.1.14.3  1997/05/28  17:20:09  Seema_Peterson
 * 	Added support to log ADVFS domain panic in binary.errlog
 * 	[1997/05/27  15:02:46  Seema_Peterson]
 * 
 * Revision 1.1.14.2  1997/05/06  21:45:38  Donald_Dutile
 * 	Change BINLOG_BUFMAX to 1MB;
 * 	add new define BINLOG_BUFSTD and set to 32KB.
 * 	part of making binlog buffer dynamically & more approp. sized.
 * 	[1997/05/06  21:22:09  Donald_Dutile]
 * 
 * Revision 1.1.11.2  1997/03/03  15:32:36  Robin_Miller
 * 	Adding function prototypes for binlog* functions.
 * 	[1997/03/03  14:57:00  Robin_Miller]
 * 
 * Revision 1.1.9.2  1995/03/24  18:47:12  Michael_Schloss
 * 	UERF/DECevent/binlogger support
 * 	[1995/03/23  19:30:00  Michael_Schloss]
 * 
 * Revision 1.1.7.3  1994/05/11  19:24:37  Stuart_Hollander
 * 	merge of agoshw2 bl6 to gold pre-bl11
 * 	Revision 1.1.5.3  1994/04/28  17:16:46  Robin_Lewis
 * 	fixed binlog header to id platforns correctly
 * 	[1994/04/28  17:09:44  Robin_Lewis]
 * 	binlog header fix to ID systems correctly
 * 	[1994/04/27  19:42:01  Robin_Lewis]
 * 
 * Revision 1.1.7.2  1994/02/25  21:21:10  Stuart_Hollander
 * 	merge agoshw2 bl3 to gold
 * 	[1994/02/17  20:45:04  Stuart_Hollander]
 * 
 * Revision 1.1.5.2  1994/02/09  22:24:16  William_Dallas
 * 	Added support for the xcr controller (EISA RAID) record num 198
 * 	[1994/02/08  21:59:38  William_Dallas]
 * 
 * Revision 1.1.2.6  1992/06/25  22:30:39  Peter_Smith
 * 	merged in Silver BL8
 * 	[92/06/25  22:24:04  Peter_Smith]
 * 
 * Revision 1.1.2.5  92/05/28  15:36:42  Peter_Mott
 * 	Change ELCT_ numbers to conform with UEG request...
 * 	[92/05/28  15:35:41  Peter_Mott]
 * 
 * Revision 1.1.2.4  92/05/28  15:03:00  Peter_Mott
 * 	Modify ELCT_STKDMP, ELCT_EXPTFLT, ELCT_STATE to conform with requested
 * 	values from UEG
 * 	[92/05/28  15:02:18  Peter_Mott]
 * 
 * Revision 1.1.2.3  92/05/28  13:21:33  Peter_Mott
 * 	Add subid class ELCT_EXPTFLT, to encompass ALPHA 660 and 630 exception packets.
 * 	Add subid class ELCT_STATE, to encompass ALPHA machine state packets.
 * 	[92/05/28  13:21:00  Peter_Mott]
 * 
 * Revision 1.1.2.2  92/05/28  07:24:53  Peter_Smith
 * 	bmerge
 * 	[92/05/27  09:10:55  Peter_Smith]
 * 	Moved from sys/binlog.h
 * 	[92/05/26  14:52:27  Peter_Smith]
 * 
 * Revision 1.1.2.4  92/04/30  10:54:54  Anton_Verhulst
 * 	Merge in BL6_3.
 * 	[92/04/30  10:54:26  Anton_Verhulst]
 * 
 * Revision 1.1.2.3  92/03/18  22:24:39  Shashi_Mangalat
 * 	Merged in Silver BL5
 * 	added CAM.  64bit cleanup in struct el_rhdr and el_sub_id
 * 	  [Scott_Cranston]
 * 	[92/03/18  22:03:58  Shashi_Mangalat]
 * 
 * Revision 1.1.2.2  92/03/06  16:42:16  Peter_Smith
 * 	Merge for submit.
 * 	[92/03/06  16:36:43  Peter_Smith]
 * 	In anticipation of Silver BL5 merge.
 * 	[92/03/06  16:29:46  Peter_Smith]
 * 
 * 
 * $EndLog$
 */
/*
 *      @(#)$RCSfile: binlog.h,v $ $Revision: 1.1.46.1 $ (DEC) $Date: 2003/05/20 18:02:16 $
 */

/* 
 * logs from origional file location (kernel/sys/binlog.h)
 *
 * 	Decided, from code review, to remove open and seqnum fields from
 * 	struct binlog_getstatus for security reasons.
 * 	[92/02/19  13:25:24  Scott_Cranston]
 * 
 * 	Added an 'L' to the value for BUFMIN and BUFMAX as these are now used
 * 	with a long data type.
 * 	[92/02/07  12:45:07  Scott_Cranston]
 * 
 * 	  -  deleted class code ELCT_EXPTFLT... was VAX specific.
 * 
 * 	  -  in struct binlog_bufhdr changed int's to long's so that the
 * 	     data structure would be sized for machine architecture boundaries.
 * 	[92/02/07  09:54:36  Scott_Cranston]
 * 
 * 	Make some items unsigned.
 * 	[92/01/28  18:54:23  Scott_Cranston]
 * 
 * 	  -  changed some long's to int's for 64-bit cleanliness.
 * 
 * 	  -  moved rhdr_sid and rhdr_elver so they would be a constant
 * 	     offset from start of header regardless of 32/64 bit arch.
 * 	     This is to help the report generator easly find this info
 * 	     so it can determine the machine arch.
 * 	[92/01/28  17:46:55  Scott_Cranston]
 * 
 * 	bcreate'ed file worng and had an 'rcsid'.
 * 	[92/01/15  08:57:40  Scott_Cranston]
 * 
 * 	Initial file creation.
 * 	[92/01/14  15:59:52  Scott_Cranston]
 * 
 */

#ifndef __BINLOG__
#define __BINLOG__ 

#ifdef __cplusplus
extern "C" {
#endif
/*
 *  This file contains the common components of a binary event log record.  
 *  The data structures and ID codes to be used are defined here.
 *
 *  This file also contains the ID codes used by/with the kernel binary
 *  event logging routines.
 *
 *  The following is a template and description for what a binary event 
 *  record looks like....
 *
 *          struct el_rec {
 *                  struct el_rhdr elrhdr;            ** mandatory component **
 *                  struct el_sub_id elsubid;         ** mandatory component **
 *                  struct EVENT-SPECIFIC-DATA
 *                  char eltrailer[EL_TRAILERSIZE];   ** mandatory component **
 *          };
 *
 *  The mandatory components must be in every event record and must be named
 *  as shown above.  The sequence of the components of an event record must
 *  be as shown.
 *
 ***************
 *
 *  The component 'elrhdr' is the primary header of the event record.  It
 *  contains vendor independent data suppled by the kernel.  The data is
 *  generic to the event being logged and does not describe the event itself.
 *  The data in elrhdr is ONLY manipulated by the kernel binary event
 *  logging routines.  An entity logging an event does not touch any element
 *  of elrhdr, doing so could produce unpredictable results.  The elrhdr 
 *  data structure is composed of the elements:
 *
 *        rhdr_reclen  -  The length in bytes of the total event record
 *                        being logged.  This is inclusive of 'elrhdr',
 *                        'elsubid', 'eltrailer' and of course the event
 *                        specific data.
 *
 *        rhdr_seqnum  -  The sequence number of the event.  When the system
 *                        boots the sequence number is initailized to start
 *                        at zero (0).  The sequence number is incremented
 *                        for each event that is attempted to be logged. 
 *
 *        rhdr_time    -  This is the time at which the event record was
 *                        created, effectively the time at which the event
 *                        occured.
 *
 *        rhdr_sid     -  The system (CPU type) identifer for the processor
 *                        which is logging the event.  This is defined as:
 *
 *                          rhdr_sid
 *                            bits                definition
 *                          --------   --------------------------------------
 *                            31:16    machine_slot[].cpu_subtype, bits <15:00>
 *                            15:00    machine_slot[].cpu_type, bits <15:00>
 *
 *                         The index into machine_slot[] is obtained by
 *                         using cpu_number().  See mach/machine.h for further
 *                         details.
 *
 *        rhdr_valid   -  A flag that signals that the event record is valid.
 *                        This is either EL_INVALID or EL_VALID.
 *
 *        rhdr_pri     -  The priority level (severity) of the event being 
 *                        logged.  Allowed values are:
 *
 *                            EL_PRISEVERE - An unrecoverable/fatal error
 *                                           condition.  System or device
 *                                           operation can not continue.
 *                                           Immediate attention is required.
 *
 *                            EL_PRIHIGH   - A successfully recovered error
 *                                           condition.  An error/problem was
 *                                           detected with the system or device
 *                                           which has been corrected or is not
 *                                           fatal.  Attention to the situation
 *                                           will be needed as soon as possible.
 *
 *                            EL_PRILOW    - Non critical events, can be of an
 *                                           informational nature only.  
 *                                           Attention to the stituation can
 *                                           be given on an as needed basis.
 *
 *        rhdr_elver   -  The verision of the event record format. This is
 *                        set to ELVER.
 *
 *        rhdr_hname   -  The hostname of the system logging the event.
 *
 *        rhdr_systype -  Not used, always zero (0).
 *
 *        rhdr_mpnum   -  The number of active processors on the system.
 *                        This is set equal to machine_info.avail_cpus (see
 *                        mach/machine.h).
 *
 *        rhdr_mperr   -  The slot number of the CPU logging the event.
 *                        The slot number is obtained by using cpu_number();
 *
 *************
 *
 *  The component 'elsubid' is a sub header and contains data specific to 
 *  the event being logged.  The entity logging the event supplies the
 *  data for elsubid.  The LSUBID macro is the recomended programming interface
 *  to use for doing this.  The elsubid data structure is composed of
 *  the elements:
 *
 *        subid_class  -  A code identifing the top level catagory  that
 *                        the event being logged fits into.  These 'class'
 *                        are common across all vendors and architectures.
 *                        For example there are class codes for disk, tape,
 *                        ascii messages, etc.  The class codes are defined 
 *                        in this file.  The subid_class code is mandatory.
 *                        
 *        subid_type   -  An identifier code that is unique to the event
 *                        being logged.  This code provides a finner
 *                        ganularity description of the event than the
 *                        subid_class code does.  For example if subid_class
 *                        specifies disk, than subid_type could specify
 *                        SCSI.  These codes are to be #define'ed in a vendor
 *                        supplied unique header file.  The subid_type is 
 *                        optional and should then be set to EL_UNDEF.
 *
 *         subid_ctldevtype  -
 *                        A identifer code that specifies what the specific
 *                        kind of entity it is that is logging the event.
 *                        For a hardware device this would typically
 *                        identify the model or name.  These codes are 
 *                        to be #defined'ed in a vendor supplied unique header
 *                        file. The subid_ctldevtype is optional and should
 *                        then be set to EL_UNDEF.
 *
 *   Note:   The subid_class, subid_type, and subid_ctldevtype codes, when
 *           used together, uniquely identify what a given event record
 *           is logging.  Specificly, it uniquely identifies what the data
 *           structure is that contains the event specific data.  This
 *           is required so that the binary event log report generator
 *           (bit-to-text) tool can determine how to interpret the event
 *           specific data.... this is vendor dependent data.  
 *
 *           Mininally the subid_class is required to be used.  Depending
 *           upon the event specific data being logged either subid_type
 *           or subid_ctldevtype (or both) may not be required.  For example
 *           if subid_class is ELMSGT_SU (a startup event) than both
 *           subid_type and subid_ctldevtype can be EL_UNDEF.  In this
 *           example the class code ELMSGT_SU is sufficent for uniquely
 *           describing what is being logged.
 *           
 *
 *         subid_num   -  The number identifing the CPU, bus, controller or
 *                        adapter on which the event being logged occured. 
 *                        This item is not applicable in all cases or may
 *                        be unknown and is then set to EL_UNDEF.
 *
 *         subid_unitnum  -
 *                        The physical unit number of the device on which the
 *                        event being logged occured.  This item is not 
 *                        applicable or may be unknown and is then set 
 *                        to EL_UNDEF.
 *                        
 *                        
 *   Note:   The usage of subid_num and subid_unitnum is not clear in all
 *           cases and can be confusing.  Perhaps an example will clarify:
 *
 *               A disk subsystem consists of a contoller (connected to the
 *               system bus) and the disk drive itself.  Take for example
 *               a system with two SCSI disk contollers (0 & 1) with
 *               one disk on each contoller, physical unit numbers 4 & 6
 *               respectively.  Suppose a nonexistent memory error occured 
 *               during a DMA write to disk unit number 6.  This is a
 *               contoller problem, not a disk problem.  In this case 
 *               subid_num would be set to '1' and subid_unitnum would
 *               be EL_UNDEF.  Or, suppose a CRC error occured on a read
 *               from disk unit 4.  This is a disk error and subid_num would
 *               be set to '0' and subid_unitnum would be set to 4.
 *                        
 *           In some cases the event specifc data protion of the event
 *           record may describe the identifing numbers.  In this case
 *           subid_num and subid_unitnum may optionally be set to EL_UNDEF.
 *
 *
 *         subid_errcode  -
 *                        A code that summarizes what the eventbeing logged
 *                        is.  This is optional and may be set to EL_UNDEF.
 *
 ************
 *
 *  The 'struct EVENT-SPECIFIC-DATA' is data structure describing the event
 *  specific data being logged.  These data structures and any associated
 *  #define's should go into a vendor unique binary event logging header 
 *  file.  Generally you will #include binlog.h into this file.
 *  This file should define all the event specific data structures, 
 *  subid_type codes and subid_ctldevtype codes unique to a specific vendors
 *  needs.  At the end of this vendor unique file you may wish to do
 *  something like:
 *
 *          struct el_rec {
 *                  struct el_rhdr elrhdr;
 *                  struct el_sub_id elsubid;
 *                  union {
 *                           PUT-ALL-YOUR-EVENT-SPECIFIC-DATA-STRUCTURES-HERE
 *                           struct el_msg elmsg;      ** an example **
 *                   } el_body;
 *                  char eltrailer[EL_TRAILERSIZE];    ** mandatory component **
 *          };
 *   
 *
 *  Using the union 'el_body' may make things more convenient to use when
 *  coding up the actual binary event logging.  The struct el_msg is shown
 *  here as an example.  The el_msg is used by the kernel binary event 
 *  logging facility to capture formated kernel ASCII messages (printf) into 
 *  the binary event log.  It can also be used anywhere it is desired to put 
 *  a formatted ASCII into the binary event log.
 *
 ************
 *
 *  The eltrailer[] uniquely marks the end of an event record.  The purpose
 *  of this is to allow an application to easily search backward through a
 *  file of binary event log records (for example the binary event log file).
 *  Doing a binary search through such file is even aided by having the 
 *  trailer.  Once a trailer is identified the begining of a new event record
 *  would follow.
 *
*/



/***********  START OF class codes  (el_sub_id.subid_class)  ***************/

/*       Note:  Please give careful consideration to adding a new
 *              class code.  Be very certain that existing ones can not
 *              serve the purpose when used with appropriate 
 *              el_sub_id.subid_type and el_sub_id.subid_ctldevtyp codes.
 *
 *       Note:  For class codes labeled as an "ascii message" the data
 *              structure el_msg is always to be used to log the ascii
 *              message with.
*/

/* Hardware related events 100-199 */
#define ELCT_MCK	100		/* CPU machinechecks & exceptions */
#define ELCT_EXPTFLT	100		/* Generalized exception/ */
					/* fault. Distinguished by */
					/* subid type and subid */
					/* ctldevtyp */
#define ELCT_MEM	101		/* memory errors soft/hard */
#define ELCT_DISK	102		/* disk errors */
#define ELCT_TAPE	103		/* tape errors */
#define ELCT_DCNTL	104		/* device controller errs */
#define ELCT_ADPTR	105		/* adapter errs */
#define ELCT_BUS	106		/* bus errs */
#define ELCT_SINT	107		/* stray intr. */
#define ELCT_CTE	108		/* console event */
#define ELCT_STKDMP	109		/* stack dump */
#define ELCT_STATE	110		/* generalized machine state. */
					/* Distinguished by subid type */
					/* and subid ctldevtyp */
#define ELCT_SYSCONSOLE 113		/* system console event */
#define ELCT_DBLERRHLT  113             /* Obsolete: double err halt is a */
					/* console event */
#define ELCT_CORRENV    115             /* (un)correctable environmental */
                                        /* Distinguished by subid type */
#define ELCT_RMCK	116		/* Recoverable uncorrectable MCHKs */
#define ELCT_CORRDIS    120             /* reporting of correctables disabled */
#define ELCT_SWCC	195		/* StorageWorks Command Console (SWCC) event */
#define ELCT_I2O_ERRPKT 196		/* I2O Block Storage Event */
#define ELCT_EMX_ERRPKT	197		/* emx driver event */
#define ELCT_XCR_ERRPKT 198             /* SWXCR RAID controller Event */
#define ELCT_CAM_ERRPKT 199             /* SCSI CAM Event */


/* Software detected events 200-249 */
#define ELSW_CIPPD      201                     /* ci ppd events */
#define	ELSW_SCS	202			/* scs events */
#define	ELSW_LSM_NOTE	203			/* LSM note */
#define	ELSW_LSM_WARN	204			/* LSM warning */
#define	ELSW_LSM_CONT	205			/* LSM continuation */
#define ELSW_ADVFS_DMNPNC 206                   /* ADVFS domain panic */


/* Informational ascii messages 250-299 */
#define ELMSGT_INFO	250			/* generic info ascii message */


/* Operational Class 300-400 */


/* reload/restart 300-350 */
#define ELMSGT_SU	300			/* start up ascii message */
#define ELMSGT_SD	301			/* shutdown ascii message */
#define ELMSGT_PANIC    302                     /* ascii panic message */

/* time stamp 310 */
#define ELMSGT_TIM	310			/* time stamp */


/* usage 311-315 */

/* statistics 316-319 */

/* maintenance events 350-399 */
#define ELMSGT_DIAG	350			/* diag ascii message */
#define ELMSGT_REPAIR   351			/* repair ascii message */

/* filter log event 400 */
#define ELMSGT_FILTER	400			/* Use only with filterlog */

/* QBOX and diagnostic class codes */
#define ELCT_EV7_QBOX	900



/************************   END OF subid_class CODES  ************************/






#define BINLOG_MAGIC    0x063061L      /* kernel buffer valid indicator */

/* minimum & maximum configurable sizes of the kernel binary event log buffer */
#define BINLOG_BUFMIN    8192L   /* min size of kernel event log buffer, 8Kb */
#define BINLOG_BUFSTD   (1<<15)	 /* 32KB */ 
#define BINLOG_BUFMAX   1048576L /* max size of kernel event log buffer, 1Mb */



/* sc_state bit masks */
#define BINLOG_ON         0x1     /* binary event logging enabled */
#define BINLOG_ASCIION    0x2     /* ASCII msg binary event logging enabled */
#define BINLOG_BUFALLOCED 0x4     /* binary log buffer has been allocated */
#define BINLOG_RDWAIT     0x10    /* readers waiting */


/* binlog_alloc() return values */
#define BINLOG_NOBUFAVAIL  (char *)0    /* no buf space available */

    
/* sizes of mandatory parts of an event record
 * 
 * The original ErrLog definitions are prefixed with "EL_".
 */
#define EL_RHDRSIZE	sizeof(struct el_rhdr)
#define EL_SUBIDSIZE	sizeof(struct el_sub_id)
#define EL_MISCSIZE  	(EL_RHDRSIZE + EL_SUBIDSIZE + EL_TRAILERSIZE)
#define EL_TRAILERSIZE  4L
#define trailer "%~<^"

/*
 * The Common ErrLog Header (CEH) constants are prefixed "CEH_". Since
 * the CEH's are variable in size, we define two sets of constants that
 * will be used for malloc buffersize calculations:
 * 
 *   CEH_MIN_	prefixes the constant names for the minimum sizes
 * 		necessary.  The minimum sizes include only the mandatory
 * 		elements of the CEH.  The two TLV strings that are
 *		mandatory include the hostname and time.
 * 
 *   CEH_MAX_	prefixes the maximum sizes that the CEH can occupy.
 */
#define CEH_MIN_RHDRSIZE	sizeof(struct ceh_rhdr)
#define CEH_MIN_MISCSIZE	(CEH_MIN_RHDRSIZE + CEH_TRAILERSIZE)
/*
 * Maximum CEH adds seven more TLV string structures
 */
#define CEH_MAX_RHDRSIZE	CEH_MIN_RHDRSIZE + \
				(7*(TLV_MAX_STRLEN + TLV_OVERHEAD_SIZE))
#define CEH_MAX_MISCSIZE	(CEH_MAX_RHDRSIZE + CEH_TRAILERSIZE)
#define CEH_TRAILERSIZE	8L	/* includes 4 trailer char's and length */
#define CEH_LEADER	-2	/* 0xFFFFFFFE */


/* misc event record codes */
#define EL_INVALID 	0L      /* event record is not valid */
#define EL_VALID 	1L      /* event record is valid */
#define EL_UNDEF	-1L     /* unused element of a data structure */
#define EL_CAM_WIDE	2L	/* alternate subid_unitnum layout for >7 */

/* event record prioroty (severity) levels (el_rhdr.rhdr_pri) */
#define EL_PRISEVERE	1
#define EL_PRIHIGH	3
#define EL_PRILOW	5


/* misc sizes */
#define EL_STKDUMP	512L
#define EL_SIZE512	512L
#define EL_SIZE256	256L
#define EL_SIZE128	128L
#define EL_SIZE64	64L
#define EL_SIZE16	16L
#define EL_SIZE12	12L
#define EL_SIZE2048	2048L
#define EL_SIZE4096	4096L
#define EL_SIZEAPPND	1400L

#define ELVER 6          /* event log record format internal version */

/* CEH: operating system ID's */
#define CEH_OS_DUNIX	1	/* obviously, the only one we write */
#define CEH_OS_OVMS	2
#define CEH_OS_WINNT	3
#define CEH_OS_VAXELN	4

#define CEH_OS_SUNSOL	5
#define CEH_OS_HPUX	6
#define CEH_OS_IBMAIX	7
#define CEH_OS_NOVELL	8
#define CEH_OS_SGIIRIX	9
/* CEH: hardware architecture constants */
#define CEH_HW_PDP11	1
#define CEH_HW_VAX	2
#define CEH_HW_MIPS	3
#define CEH_HW_ALPHA	4
#define CEH_HW_INTELX86	5
#define CEH_HW_INTELVLIW	6
    
/* CEH: vendor id */
#define CEH_VENDOR_DEC	0x0DEC

/*
 * Keep this data structure sized for machine architecture boundaries.
 * This makes the start of the data area (which is right after this data 
 * structure and is pointed to by binlog_bufhdr.in) aligned appropriately.
 */
struct binlog_bufhdr {              /* Kernel binary event log buffer header */
          unsigned long  size;      /* size of buffer - for savecore */
	  unsigned long  magic;     /* validity flag */
	  unsigned long  pending;   /* event records in process count */
	  char           *in;       /* pointer to start of current input spot */
          char           *out;      /* pointer to start of output data */
	  char           *le;       /* pointer to logical end of buffer */
};

#define BUFHDRSIZE     sizeof(struct binlog_bufhdr)  /* size of buffer header */


/* BINLOG_GETSTATUS ioctl state/status info for binary event logger */
struct binlog_getstatus {  
       unsigned int   sc_state;        /* state flags */
       unsigned int   sc_size;         /* size of event log buffer */
       unsigned int   sc_nobufavail;   /* no buffer available counter */
       unsigned int   sc_badsize;      /* bad record size counter */
       unsigned int   sc_readbusy;     /* log busy on read counter */
};



/* CEH: string ID's for TLV structs */
#define CEH_TLV_UNKNOWN 0	/* Unknown */
#define CEH_TLV_UNUSED	1	/* Present, but undefined */
#define CEH_TLV_TIME	2	/* Time */
#define CEH_TLV_DSR	3	/* Dynamic System Recognition */
#define CEH_TLV_OSVER	4	/* Operating System Version */
#define CEH_TLV_OSBUILD	5	/* Operating System Build number */
#define CEH_TLV_SSN	6	/* System Serial Number */
#define CEH_TLV_DDR	7	/* Dynamic Device Recognition */
#define CEH_TLV_PATCHL	8	/* Patch Level */
#define CEH_TLV_HNAME	9	/* Host name of the system */
#define CEH_TLV_ROLE	10	/* Role (future) */
    
/* CEH: TLV struct data types */
#define CEH_DT_UNDEF	0	/* Undefined */
#define CEH_DT_STRING	1	/* ISO Latin String */
#define CEH_DT_QUOTED	2	/* Quoted string (??) */
#define CEH_DT_BINARY	3	/* Binary value */
#define CEH_DT_UNICODE	4	/* 16-bit UNICODE */

/*
 * TLV string definitions (Tag, Length, Value)
 * 
 * A TLV is a variable-length structure aligned on a 32-bit word
 * boundary.  Each TLV structure contains four values:
 * 	- type	   <TL 4:0>
 * 	- name     <TL 15:5>
 * 	- length   <TL 31:16>
 * 	- value (padded with NULLs to next 32-bit value)
 * 
 * 	|3                             1|1		      | 	|
 * 	|1                             6|5                   5|4       0|
 * 	+---------------+---------------+---------------+-----+---------+
 *	|	   TL.length		|        TL.name      | TL.type |
 * 	+---------------+---------------+---------------+-----+---------+
 *	|			      VALUE				|
 * 	+---------------+---------------+---------------+---------------+
 *
 * Note: the C compiler wants bitfield definitions within type int or
 * (preferably) an unsigned type.  This is why we have to define three
 * bitfields instead of just two.
 */
typedef struct tl {
    unsigned type:5;	/* type occupies bits <4:0>  */
    unsigned name:11;	/* name occupies bits <15:5> */
    unsigned length:16; /* length of data occupies bits <31:16> */
} TL;

typedef struct tlv {
    TL tl;		/* Tag and Length */
    char string[1];	/* Address of first byte of TLV Value */
} TLV;

#define TLV_MAX_STRLEN		80
#define TLV_OVERHEAD_SIZE	(sizeof(struct tl))
    
/*
 * tlv_time and tlv_hostname are mandatory Tag-Length-Value (TLV)
 * structures that are included in every Common Errlog Header (CEH). Unlike
 * generic TLV structures, tlv_time and tlv_hostname are static structures
 * included as a mandatory part of the CEH. As stated above, TLV structures
 * are usually aligned on 32-bit words, but the tlv_hostname struct is a
 * special case.  Since tlv_hostname may be the last structure of the CEH,
 * it purposely aligns on a 64-bit longword. (The body of a binary errlog
 * record always aligns on a 64-bit longword.)
 */
typedef struct tlv_time {
    TL tl;
    char string[24];	/* 22 char's + \0, padded to next 32-bit word */
} TLV_TIME;

typedef struct tlv_hostname {
    TL tl;
    char string[20];	/* 12 char's + \0, padded to next 64-bit longword */
} TLV_HNAME;

/*
 * COMMON ERROR LOG HEADER DECLARATION
 * 
 * The following common header format is common across the three major
 * Digital operating systems: Digital UNIX, OpenVMS and Windows NT.  It is
 * important that the following header definition stays common across all
 * three operating systems.  Changes must be reviewed and approved by
 * Digital UNIX, OpenVMS and WinNT.
 */
struct ceh_rhdr {		/* errlog primary header */
    int ceh_leader;   		/* "-2" identifies common header */
    unsigned ceh_hdrlen;	/* length of common header (variable) */
    unsigned ceh_reclen;	/* errlog record length, including header */
    unsigned short ceh_majorv;	/* errlog version,filled in by elcs */
    unsigned short ceh_minorv;	/* errlog minor header revision */
    unsigned short ceh_ostype;	/* operating system ID */
    unsigned short ceh_hwarch;	/* hardware architecture */
    unsigned ceh_vendor;	/* vendor ID */
    unsigned long ceh_systype;	/* system type */
    unsigned ceh_mperr;       	/* which cpu serviced the error */
    unsigned ceh_mpnum;       	/* number of processors in system */
    unsigned short ceh_s_class;	/* class type, ELCT_DISK */
    unsigned short ceh_s_type;	/* error type, ELDEV_MSCP */
    unsigned ceh_dsrnum;	/* dsr message number */
    unsigned short ceh_s_ctldevtyp;/* controller/device type, ELDT_RA60 */
    unsigned char ceh_pri;	/* priority hi - low */
    unsigned char ceh_didfmt;	/* device_id format */
    unsigned ceh_s_errcode;	/* ci,mck summ.,cte,emm,exptflt */
    unsigned ceh_s_num;		/* cpu number - mchk errors */
				/* bus number - bus/adptr/cntr errors*/
				/* cntl number - device errors */
    unsigned ceh_chiptype;	/* cpu chip type */
    unsigned ceh_bus;		/* CEH spec DeviceId[0] */
    unsigned ceh_target;	/* CEH spec DeviceId[1] */
    unsigned ceh_lun;		/* CEH spec DeviceId[2] */
    struct {
	unsigned short seqnum;	/* sequence number */
	unsigned short seqpfx;  /* sequence prefix */
    } ceh_uuid;			/* "universally unique" identifier */
    long ceh_reserved[5];	/* reserved: 5 longwords */
    unsigned ceh_numstr;	/* number header strings present >= 2 */
    TLV_TIME ceh_time_s;	/* ISO date/time */
    TLV_HNAME ceh_hname_s;	/* host name, filled in by daemon */
};
    /*
     * Depending on the type of errlog event, additional, variable-length
     * TLV strings may follow...
     * 
     *    TLV	ceh_dsr_s;	    dynamic system recognition
     *    TLV	ceh_osver_s;	    operating system version
     *    TLV	ceh_osbuild_s;	    operating system build number
     *    TLV	ceh_serial_num_s;   system serial number
     *    TLV	ceh_ddr_s;	    (future) dynamic device recognition
     *    TLV	ceh_patchlev_s;	    (future) patch level
     *    TLV	ceh_role_s;	    (future) role to whom event is visible
     */

/*
 * ALIGNMENT MACROS
 * 
 *     These macros are used to pad TLV and header structures used within
 *     the specification of the Common Errlog Header.
 * 
 * ALIGNVAL rounds _val up to the next _aln size (a power of 2)
 */
#define ALIGNVAL(_val, _aln) ( ((long)_val+(_aln-1)) & ~(_aln-1) )
/*
 * ROUND32 rounds a value (_val) up to the next 32-bit word
 * ROUND64 rounds a value (_val) up to the next 64-bit longword
 */
#define ROUND32(_val) ALIGNVAL( _val, sizeof(int) )
#define ROUND64(_val) ALIGNVAL( _val, sizeof(long) )
    

/* programming interface for filling struct el_sub_id */
#define LSUBID(eptr, class, type, ctldev, num, unitnum, errcode) \
	eptr->elsubid.subid_class  = class; \
	eptr->elsubid.subid_type = type; \
	eptr->elsubid.subid_ctldevtyp = ctldev; \
	eptr->elsubid.subid_num = num; \
	eptr->elsubid.subid_unitnum = unitnum; \
	eptr->elsubid.subid_errcode = errcode;

/*
 * original errlog header and sub-header definitions
 */
struct el_rhdr {			/* errlog primary header */
	unsigned short rhdr_reclen;	/* errlog record length */
	unsigned short rhdr_seqnum; 	/* seq. number */
	unsigned int rhdr_sid;		/* cpu subtype & type */
	unsigned char rhdr_valid;	/* valid error record */
	unsigned char rhdr_pri;		/* priority hi - low */
	unsigned short rhdr_elver;	/* errlog version,filled in by elcs */
	int rhdr_time;		        /* time in sec event logged */
	char rhdr_hname[EL_SIZE12];	/* host name, filled in by daemon */
	unsigned int rhdr_systype;	/* system type register */
	unsigned int rhdr_mpnum;       	/* number of processors in system */
	unsigned int rhdr_mperr;       	/* which cpu serviced the error */
};

struct el_sub_id {			/* errlog secondary header */
	unsigned short subid_class;	/* class type, ELCT_DISK */
	unsigned char subid_type;	/* error type, ELDEV_MSCP */
	unsigned char subid_ctldevtyp;	/* controller/device type, ELDT_RA60 */
	unsigned short subid_num;	/* cpu number - mchk errors */
					/* bus number - bus/adptr/cntr errors*/
					/* cntl number - device errors */
	unsigned short subid_unitnum;	/* adpt number - adapter errors */
					/* cntl number - controller errors */
					/* unit number - device errors */
	unsigned int subid_errcode;	/* ci,mck summ.,cte,emm,exptflt */
	unsigned int subid_notused;     /* padding to 64bit alignment */
};



/******  COMMON (VENDOR INDEPENDENT) EVENT SPECIFIC DATA DEFINITIONS *********/
/* alpha note:
 * The code referencing msg_len uses ints.  We make it a long here to
 * guarantee 64 bit alignment of msg_asc;
 */

struct el_msg {				/* ascii text message */
	unsigned int msg_type;
	unsigned int msg_len;		/* actual length of string */
	char msg_asc[1024];		/* the ascii string */
};

#if defined(_KERNEL) && defined(_USE_KERNEL_PROTOS)

extern void binlog_logmsg(int class, char *ptr, int size);
extern char *binlog_alloc(int asize, int pri);
extern char *binlog_alloc_evm(int asize, int pri,...);
extern int binlog_allocate(caddr_t start);
extern int binlog_init(void);
extern void binlog_hdrinit(char *loc, int length, int priority);
extern void binlog_valid(char *buf);

#endif /* defined(_KERNEL) && defined(_USE_KERNEL_PROTOS) */

#ifdef __cplusplus
}
#endif
#endif /* __BINLOG__ */
