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
 * @(#)$RCSfile: auth.h,v $ $Revision: 1.1.3.3 $ (DEC) $Date: 1992/03/30 22:56:13 $
 */
/*	@(#)auth.h	1.3 90/07/17 4.1NFSSRC SMI	*/

/* 
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 *  1.17 88/02/08 SMI  
 */


/*
 * auth.h, Authentication interface.
 *
 * Copyright (C) 1984, Sun Microsystems, Inc.
 *
 * The data structures are completely opaque to the client.  The client
 * is required to pass a AUTH * to routines that create rpc
 * "sessions".
 */


#ifndef _rpc_auth_h
#define	_rpc_auth_h

#define	MAX_AUTH_BYTES	400
#define	MAXNETNAMELEN	255	/* maximum length of network user's name */

/*
 * Status returned from authentication check
 */
enum auth_stat {
	AUTH_OK=0,
	/*
	 * failed at remote end
	 */
	AUTH_BADCRED=1,			/* bogus credentials (seal broken) */
	AUTH_REJECTEDCRED=2,		/* client should begin new session */
	AUTH_BADVERF=3,			/* bogus verifier (seal broken) */
	AUTH_REJECTEDVERF=4,		/* verifier expired or was replayed */
	AUTH_TOOWEAK=5,			/* rejected due to security reasons */
	/*
	 * failed locally
	*/
	AUTH_INVALIDRESP=6,		/* bogus response verifier */
	AUTH_FAILED=7			/* some unknown reason */
};

typedef unsigned int u_int32;	/* 32-bit unsigned integers */

union des_block {
	struct {
		u_int32 high;
		u_int32 low;
	} key;
	char c[8];
};
typedef union des_block des_block;
extern bool_t xdr_des_block();

/*
 * Authentication info.  Opaque to client.
 */
struct opaque_auth {
	enum_t	oa_flavor;		/* flavor of auth */
	caddr_t	oa_base;		/* address of more auth stuff */
	u_int	oa_length;		/* not to exceed MAX_AUTH_BYTES */
};


/*
 * Auth handle, interface to client side authenticators.
 */
typedef struct {
        struct  opaque_auth     ah_cred;
        struct  opaque_auth     ah_verf;
        union   des_block       ah_key;
        struct auth_ops {
                void    (*ah_nextverf)();
                int     (*ah_marshal)();        /* nextverf & serialize */
                int     (*ah_validate)();       /* validate varifier */
                int     (*ah_refresh)();        /* refresh credentials */
                void    (*ah_destroy)();        /* destroy this structure */
        } *ah_ops;
        caddr_t ah_private;
} AUTH;

/*
 * Authentication ops.
 * The ops and the auth handle provide the interface to the authenticators.
 *
 * AUTH	*auth;
 * XDR	*xdrs;
 * struct opaque_auth verf;
 */
#define AUTH_NEXTVERF(auth)		\
		((*((auth)->ah_ops->ah_nextverf))(auth))
#define auth_nextverf(auth)		\
		((*((auth)->ah_ops->ah_nextverf))(auth))

#define AUTH_MARSHALL(auth, xdrs)	\
		((*((auth)->ah_ops->ah_marshal))(auth, xdrs))
#define auth_marshall(auth, xdrs)	\
		((*((auth)->ah_ops->ah_marshal))(auth, xdrs))

#define AUTH_VALIDATE(auth, verfp)	\
		((*((auth)->ah_ops->ah_validate))((auth), verfp))
#define auth_validate(auth, verfp)	\
		((*((auth)->ah_ops->ah_validate))((auth), verfp))

#define AUTH_REFRESH(auth)		\
		((*((auth)->ah_ops->ah_refresh))(auth))
#define auth_refresh(auth)		\
		((*((auth)->ah_ops->ah_refresh))(auth))

#define AUTH_DESTROY(auth)		\
		((*((auth)->ah_ops->ah_destroy))(auth))
#define auth_destroy(auth)		\
		((*((auth)->ah_ops->ah_destroy))(auth))


extern struct opaque_auth _null_auth;


/*
 * These are the various implementations of client side authenticators.
 */

/*
 * Unix style authentication
 * AUTH *authunix_create(machname, uid, gid, len, aup_gids)
 *	char *machname;
 *	int uid;
 *	int gid;
 *	int len;
 *	int *aup_gids;
 */
#ifdef KERNEL
extern AUTH *authkern_create();		/* takes no parameters */
#else
extern AUTH *authunix_create();
extern AUTH *authunix_create_default();	/* takes no parameters */
extern AUTH *authnone_create();		/* takes no parameters */
#endif
extern AUTH *authdes_create();	

#define AUTH_NONE	0		/* no authentication */
#define	AUTH_NULL	0		/* backward compatibility */
#define	AUTH_UNIX	1		/* unix style (uid, gids) */
#define	AUTH_SHORT	2		/* short hand unix style */
#define AUTH_DES	3		/* des style (encrypted timestamps) */

#endif /*!_rpc_auth_h*/
