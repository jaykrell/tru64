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
 * @(#)$RCSfile: emmtype.h,v $ $Revision: 1.1.2.6 $ (DEC) $Date: 2001/11/02 21:47:21 $
 */
/*-----------------------------------------------------------------------
 * File: EMMTYPE.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */

#ifndef _EMMTYPE_H
#define _EMMTYPE_H


/* these are the valid hint values for cssm_IsFuncCallValid */
#define CSSM_HINT_NONE (0)
#define CSSM_HINT_ADDRESS_APP (1)
#define CSSM_HINT_ADDRESS_SP (2)


typedef uint32 CSSM_MANAGER_EVENT_TYPES;
#define CSSM_MANAGER_SERVICE_REQUEST 1
#define CSSM_MANAGER_REPLY 2


typedef struct cssm_manager_event_notification {
	CSSM_SERVICE_MASK DestinationModuleManagerType;
	CSSM_SERVICE_MASK SourceModuleManagerType;
	CSSM_MANAGER_EVENT_TYPES Event;
	uint32 EventId;
	CSSM_DATA EventData;
} CSSM_MANAGER_EVENT_NOTIFICATION, *CSSM_MANAGER_EVENT_NOTIFICATION_PTR; 




#endif /* _EMMMTYPE_H */

