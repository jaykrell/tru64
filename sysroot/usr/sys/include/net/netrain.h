/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: netrain.h,v $
 * Revision 1.1.26.2  2006/03/18  00:29:31  Terrence_Harple
 * 	Added #ifndef NIFF_EVENT so that including both netrain.h and lag.h compiles.
 *
 * Revision 1.1.26.1  2002/10/16  14:43:11  Michael_Daniele
 * 	Add nrifp argument to netrain_add_device() to support IFF_TAGGING.
 *
 * Revision 1.1.23.1  2002/01/11  17:17:36  Jack_McCann
 * 	Merge v51asupportos-171-daniele to wcalpha bl3.
 *
 * Revision 1.1.21.1  2001/12/20  16:22:47  Michael_Daniele
 * 	NetRAIN ECP: Support millisecond timers.
 *
 * Revision 1.1.15.3  2000/01/21  20:26:00  Brian_Haley
 * 	NUMA ifnet support:
 * 	- added second argument (RADid) to nr_init_softc() prototype
 *
 * Revision 1.1.15.2  1999/12/15  14:50:04  Sowmini_Varadhan
 * 	Added netrain_add_one_to_set, netrain_remove_one_from_set
 *
 * Revision 1.1.15.1  1999/11/03  22:43:52  Ernie_Petrides
 * 	Fix build warnings.
 *
 * Revision 1.1.4.7  1999/02/02  14:09:09  Ted_Qian
 * 	add netrain_load_dli function prototype.
 * 	[1999/01/08  20:37:52  Ted_Qian]
 *
 * Revision 1.1.4.6  1998/10/30  13:48:58  Ted_Qian
 * 	removed DT since it is calculated on fly
 * 	from T1 and T2
 * 
 * 	added per instance timers for eliminating a race
 * 	between NRTIMERS ioctl and netrain_worker thread.
 * 
 * 	added if_nrif_state
 * 
 * 	niffizing NetRAIN project.
 * 	[1998/10/27  22:23:36  Ted_Qian]
 * 
 * Revision 1.1.4.5  1998/09/30  19:27:42  Tony_Bono
 * 	Merge from PTEV6OS_BL8.
 * 	[1998/09/30  19:11:30  Tony_Bono]
 * 
 * Revision 1.1.8.3  1998/08/19  17:37:20  Farrell_Woods
 * 	Fix for QAR 63360 - bump up NR_DEVICES
 * 	[1998/08/18  18:47:54  Farrell_Woods]
 * 
 * Revision 1.1.8.2  1998/03/31  22:27:06  Farrell_Woods
 * 	Back-port of NetRAIN
 * 	[1998/02/20  21:05:29  Farrell_Woods]
 * 
 * Revision 1.1.4.4  1998/02/12  19:47:28  Brian_Haley
 * 	Changed nr_init, nr_start, nr_watch and nr_reset protos to
 * 	match their ifnet structure definitions so we can compile
 * 	with -warnprotos.
 * 	[1998/01/29  17:06:52  Brian_Haley]
 * 
 * Revision 1.1.4.3  1997/08/13  13:21:04  Paul_Litvak
 * 	Cleanup of compiler warning messages
 * 	[1997/07/09  18:25:58  Paul_Litvak]
 * 
 * Revision 1.1.4.2  1997/02/19  19:52:50  Steve_Hurst
 * 	Initial NetRAIN checkin. This module contains all of the NetRAIN
 * 	specific data structure, symbol definitions, and function prototypes.
 * 	[1997/02/12  18:48:10  Steve_Hurst]
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: netrain.h,v $ $Revision: 1.1.26.2 $ (DEC) $Date: 2006/03/18 00:29:31 $
 */

#ifndef _NETRAIN_H_
#define _NETRAIN_H_

#include "kern/thread.h"

/*
 * This is mainly used by LANE, and etc.
 * nr_status of an interface is initialized with NIT_INIT 
 * and is set to NIT_CONFIGURED when the link MAC address
 * is available.
 */
typedef enum ifstatus {NIT_INIT, NIT_CONFIGURED, NIT_UP, NIT_DOWN, NIT_DONT_KNOW} ifstatus_t;

/* 
 * NetRAIN macros 
 */
#define	IsItANetRAINInterface(ifp)	   ((ifp) && (ifp)->if_nrnext)
#define	IsItANetRAINVirtualInterface(ifp)  ((ifp) && (ifp)->if_nrnext && !((ifp)->if_nrif))
#define	IsItANetRAINPhysicalInterface(ifp) ((ifp) && (ifp)->if_nrnext && (ifp)->if_nrif)
#define	IsItANetRAINCurrentInterface(ifp)  ((ifp) && IsItANetRAINPhysicalInterface(ifp) && ((ifp)->if_nrif->if_nrnext == ifp))

/* NetRAIN device name prefix. */
#define NR_NAME_PREFIX "nr"

/* Netrain device counts. */
#define NR_MAXDEV 512            /* Max */
#define NR_DEVICES 128           /* Default - overridden in sysconfigtab */

/* Local MAC address bit. This bit is set in the high order nibble of
 * an ethernet MAC address to indicate that it is a locally administered
 * address. 
 */
#define NR_LOCAL_MAC_BIT 2

/* Undefined device type. */
#define NR_TYPE_UNKNOWN 0

#define  NR_UNIT_NOTMEMBER -1

/*
 * Timeout Values 
 */
#define  NR_MAX_TIMEOUT		2147483647      /* Max timeout */
#define  NR_HZ				1000	/* Timer values are in milliseconds */
#define  NR_TIMEOUT_DEAD_INTERFACE      6       /* Default for dead interface scanning (seconds) */
#define  NR_DEAD_STR			"6"	/* String version of NR_TIMEOUT_DEAD_INTERFACE */
#define  NR_T1                          4       /* NetRAIN default T1 (seconds) */
#define  NR_T1_STR			"4"	/* String version of NR_T1 */
#define  NR_T2                          10      /* NetRAIN default T2 (seconds) */
#define  NR_T2_STR			"10"	/* String version of NR_T2 */
#define  NR_T1_MIN	 		500	/* NetRAIN default t1_min (milliseconds) */
#define  NR_DT_MIN			200     /* NetRAIN default dt_min (milliseconds) */
#define  NR_T2_MIN			1100	/* NetRAIN default t2_min (milliseconds) */
#define  NR_DEAD_MIN			500	/* NetRAIN default dead_min (milliseconds) */
#define  NR_STR_SIZE			10	/* Max size of string attributes */

/* Calculate dt from t1 and t2. */
#define NR_DT_OF(t1, t2) ((t2) - (t1))/3

ndecl_lock_data(extern, nrlist_lock)
#define NRLIST_LOCKINIT()   ulock_setup(&nrlist_lock,  nrlist_li, TRUE)
#define NRLIST_READ_LOCK()  ulock_read(&nrlist_lock)
#define NRLIST_WRITE_LOCK() ulock_write(&nrlist_lock)
#define NRLIST_UNLOCK()     ulock_done(&nrlist_lock)
#define NRLIST_ISLOCKED()   (lockmode==0||lock_holder(&nrlist_lock))

/* NetRAIN softc definition */

struct nr_softc {
    struct      ether_driver is_ed;     /* driver */
#define is_ac   is_ed.ess_ac            /* common part */
#define ztime   is_ed.ess_ztime         /* Time since last zeroed */
#define is_if   is_ac.ac_if             /* network-visible interface */
#define is_addr is_ac.ac_enaddr         /* hardware address */

    decl_simple_lock_data(, nr_softc_lock)
};

/*
 * data structure used for building a socket linked
 * list to its peers.
 */
struct nr_peer_socket
{
    struct nr_peer_socket *next;       
    struct socket 	*sock;	/* socket to the peer ifp */
    struct ifnet 	*ifp;	/* peer Ifnet pointer */
};

/* Interface instance structure */

struct nr_instance
{
    struct   nr_instance *nr_next;      /* Next netrain instance */
    int      nr_flags;                  /* Flags field */
    int      nr_state;                  /* Current state of this interface */
    struct   ifnet *nr_ifp;             /* Ifnet pointer */
    int      nr_unit;                   /* Unit number for netrain set */
    ifstatus_t nr_status;               /* MAC address availability */  
    int      nr_autotmo;                /* Autofail timeout */
    int      nr_autofail;               /* Autofail timer value */
    struct ifdevea	hwaddr;		/* MAC address */
    struct nr_peer_socket *peer_sock;   /* socket list to its peers */
    int refcount;			/* to protect the set w/o the NR lock */
    int      if_nrif_state;             /* Current state of the nr interface */
    int      t1;			/* time between green poll */
    int      t2;			/* time to dead */
};

struct nr_globals_t 
{
    int	nr_timeout_dead_interface;	/* dead interface scan interval	*/
    int t1;				/* GREEN to YELLOW interval, ms */
    int t2;				/* GREEN to DEAD interval, ms */
    int nrg_t1_min;			/* min value for t1, in ms */
    int nrg_t2_min;			/* min value for t2, in ms */
    int nrg_dt_min;			/* min value for dt, in ms */
    int nrg_dead_min;			/* min value for dead, in ms */

    /*
     * String versions of timer attributes.  The "configured" versions
     * are used by the configuration management framework, and should
     * always be the same as the "current" versions except during a
     * reconfigure operation (e.g. sysconfig -r netrain nr_timeout_t=3).
     */
    char nrg_t1_str[NR_STR_SIZE];	/* configured t1 (nr_timeout_t) */
    char nrg_t1_cur_str[NR_STR_SIZE];	/* current t1 */
    char nrg_t2_str[NR_STR_SIZE];	/* configured t2 (nr_timeout_o) */
    char nrg_t2_cur_str[NR_STR_SIZE];	/* current t2 */
    char nrg_dead_str[NR_STR_SIZE];	/* configured nr_timeout_dead_interface */
    char nrg_dead_cur_str[NR_STR_SIZE];	/* current nr_timeout_dead_interface */

    thread_t	 dead_interface_recovery_thread;
    thread_t	 niff_event_q_rcv_process_thread;
    thread_t	 worker_thread;		/* auto failover and link online */
    queue_head_t niff_event_q;		/* events from the NIFF */
#ifdef NETSYNC_LOCK
    decl_simple_lock_data(, (niff_event_q_lock)) /* the event queue protection */
#endif
};

/* 
 *  The lock that protects the NIFF to NetRAIN event queue 
 */
#ifdef NETSYNC_LOCK
#define NIFF_EVENT_Q_LOCKINIT()	simple_lock_setup(&(nr_globals.niff_event_q_lock), niff_event_q_lock_li)
#define NIFF_EVENT_Q_LOCK()	simple_lock(&(nr_globals.niff_event_q_lock))
#define NIFF_EVENT_Q_UNLOCK()	simple_unlock(&(nr_globals.niff_event_q_lock))
#define NIFF_EVENT_Q_ISLOCKED()	(lockmode==0||simple_lock_holder(&(nr_globals.niff_event_q_lock)))
#else
#define NIFF_EVENT_Q_LOCKINIT()
#define NIFF_EVENT_Q_LOCK()
#define NIFF_EVENT_Q_UNLOCK()
#define NIFF_EVENT_Q_ISLOCKED()
#endif

/* 
 *  The  NIFF to NetRAIN event data structure 
 */
#ifndef NIFF_EVENT
#define NIFF_EVENT
typedef struct niff_event_type 
{
    queue_chain_t	q;
    struct ifnet 	*ifp; /* which interface */
    char 	interface_name[20];
    ifstate_t 	interface_current_state; /* its current state */
} niff_event_type_t;
#endif
 
/* Function prototype */

struct ifnet *nr_init_softc(int, int);
int nr_init(int);
void nr_start_locked(struct nr_softc *, struct ifnet *);
int nr_start(struct ifnet*);
int nr_watch(int);
int nr_reset(int, int);
void nr_reset_locked(struct nr_softc *, struct ifnet *, int);
int nr_ioctl(struct ifnet *, u_int, caddr_t);
void netraininit(void);
int netrain_tmt_add(struct ifnet *ifp, int t1, int dt, int t2);
int netrain_tmt_remove(struct ifnet *ifp);
int netrain_tmt_state_modify(struct ifnet *ifp, ifstate_t state);
int netrain_tmt_timer_modify(struct ifnet *ifp, int t1, int dt, int t2);
int netrain_ioctl(struct socket *so, unsigned int cmd, caddr_t data);
void netrain_create_instance_list_for_delete(struct ifnet *ifp,  struct nr_instance **tmp_nr_list);
void netrain_destroy_instance(struct nr_instance *instance);
void netrain_destroy_instance_list(struct nr_instance *tmp_nr_list);
int nr_get_unit(char *name);
struct nr_instance *nr_get_instance(struct ifnet *ifp);
int netrain_switch(struct ifnet *ifp, boolean_t force_switching);
void netrain_worker(void);
void netrain_dead_interface_recovery(void);
boolean_t netrain_search_nrlist(struct nr_instance *search_instance);
struct nr_instance* netrain_get_a_peer_interface(struct nr_instance *curr_instance, boolean_t must);
struct nr_instance* netrain_get_current_interface(struct nr_instance *instance);
boolean_t netrain_ping(struct nr_instance * from_instance, struct nr_instance * to_instance);
void netrain_xid_send(struct socket *sock);
int netrain_xid_setup(struct nr_instance *from_p, struct nr_instance *to_p);
int netrain_xid_setup_to_active(struct nr_instance *from_p,struct ifnet *nrifp,struct ifdevea *physaddr);
void netrain_niff_event_handler(niff_event_type_t *niff_event_p);
void netrain_process_niff_event(void);
int tmt_ioctl(struct socket *so, unsigned int cmd, caddr_t data);
int netrain_add_device(struct ifnet *ifp, int unit, struct ifnet *nrifp);
int netrain_dev_init(struct nr_instance *instance);
void nr_save_if_nrif_state(struct ifnet *ifp, int current_state);
boolean_t netrain_event_acceptance(int cur_state, int new_state);
int netrain_load_dli(void);
int netrain_add_one_to_set(struct ifnet *nrifp, struct ifnet *ifp);
int netrain_remove_one_from_set(struct ifnet *nrifp, struct ifnet *ifp);
#endif
