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
 * |-----------------------------------------------------------|
 * | Copyright (c) 1991 MIPS Computer Systems, Inc.            |
 * | All Rights Reserved                                       |
 * |-----------------------------------------------------------|
 * |          Restricted Rights Legend                         |
 * | Use, duplication, or disclosure by the Government is      |
 * | subject to restrictions as set forth in                   |
 * | subparagraph (c)(1)(ii) of the Rights in Technical        |
 * | Data and Computer Software Clause of DFARS 52.227-7013.   |
 * |         MIPS Computer Systems, Inc.                       |
 * |         950 DeGuigne Drive                                |
 * |         Sunnyvale, CA 94086                               |
 * |-----------------------------------------------------------|
 */
/* $Header: /usr/sde/osf1/rcs/os/src/usr/include/alpha/opnames.h,v 1.1.6.2 1996/08/23 17:15:38 Craig_Neth Exp $ */
#ifndef _OPNAMES_H_
#define _OPNAMES_H_
#ifdef __cplusplus
extern "C" {
#endif

#if !defined(__alpha) && !defined(__mips64)
extern char *op_name[64];
extern char *spec_name[64];
extern char *bcond_name[32];
extern char *cop1func_name[64];
extern char *bc_name[32];
extern char *c0func_name[64];
extern char *c0reg_name[32];
#else /* defined(__alpha) */
extern char *op_name[64];
extern enum { PAL, OP, FOP, MEM, MEM1, FMEM, JSR, BRA, FBRA, ILL } format[64];
extern char *pal_name[192];
extern char *vfop_name[64];
extern char *ifop_name[64];
extern char *gfop_name[64];
extern char *mfop_name[64];
extern char *fmod_name[32];
extern char vmod_form[64];
extern char imod_form[64];
#endif /* defined(__alpha) */

#ifdef __cplusplus
}
#endif
#endif /* _OPNAMES_H_ */
