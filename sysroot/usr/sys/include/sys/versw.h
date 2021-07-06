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
 * @(#)$RCSfile: versw.h,v $ $Revision: 1.1.7.3 $ (DEC) $Date: 2001/03/28 19:38:32 $
 */
/************************************************************************/
/*      versw.h - version switch defines 	                    	*/
/************************************************************************/
/*									*/
/*	Version identifier interfaces					*/
/*									*/
/*	VERSW()	- Used in a base release to enable new functions when   */
/*		  all cluster members are running the new version	*/
/*									*/
/*	VERSW_VARIANT() - Used in a base release variant to enable new  */
/*		  functions when all cluster members are running the    */
/*		  new version						*/
/*									*/
/*	VERSW_PATCH() - Used in a patch release to enable new functions */
/*		when  all cluster members are running the new version   */
/*									*/
/*	NOTE: These interfaces assume that any version can only roll to */
/*		one distinct version. The only exceptions to this is    */
/*		the VARIANT and PATCH interfaces which can provide an   */
/*		additional level of version switching. But they cannot  */
/*		be used on consequtive patches or variant releases 	*/
/*		without removing the previous instanciations		*/
/*									*/
/*      Version.id - version identifier   	  			*/
/*                                     					*/
/*      The file /usr/sys/conf/version.id is edited by the 		*/
/*	release build process to contain unigue version         	*/
/*	identifier:                      				*/
/*                                                              	*/
/*              BUILTIN_VERS_ID_HIGH and BUILTIN_VERS_ID_LOW    	*/
/*                                                              	*/
/*      The BUILTIN_VERS_ID_HIGH is the most significant        	*/
/*      unsigned long and the BUILTIN_VERS_ID_LOW is the least  	*/
/*      significant unsigned long of the version identifier.    	*/
/*									*/
/*                                                              	*/
/*	Version identifier bit fields				        */
/*								        */
/*	BUILTIN_VERS_ID_HIGH:						*/
/*									*/
/*   64      56      48      40      32      24      16      8       0  */
/*   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |	*/
/*   |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||	*/
/*   |     |    |    |    |    |     |     |   |               |     |	*/
/*   ^-----^-----^---^----^----^-----^-----^---^---------------^-----^	*/
/* bits:6    6     4    5    5    6     6    4        16          6	*/
/*     Ver  Ver   Resd  |  Resd   |     |   Resd    Base Rev     base	*/
/*    Major Minor       |Version-Variant|                        spin	*/
/*                   Letter      Num   SubNum				*/
/*Like:"V6.8"	       "A"	    "3.2"				*/
/*									*/
/*									*/
/* 	BUILTIN_VERS_ID_LOW:						*/
/*									*/
/*   64      56      48      40      32      24      16      8       0	*/
/*   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |	*/
/*   |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||	*/
/*   |                   |               |     |    |       |   |    |	*/
/*   ^-------------------^---------------^-----^----^-------+---+----^	*/
/* bits:      20                 16         6      5     17 (8+4+5)	*/
/*         Reserved             Patch      Patch  Resd    Build Date	*/
/*                               Rev       spin           year 2255 	*/
/*									*/
/* This version.id supports following version strings:			*/
/*									*/
/*   V5.3A6.23 -> where:  5 = major version       (0-63)		*/
/*                        3 = minor version       (0-63)		*/
/*                        A = Variant letter      (A-Z+others up to 63) */
/*                        6 = Variant number      (0-63)		*/
/*                        23= Variant subnumber   (0-63)		*/
/*									*/
/*        Base revs  (0-65536)						*/
/*        Base spins (0-63)						*/
/*									*/
/*        Patch revs (0-65536)						*/
/*        Patch spins(0-63)						*/
/*									*/
/************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include <conf/version.id> 


/*	returns from the VERSW() function	*/

#define VERSW_ENABLE            0       /* enable all new functions 		*/
#define VERSW_DISABLE           1       /* disable new, incompatible functions 	*/
#define VERSW_TRANSITION        2       /* disable new, incompatible functions 	*/
                                        /* and handle any new capabilities originating */
					/* from other cluster members          	*/

/* versw base masks used in VERSW() */
#define	BASE_HIGH_MASK         0xFFFF000000000000     /* BASE O/S high version id mask */
#define	BASE_LOW_MASK          0x0000000000000000     /* BASE O/S low version id mask  */

/* versw base + variant rev masks used in VERSW_VARIANT() */
#define	VARIANT_HIGH_MASK      0xFFFFFFFFFC000000     /* VARIANT O/S high version id mask */
#define	VARIANT_LOW_MASK       0x0000000000000000     /* VARIANT O/S low version id mask  */

/* versw base + variant + patch rev masks used in VERSW_PATCH() */
#define	PATCH_HIGH_MASK        0xFFFFFFFFFC000000      /* BASE O/S high version id mask */
#define	PATCH_LOW_MASK         0x00000FFFF0000000      /* BASE O/S low version id mask  */

extern int versw( ulong high_vers, ulong low_vers);

/****************************************************************/
/*      VERSW function definitions                              */
/****************************************************************/
/* The VERSW_SPECIFIC is only used when overlapping Versions are beging switched */
/*  VERSW_SPECIFIC(int majVers, int minVers, char varLet, int varMaj, int varMin, int baserevspin, int ptchRev) */

#define VERSW_SPECIFIC(majVers, minVers, varLet, varMaj, varMin, baserevspin, ptchRev) \
	(( varLet != NULL && varLet >= 'A' && varLet <= 'Z')                \
	   ? versw((((ulong) majVers << 58) | ((ulong) minVers << 52) | ((ulong) (varLet - '@') << 43) | \
                  ((ulong) varMaj << 32) | ((ulong) varMin << 26)) | (ulong) baserevspin, ((ulong) ptchRev << 28)) \
    	   : versw((((ulong) majVers << 58) | ((ulong) minVers << 52)) | (ulong) baserevspin , ((ulong) ptchRev << 28)))

#define VERSW()  versw((VARIANT_HIGH_MASK & BUILTIN_VERS_ID_HIGH),(VARIANT_LOW_MASK & BUILTIN_VERS_ID_LOW))

#ifdef __cplusplus
} /* extern "C" */
#endif
