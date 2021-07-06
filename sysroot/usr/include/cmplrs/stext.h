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
 * |
 * | 13-Dec-1991 ccg:  Added ANSI prototypes 
 */
#ifndef _CMPLRS_STEXT_H
#define _CMPLRS_STEXT_H

#ifdef __cplusplus
extern "C" {
#endif
#include <ldfcn.h>
extern int st_readbinary( char *, int  );
extern int st_readst( int, int, int, pCHDRR, int );
extern void st_writebinary( char *, int );
extern void st_writest( int, int );
extern void st_shifttq( int, int );
extern int st_iaux_copyty( int, pSYMR );
extern void st_changeaux( int, AUXU );
extern void st_addtq( int, int );
extern void st_changeauxrndx( int, int, int );
extern int st_auxbtadd( int );
extern int st_auxisymadd( int );
extern int st_auxrndxadd( int, int );
extern int st_auxbtsize( int, int );
extern int st_auxrndxadd_idn( int );
extern void st_addcontinued( int );
extern char *st_mlang_ascii [];
extern char *st_mst_ascii [];
extern char *st_msc_ascii [];
extern char *st_mbt_ascii [];
extern char *st_mtq_ascii [];
extern void st_dump( FILE *, int );
extern void st_printfd( FILE *, int, int );
extern int st_currentifd( void );
extern int st_ifdmax( void );
extern void st_setfd( int );
extern void st_fdadd( char *, int, int, int );
extern int st_symadd( int, long, int, int, int );
extern int st_auxadd( AUXU );
extern int st_pdadd( int );
extern int st_lineadd( int );
extern int st_stradd( char * );   
extern pSYMR st_psym_ifd_isym( int, int );
extern pAUXU st_paux_ifd_iaux( int, int );
extern pLINER st_pline_ifd_iline( int, int );
extern pAUXU st_paux_iaux( int );
extern pPDR st_ppd_ifd_isym( int, int );
extern int st_ifd_pcfd( pCFDR );
extern pCFDR st_pcfd_ifd( int );
extern char *st_str_iss( int );
extern char *st_str_ifd_iss( int, int );
extern void * st_malloc( void *, int *, int, int );
extern pCHDRR st_cuinit( void );
extern void st_setchdr( pCHDRR );
extern pCHDRR st_currentpchdr( void );
extern void st_free( void );
extern int st_extadd( int, long, int, int, int );
extern int st_extadd_align (int, long, int, int, int, int);
extern int st_extstradd( char * );
extern char *st_str_extiss( int );
extern int st_idn_index_fext( int, int );
extern int st_idn_dn ( DNR );
extern int st_idn_rndx( RNDXR );
extern RNDXR st_rndx_idn( int );
extern pDNR st_pdn_idn( int );
extern void st_setidn( int, int );
extern pEXTR st_pext_dn( DNR );
extern pEXTR st_pext_iext( int );
extern pPDR st_ppd_ipd( int );
extern int st_iextmax ( void );
extern int st_freadbinary (char	*, char, unsigned int);
export int st_freadst (int, char, int, pCHDRR, unsigned int, unsigned int);
extern char *st_extended_src (pCFDR, pPDR, long *);
export int st_interpret_cmd_mode(pCFDR, char *, unsigned long *, long *, 
				 unsigned long *, int *);
extern char *_mld_raw_st_str_iss ( int );
extern char *_mld_raw_st_str_ifd_iss ( int, int );
#ifdef __cplusplus
}
#endif
#endif
