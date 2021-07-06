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
 * @(#)$RCSfile: xti.h,v $ $Revision: 4.2.41.2 $ (DEC) $Date: 2002/05/07 17:04:23 $
 */ 

/** Copyright (c) 1989  Mentat Inc.
 ** xti.h 1.1, last change 4/14/90
 **/

#ifndef _XTI_H
#define _XTI_H
#ifdef __cplusplus
extern "C" {
#endif
#include <sys/types.h>
#if defined (_XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)
#include <inttypes.h>   /* defines uintptr_t for UNIX98 */
#endif
#ifndef	_KERNEL
#include <standards.h>
#endif  /* ifndef _KERNEL */

/* 
 * To get the SPEC1170 or XPG4 XTI compliance the macro _XOPEN_SOURCE
 * must be defined.
 * 
 * MIGRATION NOTE:
 * If you want to maintain the XTI compatibility at XPG3 level, while getting
 * the SPEC1170 or XPG4 functionality for other subsystems, then XTI_XPG3 macro 
 * can be defined to override the _XOPEN_SOURCE for XTI at 
 * compile-time. 
 */
#if defined(XTI_SPEC1170) && !defined(_XOPEN_SOURCE)
#define _XOPEN_SOURCE
#endif

/*
 * The following are the error codes needed by both the kernel
 * level transport providers and the user level library.
 */

#define	TBADADDR	1	/* incorrect addr format		*/
#define	TBADOPT		2	/* incorrect option format		*/
#define	TACCES		3	/* incorrect permissions		*/
#define	TBADF		4	/* illegal transport fd			*/
#define	TNOADDR		5	/* couldn't allocate addr		*/
#define	TOUTSTATE	6	/* out of state				*/
#define	TBADSEQ		7	/* bad call sequence number		*/
#define TSYSERR		8	/* system error				*/
#define	TLOOK		9	/* event requires attention		*/
#define	TBADDATA	10	/* illegal amount of data		*/
#define	TBUFOVFLW	11	/* buffer not large enough		*/
#define	TFLOW		12	/* flow control				*/
#define	TNODATA		13	/* no data				*/
#define	TNODIS		14	/* discon_ind not found of queue	*/
#define	TNOUDERR	15	/* unitdata error not found		*/
#define	TBADFLAG	16	/* bad flags				*/
#define	TNOREL		17	/* no ord rel found on queue		*/
#define	TNOTSUPPORT	18	/* primitive not supported		*/
#define	TSTATECHNG	19	/* state is in process of changing	*/
#define	TNOSTRUCTYPE	20	/* unsupported struct-type requested	*/
#define TBADNAME	21	/* invalid transport provider name	*/
#define	TBADQLEN	22	/* qlen is zero				*/
#define	TADDRBUSY	23	/* address in use			*/

#if   defined(_XOPEN_SOURCE) && !defined(XTI_XPG3)
#define TINDOUT		24	/* outstanding connection indications	*/
#define TPROVMISMATCH	25	/* transport provider mismatch		*/
#define TRESQLEN	26	/* resfd specified to accept w/ qlen>0	*/
#define TRESADDR	27	/* resfd not bound to same addr as fd	*/
#define TQFULL		28	/* incoming connection queue full	*/
#define TPROTO		29	/* XTI protocol error			*/
#endif	/* defined(_XOPEN_SOURCE) && !defined(XTI_XPG3) */

/*
 * The following are the events returned from t_look()
 */

#define	T_LISTEN	0x0001	/* connection indication received	*/
#define	T_CONNECT	0x0002	/* connect conformation received	*/
#define	T_DATA		0x0004	/* normal data received			*/
#define	T_EXDATA	0x0008	/* expedited data received		*/
#define	T_DISCONNECT	0x0010	/* disconnect received			*/
#define	T_UDERR		0x0040	/* datagram error indication		*/
#define	T_ORDREL	0x0080	/* orderly release indication		*/
#define	T_GODATA	0x0100	/* sending normal data is again possible*/
#define	T_GOEXDATA	0x0200	/* sending expedited data in again possible */
#define	T_EVENTS	0x0400

/*
 * The following are the flag definitions needed by the
 * user level library routines.
 */

#define	T_MORE		0x001	/* more data				*/
#define	T_EXPEDITED	0x002	/* expedited data			*/
#define	T_NEGOTIATE	0x004	/* set opts				*/
#define	T_CHECK		0x008	/* check opts				*/
#define	T_DEFAULT	0x010	/* get default opts			*/
#define T_SUCCESS	0x020	/* successful				*/
#define	T_FAILURE	0x040	/* failure				*/

#if defined(_XOPEN_SOURCE) && !defined(XTI_XPG3)
#define T_CURRENT	0x080	/* get current options			*/
#define T_PARTSUCCESS	0x100	/* partial success			*/
#define T_READONLY	0x200	/* read-only				*/
#define T_NOTSUPPORT	0x400	/* not supported			*/


/*
 * iov maximum
 */
#define	T_IOV_MAX 16	/* maximum number of scatter/gather buffers	*/
			/* value is not mandatory but if present	*/
			/* must be at least 16 				*/

struct t_iovec {
	void	*iov_base;
	size_t	iov_len;
};
#endif	/* defined(_XOPEN_SOURCE) && !defined(XTI_XPG3) */

/*
 * Protocol-specific service limits
 */

struct t_info {
#if defined( _XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)
	t_scalar_t	addr;	/* max size of transport protocol	*/
				/* address				*/
	t_scalar_t	options;/* max number of bytes of protocol-	*/
				/* specific options			*/
	t_scalar_t	tsdu;	/* max size of a transport service data */
				/* unit 				*/
	t_scalar_t	etsdu;	/* max size of expedited transport 	*/
				/* service data				*/
	t_scalar_t	connect;/* max amount of data allowed on	*/
				/* connection establishment functions	*/
	t_scalar_t	discon;	/* max data allowed on t_snddis and	*/
				/* t_rcvdis functions			*/
	t_scalar_t	servtype;/* service type supported by transport	*/
				/* provider				*/
	t_scalar_t	flags;	/* other info about the transport	*/
				/* provider				*/
#else
	long	addr;		/* max size of transport protocol	*/
				/* address				*/
	long	options;	/* max number of bytes of protocol-	*/
				/* specific options			*/
	long	tsdu;		/* max size of a transport service data */
				/* unit 				*/
	long	etsdu;		/* max size of expedited transport 	*/
				/* service data				*/
	long	connect;	/* max amount of data allowed on	*/
				/* connection establishment functions	*/
	long	discon;		/* max data allowed on t_snddis and	*/
				/* t_rcvdis functions			*/
	long	servtype;	/* service type supported by transport	*/
				/* provider				*/
#if defined(_XOPEN_SOURCE) && !defined(XTI_XPG3)
	long	flags;		/* other info about the transport	*/
				/* provider				*/
#endif /* defined(_XOPEN_SOURCE) && !defined(XTI_XPG3) */
#endif /* defined (_XOPEN_SOURCE) && (_XOPEN_SOURCE>=500) */
};

/*
 * Service types defines
 */

#define T_COTS		01	/* Connection-oriented transport	*/
				/* service				*/
#define	T_COTS_ORD	02	/* Connection-oriented with orderly	*/
				/* release				*/
#define	T_CLTS		03	/* Connectionless transport service	*/

/*
 * Flags defines (other info about the transport provider).
 */

#define T_SENDZERO	0x001	/* supports 0-length TSDUs		*/
#define T_ORDRELDATA	0x002	/* supports orderly release data	*/
#define T_XPG4_1        0x100  /* XPG4 and higher */
#define T_XPG5		0x200  /* XPG5 */


/*
 * netbuf structure
 */

struct netbuf {
	unsigned int	maxlen;
	unsigned int	len;
#if defined( _XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)
	void		*buf;
#else
	char		*buf;
#endif
};

/*
 * t_opthdr structure
 */

struct t_opthdr {
#if defined( _XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)
	t_uscalar_t	len;	/* total length of option; i.e.		*/
				/* sizeof(struct t_opthdr) + length of	*/
				/* option value in bytes		*/
	t_uscalar_t	level;	/* protocol value in bytes		*/
	t_uscalar_t	name;	/* option name				*/
	t_uscalar_t	status;	/* status value				*/
	/* followed by the option value(s)				*/
#else
	unsigned long	len;	/* total length of option; i.e.		*/
				/* sizeof(struct t_opthdr) + length of	*/
				/* option value in bytes		*/
	unsigned long	level;	/* protocol value in bytes		*/
	unsigned long	name;	/* option name				*/
	unsigned long	status;	/* status value				*/
	/* followed by the option value(s)				*/
#endif /* defined (_XOPEN_SOURCE) && (_XOPEN_SOURCE>=500) */
};

/*
 * t_bind - format of the address and options arguments of bind
 */

struct t_bind {
	struct netbuf	addr;
	unsigned	qlen;
};

/*
 * Options management structure
 */

struct t_optmgmt {
	struct netbuf	opt;
#if defined( _XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)
	t_scalar_t	flags;
#else
	long		flags;
#endif
};

/*
 * Disconnect structure
 */

struct t_discon {
	struct netbuf	udata;		/* user data			*/
	int		reason;		/* reason code			*/
	int		sequence;	/* sequence number		*/
};

/*
 * Call structure
 */

struct t_call {
	struct netbuf	addr;		/* address			*/
	struct netbuf	opt;		/* options			*/
	struct netbuf	udata;		/* user data			*/
	int		sequence;	/* sequence number		*/
};

/*
 * Datagram structure
 */

struct t_unitdata {
	struct netbuf	addr;		/* address			*/
	struct netbuf	opt;		/* options			*/
	struct netbuf	udata;		/* user data			*/
};

/*
 * Unitdata error structure
 */

struct t_uderr {
	struct netbuf	addr;		/* address			*/
	struct netbuf	opt;		/* options			*/
#if defined( _XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)
	t_scalar_t	error;		/* error code			*/
#else
	long		error;		/* error code			*/
#endif
};

/*
 * The following are structure types used when dynamically
 * allocating the above structure via alloc().
 */

#if defined(_XOPEN_SOURCE) && !defined(XTI_XPG3)

#define	T_BIND		1	/* struct t_bind			*/
#define T_OPTMGMT	2	/* struct t_optmgmt			*/
#define	T_CALL		3	/* struct t_call			*/
#define	T_DIS		4	/* struct t_discon			*/
#define	T_UNITDATA	5	/* struct t_unitdata			*/
#define	T_UDERROR	6	/* struct t_uderr			*/
#define	T_INFO		7	/* struct t_info			*/

#endif	/* defined(_XOPEN_SOURCE) && !defined(XTI_XPG3) */

#define	T_BIND_STR	1	/* struct t_bind			*/
#define T_OPTMGMT_STR	2	/* struct t_optmgmt			*/
#define	T_CALL_STR	3	/* struct t_call			*/
#define	T_DIS_STR	4	/* struct t_discon			*/
#define	T_UNITDATA_STR	5	/* struct t_unitdata			*/
#define	T_UDERROR_STR	6	/* struct t_uderr			*/
#define	T_INFO_STR	7	/* struct t_info			*/


/*
 * The following bits specify which fields of the above
 * structures should be allocated by t_alloc().
 */

#define	T_ADDR		0x01	/* address				*/
#define	T_OPT		0x02	/* options				*/
#define	T_UDATA		0x04	/* user data				*/
#define	T_ALL		0xffff	/* all the above fields supported	*/

/*
 * The following are the states for the user.
 */

#define T_UNINIT	0	/* uninitialized state			*/
#define	T_UNBND		1	/* unbound				*/
#define	T_IDLE		2	/* idle					*/
#define	T_OUTCON	3	/* outgoing connection pending		*/
#define	T_INCON		4	/* incoming connection pending		*/
#define	T_DATAXFER	5	/* data transfer			*/
#define	T_OUTREL	6	/* outgoing orderly release		*/
#define	T_INREL		7	/* incoming orderly release		*/

/* General purpose defines */

#define	T_YES		1
#define	T_NO		0
#define	T_UNUSED	(-1)	/* LEGACY */
#define	T_NULL		0
#define	T_ABSREQ	0x8000

#if defined(_XOPEN_SOURCE) && !defined(XTI_XPG3)
#define T_INFINITE	(-1)	/* values for t_info			*/
#define T_INVALID	(-2)	/* values for t_info			*/

/*
 *  Definitions for t_sysconf
 */
#define	_SC_T_IOV_MAX	1	/* value recommended only, not mandatory */

/*
 * General definitions for option management
 */

#define T_UNSPEC	(~0-2)	/* applicable to t_uscalar_t, t_scalar_t, char,..	*/
#define T_ALLOPT	0	/* value recommended only, not mandatory */

#if defined( _XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)

#define T_ALIGN(p)	(((t_uscalar_t)(p) + sizeof (t_scalar_t) - 1) \
					       & ~(sizeof (t_scalar_t) - 1))
/*
 * Helper macro
 * _T_USCALAR_ALIGN - macro aligns to "sizeof (t_uscalar_t) boundary
 */
#define _T_USCALAR_ALIGN(p)     (((uintptr_t)(p) + (sizeof (t_scalar_t) - 1))\
                                        & ~(sizeof (t_scalar_t)-1))

#define	T_OPT_DATA(tohp)	\
	((unsigned char *)(tohp) + sizeof (struct t_opthdr))

#define _T_NEXTHDR(pbuf, buflen, popt) \
        (((char *)(popt) + _T_USCALAR_ALIGN((popt)->len) + \
            sizeof (struct t_opthdr) <= \
                ((char *)(pbuf) + (buflen))) ? \
        (struct t_opthdr *)((char *)(popt) + _T_USCALAR_ALIGN((popt)->len)) :\
            (struct t_opthdr *)0)

#define T_OPT_NEXTHDR(nbp, tohp)   _T_NEXTHDR((nbp)->buf, (nbp)->len, (tohp))

#define	T_OPT_FIRSTHDR(nbp)	\
     ((((char *)(nbp)->buf + sizeof (struct t_opthdr)) <= \
	(char *)(nbp)->buf + (nbp)->len) ? \
	(struct t_opthdr *)(nbp)->buf : (struct t_opthdr *)0)

#else
#define T_ALIGN(p)	(((unsigned long)(p) + sizeof (long) - 1) \
						& ~(sizeof (long) - 1))

#define OPT_NEXTHDR(pbuf, buflen, popt)	\
			(struct t_opthdr *) \
			 (((char *)(popt) + T_ALIGN((popt)->len) <  \
				(char *)(pbuf) + (buflen)) ? \
			 ((char *)(popt) + T_ALIGN((popt)->len)) : \
			 0)

#endif

/*
 * XTI-level Options
 */

#define XTI_GENERIC	0xffff

#define XTI_DEBUG	0x0001	/* enable debugging			*/
#define XTI_LINGER	0x0080	/* linger on close if data present	*/
#define XTI_RCVBUF	0x1002	/* receive buffer size			*/
#define XTI_RCVLOWAT	0x1004	/* receive low-water mark		*/
#define XTI_SNDBUF	0x1001	/* send buffer size			*/
#define XTI_SNDLOWAT	0x1003	/* send low-water mark			*/

/*
 * Structure used with linger option
 */

struct t_linger {
#if defined( _XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)
	t_scalar_t	l_onoff;	/* option on/off		*/
	t_scalar_t	l_linger;	/* linger time			*/
#else
	long		l_onoff;	/* option on/off		*/
	long		l_linger;	/* linger time			*/
#endif /* defined (_XOPEN_SOURCE) && (_XOPEN_SOURCE>=500) */
};
#endif	/* defined(_XOPEN_SOURCE) && !defined(XTI_XPG3) */


#if defined(_KERNEL) 
#include <streamsm/xti_inet.h>
#include <streamsm/xti_osi.h>
#elif (_XOPEN_SOURCE<500)
#include <xti_inet.h>
#include <xti_osi.h>
#endif


#ifndef	_KERNEL

/* 
 * XTI error return
 */

extern	int	*_terrno(void);
#define	t_errno	(*(_terrno()))

extern	char *	t_errlist[];
extern	int	t_nerr;


#if defined( _XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)
extern	int	t_accept __((int, int, const struct t_call *));
extern	void *  t_alloc __((int, int, int));
extern	int	t_bind __((int, const struct t_bind *, struct t_bind *));
extern	int	t_connect __((int, const struct t_call *,struct t_call *));
extern	int	t_error __((const char *));
extern	int	t_free __((void *, int));
extern	int	t_open __((const char *, int, struct t_info *));
extern	int	t_optmgmt __((int, const struct t_optmgmt *, 
				struct t_optmgmt *));
extern	int	t_rcv __((int, void *, unsigned, int *));
extern int	t_rcvreldata __((int, struct t_discon *));
extern int	t_rcvv __((int, struct t_iovec *, unsigned int, int *));
extern int	t_rcvvudata __((int, struct t_unitdata *, struct t_iovec *, 
				unsigned int, int *));
extern	int	t_snd __((int, void *, unsigned, int));
extern	int	t_snddis __((int, const struct t_call *));
extern int	t_sndreldata __((int, struct t_discon *));
extern	int	t_sndudata __((int, const struct t_unitdata *));
extern int	t_sndv __((int, const struct t_iovec *, unsigned int, int));
extern int	t_sndvudata __((int, struct t_unitdata *, struct t_iovec *, 
				unsigned int));
extern	const char *	t_strerror __((int));
extern int	t_sysconf __((int));
#else
extern	int	t_accept __((int, int, struct t_call *));
extern	char *	t_alloc __((int, int, int));
extern	int	t_bind __((int, struct t_bind *, struct t_bind *));
extern	int	t_connect __((int, struct t_call *,struct t_call *));
extern	int	t_error __((char *));
extern	int	t_free __((char *, int));
extern	int	t_open __((char *, int, struct t_info *));
extern	int	t_optmgmt __((int, struct t_optmgmt *, struct t_optmgmt *));
extern	int	t_rcv __((int, char *, unsigned, int *));
extern	int	t_snd __((int, char *, unsigned, int));
extern	int	t_snddis __((int, struct t_call *));
extern	int	t_sndudata __((int, struct t_unitdata *));
extern	char *	t_strerror __((int));
#endif


extern	int	t_blocking __((int));
extern	int	t_close __((int));
extern	int	t_getinfo __((int, struct t_info *));
extern	int	t_getprotaddr __((int, struct t_bind *, struct t_bind *));
extern	int	t_getstate __((int));
extern	int	t_listen __((int, struct t_call *));
extern	int	t_look __((int));
extern	int	t_nonblocking __((int));
extern	int	t_rcvconnect __((int, struct t_call *));
extern	int	t_rcvdis __((int, struct t_discon *));
extern	int	t_rcvrel __((int));
extern	int	t_rcvudata __((int, struct t_unitdata *, int *));
extern	int	t_rcvuderr __((int, struct t_uderr *));
extern	int	t_sndrel __((int));
extern	int	t_sync __((int));
extern	int	t_unbind __((int));

#endif  /* !_KERNEL */
#ifdef __cplusplus
}
#endif
#endif
