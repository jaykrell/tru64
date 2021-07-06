/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: prot.h,v $
 * Revision 4.2.63.2  2003/06/11  15:51:20  Eric_Abis
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree v51bsupportos
 *     User Revision:  Eric_Abis_rp1b_br:4.2.59.1 Local Ancestor:4.2.38.9
 *    Merge Revision:  v51bsupportos_br:4.2.63.1
 *   Common Ancestor:  4.2.38.9
 * 	Add a mask bit to signal prpasswdd when writing the root partition.
 *
 * Revision 4.2.63.1  2003/06/10  18:56:07  Spider_Boardman
 * 	Added additional declarations for nsswitch with authcap.
 * 	[2003/05/09  22:29:40  Spider_Boardman]
 * 	Add some definitions for nsswitch support of authcap-style data.
 * 	[2003/04/18  20:51:00  Spider_Boardman]
 * 
 * Revision 4.2.38.9  1998/10/30  21:22:17  Spider_Boardman
 * 	Add auth_close_all().
 * 	[1998/10/29  17:05:08  Spider_Boardman]
 * 	Add auth_is_local_addr().
 * 	[1998/10/27  18:38:34  Spider_Boardman]
 * 	Add declaration for auth_lrpc_getlocal().
 * 	[1998/09/12  06:17:33  Spider_Boardman]
 * 	Update for V3 of the prpasswdd protocol, and associated authcap.c
 * 	changes to use it.
 * 	[1998/09/12  01:14:38  Spider_Boardman]
 * 
 * Revision 4.2.38.8  1998/08/17  16:28:21  John_Ferlan
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	4.2.47.2 **
 * 		** Merge revision:	4.2.38.7 **
 * 	 	** End **
 * 	Merge in Spider's changes.
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -r4.2.47.2 -visual **
 * 		** Ancestor revision:	4.2.38.6 **
 * 		** Merge revision:	4.2.47.2 **
 * 	 	** End **
 * 	[1998/08/14  14:02:38  John_Ferlan]
 * 
 * Revision 4.2.38.7  1998/08/13  18:29:23  John_Ferlan
 * 	Change name of symbol for null password stuff to reflect what
 * 	it truly does.
 * 	[1998/07/23  16:38:19  John_Ferlan]
 * 
 * Revision 4.2.47.2  1998/08/03  20:18:48  Spider_Boardman
 * 	Add auth_mapndbm_findent() for faster rpc.yppasswdd response.
 * 
 * Revision 4.2.38.6  1998/06/29  14:15:44  John_Ferlan
 * 	Add support for BSD Compatibility changes - skipping successful/failed
 * 	login logging and null password prompt options.
 * 	[1998/06/19  16:39:30  John_Ferlan]
 * 
 * Revision 4.2.38.5  1998/04/02  22:22:09  Spider_Boardman
 * 	Fix up prototypes.
 * 	[1998/03/06  14:48:38  Spider_Boardman]
 * 
 * Revision 4.2.38.4  1997/07/16  14:51:56  Spider_Boardman
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	4.2.38.3 **
 * 		** Merge revision:	4.2.38.3 **
 * 	 	** End **
 * 	Add hint for maximum useful length in AUTH_PW_CRYPTNAME.
 * 	[1997/07/14  19:44:01  Spider_Boardman]
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rSTEELOS **
 * 		** Ancestor revision:	4.2.20.3 **
 * 		** Merge revision:	4.2.38.3 **
 * 	 	** End **
 * 	Add u_maxchosen/u_minchosen.
 * 	Note acceptable_password()'s first arg is const.
 * 	[1997/07/10  16:03:14  Spider_Boardman]
 * 	Add pwpolicy callout codes for site-replaceable 1-way encryption
 * 	and password-testing.
 * 	Add declarations for the related new libsecurity entry points.
 * 	Add signed-enum type for escap_parse_fields().
 * 	[1997/07/07  18:07:12  Spider_Boardman]
 * 
 * Revision 4.2.38.3  1997/07/07  05:45:50  Spider_Boardman
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	4.2.20.3 **
 * 		** Merge revision:	4.2.38.2 **
 * 	 	** End **
 * 	Add u_flogins field.
 * 	Update prpasswd protocol to V2 for proper "flogins" handling.
 * 	Expose tty_tagtyped().
 * 	[1997/07/03  19:15:35  Spider_Boardman]
 * 
 * Revision 4.2.38.2  1997/07/03  23:19:14  Spider_Boardman
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL6:spider_n2min **
 * 		** Ancestor revision:	4.2.20.3 **
 * 		** Merge revision:	4.2.34.2 **
 * 	 	** End **
 * 	[1997/07/02  22:39:49  Spider_Boardman]
 * 
 * Revision 4.2.37.2  1997/07/02  22:39:49  Spider_Boardman
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL6:spider_n2min **
 * 		** Ancestor revision:	4.2.20.3 **
 * 		** Merge revision:	4.2.34.2 **
 * 	 	** End **
 * 
 * Revision 4.2.34.2  1997/07/01  20:18:02  Spider_Boardman
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTOS_BL12:spider_n2 **
 * 		** Ancestor revision:	4.2.20.3 **
 * 		** Merge revision:	4.2.30.4 **
 * 	 	** End **
 * 
 * Revision 4.2.33.2  1997/06/03  18:07:14  Spider_Boardman
 * 	Fix (non-)inclusion of <acl.h> for non-MLS+ systems.
 * 	[1997/05/16  16:48:31  Spider_Boardman]
 * 
 * Revision 4.2.30.4  1997/02/26  00:39:45  Spider_Boardman
 * 	Add additional declarations for NIS-master-specific authcap
 * 	routines.
 * 
 * Revision 4.2.30.3  1996/07/22  22:13:53  Spider_Boardman
 * 	Fix up declarations, add error code definitions.
 * 
 * Revision 4.2.30.2  1996/07/10  18:35:37  Spider_Boardman
 * 	Add NIS error codes, program and procedure numbers, and the
 * 	request/response structures for prpasswd map updates.
 * 	Add declarations for the corresponding xdr routines.
 * 
 * Revision 4.2.20.3  1995/06/30  20:54:30  Spider_Boardman
 * 	Add new u_* fields for forced password change and 'grace-period'
 * 	handling.
 * 	Add externs for the various parse tables.
 * 	[1995/06/30  03:11:44  Spider_Boardman]
 * 	Since nobody else has used it yet, add an argument to
 * 	escap_cmp_fields so that edauth can audit changed fields
 * 	more easily.
 * 	Add some defines for things used in common by convauth, convuser,
 * 	and edauth (db-file search-list manipulation, and the default
 * 	'general user' uid).
 * 	[1995/06/22  20:50:09  Spider_Boardman]
 * 	Add escap_cmp_fields().
 * 	[1995/06/16  07:47:43  Spider_Boardman]
 * 	Add various fields to some of the data structures in support of
 * 	the Bellcore RFP and such.
 * 	Update for new routines in fields.c, seed.c, and tod.c.
 * 	[1995/06/15  11:06:16  Spider_Boardman]
 * 	Update for extended authcap API work.
 * 	[1995/05/24  19:33:24  Spider_Boardman]
 * 
 * Revision 4.2.20.2  1995/04/28  22:39:42  Spider_Boardman
 * 	Update for exposing _agetent.
 * 	[1995/04/28  22:24:19  Spider_Boardman]
 * 	Fix more prototype conflicts.
 * 	Update to include agetnstr() and auth_db_set_searchlist().
 * 	Fix loadnamepair to have some const args.
 * 	[1995/04/28  22:21:20  Spider_Boardman]
 * 
 * Revision 4.2.11.5  1994/05/27  20:49:35  Spider_Boardman
 * 	Fix type conflicts caused by first pass at prototype addition.
 * 	[1994/05/27  19:12:53  Spider_Boardman]
 * 
 * Revision 4.2.11.4  1994/05/12  18:04:14  Thomas_Peterson
 * 	Fixes for ANSI/C++.  Added includes for needed typedefs and macros.
 * 	Added fwd decl for struct passwd.  Fully prototyped function decls
 * 	using __() macro from <standards.h> (instead of ifdef _NO_PROTO
 * 	clutter).  Removed function decls for functions which do not exist on
 * 	the system.
 * 	[1994/04/15  18:32:44  Thomas_Peterson]
 * 
 * Revision 4.2.11.3  1994/02/16  19:10:42  Spider_Boardman
 * 	bmerge C++ header changes.
 * 	[1994/02/15  20:22:14  Spider_Boardman]
 * 	Add in extra entry points in authcap.c.
 * 	[1994/02/09  16:31:02  Spider_Boardman]
 * 	post-bmerge check-in
 * 	[1993/12/01  15:26:43  Spider_Boardman]
 * 	bmerge stuff
 * 	[1993/12/01  15:04:43  Spider_Boardman]
 * 	Update external entry points in authcap.c.
 * 	[1993/06/17  00:43:19  Spider_Boardman]
 * 
 * Revision 4.2.11.2  1994/01/07  18:32:34  Thomas_Peterson
 * 	Merged C++ header changes fwd from sterl bl9 to gold bl8
 * 	[1994/01/05  17:24:59  Thomas_Peterson]
 * 
 * Revision 4.2.8.4  1993/12/15  22:13:49  Thomas_Peterson
 * 	Added extern "C" blocks around function declarations as
 * 	required for C++.
 * 	[1993/12/10  15:25:43  Thomas_Peterson]
 * 
 * Revision 4.2.8.3  1993/08/24  22:33:24  Spider_Boardman
 * 	Add ULTRIX migration hooks in pr_passwd structures.
 * 	[1993/08/23  16:24:12  Spider_Boardman]
 * 
 * Revision 4.2.8.2  1993/04/01  20:26:53  Michael_Fairbrother
 * 	Merge from shared sandbox to sandbox prior to submit
 * 	[1993/04/01  16:07:47  Michael_Fairbrother]
 * 
 * Revision 4.2.6.8  1993/03/31  10:26:04  Spider_Boardman
 * 	Add the field for the site password policy callout.
 * 	Add defines for the functions to be communicated with the
 * 	site's callout image.
 * 	[1993/03/31  10:18:35  Spider_Boardman]
 * 
 * Revision 4.2.6.7  1993/03/29  14:04:48  Spider_Boardman
 * 	Fix types for audit, and the comments on password lifetimes.
 * 	[1993/03/29  14:02:54  Spider_Boardman]
 * 
 * Revision 4.2.6.6  1993/03/25  11:56:31  Spider_Boardman
 * 	Add missing fields from pr_passwd & pr_term for I&A requirements.
 * 	[1993/03/25  11:55:39  Spider_Boardman]
 * 
 * Revision 4.2.6.5  1993/03/24  19:44:27  Spider_Boardman
 * 	Begin support for enhanced I&A without SEC_BASE.
 * 	[1993/03/23  10:45:12  Spider_Boardman]
 * 
 * Revision 4.2.6.4  1993/02/18  16:31:49  Spider_Boardman
 * 	Add (more) global entry points in authcap.c
 * 	[93/02/18  16:27:21  Spider_Boardman]
 * 
 * Revision 4.2.6.3  93/02/07  16:22:38  Spider_Boardman
 * 	Add an X-display type for dev_asg to match the xdisp field in pr_term.
 * 	[93/02/07  15:26:31  Spider_Boardman]
 * 	Fix pr_term struct for the xdm flag.
 * 	[93/02/05  14:46:27  Spider_Boardman]
 * 	Entry point changes in libsecurity.
 * 	[93/02/05  11:02:49  Spider_Boardman]
 * 	Add global entry points in authcap.c
 * 	Restore 4.2.4.2 (undo 4.2.4.3) - we should be able to use ":" now.
 * 	[93/02/03  17:51:24  Spider_Boardman]
 * 
 * Revision 4.2.6.2  93/01/27  14:21:31  Michael_Fairbrother
 * 	More OSF/1 hacks... Need to address the AUTH_LOCK_ATTEMPTS
 * 	[93/01/26  15:14:09  Michael_Fairbrother]
 * 
 * Revision 4.2.3.3  92/04/14  17:17:46  Robin_Miller
 * 	Merged in Silver BL5 changes.
 * 	Revision 4.2.4.3  92/03/27  13:32:18  Sec_Proj_Michael_Fairbrother
 * 	Change extensions back to '-t' '-o', can't use ':t' ':o'
 * 	[92/03/09  16:28:44  Uday_Gupta]
 * 
 * Revision 4.2.3.2  92/03/19  17:44:19  Al_Delorey
 * 	From Silver: AG_BL5
 * 	[92/03/19  17:43:46  Al_Delorey]
 * 
 * Revision 4.2.1.2  92/03/17  18:42:15  devbld_gsf
 * 	First AG_BL5 version.  Moved from Ag baselevel delivery tree.
 * 
 * Revision 4.2.4.2  92/02/28  21:40:04  Sec_Proj_Michael_Fairbrother
 * 	change AUTH_TEMP_EXT from -t to :t
 * 	change AUTH_OLD_EXT from -o to :o
 * 	[92/02/06  10:10:19  Uday_Gupta]
 * 
 * Revision 4.2  91/09/20  05:18:26  devbld
 * 	Adding ODE Headers
 * 
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: prot.h,v $ $Revision: 4.2.63.2 $ (DEC) $Date: 2003/06/11 15:51:20 $
 */ 
/*
 */
#ifndef __PROT__
#define __PROT__

/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */


/* Copyright (c) 1988, 1989 SecureWare, Inc.
 *   All rights reserved.
 *
 * Header file for Security Databases
 *

 * Based on:

 */

/*
 * This Module contains Proprietary Information of SecureWare, Inc.
 * and should be treated as Confidential.
 */

#include <standards.h>
_BEGIN_CPLUSPLUS
#include <stdio.h>
#include <sys/security.h>
#include <sys/sec_objects.h>
#include <pwd.h>

#if SEC_MAC
#include <mandatory.h>
#else
typedef void mand_ir_t;
typedef void ilb_ir_t;
#endif

/* This should be redundant with sys/security.h, but keep it just in case.  */
#include <sys/acl.h>

#include <rpc/rpc.h>
#include <sys/time.h>

#define	AUTH_CAPBUFSIZ	10240

/* file template used to prove subsystem identity to audit_dlvr */

#define AUTH_SUBSYS_TICKET	"/tcb/files/subsys/XXXXXXXXXXXXXX"

/* Location of program support for Authentication and Subsystem auditing */



/*  Authentication database locking */

/*
 * AUTH_LOCK_ATTEMPTS used to be 8.  This is unacceptably low, especially
 * since libsecurity code will give up in half that many attempts if the
 * file in question hasn't changed.  Something as simple as being swapped
 * out for a few seconds could cause another process to assume the
 * lock will never be freed, take the lock, and cause database corruption.
 * Choosing a higher value reduces the risk of this problem, but certainly
 * doesn't eliminate it.
 * Note that the DB-based routines use fcntl locking instead.
 */

#define	AUTH_LOCK_ATTEMPTS	100		/* before giving up lock try */
#define	AUTH_RETRY_DELAY	1		/* seconds */
#define	AUTH_CHKENT		"chkent"	/* sanity check when reading */
#define	AUTH_SILENT		0		/* do actions silently */
#define	AUTH_LIMITED		1		/* tell something of action */
#define	AUTH_VERBOSE		2		/* full disclosure of action */


/*  Database system default entry name */

#define	AUTH_DEFAULT		"default"


/*  Support for large passwords and pass-phrases. */

/*
 * The size of the ciphertext is the salt at the
 * beginning, a series of 11-character segments produced by
 * each call to crypt(), and the trailing end-of-string character.
 * Each 11-character segment uses the a newly computed salt based
 * on the previous encrypted value.
 */
#define	AUTH_MAX_PASSWD_LENGTH		80
#define	AUTH_SALT_SIZE			2
#define	AUTH_CLEARTEXT_SEG_CHARS	8
#define	AUTH_CIPHERTEXT_SEG_CHARS	11
#define	AUTH_SEGMENTS(len)		(((len)-1)/AUTH_CLEARTEXT_SEG_CHARS+1)
#define	AUTH_CIPHERTEXT_SIZE(segments)	(AUTH_SALT_SIZE+(segments)*AUTH_CIPHERTEXT_SEG_CHARS+1)
#define	AUTH_MAX_CIPHERTEXT_LENGTH	AUTH_CIPHERTEXT_SIZE(AUTH_SEGMENTS(AUTH_MAX_PASSWD_LENGTH))
#define	AUTH_MAX_PASSWD_DICT_DEPTH	9
#define	AUTH_MAX_PASSWD_DICT_SIZE	(AUTH_MAX_PASSWD_DICT_DEPTH*AUTH_MAX_CIPHERTEXT_LENGTH)
#define	AUTH_MAX_UNAME_SIZE		(8+1)
#ifndef TRUSTED_MASK_LEN
#include <sys/audit.h>
#endif
#define	AUTH_MAX_AUDIT_LENGTH		(4096)	/* 3867 last I checked */
/* Indices for fd_{old,new}crypt algorithms */
#define	AUTH_CRYPT_BIGCRYPT		0	/* index to use bigcrypt */
#define	AUTH_CRYPT_CRYPT16		1	/* index to use crypt16 */
#define	AUTH_CRYPT_OLDCRYPT		2	/* index to use old crypt */
#define	AUTH_CRYPT_C1CRYPT		3	/* index to use /etc/passwd */
#define	AUTH_CRYPT__MAX			3	/* last legal index */


/*  Time-of-day session login constraints */

#define	AUTH_TOD_SIZE		50	/* length of time-of-day constraints */

#if defined(TPATH)
/*
 *
 *	Length of the Trusted Path Sequence (not including the \0)
 *
 */

#define	AUTH_TRUSTED_PATH_LENGTH	12
#endif

/*
 *
 *	Values returned from create_file_securely()
 *
 */

#define	CFS_GOOD_RETURN			0
#define	CFS_CAN_NOT_OPEN_FILE		1
#define	CFS_NO_FILE_CONTROL_ENTRY	2
#define	CFS_CAN_NOT_CHG_MODE		3
#define	CFS_CAN_NOT_CHG_OWNER_GROUP	4
#define	CFS_CAN_NOT_CHG_ACL		5
#define	CFS_CAN_NOT_CHG_SL		6



/*  Database access parameters */

#define	AUTH_REWIND		0	/* look for entry from file beginning */
#define	AUTH_CURPOS		1	/* look for entry from current pos'n */


/*  File updating extensions -- must use 1 char no user can have */

#define	AUTH_OLD_EXT		":o"	/* previous version of file */
#define	AUTH_TEMP_EXT		":t"	/* going to be new version of file */


/*  Time values can be set to current time on initial installation */

#define AUTH_TIME_NOW		"now"
#define	AUTH_TIME_NOW_VALUE	((time_t)-1L)

/*  Location of Subsystem database.  */

#define	AUTH_SUBSYSDIR		"/etc/auth/subsystems"


/*  for fd_secclass  */

#define	AUTH_CLASSES			"security classes"
#define AUTH_D			0	/* TCSEC Class D */
#define AUTH_C1			1	/* TCSEC Class C1 */
#define AUTH_C2			2	/* TCSEC Class C2 */
#define AUTH_B1			3	/* TCSEC Class B1 */
#define AUTH_B2			4	/* TCSEC Class B2 */
#define AUTH_B3			5	/* TCSEC Class B3 */
#define AUTH_A1			6	/* TCSEC Class A1 */
#define	AUTH_MAX_SECCLASS	6


/*  for fd_cprivs and subsystem audit recording  */

#define	AUTH_CMDPRIV			"command authorizations"
/* The actual command authorizations are specified in a control file */

/*  for fd_sprivs  */

#define	AUTH_SYSPRIV			"kernel authorizations"
/* The actual kernel authorizations are defined in <sys/security.h> . */

#define	AUTH_BASEPRIV			"base privileges"
#define	AUTH_PPRIVS			"potential privileges"
#define	AUTH_GPRIVS			"granted privileges"

/*  for fd_auditmask  */

/* The actual event types are defined in <sys/audit.h>. */

#define	AUTH_TYPEVEC_SIZE	(WORD_OF_BIT(AUTH_MAX_TYPE) + 1)

/*
 * NOTE: the system must be re-compiled if more than 32 command
 *	 authorizations are defined.
 * (Should be not true with 'es' interfaces rather than 'pr' calls.)
 */
#define	AUTH_CPRIVVEC_SIZE	1	/* obsolete - don't use */
#define	AUTH_SECCLASSVEC_SIZE	(WORD_OF_BIT(AUTH_MAX_SECCLASS) + 1)
#define	AUTH_SEEDVEC_SIZE	(WORD_OF_BIT(AUTH_MAX_SEED) + 1)

/*
 * The number of command authorizations is defined at runtime according
 * to the Command Authorization Definition file.  This variable is
 * initialized by build_cmd_priv(), automatically invoked from Protected
 * Password and command authorization checking routines.
 */

extern int ST_MAX_CPRIV;

/*
 * Default value for 'general-user' uid, used when creating new
 * users.  Lesser uids should be written to /tcb/files/auth.db.
 * Profiles with uids of at least AUTH_MIN_GEN_UID should be
 * written to /var/tcb/files/auth.db.
 */

#define	AUTH_MIN_GEN_UID	100


/* Extended scan implementation for authcap data */

/* Parser types known to escap_parse_fields: */

/*
flag	parse meaning		storage size	notes
----	--------------------	------------	---------
'b'	boolean			(u)char
'h'	short			short
'H'	ushort			short
't'	time_t			time_t
'i'	int			int
'o'	octal-output int	int
'x'	hex-output int		int		[NYI, same as 'o' now]
'I'	uint			int
'l'	long			long
'O'	octal-output long	long
'X'	hex-output long		long		[NYI, same as 'O' now]
'L'	ulong			long
's'	string			char *
'S'	string list		char **
'm'	sl			mand_ir_t *
'C'	clearance		mand_ir_t *
'M'	il			ilb_ir_t *
'n'	namepair		mask_t *	[namepair index in fmax]
'a'	acl			acle_t *,int
'e'	enum-constrained int	(u)char
'E'	signed enum		char		[backwards because of history]
'p'	privmask		priv_t *
'c'	cmdauth mask		mask_t *
'u'	uid			uid_t
'g'	gid			gid_t
'*'	function special	int(*)(int,...) [field size in fmax] [NYI]

namepair index values:
flag	namepair
----	--------
'c'	cmd_priv
'p'	sys_priv
's'	secclass
'a'	auth_dev_assign
'v'	auth_dev_type

*/

/* The struct used for the table-driven parser */

struct escap_parse {
	const char *fname;	/* name of the field in the buffer */
	int	ptype;		/* parser type (from above list) */
	uint_t	fmax;		/* field maximum, special in many cases */
	size_t	where;		/* how far into the field to store */
	size_t	nmlen;		/* strlen of fname field */
};

/*
 * Note that escap_parse_fields takes an array of escap_parse structs,
 * terminated by an entry with a NULL fname pointer.  It is essential
 * that the list be in precisely the order of the associated flags
 * structure, since that assumption is the basis for the update of the
 * flag bits during the parsing of the data.
 */

/*
 * Macro to build escap_parse arrays.
 */
#define	_ES_PAR(_nm,_pt,_fm,_wh)	{(_nm), (_pt), (_fm), (_wh), \
					     sizeof(_nm)-1}

/*
 * The following structure is used for buffering the 'unparseable'
 * data from the authcap buffer and for keeping copies of pointed-to
 * strings (so that gazillions of separate malloc and subsequent free
 * calls aren't required).  If the 'area' pointer is NULL on entry,
 * an initial guess will be made to fill in the fields based on the
 * string length of the authcap buffer.
 */

struct escap_pad {
	char *area;		/* where the region begins */
	char *next;		/* where next string will go */
	char *aend;		/* last legal place to write */
	size_t size;		/* how big the last allocation was */
};

/* Extended authcap common prologue - used in each OT_* struct */

#define	AUTH_ESCAP_COMMON \
	int version;		/* escap api version */ \
	int source;		/* how did we find this entry */ \
	char *ibuf;		/* raw authcap buffer */ \
	char *ubuf;		/* 'unrecognised' authcap data */


/* Initial version of the extended scanning api, grandfathering the old way */
#define	AUTH_ESCAP_API_VER	2

/* Values for the "source" field in the escap prologue */
#define	AUTH_SRC_LOCAL		1
#define	AUTH_SRC_NIS		2
#define	AUTH_SRC_MAP		4
#define	AUTH_SRC_NSS0		8
/* the above is for non-legacy values from the now-misnamed _svc_ schema */

struct espw_field  {
	/* Identity: */
#define	AUTH_U_NAME		"u_name"
	char	*fd_name;
#define	AUTH_U_ID		"u_id"
	uid_t	fd_uid;	 	/* uid associated with name above */
#define	AUTH_U_PWD		"u_pwd"
	char	*fd_encrypt;	/* Encrypted password */
#define	AUTH_U_OWNER		"u_owner"
	char	*fd_owner;	/* if a pseudo -user, the user behind it */
#define	AUTH_U_PRIORITY		"u_priority"
	int	fd_nice;	/* nice value with which to login */
#define	AUTH_U_CMDPRIV		"u_cmdpriv"
	mask_t	*fd_cprivs;	/* command authorization vector */
#define	AUTH_U_SYSPRIV		"u_syspriv"
	priv_t *fd_sprivs;	/* kernel authorizations vector */
#define	AUTH_U_BASEPRIV		"u_basepriv"
	priv_t *fd_bprivs;	/* base privilege vector */
#define	AUTH_U_AUDITDISP	"u_auditmask"
	char	*fd_auditdisp;	/* auditmask text */
#define	AUTH_U_AUDITCNTL	"u_audcntl"
	uint_t	fd_auditcntl;	/* audit mask use control */

	/* Password maintenance parameters: */
#define	AUTH_U_MINCHG		"u_minchg"
	time_t	fd_min;		/* minimum time between password changes */
#define	AUTH_U_MINLEN		"u_minlen"
	int	fd_minlen;	/* minimum length of password */
#define	AUTH_U_MAXLEN		"u_maxlen"
	int	fd_maxlen;	/* maximum length of password */
#define	AUTH_U_EXP		"u_exp"
	time_t	fd_expire;	/* soft expiration interval (seconds) */
#define	AUTH_U_LIFE		"u_life"
	time_t	fd_lifetime;	/* hard expiration interval (seconds) */
#define	AUTH_U_SUCCHG		"u_succhg"
	time_t	fd_schange;	/* last successful change in secs past 1/1/70 */
#define	AUTH_U_UNSUCCHG		"u_unsucchg"
	time_t	fd_uchange;	/* last unsuccessful change */
#define	AUTH_U_PICKPWD		"u_pickpw"
	char	fd_pick_pwd;	/* can user pick his own passwords? */
#define	AUTH_U_GENPWD		"u_genpwd"
	char	fd_gen_pwd;	/* can user get passwords generated for him? */
#define	AUTH_U_RESTRICT		"u_restrict"
	char	fd_restrict;	/* should generated passwords be restricted? */
#define	AUTH_U_POLICY		"u_policy"
	char	fd_policy;	/* check passwords by policy callout ? */
#define	AUTH_U_NULLPW		"u_nullpw"
	char	fd_nullpw;	/* is user allowed to have a null password? */
#define	AUTH_U_PWCHANGER	"u_pwchanger"
	uid_t	fd_pwchanger;	/* who last changed this user's password */
#ifdef TMAC
#define	AUTH_U_PW_ADMIN_NUM	"u_pw_admin_num"
	long	fd_pw_admin_num;/* password generation verifier */
#endif
#define	AUTH_U_GENCHARS		"u_genchars"
	char	fd_gen_chars;	/* can have password of random ASCII? */
#define	AUTH_U_GENLETTERS	"u_genletters"
	char	fd_gen_letters;	/* can have password of random letters? */
#define	AUTH_U_PWDEPTH		"u_pwdepth"
	int	fd_pwdepth;	/* depth of password dictionary to keep */
#define	AUTH_U_PWDICT		"u_pwdict"
	char	*fd_pwdict;	/* password history dictionary */
#define	AUTH_U_OLDCRYPT		"u_oldcrypt"
	char	fd_oldcrypt;	/* algorithm index for current crypt function */
#define	AUTH_U_NEWCRYPT		"u_newcrypt"
	char	fd_newcrypt;	/* algorithm index for next crypt function */

	/* Mandatory policy parameters: */
#define	AUTH_U_CLEARANCE	"u_clearance"
	mand_ir_t *fd_clearance; /* internal representation of clearance */

	/* Login parameters: */
#define	AUTH_U_SUCLOG		"u_suclog"
	time_t	fd_slogin;	/* last successful login */
#define	AUTH_U_UNSUCLOG		"u_unsuclog"
	time_t	fd_ulogin;	/* last unsuccessful login */
#define	AUTH_U_SUCTTY		"u_suctty"
	char	*fd_suctty;	/* tty of last successful login */
#define	AUTH_U_NUMUNSUCLOG	"u_numunsuclog"
	int	fd_nlogins;	/* consecutive unsuccessful logins */
#define	AUTH_U_UNSUCTTY		"u_unsuctty"
	char	*fd_unsuctty;	/* tty of last unsuccessful login */
#define	AUTH_U_TOD		"u_tod"
	char	*fd_tod;	/* times when user may login */
#define	AUTH_U_MAXTRIES		"u_maxtries"
	int	fd_max_tries;	/* maximum unsuc login tries allowed */
#define	AUTH_U_UNLOCK		"u_unlock"
	time_t	fd_unlockint;	/* interval (seconds) before unlocking again */
#define	AUTH_U_RETIRED		"u_retired"
	char	fd_retired;	/* Is account retired? */
#define	AUTH_U_LOCK		"u_lock"
	char	fd_lock;	/* Unconditionally lock account? */
#define	AUTH_U_EXPDATE		"u_expdate"
	time_t	fd_expdate;	/* time at which to auto-retire the account */
#define	AUTH_U_ISTEMPLATE	"u_istemplate"
	char	fd_istemplate;	/* this account is a template only */
#define	AUTH_U_TEMPLATE		"u_template"
	char	*fd_template;	/* name of (template) account for defaults */
#define	AUTH_U_VAC_START	"u_vacation_start"
	time_t	fd_vac_start;	/* time of user's scheduled vacation */
#define	AUTH_U_VAC_END		"u_vacation_end"
	time_t	fd_vac_end;	/* time when password policy is active again */
#define	AUTH_U_RLIMIT_CPU	"u_rlimit_cpu"
	ulong_t	fd_rlim_cpu;	/* RLIMIT_CPU rlim_max for setrlimit */
#define	AUTH_U_RLIMIT_FSIZE	"u_rlimit_fsize"
	ulong_t	fd_rlim_fsize;	/* RLIMIT_FSIZE rlim_max for setrlimit */
#define	AUTH_U_RLIMIT_DATA	"u_rlimit_data"
	ulong_t	fd_rlim_data;	/* RLIMIT_DATA rlim_max for setrlimit */
#define	AUTH_U_RLIMIT_STACK	"u_rlimit_stack"
	ulong_t	fd_rlim_stack;	/* RLIMIT_STACK rlim_max for setrlimit */
#define	AUTH_U_RLIMIT_CORE	"u_rlimit_core"
	ulong_t	fd_rlim_core;	/* RLIMIT_CORE rlim_max for setrlimit */
#define	AUTH_U_RLIMIT_RSS	"u_rlimit_rss"
	ulong_t	fd_rlim_rss;	/* RLIMIT_RSS rlim_max for setrlimit */
#define	AUTH_U_RLIMIT_NOFILE	"u_rlimit_nofile"
	ulong_t	fd_rlim_nofile;	/* RLIMIT_NOFILE rlim_max for setrlimit */
#define	AUTH_U_RLIMIT_VMEM	"u_rlimit_vmem"
	ulong_t	fd_rlim_vmem;	/* RLIMIT_VMEM rlim_max for setrlimit */
#define	AUTH_U_MAX_LOGIN_INT	"u_max_login_intvl"
	time_t	fd_max_login_int; /* max. time between logins before lockout */
#define	AUTH_U_GRACE_LIMIT	"u_grace_limit"
	time_t	fd_grace_limit;	/* you have until this time to fix things */
#define	AUTH_U_PSW_CHG_REQD	"u_psw_change_reqd"
	char	fd_psw_chg_reqd; /* password change required */
#define	AUTH_U_GEN_SITE		"u_gen_site"
	char	fd_gen_site;
#define	AUTH_U_MINCHOSEN	"u_minchosen"
	uchar_t	fd_minchosen;
#define	AUTH_U_MAXCHOSEN	"u_maxchosen"
	uchar_t	fd_maxchosen;
#define	AUTH_U_FLOGINS		"u_flogins"
	int	fd_flogins;	/* displayable failed login count */
};

struct espw_flag  {
	unsigned int
		/* Identity: */
		fg_name:1,		/* Is fd_name set? */
		fg_uid:1,		/* Is fd_uid set? */
		fg_encrypt:1,		/* Is fd_encrypt set? */
		fg_owner:1,		/* Is fd_owner set? */
		fg_nice:1,		/* Is fd_nice set? */
		fg_cprivs:1,		/* Is fd_sprivs set? */
		fg_sprivs:1,		/* Is fd_sprivs set? */
		fg_bprivs:1,		/* Is fd_bprivs set? */
		fg_auditcntl:1,		/* Is fd_auditcntl set? */
		fg_auditdisp:1,		/* Is fd_auditdisp set? */

		/* Password maintenance parameters: */
		fg_min:1,		/* Is fd_min set? */
		fg_minlen:1,		/* Is fd_minlen set? */
		fg_maxlen:1,		/* Is fd_maxlen set? */
		fg_expire:1,		/* Is fd_expire set? */
		fg_lifetime:1,		/* Is fd_lifetime set? */
		fg_schange:1,		/* Is fd_schange set? */
		fg_uchange:1,		/* Is fd_fchange set? */
		fg_pick_pwd:1,		/* Is fd_pick_pwd set? */
		fg_gen_pwd:1,		/* Is fd_gen_pwd set? */
		fg_restrict:1,		/* Is fd_restrict set? */
		fg_policy:1,		/* Is fd_policy set? */
		fg_nullpw:1,		/* Is fd_nullpw set? */
		fg_pwchanger:1,		/* Is fd_pwchanger set? */
		fg_pwdepth:1,		/* Is fd_pwdepth set? */
		fg_pwdict:1,		/* Is fd_pwdict set? */
#ifdef TMAC
		fg_pw_admin_num:1,	/* Is fd_pw_admin_num set? */
#endif
		fg_gen_chars:1,		/* Is fd_gen_chars set? */
		fg_gen_letters:1,	/* Is fd_gen_letters set? */
		fg_oldcrypt:1,		/* Is fd_oldcrypt set? */
		fg_newcrypt:1,		/* Is fd_newcrypt set? */

		/* Mandatory policy parameters: */
		fg_clearance:1,		/* Is fd_clearance set? */

		/* Login parameters: */
		fg_slogin:1,		/* Is fd_slogin set? */
		fg_suctty: 1,		/* is fd_suctty set ? */
		fg_unsuctty: 1,		/* is fd_unsuctty set ? */
		fg_ulogin:1,		/* Is fd_ulogin set? */
		fg_nlogins:1,		/* Is fd_nlogins set? */
		fg_max_tries:1,		/* Is fd_max_tries set? */
		fg_retired:1,		/* Is fd_retired set? */
		fg_lock:1,		/* Is fd_lock set? */
		fg_unlockint:1,		/* Is fd_unlockint set? */
		fg_tod:1,		/* Is fd_tod set? */
		fg_expdate:1,		/* Is fd_expdate set? */
		fg_istemplate:1,	/* Is fd_istemplate set? */
		fg_template:1,		/* Is fd_template set? */
		fg_vac_start:1,		/* Is fd_vac_start set? */
		fg_vac_end:1,		/* Is fd_vac_end set? */
		fg_rlim_cpu:1,		/* Is fd_rlim_cpu set? */
		fg_rlim_fsize:1,	/* Is fd_rlim_fsize set? */
		fg_rlim_data:1,		/* Is fd_rlim_data set? */
		fg_rlim_stack:1,	/* Is fd_rlim_stack set? */
		fg_rlim_core:1,		/* Is fd_rlim_core set? */
		fg_rlim_rss:1,		/* Is fd_rlim_rss set? */
		fg_rlim_nofile:1,	/* Is fd_rlim_nofile set? */
		fg_rlim_vmem:1,		/* Is fd_rlim_vmem set? */
		fg_max_login_int:1,	/* Is fd_max_login_int set? */
		fg_grace_limit:1,	/* Is fd_grace_limit set? */
		fg_psw_chg_reqd:1,	/* Is fd_psw_chg_reqd set? */
		fg_flogins:1,		/* Is fd_flogins set? */
		fg_gen_site:1,		/* Is fd_gen_site set? */
		fg_minchosen:1,		/* Is fd_minchosen set? */
		fg_maxchosen:1		/* Is fd_maxchosen set? */
		;
};

struct es_passwd  {
	AUTH_ESCAP_COMMON	/* overhead fields */
	size_t		fieldlen; /* length of one of our field structs */
	struct espw_field	*ufld; /* Fields assoc with this user */
	struct espw_flag	*uflg; /* Flags assoc with this user */
	struct espw_field	*sfld; /* Fields assoc with system */
	struct espw_flag	*sflg; /* Flags assoc with system */
};
typedef struct es_passwd es_profile;

/*  Terminal Control Database Entry  */

struct	estc_field  {
#define	AUTH_T_DEVNAME		"t_devname"
	char	*fd_devname;	/* Device/host name */
#define	AUTH_T_UID		"t_uid"
	uid_t	fd_uid;		/* uid of last successful login */
#define	AUTH_T_LOGTIME		"t_logtime"
	time_t	fd_slogin;	/* time stamp of   "        "   */
#define	AUTH_T_UNSUCUID		"t_unsucuid"
	uid_t	fd_uuid;	/* uid of last unsuccessful login */
#define	AUTH_T_UNSUCTIME	"t_unsuctime"
	time_t	fd_ulogin;	/* time stamp of  "           "   */
#define	AUTH_T_PREVUID		"t_prevuid"
	uid_t	fd_loutuid;	/* uid of last logout */
#define	AUTH_T_PREVTIME		"t_prevtime"
	time_t	fd_louttime;	/* time stamp of   "    */
#define	AUTH_T_FAILURES		"t_failures"
	int	fd_nlogins;	/* consecutive failed attempts */
#define	AUTH_T_MAXTRIES		"t_maxtries"
	int	fd_max_tries;	/* maximum unsuc login tries allowed */
#define	AUTH_T_LOGDELAY		"t_logdelay"
	time_t	fd_logdelay;	/* delay between login tries */
#define	AUTH_T_UNLOCK		"t_unlock"
	time_t	fd_unlockint;	/* delay before clearing t_failures */
#define	AUTH_T_LOCK		"t_lock"
	char	fd_lock;	/* terminal locked? */
#define	AUTH_T_XDISPLAY		"t_xdisplay"
	char	fd_xdisp;	/* this entry is for an X display (xdm) */
#define	AUTH_T_LOGIN_TIMEOUT	"t_login_timeout"
	time_t	fd_login_timeout ;	/* login timeout in seconds */
};


struct	estc_flag  {
	unsigned int
		fg_devname:1,		/* Is fd_devname set? */
		fg_uid:1,		/* Is fd_uid set? */
		fg_slogin:1,		/* Is fd_stime set? */
		fg_uuid:1,		/* Is fd_uuid set? */
		fg_ulogin:1,		/* Is fd_ftime set? */
		fg_loutuid:1,		/* Is fd_loutuid set? */
		fg_louttime:1,		/* Is fd_louttime set? */
		fg_nlogins:1,		/* Is fd_nlogins set? */
		fg_max_tries:1,		/* Is fd_max_tries set? */
		fg_logdelay:1,		/* Is fd_logdelay set? */
		fg_lock:1,		/* Is fd_lock set? */
		fg_unlockint:1,		/* Is fd_unlockint set? */
		fg_login_timeout : 1,	/* is fd_login_timeout valid? */
		fg_xdisp : 1		/* Is fd_xdisp valid ? */
		;
};


struct	es_term  {
	AUTH_ESCAP_COMMON
	size_t			fieldlen;
	struct estc_field	*ufld;
	struct estc_flag	*uflg;
	struct estc_field	*sfld;
	struct estc_flag	*sflg;
};


/*  File Control Database Entry  */

struct	esfi_field  {
	char	*fd_name;	/* Holds full path name */
#define	AUTH_F_OWNER		"f_owner"
	uid_t	fd_uid;		/* uid of owner */
#define	AUTH_F_GROUP		"f_group"
	gid_t	fd_gid;		/* gid of group */
#define	AUTH_F_MODE		"f_mode"
	mode_t	fd_mode;	/* permissions */
#define	AUTH_F_TYPE		"f_type"
	char 	*fd_type;	/* file type (one of r,b,c,d,f,s,m) */
#define	AUTH_F_SLEVEL		"f_slevel"
#define	AUTH_F_SYSLO		"syslo"
#define	AUTH_F_SYSHI		"syshi"
#define	AUTH_F_WILD		"WILDCARD"
	mand_ir_t *fd_slevel;	/* sensitivity level for file */
#define	AUTH_F_ACL		"f_acl"
	acle_t	*fd_acl;	/* access control list for file */
	int	fd_acllen;	/* number of entries in fd_acl */
#define	AUTH_F_PPRIVS		"f_pprivs"
	priv_t *fd_pprivs;	/* potential privileges */
#define	AUTH_F_GPRIVS		"f_gprivs"
	priv_t *fd_gprivs;	/* granted privileges */
};

struct	esfi_flag  {
	unsigned int
		fg_name:1,	/* Is fd_name set? */
		fg_uid:1,	/* Is fd_uid set? */
		fg_gid:1,	/* Is fd_gid set? */
		fg_mode:1,	/* Is fd_mode set? */
		fg_type:1	/* Is fd_type set? */
	      , fg_slevel:1	/* Is fd_slevel set? */
	      , fg_acl:1	/* Is fd_acl set? */
	      , fg_pprivs:1,	/* Is fd_pprivs set? */
		fg_gprivs:1	/* Is fd_gprivs set? */
		;
};

struct	es_file  {
	AUTH_ESCAP_COMMON
	size_t			fieldlen;
	struct esfi_field	*ufld;
	struct esfi_flag 	*uflg;
};


/*  Printer Control Database Entry  */

struct	eslp_field  {
#define	AUTH_L_LPNAME		"l_name"
	char	*fd_name;	/* holds printer name */
#define	AUTH_L_INITSEQ		"l_initseq"
	char	*fd_initseq;	/* initial sequence */
#define	AUTH_L_TERMSEQ		"l_termseq"
	char	*fd_termseq;	/* termination sequence */
#define	AUTH_L_EMPH		"l_emph"
	char	*fd_emph;	/* emphasize sequence */
#define	AUTH_L_DEEMPH		"l_deemph"
	char	*fd_deemph;	/* de-emphasize sequence */
#define	AUTH_L_CHRS		"l_chrs"
	char	*fd_chrs;	/* characters to filter */
#define	AUTH_L_CHRSLEN		"l_chrslen"
	size_t	fd_chrslen;	/* length of string of illegal chars */
#define	AUTH_L_ESCS		"l_escs"
	char	*fd_escs;	/* escape sequences */
#define	AUTH_L_ESCSLEN		"l_esclens"
	size_t	fd_escslen;	/* length of string of illegal escape codes */
#define	AUTH_L_LINELEN		"l_linelen"
	int	fd_linelen;	/* length of a line in characters */
#define	AUTH_L_PAGELEN		"l_pagelen"
	int	fd_pagelen;	/* length of a page in lines */
#define	AUTH_L_TRUNCLINE	"l_truncline"
	char	fd_truncline;	/* does printer truncate long lines? */
};

struct	eslp_flag  {
	unsigned int
		fg_name:1,	/* Is fd_name set? */
		fg_initseq:1,	/* Is fd_initseq set? */
		fg_termseq:1,	/* Is fd_termseq set? */
		fg_emph:1,	/* Is fd_emph set? */
		fg_deemph:1,	/* Is fd_deemph set? */
		fg_chrs:1,	/* Is fd_chrs set? */
		fg_chrslen:1,	/* Is fd_chrslen set? */
		fg_escs:1,	/* Is fd_escs set? */
		fg_escslen:1,	/* Is fd_escslen set? */
		fg_linelen:1,	/* Is fd_linelen set? */
		fg_pagelen:1,	/* Is fd_pagelen set? */
		fg_truncline:1	/* Is fd_truncline set? */
		;
};

struct	es_lp  {
	AUTH_ESCAP_COMMON
	size_t			fieldlen;
	struct eslp_field	*ufld;
	struct eslp_flag	*uflg;
	struct eslp_field	*sfld;
	struct eslp_flag	*sflg;
};


/* Device Assignment Database entry */

struct esdev_field {
	char	*fd_name;	/* external name */
#define	AUTH_V_DEVICES	"v_devs"
	char	**fd_devs;	/* device list */
#define	AUTH_V_TYPE	"v_type"
	mask_t	*fd_type;	/* tape, printer, terminal */
#define AUTH_V_MAX_SL	"v_maxsl"
	mand_ir_t	*fd_max_sl;	/* maximum sensitivity level */
#define AUTH_V_MIN_SL	"v_minsl"
	mand_ir_t	*fd_min_sl ;	/* minimum sensitivity level */
#define AUTH_V_CUR_SL	"v_cursl"
	mand_ir_t	*fd_cur_sl ;	/* currently assigned s.l. */
#define AUTH_V_CUR_IL	"v_curil"
	ilb_ir_t	*fd_cur_il ;	/* currently assigned info l. */
#define AUTH_V_ASSIGN	"v_assign"
	mask_t		*fd_assign;	/* single-, multilevel, etc. */
#define	AUTH_V_USERS	"v_users"
	char	**fd_users ; 	/* list of users */
};

struct esdev_flag {
	unsigned int
			fg_name : 1,
			fg_devs : 1,
			fg_type : 1,
			fg_max_sl : 1,
			fg_min_sl : 1,
			fg_cur_sl : 1,
			fg_cur_il : 1,
			fg_assign : 1,
			fg_users  : 1;
};

struct esdev_asg {
	AUTH_ESCAP_COMMON
	size_t			fieldlen;
	struct esdev_field	*ufld;
	struct esdev_flag	*uflg;
	struct esdev_field	*sfld;
	struct esdev_flag	*sflg;
};


/*
 *
 *	Structure definitions for the System Default global values.
 *
 */

struct	es_default_fields
  {
#define	AUTH_D_NAME			"d_name"
    char	*fd_name;
#define	AUTH_D_INACTIVITY_TIMEOUT	"d_inactivity_timeout"
    time_t	fd_inactivity_timeout;
#define	AUTH_D_PW_EXPIRE_WARNING	"d_pw_expire_warning"
    time_t	fd_pw_expire_warning;
#define AUTH_D_PW_SITE_CALLOUT		"d_pw_site_callout"
    char	*fd_pw_site_callout;

#define AUTH_D_SINGLE_USER_SL		"d_single_user_sl"
    mand_ir_t	*fd_single_user_sl;

#define	AUTH_D_SECCLASS			"d_secclass"
    mask_t	*fd_secclass;	/* System security class */
#define	AUTH_D_BOOT_AUTHENTICATE	"d_boot_authenticate"
    char	fd_boot_authenticate;
    char	fd_audit_enable;

#if defined(TPATH)
#define	AUTH_D_LOGIN_SESSION_TIMEOUT	"d_login_session_timeout"
    ushort	fd_session_timeout;
#define	AUTH_D_LOGIN_SESSION_WARNING	"d_login_session_warning"
    ushort	fd_session_warning;
#if SEC_CHOTS
#define AUTH_D_MULTIPLE_LOGIN		"d_multiple_login_rule"
    ushort	fd_multiple_login_rule;
#else
#define AUTH_D_TRUSTED_PATH_SEQ		"d_trusted_path_seq"
    char	*fd_trusted_path_seq;
#endif
#endif
#define	AUTH_D_ADMIN_PREEXPIRE		"d_admin_preexpire_psw"
    char	fd_preexpire;		/* admin-set psw should be expired */
#define	AUTH_D_SKIP_TTYS_UPDATE		"d_skip_ttys_updates"
    char	fd_skip_ttys_update;	/* skip putprtcnam in login path */
#define	AUTH_D_AUTO_MIGRATE_U		"d_auto_migrate_users"
    char	fd_auto_migrate_u;	/* auto-create 'missing' profiles */
#define	AUTH_D_MAX_VAC_FUTURE		"d_max_vacation_future"
    time_t	fd_max_vac_future;	/* how far into future can vac. be? */
#define	AUTH_D_MAX_VAC_LENGTH		"d_max_vacation_duration"
    time_t	fd_max_vac_len;		/* how long can vac. be (by user)? */
/* if either of the above fields is 0, user-originated 'vacation' scheduling
   is disabled.
 */
#define	AUTH_D_ACCEPT_VOUCH		"d_accept_alternate_vouching"
    char	fd_accept_vouch;	/* accept 'vouching' in SIA */
#define AUTH_D_SKIP_SLOGIN_LOG		"d_skip_success_login_log"
    char	fd_skip_slogin_log;	/* Skip successful login logging */
#define AUTH_D_SKIP_FLOGIN_LOG		"d_skip_fail_login_log"
    char	fd_skip_flogin_log;	/* Skip failed login logging */
#define AUTH_D_NULL_PSW_PROMPT		"d_null_psw_prompt"
    uchar_t	fd_null_psw_prompt;	/* Null password prompt enum */
  } ;

struct	es_default_flags
  {
    unsigned int
		fg_name		       : 1,
		fg_inactivity_timeout  : 1,
		fg_pw_expire_warning   : 1,
		fg_pw_site_callout     : 1,
		fg_single_user_sl      : 1,	/* sens. level for single-user*/
		fg_boot_authenticate   : 1,
		fg_audit_enable        : 1,
#ifdef TPATH
		fg_session_timeout     : 1,	/* set if fd_session valid */
		fg_session_warning     : 1,	/* set if fd_session valid */
#if SEC_CHOTS
		fg_single_user_sl      : 1,	/* sens. level for single-user*/
   	 	fg_multiple_login_rule : 1,	/* set if fd_multiple valid */
#else
		fg_trusted_path_seq    : 1,	/* set if fd_trusted valid */
#endif
#endif
		fg_secclass            : 1,
		fg_preexpire	       : 1,	/* Is fd_preexpire set? */
		fg_skip_ttys_update    : 1,	/* Have fd_skip_ttys_update? */
		fg_auto_migrate_u      : 1,	/* Have fd_auto_migrate_u? */
		fg_max_vac_future      : 1,	/* Have fd_max_vac_future? */
		fg_max_vac_len	       : 1,	/* Have fd_max_vac_len? */
		fg_accept_vouch	       : 1,	/* Have fd_accept_vouch? */
		fg_skip_slogin_log     : 1,	/* Have fd_skip_slogin_log? */
		fg_skip_flogin_log     : 1,	/* Have fd_skip_flogin_log? */
		fg_null_psw_prompt     : 1	/* Have fd_null_psw_prompt */
		;
  } ;

#if SEC_CHOTS
/*
 *
 *	values associated with AUTH_D_MULTIPLE_LOGIN
 *
 */

#define	D_ALLOW_MULTIPLE_LOGINS		0
#define	D_PREVENT_SECOND_LOGIN		1
#define D_PREVENT_SECOND_LOGOUT_FIRST	2

#define D_MIN_MULTIPLE_LOGIN_VALUE	D_ALLOW_MULTIPLE_LOGINS
#define	D_MAX_MULTIPLE_LOGIN_VALUE	D_PREVENT_SECOND_LOGOUT_FIRST
#endif

/* 
 * Values associated with AUTH_D_NULL_PSW_PROMPT
 *	0 : C2 Behavior - always prompt
 *	1 : Prompt if user's shell is in /etc/shells
 *	2 : BSD Behavior - skip if stored passphrase is null
 */
#define AUTH_PSW_PROMPT_ALWAYS		0
#define AUTH_PSW_PROMPT_IFUSERSHELL	1
#define AUTH_PSW_PROMPT_IFNOTEMPTY	2
#define AUTH_PSW_PROMPT_MAXIMUM		2

struct	es_default  {
	AUTH_ESCAP_COMMON
	char				*dd_name ; /* copy of sfld->fd_name */
	int				dg_name ; /* copy of sflg->fg_name */
	size_t			esprof_flen;
	struct espw_field		*prd ;
	struct espw_flag		*prg ;
	size_t			estc_flen;
	struct estc_field		*tcd ;
	struct estc_flag		*tcg ;
	size_t			esdev_flen;
	struct esdev_field		*devd ;
	struct esdev_flag		*devg ;
	size_t			fieldlen;
	struct es_default_fields	*sfld ;
	struct es_default_flags		*sflg ;
} ;


/* old authcap structures */

/*  Protected password database entry  */

struct pr_field  {
	/* Identity: */
/*	AUTH_U_NAME		"u_name"	*/
	char	fd_name[AUTH_MAX_UNAME_SIZE];	/* uses 8 character maximum(and \0) from utmp */
/*	AUTH_U_ID		"u_id"	*/
	uid_t	fd_uid;	 	/* uid associated with name above */
/*	AUTH_U_PWD		"u_pwd"	*/
	char	fd_encrypt[AUTH_MAX_CIPHERTEXT_LENGTH];	/* Encrypted password */
/*	AUTH_U_OWNER		"u_owner"	*/
	char	fd_owner[AUTH_MAX_UNAME_SIZE];	/* if a pseudo -user, the user behind it */
/*	AUTH_U_PRIORITY		"u_priority"	*/
	int	fd_nice;	/* nice value with which to login */
/*	AUTH_U_CMDPRIV		"u_cmdpriv"	*/
	mask_t	fd_cprivs[AUTH_CPRIVVEC_SIZE];	/* command authorization vector */
/*	AUTH_U_SYSPRIV		"u_syspriv"	*/
	privvec_t fd_sprivs;	/* kernel authorizations vector */
/*	AUTH_U_BASEPRIV		"u_basepriv"	*/
	privvec_t fd_bprivs;	/* base privilege vector */
/*	AUTH_U_AUDITDISP	"u_auditmask"	*/
	char	fd_auditdisp[AUTH_MAX_AUDIT_LENGTH];	/* auditmask text */
/*	AUTH_U_AUDITCNTL	"u_audcntl"	*/
	uchar_t	fd_auditcntl;	/* audit mask use control */

	/* Password maintenance parameters: */
/*	AUTH_U_MINCHG		"u_minchg"	*/
	time_t	fd_min;		/* minimum time between password changes */
/*	AUTH_U_MINLEN		"u_minlen"	*/
	int	fd_minlen;	/* minimum length of password */
/*	AUTH_U_MAXLEN		"u_maxlen"	*/
	int	fd_maxlen;	/* maximum length of password */
/*	AUTH_U_EXP		"u_exp"	*/
	time_t	fd_expire;	/* soft expiration interval (seconds) */
/*	AUTH_U_LIFE		"u_life"	*/
	time_t	fd_lifetime;	/* hard expiration interval (seconds) */
/*	AUTH_U_SUCCHG		"u_succhg"	*/
	time_t	fd_schange;	/* last successful change in secs past 1/1/70 */
/*	AUTH_U_UNSUCCHG		"u_unsucchg"	*/
	time_t	fd_uchange;	/* last unsuccessful change */
/*	AUTH_U_PICKPWD		"u_pickpw"	*/
	char	fd_pick_pwd;	/* can user pick his own passwords? */
/*	AUTH_U_GENPWD		"u_genpwd"	*/
	char	fd_gen_pwd;	/* can user get passwords generated for him? */
/*	AUTH_U_RESTRICT		"u_restrict"	*/
	char	fd_restrict;	/* should generated passwords be restricted? */
/*	AUTH_U_POLICY		"u_policy"	*/
	char	fd_policy;	/* check passwords by policy callout ? */
/*	AUTH_U_NULLPW		"u_nullpw"	*/
	char	fd_nullpw;	/* is user allowed to have a null password? */
/*	AUTH_U_PWCHANGER	"u_pwchanger"	*/
	uid_t	fd_pwchanger;	/* who last changed this user's password */
#ifdef TMAC
/*	AUTH_U_PW_ADMIN_NUM	"u_pw_admin_num"	*/
	long	fd_pw_admin_num;/* password generation verifier */
#endif
/*	AUTH_U_GENCHARS		"u_genchars"	*/
	char	fd_gen_chars;	/* can have password of random ASCII? */
/*	AUTH_U_GENLETTERS	"u_genletters"	*/
	char	fd_gen_letters;	/* can have password of random letters? */
/*	AUTH_U_PWDEPTH		"u_pwdepth"	*/
	char	fd_pwdepth;	/* depth of password dictionary to keep */
/*	AUTH_U_PWDICT		"u_pwdict"	*/
	char	fd_pwdict[AUTH_MAX_PASSWD_DICT_SIZE];	/* password history dictionary */
/*	AUTH_U_OLDCRYPT		"u_oldcrypt"	*/
	uchar_t	fd_oldcrypt;	/* algorithm index for current crypt function */
/*	AUTH_U_NEWCRYPT		"u_newcrypt"	*/
	uchar_t	fd_newcrypt;	/* algorithm index for next crypt function */

#if SEC_MAC
	/* Mandatory policy parameters: */
/*	AUTH_U_CLEARANCE	"u_clearance"	*/
	mand_ir_t fd_clearance;	/* internal representation of clearance */
	char fd_clearance_filler[200]; /* MUST follow fd_clearance */
#endif

	/* Login parameters: */
/*	AUTH_U_SUCLOG		"u_suclog"	*/
	time_t	fd_slogin;	/* last successful login */
/*	AUTH_U_UNSUCLOG		"u_unsuclog"	*/
	time_t	fd_ulogin;	/* last unsuccessful login */
/*	AUTH_U_SUCTTY		"u_suctty"	*/
	char	fd_suctty[14];	/* tty of last successful login */
/*	AUTH_U_NUMUNSUCLOG	"u_numunsuclog"	*/
	short	fd_nlogins;	/* consecutive unsuccessful logins */
/*	AUTH_U_UNSUCTTY		"u_unsuctty"	*/
	char	fd_unsuctty[14];/* tty of last unsuccessful login */
/*	AUTH_U_TOD		"u_tod"	*/
	char	fd_tod[AUTH_TOD_SIZE];		/* times when user may login */
/*	AUTH_U_MAXTRIES		"u_maxtries"	*/
	ushort	fd_max_tries;	/* maximum unsuc login tries allowed */
/*	AUTH_U_UNLOCK		"u_unlock"	*/
	time_t	fd_unlockint;	/* interval (seconds) before unlocking again */
/*	AUTH_U_RETIRED		"u_retired"	*/
	char	fd_retired;	/* Is account retired? */
/*	AUTH_U_LOCK		"u_lock"	*/
	char	fd_lock;	/* Unconditionally lock account? */
/*	AUTH_U_EXPDATE		"u_expdate"	*/
	time_t	fd_expdate;	/* time at which to auto-retire the account */
/*	AUTH_U_ISTEMPLATE	"u_istemplate"	*/
	char	fd_istemplate;	/* this account is a template only */
/*	AUTH_U_TEMPLATE		"u_template"	*/
	char	fd_template[AUTH_MAX_UNAME_SIZE];	/* name of (template) account for defaults */
};


struct pr_flag  {
	unsigned int
		/* Identity: */
		fg_name:1,		/* Is fd_name set? */
		fg_uid:1,		/* Is fd_uid set? */
		fg_encrypt:1,		/* Is fd_encrypt set? */
		fg_owner:1,		/* Is fd_owner set? */
		fg_nice:1,		/* Is fd_nice set? */
		fg_cprivs:1,		/* Is fd_sprivs set? */
		fg_sprivs:1,		/* Is fd_sprivs set? */
		fg_bprivs:1,		/* Is fd_bprivs set? */
		fg_auditcntl:1,		/* Is fd_auditcntl set? */
		fg_auditdisp:1,		/* Is fd_auditdisp set? */

		/* Password maintenance parameters: */
		fg_min:1,		/* Is fd_min set? */
		fg_minlen:1,		/* Is fd_minlen set? */
		fg_maxlen:1,		/* Is fd_maxlen set? */
		fg_expire:1,		/* Is fd_expire set? */
		fg_lifetime:1,		/* Is fd_lifetime set? */
		fg_schange:1,		/* Is fd_schange set? */
		fg_uchange:1,		/* Is fd_fchange set? */
		fg_pick_pwd:1,		/* Is fd_pick_pwd set? */
		fg_gen_pwd:1,		/* Is fd_gen_pwd set? */
		fg_restrict:1,		/* Is fd_restrict set? */
		fg_policy:1,		/* Is fd_policy set? */
		fg_nullpw:1,		/* Is fd_nullpw set? */
		fg_pwchanger:1,		/* Is fd_pwchanger set? */
		fg_pwdepth:1,		/* Is fd_pwdepth set? */
		fg_pwdict:1,		/* Is fd_pwdict set? */
#ifdef TMAC
		fg_pw_admin_num:1,	/* Is fd_pw_admin_num set? */
#endif
		fg_gen_chars:1,		/* Is fd_gen_chars set? */
		fg_gen_letters:1,	/* Is fd_gen_letters set? */
		fg_oldcrypt:1,		/* Is fd_oldcrypt set? */
		fg_newcrypt:1,		/* Is fd_newcrypt set? */

#if SEC_MAC
		/* Mandatory policy parameters: */
		fg_clearance:1,		/* Is fd_clearance set? */
#endif

		/* Login parameters: */
		fg_slogin:1,		/* Is fd_slogin set? */
		fg_suctty: 1,		/* is fd_suctty set ? */
		fg_unsuctty: 1,		/* is fd_unsuctty set ? */
		fg_ulogin:1,		/* Is fd_ulogin set? */
		fg_nlogins:1,		/* Is fd_nlogins set? */
		fg_max_tries:1,		/* Is fd_max_tries set? */
		fg_retired:1,		/* Is fd_retired set? */
		fg_lock:1,		/* Is fd_lock set? */
		fg_unlockint:1,		/* Is fd_unlockint set? */
		fg_tod:1,		/* Is fd_tod set? */
		fg_expdate:1,		/* Is fd_expdate set? */
		fg_istemplate:1,	/* Is fd_istemplate set? */
		fg_template:1		/* Is fd_template set? */
		;
};

struct pr_passwd  {
	struct pr_field ufld;	/* Fields assoc specifically with this user */
	struct pr_flag uflg;	/* Flags assoc specifically with this user */
	struct pr_field sfld;	/* Fields assoc with system */
	struct pr_flag sflg;	/* Flags assoc with system */
};

/*  Terminal Control Database Entry  */

struct	t_field  {
/*	AUTH_T_DEVNAME		"t_devname"	*/
	char	fd_devname[14];	/* Device/host name */
/*	AUTH_T_UID		"t_uid"	*/
	uid_t	fd_uid;		/* uid of last successful login */
/*	AUTH_T_LOGTIME		"t_logtime"	*/
	time_t	fd_slogin;	/* time stamp of   "        "   */
/*	AUTH_T_UNSUCUID		"t_unsucuid"	*/
	uid_t	fd_uuid;	/* uid of last unsuccessful login */
/*	AUTH_T_UNSUCTIME	"t_unsuctime"	*/
	time_t	fd_ulogin;	/* time stamp of  "           "   */
/*	AUTH_T_PREVUID		"t_prevuid"	*/
	uid_t	fd_loutuid;	/* uid of last logout */
/*	AUTH_T_PREVTIME		"t_prevtime"	*/
	time_t	fd_louttime;	/* time stamp of   "    */
/*	AUTH_T_FAILURES		"t_failures"	*/
	ushort	fd_nlogins;	/* consecutive failed attempts */
/*	AUTH_T_MAXTRIES		"t_maxtries"	*/
	ushort	fd_max_tries;	/* maximum unsuc login tries allowed */
/*	AUTH_T_LOGDELAY		"t_logdelay"	*/
	time_t	fd_logdelay;	/* delay between login tries */
/*	AUTH_T_UNLOCK		"t_unlock"	*/
	time_t	fd_unlockint;	/* delay before clearing t_failures */
/*	AUTH_T_LOCK		"t_lock"	*/
	char	fd_lock;	/* terminal locked? */
/*	AUTH_T_XDISPLAY		"t_xdisplay"	*/
	char	fd_xdisp;	/* this entry is for an X display (xdm) */
/*	AUTH_T_LOGIN_TIMEOUT	"t_login_timeout"	*/
	ushort	fd_login_timeout ;	/* login timeout in seconds */
};


struct	t_flag  {
	unsigned int
		fg_devname:1,		/* Is fd_devname set? */
		fg_uid:1,		/* Is fd_uid set? */
		fg_slogin:1,		/* Is fd_stime set? */
		fg_uuid:1,		/* Is fd_uuid set? */
		fg_ulogin:1,		/* Is fd_ftime set? */
		fg_loutuid:1,		/* Is fd_loutuid set? */
		fg_louttime:1,		/* Is fd_louttime set? */
		fg_nlogins:1,		/* Is fd_nlogins set? */
		fg_max_tries:1,		/* Is fd_max_tries set? */
		fg_logdelay:1,		/* Is fd_logdelay set? */
		fg_lock:1,		/* Is fd_lock set? */
		fg_unlockint:1,		/* Is fd_unlockint set? */
		fg_login_timeout : 1,	/* is fd_login_timeout valid? */
		fg_xdisp : 1		/* Is fd_xdisp valid ? */
		;
};


struct	pr_term  {
	struct t_field ufld;
	struct t_flag uflg;
	struct t_field sfld;
	struct t_flag sflg;
};


/*  File Control Database Entry  */

struct	f_field  {
	char	*fd_name;	/* Holds full path name */
/*	AUTH_F_OWNER		"f_owner"	*/
	uid_t	fd_uid;		/* uid of owner */
/*	AUTH_F_GROUP		"f_group"	*/
	gid_t	fd_gid;		/* gid of group */
/*	AUTH_F_MODE		"f_mode"	*/
	mode_t	fd_mode;	/* permissions */
/*	AUTH_F_TYPE		"f_type"	*/
	char 	fd_type[2];	/* file type (one of r,b,c,d,f,s,m) */
#if SEC_MAC
/*	AUTH_F_SLEVEL		"f_slevel"	*/
/*	AUTH_F_SYSLO		"syslo"	*/
/*	AUTH_F_SYSHI		"syshi"	*/
/*	AUTH_F_WILD		"WILDCARD"	*/
	mand_ir_t *fd_slevel;	/* sensitivity level for file */
#endif
#if SEC_ACL
/*	AUTH_F_ACL		"f_acl"	*/
#ifndef AUTH_F_WILD
#define AUTH_F_WILD		"WILDCARD"	/* def. shared with MAC */
#endif
	acle_t	*fd_acl;	/* access control list for file */
	int	fd_acllen;	/* number of entries in fd_acl */
#endif
#if SEC_PRIV
/*	AUTH_F_PPRIVS		"f_pprivs"	*/
	privvec_t fd_pprivs;	/* potential privileges */
/*	AUTH_F_GPRIVS		"f_gprivs"	*/
	privvec_t fd_gprivs;	/* granted privileges */
#endif
};

struct	f_flag  {
	unsigned int
		fg_name:1,	/* Is fd_name set? */
		fg_uid:1,	/* Is fd_uid set? */
		fg_gid:1,	/* Is fd_gid set? */
		fg_mode:1,	/* Is fd_mode set? */
		fg_type:1	/* Is fd_type set? */
#if SEC_MAC
	      , fg_slevel:1	/* Is fd_slevel set? */
#endif
#if SEC_ACL
	      , fg_acl:1	/* Is fd_acl set? */
#endif
#if SEC_PRIV
	      , fg_pprivs:1,	/* Is fd_pprivs set? */
		fg_gprivs:1	/* Is fd_gprivs set? */
#endif
		;
};

struct	pr_file  {
	struct f_field ufld;
	struct f_flag uflg;
};


/*  Printer Control Database Entry  */

struct	l_field  {
/*	AUTH_L_LPNAME		"l_name"	*/
	char	fd_name[15];	/* holds printer name */
/*	AUTH_L_INITSEQ		"l_initseq"	*/
	char	fd_initseq[256];/* initial sequence */
/*	AUTH_L_TERMSEQ		"l_termseq"	*/
	char	fd_termseq[256];/* termination sequence */
/*	AUTH_L_EMPH		"l_emph"	*/
	char	fd_emph[256];	/* emphasize sequence */
/*	AUTH_L_DEEMPH		"l_deemph"	*/
	char	fd_deemph[256];	/* de-emphasize sequence */
/*	AUTH_L_CHRS		"l_chrs"	*/
	char	fd_chrs[130];	/* characters to filter */
/*	AUTH_L_CHRSLEN		"l_chrslen"	*/
	ushort	fd_chrslen;	/* length of string of illegal chars */
/*	AUTH_L_ESCS		"l_escs"	*/
	char	fd_escs[256];	/* escape sequences */
/*	AUTH_L_ESCSLEN		"l_esclens"	*/
	ushort	fd_escslen;	/* length of string of illegal escape codes */
/*	AUTH_L_LINELEN		"l_linelen"	*/
	int	fd_linelen;	/* length of a line in characters */
/*	AUTH_L_PAGELEN		"l_pagelen"	*/
	int	fd_pagelen;	/* length of a page in lines */
/*	AUTH_L_TRUNCLINE	"l_truncline"	*/
	char	fd_truncline;	/* does printer truncate long lines? */
};

struct	l_flag  {
	unsigned int
		fg_name:1,	/* Is fd_name set? */
		fg_initseq:1,	/* Is fd_initseq set? */
		fg_termseq:1,	/* Is fd_termseq set? */
		fg_emph:1,	/* Is fd_emph set? */
		fg_deemph:1,	/* Is fd_deemph set? */
		fg_chrs:1,	/* Is fd_chrs set? */
		fg_chrslen:1,	/* Is fd_chrslen set? */
		fg_escs:1,	/* Is fd_escs set? */
		fg_escslen:1,	/* Is fd_escslen set? */
		fg_linelen:1,	/* Is fd_linelen set? */
		fg_pagelen:1,	/* Is fd_pagelen set? */
		fg_truncline:1	/* Is fd_truncline set? */
		;
};

struct	pr_lp  {
	struct l_field ufld;
	struct l_flag uflg;
	struct l_field sfld;
	struct l_flag sflg;
};


/* Device Assignment Database entry */

#define AUTH_DEV_TYPE "device type"
#define AUTH_DEV_PRINTER	0
#define AUTH_DEV_TERMINAL	1
#define AUTH_DEV_TAPE		2
#define AUTH_DEV_REMOTE		3
#define AUTH_DEV_XDISPLAY	4
#define AUTH_MAX_DEV_TYPE	4

#define AUTH_DEV_TYPE_SIZE	(WORD_OF_BIT (AUTH_MAX_DEV_TYPE) + 1)

#define AUTH_DEV_ASSIGN	"device assignment"
#define AUTH_DEV_SINGLE  	0	/* single-level sens. labels. */
#define AUTH_DEV_MULTI   	1	/* multilevel sens. labels. */
#define AUTH_DEV_LABEL   	2	/* labeled import/export enabled */
#define AUTH_DEV_NOLABEL 	3	/* unlabeled import/export enabled */
#define AUTH_DEV_IMPORT  	4	/* enabled for import */
#define AUTH_DEV_EXPORT  	5	/* enabled for export */
#define AUTH_DEV_PASS	 	6	/* internal to mltape */
#define AUTH_DEV_ILSINGLE  	7	/* single-level info. labels. */
#define AUTH_DEV_ILMULTI   	8	/* multilevel info. labels. */
#define AUTH_MAX_DEV_ASSIGN 	10	/* extras were for NCAV junk */
#define AUTH_DEV_ASSIGN_SIZE	(WORD_OF_BIT (AUTH_MAX_DEV_ASSIGN) + 1)

struct dev_field {
	char	*fd_name;	/* external name */
/*	AUTH_V_DEVICES	"v_devs"	*/
	char	**fd_devs;	/* device list */
/*	AUTH_V_TYPE	"v_type"	*/
	mask_t	fd_type[AUTH_DEV_TYPE_SIZE];	/* tape, printer, terminal */
#if SEC_MAC
/*	AUTH_V_MAX_SL	"v_maxsl"	*/
/*	AUTH_V_MIN_SL	"v_minsl"	*/
/*	AUTH_V_CUR_SL	"v_cursl"	*/
	mand_ir_t	*fd_max_sl;	/* maximum sensitivity level */
	mand_ir_t	*fd_min_sl ;	/* minimum sensitivity level */
	mand_ir_t	*fd_cur_sl ;	/* currently assigned s.l. */
#endif
#if SEC_ILB
/*	AUTH_V_CUR_IL	"v_curil"	*/
	ilb_ir_t	*fd_cur_il ;	/* currently assigned info l. */
#endif
#if SEC_ARCH
/*	AUTH_V_ASSIGN	"v_assign"	*/
	mask_t	fd_assign[AUTH_DEV_ASSIGN_SIZE];/* single-, multilevel, etc. */
#endif
/*	AUTH_V_USERS	"v_users"	*/
	char	**fd_users ; 	/* list of users */
};

struct dev_flag {
	unsigned int
			fg_name : 1,
			fg_devs : 1,
			fg_type : 1,
#if SEC_MAC
			fg_max_sl : 1,
			fg_min_sl : 1,
			fg_cur_sl : 1,
#endif
#if SEC_ILB
			fg_cur_il : 1,
#endif
			fg_assign : 1,
			fg_users  : 1;
};

struct dev_asg {
	struct dev_field ufld;
	struct dev_flag  uflg;
	struct dev_field sfld;
	struct dev_flag  sflg;
};


/*
 *
 *	Structure definitions for the System Default global values.
 *
 */

/*	AUTH_D_INACTIVITY_TIMEOUT	"d_inactivity_timeout"	*/
/*	AUTH_D_PW_EXPIRE_WARNING	"d_pw_expire_warning"	*/
/*	AUTH_D_PW_SITE_CALLOUT		"d_pw_site_callout"	*/
/*	AUTH_D_BOOT_AUTHENTICATE	"d_boot_authenticate"	*/
/*	AUTH_D_SECCLASS			"d_secclass"	*/
/*	AUTH_D_SINGLE_USER_SL		"d_single_user_sl"	*/

#ifdef TPATH	/*{*/
/*	AUTH_D_LOGIN_SESSION_TIMEOUT	"d_login_session_timeout"	*/
/*	AUTH_D_LOGIN_SESSION_WARNING	"d_login_session_warning"	*/
#if SEC_CHOTS
/*	AUTH_D_MULTIPLE_LOGIN		"d_multiple_login_rule"	*/
#else
/*	AUTH_D_TRUSTED_PATH_SEQ		"d_trusted_path_seq"	*/
#endif

#endif /*} TPATH */


struct	system_default_fields
  {
    time_t	fd_inactivity_timeout;
    time_t	fd_pw_expire_warning;
    char	fd_pw_site_callout[MAXPATHLEN];

#if SEC_MAC
    mand_ir_t	*fd_single_user_sl;
#endif

    mask_t	fd_secclass[AUTH_SECCLASSVEC_SIZE];/* System security class */
    char	fd_boot_authenticate;
    char	fd_audit_enable;

#if defined(TPATH)
    ushort	fd_session_timeout;
    ushort	fd_session_warning;
#if SEC_CHOTS
    ushort	fd_multiple_login_rule;
#else
    char	fd_trusted_path_seq[AUTH_TRUSTED_PATH_LENGTH+1];
#endif
#endif
  } ;

struct	system_default_flags
  {
    unsigned int
		fg_inactivity_timeout  : 1,
		fg_pw_expire_warning   : 1,
		fg_pw_site_callout     : 1,
#if SEC_MAC
		fg_single_user_sl      : 1,	/* sens. level for single-user*/
#endif
		fg_boot_authenticate   : 1,
		fg_audit_enable        : 1,
#ifdef TPATH
		fg_session_timeout     : 1,	/* set if fd_session valid */
		fg_session_warning     : 1,	/* set if fd_session valid */
#if SEC_CHOTS
		fg_single_user_sl      : 1,	/* sens. level for single-user*/
   	 	fg_multiple_login_rule : 1,	/* set if fd_multiple valid */
#else
		fg_trusted_path_seq    : 1,	/* set if fd_trusted valid */
#endif
#endif
		fg_secclass            : 1 ;
  } ;

struct	pr_default  {
/*	AUTH_D_NAME			"d_name"	*/
	char				dd_name[20] ;
	char				dg_name ;
	struct pr_field			prd ;
	struct pr_flag			prg ;
	struct t_field			tcd ;
	struct t_flag			tcg ;
	struct dev_field		devd ;
	struct dev_flag			devg ;
	struct system_default_fields	sfld ;
	struct system_default_flags	sflg ;
} ;


struct namepair  {
	char *name;
	ulong value;
};


extern char *command_name;
extern char *command_line;

extern struct namepair user_type[];
extern struct namepair *cmd_priv;
extern struct namepair sys_priv[];
extern struct namepair secclass[];
extern struct namepair audit_mask[];
extern struct namepair auth_dev_assign[];
extern struct namepair auth_dev_type[];

extern	int	authcap_last_source[]; /* for "source" fields in escap */

extern struct escap_parse const espw_parse[], esdv_parse[], estc_parse[],
				esfi_parse[], esdf_parse[];
#if SEC_MAC || SEC_ILB
extern struct escap_parse const eslp_parse[];
#endif


/*
 * Structures and definitions for the RPC protocol used in updating the
 * prpasswd NIS map.
 */

/*
 * First, some alternate timeval structs for dealing with "wide" versus
 * "narrow" time over-the-wire.
 */

typedef struct timeval_narrow { int tv_sec; int tv_usec; } timeval_narrow_t;
typedef struct timeval_wide { long tv_sec; int tv_usec; } timeval_wide_t;

#define PRPWPROG_NUM	300632	/* assignment from Sun for "prpasswd" */
#define LPRPWPROG_NUM	300729	/* assignment from Sun for "lprpasswd" */

#define PRPWPROG_VERS_V1	1	/* redundant(?), but handy for V2 */
#define PRPWPROG_VERS_V2	2	/* redundant(?), but handy for V3 */
#define PRPWPROG_VERS_V3	3	/* redundant(?), but handy for V4 */
#define PRPWPROG_VERS		PRPWPROG_VERS_V3

#define PRPW_PROC_NULL		0
#define PRPW_PROC_PWCHG_FAIL	1
#define PRPW_PROC_PWCHG_SUCC	2
#define PRPW_PROC_LOGIN_FAIL	3
#define PRPW_PROC_LOGIN_SUCC	4
#define PRPW_PROC_VAC_UPDATE	5
#define PRPW_PROC_V1_MAX	5
/* End of V1 proc numbers */
#define	PRPW_PROC_LOGIN_FULL	6	/* real login, not just auth_event */
#define PRPW_PROC_V2_MAX	6
/* End of V2 proc numbers */
#define PRPW_PROC_ADMIN_CHANGE	7
#define PRPW_PROC_QUERY_FIELDS	8
#define PRPW_PROC_V3_MAX	8
/* End of V3 proc numbers */

struct prpw_update_req_v1 {
    /* fixed fields, always present */
    char	*fd_name;	/* username for which we're doing the update */
    timeval_narrow_t fd_tstamp;	/* source timestamp, ignored(?) from clients */
    uint32	fd_options;	/* bit-mask for presenting optional fields */
# define PRPW_OPTREQ_OLDPASS	(1<<0)	/* old password present if set */
# define PRPW_OPTREQ_NEWPASS	(1<<1)	/* new fd_encrypt present if set */
# define PRPW_OPTREQ_ORIGIN	(1<<2)	/* point of origin ('tty') present */
# define PRPW_OPTREQ_VACATION	(1<<3)	/* vacation start/end fields present */
    /* optional fields */
    char	*fd_oldpass;	/* cleartext old password (if present) */
    char	*fd_encrypt;	/* encrypted new password (if present) */
    char	*fd_origin;	/* 'tty' of this attempt (if present) */
    int		fd_vac_start;	/* starting timestamp of user vacation (i/p) */
    int		fd_vac_end;	/* ending timestamp of user vacation (i/p) */
};

struct prpw_update_rsp_v1 {
    /* fixed fields, always present */
    uint32	status;		/* 0 for OK, else rpc.yppasswdd error code */
    uint32	optmask;	/* bit-mask for presenting optional fields */
# define PRPW_OPTRSP_ORDNUM	(1<<0)	/* order number to await is present */
    /* optional fields */
    uint32	min_ordnum;	/* must wait for a map update with this o/n */
};

/* XDR functions for above */

extern bool_t xdr_prpw_update_req_v1 __((XDR *, struct prpw_update_req_v1 *));
extern bool_t xdr_prpw_update_rsp_v1 __((XDR *, struct prpw_update_rsp_v1 *));

#define	prpw_update_req_v2	prpw_update_req_v1
#define	prpw_update_rsp_v2	prpw_update_rsp_v1
#define	xdr_prpw_update_req_v2	xdr_prpw_update_req_v1
#define	xdr_prpw_update_rsp_v2	xdr_prpw_update_rsp_v1

struct prpw_update_req_v3 {
    /* fixed fields, always present */
    char	*fd_name;	/* username for which we're doing the update */
    timeval_wide_t tstamp;	/* source timestamp, ignored(?) from clients */
    uint32	fd_options;	/* bit-mask for presenting optional fields */
    /* same bits as in V2 */
    /* optional fields */
    char	*fd_oldpass;	/* cleartext old password (if present) */
    char	*fd_encrypt;	/* encrypted new password (if present) */
    char	*fd_origin;	/* 'tty' of this attempt (if present) */
    long	fd_vac_start;	/* starting timestamp of user vacation (i/p) */
    long	fd_vac_end;	/* ending timestamp of user vacation (i/p) */
};

struct prpw_admin_change_req_v3 {
    /* fixed fields, always present */
    char	*fd_name;	/* name for which we're doing the change */
    timeval_wide_t tstamp;	/* source timestamp, ignored(?) from clients */
    uint32	ot_type;	/* database type: [OT_PRPWD-OT_LP_CNTL] */
    uint32	subtype;        /* operation */
# define PRPW_ADMINT_CREATE	1
# define PRPW_ADMINT_REMOVE	2
# define PRPW_ADMINT_UPDATE	3
    uint32	optmask;	/* bit-mask for presenting optional fields */
# define PRPW_OPTREQ_SPECDATA	(1<<0)
# define PRPW_OPTREQ_UBUFDATA	(1<<1)
# define PRPW_OPTREQ_MATCHDATA	(1<<2)
# define PRPW_OPTREQ_USE_ROOT	(1<<3)
    /* optional fields */
    char	*fd_specdata;	/* data for newly specified fields */
    char	*fd_ubufdata;	/* data for escap ubuf field */
    char	*fd_matchdata;	/* expected contents of changed fields */
};

struct prpw_query_fields_req_v3 {
    /* fixed fields, always present */
    timeval_wide_t tstamp;	/* source timestamp, ignored(?) from clients */
    uint32	ot_type;	/* database type: [OT_PRPWD-OT_LP_CNTL] */
    uint32	optmask;	/* reserved for future expansion */
    /* Bits reflecting inclusion of optional fields get defined here. */
    /* Optional fields (future) get defined below this point. */
};

struct prpw_update_rsp_v3 {
    /* fixed fields, always present */
    uint32	status;		/* 0 for OK, else rpc.yppasswdd error code */
    uint32	optmask;	/* bit-mask for presenting optional fields */
    /* additions to the V2 bits */
# define PRPW_OPTRSP_OBJTYP	(1<<1)	/* ot_type present                  */
# define PRPW_OPTRSP_FLEN	(1<<2)	/* numfields present                */
    /* optional fields */
    uint32	min_ordnum;	/* must wait for a map update with this o/n */
    uint32	ot_type;	/* database type: [OT_PRPWD-OT_LP_CNTL] */
    uint32      numfields;	/* number of fields in escap parse table */
};

extern bool_t xdr_prpw_admin_change_req_v3
    __((XDR *, struct prpw_admin_change_req_v3 *));
extern bool_t xdr_prpw_query_fields_req_v3
    __((XDR *, struct prpw_query_fields_req_v3 *));
extern bool_t xdr_prpw_update_req_v3
    __((XDR *, struct prpw_update_req_v3 *));
extern bool_t xdr_prpw_update_rsp_v3
    __((XDR *, struct prpw_update_rsp_v3 *));
extern bool_t xdr_prpw_v3_req_v1
    __((XDR *, struct prpw_update_req_v3 *));
extern bool_t xdr_prpw_v3_rsp_v1
    __((XDR *, struct prpw_update_rsp_v3 *));

/* Errors returned by rpc.yppasswdd for either program number */

#define	PRPW_ERR_NEW_PARSE	1	/* (ES) new entry parse failure */
#define	PRPW_ERR_OLD_ENTRY	2	/* Missing or corrupted old entry */
#define	PRPW_ERR_PW_UNCHANGED	3	/* struct passwd fields unchanged */
#define	PRPW_ERR_NEW_FIELDS	4	/* (ES) new fields invalid */
#define	PRPW_ERR_UNK_05		5	/* Unknown, not in current code */
#define	PRPW_ERR_UNK_06		6	/* Unknown, not in current code */
#define	PRPW_ERR_OLD_PW		7	/* (BSD) Old psw invalid */
					/* (ES) old daemon or null change */
#define	PRPW_ERR_PTMP_BUSY	8	/* (BSD) ptmp lock file busy - retry */
#define	PRPW_ERR_PTMP_OPEN	9	/* (BSD) ptmp open failure */
#define	PRPW_ERR_PTMP_FDOPEN	10	/* (BSD) ptmp fdopen failure */
#define	PRPW_ERR_UNK_11		11	/* Unknown, not in current code */
#define	PRPW_ERR_PASSWD_OPEN	12	/* (BSD) passwd src open failure */
#define	PRPW_ERR_PTMP_PUT	13	/* (BSD) error during fputs */
#define	PRPW_ERR_PTMP_WRITE	14	/* (BSD) ferror after write to ptmp */
#define	PRPW_ERR_UPDATE_REC	15	/* (BSD) error with final ptmp close */
					/* (ES) putespwnam failure */
#define	PRPW_ERR_UNK_16		16	/* Unknown, not in current code */
#define	PRPW_ERR_PTMP_RENAME	17	/* (BSD) error during final rename */
#define	PRPW_ERR_UNK_18		18	/* Unknown, not in current code */
#define	PRPW_ERR_OLD_PASSWORD	19	/* (ES) old password invalid */
#define	PRPW_ERR_FIELDSYNC	20	/* Unrecognized fields in request */


/*
 * Functions to be performed by the site password policy callout.
 * This has been made extensible in this fashion in case we need
 * to add additional callouts in the future.
 *
 * The calling program will pass the function code as an ASCII
 * representation of a decimal integer into the callout executable on
 * its standard input, followed by a newline (in other words, on a line
 * by itself).  Any parameters which the function requires will then be
 * passed on separate lines.  The called executable will then exit with
 * status 0 if the input was acceptable, or non-0 if it was not.  Unless
 * a function needs to receive some other sort of response from the callout,
 * it should produce no output on stdout or stderr.  It is free to make
 * calls to syslog or to write audit records, however.
 *
 * Here are the functions, and a brief description of their parameters:
 */

typedef enum AUTH_PW_funcs {
	AUTH_pw_init,	/* must be first */

	AUTH_pw_okpassword,
	AUTH_pw_genpassword,
	AUTH_pw_encrypt,
	AUTH_pw_numcrypts,
	AUTH_pw_maxcryptlen,
	AUTH_pw_cryptname,
	AUTH_pw_nsymbols,

	AUTH_pw_limit	/* must be last */
} AUTH_PW_FUNC_T;

#define	AUTH_PW_FUNC_MIN	((int) AUTH_pw_init+1)
#define	AUTH_PW_OKPASSWORD	((int) AUTH_pw_okpassword)
/*
 * First parm is username for which we're trying to change the password.
 * Second is the proposed new password.
 * Exit status is the only expected response.
 */
#define	AUTH_PW_GENPASSWORD	((int) AUTH_pw_genpassword)
/*
 * First parm is username for which we need a new password.
 * Second is the (signed) encryption index (in case it's relevant).
 * Third is the minimum acceptable length for the returned string.
 * Fourth is the maximum acceptable length for the returned string.
 * Output is generated password text, terminated by a newline.
 * The output will be used only if the exit status is 0 and the string
 * output is in the required length range.
 */
#define	AUTH_PW_ENCRYPT		((int) AUTH_pw_encrypt)
/*
 * First parm is the (positive) customer encryption index.
 * Second is the "salt" text (which may not be relevant).
 * Third is the cleartext passcode which needs encrypting.
 * Output is the crypt-string, terminated by a newline.
 * The crypt-string must be no longer than AUTH_MAX_CIPHERTEXT_LENGTH - 1.
 * The output will be used only if the exit status is 0.
 */
#define	AUTH_PW_NUMCRYPTS	((int) AUTH_pw_numcrypts)
/*
 * No input parameters.
 * Output is a string representation of the number of customer algorithms,
 * followed by a newline.  Specifically, if the customer algorithms are
 * numbered -1 and -2, this shall return "2\n".
 * The output will be used only if the exit status is 0.
 */
#define	AUTH_PW_MAXCRYPTLEN	((int) AUTH_pw_maxcryptlen)
/*
 * First (only) parm is the (positive) customer encryption algorithm for
 * which the maximum significant (or acceptable) input length is needed.
 * Output is the formatted number giving that max. length, terminated by a
 * newline.
 * The output will be used only if the exit status is 0.
 */
#define	AUTH_PW_CRYPTNAME	((int) AUTH_pw_cryptname)
/*
 * First (only) parm is the (positive) customer encryption algorithm index
 * for which a "name" tag is desired (primarily for dxaccounts).
 * Output is a short name to use for describing the algorithm, terminated by
 * a newline (the string should be at most 20 characters long).
 * The output will be used only if the exit status is 0.
 */
#define	AUTH_PW_NSYMBOLS	((int) AUTH_pw_nsymbols)
/*
 * First parm is the username for which we're doing the passcode generation.
 * Second parm is the (signed) encryption algorithm index to be used.
 * Output is a formatted number giving the "alphabet size" for passlen(),
 * terminated by a newline.
 * The output will be used only if the exit status is 0 and the number
 * output is in the range 2-191.
 * Exception: exit status of 0 and returned numeric string of "0" means that
 * passcode generation for this user is declined.  This allows suppressing
 * the site-generation option from the password-changing menu.
 */
#define	AUTH_PW_FUNC_MAX	((int) AUTH_pw_limit-1)

/*
 * Type of values to pass to authcap_functab_setup.
 */

typedef struct _authcap_functab {
	int ot_index;
	int	(*setent) __((int)), (*endent) __((int)),
		(*getent) __((int, char **)),
		(*findent) __((int, char const *, char **)),
		(*putent) __((int, char const *, char const *, void const *,
				int (*)(FILE *, char const *, void const *))),
		(*delent) __((int, char const *, char const *));
} authcap_functab_type, *authcap_functab_list;

/*
 * Function table interactions:
 *
 * 'setent' is a rewind & initialize routine.  In particular, it primes
 *	'getent' to fetch the first entry, rather than succeeding entries.
 * 'endent' is a cleanup routine.  It should free any associated dynamic
 *	resources.  It must be robust in the face of redundant calls.
 * 'getent' is a fetch first/next routine.
 * 'findent' is a fetch-by-key routine.  (NULL key implies first/next logic.)
 * 'putent' is a write-by-key routine.
 * 'delent' is a delete-by-key routine.
 *
 * If there is a 'getent', there must be an 'endent'.  If there is no
 * 'setent', an 'endent' call will be tried instead.
 * If there is no 'getent', then attempts to step the database through this
 * interface will call the 'findent' routine with a null key.
 * If there is no 'findent', it should be simulated with 'setent' and multiple
 * 'getent' calls until a match is found.  (NYI)
 * If there is no 'putent', attempts to update the database through this
 * interface will fail.
 * If there is no 'delent', but there is a 'putent', we will ask the 'putent'
 * routine to simulate a 'delent' by entering a NULL key.  If this is not the
 * desired action, provide a failing 'delent' routine.
 *
 * Both 'getent' and 'findent', if provided, must know how to make their
 * own calls to 'setent', in case that has not already been done.
 *
 */

/*
 * These routines are called according to the following prototypes:
 *
 * void authcap_functab_setup(int stype, authcap_functab_list list);
 * int asetent(int atype);
 * int aendent(int atype);
 * int agetent(int atype, char **bpp);
 * int afindent(int atype, char const *key, char **bpp);
 * int aputent(int atype, char const *key, char const *why, void const *db,
 * 		int (*cback)(FILE *fp, char const *keyname, void const *dbuf));
 * int adelent(int atype, char const *key, char const *why);
 *
 * The 'list' parameter to authcap_functab_setup is terminated by an
 * entry with a 0 in its ot_index field.
 *
 */

/*
 * Types of updates authcap_functab_setup will accept
 */
#define	AUTH_FUNCTAB_RESET	1	/* reset to default */
#define	AUTH_FUNCTAB_SET	2	/* set to explicit list */
#define	AUTH_FUNCTAB_UPDATE	3	/* only non-NULL funcs are meaningful */
#define	AUTH_FUNCTAB_QUERY	4	/* fetch current values */

/*
 * The type for the formatting callbacks from auth_*_putent
 */
typedef int auth_xxx_putent_cback __((FILE *, char const *, void const *));
typedef auth_xxx_putent_cback *auth_xxx_putent_cback_ptr;

/*
 * Routines which are currently exported for functab use
 */

/* ye olde interface equivalents, mostly as acquired from SecureWare by OSF */
extern int	auth_gen_setent __((int)), auth_gen_endent __((int)),
		auth_gen_getent __((int, char **)),
		auth_gen_findent __((int, char const *, char **)),
		auth_gen_putent __((int, char const *, char const *,
				    void const *,
				    auth_xxx_putent_cback_ptr)),
		auth_gen_delent __((int, char const *, char const *));

/* routines to use a DB btree file */
extern int	auth_db_setent __((int)), auth_db_endent __((int)),
		auth_db_getent __((int, char **)),
		auth_db_findent __((int, char const *, char **)),
		auth_db_putent __((int, char const *, char const *,
				   void const *,
				   auth_xxx_putent_cback_ptr)),
		auth_db_delent __((int, char const *, char const *));

/* routines to use rpc to a local prpasswd daemon */
extern int	auth_lrpc_setent __((int)), auth_lrpc_endent __((int)),
		auth_lrpc_getent __((int, char **)),
		auth_lrpc_findent __((int, char const *, char **)),
		auth_lrpc_putent __((int, char const *, char const *,
				     void const *,
				     auth_xxx_putent_cback_ptr)),
		auth_lrpc_delent __((int, char const *, char const *));

/* 'switch' routines to go between _gen_ and _db_ */
extern int	auth_lfile_setent __((int)), auth_lfile_endent __((int)),
		auth_lfile_getent __((int, char **)),
		auth_lfile_findent __((int, char const *, char **)),
		auth_lfile_putent __((int, char const *, char const *,
				      void const *,
				      auth_xxx_putent_cback_ptr)),
		auth_lfile_delent __((int, char const *, char const *));

/* 'switch' routines to go between _lfile_ and _lrpc_ */
extern int	auth_lcl_setent __((int)), auth_lcl_endent __((int)),
		auth_lcl_getent __((int, char **)),
		auth_lcl_findent __((int, char const *, char **)),
		auth_lcl_putent __((int, char const *, char const *,
				    void const *,
				    auth_xxx_putent_cback_ptr)),
		auth_lcl_delent __((int, char const *, char const *));

/* routines to use 'secured' NIS (depends on ypbind -s) */
extern int	auth_nis_setent __((int)), auth_nis_endent __((int)),
		auth_nis_getent __((int, char **)),
		auth_nis_findent __((int, char const *, char **)),
		auth_nis_putent __((int, char const *, char const *,
				    void const *,
				    auth_xxx_putent_cback_ptr)),
		auth_nis_delent __((int, char const *, char const *));

/* using /etc/nsswitch.conf to determine whether to use _lcl_ and/or _nis_ */
extern int	auth_svc_setent __((int)), auth_svc_endent __((int)),
		auth_svc_getent __((int, char **)),
		auth_svc_findent __((int, char const *, char **)),
		auth_svc_putent __((int, char const *, char const *,
				    void const *,
				    auth_xxx_putent_cback_ptr)),
		auth_svc_delent __((int, char const *, char const *));

/* routines to update local maps on the NIS master */
extern int	auth_map_setent __((int)), auth_map_endent __((int)),
		auth_map_getent __((int, char **)),
		auth_map_findent __((int, char const *, char **)),
		auth_map_putent __((int, char const *, char const *,
				    void const *,
				    auth_xxx_putent_cback_ptr)),
		auth_map_delent __((int, char const *, char const *));

/* routines for ndbm map handling on the NIS master */
/* auth_mapndbm_*ent return 2 for partial success--full ypmake required */
extern int	auth_mapndbm_putent __((int, char const *, char const *,
					void const *,
					auth_xxx_putent_cback_ptr)),
		auth_mapndbm_delent __((int, char const *, char const *)),
		auth_mapndbm_findent __((int, char const *, char **)),
		auth_map_yporder __((int, time_t *)),
		auth_update_map __((time_t *, const char *, const char *,
					const char *, const char *, int));

/* Functions from accept_pw.c */
extern int acceptable_password __((char const *, FILE *));

/* Functions from authaudit.c */ /* OBSOLETE */
extern void	audit_security_failure __((int, caddr_t, caddr_t, int)),
		audit_no_resource __((caddr_t, int, caddr_t, int)),
		audit_auth_entry __((char const *, int, char const *, int)),
		audit_subsystem __((caddr_t, caddr_t, int)),
		audit_login __((struct pr_passwd *, struct passwd *,
				caddr_t, caddr_t, int)),
		audit_passwd __((caddr_t, int, int)),
		audit_lock __((caddr_t, int, int, int)),
		audit_adjust_mask __((struct pr_passwd *)),
		sa_audit_lock __((int, caddr_t)),
		sa_audit_audit __((int, caddr_t)),
		audit_rcmd __((struct pr_passwd *, struct passwd *,
				caddr_t, caddr_t, caddr_t, caddr_t,
				caddr_t, caddr_t, caddr_t));

/* Functions from authcap.c */
extern uint_t	agetuid __((char const *)),
		agetgid __((char const *));
extern bool_t	auth_lrpc_getlocal __((struct sockaddr_in *)),
		auth_lrpc_getmaster __((struct sockaddr_in *)),
		auth_is_local_addr __((struct sockaddr *)),
		auth_is_prived_addr __((struct sockaddr *));
extern int	asetent __((int)), aendent __((int)),
		agetent __((int, char **)),
		afindent __((int, char const *, char **)),
		aputent __((int, char const *, char const *, void const *,
				int (*)(FILE *, char const *, void const *))),
		adelent __((int, char const *, char const *)),
		ackentname __((char const *, char const *)),
		ackentfile __((char const *, char const *)),
		agetdefault __((void)),
		agetflag __((char const *)),
		agttime __((char const *, time_t *)),
		agtnum __((char const *, long *)),
		aencode __((char **, char const *)),
		aptentnames __((FILE *, int *, int, char const **)),
		aptentflush __((FILE *)),
		aptentslist __((FILE *, int *, int,
				char const *, char const **)),
		aptentname __((FILE *, int *, int, char const *)),
		aptentnameq __((FILE *, int *, int, char const *)),
		aptentfileq __((FILE *, int *, int, char const *)),
		aptentstr __((FILE *, int *, int, char const *, char const *)),
		aptentnstr __((FILE *, int *, int, char const *,
			       size_t, char const *)),
		aptentnmpair __((FILE *, int *, int, char const *,
				 mask_t const *,
				 int, struct namepair const *, char const *)),
		aptentgid __((FILE *, int *, int, char const *, gid_t)),
		aptentuid __((FILE *, int *, int, char const *, uid_t)),
		aptentunum __((FILE *, int *, int, char const *, u_long)),
		aptentonum __((FILE *, int *, int, char const *, u_long)),
		aptentuint __((FILE *, int *, int, char const *, u_int)),
		aptentsnum __((FILE *, int *, int, char const *, long)),
		aptentsint __((FILE *, int *, int, char const *, int)),
		aptenttime __((FILE *, int *, int, char const *, time_t)),
		aptentbool __((FILE *, int *, int, char const *, int)),
		aptentfin __((FILE *, int *)),
		aptentfclose __((FILE *)),
		auth_db_set_searchlist __((int, const char *)),
		auth_nis_master __((void)),
		auth_nis_clu_master __((int)),
		auth_nis_on_master __((int, int)),
		auth_map_use_file __((int, char const *)),
		auth_null_cback __((FILE *, char const *, void const *)),
		_agetent __((char **, int *, char const *, int,
			     long *, FILE *));
extern int	auth_nss_getent __((int, int, char **, void *)),
		auth_nss_findent __((int, int, char const *, char **, void *)),
		auth_nss_putent __((int, char const *, int,
				    int, char const *, char const *,
				    void const *, auth_xxx_putent_cback_ptr,
				    void *)),
		auth_nss_delent __((int, int, char const *, char const *,
				    void *)),
		acapquery __((int, int, int, void *));
extern void	open_auth_file __((char const *, int, FILE **)),
		end_authcap __((int)),
		endprdfent __((void)), setprdfent __((void)),
		authcap_functab_setup __((int, authcap_functab_list)),
		setprpwaux __((struct passwd * (*) (char const *) )),
		auth_close_all __((void)),
		auth_drop_master __((int)),
		auth_nis_update_type __((int, int)),
		auth_nis_opt_oldpass __((int)),
		auth_nis_use_oldpass __((char const *)),
		auth_take_master __((int));
extern char	*agetstr __((char const *, char **)),
		**agetstrlist __((char const *)),
		*agetnstr __((char const *, char **, size_t)),
		*find_auth_file __((char const*, int)),
		*agetdefault_buf __((void)),
		**agetnmlist __((void)),
		*adecodestr __((char const *)),
		*agetnextfield __((char const *)),
		*agetnextident __((char const *, size_t *)),
		*auth_db_get_searchlist __((int)),
		*auth_map_get_basedir __((int));
extern char const *auth_ot_name __((int));
extern long	adecodenum __((char const *));
extern FILE	*aptentfsopen __((void));

/*
 * Special values for the second parameter to auth_db_set_searchlist()
 */

#define	AUTH_DB_SL_RESET	((const char *)0) /* restore default s/l */
#define	AUTH_DB_SL_SINGLE	((const char *)-1L) /* root f/s only s/l */

/* values for 'prefsrc' parameters to various nsdispatch-called routines */
#define	AUTH_NSS_ANY		(-1)
#define	AUTH_NSS_ALL		(-2)
#define	AUTH_NSS_LOCAL		(-3)

/* values for nsdispatch-called acapquery routines */
#define	AUTH_QRY_VERSION	(1)
#define	AUTH_QRY_NUMFIELDS	(2)
#define	AUTH_QRY_ISMASTER	(3)
#define	AUTH_QRY_ISWRITABLE	(4)

/* Functions from discr.c */
extern int	create_file_securely __((char const *, int, char const *)),
		create_dir_securely __((char const *, int, char const *)),
		make_transition_files __((char const *, char **, char **)),
		replace_file __((char *, char const *, char *)),
		set_file_securely __((char const *, char const *));
extern void	setuid_least_privilege __((void));

#if SEC_ARCH
/* Functions from disk.c */
extern void	disk_set_file_system __((struct filsys *, int)),
		disk_inode_incr __((struct dinode **, int));
#ifndef BSD
extern daddr_t	disk_itod __((int)), disk_itoo __((int));
#else
extern void disk_inode_in_block __((struct fs *, char *, struct dinode **, ino_t));
#endif
#endif /* SEC_ARCH */

/* Functions from escap.c */
extern int	escap_cmp_fields __((struct escap_parse const *,
				     size_t, void const *, void const *,
				     uint_t const *, uint_t const *,
				     uint_t **));
extern int	escap_copy_fields __((struct escap_parse const *,
				      size_t, void *, void const *,
				      uint_t *, uint_t const *,
				      struct escap_pad *));
extern int	escap_count_fields __((struct escap_parse const *));
extern int	escap_parse_fields __((struct escap_parse const *,
				       size_t, void *, uint_t *, char *,
				       struct escap_pad *,
				       struct escap_pad *));
extern int	escap_print_fields __((struct escap_parse const *,
				       size_t, void const *, uint_t const *,
				       FILE *));
extern size_t	escap_size_data __((struct escap_parse const *,
				    size_t, void const *, uint_t const *));

/* Functions from fields.c */
extern void	loadnamepair __((mask_t *, int, char const *,
				 struct namepair const *,
				 const char *, int, const char *));
extern char	*storenamepair __((mask_t const *, int,
				   struct namepair const *, char const *)),
		*storebool __((int));
#define AUTH_LOCKED_OUT_AUD_FLAG 0x001
extern int	locked_out __((struct pr_passwd *)),
		locked_out_es __((struct es_passwd *)),
		locked_out_acct_es __((struct es_passwd *, struct es_default *,
					int, ...)),
		auth_for_terminal __((struct pr_passwd *, struct pr_term *)),
		auth_for_terminal_es __((struct es_passwd *,
					 struct es_term *)),
		pr_newline __((FILE *, int, int *));

/* Functions from getprpwent.c */
extern int	putprpwnam __((char const *, struct pr_passwd const *)),
		putespwnam __((char const *, struct es_passwd const *));
extern struct es_passwd
		*getespwent __((void)), *getespwuid __((uid_t)),
		*getespwnam __((char const *)),
		*copyespwent __((struct es_passwd const *));
extern struct pr_passwd
		*getprpwent __((void)), *getprpwuid __((uid_t)),
		*getprpwnam __((char const *));
extern void	setprpwent __((void)), endprpwent __((void)),
		upgrade_pr_fields __((struct pr_field const *,
				      struct pr_flag const *,
				      struct espw_field *,
				      struct espw_flag *)),
		downgrade_pr_fields __((struct pr_field *,
					struct pr_flag *,
					struct espw_field const *,
					struct espw_flag const *));

/* Functions from getprtcent.c */
extern int	putprtcnam __((char const *, struct pr_term const *)),
		putestcnam __((char const *, struct es_term const *));
extern struct es_term
		*getestcent __((void)), *getestcnam __((char const *)),
		*copyestcent __((struct es_term const *));
extern struct pr_term
		*getprtcent __((void)), *getprtcnam __((char const *));
extern void	setprtcent __((void)), endprtcent __((void)),
		upgrade_tc_fields __((struct t_field const *,
				      struct t_flag const *,
				      struct estc_field *,
				      struct estc_flag *)),
		downgrade_tc_fields __((struct t_field *,
					struct t_flag *,
					struct estc_field const *,
					struct estc_flag const *));

/* Functions from getprfient.c */
extern int	putprfinam __((char const *, struct pr_file const *)),
		putesfinam __((char const *, struct es_file const *));
extern struct es_file
		*getesfient __((void)), *getesfinam __((char const *)),
		*copyesfient __((struct es_file const *));
extern struct pr_file
		*getprfient __((void)), *getprfinam __((char const *));
extern void	setprfient __((void)), endprfient __((void)),
		downgrade_fi_fields __((struct f_field *, struct f_flag *,
					const struct esfi_field *,
					const struct esfi_flag *)),
		upgrade_fi_fields __((const struct f_field *,
				      const struct f_flag *,
				      struct esfi_field *,
				      struct esfi_flag *));

/* Functions from getprdfent.c */
extern int	putprdfnam __((char const *, struct pr_default const *)),
		putesdfnam __((char const *, struct es_default const *));
extern struct es_default
		*getesdfent __((void)), *getesdfnam __((char const *)),
		*copyesdfent __((struct es_default const *));
extern struct pr_default
		*getprdfent __((void)), *getprdfnam __((char const *));

/* Functions from getdvagent.c */
extern int	putdvagnam __((char const *, struct dev_asg const *)),
		putesdvnam __((char const *, struct esdev_asg const *));
extern struct esdev_asg
		*getesdvent __((void)), *getesdvnam __((char const *)),
		*copyesdvent __((struct esdev_asg const *));
extern struct dev_asg
		*getdvagent __((void)), *getdvagnam __((char const *)),
		*copydvagent __((struct dev_asg const *));
extern void	setdvagent __((void)), enddvagent __((void)),
		upgrade_dv_fields __((struct dev_field const *,
				      struct dev_flag const *,
				      struct esdev_field *,
				      struct esdev_flag *)),
		downgrade_dv_fields __((struct dev_field *,
					struct dev_flag *,
					struct esdev_field const *,
					struct esdev_flag const *));

#if SEC_MAC || SEC_ILB
/* Functions from getprlpent.c */
extern struct es_lp
		*geteslpent __((void)), *geteslpnam __((char const *)),
		*copyeslpent __((struct es_lp const *));
extern struct pr_lp
		*getprlpent __((void)), *getprlpnam __((char const *));
extern void	setprlpent __((void)), endprlpent __((void));
#endif

/* Functions from identity.c */
extern int	is_starting_luid __((uid_t)), is_starting_ruid __((uid_t)),
		is_starting_euid __((uid_t)), is_starting_rgid __((gid_t)),
		is_starting_egid __((gid_t));
extern void	set_auth_parameters __((int, char * [])),
		check_auth_parameters __((void)),
		enter_quiet_zone __((void)), exit_quiet_zone __((void));
extern uid_t	starting_luid __((void)), starting_ruid __((void)),
		starting_euid __((void));
extern gid_t	starting_rgid __((void)), starting_egid __((void));

/* Functions from getpasswd.c */
extern char	*getpasswd __((const char *, int)),
		*fgetpasswd __((const char *, int, FILE *, FILE *)),
		*bigcrypt __((const char *, const char *)),
		*dispcrypt __((char const *, char const *, int));
extern const char *get_crypt_name __((int));
extern int	get_num_crypts __((void)), get_num_cust_crypts __((void)),
		get_crypt_maxlen __((int)),
		call_pwpolicy __((char const *, int, char const *,
				  char *, size_t));

/* Functions from login_sec.c */
extern int	tty_tagtyped __((char const *));
extern int	device_is_the_console __((char const *));	

/* Functions from map_ids.c */
extern uid_t	pw_nametoid __((char const *));
extern gid_t	gr_nametoid __((char const *));
extern char	*pw_idtoname __((uid_t)), *gr_idtoname __((gid_t));

/* Functions from printbuf.c */
extern void	printbuf __((char *, int, char *));

/* Functions from nlgetamsg.c */
extern char	*nlgetamsg __((const char *, int, int, const char *));

/* Functions from passlen.c */
extern int	passlen __((time_t, time_t, int));

/* Functions from psecerror.c */
extern void	psecerror __((char *));

/* Functions from privileges.c */
extern void	initprivs __((void)), setprivvec __((privvec_t, ...));
extern priv_t	*checksysauths __((privvec_t)), *checkprivs __((privvec_t)),
		*privvec __((int, ...));
extern char	*privtoname __((int)), *privstostr __((privvec_t, char *));
extern int	hassysauth __((int)), forcepriv __((int)),
		disablesysauth __((int)), enablepriv __((int)),
		disablepriv __((int)), enableprivs __((privvec_t, priv_t *)),
		forceprivs __((privvec_t, priv_t *)),
		disableprivs __((privvec_t, priv_t *)),
		seteffprivs __((privvec_t, priv_t *)),
		setbaseprivs __((privvec_t)), setsysauths __((privvec_t)),
		nametopriv __((char *)),
		strtoprivs __((char *, char *, privvec_t));

/* Functions from randomword.c */
extern int	randomchars __((char *, unsigned int, unsigned int,
					int, long)),
		randomletters __((char *, unsigned int, unsigned int,
					int, long)),
		randomword __((char *, char *, unsigned int, unsigned int,
					int, long));

/* Functions from security.c */
extern uid_t	getluid __((void));
extern int	stopio __((caddr_t)), security_is_on __((void)),
		setluid __((uid_t)),
		getpriv __((long, priv_t *)), security_is_avail __((void)),
		statprivsys __((long, priv_t *, long, obj_t *)),
		setpriv __((long, priv_t *)),
		chprivsys __((long, priv_t *, long, obj_t *)),
		security_turn_on __((gid_t)), security_turn_off __((void));

/* Functions from seed.c */
extern void	set_seed __((long));
extern long	get_seed __((struct pr_passwd *)),
		get_seed_es __((struct es_passwd *));

/* Functions from subsystems.c */
extern int	authorized_user __((char const *)),
		hascmdauth __((char const *, priv_t const *)),
		total_auths __((void)), widest_auth __((void)),
		build_cmd_priv __((void)),
		write_authorizations __((char const *, char const **, int)),
		primary_auth __((char const *)),
		secondary_auth __((char const *));
extern char	*subsys_real_name __((char *));

/* Functions from tod.c */
extern int	time_lock __((struct pr_passwd *)),
		time_lock_es __((struct es_passwd *));

_END_CPLUSPLUS

#endif /* __PROT__ */
