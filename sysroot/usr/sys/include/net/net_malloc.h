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
 *	@(#)$RCSfile: net_malloc.h,v $ $Revision: 4.3.8.5 $ (DEC) $Date: 1993/10/07 21:58:57 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.2
 */
/*
 * Malloc header file for OSF/1 networking.
 *
 *	NET_MALLOC(pointer, cast, size, type, flag)
 *	NET_FREE(pointer, type)
 *	(types, flags, etc defined)
 *
 * If Unix (4.4) we expect malloc.h to define the support.
 * Now OSF/1 provides the same interfaces.
 */

#ifndef _NET_MALLOC_H_
#define _NET_MALLOC_H_

#include "sys/malloc.h"
#include "mach/vm_param.h"

#define NET_MALLOC(p,c,s,t,f)   MALLOC(p,c,s,t,f)
#define NET_FREE(p,t)           FREE(p,t)

#endif
