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
 * (c) Copyright 1989, 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
*/ 
/* 
 * Motif Release 1.2.3
*/ 
/*   $RCSfile: DragOverS.h,v $ $Revision: 1.1.10.2 $ $Date: 1994/09/09 21:09:05 $ */
/*
*  (c) Copyright 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */
#ifndef _XmDragOverS_h
#define _XmDragOverS_h
#if defined(VMS) || defined (__VMS)
#include <X11/apienvset.h>
#endif

#include <Xm/Xm.h>
#include <Xm/DragC.h>
#include <Xm/DragIcon.h>

#ifdef __cplusplus
extern "C" {
#endif


/***********************************************************************
 *
 * DragOverShell Widget
 *
 ***********************************************************************/

/* Class record constants */

typedef struct _XmDragOverShellRec 	*XmDragOverShellWidget;
typedef struct _XmDragOverShellClassRec 	*XmDragOverShellWidgetClass;

externalref WidgetClass	xmDragOverShellWidgetClass;

#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#if defined(VMS) || defined (__VMS)
#include <X11/apienvrst.h>
#endif
#endif /* _XmDragOverS_h */
/* DON'T ADD STUFF AFTER THIS #endif */
