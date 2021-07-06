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
 * (c) Copyright 1989, 1990, 1991, 1992, 1993, 1994 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
*/ 
/* 
ifndef OSF_v1_2_4
 * Motif Release 1.2
else
 * Motif Release 1.2.4
endif
*/ 
/*   $RCSfile: CacheP.h,v $ $Revision: 1.1.12.2 $ $Date: 1994/09/09 21:03:11 $ */
/*
*  (c) Copyright 1989, DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS. */
/*
*  (c) Copyright 1987, 1988, 1989, 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */
#ifndef _XmCacheP_h
#define _XmCacheP_h
#if defined(VMS) || defined (__VMS)
#include <X11/apienvset.h>
#endif

#include <Xm/GadgetP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* a few convenience macros */

#define ClassCacheHead(cp) \
	((cp)->cache_head)

#define ClassCacheCopy(cp) \
	((cp)->cache_copy)

#define ClassCacheCompare(cp) \
	((cp)->cache_compare)

#define CacheDataPtr(p) \
	((XtPointer)&((XmGadgetCacheRef*)p)-> data)

#ifndef OSF_v1_2_4
#define DataToGadgetCache(p)	((char *)p - sizeof(XmGadgetCache))
#else /* OSF_v1_2_4 */
#define DataToGadgetCache(p)	((char *)p - XtOffsetOf(XmGadgetCacheRef, data))
#endif /* OSF_v1_2_4 */


/********    Private Function Declarations    ********/
#ifdef _NO_PROTO

extern void _XmCacheDelete() ;
extern void _XmCacheCopy() ;
extern XtPointer _XmCachePart() ;

#else

extern void _XmCacheDelete( 
                        XtPointer data) ;
extern void _XmCacheCopy( 
                        XtPointer src,
                        XtPointer dest,
                        size_t size) ;
extern XtPointer _XmCachePart( 
                        XmCacheClassPartPtr cp,
                        XtPointer cpart,
                        size_t size) ;

#endif /* _NO_PROTO */
/********    End Private Function Declarations    ********/


#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#if defined(VMS) || defined (__VMS)
#include <X11/apienvrst.h>
#endif
#endif /* _XmCacheP_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */
