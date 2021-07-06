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
/*   $RCSfile: TextStrSoP.h,v $ $Revision: 1.1.10.2 $ $Date: 1994/09/09 21:27:50 $ */
/*
*  (c) Copyright 1989, DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS. */
/*
*  (c) Copyright 1987, 1988, 1989, 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */
#ifndef _XmTextStrSoP_h
#define _XmTextStrSoP_h
#if defined(VMS) || defined (__VMS)
#include <X11/apienvset.h>
#endif

#include <Xm/XmP.h>
#include <Xm/Text.h>

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************
 *
 * Definitions for use by sources and source users.
 *
 ****************************************************************/

typedef enum {EditDone, EditError, EditReject} XmTextStatus;

typedef enum {XmsdLeft, XmsdRight} XmTextScanDirection;
    
typedef struct _XmSourceDataRec {
    XmTextSource source;	/* Backpointer to source record. */
    XmTextWidget *widgets;	/* Array of widgets displaying this source. */
    XmTextPosition left, right; /* Left and right extents of selection. */
    char * ptr;			/* Actual string data. */
    char * value;		/* Value of the string data. */
    char * gap_start;		/* Gapped buffer start pointer */
    char * gap_end;		/* Gapped buffer end pointer */
    char * PSWC_NWLN;           /* Holder for char*, short*, int* rep of NWLN */
    int length;			/* Number of chars of data. */
    int maxlength;		/* Space allocated. */
    int old_length;		/* Space allocated for value pointer. */
    int numwidgets;		/* Number of entries in above. */
    int maxallowed;		/* The user is not allowed to grow source */
				/* to a size greater than this. */
    Time prim_time;             /* time of primary selection */
    Boolean hasselection;	/* Whether we own the selection. */
    Boolean editable;		/* Whether we allow any edits. */
} XmSourceDataRec, *XmSourceData;

#ifdef _NO_PROTO
typedef void (*AddWidgetProc)(); /* source, widget */
#else
typedef void (*AddWidgetProc)(
    		XmTextSource,
    		XmTextWidget);
#endif

#ifdef _NO_PROTO
typedef int (*CountLinesProc)(); /* source, start, length */
#else
typedef int (*CountLinesProc)(
     		XmTextSource,
     		XmTextPosition,
     		unsigned long);
#endif

#ifdef _NO_PROTO
typedef void (*RemoveWidgetProc)(); /* source, widget */
#else
typedef void (*RemoveWidgetProc)(
    		XmTextSource,
    		XmTextWidget);
#endif

#ifdef _NO_PROTO
typedef XmTextPosition (*ReadProc)(); /* source, position,
					 last_position, block */
#else
typedef XmTextPosition (*ReadProc)(
    		XmTextSource,
    		XmTextPosition,	/* starting position */
    		XmTextPosition,	/* The last position we're interested in.
			   	   Don't return info about any later
				   positions. */
    		XmTextBlock);	/* RETURN: text read in */
#endif

#ifdef _NO_PROTO
typedef XmTextStatus (*ReplaceProc)(); /* initiator, event, start, end, block,
					  call_callback */
#else
typedef XmTextStatus (*ReplaceProc)(
    		XmTextWidget,
		XEvent *,
    		XmTextPosition *,
    		XmTextPosition *,
    		XmTextBlock,
#if NeedWidePrototypes
                int);
#else
    		Boolean);
#endif /* NeedsWidePrototypes */
#endif

#ifdef _NO_PROTO
typedef XmTextPosition (*ScanProc)(); /* source, pos, sType, dir, 
					 count, include */
#else
typedef XmTextPosition (*ScanProc)(
    		XmTextSource,
    		XmTextPosition,
    		XmTextScanType,
    		XmTextScanDirection,	/* Either XmsdLeft or XmsdRight. */
    		int,
#if NeedWidePrototypes
                int);
#else
    		Boolean);
#endif /* NeedsWidePrototypes */
#endif

#ifdef _NO_PROTO
typedef Boolean (*GetSelectionProc)(); /* source, left, right */
#else
typedef Boolean (*GetSelectionProc)(
    		XmTextSource,
    		XmTextPosition *,
    		XmTextPosition *);
#endif

#ifdef _NO_PROTO
typedef void (*SetSelectionProc)(); /* source, left, right, time */
#else
typedef void (*SetSelectionProc)(
    		XmTextSource,
    		XmTextPosition,
    		XmTextPosition,
    		Time);
#endif


typedef struct _XmTextSourceRec {
    struct _XmSourceDataRec *data;   /* Source-defined data (opaque type). */
    AddWidgetProc	AddWidget;
    CountLinesProc	CountLines;
    RemoveWidgetProc	RemoveWidget;
    ReadProc		ReadSource;
    ReplaceProc		Replace;
    ScanProc		Scan;
    GetSelectionProc	GetSelection;
    SetSelectionProc	SetSelection;
} XmTextSourceRec;


/********    Private Function Declarations    ********/
#ifdef _NO_PROTO

extern char * _XmStringSourceGetString() ;
extern Boolean _XmTextFindStringBackwards() ;
extern Boolean _XmTextFindStringForwards() ;
extern Boolean _XmStringSourceFindString() ;
extern void _XmStringSourceSetGappedBuffer() ;
extern Boolean _XmTextModifyVerify() ;
extern XmTextSource _XmStringSourceCreate() ;
extern void _XmStringSourceDestroy() ;
extern char * _XmStringSourceGetValue() ;
extern void _XmStringSourceSetValue() ;
extern Boolean _XmStringSourceHasSelection() ;
extern Boolean _XmStringSourceGetEditable() ;
extern void _XmStringSourceSetEditable() ;
extern int _XmStringSourceGetMaxLength() ;
extern void _XmStringSourceSetMaxLength() ;
extern void _XmTextValueChanged();
#ifdef DEC_ISE_EXTENSION
        /* 
         * ISE merge extension (March 1994)
         * MOTIF_QAR note number: 1277
         * Changed by: TK
         */
extern void Validate();
extern void _XmStringSourceMoveMem();
#endif
#else

extern char * _XmStringSourceGetString( 
                        XmTextWidget tw,
                        XmTextPosition from,
                        XmTextPosition to,
#if NeedWidePrototypes
                        int want_wchar) ;
#else
                        Boolean want_wchar) ;
#endif /* NeedWidePrototypes */
extern Boolean _XmTextFindStringBackwards( 
                        Widget w,
                        XmTextPosition start,
                        char *search_string,
                        XmTextPosition *position) ;
extern Boolean _XmTextFindStringForwards( 
                        Widget w,
                        XmTextPosition start,
                        char *search_string,
                        XmTextPosition *position) ;
extern Boolean _XmStringSourceFindString( 
                        Widget w,
                        XmTextPosition start,
                        char *string,
                        XmTextPosition *position) ;
extern void _XmStringSourceSetGappedBuffer( 
                        XmSourceData data,
                        XmTextPosition position) ;
extern Boolean _XmTextModifyVerify(
			XmTextWidget initiator,
        		XEvent *event,
        		XmTextPosition *start,
        		XmTextPosition *end,
        		XmTextPosition *cursorPos,
        		XmTextBlock block,
        		XmTextBlock newblock,
			Boolean *freeBlock) ;
extern XmTextSource _XmStringSourceCreate( 
                        char *value,
#if NeedWidePrototypes
                        int is_wchar) ;
#else
                        Boolean is_wchar) ;
#endif /* NeedWidePrototypes */
extern void _XmStringSourceDestroy( 
                        XmTextSource source) ;
extern char * _XmStringSourceGetValue( 
                        XmTextSource source,
#if NeedWidePrototypes
                        int want_wchar) ;
#else
                        Boolean want_wchar) ;
#endif /* NeedWidePrototypes */
extern void _XmStringSourceSetValue( 
                        XmTextWidget widget,
                        char *value) ;
extern Boolean _XmStringSourceHasSelection( 
                        XmTextSource source) ;
extern Boolean _XmStringSourceGetEditable( 
                        XmTextSource source) ;
extern void _XmStringSourceSetEditable( 
                        XmTextSource source,
#if NeedWidePrototypes
                        int editable) ;
#else
                        Boolean editable) ;
#endif /* NeedWidePrototypes */
extern int _XmStringSourceGetMaxLength( 
                        XmTextSource source) ;
extern void _XmStringSourceSetMaxLength( 
                        XmTextSource source,
                        int max) ;
extern void _XmTextValueChanged(XmTextWidget initiator,
				XEvent *event);
#ifdef DEC_ISE_EXTENSION
        /* 
         * ISE merge extension (March 1994)
         * MOTIF_QAR note number: 1277
         * Changed by: TK
         */
extern void Validate(
			XmTextPosition * start,
			XmTextPosition * end,
			int maxsize);
extern void _XmStringSourceMoveMem(
        		char * from,
        		char * to,
        		int length);
#endif

#endif /* _NO_PROTO */
/********    End Private Function Declarations    ********/


#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#if defined(VMS) || defined (__VMS)
#include <X11/apienvrst.h>
#endif
#endif /*  _XmTextStrSoP_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */
