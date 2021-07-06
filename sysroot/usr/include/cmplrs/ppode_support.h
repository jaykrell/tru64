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
 * @(#)$RCSfile: ppode_support.h,v $ $Revision: 1.1.2.3 $ (DEC) $Date: 1999/02/09 19:04:02 $
 */

#ifndef _CMPLRS_PPODE_SUPPORT_H
#define _CMPLRS_PPODE_SUPPORT_H
/* ppode_support.h */

struct bb_add {
    int		ipd;	/* Index to modified PDR */
    char	*bb;    /* Raw basic block data */
    int		sz;	/* Size of basic block data */
};

struct st_handle {
    char		*in;	  /* Input symbol table */
    long		fileoff;  /* File offset of input symbol table */
    long		size;     /* Symbol table size */
    int			nadd;     /* Number of add entries */
    struct bb_add	*add;	  /* Add or replace bb's for these PDR's */
    int			ndel;	  /* Number of delete entries */
    int			*del;	  /* Delete bb's for these PDR's */
};

#if defined (__cplusplus) || defined (__DECCXX)
extern "C" {
#endif

/* Add or replace a basic block database entry for a PDR
 *
 * Inputs:
 *      sth         handle returned by stbb_open
 *	ipd         PDR index
 *      newbb 	    basic block data
 *	newbb_size  size of newbb data
 *
 * Returns -1 for failed add, 0 for success.
 */
int stbb_add(struct st_handle *sth, int ipd, char *newbb, int newbb_size);

/* Delete a basic block database entry for a PDR
 *
 * (No change if PDR already has not bb entry.)
 *
 * Inputs:
 *	sth	handle returned by stbb_open
 *	ipd     PDR index to delete from
 */
int stbb_del(struct st_handle *sth, int ipd);

/* Free storage associated with symbol table layout handle */
void stbb_free(struct st_handle *sth);

/* Test a PDR to see if it already has basic block information. 
 * This may be used to test for error conditions:
 *      - Add new but PDR already has bb
 *      - Replace old but PDR has no bb
 *      - Delete but PDR has no bb
 *
 * Inputs:
 *      sth   handle returned by stbb_open
 *      ipd   PDR index
 */
int stbb_has_bb(struct st_handle *sth, int ipd);

/* Apply actions to optimization symbol section and layout a 
 * new symbol table.
 *
 * Inputs:
 * 	sth		handle returned by stbb_open
 *	new_fileoff	new symbol table file offset
 *	new_symtab	pointer to hold new symbol table buffer pointer
 *	symtab_size	pointer to hold new symbol table size
 */
int stbb_layout(struct st_handle 	*sth,
		long 			new_fileoff,
		char 			**new_symtab,
		long			*symtab_size);

struct st_handle *stbb_open(long file_offset, char *symbol_table);

struct st_handle *symtab_open(char *filename);

int symtab_write(char *filename, struct st_handle *sth);

#if defined (__cplusplus) || defined (__DECCXX)
} // extern "C"
#endif
#endif /* _CMPLRS_PPODE_SUPPORT_H */
