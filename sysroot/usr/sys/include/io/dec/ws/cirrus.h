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
 * @(#)$RCSfile: cirrus.h,v $ $Revision: 1.1.6.2 $ (DEC) $Date: 1997/02/21 18:24:39 $
 */

#ifndef _CIRRUS_H_
#define _CIRRUS_H_

#ifdef _KERNEL
#include <io/dec/ws/vgareg.h>

/*
 *  Cirrus registers
 */
typedef struct {
  vgaHWRec std;          /* std IBM VGA registers - must be first! */

  /* CIRRUS special registers */
  unsigned char SR6;
  unsigned char SR7;
  unsigned char SRE;
  unsigned char SRF;
  unsigned char SR12;
  unsigned char SR13;
  unsigned char SR16;
  unsigned char SR17;
  unsigned char SR1E;
  unsigned char GR9;
  unsigned char GRA;
  unsigned char GRB;
  unsigned char GRE;
  unsigned char CR19;
  unsigned char CR1A;
  unsigned char CR1B;
  unsigned char CR27;
} vgaCIRRUSRec, *vgaCIRRUSPtr;

#endif /* _KERNEL */

#endif /* _CIRRUS_H_ */
