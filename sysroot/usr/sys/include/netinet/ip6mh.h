/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: ip6mh.h,v $
 * Revision 1.1.2.2  2003/11/13  22:42:51  Brian_Haley
 * 	Changed all _hdrlen to _len.
 *
 * Revision 1.1.2.1  2003/09/23  22:00:36  Brian_Haley
 * 	Added missing RCS comment.
 * 	[2003/09/08  21:06:01  Brian_Haley]
 *
 * 	Created - Mobile IPv6 API support.
 * 	[2003/08/26  18:59:32  Brian_Haley]
 *
 * $EndLog$
 */
/*
 * @(#)$RCSfile: ip6mh.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 2003/11/13 22:42:51 $
 */

#ifndef _IP6MH_H_
#define	_IP6MH_H_

#include <netinet/in6_machtypes.h>

/***
 *** MOBILITY MESSAGES AND OPTIONS
 ***/

/*
 * Mobility header
 */
struct ip6_mh {
    uint8_t  ip6mh_proto;	/* payload proto */
    uint8_t  ip6mh_len;		/* length in units of 8 octets, excl. 1st 8 */
    uint8_t  ip6mh_type;	/* mobility message type */
    uint8_t  ip6mh_reserved;
    uint16_t ip6mh_cksum;	/* checksum of IPv6 pseudo header and MH */
    /* followed by Mobility Data of variable length */
};

/* Mobility Header Message Types */
#define IP6MH_TYPE_BRR		0x00	/* Binding Refresh Request */
#define IP6MH_TYPE_HOTI		0x01	/* Home Test Init */
#define IP6MH_TYPE_COTI		0x02	/* Care-of Test Init */
#define IP6MH_TYPE_HOT		0x03	/* Home Test */
#define IP6MH_TYPE_COT		0x04	/* Care-of Test */
#define IP6MH_TYPE_BU		0x05	/* Binding Update */
#define IP6MH_TYPE_BACK		0x06	/* Binding Ack */
#define IP6MH_TYPE_BERROR	0x07	/* Binding Error */


/*
 * Binding Refresh Request Message
 */
struct ip6mh_binding_request {
    struct ip6_mh ip6mhbr_hdr;
    uint16_t ip6mbr_reserved;
    /* followed by mobility options */
};


/*
 * Home Test Init (HoTI) Message
 */
struct ip6mh_home_test_init {
    struct ip6_mh ip6mhhti_hdr;
    uint16_t ip6mhhti_reserved;
    uint32_t ip6mhhti_cookie[2];	/* Home Init cookie */
    /* followed by mobility options */
};


/*
 * Care-of Test Init (CoTI) Message
 */
struct ip6mh_careof_test_init {
    struct ip6_mh ip6mhcti_hdr;
    uint16_t ip6mhcti_reserved;
    uint32_t ip6mhcti_cookie[2];	/* Care-of Init cookie */
    /* followed by mobility options */
};


/*
 * Home Test (HoT) Message
 */
struct ip6mh_home_test {
    struct ip6_mh ip6mhht_hdr;
    uint16_t ip6mhht_nonce_index;	/* Home Nonce index */
    uint32_t ip6mhht_cookie[2];		/* Home Init cookie */
    uint32_t ip6mhht_keygen[2];		/* Home Keygen Token */
    /* followed by mobility options */
};

#define ip6mhht_proto	ip6mhht_hdr.ip6mh_proto
#define ip6mhht_len	ip6mhht_hdr.ip6mh_len
#define ip6mhht_type	ip6mhht_hdr.ip6mh_type
#define ip6mhht_cksum	ip6mhht_hdr.ip6mh_cksum


/*
 * Care-of Test (CoT) Message
 */
struct ip6mh_careof_test {
    struct ip6_mh ip6mhct_hdr;
    uint16_t ip6mhct_nonce_index;	/* Care-of Nonce index */
    uint32_t ip6mhct_cookie[2];		/* Care-of Init cookie */
    uint32_t ip6mhct_keygen[2];		/* Care-of Keygen Token */
    /* followed by mobility options */
};

#define ip6mhct_proto	ip6mhct_hdr.ip6mh_proto
#define ip6mhct_len	ip6mhct_hdr.ip6mh_len
#define ip6mhct_type	ip6mhct_hdr.ip6mh_type
#define ip6mhct_cksum	ip6mhct_hdr.ip6mh_cksum


/*
 * Binding Update Message
 *
 * Mobile IPv6 draft, Section 6.1.7: "If no options are present in this
 * message, 4 bytes of padding is necessary and the Header Len field will
 * be set to 1."
 */
struct ip6mh_binding_update {
    struct ip6_mh ip6mhbu_hdr;
    uint16_t ip6mhbu_seqno;
    uint16_t ip6mhbu_flags;
    uint16_t ip6mhbu_lifetime;		/* lifetime, in units of 4 seconds */
    /* followed by sub-options */
};

/* Binding Update Flags, in host byte-order */
#define IP6MH_BU_ACK	0x8000	/* Request a binding ack */
#define IP6MH_BU_HOME	0x4000	/* Home Registration */
#define IP6MH_BU_LLOCAL	0x2000	/* Link-local address compatibility */
#define IP6MH_BU_KEYM	0x1000	/* Key management mobility capability */


/*
 * Binding Acknowledgement Message
 *
 * Mobile IPv6 draft, Section 6.1.8: "If no options are present in this
 * message, 4 bytes of padding is necessary and the Header Len field will
 * be set to 1."
 */
struct ip6mh_binding_ack {
    struct ip6_mh ip6mhba_hdr;
    uint8_t  ip6mhba_status;
    uint8_t  ip6mhba_flags;
    uint16_t ip6mhba_seqno;
    uint16_t ip6mhba_lifetime;		/* lifetime, in units of 4 seconds */
    /* followed by sub-options */
};

#define ip6mhba_proto	ip6mhba_hdr.ip6mh_proto
#define ip6mhba_len	ip6mhba_hdr.ip6mh_len
#define ip6mhba_type	ip6mhba_hdr.ip6mh_type
#define ip6mhba_cksum	ip6mhba_hdr.ip6mh_cksum

/*
 * Binding Acknowledgement Status Codes
 *
 * SUCCESS (0-127)
 * FAILURE (128-255)
 */
#define IP6M_BAS_ACCEPTED	0	/* Binding Update accepted */
#define IP6M_BAS_PRFX_DISCOV	1	/* Accepted but prefix disc necessary */

#define IP6M_BAS_UNSPECIFIED		128	/* Reason unspecified */
#define IP6M_BAS_PROHIBIT		129	/* Administratively prohibited*/
#define IP6M_BAS_INSUFFICIENT		130	/* Insufficient resources */
#define IP6M_BAS_HA_NOT_SUPPORTED	131	/* Home registration not supported */
#define IP6M_BAS_NOT_HOME_SUBNET	132	/* Not home subnet */
#define IP6M_BAS_NOT_HA			133	/* Not home agent for this MN */
#define IP6M_BAS_DAD_FAILED		134	/* DAD failed */
#define IP6M_BAS_SEQNO_BAD		135	/* Sequence # out of window */
#define IP6M_BAS_HOME_NI_EXPIRED	136	/* Expired Home Nonce Index */
#define IP6M_BAS_COA_NI_EXPIRED		137	/* Expired Care-of Nonce Index */
#define IP6M_BAS_NI_EXPIRED		138	/* Expired Nonces */
#define IP6M_BAS_REG_NOT_ALLOWED	139	/* Reg type change disallowed */

/* Binding Acknowledgement Flags */
#define IP6MH_BA_KEYM		0x80	/* Key management mobility capability */


/*
 * Binding Error Message
 */
struct ip6mh_binding_error {
    struct ip6_mh ip6mhbe_hdr;
    uint8_t  ip6mhbe_status;
    uint8_t  ip6mhbe_reserved;
    struct in6_addr ip6mhbe_homeaddr;	/* home address */
    /* followed by mobility options */
};

#define ip6mhbe_proto	ip6mhbe_hdr.ip6mh_proto
#define ip6mhbe_len	ip6mhbe_hdr.ip6mh_len
#define ip6mhbe_type	ip6mhbe_hdr.ip6mh_type
#define ip6mhbe_cksum	ip6mhbe_hdr.ip6mh_cksum

/* Binding Error Status Codes */
#define IP6MH_BES_UNKNOWN_HAO	1	/* Home Address Option w/o a binding */
#define IP6MH_BES_UNKNOWN_MH	2	/* unknown MH type */


/*
 * Mobility Option header
 */
struct ip6mh_opt {
    uint8_t  ip6mhopt_type;	/* mobility message type */
    uint8_t  ip6mhopt_len;	/* length in units of 8 octets, excl. 1st 8 */
};

/* Mobility Option Types */
#define IP6MHOPT_PAD1		0x00	/* Pad 1 */
#define IP6MHOPT_PADN		0x01	/* Pad N */
#define IP6MHOPT_BREFRESH	0x02	/* Binding Refresh Advice */
#define IP6MHOPT_ALTCOA		0x03	/* Alternate COA */
#define IP6MHOPT_NONCEID	0x04	/* Nonce Indices */
#define IP6MHOPT_BAUTH		0x05	/* Binding Authorization data */


/*
 * Binding Refresh Advice mobility option
 */
struct ip6mh_opt_refresh_advice {
    struct ip6mh_opt ip6mora_hdr;
    uint16_t ip6mora_interval;	/* refresh interval */
};

#define ip6mora_type	ip6mora_hdr.ip6mhopt_type
#define ip6mora_len	ip6mora_hdr.ip6mhopt_len


/*
 * Alternate Care-of Address mobility option
 */
struct ip6mh_opt_altcoa {
    struct ip6mh_opt ip6moa_hdr;
    struct in6_addr ip6moa_homeaddr;	/* Alternate Care-of Address */
};

#define ip6moa_type	ip6moa_hdr.ip6mhopt_type
#define ip6moa_len	ip6moa_hdr.ip6mhopt_len


/*
 * Nonce Indices mobility option
 */
struct ip6mh_opt_nonce_index {
    struct ip6mh_opt ip6moni_hdr;
    uint16_t ip6moni_home_index;	/* home nonce index */
    uint16_t ip6moni_careof_index;	/* care-of nonce index */
};

#define ip6moni_type	ip6moni_hdr.ip6mhopt_type
#define ip6moni_len	ip6moni_hdr.ip6mhopt_len


/*
 * Binding Authorization Data mobility option
 */
struct ip6mh_opt_auth_data {
    struct ip6mh_opt ip6moad_hdr;
    /* followed by Authorization Data of variable length */
};

#define ip6moad_type	ip6moad_hdr.ip6mhopt_type
#define ip6moad_len	ip6moad_hdr.ip6mhopt_len


/*
 * Length definitions for above Mobility Header Messages, in units of 8 octets,
 * excluding the first 8 octets.
 */
#define IP6MH_BRR_LEN		0	/* Length of BRR message */
#define IP6MH_HOTI_LEN		1	/* Length of HoTI message */
#define IP6MH_COTI_LEN		1	/* Length of CoTI message */
#define IP6MH_HOT_LEN		2	/* Length of HoT message */
#define IP6MH_COT_LEN		2	/* Length of CoT message */
#define IP6MH_BU_LEN		1	/* Length of BU message */
#define IP6MH_BA_LEN		1 	/* Length of BA message */
#define IP6MH_BE_LEN		2	/* Length of BE message */

/*
 * Length definitions for above Mobility Options, in octets
 */
#define IP6MHOPT_BRA_LEN	2	/* Length of Binding Refresh Advice */
#define IP6MHOPT_ALTCOA_LEN	16	/* Length of Alternate COA option */
#define IP6MHOPT_NI_LEN		4	/* Length of Nonce Indices option */

/*
 * Length definitions for Return Routability
 */
#define IP6MHOPT_RR_AUTHDATALEN	12	/* Authenticator length for RR */

#endif /* _IP6MH_H_ */
