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
 * @(#)$RCSfile: xti_inet.h,v $ $Revision: 1.1.4.1 $ (DEC) $Date: 2000/01/18 15:42:59 $
 */

#ifndef _XTI_INET_H
#define _XTI_INET_H
#if defined (_XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)
#include <sys/types.h>
#endif

/* INTERNET SPECIFIC ENVIRONMENT */

/*
 * TCP Level
 */

#define T_INET_TCP	0x6
#define INET_TCP	0x6	/* LEGACY */

/*
 * TCP-level Options
 *
 * TCP_NODELAY and TCP_MAXSEG collide with netinet/tcp.h - values must be 
 * equivalent.
 */

#define T_TCP_NODELAY	0x1	/* don't delay packets to coalesce	*/
#define TCP_NODELAY	0x1	/* LEGACY				*/
#define T_TCP_MAXSEG	0x2	/* get maximum segment size		*/
#define TCP_MAXSEG	0x2	/* LEGACY 				*/
#define T_TCP_KEEPALIVE	0x8	/* check, if connections are alive	*/
#define TCP_KEEPALIVE	0x8	/* LEGACY 				*/

/*
 * Structure used with TCP_KEEPALIVE option.
 */

struct t_kpalive {
#if defined( _XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)
	t_scalar_t	kp_onoff;	/* option on/off		*/
	t_scalar_t	kp_timeout;	/* timeout in minutes		*/
#else
	long	kp_onoff;	/* option on/off		*/
	long	kp_timeout;	/* timeout in minutes		*/
#endif
};

#define T_GARBAGE	0x02	/* LEGACY */

/*
 * UDP level
 */

#define T_INET_UDP	0x11
#define INET_UDP	0x11	/* LEGACY */

/*
 * UDP-level Options
 */

#define T_UDP_CHECKSUM	0x0600		/* checksum computation		*/
#define UDP_CHECKSUM	0x0600		/* LEGACY */

/*
 * IP level
 */

#define T_INET_IP	0x0
#define INET_IP		0x0	/* LEGACY */

/*
 * IP-level Options
 *
 * First three names collide with netinet/in.h - values must be equivalent.
 */

#define T_IP_OPTIONS	1	/* IP per-packet options		*/
#define IP_OPTIONS	1	/* LEGACY				*/
#define T_IP_TOS	3	/* IP per-packet type of service	*/
#define IP_TOS		3	/* LEGACY 				*/
#define T_IP_TTL	4	/* IP per-packet time to live		*/
#define IP_TTL		4	/* LEGACY 				*/
#define T_IP_REUSEADDR	16	/* allow local address reuse		*/
#define IP_REUSEADDR	16	/* LEGACY 				*/
#define T_IP_DONTROUTE	17	/* just use interface addresses		*/
#define IP_DONTROUTE	17	/* LEGACY 				*/
#define T_IP_BROADCAST	18	/* permit sending of broadcast msgs	*/
#define IP_BROADCAST	18	/* LEGACY 				*/


/*
 * IP_TOS precedence levels
 */

#define	T_ROUTINE	0
#define	T_PRIORITY	1
#define	T_IMMEDIATE	2
#define	T_FLASH		3
#define	T_OVERRIDEFLASH	4
#define	T_CRITIC_ECP	5
#define	T_INETCONTROL	6
#define	T_NETCONTROL	7

#if defined(_XOPEN_SOURCE) && !defined(XTI_XPG3)
/*
 * IP_TOS type of service
 */

#define T_NOTOS		0
#define T_LDELAY	(1 << 4)
#define T_HITHRPT	(1 << 3)
#define T_HIREL		(1 << 2)

#define SET_TOS(prec, tos)	(((prec) & 0x7) << 5 | ((tos) & 0x1c))

#else	/* defined(_XOPEN_SOURCE) && !defined(XTI_XPG3) */

/*
 * TCP security options structure
 */

struct secoptions {
	short	security;	/* security fiedl			*/
	short	compartment;	/* compartment				*/
	short	handling;	/* handling restrictions		*/
#if defined( _XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)
	t_scalar_t	tcc;	/* transmission control code		*/
#else
	long	tcc;	/* transmission control code		*/
#endif
};

/*
 * TCP options
 */

struct tcp_options {
	short		precedence;	/* precedence			*/
#if defined( _XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)
	t_scalar_t	timeout;	/* abort timeout		*/
	t_scalar_t	max_seg_size;	/* maximum segment size		*/
#else
	long	timeout;	/* abort timeout		*/
	long	max_seg_size;	/* maximum segment size		*/
#endif
	struct secoptions secopt;	/* TCP security options		*/
};
#endif	/* defined(_XOPEN_SOURCE) && !defined(XTI_XPG3) */

#endif /* _XTI_INET_H */
