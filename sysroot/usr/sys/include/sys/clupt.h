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
 * @(#)$RCSfile: clupt.h,v $ $Revision: 1.1.6.1 $ (DEC) $Date: 2000/09/28 19:38:24 $
 */
/*	clupt.h - cluster partition offsets
 *
 *	The cluster partition resides on each member
 * 	disk and the quorum disk as the "h" partition.
 *	It's partition type is "cnx". 
 *	It's size is 1 Megabyte.
 *
 *	It is divided into three separate sections.
 *
 *		+++++++++++++++++++++++++
 *		|	quorum		|
 *		|	segment		|
 *		_________________________
 *		| partition in time PIT	|
 *		|	segment		|
 *  Quorum	_________________________
 *  Division	|AdvFS cluster_root devs|
 *		|	segment		|
 *  0-256K	_________________________
 *		|CLSM cluster root devs	|
 *		|	segment		|
 *		_________________________
 *		|	SPARE SPACE	|
 *		|	segment		|
 *		|			|
 *		+++++++++++++++++++++++++
 *		|	quorum		|
 *		|	segment		|
 *		_________________________
 *		| partition in time PIT	|
 *		|	segment		|
 *  Member	_________________________
 *  Division	|AdvFS cluster_root devs|
 *		|	segment		|
 *  256-512K	_________________________
 *		|CLSM cluster root devs	|
 *		|	segment		|
 *		_________________________
 *		|	SPARE SPACE	|
 *		|	segment		|
 *		|			|
 *		+++++++++++++++++++++++++
 *		|	Unused SPACE	|
 * Unused	|			|
 * Division	|			|
 * 512K - 1 Meg	|			|
 *		|			|
 *		+++++++++++++++++++++++++
 *
 */

#ifndef _SYS_CLUPT_H_
#define _SYS_CLUPT_H_

#ifdef __cplusplus
extern "C" {
#endif

#define DKTYPENAMES
#include <sys/disklabel.h>

#define CNX_PARTITION		"h"	/* CNX partition resides on the "h" partition	*/
#define	CNX_PART_TYPE		fstypenames[FS_CNX] /* CNX partition type	*/
#define CNX_PART_SIZE		0x100000 	/* 1 Megabyte			*/

/*	definitions of cnx partition divisions	*/

#define CNX_QD_OFFSET		0x0		/* Quorum disk offset 		*/
#define CNX_QD_SIZE		0x40000		/* Quorum disk size 256K	*/
#define CNX_MEMB_OFFSET		0x40000		/* Member disk offset		*/
#define CNX_MEMB_SIZE		0x40000		/* Member disk size 256K	*/
#define CNX_UNUSED_OFFSET	0x80000		/* UNUSED 512K to 1Meg		*/
#define CNX_UNUSED_SIZE		0x80000		/*				*/

/*      definitions of cnx partition division segments	*/

#define CNX_QUORUM_OFFSET	0x0		/* Offset in division for QD segment	*/
#define CNX_QUORUM_SIZE		0x8000		/* Size of quorum segment = 64 K     	*/	
#define CNX_PIT_OFFSET		0xA000		/* Offset in division for PIT segment	*/
#define CNX_PIT_SIZE		0x2000		/* Size of PIT segment = 16 K     	*/
#define CNX_ADVFS_OFFSET	0xC000		/* Offset in division for AdvFS segment */
#define CNX_ADVFS_SIZE		0x2000		/* Size of AdvFS segment = 16 K		*/
#define CNX_CLSM_OFFSET		0xE000		/* Offset in division for CLSM segment	*/
#define CNX_CLSM_SIZE		0x2000		/* Size of CLSM segment = 16 K         	*/
#define CNX_SPARE_OFFSET	0x10000		/* Offset of SPARE segment		*/
#define CNX_SPARE_SIZE		0x10000		/* Size of SPARE segment		*/

/*      definitions for cnx partition configuration file */
#define CLUP_MAX_CSIZ		1024		/* Maximum record size for config file  */
#define CLUP_REC_MARK 		"::"		/* END and BEGIN of record mark		*/
#define CLUP_FLD_SEP		':'		/* field separator			*/
#define CLUP_ITEM_SEP		','		/* Separate items within field data	*/
#define	CLUP_PART_SEP		'|'		/* Separate parts of an item 		*/
#define CLUP_PARTH		'h'		/* cnx partition is 'h'			*/
#define CLUP_ID_SIZE		4		/* field identifier+separator size	*/
#define CLUP_TYP_NAME		"TYP:"		/* TYP field identifier+separator	*/
#define CLUP_LSM_NAME		"LSM:"		/* LSM field identifier+separator	*/
#define CLUP_CFS_NAME		"CFS:"		/* CFS field identifier+separator	*/
#define CLUP_CNX_NAME		"CNX:"		/* CNX field identifier+separator	*/

/*
 * The following structure describes the contents for the AdvFS 
 * portion of the CNX partition contained on boot disks and quorum disk.
 */
typedef struct cluster_root_info  {
	ulong	magic_num;		/* CFS magic number for data */
        ulong   seq_num;		/* CFS cluster root data seq num */
        ulong   num_devs;		/* Number of volumes in cluster_root domain */
        ulong   dev_inprog;		/* Dev with rm/addvol operation in progress */
					/* when the server node died */
        ulong   devt[256];		/* Dev_ts for all volumes needed for */
					/* cluster_root domain */
}       cluster_root_info_t;

#define CFS_ADVFS_ROOT_MAGIC	0x42534

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _SYS_CLUPT_H_ */

