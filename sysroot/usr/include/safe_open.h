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
 * @(#)$RCSfile: safe_open.h,v $ $Revision: 1.1.12.1 $ (DEC) $Date: 2002/05/03 13:28:59 $
 */

#ifndef	_SAFE_OPEN_H_
#define	_SAFE_OPEN_H_ 1

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

/* Define the flag bits for the function. */
enum opn_flags_enum {
	OPN_blocking = 0,	/* assign in Lilliputian order (see IEN 137) */
#define	OPN_BLOCKING	(1UL<<OPN_blocking)
	OPN_type_dir,
#define	OPN_TYPE_DIR	(1UL<<OPN_type_dir)
	OPN_type_symlink,
#define	OPN_TYPE_SYMLINK	(1UL<<OPN_type_symlink)
	OPN_type_fifo,
#define	OPN_TYPE_FIFO	(1UL<<OPN_type_fifo)
	OPN_type_chr,
#define	OPN_TYPE_CHR	(1UL<<OPN_type_chr)
	OPN_type_blk,
#define	OPN_TYPE_BLK	(1UL<<OPN_type_blk)
	OPN_relative,
#define	OPN_RELATIVE	(1UL<<OPN_relative)
	OPN_trust_starting_dirs,
#define	OPN_TRUST_STARTING_DIRS	(1UL<<OPN_trust_starting_dirs)
	OPN_trust_group,
#define	OPN_TRUST_GROUP	(1UL<<OPN_trust_group)
	OPN_trust_parent_dirs,
#define	OPN_TRUST_PARENT_DIRS	(1UL<<OPN_trust_parent_dirs)
	OPN_trust_nlinks,
#define	OPN_TRUST_NLINKS	(1UL<<OPN_trust_nlinks)
	OPN_trust_sticky_bit,
#define	OPN_TRUST_STICKY_BIT	(1UL<<OPN_trust_sticky_bit)
	OPN_trust_dir_owners,
#define	OPN_TRUST_DIR_OWNERS	(1UL<<OPN_trust_dir_owners)
	OPN_trust_symlink_owners,
#define	OPN_TRUST_SYMLINK_OWNERS	(1UL<<OPN_trust_symlink_owners)
	OPN_trust_default_acls,
#define	OPN_TRUST_DEFAULT_ACLS	(1UL<<OPN_trust_default_acls)
	OPN_unowned,
#define	OPN_UNOWNED	(1UL<<OPN_unowned)
	OPN_fstype_procfs,
#define	OPN_FSTYPE_PROCFS	(1UL<<OPN_fstype_procfs)
	OPN_fstype_fdfs,
#define	OPN_FSTYPE_FDFS	(1UL<<OPN_fstype_fdfs)
	OPN_fstype_ffm,
#define	OPN_FSTYPE_FFM	(1UL<<OPN_fstype_ffm)
	OPN_fstype_remote,
#define	OPN_FSTYPE_REMOTE	(1UL<<OPN_fstype_remote)
	OPN_accept_manflocks,
#define	OPN_ACCEPT_MANFLOCKS	(1UL<<OPN_accept_manflocks)
	OPN_num_flags,			/* count of flags assigned */
	OPN_first_reserved = (64 - 8)	/* reserved for the "..." extension */
};

int safe_open __((char const *, int, ulong_t, ...));

#ifdef __cplusplus
}
#endif

#endif	/* ndef _SAFE_OPEN_H_ */
