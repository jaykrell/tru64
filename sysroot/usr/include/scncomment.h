/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: scncomment.h,v $
 * Revision 1.1.28.1  2003/06/19  13:26:49  Matthew_McGrath
 * 	Add Big Page comment definitions.
 *
 * Revision 1.1.26.1  2001/09/11  15:02:51  Randy_Lowell
 * 	Copy changes from wildcat pool.
 *
 * Revision 1.1.23.1  2001/04/11  18:06:49  Randy_Lowell
 * 	Added LDEF_EXEC_FLAGS
 *
 * Revision 1.1.21.1  2000/01/18  18:21:47  Andrew_Bragg
 * 	Changed TANDEM to TANDEMSYM
 * 	[2000/01/14  21:03:43  Andrew_Bragg]
 *
 * 	Tandem, Atom II, and linkerdef additions
 * 	[2000/01/14  18:05:34  Andrew_Bragg]
 *
 * Revision 1.1.12.6  1997/12/29  21:23:21  Randy_Lowell
 * 	Added basic abstract types
 * 	[1997/12/04  18:13:22  Randy_Lowell]
 *
 * Revision 1.1.12.5  1997/10/31  13:00:42  Randy_Lowell
 * 	Changed names to begin with CM_ instead of ST_CM_.
 * 	Added tag descriptor structures and macros.
 * 	[1997/10/07  20:34:12  Randy_Lowell]
 * 
 * Revision 1.1.12.4  1997/06/24  19:53:21  Michelle_Neisser
 * 	Added #define for ST_CM_TOOLVER.
 * 	[1997/06/09  15:50:17  Michelle_Neisser]
 * 
 * Revision 1.1.12.3  1997/03/29  13:38:34  Randy_Lowell
 * 	Added ST_CMF_INPUT_ONLY
 * 	[1997/03/21  16:28:23  Randy_Lowell]
 * 
 * Revision 1.1.12.2  1997/03/19  22:02:38  Michelle_Neisser
 * 	Maintain old definitions.
 * 	[1997/03/19  13:49:42  Michelle_Neisser]
 * 
 * 	Added #define's for new tag values and flags.
 * 	[1997/03/18  23:07:22  Michelle_Neisser]
 * 
 * Revision 1.1.10.3  1994/09/08  21:08:22  Thomas_Peterson
 * 	Added header macro to protect against multiple inclusion & added C++
 * 	blocks around header body.
 * 	[1994/09/06  16:17:16  Thomas_Peterson]
 * 
 * Revision 1.1.10.2  1994/08/03  15:47:59  Jim_McHale
 * 	Copy files over from gold to gold_minor
 * 	[1994/07/19  19:58:35  Jim_McHale]
 * 
 * Revision 1.1.6.2  1994/05/04  20:04:00  Greg_Lueck
 * 	Add support for new .comment section format.
 * 	[1994/04/05  20:29:37  Greg_Lueck]
 * 
 * Revision 1.1.4.2  1993/08/12  16:55:11  Randy_Lowell
 * 	Added GPVALUE type
 * 	[1993/07/27  21:37:16  Randy_Lowell]
 * 
 * Revision 1.1.2.5  1993/01/22  15:35:52  Randy_Lowell
 * 	Added new compact relocation types
 * 	[93/01/21  16:29:15  Randy_Lowell]
 * 
 * Revision 1.1.2.4  93/01/08  15:59:57  Randy_Lowell
 * 	Changed define of CM_R_TYPE_WORD so that it doesn't conflict with the
 * 	current pixie code.
 * 	[93/01/08  15:12:58  Randy_Lowell]
 * 
 * 	Changed CM_R_TYPE_WORD def so it can be used for R_REFLONG
 * 	relocations.
 * 	[93/01/07  10:32:21  Randy_Lowell]
 * 
 * Revision 1.1.2.3  92/12/08  16:50:21  Jim_McHale
 * 	"compiler integration"
 * 
 * Revision 1.1.4.2  92/12/08  16:48:33  Jim_McHale
 * 	Intergrate randys changes
 * 
 * Revision 1.1.2.2  92/04/01  15:41:53  Ken_Lesniak
 * 	sync with compiler pool
 * 	[92/04/01  15:22:43  Ken_Lesniak]
 * 
 * $EndLog$
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

#ifndef _SCNCOMMENT_H_
#define _SCNCOMMENT_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <coff_type.h>

/*
 * Structure of an internal header in the .comment section.
 *
 *	cm_tag identifies the type of data in this subsection of the
 *	    .comment section.
 *
 *	cm_len gives the length in bytes of this subsection's data.
 *	    If cm_len is zero, the data is stored in the cm_val field.
 *
 *	cm_val is either a pointer to this subsection's data or is
 *	    itself the data.  If cm_len is non-zero, cm_val is a
 *	    relative file offset to the start of the data.  The offset
 *	    is relative to the beginning of the .comment section.
 */

typedef struct {
    coff_uint	cm_tag;
    coff_uint	cm_len;
    coff_ulong	cm_val;
} CMHDR;

#define CMHDRSZ sizeof(CMHDR)

/* 
 * Version of .comment section format 
 */
#define CM_VERSION 0

/*
 * Values for cm_tag  
 */
#define CM_NULL              0       	/* marker for last internal header */
#define CM_END               0       	/* new name for last header */
#define CM_CMSTAMP           3       	/* version stamp header, must be first */
#define CM_COMPACT_RLC       4       	/* compact relocation data */
#define CM_STRSPACE          5       	/* generic string space */
#define CM_TAGDESC           6       	/* tag descriptor subsection */
#define CM_IDENT             7       	/* ident strings */
#define CM_TOOLVER	     8 	     	/* tool-specific version information */
#define CM_II_CHECKSUMS      9          /* II(Incremental Instrumentation)
					 * Atom checksum data.
					 */
#define CM_II_ATOMARGS       10         /* II Atom argument mask */
#define CM_II_TOOLARGS       11         /* II Atom tool argument string */
#define CM_II_ANALADDRS      12         /* II Atom tool analysis addresses */
#ifdef TANDEMSYM
#define CM_FLOAT_TYPE        13         /* Reserved */
#endif /* TANDEMSYM */
#define CM_II_OBJID          14         /* II Atom object id number */
#define CM_LINKERDEF         15         /* Reloc info for linker-defs */
#define CM_BP_ENABLED	     16		/* Big Pages enabled */
#define CM_BP_ANON	     17		/* Big Pages thresh for anon objs */
#define CM_BP_SEG	     18		/* Big Pages thresh for seg objs */
#define CM_BP_SHM	     19		/* Big Pages thresh for shm objs */
#define CM_BP_SSM	     20		/* Big Pages thresh for ssm objs */
#define CM_BP_STACK	     21		/* Big Pages thresh for stack objs */
#define CM_BP_FACTOR	     22		/* Big Pages RAD factor */
#define CM_L3_ANON	     23		/* L3 PT GH for anon */
#define CM_L3_SHM	     24		/* L3 PT GH for shm */
#define CM_L3_SSM	     25		/* L3 PT GH for ssm */
#define CM_LOUSER            0x80000000 /* beginning of user range */
#define CM_HIUSER            0xffffffff /* end of user range */

/*
 *  Comment Section Flags
 */
typedef struct {
    coff_uint	cmf_strip:3;
    coff_uint	cmf_combine:5;
    coff_uint	cmf_modify:4;
    coff_uint	:20;
} cm_flags_t;

typedef enum {
    CMFS_KEEP   = 0,
    CMFS_STRIP  = 1,
    CMFS_LSTRIP = 2
} cmfs_t;

typedef enum {
    CMFC_APPEND  = 0,
    CMFC_CHOOSE  = 1,
    CMFC_DELETE  = 2,
    CMFC_ERRMULT = 3,
    CMFC_ERROR   = 4
} cmfc_t;

typedef enum {
    CMFM_COPY   = 0,
    CMFM_DELETE = 1,
    CMFM_ERROR  = 2
} cmfm_t;

#define CMFS_FLAG(flags) flags.cmf_strip
#define CMFC_FLAG(flags) flags.cmf_combine
#define CMFM_FLAG(flags) flags.cmf_modify

#define CMF_SET_FLAGS(flags, s, c, m) ((flags).cmf_strip = s, \
                                       (flags).cmf_combine = c, \
                                       (flags).cmf_modify = m)

#define CMF_SET_DEFAULT(flags) ((flags).cmf_strip = CMFS_KEEP, \
                                (flags).cmf_combine = CMFC_APPEND,\
                                (flags).cmf_modify = CMFM_COPY)

#define CMF_SAME_FLAGS(f1, f2) ((f1.cmf_strip == f2.cmf_strip) && \
                                (f1.cmf_combine == f2.cmf_combine) && \
                                (f1.cmf_modify == f2.cmf_modify))


/* 
 * Tag Descriptor Structure (CM_TAGDESC)
 */ 

struct cm_td {
    coff_uint	tag;	/* subsection tag value */
    cm_flags_t	flags;	/* flag values defined in scncomment.h */
};

typedef struct cm_td cm_td_t;

#ifdef TANDEMSYM
/* Values for CM_FLOAT_TYPE */
#define F_TANDEM_FLOATTYPE_UNUSED	0
#define F_TANDEM_FLOATTYPE_TANDEM	1
#define F_TANDEM_FLOATTYPE_NEUTRAL	2
#define F_TANDEM_FLOATTYPE_IEEE		3
#endif /* TANDEMSYM */

/* 
 * The CM_LINKERDEF subsection is an array of linker_data structures. 
 */
struct linker_data {
    coff_uint	ld_scnptr;	/* section offset of relocation address */
    coff_uint	ld_base:6;	/* section id using R_SN value (see reloc.h) */
    coff_uint	ld_symbol:6;	/* linker defined symbol id (see below) */
    coff_uint	ld_type:8;	/* relocation type (see reloc.h) */
    coff_uint	ld_size:6;	/* R_OP_STORE, bitfield size */
    coff_uint	ld_offset:6;	/* R_OP_STORE, quad based LE bit offset */
};

/*
 * These enumerate the various linker-defined symbols that may
 * be referenced in the CM_LINKERDEF section.
 */
enum LD_SYMBOL {
    LDEF__BASE_ADDRESS = 0,
    LDEF__cobol_main = 1,
    LDEF__DYNAMIC = 2,
    LDEF__DYNAMIC_LINK = 3,
    LDEF__ebss = 4,
    LDEF__edata = 5,
    LDEF_edata = 6,
    LDEF__end = 7,
    LDEF_end = 8,
    LDEF__etext = 9,
    LDEF_etext = 10,
    LDEF__fbss = 11,
    LDEF__fdata = 12,
    LDEF__fpdata = 13,
    LDEF__fpdata_size = 14,
    LDEF___fstart = 15,
    LDEF__ftext = 16,
    LDEF__ftlsinit = 17,
    LDEF_GOT_OFFSET = 18,
    LDEF__gp = 19,
    LDEF__gpinfo = 20,
    LDEF___istart = 21,
    LDEF__procedure_string_table = 22,
    LDEF__procedure_table = 23,
    LDEF__procedure_table_size = 24,
    LDEF___tlsbsize = 25,
    LDEF___tlsdsize = 26,
    LDEF___tlskey = 27,
    LDEF___tlsoffset = 28,
    LDEF___tlsregions = 29,
    LDEF___EXEC_FLAGS = 30,
    LDEF_MAX                  /* for detecting values too large */
};



/*
******************************************************************************
**
**  The rest of the definitions in this file describe the old format of
**  the .comment section.  They are described here so tools can process
**  old objects.  New tools should not generate object files using these
**  definitions.
**
******************************************************************************
*/

typedef struct {
#if defined(__mips64) || defined(__alpha)
    unsigned long cm_tag;
#else
    unsigned cm_tag;
#endif
    union {
	unsigned long cm_val;
	unsigned long cm_ptr;
    } cm_un;
} CM;

#if defined(__mips64) || defined(__alpha)
/* #define CM_NULL            0L */
#define CM_RELOC_NO        1L
#define CM_RELOC_PTR       2L
#else
/* #define CM_NULL            0x00000000 */
#define CM_RELOC_NO        0x00000001
#define CM_RELOC_PTR       0x00000002  
#endif

struct full_rlc {
    int type;
    unsigned long konst;
    unsigned long vaddr;
    unsigned long dist2lo;
};

#if defined(__mips64) || defined(__alpha)
#define CM_R_TYPE_NULL      0
#define CM_R_TYPE_ABS       1
#define CM_R_TYPE_GPREL32   2
#define CM_R_TYPE_QUAD      3
#define CM_R_TYPE_GPHI_LO   4  
#define CM_R_TYPE_WORD      5  /* 32-bit */
/* Don't use type 6 until pixie is fixed */
#define CM_R_TYPE_INITHI_LO 7
#define CM_R_TYPE_SREL16    8
#define CM_R_TYPE_SREL32    9
#define CM_R_TYPE_SREL64   10
#define CM_R_TYPE_PUSHPSUB 11
#define CM_R_TYPE_SHIFTSTORE 12
#define CM_R_TYPE_GPVALUE  13
#define CM_R_TYPE_EXTENDED_TYPE 15
#else
#define CM_R_TYPE_NULL      0
#define CM_R_TYPE_ABS       1
#define CM_R_TYPE_REL32     2
#define CM_R_TYPE_WORD      3
#define CM_R_TYPE_GPHI_LO   4
#define CM_R_TYPE_JMPADDR   5
#define CM_R_TYPE_GPHI_LO2  6
#endif

typedef struct {
    char *scn_praw;
    char *rlc_ptr;
    char *cur_rlc_ptr;
    int  rlc_no;
    int  cur_rlc_no;
    unsigned long last_base;
    struct full_rlc rlc_entry;
} cm_struct ;


/* this struct must be the same as next, except for the last item, */
/* which is the constant for the addend */
#if defined(__mips64) || defined(__alpha)
#define        ADDEND_NOCONST  0
#define        ADDEND_CONST    1   /* if an addend included, e.g. sym + k */
#define        ADDEND_BASE     2   /* base of address to be relocated */
#define        DEL_VADDR_MASK   0xFFFFF00000000000

struct COMPACT_RELOC {
    unsigned long addend:  4;
    unsigned long type:    4;      /* relocation type */
    unsigned long del_lo:  8;      /* delta to ref_lo from ref_hi, shifted 2 */
    signed   long del_vaddr: 48;   /* delta addr, from previous entry */
};

#else /* defined(__mips64) || defined(__alpha) */

struct COMPACT_RELOC {
    unsigned addend:  2;
#define        ADDEND_NOCONST  0
#define        ADDEND_CONST    1   /* if an addend included, e.g. sym + k */
#define        ADDEND_BASE     2   /* base of address to be relocated */
    unsigned type:    3;           /* relocation type */
    unsigned del_lo:  8;           /* delta to ref_lo from ref_hi, shifted 2 */
    
    signed del_vaddr: 19;          /* delta addr, from previous entry */
                                   /* to be relocated */
#define        DEL_VADDR_MASK   0xFFFF8000
};

#endif /* defined(__mips64) || defined(__alpha) */

struct COMPACT_RELOC_C {
    struct COMPACT_RELOC _rlc;
    unsigned long addend_const;         /* k of addend */
};

struct COMPACT_RELOC_C_BASE {
    struct COMPACT_RELOC _rlc;
    unsigned long addend_const;         /* k of addend */
    unsigned long base;                 /* base for next delta */
};

struct COMPACT_RELOC_BASE {
    struct COMPACT_RELOC _rlc;
    unsigned long base;                 /* base for next delta */
};


union cm_rlc {
    struct COMPACT_RELOC            r;
    struct COMPACT_RELOC_C_BASE    cb;
    struct COMPACT_RELOC_C          c;
    struct COMPACT_RELOC_BASE       b;
};


#define VADDR_OVFL(delta)  (((delta & DEL_VADDR_MASK) != 0) && \
			    ((delta & DEL_VADDR_MASK) != DEL_VADDR_MASK))

#define VADDR_DELTA(delta) (delta & ~DEL_VADDR_MASK)

#ifdef __cplusplus
}
#endif
#endif /* _SCNCOMMENT_H_ */
