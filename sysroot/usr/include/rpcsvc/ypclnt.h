/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: ypclnt.h,v $
 * Revision 4.2.14.1  2003/06/10  18:56:09  Spider_Boardman
 * 	Added yp_unbind_soft().
 *
 * Revision 4.2.9.4  1995/06/15  17:38:57  Michael_Daniele
 * 	Fix yp_all function prototype to use callback *.
 * 	[1995/06/14  21:07:11  Michael_Daniele]
 *
 * Revision 4.2.9.3  1995/05/23  13:18:03  Aju_John
 * 	merge of Platinum Lite BL4 changes
 * 	[1995/05/23  12:58:42  Aju_John]
 * 
 * Revision 4.2.10.2  1995/04/24  18:24:38  Spider_Boardman
 * 	Merge in CLD fixes from ptos.
 * 	[1995/04/24  16:35:49  Spider_Boardman]
 * 
 * Revision 4.2.9.2  1995/04/07  19:43:50  Spider_Boardman
 * 	Add __yp_match_flush for QARs 26317,31073,31419.
 * 	[1995/03/29  17:52:17  Spider_Boardman]
 * 
 * Revision 4.2.5.2  1995/03/29  17:52:17  Spider_Boardman
 * 	Add __yp_match_flush for QARs 26317,31073,31419.
 * 
 * Revision 4.2.3.2  1994/03/29  18:53:30  Thomas_Peterson
 * 	Fixes for ANSI & C++
 * 	[1994/03/02  21:24:44  Thomas_Peterson]
 * 
 * Revision 4.2  1991/09/20  05:20:06  devbld
 * 	Adding ODE Headers
 * 
 * $EndLog$
 */
/*
 *     @(#)$RCSfile: ypclnt.h,v $ $Revision: 4.2.14.1 $ (DEC) $Date: 2003/06/10 18:56:09 $ 
 */
/*
 */


/* 
 * Copyright (c) 1988,1990 by Sun Microsystems, Inc.
 *	 1.12 86/12/19 
 */


/*
 * ypclnt.h
 * This defines the symbols used in the c language
 * interface to the NIS client functions.  A description of this interface
 * can be read in ypclnt(3N).
 */

#ifndef _RPCSVC_YPCLNT_H_
#define _RPCSVC_YPCLNT_H_

#include <standards.h>

/*
 * Failure reason codes.  The success condition is indicated by a functional
 * value of "0".
 */
#define YPERR_BADARGS 1			/* Args to function are bad */
#define YPERR_RPC 2			/* RPC failure */
#define YPERR_DOMAIN 3			/* Can't bind to a server which serves
					 *   this domain. */
#define YPERR_MAP 4			/* No such map in server's domain */
#define YPERR_KEY 5			/* No such key in map */
#define YPERR_YPERR 6			/* Internal NIS server or client
					 *   interface error */
#define YPERR_RESRC 7			/* Local resource allocation failure */
#define YPERR_NOMORE 8			/* No more records in map database */
#define YPERR_PMAP 9			/* Can't communicate with portmapper */
#define YPERR_YPBIND 10			/* Can't communicate with ypbind */
#define YPERR_YPSERV 11			/* Can't communicate with ypserv */
#define YPERR_NODOM 12			/* Local domain name not set */
#define YPERR_BADDB 13			/* NIS data base is bad */
#define YPERR_VERS 14			/* NIS version mismatch */
#define YPERR_ACCESS 15			/* Access violation */
#define YPERR_BUSY 16			/* Database is busy */

/*
 * Types of update operations
 */
#define YPOP_CHANGE 1			/* change, do not add */
#define YPOP_INSERT 2			/* add, do not change */
#define YPOP_DELETE 3			/* delete this entry */
#define YPOP_STORE  4			/* add, or change */
 
 

/*           
 * Data definitions
 */

/*
 * struct ypall_callback * is the arg which must be passed to yp_all
 */

struct ypall_callback {
        /* Return non-0 to stop getting called */
	int (*foreach) __((int, char *, int, char *, int, char *));
	char *data;			/* Opaque pointer for use of callback
					 *   function */
};

/* forward decl for ANSI/C++ */
struct dom_binding;

/*
 * External NIS client function references. 
 */
_BEGIN_CPLUSPLUS
extern int yp_bind __((char *));
extern int _yp_dobind __((char *, struct dom_binding **));
extern void yp_unbind __((char *));
extern void yp_unbind_soft __((char *));
extern int yp_get_default_domain __((char **));
extern int yp_match __((char *, char *, char *, int, char **, int *));
extern void __yp_match_flush __((char *, char *, char *, int));
extern int yp_first __((char *, char *, char **, int *, char **, int *));
extern int yp_next __((char *, char *, char *, int, char **, int *, char **, int *));
extern int yp_master __((char *, char *, char **));
extern int yp_order __((char *, char *, unsigned int *));
extern int yp_all __((char *, char *, struct ypall_callback *));
extern char *yperr_string __((int));
extern int ypprot_err __((unsigned int));
_END_CPLUSPLUS

/*
 * Global NIS data structures
 */
#endif /* _RPCSVC_YPCLNT_H_ */
