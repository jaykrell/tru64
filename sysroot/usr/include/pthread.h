/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: pthread.template.h,v $
 * Revision 1.1.39.3  2004/11/01  17:49:42  devbld_zko
 * 	DECThreads V3.20-068 submit
 * 	thdbl20-3-dahl
 * Merge Information:  Non-Visual Merge: User specified tree thdbl19
 *     User Revision:  thdbl20_br:1.1.25.6 Local Ancestor: n/a
 *    Merge Revision:  thdbl19_br:1.1.20.5
 *   Common Ancestor:  1.1.20.4
 * 	Merge thdbl19-8-dahl into BL20.
 *
 * Revision 1.1.20.5  2004/10/13  17:41:13  Tom_Dahl
 * 	thdbl19-8-dahl
 * 	Add pthread_mutex_tryforcedlock_np and _POSIX_THREAD_PROCESS_SHARED.
 * 
 * Revision 1.1.25.6  2004/01/27  17:15:31  Dave_Butenhof
 * 	thdbl20-9-butenhof
 * 	Merge thdbl19-16-butenhof into bl20. (No-op merge of backported fix.)
 * 
 * Revision 1.1.20.4  2004/01/06  16:07:43  Dave_Butenhof
 * 	thdbl19-16-butenhof
 * 	Repair PTHREAD_RWLOCK_INITWITHNAME_NP.
 * 
 * Revision 1.1.25.5  2003/12/03  14:06:05  Dave_Butenhof
 * 	thdbl20-7-butenhof
 * 	Merge thdbl22-3-butenhof, pthread_getcputime_np(). Also backport the
 * 	pthread_attr_{s|g}etstack() interfaces from XSH6.
 * 
 * Revision 1.1.25.4  2003/11/18  19:38:56  RaeLyn_Crowell
 * 	thdbl20-1-crowell
 * Merge Information:  Non-Visual Merge: User specified tree thdbl19
 *     User Revision:  thdbl20_br:1.1.25.3 Local Ancestor: n/a
 *    Merge Revision:  thdbl19_br:1.1.20.3
 *   Common Ancestor:  1.1.20.2
 * 
 * Revision 1.1.20.3  2003/11/17  18:34:03  RaeLyn_Crowell
 * 	thdbl19-5-crowell
 * 	For all OpenVMS platforms, Alpha and IA64, define prototype for
 * 	pthread_join64.  Clean up conditionals surrounding prototype.
 * 
 * Revision 1.1.25.3  2003/09/03  14:45:30  Dave_Butenhof
 * 	thdbl20-6-butenhof
 * 	Remove #error that artificially breaks gcc compilation. (This
 * 	isn't to say that it WORKS, or is tested/supported; we're just
 * 	being "good sports" and not preventing it.)
 * 	[2003/08/29  17:25:27  Dave_Butenhof]
 * 	Fix PTHREAD_RWLOCK_INITWITHNAME_NP!
 * 	[2003/08/22  14:19:02  Dave_Butenhof]
 * 
 * Revision 1.1.10.13  2003/02/12  16:12:43  Peter_Portante
 * 	thdbl21-3-portante: For IA-64 platforms, PTHREAD_STACK_MIN is two 8K
 * 	pages. Add the XOPEN pthread_attr_{g|s}etstack() interface names, and
 * 	provide macros to map our pthread_attr_{g|s}etstackaddr_np()
 * 	interfaces to these new names.
 * 
 * Revision 1.1.25.2  2002/10/22  19:48:43  Peter_Portante
 * Merge Information:  Non-Visual Merge: User specified tree thdbl19
 *     User Revision:  thdbl20_br:1.1.25.1 Local Ancestor: n/a
 *    Merge Revision:  thdbl19_br:1.1.20.2
 *   Common Ancestor:  1.1.20.1
 * 
 * Revision 1.1.25.1  2002/08/14  19:35:27  devbld_zko
 * 	Populate thdbl20
 * 
 * Revision 1.1.20.2  2002/07/31  18:22:42  Peter_Portante
 * Merge Information:  Non-Visual Merge: User specified tree thdbl18
 *     User Revision:  thdbl19_br:1.1.20.1 Local Ancestor: n/a
 *    Merge Revision:  thdbl18_br:1.1.3.6
 *   Common Ancestor:  1.1.3.5
 * 
 * Revision 1.1.3.6  2002/06/25  19:33:06  Peter_Portante
 * Merge Information:  Non-Visual Merge: User specified tree thdbl17
 *     User Revision:  thdbl18_br:1.1.3.5 Local Ancestor: n/a
 *    Merge Revision:  thdbl17_br:1.1.22.1
 *   Common Ancestor:  1.1.22.1
 * 
 * Revision 1.1.22.1  2002/05/17  14:07:30  Peter_Portante
 * 	Moved the guts of pthread.h here since we now generate the actual
 * 	header file from this template.
 * 
 * Revision 1.1.10.8  2002/02/07  17:33:30  Dave_Butenhof
 * 	Include <thd_libc_protect.h> for internal (CORE) UNIX builds so
 * 	we can protect against preemption the symbols exposed by header
 * 	files used in <pthread.h>.
 * 
 * Revision 1.1.10.7  2002/01/28  19:51:23  Mike_Neverisky
 * 	Initiating thdbl20
 * Merge Information:  Non-Visual Merge: User specified tree thdbl19
 *     User Revision:  thddev_br:1.1.10.5 Local Ancestor: n/a
 *    Merge Revision:  thdbl19_br:1.1.20.1
 *   Common Ancestor:  1.1.10.5
 * 	Functional NOP merge of thdbl19 into thddev
 * 
 * Revision 1.1.20.1  2002/01/25  21:33:19  devbld_zko
 * 	Populate thdbl19 from thddev
 * 
 * Revision 1.1.10.5  2001/12/12  14:53:46  Dave_Butenhof
 * 	Don't use asm() for TEB unless asked and able. Make sure DEC C++
 * 	includes <c_asm.h>.
 * 
 * Revision 1.1.10.4  2001/10/31  16:46:55  Mike_Neverisky
 * 	Fix OldLog tokens
 * Merge Information:  Non-Visual Merge: User specified tree thdbl18
 *     User Revision:  thddev_br:1.1.10.3 Local Ancestor: n/a
 *    Merge Revision:  thdbl18_br:1.1.3.5
 *   Common Ancestor:  1.1.3.4
 * 	[2001/10/31  16:38:40  Mike_Neverisky]
 * 
 * Revision 1.1.3.5  2001/10/26  19:11:59  Mike_Neverisky
 * 	Correct OldLog token to fix comment stripping problem
 * 	Correct OldLog token to fix comment stripping problem
 * 
 * Revision 1.1.10.3  2001/08/23  17:59:51  Dave_Butenhof
 * 	Fix up IA64 support.
 * 
 * Revision 1.1.10.2  2001/07/20  16:37:00  Dave_Butenhof
 * Merge Information:  Visual Merge: User specified revision Dave_Butenhof_bl18_br
 *     User Revision:  thddev_br:1.1.10.1 Local Ancestor: n/a
 *    Merge Revision:  Dave_Butenhof_bl18_br:1.1.11.1
 *   Common Ancestor:  1.1.3.4
 * 
 * Revision 1.1.11.1  2001/07/12  19:37:38  Dave_Butenhof
 * 	Restore IA-64 support.
 * 
 * Revision 1.1.10.1  2001/04/23  22:16:25  Webb_Scales
 * 	Populate thddev from thdbl18.
 * 
 * Revision 1.1.3.4  2001/03/27  12:28:45  Dave_Butenhof
 * 	Fix a comment.
 * 	[2001/03/21  18:44:42  Dave_Butenhof]
 * 	Modify to work with old and new <sys/types.h> on UNIX.
 * 	[2001/03/20  15:31:09  Dave_Butenhof]
 * 	We need to prefix the non-portable TEB definitions with __ for
 * 	namespace purity on UNIX. Do the same on OpenVMS to support the
 * 	common definitions depending on the types.
 * 	[2001/03/20  15:05:31  Dave_Butenhof]
 * 
 * Revision 1.1.3.3  2001/02/16  23:22:01  Peter_Portante
 * 	Add a strong comment to warn users against dereferencing a
 * 	pthread_t in order to access TEB fields. Add home_rad to TEB,
 * 	bumping the TEB version.
 * 
 * Revision 1.1.3.2  2001/02/01  18:12:05  Dave_Butenhof
 * 	Fix a typo.
 * 	[2001/02/01  13:30:58  Dave_Butenhof]
 * 	Remove some VAX code.
 * 	[2001/01/30  16:32:46  Dave_Butenhof]
 * 	Fix a few name references in comments.
 * 	[2001/01/29  18:36:50  Dave_Butenhof]
 * 	Tru64 UNIX <sys/types.h> doesn't currently typedef pthreadTeb_p.
 * 	As a temporary workaround, use "pthreadTeb_t*" instead. (This
 * 	seems better than depending on separate types.h submits to every
 * 	OS version that DECthreads 3.18 supports.)
 * 	[2001/01/29  17:51:26  Dave_Butenhof]
 * 	Merge my private <pthread.h> cleanups into pthread.template.h.
 * 	[2001/01/12  15:42:22  Dave_Butenhof]
 * 
 * Revision 1.1.3.1  2001/01/11  18:11:15  Bill_Blanding
 * 	This file is a template which is used for the generation
 * 	of the include file pthread.h during a build.
 * 	It was created from and replaces pthread.h.
 * 	All future changes desired for pthread.h.
 * 	must be made either to this file or to
 * 	the text substitution files [identified in pthread_include.mk]
 * 	which are merged with this template during the build process.
 * 	Text insertion points are identified by the string:
 * 	__REPLACE_ME_WITH_FILE.
 * 
 * $EndLog$
 */
/*
 * $OldLog: pthread.template.h,v $ 
 * Revision 1.1.35.52  2001/01/11  15:25:25  Mike_Neverisky
 * 	version bump
 * 
 * Revision 1.1.35.51  2001/01/05  20:58:15  Peter_Portante
 * 	Bump version.
 * 
 * Revision 1.1.35.50  2000/12/29  16:28:31  Peter_Portante
 * 	Bump version.
 * 
 * Revision 1.1.35.49  2000/12/23  01:07:55  Peter_Portante
 * 	Bump version.
 * 
 * Revision 1.1.35.48  2000/12/19  13:28:14  Mike_Neverisky
 * 	increment build number to 100
 * 
 * Revision 1.1.35.47  2000/12/11  17:43:13  Peter_Portante
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree devbld_zko:thdbl18
 *     User Revision:  Peter_Portante_bl18_br:1.1.68.2 Local Ancestor:1.1.35.45
 *    Merge Revision:  thdbl18_br:1.1.35.46
 *   Common Ancestor:  1.1.35.45
 * 	Bump version.
 * 
 * Revision 1.1.35.46  2000/12/04  19:51:23  Mike_Neverisky
 * 	version bump
 * 
 * Revision 1.1.35.45  2000/12/01  18:20:32  Tim_Rice
 * 	Bump version for Software.Com fix to pthread_kill().
 * 
 * Revision 1.1.35.44  2000/11/03  20:13:58  Peter_Portante
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree devbld_zko:thdbl18
 *     User Revision:  Peter_Portante_bl18_br:1.1.68.1 Local Ancestor:1.1.67.2
 *    Merge Revision:  thdbl18_br:1.1.35.43
 *   Common Ancestor:  1.1.35.41
 * 
 * Revision 1.1.35.43  2000/11/03  15:39:28  Mike_Neverisky
 * 	increment version
 * 
 * Revision 1.1.35.42  2000/11/02  14:27:53  Tom_Dahl
 * Merge Information:  Non-Visual Merge: User specified tree thdbl17
 *     User Revision:  thdbl18_br:1.1.35.41 Local Ancestor: n/a
 *    Merge Revision:  thdbl17_br:1.1.29.13
 *   Common Ancestor:  1.1.29.12
 * 	Merge a version change from thdbl17 into thdbl18.
 * 
 * Revision 1.1.29.13  2000/10/12  15:27:16  Tom_Dahl
 * 	Version bump.
 * 
 * Revision 1.1.35.41  2000/10/07  17:59:46  Peter_Portante
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree devbld_zko:thdbl18
 *     User Revision:  Peter_Portante_bl18_br:1.1.62.3 Local Ancestor:1.1.35.39
 *    Merge Revision:  thdbl18_br:1.1.35.40
 *   Common Ancestor:  1.1.35.39
 * 
 * Revision 1.1.35.40  2000/10/06  17:53:25  Mike_Neverisky
 * 	Bump version for Peter's Yankee compiler enabler submit
 * 
 * Revision 1.1.35.39  2000/09/19  23:00:47  Mike_Neverisky
 * 	bump to -042
 * 
 * Revision 1.1.35.38  2000/09/12  18:38:40  Mike_Neverisky
 * 	Bump version
 * 
 * Revision 1.1.29.12  2000/09/01  18:37:14  devbld_zko
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree devbld_zko:thdbl16
 *     User Revision:  thdbl17_br:1.1.29.11 Local Ancestor:1.1.19.8
 *    Merge Revision:  thdbl16_br:1.1.19.19
 *   Common Ancestor:  1.1.19.18
 * 	Fix a bad merge.
 * 
 * Revision 1.1.29.11  2000/09/01  18:23:51  Peter_Portante
 * Merge Information:  Non-Visual Merge: User specified tree thdbl16
 *     User Revision:  Peter_Portante_bl17_br:1.1.57.1 Local Ancestor:1.1.19.18
 *    Merge Revision:  thdbl16_br:1.1.19.19
 *   Common Ancestor:  1.1.19.18
 * 	Merge BL16 changes into BL17, bumping version number.
 * 
 * Revision 1.1.19.19  2000/08/28  18:03:26  Peter_Portante
 * 	Bump version.
 * 
 * Revision 1.1.35.36  2000/08/22  17:07:07  Mike_Neverisky
 * 	version bump
 * 
 * Revision 1.1.35.35  2000/08/14  14:47:57  Peter_Portante
 * 	Bump version.
 * 
 * Revision 1.1.19.18  2000/08/14  19:32:52  Mary_Sullivan
 * 	DECthreads V3.16-027
 * 
 * Revision 1.1.35.34  2000/08/09  15:04:48  Peter_Portante
 * 	Bump version.
 * 
 * Revision 1.1.54.1  2000/08/02  19:46:57  Peter_Portante
 * 	Bump version and fail any compilation without -pthread.
 * 
 * Revision 1.1.29.10  2000/08/02  19:21:22  Mary_Sullivan
 * 	Restore PTHREAD_STACK_MIN to 4608 for VAX platforms.  We
 * 	initially increased this value to 6656 to allow for increased
 * 	stack usage in our VAX production builds which resulted from
 * 	inlined optimizations.  As we have disabled these optimizations
 * 	in our VAX builds, we can restore the minimum stack size to
 * 	the value specified in prior releases.
 * 
 * Revision 1.1.35.33  2000/07/28  14:21:17  Peter_Portante
 * 	Bump version.
 * 
 * Revision 1.1.35.32  2000/07/24  14:36:45  Mike_Neverisky
 * 	version increment
 * 
 * Revision 1.1.35.31  2000/07/10  15:16:21  Peter_Portante
 * 	Bump version.
 * 
 * Revision 1.1.35.30  2000/07/05  13:40:43  Mike_Neverisky
 * 	version increment
 * 
 * Revision 1.1.35.29  2000/06/16  14:51:09  Peter_Portante
 * 	Bump version.
 * 
 * Revision 1.1.35.28  2000/06/14  20:00:29  Mike_Neverisky
 * 	version
 * 
 * Revision 1.1.29.9  2000/06/14  18:24:16  Mary_Sullivan
 * 	Remove block comment and threads version declaration
 * 	that appear to have inadvertently duplicated when the
 * 	thdbl16 version of this file was merged forward.
 * 
 * Revision 1.1.35.27  2000/06/12  17:52:09  Dave_Butenhof
 * Merge Information:  Visual Merge: User specified default merge the submit tree devbld_zko:thdbl18
 *     User Revision:  Dave_Butenhof_bl18_br:1.1.43.16 Local Ancestor:1.1.35.25
 *    Merge Revision:  thdbl18_br:1.1.35.26
 *   Common Ancestor:  1.1.35.25
 * 	Merge
 * 	[2000/06/09  18:31:06  Dave_Butenhof]
 * 	Clean up history & comments
 * 	[2000/05/15  18:09:54  Dave_Butenhof]
 * 	Bump version.
 * 	[2000/05/04  12:25:54  Dave_Butenhof]
 * 	Update version.
 * 	[2000/03/09  18:04:09  Dave_Butenhof]
 * 
 * Revision 1.1.35.26  2000/06/09  15:18:08  Mike_Neverisky
 * 	version bump
 * 
 * Revision 1.1.35.25  2000/05/31  12:27:50  Mike_Neverisky
 * 	version bump
 * 
 * Revision 1.1.35.24  2000/05/26  19:26:00  Peter_Portante
 * 	Version -026
 * 
 * Revision 1.1.35.23  2000/05/24  16:35:29  Peter_Portante
 * 	Version -025
 * 
 * Revision 1.1.35.22  2000/05/23  18:04:22  Mike_Neverisky
 * 	Version -024
 * 
 * Revision 1.1.35.21  2000/05/11  20:07:19  Peter_Portante
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree devbld_zko:thdbl18
 *     User Revision:  Peter_Portante_zu_br:1.1.45.9 Local Ancestor:1.1.35.18
 *    Merge Revision:  thdbl18_br:1.1.35.20
 *   Common Ancestor:  1.1.35.18
 * 	Bump version number
 * 
 * Revision 1.1.35.20  2000/05/05  15:06:55  Mike_Neverisky
 * 	version -022
 * 
 * Revision 1.1.19.17  2000/05/04  17:28:18  Dave_Butenhof
 * Merge Information:  Visual Merge: User specified default merge the submit tree devbld_zko:thdbl16
 *     User Revision:  Dave_Butenhof_bl16_br:1.1.47.1 Local Ancestor:1.1.19.14
 *    Merge Revision:  thdbl16_br:1.1.19.16
 *   Common Ancestor:  1.1.19.14
 * 
 * Revision 1.1.19.15  2000/05/03  18:58:48  Mike_Neverisky
 * 	version -024
 * 	[2000/05/03  18:58:41  Mike_Neverisky]
 * 
 * Revision 1.1.35.19  2000/05/03  13:55:30  Mike_Neverisky
 * 	Version bump to -021
 * 
 * Revision 1.1.19.16  2000/05/03  19:22:35  Mike_Neverisky
 * 	version -025
 * 
 * Revision 1.1.35.18  2000/04/21  19:25:21  Mike_Neverisky
 * 	version
 * 
 * Revision 1.1.35.17  2000/04/21  14:00:41  Mike_Neverisky
 * 	version
 * 
 * Revision 1.1.35.16  2000/04/19  18:28:41  Mike_Neverisky
 * 	Version bump (again)
 * 
 * Revision 1.1.35.15  2000/04/19  14:39:43  Mike_Neverisky
 * 	Version bump
 * 
 * Revision 1.1.35.12  2000/03/31  20:32:15  Mike_Neverisky
 * 	version bump
 * 
 * Revision 1.1.35.11  2000/03/29  14:33:20  Mike_Neverisky
 * 	version bump
 * 	bump version number
 * 
 * Revision 1.1.35.10  2000/03/27  00:50:09  Peter_Portante
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree devbld_zko:thdbl18
 *     User Revision:  Peter_Portante_zu_br:1.1.48.1 Local Ancestor:1.1.47.1
 *    Merge Revision:  thdbl18_br:1.1.35.9
 *   Common Ancestor:  1.1.35.5
 * 	Bump the version number for code review comments.
 * 	[2000/03/22  23:14:10  Peter_Portante]
 * 
 * Revision 1.1.35.9  2000/03/26  22:03:51  devbld_zko
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree zuluos
 *     User Revision:  thdbl18_br:1.1.35.8 Local Ancestor:1.1.29.5
 *    Merge Revision:  ZULUOS:1.1.33.4
 *   Common Ancestor:  1.1.19.4
 * 
 * Revision 1.1.35.8  2000/03/26  20:53:25  devbld_zko
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree devbld_zko:thdbl18
 *     User Revision:  thdnuma_br:1.1.47.1 Local Ancestor: n/a
 *    Merge Revision:  thdbl18_br:1.1.35.7
 *   Common Ancestor:  1.1.35.5
 * 	Bump the version number for the NUMA changes.
 * 	[2000/03/21  02:40:52  Peter_Portante]
 * 
 * Revision 1.1.35.7  2000/03/26  13:38:45  devbld_zko
 * 	Merge from thdbl18 of decthreads-26-dahl
 * Merge Information:  Non-Visual Merge: User specified tree thdbl18
 *     User Revision:  thdnumarev_br:1.1.45.1 Local Ancestor: n/a
 *    Merge Revision:  thdbl18_br:1.1.35.6
 *   Common Ancestor:  1.1.35.5
 * 	merge from thdbl18
 * 	[2000/03/21  18:33:28  Mike_Neverisky]
 * 	Fix the build number identification.
 * 	[2000/03/21  00:52:36  Peter_Portante]
 * 
 * Revision 1.1.48.1  2000/03/22  23:14:10  Peter_Portante
 * 	Bump the version number for code review comments.
 * 
 * Revision 1.1.47.1  2000/03/21  02:40:52  Peter_Portante
 * 	Bump the version number for the NUMA changes.
 * 
 * Revision 1.1.45.1  2000/03/21  00:52:36  Peter_Portante
 * 	Fix the build number identification.
 * 
 * Revision 1.1.35.5  2000/03/17  19:48:33  Tom_Dahl
 * 	Increase the build number to V3.18-005.
 * 
 * Revision 1.1.33.4  2000/03/16  21:56:45  Mike_Neverisky
 * 	DECthreads T3.17-005 submit
 * 	Correct osversion.mk for Zulu BL8
 * 
 * Revision 1.1.35.3  2000/03/14  23:20:38  Mike_Neverisky
 * 	forward merge from thdbl17
 * Merge Information:  Non-Visual Merge: User specified tree thdbl17
 *     User Revision:  thdbl18_br:1.1.35.2 Local Ancestor: n/a
 *    Merge Revision:  thdbl17_br:1.1.29.8
 *   Common Ancestor:  1.1.29.1
 * 	thdbl17 forward merge
 * 
 * Revision 1.1.29.8  2000/03/14  17:22:23  Mike_Neverisky
 * 	thdbl16 froward merge
 * Merge Information:  Non-Visual Merge: User specified tree thdbl16
 *     User Revision:  thdbl17_br:1.1.29.7 Local Ancestor: n/a
 *    Merge Revision:  thdbl16_br:1.1.19.14
 *   Common Ancestor:  1.1.19.8
 * 	thdbl16 forward merge
 * 
 * Revision 1.1.33.3  2000/03/10  14:53:23  Mike_Neverisky
 * 	DECthreads T3.17-004 submit
 * 	Version bump for zincos-876-miken merge
 * 	[2000/03/09  21:43:29  Mike_Neverisky]
 * 
 * Revision 1.1.19.13  2000/03/07  19:00:00  Peter_Portante
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree devbld_zko:thdv50a
 *     User Revision:  Peter_Portante_bl16_br:1.1.41.1 Local Ancestor:1.1.19.12
 *    Merge Revision:  zincos_bl4:1.1.27.4
 *   Common Ancestor:  1.1.27.2
 * 	[2000/03/07  04:26:32  Peter_Portante]
 * 	New QAR fix, new version.
 * 	[2000/03/07  04:21:34  Peter_Portante]
 * 
 * Revision 1.1.19.12  2000/03/03  18:03:05  Dave_Butenhof
 * 	New QAR fix, new version.
 * 
 * Revision 1.1.33.2  2000/03/03  16:36:16  Mike_Neverisky
 * 	DECthreads V3.17-003 submit"	Update version number for QAR fix
 * 
 * Revision 1.1.29.7  2000/03/02  22:52:49  Mary_Sullivan
 * 	Update version to 3.17-008.
 * 
 * Revision 1.1.35.2  2000/03/02  17:51:19  Dave_Butenhof
 * 	Bump version
 * 	[1999/11/10  15:25:48  Dave_Butenhof]
 * 	Remove unnecessary definitions. Improve some comments.
 * 	[1999/12/20  20:28:34  Dave_Butenhof]
 * 	[2000/01/20  18:12:34  Dave_Butenhof]
 * 
 * Revision 1.1.29.6  2000/02/29  20:20:07  Mary_Sullivan
 * 	Update rev for Initial Kestrel Submit.
 * 
 * Revision 1.1.19.11  2000/02/25  20:23:54  Mike_Neverisky
 * 	Increment version for QAR fix
 * 
 * Revision 1.1.27.4  2000/02/23  19:21:16  Mike_Neverisky
 * 	DECthreads V3.16-019 submit to Zinc
 * 
 * Revision 1.1.29.5  2000/02/21  20:20:36  Dave_Butenhof
 * 	Update version to 3.17.
 * 	[2000/02/21  19:20:56  Dave_Butenhof]
 * 	Update to 3.18.
 * 	[2000/02/18  15:51:21  Dave_Butenhof]
 * 	Add const long pointer typedefs.
 * 	[2000/02/16  16:36:46  Dave_Butenhof]
 * 	Ooops. Add the new const string types on non-EVMS path.
 * 	[2000/02/15  18:34:17  Dave_Butenhof]
 * 	Add "const" string (long and short) types.
 * 	[2000/02/15  18:26:11  Dave_Butenhof]
 * 
 * Revision 1.1.29.4  2000/02/08  13:32:33  Dave_Butenhof
 * 	Add the symbolic constants for priority mutexes. (Otherwise
 * 	code can't compile to reach the ENOSYS stubs.) Clean up some
 * 	comments.
 * 
 * Revision 1.1.29.3  2000/02/03  13:59:38  devbld_zko
 * Merge Information
 *     Merge Revision:  thdbl16_br:1.1.19.8
 *     User  Revision:  thdbl17_br:1.1.29.2
 *    Common Ancestor:  1.1.19.5
 *     Merge Revision History Comments from Rev : 1.1.19.8
 *     	Increment version number
 *     -------------------------------------------------
 * 	Formally merge against BL16 and bump version number.
 * 
 * Revision 1.1.29.2  2000/02/02  16:17:50  Peter_Portante
 * 	Make sure Unix98 interface names fit within 31 characters under
 * 	OpenVMS.
 * 	[2000/01/26  21:40:38  Peter_Portante]
 * 	Increment version number. Add Unix98 required interfaces.
 * 	[2000/01/21  01:21:11  Peter_Portante]
 * 
 * Revision 1.1.19.8  2000/02/01  20:04:31  Mike_Neverisky
 * 	Increment version number
 * 
 * Revision 1.1.33.1  2000/01/31  22:32:42  Peter_Portante
 * 	Move to new sandbox for a direct submit
 * 
 * Revision 1.1.30.3  2000/01/26  21:40:38  Peter_Portante
 * 	Make sure Unix98 interface names fit within 31 characters under
 * 	OpenVMS.
 * 
 * Revision 1.1.19.7  2000/01/22  16:51:43  Webb_Scales
 * 	Bump the version number.
 * 
 * Revision 1.1.30.2  2000/01/21  01:21:11  Peter_Portante
 * 	Increment version number. Add Unix98 required interfaces.
 * 
 * Revision 1.1.19.6  2000/01/17  17:43:37  Mike_Neverisky
 * 	re-synch with pthread_version.h
 * 
 * Revision 1.1.29.1  2000/01/10  14:15:59  Mike_Neverisky
 * 	Increment version number
 * 
 * Revision 1.1.19.5  2000/01/07  13:23:40  Peter_Portante
 * 	Bump the build version number.
 * 
 * Revision 1.1.19.4  1999/12/03  17:46:22  Ravi_Chamarti
 * 	Insert a space in a bad comment line
 * 	[1999/12/03  17:46:14  Ravi_Chamarti]
 * 	Fix a comment line
 * 	[1999/12/03  17:42:30  Ravi_Chamarti]
 * Merge Information
 *     Merge Revision:  thdbl16_br:1.1.19.3
 *     User  Revision:  Ravi_Chamarti_thdbl16_br:1.1.27.2
 *    Common Ancestor:  1.1.19.2
 *     Merge Revision History Comments from Rev : 1.1.19.3
 *     	Bump build number
 *     -------------------------------------------------
 * 	[1999/12/03  17:38:47  Ravi_Chamarti]
 * 	Remove extra blank lines
 * 	[1999/12/02  15:28:26  Ravi_Chamarti]
 *  	Move mutex and condition variables internal flags
 * 	[1999/12/01  18:28:24  Ravi_Chamarti]
 * 
 * Revision 1.1.19.2  1999/11/17  17:49:05  Peter_Portante
 * 	Bump the build number
 * 	[1999/11/17  15:59:21  Peter_Portante]
 * 	Remove useless intermediate merge comments.
 * 	[1999/11/15  17:47:30  Peter_Portante]
 * Merge Information
 *     Merge Revision:  thdbl16_br:1.1.19.1
 *     User  Revision:  Peter_Portante_mg_br:1.1.22.4
 *    Common Ancestor:  1.1
 * 	[1999/11/15  17:45:01  Peter_Portante]
 * 	Eliminate refcnt/ovfcnt fields, which are no longer used.
 * 	[1999/11/05  18:20:19  Dave_Butenhof]
 * 
 * Revision 1.1.21.2  1999/11/05  18:20:19  Dave_Butenhof
 * 	Eliminate refcnt/ovfcnt fields, which are no longer used.
 * 	Fix a comment line
 * 	[1999/12/03  17:42:30  Ravi_Chamarti]
 * Merge Information
 *     Merge Revision:  thdbl16_br:1.1.19.3
 *     User  Revision:  Ravi_Chamarti_thdbl16_br:1.1.27.2
 *    Common Ancestor:  1.1.19.2
 *     Merge Revision History Comments from Rev : 1.1.19.3
 *     	Bump build number
 *     -------------------------------------------------
 * 	[1999/12/03  17:38:47  Ravi_Chamarti]
 * 	Remove extra blank lines
 * 	[1999/12/02  15:28:26  Ravi_Chamarti]
 *  	Move mutex and condition variables internal flags
 * 	[1999/12/01  18:28:24  Ravi_Chamarti]
 * 
 * Revision 1.1.21.1  1999/11/03  13:09:31  Peter_Portante
 * 	Move to thdadvdev
 * 
 * Revision 1.1.14.3  1999/11/01  15:38:09  Peter_Portante
 * 	Update the version number.
 * 
 * Revision 1.1.14.2  1999/10/26  16:47:03  Peter_Portante
 * 	Fix up a history comment.
 * 
 * Revision 1.1.5.5  1999/10/21  21:04:18  Richard_Love
 * 	Removed support for Win32 platforms.
 * 	Win32 is no longer supported by us.  This also
 * 	eliminates interaction problems with DCOM compilations.
 * 	Add back in the "LAST MODIFICATION DATE:", it had been removed.
 * 
 * Revision 1.1.5.4  1999/10/04  17:20:36  Tom_Dahl
 * 	Add the CMS history.
 * 	[1999/09/27  13:26:59  Tom_Dahl]
 * 	Merge Dave's IA64 changes into the zulu pool.
 * 	[1999/08/20  22:42:29  Tom_Dahl]
 * 
 * Revision 1.1.14.1  1999/09/20  13:14:46  Peter_Portante
 * Merge Information
 *     Merge Revision:  DECTHREADS_SHARED_THDZULUOS:1.1.5.3
 *     User  Revision:  Peter_Portante_thdzu:1.1.10.7
 *    Common Ancestor:  1.1
 * 	[1999/09/16  14:29:25  Peter_Portante]
 * 	Allow C++ to use asm() and inline routines.
 * 	[1999/08/25  15:28:20  Peter_Portante]
 * 	Bump the build number.
 * 	[1999/08/20  18:56:25  Peter_Portante]
 * 	Rename slow bit to config bit. Add trace and meter bits. Move
 * 	top bits around a little so that the meter bit is next to the
 * 	type bits. Bump the build number.
 * 	[1999/08/20  18:25:41  Peter_Portante]
 * 	Add a spinner and nowaiter bit for mutexes. I bumped the base level
 * 	and reset the build number.
 * 	[1999/07/27  17:01:30  Peter_Portante]
 * 	Remove inline mutex operations.
 * 	[1999/07/02  19:51:10  Peter_Portante]
 * 
 * Revision 1.1.5.3  1999/05/28  13:44:29  Terry_Cassidy
 * 	Initial CMS version
 * 	New-style copyright removed
 * 	Old-style copyright removed
 * 	Daughter history merged
 * 	History inverted
 * 	File modification date section deleted
 * 	[1999/05/28  13:39:04  Terry_Cassidy]
 * 
 * Revision 1.1.8.3  1999/05/07  17:30:03  Dave_Butenhof
 * 	A step further towards IA64 parity.
 * 
 * Revision 1.1.8.2  1999/04/28  15:54:55  Dave_Butenhof
 * 	Begin the journey to IA64. Also, move the old _np stuff to the end,
 * 	and remove redundant extern_model save/change/restore (it's not
 * 	needed here). Change "Digital UNIX" to "Tru64 UNIX". Clean up some
 * 	old comments (including recommending tis_allocator_mutex_init over
 * 	the cumbersome & unreliable PTHREAD_MUTEX_INITPRE & friends).
 * 
 * Revision 1.1.7.2  1999/04/16  20:41:36  Mike_Neverisky
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rDECTHREADS_SHARED_THDZULUOS **
 * 		** Ancestor revision:	1.1 **
 * 		** Merge revision:	1.1.5.2 **
 * 	 	** End **
 * 	propagating thdzuluos
 * 	[1999/04/16  19:53:53  Mike_Neverisky]
 * 
 * Revision 1.1.5.2  1999/04/07  15:23:05  Peter_Portante
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.2.4 **
 * 		** Merge revision:	1.1.5.1 **
 * 	 	** End **
 * 	Use new directory hierarchy for DECthreads code
 * 	[1999/04/06  20:19:27  Peter_Portante]
 * 
 * Revision 1.1.2.4  1999/03/29  18:29:17  Peter_Portante
 * 	Final CMS update
 * 	[1999/03/25  03:16:23  Peter_Portante]
 * 
 * Revision 1.1.2.3  1999/03/16  14:34:12  Peter_Portante
 * 	Update from CMS
 * 	[1999/03/15  20:53:34  Peter_Portante]
 * 
 * Revision 1.1.2.2  1999/03/09  22:19:14  Peter_Portante
 * 	Move from COMMON subdirectory
 * 	[1999/03/09  20:10:16  Peter_Portante]
 * 
 * Revision 1.1.19.1  [1999/11/03  04:58:06  Peter_Portante]
 * 	Move to thdbl16
 * 	[1999/11/03  04:58:06  Peter_Portante]
 * 	Update the version number.
 * 	[1999/11/01  15:38:09  Peter_Portante]
 * 	Fix up a history comment.
 * 	[1999/10/26  16:47:03  Peter_Portante]
 * 	Removed support for Win32 platforms.
 * 	Win32 is no longer supported by us.  This also
 * 	eliminates interaction problems with DCOM compilations.
 * 	Add back in the "LAST MODIFICATION DATE:", it had been removed.
 * 	[1999/10/21  21:04:18  Richard_Love]
 * 	Add the CMS history.
 * 	[1999/09/27  13:26:59  Tom_Dahl]
 * 	Merge Dave's IA64 changes into the zulu pool.
 * 	[1999/08/20  22:42:29  Tom_Dahl]
 * Merge Information
 *     Merge Revision:  DECTHREADS_SHARED_THDZULUOS:1.1.5.3
 *     User  Revision:  Peter_Portante_thdzu:1.1.10.7
 *    Common Ancestor:  1.1
 * 	[1999/09/16  14:29:25  Peter_Portante]
 * 	Allow C++ to use asm() and inline routines.
 * 	[1999/08/25  15:28:20  Peter_Portante]
 * 	Bump the build number.
 * 	[1999/08/20  18:56:25  Peter_Portante]
 * 	Rename slow bit to config bit. Add trace and meter bits. Move
 * 	top bits around a little so that the meter bit is next to the
 * 	type bits. Bump the build number.
 * 	[1999/08/20  18:25:41  Peter_Portante]
 * 	Add a spinner and nowaiter bit for mutexes. I bumped the base level
 * 	and reset the build number.
 * 	[1999/07/27  17:01:30  Peter_Portante]
 * 	Remove inline mutex operations.
 * 	[1999/07/02  19:51:10  Peter_Portante]
 * 	Initial CMS version
 * 	New-style copyright removed
 * 	Old-style copyright removed
 * 	Daughter history merged
 * 	History inverted
 * 	File modification date section deleted
 * 	[1999/05/28  13:39:04  Terry_Cassidy]
 * 	A step further towards IA64 parity.
 * 	[1999/05/07  17:30:03  Dave_Butenhof]
 * 	Begin the journey to IA64. Also, move the old _np stuff to the end,
 * 	and remove redundant extern_model save/change/restore (it's not
 * 	needed here). Change "Digital UNIX" to "Tru64 UNIX". Clean up some
 * 	old comments (including recommending tis_allocator_mutex_init over
 * 	the cumbersome & unreliable PTHREAD_MUTEX_INITPRE & friends).
 * 	[1999/04/28  15:54:55  Dave_Butenhof]
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rDECTHREADS_SHARED_THDZULUOS **
 * 		** Ancestor revision:	1.1 **
 * 		** Merge revision:	1.1.5.2 **
 * 	 	** End **
 * 	propagating thdzuluos
 * 	[1999/04/16  19:53:53  Mike_Neverisky]
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.2.4 **
 * 		** Merge revision:	1.1.5.1 **
 * 	 	** End **
 * 	Use new directory hierarchy for DECthreads code
 * 	[1999/04/06  20:19:27  Peter_Portante]
 * 	Final CMS update
 * 	[1999/03/25  03:16:23  Peter_Portante]
 * 	Update from CMS
 * 	[1999/03/15  20:53:34  Peter_Portante]
 * 	Move from COMMON subdirectory
 * 	[1999/03/09  20:10:16  Peter_Portante]
 * 
 * $EndLog$
 */
/*
 * $OldLog: pthread.template.h,v $ 
 * 	117	Richard Love	 4 February 1999
 * 		Remove paddock entry points.
 * 	116	Peter Portante	 8 January 1999
 * 		We need to define pthread_kill() and pthread_sigmask()
 * 		if we are not in a UNIX98 environment.  We simply define
 * 		them in both signal.h and pthread.h so that pre UNIX98
 * 		environments have them defined through pthread.h.  The
 * 		redefinitions should not conflict.
 * 	115	Peter Portante	 7 January 1999
 * 		Check to see if tis.h is including pthread.h and do
 * 		not define the inline routines.
 * 	114	Dave Butenhof	20 November 1998
 * 		Fix conditionals for use of the DEC C __builtin_try extensions
 * 		on UNIX. Do it only for DEC C, not for any non-C++
 * 		compiler.
 * 	113	Peter Portante	21 October 1998
 * 		Rework the definitions of the inline mutex operations.
 * 		We now use __inline routines for the operations
 * 		instead of macros so that the code is easier to read.
 * 		These inline routines are then just used by the actual
 * 		routines in thd_mutex.c.  Restore definition of _REENTRANT
 * 		for now since we cannot fix all the broken code in the
 * 		operating system.
 * 	112	Peter Portante	17 August 1998
 * 		Remove definition of _REENTRANT and replace with a
 * 		"#error" telling the user to compile with -pthread for 
 * 		Digital UNIX.  For Windows NT, do the same for _MT and 
 * 		tell them to compile with /MT.
 * 	111	Peter Portante	14 August 1998
 * 		Make sure inline routine parameters and local
 * 		variables are namespace safe.
 * 	110	Richard Love	14 August 1998
 * 		Add parameter identifier for pthread_getspecific(),
 * 		"__key".
 * 	109	Richard Love	13 August 1998
 * 		Name space clean up.  Removed identifiers in formal 
 * 		parameter list of function prototypes.  Work done by
 * 		Peter Portante.  I just checked it in.
 * 	108	Webb Scales	 9 July 1998
 * 		Increased the PTHREAD_STACK_MIN value to 6656 for VAX platforms.
 * 		It would seem that in-lining (or some similar "optimization")
 * 		causes production builds to use much more stack space than
 * 		debug builds (particularly dspDispatch() and thdBase(), I think)
 * 		and so an "End of Quantum" event will overflow a stack with
 * 		less than about 6400 bytes.
 * 	107	Richard Love	25 June 1998
 * 		Increased the PTHREAD_STACK_MIN value to 4608 (an increase
 * 		of 512) for VAX platforms so that servicing of an 
 * 		"End of Quantum" AST will work in a minimum stack thread.
 * 	106	Mark Simons	 5 June 1998
 * 		Include <c_asm.h> on UNIX for DECC only.
 * 	105	Mark Simons	 3 June 1998
 * 		Use __int64 on EVMS instead of int64.
 * 		Remove #include for <ints.h>.
 * 	104	Peter Portante	 7 May 1998
 * 		__pthreadStart_t, __pthreadOnce_t, __pthreadConstructor_t,
 * 		__pthreadDestructor_t, and __pthreadExtDestructor_t are once
 * 		again pointers to a function.
 * 	103	Webb Scales	30 April 1998
 * 		The top five (instead of four) bits in the synch object valid
 * 		field are now flags -- the new flag indicates whether the
 * 		object was statically initialized.  Added mask constants for
 * 		mutexes, CVs, and RW locks for the new flags.
 * 	102	Dave Butenhof	13 April 1998
 * 		Add pthread_attr_[g|s]etstackaddr_np.
 * 	101	Ravi Chamarti   19 March 1998
 * 		Namespace symbols cleanup (migrating to thd_pollution.h)
 * 	100	Peter Portante	16 March 1998
 * 		Reverse the sense of the pending wakeup bit.
 * 	099	Peter Portante	13 March 1998
 * 		Move PSHARED bit next to slow bit in the mutex lock field.
 * 		Move the nopend bit from condition variable blocking structures
 * 		to condition variables themselves.
 * 	098	Mark Simons	12 March 1998
 * 		Add a typedef for a new constructor routine, modify all
 * 		typedefs for constructor/destructor routines to use
 * 		the _PTHREAD_CALL_ keyword to ensure that the calling
 * 		standard of the prototypes is explicitly specified,
 * 		and use these defined function types in the prototypes
 * 		for pthread_key_create(_new_np).  The calling standard
 * 		of the prototypes must be explicitly specified, or else
 * 		we get inconsistencies between the standard used by the
 * 		application (i.e. the caller) and that used when
 * 		the routine is built by our library (i.e. the callee).
 * 		Which all leads to a nifty little stack corruption.
 * 	097	Dave Butenhof	27 February 1998
 * 		Change type of rwlock's wrid field (it's now a sequence number
 * 		rather than a TCB pointer).
 * 	096	Ravi Chamarti	13 February 1998
 * 		Three UNIX98 changes:
 * 		1) pthread.h nows includes <time.h> instead of <sys/time.h>
 * 		   Unix98 requires that pthread.h inclusion should make
 * 		   <time.h> routines visible
 * 		2) priority and scheduling macros for _PTHREAD_ENV_VMS 
 * 		   is made visible only when _PTHREAD_ENV_VMS is defined,
 * 		   but not when PTHREAD_ENV_UNIX is defined and 
 * 		   OSF_SOURCE is not defined.  
 * 		3) PTHREAD_DESTRUCTOR_ITERATIONS macro is defined in
 * 		   pthread.h only for non-Unix environment.
 * 	095	Steve Johnson	 5 February 1998
 * 		Fix use of _PTHREAD_CALL_ in 6 places
 * 	094	Peter Portante	23 January 1998
 * 		Move definitions of pthread_sigmask and pthread_kill to signal.h
 * 	093	Webb Scales & Peter Portante	14 January 1998
 * 		Make sure store conditional branch tests are correctly coded.
 * 	092	Mary Sullivan	 9 January 1997
 * 		On the recommendation of Bill Noyce, remove the forward-branch
 * 		to backward-branch in looping asm code. It was supposed to model
 * 		the correct EV4 branch prediction logic, but really didn't and
 * 		will actually hurt on EV45 and EV5.
 * 	091	Peter Portante	23 December 1997
 * 		Remove declaration of pthread_trace_write_np so that we have
 * 		only one and it is in pthread_trace.h.
 * 	090	Peter Portante	22 December 1997
 * 		For Digital UNIX, pthread_atfork() needs to reside in unistd.h.
 * 		Add new paddock attribute block and use it instead of the
 * 		thread attribute block.
 * 	089	Steve Johnson	 9 December 1997
 * 		Make paddock routine prototypes for all platforms
 * 	088	Peter Portante	26 November 1997
 * 		For Win32 we do not need to use the "__" for our interface
 * 		names.
 * 	087	Peter Portante	17 November 1997
 * 		Fix use of tabs.  Add pshared state flags for mutexes and
 * 		condition variables.  Provide prototypes for pre and post
 * 		UNIX98 interface names.
 * 	086	Dave Butenhof	29 October 1997
 * 		Add pthread_trace_write_np function.
 * 	085	Dave Butenhof	18 July 1997
 * 		Increase PTHREAD_STACK_MIN for OpenVMS VAX, since the
 * 		current 1024 seems inadequate for even an empty thread
 * 		routine.
 * 	084	Peter Portante	21 May 1997
 * 		Add pshared and sigmask attribute routines for Digital UNIX.
 * 		Rearrange the readers/writer locks definitions so that they
 * 		fit where the other objects are defined.  Also, for Digital
 * 		UNIX, those types are defined in types.h.
 * 	083	Brian Silver	21 May 1997
 * 		Add paddock support
 * 	082	Webb Scales	13 May 1997
 * 		Provide a definition for pthread_mutex_unlock_prim() even
 * 		when we are not using inline/asm mechanisms (i.e., on VAX)
 * 		so that code in thd_cond will be happy there.  The new
 * 		definition forces execution down the slow path in all cases
 * 		which is what normally happens on VAX anyway.
 * 	081	Mark Simons	30 April 1997
 * 		INTEL inline assembler for pthread_mutex_lock/unlock_prim.
 * 		Values for PRI_RR/FIFO/BG etc. changed for Windows.
 * 		Define _PTHREAD_CDECL_CALL_.
 * 	080	Brian Silver	25 April 1997
 * 		Add rwlock support
 * 	079	Peter Portante	25 March 1997
 * 		Perform a little formatting cleanup.
 * 	078	Dave Butenhof	13 March 1997
 * 		Move <standards.h> and <unistd.h> before <pthread_exception.h>
 * 		to allow cleaning namespace in latter.
 * 	077	Brian Silver	28 February 1997
 * 		Add protos for gettype/settype
 * 	076	Peter Portante	21 February 1997
 * 		Clean up C++ conditional changes a little.
 * 	075	Dave Butenhof	20 February 1997
 * 		Add stack_hiwater field to TEB, before it's too late
 * 		for TEB v1. This may be used by compiler, and I'll
 * 		probably use it for stack metering.
 * 	074	Dave Butenhof	14 February 1997
 * 		Clean up C++ conditionals.
 * 	042	Brian Silver	10 January 1996
 * 		Changed name mangle macros from pthread_name(_x) to pthread_name
 * 		header files. No pthread_self macro on Windows; we must
 * 		call the internal function.
 * 	041	Dave Butenhof	15 December 1995
 * 		Add _PTHREAD_MVF_INL flag for "inline" mutexes (muMute_t)
 * 	040	Peter Portante & Dave Butenhof	30 November 1995
 * 		Condition definition of some typedefs for Digital UNIX since
 * 		they are required to reside in types.h.  Add name mangling
 * 		support.  The "#pragma extern_prefix" is used to add a prefix
 * 		to external names so new interfaces which have the same name as
 * 		old ones will not conflict.  It's much cleaner and more
 * 		conformant than #define (you can #undef, take the address,
 * 		etc.).  For cc -oldc compilation, alternately use parameterized
 * 		macros (which don't allow taking addresses, but also don't
 * 		conflict with field names, etc.) This is how libc is doing
 * 		_XOPEN_SOURCE_EXTENDED support.
 * 	039	Peter Portante	15 November 1995
 * 		Make cleanup push/pop handlers use a native try finally block
 * 		on platforms which support it.
 * 	038	Dave Butenhof	13 November 1995
 * 		DEC C++ doesn't like 037 -- apparently it won't allow
 * 		"redeclaring" a class (struct) name using a typedef, if the
 * 		class is volatile. (I suspect this is a DEC C++ bug, but at
 * 		this point it's easier to change our struct tags to avoid
 * 		any conflict.)
 * 	037	Dave Butenhof	 1 November 1995
 * 		Modify the pthread_mutex_t and pthread_cond_t structures to
 * 		be volatile! This ensures that the compiler can't perform any
 * 		possibly disastrous optimizations upon them.
 * 	036	Dave Butenhof	 1 November 1995
 * 		Modify pthread_mutex_unlock asm() logic to decrement the
 * 		refcnt only if it didn't call unblock. This allows unblock
 * 		to release the reference before waking a blocked waiter, and
 * 		fix a race where that waiter could run and (reasonably) try
 * 		(but undesirably fail) to delete the mutex after unlocking it,
 * 		before the waker was able to release its reference.
 * 	035	Dave Butenhof & Webb Scales	27 October 1995
 * 		Add thread_flags to TEB, to match all the other places where
 * 		the TEB is defined...
 * 	034	Dave Butenhof	 1 September 1995
 * 		Fix register naming in unlock_prim (%r0 and %v0 used together).
 * 	033	Dave Butenhof	 2 August 1995
 * 		Move cancel definitions into pthread_defs.h so we don't
 * 		advertise dangerous information. Also obscure the
 * 		"cancel_flags" TEB field -- which will be just a place to
 * 		save the "live" flags when the thread's not running, on
 * 		Digital UNIX (the real flags are in the per_kt_area "kernel
 * 		inline" data area).
 * 	032	Dave Butenhof	 1 August 1995
 * 		C++ doesn't support asm(), and c_asm.h has a #error for C++,
 * 		so it can't even be included. Adjust pthread.h.
 * 	031	Dave Butenhof	31 July 1995
 * 		After a talk with Ken Cowan of DECC, I decided to follow their
 * 		philosophy on header files -- there's no need to disable the
 * 		features of a header file (pthread.h) just because
 * 		_POSIX_C_SOURCE is defined to a lower value if the header file
 * 		was never defined by earlier standards. E.g., an application
 * 		that strictly conforms to 1003.1-1990 has no business ever
 * 		including <pthread.h> -- and if it does, it can't expect us to
 * 		work around its own error. (Or to put it another way, POSIX
 * 		1003.1-1990 doesn't say anywhere that including pthread.h will
 * 		do nothing.) I've also removed our unistd.h feature test
 * 		macros, because they're going to put them into the real DECC
 * 		unistd.h!
 * 	030	Dave Butenhof	28 July 1995
 * 		Clean up _POSIX_C_SOURCE one final time -- instead of defining
 * 		it if not already defined, just react to absence by assuming
 * 		everything's allowed. This is a cleaner workaround for
 * 		Platinum and also avoids breaking the Theta DEC C code, which
 * 		lacks an equivalent to standards.h (so far).
 * 	029	Dave Butenhof	13 July 1995
 * 		I'm still nervous about definition dependencies and the
 * 		implicit documentation issues of having the actual types in
 * 		attributes object structures. Just to be safe, I'm going to
 * 		reduce them to anonymous arrays of longs. I've added
 * 		assertions to the respective module init code to report if
 * 		we ever exceed the reserved size.
 * 	028	Dave Butenhof	 7 July 1995
 * 		Add in _POSIX_SOURCE & _POSIX_4SOURCE definitions temporarily
 * 		until Blue's _POSIX_C_SOURCE support shows up in ptos.nightly;
 * 		libc sometimes uses _XOPEN_SOURCE_EXTENDED, which defines
 * 		_POSIX_SOURCE but not _POSIX_4SOURCE. I'm not really sure how
 * 		all this needs to interact, but it could be messy to solve for
 * 		real.
 * 	027	Dave Butenhof	 6 July 1995
 * 		A little more 1003.1c-1995 cleanup. A few comments, and I
 * 		added the config symbols. (These also need to go into unistd.h
 * 		for Digital UNIX.)
 * 	026	Dave Butenhof	 5 July 1995
 * 		Add reserved mutex valid fields for internal & "malloc".
 * 		Also some 1003.1c-1995 comment & setup cleanups. Among other
 * 		things, there was an old hack that defined _POSIX_4SOURCE and
 * 		_OSF_SOURCE as well as an RT_SCHED symbol to coerce sched.h
 * 		to make needed symbols visible -- a recent review of
 * 		standards.h and sched.h assures me these aren't necessary (and
 * 		likely haven't been for several releases). So remove them.
 * 	025	Peter Portante	29 June 1995
 * 		LOOPY ASMs do not work on DEC C V5.2 yet...
 * 	024	Dave Butenhof	29 June 1995
 * 		Resolve some conflicts with DEC C V5.2 on Theta (which adds
 * 		struct timespec), and make some other cleanups suggested by
 * 		DEC C folks (like basing asm use on the version of DEC C).
 * 	023	Dave Butenhof	27 June 1995
 * 		Remove the "$" in the OpenVMS external names, per advice of
 * 		OpenVMS "name police" (who said they agreed in principle and
 * 		we should do it unless we heard otherwise -- and we haven't,
 * 		and now is the time).
 * 	022	Dave Butenhof	23 June 1995
 * 		Compiling with _PTHREAD_USE_INLINE on OpenVMS Alpha resulted
 * 		"data loss" warnings in the inlined pthread_getspecific. Add
 * 		an explicit cast to (void *) to avoid warning.
 * 	021	Dave Butenhof	21 June 1995
 * 		Add ENOTSUP definition for VAXC. We don't currently use it,
 * 		but we should have it available.
 * 	020	Dave Butenhof	 6 June 1995
 * 		Fix conditionals on pthread_t size.
 * 	019	Dave Butenhof	 5 June 1995
 * 		Fix some more fallout from 018, since some things that should
 * 		have been using pthreadTeb_p (always a pointer) are using
 * 		pthread_t -- which may be a "uint64" on OpenVMS Alpha.
 * 	018	Dave Butenhof	 2 June 1995
 * 		Move pthread_t back into required pointer size (virtually);
 * 		using __uint64 ifndef __INITIAL_POINTER_SIZE. This resolves
 * 		the ambiguity of pthread_create without adding interfaces
 * 		(so why didn't I notice that before?)
 * 	017	Dave Butenhof	 1 June 1995
 * 		The only remaining _PTHREAD_NOWRAPPERS_ is in the #pragma
 * 		inline pthread_getspecific(), and it's not necessary. So
 * 		nuke it.
 * 	016	Dave Butenhof	 1 June 1995
 * 		Somehow the various thread attributes definitions have gotten
 * 		skewed. Aren't tests nice to have around?
 * 	015	Peter Portante	31 May 1995
 * 		Include pthread_d4.h from the dce directory on Digital UNIX.
 * 	014	Dave Butenhof	30 May 1995
 * 		Change name of _PTHREAD_FAST, remove setname/getname protos,
 * 		and add leading "reserved" fields to attributes for name &
 * 		arg.
 * 	013	Peter Portante	25 May 1995
 * 		Remove definition of sigwait().  signal.h now defines it.  Make
 * 		unblock prims for the inline mutex macros so that TIS.H can
 * 		use them directly.
 * 	012	Dave Butenhof	24 May 1995
 * 		Remove 'scope' field from pthread_attr_t... it should really
 * 		be a flag.
 * 	011	Dave Butenhof	24 May 1995
 * 		Finish changing exc_e_SIGIOT to pthread_exc_SIGABRT_e.
 * 	010	Dave Butenhof	24 May 1995
 * 		Move pthread_t type out of the required_pointer_size block
 * 		so that it works right in a 32-bit compilation. This is a
 * 		permanent commitment not to put TEBs into high memory... but
 * 		I think that's reasonable. (And we can always create a new
 * 		"pthread64_t" or something later, if needed.)
 * 	009	Dave Butenhof	23 May 1995
 * 		Remove the "mixed protos" disablement of the special long
 * 		pointer sizes -- those are for things that MUST be long,
 * 		regardless of the user's /pointer_size selection; otherwise
 * 		structures won't align right!
 * 	008	Dave Butenhof	20 May 1995
 * 		Change types of state/lock and valid fields in the mutex
 * 		and condition variable from "long" to "int" -- I only use
 * 		32 bits anyway, and it satisfies DECC type checking. It'll
 * 		even make them smaller on Digital UNIX.
 * 	007	Peter Portante	20 May 1995
 * 		Change cancel flags to be an unsigned int.
 * 	011	Dave Butenhof	18 May 1995
 * 		Remove pthreadDateTime_t.
 * 	010	Paul Clark	17 May 1995
 * 		Define sched_yield for VMS platforms.  Define pthread_
 * 		setcanceltype.
 * 	009	Paul Clark	16 May 1995
 * 		To accommodate source modules that happen to include both
 * 		CMA.H [as exported by LEGACY] and PTHREAD.H, conditionally
 * 		undefine _DECTHREADS_ before defining it.
 * 	008	Dave Butenhof	12 May 1995
 * 		More fixes to pthread_mutex_unlock asm(). Reverse cmovne to
 * 		cmove.
 * 	007	Dave Butenhof	10 May 1995
 * 		Add name/arg fields to mutex and cond, and put recursion
 * 		depth and owner into mutex.
 * 	006	Dave Butenhof	 4 May 1995
 * 		Fix a typo in the description of _DECTHREADS_
 * 	005	Webb Scales	 3 May 1995
 * 		Provide a routine version of pthread_getselfseq_np for ladebug.
 * 	004	Dave Butenhof	 2 May 1995
 * 		Fix zapnot in mutex_unlock_inline -- should be "0x7", not
 * 		"0x11". Ooops. Also convert hardcoded long literal in the
 * 		lock_prim macro into a ldah.
 * 	003	Webb Scales	28 April 1995
 * 		Touch up the VMS name mangling for the symbols that are
 * 		conditionally defined.
 * 	002	Webb Scales	28 April 1995
 * 		Get rid of undefined "pthread_voidstar_np_t".
 * 		Change the type of PTHREAD_{M|C}VALID to unsigned long.
 * 		Add name mangling for the VMS platforms
 * 	001	Dave Butenhof	21 April 1995
 * 		All new and improved, the 1003.1c DECthreads interface.
 * $EndLog$
 */
/*
 * @(#)$RCSfile: pthread.template.h,v $ $Revision: 1.1.39.3 $ (DEC) $Date: 2004/11/01 17:49:42 $
 */
/*
 *  FACILITY:
 *
 *	DECthreads POSIX 1003.1c
 *
 *  ABSTRACT:
 *
 *	External definitions for POSIX 1003.1c interfaces
 *
 *	General notice: some of the types defined and used in this header are
 *	not standard POSIX 1003.1c types. The DECthreads specific types are
 *	generally used instead of "void *" and "long" where pointer size
 *	#pragma declarations are necessary to support the OpenVMS Alpha 64-bit
 *	programming environment. (And in a few other cases where it's
 *	convenient.) These types should not present any obstacle to programs
 *	coded using the standard types. The "addon" types are distinguished by
 *	naming convention -- they begin with "__pthread" and the remainder
 *	appears in mixed-case without punctuation. For example,
 *	"__pthreadLongAddr_t" for "void *" and "__pthreadLongUint_t" for
 *	"unsigned long".
 *
 *	This header file contains extensive comments regarding the structures
 *	and options. Please read them carefully before relying upon any
 *	undocumented features -- they're undocumented for a reason! We want
 *	you to be able to take advantage of them where appropriate, but you
 *	must also understand the restrictions and risks.
 *
 *  AUTHORS:
 *
 *	Dave Butenhof
 *
 *  CREATION DATE:
 *
 *	January 1995
 *
 *  MODIFIED BY:
 *
 *	Dave Butenhof
 *	Paul Clark
 *	Steve Johnson
 *	Richard Love
 *	Peter Portante
 *	Webb Scales
 *	Brian Silver
 *	Mark Simons
 *	Tom Dahl
 *	Greg Jordan
 *
 */

#ifndef _PTHREAD_HEADER
# define _PTHREAD_HEADER

/******************************************************************************
 *
 * NOTICE: Temporary support for POSIX 1003.4a/D4 migration
 * --------------------------------------------------------
 *
 * Support 1003.4a/D4 ("DCE threads") source migration mode by allowing
 * programmer to cause #include <pthread.h> to define the old interfaces (with
 * modified names) if the _PTHREAD_USE_D4 macro is defined. This is equivalent
 * to #include <pthread_d4.h> -- the remainder of this header file is not
 * processed.
 *
 * In practice, the easiest way to do this is to continue to build threaded
 * code using the "-threads" switch, which will define _PTHREAD_USE_D4:
 *
 *	cc -threads foo.c
 *
 * Or, you can invoke the source migration mode by the following sequence
 * within your .c or .h files:
 *
 *	#define _PTHREAD_USE_D4
 *	#include <pthread.h>
 *
 * Or, finally, by modifying your Makefile (or manual build sequence) to use
 * the -D compiler option. (Note: you must ALWAYS define _REENTRANT when
 * compiling threaded or thread-safe code on Tru64 UNIX. Using "cc -threads"
 * or "cc -pthread" does this automatically.)
 *
 *	cc -D_PTHREAD_USE_D4 -D_REENTRANT foo.c
 *
 * On OpenVMS, use the #define solution, or the following DECC command (it is
 * not necessary to define _REENTRANT on OpenVMS):
 *
 *	cc /define=_PTHREAD_USE_D4 foo.c
 *
 * The POSIX 1003.4a/D4 migration support may be retired (this clause will be
 * removed from pthread.h!) in the next major release of each operating system
 * (OpenVMS Alpha and Tru64 UNIX) that occurs at least one year after the
 * initial release of the POSIX 1003.1c interfaces in Tru64 UNIX 4.0 and
 * OpenVMS 7.0.
 *
 *****************************************************************************/

#if defined (_PTHREAD_USE_D4) || defined (PTHREAD_USE_D4)
# if defined (__unix__) || defined (__unix) || defined (unix)
#  include <dce/pthread_d4.h>
# else
#  include <pthread_d4.h>
# endif
#else

/*
 * Define a symbol which client code can test to determine whether the
 * underlying threads package is DECthreads or not. This is especially
 * important to clients of the POSIX 1003.1c interface who may want to use
 * DECthreads extensions, such as the TEB, global lock and non-real-time
 * scheduling policies while maintaining portability to a "vanilla"
 * 1003.1c-1995 implementation.
 *
 * The DECthreads version is encoded in this number. The version is normally
 * in the form "Vvv.bb-lll" where "vv" represents the major version, "bb"
 * represents the baselevel (which increases continuously regardless of
 * version), and "lll" is a build level that increases in each DECthreads
 * project build within a baselevel.
 *
 * Higher numeric values are always more recent versions. So to check for
 * support of a feature that appeared in DECthreads V3.13-100, you could check
 * whether the symbol is > 212100L.
 */

#ifdef _DECTHREADS_VERSION
# undef _DECTHREADS_VERSION
#endif

#define _DECTHREADS_VERSION 320071

#ifndef _DECTHREADS_
# define _DECTHREADS_ _DECTHREADS_VERSION
#endif

/******************************************************************************
 *
 * NOTICE: inline function performance vs. binary compatibility
 * ------------------------------------------------------------
 *
 * This version of pthread.h supports the capability of generating inlined
 * code on OpenVMS Alpha and Tru64 UNIX for improved performance on some
 * critical operations -- especially mutex synchronization and reading thread
 * specific data.
 *
 * There is a balance between performance and maintainability, however. Inline
 * code sequences cannot be transparently fixed by future versions of
 * DECthreads. Thus, if a bug is found in the inlined code and later fixed,
 * programs using the inlined sequences must be recompiled to acquire the fix.
 * Additionally changes may be made to inlined sequences to improve
 * reliability or performance in the future. Digital cannot guarantee that the
 * new sequences will be binary compatible with the old sequences, and
 * therefore any such changes may also require recompilation.
 *
 * By default, this version of pthread.h will generate calls to carefully
 * tuned assembly code functions within DECthreads that implement the same
 * algorithm as the inline asm() code sequences. This provides safety at the
 * expense of performance by adding the overhead of a call and some
 * unavoidable procedure prolog and epilog code. If you need the performance
 * advantage of avoiding those calls, AND ARE WILLING TO ACCEPT THE RISK THAT
 * YOU WILL NEED TO RECOMPILE LATER, define the preprocessor symbol
 * _PTHREAD_USE_INLINE before including this header file; either by compiling
 * with
 *
 *	cc -D_PTHREAD_USE_INLINE
 *
 * or by using "#define" before including this header file:
 *
 *	#define _PTHREAD_USE_INLINE
 *	#include <pthread.h>
 *
 * Although _PTHREAD_USE_INLINE is made available for experimentation and
 * where the need for performance is extreme, Digital STRONGLY RECOMMENDS that
 * use of this option be avoided.
 *
 *****************************************************************************/

/******************************************************************************
 *
 * NOTICE: DECthreads tracing and static mutex initialization
 * -------------------------------------------------------------------------
 *
 * When a mutex is statically initialized using PTHREAD_MUTEX_INITIALIZER that
 * mutex is normally set up so that the first attempt to lock the mutex can be
 * recorded for Visual Threads or another trace client.
 *
 * If the preprocessor symbol _PTHREAD_NOMETER_STATIC is defined when this
 * header file is included, statically initialized mutexes will be set up so
 * that this extra overhead will occur only if the calling thread needs to
 * wait for the mutex. That is, statically initialized mutex operations	 
 * will not be recorded for Visual Threads until a thread blocks on that
 * mutex.
 *
 * Normally the minor overhead of this single "extra" call on the first mutex
 * access is acceptable in exchange for tracing support. For rare cases where
 * that overhead is not acceptable, compile with -D_PTHREAD_NOMETER_STATIC.
 *
 *****************************************************************************/

/******************************************************************************
 *
 * NOTICE: POSIX 1003.1c support
 * -----------------------------
 *
 * The POSIX 1003.1c-1995 standard was formally approved at the June 1995
 * meeting of the IEEE Standards Board. The correct configuration test macro
 * for strictly conforming POSIX 1003.1c-1995 applications is
 *
 *	#define _POSIX_C_SOURCE 199506L
 *
 * The POSIX standard requires that, for portability, the application must
 * define _POSIX_C_SOURCE within each compilation unit, for example, by
 * compiling with -D_POSIX_C_SOURCE=199506L.
 *
 * As of Tru64 UNIX V5.1A, this header also supports full compatiblity with
 * The Single UNIX Specification, Version 2, also known as UNIX 98, as
 * specified by CAE Specification Version 5 (XSH5). Application conformance
 * with this specification is designated by defining the preprocessor symbol
 * _XOPEN_SOURCE to a value of 500, preferably via -D_XOPEN_SOURCE=500. In
 * this case, defining _POSIX_C_SOURCE to 199506L is optional.
 *
 * The Tru64 UNIX <standards.h> will default _POSIX_C_SOURCE to the latest
 * POSIX 1003.1 revision supported by the operating system (currently
 * 1003.1c-1995) if no other confining standard definitions are already
 * defined, and will allow all XSH5 extensions. Unless the programmer
 * specifies a specific restriction, the programmer will have access to all
 * standards that aren't inherently incompatible.
 *
 * Compiling with some other standards modes will disable POSIX 1003.1c-1995
 * and XSH5 support, as the thread interfaces violate name space rules
 * required by those standards. For example, defining any of the symbols
 * _POSIX_SOURCE (1003.1-1990), _POSIX_C_SOURCE=199309L (1003.1b-1993),
 * _XOPEN_SOURCE (with no value or with a value less than 500), or
 * _XOPEN_SOURCE_EXTENDED (UNIX95, which requires 1003.1-1990), or
 * _ANSI_C_SOURCE (ANSI C) will disable thread support. A program built with
 * any of these options that includes <pthread.h> will not compile properly,
 * as <sys/types.h> will fail to define types and symbols required by
 * pthread.h.
 *
 * Note that The Single UNIX Specification, Version 2 provides that defining
 * _XOPEN_SOURCE=500 (XSH5) overrides any "inappropriate" settings of
 * _POSIX_C_SOURCE, _POSIX_SOURCE, or _ANSI_C_SOURCE.
 *
 * The <unistd.h> header always defines _POSIX_VERSION to the latest POSIX.1
 * revision supported by the system -- 199506L (1003.1c-1995) for Tru64 UNIX
 * 4.0. A portable program can use this symbol (or specific POSIX feature test
 * macros such as _POSIX_THREADS, also defined in <unistd.h>) to determine
 * whether the system supports POSIX 1003.1c-1995. (However, beware that
 * implementations of early drafts of 1003.1c, such as "DCE threads", which
 * supported 1003.4a/D4, may also define _POSIX_THREADS, but will not define
 * _POSIX_VERSION to 199506L.)
 *
 *****************************************************************************/

#if defined (__DECCXX)
# define _PTHREAD_ENV_CXX
# define _PTHREAD_ENV_DECCXX
#elif defined (__cplusplus)
# define _PTHREAD_ENV_CXX
#elif defined (__DECC) || defined (__decc)
# define _PTHREAD_ENV_DECC
#elif defined (__INTEL_COMPILER)
# define _PTHREAD_ENV_INTELC
#endif

#if defined (VMS) || defined (__VMS) || defined (__vms) || defined (vms)
# define _PTHREAD_ENV_VMS
# define _POSIX_THREAD_PROCESS_SHARED  /* Typically in unistd.h */
#elif defined (__unix__) || defined (__unix) || defined (unix)
# define _PTHREAD_ENV_UNIX
#endif

#if defined (__alpha) || defined (__ALPHA)
# define _PTHREAD_ENV_ALPHA
#elif defined (__ia64__)
# define _PTHREAD_ENV_IA64
#else
# error <pthread.h>: unsupported hardware architecture.
#endif

/*
 * Protect libpthread.so against preemption of libc entry points.
 */
#if defined (_PTHREAD_ENV_UNIX) && defined (_PTHREAD_CORE_BUILD_)
# include <thd_libc_protect.h>
#endif

#ifdef _PTHREAD_ENV_CXX
    extern "C" {
#endif

/*
 * Make sure we are included with _REENTRANT defined. This helps to catch
 * cases where the wrong per-thread errno value will be used.
 *
 * You should always define _REENTRANT on the command line, usually by using
 * "cc -pthread" or "cxx -pthread", to be sure that it will be available for
 * all header files.
 */
#ifdef _PTHREAD_ENV_UNIX
# ifndef _REENTRANT
#  error "Please compile the module including pthread.h with -pthread"
# endif
#endif

#ifdef _PTHREAD_ENV_UNIX
# include <standards.h>
# include <unistd.h>
#endif

#include <stddef.h>

#if defined (_PTHREAD_ENV_UNIX) && !defined (_PTHREAD_CORE_BUILD_)
# define _PTHREAD_EXC_INCL_CLEAN
#endif
#include <pthread_exception.h>
#ifdef _PTHREAD_EXC_INCL_CLEAN
# undef _PTHREAD_EXC_INCL_CLEAN
#endif

#if defined (_PTHREAD_ENV_UNIX)
# if defined (_OSF_SOURCE) && defined (_PTHREAD_ENV_ALPHA)
#  if defined (_PTHREAD_ENV_DECC) || defined (_PTHREAD_ENV_DECCXX)
#   include <c_asm.h>
#   define _PTHREAD_USE_ASM_		1
#  endif
# endif
# define _PTHREAD_USE_MANGLED_NAMES_	1
# ifndef _PTHREAD_LEGACY_NP			/* libpthreads wrappers */
#  ifdef _PTHREAD_ENV_DECC
#   define _PTHREAD_USE_PTDNAM_
#  endif
# endif
# define _PTDNAM(name) __##name
# include <sched.h>
# include <timers.h>
# include <sys/types.h>
# include <time.h>
#else
# include <types.h>
# if defined (_PTHREAD_ENV_DECC) && (__DECC_VER >= 50260000)
#  include <timers.h>
# else
#  ifndef _TIMESPEC_T_
#   define _TIMESPEC_T_
typedef struct timespec {
    unsigned long	tv_sec;		/* seconds */
    long		tv_nsec;	/* nanoseconds */
    } timespec_t;
#  endif
# endif
# ifndef _SCHEDPARAM_T_
#  define _SCHEDPARAM_T_
typedef struct sched_param {
    int sched_priority;
    } sched_param_t;
# endif
# ifndef sched_yield
#  define sched_yield	pthread_yield_np
# endif
#endif

#if defined (_PTHREAD_ENV_DECC)
# define _PTHREAD_INLINE_	__inline
#elif defined (_PTHREAD_ENV_DECCXX)
# define _PTHREAD_INLINE_	inline
#else
# define _PTHREAD_INLINE_
#endif

#ifndef _PTDNAM
# define _PTDNAM(name) name
#endif

#if defined (_PTHREAD_ENV_VMS)
# if defined (__DECC) && (__DECC_VER >= 50000000)
#  define _PTHREAD_USE_ASM_		1
#  if __DECC_VER < 50230004
#   define _PTHREAD_SKIP_LOOPY_ASM_	1
#  endif
#  include <c_asm.h>
# endif
# define _PTHREAD_ALLOW_MIXED_PROTOS_	1
#endif

#if !defined (_PTHREAD_ENV_UNIX)
/*
 * If we are not a UNIX system, then the field names for the POSIX standard
 * types don't have to be name space protected.
 */
# define _Pfield(_arg_)	_arg_
#endif

/******************************************************************************
 *
 * NOTICE: Tru64 UNIX and "name mangling"
 * --------------------------------------
 *
 * On Tru64 UNIX, maintaining binary compatibility for call_shared code using
 * the old 1003.4a/D4 interfaces (many of which have the same names as the
 * 1003.1c functions) requires that the compatibility interfaces retain their
 * names. Since the 1003.4a/D4 and 1003.1c functions must be able to coexist
 * within a process, this inevitably leads to the conclusion that we must give
 * the 1003.1c functions "mangled" names during the 1003.4a/D4 retirement
 * period.
 *
 * To that end, we map the 1003.1c standard names into "mangled" internal
 * names. When 1003.4a/D4 is retired these macros will be removed; the 1003.1c
 * functions will then be given their proper names. Binary compatibility for
 * images compiled during the retirement period will be retained by aliases
 * for the transition names. Note that we "mangle" only the names that are
 * identical to 1003.4a/D4 names. New functions (such as pthread_key_delete)
 * and functions with changed names (such as pthread_key_create, contrasted to
 * 1003.4a/D4's pthread_keycreate) are not mangled.
 *
 * The following names are "mangled":
 *
 *	pthread_attr_getguardsize_np
 *	pthread_attr_getinheritsched
 *	pthread_attr_getstacksize
 *	pthread_attr_setguardsize_np
 *	pthread_attr_setinheritsched
 *	pthread_attr_setstacksize
 *	pthread_cancel
 *	pthread_cond_broadcast
 *	pthread_cond_destroy
 *	pthread_cond_init
 *	pthread_cond_sig_preempt_int_np
 *	pthread_cond_signal
 *	pthread_cond_signal_int_np
 *	pthread_cond_timedwait
 *	pthread_cond_wait
 *	pthread_create
 *	pthread_delay_np
 *	pthread_detach
 *	pthread_equal
 *	pthread_exit
 *	pthread_get_expiration_np
 *	pthread_getspecific
 *	pthread_join
 *	pthread_lock_global_np
 *	pthread_mutex_destroy
 *	pthread_mutex_init
 *	pthread_mutex_lock
 *	pthread_mutex_trylock
 *	pthread_mutex_unlock
 *	pthread_once
 *	pthread_self
 *	pthread_setspecific
 *	pthread_testcancel
 *	pthread_unlock_global_np
 *
 * On OpenVMS this is irrelevant since name binding occurs at link time: when
 * images are activated they bind to a known offset within the image symbol
 * vector. The binary compatibility interface names have been changed, but the
 * arrangement of the transfer vector and symbol vector remain the same. Thus
 * old code linked against the old shareable images will call the correct new
 * routine.
 *
 *****************************************************************************/

/*
 * NOTICE: OpenVMS Alpha 64-bit pointer support
 * --------------------------------------------
 *
 * On OpenVMS Alpha DECthreads generally supports both the 64 bit and 32 bit
 * programming environments. Some external data structures (such as the TEB
 * and attributes objects) cannot vary between interfaces, and are defined to
 * contain 64 bit values regardless of programming environment. Only one
 * 1003.1c routine varies between the interfaces: pthread_join, which writes a
 * "void *" to a caller-provided address. For pthread_join32 only the low 32
 * bits of the thread return value is written. For pthread_join64 all 64 bits
 * are written (this will corrupt caller data if the allocated "void *" is 32
 * bits wide). The default definition of "pthread_join" depends upon the
 * programming environment specified by compiler switches -- in other words,
 * the value of the _INITIAL_POINTER_SIZE macro.
 *
 * The following typedefs allow fields with required sizes to be declared
 * without needing a lot of #pragma __required_pointer_size statements
 * scattered through the header. On Tru64 UNIX these types always correspond
 * unambiguously to a single type. On OpenVMS Alpha the types select the
 * appropriate size to maintain datastructure layout regardless of the default
 * pointer size.
 *
 * Per the convention the 64-bit task force has established, a compilation on
 * OpenVMS Alpha that occurs without any /pointer_size switch should yield
 * only a 32-bit interface. But, if compilation on OpenVMS Alpha occurs with
 * an explicit /pointer_size switch, then (a) all prototypes should accept
 * long [64] bit pointers as arguments and (b) all functions which return
 * pointer values should return [32] bit pointers unless the function is a
 * variant with _64 in the name.
 *
 * The DECthreads team has no intention of supporting short pointer
 * compilation environments (cc -xtaso) on Tru64 UNIX.
 *
 *	NOTE: _PTHREAD_ALLOW_MIXED_PROTOS_ should be defined only for the
 *	OpenVMS Alpha platform.
 */
#ifdef _PTHREAD_ALLOW_MIXED_PROTOS_
# ifdef __INITIAL_POINTER_SIZE
   /*
    * This is a DECC compiler with 64-bit pointer support.
    */
#  ifdef _PTHREAD_CORE_BUILD_
#   define _PTHREAD_MIXED_PROTOS_
#  else
#   if __INITIAL_POINTER_SIZE > 0
     /*
      * The compilation has an explicit /pointer_size.
      */
#    define _PTHREAD_MIXED_PROTOS_
#   endif
#  endif
# else
   /*
    * This is some compiler on AXP/VMS that does not have 64-bit pointer
    * support.
    */
#  ifdef _PTHREAD_CORE_BUILD_
#   error <pthread.h>: OpenVMS compiler without 64-bit pointer support
#  endif
# endif
#endif

#ifdef _PTHREAD_ALLOW_MIXED_PROTOS_
/*
 * On OpenVMS Alpha, some of the fields in DECthreads structures (TEB,
 * pthread_mutex_t, pthread_cond_t) need to be 64-bit pointers regardless of
 * the default pointer size in use by the compiler. They need to be 64 bit
 * fields even on older versions of DEC C (prior to V5.0) which don't support
 * 64 bit pointers at all.
 *
 * If the compiler supports long pointers, we use the __required_pointer_size
 * pragma to force the proper interpretation of these pointers. On older
 * compilers, we use uint64 instead.
 */
typedef __int64			__pthreadLongInt_t;
typedef unsigned __int64	__pthreadLongUint_t;
# ifdef __INITIAL_POINTER_SIZE
#  pragma __required_pointer_size __save
#  pragma __required_pointer_size __long
typedef void			*__pthreadLongAddr_t;
typedef const void		*__pthreadLongConstAddr_t;
typedef char			*__pthreadLongString_t;
typedef const char		*__pthreadLongConstString_t;
typedef __pthreadLongAddr_t	*__pthreadLongAddr_p;
#  pragma __required_pointer_size __short
typedef void			*__pthreadShortAddr_t;
typedef const void		*__pthreadShortConstAddr_t;
typedef char			*__pthreadShortString_t;
typedef const char		*__pthreadShortConstString_t;
typedef __pthreadLongAddr_t	*__pthreadShortAddr_p;
#  pragma __required_pointer_size __restore
# else			/* OpenVMS Alpha with no long pointer support */
typedef unsigned __int64	__pthreadLongAddr_t;
typedef unsigned __int64	__pthreadLongConstAddr_t;
typedef unsigned __int64	__pthreadLongString_t;
typedef unsigned __int64	__pthreadLongConstString_t;
typedef unsigned __int64	__pthreadLongAddr_p;
typedef const void		*__pthreadShortConstAddr_t;
typedef void			*__pthreadShortAddr_t;
typedef char			*__pthreadShortString_t;
typedef const char		*__pthreadShortConstString_t;
typedef __pthreadLongAddr_t	*__pthreadShortAddr_p;
# endif					/* Long pointer support */
#else					/* No mixed pointers */
typedef long			__pthreadLongInt_t;
typedef unsigned long		__pthreadLongUint_t;
typedef void			*__pthreadLongAddr_t;
typedef const void		*__pthreadLongConstAddr_t;
typedef char			*__pthreadLongString_t;
typedef const char		*__pthreadLongConstString_t;
typedef __pthreadLongAddr_t	*__pthreadLongAddr_p;
typedef void			*__pthreadShortAddr_t;
typedef char			*__pthreadShortString_t;
typedef const char		*__pthreadShortConstString_t;
typedef __pthreadLongAddr_t	*__pthreadShortAddr_p;
#endif

typedef __pthreadLongAddr_p	__pthreadTsd_t;

#ifndef PTHREAD_KEYS_MAX
# define PTHREAD_KEYS_MAX		255
#endif
#ifndef _PTHREAD_ENV_UNIX
# ifndef PTHREAD_DESTRUCTOR_ITERATIONS
#  define PTHREAD_DESTRUCTOR_ITERATIONS	4
# endif
#endif
#ifndef PTHREAD_STACK_MIN
# define PTHREAD_STACK_MIN		8192
#endif

#define PTHREAD_CANCEL_DISABLE		0
#define PTHREAD_CANCEL_ENABLE		1

#define PTHREAD_CANCEL_DEFERRED		0
#define PTHREAD_CANCEL_ASYNCHRONOUS	1

#define PTHREAD_CANCELED		(void *)-1

#define PTHREAD_SCOPE_PROCESS		0
#define PTHREAD_SCOPE_SYSTEM		1

#define PTHREAD_MUTEX_NORMAL		0
#define PTHREAD_MUTEX_RECURSIVE		1
#define PTHREAD_MUTEX_ERRORCHECK	2
#define PTHREAD_MUTEX_DEFAULT		PTHREAD_MUTEX_NORMAL

#define PTHREAD_PROCESS_PRIVATE		0
#define PTHREAD_PROCESS_SHARED		1

#define PTHREAD_PRIO_NONE		0
#define PTHREAD_PRIO_PROTECT		1
#define PTHREAD_PRIO_INHERIT		2

/*
 * The following are internal, private flags used by the thread library
 * implementation. Any application or library code depending on the value or
 * meaning of these flags (except in the initialization of static objects
 * using the precise bit patterns constructed by the PTHREAD_*_INITIALIZER
 * family of macros) is unsupported and may break on future releases
 * (including patches).
 *
 * I.e., your code may not dynamically write these bits, nor can your code
 * read or interpret these bits from a thread synchronization object that may
 * have been used. (For example, the thread library may choose to replace the
 * initial bit patterns completely on the first use of a mutex.)
 */
#define _PTHREAD_MSTATE_CONFIG	0x00200000	/* Configure mutex */
#define _PTHREAD_MSTATE_TYPE	0x0f000000	/* Mutex type */
#define _PTHREAD_MTYPE_NORMAL	0x00000000	/*  Normal (fast or metered) */
#define _PTHREAD_MTYPE_RECURS	0x01000000	/*  Recursive */
#define _PTHREAD_MTYPE_ERRCHK	0x02000000	/*  Detect usage errors */
#define _PTHREAD_CSTATE_SLOW	0x00200000	/* Slow signal/broadcast */

/*
 * Validation of caller-allocated structures is minimal, but to allow basic
 * consistency checking each structure comes with a "validation" field that
 * helps to determine whether it's likely to be the correct type. Following
 * are the constants. Note that with the exception of the mutex and condition
 * variable, these constants are stored into memory passed into DECthreads, so
 * we're trusting what the caller says. Mutexes and condition variables, if
 * statically initialized using PTHREAD_COND_INITIALIZER,
 * PTHREAD_MUTEX_INITIALIZER, or their relatives, are loaded with the
 * validation constants at compile time.
 */
#define _PTHREAD_CVALID		(0x06facbd1L)	/* Condition variable */
#define _PTHREAD_MVALID		(0x05bcafe1L)	/* Mutex */
#define _PTHREAD_PVALID		(0xdeadbeefL)	/* Paddock */
#define _PTHREAD_RWVALID	(0x02bacab1L)	/* Read/Write lock */
#define _PTHREAD_CAVALID	(0xaceface1L)	/* Condition attributes */
#define _PTHREAD_MAVALID	(0xecafeca1L)	/* Mutex attributes */
#define _PTHREAD_TAVALID	(0xbeefeed1L)	/* Thread attributes */
#define _PTHREAD_RWVF_STA	0x08000000L
#define _PTHREAD_RWVF_INT	0x10000000L
#define _PTHREAD_RWVF_PRE	0x20000000L
#define _PTHREAD_RWVF_INL	0x40000000L
#define _PTHREAD_RWVF_NAM	0x80000000L
#define _PTHREAD_MVF_STA	0x08000000L
#define _PTHREAD_MVF_INT	0x10000000L
#define _PTHREAD_MVF_PRE	0x20000000L
#define _PTHREAD_MVF_INL	0x40000000L
#define _PTHREAD_MVF_NAM	0x80000000L
#define _PTHREAD_CVF_STA	0x08000000L

#ifndef _PTHREAD_NOMETER_STATIC
# define PTHREAD_MUTEX_INITIALIZER \
    {_PTHREAD_MSTATE_CONFIG, _PTHREAD_MVALID | _PTHREAD_MVF_STA}
# define PTHREAD_COND_INITIALIZER \
    {_PTHREAD_CSTATE_SLOW, _PTHREAD_CVALID | _PTHREAD_CVF_STA}
# define PTHREAD_MUTEX_INITWITHNAME_NP(_n_,_a_) \
    {_PTHREAD_MSTATE_CONFIG, _PTHREAD_MVALID | _PTHREAD_MVF_STA, _n_, _a_}
# define PTHREAD_COND_INITWITHNAME_NP(_n_,_a_) \
    {_PTHREAD_CSTATE_SLOW, _PTHREAD_CVALID | _PTHREAD_CVF_STA, _n_, _a_}
#else
# define PTHREAD_MUTEX_INITIALIZER {0, _PTHREAD_MVALID | _PTHREAD_MVF_STA}
# define PTHREAD_COND_INITIALIZER  {0, _PTHREAD_CVALID | _PTHREAD_CVF_STA}
# define PTHREAD_MUTEX_INITWITHNAME_NP(_n_,_a_) \
    {0, _PTHREAD_MVALID | _PTHREAD_MVF_STA, _n_, _a_}
# define PTHREAD_COND_INITWITHNAME_NP(_n_,_a_) \
    {0, _PTHREAD_CVALID | _PTHREAD_CVF_STA, _n_, _a_}
#endif

#define PTHREAD_RWLOCK_INITIALIZER {_PTHREAD_RWVALID | _PTHREAD_RWVF_STA}
#define PTHREAD_RWLOCK_INITWITHNAME_NP(_n_,_a_) \
	{_PTHREAD_RWVALID | _PTHREAD_RWVF_STA, 0, _n_, _a_}

#define PTHREAD_MUTEX_INITFAST_NP {0, _PTHREAD_MVALID | _PTHREAD_MVF_STA}
#define PTHREAD_MUTEX_INITFASTWITHNAME_NP(_n_,_a_) \
    {0, _PTHREAD_MVALID | _PTHREAD_MVF_STA, _n_, _a_}
#define PTHREAD_MUTEX_INITRECURSIVE_NP \
    {_PTHREAD_MTYPE_RECURS | _PTHREAD_MSTATE_CONFIG, \
    _PTHREAD_MVALID | _PTHREAD_MVF_STA}
#define PTHREAD_MUTEX_INITRECURSIVEWITHNAME_NP(_n_,_a_) \
    {_PTHREAD_MTYPE_RECURS | _PTHREAD_MSTATE_CONFIG, \
    _PTHREAD_MVALID | _PTHREAD_MVF_STA, _n_, _a_}
#define PTHREAD_MUTEX_INITERRCHK_NP \
    {_PTHREAD_MTYPE_ERRCHK | _PTHREAD_MSTATE_CONFIG, \
    _PTHREAD_MVALID | _PTHREAD_MVF_STA}
#define PTHREAD_MUTEX_INITERRCHKWITHNAME_NP(_n_,_a_) \
    {_PTHREAD_MTYPE_ERRCHK | _PTHREAD_MSTATE_CONFIG, \
    _PTHREAD_MVALID | _PTHREAD_MVF_STA, _n_, _a_}

/*
 * OBSOLETE:
 *
 * These macros are special variants of the PTHREAD_MUTEX_INITIALIZER macros.
 *
 * They represent an early attempt to support applications that needed to
 * preempt the C runtime malloc/free package of functions, and avoid problems
 * when the thread library needed to allocate or free memory.
 *
 * The extended documentation of the use of these macros has been removed, and 
 * these functions will be retired in a future release.
 *
 * On Tru64 UNIX, use the tis_allocator_mutex_init() function, instead.
 *
 * On OpenVMS, use LIB$VM_MALLOC/LIB$VM_FREE for raw allocation and free.
 * These don't use mutexes for thread-safety, and they're fully reentrant. No
 * special support is required.
 */
#define _PTHREAD_MUTEX_INITPRE \
    {_PTHREAD_MSTATE_CONFIG, _PTHREAD_MVALID|_PTHREAD_MVF_STA|_PTHREAD_MVF_PRE}
#define _PTHREAD_MUTEX_INITPREWITHNAME(_n_,_a_) \
    {_PTHREAD_MSTATE_CONFIG, \
    _PTHREAD_MVALID|_PTHREAD_MVF_STA|_PTHREAD_MVF_PRE, \
    _n_, _a_}
#define _PTHREAD_MUTEX_INITPRERECUR \
    {_PTHREAD_MTYPE_RECURS | _PTHREAD_MSTATE_CONFIG, \
    _PTHREAD_MVALID | _PTHREAD_MVF_STA | _PTHREAD_MVF_PRE}
#define _PTHREAD_MUTEX_INITPRERECURWITHNAME(_n_,_a_) \
    {_PTHREAD_MTYPE_RECURS | _PTHREAD_MSTATE_CONFIG, \
    _PTHREAD_MVALID | _PTHREAD_MVF_STA | _PTHREAD_MVF_PRE, _n_, _a_}
#define _PTHREAD_MUTEX_INITPREERRCHK \
    {_PTHREAD_MTYPE_ERRCHK | _PTHREAD_MSTATE_CONFIG, \
    _PTHREAD_MVALID | _PTHREAD_MVF_STA | _PTHREAD_MVF_PRE}
#define _PTHREAD_MUTEX_INITPREERRCHKWITHNAME(_n_,_a_) \
    {_PTHREAD_MTYPE_ERRCHK | _PTHREAD_MSTATE_CONFIG, \
    _PTHREAD_MVALID | _PTHREAD_MVF_STA | _PTHREAD_MVF_PRE, _n_, _a_}

/*
 * NOTE: "Constructor keys" are currently supported only for limited use by
 * the dynamic loader to implement the C language "__declspec(__thread)"
 * allocation class. Use for any other purpose at all is completely
 * unsupported. (This may be changed in a future release.)
 */

/*
 * "Constructor keys" (keys created using pthread_key_create_new_np) must
 * be statically initialized using this macro prior to creation, e.g.,
 *
 *	pthread_key_t	key = PTHREAD_KEY_INITIALIZER_NP;
 */
#define PTHREAD_KEY_INITIALIZER_NP	0

/*
 * Flags for pthread_key_construct_np
 */
#define PTHREAD_KEY_ALLTHREAD_NP	0x1  /* Constr/Destr in all threads */

#ifndef _PTHREAD_ENV_UNIX
/*
 * All references to "individual attributes" fields within these attributes
 * object structures MUST be made through the defined function calls in this
 * header file. Not all fields in these structures mean what you might infer
 * from the field type. Not all of the fields are implemented at this time.
 * The name and order of fields may change without notice, although the size
 * of the structure will never change.
 */
typedef struct __pthread_attr_t {
    __pthreadLongUint_t		_Pfield(valid);
    __pthreadLongString_t	_Pfield(name);
    __pthreadLongUint_t		_Pfield(arg);
    __pthreadLongUint_t		_Pfield(reserved)[19];
    } pthread_attr_t;
#endif

#ifndef _PTHREAD_ENV_UNIX
/*
 * All references to "individual attributes" fields within these attributes
 * object structures MUST be made through the defined function calls in this
 * header file. Not all fields in these structures mean what you might infer
 * from the field type. Not all of the fields are implemented at this time.
 * The name and order of fields may change without notice, although the size
 * of the structure will never change.
 */
typedef struct __pthread_mutexattr_t {
    __pthreadLongUint_t	_Pfield(valid);
    __pthreadLongUint_t	_Pfield(reserved)[15];
    } pthread_mutexattr_t;
#endif

#ifndef _PTHREAD_ENV_UNIX
/*
 * All references to "individual attributes" fields within these attributes
 * object structures MUST be made through the defined function calls in this
 * header file. Not all fields in these structures mean what you might infer
 * from the field type. Not all of the fields are implemented at this time.
 * The name and order of fields may change without notice, although the size
 * of the structure will never change.
 */
typedef struct __pthread_condattr_t {
    __pthreadLongUint_t	_Pfield(valid);
    __pthreadLongUint_t	_Pfield(reserved)[13];
    } pthread_condattr_t;
#endif

#ifndef _PTHREAD_ENV_UNIX
/*
 * All references to "individual attributes" fields within these attributes
 * object structures MUST be made through the defined function calls in this
 * header file. Not all fields in these structures mean what you might infer
 * from the field type. Not all of the fields are implemented at this time.
 * The name and order of fields may change without notice, although the size
 * of the structure will never change.
 */
typedef struct __pthread_rwlockattr_t {
    __pthreadLongUint_t	_Pfield(valid);		/* Validation flag */
    __pthreadLongUint_t	_Pfield(reserved)[15];
    } pthread_rwlockattr_t;
#endif

/*
 * All references to "individual attributes" fields within these attributes
 * object structures MUST be made through the defined function calls in this
 * header file. Not all fields in these structures mean what you might infer
 * from the field type. Not all of the fields are implemented at this time.
 * The name and order of fields may change without notice, although the size
 * of the structure will never change.
 */

#ifndef _PTHREAD_ENV_UNIX
/*
 * DECthreads maintains a substantial amount of internal information about
 * each thread in a "Thread Control Block" that is not directly accessible to
 * the programmer. However, some of this information is required by
 * application, library, or debug/profile code in performance critical code
 * paths. Thus, DECthreads provides an architected "Thread Environment Block"
 * that makes a subset of the TCB information available directly. On Alpha
 * hardware systems the address of the TEB is available by using the CALL_PAL
 * RDUNIQ instruction. DECthreads also provides both a macro and a callable
 * function to return the TEB address, for convenience and portability.
 */
# if defined (_PTHREAD_ALLOW_MIXED_PROTOS_) && defined (__INITIAL_POINTER_SIZE)
#  pragma __required_pointer_size __save
#  pragma __required_pointer_size __long
# endif

# ifndef _PTHREAD_ENV_UNIX
/*
 * Define the TEB's version.
 *
 * Version 0: Tru64 UNIX 4.0 and OpenVMS 7.0
 * Version 1: Tru64 UNIX 4.0D and OpenVMS 7.2
 * Version 2: Try64 UNIX V5.1A
 */
#  define PTHREAD_TEB_VERSION		2	/* Current version */
#  define PTHREAD_TEB_SIZE \
     ((size_t)((char *)&((__pthreadTeb_p)0L)->_Pfield(home_rad) \
     - (char *)0L)) + sizeof (int)
#  define PTHREAD_TEB_EFLG_USER		0x01	/* User thread */
#  define PTHREAD_TEB_EFLG_INITIAL	0x02	/* Process initial thread */

#  define PTHREAD_TEB_CREATOR_PTHREAD	1   /* Created by 1003.1c API */
#  define PTHREAD_TEB_CREATOR_CMA	2   /* Created by CMA API */
#  define PTHREAD_TEB_CREATOR_D4	3   /* Created by Draft 4 API */
#  define PTHREAD_TEB_CREATOR_D4EXC	4   /* Created by D4-Exception API */
# endif

/*
 * Thread Environment Block (TEB). (On UNIX, this definition is duplicated in
 * the <sys/types.h> header file.)
 *
 * NOTE: Modification of any field in a thread's TEB structure will result in
 * undefined behavior. Fields that are commented as "RESERVED" are
 * undocumented and unsupported, and the contents or meaning may change at any
 * time. The "per_kt_area" field is reserved entirely for use by DECthreads
 * and the operating system kernel: it contains undefined, undocumented,
 * unsupported, and volatile data of unspecified type.
 *
 * Each public field is documented with a comment that begins with the TEB
 * version in which the field was created or documented. If the TEB "version"
 * has a value lower than version in which the field became accessible, do not
 * depend upon the value of that field.
 *
 * NOTE: The fact that pthread_t is currently the same as __pthreadTeb_p is
 * an artifact of the current IMPLEMENTATION, and is not intended to be a
 * documented or supported relationship. In the future, they may be separate.
 * In general, direct TEB access should be avoided. It is NOT supported (and
 * never will be supported) except on Alpha hardware. On Alpha hardware, TEB
 * access should be done only using the RDUNIQ PAL call, which can be
 * implemented directly or through C using the __pthreadTeb() call.
 */

typedef struct __pthreadTeb_tag {
    __pthreadLongAddr_p	_Pfield(reserved1);	/* Reserved to DECthreads */
    __pthreadLongAddr_p	_Pfield(reserved2);	/* Reserved to DECthreads */
    unsigned short	_Pfield(size);		/* V1: Size of TEB */
    unsigned char	_Pfield(version);	/* TEB version */
    unsigned char	_Pfield(reserved3);	/* Reserved to DECthreads */
    unsigned char	_Pfield(external);	/* V1: PTHREAD_TEB_EFLG_ flgs */
    unsigned char	_Pfield(reserved4)[2];	/* RESERVED */
    unsigned char	_Pfield(creator);	/* V1: PTHREAD_TEB_CREATOR_* */
    __pthreadLongUint_t	_Pfield(sequence);	/* V0: Thread sequence */
    __pthreadLongUint_t	_Pfield(reserved5)[2];	/* Reserved to DECthreads */
    __pthreadLongAddr_t	_Pfield(per_kt_area);	/* V0: Reserved */
    __pthreadLongAddr_t	_Pfield(stack_base);	/* V0: Initial SP */
    __pthreadLongAddr_t	_Pfield(stack_reserve); /* V0: reserved stack */
    __pthreadLongAddr_t	_Pfield(stack_yellow);	/* V0: yellow zone */
    __pthreadLongAddr_t	_Pfield(stack_guard);	/* V0: guard (red) zone */
    __pthreadLongUint_t	_Pfield(stack_size);	/* V0: total stack size */
    __pthreadTsd_t	_Pfield(tsd_values);	/* V0: TSD array (void *) */
    unsigned long	_Pfield(tsd_count);	/* V0: TSD array size */
    unsigned int	_Pfield(reserved6);	/* Reserved to DECthreads */
    unsigned int	_Pfield(reserved7);	/* Reserved to DECthreads */
    unsigned int	_Pfield(thread_flags);	/* Reserved to DECthreads */
    int			_Pfield(thd_errno);	/* V1: thread's errno */
    __pthreadLongAddr_t	_Pfield(stack_hiwater);	/* V1: lowest known SP */
    __pthreadLongUint_t	_Pfield(home_rad);	/* V2: thread's home RAD */
    } __pthreadTeb_t, *__pthreadTeb_p;

typedef __pthreadTeb_t pthreadTeb_t;
typedef __pthreadTeb_p pthreadTeb_p;

/*
 * The only official or supported mechanism to find the TEB of a thread is for
 * code within that thread to execute the "rduniq" call_pal instruction. The
 * following typedef of pthread_t, as a pointer to a TEB, is an unsupported
 * artifact of the current implementation, and will be changed in the future.
 * No correct code may reference a TEB through a pthread_t value.
 */
# if defined (_PTHREAD_ALLOW_MIXED_PROTOS_) && defined (__INITIAL_POINTER_SIZE)
typedef __pthreadTeb_p	pthread_t;	/* Long pointer if possible */
#  pragma __required_pointer_size __restore
# elif defined (_PTHREAD_ENV_ALPHA) && defined (_PTHREAD_ENV_VMS)
typedef unsigned __int64	pthread_t;	/* Force 64 bits anyway */
# else
typedef __pthreadTeb_p		pthread_t;	/* Pointers is pointers */
# endif
#elif !defined(_PTHREAD_NEW_TEB)
/*
 * For compilation on versions of Tru64 UNIX prior to 5.1A, where
 * <sys/types.h> doesn't yet define the namespace-safe variants of the TEB
 * types, declare them here for the benefit of the rest of this header.
 */
typedef pthreadTeb_t	__pthreadTeb_t;
typedef pthreadTeb_t	*__pthreadTeb_p;
#endif

#ifndef _PTHREAD_ENV_UNIX
typedef unsigned int	pthread_key_t;
#endif

typedef void*	__pthreadStartFunc_t (void *);
typedef void	__pthreadDestructorFunc_t (void*);
typedef void*	__pthreadConstructorFunc_t (pthread_key_t, pthread_t);
typedef void	__pthreadExtDestructorFunc_t (void*, pthread_t, pthread_key_t);
typedef void	__pthreadOnceFunc_t (void);

typedef __pthreadStartFunc_t*		__pthreadStart_t;
typedef __pthreadDestructorFunc_t*	__pthreadDestructor_t;
typedef __pthreadConstructorFunc_t*	__pthreadConstructor_t;
typedef __pthreadExtDestructorFunc_t*	__pthreadExtDestructor_t;
typedef __pthreadOnceFunc_t*		__pthreadOnce_t;

/*
 * Macros to utilize the TEB directly for maximum efficiency. With hardware
 * and a compiler that supports it, this header uses inline instructions to
 * get access to the thread's TEB... otherwise this will result in a simple
 * call into DECthreads.
 *
 * It is perfectly reasonable for code to freely access any defined TEB field
 * on any DECthreads platform, as long as you meet all of the following rules
 * (read this section carefully!)
 *
 * You must not depend in any way upon the content or meaning of any
 * "reserved" fields (reserved1, reserved2, reserved3, etc.). These are for
 * DECthreads internal use only and are subject to change without notice.
 *
 * You may not write directly to any field of the TEB. Any modification may
 * result in undefined and possibly severe errors that may show up only much
 * later in the program.
 *
 * Don't make any assumptions about the nature of the sequence number returned
 * by pthread_getsequence_np or pthread_getselfseq_np, except that it is a
 * unique integer among all threads created within the current image.
 * Consecutively created threads may not necessarily have consecutive sequence
 * numbers, nor are all possible sequence numbers necessarily assigned by
 * DECthreads. A thread created "later" does not necessarily have a sequence
 * number higher than that of a thread created "earlier".
 *
 * A thread may read or write thread-specific data values directly to its own
 * tsd_values array. Writing a value to any array element of tsd_values that
 * does not correspond to the value of a thread-specific data key "owned" by
 * the calling subsystem (returned by a call to pthread_key_create or
 * pthread_key_create_new) is erroneous. If you choose to code inline access
 * to the TSD array, do so very cautiously! Write to another thread's
 * tsd_values array only if your code provides sufficient synchronization to
 * ensure that this is "safe" -- in general, this is not a good idea.
 *
 * Only DECthreads and the O/S may use the value of the "per_kt_area" pointer;
 * for other code this is unpredictable and undefined.
 */
#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_self __pthread_self
# endif
#endif
extern pthread_t pthread_self (void);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

/*
 * Return the address of the calling thread's Thread Environment BLock. If
 * inlining is allowed and the platform supports asm(), hide the function
 * behind a macro that inlines the operation.
 */
extern __pthreadTeb_p pthread_teb_np (void);
#if defined (_PTHREAD_USE_ASM_) && defined (_PTHREAD_USE_INLINE)
# define pthread_teb_np()	((__pthreadTeb_p)asm ("call_pal 0x9e"))
#endif

#define pthread_unchecked_getspecific_np(_key_) \
    (pthread_teb_np ()->_Pfield(tsd_values)[_key_])
#define pthread_unchecked_setspecific_np(_key_,_value_) \
    (pthread_teb_np ()->_Pfield(tsd_values)[_key_] = (_value_))

#ifndef _PTHREAD_ENV_UNIX
/*
 * This is the primary structure controlling the identity and state of a
 * mutex. The "lock" field contains the primary mutex lock bit, a flag
 * indicating whether lock/unlock protocols are "fast" or "slow", the full
 * type of the mutex, and an internal reference count. The reference count
 * assures atomicity of unlock/wake sequences with respect to deletion.
 *
 * The "sequence" field gives each mutex a unique identifier, which is
 * primarily used for debugging. A new static mutex has a sequence number of
 * zero; DECthreads assigns a real sequence number when a thread first blocks
 * on the mutex. (A mutex created by calling pthread_mutex_init has a sequence
 * number assigned at creation.)
 *
 * Beware that the name and order of these fields are undocumented and
 * unsupported. Directly accessing any in your program may result in serious
 * difficulties in future releases of the operating system.
 */
typedef struct __pthread_mutex_t {
    unsigned int	_Pfield(lock);		/* LOCK, CONFIG, TYPE, REFCNT */
    unsigned int	_Pfield(valid);		/* Validation info */
    __pthreadLongString_t	_Pfield(name);	/* Name of mutex */
    unsigned int	_Pfield(arg);		/* printf argument for name */
    unsigned int	_Pfield(depth);		/* Recursive lock depth */
    unsigned long	_Pfield(sequence);	/* Mutex sequence number */
    unsigned long	_Pfield(owner);		/* Current owner (if known) */
    __pthreadLongAddr_p	_Pfield(block);		/* Pointer to blocking struct */
    } pthread_mutex_t;
#endif

#ifndef _PTHREAD_ENV_UNIX
/*
 * Similar to pthread_mutex_t, but for a condition variable.
 */
typedef struct __pthread_cond_t {
    unsigned int	_Pfield(state);		/* EVENT, SLOW, REFCNT, etc. */
    unsigned int	_Pfield(valid);		/* Validation info */
    __pthreadLongString_t	_Pfield(name);	/* Name of condition variable */
    unsigned int	_Pfield(arg);		/* printf argument for name */
    unsigned long	_Pfield(sequence);	/* Condition variable seq # */
    __pthreadLongAddr_p	_Pfield(block);		/* Pointer to blocking struct */
    } pthread_cond_t;
#endif

/*
 * Ensure that an initialization routine is called exactly once.
 */
#define PTHREAD_ONCE_UNINIT	0
#define PTHREAD_ONCE_INITING	1
#define PTHREAD_ONCE_INITED	2
#define PTHREAD_ONCE_INIT	{PTHREAD_ONCE_UNINIT}
#ifndef _PTHREAD_ENV_UNIX
typedef volatile struct __pthread_once_t {
    long	_Pfield(state);
    long	_Pfield(reserved)[10];
    } pthread_once_t;
#endif

#ifndef _PTHREAD_ENV_UNIX
/*
 * Readers-Writers Locks
 */
typedef struct __pthread_rwlock_t {
    unsigned int	_Pfield(valid);		/* Validation flag */
    unsigned int	_Pfield(flags);		/* Internal flags */
    __pthreadLongString_t	_Pfield(name);	/* Name of rwlock */
    unsigned int	_Pfield(arg);		/* printf argument for name */
    unsigned int	_Pfield(readers);	/* Number of readers */
    unsigned int	_Pfield(rwaits);	/* Waiting readers */
    unsigned int	_Pfield(wwaits);	/* Waiting writers */
    __pthreadLongUint_t	_Pfield(sequence);	/* rwlock variable seq # */
    unsigned long	_Pfield(wrid);		/* Current write owner */
    __pthreadLongAddr_p	_Pfield(block);		/* Pointer to blocking struct */
    __pthreadLongUint_t	_Pfield(reserved1);	/* Reserved to DECthreads */
    } pthread_rwlock_t;
#endif

#define PTHREAD_INHERIT_SCHED		0
#define PTHREAD_EXPLICIT_SCHED		1

#define PTHREAD_CREATE_JOINABLE		0
#define PTHREAD_CREATE_DETACHED		1

#ifndef _PTHREAD_ENV_UNIX
# define SCHED_FIFO	1		/* Tru64 UNIX sched.h defines */
# define SCHED_RR	2		/* these constants already */
# define SCHED_OTHER	3
# define SCHED_FG_NP	SCHED_OTHER	/* "Foreground" (Timeshare) */
# define SCHED_BG_NP	(SCHED_OTHER+1)	/* "Background" */
# define SCHED_LFI_NP	(SCHED_OTHER+2)	/* "Low FIFO" (background FIFO) */
# define SCHED_LRR_NP	(SCHED_OTHER+3)	/* "Low RR" (background RR) */
#endif

#if (defined _PTHREAD_ENV_UNIX) && (defined _OSF_SOURCE)
# define PRI_FIFO_MIN	14
# define PRI_FIFO_MAX	SCHED_PRIO_RT_MAX
# define PRI_RR_MIN	14
# define PRI_RR_MAX	SCHED_PRIO_RT_MAX
# define PRI_OTHER_MIN	14
# define PRI_OTHER_MAX	SCHED_PRIO_RT_MAX
# define PRI_FG_MIN_NP	14
# define PRI_FG_MAX_NP	63
# define PRI_BG_MIN_NP	0
# define PRI_BG_MAX_NP	13
# define PRI_LFI_MIN_NP	0
# define PRI_LFI_MAX_NP	13
# define PRI_LRR_MIN_NP	0
# define PRI_LRR_MAX_NP	13
#elif defined (_PTHREAD_ENV_VMS)
# define PRI_FIFO_MIN	16
# define PRI_FIFO_MAX	31
# define PRI_RR_MIN	16
# define PRI_RR_MAX	31
# define PRI_OTHER_MIN	PRI_FG_MIN_NP
# define PRI_OTHER_MAX	PRI_FG_MAX_NP
# define PRI_FG_MIN_NP	8
# define PRI_FG_MAX_NP	15
# define PRI_BG_MIN_NP	0
# define PRI_BG_MAX_NP	7
# define PRI_LFI_MIN_NP	0
# define PRI_LFI_MAX_NP	7
# define PRI_LRR_MIN_NP	0
# define PRI_LRR_MAX_NP	7

# define sched_get_priority_max (_pol_) \
   (_pol_ == SCHED_OTHER ? PRI_FG_MAX_NP : PRI_FIFO_MAX)
# define sched_get_priority_min (_pol_) \
   (_pol_ == SCHED_OTHER ? PRI_FG_MIN_NP : PRI_FIFO_MIN)
#endif

#ifdef _PTHREAD_ENV_UNIX
# if !defined (_XOPEN_SOURCE) || (_XOPEN_SOURCE+0 < 400)
extern int pthread_sigmask (int, const sigset_t*, sigset_t*);

extern int pthread_kill (pthread_t, int);
# endif
#endif

/*
 * DECthreads provides three distinct types of mutex. The default (normal or
 * "fast" mutex), which can lock and unlock with completely inline code on
 * Alpha processors, but does no consistency checking; the "recursive" mutex
 * which allows a given thread to lock a mutex it already owns without
 * deadlock (it remains locked until all nested locks are released); and the
 * "errorcheck" mutex, which behaves much like a normal mutex but checks for
 * self deadlock and for releasing a mutex that is either unowned or is owned
 * by another thread. The recursive and errorcheck mutexes require a call
 * into the DECthreads library for every lock and unlock.
 *
 * When synchronization metering is enabled, all mutex types monitor every
 * lock and unlock. A mutex statically initialized using
 * PTHREAD_MUTEX_INITIALIZER is "normal", but is set up so that the first use
 * of the mutex will result in a call into DECthreads (as if the mutex was
 * already locked). If synchronization metering is not enabled, DECthreads
 * will disable this extra state so that future references (in the absence of
 * normal mutex contention) will not cause unnecessary calls. Should you wish
 * to avoid this initial call, you can compile with _PTHREAD_NOMETER_STATIC;
 * normal mutexes statically initialized using this option are not metered.
 */
extern int pthread_mutexattr_init (pthread_mutexattr_t*);

#ifdef _PTHREAD_ENV_UNIX
extern int pthread_mutexattr_getprioceiling (const pthread_mutexattr_t*, int*);

extern int pthread_mutexattr_setprioceiling (pthread_mutexattr_t*, int);
#else
# define pthread_mutexattr_getprioceiling pthread_mutexattr_getpriceiling
extern int pthread_mutexattr_getpriceiling (const pthread_mutexattr_t*, int*);

# define pthread_mutexattr_setprioceiling pthread_mutexattr_setpriceiling
extern int pthread_mutexattr_setpriceiling (pthread_mutexattr_t*, int);
#endif

extern int pthread_mutexattr_getprotocol (const pthread_mutexattr_t*, int*);

extern int pthread_mutexattr_setprotocol (pthread_mutexattr_t*, int);

extern int pthread_mutexattr_getpshared (const pthread_mutexattr_t*, int*);

extern int pthread_mutexattr_setpshared (pthread_mutexattr_t*, int);

extern int pthread_mutexattr_gettype (const pthread_mutexattr_t*, int*);

extern int pthread_mutexattr_settype (pthread_mutexattr_t*, int);

extern int pthread_mutexattr_destroy (pthread_mutexattr_t*);

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_mutex_init __pthread_mutex_init
# endif
#endif
extern int pthread_mutex_init (pthread_mutex_t*, const pthread_mutexattr_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_mutex_destroy __pthread_mutex_destroy
# endif
#endif
extern int pthread_mutex_destroy (pthread_mutex_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef  _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_mutex_lock __pthread_mutex_lock
# endif
#endif
extern int pthread_mutex_lock (pthread_mutex_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

extern int pthread_mutex_getprioceiling (const pthread_mutex_t*, int*);

extern int pthread_mutex_setprioceiling (pthread_mutex_t*, int, int*);

#if defined (_PTHREAD_ENV_VMS)
extern int pthread_mutex_tryforcedlock_np (pthread_mutex_t*);
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_mutex_trylock __pthread_mutex_trylock
# endif
#endif
extern int pthread_mutex_trylock (pthread_mutex_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_mutex_unlock __pthread_mutex_unlock
# endif
#endif
extern int pthread_mutex_unlock (pthread_mutex_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

extern int pthread_condattr_init (pthread_condattr_t*);

extern int pthread_condattr_destroy (pthread_condattr_t*);

extern int pthread_condattr_setpshared (pthread_condattr_t*, int);

extern int pthread_condattr_getpshared (const pthread_condattr_t*, int*);

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_cond_init __pthread_cond_init
# endif
#endif
extern int pthread_cond_init (
	pthread_cond_t*,
	const pthread_condattr_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_cond_destroy __pthread_cond_destroy
# endif
#endif
extern int pthread_cond_destroy (pthread_cond_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_cond_signal __pthread_cond_signal
# endif
#endif
extern int pthread_cond_signal (pthread_cond_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_cond_broadcast __pthread_cond_broadcast
# endif
#endif
extern int pthread_cond_broadcast (pthread_cond_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_cond_wait __pthread_cond_wait
# endif
#endif
extern int pthread_cond_wait (pthread_cond_t*, pthread_mutex_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_cond_timedwait __pthread_cond_timedwait
# endif
#endif
extern int pthread_cond_timedwait (
	pthread_cond_t*,
	pthread_mutex_t*,
	const struct timespec*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

extern int pthread_rwlockattr_init (pthread_rwlockattr_t*);

extern int pthread_rwlockattr_destroy (pthread_rwlockattr_t*);

extern int pthread_rwlockattr_getpshared (const pthread_rwlockattr_t*, int*);

extern int pthread_rwlockattr_setpshared (pthread_rwlockattr_t*, int);

extern int pthread_rwlock_init (pthread_rwlock_t*, const pthread_rwlockattr_t*);

extern int pthread_rwlock_destroy (pthread_rwlock_t*);

extern int pthread_rwlock_rdlock (pthread_rwlock_t*);

extern int pthread_rwlock_tryrdlock (pthread_rwlock_t*);

extern int pthread_rwlock_wrlock (pthread_rwlock_t*);

extern int pthread_rwlock_trywrlock (pthread_rwlock_t*);

extern int pthread_rwlock_unlock (pthread_rwlock_t*);

/*
 * Routines to get/set the contention scope for a thread that will be created
 * using the attributes object.
 */
extern int pthread_attr_getscope (const pthread_attr_t*, int*);

extern int pthread_attr_setscope (pthread_attr_t*, int);

/*
 * Extended versions of set/get stackaddr routines that allow the caller to
 * specify the stack using a low address and size. The implementation will
 * compute the proper "stack base" using this information. E.g. you might mmap
 * space, add the size to the returned pointer, and then pass the result to
 * pthread_attr_setstackaddr on a machine with a pre-decremented stack
 * pointer; but on a machine with a post-incremented stack you would pass the
 * pointer returned by mmap. Using pthread_attr_setstack instead, you always
 * pass the pointer returned by mmap and the requested size.
 */
extern int pthread_attr_setstack (pthread_attr_t*, void*, size_t);
#define pthread_attr_setstackaddr_np pthread_attr_setstack

extern int pthread_attr_getstack (const pthread_attr_t*, void**, size_t*);
#define pthread_attr_getstackaddr_np pthread_attr_getstack

/*
 * Routines to get/set the stack address for a thread that will be created
 * using the attributes object. Note that "stackaddr" must be the correct
 * initial stack BASE for the thread, which is highly machine-dependent.
 * (E.g., does the machine increment or decrement the stack, and does it do so
 * before or after storing a new value?) Use of these functions is inherently
 * NON-PORTABLE, and they should be used only with great caution.
 * Additionally, they do not provide any way for the implementation to know
 * the size of the stack, so it can neither prevent nor detect stack overflows
 * or the corruption that may be caused by this application error. (See the
 * XOPEN and POSIX 1003.1-2001 pthread_attr_setstack and pthread_attr_getstack
 * routine descriptions.)
 */
extern int pthread_attr_setstackaddr (pthread_attr_t*, void*);

extern int pthread_attr_getstackaddr (const pthread_attr_t*, void**);

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_attr_setinheritsched __pthread_attr_setinheritsched
# endif
#endif
extern int pthread_attr_setinheritsched (pthread_attr_t*, int);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_attr_getinheritsched __pthread_attr_getinheritsched
# endif
#endif
extern int pthread_attr_getinheritsched (const pthread_attr_t*, int*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

extern int pthread_attr_setschedpolicy (pthread_attr_t*, int);

extern int pthread_attr_getschedpolicy (const pthread_attr_t*, int*);

extern int pthread_attr_setschedparam (
	pthread_attr_t*, const struct sched_param*);

extern int pthread_attr_getschedparam (
	const pthread_attr_t*, struct sched_param*);

extern int pthread_getcputime_np (pthread_t, struct timespec*);

extern int pthread_getschedparam (pthread_t, int*, struct sched_param*);

extern int pthread_setschedparam (pthread_t, int, const struct sched_param*);

extern int pthread_getconcurrency (void);

extern int pthread_setconcurrency (int);

extern int pthread_attr_init (pthread_attr_t*);

extern int pthread_attr_destroy (pthread_attr_t*);

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_attr_setstacksize __pthread_attr_setstacksize
# endif
#endif
extern int pthread_attr_setstacksize (pthread_attr_t*, size_t);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_attr_getstacksize __pthread_attr_getstacksize
# endif
#endif
extern int pthread_attr_getstacksize (
	const pthread_attr_t*,
	size_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

extern int pthread_attr_setdetachstate (pthread_attr_t*, int);

extern int pthread_attr_getdetachstate (const pthread_attr_t*, int*);

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_create __pthread_create
# endif
#endif
extern int pthread_create (
	pthread_t*,
	const pthread_attr_t*,
	void* (*)(void *),
	void*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_ALLOW_MIXED_PROTOS_
extern int pthread_join64 (pthread_t, __pthreadLongAddr_t*);
extern int pthread_join32 (pthread_t, __pthreadShortAddr_t*);
# ifdef pthread_join
#  undef pthread_join
# endif
# if defined (_PTHREAD_MIXED_PROTOS_) && (__INITIAL_POINTER_SIZE == 64)
#  define pthread_join pthread_join64
# else
#  define pthread_join pthread_join32
# endif
#else
# ifdef _PTHREAD_USE_MANGLED_NAMES_
#  ifdef _PTHREAD_USE_PTDNAM_
#   pragma extern_prefix "__"
#  else
#   define pthread_join __pthread_join
#  endif
# endif
extern int pthread_join (pthread_t, void**);
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix ""
# endif
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_detach __pthread_detach
# endif
#endif
extern int pthread_detach (pthread_t);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_exit __pthread_exit
# endif
#endif
extern void pthread_exit (void*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_equal __pthread_equal
# endif
#endif
extern int pthread_equal (pthread_t, pthread_t);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

/*
 * See the note near the top of this header for the risks and benefits of
 * using inlined operations! They are NOT compiled into your program by
 * default, and if you choose to enable them you will be required to
 * recompile should DECthreads ever need to change the inline instruction
 * sequences! (While we will not do this arbitrarily, we will not hesitate
 * should it become necessary to substantially improve code performance or
 * reliability, or to fix a bug!)
 */

#ifdef _PTHREAD_USE_INLINE
# ifdef pthread_equal
#  undef pthread_equal
# endif
# define pthread_equal(t1,t2) (t1==t2)
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_once __pthread_once
# endif
#endif
extern int pthread_once (pthread_once_t*, __pthreadOnce_t);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

extern int pthread_key_create (pthread_key_t*, __pthreadDestructor_t);

extern int pthread_key_delete (pthread_key_t);

extern int pthread_key_create_new_np (
	pthread_key_t*,
	__pthreadConstructor_t,
	__pthreadExtDestructor_t,
	int);

/*
 * See the note near the top of this header for the risks and benefits of
 * using inlined operations! They are NOT compiled into your program by
 * default, and if you choose to enable them you will be required to
 * recompile should DECthreads ever need to change the inline instruction
 * sequences! (While we will not do this arbitrarily, we will not hesitate
 * should it become necessary to substantially improve code performance or
 * reliability, or to fix a bug!)
 *
 * Additional note:
 *
 * pthread_getspecific can't be efficiently implemented as a macro in ANSI C,
 * since it involves two invocations of pthread_teb_np(), which the compiler can't
 * be depended upon to combine. The next best alternative is a static inlined
 * routine; even if the #pragma inline isn't recognized by your compiler it's
 * no worse than the real call (and may be better because the compiler can use
 * optimized local call sequences); and the routine is small. Consider this an
 * experiment -- it can be used for a lot more if it works well.
 */

#if defined (_PTHREAD_USE_ASM_) && defined (_PTHREAD_USE_INLINE)
_PTHREAD_INLINE_ static void *
pthread_getspecific (pthread_key_t __key)
    {
    __pthreadTeb_p	__teb = pthread_teb_np ();
    return (void *)(__key >= __teb->_Pfield(tsd_count)
		? NULL : __teb->_Pfield(tsd_values)[__key]);
    }
#else
# ifdef _PTHREAD_USE_MANGLED_NAMES_
#  ifdef _PTHREAD_USE_PTDNAM_
#   pragma extern_prefix "__"
#  else
#   define pthread_getspecific __pthread_getspecific
#  endif
# endif
extern void* pthread_getspecific (pthread_key_t);
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix ""
# endif
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_setspecific __pthread_setspecific
# endif
#endif
extern int pthread_setspecific (pthread_key_t, const void*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#if defined (_PTHREAD_EXC_USE_NATIVE)
# define pthread_cleanup_push(_routine_,_arg_) \
    { \
    void (*_XXX_proc) (void *) = (void (*)(void *))(_routine_); \
    void *_XXX_arg = (void *)(_arg_); \
    int _XXX_completed = 0; \
    _PTHREAD_NATIVE_TRY {
# define pthread_cleanup_pop(_execute_) \
    _XXX_completed = 1;} \
    _PTHREAD_NATIVE_FINALLY { \
	if ((! _XXX_completed) || (_execute_)) _XXX_proc (_XXX_arg);} \
    }
#else
# define pthread_cleanup_push(_routine_,_arg_)	\
    { \
    void (*_XXX_proc) (void *) = (void (*)(void *))(_routine_); \
    void *_XXX_arg = (void *)(_arg_); \
    int _XXX_completed = 0; \
    PTHREAD_TRY_NP {

# define pthread_cleanup_pop(_execute_)	\
    _XXX_completed = 1;} \
    PTHREAD_FINALLY_NP { \
	if ((! _XXX_completed) || (_execute_)) _XXX_proc (_XXX_arg);} \
    PTHREAD_ENDTRY_NP}
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_cancel __pthread_cancel
# endif
#endif
extern int pthread_cancel (pthread_t);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

extern int pthread_setcancelstate (int, int*);

extern int pthread_setcanceltype (int, int*);

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_testcancel __pthread_testcancel
# endif
#endif
extern void pthread_testcancel (void);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

/*
 * DECthreads non-portable extensions to POSIX 1003.1c-1995.
 */

/*
 * Get or set a name to be associated with threads created using the
 * attributes object. Note that only the thread attributes object includes a
 * name -- for other objects, it is sufficient to set the name immediately
 * after initializing the object (whereas a thread may run between the call to
 * pthread_create and the call to pthread_setname_np, without a name).
 *
 * Note that the "void*" value to which "mbz" points MAY be written by the
 * thread library. On Alpha hardware (Tru64 UNIX and OpenVMS) and on IA-64,
 * the value to which "mbz" points must be a 64-bit pointer. If you are
 * compiling with short pointers, you must take extra steps to ensure that you
 * have allocated a 64-bit value to receive the result.
 */
extern int pthread_attr_getname_np (
	const pthread_attr_t*,
	char*,
	size_t,
	void**);

extern int pthread_attr_setname_np (pthread_attr_t*, const char*, void*);

/*
 * Get or set a name on a condition variable.
 */
extern int pthread_cond_getname_np (pthread_cond_t*, char*, size_t);

extern int pthread_cond_setname_np (pthread_cond_t*, const char*, void*);

/*
 * Get or set a name on a thread-specific data key
 */
extern int pthread_key_getname_np (pthread_key_t, char*, size_t);

extern int pthread_key_setname_np (pthread_key_t, const char*, void*);

/*
 * Get or set a name on a mutex
 */
extern int pthread_mutex_getname_np (pthread_mutex_t*, char*, size_t);

extern int pthread_mutex_setname_np (pthread_mutex_t*, const char*, void*);

/*
 * Get or set a name on a rwlock
 */
extern int pthread_rwlock_getname_np (pthread_rwlock_t*, char*, size_t);

extern int pthread_rwlock_setname_np (pthread_rwlock_t*, const char*, void*);

/*
 * Get or set a name on a thread
 */
extern int pthread_getname_np (pthread_t, char*, size_t);

extern int pthread_setname_np (pthread_t, const char*, void*);

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_cond_sig_preempt_int_np __pthread_cond_sig_preempt_int_np
# endif
#endif
extern int pthread_cond_sig_preempt_int_np (pthread_cond_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_cond_signal_int_np __pthread_cond_signal_int_np
# endif
#endif
extern int pthread_cond_signal_int_np (pthread_cond_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_get_expiration_np __pthread_get_expiration_np
# endif
#endif
extern int pthread_get_expiration_np (const struct timespec*, struct timespec*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_delay_np __pthread_delay_np
# endif
#endif
extern int pthread_delay_np (const struct timespec*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_lock_global_np __pthread_lock_global_np
# endif
#endif
extern int pthread_lock_global_np (void);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_unlock_global_np __pthread_unlock_global_np
# endif
#endif
extern int pthread_unlock_global_np (void);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

extern int pthread_attr_setguardsize (pthread_attr_t*, size_t);

extern int pthread_attr_getguardsize (const pthread_attr_t*, size_t*);

extern unsigned long pthread_getsequence_np (pthread_t);

extern unsigned long pthread_getselfseq_np (void);

/*
 * By default (unless #undef-ed) use an inlined macro version of
 * pthread_getsequence_np, since it's trivial.
 */
#define pthread_getsequence_np(_t_) (((__pthreadTeb_p)(_t_))->_Pfield(sequence))
#define pthread_getselfseq_np() (pthread_teb_np ()->_Pfield(sequence))

/*
 * The POSIX 1003.1c pthread_getspecific() function doesn't report any
 * errors. If the key value is illegal, or if the thread has no value for the
 * key, it returns NULL without any error indication. Normally that's not a
 * problem. However if you really want to know whether a key is valid, you
 * can use this function. It will return EINVAL if the key is invalid, ENOENT
 * if the key exists but the thread has no value for the key (or value is
 * NULL), and 0 if the key is valid and the thread has a value.
 */
extern int pthread_key_validate_np (pthread_key_t);

extern int pthread_yield_np (void);

/*
 * OBSOLETE functions will be moved here before destruction.
 */

/*
 * The "DCE thread" heritage _np mutex type attribute operations have been
 * superceded by the Single UNIX Specification, Version 2 operations. (Same
 * name but without the _np suffix.) The _np variations will be removed in a
 * future release.
 */

#define PTHREAD_MUTEX_NORMAL_NP		PTHREAD_MUTEX_NORMAL
#define PTHREAD_MUTEX_RECURSIVE_NP	PTHREAD_MUTEX_RECURSIVE
#define PTHREAD_MUTEX_ERRORCHECK_NP	PTHREAD_MUTEX_ERRORCHECK

extern int pthread_mutexattr_gettype_np (const pthread_mutexattr_t*, int*);

extern int pthread_mutexattr_settype_np (pthread_mutexattr_t*, int);

/*
 * The "DCE thread" heritage _np guardsize attribute operations have been
 * superceded by the Single UNIX Specification, Version 2 operations. (Same
 * name but without the _np suffix.) The _np variations will be removed in a
 * future release.
 */
#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_attr_getguardsize_np __pthread_attr_getguardsize_np
# endif
#endif
extern int pthread_attr_getguardsize_np (const pthread_attr_t*, size_t*);

#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_attr_setguardsize_np __pthread_attr_setguardsize_np
# endif
#endif
extern int pthread_attr_setguardsize_np (
	pthread_attr_t*,
	size_t);

#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

/*
 * OBSOLETE: The function pthread_debug() is no longer implemented. The entry
 * point remains for source/binary compatibility for now, but will be removed
 * in a future release.
 */
extern void pthread_debug (void);

/*
 * OBSOLETE: This type is no longer used. The definition remains for
 * source/binary compatibility for now, but will be removed in a future
 * release.
 */
typedef enum pthreadDbgStatus_t {
    PTHREAD_DBG_SUCCESS = 0,
    PTHREAD_DBG_QUIT = 1,
    PTHREAD_DBG_NONESEL = 2,
    PTHREAD_DBG_SUCCESSPEND = 3,
    PTHREAD_DBG_NOPRIV = -1,
    PTHREAD_DBG_INVPARAM = -2,
    PTHREAD_DBG_INVSEQ = -3,
    PTHREAD_DBG_INCONSTATE = -4,
    PTHREAD_DBG_CORRUPT = -5,
    PTHREAD_DBG_INVOPTION = -6,
    PTHREAD_DBG_NOARG = -7,
    PTHREAD_DBG_INVADDR = -8,
    PTHREAD_DBG_INVCMD = -9,
    PTHREAD_DBG_NULLCMD = -10,
    PTHREAD_DBG_CONFLICT = -11,
    PTHREAD_DBG_UNIMPL = -12
    } pthreadDbgStatus_t;

/*
 * OBSOLETE: The function pthread_debug_cmd() is no longer implemented. The
 * entry point remains for source/binary compatibility for now, but will be
 * removed in a future major release.
 */
extern pthreadDbgStatus_t pthread_debug_cmd (char *);

#ifdef _PTHREAD_ENV_CXX
    } /* End of extern "C" { */
#endif

#endif					/* _PTHREAD_USE_D4 */

#endif
