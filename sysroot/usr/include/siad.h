/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: siad.h,v $
 * Revision 1.1.49.2  2003/06/10  18:55:08  Spider_Boardman
 * 	Added entry points for getpwnam_compat() and friends.  This helps with
 * 	figuring out where and how to write back updated entries.
 * 	[2003/05/16  18:04:36  Spider_Boardman]
 *
 * 	Added additional 'how-found' bits for indicating NSS sources.
 * 	[2003/04/03  22:03:46  Spider_Boardman]
 *
 * 	Added nss-related entry points.
 * 	[2003/04/02  12:02:33  Spider_Boardman]
 *
 * Revision 1.1.49.1  2003/01/24  21:40:30  Spider_Boardman
 * 	Fix sia_check_sysenv() to take a recording parameter, and add
 * 	sia_restore_sysenv() for cleanup.  Addresses x29logind complaint.
 *
 * Revision 1.1.47.5  2002/05/14  13:20:53  John_Ferlan
 * 	Add bits for siaentityprivate flags for netauth and auditing issues.
 *
 * Revision 1.1.47.4  2002/03/20  20:15:39  John_Ferlan
 * 	Add sia_check_sysenv() definition - for QAR 92001.
 *
 * Revision 1.1.47.3  2002/01/31  18:47:03  John_Ferlan
 * 	Add new SIADEF for sia_initialized state. This allows for a
 * 	default configuration to be created (QAR 90431).
 *
 * Revision 1.1.47.2  2001/10/23  19:03:02  John_Ferlan
 * 	Fix prototype defs for new sia_switch_* routines for
 * 	cplusplus defs.
 *
 * Revision 1.1.47.1  2001/09/19  17:04:42  John_Ferlan
 *  * Add sia_switch_session and sia_switch_change
 *  * Remove defrtn from sia_capcfg_table
 *  *
 *
 * Revision 1.1.43.2  2000/10/30  17:57:12  John_Ferlan
 * 	Add constant to alleviate memory loss for entity reinit.
 * 	Add some more constants and fix up comments a bit.
 * 
 * Revision 1.1.43.1  2000/08/11  14:11:21  Eric_Abis
 * 	Add ifdef for cplusplus and void arguments in function pointers
 * 
 * Revision 1.1.39.2  2000/01/24  18:11:38  Spider_Boardman
 * Merge Information
 *     Merge Revision:  ZULUOS:1.1.39.1
 *     User  Revision:  Spider_Boardman_zmrg_br:1.1.40.2
 *    Common Ancestor:  1.1
 * 	Merge up with submit tree.
 * 
 * Revision 1.1.40.2  2000/01/24  15:37:37  Spider_Boardman
 * 	Re-sync with zincos bl3 pass 5.
 * 
 * Revision 1.1.39.1  2000/01/21  21:19:55  Mark_Keller
 * 	Adding sia token attribute handling
 * 
 * Revision 1.1.36.2  2000/01/19  23:24:06  Spider_Boardman
 * 	* Add declaration for __sia_update_grouplist().  It's here rather than
 * 	* in <sia.h> because it's intended for use by mechanisms, not by
 * 	* normal callers of the 'middle layer'.
 * 
 * Revision 1.1.36.1  1999/10/12  19:52:34  John_Ferlan
 * 	Add routine definition for __sia_ses_islogin.
 * 	[1999/09/30  14:35:59  John_Ferlan]
 * 	Add __sia_read_lastlog() definition.
 * 	[1999/09/28  18:59:43  John_Ferlan]
 * 	Add definition for SIA_A_ISLOGIN.  Add references to the
 * 	__sia_priv_ interfaces.
 * 	[1999/09/23  17:07:26  John_Ferlan]
 * 
 * Revision 1.1.32.3  1998/04/02  22:19:35  Spider_Boardman
 * 	Add missing sia_mat_init() declaration.
 * 	[1998/03/21  00:43:32  Spider_Boardman]
 * 	Add sia_free_context(), and bsd_upd_it().
 * 	[1998/03/06  14:43:15  Spider_Boardman]
 * 	Add new flags and entrypoints.  Eliminate symbols which were marked
 * 	obsolete in v4.0.
 * 	[1997/12/02  17:44:55  Spider_Boardman]
 * 
 * Revision 1.1.32.2  1996/12/09  22:02:15  Neil_Lewis
 * 	Fix new prototypes; can't assume -std1.
 * 	[1996/11/25  16:18:44  Neil_Lewis]
 * 	Eliminate compiler warnings when compiled with -warnprotos.
 * 	[1996/11/12  16:21:59  Neil_Lewis]
 * 
 * Revision 1.1.21.8  1995/06/30  08:40:39  Spider_Boardman
 * 	Change {elevate,restore}_privs to a single toggle_privs.
 * 	[1995/06/29  16:34:18  Spider_Boardman]
 * 	Add new callouts for siad_get_groups(),
 * 	siad_ses_{elevate,restore}_privs(),
 * 	siad_ses_update_audit_record(), __sia_isagroup().
 * 	[1995/06/27  22:02:29  Spider_Boardman]
 * 
 * Revision 1.1.21.7  1995/06/12  20:37:00  David_Long
 * 	Pt DECthreads functional submit for public TIS and static/inline mutexes.
 * 	[1995/06/05  18:25:23  David_Long]
 * 
 * Revision 1.1.21.6  1995/05/23  14:49:46  Spider_Boardman
 * 	Sync up with ptliteos.bl4.
 * 	[1995/05/23  14:37:50  Spider_Boardman]
 * 
 * Revision 1.1.21.5  1995/03/21  21:47:17  David_Long
 * 	Merge generic group and passwd context structures, and change context type in protos.
 * 	[1995/03/17  16:01:18  David_Long]
 * 	Significant changes to use per-thread context instead of static variables, for threadsafeness.
 * 	Context is retrieved in sia_get* function, passed through sia_switch, and used in siad_get*.
 * 	the siad_get* interface prototypes have a new argument.
 * 	[1995/03/09  18:55:02  David_Long]
 * 
 * Revision 1.1.21.4  1995/01/30  19:10:27  David_Long
 * 	Use TIS mutex macro instead of recursive mutex functions.
 * 	[1995/01/25  16:44:39  David_Long]
 * 
 * Revision 1.1.21.3  1994/12/16  21:45:11  Spider_Boardman
 * 	Update (undocumented) sia_switch & sia_setupfp calling seq for more modular loading from libc.a.
 * 	[1994/12/16  20:39:11  Spider_Boardman]
 * 
 * Revision 1.1.21.2  1994/11/23  19:17:28  David_Long
 * 	Fixed declaration of mutexes for merged libc/libc_r.
 * 	[1994/11/15  18:47:21  David_Long]
 * 
 * Revision 1.1.19.2  1994/09/08  21:07:48  Thomas_Peterson
 * 	Moved C++ linkage blocks around entire header body.
 * 	[1994/09/06  17:22:21  Thomas_Peterson]
 * 
 * Revision 1.1.14.3  1994/05/27  20:31:26  Spider_Boardman
 * 	Fix type for collection routines.
 * 	[1994/05/27  16:17:00  Spider_Boardman]
 * 
 * Revision 1.1.14.2  1994/02/24  23:13:58  Spider_Boardman
 * 	Add record of how BSD-style records was found when NIS is involved.
 * 	[1994/02/24  19:31:33  Spider_Boardman]
 * 
 * Revision 1.1.12.5  1993/11/19  21:44:28  David_Long
 * 	Added context argument to various passwd and group functions for POSIX
 * 	P1003.4a support.
 * 	[1993/11/19  16:14:05  David_Long]
 * 
 * Revision 1.1.12.4  1993/08/04  21:21:57  Spider_Boardman
 * 	post-bmerge checkin.
 * 	[1993/08/04  14:02:19  Spider_Boardman]
 * 	pre-submit bmerge.
 * 	[1993/08/03  20:42:44  Spider_Boardman]
 * 	Add definitions for sia_chdir().  [OSF_QAR(H)10910]
 * 	Add a table of libc{,_r}.so function addresses to map names.
 * 	[1993/07/16  21:28:59  Spider_Boardman]
 * 
 * Revision 1.1.12.3  1993/05/21  21:27:13  Spider_Boardman
 * 	Add extra interface sia_getamsg to replace NLgetamsg.
 * 	(See OSF_QAR(M)12709.)
 * 	[1993/05/20  16:42:50  Spider_Boardman]
 * 
 * Revision 1.1.12.2  1993/04/01  20:19:49  Michael_Fairbrother
 * 	Merge from shared sandbox to sandbox prior to submit
 * 	[1993/04/01  16:01:43  Michael_Fairbrother]
 * 
 * Revision 1.1.10.2  1993/03/31  10:25:17  Spider_Boardman
 * 	Fix some prototypes.
 * 	Add missing declarations for routines to be called by mechanisms.
 * 	[1993/03/31  10:17:17  Spider_Boardman]
 * 
 * Revision 1.1.3.7  1992/12/11  15:25:18  Paula_Long
 * 	Removing duplicate data conflicts for libc_r (data will reside in
 * 	libc and be declared as an extern to libc_r).
 * 	[92/12/10  06:21:07  Paula_Long]
 * 
 * Revision 1.1.3.6  92/07/01  14:00:11  John_Williams
 * 	ALPHA SVR4 shared libs SIA port
 * 	[92/06/29  10:39:05  John_Williams]
 * 
 * Revision 1.1.3.5  92/04/22  15:21:03  Mike_Rickabaugh
 * 	Fixed extern declaration of cap_table.
 * 	[92/04/22  15:19:23  Mike_Rickabaugh]
 * 
 * Revision 1.1.3.4  92/04/20  21:29:44  Mike_Rickabaugh
 * 	Converted cap_table to array of pointers instead of ints.
 * 	[92/04/20  21:29:17  Mike_Rickabaugh]
 * 
 * Revision 1.1.3.3  92/04/16  17:46:09  Mike_Rickabaugh
 * 	Silver BL6 merge.
 * 	[92/04/16  17:24:23  Mike_Rickabaugh]
 * 
 * Revision 1.1.4.2  92/04/13  19:08:38  devbld_gsf
 * 	First AG_BL6 version.  Moved from Ag baselevel delivery tree.
 * 
 * Revision 1.1.2.4  92/03/30  10:28:30  Sec_Proj_Michael_Fairbrother
 * 	Changed OSFsec to OSFC2
 * 	[92/03/30  09:18:42  Michael_Fairbrother]
 * 	pre submit checkin
 * 	[92/03/26  14:13:29  William_Brown]
 * 	baker check-in for ag.latest merge
 * 	[92/03/24  20:28:26  William_Brown]
 * 	pre-build check in
 * 	[92/03/13  17:43:59  William_Brown]
 * 	3/11/92 test checkin
 * 	[92/03/11  20:01:44  William_Brown]
 * 	test check in 3/10/92
 * 	[92/03/10  20:23:36  William_Brown]
 * 	SIA resubmit build
 * 	[92/03/09  18:04:29  William_Brown]
 * 	pre-build check in #2
 * 	[92/03/03  21:36:17  William_Brown]
 * 	pre-build checkin
 * 	[92/03/03  15:38:23  William_Brown]
 * 
 * Revision 1.1.2.3  92/03/26  16:54:08  William_Brown
 * 	"SIA the sequel"
 * 
 * Revision 1.1.2.2  92/02/14  15:26:52  John_Williams
 * 	for pre-submit build
 * 	[92/02/14  11:02:28  John_Williams]
 * 	Changed getpasswdbyuid to getpasswduid and getpasswdbynam to getpasswdnam
 * 	[92/02/14  09:55:54  John_Williams]
 * 	Initial SIA submit
 * 	[92/02/13  15:29:59  John_Williams]
 * 
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: siad.h,v $ $Revision: 1.1.49.2 $ (DEC) $Date: 2003/06/10 18:55:08 $
 */
/***********************************************************************
*	siad.h - SIA constants, structures, and macro definitions 
*		internally used by the interfaces and security mechanisms
************************************************************************/
#include <sia.h>
#include <dlfcn.h>

#ifndef _SIAD_H_
#define _SIAD_H_
#ifdef __cplusplus
extern "C" {
#endif
                                  
/***** Authentication types ******/

#define	SIA_A_NONE	0
#define	SIA_A_AUTH	1
#define	SIA_A_REAUTH	2
#define	SIA_A_SUAUTH	3

/*
 * Define what a "real" login is.  
 */
extern int __sia_ses_islogin __((int));
#define SIA_A_ISLOGIN(atype) (__sia_ses_islogin(atype))

/***** entity freeing parameter *****/

#define SIAREINITFREE	2	/* used when doing everything except the free
				 * of the entity structure also doesn't clear
				 * the mech specific data...
				 */
#define SIAAUTHFREE	1	/* used when freeing authentication data only */
#define SIAFREEALL	0	/* used to free the whole entity */

/***** sia initialization flags *****/
#define SIANEW	0
#define SIABAD  -1
#define SIAGOOD 1
#define SIADEF	2

/***** siad returns ********/
/*
 * In general, mechanisms are expected to return one of the following values
 * which the SIA middle layer will handle.  The sia_* routines will return 
 * either the SIASUCCESS or SIAFAIL value.
 *
 *	0 = SIADFAIL
 *	1 = SIADSUCCESS
 *	2 = SIADSTOP | SIADFAIL
 *	3 = SIADSTOP | SIADSUCCESS
 * 
 * The following are not returned by mechanisms, rather they are stored in
 * a private internal data structure which keeps track of the state of each
 * mechanism as it is run.  If the mech is not run, then bit2 will not be set.
 * Use the __sia_priv_get_state routine to access.
 *
 *	4 = SIADRUN [| SIADFAIL]
 *	5 = SIADRUN | SIADSUCCESS
 *	6 = SIADRUN | SIADSTOP | SIADFAIL
 *	7 = SIADRUN | SIADSTOP | SIADSUCCESS
/*
 * bit0 - success or fail
 */
#define SIADSUCCESS	1	/* The siad function was successful */
#define SIADFAIL	0	/* The siad function failed */

/*
 * bit1 - continue or stop 
 */
#define SIADCONTINUE	0	/* Continue to the next vectored siad function*/
#define SIADSTOP	2	/* Stop the vector processing */

/*
 * bit2 - state determination if mech was called or not
 */
#define SIADRUN		4	/* Set in state structures when mech is run */

/***** Flags for specifying changes to user account information and password **/

#define	CHGPASSWD	0x001		/* change password flag */
#define	CHGSHELL	0x002		/* change shell flag    */
#define	CHGFINGER	0x004		/* change finger flag   */
#define	CHGENTITY	0x008		/* change via siad_update_pass */
#define	CHGNEWVALUE	0x010		/* change despite siad_test_newpass */

/***** sia log formats *****/

#define	SIALOGENTFMT	"\nSIA:%s %s"	/* SIA log entry header */

/***** sia security mechanisms must match global sia_mechs table *****/
/* these names are illustrative only, and the sia_mechs table is obsolete */

#define BSD_SIA_NUM		    1
#define BSD_SIA			    "BSD"
#define DCE_NUM			    2
#define DCE                         "DCE"
#define X_509_NUM                   3
#define X_509                       "X.509"
#define OSFC2_NUM                  4
#define OSFC2                      "OSFC2"
#define NIS_NUM                     5
#define NIS                         "NIS"
#define LAST_NUM		    6
#define MATRIX_LAST                 "LAST"

/***** siad capabilities  must match global sia_capcfg_table*****/

#define	SIA_INIT		0
#define	SIAD_INIT		"siad_init"
#define SIA_CHK_INVOKER		1
#define SIAD_CHK_INVOKER	"siad_chk_invoker"
#define SIA_SES_INIT		2
#define SIAD_SES_INIT		"siad_ses_init"
#define SIA_SES_AUTHENT		3
#define SIAD_SES_AUTHENT	"siad_ses_authent"
#define	SIA_SES_ESTAB		4
#define SIAD_SES_ESTAB		"siad_ses_estab"
#define SIA_SES_LAUNCH		5
#define SIAD_SES_LAUNCH		"siad_ses_launch"
#define SIA_SES_SUAUTHENT	6
#define	SIAD_SES_SUAUTHENT	"siad_ses_suauthent"
#define SIA_SES_REAUTHENT	7
#define	SIAD_SES_REAUTHENT	"siad_ses_reauthent"
#define	SIA_CHG_FINGER		8
#define SIAD_CHG_FINGER		"siad_chg_finger"
#define SIA_CHG_PASSWORD	9
#define SIAD_CHG_PASSWORD	"siad_chg_password"
#define SIA_CHG_SHELL		10
#define SIAD_CHG_SHELL		"siad_chg_shell"
#define SIA_GETPWENT		11
#define SIAD_GETPWENT		"siad_getpwent"
#define SIA_GETPWUID		12
#define SIAD_GETPWUID		"siad_getpwuid"
#define SIA_GETPWNAM		13
#define SIAD_GETPWNAM		"siad_getpwnam"
#define SIA_SETPWENT            14
#define SIAD_SETPWENT           "siad_setpwent"
#define SIA_ENDPWENT            15
#define SIAD_ENDPWENT           "siad_endpwent"
#define SIA_GETGRENT		16
#define SIAD_GETGRENT		"siad_getgrent"
#define SIA_GETGRGID		17
#define SIAD_GETGRGID		"siad_getgrgid"
#define SIA_GETGRNAM		18
#define SIAD_GETGRNAM		"siad_getgrnam"
#define SIA_SETGRENT            19
#define SIAD_SETGRENT           "siad_setgrent"
#define SIA_ENDGRENT            20
#define SIAD_ENDGRENT           "siad_endgrent"
#define SIA_SES_RELEASE		21
#define SIAD_SES_RELEASE	"siad_ses_release"
#define SIA_CHK_USER		22
#define SIAD_CHK_USER		"siad_chk_user"
#define	_SIA_MAX_REQUIRED	SIA_CHK_USER

/* Optional (and new) mechanism indices below here 
 * NOTE: The _SIA_* defs will eventually be obsoleted by the
 *	 sia_capcfg_table 
 */
#define SIA_GET_GROUPS		23
#define SIAD_GET_GROUPS		"siad_get_groups"
#define	_SIA_GET_GROUPS		SIA_GETGRENT
#define SIA_SES_TOGGLE_PRIVS	24
#define SIAD_SES_TOGGLE_PRIVS	"siad_ses_toggle_privs"
#define	_SIA_SES_TOGGLE_PRIVS	SIA_SES_INIT
#define SIA_SES_UPDATE_AUDIT_RECORD	25
#define SIAD_SES_UPDATE_AUDIT_RECORD	"siad_ses_update_audit_record"
#define	_SIA_SES_UPDATE_AUDIT_RECORD	SIA_SES_INIT
#define	SIA_TEST_NEWPASS	26
#define	SIAD_TEST_NEWPASS	"siad_test_newpass"
#define	_SIA_TEST_NEWPASS	SIA_SES_INIT
#define	SIA_UPDATE_PASS		27
#define	SIAD_UPDATE_PASS	"siad_update_pass"
#define	_SIA_UPDATE_PASS	SIA_SES_INIT
#define	SIA_ATTR_GETENT		28
#define	SIAD_ATTR_GETENT	"siad_attr_getent"
#define	_SIA_ATTR_GETENT	SIA_SES_INIT
#define	SIA_ATTR_GETNAM		29
#define	SIAD_ATTR_GETNAM	"siad_attr_getnam"
#define	_SIA_ATTR_GETNAM	SIA_SES_INIT
#define	SIA_ATTR_QUERY		30
#define	SIAD_ATTR_QUERY		"siad_attr_query"
#define	_SIA_ATTR_QUERY		SIA_SES_INIT
#define	SIA_ATTR_ENDENT		31
#define	SIAD_ATTR_ENDENT	"siad_attr_endent"
#define	_SIA_ATTR_ENDENT	SIA_SES_INIT
#define	SIA_ATTR_SETENT		32
#define	SIAD_ATTR_SETENT	"siad_attr_setent"
#define	_SIA_ATTR_SETENT	SIA_SES_INIT
#define	SIA_ATTR_PUTENT		33
#define	SIAD_ATTR_PUTENT	"siad_attr_putent"
#define	_SIA_ATTR_PUTENT	SIA_SES_INIT
/* Add new indices right here */

/*
 * The following structure describes the entries in the sia_cap array/table
 * listed later in this file.  When new capabilities are added to the above
 * list of mechanism indices and names, the sia_cap array/table must be
 * updated to include the new routine using the following definitions:
 *
 * 	capind
 *		SIA_* index from above list to indicate the index of the
 *		the current capability.
 *
 *	reqcapind
 *		SIA_* index of the mechanism capability that is required to 
 *		be present within the mechanism for this capability to be 
 *		supported. 
 *
 *		For required capabilities, this is the index of the capability
 *		that is responsible for "allocating" or "initializing" the
 *		state for the rest of the capabilities within the group. In
 *		this case, if the "base capability" does not exist, then 
 *		there is no reason to even attempt the dlopen()/dlsym() to
 *		find the capability within a mechanism. Currently there are
 *		5 different styles of capabilities:
 *
 *			Session, Data Fetch, Change, Attr, and Other.
 *
 *		For optional capabilities, this is the index of a required
 *		capability that must be present in the mechanism in order to 
 *		support the optional capability.
 *	
 *	cap_name
 *		Name of the capability routine.  This is used during dlopen() 
 *		and dlsym() calls to look up the capability in the mechanism 
 *		by name.
 *
 */
typedef struct sia_cap_ent_t {
	int	capind;
	int	reqcapind;
	char	*cap_name;
} sia_cap_ent_t;


/***** sia macros ********/

#define SIALOG	sia_log


/*	SIA mutex locks		*/

#define SIA_ENTITY_LOCK		1 /* lock for allocation and freeing entities*/
#define SIA_LOG_LOCK		2 /* lock for writing log entries	*/ 
#define SIA_AUTHENT_LOCK	3 /* locks authentication processes 	*/
#define SIA_ESTAB_LOCK		4 /* locks session establishment    	*/
#define SIA_LAUNCH_LOCK		5 /* locks session launching	    	*/
#define SIA_INIT_LOCK		6 /* locks SIA initialization		*/
#define SIA_CHANGE_LOCK		7 /* change finger,shell,password mutex	*/
#define SIA_GROUP_LOCK          8 /* locks SIA getgr* calls             */
#define SIA_PASSWD_LOCK         9 /* locks SIA getpw* calls             */
#define SIA_SES_LOCK           10
#define SIA_MAT_LOCK	       11 /* lock for sia_mat_init()		*/
#define SIA_AI_LIST_LOCK       12 /* locks ai_list			*/

/***** sia collect definitions *****/

/***** sia collect routine interface definition *****/

/*
extern int sia_collect (
        int             timeout,
        int             rendition,
        unsigned char   *title,
        int             num_prompts,
        prompt_t        *prompt);
*/

/* MAX_PROMPTS is obsolete and never was accurate.  The collection routine
 * should believe the num_prompts parameter.
 */
#define MAX_PROMPTS	8

/*	timeout - how long to wait for user    */
/* 	if 0 then wait forever if nonzero then */
/*	that number of seconds		       */

#define	SIAWAITFOREVER	0
#define SIAONEMIN	60
#define	SIA_DEF_TIMEOUT	(2*60)

/*	rendition - how to run the parameter collection */
/*							*/

#define SIAMENUONE      1	/* select one of the choices given */
#define SIAMENUANY      2	/* select any of the choices given */
#define SIAFORM         3	/* fill out the form */
#define SIAONELINER     4	/* One question with one answer */
#define SIAINFO         5	/* Information only */
#define SIAWARNING      6	/* ERROR or WARNING message  (possibly usage)*/
#define LAST_RENDITION  6

/*** collect return values ***/

#define SIACOLSUCCESS   1       /* the collection was successful */
#define SIACOLABORT     2       /* the collection was aborted */
#define SIACOLTIMOUT    3       /* the collection timed out */
#define SIACOLPARAMS    4       /* bad parameters to sia_collect */


/* control_flags are used to control the display a bit */

/*	NOTE: non-NULL result pointer => a selected menu item */

#define SIARESINVIS     0x2     /*result is invisible */
#define SIARESANY       0x10    /*result can contain any ASCII chars*/
#define SIAPRINTABLE    0x20    /*result can contain only printable chars*/
#define SIAALPHA        0x40    /*result can contain only letters */
#define SIANUMBER       0x80    /*result can contain only numbers*/
#define SIAALPHANUM     0x100   /*result can contain only letters and numbers*/
#define FLAG_MAX        0x200

/* Context structures. */

struct mech_contexts {
	void *value;
#ifdef __cplusplus
	void (*destructor)(...);
#else
	void (*destructor)();
#endif
};

struct sia_context {
	FILE *fp;
	union {
	struct group *group;
	struct passwd *pass;
	} value;
	int pkgind;
	unsigned buflen;
	char *buffer;
	void *rsrv1;
	void *rsrv2;
	/* this array may be longer -- see __sia_sw_max */
	struct mech_contexts mech_contexts[SIASWMAX];
};
/* See also sia_alloc_context() and sia_free_context(). */

extern  int siad_init __((void));
extern  int siad_chk_invoker __((void));
extern  int siad_ses_init __((SIAENTITY *, int));
extern  int siad_ses_authent __((sia_collect_func_t *,
				 SIAENTITY *, int, int));
extern  int siad_ses_estab __((sia_collect_func_t *,
			       SIAENTITY *, int));
extern  int siad_ses_launch __((sia_collect_func_t *,
				SIAENTITY *, int));
extern  int siad_ses_suauthent __((sia_collect_func_t *,
				   SIAENTITY *, int, int));
extern  int siad_ses_reauthent __((sia_collect_func_t *,
				   SIAENTITY *, int, int));
extern  int siad_chg_finger __((sia_collect_func_t *,
				const char *, int, char *[]));
extern  int siad_chg_password __((sia_collect_func_t *,
				  const char *, int, char *[]));
extern  int siad_chg_shell __((sia_collect_func_t *,
			       const char *, int, char *[]));
extern	int siad_test_newpass __((sia_collect_func_t *,
				  SIAENTITY *, int, const char *));
extern	int siad_update_pass __((sia_collect_func_t *,
				 SIAENTITY *, int, const char *));
extern int siad_getpwent __((struct passwd *, char *, int,
			     struct sia_context *));
extern int siad_getpwuid __((uid_t, struct passwd *, char *, int,
			     struct sia_context *));
extern int siad_getpwnam __((const char *, struct passwd *, char *, int,
			     struct sia_context *));
extern int siad_setpwent __((struct sia_context *));
extern int siad_endpwent __((struct sia_context *));
extern int siad_getgrent __((struct group *, char *, int,
			     struct sia_context *));
extern int bsd_siad_getpwnam __((const char *, struct passwd *, char *, int));
extern int bsd_chg_it __((sia_collect_func_t *,
			  struct passwd *, uid_t, char *, int));
extern int bsd_upd_it __((sia_collect_func_t *,
			  struct passwd *, uid_t, const char *, int,
			  const char *));
extern int siad_getgrgid __((gid_t, struct group *, char *, int,
			     struct sia_context *));
extern int siad_getgrnam __((const char *, struct group *, char *, int,
			     struct sia_context *));
extern int siad_setgrent __((struct sia_context *));
extern int siad_endgrent __((struct sia_context *));
extern int siad_ses_release __((SIAENTITY *, int));
extern int siad_chk_user __((const char *, int));
extern int siad_get_groups __((struct sia_context *,
			       const char *, gid_t *, int *, int));
extern void siad_ses_toggle_privs __((SIAENTITY *, int, int));
extern void siad_ses_update_audit_record __((SIAENTITY *,
					     int, int, char *, char **,
					     int *, int));
extern int siad_attr_getnam __((SIAENTITY *, int, char *, uint_t, uint_t));
extern int siad_attr_query __((SIAENTITY *, int, SIA_AI_PKT **, size_t));
extern int siad_attr_getent __((SIAENTITY *, int, uint_t, uint_t));
extern int siad_attr_endent __((SIAENTITY *, int));
extern int siad_attr_setent __((SIAENTITY *, int));
extern int siad_attr_putent __((SIAENTITY *, int, SIA_AI_PKT *));

extern int sia_make_entity_pwd __((struct passwd *, SIAENTITY *));
union sia_get_params;	/* forward */
#ifdef __cplusplus
  extern int sia_setupfp __((int, int, int (*)(...)));
  extern int sia_switch __((int, union sia_get_params *, int (*[])(...)));
  extern int sia_switch_session __((int, int (*)(...), SIAENTITY *, ...));
  extern int sia_switch_change __((int, int (*)(...), sia_collect_func_t *, 
				char *, int, int, char **));
#else
  extern int sia_setupfp __((int, int, int (*)()));
  extern int sia_switch __((int, union sia_get_params *, int (*[])()));
  extern int sia_switch_session __((int, int (*)(), SIAENTITY *, ...));
  extern int sia_switch_change __((int, int (*)(), sia_collect_func_t *, 
				char *, int, int, char **));
#endif
extern int sia_audit __((u_int, ...));
extern int sia_chdir __((const char *, time_t));
extern int sia_check_sysenv __((int *));
extern void sia_restore_sysenv __((int *));
extern int sia_timed_action __((int (*)(void *), void *, time_t));
extern char *sia_getamsg __((const char *, int, int, const char *));

extern int sia_log __((const char *, const char *, ...));
extern int sia_warning __((sia_collect_func_t *, const char *, ...));
extern int sia_init __((void));
extern int __sia_isagroup __((gid_t, gid_t *, int));
extern char *__sia_ses_latinfo __((const char *));
extern int __sia_read_lastlog __((sia_collect_func_t *, uid_t, struct lastlog *));
extern void __sia_ses_toggle_privs __((SIAENTITY *, int));
extern void __sia_ses_update_audit_record __((SIAENTITY *,
					      int, char *, char **,
					      int *, int));
extern int sia_getgroup __((int, int, union sia_get_params *));
extern int sia_getpasswd __((int, int, union sia_get_params *));
extern struct sia_context *sia_alloc_context __((void));
extern void sia_free_context __((struct sia_context *));
extern int sia_mat_init __((void));
extern char *sia_mat_get_libnam __((int, int));
extern int sia_mat_get_pkgind __((char const *));
extern char *sia_mat_get_pkgnam __((int, int));
extern int __sia_free_ai(SIAENTITY *, SIA_AI_PKT **, uint_t);
extern int __sia_do_token(SIAENTITY *, void  *, size_t, char, char *, int);
extern int __sia_attr_query_cmn(SIA_AI_PKT **, size_t, int *, int);
extern int __sia_update_grouplist __((gid_t, gid_t *, int *, int,
				      const char * const *,
				      const char *, size_t));
/* These are really 'noncompat', in that they bypass /etc/passwd for the
 * 'real' backing-store without local overrides.  In other words, these
 * go directly to nsswitch's passwd_compat dbtype, bypassing "passwd: compat".
 */
extern int getpwnam_compat __((const char *, struct passwd *, char *, size_t,
			       struct sia_context *, struct passwd **, int *));
extern int getpwuid_compat __((uid_t, struct passwd *, char *, size_t,
			       struct sia_context *, struct passwd **, int *));
/* Maybe move these next two to <pwd.h> some day. */
extern int getpwnam_nis __((const char *, struct passwd *, char *, size_t,
			    struct passwd **));
extern int getpwuid_nis __((uid_t, struct passwd *, char *, size_t,
			    struct passwd **));

/**** sia globals and externs ****/
/*
 * only defined in sia_init.c.
 */

#ifdef SIAGLOBAL /****** only defined in sia_init.c *****/


struct sia_matrix_t __sia_matrix;
int	sia_initialized=SIANEW;
int	__sia_sw_max=0;
ldr_module_t    sia_handle=NULL;
char const *__sia_lib_helper = "/usr/shlib/libsecurity.so";

/*
 * The following is a list of SIA "capabilities" (routines) that maps to the
 * SIA matrix.conf file. Each of the "required" entries in the table must be
 * present in a mechanism in order for the mechanism to be loaded successfully.
 * Even if the routine simply returns SIADFAIL, the capability must exist.
 * The entries are listed by package index, required index, and name. The
 * entries with the same pkgind and reqind value means that each of the
 * capabilities must be in the mechanism. In order to preserve compatibility 
 * over time and to allow for support of new mechanism functionality, optional
 * SIA routine support was added.  Optional routines require that the mechanism
 * supports some "required" capability. This indicates the linkage between the
 * optional and required routine.
 */ 
struct sia_cap_ent_t const sia_capcfg_table[] = {
/*
 * The first set of indices are for the required entries. If any of these
 * capabilities is missing from the mechanism, the mechanism will not be
 * loaded. For the 'reqcapind' column and "required" routines, make sure to 
 * select an index which represents a capability upon which the current
 * index would rely on. The following capabilities must be called prior to
 * the subsequent listed capabilities.  For example, in order to call
 * SIA_SES_AUTHENT, the SIA_SES_INIT routine must have been already called.
 * If not, the setup routines will return SIAFAIL without attempting to 
 * locate the capability routine in the mechanism.
 *
 * SIA_SES_INIT: (must be called prior to)
 *	SIA_SES_*AUTHENT, SIA_SES_ESTAB, SIA_SES_LAUNCH, and SIA_SES_RELEASE
 *
 * SIA_CHK_USER:
 *	SIA_CHG_SHELL, SIA_CHG_FINGER, and SIA_CHG_PASSWORD
 *
 * SIA_SETPWENT:
 *	SIA_GETPWENT and SIA_ENDPWENT
 *
 * SIA_SETGRENT:
 *	SIA_GETGRENT and SIA_ENDGRENT
 */
/* capind, reqcapind, cap_name */
{SIA_INIT, SIA_INIT, SIAD_INIT},
{SIA_CHK_INVOKER, SIA_CHK_INVOKER, SIAD_CHK_INVOKER},
{SIA_SES_INIT, SIA_SES_INIT, SIAD_SES_INIT},
{SIA_SES_AUTHENT, SIA_SES_INIT, SIAD_SES_AUTHENT},
{SIA_SES_ESTAB, SIA_SES_INIT, SIAD_SES_ESTAB},
{SIA_SES_LAUNCH, SIA_SES_INIT, SIAD_SES_LAUNCH},
{SIA_SES_SUAUTHENT, SIA_SES_INIT, SIAD_SES_SUAUTHENT},
{SIA_SES_REAUTHENT, SIA_SES_INIT, SIAD_SES_REAUTHENT},
{SIA_CHG_FINGER, SIA_CHK_USER, SIAD_CHG_FINGER},
{SIA_CHG_PASSWORD, SIA_CHK_USER, SIAD_CHG_PASSWORD},
{SIA_CHG_SHELL, SIA_CHK_USER, SIAD_CHG_SHELL},
{SIA_GETPWENT, SIA_SETPWENT, SIAD_GETPWENT},
{SIA_GETPWUID, SIA_GETPWUID, SIAD_GETPWUID},
{SIA_GETPWNAM, SIA_GETPWNAM, SIAD_GETPWNAM},
{SIA_SETPWENT, SIA_SETPWENT, SIAD_SETPWENT},
{SIA_ENDPWENT, SIA_ENDPWENT, SIAD_ENDPWENT},
{SIA_GETGRENT, SIA_SETGRENT, SIAD_GETGRENT},
{SIA_GETGRGID, SIA_GETGRGID, SIAD_GETGRGID},
{SIA_GETGRNAM, SIA_GETGRNAM, SIAD_GETGRNAM},
{SIA_SETGRENT, SIA_SETGRENT, SIAD_SETGRENT},
{SIA_ENDGRENT, SIA_ENDGRENT, SIAD_ENDGRENT},
{SIA_SES_RELEASE, SIA_SES_INIT, SIAD_SES_RELEASE},
{SIA_CHK_USER, SIA_CHK_USER, SIAD_CHK_USER},
							
/*
 * Below this point are all the optional groups.  Mechanism routines do not
 * have to support these routines; however, if they do, then they must support
 * the routine listed (by index) in the center column
 *
 * For the optional routines, the 'reqcapind' is the capability index that must
 * be present in the mechanism to support the specific capability. Thus in 
 * order support SIA_GET_GROUPS, the mechanism would have to support the
 * SIA_GETGRENT capability.
 */
{SIA_GET_GROUPS, SIA_GETGRENT, SIAD_GET_GROUPS},
{SIA_SES_TOGGLE_PRIVS, SIA_SES_INIT, SIAD_SES_TOGGLE_PRIVS},
{SIA_SES_UPDATE_AUDIT_RECORD, SIA_SES_INIT, SIAD_SES_UPDATE_AUDIT_RECORD},
{SIA_TEST_NEWPASS, SIA_SES_INIT, SIAD_TEST_NEWPASS},
{SIA_UPDATE_PASS, SIA_SES_INIT, SIAD_UPDATE_PASS},
{SIA_ATTR_GETENT, SIA_SES_INIT, SIAD_ATTR_GETENT},
{SIA_ATTR_GETNAM, SIA_SES_INIT, SIAD_ATTR_GETNAM},
{SIA_ATTR_QUERY, SIA_SES_INIT, SIAD_ATTR_QUERY},
{SIA_ATTR_ENDENT, SIA_SES_INIT, SIAD_ATTR_ENDENT},
{SIA_ATTR_SETENT, SIA_SES_INIT, SIAD_ATTR_SETENT},
{SIA_ATTR_PUTENT, SIA_SES_INIT, SIAD_ATTR_PUTENT},
{NULL, NULL, NULL}
};

int const __sia_cap_max = (sizeof sia_capcfg_table / 
				sizeof *sia_capcfg_table) - 1;

/* 
 * The following are the to be OBSOLETED at some time in the future 
 * sia_caps[] and sia_opt_groups[] arrays. They are replaced by the 
 * above sia_capcfg_table.
 */
char const *const sia_caps[] = {
  SIAD_INIT,
  SIAD_CHK_INVOKER,
  SIAD_SES_INIT,
  SIAD_SES_AUTHENT,
  SIAD_SES_ESTAB,
  SIAD_SES_LAUNCH,
  SIAD_SES_SUAUTHENT,
  SIAD_SES_REAUTHENT,
  SIAD_CHG_FINGER,
  SIAD_CHG_PASSWORD,
  SIAD_CHG_SHELL,
  SIAD_GETPWENT,
  SIAD_GETPWUID,
  SIAD_GETPWNAM,
  SIAD_SETPWENT,
  SIAD_ENDPWENT,
  SIAD_GETGRENT,
  SIAD_GETGRGID,
  SIAD_GETGRNAM,
  SIAD_SETGRENT,
  SIAD_ENDGRENT,
  SIAD_SES_RELEASE,
  SIAD_CHK_USER,
  SIAD_GET_GROUPS,
  SIAD_SES_TOGGLE_PRIVS,
  SIAD_SES_UPDATE_AUDIT_RECORD,
  SIAD_TEST_NEWPASS,
  SIAD_UPDATE_PASS,
  SIAD_ATTR_GETENT,
  SIAD_ATTR_GETNAM,
  SIAD_ATTR_QUERY,
  SIAD_ATTR_ENDENT,
  SIAD_ATTR_SETENT,
  SIAD_ATTR_PUTENT,
  NULL
};

int const __sia_opt_groups[(sizeof sia_caps / sizeof *sia_caps) -
			   _SIA_MAX_REQUIRED] =
	{
		_SIA_GET_GROUPS,
		_SIA_SES_TOGGLE_PRIVS,
		_SIA_SES_UPDATE_AUDIT_RECORD,
		_SIA_TEST_NEWPASS,
		_SIA_UPDATE_PASS,
		_SIA_ATTR_GETENT,
		_SIA_ATTR_GETNAM,
		_SIA_ATTR_QUERY,
		_SIA_ATTR_ENDENT,
		_SIA_ATTR_SETENT,
		_SIA_ATTR_PUTENT,
		0
};

/* End of to be OBSOLETED arrays */

#else /* SIAGLOBAL */

extern  struct sia_matrix_t __sia_matrix;
extern  int sia_initialized;
extern	int __sia_sw_max;
extern	int const __sia_cap_max;
extern  ldr_module_t sia_handle;
extern	char const *__sia_lib_helper;
extern 	struct sia_cap_ent_t const sia_capcfg_table[];
/* The following 2 entries will be OBSOLETED at some time in the future */
extern char const *const sia_caps[];
extern	int const __sia_opt_groups[];

extern  int siad_group[];
extern  int siad_passwd[];

#endif /* SIAGLOBAL */

#ifdef _THREAD_SAFE
#include <ts_supp.h>
extern TIS_MUTEX_T sia_mutex[SIAMUTMAX];
#endif	/* _THREAD_SAFE */

/* Get call switching */
#define G_ENT	0
#define G_GID	1
#define G_NAM	2
#define G_SET   3
#define G_END   4

#define P_ENT	0
#define P_UID	1
#define P_NAM	2
#define P_SET   3
#define P_END   4

#define REENTRANT       1
#define NON_REENTRANT   0

typedef struct {
  char *name;
  gid_t gid;
  int unused;
  struct group *result;
  char *buffer;
  int len;
  int pkgind;
} group_params;

typedef struct {
  char *name;
  uid_t uid;
  int unused;
  struct passwd *result;
  char *buffer;
  int len;
  int pkgind;
} passwd_params;

union sia_get_params {
  group_params group;
  passwd_params passwd;
  struct {
    void *ct_ent_id;
    void *ct_nam;
  } context;
};

#define sia_matrix	__sia_matrix.matrix_ent

extern	const char * __bsd_group_last_nss __((int, struct sia_context *));
extern	const char * __bsd_passwd_last_nss __((int, struct sia_context *));

extern	int __bsd_passwd_lastmatch;	/* deprecated--not thread-safe */
extern	int __bsd_group_lastmatch;	/* deprecated--not thread-safe */

extern	int __bsd_passwd_lastfound __((void));
extern	int __bsd_group_lastfound __((void));
extern	int __bsd_passwd_lastfound_ctx __((struct sia_context *));
extern	int __bsd_group_lastfound_ctx __((struct sia_context *));

#define	BSD_FOUND_LOCAL		1	/* purely local entry */
#define	BSD_FOUND_PLUS		2	/* +user: or +group: */
#define	BSD_FOUND_NETGR		3	/* +@netgroup: */
#define	BSD_FOUND_WILD		4	/* +: */
#define	BSD_FOUND_HOWMASK	0x000f	/* mask for how-found values */
#define	BSD_LOCAL_PASS		0x0010	/* local-override in password field */
#define	BSD_LOCAL_MEMBERS	0x0020	/* l.-o. in gr_mem field */
#define	BSD_LOCAL_GECOS		0x0040	/* l.-o. in pw_gecos field */
#define	BSD_LOCAL_HOMEDIR	0x0080	/* l.-o. in pw_dir field */
#define	BSD_LOCAL_SHELL		0x0100	/* l.-o. in pw_shell field */
#define	BSD_LOCAL_OVMASK	0x0ff0	/* mask for local override bits */
#define	BSD_FOUND_NSS0		0x1000	/* start of files/nis/ldap/etc bits */


/***** sia thread locking *****/
#ifdef _THREAD_SAFE


#define SIATHREADLOCK(x) 	TS_LOCK(&sia_mutex[(x)]);
#define SIATHREADREL(x)		TS_UNLOCK(&sia_mutex[(x)]);

#else /* _THREAD_SAFE */

#define SIATHREADLOCK(x)
#define SIATHREADREL(x)

#endif /* _THREAD_SAFE */


/* sia matrix definitions */

#ifndef SIA_MATRIX_H
#define SIA_MATRIX_H
#endif /* SIA_MATRIX_H */

typedef struct sia_matrix_ent {	   /* sia matrix conf entry */
  char *libnam;
  char *pkgnam;   
#ifdef __cplusplus
  int (*fp)(...); 
#else
  int (*fp)(); 
#endif
} sia_matrix_ent;		   
			
typedef struct sia_matrix_t {
  time_t             matrix_date; /* Last mod date of matrix.conf */
  sia_matrix_ent     **matrix_ent;
  struct stat	     matstat;
} sia_matrix_t;

/*
 * The following definitions are for the interfaces to 
 * the private SIA data structure.
 */

/*
 * The following defintions and routines manipulate a flags 'int'.
 *
 * The SUC_LOGIN_DISP flag controls whether or not a mechanism has displayed 
 * (or wishes to have displayed) the last successful login time. If none of 
 * the mechanisms set the flag, then the SIA local mechanism will perform
 * the display.
 *
 * The SIA_CONSOLE_LOGIN flag is set during sia_ses_init() when it is 
 * determined that the session is attempting to login using the console
 *
 * When the SIA_NETAUTH_SELF_AUDIT is set and we have a network authentication
 * taking place, the SIA Session Authentication code will reenable "self
 * auditing". This allows network applications such as telnet, rcp, rsh,
 * rlogin, etc. to provide more detailed audit information about the
 * incoming request
 *
 * When the SIA_NETAUTH_AUDAUTH is set, the session authentication code will
 * audit the successful authentication rather than waiting for the session
 * launch code (which doesn't get run for network application authentication).
 *
 * When the SIA_IGN_LOC_ESTAB flag is set, the local mechanism code for the
 * establish phase is not run. This includes checking /etc/nologin, disk quota
 * checks, license checks, and display of lastlog information. The only code
 * not ignored is the setting of the login uid (setluid()).
 *
 * When the SIA_IGN_LOC_LAUNCH flag is set, the local mechanism code for the
 * launch phase is not run.  This includes calls to setgid(), initgroups(),
 * updating lastlog/utmp, setting terminal ownership and protections, setting
 * effective uid, and changing to user's home directory. The only code not
 * ignored is the setting of the login name (setlogin()).
 *
 */
#define SUC_LOGIN_DISP	0x0001	
#define SIA_CONSOLE_LOGIN 0x0002
#define SIA_NETAUTH_SELF_AUDIT 0x0004
#define SIA_NETAUTH_AUDAUTH 0x0008
#define SIA_IGN_LOC_ESTAB 0x0010
#define SIA_IGN_LOC_LAUNCH 0x0020

/*
 * The following routines takes 3 parameters, the first 2 are the entity and
 * current package index.  The third parameter is the to be manipulated. 
 */
void __sia_priv_set_flag __((SIAENTITY *, int, int));
void __sia_priv_clear_flag __((SIAENTITY *, int, int));

/* 
 * The following routine will return the 'int' value in the flags field. 
 * It takes 2 parameters, the entity and the current package index
 */
int __sia_priv_get_flag __((SIAENTITY *, int)); 

#ifdef __cplusplus
}
#endif
#endif /* _SIAD_H_ */

