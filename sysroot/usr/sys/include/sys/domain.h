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
 *	@(#)$RCSfile: domain.h,v $ $Revision: 4.2.8.1 $ (DEC) $Date: 2002/01/29 21:19:43 $
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
 * Copyright (c) 1982, 1986 Regents of the University of California.
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
 *	Base:	domain.h	7.3 (Berkeley) 6/27/88
 *	Merged: domain.h	7.4 (Berkeley) 6/28/90
 */

#ifndef	_SYS_DOMAIN_H_
#define _SYS_DOMAIN_H_

/* forward declaration required for C++ */
#ifdef __cplusplus
struct protosw;
#endif

/*
 * Uniprocessor compatibility: allows per-domain funnel operation.
 * Replaces all socket-level spl's, for instance.
 */
struct domain_funnel {
	void (*unfunnel)();		/* unfunnel operation or NULL */
	union {				/* local storage for operation */
		int	spl;			/* previous spl */
		caddr_t	other;			/* recursive lock_t, e.g. */
	} object;
};

#ifndef	CONST
#define CONST
#endif

/*
 * Structure per communications domain.
 */
struct	domain {
	int	dom_family;		/* AF_xxx */
	char	*dom_name;
#ifdef	_KERNEL
	void	(*dom_init)(void);
	int	(*dom_externalize)(struct mbuf *);
	void	(*dom_dispose)(struct mbuf *);
#else
	void	(*dom_init)();		/* initialize domain data structures */
	int	(*dom_externalize)();	/* externalize access rights */
	void	(*dom_dispose)();	/* dispose of internalized rights */
#endif
	struct	protosw CONST *dom_protosw, *dom_protoswNPROTOSW;
	struct	domain *dom_next;
	int	dom_refcnt;		/* # sockets in this domain */
#ifdef	_KERNEL
	void	(*dom_funnel)(struct domain_funnel *);
	void	(*dom_funfrc)(struct domain_funnel *);
#if	NETSYNC_LOCK
	simple_lock_data_t	dom_rc_lock;
#endif
#else
	void	(*dom_funnel)();	/* uniprocessor compat */
	void	(*dom_funfrc)();	/* uniprocessor compat */
#endif
};

#ifdef	_KERNEL
extern	struct domain *domains;
#if	NETSYNC_LOCK
ndecl_lock_data(extern, domain_lock)
ndecl_lock_data(extern, pr_dom_lock)

/* 
 * The domain list is protected by two domain locks.  Protocol-specific
 * locks can exists between the two domain locks in the lock hierarchy.
 * The DOMAIN_READ lock is held when searching the domain list and then 
 * calling domain protocol routines.
 * The PRDOMAIN_READ lock is held to simply search the domain list (but
 * not call protocol domain routines), so it can be acquired with a 
 * protocol-specific lock already held.
 * Both write locks must be taken to update the domain list.
 */
#define DOMAIN_LOCKINIT()	ulock_setup(&domain_lock,domain_li,TRUE)
#define DOMAIN_LOCK_DECL()	NETSPL_DECL(_ds)
#define DOMAIN_READ_LOCK()	{ NETSPL(_ds,net); ulock_read(&domain_lock); }
#define DOMAIN_WRITE_LOCK()	{ NETSPL(_ds,net); ulock_write(&domain_lock); }
#define DOMAIN_READ_UNLOCK()	{ ulock_done(&domain_lock); NETSPLX(_ds); }
#define DOMAIN_WRITE_UNLOCK()	{ ulock_done(&domain_lock); NETSPLX(_ds); }

#define PRDOMAIN_LOCKINIT()	ulock_setup(&pr_dom_lock,pr_dom_li,TRUE)
#define PRDOMAIN_LOCK_DECL()	NETSPL_DECL(_pds)
#define PRDOMAIN_READ_LOCK()	{ NETSPL(_pds,net); ulock_read(&pr_dom_lock); }
#define PRDOMAIN_WRITE_LOCK()	{ NETSPL(_pds,net); ulock_write(&pr_dom_lock); }
#define PRDOMAIN_READ_UNLOCK()	{ ulock_done(&pr_dom_lock); NETSPLX(_pds); }
#define PRDOMAIN_WRITE_UNLOCK()	{ ulock_done(&pr_dom_lock); NETSPLX(_pds); }

#define DOMAINRC_LOCKINIT(dp)	simple_lock_setup(&(dp)->dom_rc_lock,dom_rc_li)
#define DOMAINRC_LOCK(dp)	simple_lock(&(dp)->dom_rc_lock)
#define DOMAINRC_UNLOCK(dp)	simple_unlock(&(dp)->dom_rc_lock)
#else
#define DOMAIN_LOCKINIT()
#define DOMAIN_LOCK_DECL()
#define DOMAIN_READ_LOCK()
#define DOMAIN_WRITE_LOCK()
#define DOMAIN_READ_UNLOCK()
#define DOMAIN_WRITE_UNLOCK()

#define PRDOMAIN_LOCKINIT()
#define PRDOMAIN_LOCK_DECL()
#define PRDOMAIN_READ_LOCK()
#define PRDOMAIN_WRITE_LOCK()
#define PRDOMAIN_READ_UNLOCK()
#define PRDOMAIN_WRITE_UNLOCK()

#define DOMAINRC_LOCKINIT(dp)
#define DOMAINRC_LOCK(dp)
#define DOMAINRC_UNLOCK(dp)
#endif /* NETSYNC_LOCK */

#define	DOMAINRC_REF(dp) \
	{ DOMAINRC_LOCK(dp); (dp)->dom_refcnt++; DOMAINRC_UNLOCK(dp); }

#define	DOMAINRC_UNREF(dp) \
	{ DOMAINRC_LOCK(dp); (dp)->dom_refcnt--; DOMAINRC_UNLOCK(dp); }

#if DOMAIN_FUNNEL_SUPPORT

#define DOMAIN_FUNNEL_DECL(f) \
	struct domain_funnel f;

#define DOMAIN_FUNNEL(dp, f) \
	{ (f).unfunnel = 0; if ((dp)->dom_funnel) (*(dp)->dom_funnel)(&(f)); }

#define DOMAIN_UNFUNNEL(f) \
	{ if ((f).unfunnel) (*(f).unfunnel)(&(f)); }
/* Forced unfunnel is used before sleeping in sosleep() */
#define DOMAIN_UNFUNNEL_FORCE(dp, f) \
	{ (f).unfunnel = 0; \
	  if ((dp)->dom_funfrc) (*(dp)->dom_funfrc)(&(f)); }

#else /* !DOMAIN_FUNNEL_SUPPORT */

#define DOMAIN_FUNNEL_DECL(f)
#define DOMAIN_FUNNEL(dp, f)
#define DOMAIN_UNFUNNEL(f)
#define DOMAIN_UNFUNNEL_FORCE(dp, f)

#endif /* DOMAIN_FUNNEL_SUPPORT */

#endif
#endif
