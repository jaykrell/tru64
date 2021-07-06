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
 *      @(#)$RCSfile: ypsym.h,v $ $Revision: 4.2.5.2 $ (DEC) $Date: 1994/03/29 18:56:08 $
 */
/*
 */

/*
 * This contains symbol and structure definitions for modules in the NIS
 * server.  
 */

#ifndef _RPCSVC_YPSYM_H_
#define _RPCSVC_YPSYM_H_

#include <standards.h>
#include <dbm.h>			/* Pull this in first */
#define DATUM
_BEGIN_CPLUSPLUS
extern void dbmclose();			/* Refer to dbm routine not in dbm.h */
_END_CPLUSPLUS
#ifdef NULL
#undef NULL				/* Remove dbm.h's definition of NULL */
#endif
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <rpc/rpc.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <rpcsvc/yp_prot.h>
#include <rpcsvc/ypv1_prot.h>
#include <rpcsvc/ypclnt.h>

typedef void (*PFV)();
typedef int (*PFI)();
typedef unsigned int (*PFU)();
typedef int (*PFLI)();
typedef unsigned int (*PFULI)();
typedef short int (*PFSI)();
typedef unsigned short int (*PFUSI)();

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#  define NULL 0L
#endif

#define YPINTERTRY_TIME 10		/* Secs between tries for peer bind */
#define YPTOTAL_TIME 30			/* Total secs until timeout */
#define YPNOPORT ((unsigned short) 0)	/* Out-of-range port value */

/* External refs to cells and functions outside of the NIS */

extern int errno;
#include <stdlib.h>       /* for malloc() & atol() */
#include <string.h>       /* for strcpy() & strcat() */

/* External refs to NIS server data structures */

extern bool ypinitialization_done;
extern struct timeval ypintertry;
extern struct timeval yptimeout;
extern char myhostname[];

/* External refs to NIS server-only functions */

_BEGIN_CPLUSPLUS
extern bool ypcheck_map_existence __((char *));
extern bool ypset_current_map __((char *, char *, unsigned *));
extern void ypclr_current_map ();
extern bool ypbind_to_named_server ();
extern void ypmkfilename __((char *, char *, char *));
extern int yplist_maps __((char *, struct ypmaplist **));
_END_CPLUSPLUS

#endif /* _RPCSVC_YPSYM_H_ */
