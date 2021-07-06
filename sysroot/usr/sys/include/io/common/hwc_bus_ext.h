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

#pragma ident "@(#)$RCSfile: hwc_bus_ext.h,v $ $Revision: 1.1.2.4 $ (DEC) $Date: 1999/03/11 22:06:49 $"

#ifndef _HWC_BUS_EXT_H_
#define _HWC_BUS_EXT_H_

#ifdef __cplusplus
extern "C" {
#endif

#define HWC_MAX_FCN_PER_CONNECTION	16
#define HWC_FCN_NUM_MULT		100

#define HWC_COMPONENT_UNCH	0x00000001
#define HWC_COMPONENT_LEGH	0x00000002
#define HWC_BUS_EHM_CALLBACK_PROBE		0x00000001

#define HWC_BUS_BUS_SCANTIME_INDX	2
#define HWC_BUS_CONNECTION_SCANTIME_INDX	2

#define HWCBUS_GET_FCN(x) ((x)/HWC_FCN_NUM_MULT)
#define HWCBUS_GET_SLOT(x) ((x)%HWC_FCN_NUM_MULT)
#define HWCBUS_SINGLE_FCN 1
#define HWCBUS_SLOT_FCN_TO_CMP(slot_num, fcn_num) \
	((slot_num) + (fcn_num)*HWC_FCN_NUM_MULT)


struct hwc_bus_ehm_callback_info
{
    int (*scan_bus)(struct bus *callback_bus_ptr,
                    u_long scan_bus_data,
                    void *scan_bus_data_ptr,
                    u_int flags);
    u_long scan_bus_data;
    void *scan_bus_data_ptr;

    int (*scan_connection)(struct bus *callback_bus_ptr,
                           int component_num,
                           u_long scan_connection_data,
                           void *scan_connection_data_ptr,
                           u_int flags);
    u_long scan_connection_data;
    void *scan_connection_data_ptr;

    int (*remove_connection)(struct bus *callback_bus_ptr,
                             int component_num,
                             u_long remove_connection_data,
                             void *remove_connection_data_ptr);
    u_long remove_connection_data;
    void *remove_connection_data_ptr;

    char *connection_name;
};

extern int
hwcbus_create_bus_comp(struct bus *bus);

extern int
hwcbus_initialize_bus_comp(struct bus *bus,
                           struct hwc_bus_ehm_callback_info *infop);

extern int
hwcbus_create_connection_comp(struct bus *bus,
                              int connection_num);

extern int
hwcbus_setup_connection_comp(struct bus *bus,
                             int connection_num);
 
extern int
hwcbus_create_local_comp(struct bus *bus,
                         int connection_func_num,
                         char *comp_cat,
                         int local_type);

extern int
hwcbus_remove_bus_comp(struct bus *bus);

extern int
hwcbus_remove_connection_comp(struct bus *bus, int component_func_num);

extern int
hwcbus_zero_connection_comp(struct bus *bus, int component_func_num);

extern int
hwcbus_remove_local_comp(struct bus *bus, int component_func_num);

extern int
hwcbus_set_bus_attribute(struct bus *bus, int attribute_index, void *attr);

extern int
hwcbus_set_connection_attribute(struct bus *bus, int component_func_num, 
                                int attribute_index, void *attr);

extern void
hwcbus_register_legacy_ctlr(struct bus *bus, struct controller *ctlr);

#ifdef __cplusplus
}
#endif

#endif	/* _HWC_BUS_EXT_H_ */

