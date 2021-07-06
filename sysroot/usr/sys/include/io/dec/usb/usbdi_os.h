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
 * @(#)$RCSfile: usbdi_os.h,v $ $Revision: 1.1.8.2 $ (DEC) $Date: 1999/08/03 08:01:09 $
 */
#ifndef _USBDI_OS_H_
#define _USBDI_OS_H_

#include <sys/types.h>
#include <io/common/iotypes.h>

/*
 * This file contains defines and declarations needed by the
 * USBDI which are OS specific.
 */

typedef U64 USBD_HANDLE;


/*
 * For Steel based releases...
 */
#define USB_STEEL

#endif /* _USBDI_OS_H_ */
