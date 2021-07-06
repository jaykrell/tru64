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
 * @(#)$RCSfile: cam_debug.h,v $ $Revision: 1.1.25.2 $ (DEC) $Date: 2002/05/30 23:15:15 $
 */
#ifndef _CAM_DEBUG_H_
#define _CAM_DEBUG_H_
#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------------------------------------------- */

/* cam_debug.h		Version 1.13			Nov. 20, 1991 */

/*
 *	This file contains the CAM debugging macros.
 */

/* ---------------------------------------------------------------------- */

/* The ultimate debug definition.  This define will turn it all on. */

/* #define CAMDEBUG */

/* ---------------------------------------------------------------------- */

/* Currently the CAM module testing within the kernel uses the printf()
functions.  Debugging in the CAM modules has two levels, debugging 
within the modules independent of a particular SCSI ID and debugging within the
modules tracking a particular bus, or target or LUN.  The setting of "flags"
in a debug variable will turn on specific printf() calls within the kernel.  
This variable is called camdbg_flag.  A second debug variable is used, 
camdbg_id, to contain the bus, target, and LUN information for tracking.

The msb of camdbg_flag, has special meaning.  It is used to flag the fact
that the camdbg_id variable contains valid bus/target/LUN information for the
device that needs to be tracked.  Bit 31 is the TVALID, target ID valid bit.
The remaining bits 30 - 00, are used to define the DEBUG flag level. 

camdbg_flag
     31 30                                                          0
    +----------------------------------------------------------------+
    |TV|                       Debug Flags                           |
    +----------------------------------------------------------------+

The camdbg_id variable contains the bus, target, and LUN information, (B/T/L)
for a particular target to track with the debugging informatation.  The 
camdbg_id variable is broken in 3 parts each holding a part of the B/T/L
information.  At this time each of the parts are allocated 4 bits, mostly for
ease of mapping one ASCII character 0 - 7 to a valid binary number, 0x0 - 0x7.
The allocation of bits are: 31 - 16 Reserved, 15 - 8 Bus number, 7 - 4 Target
number, 3 - 0 LUN number.

camdbg_id
     31                             16 15           8 7     4 3     0
    +----------------------------------------------------------------+
    |        Reserved (MB0)           |    Bus #     |  TGT  |  LUN  |
    +----------------------------------------------------------------+

*/

/* ---------------------------------------------------------------------- */

/* The following defines are used for the flag bits in the printf macro. */

#define CAMD_TMPLT	0x00000000	/* template */
#define	CAMD_INOUT	0x00000001	/* routine entry and exit */
#define CAMD_FLOW	0x00000002	/* code flow through the modules */
#define CAMD_PHASE	0x00000004	/* SCSI phase values */
#define CAMD_SM		0x00000008	/* State machine settings */
#define CAMD_ERRORS	0x00000010	/* error handling */
#define CAMD_CMD_EXP	0x00000020	/* expansion of cmds and responses */
#define CAMD_IO_MAPPING	0x00000040	/* DME I/O mapping for user space */
#define CAMD_DMA_FLOW	0x00000080	/* DME DMA flow */
#define CAMD_DISCONNECT	0x00000100	/* signal disconnect handling */
#define CAMD_TAGS	0x00000200	/* tag queuing code */
#define CAMD_POOL	0x00000400	/* Stuff in the DEC CAM pkt pool */
#define CAMD_AUTOS	0x00000800	/* autosense handling */
#define CAMD_CCBALLOC	0x00001000	/* CCB allocation/free flow */
#define CAMD_MSGOUT	0x00002000	/* messages going out */
#define CAMD_MSGIN	0x00004000	/* messages coming in */
#define CAMD_STATUS	0x00008000	/* scsi status bytes */
#define CAMD_CONFIG	0x00010000	/* CAM configuration paths */
#define CAMD_TAPE	0x00020000	/* PDrv TAPE work */
#define CAMD_COMMON	0x00040000	/* PDrv Common work */
#define CAMD_DISK	0x00080000	/* PDrv DISK work */
#define CAMD_DISK_REC	0x00100000	/* PDrv DISK Recovery work */
#define CAMD_DBBR	0x00200000	/* PDrv DIsk DBBR work */
#define CAMD_CDROM	0x00400000	/* PDrv CDROM functions */
#define CAMD_INTERRUPT  0x00800000	/* SIM Trace Interrupts */
#define CAMD_SCHED	0x01000000	/* SIM Scheduler points */
#define CAMD_SIMQ	0x02000000	/* SIM Q manipulation */
#define CAMD_RESRC	0x04000000	/* General Resource manipulation */
#define CAMD_CHANGER	0x08000000	/* PDrv Medium Changer debug */
#define CAMD_SENSOR	0x10000000	/* PDrv Storage Sensor debug */

#define TVALID		0x80000000	/* B/T/L bits are valid in camdbg_id */

/* ---------------------------------------------------------------------- */
/* These defines are for accessing the B/T/L information in the camdbg_id
variable. */

#define BMASK	0x0000FF00		/* mask for the SCSI bus bits */
#define BSHIFT	8			/* shift for SCSI bus bits */
#define TMASK	0x00000070		/* mask for the target bits */
#define TSHIFT	4			/* shift for target bits */
#define LMASK	0x00000007		/* mask for the LUN bits */
#define LSHIFT	0			/* shift for LUN bits */

#define NOBTL	0xFF			/* the debug has no BTL knowledge */

/* ---------------------------------------------------------------------- */
/* These two externs are for the CAM debug variables. */

extern U32 camdbg_flag;
extern U32 camdbg_id;

/* ---------------------------------------------------------------------- */

/* This Macro is an attempt to be able to track target specific messages, and
allow for specific subsets of the DEBUG statements be printed. 
The format for the Macro is not immediatly obvious.  The B/T/L arguments are
for target specific tracking.  The F argument is for tracking particular
subsets of the statements.  This flag argument is compared with the 
camdbg_flag static variable to determine if the user wants to see the message.
The X argument is "ugly" it must be a complete printf argument set 
enclosed within "()", this will allow the pre-processor to include
it in the finial printf statement. */

/* NOTE: an attempt to describe what the following if statements are checking.

The first "if( camdbg_flag & (int)F )" is checking to see if any of the
flags for the Macro are turned on.  It is not checking for exact matching, ie
"== (int)F", this allows the same Macro to be used for different settings of
the flags in camdbg_flag, ie CAMD_SM | CAMD_PHASE.

The second "if( ((camdbg_flag & TVALID) == 0) ||
		(((camdbg_flag & TVALID) != 0) && 
                (((((camdbg_id & BMASK) >> BSHIFT) == B) || (B == NOBTL)) &&
                ((((camdbg_id & TMASK) >> TSHIFT) == T) || (T == NOBTL)) &&
                ((((camdbg_id & LMASK) >> LSHIFT) == L) || (L == NOBTL)))) "
is checking for any target information for tracing a target.  The if
statement is very large, to allow the use of only one printf() call. 

The first condition "((camdbg_flag & TVALID) == 0)", checks to see if the
target valid bit is not set, if not, the "||" condition is met and the printf()
call is made.  If the TVALID bit is set, "((camdbg_flag & TVALID) != 0)", then
the bus, target, and LUN fields in camdbg_id must be compared to the B, T, and
L arguments in the macro.  In a more english term : "If TVALID is true and
bus == B and target == T and LUN == L then also print.". 

The construct used to check the B/T/L fields, for example the bus field:
    "((((camdbg_id & BMASK) >> BSHIFT) == B) || (B == NOBTL))",
masks out the other fields, shifts the bus value down to allow comparision
with the B argument.  The Macro arguments can also have a "wildcard" value,
NOBTL.  Using the wildcard will always allow the B or T or L comparision to
be true. */

/* If not linked in a kernel, "xprintf" isn't available.  Use "printf"
in this situation. */

extern void (*cdbg_printf)(char *fmt, ...);
extern void (*cdbg_cprintf)(char *fmt, ...);
extern void (*cdbg_xprintf)(char *fmt, ...);

#define CAM_MODULE(name)	static char *module = "name";

/*
 * Conditionally Print Debug Information.
 */
#if defined(CAMDEBUG) && !defined(lint)
#   define PRINTD(B, T, L, F, X)                                            \
    {                                                                       \
	/* NOSTRICT */                                                      \
        if( camdbg_flag & (int)F )                                          \
        {                                                                   \
            if( ((camdbg_flag & TVALID) == 0) ||                            \
		(((camdbg_flag & TVALID) != 0) &&                           \
                ((((camdbg_id & BMASK) >> BSHIFT) == B) || (B == NOBTL)) && \
                ((((camdbg_id & TMASK) >> TSHIFT) == T) || (T == NOBTL)) && \
                ((((camdbg_id & LMASK) >> LSHIFT) == L) || (L == NOBTL))) ) \
            {                                                               \
	    /* VARARGS */                                                   \
            (void)(*cdbg_printf) X ;                                        \
            }                                                               \
        }                                                                   \
    }

/*
 * Conditionally Call a Debug Function.
 */
#   define CALLD(B, T, L, F, X)                                             \
    {                                                                       \
	/* NOSTRICT */                                                      \
        if( camdbg_flag & (int)F )                                          \
        {                                                                   \
            if( ((camdbg_flag & TVALID) == 0) ||                            \
		(((camdbg_flag & TVALID) != 0) &&                           \
                ((((camdbg_id & BMASK) >> BSHIFT) == B) || (B == NOBTL)) && \
                ((((camdbg_id & TMASK) >> TSHIFT) == T) || (T == NOBTL)) && \
                ((((camdbg_id & LMASK) >> LSHIFT) == L) || (L == NOBTL))) ) \
            {                                                               \
	    /* VARARGS */                                                   \
            (void) X ;                                                      \
            }                                                               \
        }                                                                   \
    }
#   define CAMD_MODULE(name)	static char *module = "name";

#else  /* CAMDEBUG and not lint */
#   define PRINTD(B, T, L, F, X) 
#   define CALLD(B, T, L, F, X) 
#   define CAMD_MODULE(name)
#endif /* CAMDEBUG and not lint */

/*
 * Declare CAM Debugging Definitions:
 */
#define CDBG_BRIEF	0		/* Brief message text. */
#define CDBG_FULL	1		/* Full message text. */

/*
 * Additional Sense Code Table Entry Format:
 */
struct sense_entry {
	u_char	sense_code;		/* Additional sense code.	*/
	u_char	sense_qualifier;	/* Sense code qualifier.	*/
	char	*sense_message;		/* Error message text.		*/
};

#if defined(_KERNEL)
#if defined(CAMDEBUG)

/* pick up the PDRV_WS definition */
#include <io/cam/pdrv.h> 
#include <io/cam/pdrv3.h> 

extern caddr_t 
	cdbg_SystemStatus(int errnum), 
	cdbg_GetDeviceName(int device_type),
	cdbg_SenseMessage(struct all_req_sns_data *sdp),
	cdbg_CamFunction(u_char cam_function, int report_format);
extern void 
	cdbg_DumpCCB(CCB_HEADER *ccbh),
	cdbg_DumpCCBHeader(CCB_HEADER *ccb), 
	cdbg_DumpCCBHeaderFlags(unsigned int cam_flags),
	cdbg_DumpSCSIIO(CCB_SCSIIO *ccb), 
	cdbg_DumpABORT(CCB_ABORT *ccb), 
	cdbg_DumpTERMIO(CCB_TERMIO *ccb),
	cdbg_DumpGETDEV(CCB_GETDEV *ccb), 
	cdbg_DumpPATHINQ(CCB_PATHINQ *ccb), 
	cdbg_DumpSETDEV(CCB_SETDEV *ccb),
	cdbg_DumpPDRVws(PDRV3_WS *pws), 
	cdbg_DumpBuffer(void *buffer, int size), 
	cdbg_DumpSenseData(struct all_req_sns_data *sdp),
	cdbg_DumpInquiryData(ALL_INQ_DATA *inquiry), 
	cdbg_DumpHBACapabilityFlags(u_char hba_flags),
	cdbg_DumpHBATargetSupportFlags(u_char target_support_flags), 
	cdbg_DumpHBAMiscFlags(u_char hba_misc_flags),
	cdbg_DumpHBAAsyncEventFlags(u_char async_flags);

#endif /* defined(CAMDEBUG) */

extern char *cdbg_SenseKeyTable[];
extern caddr_t cdbg_CamStatus(uchar_t cam_status, int report_format);
extern caddr_t cdbg_ScsiStatus(uchar_t scsi_status, int report_format);

#endif /* defined(_KERNEL */

#ifdef __cplusplus
}
#endif
#endif /* !_CAM_DEBUG_H_ */
