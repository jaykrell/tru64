/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: audit.h,v $
 * Revision 4.2.70.3  2005/04/25  18:43:02  Larry_Scott
 * 	Add #define AUD_ASSERT (qar 462)
 *
 * Revision 4.2.70.2  2004/09/02  17:34:02  Larry_Scott
 * 	Rework data buffering.  Add support for auditing from non-block'able
 * 	codepaths.  Cleanup.  (qar 97389, GB_G08739)
 *
 * Revision 4.2.70.1  2002/10/15  20:00:24  Curry_Bartlett
 * Merge Information:  Non-Visual Merge: User specified tree v51asupportos.nightly
 *     User Revision:  v51bsupportos_nightly:4.2.48.4 Local Ancestor:4.2.48.4
 *    Merge Revision:  v51asupportos_nightly:4.2.60.4
 *   Common Ancestor:  4.2.39.4
 * 	Merge up to v51asupport.nightly
 *
 * Revision 4.2.48.4  2002/06/05  21:11:02  Curry_Bartlett
 * 	Merge up to v51asupport.bl2
 *
 * Revision 4.2.48.3  2002/05/31  21:03:56  Curry_Bartlett
 * 	changed kernel audit buffer management from a buffer
 * 	pool to one buffer per processor. defined structures
 * 	to support moving audit buffer pointers and stats into
 * 	the processor structure. fixed buffer overflow issues.
 * 	added new audit stats.
 * 	fixed buffer overflow problems by changing AUD_RECTAIL
 * 	to leave space for the b,r,v,w,x encodings which add
 * 	data after a variable length string using INSERT_
 * 	routines which depend on Y_ZONE.
 *
 * Revision 4.2.48.2  2002/02/01  00:35:31  Curry_Bartlett
 * 	added the DO_AUDEVENT and DO_AUD_ERRSTAT to allow the user
 * 	to get the mask for an audit event and to check it later
 * 	to see if the event was enabled for auditing for failure
 * 	or success. added definitions for u_vno_aud.
 *
 * Revision 4.2.48.1  2001/10/01  18:34:25  Curry_Bartlett
 * 	- Feature tag wc.audit.010.flock:
 * 	  Add support for auditing file lock data - add token and encoding
 * 	for flock structure.
 * 	- QAR 86098:
 * 	  Add AUD_EVENT_HDR_FIXLEN - fixed size of audit event header.
 * 	Add token for exportfs root address vector (AUD_TP_ROOTADDRVEC)
 * 	- Feature tag yn.audit.008.objsel:
 * 	  Added symbols associated with u_vno_aud & encoding
 * 	- Feature tag yn.audit.001.clock:
 * 	  added token for audit event sequence number (AUD_TP_SEQ).
 * 	- Feature tag yn.audit.001.socket:
 * 	  added token for socket network protocol data (AUD_T_NETPROTO).
 * 	- Feature tag yn.audit.001.new_events:
 * 	  added IPv6 trusted events (QAR 83004).
 *
 * Revision 4.2.39.4  2000/02/28  16:14:31  Spider_Boardman
 * 	* Additional NUMA replications.
 * 
 * Revision 4.2.39.3  2000/01/29  03:08:52  Ernie_Petrides
 * 	Restore revision 4.2.39.1 lost in last change.
 * 
 * Revision 4.2.39.2  2000/01/29  00:00:46  Curry_Bartlett
 * 	zinc to zulu merge cleanup
 * 	[2000/01/29  00:00:20  Curry_Bartlett]
 * 
 * Revision 4.2.39.1  2000/01/27  20:27:09  Ernie_Petrides
 * 	Allow for replication of "audswitch".
 * 
 * Revision 4.2.37.1  2000/01/05  00:20:40  Curry_Bartlett
 * 	Code to add new network trusted audit events"	Added support for asynchronous kernel trusted events. Provided a macro
 * 	to test to see if the events are enable (audit.h):
 * 	#define DO_KERN_TRUSTED_AUDIT(event, error)
 * 	 (audswitch && (AUDIT_EVENT_T((event)-MIN_TRUSTED_EVENT) & ((error) ? 0x01 : 0x02)))
 * 	Created a new audit record header in audit_rec_build (kern_audit.c) for the
 * 	asynchronous kernel trusted events:
 * 	 #define AUD_H2PR             (AUD_HDR2|AUD_PRM|AUD_RES)
 * 	 #define AUD_HDR2             0x400
 * 	Added 3 new transfer flags to audit_rec_build (kern_audit.c) to support new
 * 	tokens:
 * 	     e/E: local bsd 4.4 sockaddr (kernel-space)
 * 	     f/F: remote bsd 4.4 sockaddr (kernel-space)
 * 	     j/J: tcp flags, int (kernel-space)
 * 	Added support in audgen (kern_auditcalls.c) for the new tokens:
 * 	 #define T_LSOCK              AUD_T_LSOCK
 * 	 #define T_RSOCK              AUD_T_RSOCK
 * 	 #define T_LHOSTNAME          AUD_T_LHOSTNAME
 * 	Added 5 new asynchronous kernel trusted events (audit.h & trustedevents.c):
 * 	 #define NET_TCP_STRAY_PACKET     529
 * 	 #define NET_TCP_SYN_TIMEOUT      530
 * 	 #define NET_UDP_STRAY_PACKET     531
 * 	 #define NET_TCP_REJECTED_CONN    532
 * 	 #define DEBUG_LOG                533
 * 	Added 4 new audit tokens to handle new data types assocated with the
 * 	new asynchronous kernel trusted events (audit.h):
 * 	 #define AUD_T_LSOCK          0x0e   * 0016 - local sys sockaddr    *
 * 	 #define AUD_T_RSOCK          0x0f   * 0017 - remote sys sockaddr   *
 * 	 #define AUD_T_LHOSTNAME      0x10   * 0020 - local hostname        *
 * 	 #define AUD_T_TCPFLAGS       0x36   * 0066 - tcp flags             *
 * 	 #define T_LSOCK              AUD_T_LSOCK
 * 	 #define T_RSOCK              AUD_T_RSOCK
 * 	 #define T_LHOSTNAME          AUD_T_LHOSTNAME
 * 	 #define T_TCPFLAGS           AUD_T_TCPFLAGS
 * 	Added code to create audit event in:
 * 	tcp_input.c  NET_TCP_REJECTED_CONN
 * 	             NET_TCP_STRAY_PACKET
 * 	tcp_timer.c  NET_TCP_SYN_TIMEOUT
 * 	udp_usrreq.c NET_UDP_STRAY_PACKET
 * 	Ported code from 4.0f which logged the NET_TCP_REJECTED_CONN,
 * 	NET_TCP_STRAY_PACKET, NET_TCP_SYN_TIMEOUT, NET_UDP_STRAY_PACKET
 * 	events with a printf into:
 * 	tcp_input.c
 * 	tcp_timer.c
 * 	udp_usrreq.c
 * 
 * Revision 4.2.22.11  1998/04/08  16:06:41  Ann_Majeske
 *  	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	4.2.22.9 **
 * 		** Merge revision:	4.2.22.10 **
 *  	** End **
 * 	Change decsec_lblir_type to decsec_ir_type (not just labels).
 * 	[1998/03/10  15:56:03  Ann_Majeske]
 * 
 * 	Replace attr_t typedef with decsec_lblir_type so as to not
 * 	conflict with standards and curses.h.  QAR 48246.
 * 	[1998/03/09  18:52:46  Ann_Majeske]
 * 
 * 	Replace references to KERNEL with _KERNEL.  See QAR 49443.
 * 	[1998/03/09  17:00:22  Ann_Majeske]
 * 
 * Revision 4.2.22.10  1998/04/08  15:29:23  Larry_Scott
 * 	add AUDITD_EVENT macro
 * 	[1998/03/22  16:03:05  Larry_Scott]
 * 
 * Revision 4.2.22.9  1997/10/23  17:24:14  Spider_Boardman
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL10:PTCOS_BL11 **
 * 		** Ancestor revision:	4.2.28.2 **
 * 		** Merge revision:	4.2.28.3 **
 * 	 	** End **
 * 	PTCOS BL11 merge
 * 	[1997/10/23  17:20:21  Spider_Boardman]
 * 
 * Revision 4.2.22.8  1997/09/18  13:39:13  Andrew_Duane
 * 	Last arg to audit_call is char *, not u_char *.
 * 	Add prototype for audit_rec_build.
 * 	[1997/08/26  20:42:13  Andrew_Duane]
 * 
 * Revision 4.2.22.7  1997/08/21  20:19:26  Andrew_Duane
 * 	Merge with STEELOS.
 * 	[1997/08/21  18:11:49  Andrew_Duane]
 * 
 * 	Add prototypes for audit_call() and aud_overflow_hndlr().
 * 	[1997/08/19  19:21:22  Andrew_Duane]
 * 
 * Revision 4.2.28.3  1997/08/12  14:02:43  Larry_Scott
 * 	Add check for null habitats compat_mod pointer
 * 	[1997/08/08  19:00:18  Larry_Scott]
 * 
 * Revision 4.2.22.6  1997/08/04  11:09:32  James_Woodward
 * 	replace pid_tab lock with per pidtab entry lock
 * 	[1997/05/20  13:29:51  James_Woodward]
 * 
 * Revision 4.2.28.2  1997/04/14  20:06:19  Larry_Scott
 * 	Add GET_DATALEN option
 * 	[1997/04/07  20:51:16  Larry_Scott]
 * 
 * Revision 4.2.22.5  1997/01/03  21:54:15  Larry_Scott
 * 	Change "#if AUD_COMPAT" back to "#if defined(AUD_COMPAT)"
 * 	This was the previous behavior; libc uses it.
 * 	[1997/01/03  17:04:09  Larry_Scott]
 * 
 * Revision 4.2.22.4  1997/01/02  18:59:54  Larry_Scott
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	4.2.22.3 **
 * 		** Merge revision:	4.2.22.3 **
 * 	 	** End **
 * 	 	** Merge Information **
 * 		** Command used:	bmerge **
 * 		** Ancestor revision:	4.2.16.14 **
 * 		** Merge revision:	4.2.22.3 **
 * 	 	** End **
 * 	merge audit work
 * 	[1996/12/26  15:50:41  Larry_Scott]
 * 
 * 	support optionally recording u_comm
 * 	[1996/11/01  17:43:03  Larry_Scott]
 * 
 * 	remove temporary def'n of M_SEC now that it's in malloc.h
 * 	[1996/08/15  19:49:23  Larry_Scott]
 * 
 * 	merge with steel pool
 * 	[1996/08/15  18:20:16  Larry_Scott]
 * 
 * 	mls: remove include of acl.h
 * 	[1996/06/29  00:29:58  Larry_Scott]
 * 
 * 	merge in mls MAC updates
 * 	[1996/06/22  19:46:12  Larry_Scott]
 * 
 * 	update encodings descriptions
 * 	[1996/05/23  12:15:00  Larry_Scott]
 * 
 * 	add comments for tokens
 * 	add AUD_DBG
 * 	[1996/04/20  15:07:42  Larry_Scott]
 * 
 * 	add encoding for kernel-space strings (audprintf support)
 * 	[1996/04/12  00:50:19  Larry_Scott]
 * 
 * 	Add machipc operations
 * 	[1996/04/10  15:30:35  Larry_Scott]
 * 
 * 	Add mach trap auditing support.
 * 	Define old token names (e.g. T_UID) only if AUD_COMPAT defined (i.e. don't
 * 	automatically define them for kernel.
 * 	[1996/03/27  21:35:47  Larry_Scott]
 * 
 * Revision 4.2.22.3  1996/12/09  22:01:27  Neil_Lewis
 * 	Eliminate compiler warnings when compiled with -warnprotos.
 * 	[1996/11/12  16:14:47  Neil_Lewis]
 * 
 * Revision 4.2.22.2  1996/07/30  17:56:32  Larry_Scott
 * 	add GET_DATALEN option
 * 	[1996/07/29  15:36:55  Larry_Scott]
 * 
 * Revision 4.2.16.14  1995/12/19  23:15:16  Larry_Scott
 * 	increment AUD_VERSION value
 * 	[1995/12/19  22:01:41  Larry_Scott]
 * 
 * Revision 4.2.16.13  1995/12/12  16:11:27  Larry_Scott
 * 	add AUD_TP_TID token
 * 	[1995/12/08  16:52:07  Larry_Scott]
 * 
 * Revision 4.2.16.12  1995/11/16  19:54:48  Larry_Scott
 * 	lint work
 * 	[1995/11/16  19:46:27  Larry_Scott]
 * 
 * Revision 4.2.16.11  1995/11/03  20:36:10  Larry_Scott
 * 	update description of aud_param encodings
 * 	[1995/11/03  19:09:56  Larry_Scott]
 * 
 * Revision 4.2.16.10  1995/09/20  18:57:57  Larry_Scott
 * 	add AUD_MINBUF_SIZ macro
 * 	[1995/09/20  15:39:34  Larry_Scott]
 * 
 * Revision 4.2.16.9  1995/06/16  21:01:41  Larry_Scott
 * 	add AUD_PROPL_UNAVAIL; remove AUD_ACL
 * 	[1995/06/14  21:34:23  Larry_Scott]
 * 
 * Revision 4.2.16.8  1995/04/18  15:21:58  Larry_Scott
 * 	add AUDIT_HABITAT_USR audcntl flag to explicitly enable audit
 * 	of habitat events for a specific process
 * 	[1995/04/16  17:17:08  Larry_Scott]
 * 
 * Revision 4.2.16.7  1995/03/24  04:19:22  Larry_Scott
 * 	remove AUD_T_IRLABEL (unused)
 * 	add AUTHORIZATION_USE
 * 	[1995/03/24  03:45:22  Larry_Scott]
 * 
 * Revision 4.2.16.6  1995/02/03  16:47:28  Larry_Scott
 * 	remove TRUSTED_CMD_EXEC
 * 	[1995/02/02  23:30:16  Larry_Scott]
 * 
 * Revision 4.2.16.5  1995/01/25  16:43:41  Larry_Scott
 * 	comment: add encoding for privvec_t, label
 * 	restore previous names for X events
 * 	add AUD_T_IRLABEL
 * 	[1995/01/09  17:11:14  Larry_Scott]
 * 
 * Revision 4.2.16.4  1994/12/16  16:18:17  Larry_Scott
 * 	add extern declaration for audit_rec_build
 * 	[1994/12/15  19:35:48  Larry_Scott]
 * 
 * Revision 4.2.16.3  1994/12/13  21:23:25  Larry_Scott
 * 	add support for X auditing
 * 	[1994/12/12  15:20:45  Larry_Scott]
 * 
 * Revision 4.2.16.2  1994/11/23  18:13:59  Larry_Scott
 * 	add new audstyle options
 * 	set audsize to be u_int
 * 	handle audit records of size which exceeds that of record buffer
 * 	support opaque data entries
 * 	add AUD_OVERRIDE_OBJ_SEL
 * 	update aud_stats
 * 	support configurable siteauditmask size
 * 	support non-exclusive audcntl states - AUDIT_SYSCALL_OFF
 * 	support iovec style data
 * 	MLS support
 * 	update trusted event list
 * 	[1994/11/16  01:15:35  Larry_Scott]
 * 
 * Revision 4.2.14.10  1994/04/04  20:48:55  Larry_Scott
 * 	fix namespace conflict
 * 	[1994/03/31  16:15:34  Larry_Scott]
 * 
 * Revision 4.2.14.9  1994/03/29  16:21:27  Larry_Scott
 * 	add support for T_INTP; fix boundary check for oversized records
 * 	[1994/03/16  20:32:02  Larry_Scott]
 * 
 * Revision 4.2.14.8  1994/01/19  14:49:16  Larry_Scott
 * 	add options to fetch another proc's auditmask, audcntl flag
 * 	[1994/01/11  23:52:03  Larry_Scott]
 * 
 * Revision 4.2.14.7  1993/12/16  17:08:58  Larry_Scott
 * 	merge of Sterling BL8 changes
 * 	[1993/12/16  17:04:46  Larry_Scott]
 * 
 * Revision 4.2.14.6  1993/12/14  16:57:36  Ernie_Petrides
 * 	Optimize DO_AUDIT() and AUDIT_CALL() and modify audit_rec_build() args.
 * 	[1993/12/12  02:44:10  Ernie_Petrides]
 * 
 * Revision 4.2.14.5  1993/11/05  06:29:00  Tim_Hoskins
 * 	merge of Sterling BL7 changes
 * 	[1993/11/05  06:16:08  Tim_Hoskins]
 * 
 * Revision 4.2.14.4  1993/10/20  20:43:41  Larry_Scott
 * 	sync up with sterling changes
 * 	[1993/10/20  14:35:42  Larry_Scott]
 * 
 * Revision 4.2.11.12  1993/10/14  13:54:52  Larry_Scott
 * 	memory capacity work - AUDIT_CALL2 macro
 * 	[1993/10/11  22:11:38  Larry_Scott]
 * 
 * Revision 4.2.14.3  1993/09/28  23:28:33  Larry_Scott
 * 	security merge
 * 	[1993/09/28  15:41:34  Larry_Scott]
 * 
 * Revision 4.2.11.11  1993/09/23  18:52:40  Larry_Scott
 * 	add T_HOSTNAME token for I&A use
 * 	[1993/09/16  20:27:47  Larry_Scott]
 * 
 * Revision 4.2.14.2  1993/09/15  20:11:34  Larry_Scott
 * 	start of security merge
 * 	[1993/09/15  20:07:20  Larry_Scott]
 * 
 * Revision 4.2.11.10  1993/07/20  18:43:39  Larry_Scott
 * 	update encodings table (comment)
 * 	[1993/07/20  14:09:11  Larry_Scott]
 * 
 * Revision 4.2.11.9  1993/06/23  13:44:44  Larry_Scott
 * 	add comment for new encoding for BSD4.4 msghdr
 * 	[1993/06/16  22:01:52  Larry_Scott]
 * 
 * Revision 4.2.11.8  1993/06/14  16:07:21  Larry_Scott
 * 	add TP_ADDRVEC token for exportfs() support; fix N_SYSCALLS
 * 	[1993/06/10  03:23:42  Larry_Scott]
 * 
 * Revision 4.2.11.7  1993/05/26  15:41:38  Michael_Fairbrother
 * 	Added support for SecureWare Audit event compatiblity
 * 	[1993/05/18  13:55:19  Michael_Fairbrother]
 * 
 * Revision 4.2.11.6  1993/05/14  19:53:45  Larry_Scott
 * 	updevents cleanup
 * 	[1993/05/05  17:56:11  Larry_Scott]
 * 
 * 	update encodings' comments
 * 	[1993/05/03  18:13:24  Larry_Scott]
 * 
 * Revision 4.2.11.5  1993/04/23  17:20:12  Larry_Scott
 * 	add comment
 * 	[1993/04/19  18:35:27  Larry_Scott]
 * 
 * 	add TP_SET_UIDS
 * 	[1993/04/15  19:11:26  Larry_Scott]
 * 
 * 	perf work
 * 	[1993/04/14  13:25:06  Larry_Scott]
 * 
 * Revision 4.2.11.4  1993/04/08  19:21:11  Michael_Fairbrother
 * 	Added missing revision information so that the tracking^Jtool does not always flag this file.
 * 	[1993/04/08  18:08:24  Michael_Fairbrother]
 * 
 * Revision 4.2.11.3  1993/04/02  20:46:34  Larry_Scott
 * 	update encodings comment
 * 	[1993/04/02  18:56:21  Larry_Scott]
 * 
 * Revision 4.2.11.2  1993/04/01  20:06:57  Michael_Fairbrother
 * 	Merge from shared sandbox to sandbox prior to submit
 * 	[1993/04/01  15:49:31  Michael_Fairbrother]
 * 
 * Revision 4.2.9.19  1993/03/31  13:12:10  Spider_Boardman
 * 	Update prototype for audit_change_mask().
 * 	Add audit_build_mask().
 * 	[1993/03/31  13:11:17  Spider_Boardman]
 * 
 * Revision 4.2.9.18  1993/03/29  19:15:04  Spider_Boardman
 * 	Fix typo on name of audit_mask_change_done().
 * 	[1993/03/29  19:13:28  Spider_Boardman]
 * 
 * 	Add references to library routines for user-mode includes.
 * 	[1993/03/29  18:35:45  Spider_Boardman]
 * 
 * Revision 4.2.9.17  1993/03/28  21:24:17  Larry_Scott
 * 	add option to override sysent.aud_param encoding
 * 	[1993/03/27  21:34:52  Larry_Scott]
 * 
 * Revision 4.2.9.16  1993/03/23  20:16:09  Larry_Scott
 * 	define AUDIT_MASK_LEN
 * 	[1993/03/23  20:15:12  Larry_Scott]
 * 
 * Revision 4.2.9.15  1993/03/22  18:29:48  Larry_Scott
 * 	add AUD_LOGIN_UNAME
 * 	[1993/03/19  22:37:23  Larry_Scott]
 * 
 * Revision 4.2.9.14  1993/03/11  19:10:42  Larry_Scott
 * 	fix AUDMASK_LEN macro
 * 	[1993/03/11  19:07:53  Larry_Scott]
 * 
 * Revision 4.2.9.13  1993/03/09  16:15:16  Larry_Scott
 * 	add SELF_AUDIT constant
 * 	[1993/03/09  15:59:17  Larry_Scott]
 * 
 * Revision 4.2.9.12  1993/02/28  10:57:56  Larry_Scott
 * 	32,64-bit data compatibility
 * 	[93/02/27  23:29:28  Larry_Scott]
 * 
 * Revision 4.2.9.11  93/02/24  16:59:56  Larry_Scott
 * 	add version token
 * 	[93/02/24  16:56:41  Larry_Scott]
 * 
 * Revision 4.2.9.10  93/02/20  15:58:08  Larry_Scott
 * 	add new encodings
 * 	[93/02/20  15:36:57  Larry_Scott]
 * 
 * Revision 4.2.9.9  93/02/19  14:19:49  Larry_Scott
 * 	add audcntl options (again)
 * 	[93/02/19  14:16:17  Larry_Scott]
 * 
 * 	add audcntl options
 * 	[93/02/19  14:10:36  Larry_Scott]
 * 
 * Revision 4.2.9.8  93/02/17  13:34:13  Larry_Scott
 * 	add libaud with support changes
 * 	[93/02/17  13:22:40  Larry_Scott]
 * 
 * Revision 4.2.9.7  93/02/16  11:03:13  Larry_Scott
 * 	merge with alpha.bl012
 * 	[93/02/16  10:56:15  Larry_Scott]
 * 
 * Revision 4.2.9.6  93/01/25  10:10:04  Larry_Scott
 * 	move VNO_MAX to be non-kernel specific
 * 	[93/01/25  10:09:22  Larry_Scott]
 * 
 * Revision 4.2.9.5  93/01/21  11:59:19  Larry_Scott
 * 	update (again)
 * 	[93/01/21  11:40:04  Larry_Scott]
 * 
 * Revision 4.2.9.2  92/12/07  13:10:42  Michael_Fairbrother
 * 	New audit subsystem
 * 	[92/12/07  12:40:01  Michael_Fairbrother]
 * 
 * Revision 4.2.6.4  1992/06/03  13:43:43  Paul_Hansen
 * 	Merged in Silver BL7
 * 	[92/06/03  13:34:41  Paul_Hansen]
 * 
 * $EndLog$
 */

#ifndef __AUDIT__
#define __AUDIT__ 1

#include <sys/types.h>
#include <sys/time.h>
#include <sys/param.h>
#include <sys/syscall.h>
#include <sys/systm.h>
#include <sys/habitat.h>
#include <sys/unix_defs.h>
#include <kern/lock.h>

#if MLS_AUDIT
#include <sys/security.h>
#include <sys/secpolicy.h>
#if !defined(_KERNEL)
#include <mandatory.h>
#endif /* !defined(_KERNEL) */
#define AUD_COMPAT    1
#endif /* MLS_AUDIT */

/* audcntl options */
#define GET_SYS_AMASK           0
#define SET_SYS_AMASK           1
#define GET_TRUSTED_AMASK       2
#define SET_TRUSTED_AMASK       3
#define GET_PROC_AMASK          4
#define SET_PROC_AMASK          5
#define GET_PROC_ACNTL          6
#define SET_PROC_ACNTL          7
#define GET_AUDSWITCH           8
#define SET_AUDSWITCH           9
#define GETPAID                10
#define SETPAID                11
#define GET_AUDSTYLE           12
#define SET_AUDSTYLE           13
#define GET_SITEMASK           14
#define SET_SITEMASK           15
#define GET_OBJAUDBIT          16
#define SET_OBJAUDBIT          17
#define UPDEVENTS              18
#define FLUSH_AUD_BUF          19
#define GET_HABITAT_EVENT      20
#define SET_HABITAT_EVENT      21
#define GET_NSITEVENTS         22
#define GET_AUDSIZE            23
#define GET_SUBJ_AMASK         24
#define GET_SUBJ_ACNTL         25
#define GET_MACH_AMASK         26
#define SET_MACH_AMASK         27
#define GET_MACHIPC_AMASK      28
#define SET_MACHIPC_AMASK      29
#define GET_DATALEN            30
#define GET_SLRANGE            39   /* MLS */
#define SET_SLRANGE            40   /* MLS */
#define GET_AUDSTATS           41
#define GET_MISSEDEVENT_CTR    42


/* audcntl flags - exclusive states */
#define AUDIT_OR             0x000
#define AUDIT_AND            0x001
#define AUDIT_OFF            0x002
#define AUDIT_USR            0x004
#define AUDIT_CNTLMASK       0x007

/* audcntl flags - non-exclusive states */
#define AUDIT_SYSCALL_OFF    0x008
#define AUDIT_HABITAT_USR    0x010
#define AUDIT_MACH_USR       0X020

/* audcntl UPDEVENTS flags */
#define UPD_CNTL             0x001
#define UPD_MASK             0x002

/* audstyle flags */
#define AUD_EXEC_ARGP        0x001
#define AUD_EXEC_ENVP        0x002
#define AUD_LOGIN_UNAME      0x004
#define AUD_OBJ_DESEL        0x008
#define AUD_OBJ_SEL          0x010
#define AUD_MAC_SL           0x020
#define AUD_MAC_IL           0x040
#define AUD_UCOMM            0x080
#define AUD_OBJSEL_IPC       0x100
#define AUD_OBJ_SELPLUS      0x200
#define AUD_OBJ_MASK         (AUD_OBJ_SELPLUS|AUD_OBJ_DESEL|AUD_OBJ_SEL)
#define AUD_STYLFLAGS        0x3ff  /* user visible flags */
#define AUD_PROPL_UNAVAIL    0x80000000   /* kernel only  */

/* audioctl commands and structure */
#define AUDIOCGETN           _IOR('C', 0, struct audiocp)
#define AUDIOCSETN           _IOW('C', 1, int)
struct audiocp {
    u_int size;              /* size of audit buffer      */
    u_int offset;            /* offset into buffer        */
    u_int nbytes;            /* # bytes of data available */
};

/* objaudbit/property-list values */
#define AUD_PROPL_FLAG       "DEC_AUDIT_PROPLISTFLAG"
#define AUD_SELECT           0x1
#define AUD_DESELECT         0x2

/* misc values */
#define AUID_INVAL          -1
#define AUDITD_RECSZ         (MAXPATHLEN*2)
#define AUD_BUF_SIZ          8192
#define AUD_MAXEVENT_LEN     64
#define N_SYSCALLS           ((LAST&~0x3)+(NBBY>>1))
#define MAXHABSYSCALL_LEN    128
#define AUD_VNOMAX           2      /* must be at least 2 */
#define N_AUDTUPLES          128

/* u_vno_aud bits (for object selection/deselection) */
#define VNOAUD_FILE_OBJSEL   0x0001  /* file monitored per AUD_SELECT         */
#define VNOAUD_FILE_OBJDESEL 0x0002  /* file monitored per AUD_DESELECT       */
#define VNOAUD_PDIR_OBJSEL   0x0010  /* parent dir monitored per AUD_SELECT   */
#define VNOAUD_PDIR_OBJDESEL 0x0020  /* parent dir monitored per AUD_DESELECT */

#define VNOAUD_FILEFLG_ACC   VNOAUD_FILE_OBJSEL
#define VNOAUD_FILEFLG_MOD   VNOAUD_FILE_OBJDESEL
#define VNOAUD_PDIRFLG_ACC   VNOAUD_PDIR_OBJSEL
#define VNOAUD_PDIRFLG_MOD   VNOAUD_PDIR_OBJDESEL
#define VNOAUD_FILE_A        0x0100  /* unused */
#define VNOAUD_PDIR_A        0x1000  /* unused */
#define VNOAUD_FILE_W        0x0200  /* unused */
#define VNOAUD_PDIR_W        0x2000  /* unused */

/* audit version number
    also distinguish between 64-bit and 32-bit longword
    low-order 16 bits used for version #
    high-order 16 bits used for flags

    - updated to version 2 for new msfs_syscall audit format
    - updated to version 3 to differentiate wcalpha bl5 from v51asupportos_bl2 diffs
*/
#define AUD_VERSION          0x0003
#define AUD_VERS_MASK        0x00ff
#define AUD_VERS_LONG        0x8000     /* 64-bit longword */
#define AUD_MLS              0x4000     /* mls data        */


/* token encodings:
    bit 0x80 (TP_* tokens) indicates private token; cannot be given to audgen(2)
    0x01-0x1f, 0x81-0x8f are reserved for ptr token types
*/
#define A_TOKEN_PRIV(x)      ((x)&0x80)
#define A_TOKEN_PTR(x)       (((x)&0x7f) >= 0x01 && ((x)&0x7f) <= AUD_TOKEN_PTR_MAX)
#define A_TOKEN_IOVEC(x)     ((x) >= AUD_TOKEN_IOVEC_MIN && (x) <= AUD_TOKEN_PTR_MAX)

/* -- public tokens -- */
    /* start of ptr token types */
#define AUD_T_CHARP          0x01   /* 0001 - string                */
#define AUD_T_SOCK           0x03   /* 0003 - sockaddr struct       */
#define AUD_T_LOGIN          0x04   /* 0004 - login name            */
#define AUD_T_HOMEDIR        0x05   /* 0005 - home directory        */
#define AUD_T_SHELL          0x06   /* 0006 - shell name            */
#define AUD_T_DEVNAME        0x07   /* 0007 - device name           */
#define AUD_T_SERVICE        0x08   /* 0010 - service name          */
#define AUD_T_HOSTNAME       0x09   /* 0011 - hostname              */
#define AUD_T_INTP           0x0a   /* 0012 - integer array         */
#define AUD_T_SLABEL         0x0b   /* 0013 - MLS security label    */
#define AUD_T_ILABEL         0x0c   /* 0014 - MLS information label */
#define AUD_T_PRIVMASK       0x0d   /* 0015 - MLS privilege mask    */
#define AUD_T_LSOCK          0x0e   /* 0016 - local sys sockaddr    */
#define AUD_T_RSOCK          0x0f   /* 0017 - remote sys sockaddr   */
#define AUD_T_LHOSTNAME      0x10   /* 0020 - local hostname        */
#define AUD_T_NETPROTO       0x11   /* 0021 - socket protocol data  */
    /* 1st element of int array is # of data elements in array */

    /* start of iovec style data */
#define AUD_TOKEN_IOVEC_MIN  0x18
#define AUD_T_OPAQUE         0x18   /* 0030 - opaque data           */
#define AUD_T_INTARRAY       0x19   /* 0031 - integer array         */
#define AUD_T_GIDSET         0x1a   /* 0032 - group set             */
#define AUD_T_XDATA          0x1b   /* 0033 - aud_xdata struct      */
#define AUD_TOKEN_PTR_MAX    0x1f   /* 0037 */
    /* end of iovec style data */
    /* end of ptr token types */

#define AUD_T_AUID           0x20   /* 0040 - audit id              */
#define AUD_T_RUID           0x21   /* 0041 - real uid              */
#define AUD_T_UID            0x22   /* 0042 - effective uid         */
#define AUD_T_PID            0x23   /* 0043 - pid                   */
#define AUD_T_PPID           0x24   /* 0044 - parent pid            */
#define AUD_T_GID            0x25   /* 0045 - gid                   */
#define AUD_T_EVENT          0x26   /* 0046 - event #               */
#define AUD_T_SUBEVENT       0x27   /* 0047 - subevent #            */

#define AUD_T_DEV            0x28   /* 0050 - dev major,minor #     */
#define AUD_T_ERRNO          0x29   /* 0051 - errno                 */
#define AUD_T_RESULT         0x2a   /* 0052 - result (8 bytes)      */
#define AUD_T_MODE           0x2b   /* 0053 - object mode           */
#define AUD_T_HOSTADDR       0x2c   /* 0054 - host ipaddr           */
#define AUD_T_INT            0x2d   /* 0055 - integer               */
#define AUD_T_DESCRIP        0x2e   /* 0056 - descriptor            */
#define AUD_T_HOSTID         0x2f   /* 0057 - hostid                */

#define AUD_T_X_ATOM         0x30   /* 0060 - X atom                */
#define AUD_T_X_CLIENT       0x31   /* 0061 - X client id           */
#define AUD_T_X_PROPERTY     0x32   /* 0062 - X property id         */
#define AUD_T_X_RES_CLASS    0x33   /* 0063 - X resource class      */
#define AUD_T_X_RES_TYPE     0x34   /* 0064 - X resource type       */
#define AUD_T_X_RES_ID       0x35   /* 0065 - X resource id         */
#define AUD_T_TCPFLAGS       0x36   /* 0066 - tcp flags             */

#define AUD_T_SECEVENT       0x7f   /* 0177 - MLS security event    */

/* -- private tokens -- */
#define AUD_TP_ACCRGHT       0x81   /* 0201 - msghdr access rights  */
#define AUD_TP_MSGHDR        0x82   /* 0202 - msghdr msg_name       */
#define AUD_TP_EVENTP        0x83   /* 0203 - habitat event name    */
#define AUD_TP_HABITAT       0x84   /* 0204 - habitat name          */
#define AUD_TP_ADDRVEC       0x85   /* 0205 - exportfs address list */
#define AUD_TP_INTP          0x86   /* 0206 - integer array         */
#define AUD_TP_UCOMM         0x87   /* 0207 - command name          */
#define	AUD_TP_ROOTADDRVEC   0x88   /* 0208 - exportfs root addr lst*/
#define AUD_TP_FLOCK         0x89   /* 0210 - flock structure       */

#define AUD_TP_AUID          0xa1   /* 0241 - audit id              */
#define AUD_TP_RUID          0xa2   /* 0242 - real uid              */
#define AUD_TP_UID           0xa3   /* 0243 - effective uid         */
#define AUD_TP_PID           0xa4   /* 0244 - pid                   */
#define AUD_TP_PPID          0xa5   /* 0245 - parent pid            */
#define AUD_TP_HOSTADDR      0xa6   /* 0246 - host ipaddr           */
#define AUD_TP_EVENT         0xa7   /* 0247 - event #               */

#define AUD_TP_SUBEVENT      0xa8   /* 0250 - subevent #            */
#define AUD_TP_NCPU          0xa9   /* 0251 - cpu #                 */
#define AUD_TP_DEV           0xaa   /* 0252 - dev major,minor #     */
#define AUD_TP_LENGTH        0xab   /* 0253 - audit record length   */
#define AUD_TP_IPC_GID       0xac   /* 0254 - sysV object gid       */
#define AUD_TP_IPC_MODE      0xad   /* 0255 - sysV object mode      */
#define AUD_TP_IPC_UID       0xae   /* 0256 - sysV object uid       */
#define AUD_TP_TV_SEC        0xaf   /* 0257 - timestamp (sec)       */

#define AUD_TP_TV_USEC       0xb0   /* 0260 - timestamp (usec)      */
#define AUD_TP_SHORT         0xb1   /* 0261 - short-sized data      */
#define AUD_TP_LONG          0xb2   /* 0262 - long-sized data       */
#define AUD_TP_VNODE_DEV     0xb3   /* 0263 - inode's device        */
#define AUD_TP_VNODE_ID      0xb4   /* 0264 - inode identifier      */
#define AUD_TP_VNODE_MODE    0xb5   /* 0265 - object mode           */
#define AUD_TP_VERSION       0xb6   /* 0266 - audit version #       */
#define AUD_TP_SET_UIDS      0xb7   /* 0267 - uid change flag       */

#define AUD_TP_CONT          0xb8   /* 0270 - continuation flag     */
#define AUD_TP_TID           0xb9   /* 0271 - thread id             */
#define AUD_TP_PRIV          0xba   /* 0272 - MLS privilege used    */
#define AUD_TP_SEQ           0xbb   /* 0273 - event seq#            */
#define AUD_TP_NB            0xbc   /* 0274 - non-blking event      */

#if defined(AUD_COMPAT)
/* -- public tokens -- */
    /* start of ptr token types */
#define T_CHARP              AUD_T_CHARP
#define T_SOCK               AUD_T_SOCK
#define T_LOGIN              AUD_T_LOGIN
#define T_HOMEDIR            AUD_T_HOMEDIR
#define T_SHELL              AUD_T_SHELL
#define T_DEVNAME            AUD_T_DEVNAME
#define T_SERVICE            AUD_T_SERVICE
#define T_HOSTNAME           AUD_T_HOSTNAME
#define T_INTP               AUD_T_INTP
#define T_SLABEL             AUD_T_SLABEL
#define T_ILABEL             AUD_T_ILABEL
#define T_PRIVMASK           AUD_T_PRIVMASK
#define T_LSOCK              AUD_T_LSOCK
#define T_RSOCK              AUD_T_RSOCK
#define T_LHOSTNAME          AUD_T_LHOSTNAME
#define T_TCPFLAGS           AUD_T_TCPFLAGS
    /* 1st element of int array is # of data elements in array */

    /* start of iovec style data */
#define T_OPAQUE             AUD_T_OPAQUE
#define T_INTARRAY           AUD_T_INTARRAY
#define T_GIDSET             AUD_T_GIDSET
#define T_XDATA              AUD_T_XDATA
    /* end of iovec style data */
    /* end of ptr token types */

#define T_AUID               AUD_T_AUID
#define T_RUID               AUD_T_RUID
#define T_UID                AUD_T_UID
#define T_PID                AUD_T_PID
#define T_PPID               AUD_T_PPID
#define T_GID                AUD_T_GID
#define T_EVENT              AUD_T_EVENT
#define T_SUBEVENT           AUD_T_SUBEVENT

#define T_DEV                AUD_T_DEV
#define T_ERRNO              AUD_T_ERRNO
#define T_RESULT             AUD_T_RESULT
#define T_MODE               AUD_T_MODE
#define T_HOSTADDR           AUD_T_HOSTADDR
#define T_INT                AUD_T_INT
#define T_DESCRIP            AUD_T_DESCRIP
#define T_HOSTID             AUD_T_HOSTID

#define T_X_ATOM             AUD_T_X_ATOM
#define T_X_CLIENT           AUD_T_X_CLIENT
#define T_X_PROPERTY         AUD_T_X_PROPERTY
#define T_X_RES_CLASS        AUD_T_X_RES_CLASS
#define T_X_RES_TYPE         AUD_T_X_RES_TYPE
#define T_X_RES_ID           AUD_T_X_RES_ID

#define T_SECEVENT           AUD_T_SECEVENT

/* -- private tokens -- */
#define TP_ACCRGHT           AUD_TP_ACCRGHT
#define TP_MSGHDR            AUD_TP_MSGHDR
#define TP_EVENTP            AUD_TP_EVENTP
#define TP_HABITAT           AUD_TP_HABITAT
#define TP_ADDRVEC           AUD_TP_ADDRVEC
#define TP_INTP              AUD_TP_INTP
#define TP_UCOMM             AUD_TP_UCOMM
#define	TP_ROOTADDRVEC	     AUD_TP_ROOTADDRVEC
#define TP_FLOCK             AUD_TP_FLOCK

#define TP_AUID              AUD_TP_AUID
#define TP_RUID              AUD_TP_RUID
#define TP_UID               AUD_TP_UID
#define TP_PID               AUD_TP_PID
#define TP_PPID              AUD_TP_PPID
#define TP_HOSTADDR          AUD_TP_HOSTADDR
#define TP_EVENT             AUD_TP_EVENT

#define TP_SUBEVENT          AUD_TP_SUBEVENT
#define TP_NCPU              AUD_TP_NCPU
#define TP_DEV               AUD_TP_DEV
#define TP_LENGTH            AUD_TP_LENGTH
#define TP_IPC_GID           AUD_TP_IPC_GID
#define TP_IPC_MODE          AUD_TP_IPC_MODE
#define TP_IPC_UID           AUD_TP_IPC_UID
#define TP_TV_SEC            AUD_TP_TV_SEC

#define TP_TV_USEC           AUD_TP_TV_USEC
#define TP_SHORT             AUD_TP_SHORT
#define TP_LONG              AUD_TP_LONG
#define TP_VNODE_DEV         AUD_TP_VNODE_DEV
#define TP_VNODE_ID          AUD_TP_VNODE_ID
#define TP_VNODE_MODE        AUD_TP_VNODE_MODE
#define TP_VERSION           AUD_TP_VERSION
#define TP_SET_UIDS          AUD_TP_SET_UIDS

#define TP_CONT              AUD_TP_CONT
#define TP_TID               AUD_TP_TID
#define TP_PRIV              AUD_TP_PRIV
#define TP_SEQ               AUD_TP_SEQ
#define TP_NB                AUD_TP_NB
#endif /* defined(AUD_COMPAT) */


/* trusted audit events */
#define MIN_TRUSTED_EVENT    512
#define AUDIT_START          512
#define AUDIT_STOP           513
#define AUDIT_SETUP          514
#define AUDIT_SUSPEND        515
#define AUDIT_LOG_CHANGE     516
#define AUDIT_LOG_CREAT      517
#define AUDIT_XMIT_FAIL      518
#define AUDIT_REBOOT         519
#define AUDIT_LOG_OVERWRITE  520
#define AUDIT_DAEMON_EXIT    521
#define LOGIN                522
#define LOGOUT               523
#define AUTH_EVENT           524
#define AUDGEN8              525
#define SW_COMPATIBILITY     526    /* MLS compatibility */
#define DNSIX_AUDIT_EVENT    527    /* MLS */
#define AUTHORIZATION_USE    528    /* MLS */
#define NET_TCP_STRAY_PACKET 529
#define NET_TCP_SYN_TIMEOUT  530
#define NET_UDP_STRAY_PACKET 531
#define NET_TCP_REJECTED_CONN    532
#define DEBUG_LOG            533

#define X_SERVER_STARTUP     540
#define X_SERVER_SHUTDOWN    541
#define X_CLIENT_STARTUP     542
#define X_CLIENT_SHUTDOWN    543
#define X_CLIENT_ATTR        544
#define X_OBJECT_ATTR        545    /* MLS */
#define X_OBJECT_CREATE      546
#define X_OBJECT_RENAME      547
#define X_OBJECT_DESTROY     548
#define X_DATA_MOVE          549    /* MLS */
#define X_OBJECT_READ        550
#define X_OBJECT_WRITE       551
#define X_SEC_CLEARANCE      552    /* MLS */
#define X_TPATH_HNDLR        553    /* MLS */
#define X_SELECTION_HNDLR    554    /* MLS */
#define X_WIN_MNGR           555    /* MLS */

#define NET_IPSEC_NO_POLOCY      556    /* sic */
#define NET_IPSEC_SEQ_OVERFLOW   557
#define NET_IPSEC_FRAGMENT       558
#define NET_IPSEC_NO_SA          559
#define NET_IPSEC_PACKET_REPLAY  560
#define NET_IPSEC_AUTH_FAILED    561
#define NET_IPSEC_NULL_ESP       562

#define CDSA_SYSTEM_DEFAULT_CHANGE 565
#define CDSA_MODULE_LOAD           566

#define NET_IPSEC_IKE_ERROR      568
#define NET_IPSEC_STARTED        569
#define NET_IPSEC_STOPPED        570

#define LPR_EVENT            573    /* MLS */

/* retired/recycled values */
#define X_SERVER_DAC         544
#define X_CLIENT_IPC         545
#define X_OBJECT_DAC         549

#define AUDITD_EVENT(event)  ((event) >= AUDIT_START && (event) <= AUDIT_DAEMON_EXIT)
#define MAX_TRUSTED_EVENT    (MIN_TRUSTED_EVENT+N_TRUSTED_EVENTS-1)

/* trusted, site event info */
#define N_TRUSTED_EVENTS     64
#define MIN_SITE_EVENT       2048


#if !defined(_KERNEL)
/* X auditing; data format associated with AUD_T_XDATA (iov_base) */
struct aud_xdata {
    u_short version;                /* see AUD_XOBJ_VERSION         */
    u_short flags;
#define AUD_XOBJ_CLIENT      0x001
#define AUD_XOBJ_OBJECT      0x002
    uid_t   auid;                   /* auid or -1                   */
    uid_t   euid;                   /* euid or -1                   */
    gid_t   egid;                   /* egid or -1                   */
    int     gidsetsize;             /* # of groups in gidset        */
    gid_t   gidset[NGROUPS_MAX];
    pid_t   pid;                    /* pid or 0                     */
    mode_t  mode;                   /* mode or -1                   */
    int     client_id;              /* client_id or -1              */
    int     objtyp;                 /* objtyp or -1                 */
    u_int   atom;                   /* atom or 0                    */
    u_int   res_id;                 /* res_id or 0                  */
    char    info_string[80];
    char    hdr_string[80];
#if MLS_AUDIT
    priv_t  privmask[SEC_SPRIVVEC_SIZE]; /* privmask or 0-filled    */
    decsec_ir_type  acl;         /* acl or ir_length of 0        */
    decsec_ir_type  slabel;      /* slabel or ir_length of 0     */
    decsec_ir_type  ilabel;      /* ilabel or ir_length of 0     */
    decsec_ir_type  kbd_il;      /* kbd_il or ir_length of 0     */
    decsec_ir_type  ptr_il;      /* ptr_il or ir_length of 0     */
    char    xdata[1];               /* placeholder for ir data      */
#define AUD_XOBJ_VERSION     (0|AUD_MLS)
#else
#define AUD_XOBJ_VERSION     0
#endif /* MLS_AUDIT */
};
#endif /* !defined(_KERNEL) */


/* per cpu buffer data */
struct aud_buff_cpu { /* buffer data */
    uint_t inited;           /* per-cpu values initialized                  */
    uint_t seqnum;           /* audit event sequence #                      */
    char *data;              /* audit data buffer (protected by audbuf lock)*/

    /* pointers associated with loading the buffer */
    udecl_simple_lock_data(,llock)    /* setup storage for buffer load lock.
                              * thread must hold lock to load tid into 
                              * owner_l and become owner. a thread must be  
                              * the owner when modifying _l values          */
    struct thread *owner_l;  /* id of thread loading the buffer             */
    int slp_l;               /* chan for sleep/wake load buff full/busy     */

    uint_t ptr_l;            /* pointer to the end of the event records in the 
                              * buffer. 
                              * # of bytes of data (for complete event 
                              *                     records) = ptr_l-off_o  */
    uint_t len_l;            /* pointer to the end of data in the per cpu 
                              * buffer. this pointer gets adjusted as each
                              * element gets added into this buffer.        */
    uint_t bufsz;            /* size of data buffer in bytes                */
 
    /* pointers associated with outputting data to log */
    udecl_simple_lock_data(,olock)   /* setup storage for buffer load lock  
                              * thread must hold lock to load tid into 
                              * owner_o and become owner. a thread must be the
                              * must be the owner when modifying _o values  */ 
    struct thread *owner_o;  /* id of thread outputting the buffer          */
    int slp_o;               /* chan sleep/wake on output buff full/busy    */

    uint_t off_o;            /* pointer to start of data in the buffer      */
    uint_t ptr_o;            /* RFU */
    int  reserved_int;
    long reserved[14];
/* 64 byte alignment */
};

/* Per-cpu statistics.  No locking done here; stats are approximate.
 * (If this structure changes, update the GET_AUDSTATS audcntl code.)
 */
struct aud_stats_cpu {
    ulong_t aud_hdr1_recs;     /* # audit records built                       */
    ulong_t aud_hdr2_recs;     /* unused                                      */
    ulong_t aud_sleep;         /* # sleeps against resource set               */
    ulong_t aud_flush1;        /* # implicit flushes into driver buffer       */
    ulong_t aud_flush2;        /* # explicit flushes into driver buffer       */
    ulong_t aud_overflow1;     /* # overflow hndlr calls for syscalls         */
    ulong_t aud_overflow2;     /* # overflow hndlr calls for audgen()         */
    ulong_t aud_deselect;      /* # events deselected                         */
    ulong_t aud_recful;        /* # aborted attempts to add to a record       */
    ulong_t aud_ovfnd;         /* # overflow hndlr calls with no data         */
    ulong_t aud_ovf[8];        /* breakdown of overflow hndlr callers         */
#define AUD_OVFCOU_AUD5B 0     /* INSERT_AUD5B                                */
#define AUD_OVFCOU_AUD0  1     /* INSERT_AUD0 (audgen)                        */
#define AUD_OVFCOU_AUD0B 1     /* INSERT_AUD0B                                */
#define AUD_OVFCOU_AUD1  2     /* INSERT_AUD1                                 */
#define AUD_OVFCOU_AUD2  3     /* INSERT_AUD2 (audgen)                        */
#define AUD_OVFCOU_AUD3  4     /* INSERT_AUD3                                 */
#define AUD_OVFCOU_AUD4  5     /* INSERT_AUD4                                 */
#define AUD_OVFCOU_AUD5  6     /* INSERT_AUD5 (audgen)                        */
#define AUD_OVFCOU_PRERECLOA 7 /* overflow check prior to loading params      */
    ulong_t aud_suspendpriv;   /* # events bypassed due to privilege          */
    ulong_t aud_maclevel;      /* # events bypassed due to mac level          */
    ulong_t n_read;            /* # /dev/audit device reads                   */
    ulong_t n_getn;            /* # AUDIOCGETN operations                     */
    ulong_t n_setn;            /* # AUDIOCSETN operations                     */
    ulong_t n_sel;             /* # select ops with data available            */
    ulong_t n_sleep;           /* # sleeps in /dev/audit driver               */
    ulong_t n_getpropl_call;   /* # audit getproplist calls                   */
    ulong_t n_getpropl_err;    /* # audit getproplist errors                  */
    ulong_t n_setpropl_call;   /* # audit setproplist, delproplist calls      */
    ulong_t n_setpropl_err;    /* # audit setproplist, delproplist errors     */
    ulong_t aud_badcall;       /* # bad calls into audit_rec_build            */
    ulong_t aud_missedrecs;    /* # dropped kernel network events             */
    long reserved[9];
/* 64 byte alignment */
};

#define AUD_STAT_COLLECT 1
#if AUD_STAT_COLLECT
/* collect stats for current processor, specified cpu, or specified processor */
#define AUD_STAT(field)             current_processor()->aud.astats.field++
#define AUD_STAT_CPU(ncpu,field)    cpu_to_processor(ncpu)->aud.astats.field++
#define AUD_STAT_PR(pr,field)       \
do { \
        if (pr) (pr)->aud.astats.field++; \
} while (0)

#else
#define AUD_STAT(field)
#define AUD_STAT_CPU(ncpu,field)
#define AUD_STAT_PR(pr,field)
#endif /* AUD_STAT_COLLECT */

/* per-processor data  */
struct audit_per_processor {
    struct aud_buff_cpu abuf[2];
#ifdef _KERNEL
#define AUD_BUF_DFLT   0
#define AUD_BUF_NOBLK  1
#endif /* _KERNEL */
    struct aud_stats_cpu astats;   /* audit per-processor stats */
/* 64 byte alignment */
};

/* deprecated */
#define AUD_BUF_KERN   0
#define AUD_BUF_DAEMON 1


/* macros used for auditmask lengths
    kernel space: used as int-mask
    user space: used as char-mask
*/
#define AUDMASK_LEN(x)       ((x) > 0 ? ((x)-1)/(NBBY>>1)+1 : 0)
#define SYSCALL_MASK_LEN     AUDMASK_LEN(N_SYSCALLS)
#define TRUSTED_MASK_LEN     AUDMASK_LEN(N_TRUSTED_EVENTS)
#define AUDIT_MASK_LEN       (SYSCALL_MASK_LEN+TRUSTED_MASK_LEN)
#define AUDINTMASK_LEN(x)    ((x) > 0 ? ((x)-1)/(WORD_BIT>>1)+1 : 0)
#define SYSCALL_INTMASK_LEN  AUDINTMASK_LEN(N_SYSCALLS)
#define TRUSTED_INTMASK_LEN  AUDINTMASK_LEN(N_TRUSTED_EVENTS)
#define AUDIT_INTMASK_LEN    (SYSCALL_INTMASK_LEN+TRUSTED_INTMASK_LEN)


/* macros used to adjust various auditmasks */
#define BYTE_IN_MASK(event)         ((event)>>2)
#define BITS_IN_BYTE(status,event)  ( (status) << ( (~(event) & ((NBBY>>1)-1)) << 1) )
#define WORD_IN_MASK(event)         ((event)>>4)
#define BITS_IN_WORD(status,event)  ( (status) << EVENT_SHIFT(event) )
#define EVENT_SHIFT(event)          \
    ((((event)&((WORD_BIT>>1)-1) | 0x3) - ((event)&0x3)) << 1)

/* adjust buf for system audit_mask by setting event succeed/fail bits */
#define A_SYSMASK_SET(buf,event,succeed,fail) \
    { if ( (event) >= MIN_TRUSTED_EVENT ) { \
        (buf)[BYTE_IN_MASK((event)-MIN_TRUSTED_EVENT)] &= ~BITS_IN_BYTE(0x3,(event)-MIN_TRUSTED_EVENT); \
        (buf)[BYTE_IN_MASK((event)-MIN_TRUSTED_EVENT)] |= \
            BITS_IN_BYTE(( ((succeed)<<1)|(fail) ),(event)-MIN_TRUSTED_EVENT); \
      } \
      else { \
        (buf)[BYTE_IN_MASK(event)] &= ~BITS_IN_BYTE(0x3,(event)); \
        (buf)[BYTE_IN_MASK(event)] |= BITS_IN_BYTE(( ((succeed)<<1)|(fail) ),(event)); \
      } \
    }

/* adjust buf for user audit_mask by setting event succeed/fail bits */
#define A_PROCMASK_SET(buf,event,succeed,fail) \
    { if ( (event) >= MIN_TRUSTED_EVENT ) { \
        (buf)[BYTE_IN_MASK((event)-MIN_TRUSTED_EVENT+N_SYSCALLS)] &= \
            ~BITS_IN_BYTE(0x3,(event)-MIN_TRUSTED_EVENT+N_SYSCALLS); \
        (buf)[BYTE_IN_MASK((event)-MIN_TRUSTED_EVENT+N_SYSCALLS)] |= \
            BITS_IN_BYTE(( ((succeed)<<1)|(fail) ),(event)-MIN_TRUSTED_EVENT+N_SYSCALLS); \
      } \
      else { \
        (buf)[BYTE_IN_MASK(event)] &= ~BITS_IN_BYTE(0x3,(event)); \
        (buf)[BYTE_IN_MASK(event)] |= BITS_IN_BYTE(( ((succeed)<<1)|(fail) ),(event)); \
      } \
    }

/* adjust buf for siteauditmask by setting event succeed/fail bits */
#define A_SITEMASK_SET(buf,event,succeed,fail) \
    { if ( (event) >= MIN_SITE_EVENT ) { \
        (buf)[BYTE_IN_MASK((event)-MIN_SITE_EVENT)] &= \
            ~BITS_IN_BYTE(0x3,(event)-MIN_SITE_EVENT); \
        (buf)[BYTE_IN_MASK((event)-MIN_SITE_EVENT)] |= \
            BITS_IN_BYTE(( ((succeed)<<1)|(fail) ),(event)-MIN_SITE_EVENT); \
      } \
    }

/* adjust buf for mach audit_mask by setting event succeed/fail bits */
#define A_MACHMASK_SET(buf,event,succeed,fail) \
    {   (buf)[BYTE_IN_MASK(event)] &= ~BITS_IN_BYTE(0x3,(event)); \
        (buf)[BYTE_IN_MASK(event)] |= BITS_IN_BYTE(( ((succeed)<<1)|(fail) ),(event)); \
    }


#ifdef _KERNEL
#include "bin_compat.h"

extern lock_data_t lk_audit;
 
extern int audit_mask_sync;
#define AUD_READ_LOCK()		lock_read(&lk_audit)
#define AUD_READ_UNLOCK()	lock_done(&lk_audit)
#define AUD_WRITE_LOCK()	lock_write(&lk_audit)
#define AUD_WRITE_UNLOCK()	lock_done(&lk_audit)
#define AUD_LOCK_INIT()		lock_setup(&lk_audit, lk_audit_info, TRUE)

/* macros to check auditability of event according to auditmask; 2 bits/event */
#define EVENT_BITS(mask,event)  (((mask)[WORD_IN_MASK(event)] >> \
					EVENT_SHIFT(event)) & 0x3)
#define AUDIT_EVENT_K(event)    (syscallauditmask[(event)])
#define AUDIT_EVENT_U(event)    (EVENT_BITS(u.u_auditmask,(event)))
#define AUDIT_EVENT_T(event)    (EVENT_BITS(trustedauditmask,(event)))
#define AUDIT_EVENT_S(event)    (EVENT_BITS(siteauditmask,(event)))

#define DO_AUD_ERRSTAT(event_mask,error) \
    ((event_mask) & (((error) == 0) ? 0x02 : 0x01))

#define DO_AUD(event) \
    ((u.u_audit_cntl & (AUDIT_OFF|AUDIT_SYSCALL_OFF)) ? 0 : \
    ((u.u_audit_cntl & AUDIT_AND) ? \
        AUDIT_EVENT_K(event) & AUDIT_EVENT_U(event) : \
    ((u.u_audit_cntl & AUDIT_USR) ? \
        AUDIT_EVENT_U(event) : \
        AUDIT_EVENT_K(event) | AUDIT_EVENT_U(event) )))

#define DO_TRUSTED_AUD(event) \
    ((u.u_audit_cntl & AUDIT_OFF) ? 0 : \
    ((u.u_audit_cntl & AUDIT_AND) ? \
        AUDIT_EVENT_T((event)-MIN_TRUSTED_EVENT) & AUDIT_EVENT_U((event)-MIN_TRUSTED_EVENT+N_SYSCALLS) : \
    ((u.u_audit_cntl & AUDIT_USR) ? \
        AUDIT_EVENT_U((event)-MIN_TRUSTED_EVENT+N_SYSCALLS) : \
        AUDIT_EVENT_T((event)-MIN_TRUSTED_EVENT) | AUDIT_EVENT_U((event)-MIN_TRUSTED_EVENT+N_SYSCALLS) )))

#define DO_KERN_TRUSTED_AUDIT(event, error) \
    (audswitch && (AUDIT_EVENT_T((event)-MIN_TRUSTED_EVENT) & ((error) ? 0x01 : 0x02)))


#if BIN_COMPAT
#define DO_HABITAT_AUD(habitat,event,error) \
    ( u.u_audit_cntl & AUDIT_HABITAT_USR \
    || \
    (!(u.u_audit_cntl & (AUDIT_OFF|AUDIT_SYSCALL_OFF|AUDIT_USR)) && \
    habitats[(habitat)] && habitats[(habitat)]->cm_auditmask && \
    (EVENT_BITS(habitats[(habitat)]->cm_auditmask, (event)) & \
        (((error) == 0) ? 0x02 : 0x01))) )

#define DO_AUDIT(event,error) \
	(audswitch && \
		(!hbval(event) ? \
			(DO_AUD(event) & (((error) == 0) ? 0x02 : 0x01)) \
		: \
			(DO_HABITAT_AUD(hbval(event),syscval(event),(error)))))

#define DO_AUDEVENT(event) \
	(audswitch ? \
		(!hbval(event) ? \
			DO_AUD(event) & 0x03 \
	 	: \
	        	(((u.u_audit_cntl & AUDIT_HABITAT_USR) || \
        		  (!(u.u_audit_cntl & \
			     (AUDIT_OFF|AUDIT_SYSCALL_OFF|AUDIT_USR)))) && \
			 habitats[(hbval(event))] && \
			 habitats[(hbval(event))]->cm_auditmask ? \
				(EVENT_BITS(habitats[(hbval(event))]->cm_auditmask, \
				 (syscval(event))) & 0x03 ) \
			: \
				0) \
		) \
	: 0)


#else /* BIN_COMPAT */
#define DO_AUDIT(event,error) \
	(audswitch && (DO_AUD(event) & (((error) == 0) ? 0x02 : 0x01)))

#define DO_AUDEVENT(event) \
	(audswitch && (DO_AUD(event) & 0x03)) 

#endif /* BIN_COMPAT */

/* perform audit_rec_build if auditing on for specified event/proc */
#if BIN_COMPAT
#define AUDIT_CALL(event,error,args,retval,flags,param) \
do { \
	u_int c, h, m, *mp; \
	if (audswitch && !((c = u.u_audit_cntl) & (AUDIT_OFF|AUDIT_SYSCALL_OFF))) { \
		if (!(h = hbval(event))) { \
			m = AUDIT_EVENT_U(event); \
			if (c & AUDIT_AND) \
				m &= AUDIT_EVENT_K(event); \
			else if (!(c & AUDIT_USR)) \
				m |= AUDIT_EVENT_K(event); \
		} else { \
			if (c & AUDIT_HABITAT_USR) \
				m = 0x03; \
			else if (!(c & AUDIT_USR) && \
			    habitats[h] && (mp = habitats[h]->cm_auditmask)) \
				m = EVENT_BITS(mp, syscval(event)); \
			else \
				m = 0; \
		} \
		if (m & (((error) == 0) ? 0x02 : 0x01)) \
			audit_rec_build((event), (args), (error), (retval), \
				(flags), (param)); \
	} \
} while (0)

#else /* BIN_COMPAT */

#define AUDIT_CALL(event,error,args,retval,flags,param) \
do { \
	u_int c, m; \
	if (audswitch && !((c = u.u_audit_cntl) & (AUDIT_OFF|AUDIT_SYSCALL_OFF))) { \
		m = AUDIT_EVENT_U(event); \
		if (c & AUDIT_AND) \
			m &= AUDIT_EVENT_K(event); \
		else if (!(c & AUDIT_USR)) \
			m |= AUDIT_EVENT_K(event); \
		if (m & (((error) == 0) ? 0x02 : 0x01)) \
			audit_rec_build((event), (args), (error), (retval), \
				(flags), (param)); \
	} \
} while (0)
#endif /* BIN_COMPAT */


/* version of AUDIT_CALL which calls a function instead of inline expansion;
   specifically to decrease text space growth
*/
#define AUDIT_CALL2(event,error,args,retval,flags,param) \
do { \
	if (audswitch) \
        	audit_call((event), (error), (args), (retval), (flags), \
			(param)); \
} while (0)


/* audit_rec_build operations */
#define AUD_VNO              0x001
#define AUD_HDR              0x002
#define AUD_PRM              0x004
#define AUD_RES              0x008
#define AUD_HPR              (AUD_HDR|AUD_PRM|AUD_RES)
#define AUD_H2PR             (AUD_HDR2|AUD_PRM|AUD_RES)
#define AUD_VHPR             (AUD_VNO|AUD_HDR|AUD_PRM|AUD_RES)
#define AUD_FLU              0x010
#define AUD_PTR              0x020
#define AUD_LCL              0x040
#define AUD_LCK              0x080
#define AUD_GEN              0x100
#define AUD_DBG              0x200
#define AUD_HDR2             0x400
#define AUD_NB               0x800

/* kernaudwrite flags */
#define AUD_KAW_FLUSH        0x001
#define AUD_KAW_NB           0x002


/* misc values used in building audit records */
#define SIZ_TOKEN            1
#define AUD_RECTAIL          (3*SIZ_TOKEN + 2*sizeof(int) + sizeof(long))
/* base size for audit data buffer */
#define AUD_MINBUF_SIZ (AUD_BUF_SIZ<<2)
#define AUDSIZE(x) \
    ( ((x)*1024) < AUD_MINBUF_SIZ ? AUD_MINBUF_SIZ : ((x)*1024) )

/* exportfs */
#define	AUD_EVENT_HDR_FIXLEN	((16*SIZ_TOKEN)+(15*sizeof(int))+sizeof(long))

/* global data */
#ifndef REPLICATED
#define REPLICATED
#endif
extern REPLICATED u_int  syscallauditmask[];
extern REPLICATED u_int  trustedauditmask[];
extern u_int  *siteauditmask;
extern REPLICATED int    n_sitevents;
extern REPLICATED u_int  audsize;
extern REPLICATED u_int  audstyle;
extern struct aud_log aud_log;
extern REPLICATED boolean_t audswitch;

u_long audit_rec_build(u_int, long *, int, long, u_int, char *);
void audit_call(int, int, long *, long, u_int, char *);
void audprintf ( char *fmt, ... );

/*
  encodings for sysent[].aud_param
  (cap designation indicates security level must be recorded)
    0:   nothing
    1:   string (kernel-space)
    2:   mode_t
    3:   long
    4:   *int (user-space)
    5:   int[], length in prev param (user-space)
    6:   privvec_t
    7:   label (ir)
    8:   record continuation marker
    9:   subevent
    a/A: int
    b/B: *char (user-space)
    c/C: fd
    d/D: data, length in next param (user-space)
    e/E: local bsd 4.4 sockaddr (kernel-space)
    f/F: remote bsd 4.4 sockaddr (kernel-space) 
    g/G: string, length in next param (user-space)
    h/H: struct sockaddr *addr, length in next param (user-space)
    i/I: struct msghdr *msg (4.3) (user-space)
    j/J: tcp flags, int (kernel-space)
    k/K: msgctl operations (user-space)
    l/L: uid_t
    m/M: gid_t
    n/N: semctl operations (similar to msgctl operations)
    o/O: shmctl operations (similar to msgctl operations)
    p/P: dev_t
    q/Q: pid_t
    r/R: filename (kernel-space)
    s/S: fd[2] (for socketpair) (user-space)
    u  : flock structure (kernel-space)
    t/T: struct msghdr *msg (4.4) (user-space)
    v/V: exportfs operation (user-space)
    w/W: *char (user-space), inode info taken from retval (obj creat)
    x/X: *char (user-space), inode info taken from extra namei (obj creat)

  last field in sysent[].aud_param entry (entries may be combined):
    1:   apply audit object deselection model
    2:   audit despite selection model
    4:   perform audit from system call's code
*/

#define AUD_DATA_ACCESS          FREAD
#define AUD_OVERRIDE_OBJ_SEL     2
#define SELF_AUDIT              '4'


#if MLS_AUDIT
#define AUDIT_ENABLED (audswitch)
#endif /* MLS_AUDIT */

#define AUD_ASSERT 0
#endif /* _KERNEL */


#if !defined(_KERNEL)

extern char *syscallnames[];
extern char *trustedevent[];

#ifdef _NO_PROTO

extern int audit_change_mask();
extern int audit_build_mask();
extern void audit_change_mask_done();
extern int aud_aliasent();
extern int aud_alias_event();
extern int aud_sitevent();
extern int aud_sitevent_num();

#else /* !_NO_PROTO */

#if defined(__STDC__) || defined(__cplusplus)
#ifdef __cplusplus
extern "C"
{
#endif

extern int audit_change_mask(char const * , char * , char * , char * , int , char * , int );
extern int audit_build_mask(char const * , char * , char * , int );
extern void audit_change_mask_done(void);
extern int aud_aliasent(int , char * , int );
extern int aud_alias_event(char const * , int , char * , int );
extern int aud_sitevent(int , int , char * , char * );
extern int aud_sitevent_num( char const * , char const * , int * , int * );
extern int audcntl(int, char *, int, int, uid_t, pid_t);
extern int audgen(int, char *, char *[], char *, long *);

#ifdef __cplusplus
}
#endif
#endif /* __STDC__ || __cplusplus */

#endif /* !_NO_PROTO */

#endif /* !defined(_KERNEL) */
#endif /* __AUDIT__ */
