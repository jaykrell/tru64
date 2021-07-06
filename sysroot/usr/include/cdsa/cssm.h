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
 * @(#)$RCSfile: cssm.h,v $ $Revision: 1.1.2.7 $ (DEC) $Date: 2001/11/02 21:47:01 $
 */
/*-----------------------------------------------------------------------
 * File: CSSM.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */

/* Portions:
 * (C) COPYRIGHT International Business Machines Corp. 1996, 1997
 * All Rights Reserved
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/* 
 * Basic include file for all CSSM headers. Behavior of the file can be
 * modified by specifying pre-processor symbols prior to including the
 * header.
 *
 * Identifier		Result
 * ----------       ------
 * NO_CSSM_SPI		The types and functions for the CSSM SPI are not
 *					included.
 * NO_CSSM_EMM_API	The types and functions for the CSSM EMM API are not
 *					included.
 * CSSM_LEAN		Equivalent to specifying all of the above identifiers.
 */

#ifndef __CSSM_H__
#define __CSSM_H__

#ifdef __unix__
#ifndef UNIX
#define UNIX
#endif
#endif

#if defined(CSSM_LEAN)
#define NO_CSSM_SPI
#define NO_CSSM_EMM_API
#endif /* defined(CSSM_LEAN) */

/* Version information */
/* Version 2.1.0.X */
#define CSSM_MAJOR 2 /* Major version # */
#define CSSM_MINOR 1 /* Minor version # */

/* All data types defined by the CSSM API specification */
#include "cssmtype.h"

/* All APIs defined by the CSSM API specification for the CSSM core,
 * CSP, CL, DL, TP, and AC modules. If the symbol KEY_RECOVERY is
 * defined, then the optional KR APIs will also be defined.
 */
#include "cssmapi.h"

/* Error code definitions used in the CSSM specification. */
#include "cssmerr.h"

#if !defined(NO_CSSM_SPI)
/* Data types and function declarations for the common interfaces
 * that must be implemented by a CDSA service provider.
 */
#include "cssmspi.h"

/* Interfaces that must be implemented by a Cryptographic Service Provider
 * (CSP) SPI.
 */
#include "cssmcspi.h"

/* Interfaces that must be implemented by a Data Storage Library (DL) SPI.
 */
#include "cssmdli.h"

/* Interfaces that must be implemented by a Certificate Services Library 
 * (CL) SPI.
 */
#include "cssmcli.h"

/* Interfaces that must be implemented by a Trust Policy Library (TP) SPI.
 */
#include "cssmtpi.h"

/* Interfaces that must be implemented by an Authorization Computation
 * Library (AC) SPI.
 */
#include "cssmaci.h"

#endif /* !defined(NO_CSSM_SPI) */

#if !defined(NO_CSSM_EMM_API)
/* Data types and interfaces defined by the CSSM for interaction with
 * Elective Module Managers (EMM).
 */
#include "emmtype.h"
#include "emmspi.h"

#endif /* !defined(NO_CSSM_EMM_API) */

#endif /* ifndef __CSSM_H__ */
