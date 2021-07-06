/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: clua.h,v $
 * Revision 1.1.24.2  2007/06/01  03:15:08  Akshay_Nesari
 *  Added CLUASRV_NONE option to unset flags for a cluster alias service
 *
 * Revision 1.1.24.1  2003/10/29  13:57:57  Dan_Vuong
 *      Added CLUASRV_STICKY option for sticky port support.
 *
 * Revision 1.1.18.1  2001/11/14  18:07:44  David_Lindner
 * 	Fix for qar 87718 bsd 4.3 / 4.4 incompatibility
 *
 * Revision 1.1.13.2  2000/10/13  12:52:57  Larry_Cohen
 * 	Can not include cluster_defs.h yet.
 *
 * Revision 1.1.13.1  2000/10/12  19:52:16  Larry_Cohen
 * 	Include cluster_defs.h and redefine CLUA_MAX_MEMBERS to be CLU_MAX_MEMBERS.
 * 	Also added CLUASRV_OUT_LOCAL to be consistent with cluster version.
 *
 * Revision 1.1.5.9  1999/04/14  12:06:24  John_Carr
 * 	From Larry Cohen: Remove never-implemented CLUASRV_SINGLE_NOFAIL.
 * 	[1999/04/13  14:58:30  John_Carr]
 *
 * Revision 1.1.5.8  1999/03/11  16:27:55  John_Carr
 * 	Add CLUASRV_TRANSIENT.
 * 	[1999/03/08  15:00:23  John_Carr]
 * 
 * Revision 1.1.5.7  1999/02/11  16:54:20  Larry_Cohen
 * 	merge in cplusplus changes from tcr pool
 * 	[1999/02/11  16:51:23  Larry_Cohen]
 * 
 * Revision 1.1.5.6  1999/02/09  19:03:02  Ken_Block
 * 	Make header C++ compliant.
 * 	[1998/12/29  20:01:17  Ken_Block]
 * 
 * Revision 1.1.5.5  1998/11/17  16:31:05  Larry_Cohen
 * 	merge with tcr4os
 * 	[1998/11/17  16:27:34  Larry_Cohen]
 * 
 * Revision 1.1.3.11  1998/10/08  01:55:58  Larry_Cohen
 * 	changed long's to u_long's
 * 	[1998/10/08  01:50:30  Larry_Cohen]
 * 
 * Revision 1.1.3.10  1998/08/25  20:59:07  Farrell_Woods
 * 	prevent this file from being included more than once
 * 	[1998/08/25  19:58:43  Farrell_Woods]
 * 
 * Revision 1.1.3.9  1998/06/03  20:09:15  Larry_Cohen
 * 	change CLUA_SRV bits:  IN_NO_LOCAL, IN_NO_ALIAS
 * 	[1998/06/03  19:27:51  Larry_Cohen]
 * 
 * Revision 1.1.3.8  1998/04/07  15:53:49  Larry_Cohen
 * 	Move round robin callout definitions from clua_defs.h to here.
 * 	Change prototype definition of clua_getaliasinfo to use sockaddr pointer.
 * 	[1998/04/06  14:49:36  Larry_Cohen]
 * 
 * Revision 1.1.3.7  1998/01/30  20:00:15  Larry_Cohen
 * 	minor cleanup ... removed structure that was already ifdef'ed out.
 * 	[1998/01/30  17:31:52  Larry_Cohen]
 * 
 * Revision 1.1.3.6  1998/01/27  21:36:27  Steve_Dickson
 * 	Changed clua_getaliasinfo's prototype. The
 * 	    first argument is now a struct hostent *
 * 	[1998/01/27  20:51:09  Steve_Dickson]
 * 
 * Revision 1.1.3.5  1998/01/15  20:29:03  Larry_Cohen
 * 	cleanup in support of kch group services integration.
 * 	[1998/01/15  19:50:59  Larry_Cohen]
 * 
 * Revision 1.1.3.4  1997/12/29  22:53:41  Steve_Dickson
 * 	Added CLUA_ECONFIG to the clua_status enum
 * 	Added user function prototypes
 * 	[1997/12/29  20:50:21  Steve_Dickson]
 * 
 * Revision 1.1.3.3  1997/11/20  15:31:12  Larry_Cohen
 * 	update to support socket registration and round robin selection.
 * 	[1997/11/18  19:29:22  Larry_Cohen]
 * 
 * Revision 1.1.3.2  1997/10/20  19:50:18  Larry_Cohen
 * 	Header file for user application definitions.
 * 	[1997/10/20  14:39:40  Larry_Cohen]
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: clua.h,v $ $Revision: 1.1.24.2 $ (DEC) $Date: 2007/06/01 03:15:08 $
 */

/*
12345678901234567890123456789012345678901234567890123456789012345678901234567890
*/

/*
 *    This file contains public definitions for components of the
 *    Digital UNIX TruCluster implementation of Cluster Alias.
 */

#ifndef __CLUA_H__
#define __CLUA_H__ 1

#include <standards.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <netinet/in.h>		


#define CLUA_MAX_MEMBERS 64	/*  max members for a single alias */

/*
 *  One element of the clua_info.members array.
 */
typedef struct clua_member_info {
    unsigned short int		flags;		/* State information */
    unsigned short int		selw;		/* Selection weight */
    unsigned short int		selp;		/* Selection priority */
    unsigned short int		rpri; 		/* Router prio for this alias */
} clua_member_info_t;

/*
 *  Status information about one cluster alias.
 *  This structure is returned from a call to the library routine
 *  clua_getaliasinfo (which is called interatively to return information
 *  about one cluster alias at a time).
 */

typedef struct clua_info {
    /*
     *	Global information about this alias
     */
    struct in_addr	addr;			/* Cluster Alias IP address */
    struct in_addr	netmask;		/* Cluster Alias subnet mask */
    int			aliasid;		/* ID of this alias */
    unsigned int        flags;                  /* State information */
    /*
     *  Counters for this cluster alias (from the local node's perspective)
     */
    u_long    count_cnx_rcv_net;       /* # connections received from network */
    u_long    count_cnx_fwd_clu;       /* # connections forwarded within cluster */
    u_long    count_cnx_rcv_clu;       /* # connections received within cluster */
    u_long    count_data_rcv_net;      /* # data packets received from network */
    u_long    count_data_fwd_clu;      /* # data packets forwarded within cluster */
    u_long    count_data_rcv_clu;      /* # data packets received within cluster */
    u_long    count_dgm_rcv_net;       /* # datagrams received from network */
    u_long    count_dgm_fwd_clu;       /* # datagrams forwarded within cluster */
    u_long    count_dgm_rcv_clu;       /* # datagrams received within cluster */
    u_long    count_frag_rcv_net;      /* # fragments received from network */
    u_long    count_frag_fwd_clu;      /* # fragments forwarded within cluster */
    u_long    count_frag_rcv_clu;      /* # fragments received within cluster */
    /*
     *  Array of clua_member_status structs, indexed by memberid.
     *	If the flags field is zero, the entry is void (the node with this
     *  memberid is not a member of this alias).
     */
     int		      maxmember; /* highest entry filled in members[] (-1 if none) */
     struct clua_member_info  members[CLUA_MAX_MEMBERS];


} clua_info_t;

/*
 *  Status messages returned from cluster alias library routines.
 */

typedef enum clua_status {
    /*
     *	Errors
     */
    CLUA_ENOCLUSTER =	-100,	/* Caller is not cluster member */
    CLUA_ENODEFAULT,		/* No default alias defined */
    CLUA_NOMOREALIASES,	      	/* Normal end of clua_getaliasaddr call */
    CLUA_ENOTALIAS,		/* Specified address is not a cluster alias */
    CLUA_EBADOPTION,		/* Illegal option supplied */
    CLUA_EBADTYPE,		/* Illegal socket type supplied */
    CLUA_EPORTCONFLICT,		/* Incompatible port registration exists */
    CLUA_ENOTRESERVED,		/* Port not registered, can't unreserve */
    CLUA_EBADVERSION,		/* Unmanaged version skew between cluster nodes */
    CLUA_ENOTCONFIG,		/* Cluster alias subsystem not loaded */
    CLUA_ECONFIG,		/* Configuration manager error  */
    CLUA_ERRNO,			/* System error. error is in errno */
    /*
     * return codes for callout routine
     */
    CLUA_CALL_SUCCESS =  0,	/* use memberid supplied by callout routine */
    CLUA_CALL_DROP    =  1,	/* drop the packet */
    CLUA_CALL_LOCAL   =  2,     /* send to the local member */
    CLUA_CALL_RR      =  3,     /* let the round robin algorithm choose */

    /*
     *  Success codes
     */
    CLUA_SUCCESS =	1	/* General purpose success return */

} clua_status_t;

/* mumble: how many places does this get defined ?
 */

typedef short		aliasid_t;	/* Internal id for a cluster alias */


#define CLUASRV_MULTI	0x0010		/* in_multi option */
#define CLUASRV_SINGLE	0x0020		/* in_single option */
#define CLUASRV_IN	(CLUASRV_MULTI|CLUASRV_SINGLE) /* 'or' of in_xxx options */
#define CLUASRV_IN_NOALIAS	0x0080		/* in_noalias option */
#define CLUASRV_OUT		0x0100		/* out_alias option */
#define CLUASRV_IN_NOLOCAL	0x0200		/* in_nolocal option */
#define CLUASRV_STATIC		0x0400		/* static option */
#define CLUASRV_OUT_LOCAL	0x0800		/* out_alias_local option */
#define CLUASRV_TRANSIENT	0x1000		/* reset flags on last unbind */
#define CLUASRV_STICKY          0X2000          /* sticky port option */
#define CLUASRV_NONE		0x4000		/* no option */
#define CLUASRV_VALID           0x7fff		/* valid user flag bits */ 
#define CLUA_DFPORTFLAGS  CLUASRV_SINGLE

#define CLUASRV_FORMAT "\20\5MULTI\6SINGLE\7NOFAIL\10IN_NOALIAS\11OUT_ALIAS\12IN_NOLOCAL\13STATIC\15TRANSIENT"

#if defined (_SOCKADDR_LEN) || defined (_XOPEN_SOURCE_EXTENDED)
#define clua_getdefaultalias clua_getdefaultalias_44
#define clua_getaliasaddress clua_getaliasaddress_44
#endif

#ifndef _KERNEL
/*  Function Prototypes  */
_BEGIN_CPLUSPLUS
extern clua_status_t clua_getdefaultalias(struct sockaddr *);
extern clua_status_t clua_getaliasaddress(struct sockaddr *, int *);
extern clua_status_t clua_registerservice(u_short, int, int);
extern clua_status_t clua_unregisterservice(u_short, int);
extern int clua_testsocket(int, u_short, int, struct in_addr *);
extern clua_status_t clua_getaliasinfo(struct sockaddr *, struct clua_info *);
extern int clua_isalias(struct in_addr *);
extern void print_clua_liberror(clua_status_t);
extern char *clua_error(clua_status_t);
_END_CPLUSPLUS
#endif /* _KERNEL */

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* __CLUA_H__ */
