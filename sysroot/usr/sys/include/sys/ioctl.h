/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: ioctl.h,v $
 * Revision 4.4.115.1  2003/09/23  22:01:03  Brian_Haley
 * 	Mobile IPv6 - Home Agent, add/remove prefix
 *
 * Revision 4.4.98.2  2000/10/30  23:47:23  Brian_Haley
 * 	Added SIOCDISARPREQ and SIOCENAARPREQ defines for ioctl's to
 * 	disable/enable ARP for a local IP address (qar 83031).  Changed
 * 	defines of the other ARPREQ's to have a "struct arpreq" arg
 * 	since that's what correct.  Kept old defines around as "O" to
 * 	not break binary compatability.
 *
 * Revision 4.4.98.1  2000/07/19  15:34:15  Sowmini_Varadhan
 *  - Added SIOCIPV6DELGATE and ipv6 ioctls from in6.h
 *
 * Revision 4.4.96.1  1999/09/10  19:00:14  Kris_Corwin
 * 	Add I_FATTACH ioctl.
 *
 * Revision 4.4.56.19  1999/03/23  23:46:50  Per_Hamnqvist
 * 	Revise list of ioctl functions for IP Traffic Control
 * 	1. SIOCGHASHINFO (new)
 * 	2. SIOCGLISTSPECFLOW (new)
 * 	3. SIOCGLISTSPECFILT (new)
 * 	4. SIOCGTCNTLLIST (no longer used; added in steel)
 * 	[1999/03/23  02:28:37  Per_Hamnqvist]
 * 
 * Revision 4.4.56.18  1999/03/12  16:37:36  Ted_Qian
 * 	added gratuitous ARP request.
 * 	[1999/02/26  17:59:22  Ted_Qian]
 * 
 * Revision 4.4.56.17  1999/02/23  15:57:49  Farrell_Woods
 * 	Added SIOCAARPREQ ioctl for cluster alias project.  This
 * 	allows a user level program (with root priv's) to issue
 * 	a gratuitous arp.  This will be used by aliasd to send
 * 	gratuitous arps for "common subnet" cluster alias addresses.
 * 	[1999/02/22  19:43:49  Farrell_Woods]
 * 
 * Revision 4.4.56.16  1998/10/30  13:49:03  Ted_Qian
 * 	added SIOCTMTSTATEMODIFY
 * 	[1998/10/27  22:22:56  Ted_Qian]
 * 
 * 	niff'izing NetRAIN project.
 * 	[1998/10/23  18:32:24  Ted_Qian]
 * 
 * Revision 4.4.56.15  1998/10/13  15:50:51  Brian_Haley
 * 	Moved SIOCGIFINDEX to be consistent with 4.0F.  Re-organized
 * 	network section so it is in numerical order to help avoid
 * 	duplicating #'s (qar 64558).
 * 	[1998/10/09  19:27:49  Brian_Haley]
 * 
 * Revision 4.4.56.14  1998/09/01  19:13:32  Jan_Reimers
 * 	Added MTIOCRDPOS ioctl definition
 * 	[1998/08/12  19:06:39  Jan_Reimers]
 * 
 * Revision 4.4.56.13  1998/07/08  19:33:16  Farrell_Woods
 * 	Pull in NIFF changes from tcr4os pool.
 * 	[1998/07/01  00:09:03  Farrell_Woods]
 * 
 * Revision 4.4.56.12  1998/05/21  15:59:55  Vladislav_Yasevich
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	4.4.56.10 **
 * 		** Merge revision:	4.4.56.11 **
 * 	 	** End **
 * 	Added 2 new ioctls to get the Medai mtu size and interface type.
 * 	QAR# 23838
 * 	[1998/05/20  16:15:39  Vladislav_Yasevich]
 * 
 * Revision 4.4.56.11  1998/05/11  20:24:12  Anton_Verhulst
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL14:PTEV6OS_BL4 **
 * 		** Ancestor revision:	4.4.61.3 **
 * 		** Merge revision:	4.4.71.2 **
 * 	 	** End **
 * 	[1998/05/11  20:08:40  Anton_Verhulst]
 * 
 * Revision 4.4.71.2  1998/03/31  22:27:17  Farrell_Woods
 * 	Back-port of NetRAIN
 * 	[1998/02/20  21:05:42  Farrell_Woods]
 * 
 * Revision 4.4.56.10  1998/01/15  20:08:22  Anton_Verhulst
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL11:PTCOS_BL14 **
 * 		** Ancestor revision:	4.4.61.2 **
 * 		** Merge revision:	4.4.61.3 **
 * 	 	** End **
 * 	[1998/01/15  20:06:39  Anton_Verhulst]
 * 
 * Revision 4.4.61.3  1997/10/09  23:22:29  Tony_Bono
 * 	Added the definition of several ioctls used to support the
 * 	wired output for tcp.
 * 	[1997/10/09  15:40:20  Tony_Bono]
 * 
 * Revision 4.4.56.9  1997/09/29  20:43:35  Michael_Enright
 * 	added SIOCGIFINDEX
 * 	[1997/09/26  02:01:04  Michael_Enright]
 * 
 * Revision 4.4.56.8  1997/07/23  15:41:20  John_Dustin
 * 	For RSVP project, Markus Jork:
 * 	added two new ioctl cmds
 * 	[1997/07/10  19:39:17  John_Dustin]
 * 
 * 	Removed #ifdef INTSERV around traffic control ioctls.
 * 	[1997/06/18  16:34:19  Markus_Jork]
 * 
 * 	Added new ioctls for traffic control support.
 * 	[1997/06/17  18:28:27  Markus_Jork]
 * 
 * Revision 4.4.56.7  1997/06/04  18:42:23  Ken_Martin
 * 	Added GETMAP definition to deal with file sparseness maps.  This fixes
 * 	QAR 53303.
 * 	[1997/06/03  20:18:53  Ken_Martin]
 * 
 * Revision 4.4.56.6  1997/04/23  19:08:26  Andrew_Duane
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL3:PTCOS_BL6 -visual **
 * 		** Ancestor revision:	4.4.42.2 **
 * 		** Merge revision:	4.4.61.2 **
 * 	 	** End **
 * 	merge of PTmin BL6 changes - moved FIREWALL ioctl numbers
 * 	[1997/04/23  18:47:16  Andrew_Duane]
 * 
 * Revision 4.4.61.2  1997/02/25  19:51:43  Ajay_Kachrani
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -j4.4.33.9:4.4.42.2 **
 * 		** Ancestor revision:	4.4.33.9 **
 * 		** Merge revision:	4.4.42.2 **
 * 	 	** End **
 * 	[1997/02/11  22:23:08  Ajay_Kachrani]
 * 
 * 	Firewall patch
 * 	[1997/02/11  22:03:48  Ajay_Kachrani]
 * 
 * Revision 4.4.56.5  1997/02/25  17:07:33  Janet_Schank
 * 	Added XOPEN and OSF_SOURCE check around file
 * 	system ioctl defines.
 * 	[1997/02/25  17:06:15  Janet_Schank]
 * 
 * Revision 4.4.56.4  1997/02/19  19:52:55  Steve_Hurst
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rSTEELOS -visual **
 * 		** Ancestor revision:	4.4.42.2 **
 * 		** Merge revision:	4.4.56.3 **
 * 	 	** End **
 * 	[1997/02/18  19:20:45  Steve_Hurst]
 * 
 * 	This checkin is for NetRAIN support. The changes here include
 * 	additional ioctl commands for NetRAIN.
 * 	[1997/02/12  16:29:28  Steve_Hurst]
 * 
 * Revision 4.4.56.3  1997/01/24  15:47:15  Kris_Corwin
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	4.4.42.2 **
 * 		** Merge revision:	4.4.56.2 **
 * 	 	** End **
 * 	add TIOCISATTY
 * 	[1997/01/09  16:35:35  Kris_Corwin]
 * 
 * Revision 4.4.56.2  1997/01/17  16:06:47  Janet_Schank
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rSTEELOS;PTBOS_BL4;<> **
 * 		** Ancestor revision:	4.4.33.9 **
 * 		** Merge revision:	4.4.42.2 **
 * 	 	** End **
 * 	[1997/01/16  15:52:14  Janet_Schank]
 * 
 * 	Added defines for GETCACHEPOLICY and SETCACHEPOLICY.
 * 	[1996/12/16  12:59:33  Janet_Schank]
 * 
 * Revision 4.4.42.2  1996/10/30  19:25:18  Stephen_Ofsthun
 * 	Add new debugger line discipline KDBDISC.
 * 	[1996/10/29  16:19:53  Stephen_Ofsthun]
 * 
 * Revision 4.4.33.9  1995/08/18  20:51:03  Dirce_Richards
 * 	Introduce access filter (provided by Fred Templin)
 * 	[1995/08/16  15:48:48  Dirce_Richards]
 * 
 * Revision 4.4.33.8  1995/08/15  18:14:26  Thomas_Peterson
 * 	Add _OSF_SOURCE to !_XOPEN_SOURCE_EXTENDED conditionals to restore
 * 	the less-restrictive name space in the default case for c89.  Also
 * 	fixed extern "C" blocks & replaced _NO_PROTO #ifdef block with __()
 * 	macro from <standards.h>.
 * 	[1995/08/10  17:34:32  Thomas_Peterson]
 * 
 * Revision 4.4.33.7  1995/06/30  22:39:04  Mike_Milicia
 * 	Add MLS secure networking hooks.
 * 	[1995/06/20  22:23:21  Mike_Milicia]
 * 
 * Revision 4.4.33.6  1995/06/15  20:29:41  Ajay_Kachrani
 * 	bmerged
 * 	[1995/06/13  20:56:28  Ajay_Kachrani]
 * 
 * 	Add quoutes missed
 * 	[1995/05/26  19:55:33  Ajay_Kachrani]
 * 
 * 	Add SIOCGETVIFCNT and SIOCGETSGCNT for 3.5 IP Multicast support.
 * 	[1995/05/19  20:40:23  Ajay_Kachrani]
 * 
 * Revision 4.4.33.5  1994/12/16  00:27:49  Sunil_Bangad
 * 	Conditionalized inclusion to restrict for Spec1170 namespace
 * 	rules.  Duplicated and aligned with Spec1170 namespace rules
 * 	the _IOC related macros.
 * 	[1994/12/13  22:09:17  Sunil_Bangad]
 * 
 * Revision 4.4.33.4  1994/10/09  18:37:33  Deepak_Gupta
 * 	Merged with platinum .BL1
 * 	[1994/10/09  18:35:52  Deepak_Gupta]
 * 
 * Revision 4.4.31.3  1994/09/27  18:20:01  Deepak_Gupta
 * 	merged with GOLD MINOR .BL2
 * 	[1994/09/27  18:16:25  Deepak_Gupta]
 * 
 * Revision 4.4.31.2  1994/09/23  18:58:11  Deepak_Gupta
 * 	prototype for ioctl is correctly surrounded by C++ wrappers.
 * 	[1994/09/23  18:57:52  Deepak_Gupta]
 * 
 * Revision 4.4.30.2  1994/08/29  19:01:46  Robert_Fontaine
 * 	New constant definitions and macros for Asian tty support.
 * 	[1994/08/26  18:59:45  Robert_Fontaine]
 * 
 * Revision 4.4.26.2  1994/07/20  21:34:58  atmproj_Peter_Schulter
 * 	bsubmitted from shared SB
 * 	[1994/07/20  20:29:09  atmproj_Peter_Schulter]
 * 
 * Revision 4.4.22.8  1994/05/24  17:03:14  Jeff_Denham
 * 	Remove comment about AIO ioctl commands. No longer needed.
 * 	[1994/05/23  19:58:01  Jeff_Denham]
 * 
 * Revision 4.4.22.7  1993/12/16  20:59:01  Jeff_Denham
 * 	Sterling BL8 merge.
 * 	[1993/12/16  20:18:36  Jeff_Denham]
 * 
 * Revision 4.4.14.10  1993/11/27  13:37:09  Brett_Sampson
 * 	fix problem in earlier submit
 * 	[1993/11/27  13:36:31  Brett_Sampson]
 * 
 * Revision 4.4.14.9  1993/11/27  13:23:13  Brett_Sampson
 * 	fix ioctl.h for x build
 * 	[1993/11/27  13:22:30  Brett_Sampson]
 * 
 * Revision 4.4.14.8  1993/11/23  21:41:12  William_Burns
 * 	Add function prototype for ioctl.
 * 	[1993/10/22  13:16:49  William_Burns]
 * 
 * Revision 4.4.22.6  1993/10/08  18:42:58  Anton_Verhulst
 * 	Sterling BL6 to Gold BL7 Merge
 * 	[1993/10/08  18:18:46  Anton_Verhulst]
 * 
 * Revision 4.4.22.5  1993/09/28  22:48:30  Peter_Schulter
 * 	Pre-merge of IP aliasing code
 * 	[1993/09/28  21:30:07  Peter_Schulter]
 * 
 * Revision 4.4.22.4  1993/09/15  18:03:20  Ronald_Menner
 * 	Added UNLCKPT and ISPTS ioctls... modified ISPTM to be an
 * 	IO_VOID type ioctl
 * 	[1993/09/14  14:06:14  Ronald_Menner]
 * 
 * Revision 4.4.22.3  1993/08/26  18:22:22  Julia_Fey
 * 	Token Ring premerge
 * 	[1993/08/25  21:35:35  Julia_Fey]
 * 
 * Revision 4.4.22.2  1993/08/18  21:29:55  Peter_Schulter
 * 	SVR4 Compatable STREAMS infrastructure premerge
 * 	[1993/08/18  18:21:32  Peter_Schulter]
 * 
 * Revision 4.4.14.7  1993/07/27  15:21:24  Robert_Scott
 * 	Map SVID-required ioctls (TCGETS, TCSETS, TCSETSW, TCSETSF) to others.
 * 	[1993/07/23  16:18:22  Robert_Scott]
 * 
 * Revision 4.4.14.6  1993/07/13  19:30:05  Peter_Schulter
 * 	Added SIOCPIFADDR for IP aliases
 * 	[1993/07/13  17:33:13  Peter_Schulter]
 * 
 * Revision 4.4.14.5  1993/05/26  17:47:58  Ronald_Menner
 * 	correct TIOCGSID ioctl to be a IOR ioctl
 * 	[1993/05/20  21:28:32  Ronald_Menner]
 * 
 * Revision 4.4.14.4  1993/05/12  19:02:24  Peter_Schulter
 * 	Check in for submit to minor pool
 * 	[1993/05/12  16:13:46  Peter_Schulter]
 * 
 * Revision 4.4.9.5  1993/05/11  03:44:48  Ronald_Menner
 * 	merge to Sterling BL2+
 * 	[1993/05/11  03:19:54  Ronald_Menner]
 * 
 * Revision 4.4.9.4  1993/04/30  20:49:59  Ronald_Menner
 * 	Merge with Sterling BL1
 * 	[1993/04/30  14:40:21  Ronald_Menner]
 * 
 * Revision 4.4.14.3  1993/04/20  15:02:52  Uttam_Shikarpur
 * 	Removed referece to ifval structure from SIOCRIPMTU  and SIOCRMACSPEED
 * 	[1993/04/19  20:35:17  Uttam_Shikarpur]
 * 
 * 	Merged the file with the Minor pool.
 * 	[1993/04/19  19:45:14  Uttam_Shikarpur]
 * 
 * 	Added SIOCRIPMTU and SIOCRMACSPEED.
 * 	[1993/04/13  20:21:12  Uttam_Shikarpur]
 * 
 * 	Added SIOCSIPMTU ioctl to set the IP MTU.
 * 	[1993/04/13  14:54:29  Uttam_Shikarpur]
 * 
 * 	Submit to the FT pool.
 * 	[1993/04/06  14:37:56  Uttam_Shikarpur]
 * 
 * Revision 4.4.9.3  1993/04/02  15:00:48  Ronald_Menner
 * 	Modified made TIOCGETSID & ISPTM IOC_VOIDs; added ISPTS & UNLCKPT
 * 	[1993/04/02  15:00:09  Ronald_Menner]
 * 
 * Revision 4.4.14.2  1993/04/01  20:07:06  Michael_Fairbrother
 * 	Merge from shared sandbox to sandbox prior to submit
 * 	[1993/04/01  15:49:37  Michael_Fairbrother]
 * 
 * Revision 4.4.12.2  1993/03/25  01:50:45  Larry_Scott
 * 	added comment to reserve group 'C' ioctl's
 * 	[1993/03/25  01:50:23  Larry_Scott]
 * 
 * Revision 4.4.9.2  1993/03/10  21:39:46  Peter_Schulter
 * 	First pass at R4 STREAMS Alpha port
 * 	[1993/03/10  21:34:41  Peter_Schulter]
 * 
 * Revision 4.4.3.6  1992/06/03  13:44:47  Paul_Hansen
 * 	Merged in Silver BL7
 * 	[92/06/03  13:35:22  Paul_Hansen]
 * 
 * Revision 4.4.3.5  92/05/06  09:03:18  Shashi_Mangalat
 * 	Merged in Silver BL6_4.
 * 	Removed nested comment that broke OSFPGMR scp.
 * 	  [92/04/24  08:06:53  William_Burns]
 * 	[92/05/06  08:55:09  Shashi_Mangalat]
 * 
 * Revision 4.4.3.4  92/04/15  14:08:49  Shashi_Mangalat
 * 	Merged in Silver BL6.
 * 	Reserve (optional) screend ioctls. Defined in net/gw_screen.h.
 * 	  [Heather_Gray]
 * 	Removed invalid copyright token.  [William_Burns]
 * 	Added TIOCGSID.  [Peter_Lega]
 * 	[92/04/15  13:18:04  Shashi_Mangalat]
 * 
 * Revision 4.4.3.3  92/03/18  22:25:07  Shashi_Mangalat
 * 	Merged in Silver BL5
 * 	Added the SVR4 pty ioctl - ISPTM [ Ron Menner]
 * 	Added BINLOG_xxxx ioctl's [ Scott_Cranston]
 * 	[92/03/18  22:10:33  Shashi_Mangalat]
 * 
 * Revision 4.4.3.2  92/01/28  18:38:13  Shashi_Mangalat
 * 	Merged in Silver BL3
 * 	[91/12/05  11:52:12  William_Burns]
 * 
 * Revision 4.4  92/01/15  02:11:06  devbld_gsf
 * 	Baselevel alpha_bl002
 * 
 * Revision 4.3.2.3  92/01/02  11:21:18  Anton_Verhulst
 * 	Changed data types of xxxxPGRP ioctls from int to pid_t.
 * 	[92/01/02  11:20:46  Anton_Verhulst]
 * 
 * Revision 4.3.3.2  92/01/02  11:20:46  Anton_Verhulst
 * 	Changed data types of xxxxPGRP ioctls from int to pid_t.
 * 
 * Revision 4.3.2.2  91/12/07  16:50:58  Jay_Estabrook
 * 	merge ALPHA with SILVER via ODE
 * 	[91/12/07  16:26:41  Jay_Estabrook]
 * 
 * Revision 4.3.1.2  91/12/07  16:26:41  Jay_Estabrook
 * 	merge ALPHA with SILVER via ODE
 * 
 * Revision 4.3  91/11/26  11:12:58  devbld_zk3
 * 	Baselevel AG_BL0
 * 
 * Revision 4.2.2.2  91/11/05  10:35:51  William_Burns
 * 	Merge from ODE/TIN: revision 3.9.9.2
 * 	date: 91/10/24 16:15:43;  author: devrcs;  state: Exp;  lines added/del: 1/5
 * 	sccs rev: 3.11;  orig date: 91/10/10 10:21:49;  orig author: larz
 * 	1. remove definition of TERMIODISC - this disipline is not
 * 	used by OSF and its definition does not belong in <sys/ioctl.h>.
 * 	[91/10/28  10:39:34  William_Burns]
 * 
 * Revision 4.2.1.2  91/10/28  10:39:34  William_Burns
 * 	Merge from ODE/TIN: revision 3.9.9.2
 * 	date: 91/10/24 16:15:43;  author: devrcs;  state: Exp;  lines added/del: 1/5
 * 	sccs rev: 3.11;  orig date: 91/10/10 10:21:49;  orig author: larz
 * 	1. remove definition of TERMIODISC - this disipline is not
 * 	used by OSF and its definition does not belong in <sys/ioctl.h>.
 * 
 * Revision 3.9.9.2  91/10/24  16:15:43  devrcs
 * 	sccs rev: 3.11;  orig date: 91/10/10 10:21:49;  orig author: larz
 * 	1. remove definition of TERMIODISC - this disipline is not
 * 	used by OSF and its definition does not belong in <sys/ioctl.h>.
 * 
 * 	Old revision info
 * 	Revision 1.11  90/10/07  14:50:58  devrcs
 * 	changed USE_OLD_TTY to _USE_OLD_TTY, USE_NEW_TTY to _USE_NEW_TTY
 * 	[90/10/04  09:38:58  rabin]
 * 
 * 	Added EndLog Marker.
 * 	[90/09/28  11:40:16  gm]
 * 
 * Revision 1.10  90/08/09  13:28:40  devrcs
 * 	Delete CMU ttyloc, vcons, rpause ioctl's.
 * 	Update to BSD Reno (pty EXT, SIG).
 * 	Add multicast add/delete.
 * 	[90/08/01  14:49:02  tmt]
 * 
 * 	Add KJI line discipline.
 * 	[90/07/26  14:03:41  morris]
 * 
 * Revision 1.9  90/07/17  11:42:07  devrcs
 * 	Add new security STREAMS ioctls.
 * 	[90/07/10  22:01:10  seiden]
 * 
 * Revision 1.8  90/06/29  13:53:49  devrcs
 * 	Add new STREAMS ioctls.
 * 	[90/06/26  12:19:19  brezak]
 * 
 * Revision 1.7  90/06/22  20:53:02  devrcs
 * 	Added SVID ioctls for tty.
 * 	[90/06/14  23:01:50  havens]
 * 
 * 	Removed the JUNK_* ioctls and added the SVID ioctls.
 * 	[90/06/13  12:50:41  havens]
 * 
 * 	Changes from SecureWare for least privilege, MAC, DAC, auditing, etc.
 * 	[90/06/09  18:46:01  seiden]
 * 
 * 	Posix tty support.
 * 	[90/02/06  12:07:49  morris]
 * 
 * Revision 1.6  90/05/13  20:33:35  devrcs
 * 	Changes for gcc for osc.10
 * 	[90/05/02  19:42:59  brezak]
 * 
 * 	Changes for gcc
 * 	[90/05/01  21:49:35  brezak]
 * 
 * Revision 1.5  90/04/27  19:25:50  devrcs
 * 	Add ioctl's for SLIP, modify some SIOC ioctl's to follow
 * 	compat for bsd4.4-format sockaddr's, also see socket.h.
 * 	Removed #ifdef mips socket ioctl's - not supported.
 * 	Cleaned up #ifdef's: _KERNEL, commented #endif tags.
 * 	[90/04/19  16:35:13  tmt]
 * 
 * Revision 1.4  90/03/13  20:49:21  mbrown
 * 	duplicates with sys/termio.h...added ifdef kernel to play safe.
 * 	[90/02/25  14:46:55  mbrown]
 * 
 * Revision 1.3  90/02/16  16:52:14  devrcs
 * 	Fixed FSPARAM and NOSPC ioctls.
 * 	[90/02/16  00:14:30  ers]
 * 
 * 	Do not define USE_OLD_TTY if KERNEL.
 * 	[90/02/15  15:33:59  ers]
 * 
 * 	Define USE_OLD_TTY unless USE_NEW_TTY.
 * 	[90/02/15  14:41:19  ers]
 * 
 * 	Merged Robert Coren's and Rich Morris's changes
 * 	[90/02/15  14:04:34  ers]
 * 
 * Revision 1.2  90/01/02  20:15:56  gm
 * 	Fixes for first snapshot.
 * 
 * Revision 1.1  89/10/16  19:48:15  gm
 * 	Mach 2.5 and Encore 0.6 merge
 * 
 * Revision 6.1  89/07/26  14:18:01  alan
 * 	Mach Release 2.5 (preliminary) merged with Encore Multimax
 * 	support and BSD parallelization changes.
 * 
 * Revision 2.15  89/07/12  01:27:56  jjc
 * 	Defined NTABLDISC for Sun.
 * 	[89/07/05  21:14:36  jjc]
 * 
 * Revision 2.14  89/05/03  14:58:31  mikeg
 * 	Defined TIOCGSIZE and TIOCSSIZE to be TIOCGWINSZ and
 * 	TIOCSWINSZ respectively and made other modifications
 * 	to the TIOC[GS]SIZE family of ioctl's so that both X
 * 	and Suntools will run correctly on Sun's.
 * 	[89/04/12  12:08:28  mikeg]
 * 
 * Revision 2.13  89/03/09  22:05:08  rpd
 * 	More cleanup.
 * 
 * Revision 2.12  89/02/25  17:54:17  gm0w
 * 	Made all code that depended on CMUCS unconditional
 * 	except for ttyloc stuff.
 * 	[89/02/14            mrt]
 * 
 * Revision 2.11  89/01/23  22:26:42  af
 * 	Added a bunch of Mips-specific ioctls.
 * 	[89/01/04            af]
 * 
 * Revision 2.10  88/12/13  13:19:29  mikeg
 * 	Enclosed new Sun specific ioctl's I added previously
 * 	in "#ifdef sun" conditional.
 * 
 * Revision 2.9  88/12/08  15:36:01  mikeg
 * 	Added the Sun ioctl's TIOCSSIZE, _O_TIOCSSIZE,
 * 	_N_TIOCSSIZE, TIOCGSIZE, _O_TIOCGSIZE, and _N_TIOCGSIZE
 * 	to allow Suntools to run on Mach.
 * 	[88/11/30  12:16:14  mikeg]
 * 
 * Revision 2.7  88/11/14  14:34:08  gm0w
 * 	Added CSNET DialupIP support.
 * 	[88/11/14            gm0w]
 * 
 * Revision 2.6  88/09/27  17:31:58  rvb
 * 	Fixed Log
 * 
 * Revision 2.5  88/09/27  16:08:19  rvb
 * 	QIOCCIFNCTRS: Clear interface counters.
 * 	[88/09/23            rvb]
 * 
 * Revision 2.4  88/08/24  02:29:23  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:13:38  mwyoung]
 * 
 * Revision 2.3  88/08/22  21:29:21  mja
 * 	Flush obsolete SIOCBROAD definition.
 * 	[88/08/09  09:54:45  mja]
 * 
 * 	Delete obsolete TIOCSCONS definition;  add TIOCVCONS and
 * 	TIOCGCONS definitions;  coalesce CMUCS conditionsals.
 * 	[88/08/04  17:59:21  mja]
 * 
 * Revision 0.0  87/11/10            mja
 * 	Fix to conditionalize all local exported names on only CMU or
 * 	CMUCS and retain special purpose kernel conditionals as
 * 	comments only; define TIOCCONS on all architectures.
 * 	[ V5.1(XF21) ]
 * 	[87/11/10            mja]
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: ioctl.h,v $ $Revision: 4.4.115.1 $ (DEC) $Date: 2003/09/23 22:01:03 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
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
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)ioctl.h	7.12 (Berkeley) 5/18/90
 */


/*
 * Ioctl definitions
 */

#ifndef	_SYS_IOCTL_H_
#define _SYS_IOCTL_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#if !defined(_XOPEN_SOURCE_EXTENDED) || defined(_OSF_SOURCE)
#include <sys/secdefines.h>
#endif

/*
 * Function prototype for the ioctl system call.
 */
#ifndef _KERNEL
extern int 	ioctl __((int, int, ...));
#endif /* _KERNEL */

#if !defined(_XOPEN_SOURCE_EXTENDED) || defined(_OSF_SOURCE)
/*
 * Window/terminal size structure.
 * This information is stored by the kernel
 * in order to provide a consistent interface,
 * but is not used by the kernel.
 */
struct winsize {
	unsigned short	ws_row;			/* rows, in characters */
	unsigned short	ws_col;			/* columns, in characters */
	unsigned short	ws_xpixel;		/* horizontal size, pixels */
	unsigned short	ws_ypixel;		/* vertical size, pixels */
};

/*
 * Pun for SUN.
 */
struct ttysize {
	unsigned short	ts_lines;
	unsigned short	ts_cols;
	unsigned short	ts_xxx;
	unsigned short	ts_yyy;
};
#define	TIOCGSIZE	TIOCGWINSZ
#define	TIOCSSIZE	TIOCSWINSZ
#endif

#if	defined(_KERNEL) && defined(sun)
/*
 * The following structure and ioctl's have been added to allow
 * Suntools to run under Mach.
 */

/*
 * Sun version of the winsize struct.
 */
struct swsize {
	int	ts_lines;	/* number of lines on terminal */
	int	ts_cols;	/* number of columns on terminal */
};

/*
 * These ioctl's are used in Suntools.  Although they may seem to conflict
 * with existing 4.3 ioctl's, either the resulting value is different
 * from the other ioctl with the same number or there is code in the
 * appropriate driver to distinguish between them.
 */
#define	_O_TIOCSSIZE	_IOW('t',103,struct swsize)	/* set tty size */
#define	_O_TIOCGSIZE	_IOR('t',102,struct swsize)	/* get tty size */
#define	_N_TIOCSSIZE	_IOW('t',37,struct swsize)	/* set tty size */
#define	_N_TIOCGSIZE	_IOR('t',38,struct swsize)	/* get tty size */

#endif	/* _KERNEL && sun */

#ifndef _IO
#if !defined(_XOPEN_SOURCE_EXTENDED) || defined(_OSF_SOURCE)
/*
 * Ioctl's have the command encoded in the lower word,
 * and the size of any in or out parameters in the upper
 * word.  The high 3 bits of the upper word are used
 * to encode the in/out status of the parameter.
 */
#define	IOCPARM_MASK	0x1fff		/* parameter length, at most 13 bits */
#define	IOCPARM_LEN(x)	(((x) >> 16) & IOCPARM_MASK)
#define	IOCBASECMD(x)	((x) & ~IOCPARM_MASK)
#define	IOCGROUP(x)	(((x) >> 8) & 0xff)

#define	IOCPARM_MAX	NBPG		/* max size of ioctl, mult. of NBPG */

#define IOC_VOID	0x20000000	/* no parameters */
#define IOC_OUT		0x40000000	/* copy out parameters */
#define IOC_IN		0x80000000	/* copy in parameters */
#define IOC_INOUT	(IOC_IN|IOC_OUT)
#define	IOC_DIRMASK	0xe0000000	/* mask for IN/OUT/VOID */

#else
#define _IOCPARM_MASK	0x1fff	/* parameter length, at most 13 bits */
#endif /* !_XOPEN_SOURCE_EXTENDED || _OSF_SOURCE */

#define _IOC_VOID	0x20000000	/* no parameters */
#define _IOC_OUT		0x40000000	/* copy out parameters */
#define _IOC_IN		0x80000000	/* copy in parameters */
#define _IOC_INOUT	(_IOC_IN|_IOC_OUT)
#define	_IOC_DIRMASK	0xe0000000	/* mask for IN/OUT/VOID */

#if !defined(_XOPEN_SOURCE_EXTENDED) || defined(_OSF_SOURCE)
#define _IOC(inout,group,num,len) \
	(inout | ((len & IOCPARM_MASK) << 16) | ((group) << 8) | (num))
#define	_IO(g,n)	_IOC(IOC_VOID,	(g), (n), 0)
#define	_IOR(g,n,t)	_IOC(IOC_OUT,	(g), (n), sizeof(t))
#define	_IOW(g,n,t)	_IOC(IOC_IN,	(g), (n), sizeof(t))

/* this should be _IORW, but stdio got there first */
#define	_IOWR(g,n,t)	_IOC(IOC_INOUT,	(g), (n), sizeof(t))
#else
#define _IOC(inout,group,num,len) \
	(inout | ((len & _IOCPARM_MASK) << 16) | ((group) << 8) | (num))
#define	_IO(g,n)	_IOC(_IOC_VOID,	(g), (n), 0)
#define	_IOR(g,n,t)	_IOC(_IOC_OUT,	(g), (n), sizeof(t))
#define	_IOW(g,n,t)	_IOC(_IOC_IN,	(g), (n), sizeof(t))

/* this should be _IORW, but stdio got there first */
#define	_IOWR(g,n,t)	_IOC(_IOC_INOUT, (g), (n), sizeof(t))
#endif

#endif /* !_IO */

#if !defined(_XOPEN_SOURCE_EXTENDED) || defined(_OSF_SOURCE)
/*
 * tty ioctl commands
 */
						/* 0-2 compat */
#define	TIOCMODG	_IOR('t', 3, int)	/* get modem control state */
#define	TIOCMODS	_IOW('t', 4, int)	/* set modem control state */
#define		TIOCM_LE	0001		/* line enable */
#define		TIOCM_DTR	0002		/* data terminal ready */
#define		TIOCM_RTS	0004		/* request to send */
#define		TIOCM_ST	0010		/* secondary transmit */
#define		TIOCM_SR	0020		/* secondary receive */
#define		TIOCM_CTS	0040		/* clear to send */
#define		TIOCM_CAR	0100		/* carrier detect */
#define		TIOCM_CD	TIOCM_CAR
#define		TIOCM_RNG	0200		/* ring */
#define		TIOCM_RI	TIOCM_RNG
#define		TIOCM_DSR	0400		/* data set ready */
						/* 8-10 compat */
#define	TIOCEXCL	_IO('t', 13)		/* set exclusive use of tty */
#define	TIOCNXCL	_IO('t', 14)		/* reset exclusive use of tty */
						/* 15 unused */
#define	TIOCFLUSH	_IOW('t', 16, int)	/* flush buffers */
						/* 17-18 compat */
#define	TIOCGETA	_IOR('t', 19, struct termios) /* get termios struct */
#define	TIOCSETA	_IOW('t', 20, struct termios) /* set termios struct */
#define	TIOCSETAW	_IOW('t', 21, struct termios) /* drain output, set */
#define	TIOCSETAF	_IOW('t', 22, struct termios) /* drn out, fls in, set */
/* System V tty ioctls */

#define TCGETS          TIOCGETA
#define TCSETS          TIOCSETA
#define TCSETSW         TIOCSETAW
#define TCSETSF         TIOCSETAF
#define TCGETA	        _IOR('t', 23, struct termio) /* get termio struct */
#define TCSETA	        _IOW('t', 24, struct termio) /* set termio struct */
#define TCSETAW	        _IOW('t', 25, struct termio) /* drain output, set */
#define TCSETAF	        _IOW('t', 28, struct termio) /* drn out, flsh, set */
#define TCSBREAK        _IO('t', 29)		/* Send break */
#define TCSBRK          TCSBREAK
#define TCXONC          _IO('t', 30)		/* Set flow control */
#define TCFLSH          _IO('t', 31)		/* Flush queue */

#define	TIOCGETD	_IOR('t', 26, int)	/* get line discipline */
#define	TIOCSETD	_IOW('t', 27, int)	/* set line discipline */


/* locals, from 127 down */
						/* 127-124 compat */
#define	TIOCSBRK	_IO('t', 123)		/* set break bit */
#define	TIOCCBRK	_IO('t', 122)		/* clear break bit */
#define	TIOCSDTR	_IO('t', 121)		/* set data terminal ready */
#define	TIOCCDTR	_IO('t', 120)		/* clear data terminal ready */
#define	TIOCGPGRP	_IOR('t', 119, pid_t)	/* get pgrp of tty */
#define	TIOCSPGRP	_IOW('t', 118, pid_t)	/* set pgrp of tty */
						/* 117-116 compat */
#define	TIOCOUTQ	_IOR('t', 115, int)	/* output queue size */
#define	TIOCSTI		_IOW('t', 114, char)	/* simulate terminal input */
#define	TIOCNOTTY	_IO('t', 113)		/* void tty association */
#define	TIOCPKT		_IOW('t', 112, int)	/* pty: set/clear packet mode */
#define		TIOCPKT_DATA		0x00	/* data packet */
#define		TIOCPKT_FLUSHREAD	0x01	/* flush packet */
#define		TIOCPKT_FLUSHWRITE	0x02	/* flush packet */
#define		TIOCPKT_STOP		0x04	/* stop output */
#define		TIOCPKT_START		0x08	/* start output */
#define		TIOCPKT_NOSTOP		0x10	/* no more ^S, ^Q */
#define		TIOCPKT_DOSTOP		0x20	/* now do ^S ^Q */

#define	TIOCSTOP	_IO('t', 111)		/* stop output, like ^S */
#define	TIOCSTART	_IO('t', 110)		/* start output, like ^Q */
#define	TIOCMSET	_IOW('t', 109, int)	/* set all modem bits */
#define	TIOCMBIS	_IOW('t', 108, int)	/* bis modem bits */
#define	TIOCMBIC	_IOW('t', 107, int)	/* bic modem bits */
#define	TIOCMGET	_IOR('t', 106, int)	/* get all modem bits */
#define	TIOCREMOTE	_IOW('t', 105, int)	/* remote input editing */
#define	TIOCGWINSZ	_IOR('t', 104, struct winsize)	/* get window size */
#define	TIOCSWINSZ	_IOW('t', 103, struct winsize)	/* set window size */
#define	TIOCUCNTL	_IOW('t', 102, int)	/* pty: set/clr usr cntl mode */
#define		UIOCCMD(n)	_IO('u', n)		/* usr cntl op "n" */
#define	TIOCCONS	_IOW('t', 98, int)		/* become virtual console */
#define	TIOCSCTTY	_IO('t', 97)		/* become controlling tty */
#define TIOCEXT		_IOW('t', 96, int)	/* pty: external processing */
#define TIOCSIG		_IO('t', 95)		/* pty: generate signal */
#define TIOCISATTY	_IO('t', 94)		/* is this a tty? */

/* SLIP (Serial Line IP) ioctl's */
#define	SLIOGUNIT	_IOR('t', 88, int)	/* get slip unit number */
#define	SLIOCSFLAGS	_IOW('t', 89, int)	/* set configuration flags */
#define	SLIOCGFLAGS	_IOR('t', 90, int)	/* get configuration flags */

#define TTYDISC		0		/* termios tty line discipline */
#define TABLDISC	3		/* tablet discipline */
#define SLIPDISC	4		/* serial IP discipline */
#ifdef	sun
#define MOUSELDISC      5               /* mouse discipline */
#define KBDLDISC        6               /* up/down keyboard trans (console) */
#define NTABLDISC	7		/* gtco tablet discipline */
#endif
#define DUDISC		7		/* Dialup IP discipline */
#define KJIDISC         8               /* Kanji Shift JIS discipline */
#define ASYDISC         9               /* Asian multibyte line discipline */
#define TSBDISC         10              /* I18N single-byte line discipline */
#define KDBDISC         11              /* debug filter line discipline */

/*
 * Macros for determining Asian/I18N line disciplines
 */
#define IS_ASY_LINE(tp) ((tp)->t_line == ASYDISC)
#define IS_TSB_LINE(tp) ((tp)->t_line == TSBDISC)

/* SYS V REL. 4 PTY IOCTL    */
#define ISPTM           _IO('t',71)     	/* get dev_t  */
#define UNLKPT          _IO('t',73)             /* unlock slave pty */
#define ISPTS           _IO('t',74)             /* ret. maj+min of pty master */

#define	TIOCGSID	_IOR('t', 72, int)	/* get sid of tty */

/*
 * Compatability with old terminal driver
 *
 * Source level -> #define _USE_OLD_TTY
 * Kernel level -> options COMPAT_43
 */
#if	!defined(_KERNEL) && !defined(_USE_OLD_TTY) && !defined(_USE_NEW_TTY)
#define _USE_OLD_TTY 1
#endif

#if (defined(_USE_OLD_TTY) || defined(COMPAT_43)) && (!defined (_XOPEN_SOURCE_EXTENDED) || defined(_OSF_SOURCE))
#include <sys/ioctl_compat.h>
#endif

#define	FIOCLEX		_IO('f', 1)		/* set close on exec on fd */
#define	FIONCLEX	_IO('f', 2)		/* remove close on exec */
#define	FIONREAD	_IOR('f', 127, int)	/* get number of bytes to read */
#define	FIONBIO		_IOW('f', 126, int)	/* set/clear non-blocking i/o */
#define	FIOASYNC	_IOW('f', 125, int)	/* set/clear async i/o */
#define	FIOSETOWN	_IOW('f', 124, int)	/* set owner */
#define	FIOGETOWN	_IOR('f', 123, int)	/* get owner */
#define FIOPIPESTAT     _IOR('f', 122, struct stat)     /* pipe|fifo stat */
#define FIOFATTACH      _IOW('f', 121, void *)  /* internal: fattach */
#define FIOFDETACH      _IOW('f', 120, void *)  /* internal: fdetach */


/* socket i/o controls */
#define	SIOCCHILDNBIO	_IOW('s', 94, int)	/* set/clear the inherit nbio flag */
#define	SIOCWIRE	_IOW('s', 95, int)	/* set/clear the wire all pages(send only) */


#define	SIOCSHIWAT	_IOW('s',  0, int)		/* set high watermark */
#define	SIOCGHIWAT	_IOR('s',  1, int)		/* get high watermark */
#define	SIOCSLOWAT	_IOW('s',  2, int)		/* set low watermark */
#define	SIOCGLOWAT	_IOR('s',  3, int)		/* get low watermark */
#define	SIOCATMARK	_IOR('s',  7, int)		/* at oob mark? */
#define	SIOCSPGRP	_IOW('s',  8, pid_t)		/* set process group */
#define	SIOCGPGRP	_IOR('s',  9, pid_t)		/* get process group */
#if SEC_ARCH
#define	SIOCGPEERPRIV	_IOR('s', 10, int)		/* get peer privs */
#endif

#define	SIOCADDRT	_IOW('r', 10, struct ortentry)	/* add route */
#define	SIOCDELRT	_IOW('r', 11, struct ortentry)	/* delete route */

#define	SIOCSIFADDR	_IOW('i', 12, struct ifreq)	/* set ifnet address */
#define	SIOCSIFDSTADDR	_IOW('i', 14, struct ifreq)	/* set p-p address */
#define	SIOCSIFFLAGS	_IOW('i', 16, struct ifreq)	/* set ifnet flags */
#define	SIOCGIFFLAGS	_IOWR('i',17, struct ifreq)	/* get ifnet flags */
#define	SIOCSIFBRDADDR	_IOW('i', 19, struct ifreq)	/* set broadcast addr */
#define	SIOCSIFNETMASK	_IOW('i', 22, struct ifreq)	/* set net addr mask */
#define	SIOCGIFMETRIC	_IOWR('i',23, struct ifreq)	/* get IF metric */
#define	SIOCSIFMETRIC	_IOW('i', 24, struct ifreq)	/* set IF metric */
#define	SIOCDIFADDR	_IOW('i', 25, struct ifreq)	/* delete IF addr */
#define	SIOCAIFADDR	_IOW('i', 26, struct ifaliasreq)/* add/chg IF alias */
#define SIOCRDZCTRS	_IOWR('i', 27, struct ctrreq)	/* Read counter */
#define SIOCRDCTRS	_IOWR('i', 28, struct ctrreq)	/* Read counter */
#define SIOCPIFADDR     _IOW('i', 29, struct ifaliasreq)/* set primary addr */
#define	SIOCSARP	_IOW('i', 30, struct arpreq)	/* set arp entry */
#define	SIOCDARP	_IOW('i', 32, struct arpreq)	/* delete arp entry */
#define OSIOCARPREQ	_IOWR('i', 40, struct ifreq)	/* old arp request pkt*/
#define SIOCARPREQ	_IOWR('i', 40, struct arpreq)	/* arp request pkt */
#define OSIOCAARPREQ	_IOWR('i', 41, struct ifreq)	/* old alias arp request pkt */
#define SIOCAARPREQ	_IOWR('i', 41, struct arpreq)	/* alias arp request pkt */
#define OSIOCGARPREQ	_IOWR('i', 42, struct ifreq)	/* old gratuitous arp request pkt */
#define SIOCGARPREQ	_IOWR('i', 42, struct arpreq)	/* gratuitous arp request pkt */
#define	SIOCDISARPREQ	_IOWR('i', 43, struct arpreq)	/* disable arp req */
#define	SIOCENAARPREQ	_IOWR('i', 44, struct arpreq)	/* enable arp req */
#define SIOCMANREQ      _IOWR('i',45, struct ifdata)    /* mgmt request */ 
#define SIOCGETEVENTS   _IOWR('i',46, struct ifdata)    /* event notif */
#define SIOCIFRESET     _IOW('i',47, struct ifreq)      /* Reset interface */
#define SIOCEEUPDATE    _IOW('i',48, struct ifeeprom)   /* Write EEPROM */

#define SIOCADDMULTI	_IOW('i', 49, struct ifreq)	/* add m'cast addr */
#define SIOCDELMULTI	_IOW('i', 50, struct ifreq)	/* del m'cast addr */

/* #define SIOCSCREENON _IOWR('i', 51, int)      screend, net/gw_screen.h */
/* #define SIOCSCREEN   _IOWR('i', 52, struct screen_data)     screend */
/* #define SIOCSCREENSTATS _IOR('i', 53, struct screen_stats)  screend */

#define SIOCGETVIFCNT _IOWR('r', 54, struct sioc_vif_req)/* get vif pkt cnt */
#define SIOCGETSGCNT  _IOWR('r', 55, struct sioc_sg_req) /* get s,g pkt cnt */

#if SEC_NET
#define SIOCGIFNET	 _IOWR('i', 56, struct ifreq)	/* get ifnet struct */
#define SIOCSIFNET	 _IOW('i', 57, struct ifreq)    /* set ifnet struct */
#endif

/* Set/get interface access filter */
#define	SIOCSIFAFILT    _IOW('i', 58, struct ifafiltreq)/* set filter */
#define	SIOCGIFAFILT    _IOWR('i', 59, struct ifafiltreq)/* get filter */

/* Added by choosing arbitrary numbers */
#define SIOCENABLBACK	_IOW('i', 60, struct ifreq)	/* Enable loopback */
#define SIOCDISABLBACK	_IOW('i', 61, struct ifreq)	/* Disable loopback */
#define SIOCRPHYSADDR	_IOWR('i', 62, struct ifdevea)	/* Read Phys addr */
#define SIOCSPHYSADDR	_IOWR('i', 63, struct ifdevea)	/* Set addr */
#define SIOCIFSETCHAR	_IOWR('i', 64, struct ifchar)	/* Set characteristic */
#define SIOCSMACSPEED	_IOW('i', 65, struct ifreq)	/* Set MAC speed */
#define SIOCRMACSPEED	_IOWR('i', 66, struct ifreq)	/* Read MAC speed */
#define SIOCSIPMTU	_IOW('i', 67, struct ifreq)	/* Set intf. IP MTU */
#define SIOCRIPMTU	_IOWR('i', 68, struct ifreq)	/* Read intf. IP MTU */

#define SIOCGIFINDEX	_IOWR('i', 69, struct ifreq)	/* get IF index */

/* Source Routing ioctl */
#define SIOCSRREQR	_IOWR('i', 70, struct srreq)	/* SR read request */
#define SIOCSRREQW	_IOWR('i', 71, struct srreq)	/* SR write request */

/* Network Redundant Adapters (NetRAIN) */
#define SIOCIFADD       _IOWR('i', 72, struct if_nrset) /* Attach adapter  */
#define SIOCIFSWITCH    _IOWR('i', 73, struct ifreq)    /* Switch adapters */
#define SIOCIFREMOVE    _IOWR('i', 74, struct ifreq)    /* Remove adapter */
#define SIOCIFNRTIMERS	_IOWR('i', 75, mif_t)    	/* modify timers for NIFF */
#define SIOCGNRSET      _IOWR('i', 76, struct if_nrset) /* Get list of netrain members */
#define SIOCIFAUTOFAIL  _IOWR('i', 77, struct ifreq)    /* Enable auto failover mode */

/* Set/get interface trustgrp for FIREWALL product */
#define	SIOCSIFTRUSTGRP	_IOW('i', 85, struct ifreq)	/* Set if_trustgrp */
#define	SIOCGIFTRUSTGRP	_IOWR('i', 85, struct ifreq)	/* Get if_trustgrp */

/*
 * IPv6 ioctls
 * See netinet/in6.h for struct defn of ip6ifreq
 */
#define SIOCIPV6ADDHOMEPREFIX _IOWR('i',244, struct ip6ifreq)/* MIPv6 - Add Home Prefix */
#define SIOCIPV6REMHOMEPREFIX _IOWR('i',245, struct ip6ifreq)/* MIPv6 - Remove Home Prefix */
#define SIOCIPV6GIFADDR	 _IOWR('i', 246, struct ip6ifreq)    /* get IPv6 
							      * addr opts */
#define SIOCIPV6ADDROUT  _IOWR('i', 247, struct ip6ifreq)    /* add LLADDR */
#define SIOCIPV6DELGATE  _IOWR('i', 248, struct ip6ifreq)    /* flush routes 
							      * through gate 
							      */
#define SIOCIPV6IFUNINIT _IOWR('i', 249, struct ip6ifreq)    /* uninit IPv6 */
#define SIOCIPV6IFINIT	 _IOWR('i', 250, struct ip6ifreq)    /* init if IPv6 */
#define SIOCIPV6AIFADDR	 _IOWR('i', 251, struct ip6ifreq)    /* add if IPv6 */
#define SIOCIPV6SIFATTR	 _IOW ('i', 252, struct ip6ifreq)    /* set IPv6 if 
							      * attributes */
#define SIOCIPV6DIFADDR	 _IOWR ('i', 253, struct ip6ifreq)    /* del if IPv6 
							      * global addr */
#define SIOCIPV6GIFATTR	 _IOWR('i', 254, struct ip6ifreq)    /* get IPv6 if attributes */
#define SIOCIPV6MIFADDR	 _IOWR('i', 255, struct ip6ifreq)    /* mdfy IPv6 addr opts */


/*
 * IP traffic control (Integrated Services) ioctls
 * See netinet/ip_tcntl.h for definition of structs below.
 */
#define SIOCFLOWSPEC	_IOWR('i', 86, struct flowreq)	/* flowspec request */
#define SIOCFILTSPEC	_IOWR('i', 87, struct filtreq)	/* filtspec request */
#define SIOCGADSPEC	_IOWR('i', 88, struct adspecreq) /* get adspec */
#define SIOCGHASHINFO   _IOWR('i', 89, struct hashreq)  /* hash info */
#define SIOCTCNTLCONF   _IOWR('i', 90, struct tcntlconfreq) /* tcntl config */


/*
 * These ioctls help RSVP get routing information.
 * See net/route.h and netinet/ip_mroute.h for definition of structs below
 */
#define SIOCGROUTE	_IOWR('r', 91, struct rtgetreq)	/* get routing info */
#define	SIOCGVIFCONF	_IOWR('r', 92, struct vifconf)	/* get vif list */

#define SIOCGMEDIAMTU	_IOWR('i', 93, struct ifreq)	/* get media mtu */
#define SIOCGIFTYPE	_IOWR('i', 94, struct ifreq)	/* get interface type */

/*
 * Some additional Traffic Control functions
 */
#define SIOCGLISTSPECFLOW _IOWR('i', 95, struct listflowreq) /* Flow info */
#define SIOCGLISTSPECFILT _IOWR('i', 96, struct listfiltreq) /* Filter info */

/*
 * #'s 97-99 are available for use
 */

/* Traffic Monitor Thread (TMT) */
#define SIOCTMTADD	_IOWR('i', 100, struct monitored_interface)
#define SIOCTMTREMOVE	_IOWR('i', 101, struct monitored_interface)
#define SIOCTMTMODIFY	_IOWR('i', 102, struct monitored_interface)
#define SIOCTMTHOWMANY	_IOWR('i', 103, int)
#define SIOCTMTSTATUS	_IOWR('i', 104, struct monitored_interface)
#define SIOCTMTDUMP	_IOWR('i', 105, caddr_t)
#define SIOCTMTWALK	_IO('i', 106)
#define SIOCTMTSTATEMODIFY _IOWR('i', 107, struct monitored_interface)

#if	defined(_SOCKADDR_LEN) || defined(_KERNEL)
/* BSD4.4 sockaddr format accepted and returned - also see sys/socket.h */
#define	OSIOCGIFADDR	_IOWR('i',13, struct ifreq)	/* get ifnet address */
#define	SIOCGIFADDR	_IOWR('i',33, struct ifreq)	/* get ifnet address */
#define	OSIOCGIFDSTADDR	_IOWR('i',15, struct ifreq)	/* get p-p address */
#define	SIOCGIFDSTADDR	_IOWR('i',34, struct ifreq)	/* get p-p address */
#define	OSIOCGIFBRDADDR	_IOWR('i',18, struct ifreq)	/* get broadcast addr */
#define	SIOCGIFBRDADDR	_IOWR('i',35, struct ifreq)	/* get broadcast addr */
#define	OSIOCGIFCONF	_IOWR('i',20, struct ifconf)	/* get ifnet list */
#define	SIOCGIFCONF	_IOWR('i',36, struct ifconf)	/* get ifnet list */
#define	OSIOCGIFNETMASK	_IOWR('i',21, struct ifreq)	/* get net addr mask */
#define	SIOCGIFNETMASK	_IOWR('i',37, struct ifreq)	/* get net addr mask */
#define	OSIOCGARP	_IOWR('i',31, struct arpreq)	/* get arp entry */
#define	SIOCGARP	_IOWR('i',38, struct arpreq)	/* get arp entry */
#else
/* BSD4.3 sockaddr format */
#define	SIOCGIFADDR	_IOWR('i',13, struct ifreq)	/* get ifnet address */
#define	SIOCGIFDSTADDR	_IOWR('i',15, struct ifreq)	/* get p-p address */
#define	SIOCGIFBRDADDR	_IOWR('i',18, struct ifreq)	/* get broadcast addr */
#define	SIOCGIFCONF	_IOWR('i',20, struct ifconf)	/* get ifnet list */
#define	SIOCGIFNETMASK	_IOWR('i',21, struct ifreq)	/* get net addr mask */
#define	SIOCGARP	_IOWR('i',31, struct arpreq)	/* get arp entry */
#endif

/* TODO: added the MTIOC stuff from ULTRIX - does it really belong here */
/* Tape i/o controls */
#define MTIOCTOP	_IOW('m', 1, struct mtop) 	/* Do a tape op.*/
#define MTIOCGET	_IOR('m', 2, struct mtget)	/* Get status	*/
#define MTIOCRDPOS	_IOWR('m', 3, struct mtrdpos)	/* Read Position */

#endif /* !_XOPEN_SOURCE_EXTENDED || _OSF_SOURCE */

/*
 * STREAMS ioctl commands - group 'S'
 */
#define I_NREAD         _IO('S', 1) /* return the number of bytes in 1st msg */
#define I_PUSH          _IO('S', 2) /* push module just below stream head */
#define I_POP           _IO('S', 3) /* pop module below stream head */
#define I_LOOK          _IO('S', 4) /* retrieve name of first stream module */
#define I_FLUSH         _IO('S', 5) /* flush all input and/or output queues */
#define I_SRDOPT        _IO('S', 6) /* set the read mode */
#define I_GRDOPT        _IO('S', 7) /* get the current read mode */
#define I_STR           _IO('S', 8) /* create an internal ioctl message */
#define I_SETSIG        _IO('S', 9) /* request SIGPOLL signal on events */
#define I_GETSIG        _IO('S',10) /* query the registered events */
#define I_FIND          _IO('S',11) /* check for module in stream */
#define I_LINK          _IO('S',12) /* connect stream under mux fd */
#define I_UNLINK        _IO('S',13) /* disconnect two streams */
#define I_ISASTREAM     _IO('S',14) /* identifies as stream/pipe/fifo */
#define I_PEEK          _IO('S',15) /* peek at data on read queue */
#define I_FDINSERT      _IO('S',16) /* create a message and send downstream */
#define I_SENDFD        _IO('S',17) /* send an fd to a connected pipe stream */
#define I_RECVFD        _IO('S',18) /* retrieve a file descriptor */
#define I_FLUSHBAND     _IO('S',19) /* flush a particular input and/or output band */
#define I_SWROPT        _IO('S',20) /* set the write mode */
#define I_GWROPT        _IO('S',21) /* get the current write mode */
#define I_LIST          _IO('S',22) /* get a list of all modules on a stream */
#define I_ATMARK        _IO('S',23) /* is the next message is "marked"? */
#define I_CKBAND        _IO('S',24) /* check for a message of a particular band */
#define I_GETBAND       _IO('S',25) /* get the band of the next message */
#define I_CANPUT        _IO('S',26) /* check to see if a message may be passed on a stream */
#define I_SETCLTIME     _IO('S',27) /* set the close timeout wait */
#define I_GETCLTIME     _IO('S',28) /* get the current close timeout wait */
#define I_PLINK         _IO('S',29) /* persistently connect a stream under a mux */
#define I_PUNLINK       _IO('S',30) /* disconnect a persistent link */
/* 31-39 available */
#define I_GETMSG        _IO('S',40) /* getmsg() system call */
#define I_PUTMSG        _IO('S',41) /* putmsg() system call */
#define I_GETPMSG       _IO('S',42) /* getpmsg() system call */
#define I_PUTPMSG       _IO('S',43) /* putpmsg() system call */
#define I_PIPE          _IO('S',44) /* connect two streams as a pipe */
#define I_FIFO          _IO('S',45) /* convert a stream into a FIFO */
#define I_FATTACH       _IO('S',46) /* check if fattached file */
#if SEC_BASE
#define I_STR_ATTR      _IO('S',60)
#define I_PEEK_ATTR     _IO('S',61)
#define I_FDINSERT_ATTR _IO('S',62)
#define I_SENDFD_ATTR   _IO('S',63)
#define I_RECVFD_ATTR   _IO('S',64)
#define I_GETMSG_ATTR   _IO('S',65)
#define I_PUTMSG_ATTR   _IO('S',66)
#endif  /* SEC_BASE */

#if !defined(_XOPEN_SOURCE_EXTENDED) || defined(_OSF_SOURCE)
/* binary event logger - group B */
#define BINLOG_ENABLE           _IO('B', 1)
#define BINLOG_DISABLE          _IO('B', 2)
#define BINLOG_ASCIIENABLE      _IO('B', 3)
#define BINLOG_ASCIIDISABLE     _IO('B', 4)
#define BINLOG_CLRCNTRS         _IO('B', 5)
#define BINLOG_SETPID           _IOW('B', 6, long)
#define BINLOG_GETSTATUS        _IOR('B', 20, struct binlog_getstatus)
#endif

/*
 * File system Ioctl's.
 */
#if !defined(_XOPEN_SOURCE_EXTENDED) || defined(_OSF_SOURCE)
#define GETCACHEPOLICY _IOR('F', 00, int)	/* Get caching policy */
#define SETCACHEPOLICY _IOW('F', 01, int)	/* Set caching policy */
#define CS_CACHE     FCACHE			/* Cache file data */
#define CS_DIRECTIO  FDIRECTIO			/* Do not cache file data */

#define GETMAP	       _IOR('F', 02, int)	/* Get file's extent map */
#endif

/*
 * audit ioctl commands - group 'C' -- just here to reserve group 'C'.
 * 	See <sys/audit.h> for command definitions.
 */

/*
 * Asynchronous Transfer Mode (ATM) ioctl commands - group 'G' (gigabit
 * 	networking).  Here to reserve group 'G'.
 *	See <sys/atm.h> for command definitions.
 */

#ifdef __cplusplus
}
#endif
#endif	/* _SYS_IOCTL_H_ */
