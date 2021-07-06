/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: ip6.h,v $
 * Revision 1.1.31.1  2003/09/23  22:00:26  Brian_Haley
 * 	Mobile IPv6 update:
 * 	- moved all Mobility messages to ip6mh.h
 * 	- added Routing Header Type 2 definition
 * 	- changed home address option to match mobile ipv6 api
 *
 * Revision 1.1.19.3  2002/01/30  20:58:53  Vladislav_Yasevich
 * 	Fixed ip6_hdr to comply to 2292bis and fixed typo in definition of
 * 	IP6OPT_JUMBO_LEN. QAR 91672.
 *
 * Revision 1.1.19.2  2002/01/17  20:41:31  Brian_Haley
 * 	Updated to support Mobile IPv6 draft 15 - Binding Update prefixlen
 * 	removed, new single address registration bit, seqno in BU and BAck
 * 	reduced to 8 bits, new BAck status codes and new Auth Data Sub-option
 * 	definition (qar 91336).
 *
 * Revision 1.1.19.1  2001/12/17  20:55:10  Vladislav_Yasevich
 * 	Removed IP6_BUF_VALID_FLAG_MASK for Mobile IPv6.
 * 	[2001/12/07  21:43:13  Brian_Haley]
 *
 * 	Mobile IPv6 submit:
 * 	- re-defined Binding Update, Ack and Home Address for correct alignment
 * 	- added Binding Ack status definitions
 * 	- added Unique Id sub-option
 * 	- added Alternate Care-of Address sub-option
 * 	- added length definitions for these new options
 * 	[2001/10/10  15:35:43  Brian_Haley]
 *
 * 	Merge of the Advanced API implementations from wildcat.classic
 * 	[2001/10/02  15:44:47  Vladislav_Yasevich]
 *
 * Revision 1.1.9.1  2000/11/09  17:48:42  Vladislav_Yasevich
 * 	Added defines for structures that were changed to make
 * 	them compatible with 2292.
 * 	[2000/11/07  20:44:14  Vladislav_Yasevich]
 *
 * 	Fixed compile problem.
 * 	[2000/11/07  17:12:59  Vladislav_Yasevich]
 *
 * 	Added deffinitions from rfc2292bis-01.
 * 	[2000/11/07  15:58:41  Vladislav_Yasevich]
 *
 * Revision 1.1.7.1  1999/10/18  20:21:13  Jack_McCann
 * 	IPv6 submit to Zulu BL6
 *
 * Revision 1.1.2.7  1999/07/08  18:22:24  Sowmini_Varadhan
 * 	Added definitions for ESP headers
 * 	[1999/07/08  16:54:04  Sowmini_Varadhan]
 *
 * Revision 1.1.2.6  1999/06/30  20:44:00  Gary_Grebus
 * 	Fix comment in ip6_auhdr.
 * 	[1999/06/29  20:49:14  Gary_Grebus]
 * 
 * 	Add sequence number field to the authentication extension header.
 * 	This is a fixed part of the header per RFC 2402.
 * 	[1999/06/28  21:12:56  Gary_Grebus]
 * 
 * Revision 1.1.2.5  1999/06/08  18:09:50  Jack_McCann
 * 	Steel BL23 merge:
 * 	- remove <sys/inttypes.h> include, we get the types we need from
 * 	  the include of in6_machtypes.h
 * 	- remove unused defines: IPV6_OPT_INTEGRITY_MASK,
 * 	  IPV6_OPT_INCLUDE_INTEGRITY, IPV6_OPT_EXCLUDE_INTEGRITY
 * 	[1999/06/08  15:52:58  Jack_McCann]
 * 
 * Revision 1.1.2.4  1998/10/30  16:58:36  Jack_McCann
 * 	- fix struct ip6_opt_jumbo_payload to eliminate padding (PTR 52-1-28)
 * 	  by changing 'u_int32_t jp_plen' to 'u_int8_t jp_plen[4]'
 * 	[1998/10/29  18:47:02  Jack_McCann]
 * 
 * Revision 1.1.2.3  1998/08/05  15:18:23  Jack_McCann
 * 	Spec updates:
 * 	- remove obsolete define of IP6_MINIMUM_LINK_MTU
 * 	- increase IPV6_MINIMUM_LINK_MTU to 1280 per
 * 	  draft-ietf-ipngwg-ipv6-spec-v2-01.txt
 * 	- remove "priority" argument from IN6_SET_IP6CTL_NORMAL macro
 * 	- remove unused IN6_SET_IP6CTL_LINKLOCAL macro
 * 	- remove ip6_un2_vfc field from struct ip6_hdr
 * 	- change ip6_un1_flow field to ip6_un1_vcf
 * 	- add IP6_VCF_xxx defines
 * 	[1998/08/05  14:30:59  Jack_McCann]
 * 
 * Revision 1.1.2.2  1998/06/22  20:59:41  Jack_McCann
 * 	IPv6 EAK version X6.2 initial submit to ipv6os pool
 * 
 * 	Remove strict/loose bitmap from type 0 routing header per latest
 * 	IPv6 spec (draft-ietf-ipngwg-ipv6-spec-v2-01.txt, Nov 1997)
 * 
 * 	revision 1.11
 * 	date: 1997/10/30 19:12:36;  author: gfisher;  state: Exp;  lines: +69 -25
 * 	name space changes for the advanced socket API
 * 	----------------------------
 * 	revision 1.10
 * 	date: 1997/02/18 19:34:30;  author: mccann;  state: Exp;  lines: +50 -0
 * 	DIGITAL UNIX V4.0B merge
 * 	----------------------------
 * 	revision 1.9
 * 	date: 1996/06/12 17:47:15;  author: mccann6;  state: Exp;  lines: +1 -0
 * 	add IPV6_MIN_JUMBO_PAYLOAD
 * 	----------------------------
 * 	revision 1.8
 * 	date: 1996/04/05 21:03:17;  author: root;  state: Exp;  lines: +46 -5
 * 	frag/reas support
 * 	----------------------------
 * 	revision 1.7
 * 	date: 1996/01/31 20:26:23;  author: root;  state: Exp;  lines: +2 -0
 * 	add IP6_MINIMUM_LINK_MTU
 * 	----------------------------
 * 	revision 1.6
 * 	date: 1996/01/29 17:01:05;  author: thomas;  state: Exp;  lines: +35 -67
 * 	Update to RFC1883
 * 	----------------------------
 * 	revision 1.5
 * 	date: 1996/01/19 18:03:02;  author: thomas;  state: Exp;  lines: +3 -11
 * 	cleanup and revamp
 * 	----------------------------
 * 	revision 1.4
 * 	date: 1995/09/11 18:31:43;  author: thomas;  state: Exp;  lines: +1 -1
 * 	fix endian problems with set_ip6_ctl macros
 * 	----------------------------
 * 	revision 1.3
 * 	date: 1995/09/06 19:49:27;  author: thomas;  state: Exp;  lines: +23 -12
 * 	move IPV6VERSION to ip6.h.  Add IPVERSIONMASK
 * 	----------------------------
 * 	revision 1.2
 * 	date: 1995/09/02 19:40:22;  author: thomas;  state: Exp;  lines: +1 -2
 * 	ANSI C cleanup
 * 	----------------------------
 * 	revision 1.1
 * 	date: 1995/09/01 23:45:25;  author: thomas;  state: Exp;
 * 	Initial revision
 * 	[1998/06/16  14:58:33  Jack_McCann]
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: ip6.h,v $ $Revision: 1.1.31.1 $ (DEC) $Date: 2003/09/23 22:00:26 $
 */

#ifndef _IP6_H_
#define	_IP6_H_

#include <netinet/in6_machtypes.h>

#define IPV6VERSION	0x60
#define	IPVERSIONMASK	0xF0

#define IPV6_MINIMUM_LINK_MTU	1280		/* minimum link mtu */
#define IPV6_MAX_PAYLOAD	65535		/* max non-jumbo payload */
#define IPV6_MIN_JUMBO_PAYLOAD	65536		/* min jumbo payload */
#define IPV6_MAX_JUMBO_PAYLOAD	0xffffffff	/* max jumbo payload */
#define IPV6_REASS_TIME		60		/* reassembly timeout seconds */

#define	IPV6_ISALIGNED(d)	((((int)(d)) & (sizeof(u_long) - 1)) == 0)
/*
 * Define the base IPv6 header
 */

struct ip6_hdrctl;
struct ip6_hdr {
    union {
	struct ip6_hdrctl {
	    uint32_t ip6_un1_flow;	/* 4 bits version, 8 bits traffic
					   class, 20 bits flow label */
	    uint16_t ip6_un1_plen;	/* payload length */
	    uint8_t  ip6_un1_nxt;	/* next header */
	    uint8_t  ip6_un1_hlim;	/* hop limit */
	} ip6_un1;
	u_int8_t  ip6_un2_vfc;		/* 4 bits version, top 4 bits tclass */
	u_int32_t ip6_un3_ctldata[2];
    } ip6_ctlun;
    struct in6_addr ip6_src;		/* source address */
    struct in6_addr ip6_dst;		/* destination address */
};

#define ip6_vcf		ip6_ctlun.ip6_un1.ip6_un1_flow
#define ip6_vfc		ip6_ctlun.ip6_un2_vfc
#define	ip6_ctl		ip6_ctlun.ip6_un3_ctldata
#define ip6_flow	ip6_ctlun.ip6_un1.ip6_un1_flow
#define	ip6_plen	ip6_ctlun.ip6_un1.ip6_un1_plen
#define	ip6_nxt		ip6_ctlun.ip6_un1.ip6_un1_nxt
#define	ip6_hlim	ip6_ctlun.ip6_un1.ip6_un1_hlim
#define	ip6_hops	ip6_ctlun.ip6_un1.ip6_un1_hlim

#define IP6_VCF_VERSION_IPV6	    IN6__MK0_MSB32_VALUE(IPV6VERSION)
#define IP6_VCF_VERSION_MASK	    IN6__MK0_MSB32_VALUE(IPVERSIONMASK)
#define	IP6_VCF_TRAFFIC_CLASS_MASK  IN6__MK3_MSB32_VALUE(0x0F, 0xF0, 0, 0)
#define IP6_VCF_FLOW_LABEL_MASK	    IN6__MK3_MSB32_VALUE(0, 0x0F, 0xFF, 0xFF)
#define IP6_VCF_CLASS_FLOW_MASK	    (IP6_VCF_TRAFFIC_CLASS_MASK|IP6_VCF_FLOW_LABEL_MASK)


/****
 ****  IPV6 OPTIONS
 ****/

/*
 * Define the high two bits of the option type. This signifies the
 * actions to take when the implementation doesn't recognize the option
 */
#define IPV6_OPT_MASK		0xC0
#define IP6OPT_TYPE(o)		((o) & IPV6_OPT_MASK)
#define IP6OPT_TYPE_SKIP	0x00	/* Skip the option */
#define IP6OPT_TYPE_DISCARD	0x40	/* Discard the packet */
#define IP6OPT_TYPE_FORCEICMP	0x80	/* Discard, send an ICMP error msg */
#define IP6OPT_TYPE_ICMP	0xc0	/* Discard, send an ICMP msg only
					   if the dst addr is not multicast */
#define IP6OPT_MUTABLE		0x20	/* Option can change in flight */

#define IPV6_OPT_IGNORE		IP6OPT_TYPE_SKIP
#define IPV6_OPT_DISCARD	IP6OPT_TYPE_DISCARD
#define IPV6_OPT_ICMP		IP6OPT_TYPE_FORCEICMP
#define IPV6_OPT_ICMP_NOMCAST	IP6OPT_TYPE_ICMP

/*
 * Known option types
 */
#define IP6OPT_PAD1		0x00	/* 00 0 00000 */
#define IP6OPT_PADN		0x01	/* 00 0 00001 */
#define IP6OPT_JUMBO		0xc2	/* 11 0 00010 = 194 */
#define IP6OPT_NSAP_ADDR	0xc3	/* 11 0 00011 */
#define IP6OPT_TUNNEL_LIMIT	0x04	/* 00 0 00100 */
#define IP6OPT_ROUTER_ALERT	0x05	/* 00 0 00101 */
#define IP6OPT_HOME_ADDRESS	0xc9	/* 11 0 01001 */
#define IP6OPT_EID		0x8a	/* 10 0 01010 */

#define IPV6_OPT_PAD1		IP6OPT_PAD1
#define IPV6_OPT_PADN		IP6OPT_PADN
#define IPV6_OPT_JUMBO_PAYLOAD	IP6OPT_JUMBO


/*
 * Generic option header
 */
struct ip6_opt {
    u_int8_t  ip6o_type;
    u_int8_t  ip6o_len;
};

/* the minimum length of an option header */
#define IP6OPT_MINLEN	2


/*
 * Pad1 option
 */
struct ip6_opt_pad1 {
    u_int8_t  ip6op1_type;	/* option type (0) */
};
/* defines for 2292 compatability */
#define p1_type		ip6op1_type


/*
 * PadN option
 */
struct ip6_opt_padn {
    u_int8_t  ip6opn_type;	/* option type (1) */
    u_int8_t  ip6opn_dlen;	/* option data length (excludes type, dlen) */
				/* option data (variable length) */
};
/* defines for 2292 compatability */
#define pn_type		ip6opn_type
#define pn_dlen		ip6opn_dlen


/*
 * Jumbo Payload option
 */
struct ip6_opt_jumbo {
    u_int8_t  ip6oj_type;	/* option type (194) */
    u_int8_t  ip6oj_len;	/* option data length (4) */
    u_int8_t  ip6oj_jumbo_len[4];	/* jumbo payload length */
};
#define IP6OPT_JUMBO_LEN	6
/* defines for 2292 compatability */
#define ip6_opt_jumbo_payload	ip6_opt_jumbo
#define jp_type			ip6oj_type
#define jp_dlen			ip6oj_len
#define jp_plen			ip6oj_jumbo_len


/*
 * NSAP Address Option
*/
struct ip6_opt_nsap {
    uint8_t  ip6on_type;
    uint8_t  ip6on_len;
    uint8_t  ip6on_src_nsap_len;
    uint8_t  ip6on_dst_nsap_len;
    /* followed by source NSAP */
    /* followed by destination NSAP */
};


/*
 * Tunnel Limit Option
 */
struct ip6_opt_tunnel {
    uint8_t  ip6ot_type;
    uint8_t  ip6ot_len;
    uint8_t  ip6ot_encap_limit;
};


/*
 * Router Alert Option
 */
struct ip6_opt_router {
    uint8_t  ip6or_type;
    uint8_t  ip6or_len;
    uint8_t  ip6or_value[2];
};

/* Router alert values (in network byte order) */
#define	IP6_ALERT_MLD	0x0000
#define	IP6_ALERT_RSVP	0x0001
#define	IP6_ALERT_AN	0x0002


/*
 * Home Address Option
 */
struct ip6_opt_home_address {
    uint8_t  ip6oha_type;
    uint8_t  ip6oha_len;		/* length, always 16 */
    uint8_t  ip6oha_addr[16];		/* Home Address */
};

#define IP6OPT_HALEN		16	/* Length of HA option */


/***
 *** EXTENSION HEADERS
 ***/

/*
 * Hop-by-Hop options header
 */

struct ip6_hbh {
    uint8_t  ip6h_nxt;        /* next header */
    uint8_t  ip6h_len;        /* length in units of 8 octets */
           /* followed by options */
};


/*
 * Destination options header
 */

struct ip6_dest {
    uint8_t  ip6d_nxt;        /* next header */
    uint8_t  ip6d_len;        /* length in units of 8 octets */
    /* followed by options */
};


/*
 * Routing header
 */

struct ip6_rthdr {
    uint8_t  ip6r_nxt;        /* next header */
    uint8_t  ip6r_len;        /* length in units of 8 octets */
    uint8_t  ip6r_type;       /* routing type */
    uint8_t  ip6r_segleft;    /* segments left */
    /* followed by routing type specific data */
};


/*
 * Routing extension header, type 0
 */

struct ip6_rthdr0 {
    uint8_t  ip6r0_nxt;       /* next header */
    uint8_t  ip6r0_len;       /* length in units of 8 octets */
    uint8_t  ip6r0_type;      /* always zero */
    uint8_t  ip6r0_segleft;   /* segments left */
    uint32_t ip6r0_reserved;  /* reserved field */
    /* followed by up to 127 IPv6 addresses */
};


/*
 * Routing extension header, type 2
 */

struct ip6_rthdr2 {
    uint8_t  ip6r2_nxt;          /* next header */
    uint8_t  ip6r2_len;          /* length in units of 8 octets, always 2 */
    uint8_t  ip6r2_type;         /* always 2 */
    uint8_t  ip6r2_segleft;      /* always 1 */
    uint32_t ip6r2_reserved;     /* reserved field */
    struct in6_addr ip6r2_homeaddr;     /* Home Address */
};


/*
 * Fragment extension header
 */

struct ip6_frag {
    uint8_t   ip6f_nxt;       /* next header */
    uint8_t   ip6f_reserved;  /* reserved field */
    uint16_t  ip6f_offlg;     /* offset, reserved, and flag */
    uint32_t  ip6f_ident;     /* identification */
};

#define IP6F_OFF_MASK		0xfff8  /* mask out offset from _offlg */
#define IP6F_RESERVED_MASK	0x0006  /* reserved bits in ip6f_offlg */
#define IPV6_FR6_MORE		0x0001	/* more fragments */


/*
 * Authentication extension header, may be followed by variable length
 * authentication data which must be an integral number of 32-bit words.
 */
struct ip6_auhdr {
    u_int8_t  au6_nxt;       /* next header */
    u_int8_t  au6_len;       /* length of header minus 2 (in 32-bit units) */
    u_int16_t au6_res;       /* reserved... */
    u_int32_t au6_spi;       /* security parameter index */
    u_int32_t au6_seq;	     /* anti-replay sequence number */
};


/*
 * ESP headers
 */
struct ip6_esphdr {
    u_int32_t esp6_spi;      /* security parameter index */
    u_int32_t esp6_seq;      /* sequence number */
};

struct ip6_espfixedtrailer {
    u_int8_t  esp6t_pad_len; /* pad length */
    u_int8_t  esp6t_nxt;     /* next header */
};


#define	IN6_SET_IP6CTL_NORMAL(ip6, protocol, hops, payload_length) \
    do { \
	ip6->ip6_ctl[0] = IN6__MK0_MSB32_VALUE(IPV6VERSION); \
	ip6->ip6_ctl[1] = IN6__MK1_MSW32_VALUE(payload_length, IN6__MK1_MSB16_VALUE(protocol, hops)); \
    } while (0)

#endif /* _IP6_H_ */
