/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: stsupport.h,v $
 * Revision 4.2.20.1  2002/12/18  21:17:48  Randy_Lowell
 * 	Added plinefd for ESLI file transitions
 *
 * Revision 4.2.14.5  1997/12/12  15:10:43  Andrew_Bragg
 * 	removed references of btStruct_64
 * 	[1997/12/05  18:49:28  Andrew_Bragg]
 *
 * Revision 4.2.14.4  1997/07/25  17:59:39  Peter_Thompson
 * 	Added ST_USEEXTSRC to help select the use of extended source info
 * 	in st_readst and st_freadst.
 * 	[1997/07/24  21:57:39  Peter_Thompson]
 * 
 * Revision 4.2.14.3  1997/07/08  17:42:58  Randy_Lowell
 * 	Added btProc
 * 	[1997/07/02  21:06:39  Randy_Lowell]
 * 
 * Revision 4.2.14.2  1997/04/08  19:08:55  Peter_Thompson
 * 	Add support for TqArray_64, btRange_64 and btStruct_64
 * 	[1997/04/04  21:12:50  Peter_Thompson]
 * 
 * Revision 4.2.12.2  1994/11/16  21:10:25  Lee_Miller
 * 	add ST_PNOSMALL for as -x functionality
 * 	[1994/11/15  18:39:50  Lee_Miller]
 * 
 * Revision 4.2.10.2  1994/05/12  18:03:46  Thomas_Peterson
 * 	Added __cplusplus ifdefs to __LANGUAGE_C__ ifdefs for C++.
 * 	Commented out unused _auxtemp variable & macro leftover from Mips.
 * 	[1994/03/15  19:41:06  Thomas_Peterson]
 * 
 * Revision 4.2.5.5  1993/01/12  22:50:08  Mark_Himelstein
 * 	C++ demangler name support
 * 	[93/01/04  20:21:22  Mark_Himelstein]
 * 
 * Revision 4.2.5.4  92/07/30  09:22:10  Jin_Chen
 * 	Deleted duplicate HISTORY log at end of the file
 * 	[92/07/30  09:21:12  Jin_Chen]
 * 
 * Revision 4.2.5.3  92/04/30  15:59:42  Ken_Lesniak
 * 	initial 3.10 compiler version
 * 	[92/04/30  14:19:06  Ken_Lesniak]
 * 
 * Revision 4.2.5.2  92/03/19  17:39:45  Al_Delorey
 * 	From Silver: AG_BL5
 * 	[92/03/19  17:39:12  Al_Delorey]
 * 
 * Revision 4.2.3.2  92/03/17  18:41:26  devbld_gsf
 * 	First AG_BL5 version.  Moved from Ag baselevel delivery tree.
 * 
 * Revision 4.2.2.3  92/02/27  18:11:24  Mark_Himelstein
 * 	check for extr.ifd being nil
 * 	[92/02/18  22:16:33  Mark_Himelstein]
 * 
 * Revision 4.2.2.2  91/12/05  14:13:23  Jim_McHale
 * 	"Integrate with AG pool"
 * 
 * Revision 4.2.1.2  91/11/22  20:22:44  Jim_McHale
 * 	Merge with mips 3.0
 * 
 * Revision 4.2  91/09/20  05:13:17  devbld
 * 	Adding ODE Headers
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
/* $Header: /share/buffer/build/rcs.dsk1/os/src/usr/include/cmplrs/stsupport.h,v 4.2.20.1 2002/12/18 21:17:48 Randy_Lowell Exp $ */
/*
 * Author	Mark I. Himelstein
 * Date Started	5/15/85
 * Purpose	provide support to uc to produce mips symbol tables.
 */
#ifndef __CMPLRS_STSUPPORT_H
#define __CMPLRS_STSUPPORT_H


#if defined(__LANGUAGE_C__) || defined(__cplusplus)
#include <sym.h>
/* C++ demangler demangle_string routine flag options */
#include <cmplrs/demangle_string.h>
#endif /* LANGUAGE_C */

#if defined(__LANGUAGE_C__) || defined(__cplusplus)
/*
AUXU _auxtemp;
#define AUXINT(c) ((_auxtemp.isym = c), _auxtemp)
*/

/* the following struct frames the FDR structure and is used at runtime
 *	to access the objects in the FDR with pointers (since the FDR
 *	only has indeces.
 */
typedef struct {
	pFDR	pfd;		/* file descriptor for this file */
	pSYMR	psym;		/* symbols for this file */
	int	csymMax;	/* max allocated */
	pAUXU	paux;		/* auxiliaries for this file */
	int	cauxMax;	/* max allocated */
	char	*pss;		/* strings space for this file */
	long	cbssMax;	/* max bytes allowed in ss */
	pOPTR	popt;		/* optimization table for this file */
	int	coptMax;	/* max allocated */
	pLINER	pline;		/* lines for this file */
        int     *plinefd;	/* ifd for lines inc'd from header file */
	int	clineMax;	/* max allocated */
	pRFDT	prfd;		/* file indirect for this file */
	int	crfdMax;	/* max allocated */
	pPDR	ppd;		/* procedure descriptor tables */
	int	cpdMax;		/* max allocated */
	int	freadin;	/* set if read in */
	} CFDR, *pCFDR;
#define cbCFDR sizeof (CFDR)
#define cfdNil ((pCFDR) 0)
#define icfdNil -1


/* the following struct embodies the HDRR dtructure and is used at runtime
 *	to access the objects in the HDRR with pointers (since the HDRR
 *	only has indeces.
 */
typedef struct {
	int	fappend;	/* are we appending to this beast ? */
	pCFDR	pcfd;		/* the compile time file descriptors */
	pFDR	pfd;		/* all of the file descriptors in this cu */
	int	cfd;		/* count of file descriptors */
	int	cfdMax;		/* max file descriptors */
	pSYMR	psym;		/* the symbols for this cu */
	pEXTR	pext;		/* externals for this cu */
	int	cext;		/* number of externals */
	int	cextMax;	/* max currently allowed */
	char	*pssext;	/* string space for externals */
	long	cbssext;	/* # of bytes in ss */
	long	cbssextMax;	/* # of bytes allowed in ss */
	pAUXU	paux;		/* auxiliaries for this cu */
	char	*pss;		/* string space for this cu */
	pDNR	pdn;		/* dense number table for this cu */
	int	cdn;		/* number of dn's */
	int	cdnMax;		/* max currently allowed */
	pOPTR	popt;		/* optimization table for this cu */
	pLINER	pline;		/* lines for this cu */
        int     *plinefd;	/* ifd for lines inc'd from header file */
	pRFDT	prfd;		/* file indirect for this cu */
	pPDR	ppd;		/* procedure descriptor tables */
	int	flags;		/* which has been read in already */
	int	fswap;		/* do dubtables need to be swapped */
	HDRR	hdr;		/* header from disk */
	} CHDRR, *pCHDRR;
#define cbCHDRR sizeof (CHDRR)
#define chdrNil ((pCHDRR) 0)
#define ichdrNil -1
#endif /* __LANGUAGE_C__ */

/* constants and macros */

#define ST_FILESINIT	25 	/* initial number of files */
#define ST_STRTABINIT	512 	/* initial number of bytes in strring space */
#define ST_EXTINIT	32	/* initial number of symbols/file */
#define ST_SYMINIT	64	/* initial number of symbols/file */
#define ST_AUXINIT	64	/* initial number of auxiliaries/file */
#define ST_LINEINIT	512	/* initial number of auxiliaries/file */
#define ST_PDINIT	32	/* initial number of procedures in one file */
#define ST_DNINIT	128	/* initial # of dense numbers */
#define ST_FDISS	1	/* we expect a fd's iss to be this */
#define ST_IDNINIT	2	/* start the dense num tab with this entry */
#define ST_PROCTIROFFSET 1	/* offset from aux of proc's tir */
#define ST_RELOC	1	/* this sym has been reloced already */

#ifdef __LANGUAGE_FORTRAN__
#define ST_EXTIFD	0x7fffffff	/* ifd for externals */
#define ST_RFDESCAPE	0xfff	/* rndx.rfd escape says next aux is rfd */
#define ST_ANONINDEX	0xfffff /* rndx.index for anonymous names */
#endif

#if defined(__LANGUAGE_C__) || defined(__cplusplus)
#define ST_EXTIFD	0x7fffffff	/* ifd for externals */
#define ST_RFDESCAPE	0xfff	/* rndx.rfd escape says next aux is rfd */
#define ST_ANONINDEX	0xfffff /* rndx.index for anonymous names */
#define ST_PEXTS	0x01	/* mask, if set externals */
#define ST_PSYMS	0x02	/* mask, if set symbols */
#define ST_PLINES	0x04	/* mask, if set lines */
#define ST_PHEADER	0x08	/* mask, if set headers */
#define ST_PDNS		0x10	/* mask, if set dense numbers */
#define ST_POPTS	0x20	/* mask, if set optimization entries */
#define ST_PRFDS	0x40	/* mask, if set file indirect entries */
#define ST_PSSS		0x80	/* mask, if set string space */
#define ST_PPDS		0x100	/* mask, if set proc descriptors */
#define ST_PFDS		0x200	/* mask, if set file descriptors */
#define ST_PAUXS	0x400	/* mask, if set auxiliaries */
#define ST_PSSEXTS	0x800	/* mask, if set external string space */
#define ST_PNOSMALL   0x1000  /* mask, if not set minimalize file descriptors */
#define ST_USEEXTSRC    0x2000  /* mask, if set use extended src, if there */
#endif /* __LANGUAGE_C__ */

#ifdef __LANGUAGE_PASCAL__
#define ST_EXTIFD	16#7fffffff	/* ifd for externals */
#define ST_RFDESCAPE	16#fff	/* rndx.rfd escape says next aux is rfd */
#define ST_ANONINDEX	16#fffff /* rndx.index for anonymous names */
#define ST_PEXTS	16#01	/* mask, if set externals */
#define ST_PSYMS	16#02	/* mask, if set symbols */
#define ST_PLINES	16#04	/* mask, if set lines */
#define ST_HEADER	16#08	/* mask, if set header */
#define ST_PDNS		16#10	/* mask, if set dense numbers */
#define ST_POPTS	16#20	/* mask, if set optimization entries */
#define ST_PRFDS	16#40	/* mask, if set file indirect entries */
#define ST_PSSS		16#80	/* mask, if set string space */
#define ST_PPDS		16#100	/* mask, if set proc descriptors */
#define ST_PFDS		16#200	/* mask, if set file descriptors */
#define ST_PAUXS	16#400	/* mask, if set auxiliaries */
#define ST_PSSEXTS	16#800	/* mask, if set external string space */
#define ST_PNOSMALL   16#1000 /* mask, if not set minimalize file descriptors */
#define ST_USEEXTSRC    16#2000 /* mask, if set use extended src, if there */
#endif /* __LANGUAGE_PASCAL__ */

#define ST_FCOMPLEXBT(bt) ((bt == btStruct) || (bt == btUnion) || (bt == btTypedef) || (bt == btEnum) || (bt == btClass) || (bt == btProc))
#define valueNil	0
#define export

/*
 * Constants to describe aux types used in swap_aux( , ,type);
 */
#define ST_AUX_TIR	0
#define ST_AUX_RNDXR	1
#define ST_AUX_DNLOW	2
#define ST_AUX_DNMAC	3
#define ST_AUX_ISYM	4
#define ST_AUX_ISS	5
#define ST_AUX_WIDTH	6
#endif
