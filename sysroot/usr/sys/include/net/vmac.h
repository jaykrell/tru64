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
 * @(#)$RCSfile: vmac.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2000/09/25 22:41:15 $
 */

/*
 * Contains: data structure, definitions and macros needed for VMAC support
 */

#ifndef _NET_VMAC_H_
#define _NET_VMAC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/socket.h>
#include <net/if.h>
#include <net/if_dl.h>

#ifndef REPLICATED
#define REPLICATED
#endif

/*
 * Structure used to identify virtual mac addresses.  These are created by
 * the ARP code and will be used to identify non-default mac addresses.
 * The list is hashed to allow for faster searches.
 */
struct vmac_ifnet {
        struct	vmac_ifnet *vmif_next;	/* the next structure in the list */
        struct	sockaddr_dl vmif_hwaddr;/* HW address of interface */
	int	vmif_padding;		/* to fill cache block (24 byte s_dl) */
        struct	sockaddr vmif_paddr;	/* protocol address of interface */
        int	vmif_flags;		/* IFF_UP and IFF_VMIFNET only */
        int	vmif_refcnt;		/* last one out needs to delete this */
        struct	ifnet *vmif_ifnet;	/* pointer to the real ifnet struct */
};

/* used to index into **vmac_ifnet global array */
#define VMAC_INDEX(addr) \
	(((((struct sockaddr *)addr)->sa_family == AF_INET) ? \
		(((struct sockaddr_in *)addr)->sin_addr.s_addr) : 0) \
		%vmac_mod)

/* is this VMAC struct valid or invalid? */
#define VMAC_VALID(vmifp) ((vmifp)->vmif_flags & IFF_UP)
#define VMAC_INVALID(vmifp) (((vmifp)->vmif_flags & IFF_UP) == 0)

/* are there any VMAC entries and is this interface valid for VMAC use? */
#define VMAC_ENTRIES_IFP(ifp) ((vmac_entries != 0) && \
			       ((ifp)->if_output == ether_output))

/* points to the list of virtual macs */
extern struct vmac_ifnet ** REPLICATED vmac_ifnet;

/* current number of vmac entries */
extern REPLICATED int vmac_entries;

/* controls logging of vmac events */
extern REPLICATED int vmac_log;

/* current size of vmac table, used in VMAC_INDEX macro */
extern REPLICATED int vmac_mod;

/*
 * VMAC request structure
 */
struct vmacreq {
	int cmd;			/* command, see below */
	struct	ifreq vmr_ifreq_pa;	/* contains protocol address */
        struct  ifreq vmr_ifreq_mac;	/* virtual mac address */
};

/* VMAC commands */
#define VMAC_ADD	1
#define VMAC_DELETE	2

/*
 * The vmacreq request structure is passed into the kernel via a
 * cfg_subsys_op() call with NET_CFG_VMAC as the op code and "net"
 * as the subsystem name.
 */
#define NET_CFG_VMAC	100

#ifdef __cplusplus
}
#endif

#endif /* _NET_VMAC_H_ */
