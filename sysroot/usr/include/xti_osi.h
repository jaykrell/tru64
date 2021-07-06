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
 * @(#)$RCSfile: xti_osi.h,v $ $Revision: 1.1.4.3 $ (DEC) $Date: 1997/11/25 21:12:18 $
 */

#ifndef _XTI_OSI_H
#define _XTI_OSI_H

	/* SPECIFIC ISO OPTIONS AND MANAGEMENT PARAMETERS */

/* Definition of the ISO transport classes */

#define	T_CLASS0	0
#define	T_CLASS1	1
#define	T_CLASS2	2
#define	T_CLASS3	3
#define	T_CLASS4	4

/* Definition of the priorities */

#define	T_PRITOP	0
#define	T_PRIHIGH	1
#define	T_PRIMID	2
#define	T_PRILOW	3
#define	T_PRIDFLT	4

/* Definition of the protection levels */

#define	T_NOPROTECT		1
#define	T_PASSIVEPROTECT	2
#define	T_ACTIVEPROTECT		4

/* Default value for the length of TPDU's */

#define	T_LTPDUDFLT	128	/* define obsolete in XPG4 */

/* 
 * rate structure
 */

struct rate {
#if defined( _XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)
	t_scalar_t	targetvalue;	/* target value			*/
	t_scalar_t	minacceptvalue;	/* value of minimum acceptable quality*/
#else
	long		targetvalue;	/* target value			*/
	long		minacceptvalue;	/* value of minimum acceptable quality*/
#endif
};

/*
 * reqvalue structure
 */

struct reqvalue {
	struct rate	called;		/* called rate			*/
	struct rate	calling;	/* calling rate			*/
};

/*
 * thrpt structure
 */

struct thrpt {
	struct reqvalue	maxthrpt;	/* maximum throughput		*/
	struct reqvalue	avgthrpt;	/* average throughput		*/
};

#if defined(_XOPEN_SOURCE) && !defined(XTI_XPG3)
/*
 * transdel structure
 */

struct transdel {
	struct reqvalue	maxdel;		/* maximum transist delay	*/
	struct reqvalue	avgdel;		/* average transist delay	*/
};

/*
 * Protocol Levels
 */

#define	T_ISO_TP	0x0100
#define ISO_TP		0x0100	/* LEGACY */

/*
 * Options for Quality of Service and Expedited Data (ISO 8072:1986)
 */

#define T_TCO_THROUGHPUT	0x0001
#define TCO_THROUGHPUT		0x0001			/* LEGACY */
#define T_TCO_TRANSDEL		0x0002
#define TCO_TRANSDEL		0x0002			/* LEGACY */
#define T_TCO_RESERRORRATE	0x0003
#define TCO_RESERRORRATE	0x0003			/* LEGACY */
#define T_TCO_TRANSFFAILPROB	0x0004
#define TCO_TRANSFFAILPROB	0x0004			/* LEGACY */
#define T_TCO_ESTFAILPROB	0x0005
#define TCO_ESTFAILPROB		0x0005			/* LEGACY */
#define T_TCO_RELFAILPROB	0x0006
#define TCO_RELFAILPROB		0x0006			/* LEGACY */
#define T_TCO_ESTDELAY		0x0007
#define TCO_ESTDELAY		0x0007			/* LEGACY */
#define T_TCO_RELDELAY		0x0008
#define TCO_RELDELAY		0x0008			/* LEGACY */
#define T_TCO_CONNRESIL		0x0009
#define TCO_CONNRESIL		0x0009			/* LEGACY */
#define T_TCO_PROTECTION	0x000a
#define TCO_PROTECTION		0x000a			/* LEGACY */
#define T_TCO_PRIORITY		0x000b
#define TCO_PRIORITY		0x000b			/* LEGACY */
#define T_TCO_EXPD		0x000c
#define TCO_EXPD		0x000c			/* LEGACY */

#define T_TCL_TRANSDEL		0x000d
#define TCL_TRANSDEL		0x000d			/* LEGACY */
#define T_TCL_RESERRORRATE	T_TCO_RESERRORRATE
#define TCL_RESERRORRATE	T_TCO_RESERRORRATE	/* LEGACY */
#define T_TCL_PROTECTION	T_TCO_PROTECTION
#define TCL_PROTECTION		T_TCO_PROTECTION	/* LEGACY */
#define T_TCL_PRIORITY		T_TCO_PRIORITY
#define TCL_PRIORITY		T_TCO_PRIORITY		/* LEGACY */

/*
 * Management Options
 */

#define T_TCO_LTPDU		0x0100
#define TCO_LTPDU		0x0100
#define T_TCO_ACKTIME		0x0200
#define TCO_ACKTIME		0x0200
#define T_TCO_REASTIME		0x0300
#define TCO_REASTIME		0x0300
#define T_TCO_EXTFORM		0x0400
#define TCO_EXTFORM		0x0400
#define T_TCO_FLOWCTRL		0x0500
#define TCO_FLOWCTRL		0x0500
#define T_TCO_CHECKSUM		0x0600
#define TCO_CHECKSUM		0x0600
#define T_TCO_NETEXP		0x0700
#define TCO_NETEXP		0x0700
#define T_TCO_NETRECPTCF	0x0800
#define TCO_NETRECPTCF		0x0800
#define T_TCO_PREFCLASS		0x0900
#define TCO_PREFCLASS		0x0900
#define T_TCO_ALTCLASS1		0x0a00
#define TCO_ALTCLASS1		0x0a00
#define T_TCO_ALTCLASS2		0x0b00
#define TCO_ALTCLASS2		0x0b00
#define T_TCO_ALTCLASS3		0x0c00
#define TCO_ALTCLASS3		0x0c00
#define T_TCO_ALTCLASS4		0x0d00
#define TCO_ALTCLASS4		0x0d00

#define T_TCL_CHECKSUM		T_TCO_CHECKSUM
#define TCL_CHECKSUM		T_TCO_CHECKSUM

#else	/* defined(_XOPEN_SOURCE) && !defined(XTI_XPG3) */

/*
 * management structure
 */

struct management {
	short	dflt;		/* T_YES: the following parameters	*/
				/* are ignored, default vales are used;	*/
				/* T_NO: the following parameters	*/
				/* are used				*/
	int	ltpdu;		/* maximum length of TPDU (in octets)	*/
	short	reastime;	/* reassignment time (in seconds)	*/
#ifndef __cplusplus
	char	class;		/* preferred class;			*/
				/* value: T_CLASS - TCLASS4		*/
#else
	char	tclass;		/* "class" is reserved word in C++	*/
#endif
	char	altclass;	/* alternative class			*/
	char	extform;	/* extended format: T_YES or T_NO	*/
	char	flowctrl;	/* flow control: T_YES or T_NO		*/
	char	checksum;	/* checksum (cl. 4): T_YES or T_NO	*/
	char	netexp;		/* network expedited data: T_YES or T_NO*/
	char	netrecptcf;	/* receipt confirmation: T_YES or T_NO	*/ 
};

/*
 * ISO connection-oriented options
 */

struct isoco_options {
	struct thrpt	throughput;	/* throughput			*/
	struct reqvalue	transdel;	/* transit delay		*/
	struct rate	reserrorrate;	/* residual error rate		*/
	struct rate	transffailprob;	/* transfer failure problem	*/
	struct rate	estfailprob;	/* connection establishment failure */
	struct rate	relfailprob;	/* connection release failure	*/
	struct rate	estdelay;	/* connection establishment delay */
	struct rate	reldelay;	/* connection release delay	*/
	struct netbuf	connresil;	/* connection resilience	*/
	unsigned short	protection;	/* protection			*/
	short		priority;	/* priority			*/
	struct management mngmt;	/* management parameters	*/
	char		expd;		/* expedited data: T_YES or T_NO*/
};

/*
 * ISO connectionless options
 */

struct isocl_options {
	struct rate	transdel;	/* transit delay		*/
	struct rate	reserrorrate;	/* residual error rate		*/
	unsigned short	protection;	/* protection			*/
	short		priority;	/* priority			*/
};

#endif	/* defined(_XOPEN_SOURCE) && !defined(XTI_XPG3) */

#endif /* _XTI_OSI_H */
