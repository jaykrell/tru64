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
 * @(#)$RCSfile: rpc.h,v $ $Revision: 1.1.5.2 $ (DEC) $Date: 1993/06/01 20:44:58 $
 */
/*	@(#)rpc.h	1.3 90/07/17 4.1NFSSRC SMI	*/

/* 
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 *	@(#)rpc.h 1.9 88/02/08 SMI	  
 */


/*
 * rpc.h, Just includes the billions of rpc header files necessary to 
 * do remote procedure calling.
 */

#ifndef _rpc_rpc_h
#define	_rpc_rpc_h

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/user.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/protosw.h>
#include <net/net_globals.h>
#include <net/if.h>
#include <net/route.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/in_pcb.h>
#include <netinet/in_var.h>
#include <netinet/ip_var.h>
#include <kern/lock.h>

#define register 
#include <rpc/types.h>		/* some typedefs */

/* external data representation interfaces */
#include <rpc/xdr.h>		/* generic (de)serializer */

/* Client side only authentication */
#include <rpc/auth.h>		/* generic authenticator (client side) */

/* Client side (mostly) remote procedure call */
#define _rpcv2_h
#include <rpc/clnt.h>		/* generic rpc stuff */

/* semi-private protocol headers */
#include <rpc/rpc_msg.h>	/* protocol for rpc messages */
#include <rpc/auth_unix.h>	/* protocol for unix style cred */
#include <rpc/auth_des.h>	/* protocol for des style cred */

/* Server side only remote procedure callee */
#include <rpc/svc.h>		/* service manager and multiplexer */
#include <rpc/svc_auth.h>	/* service side authenticator */


#endif /*!_rpc_rpc_h*/
