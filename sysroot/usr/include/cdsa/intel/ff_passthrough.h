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
 * @(#)$RCSfile: ff_passthrough.h,v $ $Revision: 1.1.2.7 $ (DEC) $Date: 2002/03/20 21:54:39 $
 */
/*-----------------------------------------------------------------------
 * File: FF_PASSTHROUGH.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */

#ifndef _FF_PASSTHROUGH_H
#define _FF_PASSTHROUGH_H

#include "cssmerr.h"

#define FFDL_PASSTHROUGH_SET_WRITE_BACK_CACHE    1

/* Passthrough data types */
typedef enum ffdl_write_back_cache_status
{
	FFDL_ENABLE_CACHE = 0,
	FFDL_DISABLE_CACHE = 1
} FFDL_WRITE_BACK_CACHE_STATUS;


/* Passthrough error codes */
#define FFDL_CACHE_STATUS_INVALID        (CSSM_DL_PRIVATE_ERROR + 0)
#define LAST_FFDL_PASSTHROUGH_ERROR      (FFDL_CACHE_STATUS_INVALID)

#endif /* _FF_PASSTHROUGH_H */
