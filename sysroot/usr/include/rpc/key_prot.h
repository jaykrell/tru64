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
 *	@(#)$RCSfile: key_prot.h,v $ $Revision: 4.2.3.2 $ (DEC) $Date: 1994/03/29 18:30:04 $
 */
/*
 */


/* 
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 * 1.4 87/03/10 Copyr 1986 Sun Micro 
 */


/* 
 * Compiled from key_prot.x using rpcgen.
 * DO NOT EDIT THIS FILE!
 * This is NOT source code!
 */

#ifndef _rpc_key_prot_h_
#define _rpc_key_prot_h_

#include <standards.h>
#include <rpc/types.h>
#include <rpc/auth.h>

#define KEY_PROG 100029
#define KEY_VERS 1
#define KEY_SET 1
#define KEY_ENCRYPT 2
#define KEY_DECRYPT 3
#define KEY_GEN 4
#define KEY_GETCRED 5

#define PROOT 3
#define HEXMODULUS "d4a0ba0250b6fd2ec626e7efd637df76c716e22d0944b88b"
#define HEXKEYBYTES 48
#define KEYSIZE 192
#define KEYBYTES 24
#define KEYCHECKSUMSIZE 16

enum keystatus {
	KEY_SUCCESS=0,
	KEY_NOSECRET=1,
	KEY_UNKNOWN=2,
	KEY_SYSTEMERR=3
};
typedef enum keystatus keystatus;
_BEGIN_CPLUSPLUS
bool_t xdr_keystatus __((XDR *, keystatus *));
_END_CPLUSPLUS

#ifndef KERNEL

typedef char keybuf[HEXKEYBYTES];
_BEGIN_CPLUSPLUS
bool_t xdr_keybuf __((XDR *, keybuf));
_END_CPLUSPLUS

#endif

typedef char *netnamestr;
_BEGIN_CPLUSPLUS
bool_t xdr_netnamestr __((XDR *, netnamestr *));
_END_CPLUSPLUS


struct cryptkeyarg {
	netnamestr remotename;
	des_block deskey;
};
typedef struct cryptkeyarg cryptkeyarg;
_BEGIN_CPLUSPLUS
bool_t xdr_cryptkeyarg __((XDR *, cryptkeyarg *));
_END_CPLUSPLUS


struct cryptkeyres {
	keystatus status;
	union {
		des_block deskey;
	} cryptkeyres_u;
};
typedef struct cryptkeyres cryptkeyres;
_BEGIN_CPLUSPLUS
bool_t xdr_cryptkeyres __((XDR *, cryptkeyres*));
_END_CPLUSPLUS

#define MAXGIDS 16

struct unixcred {
	int uid;
	int gid;
	struct {
		u_int gids_len;
		int *gids_val;
	} gids;
};
typedef struct unixcred unixcred;
_BEGIN_CPLUSPLUS
bool_t xdr_unixcred __((XDR *, unixcred *));
_END_CPLUSPLUS


struct getcredres {
	keystatus status;
	union {
		unixcred cred;
	} getcredres_u;
};
typedef struct getcredres getcredres;
_BEGIN_CPLUSPLUS
bool_t xdr_getcredres __((XDR *, getcredres *));
_END_CPLUSPLUS

#endif /* _rpc_key_prot_h_ */
