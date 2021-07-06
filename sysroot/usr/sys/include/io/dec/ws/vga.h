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
 * @(#)$RCSfile: vga.h,v $ $Revision: 1.1.14.2 $ (DEC) $Date: 1997/02/21 18:26:29 $
 */

#ifndef _VGA_H_
#define _VGA_H_

#ifdef _KERNEL

/* 
 * driver functions needed for generic VGA fallback 
 */
extern int vgaprobe(vm_offset_t addr, struct controller *ctlr);
extern int vgaattach(struct controller *ctlr);

#endif /* _KERNEL */

#endif /* _VGA_H_ */


