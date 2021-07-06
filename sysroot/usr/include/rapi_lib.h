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
 * @(#)$RCSfile: rapi_lib.h,v $ $Revision: 1.1.9.1 $ (DEC) $Date: 2001/12/10 16:37:33 $
 */
/**************************************************************************
 *	 rapi_lib.h -- include file for RSVP API (RAPI)
 *
 *	Definitions of RSVP API (RAPI) library calls.
 *             Matches RAPI approved specification
 *
 *	Also includes rsvp_intserv.h, which contains formats of integrated
 *	services data structures across application program interface.
 *
 **************************************************************************/
/****************************************************************************

            RSVPD -- ReSerVation Protocol Daemon

                USC Information Sciences Institute
                Marina del Rey, California

		Current version by: Bob Braden, August 1996

  Copyright (c) 1996 by the University of Southern California
  All rights reserved.

  Permission to use, copy, modify, and distribute this software and its
  documentation in source and binary forms for any purpose and without
  fee is hereby granted, provided that both the above copyright notice
  and this permission notice appear in all copies, and that any
  documentation, advertising materials, and other materials related to
  such distribution and use acknowledge that the software was developed
  in part by the University of Southern California, Information
  Sciences Institute.  The name of the University may not be used to
  endorse or promote products derived from this software without
  specific prior written permission.

  THE UNIVERSITY OF SOUTHERN CALIFORNIA makes no representations about
  the suitability of this software for any purpose.  THIS SOFTWARE IS
  PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES,
  INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

  Other copyrights might apply to parts of this software and are so
  noted when applicable.

********************************************************************/

#ifndef _RAPILIB_H_
#define _RAPILIB_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <netinet/rsvp_intserv.h>
#include <netinet/in.h>

/**************************************************************************
 **************************************************************************
 **
 **      RAPI (RSVP API) defns for flowspec, Tspec, Adspec begin here...
 **
 **
 **************************************************************************
 **************************************************************************/

/*
 *      Flowspec/Tspec Service types
 */
typedef enum {
        RAPI_QOS_TSPEC = 1,             /* Generic Tspec */
        RAPI_QOS_CNTR_LOAD = 2,         /* Controlled-load service */
        RAPI_QOS_GUARANTEED = 3         /* Guaranteed service */
} rapi_qos_service_t;

/* Backwards compatibility */
#define QOS_TSPECX	QOS_TSPEC
#define QOS_GUARANTEEDX	QOS_GUARANTEED

typedef  struct {
	float32_t       spec_Tspec_b;	/* Token bucket depth (B) */
	float32_t       spec_Tspec_r;	/* Token bucket avg rate (Bps)*/
	float32_t	spec_Tspec_p;	/* Peak data rate (Bps)	*/
	uint32_t	spec_Tspec_m;	/* Min policed unit (B)	*/
	uint32_t	spec_Tspec_M;	/* Max pkt size (B)	*/
}    rapi_qos_Tspec_body;
            
/*
 *      Simplified-format Flowspec
 *
 *	This structure contains the union of the parameters for
 *	Controlled-Load and Guaranteed service models.
 */
typedef struct {
        rapi_qos_service_t   spec_type;		/* qos_service_type */
        rapi_qos_Tspec_body  xspec_Tspec;	/* Tspec		*/
        float32_t       xspec_R;                /* Rate (Bps)		*/
        uint32_t       xspec_S;                /* Slack term (microsecs)*/
}   rapi_qos_flowspecx_t;

#define xspec_r  xspec_Tspec.spec_Tspec_r
#define xspec_b  xspec_Tspec.spec_Tspec_b
#define xspec_p  xspec_Tspec.spec_Tspec_p
#define xspec_m  xspec_Tspec.spec_Tspec_m
#define xspec_M  xspec_Tspec.spec_Tspec_M
        
/*
 *      Simplified-format Tspec.
 *
 *	This structure contains the generic Tspec parameters.
 */
typedef struct {
        rapi_qos_service_t      spec_type;	/* qos_service_type */
        rapi_qos_Tspec_body	xtspec_Tspec;	/* Tspec	*/
} rapi_qos_tspecx_t;

#define xtspec_r  xtspec_Tspec.spec_Tspec_r
#define xtspec_b  xtspec_Tspec.spec_Tspec_b
#define xtspec_p  xtspec_Tspec.spec_Tspec_p
#define xtspec_m  xtspec_Tspec.spec_Tspec_m
#define xtspec_M  xtspec_Tspec.spec_Tspec_M
        
/*
 *	Simplified-format Adspec.
 *
 *	This structure is the union of all adspec parameters for
 *	Controlled-Load and Guaranteed service models.
 */
#define RAPI_XASPEC_FLG_BRK 0x01 /* Break bit: serv. unsupported in some node */
#define RAPI_XASPEC_FLG_IGN 0x02 /* Ignore flag: Do not include this service */
#define RAPI_XASPEC_FLG_PARM 0x04 /* Parms-present flag: Include service parms */
				/* (IGN and PARM flags both on is an error) */

typedef struct {
	/*
	 *	General path characterization parameters
	 */
	uint8_t		xaspec_flags;	/* See flags above (FLG_IGN not	*/
					/*  allowed, FLG_PARM assumed)	*/
	uint16_t	xaspec_hopcnt;
	float32_t	xaspec_path_bw;
	uint32_t	xaspec_min_latency;
	uint32_t	xaspec_composed_MTU;

	/*      Controlled-Load service Adspec parameters
	 */
	uint8_t	  	xClaspec_flags;		/* See flags above	 */
	uint8_t	 	xClaspec_override;	/* 1 => override all gen */
						/*    parameters	 */
	uint16_t       xClaspec_hopcnt;
	float32_t       xClaspec_path_bw;
	uint32_t       xClaspec_min_latency;
	uint32_t       xClaspec_composed_MTU;

	/*	Guaranteed service Adspec parameters
	 */
	uint8_t		xGaspec_flags;		/* See flags above */
	uint32_t	xGaspec_Ctot;
	uint32_t	xGaspec_Dtot;
	uint32_t	xGaspec_Csum;
	uint32_t	xGaspec_Dsum;
	uint8_t	  	xGaspec_override;       /* 1 => override all gen */
						/*     parameters	 */
	uint16_t       xGaspec_hopcnt;
	float32_t       xGaspec_path_bw;
	uint32_t       xGaspec_min_latency;
	uint32_t       xGaspec_composed_MTU;
}  qos_adspecx_t;


/**************************************************************************
 *
 *	RAPI call formats and definitions
 *
 **************************************************************************/

#define RAPI_VERSION	502	/* RAPI Version 5.02 */
#define MAX_RAPI_SESS	100	/* max #flows the daemon api can handle */

/*	Define RAPI flowspec/Tspec formats
 */
typedef enum {
	RAPI_EMPTY_OTYPE =	0,	/* Format = 0 => empty object */

	RAPI_FLOWSTYPE_Intserv = 2,	/* Int-Serv format flowspec	*/
	RAPI_FLOWSTYPE_Simplified = 3,	/* Simplified format flowspec	*/

	RAPI_TSPECTYPE_Intserv = 17,	/* Int-Serv format (sndr)Tspec	*/
	RAPI_TSPECTYPE_Simplified = 18,	/* Simplified format (sndr)Tspec*/

	RAPI_ADSTYPE_Intserv = 33,	/* Int-Serv format Adspec	*/
	RAPI_ADSTYPE_Simplified =34,	/* SImplified format Adspec	*/

	RAPI_FILTERFORM_RSVD1 = 257,	/* (obsolete format: reserved)	*/
	RAPI_FILTERFORM_BASE = 258,	/* Simple V4: Only sockaddr	*/
	RAPI_FILTERFORM_GPI = 259,	/* V4 GPI filter format 	*/
	RAPI_FILTERFORM_BASE6 = 260,	/* Simple V6: Only sockaddr 	*/
	RAPI_FILTERFORM_GPI6 = 261	/* V6 GPI filter format 	*/
} rapi_format_t;

/*
 * Protocol address
 */
typedef struct sockaddr rapi_addr_t;

/*
 *	Generic RAPI object header
 */
typedef struct {
	unsigned int		len;	/* Actual length in bytes */
	rapi_format_t		form;	/* Format (see rapi_format_t) */

	/* Followed by type-specific contents */
}  rapi_hdr_t;

#define RAPIObj_Size(p) (((rapi_hdr_t *)(p))->len)
#define RAPIObj_data(p) ((rapi_hdr_t *)(p)+1)
#define After_RAPIObj(p) ((char *)(p) + RAPIObj_Size(p))
#define NTOH_RAPIhdr(p) {NTOH32(((rapi_hdr_t *)p)->len); \
			 NTOH32(((rapi_hdr_t *)p)->form);}
#define HTON_RAPIhdr(p) {HTON32(((rapi_hdr_t *)p)->len); \
			 HTON32(((rapi_hdr_t *)p)->form);}


/*
 *	RAPI Flowspec descriptor
 */
typedef struct {
	unsigned int	len;	/* actual length in bytes */
	rapi_format_t   form;	/* flowspec format (see enum above) */
	union {
		rapi_qos_flowspecx_t	qosx;	/* Simplified format flowspec */
		IS_specbody_t   IS;	/* Int-serv format flowspec */
	}		specbody_u;
}   rapi_flowspec_t;

#define specbody_qosx   specbody_u.qosx
#define specbody_IS	specbody_u.IS

/*
 *	RAPI Tspec descriptor
 */
typedef struct {
	unsigned int   	len;	/* actual length in bytes */
	rapi_format_t	form;	/* flowspec format (see enum above) */
	union {
		rapi_qos_tspecx_t qosxt; /* Simplified format Tspec */
		IS_tspbody_t	ISt;	/* Int-serv format Tspec */
	}		tspecbody_u;
}   rapi_tspec_t;
#define tspecbody_qosx	tspecbody_u.qosxt
#define tspecbody_IS	tspecbody_u.ISt
	
/*
 *	RAPI Adspec descriptor
 */
typedef struct {
	unsigned int	len;		/* actual length in bytes */
	rapi_format_t	form;		/* adspec format(see rapi_format)*/
	union {
		qos_adspecx_t	adsx;	/* Simplified format adspec */
		IS_adsbody_t	ISa;	/* Int-serv format adspec */
	}		adsbody_u;
}   rapi_adspec_t;

#define adspecbody_qosx adsbody_u.adsx
#define adspecbody_IS	adsbody_u.ISa


/**************************************************************************
 *
 *	Filter Spec formats
 *
 **************************************************************************/

/*	RAPI filter spec/sender template formats
 */
typedef struct {
	struct sockaddr_in sender;
} rapi_filter_base_t;

typedef struct {
	struct in_addr	sender;
	uint32_t	gpi;
} rapi_filter_gpi_t;

typedef struct {
	struct sockaddr_in6 sender;
} rapi_filter_base6_t;

typedef struct {
	struct in6_addr sender;
	uint32_t	gpi;
} rapi_filter_gpi6_t;


/*
 *	Filter Spec descriptor
 */
typedef struct {
	unsigned int   		len;	/* length of filter, in bytes */
	rapi_format_t 	form;	/* format (rapi_filterform_t) */
	union {
	    rapi_filter_base_t	base;
	    rapi_filter_gpi_t	gpi;
	    rapi_filter_base6_t	base6;
	    rapi_filter_gpi6_t	gpi6;
	}	   filt_u;		/* variable length */
} rapi_filter_t;

#define rapi_filt4		filt_u.base.sender
#define rapi_filtbase4_addr	rapi_filt4.sin_addr
#define rapi_filtbase4_port	rapi_filt4.sin_port
#define rapi_filtgpi4		filt_u.gpi
#define rapi_filtgpi4_addr	rapi_filtgpi4.sender
#define rapi_filtgpi4_gpi	rapi_filtgpi4.gpi
#define rapi_filt6		filt_u.base6.sender
#define rapi_filtbase6_addr	rapi_filt6.sin6_addr
#define rapi_filtbase6_port	rapi_filt6.sin6_port
#define rapi_filtgpi6		filt_u.gpi6
#define rapi_filtgpi6_addr	rapi_filtgpi6.sender
#define rapi_filtgpi6_gpi	rapi_filtgpi6.gpi


/**************************************************************************
 *
 *      Policy Data formats
 *
 **************************************************************************/

typedef struct {
	char    name[1];
}   rapi_policy_name_string_t;

typedef struct {
	unsigned int		len;	   /* actual length in bytes */
	rapi_format_t      form;	   /* policy data format */
	union {
	    rapi_policy_name_string_t   name_string;
	} pol_u;
} rapi_policy_t;

/******************************************************************/
/******************************************************************/

/*
 *	Reservation style ids
 */
typedef enum {
	RAPI_RSTYLE_WILDCARD = 1,	/* STYLE_ID_WF */
	RAPI_RSTYLE_FIXED = 2, 		/* STYLE_ID_FF */
	RAPI_RSTYLE_SE = 3		/* STYLE_ID_SE */
} rapi_styleid_t;
#define RAPI_RSTYLE_MAX  3

/*
 *	Reservation style extension
 */
/*	This structure is currently undefined; in the future, it will
 *	allow passing style-specific parameters for possible new styles.
 */
typedef void rapi_stylex_t;

	/* RAPI client handle */
typedef unsigned int rapi_sid_t;
#define RAPI_NULL_SID	0	/* Error return from rapi_session */

	/* RAPI User callback function */

typedef enum {
	RAPI_PATH_EVENT = 1,
	RAPI_RESV_EVENT = 2,
	RAPI_PATH_ERROR = 3,
	RAPI_RESV_ERROR = 4,
	RAPI_RESV_CONFIRM = 5,
/* Following are private to ISI implementation: */
	RAPI_PATH_STATUS = 9,
	RAPI_RESV_STATUS = 10
} rapi_eventinfo_t;

typedef void    rapi_event_rtn_t(
         rapi_sid_t        Sid,              /* Session ID            */
         rapi_eventinfo_t  EventType,        /* Event type            */
         rapi_styleid_t    Style,            /* Reservation style     */
         int               ErrorCode,        /* Error event: code     */
         int               ErrorValue,       /* Error event: value    */
         rapi_addr_t       *ErrorNode,       /* Node detecting error  */
         unsigned int      ErrorFlags,       /* Error flags           */
#define RAPI_ERRF_InPlace  0x01	 /*   Left resv in place	*/
#define RAPI_ERRF_NotGuilty 0x02 /*   This rcvr not guilty	*/
         int               FilterSpecNo,     /* number of filterSpecs */
         rapi_filter_t     *FilterSpec_list,
         int               FlowspecNo,       /* number of flowspecs   */
         rapi_flowspec_t   *Flowspec_list,
         int               AdspecNo,         /* number of adspecs     */
         rapi_adspec_t     *Adspec_list,
         void              *Event_arg        /* application argument  */
);  /* ### */

/*
 *	RAPI External Functions
 */
#ifndef _SOCKADDR_LEN
#define rapi_session rapi_session_compat43
#endif

rapi_sid_t rapi_session(
         rapi_addr_t      *Dest,       /* Session: (Dst addr, port)  */
         int               Protid,     /* Protocol Id                */
         unsigned int      Flags,      /* Flags                      */
#define RAPI_USE_INTSERV        0X10    /* Use  Int-Serv fmt in upcalls */
#define RAPI_GPI_SESSION        0x08    /* Use GPI session format */
         rapi_event_rtn_t *Event_rtn,  /* Address of upcall routine  */
         void             *Event_arg,  /* App argument to upcall     */
         int              *Errnop      /* Place to return error code */
);

int rapi_sender(
         rapi_sid_t       Sid,            /* Session ID         */
         unsigned int     Flags,          /* Flags              */
         rapi_addr_t     *LHost,          /* Local Host         */
         rapi_filter_t   *SenderTemplate, /* Sender template    */
         rapi_tspec_t    *SenderTspec,    /* Sender Tspec       */
         rapi_adspec_t   *SenderAdspec,   /* Sender Adspec      */
         rapi_policy_t   *SenderPolicy,   /* Sender policy data */
         int              TTL             /* Multicast data TTL */
);

const char *rapi_strerror(int ErrorCode, int ErrorValue);

int rapi_reserve(
         rapi_sid_t       Sid,             /* Session ID             */
         unsigned int     Flags,           /* Flags                  */
#define RAPI_REQ_CONFIRM	0x20	/* Request confirmation */
         rapi_addr_t     *RHost,           /* Receive host addr      */
         rapi_styleid_t   StyleId,         /* Style ID               */
         rapi_stylex_t   *Style_Ext,       /* Style extension        */
         rapi_policy_t   *Rcvr_Policy,     /* Receiver policy        */
         int              FilterSpecNo,    /* Number of filter specs */
         rapi_filter_t   *FilterSpec_list, /* List of filter specs   */
         int              FlowspecNo,      /* Number of flowspecs    */
         rapi_flowspec_t *Flowspec_list    /* List of flowspecs      */
);

int 	rapi_release(rapi_sid_t sid);
int 	rapi_getfd(rapi_sid_t sid);
int 	rapi_dispatch(void);
int 	rapi_dispatch_fd(int fd_val);
int	rapi_version(void);

/*	Formatting routines in rapi_fmt.c
 */
void	rapi_fmt_flowspec(rapi_flowspec_t *, char *, int);
void	rapi_fmt_tspec(rapi_tspec_t *, char *, int);
void	rapi_fmt_adspec(rapi_adspec_t *, char *, int);
void	rapi_fmt_filtspec(rapi_filter_t *, char *, int);

/*
 *	RAPI Error Codes
 */
#define RAPI_ERR_OK		0	/* No error			*/
#define RAPI_ERR_INVAL		1	/* Invalid parameter		*/
#define RAPI_ERR_MAXSESS	2	/* Too many sessions		*/
#define RAPI_ERR_BADSID		3	/* Sid out of legal range.	*/
#define RAPI_ERR_N_FFS		4	/* Wrong n_filter/n_flow for style*/
#define RAPI_ERR_BADSTYLE	5	/* Illegal reservation style	*/
#define RAPI_ERR_SYSCALL	6	/* Some sort of syscall err; see errno*/
#define RAPI_ERR_OVERFLOW	7	/* Parm list overflow		*/
#define RAPI_ERR_MEMFULL	8	/* Not enough memory		*/
#define RAPI_ERR_NORSVP		9	/* Daemon doesn't respond/exist.*/
#define RAPI_ERR_OBJTYPE	10	/* Object type error		*/
#define RAPI_ERR_OBJLEN		11	/* Object length error		*/
#define RAPI_ERR_NOTSPEC	12	/* No sender tspec in rapi_sendr*/
#define RAPI_ERR_INTSERV	13	/* Intserv format error		*/
#define RAPI_ERR_GPI_CONFLICT	14	/* IPSEC: Conflicting C-type	*/
#define RAPI_ERR_BADPROTO	15	/* IPSEC: Protocol not AH|ESP	*/
#define RAPI_ERR_BADVDPORT	16	/* IPSEC: vDstPort is zero	*/
#define RAPI_ERR_GPISESS	17	/* IPSEC: Other parm error	*/

/*  The following occur only asynchronously, as the error value when
 *	error code = RSVP_Err_API_ERROR
 */
#define RAPI_ERR_BADSEND	21	/* Sender addr not my interface	*/
#define RAPI_ERR_BADRECV	22	/* Recv addr not my interface	*/
#define RAPI_ERR_BADSPORT	23	/* Sport !=0 but Dport == 0	*/


#define RAPI_ERR_UNSUPPORTED	254
#define RAPI_ERR_UNKNOWN	255
#define RAPI_ERR_MAXERROR       255

/*
 * RSVP Error codes. An RSVP error code and error value are then
 * contained in the ErrorCode and ErrorValue arguments of the event
 * upcall function.
 *
 * The numeric values are hard coded in the RSVP specification. There
 * is a second set of symbols for this, in the rsvpproto.h, which is
 * used by rsvpd. But they all map back to the same numeric values
 * as you see below.
 */
#define RSVP_Err_NONE            (0) /* No error (confirmation) */
#define RSVP_Err_ADMISSION       (1) /* Admission control failure */
#define RSVP_Err_POLICY          (2) /* Policy control failure */
#define RSVP_Err_NO_PATH         (3) /* No path information */          
#define RSVP_Err_NO_SENDER       (4) /* No sender information */
#define RSVP_Err_BAD_STYLE       (5) /* Conflicting style */
#define RSVP_Err_UNKNOWN_STYLE   (6) /* Unknown style */
#define RSVP_Err_BAD_DSTPORT     (7) /* Conflicting destination port session */
#define RSVP_Err_BAD_SNDPORT     (8) /* Conflicting source port */
#define RSVP_Err_PREEMPTED      (12) /* Service preempted */
#define RSVP_Err_UNKN_OBJ_CLASS (13) /* Unknown object class */
#define RSVP_Err_UNKNOWN_CTYPE  (14) /* Unknown object C-type */
#define RSVP_Err_API_ERROR      (20) /* API error */
#define RSVP_Err_TC_ERROR       (21) /* Traffic control error */
#define RSVP_Err_TC_SYS_ERROR   (22) /* Traffic control system error */
#define RSVP_Err_RSVP_STS_ERROR (23) /* RSVP system error */
#define RSVP_Err_MAXERROR       (23) /* Highest known value */


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif				/* _RAPILIB_H_ */
