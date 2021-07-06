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
 * @(#)$RCSfile: dvdfs.h,v $ $Revision: 1.1.9.3 $ (DEC) $Date: 2002/06/07 19:16:19 $
 */
#ifndef	_DVDFS_FS_H_
#define _DVDFS_FS_H_


#include <sys/types.h>
#include <sys/param.h>
#include <dvdfs/dvdfsnode.h>

#define DVDFS_IOBLOCKSIZE	2048



/*
 * ECMA-167 UDF definitions
 */

/*
 * type declarations
 */
typedef	unsigned char		byte;
typedef	unsigned char		uchar8;
typedef unsigned char		uint8;
typedef unsigned short int	uint16;
typedef unsigned int		uint32;
typedef unsigned long int	uint64;
/* 
 * dstring is a null-terminated string of length n, where d is the count of
 * characters in the string; d is recorded at byte offset n-1, the characters
 * are recorded starting with the first byte of the field, and #00 is
 * recorded at byte offset d+1 through n-2, inclusive.  OSTA 2.00 2.1.3
 */
typedef byte			dstring;

/*
 * misc defines
 */

#define ANCHOR_LOC		256	/* location of anchor vol des ptr */

/*
 * memory representations of on-disk structures
 */


struct charspec {	/* OSTA 2.00 2.1.2 */
	uint8	charset_type;		/* 0 (zero) (CS0 coded char set) */
	byte	charset_info[63];	/* "OSTA Compressed Unicode" */
};

struct timestamp {	/* OSTA 2.00 2.1.4 */
	uint16	type_timezone;
	uint16	year;
	uint8	month;
	uint8	day;
	uint8	hour;
	uint8	minute;
	uint8	second;
	uint8	csecs;
	uint8	husecs;
	uint8	usecs;
};

struct lb_addr {		/* ECMA 167 4/7.1 */
	uint32          lbn;
	uint16          partno;
};

/* 
   Allocation Descriptors  ECMA 167 4/14.14
*/

struct short_ad {
        uint32          extentlen;	/* in bytes, multiple of lbs */
        uint32          extentloc;	/* logical block address */
};

struct long_ad {
	uint32		extentlen;
	struct lb_addr	extentloc;
	byte		implementation_use[6];
};

struct ext_ad {
	uint32		extentlen;
	uint32		recorded_length;
	uint32		information_length;
	struct lb_addr	extentloc;
	char		implementation_use[2];
};

/* Extent type ECMA 167 4/14.14.1.1 */
#define EMASK 0x3fffffff
#define etype(x) x>>30
#define EXTENT_RECORDED_ALLOCATED               0x00
#define EXTENT_NOT_RECORDED_ALLOCATED           0x01
#define EXTENT_NOT_RECORDED_NOT_ALLOCATED       0x02
#define EXTENT_NEXT_EXTENT_ALLOCDECS            0x03

/* Extent Descriptor (3/7.1) */

struct extent_ad {
	uint32	length;
	uint32	location;
};

struct entity_id {	/* OSTA 2.00 2.1.5 */
	uint8	flags;		/* must be 0 (zero) */
	char	id[23];		/* implementation id of last modifier */
				/* sequence of bytes (not a dstring) */
	char	idsfx[8];	/* suffix: Domain, UDF or Implementation */
};

struct domain_idsfx {	/* Domain Identifier Suffix */
	unsigned char udf_rev[2];	/* UDF revision */
	unsigned char domain_flags;
	unsigned char reserved[5];	/* null */
};
#define UDF_REVISION 0x0200
#define HARD_WRITE_PROTECT 0x01
#define SOFT_WRITE_PROTECT 0x02

struct udf_idsfx {	/* UDF Identifier Suffix */
	unsigned char udf_rev[2];	/* UDF revision */
	unsigned char os_class;		/* OSTA 2.00 6.3 */
	unsigned char od_id;		/* OSTA 2.00 6.3 */
	unsigned char reserved[4];	/* null */
};
#define OS_UNDEFINED		0
#define OS_DOS			1
#define OS_OS_2			2
#define	OS_MACINTOSH		3
#define	OS_UNIX			4
#define	OS_WIN_95		5
#define	OS_WIN_NT		6	/* values 7-255 reserved */
#define ID_WIN_3X		0
#define ID_OS_2			0
#define ID_SYSTEM7		0
#define ID_UNIX_GENERIC		0
#define ID_IBM_AIX		1
#define ID_SUNOS_SOLARIS	2
#define ID_HP_UX		3
#define ID_SG_IRIX		4
#define ID_LINUX		5
#define ID_MKLINUX		6
#define ID_FREE_BSD		7
#define ID_WIN_95		8
#define ID_WIN_NT		9

struct implementation_idsfx {		/* Implementation Identifier Suffix */
	unsigned char os_class;		/* OSTA 2.00 6.3 */
	unsigned char os_id;		/* OSTA 2.00 6.3 */
	unsigned char implementation_use[6];
};

struct tag {		/* OSTA 2.00 2.2.1, 2.3.1 */
	uint16	tag_id;
	uint16	descriptor_ver;
	uint8	tag_cs;
	byte	reserved;
	uint16	tag_sn;
	uint16	descriptor_crc;
	uint16	dcrc_length;
	uint32	tag_location;
};
/* tag.tag_id field values: */
#define TAGID_NONE             0	/* no tag                         */
#define TAGID_PVD              1	/* primary volume desc            */
#define TAGID_ANCHOR           2	/* anchor desc                    */
#define TAGID_POINTER          3	/* pointer desc                   */
#define TAGID_IUD              4	/* implementation use desc        */
#define TAGID_PD               5	/* volume partition desc          */
#define TAGID_LVD              6	/* logical volume desc            */
#define TAGID_USD              7	/* unallocated volume space desc  */
#define TAGID_TERM_DESC        8	/* terminator desc                */
#define TAGID_LVID             9	/* logical volume integrity desc  */
#define TAGID_FSD              256	/* file set desc                  */
#define TAGID_FILE_ID          257	/* file identifier desc           */
#define TAGID_ALLOC_EXTENT     258	/* Allocation extent desc         */
#define TAGID_INDIRECT         259	/* Indirect entry                 */
#define TAGID_TERM_ENTRY       260	/* Terminal entry                 */
#define TAGID_FILE_ENTRY       261	/* File entry                     */
#define TAGID_EXT_ATTR         262	/* Extended attribute desc        */
#define TAGID_UNALLOC_SP_ENTRY 263	/* Unallocated space entry (WORM) */
#define TAGID_SPACE_BMAP       264	/* Space bitmap desc              */
#define TAGID_PART_INTEGRITY   265	/* Partition integrity desc       */
/* macro to access tag id from bp after read */
#define	TAG(X)		((struct tag *) ((X)->b_un.b_addr))
#define	TAGID(X)	TAG(X)->tag_id

struct regid {			/* ECMA 167 1/7.4 */
        uint8           flags;
        byte            id[23];
        byte            idsfx[8];
};

struct primary_vd {	/* OSTA 2.00 2.2.2 */
	struct tag	tag;
	uint32		vd_seqno;
	uint32		pvd_no;
	dstring		volid[32];
	uint16		vseqno;
	uint16		max_vseqno;
	uint16		intchlvl;
	uint16		max_intchlvl;
	uint32		charsetlist;	
	uint32		max_charsetlist;
	dstring		vsetid[128];
	struct charspec	dcharset;
	struct charspec	echarset;
	struct extent_ad volabstract;
	struct extent_ad volcopyright;
	struct entity_id application_id;
	struct timestamp recordtime;
	struct entity_id implementation_id;
	byte		implementation_use[64];
	uint32		predecessorvd_seqloc;
	uint16		flags;
	byte		reserved[22];
};

struct anchor_vdp {	/* OSTA 2.00 2.2.3 */	/* at Logical Sector 256 */
	struct tag	tag;
	struct extent_ad mainvd_seqext;		/* min length 16 log sectors */
	struct extent_ad reservevd_seqext;	/* min length 16 log sectors */
	byte		reserved[480];
};

struct logical_vd {	/* OSTA 2.00 2.2.4 */
	struct tag	tag;
	uint32		vd_seqno;
	struct charspec	dcharset;		
	dstring		lvolid[128];
	uint32		lbs;			
	struct entity_id domain_id;	    
	byte		lvol_contentuse[16];
	uint32		maptablelen;		/* MT_L, could be 0 */
	uint32		num_partmaps;
	struct entity_id implementation_id;
	byte		implementation_use[128];
	struct extent_ad integrity_seqext;
/*
	byte		partmaps[MT_L];
*/
};

struct partition_map {	/* OSTA 10.7.2 */
	uint8		type;
	uint8		maplength;
	uint16		vseqno;
	uint16		partnum;
};

struct unallocsp {	/* OSTA 2.00 2.2.5 */
	struct tag	tag;
	uint32		vd_seqno;
	uint32		num_allocation_descrip;	/* N_AD, could be 0 */
/*
	struct extent_ad allocation_descrip[N_AD];
*/
};


/*
 * OSTA 2.00 3.2.1.1 UniqueID
 * UniqueID is initialized to 16, and monotonically increases
 * with each assignment.  Whenever the lower 32-bits of this
 * value reach 0xFFFFFFFF, the upper 32-bits are incremented by 1,
 * but the lower 32-bits "wrap" up to 16.
 */

#define init_uniqueid() 16
#define inc_uniqueid(id) \
    (((id & 0xffffffff) ^ 0xffffffff) ? (id + 1) : (id + 1 + 16))

struct implementuse_vd {
	struct tag	tag;
	uint32		vd_seqno;
	struct entity_id implementation_id;	/* "*UDF LV Info"+UDF */
	byte		implemtation_use[460];
};

struct partition_d {		/* ECMA 167 3/10.5 */
	struct tag	tag;
	uint32		vd_seqno;
	uint16		flags;
	uint16		number;
	struct regid	contents;
	byte		contentuse[128];
	uint32		access_type;
	uint32		partition_start;
	uint32		partition_length;
	struct regid	implementation_id;
	byte		implementation_use[128];
	byte		reserved[156];
};

struct fileset_d {		/* OSTA 2.00 2.3.2 */
	struct tag	tag;
	struct timestamp recordtime;
	uint16		intchlvl;		/* 3 */
	uint16		max_intchlvl;		/* 3 */
	uint32		charsetlist;		/* CSO only */
	uint32		max_charsetlist;	/* supported char sets (1) */
	uint32		fileset_no;
	uint32		fileset_dno;
	struct charspec	lvid_charset;		/* for lv_id */
	dstring		lv_identifier[128];
	struct charspec	fs_charset;		/* for dstrings in struct */
	dstring		fileset_id[32];
	dstring		copyright_fid[32];
	dstring		abstract_fid[32];
	struct long_ad	rootdir_icb;
	struct entity_id domain_id;	    /* "*OSTA UDF Compliant"+Domain */
	struct long_ad	next_extent;
	struct long_ad	streamdir_icb;
	byte		reserved[32];
};

struct parthead_d {		/* OSTA 2.00 2.3.3 */
	struct short_ad	unallocsp_tab;
	struct short_ad	unallocsp_bmap;
	struct short_ad	partinteg_tab;		/* not used, null */
	struct short_ad	freedsp_tab;
	struct short_ad	freedsp_bmap;
	unsigned char	reserved[88];
};

/* calculate padding factor for File Identifier Descriptor (ECMA 4/14.4.9) */
#define FIDPAD(L_FI, L_IU)	4*((L_FI+L_IU+38+3)/4)-(L_FI+L_IU+38)

struct fileid_d {		/* OSTA 2.00 2.3.4, 3.3.1 */
	struct tag	tag;
	uint16		file_vernum;
	uint8		file_characteristics;
	uint8		fileid_len;	/* L_FI, could be 0 */
	struct long_ad	icb;
	uint16		impuse_len;	/* L_IU, could be 0 */
/*
	byte		implementation_use[L_IU];
	dstring		file_identifier[L_FI];
	byte		padding[FIDPAD];
*/
};

/* file_characteristics */
#define FC_HIDDEN	0x01		/* hidden file (normal file in UNIX) */
#define FC_DIRECTORY	0x02		/* directory */
#define FC_DELETED	0x04		/* deleted file */
#define FC_ICBISPARENT	0x08		/* if set, the ICB identifies parent */

struct icbtag {		/* OSTA 2.00 2.3.5, 3.3.2 */
	uint32		priordirects;
	uint16		strategytype;		/* type 4 or 4096 (WORM) */
	uint16		strategyparm;
	uint16		num_entries;
	uint8		reserved;
	uint8		filetype;
	struct lb_addr	parent_icbloc;
	uint16		flags;
};

#define FT_UNSPECIFIED          0	/* valid for OSTA 2.00 ?? */
#define FT_UNALLOC_SP_ENTRY     1
#define FT_PARTITION_INTEGRITY  2
#define FT_INDIRECT_ENTRY       3
#define FT_DIRECTORY            4
#define FT_RAW                  5	/* regular file */
#define FT_BDEV                 6
#define FT_CDEV                 7
#define FT_EXT_ATTR             8
#define FT_FIFO                 9
#define FT_SOCKET              10
#define FT_TERMINAL_ENTRY      11
#define FT_SYMLINK             12
/* Bits 0,1,2 - Allocation Descriptor Type */
#define ADTYPEMASK	0x0007		/* allocation descriptor type */
#define ADGENERIC	0x2000		/* internal use ONLY */
#define ADSHORT		0x00		/* short ADs */
#define ADLONG		0x01		/* long ADs */
#define ADEXTENDED	0x02		/* extended ADs */
#define ADNONE		0x03		/* data replaces ADs */
#define valid_adtype(x) ((x)==ADSHORT||(x)==ADLONG||(x)==ADEXTENDED)
/* Bits 3-9 : Miscellaneous */
#define SORTED_DIRECTORY	0x0008
#define NON_RELOCATABLE		0x0010
#define CONTIGUOUS		0x0200
#define TRANSFORMED		0x0800
#define MULTIVERS		0x1000

/* Extent Length and Type share field (4/14.14.1.1) */
#define EXTENTLEN		0x3fffffff
#define EXTENTTYPE		0xc0000000

struct file_entry {		/* OSTA 2.00 2.3.6, 3.3.3 */
	struct tag	tag;
	struct icbtag	icb_tag;
	uint32		uid;
	uint32		gid;
	uint32		permissions;
	uint16		filelinkcnt;
	uint8		record_format;
	uint8		record_dattributes;
	uint32		record_len;
	uint64		info_len;
	uint64		lb_recorded;
	struct timestamp accesstime;
	struct timestamp modtime;
	struct timestamp attributetime;
	uint32		checkpoint;
	struct long_ad	extattrib_icb;
	struct regid	implementation_id;
	uint64		uniqueid;
	uint32		extendedattribs_len;		/* L_EA, could be 0 */
	uint32		allocdescriptors_len;		/* L_AD, could be 0 */
/*
	byte		extendedattribs[L_EA];
	byte		allocdescriptors[L_AD];
??? Can this cross a block boundary? May need multiple reads.
*/
};

/* Permissions 4/14.9.5 */
#define OTHER_EXECUTE		0x00000001
#define OTHER_WRITE		0x00000002
#define OTHER_READ		0x00000004
#define OTHER_CHATTR		0x00000008
#define OTHER_DELETE		0x00000010
#define GROUP_EXECUTE		0x00000020
#define GROUP_WRITE		0x00000040
#define GROUP_READ		0x00000080
#define GROUP_CHATTR		0x00000100
#define GROUP_DELETE		0x00000200
#define OWNER_EXECUTE		0x00000400
#define OWNER_WRITE		0x00000800
#define OWNER_READ		0x00001000
#define OWNER_CHATTR		0x00002000
#define OWNER_DELETE		0x00004000

/*
 * Contents of mount point buf.
 */

struct part_table {
	int		flag;
	ushort		partno;
	uint		partstart;
	uint		partlen;
	uint		partend;
};

#define	PT_VALID	0x01

struct dvdfs {
	struct	fs *fs_link;		/* linked list of file systems */
	struct	fs *fs_rlink;		/* used for incore super blocks */
	char	fs_ronly;		/* Read only ? */
	int	fs_ibsize;		/* File system block size */
	struct	dvdnumber volino;	/* volume info (File Set Desc) */
	struct	dvdnumber rootino;	/* fs info (File Entry for root) */
	struct	anchor_vdp	*anchor;
	struct	primary_vd	*primary;
	struct	implementuse_vd	*impuse;
	struct	logical_vd	*logical;
	struct	unallocsp	*unallocsp;
#ifdef _KERNEL
	udecl_simple_lock_data(,fsu_lock) /* see notes below */
#endif /* _KERNEL */
	struct	part_table	*ptab;	  /* pointer to part_table[#PARTS] */
};

#ifdef _KERNEL
extern enum vtype	dvdftovt_tab[];
#define DVDFTOVT(mode)	(dvdftovt_tab[((mode) & DVDFMT) >> 12])

#define	fs_lock		fsu_lock

udecl_simple_lock_info(extern, dvdfs_lockinfo)

#define FS_LOCK(fs)		usimple_lock(&(fs)->fs_lock)
#define	FS_UNLOCK(fs)		usimple_unlock(&(fs)->fs_lock)
#define	FS_LOCK_INIT(fs)	usimple_lock_setup(&(fs)->fs_lock, dvdfs_lockinfo)
#define	FS_LOCK_HOLDER(fs)	SLOCK_HOLDER(&(fs)->fs_lock)
#endif

#endif	/* _DVDFS_FS_H_ */
