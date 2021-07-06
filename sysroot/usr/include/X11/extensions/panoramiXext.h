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
 * @(#)$RCSfile: panoramiXext.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1997/08/17 00:57:58 $
 */
/*  
 *	PanoramiX definitions
 */

#define PANORAMIX_MAJOR_VERSION         1       /* current version number */
#define PANORAMIX_MINOR_VERSION         0

typedef struct {
    Window  window;         /* PanoramiX window - may not exist */
    int	    screen;
    int     State;          /* PanroamiXOff, PanoramiXOn */
    int	    width;	    /* width of this screen */
    int     height;	    /* height of this screen */
    int     ScreenCount;    /* real physical number of screens */
    XID     eventMask;      /* selected events for this client */
} XPanoramiXInfo;    

extern XPanoramiXInfo *XPanoramiXAllocInfo (
#if NeedFunctionPrototypes
    void
#endif
);        
