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
/* $Header: /share/buffer/build/rcs.dsk1/os/src/usr/include/alpha/sym.h,v 1.2.30.1 2001/09/11 15:02:56 Randy_Lowell Exp $ */
#ifndef _SYM_H
#define _SYM_H

/* (C) Copyright 1984 by Third Eye Software, Inc.
 *
 * Third Eye Software, Inc. grants reproduction and use rights to
 * all parties, PROVIDED that this comment is maintained in the copy.
 *
 * Third Eye makes no claims about the applicability of this
 * symbol table to a particular use.
 */

#include <coff_type.h>

/* 
 * This file contains the definition of the Third Eye Symbol Table.
 *
 * Symbols are assumed to be in 'encounter order' - i.e. the order that
 * the things they represent were encountered by the compiler/assembler/loader.
 * EXCEPT for globals!	These are assumed to be bunched together,
 * probably right after the last 'normal' symbol.  Globals ARE sorted
 * in ascending order.
 *
 * -----------------------------------------------------------------------
 * A brief word about Third Eye naming/use conventions:
 *
 * All arrays and index's are 0 based.
 * All "ifooMax" values are the highest legal value PLUS ONE. This makes
 * them good for allocating arrays, etc. All checks are "ifoo < ifooMax".
 *
 * "isym"	Index into the SYMbol table.
 * "ipd"	Index into the Procedure Descriptor array.
 * "ifd"	Index into the File Descriptor array.
 * "iss"	Index into String Space.
 * "cb"		Count of Bytes.
 * "rgPd"	array whose domain is "0..ipdMax-1" and RanGe is PDR.
 * "rgFd"	array whose domain is "0..ifdMax-1" and RanGe is FDR.
 */


/* 
 * Symbolic Header (HDR) structure.
 * As long as all the pointers are set correctly,
 * we don't care WHAT order the various sections come out in!
 *
 * A file produced solely for the use of CDB will probably NOT have
 * any instructions or data areas in it, as these are available
 * in the original.
 */

#if defined(__LANGUAGE_C__) || defined(__cplusplus)

#ifdef __lint
#include <exception.h> 		/* defines struct exception_info */
#endif

typedef struct {
  coff_ushort	magic;		/* to verify validity of the table */
  coff_ushort	vstamp;		/* version stamp */
  coff_int	ilineMax;	/* number of line number entries */
  coff_int	idnMax;		/* max index into dense number table */
  coff_int	ipdMax;		/* number of procedures */
  coff_int	isymMax;	/* number of local symbols */
  coff_int	ioptMax;	/* byte size of optimization symbol entries */
  coff_int	iauxMax;	/* number of auxiliary symbol entries */
  coff_int	issMax;		/* max index into local strings */
  coff_int	issExtMax;	/* max index into external strings */
  coff_int	ifdMax;		/* number of file descriptor entries */
  coff_int	crfd;		/* number of relative file descriptors */
  coff_int	iextMax;	/* max index into external symbols */
  coff_long	cbLine;		/* number of bytes for line number entries */
  coff_off	cbLineOffset;	/* file offset of line number entries*/
  coff_off	cbDnOffset;	/* file offset of dense number table */
  coff_off	cbPdOffset;	/* file offset of procedure descriptor table */
  coff_off	cbSymOffset;	/* file offset of local symbols */
  coff_off	cbOptOffset;	/* file offset of optimization symbols */
  coff_off	cbAuxOffset;	/* file offset of auxiliary symbol entries*/
  coff_off	cbSsOffset;	/* file offset of local strings */
  coff_off	cbSsExtOffset;	/* file offset of external strings */
  coff_off	cbFdOffset;	/* file offset of file descriptor table */
  coff_off	cbRfdOffset;	/* file offset of relative file descriptors */
  coff_off	cbExtOffset;	/* file offset of external symbol entries */
  /* If you add machine dependent fields, add them here */
} HDRR, *pHDRR; 
#define cbHDRR sizeof(HDRR)
#define hdrNil ((pHDRR)0)

/*
 * The FDR and PDR structures speed mapping of address <-> name.
 * They are sorted in ascending memory order and are kept in
 * memory by CDB at runtime.
 */

/* 
 * File Descriptor
 *
 * There is one of these for EVERY FILE, whether compiled with
 * full debugging symbols or not.  The name of a file should be
 * the path name given to the compiler.	 This allows the user
 * to simply specify the names of the directories where the COMPILES
 * were done, and we will be able to find their files.
 *
 * Unless otherwise specified the "Base" fields are table indexes 
 * rather than byte offsets.  Likewise "count" fields give the number
 * of entries unless otherwise specified.  Together these fields identify
 * subtables which belong to the source file represented by this file
 * descriptor.
 */
typedef struct fdr {
  coff_addr	adr;		/* first text address of file */
  coff_long	cbLineOffset;	/* start of line number entries byte offset */
  coff_long	cbLine;		/* byte size of line entries */
  coff_long	cbSs;		/* byte size of local string space */
  coff_int	rss;		/* file name (of source, if known) */
  coff_int	issBase;	/* string space byte offset */
  coff_int	isymBase;	/* start of local symbols */
  coff_int	csym;		/* number of local symbols */
  coff_int	ilineBase;	/* start of expanded line numbers */
  coff_int	cline;		/* number of expanded line numbers */
  coff_int	ioptBase;	/* start of optimization entries byte offset */
  coff_int	copt;		/* byte size of file's optimization entries */
  coff_int	ipdFirst;	/* start of procedures descriptors */
  coff_int	cpd;		/* number of procedures descriptors */
  coff_int	iauxBase;	/* start of auxiliary entries */
  coff_int	caux;		/* number of file's auxiliary entries */
  coff_int	rfdBase;	/* start of file indirect table entries */
  coff_int	crfd;		/* number of file indirect entries */
  coff_uint	lang: 5;	/* language for this file */
  coff_uint	fMerge : 1;	/* whether this file can be merged */
  coff_uint	fReadin : 1;	/* true if it was read in (not just created) */
  coff_uint	fBigendian : 1;	/* if set, was compiled on big endian machine
				 * aux's will be in compile host's sex 
				 */
  coff_uint	glevel : 2;	/* level this file was compiled with */
  coff_uint	fTrim : 1;	/* whether the symbol table was trimmed */
#ifndef TANDEMSYM
  coff_uint     reserved : 4;   /* reserved for future use */
#else
  coff_uint     platform : 3;   /* platform associated with file */
  coff_uint     NonStop : 1;    /* NonStop process pair fault tolerance 
				 * support is enabled 
				 */
#endif
  coff_uint     fullExternals:1;/* If true, this file's local symbols contain
				 * stExternal entries for all external symbols
				 * visible within the scope of this file.
				 */
  coff_ushort	vstamp;		/* in a linked object, the value of HDRR.vstamp
				 * in the .o file input to the linker 
				 */
  coff_uint	reserved2;
} FDR, *pFDR;
#define cbFDR sizeof(FDR)
#define fdNil ((pFDR)0)
#define ifdNil -1
#define ifdTemp 0
#define ilnNil -1


/* 
 * Procedure Descriptor
 *
 * There is one of these for EVERY TEXT LABEL.
 * If a procedure is in a file with full symbols, then isym
 * will point to the PROC symbols, else it will point to the
 * global symbol for the label.
 *
 * Table offsets are relative to the subtable ranges of the containing
 * file descriptor.
 */
#ifndef TANDEMSYM
typedef struct pdr {
#else
typedef struct pdrv4 {
#endif /* TANDEMSYM */
  coff_addr	adr;		/* first text address of procedure */
  coff_long	cbLineOffset;	/* byte offset for this procedure */
  coff_int	isym;		/* start of local symbol entries */
  coff_int	iline;		/* start of line number entries*/
  coff_uint	regmask;	/* save register mask */
  coff_int	regoffset;	/* save register offset (reg_frame == 0)
				 * save-ra register number (reg_frame == 1) 
				 */
  coff_int	iopt;		/* byte offset of optimization symbols */
  coff_uint	fregmask;	/* save floating point register mask */
  coff_int	fregoffset;	/* save floating point register offset */
  coff_int	frameoffset;	/* frame size */
  coff_int	lnLow;		/* lowest line in the procedure */
  coff_int	lnHigh;		/* highest line in the procedure */
  coff_uint	gp_prologue:8; 	/* byte size of GP prologue */
  coff_uint	gp_used : 1;	/* true if the procedure uses GP */
  coff_uint	reg_frame : 1;	/* true if register frame procedure */
  coff_uint	prof : 1;	/* true if compiled with -pg */
  coff_uint	gp_tailcall:1;	/* may do tailcall from different gp domain */
#ifndef TANDEMSYM
  coff_uint     reserved4 : 4;  /* reserved: must be zero */
#else
  coff_uint     optlevel : 4;
#endif  
  coff_uint     no_stack_data:1;/* no data passed on stack */
  coff_uint     reserved : 7;   /* reserved: must be zero */
  coff_uint     localoff : 8;   /* offset of local variables from vfp */
  coff_ushort   framereg;       /* frame pointer register */
  coff_ushort   pcreg;          /* offset or reg of return pc */
#ifdef TANDEMSYM
  coff_uint     proctype : 16;
  coff_uint     reserved2 : 16; /* reserved: must be zero */
  coff_uint	reserved3;      /* reserved: must be zero */
} PDRV4, *pPDRV4;
#else /* TANDEMSYM */
} PDR, *pPDR;
#endif /* TANDEMSYM */
#define cbPDR sizeof(PDR)
#define pdNil ((pPDR) 0)
#define ipdNil	-1

/*
 * The structure of the runtime procedure descriptor created by the loader
 * for use by the static exception system.
 */
struct exception_info;

typedef struct runtime_pdr {
  coff_addr	adr;		/* memory address of start of procedure */
  coff_uint	regmask;	/* save register mask */
  coff_int	regoffset;	/* save register offset */
  coff_uint	fregmask;	/* save floating point register mask */
  coff_int	fregoffset;	/* save floating point register offset */
  coff_int	frameoffset;	/* frame size */
  coff_ushort	framereg;	/* frame pointer register */
  coff_ushort	pcreg;		/* offset or reg of return pc */
  coff_int	irpss;		/* index into the runtime string table */
  coff_uint	reserved;
  struct exception_info *exception_info;/* pointer to exception array */
} RPDR, *pRPDR;
#define cbRPDR sizeof(RPDR)
#define rpdNil ((pRPDR) 0)

/*
 * Line Numbers
 *
 * Line Numbers are segregated from the normal symbols because they
 * are [1] smaller , [2] are of no interest to your
 * average loader, and [3] are never needed in the middle of normal
 * scanning and therefore slow things down.
 *
 * By definition, the first LINER for any given procedure will have
 * the first line of a procedure and represent the first address.
 */

typedef	coff_int LINER, *pLINER;
#define lineNil ((pLINER)0)
#define cbLINER sizeof(LINER)
#define ilineNil	-1



/*
 * The Symbol Structure
 */

typedef struct {
  coff_long	value;		/* value of symbol */
  coff_int	iss;		/* index into String Space of name */
  coff_uint	st : 6;		/* symbol type */
  coff_uint	sc : 5;		/* storage class - text, data, etc */
  coff_uint	reserved : 1;	/* reserved */
  coff_uint	index : 20;	/* index into sym/aux table */
} SYMR, *pSYMR;
#define symNil ((pSYMR)0)
#define cbSYMR sizeof(SYMR)
#define isymNil -1
#define indexNil ((long)0xfffff)
#define issNil -1
#define issNull 0


/* E X T E R N A L   S Y M B O L  R E C O R D
 *
 *	Same as the SYMR except it contains file context to determine where
 *	the index is.  The SYMR's iss field points into the external string
 *	table.
 */
typedef struct {
  SYMR		asym;		/* symbol for the external */
  coff_uint	jmptbl:1;	/* symbol is a jump table entry for shlibs */
  coff_uint	cobol_main:1;	/* symbol is a cobol main procedure */
  coff_uint	weakext:1;	/* symbol is weak external */
  coff_uint     alignment:4;	/* symbol is for alignment of commons */
#ifdef TANDEMSYM
  coff_uint	xport:1;	/* export symbol from a shared library */
  coff_uint	multiext:1;	/* multiple definition of this symbol okay */
#else
  coff_uint	reserved2:2;	/* reserved for future use */
#endif
  coff_uint     linkerdef:1;	/* linker-defined symbol */
  coff_uint	reserved:22;	/* reserved for future use */
  coff_int	ifd;		/* where the index field points into */
} EXTR, *pEXTR;
#define extNil ((pEXTR)0)
#define cbEXTR sizeof(EXTR)


/* A U X I L I A R Y   T Y P E	 I N F O R M A T I O N
 *
 * Auxiliary information describes the type of each symbol.  The number
 * of AUX records required to describe a type depends upon the complexity
 * of that type.  The first record for a type is denoted by the index
 * field of a SYMR record.
 *
 * Types are composed of a basic type with zero or more type qualifiers.
 * A basic type is a core type supported by a language such as "integer",
 * "character", or "floating point".  Some basic types such as "structure"
 * or "set" can reference other types or other symbols.
 *
 * A type qualifier is a modifier for a type such as "pointer to", or
 * "array of".	If a type has more than one qualifier, they are ordered
 * from lowest to highest.  Lower qualifiers are applied to the basic
 * type before higher qualifiers.  To illustrate this, consider a
 * complex type such as "array of pointers to integers".  The basic type
 * for this is "integer" and there are two qualifiers, "array of" and
 * "pointer to".  Each element of the array is a "pointer to integer".
 * Therefore, the qualifier "pointer to" must be applied to the basic
 * type "integer" first.  In this example, the qualifier "pointer to" is
 * lower than the qualifier "array of".
 *
 * With this background, we can describe the structure of a type
 * description.	 AUX records must be decoded by starting at the first
 * record for a type description and decoding each successive record in
 * the context of the previous records.	 The following steps define an
 * algorithm for consuming AUX records and decoding a type description.
 * The numbered steps must be followed in order to consume the AUX
 * records correctly.
 *
 *	1. If this type description is pointed at by a symbol with type
 *	   stProc or stStaticProc, the first AUX is interpreted as an
 *	   'isym'.  Its value is the index of the local symbol table entry
 *	   that follows the procedure's stEnd symbol.
 *
 *	2. The next AUX is always a TIR record.	 This record contains
 *	   the basic type and the first few type qualifiers.  If more
 *	   type qualifiers are required, the TIR record has its
 *	   'continued' field set.  The type qualifiers are numbered from
 *	   0 to 5.  Qualifier 0 is the "lowest" (in the sense defined above).
 *
 *	3. If the TIR record has its 'fBitfield' field set, the next
 *	   AUX is interpreted as a 'width'.  The width is the size, in
 *	   bits, of the type.
 *
 *	4. The next AUX depends upon the basic type in the TIR record.
 *	   If the next AUX is an RNDXR record, it may occupy either one
 *	   or two AUX records.	See the RNDXR definition below for
 *	   details.
 *
 *		A) If the basic type is btStruct, btUnion, btEnum,
 *		   btClass, or btTypedef; the next AUX is an RNDXR
 *		   record.  The 'index' field of the RNDXR points into
 *		   the local symbol table.  The specified local symbol is
 *		   the start of the definition of the structure, union,
 *		   enumeration, class or typedef.
 *
 *		B) If the basic type is btSet, the next AUX is also an
 *		   RNDXR.  The 'index' field of the RNDXR points into
 *		   the AUX table.  The specified AUX record is the start
 *		   of the description of the type of each element in the
 *		   set.
 *
 *		C) If the basic type is btIndirect, the next AUX is
 *		   again an RNDXR whose 'index' field points into the
 *		   AUX table.  The specified AUX record is the start of
 *		   the description of the referenced type.
 *
 *		D) If the basic type is btRange, the next three AUX
 *		   records are used.  The next AUX is an RNDXR whose
 *		   'index' field points into the AUX table.  The
 *		   specified AUX is the start of the description of the
 *		   type being subranged.  The AUX following the RNDXR is
 *		   interpreted as a 'dnLow'.  This is the low bound of
 *		   the range.  The final AUX is interpreted as a
 *		   'dnHigh' and is the high bound of the range.
 *
 *	5. The next AUX depends on the type qualifiers in the TIR record.
 *	   Information for lower numbered type qualifiers is stored
 *	   before information for higher numbered qualifiers.
 *
 *		A) Each tqArray qualifier has four additional AUX
 *		   records.  The first is an RNDXR whose index field
 *		   points into the AUX table.  The AUX specified by this
 *		   RNDXR is the type of the index into the array.  The
 *		   AUX following the RNDXR is interpreted as a 'dnLow'.
 *		   This is the low dimension of the array.  The next AUX
 *		   is interpreted as a 'dnHigh' and is the high
 *		   dimension.  The final AUX is interpreted as a
 *		   'width'.  This is the size in bits of each element in
 *		   the array.
 *		B) Each tqASharArr_64 acts as if it were a tqArray_64 with two
 *		   additional AUXES representing the slice. The Slice
 *		   describes how the memory for the array is distributed
 *		   across available processors.
 *
 *	6. If the TIR record has its 'continued' field set, the next AUX
 *	   is another TIR record.  Only the type qualifier and
 *	   'continued' fields of this TIR are important.  The qualifiers
 *	   in this TIR are all "higher" than the qualifiers in the previous
 *	   TIR.	 Additional AUX records are decoded as described in step 5.
 *	   If this TIR has its 'continued' field set, repeat step 6.  The
 *	   process stops when we reach a TIR with its 'continued' field
 *	   cleared.  
 */

/*
 * Type Information Record 
 */
typedef struct {
  coff_uint	fBitfield : 1;	/* set if bit width is specified */
  coff_uint	continued : 1;	/* indicates additional TQ info to follow */
  coff_uint	bt  : 6;	/* basic type */
  coff_uint	tq4 : 4;
  coff_uint	tq5 : 4;
  /* ---- 16 bit boundary ---- */
  coff_uint	tq0 : 4;
  coff_uint	tq1 : 4;	/* 6 type qualifiers - tqPtr, etc. */
  coff_uint	tq2 : 4;
  coff_uint	tq3 : 4;
} TIR, *pTIR;
#define cbTIR sizeof(TIR)
#define tiNil ((pTIR)0)
#define itqMax 6

/*
 * Relative symbol record
 *
 * If the rfd field is ST_RFDESCAPE, the isym field of the next AUX record is
 * the index into the file indirect table.
 */

typedef struct {
  coff_uint	rfd : 12;	/* index into the file indirect table */
  coff_uint	index : 20;	/* index int sym/aux/iss tables */
} RNDXR, *pRNDXR;
#define cbRNDXR sizeof(RNDXR)
#define rndxNil ((pRNDXR)0)

/* a union of all possible info in the AUX universe */
typedef union {
  TIR		ti;		/* type information record */
  RNDXR		rndx;		/* relative index into symbol table */
  coff_int	dnLow;		/* low dimension */
  coff_int	dnHigh;		/* high dimension */
  coff_int	isym;		/* symbol table index (end of proc) */
  coff_int	iss;		/* index into string space (not used) */
  coff_int	width;		/* width for non-default sized struc fields */
  coff_int	count;		/* count of ranges for variant arm */
  coff_int	slice;		/* how the memory for the array is distributed
				 * across available processors. */
} AUXU, *pAUXU;
#define cbAUXU sizeof(AUXU)
#define auxNil ((pAUXU)0)
#define iauxNil -1


/*
 * Optimization symbols
 *
 * Optimization symbols consist of a sequence of zero or more "per
 * procedure optimization descriptions" (PPOD).	 Each PPOD is pointed
 * to by the "iopt" field of the procedure descriptor (PDR).
 */

typedef struct {
  coff_uint	ppode_tag;
  coff_uint	ppode_len;
  coff_ulong	ppode_val;
} PPODHDR, *pPPODHDR;

/* The pOPTR type below must be used when calculating offsets within the
 * optimization symbols section.  The optimization symbol section is 
 * composed of both PPODHDR entries and freeform data, so counts and 
 * offsets within the section are recorded in bytes.
 */

#define cbOPTR	 1
typedef coff_byte OPTR;
typedef coff_byte *pOPTR;
#define optNil	((pOPTR) 0)
#define ioptNil -1


/* Semantic Event Information (PPODE_SEM_EVENT == 4)
 *
 * The raw data for semantic event information is an array of the following
 * element type:
 */ 

typedef struct {
    coff_ubyte	sem_event;  /* count:4, event:4 */
} PPODSE, * pPPODSE;

typedef PPODSE*		PPODSE_ARRAY;

/* The following macros can be used to extract the count and event fields
 * from a PPODE and to make a PPODE:
 */ 
#define PPODSE_count(ppode)	  ( (ppode)	  & 0x0f)
#define PPODSE_event(ppode)	  (((ppode) >> 4) & 0x0f)
#define PPODSE_make(count, event) ((((event) & 0x0f) << 4) + ((count) & 0x0f))

/* The PPODSE count field is a integer from 0 thru 15, which indicates the 
 * number of instructions from the previous semantic event location to this 
 * one. An offset of 0 is valid -- and is used when more than one semantic 
 * event applies to the same instruction. Conversely, if there are more than 
 * 15 instructions between events, then multiple occurences of the "no event"
 * event code (PPODSE_NONE) can be used to add up to the required
 * amount.
 *
 * event is a code for the kind of event that applies to the indicated
 * instruction. See symconst.h for the definitions of the PPODSE codes.
 */

/* Split Lifetime Information (PPODE_SPLIT == 5)
 *
 * Split lifetime information consists of sequence of discontiguous lifetime
 * segment values (terminated as implied by the ppode_len field), where each
 * segment is encoded as follows:
 *
 *    - Target variable specifier
 *    - Child description scheme
 *    - Counted sequence of child descriptions
 */
typedef struct {
    coff_ubyte	target;	  /* target_type:4, target_scheme:4 */
} PPODE_SPLIT_DESC, *pPPODE_SPLIT_DESC;

/* The following macros can be used to extract the target_type and 
 * target_scheme fields from a PPODE and to make a PPODE:
 */ 
#define PPODE_SPLIT_DESC_type(ppode)	  ( (ppode)	  & 0x0f)
#define PPODE_SPLIT_DESC_scheme(ppode)	  (((ppode) >> 4) & 0x0f)
#define PPODE_SPLIT_DESC_make(type, scheme) ((((event) & 0x0f) << 4) + ((count) & 0x0f))

/* The target_type field is set to one of the following values.
 *
 * PPODE_SPLIT_TYPE_EXT is used when the split information applies to a symbol
 * in the external symbol table. The name string follows as a null terminated
 * string.
 *
 * PPODE_SPLIT_TYPE_LCL is used when the split information applies to a symbol
 * in the local symbol table. The symbol is identified using an OPT RNDX (see
 * below), which immediately follows.
 */

/* The target_scheme field is set to one of the following values.
 *
 * PPODE_SPLIT_SCHEME_DEF indicates a "normal" definition sequence of child
 * lifetimes (see below).
 *
 * PPODE_SPLIT_SCHEME_DUP indicates re-use of a clild lifetime sequence that
 * is already present for a previous symbol. The previous symbol is identified
 * using an OPT RNDX (see below). There are two cases where the duplicate
 * scheme comes into play:
 *
 *    - When a FORTRAN subprogram with alternate entry points has a parameter
 *	that is passed in more than one entry, the local table for the
 *	procedure will contain duplicate parameter STEs in the applicable
 *	prologue regions (the STEs that occur between the stProc and following
 *	stBegin STE).
 *
 *    - More generally, any time that two user variables are allocated to
 *	exactly the same storage locations.
 */

/* OPT RNDX
 *
 * An OPT RNDX is a AUX RNDX-like pointer that occurs in the optimization
 * symbols section. It consists of two values:
 *
 *    - a relative file descriptor index
 *
 *    - a local symbol index within the given file
 *
 * both expressed as unsigned LEB integers.
 */

/* Child Description Sequence
 *
 * The sequence of child descriptions begins with an unsigned LEB count of the
 * number of entries in the sequence.
 *
 * Child Description
 * 
 * Each child description consists of a child location description consisting
 * of the sc, st and value data that would be used to describe a variable in
 * that same location, followed by a counted sequence of PC ranges (over which
 * that location applies).
 */

/* PC Ranges
 *
 * The first PC range of a split variable description begins with an signed
 * LEB value giving the beginning instruction in the sequence relative to the
 * base address of the containing procedure (as expressed in the appropriate
 * procedure descriptor, PDR). For subsequent ranges, the beginning of	the
 * range is relative to the instruction following the end of the previous
 * range.
 *
 * The second value of each range is an unsigned count of the number of
 * instructions that are included in the range.
 */

/* Discontiguous Scope Information (PPODE_DISCONTIG == 6)
 *
 * Definitions will be provided in a future release.
 */


/* Inlined Procedure Call Information (PPODE_INLINED_CALL == 7)
 *
 * Definitions will be provided in a future release.
 */

/* Object Annotation Summary Header 
 * (PPODE_ANNOT_SUMMARY == 64)
 */
typedef struct {
    coff_uint version : 8;
    coff_uint safe_pc_usage : 1;
    coff_uint safe_gp_usage : 1;
    coff_uint safe_references : 1;
    coff_uint safe_targets : 1;
    coff_uint safe_frame : 1;
    coff_uint safe_calls : 1;
    coff_uint safe_linkage : 1;
    coff_uint safe_floating_use : 1;
    coff_uint arch : 8;
    coff_uint tune : 8;
    coff_uint os_version : 8;
    coff_uint jump_table_annot : 1;
    coff_uint reserved : 23;
} ANNOT_SUMMARY_VAL, *pANNOT_SUMMARY_VAL;

/* Object Annotation Restricted Offset Flags
 * (PPODE_ANNOT_RESTRICTED_OFFSET == 65)
 */
typedef struct {
    coff_uint volatile_target : 1;
    coff_uint handler_target : 1;
    coff_uint nonlocal_referenced : 1;
    coff_uint uplevel_referenced : 1;
    coff_uint exception_fence : 1;
    coff_uint soft_order : 1;
} ANNOT_RESTRICTED_OFFSET_FLAGS, *pANNOT_RESTRICTED_OFFSET_FLAGS;

/* Object Annotation Restricted Instruction Flags
 * (PPODE_ANNOT_RESTRICTED_INSTRUCTION == 66)
 */
typedef struct {
    coff_uint io_volatile : 1;
    coff_uint must_read : 1;
    coff_uint must_write : 1;
    coff_uint preserve_exceptions : 1;
    coff_uint no_exception : 1;
} ANNOT_RESTRICTED_INSTRUCTION_FLAGS, *pANNOT_RESTRICTED_INSTRUCTION_FLAGS;

/* Object Annotation Restricted Sequence Flags
 * (PPODE_ANNOT_RESTRICTED_SEQUENCE == 67)
 */
typedef struct {
    coff_uint nomove : 1;
    coff_uint noreorder : 1;
    coff_uint noschedule : 1;
    coff_uint reserved : 5;
    coff_uint arch : 8;
    coff_uint tune : 8;
} ANNOT_RESTRICTED_SEQUENCE_FLAGS, *pANNOT_RESTRICTED_SEQUENCE_FLAGS;

/* Object Annotation Restricted Call Flags
 * (PPODE_ANNOT_RESTRICTED_CALL == 68)
 */
typedef struct {
    coff_uint extra_inputs : 1;
    coff_uint extra_outputs : 1;
    coff_uint extra_kill : 1;
    coff_uint nonstandard_flow : 1;
    coff_uint stack_return : 1;
} ANNOT_RESTRICTED_CALL_FLAGS, *pANNOT_RESTRICTED_CALL_FLAGS;

/* Object Annotation Restricted Entry Flags
 * (PPODE_ANNOT_RESTRICTED_ENTRY == 69)
 */
typedef struct {
    coff_uint extra_inputs : 1;
    coff_uint nonstandard_save_kill : 1;
} ANNOT_RESTRICTED_ENTRY_FLAGS, *pANNOT_RESTRICTED_ENTRY_FLAGS;

/* Object Annotation Restricted Return Flags
 * (PPODE_ANNOT_RESTRICTED_RETURN == 70)
 */
typedef struct {
    coff_uint extra_outputs : 1;
    coff_uint nonstandard_save_kill : 1;
} ANNOT_RESTRICTED_RETURN_FLAGS, *pANNOT_RESTRICTED_RETURN_FLAGS;

/* Object Annotation Linkage Flags
 */
typedef struct {
    coff_uint previous_masks : 1;
    coff_uint must_not_inline : 1;
    coff_uint requires_call : 1;
    coff_uint abnormal_flow : 1;
} ANNOT_LINKAGE_FLAGS, *pANNOT_LINKAGE_FLAGS;

/*
 * Dense number record
 *
 * Rather than use file index, symbol index pairs to represent symbols
 *	and globals, we use dense number so that they can be easily embedded
 *	in intermediate code and the programs that process them can
 *	use direct access tables instead of hash table (which would be
 *	necessary otherwise because of the sparse name space caused by
 *	file index, symbol index pairs.	 Ucode uses the term block
 *	number instead of dense number.
 *
 * If the rfd field is ST_EXTIFD, the index field points into the external
 *	symbol table.  If the index field is ST_ANONINDEX, it is an anonymous
 *	entry and does not index any table.
 */
typedef struct {
  coff_uint	rfd;	/* index into the file table */
  coff_uint	index;	/* index into sym table */
} DNR, *pDNR;
#define cbDNR sizeof(DNR)
#define dnNil ((pDNR)0)


/*
 * File Indirect
 *
 * When a symbol is referenced across files the following procedure is used:
 *	1) use the file index to get the File indirect entry.
 *	2) use the file indirect entry to get the File descriptor.
 *	3) add the sym index to the base of that file's sym table
 *
 */

typedef coff_int RFDT, *pRFDT;
#define cbRFDT sizeof(RFDT)
#define rfdNil	-1

/*
 * The file indirect table is simply another name used by the linker for the 
 * relative file descriptors.
 */
typedef coff_int FIT, *pFIT;
#define cbFIT	sizeof(FIT)
#define ifiNil	-1
#define fiNil	((pFIT) 0)

#endif	/* __LANGUAGE_C__ */

#ifdef __LANGUAGE_PASCAL__
#define ifdNil -1
#define ilnNil -1
#define ipdNil -1
#define ilineNil -1
#define isymNil -1
#define indexNil 16#fffff
#define issNil -1
#define issNull 0
#define itqMax 6
#define iauxNil -1
#define ioptNil -1
#define rfdNil -1
#define ifiNil -1
#endif	/* __LANGUAGE_PASCAL__ */


/*
 * The following table defines the meaning of each SYM field as
 * a function of the "st". (scD/B is any of scData, scSData, scBss,
 * scSBss, scRData, or scRConst)
 *
 * Note: the value "isymMac" is used by symbols that have the concept
 * of enclosing a block of related information.	 This value is the
 * isym of the first symbol AFTER the end associated with the primary
 * symbol. For example if a procedure was at isym==90 and had an
 * isymMac==155, the associated end would be at isym==154, and the
 * symbol at 155 would probably (although not necessarily) be the
 * symbol for the next procedure.  This allows rapid skipping over
 * internal information of various sorts. "stEnd"s ALWAYS have the
 * isym of the primary symbol that started the block.
 * 

ST		SC	VALUE		INDEX
--------	------	--------	------
stFile		scText	-------		isymMac
stLabel		scText	address		---
stGlobal	scD/B	address		iaux
stStatic	scD/B	address		iaux
stParam		scAbs	offset		iaux
stLocal		scAbs	offset		iaux
stProc		scText	address		iaux	(isymMac is first AUX)
stStaticProc	scText	address		iaux	(isymMac is first AUX)

stMember	scNil	ordinal		---	(if member of enum)
stMember	scNil	byte offset	iaux	(if member of struct/union)
stMember	scBits	bit offset	iaux	(bit field spec)

stBlock		scText	offset		isymMac (text block, offset from proc)
stBlock		scNil	cb		isymMac (struct/union member define)
stBlock		scNil	cMembers	isymMac (enum member define)

stEnd		scText	offset		isymStart (offset from proc start)
stEnd		scNil	-------		isymStart (struct/union/enum)

stTypedef	scNil	-------		iaux
stRegReloc	sc???	value		old register number
stForward	sc???	new address	isym to original symbol

stConstant	scInfo	value		--- (scalar)
stConstant	scInfo	iss		--- (complex, e.g. string)

 *
 */
#endif
