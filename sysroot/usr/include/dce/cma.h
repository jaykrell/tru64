/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: cma.template.h,v $
 * Revision 1.1.19.1  2003/09/12  19:07:56  devbld_zko
 * 	DECthreads V3.20-049 submit
 * Merge Information:  Non-Visual Merge: User specified tree thdbl19
 *     User Revision:  thdbl20_br:1.1.12.2 Local Ancestor: n/a
 *    Merge Revision:  thdbl19_br:1.1.8.3
 *   Common Ancestor:  1.1.8.2
 * 	thdbl20-3-miken
 * 	NOP merge with thdbl19
 *
 * Revision 1.1.8.3  2003/08/26  15:22:08  Mike_Neverisky
 * Merge Information:  Non-Visual Merge: User specified tree thdbl18
 *     User Revision:  thdbl19_br:1.1.8.2 Local Ancestor: n/a
 *    Merge Revision:  thdbl18_br:1.1.3.3
 *   Common Ancestor:  1.1.3.2
 * 	thdbl19-2-miken
 * 	NOP merge with thdbl18
 * 
 * Revision 1.1.3.3  2003/07/10  01:25:43  Mike_Neverisky
 * 	thdbl18-6-miken
 * 	Correct OldLog/EndLog token usage
 * 
 * Revision 1.1.12.2  2002/10/22  19:55:49  Peter_Portante
 * Merge Information:  Non-Visual Merge: User specified tree thdbl19
 *     User Revision:  thdbl20_br:1.1.12.1 Local Ancestor: n/a
 *    Merge Revision:  thdbl19_br:1.1.8.2
 *   Common Ancestor:  1.1.8.1
 * 	[2002/09/25  20:14:02  Peter_Portante]
 * 
 * Revision 1.1.12.1  2002/08/14  19:38:31  devbld_zko
 * 	Populate thdbl20
 * 
 * Revision 1.1.8.2  2002/07/31  18:27:20  Peter_Portante
 * Merge Information:  Non-Visual Merge: User specified tree thdbl18
 *     User Revision:  thdbl19_br:1.1.8.1 Local Ancestor: n/a
 *    Merge Revision:  thdbl18_br:1.1.3.2
 *   Common Ancestor:  1.1.3.1
 * 
 * Revision 1.1.3.2  2002/06/25  19:42:57  Peter_Portante
 * Merge Information:  Non-Visual Merge: User specified tree thdbl17
 *     User Revision:  Peter_Portante_bl18_br:1.1.12.1 Local Ancestor:1.1.3.1
 *    Merge Revision:  thdbl17_br:1.1.11.1
 *   Common Ancestor:  1.1.3.1
 * 	[2002/05/28  19:41:03  Peter_Portante]
 * 	Begin merge with BL17
 * 	[2002/05/24  19:54:51  Peter_Portante]
 * 
 * Revision 1.1.11.1  2002/05/24  12:56:59  Peter_Portante
 * 	Add to BL17.
 * 
 * Revision 1.1.6.3  2002/01/28  20:00:59  Mike_Neverisky
 * 	Initiating thdbl20
 * Merge Information:  Non-Visual Merge: User specified tree thdbl19
 *     User Revision:  thddev_br:1.1.6.2 Local Ancestor: n/a
 *    Merge Revision:  thdbl19_br:1.1.8.1
 *   Common Ancestor:  1.1.6.2
 * 	Functional NOP merge of thdbl19 into thddev
 * 
 * Revision 1.1.8.1  2002/01/25  21:35:23  devbld_zko
 * 	Populate thdbl19 from thddev
 * 
 * Revision 1.1.6.2  2001/10/31  19:01:52  Tom_Dahl
 * 	Code review feedback: Another reason why constants are used is because
 * 	DEC Ada doesn't use this header file, and so uses hard-coded values
 * 	itself. By hard-coding them here, the symbols can't inadvertently be
 * 	redefined if/when the underlying POSIX symbols change.
 * 	[2001/10/31  12:56:53  Tom_Dahl]
 * 	Manual merge of a change to cma.h in thdbl17 which apparently got lost
 * 	when templatizing this file.
 * 	Use constants for cma_c_sched_ada_low and cma_c_sched_ada_rtb, so as
 * 	to not risk confusing them with POSIX policies.
 * 	[2001/10/30  15:51:55  Tom_Dahl]
 * 
 * Revision 1.1.6.1  2001/08/06  22:06:37  Peter_Portante
 * 	Add to thddev shared sandbox
 * 
 * Revision 1.1.3.1  2001/01/11  18:11:51  Bill_Blanding
 * 	This file is a template which is used for the generation
 * 	of the include file cma.h during a build.
 * 	It was created from and replaces cma.h.
 * 	All future changes desired for cma.h.
 * 	must be made either to this file or to
 * 	the text substitution files [identified in pthreads_include.mk]
 * 	which are merged with this template during the build process.
 * 	Text insertion points are identified by the string: __REPLACE_ME_WITH_FILE.
 * 
 * Revision 1.1.16.4  2001/01/05  20:58:38  Peter_Portante
 * Merge Information:  Non-Visual Merge: User specified tree thdbl17
 *     User Revision:  thdbl18_br:1.1.16.3 Local Ancestor: n/a
 *    Merge Revision:  thdbl17_br:1.1.15.3
 *   Common Ancestor:  1.1.15.2
 * 
 * Revision 1.1.16.3  2000/11/03  20:14:18  Peter_Portante
 * Merge Information:  Non-Visual Merge: User specified tree yankeeos.nightly
 *     User Revision:  thdbl18_br:1.1.16.2 Local Ancestor: n/a
 *    Merge Revision:  yankeeos_nightly:1.1.26.2
 *   Common Ancestor:  1.1.16.2
 * 
 * Revision 1.1.15.3  2000/10/24  16:39:37  Mary_Sullivan
 * 	Since we're now adjusting the extern_model (and setting nostandard)
 * 	prior to inclusion of cma_config.h, we shouldn't base our decision
 * 	to do so on the value of CMA_ symbols defined in cma_config.h
 * 
 * Revision 1.1.26.2  2000/10/18  20:35:26  Peter_Portante
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree devbld_zko:thdbl18
 *     User Revision:  Peter_Portante_yk_br:1.1.23.1 Local Ancestor:1.1.16.1
 *    Merge Revision:  thdbl18_br:1.1.16.2
 *   Common Ancestor:  1.1.16.1
 * 
 * Revision 1.1.16.2  2000/10/07  17:54:39  Peter_Portante
 * Merge Information:  Non-Visual Merge: User specified tree thdbl17
 *     User Revision:  thdbl18_br:1.1.16.1 Local Ancestor: n/a
 *    Merge Revision:  thdbl17_br:1.1.15.2
 *   Common Ancestor:  1.1.15.1
 * 
 * Revision 1.1.23.1  2000/08/02  19:30:58  Peter_Portante
 * 	Fail any compilation without -threads.
 * 
 * Revision 1.1.15.2  2000/05/30  16:16:34  Mary_Sullivan
 * 	For VMS, save/adjust the extern model (for Alpha) and issue the
 * 	nostandard pragma (for VAX) before including cma_config.h, as that
 * 	header now assumes these are appropriately set.
 * 
 * Revision 1.1.16.1  2000/03/02  21:35:10  devbld_zko
 * 	Move from BL17 to BL18
 * 
 * Revision 1.1.15.1  2000/03/01  15:44:09  Peter_Portante
 * 	Adding BL16 version to BL17
 * 
 * Revision 1.1.9.1  1999/11/03  05:04:06  Peter_Portante
 * 	Move to thdbl16
 * 
 * Revision 1.1.4.3  1999/05/28  14:15:11  Terry_Cassidy
 * 	Initial CMS version
 * 	New-style copyright removed
 * 	Daughter history merged
 * 	History inverted
 * 	File modification date section deleted
 * 	[1999/05/28  14:12:52  Terry_Cassidy]
 * 
 * $EndLog$
 */
/*
 * $OldLog: cma.template.h,v $
 * Revision 1.1.15.4  2001/07/23  20:04:18  Tom_Dahl
 * 	Use constants for cma_c_sched_ada_low and cma_c_sched_ada_rtb, so as
 * 	to not risk confusing them with POSIX policies.
 * 
 * Revision 1.1.16.4  2001/01/05  20:58:38  Peter_Portante
 * Merge Information:  Non-Visual Merge: User specified tree thdbl17
 *     User Revision:  thdbl18_br:1.1.16.3 Local Ancestor: n/a
 *    Merge Revision:  thdbl17_br:1.1.15.3
 *   Common Ancestor:  1.1.15.2
 * 
 * Revision 1.1.16.3  2000/11/03  20:14:18  Peter_Portante
 * Merge Information:  Non-Visual Merge: User specified tree yankeeos.nightly
 *     User Revision:  thdbl18_br:1.1.16.2 Local Ancestor: n/a
 *    Merge Revision:  yankeeos_nightly:1.1.26.2
 *   Common Ancestor:  1.1.16.2
 * 
 * Revision 1.1.15.3  2000/10/24  16:39:37  Mary_Sullivan
 * 	Since we're now adjusting the extern_model (and setting nostandard)
 * 	prior to inclusion of cma_config.h, we shouldn't base our decision
 * 	to do so on the value of CMA_ symbols defined in cma_config.h
 * 
 * Revision 1.1.26.2  2000/10/18  20:35:26  Peter_Portante
 * Merge Information:  Merge: tree thdbl18
 *     User Revision:  Peter_Portante_yk_br:1.1.23.1 Local Ancestor:1.1.16.1
 *    Merge Revision:  thdbl18_br:1.1.16.2
 *   Common Ancestor:  1.1.16.1
 * 	Fail any compilation without -threads.
 * 	[2000/08/02  19:30:58  Peter_Portante]
 * 
 * Revision 1.1.16.2  2000/10/07  17:54:39  Peter_Portante
 * Merge Information:  Non-Visual Merge: User specified tree thdbl17
 *     User Revision:  thdbl18_br:1.1.16.1 Local Ancestor: n/a
 *    Merge Revision:  thdbl17_br:1.1.15.2
 *   Common Ancestor:  1.1.15.1
 * 
 * Revision 1.1.15.2  2000/05/30  16:16:34  Mary_Sullivan
 * 	For VMS, save/adjust the extern model (for Alpha) and issue the
 * 	nostandard pragma (for VAX) before including cma_config.h, as that
 * 	header now assumes these are appropriately set.
 * 
 * Revision 1.1.16.1  2000/03/02  21:35:10  devbld_zko
 * 	Move from BL17 to BL18
 * 
 * Revision 1.1.15.1  2000/03/01  15:44:09  Peter_Portante
 * 	Adding BL16 version to BL17
 * 
 * Revision 1.1.9.1  1999/11/03  05:04:06  Peter_Portante
 * 	Move to thdbl16
 * 
 * Revision 1.1.4.3  1999/05/28  14:15:11  Terry_Cassidy
 * 	Initial CMS version
 * 	New-style copyright removed
 * 	Daughter history merged
 * 	History inverted
 * 	File modification date section deleted
 * 	[1999/05/28  14:12:52  Terry_Cassidy]
 * 
 * $EndLog$
 */
/*
 * $OldLog: cma.template.h,v $
 * 	140	Paul Clark	16 May 1995
 * 		Removed includes of the following superfluous headers:
 * 	139	Paul Clark	15 May 1995
 * 		A bunch of exception names that used to be declared in
 * 		EXC_HANDLING.H were removed from that header for purposes
 * 		of setting up the new CORE domain build.  Now CMA.H will
 * 		declare those names.
 * 	138	Webb Scales	10 February 1995
 * 		Fix cma_t_call_routine type to return cma_t_address.
 * 	137	Webb Scales	 9 February 1995
 * 		Fix pointer size for TSD pointer in TEB.
 * 	136	Richard Love	13 December 1994
 * 		Remove the #ifdef of WIN32 for inclusion of short filename
 * 		versions of include files, obsoletes cma_conf.h and exc_hand.h.
 * 	135	Dave Butenhof	18 November 1994
 * 		Fix cma_t_longnatural (non-EVMS) to be cma_t_natural. It was
 * 		"unsigned int" which is wrong on OSF/1.
 * 	134	Dave Butenhof	 7 October 1994
 * 		Add get/set name functions
 * 	133	Dave Butenhof & Webb Scales	 5 October 1994
 * 		Add architected TEB block to TCB to allow fast location of
 * 		critical environmental info. Including: stack limit, sequence
 * 		number, thread specific data, and OpenVMS AXP kernel thread
 * 		block pointer.
 * 	132	Brian Keane	1 September 1994
 * 		Temporarily removed _CMA_CALL_ from typedefs.  CLAXP compiler
 * 		has a bug (duly reported) which causes it to reject the
 * 		syntax in a typedef.
 * 	131	Brian Keane	29 August 1994
 * 		Incorporate 24 August 1994 review comments
 * 	130	Brian Keane	18 August 1994
 * 		Make the external test for "Windows NT" WIN32, not _MSDOS.
 * 		Add the _CMA_CALL_ macro to all routines for Windows NT.
 * 	129	Dave Butenhof	15 June 1994
 * 		Add cma_s_dbg_unimpl status for reporting that 'lock' can't
 * 		block a thread yet.
 * 	128	Dave Butenhof	10 June 1994
 * 		Back off 127 -- I can't make OpenVMS AXP cma$open_rtl work, so
 * 		forget it.
 * 	127	Dave Butenhof	 9 June 1994
 * 		Add optional format arguments to cma_debug_cmd so the command
 * 		can include vsprintf commands.
 * 	126	Dave Butenhof	 3 June 1994
 * 		Change cma_t_handle to two unsigned longwords rather than an
 * 		unsigned long and two shorts. The sequence number and type are
 * 		no longer "short", so any code (illegally) referencing these
 * 		fields would be broken anyway.
 * 	125	Dave Butenhof	27 May 1994
 * 		Make cma_t_key unsigned -- it makes it easier to check against
 * 		array bounds (no need to check for < 0).
 * 	124	Brian Keane	20 April 1994
 * 		Add cma_thread_bind_to_cpu().
 * 	123	Brian Keane	7 April 1994
 * 		Re-adjust priority ranges to remove binary incompatabilities.
 * 	122	Brian Keane	21 March 1994
 * 		Remove trailing comma from enum.  It perplexes C++.
 * 	121	Dave Butenhof	22 February 1994
 * 		While I'm thinking about it, change _DECTHREADS_ to something
 * 		that approximates the DECthreads version, rather than a
 * 		modification date.
 * 	120	Dave Butenhof	10 December 1993
 * 		Change prototype for cma_debug_cmd, and add definition of
 * 		status codes it may return.
 * 	119	Webb Scales	 8 December 1993
 * 		Change exit-status, scheduling-inheritance, and detachstate
 * 		constants to enums.
 * 	118	Dave Butenhof	 6 December 1993
 * 		Add detach_state routines & constants
 * 	117	Webb Scales	 2 December 1993
 * 		Integrate code review comments
 * 	116	Webb Scales	23 November 1993
 * 		In keeping with the practice of screwing with the module just
 * 		before code review...
 * 		 - Add define for NT
 * 	115	Dave Butenhof	22 November 1993
 * 		This is kinda getting a jump on the code review scheduled for
 * 		next week. Remove hooks for per-object metering that I ended
 * 		up not using (but accidentally checked in), and also fix the
 * 		numbering sequence in this file.
 * 	114	Brian Keane	18 November 1993
 * 		Restrict use of pragma __extern_model to VMS - some
 * 		DEC C-based compilers on OSF give warnings about it.
 * 	113	Brian Keane	9 November 1993
 * 		Integrate additions from NT port.
 * 	112	Dave Butenhof	17 September 1993
 * 		Add a "metered" mutex type.
 * 	111	Dave Butenhof	 9 September 1993
 * 		Don't include cma_sigwait.h on VMS platforms (it's not
 * 		implemented anyway, and sigset_t definition conflicts with
 * 		VMS POSIX V2.0).
 * 	110	Paul Curtin	16 July 1993
 * 		Initial additions for NT port.
 * 	109	Dave Butenhof	 7 May 1993
 * 		Change typedef of cma_t_errno from cma_t_integer (which is
 * 		now "long") to "int", so it won't conflict with old-fashioned
 * 		"extern int errno;" in errno.h.
 * 	108	Dave Butenhof	26 April 1993
 * 		Include cma_config.h before exc_handling.h, so latter can
 * 		use the constants.
 * 	107	Dave Butenhof	 4 March 1993
 * 		Webb's complained about making ada_low & ada_rtb overlap
 * 		with fifo & rr for OSF/1 RT -- since they're really "low
 * 		priority" versions of fifo & rr. OK, I'm convinced: I'm
 * 		lowering them to the background range.
 * 	106	Dave Butenhof	29 January 1993
 * 		Peter Hunt (NaC) pointed out that DEC OSF/1 BL11 cma.h can
 * 		screw up some applications by defining _POSIX_4SOURCE and
 * 		_OSF_SOURCE before including unistd.h. The header defines
 * 		ALL of the "standards" symbols if none are defined, but if
 * 		any are already defined, it doesn't add any. Change to pull
 * 		in unistd.h FIRST, with whatever symbols the application has
 * 		defined -- then add the ones we actually need if it didn't
 * 		before including sched.h. That'll minimize the impact on
 * 		application code.
 * 	105	Dave Butenhof	25 January 1993
 * 		Use #ifndef for _POSIX_4SOURCE and _OSF_SOURCE, in case code
 * 		has already #included standards.h on DEC OSF/1.
 * 	104	Dave Butenhof	21 January 1993
 * 		Modify DEC OSF/1 RT priority ranges to allow for pending
 * 		change to privilege rules.
 * 	103	Webb Scales	15 January 1993
 * 		Add #pragmas to restore extern model for DEC C and standards 
 * 		checks for VAX C (both are set in cma_config.h)
 * 	102	Dave Butenhof	 4 January 1993
 * 		Add "#ifdef __cplusplus" stuff
 * 	101	Dave Butenhof	11 December 1992
 * 		Include unistd.h on OSF/1 even without RT support.
 * 	100	Dave Butenhof	 7 December 1992
 * 		After I started 100, I cut the range from 1/2 of RT priority
 * 		range for each policy (32 priorities) down to 1/4, to avoid
 * 		breaking ccvb_thd_009 which has a fixed-size array for each
 * 		policy/priority combination. DEC OSF/1 signals are handled by
 * 		a special kernel thread that runs at POSIX prio 42, so any
 * 		priority above that has trouble. So, the "low end" policies
 * 		will now range from 0 - 7, and the high end from 8 - 40. Under
 * 		_CMA_RT4_KTHREAD_, we'll allow setting priorities up to 64
 * 		for RR and FIFO (even though it's above fifo_max).
 * 	099	Dave Butenhof	25 November 1992
 * 		Changed ADA_LOW policy to use DEC OSF/1 RT 'SCHED_RR' with
 * 		the low half of the actual priority range, and ADA_RTB to do
 * 		the same with SCHED_FIFO.
 * 	098	Dave Butenhof	20 November 1992
 * 		All 'int' types should generally be based on cma_t_integer or
 * 		cma_t_natural, to get alignment advantages of 'long' on 64
 * 		bit architecture.
 * 	097	Dave Butenhof	16 October 1992
 * 		Include unistd.h along with sched.h, so we use the "standard"
 * 		OSF/1 definitions for P1002.4a symbols and don't generate
 * 		warnings by overriding them with our own.
 * 	096	Dave Butenhof	 8 October 1992
 * 		Change the comment about _POSIX_4SOURCE -- I forgot to update
 * 		it when I did 096.
 * 	095	Dave Butenhof	 6 October 1992
 * 		Possible workaround for sched.h? Define _OSF_SOURCE & friends
 * 		manually (which standards.h doesn't do because _POSIX_4SOURCE
 * 		is defined).
 * 	094	Dave Butenhof	 2 October 1992
 * 		Change the cma_c_pri* constants into externs for
 * 		_CMA_RT4_KTHREAD_ builds, since we need to call functions in
 * 		the kernel (which may not even exist if the RT option isn't
 * 		configured).
 * 	093	Webb Scales	23 September 1992
 * 		Add the "ada-rtb" scheduling policy.
 * 	092	Dave Butenhof	17 September 1992
 * 		OK, so I screwed 092... let's try again.
 * 	091	Dave Butenhof	16 September 1992
 * 		Yeah, and it's got terrible effects on lots of other things,
 * 		too. _POSIX_4SOURCE grants access to 1003.4 definitions; but
 * 		also seems to declare a "strictly conforming" application;
 * 		non-POSIX stuff (e.g., sigcontext) isn't defined. This isn't
 * 		acceptable for DECthreads. So I'm going to pull the pieces
 * 		of sched.h that I really need and bundle them in cma.h. Gross!
 * 	090	Dave Butenhof	15 September 1992
 * 		Defining _POSIX_4SOURCE seems to have bad effects on signal.h;
 * 		so #undef it right away after sched.h
 * 	089	Dave Butenhof	15 September 1992
 * 		Define _POSIX_4SOURCE before including sched.h, so that latter
 * 		will define the P1003.4 SCHED_* constants that we want.
 * 	088	Dave Butenhof	04 September 1992
 * 		Change definition of scheduling symbols to conform to the
 * 		system POSIX 1003.4 definitions if possible.
 * 	087	Webb Scales	27 August 1992
 * 		Added cma_cond_signal_preempt_int.
 * 	086	Dave Butenhof	09 July 1992
 * 		Change cmalib_crtlx.h to cma_crtlx.h
 * 	085	Brian Keane	14 June 1992
 * 		Change cma_t_integer and cma_t_natural to be
 * 		long/unsigned long, ensuring a 64 bit quantity on Alpha OSF/1.
 * 	084	Paul Curtin	14 April 1992
 * 		Add _CMA_SUPPRESS_EXTERNALS_ around cma_c_null & cma_g_debug
 * 	083	Dave Butenhof	10 March 1992
 * 		Integrate Aron Insinga's C++ changes.
 * 	082	Dave Butenhof	10 March 1992
 * 		Change cma_t_date_time from 'timeb' (which is BSD-only) to
 * 		'timeval', which is common. Note that 'timeval' is a smaller
 * 		structure, so existing object code won't be broken!
 * 	081	Dave Butenhof	04 March 1992
 * 		Change cma_t_thread to reflect actual fields of handle, so
 * 		that cma_thread_get_unique() can find sequence number without
 * 		knowing endianness of the machine.
 * 	080	Paul Curtin	26 February 1992
 * 		Remove include of cma_errno.h on VMS.
 * 	079	Dave Butenhof	07 January 1992
 * 		Move edit comments from external header files into separate
 * 		.h-edits files.
 * 	078	Dave Butenhof	03 December 1991
 * 		Fix test for cma_config.h to check for __vms as well as vms
 * 		(to work with DEC C /standard=ansi).
 * 	077	Dave Butenhof	19 November 1991
 * 		Remove use of _POSIX_REENTRANT_FUNCTIONS, since it breaks the
 * 		capability to build without libc_r.a on OSF/1 for code that
 * 		also includes unistd.h.
 * 	076	Dave Butenhof	29 October 1991
 * 		Make the cxxl_unused_handle variable static (this is a hack
 * 		for the "cfront" C++ preprocessor, to ensure that handle
 * 		typedefs are written to the C intermediate file).
 * 	075	Dave Butenhof	04 October 1991
 * 		Move a few files into "dce/" for non-VMS. Also fix
 * 		uniprocessor conditionals.
 * 	074	Dave Butenhof	18 September 1991
 * 		Integrate HP CMA5 reverse drop.
 * 	073	Dave Butenhof	10 June 1991
 * 		Create cma_thread_get_unique
 * 	072	Dave Butenhof	05 June 1991
 * 		On non-VMS DCE platforms, public header files (except
 * 		pthread.h and pthread_exc.h) are in /usr/include/dce.
 * 	071	Dave Butenhof	23 May 1991
 * 		Include cma_ux.h and cma_px.h headers on MP system, so we get
 * 		a few of the wrappers.
 * 	070	Dave Butenhof	12 April 1991
 * 		Don't include the DECthreads "hack" support for
 * 		thread-synchronous I/O and per-thread errno if this is an
 * 		OSF/1 based system, since the standard system versions
 * 		provide the necessary support.
 * 	069	Dave Butenhof	05 April 1991
 * 		CFRONT fix from Aron Insinga.
 * 	068	Dave Butenhof	25 March 1991
 * 		Include exc_handling.h rather than cma_exception.h, and move
 * 		all the exception definitions into exc_handling.h.
 * 	067	Dave Butenhof	18 March 1991
 * 		Add an external variable cma_g_debug which points to the
 * 		debugger code, so that users can always call through it (this
 * 		is mostly necessary under the VAX/VMS Debugger, which refuses
 * 		to look at function names from a shareable image).
 * 	066	Webb Scales	19 February 1991
 * 		Added symbol which users can test to see if the threading
 * 		package is us (especially important for the pthreads interface)
 * 	065	Dave Butenhof	14 February 1991
 * 		Integrate Aron Insinga's changes to improve compatibility
 * 		with non-default C/C++ compilers.
 * 	064	Dave Butenhof	12 February 1991
 * 		Change "friendly" mutex to "recursive"
 * 	063	Dave Butenhof	7 February 1991
 * 		New alert control scoping primitives.
 * 	062	Paul Curtin	31 January 1991
 * 		Added user header files; conditionally removed
 * 		on defining _CMA_NOWRAPPERS_  (for CMA build, ...)
 * 	061	Dave Butenhof & Webb Scales	21 January 1991
 * 		Figure out new exception prefixes (change low-level
 * 		exceptions to "exc" prefix).
 * 	060	Dave Butenhof	27 December 1990
 * 		Rearrange and rename some exceptions.
 * 	059	Webb Scales	15 October 1990
 * 		Removed "idle" scheduling policy.
 * 	058	Dave Butenhof	11 October 1990
 * 		Move errno stuff to it's own file, cma_errno.h.
 * 	057	Dave Butenhof	9 October 1990
 * 		Use new _CMA_IMPORT_ config symbol for the exception and
 * 		cma_c_null definitions.
 * 	056	Dave Butenhof	9 October 1990
 * 		Add argument to cma_t_init_routine and cma_once prototypes,
 * 		to accomodate enhancement to one-time initialization.
 * 	055	Bob Conti	1 October 1990
 * 		Delete cma_c_null_thread from exit_status
 * 	054	Webb Scales	17 September 1990
 * 		Added errno macro that sets up wrapper function.
 * 	053	Paul Curtin	17 September 1990
 * 		Added errno function
 * 	052	Webb Scales	31 August 1990
 * 		Added severity argument to CMA_STATUS macro
 * 	051	Dave Butenhof	27 August 1990
 * 		Change interfaces to pass handles & structures by reference.
 * 	050	Dave Butenhof	27 August 1990
 * 		Change name of Webb's "interrupt level signal" to
 * 		cma_cond_signal_int rather than more awkward
 * 		cma_cond_signal_interrupt (since he put the shorter form into
 * 		the transfer vector, and has used it in cmalib).
 * 	049	Webb Scales	15 August 1990
 * 		Made status code definitions platform-generic.
 * 	048	Dave Butenhof and Webb Scales	03 August 1990
 * 		Add prototype for cma_cond_signal_interrupt.
 * 	047	Dave Butenhof	26 June 1990
 * 		Add constants and functions for controlling whether mutex
 * 		locks can nest within a thread ("friendly mutexes").
 * 	046	Webb Scales	15 June 1990
 * 		Added scheduling policies for "Ada low" and "idle".
 * 	045	Dave Butenhof	13 June 1990
 * 		During initial MIPS ULTRIX migration, prototypes for the
 * 		"callback" routines (main thread, destructor, init) were
 * 		removed because they wouldn't compile.  They should have been
 * 		restored when conditional prototypes were implemented; do so
 * 		now.
 * 	044	Webb Scales	4 June 1990
 * 		Added more exceptions.
 * 	043	Webb Scales	2 May 1990
 * 		Changed the value of cma_c_true to a constant instead of an
 * 		expression, to accomodate the old (V1.3) MIPS/Ultrix compiler.
 * 	042	Dave Butenhof	18 April 1990
 * 		Remove conditionals around cma_c_null (now extern even on
 * 		VAX/VMS).
 * 	041	Webb Scales	16 April 1990
 * 		Added notcmastack exception
 * 	040	Webb Scales	20 March 1990
 * 		Added exceptions to support U*ix signal-to-exception mapping.
 * 	039	Dave Butenhof	28 February 1990
 * 		Ooops--we've got two "cma_c_sched_default" symbols.  Change
 * 		the inherit-sched one to "cma_c_sched_use_default".
 * 	038	Dave Butenhof	27 February 1990
 * 		Add priority argument to cma_attr_set_sched, since setting
 * 		policy and priority separately on an attributes object really
 * 		makes no more sense than setting them separately on a running
 * 		thread.  Also, "implement" the new symbols for scheduling
 * 		policies and priorities.
 * 	037	Dave Butenhof	15 February 1990
 * 		Correct oversight; add priority argument to
 * 		cma_thread_set_sched to conform to POSIX pthreads.
 * 	036	Dave Butenhof	8 February 1990
 * 		Recognize that (for now) cma_debug is a legitimate part of
 * 		the CMA reference implementation, and define it in the
 * 		interface.
 * 	035	Dave Butenhof	26 January 1990
 * 		Use new cma_config.h to define configuration symbols.
 * 	034	Dave Butenhof	23 January 1990
 * 		Add support for conditional use of function prototypes.
 * 	033	Bob Conti	11 December 1989
 * 		Remove cma_s_errimprep status code.
 * 		Add status code cma_s_inialrpro, for attempting to call 
 * 		cma_init while an initialization is in progress.
 * 	032	Bob Conti	11 December 1989
 * 		Added cma_s_errimprep status code.
 * 	031	Bob Conti	10 December 1989
 * 		Restored cma_e_uninitexc to this interface.  
 * 		(It can't hurt to be here *and* in CMA_EXCEPTION.h)
 * 	030	Bob Conti	9 December 1989
 * 		Added INCLUDE for CMA_EXCEPTIONS and moved the 
 * 		typedefs for exceptions into that package. 
 * 		Removed definitions for statuses that are never exceptions and
 * 		exception cma_e_uninitexc.
 * 	029	Webb Scales	8 December 1989
 * 		MIPS/Ultrix integration:  made "EXCEPTION.match_value" into a
 * 		union of "match.addr" and "match.value".
 * 	028	Dave Butenhof	8 December 1989
 * 		Add cma_s_unimp status code.
 * 	027	Bob Conti	8 December 1989
 * 		Add status codes corresponding to new conditions for
 * 		raising CMA exceptions.
 * 	026	Dave Butenhof	5 December 1989
 * 		Make some consistency changes to function names.
 * 	025	Dave Butenhof	30 November 1989
 * 		Name and argument order changes to track changes made to CMA
 * 		interface by POSIX 1003.4 threads working group.
 * 	024	Dave Butenhof	27 November 1989
 * 		Add cma_allocate_stack_np routine.
 * 	023	Webb Scales	26 October 1989
 * 		Add include of types.h for timeb.h
 * 	022	Dave Butenhof	24 October 1989
 * 		Make cma_t_date_time fields unsigned to correspond to internal
 * 		tick time.
 * 	021	Dave Butenhof	20 October 1989
 * 		Change conditional on cma_c_null definition: "globalref" on
 * 		vms (not on vaxc) and "extern" otherwise (even on VAX/ULTRIX
 * 		vcc).
 * 	020	Webb Scales	17 October 1989
 * 		MIPS/Ultrix integration:  removed argument prototypes from
 * 		routine-typedef declarations, and redefined cma_t_address for
 * 		MIPS platforms
 * 	019	Dave Butenhof	16 October 1989
 * 		cma_dcl_once incorrectly declares a "cma_once_block" instead
 * 		of a "cma_t_once_block".
 * 	018	Dave Butenhof	12 October 1989
 * 		Modify cma_t_once structure to follow internal definition.
 * 	017	Bob Conti 	05 October 1989
 * 		Add type cma_t_status and provide octal status values
 * 		for architecture-defined errors. Add exception for thread exit.
 * 	016	Hans Oser	03 October 1989
 * 		cma_c_null_thread added in cma_t_exit_status for null thread
 * 	015	Dave Butenhof	27 September 1989
 * 		Make cma_t_boolean an unsigned int (not a char) to improve
 * 		data structure alignment.
 * 	014	Dave Butenhof	14 September 1989
 * 		Change "state" field of cma_t_alert_state to be boolean.
 * 	013	Dave Butenhof	12 September 1989
 * 		Change cma_c_null (for VMS) to be globaldef.
 * 	012	Dave Butenhof	31 August 1989
 * 		Change back to match architecture: take input handles by
 * 		value, not by reference.
 * 	011	Dave Butenhof	30 August 1989
 * 		Change cma_c_true to "!cma_c_false" (conform to C convention
 * 		more explicitly).
 * 	010	Dave Butenhof	25 August 1989
 * 		Define stack operations (these are all suffixed with _np,
 * 		since they're not architecturally defined).
 * 	009	Dave Butenhof	25 August 1989
 * 		Fix handle (embed array in a structure to make argument
 * 		passing more consistent).
 * 	008	Dave Butenhof	16 August 1989
 * 		Add some constants for boolean and address types
 * 	007	Dave Butenhof	16 August 1989
 * 		More APA changes (argument passing)
 * 	006	Dave Butenhof	2 August 1989
 * 		Add MBZ field to once block for revision control.
 * 	005	Dave Butenhof	20 July 1989
 * 		Update to latest APA conventions, CMA style
 * 	004	Dave Butenhof	2 March 1989
 * 		IN Handles by value, fix routine types
 * 	003	Dave Butenhof	9 February 1989
 * 		Bring up to latest arch. spec
 * 	002	Dave Butenhof	7 November 1988
 * 		Clean up code and typedefs
 * 	001	Robert A. Conti	3 November 1988
 * 		Merge comments from Ada version
 * $EndLog$
 */
/*
 * @(#)$RCSfile: cma.template.h,v $ $Revision: 1.1.19.1 $ (DEC) $Date: 2003/09/12 19:07:56 $
 */
/*
 *  FACILITY:
 *
 *	Digital's Proprietary Interface to DECthreads (cma)
 *
 *	This interface is OBSOLETE. Although it will continue to be supported
 *	in the future, no new features will be added (including 64-bit
 *	pointer support for OpenVMS Alpha). In the future, documentation of
 *	this interface will be moved to an "obsolete features" appendix that
 *	may eventually be dropped from the distributed documentation set.
 *
 *	New development should not use this interface. Instead, refer to the
 *	Guide to DECthreads for information on the standard POSIX
 *	1003.1c-1995 interface, which uses the header file <pthread.h>.
 *
 *	In addition, it is usually relatively easy to migrate from the
 * 	proprietary cma interface to the open standard 1003.1c-1995 "pthread"
 *	interface -- the semantics are very similar.
 *
 *  ABSTRACT:
 *
 *	External definitions for the OBSOLETE cma interface to the
 *	DECthreads "core" services.
 *
 *  AUTHORS:
 *
 *	Dave Butenhof
 *
 *  CREATION DATE:
 *
 *	 2 November 1988
 *
 *  MODIFIED BY:
 *
 *	Dave Butenhof
 *	Paul Clark
 *	Bob Conti
 *	Paul Curtin
 *	Steve Johnson
 *	Brian Keane
 *	Hans Oser
 *	Peter Portante
 *	Webb Scales
 *	Ravi Chamarti
 *
 */

#ifndef CMA_INCLUDE
#define CMA_INCLUDE

#ifdef __cplusplus
    extern "C" {
#endif

#ifndef _DECTHREADS_
/*
 * Define a symbol which client code can test to determine the current
 * version of DECthreads.
 *
 * The DECthreads version is encoded in the numeric value of this symbol. The
 * version is normally in the form "Vvv.bb-ll" where "vv" represents the
 * major version, "bb" represents the baselevel (which increases continuously
 * regardless of version), and "ll" is a build level that increases in each
 * DECthreads project build within a baselevel.
 *
 * Higher numeric values are always more recent versions. So to check for
 * support of a feature that appeared in DECthreads V2.12-100, you could
 * check whether the symbol is > 212100.
 */
#define _DECTHREADS_ 320002
#endif

/*
 * The implementation makes these basic decisions.   On VMS, save and adjust
 * the extern_model (standard for VAXC) prior to including cma_config.h.
 */

#if defined (vms) || defined (__vms) || defined (VMS) || defined (__VMS) || defined (__vms__)
# if defined (__decc) || defined (__DECC) || (defined (__cplusplus) && defined (__DECCXX))
#  pragma __extern_model __save
#  pragma __extern_model __strict_refdef
# elif defined (vaxc) || defined (VAXC) || defined (__vaxc) || defined (__VAXC)
#  pragma nostandard
# endif
# include <cma_config.h>		/* configuration symbols */
# include <exc_handling.h>
#else
# include <dce/cma_config.h>
# include <dce/exc_handling.h>
#endif

#if _CMA_OSIMPL_ == _CMA__OS_OSF
/*
 * The Digital UNIX standards.h defines POSIX and OSF programming environment
 * symbols if none of the recognized symbols are already defined, but defines
 * no more if any are already defined. To retain as much as possible of the
 * application's desired environment, we'll include unistd.h first to get
 * whatever it thinks we need -- and then define what we really do need if it
 * didn't.
 */
# include <unistd.h>
# include <sched.h>
#endif

#if _CMA_OS_ == _CMA__UNIX
# include <sys/types.h>
# include <sys/time.h>
#endif

#if _CMA_PLATFORM_ == _CMA__ALPHA_VMS
# include <ints.h>
#endif

/*
 * Make sure we are included with _REENTRANT defined. This helps to catch
 * cases where the wrong per-thread errno value will be used.
 */
#if (_CMA_OSIMPL_ == _CMA__OS_OSF) && _CMA_REENTRANT_CLIB_
# ifndef _REENTRANT
#  error "Please compile the module including cma.h with -threads"
# endif
#endif

/*
 * Basic types
 */

typedef long		cma_t_integer;
typedef unsigned long	cma_t_natural;
typedef cma_t_natural	cma_t_boolean;
typedef float		cma_t_interval;
typedef int		cma_t_errno;
#if _CMA_VOID_
typedef void		*cma_t_address;
#else
typedef char		*cma_t_address;
#endif

#define cma_c_false	(cma_t_boolean)0
#define cma_c_true	(cma_t_boolean)1
#define cma_c_null_ptr	(cma_t_address)0


/*
 * If we're on a system with POSIX 1003.4 support, use the system symbols for
 * scheduling policy.
 */
#if _CMA_RT4_KTHREAD_
# define cma_c_sched_fifo	SCHED_FIFO
# define cma_c_sched_rr		SCHED_RR
# define cma_c_sched_throughput	SCHED_FG_NP
# define cma_c_sched_background	SCHED_BG_NP
# define cma_c_sched_ada_low	5
# define cma_c_sched_ada_rtb	6

/*
 * NOTE:
 *
 * On Digital UNIX, this header file retains the binary value of cma priority
 * symbols used prior to Digital UNIX 4.0. However, on earlier versions the
 * cma priorities mapped directly to kernel realtime priorities. In the new
 * version of DECthreads, all cma threads are "multiplexed" onto arbitrary
 * kernel threads in user mode, and cma priority has no real relationship to
 * the kernel priority at which the thread runs -- it controls only which
 * user thread the DECthreads core will select to run when a kernel thread
 * becomes available.
 */
# define cma_c_prio_fifo_max	21
# define cma_c_prio_fifo_mid	18
# define cma_c_prio_fifo_min	14
# define cma_c_prio_rr_max	22
# define cma_c_prio_rr_mid	19
# define cma_c_prio_rr_min	15
# define cma_c_prio_through_max	22
# define cma_c_prio_through_mid	19
# define cma_c_prio_through_min	15
# define cma_c_prio_back_max	13
# define cma_c_prio_back_mid	8
# define cma_c_prio_back_min	0
# define cma_c_prio_ada_low_max	13
# define cma_c_prio_ada_low_mid	8
# define cma_c_prio_ada_low_min	0
# define cma_c_prio_ada_rtb_max	13
# define cma_c_prio_ada_rtb_mid	8
# define cma_c_prio_ada_rtb_min	0
#else
# define cma_c_sched_fifo	0
# define cma_c_sched_rr		1
# define cma_c_sched_throughput	2
# define cma_c_sched_background	3
# define cma_c_sched_ada_low	4
# define cma_c_sched_ada_rtb	5

# define cma_c_prio_fifo_max	31
# define cma_c_prio_fifo_mid	((31+16)/2)
# define cma_c_prio_fifo_min	16
# define cma_c_prio_rr_max	cma_c_prio_fifo_max
# define cma_c_prio_rr_mid	cma_c_prio_fifo_mid
# define cma_c_prio_rr_min	cma_c_prio_fifo_min
# define cma_c_prio_through_max	15
# define cma_c_prio_through_mid	((15+8)/2)
# define cma_c_prio_through_min	8
# define cma_c_prio_back_max	7
# define cma_c_prio_back_mid	((7+0)/2)
# define cma_c_prio_back_min	0
# define cma_c_prio_ada_low_max	cma_c_prio_back_max
# define cma_c_prio_ada_low_mid	cma_c_prio_back_mid
# define cma_c_prio_ada_low_min	cma_c_prio_back_min
# define cma_c_prio_ada_rtb_max	cma_c_prio_ada_low_max
# define cma_c_prio_ada_rtb_mid	cma_c_prio_ada_low_mid
# define cma_c_prio_ada_rtb_min	cma_c_prio_ada_low_min
#endif

#define cma_c_sched_default	cma_c_sched_throughput
#define cma_c_sched_other	cma_c_sched_default

/*
 * Contention scope possible values
 */
#if _CMA_OS_ == _CMA__UNIX
#define cma_c_scope_process   0
#define cma_c_scope_system    1
#endif


/*
 * The implementation of the cma_t_date_time type should match the "native
 * time" of the platform: that allows clients to use the full set of platform
 * time operations, rather than just "cma_get_expiration", to compute and
 * test timed waits.
 *
 * This section assumes the platform is either "VMS" or "UNIX-ish".  Others
 * will require changes.
 */
#if _CMA_OS_ == _CMA__VMS
typedef struct CMA_T_DATE_TIME {
    unsigned long int	low;
    unsigned long int	high;
    }				cma_t_date_time;
#else
typedef struct timeval		cma_t_date_time;
#endif

/*
 * Handle type
 */

typedef struct CMA_T_HANDLE {
    cma_t_natural	field1;
    cma_t_natural	field2;
    } cma_t_handle;

#if (_CMA_COMPILER_ == _CMA__CFRONT) && (_CMA_OS_ == _CMA__VMS)
/*
 * The following declaration is a hack to support CFRONT (C++ preprocessor);
 * without an actual instance, the struct definition isn't written out.
 * Creates problems for VAX C when it compiles CFRONT output.
 */
static struct CMA_T_HANDLE	cxxl_unused_handle;
#endif

#define cma_c_handle_size sizeof(cma_t_handle)

/*
 * Predefined null handle
 */
#ifndef _CMA_SUPPRESS_EXTERNALS_
_CMA_IMPORT_ cma_t_handle	cma_c_null;
#endif

/*
 * One-time initialization control block and its initialization macro.
 *
 * Declare a one time initialization control block as:
 *
 *	static cma_t_once	block = cma_once_init;
 */
typedef struct CMA_T_ONCE {
    cma_t_integer	field1;
    cma_t_integer	field2;
    cma_t_integer	field3;
    }				cma_t_once;

#define cma_once_init	{0, 0, 0}

/*
 * Alert state structure
 */
typedef struct CMA_T_ALERT_STATE {
    cma_t_integer	state1;
    cma_t_integer	state2;
    }				cma_t_alert_state;

/*
 * Operations on Handles
 */

extern void _CMA_CALL_
cma_handle_assign (	/*  Assign one handle to another */
	cma_t_handle	*handle1,	/* Input handle */
	cma_t_handle	*handle2);	/* Output handle */

extern cma_t_boolean _CMA_CALL_
cma_handle_equal (	/* Compare two handles */
	cma_t_handle	*handle1,
	cma_t_handle	*handle2);

/*
 * Operations on attributes objects
 */

typedef cma_t_handle	cma_t_attr;

/*
 * An attributes object is created to specify the attributes of other CMA
 * objects that will be created.
 */

extern void _CMA_CALL_
cma_attr_create (
	cma_t_attr	*new_attr,
	cma_t_attr	*attr);

/*
 * An attributes object can be deleted when it is no longer needed.
 */

extern void _CMA_CALL_
cma_attr_delete (
	cma_t_attr	*attr);

/*
 * Operations on threads
 */

typedef cma_t_handle	cma_t_thread;
typedef cma_t_address	(*cma_t_start_routine) (cma_t_address arg);

typedef enum CMA_T_EXIT_STATUS {
    cma_c_term_error = 0,
    cma_c_term_normal = 1,
    cma_c_term_alert = 2
    }			cma_t_exit_status;

typedef enum CMA_T_SCHED_INHERIT {
    cma_c_sched_inherit = 0,
    cma_c_sched_use_default = 1
    }			cma_t_sched_inherit;

typedef enum CMA_T_DETACH_STATE {
    cma_c_create_joinable = 0,
    cma_c_create_detached = 1
    }			cma_t_detach_state;

/*
 * The following procedures can be used to control thread creation,
 * termination and deletion.
 */

/*
 * To create a thread object and runnable thread, a routine must be specified
 * as the new thread's start routine.  An argument may be passed to this
 * routine, as an untyped address; an untyped address may also be returned as
 * the routine's value.  An attributes object may be used to specify details
 * about the kind of thread being created.
 */
extern void _CMA_CALL_
cma_thread_create (
	cma_t_thread		*new_thread,
	cma_t_attr		*attr,
	cma_t_start_routine	start_routine,
	cma_t_address		arg);

/*
 * A thread object may be "detached" to specify that the return value and
 * completion status will not be requested.
 */
extern void _CMA_CALL_
cma_thread_detach (
	cma_t_thread	*thread);

/*
 * A thread may terminate it's own execution.
 */
extern void _CMA_CALL_
cma_thread_exit_error (void);

extern void _CMA_CALL_
cma_thread_exit_normal (
	cma_t_address	result);

/*
 * A thread can await termination of another thread and retrieve the return
 * value and completion status of the thread.
 */
extern void _CMA_CALL_
cma_thread_join (
	cma_t_thread		*thread,
	cma_t_exit_status	*exit_status,
	cma_t_address		*result);

/*
 * Operations to define thread creation attributes
 */

typedef	cma_t_integer		cma_t_priority;
typedef	cma_t_integer		cma_t_sched_policy;
#if _CMA_OS_ == _CMA__UNIX
typedef cma_t_integer		cma_t_scope;
#endif

/*
 * Set or obtain the default thread priority.
 */
extern void _CMA_CALL_
cma_attr_set_priority (
	cma_t_attr	*attr,
	cma_t_priority	pri);

extern void _CMA_CALL_
cma_attr_get_priority (
	cma_t_attr	*attr,
	cma_t_priority	*pri);

/*
 * Set or obtain the default scheduling algorithm
 */
extern void _CMA_CALL_
cma_attr_set_sched (
	cma_t_attr		*attr,
	cma_t_sched_policy	policy,
	cma_t_priority		priority);

extern void _CMA_CALL_
cma_attr_get_sched (
	cma_t_attr		*attr,
	cma_t_sched_policy	*policy);

/*
 * Set or obtain whether a thread will use the scheduling attributes set in
 * the attributes object or inherit them from the creating thread.  Note,
 * inheritance is the default.
 */
extern void _CMA_CALL_
cma_attr_set_inherit_sched (
	cma_t_attr		*attr,
	cma_t_sched_inherit	setting);

extern void _CMA_CALL_
cma_attr_get_inherit_sched (
	cma_t_attr		*attr,
	cma_t_sched_inherit	*setting);

/*
 * Set or obtain the default stack size
 */
extern void _CMA_CALL_
cma_attr_set_stacksize (
	cma_t_attr	*attr,
	cma_t_natural	stacksize);

extern void _CMA_CALL_
cma_attr_get_stacksize (
	cma_t_attr	*attr,
	cma_t_natural	*stacksize);

/*
 * Set or obtain the default guard size
 */
extern void _CMA_CALL_
cma_attr_set_guardsize (
	cma_t_attr	*attr,
	cma_t_natural	guardsize);

extern void _CMA_CALL_
cma_attr_get_guardsize (
	cma_t_attr	*attr,
	cma_t_natural	*guardsize);

/*
 * Set or obtain the default contention scope
 */
#if _CMA_OS_ == _CMA__UNIX
extern void _CMA_CALL_
cma_attr_set_scope (
	cma_t_attr	*attr,
	cma_t_scope	scope);

extern void _CMA_CALL_
cma_attr_get_scope (
	cma_t_attr	*attr,
	cma_t_scope	*scope);
#endif
/*
 * Set or obtain the create-already-detached attribute
 */
extern void _CMA_CALL_
cma_attr_get_detachstate (
	cma_t_attr		*att,
	cma_t_detach_state	*setting);

extern void _CMA_CALL_
cma_attr_set_detachstate (
	cma_t_attr		*att,
	cma_t_detach_state	setting);

/*
 * Thread Scheduling Operations
 */

/*
 * Set or obtain the priority of a thread.
 */
extern void _CMA_CALL_
cma_thread_get_priority (
	cma_t_thread	*thread,
	cma_t_priority	*priority);

extern void _CMA_CALL_
cma_thread_set_priority (
	cma_t_thread	*thread,
	cma_t_priority	priority);

/*
 * Set or obtain the scheduling algorithm of a thread.
 */
extern void _CMA_CALL_
cma_thread_get_sched (
	cma_t_thread		*thread,
	cma_t_sched_policy	*policy);

extern void _CMA_CALL_
cma_thread_set_sched (
	cma_t_thread		*thread,
	cma_t_sched_policy	policy,
	cma_t_priority		priority);

/*
 * A thread may tell the scheduler that its processor can be made available.
 */
extern void _CMA_CALL_
cma_yield (void);

/*
 * A thread may enter a wait state for a specified period of time.
 */
extern void _CMA_CALL_
cma_delay (
	cma_t_interval	interval);

/*
 * Bind a thread to a particular CPU on a multiprocessor system.
 */
extern void _CMA_CALL_
cma_thread_bind_to_cpu (
	cma_t_thread	*thread,
	long		cpu_mask);

/*
 * Thread Information Operations
 */

/*
 * A thread may obtain a copy of its own thread handle.
 */
extern void _CMA_CALL_
cma_thread_get_self (
	cma_t_thread	*thread);

/*
 * Get the sequence number of a thread.
 */
extern cma_t_natural _CMA_CALL_
cma_thread_get_unique (
	cma_t_thread	*thread);

/*
 * Operations on Mutexes
 */

typedef	cma_t_handle	cma_t_mutex;

typedef enum CMA_T_MUTEX_KIND {
    cma_c_mutex_fast = 0,
    cma_c_mutex_recursive = 1,
    cma_c_mutex_nonrecursive = 2
    }				cma_t_mutex_kind;

/*
 * Operations to define mutex creation attributes
 */

/*
 * Set or obtain whether mutex locks can nest.
 */
extern void _CMA_CALL_
cma_attr_set_mutex_kind (
	cma_t_attr		*attr,
	cma_t_mutex_kind	nest);

extern void _CMA_CALL_
cma_attr_get_mutex_kind (
	cma_t_attr		*attr,
	cma_t_mutex_kind	*nest);

/*
 * A thread can create and delete mutexes.
 */
extern void _CMA_CALL_
cma_mutex_create (
	cma_t_mutex	*new_mutex,
	cma_t_attr	*attr);

extern void _CMA_CALL_
cma_mutex_delete (
	cma_t_mutex	*mutex);

/*
 * A thread can lock or unlock a mutex.
 */
extern void _CMA_CALL_
cma_mutex_lock (
	cma_t_mutex	*mutex);

extern cma_t_boolean _CMA_CALL_
cma_mutex_try_lock (
	cma_t_mutex	*mutex);

extern void _CMA_CALL_
cma_mutex_unlock (
	cma_t_mutex	*mutex);

/*
 * A thread may synchronize access to external non-thread-safe code or data,
 * preventing conflict with threads created by other facilities, by using the
 * DECthreads "Global Lock".
 */
extern void _CMA_CALL_
cma_lock_global (void);

extern void _CMA_CALL_
cma_unlock_global (void);

/*
 * Operations on condition variables
 */

typedef cma_t_handle	cma_t_cond;

/*
 * A thread can create and delete condition variables.
 */
extern void _CMA_CALL_
cma_cond_create (
	cma_t_cond	*new_condition,
	cma_t_attr	*attr);

extern void _CMA_CALL_
cma_cond_delete (
	cma_t_cond	*condition);

/*
 * A thread can signal to and broadcast on a condition variable.
 */
extern void _CMA_CALL_
cma_cond_broadcast (
	cma_t_cond	*condition);

extern void _CMA_CALL_
cma_cond_signal (
	cma_t_cond	*condition);

extern void _CMA_CALL_
cma_cond_signal_int (
	cma_t_cond	*condition);

extern void _CMA_CALL_
cma_cond_signal_preempt_int (
#if _CMA_OS_ == _CMA__UNIX
	cma_t_cond	*condition,
	cma_t_address	scp
#else
	cma_t_cond	*condition
#endif
	);

/*
 * A thread can wait for a condition variable to be signalled or broadcast.
 */
extern void _CMA_CALL_
cma_cond_wait (
	cma_t_cond	*condition,
	cma_t_mutex	*mutex);

/*
 * Operations for timed waiting
 */

typedef cma_t_integer		cma_t_status;

/*
 * A thread can perform a timed wait on a condition variable.
 */
extern cma_t_status _CMA_CALL_
cma_cond_timed_wait (
	cma_t_cond	*condition,
	cma_t_mutex	*mutex,
	cma_t_date_time	*expiration);

/*
 * A thread may perform some operations on absolute date-time and intervals.
 */

extern void _CMA_CALL_
cma_time_get_expiration (
	cma_t_date_time	*expiration,
	cma_t_interval	interval);

/*
 * Operations for DECthreads and client initialization.
 */

/*
 * Initialize the DECthreads facility. (Use of this routine is not required
 * on OpenVMS, Digital UNIX or Windows NT.)
 */
extern void _CMA_CALL_
cma_init (void);

/*
 * A thread can declare a one-time initialization routine.  The address of
 * the init block and routine are passed as parameters.
 */

typedef void	(*cma_t_init_routine) (cma_t_address arg);

extern void _CMA_CALL_
cma_once (
	cma_t_once		*init_block,
	cma_t_init_routine	init_routine,
	cma_t_address		arg);

/*
 * Operations for per-thread context
 */

typedef	cma_t_natural	cma_t_key;

typedef void		(*cma_t_destructor) (cma_t_address ctx_value);

/*
 * A unique per-thread context key can be obtained for the process
 */
extern void _CMA_CALL_
cma_key_create (
	cma_t_key		*key,
	cma_t_attr		*attr,
	cma_t_destructor	destructor);

/*
 * A thread can set a per-thread context value identified by a key.
 */
extern void _CMA_CALL_
cma_key_set_context (
	cma_t_key	key,
	cma_t_address	context_value);

/*
 * A thread can retrieve a per-thread context value identified by a key.
 */
extern void _CMA_CALL_
cma_key_get_context (
	cma_t_key	key,
	cma_t_address	*context_value);

/*
 * Operations for alerts.
 */

/*
 * The current thread can request that a thread terminate.
 */

extern void _CMA_CALL_
cma_thread_alert (
	cma_t_thread	*thread);

/*
 * The current thread can poll for alert delivery.
 */
extern void _CMA_CALL_
cma_alert_test (void);

/*
 * The current thread can disable asynchronous alert delivery, restore the
 * previous state of asynchronous alert delivery, or enable asynchronous
 * alert delivery.
 */
extern void _CMA_CALL_
cma_alert_disable_asynch (
	cma_t_alert_state	*prior);

extern void _CMA_CALL_
cma_alert_disable_general (
	cma_t_alert_state	*prior);

extern void _CMA_CALL_
cma_alert_enable_asynch (void);

extern void _CMA_CALL_
cma_alert_enable_general (
	cma_t_alert_state	*prior);

extern void _CMA_CALL_
cma_alert_restore (
	cma_t_alert_state	*prior);

/*
 * A thread may check to see if there is sufficient space on its current stack
 */
extern cma_t_boolean _CMA_CALL_
cma_stack_check_limit_np (
	cma_t_integer	size);

/*
 * Debug threads
 */
extern void _CMA_CALL_
cma_debug (void);

/*
 * The cma_debug_cmd() function returns the status of the last specified
 * operation in the command string.
 */
typedef enum CMA_T_DBG_STATUS {
    cma_s_dbg_success = 0,		/* Command was successful */
    cma_s_dbg_quit = 1,			/* Last command was 'quit' or 'exit' */
    cma_s_dbg_nonesel = 2,		/* No objects selected (e.g., "thread -br") */
    cma_s_dbg_successpend = 3,		/* Alternate success */
    cma_s_dbg_nopriv = -1,		/* No privilege for command */
    cma_s_dbg_invparam = -2,		/* Invalid parameter on command */
    cma_s_dbg_invseq = -3,		/* Invalid object sequence number given */
    cma_s_dbg_inconstate = -4,		/* Inconsistent state for operation */
    cma_s_dbg_corrupt = -5,		/* Unable to complete; internal corruption */
    cma_s_dbg_invoption = -6,		/* Invalid command options */
    cma_s_dbg_noarg = -7,		/* Missing command argument */
    cma_s_dbg_invaddr = -8,		/* Invalid address */
    cma_s_dbg_invcmd = -9,		/* Invalid command */
    cma_s_dbg_nullcmd = -10,		/* No command given */
    cma_s_dbg_conflict = -11,		/* Conflicting options */
    cma_s_dbg_unimpl = -12		/* Unimplemented feature */
    } cma_t_dbg_status;

/*
 * Pass a command string to DECthreads debug for interpretation. The
 * argument is a "char *" command string.
 */
extern cma_t_dbg_status _CMA_CALL_
cma_debug_cmd (char *cmd);

/*
 * Restore extern_model or standard environment, adjusted prior to
 * inclusion of cma_config.h.
 */
#if _CMA_OS_ == _CMA__VMS
# if ((_CMA_COMPILER_ == _CMA__DECC) || (_CMA_COMPILER_ == _CMA__DECCPLUS))
#  pragma __extern_model __restore
# elif _CMA_COMPILER_ == _CMA__VAXC
#  pragma standard
# endif
#endif

#ifdef __cplusplus
    }
#endif

#endif
