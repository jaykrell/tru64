/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: mbdb.h,v $
 * Revision 1.1.2.1  2006/07/18  11:15:51  Sunilkumar_Mummigatti
 * 	New for sendmail.v8.13.6
 *
 * $EndLog$
 */
/*
 * @(#)$RCSfile: mbdb.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2006/07/18 11:15:51 $
 */
/*
 * Copyright (c) 2001-2002 Sendmail, Inc. and its suppliers.
 *      All rights reserved.
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the sendmail distribution.
 *
 *	$Id: mbdb.h,v 1.1.2.1 2006/07/18 11:15:51 Sunilkumar_Mummigatti Exp $
 */

#ifndef SM_MBDB_H
# define SM_MBDB_H

#include <pwd.h>
#include <sm/types.h>
#include <sm/limits.h>

/*
**  This is an abstract interface for looking up local mail recipients.
*/

#define	MBDB_MAXNAME	256
#define SM_NO_UID	((uid_t)(-1))
#define SM_NO_GID	((gid_t)(-1))

typedef struct
{
	uid_t	mbdb_uid;
	gid_t	mbdb_gid;
	char	mbdb_name[MBDB_MAXNAME];
	char	mbdb_fullname[MBDB_MAXNAME];
	char	mbdb_homedir[PATH_MAX];
	char	mbdb_shell[PATH_MAX];
} SM_MBDB_T;

extern int	sm_mbdb_initialize __P((char *));
extern void	sm_mbdb_terminate __P((void));
extern int	sm_mbdb_lookup __P((char *, SM_MBDB_T *));
extern void	sm_mbdb_frompw __P((SM_MBDB_T *, struct passwd *));
extern void	sm_pwfullname __P((char *, char *, char *, size_t));

#endif /* ! SM_MBDB_H */
