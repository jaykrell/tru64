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
 *	"@(#)xpr.h	9.1	(ULTRIX/OSF)	10/21/91"
 */ 
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
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/*
 *	File:	alpha/xpr.h
 *
 *	Machine dependent module for the XPR tracing facility.
 *
 * NOTE: most of the following stuff should migrate to the
 *	 machine-independent section, or disappear.
 */

#ifndef	_ALPHA_XPR_H_
#define	_ALPHA_XPR_H_
#ifdef __cplusplus
extern "C" {
#endif

#define XPR_TIMESTAMP	(0)

/*
 * Debug macros.
 */

#if defined(__LANGUAGE_C__) || defined(__cplusplus)

/*
 * bit field descriptions for printf %r and %R formats
 */

/*
 * printf("%r %R", val, reg_descp);
 * struct reg_desc *reg_descp;
 *
 * the %r and %R formats allow formatted output of bit fields.
 * reg_descp points to an array of reg_desc structures, each element of the
 * array describes a range of bits within val.  the array should have a
 * final element with all structure elements 0.
 * %r outputs a string of the format "<bit field descriptions>"
 * %R outputs a string of the format "0x%x<bit field descriptions>"
 *
 * The fields in a reg_desc are:
 *	unsigned long rd_mask;	An appropriate mask to isolate the bit field
 *				within a word, and'ed with val
 *
 *	int rd_shift;		A shift amount to be done to the isolated
 *				bit field.  done before printing the isolate
 *				bit field with rd_format and before searching
 *				for symbolic value names in rd_values
 *
 *	char *rd_name;		If non-null, a bit field name to label any
 *				out from rd_format or searching rd_values.
 *				if neither rd_format or rd_values is non-null
 *				rd_name is printed only if the isolated
 *				bit field is non-null.
 *
 *	char *rd_format;	If non-null, the shifted bit field value
 *				is printed using this format.
 *
 *	struct reg_values *rd_values;	If non-null, a pointer to a table
 *				matching numeric values with symbolic names.
 *				rd_values are searched and the symbolic
 *				value is printed if a match is found, if no
 *				match is found "???" is printed.
 *				
 */

/*
 * register values
 * map between numeric values and symbolic values
 */
struct reg_values {
	unsigned long rv_value;
	char *rv_name;
};

/*
 * register descriptors are used for formatted prints of register values
 * rd_mask and rd_shift must be defined, other entries may be null
 */
struct reg_desc {
	unsigned long rd_mask;	/* mask to extract field */
	int rd_shift;		/* shift for extracted value, - >>, + << */
	char *rd_name;		/* field name */
	char *rd_format;	/* format to print field */
	struct reg_values *rd_values;	/* symbolic names of values */
};

#endif	/* __LANGUAGE_C__ || __cplusplus */


/*
 * Architecture specific trace flags.
 * XXX: clean up the unused and unify.
 */
#define XPR_TTY		(1 << 16)	/* mux i/o */
#define XPR_BIO		(1 << 17)	/* blk i/o */
#define XPR_INTR	(1 << 18)	/* interrupt handling */
#define XPR_CACHE	(1 << 19)	/* cache handling */
#define XPR_NFS		(1 << 20)	/* nfs */
#define XPR_SIGNAL	(1 << 21)	/* signal handling */

#ifdef __cplusplus
}
#endif
#endif	/* _ALPHA_XPR_H_ */
