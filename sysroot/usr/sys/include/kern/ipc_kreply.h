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
#ifndef	_KERN_IPC_KREPLY_
#define	_KERN_IPC_KREPLY_

#ifdef __cplusplus
extern "C" {
#endif

#include <kern/kern_port.h>
#include <mach/kern_return.h>
#include <mach/port.h>
#include <mach/mach_types.h>

/*
 *	Reply port cache is private data.  Define sizes here.
 */

#define REPLY_PORT_CACHE_MAX    8
#define REPLY_PORT_CACHE_EMPTY  0


/*
 *	Functions that manipulate kernel reply ports.
 */

void		kern_init_reply_cache(void);
port_name_t 	kern_get_reply_port(void);
void 		kern_release_reply_port(kern_port_t);
kern_return_t 	kern_reply_abort(thread_t);
void		kern_dealloc_reply_port(void);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif	/* _KERN_IPC_KREPLY_ */
