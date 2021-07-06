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
/*
 * @(#)$RCSfile: sec_objects.h,v $ $Revision: 1.1.7.3 $ (DEC) $Date: 1995/06/30 22:39:24 $
 */
#ifndef __SEC_OBJECTS__
#define __SEC_OBJECTS__ 1

/* Kernel objects */

#define	OT_REGULAR		1	/* regular file */
#define	OT_DIRECTORY		2	/* directory */
#define	OT_DEVICE		3	/* block, char device */
#define	OT_PIPE			4	/* named, unnamed pipe */
#define	OT_PROCESS		5	/* self explanatory */
#define	OT_MEMORY		6	/*	""	*/
#define	OT_STREAM		7	/* V.3 stream */
#define	OT_SOCKET		8	/* Berkeley socket */
#define	OT_SHARED_MEMORY	9	/* shared memory segment */
#define	OT_SEMAPHORE		10	/* semaphore */
#define	OT_MESSAGE_QUEUE	11	/* message queue */
#define OT_FILE_DESCR		12	/* file descriptor */
#define	OT_SYMLINK		13	/* symbolic link */

/* Authentication database objects */

#define	OT_PWD			14	/* /etc/passwd */
#define	OT_GRP			15	/* /etc/group */
#define	OT_PRPWD		16	/* Protected Password Database */
#define	OT_TERM_CNTL		17	/* Terminal Control Database */
#define	OT_FILE_CNTL		18	/* File Control Database */
#define	OT_DFLT_CNTL		19	/* System Default Database */
#define	OT_SUBSYS		20	/* Subsystem Database */
#define OT_DEV_ASG		21	/* Device Assignment Database */
#define OT_LP_CNTL		22	/* Printer Control Database */

/* Window System objects */

#define OT_WINDOW		23	/* top level window */
#define OT_OVERRIDE_WINDOW	24	/* override redirect window */
#define	OT_PIXMAP		25	/* pixmap */
#define	OT_COLORMAP		26	/* colormap */
#define	OT_PROPERTY		27	/* window property */
#define	OT_ATOM			28	/* window system atom */
#define OT_GC			30
#define OT_FONT			32	/* window system font */
#define OT_FONT_PATH		33	/* window system font path */
#define OT_SELECTION		34	/* window selection */
#define OT_INPUT_FOCUS		35	/* window input focus */
#define OT_CURSOR		36	/* window cursor */
#define OT_HOST_ACCESS_LIST	37	/* window system host access list */

/* More kernel objects */

#define	OT_FILE_NAME		29	/* sl and il for dir entries */

/* use 40 as next object type value */
#endif
