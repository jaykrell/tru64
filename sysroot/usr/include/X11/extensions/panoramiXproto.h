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
 * @(#)$RCSfile: panoramiXproto.h,v $ $Revision: 1.1.2.3 $ (DEC) $Date: 1998/03/31 15:14:56 $
 */
#ifndef _PANORAMIXPROTO_H_
#define _PANORAMIXPROTO_H_

#define PANORAMIX_PROTOCOL_NAME "PanoramiX"
#define XINERAMA_PROTOCOL_NAME "XINERAMA"

#define X_PanoramiXQueryVersion		0
#define X_PanoramiXGetState		1
#define X_PanoramiXGetScreenCount	2
#define X_PanoramiXGetScreenSize	3

typedef struct _PanoramiXQueryVersion {
	CARD8	reqType;		/* always PanoramiXReqCode */
	CARD8	panoramiXReqType;	/* always X_PanoramiXQueryVersion */
	CARD16	length B16;
	CARD8	clientMajor;
	CARD8	clientMinor;
	CARD16	unused B16;           
} xPanoramiXQueryVersionReq;

#define sz_xPanoramiXQueryVersionReq	8

typedef struct {
	CARD8	type;			/* must be X_Reply */
	CARD8	pad1;			/* unused	*/
	CARD16	sequenceNumber  B16;	/* last sequence number */
	CARD32	length  B32;		/* 0 */
	CARD16	majorVersion  B16;	
	CARD16	minorVersion  B16;	
	CARD32	pad2	B32;		/* unused */
	CARD32	pad3	B32;		/* unused */
	CARD32	pad4	B32;		/* unused */
	CARD32	pad5	B32;		/* unused */
	CARD32	pad6	B32;		/* unused */
} xPanoramiXQueryVersionReply;

#define sz_xPanoramiXQueryVersionReply	32


typedef	struct	_PanoramiXGetState {
        CARD8   reqType;	        /* always PanoramiXReqCode */
        CARD8   panoramiXReqType;    	/* always X_PanoramiXGetState */
        CARD16  length B16;
	CARD32  window B32;
} xPanoramiXGetStateReq;
#define sz_xPanoramiXGetStateReq	8	

typedef struct {
	BYTE	type;
	BYTE	state;
	CARD16	sequenceNumber B16;
	CARD32	length	B32;
	CARD32  window  B32;
	CARD32	pad1	B32;		/* unused */
	CARD32	pad2	B32;		/* unused */
	CARD32	pad3	B32;		/* unused */
	CARD32	pad4	B32;		/* unused */
	CARD32	pad5	B32;		/* unused */
} xPanoramiXGetStateReply;

#define sz_panoramiXGetStateReply	32

typedef	struct	_PanoramiXGetScreenCount {
        CARD8   reqType;             /* always PanoramiXReqCode */
        CARD8   panoramiXReqType;    /* always X_PanoramiXGetScreenCount */
        CARD16  length B16;
	CARD32  window B32;
} xPanoramiXGetScreenCountReq;
#define sz_xPanoramiXGetScreenCountReq	8

typedef struct {
	BYTE	type;
	BYTE	ScreenCount;
	CARD16	sequenceNumber B16;
	CARD32	length B32;
	CARD32  window  B32;
	CARD32	pad1	B32;		/* unused */
	CARD32	pad2	B32;		/* unused */
	CARD32	pad3	B32;		/* unused */
	CARD32	pad4	B32;		/* unused */
	CARD32	pad5	B32;		/* unused */
} xPanoramiXGetScreenCountReply;
#define sz_panoramiXGetScreenCountReply	32

typedef	struct	_PanoramiXGetScreenSize {
        CARD8   reqType;                /* always PanoramiXReqCode */
        CARD8   panoramiXReqType;	/* always X_PanoramiXGetState */
        CARD16  length B16;
	CARD32  window B32;
	CARD32	screen B32;
} xPanoramiXGetScreenSizeReq;
#define sz_xPanoramiXGetScreenSizeReq	12	

typedef struct {
	BYTE	type;
	CARD8	pad1;			
	CARD16	sequenceNumber B16;
	CARD32	length	B32;
	CARD32	width	B32;
	CARD32	height	B32;
	CARD32  window  B32;
	CARD32  screen  B32;
	CARD32	pad2	B32;		/* unused */
	CARD32	pad3	B32;		/* unused */
} xPanoramiXGetScreenSizeReply;
#define sz_panoramiXGetScreenSizeReply 32	

/* define any errors specific to this extension */

/* If a client asks for ScreenCount when PanoramiX
   is not in use */


/* If a client asks for Screen Size of a screen when
   PanoramiX is not in use */

#endif 
