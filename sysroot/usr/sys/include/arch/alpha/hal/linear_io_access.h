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
 * @(#)$RCSfile: linear_io_access.h,v $ $Revision: 1.1.4.2 $ (DEC) $Date: 1998/08/06 15:27:50 $
 */
#include <arch/alpha/hal/platform.h>
/*
 * externals used for io/access functions
 */
extern long	linear_read_io_port(io_handle_t iohandle, 
				    int width, 
				    int type);

extern void	linear_write_io_port(io_handle_t iohandle, 
				     int width, 
				     int type, 
				     long data);

#ifdef PLATFORM_USE_HAL_SWITCH
extern int	linear_io_blockread(io_handle_t src, 
				    vm_offset_t dest, 
				    u_long count,
				    u_long size);

extern int	linear_io_blockwrite(vm_offset_t src, 
				     io_handle_t dest, 
				     u_long count,
				     u_long size);

extern int	linear_io_blockclear(io_handle_t dest, 
				     u_long count,
				     u_long size);

extern int	linear_io_blockexchange(io_handle_t src, 
					io_handle_t dest, 
					u_long count,
					u_long size);

#else
extern int	linear_io_copyin(io_handle_t src, 
				 vm_offset_t dest, 
				 u_long count);

extern int	linear_io_copyout(vm_offset_t src, 
				  io_handle_t dest, 
				  u_long count);

extern int	linear_io_zero(io_handle_t dest, 
			       u_long count);

extern int	linear_io_copyio(io_handle_t src, 
				 io_handle_t dest, 
				 u_long count);
#endif

extern io_handle_t	linear_busphys_to_iohandle(u_long bus_addr, 
						   int flags, 
						   struct controller *ctlrp);

extern u_long	linear_iohandle_to_phys(io_handle_t iohandle, 
					long flags);

extern u_long	linear_pci_config(u_long cycle, 
				  u_int size, 
				  u_long write_data, 
				  int flags);
