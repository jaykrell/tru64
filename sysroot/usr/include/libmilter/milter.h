/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: milter.h,v $
 * Revision 1.1.2.1  2006/07/18  11:15:29  Sunilkumar_Mummigatti
 * 	New for sendmail.v8.13.6
 *
 * $EndLog$
 */
/*
 * @(#)$RCSfile: milter.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2006/07/18 11:15:29 $
 */
/*
 * Copyright (c) 1999-2003 Sendmail, Inc. and its suppliers.
 *	All rights reserved.
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the sendmail distribution.
 *
 *
 *	$Id: milter.h,v 1.1.2.1 2006/07/18 11:15:29 Sunilkumar_Mummigatti Exp $
 */

/*
**  MILTER.H -- Global definitions for mail filter.
*/

#ifndef _LIBMILTER_MILTER_H
# define _LIBMILTER_MILTER_H	1

#include "sendmail.h"
#include "libmilter/mfapi.h"

/* socket and thread portability */
# include <pthread.h>
typedef pthread_t	sthread_t;
typedef int		socket_t;

# define MAX_MACROS_ENTRIES	5	/* max size of macro pointer array */

/*
**  context for milter
**  implementation hint:
**  macros are stored in mac_buf[] as sequence of:
**  macro_name \0 macro_value
**  (just as read from the MTA)
**  mac_ptr is a list of pointers into mac_buf to the beginning of each
**  entry, i.e., macro_name, macro_value, ...
*/

struct smfi_str
{
	sthread_t	ctx_id;		/* thread id */
	socket_t	ctx_sd;		/* socket descriptor */
	int		ctx_dbg;	/* debug level */
	time_t		ctx_timeout;	/* timeout */
	int		ctx_state;	/* state */
	smfiDesc_ptr	ctx_smfi;	/* filter description */
	unsigned long	ctx_pflags;	/* protocol flags */
	char		**ctx_mac_ptr[MAX_MACROS_ENTRIES];
	char		*ctx_mac_buf[MAX_MACROS_ENTRIES];
	char		*ctx_reply;	/* reply code */
	void		*ctx_privdata;	/* private data */
};

#endif /* ! _LIBMILTER_MILTER_H */
