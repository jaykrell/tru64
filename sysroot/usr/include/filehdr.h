/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: filehdr.h,v $
 * Revision 1.2.29.2  2003/06/19  13:26:48  Matthew_McGrath
 * 	Added F_COMMENT flag
 *
 * Revision 1.2.29.1  2003/01/07  15:17:58  Andy_Kern
 * 	Initial Chatr submit
 * 	Added F_WXALLOW flag
 *
 * Revision 1.2.17.1  2001/09/11  15:02:48  Randy_Lowell
 * 	Copy changes from wildcat pool.
 *
 * Revision 1.2.14.1  2001/04/11  18:06:45  Randy_Lowell
 * 	Added __EXEC_FLAGS flags
 *
 * Revision 1.2.10.2  1997/12/29  21:23:19  Randy_Lowell
 * 	Updated basic types
 * 	[1997/12/04  16:27:32  Randy_Lowell]
 *
 * 	Added basic abstract types for coff structures
 * 	[1997/10/02  19:31:30  Randy_Lowell]
 *
 * 	Provided named constants without MIPS designator
 * 	[1997/09/25  18:02:44  Randy_Lowell]
 *
 * Revision 1.2.8.2  1994/11/15  16:32:54  Lee_Miller
 * 	add support for compressed .o files
 * 	[1994/11/03  19:43:59  Lee_Miller]
 * 
 * Revision 1.2.6.5  1994/04/19  17:28:06  Anton_Verhulst
 * 	Add F_LOMAP define. Add warning that changes in this file must
 * 	be reflected in ./src/kernel/sysV/filehdr.h.
 * 	[1994/04/18  17:59:41  Anton_Verhulst]
 * 
 * Revision 1.2.6.4  1994/04/01  21:13:09  Randy_Lowell
 * 	Added F_MIPS_SHARE_MASK
 * 	[1994/03/30  19:15:16  Randy_Lowell]
 * 
 * Revision 1.2.6.3  1994/02/24  23:52:38  Chris_Gillett
 * 	Adding the F_NO_SHARED and F_NO_CALL_SHARED flags to the format.
 * 	This is in support of marking objects w/r/t symbol preemption
 * 	status.
 * 	[1994/02/23  21:31:07  Chris_Gillett]
 * 
 * Revision 1.2.6.2  1994/01/07  18:29:41  Thomas_Peterson
 * 	Merged C++ header changes fwd from sterl bl9 to gold bl8
 * 	[1994/01/05  17:22:32  Thomas_Peterson]
 * 
 * Revision 1.2.4.2  1993/12/15  22:12:45  Thomas_Peterson
 * 	Added __cplusplus conditional everywhere __LANGUAGE_C__ is used.
 * 	[1993/12/09  15:10:04  Thomas_Peterson]
 * 
 * Revision 1.2.2.5  1993/01/07  13:14:36  Mike_Rickabaugh
 * 	Added F_MIPS_NO_REMOVE and F_MIPS_NO_REORG flags in object file header.
 * 	[93/01/07  13:11:09  Mike_Rickabaugh]
 * 
 * Revision 1.2.2.4  92/05/27  12:49:15  Ken_Lesniak
 * 	mips 3.10 alpha update
 * 	[92/05/27  12:45:17  Ken_Lesniak]
 * 
 * Revision 1.2.2.3  92/04/02  17:27:12  Mike_Rickabaugh
 * 	Corrected underscores for LANGUAGE_<language>
 * 	[92/04/02  17:23:31  Mike_Rickabaugh]
 * 
 * Revision 1.2.2.2  92/04/01  15:40:04  Ken_Lesniak
 * 	sync up with compiler pool
 * 	[92/04/01  14:15:39  Ken_Lesniak]
 * 
 * Revision 1.2  92/01/15  02:34:21  devbld_gsf
 * 	Baselevel alpha_bl002
 * 
 * Revision 1.1.2.2  91/12/09  16:02:43  Anton_Verhulst
 * 	Merge in TIN-alpha changes.
 * 	[91/12/09  15:59:13  Anton_Verhulst]
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
/* $Header: /share/buffer/build/rcs.dsk1/os/src/usr/include/alpha/filehdr.h,v 1.2.29.2 2003/06/19 13:26:48 Matthew_McGrath Exp $ */
#ifndef _FILEHDR_H
#define _FILEHDR_H
/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
 * Any changes in this file should be replicated in ./src/kernel/sysV/filehdr.h.
 */

#include <coff_type.h>

#if defined(__LANGUAGE_C__) || defined(__cplusplus)
struct filehdr {
	coff_ushort	f_magic;	/* magic number */
	coff_ushort	f_nscns;	/* number of sections */
	coff_int	f_timdat;	/* time & date stamp */
	coff_off	f_symptr;	/* file pointer to symbolic header */
	coff_int	f_nsyms;	/* sizeof(symbolic hdr) */
	coff_ushort	f_opthdr;	/* sizeof(optional hdr) */
	coff_ushort	f_flags;	/* flags */
	};
#endif /* __LANGUAGE_C__ || __cplusplus */

#ifdef __LANGUAGE_PASCAL__
type
  filehdr = packed record
      f_magic : coff_ushort; 		/* magic number 		     */
      f_nscns : coff_ushort; 		/* number of sections		     */
      f_timdat : coff_int;		/* time & date stamp		     */
      f_symptr : coff_off;		/* file pointer to symbolic header   */
      f_nsyms : coff_int;		/* sizeof(symbolic hdr) 	     */
      f_opthdr : coff_ushort;		/* sizeof(optional hdr) 	     */
      f_flags : coff_ushort; 		/* flags			     */
    end {record};
#endif /* __LANGUAGE_PASCAL__ */

/*
 *   Bits for f_flags:
 *
 *	F_RELFLG	relocation info stripped from file
 *	F_EXEC		file is executable  (i.e. no unresolved
 *				externel references)
 *	F_LNNO		line nunbers stripped from file
 *	F_LSYMS		local symbols stripped from file
 *	F_MINMAL	this is a minimal object file (".m") output of fextract
 *	F_UPDATE	this is a fully bound update file, output of ogen
 *	F_SWABD		this file has had its bytes swabbed (in names)
 *	F_AR16WR	this file has the byte ordering of an AR16WR (e.g. 11/70) machine
 *				(it was created there, or was produced by conv)
 *	F_AR32WR	this file has the byte ordering of an AR32WR machine(e.g. vax)
 *	F_AR32W		this file has the byte ordering of an AR32W machine (e.g. 3b,maxi,MC68000)
 *	F_PATCH		file contains "patch" list in optional header
 *	F_NODF		(minimal file only) no decision functions for
 *				replaced functions
 */

#if defined(__LANGUAGE_C__) || defined(__cplusplus)
#define  F_RELFLG	0000001
#define  F_EXEC		0000002
#define  F_LNNO		0000004
#define  F_LSYMS	0000010
#define  F_MINMAL	0000020
#define  F_UPDATE	0000040
#define  F_SWABD	0000100
#define  F_AR16WR	0000200
#define  F_WXALLOW      F_AR16WR
#define  F_AR32WR	0000400
#define  F_COMMENT	F_AR32WR
#define  F_AR32W	0001000
#define  F_PATCH	0002000
#define  F_NODF		0002000
#define  F_64INT	0004000		/* basic int is 64 bits */
#endif /* __LANGUAGE_C__ || __cplusplus */

#ifdef __LANGUAGE_PASCAL__
#define  F_RELFLG	16#0001
#define  F_EXEC		16#0002
#define  F_LNNO		16#0004
#define  F_LSYMS	16#0008
#define  F_MINMAL	16#0010
#define  F_UPDATE	16#0020
#define  F_SWABD	16#0040
#define  F_AR16WR       16#0080
#define  F_WXALLOW	F_AR16WR
#define  F_AR32WR	16#0100
#define  F_COMMENT	F_AR32WR
#define  F_AR32W	16#0200
#define  F_PATCH	16#0400
#define  F_NODF		16#0400
#define  F_64INT	16#0800		/* basic int is 64 bits */
#endif /* __LANGUAGE_PASCAL__ */

/*
 *	BELLMAC-32	Identification field
 *	F_BM32B		file contains BM32B code (as opposed to strictly BM32A)
 *	F_BM32MAU	file requires MAU (math arith unit) to execute
 */

#define	F_BM32ID	0160000
#define	F_BM32MAU	0040000
#define F_BM32B         0020000

/*	F_BM32RST	file has RESTORE work-around	*/
#define F_BM32RST	0010000

/*
 *	Flags for the INTEL chips.  If the magic number of the object file
 *	is IAPX16 or IAPX16TV or IAPX20 or IAPX20TV then if F_80186
 *	is set, there are some 80186 instructions in the code, and hence
 *	and 80186 or 80286 chip must be used to run the code.
 *	If F_80286 is set, then the code has to be run on an 80286 chip.
 *	And if neither are set, then the code can run on an 8086, 80186, or
 *	80286 chip.
 *	
 */

#define F_80186		    010000
#define F_80286		    020000

#define	F_LOMAP		    F_SWABD	/* allow addrs < VM_MIN_ADDRESS */

/*
 * doesn't hurt to overload these bits since they are processor dependent
 */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
#define F_SHARE_MASK   030000
#define F_NON_SHARED   010000
#define F_SHARABLE     020000
#define F_CALL_SHARED  030000
#define F_NO_REORG     040000        /* may remove nops */
#define F_NO_REMOVE    0100000       /* won't remove nops */
#endif
#ifdef __LANGUAGE_PASCAL__
#define F_SHARE_MASK   16#03000
#define F_NON_SHARED   16#01000
#define F_SHARABLE     16#02000
#define F_CALL_SHARED  16#03000
#define F_NO_REORG     16#04000
#define F_NO_REMOVE    16#08000
#endif

#if defined(__LANGUAGE_C__) || defined(__cplusplus)
/* 
**  Flags for symbol preemption and object marking.  
**  These flags indicate whether or not an object support symbol
**  preemption.  
**
**  These are equivalenced to flags that we've stolen from an implementatio-defined
**  section that isn't being used for anything else.  Note that these are "contra
**  flags" in that a 0x0 means TRUE, and a 0x1 means false.  So, the default where both
**  flags are 0x0 is that the object is sharable.
**
*/

#define F_NO_SHARED        F_MINMAL
#define F_NO_CALL_SHARED   F_UPDATE
#endif


/*
 *   Magic Numbers
 */

	/* iAPX - the stack frame and return registers differ from
	 * 	  Basic-16 and x86 C compilers, hence new magic numbers
	 *	  are required.  These are cross compilers.
	 */

	/* Intel */
#define  IAPX16		0504
#define  IAPX16TV	0505
#define  IAPX20		0506
#define  IAPX20TV	0507
/* 0514, 0516 and 0517 reserved for Intel */

	/* __mips */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
#define	 MAGIC_ARCH_MASK		0x00FF
#define	 MAGIC_ARCH_SHFT		0
#define	 MAGIC_S_ARCH_MASK		0xFF00
#define	 MAGIC_S_ARCH_SHFT		8
#define  MIPSEBMAGIC	0x0160
#define  MIPSELMAGIC	0x0162
#define  SMIPSEBMAGIC	0x6001
#define  SMIPSELMAGIC	0x6201
#define  MIPSEBUMAGIC	0x0180
#define  MIPSELUMAGIC	0x0182
#endif /* _LANGUAGE_C */
#ifdef __LANGUAGE_PASCAL__
#define	 MAGIC_ARCH_MASK		16#00FF
#define	 MAGIC_ARCH_SHFT		0
#define	 MAGIC_S_ARCH_MASK		16#FF00
#define	 MAGIC_S_ARCH_SHFT		8
#define  MIPSEBMAGIC	16#0160
#define  MIPSELMAGIC	16#0162
#define  SMIPSEBMAGIC	16#6001
#define  SMIPSELMAGIC	16#6201
#define  MIPSEBUMAGIC	16#0180
#define  MIPSELUMAGIC	16#0182
#endif
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
#define  MIPSEBMAGIC_2	0x0163
#define  MIPSELMAGIC_2	0x0166
#define  SMIPSEBMAGIC_2	0x6301
#define  SMIPSELMAGIC_2	0x6601
#endif /* __LANGUAGE_C__ || __cplusplus */
#ifdef __LANGUAGE_PASCAL__
#define  MIPSEBMAGIC_2	16#0163
#define  MIPSELMAGIC_2	16#0166
#define  SMIPSEBMAGIC_2	16#6301
#define  SMIPSELMAGIC_2	16#6601
#endif
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
#define  MIPSEBMAGIC_3	0x0140
#define  MIPSELMAGIC_3	0x0142
#define  SMIPSEBMAGIC_3	0x4001
#define  SMIPSELMAGIC_3	0x4201
#define  MAGIC_MIPS1	0x0062
#define  MAGIC_MIPS2	0x0066
#define  MAGIC_MIPS3	0x0042
#endif /* __LANGUAGE_C__ || __cplusplus */
#ifdef __LANGUAGE_PASCAL__
#define  MIPSEBMAGIC_3	16#0140
#define  MIPSELMAGIC_3	16#0142
#define  SMIPSEBMAGIC_3	16#4001
#define  SMIPSELMAGIC_3	16#4201
#define  MAGIC_MIPS1	16#0062
#define  MAGIC_MIPS2	16#0066
#define  MAGIC_MIPS3	16#0042
#endif

	/* __alpha */
#ifdef __LANGUAGE_PASCAL__
#define ALPHAMAGIC	8#603
#define ALPHAUMAGIC	8#617	/* U-code object file */
#else
#define ALPHAMAGIC	0603
#define ALPHAMAGICZ	0610    /* compressed object file */
#define ALPHAUMAGIC	0617	/* U-code object file */
#endif

#if defined(__LANGUAGE_C__) || defined(__cplusplus)
#define IS_MIPSEBMAGIC(x) ((x) == MIPSEBMAGIC || (x) == MIPSEBMAGIC_2 || (x) == MIPSEBMAGIC_3)
#define IS_SMIPSEBMAGIC(x) ((x) == SMIPSEBMAGIC || (x) == SMIPSEBMAGIC_2 || (x) == SMIPSEBMAGIC_3)
#define IS_MIPSELMAGIC(x) ((x) == MIPSELMAGIC || (x) == MIPSELMAGIC_2 || (x) == MIPSELMAGIC_3)
#define IS_SMIPSELMAGIC(x) ((x) == SMIPSELMAGIC || (x) == SMIPSELMAGIC_2 || (x) == SMIPSELMAGIC_3)
#define IS_ALPHAMAGIC(x) ((x) == ALPHAMAGIC)
#endif /* __LANGUAGE_C__ || __cplusplus */

	/* Basic-16 */
#define  B16MAGIC	0502
#define  BTVMAGIC	0503

	/* x86 */
#define  X86MAGIC	0510
#define  XTVMAGIC	0511

	/* Intel 286 */
#define I286SMAGIC	0512
#define I286LMAGIC	0522	/* used by mc68000 (UNIX PC) and iAPX 286 */

	/* n3b */
/*
 *   NOTE:   For New 3B, the old values of magic numbers
 *		will be in the optional header in the structure
 *		"aouthdr" (identical to old 3B aouthdr).
 */
#define  N3BMAGIC	0550	/* 3B20 executable, no TV */
#define  NTVMAGIC	0551	/* 3B20 executable with TV */

	/*  XL  */
#define	 XLMAGIC	0540

	/*  MAC-32, 3B15, 3B5  */
#define  WE32MAGIC	0560	/* WE 32000, no TV */
#define  FBOMAGIC	0560	/* WE 32000, no TV */
#define  RBOMAGIC	0562	/* reserved for WE 32000 */
#define  MTVMAGIC	0561	/* WE 32000 with TV */

	/* VAX 11/780 and VAX 11/750 */

			/* writeable text segments */
#define VAXWRMAGIC	0570
			/* readonly sharable text segments */
#define VAXROMAGIC	0575

	/* pdp11 */
/*			0401	UNIX-rt ldp */
/*			0405	pdp11 overlay */
/*			0407	pdp11/pre System V vax executable */
/*			0410	pdp11/pre System V vax pure executable */
/*			0411	pdp11 seperate I&D */
/*			0437	pdp11 kernel overlay */


	/* Motorola 68000/68008/68010/68020 */
#define	MC68MAGIC	0520
#define MC68KWRMAGIC	0520	/* writeable text segments */
#define	MC68TVMAGIC	0521
#define MC68KROMAGIC	0521	/* readonly shareable text segments */
#define MC68KPGMAGIC	0522	/* demand paged text segments */
#define	M68MAGIC	0210
#define	M68TVMAGIC	0211


	/* IBM 370 */
#define	U370WRMAGIC	0530	/* writeble text segments	*/
#define	U370ROMAGIC	0535	/* readonly sharable text segments	*/
/* 0532 and 0533 reserved for u370 */

	/* Amdahl 470/580 */
#define AMDWRMAGIC	0531	/* writable text segments */
#define AMDROMAGIC	0534	/* readonly sharable text segments */

	/* NSC */
/* 0524 and 0525 reserved for NSC */

	/* Zilog */
/* 0544 and 0545 reserved for Zilog */

#define	FILHDR	struct filehdr
#define	FILHSZ	sizeof(FILHDR)

#define ISCOFF(x) \
		(((x)==B16MAGIC) || ((x)==BTVMAGIC) || ((x)==X86MAGIC) \
		|| ((x)==XTVMAGIC) || ((x)==N3BMAGIC) || ((x)==NTVMAGIC) \
		|| ((x)==FBOMAGIC) || ((x)==VAXROMAGIC) || ((x)==VAXWRMAGIC) \
		|| ((x)==RBOMAGIC) || ((x)==MC68TVMAGIC) \
		|| ((x)==MC68MAGIC) || ((x)==M68MAGIC) || ((x)==M68TVMAGIC) \
		|| ((x)==IAPX16) || ((x)==IAPX16TV) \
		|| ((x)==IAPX20) || ((x)==IAPX20TV) \
		|| ((x)==MIPSEBMAGIC) || ((x)==MIPSELMAGIC) \
		|| ((x)==SMIPSEBMAGIC) || ((x)==SMIPSELMAGIC) \
		|| ((x)==MIPSEBUMAGIC) || ((x)==MIPSELUMAGIC) \
		|| ((x)==MIPSEBMAGIC_2) || ((x)==MIPSELMAGIC_2) \
		|| ((x)==SMIPSEBMAGIC_2) || ((x)==SMIPSELMAGIC_2) \
		|| ((x)==U370WRMAGIC) || ((x)==U370ROMAGIC) || ((x)==MTVMAGIC) \
		|| ((x)==I286SMAGIC) || ((x)==I286LMAGIC) \
		|| ((x)==MC68KWRMAGIC) || ((x)==MC68KROMAGIC) \
		|| ((x)==MC68KPGMAGIC) \
		|| ((x)==ALPHAMAGIC))

/* These flags are defined for the __EXEC_FLAGS symbol described
 * in the end(1) reference page.
 */
#define __EXEC_FLAG_TASO     0x1
#define __EXEC_FLAG_UNKNOWN  0x8000000000000000

/* Obsolete MIPS specific definitions */
#define F_MIPS_SHARE_MASK   F_SHARE_MASK
#define F_MIPS_NO_SHARED    F_NON_SHARED
#define F_MIPS_SHARABLE     F_SHARABLE
#define F_MIPS_CALL_SHARED  F_CALL_SHARED
#define F_MIPS_NO_REORG     F_NO_REORG
#define F_MIPS_NO_REMOVE    F_NO_REMOVE

#endif
