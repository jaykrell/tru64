/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: pdrv3.h,v $
 * Revision 1.1.60.13  2006/03/18  01:17:15  Gokhan_Sozmen
 * 	QAR.99551: added a wait channel to ccmn_path_reg_req_t.
 *
 * Revision 1.1.60.12  2006/03/14  22:56:36  Gokhan_Sozmen
 * 	FAST BOOT PROJECT
 * 	Add external definitions for ccmn_all_hier_reg_cmplt and
 * 	ccmn_reg_hier_pause. Add typedefs ccmn_path_reg_req_t and
 * 	ccmn_path_reg_req_q_hdr. Include hwc_reg.h.
 * 	Add pa_top_best, pa_top_worst, pa_top_avg, and pa_top_cnt
 * 	PATH statistics to PATH structure. Define
 * 	CCMN_PATH_TOP_BEST_IDX, CCMN_PATH_TOP_WORST_IDX,
 * 	CCMN_PATH_TOP_AVG_IDX, and CCMN_PATH_TOP_CNT_IDX.
 *
 * Revision 1.1.60.11  2005/09/15  02:11:00  William_Dallas
 * 	Changes for QAR410.  Added pws_consect_tmo member to PDRV3_WS.
 * 	This addition does not change the size of the struct since
 * 	the member was from harvested compiler alignment space.
 * 	Padded out the space with reserved members.  pws_consect_tmo
 * 	member is used to track consecutive Command timeouts in
 * 	topology probes. Added define QTAG_CREDIT_CMD_TMO which
 * 	now allows for I/O throttling for command timeouts
 * 	(credit manager functionality).  Changed PWS_CCB_QUE_REMOVE
 * 	macro to call the credit manager when a Command Timeout is
 * 	detected in addition to Queue full.  Added to CCMN_SPECIFIC
 * 	the pd_cmd_tmo_cnt from alignment space, size of struct
 * 	does not change.  This member tracks the total number
 * 	of command timeouts.
 *
 * Revision 1.1.60.10  2005/03/14  14:18:50  William_Dallas
 * 	Added flag PQ_LID_MISMATCH_REPORT to the path structure to denote
 * 	that an error report has been done on the mismatch.  This allows
 * 	for processing the inactive queue but not generate many error
 * 	log entries for the same mismatch.
 *
 * Revision 1.1.60.9  2005/01/22  16:25:02  Dwight_Brown
 * 	Revision 1.1.83.2  2004/11/01  13:56:11  Steve_Feeley
 * 	  QAR 98326: Try harder project.
 * 	  1) Add PDRV3_PRINTD debug macro.
 * 	  2) Add pa_cto_cnt and pa_cto_time to path structure.
 * 	  3) Add pi_timout_limit and pd_cmd_no_rsp_limit to PATH_INFO_HDR.
 *
 * Revision 1.1.60.8  2004/07/06  15:19:45  David_Schroeder
 * 	Fix for QAR 97779 don't call credit manager functions on non tagged
 * 	io.
 *
 * Revision 1.1.60.7  2003/11/10  18:10:04  Bjorn_Engberg
 * 	Fixed several macros to get rid of compiler warnings.
 *
 * Revision 1.1.60.6  2003/06/09  21:16:40  Charlotte_Richardson
 * 	Oops, should have read, fixes QAR 95302.
 * 	[2003/06/09  20:55:24  Charlotte_Richardson]
 *
 * 	Fixes QAR 9302.
 * 	[2003/06/02  17:05:59  Charlotte_Richardson]
 *
 * 	1) Define CCMN_DEL_INPROG in the pd_drv_state field in the
 * 	CCMN_SPECIFIC to be used when deletion or unregistration has
 * 	been confirmed but not yet committed.
 * 	2) Define CCMN_DEV_SPECIFIC1 in the pd_drv_state field in
 * 	the CCMN_SPECIFIC to be renamed and used for device-specific
 * 	actions. cdisk uses it to mark devices that we wanted to put
 * 	into recovery but did not because CCMN_DEL_INPROG was set.
 * 	[2003/05/30  18:43:48  Charlotte_Richardson]
 *
 * Revision 1.1.60.5  2003/04/01  14:21:10  Maggie_Peterson
 * 	Add macro IS_PATH_ACTIVE. QARs 95337, 90640.
 *
 * Revision 1.1.60.4  2003/01/21  16:37:48  Ashoke_Rampuria
 * 	Add pws_recovery_cnt in pdrv3_ws to keep count of
 * 	retries.
 *
 * Revision 1.1.60.3  2003/01/06  19:48:07  David_Schroeder
 * 	Add start_lbolt field to pdrv3_ws struct for  QAR 92811
 *
 * Revision 1.1.60.2  2002/12/03  22:27:49  David_Schroeder
 * 	Add definition for service routine for vendor unique
 * 	version of ccmn_scan_lun3. Change by Mike Zaharee
 *
 * Revision 1.1.60.1  2002/10/02  20:20:09  Bjorn_Engberg
 * Merge Information:  Visual Merge: User specified tree v51asupportos.nightly
 *     User Revision:  v51bsupportos_nightly:1.1.47.9 Local Ancestor: n/a
 *    Merge Revision:  v51asupportos_nightly:1.1.51.5
 *   Common Ancestor:  1.1.51.4
 * 	Merged forward of v51asupportos-773-bjorn (Rev.1.1.51.5).
 *
 * Revision 1.1.51.5  2002/09/23  15:39:04  Bjorn_Engberg
 * 	Fixed problem with NUMA Disk Statistics,
 * 	QARs 85057 and 93713.
 * 
 * Revision 1.1.47.9  2002/06/06  20:00:25  Mike_Zaharee
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree wcalphaos
 *     User Revision:  Mike_Zaharee_wcabl4_bl5_memoryleak_br:1.1.57.1 Local Ancestor:1.1.47.6
 *    Merge Revision:  wcalphaos_br:1.1.47.8
 *   Common Ancestor:  1.1.47.6
 * 
 * Revision 1.1.47.8  2002/05/30  23:16:07  Ashoke_Rampuria
 * 	Changes for compiler switch project
 * 
 * Revision 1.1.47.7  2002/05/29  12:38:03  Maggie_Peterson
 * 	Implement 'repended' argument for SEND_PENDING_CCB3 in order to
 * 	notify caller that a request remains on pending queue. QAR 90870.
 * 
 * Revision 1.1.57.1  2002/04/26  19:55:10  Mike_Zaharee
 * 	Add function prototype for ccmn_specific_release().
 * 
 * Revision 1.1.47.6  2002/04/04  16:48:36  Jan_Reimers
 * 	IO Mesh changes for Marvel
 * 
 * Revision 1.1.47.5  2002/02/01  18:13:59  Mike_Zaharee
 * 	Remove rehm thread.
 * 
 * Revision 1.1.47.4  2002/01/30  18:10:51  Jan_Reimers
 * 	New pa_mode_page_flags in the PATH structure
 * 	Addition of new path mode page flags for sending CTRL_OPS page
 * 	New macro to readdress a ccb to a particular path
 * 
 * Revision 1.1.47.3  2001/11/06  14:53:55  Jim_Goddard
 * Merge Information:  Non-Visual Merge: User specified tree v51asupportos.bl0
 *     User Revision:  wcalphaos_br:1.1.47.2 Local Ancestor: n/a
 *    Merge Revision:  v51asupportos_bl0:1.1.51.1
 *   Common Ancestor:  1.1.30.15
 * 	Merge from V51Asupport BL0.
 * 
 * Revision 1.1.51.1  2001/10/17  16:59:06  William_Dallas
 *  * Backport from wc.alpha new I/O Barrier implementation
 * 
 * Revision 1.1.47.2  2001/10/03  20:18:48  Jim_Goddard
 * 	parallel probe backport
 * 
 * Revision 1.1.44.3  2001/08/30  15:33:32  Jan_Reimers
 * 	Eliminate a goto by using a local variable and conditionl.
 * 	This fixes a warning from the IPF compiler.
 * 
 * Revision 1.1.44.2  2001/07/13  16:22:45  Robin_Miller
 * Merge Information:  Non-Visual Merge: User specified tree yankeeos.bl8
 *     User Revision:  wildcatos_br:1.1.44.1 Local Ancestor: n/a
 *    Merge Revision:  yankeeos_bl8:1.1.30.14
 *   Common Ancestor:  1.1.30.10
 * 	Merge from Yankee BL8.
 * 
 * Revision 1.1.30.15  2001/07/13  16:18:33  Jan_Reimers
 * 	QAR 88817
 * 	Pass lock flags into CCMN_PATH_FREE so it can pass them on.
 * 
 * Revision 1.1.30.14  2001/06/12  20:54:02  Jan_Reimers
 * 	QAR 87852
 * 	New opcode defined for ccmn_rehm_q
 * 	New flag defined for pd_drv_state
 * 	Changed path pointer in that structure to a generic pointer
 * 
 * Revision 1.1.30.13  2001/05/10  17:55:47  Robin_Miller
 * 	Fix for QAR 86800:
 * 	Added PATH_CHANGE_OP for enabling HWC change name request.
 * 
 * Revision 1.1.44.1  2001/05/10  13:59:49  William_Dallas
 * 	Defines for new I/O Barrier code.  Also included are
 * 	merges from YANKEE (yankeeos-1469-dallas) which fixes
 * 	QAR 87015 and Jan_Reimers submit to prevents pd_qdepth_alloc
 * 	going negative.
 * 
 * Revision 1.1.30.12  2001/04/27  13:14:40  William_Dallas
 * 	Added member and defines for ccmn_reg_hier_path3()
 * 	QAR 87015
 * 
 * Revision 1.1.30.11  2001/04/19  20:27:30  Jan_Reimers
 * 	Don't allow pd_qdepth_alloc to go negative
 * 
 * Revision 1.1.30.10  2001/04/04  21:17:56  Jan_Reimers
 * 	Added ccmn_sasy structure
 * 	Fixed arguments to CCMN_REHM_ADD macro
 * 
 * Revision 1.1.30.9  2001/03/21  20:56:03  Jan_Reimers
 * 	Added pd_max_record to CCMN_SPECIFIC
 * 
 * Revision 1.1.30.8  2001/01/16  21:40:26  Jan_Reimers
 * 	Used one reserved location in the pathing structure
 * 
 * Revision 1.1.30.7  2000/12/07  19:57:56  Jan_Reimers
 * 	Added new structure member to EHM registration thread structure
 * 	Added new arguemnt to CCMN_REHM_ADD macro
 * 
 * Revision 1.1.30.6  2000/11/09  16:20:40  Jan_Reimers
 * 	Close small timing window for possible queue corruption.
 * 
 * Revision 1.1.30.5  2000/11/03  20:33:07  Jan_Reimers
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree yankeeos
 *     User Revision:  Jan_Reimers_lun_exp_yn_br:1.1.31.2 Local Ancestor:1.1.30.3
 *    Merge Revision:  yankeeos_br:1.1.30.4
 *   Common Ancestor:  1.1.30.3
 * 	[2000/11/03  20:32:31  Jan_Reimers]
 * 	Added argument to ccmn_post_event()
 * 	[2000/11/02  14:02:51  Jan_Reimers]
 * 
 * Revision 1.1.30.4  2000/11/02  20:20:08  Ernie_Petrides
 * 	Restore revs 1.1.30.1 and 1.1.30.2 dropped in 1.1.30.3.
 * 
 * Revision 1.1.30.3  2000/10/26  17:22:09  Raul_Kacirek
 *  *	QAR 81531 - kernel build fails with CAMDEBUG defined
 * 
 * Revision 1.1.30.2  2000/10/25  17:13:21  Dennis_Paradis
 * 	Save some cpu cycles in PWS_CCB_QUE_REMOVE. QAR 81335.
 * 
 * Revision 1.1.30.1  2000/10/16  19:24:49  Michael_Gilmore
 * 	(QAR 81827) moved event definitions to hwc_events.h
 * 
 * Revision 1.1.14.20  2000/08/18  16:48:34  Tom_Miller
 * 	{** Forced Submit **}
 * 	Fix SEND_CCB3 macro for cross rad execution.
 * 
 * Revision 1.1.14.15  2000/07/18  20:58:01  Jan_Reimers
 * 	Added structures and macros for adding/removing requests to the
 * 	ccmn_rehm thread queue.
 * 
 * Revision 1.1.14.14  2000/03/29  21:03:37  Peter_Keilty
 * Merge Information:  Visual Merge: User specified tree zincos
 *     User Revision:  ZULUOS:1.1.14.13 Local Ancestor: n/a
 *    Merge Revision:  ZINCOS:1.1.17.5
 *   Common Ancestor:  1.1.17.2
 * 	Merging in Zinc BL4 spin3,4
 * 
 * Revision 1.1.17.5  2000/03/24  19:11:01  Gary_Field
 * 	Added CCMN_PATH_FREE macro and proto for ccmn_resume_path_monitoring.
 * 	QAR 75608 and QAR 77998
 * 	Moved pd_clus_directions from CCMN_SPECIFIC to TAPE_SPECIFIC.
 * 	and QAR 77341
 * 
 * Revision 1.1.17.4  2000/03/20  20:21:03  Gary_Field
 * 	Added bit definitions for the cluster_dev_directions attribute. QAR 77341
 * 
 * Revision 1.1.14.13  2000/03/03  19:44:25  Carolyn_Briglia
 * 	merge zinc bl4 pass 2
 * 
 * Revision 1.1.14.12  2000/02/24  20:34:01  Peter_Keilty
 * Merge Information
 *     Merge Revision:  ZULUOS:1.1.14.11
 *     User  Revision:  Peter_Keilty_zuluos_cnt_ras_br:1.1.18.3
 *    Common Ancestor:  1.1.14.10
 *     Merge Revision History Comments from Rev : 1.1.14.11
 *     	Added CCMN_SLEEPUNLOCK_RAD_W_STAT macro so that we can deal with
 * 	rad locks. This was something we missed in the I/O scale project.
 *     -------------------------------------------------
 * 	[2000/02/24  16:46:35  Peter_Keilty]
 * 	Merge in changes:
 * 	Revision 1.1.14.11  2000/02/23  21:28:16  William_Dallas
 * 	[2000/02/24  16:40:22  Peter_Keilty]
 * 	Added comments for cross_rad_iocnt and cross_rad_initiated_iocnt.
 * 	[2000/02/23  18:27:11  Peter_Keilty]
 * 	Modified macro GET_NEXTIO_PATH_BY_QUE to round robin paths based
 * 	oldest time value if path item counts equal.
 * 	Modified macro SEND_PENDING_CCB check for jump function.
 * 	Modified macro SEND_CCB to check for current execution rad context
 * 	and queue cross rad IO if active. Current rad context now queues
 * 	if were is pending IO and calls SEND_PENDING_CCB macro for credit
 * 	updating and checking.
 * 	Macro GET_PATH_RAD_PD_DS_NOLOCKS now takes radid argument and uses
 * 	new macro FIND_ACTIVE_RAD_NOLOCKS.
 * 	Added new macro FIND_ACTIVE_RAD_IOPATH and FIND_ACTIVE_RAD_NOLOCKS
 * 	which tries to find the closest active rad path to this rad.
 * 	Modified macro GET_NEXTIO_PATH to use new macro FIND_ACTIVE_RAD_IOPATH.
 * 	Added two new current attributes cross_rad_iocnt and
 * 	cross_rad_initiated_iocnt to the PD_RAD struct and PD CCMN_SPECIFIC.
 * 	[2000/02/23  15:41:57  Peter_Keilty]
 * 
 * Revision 1.1.14.11  2000/02/23  21:28:16  William_Dallas
 * 	Added CCMN_SLEEPUNLOCK_RAD_W_STAT macro so that we can deal with
 * 	rad locks. This was something we missed in the I/O scale project.
 * 
 * Revision 1.1.17.3  2000/02/17  17:06:56  Jan_Reimers
 * 	Added prototypes for ccmn_scan_paths() and ccmn_trans_srm_suffix()
 * 
 * Revision 1.1.14.10  2000/02/01  22:07:39  Peter_Keilty
 * 	Change struct PATH pa_stats_percpu[] moved to end of struct and
 * 	added new item ds_num_rwstats_percpu.
 * 	QAR-77062 TLASER panic kmf.
 * 	Added credit mgr define QTAG_CREDIT_UPDATE
 * 	QAR-76959 RAWHIDE PANICS IN CCMN_CREDIT_MGR ON NIGHTLY KERNEL.
 * 	Added missing prototype ccmn_init_pd_rad_data().
 * 
 * Revision 1.1.14.9  2000/01/28  21:15:15  Jan_Reimers
 * Merge Information
 *     Merge Revision:  ZULUOS:1.1.14.8
 *     User  Revision:  Jan_Reimers_ping_zu_br:1.1.18.1
 *    Common Ancestor:  1.1.14.7
 * 	[2000/01/28  21:14:12  Jan_Reimers]
 * 	clus_directions moved from disk specific to ccmn specific
 * 	[2000/01/27  21:12:47  Jan_Reimers]
 * 
 * Revision 1.1.17.2  2000/01/18  21:44:23  Alex_Iannicelli
 * 	Add prototype for ccmn_rpt_chgbl_devid3()
 * 
 * Revision 1.1.14.7  2000/01/13  19:30:38  William_Dallas
 * 	Massive changes to support NUMA and WILDFIRE.
 * 	Changed CCMN_SPECIFIC data and added new PD_RAD_DATA struct.
 * 	PD_RAD_DATA holds the IO queues (active, pending and abort),
 * 	path lists, per rad disk specific data.
 * 	Added new struct PATH_JUMP used with XPT_JMP_INQ.
 * 	Added new macro SEND_CCB3, REM_CCB3, SEND_PENDING_CCB3,
 * 	GET_PATH_LEADER_NOLOCKS, GET_FAILED_PATH_NOLOCKS,
 * 	TOTAL_ACTIVE_PATHCNT, TOTAL_ACT_STDBY_PATHCNT,
 * 	TOTAL_FAILED_PATHCNT, CCMN_IO_CCB_RADID_BLD3,
 * 	MOVEONE_STANDBY_TO_ACTIVE.
 * 	Modified macros GET_NEXTIO_PATH, GET_PATH_LEADER, CHECK_PATH_IO_CMP.
 * 	Added prototype for new functions ccmn_credit_mgr(),
 * 	ccmn_setup_ccmn_rads(), ccmn_delete_ccmn_rads(),
 * 	ccmn_io_ccb_radid_bld3(), ccmn_match_path_connid3(),
 * 	ccmn_destroy_invalid_paths(), ccmn_del_que_paths().
 * 
 * Revision 1.1.14.6  2000/01/03  22:12:16  Jan_Reimers
 * 	Added pd_consistent_name to ccmn_specific structure
 * 	merge from zinc bl3
 * 
 * Revision 1.1.17.1  1999/12/15  18:41:01  Jan_Reimers
 * 	Added pd_consistent_name to ccmn_specific structure
 * 
 * Revision 1.1.14.5  1999/08/25  17:09:46  Peter_Keilty
 * 	Change macro GET_PATH_LEADER to check the per RAD path queue first,
 * 	than the global active queue.
 * 	[1999/08/23  13:20:59  Peter_Keilty]
 * 
 * Revision 1.1.14.4  1999/08/12  20:55:54  Peter_Keilty
 * 	Fix GET_NEXTIO_PATH_BY_QUE macro to check pa_path_que item
 * 	count instead of pa_rad_que which it should have been using.
 * 	[1999/08/11  15:39:45  Peter_Keilty]
 * 
 * Revision 1.1.14.3  1999/08/02  18:32:03  Peter_Keilty
 * 	Add include files kern/queue.h, kern/thread.h and kern/rad.h
 * 	which are ifdef _KERNEL.
 * 	[1999/08/02  18:06:02  Peter_Keilty]
 * 
 * Revision 1.1.14.2  1999/07/30  19:29:50  Peter_Keilty
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.4.23 **
 * 		** Merge revision:	1.1.14.1 **
 * 	 	** End **
 * 	Changed the PATH structure adding a PATH_QUE pa_rad_que and
 * 	a LOCALITY_CONTEXT locality_context.
 * 	Changed the PATH_INFO_HDR structure adding a pointer to array of
 * 	PATH_QUEs index by rad_id which has the per RAD active paths
 * 	and variable pi_nrads.
 * 	Change macros PATH_QUE_INSERT and PATH_QUE_REMOVE to handle the
 * 	per RAD active path list.
 * 	Change macro GET_NEXTIO_PATH(ccmn_spec_ptr, path_ptr).
 * 	Added new macro GET_NEXTIO_PATH_BY_QUE(que_ptr, path_ptr).
 * 	Changed CCMN_SPECIFIC data layout for better cache line blocking.
 * 	Changed 3 arg to prototype ccmn_io_ccb_bld3(trans_p, &(c3cb_p), path_p).
 * 	[1999/07/30  14:30:34  Peter_Keilty]
 * 
 * Revision 1.1.4.24  1999/07/13  20:47:26  William_Dallas
 * 	Added lock flags argument to CCMN_CLR_DRV_STATE macro
 * 	[1999/07/12  19:37:53  William_Dallas]
 * 
 * Revision 1.1.4.23  1999/04/05  18:59:27  William_Dallas
 * 	Added new path member and defines so that when a path fails
 * 	we report it once. When the path is regained and if it fails
 * 	again its a new event.
 * 	[1999/04/05  13:22:29  William_Dallas]
 * 
 * Revision 1.1.4.22  1999/03/26  21:35:28  Carolyn_Briglia
 * 	Add define for PQ_REG_EHM_HIER
 * 	[1999/03/26  15:17:46  Carolyn_Briglia]
 * 
 * Revision 1.1.4.21  1999/03/25  14:11:29  William_Dallas
 * 	Added monitor queue lock state defines.
 * 	[1999/03/23  20:18:17  William_Dallas]
 * 
 * Revision 1.1.4.20  1998/10/30  19:03:34  William_Dallas
 * 	Merged PTFC I/O Barrier functionality.  Changed functionality
 * 	to deal with paths. Merged Jan Reimers ccmn_event posting changes.
 * 	[1998/10/29  23:21:55  William_Dallas]
 * 
 * Revision 1.1.4.19  1998/10/19  17:07:41  Raul_Kacirek
 * 	Added lock flags argument to CCMN_WAITSET_DRV_STATE macro
 * 	[1998/10/19  16:49:28  Raul_Kacirek]
 * 
 * Revision 1.1.4.18  1998/08/18  17:12:27  Raul_Kacirek
 * 	Added prototypes ccmn_restart_tagged_queue() and ccmn_send_pending_ccb3()
 * 	[1998/08/18  17:09:47  Raul_Kacirek]
 * 
 * Revision 1.1.4.17  1998/04/27  19:38:52  William_Dallas
 * 	Added new pathing members and defines so that we
 * 	can better determine path access
 * 	*** empty log message ***
 * 	[1998/04/24  20:40:03  William_Dallas]
 * 
 * Revision 1.1.4.16  1998/04/21  19:46:25  Mark_Bokhan
 * 	 	** Merge Information **
 * 		** Command used:	bmerge **
 * 		** Ancestor revision:	1.1.4.14 **
 * 		** Merge revision:	1.1.4.15 **
 * 	 	** End **
 * 	[1998/04/17  21:11:48  Mark_Bokhan]
 * 	Add timestamps to PDRV3_WS for disk statistics
 * 	[1998/04/17  20:09:44  Mark_Bokhan]
 * 
 * Revision 1.1.4.15  1998/04/17  18:09:55  William_Dallas
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.4.12 **
 * 		** Merge revision:	1.1.4.14 **
 * 	 	** End **
 * 	Added defines for EHM saving and changed macro so it is
 * 	more flexible
 * 	[1998/04/16  17:11:32  William_Dallas]
 * 
 * Revision 1.1.4.14  1998/04/15  14:46:20  James_Smart
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.4.12 **
 * 		** Merge revision:	1.1.4.13 **
 * 	 	** End **
 * 	Renamed pd_name_flags to pd_hwc_flags
 * 	[1998/04/15  14:12:23  James_Smart]
 * 	Add prototype for ccmn_get_unique_name()
 * 	Add hwc name flags (pd_name_flags) to CCMN_SPECIFIC
 * 	[1998/04/13  19:11:05  James_Smart]
 * 
 * Revision 1.1.4.13  1998/04/14  18:52:25  Jamey_Poirier
 * 	Added a prototypes for ccmn_delete_paths and dereg_path.
 * 	[1998/04/08  22:44:20  Jamey_Poirier]
 * 
 * Revision 1.1.4.12  1998/03/24  19:34:24  Jamey_Poirier
 * 	Added another flag to the driver state bits.  A special flag which
 * 	can be used by error event callbacks.
 * 	[1998/03/23  23:06:51  Jamey_Poirier]
 * 
 * Revision 1.1.4.11  1998/02/28  00:10:48  William_Dallas
 * 	Added delete state flag for a path that is going to be
 * 	deleted
 * 	Added new path stateflag.... Path struct is marked for deletion
 * 	[1998/02/27  23:18:10  William_Dallas]
 * 
 * Revision 1.1.4.10  1998/02/20  20:25:40  Raul_Kacirek
 * 	QAR 58601 - fixed macros CCMN_SLEEP_UNLOCK and CCMN_SLEEPUNLOCK_W_STAT
 * 	[1998/02/20  20:23:35  Raul_Kacirek]
 * 
 * Revision 1.1.4.9  1998/02/12  19:01:48  Raul_Kacirek
 * 	Modified CCMN_SLEEPUNLOCK to correctly lower IPL prior to sleep.
 * 	New macro CCMN_SLEEPUNLOCK_W_STAT replaces CCMN_TIMEOUTUNLOCK
 * 	[1998/02/12  18:57:12  Raul_Kacirek]
 * 
 * Revision 1.1.4.8  1998/01/09  15:55:54  Raul_Kacirek
 * 	Added structures CCMN_HELD_CALLS_HDR	and CCMN_HELD_CALL
 * 	Added prototypes for	ccmn_sched_call() and ccmn_abort_call()
 * 	[1998/01/09  15:47:56  Raul_Kacirek]
 * 
 * Revision 1.1.4.7  1997/12/09  18:56:08  William_Dallas
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.4.5 **
 * 		** Merge revision:	1.1.4.6 **
 * 	 	** End **
 * 	Implemented EHM reporting for pathing.
 * 	[1997/12/07  17:48:48  William_Dallas]
 * 
 * Revision 1.1.4.6  1997/12/04  21:07:39  David_Gagne
 * 	Add hardware management fields to CCMN_SPECIFIC
 * 	[1997/12/04  20:39:48  David_Gagne]
 * 
 * Revision 1.1.4.5  1997/11/12  20:08:52  Raul_Kacirek
 * 	Streamlined macros GET_NEXTIO_PATH, GET_PATH_LEADER, GET_FAILED_PATH
 * 	Added macro PATH_IO_COMPLETED to call if CAM status is CAM_REQ_CMP
 * 	[1997/11/12  19:43:15  Raul_Kacirek]
 * 
 * Revision 1.1.4.4  1997/10/31  19:27:21  William_Dallas
 * 	Added ifdef _KERNEL around extern struct timeval time for
 * 	usr programs that include this .h and /usr/include/time.h
 * 	[1997/10/31  19:15:47  William_Dallas]
 * 
 * Revision 1.1.4.3  1997/10/30  23:00:49  William_Dallas
 * 	Merge from shared sandbox of device access management
 * 	[1997/10/29  23:02:42  William_Dallas]
 * 	Updates for failed path monitoring
 * 	[1997/10/29  17:03:11  William_Dallas]
 * 
 * Revision 1.1.6.4  1997/10/22  21:11:09  William_Dallas
 * 	3rd argument	in ccmn_io_ccb_bld3() changed to CAM-3 sim type	flag
 * 	[1997/10/22  21:04:23  William_Dallas]
 * 
 * Revision 1.1.6.3  1997/10/22  07:04:48  Raul_Kacirek
 * 	Defined macro CCMN_IO_CCB_BLD3
 * 	Added member	pd_sense_max to	CCMN_SPECIFIC
 * 	Prototype for ccmn_io_ccb_bld3() modified to	a 3 argument call
 * 	[1997/10/22  06:52:11  Raul_Kacirek]
 * 
 * Revision 1.1.6.2  1997/10/21  17:10:42  William_Dallas
 * 	Added Pathing information for Device Access Management
 * 	[1997/10/21  16:57:38  William_Dallas]
 * 
 * Revision 1.1.4.2  1997/10/07  17:00:50  James_Smart
 * 	Creation - CAM3	project
 * 	[1997/10/03  15:48:39  James_Smart]
 * 
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: pdrv3.h,v $ $Revision: 1.1.60.13 $ (DEC)	$Date: 2006/03/18 01:17:15 $
 */

#ifndef	_PDRV3_
#define	_PDRV3_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/table.h>          /* disk statistics in tbl_dkinfo */

#ifdef _KERNEL
#include <kern/queue.h>
#include <kern/thread.h>
#include <kern/rad.h>
#include <io/cam/pdrv.h> 
#include <io/common/devrci.h>
#include <io/common/hwc_reg.h>
#endif

/* Flag for printing debug messages */
extern int pdrv3_debug;
#define PDRV3_PRINTD(a) if (pdrv3_debug) printf a

/************************************************************************
 * :tag::	Peripheral Driver Working Set Definition. GET_SENSE_SIZE3
 ************************************************************************/

/*
 * The SCSI I/O	CCB will contain a pointer to the peripheral
 * driver working set for the CCB.  This version was modified
 * for use by the CAM3 cognizant routines.
 */
typedef	struct pdrv3_ws	 {
	struct pdrv3_ws	*pws_flink;	/* Linkage of working set CCBs	*/
	struct pdrv3_ws	*pws_blink;	/* that	we have	queued		*/
	DCB_SCSIIO	*pws_ccb;	/* Ptr to this CCB.		*/
	struct ccmn_specific *pws_ccmn;	/* Ptr to peripheral device	*/
	struct path     *pws_dev_path;	/* Ptr to the path structure */
	struct pd_rad_data *pws_pd_rad;	/* Ptr to the pd rad structure */
	struct pdrv3_ws	*wait_flink;	/* Linkage of working set CCBs	*/
	U32		 pws_flags;	/* Generic to driver		*/
	U32		 pws_retry_cnt;	/* Retry count for this	request	*/
	u_long		 drv_spec_flags;/* driver specific flags	*/
	u_long		 ReferenceCNT;
        long		 start_time;	/* usec time value at I/O start	*/
        long		 pending_delta;	/* usec spent in I/O pending que */
	u_char		 pws_sense_buf[PD_SENSE_BUF_LEN];
					/* Auto	sense buffer		*/
	u_long           start_lbolt;   /* lbolt when ccb is sent       */
	U32              pws_recovery_cnt; /* recovery count            */
        u_char           pws_consect_tmo; /* Number of consecutive
                                             command timeouts.           */
        u_char           Reserved_char1; /* Reserve                     */
        u_short          Reserved_u16_1; /* Reserve                     */
	u_long		 Reserved[6];	/* Reserved			*/
} PDRV3_WS;

/*
 * CAM-1/CAM-3
 * Get the sense data size for the device by checking whether it is
 * set to that value.
 */
#define	GET_SENSE_SIZE3(pd)				\
	( (pd->pd_dev_desc->dd_valid & DD_REQSNS_VAL)	\
	  ? pd->pd_dev_desc->dd_req_sense_len		\
	  : SENSE_BUF_LEN3)				\

/************************************************************************
 * :tag::	Error logging flag, tagged queue distribution,
 *		functions entry/exit lock state	flags, drive state flags
 ************************************************************************/
/*
 * Log error enable flag
 */
#define	PD_ERRLOG_ENA	 1

/*
 * TQ_ADJUSTMENT_PERIOD	defines	time slice for which pdb operates
 * with	current	level of tag resource
 *
 * TQ_PERCENT_INCREMENT	defines	percentage of the pending ccb by which
 * effective tag allocation is increased.
 */
#define	TQ_ADJUSTMENT_PERIOD	 2	/* seconds		*/
#define	TQ_PERCENT_INCREMENT	10	/* Desired % increment	*/

/*
 * Factor and shift to calculate absolute tag allocation increment:
 * (TQ_PERCENT_INCREMENT * 5) /	512 = approx 1/100
 */
#define	TQ_FACTOR (TQ_PERCENT_INCREMENT	+	    \
		  (TQ_PERCENT_INCREMENT	<< 2))
#define	TQ_DIV_SHIFT		 9

/*
 * PMK: New Tag Que credit structures 
 */

/*
 * SCSI QUEUE TAG TOKEN STRUCT 
 */
typedef struct scsi_qtag_credits {
    CAM_U32		qtag_cred_tot_cnt;
    CAM_U32		qtag_cred_resv_cnt;
    CAM_U32		qtag_cred_init;
    CAM_U32		reserved;
    struct timeval	qtag_cred_rel_time;	/* Time at which to release 
                                                   this token.  Only use 
                                                   seconds value.  We use
                                                   the gobal systime struct
                                                   incase seconds storage is
                                                   ever increased. */
} SCSI_QTAG_CREDITS;

#define QTAG_CREDIT_INIT 	0	/* Tag Que RAD credit initialize */
#define QTAG_CREDIT_REL 	1	/* Tag Que credit release	 */
#define QTAG_CREDIT_REQ 	2	/* Tag Que credit request	 */
#define QTAG_CREDIT_QFULL 	3	/* Tag Que full indication 	 */
#define QTAG_CREDIT_DEL		4	/* Rad is going away delete	 */
#define QTAG_CREDIT_TMO		5	/* Credit time expired	 	 */
#define QTAG_CREDIT_UPDATE	6	/* Update device qdepth values   */
#define QTAG_CREDIT_CMD_TMO     7       /* Command Timeout               */

/* 
/*
 * Bits	for argument in	ccmn_send_ccb3() and ccmn_rem_ccb3()
 */
#define	PD_LOCKED		1	/* PD locked at	entry	*/
#define	PD_UNLOCKED		0	/* PD unlocked at entry	*/
#define	PD_LOCK_ON_EXIT		2	/* Lock	PD on exit	*/
#define	PD_UNLOCK_ON_EXIT	0	/* Unlock PD on	exit	*/
#define	PD_RAD_LOCKED		0x10	/* RAD locked at entry	*/
#define	PD_RAD_UNLOCKED		0x20	/* RAD unlocked at entry*/
#define	PD_RAD_LOCK_ON_EXIT	0x40	/* Lock	RAD on exit	*/
#define	PD_RAD_UNLOCK_ON_EXIT	0x80	/* Unlock RAD on exit	*/
/*
 * Drive state bits in CCMN_SPECIFIC.pd_drv_state
 */
#define	CCMN_OPENING	    0x01	/* Opening device	         */
#define	CCMN_CLOSING	    0x02	/* Closing		         */
#define CCMN_SPECIAL        0x04        /* Special operation in progress */
#define CCMN_RELEASE        0x08        /* OK to release CCMN_SPECIFIC */
#define CCMN_DEL_INPROG     0x10        /* Delete confirmed but not committed */
#define CCMN_DEV_SPECIFIC1  0x20        /* PD-specific function, renamed
                                           by any PD that uses it */

/***************************************************************************
 * :tag::	Device Access Management path defines, structures and macros
 ***************************************************************************/
/*
 * One structure exists	per each alternate path	to the device.
 * Structures are organized in a queued	list, with header in
 * the CCMN_SPECIFIC structure.
 */
/*
 * Flags used in a) CCMN_DEV_PATH.path_flags
 *		 b) As an argument in ccmn_..._bld3() calls
 *		 c) As an argument in allocation requests calls	to XPT
 */

#define	CAM3_SIM	01	/* Path	SIM is CAM-3 protocol	   a, b	*/
#define	PATH_INVALID	02	/* Path	is stale or deleted	   a	*/

/* *) -	Defined	in CAM-3 draft	*/

/*
 * The path_que	structure is used to link path structs to each other
 * and to the path_info	struct on a per	device basis.
 */

typedef	struct path_que	{
struct path_que	*pq_flink;	/* Forward link	*/
struct path_que	*pq_blink;	/* Backward Link */
struct path *pq_path;		/* Self	describing queue pointer to path */
CAM_U64	pq_item_count;		/* Count of items */
CAM_U32	pq_flags;		/* Actions performed when path fails 
				   or pinged */
CAM_U32	pq_que_id;		/* Follows pa_stateflags */
} PATH_QUE;

/* defines for pq_flags	*/
#define	PQ_RESET_DONE		0x01	/* Reset done or not needed */
#define	PQ_INQ_PING		0x02	/* Ping	validiation done. */
#define	PQ_VALID		0x04	/* Valid path for this translation */
#define PQ_MONITORING		0x08	/* On monitoring queue */
#define PQ_WAITING_FOR 		0x10	/* Someone is waiting for the path
					   to finish pinq */
#define PQ_DELETE		0x20	/* Path is marked for deletion */
#define PQ_EHM_REG		0x40	/* Path has been registered with EHM */
#define PQ_EHM_REG_HIER		0x80	/* Path has been registered with EHM hierarchy*/
#define PQ_LID_MISMATCH_REPORT 0x100    /* A LID mismatch error has been 
                                           reported */

#define	CCMN_PATH_MANAGE	0x01	/* For ccmn_path_ping3 to manage
					   the path */

/* 
 * The SCSI I/O Jump struct (FC adapters) for performance.
 */
typedef struct path_jump {
    U32		(*jmp_entry)();
    void	*arg1;
    void	*arg2;
    void	*arg3;
    void	*arg4;
} PATH_JUMP;

/* 
 * The PATH struct describes the path and state	of the path
 */
typedef struct path {
    PATH_QUE	pa_path_que;		/* linkage into active,standby,failed, etc. 
					   and accounting */
    struct pd_rad_data   *pa_rad;	/* Ptr to pd_rad struct */
    struct path_info_hdr *pa_info_hdr;	/* Ptr to our controlling path_info_hdr */
    LOCALITY_CONTEXT locality_context;	/* Locality context ie. rad */
    PATH_QUE	pa_monitor_que;		/* Linkage into monitor queue for 
					   a path failure */
    PATH_QUE	pa_mon_act_que;		/* Linkage for a scheduled ping. */
    PATH_QUE	drv_que;		/* Linkage for specific driver
					   not defined */
    CAM_U32	pa_stateflags;		/* state flags */
    CAM_U32	pa_prev_stateflags;	/* Previous State flags */	
    CAM_U32	pa_events_reported;	/* PATH events reported to EVM */
    CAM_S32	pa_event_cnt;		/* Path Number of events -
					   selection timeouts etc.*/
    CAM_S32     pa_cto_cnt;             /* Number of events -
                                         * command timeouts etc.*/
    struct timeval pa_event_time;	/* Time first event detected for this 
					   occurrence */
    struct timeval pa_cto_time;         /* Time first cmd_no_rsp event detected
                                           for this occurrence */
    struct timeval pa_ping_time;	/* Next calculated time to ping */
    CAM_U32	pa_ping_count;		/* Count of pings for path failure */
    CAM_U32     pa_pathing_type;	/* Concurrent or single	path active  */
    
    TRANSLATION pa_trans;		/* CAM-3 translation struct */
    PATH_JUMP	pa_jump;		/* Jump function to bypass xpt */

    CAM_U64     pa_avque;
    CAM_U64     pa_initial_busy;

    /* EHM info */
    CAM_U32	pa_ehm_state;		/* State reported to EHM */
    struct controller *pa_ctrl;		/* Pointer to our controller struct */
    MSS *pa_mss;			/* Our EHM MSS struct we register.  */
    CAM_S32	pa_ehm_reg_inst;	/* Registration instance number */
    CAM_U32	pa_cam_sim_generation;	/* Curr CAM-3 sim generation number */
    CAM_VOID_OFFSET pa_cam_sim_bhandle; /* Sim handle */	
    CAM_U32	pa_cam3_sim;		/* Sim type CAM-1 or CAM-3 */
    CAM_U64	pa_connection_state;	/* Flags for connection state */ 
    CAM_VOID_OFFSET pa_pname;		/* Port name string */
    CAM_U64	pa_mode_page_flags;	/* Used for vendor unique
					   Controller Operations mode page */
#undef PATH_STATISTICS  /* path scanning statistics collection */
#ifdef PATH_STATISTICS /* path scanning statistics collection */
    CAM_U64     pa_top_best;		/* Fastest scan time */
    CAM_U64     pa_top_worst;		/* Slowest scan time */
    CAM_U64     pa_top_avg;		/* Rolling average scan time */
    CAM_U64     pa_top_cnt;		/* Number of scans done */
    CAM_U64	pa_reserved[8];		/* Future expansions */
#else /* No path scanning statistics collection */
    CAM_U64	pa_reserved[12];	/* Future expansions */
#endif /* PATH_STATISTICS */

    CAM_U64     pa_num_stats_percpu;	/* Number of percpu stats */
    struct tbl_dkinfo pa_stats_percpu[1];/* Array based on cpus_per_rad */
					/* NOTE: Must last item in struct */
} PATH;

/* 
 * Flags for pa_stateflags and pa_prev_stateflags 
 */
#define	PA_QUE_MASK	0Xff
#define	PA_ACTIVE	0x01	/* Path	is active */
#define	PA_STANDBY	0x02	/* Path	is in standby to failover too */
#define	PA_INACTIVE	0x04	/* Path	has been defined as inactive do	
				   not use */
#define	PA_FAILED	0x08	/* Path	has failed */
#define	PA_RAD_ACTIVE	0x10	/* RAD Path active */
#define	PA_UNKNOWN	0x00	/* Unknown state
				   (only for pa_prev_stateflags) */

/*
 * Flags for pa_mode_page_flags
 */
#define	PA_TUR_NEEDED		0x1	/* Need to send TUR to active paths */
#define	PA_CTRL_OPS_NEEDED	0x2	/* Need to send CTRL_OPS mode page */

/* Defines for pa_events_reported */
#define PE_REDUCED_REPORTED    0x000001L	/* PATH reduction reported */

/* Defines for pa_connection_state */
#define PATH_CONNECTED	0x01L		/* Reflects INQUIRY PDQ connected = set
					   and maybe connected = 0 */
typedef	struct path_info_hdr {
    struct ccmn_specific *pi_specific;	/* Pointer to our specific struct */
    CAM_U8    pi_pathing_type;		/* Concurrent or single	path active 
					   plus monitoring indicator */
    CAM_U8    pi_fail_method;		/* the method used to fail path	
					   (time or occurrence) */
    CAM_U8    pi_fail_action;		/* Actions to perform when a path 
                                           fails	*/
    CAM_U8    pi_pad;			/* Pad field	*/
    CAM_U32   pi_method_limit;		/* The limit used for sel tmo
                                           (count of events or seconds)*/
    CAM_U32   pi_method_limit_default;  /* Default value */
    CAM_U32   pi_method_limit_saved;    /* Saved value */
    CAM_U32   pi_timout_limit;          /* The limit used for cmd tmo
                                           (count of events or seconds)*/ 
    CAM_U32   pi_cmd_no_rsp_limit;      /* The limit used for command sent with
                                            no response (count or seconds) */
    CAM_U32   pi_max_ping_time;		/* Maximum time	between	pings */
    CAM_U32   pi_initialized;

} PATH_INFO_HDR;

/* Defines for pi_fail_method */
#define	PI_PATHEVENT_TIME	0x01	/* Time	based failures */
#define	PI_PATHEVENT_CNT	0x00	/* Count based failures	*/

/* PATH	STATUS defines:	*/
#define	PATH_OK			0x00	/* No Path event */
#define	PATH_FAIL		0x01	/* Path	failure	detected failure */
#define	PATH_DEV_VIABLE		0x02	/* Device has other paths (for now) */
#define	PATH_READDR		0x04	/* CCB NEEDS re-addressing (path 
					   failure) */
#define	PATH_NONE		0x08	/* No paths */

/* pi_pathing_type definitions --  Defines single or concurrent	path(s)
   active  - If	PA_CONCURRENT NOT SET then single path*/
#define	PATH_SINGLE	0x00	/* A single path can be	active */
#define	PATH_CONCURRENT	0x01	/* Multiple paths can be active	*/
#define PATH_MONITOR	0x80   /* Do we montor path */


/*
 * Monitoring queue for path failures 
 */
typedef struct monitor_path_queue {
PATH_QUE mo_path_mon;		/* list of paths we are monitoring */
PATH_QUE mo_path_mon_act;	/* subset of above.  These are the paths
				 * that will be pinged this time around
				 */
U32 mo_init;			/* Queues and thread started */
XPT_LOCK_DATA mo_path_lck;	/* The queue lock */
} MONITOR_PATH_QUEUE;

/* PATH	QUE insertion and removal MACROS ... CCMN_SPECIFIC Must	be locked 
   Theses macros can't be used for the monitoring and ping queues */

/* Insert to a queue --- goes to tail.	ARGS are set PATH* and
   POINTER TO PATH_INFO_HDR.QUEUE  */
/* PMK: pd_rad lock held coming in and going out */
#define	PATH_QUE_INSERT(path_ptr, que_ptr)				\
{									\
    (path_ptr)->pa_prev_stateflags = 					\
			((path_ptr)->pa_stateflags & PA_QUE_MASK);	\
    (path_ptr)->pa_stateflags = (que_ptr)->pq_que_id;			\
    (que_ptr)->pq_item_count++;						\
    enqueue_tail((queue_t)&(que_ptr)->pq_flink,				\
		 (queue_entry_t)&(path_ptr)->pa_path_que);		\
}


/* Remove a path from a	path_que and adjust queue count	only 
   ARGS	are a set PATH*	*/
/* PMK: pd_rad lock held coming in and going out */
#define	PATH_QUE_REMOVE(path_ptr)					\
{									\
    if((path_ptr)->pa_stateflags == (path_ptr)->pa_rad->		\
				rad_active_paths.pq_que_id) {		\
	(path_ptr)->pa_rad->rad_active_paths.pq_item_count--;		\
    }									\
    else if((path_ptr)->pa_stateflags == (path_ptr)->pa_rad->		\
				rad_standby_paths.pq_que_id) {		\
	(path_ptr)->pa_rad->rad_standby_paths.pq_item_count--;		\
    }									\
    else if((path_ptr)->pa_stateflags == (path_ptr)->pa_rad->		\
				rad_inactive_paths.pq_que_id) {		\
	(path_ptr)->pa_rad->rad_inactive_paths.pq_item_count--;		\
    }									\
    else if((path_ptr)->pa_stateflags == (path_ptr)->pa_rad->		\
				rad_failed_paths.pq_que_id) {		\
	(path_ptr)->pa_rad->rad_failed_paths.pq_item_count--;		\
    }									\
    else if ((path_ptr)->pa_stateflags == (path_ptr)->pa_rad->		\
				rad_temp_paths.pq_que_id) {		\
	(path_ptr)->pa_rad->rad_temp_paths.pq_item_count--;		\
    }									\
    remque((struct queue_entry *)(&(path_ptr)->pa_path_que));		\
}

/* Remove an item for the temp_paths queue. Args are 
   PATH_INFO_HDR*, PATH*.  PATH* does not need to be set.. */
/* PMK: pd_rad lock held coming in and going out */
#define	PATH_TEMP_PATH_REMOVE(pd_rad_ptr, path_ptr)			\
{									\
    /* Safe	guard */						\
    (path_ptr) = (PATH *)NULL;						\
    if (pd_rad_ptr->rad_temp_paths.pq_item_count) {			\
	(path_ptr) = pd_rad_ptr->rad_temp_paths.pq_flink->pq_path;	\
	remque((struct queue_entry *)(&(path_ptr)->pa_path_que));	\
	pd_rad_ptr->rad_temp_paths.pq_item_count--;			\
    }									\
}

#define TOTAL_ACTIVE_PATHCNT(ccmn_spec_ptr, active_cnt)			\
{									\
    PD_RAD_DATA **pd_rad_pp;						\
    int          i;							\
    (active_cnt) = 0;							\
    pd_rad_pp = (ccmn_spec_ptr)->pd_rad_data;				\
    for (i = 0; i < nrads; i++, pd_rad_pp++) {				\
        (active_cnt) += (*pd_rad_pp)->Active_path_cnt;			\
    }									\
}
#define TOTAL_ACT_STDBY_PATHCNT(ccmn_spec_ptr, active_cnt, standby_cnt)	\
{									\
    PD_RAD_DATA **pd_rad_pp;						\
    int          i;							\
    (active_cnt) = 0;							\
    (standby_cnt) = 0;							\
    pd_rad_pp = (ccmn_spec_ptr)->pd_rad_data;				\
    for (i = 0; i < nrads; i++, pd_rad_pp++) {				\
        (active_cnt) += (*pd_rad_pp)->Active_path_cnt;			\
        (standby_cnt) += (*pd_rad_pp)->Standby_path_cnt;		\
    }									\
}
#define TOTAL_FAILED_PATHCNT(ccmn_spec_ptr, failed_cnt)			\
{									\
    PD_RAD_DATA **pd_rad_pp;						\
    int          i;							\
    (failed_cnt) = 0;							\
    pd_rad_pp = (ccmn_spec_ptr)->pd_rad_data;				\
    for (i = 0; i < nrads; i++, pd_rad_pp++) {				\
        (failed_cnt) += (*pd_rad_pp)->Failed_path_cnt;			\
    }									\
}

/*
 * Try to find path on active que
 */
#define IS_PATH_ACTIVE(ccmn_spec_ptr, path_ptr, found)                   \
{                                                                        \
    PD_RAD_DATA **pd_rad_pp;                                             \
    PD_RAD_DATA  *pd_rad;                                                \
    PATH_QUE	 *path_q;                                                \
    int          i;                                                      \
    (found)=0;                                                           \
    pd_rad_pp = (ccmn_spec_ptr)->pd_rad_data;                            \
    for (i=0; i<nrads; i++, pd_rad_pp++) {                               \
        pd_rad = *pd_rad_pp;                                             \
	PD_RAD_LOCK( pd_rad);                                            \
	path_q = pd_rad->rad_active_paths.pq_flink;                      \
	while (path_q != (PATH_QUE *)&pd_rad->rad_active_paths.pq_flink) { \
	    if (path_q->pq_path == (path_ptr)) {                         \
	        (found) = 1;                                             \
		break; /* out of while */                                \
	     }                                                           \
        path_q = path_q->pq_flink;                                       \
        }                                                                \
        PD_RAD_UNLOCK (pd_rad);                                          \
	if ((found)) {                                                   \
	    break; /* out of for */                                      \
        }                                                                \
    }                                                                    \
}

/* MACRO to get	next path to send I/O to (strategy routine). Path
   pointer is set to NULL if no	available paths	 Must be used when
   ccmn_specific is locked. Args are CCMN_SPECIFIC* and	PATH variable */

/* PMK: Always check RAD path que first, then other rads active list 
 *      No locks held coming in or out
 */
#define GET_NEXTIO_PATH(ccmn_spec_ptr, path_ptr)			\
{									\
    PD_RAD_DATA *pd_rad;						\
    (path_ptr) = (PATH *)NULL;						\
    pd_rad = (ccmn_spec_ptr)->pd_rad_data[current_execution_radid()];	\
    if (pd_rad->Active_path_cnt) { 					\
        PD_RAD_LOCK(pd_rad);						\
        if (pd_rad->Active_path_cnt) { 					\
            GET_NEXTIO_PATH_BY_QUE(&pd_rad->rad_active_paths, path_ptr)	\
	}								\
	PD_RAD_UNLOCK(pd_rad);						\
    }									\
    if ((path_ptr) == (PATH *)NULL) {					\
        FIND_ACTIVE_RAD_IOPATH(ccmn_spec_ptr, pd_rad, path_ptr);	\
        if ((path_ptr) != NULL) {					\
            PD_RAD_UNLOCK(pd_rad);					\
        }								\
    }									\
}

/* PMK:  PD_RAD lock held coming in or out
 */
#define GET_NEXTIO_PATH_BY_QUE(que_ptr, path_ptr)			\
{									\
    PATH_QUE *path_que_ptr;						\
    CAM_U64   itemcnt;							\
    CAM_U64   pathcnt = (que_ptr)->pq_item_count;			\
    if (pathcnt) {							\
    	path_que_ptr = (que_ptr)->pq_flink;				\
	(path_ptr) = path_que_ptr->pq_path;				\
	if (((path_ptr)->pa_pathing_type & PATH_CONCURRENT)) {		\
	    itemcnt = path_que_ptr->pq_item_count;			\
	    while (--pathcnt) {						\
	    	path_que_ptr = path_que_ptr->pq_flink;			\
		if (path_que_ptr->pq_item_count < itemcnt) {		\
		    (path_ptr) = path_que_ptr->pq_path; 		\
		    itemcnt = path_que_ptr->pq_item_count;		\
		}							\
		else if ((path_que_ptr->pq_item_count == itemcnt) &&	\
		         (path_que_ptr->pq_path->pa_initial_busy  <	\
                         (path_ptr)->pa_initial_busy)) {		\
		    (path_ptr) = path_que_ptr->pq_path; 		\
		}							\
	    }								\
	}								\
    }									\
}

/* PMK:  PD_RAD lock not held coming in!
 *       If active path found PD_RAD lock for that RAD is held going out!
 */
#define FIND_ACTIVE_RAD_IOPATH(ccmn_spec_ptr, pd_rad, path) {	 	\
    int ndx;								\
    PD_RAD_DATA **pd_rad_pp = (ccmn_spec_ptr)->pd_rad_data;		\
    struct processor *myp = current_processor();			\
									\
    for (ndx = 0; ((ndx < nrads) && (myp->numa_dist_radtab[ndx] != -1)); ndx++) { \
	pd_rad = pd_rad_pp[myp->numa_dist_radtab[ndx]];			\
        if ((pd_rad)->Active_path_cnt) {				\
            PD_RAD_LOCK(pd_rad);					\
            if ((pd_rad)->Active_path_cnt) {				\
                GET_NEXTIO_PATH_BY_QUE(&(pd_rad)->rad_active_paths, (path));\
		break;							\
            }								\
	    else {							\
		PD_RAD_UNLOCK(pd_rad);					\
	    }								\
	}								\
    }									\
}
/* PMK:  PD_RAD lock not held coming in OR out!
 *       radid is start rad index
 */
#define FIND_ACTIVE_RAD_NOLOCKS(ccmn_spec_ptr, pd_rad_ptr) { 		\
    int ndx;								\
    PD_RAD_DATA *pd_rad;						\
    PD_RAD_DATA **pd_rad_pp = (ccmn_spec_ptr)->pd_rad_data;		\
    struct processor *myp = current_processor();			\
    (pd_rad_ptr) = NULL;						\
    for (ndx = 0; ((ndx < nrads) && (myp->numa_dist_radtab[ndx] != -1)); ndx++) {					\
	pd_rad = pd_rad_pp[myp->numa_dist_radtab[ndx]];			\
        if (pd_rad->Active_path_cnt) {					\
    	    (pd_rad_ptr) = pd_rad;					\
            break;							\
        }								\
    }									\
}


/*
 * Macros to readdress CCB 
 * This one finds the next path.
 */
#define	PATH_CCB_READDR( ccb_ptr, ccmn_spec_ptr, path_ptr )		\
{									\
    GET_NEXTIO_PATH((ccmn_spec_ptr), (path_ptr))			\
    if ((path_ptr) != (PATH *)NULL) {					\
	if ((ccb_ptr)->cam_ch.cam_func_code == XPT_CAM3_CCB) {		\
	    CCB_HEADER3	*cch = (CCB_HEADER3 *)(ccb_ptr);		\
	    cch->cam_connectid = (path_ptr)->pa_trans.connection_id;	\
	    ((PDRV3_WS *)(cch->cam_pdrv_ptr))->pws_dev_path = (path_ptr);\
	    ((PDRV3_WS *)(cch->cam_pdrv_ptr))->pws_pd_rad = (path_ptr)->pa_rad;\
	    cch->cam_sim_generation = (path_ptr)->pa_cam_sim_generation;\
	    cch->cam_sim_bhandle = (path_ptr)->pa_cam_sim_bhandle;	\
	}								\
	else {								\
	    CCB_HEADER *cch = (CCB_HEADER *)(ccb_ptr);			\
	    CCB_SCSIIO *cbb = (CCB_SCSIIO *)(ccb_ptr);			\
	    cch->cam_path_id = (u_char)T_PORT(&((path_ptr)->pa_trans));	\
	    cch->cam_target_id = (u_char)T_TARGET(&((path_ptr)->pa_trans));\
	    cch->cam_target_lun	= (u_char)T_LUN(&((path_ptr)->pa_trans));\
	    ((PDRV3_WS *)(cbb->cam_pdrv_ptr))->pws_dev_path = (path_ptr);\
	    ((PDRV3_WS *)(cbb->cam_pdrv_ptr))->pws_pd_rad = (path_ptr)->pa_rad;\
	}								\
    }									\
}

/*
 * This one readdresses the ccb to the path provided by the caller.
 */
#define	PATH_CCB_READDR_THIS_PATH( ccb_ptr, path_ptr )			\
{									\
	if ((ccb_ptr)->cam_ch.cam_func_code == XPT_CAM3_CCB) {		\
	    CCB_HEADER3	*cch = (CCB_HEADER3 *)(ccb_ptr);		\
	    cch->cam_connectid = (path_ptr)->pa_trans.connection_id;	\
	    ((PDRV3_WS *)(cch->cam_pdrv_ptr))->pws_dev_path = (path_ptr);\
	    ((PDRV3_WS *)(cch->cam_pdrv_ptr))->pws_pd_rad = (path_ptr)->pa_rad;\
	    ((PDRV3_WS *)(cch->cam_pdrv_ptr))->pws_retry_cnt = 0;	\
	    cch->cam_sim_generation = (path_ptr)->pa_cam_sim_generation;\
	    cch->cam_sim_bhandle = (path_ptr)->pa_cam_sim_bhandle;	\
	}								\
	else {								\
	    CCB_HEADER *cch = (CCB_HEADER *)(ccb_ptr);			\
	    CCB_SCSIIO *cbb = (CCB_SCSIIO *)(ccb_ptr);			\
	    cch->cam_path_id = (u_char)T_PORT(&((path_ptr)->pa_trans));	\
	    cch->cam_target_id = (u_char)T_TARGET(&((path_ptr)->pa_trans));\
	    cch->cam_target_lun	= (u_char)T_LUN(&((path_ptr)->pa_trans));\
	    ((PDRV3_WS *)(cbb->cam_pdrv_ptr))->pws_dev_path = (path_ptr);\
	    ((PDRV3_WS *)(cbb->cam_pdrv_ptr))->pws_pd_rad = (path_ptr)->pa_rad;\
	    ((PDRV3_WS *)(cbb->cam_pdrv_ptr))->pws_retry_cnt = 0;	\
	}								\
}


/* Macro to obtain device path leader.	This is	used for opens to 
   send	I/O to a single	non changing path... Sets path_ptr to NULL if
   none	are available CCMN_SPEC	must be	locked.	Args are CCMN_SPECIFIC*	
   and PATH variable */

/* PMK: Always check current RAD path que first, then other rads active list 
 *      No locks held coming in
 */
#define GET_PATH_LEADER(ccmn_spec_ptr, path_ptr)			\
{									\
    PD_RAD_DATA *pd_rad;						\
    PD_RAD_DATA **pd_rad_pp;						\
    struct processor *myp = current_processor();			\
    int          i;							\
    (path_ptr) = (PATH *)NULL;						\
    pd_rad = (ccmn_spec_ptr)->pd_rad_data[current_execution_radid()];	\
    if (pd_rad->Active_path_cnt) {					\
        PD_RAD_LOCK(pd_rad);						\
        if (pd_rad->Active_path_cnt) 					\
            (path_ptr) = pd_rad->rad_active_paths.pq_flink->pq_path;	\
        PD_RAD_UNLOCK(pd_rad);						\
    }									\
    if ((path_ptr) == (PATH *)NULL) {					\
        pd_rad_pp = (ccmn_spec_ptr)->pd_rad_data;			\
        for (i = 0; ((path_ptr) == (PATH *)NULL)			\
			&& (i < nrads)					\
			&& (myp->numa_dist_radtab[i] != -1); i++) {	\
            pd_rad = pd_rad_pp[myp->numa_dist_radtab[i]];		\
            if (pd_rad->Active_path_cnt) {				\
                PD_RAD_LOCK(pd_rad);					\
                if (pd_rad->Active_path_cnt) 				\
	            (path_ptr) = pd_rad->rad_active_paths.pq_flink->pq_path;\
                PD_RAD_UNLOCK(pd_rad);					\
            }								\
        }								\
    }									\
}

#define GET_PATH_LEADER_NOLOCKS(ccmn_spec_ptr, path_ptr)		\
{									\
    PD_RAD_DATA *pd_rad;						\
    PD_RAD_DATA **pd_rad_pp;						\
    struct processor *myp = current_processor();			\
    int          i;							\
    (path_ptr) = (PATH *)NULL;						\
    pd_rad = (ccmn_spec_ptr)->pd_rad_data[current_execution_radid()];	\
    if (pd_rad->Active_path_cnt) {					\
        (path_ptr) = pd_rad->rad_active_paths.pq_flink->pq_path;	\
    }									\
    if ((path_ptr) == (PATH *)NULL) {					\
        pd_rad_pp = (ccmn_spec_ptr)->pd_rad_data;			\
        for (i = 0; ((path_ptr) == (PATH *)NULL)			\
			&& (i < nrads)					\
			&& (myp->numa_dist_radtab[i] != -1); i++) {	\
            pd_rad = pd_rad_pp[myp->numa_dist_radtab[i]];		\
            if (pd_rad->Active_path_cnt) {				\
	        (path_ptr) = pd_rad->rad_active_paths.pq_flink->pq_path;\
            }								\
        }								\
    }									\
}

#define GET_PATH_RAD_PD_DS_NOLOCKS(ccmn_spec_ptr, pd_rad, ds_rad_spec, radid)\
{									\
									\
    (pd_rad) = (ccmn_spec_ptr)->pd_rad_data[radid];			\
    if ((pd_rad)->Active_path_cnt == 0) {                               \
        (pd_rad) = (ccmn_spec_ptr)->pd_rad_data[current_execution_radid()];\
        if ((pd_rad)->Active_path_cnt == 0) {				\
            FIND_ACTIVE_RAD_NOLOCKS(ccmn_spec_ptr, pd_rad);	\
            if ((pd_rad) == NULL) {					\
                (pd_rad) = (ccmn_spec_ptr)->pd_rad_data[current_execution_radid()];\
            }								\
        }								\
    }									\
    (ds_rad_spec) = ((DS_RAD_SPECIFIC *)((pd_rad)->driver_rad_specific));\
}

/* PMK: No locks held coming in or out
 */
#define MOVEONE_STANDBY_TO_ACTIVE(ccmn_spec_ptr, path_ptr)		\
{									\
    PD_RAD_DATA *pd_rad_p;						\
    PD_RAD_DATA **pd_rad_pp;						\
    struct processor *myp = current_processor();			\
    int          i;							\
									\
    pd_rad_pp = (ccmn_spec_ptr)->pd_rad_data;				\
    for (i = 0, (path_ptr) = (PATH *)NULL; 				\
	 (((path_ptr) == (PATH *)NULL)					\
	  && (i < nrads)						\
	  && (myp->numa_dist_radtab[i] != -1)); i++) {		\
        pd_rad_p = pd_rad_pp[myp->numa_dist_radtab[i]];			\
        if (pd_rad_p->Standby_path_cnt) {				\
            PD_RAD_LOCK(pd_rad_p);					\
            if (pd_rad_p->Standby_path_cnt) { 				\
	        (path_ptr) = pd_rad_p->rad_standby_paths.pq_flink->pq_path;\
                PATH_QUE_REMOVE((path_ptr));				\
                PATH_QUE_INSERT((path_ptr), &pd_rad_p->rad_active_paths);\
            }								\
            PD_RAD_UNLOCK(pd_rad_p);					\
        }								\
    }									\
}

/* PMK: No locks held coming in or out
 */
#define GET_FAILED_PATH(ccmn_spec_ptr, path_ptr)			\
{									\
    PD_RAD_DATA *pd_rad;						\
    PD_RAD_DATA **pd_rad_pp;						\
    struct processor *myp = current_processor();			\
    int          i;							\
    									\
    (path_ptr) = (PATH *)NULL;						\
    pd_rad = (ccmn_spec_ptr)->pd_rad_data[current_execution_radid()];	\
    if ((pd_rad)->Failed_path_cnt) {					\
        PD_RAD_LOCK(pd_rad);						\
        if ((pd_rad)->Failed_path_cnt) 					\
	    (path_ptr) = (pd_rad)->rad_failed_paths.pq_flink->pq_path;	\
        PD_RAD_UNLOCK(pd_rad);						\
    }									\
    if ((path_ptr) == (PATH *)NULL) {					\
        pd_rad_pp = (ccmn_spec_ptr)->pd_rad_data;			\
        for (i = 0; ((path_ptr) == (PATH *)NULL)			\
			&& (i < nrads)					\
			&& (myp->numa_dist_radtab[i] != -1); i++) {	\
            pd_rad = pd_rad_pp[myp->numa_dist_radtab[i]];		\
            if (pd_rad->Failed_path_cnt) {				\
                PD_RAD_LOCK(pd_rad);					\
                if (pd_rad->Failed_path_cnt) 				\
	            (path_ptr) = pd_rad->rad_failed_paths.pq_flink->pq_path;\
                PD_RAD_UNLOCK(pd_rad);					\
            }								\
        }								\
    }									\
}
#define GET_FAILED_PATH_NOLOCKS(ccmn_spec_ptr, path_ptr)		\
{									\
    PD_RAD_DATA *pd_rad;						\
    PD_RAD_DATA **pd_rad_pp;						\
    struct processor *myp = current_processor();			\
    int          i;							\
    (path_ptr) = (PATH *)NULL;						\
    pd_rad = (ccmn_spec_ptr)->pd_rad_data[current_execution_radid()];	\
    if ((pd_rad)->Failed_path_cnt) {					\
	(path_ptr) = (pd_rad)->rad_failed_paths.pq_flink->pq_path;	\
    }									\
    if ((path_ptr) == (PATH *)NULL) {					\
        pd_rad_pp = (ccmn_spec_ptr)->pd_rad_data;			\
        for (i = 0; ((path_ptr) == (PATH *)NULL)			\
			&& (i < nrads)					\
			&& (myp->numa_dist_radtab[i] != -1); i++) {	\
            pd_rad = pd_rad_pp[myp->numa_dist_radtab[i]];			\
            if (pd_rad->Failed_path_cnt) {				\
	        (path_ptr) = pd_rad->rad_failed_paths.pq_flink->pq_path;\
            }								\
        }								\
    }									\
}

/* Get the translation pointer out of the path struct */
#define	GET_PATH_TRANS(trans_ptr, path_ptr)				\
{									\
    (trans_ptr)	= (TRANSLATION *)&((path_ptr)->pa_trans);		\
}


/* Macro to decrement item count on path.  When	removing Item for queue
   or when determined that we are not going to send the	I/O.  CCMN_SPEC
   must	be locked. Args	are PATH * */

/* PMK: pd_rad locked held coming in/out */
#define	DECR_PATH_ITEM_CNT(path_ptr)					\
{									\
    (path_ptr)->pa_path_que.pq_item_count--;				\
}

/* Macro to increment item count on path (retries) */
/* PMK: pd_rad locked held coming in/out */
#define	INCRE_PATH_ITEM_CNT(path_ptr)					\
{									\
    (path_ptr)->pa_path_que.pq_item_count++;				\
}

/*
 * Name:
 *	CHECK_PATH_IO_CMP  (see also PATH_IO_COMPLETED)
 *
 * Function:
 *	Macro to check an I/O path completion.	This will determine if the
 *	I/O is successful and return appropriate bit status. 
 *
 * Arguments:
 *	trans_ptr	- TRANSLATION pointer
 *	ccb_ptr		- DCB_SCSIIO pointer
 *	pdrv_ws_ptr	- working set pointer
 *	ccb_status	- valid CAM status
 *	path_status	- path status bit to be returned
 *	lock_act	- indicates state of the pd lock on entry and exit
 *
 * Returned status bits:
 *	PATH_OK	    - We have not determined that a path failure has happened.
 *	PATH_FAIL   - We have detected a Path failure and this ccb has reached
 *		      the event count.
 *	PATH_VIABLE - Indicates that there are other paths to the device.  Note
 *		      this bit may or may not be set when PATH_FAIL is set.
 *	PATH_READDR - This indicates that this CCB needs to be readdressed.
 *		      Will not be set when PATH_VIABLE is clear.
 *
 *  Additional information:	
 *	This macro will call the ccmn_check_path_fail3() 
 *	routine to determine course of action if a path fails. 
 *	This MACRO should be called after CCB removal from queues...
 */

/* PMK: check for pd_rad lock held */
#define CHECK_PATH_IO_CMP( trans_ptr, ccb_ptr, pdrv_ws_ptr,  ccb_status,\
		path_status, lock_act)					\
{									\
    int lock_act_local = lock_act;					\
									\
    if (!((lock_act_local) & PD_RAD_LOCKED)) {				\
	PD_RAD_LOCK((pdrv_ws_ptr)->pws_pd_rad);				\
    }									\
    (path_status) = PATH_OK;						\
    if ((ccb_status) ==	CAM_REQ_CMP) {					\
	(pdrv_ws_ptr)->pws_dev_path->pa_event_cnt = 0;			\
	(pdrv_ws_ptr)->pws_dev_path->pa_event_time.tv_sec = 0;		\
        if (pdrv3_debug &&                                              \
               (((pdrv_ws_ptr)->pws_dev_path->pa_cto_cnt ||             \
               (pdrv_ws_ptr)->pws_dev_path->pa_cto_time.tv_sec))) {     \
            printf("CHECK_PATH_IO_CMP: clearing counters\n");           \
        }                                                               \
        (pdrv_ws_ptr)->pws_dev_path->pa_cto_cnt = 0;                    \
        (pdrv_ws_ptr)->pws_dev_path->pa_cto_time.tv_sec = 0;            \
    }									\
    else {								\
	(path_status) = ccmn_check_io_path3((trans_ptr), (ccb_ptr),	\
		(pdrv_ws_ptr), (ccb_status),				\
		(PD_RAD_LOCKED | PD_RAD_LOCK_ON_EXIT));			\
    }									\
    if (!((lock_act_local) & PD_RAD_LOCK_ON_EXIT)) {			\
	PD_RAD_UNLOCK((pdrv_ws_ptr)->pws_pd_rad);			\
    }									\
}

/*
 * Name:
 *	PATH_IO_COMPLETED  (see also CHECK_PATH_IO_CMP)
 *
 * Function:
 *	Macro to set path info after a valid I/O completion
 *	(CAM status == CAM_REQ_CMP)
 *
 * Arguments:
 *	pdrv_ws_ptr	- working set pointer
 *	path_status	- path status bit to be returned
 *
 * Returned status bits:
 *	PATH_OK - We have not determined that a path failure has happened.
 *
 *  Additional information:
 *	This MACRO should be called after CCB removal from queues.
 *	PD_RAD lock must be taken prior to executing macro.	
 */

/* PMK: pd_rad not locked coming in/out */
#define PATH_IO_COMPLETED( pdrv_ws_ptr,	 path_status)			\
{									\
    (path_status) = PATH_OK;						\
    ((pdrv_ws_ptr)->pws_dev_path)->pa_event_cnt = 0;			\
    ((pdrv_ws_ptr)->pws_dev_path)->pa_event_time.tv_sec = 0;		\
    if (pdrv3_debug &&                                                  \
           (((pdrv_ws_ptr)->pws_dev_path->pa_cto_cnt ||                 \
           (pdrv_ws_ptr)->pws_dev_path->pa_cto_time.tv_sec))) {         \
        printf("CHECK_PATH_IO_CMP: clearing counters\n");               \
    }                                                                   \
    ((pdrv_ws_ptr)->pws_dev_path)->pa_cto_cnt = 0;                      \
    ((pdrv_ws_ptr)->pws_dev_path)->pa_cto_time.tv_sec = 0;              \
}

#define CURRENT_USEC(t, t_usec) {					\
    extern struct timeval time;						\
    TIME_READ(t);							\
    t_usec = t.tv_sec * 1000000L + t.tv_usec;				\
}

/*
 * NUMA Disk Statistics.
 *
 * The macro GET_NOW_USEC declares and fills in now_usec.
 * It is only intended to be used within the RAD_IO_*
 * macros below.
 *
 * If a routine that uses one of the RAD_IO_* macros
 * already has now_usec declared and initialized, call
 * the macro with the last argument blank.
 *
 * Otherwise, use GET_NOW_USEC as the last argument.
 */

#define GET_NOW_USEC \
	struct timeval timenow;		\
	long	       now_usec;	\
	CURRENT_USEC(timenow, now_usec);

/*
 * NUMA Disk Statistics.
 *
 * The following macros are used to keep proper track of
 * disk usage statistics on NUMA systems.
 *
 * Invoke RAD_IO_ACTIVE_CNT_INCR whenever (pd_rad)->IO_active_cnt
 * needs to be incremented. This macro will do the increment.
 *
 * That means a new I/O is getting scheduled for this device.
 *
 * If (pd_rad)->IO_active_cnt is being incremented from 0 to 1, the
 * macro will do an atomic increment on the global pd->pd_active_rad_count.
 * If that too was incremented from 0 to 1, it means that a new run
 * of I/O's on this device is starting. If so, the macro will set
 * the global pd->pd_global_timestamp to now_usec.
 *
 * If the old value of (pd)->pd_active_rad_count was not zero,
 * then I/O is already in progress on this device for some RAD
 * and we don't want to touch (pd)->pd_global_timestamp.
 *
 * When either of these macros are used, (pd_rad) should
 * already be locked, so (pd_rad)->IO_active_cnt++ is safe.
 */

#define RAD_IO_ACTIVE_CNT_INCR(pd,pd_rad,get_now_usec)		\
{								\
  if( (pd_rad)->IO_active_cnt++ == 0 ) {			\
    if( !atomic_incq( &((pd)->pd_active_rad_count) ) ) {	\
      get_now_usec;						\
      (pd)->pd_global_timestamp = now_usec;			\
    }								\
  }								\
}

/*
 * NUMA Disk Statistics.
 *
 * Invoke RAD_IO_ACTIVE_CNT_DECR wherever pd_rad->IO_active_cnt
 * needs to get decremented. This macro performs the decrement.
 *
 * This means an I/O was taken off the active queue because
 * it completed, aborted or was moved to the pending queue.
 *
 * If pd_rad->IO_active_cnt was decremented from 1 to 0, then this
 * macro atomically decrements pd->pd_active_rad_count.
 * pd->pd_active_rad_count must be kept accurate or disk
 * statistics will not be correct.
 *
 * When pd->pd_active_rad_count goes from 1 to zero, this
 * macro updates (pd)->pd_global_timestamp with the current
 * time now_usec in an atomic exchange operation. The old
 * value is put in last_usec.
 *
 * Then it adds the latest time slot (now_usec - last_usec) to
 * a global tally of time spent in the active queue, di_time.
 *
 * Note: Each CPU keeps track of the time spent in a
 * per-path, per-cpu di_time variable. Individual di_times
 * do not accurately reflect disk usage, only the sum of all
 * di_times for a given device is meaningful.
 */

#define RAD_IO_ACTIVE_CNT_DECR(pd,pd_rad,path,get_now_usec)			\
{										\
  if( --(pd_rad)->IO_active_cnt == 0 ) {					\
    if( atomic_decq( &((pd)->pd_active_rad_count) ) == 1 ) {			\
      long last_usec;								\
      get_now_usec;								\
      last_usec = atomic_excq( &((pd)->pd_global_timestamp), now_usec );	\
      (path)->pa_stats_percpu[1+current_cpu_rad_logical_index()].di_time +=	\
	(now_usec - last_usec);							\
    }										\
  }										\
}

/*
 * NUMA Disk Statistics.
 *
 * Invoke RAD_IO_CDISK_PREPARE_STATISTIC() in cdisk_get_statistics()
 * before we sum up all the di_times.
 *
 * There are three times when the (pd)->pd_global_timestamp is
 * updated, the first one is when a new seies of I/O is started,
 * the second when all I/O on a device has finished, and the third
 * if disk statistics are being gathered while an I/O is in progress.
 *
 * di_time is updated when all I/O on a device has finished or
 * if statistics are being gathered while an I/O is in progress.
 *
 * If (pd)->pd_active_rad_count is not zero, it means one or more
 * disk I/O's are in progress. If so, this macro updates
 * (pd)->pd_global_timestamp with the current time now_usec in an
 * atomic exchange operation. The old value is put in last_usec.
 *
 * Then it adds the latest time slot (now_usec - last_usec) to
 * a global tally of time spent in the active queue, di_time.
 *
 * If (pd)->pd_active_rad_count == 0, do nothing.
 */

#define RAD_IO_CDISK_PREPARE_STATISTICS(pd,pd_rad,path,get_now_usec)		\
{										\
  if( (pd)->pd_active_rad_count ) {						\
    long last_usec;								\
    get_now_usec;								\
    last_usec = atomic_excq( &((pd)->pd_global_timestamp), now_usec );		\
    (path)->pa_stats_percpu[1+current_cpu_rad_logical_index()].di_time +=	\
      (now_usec - last_usec);							\
  }										\
}

/* PMK: PD_RAD ALWAYS LOCK held coming in/out */
#define PWS_CCB_QUE_REMOVE( pd_rad, path, pws, c3cb, abort )		\
{									\
   struct timeval timenow;						\
   long 	  now_usec;	      					\
									\
   (abort) = 0;								\
   DECR_PATH_ITEM_CNT(path)						\
   if ((pws)->pws_flags & PWS_ACT_QUE) {	/* Active Que */	\
									\
      /*								\
       * NUMA Disk Statistics.						\
       * Instead of doing (pd_rad)->IO_active_cnt--;			\
       * Get current time and invoke RAD_IO_ACTIVE_CNT_DECR().		\
       */								\
      CURRENT_USEC(timenow, now_usec);					\
      RAD_IO_ACTIVE_CNT_DECR( (pd_rad)->rad_pd_ccmn, pd_rad, (pws)->pws_dev_path, /*BLANK*/ );	\
									\
      remque ((struct queue_entry *)(pws));				\
      (pws)->pws_flags &= ~PWS_ACT_QUE;					\
      /* CAM_STATS_FINISH is called in cdisk_complete */		\
   }									\
   else if ((pws)->pws_flags & PWS_PEND_QUE) { /* Pending Que */	\
      (pd_rad)->IO_pending_cnt--;					\
      remque ((struct queue_entry *)(pws));				\
      (pws)->pws_flags &= ~PWS_PEND_QUE;				\
      /*								\
       * Record time spent in pending queue.				\
       */								\
      CURRENT_USEC(timenow, now_usec);					\
      if ((pws)->start_time > 0L)                                       \
          (pws)->pending_delta = (now_usec - (pws)->start_time);        \
   }									\
   else if ((pws)->pws_flags & PWS_ABORT_QUE) { /* Abort Que */		\
      (pd_rad)->IO_abort_cnt--;						\
      remque((struct queue_entry *)(pws));				\
      (pws)->pws_flags &= ~PWS_ABORT_QUE;				\
      abort++;								\
      CURRENT_USEC(timenow, now_usec);					\
   }									\
   else {								\
      PD_RAD_UNLOCK( pd_rad ); 	/* Unlock before panic..... */		\
      panic("PWS_CCB_QUE_REMOVE: ccb not on any list");			\
   }									\
   path->pa_initial_busy = now_usec;					\
   /*                                                                   \
    * We only want to update credit manager information if this is      \
    * tagged IO. Non tagged IO isn't regulated by the credit manager    \
    * and therefore shouldn't contribute to its calculations.           \
    * QAR 97779                                                         \
    */                                                                  \
   if (c3cb->cam_tag_action != 0) {                                     \
      if (timenow.tv_sec >= (pd_rad)->IO_cred_rel_time) {		\
         ccmn_credit_mgr(pws->pws_ccmn, (pd_rad), QTAG_CREDIT_TMO);	\
      }                                                                 \
      if ((c3cb->cam_scsi_status == SCSI_STAT_QUEUE_FULL) ||		\
           ((pws->pws_ccb->cam_ch.cam_status & CAM_STATUS_MASK)         \
                                               == CAM_CMD_TIMEOUT)) {   \
         ccmn_credit_mgr(pws->pws_ccmn, (pd_rad),                       \
              (c3cb->cam_scsi_status == (SCSI_STAT_QUEUE_FULL?          \
                      QTAG_CREDIT_QFULL: QTAG_CREDIT_CMD_TMO)));        \
     }                                                                  \
   } 									\
}

/* PMK: PD_RAD ALWAYS LOCK held coming in/out */
#define REM_CCB3( pd, pd_rad, path, pws, c3cb, repended )               \
{									\
   int abort;								\
   PWS_CCB_QUE_REMOVE( pd_rad, path, pws, c3cb, abort );		\
   if (abort == 0) {							\
      SEND_PENDING_CCB3( pd, pd_rad, repended );                        \
   }									\
}

/* PMK: PD_RAD ALWAYS LOCK held coming in/out */
#define SEND_PENDING_CCB3( pd, pd_rad, repended )			\
{									\
    DCB_SCSIIO          *next_ccb;					\
    PDRV3_WS            *pws;						\
    TRANSLATION         *trans;						\
    CAM_U32             status;						\
									\
    (repended) = 0;                                                       \
    while ((pd_rad)->IO_pending_cnt) {					\
        if ((pd_rad)->IO_cred_tot_cnt > (pd_rad)->IO_active_cnt) {	\
            pws = (PDRV3_WS *)dequeue_head(&(pd_rad)->IO_pending);	\
            if (pws == (PDRV3_WS *)NULL) {				\
                break;							\
            }								\
            (pd_rad)->IO_pending_cnt--;					\
            enqueue_tail(&(pd_rad)->IO_active, (queue_entry_t)pws);	\
									\
	    /*								\
	     * NUMA Disk Statistics.					\
	     * Instead of doing (pd_rad)->IO_active_cnt++;		\
	     * invoke RAD_IO_ACTIVE_CNT_INCR().				\
	     */								\
	    RAD_IO_ACTIVE_CNT_INCR( pd, pd_rad, GET_NOW_USEC );		\
									\
            pws->pws_flags &= ~PWS_PEND_QUE;				\
            pws->pws_flags |= PWS_ACT_QUE;				\
            CAM_STATS_PENDING(pws)					\
            pws->pws_flags &= ~PWS_CALLBACK;				\
            next_ccb = pws->pws_ccb;					\
            GET_PATH_TRANS(trans, pws->pws_dev_path);			\
            PRINTD(T_PORT(trans), T_TARGET(trans), T_LUN(trans), CAMD_COMMON,\
               ("[%d/%d/%d] ccmn_send_pending_ccb3: pending ccb 0x%x sent to XPT\n",\
               T_PORT(trans), T_TARGET(trans), T_LUN(trans), next_ccb));\
									\
            PD_RAD_UNLOCK( pd_rad );					\
									\
    	    if (pws->pws_dev_path->pa_jump.jmp_entry) {			\
        	status = pws->pws_dev_path->pa_jump.jmp_entry((CCB_HEADER *)next_ccb,\
                                pws->pws_dev_path->pa_jump.arg1,	\
                                pws->pws_dev_path->pa_jump.arg2,	\
                                pws->pws_dev_path->pa_jump.arg3,	\
                                pws->pws_dev_path->pa_jump.arg4);	\
    	    }								\
    	    else {							\
                status = xpt_action((CCB_HEADER*)next_ccb);		\
    	    }								\
									\
            PD_RAD_LOCK( pd_rad );					\
            if (status != CAM_REQ_INPROG) {				\
                PRINTD(T_PORT(trans), T_TARGET(trans), T_LUN(trans),	\
                      (CAMD_COMMON | CAMD_FLOW),			\
                      ("ccmn_send_pending_ccb3: pending CCB 0x%x status 0x%x\n",\
                      T_PORT(trans), T_TARGET(trans), T_LUN(trans),	\
                      next_ccb, next_ccb->cam_ch.cam_status));		\
		if (pws->pws_flags & PWS_ACTIVE) {			\
		    remque((queue_entry_t)pws);				\
									\
		    /*							\
		     * NUMA Disk Statistics.				\
		     * Instead of doing (pd_rad)->IO_active_cnt--;	\
		     * invoke RAD_IO_ACTIVE_CNT_DECR().			\
		     */							\
		    RAD_IO_ACTIVE_CNT_DECR( pd, pd_rad, pws->pws_dev_path, GET_NOW_USEC );	\
									\
		    pws->pws_flags &= ~PWS_ACT_QUE;			\
		    CLEAR_CCB3(next_ccb, 0);				\
		    pws->pws_flags |= PWS_PEND_QUE;			\
		    enqueue_head(&(pd_rad)->IO_pending, (queue_entry_t)pws);\
		    (pd_rad)->IO_pending_cnt++;				\
                    if ((pd_rad)->IO_active_cnt == 0 )                  \
                         (repended) = 1;                                \
		}							\
                break;							\
            }								\
        }								\
        else {								\
	    if ((pd)->pd_qtag_free ||					\
	        ((pd_rad)->IO_cred_tot_cnt < (pd)->pd_qtag_optimal)) {	\
	        ccmn_credit_mgr(pd, pd_rad, QTAG_CREDIT_REQ);		\
	        if (pd_rad->IO_cred_tot_cnt > pd_rad->IO_active_cnt) {	\
	    	    continue;						\
	        }							\
	    }								\
            break;							\
        }								\
    }									\
    if (((pd_rad)->IO_active_cnt == 0) &&				\
        ((pd_rad)->IO_cred_tot_cnt > (pd_rad)->IO_cred_resv_cnt)) {	\
        ccmn_credit_mgr(pd, pd_rad, QTAG_CREDIT_REL);			\
    }									\
}

/* PMK: PD_RAD ALWAYS LOCK held coming in/ UNLOCKED out */
#define SEND_CCB3( pd, pd_rad, path, pws, ccb, status, repended )       \
{									\
    struct timeval timenow;						\
    long 	   now_usec;	      					\
    int	           local_execution = 1;					\
    int            done = 0;						\
									\
    (pws)->pws_flags &= ~(PWS_ACT_QUE | PWS_PEND_QUE);			\
    INCRE_PATH_ITEM_CNT(path);						\
    if ((pd_rad)->IO_active_cnt == 0) {					\
        CURRENT_USEC(timenow, now_usec);				\
        path->pa_initial_busy = now_usec;				\
    }									\
    if (!(((ccb)->cam_flags ^ CAM_QUEUE_ENABLE) &			\
          (CAM_QUEUE_ENABLE | CAM_SIM_QHEAD)) ) {			\
									\
        /* Check for across RAD IO, limit execution to no active cnt */	\
        if (current_execution_radid() != (pd_rad)->locality_context.rad_id) {\
            (pd_rad)->cross_rad_iocnt++;  				\
            if ((pd_rad)->IO_active_cnt) { 				\
	        local_execution = 0;					\
	        goto pend;						\
	    }								\
	    else {							\
                (pd_rad)->cross_rad_initiated_iocnt++;  		\
	    }								\
	}								\
        if (((pd_rad)->IO_pending_cnt) ||				\
	    ((pd_rad)->IO_cred_tot_cnt <= (pd_rad)->IO_active_cnt)) {	\
pend:									\
                (ccb)->cam_status = CAM_REQ_INPROG;			\
                (pws)->pws_flags |= PWS_PEND_QUE;			\
                enqueue_tail(&(pd_rad)->IO_pending, (queue_entry_t)(pws));\
                (pd_rad)->IO_pending_cnt++;				\
	        if (local_execution) {					\
		    SEND_PENDING_CCB3( pd, pd_rad, repended );		\
	        }							\
                PD_RAD_UNLOCK( (pd_rad) );				\
                status = CAM_REQ_INPROG;				\
                done = 1;						\
        }								\
    }									\
    if (!done) {							\
        (pws)->pws_flags &= ~PWS_CALLBACK;				\
        (pws)->pws_flags |= PWS_ACT_QUE;				\
        enqueue_tail(&(pd_rad)->IO_active, (queue_entry_t)(pws));	\
									\
	/*								\
	 * NUMA Disk Statistics.					\
	 * Instead of doing (pd_rad)->IO_active_cnt++;			\
	 * invoke RAD_IO_ACTIVE_CNT_INCR().				\
	 * now_usec is valid if pd_rad->IO_active_cnt == 0		\
	 * which is the only time this macro needs it.			\
	 */								\
	RAD_IO_ACTIVE_CNT_INCR( pd, pd_rad, /*BLANK*/ );		\
									\
        PD_RAD_UNLOCK( (pd_rad) );					\
									\
        if (path->pa_jump.jmp_entry) {					\
            status = path->pa_jump.jmp_entry((CCB_HEADER *)ccb,		\
                                         path->pa_jump.arg1,		\
                                         path->pa_jump.arg2,		\
                                         path->pa_jump.arg3,		\
                                         path->pa_jump.arg4);		\
        }								\
        else {								\
            status = xpt_action(ccb);					\
        }								\
    }									\
}

#define BASE_PING 		30	/* Base time for first ping	*/
#define MONITORING_CYCLE_TIME 	15 	/* Number of seconds the thread 
					   wakes */
#define MAX_PING_TIME		(60 * 3) /* 3 minutes */

/* PATH	Monitoring macros and defines */

#define PATH_MON_QUE_LOCKED	0x01
#define PATH_MON_QUE_UNLOCKED	0x00

#define	PATH_INSERT_MON_QUE(path_ptr, lock_indicator)			\
{									\
    struct timeval pingtime;						\
    if(!(lock_indicator)){						\
        CCMN_PATH_MON_LOCK(&mon_path_queue)				\
    }									\
    if(((path_ptr)->pa_pathing_type & PATH_MONITOR) &&			\
	     (!((path_ptr)->pa_monitor_que.pq_flags & PQ_MONITORING))){	\
        TIME_READ(pingtime);						\
	if(((path_ptr)->pa_monitor_que.pq_flink) || ((path_ptr)->pa_monitor_que.pq_blink)){\
		panic("Second MONITOR insert");				\
	}								\
        (path_ptr)->pa_ping_time.tv_sec = pingtime.tv_sec + BASE_PING;  \
        enqueue_tail((queue_t)&mon_path_queue.mo_path_mon,		\
		(queue_entry_t)&(path_ptr)->pa_monitor_que);		\
	mon_path_queue.mo_path_mon.pq_item_count++;			\
	(path_ptr)->pa_monitor_que.pq_flags |= PQ_MONITORING;		\
        if( mon_path_queue.mo_path_mon.pq_item_count == 1){		\
		(void)timeout((void(*)(void *))wakeup,			\
				(caddr_t)&mon_path_queue.mo_path_mon,	\
				(hz * MONITORING_CYCLE_TIME));		\
	}								\
    }									\
    if(!(lock_indicator)){						\
	CCMN_PATH_MON_UNLOCK(&mon_path_queue)				\
    }									\
}
	
#define	PATH_REM_MON_QUE(path_ptr, mon_lock, pdrv_lock)			\
{									\
    int mon_lock_local = mon_lock;					\
    int pdrv_lock_local = pdrv_lock;					\
									\
    if(!(mon_lock_local)){						\
	CCMN_PATH_MON_LOCK(&mon_path_queue)				\
    }									\
    while( (path_ptr)->pa_monitor_que.pq_flags & PQ_INQ_PING ){		\
	    (path_ptr)->pa_monitor_que.pq_flags |= PQ_WAITING_FOR;	\
	    assert_wait((vm_offset_t)(path_ptr), FALSE);		\
	    CCMN_PATH_MON_UNLOCK(&mon_path_queue);			\
	    if((pdrv_lock_local)){					\
	        CCMN_UNLOCK((path_ptr)->pa_info_hdr->pi_specific);	\
	    }								\
	    thread_block();						\
	    if((pdrv_lock_local)){					\
		CCMN_LOCK((path_ptr)->pa_info_hdr->pi_specific);	\
	    }								\
	    CCMN_PATH_MON_LOCK(&mon_path_queue);			\
    }									\
    if ( (path_ptr)->pa_monitor_que.pq_flink ) {			\
	    remque((struct queue_entry *)(&(path_ptr)->pa_monitor_que));\
	    mon_path_queue.mo_path_mon.pq_item_count--;			\
	    (path_ptr)->pa_monitor_que.pq_flink = 			\
			(path_ptr)->pa_monitor_que.pq_blink = 		\
			(PATH_QUE *)NULL;				\
	    (path_ptr)->pa_monitor_que.pq_flags &= ~PQ_MONITORING;	\
	    (path_ptr)->pa_ping_count = 0;				\
	    (path_ptr)->pa_ping_time.tv_sec = 0;			\
    }									\
    if(!(mon_lock_local)){							\
	CCMN_PATH_MON_UNLOCK(&mon_path_queue)				\
    }									\
}

/* Free memory associated with a path struct */
#define CCMN_PATH_FREE( path_ptr, mon_lock, pdrv_lock )			\
{									\
    if ( (path_ptr)->pa_monitor_que.pq_flink ) {			\
	PATH_REM_MON_QUE((path_ptr), (mon_lock), (pdrv_lock));		\
    }									\
    xpt_mem_free((CAM_VM_OFFSET)(path_ptr));				\
}

/* Macros to insert and remove for pinq active queues mon_path_queue
 * Must be locked 
 */
#define INSERT_MON_PATH_ACT(path_ptr)					\
{									\
    enqueue_tail((queue_t)&mon_path_queue.mo_path_mon_act,		\
		((queue_entry_t)&(path_ptr)->pa_mon_act_que));		\
    (path_ptr)->pa_monitor_que.pq_flags |= PQ_INQ_PING;			\
}

#define REMOVE_MON_PATH_ACT(path_ptr)					\
{									\
    remque((struct queue_entry *)(&(path_ptr)->pa_mon_act_que));	\
    (path_ptr)->pa_monitor_que.pq_flags &= ~PQ_INQ_PING;		\
    if((path_ptr)->pa_monitor_que.pq_flags & PQ_WAITING_FOR){		\
	(path_ptr)->pa_monitor_que.pq_flags &= ~PQ_WAITING_FOR;		\
	(void)wakeup((path_ptr));					\
    }									\
}


/* 
 * Structure for reporting number of paths and the respective path
 * pointers.  Used a 2 step process get the number then get the pointers.
 * See ccmn_get_path_cnt3() and ccmn_get_path_list()
 */

typedef struct path_list {
    CAM_U64	list_flags;	/* Which paths (active/standby/failed) 
				   Uses pa_stateflags defines */
    CAM_U64	list_cnt;	/* Number of paths ccmn_get_path_cnt3
				   or number of pointer to fill in list */
    CAM_U64     list_ret_cnt;	/* Number of pointers returned */
    PATH	**list_path_ptrs;/* Pointer to an array pointers */
}PATH_LIST;

/*
 * Defined index values for the ccmn_path_rpt structure (EHM reporting)
 */
#define CCMN_PORT_IDX 		0
#define CCMN_TARGET_IDX		1
#define CCMN_LUN_IDX		2
#define CCMN_DEVPATH_CNT_IDX	3
#define CCMN_PATH_STATE_IDX	4
#define CCMN_EHM_NEW_STATE_IDX	5
#define CCMN_PATH_XFER_IDX	6
#define CCMN_PATH_WDS_IDX	7
#define CCMN_PATH_AVSER_IDX	8
#define CCMN_PATH_PXFER_IDX	9
#define CCMN_PATH_AVWAIT_IDX	10
#ifdef PATH_STATISTICS /* Path scanning statistics collection */
#define CCMN_PATH_TOP_BEST_IDX  11
#define CCMN_PATH_TOP_WORST_IDX 12
#define CCMN_PATH_TOP_AVG_IDX   13
#define CCMN_PATH_TOP_CNT_IDX   14
#define CCMN_PATH_NUM_ATTR	15	/* Number of attributes */
#else /* no path scanning statistics collection */
#define CCMN_PATH_NUM_ATTR	11	/* Number of attributes */
#endif /* PATH_STATISTICS */

/************************************************************************
 * :tag::	CAM-3 common driver structure -	CCMN_SPECIFIC
 ************************************************************************/

/*
 * Forward and backward	link structure.
 */
typedef	struct pd3_list	{
	PDRV3_WS   *flink;
	PDRV3_WS   *blink;
} PD3_LIST;

/*
 * Define allocation for INQUIRY buffer	to have	it aligned
 */
#define	ALIGN_MASK (sizeof(caddr_t) - 1)
#define	INQLEN_ALLOC ((INQLEN +	ALIGN_MASK) & ~ALIGN_MASK)

/*
 * PMK: New credit and per RAD structures 
 */

/* 
 * I/O Qhead lists
 */
typedef struct scsi_io_qhead {
    PDRV3_WS            *qhd_flink;
    PDRV3_WS            *qhd_blink;
    CAM_U64              qhd_cnt;
} SCSI_IO_QHEAD;

/* 
 * RAD Granularity Token struct either per RAD or CPU for device
 * I/O management 
 */

typedef struct scsi_io_resources {
    SCSI_QTAG_CREDITS	qtag_credits;
    SCSI_IO_QHEAD       io_active;        /* Active I/Os                      */
    SCSI_IO_QHEAD       io_pending;       /* Pending I/Os, waiting to be sent */
    SCSI_IO_QHEAD       io_abort;         /* I/Os that have been aborted      */
} SCSI_IO_RESOURCES;

typedef struct pd_rad_data {
    XPT_LOCK_DATA	 rad_lock;     	    	/* SMP lock structure 16 bytes*/
    LOCALITY_CONTEXT 	 locality_context;	/* RAD locality context       */

    /* IO Queuing structures and data */
    SCSI_IO_RESOURCES	 rad_io_data;

#define IO_resources          	rad_io_data
#define IO_credits         	IO_resources.qtag_credits
#define IO_cred_init            IO_credits.qtag_cred_init
#define IO_cred_tot_cnt         IO_credits.qtag_cred_tot_cnt
#define IO_cred_resv_cnt       	IO_credits.qtag_cred_resv_cnt
#define IO_cred_rel_time       	IO_credits.qtag_cred_rel_time.tv_sec
#define IO_active          	IO_resources.io_active
#define IO_active_cnt      	IO_active.qhd_cnt
#define IO_pending         	IO_resources.io_pending
#define IO_pending_cnt     	IO_pending.qhd_cnt
#define IO_abort           	IO_resources.io_abort
#define IO_abort_cnt       	IO_abort.qhd_cnt

    /* Path Queuing structures and data */
    PATH_QUE		 rad_active_paths;  /* Queue of active paths          */
    PATH_QUE  		 rad_standby_paths; /* Queue of failover to paths     */
    PATH_QUE  		 rad_failed_paths;  /* Queue of failed paths          */
    PATH_QUE  		 rad_temp_paths;    /* Temporary linkage until we     */
                                            /* decide what to do with this    */                                            /* container                      */
    PATH_QUE  		 rad_inactive_paths;/* Queue of paths not allowed to  */
                                            /* use                            */
#define Active_path_cnt    	rad_active_paths.pq_item_count
#define Standby_path_cnt   	rad_standby_paths.pq_item_count
#define Failed_path_cnt    	rad_failed_paths.pq_item_count
#define Temp_path_cnt      	rad_temp_paths.pq_item_count
#define Inactive_path_cnt	rad_inactive_paths.pq_item_count

    struct ccmn_specific *rad_pd_ccmn;		/* Ptr to peripheral device   */
    void   *driver_rad_specific;		/* specific to driver	      */
    U32	   driver_rad_specific_size;		/* Size of driver spec data   */
    U64    cross_rad_iocnt;			/* Number of cross rad io's   */
    U64    cross_rad_initiated_iocnt;		/* Number of io's initiated   */
    U64	   reserved[14];

} PD_RAD_DATA;

typedef	struct ccmn_specific {
	XPT_LOCK_DATA  	pd_lock;		/* SMP lock structure	*/
/*
 * Pointers to related device specific	structure, SMP lock data
 */
	DEV_DESC 	*pd_dev_desc;		/* Pointer to device descriptor*/
	void		*pd_dev_specific;	/* Device specific structure*/

	struct pd_rad_data **pd_rad_data; 	/* Ptr to array of ptrs to 
					     	   pd_rad_data structure    */

	U32 pd_qdepth_max;	/* Maximum number of commands for the unit   */
        I32 pd_qdepth_alloc;    /* Tagged queue depth - indicates the        */
                                /* maximum number of commands the unit       */
                                /* can store currently.                      */
                                /* (Cluster activity dependent.)             */
	U32 pd_qtag_optimal;	/* Number of tags for each init'ed rad 	     */
				/* If all have a full load of I/O	     */
	U32 pd_qtag_doled;	/* How many qtags have we doled out	     */
	U32 pd_qtag_free;	/* BINARY: true if we have free tags 	     */
				/* if (pd_qdepth_alloc - pd_qtag_doled)      */
	U32 pd_qtag_shorted;    /* BINARY: true if a rad less than optimal   */
	U32 pd_qtag_stall;	/* BINARY: qfull stall new credit requests   */
	U32 pd_qtag_rad_init;	/* Number of rads that asked for qtags       */
	U32 pd_que_full_cnt;	/* Number of queue fulls for device 	     */
        U32 pd_cmd_tmo_cnt;     /* Number of command timeouts           */
/*
 * Tag queue depth management
 */
        U32 pd_tag_adjust_flag; /* Free tag adjustment due              */
        struct  timeval pd_adjust_time; /* Free tag count adjust due time */


	PATH_INFO_HDR 	pd_path_info;		/* Path info, etc.    */
/*
 * Queues and queue counters, sense data
 */
	caddr_t	 pd_sense_ptr;	/* Pointer to the last sense data	*/
	U16 pd_sense_len;	/* Length of last sense	data		*/
	U16 pd_sense_max;	/* Max sense data acceptable to	device	*/
/*
 * Device definition  &	state
 */
	dev_t	pd_dev;		/* CAM major/minor number		*/
	U32	pd_logical_id;	/* The logical ID of the device.	*/
	U32	pd_drv_state;	/* Device state	flags			*/
/*
 * Mode	select index; error monitoring and recovery
 */
	U32 pd_ms_index;		/* Contains the	current	index into the	*/
					/* Mode	Select Table when sending Mode	*/
					/* Select data on first	open		*/
	U32 pd_errlog;			/* error log disable one shot toggle	*/
	U32 pd_soft_err;		/* Number of soft errors		*/
	U32 pd_hard_err;		/* Number of hard errors		*/
	U32 pd_soft_err_limit;		/* Max no. of soft errors to report	*/
	U32 pd_hard_err_limit;		/* Max no. of hard errors to report	*/
					/* be used for recovery			*/
/* 
 *  Total counts for per RAD items
 */
        U32 pd_active_cnt;      	/* Total active ccb cnt - all rads */
        U32 pd_pending_cnt;        	/* Total pending ccb cnt - all rads */
        U32 pd_active_paths_cnt; 	/* Total active paths cnt - all rads */
        U32 pd_standby_paths_cnt; 	/* Total standby paths cnt - all rads */
        U32 pd_failed_paths_cnt; 	/* Total failed paths cnt - all rads */
        U32 pd_inactive_paths_cnt; 	/* Total inactive paths cnt - all rads */

	U64 pd_cross_rad_iocnt;		/* Number of cross rad io's */
	U64 pd_cross_rad_initiated_iocnt;/* Number of io's initiated  */
/*
 * Inquiry buffer
 */
	U8  pd_dev_inq[INQLEN_ALLOC];
/*
 * Hardware management data
 */
	MSS	*pd_mss;		/* Pointer to MSS for hardware mgmt	*/
	char	*pd_phys_location;	/* physical location name for ehm	*/
	char	*pd_unique_name;	/* Unique name for hardware mgmt	*/
	void	*pd_dev_handle;		/* hardware management handle		*/
	long	pd_hardware_id;		/* hardware ID for this device		*/
	U32	pd_hwc_flags;		/* Unique Id Flags for hardware mgmt	*/
	int	pd_access;		/* Access attribute flags		*/
	long	pd_consistent_name;	/* Consistent WWID flag	(for LSM)	*/
	U32	pd_max_record;		/* Copy of dev_desc->dd_max_record	*/
	U32	pd_pad2;		/* pad */

/*
 * NUMA Disk Statistics.
 *
 * pd_active_rad_count is updated whenever a RAD's active count goes
 * from 0 to 1 or 1 to 0. The RADs must ONLY use atomic_incq() or
 * atomic_decq() to change this variable.
 *
 * pd_global_timestamp is updated with the current time in microseconds
 * whenever the first RAD goes active (pd_active_rad_count goes from 0 to 1)
 * and when all I/O has completed (when pd_active_rad_count goes from 1 to 0).
 * It also gets updated if disk statistics is being gathered while I/O
 * is in progress. See the macros RAD_IO_* above.
 *
 * This allows us to keep accurate disk statistics with minimum overhead.
 */

	U64	pd_active_rad_count;	/* Number of currently active RADs. */
	U64	pd_global_timestamp;	/* Global NUMA Disk Usage Time Stamp. */

} CCMN_SPECIFIC;

    
/************************************************************************
 * :tag::	EEI (Extended Error Information) support
 ************************************************************************/

typedef	struct cam_eei_status {
  u_int	flags;			/* EEI CAM/SCSI	status flags */
  u_short status;		/* EEI status overlay */
  u_char cam_status;		/* CAM status */
  u_char scsi_status;		/* SCSI	status */
} CAM_EEI_STATUS;

/* Flags passed	to ccmn	EEI functions. */

#define	CAM_EEIF_DRV_NOTLOCKED	0x0	/* The PDRV struct is NOT locked */
#define	CAM_EEIF_DRV_LOCKED	0x10	/* The PDRV struct is locked */

/* Clear cam eei status	 */
#define	CLEAR_CAM_EEI_STATUS( cam_status )		\
{							\
	(cam_status)->status = EEI_NO_STATUS;		\
	(cam_status)->flags  = 0;			\
}

/*******************************************************************
 * :tag::	CAM-1 /	CAM-3 testing and translation
 *******************************************************************/
/*
 * IS_CAM3_SIM
 * Macro returns true for CAM-3	type SIM
 * Argument - port_id
 *	      cbus	*CAM_SCSI_BUS
 */
#define	IS_CAM3_SIM(port_id, cbus)			   \
    (  ((port_id) != XPT_PATH_INQ_ID)			   \
    && ((cbus =	ccmn_get_cam_scsi_bus((port_id))) != NULL) \
    && (cbus->sim_cam_type != 0) )

/************************************************************************
 * :tag::	CAM-3 Lock macros for ccmn_specific
 ************************************************************************/

#define	PD_RAD_INIT_LOCK( rad_ptr )				\
{								\
    XPT_INIT_LOCK( &(rad_ptr)->rad_lock, cam_pd_rad_device3_li);\
}

#define	PD_RAD_TERMINATE_LOCK( rad_ptr )	\
{						\
    XPT_TERMINATE_LOCK( &(rad_ptr)->rad_lock );	\
}

#define	PD_RAD_LOCK( rad_ptr )			\
{						\
    XPT_LOCK (&(rad_ptr)->rad_lock);		\
}

#define	PD_RAD_UNLOCK( rad_ptr )		\
{						\
    XPT_UNLOCK (&(rad_ptr)->rad_lock);		\
}

#define	PD_RAD_SPINLOCK( rad_ptr )		\
{						\
    XPT_SPINLOCK(&(rad_ptr)->rad_lock);		\
}

#define	PD_RAD_SPINUNLOCK( rad_ptr )		\
{						\
    XPT_SPINUNLOCK(&(rad_ptr)->rad_lock);	\
}

#define	CCMN_INIT_LOCK(	ccmn_ptr )			    \
{							    \
    XPT_INIT_LOCK( &(ccmn_ptr)->pd_lock, cam_pd_device3_li);\
}

#define	CCMN_TERMINATE_LOCK( ccmn_ptr )		\
{						\
    XPT_TERMINATE_LOCK( &(ccmn_ptr)->pd_lock );	\
}

#define	CCMN_SPINLOCK( ccmn_ptr	)		\
{						\
    XPT_SPINLOCK(&(ccmn_ptr)->pd_lock);		\
}

#define	CCMN_SPINUNLOCK( ccmn_ptr )		\
{						\
    XPT_SPINUNLOCK(&(ccmn_ptr)->pd_lock);	\
}

#define	CCMN_LOCK( ccmn_ptr )			\
{						\
    XPT_LOCK (&(ccmn_ptr)->pd_lock); 		\
}

#define	CCMN_UNLOCK( ccmn_ptr )			\
{						\
    XPT_UNLOCK (&(ccmn_ptr)->pd_lock); 		\
}

#define	CCMN_LOWER_IPL(	ccmn_ptr )		\
{						\
    splx ((ccmn_ptr)->pd_lock.xpt_saveipl);	\
}

/* Lock marcos for PATH monitoring queues */
#define CCMN_PATH_MON_LOCK(mon_que_ptr)		\
{						\
    XPT_LOCK(&(mon_que_ptr)->mo_path_lck);	\
}

#define CCMN_PATH_MON_UNLOCK(mon_que_ptr)	\
{						\
    XPT_UNLOCK(&(mon_que_ptr)->mo_path_lck);	\
}

/*
 * CCMN_SLEEPUNLOCK
 *	Macro lowers the IPL to the value stored in the lock structure
 *	and waits.
 *	Exit from wait is either on event or on signal (if PCATCH flag is
 *	set in the `pri` argument
 * Arguments:
 *	chan		- event pointer
 *	pri		- sleep priority (optionally ORed with PCATCH
 *	ccmn_ptr	- points to CCMN_SPECIFIC structure
 * Returns:
 *	N/A
 */

#define	CCMN_SLEEPUNLOCK( chan,	pri, ccmn_ptr )			\
{								\
    int spl_val = (ccmn_ptr)->pd_lock.xpt_saveipl;		\
    assert_wait(((vm_offset_t)(chan)), ((pri) & PCATCH));	\
    mpsleep((void *)NULL, (pri), "Zzzzzz", 0,			\
		(void *)&((ccmn_ptr)->pd_lock.xpt_lk_data),	\
		(MS_LOCK_NO_RELOCK | MS_LOCK_SIMPLE));		\
    splx (spl_val);						\
}

/*
 * CCMN_SLEEPUNLOCK_W_STAT
 *	Macro lowers the IPL to the value stored in the lock structure
 *	and waits.
 *	Exit from wait is either on event or on signal (if PCATCH flag is
 *	set in the `pri` argument
 * Arguments:
 *	chan		- event pointer
 *	pri		- sleep priority (optionally ORed with PCATCH
 *	ccmn_ptr	- points to CCMN_SPECIFIC structure
 *	msg		- pointer to optional message
 *	tmo		- timeout if event does not occur (0 - no timeout)
 *	status		- returned mpsleep() status
 * Returns:
 *	0		- waked-up by expected event on `chan`.
 *	If PCATCH is set and a signal needs to be delivered,
 *	ERESTART is returned if the current system call should be restarted
 *	(if possible), and EINTR is returned if the system call should
 *	be interrupted by the signal.
 */

#define	CCMN_SLEEPUNLOCK_W_STAT( chan, pri, ccmn_ptr, msg, tmo, status ) \
{								\
    int spl_val = (ccmn_ptr)->pd_lock.xpt_saveipl;		\
    assert_wait(((vm_offset_t)(chan)), ((pri) & PCATCH));	\
    status = mpsleep((void *)NULL, (pri), (msg), (tmo),		\
		(void *)&((ccmn_ptr)->pd_lock.xpt_lk_data),	\
		(MS_LOCK_NO_RELOCK | MS_LOCK_SIMPLE));		\
    splx (spl_val);						\
}

/* The following macro is a dup of the above one, only difference is
 * instead of PD lock we pass in the rad lock
 */
#define	CCMN_SLEEPUNLOCK_RAD_W_STAT( chan, pri, rad_ptr, msg, tmo, status ) \
{								\
    int spl_val = (rad_ptr)->rad_lock.xpt_saveipl;		\
    assert_wait(((vm_offset_t)(chan)), ((pri) & PCATCH));	\
    status = mpsleep((void *)NULL, (pri), (msg), (tmo),		\
		(void *)&((rad_ptr)->rad_lock.xpt_lk_data),	\
		(MS_LOCK_NO_RELOCK | MS_LOCK_SIMPLE));		\
    splx (spl_val);						\
}


/*****************************************************************************
 * :tag::	Macros to set, clear and check CCMN_SPECIFIC.pd_drv_state flags.
 *****************************************************************************/

/*
 * CCMN_WAITSET_DRV_STATE
 *
 * Arguments:
 *	pd	   - points to CCMN_SPECIFIC
 *	flags	   - to set in CCMN_SPECIFIC.pd_drv_state
 *	lock_flags - pd lock state on entry and exit
 */

#define	CCMN_WAITSET_DRV_STATE(	pd, flags, lock_flags )		\
{								\
    int lock_flags_local = lock_flags;				\
								\
    if (!(lock_flags_local & PD_LOCKED)) {			\
	CCMN_LOCK(pd);						\
    }								\
    while( (pd)->pd_drv_state != 0 ) {				\
	CCMN_SLEEPUNLOCK(&(pd)->pd_drv_state,			\
			(pd)->pd_lock.xpt_saveipl,(pd));	\
	CCMN_LOCK(pd);						\
    }								\
    (pd)->pd_drv_state |= (flags);				\
    if (!(lock_flags_local & PD_LOCK_ON_EXIT)) {		\
	CCMN_UNLOCK(pd);					\
    }								\
}

/*
 * CCMN_CLR_DRV_STATE
 *
 * Arguments:
 *	pd	   - points to CCMN_SPECIFIC
 *	flags	   - to clear in CCMN_SPECIFIC.pd_drv_state
 */
#pragma inline (ccmn_clr_drv_state)
#define	CCMN_CLR_DRV_STATE( pd,	flags, lock_flags)      ccmn_clr_drv_state( pd,	flags, lock_flags )
 static void
ccmn_clr_drv_state( CCMN_SPECIFIC *pd, u_int flags, u_int lock_flags )
{ 
    if (!(lock_flags & PD_LOCKED)) {
	CCMN_LOCK(pd);
    }
    (pd)->pd_drv_state &= ~(flags);
    if (!(lock_flags & PD_LOCK_ON_EXIT)) {
	CCMN_UNLOCK(pd);
    } 
    wakeup(&(pd)->pd_drv_state);
}

/************************************************************************
 * :tag::	Macros to clear	ccb, release ccb queue
 ************************************************************************/
/*
 * Macro to release CCB	(replacement for ccmn_rel_ccb3())
 */
#define	CCMN_REL_CCB3(ccb)		\
     xpt_ccb_free((CCB_HEADER *)(ccb));

/*
 * Clear the fields in the CCB which will be filled in on a retry
 * of the CCB.
 */
#define	CLEAR_CCB3(ccb,	cam_status_mask)			\
{								\
    CB_SCSIIO *c3cb_x;						\
    (ccb)->cam_ch.cam_status &=	(cam_status_mask);		\
    CAM_GET_CB_PTR(&(ccb)->cam_ch, c3cb_x, CB_SCSIIO);		\
    c3cb_x->cam_scsi_status	= 0;				\
    c3cb_x->cam_resid		= 0;				\
    c3cb_x->cam_sense_resid	= 0;				\
    ((PDRV3_WS *)c3cb_x->cam_pdrv_ptr)->pws_flags &= ~PWS_CALLBACK;  \
}

/*
 * Issue the Release SIM Queue CCB.
 */
#define	RELEASE_QUEUE3(trans) {					\
	CCMN_REL_CCB3(ccmn_rsq_ccb_bld3((trans), 0L));		\
}

/*
 * Issue the Release SIM Queue CCB if the CAM status field of the
 * ccb indicates that the queue	is frozen
 */
#define	CHK_RELEASE_QUEUE3(trans, ccb)				\
	if( (ccb)->cam_ch.cam_status & CAM_SIM_QFRZN )	{	\
		RELEASE_QUEUE3((trans));			\
		(ccb)->cam_ch.cam_status &= ~CAM_SIM_QFRZN;	\
	}							\

/************************************************************************
 * :tag::	CCMN_IO_CCB_BLD3 macro
 ************************************************************************/

/*
 * CCMN_IO_CCB_BLD3
 *
 * Arguments:
 *	ccb_p	  - Pointer to ccb structure
 *	c3cb_p	  - Pointer to ccb body	structure    *)
 *	trans_p	  - Pointer to translation structure
 *	data_p	  - Pointer to data buffer
 *	data_l	  - Length of data
 *	sense_l	  - Length of sense data
 *	cam_fl	  - CAM	flags
 *	comp_fun  - Pointer to completion function
 *	tag_act	  - tag	action
 *	timeout	  - timeout value
 *	bp_p	  - Pointer to struct buf
 *	path_p	  - PATH structure pointer
 *
 * Comments:
 *   *)	Most of	the time we need a pointer to ccb body as well
 *	as pointer to ccb. In few cases	we don't, it is	cheaper
 *	to allocate a throwaway	than to	branch around it in the
 *	ccmn_io_ccb_bld3() function.	
 */

#define	CCMN_IO_CCB_BLD3(ccb_p,	c3cb_p,	trans_p,			\
	data_p,	data_l,	sense_l, cam_fl, comp_fun,			\
	tag_act, timeout, bp_p,	path_p)					\
{									\
    /*									\
     * Get pointer to partially	filled ccb and to ccb body		\
     */									\
    ccb_p = ccmn_io_ccb_bld3(trans_p, &(c3cb_p), path_p);		\
    /*									\
     * Fill in the SCSI	I/O specific fields.				\
     */									\
    ccb_p->cam_ch.cam_flags = (cam_fl);					\
    c3cb_p->cam_cbfcnp	    = (comp_fun);				\
    c3cb_p->cam_data_ptr    = (data_p);					\
    c3cb_p->cam_dxfer_len   = (data_l);					\
    c3cb_p->cam_sense_len   = (u_char)(sense_l);			\
    c3cb_p->cam_req_map	    = (u_char *)(bp_p);				\
    c3cb_p->cam_tag_action  = (tag_act);				\
    c3cb_p->cam_timeout	    = (timeout);				\
    ((PDRV3_WS *)(c3cb_p)->cam_pdrv_ptr)->pws_dev_path = path_p;	\
    ((PDRV3_WS *)(c3cb_p)->cam_pdrv_ptr)->pws_pd_rad = path_p->pa_rad;	\
}

/* 
 * Allocate SIM 1 CCB knowing just the rad locality, NO path data!
 */
#define	CCMN_IO_CCB_RADID_BLD3(ccb_p, c3cb_p, pd,			\
	data_p,	data_l,	sense_l, cam_fl, comp_fun,			\
	tag_act, timeout, bp_p,	radid)					\
{									\
    /*									\
     * Get pointer to partially	filled ccb and to ccb body		\
     */									\
    ccb_p = ccmn_io_ccb_radid_bld3(pd, &(c3cb_p), radid);		\
    /*									\
     * Fill in the SCSI	I/O specific fields.				\
     */									\
    ccb_p->cam_ch.cam_flags = (cam_fl);					\
    c3cb_p->cam_cbfcnp	    = (comp_fun);				\
    c3cb_p->cam_data_ptr    = (data_p);					\
    c3cb_p->cam_dxfer_len   = (data_l);					\
    c3cb_p->cam_sense_len   = (u_char)(sense_l);			\
    c3cb_p->cam_req_map	    = (u_char *)(bp_p);				\
    c3cb_p->cam_tag_action  = (tag_act);				\
    c3cb_p->cam_timeout	    = (timeout);				\
}

/************************************************************************
 * :tag:: Common Barrier structs and definitions 
 ************************************************************************/

/* The common request queue - they all go here while active */
typedef struct iob_request_queue{
    struct iob_request *iob_flink;           /* Forward linkage */
    struct iob_request *iob_blink;           /* Backward linkage */
    XPT_LOCK_DATA iob_req_que_lck;           /* lock for queue insert/removal */
    u_long  iob_request_cnt;                 /* count of requests on queue */
}IOB_REQUEST_QUEUE;


/* 
 * Insertions and removal macros for enqueuing the IOB_REQUEST onto
 * the iob_request_queue.
 */
#define IOB_INSERT_REQ(iob_request_ptr)                                \
{                                                                      \
    XPT_LOCK(&(iob_request_queue.iob_req_que_lck));                    \
    enqueue_tail(&iob_request_queue.iob_flink,                         \
                (queue_entry_t)&((iob_request_ptr)->iob_flink));       \
    iob_request_queue.iob_request_cnt++;                               \
    XPT_UNLOCK(&(iob_request_queue.iob_req_que_lck));                  \
}

#define IOB_REMOVE_REQ(iob_request_ptr)                                \
{                                                                      \
    XPT_LOCK(&(iob_request_queue.iob_req_que_lck));                    \
    remque((struct queue_entry *)&((iob_request_ptr)->iob_flink));     \
    iob_request_queue.iob_request_cnt--;                               \
    XPT_UNLOCK(&(iob_request_queue.iob_req_que_lck));                  \
}

/* 
 * Structure definition for ccmn_build_prout_ccb parameters.
 * These parameters are placed into parameter list having
 * a type of ALL_PROUT_PARAMETERS
 */
typedef struct ccmn_prout_params {
    u_long           reservation_key;
    u_long           service_act_key;
    u_int            element_addr;
    u_char           aptpl   :1,
                     :7;                    /* Reserved              */
    u_char           :8;                    /* Reserved              */
    u_char           :8;                    /* Obsolete   was extent */
    u_char           :8;                    /* Obsolete   was extent */
} CCMN_PROUT_PARAMS;

 


typedef struct iob_bus_mask {
    u_long  bus_mask[MAX_CAM_SCSI_BUSSES/(sizeof(ulong) * 8)];
} IOB_BUS_MASK;

typedef struct  iob_target_mask {
    u_long  target_mask[256/sizeof(u_long)];
} IOB_TARGET_MASK;


typedef struct iob_target_reset_mask {
    IOB_TARGET_MASK iob_target_mask[MAX_CAM_SCSI_BUSSES];
} IOB_TARGET_RESET_MASK;


/* 
 * The lock definition that synchronizes access to the reset
 * masks (both bus and target
 */
typedef struct iob_reset_sync {
    XPT_LOCK_DATA iob_reset_mask_lck;    /* lock for reset mask access */
}IOB_RESET_SYNC;


/* MARCOS for dealing with IOB_TARGET_RESET_MASK */
#define CLEAR_IOB_TARGET_RESET_MASK( iob_target_reset_ptr )               \
{                                                                         \
    bzero((char *)(iob_target_reset_ptr),                                 \
                sizeof(IOB_TARGET_RESET_MASK));                           \
}


#define SET_IOB_TARGET_RESET_MASK(iob_target_reset_ptr,bus_num,target_num)\
{                                                                         \
    u_long targetidx;                                                     \
    u_long targetbit;                                                     \
    XPT_LOCK(&iob_reset_sync.iob_reset_mask_lck);                         \
    if(((bus_num) < MAX_CAM_SCSI_BUSSES) && ((target_num) < 256)){        \
       targetidx = (target_num)/sizeof(u_long);                           \
       targetbit = ((target_num)%sizeof(u_long));                         \
       (iob_target_reset_ptr)->iob_target_mask[(bus_num)].                \
            target_mask[targetidx] |= (1L << targetbit);                  \
    }                                                                     \
    XPT_UNLOCK(&iob_reset_sync.iob_reset_mask_lck);                       \
}

#define CHECK_IOB_TARGET_RESET(iob_target_reset_ptr,bus_num,target_num,   \
                        indicator)                                        \
{                                                                         \
    u_long targetidx;                                                     \
    u_long targetbit;                                                     \
    XPT_LOCK(&iob_reset_sync.iob_reset_mask_lck);                         \
    if(((bus_num) < MAX_CAM_SCSI_BUSSES) && ((target_num) < 256)){        \
        targetidx = (target_num)/sizeof(u_long);                          \
        targetbit = ((target_num)%sizeof(u_long));                        \
        (indicator) = (iob_target_reset_ptr)->                            \
            iob_target_mask[(bus_num)].                                   \
            target_mask[targetidx] & (1L << targetbit);                   \
    }                                                                     \
    XPT_UNLOCK(&iob_reset_sync.iob_reset_mask_lck);                       \
}

/*
 * MARCOS for dealing with IOB_BUS_MASK.  Note all take a pointer
 * to the IOB_BUS_MASK struct.
 */

/* Clear the bus mask struct */
#define CLEAR_IOB_BUS_MASK(iob_bus_mask_ptr)                              \
{                                                                         \
    bzero((char *)(iob_bus_mask_ptr), sizeof(IOB_BUS_MASK));              \
}


/* Set a bus indicator args are IOB_BUS_MASK * and bus number */
#define SET_IOB_BUS_NUM(iob_bus_mask_ptr, bus_num_in)                     \
{                                                                         \
    u_long slotidx;                                                       \
    u_long bus_bit;                                                       \
    XPT_LOCK(&iob_reset_sync.iob_reset_mask_lck);                         \
    if( (bus_num_in) <  MAX_CAM_SCSI_BUSSES){                             \
        slotidx = (bus_num_in)/(sizeof(u_long) * 8);                      \
        bus_bit = (bus_num_in)%(sizeof(u_long) * 8);                      \
        (iob_bus_mask_ptr)->bus_mask[slotidx] |= (1L << bus_bit);         \
    }                                                                     \
    XPT_UNLOCK(&iob_reset_sync.iob_reset_mask_lck);                       \
}

/*
 * Check if we need to do something on the bus args are IOB_BUS_MASK *,
 * bus_number and u_long indicator (positive yes 0 no)
 */
#define CHECK_IOB_BUS(iob_bus_mask_ptr, bus_num_in, indicator)            \
{                                                                         \
    u_long slotidx;                                                       \
    u_long bus_bit;                                                       \
    XPT_LOCK(&iob_reset_sync.iob_reset_mask_lck);                         \
    if( (bus_num_in) <  MAX_CAM_SCSI_BUSSES){                             \
        slotidx = (bus_num_in)/(sizeof(u_long) * 8);                      \
        bus_bit = (bus_num_in)%(sizeof(u_long) * 8);                      \
        (indicator) = (iob_bus_mask_ptr)->bus_mask[slotidx] &             \
                         (1L << bus_bit);                                 \
    }                                                                     \
    else {                                                                \
        (indicator) = 0;                                                  \
    }                                                                     \
    XPT_UNLOCK(&iob_reset_sync.iob_reset_mask_lck);                       \
}


/************************************************************************
 * :tag::	Delayed	calls -	CALL_DESCR and auxiliary structures
 ************************************************************************/

/*
 * Structure is	created	by ccmn_sched_call() function and used by
 * ccmn_exe_call() and ccmn_exe_call_thread() to service
 * delayed function calls.
 */  

struct call_descr;			/* Forward declaration		*/
#define	CCMN_CALL_DESCR_MAX	64	/* Max free descriptors	/ CPU	*/
#define	CCMN_CALL_DESCR_ISR	32	/* Reserved for calls from ISR	*/

typedef	struct call_link {
    struct call_descr  *call_flink;	/* Forward link			*/
    struct call_descr  *call_blink;	/* Backward link		*/
} CALL_LINK;

typedef	struct call_list {
    CALL_LINK		call_act;	/* Queue header	- active calls	*/
    CALL_LINK		call_held;	/* Queue header	- held calls	*/
    CALL_LINK		call_free;	/* Queue header	- free descr	*/
    CAM_U32		call_act_cnt;	/* Count of queued act.	descr	*/
    CAM_U32		call_free_cnt;	/* Count of queued free	descr	*/
    XPT_LOCK_DATA	call_lck;	/* SMP lock structure		*/
    CAM_U32		call_init;	/* Initiation indicator		*/
} CALL_LIST;

typedef	struct call_descr {
    CALL_LINK		call_hdr;
    void	       (*call_func)();	/* Function to call		*/
    caddr_t		call_arg;	/* Function call argument	*/
} CALL_DESCR;

/************************************************************************
 * :tag::	CCMN_REHM - [un]register EHM thread definitions
 ************************************************************************/
/*
 * Defines for CCMN_REHM_Q opcode
 */
#define PATH_HWC_OP          0x00000001    /* This is an EHM op defined by
                                              hwc_opcode HWC_REGISTER etc. */
#define PATH_DELETE_OP       0x00000002    /* Delete this path struct not
                                              an EHM op */
#define PATH_CHANGE_OP       0x00000004    /* Change name request. */ 
#define RELEASEBUF_OP        0x00000008    /* Release buffer request. */ 

/************************************************************************
 * :tag::	[Un]Register Async Callbacks thread
 ************************************************************************/

struct ccmn_sasy {
	U32		events;		/* Events to be registered */
	TRANSLATION	trans;		/* Copy of trans struct */
};

/************************************************************************
 * :tag::hwc path/device registration request structure	
 ************************************************************************/

#ifdef _KERNEL
typedef struct ccmn_path_reg_req {
    struct ccmn_path_reg_req *reg_flink; /* queue linkage */
    struct ccmn_path_reg_req *reg_blink;
    CCMN_SPECIFIC            *reg_pd;    /* pd of device */
    PATH                     *reg_path;  /* path */
    HW_REG_REQ                reg_rqst;  /* registration request */
    void                     *reg_wait_chan; /* wait channel */
} ccmn_path_reg_req_t;
#endif

/************************************************************************
 * :tag::	request queue header	
 ************************************************************************/

#ifdef _KERNEL
typedef struct ccmn_path_reg_req_q_hdr {
    ccmn_path_reg_req_t *reg_qnonh_flink;/* non-hierarchy request queue flink */
    ccmn_path_reg_req_t *reg_qnonh_blink;/* non-hierarchy request queue blink */
    ccmn_path_reg_req_t *reg_qh_flink;   /* hierarchy request queue flink */
    ccmn_path_reg_req_t *reg_qh_blink;   /* hierarchy request queue blink */
    XPT_LOCK_DATA        reg_q_lck;      /* synchronization lock */
    int                  req_qnonh_cnt;  /* non-hierarchy request queue length */
    int                  req_qh_cnt;     /* hierarchy request queue length */
    volatile thread_t    reg_thrd;       /* initing thread ID */
    int                  req_thrd_slpng; /* Is thread currently sleeping? */
} ccmn_path_reg_req_q_hdr_t;

/*
 * Request macros for enqueueing and dequeueing
 */

#define ENQ_NOHIER_REQ( REQ )                                              \
    MACRO_BEGIN                                                            \
    XPT_LOCK( &ccmn_reg_q_hdr.reg_q_lck );                                 \
    enqueue_tail( &ccmn_reg_q_hdr.reg_qnonh_flink, (queue_entry_t) (REQ) );\
    ccmn_reg_q_hdr.req_qnonh_cnt++;                                        \
    if (ccmn_reg_q_hdr.req_thrd_slpng ) {                                  \
        wakeup( &ccmn_reg_q_hdr );                                         \
    }                                                                      \
    XPT_UNLOCK( &ccmn_reg_q_hdr.reg_q_lck );                               \
    MACRO_END


#define ENQ_HIER_REQ( REQ )                                               \
    MACRO_BEGIN                                                           \
    XPT_LOCK( &ccmn_reg_q_hdr.reg_q_lck );                                \
    enqueue_tail( &ccmn_reg_q_hdr.reg_qh_flink, (queue_entry_t) (REQ) );  \
    ccmn_reg_q_hdr.req_qh_cnt++;                                          \
    if (ccmn_reg_q_hdr.req_thrd_slpng ) {                                 \
        wakeup( &ccmn_reg_q_hdr );                                        \
    }                                                                     \
    XPT_UNLOCK( &ccmn_reg_q_hdr.reg_q_lck );                              \
    MACRO_END


#define ENQ_REG_REQ( REQ )                                                \
    MACRO_BEGIN                                                           \
    if(!((REQ)->reg_rqst.flags & HW_REG_NO_HIER)) {                       \
        ENQ_HIER_REQ( REQ );                                              \
    }                                                                     \
    else {                                                                \
        ENQ_NOHIER_REQ( REQ );                                            \
    }                                                                     \
    MACRO_END


#define DQ_NOHIER_REQ( REQ )                                              \
    MACRO_BEGIN                                                           \
    XPT_LOCK( &ccmn_reg_q_hdr.reg_q_lck );                                \
    remque( (queue_entry_t) (REQ) );                                      \
    ccmn_reg_q_hdr.req_qnonh_cnt--;                                       \
    MACRO_END


#define DQ_HIER_REQ( REQ )                                                \
    MACRO_BEGIN                                                           \
    XPT_LOCK( &ccmn_reg_q_hdr.reg_q_lck );                                \
    remque( (queue_entry_t) (REQ) );                                      \
    ccmn_reg_q_hdr.req_qh_cnt--;                                          \
    MACRO_END

/* macro to dequeue request, enter unlocked leave LOCKED!! */
#define DQ_REG_REQ( REQ )                                                 \
    MACRO_BEGIN                                                           \
    if(!((REQ)->reg_rqst.flags & HW_REG_NO_HIER)) {                       \
        DQ_HIER_REQ( REQ );                                               \
    }                                                                     \
    else {                                                                \
        DQ_NOHIER_REQ( REQ );                                             \
    }                                                                     \
    MACRO_END

#endif /* _KERNEL */

/************************************************************************
 * :tag::	Prototypes of the pdrv3_common.c routines
 ************************************************************************/
void 	ccmn_credit_mgr(
	CCMN_SPECIFIC *pd, 		/* Pointer to CCMN_SPECIFIC     */
        PD_RAD_DATA   *pd_rad, 		/* Pointer to PD_RAD_DATA       */
	CAM_U32        credit_flag	/* Flag indicating operation    */
	);

CAM_U32	ccmn_setup_ccmn_specific (
	TRANSLATION *,			/* device translation struct	*/
	U32				/* Size of Drv specific rad data*/
	);

int ccmn_specific_release( TRANSLATION *trans );

CAM_U32	ccmn_setup_ccmn_rads (
	CCMN_SPECIFIC *,		/* Pointer to CCMN_SPECIFIC 	*/
	U32				/* Size of Drv specific rad data*/
	);

void ccmn_init_pd_rad_data(
        PD_RAD_DATA 	*pd_rad, 	/* Pointer to PD_RAD_DATA struct */
	CCMN_SPECIFIC	*pd,	    	/* Pointer to CCMN_SPECIFIC struct */
	int		rad_id);

void	ccmn_delete_ccmn_rads (
	CCMN_SPECIFIC *			/* Pointer to CCMN_SPECIFIC 	*/
	);

void *	ccmn_ccb_alloc (
	TRANSLATION *trans);	    /* device translation struct	*/

void *	ccmn_get_ccb3 (
	TRANSLATION *trans,	    /* device translation struct	*/
	CAM_U8	func_code,	    /* XPT function code		*/
	CAM_U32	cam_flags);	    /* cam_flags field of the CCB header */

void *	ccmn_io_ccb_bld3 (
	TRANSLATION *trans,	    /* device translation struct	*/
	CB_SCSIIO   **c3cb_pp,	    /* caller's	pointer	to the ccb body	*/
	PATH        *path_p);  	    /* Path pointer		*/

void *	ccmn_io_ccb_radid_bld3 (
	CCMN_SPECIFIC *pd,	    /* device translation struct	*/
	CB_SCSIIO     **c3cb_pp,    /* caller's	pointer	to the ccb body	*/
	CAM_U32       radid);  	    /* rad_id		*/

void *	ccmn_abort_ccb_bld3 (
	TRANSLATION *trans,	    /* device translation struct	*/
	CAM_U32	    cam_flags,	    /* cam_flags field			*/
	CCB_HEADER  *abort_ccb);    /* ccb to be aborted		*/

void *	ccmn_bdr_ccb_bld3 (
	TRANSLATION *trans,	    /* device translation struct	*/
	CAM_U32	cam_flags);	    /* cam_flags field			*/

void *	ccmn_br_ccb_bld3 (
	TRANSLATION *trans,	    /* device translation struct	*/
	CAM_U32	cam_flags);	    /* cam_flags field			*/

void *	ccmn_gdev_ccb_bld3 (
	TRANSLATION *trans,	    /* device translation struct	*/
	CAM_U32	cam_flags,	    /* cam_flags field			*/
	CAM_U8	*inq_addr);	    /* ptr to inq data buffer		*/

void *	ccmn_sdev_ccb_bld3 (
	TRANSLATION *trans,	    /* device translation struct	*/
	CAM_U32	cam_flags,	    /* cam_flags field			*/
	CAM_U32	dev_type);	    /* ALL_DTYPE_DIRECT	etc.		*/

void *	ccmn_rsq_ccb_bld3 (
	TRANSLATION *trans,	    /* device translation struct	*/
	CAM_U32	cam_flags);	    /* cam_flags field			*/

void *	ccmn_pinq_ccb_bld3 (
	TRANSLATION *trans,	    /* device translation struct	*/
	CAM_U32	cam_flags);	    /* cam_flags field			*/

void *	ccmn_sasy_ccb_bld3 (
	TRANSLATION *trans,	    /* device translation struct	*/
	CAM_U32	cam_flags,	    /* cam_flags field			*/
	CAM_U32	async_flags,	    /* asynchronous flags		*/
	void (*callb_func)(u_int, u_int, u_long, u_long, char *, u_int, void *),   /* async callback func		*/
	CAM_U8	*bufptr,	    /* driver buffer pointer		*/
	CAM_U32	buflen,		    /* driver buffer length		*/
	void	*driver_spec);	    /* ptr to driver specific struct	*/

CAM_U32	ccmn_send_ccb3 (
	TRANSLATION   *trans,	    /* device translation struct	*/
	CCB_HEADER    *ccb,	    /* ccb pointer			*/
	CAM_U32	      lock_flags);  /* entry / exit lock state		*/

CAM_U32	ccmn_send_ccb_wait3(
	TRANSLATION   *trans,	    /* device translation struct	*/
	CCB_HEADER    *ccb,	    /* ccb pointer			*/
	int sleep_pri);		    /* priority	to sleep at		*/

void	ccmn_rem_ccb3 (
	TRANSLATION   *trans,	    /* device translation struct	*/
	DCB_SCSIIO    *ccb,	    /* ccb pointer			*/
	CAM_U32	      lock_flags);  /* entry / exit lock state		*/

void	ccmn_rem_ccb3_nosend (
	TRANSLATION   *trans,	    /* device translation struct	*/
	DCB_SCSIIO    *ccb,	    /* ccb pointer			*/
	CAM_U32	      lock_flags);  /* entry / exit lock state		*/

CAM_U32	ccmn_abort_que3	(
	TRANSLATION  *trans,	    /* device translation struct	*/
	int	     abort_pending,
	CAM_U32	     lock_flags);   /* entry / exit lock state		*/

void	ccmn_complete3 (
	DCB_SCSIIO   *ccb	    /* ccb pointer			*/
	);

void *	ccmn_start_unit3 (
	TRANSLATION *trans,	    /* device translation struct	*/
	CAM_U32	sense_len,	    /* Size of REQUEST SENSE buffer	*/
	CAM_U32	cam_flags,	    /* cam_flags field			*/
	void	(*comp_func)(),	    /* completion function to call	*/
	CAM_U8	tag_action,	    /* action for tagged request	*/
	CAM_U32	timeout_val,	    /* command timeout			*/
	PATH	*path		    /* Current path pointer		*/	
	);

void *	ccmn_tur3 (
	TRANSLATION *trans,	    /* device translation struct	*/
	CAM_U32	sense_len,	    /* Size of REQUEST SENSE buffer	*/
	CAM_U32	cam_flags,	    /* cam_flags field			*/
	void	(*comp_func)(),	    /* completion function to call	*/
	CAM_U8	tag_action,	    /* action for tagged request	*/
	CAM_U32	timeout_val,	    /* command timeout			*/
	PATH	*path		    /* Current path pointer		*/	
	);

void *	ccmn_mode_select3(
	TRANSLATION *trans,	    /* device translation struct	*/
	CAM_U32	sense_len,	    /* Size of REQUEST SENSE buffer	*/
	CAM_U32	cam_flags,	    /* cam_flags field		*/
	void   (*comp_func)(),	    /* completion function to call	*/
	CAM_U8	tag_action,	    /* action for tagged request	*/
	CAM_U32	timeout_val,	    /* command timeout		*/
	CAM_U32	ms_index,	    /* index into Mode Select table	*/
	PATH	*path		    /* Current path pointer		*/	
	);

CAM_U32	ccmn_SysSpecialCmd3 (
	TRANSLATION *trans,	    /* Connection Information		*/
	CAM_U8	cmd,		    /* SCSI command code		*/
	caddr_t	data,		    /* data buffer address		*/
	CAM_U32	flags,		    /* file open flags			*/
	DCB_SCSIIO *ccb,	    /* ccb pointer			*/
	CAM_U32	sflags		    /* special I/O flags		*/
	);

CAM_U32	ccmn_DoSpecialCmd3 (
	TRANSLATION *trans,	    /* Connection Information		*/
	CAM_U32	cmd,		    /* I/O control command		*/
	caddr_t	data,		    /* data buffer address		*/
	CAM_U32	flags,		    /* file open flags			*/
	DCB_SCSIIO  *ccb,	    /* ccb pointer			*/
	CAM_U32	sflags		    /* special I/O flags		*/
	);

void *	ccmn_rpt_chgbl_devid3(
	TRANSLATION	*trans,	    /* Connection Information		*/
	CAM_U8	*ident_buf,	    /* buffer for identifier		*/
	CAM_U32	ident_buflen,	    /* lenght of identifier buffer	*/
	CAM_U32	sense_len,	    /* Size of REQUEST SENSE buffer	*/
	CAM_U32	cam_flags,	    /* cam_flags field			*/
	void	(*comp_func)(),	    /* completion function to call	*/
	CAM_U8	tag_action,	    /* action for tagged request	*/
	CAM_U32	tmo_val,	    /* command timeout			*/
	PATH 	*path		    /* Current path pointer 		*/
	);

void	ccmn_release_dev_desc3 (
	TRANSLATION	*trans,	    /* device translation struct	*/
	CAM_U32		lock_flags  /* entry / exit lock state		*/
	);

struct controller *
	ccmn_find_ctrl3	(
	CAM_U32	port_id		    /* registered SIM/HA port number	*/
	);

struct device *
	ccmn_find_device3 (
	struct controller *ctrl,    /* adapter descriptor struct	*/
	TRANSLATION	  *trans    /* device translation struct	*/
	);

CAM_SCSI_BUS *
ccmn_get_cam_scsi_bus (
	CAM_U32	port_id		    /* registered SIM/HA port number	*/
	);

CAM_U32	ccmn_get_sim_type (
	CAM_U32	port_id		    /* SCSI port number			*/
	);

void	ccmn_get_devinfo_scsidata3 (
	TRANSLATION	*trans,	    /* device translation struct	*/
	device_info_t	*devip	    /* ioctl argument structure		*/
	);

CAM_U32	ccmn_scan_bus (
	TRANSLATION *trans	    /* device translation struct	*/
	);

CAM_U32	ccmn_scan_lun3 (
	TRANSLATION *trans	    /* device translation struct	*/
	);

CAM_U32	ccmn_scan_lun3vu (
	TRANSLATION *trans,	    /* device translation struct	*/
	U32 *constate               /* connection state- pqual inq data */
	);

CAM_U32 ccmn_scan_paths(
	TRANSLATION *trans	    /* device translation struct	 */
	);

int
ccmn_trans_srm_suffix(
	CAM_U32 *logical_id,	    /* CAM Logical ID			*/
	struct console_device *cons_dev /* console info struct with	*
					 * srm_suffix containing the	*
					 * @wwid? of the boot device.	*/
	);

dev_t	ccmn_io_barrier	(
	dev_t	   *dev_list,	    /* pointer to list of devices	*/
	int	   device_count	    /* Number of elements in the list	*/
	);

CAM_U32	ccmn_get_eei_status3 (
	TRANSLATION	*trans,	    /* device translation struct	*/
	DEV_EEI_STATUS	*eei,
	CAM_EEI_STATUS	*cam_status,
	CAM_U32		lock_flags  /* entry / exit lock state		*/
	);

void	ccmn_record_eei_status3	(
	TRANSLATION	*trans,	    /* device translation struct	*/
	DCB_SCSIIO	*ccb,	    /* ccb pointer			*/
	CAM_EEI_STATUS	*eei,
	CAM_U32		status,
	CAM_U32		lock_flags  /* entry / exit lock state		*/
	);

void	ccmn_errlog3(
	TRANSLATION	*trans,
	CAM_S8		*func_str,  /* Pointer to func name string	*/
	char		*opt_str,   /* Pointer to optional string	*/
	CAM_U32		flags,	    /* Hard, soft, informational	*/
	CCB_HEADER	*ccb,	    /* ccb pointer			*/
	CAM_U8		*unused
	);

CAM_U32	ccmn_check_sense_residue(
	DCB_SCSIIO *ccb		    /* IO ccb pointer			*/
	);


CAM_U32	ccmn_path_setup3(CCMN_SPECIFIC *, PATH_INFO_HDR	*, 
						TRANSLATION *, u_long );

CAM_U32
ccmn_alloc_paths3(CCMN_SPECIFIC	*, PATH_INFO_HDR *,
				TRANSLATION *, u_long );

PATH *
ccmn_check_pathexist3(CCMN_SPECIFIC *, PATH_INFO_HDR *,	CONNECTION_ID *, 
						u_long );

CAM_U32
ccmn_resolve_paths3(CCMN_SPECIFIC *, PATH_INFO_HDR *, u_long );

CAM_U32
ccmn_find_fixed_path3( CCMN_SPECIFIC *,	 CONNECTION_ID *,
	TRANSLATION **,	PATH **, u_long	);

CAM_U32
ccmn_check_io_path3(TRANSLATION	*, DCB_SCSIIO *, PDRV3_WS *, CAM_U32 , CAM_U32 );

CAM_U32
ccmn_path_ping3( CCMN_SPECIFIC *, PATH_QUE *, u_long, u_long );

CAM_U32
ccmn_del_stale_paths3(CCMN_SPECIFIC *, PATH_INFO_HDR *,TRANSLATION *, u_long);

void
ccmn_start_threads3( void );

void
ccmn_monitor_paths_thread3( void );

void
ccmn_stop_path_monitor3( TRANSLATION *, CCMN_SPECIFIC *, u_long);

void
ccmn_resume_path_monitoring( TRANSLATION *, CCMN_SPECIFIC *, u_long);

cfg_subsys_attr_t *ccmn_get_ehm_path_table3( u_int );

void
ccmn_get_unique_name(TRANSLATION *trans, CCMN_SPECIFIC *pd );

void
ccmn_sched_call	(
    void	(*func)(),
    caddr_t	arg,
    int	tmo	);

CAM_U32
ccmn_abort_call(
    void	(*func)(),
    caddr_t	arg );

void
ccmn_ehm_dereg_path(
	PATH *,
	CCMN_SPECIFIC *,
	u_long );

int
ccmn_delete_paths( CCMN_SPECIFIC *, 
		   u_long );
		   
int
ccmn_path_event( PATH *, 
		CCMN_SPECIFIC *, 
		u_long ,
		u_long  );

void
ccmn_active_path_resolve(PD_RAD_DATA   *pd_rad,
			 PATH_INFO_HDR *p_hdr,
			 u_long);

int
ccmn_send_pending_ccb3(CCMN_SPECIFIC *pd,
		       PD_RAD_DATA   *pd_rad,
		       CAM_U32        lock_flags);

void
ccmn_restart_tagged_queue(CCMN_SPECIFIC *);

void
ccmn_get_path( CCMN_SPECIFIC *, PATH_LIST *, u_long);

void
ccmn_get_path_list( CCMN_SPECIFIC *, PATH_LIST *, u_long );

void
ccmn_cleanup_paths3( TRANSLATION *, CAM_U64);

void
ccmn_all_hier_reg_cmplt( void );

int
ccmn_post_event( TRANSLATION *, CCMN_SPECIFIC *, void *, u_long, u_long );

void
ccmn_destroy_invalid_paths(CCMN_SPECIFIC *ccmn_spec,
			   PD_RAD_DATA   *pd_rad, 
			   PATH_QUE      *qhd);

void
ccmn_del_que_paths( CCMN_SPECIFIC *ccmn_spec, 
		    PD_RAD_DATA   *pd_rad,
		    PATH_QUE      *qhd);

PATH *
ccmn_match_path_connid3(PATH_QUE      *qhd, 
		        CONNECTION_ID *conn_id);

void
ccmn_clr_reset_mask(void);

u_int
ccmn_remove_dup_key( u_int,
                     u_long *);

void *
ccmn_build_prout_ccb( TRANSLATION *,
                     PATH *,
                     void (*comp_func)(),
                     CCMN_PROUT_PARAMS *,
                     u_char,
                     u_char,
                     u_char,
                     int,
                     u_int,
                     u_int,
                     int,
                     u_char);

void *
ccmn_build_prin_ccb( TRANSLATION *,
                     PATH *,
                     void (*comp_func)(),
                     u_char,
                     int,
                     u_int,
                     u_int,
                     int,
                     u_char);




/************************************************************************
 * :tag::	External variable declarations
 ************************************************************************/
#ifdef	_KERNEL
extern struct timeval time;
#endif

extern long lbolt;

extern struct lockinfo *cam_pd_device_li;
extern struct lockinfo *cam_pd_device3_li;
extern struct lockinfo *cam_pd_rad_device3_li;
extern struct lockinfo *cam_pd_unit_li;
extern struct lockinfo *cam_pd_unit_table_li;
extern struct lockinfo *cam_ccmn_data_pool_li;

extern U32    cam_harderr_limit;
extern U32    cam_softerr_limit;

extern int ccmn_reg_hier_pause;	/* for debug, pause between registrations */

/*
 * error type strings
 */
extern char HardError[];
extern char SoftError[];
extern char InforError[];
extern char SoftwareError[];
extern char Unknown[];
extern char ActiveCCB[];
extern char Active_List[];
extern char Active_List_Cont[];
extern char Pend_List[];
extern char Pend_List_Cont[];
extern char NoPdrv_struct[];

#ifdef __cplusplus
}
#endif

#endif /* _PDRV3_	*/


