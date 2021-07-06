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
 * Avoid recursive and double includes
 */
#if !defined(__INCLUDE_IP_TCNTL_COMMON)
#define __INCLUDE_IP_TCNTL_COMMON

/*
 * Common include files
 */
#if defined(_KERNEL)
#include <net/net_globals.h>
#include <net/net_malloc.h>
#endif /* defined(_KERNEL) */
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
#include <sys/mbuf.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
/*#include <net/route.h>*/
#include <netinet/rsvp_intserv.h>

/*
 * This constant controls the state of TCNTL based debug
 */
/*#define TCNTL_DEBUG (1) */

/*
 * This constant controls if we should request that the 
 * compiler inline routines where speed may be gained. Turning
 * off this feature can help debug. 
 */
#define TCNTL_ENABLE_INLINE (1)

/*
 * This macro should be used as a prefix to inlined routines
 * as it emits a 'static'.
 */
#if defined(TCNTL_ENABLE_INLINE)
#define TCNTL_INLINED_RTN static
#else
#define TCNTL_INLINED_RTN
#endif

/*
 * Traffic control private files
 */
#include "netinet/ip_tcntl_struct.h"
#if defined(_KERNEL)
#include "netinet/ip_tcntl_funcprot.h"
#endif /* defined(_KERNEL) */

/*
 * Pull in external structures if appropriate. We basically
 * want to avoide making the declarations below if we're
 * being included by the data file itself.
 */
#if !defined(__IP_TCNTL_DATA) && defined(_KERNEL)
extern struct tcntl_conf_entry tcntl_conf[];
extern unsigned int tcntl_debug_flags;
extern struct socket *ip_rsvpd;
extern simple_lock_data_t tcntl_orphan_queue_lock;
extern unsigned int tcntl_orphan_queue_count;
extern struct tcntl_genflow *tcntl_orphan_queue_head;
extern struct lockinfo *tcntl_flowbucket_lockinfo_i;
extern struct lockinfo *tcntl_filtbucket_lockinfo_i;
extern struct lockinfo *tcntl_tcntl_lockinfo_i;
extern struct lockinfo *tcntl_orphan_lockinfo_i;
extern int ether_cl_scheduler;
extern struct socket *ip6_rsvpd;
extern REPLICATED int ip_rsvpd_configured;
extern REPLICATED int ip6_rsvpd_configured;
#endif /* !defined(__IP_TCNTL_DATA) && defined(_KERNEL) */

/*
 * End of include
 */
#endif /* !defined(__INCLUDE_IP_TCNTL_COMMON) */
