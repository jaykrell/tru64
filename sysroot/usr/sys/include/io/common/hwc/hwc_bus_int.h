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
 * @(#)$RCSfile: hwc_bus_int.h,v $ $Revision: 1.1.2.4 $ (DEC) $Date: 1999/03/11 22:06:48 $
 */

#ifndef	_HWC_BUS_INT_H_
#define	_HWC_BUS_INT_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Since we need the external file as well, we'll include it here so the
 * parent file does not have to bother including both.
 */
#include <io/common/hwc_bus_ext.h>

#define HWC_BUS_EHM_BUS_VERSION_ID		1
#define HWC_BUS_EHM_CONNECTION_VERSION_ID	1
#define HWC_BUS_EHM_LOCAL_VERSION_ID		1
#define HWC_BUS_EHM_UHCH_VERSION_ID		1
#define HWC_BUS_EHM_LEGH_VERSION_ID		1
#define HWC_BUS_EHM_MSS_VERSION_ID		1
#define HWC_BUS_EHM_CONNECTION_COMP_VERSION_ID	1

#define HWC_BUS_BUS_SZ_NAME	32	/* Name */
#define HWC_BUS_BUS_SZ_CAT	32	/* Category */

#define HWC_BUS_CONNECTION_SZ_NAME	32	/* Name */
#define HWC_BUS_CONNECTION_SZ_CAT	32	/* Category */

#define HWC_BUS_UNCH_SZ_NAME	64	/* Name */
#define HWC_BUS_UNCH_SZ_CAT	32	/* Category */

#define HWC_BUS_LEGH_SZ_NAME	64	/* Name */
#define HWC_BUS_LEGH_SZ_CAT	32	/* Category */

#define HWC_BUS_BUS_NAME_INDX		0
#define HWC_BUS_BUS_CAT_INDX		1
/* #define HWC_BUS_BUS_SCANTIME_INDX	2 - Defined in hwc_bus_ext.h */

#define HWC_BUS_BUS_NUM_ATTR	3

#define HWC_BUS_CONNECTION_NAME_INDX	0
#define HWC_BUS_CONNECTION_CAT_INDX	1
/* #define HWC_BUS_CONNECTION_SCANTIME_INDX  2 - Defined in hwc_bus_ext.h */

#define HWC_BUS_CONNECTION_NUM_ATTR	3

#define HWC_BUS_UNCH_NAME_INDX	0
#define HWC_BUS_UNCH_CAT_INDX	1

#define HWC_BUS_UNCH_NUM_ATTR	2

#define HWC_BUS_LEGH_NAME_INDX	0
#define HWC_BUS_LEGH_CAT_INDX	1

#define HWC_BUS_LEGH_NUM_ATTR	2

#define SCAN_BUS		1
#define SCAN_CONNECTION		2
#define REMOVE_CONNECTION	3

/*
 * Definitions for the flags field of the hwc_connection_component_info
 * structure
 */
#define HWC_CONNECTION_LOCKED   1UL


/*
 * Scan bus and scan connection flags field definition
 *
 *	HWC_BUS_EHM_CALLBACK_NOPROBE	- Set this flag to tell the
 *					  bus code no to perform probe/attach
 *					  on devices discovered on the bus.
 *					  The code will just identify the 
 *					  device.
 */

#define HWC_BUS_EHM_CALLBACK_PROBE		0x00000001

struct bus_ehm_config_data
{
    struct hwc_bus_ehm_callback_info hwc_bus_ehm_callback_routines;
    struct hwc_bus_component_info *hwc_comp_info;
};

struct hwc_bus_ehm_mss_info
{
    int  	version_id;
    void 	**current_val;
    void 	**default_val;
    CMD_ELEM 	*commands;
    int 	(*mss_support_rtn)();
    ulong	arg;
    MSS  	*mss;
    void	*handle;
};

struct hwc_bus_component_info
{
    int		version;		/* Version field                     */
    struct hwc_connection_component_info
		*bus_connection;	/* Pointer to the HWC bus component  */
					/*  structure                        */
    struct bus	*bus;			/* Pointer to the bus structure      */
    void	*handle;		/* Pointer to the bus component's    */
					/*  handle                           */
    struct hwc_bus_ehm_mss_info
		mss_info;		/* Holds information about the mss   */
					/*  structure associated with this   */
					/*  component                        */
};

struct hwc_connection_component_info
{
    int		version_id;		/* Version field                     */
    struct hwc_connection_component_info
		*next_ptr;		/* Pointer to the next slot in the   */
					/*  linked list                      */
    int		phys_connection_num;	/* Connection's connection number    */
					/*   (no func #)                     */
    struct bus	*parent_bus;		/* Pointer to the parent's bus       */
    struct hwc_connection_function_info
		*connection_function_list;
					/* Pointer to linked list of slot    */
					/*  specific information             */
    void	*handle;		/* Pointer to the slot's hwc handle  */
    struct hwc_bus_ehm_mss_info
		mss_info;		/* Holds information about the mss   */
					/*  structure associated with this   */
					/*  component                        */
    ulong	flags;			/* Flags field			     */
};

struct hwc_connection_function_info
{
    int		version;		/* Version field                     */
    int		connection_func_num;	/* Composite connection number       */
					/*  (connection+func)                */
    struct hwc_connection_function_info
		*next_ptr;		/* Pointer to the next one in the    */
					/*  list                             */
    struct hwc_connection_component_info
		*parent_connection;	/* Pointer to our parent             */
    int		local_comp_type;	/* The type of any local components  */
					/*  the bus code may have registered */
    struct hwc_local_comp_info
		*local_comp_ptr;	/* Pointer to any local components   */
					/*  the bus code may have registered */
};

struct hwc_local_comp_info
{
    int		version_id;		/* Version field                     */
    int		connection_func_num;	/* Composite connection number       */
					/*  (slot+func)                      */
    int		type;			/* Type of component                 */
    struct hwc_connection_component_info *
		parent_connection;	/* Parent connection                 */
    void	*handle;		/* Pointer to the component handle   */
    struct hwc_bus_ehm_mss_info
		mss_info;		/* Holds information about the mss   */
					/*  structure associated with this   */
					/*  component                        */
};


struct hwc_bus_bus_attribute_values
{
    char	name[HWC_BUS_BUS_SZ_NAME];
    char	category[HWC_BUS_BUS_SZ_CAT];
    ulong	scantime;
};
    
struct hwc_bus_connection_attribute_values
{
    char	name[HWC_BUS_CONNECTION_SZ_NAME];
    char	category[HWC_BUS_CONNECTION_SZ_CAT];
    ulong	scantime;
};
    
struct hwc_bus_unch_attribute_values
{
    char	name[HWC_BUS_UNCH_SZ_NAME];
    char	category[HWC_BUS_UNCH_SZ_CAT];
};

struct hwc_bus_legh_attribute_values
{
    char	name[HWC_BUS_LEGH_SZ_NAME];
    char	category[HWC_BUS_LEGH_SZ_CAT];
};

extern struct hwc_connection_component_info*
hwcbus_find_connection(struct bus *bus,
                     int connection_func_num);

#ifdef __cplusplus
}
#endif

#endif	/* _HWC_BUS_INT_H_ */

