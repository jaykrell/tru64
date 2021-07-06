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
 * @(#)$RCSfile: atm.h,v $ $Revision: 1.1.15.2 $ (DEC) $Date: 1997/05/27 18:34:54 $
 */

#ifndef _SYS_ATM_H
#define _SYS_ATM_H

#include <sys/ioctl.h>
#include <netinet/in.h>

/*
 * IOCTL commands and structures for use in Asynchronous Transfer Mode (ATM)
 * management calls.
 */

/* Module Management Interface path definitions */

struct atm_mmi_path {
	char	*name;		/* name of module to manage */
	int	length;		/* length of name */
	long	key;		/* key to access module */
};

typedef struct atm_mmi_path atm_mmi_path_t;
typedef struct atm_mmi_path *atm_mmi_path_p;

struct atm_mmi_version {
       int	version;	/* version of the module's mgmt interface */
};

typedef struct atm_mmi_version atm_mmi_version_t;
typedef struct atm_mmi_version *atm_mmi_version_p;

#define GIOC_MMI_PATH		_IOW('g', 1, atm_mmi_path_t)
#define GIOC_MMI_CLOSE		_IOW('g', 127, atm_mmi_path_t)
#define GIOC_MMI_GETVERSION	_IOR('g', 2, atm_mmi_version_t)

#endif /* _SYS_ATM_H */
