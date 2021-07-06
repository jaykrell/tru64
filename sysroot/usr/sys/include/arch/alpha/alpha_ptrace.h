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

#define REG_BASE	0
#define NGP_REGS	32
#define NFP_REGS	32

#define GPR_BASE	REG_BASE
#define FPR_BASE	(GPR_BASE+NGP_REGS)
#define	PC		(FPR_BASE+NFP_REGS)
#define SPR_PS		(PC+1)
#define SPR_FPCR	(SPR_PS+1)
#define NPTRC_REGS	(SPR_FPCR+1)
