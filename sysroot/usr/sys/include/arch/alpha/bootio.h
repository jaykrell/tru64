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
 * @(#)$RCSfile: bootio.h,v $ $Revision: 1.1.4.3 $ (DEC) $Date: 1999/03/19 18:21:54 $
 */

#ifndef _BOOTIO_H_
#define _BOOTIO_H_

/*
 * The exported interfaces for the boot_XXX interface to
 * access the root filesystem (prior to vfs_mountroot) 
 * via console callbacks, ram disk, network disk, etc.
 */

#include <sys/types.h>

extern vm_size_t	boot_recordsize;

/* only valid value for "mode" for "boot_open()" */
#define BOOT_READ	(int)0

/* valid states for bootio */
#define BOOTIO_ST_DISABLED	0
#define BOOTIO_ST_RAMDISK	1
#define BOOTIO_ST_HARDDISK	2
#define BOOTIO_ST_NETWORK	3

int		boot_devopen();
int		boot_devclose();
int		boot_open(caddr_t file_name, int mode);
int		boot_close(int fd);
int		boot_read(int fd, caddr_t buf, vm_offset_t count);
int		boot_fsize(int fd);
int		boot_lseek(int fd, off_t offset, int ptr);

/*
 * Prototypes for dec/sas/bootio_net.c
 */
int		netboot_bootp_open(void);
int		netboot_tftp_open(char *, int);
int		netboot_tftp_close(void);
int		netboot_tftp_read(unsigned char *, int);
int		netboot_tftp_fsize(void);
int		netboot_lseek(off_t, int);

#endif /* _BOOTIO_H_ */

