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
 * @(#)$RCSfile: sysdev_info.h,v $ $Revision: 1.1.11.1 $ (DEC) $Date: 2002/01/30 02:15:17 $
 */
#ifndef SYSDEV_INFO
#define SYSDEV_INFO

#include <sys/radset.h>

/*
 * Kernel structure mapped into a users address
 * space when the psuedo device sysdev_info is
 * mmap() by a application.
 */


typedef struct sysdev_cpuinfo {
	int		enabled;		/* CPU was enabled */
	int		spare1;
	long		morepad[7];		/* pad up to 64 bytes */

	/* Load info */
	long	load_avg;
	long    rt_load_avg;
	long 	int_load_avg;
	long	idle_avg;
	long	pad[4];	

} sysdev_cpuinfo_t;	

typedef sysdev_cpuinfo_t *sysdev_cpuinfo_p;

typedef struct sysdev_info {

	/* Original sysdev_info. Necessary to maintain for compatibility */
 	struct timeval	tv;
	struct timezone	tz;
	long lbolt;
	long sysdev_pad1[5];

	/* Read-mostly data. Not changed after boot */
	long	load_scale;	/* Scale factor for load values */
	int	cpu_slots;	/* Max # of cpus on current system */
	int	nrads;		/* Max # of rads on current system */
	long	sysdev_pad2[6];		

	/* Read-mostly sysdev meta-info */
	long		cpuinfo_start;	/* Offset from base of sysdev for */
					/* per-processor info */
	size_t		cpuinfo_size;	/* size of each cpuinfo element	*/
	int		cpuinfo_load;	/* Is load information being updated? */
	int		cpuinfo_hopoff;	/* Offset of hoptab from cpuinfo start	*/
	int		cpuinfo_radoff;	/* Offset of radtab from cpuinfo start	*/
	int		sysdev_pad3[9];

} sysdev_info_t;

typedef sysdev_info_t *sysdev_info_p;

#endif
