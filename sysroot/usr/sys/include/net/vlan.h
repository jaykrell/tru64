/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: vlan.h,v $
 * Revision 1.1.10.1  2002/10/16  14:43:13  Michael_Daniele
 * 	Added external data declarations.
 *
 * Revision 1.1.7.1  2002/07/10  18:36:02  Paul_Moore
 *  Forward ported this file by Mike Daniele to add 802.1Q VLAN support.
 *
 * $EndLog$
 */
/*
 * @(#)$RCSfile: vlan.h,v $ $Revision: 1.1.10.1 $ (DEC) $Date: 2002/10/16 14:43:13 $
 */

/*
 *===================================================================================
 *
 * NOTE: The data structures and APIs defined in this file are reserved for use by 
 *	 the operating system, and may be subject to change without notice.
 *
 *===================================================================================
 */


#ifndef _VLAN_H
#define _VLAN_H

#define VLAN_IFNAME     "vlan"

/*
 * VLAN Identifier (VID) stuff.
 */
typedef unsigned short vlan_vid_t;

#define VLAN_DEFAULT_VID	1
#define VLAN_MIN_VID		1	
#define VLAN_MAX_VID		4094	/* 12 bits, and FFF is reserved */
#define VLAN_VALID_VID(v)	((v) > 0 && (v) < 4095)

/* Implementation-specific values used for "untagged". */
#define VLAN_UNTAGGED_VID	0	

/*
 * VLAN sysconfig definitions.
 */
#define VLAN_SUBSYS "vlan"

#define CFG_OP_VLAN_CREATE	101	/* create vlan interface 		*/
#define CFG_OP_VLAN_DELETE	102	/* delete vlan interface 		*/
#define CFG_OP_VLAN_DUMP	103	/* DEBUG: dump vlan structures 		*/
#define CFG_OP_VLAN_SHOW	104	/* show vlan interface			*/

struct vlan_request_args {

        char            vlan_on[IFNAMSIZ];
        char            vlan_name[IFNAMSIZ];
        int             vlan_unit;
        unsigned int    vlan_id;

};


#ifdef _KERNEL

#include <net/if.h>
#include <netinet/if_ether.h>
#include <net/ether_driver.h>

/*
 * VLAN virtual interface softc structure
 */
struct vlan_softc {

	struct ether_driver	*vs_ed;		/* ether driver common part */

#define vs_ac			vs_ed->ess_ac	/* arpcom 		    */
#define vs_if			vs_ac.ac_if	/* ifnet 		    */
#define vs_addr 		vs_ac.ac_enaddr	/* MAC address 		    */
#define vs_ztime		vs_ed->ess_ztime /* time since last zeroed   */

#if NETSYNC_LOCK
	simple_lock_data_t	vs_lk_softc;	/* "driver/softc" SMP lock */
#endif

	/* 
	 * VLAN-specific data.
	 */
	struct vlan_softc	*vs_next;	/* pointer to next vlan on lower if  */
	struct vlan_softc	*vs_prev;	/* pointer to prev vlan on lower if  */
	struct ifnet		*vs_qifp;	/* pointer to lower interface        */
	vlan_vid_t		vs_vid;		/* VID this virtual interface is in */
	short			vs_unused[3];	/* Maintain 64-bit alignment	    */

};

/*
 * Since ifp->if_vlansc is used for VLAN ifnets too,
 * this distinguishes when a non-VLAN interface is in use by VLAN
 * (analogous to IsItANetRAINPhysicalInterface().
 */
#define IF_VLAN_ENABLED(ifp) ((ifp)->if_vlansc && (ifp)->if_type != IFT_VLAN)


/*
 * Synchronization primitives for the VLAN subsystem
 */

#if NETSYNC_LOCK

/* The global RWS lock protects the list of VLAN softcs on a lower interface. */
#define VLAN_SPIN_LOCKINIT() 		vlan_spin_lock=rws_alloc(vlan_spin_li, 0)
#define VLAN_SPIN_LOCK()		rws_write_lock(vlan_spin_lock)
#define VLAN_SPIN_UNLOCK()		rws_write_unlock(vlan_spin_lock)
#define VLAN_SPIN_READ_LOCK()		rws_read_lock(vlan_spin_lock)
#define VLAN_SPIN_READ_UNLOCK()		rws_read_unlock(vlan_spin_lock)
#define VLAN_SPIN_LOCKFREE() 		rws_free(vlan_spin_lock)

/* allow this to succeed since there is no way to do RWS asserts */
/*#define VLAN_SPIN_ISLOCKED() (lockmode==0||simple_lock_holder(&vlan_spin_lock))*/
#define VLAN_SPIN_ISLOCKED() (lockmode==0 || 1)

/* The global add-delete complex lock protects the entire VLAN configuration. */

#define VLAN_ADD_DEL_LOCKINIT()		ulock_setup(&vlan_add_del_lock, vlan_add_del_li, TRUE)
#define VLAN_ADD_DEL_READ_LOCK()	ulock_read(&vlan_add_del_lock)
#define VLAN_ADD_DEL_WRITE_LOCK()	ulock_write(&vlan_add_del_lock)
#define VLAN_ADD_DEL_UNLOCK()		ulock_done(&vlan_add_del_lock)
#define VLAN_ADD_DEL_ISLOCKED()		(lockmode == 0 || lock_holder(&vlan_add_del_lock))

#else /* NETSYNC_LOCK */

#define VLAN_SPIN_LOCKINIT()
#define VLAN_SPIN_LOCK()
#define VLAN_SPIN_UNLOCK()
#define VLAN_SPIN_READ_LOCK()
#define VLAN_SPIN_READ_UNLOCK()
#define VLAN_SPIN_ISLOCKED()
#define VLAN_SPIN_LOCKFREE()

#define VLAN_ADD_DEL_LOCKINIT()
#define VLAN_ADD_DEL_READ_LOCK()
#define VLAN_ADD_DEL_WRITE_LOCK()
#define VLAN_ADD_DEL_UNLOCK()
#define VLAN_ADD_DEL_ISLOCKED()

#endif /* NETSYNC_LOCK */

/*
 * External data.
 */
 
/* In if_vlan.c. */
extern int      vlan_debug;
ndecl_lock_data(extern, vlan_add_del_lock)
 
/* In if_ethersubr.c. */
ndecl_rws_lock_info(extern, vlan_spin_li)
ndecl_rws_lock_data(extern, vlan_spin_lock)
ndecl_lock_info(extern, vlan_add_del_li)
decl_simple_lock_info(extern, vlan_softc_lockinfo)
 
/* Error counters in if_ethersubr.c. */
extern u_long   vlan_rcv_unknown_vids;
extern u_long   vlan_rcv_invalid_vids;
extern u_long   vlan_rcv_cfi_frames;
 
/*
 * Function prototypes.
 */
int	vlan_create_vif( char *, int, int );
int	vlan_delete_vif( int );
int	vlan_validate_unconfig( void );
int	vlan_show( char *, struct vlan_request_args * );
int	vlan_dump( char * );

#endif /* _KERNEL */

#endif /* _VLAN_H */
