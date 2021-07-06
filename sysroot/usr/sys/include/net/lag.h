/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: lag.h,v $
 * Revision 1.1.19.2  2006/03/18  00:29:30  Terrence_Harple
 * 	Added support for lag interfaces on the cluster LAN
 * 	interconnect. Added #ifndef NIFF_EVENT so that including both
 * 	netrain.h and lag.h compiles. As well as defines for cluster
 * 	channel weighting distribution algorithm.
 *
 * Revision 1.1.19.1  2004/09/10  16:21:56  Dan_Vuong
 *      Added ls_default_lag_macaddr field to the lag_softc structure.
 *      to allow netrain to work on lag.
 *      This fixes QAR 95383.
 *
 * Revision 1.1.14.1  2002/05/24  16:04:00  Jack_McCann
 * 	Merge rev 1.1.8.3 from v51asupportos bl3 to wcalphaos.
 * 	Change ap_hwid type from u_int to ulong (part of QAR 93600 fix).
 *
 * Revision 1.1.8.3  2002/04/25  21:23:33  Jack_McCann
 * 	Add ap_flags field to aggport structure.
 * 	Add LAG_AP_F_ACTIVE flag.
 * 	Remove "IEEE 802.3ad" from LAG_DESCR since we don't yet do 802.3ad.
 * 	Add kernel function prototypes.
 * 	Add lcc_unit field to lag_cfg_create structure.
 *
 * Revision 1.1.8.2  2002/01/28  22:32:13  Jack_McCann
 * 	Add distribution type info.  Add ap_port_if_flags.
 *
 * Revision 1.1.8.1  2001/09/24  21:03:23  Rod_Payne
 * 	Include lan_common.h and devdriver.h to synchronize if_ethersubr's view
 * 	of the lag_softc structure.
 *
 * Revision 1.1.3.3  2001/05/18  17:12:37  Rod_Payne
 * 	Added ctrblk to aggport structure (i.e. per-port counter block)
 *
 * Revision 1.1.3.2  2001/03/09  13:48:31  Rod_Payne
 * 	Add ap_hwid for failure detection.
 *
 * Revision 1.1.3.1  2000/11/09  20:31:10  Rod_Payne
 * 	Initial Branch Revision
 *
 * $EndLog$
 */
/*
 * @(#)$RCSfile: lag.h,v $ $Revision: 1.1.19.2 $ (DEC) $Date: 2006/03/18 00:29:30 $
 */

/*
 * NOTE: The data structures and APIs defined in this file are reserved for use by 
 *	 the operating system, and may be subject to change without notice.
 */


#ifndef _LAG_H
#define _LAG_H

typedef unsigned short lag_key_t;       /* lag keys are 16-bit identifiers */

#ifdef _KERNEL
#include <net/net_globals.h>
#include <netinet/in.h>
#include <net/if.h>
#include <netinet/if_ether.h>
#include <net/ether_driver.h>
#include <kern/thread.h>
#include <evm/evm.h>			/* Event Manager Definitions */
#include <evm/kevm.h>			/* Kernel Event Manager Definitions */
#include <sys/bitypes.h>

#include <io/common/devdriver.h>
#include <io/dec/netif/lan_common.h>

/*
 * Type for Counter values
 */
typedef unsigned long lag_counter_t;

/*
 * Type for Time values
 */
typedef unsigned long lag_time_t;

/*
 * Link Aggregation Control - Receive machine states
 */

typedef enum {
	LAC_RX_STATE_CURRENT,
	LAC_RX_STATE_EXPIRED,
	LAC_RX_STATE_DEFAULTED,
	LAC_RX_STATE_INITIALIZE,
	LAC_RX_STATE_LACPDISABLED,
	LAC_RX_STATE_PORTDISABLED
} lac_rx_state_t;

/*
 * Link Aggregation Control - Mux machine states
 */

typedef enum {
	LAC_MUX_STATE_DETACHED,
	LAC_MUX_STATE_WAITING,
	LAC_MUX_STATE_ATTACHED,
	LAC_MUX_STATE_COLLECTING,
	LAC_MUX_STATE_DISTRIBUTING,
	LAC_MUX_STATE_COLLECTING_DISTRIBUTING
} lac_mux_state_t;

/*
 * Aggregator states
 */

typedef enum {
	AGG_STATE_UP,
	AGG_STATE_DOWN
} agg_state_t;

/*
 * Aggregator
 *
 *	AggID == if_index
 *	AggDescription == if_version
 *	AggName == if_name + if_unit
 *	AggDataRate == if_baudrate
 *	AggMACAddress == lag_softc is_addr (is_ac.ac_enaddr)
 * 	AggOctetsTxOK == 
 * 	AggOctetsRxOK == 
 * 	AggFramesTxOK == 
 * 	AggFramesRxOK ==
 * 	AggMulticastFramesTxOK ==
 * 	AggMulticastFramesRxOK ==
 * 	AggBroadcastFramesTxOK ==
 * 	AggBroadcastFramesRxOK ==
 * 	AggFramesDiscardedOnTx ==
 * 	AggFramesDiscardedOnRx ==
 * 	AggFramesWithTxErrors ==
 * 	AggFramesWithRxErrors ==
 */

struct aggregator {
	u_char		agg_a_systemid[6];	/* actor system id */
	u_int16_t	agg_a_syspriority;	/* actor system priority */
	int		agg_canaggregate;	/* yes(1) or no(0) */
	lag_key_t	agg_a_adminkey;		/* actor admin key*/
	lag_key_t	agg_a_operkey;		/* actor oper key*/
	u_char		agg_macaddress[6];	/* mac address */
	u_char		agg_p_systemid[6];	/* partner system id */
	u_int16_t	agg_p_syspriority;	/* partner system priority */
	lag_key_t	agg_p_operkey;		/* partner oper key*/
	agg_state_t	agg_adminstate;		/* administrative state */
	agg_state_t	agg_operstate;		/* operational state */
	lag_time_t	agg_lastoperchange;	/* time of last oper change */
	lag_counter_t	agg_unknownprotoframes;	/* unknown slow proto frames */
	struct ifnet    *agg_lagif;		/* back pointer to virt lagif */
	u_int16_t	agg_collectormaxdelay;	/* units of 10 microseconds */
};

/*
 * Aggregation Port
 *
 *	AggPortID == ap_ifp->if_index
 */

struct aggport {
	struct aggport *ap_next;		/* next port on agg port list */
	struct aggport *ap_prev;		/* prev port on agg port list */
	struct aggport *ap_lagnext;		/* next port on this lag */
	unsigned	ap_refcnt;		/* refcnt */
	struct ifnet   *ap_ifp;			/* ifnet for this agg port */
	u_int16_t	ap_a_syspriority;	/* actor */
	u_char		ap_a_systemid[6];	/* actor */
	lag_key_t	ap_a_adminkey;		/* actor */
	lag_key_t	ap_a_operkey;		/* actor */
	u_int16_t	ap_p_adminsyspriority;	/* partner */
	u_int16_t	ap_p_opersyspriority;	/* partner */
	u_char		ap_p_adminsystemid[6];	/* partner */
	u_char		ap_p_opersystemid[6];	/* partner */
	lag_key_t	ap_p_adminkey;		/* partner */
	lag_key_t	ap_p_operkey;		/* partner */
	u_int		ap_selectedaggid;	/* ifindex of selected aggr */
	u_int		ap_attachedaggid;	/* ifindex of attached aggr */
	u_int16_t	ap_a_port;		/* actor */
	u_int16_t	ap_a_portpriority;	/* actor */
	u_int16_t	ap_p_adminport;		/* partner */
	u_int16_t	ap_p_operport;		/* partner */
	u_int16_t	ap_p_adminportpriority;	/* partner */
	u_int16_t	ap_p_operportpriority;	/* partner */
	u_int8_t	ap_a_adminstate;	/* actor */
	u_int8_t	ap_a_operstate;		/* actor */
	u_int8_t	ap_p_adminstate;	/* partner */
	u_int8_t	ap_p_operstate;		/* partner */
	int		ap_canaggregate;	/* yes(1) or no(0) */
	int 		(*ap_port_if_output)(); /* 
					         * if_output of ap_ifp
					         * when the port was added
						 */	
	int 		(*ap_port_if_ioctl)();  /* 
					         * if_ioctl of ap_ifp
					         * when the port was added
						 */	
	u_char 		ap_port_ac_enaddr[14];	/*
					         * ac_enaddr of ap_ifp
					         * when the port was added
						 */	
	int 		ap_port_if_flags;	/* 
					         * if_flags of ap_ifp
					         * when the port was added
						 */	
        ulong           ap_hwid;                /* 
					         * hwmgr device id for this 
					         * interface
					         */
	u_int		ap_flags;		/* aggport flags:       */
#define LAG_AP_F_ACTIVE 0x01			/* port is being used   */

#ifdef ESTAT_EXTENDED_PRESENT
	struct estat_extended	
                        ap_ctrblk;	        /* per-port extended counter block */
#else
        struct estat	ap_ctrblk;	        /* estat in ether_driver */
#endif
};

#define AGGPORT_REF(ap)  {\
            atomic_incl(&(ap)->ap_refcnt); \
}

#define AGGPORT_UNREF(ap)  {\
            if (atomic_decl(&(ap)->ap_refcnt)  == 1) \
                 aggport_free(ap);\
}


#define ap_portid ap_ifp->if_index

#define LAG_DEBUG(args) if (lag_debug) printf args

/*
 * Aggregation Port Stats
 *
 *	AggPortStatsID == AggPortID
 */

struct aggportstats {

	/*
	 * Receive counters
	 */

	lag_counter_t aps_lacpdusrx;		/* LACPDUs */
	lag_counter_t aps_markerpdusrx;		/* Marker PDUs */
	lag_counter_t aps_markerresponsepdusrx;	/* Marker Response PDUs */
	lag_counter_t aps_unknownrx;		/* unknown slow protocol */
	lag_counter_t aps_illegalrx;		/* illegal slow protocol */

	/*
	 * Transmit counters
	 */

	lag_counter_t aps_lacpdustx;		/* LACPDUs */
	lag_counter_t aps_markerpdustx;		/* Marker PDUs */
	lag_counter_t aps_markerresponsepdustx;	/* Marker Response PDUs */

};


/*
 * LAG softc
 */

#define LAG_DESCR "Link Aggregation Virtual Interface"

struct lag_softc {
	struct ether_driver	ls_ed;		/* ether driver common part */
#define ls_ac	ls_ed.ess_ac			/* arpcom */
#define ls_if	ls_ac.ac_if			/* ifnet */
#define ls_addr ls_ac.ac_enaddr			/* MAC address */
#define ls_ztime	ls_ed.ess_ztime			/* time since last zeroed */
#if LANDDI_VERSION_MAJOR > 4
	struct net_hw_mgmt	ls_ehm;		/* Enhanced HW Mgmt Support */
#endif
#ifdef ESTAT_EXTENDED_PRESENT
	struct estat_extended	ls_ctrblk;	/* extended counter block */
#else
#define ls_ctrblk	ls_ed.ess_ctrblk	/* estat in ether_driver */
#endif
#if NETSYNC_LOCK
	simple_lock_data_t	ls_lk_softc;	/* "driver/softc" SMP lock */
#endif
	unsigned		ls_flags;	/* lag specific flags */
#define LAG_STATIC_MACADDR 	0x0001U	  
	struct aggregator	ls_agg;		/* lag specific stuff */
	u_int 		        ls_nports;	/* number of ports in lag */
	u_int 		        ls_maxports;	/* max number of ports in lag */
	u_int 		        ls_dist;	/* distribution type */
	u_int 		        ls_rrindex;	/* round robin dist index */
        u_char 		        ls_default_lag_macaddr[14];  /* default lag macaddr */
	struct aggport         *ls_aggport;	/* first aggport on this list */
	struct ifnet           *ls_port[1];	/* array of ptrs to ports */
};

/*
 * Timeout Values 
 */
#define  LAG_MAX_TIMEOUT		2147483647      /* Max timeout */
#define  LAG_TIMEOUT_DEAD_INTERFACE	         6	/* Default for dead interface scanning */
#define  LAG_T1					 4	/* LAG default T1 */
#define  LAG_T2					10	/* LAG default T2 */

/* 
 *  The  NIFF to LAG event data structure 
 */

#ifndef NIFF_EVENT
#define NIFF_EVENT
typedef struct niff_event_type 
{
    queue_chain_t	q;
    struct ifnet       *ifp;			/* which interface */
    char	        interface_name[20];
    ifstate_t		interface_current_state;/* its current state */
} niff_event_type_t;
#endif


#define VIRTUAL_LAG_IF(ls) ((ls) && ((ls)->ls_if.if_type  == IFT_LAG))
#define PHYS_LAG_IF(ls)    ((ls) && (ls)->ls_agg->agg_lagif) 


/* synchronization primitives for the LAG subsystem */

#if NETSYNC_LOCK
decl_simple_lock_info(extern, lag_softc_lockinfo); /* protects lag_softc */
decl_simple_lock_info(extern, aggport_list_li);    


/* 
 * The aggport_list_lock is a (reader-writer?) spin lock
 * that protects the aggportlist.
 */
#ifdef notdef			/* rw spin locks only available in steel? */ 

ndecl_rws_lock_data(extern, aggport_list_lock)

#define AGGPORT_LIST_LOCKINIT()       aggport_list_lock = \
			                    rws_alloc(aggport_list_li, 0)
#define AGGPORT_LIST_WRITE_LOCK()     rws_write_lock(aggport_list_lock)
#define AGGPORT_LIST_WRITE_UNLOCK()   rws_write_unlock(aggport_list_lock)
#define AGGPORT_LIST_READ_LOCK()      rws_read_lock(aggport_list_lock)
#define AGGPORT_LIST_READ_UNLOCK()    rws_read_unlock(aggport_list_lock)
/* allow this to succeed since there is no way to do RWS asserts */
#define AGGPORT_ISLOCKED()    	      (lockmode==0||1)

#else /* notdef */
/* use simple locks if reader-write spin locks are not available */

udecl_simple_lock_data(extern, aggport_list_lock)

#define AGGPORT_LIST_LOCKINIT()       usimple_lock_setup(&aggport_list_lock,\
			                                  aggport_list_li)
#define AGGPORT_LIST_WRITE_LOCK()     usimple_lock(&aggport_list_lock)
#define AGGPORT_LIST_WRITE_UNLOCK()   usimple_unlock(&aggport_list_lock)
#define AGGPORT_LIST_READ_LOCK()      usimple_lock(&aggport_list_lock)
#define AGGPORT_LIST_READ_UNLOCK()    usimple_unlock(&aggport_list_lock)
#define AGGPORT_ISLOCKED()    	      (lockmode==0||simple_lock_holder(&aggport_list_lock))


#endif /* rw spin locks only available in steel? */

/*
 * the lag_add_del_li is a complex lock that  synchronizes  add/del operations
 * to the set of lags.
 */
ndecl_lock_data(extern, lag_add_del_lock);
ndecl_lock_info(extern, lag_add_del_li)

#define LAG_ADD_DEL_LOCKINIT()        ulock_setup(&lag_add_del_lock,\
							 lag_add_del_li, TRUE)
#define LAG_ADD_DEL_WRITE_LOCK()      ulock_write(&lag_add_del_lock)
#define LAG_ADD_DEL_READ_LOCK()       ulock_read(&lag_add_del_lock)
#define LAG_ADD_DEL_UNLOCK()          ulock_done(&lag_add_del_lock)
#define LAG_ADD_DEL_ISLOCKED()        (lockmode==0||lock_holder(&lag_add_del_lock))

#else /* NETSYNC_LOCK */

#define AGGPORT_LIST_LOCKINIT()      
#define AGGPORT_LIST_WRITE_LOCK()     
#define AGGPORT_LIST_WRITE_UNLOCK()   
#define AGGPORT_LIST_READ_LOCK()      
#define AGGPORT_LIST_READ_UNLOCK()    
#define AGGPORT_ISLOCKED() 
#define LAG_ADD_DEL_LOCKINIT()  
#define LAG_ADD_DEL_WRITE_LOCK()  
#define LAG_ADD_DEL_READ_LOCK()   
#define LAG_ADD_DEL_UNLOCK()      
#define LAG_ADD_DEL_ISLOCKED()   

#endif /* NETSYNC_LOCK */
#endif /* _KERNEL */


/*
 * subsystem name
 */

#define LAG_SUBSYS "lag"

#define LAG_KEY_MAX		0xffffUL	   /* max lag key value */
#define	LAG_MAX_MAXPORTS        256		   /* Maximum value for maxport */

/*
 * LAG interface name
 */

#define LAGIFNAME "lag"

/*
 * LAG subsystem-specific cfgmgr operations
 */

#define CFG_OP_LAG_CREATE	101		   /* create lag interface */
#define CFG_OP_LAG_DELETE	102		   /* delete lag interface */
#define CFG_OP_LAG_SET_ATTR	103		   /* set lag attribute(s) */
#define CFG_OP_LAG_GET_ATTR	104		   /* get lag attribute(s) */
#define CFG_OP_LAG_ADD_PORT     105		   /* add an aggr port */
#define CFG_OP_LAG_DEL_PORT     106		   /* delete a port from the aggr ports */
#define CFG_OP_LAG_SHOW_AGG     107		   /* Show Aggregate attributes/components */
#define CFG_OP_LAG_SHOW_PORTS   108		   /* Show port attributes */
#define CFG_OP_LAG_GET_NPORTS   109		   /* Get total number of ports attaced to lag */
#define CFG_OP_LAG_GET_NLAGS    110		   /* Get total number of LAGs  configured */

/*
 * distribution type bit flags (_F_), and their corresponding strings (_S_)
 */

#define LAG_DIST_F_DSTIP	0x001		/* dst IP address */
#define LAG_DIST_S_DSTIP	"dstip"
#define LAG_DIST_F_PORT		0x002		/* src/dst transport port */
#define LAG_DIST_S_PORT		"port"
#define LAG_DIST_F_DSTMAC	0x004		/* dst MAC address */
#define LAG_DIST_S_DSTMAC	"dstmac"
#define LAG_DIST_F_RR		0x008		/* round robin */
#define LAG_DIST_S_RR		"roundrobin"
#define LAG_DIST_F_CLUCHAN	0x010		/* cluster channel weighting */
#define LAG_DIST_S_CLUCHAN      "cluchannel"

/*
 * request/result arguments to LAG subsystem cfg_subsys_op's
 */

struct lag_cfg_create {
	char            lcc_lagifname[IFNAMSIZ];   /* lag interface name */
	lag_key_t	lcc_key;		   /* aggregator key */
	char		lcc_macaddr[6];		   /* MAC addr of the lagif */
	short		lcc_unit;		   /* lag interface unit # */
	u_int		lcc_dist;		   /* distribution type */
};

struct lag_cfg_add {
	char            lca_portifname[IFNAMSIZ];	/* port name */
	lag_key_t	lca_key;			/* port key (optional)  */
	char		lca_lagifname[IFNAMSIZ];	/* lag ifname (output) */
};

struct lag_cfg_del {
	char            lcd_portifname[IFNAMSIZ];	/* port name  (input)  */
	char		lcd_lagifname[IFNAMSIZ];	/* lag ifname (output) */
};

struct lag_cfg_portinfo {
	char		portifname[IFNAMSIZ];		/* port ifname (input) */
	int		state;				/* port state */
};

struct lag_cfg_show {
	char		lcs_ifname[IFNAMSIZ];		/* lag/port ifname (input) */
	lag_key_t	lcs_key;			/* aggregator key */
	u_int		lcs_dist;			/* distribution type */
	int		lcs_state;			/* LAG state */
	int		lcs_nlags;			/* Number of LAGs configured */
	int		lcs_flags;			/* Aggregate flags */
	int		lcs_nports;			/* Number of ports in aggregate */
	int		lcs_maxports;			/* LAG maxport */
	struct lag_cfg_portinfo
			lcs_portinfo[LAG_MAX_MAXPORTS];	/* port information datablock */
};

#ifdef _KERNEL

/* if_lag.c */
int  lag_create_agg(struct lag_cfg_create *, struct lag_cfg_create *);
int  lag_add_port(struct lag_cfg_add *, struct lag_cfg_add *);
int  lag_del_port(struct lag_cfg_del *, struct lag_cfg_del *);
int  lag_show_agg(struct lag_cfg_show *, struct lag_cfg_show *);
int  lag_show_port(struct lag_cfg_show *, struct lag_cfg_show *);
void lag_linkup_event(EvmEvent_t, void *);
void lag_linkdown_event(EvmEvent_t, void *);

#endif

#endif /* _LAG_H */
