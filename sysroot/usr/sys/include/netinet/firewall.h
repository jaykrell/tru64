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
 * @(#)$RCSfile: firewall.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2000/07/20 15:32:49 $
 */

/*
 * Contains: data structures, definitions, and prototypes needed for
 *		firewall registration
 */

#ifndef _FIREWALL_H_
#define _FIREWALL_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _KERNEL

#include <sys/types.h>

/*
 * Structure used for IPv4 firewall I/O ops
 */
struct ip_firewall_io_ops {
	void	(* ip_input_hook)(struct mbuf *);
	int	(* ip_output_hook)(struct ifnet *,
				   struct mbuf *,
				   struct in_route *,
				   int flags,
				   struct ip_moptions *);
};

/*
 * Structure used for IPv6 firewall I/O ops
 */
struct ip6_firewall_io_ops {
	void	(* ip6_input_hook)(struct mbuf *, struct ifnet *);
	int	(* ip6_output_hook)(struct ip6_txinfo *);
};

/*
 * Structure used to register/unregister a firewall
 */
struct firewall {
	u_int	version;	/* version of data structure */
	u_int	pf;		/* protocol family (PF_INET, PF_INET6) */
	u_long	flags;		/* see FW_* below */
	void	(* in_control_hook)(struct socket *,
				    unsigned int,
				    caddr_t *,
				    struct ifnet *);
	union {
		struct ip_firewall_io_ops	ip_fw_io_ops;
		struct ip6_firewall_io_ops	ip6_fw_io_ops;
	} firewall_io_ops;
};

#define fw_ip_input_hook	firewall_io_ops.ip_fw_io_ops.ip_input_hook
#define fw_ip_output_hook	firewall_io_ops.ip_fw_io_ops.ip_output_hook

#define fw_ip6_input_hook	firewall_io_ops.ip6_fw_io_ops.ip6_input_hook
#define fw_ip6_output_hook	firewall_io_ops.ip6_fw_io_ops.ip6_output_hook

#define FIREWALL_VERSION1	1
#define FIREWALL_VERSION_MAX	FIREWALL_VERSION1

/* valid firewall structure flags */
#define FW_DISABLE_RPC_FASTPATH	0x0001 /* disable RPC "fastpath" used by NFS */
#define FW_ENABLE_RPC_FASTPATH	0x0002 /* enable RPC "fastpath" on unregister */

/* registration prototypes */
extern int register_firewall(struct firewall *);
extern int unregister_firewall(struct firewall *);

#endif /* _KERNEL */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif	/* _FIREWALL_H_ */
