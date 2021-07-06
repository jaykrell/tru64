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
 *	@(#)$RCSfile: rquota.h,v $ $Revision: 4.2.9.3 $ (DEC) $Date: 1999/06/03 16:41:43 $
 */ 
/*
 */
/*
 * OSF/1 Release 1.0
 */

/* 
 * Copyright (c) 1988,1990 by Sun Microsystems, Inc.
 * @(#) from SUN 1.7
 */

/*
 * remote quota inquiry protocol
 */


#ifndef _rpcsvc_rquota_h
#define _rpcsvc_rquota_h

#include <standards.h>
#include <rpc/xdr.h>

#define RQUOTAPROG	100011
#define RQUOTAVERS_ORIG	1
#define RQUOTAVERS	1

/*
 * inquire about quotas for uid (assume AUTH_UNIX)
 *	input - getquota_args			(xdr_getquota_args)
 *	output - getquota_rslt			(xdr_getquota_rslt)
 */
#define RQUOTAPROC_GETQUOTA		1	/* get quota */
#define RQUOTAPROC_GETACTIVEQUOTA	2	/* get only active quotas */

/*
 * args to RQUOTAPROC_GETQUOTA and RQUOTAPROC_GETACTIVEQUOTA
 */
struct getquota_args {
	char *gqa_pathp;		/* path to filesystem of interest */
	u_int gqa_uid;			/* inquire about quota for uid */
};

/*
 * remote quota structure
 */
struct rquota {
	int rq_bsize;			/* block size for block counts */
	bool_t rq_active;		/* indicates whether quota is active */
	u_int rq_bhardlimit;		/* absolute limit on disk blks alloc */
	u_int rq_bsoftlimit;		/* preferred limit on disk blks */
	u_int rq_curblocks;		/* current block count */
	u_int rq_fhardlimit;		/* absolute limit on allocated files */
	u_int rq_fsoftlimit;		/* preferred file limit */
	u_int rq_curfiles;		/* current # allocated files */
	u_int rq_btimeleft;		/* time left for excessive disk use */
	u_int rq_ftimeleft;		/* time left for excessive files */
};	

enum gqr_status {
	Q_OK = 1,			/* quota returned */
	Q_NOQUOTA = 2,			/* noquota for uid */
	Q_EPERM = 3			/* no permission to access quota */
};

struct getquota_rslt {
	enum gqr_status gqr_status;	/* discriminant */
	struct rquota gqr_rquota;	/* valid if status == Q_OK */
};

_BEGIN_CPLUSPLUS
extern bool_t xdr_getquota_args __((XDR *, struct getquota_args *));
extern bool_t xdr_getquota_rslt __((XDR *, struct getquota_rslt *));
extern bool_t xdr_rquota __((XDR *, struct rquota *));
_END_CPLUSPLUS

#endif /*!_rpcsvc_rquota_h*/
