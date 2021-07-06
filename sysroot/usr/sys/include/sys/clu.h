/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: clu.h,v $
 * Revision 1.1.190.4  2006/09/04  05:54:19  Amardeep_Kumar
 * 	Added a flag to CC_CFS_WAIT_FOR_IO (cfs_wait_for_io). QAR 99799.
 *
 * Revision 1.1.190.3  2004/10/29  16:19:31  Douglas_Frank
 * 	Added clu_fuser & clu_ics_table.
 *
 * Revision 1.1.190.2  2004/10/13  19:09:41  Janice_Chang
 * 	Add CC_DMN_NAME_DLM_LOCK_TIMEO callout.  CLD DE_G09132.
 *
 * Revision 1.1.190.1  2003/10/31  22:14:40  Allan_Graves
 * 	Submit v51bsupportos-1007-dgraves
 * 	Changes for sysconfig cluster project
 *
 * Revision 1.1.164.6  2002/04/24  15:47:13  Anthony_Zlotek
 * 	Add CC_CFS_WRITTEN_PAGE callout.
 *
 * Revision 1.1.164.5  2002/01/28  22:51:36  Mike_Milicia
 * 	QAR 91020 : Add new cluster callout CC_CFS_WAIT_FOR_IO (cfs_wait_for_io).
 *
 * Revision 1.1.164.4  2001/10/29  18:18:13  Anthony_Zlotek
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree wcalphaos
 *     User Revision:  Anthony_Zlotek_wcalpha_br:1.1.167.1 Local Ancestor:1.1.164.2
 *    Merge Revision:  wcalphaos_br:1.1.164.3
 *   Common Ancestor:  1.1.164.2
 *
 * Revision 1.1.164.3  2001/10/25  17:31:34  Charles_Rusman
 * 	Change signature of cms_cmsdb_dlm_lock(unlock).
 * 	Replace cms_dmn_name_dlm_lock with cms_dmn_name_dlm_lock_try.
 * 	Part of fix for QAR 82099.
 * 
 * Revision 1.1.167.1  2001/10/25  17:28:30  Anthony_Zlotek
 * 	Add a "stale" flag for use by NFS/CFS cache invalidation.
 * 
 * Revision 1.1.164.2  2001/10/15  20:21:29  Charles_Rusman
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree wcalphaos
 *     User Revision:  Charles_Rusman_wcalpha_br:1.1.166.1 Local Ancestor:1.1.125.11
 *    Merge Revision:  wcalphaos_br:1.1.164.1
 *   Common Ancestor:  1.1.125.11
 * 	[2001/09/27  13:45:01  Charles_Rusman]
 * 	Add wildcat submits.
 * 	- Revision 1.1.135.5  2001/08/17  11:46:34  Charles_Rusman
 *   Add CC_CFS_IS_MOUNT_THREAD.
 *   Part of fix for QAR 89166.
 * 	- Revision 1.1.135.4  2001/07/12  13:58:56  James_Woodward
 *   Merge from Yankee BL8.
 * 	- Revision 1.1.135.3  2001/04/23  20:49:07  Mike_Milicia
 *   Add new cluster callout to mark POSIX msg queue and semaphore files
 *   which have wired pages.
 * 	- Revision 1.1.135.2  2001/04/20  18:28:43  Andrew_Duane
 *   Merge from Yankee BL7.
 * 	- Revision 1.1.135.1  2001/01/18  12:37:20  Charles_Rusman
 *   Add declarations of struct kdm_vnode and
 *   struct kdm_fsetcache to keep compiler happy.
 * 	[2001/09/25  11:58:20  Charles_Rusman]
 * 
 * Revision 1.1.164.1  2001/09/19  15:13:25  Bob_Nelson
 * 	Added support for filesystem freeze.
 * 	wc.storage.002.advfs_quiesce
 * 
 * Revision 1.1.125.11  2001/05/18  18:02:34  Mike_Milicia
 * 	QAR 87526 - Add new cluster callout (CC_CFS_CHECK_CSI) to allow
 * 	msfs_real_syscall() to preallocate CFS_SENT_INFO.
 * 
 * Revision 1.1.125.10  2001/04/04  21:36:18  Anthony_Zlotek
 * 	Add CC_CFS_CLONE_NOTIFY callout.
 * 
 * Revision 1.1.125.9  2000/12/13  21:07:36  David_Akers
 * 	Add callouts (CC_CFS_COW_ENTER/LEAVE) for
 * 	directio/clone support
 * 
 * Revision 1.1.125.8  2000/11/10  03:39:55  Ernie_Petrides
 * 	Fix declarations of "cfs_dmapi_rel_right_vnode" and
 * 	"cfs_dmapi_rel_right_fs" function pointers.
 * 
 * Revision 1.1.125.7  2000/11/09  22:06:07  Bob_Bell
 * 	Added CC_CLU_KILL
 * 
 * Revision 1.1.125.6  2000/11/08  04:04:58  devbld_dmapi
 * 	Add cluster callouts for DMAPI support:    Maria_Vella
 *     - CC_CFS_DMAPI_IOCTL_ENTER
 *     - CC_CFS_DMAPI_IOCTL_LEAVE
 *     - CC_CFS_DMAPI_REL_RIGHT_VNODE
 *     - CC_CFS_DMAPI_REL_RIGHT_FS
 * 
 * Revision 1.1.125.5  2000/10/18  17:02:19  Jonathan_Wistar
 * 	Create CC_START_SHUTDOWN callout, eliminating former function
 * 	pointer "clu_start_shutdown".
 * 
 * Revision 1.1.125.4  2000/10/12  17:14:09  Mike_Milicia
 * 	Add callouts for CFS quota support
 * 
 * Revision 1.1.125.3  2000/10/10  17:36:01  Charles_Rusman
 * 	Remove obsolete cfs_init_stat().
 * 
 * Revision 1.1.125.2  2000/09/27  19:44:21  Anthony_Zlotek
 * 	Add CC_CFS_AWDL_ENABLE cluster callout.
 * 
 * Revision 1.1.125.1  2000/08/18  14:51:05  Charles_Rusman
 * 	Add forward decl. of mntinfo to keep compiler quiet.
 * 
 * Revision 1.1.107.10  2000/03/24  22:23:56  Anthony_Zlotek
 * 	Add CC_CFS_CHECK_CSID cluster callout.
 * 
 * Revision 1.1.107.8  2000/02/07  20:43:16  Dave_King
 * 	Add CC_CHANGE_VTYPE cluster callout.
 * 
 * Revision 1.1.107.7  2000/01/27  14:45:30  Maria_Vella
 * 	Add CFS directio support by removing ZULU_CDIO ifdefs.
 * 
 * Revision 1.1.107.6  2000/01/19  17:33:20  Dave_King
 * 	AutoFS"Merge Information
 *     Merge Revision:  ZULUOS:1.1.107.5
 *     User  Revision:  Dave_King_zautofs_br:1.1.120.2
 *    Common Ancestor:  1.1.107.4
 *     Merge Revision History Comments from Rev : 1.1.107.5
 *     	From Revision 1.1.93.14. Add CC_NFS_IS_SRVDOWN. QAR 76355.
 * 	[2000/01/11  18:42:13  Charles_Rusman]
 *     -------------------------------------------------
 * 	Add CC_GET_CFS_VP callout.
 * 
 * Revision 1.1.107.5  2000/01/11  21:32:27  Charles_Rusman
 * 	From Revision 1.1.93.14. Add CC_NFS_IS_SRVDOWN. QAR 76355.
 * 	[2000/01/11  18:42:13  Charles_Rusman]
 * 
 * Revision 1.1.107.4  2000/01/07  14:53:02  Bob_Bell
 * 	Merge with 'newest' zinc bl3
 * 
 * Revision 1.1.107.3  2000/01/03  15:24:19  Pam_Gaudette
 * 	merge from zinc bl3
 * 
 * Revision 1.1.93.12  1999/12/16  20:52:40  Bob_Bell
 * 	Added libclu member function prototypes
 * 
 * Revision 1.1.93.11  1999/12/13  20:41:57  Bob_Bell
 * Merge Information
 *     Merge Revision:  ZINCOS:1.1.93.10
 *     User  Revision:  Bob_Bell_clu_info_base_br:1.1.116.1
 *    Common Ancestor:  1.1.93.9
 *     Merge Revision History Comments from Rev : 1.1.93.10
 *     	{** Forced Submit **}
 * 	merge
 * 	[1999/12/08  14:29:13  Diane_Delgado]
 * 	add directio callouts
 * 	[1999/12/08  11:34:12  Diane_Delgado]
 *     -------------------------------------------------
 * 	Merge (no changes)
 * 	[1999/12/13  20:41:47  Bob_Bell]
 * 	Changes for new clu_info() interfaces
 * 	[1999/12/10  21:54:46  Bob_Bell]
 * 
 * Revision 1.1.93.9  1999/12/06  18:32:58  Charles_Rusman
 * 	Part of fix for QAR 75721.
 * 	Add support for CC_DEV_DLM_LOCK/UNLOCK.
 * 
 * Revision 1.1.107.2  1999/12/01  18:08:56  James_Woodward
 * 	put ifdef KERNEL around includes of user.h and proc.h.  This
 * 	avoids exporting kernel structure definitions to commands which
 * 	don't need them.  For example... ntp.
 * 
 * Revision 1.1.107.1  1999/11/19  19:11:43  John_H_Williams
 * 	Sync to wave4zuluos"	Sync to wave4zuluos
 * 
 * Revision 1.1.101.1  1999/10/21  21:16:12  Anthony_Zlotek
 * 	Add CC_CFS_UBC_GETOBJ() callout.  Part of fix for
 * 	QAR 74345.
 * 
 * Revision 1.1.93.7  1999/10/14  14:51:52  John_H_Williams
 * 	Merged at submit time"Merge Information
 *     Merge Revision:  ZINCOS:1.1.93.6
 *     User  Revision:  John_H_Williams_versw:1.1.97.1
 *    Common Ancestor:  1.1.93.5
 * 	[1999/10/14  14:51:43  John_H_Williams]
 * 
 * Revision 1.1.93.5  1999/10/07  15:29:52  Mike_Milicia
 * 	Add callout to check if thread is performing operations as part
 * 	of a CFS recovery.
 * 
 * Revision 1.1.93.4  1999/09/30  14:49:17  John_H_Williams
 * 	New Base clu_get_info interfaces
 * 
 * Revision 1.1.93.3  1999/08/26  14:33:59  Charles_Rusman
 * 	Add CC_FLUSHBUFS() callout. Part of fix for
 * 	QAR 73243.
 * 	[1999/08/23  20:04:43  Charles_Rusman]
 * 
 * Revision 1.1.93.2  1999/08/18  23:36:10  Anthony_Zlotek
 * 	Move cfs_ubc_msync() to end of the callout table.
 * 	[1999/08/18  20:34:25  Anthony_Zlotek]
 * 	Added CC_CFS_UBC_MSYNC callout.
 * 	[1999/08/11  20:30:31  Anthony_Zlotek]
 * 
 * Revision 1.1.2.43  1999/06/17  14:00:05  Anthony_Zlotek
 * 	Add new "stop caching" flag for CFS cache purge callout function.
 * 	[1999/06/16  13:56:24  Anthony_Zlotek]
 * 
 * Revision 1.1.2.42  1999/04/23  20:00:50  Rocco_Scavetta
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.2.40 **
 * 		** Merge revision:	1.1.2.41 **
 * 	 	** End **
 * 	Moved CFS_IN_DAEMON macro from ftx_routines.c
 * 	[1999/04/23  00:42:14  Rocco_Scavetta]
 * 
 * Revision 1.1.2.41  1999/04/23  14:07:19  Diane_Delgado
 * 	add CC_GETPFSMP_BLOCK; modify interface to cfs_getpfsmp
 * 	[1999/04/16  14:42:59  Diane_Delgado]
 * 
 * Revision 1.1.2.40  1999/04/14  18:20:35  Seema_Peterson
 * 	Add cfs_domain_change_vol_dev() and cfs_domain_change_vol_done_dev()
 * 	callouts.
 * 	[1999/04/14  14:09:27  Seema_Peterson]
 * 
 * Revision 1.1.2.39  1999/03/28  21:43:51  Geoff_Steckel
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.2.36 **
 * 		** Merge revision:	1.1.2.38 **
 * 	 	** End **
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rSTEELOS **
 * 		** Ancestor revision:	1.1.2.36 **
 * 		** Merge revision:	1.1.2.37 **
 * 	 	** End **
 * 	[1999/03/28  21:39:39  Geoff_Steckel]
 * 	Update to steel bl23
 * 	[1999/03/25  19:23:46  Geoff_Steckel]
 * 
 * Revision 1.1.2.38  1999/03/26  20:46:02  John_H_Williams
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.2.35 **
 * 		** Merge revision:	1.1.2.37 **
 * 	 	** End **
 * 	New clu_get_info interfaces
 * 	[1999/03/26  19:44:42  John_H_Williams]
 * 
 * Revision 1.1.2.37  1999/03/25  16:06:20  Dave_King
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.2.35 **
 * 		** Merge revision:	1.1.2.36 **
 * 	 	** End **
 * 	Rename hash to cdsl_hash, replace misleading comment.
 * 	[1999/03/18  19:23:46  Dave_King]
 * 
 * Revision 1.1.64.4  1999/03/23  21:04:10  Geoff_Steckel
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rSTEELOS **
 * 		** Ancestor revision:	1.1.2.35 **
 * 		** Merge revision:	1.1.2.36 **
 * 	 	** End **
 * 
 * Revision 1.1.64.3  1999/03/23  19:12:50  Geoff_Steckel
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rSTEELOS **
 * 		** Ancestor revision:	1.1.63.3 **
 * 		** Merge revision:	1.1.2.35 **
 * 	 	** End **
 * 
 * Revision 1.1.2.36  1999/03/23  17:27:48  John_Carr
 * 	Use explicit (void) to prototype functions with no arguments.
 * 	[1999/03/22  15:07:01  John_Carr]
 * 
 * Revision 1.1.64.2  1999/03/12  20:35:39  Geoff_Steckel
 * 	add vector definitions for per-domain locking of advfs syscalls
 * 
 * Revision 1.1.2.35  1999/02/09  19:03:46  Ken_Block
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rSTEELOS;PTFCOS_BL3;<> **
 * 		** Ancestor revision:	1.1.2.33 **
 * 		** Merge revision:	1.1.2.34 **
 * 	 	** End **
 * 	[1999/02/09  18:47:14  Ken_Block]
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rSTEELOS;PTFCOS_BL3;<> **
 * 		** Ancestor revision:	1.1.2.32 **
 * 		** Merge revision:	1.1.2.33 **
 * 	 	** End **
 * 	[1999/01/28  19:58:26  Ken_Block]
 * 	Make header C++ compliant.
 * 	[1998/12/29  20:21:21  Ken_Block]
 * 
 * Revision 1.1.2.34  1999/02/05  22:12:45  Per_Wahlstrom
 * 	Decouple CLU_MAXNAMELEN from MAXHOSTNAMELEN.
 * 	For now they have the same value (=256).
 * 	[1999/02/01  20:17:42  Per_Wahlstrom]
 * 
 * Revision 1.1.2.33  1999/01/27  18:41:26  John_H_Williams
 * 	Fix to cdsl table hash entry to make it a u_long
 * 	[1999/01/27  18:38:05  John_H_Williams]
 * 
 * Revision 1.1.63.3  1998/12/24  19:42:45  Per_Wahlstrom
 * 	Temporarily set CLU_MAXNAMELEN to 256
 * 	[1998/12/24  19:06:55  Per_Wahlstrom]
 * 
 * Revision 1.1.63.2  1998/12/22  19:44:24  Mitchell_Condylis
 * 	Set CLU_MAXNAMELEN to 64.
 * 	[1998/12/22  19:43:43  Mitchell_Condylis]
 * 
 * Revision 1.1.2.32  1998/12/15  16:27:00  John_H_Williams
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.2.30 **
 * 		** Merge revision:	1.1.2.31 **
 * 	 	** End **
 * 	Moving all headers back to user level and kernel level
 * 	[1998/12/15  16:05:19  John_H_Williams]
 * 
 * Revision 1.1.2.31  1998/12/15  14:38:36  John_H_Williams
 * 	Fix for hwmgr build problem
 * 	[1998/12/15  14:35:37  John_H_Williams]
 * 
 * Revision 1.1.2.30  1998/12/14  21:55:35  John_H_Williams
 * 	Sync Steel BL21 to TCR EFT code freeze
 * 	[1998/12/14  21:51:31  John_H_Williams]
 * 
 * Revision 1.1.2.29  1998/12/09  22:01:08  John_H_Williams
 * 	clu_get_info changes/fixes for wave4 EFT
 * 	[1998/12/09  21:56:07  John_H_Williams]
 * 
 * Revision 1.1.2.28  1998/12/04  23:40:08  Damon_Hung
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit -visual **
 * 		** Ancestor revision:	1.1.2.26 **
 * 		** Merge revision:	1.1.2.27 **
 * 	 	** End **
 * 	Support remote AdvFS syscalls.
 * 	[1998/12/04  07:43:46  Damon_Hung]
 * 
 * Revision 1.1.2.27  1998/12/04  20:11:27  John_H_Williams
 * 	Syncing Steel BL21 to clu_get_info interface cahnges
 * 	[1998/12/04  20:04:58  John_H_Williams]
 * 
 * Revision 1.1.2.26  1998/11/19  18:53:07  John_H_Williams
 * 	Updated submit to include changes from code review
 * 	[1998/11/19  18:36:23  John_H_Williams]
 * 
 * Revision 1.1.2.25  1998/11/18  16:54:33  Steve_Dickson
 * 	Merged in the following deltas from tcr4os pool.
 * 	 Revision 1.1.9.35  1998/11/10  22:29:04  Andrew_Kahn
 * 	 - Drop dependency/usage of Advfs specific structures.  Use generic
 * 	   void pointers instead.  Qar 64879.
 * 	 - Fix ordering of cluster callouts to sync with Steel nightly.
 * 	 Revision 1.1.9.34  1998/11/09  21:33:36  John_H_Williams
 * 	 Fix returned member state and clu_free_info prototype
 * 	 Revision 1.1.9.33  1998/10/19  15:20:41  John_H_Williams
 * 	 Fix user level usage of clu.h
 * 	 Revision 1.1.9.32  1998/10/12  20:02:04  John_H_Williams
 * 	 Merge tcr4os to Steel bl19
 * 	 Revision 1.1.9.31  1998/10/01  20:43:10  Steve_Dickson
 * 	 Added the clua_getdefaultalias interface.
 * 	[1998/11/18  16:41:19  Steve_Dickson]
 * 
 * Revision 1.1.2.24  1998/11/11  21:22:21  Andrew_Kahn
 * 	- Drop dependency/usage of Advfs specific structures.  Use generic
 * 	  void pointers instead.  Qar 64879.
 * 	- Fix ordering of cluster callouts to sync with tcr4os.
 * 	[1998/11/10  19:44:24  Andrew_Kahn]
 * 
 * Revision 1.1.2.23  1998/09/18  17:06:37  John_H_Williams
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.2.20 **
 * 		** Merge revision:	1.1.2.22 **
 * 	 	** End **
 * 	Syncing Steel bl19 to tcr4os
 * 	[1998/09/18  16:29:38  John_H_Williams]
 * 
 * Revision 1.1.2.22  1998/09/17  19:30:07  Andrew_Kahn
 * 	Don't include msfs_syscall.h; was causing a duplicate definition with
 * 	bs_public.h.  Use 'int' instead of 'opIndexT'.
 * 	[1998/09/17  15:34:15  Andrew_Kahn]
 * 
 * Revision 1.1.2.21  1998/09/16  17:43:55  Andrew_Kahn
 * 	Add cfs_domain_change_vol() and cfs_domain_change_vol_done() callouts.
 * 	[1998/09/14  20:21:33  Andrew_Kahn]
 * 
 * Revision 1.1.2.20  1998/09/04  18:05:51  Martin_Lund
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit -visual **
 * 		** Ancestor revision:	1.1.2.18 **
 * 		** Merge revision:	1.1.2.19 **
 * 	 	** End **
 * 	Synchronize CFS attr, access, and data caches with NFS caches.  QAR 58157
 * 	[1998/09/03  19:27:11  Martin_Lund]
 * 
 * Revision 1.1.2.19  1998/09/03  13:56:15  Rocco_Scavetta
 * 	Version Tagged Files support preparation.
 * 	[1998/09/01  13:43:43  Rocco_Scavetta]
 * 
 * Revision 1.1.2.18  1998/07/21  15:02:47  John_H_Williams
 * 	Fixing CC_CFS_DOMAIN_PANIC undefined build problem
 * 	[1998/07/21  14:10:19  John_H_Williams]
 * 
 * Revision 1.1.2.17  1998/07/20  17:52:10  John_H_Williams
 * 	get_clu_info commnad and message catalog
 * 	[1998/07/20  17:46:57  John_H_Williams]
 * 
 * Revision 1.1.9.23  1998/07/02  12:48:30  Alan_Brunelle
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.33.2 **
 * 		** Merge revision:	1.1.9.22 **
 * 	 	** End **
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rSTEELOS_BL16 -visual **
 * 		** Ancestor revision:	1.1.2.11 **
 * 		** Merge revision:	1.1.33.2 **
 * 	 	** End **
 * 	[1998/07/01  20:17:32  Alan_Brunelle]
 * 
 * Revision 1.1.9.22  1998/06/10  15:17:38  Per_Wahlstrom
 * 	Define CLU_OP in a cluster general file. Used by DRD/CFS.
 * 	[1998/06/09  23:01:35  Per_Wahlstrom]
 * 
 * Revision 1.1.9.21  1998/06/08  13:48:46  Per_Wahlstrom
 * 	Include fcntl.h to avoid compiler warnings for extent
 * 	[1998/06/06  23:06:07  Per_Wahlstrom]
 * 
 * Revision 1.1.9.20  1998/05/27  23:36:40  Per_Wahlstrom
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit -visual **
 * 		** Ancestor revision:	1.1.9.18 **
 * 		** Merge revision:	1.1.9.19 **
 * 	 	** End **
 * 	Make CLU_MAXNAMELEN, node_t available to user
 * 	space and BaseOS.
 * 	[1998/05/27  22:59:49  Per_Wahlstrom]
 * 
 * Revision 1.1.9.19  1998/05/26  15:47:46  John_H_Williams
 * 	reorder to resolve forward references
 * 	[1998/05/26  15:42:32  John_H_Williams]
 * 
 * Revision 1.1.33.2  1998/05/22  20:45:22  Per_Wahlstrom
 * 	Define MAXNAMELEN and include param.h
 * 	[1998/05/20  21:30:50  Per_Wahlstrom]
 * 
 * Revision 1.1.9.18  1998/05/11  17:03:55  Per_Wahlstrom
 * 	Add definitions for shutdown synchronization cluster
 * 	hooks clu_start_shutdown and clu_disk_drain.
 * 	[1998/05/08  17:53:43  Per_Wahlstrom]
 * 
 * Revision 1.1.9.17  1998/05/01  12:01:01  John_H_Williams
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.9.15 **
 * 		** Merge revision:	1.1.9.16 **
 * 	 	** End **
 * 	clu_get_info command and interface
 * 	[1998/04/30  21:10:04  John_H_Williams]
 * 
 * Revision 1.1.9.16  1998/04/29  17:18:15  Susan_Verhulst
 * 	Added a cluster callout for icssvr_uiomove().
 * 	[1998/04/28  16:40:55  Susan_Verhulst]
 * 
 * Revision 1.1.2.14  1998/04/28  21:01:55  Susan_Verhulst
 * 	Added a cluster callout for icssvr_uiomove().
 * 	[1998/04/28  18:21:30  Susan_Verhulst]
 * 
 * Revision 1.1.9.15  1998/04/15  15:21:47  John_H_Williams
 * 	Mount member boot disk on boot_partition
 * 	[1998/04/15  15:20:43  John_H_Williams]
 * 
 * Revision 1.1.2.13  1998/04/14  21:10:58  Steve_Dickson
 * 	Added cluster alias callout for NFS tunneling
 * 	Added CC_FSFLUSH callout.
 * 	[1998/04/14  20:18:15  Steve_Dickson]
 * 
 * Revision 1.1.9.14  1998/04/09  19:22:19  Steve_Dickson
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.2.11 **
 * 		** Merge revision:	1.1.9.13 **
 * 	 	** End **
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rSTEELOS_BL15 **
 * 		** Ancestor revision:	1.1.2.3 **
 * 		** Merge revision:	1.1.2.11 **
 * 	 	** End **
 * 	[1998/04/08  20:57:44  Steve_Dickson]
 * 
 * Revision 1.1.9.13  1998/04/07  19:42:59  Steve_Dickson
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rTCR4OS **
 * 		** Ancestor revision:	1.1.9.11 **
 * 		** Merge revision:	1.1.9.12 **
 * 	 	** End **
 * 	[1998/04/07  17:04:40  Steve_Dickson]
 * 	Added cluster alias callout for NFS tunneling
 * 	[1998/04/07  16:49:34  Steve_Dickson]
 * 
 * Revision 1.1.9.12  1998/04/03  17:02:17  Candy_Gao
 * 	 	** Merge Information **
 * 		** Command used:	bmerge **
 * 		** Ancestor revision:	1.1.9.10 **
 * 		** Merge revision:	1.1.9.11 **
 * 	 	** End **
 * 	[1998/04/03  16:54:28  Candy_Gao]
 * 	Code review changes.
 * 	[1998/04/03  15:12:16  Candy_Gao]
 * 	Added CC_FSFLUSH callout.
 * 	[1998/03/11  15:05:24  Candy_Gao]
 * 
 * Revision 1.1.2.12  1998/03/16  14:45:29  Maria_Vella
 * 	Added two cluster callouts: cms_find_cluster_domain_id and
 * 	cms_find_cluster_fsid along with associated macros.
 * 	[1998/03/10  17:54:27  Maria_Vella]
 * 
 * Revision 1.1.9.11  1998/03/11  17:48:57  Maria_Vella
 * 	Added CC_FIND_CLUSTER_DOMAIN_ID and CC_FIND_CLUSTER_FSID callouts.
 * 	[1998/03/10  18:23:45  Maria_Vella]
 * 
 * Revision 1.1.2.11  1998/01/07  14:46:44  Steve_Dickson
 * 	Added clucall_stat enum
 * 	Added the cluall_vector structure
 * 	Added the external declarations of clucall_load() and clucall_error()
 * 	[1998/01/06  21:56:47  Steve_Dickson]
 * 
 * Revision 1.1.9.10  1998/01/05  22:53:11  Steve_Dickson
 * 	Added clucall_stat enum
 * 	Added the cluall_vector structure
 * 	Added the external declarations of clucall_load() and clucall_error()
 * 	[1998/01/05  19:45:36  Steve_Dickson]
 * 
 * Revision 1.1.2.10  1997/12/19  22:17:42  Paul_Park
 * 	Add non _KERNEL definitions of MEMBER_ROOT_STR, et. al. with
 * 	a CLU_ prefix.
 * 	[1997/12/17  22:10:59  Paul_Park]
 * 
 * Revision 1.1.9.9  1997/12/16  15:14:21  Paul_Park
 * 	Add non _KERNEL definitions of MEMBER_ROOT_STR, et. al. with
 * 	a CLU_ prefix.
 * 	[1997/12/12  22:03:23  Paul_Park]
 * 
 * Revision 1.1.2.9  1997/11/26  20:28:47  Dave_King
 * 	Add CC_KLM_CALLBACKS callout.
 * 	[1997/11/18  02:18:28  Dave_King]
 * 
 * Revision 1.1.9.8  1997/11/24  23:19:08  Dave_King
 * 	Add CC_KLM_CALLBACKS callout.
 * 	[1997/11/18  16:53:09  Dave_King]
 * 
 * Revision 1.1.9.7  1997/10/14  21:54:03  Steve_Dickson
 * 	Added callout macros for NFS
 * 	[1997/10/14  21:17:00  Steve_Dickson]
 * 
 * Revision 1.1.2.8  1997/10/14  14:30:29  Candy_Gao
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.2.4 **
 * 		** Merge revision:	1.1.2.7 **
 * 	 	** End **
 * 	Added two cluster callouts and macros for them.
 * 	[1997/10/07  20:25:47  Candy_Gao]
 * 
 * Revision 1.1.9.5  1997/10/13  23:01:48  Stuart_Hollander
 * 	Add kevm entries to switch
 * 	[1997/10/13  22:54:03  Stuart_Hollander]
 * 
 * Revision 1.1.9.4  1997/10/13  21:58:36  Dave_King
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.9.2 **
 * 		** Merge revision:	1.1.9.3 **
 * 	 	** End **
 * 	Add clu_cluster_mount, clu_cluster_unmount, clu_mount_type,
 * 	associated CC_ macro's, and include ifndef.
 * 	[1997/10/08  02:23:17  Dave_King]
 * 
 * Revision 1.1.2.7  1997/10/13  21:32:01  Dave_King
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.2.5 **
 * 		** Merge revision:	1.1.2.6 **
 * 	 	** End **
 * 	Add clu_cluster_mount, clu_cluster_unmount, clu_mount_type,
 * 	associated CC_ macro's, and include ifndef.
 * 	[1997/10/09  18:36:02  Dave_King]
 * 
 * Revision 1.1.2.6  1997/10/13  20:40:25  Steve_Dickson
 * 	Added callout macros for NFS
 * 	[1997/10/09  20:31:04  Steve_Dickson]
 * 
 * Revision 1.1.9.3  1997/10/09  13:28:27  Candy_Gao
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.2.3 **
 * 		** Merge revision:	1.1.9.2 **
 * 	 	** End **
 * 	Modified callouts based on code review.
 * 	[1997/10/07  17:49:19  Candy_Gao]
 * 	Added two cfs callouts, clu_cfs_getpfsmp and
 * 	clu_cfs_getpfsvp. Added two macros for these
 * 	two callouts.
 * 	[1997/09/26  21:34:30  Candy_Gao]
 * 
 * Revision 1.1.2.5  1997/10/08  18:54:59  Stuart_Hollander
 * 	Add kevm entries to switch
 * 	[1997/10/06  15:57:43  Stuart_Hollander]
 * 	Revision 1.1.2.4  1997/10/03  13:58:10  Dave_King
 * 	Rework the cluster callout mechanism a bit, define cluster
 * 	callout (CC_) macros.
 * 	[1997/09/29  18:45:37  Dave_King]
 * 
 * Revision 1.1.2.4  1997/10/03  13:58:10  Dave_King
 * 	Rework the cluster callout mechanism a bit, define cluster
 * 	callout (CC_) macros.
 * 	[1997/09/29  18:45:37  Dave_King]
 * 
 * Revision 1.1.9.2  1997/09/30  17:14:39  Dave_King
 * 	Rework the cluster callout mechanism a bit, define cluster
 * 	callout (CC_) macros.
 * 	[1997/09/29  19:49:59  Dave_King]
 * 
 * Revision 1.1.2.3  1997/08/26  20:19:41  John_H_Williams
 * 	BASE/TCR user and kernel interfaces
 * 	[1997/08/26  20:14:36  John_H_Williams]
 * 
 * Revision 1.1.2.2  1997/07/25  14:17:39  John_H_Williams
 * 	Version switch submit
 * 	[1997/07/25  14:16:11  John_H_Williams]
 * 
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: clu.h,v $ $Revision: 1.1.190.4 $ (DEC) $Date: 2006/09/04 05:54:19 $
 */

#ifndef _SYS_CLU_H_
#define _SYS_CLU_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/time.h>	
#include <sys/param.h>	
#include <sys/vnode.h>	
#include <sys/mount.h>	
#include <sys/fcntl.h>	
#include <mach/boolean.h>
    
#ifdef _KERNEL
#include <sys/proc.h>	
#include <sys/user.h>	
#include <vm/vm_ubc.h>
#include <msfs/bs_public.h>
#endif

#define CLU_NOT_CONFIGURED	-1		/* TCR code not configured */

/*
 *  The memberid related definitions.  memberid is a base value but we
 *  use it to distinguish cluster nodes.
 */
typedef int             memberid_t;     /* Does this belong here        */
typedef memberid_t      node_t;         /* should be the same as a memberid */

/*
 * Valid operations for DRD/CFS attributes.
 * For details see <io/drd/drd_user.h> and <cfs/cfs_user.h>
 */
typedef enum { CLU_GET = 0,
               CLU_SET = 1 } CLU_OP;

/* Version Tagged Files support */
#define DEC_VERSION_TAG     "DEC_VERSION_TAG"   /* version tag property string */
#define DEC_VERSION_TAG_VALUE (int) (-1)        /* Property value */
#define VERSION_TAG_PREFIX  ".Old.."            /* version tag filename prefix */



/********************** KERNEL DEFINITIONS *********************************/
#ifdef _KERNEL
/*********************** KERNEL SWITCH TABLE CALLOUTS **********************/
/*	Conditional call on whether this system configured for clusters	   */	
/* if(clu_is_ready())        						   */
/*    error = (*clu_call->clu_do_cluster_become_member_stuff)(arg0, arg1); */
/*								     	   */
/*	Conditional call on whether this system is a cluster member	   */	
/* if(clu_is_member())     						   */
/*    error = (*clu_call->clu_do_cluster_member_stuff)(arg0, arg1, arg2);  */
/***************************************************************************/

#define CFS_IN_DAEMON() ((u.u_procp->p_flag & SSYS) && \
                                (u.u_comm[0] == 'i') && \
                                (u.u_comm[1] == 'c') && \
                                (u.u_comm[2] == 's'))

/****************************************************************/
/* clu_base_swtab - cluster callout table 	      		*/
/*								*/
/* Description - This table contains reference pointers to  	*/
/*	routines used in the "OSF" base kernel product that are	*/
/*	delivered by the cluster "TCR" product.	The clubase 	*/
/*	cfg subsystem configuration will setup this table during*/
/*	the subsystem configuration stage early in the boot.	*/
/****************************************************************/

struct in_addr;
struct mntinfo;
struct kdm_vnode;
struct kdm_fsetcache;

struct clu_base_swtab {
    int (*clu_getsysinfo)		/* CC_GETSYSINFO */
		__((struct proc *p, void *args, long *retval));	

    int (*clu_setsysinfo)		/* CC_SETSYSINFO */
		__((struct proc *p, void *args, long *retval));	

    void (*clu_nfspurgecaches)          /* CC_NFS_PURGECACHES */
                __((struct vnode *vp, int type, u_long *size));

    long (*clu_nfsattrdiff)             /* CC_NFS_ATTRDIFF */
                __((vattr_t *a1, vattr_t *a2));

    void (*clu_nfssrvdown)              /* CC_NFS_SRVDOWN */
                __((vnode_t *pvp));

    void (*clu_nfssrvup)                /* CC_NFS_SRVUP */
                __((vnode_t *pvp));

    int (*clu_cluster_mount)		/* CC_CLUSTER_MOUNT */
		__((vnode_t *cvp, long type, char *dir, long flags,
		    caddr_t data, long *retval, tag_t *tags,
		    struct mount **mpp));

    int (*clu_cluster_unmount)		/* CC_CLUSTER_UNMOUNT */
		__((struct vnode *vp, struct mount *mp, int flags));

    int (*clu_mount_type)		/* CC_MOUNT_TYPE */
		__((struct mount *mp));

    int	(*clu_kevm_ioctl_user_to_kernel)
		__((dev_t dev, unsigned int com, caddr_t data, int flag));

    int	(*clu_kevm_ioctl_test_hook)
		__((dev_t dev, unsigned int com, caddr_t data, int flag));

    int	(*clu_kevm_delivery_thread)
		__((void));

    int (*cfs_getpfsmp)			/* CC_GETPFSMP */
		__((struct mount *mp, struct mount **mpp, int block));

    int (*cfs_getpfsvp)			/* CC_GETPFSVP */
		__((struct vnode *vp, struct vnode **vpp));

    int (*clu_klm_callbacks)		/* CC_KLM_CALLBACKS */
		__((vnode_t *vp, void *lh, void *eld));

    int (*cms_find_cluster_domain_id)	/* CC_FIND_CLUSTER_DOMAIN_ID */
		__((void *domainid));

    int (*cms_find_cluster_fsid) 	/* CC_FIND_CLUSTER_FSID */
		__((fsid_t fsid));

    void (*cfs_blkrsrv_flush)		/* CC_FSFLUSH */
		__((struct mount *mp, int flag));

    int (*cms_get_fsid_server)      /* CC_GET_FSID_SERVER */
                __((fsid_t *fsp, node_t *memberidp));

    int (*clua_isalias)
                __((struct in_addr)); /* CC_CLUA_ISALIAS */

    int (*clua_getdefaultalias)
                __((struct in_addr *)); /* CC_CLUA_GETDEFAULTALIAS */

    int (*clua_callout_register) /* CC_CLUA_CALLOUT_REGISTER */
                __((int (*func)(), u_short proto, in_port_t port, int op));

    int (*icssvr_uiomove)		/* CC_ICSSVR_UIOMOVE */
		__((uchar *cp, int n, uio_rw_t rwflag, struct uio *uio));
 
    int (*cfs_domain_panic)             /* CC_CFS_DOMAIN_PANIC */
                __((char* domainName, int dpanic_flags));

    struct mount * (*cms_dmn_name_to_mp)	/* CC_DMN_NAME_TO_MP */
		__((char *dmn_name));

    struct mount * (*cms_dmn_id_to_mp)	/* CC_DMN_ID_TO_MP */
		__((void *domainid));

    void (*clubase_start_shutdown)	/* CC_START_SHUTDOWN */
		__((int reason, int howto));

    int (*cms_shutdown)         /* CC_SHUTDOWN */
                __((void));

    int (*cfs_domain_change_vol)	/* CC_DOMAIN_CHANGE_VOL */
                __((void *op, char *domainName, char *deviceName));

    int (*cfs_domain_change_vol_done)	/* CC_DOMAIN_CHANGE_VOL_DONE */
                __((void *op, char *domainName, char *deviceName, int sts));

    int (*cfs_relo_requested)   /* CC_CFS_RELO_REQUESTED */
                __((struct mount *mp));

    int (*clu_msfs_syscall_fship)       /* CC_MSFS_SYSCALL_FSHIP */
                __((struct mount *mp, int op, void *params, int *at_server));

    struct mount * (*cfs_path_to_mp)  /* CC_PATH_TO_MP */
                __((char *path));

    struct mount * (*cfs_fd_to_mp)    /* CC_FD_TO_MP */
                __((int fd));

    int (*cms_cmsdb_dlm_lock)         /* CC_CMSDB_DLM_LOCK */
		__((int mode, void*));

    int (*cms_cmsdb_dlm_unlock)         /* CC_CMSDB_DLM_UNLOCK */
                __((void *));

    int (*cms_dmn_name_dlm_lock_timeo)        /* CC_DMN_NAME_DLM_LOCK_TIMEO */
                __((char *domainname, int exclusive, void *, unsigned int));

    int (*cms_dmn_name_dlm_unlock)      /* CC_DMN_NAME_DLM_UNLOCK */
                __((void *));

    int (*cms_mp_to_dmn_name)           /* CC_MP_TO_DMN_NAME */
                __((struct mount *mp, char *name));

    int (*cfs_domain_change_vol_dev)    /* CC_DOMAIN_CHANGE_VOL_DEV */
                __((void *op, char *domainName, dev_t dev));

    int (*cfs_domain_change_vol_done_dev)/* CC_DOMAIN_CHANGE_VOL_DONE_DEV*/
                __((void *op, char *domainName, dev_t dev, int sts));
    
    int (*cfs_ubc_msync)        /* CC_CFS_UBC_MSYNC */
                __((vm_ubc_object_t vop, vm_offset_t offset,
		    vm_size_t len, int flags));

    int (*cms_flushbufs)        /* CC_FLUSHBUFS */
                __((void));
    int (*cfs_is_recovery_thread)	/* CC_CFS_IS_RECOVERY_THREAD */
                __((int flag));
    int (*cfs_directio_raw)    /* CC_CFS_RAWIO */
		__((struct buf *bp));
    int (*clu_versw)			/* CC_CLU_VERSW	*/
		__((int option));
    vm_ubc_object_t (*cfs_ubc_getobj)	/* CC_CFS_UBC_GETOBJ */
	        __((vm_ubc_object_t vop));
    int (*cms_dev_dlm_lock)   		/* CC_DEV_DLM_LOCK */
		__((dev_t dev, int mode));
    int (*cms_dev_dlm_unlock) 		/* CC_DEV_DLM_UNLOCK */
		__((dev_t dev));
    int (*cfs_condio_cc_excl_mode_enter) /* CC_CFS_CONDIO_EXCL_MODE_ENTER */
                __((struct vnode *vp));
    int (*cfs_condio_cc_excl_mode_leave) /* CC_CFS_CONDIO_EXCL_MODE_LEAVE */
                __((struct vnode *vp));
    int (*cfs_is_nfssrvdown)		/* CC_NFS_IS_SRVDOWN */
		__((struct mntinfo *mi));

    int (*cfs_get_cfs_vp)			/* CC_GET_CFS_VP */
		__((struct vnode *vp, struct vnode **vpp));

    int (*cfs_change_vtype)			/* CC_CHANGE_VTYPE */
		__((struct vnode *vp, enum vtype vnode_type));
    int (*cfs_check_caller_csid)		/* CC_CFS_CHECK_CSID */
		__(());
    int (*cfs_awdl_enable)		/* CC_CFS_AWDL_ENABLE */
		__((struct vnode *vp));
    int (*cfs_quota_ignore)            /* CC_QUOTA_IGNORE */
                __((void));
    int (*cfs_quota_set_error)         /* CC_QUOTA_SET_ERROR */
                __((int qtype, int errtype));
    int (*cfs_dmapi_ioctl_enter)                /* CC_CFS_DMAPI_IOCTL_ENTER */
                __((int cmd, void *argsp, void **clu_work));
    int (*cfs_dmapi_ioctl_leave)                /* CC_CFS_DMAPI_IOCTL_LEAVE */
                __((int cmd, void *argsp,int ret, void *clu_work));
    void (*cfs_dmapi_rel_right_vnode)	/* CC_CFS_DMAPI_REL_RIGHT_VNODE */
                __((struct kdm_vnode *kvp));
    void (*cfs_dmapi_rel_right_fs)	/* CC_CFS_DMAPI_REL_RIGHT_FS */
                __((struct kdm_fsetcache *fcp));
    int (*clu_kill)			/* CC_CLU_KILL */
		__((struct proc *cp, pid_t pid, int sig));
    int (*cfs_cow_mode_enter)      /* CC_CFS_COW_MODE_ENTER */
		__((fsid_t fsid, bfTagT tag));
    int (*cfs_cow_mode_leave)      /* CC_CFS_COW_MODE_LEAVE */
		__((fsid_t fsid, bfTagT tag));
    int (*cfs_clone_notify)      /* CC_CFS_CLONE_NOTIFY */
		__((fsid_t fsid, u_int cloneflags));
    void (*cfs_check_csi)           /* CC_CFS_CHECK_CSI */
		__(());
    int (*cfs_freezefs)           /* CC_FREEZEFS */
		__((struct mount *mp, u_long flags, int timeout));
    int (*cfs_set_wired_pages)      /* CC_CFS_SET_WIRED_PAGES */
		__((vm_map_t map, vm_offset_t start, int onoff));
    int (*cfs_is_mount_thread)  /* CC_CFS_IS_MOUNT_THREAD */
		__(());
    int (*cfs_wait_for_io)           /* CC_CFS_WAIT_FOR_IO */
		__((struct vnode *vp, int flag));
    int (*cfs_written_page)           /* CC_CFS_WRITTEN_PAGE */
		__((struct vm_page *pp));
    int (*clu_kmodcall)                 /* CC_CLU_KMODCALL */
                __((caddr_t subsys, long op,
                    caddr_t in_buf, size_t in_len,
                    caddr_t out_buf, size_t out_len));
    int (*cfs_max_dmn_dlm_lock_timeo)     /* CC_MAX_DMN_DLM_LOCK_TIMEO */
		__(());
    int (*clu_ics_table)           /* CC_CLU_ICS_TABLE */
        __((struct proc *pp, void *args, void *privs, long *retvalp));
    int (*clu_fuser)               /* CC_CLU_FUSER */
        __((struct proc *pp, void *argsp, long *retvalp));
}; 

/*
 * Table pointer is set by clubase configuration
 */
extern struct clu_base_swtab *clu_call;

/*
 * Hide the ugliness of the cluster callout (CC_) complexity.
 */
#define CC_GETSYSINFO(p, args, retval) 	\
		(*clu_call->clu_getsysinfo)((p), (args), (retval))

#define CC_SETSYSINFO(p, args, retval) 	\
		(*clu_call->clu_setsysinfo)((p), (args), (retval))

#define CLU_KEVM_IOCTL_USER_TO_KERNEL(dev, com, data, flag)	\
	(*clu_call->clu_kevm_ioctl_user_to_kernel)((dev), (com), (data), (flag));

#define CLU_KEVM_IOCTL_TEST_HOOK(dev, com, data, flag)	\
	(*clu_call->clu_kevm_ioctl_test_hook)((dev), (com), (data), (flag));

#define CLU_KEVM_DELIVERY_THREAD()		\
	(*clu_call->clu_kevm_delivery_thread)();

#define CC_CLUSTER_MOUNT(cvp, type, dir, flags, data, retval, tags, mpp) \
		(*clu_call->clu_cluster_mount)				 \
			((cvp), (type), (dir), (flags), (data), (retval), (tags), (mpp))

#define CC_CLUSTER_UNMOUNT(vp, mp, flags) \
		(*clu_call->clu_cluster_unmount) ((vp), (mp), (flags))

#define CC_MOUNT_TYPE(mp) (short) 				\
		((mp->m_stat.f_type == MOUNT_CFS) 	   ?	\
			((*clu_call->clu_mount_type) (mp)) :	\
			(mp->m_stat.f_type))

#define CC_GETPFSMP(mp, mpp)		\
		(*clu_call->cfs_getpfsmp)((mp), (mpp), 0)

#define CC_GETPFSMP_BLOCK(mp, mpp)              \
                (*clu_call->cfs_getpfsmp)((mp), (mpp), 1)


#define CC_GETPFSVP(vp, vpp)		\
		(*clu_call->cfs_getpfsvp)((vp), (vpp))

#define CC_NFS_PURGECACHES(vp, type, size) 	\
		(*clu_call->clu_nfspurgecaches)((vp), (type), (size))

#define CC_NFS_ATTRDIFF(a1, a2) 	\
		(*clu_call->clu_nfsattrdiff)((a1), (a2))

#define CC_NFS_SRVDOWN(pvp) 	\
		(*clu_call->clu_nfssrvdown)((pvp))

#define CC_NFS_SRVUP(pvp) 	\
		(*clu_call->clu_nfssrvdown)((pvp))

#define CC_KLM_CALLBACKS(vp, lh, eld) 	\
		(*clu_call->clu_klm_callbacks)((vp), (lh), (eld))

#define CC_FIND_CLUSTER_DOMAIN_ID(domainid)	\
		(*clu_call->cms_find_cluster_domain_id)((domainid))

#define CC_FIND_CLUSTER_FSID(fsid)   	\
		(*clu_call->cms_find_cluster_fsid)((fsid))

#define CC_GET_FSID_SERVER(fsp, memberidp) \
		(*clu_call->cms_get_fsid_server)((fsp), (memberidp))

#define CC_CLUA_ISALIAS(addr)   	\
		(*clu_call->clua_isalias)((addr))

#define CC_CLUA_GETDEFAULTALIAS(addr)   	\
		(*clu_call->clua_getdefaultalias)((addr))

#define CC_CLUA_CALLOUT_REGISTER(func, proto, port, opt) \
		(*clu_call->clua_callout_register)((func), (proto), (port), (opt))

#define CC_FSFLUSH(mp, flag)		\
		(*clu_call->cfs_blkrsrv_flush)((mp), (flag))

#define CC_ICSSVR_UIOMOVE(cp, n, uio_rw, uio)   \
		(*clu_call->icssvr_uiomove)(cp, n, uio_rw, uio)

#define CC_CFS_DOMAIN_PANIC(domainName, dpanic_flags)           \
                (*clu_call->cfs_domain_panic)((domainName), (dpanic_flags))

#define CC_DMN_ID_TO_MP(domainid)	\
		(*clu_call->cms_dmn_id_to_mp)((domainid))

#define CC_DMN_NAME_TO_MP(dmn_name)	\
		(*clu_call->cms_dmn_name_to_mp)((dmn_name))

#define CC_START_SHUTDOWN(reason, howto) \
		(*clu_call->clubase_start_shutdown)((reason, howto))

#define CC_SHUTDOWN(mp) \
                (*clu_call->cms_shutdown)()

#define CC_DOMAIN_CHANGE_VOL(op, domainName, deviceName)		\
                (*clu_call->cfs_domain_change_vol)			\
			((op), (domainName), (deviceName))

#define CC_DOMAIN_CHANGE_VOL_DONE(op, domainName, deviceName, status)	\
                (*clu_call->cfs_domain_change_vol_done)			\
			((op), (domainName), (deviceName), (status))

#define CC_DOMAIN_CHANGE_VOL_DEV(op, domainName, dev)           \
                (*clu_call->cfs_domain_change_vol_dev)          \
                        ((op), (domainName), (dev))

#define CC_DOMAIN_CHANGE_VOL_DONE_DEV(op, domainName, dev, status)      \
                (*clu_call->cfs_domain_change_vol_done_dev)             \
                        ((op), (domainName), (dev), (status))

#define CC_CFS_RELO_REQUESTED(mp)       \
                (*clu_call->cfs_relo_requested)                 \
                        ((mp))

#define CC_CFS_UBC_MSYNC(vop, offset, len, flags)          \
                (*clu_call->cfs_ubc_msync)                 \
                        ((vop), (offset), (len), (flags))

#define CC_MSFS_SYSCALL_FSHIP(mp, op, buf, at_server) 	\
                (*clu_call->clu_msfs_syscall_fship)	\
			((mp), (op), (buf), (at_server))

#define CC_PATH_TO_MP(path)     \
                (*clu_call->cfs_path_to_mp)((path))

#define CC_FD_TO_MP(fd)       \
                (*clu_call->cfs_fd_to_mp)((fd))

#define CC_CMSDB_DLM_LOCK(mode,lock)		\
	(*clu_call->cms_cmsdb_dlm_lock)((mode), (lock));

#define CC_CMSDB_DLM_UNLOCK(lock)		\
	(*clu_call->cms_cmsdb_dlm_unlock)((lock));

#define CC_DMN_NAME_DLM_LOCK_TIMEO(domainname, block, lock, timeo) \
        (*clu_call->cms_dmn_name_dlm_lock_timeo)((domainname),(block),(lock),\
                (timeo))

#define CC_DMN_NAME_DLM_UNLOCK(lock) \
        (*clu_call->cms_dmn_name_dlm_unlock)((lock))

#define CC_MP_TO_DMN_NAME(mp, name) \
        (*clu_call->cms_mp_to_dmn_name)((mp), (name))

#define CC_FLUSHBUFS()		\
        (*clu_call->cms_flushbufs)()

#define CC_CFS_IS_RECOVERY_THREAD(flag) \
        (*clu_call->cfs_is_recovery_thread)(flag)

#define CC_CFS_RAWIO(bp)        \
        (*clu_call->cfs_directio_raw) ((bp))

#define CC_CLU_VERSW(option) \
	(*clu_call->clu_versw)(option)
    
#define CC_CFS_UBC_GETOBJ(obj) \
        (*clu_call->cfs_ubc_getobj) ((obj))

#define CC_DEV_DLM_LOCK(dev, mode) \
	(*clu_call->cms_dev_dlm_lock) ((dev), (mode))

#define CC_DEV_DLM_UNLOCK(dev) \
	(*clu_call->cms_dev_dlm_unlock) ((dev))

#define CC_CFS_CONDIO_EXCL_MODE_ENTER(vp) \
        (*clu_call->cfs_condio_cc_excl_mode_enter)((vp))

#define CC_CFS_CONDIO_EXCL_MODE_LEAVE(vp) \
        (*clu_call->cfs_condio_cc_excl_mode_leave)((vp))

#define CC_NFS_IS_SRVDOWN(mi) \
	(*clu_call->cfs_is_nfssrvdown)((mi))

#define CC_GET_CFS_VP(vp, vpp)		\
		(*clu_call->cfs_get_cfs_vp)((vp), (vpp))

#define CC_CHANGE_VTYPE(vp, vnode_type)		\
		(*clu_call->cfs_change_vtype)((vp), (vnode_type))

#define CC_CFS_CHECK_CSID(void)		\
		(*clu_call->cfs_check_caller_csid)()

#define CC_CFS_AWDL_ENABLE(pvp)	\
		(*clu_call->cfs_awdl_enable)((pvp))

#define CC_QUOTA_IGNORE()   \
        (*clu_call->cfs_quota_ignore)()

#define CC_QUOTA_SET_ERROR(qtype, errtype)    \
        (*clu_call->cfs_quota_set_error)((qtype), (errtype))

#define CC_CFS_DMAPI_IOCTL_ENTER(cmd, argsp, clu_work)  \
        (*clu_call->cfs_dmapi_ioctl_enter)((cmd), (argsp), (clu_work))

#define CC_CFS_DMAPI_IOCTL_LEAVE(cmd, argsp, ret, clu_work)     \
        (*clu_call->cfs_dmapi_ioctl_leave)((cmd), (argsp), (ret), (clu_work))

#define CC_CFS_DMAPI_REL_RIGHT_VNODE(kvp)       \
        (*clu_call->cfs_dmapi_rel_right_vnode)((kvp))

#define CC_CFS_DMAPI_REL_RIGHT_FS(fcp)  \
        (*clu_call->cfs_dmapi_rel_right_fs)((fcp))

#define CC_CLU_KILL(cp, pid, sig) \
	(*clu_call->clu_kill)((cp), (pid), (sig))
	
#define CC_CFS_COW_MODE_ENTER(fsid, tag) \
	(*clu_call->cfs_cow_mode_enter)((fsid), (tag))

#define CC_CFS_COW_MODE_LEAVE(fsid, tag) \
	(*clu_call->cfs_cow_mode_leave)((fsid), (tag))

#define CC_CFS_CLONE_NOTIFY(fsid, cloneflag) \
	(*clu_call->cfs_clone_notify)((fsid), (cloneflag))

#define CC_CFS_CHECK_CSI() \
	(*clu_call->cfs_check_csi)()

#define CC_FREEZEFS(mp, flags, timeout) \
	(*clu_call->cfs_freezefs)((mp), (flags), (timeout))

#define CC_CFS_SET_WIRED_PAGES(map, start, onoff) \
	(*clu_call->cfs_set_wired_pages)((map), (start), (onoff))

#define CC_CFS_IS_MOUNT_THREAD(flag) \
        (*clu_call->cfs_is_mount_thread)()

#define CC_CFS_WAIT_FOR_IO(vp, flag)       \
        (*clu_call->cfs_wait_for_io)((vp), (flag))

#define CC_CFS_WRITTEN_PAGE(pp)       \
        (*clu_call->cfs_written_page)((pp))

#define CC_CLU_KMODCALL(subsys, op, in_buf, in_len, out_buf, out_len) \
        (*clu_call->clu_kmodcall)((subsys), (op), (in_buf), (in_len), \
                (out_buf), (out_len))

#define CC_MAX_DMN_DLM_LOCK_TIMEO()       \
        (*clu_call->cfs_max_dmn_dlm_lock_timeo)()

#define CC_CLU_ICS_TABLE(p, args, privs, retval) \
        (*clu_call->clu_ics_table)((p), (args), (privs), (retval))

#define CC_CLU_FUSER(p, args, retval) \
        (*clu_call->clu_fuser)((p), (args), (retval))

boolean_t	clu_is_ready(void);
boolean_t	clu_is_member(void);
int		clu_callout_stub(void);


#define MEMBER_ROOT_STR "/cluster/members/"
#define MEMBER_ROOT_STRLEN      17

/*      clu_versw       options */
#define VERSW_JOIN_SET          1
#define VERSW_CHECK_SET         2
#define VERSW_SWITCH_SET        3

/*  flag for CC_FSFLUSH */
#define FULL		0x00
#define CHFSET		0x01
#define RMVOL		0x02
#define	C_DONE		0x04
#define R_DONE		0x08
#define CLONE		0x10

/* flags for CC_CFS_CLONE_MODE */
#define CLONE_DELETE  0x0
#define CLONE_CREATE  0x1

/*
 * Cluster hooks for boot() function
 */
extern void    (*clu_disk_drain)(void);

/* flags for CC_NFS_PURGECACHE */ 
#define ATTR_CACHE	0x0
#define DATA_CACHE	0x1
#define ACCESS_CACHE	0x2
#define STOP_CACHING	0x4
#define STALE_FILE	0x8

/* The following is the lookup table entry structure for the cdsl's
 * and their replacement strings. The cdsl_table resides in vfs_lookup.c
 */

struct cdsl_tab_entry  {
        char *cdsl_var;      /* A pointer to the variable string which is to be replaced.
                                It must begin with '{' and end with '}' */
        int cdsl_var_len;    /* The length of the string to be replaced (including delimiters) */
        char *cdsl_val;      /* A pointer to the string value of this cdsl which replaces the cdsl
                                variable in the path element being processed. '\0' terminated */
        int cdsl_val_len;    /* The length of the replacement string */
        u_long cdsl_hash;    /* The computed hash value for the replacement
                              * string. The hash value must be calculated by
                              * calling vfs_name_hash().
                              */
};

typedef struct cdsl_tab_entry cdsl_tab_t;

#endif	/*  _KERNEL  */

/* connection manager states */

typedef enum {
    cnx_unknown_state = 0,      /* UNKNOWN */
    cnx_new_node = 1,           /* NEW: newly discovered node */
    cnx_potential_member = 2,   /* POTENTIAL: full connections
                               established.  communication state == 1 */
    cnx_member = 3,             /* MEMBER: active card carrying member */
    cnx_partitioned_member = 4, /* PARTITIONED: communication failure.
                               communication state == 0 */
    cnx_member_removed = 5,     /* REMOVED: member removed from cluster */
    cnx_invalid_state = 6       /* INVALID: invalid/illegal state */
} mbr_state;


/************************** USER DEFINITIONS ************************/
#ifndef _KERNEL
/********************************************************/
/* clu_info definitions                                 */
/********************************************************/
/* number of different types of information             */
/* each type can return its own information set         */

/* cluster information and option types                 */

#define CLU_INFO_GENERAL             1   /* used by clu_get_info as a general query option */
#define CLU_INFO_MEMBSTATE           2   /* used to determine if members are UP or configured */
#define CLU_INFO_LIMITS              3   /* used to set limits on memberids and supported members*/
#define CLU_INFO_MEMBER_BY_ID        4   /* used to return information for a member specified by memberid */
#define CLU_INFO_MEMBER_BY_NAME      5   /* used to return information for a member specified by hostname */
#define CLU_INFO_CLU_NAME            6   /* used to return the cluster name */
#define CLU_INFO_INTERNAME_BY_ID     7   /* used to return interconnect name given memberid */
#define CLU_INFO_INTERNAME_BY_NAME   8   /* used to return interconnect name given hostname */
#define CLU_INFO_MEMBERID_BY_ID      9   /* used to return memberid given hostname */
#define CLU_INFO_MEMBERID_BY_NAME   10   /* used to return memberid given memberid */
#define CLU_INFO_HOSTNAME_BY_ID     11   /* used to return hostname given memberid */
#define CLU_INFO_HOSTNAME_BY_NAME   12   /* used to return hostname given hostname */
#define CLU_INFO_NODENAME_BY_ID     13   /* used to return CNX node name given memberid */
#define CLU_INFO_NODENAME_BY_NAME   14   /* used to return CNX node name given hostname */
#define CLU_INFO_MEMBLIST           15   /* used to return list of members (hostnames) */
#define CLU_INFO_MY_ID              16   /* used to return member id for current system */

struct clucall_vector {
	char *name;             /* name of the routine in shared library */
	void *ptr_to_vector;   /* pointer to named routine */
};

typedef enum {
	CLUCALL_SUCCESS = 0,
	CLUCALL_DLOPEN,
	CLUCALL_DLSYM,
	CLUCALL_NOTCONFIG
} clucall_stat;

extern clucall_stat clucall_load(const char *, struct clucall_vector[]);
extern char *clucall_error(clucall_stat);

/* cluster information item */

/* version switch (versw) settings	*/

#define RUN_AT_INSTALLED        1       /*  1 => RUN_AT_INSTALLED               */
#define RUN_BELOW_INSTALLED     -1      /* -1 => RUN_BELOW_INSTALLED            */
#define RUN_UNKNOWN             0       /*  0 => RUN_UNKNOWN                    */

/* cluster limits definitions for the clu_info option CLU_INFO_LIMITS */

/* cluster member status array settings for option CLU_INFO_MEMBSTATE */

#define  CLU_MEMB_NOT_CONF 	-1	/* memberid is not configured in the cluster */
#define  CLU_MEMB_CONF_DOWN      0 	/* memberid is configured and DOWN */
#define  CLU_MEMB_CONF_UP	 1	/* memberid is configured and UP */
					/* UP implies that the kernel is running */
					/* as a cluster member. The member may not */
					/* be fully booted to multiuser mode */


struct clu_limits {
		  memberid_t min_membid;   /* minimum memberid (for 50A 1)       */
		  memberid_t max_membid;   /* maximum memberid (for 50A 63)      */
		  int max_sup_memb; /* maximum number of members (for 50A 8)*/
                  };

struct clu_item {
		int 	type;
		void	*ptr;
		};

struct clu_info_resp {
		int	num_clu_items;
		struct clu_item *itemlist;
		};

struct clu_member_info {
                char    *hostname;      /* actual hostname  		   DEFAULT=NULL        */
                char    *cluintername;  /* IPNAME for cluster interconnect DEFAULT=NULL        */
                char    *cluinteraddr;  /* IPADDR for cluster interconnect DEFAULT=NULL        */
                char    *base_version;  /* The Tru64 base version string   DEFAULT=NULL        */
                char    *clu_version;   /* The TruCluster version string   DEFAULT=NULL        */
                char    *cnx_nodename;  /* CNX member name                 DEFAULT=NULL        */
                memberid_t     memberid;       /* memberid 0-63                   NO DEFAULT          */
                int     running_vers;   /* running version versw() flag    DEFAULT=0	       */
                                        /*  1 => INSTALLED                      */
                                        /* -1 => BELOW INSTALLED                */
                                        /*  0 => UNKNOWN                        */
                int     state;          /* cnx_state != MEMBER => 0 => DOWN DEFAULT=0          */
                                        /* cnx_state == MEMBER => 1 => UP       */
                int     cnx_state;      /*      According to cnxdefs.h      DEFAULT=UNKNOWN    */
                                /* UNKNOWN     =>       ?????                   */
                                /* NEW         => newly discovered node         */
                                /* POTENTIAL   => full connections established  */
                                /* MEMBER      => active card carrying member   */
                                /* PARTITIONED => communication failure         */
                                /* REMOVED     => member removed from cluster   */
                                /* INVALID     => invalid/illegal state         */

                int     comm_state;     /* 0 => no comm   1 => yes comm    DEFAULT=0	       */
                u_long  incarn;         /* incarnation number              DEFAULT=0           */
                u_int   csid;           /* cluster id                      DEFAULT=0           */
                int     expected_votes; /* node's tot # votes expected     DEFAULT=0           */
                int     votes;          /* node's votes contributed        DEFAULT=-1	       */
                u_int   vers;           /* cnx version                     DEFAULT=0           */
                u_long  mtime;          /* internal use by libclu              */
		u_long  umtime;		/* internal use by libclu              */
                u_long  spare[8];       /* 8 spare longs for unexpected growth */
                };



struct clu_gen_info {
		int clu_num_of_members; /* number of configured cluster members NO DEFAULT     */
		memberid_t my_memberid;	/* this nodes memberid			NO DEFAULT     */
		char *clu_name;		/* the cluster name			NO DEFAULT     */
		u_long incarn;		/* incarnation of cluster 		NO DEFAULT     */
		int  spare;		/* spare -unused 			*/
		long current_votes;     /* current votes available for quorum	NO DEFAULT     */
		dev_t qdisk;        	/* quorum disk 				NO DEFAULT     */
		int qdisk_votes;        /* votes contributed by qdisk 		NO DEFAULT     */
		char *qdisk_name;	/* pointer to quorum disk name		DEFAULT=NULL   */
					/*			NULL => No Quorum Disk	       */
		long cev;		/* cluster expected votes		NO DEFAULT     */
		struct clu_member_info *memblist; /* member specific info 	*/
		};

_BEGIN_CPLUSPLUS

extern int		clu_info __((int option, ...));
extern int 		clu_get_info  __((struct clu_gen_info **));
extern int 		clu_free_info  __((struct clu_gen_info **));
extern int		clu_get_memb_by_name __((char *, struct clu_member_info **));
extern int		clu_get_memb_by_id __((memberid_t, struct clu_member_info **));
extern int		clu_free_memb __((struct clu_member_info **));
extern int 		versw  	__((ulong, ulong));
extern boolean_t	clu_is_ready  __((void));
extern boolean_t	clu_is_member __((void));

_END_CPLUSPLUS


/* The following are return values for clu_get_info() and clu_free_info() */
#define CLU_INFO_SUCCESS    0   /* Successful clu_get_info return      */
#define CLU_NOT_MEMBER      1   /* This system is not a cluster member */
#define CLU_NO_CLUSTER_NAME 2   /* No cluster name is defined          */
#define CLU_NO_MEMBERID     6   /* No memberid defined                 */
#define CLU_CNX_ERROR       7   /* Error from the connection manager   */
#define CLU_NO_MEMORY       3   /* No memory for interface             */
#define CLU_NO_MEMBERLIST   3   /* No memberlist file was found        */
#define CLU_BAD_MEMBERLIST  4   /* Bad memberlist file was found       */
#define CLU_NO_RC_CONFIG    5   /* No /etc/rc.config file for member   */
#define CLU_BAD_CLUINTER    8   /* Bad cluster interconnect name       */

#endif	/*  _KERNEL  */

#define CLU_MEMBER_ROOT_STR    "/cluster/members/"
#define CLU_MEMBER_ROOT_STRLEN 17
#define CLU_BOOT_PARTITION     "/boot_partition"
#define CLU_MAXNAMELEN         256 
#define CLU_ADM_LOCK_FILE      "/cluster/admin/locks/clu_admin.lck"
#define CLU_ADM_LOCK           1
#define CLU_ADM_UNLOCK         2


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* _SYS_CLU_H_ */
