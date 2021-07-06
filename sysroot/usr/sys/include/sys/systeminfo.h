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
 * @(#)$RCSfile: systeminfo.h,v $ $Revision: 1.1.12.3 $ (DEC) $Date: 1999/05/06 19:11:11 $
 */
/*
 *  Module Name:
 *	systeminfo.h
 *
 *  Description:
 *	header file for SVR4 sysinfo() system call
 */
#ifndef _SYS_SYSTEMINFO_H
#define _SYS_SYSTEMINFO_H
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>

/*
 * Commands to sysinfo()
 */

#define SI_SYSNAME		1	/* return name of operating system */
#define SI_HOSTNAME		2	/* return name of node */
#define SI_RELEASE 		3	/* return release of operating system */
#define SI_VERSION		4	/* return version field of utsname */
#define SI_MACHINE		5	/* return kind of machine */
#define SI_ARCHITECTURE		6	/* return instruction set arch */
#define SI_HW_SERIAL		7	/* return hardware serial number */
#define SI_HW_PROVIDER		8	/* return hardware manufacturer */
#define SI_SRPC_DOMAIN		9	/* return secure RPC domain */
/*
 * These commands are unpublished interfaces to sysinfo().
 */
#define SI_SET_HOSTNAME		258	/* set name of node */
					/*  -unpublished option */
#define SI_SET_SRPC_DOMAIN	265	/* set secure RPC domain */
					/* -unpublished option */
#define SI_SET_SYSNAME		259	/* set name of system */
					/*  -unpublished option */

#ifdef __alpha
/*
 * Definitions for the system V sysinfo system call: sysv_sysinfo()
 * These used to be in utsname.h but that file seems to be gone in 
 * OSF/1 for the alpha.
 */

#define ARCHITECTURE		"alpha"	/* architecture type */
#endif /* __alpha */

#ifdef __ia64__
#define ARCHITECTURE		"IA64"	/* architecture type */
#endif /* __ia64__ */

#ifndef _KERNEL
int sysinfo __((int, char *, long));
#endif

#ifdef __cplusplus
}
#endif
#endif	/* _SYS_SYSTEMINFO_H */
