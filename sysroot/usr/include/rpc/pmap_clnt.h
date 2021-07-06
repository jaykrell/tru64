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
 *	@(#)$RCSfile: pmap_clnt.h,v $ $Revision: 4.2.6.3 $ (DEC) $Date: 1996/09/20 20:52:21 $
 */
/*
 */


/* 
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 */


/*
 * pmap_clnt.h
 * Supplies C routines to get to portmap services.
 */

/*
 * Usage:
 *	success = pmap_set(program, version, protocol, port);
 *	success = pmap_unset(program, version);
 *	port = pmap_getport(address, program, version, protocol);
 *	head = pmap_getmaps(address);
 *	clnt_stat = pmap_rmtcall(address, program, version, procedure,
 *		xdrargs, argsp, xdrres, resp, tout, port_ptr)
 *		(works for udp only.) 
 * 	clnt_stat = clnt_broadcast(program, version, procedure,
 *		xdrargs, argsp,	xdrres, resp, eachresult)
 *		(like pmap_rmtcall, except the call is broadcasted to all
 *		locally connected nets.  For each valid response received,
 *		the procedure eachresult is called.  Its form is:
 *	done = eachresult(resp, raddr)
 *		bool_t done;
 *		caddr_t resp;
 *		struct sockaddr_in raddr;
 *		where resp points to the results of the call and raddr is the
 *		address if the responder to the broadcast.
 */

#ifndef _rpc_pmap_clnt_h
#define	_rpc_pmap_clnt_h

#include <standards.h>
#if defined(__STDC__) || defined(__cplusplus)
#include <rpc/clnt.h>
#endif

_BEGIN_CPLUSPLUS
extern bool_t		pmap_set __((u_int, u_int, int, u_short));
extern bool_t		pmap_unset __((u_int, u_int));
extern struct pmaplist	*pmap_getmaps __((struct sockaddr_in *));
enum clnt_stat	pmap_rmtcall __((struct sockaddr_in *, u_int, u_int, u_int,
                xdrproc_t, caddr_t, xdrproc_t, caddr_t,
                struct timeval, u_int *));
enum clnt_stat	clnt_broadcast __((u_int, u_int, u_int, xdrproc_t, char *,
                xdrproc_t, char *, bool_t (*) ( char *, struct sockaddr_in *)));
extern u_short		pmap_getport __((struct sockaddr_in *, u_int, u_int, u_int));
_END_CPLUSPLUS

#endif /*!_rpc_pmap_clnt_h*/
