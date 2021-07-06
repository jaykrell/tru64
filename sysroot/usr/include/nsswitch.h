/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: nsswitch.h,v $
 * Revision 1.1.4.1  2003/06/10  18:55:31  Spider_Boardman
 * 	Re-arranged one missed in previous.  Changing name to 'expose'
 * 	nsdispatch() a la NetBSD.
 * 	Also removed the _NS_PRIVATE clause, since the code's all been
 * 	cleaned up not to use it.
 * 	[2003/04/17  00:09:47  Spider_Boardman]
 *
 * 	Re-arranged some fields to account for (current) reality.
 * 	[2003/04/16  15:38:38  Spider_Boardman]
 *
 * 	Added __ns_db_position().
 * 	[2003/04/03  22:04:15  Spider_Boardman]
 *
 * 	Add __ns_last_lookup() and its valid arguments.
 * 	[2003/03/28  21:23:46  Spider_Boardman]
 *
 * 	Import name service switch support from NetBSD v1.6.
 * 	[2003/03/19  18:03:13  Spider_Boardman]
 *
 * $EndLog$
 */
/*
 * @(#)$RCSfile: nsswitch.h,v $ $Revision: 1.1.4.1 $ (DEC) $Date: 2003/06/10 18:55:31 $
 */
/*	$NetBSD: nsswitch.h,v 1.11 2000/12/20 20:47:55 christos Exp $	*/

/*-
 * Copyright (c) 1997, 1998, 1999 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Luke Mewburn.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *        This product includes software developed by the NetBSD
 *        Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _NSSWITCH_H
#define _NSSWITCH_H	1

/*
 * Don't use va_list in prototypes.   Va_list is typedef'd in two places
 * (<machine/varargs.h> and <machine/stdarg.h>), so if we include one of
 * them here we may collide with the utility's includes.  It's unreasonable
 * for utilities to have to include one of them to include nsswitch.h, so
 * we get _BSD_VA_LIST_ from <machine/ansi.h> and use it.
 */
/*
 * The above was only for NetBSD, not Tru64 UNIX.  We get our va_list
 * definition from our inclusion of stdio.h, which already has deep-dark
 * magic to get it right.
 */

#include <standards.h>

_BEGIN_CPLUSPLUS

#include <stdio.h>
#include <sys/bitypes.h>

#ifndef _PATH_NS_CONF
#define _PATH_NS_CONF	"/etc/nsswitch.conf"
#endif

#define	NS_CONTINUE	0
#define	NS_RETURN	1

#define	NS_SUCCESS	(1<<0)		/* entry was found */
#define	NS_UNAVAIL	(1<<1)		/* source not responding, or corrupt */
#define	NS_NOTFOUND	(1<<2)		/* source responded 'no such entry' */
#define	NS_TRYAGAIN	(1<<3)		/* source busy, may respond to retrys */
#define	NS_STATUSMASK	0x000000ff	/* bitmask to get the status flags */

/*
 * currently implemented sources
 */
#define NSSRC_FILES	"files"		/* local files */
#define	NSSRC_DNS	"dns"		/* DNS; IN for hosts, HS for others */
#define	NSSRC_NIS	"nis"		/* YP/NIS */
#define	NSSRC_COMPAT	"compat"	/* passwd,group in YP compat mode */
#define NSSRC_MAX       20              /* maximum number of data sources */

/*
 * currently implemented databases
 */
#define NSDB_GROUP		"group"
#define NSDB_GROUP_COMPAT	"group_compat"
#define NSDB_HOSTS		"hosts"
#define NSDB_NETGROUP		"netgroup"
#define NSDB_NETWORKS		"networks"
#define NSDB_PASSWD		"passwd"
#define NSDB_PASSWD_COMPAT	"passwd_compat"
#define NSDB_PROTOCOLS		"protocols"
#define NSDB_RPC		"rpc"
#define NSDB_SERVICES		"services"

/*
 * suggested databases to implement
 */
#define NSDB_ALIASES		"aliases"
#define NSDB_AUTH		"auth"
#define NSDB_AUTOMOUNT		"automount"
#define NSDB_BOOTPARAMS		"bootparams"
#define NSDB_ETHERS		"ethers"
#define NSDB_EXPORTS		"exports"
#define NSDB_NETMASKS		"netmasks"
#define NSDB_PHONES		"phones"
#define NSDB_PRINTCAP		"printcap"
#define NSDB_REMOTE		"remote"
#define NSDB_SENDMAILVARS	"sendmailvars"
#define NSDB_SHELLS		"shells"
#define NSDB_TERMCAP		"termcap"
#define NSDB_TTYS		"ttys"

/*
 * ns_dtab - `nsswitch dispatch table'
 * contains an entry for each source and the appropriate function to call
 */
typedef struct {
    const char *src;
    int	(*callback) (void *retval, void *cb_data, va_list ap);
    void *cb_data;
} ns_dtab;

/*
 * macros to help build an ns_dtab[]
 */
#define NS_FILES_CB(F,C)	{ NSSRC_FILES,	F,	C }
#define NS_COMPAT_CB(F,C)	{ NSSRC_COMPAT,	F,	C }
#define NS_DNS_CB(F,C)	        { NSSRC_DNS,	F,	C }
#define NS_NIS_CB(F,C)	        { NSSRC_NIS,	F,	C }


/*
 * ns_src - `nsswitch source'
 * used by the nsparser routines to store a mapping between a source
 * and its dispatch control flags for a given database.
 */
typedef struct {
    const char *name;
    u_int32_t flags;
} ns_src;


/*
 * default sourcelist (if nsswitch.conf is missing, corrupt,
 * or the requested database doesn't have an entry.
 */
extern const ns_src __nsdefaultsrc[];


int nsdispatch(void *, const ns_dtab [], const char *, const char *, 
	       const ns_src [], ...);


/* types of "last lookup" to provide */
#define	NSLAST_ANY	0	/* most-recent of any kind */
#define	NSLAST_INCOMPAT	1	/* most-recent that wasn't "compat" */

const char *__ns_last_lookup(int);

/*
 * What 'position' am I in my NSDB's search order?
 * Called with NSDB name, NSSRC name, default number.
 * Returns new number if anything non-default has been loaded,
 * or the default number if not.
 * Returns -1 on invalid parameters, with errno == EINVAL.
 * Returns -1 with errno == 0 if the given source is not in use.
 */

int __ns_db_position(const char *, const char *, int);


_END_CPLUSPLUS

#endif /* !_NSSWITCH_H */

