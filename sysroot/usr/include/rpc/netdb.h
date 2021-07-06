/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: netdb.h,v $
 * Revision 4.2.8.1  2003/06/10  18:56:08  Spider_Boardman
 * 	Added _r-style data for name service switch support.
 *
 * Revision 4.2.6.2  1996/12/09  22:12:04  Neil_Lewis
 * 	Eliminate compiler warnings when compiled with -warnprotos.
 * 	[1996/11/12  17:37:40  Neil_Lewis]
 *
 * Revision 4.2.3.2  1994/03/29  18:30:51  Thomas_Peterson
 * 	Fixes for ANSI & C++
 * 	[1994/02/28  14:35:09  Thomas_Peterson]
 * 
 * Revision 4.2  1991/09/20  05:10:33  devbld
 * 	Adding ODE Headers
 * 
 * $EndLog$
 */
/*
 *	@(#)$RCSfile: netdb.h,v $ $Revision: 4.2.8.1 $ (DEC) $Date: 2003/06/10 18:56:08 $
 */
/*
 */

/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */ 

/*
 * Sun RPC is a product of Sun Microsystems, Inc. and is provided for
 * unrestricted use provided that this legend is included on all tape
 * media and as a part of the software program in whole or part.  Users
 * may copy or modify Sun RPC without charge, but are not authorized
 * to license or distribute it to anyone else except as part of a product or
 * program developed by the user.
 * 
 * SUN RPC IS PROVIDED AS IS WITH NO WARRANTIES OF ANY KIND INCLUDING THE
 * WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE OR TRADE PRACTICE.
 * 
 * Sun RPC is provided with no support and without any obligation on the
 * part of Sun Microsystems, Inc. to assist in its use, correction,
 * modification or enhancement.
 *
 * SUN MICROSYSTEMS, INC. SHALL HAVE NO LIABILITY WITH RESPECT TO THE
 * INFRINGEMENT OF COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY SUN RPC
 * OR ANY PART THEREOF.
 * 
 * In no event will Sun Microsystems, Inc. be liable for any lost revenue
 * or profits or other special, indirect and consequential damages, even if
 * Sun has been advised of the possibility of such damages.
 * 
 * Sun Microsystems, Inc.
 * 2550 Garcia Avenue
 * Mountain View, California  94043
 */

#ifndef _RPC_NETDB_H_
#define _RPC_NETDB_H_

#include <standards.h>

/* Really belongs in <netdb.h> */

_BEGIN_CPLUSPLUS

struct rpcent {
      char    *r_name;        /* name of server for this rpc program */
      char    **r_aliases;    /* alias list */
      int     r_number;       /* rpc program number */
};

#ifdef _OSF_SOURCE
#if defined(_THREAD_SAFE) || defined(_REENTRANT)

#ifndef	_MAXALIASES
#include <netdb.h>
#endif

struct rpcent_data {	/* should be considered opaque */
	char	line[_MAXLINELEN];
	char	*rpc_aliases[_MAXALIASES];
	void	*svc_data;
};

#endif /* _THREAD_SAFE || _REENTRANT */
#endif /* _OSF_SOURCE */

struct rpcent *getrpcbyname __((const char *)),
	      *getrpcbynumber __((int)),
	      *getrpcent __((void));
void setrpcent __((int)), endrpcent __((void));

#ifdef _OSF_SOURCE
#if defined(_THREAD_SAFE) || defined(_REENTRANT)

int getrpcbyname_r __((const char *, struct rpcent *, struct rpcent_data *)),
    getrpcbynumber_r __((int, struct rpcent *, struct rpcent_data *)),
    getrpcent_r __((struct rpcent *, struct rpcent_data *));
void setrpcent_r __((int, struct rpcent_data *)),
     endrpcent_r __((struct rpcent_data *));

#endif /* _THREAD_SAFE || _REENTRANT */
#endif /* _OSF_SOURCE */

_END_CPLUSPLUS

#endif	/* _RPC_NETDB_H_ */
