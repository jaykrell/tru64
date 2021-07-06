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
 * @(#)$RCSfile: DXmAclEditorP.h,v $ $Revision: 1.1.17.1 $ (DEC) $Date: 2001/09/17 13:50:54 $
 */

#ifndef _DXmAclP_h
#define _DXmAclP_h

#if defined(VMS) || defined (__VMS)
#include <X11/apienvset.h>
#endif

#include <sys/security.h>
#include <sys/acl.h>
#include <Xm/SelectioBP.h>
#include "DXmAclEditor.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Defines for geometry manager. */
#define DXmAE_MAX_WIDGETS_VERT 20

/* Constraint part record for AclEditor widget */

typedef struct _DXmAclEditorConstraintPart
{
   char unused;
} DXmAclEditorConstraintPart, * DXmAclEditorConstraint;

/*  New fields for the AclEditor widget class record  */

typedef struct
{
    XtPointer           extension;      /* Pointer to extension record */
} DXmAclEditorClassPart;


/* Full class record declaration */

typedef struct _DXmAclEditorClassRec
{
   CoreClassPart       core_class;
   CompositeClassPart  composite_class;
   ConstraintClassPart constraint_class;
   XmManagerClassPart  manager_class;
   XmBulletinBoardClassPart    bulletin_board_class;
   XmSelectionBoxClassPart    selection_box_class;
   DXmAclEditorClassPart    acl_editor_class;
} DXmAclEditorClassRec;

externalref DXmAclEditorClassRec dxmAclEditorClassRec;


typedef struct _dxmAclModes {
    Widget	r;
    Widget	w;
    Widget	x;
} DXmAclModesRec, *DXmAclModes;
    

typedef struct _dxmAclEntry
{
    Widget	tag;
    Widget	qualifier;
    DXmAclModesRec modes;
} DXmAclEntryRec, *DXmAclEntry;

/* New fields for the AclEditor widget record */

typedef struct
{
    String	    acl_string;			/* resource */
    XtPointer	    acl_acl;			/* resource */
    XtCallbackList  validate_callback;		/* resource */
    XmString	    object_type_label_string;	/* resource */
    String	    object_type_value;		/* resource */
    XmString	    object_name_label_string;	/* resource */
    String	    object_name_value;		/* resource */
    XmString	    owner_label_string;		/* resource */
    String	    owner_value;		/* resource */
    XmString	    group_label_string;		/* resource */
    String	    group_value;		/* resource */
    Widget	    object_type_label;
    Widget	    object_type_field;
    Widget	    object_name_label;
    Widget	    object_name_field;
    Widget	    owner_label;
    Widget	    owner_field;
    Widget	    group_label;
    Widget	    group_field;
    Widget	    add_button;
    Widget	    modify_button;
    Widget          delete_button;
    Widget	    reset_button;
    Widget	    new_entry_dialog;
    Widget	    new_form;
    DXmAclEntryRec  new_entry;
    XmString        tag_strings[3];
    XmString        mode_strings[4];
    XmString        add_string;
    XmString        delete_string;
    Dimension       mode_button_width;
} DXmAclEditorPart;

/****************************************************************
 *
 * Full instance record declaration
 *
 ****************************************************************/

typedef struct _DXmAclEditorRec
{
    CorePart	            core;
    CompositePart           composite;
    ConstraintPart          constraint;
    XmManagerPart           manager;
    XmBulletinBoardPart     bulletin_board;
    XmSelectionBoxPart      selection_box;
    DXmAclEditorPart	    acl_editor;
} DXmAclEditorRec;


/* Access macros */
#define DXmAE_Acl(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.acl_acl)
#define DXmAE_AclString(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.acl_string)
#define DXmAE_ObjectTypeLabelString(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.object_type_label_string)
#define DXmAE_ObjectTypeLabel(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.object_type_label)
#define DXmAE_ObjectTypeValue(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.object_type_value)
#define DXmAE_ObjectTypeField(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.object_type_field)
#define DXmAE_ObjectNameLabelString(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.object_name_label_string)
#define DXmAE_ObjectNameLabel(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.object_name_label)
#define DXmAE_ObjectNameValue(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.object_name_value)
#define DXmAE_ObjectNameField(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.object_name_field)
#define DXmAE_OwnerLabelString(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.owner_label_string)
#define DXmAE_OwnerLabel(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.owner_label)
#define DXmAE_OwnerValue(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.owner_value)
#define DXmAE_OwnerField(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.owner_field)
#define DXmAE_GroupLabelString(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.group_label_string)
#define DXmAE_GroupLabel(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.group_label)
#define DXmAE_GroupValue(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.group_value)
#define DXmAE_GroupField(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.group_field)
#define DXmAE_NewEntry(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.new_entry_dialog)
#define DXmAE_NewForm(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.new_form)
#define DXmAE_AddButton(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.add_button)
#define DXmAE_ModifyButton(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.modify_button)
#define DXmAE_DeleteButton(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.delete_button)
#define DXmAE_ResetButton(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.reset_button)
#define DXmAE_NewTag(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.new_entry.tag)
#define DXmAE_NewQualifier(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.new_entry.qualifier)
#define DXmAE_NewRButton(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.new_entry.modes.r)
#define DXmAE_NewWButton(_w) \
    (((DXmAclEditorWidget)(_w))->acl_editor.new_entry.modes.w)
#define DXmAE_NewXButton(w) \
    (((DXmAclEditorWidget)(w))->acl_editor.new_entry.modes.x)

#define DXmAE_USER_LABEL 0
#define DXmAE_GROUP_LABEL 1
#define DXmAE_OTHER_LABEL 2

#define DXmAE_user_string(w) (((DXmAclEditorWidget)(w))->acl_editor.tag_strings[DXmAE_USER_LABEL])
#define DXmAE_group_string(w) (((DXmAclEditorWidget)(w))->acl_editor.tag_strings[DXmAE_GROUP_LABEL])
#define DXmAE_other_string(w) (((DXmAclEditorWidget)(w))->acl_editor.tag_strings[DXmAE_OTHER_LABEL])
#define DXmAE_r_string(w) (((DXmAclEditorWidget)(w))->acl_editor.mode_strings[0])
#define DXmAE_w_string(w) (((DXmAclEditorWidget)(w))->acl_editor.mode_strings[1])
#define DXmAE_x_string(w) (((DXmAclEditorWidget)(w))->acl_editor.mode_strings[2])
#define DXmAE_off_string(w) (((DXmAclEditorWidget)(w))->acl_editor.mode_strings[3])
#define DXmAE_add_string(w) (((DXmAclEditorWidget)(w))->acl_editor.add_string)
#define DXmAE_delete_string(w) (((DXmAclEditorWidget)(w))->acl_editor.delete_string)

#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#if defined(VMS) || defined (__VMS)
#include <X11/apienvrst.h>
#endif
#endif /* _DXmAclP_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */
