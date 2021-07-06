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

/* $Header: /share/buffer/build/rcs.dsk1/os/src/usr/include/alpha/symconst.h,v 1.2.38.1 2001/09/11 15:02:57 Randy_Lowell Exp $ */

/* (C) Copyright 1984 by Third Eye Software, Inc.
 *
 * Third Eye Software, Inc. grants reproduction and use rights to
 * all parties, PROVIDED that this comment is maintained in the copy.
 *
 * Third Eye makes no claims about the applicability of this
 * symbol table to a particular use.
 */

#ifndef _SYMCONST_H
#define _SYMCONST_H

/* glevels for field in FDR */
#define GLEVEL_0    2
#define GLEVEL_1    1
#define GLEVEL_2    0   /* for upward compat reasons. */
#define GLEVEL_3    3

/* magic number for symheader */
#define magicSym    0x1992
#define magicSym_cia    0x1957  /* uld need to preserve symbols inside cia's */

/* Language codes */
#define langC       0   
#define langPascal  1
#define langFortran 2
#define langAssembler   3   /* one Assembley inst might map to many mach */
#define langMachine 4
#define langNil     5
#define langAda     6
#define langPl1     7
#define langCobol   8
#define langStdc    9
#define langMIPSCxx     10  /* MIPS version of CXX symtab */
#define langDECCxx      11  /* DEC version of CXX symtab */
#define langCxx         12  /* Joint plan for CXX symtab */
#define langFortran90   13
#define langBliss   14
#ifdef TANDEMSYM
#define langPTAL	15
#define langCplusplusV1	16
#define langCplusplusV2	17
#endif /* TANDEMSYM */
#define langMax         32      /* maximum allowed 32 -- 5 bits */


/* The following are value definitions for the fields in the PDR */

#ifdef TANDEMSYM
/* 
 * Procedure Attributes (proctype)
 */
#define TNDM_MAIN	0x0001	/* TANDEM main entry point */
#define TNDM_RESIDENT	0x0002	/* TANDEM resident routines */
#define TNDM_PRIVILEGED 0x0004	/* TANDEM priv routines */
#define TNDM_CALLABLE	0x0008	/* TANDEM callable routines */
#define TNDM_ENTRY	0x0010	/* TANDEM alternate entry, proc or subproc */
#define TNDM_SUBPROC	0x0020	/* TANDEM subprocs  */
#define TNDM_INTERRUPT	0x0040	/* TANDEM interrupt routines */
#define TNDM_SHELL	0x0080	/* TANDEM shell routine */
#define TNDM_COMPILER_GENERATED	 0x0200	 /* proc can have multiple copies */
#define TNDM_EXTENSIBLE 0x0800	/* TANDEM extensible procedure */
#define TNDM_EDITLINE	0x8000	/* TANDEM edit line numbers */	  
#endif /* TANDEMSYM */



/* The following are value definitions for the fields in the SYMR */

/*
 * Storage Classes
 */

#define scNil           0
#define scText          1	/* text symbol */
#define scData          2	/* initialized data symbol */
#define scBss           3	/* un-initialized data symbol */
#define scRegister      4	/* value of symbol is register number */
#define scAbs           5	/* value of symbol is absolute */
#define scUndefined     6	/* who knows? */
/* There are no known uses of scCdbLocal */
#define scCdbLocal      7	/* variable's value is IN se->va.?? */
#define scUnallocated   7	/* sym not given memory or reg */
#define scBits          8	/* this is a bit field */
#ifdef TANDEMSYM
#define scResText	8	/* resident text */
#endif /* TANDEMSYM */
#define scTlsUndefined  9	/* TLS external */
#define scRegImage     10	/* register value saved on stack */
#define scInfo         11	/* symbol contains debugger information */
#define scUserStruct   12	/* address in struct user for current process */
#define scSData        13	/* load time only small data */
#define scSBss         14	/* load time only small common */
#define scRData        15	/* load time only read only data */
#define scVar          16	/* Var parameter (fortran,pascal) */
#define scCommon       17	/* common variable */
#define scSCommon      18	/* small common */
#define scVarRegister  19	/* Var parameter in a register */
#define scVariant      20	/* Variant record */
#define scFileDesc     20	/* COBOL: File Descriptor (FD) */
#define scSUndefined   21	/* small undefined(external) data */
#define scInit         22	/* .init section symbol */
#define scBasedVar     23	/* Fortran or PL/1 ptr based var */ 
#define scReportDesc   23	/* COBOL: Report Descriptor (RD) */
#define scXData        24	/* exception handling data */
#define scPData        25	/* Procedure section */
#define scFini         26	/* .fini section */
#define scRConst       27	/* .rconst */
#define scSymRef       28	/* Pointer to main symbol entry */
#define scTlsCommon    29	/* TLS unallocated common */
#define scTlsData      30	/* TLS initialized data */
#define scTlsBss       31	/* TLS 0-initialized data */

#define scMax          32

/* Some helpful combinations */

#define _SC_IS_DATA(x) ((x) == scData || (x) == scSData || (x) == scRData || \
			(x) == scBss || (x) == scSBss || (x) == scRConst)
#define _SC_IS_XDATA(x) ((x) == scXData || (x) == scPData)
#define _SC_IS_TLSDATA(x) ((x) == scTlsData || (x) == scTlsBss)
#define _SC_IS_TEXT(x) ((x) == scText || (x) == scFini || (x) == scInit)

/*
 *   Symbol Types
 */

#define stNil       0   /* Nuthin' special */
#define stGlobal    1   /* external symbol */
#define stStatic    2   /* static */
#define stParam     3   /* procedure argument */
#define stLocal     4   /* local variable */
#define stLabel     5   /* label */
#define stProc      6   /*     "      "  Procedure */
#define stBlock     7   /* beginnning of block */
#define stEnd       8   /* end (of anything) */
#define stMember    9   /* member (of anything  - struct/union/enum */
#define stTypedef   10  /* type definition */
#define stFile      11  /* file name */
#define stRegReloc  12  /* register relocation */
#define stForward   13  /* forwarding address */
#define stStaticProc    14	/* load time only static procs */
#define stConstant	15	/* const */
#define stStaParam	16	/* Fortran static parameters */
#define stBase          17      /* DEC C++ base class */
#define stVirtBase      18      /* DEC C++ virtual base class */
#define stTag           19      /* DEC C++ tag */
#define stInter         20      /* DEC C++ interlude */
#define stSplit		21	/* split lifetime description block start */
#define stModule	22	/* module block start */
#define stNamespace	22	/* DEC C++ namespace */
#define stUsing		23      /* specifies a namespace or module imported */
#define stAlias		24      /* defines an alias name for a namespace */
#ifdef TANDEMSYM
#define stDefine	25	/* macro definition */
#define stObjinfo	26	/* name/data object info */
#define stToolinfo	27	/* compiler info */
#define stSrcinfo	28	/* source data info */
#define stEquivRel	29	/* equivalence variable */
#endif /* TANDEMSYM */
#define stExternal	30	/* local symbol with global linkage */
#define stUseModule	31	/* Fortran module use */
#define stRename	32	/* name replacement */
#define stInterface	33	/* generic interface declaration */

    /* Psuedo-symbols - internal to debugger */
#define stStr       60  /* string */
#define stNumber    61  /* pure number (ie. 4 NOR 2+2) */
#define stExpr      62  /* 2+2 vs. 4 */
#define stType      63  /* post-coersion SER */
#define stMax       64

/* stUseModule values */
#define USE_MODULE_ONLY 0	/* Use selected members of F90 module */
#define USE_MODULE_ALL  1	/* Use all members of F90 module */

/* definitions for fields in TIR */

/* type qualifiers for ti.tq0 -> ti.(itqMax-1) */
#define tqNil   0         /* bt is what you see */
#define tqPtr   1         /* pointer */
#define tqProc  2         /* procedure */
#define tqArray 3         /* array */
#define tqFar   4         /* xtaso pointers (should be tqNear) */
#define tqVol   5         /* volatile */
#define tqConst 6         /* const */
#define tqRef   7         /* reference */
#define tqArray_64  8     /* large size arrays */
#ifdef TANDEMSYM
#define TqHasLen 9        /* pairs of parameters TANDEM */
#endif
#define tqShar  10        /* shareable UPC (with cpu slice) */
#define tqExpArray_64 11  /* array_64 expanded by *THREADS */
#define tqSharArr_64 11   /* obsolete */
#define tqMax   16

/* basic types as seen in ti.bt */
#define btNil       0   /* undefined */
#define btAdr32     1   /* 32-bit address */
#define btChar      2   /* character */
#define btUChar     3   /* unsigned character */
#define btShort     4   /* short */
#define btUShort    5   /* unsigned short */
#define btInt32     6   /* 32-bit int */
#define btInt       btInt32	/* int */
#define btUInt32    7   /* 32-bit unsigned int */
#define btUInt      btUInt32    /* unsigned int */
#define btLong32    8   /* 32-bit long */
#define btULong32   9   /* 32-bit unsigned long */
#define btFloat     10  /* float (real) */
#define btDouble    11  /* Double (real) */
#define btStruct    12  /* Structure (Record) */
#define btUnion     13  /* Union (variant) */
#define btEnum      14  /* Enumerated */
#define btTypedef   15  /* defined via a typedef, isymRef points */
#define btRange     16  /* subrange of int */
#define btSet       17  /* pascal sets */
#define btComplex   18  /* fortran complex */
#define btDComplex  19  /* fortran double complex */
#define btIndirect  20  /* forward or unnamed typedef */
#define btFixedDec  21  /* Fixed Decimal */
#define btFixedBin  21  /* COBOL: Fixed Binary */
#define btFloatDec  22  /* Float Decimal */
#define btDecimal   22  /* COBOL: packed/unpacked decimal */
#define btString    23  /* obsolete */
#define btBit       24  /* obsolete */
#define btPicture   25  /* Picture */
#define btVoid      26  /* void */
#define btPtrMem    27  /* DEC C++:  Pointer to member */
#define btScaledBin 27  /* COBOL: Scaled Binary */
#define btVptr      28  /* DEC C++:  Virtual function table */
#define btArrayDesc 28  /* FORTRAN 90: Array Descriptor */
#define btClass     29  /* DEC C++:  Class (Record) */
#define btLong64    30  /* 64-bit long */
#define btLong      btLong64
#define btULong64   31  /* 64-bit unsigned long */
#define btULong     btULong64
#define btLongLong64    32		/* 64-bit long long */
#define btLongLong      btLongLong64    /* long long */
#define btULongLong64   33		/* 64-bit unsigned long long */
#define btULongLong     btULongLong64   /* unsigned long long */
#define btAdr64         34		/* 64-bit address */
#define btAdr           btAdr64		/* address - same size as pointer */
#define btInt64		35	/* 64-bit int */
#define btUInt64	36	/* 64-bit unsigned int */
#define btLDouble	37	/* long double (real*16) */
#define btInt8		38	/* Signed char-sized integer */
#define btUInt8		39	/* Unsigned char-sized integer */
#define btRange_64	41	/* Large ranges */
#define btProc		42	/* Procedure or function */
#ifdef TANDEMSYM
#define btCobolIndex	43	/* COBOL index variables */
#define btReal32	44	/* TANDEM float */
#define btReal64	45	/* TANDEM double */
#endif /* TANDEMSYM */
#define btQComplex  	46  	/* fortran long double complex */
#define btBool          47 	/* 1 byte boolean (false=0, true=1) */
#define btWchar_t       48 	/* 4 byte wchar_t */
#define btChecksum  63  /* symbol table checksum for file merging. */
#define btMax       64

/* Additional description for btDecimal */
#define decDecimal4		1   /* 4 bits/digit */
#define decDecimal8		2   /* 8 bits/digit */
#define signUnsigned		1   /* No sign present */
#define signLeadingOverpunch    2   /* Sign with leading digit */
#define signTrailingOverpunch   3   /* Sign with final digit */
#define signLeadingSeparate	4   /* Sign in front alone */
#define signTrailingSeparate    5   /* Sign at end alone */

/* Optimization symbol types for ppode_tag field */
#define PPODE_FIRST		1  /* First valid PPODE value */
#define PPODE_STAMP		1  /* Version number of the PPOD */
#define PPODE_END		2  /* End of PPODE entries for this PPOD */
#define PPODE_EXT_SRC		3  /* Extended Source Line information */
#define PPODE_SEM_EVENT         4  /* Semantic event information */
#define PPODE_SPLIT             5  /* Split lifetime information */
#define PPODE_DISCONTIG_SCOPE	6  /* Discontiguous scope information */
#define PPODE_INLINED_CALL	7  /* Inlined procedure call information */
#define PPODE_PROFILE_INFO	8  /* Profile feedback information */
#define PPODE_WHERE_INLINED	9  /* Where inlined summary information */

/* PPODE types 64 through 127 are reserved for PPOD entries related
 * to object annotation.
 */
#define PPODE_ANNOT_RESERVED_FIRST		64
#define PPODE_ANNOT_SUMMARY			64  /* Annotation summary */

/* Restrictive object annotations. */
#define PPODE_ANNOT_RESTRICTED_FIRST		65
#define PPODE_ANNOT_RESTRICTED_OFFSET		65
#define PPODE_ANNOT_RESTRICTED_INSTRUCTION	66
#define PPODE_ANNOT_RESTRICTED_SEQUENCE		67
#define PPODE_ANNOT_RESTRICTED_CALL		68
#define PPODE_ANNOT_RESTRICTED_ENTRY		69
#define PPODE_ANNOT_RESTRICTED_RETURN		70
#define PPODE_ANNOT_RESTRICTED_LAST_NOW		70
#define PPODE_ANNOT_RESTRICTED_LAST		95

/* Optimization enabling annotations. */
#define PPODE_ANNOT_OPTIMIZATION_FIRST		96
#define PPODE_ANNOT_GPREL32_JUMP_TABLE		96
#define PPODE_ANNOT_CALL_SPECIFIED_LINKAGE	97
#define PPODE_ANNOT_ENTRY_SPECIFIED_LINKAGE	98
#define PPODE_ANNOT_ENTRY_UTILIZED_LINKAGE	99
#define PPODE_ANNOT_ENTRY_IMPLEMENTED_LINKAGE	100
#define PPODE_ANNOT_RETURN_SPECIFIED_LINKAGE	101
#define PPODE_ANNOT_OPTIMIZATION_LAST_NOW	101
#define PPODE_ANNOT_OPTIMIZATION_LAST		127

#define PPODE_ANNOT_RESERVED_LAST		127

#define PPODE_LAST		127  /* Last valid PPODE value */

/* Optimization symbol values for ppode_val field */
#define PPOD_VERSION		1   /* Current PPOD version */

/* Semantic event codes for PPODE entries of type PPODE_SEM_EVENT */
#define PPODSE_FIRST            0	/* First valid event code value */
#define PPODSE_NONE             0	/* No event applies             */
#define PPODSE_WRITE            1	/* Write event                  */
#define PPODSE_CONTROL          2       /* Control (branch) event       */
#define PPODSE_CALL             3       /* Call (or return) event       */
#define PPODSE_LABEL            4       /* Label event                  */
#define PPODSE_INST_ONLY        5       /* Instruction only event       */
#define PPODSE_LAST             5       /* Last valid event code value  */
    
/* Split lifetime target types for PPODE entries of type PPODE_SPLIT */
#define PPODE_SPLIT_TYPE_FIRST	    1	/* First valid target type code     */
#define PPODE_SPLIT_TYPE_EXT        1   /* Target is in external symbols    */
#define PPODE_SPLIT_TYPE_LCL        2   /* Target is in local symbols       */
#define PPODE_SPLIT_TYPE_LAST       2   /* Last valid target type code      */
    
/* Split lifetime target schemes for PPODE entries of type PPODE_SPLIT */
#define PPODE_SPLIT_SCHEME_FIRST    1   /* First valid scheme code          */
#define PPODE_SPLIT_SCHEME_DEF      1   /* Normal definition                */
#define PPODE_SPLIT_SCHEME_DEF_PROMOTED 2/*Promoted + normal definition     */
#define PPODE_SPLIT_SCHEME_DUP      3   /* Duplicate of prior definition    */
#define PPODE_SPLIT_SCHEME_LAST     3   /* Last valid scheme code           */

/* Annotation summary version for ANNOT_SUMMARY_VAL */
#define ANNOT_VERSION	1

/* Architecture and tuning values for object annotation data */
#define ANNOT_ARCH_GENERIC	1	/* Generic alpha system */
#define ANNOT_ARCH_EV4	3		/* EV4 system */
#define ANNOT_ARCH_EV5	4		/* EV5 system */
#define ANNOT_ARCH_EV56	5		/* EV56 system */
#define ANNOT_ARCH_PCA56	6	/* PCA56 system */
#define ANNOT_ARCH_EV6	7		/* EV6 system */
#define ANNOT_ARCH_EV67	8		/* EV67 system */
#define ANNOT_ARCH_EV68	9		/* EV68 system */
#define ANNOT_ARCH_EV69	10		/* EV69 system */
#define ANNOT_ARCH_EV7	11		/* EV7 system */

/* OS Revisions for object annotation data. */
#define ANNOT_OS_V30		2	/* Tru64 UNIX V3.0 or later */
#define ANNOT_OS_V40		3	/* Tru64 UNIX V4.0 or later */
#define ANNOT_OS_V50		4	/* Tru64 UNIX V5.0 or later */
#define ANNOT_OS_V51		5	/* Tru64 UNIX V5.1 or later */
#define ANNOT_OS_V51A		7	/* Tru64 UNIX V5.1A or later */
#define ANNOT_OS_V51B		8	/* Tru64 UNIX V5.1B or later */

/* Nil symbol for address, to distinguish procedures with no code */
#define addressNil         -1UL

#ifdef TANDEMSYM
/* FDR's "platform" settings */
#define platUndef  0
#define platGuard  1
#define platOss	   2
#define platPc	   3
#endif /* TANDEMSYM */

/* Obsolete definitions */
#define scDbx       scTlsUndefined  /* obsolete storage class */
#define scCdbSystem scTlsUndefined  /* obsolete storage class */
#define stModview   stUsing         /* obsolete symbol type */
#define mvOnly	    1               /* used with stModview */
#define mvRename    2               /* used with stModview */
#define mvExcept    3               /* used with stModview */

#endif /* _SYMCONST_H */
