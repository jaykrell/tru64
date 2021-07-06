/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: unistd.h,v $
 * Revision 4.2.81.1  2003/06/10  18:56:09  Spider_Boardman
 * 	Update netgroup prototypes to have 'const' where ISC bind/named
 * 	seems to expect.
 * 	[2003/04/10  23:02:36  Spider_Boardman]
 *
 * 	Add {set,get,end}netgrent_r.
 * 	[2003/03/28  21:23:54  Spider_Boardman]
 *
 * Revision 4.2.79.1  2001/12/17  20:57:46  Vladislav_Yasevich
 * 	Merge of Advanced API functionality from wildcat.classic inlcuding applicable QAR fixes.
 *
 * Revision 4.2.71.3  2000/10/13  20:08:51  Barry_Andreasen
 * 	created 'DISABLED' sysconf case - QAR 82280
 *
 * Revision 4.2.71.2  2000/09/25  18:26:50  Brian_Haley
 * 	Added setnetgrent(), getnetgrent(), endnetgrent() and innetgr()
 * 	prototypes (qar 72387).
 *
 * Revision 4.2.71.1  2000/08/11  06:49:19  Bethur_Mohan
 * 	Hide _POSIX_THREAD_PRIORITY_SCHEDULING in XSH5 namespace.
 * 	Also, change the values of  _XOPEN_VERSION and _XOPEN_XCU_VERSION
 * 	for XSH5/UNIX98 compliance.
 * 	[2000/8/10 16:18:36 Bethur_Mohan]
 *
 * Revision 4.2.66.7  2000/05/03  20:29:05  Bethur_Mohan
 * 	Change back to UNIX95 values for _XOPEN_VERSION and
 * 	_XOPEN_XCU_VERSION.
 * 	[2000/5/3 16:18:36 Bethur_Mohan]
 *
 * Revision 4.2.66.6  2000/03/13  15:04:21  Bethur_Mohan
 * 	Removed UNIX95 definitions of _XOPEN_VERSION and _XOPEN_XCU_VERSION
 * 	[2000/3/13 09:55:44 Bethur_Mohan]
 *
 * Revision 4.2.66.5  2000/01/14  14:34:53  Bethur_Mohan
 * 	Added the required definitions for XSH5.
 * 	[2000/1/12 13:06:44 Bethur_Mohan]
 *
 * Revision 4.2.66.4  1999/12/01  18:55:40  Barry_Andreasen
 * 	fixed getconf handling of different spellings for symbol names for -v <spec> and <input> args
 * 	[1999/12/01  18:46:47  Barry_Andreasen]
 *
 * 	UNIX98 functionality supported
 * 	[1999/11/18  19:41:56  Barry_Andreasen]
 *
 * 	added support for UNIX98 features
 * 	[1999/11/10  21:12:16  Barry_Andreasen]
 *
 * Revision 4.2.66.3  1999/10/18  20:23:50  Jack_McCann
 * 	IPv6 submit to Zulu BL6
 *
 * Revision 4.2.60.4  1999/10/13  20:52:37  Vladislav_Yasevich
 * 	Updated with zinc bl1 merge.
 *
 * Revision 4.2.66.2  1999/10/07  17:06:52  Neil_Lewis
 * 	merge from zinc bl1
 *
 * Revision 4.2.60.3  1999/10/08  21:09:31  Vladislav_Yasevich
 * 	ipv6os merge to zulu.
 * 	Additional changes:
 * 	- Added new definitions for rcmd_af, rcmd2_af, rresvport2_af,
 * 	and rexec_af. (Preserve V4 functionality for original functions)
 *
 * Revision 4.2.65.2  1999/08/25  19:50:10  Barry_Andreasen
 * 	added support for abbreviated vendor name feature to confstr functionality
 * 	[1999/08/18  20:16:51  Barry_Andreasen]
 *
 * Revision 4.2.66.1  1999/09/10  18:28:38  Neil_Lewis
 * 	Fix cuserid() declaration so it's visible for C++. Qar 71054.
 *
 * Revision 4.2.60.2  1999/07/02  17:26:33  Vladislav_Yasevich
 * 	Added a definition for rresvport_af.
 * 	[1999/07/02  14:05:22  Vladislav_Yasevich]
 *
 * Revision 4.2.26.21  1999/02/06  23:54:58  David_Long
 * 	Resubmit to fix dropped changes.
 * 	[1999/02/06  23:48:59  David_Long]
 * 
 * Revision 4.2.26.20  1999/02/05  19:10:28  David_Long
 * 	Add support for OEM product renaming
 * 	[1999/02/03  21:12:35  David_Long]
 * 
 * Revision 4.2.26.19  1998/12/03  22:27:41  John_Ferlan
 * 	Add support for long user names.  Change the to the cuserid
 * 	definition.
 * 	[1998/12/02  19:32:25  John_Ferlan]
 * 
 * Revision 4.2.26.18  1998/10/30  22:19:04  Ann_Majeske
 * 	Add _PC_ACL_EXTENDED variable to pathconf to return ACL
 * 	enable/disable/no-support status.  QAR 51881.
 * 	[1998/10/27  16:42:02  Ann_Majeske]
 * 
 * Revision 4.2.26.17  1998/08/18  20:27:03  Brian_Haley
 * 	Added rcmd2() prototype.
 * 	[1998/08/17  18:51:32  Brian_Haley]
 * 
 * Revision 4.2.26.16  1998/07/27  15:13:47  Neil_Lewis
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTEV6OS_BL4:PTEV6OS_BL6 **
 * 		** Ancestor revision:	4.2.41.2 **
 * 		** Merge revision:	4.2.41.4 **
 * 	 	** End **
 * 	[1998/07/27  14:53:26  Neil_Lewis]
 * 
 * Revision 4.2.26.15  1998/06/22  17:20:27  Neil_Lewis
 * 	Fix sbrk() prototype to work for UNIX95. Qar 58746.
 * 	 This supports large amounts of memory.
 * 	 We are intentionally breaking the UNIX95 standard.
 * 	 We are adding support for the UNIX98 standard, which also fixes the problem.
 * 	[1998/06/18  18:45:26  Neil_Lewis]
 * 
 * Revision 4.2.41.4  1998/06/17  20:31:17  Brian_Haley
 * 	Remove rcmd() and rcmd2() prototypes until we can figure out
 * 	why the compiler is having problems with the u_short argument.
 * 	[1998/06/17  18:55:38  Brian_Haley]
 * 
 * Revision 4.2.41.3  1998/06/16  14:52:57  Brian_Haley
 * 	Added rcmd, rcmd2, rresvport and rresvport2 protos (qar 55817).
 * 	[1998/05/28  21:53:13  Brian_Haley]
 * 
 * Revision 4.2.26.14  1998/03/10  12:02:16  James_Woodward
 * 	add function prototypes for pread/pwrite
 * 	[1998/03/09  14:01:06  James_Woodward]
 * 
 * Revision 4.2.41.2  1998/03/09  12:59:54  James_Woodward
 * 	if def pread/pwrite for osf source.  In steel add xpg5.
 * 	[1998/03/02  15:45:34  James_Woodward]
 * 
 * 	add function prototypes for pread and pwrite system calls
 * 	[1998/02/23  20:56:23  James_Woodward]
 * 
 * Revision 4.2.26.13  1998/02/17  20:41:53  Peter_Portante
 * 	Merge definition of pthread_atfork from pthread.h with the one
 * 	defined here.  The UNIX98 branding requires it only live here.
 * 	Additionally, cleanup the POSIX_C_SOURCE usage so that it is
 * 	less confusing.
 * 	[1998/02/16  17:10:27  Peter_Portante]
 * 
 * Revision 4.2.26.12  1998/02/11  23:12:39  Thomas_Woodburn
 * 	Added prototype for crypt16().  (QAR 54848)
 * 	[1998/02/05  21:42:00  Thomas_Woodburn]
 * 
 * Revision 4.2.26.11  1997/10/14  17:43:46  Neil_Lewis
 * 	 	** Merge Information **
 * 		** Command used:	bmerge **
 * 		** Ancestor revision:	4.2.26.9 **
 * 		** Merge revision:	4.2.26.10 **
 * 	 	** End **
 * 	[1997/10/13  15:21:38  Neil_Lewis]
 * 
 * 	Also provide usleep() prototype when _XOPEN_SOURCE is defined
 * 	 and _XOPEN_SOURCE_EXTENDED isn't.
 * 	[1997/09/23  22:02:59  Neil_Lewis]
 * 
 * Revision 4.2.26.10  1997/10/08  16:09:20  Brian_Haley
 * 	Added bindresvport(), rcmd() and rexec() prototypes inside
 * 	#ifdef OSF_SOURCE so that it's not visible for standards
 * 	compliance (qar 52185).
 * 	[1997/10/06  22:07:59  Brian_Haley]
 * 
 * Revision 4.2.26.9  1997/09/02  17:33:23  Thomas_Peterson
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL6:PTCOS_BL10 -visual **
 * 		** Ancestor revision:	4.2.36.2 **
 * 		** Merge revision:	4.2.36.4 **
 * 	 	** End **
 * 	merge of PTmin BL10 changes
 * 	[1997/09/02  17:25:49  Thomas_Peterson]
 * 
 * Revision 4.2.26.8  1997/07/29  14:55:32  Bob_Harris
 * 	(st.vfs.024.UNIX98)
 * 	Add _PC_FILESIZEBITS for UNIX98 support.  The choice of 22 for the
 * 	value is because PTmin will merge in _PC_ASYNC_IO, _PC_SYNC_IO and
 * 	_PC_PRIO_IO.  This should avoid a merge conflict.
 * 	[1997/07/29  14:49:44  Bob_Harris]
 * 
 * Revision 4.2.26.7  1997/07/14  17:05:26  Robert_Fontaine
 * 	Move gettxt() prototype inside OSF_SOURCE macro.
 * 	[1997/07/10  18:02:44  Robert_Fontaine]
 * 
 * Revision 4.2.36.4  1997/05/22  18:30:47  Robert_Fontaine
 * 	Move gettxt() function prototype inside OSF_SOURCE #ifdef so that is
 * 	is not visible when XOPEN_SOURCE is defined for standards compliance.
 * 	[1997/05/22  18:30:08  Robert_Fontaine]
 * 
 * Revision 4.2.36.3  1997/05/20  19:04:37  Jeff_Denham
 * 	Add missing definitions for _PC_ASYNC_IO, _PC_PRIO_IO, & _PC_SYNC_IO.
 * 	[1997/05/19  14:35:37  Jeff_Denham]
 * 
 * Revision 4.2.26.6  1997/04/22  15:39:03  David_Long
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL3:PTCOS_BL6 **
 * 		** Ancestor revision:	4.2.31.2 **
 * 		** Merge revision:	4.2.36.2 **
 * 	 	** End **
 * 	merge of PTmin BL6 changes
 * 	[1997/04/21  21:50:28  David_Long]
 * 
 * Revision 4.2.26.5  1997/03/30  21:50:36  David_Long
 * 	Changed for UNIX98.
 * 	[1997/03/26  18:46:45  David_Long]
 * 
 * Revision 4.2.36.2  1997/03/24  15:45:25  Robert_Fontaine
 * 	Add function prototype for gettxt() function.
 * 	[1997/03/18  14:27:06  Robert_Fontaine]
 * 
 * Revision 4.2.26.4  1997/02/14  18:31:21  Brian_Haley
 * 	Added rresvport() and ruserok() prototypes (qar 33030).
 * 	[1997/02/03  22:05:04  Brian_Haley]
 * 
 * Revision 4.2.26.3  1996/12/09  22:12:17  Neil_Lewis
 * 	Eliminate compiler warnings when compiled with -warnprotos.
 * 	[1996/11/12  17:38:21  Neil_Lewis]
 * 
 * Revision 4.2.31.2  1996/09/24  13:08:26  David_Long
 * 	Merge from v40asupportos to ptbos.bl3
 * 	[1996/09/23  20:44:26  David_Long]
 * 
 * Revision 4.2.28.2  1996/08/30  18:38:13  David_Long
 * 	Added __P_C() macro to fix P1003.1C prototypes for c++.
 * 	[1996/08/16  20:40:59  David_Long]
 * 
 * Revision 4.2.26.2  1996/08/05  20:11:12  David_Long
 * 	Added __P_C() macro to fix P1003.1C prototypes for c++.
 * 	[1996/08/01  18:04:53  David_Long]
 * 
 * Revision 4.2.24.17  1995/12/21  22:44:35  Blue_Tabor
 * 	Make P1003.1b fdatasync() visible when _POSIX_C_SOURCE >= 199306L
 * 	*
 * 	Revision 4.2.24.16  1995/12/01  18:35:25  Geoffrey_Cooper
 * 	Removed namespace pollution introduced by the P1003.1c
 * 	support.
 * 	[1995/11/29  21:48:17  Geoffrey_Cooper]
 * 
 * Revision 4.2.24.15  1995/11/29  20:09:59  David_Long
 * 	Fix arglist of ttyname_r define for acc.
 * 	[1995/11/21  18:42:37  David_Long]
 * 
 * Revision 4.2.24.14  1995/10/25  15:17:52  David_Long
 * 	Added support for incompatable P1003.1c APIs.
 * 	[1995/10/20  20:30:44  David_Long]
 * 
 * Revision 4.2.24.13  1995/09/07  17:40:05  Blue_Tabor
 * 	Replace obsolete symbols _POSIX_4SOURCE and _POSIX_SOURCE with
 * 	POSIX 1003.1b symbol _POSIX_C_SOURCE.  Remove obsolete symbol
 * 	_POSIX4_VERSION.  Remove obsolete SC option and values for
 * 	_SC_4VERSION, _SC_SEM_NSETS_MAX, _SC_BINARY_SEMAPHORES,
 * 	_SC_REALTIME_FILES, _SC_MQ_NAME_MAX.  Add constants for POSIX
 * 	threads 1003.1c-1995.  Remove fdatasync from XPG4 namespace.
 * 	[1995/09/03  21:01:36  Blue_Tabor]
 * 
 * Revision 4.2.24.12  1995/08/15  18:51:37  Thomas_Peterson
 * 	     Added SysV version of swab() declaration under __SVID__ #ifdef
 * 	     which was missing from this header.
 * 	     [1995/08/14  19:33:08  Thomas_Peterson]
 * 
 * Revision 4.2.24.11  1995/07/28  21:21:44  Geoffrey_Cooper
 * 	Added renaming for pipe and setpgrp as per Spec1170 Exception
 * 	request.
 * 	[1995/07/06  22:36:09  Geoffrey_Cooper]
 * 
 * 	Removed fdatasync from spec1170 namespace
 * 	[1995/07/06  20:55:41  Geoffrey_Cooper]
 * 
 * Revision 4.2.24.10  1995/06/12  17:50:11  Floyd_Smith
 * 	Added support for _SC_NPROC_CONF & ...ONLN - QAR31219 - fys
 * 	[1995/06/06  11:41:04  Floyd_Smith]
 * 
 * Revision 4.2.24.9  1995/04/28  19:25:39  Blue_Tabor
 * 	Modified comment to accurately reflect POSIX 1003.1b standard
 * 	[1995/04/25  02:49:34  Blue_Tabor]
 * 
 * Revision 4.2.24.8  1995/04/14  22:06:00  Blue_Tabor
 * 	Added _POSIX_SYNCHRONIZED_IO, removed _POSIX_BINARY_SEMAPHORES,
 * 	and added fdatasync function declaration
 * 	[1995/04/13  16:03:05  Blue_Tabor]
 * 
 * Revision 4.2.24.7  1995/03/24  20:11:15  Christine_Ahrens
 * 	Cleaned up repeated definitions, added #ifndef _KERNEL, and
 * 	added #ifndef _POSIX_VDISABLE.
 * 	[1995/03/23  16:59:13  Christine_Ahrens]
 * 
 * Revision 4.2.24.6  1995/02/17  19:26:46  Thomas_Peterson
 * 	Fixed default declaration for setpgrp() to be consistent with
 * 	the actual routine.  It should accept two args (pid_t, pid_t)
 * 	and return an int (BSD/historical behavior).  Conditionalized
 * 	alternate decl for SysV/Spec1170, which takes no args (void)
 * 	and returns a pid_t.  Replaced individual extern "C" blocks
 * 	with all-inclusive one surrounding entire header for C++.  Also
 * 	removed #ifdefs around swab() decl, since this matches the
 * 	<string.h> version.  Removed duplicate swab() decl as well.
 * 	[1995/02/13  15:07:35  Thomas_Peterson]
 * 
 * Revision 4.2.24.5  1995/02/09  21:11:35  Jeff_Denham
 * 	Add comments about hardcoded values for  _SC_RTSIG_LOW and
 * 	_SC_RTSIG_HI in <sys/signal.h>
 * 	[1995/02/09  17:04:38  Jeff_Denham]
 * 
 * Revision 4.2.24.4  1995/02/08  22:02:50  Jeff_Denham
 * 	Finish up realtime signals work for POSIX.1b.
 * 	[1995/02/03  18:14:23  Jeff_Denham]
 * 
 * Revision 4.2.24.3  1994/10/09  18:09:12  Deepak_Gupta
 * 	Merged into Platinum BL1
 * 	[1994/10/09  18:00:41  Deepak_Gupta]
 * 
 * 	Added _BEGIN_CPLUSPLUS for matching.
 * 	Removed use of useconds_t in the DEC OSF/1 name space
 * 	Added F_LOCK, F_ULOCK, F_TEST, T_LOCK in spec1170 name space.
 * 	[1994/10/09  17:44:16  Deepak_Gupta]
 * 
 * Revision 4.2.18.3  1994/09/26  17:41:50  Deepak_Gupta
 * 	spec1170 name space changes
 * 	[1994/09/26  17:41:37  Deepak_Gupta]
 * 
 * Revision 4.2.21.2  1994/09/09  18:02:07  Jeff_Denham
 * 	Add definitions for realtime signals. The official POSIX.1b
 * 	feature-test macro has not been turned on yet, because we don't
 * 	define RTSIGMIN and RTSIGMAX yet.
 * 	[1994/09/08  20:09:33  Jeff_Denham]
 * 
 * Revision 4.2.18.2  1994/08/19  20:03:02  Deepak_Gupta
 * 		Following changes were done:
 * 
 * 	-	spec1170 prototypes for fchown(), fchdir(), ftruncate(),
 * 		gethostid(), gethostname(), getpagesize(), getpgid()
 * 		getsid(), getwd(), lchown(), lockf(), readlink(), sbrk(),
 * 		setpgrp(), setregid(), setreuid(), symlink(), sync(),
 * 		truncate(), ualarm(), usleep(), vfork(), and brk() were added.
 * 
 * 		typedef useconds_t is a new type for spec1170 which
 * 		translates to the same DEC OSF/1 type. This is defined in
 * 		sys/types.h.
 * 
 * 	-	Feature group constant _XOPEN_UNIX is defined ( along with
 * 		_SC_XOPEN_UNIX)
 * 
 * 	-	Symbolic constants _SC_ATEXIT_MAX, _SC_IOV_MAX, _SC_PAGESIZE
 * 		and _SC_PAGE_SIZE  required by
 * 		spec1170 are defined.
 * 	[1994/08/19  20:02:17  Deepak_Gupta]
 * 
 * Revision 4.2.16.13  1994/06/21  22:48:31  Tim_Hoskins
 * 	Added proto for vfork().
 * 	[1994/06/21  02:39:24  Tim_Hoskins]
 * 
 * Revision 4.2.16.12  1994/05/16  18:52:55  Thomas_Peterson
 * 	Moved declaration for lockf() here from <sys/fnctl.h> because it was
 * 	causing name space pollution for the XPG4 test suite.  SPEC1170
 * 	specifies that this declaration belongs in <unistd.h>, so we are
 * 	adding this under the _OSF_SOURCE ifdef until the official SPEC1170
 * 	macro is available in the next release.
 * 	[1994/05/13  18:52:13  Thomas_Peterson]
 * 
 * Revision 4.2.16.11  1994/04/25  13:24:37  Robert_McGuirk
 * 	Add protos for gethostname() and getdtablesize()
 * 	[1994/04/25  13:22:16  Robert_McGuirk]
 * 
 * Revision 4.2.16.10  1994/03/17  01:24:00  Blue_Tabor
 * 	Modified _POSIX4_VERSION string to reflect POSIX 1003.4 Draft 14 version
 * 	[1994/03/15  20:48:40  Blue_Tabor]
 * 
 * Revision 4.2.16.9  1994/03/02  20:34:49  Neil_OBrien
 * 	Changed the declaration of sbrk() from extern char * to extern
 * 	void *.  Fixes OSF_QARs #18324 and #20165.
 * 	[1994/03/02  13:32:16  Neil_OBrien]
 * 
 * Revision 4.2.16.8  1994/02/22  17:40:37  Neil_OBrien
 * 	Move the declarations of read() and write() to a _NONSTD_TYPES
 * 	block.  Fixes OSF_QAR #19958.
 * 	[1994/02/18  21:27:44  Neil_OBrien]
 * 
 * Revision 4.2.16.7  1994/02/10  16:43:18  Neil_OBrien
 * 	Add usleep() to the list of declarations.  Fixes OSF_QAR #16854.
 * 	[1994/01/12  16:45:51  Neil_OBrien]
 * 
 * Revision 4.2.16.6  1994/01/07  18:33:58  Thomas_Peterson
 * 	Merged C++ header changes fwd from sterl bl9 to gold bl8
 * 	[1994/01/05  17:27:00  Thomas_Peterson]
 * 
 * Revision 4.2.16.5  1993/12/16  18:27:02  Thomas_Peterson
 * 	merge of Sterling BL8 changes
 * 	[1993/12/16  18:18:59  Thomas_Peterson]
 * 
 * Revision 4.2.14.11  1993/12/15  22:14:37  Thomas_Peterson
 * 	Replaced awkward __cplusplus ifdef blocks with macros from <standards.h>.
 * 	Added ifndef _XOPEN_SOURCE around cuserid() in _POSIX_SOURCE section so
 * 	we don't get duplicate declarations. (illegal in C++)  Added C++
 * 	conditional to declaration of swab() so doesn't conflict with declaration
 * 	from <string.h> (only a problem in C++).
 * 	[1993/12/14  22:49:16  Thomas_Peterson]
 * 
 * Revision 4.2.14.10  1993/11/22  19:06:16  Brett_Sampson
 * 	backed out 4.2.14.9 the changes were not ansii safe
 * 	broke the x build and should not be made in this header file.
 * 	[1993/11/22  19:04:30  Brett_Sampson]
 * 
 * Revision 4.2.14.9  1993/11/17  18:17:55  Donald_Stadler
 * 	Added two #defines related to the XPG/4 standard shell code.
 * 	[1993/11/17  18:05:00  Donald_Stadler]
 * 
 * Revision 4.2.16.4  1993/11/08  15:07:45  Thomas_Peterson
 * 	merge of Sterling BL7 changes
 * 	[1993/11/08  14:53:22  Thomas_Peterson]
 * 
 * Revision 4.2.16.3  1993/10/12  14:11:39  Thomas_Peterson
 * 	merge of Sterling BL6 changes
 * 	[1993/10/11  20:16:46  Thomas_Peterson]
 * 
 * Revision 4.2.14.8  1993/09/30  17:52:13  Robert_Fontaine
 * 	Change define _POSIX2_LOCALDEF to _POSIX2_LOCALEDEF
 * 	[1993/09/30  17:37:17  Robert_Fontaine]
 * 
 * 	Change argument of sbrk from int to ssize_t.
 * 	[1993/09/27  19:17:00  Robert_Fontaine]
 * 
 * Revision 4.2.16.2  1993/09/23  19:15:21  Vikas_Sontakke
 * 	Added POSIX 1003.4 D14 new features for counting semaphores & IPC
 * 	[1993/09/23  00:43:53  Vikas_Sontakke]
 * 
 * Revision 4.2.14.7  1993/08/31  17:58:45  Thomas_Woodburn
 * 	Added _XOPEN_ENH_I18N and _XOPEN_SHM for XPG/4.
 * 	[1993/08/27  18:55:18  Thomas_Woodburn]
 * 
 * Revision 4.2.14.6  1993/08/23  21:32:19  Thomas_Peterson
 * 	Various changes required for XPG4: Protected the following symbols
 * 	from XPG4 with _OSF_SOURCE: environ, F_ULOCK, F_LOCK, F_TLOCK, F_TEST.
 * 	Removed parameter names (which are illegal in ANSI-C) from these
 * 	declarations: execl, execv, execle, execve, execlp, execvp, getgroups,
 * 	pipe.  Moved the following out of POSIX_SOURCE and protected with
 * 	_OSF_SOURCE: getenv, rename.  Moved the following out of _XOPEN_SOURCE
 * 	and protected with _OSF_SOURCE: brk, getpagesize, getsid, getwd, sbrk,
 * 	seteuid, setegid, setlogin, setpgrp, setregid, setreuid, setrgid,
 * 	setruid, ualarm.
 * 	[1993/08/20  16:55:57  Thomas_Peterson]
 * 
 * Revision 4.2.14.5  1993/07/22  20:56:45  Thomas_Peterson
 * 	Removed declarations for localtime_r and gmtime_r and include
 * 	of <time.h>.  Previous revision history states that POSIX 4
 * 	requires these here.  Current drafts of P1003.4 and P1003.4a
 * 	do not support this.  Leaving these here creates name space
 * 	pollution identified in the XPG4 test suite.  See QARs 13747
 * 	& 13612 for more information.
 * 	[1993/07/21  15:08:24  Thomas_Peterson]
 * 
 * Revision 4.2.14.4  1993/07/20  20:28:32  David_Long
 * 	Set _XOPEN_CRYPT which is required by XPG4 for any system supporting the
 * 	crypt function, whether or not decryption is also supported.
 * 	[1993/07/16  20:17:03  David_Long]
 * 
 * Revision 4.2.14.3  1993/06/08  21:06:26  David_Long
 * 	Changed return type of non-std write to int.
 * 	[1993/06/08  20:46:30  David_Long]
 * 
 * Revision 4.2.14.2  1993/06/08  01:15:07  Thomas_Woodburn
 * 	I18N/thread-safe/ANSI-name-space joint submit.
 * 	[1993/06/07  21:02:50  Thomas_Woodburn]
 * 
 * Revision 4.2.11.7  1993/06/04  00:00:38  Thomas_Woodburn
 * 	Fixed typo in swab() prototype.
 * 	[1993/06/03  23:59:51  Thomas_Woodburn]
 * 
 * Revision 4.2.11.6  1993/06/03  17:01:37  Robert_Fontaine
 * 	Add include for getopt.h and move POSIX_JOB_CONTROL thu POSIX2_VERSION
 * 	from under POSIX4_SOURCE to POSIX_SOURCE.  Add XOPEN_XCU_VERSION and
 * 	XOPEN_XPG4 constants.
 * 	[1993/06/03  13:41:42  Robert_Fontaine]
 * 
 * Revision 4.2.11.5  1993/05/25  00:31:05  Thomas_Woodburn
 * 	Commented text following #endif.
 * 	[1993/05/25  00:29:50  Thomas_Woodburn]
 * 
 * Revision 4.2.11.4  1993/05/24  12:51:21  Robert_Fontaine
 * 	Deleted extra defines for POSIX_JOB_CONTROL AND POSIX_SAVED_IDS.
 * 	[1993/05/24  12:49:49  Robert_Fontaine]
 * 
 * Revision 4.2.11.3  1993/05/20  17:47:04  Robert_Fontaine
 * 	Add new XPG4 constants and function prototypes.  Delete seek constants
 * 	and include sys/seek.h header file instead.
 * 	[1993/05/20  17:45:23  Robert_Fontaine]
 * 
 * Revision 4.2.11.2  1993/05/19  17:22:56  Thomas_Woodburn
 * 	Added confstr() prototype and its constants _CS_PATH
 * 	and _CSPATH.  All are new in XPG/4.
 * 	[1993/05/19  17:17:24  Thomas_Woodburn]
 * 
 * Revision 4.2.3.14  1992/12/09  10:37:54  Paula_Long
 * 	fixed botched submit.
 * 	[92/12/09  10:34:57  Paula_Long]
 * 
 * Revision 4.2.3.13  92/12/09  10:30:33  Paula_Long
 * 	Proto-type for ttyname_r is incorrect.  The function returns an int
 * 	not a char *.
 * 	[92/12/08  10:03:46  Paula_Long]
 * 
 * Revision 4.2.3.12  92/11/20  12:27:55  Dick_Bergersen
 * 	Added supported Posix 1003.4 features
 * 	Added 1003.4 draft 11 arguments to sysconf()
 * 	Bracketed draft 10 compatibility features with ifdef...endif
 * 	[92/11/20  11:45:19  Dick_Bergersen]
 * 
 * Revision 4.2.3.11  92/11/16  16:52:00  Gerry_Feldman
 * 	QAR4436: Added _REENTRANT || _THREAD_SAFE blocks around POSIX reentrant
 * 		functions.
 * 	QAR8366: localtime_r and gmtime_r are required by POSIX 4 to be in Unistd.h
 * 		 Included time.h for the definition of struct tm.
 * 	[92/11/10  12:47:10  Gerry_Feldman]
 * 
 * Revision 4.2.3.10  92/11/06  18:25:57  Terry_Linsey
 * 	Added gmtime_r() and localtime_r() for POSIX.
 * 	[92/11/04  16:48:54  Terry_Linsey]
 * 
 * Revision 4.2.3.9  92/06/26  10:36:52  Brett_Sampson
 * 	Merged Silver BL8_1
 * 	Revision 4.2.8.2  92/06/23  19:23:16  devbld_gsf
 * 	First AG_BL8_1 version.  Moved from Ag baselevel delivery tree.
 * 
 * 	Revision 4.2.4.15  92/06/05  12:17:31  Mary_Walker
 * 	changes _SC_STREAM_MAX to 13 as it is in osf1.1
 * 	[92/06/01  11:23:55  Mary_Walker]
 * 
 * 	added _SC_STREAM_MAX for posix compliance
 * 	[92/05/29  14:33:17  Mary_Walker]
 * 
 * 	Revision 4.2.4.14  92/05/19  11:48:44  Stephen_Strange
 * 	[92/06/26  10:36:05  Brett_Sampson]
 * 
 * Revision 4.2.3.8  92/06/04  16:26:05  Paul_Hansen
 * 	Changed getcwd(char *, int) to getcwd(char *, size_t) to fix QAR 03928
 * 	[92/06/04  16:23:08  Paul_Hansen]
 * 
 * Revision 4.2.3.7  92/06/03  12:17:46  Robin_Miller
 * 	Merged in Silver BL7 changes.
 * 	Revision 4.2.4.14  92/05/19  11:48:44  Stephen_Strange
 * 	Changed definition for getcwd for 1990 POSIX compliance
 * 	[92/05/08  16:54:16  Stephen_Strange]
 * 
 * 	Revision 4.2.4.13  92/05/18  08:57:40  Shirley_Smith
 * 	Bmerged with ag.latest
 * 	[92/05/15  14:42:56  Shirley_Smith]
 * 
 * 	Removed type-cast on _POSIX_VDISABLE.
 * 	[92/05/15  14:15:20  Shirley_Smith]
 * 
 * 	Revision 4.2.4.12  92/05/06  12:23:17  Larry_Woodman
 * 	Make the exec() function arguments comply with the posix ansi standard.
 * 	[92/04/24  10:29:54  Larry_Woodman]
 * 
 * Revision 4.2.3.6  92/05/06  09:35:38  Robin_Miller
 * 	Merged in Silver BL6-4 changes.
 * 	Revision 4.2.6.2  92/05/05  10:12:34  devbld_gsf
 * 	First AG_BL6_4 version.  Moved from Ag baselevel delivery tree.
 * 
 * 	Revision 4.2.4.11  92/04/23  13:14:14  Raymond_Glaser
 * 	Remove merge markers ??
 * 	[92/04/23  13:11:44  Raymond_Glaser]
 * 
 * 	Revision 4.2.4.10  92/04/23  12:59:40  Raymond_Glaser
 * 	Add definition of _SC_TZNAME_MAX for POSIX
 * 	[92/04/23  12:53:27  Raymond_Glaser]
 * 
 * 	Revision 4.2.4.9  92/04/22  09:34:02  David_Metsky
 * 	Went back to 199009L for _POSIX_VERSION.
 * 	[92/04/22  09:13:18  David_Metsky]
 * 
 * Revision 4.2.3.5  92/04/23  14:38:32  Robin_Miller
 * 	Merged in Silver BL6-3 changes.
 * 	Revision 4.2.5.2  92/04/22  08:39:37  devbld_gsf
 * 	First AG_BL6_3 version.  Moved from Ag baselevel delivery tree.
 * 
 * 	Revision 4.2.4.8  92/04/10  11:16:37  Stephen_Strange
 * 	POSIX compliance changes for ISO 9945-1 (1990)
 * 	[92/03/30  18:16:42  Stephen_Strange]
 * 
 * 	Revision 4.2.4.7  92/04/08  12:02:03  David_Metsky
 * 	Change _POSIX_VERSION back to 198808L because of our version of the
 * 	VSX test suite
 * 	[92/04/08  10:35:47  David_Metsky]
 * 
 * 	Updated _POSIX_VERSION and changed return value for read() and write()
 * 	to ssize_t, which is now defined in types.h
 * 	[92/03/31  18:25:11  David_Metsky]
 * 
 * Revision 4.2.3.4  92/04/14  18:21:49  Robin_Miller
 * 	Revision 4.2.4.6  92/03/27  16:56:23  Lai-Wah_Hui
 * 	"Add RT support"
 * 
 * 	Revision 4.2.4.5  92/03/27  15:37:52  Craig_Horman
 * 	Merge with AG
 * 	[92/03/27  14:09:29  Craig_Horman]
 * 
 * 	Merge with BL5
 * 	[92/03/09  15:14:00  Craig_Horman]
 * 
 * 	Added C++ Support
 * 	[92/02/26  17:42:01  Craig_Horman]
 * 
 * 	Revision 4.2.4.4  92/03/24  14:03:07  Daniel_Eskenazi
 * 	Merged with concurrent edits
 * 	[92/03/23  17:39:13  Daniel_Eskenazi]
 * 
 * 	Modified _SC_PAGESIZE to match Gold definition
 * 	[92/03/16  14:31:42  Daniel_Eskenazi]
 * 
 * 	Added _SC_PAGESIZE for SVID3 Compatibility
 * 	[92/03/13  13:44:33  Daniel_Eskenazi]
 * 
 * 	Revision 4.2.4.3  92/03/23  16:03:54  Stephen_Strange
 * 	ISO 9945-1 POSIX compliance -- arg types to read() and write() changed.
 * 	[92/03/23  15:19:54  Stephen_Strange]
 * 
 * Revision 4.2.2.3  92/03/27  15:25:56  Lai-Wah_Hui
 * 	Add RT support
 * 
 * Revision 4.2.2.2  92/03/27  11:01:49  Lai-Wah_Hui
 * 	Add P1003.4 _SC_
 * 
 * Revision 4.2.3.3  92/03/20  14:25:55  Mike_Rickabaugh
 * 	NULL should be 0L.
 * 	[92/03/20  14:22:44  Mike_Rickabaugh]
 * 
 * Revision 4.2.3.2  92/03/19  17:50:11  Al_Delorey
 * 	From Silver: AG_BL5
 * 	[92/03/19  17:49:42  Al_Delorey]
 * 
 * Revision 4.2.1.2  92/03/17  18:43:24  devbld_gsf
 * 	First AG_BL5 version.  Moved from Ag baselevel delivery tree.
 * 
 * Revision 4.2.4.2  92/02/12  19:03:40  William_Burns
 * 	Merge from ODE/TIN: revision 3.2.9.2
 * 	date: 92/02/05 14:51:04;  author: devrcs;  state: Exp;  lines added/del: 4/4
 * 	sccs rev: 3.3;  orig date: 92/01/28 16:45:40;  orig author: fred
 * 	Fred Canter - fix execl* function prototypes to make PCTS happy.
 * 	[92/02/12  10:32:40  William_Burns]
 * 
 * Revision 4.2  91/09/20  05:19:35  devbld
 * 	Adding ODE Headers
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: unistd.h,v $ $Revision: 4.2.81.1 $ (DEC) $Date: 2003/06/10 18:56:09 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */

/*
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * Copyright (c) 1984 AT&T	
 * All Rights Reserved  
 *
 * THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	
 * The copyright notice above does not evidence any   
 * actual or intended publication of such source code.
 * 
 * unistd.h	1.17  com/inc,3.1,8943 9/22/89 15:13:11
 */

#ifndef _UNISTD_H_
#define _UNISTD_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>
#if defined (_XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)
#include <inttypes.h>   /* defines intptr_t for XSH5 */
#endif

#ifndef _KERNEL	
#include <sys/types.h>  /* for time_t and size_t */
#include <sys/access.h>	/* for the "access" function */

/*
 * POSIX requires that certain values be included in unistd.h.  It also
 * requires that when _POSIX_C_SOURCE is defined (>= 1) only those 
 * standard specific values are present.  This header includes all the POSIX
 * required entries.
 */

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 1)
/* Symbolic constants for the "lseek" function: */

#include <sys/seek.h>
#include <getopt.h>

/***AAB-XPG4*** must protect from XPG4 ***/
#ifdef _OSF_SOURCE
extern char **environ;          /* Environment description variable */
/* forward declaration for bindresvport() */
struct sockaddr_in;
#endif /*OSF_SOURCE*/

#ifdef _NONSTD_TYPES
extern int     read();
extern int     write();
#else

#if defined(_OSF_SOURCE) || (_XOPEN_SOURCE>=500)
extern ssize_t  pread __((int, void *, size_t, off_t));
extern ssize_t  pwrite __((int , const void *, size_t, off_t));
#endif

extern ssize_t	read __((int, void *, size_t));
extern ssize_t	write __((int , const void *, size_t)); 
#endif  /* _NONSTD_TYPES */

extern int access __((const char *, int ));
extern unsigned int alarm __((unsigned int ));
extern int chdir __((const char *));
extern int chown __((const char *, uid_t , gid_t ));
extern int chroot __((const char *));
extern int close __((int ));
extern size_t confstr __((int, char *, size_t));

#ifndef _XOPEN_SOURCE
#if !defined(_LIBC_POLLUTION_H_) && !defined(__V40_OBJ_COMPAT)
#ifdef __DECC
#pragma extern_prefix "_E"
#else
#define cuserid(__a) _Ecuserid(__a)
#endif /* __DECC */
#endif /* __V40_OBJ_COMPAT && _LIBC_POLLUTION_H_ */

extern char *__V40_OC(cuserid) __((char *));

#if !defined(_LIBC_POLLUTION_H_) && !defined(__V40_OBJ_COMPAT) && defined(__DECC)
#pragma extern_prefix ""
#endif
#endif /* _XOPEN_SOURCE for cuserid */

extern int dup __((int ));
extern int dup2 __((int , int ));

/***AAB-XPG4 Parameter names not allowed in ANSI-C ***/
extern int execl __((const char *, const char *, ...));
extern int execv __((const char *, char *const[]));
extern int execle __((const char *, const char *, ...)); 
extern int execve __((const char *, char *const[], char *const[]));
extern int execlp __((const char *, const char *, ...)); 
extern int execvp __((const char *, char *const[]));
/*AAB_XPG4*/

extern void _exit __((int ));
extern pid_t fork __((void));
extern long fpathconf __((int , int ));
extern int fsync __((int));
#if (_POSIX_C_SOURCE >= 199306L)
extern int fdatasync __((int));
#endif
extern char *getcwd __((char *, size_t ));
extern gid_t getegid __((void));
extern uid_t geteuid __((void));
extern gid_t getgid __((void));


/***AAB-XPG4 Parameter names not allowed in ANSI-C ***/
extern int getgroups __((int , gid_t []));

extern char *getlogin __((void));
extern pid_t getpgrp __((void));
extern pid_t getpid __((void));
extern pid_t getppid __((void));
extern uid_t getuid __((void));
extern int isatty __((int ));
extern int link __((const char *, const char *));
extern off_t lseek __((int , off_t , int ));
extern long pathconf __((const char *, int ));
extern int pause __((void));


/***AAB-XPG4 Parameter names not allowed in ANSI-C ***/

#if defined(_XOPEN_SOURCE_EXTENDED) && !defined(_LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix "_E"
#else
#define pipe(__a) _Epipe(__a)
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */

extern int __R(pipe) __((int []));

#if defined(_XOPEN_SOURCE_EXTENDED) && !defined( _LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix ""
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */

extern int rmdir __((const char *));
extern int setgid __((gid_t ));
extern int setpgid __((pid_t , pid_t ));
extern pid_t setsid __((void));
extern int setuid __((uid_t ));
extern unsigned int sleep __((unsigned int ));

#if defined(_XOPEN_SOURCE_EXTENDED) || ( defined(_XOPEN_SOURCE) && defined(_OSF_SOURCE))
extern int usleep __((useconds_t ));	/* spec1170 requires a value to be returned */
#else

#ifndef _XOPEN_SOURCE
extern void usleep __((unsigned int));
#endif	/* _XOPEN_SOURCE */

#endif /* _XOPEN_SOURCE_EXTENDED */

extern long sysconf __((int ));
extern pid_t tcgetpgrp __((int ));
extern int tcsetpgrp __((int , pid_t ));
extern char *ttyname __((int ));
extern int unlink __((const char *));
#ifndef __SVID__
extern void swab __((const void *, void *, ssize_t));
#endif

/* POSIX REENTRANT FUNCTIONS */
#if (_POSIX_C_SOURCE >= 199506L)

#ifndef	_LIBC_POLLUTION_H_
#ifdef	__DECC
#pragma extern_prefix "_P"
#else
#define	getlogin_r(__a,__b)	_Pgetlogin_r(__a,__b)
#define	ttyname_r(__a,__b,__c)	_Pttyname_r(__a,__b,__c)
#endif	/* __DECC */
#endif	/* !_LIBC_POLLUTION_H_ */
extern int __P_C(getlogin_r) __((char *, size_t));	/* _POSIX_REENTRANT_FUNCTIONS */
extern int __P_C(ttyname_r) __((int, char *, size_t));	/* _POSIX_REENTRANT_FUNCTIONS */
#ifndef	_LIBC_POLLUTION_H_
#ifdef	__DECC
#pragma extern_prefix ""
#endif	/* __DECC */
#endif	/* !_LIBC_POLLUTION_H_ */

extern ssize_t pread __((int, void *, size_t, off_t));
extern ssize_t pwrite __((int, const void *, size_t, off_t));
extern int pthread_atfork __((void (*)(void), void (*)(void), void (*)(void)));

#else

#if !defined (_XOPEN_SOURCE) || defined (_OSF_SOURCE)

extern int getlogin_r __((char *, int));
extern int ttyname_r __((int, char *, int));

#endif /* !defined (_XOPEN_SOURCE) || defined (_OSF_SOURCE) */

#endif	/* P1003.1c */

#define STDIN_FILENO	0
#define STDOUT_FILENO	1
#define STDERR_FILENO	2

#define _POSIX_VERSION  199506L

#endif /* _POSIX_C_SOURCE */
#endif /* ifndef _KERNEL */

/* swab() declaration for SysV */
#ifdef __SVID__
extern void swab __((const char *, char *, int));
#endif

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 1)

#define _POSIX_CHOWN_RESTRICTED	 0 /* chown requires appropriate privileges */
#define _POSIX_NO_TRUNC	     	 0 /* too-long path components gen errors */

#ifndef _POSIX_VDISABLE
#define _POSIX_VDISABLE		0377
#endif /* _POSIX_VDISABLE */

#endif /* _POSIX_C_SOURCE */
#ifndef _KERNEL
#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 1)

#define	_POSIX_THREADS		/* 1003.1c (pthreads) comformant */
#define _POSIX_THREAD_ATTR_STACKSIZE /* support for specifiable stack sizes */
#define	_POSIX_REENTRANT_FUNCTIONS  /* multithreaded 1003.1 interfaces */
#define _POSIX_JOB_CONTROL       1  /* implementation supports job control */
#define _POSIX_SAVED_IDS         1  /* saved set-user-id and set-group-id */

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199506L)
#define _POSIX_THREAD_SAFE_FUNCTIONS
#if !defined (_XOPEN_SOURCE) || defined (_OSF_SOURCE)
#define _POSIX_THREAD_PRIORITY_SCHEDULING
#endif /* !_XOPEN_SOURCE || _OSF_SOURCE */
#define	_POSIX_THREAD_ATTR_STACKADDR
#define	_POSIX_THREAD_PROCESS_SHARED
#endif /* _POSIX_C_SOURCE >= 199506L */

#define _POSIX2_C_BIND     1  /* supports the C language binding */
#define _POSIX2_C_DEV      1  /* supports the C development env  */
#define _POSIX2_LOCALEDEF  1  /* supports creation of lacales with localedef */
#define _POSIX2_SW_DEV     1  /* supports software development */
#define _POSIX2_CHAR_TERM  1  /* supports a least one terminal */
#define _POSIX2_UPE        1  /* supports the User Portability Environment */

#undef _POSIX2_FORT_DEV       /* no support for FORTRAN developemnt */
#undef _POSIX2_FORT_RUN       /* no support for FORTRAN runtime */

#define _POSIX2_C_VERSION     199209L /* Support ISO POSIX-2 */
#define _POSIX2_VERSION       199209L /* POSIX.2 standard */


#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L)
/*
 * POSIX 1003.1b Feature Test Macros
 * Supported features
 */

#define _POSIX_ASYNCHRONOUS_IO
#define _POSIX_SYNCHRONIZED_IO
#define _POSIX_FSYNC
#define _POSIX_MAPPED_FILES
#define _POSIX_MEMLOCK
#define _POSIX_MEMLOCK_RANGE
#define _POSIX_MEMORY_PROTECTION
#define _POSIX_PRIORITY_SCHEDULING
#define _POSIX_SHARED_MEMORY_OBJECTS
#define _POSIX_TIMERS
#define _POSIX_REALTIME_SIGNALS
#define _POSIX_MESSAGE_PASSING 
#define _POSIX_SEMAPHORES    

/*
 * NOTE: _SC_PAGESIZE for sysconf() is defined both in POSIX 1003.1b,
 * and in AES, below. Keep same as AES definition.
 */
#ifndef _AES_SOURCE
#define _SC_PAGESIZE		43
#endif /* ifndef _AES_SOURCE */

/* Realtime arguments for the sysconf() function */
#define _SC_4VERSION            100
#define _SC_LISTIO_AIO_MAX      101
#define _SC_AIO_MAX             102
#define _SC_CLOCKDRIFT_MAX      103
#define _SC_DELAYTIMER_MAX      104
#define _SC_RTSIG_MAX		105
#define _SC_SEM_NAME_MAX	106
#define _SC_SEM_NSEMS_MAX	107
#define _SC_TIMER_MAX		109
#define _SC_ASYNCHRONOUS_IO	110
#define _SC_FSYNC		112
#define _SC_MAPPED_FILES	113
#define _SC_MEMLOCK		114
#define _SC_MEMLOCK_RANGE	115
#define _SC_MEMORY_PROTECTION	116
#define _SC_MESSAGE_PASSING	117
#define _SC_PRIORITIZED_IO	118
#define _SC_PRIORITY_SCHEDULING	119
#define _SC_REALTIME_SIGNALS	121
#define _SC_SHARED_MEMORY_OBJECTS 122
#define _SC_SYNCHRONIZED_IO	123
#define _SC_TIMERS		124
#define _SC_SEMAPHORES          125
#define _SC_SEM_VALUE_MAX       126
#define _SC_MQ_OPEN_MAX         127
#define _SC_MQ_PRIO_MAX         128
#define _SC_SIGQUEUE_MAX	130
/*
 * NOTE: these values are hardcoded for SIGRTMIN and SIGRTMAX
 * in <sys/signal.h>. Any change here must be reflected there.
 */
#define _SC_RTSIG_LOW		131
#define _SC_RTSIG_HI		132
#endif /* _POSIX_C_SOURCE >= 199309L */

/*
 * Definitions for XSH5.
 */
#if defined (_XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)
#define	_SC_AIO_LISTIO_MAX	150
#define	_SC_AIO_PRIO_DELTA_MAX	151
#define	_SC_XBS5_ILP32_OFF32	152
#define	_SC_XBS5_ILP32_OFFBIG	153
#define	_SC_XBS5_LP64_OFF64	154
#define	_SC_XBS5_LPBIG_OFFBIG	155
#endif /* _XOPEN_SOURCE>=500 */

/*
 * definitions for the MP extensions to sysconf()
 */

#define _SC_NPROC_CONF  200
#define _SC_NPROCESSORS_CONF _SC_NPROC_CONF
#define	_SC_NPROC_ONLN	201
#define	_SC_NPROCESSORS_ONLN _SC_NPROC_ONLN

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199506L)
/*
 * definitions for the POSIX thread arguments to sysconf()
 */
/* This value is to be used when standard specifications, require
 * functional features to be disabled */
#define _SC_THREAD_DISABLED              209

#define _SC_THREAD_DESTRUCTOR_ITERATIONS 210
#define _SC_THREAD_KEYS_MAX              211
#define _SC_THREAD_STACK_MIN             212
#define _SC_THREAD_THREADS_MAX           213
#define _SC_THREADS                      214
#define _SC_THREAD_SAFE_FUNCTIONS        215
#define _SC_THREAD_ATTR_STACKSIZE        216
#if _XOPEN_SOURCE>=500 && !defined(_OSF_SOURCE)
# define _SC_THREAD_PRIORITY_SCHEDULING _SC_THREAD_DISABLED
#else
# define _SC_THREAD_PRIORITY_SCHEDULING 217
#endif
#define	_SC_GETGR_R_SIZE_MAX		218
#define	_SC_GETPW_R_SIZE_MAX		219
#define	_SC_LOGIN_NAME_MAX		220
#define	_SC_TTY_NAME_MAX		221
#define	_SC_THREAD_ATTR_STACKADDR	222
#define	_SC_THREAD_PRIO_INHERIT		223
#define	_SC_THREAD_PRIO_PROTECT		224
#define	_SC_THREAD_PROCESS_SHARED	225
#endif /* _POSIX_C_SOURCE >= 199506L */

#ifndef NULL
#define NULL	0L
#endif

/* arguments for the confstr() function */

#define	_CS_PATH		1

#ifdef	_OSF_SOURCE
#define	_CS_SYSTEM_BANNER	2
#define	_CS_VENDOR_NAME		3
#define	_CS_PRODUCT_NAME	4
#define	_CS_SYSTEM_VERSION	5
#define	_CS_VENDOR_ABBREV	6
#endif	/* _OSF_SOURCE */

#define	_CS_XBS5_ILP32_OFF32_CFLAGS	7
#define	_CS_XBS5_ILP32_OFF32_LDFLAGS	8
#define	_CS_XBS5_ILP32_OFF32_LIBS	9
#define	_CS_XBS5_ILP32_OFF32_LINTFLAGS	10
#define	_CS_XBS5_ILP32_OFFBIG_CFLAGS	11
#define	_CS_XBS5_ILP32_OFFBIG_LDFLAGS	12
#define	_CS_XBS5_ILP32_OFFBIG_LIBS	13
#define	_CS_XBS5_ILP32_OFFBIG_LINTFLAGS	14
#define	_CS_XBS5_LP64_OFF64_CFLAGS	15
#define	_CS_XBS5_LP64_OFF64_LDFLAGS	16
#define	_CS_XBS5_LP64_OFF64_LIBS	17
#define	_CS_XBS5_LP64_OFF64_LINTFLAGS	18
#define	_CS_XBS5_LPBIG_OFFBIG_CFLAGS	19
#define	_CS_XBS5_LPBIG_OFFBIG_LDFLAGS	20
#define	_CS_XBS5_LPBIG_OFFBIG_LIBS	21
#define	_CS_XBS5_LPBIG_OFFBIG_LINTFLAGS	22

#define _CSPATH			"/usr/bin"

/* arguments for the sysconf() function */

#define _SC_ARG_MAX		1
#define _SC_CHILD_MAX		2
#define _SC_CLK_TCK		3
#define _SC_JOB_CONTROL		4
#define _SC_NGROUPS_MAX		5
#define _SC_OPEN_MAX		6
#define _SC_SAVED_IDS		8
#define _SC_VERSION		9
#define _SC_STREAM_MAX		13
#define _SC_TZNAME_MAX		14
#define _SC_BC_BASE_MAX         15
#define _SC_BC_DIM_MAX          16
#define _SC_BC_SCALE_MAX        17
#define _SC_BC_STRING_MAX       18
#define _SC_COLL_WEIGHTS_MAX    20
#define _SC_EXPR_NEST_MAX       21
#define _SC_LINE_MAX            22
#define _SC_2_C_DEV             23
#define _SC_2_FORT_DEV          24
#define _SC_2_FORT_RUN          25
#define _SC_2_LOCALEDEF         26
#define _SC_2_SW_DEV            27
#define _SC_2_VERSION           28
#define _SC_RE_DUP_MAX          29
#define _SC_THREAD_MAX          34
#define _SC_TASK_MAX            35
#define _SC_MAXUTHREADS         36
#define _SC_STACK_SIZE          37
#define _SC_STACK_SIZE_MAX      38
#define _SC_DATA_SIZE           39
#define _SC_DATA_SIZE_MAX       40
#define _SC_ADDR_SPACE          41
#define _SC_ADDR_SPACE_MAX      42
#define _SC_2_UPE               47

#ifdef _XOPEN_SOURCE

#define _SC_XOPEN_CRYPT         48
#define _SC_XOPEN_ENH_I18N      49
#define _SC_XOPEN_SHM           50
#define _SC_XOPEN_XCU_VERSION   51
#define _SC_2_C_BIND            52
#endif

#define _SC_2_C_VERSION         53
#define _SC_2_CHAR_TERM         54

#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)
#define _SC_XOPEN_UNIX          55
#define _SC_IOV_MAX 		56		/* required for spec1170 */
#endif

#if defined (_XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)
#define _SC_XOPEN_LEGACY		57
#define _SC_XOPEN_REALTIME		58
#define _SC_XOPEN_REALTIME_THREADS	59
#endif

#endif /* _POSIX_C_SOURCE >= 1 */
#endif /* ifndef _KERNEL */
#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 1) 

/* arguments for the pathconf() function */

#define _PC_CHOWN_RESTRICTED	10
#define _PC_LINK_MAX		11
#define _PC_MAX_CANON		12
#define _PC_MAX_INPUT		13
#define _PC_NAME_MAX		14
#define _PC_NO_TRUNC		15
#define _PC_PATH_MAX		16
#define _PC_PIPE_BUF		17
#define _PC_VDISABLE 		18
#if defined(_KERNEL) || defined (_XOPEN_SOURCE) && (_XOPEN_SOURCE>=500) 
#define _PC_FILESIZEBITS	22
#endif /* _XOPEN_SOURCE>=500 || defined(_KERNEL) */
#if _POSIX_C_SOURCE >= 199309L
#define _PC_ASYNC_IO		19
#define _PC_SYNC_IO		20
#define _PC_PRIO_IO		-1
/*
 * Return values for _PC queries.
 */
#define _POSIX_ASYNC_IO		1
#define _POSIX_SYNC_IO		2
#endif
#define _PC_ACL_EXTENDED	23

#endif /* _POSIX_C_SOURCE >= 1 */
#ifndef _KERNEL

#ifdef _XOPEN_SOURCE

#define _SC_PASS_MAX		7
#define _SC_XOPEN_VERSION	19

#define _XOPEN_VERSION		500
#define _XOPEN_XCU_VERSION	5

#if defined (_XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)
#define _XOPEN_LEGACY           1
#define _XOPEN_REALTIME         -1
#define _XOPEN_REALTIME_THREADS -1
#endif

#define _XOPEN_XPG4		4
#define	_XOPEN_CRYPT		1
#define _XOPEN_ENH_I18N		1 /* Supports enhanced internationalization */
#define _XOPEN_SHM		1 /* Supports Shared Memory Feature Group */
#define _XOPEN_UNIX		1 /* Supports XSH4 extended feature group */

#define	_XBS5_ILP32_OFF32       -1
#define	_XBS5_ILP32_OFFBIG	-1
#define	_XBS5_LP64_OFF64	1
#define	_XBS5_LPBIG_OFFBIG	-1

/*** AAB-XPG4 Illegal symbols ***/
#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)
#define F_ULOCK	0	/* Unlock a previously locked region */
#define F_LOCK	1	/* Lock a region for exclusive use */
#define F_TLOCK	2	/* Test and lock a region for exclusive use */
#define F_TEST	3	/* Test a region for other processes locks */
#endif /*_OSF_SOURCE || _XOPEN_SOURCE_EXTENDED */
/*AAB-XPG4*/

#endif /* _XOPEN_SOURCE */

#if defined(_AES_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)

#define _SC_ATEXIT_MAX		10
#define _SC_PAGE_SIZE		11

#ifndef _SC_PAGESIZE
#define _SC_PAGESIZE		43  /* NOTE: keep synch with realtime, above */
#endif

#ifdef _AES_SOURCE
#define _SC_AES_OS_VERSION	12

#define _AES_OS_VERSION		1
#endif

extern int  fchown __((int, uid_t, gid_t));
extern int  ftruncate __((int, off_t));
#ifdef _XOPEN_SOURCE_EXTENDED
extern int  readlink __((const char *, char *, size_t));
extern int  fchdir __((int));
extern long gethostid __((void));
#else
extern int  readlink __((const char *, char *, int));
#endif
extern int  symlink __((const char *, const char *));
#ifdef _AES_SOURCE
extern int  setgroups __((int, gid_t []));
#endif
extern int  truncate __((const char *, off_t));

#endif 	/* _AES_SOURCE || _XOPEN_SOURCE_EXTENDED */

#ifdef _XOPEN_SOURCE

extern char *crypt __((const char *, const char *));
#if !defined(_LIBC_POLLUTION_H_) && !defined(__V40_OBJ_COMPAT)
#ifdef __DECC
#pragma extern_prefix "_E"
#else
#define cuserid(__a) _Ecuserid(__a)
#endif /* __DECC */
#endif /* __V40_OBJ_COMPAT && _LIBC_POLLUTION_H_ */

extern char *__V40_OC(cuserid) __((char *));

#if !defined(_LIBC_POLLUTION_H_) && !defined(__V40_OBJ_COMPAT) && defined(__DECC)
#pragma extern_prefix ""
#endif
extern char *ctermid __((char *));
extern void encrypt __((char [], int));
extern char *getpass __((const char *));
extern int  nice __((int));

#define _SC_MAJ_NUM_SHIFT          53

#endif /* _XOPEN_SOURCE */

/*** AAB-XPG4 The protos below were removed from above since XPG4
 does not allow them to be visible. They were put here just in case
 they are needed for compilation. Should remove them if not needed ***/

#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)

#ifdef _XOPEN_SOURCE_EXTENDED
extern int  brk __((void *));
extern int  gethostname __((char *, size_t));
#else
extern int  brk __((char *));
extern int  gethostname __((char *, int));
#endif
extern int  getpagesize __((void));
extern pid_t getpgid __((pid_t));
extern pid_t getsid __((pid_t));
extern char *getwd __((char *));
extern int lchown __((const char *, uid_t, gid_t));
extern int lockf __((int, int, off_t));
#ifdef _XOPEN_SOURCE_EXTENDED
#if defined (_XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)
extern void *sbrk __((intptr_t));
#else
	/* The standard, before it was fixed, said the arg was an int. 
	 * An int was not big enough for large address spaces. 
	 * We are intentionally breaking the standard here.
	 */
extern void *sbrk __((long)); 
#endif /* _XOPEN_SOURCE>=500 */
extern useconds_t ualarm __((useconds_t, useconds_t));
#else
extern void *sbrk __((ssize_t));
extern unsigned int ualarm __((unsigned int, unsigned int));
#endif
extern void sync __((void));
#if defined(_XOPEN_SOURCE_EXTENDED) || defined(__SVID__)

#if defined(_XOPEN_SOURCE_EXTENDED) && !defined(_LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix "_E"
#else
#define setpgrp() _Esetpgrp()
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */

extern pid_t __R(setpgrp) __((void));

#if defined(_XOPEN_SOURCE_EXTENDED) && !defined( _LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix ""
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */

#else
extern int setpgrp __((pid_t, pid_t));
#endif

extern int  setregid __((gid_t, gid_t));
extern int  setreuid __((uid_t, uid_t));
extern pid_t vfork __((void));
extern int  getdtablesize __((void));

#ifdef _OSF_SOURCE
extern char *gettxt __((const char *, const char *));
extern char *getenv __((const char *));
extern int bindresvport __((int, struct sockaddr_in *));
extern char *crypt16 __((const char *, const char *));
extern void endnetgrent __((void));
#if defined(_THREAD_SAFE) || defined(_REENTRANT)
extern void endnetgrent_r __((void *));
extern int getnetgrent_r __((const char **, const char **, const char **,
			     void *));
#endif
extern int getnetgrent __((const char **, const char **, const char **));
extern int innetgr __((const char *, const char *,
		       const char *, const char *));
extern int rcmd __((char **, u_short, char *, char *, char *, int *));
extern int rcmd2 __((char **, u_short, char *, char *, char *, int *, int));
extern int rcmd_af __((char **, u_short, char *, char *, char *, int *, int));
extern int rcmd2_af __((char **, u_short, char *, char *, char *, int *, int,
			int));
extern int rename __((const char *, const char *));
extern int rexec __((char **, int, char *, char *, char *, int *));
extern int rexec_af __((char **, int, char *, char *, char *, int *, int));
extern int rresvport __((int *));
extern int rresvport2 __((int *, int));
extern int rresvport2_af __((int *, int, int));
extern int rresvport_af __((int *, int));
extern int ruserok __((char *, int, char *, char *));
extern int  seteuid __((uid_t));
extern int  setegid __((gid_t));
extern int  setlogin __((char *));
extern void setnetgrent __((const char *));
#if defined(_THREAD_SAFE) || defined(_REENTRANT)
extern void setnetgrent_r __((const char *, void **));
#endif
extern int  setrgid __((gid_t));
extern int  setruid __((uid_t));
extern int  syscall __((int, ...));
#endif

#endif /*_OSF_SOURCE || _XOPEN_SOURCE_EXTENDED */
#endif /* ifndef _KERNEL */	
#ifdef __cplusplus
}
#endif
#endif /* _UNISTD_H_ */
