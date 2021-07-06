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
 * @(#)$RCSfile: ipv6_cfg.h,v $ $Revision: 1.1.4.1 $ (DEC) $Date: 1999/10/18 20:21:47 $
 */

#ifndef _IPV6_CFG_H
#define _IPV6_CFG_H



#ifdef _KERNEL

#include <net/net_globals.h>

#if NETSYNC_LOCK
/* 
 * The IPV6_CFG_LOCK prevents multiple threads from simultaneously
 * configuring ipv6.mod.   This lock is only necessary for the case
 * when ipv6.mod is dynamically loaded.
 */
ndecl_lock_data(extern, ipv6_cfg_lock)
ndecl_lock_info(extern, ipv6_cfg_li)
#define IPV6_CFG_LOCKINIT()   ulock_setup(&ipv6_cfg_lock, ipv6_cfg_li, TRUE)
#define IPV6_CFG_WRITE_LOCK() ulock_write(&ipv6_cfg_lock)
#define IPV6_CFG_READ_LOCK()  ulock_read(&ipv6_cfg_lock)
#define IPV6_CFG_UNLOCK()     ulock_done(&ipv6_cfg_lock)
#define IPV6_CFG_ISLOCKED()   ( lockmode == 0 || lock_holder(&ipv6_cfg_lock) )

#else   /* NETSYNC_LOCK */

#define IPV6_CFG_LOCKINIT()  
#define IPV6_CFG_WRITE_LOCK()
#define IPV6_CFG_READ_LOCK() 
#define IPV6_CFG_UNLOCK()    
#define IPV6_CFG_ISLOCKED()  

#endif /* NETSYNC_LOCK */

#endif /* _KERNEL */

#endif /* _IPV6_CFG_H */
