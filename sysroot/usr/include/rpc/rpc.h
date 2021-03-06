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
 *	@(#)$RCSfile: rpc.h,v $ $Revision: 4.2.2.2 $ (DEC) $Date: 1996/12/09 22:12:06 $
 */
/*
 */


/* 
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 */


/*
 * rpc.h, Just includes the billions of rpc header files necessary to 
 * do remote procedure calling.
 */

#ifndef _rpc_rpc_h
#define	_rpc_rpc_h
#ifdef	KERNEL
#include "../rpc/types.h"
#include "../netinet/in.h"

/* external data representation interfaces */
#include "../rpc/xdr.h"		/* generic (de)serializer */

/* Client side only authentication */
#include "../rpc/auth.h"	/* generic authenticator (client side) */

/* Client side (mostly) remote procedure call */
#include "../rpc/clnt.h"	/* generic rpc stuff */

/* semi-private protocol headers */
#include "../rpc/rpc_msg.h"	/* protocol for rpc messages */
#include "../rpc/auth_unix.h"	/* protocol for unix style cred */
#include "../rpc/auth_des.h"	/* protocol for des style cred */

/* Server side only remote procedure callee */
#include "../rpc/svc.h"		/* service manager and multiplexer */
#include "../rpc/svc_auth.h"	/* service side authenticator */

#else

#include <rpc/types.h>		/* some typedefs */
#include <netinet/in.h>

/* external data representation interfaces */
#include <rpc/xdr.h>		/* generic (de)serializer */

/* Client side only authentication */
#include <rpc/auth.h>		/* generic authenticator (client side) */

/* Client side (mostly) remote procedure call */
#include <rpc/clnt.h>		/* generic rpc stuff */

/* semi-private protocol headers */
#include <rpc/rpc_msg.h>	/* protocol for rpc messages */
#include <rpc/auth_unix.h>	/* protocol for unix style cred */

/* Server side only remote procedure callee */
#include <rpc/svc.h>		/* service manager and multiplexer */
#include <rpc/svc_auth.h>	/* service side authenticator */

_BEGIN_CPLUSPLUS
extern int _rpc_dtablesize __((void));
_END_CPLUSPLUS

#endif /* KERNEL */

#endif /*!_rpc_rpc_h*/
