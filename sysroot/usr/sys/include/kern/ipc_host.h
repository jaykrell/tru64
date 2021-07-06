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
 *	@(#)$RCSfile: ipc_host.h,v $ $Revision: 4.2.3.3 $ (DEC) $Date: 1999/02/09 19:03:08 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */

#ifndef	_KERN_IPC_HOST_H_
#define	_KERN_IPC_HOST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include<kern/processor.h>

extern void ipc_host_init(void);

extern void ipc_processor_init(processor_t);
extern void ipc_processor_enable(processor_t);
extern void ipc_processor_disable(processor_t);
extern void ipc_processor_terminate(processor_t);

extern void ipc_pset_init(processor_set_t);
extern void ipc_pset_enable(processor_set_t);
extern void ipc_pset_disable(processor_set_t);
extern void ipc_pset_terminate(processor_set_t);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif	/* _KERN_IPC_HOST_H_ */
