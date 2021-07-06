/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: table.h,v $
 * Revision 4.2.63.3  2004/10/29  16:19:33  Douglas_Frank
 * 	Added clu_table.
 *
 * Revision 4.2.63.2  2004/08/19  08:19:48  Akshay_Nesari
 * 	QAR 77928 : TBL_TCPCONN for IPv6 connections
 *
 * Revision 4.2.63.1  2003/10/09  21:26:48  Jeffrey_Cilley
 * 	Add new ubc vm stats and performance counters.
 *
 * Revision 4.2.55.3  2001/03/28  18:07:21  Anton_Verhulst
 *  	Add cpu type to struct tbl_processor.
 *
 * Revision 4.2.55.2  2000/10/10  15:14:37  Anton_Verhulst
 * 	Add num_cache_bytes to struct tbl_processor.
 *
 * Revision 4.2.55.1  2000/07/27  14:51:34  Chang_Song
 * 	tbl_ncstats updated to match updated ncstats
 *
 * Revision 4.2.51.9  2000/02/22  20:48:50  Shashi_Mangalat
 * 	UNIX98 support and changes for V50 IPC_STAT.
 *
 * Revision 4.2.51.8  2000/01/21  20:51:45  Brian_Haley
 * 	Added TBL_RAD_RNH support.
 *
 * Revision 4.2.51.7  2000/01/20  21:38:51  Anton_Verhulst
 * 	Add mhz to struct tbl_processor.
 *
 * Revision 4.2.51.6  1999/12/15  20:09:35  Shashi_Mangalat
 * 	Add page migration statistic.
 *
 * Revision 4.2.51.5  1999/11/03  22:06:33  Eric_Werme
 * 	Add NFS support.
 * 	[1999/10/27  18:40:19  Eric_Werme]
 *
 * Revision 4.2.51.4  1999/09/30  15:05:18  Stephen_Corbin
 * 	Added vm_perf statistics reporting.
 *
 * Revision 4.2.51.3  1999/09/23  20:04:47  Stephen_Corbin
 * 	Added per-RAD type flag.  Added more info to tbl_threadstates.
 *
 * Revision 4.2.51.2  1999/06/16  19:59:18  Anton_Verhulst
 * 	Created.
 * 	[1999/06/16  19:29:20  Anton_Verhulst]
 *
 * Revision 4.2.26.23  1999/03/17  22:33:30  Dave_King
 * 	Add TBL_VNODESTATS support.
 * 	[1999/03/15  20:40:05  Dave_King]
 * 
 * Revision 4.2.26.22  1999/02/21  16:13:01  Shashi_Mangalat
 * 	Extend tbl_vmstat to include task swap info. and replace unused object
 * 	cache hit with UBC cache hit information.
 * 	[1999/02/21  16:12:03  Shashi_Mangalat]
 * 
 * Revision 4.2.26.21  1999/02/19  22:03:05  Nitin_Karkhanis
 * 	Add new table ID, TBL_TASKINFO and its related structure.
 * 	[1999/02/18  22:09:20  Nitin_Karkhanis]
 * 
 * Revision 4.2.26.20  1998/11/24  16:20:49  Larry_Scott
 * 	Add TBL_FDSTAT option.
 * 	[1998/11/21  19:28:54  Larry_Scott]
 * 
 * Revision 4.2.26.19  1998/10/30  21:34:04  Mark_Bokhan
 * 	Update di_time comment in tbl_dkinfo struct definition.
 * 	[1998/10/27  18:38:45  Mark_Bokhan]
 * 
 * Revision 4.2.26.18  1998/10/05  14:40:48  Dave_King
 * 	Add TBL_NCSTATS support.
 * 	[1998/09/17  00:16:31  Dave_King]
 * 
 * Revision 4.2.26.17  1998/04/21  19:46:29  Mark_Bokhan
 * 	Add di_pxfer field to tbl_dkinfo struct, the number of
 * 	disk i/o transfers that spent time on the pending queue.
 * 	Also added comments to clarify dkinfo fields.
 * 	[1998/04/17  20:09:51  Mark_Bokhan]
 * 
 * Revision 4.2.26.16  1998/03/10  21:48:43  Anton_Verhulst
 * 	Add start_stop_time and pset_assign_time to tbl_processor.
 * 	[1998/03/10  21:33:23  Anton_Verhulst]
 * 
 * Revision 4.2.26.15  1998/01/15  17:27:51  James_Woodward
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL11:PTCOS_BL14 **
 * 		** Ancestor revision:	4.2.29.2 **
 * 		** Merge revision:	4.2.29.3 **
 * 	 	** End **
 * 	[1998/01/15  17:18:08  James_Woodward]
 * 
 * Revision 4.2.26.14  1997/11/06  12:26:24  James_Woodward
 * 	per-perocessor numa work
 * 	[1997/11/03  13:25:59  James_Woodward]
 * 
 * Revision 4.2.29.3  1997/09/29  20:37:52  Brian_Haley
 * 	Backport steelos-1052-ajay.  Definitions needed for TCP aborts (qar 55702).
 * 	[1997/09/29  14:26:32  Brian_Haley]
 * 
 * Revision 4.2.26.13  1997/09/24  21:21:43  Shashi_Mangalat
 * 	Add backward compatibility code to TBL_SHMINFO.
 * 	[1997/09/23  16:59:16  Shashi_Mangalat]
 * 
 * Revision 4.2.26.12  1997/08/14  12:10:57  Mark_Dewandel
 * 	Added TBL_UMAST_INFO, TBL_XCPU_INTR_MP, and tbl_umast_info
 * 	declarations.
 * 	[1997/08/08  13:31:01  Mark_Dewandel]
 * 
 * Revision 4.2.26.11  1997/06/26  13:08:37  Shashi_Mangalat
 * 	Unix98 conformance: binary compatibility support.
 * 	[1997/06/23  03:20:06  Shashi_Mangalat]
 * 
 * Revision 4.2.26.10  1997/06/02  17:36:25  Mark_Dewandel
 * 	Added TBL_PROCESSOR_INFO.
 * 	[1997/05/28  18:42:34  Mark_Dewandel]
 * 
 * Revision 4.2.26.9  1997/05/09  18:32:52  Stuart_Hollander
 * 	fix pi_pgrp to be pid_t
 * 	[1997/05/08  20:41:22  Stuart_Hollander]
 * 
 * 	Fix types in struct tbl_procinfo.
 * 	[1997/05/08  15:18:33  Stuart_Hollander]
 * 
 * Revision 4.2.26.8  1997/04/24  20:14:25  Stuart_Hollander
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL3:PTCOS_BL6 **
 * 		** Ancestor revision:	4.2.15.14 **
 * 		** Merge revision:	4.2.29.2 **
 * 	 	** End **
 * 	merge of PTmin BL6 changes
 * 	[1997/04/24  20:01:41  Stuart_Hollander]
 * 
 * Revision 4.2.26.7  1997/04/15  18:24:49  Andrew_Duane
 * 	Add TBL_UIDINFO, bumping TBL_THREADSTATES.
 * 	[1997/04/09  19:21:15  Andrew_Duane]
 * 
 * Revision 4.2.29.2  1997/01/31  18:25:52  Andrew_Duane
 * 	Add TBL_UIDINFO define.
 * 	[1996/12/30  15:24:48  Andrew_Duane]
 * 
 * Revision 4.2.26.6  1996/11/15  21:07:18  Ajay_Kachrani
 * 	Add definition for supporting ABORT_IF_TCBS (QAR 48227)
 * 	[1996/10/24  19:38:03  Ajay_Kachrani]
 * 
 * Revision 4.2.26.5  1996/07/24  19:09:21  Andrew_Duane
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit -visual **
 * 		** Ancestor revision:	4.2.26.3 **
 * 		** Merge revision:	4.2.26.4 **
 * 	 	** End **
 * 	Leave TBL_MAPINFO defined; don't retire value yet so it won't be recycled.
 * 	[1996/07/24  18:22:58  Andrew_Duane]
 * 
 * 	C++ fix for QAR 46818
 * 	Remove support for TBL_MAPINFO
 * 	[1996/07/19  14:58:52  Andrew_Duane]
 * 
 * Revision 4.2.26.4  1996/07/24  14:53:55  Jeff_Colburn
 * 	Function prototype work, header definitions
 * 	[1996/07/22  17:38:59  Jeff_Colburn]
 * 
 * Revision 4.2.26.3  1996/06/21  19:44:50  Andrew_Duane
 * 	Added tbl_threadstates structure for TBL_THREADSTATES call.
 * 	[1996/06/20  19:20:53  Andrew_Duane]
 * 
 * Revision 4.2.26.2  1996/05/01  14:34:54  Larry_Woodman
 * 	Merge brom bravos.bl2
 * 	[1996/05/01  14:27:20  Larry_Woodman]
 * 
 * Revision 4.2.24.4  1996/03/07  23:36:32  Jeff_Denham
 * 	merge of Platinum BL8 to BL11 pass 1 changes
 * 	[1996/03/07  23:34:32  Jeff_Denham]
 * 
 * Revision 4.2.15.14  1996/01/08  22:36:10  Ashoke_Rampuria
 * 	Added kb_failed field to kmembucket.
 * 	[1996/01/08  21:06:34  Ashoke_Rampuria]
 * 
 * Revision 4.2.24.3  1995/12/22  16:18:37  Larry_Woodman
 * 	Fix the table_info struct for non-alpha.
 * 	[1995/12/22  16:17:38  Larry_Woodman]
 * 
 * Revision 4.2.24.2  1995/12/18  22:23:21  Jeff_Denham
 * 	Neutralize TBL_MAPINFO cruft.
 * 	[1995/12/18  22:22:32  Jeff_Denham]
 * 
 * Revision 4.2.15.13  1995/12/14  17:49:10  Ajay_Kachrani
 * 	Added TBL_TCPCONN data-structure
 * 	[1995/11/15  19:49:41  Ajay_Kachrani]
 * 
 * Revision 4.2.15.12  1995/12/12  20:38:37  Floyd_Smith
 * 	Added SAR STATS functionality (exception request) (QAR20700) (fys)
 * 	[1995/12/06  20:19:13  Floyd_Smith]
 * 
 * Revision 4.2.15.11  1995/06/28  13:53:43  Mark_Warren
 * 	Back out ptos-1768-fys, per PRMT.
 * 	[1995/06/27  18:47:56  Mark_Warren]
 * 
 * Revision 4.2.15.10  1995/06/12  22:25:54  John_Flanagan
 * 	Removing merge markers
 * 	[1995/06/12  22:25:12  John_Flanagan]
 * 
 * Revision 4.2.15.9  1995/06/12  18:27:52  Floyd_Smith
 * 	Added that needed for QAR20700 (had some extranuous lines) - fys
 * 	[1995/06/07  15:38:51  Floyd_Smith]
 * 
 * 	changes made for "sar statistics" - QAR20700 - fys
 * 	[1995/06/06  13:45:43  Floyd_Smith]
 * 
 * Revision 4.2.15.8  1995/06/12  14:02:39  Andrew_Duane
 * 	Removed ODE merge markers left in 4.2.15.7
 * 	[1995/06/12  13:12:27  Andrew_Duane]
 * 
 * Revision 4.2.15.7  1995/06/09  14:30:04  Humberto_Sanchez
 * 	These changes are for SVE support as documented
 * 	in QAR 30285.
 * 	[1995/06/06  13:28:06  Humberto_Sanchez]
 * 
 * Revision 4.2.15.6  1995/06/06  21:07:24  Anton_Verhulst
 * 	Add TBL_MACHINE_SLOT.
 * 	[1995/06/06  20:05:39  Anton_Verhulst]
 * 
 * Revision 4.2.15.5  1995/05/31  19:43:02  Ann_Milicia
 * 	bmerge to latest
 * 	[1995/05/31  19:35:41  Ann_Milicia]
 * 
 * 	Fix -std1 compiler warnings by ifdef'ing around TBL_MAPINFO
 * 	declares.  QAR 32196.
 * 	[1995/05/16  13:38:43  Ann_Milicia]
 * 
 * Revision 4.2.15.4  1995/05/23  15:37:01  Jie_Yao
 * 	merge of Platinum Lite BL4 changes
 * 	[1995/05/23  14:35:57  Jie_Yao]
 * 
 * Revision 4.2.15.3  1995/04/28  15:48:23  Ann_Milicia
 * 	Make table arg void * instead of caddr_t.
 * 	[1995/04/27  19:04:22  Ann_Milicia]
 * 
 * 	Add table prototype for QARs 30481 and 32196.
 * 	[1995/04/26  20:38:04  Ann_Milicia]
 * 
 * Revision 4.2.17.3  1995/04/07  16:59:57  Anton_Verhulst
 * 	Add TBL_MALLOCSTATS.
 * 	[1995/04/07  15:23:24  Anton_Verhulst]
 * 
 * Revision 4.2.17.2  1995/03/17  19:11:37  Ashoke_Rampuria
 * 	Added defines and data structure for physical memory
 * 	stat and vmstat.
 * 	[1995/03/17  17:07:27  Ashoke_Rampuria]
 * 
 * Revision 4.2.15.2  1994/12/16  15:36:55  Ashoke_Rampuria
 * 	Added TBL_MALLOCNBUCKETS define.
 * 	[1994/12/15  18:42:40  Ashoke_Rampuria]
 * 
 * Revision 4.2.12.3  1994/11/07  19:32:52  Ashoke_Rampuria
 * 	Added define for TBL_MALLOCNTYPES.
 * 	[1994/11/07  18:35:51  Ashoke_Rampuria]
 * 
 * Revision 4.2.12.2  1994/08/26  14:07:24  Ashoke_Rampuria
 * 	Added defines for TBL_MALLOCLEAK and TBL_MALLOCLEAKCOUNT.
 * 	[1994/08/25  18:47:14  Ashoke_Rampuria]
 * 
 * Revision 4.2.10.10  1994/04/25  20:28:40  Geraldine_Harter
 * 	netstat hooks for netisr thread config/usage stats
 * 	[1994/04/25  12:57:00  Geraldine_Harter]
 * 
 * Revision 4.2.10.9  1994/02/26  23:41:31  Ernie_Petrides
 * 	Add TBL_KNLIST support.
 * 	[1994/02/26  23:05:28  Ernie_Petrides]
 * 
 * Revision 4.2.10.8  1994/02/26  18:54:22  Ernie_Petrides
 * 	Isolate internal kmemtypes and kmembuckets data structures from
 * 	user-level table() interface with tbl_malloct and tbl_mallocb.
 * 	[1994/02/26  02:11:27  Ernie_Petrides]
 * 
 * Revision 4.2.10.7  1994/02/16  19:04:49  Ernie_Petrides
 * 	Remove definitions relating to obsolete interrupt counting tables.
 * 	[1994/02/15  20:53:56  Ernie_Petrides]
 * 
 * Revision 4.2.10.6  1993/12/16  20:59:12  Jeff_Denham
 * 	Sterling BL8 merge.
 * 	[1993/12/16  20:18:49  Jeff_Denham]
 * 
 * Revision 4.2.8.4  1993/11/11  20:44:15  Ashoke_Rampuria
 * 	Added defines for TBL_MALLOCBUCKETS, TBL_MALLOCTYPES and
 * 	TBL_MALLOCNAMES.
 * 	[1993/11/10  21:50:41  Ashoke_Rampuria]
 * 
 * Revision 4.2.10.5  1993/11/05  06:29:41  Tim_Hoskins
 * 	merge of Sterling BL7 changes
 * 	[1993/11/05  05:32:25  Tim_Hoskins]
 * 
 * Revision 4.2.8.3  1993/10/16  13:03:47  Joe_Martin
 * 	TBL_MAPINFO
 * 	[1993/10/14  17:54:03  Joe_Martin]
 * 
 * Revision 4.2.10.4  1993/10/08  21:34:41  Jeff_Denham
 * 	Sterling/Gold merge sanity check.
 * 	[1993/10/08  21:20:19  Jeff_Denham]
 * 
 * Revision 4.2.10.3  1993/09/10  18:27:26  Geraldine_Harter
 * 	Add TBL_MALLOCT support, so netstat can obtain mbuf statistics
 * 	(needed for mbuf alloc premerge).
 * 	[1993/09/09  20:58:45  Geraldine_Harter]
 * 
 * Revision 4.2.10.2  1993/09/03  21:57:25  Jeff_Denham
 * 	Add SAR counter constants and structures.
 * 	[1993/08/12  19:39:40  Jeff_Denham]
 * 
 * Revision 4.2.8.2  1993/05/27  19:07:22  Jeff_Denham
 * 	SVR4 SAR integration.
 * 	[1993/05/25  23:48:12  Jeff_Denham]
 * 
 * Revision 4.2.4.6  1992/10/20  14:01:03  James_Woodward
 * 	merge with latest
 * 	[92/10/15  09:37:54  James_Woodward]
 * 
 * 	allow .s files to include header
 * 	[92/10/15  09:28:42  James_Woodward]
 * 
 * Revision 4.2.4.5  92/10/13  16:38:57  Shashi_Mangalat
 * 	Merged in Silver BL10_6.
 * 	  Added TBL_SWAPINFO subfunction and corresponding tbl_swapinfo
 * 	  structure.
 * 	  [92/09/30  14:26:47  John_Gemignani]
 * 	[92/10/13  16:32:08  Shashi_Mangalat]
 * 
 * Revision 4.2.4.4  92/07/14  11:00:27  Jeff_Denham
 * 	"Submit to ALPHA"
 * 
 * Revision 4.2.5.2  92/07/14  10:57:08  Jeff_Denham
 * 	Include <standards.h> and <types.h> to support the new use of sigset_t.
 * 
 * Revision 4.2.4.3  92/07/07  18:58:28  Jeff_Denham
 * 	"Submit to alpha"
 * 
 * Revision 4.2.4.2  92/06/04  12:46:23  Al_Delorey
 * 	From Silver: AG_BL7
 * 	[92/06/03  15:26:03  Al_Delorey]
 * 
 * Revision 4.2.2.2  92/06/02  17:01:49  devbld_gsf
 * 	First AG_BL7 version.  Moved from Ag baselevel delivery tree.
 * 
 * Revision 4.2  91/09/19  23:00:52  devbld
 * 	Adding ODE Headers
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: table.h,v $ $Revision: 4.2.63.3 $ (DEC) $Date: 2004/10/29 16:19:33 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * Copyright (c) 1986 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */

#ifndef	_SYS_TABLE_H_
#define _SYS_TABLE_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>
#include <sys/types.h>
#include <mach/time_value.h>
#include <mach/vm_prot.h>
#include <mach/machine/vm_types.h>
#include <net/if.h>
#include <netinet/in.h>

#define TBL_TTYLOC		0	/* index by device number */
#define TBL_U_TTYD		1	/* index by process ID */
#define TBL_UAREA		2	/* index by process ID */
#define TBL_LOADAVG		3	/* (no index) */
#define TBL_INCLUDE_VERSION	4	/* (no index) */
#define TBL_FSPARAM		5	/* index by device number */
#define TBL_ARGUMENTS		6	/* index by process ID */
#define TBL_MAXUPRC		7	/* index by process ID */
#define TBL_AID			8	/* index by process ID */
#define TBL_MODES		9	/* index by process ID */
#define TBL_PROCINFO		10	/* index by proc table slot */
#define TBL_ENVIRONMENT		11	/* index by process ID */
#define TBL_SYSINFO		12	/* (no index) */
#define TBL_DKINFO		13	/* index by disk */
#define TBL_TTYINFO		14	/* (no index) */
#define TBL_MSGDS		15	/* index by array index */
#define TBL_SEMDS		16	/* index by array index */
#define TBL_SHMDS_V40		17	/* for V40 compatibility */
#define TBL_MSGINFO		18	/* index by structure element */
#define TBL_SEMINFO		19	/* index by structure element */
#define TBL_SHMINFO		20	/* index by structure element */
#define TBL_INTR		21	/* (no index) */
#define TBL_SWAPINFO		22	/* index by vm_swap element */
#define TBL_SCALLS      	23      /* system call info table (no index) */
#define TBL_FILEINFO    	24      /* file access status (no index) */
#define TBL_TBLSTATS    	25      /* system tables status (no index) */
#define TBL_RUNQ        	26      /* run queue status (no index) */
#define TBL_BUFFER      	27      /* buffer activity (no index) */
#define TBL_KMEM      		28      /* kernel memory activity (no index) */
#define TBL_PAGING      	29      /* paging activity (no index) */
#define TBL_MALLOCT             30      /* same as TBL_MALLOCTYPES */
#define TBL_MAPINFO		31	/* DO NOT USE; retired interface in V4.2, remove in V5.0 */
#define TBL_MALLOCBUCKETS	32	/* get malloc allocator kmembuckets */
#define TBL_MALLOCTYPES		33	/* get malloc allocator kmemtypes */
#define TBL_MALLOCNAMES		34	/* get malloc memory type names */
#define TBL_KNLIST		35	/* get kernel namelist table */
#define TBL_NETINFO             36      /* get netisr info */
#define TBL_MALLOCLEAK          37      /* get malloc leak info */
#define TBL_MALLOCLEAKCOUNT     38      /* get malloc leak count */
#define TBL_MALLOCNTYPES	39	/* get number of malloc types - M_LAST*/
#define TBL_MALLOCNBUCKETS      40      /* get number of malloc buckets*/
#define TBL_PMEMSTATS      	41      /* physical memory stats */
#define TBL_PMEMCLUSTERTYPE    	42      /* physical memory cluster type */
#define TBL_PMEMUSETYPE      	43      /* physical memory use type */
#define TBL_PMEMUSAGE      	44      /* physical memory usage */
#define TBL_PMEMCLUSTERS      	45      /* physical memory clusters */
#define TBL_VMSTATS      	46      /* vmstat */
#define TBL_MALLOCMSTATS      	47      /* malloc */
#define	TBL_MACHINE_SLOT	48	/* machine slot */

/* ======================== QAR30285 ================================
                SVE Multiprocessor Version of Above
   ================================================================== */

#define	TBL_SYSINFO_MP		49
#define	TBL_BUFFER_MP		50
#define	TBL_SCALLS_MP		51
#define	TBL_FILEINFO_MP		52
#define	TBL_PAGING_MP		53
#define	TBL_INTR_MP		54

/* ======================== QAR30285 ================================ */

#define	TBL_TCPCONN		55      /* set(delteTCB) tcp conn state */
#define	TBL_UIDINFO		56	/* get uid_max; ignore arguments */
					/* except nel (== 1) */
#define	TBL_THREADSTATES	57	/* Get thread state count(s) */
#define	TBL_PROCESSOR_STATS_INFO 58	/* Get all processor_stats structs */
#define TBL_SHMDS_V50		59	/* for V50 compatibility */
#define TBL_UMAST_INFO		60	/* Get unix_master_info */
#define TBL_XCPU_INTR_MP	61	/* Get per-CPU TB shootdown xintrs */
#define	TBL_PROCESSOR_INFO 	62	/* Get all tbl_processor structs */
#define	TBL_NCSTATS 		63	/* Get name cache stats */
#define TBL_FDSTAT		64	/* Get stat struct for specified pid/fd */
#define TBL_TASKINFO		65	/* Task-related information */
#define	TBL_VNODESTATS		66	/* Get vnode stats */
#define	TBL_VMPERF		67	/* processor VM performance stats */
#define	TBL_NFSSTATS		68	/* Get/Clr client nfs/nfs_stat.h */
#define	TBL_RFSSTATS		69	/* Get/Clr server nfs/nfs_stat.h */
#define	TBL_RPCSTATS		70	/* Get/Clr RPC stats rpc/rpc_stat.h */
#define	TBL_RAD_RNH		71	/* Get RAD's radix_node_head */
#define	TBL_SHMDS		72	/* index by array index */

/* ========================= FLAGS ================================== */
#define TBL_F_RAD		(1L << 32)	/* per-RAD stats */


#define MSGINFO_MAX		0	/* max message size */
#define MSGINFO_MNB		1	/* max # bytes on queue */
#define MSGINFO_MNI		2	/* # of message queue identifiers */
#define MSGINFO_TQL		3	/* # of system message headers */
#define MSGINFO_SAR     	4       /* # of send and receive messages */

#define	SEMINFO_MNI		0	/* # of semaphore identifiers */
#define	SEMINFO_MSL		1	/* max # of semaphores per id */
#define	SEMINFO_OPM		2	/* max # of operations per semop call */
#define	SEMINFO_UME		3	/* max # of undo entries per process */
#define	SEMINFO_VMX		4	/* semaphore maximum value */
#define	SEMINFO_AEM		5	/* adjust on exit max value */
#define SEMINFO_OPT     	6       /* # of semaphore operations */

#define SHMINFO_MAX_COMPAT	0	/* max shared memory segment size */
#define SHMINFO_MIN_COMPAT	1	/* min shared memory segment size */
#define SHMINFO_MNI		2	/* num shared memory identifiers */
#define SHMINFO_SEG		3	/* max attached segments per process */
#define SHMINFO_MAX		4	/* max shared memory segment size */
#define SHMINFO_MIN		5	/* min shared memory segment size */

/*
 *  TBL_FSPARAM data layout
 */

struct tbl_fsparam
{
    long tf_used;		/* free fragments */
    long tf_iused;		/* free inodes */
    long tf_size;		/* total fragments */
    long tf_isize;		/* total inodes */
};


/*
 *  TBL_LOADAVG data layout
 */

struct tbl_loadavg
{
    union {
	    long   l[3];
	    double d[3];
    } tl_avenrun;
    int    tl_lscale;		/* 0 scale when floating point */
    long   tl_mach_factor[3];
};


/*
 *  TBL_INTR data layout
 */

struct tbl_intr
{
	long   	in_devintr;	/* Device interrupts (non-clock) */
	long   	in_context;	/* Context switches */
	long   	in_syscalls;	/* Syscalls */
	long   	in_forks;	/* Forks */
	long   	in_vforks;	/* Vforks */
};


/*
 *  TBL_MODES bit definitions
 */

#define UMODE_P_GID	01	/* - 4.2 parent GID on inode create */
#define UMODE_NOFOLLOW	02	/* - don't follow symbolic links */
#define UMODE_NONICE	04	/* - don't auto-nice long job */



/*
 *	TBL_PROCINFO data layout
 */
#define PI_COMLEN	19	/* length of command string */
struct tbl_procinfo
{
    uid_t	pi_uid;		/* (effective) user ID */
    pid_t	pi_pid;		/* proc ID */
    pid_t	pi_ppid;	/* parent proc ID */
    pid_t	pi_pgrp;	/* proc group ID */
    dev_t	pi_ttyd;	/* controlling terminal number */
    int		pi_status;	/* process status: */
#define PI_EMPTY	0	    /* no process */
#define PI_ACTIVE	1	    /* active process */
#define PI_EXITING	2	    /* exiting */
#define PI_ZOMBIE	3	    /* zombie */
    int		pi_flag;	/* other random flags */
    char	pi_comm[PI_COMLEN+1];
				/* short command name */
    uid_t	pi_ruid;        /* (real) user ID */
    uid_t	pi_svuid;       /* saved (effective) user ID */
    gid_t       pi_rgid;        /* (real) group ID */
    gid_t       pi_svgid;       /* saved (effective) group ID */
    pid_t	pi_session;	/* session ID */
    pid_t       pi_tpgrp;       /* tty pgrp */
    pid_t       pi_tsession;    /* tty session id */
    u_int       pi_jobc;        /* # procs qualifying pgrp for job control */
    int         pi_cursig;
    sigset_t    pi_sig;         /* signals pending */
    sigset_t    pi_sigmask;     /* current signal mask */
    sigset_t    pi_sigignore;   /* signals being ignored */
    sigset_t    pi_sigcatch;    /* signals being caught by user */
};

/*
 *	TBL_TASKINFO data layout
 */
struct tbl_taskinfo
{
    int			ti_suspend_count;
    int			ti_base_priority;
    vm_size_t		ti_virtual_size;
    vm_size_t		ti_resident_size;
    time_value_t	ti_user_time;
    time_value_t	ti_system_time;
    int			ti_swap_state;
#define TI_NOT_QUEUED		0x00
#define TI_INSWAPPED		0x01
#define TI_OUTSWAPPED		0x02
#define TI_COMING_IN		0x03
#define TI_GOING_OUT		0x04
#define TI_UNSWAPPABLE		0x05
    int			ti_pad1;
    unsigned long	ti_pad2;
    unsigned long	ti_pad3;
};

/*
 *	TBL_THREADSTATES data layout
 */
struct tbl_threadstates {
	int	runqueue;	/* Runnable */
	int	waiting;	/* Waiting interruptibly */
	int	unintr;		/* Waiting uninterruptibly */
	int	stopped;	/* Told to stop */
	int	swapped;	/* Swapped out */
	int	idle;		/* Is an idle thread */
};

/*
 *	TBL_SYSINFO data layout
 */
struct tbl_sysinfo {
        long	si_user;		/* User time */
        long	si_nice;		/* Nice time */
        long	si_sys;			/* System time */
        long	si_idle;		/* Idle time */
        long    si_hz;
        long    si_phz;
	long 	si_boottime;		/* Boot time in seconds */
        long wait; /* Wait time */
	int	si_max_procs;		/* rpb->rpb_numprocs */
#define usr si_user
#define sys si_sys
#define idle si_idle
};

/*
 *	TBL_DKINFO data layout
 * 
 * 	Note that these disk statistics have recently been updated.
 * 	Some of the fields (di_seek) reflect obsolete technology.
 * 	The fields beginning with "di_av*" are no longer averages,
 * 	as their names would imply (averages are not calculated
 *	in real time).  For compatibility reasons, the names of
 *	those fields have not changed, even though their meanings
 *	have changed.
 */
#define DI_NAMESZ	8
struct tbl_dkinfo {
	/*******SAR STATS******/
        int  di_ndrive;		/* current number of disk statistics slots */
        int  di_busy;		/* unused */
        long di_time;		/* linear time (usec) spent servicing i/o */
        long di_seek;		/* unused */
        long di_xfer;		/* number of i/o transfers completed */
        long di_wds;		/* number of bytes transfered >>6 */
        long di_wpms;		/* unused */
        int  di_unit;		/* disk unit number */
        char di_name[DI_NAMESZ+1]; /* first DI_NAMESZ char's of disk name */
        long di_avque;		/* number of currently outstanding i/o req's */
        long di_avwait; 	/* TOTAL time (usec) in i/o pending queue */
        long di_avserv; 	/* TOTAL time (usec) in i/o active queue */
	long di_usec;		/* unused */
	long di_initial_busy;	/* internal usage by some disk drivers */
	long di_ref_cnt;	/* internal usage by some disk drivers */
	long di_num_req_initiated;	/* unused */
	long di_num_req_completed;	/* unused */
        long di_pxfer; 		/* number of i/o requests that spent time in
				 * the pending queue
				 */
	/*******SAR STATS******/
};
        
/*
 *	TBL_UMAST_INFO data layout
 */

struct tbl_umast_info {
	int	umast_calls;
	int	umast_to_master;
	int	umast_block;
	int	umast_release;
	int	umast_rel_cpu;
	int	umast_rel_block;
};

/*
 *	TBL_TTYINFO data layout
 */
struct tbl_ttyinfo {
        long	ti_nin;
        long	ti_nout;
        long	ti_cancc;
        long	ti_rawcc;
        long rcvin;     /* # of receive hardware interrupts (always zero) */
        long xmtin;     /* # of transmit hardware interrupts (always zero) */
        long mdmin;     /* # of modem interrupts (always zero) */
#define rawch ti_nin    /* see above */
#define canch ti_cancc  /* see above */
#define outch ti_nout   /* see above */
};

/*
 *	TBL_SWAPINFO data layout
 */
struct tbl_swapinfo {
	int	flags;
	int	size;
	int	free;
	dev_t	dev;
	ino_t	ino;
	};

/* 
 *	TBL_FILEINFO data layout - file access stats
 */
struct tbl_file {
	long iget;
	long namei;
	long dirblk;
};

/*
 *	 TBL_RUNQ data layout - run queue stats
 */
struct tbl_runq {
	long runque; /* processes in run queue */
	long runocc; /* % of time run queue is occupied */
};

/*
 *	TB__SCALLS data layout - system call stats
 */
struct tbl_scalls {
	long syscall; /* all system calls */
	long sysread; /* read system calls */
	long sysfork; /* fork system calls */
	long syswrite; /* write system calls */
	long sysexec; /* exec system calls */
	ulong readch; /* bytes transferred on read system calls */
	ulong writech; /* bytes transferred on write system calls */
};

/*
 *	TBL_BUFFER data layout - buffer activity
 */
struct tbl_buffer {
	long bread; /* # of physical block reads into system */
	long bwrite; /* # of physical writes from system buffers */
	long lread; /* logical reads from system buffer */
	long lwrite; /* logical writes from system buffer */
	long phread; /* # of physical read requests */
	long phwrite; /* # of physical write requests */
};

/*
 *	TBL_TBLSTATS - file tables stats
 */

struct tbl_tblstats {
	long tb_procu; /* process table entries used */
	long tb_proca; /* process table entries allocated */
	long tb_inodu; /* inode table entries used */
	long tb_inoda; /* inode table entries alocated */
	long tb_fileu; /* file table entries used */
	long tb_filea; /* file table entries allocated */
	long tb_procov; /* proc table overflows */
	long tb_inodov; /* inode table overflows */
	long tb_fileov; /* file table overflows */
	long tb_locku; /* shared memory table entries used */
	long tb_locka; /* shared memory table entries allocated */
};

/*
 *	TBL_KMEM - kernel memory stats
 */

struct tbl_kmem {
	ulong kmem_avail;		/* total kernel memory available */
	ulong kmem_alloc;		/* total kernel memory allocated */
	long kmem_fail;			/* # of kernel memory request failures */
};

/*
 *	TBL_PAGING - paging stats
 */
struct tbl_paging {
	/* sar -g and -p */
	long v_pgpgin;			/* # of pages paged-in */
	long v_sftlock;			/* # of software lock faults */
	long v_pgout;			/* # of page-out requests */
	long v_dfree;			/* # of pages freed */
	long v_scan;			/* # of pages scanned */
	long v_s5ifp;			/* # of s5 inodes taken of freelist */
	/* sar -r */
	long freeswap;			/* # of 512-byte disk blocks avail for page swapping */
};

/*
 *	TBL_MALLOCT and TBL_MALLOCTYPES data layout.
 */
struct tbl_malloct {
	long	kt_memuse;	/* # of bytes of this type in use */
	long	kt_limit;	/* # of bytes of this type allowed to exist */
	long    kt_wait;        /* blocking flag for this type of memory */
	long	kt_limblocks;	/* stat: # of times blocked for hitting limit */
	long	kt_failed;	/* stat: # of times failed for hitting
							limit with NOWAIT */
	long	kt_maxused;	/* stat: max # of bytes of this type ever used*/
};

/*
 *	TBL_MALLOCBUCKETS data layout.
 */
struct tbl_mallocb {
	void	*kb_next;	/* list of free blocks */
	long	kb_indx;	/* this bucket's index */
	long	kb_size;	/* bucket element size */
	long	kb_free;	/* # of free elements in this bucket */
	long	kb_total;	/* # of elements allocated to this bucket at
							 any given time */
	long	kb_failed;	/* # of times we failed to allocate */
};

/*
 * physical memory stats 
 */

struct  tbl_pmemstats {
	long 	pagesize;
	long 	physmem;
	long	npmem_clusters;
	long	npmem_cluster_type;
	long	npmem_usage;
	long	npmem_use_type;
	long	pmem_typesize;
};

/*
 * physical memory use 
 */

struct  tbl_pmemuse {
        vm_offset_t             start;          /* start addr */
        vm_offset_t             end;            /* end addr */
        int                     type;           /* mem use type */
        struct tbl_pmemuse      *next;          /* pointer to next element */
};

/*
 * physical memory cluster 
 */

struct  tbl_pmemcluster {
        vm_offset_t             start;          /* start addr */
        vm_offset_t             end;            /* end addr */
        int                     type;           /* mem use type */
};

/*
 * vmstats 
 */

struct  tbl_vmstats {
        long    pagesize;               /* page size in bytes */
        long    free_count;             /* # of pages free */
        long    active_count;           /* # of pages active */
        long    inactive_count;         /* # of pages inactive */
        long    wire_count;             /* total # of pages wired down */
        long    zero_fill_count;        /* # of zero fill pages */
        long    reactivations;          /* # of pages reactivated */
        long    pageins;                /* # of pageins */
        long    pageouts;               /* # of pageouts */
        long    faults;                 /* # of faults */
        long    cow_faults;             /* # of copy-on-writes */
        long    lookups;                /* UBC cache lookups */
        long    hits;                   /* UBC cache hits */
        long    user_ptepages;          /* # of user pte pages */
        long    kernel_ptepages;        /* # of kernel pte pages */
        long    free_ptepages;          /* # of free ptepages */
        long    ubc_pages;              /* # of ubc pages */
        long    contig_pages;           /* # of contig_malloc pages */
        long    malloc_pages;           /* # of malloc pages */
        long    vm_wired_count;         /* # of vm wired pages */
        long    ubc_wired_count;        /* # of ubc wired pages */
        long    meta_data_count;        /* # of meta data buffer pages */
        long    task_swapins;           /* # of task swapins */
        long    task_swapouts;          /* # of task swapouts */
        long    task_inswap_count;      /* # of resident tasks */
        long    task_outswap_count;     /* # of swapped out tasks */
	long	ubc_active_count;	/* # of ubc pages active */
	long	ubc_inactive_count;	/* # of ubc pages inactive */
};

#ifdef	_KERNEL
struct  tbl_vmstats_compat {
        long    pagesize;               /* page size in bytes */
        long    free_count;             /* # of pages free */
        long    active_count;           /* # of pages active */
        long    inactive_count;         /* # of pages inactive */
        long    wire_count;             /* total # of pages wired down */
        long    zero_fill_count;        /* # of zero fill pages */
        long    reactivations;          /* # of pages reactivated */
        long    pageins;                /* # of pageins */
        long    pageouts;               /* # of pageouts */
        long    faults;                 /* # of faults */
        long    cow_faults;             /* # of copy-on-writes */
        long    lookups;                /* object cache lookups */
        long    hits;                   /* object cache hits */
        long    user_ptepages;          /* # of user pte pages */
        long    kernel_ptepages;        /* # of kernel pte pages */
        long    free_ptepages;          /* # of free ptepages */
        long    ubc_pages;              /* # of ubc pages */
        long    contig_pages;           /* # of contig_malloc pages */
        long    malloc_pages;           /* # of malloc pages */
        long    vm_wired_count;         /* # of vm wired pages */
        long    ubc_wired_count;        /* # of ubc wired pages */
        long    meta_data_count;        /* # of meta data buffer pages */
};
#endif

/*
 *	TBL_KNLIST data layout.
 */
#define TBL_KNLIST_NAMSIZ 24
struct tbl_knlist {
	void	*kn_addr;			/* symbol address */
	char	kn_name[TBL_KNLIST_NAMSIZ];	/* symbol name */
};
/* Netisr thread info */
struct tbl_netinfo {
        int     nt_nthreads;    /* # configured netisr threads */
        int     nt_maxactive;   /* max # concurrently active threads */
};

#ifndef	_KERNEL
extern	int    table __((long, long, void *, long, u_long));
extern	int    clu_table __((long, long, void *, long, u_long, int));
#endif /* _KERNEL */

#ifdef __cplusplus
}
#endif
/* MALLOC_STATS is used in bsd/{kern_malloc,cmu_syscalls}.c */
#undef MALLOC_STATS
#define MSTATS_REQUEST 50
struct malloc_stats {
	int request_size;
	int bucket_size;
	long nmalloc;		/* number of invokations */
};

/*
 *    TBL_TCPCONN data layout.
 *    tbl_tcpconn and tbl_tcpops are both used with the same system
 *    id and thus must begin with a common 'state' member. tbl_tcpops
 *    may contain more info the tbl_tcpconn and may support additional
 *    operations in the future.
 *    
 */
#define       DELETETCB       12
#define       ABORT_IF_TCBS   1

struct tbl_tcpconn {
      int             state;      /* must be DELETETCB or ABORT_IF_TCBS */
      struct in_addr  local_addr; /* local IP address for this conn. */
      u_short         local_port; /* local port number for this conn. */
      struct in_addr  rem_addr;   /* remote IP address for this conn. */
      u_short         rem_port;   /* remote port number for this conn. */
};

struct tbl_tcpops {
      int             state;      /* must be DELETETCB or ABORT_IF_TCBS */
      struct sockaddr_storage  local_addr; /* local IP address for this conn. */
      struct sockaddr_storage  rem_addr;  /* remote IP address for this conn. */
};

struct abort_inps  {
      struct inpcb    *abortinp;  /* ptr to inpcb */
};

struct tbl_processor {
	long desired_load;
	long load_avg;
	long int_load_avg;
	long rt_load_avg;
	struct timeval start_stop_time;
	struct timeval pset_assign_time;
	int  mhz;
	int  spare_int;
	u_long  num_cache_bytes;
	u_long  type;
	long spare_long[47];
};

/*
 * Name cache stats.
 */
struct tbl_ncstats {
	u_long	nc_goodhits;		/* Good hit, positive */
	u_long	nc_neghits;		/* Good hit, negative */
	u_long	nc_badhits;		/* Bad hit, must drop (RENAME/DELETE)*/
	u_long	nc_falsehits;		/* Bad hit, v_id mismatch */
	u_long	nc_miss;		/* Miss, no entry found in cache */
	u_long	nc_long;		/* Miss, name too long for cache */
	u_long	nc_badtimehits;		/* Bad hit, nache_valid_time expiry */
	u_long	nc_collisions;		/* Collisions inserting new entries */
	u_long	nc_unequaldups;		/* On insert, found invalid entry */
	u_long	nc_newentry;		/* new entry with no dup */
	u_long	nc_newnegentry;		/* negative entry inserted */
	u_long	nc_gnn_hit;		/* negative hit in gnnchash list */
	u_long	nc_gnn_miss;		/* bogus local negative hit */
	u_long	nc_gnn_badhits;		/* remove gnnchash entry */
	u_long	nc_gnn_collision;	/* duplicate gnn entry */
	u_long	nc_pad[1];		/* Future expansion. */
};

/*
 * Vnode table stats.
 */
struct tbl_vnodestats {
	u_long	vn_allocations;		/* number of vnode MALLOCs */
	u_long	vn_recycled;		/* number of vnodes recycled */ 
	u_long	vn_getnewcalls;		/* number of calls to getnewvnode */
	u_long	vn_getlock;		/* getnewvnode hitting lock or VXLOCK */
	u_long	vn_vgetcalls;		/* total calls to vgetm */
	u_long	vn_vgetfree;		/* calls to vgetm accessing free list */
	u_long	vn_freecalls;		/* total number put on free list */
	u_long	vn_failget;		/* failed getnewvnode calls */
	u_long	vn_waitvxlock;		/* VXLOCK hit in wait_for_vxlock */
	u_long	vn_inactivating;	/* vget found VINACTIVATING */
	u_long	vn_transitioning;	/* vgetm_nowait VXLOCK|VINACTIVATING */
	u_long	vn_prim_deallocs;	/* # primary deallocs (getnewvnode) */
	u_long	vn_sec_deallocs;	/* # secondary deallocs (vdealloc) */
	u_long	vn_failed_prim_deallocs;/* primary deallocation failures  */
	u_long	vn_failed_sec_deallocs;	/* secondary deallocation failures */
	u_long	vn_pad[9];		/* pad out to 192 bytes */
};

/*
 * Processor VM performance stats.
 */
typedef	unsigned long vpf_t;

struct tbl_vmperf {
	int   vp_pid;			/* Processor set/Partition id */
	int   vp_rad;			/* RAD id or RAD count */
	int   vp_cpu;			/* cpu id or cpu count*/
	int   vp_ticks;			/* accumulated ticks */
	/*
	 * VM
	 */
	vpf_t vp_v_faults;		/* VM All page faults */
	vpf_t vp_v_kfaults;		/* VM Kernel page faults */
	vpf_t vp_v_cowcopy;		/* VM Optimized COW faults */
	vpf_t vp_v_kzfod;		/* VM Kernel zero filled on demand */
	vpf_t vp_v_pagesteal;		/* VM page steals */
	vpf_t vp_v_prewrites;		/* VM pre-writes */
	vpf_t vp_v_anon_prewrites;	/* VM "" anon */
	vpf_t vp_v_swap_prewrites;	/* VM "" anon */
	vpf_t vp_v_cleanrecs;		/* VM clean reclaims */
	vpf_t vp_v_swaprecs;		/* VM Swap write reclaims */
	vpf_t vp_v_lmsteal;		/* VM Low Mem. steal */
	vpf_t vp_v_lmstealwins;		/* VM Low Mem. steal wins */
	vpf_t vp_v_ffl;			/* VM faults from free list */
	vpf_t vp_v_pout_scan;		/* VM vm_pageout_scan calls */
	vpf_t vp_v_pout_pagescan;	/* VM pages scanned */
	vpf_t vp_v_pout_call;		/* VM pageout calls */
	vpf_t vp_v_pout;		/* VM successful pageouts */
	vpf_t vp_v_pout_target;		/* VM vm target met */
	vpf_t vp_v_pout_burst;		/* VM vm I/O met */
	vpf_t vp_v_act_scans;		/* VM active pages examined */
	vpf_t vp_v_act_moves;		/* VM active pages deactivated */
	vpf_t vp_v_lock_fails;		/* VM failed oop lock tries */
	vpf_t vp_v_migrations;		/* VM page migrations */
	/*
	 * UBC
	 */
	vpf_t vp_u_allocscans;		/* UBC page alloc LRU scans */
	vpf_t vp_u_alloceol;		/* UBC "" end-of-LRU reached */
	vpf_t vp_u_allocpush;		/* UBC "" pushed page */
	vpf_t vp_u_allocstole;		/* UBC "" stole page */
	vpf_t vp_u_allocseq;		/* UBC "" seq drain attempts */
	vpf_t vp_u_wacalls;		/* UBC write ahead calls */
	vpf_t vp_u_wascans;		/* UBC "" scans */
	vpf_t vp_u_waeol;		/* UBC "" end-of-LRU */
	vpf_t vp_u_prges;		/* UBC ubc_mem_purges */
	vpf_t vp_u_prgscans;		/* UBC "" LRU scans */
	vpf_t vp_u_prgeol;		/* UBC "" end-of-LRU */
	vpf_t vp_u_prgburst;		/* UBC "" I/O target met */
	vpf_t vp_u_prgfree;		/* UBC "" pages freed */
	vpf_t vp_u_mmapfree;	 	/* UBC mmaped page freed */
	vpf_t vp_u_wdeny;		/* UBC FS denied writes */
	vpf_t vp_u_hardsteals;		/* UBC hardsteals */
	vpf_t vp_u_stealscans;		/* UBC pagesteal scans */
	vpf_t vp_u_dirtywra;		/* UBC dirty write aheads */
	vpf_t vp_u_reclaim;		/* UBC page reclaims */
	vpf_t vp_u_pagesteal;		/* UBC page steals */
	vpf_t vp_u_lookups;		/* UBC lookup tries */
	vpf_t vp_u_lookuphits;		/* UBC lookup hits */
	vpf_t vp_u_ffl;			/* UBC fault from free list */
	vpf_t vp_u_lmsteal;		/* UBC low mem steal */
	vpf_t vp_u_lmstealwins;		/* UBC low mem steal wins */
	vpf_t vp_u_seqdrain;		/* UBC sequential drains */
	/*
	 * Totals
	 */
	vpf_t vp_tv_cowfaults;		/* VM Cow part of all faults */
	vpf_t vp_tv_zfod;		/* VM User zero filled on demand */
	vpf_t vp_tv_iowrites;		/* VM I/O writes */
	vpf_t vp_tv_pgwrites;		/* VM Page writes */
	vpf_t vp_tv_ioreads;		/* VM I/O reads */
	vpf_t vp_tv_pgreads;		/* VM Page reads */
	vpf_t vp_tv_reactivate;		/* VM Pageout system reactivate */
	vpf_t vp_tu_reactivate;		/* UBC referenced LRU page */
	vpf_t vp_tu_alloc;		/* UBC memory demand of ubc */
	vpf_t vp_tu_iowrites;		/* UBC I/O issued */
	vpf_t vp_tu_pgwrites;		/* UBC pages written */
	/*
	 * More UBC
	 */
	vpf_t vp_u_act_scans;		/* UBC approximation scans */
	vpf_t vp_u_deactivates;		/* UBC page deactivate */
};

#ifdef	_KERNEL
/* for HP Use Only */
struct xtnd_args {
	long id;
	long index;
	caddr_t addr;
	long nel;
	u_long lel;
	int  memberID;
};
struct privs {
	pid_t pid;
	int sec_debug;
	struct ucred *cred;
};
#endif /* _KERNEL */
#endif	/* _SYS_TABLE_H_ */


