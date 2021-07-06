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
 *      @(#)$RCSfile: ypv1_prot.h,v $ $Revision: 4.2.5.2 $ (DEC) $Date: 1994/03/29 18:57:48 $
 */
/*
 */

/* 
 * Copyright (c) 1988,1990 by Sun Microsystems, Inc.
 * 1.4 86/07/16
 */

#ifndef _RPCSVC_YPV1_PROT_H_
#define _RPCSVC_YPV1_PROT_H_

#include <standards.h>
#include <rpcsvc/yp_prot.h>

/*
 * This contains symbol and structure definitions used in supporting the old
 * "v1" protocol.  They were previously defined in yp_prot.h.
 * 
 * This file exists so that the NIS system can provide backward compatibility.
 * Normal NIS client processes should not use this interface:  the old
 * protocol will not be supported in the next release.  
 */
#define YPOLDVERS		(YPVERS - 1)
#define YPOLDPROC_NULL		0
#define YPOLDPROC_DOMAIN	1
#define YPOLDPROC_DOMAIN_NONACK	2
#define YPOLDPROC_MATCH		3
#define YPOLDPROC_FIRST		4
#define YPOLDPROC_NEXT		5
#define YPOLDPROC_POLL		6
#define YPOLDPROC_PUSH		7
#define YPOLDPROC_PULL		8
#define YPOLDPROC_GET		9

enum ypreqtype {YPREQ_KEY = 1, YPREQ_NOKEY = 2, YPREQ_MAP_PARMS = 3};
struct yprequest {
	enum ypreqtype yp_reqtype;
	union {
		struct ypreq_key yp_req_keytype;
		struct ypreq_nokey yp_req_nokeytype;
		struct ypmap_parms yp_req_map_parmstype;
	}yp_reqbody;
};

#define YPMATCH_REQTYPE YPREQ_KEY
#define ypmatch_req_domain yp_reqbody.yp_req_keytype.domain
#define ypmatch_req_map yp_reqbody.yp_req_keytype.map
#define ypmatch_req_keydat yp_reqbody.yp_req_keytype.keydat
#define ypmatch_req_keyptr yp_reqbody.yp_req_keytype.keydat.dptr
#define ypmatch_req_keysize yp_reqbody.yp_req_keytype.keydat.dsize

#define YPFIRST_REQTYPE YPREQ_NOKEY
#define ypfirst_req_domain yp_reqbody.yp_req_nokeytype.domain
#define ypfirst_req_map yp_reqbody.yp_req_nokeytype.map

#define YPNEXT_REQTYPE YPREQ_KEY
#define ypnext_req_domain yp_reqbody.yp_req_keytype.domain
#define ypnext_req_map yp_reqbody.yp_req_keytype.map
#define ypnext_req_keydat yp_reqbody.yp_req_keytype.keydat
#define ypnext_req_keyptr yp_reqbody.yp_req_keytype.keydat.dptr
#define ypnext_req_keysize yp_reqbody.yp_req_keytype.keydat.dsize

#define YPPUSH_REQTYPE YPREQ_NOKEY
#define yppush_req_domain yp_reqbody.yp_req_nokeytype.domain
#define yppush_req_map yp_reqbody.yp_req_nokeytype.map

#define YPPULL_REQTYPE YPREQ_NOKEY
#define yppull_req_domain yp_reqbody.yp_req_nokeytype.domain
#define yppull_req_map yp_reqbody.yp_req_nokeytype.map

#define YPPOLL_REQTYPE YPREQ_NOKEY
#define yppoll_req_domain yp_reqbody.yp_req_nokeytype.domain
#define yppoll_req_map yp_reqbody.yp_req_nokeytype.map

#define YPGET_REQTYPE YPREQ_MAP_PARMS
#define ypget_req_domain yp_reqbody.yp_req_map_parmstype.domain
#define ypget_req_map yp_reqbody.yp_req_map_parmstype.map
#define ypget_req_ordernum yp_reqbody.yp_req_map_parmstype.ordernum
#define ypget_req_owner yp_reqbody.yp_req_map_parmstype.owner

enum ypresptype {YPRESP_VAL = 1, YPRESP_KEY_VAL = 2, YPRESP_MAP_PARMS = 3};
struct ypresponse {
	enum ypresptype yp_resptype;
	union {
		struct ypresp_val yp_resp_valtype;
		struct ypresp_key_val yp_resp_key_valtype;
		struct ypmap_parms yp_resp_map_parmstype;
	} yp_respbody;
};

#define YPMATCH_RESPTYPE YPRESP_VAL
#define ypmatch_resp_status yp_respbody.yp_resp_valtype.status
#define ypmatch_resp_valdat yp_respbody.yp_resp_valtype.valdat
#define ypmatch_resp_valptr yp_respbody.yp_resp_valtype.valdat.dptr
#define ypmatch_resp_valsize yp_respbody.yp_resp_valtype.valdat.dsize

#define YPFIRST_RESPTYPE YPRESP_KEY_VAL
#define ypfirst_resp_status yp_respbody.yp_resp_key_valtype.status
#define ypfirst_resp_keydat yp_respbody.yp_resp_key_valtype.keydat
#define ypfirst_resp_keyptr yp_respbody.yp_resp_key_valtype.keydat.dptr
#define ypfirst_resp_keysize yp_respbody.yp_resp_key_valtype.keydat.dsize
#define ypfirst_resp_valdat yp_respbody.yp_resp_key_valtype.valdat
#define ypfirst_resp_valptr yp_respbody.yp_resp_key_valtype.valdat.dptr
#define ypfirst_resp_valsize yp_respbody.yp_resp_key_valtype.valdat.dsize

#define YPNEXT_RESPTYPE YPRESP_KEY_VAL
#define ypnext_resp_status yp_respbody.yp_resp_key_valtype.status
#define ypnext_resp_keydat yp_respbody.yp_resp_key_valtype.keydat
#define ypnext_resp_keyptr yp_respbody.yp_resp_key_valtype.keydat.dptr
#define ypnext_resp_keysize yp_respbody.yp_resp_key_valtype.keydat.dsize
#define ypnext_resp_valdat yp_respbody.yp_resp_key_valtype.valdat
#define ypnext_resp_valptr yp_respbody.yp_resp_key_valtype.valdat.dptr
#define ypnext_resp_valsize yp_respbody.yp_resp_key_valtype.valdat.dsize

#define YPPOLL_RESPTYPE YPRESP_MAP_PARMS
#define yppoll_resp_domain yp_respbody.yp_resp_map_parmstype.domain
#define yppoll_resp_map yp_respbody.yp_resp_map_parmstype.map
#define yppoll_resp_ordernum yp_respbody.yp_resp_map_parmstype.ordernum
#define yppoll_resp_owner yp_respbody.yp_resp_map_parmstype.owner

_BEGIN_CPLUSPLUS
extern bool _xdr_yprequest __((XDR *, struct yprequest *));
extern bool _xdr_ypresponse __((XDR *, struct ypresponse *));
_END_CPLUSPLUS

#define YPBINDOLDVERS 		(YPBINDVERS - 1)
struct ypbind_oldsetdom {
	char ypoldsetdom_domain[YPMAXDOMAIN + 1];
	struct ypbind_binding ypoldsetdom_binding;
};
#define ypoldsetdom_addr ypoldsetdom_binding.ypbind_binding_addr
#define ypoldsetdom_port ypoldsetdom_binding.ypbind_binding_port

_BEGIN_CPLUSPLUS
extern bool _xdr_ypbind_oldsetdom __((XDR *, struct ypbind_setdom *));
_END_CPLUSPLUS

#endif /* _RPCSVC_YPV1_PROT_H_ */
