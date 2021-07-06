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
 * @(#)$RCSfile: mach_proto.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1997/02/15 15:23:14 $
 */

#ifdef _KERNEL
host_priv_t	convert_port_to_host_priv(port_t);
host_t		convert_port_to_host(port_t);
port_t		convert_host_to_port(host_t);
port_t		convert_pset_to_port(processor_set_t);
port_t		convert_pset_name_to_port(processor_set_t);
port_t		convert_processor_to_port(processor_t);
port_t		convert_task_to_port(task_t);
port_t		convert_thread_to_port(thread_t);
processor_t	convert_port_to_processor(port_t);
processor_t	convert_port_name_to_processor(port_t);
processor_set_t	convert_port_to_pset(port_t);
processor_set_t	convert_port_to_pset_name(port_t);
task_t		convert_port_to_task(port_t);
thread_t	convert_port_to_thread(port_t);
vm_map_t	convert_port_to_map(port_t);

kern_return_t	catch_exception_raise(port_t, port_t, port_t, long,
					 long, long);
#endif /* _KERNEL */
