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
 * (c) Copyright 1990, 2002, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*	
 *	@(#)$RCSfile: mesg.h,v $ $Revision: 4.2.16.2 $ (DEC) $Date: 1999/02/02 21:27:36 $
 */ 
/*
 */
/*
 * COMPONENT_NAME: INC
 *
 * FUNCTIONS: mesg.h
 *
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1989, 1991
 * All Rights Reserved
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * (Copyright statements and/or associated legends of other
 * companies whose code appears in any part of this module must
 * be copied here.)
 */

#ifndef _MESG_H_
#define _MESG_H_

#include <stdio.h>
#include <nl_types.h>
#include <limits.h>
#include <sys/types.h>

#define CAT_MAGIC 	505
#define CATD_ERR 	((nl_catd) -1)
#define NL_MAXOPEN	10
#define	NL_CAT_MSGID	2	/* Enable error message ID support (catopen) */
#define	CAT_SEVERITY	"severity"
#define	CAT_CLASS	"class"

/*
 * Magic string for indicating symbolic set/message name support when it
 * is the prefix of the string with set = _n_sets & msg = _n_sets.
 */
#define	CAT_SYMSTR	"$@ "
#define	CAT_SYMSTRLEN	(sizeof(CAT_SYMSTR) - 1)

/*
 * Predefined value of _symstr
 */
#define	CAT_NOTINIT	NULL		/* Flag not initialized		   */
#define	CAT_NOSYM	((char *)-1)	/* Catalog has no symbolic set/msg */

/*
 * Data structures for storing additional set attribute information which
 * are put immmediately after all the set/message information on an pointer
 * boundary.
 *
 *	+-----------------------+
 *	|   Attribute header	|
 *	+-----------------------+
 *	|   Attribute record 1	|
 *	+-----------------------+
 *	|   	    :		|
 *	+-----------------------+
 *	|   Attribute record n	|
 *	+-----------------------+
 *	|			|
 *	|   Attribute buffer	|
 *	|			|
 *	+-----------------------+
 *
 * The attribute records are sorted in ascending order of set & key number.
 */
struct _attrib_hdr {
	int		_magic    ;	/* Magic number			 */
	int		_n_records;	/* Number of attribute records   */
	int		_size	  ;	/* Total size from header to end */
					/* of string buffer		 */
	int		_unused	  ;
} ;

struct _attrib_rec {
	unsigned short 	_set   ,	/* Set number		  */
			_key   ;	/* Attribute key	  */
	unsigned int	_bufoff;	/* Offset from buffer top */
} ;

/*
 * In memory data structure for set attribute record
 */
struct _attrib {
	int		    _n_records;	/* Number of attribute records	*/
	struct _attrib_rec *_attribs  ;	/* Attribute records pointer	*/
	char		   *_buftop   ;	/* String buffer top pointer	*/
} ;

/*
 * Data structures for set and message information
 */
struct _header {
	int 		_magic;
	unsigned short	_n_sets,
			_setmax;
	char		_filler[16];
	unsigned int	_offattrib;	/* Offset of attribute header */
};
struct _msgptr {
	unsigned short 	_msgno,
			_msglen;
	unsigned int	_offset;
};

struct _catset {
	unsigned short 	_setno,
			_n_msgs;
	struct _msgptr 	*_mp;
	int		_msgs_expanded;
};


struct __catalog_descriptor {
	char		*_mem;
	char		*_name;
	char		*_lc_message;
	char		*_nlspath;
	struct _header 	*_hd;
	struct _catset 	*_set;
	struct _attrib	*_setattrib;	/* Ptr to set attribute records */
	void		*_iconv;	/* Ptr to iconv data */
	char		*_symstr;	/* Symbolic set conversion string */
	char		*_midfmt;	/* Message ID format string */
	int 		_fd;		/* i/o descriptor */
	int		_catlen;	/* Size of mapped object */
	int		_setmax;	/* # message sets in file */
	int		_count;
	int		_magic;		/* Also holds copy of CAT_MAGIC */
	int		_n_sets;	/* max index in _set array */
	int		_sets_expanded;
	int		_midflag;	/* Enable message ID if set */
};


_BEGIN_CPLUSPLUS
#ifdef _XOPEN_SOURCE
extern struct _catset *__cat_get_catset(nl_catd, int);
#endif /* _XOPEN_SOURCE */
extern struct _msgptr *__cat_get_msgptr(struct _catset *, int);
extern char	      *catgets_sym(nl_catd, const char *, const char *, const char *);
extern int	       catgetm(nl_catd, const char *, const char *, const char *, const char **, char *);
extern int	       catgetmh(nl_catd, const char *, const char *, const char **, char *);
extern int	       __catgetm_num(nl_catd, int, int, const char *, const char **, char *);
extern int             __catgetmh_num(nl_catd, int, int, const char **, char *);

_END_CPLUSPLUS

#endif  /* _MESG_H_ */
