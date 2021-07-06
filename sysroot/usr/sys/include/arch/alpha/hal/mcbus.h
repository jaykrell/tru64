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
 * @(#)$RCSfile: mcbus.h,v $ $Revision: 1.1.4.2 $ (DEC) $Date: 1996/04/01 23:45:27 $
 */

#ifndef __MCBUS_H__
#define __MCBUS_H__

#include <sys/types.h>

/*
 *      Definition of bus info structures.
 */
/*----------------------------------------------------------------*/
/* The agreed upon format for bus info structures is              */
/*                                                                */
/*      +----------------------------------------+                */
/*      |  Pointer to common info block          |                */
/*      |  (this is a struct common_bus_info *)  |                */
/*      +----------------------------------------|                */
/*      |  Bus specific data block               |                */
/*      +----------------------------------------+                */
/*                                                                */
/*----------------------------------------------------------------*/
/*
 * note: the common_bus_info looks like:
 * struct  common_bus_info
 *      {
 *       int            (**intr)();
 *       io_handle_t    sparse_io_base;
 *       io_handle_t    sparse_mem_base;
 *       vm_offset_t    dense_mem_base;
 *      };
 */
struct mcbus_bus_info {
        struct common_bus_info *common_bus_info;
        ulong                   gid_mid_base;
};

#endif 	/* __MCBUS_H__ */
