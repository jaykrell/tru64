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
 * @(#)$RCSfile: DXmAclEditor.h,v $ $Revision: 1.1.20.1 $ (DEC) $Date: 2002/01/29 17:35:43 $
 */

#ifndef _DXmAcl_h
#define _DXmAcl_h
#if defined(VMS) || defined (__VMS)
#include <X11/apienvset.h>
#endif

#include <Xm/Xm.h>

#ifdef __cplusplus
extern "C" {
#endif


/* Type definitions for AclEditor resources: */


/* Class record constants */

externalref WidgetClass dxmAclEditorWidgetClass;

typedef struct _DXmAclEditorClassRec * DXmAclEditorWidgetClass;
typedef struct _DXmAclEditorRec      * DXmAclEditorWidget;


#ifndef DXmIsAclEditor
#define DXmIsAclEditor(w) (XtIsSubclass((w),dxmAclEditorWidgetClass))
#endif


/* Resource constants */
#define DXmNacl "acl"
#define DXmCacl "Acl"
#define DXmNaclString "aclString"
#define DXmCaclString "AclString"
#define DXmNvalidateCallback       "validateCallback"
#define DXmNobjectTypeLabelString  "objectTypeLabelString"
#define DXmCobjectTypeLabelString  "ObjectTypeLabelString"
#define DXmNobjectTypeValue        "objectTypeValue"
#define DXmCobjectTypeValue        "ObjectTypeValue"
#define DXmNobjectNameLabelString  "objectNameLabelString"
#define DXmCobjectNameLabelString  "ObjectNameLabelString"
#define DXmNobjectNameValue        "objectNameValue"
#define DXmCobjectNameValue        "ObjectNameValue"
#define DXmNownerLabelString	   "ownerLabelString"
#define DXmCownerLabelString	   "OwnerLabelString"
#define DXmNownerValue		   "ownerValue"
#define DXmCownerValue		   "OwnerValue"
#define DXmNgroupLabelString	   "groupLabelString"
#define DXmCgroupLabelString	   "GroupLabelString"
#define DXmNgroupValue		   "groupValue"
#define DXmCgroupValue		   "GroupValue"
#define DXmNaclEntryListLabelString "aclEntryListLabelString"
#define DXmCaclEntryListLabelString "AclEntryListLabelString"

/* Constants for the DXmGetAclEditorGetChild() function. */
enum {
    DXmDIALOG_NONE,
    DXmDIALOG_APPLY_BUTTON,
    DXmDIALOG_CANCEL_BUTTON,
    DXmDIALOG_DEFAULT_BUTTON,
    DXmDIALOG_OK_BUTTON,
    DXmDIALOG_HELP_BUTTON,
    DXmDIALOG_OBJECT_NAME_FIELD,
    DXmDIALOG_OBJECT_TYPE_FIELD,
    DXmDIALOG_ACCESS_CONTROL_LIST,
    DXmDIALOG_NEW_ENTRY_BUTTON,
    DXmDIALOG_NEW_DELETE_BUTTON,
    DXmDIALOG_NEW_ADD_BUTTON,
    DXmDIALOG_NEW_TAG,
    DXmDIALOG_NEW_QUALIFIER,
    DXmDIALOG_RESET_BUTTON,
    DXmDIALOG_NEW_ENTRY_DB,
    DXmDIALOG_NEW_MODIFY_BUTTON
};

/* Callback reasons. */
enum{	DXmCR_VALIDATE = 105
    };

typedef struct
{
    int		reason;
    XEvent    * event;
    Boolean	valid;
    XtPointer	acl;
    String	value;
    ssize_t	length;
} DXmAclEditorCallbackStruct;

/********    Public Function Declarations    ********/
#ifdef _NO_PROTO

extern Widget DXmAclEditorGetChild() ;
extern Widget DXmCreateAclEditor() ;
extern Widget DXmCreateAclEditorDialog() ;

#else

extern Widget DXmAclEditorGetChild( 
                        Widget fs,
#if NeedWidePrototypes
                        unsigned int which) ;
#else
                        unsigned char which) ;
#endif /* NeedWidePrototypes */
extern Widget DXmCreateAclEditor( 
                        Widget p,
                        String name,
                        ArgList args,
                        Cardinal n) ;
extern Widget DXmCreateAclEditorDialog( 
                        Widget ds_p,
                        String name,
                        ArgList fsb_args,
                        Cardinal fsb_n) ;

#endif /* _NO_PROTO */
/********    End Public Function Declarations    ********/


#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#if defined(VMS) || defined (__VMS)
#include <X11/apienvrst.h>
#endif
#endif /* _DXmAcl_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */
