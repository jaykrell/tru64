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
 * @(#)$RCSfile: pci_common_intr_handler.h,v $ $Revision: 1.1.5.2 $ (DEC) $Date: 1999/04/05 11:40:32 $
 */

#ifndef _PCI_COMMON_INTR_HANDLER_H_
#define _PCI_COMMON_INTR_HANDLER_H_

#include <sys/types.h>
#include <io/common/handler.h>

/*
 * External functions used for interrupt handling
 */

extern ihandler_id_t	pci_intline_handler_add(int slot, 
					       u_int intr_mask, 
					       struct handler_intr_info *intr_infop, 
					       struct bus *busp);

extern int	pci_intline_handler_del(shared_intr_info_t *sip, 
				       struct bus *busp);

extern int	pci_intline_handler_enable(shared_intr_info_t *sip, 
					  struct bus *busp);

extern int	pci_intline_handler_disable(shared_intr_info_t *sip, 
					   struct bus *busp);

extern int 	pci_intline_option_enable(int intr_num);

extern int 	pci_intline_option_disable(int intr_num);


extern ihandler_id_t	pic_handler_add(int (*function)(), 
					int isa_irq_level, 
					caddr_t param,
					struct bus *busp);

extern int	pic_handler_del(shared_intr_info_t *sip);

extern int	pic_handler_enable(shared_intr_info_t *sip);

extern int	pic_handler_disable(shared_intr_info_t *sip);

extern int	pic_option_enable(shared_intr_info_t *sip);

extern int	pic_option_disable(shared_intr_info_t *sip);

extern int	pic_this_is_an_isa_handle(ihandler_id_t int_handler);

#endif /* _PCI_COMMON_INTR_HANDLER_H_ */
