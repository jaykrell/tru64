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
 * @(#)$RCSfile: iptunnel_cfg.h,v $ $Revision: 1.1.11.1 $ (DEC) $Date: 2001/12/17 20:55:40 $
 */
#ifndef __IPTUNNEL_CFG_H
#define __IPTUNNEL_CFG_H

#define CFG_OP_IPTUNNEL_IPT 101

#ifdef _KERNEL
#include <net/net_globals.h>

#if NETSYNC_LOCK
/*
 * The IPTUNNEL_CFG_LOCK prevents multiple threads from simultaneously
 * configuring iptunnel.mod.   This lock is only necessary for the case
 * when iptunnel.mod is dynamically loaded.
 */
ndecl_lock_data(extern, iptunnel_cfg_lock)
ndecl_lock_info(extern, iptunnel_cfg_li)
#define IPTUNNEL_CFG_LOCKINIT()   ulock_setup(&iptunnel_cfg_lock, \
						iptunnel_cfg_li, TRUE)
#define IPTUNNEL_CFG_WRITE_LOCK() ulock_write(&iptunnel_cfg_lock)
#define IPTUNNEL_CFG_READ_LOCK()  ulock_read(&iptunnel_cfg_lock)
#define IPTUNNEL_CFG_UNLOCK()     ulock_done(&iptunnel_cfg_lock)
#define IPTUNNEL_CFG_ISLOCKED()   ( lockmode == 0 || \
					lock_holder(&iptunnel_cfg_lock) )

#else   /* NETSYNC_LOCK */

#define IPTUNNEL_CFG_LOCKINIT()
#define IPTUNNEL_CFG_WRITE_LOCK()
#define IPTUNNEL_CFG_READ_LOCK()
#define IPTUNNEL_CFG_UNLOCK()
#define IPTUNNEL_CFG_ISLOCKED()

#endif /* NETSYNC_LOCK */

#endif /* _KERNEL */


#endif /* __IPTUNNEL_CFG_H */
