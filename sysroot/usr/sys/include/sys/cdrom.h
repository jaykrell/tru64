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
#ifndef	_SYS_CDROM_INCLUDE
#define	_SYS_CDROM_INCLUDE	1
#ifdef __cplusplus
extern "C" {
#endif

/*	
 *	@(#)$RCSfile: cdrom.h,v $ $Revision: 4.3.14.3 $ (DEC) $Date: 1997/08/11 17:03:25 $
 */ 
/*
 * <sys/cdrom.h> is specified by the Rock Ridge Interchange Protocol (rev 1.09)
 *
 * <cdfs/rrip.h> has the Rock Ridge stuff.
 * <cdfs/xcdr.h> has the XCDR stuff.
 */
#include <cdfs/rrip.h>
#include <cdfs/xcdr.h>

#ifndef _KERNEL
/*
 * Other stuff:
 */
#include <sys/time.h>

/* these are not specified by either XCDR or RRIP: */
extern void cdfs_tounixdate(time_t *ret_time, char yrs, char mon, char dys,
			char hrs, char mins, char secs, char gmtoff);
time_t rrip_convert_tf_ts(int, signed char *);
time_t cdfs_longdate(signed char *);
void xcdr_pvd(const char *, struct iso9660_pvd *);
#endif

#ifdef __cplusplus
}
#endif
#endif /* _SYS_CDROM_INCLUDE */
