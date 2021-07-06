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
 * @(#)$RCSfile: if_llinfo.h,v $ $Revision: 1.1.4.1 $ (DEC) $Date: 2002/01/28 22:32:14 $
 */

#ifndef _IF_LLINFO_H_
#define _IF_LLINFO_H_

#ifdef _KERNEL

#include <netinet/nd6_var.h>
#ifdef INTSERV
#include <netinet/ip_tcntl.h>
#endif

/*
 * Generic link-layer info struct contained in in_route of an inpcb
 */
struct in_ro_llinfo {
	caddr_t		in_ro_lhandle;		/* generic handle ptr */
	void		(*in_ro_lh_unref)(caddr_t); /* routine to unref handle*/
	u_int		in_ro_lhandle_ifindex;	/* if_index assoc. w/handle */
	u_int		in_ro_reserved;		/* reserved */
	nd6_cache_t	*in_ro_nd6_cache;	/* nd6 cache entry */
	struct vmac_ifnet *in_ro_vmifp;		/* VMAC ifnet pointer */
};

/* in_ro_llinfo macros */
#define LH_HANDLE_INDEX(inrollinfo) \
	((struct in_ro_llinfo *)(inrollinfo))->in_ro_lhandle_ifindex

#define LH_HANDLE(inrollinfo) \
	((struct in_ro_llinfo *)(inrollinfo))->in_ro_lhandle

#define LH_EXISTS(inrollinfo) \
	((inrollinfo) && LH_HANDLE((inrollinfo)))

#define LH_ND6_HANDLE(inrollinfo) \
	((struct in_ro_llinfo *)(inrollinfo))->in_ro_nd6_cache

#define LH_ND6_HANDLE_EXISTS(inrollinfo) \
	((inrollinfo) && LH_ND6_HANDLE((inrollinfo)))

#define LH_VMIFP(inrollinfo) \
	((struct in_ro_llinfo *)(inrollinfo))->in_ro_vmifp

#define LH_VMIFP_EXISTS(inrollinfo) \
	((inrollinfo) && LH_VMIFP((inrollinfo)))

#define LH_UNREF(inrollinfo) \
	(*(((struct in_ro_llinfo *)(inrollinfo))->in_ro_lh_unref))( \
		LH_HANDLE((inrollinfo)))

#define LH_FREE(inrollinfo) \
	if (LH_EXISTS((inrollinfo))) { \
		LH_UNREF((inrollinfo)); \
		LH_HANDLE((inrollinfo)) = NULL; \
		LH_HANDLE_INDEX((inrollinfo)) = UINT_MAX; \
	}

/*
 * Interface link-layer information struct passed to if_output routine
 */
struct if_llinfo {
	u_int		il_version;	/* API version - necessary? */
	u_int		il_flags;	/* see IF_LLINFO_* below */
	struct sockaddr_dl *il_dst;	/* link-layer dst address */
	struct sockaddr_dl *il_src;	/* link-layer src address */
	void		*il_lhandle;	/* handle used at link-layer */
	void		(*il_lh_unref)(caddr_t); /* routine to unref handle */
	u_int		il_lhandle_ifindex;/* ifp->if_index assoc. w/handle */
	u_int		il_reserved;	/* reserved */
#ifdef INTSERV
	struct tcntl_genflow *il_rhandle; /* flow this packet belongs to */
#else
	void		*il_rhandle;	/* padding */
#endif
	long		llinfo_pad;	/* to fill cache block */
};

#define IL_VERSION_1	1

/* if_llinfo flags */
#define	IF_LLINFO_CANCACHE	0x0001		/* link-layer can cache info */

/* if_llinfo macros */
#define IF_LH_VALID(ifllinfo) \
	((ifllinfo) && \
	 (((struct if_llinfo *)(ifllinfo))->il_version == IL_VERSION_1))

#define IF_LH_HANDLE(ifllinfo) \
	(ifllinfo)->il_lhandle

#define IF_LH_VALID_IFINDEX(ifllinfo, ifp) \
	((ifllinfo)->il_lhandle_ifindex == (ifp)->if_index)

#define IF_LH_FREE(ifllinfo) \
	(*(ifllinfo)->il_lh_unref)((ifllinfo)->il_lhandle); \
	(ifllinfo)->il_lhandle = NULL; \
	(ifllinfo)->il_lhandle_ifindex = UINT_MAX;

#endif /* _KERNEL */

#endif /* _IF_LLINFO_H_ */
