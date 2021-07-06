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
 * @(#)$RCSfile: pwrmgr.h,v $ $Revision: 1.1.12.1 $ (DEC) $Date: 2002/01/24 18:55:22 $
 */

#ifndef _DEC_PWRMGR_PWRMGR_H_
#define _DEC_PWRMGR_PWRMGR_H_

#ifndef __cplusplus

/*
 *	pwrmgr.h
 */
#include <sys/sysconfig.h>		/* subsystem definitions */
#include <evm/evm.h>			/* Event Manager definitions */
#include <ksm/ksm.h>			/* Kernel Set Management data structures */
#include <io/common/hwc_reg.h>		/* Hardware management definitions */

/*
 * Power Management Commands supported by Power Manager 
 */
#define PWRMGR_REGISTER_DEVICE		(CFG_OP_SUBSYS_MIN+0)
#define PWRMGR_DEREGISTER_DEVICE	(CFG_OP_SUBSYS_MIN+1)
#define PWRMGR_SET_DEVINFO		(CFG_OP_SUBSYS_MIN+2)
#define PWRMGR_POWER_UP			(CFG_OP_SUBSYS_MIN+3)
#define PWRMGR_POWER_DOWN		(CFG_OP_SUBSYS_MIN+4)

/*
 * NOTE ... you need to update this if you add a new subsystem
 * specfic operation
 */
#define PWRMGR_MAX_OP	PWRMGR_POWER_DOWN
#define PWRMGR_MAX_FUNC ((PWRMGR_MAX_OP-CFG_OP_SUBSYS_MIN)+1)

/*
 * Power Management Device Types
 */
#define PWRMGR_DEV_CPU			0x1
#define PWRMGR_DEV_DISK			0x2
#define PWRMGR_DEV_TAPE			0x4
#define PWRMGR_DEV_GRAPHICS		0x8
#define PWRMGR_DEV_NETWORK		0x10
#define PWRMGR_DEV_MULTIMEDIA		0x20
#define PWRMGR_DEV_THERMAL		0x40
#define PWRMGR_DEV_BATTERY		0x80
#define PWRMGR_DEV_UI			0x100
#define PWRMGR_DEV_XSERVER		0x200

/*
 * Power Management power states
 */
#define MAX_POWER_STATE 3
#define PWRMGR_MAX_NAME 16
#define MAX_PRIVATE 3
/*
 * pwrmgr_devinfo data structure
 *
 *	Some fields are for use by the power manager (MGR), others by the
 *	clients (CLI). Non-tagged fields are used by both.
 */

#define PWRMGR_DEVINFO_VERSION 1
#define PWRMGR_SET_VERSION()

typedef struct pwrmgr_devinfo {
	struct pwrmgr_devinfo *next;	/* MGR: Linked list */
	struct pwrmgr_devinfo *previous;/* MGR: Linked list */
	char device_name[PWRMGR_MAX_NAME];/* CLI: unique name  */
	int device_type;		/* Defined device types:PWRMGR_DEV_* */
	caddr_t private[MAX_PRIVATE];	/* CLI: Client's private data */
	int global_enable;               /* Global Power management enable */
	int dev_enable;			/* Device's Power Management enable*/
	int power_state;		/* CLI: current power status of the client */
	int dwell_time[MAX_POWER_STATE];/* CLI: timing parameter */
	struct pwrmgr_devinfo *handle;	/* MGR: */
	u_long count;			/* CLI: client tracks it's changes  */
	int deregistered;		/* MGR: set to a 1 on deregistration */
#ifdef _KERNEL
	EvmHandle_S_t  event_handle;	/* CLI: saves event subscription handle */
#else
	caddr_t	event_handle;
#endif
} pwrmgr_devinfo_t;

/*
 * pwrmgr_dev_handles data structure
 */
struct pwrmgr_dev_handles {
	int count;
	caddr_t handles;
};


/*
 * Event Management Manager related defines
 */ 

#define	PWRMGR_NOTIFY_ATTR_CHANGE	0
#define	PWRMGR_NOTIFY_PWR_CHANGE	1
#define	PWRMGR_NOTIFY_DEV_REG		2
#define	PWRMGR_NOTIFY_DEV_DEREG		3
#define	PWRMGR_NOTIFY_THERMAL		4
#define	PWRMGR_NOTIFY_BATTERY		5




#define _PWRMGR_EVENT_NAME(x) 	_EvmSYSTEM_EVENT_NAME("power") "." x

#define PWRMGR_EVM_ATTR_CHANGE	_PWRMGR_EVENT_NAME("attr_change")
#define PWRMGR_EVM_PWR_CHANGE	_PWRMGR_EVENT_NAME("state_change")
#define PWRMGR_EVM_DEV_REG	_PWRMGR_EVENT_NAME("dev_reg")
#define PWRMGR_EVM_DEV_DEREG   	_PWRMGR_EVENT_NAME("dev_dereg")
#define PWRMGR_EVM_THERMAL	_PWRMGR_EVENT_NAME("thermal_change")
#define PWRMGR_EVM_BATTERY	_PWRMGR_EVENT_NAME("battery_change")

#define PWRMGR_VAR_ATTR_CHANGE	"attribute"
#define PWRMGR_VAR_PWR_CHANGE	"power_state"
#define PWRMGR_VAR_THERMAL	"thermal_state"
#define PWRMGR_VAR_DEVICE_ID	"device_id"
#define PWRMGR_VAR_BATTERY	"battery_state"

#define PWRMGR_USE_ATTR_CHANGE	0x1
#define PWRMGR_USE_PWR_CHANGE	0x2
#define PWRMGR_USE_THERMAL	0x4
#define PWRMGR_USE_DEVICE_ID	0x8
#define PWRMGR_USE_BATTERY	0x10




#define PWRMGR_ATTR_SIZE	(sizeof(int) * MAX_PWRMGR_CFG_ENTRIES)	


/* definitions related to attribute changes */
#define ATTR_DEF_PWRMGR 	0
#define ATTR_CPU_SLOW 		1
#define ATTR_DISK_SPIN		2
#define ATTR_DISK_DWELL		3
#define ATTR_GFX_POWER		4
#define ATTR_GFX_DWELL_ST	5
#define ATTR_GFX_DWELL_SU	6
#define ATTR_GFX_DWELL_OF	7


/*
 * functional prototypes for pwrmgr functions 
 */

#ifdef _KERNEL

extern cfg_status_t 
pwrmgr_register_device(caddr_t indata,
		       ulong indata_size,
		       caddr_t outdata,       
		       ulong outdata_size);

extern cfg_status_t 
pwrmgr_deregister_device(caddr_t indata,
			 ulong indata_size,
			 caddr_t outdata,       
			 ulong outdata_size);

extern cfg_status_t
pwrmgr_notify_event(pwrmgr_devinfo_t *devinfo,
		    int evtmgr_event);

#if defined(_USE_KERNEL_PROTOS)
extern int pwrmgr_subsys_state(int *state);

#endif /* defined(_USE_KERNEL_PROTOS) */

#endif /* _KERNEL */

#endif /* __cplusplus */
#endif /* _DEC_PWRMGR_PWRMGR_H_ */


















