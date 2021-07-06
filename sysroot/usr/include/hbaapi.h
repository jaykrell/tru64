/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: hbaapi.h,v $
 * Revision 1.1.2.2  2008/02/14  00:36:26  John_Franzini
 * 	Add port types HBA_PORTTYPE_EPORT and HBA_PORTTYPE_GPORT
 * 	for use by the Storage Essentials agent.
 *
 * Revision 1.1.2.1  2005/12/01  18:33:35  Heather_Lanigan
 * 	Initial Revision
 *
 * $EndLog$
 */
/*
 * @(#)$RCSfile: hbaapi.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 2008/02/14 00:36:26 $
 */

#ifndef _HBAAPI_H_
#define _HBAAPI_H_

#include <io/common/iotypes.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Basic Types
 ****************************************************************************/
typedef	U8  HBA_UINT8;
typedef	U16 HBA_UINT16;
typedef U32 HBA_UINT32;
typedef	I32 HBA_INT32;
typedef	I64 HBA_INT64;
typedef	U64 HBA_UINT64;
typedef HBA_UINT8  HBA_BOOLEAN;
typedef HBA_UINT32 HBA_HANDLE;

#define HBA_TRUE (HBA_BOOLEAN)1
#define HBA_FALSE (HBA_BOOLEAN)0

typedef struct HBA_wwn {
    HBA_UINT8 wwn[8];
} HBA_WWN, *PHBA_WWN;

/*****************************************************************************
 * Status Return Values
 ****************************************************************************/

typedef HBA_UINT32 HBA_STATUS;

/* No Error */
#define		HBA_STATUS_OK				     0 

/* Error */
#define		HBA_STATUS_ERROR			     1 

/* Function not supported.*/
#define		HBA_STATUS_ERROR_NOT_SUPPORTED		     2 

/* Invalid handle */
#define 	HBA_STATUS_ERROR_INVALID_HANDLE		     3 

/* Bad argument */
#define 	HBA_STATUS_ERROR_ARG			     4 

/* WWN not recognized */
#define 	HBA_STATUS_ERROR_ILLEGAL_WWN		     5 

/* Index not recognized */
#define 	HBA_STATUS_ERROR_ILLEGAL_INDEX		     6 

/* Larger buffer required */
#define 	HBA_STATUS_ERROR_MORE_DATA		     7 

/* Data has changed since the last call to HBA_RefreshInformation */
#define 	HBA_STATUS_ERROR_STALE_DATA		     8 

/* SCSI Check Condition reported */
#define		HBA_STATUS_SCSI_CHECK_CONDITION		     9 

/* Adapter busy or reserved, retry may be effective */
#define        HBA_STATUS_ERROR_BUSY                        10

/* Request timed out, retry may be effective */
#define        HBA_STATUS_ERROR_TRY_AGAIN                   11

/* Referenced HBA has been removed or deactivated */
#define        HBA_STATUS_ERROR_UNAVAILABLE                 12

/* The requested ELS was rejected by the local adapter */
#define        HBA_STATUS_ERROR_ELS_REJECT                  13

/* The specified LUN is not provided by the specified adapter */
#define        HBA_STATUS_ERROR_INVALID_LUN                 14

/* An incompatibility has been detected*/
/* among the library and driver modules invoked */
/* which will cause one or more functions */
/* in the highest version that all support */
/* to operate incorrectly. */
/* The differing function sets of software modules */
/* implementing different versions of the HBA API specification */
/* does not in itself constitute an incompatibility.*/
/* Known interoperability bugs among supposedly compatible versions */
/* should be reported as incompatibilities, */
/* but not all such interoperability bugs may be known. */
/* This value may be returned by any function */
/* that calls a Vendor Specific Library and returns an HBA_STATUS, */
/* and by HBA_LoadLibrary and HBA_GetAdapterName. */
#define        HBA_STATUS_ERROR_INCOMPATIBLE                15

/* Multiple adapters have a matching WWN. */
/* This could occur if the NodeWWN of multiple adapters is identical. */
#define        HBA_STATUS_ERROR_AMBIGUOUS_WWN               16

/* A persistent binding request included a bad local SCSI bus number */
#define        HBA_STATUS_ERROR_LOCAL_BUS                   17

/* A persistent binding request included a bad local SCSI target number */
#define        HBA_STATUS_ERROR_LOCAL_TARGET                18

/* A persistent binding request included a bad local SCSI logical unit number */
#define        HBA_STATUS_ERROR_LOCAL_LUN                   19

/* A persistent binding set request included */
/* a local SCSI ID that was already bound */
#define        HBA_STATUS_ERROR_LOCAL_SCSIID_BOUND          20

/* A persistent binding request included a bad or unlocatable FCP Target FCID */
#define        HBA_STATUS_ERROR_TARGET_FCID                 21

/* A persistent binding request included a bad FCP Target Node WWN */
#define        HBA_STATUS_ERROR_TARGET_NODE_WWN             22

/* A persistent binding request included a bad FCP Target Port WWN */
#define        HBA_STATUS_ERROR_TARGET_PORT_WWN             23

/* A persistent binding request included */
/* an FCP Logical Unit Number not defined by the identified Target*/
#define 	HBA_STATUS_ERROR_TARGET_LUN 		    24

/* A persistent binding request included */
/* an undefined or otherwise inaccessible Logical Unit Unique Identifier */
#define        HBA_STATUS_ERROR_TARGET_LUID                 25

/* A persistent binding remove request included */
/* a binding which did not match a binding established by the specified port */
#define        HBA_STATUS_ERROR_NO_SUCH_BINDING             26

/* A SCSI command was requested to an Nx_Port that was not a SCSI Target Port */
#define        HBA_STATUS_ERROR_NOT_A_TARGET                27

/* A request was made concerning an unsupported FC protocol */
#define        HBA_STATUS_ERROR_UNSUPPORTED_FC4             28

/* A request was made to enable unimplemented capabilities for a port */
#define	       HBA_STATUS_ERROR_INCAPABLE 		    29

/* A SCSI function was rejected to prevent causing a SCSI command */
/* condition (see SAM) */
#define        HBA_STATUS_ERROR_TARGET_BUSY		    30

/* A call was made to HBA_FreeLibrary when no library was loaded */
#define        HBA_STATUS_ERROR_NOT_LOADED                  31

/* A call was made to HBA_LoadLibrary when a library was already loaded */
#define        HBA_STATUS_ERROR_ALREADY_LOADED              32

/* The Address Identifier specified in a call to HBA_SendRNIDV2 */
/* violates access control rules for that call */
#define        HBA_STATUS_ERROR_ILLEGAL_FCID                33


/*****************************************************************************
 * Library Attributes Structure
 ****************************************************************************/
typedef struct HBA_LibraryAttributes {
    HBA_BOOLEAN	final;		/* Is the final draft of the HBA-API lib 
				   spec indicated by the value of 
				   HBA_GetVersion implemented */
    char	LibPath[256];	/* Library Path including Library Name */
    char	VName[256];	/* Vendor Name */
    char	VVersion[256];	/* Vendor Version */
    struct tm	build_date;	/* Build date of library */
} HBA_LIBRARYATTRIBUTES, *PHBA_LIBRARYATTRIBUTES;


/*****************************************************************************
 * Adapter Attributes
 ****************************************************************************/
typedef struct HBA_AdapterAttributes {
    char	Manufacturer[64];	/* Adapter's manufacturer */
    char	SerialNumber[64];	/* Adapter's serial number */
    char	Model[256];		/* Model number */
    char	ModelDescription[256];	/* Verbal description of Model */
    HBA_WWN	NodeWWN;		/* Node World Wide Name */
    char	NodeSymbolicName[256];	/* From FC-GS */
    char	HardwareVersion[256];	/* Vendor use */
    char	DriverVersion[256];
    char	OptionROMVersion[256];	/* Vendor use i.e. hardware boot ROM */
    char	FirmwareVersion[256];	/* Vendor use */
    HBA_UINT32	VendorSpecificID;	/* Vendor Specific */
    HBA_UINT32	NumberOfPorts;		/* Number of Ports on this Adapter */
    char	DriverName[256];	/* Binary path and/or name of driver 
					   file */
} HBA_ADAPTERATTRIBUTES, *PHBA_ADAPTERATTRIBUTES;

/*****************************************************************************
 * Local and Discovered Port Attributes
 ****************************************************************************/

/* Port Type */
typedef HBA_UINT32 HBA_PORTTYPE;

#define HBA_PORTTYPE_UNKNOWN		1        /* Unknown */
#define HBA_PORTTYPE_OTHER		2        /* Other */
#define HBA_PORTTYPE_NOTPRESENT		3        /* Not present */
#define HBA_PORTTYPE_NPORT		5        /* Fabric */
#define HBA_PORTTYPE_NLPORT		6        /* Public Loop */
#define HBA_PORTTYPE_FLPORT		7        /* Fabric on a Loop */
#define HBA_PORTTYPE_FPORT		8        /* Fabric Port */
#define HBA_PORTTYPE_EPORT		9        /* Expansion Port */
#define HBA_PORTTYPE_GPORT		10       /* Generic Port */
#define HBA_PORTTYPE_LPORT		20       /* Private Loop */
#define HBA_PORTTYPE_PTP		21       /* Point to Point */

/* Port State */
typedef HBA_UINT32 HBA_PORTSTATE;

#define HBA_PORTSTATE_UNKNOWN		1       /* Unknown */
#define HBA_PORTSTATE_ONLINE		2       /* Operational */
#define HBA_PORTSTATE_OFFLINE		3       /* User Offline */
#define HBA_PORTSTATE_BYPASSED		4       /* Bypassed */
#define HBA_PORTSTATE_DIAGNOSTICS	5       /* In diagnostics mode */
#define HBA_PORTSTATE_LINKDOWN		6       /* Link Down */
#define HBA_PORTSTATE_ERROR		7       /* Port Error */
#define HBA_PORTSTATE_LOOPBACK		8       /* Loopback */

/* Port Speed */
typedef HBA_UINT32 HBA_PORTSPEED;

#define HBA_PORTSPEED_UNKNOWN		0       /* Unknown - transceiver 
						   incapable of reporting */
#define HBA_PORTSPEED_1GBIT		1       /* 1 GBit/sec */
#define HBA_PORTSPEED_2GBIT		2       /* 2 GBit/sec */
#define HBA_PORTSPEED_10GBIT		4       /* 10 GBit/sec */
#define HBA_PORTSPEED_4GBIT		8       /* 4 GBit / sec */
#define HBA_PORTSPEED_NOT_NEGOTIATED	(1<<15) /* Speed not established */

/* Class of Service */
typedef HBA_UINT32 HBA_COS;          /* See "Class of Service - Format" 
					in FC-GS */


/* FC Types */
typedef struct HBA_fc4types {
           HBA_UINT8 bits[32];           /* See "FC TYPEs - Format"
					    in FC-GS */
} HBA_FC4TYPES, *PHBA_FC4TYPES;


typedef struct HBA_PortAttributes {
    HBA_WWN		NodeWWN;		/* Node World Wide Name */
    HBA_WWN		PortWWN;		/* Port World Wide Name */
    HBA_UINT32		PortFcId;		/* 3-byte ID of current
						   FC address of port */
    HBA_PORTTYPE	PortType;		/* PTP, Fabric, Etc. */
    HBA_PORTSTATE	PortState;
    HBA_COS		PortSupportedClassofService;
    HBA_FC4TYPES	PortSupportedFc4Types;
    HBA_FC4TYPES	PortActiveFc4Types;
    char		PortSymbolicName[256];
    char		OSDeviceName[256];	/* OS Special file */
    HBA_PORTSPEED	PortSupportedSpeed;	/* Signaling bit rates
						   this port may
						   operate at */
    HBA_PORTSPEED	PortSpeed;		/* Current port speed */
    HBA_UINT32		PortMaxFrameSize;	
    HBA_WWN		FabricName;		/* Fabric's WWN */
    HBA_UINT32		NumberofDiscoveredPorts; /* 0 if this is a 
						    discovered port*/
} HBA_PORTATTRIBUTES, *PHBA_PORTATTRIBUTES;

/*****************************************************************************
 * Nx_Port Statistics: Statistical counters for FC
 ****************************************************************************/
typedef struct HBA_PortStatistics {
    HBA_INT64	SecondsSinceLastReset;
    HBA_INT64	TxFrames;
    HBA_INT64	TxWords;
    HBA_INT64	RxFrames;
    HBA_INT64	RxWords;	
    HBA_INT64	LIPCount;
    HBA_INT64	NOSCount;
    HBA_INT64	ErrorFrames;
    HBA_INT64	DumpedFrames;	
    HBA_INT64	LinkFailureCount;
    HBA_INT64	LossOfSyncCount;	
    HBA_INT64	LossOfSignalCount;
    HBA_INT64	PrimitiveSeqProtocolErrCount;
    HBA_INT64	InvalidTxWordCount;	
    HBA_INT64	InvalidCRCCount;
} HBA_PORTSTATISTICS, *PHBA_PORTSTATISTICS;

/*****************************************************************************
 * Nx_Port Statistics: Statistical counters for FC protocols
 ****************************************************************************/
typedef struct HBA_FC4Statistics {
       HBA_INT64	InputRequests;
       HBA_INT64	OutputRequests;
       HBA_INT64	ControlRequests;
       HBA_INT64	InputMegabytes;
       HBA_INT64	OutputMegabytes;
} HBA_FC4STATISTICS, *PHBA_FC4STATISTICS;

/*****************************************************************************
 * FCP_Port Attributes (See FCP)
 ****************************************************************************/

/* HBA_FCPBINDINGTYPE was used in Rev 1.0. Add TO_OTHER for older calls to 
 * indicate other binding types for HBA_GetPersistentBinding. To support 
 * multiple types a new flag has been created to allow for multiple bindings 
 * supported */
typedef enum HBA_fcpbindingtype {TO_D_ID, TO_WWN,TO_OTHER} HBA_FCPBINDINGTYPE;

/* A bit mask of Rev 2.0 persistent binding capabilities */
typedef HBA_UINT32 HBA_BIND_CAPABILITY;

/* The following are bit flags indicating persistent binding capabilities */
#define HBA_CAN_BIND_TO_D_ID     0x0001
#define HBA_CAN_BIND_TO_WWPN     0x0002
#define HBA_CAN_BIND_TO_WWNN     0x0004
#define HBA_CAN_BIND_TO_LUID     0x0008
#define HBA_CAN_BIND_ANY_LUNS    0x0400
#define HBA_CAN_BIND_TARGETS     0x0800
#define HBA_CAN_BIND_AUTOMAP     0x1000
#define HBA_CAN_BIND_CONFIGURED  0x2000

/* A bit mask of Rev 2.0 persistent binding setting types */
typedef HBA_UINT32 HBA_BIND_TYPE;

/* The following are bit flags indicating persistent binding setting types */
#define HBA_BIND_TO_D_ID 0x0001
#define HBA_BIND_TO_WWPN 0x0002
#define HBA_BIND_TO_WWNN 0x0004
#define HBA_BIND_TO_LUID 0x0008
#define HBA_BIND_TARGETS 0x0800

typedef struct HBA_LUID {
       char	buffer[256]; /* Logical Unit Unique Device 
					       Identifier */
} HBA_LUID, *PHBA_LUID;

typedef struct HBA_ScsiId {
       char		    OSDeviceName[256]; /* \device\ScsiPort3 */
       HBA_UINT32	ScsiBusNumber;         /* Bus on the HBA */
       HBA_UINT32	ScsiTargetNumber;      /* SCSI Target ID to OS */
       HBA_UINT32	ScsiOSLun;
} HBA_SCSIID, *PHBA_SCSIID;

typedef struct HBA_FcpId {
       HBA_UINT32		FcId;
       HBA_WWN         	NodeWWN;
       HBA_WWN         	PortWWN;
       HBA_UINT64      	FcpLun;
} HBA_FCPID, *PHBA_FCPID;

typedef struct HBA_FcpScsiEntry {
       HBA_SCSIID      	ScsiId;
       HBA_FCPID       	FcpId;
} HBA_FCPSCSIENTRY, *PHBA_FCPSCSIENTRY;

typedef struct HBA_FcpScsiEntryV2 {
       HBA_SCSIID 		ScsiId;
       HBA_FCPID 		FcpId;
       HBA_LUID 		LUID;
} HBA_FCPSCSIENTRYV2, *PHBA_FCPSCSIENTRYV2;

typedef struct HBA_FCPTargetMapping {
       HBA_UINT32		 NumberOfEntries;
       HBA_FCPSCSIENTRY	 entry[1];              /* Variable length array 
							 containing mappings */
} HBA_FCPTARGETMAPPING, *PHBA_FCPTARGETMAPPING;

typedef struct HBA_FCPTargetMappingV2 {
       HBA_UINT32 		   NumberOfEntries;
       HBA_FCPSCSIENTRYV2  entry[1];            /* Variable length array 
							containing mappings */
} HBA_FCPTARGETMAPPINGV2, *PHBA_FCPTARGETMAPPINGV2;

typedef struct HBA_FCPBindingEntry {
       HBA_FCPBINDINGTYPE	type;
       HBA_SCSIID		ScsiId;
       HBA_FCPID		FcpId;
       HBA_UINT32		FcId;
} HBA_FCPBINDINGENTRY, *PHBA_FCPBINDINGENTRY;

typedef struct HBA_FCPBinding {
       HBA_UINT32		NumberOfEntries;
       HBA_FCPBINDINGENTRY	entry[1];       /* Variable length array */
} HBA_FCPBINDING, *PHBA_FCPBINDING;

typedef struct HBA_FCPBindingEntry2 {
       HBA_BIND_TYPE          	type;
       HBA_SCSIID              	ScsiId;
       HBA_FCPID               	FcpId;
       HBA_LUID                	LUID;
       HBA_STATUS              	Status;
} HBA_FCPBINDINGENTRY2, *PHBA_FCPBINDINGENTRY2;

typedef struct HBA_FcpBinding2 {
       HBA_UINT32               NumberOfEntries;
       HBA_FCPBINDINGENTRY2     entry[1]; 	/* Variable length array */
} HBA_FCPBINDING2, *PHBA_FCPBINDING2;

/*****************************************************************************
 * Fibre Channel Management Attributes
 ****************************************************************************/

typedef enum HBA_wwntype {NODE_WWN, PORT_WWN} HBA_WWNTYPE;

/* Although the HBA_MgmtInfo structure closely resembles */
/* the ACC to an RNID, it is different. */
/* It includes only 8 bytes for WWN */
typedef struct HBA_MgmtInfo {
       HBA_WWN            wwn;
       HBA_UINT32         unittype;
       HBA_UINT32         PortId;
       HBA_UINT32         NumberOfAttachedNodes;
       HBA_UINT16         IPVersion;
       HBA_UINT16         UDPPort;
       HBA_UINT8          IPAddress[16];
       HBA_UINT16         reserved;
       HBA_UINT16         TopologyDiscoveryFlags;
} HBA_MGMTINFO, *PHBA_MGMTINFO;


/*****************************************************************************
 * Polled Event Notification Data Structures and Defines
 ****************************************************************************/

#define        HBA_EVENT_LIP_OCCURRED                    1
#define        HBA_EVENT_LINK_UP                         2
#define        HBA_EVENT_LINK_DOWN                       3
#define        HBA_EVENT_LIP_RESET_OCCURRED              4
#define        HBA_EVENT_RSCN                            5
#define        HBA_EVENT_PROPRIETARY                     0xFFFF

typedef struct HBA_Link_EventInfo {
       HBA_UINT32     PortFcId;              /* Nx_Port which this event 
						occurred */
       HBA_UINT32     Reserved[3];
} HBA_LINK_EVENTINFO, *PHBA_LINK_EVENTINFO;

typedef struct HBA_RSCN_EventInfo {
       HBA_UINT32     PortFcId;              /* Nx_Port which this event 
						occurred */
       HBA_UINT32     NPortPage;             /* Reference FC-FS for RSCN ELS
                                                "Affected Port_ID Pages"*/
       HBA_UINT32     Reserved[2];
} HBA_RSCN_EVENTINFO, *PHBA_RSCN_EVENTINFO;

typedef struct HBA_Pty_EventInfo {
       HBA_UINT32     PtyData[4];            /* Proprietary data */
} HBA_PTY_EVENTINFO, *PHBA_PTY_EVENTINFO;

typedef struct HBA_EventInfo {
       HBA_UINT32     EventCode;
       union {
	       HBA_LINK_EVENTINFO            Link_EventInfo;
               HBA_RSCN_EVENTINFO            RSCN_EventInfo;
               HBA_PTY_EVENTINFO             Pty_EventInfo;
       } Event;
} HBA_EVENTINFO, *PHBA_EVENTINFO;

/*****************************************************************************
 * Asynchronous Event Notification Data Structures and Defines
 ****************************************************************************/

typedef void *HBA_CALLBACKHANDLE;

/* Adapter Level Events */
#define        HBA_EVENT_ADAPTER_UNKNOWN           0x100
#define        HBA_EVENT_ADAPTER_ADD               0x101
#define        HBA_EVENT_ADAPTER_REMOVE            0x102
#define        HBA_EVENT_ADAPTER_CHANGE            0x103

/* Port Level Events */
#define        HBA_EVENT_PORT_UNKNOWN              0x200
#define        HBA_EVENT_PORT_OFFLINE              0x201
#define        HBA_EVENT_PORT_ONLINE               0x202
#define        HBA_EVENT_PORT_NEW_TARGETS          0x203
#define        HBA_EVENT_PORT_FABRIC               0x204

/* Port Statistics Events */
#define        HBA_EVENT_PORT_STAT_THRESHOLD       0x301
#define        HBA_EVENT_PORT_STAT_GROWTH          0x302

/* Target Level Events */
#define        HBA_EVENT_TARGET_UNKNOWN            0x400
#define        HBA_EVENT_TARGET_OFFLINE            0x401
#define        HBA_EVENT_TARGET_ONLINE             0x402
#define        HBA_EVENT_TARGET_REMOVED            0x403

/* Fabric Link Events */
#define        HBA_EVENT_LINK_UNKNOWN              0x500
#define        HBA_EVENT_LINK_INCIDENT             0x501


/*****************************************************************************
 * HBA Library Function Prototypes
 ****************************************************************************/

/* The following function prototypes are defined in both HBA API Phase 1 
 * and HBA API Phase 2
 */

HBA_UINT32 
HBA_GetVersion( void );

HBA_STATUS
HBA_LoadLibrary( void );

HBA_STATUS
HBA_FreeLibrary( void );

HBA_UINT32 
HBA_GetNumberOfAdapters( void ); 

HBA_STATUS
HBA_GetAdapterName( 
    HBA_UINT32 adapterIndex, 
    char *pAdapterName );

HBA_HANDLE 
HBA_OpenAdapter( char *pAdapterName );

void 
HBA_CloseAdapter( HBA_HANDLE handle );

HBA_STATUS
HBA_GetAdapterAttributes( 
    HBA_HANDLE handle, 
    HBA_ADAPTERATTRIBUTES *pAdapterAttributes );

HBA_STATUS
HBA_GetAdapterPortAttributes( 
    HBA_HANDLE handle, 
    HBA_UINT32 portIndex, 
    HBA_PORTATTRIBUTES *pPortAttributes );

HBA_STATUS
HBA_GetPortStatistics( 
    HBA_HANDLE handle, 
    HBA_UINT32 portIndex, 
    HBA_PORTSTATISTICS *pPortStatistics );

HBA_STATUS
HBA_GetDiscoveredPortAttributes( 
    HBA_HANDLE handle, 
    HBA_UINT32 portIndex, 
    HBA_UINT32 discoveredPortIndex,
    HBA_PORTATTRIBUTES *pPortAttributes );

HBA_STATUS
HBA_GetPortAttributesByWWN( 
    HBA_HANDLE handle, 
    HBA_WWN portWWN, 
    HBA_PORTATTRIBUTES *pPortAttributes );

HBA_STATUS
HBA_SendCTPassThru( 
    HBA_HANDLE handle, 
    void *pReqBuffer, 
    HBA_UINT32 ReqBufferSize, 
    void *pRspBuffer,
   HBA_UINT32 RspBufferSize );

void 
HBA_RefreshInformation( HBA_HANDLE handle );

HBA_STATUS
HBA_GetFcpTargetMapping( 
    HBA_HANDLE handle,
    HBA_FCPTARGETMAPPING *pMapping );

HBA_STATUS
HBA_GetFcpPersistentBinding( 
    HBA_HANDLE handle, 
    HBA_FCPBINDING *pBinding );

HBA_STATUS
HBA_GetEventBuffer( 
    HBA_HANDLE handle, 
    HBA_EVENTINFO *pEventBuffer,
    HBA_UINT32 *pEventCount );

HBA_STATUS
HBA_SetRNIDMgmtInfo( 
    HBA_HANDLE handle, 
    HBA_MGMTINFO info );

HBA_STATUS
HBA_GetRNIDMgmtInfo( 
    HBA_HANDLE handle, 
    HBA_MGMTINFO *pInfo );

HBA_STATUS
HBA_SendRNID(
    HBA_HANDLE handle, 
    HBA_WWN wwn, 
    HBA_WWNTYPE wwntype,
    void *pRspBuffer, 
    HBA_UINT32 *pRspBufferSize );

HBA_STATUS
HBA_SendScsiInquiry(
    HBA_HANDLE handle, 
    HBA_WWN portWWN, 
    HBA_UINT64 fcLUN,
    HBA_UINT8 EVPD, 
    HBA_UINT32 PageCode, 
    void *pRspBuffer,
    HBA_UINT32 rspBufferSize, 
    void *pSenseBuffer,
    HBA_UINT32 senseBufferSize );

HBA_STATUS
HBA_SendReportLUNs( 
    HBA_HANDLE handle, 
    HBA_WWN portWWN, 
    void *pRspBuffer, 
    HBA_UINT32 rspBufferSize, 
    void *pSenseBuffer, 
    HBA_UINT32 senseBufferSize );

HBA_STATUS
HBA_SendReadCapacity( 
    HBA_HANDLE handle, 
    HBA_WWN portWWN, 
    HBA_UINT64 fcLUN, 
    void *pRspBuffer, 
    HBA_UINT32 rspBufferSize, 
    void *pSenseBuffer, 
    HBA_UINT32 senseBufferSize);
/*
 * The following function prototypes are defined only in HBA API Phase 2 
 */


HBA_STATUS
HBA_OpenAdapterByWWN(
    HBA_HANDLE *pHandle, 
    HBA_WWN wwn );

HBA_STATUS
HBA_GetFcpTargetMappingV2( 
    HBA_HANDLE handle, 
    HBA_WWN hbaPortWWN, 
    HBA_FCPTARGETMAPPINGV2 *pMapping );

HBA_STATUS
HBA_SendCTPassThruV2( 
    HBA_HANDLE handle, 
    HBA_WWN hbaPortWWN, 
    void *pReqBuffer, 
    HBA_UINT32 reqBufferSize, 
    void *pRspBuffer, 
    HBA_UINT32 *pRspBufferSize );

void	   
HBA_RefreshAdapterConfiguration( void );

HBA_STATUS
HBA_GetBindingCapability(
    HBA_HANDLE handle, 
    HBA_WWN hbaPortWWN, 
    HBA_BIND_CAPABILITY *pFlags );

HBA_STATUS
HBA_GetBindingSupport( 
    HBA_HANDLE handle, 
    HBA_WWN hbaPortWWN, 
    HBA_BIND_CAPABILITY *pFlags );

HBA_STATUS
HBA_SetBindingSupport( 
    HBA_HANDLE handle, 
    HBA_WWN hbaPortWWN, 
    HBA_BIND_CAPABILITY flags );

HBA_STATUS
HBA_SetPersistentBindingV2( 
    HBA_HANDLE handle, 
    HBA_WWN hbaPortWWN, 
    const HBA_FCPBINDING2 *binding ); 

HBA_STATUS
HBA_GetPersistentBindingV2( 
    HBA_HANDLE handle, 
    HBA_WWN hbaPortWWN, 
    HBA_FCPBINDING2 *binding ); 

HBA_STATUS
HBA_RemovePersistentBinding( 
    HBA_HANDLE handle, 
    HBA_WWN hbaPortWWN, 
    HBA_FCPBINDING2 *binding );

HBA_STATUS
HBA_RemoveAllPersistentBindings(
    HBA_HANDLE handle, 
    HBA_WWN hbaPortWWN );

HBA_STATUS
HBA_SendRNIDV2( 
    HBA_HANDLE handle, 
    HBA_WWN hbaPortWWN, 
    HBA_WWN destWWN, 
    HBA_UINT32 destFCID, 
    HBA_UINT32 nodeIdDataFormat, 
    void *pRspBuffer, 
    HBA_UINT32 *pRspBufferSize );

HBA_STATUS
HBA_ScsiInquiryV2( 
    HBA_HANDLE handle, 
    HBA_WWN hbaPortWWN, 
    HBA_WWN discoveredPortWWN, 
    HBA_UINT64 fcLUN, 
    HBA_UINT8 CDB_Byte1,
    HBA_UINT8 CDB_Byte2,
    void *pRspBuffer, 
    HBA_UINT32 *pRspBufferSize, 
    HBA_UINT8 *pScsiStatus, 
    void *pSenseBuffer, 
    HBA_UINT32 *pSenseBufferSize );

HBA_STATUS
HBA_ScsiReportLUNsV2( 
    HBA_HANDLE handle, 
    HBA_WWN hbaPortWWN, 
    HBA_WWN discoveredPortWWN, 
    void *pRspBuffer, 
    HBA_UINT32 *pRspBufferSize, 
    HBA_UINT8 *pScsiStatus, 
    void *pSenseBuffer, 
    HBA_UINT32 *pSenseBufferSize );
    

HBA_STATUS
HBA_ScsiReadCapacityV2( 
    HBA_HANDLE handle, 
    HBA_WWN hbaPortWWN, 
    HBA_WWN discoveredPortWWN, 
    HBA_UINT64 fcLUN, 
    void *pRspBuffer, 
    HBA_UINT32 *pRspBufferSize, 
    HBA_UINT8 *pScsiStatus, 
    void *pSenseBuffer, 
    HBA_UINT32 *pSenseBufferSize );

HBA_UINT32 
HBA_GetVendorLibraryAttributes( 
    HBA_UINT32 adapterIndex, 
    HBA_LIBRARYATTRIBUTES *attributes );


HBA_STATUS
HBA_RemoveCallback( HBA_CALLBACKHANDLE callbackHandle );

HBA_STATUS
HBA_RegisterForAdapterAddEvents(
    void (*pCallback)( void *pData, 
		       HBA_WWN PortWWN, 
		       HBA_UINT32 eventType ) ,
    void *pUserData, 
    HBA_CALLBACKHANDLE *pCallbackhandle );

HBA_STATUS
HBA_RegisterForAdapterEvents(
    void (*pCallback)( void *pData, 
		       HBA_WWN PortWWN, 
		       HBA_UINT32 eventType ),
    void *pUserData, 
    HBA_HANDLE handle, 
    HBA_CALLBACKHANDLE *pCallbackhandle );

HBA_STATUS
HBA_RegisterForAdapterPortEvents(
    void (*pCallback) ( void *pData, 
			HBA_WWN portWWN, 
			HBA_UINT32 eventType, 
			HBA_UINT32 fabricPortID ),
    void *pUserData, 
    HBA_HANDLE handle, 
    HBA_WWN PortWWN, 
    HBA_CALLBACKHANDLE *pCallbackhandle );

HBA_STATUS
HBA_RegisterForAdapterPortStatEvents(
    void (*pCallback)( void *pData, 
		       HBA_WWN portWWN, 
		       HBA_UINT32 eventType ),
    void *pUserData, 
    HBA_HANDLE handle, 
    HBA_WWN PortWWN, 
    HBA_PORTSTATISTICS stats, 
    HBA_UINT32 statType, 
    HBA_CALLBACKHANDLE *pCallbackhandle );

HBA_STATUS
HBA_RegisterForTargetEvents(
    void (*pCallback)( void *pData, 
		       HBA_WWN portWWN, 
		       HBA_WWN discoveredPortWWN, 
		       HBA_UINT32 eventType ),
    void *pUserData, 
    HBA_HANDLE handle, 
    HBA_WWN hbaPortWWN, 
    HBA_WWN discoveredPortWWN, 
    HBA_CALLBACKHANDLE *pCallbackhandle, 
    HBA_UINT32 allTargets );

HBA_STATUS
HBA_RegisterForLinkEvents(
    void (*pCallback)( void *pData, 
		       HBA_WWN adapterWWN, 
		       HBA_UINT32 eventType, 
		       void *pRLIRBuffer, 
		       HBA_UINT32 RLIRBufferSide ),
    void *pUserData, 
    void *pRLIRBuffer, 
    HBA_UINT32 RLIRBufferSize, 
    HBA_HANDLE handle, 
    HBA_CALLBACKHANDLE *pCallbackhandle );

HBA_STATUS
HBA_SendRPL( 
    HBA_HANDLE handle, 
    HBA_WWN hbaPortWWN, 
    HBA_WWN agent_wwn, 
    HBA_UINT32 agent_domain, 
    HBA_UINT32 portIndex, 
    void *pRspBuffer, 
    HBA_UINT32 *pRspBufferSize );

HBA_STATUS
HBA_SendRPS( 
    HBA_HANDLE handle, 
    HBA_WWN hbaPortWWN, 
    HBA_WWN agent_wwn, 
    HBA_UINT32 agent_domain, 
    HBA_WWN object_wwn, 
    HBA_UINT32 object_port_number, 
    void *pRspBuffer, 
    HBA_UINT32 *pRspBufferSize );

HBA_STATUS
HBA_SendSRL( 
    HBA_HANDLE handle, 
    HBA_WWN hbaPortWWN, 
    HBA_WWN wwn, 
    HBA_UINT32 domain, 
    void *pRspBuffer, 
    HBA_UINT32 *pRspBufferSize );

HBA_STATUS
HBA_SendLIRR( 
    HBA_HANDLE handle, 
    HBA_WWN hbaPortWWN, 
    HBA_WWN destWWN,
    HBA_UINT8 function, 
    HBA_UINT8 type, 
    void *pRspBuffer, 
    HBA_UINT32 *pRspBufferSize );

HBA_STATUS
HBA_GetFC4Statistics( 
    HBA_HANDLE handle, 
    HBA_WWN portWWN, 
    HBA_UINT8 FC4type, 
    HBA_FC4STATISTICS *statistics );

HBA_STATUS
HBA_GetFCPStatistics( 
    HBA_HANDLE handle, 
    const HBA_SCSIID *lunit, 
    HBA_FC4STATISTICS *statistics );

HBA_STATUS 
HBA_SendRLS(
    HBA_HANDLE handle, 
    HBA_WWN hbaPortWWN, 
    HBA_WWN destWWN, 
    void *pRspBuffer, 
    HBA_UINT32 *pRspBufferSize);

/*****************************************************************************
 * HBA Library Function Table
 ****************************************************************************/

/* The following function prototypes are defined in both HBA API Phase 1
 * and HBA API Phase 2
 */
typedef HBA_UINT32 (* HBAGetVersionFunc)(void);
typedef HBA_STATUS (* HBALoadLibraryFunc)(void);
typedef HBA_STATUS (* HBAFreeLibraryFunc)(void);
typedef HBA_UINT32 (* HBAGetNumberOfAdaptersFunc)(void);
typedef HBA_STATUS (* HBAGetAdapterNameFunc)(HBA_UINT32, char *);
typedef HBA_HANDLE (* HBAOpenAdapterFunc)(char *);
typedef void       (* HBACloseAdapterFunc)(HBA_HANDLE);
typedef HBA_STATUS (* HBAGetAdapterAttributesFunc)
                        (HBA_HANDLE, HBA_ADAPTERATTRIBUTES *);
typedef HBA_STATUS (* HBAGetAdapterPortAttributesFunc)
                        (HBA_HANDLE, HBA_UINT32, HBA_PORTATTRIBUTES *);
typedef HBA_STATUS (* HBAGetPortStatisticsFunc)
                        (HBA_HANDLE, HBA_UINT32, HBA_PORTSTATISTICS *);
typedef HBA_STATUS (* HBAGetDiscoveredPortAttributesFunc)
                        (HBA_HANDLE, HBA_UINT32,
                         HBA_UINT32, HBA_PORTATTRIBUTES *);
typedef HBA_STATUS (* HBAGetPortAttributesByWWNFunc)
                        (HBA_HANDLE, HBA_WWN, HBA_PORTATTRIBUTES *);
typedef HBA_STATUS (* HBASendCTPassThruFunc)
                        (HBA_HANDLE, void *, HBA_UINT32, void *, HBA_UINT32);
typedef void       (* HBARefreshInformationFunc)(HBA_HANDLE);
typedef void       (* HBAResetStatisticsFunc)(HBA_HANDLE, HBA_UINT32);
typedef HBA_STATUS (* HBAGetFcpTargetMappingFunc)
                        (HBA_HANDLE, HBA_FCPTARGETMAPPING *);
typedef HBA_STATUS (* HBAGetFcpPersistentBindingFunc)
                        (HBA_HANDLE, HBA_FCPBINDING *);
typedef HBA_STATUS (* HBAGetEventBufferFunc)
                        (HBA_HANDLE, HBA_EVENTINFO *, HBA_UINT32 *);
typedef HBA_STATUS (* HBASetRNIDMgmtInfoFunc)
                        (HBA_HANDLE, HBA_MGMTINFO);
typedef HBA_STATUS (* HBAGetRNIDMgmtInfoFunc)
                        (HBA_HANDLE, HBA_MGMTINFO *);
typedef HBA_STATUS (* HBASendRNIDFunc)
                        (HBA_HANDLE, HBA_WWN, HBA_WWNTYPE, void *,HBA_UINT32 *);
typedef HBA_STATUS (* HBASendScsiInquiryFunc)
                        (HBA_HANDLE, HBA_WWN,HBA_UINT64, HBA_UINT8,
                         HBA_UINT32, void *, HBA_UINT32, void *, HBA_UINT32);
typedef HBA_STATUS (* HBASendReportLUNsFunc)
                        (HBA_HANDLE, HBA_WWN, void *, HBA_UINT32, void *,
                         HBA_UINT32);
typedef HBA_STATUS (* HBASendReadCapacityFunc)
                        (HBA_HANDLE, HBA_WWN, HBA_UINT64, void *, HBA_UINT32,
                         void *, HBA_UINT32);
/*
 * The following function prototypes are defined only in HBA API Phase 2
 */

typedef HBA_STATUS (* HBAOpenAdapterByWWNFunc)
                        (HBA_HANDLE *, HBA_WWN);
typedef HBA_STATUS (* HBAGetFcpTargetMappingV2Func)
                        (HBA_HANDLE, HBA_WWN, HBA_FCPTARGETMAPPINGV2 *);
typedef HBA_STATUS (* HBASendCTPassThruV2Func)
                        (HBA_HANDLE, HBA_WWN, void *, HBA_UINT32, void *,
                         HBA_UINT32 *);
typedef void       (* HBARefreshAdapterConfigurationFunc) (void);
typedef HBA_STATUS (* HBAGetBindingCapabilityFunc)
                        (HBA_HANDLE, HBA_WWN, HBA_BIND_CAPABILITY *);
typedef HBA_STATUS (* HBAGetBindingSupportFunc)
                        (HBA_HANDLE, HBA_WWN, HBA_BIND_CAPABILITY *);
typedef HBA_STATUS (* HBASetBindingSupportFunc)
                        (HBA_HANDLE, HBA_WWN, HBA_BIND_CAPABILITY);
typedef HBA_STATUS (* HBASetPersistentBindingV2Func)
                        (HBA_HANDLE, HBA_WWN, const HBA_FCPBINDING2 *);
typedef HBA_STATUS (* HBAGetPersistentBindingV2Func)
                        (HBA_HANDLE, HBA_WWN, HBA_FCPBINDING2 *);
typedef HBA_STATUS (* HBARemovePersistentBindingFunc)
                        (HBA_HANDLE, HBA_WWN, const HBA_FCPBINDING2 *);
typedef HBA_STATUS (* HBARemoveAllPersistentBindingsFunc)
                        (HBA_HANDLE, HBA_WWN);
typedef HBA_STATUS (* HBASendRNIDV2Func)
                        (HBA_HANDLE, HBA_WWN, HBA_WWN, HBA_UINT32,
                         HBA_UINT32, void *, HBA_UINT32*);
typedef HBA_STATUS (* HBAScsiInquiryV2Func)
                        (HBA_HANDLE,HBA_WWN,HBA_WWN, HBA_UINT64, HBA_UINT8,
                         HBA_UINT8, void *, HBA_UINT32 *, HBA_UINT8 *,
                         void *, HBA_UINT32 *);
typedef HBA_STATUS (* HBAScsiReportLUNsV2Func)
                        (HBA_HANDLE, HBA_WWN, HBA_WWN, void *, HBA_UINT32 *,
                         HBA_UINT8 *, void *, HBA_UINT32 *);
typedef HBA_STATUS (* HBAScsiReadCapacityV2Func)
                        (HBA_HANDLE, HBA_WWN, HBA_WWN, HBA_UINT64, void *,
                         HBA_UINT32 *, HBA_UINT8 *, void *, HBA_UINT32 *);
typedef HBA_UINT32 (* HBAGetVendorLibraryAttributesFunc)
                        (HBA_LIBRARYATTRIBUTES *);
typedef HBA_STATUS (* HBARemoveCallbackFunc) (HBA_CALLBACKHANDLE);
typedef HBA_STATUS (* HBARegisterForAdapterAddEventsFunc)
                        (void (*)(void *, HBA_WWN, HBA_UINT32),
                        void *,HBA_CALLBACKHANDLE *);
typedef HBA_STATUS (* HBARegisterForAdapterEventsFunc)
                        (void (*)(void *, HBA_WWN, HBA_UINT32),
                        void *,HBA_HANDLE, HBA_CALLBACKHANDLE *);
typedef HBA_STATUS (* HBARegisterForAdapterPortEventsFunc)
                        (void (*)(void *, HBA_WWN, HBA_UINT32, HBA_UINT32),
                        void *, HBA_HANDLE, HBA_WWN, HBA_CALLBACKHANDLE *);
typedef HBA_STATUS (* HBARegisterForAdapterPortStatEventsFunc)
                        (void (*)(void *, HBA_WWN, HBA_UINT32),
                        void *,HBA_HANDLE, HBA_WWN, HBA_PORTSTATISTICS,
                        HBA_UINT32, HBA_CALLBACKHANDLE *);
typedef HBA_STATUS (* HBARegisterForTargetEventsFunc)
                        (void (*)(void *, HBA_WWN, HBA_WWN, HBA_UINT32),
                        void *, HBA_HANDLE, HBA_WWN, HBA_WWN,
                        HBA_CALLBACKHANDLE *, HBA_UINT32 );
typedef HBA_STATUS (* HBARegisterForLinkEventsFunc)
                        (void (*)(void *, HBA_WWN, HBA_UINT32, void *,
                                  HBA_UINT32),
                        void *, void *, HBA_UINT32, HBA_HANDLE,
                        HBA_CALLBACKHANDLE *);
typedef HBA_STATUS (* HBASendRPLFunc)
                        (HBA_HANDLE, HBA_WWN, HBA_WWN, HBA_UINT32,
                        HBA_UINT32, void *, HBA_UINT32 *);
typedef HBA_STATUS (* HBASendRPSFunc)
                        (HBA_HANDLE, HBA_WWN, HBA_WWN, HBA_UINT32, HBA_WWN,
                        HBA_UINT32, void *, HBA_UINT32 *);
typedef HBA_STATUS (* HBASendSRLFunc)
                        (HBA_HANDLE, HBA_WWN, HBA_WWN, HBA_UINT32, void *,
                        HBA_UINT32 *);
typedef HBA_STATUS (* HBASendLIRRFunc)
                        (HBA_HANDLE, HBA_WWN, HBA_WWN, HBA_UINT8, HBA_UINT8,
                        void *, HBA_UINT32 *);
typedef HBA_STATUS (* HBAGetFC4StatisticsFunc)
                        (HBA_HANDLE, HBA_WWN, HBA_UINT8,
                        HBA_FC4STATISTICS *);
typedef HBA_STATUS (* HBAGetFCPStatisticsFunc)
                        (HBA_HANDLE, const HBA_SCSIID *,
                        HBA_FC4STATISTICS *);
typedef HBA_STATUS (* HBASendRLSFunc )
			(HBA_HANDLE, HBA_WWN, HBA_WWN, void *,
			 HBA_UINT32 *);


typedef struct HBA_EntryPoints {
    HBAGetVersionFunc                   GetVersionHandler;
    HBALoadLibraryFunc                  LoadLibraryHandler;
    HBAFreeLibraryFunc                  FreeLibraryHandler;
    HBAGetNumberOfAdaptersFunc          GetNumberOfAdaptersHandler;
    HBAGetAdapterNameFunc               GetAdapterNameHandler;
    HBAOpenAdapterFunc                  OpenAdapterHandler;
    HBACloseAdapterFunc                 CloseAdapterHandler;
    HBAGetAdapterAttributesFunc         GetAdapterAttributesHandler;
    HBAGetAdapterPortAttributesFunc     GetAdapterPortAttributesHandler;
    HBAGetPortStatisticsFunc            GetPortStatisticsHandler;
    HBAGetDiscoveredPortAttributesFunc  GetDiscoveredPortAttributesHandler;
    HBAGetPortAttributesByWWNFunc       GetPortAttributesByWWNHandler;
    HBASendCTPassThruFunc               SendCTPassThruHandler;
    HBARefreshInformationFunc           RefreshInformationHandler;
    HBAResetStatisticsFunc              ResetStatisticsHandler;
    HBAGetFcpTargetMappingFunc          GetFcpTargetMappingHandler;
    HBAGetFcpPersistentBindingFunc      GetFcpPersistentBindingHandler;
    HBAGetEventBufferFunc               GetEventBufferHandler;
    HBASetRNIDMgmtInfoFunc              SetRNIDMgmtInfoHandler;
    HBAGetRNIDMgmtInfoFunc              GetRNIDMgmtInfoHandler;
    HBASendRNIDFunc                     SendRNIDHandler;
    HBASendScsiInquiryFunc              ScsiInquiryHandler;
    HBASendReportLUNsFunc               ReportLUNsHandler;
    HBASendReadCapacityFunc             ReadCapacityHandler;
} HBA_ENTRYPOINTS, *PHBA_ENTRYPOINTS;

typedef struct HBA_EntryPointsV2 {
    HBAGetVersionFunc                   GetVersionHandler;
    HBALoadLibraryFunc                  LoadLibraryHandler;
    HBAFreeLibraryFunc                  FreeLibraryHandler;
    HBAGetNumberOfAdaptersFunc          GetNumberOfAdaptersHandler;
    HBAGetAdapterNameFunc               GetAdapterNameHandler;
    HBAOpenAdapterFunc                  OpenAdapterHandler;
    HBACloseAdapterFunc                 CloseAdapterHandler;
    HBAGetAdapterAttributesFunc         GetAdapterAttributesHandler;
    HBAGetAdapterPortAttributesFunc     GetAdapterPortAttributesHandler;
    HBAGetPortStatisticsFunc            GetPortStatisticsHandler;
    HBAGetDiscoveredPortAttributesFunc  GetDiscoveredPortAttributesHandler;
    HBAGetPortAttributesByWWNFunc       GetPortAttributesByWWNHandler;
    HBASendCTPassThruFunc               SendCTPassThruHandler;
    HBARefreshInformationFunc           RefreshInformationHandler;
    HBAResetStatisticsFunc              ResetStatisticsHandler;
    HBAGetFcpTargetMappingFunc          GetFcpTargetMappingHandler;
    HBAGetFcpPersistentBindingFunc      GetFcpPersistentBindingHandler;
    HBAGetEventBufferFunc               GetEventBufferHandler;
    HBASetRNIDMgmtInfoFunc              SetRNIDMgmtInfoHandler;
    HBAGetRNIDMgmtInfoFunc              GetRNIDMgmtInfoHandler;
    HBASendRNIDFunc                     SendRNIDHandler;
    HBASendScsiInquiryFunc              ScsiInquiryHandler;
    HBASendReportLUNsFunc               ReportLUNsHandler;
    HBASendReadCapacityFunc             ReadCapacityHandler;
    HBAOpenAdapterByWWNFunc             OpenAdapterByWWNHandler;
    HBAGetFcpTargetMappingV2Func        GetFcpTargetMappingV2Handler;
    HBASendCTPassThruV2Func             SendCTPassThruV2Handler;
    HBARefreshAdapterConfigurationFunc  RefreshAdapterConfigurationHandler;
    HBAGetBindingCapabilityFunc         GetBindingCapabilityHandler;
    HBAGetBindingSupportFunc            GetBindingSupportHandler;
    HBASetBindingSupportFunc            SetBindingSupportHandler;
    HBASetPersistentBindingV2Func       SetPersistentBindingV2Handler;
    HBAGetPersistentBindingV2Func       GetPersistentBindingV2Handler;
    HBARemovePersistentBindingFunc      RemovePersistentBindingHandler;
    HBARemoveAllPersistentBindingsFunc  RemoveAllPersistentBindingsHandler;
    HBASendRNIDV2Func                   SendRNIDV2Handler;
    HBAScsiInquiryV2Func                ScsiInquiryV2Handler;
    HBAScsiReportLUNsV2Func             ScsiReportLUNsV2Handler;
    HBAScsiReadCapacityV2Func           ScsiReadCapacityV2Handler;
    HBAGetVendorLibraryAttributesFunc   GetVendorLibraryAttributesHandler;
    HBARemoveCallbackFunc               RemoveCallbackHandler;
    HBARegisterForAdapterAddEventsFunc  RegisterForAdapterAddEventsHandler;
    HBARegisterForAdapterEventsFunc     RegisterForAdapterEventsHandler;
    HBARegisterForAdapterPortEventsFunc RegisterForAdapterPortEventsHandler;
    HBARegisterForAdapterPortStatEventsFunc
                                        RegisterForAdapterPortStatEventsHandler;
    HBARegisterForTargetEventsFunc      RegisterForTargetEventsHandler;
    HBARegisterForLinkEventsFunc        RegisterForLinkEventsHandler;
    HBASendRPLFunc                      SendRPLHandler;
    HBASendRPSFunc                      SendRPSHandler;
    HBASendSRLFunc                      SendSRLHandler;
    HBASendLIRRFunc                     SendLIRRHandler;
    HBAGetFC4StatisticsFunc             GetFC4StatisticsHandler;
    HBAGetFCPStatisticsFunc             GetFCPStatisticsHandler;
    HBASendRLSFunc			SendRLSHandler;
} HBA_ENTRYPOINTSV2, *PHBA_ENTRYPOINTSV2;

typedef HBA_STATUS (* HBARegisterLibraryFunc)( HBA_ENTRYPOINTS * );
typedef HBA_STATUS (* HBARegisterLibraryV2Func)( HBA_ENTRYPOINTSV2 * );

#ifdef __cplusplus
}
#endif

#endif /* _HBAAPI_H_ */
