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
 * @(#)$RCSfile: dvdfsdisk.h,v $ $Revision: 1.1.4.1 $ (DEC) $Date: 2000/01/21 15:59:30 $
 */
#ifndef	_DVDFSDISK_FS_H_
#define _DVDFSDISK_FS_H_


#include <sys/types.h>
#include <sys/param.h>


/*
 * ECMA-167 UDF definitions of on-disk structures
 */

struct d_charspec {	/* OSTA 2.00 2.1.2 */
	unsigned char charset_type;	/* 0 (zero) (CS0 coded char set) */
	unsigned char charset_info[63];	/* "OSTA Compressed Unicode" */
};

struct d_timestamp {	/* OSTA 2.00 2.1.4 */
	unsigned char type_timezone[2];
	unsigned char year[2];
	unsigned char month;
	unsigned char day;
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
	unsigned char csecs;
	unsigned char husecs;
	unsigned char usecs;
};

struct d_lb_addr {		/* ECMA 167 4/7.1 */
	unsigned char lbn[4];
	unsigned char partno[2];
};

struct d_short_ad {		/* ECMA 167 4/14.14.1 */
	unsigned char extentlen[4];
	unsigned char extentloc[4];         /* logical block address */
};

struct d_long_ad {		/* ECMA 167 4/14.14.2 */
	unsigned char extentlen[4];
	struct d_lb_addr extentloc;
	unsigned char implementation_use[6];
};

struct d_ext_ad {			/* ECMA 167 4/14.14.3 */
	unsigned char extentlen[4];
	unsigned char recorded_length[4];
	unsigned char information_length[4];
	struct d_lb_addr extentloc;
	unsigned char implementation_use[2];
};

struct d_extent_ad {
	unsigned char length[4];
	unsigned char location[4];
};

struct d_entity_id {	/* OSTA 2.00 2.1.5 */
	unsigned char flags;	/* must be 0 (zero) */
	unsigned char id[23];	/* implementation id of last modifier */
				/* sequence of bytes (not a dstring) */
	unsigned char idsfx[8];	/* suffix: Domain, UDF or Implementation */
};

struct d_domain_idsfx {	/* Domain Identifier Suffix */
	unsigned char udf_rev[2];	/* UDF revision */
	unsigned char domain_flags;
	unsigned char reserved[5];	/* null */
};

struct d_udf_idsfx {	/* UDF Identifier Suffix */
	unsigned char udf_rev[2];	/* UDF revision */
	unsigned char os_class;		/* OSTA 2.00 6.3 */
	unsigned char od_id;		/* OSTA 2.00 6.3 */
	unsigned char reserved[4];	/* null */
};
struct d_implementation_idsfx {		/* Implementation Identifier Suffix */
	unsigned char os_class;		/* OSTA 2.00 6.3 */
	unsigned char os_id;		/* OSTA 2.00 6.3 */
	unsigned char implementation_use[6];
};

struct d_tag {		/* on-disk representation */
	unsigned char tag_id[2];
	unsigned char descriptor_ver[2];
	unsigned char tag_cs;
	unsigned char reserved;
	unsigned char tag_sn[2];
	unsigned char descriptor_crc[2];
	unsigned char dcrc_length[2];
	unsigned char tag_location[4];
};

struct d_regid {			/* ECMA 167 1/7.4 */
	unsigned char flags;
	unsigned char id[23];
	unsigned char idsfx[8];
};

struct d_primary_vd {	/* OSTA 2.00 2.2.2 */
	struct d_tag	d_tag;
	unsigned char	vd_seqno[4];
	unsigned char	pvd_no[4];
	unsigned char		volid[32];
	unsigned char	vseqno[2];
	unsigned char	max_vseqno[2];
	unsigned char	intchlvl[2];
	unsigned char	max_intchlvl[2];
	unsigned char	charsetlist[4];
	unsigned char	max_charsetlist[4];
	unsigned char		vsetid[128];
	struct d_charspec	dcharset;
	struct d_charspec	echarset;
	struct d_extent_ad volabstract;
	struct d_extent_ad volcopyright;
	struct d_entity_id application_id;
	struct d_timestamp recordtime;
	struct d_entity_id implementation_id;
	unsigned char	implementation_use[64];
	unsigned char	predecessorvd_seqloc[4];
	unsigned char	flags[2];
	unsigned char	reserved[22];
};

struct d_anchor_vdp {	/* OSTA 2.00 2.2.3 */	/* at Logical Sector 256 */
	struct d_tag	d_tag;
	struct d_extent_ad mainvd_seqext;
	struct d_extent_ad reservevd_seqext;
	unsigned char 	reserved[480];
};

struct d_logical_vd {	/* OSTA 2.00 2.2.4 */
	struct d_tag	d_tag;
	unsigned char	vd_seqno[4];
	struct d_charspec	dcharset;
	unsigned char		lvolid[128];
	unsigned char	lbs[4];
	struct d_entity_id domain_id;
	unsigned char	lvol_contentuse[16];
	unsigned char	maptablelen[4];		/* MT_L, could be 0 */
	unsigned char	num_partmaps[4];
	struct d_entity_id implementation_id;
	unsigned char	implementation_use[128];
	struct d_extent_ad integrity_seqext;
/*
	unsigned char	partmaps[MT_L];
*/
};

struct d_unallocsp {	/* OSTA 2.00 2.2.5 */
	struct d_tag	d_tag;
	unsigned char	vd_seqno[4];
	unsigned char	num_allocation_descrip[4];	/* N_AD, could be 0 */
/*
	struct extent_ad allocation_descrip[N_AD];
*/
};

struct d_implementuse_vd {	/* OSTA 2.00 2.2.7 */
	struct d_tag	d_tag;
	unsigned char	vd_seqno[4];
	struct d_entity_id implementation_id;	/* "*UDF LV Info"+UDF */
	unsigned char	implemtation_use[460];
};

struct d_partition_d {		/* ECMA 167 3/10.5 */
	struct d_tag	d_tag;
	unsigned char	vd_seqno[4];
	unsigned char	flags[2];
	unsigned char	number[2];
	struct d_regid	contents;
	unsigned char	contentuse[128];
	unsigned char	access_type[4];
	unsigned char	partition_start[4];
	unsigned char	partition_length[4];
	struct d_regid	implementation_id;
	unsigned char	implementation_use[128];
	unsigned char	reserved[156];
};

struct d_fileset_d {		/* OSTA 2.00 2.3.2 */
	struct d_tag	d_tag;
	struct d_timestamp recordtime;
	unsigned char	intchlvl[2];
	unsigned char	max_intchlvl[2];
	unsigned char	charsetlist[4];
	unsigned char	max_charsetlist[4];
	unsigned char	fileset_no[4];
	unsigned char	fileset_dno[4];
	struct d_charspec	lvid_charset;
	unsigned char		lv_identifier[128];
	struct d_charspec	fs_charset;	
	unsigned char		fileset_id[32];
	unsigned char		copyright_fid[32];
	unsigned char		abstract_fid[32];
	struct d_long_ad	rootdir_icb;
	struct d_entity_id domain_id;	
	struct d_long_ad	next_extent;
	struct d_long_ad	streamdir_icb;
	unsigned char	reserved[32];
};

struct d_parthead_d {		/* OSTA 2.00 2.3.3 */
	struct d_short_ad	unallocsp_tab;
	struct d_short_ad	unallocsp_bmap;
	struct d_short_ad	partinteg_tab;		/* not used, null */
	struct d_short_ad	freedsp_tab;
	struct d_short_ad	freedsp_bmap;
	unsigned char	reserved[88];
};

struct d_fileid_d {		/* OSTA 2.00 2.3.4, 3.3.1 */
	struct d_tag	d_tag;
	unsigned char	file_vernum[2];
	unsigned char	file_characteristics;
	unsigned char	fileid_len;	/* L_FI, could be 0 */
	struct d_long_ad	icb;
	unsigned char	impuse_len[2];	/* L_IU, could be 0 */
/*
	unsigned char	implementation_use[L_IU];
	string		file_identifier[L_FI];
	unsigned char	padding[FIDPAD];
*/
};

struct d_icbtag {		/* OSTA 2.00 2.3.5, 3.3.2 */
	unsigned char	priordirects[4];
	unsigned char	strategytype[2];
	unsigned char	strategyparm[2];
	unsigned char	num_entries[2];
	unsigned char	reserved;
	unsigned char	filetype;
	struct d_lb_addr	parent_icbloc;
	unsigned char	flags[2];
};

struct d_file_entry {		/* OSTA 2.00 2.3.6, 3.3.3 */
	struct d_tag	d_tag;
	struct d_icbtag	icb_tag;
	unsigned char	uid[4];
	unsigned char	gid[4];
	unsigned char	permissions[4];
	unsigned char	filelinkcnt[2];
	unsigned char	record_format;
	unsigned char	record_dattributes;
	unsigned char	record_len[4];
	unsigned char	info_len[8];
	unsigned char	lb_recorded[8];
	struct d_timestamp accesstime;
	struct d_timestamp modtime;
	struct d_timestamp attributetime;
	unsigned char	checkpoint[4];
	struct d_long_ad	extattrib_icb;
	struct d_regid	implementation_id;
	unsigned char	uniqueid[8];
	unsigned char	extendedattribs_len[4];		/* L_EA, could be 0 */
	unsigned char	allocdescriptors_len[4];	/* L_AD, could be 0 */
/*
	unsigned char	extendedattribs[L_EA];
	unsigned char	allocdescriptors[L_AD];
??? Can this cross a block boundary? May need multiple reads.
*/
};


#endif	/* _DVDFSDISK_FS_H_ */
