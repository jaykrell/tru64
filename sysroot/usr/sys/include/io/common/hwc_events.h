/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: hwc_events.h,v $
 * Revision 1.1.20.1  2002/10/14  17:41:21  Jason_Miller
 * 	Add EVM_ERR_COUNT_CHANGE event.
 *
 * Revision 1.1.12.1  2001/09/13  20:32:05  Mark_Bokhan
 * 	Merge motoos into wcalpha
 *
 * Revision 1.1.7.2  2001/07/10  21:53:18  Carolyn_Briglia
 * 	hwc event fixes
 *
 * Revision 1.1.10.1  2001/07/03  19:38:18  Mark_Bokhan
 * 	Add HWC_EVT_MEMB_LOCKED flag to HWC_POST_EVENT_REQ structure
 * 	to fix a deadlock condition in the set attr path (QAR 88789)
 *
 * Revision 1.1.7.1  2001/06/01  13:53:16  Joshua_Smith
 *      Merge from hotswap.
 *
 * Revision 1.1.5.1  2001/05/08  22:27:56  Mark_Bokhan
 * 	Add HWC_EVT_NO_HANDLE and HWC_EVT_KERNEL_ONLY flags
 *
 * Revision 1.1.4.2  2000/11/03  20:28:11  Jan_Reimers
 * 	Add definition for EVM_LUN_EXPANDED
 * 	Update EVM_DISK_LABEL definitions
 *
 * Revision 1.1.4.1  2000/10/16  19:24:53  Michael_Gilmore
 * 	(QAR 81827) moved event definitions here. Added event for disk label write.
 *
 * Revision 1.1.2.5  1999/04/29  14:37:33  Mark_oBokhan
 * 	Add definition for popular _hwid, HWC_EVT_VAR_HWID
 * 	[1999/04/23  15:35:41  Mark_Bokhan]
 *
 * Revision 1.1.2.4  1998/12/04  23:23:05  Jem_Treadwell
 * 	Use macro for EVM event names
 * 	[1998/12/04  23:09:14  Jem_Treadwell]
 * 
 * Revision 1.1.2.3  1998/01/07  19:58:36  Mark_Bokhan
 * 	Allow caller of hwc_post_event to specify a category name, to be
 * 	used in the event name.  Hardware deregistration needs this feature
 * 	because the pointer to the hardware component's category no longer
 * 	exists at the time the event is being posted.
 * 	[1997/12/22  22:28:31  Mark_Bokhan]
 * 
 * Revision 1.1.2.2  1997/11/12  23:25:36  Mark_Bokhan
 * 	Genesis.
 * 	[1997/11/07  23:35:23  Mark_Bokhan]
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: hwc_events.h,v $ $Revision: 1.1.20.1 $ (DEC) $Date: 2002/10/14 17:41:21 $
 */
#ifndef _HWC_EVENTS_H_
#define _HWC_EVENTS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <evm/evm.h>		/* Event Manager */
    
/*
 * This is the hardware configuration (hwc) request structure for
 * posting hardware events.  Since we are dependant on the Event
 * Manager, most of the field types are dictated in evm.h.
 */
typedef struct hwc_post_event_req {
    int		   version;	   /* version of this structure */
    ulong	   flags;	   /* see hw event bit flags def's below */
    void	   *dev_handle;	   /* hwc device handle */
    EvmString_t	   family;	   /* event family name (NULL=default prefix) */
    EvmString_t	   name;	   /* name of the event */
    EvmPriority_t  priority;	   /* evt priority (opt./must be flagged)*/
    EvmPid_t	   pid;		   /* process id (optional, must be flagged) */
    int		   category_idx;   /* category array index (optional/flagged) */
    int		   num_named_vars; /* number of specified named_vars */
    EvmVarStruct_t *named_vars_p;  /* pointer to array of EvmVarStructs  */
} HWC_POST_EVENT_REQ;

/*
 * HWC_POST_EVENT_REQ bit flag definitions
 * 
 * When one of these flags is set, it means the corresponding entry in the
 * hwc_post_event_req structure is valid, to be used in the event attribute
 * and/or name.
 */
#define HWC_EVT_PRIORITY	0x01	/* specifying priority in request */
#define HWC_EVT_PID		0x02	/* specifying pid in request */
#define HWC_EVT_CATEGORY	0x04	/* specifying event name category */
#define HWC_EVT_NO_HANDLE	0x08	/* no dev_handle specified */
#define HWC_EVT_KERNEL_ONLY	0x10	/* if set, don't propagate to evmd */
#define HWC_EVT_MEMB_LOCKED	0x20	/* if set, member is already locked */

/*
 * Event name string definitions
 */
#define HWC_EVT_PREFIX		_EvmSYSTEM_VP
#define HWC_EVT_HW		"hw"
#define HWC_EVT_REG		"registered"
#define HWC_EVT_DEREG		"deregistered"
    
/*
 * Event variable names
 */
#define HWC_EVT_VAR_HWID	"_hwid"
    
    
#define	MAX_HW_EVENT_LEN	256
    
/*
 * Function prototypes
 */
extern int hwc_post_event(HWC_POST_EVENT_REQ *);


/*
 *  EVM events:
 */

#define EVM_PATH_REDUCED        100     /* CAM: Lost a Path                 */
#define EVM_PATH_LOST           101     /* CAM: No Paths                    */
#define EVM_PATH_GAIN           102     /* CAM: Gained a path               */

#define EVM_DISK_CLUSTER_DISA   200     /* CAM: Cluster disable state change*/

#define EVM_TAPE_MEDIA_CHANGED  300     /* CAM: Media changed or reset      */

#define EVM_DISK_LABEL_MEM_WRITTEN  400 /* In-memory disk label written     */
#define EVM_DISK_LABEL_DISK_WRITTEN 401 /* On-disk   disk label written     */
#define EVM_LUN_EXPANDED        402     /* LUN expanded                     */
#define EVM_ERR_COUNT_CHANGE	403	/* Some error counter changed	    */


#ifdef __cplusplus
}
#endif
#endif /*_HWC_EVENTS_H_ */
