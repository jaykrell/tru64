/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: svcinfo.h,v $
 * Revision 4.3.9.1  2003/06/10  18:55:01  Spider_Boardman
 * 	Add obsolescence warning for nsswitch support.
 * 	Should probably also remove second copyright block (below), but I'll
 * 	leave that decision to someone else.
 *
 * Revision 4.3.7.4  1999/02/09  19:03:55  Ken_Block
 * 	Make header C++ compliant.
 * 	[1998/12/29  20:23:52  Ken_Block]
 *
 * Revision 4.3.7.3  1998/02/23  17:47:43  John_Ferlan
 * 	Increase the maximum password length to 80 - QAR 42723
 * 	[1998/02/06  17:47:09  John_Ferlan]
 * 
 * Revision 4.3.7.2  1996/12/09  22:01:37  Neil_Lewis
 * 	Add prototypes for reentrant forms of functions.
 * 	[1996/11/19  17:27:08  Neil_Lewis]
 * 
 * 	Eliminate compiler warnings when compiled with -warnprotos.
 * 	[1996/11/12  16:15:57  Neil_Lewis]
 * 
 * Revision 4.3.5.2  1995/06/30  22:40:54  Mike_Milicia
 * 	Add MLS secure networking hooks.
 * 	[1995/06/20  22:19:50  Mike_Milicia]
 * 
 * Revision 4.3.3.2  1993/07/15  18:52:38  SJ_Lee
 * 	add #ifndef _SYS_SVCINFO_H_ to avoid multiple inclusion.
 * 	[1993/07/14  19:46:49  SJ_Lee]
 * 
 * Revision 4.3  1992/01/15  02:12:31  devbld_gsf
 * 	Baselevel alpha_bl002
 * 
 * Revision 4.2.2.2  91/12/11  14:37:12  David_Snow
 * 	"Jump over B65"
 * 
 * Revision 4.2.1.2  91/12/11  13:38:12  David_Snow
 * 	jump around old B65 rev
 * 
 * Revision 4.2  91/09/19  23:04:25  devbld
 * 	Adding ODE Headers
 * 
 * $EndLog$
 */
/*
 *      @(#)$RCSfile: svcinfo.h,v $ $Revision: 4.3.9.1 $ (DEC) $Date: 2003/06/10 18:55:01 $
 */
/*
 */

/*
 * WARNING:
 * This file describes interfaces where are now obsolete.  Please see
 * the nsswitch.conf(4) and nsdispatch(3) reference pages for the
 * replacements.
 */

/************************************************************************
 *                                                                      *
 *                      Copyright (c) 1989 by                           *
 *              Digital Equipment Corporation, Maynard, MA              *
 *                      All rights reserved.                            *
 *                                                                      *
 *   This software is furnished under a license and may be used and     *
 *   copied  only  in accordance with the terms of such license and     *
 *   with the  inclusion  of  the  above  copyright  notice.   This     *
 *   software  or  any  other copies thereof may not be provided or     *
 *   otherwise made available to any other person.  No title to and     *
 *   ownership of the software is hereby transferred.                   *
 *                                                                      *
 *   This software is  derived  from  software  received  from  the     *
 *   University    of   California,   Berkeley,   and   from   Bell     *
 *   Laboratories.  Use, duplication, or disclosure is  subject  to     *
 *   restrictions  under  license  agreements  with  University  of     *
 *   California and with AT&T.                                          *
 *                                                                      *
 *   The information in this software is subject to change  without     *
 *   notice  and should not be construed as a commitment by Digital     *
 *   Equipment Corporation.                                             *
 *                                                                      *
 *   Digital assumes no responsibility for the use  or  reliability     *
 *   of its software on equipment which is not supplied by Digital.     *
 *                                                                      *
 ************************************************************************/

#ifndef _SYS_SVCINFO_H_
#define _SYS_SVCINFO_H_

#ifdef __cplusplus
extern "C" {
#endif

#define SVC_CONF "/etc/svc.conf"

/* databases indeces for svcadmin and svcpath in svcinfo*/
#define SVC_ALIASES 0
#define SVC_AUTH 1
#define SVC_GROUP 2
#define SVC_HOSTS 3
#define SVC_NETGROUP 4 
#define SVC_NETWORKS 5
#define SVC_PASSWD 6
#define SVC_PROTOCOLS 7
#define SVC_RPC 8
#define SVC_SERVICES 9

/* Equate TNETRHDB and protected passwords
 * to HOSTS and PASSWD respectively.
 */
#define SVC_RHDB SVC_HOSTS
#define SVC_PRPASSWD SVC_PASSWD

#define SVC_DATABASES 20
#define SVC_PATHSIZE 8

/* sources stored in array svcpath*/
#define SVC_LOCAL 0
#define SVC_YP 1
#define SVC_BIND 2
#define SVC_LAST 99

/* values for seclevel */
#define SEC_BSD 0
#define SEC_UPGRADE 1
#define SEC_ENHANCED 22

#define MAX_PASSWORD_LENGTH 80

extern int svc_lastlookup;
struct svcinfo {
        int svcdate;            /* Last mod date of /etc/svc.conf */


	int	svcpath[SVC_DATABASES][SVC_PATHSIZE]; /* indexed by databases
						 and choice 0=first choice
						 1=second choice, etc
						 value stored is source */

	struct  {
		int passlenmin;
		int passlenmax;
		int softexp;
		int seclevel;
	} svcauth;

};

#ifdef _NO_PROTO
extern struct svcinfo * getsvc();
extern struct svcinfo * getsvc_last();
extern int init_svc();
#if defined(_REENTRANT) || defined(_THREAD_SAFE)
extern init_svc_r();
extern int getsvc_r();
#endif  /* _REENTRANT || _THREAD_SAFE */
#else
extern struct svcinfo * getsvc(void);
extern struct svcinfo * getsvc_last(void);
extern int init_svc(void);
#if defined(_REENTRANT) || defined(_THREAD_SAFE)
struct stat;
extern init_svc_r(struct svcinfo *, struct stat *);
extern int getsvc_r(struct svcinfo *);
#endif  /* _REENTRANT || _THREAD_SAFE */
#endif


/**********  /etc/svc.conf file format **************/
/*
NOTE: white space allowed only after commas or newlines

database=service,
	service,
	service

database=service,service,service

PASSLENMIN=6
PASSLENMAX=80
SOFTEXP=604800
SECLEVEL=ENHANCED        (BSD | UPGRADE | ENHANCED)


database = aliases | auth | group | hosts | netgroup | networks |
	  passwd | protocols | rpc | services
source =  local | yp | bind

*/
/*
 * getsvc() libc routines
 *
 * #include <sys/svcinfo.h>
 *
 * struct svcinfo * getsvc()
 * int init_svc()
 *
 * getsvc() returns a pointer to the svcinfo structure.
 * If there is no svcinfo structure, then the /etc/svc.conf file
 * is parsed.  On failure getsvc() returns 0.
 */

#ifdef __cplusplus
}
#endif

#endif
