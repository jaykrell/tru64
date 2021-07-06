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
#pragma ident "@(#)$RCSfile: hwc_reg.h,v $ $Revision: 1.1.51.6 $ (DEC) $Date: 2002/05/31 03:32:15 $"

#ifndef _HWC_REG_H_
#define _HWC_REG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <ksm/ksm.h>
#include <sys/table.h>
 
/*
 * Hardware components registered through the hwc_reg_hw() interface, 
 * are made available via the kernel set management (ksm) interface.
 *
 * RELATIONSHIPS
 * Upon registration a hardware component becomes a member of the 
 * Hardware Set.  There are 3 relationships established in the Hardware Set:
 * Category, Hierarchy, and MIB-id Relationships.  The flag field is used to 
 * control the establishment of these relationships.  For full access to this 
 * hardware component's information via the ksm interface, request that all 
 * relationships be established for this component member. (default)
 *
 * HARDWARE COMPONENT REGISTRATION
 * The version, opcode, flags, hw_name, and mgt_ss fields are mandatory for 
 * all registrations.
 *   version - This is the version of the HW_REG_REQ data structure being used.
 *
 *   opcode - This specifies the type of registration operation to perform.
 * 
 *      HWC_REGISTER - Opcode for general purpose registration.  Requires 
 *      valid parent_id and parent_inst
 *      
 *      HWC_REGISTER_BUS - Opcode for registering a bus component.  This
 *      opcode requires the topology_ds to point to the struct bus
 *      for this component.
 * 
 *      HWC_REGISTER_CTLR - Opcode for registering a controller component.
 *      This opcode requires the topology_ds to point to the controller
 *      struct for this component.
 *
 *      HWC_REGISTER_DEV - Opcode for registering a device component.  This
 *      opcode requires the topology_ds to point to the struct device 
 *      for this component.
 *
 *   flags - These specify various features about this component.
 *
 *      HW_REG_SHARED - Indicates that the hw_name is globally unique.  This 
 *      flag is required for any component that is attached to an interconnect 
 *      capable of being shared on the same or different host.
 *
 *      HW_REG_NO_CAT - Do not place this component in  the 
 *      category relationship with this registration request.
 *
 *      HW_REG_NO_HIER - Do not place this component in the
 *      hierarchy relationship with this registration request.
 *  
 *      HW_REG_NO_MIB - Do not place this component in the
 *      MIB-id relationship with this registration request
 *
 *      HW_REG_CMN_RTN - Indicates a common support routine is available for this 
 *      component. The cmn_support_rtn field must be initialize when this flag
 *      is set.
 *
 *      HW_REG_SUB_SYS - Indicates a module name is provided for the "owner"
 *      of this component. The module_name field must be initialize when this
 *      flag is set.
 * 
 *      HW_REG_STATE - Indicates an initial state is being
 *      provided.  The state field must be set.
 *
 *      HW_REG_COD - Indicates this component supports CCOD
 *      (Compaq Capacity on Demand)
 * 
 *      HW_REG_CAPABLE - Indicates that an initial capabilities
 *      attribute is being specified in reg_request.capabilities 
 *
 *
 *   hw_name - This must be a null-terminated string that uniquely identifies
 *      this hardware component. If the flag field indicates HW_REG_SHARED, this 
 *      name must be unique within a cluster.  If the HW_REG_SHARED flag is not
 *      set, the name must be unique within the host that the component resides.
 *             
 *   mgt_ss  - This is the address of an MSS structure as defined in ksm.h
 *      Multiple MSS structures may be registered for a hardware component. All
 *      registration calls for the same hardware component must supply the same
 *      hw_name so that the registration routine can properly process the requests 
 *      for the same hardware component.
 *             
 *   cat_name - This field supplies the name of the category to which this 
 *      component member belongs.  Any null-terminated string less than 
 *      KSM_CAT_NAME_SIZE can be used to specify a category.  The system provided 
 *      categories are listed below.  Unless the HW_REG_NO_CAT flag is set to indicate
 *      this hardware component does not belong to any category, the cat_name field 
 *      may not be NULL. 
 * 
 *   parent_id - The hardware member id for this component's parent.  Required
 *      with the HWC_REGISTER opcode.
 *
 *   parent_inst - The member instance number for this component's parent. 
 *      Required with the HWC_REGISTER opcode.
 *
 *   topology_ds - A pointer to a topology data structure. Required for the
 *      following opcodes: HWC_REGISTER_BUS, HWC_REGISTER_CTLR, HWC_REGISTER_DEV.
 *
 *      The Parent ID and Parent Instance are required for the Hierarchy Relationship.
 *      For the HWC_REGISTER_BUS, HWC_REGISTER_CTLR, HWC_REGISTER_DEV opcodes, the
 *      parent_id and parent_inst will be derived from the topology_ds.
 *   
 *   cmn_support_rtn() - A  pointer to the common support routine for this component
 *      member (or NULL).  Subsequent registration request supplying a different
 *      common support routine will fail with EINVAL.  The HW_REG_CMN_RTN flag must
 *      be set when providing a common support routine.
 * 
 *   cmn_arg - The argument (arg) to be supplied when the cmn_support_rtn() is 
 *      invoked.
 * 
 *   sub_sys_name - A char pointer to the string containing the name of the sub system
 *      that "owns" or is responsible for this component.
 *
 * OUTPUT FIELDS
 *
 * The following fields are returned by the registration routine
 *
 *    *lock - This is the pointer to the complex lock structure for the hardware
 *      member.  Subsequent access to the hardware component member and all the MSS
 *      structures attached to this member require the use of this lock.
 *
 *    hw_id - This is the unique hardware id assigned to this component. 
 *      this unique id can be used during configuration time (before the root file 
 *      system is writable) for registration purposes. For example, this hw_id can 
 *      be used as the parent_id for a subsequent configuration time registration. 
 *      NOTE: The hw_id assigned during hardware configuration may be a temporary id. 
 *      These ids should not be saved for use after the root file system becomes
 *      writable.
 *
 *   hw_inst - This is the instance number assigned for this component. It 
 *      is used to differentiate multiple instances of a component within the
 *      hierarchy relationship.
 *
 *   dev_handle - This points to the device's device handle upon successful 
 *      registration. The dev_handle is used for subsequent hwc_reg_devnode() calls
 *      for this device.
 *
 * STATUS VALUES
 * The hwc_reg_hw() return value is a status value with the following possible
 * values:
 *       ESUCCESS    - successful registration
 *       ENOMEM      - insufficient memory
 *       EINVAL      - invalid argument 
 *       ECHILD      - no such parent
 *       EALREADY    - already registered 
 *       EFAIL       - registration failed
 *       EACCESS     - too early to register
 *       EBUSY       - cannot register at this time (delete or replace occurring)
 *
 *====================================================================================
 * HARDWARE COMPONENT UN-REGISTRATION
 * The version, opcode, and dev_handle fields are mandatory for all un-registrations.
 *
 *   version - This is the version of the HW_REG_REQ data structure being used.
 *
 *   opcode - This specifies the type of un-registration operation to perform.
 * 
 *      HWC_UNREGISTER - Opcode for general purpose un-registration.  This requires
 *      the mgt_ss field to specify the mss field to be un-registered.
 *      
 *      HWC_UNREGISTER_FULL - Opcode for un-registering a hardware component,
 *      including all mss structures registered for this component, all set
 *      relationships, and multiple hierarchical relationships.
 * 
 *   flags - These specify various features about this un-registration.
 *
 *      HW_REG_NO_CAT - Do not remove this component from the
 *      category relationship with this un-registration request
 *
 *      HW_REG_NO_HIER - Do not remove this component from any
 *      hierarchy relationships with this un-registration request.
 *  
 *      HW_REG_NO_MIB - Do not remove this component from the
 *      MIB-id relationship with this un-registration request.
 *
 *   mgt_ss  - This is the address of an MSS structure as defined in ksm.h
 *      This field is required by the HWC_UNREGISTER opcode.
 *      If multiple MSS structures have been registered for a hardware component,
 *      either multiple un-registration calls can be made using HWC_UNREGISTER 
 *      opcode and specifying the individual MSS structure, or the 
 *      HWC_UNREGISTER_FULL opcode can be used.
 *             
 *
 *   hw_id - This is the unique hardware id that was assigned to this component
 *      during the hwc_reg_hw() call. 
 *      This field is optional and can be used when specifying a particular
 *      hw_id/hw_inst to un-register.  This field is ignored by the 
 *      HWC_UNREGISTER_FULL opcode.
 *
 *   hw_inst - This is the instance number that was assigned for this component
 *      during the hwc_reg_hw() call. This field is optional and can be used to
 *      specify a particular hw_id/hw_inst to un-register. This field is ignored
 *      by the HWC_UNREGISTER_FULL opcode.
 *
 *   dev_handle - This is the device's dev_handle that was assigned for this
 *      component during the hwc_reg_hw() call.
 *
 * STATUS VALUES
 * The hwc_unreg_hw() return value is a status value with the following possible
 * values:
 *       ESUCCESS    - successful un-registration
 *       EINVAL      - invalid argument 
 *       ECHILD      - no such instance found
 *       EFAIL       - un-registration failed
 *
 */

typedef struct hw_reg_req {
    int          version;      /* version of this structure                     */
    int          opcode;       /* requested operation                           */
    ulong        flags;        /* See hardware reg bit flags definitions below  */
    char         *hw_name;     /* unique name of the hardware component         */
    MSS          *mgt_ss;      /* address of required KSM structure             */
    char         *cat_name;    /* hardware category name for with this comp     */
    long         parent_id;    /* unique hardware id of parent                  */
    int          parent_inst;  /* instance number of parent within hierarchy    */
    void         *topology_ds; /* points to a struct struct bus, struct ctlr,   */
                               /* struct device, or NULL                        */
    lock_data_t  *lock;        /* lock for subsequent access to component       */
    long         hw_id;        /* unique hardware id of this member component   */
    int          hw_inst;      /* component's instance number within hierarchy  */
    void         *dev_handle;  /* device handle                                 */
    int         (*cmn_support_rtn)(KSM_MEM_REQ_BUF*, caddr_t, size_t, 
                                   caddr_t, size_t, ulong);
    ulong        cmn_arg;      /* member-supplied argument to common support rtn */
    ulong	 capabilities; /* init capabilities, req. HW_REG_CAPABLE */
    char         *module_name; /* module name associated with this component     */
    int		 state_idx;    /* initial state, requires HWC_REG_STATE flag */
} HW_REG_REQ;

/*
 * hardware registration opcodes
 */
#define HWC_REGISTER            0x000
#define HWC_REGISTER_BUS        0x001
#define HWC_REGISTER_CTLR       0x002
#define HWC_REGISTER_DEV        0x003
#define HWC_UNREGISTER          0x004
#define HWC_UNREGISTER_FULL     0x005
#define HWC_CHANGE_CATEGORY     0x100


/*
 * bit flags for hardware component registration
 */
#define HW_REG_SHARED    0x01   /* shared component                                      */
#define HW_REG_NO_CAT    0x02   /* do not register/unregister the category relationship  */
#define HW_REG_NO_HIER   0x04   /* do not register/unregister the hierarchy relationship */
#define HW_REG_NO_MIB    0x08   /* do not register/unregister the MIB-id relationship    */
#define HW_REG_CMN_RTN   0x10   /* common support routine provided                       */
#define HW_REG_SUB_SYS   0x20   /* module name provided */
#define HW_REG_STATE     0x40	/* initial state provided */
#define HW_REG_COD       0x80	/* component suports COD */
#define HW_REG_CAPABLE   0x100  /* initial capabilities provided */

#define HW_DELETE_INPROG 0x1000  /* used to tag component during delete                   */
#define HW_DEL_ON_REBOOT 0x2000  /* delete this hardware component upon reboot            */
#define HW_CLEANUP_CHWC  0x4000  /* clusterized hardware component (used by cleanup)      */
#define HW_DO_REFRESH    0x8000  /* refresh has to be performed on this hwdesc            */

/*
 * Device Nodes are registered through the hwc_reg_devnode() interface. 
 *
 * DEVICE NODE REGISTRATION
 *
 * The version, opcode, flags, hw_name, and mgt_ss fields are mandatory for 
 * all registrations.
 *   version - This is the version of the HW_REG_REQ data structure being used.
 *
 *   opcode - This specifies the type of registration operation to perform.
 *       DEVNODE_REGISTER - Opcode for general purpose registration.
 *       DEVNODE_REGISTER_SPEC_INST - Opcode for registering device nodes 
 *             with a specified instance number. The device instance_num is 
 *             specified by the caller in order to tell dsfmgr to use the 
 *             specified instance number when creating device special files 
 *             for this device, rather than determining the next available
 *             device instance number.
 *      
 *   dev_handle - The dev_handle is the value returned from the hwc_reg_hw() call
 *       for the hardware component associated with this device node.
 *
 *   basename_id - A number that is used to group related device nodes for a device.
 *       This group of related device nodes will all share the same device special
 *       file basename.  A non-zero basename_id indicates the caller is supplying
 *       the basename_id. A basename_id of 0 (zero) indicates the basename_id should 
 *       be determined by the hwc_devnode_reg() routine (see OUTPUT FIELDS below)
 * 
 *   dev_node_id -  The driver's internal id for this device node within the 
 *       group of device nodes that share the same basename_id.  This is used
 *       to distinguish one device notde within the group from other device nodes
 *       within the group. 
 *
 *   ldevt_blk - The block dev_t for this devnode. This field only needs to be 
 *       initialized if the HWC_DEVNODE_VALID flag is set in the flags_blk.
 *
 *   ldevt_char - The character dev_t for this devnode.  This field only needs to be 
 *       initialized if the HWC_DEVNODE_VALID flag is set in the flags_char.
 *
 *   flags_blk  - This specifies the various features specific to the block
 *        device special file
 *        
 *        HWC_DEVNODE_VALID
 *             set if there is a block device node to be registered. 
 *             ldevt_blk must be valid.
 *        HWC_DEVNODE_OLD_NODE
 *             set if this device node is for an old device special file
 *        HWC_DEVNODE_NO_MAP
 *             set if the device special file should be made with a local devt
 *        HWC_DEVNODE_LOCAL_ONLY
 *             set if i/o requests are to be made locally only - this flag is ignored 
 *             if HWC_DEVNODE_NO_MAP is set
 *        HWC_DEVNODE_NO_AUTOCREATE 
 *             set if the device speccial files should not be made automatically by
 *             dsfmgr - this flag is ignored if HWC_DEVNODE_OLD_NODE is set
 *
 *   flags_char - This specifies the various features specific to the character
 *        device special file
 *       (see flags_blk)
 *
 *   mapinfo  -   This field is used by any driver that i intercepting i/o requests
 *        through the mapping driver.  The mapping driver will pass this information
 *        to the intercepting driver.  For disk devices that do not set the 
 *        HWC_DEVNODE_LOCAL_ONLY bit, this field must be set to the partition mask 
 *        for this devt.  At this time, other devices must set this field to 0.
 *
 *   sub_system_name - A null terminated string representing the sub system name
 *        that is registering this device.  The maximum string length is 31
 *        (HWC_NAME_LEN - 1).  
 *
 *   dsf_suffix - NULL or a pointer to a null terminated string containing
 *        comma separated driver specific strings that will be used by dsfmgr to
 *        create the device special file name for this device node. 
 *        The format of this string is mandated by the device class to which the 
 *        device node belongs.
 *        The storage space for this string must remain available after the
 *        hwc_devnode_reg() invocation.
 *
 *        For example:
 *        Dev Nodes for disk devices indicate the partition letter.
 *        Dev Nodes for tape devices indicate the density.
 *
 *   dsf_lookup_s1 - NULL or a pointer to a null terminated string.  This string
 *        is used by the dsfmgr. The contents and format of this string is
 *        mandated by dsfmgr and the device class to which this device node
 *        belongs.  Typically, this string contains the device category name.
 *        The storage space for this string must remain available after the
 *        hwc_devnode_reg() invocation.
 *
 *   dsf_lookup_s2 - NULL or a pointer to a null terminated string.  This string
 *        is used by the dsfmgr.  The contents and format of this string is
 *        mandated by dsfmger and the device class to which this device node
 *        belongs.  Typically, this string contains the device sub-category
 *        name.  The storage space for this string must remain available
 *        after the hwc_devnode_reg() invocation.
 *
 *   dsf_lookup_s3_blk - NULL or a pointer to a null terminated string.  This 
 *        string is used by the dsfmgr.  The contents and format of this string
 *        is mandated by dsfmgr and the device class to which this device node
 *        belongs. Typically, this string contains some device specific type
 *        information. e.g.: "block"
 *        The storage space for this string must remain available after the
 *        hwc_devnode_reg() invocation.
 *
 *   dsf_lookup_s3_char - NULL or a pointer to a null terminated string.  This 
 *        string is used by the dsfmgr.  The contents and format of this string
 *        is mandated by dsfmgr and the device class to which this device node
 *        belongs. Typically, this string contains some device specific type
 *        information for the device. e.g.: "char" or "rewind" or "norewind"
 *        The storage space for this string must remain available after the
 *        hwc_devnode_reg() invocation.
 *
 *   old_dsfname_blk - NULL or a pointer to a null terminated string containing
 *        the basename that was used for this block oriented dev node prior
 *        to the implementation of the class-based device node namespace.
 *        The storage space for this string must remain available after the
 *        hwc_devnode_reg() invocation.
 * 
 *   old_dsfname_char - NULL or a pointer to a null terminated string containing
 *        the basename that was used for this character oriented dev node prior
 *        to the implementation of the class-based device node namespace.
 *        The storage space for this string must remain available after the
 *        hwc_devnode_reg() invocation.
 *
 *   instance_num - (Optional) used to specify the instance number dsfmgr
 *        should assign for this device.  If this field is used the
 *        DEVNODE_REGISTER_SPEC_INST opcode must be used. 
 *
 * OUTPUT FIELDS
 *
 * The following fields are returned by the registration routine
 * 
 *  basename_id - A number that is used to group related device nodes for a device.
 *       This group of related device nodes will all share the same device special
 *       file basename.  A non-zero basename_id indicates the caller is supplying
 *       the basename_id. A basename_id of 0 (zero) indicates the basename_id should 
 *       be determined by the hwc_devnode_reg() routine.  
 *       The hwc_devnode_reg() routine will determine the basename_id as follows:
 *          - dev_t is found in the database.  The existing basename_id is 
 *            provided and returned to the caller.
 *          - dev_t is not found in the database.  A new basename_id is created
 *
 *  dev_node - This points to the device's dev node handle upon successful 
 *        registration. 
 *
 * STATUS VALUES
 * The hwc_reg_devnode() return value is a status value with the following possible
 * values:
 *       ESUCCESS    - successful registration
 *       ENOMEM      - insufficient memory
 *       EINVAL      - invalid argument 
 *       EALREADY    - already registered 
 *       EFAIL       - registration failed
 *       EACCESS     - too early to register
 *
 *=============================================================================
 * Device Nodes are un-registered through the hwc_unreg_devnode() interface. 
 *
 * DEVICE NODE UN-REGISTRATION
 *
 * The version and opcode fields are mandatory for all un-registrations.
 *
 *   version - This is the version of the HW_REG_REQ data structure being used.
 *
 *   opcode - This specifies the type of un-registration operation to perform.
 *       DEVNODE_UNREGISTER - Opcode for general purpose un-registration of a 
 *             single devnode.
 *       DEVNODE_UNREGISTER_ALL - Opcode for un-registering all device nodes 
 *             associated with a dev_handle and sub_system_name.
 *      
 *   dev_handle - The dev_handle is the value returned from the hwc_reg_hw() call
 *       for the hardware component associated with this device node or nodes.
 *       This field is required by the DEVNODE_UNREGISTER_ALL opcode.
 *
 *   sub_system_name - A null terminated string representing the sub system name
 *       that is registering this device.  The maximum string length is 31
 *       (HWC_NAME_LEN - 1).  
 *       This field is required by the DEVNODE_UNREGISTER_ALL opcode.
 *
 *   dev_node - The dev_node is the value returned from the hwc_reg_devnode() call
 *       and is the device's dev node handle.
 *       This field is required by the DEVNODE_UNREGISTER opcode.
 *
 * STATUS VALUES
 * The hwc_unreg_devnode() return value is a status value with the following 
 * possible values:
 *       ESUCCESS    - successful unregistration
 *       EINVAL      - invalid argument 
 *
 */

typedef struct devnode_reg_req
{
  int    version;             /* version of this structure                     */
  int    opcode;              /* requested operation                           */
  void   *dev_handle;         /* the dev_handle pointer for this device        */
  long   basename_id;         /* the id used to group dev_ts for a device      */
   int   dev_node_id;         /* driver specific id within a devnode group     */
  dev_t  ldevt_blk;           /* the character oriented dev_t for this devnode */
  dev_t  ldevt_char;          /* the block oriented dev_t for this devnode     */
  uint   flags_blk;           /* flags for the block oriented devnode          */
  uint   flags_char;          /* flags for the character oriented devnode      */
  long   class_info;          /* info used by the map driver                   */
  char   *sub_sys_name;       /* subsystem name associated with this devnode   */
  char   *dsf_suffix;         /* driver specific name suffix                   */
  char   *dsf_lookup_s1;      /* name string used by dsfmgr (typ. category)    */
  char   *dsf_lookup_s2;      /* name string used by dsfmgr (typ. sub-category)*/
  char   *dsf_lookup_s3_blk;  /* name string used by dsfmgr (typ. type)        */
  char   *dsf_lookup_s3_char; /* name string used by dsfmgr (typ. type)        */
  char   *old_dsfname_blk;    /* old block oriented basename                   */
  char   *old_dsfname_char;   /* old character oriented basename               */
   int   instance_num;        /* device instance number (optional)             */
  void   *dev_node;           /* returned device node pointer                  */
} DEVNODE_REG_REQ;

#define DEVNODE_REGISTER                0x001
#define DEVNODE_REGISTER_SPEC_INST      0x002
#define DEVNODE_UNREGISTER              0x003
#define DEVNODE_UNREGISTER_ALL          0x004

#define HWC_DEVNODE_VALID               0x00001
#define HWC_DEVNODE_OLD_NODE            0x00002
#define HWC_DEVNODE_NO_MAP              0x00004
#define HWC_DEVNODE_LOCAL_ONLY          0x00008
#define HWC_DEVNODE_NO_AUTOCREATE       0x00010
#define HWC_DEVNODE_DSF_MADE            0x00020
#define HWC_DEVNODE_REG                 0x00040
#define HWC_DEVNODE_INST_VALID          0x00080
#define HWC_DEVNODE_UNREG               0x00100
#define HWC_DEVNODE_PROC                0x00200
#define HWC_DEVNODE_NO_DSF_NOTIFY       0x00400
#define HWC_DEVNODE_LOCAL               0x00800

/*
 * Attributes are saved through the hwc_save_attribute() interface. 
 *
 * HWC SAVE ATTRIBUTE
 * The version, opcode, dev_handle, mss, and attr_index fields are mandatory 
 * for the save attribute operation.
 * 
 *   version - This is the version of the HWC_ATTR_REQ data structure being used.
 *
 *   opcode - This specifies the type of attribute operation to perform.
 * 
 *      HWC_ATTRIBUTE_SAVE - Opcode for saving a specified attribute.
 *      HWC_ATTRIBUTE_REMOVE - Opcode for removing a specified attribute.
 *
 *   dev_handle - The dev_handle is the value returned from the hwc_reg_hw() call
 *       for the hardware component associated with this attribute.
 *
 *   mss - The address of the MSS structure that was registered for a hardware
 *       component. This mss must contain the pointers to attribute table 
 *       (attr_table), the default_value arrary of pointers (default_val), and
 *       the saved_value arrary of pointers (saved_val) for the attribute
 *       that will be operated on.
 *
 *   attr_index - The index into the attribute_table of the attribute to be
 *       operated on.
 *
 * STATUS VALUES
 * The hwc_save_attribute() return value is a status value with the following possible
 * values:
 *       ESUCCESS    - success
 *       EINVAL      - invalid argument 
 *       EFAIL       - operation failed
 */
typedef struct hwc_attr_req
{
  int    version;             /* version of this structure                     */
  int    opcode;              /* requested operation                           */
  void   *dev_handle;         /* the dev_handle pointer for this device        */
  MSS    *mss;		      /* the pointer to the MSS structure containing   */
                              /*  the attribute table for this attribute       */
  uint   attr_index;          /* the attribute table index of the attribute    */
} HWC_ATTR_REQ;

#define HWC_ATTRIBUTE_SAVE    0x001
#define HWC_ATTRIBUTE_REMOVE  0x002

/*
 * The operating state of a hardware component is set/changed through the
 * hwc_set_access_state() interface.  This routine takes a
 * 
 * ACCESS_STATE_SET_REQ data structure:
 * 
 *   version - This is the version of the ACCESS_STATE_SET_REQ data
 *       structure being passed.
 *
 *   opcode - This specifies the type of attribute operation to perform.
 * 
 *       HWC_OP_SET_ACCESS_STATE - set the access_state attribute
 *       HWC_OP_CHANGE_ACCESS_STATE - change the access_state attribute
 *
 *   flags - Set this field to zero for this version.
 *
 *   dev_handle - The dev_handle is the value returned from the hwc_reg_hw()
 *       call for the hardware component associated with this attribute.
 *
 *   req_state - The (new) requested state for this hardware component.
 *
 * STATUS VALUES
 * This routine will return one of these possible values:
 *       ESUCCESS    - success
 *       EINVAL      - invalid argument 
 *       EFAIL       - operation failed
 */

typedef struct access_state_set_req {
  int		version;		/* version of this structure       */
  int		opcode;			/* requested operation             */
  ulong		flags;			/* flags for this request          */
  void		*dev_handle;		/* hardware component handle       */
  int           req_access_state;       /* requested access_state          */
} ACCESS_STATE_SET_REQ;

#define HWC_OP_SET_ACCESS_STATE	0x01	/* set access_state                */
#define HWC_OP_CHANGE_ACCESS_STATE 0x02	/* change existing access_state    */

#define HWC_ACCESS_STATE_INVALID 0x00	/* invalid/illegal access_state value */
#define HWC_ACCESS_STATE_OFFLINE 0x01	/* hw component is offline */
#define HWC_ACCESS_STATE_ONLINE	 0x02	/* hw component is online */
        /*
	 * Insert new access_states here - but you must verify that the new
	 * access_state is okay with:
	 *   - SMS - they have a different "picture" for each access_state
	 *   - MIB agents - they convert our states to their states
	 */
#define HWC_ACCESS_STATE_MAX  HWC_ACCESS_STATE_ONLINE	/* maximum valid */

/*
 * The operating state of a hardware component is set/changed through the
 * hwc_set_state() interface.  This routine takes a STATE_SET_REQ parameter.
 *
 * STATE_SET_REQ data structure
 * 
 *   version - This is the version of the STATE_SET_REQ data structure
 *       being passed.
 *
 *   opcode - This specifies the type of attribute operation to perform.
 * 
 *       HWC_OP_SET_STATE - set the value of the state attribute
 *       HWC_OP_CHANGE_STATE - change the value of the state attribute
 *
 *   flags - Set this field to zero for this version.
 *
 *   dev_handle - The dev_handle is the value returned from the hwc_reg_hw()
 *       call for the hardware component associated with this attribute.
 *
 *   req_state - The (new) requested state for this hardware component.
 *
 * STATUS VALUES
 * This routine will return one of these possible values:
 *       ESUCCESS    - success
 *       EINVAL      - invalid argument 
 *       EFAIL       - operation failed
 */

typedef struct state_set_req {
  int		version;		/* version of this structure       */
  int		opcode;			/* requested operation             */
  ulong		flags;			/* flags for this request          */
  void		*dev_handle;		/* hardware component handle       */
  int           req_state;              /* requested state of the hardware */
} STATE_SET_REQ;

#define HWC_OP_SET_STATE	0x01	/* set state to requested value    */
#define HWC_OP_CHANGE_STATE	0x02	/* change state to requested value */

#define HWC_STATE_UNKNOWN	0x00	/* state cannot be detected */
#define HWC_STATE_AVAILABLE	0x01	/* usable, no known problems */
#define HWC_STATE_LIMITED	0x02	/* usable, some problems */
#define HWC_STATE_UNAVAILABLE	0x03	/* not usable, gone or broken */
#define HWC_STATE_BROKEN	0x04	/* not usable, has problems */
#define HWC_STATE_TESTING	0x05	/* not usable, being tested */
#define HWC_STATE_OFF		0x06	/* not usable, off */
        /*
	 * Insert new states here - but you have to check that any new
	 * state is okay with:
	 *   - SMS - they have a different "picture" for each state
	 *   - MIB agents - they convert our states to their states
	 */
#define HWC_STATE_MAX		HWC_STATE_OFF	/* maximum valid state */

/*
 * Offset values for the return arguments of a GET_STATUS request.
 * Note that we also use these as the class of the argument.
 */
#define HWC_ARG_GS_HWID		0	/* hardware ID */
#define HWC_ARG_GS_SSUMMARY	1	/* short summary */
#define HWC_ARG_GS_SUMMARY	2	/* summary */
#define HWC_ARG_GS_ACCESS	3	/* access state */
#define HWC_ARG_GS_HEALTH	4	/* health state */
#define HWC_ARG_GS_INDICT_PROB	5	/* indicted probability */
#define HWC_ARG_GS_COD_STATE	6	/* capacity on demand state */
#define HWC_ARG_GS_NAME		7	/* component name */
#define HWC_ARG_GS_NUM		8	/* number of arguments */

/*
 * Registration data structure used when calling the disk registration
 * routine.  This is version 1 of this data structure.
 */

typedef struct diskmajor_reg_req {
  int		version;		/* version of this structure       */
  int		opcode;			/* requested operation             */
  ulong		flags;			/* flags for this request          */
  char		*driver_name;		/* driver name                     */
  int		dsr_instance;		/* reservation instance number     */
  int		major_req;		/* requested major number          */
  struct dsent	*dsent_ptr;		/* pointer to device switch entry  */
  int		major;			/* assigned major number           */
  int		(*presto_rtn)();	/* pointer to presto routine       */
} DISKMAJOR_REG_REQ;

/*
 * The operation codes for the disk major number registration request
 * structure.
 */

#define HWC_OP_REG_DISKMAJOR	0x01	/* register a disk major number    */
#define HWC_OP_REG_PRESTO	0x02	/* register presto                 */
#define HWC_OP_DEREG_DISKMAJOR	0x03	/* deregister a disk major number  */
#define HWC_OP_DEREG_PRESTO	0x04	/* deregister presto               */

/*
 * The flag bits for the disk major number registration request structure
 * (flags field)
 */

#define HWC_FL_OLD_MAJOR	0x01	/* old disk major number           */

/*
 * This table describes which fields in the request structure are
 * initialized by the caller (C) and which fields in the request structure
 * are initialized by the hwc_reg_diskmajor routine (R).  This depends on the
 * operation code being requested.
 *
 * OPERATION CODE  REG_D    REG_P    DEREG_D  DEREG_P
 * 
 * version . . . . C        C        C        C
 * opcode  . . . . C        C        C        C
 * flags . . . . . C        C        C        C
 * driver_name . . C                 C
 * dsr_instance  . C                 C
 * major_req . . . C
 * dsent_ptr . . . C
 * major . . . . . R
 * presto_rtn  . .          C
 */

/*
 * Data structure used to track the registered disk driver major numbers.
 */

typedef struct hwc_disk_major {
  struct hwc_disk_major *next_dm;	/* pointer to next structure       */
  ulong		flags;			/* flags for this disk driver      */
  char		*driver_name;		/* driver name                     */
  int		dsr_instance;		/* reservation instance number     */
  struct dsent	*dsent_ptr;		/* pointer to device switch entry  */
  int		major;			/* assigned major number           */
} HWC_DISK_MAJOR;

/*
 * The flag bits for the disk driver data structure (flags field)
 */

#define HWC_MAJOR_ASSIGNED	0x01	/* major number has been assigned  */
#define HWC_PRESTOIZED		0x02	/* presto controls major number    */
#define HWC_OLD_MAJOR		0x04	/* old disk major number           */

/*
 * HWC_DISKSTAT_REQ
 * 
 * Disk drivers register their "get-statistics" routines for all of the
 * drives on the system by calling hwc_reg_diskstat(). The "get-statistics"
 * routine will be called by hwc_get_diskstat() whenever a table(2)
 * syscall is made that specifies id=TBL_DKINFO.
 *
 * Drivers can unregister the statistics routine using hwc_unreg_diskstat().
 *
 * The version, drv_statfunc, drv_handle and dev_handle fields are mandatory
 * to register and unregister "get-statistics" routines:
 * 
 *   version - This is the version of the HWC_DISKSTAT_REQ data structure
 *	being used.
 *
 *   opcode - Unused, reserved for future variants of hwc_reg_diskstat().
 *
 *   flags - flags for this request (none yet defined) 
 * 
 *   dvr_handle - The drv_handle is specified by a driver when it calls
 * 	hwc_reg_diskstat.  This handle specifies the disk for which 
 * 	statistics are requested when calling the routine pointed to
 * 	by the previous field, "statfunc".
 * 
 *   dvr_statfunc - This field is specified by the driver when it calls
 *	hwc_reg_diskstat.  It holds the 64-bit address of the driver
 *	routine to call to retrieve statistics for a disk specified
 * 	by "drv_handle".
 * 
 *   dev_handle - The hardware configuration (hwc) device handle associated
 * 	with this disk drive.
 * 
 *   dstat_i - This field is returned to the driver when it calls 
 * 	hwc_reg_diskstat.  It is an index into the hwc_diskstat
 * 	table for this disk.
 */
typedef struct hwc_diskstat_req {
    int    version;        	/* version of this structure */
    int    opcode;         	/* requested operation */
    ulong  flags;		/* request flags (none yet defined) */
    void   *dvr_handle;   	/* driver's reference handle to this disk */
    int    (*dvr_statfunc)(void *, struct tbl_dkinfo *); 
				/* address of driver statistics function */
    void   *dev_handle;		/* hwc dev_handle for hardware management */
    int    dstat_i;             /* hwc disk statistics table index */
    struct tbl_dkinfo *dkinfo;	/* -->dkinfo struct to hold statistics */
} HWC_DISKSTAT_REQ;

/*
 * The operation codes for the disk statistics registration request
 * structure.
 */
#define HWC_OP_REG_DISKSTAT	0x01	/* register disk statistics routine */
#define HWC_OP_DEREG_DISKSTAT	0x02	/* deregister disk stat's routine   */
#define HWC_OP_GET_STATISTICS	0x03	/* get disk statistics              */
    
/*
 * This table describes the request structure fields that are initialized
 * by the caller (C) and the request structure fields that are initialized
 * by the hwc_reg_diskstat and hwc_get_statistics routines (R).
 *
 * OPERATION CODE:	REG	DEREG	GET
 * 
 * version . . . . . . .C	C	C
 * opcode  . . . . . . .C	C	C
 * flags . . . . . . . .C	C	C
 * dvr_handle. . . . . .C
 * dvr_statfunc. . . . .C
 * dev_handle. . . . . .C
 * dstat_i . . . . . . .R	C	C
 * dkinfo. . . . . . . .		C
 */

/*
 * This defines a hwc disk statistics dispatch table entry. To retrieve
 * disk statistics, hwc maintains a table of entries used to dispatch
 * directly to the drivers' "get-statistics" routines.
 */
typedef struct hwc_diskstat_ent {
    void *dvr_handle;	    /* driver's reference handle to this disk */
    int  (*dvr_statfunc)(void *, struct tbl_dkinfo *);
			    /* address of driver statistics function */
    void *dev_handle;	    /* hwc's reference handle to this disk drive */
} HWC_DISKSTAT_ENT;    

/*
 * Config Tree/FRU Table information is registered via hwc_reg_ctft()
 * Config Tree/FRU Table information is retrieved  via hwc_get_ctft()
 *
 * HWC_REG_CTFT
 *
 * All fields must be initialized by the caller
 *
 *   version - the version of the HWC_CTFT_REQ data structure being used
 *
 *   opcode - specifies the type of operation to perform
 *
 *      HWC_CTFT_REGISTER - Opcode for setting the CTFT data
 *
 *   dev_handle - initialize to be the value returned from the hwc_reg_hw()
 *       call for the hardware component associated with this attribute
 *
 *   flags - set to zero
 *
 *   cfg_tree_type     - Config tree type
 *   cfg_tree_subtype  - Config tree subtype
 *   cfg_tree_id       - Config tree id
 *   fru_table_type    - FRU table type
 *   fru_table_subtype - FRU table subtype
 *   fru_table_id      - FRU table id 
 *
 * The hwc_reg_ctft() return value is a status value with the following
 * possible values:
 *   ESUCCESS - successful request
 *   EINVAL   - invalid argument 
 *   ENOMEM   - too early to make this request
 *
 * ============================================================================
 * HWC_GET_CTFT
 *
 * The following fields must be initialized by the caller:
 *
 *   version - the version of the HWC_CTFT_REQ data structure being used
 *
 *   opcode - specifies the type of operation to perform
 *
 *      HWC_CTFT_GET - Opcode for getting the CTFT data
 *
 *   dev_handle - initialize to be the value returned from the hwc_reg_hw()
 *       call for the hardware component associated with this attribute
 *
 *   flags - set to zero
 *
 * Upon a successful request, the following fields will be initialized by hwc:
 *
 *   flags
 *     If there is CT information, HWC_FL_CT_VALID will be set
 *     If there is FT information, HWC_FL_FT_VALID will be set
 *
 *   cfg_tree_type     - Config tree type    (zero if no ct information)
 *   cfg_tree_subtype  - Config tree subtype (zero if no ct information)
 *   cfg_tree_id       - Config tree id      (zero if no ct information)
 *   fru_table_type    - FRU table type      (zero if no ft information)
 *   fru_table_subtype - FRU table subtype   (zero if no ft information)
 *   fru_table_id      - FRU table id        (zero if no ft information)
 *
 * The hwc_get_ctft() return value is a status value with the following
 * possible values:
 *   ESUCCESS - successful request
 *   EINVAL   - invalid argument 
 *   ENOMEM   - too early to make this request
 */
typedef struct hwc_ctft_req
{
  int    version;             /* version of this structure                 */
  int    opcode;              /* requested operation                       */
  void   *dev_handle;         /* the dev_handle pointer for this device    */
  ulong  flags;               /* flags                                     */
  long   cfg_tree_type;       /* the config tree type                      */
  long   cfg_tree_subtype;    /* the config tree subtype                   */
  long   cfg_tree_id;         /* the config tree id                        */
  long   fru_table_type;      /* the FRU table type                        */
  long   fru_table_subtype;   /* the FRU table subtype                     */
  long   fru_table_id;        /* the FRU table id                          */
} HWC_CTFT_REQ;

#define HWC_CTFT_REGISTER 0x001
#define HWC_CTFT_GET      0x002

#define HWC_FL_CT_VALID   0x0001
#define HWC_FL_FT_VALID   0x0002

/*
 * function prototypes
 */
extern int hwc_reg_hw( HW_REG_REQ *);
extern int hwc_unreg_hw( HW_REG_REQ *);
extern MSS *hwc_new_mss(void);
extern void hwc_free_mss(MSS *);
extern int hwc_reg_devnode( DEVNODE_REG_REQ *);
extern int hwc_unreg_devnode( DEVNODE_REG_REQ *);
extern int hwc_save_attribute( HWC_ATTR_REQ *);
extern int hwc_reg_diskmajor( DISKMAJOR_REG_REQ *);
extern int hwc_reg_diskstat( HWC_DISKSTAT_REQ *);
extern int hwc_unreg_diskstat( HWC_DISKSTAT_REQ *);
extern int hwc_get_diskstat( HWC_DISKSTAT_REQ *);
extern int hwc_reg_ctft( HWC_CTFT_REQ *);
extern int hwc_get_ctft( HWC_CTFT_REQ *);
extern char *hwc_get_hw_name(void *dev_handle);
extern long hwc_get_hw_id(void *dev_handle);
extern int hwc_is_registered(char *name, long hwid);
extern int hwc_set_state(STATE_SET_REQ *);

extern long hwc_devt2hwid(dev_t t, int devtype, int local);  
       /*
        * devtype is S_IFBLK or S_IFCHR)
        * local (1) - do not search cluster database 
        *       (0) - include searching cluster database
        * RESTRICTIONS: local=0 requires caller to block if
        *               cluster database is being updated.
        * returns: hwid or 0L
        */

extern dev_t hwc_hwid2devt(ulong hwid, char *suffix, int local, int borc);  
       /*
        * hwid   - hardware id of the component 
        * suffix - suffix of the device special file of the desired devt
        *          NULL if no suffix
        * local  - 1 = local devt desired
        *          0 = cluster devt desired
        * borc   - block or character devt value
        *          S_IFBLK = block devt value desired
        *          S_IFCHR = char devt value desired
        * RESTRICTIONS: the component represented by the hardware id
        *          must be registered (locally) with hwc. This routine 
        *          cannot return cluster devts when the device special file
        *          has not yet been made.
        *
        * returns: desired devt or NODEV
        */

/*
 *  Hardware Registration Callback priorities
 *  The initialization of Hardware Registration occurs after CFG_PT_LOCK_AVAIL,
 *  with a priority of HWC_INIT_PRIORITY. (HWC_INIT_PRIORITY is KDS_PRIORITY + 100.)
 *  The platform must be the first component to register in the Hardware Set.
 *  All other components can register any time after platform.
 */
#define HWC_INIT_PRIORITY       100 + 100               /* KDS_PRIORITY + 100 */
#define HWC_PLATFORM_PRIORITY   HWC_INIT_PRIORITY + 100   
#define HWC_REGISTER_PRIORITY   HWC_PLATFORM_PRIORITY + 100

/*
 *  The set name of the Hardware Set
 */
#define HWC_HARDWARE_SET         "hardware"

/*****************************************************************************
 *  Hardware Configuration Categories                                        *
 *  Note: These names cannot be longer than KSM_CAT_NAME_SIZE - 1 [31]       *
 *****************************************************************************/
#define HWC_CAT_UNDEFINED	 "undefined"
#define HWC_CAT_ADAPTER          "adapter"
#define HWC_CAT_BUS              "bus"
#define HWC_CAT_CLUSTER_INTER	 "cluster_interconnect"
#define HWC_CAT_CONSOLE          "console"
#define HWC_CAT_CONTROL_PORT     "control_port"
#define HWC_CAT_CPU              "cpu"
#define HWC_CAT_DISK             "disk"
#define HWC_CAT_ENV_MONITOR      "env_monitor"
#define HWC_CAT_FAN              "fan"
#define HWC_CAT_FIBRECHAN        "fibrechannel_adapter"
#define HWC_CAT_GENERIC          "generic"
#define HWC_CAT_GRAPHICS_CTLR    "graphics_controller"
#define HWC_CAT_I2O_CTLR         "i2o_controller";
#define HWC_CAT_IDE_ADAPTER	 "ide_adapter"
#define HWC_CAT_KEYBOARD         "keyboard"
#define HWC_CAT_LEGACY_HW        "legacy_driver"
#define HWC_CAT_MEDIA_CHANGER    "media_changer"
#define HWC_CAT_MEMORY           "memory"
#define HWC_CAT_MONITOR          "monitor"
#define HWC_CAT_NETWORK          "network"
#define HWC_CAT_PARALLEL_PORT    "parallel_port"
#define HWC_CAT_PLATFORM         "platform"
#define HWC_CAT_POINTER          "pointer"
#define HWC_CAT_POWER            "power_supply"
#define HWC_CAT_SA_ADAPTER       "smart_array_adapter"
#define HWC_CAT_SCSI_ADAPTER     "scsi_adapter"
#define HWC_CAT_SCSI_BUS         "scsi_bus"
#define HWC_CAT_SCSI_CTLR	 "scsi_adapter"
#define HWC_CAT_SENSOR           "sensor"
#define HWC_CAT_SERIAL_PORT      "serial_port"
#define HWC_CAT_SLOT             "connection"
#define HWC_CAT_SOUND_CTLR       "sound_controller"
#define HWC_CAT_TAPE             "tape"
#define HWC_CAT_UNCONF_HW        "unconfigured_hardware"
#define HWC_CAT_USB              "usb"
#define HWC_CAT_VIDEO_CTLR       "video_controller"

   /* Sub-Category */
#define HWC_SUBCAT_GENERIC       "generic"
#define HWC_SUBCAT_PRINTER       "printer"
#define HWC_SUBCAT_TERMINAL      "terminal"
#define HWC_SUBCAT_BUILDING_BLOCK "building_block"

   /* Disk Sub-Categories */
#define HWC_DISK_SUBCAT_FLOPPY   "floppy" 
#define HWC_DISK_SUBCAT_CDROM    "cdrom"
#define HWC_DISK_SUBCAT_WORM     "worm"
#define HWC_DISK_SUBCAT_MAGOPT   "magneto_optical"

   /* Port Sub-Categories */
#define HWC_PORT_SUBCAT_STORAGE  "storage"
#define HWC_PORT_SUBCAT_GENERIC_STOR  "sgeneric"

   /* Other strings */
#define HWC_CONTROL              "control"
#define HWC_PORT                 "port"

/* Summary status values */
/* Note: max string length is HWC_STATE_STR_MAX */
#define HWC_GOOD                 "good"
#define HWC_WARNING              "warning"
#define HWC_CRITICAL             "critical"
#define HWC_INACTIVE             "inactive"

/* Short summary status values */
/* Note: max string length is 2 (including the null terminator) */
#define HWC_SHORT_GOOD           " "
#define HWC_SHORT_WARNING        "!"
#define HWC_SHORT_CRITICAL       "X"
#define HWC_SHORT_INACTIVE       "-"

/* State values */
/* Note: max string length is HWC_STATE_STR_MAX */
#define HWC_UNKNOWN              "unknown"
#define HWC_AVAILABLE            "available"
#define HWC_LIMITED              "limited"
#define HWC_UNAVAILABLE          "unavailable"
#define HWC_BROKEN               "broken"
#define HWC_TESTING              "testing"
#define HWC_OFF                  "off"

/* Access state values */
/* Note: max string length is HWC_STATE_STR_MAX */
#define HWC_ONLINE               "online"
#define HWC_OFFLINE              "offline"
#define HWC_FROZEN               "frozen"

/* Capacity on demand state values */
/* Note: max string length is HWC_STATE_STR_MAX */
#define HWC_PURCHASED            "purchased"
#define HWC_ON_LOAN              "on_loan"
#define HWC_SPARE                "spare"

/* Indicted probability string values */
/* Note: max string length is HWC_STATE_STR_MAX */
#define HWC_LOW                  "low"
#define HWC_MEDIUM               "medium"
#define HWC_HIGH                 "high"

/* String needed for state change events */
#define HWC_DISABLED             "disabled"
#define HWC_INDICTED             "indicted"
#define HWC_ENABLED              "enabled"

/*
 * Define the bit mask for the "capabilities" attribute
 */
#define HWC_CAPABLE_POWER	0x1

/*
 * Define the index values for each of the common attributes.  This
 * must align with the common attributes table in the hwc module.  We
 * also define the maximum size of some of the string values for some
 * of the attributes.
 */
#define HWC_CMN_I_REG_TIME         0
#define HWC_CMN_I_USER_NAME        1
#define HWC_CMN_I_LOCATION         2
#define HWC_CMN_I_SW_MODULE        3
#define HWC_CMN_I_STATE            4
#define HWC_CMN_I_STATE_PREV       5
#define HWC_CMN_I_STATE_TIME       6
#define HWC_CMN_I_EVENT_COUNT      7
#define HWC_CMN_I_EVENT_TIME       8
#define HWC_CMN_I_ACCESS_STATE     9
#define HWC_CMN_I_ASTATE_TIME     10
#define HWC_CMN_I_CAPABILITIES    11
#define HWC_CMN_I_INDICTED        12
#define HWC_CMN_I_INDICTED_PROB   13
#define HWC_CMN_I_INDICTED_URG    14
#define HWC_CMN_I_DISABLED        15
#define HWC_CMN_NUM_ATTR          16 /* number of common attributes */    

#define HWC_USERNAME_STR_MAX       16 /* max size of the user_name string */
#define HWC_LOCATION_STR_MAX       24 /* max size of the location string  */
#define HWC_STATE_STR_MAX          12 /* max size of the state string */
#define HWC_ACCESS_STATE_STR_MAX    8 /* max size of the access_state string */

/*
 * These are for strings that are in category specific tables, but
 * could be in more than one.  This way applications are guaranteed
 * a maximum size for these strings.
 */
#define HWC_MODEL_STR_MAX    32
#define HWC_FIRMWARE_STR_MAX 16
#define HWC_VENDOR_STR_MAX   16

/*
 * Define the index values for the common bus attributes
 */
#define HWC_I_NAME                0
#define HWC_I_CATEGORY            1
#define HWC_BUS_NUM_ATTR          2 /* number of bus attributes */

/*
 * Define the index values for each of the common disk attributes.  This
 * must align with the common disk attributes table in the hwc module.
 */
#define HWC_DISK_I_NAME            0
#define HWC_DISK_I_CATEGORY        1
#define HWC_DISK_I_SUB_CAT         2
#define HWC_DISK_I_ARCH            3
#define HWC_DISK_I_PHYS_LOC        4
#define HWC_DISK_I_DEV_NAME        5
#define HWC_DISK_I_ACCESS          6
#define HWC_DISK_I_CAPACITY        7
#define HWC_DISK_I_BLOCK_SIZE      8 
#define HWC_DISK_I_OPEN_PART       9
#define HWC_DISK_I_PART_MINOR     10
#define HWC_DISK_I_ARCH_MINOR     11
#define HWC_DISK_I_PART_0_PATT    12
#define HWC_DISK_I_PART_0_SIZE    13
#define HWC_DISK_I_PART_1_PATT    14
#define HWC_DISK_I_PART_1_SIZE    15
#define HWC_DISK_I_PART_2_PATT    16
#define HWC_DISK_I_PART_2_SIZE    17
#define HWC_DISK_I_PART_3_PATT    18
#define HWC_DISK_I_PART_3_SIZE    19 
#define HWC_DISK_I_PART_4_PATT    20
#define HWC_DISK_I_PART_4_SIZE    21
#define HWC_DISK_I_PART_5_PATT    22
#define HWC_DISK_I_PART_5_SIZE    23
#define HWC_DISK_I_PART_6_PATT    24
#define HWC_DISK_I_PART_6_SIZE    25
#define HWC_DISK_I_PART_7_PATT    26
#define HWC_DISK_I_PART_7_SIZE    27
#define HWC_DISK_I_MAX_XFER       28
#define HWC_DISK_I_MODEL          29
#define HWC_DISK_I_SERIAL_NUM     30
#define HWC_DISK_I_PWRMGMT_CAP    31
#define HWC_DISK_I_BOOT_CAP       32
#define HWC_DISK_NUM_ATTR         33 /* number of common disk attributes */

#define HWC_DISK_PART_MINOR_MASK  0xffffffc0
#define HWC_DISK_ARCH_MINOR_MASK  0xffc003ff
#define HWC_DISK_PART_0_PATT      0x00
#define HWC_DISK_PART_1_PATT      0x01
#define HWC_DISK_PART_2_PATT      0x02
#define HWC_DISK_PART_3_PATT      0x03
#define HWC_DISK_PART_4_PATT      0x04
#define HWC_DISK_PART_5_PATT      0x05
#define HWC_DISK_PART_6_PATT      0x06
#define HWC_DISK_PART_7_PATT      0x07
#define HWC_DISK_ACCESS_READABLE    0x01
#define HWC_DISK_ACCESS_WRITEABLE   0x02
#define HWC_DISK_ACCESS_SHAREABLE   0x04
#define HWC_DISK_ACCESS_WRITE_PROT  0x08
#define HWC_DISK_ACCESS_REMOVEABLE  0x10

/*
 * Define the index values for the common medium changer attributes.
 */
#define HWC_CHANGER_I_NAME            0
#define HWC_CHANGER_I_CATEGORY        1
#define HWC_CHANGER_I_ARCH            2
#define HWC_CHANGER_I_PHYS_LOC        3
#define HWC_CHANGER_I_DEV_NAME        4
#define HWC_CHANGER_I_MODEL           5
#define HWC_CHANGER_NUM_ATTR          6 /* number of common changer attributes */

/*
 * Define the index values for each of the common tape attributes.  This
 * must align with the common tape attributes table in the hwc module.
 */
#define HWC_TAPE_I_NAME            0
#define HWC_TAPE_I_CATEGORY        1
#define HWC_TAPE_I_ARCH            2
#define HWC_TAPE_I_PHYS_LOC        3
#define HWC_TAPE_I_DEV_NAME        4
#define HWC_TAPE_I_MODEL           5
#define HWC_TAPE_NUM_ATTR          6 /* number of common tape attributes */

/*
 * Define the index values for power management related attributes.
 */
#define HWC_PWRMGMT_I_ENABLED      0
#define HWC_PWRMGMT_NUM_ATTR       1 /* number of pwr mgmt attributes */

/*
 * Define the index values for each of the common control-port attributes.
 * This must align with the common control-port attribute table in the hwc
 * module.
 */
#define HWC_PORT_I_NAME      0
#define HWC_PORT_I_CATEGORY  1
#define HWC_PORT_I_SUB_CAT   2
#define HWC_PORT_I_ARCH      3
#define HWC_PORT_I_PHYS_LOC  4
#define HWC_PORT_I_DEV_NAME  5
#define HWC_PORT_I_MODEL     6
#define HWC_PORT_I_NUM_ATTR  7 /* number of common control port attributes */

/***************************************************************************
 * Hardware set-specific opcodes (privileged requests to the set)
 ***************************************************************************/
#define HWC_OP_PRIV_SET_MIN		KSM_OP_PRIV_SET_MIN
#define KSM_OP_SET_DELETE		HWC_OP_PRIV_SET_MIN+00
#define KSM_OP_SET_SCAN			HWC_OP_PRIV_SET_MIN+01
        /* INSERT NEW COMMON OPERATION CODES HERE */
#define HWC_OP_SET_REDIRECT		HWC_OP_PRIV_SET_MIN+25
#define HWC_OP_SET_VERIFY		HWC_OP_PRIV_SET_MIN+26
#define HWC_OP_SET_RELOAD		HWC_OP_PRIV_SET_MIN+27
#define HWC_OP_SET_UNLOAD		HWC_OP_PRIV_SET_MIN+28
#define HWC_OP_SET_UNCONFIGURE		HWC_OP_PRIV_SET_MIN+29
#define HWC_OP_SET_EDIT			HWC_OP_PRIV_SET_MIN+30
#define HWC_OP_SET_ADD			HWC_OP_PRIV_SET_MIN+31
#define HWC_OP_SET_LOCATE		HWC_OP_PRIV_SET_MIN+32
#define HWC_OP_SET_REFRESH		HWC_OP_PRIV_SET_MIN+33
#define HWC_OP_SET_READ_CDB		HWC_OP_PRIV_SET_MIN+34
#define HWC_OP_SET_NULL			HWC_OP_PRIV_SET_MIN+35
#define HWC_OP_SET_CHGN_LOCK		HWC_OP_PRIV_SET_MIN+36
#define HWC_OP_SET_CHGN_COMMIT		HWC_OP_PRIV_SET_MIN+37
#define HWC_OP_SET_MODC_LOCK		HWC_OP_PRIV_SET_MIN+38
#define HWC_OP_SET_REMOVE		HWC_OP_PRIV_SET_MIN+39
#define HWC_OP_SET_INDICT               HWC_OP_PRIV_SET_MIN+40
#define HWC_OP_SET_UNINDICT             HWC_OP_PRIV_SET_MIN+41
#define HWC_OP_SET_OFFLINE              HWC_OP_PRIV_SET_MIN+42
#define HWC_OP_SET_DISABLE              HWC_OP_PRIV_SET_MIN+43
#define HWC_OP_SET_GET_STATUS           HWC_OP_PRIV_SET_MIN+44
#define HWC_OP_SET_SET_COD_STATE        HWC_OP_PRIV_SET_MIN+45
#define HWC_OP_SET_ENABLE               HWC_OP_PRIV_SET_MIN+46
#define HWC_OP_SET_MEMB_LOCK            HWC_OP_PRIV_SET_MIN+47
#define HWC_OP_SET_GET_DEVT_INFO        HWC_OP_PRIV_SET_MIN+48

        /* INSERT NEW HARDWARE OPERATION CODES HERE AND CHANGE THE NEXT LINE */
#define HWC_OP_PRIV_SET_MAX		HWC_OP_PRIV_SET_MIN+48
/***************************************************************************
 * Hardware set-specific opcodes (non-privileged requests to the set)
 ***************************************************************************/
#define HWC_OP_NONPRIV_SET_MIN		KSM_OP_NONPRIV_SET_MIN
        /* INSERT NEW COMMON OPERATION CODES HERE */
#define HWC_OP_SET_SHOW			HWC_OP_NONPRIV_SET_MIN+25
#define HWC_OP_SET_STATUS		HWC_OP_NONPRIV_SET_MIN+26
#define HWC_OP_GET_REG_ID               HWC_OP_NONPRIV_SET_MIN+27
        /* INSERT NEW HARDWARE OPERATION CODES HERE AND CHANGE THE NEXT LINE */
#define HWC_OP_NONPRIV_SET_MAX		HWC_OP_NONPRIV_SET_MIN+26

/***************************************************************************
 * Hardware set-specific opcodes (privileged requests to the member)
 ***************************************************************************/
#define HWC_OP_PRIV_MEM_MIN		KSM_OP_PRIV_MEM_MIN
#define KSM_OP_MEM_SCAN			HWC_OP_PRIV_MEM_MIN+00
        /* INSERT NEW COMMON OPERATION CODES HERE */
#define HWC_OP_MEM_DELH_CONFIRM		HWC_OP_PRIV_MEM_MIN+25
#define HWC_OP_MEM_DELH_COMMIT		HWC_OP_PRIV_MEM_MIN+26
#define HWC_OP_MEM_DELH_CANCEL		HWC_OP_PRIV_MEM_MIN+27
#define HWC_OP_MEM_REDH_CONFIRM		HWC_OP_PRIV_MEM_MIN+28
#define HWC_OP_MEM_REDH_COMMIT1		HWC_OP_PRIV_MEM_MIN+29
#define HWC_OP_MEM_REDH_COMMIT2		HWC_OP_PRIV_MEM_MIN+30
#define HWC_OP_MEM_REDH_CANCEL		HWC_OP_PRIV_MEM_MIN+31
#define HWC_OP_MEM_REDH_SCAN		HWC_OP_PRIV_MEM_MIN+32
#define HWC_OP_MEM_UNCH_CONFIRM		HWC_OP_PRIV_MEM_MIN+33
#define HWC_OP_MEM_UNCH_COMMIT		HWC_OP_PRIV_MEM_MIN+34
#define HWC_OP_MEM_UNCH_CANCEL		HWC_OP_PRIV_MEM_MIN+35
#define HWC_OP_MEM_LOCATE		HWC_OP_PRIV_MEM_MIN+36
#define HWC_OP_MEM_REFD_LOCK		HWC_OP_PRIV_MEM_MIN+37
#define HWC_OP_MEM_CHGB			HWC_OP_PRIV_MEM_MIN+38
#define HWC_OP_MEM_ENABLE	        HWC_OP_PRIV_MEM_MIN+39
#define HWC_OP_MEM_DISABLE        	HWC_OP_PRIV_MEM_MIN+40
        /* INSERT NEW HARDWARE OPERATION CODES HERE AND CHANGE THE NEXT LINE */
#define HWC_OP_PRIV_MEM_MAX		HWC_OP_PRIV_MEM_MIN+40
/***************************************************************************
 * Hardware set-specific opcodes (non-privileged requests to the member)
 ***************************************************************************/
#define HWC_OP_NONPRIV_MEM_MIN		KSM_OP_NONPRIV_MEM_MIN
        /* INSERT NEW COMMON OPERATION CODES HERE */
        /* INSERT NEW HARDWARE OPERATION CODES HERE AND CHANGE THE NEXT LINE */
#define HWC_OP_NONPRIV_MEM_MAX		HWC_OP_NONPRIV_MEM_MIN+00

/***************************************************************************
 * Hardware set-specific opcodes (privileged requests to the mss)
 ***************************************************************************/
#define HWC_OP_PRIV_MSS_MIN		KSM_OP_PRIV_SYS_MIN+75
#define HWC_OP_MSS_UREG_CONFIRM		HWC_OP_PRIV_MSS_MIN+00
#define HWC_OP_MSS_UREG_COMMIT		HWC_OP_PRIV_MSS_MIN+01
#define HWC_OP_MSS_UREG_CANCEL		HWC_OP_PRIV_MSS_MIN+02
        /* INSERT NEW HARDWARE OPERATION CODES HERE AND CHANGE THE NEXT LINE */
#define HWC_OP_PRIV_MSS_MAX		HWC_OP_PRIV_MSS_MIN+02
/***************************************************************************
 * Hardware set-specific opcodes (non-privileged requests to the mss)
 ***************************************************************************/
#define HWC_OP_NONPRIV_MSS_MIN		KSM_OP_NONPRIV_SYS_MIN+75
        /* INSERT NEW HARDWARE OPERATION CODES HERE AND CHANGE THE NEXT LINE */
#define HWC_OP_NONPRIV_MSS_MAX		HWC_OP_NONPRIV_MSS_MIN+00

/* Define variables and structures for indictment */

#define INDICT_MIN_URGENCY	1  /* The urgency value represents the 
                                    seriousness of the problem.  The higher
                                    the urgency, the more serious the 
                                    problem */
#define INDICT_MAX_URGENCY	10

#define INDICT_MIN_PROBABILITY	1  /* The probability value represents the 
                                    likelihood that the indicted component
                                    is the culprit. The higher the probability
                                    the more likely the initiator of the 
                                    indictment notification believes the 
                                    indicted component is the source of the 
                                    errors */
#define INDICT_MAX_PROBABILITY	100

#define INDICT_MIN_INDICTMENTS	1 /* The total_indictments value represents
                                   the number of components being indicted 
                                   for the same error.  In some cases, the
                                   indictment initiator isn't 100% sure 
                                   which component needs to be replaced, so
                                   the initiator will indict more than one 
                                   component.  For the case where two
                                   components get indicted for the same
                                   error, the total_indictments should 
                                   be set to 2. */
                                       
#define INDICT_MAX_INDICTMENTS	10


#define INDICT_MAX_DESCR	256 /* The reason for the indictment contains
                                     up to this many characters including
                                     the null terminator */

#define INDICT_MAX_INITIATOR	32 /* The initiator of the indictment request
				     contains up to this many characters
                                     including the null terminator */

#define INDICT_MAX_REPORT_HNDL	128 /* The report handle contains up to this
				     many characters including the null
				     terminator */
    
#define INDICT_VERSION_1	1  /* version number for indictment Info 
                                    structure.  This is set by the
                                    caller. */

/* Define data types for readability and portability */
typedef int		indict32int_t;
typedef long		indict64int_t;
typedef unsigned char	indictuchar_t;

/* List of error codes returned by indictObject API */ 
typedef enum {
   indictERROR_NONE = 0,
   indictERROR_INVALID_URGENCY,
   indictERROR_INVALID_OBJECT_TYPE,
   indictERROR_INVALID_PROBABILITY,
   indictERROR_KSM_REGISTRATION_FAILURE,
   indictERROR_MUST_BE_ROOT,
   indictERROR_INVALID_TOTAL_INDICTMENTS
} indictStatus_t;

/* List of objects that can be indicted.  If new object types get added
   to the enum type then place in between INDICT_COMPONENT and 
   INDICT_OS_SPECIFIC since the validation code in indictObject API uses 
   these values as the min and max. */
typedef enum {
   INDICT_COMPONENT,	/* component to be indicted as specified 
			in the FRU Configuration Tree */
   INDICT_PFN,		/* Page Frame Number to be indicted as specified 
			by the physical address in the pfn_handle
			structure member */
   INDICT_OS_SPECIFIC	/* component to be indicted as represented by the 
			os (e.g. ksm/hwc HWID) */
} indictObject_t;

/* Handle to the physical module (FRU) that needs replacement.  This is the 
   module that is linked to the indicted component.  The handle is represented 
   by the attributes: id, type, and subtype. These attributes uniquely identify 
   a FRU node in the FRU branch of the config tree. */ 
typedef struct configTree_module_handle_type {
   indict64int_t	id;
   indictuchar_t	type;
   indictuchar_t	subtype;
} indictModule_handle_t;
   
/* Handle to the component that is being indicted.  The handle is represented 
   by the attributes: id, type, and subtype. These attributes uniquely identify
   a component node in the hardware branch of the config tree. */ 
typedef struct configTree_component_handle_type {
   indict64int_t	id;
   indictuchar_t	type;
   indictuchar_t	subtype;
} indictComponent_handle_t;

typedef struct configTree_handle_type {
   indictComponent_handle_t	component_handle;
   indictModule_handle_t	module_handle;
} indictConfigTree_handle_t;
   
typedef struct indictInfo {
				/* Version of this structure */
   indict32int_t	version;      

				/* Type of object being indicted */
   indictObject_t	object_type;  

   union {
				/* A 64-bit integer is used to specify
				the handle for pfn indictments (physical
				address) as well as the handle for the
				indictment of an os specific component (HWID) */
      indict64int_t		pfn_or_os_handle;
      indictConfigTree_handle_t configTree_handle;
   } handle;
				/* A value between INDICT_MIN_URGENCY and 
				INDICT_MAX_URGENCY */
   indict32int_t	urgency;     

				/* A value between INDICT_MIN_PROBABILITY and 
				INDICT_MAX_PROBABILITY */
   indict32int_t	probability; 

				/* The details which describe the reason for 
				the indictment */
   char			description[INDICT_MAX_DESCR]; 

				/* Specifies who initiated the indictment
				notification */ 
   char			initiator[INDICT_MAX_INITIATOR]; 

				/* A value between INDICT_MIN_INDICTMENTS and 
				INDICT_MAX_INDICTMENTS */
   indict32int_t	total_indictments;

				/* Represents handle to additional indictment
				 information (e.g. FRU callout report).  This
				 attribute should be specified to tie together
				 multiple indictment requests for the same error 
				(i.e. total_indictments is greater than 1. */
   char			report_handle[INDICT_MAX_REPORT_HNDL];
} indictInfo_t;

#ifdef _KERNEL
extern char *hwc_cat_undefined;
extern char *hwc_cat_adapter;
extern char *hwc_cat_bus;
extern char *hwc_cat_cluster_inter;
extern char *hwc_cat_console;
extern char *hwc_cat_control_port;
extern char *hwc_cat_cpu;
extern char *hwc_cat_disk;
extern char *hwc_cat_env_monitor;
extern char *hwc_cat_fan;
extern char *hwc_cat_fibrechan;
extern char *hwc_cat_generic;
extern char *hwc_cat_graphics;
extern char *hwc_cat_i2o_ctlr;
extern char *hwc_cat_ide_adapter;
extern char *hwc_cat_keyboard;
extern char *hwc_cat_media_changer;
extern char *hwc_cat_memory;
extern char *hwc_cat_monitor;
extern char *hwc_cat_network;
extern char *hwc_cat_parallel_port;
extern char *hwc_cat_platform;
extern char *hwc_cat_pointer;
extern char *hwc_cat_power;
extern char *hwc_cat_sa_adapter;
extern char *hwc_cat_scsi_adapter;
extern char *hwc_cat_scsi_bus;
extern char *hwc_cat_serial_port;
extern char *hwc_cat_sound;
extern char *hwc_cat_tape;
extern char *hwc_cat_thermal;
extern char *hwc_cat_usb;
extern char *hwc_cat_video;
   
extern char *hwc_subcat_generic;
extern char *hwc_subcat_printer;
extern char *hwc_subcat_terminal;
extern char *hwc_subcat_building_block;

extern char *hwc_disk_subcat_floppy;
extern char *hwc_disk_subcat_cdrom;
extern char *hwc_disk_subcat_worm;
extern char *hwc_disk_subcat_magopt;

extern char *hwc_cpu_subcat_ev3;
extern char *hwc_cpu_subcat_ev4;
extern char *hwc_cpu_subcat_lca4;
extern char *hwc_cpu_subcat_ev45;
extern char *hwc_cpu_subcat_ev5;
extern char *hwc_cpu_subcat_ev56;
extern char *hwc_cpu_subcat_ev6;

extern char *hwc_port_subcat_storage;
extern char *hwc_port_subcat_generic_storage;

extern char *hwc_control;
extern char *hwc_port;

extern char *hwc_good;
extern char *hwc_warning;
extern char *hwc_critical;
extern char *hwc_inactive;

extern char *hwc_short_good;
extern char *hwc_short_warning;
extern char *hwc_short_critical;
extern char *hwc_short_inactive;

extern char *hwc_online;
extern char *hwc_offline;
extern char *hwc_frozen;

extern char *hwc_unknown;
extern char *hwc_available;
extern char *hwc_limited;
extern char *hwc_unavailable;
extern char *hwc_broken;
extern char *hwc_testing;
extern char *hwc_off;

extern char *hwc_low;
extern char *hwc_medium;
extern char *hwc_high;

extern char *hwc_purchased;
extern char *hwc_on_loan;
extern char *hwc_spare;

extern cfg_subsys_attr_t hwc_attributes_bus[];     /* Common attribute table           */
extern cfg_subsys_attr_t hwc_attributes_disk[];    /* Common disk attribute table      */
extern cfg_subsys_attr_t hwc_attributes_tape[];    /* Common tape attribute table      */
extern cfg_subsys_attr_t hwc_attributes_pwrmgmt[]; /* Power management attribute table */
extern cfg_subsys_attr_t hwc_attributes_port[];    /* Common control-port attr table   */

extern int hwc_disk_part_minor_mask;
extern int hwc_disk_arch_minor_mask;
extern int hwc_disk_part_0_patt;
extern int hwc_disk_part_1_patt;
extern int hwc_disk_part_2_patt;
extern int hwc_disk_part_3_patt;
extern int hwc_disk_part_4_patt;
extern int hwc_disk_part_5_patt;
extern int hwc_disk_part_6_patt;
extern int hwc_disk_part_7_patt;

extern char *hwc_disk_pnames[];
extern char *hwc_disk_char;
extern char *hwc_disk_block;

extern int hwc_pwrmgmt_capable;
extern int hwc_pwrmgmt_not_capable;
extern int hwc_pwrmgmt_dev_disabled;

extern int hwc_boot_capable;
extern int hwc_boot_not_capable;
extern int hwc_boot_dev_disabled;

/*
 * Macro to determine default status for opcodes supplied to 
 * the set, member, and mss support routines of the hardware set.
 */
#define HWC_SUPPORT_STATUS(op) \
     ( ((op >= KSM_OP_PRIV_SET_MIN) && (op <= KSM_OP_PRIV_SET_MAX)) ||       \
       ((op >= KSM_OP_NONPRIV_SET_MIN) && (op <= KSM_OP_NONPRIV_SET_MAX)) || \
       ((op >= KSM_OP_PRIV_MEM_MIN) && (op <= KSM_OP_PRIV_MEM_MAX)) ||       \
       ((op >= KSM_OP_NONPRIV_MEM_MIN) && (op <= KSM_OP_NONPRIV_MEM_MAX)) )  \
        ? ENOTSUP : ESUCCESS

/*
 * Macro to store time.  This is needed because the real macro may
 * fetch a value of zero and we don't want to ever store a zero.  So
 * our macro will check for a zero and change it to a time of 1 micro-
 * second.  This is because the applications (hwmgr) will display a
 * timestamp of 0 as "none".
 */
#define HWC_TIME_READ(storage) \
  TIME_READ(storage); \
  if (*((ulong *)(&(storage))) == 0) { \
    extern int hwc_time_cnt;           \
    ((struct timeval *)(&(storage)))->tv_usec = hwc_time_cnt++; \
  }

/*
 * Power control struct and flags.
 */
#define POWER_REV_1	1
struct hal_pwr_ctl {
	u_int	rev;
	u_int	flags;
	long	id;
};

/*
 * event_code definitions used for all state_change events,
 * including [un]indicted and COD (Capacity On Demand) state changes
 */
#define HWC_STATE_CHANGE_INDICTED	 1
#define HWC_STATE_CHANGE_INDICTED_PFN	 2
#define HWC_STATE_CHANGE_UNINDICTED	 3
#define HWC_STATE_CHANGE_ONLINE		 4
#define HWC_STATE_CHANGE_OFFLINE_NOSAVE	 5
#define HWC_STATE_CHANGE_OFFLINE	 6
#define HWC_STATE_CHANGE_OFFLINE_REQUEST 7
#define HWC_STATE_CHANGE_AVAILABLE	 8
#define HWC_STATE_CHANGE_UNAVAILABLE	 9
#define HWC_STATE_CHANGE_LIMITED	10
#define HWC_STATE_CHANGE_BROKEN		11
#define HWC_STATE_CHANGE_OFF		12
#define HWC_STATE_CHANGE_TESTING	13
#define HWC_STATE_CHANGE_UNKNOWN	14
#define HWC_STATE_CHANGE_ASSIGNED	15
#define HWC_STATE_CHANGE_UNASSIGNED	16
#define HWC_STATE_CHANGE_ENABLED	17
#define HWC_STATE_CHANGE_DISABLED	18
#define HWC_STATE_CHANGE_COD_NULL	19
#define HWC_STATE_CHANGE_COD_ON_LOAN	20
#define HWC_STATE_CHANGE_COD_SPARE	21
#define HWC_STATE_CHANGE_COD_PURCHASED	22

/* 
 * Indictment variables
 * 
 * Members of struct INDICT_VARS are listed in the pre-specified
 * KSM order of indictment HWMGR_DATA buffers.
 * 
 * Note: all of the fields in this structure must be longword-aligned!
 */
typedef struct indict_vars {
    long  urgency;
    long  probability;
    long  previous_probability;
    long  total_indictments;
    char *description;
    char *initiator;
    char *report_handle;
    long component_id;
    long component_type;
    long component_subtype;
    long module_id;
    long module_type;
    long module_subtype;
    char *component;		/* non-pfn indictment only */
    ulong physical_address;	/* for pfn indictment only */
    long hwid;			/* for component indictment */
} INDICT_VARS;

/*
 * Define the index values for each of the lsm attributes.  This
 * must align with the lsm attributes table in the hwc module.  We
 * also define the maximum size of some of the string values for some
 * of the attributes.
 */
#define HWC_LSM_I_GROUP_NAME       0
#define HWC_LSM_NUM_ATTR           1 /* number of common lsm attributes */

#define HWC_LSM_GROUP_LEN         32 /* max length of lsm group name */

/*
 * Define the index values for each of the cod attributes.  This
 * must align with the cod attributes table in the hwc module.  We
 * also define the maximum size of some of the string values for some
 * of the attributes.
 */
#define HWC_COD_I_STATE            0
#define HWC_COD_NUM_ATTR           1 /* number of common cod attributes */

#endif /* _KERNEL */

#define POWER_UP	1
#define POWER_DOWN	2
#define POWER_QUERY	3
/* End power control struct and flags. */

#ifdef __cplusplus
}
#endif
#endif /*_HWC_REG_H_ */
