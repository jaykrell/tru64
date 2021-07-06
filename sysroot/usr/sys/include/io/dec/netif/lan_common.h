/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: lan_common.h,v $
 * Revision 1.1.45.1  2002/10/17  17:43:25  Chris_Houser
 * 	Added note to stop increasing the LANDDI_VERSION numbers.
 * 	Defined LANDDI_TAGFRAME to indicate new LAN_MEDIA_COMPAT,
 * 	LAN_OPTION_PRESENT, and other tagged-frame-related features.
 * 	[OSF_QAR 93955]
 *
 * Revision 1.1.33.3  2002/07/10  18:35:37  Paul_Moore
 * 	added if_options, LAN_MEDIA_COMPAT(), and LAN_OPTION_PRESENT()
 * 	to support en/disabling misc driver options
 *
 * Revision 1.1.33.2  2002/01/30  18:37:48  Chris_Houser
 * 	Bumped LANDDI_VERSION_REV to 10 and defined
 * 	LANDDI_AUTONEG_ATTR to indicate the new
 * 	autoneg_enable hwm attribute (NET_AUTONEG_NDX).
 * 	[OSF_QAR 89489]
 *
 * Revision 1.1.33.1  2001/09/13  13:35:35  Chris_Houser
 * 	Bumped LANDDI_VERSION_REV to 9, NET_EHM_VERSION_ID
 * 	to 2, and defined LANDDI_MSSLIST to reflect new
 * 	msslist member in struct net_hw_mgmt.  This msslist
 * 	member is used by lan_ehm_append_mss().
 *
 * Revision 1.1.24.1  2001/03/07  21:16:39  Julie_Dewandel
 * 	Bumped LANDDI_VERSION_REV to 8 to reflect the new linkstate
 * 	hardware management attribute.
 *
 * Revision 1.1.20.5  2000/06/21  16:48:57  Julie_Dewandel
 * 	Updated extended counter macros as part of fix for
 * 	cluster failover regression [see OSF_QAR 80560].
 *
 * Revision 1.1.20.4  2000/05/04  12:30:00  Julie_Dewandel
 * 	Modified calling args to the extended counter macros
 *
 * Revision 1.1.20.3  2000/01/14  20:31:59  Julie_Dewandel
 * 	Bumped LANDDI_VERSION_REV to 7 to indicate NUMA functionality for
 * 	hwind drivers.
 *
 * Revision 1.1.20.2  1999/12/14  17:49:05  Aron_Griffis
 * 	Bumped LANDDI_VERSION_REV up to 6 since it's 5 in pthwindos
 * 	LANDDI_VERSION_MINOR was changed accidentally to 2; dropped it back
 * 	to 0
 *
 * Revision 1.1.20.1  1999/11/02  20:33:29  Aron_Griffis
 * 	Added macros to support extended counters
 * 	Incremented LANDDI_VERSION_REV to 1 to reflect interface change
 *
 * Revision 1.1.14.7  1999/05/17  16:23:24  James_Smart
 * 	Add Define's for the LAN DDI level supported
 * 	   LANDDI_VERSION_MAJOR
 * 	   LANDDI_VERSION_MINOR
 * 	   LANDDI_VERSION_REV
 * 	[1999/04/28  20:51:05  James_Smart]
 *
 * Revision 1.1.14.6  1999/04/02  21:45:09  Julie_Dewandel
 * 	Expanded Enhanced Hardware Management structure for
 * 	future development purposes.
 * 	[1999/04/02  20:49:58  Julie_Dewandel]
 * 
 * Revision 1.1.14.5  1998/04/15  19:33:41  Julie_Dewandel
 * 	Added function prototype definitions for global empty
 * 	functions used by token ring source routing module.
 * 	[1998/04/14  13:35:42  Julie_Dewandel]
 * 
 * Revision 1.1.14.4  1998/02/24  17:39:04  Julie_Dewandel
 * 	Revision 1.1.15.2  1998/02/10  15:43:10  Julie_Dewandel
 * 	Added a handle to the EHM data structure so that we
 * 	can easily unregister our adapter later.
 * 	Added CLEAR_LAN_COUNTERS macro to initialize
 * 	network driver counters.
 * 	[1998/02/13  19:32:01  Julie_Dewandel]
 * 
 * Revision 1.1.14.3  1997/07/28  11:48:10  Julie_Dewandel
 * 	Added Enhanced Hardware Management support.
 * 	[1997/07/24  14:02:45  Julie_Dewandel]
 * 
 * Revision 1.1.14.2  1997/03/20  19:14:44  Julie_Dewandel
 * 	Added prototypes for functions exported by lan_common.c.
 * 	Added data definition for the structure required by the
 * 	generic network configure routines.
 * 	[1997/03/13  21:44:19  Julie_Dewandel]
 * 
 * Revision 1.1.12.3  1996/10/03  13:44:21  Kirt_Gillum
 * 	1) Remove ifnet exports (not supported yet).
 * 	2) Correctly specify macro parameter substitution for
 * 	   the counter macros.
 * 	[1996/09/20  15:12:28  Kirt_Gillum]
 * 
 * Revision 1.1.12.2  1996/09/05  19:15:07  Thomas_Blinn
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rTADPOLE **
 * 		** Ancestor revision:	1.1.10.2 **
 * 		** Merge revision:	1.1.8.4 **
 * 	 	** End **
 * 	propagating tadpole
 * 	[1996/08/31  14:28:21  Thomas_Blinn]
 * 
 * Revision 1.1.8.4  1996/06/30  17:15:35  Thomas_Blinn
 * 	Fix problems introduced by merge -- duplicate lan_media
 * 	structure definition.
 * 	Make #ifdef KERNEL be #ifdef _KERNEL throughout
 * 	[1996/06/30  17:14:26  Thomas_Blinn]
 * 
 * Revision 1.1.8.3  1996/06/29  15:03:06  Thomas_Blinn
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.10.2 **
 * 		** Merge revision:	1.1.8.2 **
 * 	 	** End **
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rPTAOS_BL2 **
 * 		** Ancestor revision:	1.1 **
 * 		** Merge revision:	1.1.10.2 **
 * 	 	** End **
 * 	[1996/06/29  14:43:16  Thomas_Blinn]
 * 
 * Revision 1.1.10.2  1996/06/14  17:46:16  Rajul_Shah
 * 	Merge from MP2OS.
 * 	[1996/06/11  19:35:16  Rajul_Shah]
 * 
 * Revision 1.1.8.2  1996/05/30  19:08:21  Kirt_Gillum
 * 	Initial creation.  LAN driver common interface definitions.
 * 	[1996/05/30  18:45:31  Kirt_Gillum]
 * 
 * Revision 1.1.6.2  1996/05/09  20:40:29  Rajul_Shah
 * 	Initial creation --- original author: Kirt Gillum.
 * 	[1996/05/09  19:05:15  Rajul_Shah]
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: lan_common.h,v $ $Revision: 1.1.45.1 $ (DEC) $Date: 2002/10/17 17:43:25 $
 */

#ifndef _IO_DEC_NETIF_LAN_COMMON_
#define _IO_DEC_NETIF_LAN_COMMON_

#ifdef __cplusplus
extern "C" { 
#endif  

#include <kern/lock.h>
#include <machine/machlimits.h>

#if defined(_KERNEL)
#include <sys/sysconfig.h>
#include <net/if.h>
#include <ksm/ksm.h>
#include <io/common/hwc_reg.h>
#include <io/common/hwc_events.h>
#endif

/*
 * NOTE: LANDDI_VERSION_* macros should not be changed anymore, and we
 * may in fact phase them out of use completely at some point.
 * Instead, individual LANDDI_* feature names should be defined when
 * individual API changes are made.
 */
#define LANDDI_VERSION_MAJOR        5
#define LANDDI_VERSION_MINOR        0
#define LANDDI_VERSION_REV         10

/* Interface revision names */
#define ESTAT_EXTENDED_PRESENT
#define FSTAT_EXTENDED_PRESENT
#define LANDDI_NUMA
#define LANDDI_LINKSTATE
#define LANDDI_MSSLIST
#define LANDDI_AUTONEG_ATTR
#define LANDDI_TAGFRAME

/*
 * Definitions/macros that are common to all LAN interface drivers.
 */

/*
 * M E D I A    D E F I N I T I O N S 
 * ==================================
 */

/*
 * Medium structure to put in driver's softc structure.
 */
struct lan_media {
    unsigned long lan_media_mode; /* see media_types enum for values */
    unsigned long lan_media_state;/* valid if media_mode = autosense */
    unsigned long lan_media;	  /* valid if media_mode = determined */
};

/*
 * Media definitions.  For drivers that support them.  Most good hardware 
 * determines media automagically, but there are a few implementations
 * that do not figure it out.
 */
enum media_types {
      LAN_MEDIA_UTP=1,			/* Unshielded Twisted Pair */
      LAN_MEDIA_BNC,			/* Thinwire */
      LAN_MEDIA_STP,			/* Shielded Twisted Pair */
      LAN_MEDIA_FIBER,			/* Any Fiber based media */
      LAN_MEDIA_AUI,			/* Attachment Unit Interface */
      LAN_MEDIA_4PAIR,			/* Four Pair */
      LAN_MEDIA_MAX,
      LAN_MEDIA_ULIM=0xFF               /* media_type upper limit */
};

/*
 * Interface (i.e. driver) options, used in the ifchar.ifc_extra_options
 * field.  Currently this piggybacks on top of the ifc_media_type field and
 * is designed in such a way as to not interfere with the values there.
 * Drivers that are unaware of these options will simply return an error.
 */
enum if_options {
      LAN_OPTION_LLIM=0x000000ff,       /* if_option lower limit */
      LAN_OPTION_TAGFRAME=0x00000100,   /* tagged frames */
      /* add more options here */
      LAN_OPTION_ULIM=0x1fffffff,       /* if_option upper limit */
      LAN_OPTION_DIS=0x20000000,        /* disable specified options */
      LAN_OPTION_ENB=0x40000000,        /* enable specified options */
      LAN_OPTION_VALIDMASK=0x7fffffff   /* if valid, highest bit must be 0 */
};
/* macro used to create media_type values that are a full 32 bits */
#define LAN_MEDIA_COMPAT(x) ((x & LAN_MEDIA_ULIM) == LAN_MEDIA_ULIM? \
                             0xffffffff:                             \
                             (0 | (x & LAN_MEDIA_ULIM)))
/* macro used to determine if option processing needs to happen */
#define LAN_OPTION_PRESENT(x) ((x & ~LAN_OPTION_LLIM) > 0)

/*
 * Media modes.  These are the same as media_types except for the autosense
 * case.
 */
enum media_modes {
      LAN_MODE_AUTOSENSE=0xFF
};

/*
 * Autosense mode definitions.
 */
enum autosense_types {
      LAN_AUTOSENSE_ENABLE=1,
      LAN_AUTOSENSE_DISABLE=2
};

/*
 * Full duplex types.
 */
enum fdx_types {
      LAN_FDX_ENABLE=1,
      LAN_FDX_DISABLE=2
};

/* 
 * Media STATE definitions.  This is used when media mode is autosensing.
 */
#define LAN_MEDIA_STATE_SENSING		1 	/* Currently auto sensing */
#define LAN_MEDIA_STATE_DETERMINED 	0 	/* Media is determined */

/*
 * M U L T I C A S T    S U P P O R T
 * ==================================
 * 
 * Important NOTE:  The broadcast address should always be enabled 
 * on LAN Device Drivers.   This will not be a requirement if IP changes
 * to actually enable the broadcast address by itself.
 */

/*
 * The number of multicasts to support.  This is a ballpark figure 
 * with, at this time, no demand for this number of multicasts.
 */
#define LAN_NMULTI 512

#if defined(_KERNEL)

/*
 * The multicast tracking structure.  This is included in a LAN driver's
 * softc structure if they wish to use the common multicast support.
 */
struct lan_multi {
    struct {			/* The table of multicast addresses */
	unsigned char maddr[6];
	unsigned short muse;
    } lan_mtable[LAN_NMULTI];
    unsigned int lan_nmulti;	/* The number of active entries */
    unsigned int lan_index;	/* Next available index */
};

#endif /* _KERNEL */

/*
 * Return Status for common routines and filtering macros.
 */
enum lan_multi_status {
      LAN_MULTI_FAILED,
      LAN_MULTI_FOUND,
      LAN_MULTI_NOT_FOUND,
      LAN_MULTI_CHANGED,
      LAN_MULTI_NOT_CHANGED
};

#if defined(_KERNEL)

/*
 * LAN_FIND_MULTI
 * 	For devices which don't perform perfect filtering, the following
 * 	macro will check to see if a given multicast is enabled on the given 
 * 	softc.  This macro is also used by the common routines.
 * 
 * Arguments:
 * 	lm_p	lan multicast table pointer
 * 	mc_p	multicast to check
 * 	ind_v	index variable
 * 	stat_v	status variable
 * 
 * Return Values:
 * 	stat_v	LAN_MULTI_FOUND if found, otherwise LAN_MULTI_NOT_FOUND
 * 	ind_v	table index of matching multicast table
 */
#define LAN_FIND_MULTI(lm_p, mc_p, ind_v, stat_v) \
	for ((ind_v) = 0; (ind_v)<(lm_p)->lan_index; (ind_v)++) \
	   if (bcmp((lm_p)->lan_mtable[(ind_v)].maddr, (mc_p), 6) == 0) \
	      break; \
	if ((ind_v) == (lm_p)->lan_index) \
	   (stat_v) = LAN_MULTI_NOT_FOUND; \
	else \
	   (stat_v) = LAN_MULTI_FOUND

/*
 * LAN_GET_MULTI
 * 	Returns a pointer to the next enabled multicast address.  To use
 * 	this to go through the multicast list, you'd do something like the
 * 	following
 * 
 * 	int i, j;
 * 	unsigned char *maddr;
 * 
 * 	j = 0;
 * 	for (i=0; i<lmt->lan_nmulti; i++) {
 *         LAN_GET_MULTI(lmt, maddr, j);
 *         if (maddr != NULL)    ---   maddr should never be null in this case
 *           printf("Multicast %s enabled\n", ether_sprintf(maddr));
 *      }
 * 
 * Arguments:
 * 	lmt	pointer to the lan multicast table.
 * 	mc_p	pointer to hold the multicast address pointer
 * 	ind_v	index value 
 *
 * Return Values:
 * 
 */
#define LAN_GET_MULTI(lm_p, mc_p, ind_v) \
	for (; (ind_v) < (lm_p)->lan_index; (ind_v)++) \
	  if ((lm_p)->lan_mtable[(ind_v)].muse != 0) \
	    break; \
	if ((ind_v) >= (lm_p)->lan_index) \
	   (mc_p) = NULL; \
	else { \
	   (mc_p) = (lm_p)->lan_mtable[(ind_v)].maddr; \
	   (ind_v)++; \
	}

/*
 * C O U N T E R     S U P P O R T
 * ===============================
 */

/*
 * ifnet and ctrblk counter manipulation.   The ctrblk counters are only 32 
 * bit counters so we have to watch for wrap.   All take ifp & softc pointer 
 * and size as input.
 * 
 * These macros increment the packet (block) count, and then adjust the
 * byte count.
 */
#define ADD_XMIT_PACKET(if_p, sc_p, siz_v) \
	(if_p)->if_opackets++; \
	if ((sc_p)->ctrblk.est_bloksent != 0xffffffff) \
	   (sc_p)->ctrblk.est_bloksent++; \
	if (((sc_p)->ctrblk.est_bytesent + (siz_v)) >  \
	    ((sc_p)->ctrblk.est_bytesent)) \
	   (sc_p)->ctrblk.est_bytesent += (siz_v); \
	else \
	   (sc_p)->ctrblk.est_bytesent = 0xffffffff
#define ADD_XMIT_MPACKET(if_p, sc_p, siz_v) \
	if ((sc_p)->ctrblk.est_mbloksent != 0xffffffff) \
	   (sc_p)->ctrblk.est_mbloksent++; \
	if (((sc_p)->ctrblk.est_mbytesent + (siz_v)) >  \
	    ((sc_p)->ctrblk.est_mbytesent)) \
	   (sc_p)->ctrblk.est_mbytesent += (siz_v); \
	else \
	   (sc_p)->ctrblk.est_mbytesent = 0xffffffff
#define ADD_RECV_PACKET(if_p, sc_p, siz_v) \
	(if_p)->if_ipackets++;\
	if ((sc_p)->ctrblk.est_blokrcvd != 0xffffffff) \
	   (sc_p)->ctrblk.est_blokrcvd++; \
	if (((sc_p)->ctrblk.est_bytercvd + (siz_v)) >  \
	    ((sc_p)->ctrblk.est_bytercvd)) \
	   (sc_p)->ctrblk.est_bytercvd += (siz_v); \
	else \
	   (sc_p)->ctrblk.est_bytercvd = 0xffffffff
#define ADD_RECV_MPACKET(if_p, sc_p, siz_v) \
	if ((sc_p)->ctrblk.est_mblokrcvd != 0xffffffff) \
	   (sc_p)->ctrblk.est_mblokrcvd++; \
	if (((sc_p)->ctrblk.est_mbytercvd + (siz_v)) >  \
	    ((sc_p)->ctrblk.est_mbytercvd)) \
	   (sc_p)->ctrblk.est_mbytercvd += (siz_v); \
	else \
	   (sc_p)->ctrblk.est_mbytercvd = 0xffffffff
#define CLEAR_LAN_COUNTERS(ed_p)	\
	bzero (&(ed_p)->ess_ctrblk, sizeof(struct estat)); \
	(ed_p)->ess_missed = 0;

/* 
 * Extended counter manipulation.  These counters are 64 bit counters
 * so we ignore wrap.  All take counter block pointer and size as input.
 *
 * The ifnet counters are split between if_ethersubr.c and here,
 * although the explanation for this is elusive at best.  At this
 * point, the behavior must be preserved for the sake of binary
 * compatibility and third-party drivers.
 *
 * The driver maintains its own set of counters for packets and bytes
 * sent and received.  At first this appears to be redundant work, but
 * it is critical that the driver keep its own copy of these counters
 * and return the copy when presented with the SIOCRDCTRS or SIOCRDZCTRS
 * IOCTLs.  This is because the ifnet counters can be changed by other
 * entities and would then not accurately reflect what is happening at 
 * the driver layer.
 *
 * FILL_ESTAT_EXT fills an estat_extended struct based on the 
 * estat_extended ctrblk.  It is for use when responding to an ioctl.
 *
 * AUTOLATCH copies src to dest, latching if necessary.  It works for
 * all combinations of u_long, u_int, and u_short, latching only if
 * necessary.  There is no penalty for using this macro over a
 * straight assign due to the sizeof comparison, which is done at
 * compile-time.
 *
 * FILL_ESTAT fills an estat struct based on the estat_extended ctrblk.  
 * It is for use when responding to an ioctl for the old estat counters.  
 * It zeros the target estat first. est_latecoll, est_unaligned, and 
 * est_symbolerror from estat_extended are not copied into estat since 
 * they have no equivalents there.  
 *
 * See http://www.eskimo.com/~scs/C-faq/q10.4.html for explanation of
 * "do { ... } while(0)".
 */

#define ADD_XMIT_PACKET_EXT(ctrblk_p, siz_v) do { \
	(ctrblk_p)->est_bloksent++; \
	(ctrblk_p)->est_bytesent += (siz_v); \
        } while(0)
#define ADD_RECV_PACKET_EXT(ctrblk_p, siz_v) do { \
        (ctrblk_p)->est_blokrcvd++; \
        (ctrblk_p)->est_bytercvd += (siz_v); \
        } while(0)
#define ADD_XMIT_MPACKET_EXT(ctrblk_p, siz_v) do { \
        (ctrblk_p)->est_mbloksent++; \
        (ctrblk_p)->est_mbytesent += (siz_v); \
        } while(0)
#define ADD_RECV_MPACKET_EXT(ctrblk_p, siz_v) do { \
        (ctrblk_p)->est_mblokrcvd++; \
        (ctrblk_p)->est_mbytercvd += (siz_v); \
        } while(0)
#define CLEAR_LAN_COUNTERS_EXT(ctrblk_p, ed_p) do { \
        bzero((ctrblk_p), sizeof(struct estat_extended)); \
        (ed_p)->ess_missed = 0; \
        } while(0)
#define FILL_ESTAT_EXT(estat_ext_p, ctrblk_p) do { \
        *(estat_ext_p) = *(ctrblk_p); \
        } while(0)
#define AUTOLATCH(dest, src) do { \
        if (sizeof(src) <= sizeof(dest)) \
            dest = src; \
        else if (sizeof(dest) == 4) \
            dest = (src < UINT_MAX) ? src : UINT_MAX; \
        else /* if (sizeof(dest) == 2) */ \
            dest = (src < USHRT_MAX) ? src : USHRT_MAX; \
        } while(0)
#define FILL_ESTAT(estat_p, ctrblk_p) do { \
        /* zero the target estat */ \
        bzero((estat_p), sizeof(struct estat)); \
        AUTOLATCH((estat_p)->est_bloksent, (ctrblk_p)->est_bloksent); \
        AUTOLATCH((estat_p)->est_bytesent, (ctrblk_p)->est_bytesent); \
        AUTOLATCH((estat_p)->est_blokrcvd, (ctrblk_p)->est_blokrcvd); \
        AUTOLATCH((estat_p)->est_bytercvd, (ctrblk_p)->est_bytercvd); \
        AUTOLATCH((estat_p)->est_mbloksent, (ctrblk_p)->est_mbloksent); \
        AUTOLATCH((estat_p)->est_mblokrcvd, (ctrblk_p)->est_mblokrcvd); \
        AUTOLATCH((estat_p)->est_seconds, (ctrblk_p)->est_seconds); \
        AUTOLATCH((estat_p)->est_mbytesent, (ctrblk_p)->est_mbytesent); \
        AUTOLATCH((estat_p)->est_deferred, (ctrblk_p)->est_deferred); \
        AUTOLATCH((estat_p)->est_single, (ctrblk_p)->est_single); \
        AUTOLATCH((estat_p)->est_multiple, (ctrblk_p)->est_multiple); \
        AUTOLATCH((estat_p)->est_collis, (ctrblk_p)->est_collis); \
        AUTOLATCH((estat_p)->est_unrecog, (ctrblk_p)->est_unrecog); \
        AUTOLATCH((estat_p)->est_overrun, (ctrblk_p)->est_overrun); \
        AUTOLATCH((estat_p)->est_sysbuf, (ctrblk_p)->est_sysbuf); \
        AUTOLATCH((estat_p)->est_userbuf, (ctrblk_p)->est_userbuf); \
        ((ctrblk_p)->est_excesscoll) && ((estat_p)->est_sendfail_bm |= 1); \
        ((ctrblk_p)->est_carrierfail) && ((estat_p)->est_sendfail_bm |= 2); \
        ((ctrblk_p)->est_shortcirc) && ((estat_p)->est_sendfail_bm |= 4); \
        ((ctrblk_p)->est_opencirc) && ((estat_p)->est_sendfail_bm |= 8); \
        ((ctrblk_p)->est_sndlong) && ((estat_p)->est_sendfail_bm |= 16); \
        ((ctrblk_p)->est_collis) && ((estat_p)->est_sendfail_bm |= 32); \
        AUTOLATCH((estat_p)->est_sendfail, (ctrblk_p)->est_sendfail); \
        AUTOLATCH((estat_p)->est_collis, (ctrblk_p)->est_collis); \
        AUTOLATCH((estat_p)->est_mbytercvd, (ctrblk_p)->est_mbytercvd); \
        ((ctrblk_p)->est_fcsfail) && ((estat_p)->est_recvfail_bm |= 1); \
        ((ctrblk_p)->est_badframe) && ((estat_p)->est_recvfail_bm |= 2); \
        ((ctrblk_p)->est_longframe || (ctrblk_p)->est_shortframe) \
            && ((estat_p)->est_recvfail_bm |= 4); \
        AUTOLATCH((estat_p)->est_recvfail, (ctrblk_p)->est_recvfail); \
        } while(0)

/*
 * C O N F I G U R A T I O N   S U P P O R T
 * =========================================
 */

/*
 * The following data structure contains data maintained by each
 * device driver.  This structure is a convenient way to pass
 * relevant data between the various generic configure and callback 
 * functions present in the lan_common.c
 *  
 * All members are supplied by the device driver except for 'cfg_state'
 * which will be filled in by the generic lan_configure routine.
 */

struct lan_config_data {
    int 	   version_id;		/* version # of this data structure */
    int		   cfg_state;		/* how the driver was configured */
    struct driver *info;		/* driver's "driver" structure */
    int		  *config_count;	/* # of instances successfully 
					   configured */
};

#define LAN_CONFIG_VERSION_ID	1	/* current version of the lan_data
					   structure */


/*
 * H A R D W A R E   M A N A G E M E N T   S U P P O R T
 * =====================================================
 */

/*
 * Define the index values for the common network attributes.
 * 
 * If adding a new attribute, add it to the end of the list,
 * update NET_NUM_ATTR, add a structure element to the 
 * net_attribute_values structure below, and add the definition 
 * to the hwc_net_attributes structure in lan_common.c.  The
 * appropriate pointer will also need to be set up in the 
 * lan_setup_table routine in lan_common.c.
 */

#define NET_NAME_NDX	0	/* Name */
#define NET_CAT_NDX	1	/* Category */
#define NET_SUBCAT_NDX	2	/* Sub-category */
#define NET_MODEL_NDX	3	/* Model Name */
#define NET_HWREV_NDX	4	/* Hardware Revision */
#define NET_FWREV_NDX	5	/* Firmware Revision */
#define NET_MAC_NDX	6	/* MAC Address */
#define NET_MTU_NDX	7	/* Maximum Transmission Unit */
#define NET_SPEED_NDX	8	/* Megabits Per Second Rate */
#define NET_METHOD_NDX	9	/* Media Selection Method */
#define NET_MEDIA_NDX	10	/* Media Type Selected */
#define NET_LOOP_NDX	11	/* Loopback Status */
#define NET_PROMISC_NDX	12	/* Promiscuous Mode Status */
#define NET_FDX_NDX	13	/* Full Duplex Status */
#define NET_MCLIST_NDX	14	/* Multicast Address List */
#define NET_IFNDX_NDX	15	/* Ifnet Index */
#define NET_LINK_NDX	16	/* Link State Index */
#define NET_AUTONEG_NDX	17	/* Auto-negotiate enabled */

#define NET_NUM_ATTR	18	/* Total number of attributes */

/*
 * Size in bytes of attributes which are string values
 */

#define NET_SZ_NAME	8	/* Name */
#define NET_SZ_CAT	8	/* Category */
#define NET_SZ_SUBCAT	16	/* Sub-category */
#define NET_SZ_MODEL	16	/* Model Name */
#define NET_SZ_HWREV	16	/* Hardware Revision */
#define NET_SZ_FWREV	16	/* Firmware Revision */
#define NET_SZ_MAC	18	/* MAC Address */
#define NET_SZ_METHOD	32	/* Media Selection Method */
#define NET_SZ_MEDIA	32	/* Media Type Selected */
#define NET_SZ_MCLIST	288	/* Multicast Address List */
#define NET_SZ_LINK	8	/* Link State */

/*
 * Media Speed in Megabits Per Second (for the media_speed attribute)
 */

#define NET_SPEED_10MB	10	/* Ethernet */
#define NET_SPEED_100MB	100	/* Fast Ethernet, FDDI */
#define NET_SPEED_4MB	4	/* Token Ring */
#define NET_SPEED_16MB	16	/* Token Ring */
#define NET_SPEED_155MB	155	/* ATM - OTTO/OPPO */
#define NET_SPEED_622MB	622	/* ATM - DART */

/* 
 * The following data structure should be included by all network
 * drivers as part of their softc structure.  It contains everything
 * needed for hardware management purposes:
 *
 * version_id
 *	An identifier which tells what rev of the data structure is
 *	being used.  If this data structure is changed, the 
 *	NET_EHM_VERSION_ID field should be incremented.
 *
 * current_val
 *	A table allocated by lan_ehm_init containing pointers to the
 *	current values for all network attributes.
 *
 * default_val
 *	A table allocated by lan_ehm_init containing pointers to the
 *	default values for all network attributes.  In general, the 
 *      default values and current values will be the same, unless 
 *      someone modifies an attribute value through the hardware 
 *      management support interface or via an IOCTL call into the driver.  
 *
 * commands
 *	This is a pointer to an array of commands supported by the
 *	network adapter.  For the initial release, none of the network
 *	drivers support any commands.
 * 
 * support_rtn
 *	This is a special routine which can be called to perform any
 *	of the commands listed in the commands array (above).
 *
 * mss
 *	The management support structure allocated by lan_register_adapter.
 *	This data structure is registered with the hardware management
 *	facility and contains pointers to all the above tables plus other
 *	information needed by the facility.
 *
 * handle
 *	Handle returned by hardware registration function.
 *
 * reserved
 *	Reserved for future use
 */
struct net_hw_mgmt {
    int  	version_id;
    void 	**current_val;
    void 	**default_val;
    CMD_ELEM 	*commands;
    int 	(*support_rtn)();
    MSS  	*mss;		
    void	*handle;
    void	*msslist;
    void	*reserved[7];
};

#define NET_EHM_VERSION_ID	2

/*
 * The following data structure shows the layout of the storage area
 * for the attribute values (pointed to by members of either the
 * "current_val" or "default_val" tables).  It is used to get the 
 * proper alignment of data items (especially the integer ones) when
 * initializing all the pointers in the aforementioned tables.
 *
 * One could more easily reference all the attribute items by doing 
 * the following line of code:
 *
 *	values = (struct net_attribute_values *) sc->ehm.current_val[0];
 *	printf("model name is %s and it is a %s controller\n",
 *		values->model, values->sub_category);
 *	...etc...
 */
 
struct net_attribute_values {
    char	name[NET_SZ_NAME];
    char	category[NET_SZ_CAT];
    char	sub_category[NET_SZ_SUBCAT];
    char	model[NET_SZ_MODEL];
    char	hardware_rev[NET_SZ_HWREV];
    char	firmware_rev[NET_SZ_FWREV];
    char	MAC_address[NET_SZ_MAC];
    uint	MTU_size;
    uint	media_speed;
    char	selection_method[NET_SZ_METHOD];
    char	media_type[NET_SZ_MEDIA];
    uint	loopback_mode;
    uint	promiscuous_mode;
    uint	full_duplex;
    char	mc_addr_list[NET_SZ_MCLIST];
    uint	if_number;
    char	linkstate[NET_SZ_LINK];
    uint	autoneg_enable;
};



/*
 * E X T E R N S   /    P R O T O T Y P E S
 * ========================================
 */

extern char *lan_media_strings_10[LAN_MEDIA_MAX];
extern char *lan_media_strings[LAN_MEDIA_MAX];
extern int lan_common_version;

extern char *net_subcat_ether;
extern char *net_subcat_fddi;
extern char *net_subcat_tokenring;
extern char *net_subcat_atm;

extern char *net_link_unknown;
extern char *net_link_up;
extern char *net_link_down;

extern char *net_method_automatic;
extern char *net_method_jumpers;
extern char *net_method_console;
extern char *net_method_ECU;
extern char *net_method_ECU_and_jumpers;
extern char *net_method_SRM_and_jumpers;

/*
 *  The following functions are defined in lan_common.c and are
 *  exported for the use of the network drivers.
 */

#if defined(_USE_KERNEL_PROTOS)
int	lan_common_configure(cfg_op_t, cfg_attr_t *, size_t, cfg_attr_t *, 
			     size_t);
void 	lan_zer_multi(struct lan_multi *);
int  	lan_add_multi(struct lan_multi *, unsigned char *);
int  	lan_del_multi(struct lan_multi *, unsigned char *);
void  	lan_build_mclist(unsigned char *, int, struct lan_multi *);
int	lan_configure (cfg_op_t, struct lan_config_data *);
int	lan_create_controller (struct lan_config_data *);
void 	lan_ehm_init (struct net_hw_mgmt *, int);
void 	lan_set_attribute (void **, int, void *);
void 	lan_set_common_attributes (void **, struct ether_driver *);
void 	lan_ehm_free (struct net_hw_mgmt *);
void	lan_register_adapter (struct net_hw_mgmt *, struct controller *);

/* empty functions for source routing module */
void 	nullvoid(void);
int 	nullint(void);
int 	sr_ioctl_nulldev(void);


#endif

#endif /* _KERNEL */

#ifdef __cplusplus
}          
#endif                  

#endif /* ifndef _IO_DEC_NETIF_LAN_COMMON_ */
