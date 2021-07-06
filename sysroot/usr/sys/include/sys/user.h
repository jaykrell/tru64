/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: user.h,v $
 * Revision 4.3.186.5  2006/03/03  17:33:04  Larry_Scott
 * 	Use one of the np_uthread spare fields for uu_vno_resv, fifo in
 * 	process of getting open'ed.  QAR 19389.
 *
 * Revision 4.3.186.4  2003/12/09  20:23:35  Jason_Hennessey
 * 	Add struct for uprintf_safe(). Case BCSMP01GD
 * 	[2003/12/08  22:35:58  Jason_Hennessey]
 *
 * Revision 4.3.186.3  2003/06/19  13:26:38  Matthew_McGrath
 * 	Add UL_COMMENT, new utask members for per-binary tunables.
 *
 * Revision 4.3.186.2  2003/01/06  20:29:12  Matthew_McGrath
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree v51bsupportos
 *     User Revision:  Matthew_McGrath_execdata_br:4.3.189.1 Local Ancestor:4.3.165.5
 *    Merge Revision:  v51bsupportos_br:4.3.186.1
 *   Common Ancestor:  4.3.165.5
 * 	[2003/01/06  19:23:59  Matthew_McGrath]
 *
 * 	Add the UL_WXALLOW flag to the load flags.  [QAR 94136]
 * 	[2002/12/18  21:40:30  Matthew_McGrath]
 *
 * Revision 4.3.186.1  2002/10/09  17:13:09  Kevin_Harty
 *      Add close_task_files_nofree for exit-fuser interaction.
 *      v51asupportos-705-scott
 * 
 * Revision 4.3.165.5  2002/02/01  15:43:27  Curry_Bartlett
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree wcalphaos
 *     User Revision:  Curry_Bartlett_wc_dir_aud_br:4.3.169.3 Local Ancestor:4.3.165.3
 *    Merge Revision:  wcalphaos_br:4.3.165.4
 *   Common Ancestor:  4.3.165.3
 * 	[2002/02/01  00:42:06  Curry_Bartlett]
 * 	added support for parent dir infor for file obj audit
 * 	[2002/01/31  18:37:58  Curry_Bartlett]
 * 
 * Revision 4.3.165.4  2002/01/29  20:33:33  Mark_Dewandel
 * 	Add u.uu_radset to support RAD attach/bind operations to more
 * 	than one RAD.  Keeping a per-thread RAD set simplifies RAD set
 * 	creation when holding simple locks (i.e., radsetinit() does not
 * 	call malloc()).
 * 
 * Revision 4.3.165.3  2001/10/03  17:44:09  David_Bernardo
 * 	Added per-process bigpage attributes to utask structure.
 * 
 * Revision 4.3.165.2  2001/10/01  18:34:27  Curry_Bartlett
 * 	Added comment which points to definition of audit related symbols
 * 
 * Revision 4.3.165.1  2001/09/21  13:16:45  James_Woodward
 * 	Separate socket select and devpoll ofile table usage.
 * 	Create the routine close_task_files() to be used by
 * 	exit() and procdup() for cleaning up the open file
 * 	table of a task.
 * 	Changes to support devpoll.
 * 
 * Revision 4.3.151.3  2001/05/03  11:03:40  James_Woodward
 * 	Add function prototype for getf_by_remote_task().
 * 
 * Revision 4.3.151.2  2000/11/03  15:56:17  Per_Wahlstrom
 * 	uu_copyinctl->uu_copyio_ctl. Define u_copyio_ctl
 * 
 * Revision 4.3.151.1  2000/10/24  23:54:25  Ernie_Petrides
 * 	Merge v51supportos-23-stuarth from Zulu PK2 revision 4.3.144.1.
 * 
 * Revision 4.3.144.1  2000/09/18  17:17:41  Stuart_Hollander
 * 	Check for null uf_of_entry in U_GET_FE QAR82347 (fix by woodward).
 * 
 * Revision 4.3.110.14  2000/07/10  18:27:07  Mark_Dewandel
 * 	Add U_ADDR_{UN,}LOCK_ALWAYS_PROC() macros to support atomic
 * 	idhash[] list and ucred modifications.
 * 
 * Revision 4.3.110.13  2000/01/04  15:57:39  Anton_Verhulst
 * 	merge from zinc bl3
 * 
 * Revision 4.3.110.12  1999/11/05  20:18:54  John_H_Williams
 * 	Syncing to wave4zincos.bl2
 * 
 * Revision 4.3.110.11  1999/11/03  18:46:01  Dean_Gagne
 * 	QAR 74267 part 2. UL_ALL_FUTURE flag is set and cleared, but never used.
 * 	Remove definition and all setting and clearing of this flag.
 * 
 * Revision 4.3.134.3  1999/11/03  11:56:11  James_Woodward
 * 	add support for per-task core file directory support.
 * 
 * Revision 4.3.110.10  1999/10/08  20:51:53  Kevin_Harty
 * 	Change macro used to access CFS thread-specific data from
 * 	CFS_INFS to CFS_SENT_INFO.
 * 
 * Revision 4.3.110.9  1999/09/17  12:55:56  Mark_Dewandel
 * 	Added U_ADDR_{UN,}LOCK_ALWAYS() macros to provide unconditional
 * 	u_addr_lock operations.
 * 
 * Revision 4.3.110.8  1999/07/14  19:45:31  James_Woodward
 * 	remove u_mad from thread structure and use u_rad pointer.
 * 	[1999/07/12  18:48:16  James_Woodward]
 * 
 * Revision 4.3.110.7  1999/06/21  14:05:28  James_Woodward
 * 	add rad.h and rad structure
 * 	[1999/06/17  12:19:40  James_Woodward]
 * 
 * Revision 4.3.110.6  1999/05/06  19:11:13  James_Woodward
 * 	steel bl23 pass 3 merge
 * 	[1999/05/06  18:37:00  James_Woodward]
 * 
 * Revision 4.3.55.25  1999/03/23  18:43:51  Mark_Dewandel
 * 	Added TSD_CFS_KEY and bumped TSD_FIRST_AVAIL_KEY to replace NINFS
 * 	and uu_infs[].  Added convenience macro CFS_INFS to reference
 * 	reserved uu_tsd[] slot for CFS.
 * 	[1999/03/23  13:08:25  Mark_Dewandel]
 * 
 * Revision 4.3.55.24  1999/03/19  20:06:36  Ernie_Petrides
 * 	Reorganize the utask and np_uthread structures to improve
 * 	cache line locality and restore the size of the uthread
 * 	structure to 768 bytes (should remain a multiple of 64).
 * 	[1999/03/19  05:03:41  Ernie_Petrides]
 * 
 * Revision 4.3.110.5  1999/03/09  13:13:53  James_Woodward
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jSTEELOS_BL20:STEELOS_BL21 **
 * 		** Ancestor revision:	4.3.55.15 **
 * 		** Merge revision:	4.3.55.20 **
 * 	 	** End **
 * 	[1999/03/09  13:08:23  James_Woodward]
 * 
 * Revision 4.3.55.23  1999/02/10  21:29:04  Mark_Dewandel
 * 	Remove uu_unix_lock.
 * 	[1999/02/09  14:32:53  Mark_Dewandel]
 * 
 * Revision 4.3.55.22  1999/02/09  19:03:59  Ken_Block
 * 	Make C++ Compliant.
 * 	[1999/01/26  22:58:39  Ken_Block]
 * 
 * Revision 4.3.55.21  1999/02/02  19:48:08  Shashi_Mangalat
 * 	Add uu_mad for NUMA.
 * 	[1999/02/01  15:10:43  Shashi_Mangalat]
 * 
 * Revision 4.3.55.20  1998/12/23  22:30:37  Diane_Lebel
 * 	Incorporate wave 4 changes.
 * 	[1998/12/22  21:29:19  Diane_Lebel]
 * 
 * Revision 4.3.110.4  1998/12/08  17:53:05  James_Woodward
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jSTEELOS_BL18:STEELOS_BL20 **
 * 		** Ancestor revision:	4.3.55.13 **
 * 		** Merge revision:	4.3.55.15 **
 * 	 	** End **
 * 	[1998/12/08  17:30:22  James_Woodward]
 * 
 * Revision 4.3.55.19  1998/12/04  16:39:16  Anton_Verhulst
 * 	Changes to allow upto 64 charater login names.
 * 	[1998/12/04  16:27:31  Anton_Verhulst]
 * 
 * Revision 4.3.55.18  1998/12/04  16:14:19  Anton_Verhulst
 * 	u_spec is now a pointer. Space gets malloc'ed on demand.
 * 	[1998/12/04  15:57:19  Anton_Verhulst]
 * 
 * Revision 4.3.55.17  1998/12/04  11:40:33  James_Woodward
 * 	U_FE_LOCK/U_FE_UNLOCK changed to have one argument for all calls
 * 	[1998/12/03  21:38:30  James_Woodward]
 * 
 * Revision 4.3.55.16  1998/12/01  20:07:13  James_Woodward
 * 	break up task open file table lock
 * 	[1998/11/25  19:30:57  James_Woodward]
 * 
 * Revision 4.3.114.3  1998/10/12  20:26:39  Geoff_Steckel
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rSTEELOS_BL19 **
 * 		** Ancestor revision:	4.3.55.13 **
 * 		** Merge revision:	4.3.55.15 **
 * 	 	** End **
 * 	[1998/10/12  19:05:52  Geoff_Steckel]
 * 
 * Revision 4.3.110.3  1998/09/25  20:52:55  James_Woodward
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jSTEELOS_BL16:STEELOS_BL18 **
 * 		** Ancestor revision:	4.3.55.12 **
 * 		** Merge revision:	4.3.55.13 **
 * 	 	** End **
 * 	[1998/09/25  20:21:14  James_Woodward]
 * 
 * Revision 4.3.114.2  1998/09/24  23:42:13  Geoff_Steckel
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	4.3.55.12 **
 * 		** Merge revision:	4.3.114.1 **
 * 	 	** End **
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rTCR4OS_NIGHTLY0 **
 * 		** Ancestor revision:	4.3.55.11 **
 * 		** Merge revision:	4.3.55.12 **
 * 	 	** End **
 * 	[1998/09/24  23:22:56  Geoff_Steckel]
 * 	add recursive FS reference list
 * 	[1998/07/13  17:11:47  Geoff_Steckel]
 * 
 * Revision 4.3.55.15  1998/09/03  11:08:00  James_Woodward
 * 	cache align field is uthread structure and add cpu_number to uthread
 * 	[1998/09/01  11:47:51  James_Woodward]
 * 
 * Revision 4.3.110.2  1998/08/26  12:41:41  James_Woodward
 * 	Merge of numaproj and zulu
 * 	[1998/07/29  20:17:22  James_Woodward]
 * 
 * Revision 4.3.55.14  1998/08/24  20:47:03  Ken_Block
 * 	Add forward struct decls to make pre-ansi C++ happy.
 * 	[1998/08/24  14:59:38  Ken_Block]
 * 
 * Revision 4.3.103.3  1998/07/22  13:13:31  James_Woodward
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rSTEELOS_BL16 **
 * 		** Ancestor revision:	4.3.55.11 **
 * 		** Merge revision:	4.3.55.12 **
 * 	 	** End **
 * 	[1998/07/22  13:12:49  James_Woodward]
 * 
 * Revision 4.3.55.13  1998/05/11  17:57:35  Stuart_Hollander
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL14:PTEV6OS_BL4 **
 * 		** Ancestor revision:	4.3.63.6 **
 * 		** Merge revision:	4.3.95.3 **
 * 	 	** End **
 * 	[1998/05/11  17:47:24  Stuart_Hollander]
 * 
 * Revision 4.3.103.2  1998/04/20  21:45:40  Shashi_Mangalat
 * 	Add uu_mad to uthread to determine current memory allocation policy.
 * 	[1998/04/20  21:32:14  Shashi_Mangalat]
 * 
 * Revision 4.3.55.12  1998/04/14  12:27:10  Mark_Dewandel
 * 	Removed uu_spare and its aliases and added uu_tsd array to
 * 	support registered per-thread data hooks.
 * 	[1998/04/03  21:30:27  Mark_Dewandel]
 * 
 * Revision 4.3.95.3  1998/03/27  18:27:45  James_Woodward
 * 	backport steel proc relation lock changes
 * 	[1998/03/25  14:35:56  James_Woodward]
 * 
 * Revision 4.3.95.2  1998/01/12  20:08:46  Andrew_Duane
 * 	Add fields for PIOC[T]USAGE procfs ioctls.
 * 	[1998/01/05  15:51:18  Andrew_Duane]
 * 
 * Revision 4.3.55.11  1997/11/06  12:26:28  James_Woodward
 * 	per-processor numa work
 * 	[1997/11/06  12:05:42  James_Woodward]
 * 
 * Revision 4.3.55.10  1997/10/29  14:56:13  Anton_Verhulst
 * 	Add file descriptor bitmaps to struct ufile_state.
 * 	[1997/10/28  18:03:10  Anton_Verhulst]
 * 
 * Revision 4.3.55.9  1997/10/03  14:04:59  Paul_Park
 * 	 	** Merge Information **
 * 		** Command used:	bmerge **
 * 		** Ancestor revision:	4.3.55.7 **
 * 		** Merge revision:	4.3.55.8 **
 * 	 	** End **
 * 	[1997/10/01  13:52:12  Paul_Park]
 * 	Add uu_copyinctl to uthread for copyin[str] control.
 * 	[1997/08/27  18:36:52  Paul_Park]
 * 
 * Revision 4.3.55.8  1997/09/04  19:30:33  James_Woodward
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL6:PTCOS_BL10 **
 * 		** Ancestor revision:	4.3.63.5 **
 * 		** Merge revision:	4.3.63.6 **
 * 	 	** End **
 * 	merge of PTmin BL10 changes
 * 	[1997/09/04  19:16:38  James_Woodward]
 * 
 * Revision 4.3.63.6  1997/06/24  21:10:21  Jeff_Denham
 * 	Add uu_fbhandler to the utask structure for user-space fat binary
 * 	fixup support.
 * 	[1997/06/24  20:59:41  Jeff_Denham]
 * 
 * Revision 4.3.55.7  1997/06/18  15:37:16  Dave_King
 * 	Added support for TNC remote copyin/copyout.
 * 	[1997/06/02  16:01:08  Dave_King]
 * 
 * Revision 4.3.55.6  1997/04/24  20:14:30  Stuart_Hollander
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL3:PTCOS_BL6 **
 * 		** Ancestor revision:	4.3.63.3 **
 * 		** Merge revision:	4.3.63.5 **
 * 	 	** End **
 * 	merge of PTmin BL6 changes
 * 	[1997/04/24  20:01:48  Stuart_Hollander]
 * 
 * Revision 4.3.55.5  1997/02/05  21:02:28  Stephen_Ofsthun
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTBOS_BL4:PTCOS_BL3 -visual **
 * 		** Ancestor revision:	4.3.42.15 **
 * 		** Merge revision:	4.3.63.3 **
 * 	 	** End **
 * 	merge of PTC BL3 changes
 * 	[1997/02/05  20:55:15  Stephen_Ofsthun]
 * 
 * Revision 4.3.63.5  1997/01/24  20:35:24  Janice_Chang
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	4.3.63.3 **
 * 		** Merge revision:	4.3.63.4 **
 * 	 	** End **
 * 	Add field uu_fd_newmax to utask structure that denotes whether extended
 * 	file descriptor support is enabled.
 * 	[1997/01/23  14:51:42  Janice_Chang]
 * 
 * Revision 4.3.63.4  1997/01/23  18:34:00  James_Woodward
 * 	add caching for space for doing select on large numbers
 * 	of file descriptors.
 * 	[1997/01/23  12:55:35  James_Woodward]
 * 	changes to make socket select a readonly operation...
 * 	[1997/01/15  12:45:12  James_Woodward]
 * 
 * Revision 4.3.55.4  1997/01/02  18:59:55  Larry_Scott
 * 	 	** Merge Information **
 * 		** Command used:	bmerge **
 * 		** Ancestor revision:	4.3.42.15 **
 * 		** Merge revision:	4.3.55.3 **
 * 	 	** End **
 * 	bmerge
 * 	[1996/08/15  18:21:48  Larry_Scott]
 * 	Add uu_target_pid field into an alignment hole in the uthread structure.
 * 	This is for mach auditing.
 * 	[1996/05/23  12:15:17  Larry_Scott]
 * 
 * Revision 4.3.63.3  1996/12/06  16:03:40  Edward_Cande
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit -visual **
 * 		** Ancestor revision:	4.3.42.15 **
 * 		** Merge revision:	4.3.63.2 **
 * 	 	** End **
 * 	Add field to the ufile_state structure and a check for
 * 	freeing of file descriptors (fd) in the U_OFILE_SET macro
 * 	to use a low watermark for looking for open fd.  POSIX
 * 	states that the lowest available fd available must be
 * 	returned on an open() or any of it cousins. This mean that
 * 	an exhaustive search of the list was necessary.  These
 * 	changes allows the search to start at last closed file
 * 	discriptor or one greater than the last allocated.  This
 * 	changes go hand in hand with changes in ufalloc
 * 	(bsd/kern_descrip.c).
 * 	[1996/12/06  15:39:29  Edward_Cande]
 * 
 * Revision 4.3.63.2  1996/12/03  21:49:53  Jeff_Denham
 * 	Add U_ADDR_LOCK_TRY() for the manager thread.
 * 	[1996/12/03  21:24:29  Jeff_Denham]
 * 
 * Revision 4.3.55.3  1996/07/11  18:25:00  James_Woodward
 * 	fix kernel layered product binary compatibility bug introduced
 * 	by the bravo merge.
 * 	[1996/07/10  18:30:11  James_Woodward]
 * 
 * Revision 4.3.55.2  1996/05/01  20:10:27  Jeff_Denham
 * 	Merge from bravos.bl2
 * 	[1996/05/01  19:22:54  Jeff_Denham]
 * 
 * Revision 4.3.53.6  1996/03/10  15:37:40  Ray_Lanza
 * 	Merge of Platinum BL8 to BL11 pass 1 changes
 * 	[1996/03/10  15:19:33  Ray_Lanza]
 * 
 * Revision 4.3.42.15  1996/02/20  16:36:01  Jeff_Denham
 * 	Remove spare fields added to prevent create binary compat problems.
 * 	Moved both sigtramp field to dynamic signal action structure.
 * 	[1996/02/16  20:05:27  Jeff_Denham]
 * 
 * Revision 4.3.42.14  1996/02/08  19:02:47  Jeff_Denham
 * 	Move spare fields to struct utask, not struct user!
 * 	[1996/02/08  18:30:02  Jeff_Denham]
 * 
 * Revision 4.3.42.13  1996/02/08  18:21:06  Jeff_Denham
 * 	Add space at the end of the user structures for future growth.
 * 	[1996/02/07  20:37:11  Jeff_Denham]
 * 
 * Revision 4.3.42.12  1996/02/07  19:28:18  Jeff_Denham
 * 	Add a uarea sigtramp address for Spec 1170 handlers.
 * 	[1996/01/27  16:48:06  Jeff_Denham]
 * 
 * Revision 4.3.42.11  1996/01/05  21:01:25  James_Woodward
 * 	fix locking of uarea fi_flags to always use handy lock
 * 	[1996/01/05  17:51:54  James_Woodward]
 * 
 * Revision 4.3.42.10  1995/11/14  19:13:00  Jeff_Denham
 * 	Replace ONSIG symbol with hardcode 32 to make 1170 programs
 * 	build easily. The ONSIG in signal.h is not in the 1170 namespace.
 * 	[1995/11/13  20:40:55  Jeff_Denham]
 * 
 * Revision 4.3.53.5  1995/11/10  23:43:35  Ray_Lanza
 * 	Merge of PTOS BL8
 * 	[1995/11/10  23:25:48  Ray_Lanza]
 * 
 * Revision 4.3.53.4  1995/10/31  23:06:44  Ray_Lanza
 * 	Reenabled advfs asmp field
 * 	[1995/10/31  22:53:47  Ray_Lanza]
 * 
 * Revision 4.3.53.3  1995/10/25  20:00:32  Ray_Lanza
 * 	Initial __alpha conditional evaluation and changes
 * 	[1995/10/25  19:30:34  Ray_Lanza]
 * 
 * Revision 4.3.53.2  1995/10/12  20:15:34  Ray_Lanza
 * 	Initial round of basic Intel related changes
 * 	[1995/10/12  19:48:57  Ray_Lanza]
 * 
 * Revision 4.3.42.9  1995/08/03  18:07:20  Jeff_Denham
 * 	Add a define for u.u_cancel_state.
 * 	[1995/07/31  14:29:40  Jeff_Denham]
 * 
 * Revision 4.3.42.8  1995/06/30  22:40:59  Mike_Milicia
 * 	Add MLS security hooks.
 * 	[1995/06/20  22:24:03  Mike_Milicia]
 * 
 * Revision 4.3.42.7  1995/06/30  15:31:05  Jeff_Denham
 * 	Move nxm uu_share members of np_uthread under #ifdef _KERNEL.
 * 	[1995/06/30  13:46:53  Jeff_Denham]
 * 
 * Revision 4.3.42.6  1995/06/29  20:21:35  Jeff_Denham
 * 	Move struct uuprof to sysmisc.h to avoid cross dependencies with
 * 	nmx.h.
 * 	[1995/06/23  22:07:24  Jeff_Denham]
 * 
 * Revision 4.3.42.5  1995/06/06  21:06:51  Anton_Verhulst
 * 	Add more speculative execution enums.
 * 	[1995/06/06  20:06:53  Anton_Verhulst]
 * 
 * Revision 4.3.42.4  1995/05/30  18:13:28  Jeff_Denham
 * 	Move u.u_sflags to np_uthread, filling an existing hole.
 * 	[1995/05/30  16:03:29  Jeff_Denham]
 * 
 * Revision 4.3.42.3  1995/04/27  16:37:45  James_Woodward
 * 	Add nxm definitions for 2-level scheduling.
 * 	[1995/04/25  18:57:57  James_Woodward]
 * 
 * Revision 4.3.42.2  1995/02/08  22:02:01  Jeff_Denham
 * 	Add support for dynamic signal actions.
 * 	[1995/02/03  18:21:55  Jeff_Denham]
 * 
 * Revision 4.3.40.3  1994/09/09  21:13:55  Paul_Shaughnessy
 * 	AdvFS ASMP support
 * 	[1994/09/08  12:08:54  Paul_Shaughnessy]
 * 
 * Revision 4.3.40.2  1994/09/09  18:01:17  Jeff_Denham
 * 	Add support for realtime signals.
 * 	[1994/09/08  20:08:24  Jeff_Denham]
 * 
 * Revision 4.3.22.34  1994/06/11  21:06:29  James_Woodward
 * 	Must always take out the uarea file table lock when adding or
 * 	deleting a file from the open file table.  This is needed to
 * 	synchronize with the fuser system call when can peek into another
 * 	tasks file table.
 * 	[1994/06/10  14:18:37  James_Woodward]
 * 
 * Revision 4.3.22.33  1994/04/23  02:10:14  Jeff_Denham
 * 	Thread/signal enhancements:
 * 	. move uu_oldmask from np_uthread to uthread.
 * 	. uu_cursig from uthread to np_uthread.
 * 	. add uu_sigwaitmask to np_uthread.
 * 	[1994/04/22  16:40:17  Jeff_Denham]
 * 
 * Revision 4.3.22.32  1994/04/05  19:02:20  James_Woodward
 * 	turn on/off uarea locking based on whether task is multi-thread or not.
 * 	[1994/04/05  11:05:58  James_Woodward]
 * 
 * Revision 4.3.22.31  1994/04/01  15:42:33  Anton_Verhulst
 * 	Final tweaks for Gold speculative execution.
 * 	[1994/04/01  15:22:29  Anton_Verhulst]
 * 
 * Revision 4.3.22.30  1994/03/31  15:15:47  Dave_Gerson
 * 	Added conditionalized structure name declarations as
 * 	required by C++ due to use of forward references.
 * 	[1994/03/14  19:32:43  Dave_Gerson]
 * 
 * Revision 4.3.22.29  1994/02/25  21:49:30  Ernie_Petrides
 * 	Move uu_handy_lock/utnd_lock/uf_ofile_lock fields of
 * 	utask/utask_nd/ufile_state structures to the tops of
 * 	structures to eliminate superfluous stores and loads
 * 	of lock addresses.  Also eliminated holes and potential
 * 	word-tear problems in utask structure.
 * 	[1994/02/25  00:14:19  Ernie_Petrides]
 * 
 * Revision 4.3.22.28  1994/02/18  21:05:43  James_Woodward
 * 	Move u_timer from utask structure to proc.  Combine utask timer lock
 * 	and proc timer lock.
 * 	[1994/02/18  19:28:27  James_Woodward]
 * 
 * Revision 4.3.22.27  1994/02/14  21:46:50  Anton_Verhulst
 * 	Add thread_rusage.
 * 	[1994/02/14  21:16:01  Anton_Verhulst]
 * 
 * Revision 4.3.22.26  1994/02/10  19:57:17  Ernie_Petrides
 * 	Remove UNIX_LOCKS dependency.
 * 	[1994/02/10  16:18:05  Ernie_Petrides]
 * 
 * Revision 4.3.22.25  1994/01/11  23:33:48  Anton_Verhulst
 * 	Add speculative execution structures.
 * 	[1994/01/11  23:32:37  Anton_Verhulst]
 * 
 * Revision 4.3.22.24  1994/01/05  21:45:55  Anton_Verhulst
 * 	Make user PC profiling on per-thread basis.
 * 	[1994/01/05  20:39:31  Anton_Verhulst]
 * 
 * Revision 4.3.22.23  1993/12/30  20:20:58  Jeff_Denham
 * 	Merge to latest.
 * 	[1993/12/30  16:10:28  Jeff_Denham]
 * 	Add uu_cursig to avoid having to requeue signals in mpsleep().
 * 	Saves an extra call to issig().
 * 	[1993/12/20  14:00:47  Jeff_Denham]
 * 
 * Revision 4.3.22.22  1993/12/14  16:57:50  Ernie_Petrides
 * 	Add u.u_callp for audit_rec_build() optimization.
 * 	[1993/12/12  02:44:44  Ernie_Petrides]
 * 
 * Revision 4.3.22.21  1993/11/16  22:58:13  James_Woodward
 * 	split uthread from pcb struct
 * 	[1993/11/10  12:06:31  James_Woodward]
 * 
 * Revision 4.3.22.20  1993/10/16  15:58:20  Paula_Long
 * 	Hide sigqueue_t from users.
 * 	[1993/10/16  15:51:41  Paula_Long]
 * 
 * Revision 4.3.22.19  1993/10/11  18:30:18  Jeff_Denham
 * 	Sterling/Gold merge.
 * 	[1993/10/11  13:52:45  Jeff_Denham]
 * 
 * Revision 4.3.22.18  1993/09/23  17:52:47  Jeff_Denham
 * 	Move uu_curinfo to uthread from np_uthread.
 * 	[1993/09/22  23:29:57  Jeff_Denham]
 * 	Merge with latest.
 * 	[1993/09/20  21:36:40  Jeff_Denham]
 * 	Tweaks.
 * 	[1993/09/17  21:50:56  Jeff_Denham]
 * 	Merge with latest.
 * 	[1993/09/03  22:32:23  Jeff_Denham]
 * 	Etype integration.
 * 	[1993/08/19  23:07:31  Jeff_Denham]
 * 
 * Revision 4.3.22.17  1993/09/23  14:54:47  Anton_Verhulst
 * 	Added u_mgr and u_handle to support the OSF 1.2 exec().
 * 	[1993/09/20  16:55:08  Anton_Verhulst]
 * 
 * Revision 4.3.22.16  1993/09/15  23:36:46  Larry_Scott
 * 	merge fix
 * 	[1993/09/15  23:33:42  Larry_Scott]
 * 
 * Revision 4.3.22.15  1993/09/15  20:28:52  Larry_Scott
 * 	start of security merge
 * 	[1993/09/15  20:08:13  Larry_Scott]
 * 
 * Revision 4.3.22.14  1993/09/14  18:47:12  James_Woodward
 * 	fixes to proc layout
 * 	[1993/09/13  10:53:33  James_Woodward]
 * 
 * Revision 4.3.22.13  1993/08/27  20:47:39  James_Woodward
 * 	allocate proc/task/utask and thread/np_uthread together
 * 	[1993/08/25  11:55:49  James_Woodward]
 * 
 * Revision 4.3.22.12  1993/07/30  21:39:19  Ernie_Petrides
 * 	Remove macros for utask lock initialization now done in
 * 	uarea_lock_init() and add U_FDTABLE locking macros.
 * 	[1993/07/30  20:57:58  Ernie_Petrides]
 * 
 * Revision 4.3.22.11  1993/07/16  13:19:35  Jeff_Denham
 * 	Need to #ifdef _KERNEL uu_select_event (moved here from thread.h).
 * 	[1993/07/16  13:14:03  Jeff_Denham]
 * 
 * Revision 4.3.22.10  1993/07/15  18:24:56  Jeff_Denham
 * 	More np_uthread adjustments.
 * 	[1993/07/14  23:16:53  Jeff_Denham]
 * 	At this point, create the np_uthread structure from OSF1.2.
 * 	[1993/07/13  20:32:04  Jeff_Denham]
 * 
 * Revision 4.3.22.9  1993/07/11  18:15:38  Paula_Long
 * 	For now move uu_select_event to the end of the uthread structure
 * 	so that libdpi will build.  At some point the none
 * 	pageable uthread area needs to get created and this field
 * 	should live there.
 * 	[1993/07/11  16:59:40  Paula_Long]
 * 
 * Revision 4.3.22.8  1993/07/08  18:56:35  James_Woodward
 * 	fix dbx build in nightly
 * 	[1993/07/08  15:29:34  James_Woodward]
 * 
 * Revision 4.3.22.7  1993/07/06  18:23:24  James_Woodward
 * 	fix command build errors
 * 	[1993/07/06  17:52:35  James_Woodward]
 * 
 * Revision 4.3.22.6  1993/07/03  22:52:11  Paula_Long
 * 	Attempting to fix commments.  Revision history is
 * 	messed up.
 * 	[1993/07/03  22:51:27  Paula_Long]
 * 
 * Revision 4.3.22.5  1993/07/03  22:36:21  Paula_Long
 * 	Only include machine/event.h if _KERNEL is defined
 * 
 * Revision 4.3.22.4  1993/07/02  17:40:48  James_Woodward
 * 	merge osf1.2 signals
 * 	[1993/07/02  16:56:10  James_Woodward]
 * 	osf12 merge
 * 	[1993/06/24  13:02:25  James_Woodward]
 * 
 * Revision 4.3.22.3  1993/05/26  22:16:45  Paula_Long
 * 	submitting the SMP project
 * 	[1993/05/26  06:56:40  Paula_Long]
 * 
 * Revision 4.3.15.4  1993/05/24  12:21:05  James_Woodward
 * 	move unix_master funnelling data to u_thread structure
 * 	[1993/05/12  19:18:27  James_Woodward]
 * 
 * Revision 4.3.18.4  1993/05/22  17:58:58  Jeff_Denham
 * 	Hide queue types from user space.
 * 	[1993/05/22  04:04:46  Jeff_Denham]
 * 	SVR4 integration.
 * 	[1993/05/21  20:18:20  Jeff_Denham]
 * 
 * Revision 4.3.18.3  1993/04/23  17:20:17  Larry_Scott
 * 	add set_uids fields
 * 	[1993/04/15  19:10:22  Larry_Scott]
 * 	perf work
 * 	[1993/04/14  13:25:21  Larry_Scott]
 * 
 * Revision 4.3.15.3  1993/04/08  19:50:02  James_Woodward
 * 	implement aligned stack data
 * 	[1993/04/08  14:33:39  James_Woodward]
 * 
 * Revision 4.3.18.2  1993/04/01  20:08:06  Michael_Fairbrother
 * 	Merge from shared sandbox to sandbox prior to submit
 * 	[1993/04/01  15:50:39  Michael_Fairbrother]
 * 
 * Revision 4.3.10.10  1993/03/28  21:24:20  Larry_Scott
 * 	set uu_vno_mode to be type mode_t
 * 	[1993/03/28  21:11:30  Larry_Scott]
 * 
 * Revision 4.3.10.9  1993/03/23  20:16:14  Larry_Scott
 * 	thread-safe
 * 	[1993/03/23  20:08:51  Larry_Scott]
 * 
 * Revision 4.3.10.8  1993/03/11  19:10:45  Larry_Scott
 * 	remove secureware code
 * 	[1993/03/11  19:07:22  Larry_Scott]
 * 
 * Revision 4.3.15.2  1993/03/06  02:11:26  Paula_Long
 * 	moved sandbox from smpproj to smpsb
 * 	[1993/03/05  04:12:09  Paula_Long]
 * 
 * Revision 4.3.10.7  1993/02/16  11:03:27  Larry_Scott
 * 	merge with alpha.bl012
 * 	[93/02/16  10:56:28  Larry_Scott]
 * 
 * Revision 4.3.12.2  93/02/10  14:29:39  James_Woodward
 * 	make pr_lock an instance of the lock instead of a pointer.
 * 	[93/02/10  14:21:00  James_Woodward]
 * 
 * Revision 4.3.4.9  92/12/01  16:43:28  Anton_Verhulst
 * 	Add per thread ieee emulation state.
 * 	[92/11/25  16:26:50  Anton_Verhulst]
 * 
 * Revision 4.3.4.8  92/11/06  16:56:25  Anton_Verhulst
 * 	Removed uu_uac and moved it to proc struct as p_uac since it can
 * 	now be set if not resident.
 * 	[92/11/06  16:45:07  Anton_Verhulst]
 * 
 * Revision 4.3.4.7  92/10/27  15:34:00  Anton_Verhulst
 * 	Add uu_uac for Unaligned Access Control.
 * 	[92/10/27  15:08:53  Anton_Verhulst]
 * 
 * Revision 4.3.4.6  92/09/11  16:57:48  Anton_Verhulst
 * 	Change sizes of profile struct elements to longs.
 * 	[92/09/11  16:48:41  Anton_Verhulst]
 * 	Change uthread and utask signal masks to sigset_t type.
 * 	[92/07/07  17:30:25  Jeff_Denham]
 * 
 * Revision 4.3.4.5  92/07/07  19:00:07  Jeff_Denham
 * 	"Submit to alpha"
 * 
 * Revision 4.3.4.4  92/06/03  13:46:31  Paul_Hansen
 * 	Merged in Silver BL7
 * 	[92/06/03  13:36:21  Paul_Hansen]
 * 
 * Revision 4.3.4.3  92/04/15  14:15:19  Shashi_Mangalat
 * 	Merged in Silver BL6.
 * 	Added uu_uswitch
 * 	  [92/03/27  16:25:34  Alaa_Zeineldine]
 * 	Add u_exitp to user
 * 	   [92/03/10  14:26:38  Carlos_Christensen]
 * 	[92/04/15  13:30:55  Shashi_Mangalat]
 * 
 * Revision 4.3.4.2  92/03/18  22:27:19  Shashi_Mangalat
 * 	Merged in Silver BL5
 * 	pickup def. of audit_info from security.h [Uday_Gupta]
 * 	Changed default def. of u for mips;  need to know the size of
 * 	  uthread and pcb before defining u;  u now defined in
 * 	  machine/thread.h;  part of mips kstack change. [Donald_Dutile]
 * 	[92/03/18  22:12:35  Shashi_Mangalat]
 * 
 * Revision 4.2.3.3  92/02/28  21:30:28  Sec_Proj_Michael_Fairbrother
 * 	pickup def. of audit_info from security.h
 * 	[92/02/24  16:02:29  Uday_Gupta]
 * 
 * Revision 4.2.3.2  92/02/05  17:28:46  Donald_Dutile
 * 	Changed default def. of u for mips;  need to know the size of
 * 	uthread and pcb before defining u;  u now defined in
 * 	     machine/thread.h;  part of mips kstack change.
 * 	[92/01/10  10:41:16  Donald_Dutile]
 * 
 * Revision 4.3  92/01/15  02:13:02  devbld_gsf
 * 	Baselevel alpha_bl002
 * 
 * Revision 4.2.2.2  91/12/07  16:53:05  Jay_Estabrook
 * 	merge ALPHA with SILVER via ODE
 * 	[91/12/07  16:41:56  Jay_Estabrook]
 * 
 * Revision 4.2  91/09/19  23:02:43  devbld
 * 	Adding ODE Headers
 * 
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: user.h,v $ $Revision: 4.3.186.5 $ (DEC) $Date: 2006/03/03 17:33:04 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * Copyright (C) 1988,1989 Encore Computer Corporation.
 * All Rights Reserved.
 *
 * Property of Encore Computer Corporation.
 * This software is made available solely pursuant to the terms of
 * a software license agreement which governs its use. Unauthorized
 * duplication, distribution or sale are strictly prohibited.
 *
 */
/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.2
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#ifndef	_SYS_USER_H_
#define _SYS_USER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/secdefines.h>
#include <mach/boolean.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/namei.h>
#include <sys/ucred.h>
#include <sys/sem.h>
#include <sys/audit.h>
#include <sys/unix_defs.h>
#include <kern/lock.h>
#include <kern/queue.h>
#ifdef	_KERNEL
#include <sys/siginfo.h>
#include <kern/event.h>
#include <sys/security.h>
#include <machine/nxm.h>
#endif	/* _KERNEL */

#if defined (__cplusplus)
struct proc;
struct file;
struct exit_actn;
#endif

/*
 * Per process structure containing data that
 * isn't needed in core when the process is swapped out.
 */

/*
 * V5.0, the maximum login name size is 64 (up from 12).  By default, the
 * user still gets 12 but that can be bumped via sysconfigtab (generic)
 * by setting the global login_name_max.
 */
#define MAXLOGNAME      64
#define	DEFAULT_LOGNAME	12
#define	COMPAT_LOGNAME	12

#define MAXCOMLEN	16	/* <= MAXNAMLEN, >= sizeof(ac_comm) */

struct flag_field {
	int	fi_flag;
	udecl_simple_lock_data(,*fi_lock) /* unused */
};

#define NOFILE_IN_U   64 
#define U_FE_ALLOC_SIZE 8 		/* allocation size of uarea open file */
#define U_FE_ARRAY_SIZE ((NOFILE_IN_U + U_FE_ALLOC_SIZE - 1)/U_FE_ALLOC_SIZE)

#define U_FE_OF_ALLOC_SIZE 256 		/* allocation size for overflow area */

#define NUM_LVL1_IN_LVL0	(sizeof(long) * NBBY)
#define NUM_FD_IN_LVL1		(sizeof(long) * NBBY)
#define MAX_NUM_LVL0_ENTRIES  \
	  (NEW_OPEN_MAX_SYSTEM / (NUM_LVL1_IN_LVL0 * NUM_FD_IN_LVL1))

#ifdef __alpha
typedef enum {
	SPEC_ACTION_RAISE,
	SPEC_ACTION_IGNORE,
	SPEC_ACTION_CALL_HANDLER,
	SPEC_ACTION_INITIALIZE,
	SPEC_FAULT_IGNORE,
	SPEC_FAULT_RAISE,
	SPEC_ACTION_INITIALIZE_FB_FIXUP
} spec_action;

struct uuspeculative {	/* speculative execution data */
	int		sp_version;
	spec_action	sp_segv_action;
	spec_action	sp_fpe_action;
	vm_offset_t	sp_handler_addr;
};
#endif /* __alpha */

/* For uprintf_safe() */
#define UPRINT_TXT_SZ (244)

struct uprint {
	struct uprint	*next;		/* 0 == end */
	int		n;		/* Length of string */
	char text[UPRINT_TXT_SZ];	/* text to be printed this trip */
};


#if	(defined(_KERNEL) || defined(SHOW_UTT))

/*
 *      Forward Declarations of structures at file scope to make 
 *      pre-ANSI C++ happy.
 */
struct processor;
struct np_uthread;
struct utask;
struct task;
struct event;
struct execops;

/*
 *	Per-thread U area.
 *
 *	It is likely that this structure contains no fields that must be
 *	saved between system calls.  Note that the size of this structure
 *	must not be changed in minor releases because it affects binary
 *	compatibility with kernel layered products (due to the arrangement
 *	of the stack_layout structure).
 */
struct uthread {
/* namei & co. */
	struct unameicache {		/* last successful directory search */
		int nc_prevoffset;	/* offset at which last entry found */
		ino_t nc_inumber;	/* inum of cached directory */
		dev_t nc_dev;		/* dev of cached directory */
		time_t nc_time;		/* time stamp for cache entry */
	} uu_ncache;
	struct	nameidata uu_nd;
	int	reserved;
	/*
	 * Member uu_upcf is written at interrupt level.
	 * Give it its own longword, to avoid any locking
	 * overlap (if anything here needed locking, which
	 * nothing currently does).
	 */
	int     uu_upcf;

#ifdef __alpha

/* per thread ieee floating point state */
	ulong_t	uu_ieee_fp_trap_pc;
	ulong_t	uu_ieee_fp_trigger_sum;
	uint_t	uu_ieee_fp_trigger_inst;

	boolean_t uu_asmp;	/* AdvFS ASMP indicator */

        /* the following ieee variables are set via hal_sysinfo(2) */
	ulong_t	uu_ieee_fp_control;
	ulong_t	uu_ieee_set_state_at_signal;
	ulong_t	uu_ieee_fp_control_at_signal;
	ulong_t	uu_ieee_fpcr_at_signal;
#else /* __alpha */
	boolean_t uu_asmp;	/* AdvFS ASMP indicator */
#endif /* __alpha */

/* audit information (see audit.h for AUD_ definitions) */ 
	struct sysent *uu_callp;	/* system call table entry */
	int      uu_event;		/* audit event             */
	int      uu_vno_indx;		/* # of vno_{dev,num} used */
	dev_t    uu_vno_dev[AUD_VNOMAX];  /* vnode dev's referenced by cur proc */
	ino_t    uu_vno_num[AUD_VNOMAX];  /* vnode num's referenced by cur proc */
	ino_t    uu_vno_pdir[AUD_VNOMAX]; /* vnode num's parent dir referenced by
					   *cur proc */
	ushort_t uu_vno_aud[AUD_VNOMAX];  /* vnode audit-mode bits   */
	ushort_t uu_vno_mode[AUD_VNOMAX]; /* vnode mode flag         */
	u_int    uu_set_uids_snap;        /* snapshot of set_uids    */
	pid_t    uu_target_pid;           /* target of mach ipc op   */

#if SEC_MAC
	tag_t	uu_obj_slevel[AUD_VNOMAX]; /* vnode/object sensitivity level (SL) */
#endif
#if SEC_ILB
	tag_t	uu_obj_ilevel[AUD_VNOMAX];  /* vnode/object information level (IL) */
#endif
#if SEC_BASE
	ushort	  uu_sec_error;		    /* security related errno */
	ushort	  uu_last_fail_priv;	    /* last priv that failed and */
	privvec_t uu_privs_used;	    /* history of privs used */
#endif
#if SEC_PRIV || SEC_ARCH
	sec_eventvec_t	uu_sec_event_hist;  /* recent security event history
					     * mask.  flag bits accessed
					     * SE_ symbols as offsets (from
					     * security.h).  */
#endif

        sigset_t uu_oldmask;            /* saved mask from before sigpause */

	struct uuprof uu_prof;
#ifdef _KERNEL
	struct nxm_pth_state *uu_proflast;/* last nxm thread to use uu_prof */
#endif
	stack_t  uu_sigstack;		/* sp & on stack state variable */

/* Cluster related uthread fields.  */
	/*
	 * uu_copyio_ctl must be first short of this int.
	 */
	ushort_t  uu_copyio_ctl;	/* copy[in,out][str]() control */
	char	  uu_icsprio;		/* ICS priority */
	uchar_t	  uu_filler;		/* Pad to uint_t */
	boolean_t uu_remotecopy;	/* CSPECFS related support */
	uint_t	  uu_remotenode;	/* CSPECFS related support */
	pid_t	  uu_remotepid;		/* CSPECFS related support */

	long	uu_devpoll_mode;	/* signal select routines we are 
					   being called on behalf of devpoll */

/* NOTE!!!
 * Don't add anything past this. These elements are at the end
 * of the structure to force cache alignments
 */
	struct rad *uu_rad;
	struct np_uthread *np_uthread;
	struct utask *utask;
	struct proc *proc;		/* pointer to proc structure */
	struct thread *thread;		/* quick lookup for current_thread() */
	struct task *task;		/* quick lookup for current_task() */
	struct processor *processor;	/* current_processor() */
	int	cpu_number;		/* cpu_number() */
	int	disable_preemption;	/* stop preemptions */
};

/*
 * Non-pageable per-thread U area.
 *
 * All the data here may be accessed on behalf of threads other
 * than the current thread, so must always be resident.
 */
struct np_uthread {
    /* 64-byte alignment */
	long	*uu_ar0;		/* address of users saved R0 */

/* thread exception handling */
	int	uu_code;		/* ``code'' to trap */
	int	uu_cursig;		/* signal to take */

/* per thread signal state */
	int	uu_tsig;		/* thread signal for upcalls */
	int	uu_sflags;		/* origin of signal */
	sigset_t uu_sigwaitmask;	/* signals waiting for */
#ifdef  _KERNEL
        struct event uu_select_event;	/* select waits on this */

    /* 64-byte alignment */
	queue_head_t uu_sigqueue;	/* queue of sigqueue structs */
	sigqueue_t uu_curinfo;		/* curinfo for exc. */ 
	struct thread_rusage uu_tru;
	int	spare1;

    /* 64-byte alignment */
	struct ushared_state *uu_sptr;
	struct ushared_state uu_share;

    /* 64-byte alignment */
#define MAX_TSD_SLOTS			8
	void *uu_tsd[MAX_TSD_SLOTS];	/* thread-specific data */

    /* 64-byte alignment */
	long uu_radset[4];		/* Container for radset_t */
	struct uprint *uprint_list;	/* For uprintf_safe() */
	struct vnode *uu_vno_resv;	/* fifo open in progress */
	long spare2[2];
#endif
};

struct utask_nd {
	struct vnode *utnd_cdir;	/* current directory */
	struct vnode *utnd_rdir;	/* root directory of current process */
};

struct  ufile_entry {
	struct file *ufe_ofile;			/* pointer to file structure */
	struct devpoll_entry *ufe_dpe;       /* devpoll entry */
	struct socket_sel_queue *ufe_so_sel; /* socket select entry */
	int	ufe_unused;
	int	ufe_oflags;
#define UF_EXCLOSE	0x1			/* auto-close on exec */
#define UF_MAPPED	0x2			/* mapped from device */
#define UF_RESERVED_WAIT 0x4			/* thread waiting for slot in dup2 */

	udecl_simple_lock_data(,ufe_ofile_lock)	/* lock controls structure fields */
	long	pad[3];				/* make structure 64 bytes */
};

/*
 * Structures associated with the per-process open file table.
 */
struct ufile_state {
	udecl_simple_lock_data(,uf_ofile_lock)
	int	utask_need_to_lock;	/* set if utask locks needed */
	int	uf_first_available;	/* low water mark for available
						file descriptors */
	int	uf_lastfile;		/* high-water mark of uf_ofile */
	u_int	uf_of_count;		/* number of overflow entrys */

	u_int	uf_flags;

#define UF_TABLE_SHRINK_PENDING 1	/* thread waiting to do file table
					 * shrink... wait for uf_references to
					 * go to zero
					 */
#define UF_TABLE_SHRINK_WAIT	2	/* thread waiting for task open file
					 * table shrink operation to finish.
					 */
#define UF_TABLE_FD_WAIT	4	/* wait for free fdbit to be cleared */

	u_int	uf_references;		/* used to block table shrink */

	/*
	 * Open file bit arrays.  Bit set means that the file descriptor
	 * has been allocated.  If no fd > NOFILE_IN_U have been allocated,
	 * uf_popen_bits_lvlx points to uf_open_bits_lvlx.  This depends
	 * on NOFILE_IN_U never being > 64.  If the table expands,
	 * (uf_of_count > 0) uf_popen_bits_lvlx points to KALLOC'ed buffers.
	 */
	u_long	uf_open_bits_lvl0;
	u_long	uf_open_bits_lvl1;
	u_long	*uf_popen_bits_lvl0;
	u_long	*uf_popen_bits_lvl1;

	/*
	 * If greater than NOFILE_IN_U file descriptors are allocated,
	 * uf_ofile_of and uf_pofile_of are used to reference the KALLOC'ed
	 * buffers which store the additional entries.
	 */
	struct ufile_entry	*uf_entry[U_FE_ARRAY_SIZE];
	struct ufile_entry	**uf_of_entry;/* Pointer to KALLOC'ed buffer */
};


struct socket_sel_queue {
	struct queue_entry	links;
	int			msel;	/* set if multiple threads selecting */
	int			mbz;	/* maker to tell sel_queue form so_* */
	struct event		*event; /* event to wake-up */
	struct ufile_state	*ufile;	/* file state of task involved */
	struct task		*task;
	struct ufile_entry	*fe;
};

/*
 *	Per-task U area - global process state.
 */
struct utask {
    /* 64-byte-aligned section of read-mostly (rarely modified) data */
	char		uu_comm[MAXCOMLEN + 1];
	int		uu_maxuprc;	/* max processes per UID */
	char		*uu_logname;	/* login name, if available */
	char		*uu_argp;	/* pointers to args and env */
	char		*uu_envp;
	int		uu_arg_size;	/* and associated lengths */
	int		uu_env_size;
	struct timeval	uu_start;	/* process start time */

    /* 64-byte-aligned section of memory management data */
	caddr_t		uu_text_start;	/* text starting address */
	caddr_t		uu_data_start;	/* data starting address */
	caddr_t		uu_stack_start;	/* stack starting address */
	caddr_t		uu_stack_end;	/* stack ending address */
	size_t		uu_tsize;	/* text size (clicks) */
	size_t		uu_dsize;	/* data size (clicks) */
	size_t		uu_ssize;	/* stack size (clicks) */
	boolean_t	uu_stack_grows_up; /* stack grows at high end? */
	int		uu_lflags;	/* process lock and load flags */
/* lock flags */
#define UL_TXTLOCK	1
#define UL_DATLOCK	2
#define UL_STKLOCK	4
#define UL_PROLOCK	8
/* load flags */
#define UL_WXALLOW	0x100		/* execute perms for wrt only data */
#define UL_COMMENT	0x200		/* load data in comment section */

    /* 64-byte-aligned section of file descriptor management data */
	struct ufile_state uu_file_state; /* open file information */
	char		*uu_sel_cache;
	long		uu_sel_size;
	long		uu_ioch;	/* # of chars read/written */
	mode_t		uu_cmask;	/* mask for file creation */
	u_int		uu_fd_newmax;	/* extended descriptor support */
	long		spare1;
	long		spare2;
	long		spare3;

    /* 64-byte-aligned section of some of the handy-locked data */
	udecl_simple_lock_data(,uu_handy_lock) /* handy lock for misc. data */
	u_int		uu_set_uids;	/* uid change count */
	int		uu_shmsegs;	/* # attached shared-memory-segments */
	struct flag_field uu_acflag;	/* accounting flags */
	struct utask_nd uu_utnd;	/* current/chroot directory vnodes */
	long		spare4;
	long		spare5;

    /* 64-byte-aligned section of resource limit data */
	struct rlimit	uu_rlimit[RLIM_NLIMITS];

    /* 64-byte-aligned section of resource usage statistics */
	struct rusage	uu_ru;		/* stats for this proc */
	struct rusage	uu_cru;		/* sum of stats for reaped children */

    /* 64-byte-aligned section of the rest */
	lock_data_t	uu_addr_lock;	/* user addr space lock */
	struct sem_undo *uu_semundo;	/* semaphore undo structure */
	char		*uu_coredir;	/* pointer to core path */

	struct execops	*uu_mgr;	/* file format manager */
	void		*uu_handle;	/* handle for that manager */
	struct compat_mod *uu_compat_mod; /* compat module control block */
	u_int		uu_sigresvcnt;	/* reserved mesq notif. queue count */
	int		spare7;
	long		uu_task_rq_wait_sum; /* runq wait sum exited threads */
	struct exit_actn *uu_exitp;	/* LMF actions to do at process exit */
#ifdef __alpha
	struct uuspeculative *uu_spec;	/* speculative execution */
	void		(*uu_fbhandler)();
#endif /* __alpha */

	u_int		uu_auditmask[AUDIT_INTMASK_LEN]; /* auditmask */
	u_int		uu_audit_cntl;	/* audit control flag */
	u_int           uu_bigpg_anon;  /* bigp settings for anon objs */
	u_int           uu_bigpg_seg;   /* bigp settings for seg objs */
	u_int           uu_bigpg_shm;   /* bigp settings for shm objs */
	u_int           uu_bigpg_ssm;   /* bigp settings for ssm objs */
	u_int           uu_bigpg_stack; /* bigp settings for stack obj */
	u_int		uu_bigpg_factor;/* settings for gh factor */
	/* these three could be compacted to bits, but for now we have space */
	u_int		uu_l3gh_anon;	/* l3gh enabled for anon */
	u_int		uu_l3gh_shm;	/* l3gh enabled for shm */
	u_int		uu_l3gh_ssm;	/* l3gh enabled for ssm */
	u_int           spare8;
};

#endif	/* (defined(_KERNEL) || defined(SHOW_UTT)) */

#include <machine/pcb.h>
struct user {
	struct	pcb u_pcb;
	struct	proc *u_procp;		/* pointer to proc structure */
	long	*u_ar0;			/* address of users saved R0 */
	char	u_comm[MAXCOMLEN + 1];

/* ssycall parameters, results and catches */
	int	u_arg[8];		/* arguments to current system call */
					/* now only used for signal */

/* 1.1 - processes and protection */
	char	u_logname[MAXLOGNAME];	/* login name, if available */

/* 1.2 - memory management */
	/* u_tsize must follow u_logname - TBL_UAREA bin compat */
	size_t	u_tsize;		/* text size (clicks) */
	size_t	u_dsize;		/* data size (clicks) */
	size_t	u_ssize;		/* stack size (clicks) */
	caddr_t	u_text_start;		/* text starting address */
	caddr_t	u_data_start;		/* data starting address */
	caddr_t	u_stack_start;		/* stack starting address */
	caddr_t	u_stack_end;		/* stack ending address */
	int	u_stack_grows_up;	/* stack grows at high end? */
	time_t	u_outime;		/* user time at last sample */

/* 1.3 - signal management */
	sig_t	u_signal[32+1];	/* disposition of signals */
	sigset_t u_sasigmask[32+1];	/* signals to be blocked */
	sigset_t u_sigonstack;		/* signals to take on sigstack */
	sigset_t u_sigintr;		/* signals that interrupt syscalls */
	sigset_t u_oldmask;		/* saved mask from before sigpause */
	int	u_code;			/* ``code'' to trap */
	stack_t u_sigstack;		/* sp & on stack state variable */
#define u_onstack	u_sigstack.ss_flags
#define u_sigsflags	u_sigstack.ss_flags
#define u_sigsp		u_sigstack.ss_sp
#define u_sigssz	u_sigstack.ss_size

/* 1.4 - descriptor management */
/* This information must exactly match ufile_state structure */
	struct	file *u_ofile[NOFILE_IN_U];/* file structs of open files */
	char	u_pofile[NOFILE_IN_U];	/* per-process flags of open files */
	int	u_lastfile;		/* high-water mark of u_ofile */
	/*
	 * If greater than NOFILE_IN_U file descriptors are allocated,
	 * uf_ofile_of and uf_pofile_of are used to reference the KALLOC'ed
	 * buffers which store the additional entries.
	 */
	u_int   u_of_count;
	struct  file    **u_ofile_of; /* Pointer to KALLOC'ed buffer */
	char            *u_pofile_of; /* Pointer to KALLOC'ed buffer */
#define UF_EXCLOSE	0x1		/* auto-close on exec */
#define UF_MAPPED	0x2		/* mapped from device */
				/* These definitions must match utask_nd */
	struct vnode *u_cdir;	/* current directory */
	struct vnode *u_rdir;	/* root directory of current process */
	short	u_cmask;		/* mask for file creation */

/* 1.5 - timing and statistics */
	struct	rusage u_ru;		/* stats for this proc */
	struct	rusage u_cru;		/* sum of stats for reaped children */
	struct	itimerval u_timer[3];
	int	u_XXX[3];
	struct	timeval u_start;
	struct	flag_field u_acflag;

	struct uuprof u_prof;
	u_short	u_maxuprc;		/* max processes per UID (per tree) */

/* 1.6 - resource controls */
	struct	rlimit u_rlimit[RLIM_NLIMITS];

/* namei & co. */
	struct nameicache {		/* last successful directory search */
		int nc_prevoffset;	/* offset at which last entry found */
		ino_t nc_inumber;	/* inum of cached directory */
		dev_t nc_dev;		/* dev of cached directory */
		time_t nc_time;		/* time stamp for cache entry */
	} u_ncache;
	struct	nameidata u_nd;
#define UL_TXTLOCK	1
#define UL_DATLOCK	2

/* compatability module pointer */
	struct compat_mod *u_compat_mod;

/* pointer to chain of LMF actions to do at process exit */
	struct exit_actn *u_exitp;     /* _LMF_ */
	int	u_stack[1];
};

/* u_error codes */
#include <sys/errno.h>

#ifdef	_KERNEL
#include <kern/thread.h>

#ifndef	u
#ifdef	multimax
extern struct u_address	active_uareas[NCPUS];
#define u       (active_uareas[cpu_number()])
#else	/* multimax */
#ifdef	balance
#define u	(*(struct u_address *) 0x40)
#else	/* balance */
#ifndef __digital__ /* need to know size of uthread & pcb before def. u */
#define u	(current_thread()->u_address)
#endif	/* __digital__ */
#endif	/* balance */
#endif	/* multimax */
#endif	/* u */
#ifdef __alpha
#define	u_ieee_fp_trigger_sum		uu_ieee_fp_trigger_sum
#define	u_ieee_fp_trigger_inst		uu_ieee_fp_trigger_inst
#define	u_ieee_fp_trap_pc		uu_ieee_fp_trap_pc
#define u_ieee_fp_control		uu_ieee_fp_control
#define u_ieee_set_state_at_signal	uu_ieee_set_state_at_signal
#define u_ieee_fp_control_at_signal	uu_ieee_fp_control_at_signal
#define u_ieee_fpcr_at_signal		uu_ieee_fpcr_at_signal
#endif /* __alpha */
#ifdef __digital__
#define u_procp				proc
#define u_nd				uu_nd
#define u_asmp				uu_asmp
#define u_upcf				uu_upcf
#define u_ncache			uu_ncache
#define u_callp				uu_callp
#define u_event				uu_event
#define u_vno_indx			uu_vno_indx
#define u_vno_dev			uu_vno_dev
#define u_vno_num			uu_vno_num
#define u_vno_pdir			uu_vno_pdir
#define u_vno_aud			uu_vno_aud
#define u_vno_mode			uu_vno_mode
#define u_set_uids_snap			uu_set_uids_snap
#define u_target_pid			uu_target_pid
#define u_oldmask			uu_oldmask
#define u_prof				uu_prof
#define u_proflast			uu_proflast
#define u_sigstack			uu_sigstack
#define u_onstack			u_sigstack.ss_flags
#define u_sigsflags			u_sigstack.ss_flags
#define u_sigsp				u_sigstack.ss_sp
#define u_sigssz			u_sigstack.ss_size
#if SEC_MAC
#define u_obj_slevel			uu_obj_slevel
#endif /* SEC_MAC */
#if SEC_ILB
#define u_obj_ilevel			uu_obj_ilevel
#endif /* SEC_ILB */
#if SEC_BASE
#define u_sec_error			uu_sec_error
#define u_privs_used			uu_privs_used
#define u_last_fail_priv		uu_last_fail_priv
#endif /* SEC_BASE */
#if SEC_PRIV || SEC_ARCH
#define u_sec_event_hist		uu_sec_event_hist
#endif /* SEC_PRIV || SEC_ARCH */
#define u_copyinctl			uu_copyio_ctl
#define u_copyio_ctl			uu_copyio_ctl
#define u_icsprio			uu_icsprio
#define u_remotecopy			uu_remotecopy
#define u_remotepid			uu_remotepid
#define u_remotenode			uu_remotenode
#define u_rad				uu_rad
#define u_devpoll_mode			uu_devpoll_mode
#else /* ! __digital__ */
#define u_nd		uthread->uu_nd
#define u_upcf		uthread->uu_upcf
#define u_ncache	uthread->uu_ncache
#define u_event		uthread->uu_event
#define u_vno_indx	uthread->uu_vno_indx
#define u_vno_dev	uthread->uu_vno_dev
#define u_vno_num	uthread->uu_vno_num
#define u_vno_pdir	uthread->uu_vno_pdir
#define u_vno_aud	uthread->uu_vno_aud
#define u_vno_mode	uthread->uu_vno_mode
#define u_set_uids_snap	uthread->uu_set_uids_snap
#define u_target_pid	uthread->uu_target_pid
#define u_oldmask	uthread->uu_oldmask
#define u_prof		uthread->uu_prof
#define u_sigstack	uthread->uu_sigstack
#define u_onstack	u_sigstack.ss_flags
#define u_sigsflags	u_sigstack.ss_flags
#define u_sigsp		u_sigstack.ss_sp
#define u_sigssz	u_sigstack.ss_size
#define	u_copyinctl	uthread->uu_copyio_ctl
#define	u_copyio_ctl	uthread->uu_copyio_ctl
#define u_icsprio	uthread->uu_icsprio
#define u_remotecopy	uthread->uu_remotecopy
#define u_remotepid	uthread->uu_remotepid
#define u_remotenode	uthread->uu_remotenode
#endif /* __digital__ */

/*
 * Cluster related CSPECFS support.
 */
#define IS_REMOTE_COPY(up)		((up)->u_remotecopy == TRUE)
#define SET_REMOTE_COPY(up, val)	(up)->u_remotecopy = (val)
#define SET_REMOTE_PID(up, val)		(up)->u_remotepid = (val)
#define GET_REMOTE_PID(up)		(up)->u_remotepid
#define SET_REMOTE_NODE(up, val)	(up)->u_remotenode = (val)
#define GET_REMOTE_NODE(up)		(up)->u_remotenode


/*
 * function prototypes for task open file table routines 
 */
void clear_fdbit(int, struct ufile_state *);
boolean_t set_fdbit(int, struct ufile_state *);
int ufalloc(long, int *, struct ufile_entry **, struct ufile_state *);
int falloc(struct file **, int *,  struct ufile_entry **);
int getf(struct file **, long, char *, struct ufile_state *);
int getf_ref_always(struct file **, long, char *, struct ufile_state *);
struct ufile_entry * get_remote_task_fe(int, struct ufile_state *);
void u_set_fe(int, struct ufile_entry *, struct file *, struct ufile_state *); 
void u_set_fe_with_flag(int, struct ufile_entry *, struct file *, 
			struct ufile_state *, int); 
void u_file_table_ref(struct ufile_state *);
void u_file_table_unref(struct ufile_state *);
struct ufile_entry *get_remote_task_fe(int, struct ufile_state *);
void close_task_files(struct ufile_state *);
int getf_by_remote_task(struct file **, long, char *, struct ufile_state *);
void close_task_files_nofree(struct ufile_state *);

/*
 * function prototypes for coredir handling routines
 */
int  add_corepath(char *);
void remove_corepath(void);

/* 
 * locking macros for open file table.
 */
udecl_simple_lock_info(extern ,ufe_lockinfo)

#define U_FE_LOCK_INIT(fe)	\
	usimple_lock_setup(&(fe)->ufe_ofile_lock, ufe_lockinfo)

#define U_FE_LOCK_TERMINATE(fe)	\
	usimple_lock_terminate(&(fe)->ufe_ofile_lock)

struct ufile_entry * enable_fd_slot(int, struct ufile_state *);

/*
 * The U_FILE_STATE_LOCK lock is used when accessing the uf_flags or uf_references
 * fields in the task open file table.  For all other cases the U_FILE_STATE_LOCK_MT
 * is used since we only need to synchronize against threads within a multi-threaded
 * task.
 */
#define U_FILE_STATE_LOCK(ufp) 					\
MACRO_BEGIN							\
{								\
	usimple_lock(&(ufp)->uf_ofile_lock); 			\
}								\
MACRO_END

#define U_FILE_STATE_UNLOCK(ufp) 				\
MACRO_BEGIN							\
{								\
	usimple_unlock(&(ufp)->uf_ofile_lock); 			\
}								\
MACRO_END

#define U_FILE_STATE_LOCK_MT(ufp) 				\
MACRO_BEGIN							\
{								\
	if ((ufp)->utask_need_to_lock)				\
		usimple_lock(&(ufp)->uf_ofile_lock); 		\
}								\
MACRO_END

#define U_FILE_STATE_UNLOCK_MT(ufp) 				\
MACRO_BEGIN							\
{								\
	if ((ufp)->utask_need_to_lock)				\
		usimple_unlock(&(ufp)->uf_ofile_lock); 		\
}								\
MACRO_END

/*
 * The U_FE_LOCK needs to be taken whenever the field ufe_ofile is being 
 * changed from valid to NULL, NULL to  valid, or U_FD_RESERVED to valid.
 * The U_FE_LOCK is also used when looking at another tasks open file 
 * table.  For all other cases, the U_FE_LOCK_MT is used since we only need
 * to synchronize if it is a multi-threaded task.
 */ 
#define U_FE_LOCK(fe) 						\
MACRO_BEGIN							\
{								\
	usimple_lock(&(fe)->ufe_ofile_lock);			\
}								\
MACRO_END

#define U_FE_UNLOCK(fe) 					\
MACRO_BEGIN							\
{								\
	usimple_unlock(&(fe)->ufe_ofile_lock);			\
}								\
MACRO_END

#define U_FE_LOCK_MT(fe,ufp) 					\
MACRO_BEGIN							\
{								\
	if ((ufp)->utask_need_to_lock)				\
		usimple_lock(&(fe)->ufe_ofile_lock);		\
}								\
MACRO_END

#define U_FE_UNLOCK_MT(fe,ufp) 					\
MACRO_BEGIN							\
{								\
	if ((ufp)->utask_need_to_lock)				\
		usimple_unlock(&(fe)->ufe_ofile_lock);		\
}								\
MACRO_END


/*
 * The U_GET_FE macro is used to get a file entry structure pointer for the 
 * current task.  Need to use get_remote_task_fe() if going after another task.
 */
#define U_GET_FE(fd, ufp) 	(((fd) < NOFILE_IN_U) 	? 		\
	((ufp)->uf_entry[(fd)/U_FE_ALLOC_SIZE]  ? 			\
	(ufp)->uf_entry[(fd)/U_FE_ALLOC_SIZE] + 			\
			((fd) %U_FE_ALLOC_SIZE) :			\
	NULL) :								\
	((ufp)->uf_of_entry ?						\
	((((ufp)->uf_of_entry[((fd)-NOFILE_IN_U)/U_FE_OF_ALLOC_SIZE]) +	\
			(((fd)-NOFILE_IN_U) % U_FE_OF_ALLOC_SIZE))) : NULL))


#define u_ar0		np_uthread->uu_ar0
#define u_code		np_uthread->uu_code
#define u_sig		np_uthread->uu_sptr->sig
#define	u_cursig	np_uthread->uu_cursig
#define	u_sflags	np_uthread->uu_sflags
#define	u_tsig		np_uthread->uu_tsig
#define u_share		np_uthread->uu_share
#define u_sptr		np_uthread->uu_sptr
#define u_sigmask	np_uthread->uu_sptr->sigmask
#define uu_sigmask	uu_sptr->sigmask
#define uu_sig		uu_sptr->sig
#define u_nxm_active	np_uthread->uu_sptr->nxm_active
#define u_nxm_ssig	np_uthread->uu_sptr->nxm_ssig
#define u_sigwaitmask	np_uthread->uu_sigwaitmask
#define u_select_event	np_uthread->uu_select_event
#define	u_sigqueue	np_uthread->uu_sigqueue
#define	u_curinfo	np_uthread->uu_curinfo
#define u_tru		np_uthread->uu_tru
#define u_pthid		np_uthread->uu_sptr->pth_id
#define u_shflags	np_uthread->uu_sptr->flags
#define u_cancel_state	np_uthread->uu_sptr->cancel_state
#define u_tsd		np_uthread->uu_tsd
#define u_uprint_list	np_uthread->uprint_list
#define u_vno_resv	np_uthread->uu_vno_resv

#define u_comm		utask->uu_comm
#define u_calltype	utask->uu_calltype	/* ROMP_DUALCALL */
#define u_logname	utask->uu_logname
#define	u_utnd		utask->uu_utnd
#define	u_file_state	utask->uu_file_state
#define u_fd_newmax	utask->uu_fd_newmax
#define u_task_rq_wait_sum	utask->uu_task_rq_wait_sum
#define uu_cdir		uu_utnd.utnd_cdir
#define uu_rdir		uu_utnd.utnd_rdir

#define u_cdir		utask->uu_cdir
#define u_rdir		utask->uu_rdir
#define u_cred		u_nd.ni_cred
#define	u_ruid		u_procp->p_ruid
#define	u_rgid		u_procp->p_rgid
#define u_uid		u_cred->cr_uid
#define u_gid		u_cred->cr_gid
#define u_ngroups	u_cred->cr_ngroups
#define u_groups	u_cred->cr_groups

#define u_tsize		utask->uu_tsize
#define u_dsize		utask->uu_dsize
#define u_ssize		utask->uu_ssize
#define u_text_start	utask->uu_text_start
#define u_data_start	utask->uu_data_start
#define u_stack_start	utask->uu_stack_start
#define u_stack_end	utask->uu_stack_end
#define u_stack_grows_up utask->uu_stack_grows_up
#ifdef __alpha
#define u_spec		utask->uu_spec
#define u_fbhandler	utask->uu_fbhandler
#endif /* __alpha */

#define u_sigtramp	utask->uu_sigtramp

#define u_lastfile	u_file_state.uf_lastfile
#define	u_ofile_lock	u_file_state.uf_ofile_lock
#define u_handy_lock    utask->uu_handy_lock
#define u_addr_lock	utask->uu_addr_lock
#define u_cmask		utask->uu_cmask

#define u_ru		utask->uu_ru
#define u_cru		utask->uu_cru
#define u_ioch		utask->uu_ioch
#define u_timer		proc->p_timer
#define u_XXX		utask->uu_XXX
#define u_start		utask->uu_start
#define u_acflag	utask->uu_acflag

#define u_maxuprc	utask->uu_maxuprc

#define u_lflags	utask->uu_lflags

#define u_rlimit	utask->uu_rlimit


#define	u_coredir	utask->uu_coredir
#define u_semundo	utask->uu_semundo
#define u_shmsegs	utask->uu_shmsegs

#define u_argp          utask->uu_argp
#define u_envp          utask->uu_envp
#define u_arg_size      utask->uu_arg_size
#define u_env_size      utask->uu_env_size
#define u_compat_mod    utask->uu_compat_mod
#define u_exitp         utask->uu_exitp           /* _LMF_ */
#define u_auditmask     utask->uu_auditmask
#define u_audit_cntl    utask->uu_audit_cntl
#define u_bigpg_anon    utask->uu_bigpg_anon
#define u_bigpg_seg     utask->uu_bigpg_seg
#define u_bigpg_shm     utask->uu_bigpg_shm
#define u_bigpg_ssm     utask->uu_bigpg_ssm
#define u_bigpg_stack   utask->uu_bigpg_stack
#define u_bigpg_factor	utask->uu_bigpg_factor
#define u_l3gh_anon	utask->uu_l3gh_anon
#define u_l3gh_shm	utask->uu_l3gh_shm
#define u_l3gh_ssm	utask->uu_l3gh_ssm
#define u_set_uids      utask->uu_set_uids
#define u_mgr           utask->uu_mgr
#define u_handle        utask->uu_handle
#define u_sigresvcnt	utask->uu_sigresvcnt
#define u_sel_cache	utask->uu_sel_cache
#define u_sel_size	utask->uu_sel_size

/*
 * Reserved TSD key definitions
 *
 * The NFS server, the Streams subsystem, and CFS have reserved keys
 * with which to access per-subsystem thread-specific data in the kernel.
 * All other subsystems must explicitly reserve a TSD key via the
 * interface.  (See thread.h)
 */
#define TSD_NFS_KEY             0
#define TSD_STREAMS_KEY         1
#define TSD_CFS_KEY		2

#define TSD_FIRST_AVAIL_KEY     3

/*
 * Convenience macros for the NFS server to short-circuit the TSD
 * access methods
 */
#define NFS_SERVER_TSD		u.u_tsd[TSD_NFS_KEY]

#define NFS_SERVER_TSD_BY_THD(__th__)				\
    thread_to_np_uthread(__th__)->uu_tsd[TSD_NFS_KEY]

/*
 * Convenience macro for CFS to short-circuit the TSD
 * access methods
 */
#define CFS_SENT_INFO		((struct cfs_sent_info *)u.u_tsd[TSD_CFS_KEY])

/*
 * Per-utask locks for MP synchronization.
 */

/*
 * This lock covers miscellaneous Unix-related per-task data:
 *   u.u_ru, u.u_cru, u.logname, u.u_acflag, u.u_rdir, u.u_cmask,
 *   and all members of u.u_rlimit except RLIMIT_CPU.
 */
#define U_HANDY_LOCK() 						\
MACRO_BEGIN							\
{								\
	register struct utask *utask;				\
	utask = u.utask;					\
	if (utask->uu_file_state.utask_need_to_lock)		\
		usimple_lock(&utask->uu_handy_lock);		\
}								\
MACRO_END
#define U_HANDY_UNLOCK() 					\
MACRO_BEGIN							\
{								\
	register struct utask *utask;				\
	utask = u.utask;					\
	if (utask->uu_file_state.utask_need_to_lock)		\
		usimple_unlock(&utask->uu_handy_lock);		\
}								\
MACRO_END

/*
 * multithreaded synchronization to Unix address space parameters:
 *   u.u_curbrk, u.u_minbrk, u.u_lflags, u.u_stack_start,
 *   u.u_stack_end, process sigactions, and POSIX timers
 */
#define U_ADDR_LOCK() 						\
MACRO_BEGIN							\
{								\
	register struct utask *utask;				\
	utask = u.utask;					\
	if (utask->uu_file_state.utask_need_to_lock)		\
		lock_write(&utask->uu_addr_lock);		\
}								\
MACRO_END

#define U_ADDR_UNLOCK() 					\
MACRO_BEGIN							\
{								\
	register struct utask *utask;				\
	utask = u.utask;					\
	if (utask->uu_file_state.utask_need_to_lock)		\
		lock_done(&utask->uu_addr_lock);		\
}								\
MACRO_END

#define U_ADDR_LOCK_TRY()					\
	(u.utask->uu_file_state.utask_need_to_lock ?		\
		lock_try_write(&u.utask->uu_addr_lock) : 1)

/*
 * Unconditional versions of the U_ADDR_LOCK family
 */
#define U_ADDR_LOCK_ALWAYS()					\
MACRO_BEGIN							\
	lock_write(&u.utask->uu_addr_lock);			\
MACRO_END

#define U_ADDR_UNLOCK_ALWAYS()					\
MACRO_BEGIN							\
	lock_done(&u.utask->uu_addr_lock);			\
MACRO_END

/*
 * Unconditional version of U_ADDR_LOCK that targets a proc
 */
#define U_ADDR_LOCK_ALWAYS_PROC(__p__)					\
MACRO_BEGIN								\
	struct utask *utaskp = proc_to_utask(__p__);			\
	lock_write(&utaskp->uu_addr_lock);				\
MACRO_END

#define U_ADDR_UNLOCK_ALWAYS_PROC(__p__)				\
MACRO_BEGIN								\
	struct utask *utaskp = proc_to_utask(__p__);			\
	lock_done(&utaskp->uu_addr_lock);				\
MACRO_END

#endif	/* _KERNEL */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif	/* _SYS_USER_H_ */
