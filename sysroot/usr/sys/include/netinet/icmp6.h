/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: icmp6.h,v $
 * Revision 1.1.30.4  2008/03/07  03:40:47  Akshay_Nesari
 *  TAHI expects minimum of 48 bytes of data within icmp6 error message.
 *  Increased ICMP6_BUF_LENGTH so that TAHI Mobile IPv6 test for redirection
 *  (tunneling) of icmp error messages pass.
 *
 * Revision 1.1.30.3  2003/11/21  14:59:02  Brian_Haley
 * 	Updated Mobile IPv6 DHAAD and MPS codes based on RFC.
 *
 * Revision 1.1.30.2  2003/10/15  21:10:59  Vladislav_Yasevich
 * 	Added an MLD constant to specifies a default delay of the
 * 	MLD report.  The variable is described as Unsolicited Report Interval
 * 	in rfc 2710.
 *
 * Revision 1.1.30.1  2003/09/23  21:52:38  Brian_Haley
 * 	Added Home Agent Mobility Information Option, DHAAD and Prefix Sol/Adv
 * 	messages.
 *
 * Revision 1.1.20.1  2001/12/17  20:54:43  Vladislav_Yasevich
 * 	Mobile IPv6 submit:
 * 	- added Router Advertisement H-bit
 * 	- added Prefix Information R-bit
 * 	- added Advertisement Interval option structure
 *
 * Revision 1.1.10.2  2000/03/14  20:05:19  Vladislav_Yasevich
 * 	Changed NOTNEIGHBOR to BEYONDSCOPE as per the new spec. QAR 77901
 *
 * Revision 1.1.10.1  1999/10/18  20:20:40  Jack_McCann
 * 	IPv6 submit to Zulu BL6
 *
 * Revision 1.1.2.10  1999/06/08  18:09:37  Jack_McCann
 * 	IPv6 EAK X6.3 to Steel BL23 merge:
 * 	- remove <sys/inttypes.h> include, we get the types we need from
 * 	  the include of in6_machtypes.h
 * 	[1999/06/08  15:51:00  Jack_McCann]
 *
 * Revision 1.1.2.9  1999/03/26  21:41:25  Jack_McCann
 * 	merge 32-bit icmp6_filter and macros from yanick pouffary
 * 	[1999/03/26  21:08:38  Jack_McCann]
 * 
 * Revision 1.1.2.8  1999/01/12  19:48:05  Sowmini_Varadhan
 * 	modified ether-centric definition of nd_opt_linkaddr_addr
 * 	[1999/01/08  15:49:36  Sowmini_Varadhan]
 * 
 * Revision 1.1.2.7  1999/01/07  22:49:08  Jack_McCann
 * 	- remove previously commented out define of ND6_SIZE_OPTIONSPACE
 * 	- change ND_DEF_ADVVALIDLIFETIME from ND_INFINITY to 2592000 seconds
 * 	[1998/11/13  23:40:27  Jack_McCann]
 * 
 * Revision 1.1.2.6  1998/09/15  18:08:25  Eric_Wong
 * 	RFC2292 Advanced Sockets API for IPv6 changes
 * 	Changed ICMP6 filter access as defined in section 3.2.
 * 	[1998/09/15  15:01:59  Eric_Wong]
 * 
 * Revision 1.1.2.5  1998/08/11  18:45:08  Geraldine_Harter
 * 	Remove support for IPV6_SOLMCAST_COMPAT
 * 	[1998/08/06  16:58:26  Geraldine_Harter]
 * 
 * Revision 1.1.2.4  1998/08/05  15:18:17  Jack_McCann
 * 	Spec updates:
 * 	- derive ICMP6_MAX_ERROR_LENGTH from IPV6_MINIMUM_LINK_MTU (1280)
 * 	  rather than hard coded 576 in anticipation of the next update to
 * 	  draft-ietf-ipngwg-icmp-v2-00.txt (as discussed on ipng mail list)
 * 	- remove IPV6_PRIORITY_ICMPV6 macro
 * 	- update ND_SET_IP6CTL use of IN6_SET_IP6CTL_NORMAL macro
 * 	  (it no longer takes a "priority" argument)
 * 	[1998/08/05  14:30:44  Jack_McCann]
 * 
 * Revision 1.1.2.3  1998/07/08  18:12:24  Ravi_Shankar
 * 	Update the constants as per draft-ietf-ipngwg-discovery-v2-02.txt (PTR 52-1-63)
 * 	[1998/07/08  17:12:57  Ravi_Shankar]
 * 
 * Revision 1.1.2.2  1998/06/22  20:58:56  Jack_McCann
 * 	IPv6 EAK version X6.2 initial submit to ipv6os pool
 * 
 * 	Revision 1.2  1998/01/12  19:37:12  varadhan
 * 	added source link layer addr option
 * 
 * 	Revision 1.1  1997/10/29  21:17:07  gfisher
 * 	Initial revision (renamed from ip6_icmp.h to icmp6.h)
 * 	the new header ICMP header file for the advanced socket API
 * 	encompassing all previous defines from ip6_icmp.h and nd6_protocol.h
 * 	as well as new defines
 * 
 * 	Revision 1.5  1997/02/18  19:34:30  mccann
 * 	DIGITAL UNIX V4.0B merge
 * 
 * 	revision 1.4
 * 	date: 1996/01/31 20:24:31;  author: root;  state: Exp;  lines: +2 -0
 * 	add icmp6_data8
 * 
 * 	revision 1.3
 * 	date: 1996/01/19 18:03:02;  author: thomas;  state: Exp;  lines: +170 -317
 * 	Rewrite.  Add ICMPv6 setsockopts.
 * 
 * 	revision 1.2
 * 	date: 1995/09/02 19:40:22;  author: thomas;  state: Exp;  lines: +9 -8
 * 	ANSI C cleanup
 * 
 * 	revision 1.1
 * 	date: 1995/08/24 19:28:29;  author: root;  state: Exp;
 * 	Initial revision (entered into source control)
 * 
 * 	5 MAy 1995	Alex Conta 	X1.7
 * 	Add the ICMP6_LISTEN flag.
 * 
 * 	28 April 1995	Alex Conta 	X1.6
 * 	Make the MGM header definitions in a separate header,
 * 	since they brake the inside header alignments. For now only.
 * 
 * 	23 March 1995	Alex Conta 	X1.5
 * 	Add Discovery definitons.
 * 
 * 	23 March 1995	Alex Conta 	X1.4
 * 	Add Multicast Group Management definitons.
 * 
 * 	22 March 1995	Alex Conta 	X1.3
 * 	Add IP6PROTO_ICMP6 flags definiton.
 * 
 * 	22 March 1995	Alex Conta 	X1.2
 * 	Add IP6PROTO_ICMP6 definiton.
 * 
 * 	15 March 1995	Alex Conta 	X1.1
 * 	Add protoype entry points.
 * 
 * 	10 March 1995	Alex Conta	created
 * 	[1998/06/16  14:57:49  Jack_McCann]
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: icmp6.h,v $ $Revision: 1.1.30.4 $ (DEC) $Date: 2008/03/07 03:40:47 $
 */

#ifndef _IP6_ICMP_H_
#define _IP6_ICMP_H_

#include <netinet/in6_machtypes.h>

/*
 * Internet Control Message Protocol V6 Definitions.
 */

/*
 * Define IPv6 ICMP (ICMPv6) error and informational header structures.
 */
struct icmp6_hdr {
    uint8_t	icmp6_type;		/* Type field */
    uint8_t	icmp6_code;		/* Code field */
    uint16_t	icmp6_cksum;		/* Checksum field */
    union {
	uint32_t	icmp6_un_data32[1];	/* Type-specific field */
	uint16_t	icmp6_un_data16[2];	/* Type-specific field */
	uint8_t		icmp6_un_data8[4];	/* Type-specific field */
    } icmp6_dataun;
};

#define	icmp6_data32	icmp6_dataun.icmp6_un_data32
#define	icmp6_data16	icmp6_dataun.icmp6_un_data16
#define	icmp6_data8	icmp6_dataun.icmp6_un_data8
#define	icmp6_pptr	icmp6_data32[0]		/* PARAMPROB */
#define	icmp6_mtu	icmp6_data32[0]		/* PKT_TOOBIG */
#define	icmp6_id	icmp6_data16[0]		/* ECHO */
#define	icmp6_seq	icmp6_data16[1]		/* ECHO */
#define	icmp6_maxdelay	icmp6_data16[0]		/* MLD/MGM_xxx  */
#define	icmp6_reserved	icmp6_data16[1]		/* MIP6 */

#define	ICMP6_DST_UNREACH	1
#define	ICMP6_PACKET_TOO_BIG	2
#define	ICMP6_TIME_EXCEEDED	3
#define	ICMP6_PARAM_PROB	4

#define	ICMP6_INFOMSG_MASK	0x80	/* all informational messages */

#define	ICMP6_ECHO_REQUEST		128
#define	ICMP6_ECHO_REPLY		129
#define	ICMP6_MEMBERSHIP_QUERY		130
#define	ICMP6_MEMBERSHIP_REPORT		131
#define	ICMP6_MEMBERSHIP_REDUCTION	132

/*
 * Definition of IPv6 ICMP error messages Code field values.
 */

#define	ICMP6_DST_UNREACH_NOROUTE	0 /* no route to destination */
#define	ICMP6_DST_UNREACH_ADMIN 	1 /* communication with destination */
					  /*  administratively prohibited */
#define	ICMP6_DST_UNREACH_BEYONDSCOPE	2 /* address beyond scope */
#define	ICMP6_DST_UNREACH_ADDR		3 /* address unreachable */
#define	ICMP6_DST_UNREACH_NOPORT	4 /* bad port */

#define	ICMP6_TIME_EXCEED_TRANSIT	0 /* Hop Limit == 0 in transit */
#define	ICMP6_TIME_EXCEED_REASSEMBLY	1 /* Reassembly time out */

#define	ICMP6_PARAMPROB_HEADER		0 /* erroneous header field */
#define	ICMP6_PARAMPROB_NEXTHEADER	1 /* unrecognized Next Header */
#define	ICMP6_PARAMPROB_OPTION		2 /* unrecognized IPv6 option */


#ifdef IN6_HAS_64BIT_INTTYPE
    /*
     * This is a cheat for little endian architectures.
     * Since the first byte is the type, it's the LSB for
     * little endian machines so set entire quadword at
     * one time...
     */
#define	ICMP6_SET_HDR_SIMPLE(icmp, type) \
    ((void) (*(u_int64_t *) (icmp) = IN6__MK0_MSB64_VALUE(type)))
#else
#define	ICMP6_SET_HDR_SIMPLE(icmp, type) \
    do { \
        ((u_int32_t *) icmp)[0] = IN6__MK0_MSB32_VALUE(type); \
	((u_int32_t *) icmp)[1] = 0; \
    } while (0)
#endif
#define	ICMP6_SET_HDR(icmp, type, code, data) \
    do { \
        ((u_int32_t *) icmp)[0] = IN6__MK1_MSB32_VALUE(type, code); \
	((u_int32_t *) icmp)[1] = (data); \
    } while (0)

/*
 * Additional constants
 */
#define	ICMP6_MAX_ERROR_LENGTH	(IPV6_MINIMUM_LINK_MTU - sizeof(struct ip6_hdr) - sizeof(struct icmp6_hdr))

/*
 * This should be enough for the ICMPv6 header as well
 * either the neighbor discovery packet or the upper layer
 * packet header (ie. TCP or UDP)
 */
#define	ICMP6_BUF_LENGTH   (sizeof(struct icmp6_hdr) + sizeof(struct ip6_hdr) + 48)

/*
 * The following are used to control the ICMPv6 message filters.
 */

#define	ICMP6_FILTER		1

struct icmp6_filter {
#ifdef IN6_HAS_64BIT_INTTYPE
    uint64_t  icmp6_filt[4];  /* 4*64 = 256 bits */
#else
    uint32_t  icmp6_filt[8];  /* 8*32 = 256 bits */
#endif
};

#ifdef IN6_HAS_64BIT_INTTYPE
#define ICMP6_FILTER_WILLPASS(_type_, _filterp_) \
    ((((_filterp_)->icmp6_filt[(_type_) >> 6]) & (1 << ((_type_) & 63))) != 0)
#define ICMP6_FILTER_WILLBLOCK(_type_, _filterp_) \
    ((((_filterp_)->icmp6_filt[(_type_) >> 6]) & (1 << ((_type_) & 63))) == 0)
#define ICMP6_FILTER_SETPASS(_type_, _filterp_) \
    ((((_filterp_)->icmp6_filt[(_type_) >> 6]) |=  (1 << ((_type_) & 63))))
#define ICMP6_FILTER_SETBLOCK(_type_, _filterp_) \
    ((((_filterp_)->icmp6_filt[(_type_) >> 6]) &= ~(1 << ((_type_) & 63))))
#define ICMP6_FILTER_SETPASSALL(_filterp_) \
    (_filterp_)->icmp6_filt[0] = ~0L; \
    (_filterp_)->icmp6_filt[1] = ~0L; \
    (_filterp_)->icmp6_filt[2] = ~0L; \
    (_filterp_)->icmp6_filt[3] = ~0L; 
#define ICMP6_FILTER_SETBLOCKALL(_filterp_) \
    (_filterp_)->icmp6_filt[0] = 0L; \
    (_filterp_)->icmp6_filt[1] = 0L; \
    (_filterp_)->icmp6_filt[2] = 0L; \
    (_filterp_)->icmp6_filt[3] = 0L; 
#else	/* IN6_HAS_64BIT_INTTYPE */
#define ICMP6_FILTER_WILLPASS(_type_, _filterp_) \
    ((((_filterp_)->icmp6_filt[(_type_) >> 5]) & (1 << ((_type_) & 31))) != 0)
#define ICMP6_FILTER_WILLBLOCK(_type_, _filterp_) \
    ((((_filterp_)->icmp6_filt[(_type_) >> 5]) & (1 << ((_type_) & 31))) == 0)
#define ICMP6_FILTER_SETPASS(_type_, _filterp_) \
    ((((_filterp_)->icmp6_filt[(_type_) >> 5]) |=  (1 << ((_type_) & 31))))
#define ICMP6_FILTER_SETBLOCK(_type_, _filterp_) \
    ((((_filterp_)->icmp6_filt[(_type_) >> 5]) &= ~(1 << ((_type_) & 31))))
#define ICMP6_FILTER_SETPASSALL(_filterp_) \
    (_filterp_)->icmp6_filt[0] = ~0L; \
    (_filterp_)->icmp6_filt[1] = ~0L; \
    (_filterp_)->icmp6_filt[2] = ~0L; \
    (_filterp_)->icmp6_filt[3] = ~0L; \
    (_filterp_)->icmp6_filt[4] = ~0L; \
    (_filterp_)->icmp6_filt[5] = ~0L; \
    (_filterp_)->icmp6_filt[6] = ~0L; \
    (_filterp_)->icmp6_filt[7] = ~0L; 
#define ICMP6_FILTER_SETBLOCKALL(_filterp_) \
    (_filterp_)->icmp6_filt[0] = 0L; \
    (_filterp_)->icmp6_filt[1] = 0L; \
    (_filterp_)->icmp6_filt[2] = 0L; \
    (_filterp_)->icmp6_filt[3] = 0L; \
    (_filterp_)->icmp6_filt[4] = 0L; \
    (_filterp_)->icmp6_filt[5] = 0L; \
    (_filterp_)->icmp6_filt[6] = 0L; \
    (_filterp_)->icmp6_filt[7] = 0L; 
#endif	/* IN6_HAS_64BIT_INTTYPE */

/*
 * ICMPv6 Neighbor Discovery Type and Code Values
 */

#define ND_ROUTER_SOLICIT           133
#define ND_ROUTER_ADVERT            134
#define ND_NEIGHBOR_SOLICIT         135
#define ND_NEIGHBOR_ADVERT          136
#define ND_REDIRECT                 137

/*
 * Router solicitation structure
 */

struct nd_router_solicit {
    struct icmp6_hdr  nd_rs_hdr;
    /* could be followed by options */
};

#define ND_SIZE_ROUTER_SOLICITATION sizeof(struct nd_router_solicit)


#define nd_rs_type               nd_rs_hdr.icmp6_type
#define nd_rs_code               nd_rs_hdr.icmp6_code
#define nd_rs_cksum              nd_rs_hdr.icmp6_cksum
#define nd_rs_reserved           nd_rs_hdr.icmp6_data32[0]

/*
 * Router advertisement structure
 */

struct nd_router_advert {	    /* router advertisement */
    struct icmp6_hdr  nd_ra_hdr;
    uint32_t   nd_ra_reachable;	    /* reachable time */
    uint32_t   nd_ra_retransmit;    /* retransmit timer */
    /* could be followed by options */
};

#define nd_ra_type               nd_ra_hdr.icmp6_type
#define nd_ra_code               nd_ra_hdr.icmp6_code
#define nd_ra_cksum              nd_ra_hdr.icmp6_cksum
#define nd_ra_curhoplimit        nd_ra_hdr.icmp6_data8[0]
#define nd_ra_flags_reserved     nd_ra_hdr.icmp6_data8[1]
#define nd_ra_router_lifetime    nd_ra_hdr.icmp6_data16[1]
#define ND_RA_FLAG_MANAGED       0x80
#define ND_RA_FLAG_OTHER         0x40
#define ND_RA_FLAG_HOMEAGENT     0x20

#define ND_SIZE_ROUTER_ADVERTISEMENT sizeof(struct nd_router_advert)

/*
 * Neighbor solicitation structure
 */

struct nd_neighbor_solicit {
    struct icmp6_hdr  nd_ns_hdr;
    struct in6_addr   nd_ns_target; /* target address */
    /* could be followed by options */
};

#define nd_ns_type               nd_ns_hdr.icmp6_type
#define nd_ns_code               nd_ns_hdr.icmp6_code
#define nd_ns_cksum              nd_ns_hdr.icmp6_cksum
#define nd_ns_reserved           nd_ns_hdr.icmp6_data32[0]

#define	ND_SIZE_NEIGHBOR_SOLICITATION	sizeof(struct nd_neighbor_solicit)

#define	ND_SET_SOLICIT_MULTICAST(addrp, srcaddrp) \
    do { \
        IN6_SET_MULTICAST_CLASS(addrp, IN6_MCSCOPE_LINKLOCAL); \
	(addrp)->s6_laddr[2] = (0x01 << IN6_LSB32_SHIFT); \
	(addrp)->s6_laddr[3] = (srcaddrp)->s6_laddr[3] | IN6__MK0_MSB32_VALUE(0xff); \
    } while (0)

#define ND_IS_ADDR_SOLICIT_MULTICAST(addrp) \
    ((addrp)->s6_laddr[0] == IN6__MK1_MSB32_VALUE(0xFF, IN6_MCSCOPE_LINKLOCAL) \
     && (addrp)->s6_laddr[1] == 0 \
     && (addrp)->s6_laddr[2] == (0x01 << IN6_LSB32_SHIFT) \
     && (addrp)->s6_addr[12] == 0xffU)

/*
 * Neighbor advertisement structure
 */

struct nd_neighbor_advert {
    struct icmp6_hdr  nd_na_hdr;
    struct in6_addr   nd_na_target; /* target address */
    /* could be followed by options */
};

#define nd_na_type               nd_na_hdr.icmp6_type
#define nd_na_code               nd_na_hdr.icmp6_code
#define nd_na_cksum              nd_na_hdr.icmp6_cksum
#define nd_na_flags_reserved     nd_na_hdr.icmp6_data32[0]

#define	ND_SIZE_NEIGHBOR_ADVERTISEMENT sizeof(struct nd_neighbor_advert)

/*
 * Note that the following are defined such can be used
 * directly without having to change nadv6_flags to host
 * order.
 */

#if     BYTE_ORDER == BIG_ENDIAN
#define ND_NA_FLAG_ROUTER        0x80000000
#define ND_NA_FLAG_SOLICITED     0x40000000
#define ND_NA_FLAG_OVERRIDE      0x20000000
#else   /* BYTE_ORDER == LITTLE_ENDIAN */
#define ND_NA_FLAG_ROUTER        0x00000080
#define ND_NA_FLAG_SOLICITED     0x00000040
#define ND_NA_FLAG_OVERRIDE      0x00000020
#endif

/*
 * redirect
 */

struct nd_redirect {
    struct icmp6_hdr  nd_rd_hdr;
    struct in6_addr   nd_rd_target; /* target address */
    struct in6_addr   nd_rd_dst;    /* destination address */
    /* could be followed by options */
};

#define nd_rd_type               nd_rd_hdr.icmp6_type
#define nd_rd_code               nd_rd_hdr.icmp6_code
#define nd_rd_cksum              nd_rd_hdr.icmp6_cksum
#define nd_rd_reserved           nd_rd_hdr.icmp6_data32[0]

#define ND_SIZE_REDIRECT	sizeof(struct nd_redirect)

/*
 * Neighbor discovery option header
 */

struct nd_opt_hdr {
    uint8_t  nd_opt_type;
    uint8_t  nd_opt_len;        /* in units of 8 octets */
    /* followed by option specific data */
};


/*
 * Neighbor Discovery options.
 */
#define  ND_OPT_SOURCE_LINKADDR       1
#define  ND_OPT_TARGET_LINKADDR       2
#define  ND_OPT_PREFIX_INFORMATION    3
#define  ND_OPT_REDIRECTED_HEADER     4
#define  ND_OPT_MTU                   5
#define  ND_OPT_ADVERTISEMENT_INTERVAL 7
#define  ND_OPT_HOME_AGENT_INFORMATION 8
#define  ND_OPT_ENDOFLIST	    256


#define	ND_SIZE_OPTIONSPACE	16

/*
 * prefix information
 */

struct nd_opt_prefix_info {
    uint8_t   nd_opt_pi_type;
    uint8_t   nd_opt_pi_len;
    uint8_t   nd_opt_pi_prefix_len;
    uint8_t   nd_opt_pi_flags_reserved;
    uint32_t  nd_opt_pi_valid_time;
    uint32_t  nd_opt_pi_preferred_time;
    uint32_t  nd_opt_pi_reserved2;
    struct in6_addr  nd_opt_pi_prefix;
};

#define ND_OPT_PI_FLAG_ONLINK        0x80
#define ND_OPT_PI_FLAG_AUTO          0x40
#define ND_OPT_PI_FLAG_ROUTER        0x20

#define	ND_SIZE_OPT_PREFIX_INFO sizeof(struct nd_opt_prefix_info)

/*
 * redirected header
 */

struct nd_opt_rd_hdr {
    uint8_t   nd_opt_rh_type;
    uint8_t   nd_opt_rh_len;
    uint16_t  nd_opt_rh_reserved1;
    uint32_t  nd_opt_rh_reserved2;
    /* followed by IP header and data */
};

#define ND_SIZE_OPT_RED_HDR sizeof(struct nd_opt_rd_hdr)

#define ND_OPT_LEN_UNIT 8	/* option length is units of 8 octets */
#define ND_OPT_MIN_SIZE 8	/* minimum size of option is 8 octets */

/*
 * MTU option
 */

struct nd_opt_mtu {
    uint8_t   nd_opt_mtu_type;
    uint8_t   nd_opt_mtu_len;
    uint16_t  nd_opt_mtu_reserved;
    uint32_t  nd_opt_mtu_mtu;
};

#define ND_SIZE_OPT_MTU sizeof(struct nd_opt_mtu)

/*
 * source link layer addr option 
 */
struct nd_opt_linkaddr {
  u_int8_t nd_opt_linkaddr_type;
  u_int8_t nd_opt_linkaddr_len;
  u_int8_t nd_opt_linkaddr_addr[1];
};

#define ND_SIZE_OPT_LINKADDR sizeof(struct nd_opt_linkaddr)

/*
 * advertisement interval option 
 */
struct nd_opt_adv_interval {
  u_int8_t  nd_opt_ai_type;
  u_int8_t  nd_opt_ai_len;
  u_int16_t nd_opt_ai_reserved;
  u_int32_t nd_opt_ai_interval;
};

#define ND_SIZE_OPT_ADV_INTERVAL sizeof(struct nd_opt_adv_interval)

struct nd_opt_homeagent_info {
  u_int8_t nd_opt_hai_type;
  u_int8_t nd_opt_hai_len;
  u_int16_t nd_opt_hai_reserved;
  u_int16_t nd_opt_hai_pref;
  u_int16_t nd_opt_hai_lifetime;
};

#define ND_SIZE_OPT_HOMEAGENT_INFO sizeof(struct nd_opt_homeagent_info)

/*
 * Multicast Listener Discovery structures and defnitions.
 */

#define MLD_LISTENER_QUERY	ICMP6_MEMBERSHIP_QUERY
#define MLD_LISTENER_REPORT	ICMP6_MEMBERSHIP_REPORT
#define MLD_LISTENER_REDUCTION	ICMP6_MEMBERSHIP_REDUCTION

struct mld_hdr {
  struct icmp6_hdr	mld_icmp6_hdr;
  struct in6_addr	mld_addr;
};

#define mld_type	mld_icmp6_hdr.icmp6_type
#define mld_code        mld_icmp6_hdr.icmp6_code
#define mld_cksum       mld_icmp6_hdr.icmp6_cksum
#define mld_maxdelay	mld_icmp6_hdr.icmp6_maxdelay
#define mld_reserved	mld_icmp6_hdr.icmp6_reserved

#define	ICMP6_MLD_LENGTH   (sizeof(struct mld_hdr))

/* 
 * Mobile IPv6 header structuers and definitions.
 */

/* Dynamic Home Agent Discovery */
#define MIP6_HA_DISCOVERY_REQUEST	144
#define MIP6_HA_DISCOVERY_REPLY		145

/*
 * Home Agent Address Discovery Request Message
 */
struct mip6_dhaad_req {
    struct icmp6_hdr    mip6_dhreq_hdr;
};

#define mip6_dhreq_type      mip6_dhreq_hdr.icmp6_type
#define mip6_dhreq_code      mip6_dhreq_hdr.icmp6_code
#define mip6_dhreq_cksum     mip6_dhreq_hdr.icmp6_cksum
#define mip6_dhreq_id        mip6_dhreq_hdr.icmp6_id
#define mip6_dhreq_reserved  mip6_dhreq_hdr.icmp6_reserved

#define MIP6_SIZE_DHAAD_REQUEST sizeof(struct mip6_dhaad_req)

/*
 * Home Agent Address Discovery Reply Message
 */
struct mip6_dhaad_rep {
    struct icmp6_hdr    mip6_dhrep_hdr;
    /* followed by address(es) */
};

#define mip6_dhrep_type      mip6_dhrep_hdr.icmp6_type
#define mip6_dhrep_code      mip6_dhrep_hdr.icmp6_code
#define mip6_dhrep_cksum     mip6_dhrep_hdr.icmp6_cksum
#define mip6_dhrep_id        mip6_dhrep_hdr.icmp6_id
#define mip6_dhrep_reserved  mip6_dhrep_hdr.icmp6_reserved

#define MIP6_SIZE_DHAAD_REPLY sizeof(struct mip6_dhaad_rep)

/* Mobile Prefix Solicitation/Advertisement */
#define MIP6_PREFIX_SOLICIT	146
#define MIP6_PREFIX_ADVERT	147

/*
 * Mobile Prefix Solicitation Message
 */
struct mip6_prefix_solicit {
    struct icmp6_hdr	mip6_ps_hdr;
};
#define mip6_ps_type		mip6_ps_hdr.icmp6_type
#define mip6_ps_code		mip6_ps_hdr.icmp6_code
#define mip6_ps_cksum		mip6_ps_hdr.icmp6_cksum
#define mip6_ps_id		mip6_ps_hdr.icmp6_id
#define mip6_ps_reserved	mip6_ps_hdr.icmp6_reserved

#define MIP6_SIZE_PREFIX_SOLICIT sizeof(struct mip6_prefix_solicit)

/*
 * Mobile Prefix Advertisement Message
 */
struct mip6_prefix_advert {
    struct icmp6_hdr	mip6_pa_hdr;
    /* could be followed by options */
};
#define mip6_pa_type		mip6_pa_hdr.icmp6_type
#define mip6_pa_code		mip6_pa_hdr.icmp6_code
#define mip6_pa_cksum		mip6_pa_hdr.icmp6_cksum
#define mip6_pa_id		mip6_pa_hdr.icmp6_id
#define mip6_pa_flags		mip6_pa_hdr.icmp6_data8[2]
#define mip6_pa_reserved	mip6_pa_hdr.icmp6_data8[3]
#define mip6_pa_flags_reserved	mip6_pa_hdr.icmp6_data16[1]
#define ND_PA_FLAG_MANAGED	0x80
#define ND_PA_FLAG_OTHER	0x40

#define MIP6_SIZE_PREFIX_ADVERT sizeof(struct mip6_prefix_advert)


/*
 * Neighbor Discovery protocol constants
 */

#define ND_INFINITY                    0xffffffff      /* infinite lifetime */

#define ND_MAX_ADVREACHABLETIME        3600000         /* milliseconds */
#define ND_MAX_ADVRETRANSTIME          UINT_MAX        /* milliseconds */

#define ND_DEF_ADVMAXHOPLIMIT          64
#define ND_MAX_ADVMAXHOPLIMIT          255

#define ND_MAX_ADVDEFAULTLIFETIME      9000            /* seconds */

#define ND_MIN_MINRTRADVINTVL          3               /* seconds */

#define ND_MIN_MAXRTRADVINTVL          4               /* seconds */
#define ND_DEF_MAXRTRADVINTVL          600             /* seconds */
#define ND_MAX_MAXRTRADVINTVL          1800            /* seconds */

#define ND_DEF_ADVVALIDLIFETIME        2592000		/* seconds */
#define ND_DEF_ADVPREFERREDLIFETIME    604800		/* seconds */

/* Router Constants */
#define ND_MAX_INITIAL_RTR_ADVERT_INTERVAL     16      /* seconds */
#define ND_MAX_INITIAL_RTR_ADVERTISEMENTS      3       /* transmissions */
#define ND_MAX_FINAL_RTR_ADVERTISEMENTS        3       /* transmissions */
#define ND_MIN_DELAY_BETWEEN_RAS               3       /* seconds */
#define ND_MAX_RA_DELAY_TIME                   500     /* milliseconds */

/* Host Constants */
#define ND_MAX_RTR_SOLICITATION_DELAY          1       /* seconds */
#define ND_RTR_SOLICITATION_INTERVAL           4       /* seconds */
#define ND_MAX_RTR_SOLICITATIONS               3       /* transmissions */

/* Node Constants */
#define ND_MAX_MULTICAST_SOLICIT               3          /* transmissions */
#define ND_MAX_UNICAST_SOLICIT                 3          /* transmissions */
#define ND_MAX_ANYCAST_DELAY_TIME              1          /* seconds */
#define ND_MAX_NEIGHBOR_ADVERTISEMENT          3          /* transmissions */
#define ND_REACHABLE_TIME                      30000      /* milliseconds */
#define ND_RETRANS_TIMER                       1000       /* milliseconds */
#define ND_DELAY_FIRST_PROBE_TIME              5          /* seconds */

/* MLD Constants */
#define ICMPV6_MGM_REPORT_INTERVAL	      10000	 /* milliseconds */

#define	ND_SET_IP6CTL(ip6, protocol, payload_length) \
    IN6_SET_IP6CTL_NORMAL(ip6, protocol, 0xFF, payload_length)

#endif /* _IP6_ICMP_H_ */
