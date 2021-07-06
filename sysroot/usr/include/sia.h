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
/***** Until this works its commented out dupdef in Date variable
***#ifndef lint
***static char *rcsid = "@(#)$RCSfile: sia.h,v $ $Revision: 1.1.57.1 $ (DEC) $Date: 2001/10/01 19:16:36 $";
***#endif
***************/
/***********************************************************************
*	sia.h - SIA constants, structures, and macro definitions 
************************************************************************/
#ifndef _SIA_H_
#define _SIA_H_
#ifdef __cplusplus
extern "C" {
#endif

/***** sia common sys includes **/
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <sys/sem.h>
#include <sys/uio.h>
#include <sys/audit.h>

/***** sia common usr includes **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sgtty.h>
#include <utmp.h>
#include <signal.h>
#include <pwd.h>
#include <grp.h>
#include <lastlog.h>
#include <errno.h>
#include <ttyent.h>
#include <syslog.h>
#include <limits.h>
#include <strings.h>
#include <loader.h>
#include <nl_types.h>

#ifdef _THREAD_SAFE
#ifndef __BRAVO_DISABLED__
#include <cma.h>
#endif
#include <pthread.h>
#endif

/**** sia logical definitions ****/

#ifndef	NULL
#define NULL 0L
#endif
#ifndef	YES
#define YES 1
#endif
#ifndef	NO
#define NO 0
#endif
#ifndef	TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/**** sia library and filenames ****/

#define SIALOGFILE      "/var/adm/sialog"          /* SIA logging file       */
#define SIAIGOODFILE    "/etc/sia/siainitgood"     /* siainit good file flag */
#define MATRIX_CONF     "/etc/sia/matrix.conf"     /* sia matrix config file */
#define SIALIBCSO       "libc.so"                  /* local security in libc */

/***** sia limits ***********/

#define SIABUFSIZ       1024    /* buffer size for loginname, password, and  */
                                /* one line of the SIA matrix config file    */
#define SIAPKGNAMAX     64      /* Libsia packagename maximum size           */
#define SIALIBNAMAX     64      /* Libsia packagename maximum size           */
/* This next is obsolete -- the sia_caps array is NULL-terminated.  See also
 * __sia_cap_max (in siad.h).
 */
#define SIADCAPMAX      32      /* max sec mech sia capabilities             */
/* This next is obsolete -- If you really need to know, see __sia_sw_max     */
#define SIASWMAX        4       /* max switches per capability               */
#define SIAMUTMAX       16      /* number mutexes utilized by SIA            */
#define SIAMXACCTNAME   64      /* maximum size of an account name           */
#define SIAMXPASSWORD   80      /* maximum size of a password                */
#define SIANAMEMIN      16      /* minimum space allocated for entity->name  */


typedef struct sia_ai_packet {
        int  token;           /* tkn number */
                /*equate the token number with the msg cat and the
                * look up by type, see SIA_T_IDX.
                */
        int  toktype;		/* token data type */
        void *tokval;		/* token data */
	char tokstat;
        char **responders;      /* list of strings of who answered. */
        char *litstring;        /* see prot.h for definitions */
        char *msglabel;
        char *msghelp;
        void *reserved1;
        void *reserved2;
        void *reserved3;
        void *reserved4;
        void *reserved5;
}SIA_AI_PKT;

/* sia_attr_query() block allocates SIA_E_AI_LIST[]. reserved[1-5] provide
*  future expansion/backwards compatility.
*/ 

/* responders field components/answers */
#define SIA_T_BSD_STR "bsd"
#define SIA_T_EHNANCED_STR "enhanced"
#define SIA_T_DB_DEFAULT 'd'
#define SIA_T_DB_PRIMARY 'p'
#define SIA_T_DB_NONE 'n'
#define SIA_T_DB_UNKNOWN '?'

#define SIA_T_DBA_PRIMARY 0x1
#define SIA_T_DBA_DEFAULT 0x2

#define IS_PDBA(dba)((dba) & SIA_T_DBA_PRIMARY)
#define IS_DDBA(dba)((dba) & SIA_T_DBA_DEFAULT)

/* see SIA_T_IDX */
#define SIA_IDX_BSD 1
#define SIA_IDX_ENHANCED 2

/* token type_values */
#define SIA_TT_INT              0x1
#define SIA_TT_PPSTR            0x2
#define SIA_TT_CHAR             0x3
#define SIA_TT_TIME             0x4
#define SIA_TT_UID              0x5
#define SIA_TT_GID              0x6
#define SIA_TT_UINT             0x7
#define SIA_TT_UCHAR            0x8
#define SIA_TT_ULONG            0x9
#define SIA_TT_LONG             0xA
#define SIA_TT_MAND_IR		0xB  /* no op, TBI */

/*#define SIA_TT_MASKT
* #define SIA_TT_PRIV  
*/

/* what field to fill in or remove for [qgs]attr response parameter*/
#define SIA_AI_ALL              0xFFFFFFFFF
#define SIA_AI_TOKEN            0x1
#define SIA_AI_RESPONDER        0x2  /* responders, cleans out tokval too */
#define SIA_AI_LITSTR           0x4  /* literal  string */
#define SIA_AI_MSGLABEL         0x8
#define SIA_AI_MSGHELP          0x10  /* help message */
#define SIA_AI_TOKENTYPE        0x100 /* token data type */
#define SIA_AI_VALUE            0x200 /* attribute value */
#define SIA_AI_BLKZERO          0x400 /* zero the ai_list*/
#define SIA_AI_BLKFREE          0x800 /* free the ai_list, must zero if free */
#define SIA_AI_FLIST            SIA_AI_MSGLABEL|SIA_AI_MSGHELP|SIA_AI_RESPONDER
#define SIA_AI_KEEPZBLK         SIA_AI_MSGLABEL|SIA_AI_MSGHELP|SIA_AI_RESPONDER|SIA_AI_BLKZERO


/* Token status */
#define SIA_TS_UNANSWERED '\000'
#define SIA_TS_ANSWERED 'a'
#define SIA_TS_AMBIGUOUS 'd'
#define SIA_TS_NOTSET 'n'
#define SIA_TS_UNKNOWN '?'

/* number of possible token types */
#define SIA_TT_LIMIT	1024

/* number of tokens that can be used at one time -1 */
#define SIA_NT_LIMIT	1024

/* TU - token user db */
typedef enum sia_t_idx {	/* /etc/passwd first */
   SIA_TU_PWNAME=1,		/* char *pw_pwname, fd_name */
   SIA_TU_PWD,			/* char *pw_pwd, fd_encrypt */
   SIA_TU_UID,			/* uid_t pw_uid, fd_uid */
   SIA_TU_GID,			/* gid_t pw_gid */
   SIA_TU_COMMENT,		/* char * for future SysV compatibility */
   SIA_TU_QUOTA,		/* int for future SysV compatibility */
   SIA_TU_GECOS,		/* char *pw_gecos */
   SIA_TU_DIR,			/* char *pw_dir */
   SIA_TU_SHELL,		/* char *pw_shell */
   SIA_TU_OWNER,		/* char *, start enhanced 'd' indicates defaults also */
   SIA_TU_PRIORITY,		/* int fd_nice */
   SIA_TU_CMDPRIV,		/* char *, NOT mask_t * */
   SIA_TU_SYSPRIV,		/* char *, NOT priv_t * */
   SIA_TU_BASEPRIV,		/* char *, NOT priv_t * */
   SIA_TU_AUDITDISP,		/* char * */
   SIA_TU_AUDITCNTL,		/* uint_t */
   SIA_TU_MINCHG,		/* time_t */
   SIA_TU_MINLEN,		/* int */
   SIA_TU_MAXLEN,		/* int */
   SIA_TU_EXP,			/* time_t fd_expire */
   SIA_TU_LIFE,			/* time_t fd_lifetime */
   SIA_TU_SUCCHG,		/* time_t fd_schange */
   SIA_TU_UNSUCCHG,		/* time_t fd_uchange */
   SIA_TU_PICKPWD,		/* char fd_pick_pwd */
   SIA_TU_GENPWD,		/* char fd_gen_pwd */
   SIA_TU_RESTRICT,		/* char */ 
   SIA_TU_POLICY,		/* char */
   SIA_TU_NULLPW,		/* char */
   SIA_TU_PWCHANGER,		/* uid_t */
   SIA_TU_GENCHARS,		/* char fd_gen_chars */
   SIA_TU_GENLETTERS,		/* char fd_gen_letters */
   SIA_TU_PWDEPTH,		/* int */
   SIA_TU_PWDICT,		/* char * */ 
   SIA_TU_OLDCRYPT,		/* char */
   SIA_TU_NEWCRYPT,		/* char */
   SIA_TU_CLEARANCE,		/* mand_ir_t * */
   SIA_TU_SUCLOG,		/* time_t fd_slogin */
   SIA_TU_UNSUCLOG,		/* time_t fd_ulogin */
   SIA_TU_SUCTTY,		/* char * */
   SIA_TU_NUMUNSUCLOG,		/* int fd_nlogins */
   SIA_TU_UNSUCTTY,		/* char * */
   SIA_TU_TOD,			/* char * */
   SIA_TU_MAXTRIES,		/* int fd_max_tries */
   SIA_TU_UNLOCK,		/* time_t fd_unlockint */
   SIA_TU_RETIRED,		/* char */
   SIA_TU_LOCK,			/* char */
   SIA_TU_EXPDATE,		/* time_t */
   SIA_TU_ISTEMPLATE,		/* char */
   SIA_TU_TEMPLATE,		/* char * */
   SIA_TU_VAC_START,		/* time_t */
   SIA_TU_VAC_END,		/* time_t */
   SIA_TU_RLIMIT_CPU,		/* ulong_t fd_rlim_cpu */
   SIA_TU_RLIMIT_FSIZE,		/* ulong_t fd_rlim_fsize */
   SIA_TU_RLIMIT_DATA,		/* ulong_t fd_rlim_data */
   SIA_TU_RLIMIT_STACK,		/* ulong_t fd_rlim_stack */
   SIA_TU_RLIMIT_CORE,		/* ulong_t fd_rlim_core */
   SIA_TU_RLIMIT_RSS,		/* ulong_t fd_rlim_rss */
   SIA_TU_RLIMIT_NOFILE,	/* ulong_t fd_rlim_nofile */
   SIA_TU_RLIMIT_VMEM,		/* ulong_t fd_rlim_vmem */
   SIA_TU_MAX_LOGIN_INT,	/* time_t */
   SIA_TU_GRACE_LIMIT,		/* time_t */
   SIA_TU_PSW_CHG_REQD,		/* char */
   SIA_TU_GEN_SITE,		/* char */
   SIA_TU_MINCHOSEN,		/* uchar_t */
   SIA_TU_MAXCHOSEN,		/* uchar_t */
   SIA_TU_FLOGINS,		/* int */
   SIA_TU_PWDSTAT		/* fake token */
} SIA_T_IDX;

/**** Network Authentication ****/

/*
 * The following structure is to be used by applications wishing to support
 * the ability to authenticate an entity via some network authentication
 * mechanism such as Kerberos. Applications will use the SIA routine
 * sia_alloc_netauth() to allocate a netauth structure and then will fill
 * in the appropriate fields.  This structure should be passed to the session
 * initialization routine (sia_ses_init) in the 8th argument (gssapi). The
 * session initialization routine will store the address of the structure
 * in the entity->gssapi field.  The entity is then passed to each mechanism.
 *
 * netappid	=> Network Application Identifier.  Used by applications
 *		   to define "which" application is making the authentication
 *		   request.  Used by the mechanism to define "which" mechanisms
 *		   may attempt to satisfy the request. Initialized to 0
 *
 * sockfd	=> Socket Descriptor.  This should be the socket being used
 *		   by the network application to perform the communication
 *		   between client and daemon app. Initialized to -1.
 *
 * status	=> May be used by the mechanism layer to store the status of
 *		   a mechanism specific call or sequence that needs to be
 *		   passed back to an application. Mechanisms must check this
 *		   field for a non zero value before setting. Applications
 *		   may check this field depending on whether or not they
 *		   expect the mechanism to set the value. This is similar
 *		   to the entity->error value. Initialized to 0.
 *
 * flags	=> May be used by applications and mechanisms to pass state or 
 *		   sequence style information during the processing of an
 *		   entity, such as during kerberos telnet or ftp processing.
 *		   Initialized to 0.
 *
 * authdata	=> This is an application specific (and allocated) data
 * destructor	   block that describes the authenticatable entity as per
 *		   the applications requirements. During the sia_ses_release()
 *		   processing, if it's determined that there is authdata and
 *		   a destructor routine present in the netauth buffer, then
 *		   the destructor routine will be called. Initialized to NULL.
 *
 * mech_netauth	=> Mechanisms that determine the entity->gssapi field is 
 *  [pkgind]	   non-NULL would use their package index to offset into
 *		   this array in order to store and access mechanism specific 
 *		   data. Each index is initialized to NULL.
 *
 * Do not rely on the length of this structure for anything.  First, the
 * SIASWMAX is really a minimum of the count of mechanisms available on
 * the system - the real value is kept in __sia_sw_max.  Second, this 
 * structure may evolve over time.
 */
typedef struct sianetauth {
			uint_t	netappid;
			int	sockfd;
			uint_t	status;
			uint_t	flags;
			void	*authdata;
			void	(*destructor)(void *);
			void	*mech_netauth[SIASWMAX];
	} SIANETAUTH;

/* 
 * netappid definitions 
 *
 * The following are values that Tru64 UNIX provided applications will use
 * to identify their sianetauth data buffer. The application side will set
 * the appropriate SIA_NETAUTHAPP_* value in the netappid field and call the
 * sia_ses_init() routine with the buffer. A "supporting mechanism" would
 * determine whether or not it recognizes the application id and if desires
 * to perform the authentication for the application. 
 *
 * NOTE: The "network daemon apps" and "local apps" all are defined using 
 *	 odd numbers, while the the "network client apps" are all defined
 *	 using even numbers.
 */
#define SIA_NETAUTHAPP_NONE	0x0000	/* None - used to pass sockfd */

/*
 * The following are not necessarily network apps, but are utilities that
 * require some kind of authentication takes place on the "current user" 
 * before providing a service.
 *
 * The SIA_NETAUTH_LOGIN should be used by applications that will essentially
 * follow the path to authenticate a user with proper credentials locally.
 */
#define SIA_NETAUTHAPP_SU	0x0001	/* Used by /bin/su */
#define SIA_NETAUTHAPP_PASSWD	0x0003	/* Used by /bin/passwd */
#define SIA_NETAUTHAPP_LOGIN	0x0005	/* Use to follow the /bin/login path */
					   
/*
 * The following are set by the r* utils network applications.
 */
#define SIA_NETAUTHAPP_RSH	0x0020	/* Used by /usr/bin/rsh */
#define SIA_NETAUTHAPP_RSHD	0x0021	/* Used by /usr/sbin/rshd */
#define SIA_NETAUTHAPP_RLOGIN	0x0022	/* Used by /usr/bin/rlogin */
#define SIA_NETAUTHAPP_RLOGIND	0x0023	/* Used by /usr/sbin/rlogind */
#define SIA_NETAUTHAPP_RCP	0x0024	/* Used by /usr/bin/rcp */

/*
 * The following are set by telnet and telnetd.
 * For kerberized mechanisms, telnet(d) follows RFC 1416
 */
#define SIA_NETAUTHAPP_TELNET	0x0040	/* Used by /usr/bin/telnet */
#define SIA_NETAUTHAPP_TELNETD	0x0041	/* Used by /usr/sbin/telnetd */

/* 
 * The following are set by ftp and ftpd.
 * For kerberized mechanisms, ftp(d) follows RFC 2228
 */
#define SIA_NETAUTHAPP_FTP	0x0060	/* Used by /usr/bin/ftp */
#define SIA_NETAUTHAPP_FTPD	0x0061	/* Used by /usr/sbin/ftpd */


/*
 * Use the following constant as the beginning point in a enum list for
 * any non Compaq supplied value for the sianetauth netappid field. Any future
 * Compaq supplied apps will use indices below this value.
 */
#define SIA_NETAUTHAPP_MAXIDX	0x00000100

/*
 * sianetauth 'flags' definitions
 *
 * The following flags will be used by the session initialization phase to
 * help the network application determine which mechanism is providing the
 * authentication services so that it can make decisions with respect to how
 * to create/construct the authdata buffer.
 *
 * If more than one mechanism responds to supporting the network application,
 * then the netapp will construct an authdata buffer as dictated by the lowest
 * flag value and attempt authentication.  If authentication fails, then the
 * next flag value's authdata buffer would be attempted.
 * 
 * A mechanism must set the following in it's siad_ses_init() routine when
 * it supports Kerberos v5 as described in RFC 1510
 */
#define SIA_NETAUTH_KRB5	0x00000001	/* Currently - CyberSafe */
#define SIA_NETAUTH_CERT	0x00000002	/* Future */

/*
 * The current set of mechanisms that are recognized by the Tru64 UNIX provided
 * network applications (rsh, rcp, rlogin, rlogind, rshd, ftp, ftpd, telnet,
 * telnetd, su, passwd, & login)
 *
 * to perform the authentication for the application. The mechanism's session
 * initialization routine will "add" the appropriate SIA_NETAUTHMECH_* value
 * to the 'flags' field and let the application determine which mechanism
 * it will attempt to use to perform the authentication.
 */
#define SIA_NETAUTHMECH_CSF	0x00010000    /* CyberSafe - libcsfk5siad.so */
#define SIA_NETAUTHMECH_MIT	0x00020000    /* MIT - tbd */

/**** Separate expansion sia entity structure ****/

/* 
 * The following is a description of each field
 *
 * orig_amask	=> The original audit mask for the process as determined via
 *		   a call to audcntl(GET_PROC_AMASK, ...) during the 
 *		   sia_ses_init() processing.
 *
 * orig_acntl	=> The original audit control flags for the process as 
 *		   determined via a call to audcntl(GET_PROC_ACNTL, ...) during
 *		   the sia_ses_init() processing.
 *
 * ai_list	=> Used by the sia_attr_* interfaces to store the attribute
 *		   list as described above.
 * pw_gname	=> Used by the sia_attr_* interface 
 */
typedef struct siaentitytoo {
			unsigned char *orig_amask;
			int orig_acntl;
			SIA_AI_PKT **ai_list;
			char *pw_gname;
			/* May be extended -- don't rely on this length. */
			} SIAENTITYTOO;
/* macros which can be changed to access private info */
#define SIA_E_AI_LIST entity->siaetoo->ai_list
#define SIA_E_PW_GNAME entity->siaetoo->pw_gname

/***** sia entity structure *******/ 

/*
 * The following is a description of each field.
 *
 * name		=> The UNIX user name of the entity. To be either filled in
 *		   prior to sia_ses_authent() call or determined via the
 *		   collection routine during the siad_ses_authent() routine.
 *
 * password	=> A cleartext string of the password. To be either filled in
 *		   prior to sia_ses_authent() call or determined via the
 *		   collection routine in the siad_ses_authent() routine.
 *
 * acctname	=> A mechanism dependant way to describe or otherwise name
 *		   the entity->name. Mechanisms are required to fill this field 
 *		   when they successfully authenticate the entity->name. If 
 *		   the field is not filled or is different than a previous
 *		   successful mechanism, then SIAFAIL is returned from the
 *		   sia_ses_authent call.
 *
 * argv		=> A copy of the argument list for the application
 * argc		=> The number of arguments in the argv
 *
 * ouid		=> The "originally" logged in uid. Filled in by sia_ses_init()
 *		   by a getuid() call.
 *
 * hostname	=> String indicating the requesting host - NULL means local
 *
 * tty		=> String indicating path to the local tty
 *
 * colinput	=> If set to 1, then allow input from user for entity; 
 *		   otherwise, set it to 0 to disallow user input via the
 *		   collection routine.
 *
 * error	=> Used typically by mechanisms to indicate the "last errno"
 *		   value when an error occurs.  Mechanisms should check for a
 *		   non zero (0) value before setting so as to not overwrite 
 *		   another mechanism's setting of the value.
 *
 * authcount	=> Number of consecutive failed authentication attempts
 *
 * authtype	=> Type of last authentication attempt - see SIA_A_* in siad.h
 *
 * pwd		=> Pointer to a passwd struct for entity->name. The mechanism
 *		   that successfully authenticates the entity->name should
 *		   use the sia_make_entity_pwd() routine to copy the
 *		   entity->name's passwd struct into here. The sia_ses_release()
 *		   routine will free memory used by this field.
 *
 * gssapi	=> Pointer to a sianetauth buffer if it exists.
 *
 * siaetoo	=> Pointer to SIAETOO buffer (previously was sia_pp)
 *
 * mech[]	=> Array of mechanism specific data.  To be used by mechanisms 
 *  [pkgind]	   to store information in a mechanism specific buffer that
 *		   may be needed to facilitate cross SIA call data. This
 *		   would typically be allocated and saved into the mech[pkgind]
 *		   index during the siad_ses_init call and then freed during
 *		   the siad_ses_release call.
 *
 * Do not rely on the length of this structure for anything.  First, the
 * SIASWMAX is really a minimum of the count of mechanisms available on
 * the system - the real value is kept in __sia_sw_max.  Second, this 
 * structure may evolve over time.
 */
typedef struct siaentity {
                        char *name;
			char *password;
                        char *acctname;
                        char **argv;
                        int  argc;
			uid_t ouid;
                        char *hostname;
                        char *tty;
                        int colinput;
                        int error;
                        int authcount;
                        int authtype;
                        struct passwd *pwd;
			void *gssapi;
                        SIAENTITYTOO *siaetoo;
                        int *mech[SIASWMAX];
		} SIAENTITY;


/***** sia collect routine interface definition *****/

typedef struct prompt_t {
        unsigned char *prompt;
        unsigned char *result;
        int max_result_length;
        int min_result_length;
        int control_flags;
} prompt_t;

typedef int sia_collect_func_t __((int /* timeout */, int /* rendition */,
					unsigned char * /* title */,
					int /* num_prompts */,
					prompt_t * /* prompts */));

/* top level returns from sia routines */

#define SIASUCCESS      1  		/* success return */
#define SIAFAIL         0 		/* failure return */
#define SIASTOP		2		/* stop processing */


/**************************************/
/***** sia top level interface    *****/
/***** special purpose routines   *****/
/**************************************/

extern int sia_init __((void));		/* Called to ensure that matrix.conf */
					/* has been read.		     */
extern int __sia_set_matconf __((char const *));
					/* Called to allow the use of an     */
					/* alternate matrix.conf file.	     */

extern int sia_authorize __((SIAENTITY *)); /* only called internally */
					     /* for sia authorization */

extern int sia_chk_invoker __((void));	     /* called to check if process is */
					     /* sufficiently privileged	      */

extern int sia_get_groups __((const char *, gid_t, gid_t *, int *)); /* initgroups processing, short of setgroups() */

sia_collect_func_t sia_collect_trm;	/* general collection routine for*/
					/* terminals */

extern int sia_free_entity __((SIAENTITY *, int));

/**************************************/
/***** sia change secure info calls ***/
/**************************************/

extern int sia_chg_finger __((sia_collect_func_t *, char *, int, char *[]));
extern int sia_chg_password __((sia_collect_func_t *, char *, int, char *[]));
extern int sia_chg_shell __((sia_collect_func_t *, char *, int, char *[]));
extern int sia_update_pass __((sia_collect_func_t *,
			       SIAENTITY *, const char *));

/*************************************/
/**** session processing calls	******/
/*************************************/

/* The following 3 are specific to network authentication processing. */
extern SIANETAUTH *sia_alloc_netauth __((void));
extern void *sia_get_mech_netauth __((SIANETAUTH *, char const *));
extern int sia_free_netauth __((SIANETAUTH **));

extern int sia_ses_init __((SIAENTITY **, int, char *[], char *, char *, char *, int, char *));
extern int sia_ses_authent __((sia_collect_func_t *, char *, SIAENTITY *));
extern int sia_ses_reauthent __((sia_collect_func_t *,  SIAENTITY *));
extern int sia_ses_suauthent __((sia_collect_func_t *,  SIAENTITY *));
extern int sia_ses_estab __((sia_collect_func_t *, SIAENTITY *));
extern int sia_ses_launch __((sia_collect_func_t *, SIAENTITY *));
extern int sia_ses_release __((SIAENTITY **));
extern int sia_attr_getnam __((SIAENTITY *, char *, SIA_AI_PKT **, uint_t, uint_t));
extern int sia_attr_query __((SIAENTITY *, SIA_AI_PKT **, size_t, int *));

extern int sia_attr_setent __((SIAENTITY *));
extern int sia_attr_getent __((SIAENTITY *, SIA_AI_PKT **, uint_t, uint_t));
extern int sia_attr_putent __((SIAENTITY *, SIA_AI_PKT **));
extern int sia_attr_endent __((SIAENTITY *));
extern int sia_attr_to_string __((SIA_AI_PKT **, char **, size_t *, const char));


/*********************************************/
/**** streamlined session processing calls ***/
/*********************************************/

#define	SIA_BEU_CLEARENV	0x001
#define	SIA_BEU_SETLUID		0x002
#define	SIA_BEU_DOCHDIR		0x004
#define	SIA_BEU_OKROOTDIR	0x008	/* ignored without *_DOCHDIR */
#define	SIA_BEU_REALLOGIN	0x010	/* do ses_estab & such, not su-style */
/* REALLOGIN implies DOCHDIR and SETLUID and sort-of implies OKROOTDIR */

extern int sia_become_user __((sia_collect_func_t *, int, char *[], char *, char *, char *, int, char *, char **, int));
extern int sia_validate_user __((sia_collect_func_t *, int, char *[], char *, char *, char *, int, char *, char *));

#ifdef __cplusplus
}
#endif
#endif /* _SIA_H_ */
