/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: mbuf.h,v $
 * Revision 4.3.77.1  2003/09/23  22:01:04  Brian_Haley
 * 	Added M_IPSEC_AUTH flag for Mobile IPv6 work, this tells mobility
 * 	that the packet was authenticated by IPsec.
 *
 * Revision 4.3.68.1  2002/01/29  21:19:44  Geraldine_Harter
 * 	Add VMS code changes needed to facilitate porting TCP/IP to VMS.
 *
 * Revision 4.3.63.5  2001/07/10  15:02:08  Paul_Moore
 * 	backport of wildcatos-760-grebus
 *
 * Revision 4.3.63.4  2001/03/09  13:48:33  Rod_Payne
 * 	Removed M_NETRAIN - lsg failure detection has been decoupled from netrain.
 *
 * Revision 4.3.63.3  2000/11/09  20:17:33  Rod_Payne
 * 	Add M_NETRAIN flag to enable monitoring of non-netrain interfaces
 * 	for link aggregation.
 *
 * Revision 4.3.63.2  2000/10/24  22:48:23  Brian_Haley
 * 	Changed M_IFLLINFO #define to not conflict with M_IPSEC_UDP_SEND_FP
 * 	in crypto pool.  Merged M_IPSEC_UDP_SEND_FP in as well.
 *
 * Revision 4.3.63.1  2000/09/25  22:42:40  Brian_Haley
 * 	Added M_IFLLINFO flag for if_llinfo work.
 *
 * Revision 4.3.59.3  2000/07/20  15:32:56  Brian_Haley
 * 	Re-named IPsec mbuf flags to make them more generic - kept old flags
 * 	around for backwards-compatibility.
 *
 * Revision 4.3.59.2  2000/03/17  15:13:52  Brian_Haley
 * 	NUMA replication work - max_linkhdr, max_protohdr
 *
 * Revision 4.3.59.1  2000/01/21  20:14:47  Dan_Vuong
 * 	add M_IPSEC_INPUT_DONE and M_IPSEC_OUTPUT_DONE for SSH IPsec
 *
 * Revision 4.3.57.2  1999/08/25  19:25:57  Larry_Cohen
 * 	Added M_NOCHECKSUM flag to avoid checksumming cluster alias packets
 * 	that originate from the cluster and are tunneled over the cluster
 * 	interconnect.
 *
 * 	Added both M_NOCHECKSUM and M_ALIAS to M_COPYFLAGS.
 * 	[1999/08/25  18:58:48  Larry_Cohen]
 *
 * Revision 4.3.30.11  1999/02/09  19:03:52  Ken_Block
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rSTEELOS;PTEV6OS_BL8;<> **
 * 		** Ancestor revision:	4.3.30.9 **
 * 		** Merge revision:	4.3.30.10 **
 * 	 	** End **
 * 	[1999/01/26  23:22:09  Ken_Block]
 * 
 * 	Make header C++ compliant.
 * 	[1998/12/29  20:22:34  Ken_Block]
 * 
 * Revision 4.3.30.10  1999/01/20  19:08:01  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTEV6OS_BL8:PTFCOS_BL3 **
 * 		** Ancestor revision:	4.3.43.2 **
 * 		** Merge revision:	4.3.49.3 **
 * 	 	** End **
 * 	[1999/01/20  19:06:04  Tony_Bono]
 * 
 * Revision 4.3.49.3  1998/10/29  21:01:12  Ashoke_Rampuria
 * 	Made mbuf and mbuf_ext_lock compatible with the old
 * 	mbuf lock.
 * 	[1998/10/29  17:21:39  Ashoke_Rampuria]
 * 
 * Revision 4.3.49.2  1998/10/01  15:37:09  Ashoke_Rampuria
 * 	Added MBUF_EXT_LOCK macros.
 * 	[1998/09/30  23:16:50  Ashoke_Rampuria]
 * 
 * Revision 4.3.30.9  1998/07/30  21:48:16  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTEV6OS_BL4:PTEV6OS_BL6 **
 * 		** Ancestor revision:	4.3.40.2 **
 * 		** Merge revision:	4.3.43.2 **
 * 	 	** End **
 * 	[1998/07/30  21:37:27  Tony_Bono]
 * 
 * Revision 4.3.43.2  1998/05/01  22:22:28  Tony_Bono
 * 	Added parameter to support modification of m_copym to optionally
 * 	ignore too short mbuf chains even if M_COPYALL is not set. This
 * 	prevents panics when the user passes the wrong length to a raw
 * 	ip socket.
 * 	[1998/04/30  22:36:55  Tony_Bono]
 * 
 * Revision 4.3.30.8  1998/01/21  21:15:18  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL11:PTCOS_BL14 **
 * 		** Ancestor revision:	4.3.19.7 **
 * 		** Merge revision:	4.3.40.2 **
 * 	 	** End **
 * 	[1998/01/21  20:53:48  Tony_Bono]
 * 
 * Revision 4.3.30.7  1997/11/06  12:26:17  James_Woodward
 * 	per-perocessor numa work
 * 	[1997/11/03  13:25:48  James_Woodward]
 * 
 * Revision 4.3.40.2  1997/10/09  23:22:33  Tony_Bono
 * 	Added the definitions of Flags and fields used to
 * 	support caching of checksums and wiring user pages
 * 	for output.
 * 	[1997/10/09  20:04:03  Tony_Bono]
 * 
 * Revision 4.3.30.6  1997/07/23  15:41:24  John_Dustin
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	4.3.30.4 **
 * 		** Merge revision:	4.3.30.5 **
 * 	 	** End **
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -r4.3.30.4 **
 * 		** Ancestor revision:	4.3.30.3 **
 * 		** Merge revision:	4.3.30.4 **
 * 	 	** End **
 * 	RSVP project, Markus Jork
 * 
 * 	Removed #ifdef INTSERV around M_RHANDLE definition and
 * 	added it to M_COPYFLAGS.
 * 	[1997/06/18  16:34:24  Markus_Jork]
 * 
 * 	Added new mbuf flag M_RHANDLE for traffic control / RSVP.
 * 	[1997/06/17  18:28:31  Markus_Jork]
 * 
 * Revision 4.3.30.5  1997/07/15  16:18:56  Larry_Cohen
 * 	Add cluster alias mbuf flag to indicate a packet was tunneled
 * 	to this host from a cluster alias router.
 * 	[1997/07/14  17:18:29  Larry_Cohen]
 * 
 * Revision 4.3.30.4  1997/06/18  15:37:05  Dave_King
 * 	Add typedef mbuf_t.
 * 	[1997/06/02  16:00:10  Dave_King]
 * 
 * Revision 4.3.30.3  1996/11/18  15:40:58  Brian_Haley
 * 	Moved HDRALIGN here from bsd/uipc_domain.c
 * 	[1996/11/04  21:07:59  Brian_Haley]
 * 
 * Revision 4.3.30.2  1996/05/01  20:06:51  Stephen_Ofsthun
 * 	Merge from bravos.bl2
 * 	[1996/05/01  19:57:27  Stephen_Ofsthun]
 * 
 * Revision 4.3.28.4  1996/03/10  15:37:38  Ray_Lanza
 * 	Merge of Platinum BL8 to BL11 pass 1 changes
 * 	[1996/03/10  15:19:27  Ray_Lanza]
 * 
 * Revision 4.3.19.7  1995/11/15  20:33:25  John_Dustin
 * 	add M_PROXY as hook for IBG Firewall product
 * 	[1995/11/09  16:39:12  John_Dustin]
 * 
 * Revision 4.3.19.6  1995/11/15  14:42:42  Rajul_Shah
 * 	Added #defines for M_REQUE_OK and M_REQUED_ONCE as couple
 * 	of additional mbuf-header flags.
 * 	[1995/11/13  20:16:40  Rajul_Shah]
 * 
 * Revision 4.3.19.5  1995/10/26  21:23:00  atmproj_Peter_Schulter
 * 	Merged  changes  from  shared  SB
 * 	[1995/10/25  20:42:21  atmproj_Peter_Schulter]
 * 
 * 	Added #define of M_ATM_CLP as another mbuf-header flag.
 * 	[1995/07/28  20:45:54  Rajul_Shah]
 * 
 * Revision 4.3.28.3  1995/10/25  20:00:16  Ray_Lanza
 * 	Initial __alpha conditional evaluation and changes
 * 	[1995/10/25  19:30:01  Ray_Lanza]
 * 
 * Revision 4.3.28.2  1995/10/12  20:15:25  Ray_Lanza
 * 	Initial round of basic Intel related changes
 * 	[1995/10/12  19:48:48  Ray_Lanza]
 * 
 * Revision 4.3.19.4  1995/06/30  22:39:12  Mike_Milicia
 * 	Add MLS secure networking hooks.
 * 	[1995/06/20  22:19:42  Mike_Milicia]
 * 
 * Revision 4.3.19.3  1995/04/27  19:04:55  Geraldine_Harter
 * 	Changes necessary to track the mbuf stats through the memory allocator
 * 	instead of through the mbstat struct (mbstat info was inaccurate because
 * 	of VAGUE_STATS).
 * 	[1995/04/26  18:41:22  Geraldine_Harter]
 * 
 * Revision 4.3.19.2  1995/04/14  21:23:08  John_Dustin
 * 	added DART hooks: new mbuf flags and new protocolSum in mbuf header
 * 	[1995/04/14  19:05:58  John_Dustin]
 * 
 * Revision 4.3.13.13  1994/07/22  20:55:07  Heather_Gray
 * 	Add mbuf type for multicast route table mbufs.
 * 	[1994/07/20  23:38:19  Heather_Gray]
 * 
 * Revision 4.3.13.12  1994/04/25  19:43:05  Heather_Gray
 * 	Remove unused fields.
 * 	[1994/04/25  18:15:23  Heather_Gray]
 * 
 * Revision 4.3.13.11  1994/02/03  21:57:48  Geraldine_Harter
 * 	Merge with Sterling BL9.  Turns out to be a NOP (merge done in
 * 	revision 4.3.13.10):
 * 	Revision 4.3.17.8  1993/12/15  22:11:58  Thomas_Peterson
 * 	Added forward declarations for struct mbuf & struct m_hdr as
 * 	required for C++.
 * 	[1993/12/09  20:51:08  Thomas_Peterson]
 * 
 * Revision 4.3.13.10  1994/01/07  18:28:28  Thomas_Peterson
 * 	Merged C++ header changes fwd from sterl bl9 to gold bl8
 * 	[1994/01/05  17:21:02  Thomas_Peterson]
 * 
 * Revision 4.3.13.9  1994/01/03  19:27:03  John_Dustin
 * 	define generic context structure (primarily for DLI)
 * 	[1993/12/23  21:12:56  John_Dustin]
 * 
 * Revision 4.3.13.8  1993/12/16  14:43:23  Geraldine_Harter
 * 	Merge with Sterling BL8:
 * 	Revision 4.3.17.7  1993/11/09  15:09:39  Sandeep_Shah
 * 
 * Revision 4.3.17.8  1993/12/15  22:11:58  Thomas_Peterson
 * 	Added forward declarations for struct mbuf & struct m_hdr as
 * 	required for C++.
 * 	[1993/12/09  20:51:08  Thomas_Peterson]
 * 
 * Revision 4.3.13.7  1993/11/09  19:42:13  Geraldine_Harter
 * 	Merge with Sterling BL7:
 * 	Revision 4.3.17.6  1993/10/13  20:04:42  Heather_Gray
 * 	Replace cluster get macros for efficiency and text reduction.
 * 	Clean up comments and unsued structure defs.
 * 	[1993/10/11  21:09:23  Heather_Gray]
 * 
 * 	Add macro and def for 2K byte mbufs.
 * 	[1993/10/04  20:43:01  Heather_Gray]
 * 
 * 	Revision 4.3.17.5  1993/10/08  17:45:45  SJ_Lee
 * 	add <sys/param.h>
 * 	[1993/10/08  17:44:02  SJ_Lee]
 * 
 * 	Revision 4.3.17.4  1993/10/07  16:46:04  SJ_Lee
 * 	mcl_buf size is dependent on NBPG, and shouldn't be hard coded as
 * 	8192, change it to MCLBYTES(currently 8192).
 * 	[1993/09/24  19:26:46  SJ_Lee]
 * 
 * Revision 4.3.17.7  1993/11/09  15:09:39  Sandeep_Shah
 * 	mbclusters.h doesnot exist for alpha now.
 * 	[1993/11/09  14:34:58  Sandeep_Shah]
 * 
 * Revision 4.3.13.6  1993/10/07  21:59:45  Geraldine_Harter
 * 	Merge with Sterling BL6.  For completeness, all revision logs follow.
 * 	Note that some of the changes have been made prior to this merge:
 * 
 * 	add MLENGTH() macro
 * 	[1993/08/31  13:34:39  John_Dustin]
 * 
 * 	Revision 4.3.17.2  1993/07/31  18:49:25  Heather_Gray
 * 	Change mh_type, mh_flags from short to int, and m_mtypes
 * 	from u_short to u_int per Vasu for LADDIS performance.
 * 	Reduce MT_MAX from 32 to 20.
 * 	[1993/07/31  18:42:17  Heather_Gray]
 * 
 * 	Remove extern of nmbclusters.
 * 	[1993/07/29  19:35:04  Heather_Gray]
 * 
 * 	Use OSF 1.2 general memory allocator.
 * 	[1993/07/28  15:57:39  Heather_Gray]
 * 
 * Revision 4.3.13.5  1993/09/10  18:27:20  Geraldine_Harter
 * 	Merge with Sterling BL5 & selected OSF1.2 changes
 * 	(needed for mbuf alloc premerge).
 * 	[1993/09/09  20:58:33  Geraldine_Harter]
 * 
 * Revision 4.3.13.4  1993/08/26  14:31:52  Timothy_Burke
 * 	Merge a single delta from sterling into gold.
 * 	Revision 4.3.11.2  1993/02/15  15:04:06  Chet_Juszczak
 * 	Add M_FASTFREE define for m_flags.
 * 	[93/02/15  13:42:18  Chet_Juszczak]
 * 
 * Revision 4.3.13.3  1993/08/03  16:36:01  Ajay_Kachrani
 * 	Convert n/w locks to new lock stats using LI
 * 	[1993/07/22  19:38:10  Ajay_Kachrani]
 * 
 * Revision 4.3.13.2  1993/06/25  21:19:48  Geraldine_Harter
 * 	Merge selected OSF1.2 changes.
 * 	[1993/06/25  20:36:03  Geraldine_Harter]
 * 
 * Revision 4.3.2.6  1993/02/15  14:46:28  Chet_Juszczak
 * 	Back out last change.
 * 	[93/02/15  13:54:31  Chet_Juszczak]
 * 
 * Revision 4.3.2.4  92/12/09  15:13:20  Heather_Gray
 * 	Conditionalise alpha-only code and clean up comments.
 * 	[92/12/06  22:28:20  Heather_Gray]
 * 
 * Revision 4.3.2.3  92/01/26  20:39:50  Tim_Hoskins
 * 	Alpha support for TCP segment reassembly
 * 	[92/01/26  20:39:07  Tim_Hoskins]
 * 
 * Revision 4.3.2.2  92/01/20  13:36:54  Tim_Hoskins
 * 	Added Alpha support for IP reassembly.
 * 	[92/01/20  13:36:07  Tim_Hoskins]
 * 
 * Revision 4.3  92/01/15  02:11:33  devbld_gsf
 * 	Baselevel alpha_bl002
 * 
 * Revision 4.2.2.3  92/01/11  14:49:22  Tim_Hoskins
 * 	Increased the size of an mbuf (MSIZE) for Alpha due to larger pointers
 * 	[92/01/11  14:48:04  Tim_Hoskins]
 * 
 * Revision 4.2.2.2  91/12/07  16:51:28  Jay_Estabrook
 * 	merge ALPHA with SILVER via ODE
 * 	[91/12/07  16:36:33  Jay_Estabrook]
 * 
 * Revision 4.2  91/09/19  22:58:44  devbld
 * 	Adding ODE Headers
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: mbuf.h,v $ $Revision: 4.3.77.1 $ (DEC) $Date: 2003/09/23 22:01:04 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.2
 */
/*
 * Copyright (C) 1988,1989 Encore Computer Corporation.  All Rights Reserved
 *
 * Property of Encore Computer Corporation.
 * This software is made available solely pursuant to the terms of
 * a software license agreement which governs its use. Unauthorized
 * duplication, distribution or sale are strictly prohibited.
 *
 */
/*
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	Base:	mbuf.h	7.12 (Berkeley) 9/4/89
 *	Merged: mbuf.h	7.13 (Berkeley) 6/28/90
 */

#ifndef	_SYS_MBUF_H_
#define	_SYS_MBUF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/param.h>
#include <sys/malloc.h>
#ifdef	_KERNEL
#include <kern/thread.h>
#include <kern/sched_prim.h>

#ifndef	_NET_GLOBALS_H_
#include "net/net_globals.h"
#endif
#ifndef	NET_MALLOC
#include "net/net_malloc.h"
#endif
#endif

#if	!defined(MCLBYTES)
/* Compat for now */
#ifndef __VMS
#ifdef __arch32__
#define	MSIZE		128	/* size of an mbuf */
#else /* __arch32__ */
#define	MSIZE		256	/* size of an mbuf */
#endif /* __arch32__ */
#else /* __VMS */
#define	MSIZE		512	/* size of an mbuf */
#endif /* __VMS */
#define MCLBYTES	CLBYTES
#define MCL2KBYTES	2048
#define MAPPED_MBUFS	/* safe */
#endif /* !defined(MCLBYTES) */
#if defined(_KERNEL) && !defined(NMBCLUSTERS) && !defined(__digital__)
#include <mbclusters.h>
#endif

/*
 * Mbufs are of a single size, MSIZE, which includes overhead.  
 * An mbuf may add a single "mbuf cluster" of size MCLBYTES (from CLBYTES 
 * in sys/param.h), which has no additional overhead and is used instead 
 * of the internal data area; this is usually done when
 * at least MINCLSIZE of data must be stored.
 */

#ifndef __VMS
#define	MLEN		(MSIZE - sizeof(struct m_hdr))	/* normal data len */
#else /* __VMS */
#define	MLEN		(MSIZE - sizeof(struct m_hdr) - sizeof(DCBE))	/* normal data len */
#endif	/* __VMS */
#define	MHLEN		(MLEN - sizeof(struct pkthdr))	/* data len w/pkthdr */
#ifdef __VMS
#define	MEXT_LEN	(MHLEN - sizeof(m_ext_t))	/* data len w/pkthdr and w/exthdr */
#endif	/* __VMS */

#define	MINCLSIZE	(MHLEN + MLEN)	/* smallest amount to put in cluster */
#define	M_MAXCOMPRESS	(MHLEN / 2)	/* max amount to copy for compression */
#define MLENGTH(m)	((m)->m_flags & M_PKTHDR ? (m)->m_pkthdr.len : m_length(m))

/* forward declarations as required for C++ */
#ifdef __cplusplus
struct mbuf;
struct m_hdr;
#endif

#include <sys/secdefines.h>
#if SEC_NET
#       undef MMINOFF
#       define MMINOFF  24
/* For debugging we use a function call to allow us to trap MGET calls */
#	define TNSMM_CLEAR_ATTR(m) m->m_attr = (struct mbuf*)0
#       define TNSMM_FREE_ATTR(m) \
          if ((m)->m_attr != (struct mbuf *)0) {\
                (void)tnsmm_free_attr(m);\
                }
#else
#       define TNSMM_CLEAR_ATTR(m)
#       define TNSMM_FREE_ATTR(m)
#endif

/*
 * Macros for type conversion
 * mtod(m,t) -	convert mbuf pointer to data pointer of correct type
 * dtom(x) -	convert data pointer within mbuf to mbuf pointer (XXX)
 */
#define mtod(m,t)	((t)((m)->m_data))
#define	dtom(x)		((struct mbuf *)((u_long)(x) & ~(MSIZE-1)))

/* header at beginning of each mbuf: */
struct m_hdr {
	struct	mbuf *mh_next;		/* next buffer in chain */
	struct	mbuf *mh_nextpkt;	/* next chain in queue/record */
	caddr_t	mh_data;		/* location of data */
	int	mh_len;			/* amount of data in this mbuf */
	int	mh_type;		/* type of data in this mbuf */
	int	mh_flags;		/* flags; see below */
#if !defined(__arch32__)
	union {
		caddr_t	*mun1_ipq[4];	/* ipasfrag chain pointers */
		caddr_t	*mun1_ihp[4];	/* protocol sequence chain */
#ifdef M_CTX_T
		m_ctx_t	*mun1_ctx[4];	/* generic context structure */
#endif
	} mh_un1;
#define	m_ipq		m_hdr.mh_un1.mun1_ipq
#define	m_ihp		m_hdr.mh_un1.mun1_ihp
#ifdef M_CTX_T
#define	m_ctx		m_hdr.mh_un1.mun1_ctx
#endif
#endif
#if SEC_NET
        struct mbuf *mh_attr;            /* mbuf chain security attributes */
#endif
#ifdef __VMS
	caddr_t	mh_ovms_mbag;		/* ptr to OPENVMS buffer allocation group struct */
	caddr_t	mh_ovms_inetkvci;	/* ptr to OPENVMS Kernel VCI structure, if any. */
	caddr_t	mh_ovms_allocator_pc;	/* ptr to routine return PC of where mbuf allocated */
	int	mh_ovms_previous_type;	/* previous type of this mbuf, filled in by INET$M_FREE */
#endif /* __VMS */
};

/* record/packet header in first mbuf of chain; valid if M_PKTHDR set */
struct	pkthdr {
	int	len;		/* total packet length */
	int	protocolSum;	/* DART: rcv: TCP/UDP checksum from hardware */
	struct	ifnet *rcvif;	/* rcv interface */
};

/* description of external storage mapped into mbuf, valid if M_EXT set */
struct m_ext {
	caddr_t	ext_buf;		/* start of buffer */
#if	__STDC__ || defined(__cplusplus)
#ifndef __VMS
	void	(*ext_free)(caddr_t, u_long, caddr_t);
#else /* __VMS */
	void	(*ext_free)(caddr_t, u_long, caddr_t, void (*)());
#endif /* __VMS */
#else
	void	(*ext_free)();		/* free routine if not the usual */
#endif
	u_int	ext_size;		/* size of buffer, for ext_free */
	caddr_t	ext_arg;		/* additional ext_free argument */
	struct	ext_refq {		/* reference list */
		struct ext_refq *forw, *back;
	} ext_ref;
	int	(*uiomove_f)();	/* DART: copy routine if M_UIOMOVE */
	int	protocolSum;	/* DART: xmt: TCP/UDP checksum from hardware */
	int	bytesSummed;	/* DART: */
	unsigned short	(*checksum)();  /* external checksum routine */
#ifdef __VMS
	void	(*ext_ovms_free)(caddr_t);	/* OVMS kernel client callback routine. */
	struct	ext_refq ext_ovms_dummy_ref; 	/* dummy reference list */
#endif	/* __VMS */
};

#ifdef __VMS
typedef struct m_ext m_ext_t;
struct m_ovms_superset_ext {
	struct m_ext ovms_ext;
	union {
	    char ext_ovms_dat[MEXT_LEN];
	    struct {
		int	pad_a[5];			/* pad to 64 byte boundary. */
		char	ext_ovms_tcpip_krp[100];	/* Space for a TCPIP_KRP structure. */
	    } EXT_ovms_tcpip_krp;
	} EXT_ovms_dat;
};
#endif	/* __VMS */

struct mbuf {
	struct	m_hdr m_hdr;
	union {
		struct {
			struct	pkthdr MH_pkthdr;	/* M_PKTHDR set */
			union {
				struct	m_ext MH_ext;	/* M_EXT set */
#ifdef __VMS
				struct m_ovms_superset_ext MH_ovms_ext;
#endif /* __VMS */
				char	MH_databuf[MHLEN];
			} MH_dat;
		} MH;
		char	M_databuf[MLEN];		/* !M_PKTHDR, !M_EXT */
	} M_dat;
#ifdef __VMS
	DCBE	m_ovms_dcbe;				/* space for VMS DCBE */
#endif	/* __VMS */
};
typedef struct mbuf mbuf_t;

#if SEC_NET
#define m_ifp           M_dat.MH.MH_pkthdr.rcvif
#endif /*SEC_NET*/
#ifdef INTSERV
#define m_rhandle	M_dat.MH.MH_pkthdr.rcvif
#endif
                                                       
#define m_attr          m_hdr.mh_attr
#define	m_next		m_hdr.mh_next
#define	m_len		m_hdr.mh_len
#define	m_data		m_hdr.mh_data
#define	m_type		m_hdr.mh_type
#define	m_flags		m_hdr.mh_flags
#define	m_nextpkt	m_hdr.mh_nextpkt
#define	m_act		m_nextpkt
#define	m_pkthdr	M_dat.MH.MH_pkthdr
#define	m_ext		M_dat.MH.MH_dat.MH_ext
#define	m_pktdat	M_dat.MH.MH_dat.MH_databuf
#define	m_dat		M_dat.M_databuf

#ifdef __VMS
#define	m_ovms_mbag	 m_hdr.mh_ovms_mbag
#define	m_ovms_inetkvci	 m_hdr.mh_ovms_inetkvci
#define	m_ovms_allocator_pc	m_hdr.mh_ovms_allocator_pc
#define	m_ovms_previous_type	m_hdr.mh_ovms_previous_type
#define	m_ext_ovms_dat		M_dat.MH.MH_dat.MH_ovms_ext.EXT_ovms_dat.ext_ovms_dat
#define m_ext_ovms_tcpip_krp	M_dat.MH.MH_dat.MH_ovms_ext.EXT_ovms_dat.EXT_ovms_tcpip_krp.ext_ovms_tcpip_krp
#endif /* __VMS */

/* mbuf flags */
#define	M_EXT		0x0001	/* has associated external storage */
#define	M_PKTHDR	0x0002	/* start of record */
#define	M_EOR		0x0004	/* end of record */
#define	M_FASTFREE	0x0008	/* free external storage asap */
#define M_UIOMOVE	0x0010	/* DART: m_ext.uiomove_f is valid */
#define M_HDRRSVD	0x0020	/* DART: ATOMIC_FRAG_NETIO */

/* mbuf pkthdr flags, also in m_flags */
#define	M_BCAST		0x0100	/* send/received as link-level broadcast */
#define	M_MCAST		0x0200	/* send/received as link-level multicast */
#define	M_WCARD		0x0400	/* received as network-level broadcast */
#define M_PROTOCOL_SUM	0x0800	/* DART: protocolSum is valid */
#define M_ATM_CLP	0x1000	/* ATM: do Congestion Loss Priority on packet */
#define M_REQUE_OK	0x2000	/* OK for drivers to reque failed transmits */ 
#define M_REQUED_ONCE	0x4000	/* Driver re-queued a failed transmit (once) */ 
#define M_PROXY		0x8000	/* Firewall: proxy on localhost */
#define	M_ALIAS	       0x10000  /* received as cluster alias packet */
#define M_RHANDLE      0x20000	/* RSVP: rcvif in pkthdr misused as rhandle */
#define M_CHECKSUM	0x40000	/* External Checksum Routine valid */
#define M_IPPREPROCESS	0x80000	/* ip preprocess run on mbuf. mutually exclusive with M_PROTOCOL_SUM */
#define M_NOCHECKSUM	0x100000 /* No checksum required */
#define M_INPUT_PROCESSING_DONE		0x200000 /* packet already thru ip */
						 /* input processing */
#define M_IPSEC_INPUT_DONE	M_INPUT_PROCESSING_DONE /* backwards compat */
#define M_OUTPUT_PROCESSING_DONE	0x400000 /* packet already thru ip */
						 /* output processing */
#define M_IPSEC_OUTPUT_DONE	M_OUTPUT_PROCESSING_DONE /* backwards compat */
#define M_IPSEC_UDP_SEND_FP	0x800000 /* packet sent from udp fastpath */
#define M_IFLLINFO	0x1000000 /* ifllinfo has been provided */
#define M_IPSEC_AUTH	0x2000000 /* IPsec auth has been performed */

/* does mbuf hold a broadcast packet? */
#define m_broadcast(m)	((m)->m_flags & (M_BCAST|M_MCAST|M_WCARD))

/* flags copied when copying m_pkthdr */
#define	M_COPYFLAGS	(M_PKTHDR|M_EOR|M_BCAST|M_MCAST|M_WCARD|M_PROTOCOL_SUM|M_PROXY|M_RHANDLE|M_CHECKSUM| \
			 M_ALIAS|M_NOCHECKSUM)

/* These flags should be cleared before reusing an mbuf that has already
 * been through the IP input or output path. */
#define M_DONE_FLAGS	(M_INPUT_PROCESSING_DONE|M_OUTPUT_PROCESSING_DONE)

/* mbuf types */
#define	MT_FREE		M_FREE		/* should be on free list */
#define	MT_DATA		M_MBUF		/* dynamic (data) allocation */ 
#define	MT_HEADER	M_HEADER	/* packet header */
#define	MT_SOCKET	M_SOCKET	/* socket structure */
#define	MT_PCB		M_PCB		/* protocol control block */
#define	MT_RTABLE	M_RTABLE	/* routing tables */
#define	MT_HTABLE	M_HTABLE	/* IMP host tables */
#define	MT_ATABLE	M_ATABLE	/* address resolution tables */
#define	MT_SONAME	M_SONAME	/* socket name */
#define	MT_MRTABLE	M_MRTABLE	/* multicast route tables */
#define	MT_SOOPTS	M_SOOPTS	/* socket options */
#define	MT_FTABLE	M_FTABLE	/* fragment reassembly header */
#define	MT_RIGHTS	M_RIGHTS	/* access rights */
#define	MT_IFADDR	M_IFADDR	/* interface address */
#define MT_CONTROL	M_CONTROL	/* extra-data protocol message */
#define MT_OOBDATA	M_OOBDATA	/* expedited data */
#define MT_MAX		16		/* for backwards compatibility */

/* flags to m_get/MGET */
#define	M_DONTWAIT	M_NOWAIT
#define	M_WAIT		M_WAITOK
/*
 * flag to m_copym
 */
#define M_IGNOREEND	0x1000

/*
 * mbuf allocation/deallocation macros:
 *
 *	MGET(struct mbuf *m, int how, int type)
 * allocates an mbuf and initializes it to contain internal data.
 *
 *	MGETHDR(struct mbuf *m, int how, int type)
 * allocates an mbuf and initializes it to contain a packet header
 * and internal data.
 */

#ifndef __VMS
#define MGETMEM(m, type, how)  \
	MALLOC((m), struct mbuf *, MSIZE, (type), (how))
#else /* __VMS */
#define MGETMEM(m, type, how) \
	(m) = (struct mbuf *)inet$m_get((how), (type))
#endif /* __VMS */

#define	MGET(m, how, type) { \
	MGETMEM(m, type, how); \
	if (m) { \
		(m)->m_next = (m)->m_nextpkt = 0; \
		(m)->m_type = (type); \
		(m)->m_data = (m)->m_dat; \
		(m)->m_flags = 0; \
		TNSMM_CLEAR_ATTR(m); \
	} else \
		(m) = m_retry((how), (type)); \
}

#define	MGETHDR(m, how, type) { \
	MGETMEM(m, type, how); \
	if (m) { \
		(m)->m_next = (m)->m_nextpkt = 0; \
		(m)->m_type = (type); \
		(m)->m_data = (m)->m_pktdat; \
		(m)->m_flags = M_PKTHDR; \
		TNSMM_CLEAR_ATTR(m); \
	} else \
		(m) = m_retryhdr((how), (type)); \
}

/*
 * Mbuf cluster macros.
 * MCLALLOC(caddr_t p, int how) allocates an mbuf cluster.
 * MCLGET adds such clusters to a normal mbuf;
 * the flag M_EXT is set upon success.
 * MCLFREE unconditionally frees a cluster allocated by MCLALLOC.
 */

#define	MCLALLOC(p, how) \
	  p = m_clalloc(1, (how));

#define	MCLFREE(p) { \
	FREE((p), M_CLUSTER); \
}

#define	MCLGET(m, how) { \
	(void) m_clalloc8((m), (how)); \
}

#define	MCLGET2(m, how) { \
	(void) m_clalloc2((m), (how)); \
}

#define MCLREFERENCED(m) \
	((m)->m_ext.ext_ref.forw != &((m)->m_ext.ext_ref))

/*
 * MFREE(struct mbuf *m, struct mbuf *n)
 * Free a single mbuf and associated external storage.
 * Place the successor, if any, in n.
 */
#define	MFREE(m, n) \
	((n) = m_free(m))

/*
 * Copy mbuf pkthdr from from to to.
 * from must have M_PKTHDR set, and to must be empty.
 */
#define	M_COPY_PKTHDR(to, from) { \
	(to)->m_pkthdr = (from)->m_pkthdr; \
	(to)->m_flags = (from)->m_flags & M_COPYFLAGS; \
	(to)->m_data = (to)->m_pktdat; \
}

/*
 * Set the m_data pointer of a newly-allocated mbuf (m_get/MGET) to place
 * an object of the specified size at the aligned end of the mbuf.
 */
#define	M_ALIGN(m, len) { \
	(m)->m_data += (MLEN - (len)) &~ (sizeof(long) - 1); \
}
/*
 * As above, for mbufs allocated with m_gethdr/MGETHDR
 * or initialized by M_COPY_PKTHDR.
 */
#define	MH_ALIGN(m, len) { \
	(m)->m_data += (MHLEN - (len)) &~ (sizeof(long) - 1); \
}

/*
 * Compute the amount of space available
 * before the current start of data in an mbuf.
 * Subroutine - data not available if certain references.
 */
#define	M_LEADINGSPACE(m)	m_leadingspace(m)

/*
 * Compute the amount of space available
 * after the end of data in an mbuf.
 * Subroutine - data not available if certain references.
 */
#define	M_TRAILINGSPACE(m)	m_trailingspace(m)

/*
 * Arrange to prepend space of size plen to mbuf m.
 * If a new mbuf must be allocated, how specifies whether to wait.
 * If how is M_DONTWAIT and allocation fails, the original mbuf chain
 * is freed and m is set to NULL.
 */
#define	M_PREPEND(m, plen, how) { \
	if (M_LEADINGSPACE(m) >= (plen)) { \
		(m)->m_data -= (plen); \
		(m)->m_len += (plen); \
	} else \
		(m) = m_prepend((m), (plen), (how)); \
	if ((m) && (m)->m_flags & M_PKTHDR) \
		(m)->m_pkthdr.len += (plen); \
}

/* change mbuf to new type */
/* Note: this may cause malloc() mbuf type stats to be inaccurate */
#define MCHTYPE(m, t) { \
	(m)->m_type = (t);\
}

/* length to m_copy to copy all */
#define	M_COPYALL	1000000000

/* compatiblity with 4.3 */
#define  m_copy(m, o, l)	m_copym((m), (o), (l), M_DONTWAIT)

/*
 * Mbuf statistics.
 */
struct mbstat {
	u_long	m_mbufs;	/* obsolete: tracked by malloc M_MBUF stats */
	u_long	m_clusters;	/* obsolete: tracked by malloc M_CLUSTER stats*/
	u_long	m_drops;	/* times failed to find space */
	u_long	m_drain;	/* times drained protocols for space */
#ifndef __VMS
	u_int	m_mtypes[MT_MAX];	/* obsolete: tracked by MALLOC(type) stats */
#else	/* __VMS */
	u_int	m_mtypes[M_LAST];	/* OPENVMS tracks these stats */
#endif /* __VMS */
};

#ifdef	_KERNEL
#if	NETSYNC_LOCK
extern	simple_lock_data_t mbuf_slock;
#define MBUF_LOCKINIT()	simple_lock_setup(&mbuf_slock,mbuf_sli)
#define MBUF_LOCK()	simple_lock(&mbuf_slock)
#define MBUF_UNLOCK()	simple_unlock(&mbuf_slock)

#define MBUF_EXT_LOCK_SHIFT  24
extern simple_lock_data_t      *mbuf_ext_slock;
extern unsigned int 		mbuf_ext_lock_mask;
#define MBUF_EXT_LOCK_ADDR(m) \
        	(mbuf_ext_slock +    \
         	(((unsigned)(m) >> MBUF_EXT_LOCK_SHIFT) & mbuf_ext_lock_mask))

#define MBUF_EXT_LOCK(m) simple_lock(MBUF_EXT_LOCK_ADDR(m))
#define MBUF_EXT_UNLOCK(m) simple_unlock(MBUF_EXT_LOCK_ADDR(m))
#if	!VAGUE_STATS
#define MBSTAT(x)	do { spl_t _ns = splimp(); MBUF_LOCK(); \
			  x; MBUF_UNLOCK(); splx(_ns); } while (0)
#else	/* !VAGUE_STATS */
#define MBSTAT(x)	x
#endif  /* !VAGUE_STATS */
#else	/* NETSYNC_LOCK */
#define MBUF_LOCKINIT()
#define MBUF_LOCK()
#define MBUF_UNLOCK()
#define MBUF_EXT_LOCK(m) 
#define MBUF_EXT_UNLOCK(m)
#define MBSTAT(x)	x
#endif	/* NETSYNC_LOCK */
extern struct	mbstat mbstat;		/* statistics */
extern REPLICATED int	max_linkhdr;	/* largest link-level header */
extern REPLICATED int	max_protohdr;	/* largest protocol header */
extern int	max_hdr;		/* largest link+protocol header */
extern int	max_datalen;		/* MHLEN - max_hdr */
extern int	mclbytes;		/* variable version of MCLBYTES */
/*
 * Align (x) on a word boundary.
 */
#define HDRALIGN(x)	(((x)+sizeof(u_long)-1) & ~(sizeof(u_long)-1))
#endif
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
