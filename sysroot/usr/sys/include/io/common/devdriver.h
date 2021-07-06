/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: devdriver.h,v $
 * Revision 1.2.286.6  2008/02/13  05:59:28  Chilaka_Ravi_Kumar
 * 	Add GET_PS_PRESENT and GET_PS_DEFUNCT queries.
 * 	QAR-20165
 *
 * Revision 1.2.286.5  2006/11/20  14:07:36  Mayank_Rajawat
 * 	QAR 19723: Workaround for some PCI cards (token ring) that
 * 	freeze-up during probe after the command register is
 * 	written and then a BAR register is written without a DELAY.
 * 	during pci probe.
 *
 * Revision 1.2.286.4  2005/01/12  16:15:58  Aaron_Biver
 * Compiler issue:  Remove typo/trailing semicolon after
 * topology tree lock and lock info declarations.
 *
 * Revision 1.2.286.3  2004/10/21  19:48:28  Aaron_Biver
 * 	QAR 97736: Update topology locking macros.
 * 	Add protos for new utility routines for queue
 * 	management.
 * 	[2004/09/01  19:25:34  Aaron_Biver]
 *
 * Revision 1.2.286.2  2002/11/08  15:33:46  Martine_Silbermann
 * 	Added define for GET_MSI_SCB_INFO option for get_info
 *
 * Revision 1.2.286.1  2002/10/16  15:48:45  Joshua_Smith
 *      added the MCHECK_SUBSYS_CAPABLE getinfo case
 *
 * Revision 1.2.263.12  2002/05/31  19:12:18  Aaron_Biver
 * 	Add HAL_OPEN_USB and HAL_CLOSE_USB for USB console
 * 	support.
 *
 * Revision 1.2.263.11  2002/05/30  23:16:34  Ashoke_Rampuria
 * 	Changes for compiler switch project
 *
 * Revision 1.2.263.10  2002/05/29  20:13:05  Martine_Silbermann
 * 	Added GET_ERR_LOG_CAPS_HDR get_info define.
 *
 * Revision 1.2.263.9  2002/03/27  15:15:19  Jason_Miller
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree wcalphaos
 *     User Revision:  Jason_Miller_wcalphaos_br:1.2.272.1 Local Ancestor:1.2.263.7
 *    Merge Revision:  wcalphaos_br:1.2.263.8
 *   Common Ancestor:  1.2.263.7
 *
 * Revision 1.2.263.8  2002/03/25  22:33:42  Aaron_Biver
 * 	Add support for HAL_HOTSWAP_CAPABLE.
 * 
 * Revision 1.2.272.1  2002/03/25  14:24:04  Jason_Miller
 * 	Add CHECK_IDE_CONTROLLER getinfo define.
 * 
 * Revision 1.2.263.7  2002/01/29  19:25:09  Martine_Silbermann
 * 	Added GET_MAX_PCI_SLOTS getinfo define.
 * 
 * Revision 1.2.263.6  2002/01/02  18:46:50  Andrew_Duane
 * 	Add READ_IPRS and fix duplicate line from last merge.
 * 
 * Revision 1.2.263.5  2001/12/14  18:16:50  Aaron_Biver
 * 	MErge from hotswapos.
 * 
 * Revision 1.2.268.2  2001/11/19  19:43:54  Aaron_Biver
 * 	Changes to numa_info_t struct:
 * 	replace ni_shift with ni_nodes_per_rad.
 * 	add ni_align_mask
 * 
 * Revision 1.2.268.1  2001/11/19  17:04:47  Aaron_Biver
 * 	Add HAL_GET_MEMDSC_INFO.
 * 
 * Revision 1.2.265.3  2001/11/08  19:14:34  Aaron_Biver
 * 	Add a hal_handle to HAL_SLOT_INFO.
 * 
 * Revision 1.2.263.3  2001/11/06  19:48:54  David_Partridge
 * 	Yankee IPK BL0 merge.
 * 	Revision 1.2.249.2  2001/07/10  23:34:32  Aaron_Biver
 * 	Add SAVEENV_FIXUP_REQUIRED get_info code.
 * 
 * Revision 1.2.263.2  2001/10/24  22:19:32  Rajesh_R
 * 	Modify numa_info_t (struct get_numa_info) for Marvel.
 * 
 * Revision 1.2.265.2  2001/09/28  13:32:46  David_Gagne
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree hotswapos
 *     User Revision:  David_Gagne_hs1_br:1.2.266.1 Local Ancestor:1.2.263.1
 *    Merge Revision:  hotswapos_br:1.2.265.1
 *   Common Ancestor:  1.2.263.1
 * 	[2001/09/28  13:32:37  David_Gagne]
 * 	Fix Aaron's change.  It defined a data structure (hal_slot_info)
 * 	that is available to both kernel mode and user mode.  However, the
 * 	header file that it requires (ksm.h) is only included in kernel
 * 	mode.  The user mode users of this header file get errors.  I will
 * 	change this header file such that the hal_slot_info data structure
 * 	is only available in kernel mode.
 * 	[2001/09/28  13:30:05  David_Gagne]
 * 
 * Revision 1.2.265.1  2001/09/27  16:55:18  Aaron_Biver
 * 	Add HAL_GET_MEMDSC_INFO and HAL_GET_PCI_SLOT_INFO.
 * 	Modify numa_info_t (struct get_numa_info) for Marvel.
 * 
 * Revision 1.2.263.1  2001/09/20  15:01:14  Joel_Martin
 *  Add fibre channel support to hwc (hwmgr)
 *  Increase DDIDKI_VERSION_REV to 2 (5.0.2) to indicate hwc_fibre
 *  sub-system interface for fibre channel drivers.
 * 
 * Revision 1.2.247.2  2001/03/09  01:30:28  Gregg_Rivinius
 * 	Added GET_SYS_AGP_CAPS getinfo define.
 * 
 * Revision 1.2.247.1  2000/10/18  19:04:19  Frederick_Canter
 * 	Add GET_INTR_TARGET_CPU get_info call.
 * 
 * Revision 1.2.230.12  2000/08/15  21:18:37  Mike_Winiarski
 * 	Fix for QAR 81823.
 * 	There are inconsistencies between the uses of CTLR_CONFIG_REVISION and
 * 	BUS_CONFIG_REVISION in kernel builds and external builds of drivers due
 * 	to documentation errors in the DDK.
 *  *
 * 	To maintain a level of source compatiblity, the definitions of
 * 	CTLR_CONFIG_REVISION and BUS_CONFIG_REVISION are now conditional upon
 * 	whether this is a kernel (ode environment) build or an external build.
 * 	The conditional check is _BASE_KERNEL_PRIVATE.
 * 
 * Revision 1.2.230.11  2000/06/01  20:41:33  Mike_Winiarski
 * 	Fix for QAR 80256.
 * 	Added prototype defs for get_bus_num() and remove_bus_instance().
 * 	Calls to these routines added in wfcpu.c (wfcpu_configure_platform()).
 * 
 * Revision 1.2.230.10  2000/04/28  17:21:20  Julie_Dewandel
 * 	Add new HWBUG define for failing PCI Rd Mlt for FORE-ATM on Wildfire.
 * 
 * Revision 1.2.230.9  2000/04/10  21:31:28  Jan_Reimers
 * 	Added dev_console_allp_t structure for DEVCONSOLE_ALLPATHS ioctl
 * 
 * Revision 1.2.230.8  2000/03/16  16:32:09  Frederick_Canter
 * Define get_info call for CRD/DBE memory troller.
 * 
 * Revision 1.2.230.7  2000/02/18  21:10:59  Donald_Dutile
 * 	Add CONFIG_PRIMARY_PCI_IDE define for ata-on-Wildfire config limitation.
 * 
 * Revision 1.2.230.6  2000/01/21  20:16:46  Mike_Winiarski
 * 	merge of zincos-771-mikew zinc bl3 to zulu bl8
 * 	[2000/01/21  20:00:33  Mike_Winiarski]
 * 
 * Revision 1.2.230.5  2000/01/07  21:59:22  Mike_Winiarski
 * 	merge from zinc bl3
 * 
 * Revision 1.2.238.5  2000/01/05  21:05:32  Mike_Winiarski
 * 	{** Forced Submit **}
 * 	QAR 76131
 * 	Added new defines for support of the enhanced create_bus_struct()
 * 	and create_controller_struct() routines.
 * 	Bumped the revision number for bus_config and controller_config
 * 	structs
 * 	Extended the bus_config struct with preferred instance num and
 * 	slot num fields.
 * 	Extended the controller_config struct with preferred instance num
 * 	and slot num fields.
 * 	The extended fields are valid when flags bits are set in the
 * 	structs.
 * 	[2000/01/05  16:13:56  Mike_Winiarski]
 * 
 * Revision 1.2.230.4  1999/12/13  14:03:22  Dennis_Paradis
 * 	Merged ACE_PIC_INT_MODE define from ptwild.
 * 
 * Revision 1.2.230.3  1999/10/04  23:12:13  Donald_Dutile
 * 	* Port from v40g-bl4, zinc-bl2:
 * 	* (1) Add find_*_config_entry functions def's here, so
 * 	*      externs don't have to be declared in C files.
 * 	* (2) Add Wildfire-specific HWBUG getinfo defines
 * 	* (3) Add NEXUS_BUS_PTR define used by find_bus;
 * 	*     needed to find a bus connected to nexus.
 * 	*     [Part of change to find_bus_config_entry().]
 * 	* (4) Rename MEM_ADDR_ALIGN to GET_NUMA_INFO.
 * 
 * Revision 1.2.230.2  1999/08/13  12:22:03  James_Smart
 * 	Bump DDIDKI_VERSION_REV to (1) to indicate addition of the
 * 	NUMA interfaces to the base ddi/dki.
 * 	[1999/08/04  18:58:33  James_Smart]
 * 
 * Revision 1.2.119.55  1999/05/17  16:23:22  James_Smart
 * 	Add Define's for the DDI/DKI level supported
 * 	   DDIDKI_VERSION_MAJOR
 * 	   DDIDKI_VERSION_MINOR
 * 	   DDIDKI_VERSION_REV
 * 	[1999/04/28  20:51:02  James_Smart]
 * 
 * Revision 1.2.119.54  1999/03/25  17:09:10  Shashi_Mangalat
 * 	Add IS_32BIT_CONSOLE for bird machines.
 * 	[1999/03/25  17:00:14  Shashi_Mangalat]
 * 
 * Revision 1.2.119.53  1999/03/24  14:32:39  Mike_Winiarski
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTFCOS_BL5:PTFCOS_BL6 **
 * 		** Ancestor revision:	1.2.203.7 **
 * 		** Merge revision:	1.2.203.8 **
 * 	 	** End **
 * 	 Revision 1.2.203.8  1999/03/16  21:49:57  Dick_Bagley
 * 	 Add support for CHECK_IDE_LIMITS get_info call.
 * 	[1999/03/23  19:09:45  Mike_Winiarski]
 * 
 * Revision 1.2.119.52  1999/03/11  22:06:44  Peter_Woods
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.2.119.49 **
 * 		** Merge revision:	1.2.119.51 **
 * 	 	** End **
 * 	Back out CONFIG_V5DRIVER and ALV_V5DRIVER flags.  They are not
 * 	required.
 * 	[1999/03/02  15:16:09  Peter_Woods]
 * 
 * Revision 1.2.119.51  1999/03/03  16:41:41  Peter_Woods
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.2.119.49 **
 * 		** Merge revision:	1.2.119.50 **
 * 	 	** End **
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTFCOS_BL3:PTFCOS_BL5 **
 * 		** Ancestor revision:	1.2.203.4 **
 * 		** Merge revision:	1.2.203.7 **
 * 	 	** End **
 * 	[1999/03/03  16:34:28  Peter_Woods]
 * 
 * Revision 1.2.119.50  1999/03/03  00:07:13  Ernie_Petrides
 * 	Fix function prototype for drvr_shutdown().
 * 	[1999/03/02  23:56:22  Ernie_Petrides]
 * 
 * Revision 1.2.119.49  1999/02/26  22:57:18  Peter_Woods
 * 	Add in CONFIG_V5DRIVER and ALV_V5DRIVER used to indicate that
 * 	the driver is using the new V5.0 Driver model.
 * 	[1999/02/25  17:35:36  Peter_Woods]
 * 
 * Revision 1.2.119.48  1999/02/19  21:25:49  Peter_Woods
 * 	Add additional fields in the module_load structure to
 * 	support instance loading during hwautoconfig executution.
 * 	[1999/02/18  14:36:00  Peter_Woods]
 * 
 * Revision 1.2.119.47  1999/02/12  17:22:06  Peter_Woods
 * 	Add in bus_ehm_config_data pointer into one of the reserved
 * 	fields of the bus structure.
 * 	Add in persistence key request buffer and function prototype.
 * 	Add in externs for create/remove bus/ctlr/device structures.
 * 	Add in extern prototypes for create_hwconfig_struct and
 * 	free_hwconfig_struct.
 * 	[1999/02/12  14:22:21  Peter_Woods]
 * 
 * Revision 1.2.203.7  1999/02/12  14:26:11  James_Smart
 * 	Raise BUS_INDEX from 10 to 32
 * 	[1999/02/11  14:02:28  James_Smart]
 * 
 * Revision 1.2.203.6  1999/02/09  17:31:48  Frederick_Canter
 * 	Add GET_BAD_PAGE_LIST get_info function. Returns a list of
 * 	bad pages (pages with uncorrectable memory errors), so they
 * 	can be excluded from the crash dump.
 * 	Add GET_PLATFORM_RESET_PTR get_info function. Returns a
 * 	pointer to the platform's reset function (if supported).
 * 	Add GET_HALT_AFTER_PANIC get_info function. Returns the
 * 	platform's force halt after panic flag.
 * 	[1999/02/08  22:40:35  Frederick_Canter]
 * 
 * Revision 1.2.119.46  1999/01/28  16:13:43  Peter_Woods
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.2.119.44 **
 * 		** Merge revision:	1.2.119.45 **
 * 	 	** End **
 * 	Add in phys_bus_num and phys_subbus_num fields into the
 * 	bus structure.  These elements hold physical bus information
 * 	that used to be in the bus_num field.  This allows the bus_num
 * 	field to contain a logical bus number which is what we need
 * 	in order to make persistence work correctly for busses.
 * 	[1999/01/13  20:52:18  Peter_Woods]
 * 
 * Revision 1.2.119.45  1999/01/14  16:35:47  Peter_Woods
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTEV6OS_BL8:PTFCOS_BL3 **
 * 		** Ancestor revision:	1.2.194.5 **
 * 		** Merge revision:	1.2.203.4 **
 * 	 	** End **
 * 	[1999/01/14  16:30:23  Peter_Woods]
 * 
 * Revision 1.2.119.44  1999/01/08  15:02:07  Peter_Woods
 * 	Add in constant for HWCONFIG_UNLOAD_MODULE
 * 	[1998/12/03  21:38:52  Peter_Woods]
 * 	Change default from persist in the name database to
 * 	nopersist in the name database.
 * 	[1998/12/03  19:39:49  Peter_Woods]
 * 
 * Revision 1.2.203.5  1998/12/29  15:57:36  Dick_Bagley
 * 	Added defines for three new get_info() calls:
 * 	  o GET_MEM_BANK_COUNT
 * 	  o GET_MEM_BANK_SIZE
 * 	  o GET_MEM_BANK_BASE_PA
 * 	These get_info functions provide support for software
 * 	memory interleaving.
 * 	[1998/12/18  22:41:51  Dick_Bagley]
 * 
 * Revision 1.2.203.4  1998/10/30  17:13:34  Frederick_Canter
 * 	Remove MAX_HWP_NODE_COUNT get_info define.
 * 	[1998/10/29  19:09:35  Frederick_Canter]
 * 
 * Revision 1.2.119.43  1998/10/21  17:45:31  Ernie_Petrides
 * 	Add hw_sg_*() function prototypes.
 * 	[1998/10/16  15:57:10  Ernie_Petrides]
 * 
 * Revision 1.2.203.3  1998/10/02  16:00:03  Frederick_Canter
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.2.194.5 **
 * 		** Merge revision:	1.2.203.2 **
 * 	 	** End **
 * 	Add MAX_HWP_NODE_COUNT get_info define for HARD_PARTITIONS.
 * 	[1998/10/01  17:33:29  Frederick_Canter]
 * 
 * Revision 1.2.203.2  1998/10/02  15:49:50  Donald_Dutile
 * 	Add fcn-proto's for 2 new dma interfaces.
 * 	[1998/10/01  18:47:07  Donald_Dutile]
 * 
 * Revision 1.2.119.42  1998/08/06  15:49:03  Matthew_Waxman
 * 	More merge fixes.
 * 	[1998/08/06  15:45:00  Matthew_Waxman]
 * 
 * Revision 1.2.119.41  1998/08/05  17:18:10  Matthew_Waxman
 * 	Merge fix.
 * 	[1998/08/05  15:23:51  Matthew_Waxman]
 * 
 * Revision 1.2.119.40  1998/08/03  18:53:38  Shashi_Mangalat
 * 	Merge fix.
 * 	[1998/08/03  17:58:22  Shashi_Mangalat]
 * 
 * Revision 1.2.119.39  1998/07/30  03:31:20  Matthew_Waxman
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTEV6OS_BL4:PTEV6OS_BL6 **
 * 		** Ancestor revision:	1.2.194.2 **
 * 		** Merge revision:	1.2.194.5 **
 * 	 	** End **
 * 	[1998/07/30  03:16:07  Matthew_Waxman]
 * 
 * Revision 1.2.119.38  1998/06/18  20:03:54  Peter_Woods
 * 	Relocate dyn_struct_alloc definition to driver_support.h  Change
 * 	module_load struct to a linked list.
 * 	[1998/06/16  18:47:49  Peter_Woods]
 * 	Add module load structure used to load drivers and associated modules
 * 	during hardware autoconfig.
 * 	Add module_list pointer to hwconfig structure.  This allows
 * 	driver_framework to properly load any associated modules that
 * 	the targeted device driver requres.
 * 	Add 'flags' field to the controller_config structure.  Remove
 * 	the BUS_INDEX, CTLR_INDEX, and DEVICE_INDEX defines as they are
 * 	no longer used by the driver_support code.
 * 	[1998/06/09  20:40:56  Peter_Woods]
 * 	Create dyn_struct_alloc structure which is used by
 * 	driver support as a general structure to hold our
 * 	dynamic bus, controller, and device structures.
 * 	[1998/05/27  12:57:54  Peter_Woods]
 * 
 * Revision 1.2.119.37  1998/05/12  18:21:45  Peter_Woods
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL14:PTEV6OS_BL4 **
 * 		** Ancestor revision:	1.2.140.10 **
 * 		** Merge revision:	1.2.194.2 **
 * 	 	** End **
 * 	[1998/05/12  18:06:05  Peter_Woods]
 * 
 * Revision 1.2.194.5  1998/05/11  22:17:06  Donald_Dutile
 * 	Propagate i2oshared work into ptev6
 * 	[1998/05/05  15:57:52  Donald_Dutile]
 * 
 * Revision 1.2.183.5  1998/05/05  15:06:42  Donald_Dutile
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rPTEV6OS_NIGHTLY **
 * 		** Ancestor revision:	1.2.194.3 **
 * 		** Merge revision:	1.2.194.4 **
 * 	 	** End **
 * 	Backport Steel's ALV_STATIC define.
 * 	[1998/05/05  13:54:43  Donald_Dutile]
 * 
 * Revision 1.2.194.4  1998/05/01  17:04:41  Mike_Winiarski
 * 	Modifications, additions for 64-bit DMA addressing.
 * 	[1998/04/29  20:32:18  Mike_Winiarski]
 * 
 * Revision 1.2.183.4  1998/04/29  20:30:04  Donald_Dutile
 * 	Add BUS_I2O -- merge of original devdriver.h to 1.2.194.3
 * 	[1998/04/28  21:12:19  Donald_Dutile]
 * 
 * Revision 1.2.194.3  1998/04/20  17:29:24  David_Anderson
 * 	Large memory-hole support for Wildfire.
 * 	(QAR 60399)
 * 	[1998/04/17  18:14:31  David_Anderson]
 * 
 * Revision 1.2.119.36  1998/04/08  13:58:35  Frederick_Canter
 * 	Sync up EV6 support with PT.ev6 BL4.
 * 	 Add PLATFORM_IO_BIT get_info() function code.
 * 	Also reserved function codes so V4.0E and future
 * 	release don't collide (driver binary compatability).
 * 	Steel codes PEER_TO_PEER, MEM_ADDR_ALIGN move to
 * 	steel reserved space. CTLR_2_CONSOLE back to 1d.
 * 	[1998/04/06  12:25:20  Frederick_Canter]
 * 
 * Revision 1.2.194.2  1998/03/31  20:02:31  Frederick_Canter
 * 	Add PLATFORM_IO_BIT get_info() function code.
 * 	Also reserved function codes so V4.0E and future
 * 	release don't collide (driver binary compatability).
 * 	[1998/03/29  16:09:35  Frederick_Canter]
 * 
 * Revision 1.2.119.35  1998/03/31  02:50:47  Mark_Bokhan
 * 	Change obsolete "perf" alias to "dstats".  This alias specifies
 * 	the private[1] field of the device struct.  The field now points
 * 	to an allocated tbl_dkinfo struct, used to hold the current disk
 * 	statistics.  Change perf_init prototype to dstats_init.
 * 	[1998/03/26  23:38:15  Mark_Bokhan]
 * 
 * Revision 1.2.119.34  1998/01/15  19:34:50  Peter_Woods
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL11:PTCOS_BL14 **
 * 		** Ancestor revision:	1.2.140.9 **
 * 		** Merge revision:	1.2.140.10 **
 * 	 	** End **
 * 	[1998/01/15  19:01:26  Peter_Woods]
 * 
 * Revision 1.2.119.33  1997/12/08  14:18:23  Andrew_Duane
 * 	Fuix build problem with last merge.
 * 	[1997/12/08  14:17:38  Andrew_Duane]
 * 
 * Revision 1.2.119.32  1997/12/05  20:30:31  Gary_Field
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.2.119.30 **
 * 		** Merge revision:	1.2.119.31 **
 * 	 	** End **
 * 	Changed type of perf_init() routine to void to eliminate compiler warning
 * 	caused by changing type of perf_init routine in driver_support.c.
 * 	[1997/12/04  17:25:34  Gary_Field]
 * 
 * Revision 1.2.119.31  1997/12/04  21:07:41  David_Gagne
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.2.119.29 **
 * 		** Merge revision:	1.2.119.30 **
 * 	 	** End **
 * 	Change the name of the disk_name field in protocol_struct to
 * 	dsf_name so that it's more meaningful.
 * 	Modify/re-design the data structures used for device translation
 * 	so that they work for more than the boot device and so that they
 * 	work with the new device special file names.
 * 	[1997/12/04  20:39:52  David_Gagne]
 * 
 * Revision 1.2.119.30  1997/12/01  15:18:10  Karl_Ebner
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.2.119.28 **
 * 		** Merge revision:	1.2.119.29 **
 * 	 	** End **
 * 	Bus Framework support is added to detect unconfigured hardware
 * 	in the system.
 * 	[1997/10/14  22:45:49  Karl_Ebner]
 * 
 * Revision 1.2.119.29  1997/10/23  15:54:05  Janet_Schank
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL10:PTCOS_BL11 **
 * 		** Ancestor revision:	1.2.140.8 **
 * 		** Merge revision:	1.2.140.9 **
 * 	 	** End **
 * 	merge of PTmin BL11 changes
 * 	[1997/10/23  15:46:49  Janet_Schank]
 * 
 * Revision 1.2.119.28  1997/09/12  19:10:07  John_Flanagan
 * 	Change value of CTLR_2_CONSOLE to 0x001f
 * 	[1997/09/12  19:02:48  John_Flanagan]
 * 
 * Revision 1.2.140.10  1997/09/12  15:17:43  Peter_Woods
 * 	Add flag to define HANDLE_LINEAR_SPACE in the flags field of
 * 	iohandle_to_phys()
 * 	[1997/09/11  13:30:29  Peter_Woods]
 * 
 * Revision 1.2.119.27  1997/09/10  18:35:51  John_Flanagan
 * 	post merge cleanup
 * 	[1997/09/10  17:57:41  John_Flanagan]
 * 
 * Revision 1.2.119.26  1997/09/05  20:45:15  Karl_Ebner
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL6:PTCOS_BL10 **
 * 		** Ancestor revision:	1.2.140.5 **
 * 		** Merge revision:	1.2.140.8 **
 * 	 	** End **
 * 	[1997/09/03  19:38:38  Karl_Ebner]
 * 
 * Revision 1.2.140.9  1997/09/02  13:35:16  Janet_Schank
 * 	Added BUS_USB define.
 * 	Added BUS_USB define
 * 	Revision 1.2.140.8  1997/07/21  21:08:51  Alex_Malone
 * 	Add CTLR_2_CONSOLE
 * 	[1997/07/09  19:15:36  Alex_Malone]
 * 
 * Revision 1.2.119.25  1997/08/21  20:28:24  Peter_S_Thompson
 * 	Add definitions for return values for get_info(PEER_TO_PEER)
 * 	[1997/08/20  20:47:24  Peter_S_Thompson]
 * 
 * Revision 1.2.119.24  1997/08/11  19:45:29  James_Smart
 * 	Add "srm_suffix" field to dump_request, dev_console_t, and
 * 	  console_device
 * 	[1997/08/08  15:58:24  James_Smart]
 * 
 * Revision 1.2.119.23  1997/07/29  21:01:27  Karl_Ebner
 * 	reserved flags field added to the bus_config() struct definition.
 * 	[1997/07/24  16:40:16  Karl_Ebner]
 * 
 * Revision 1.2.140.8  1997/07/21  21:08:51  Alex_Malone
 * 	Add CTLR_2_CONSOLE
 * 	[1997/07/09  19:15:36  Alex_Malone]
 * 
 * Revision 1.2.119.22  1997/07/17  21:29:32  Karl_Ebner
 * 	HWCONFIG_LOAD_MODULE action flag is added to the driver framework calling
 * 	interface. This allows the user of the framework to specify the
 * 	loading of a software module.
 * 	[1997/07/17  20:33:15  Karl_Ebner]
 * 
 * Revision 1.2.119.21  1997/07/16  18:04:38  Peter_S_Thompson
 * 	Add PEER_TO_PEER flag for get_info.  This will return whether
 * 	a given system is peer-to-peer capable (in all configurations).
 * 	[1997/07/15  18:28:23  Peter_S_Thompson]
 * 
 * Revision 1.2.119.20  1997/07/02  18:14:13  Peter_Woods
 * 	Add #define for Cardbus in the resource allocation section
 * 	[1997/05/28  16:19:08  Peter_Woods]
 * 
 * Revision 1.2.119.19  1997/05/20  21:40:08  Carolyn_Briglia
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit -visual **
 * 		** Ancestor revision:	1.2.119.17 **
 * 		** Merge revision:	1.2.119.18 **
 * 	 	** End **
 * 	Added prototype for register_bus_hw()
 * 	[1997/05/19  19:24:20  Carolyn_Briglia]
 * 
 * Revision 1.2.119.18  1997/05/20  15:57:59  Karl_Ebner
 * 	ALV_PERSIST flag added to tell the driver framework when
 * 	a subsystem does not want to participate in the persistance
 * 	database.
 * 	[1997/05/17  18:34:43  Karl_Ebner]
 * 
 * Revision 1.2.140.7  1997/05/19  13:45:33  Bruce_Hansen
 * 	QAR 52985 - Increased the maximum limit of controller
 * 	instances from 50 to 1024.
 * 	[1997/05/15  15:09:52  Bruce_Hansen]
 * 
 * Revision 1.2.119.17  1997/05/07  18:14:49  Andrew_Duane
 * 	Remove references to wbflush.
 * 	[1997/05/07  12:30:33  Andrew_Duane]
 * 
 * Revision 1.2.119.16  1997/05/05  20:47:03  Karl_Ebner
 * 	Add BUS_CONFIG_REVISION definition
 * 	Add unconfl1 defintion for the bus structure
 * 	[1997/05/05  15:13:04  Karl_Ebner]
 * 
 * Revision 1.2.119.15  1997/04/24  19:00:16  Dave_Gerson
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL3:PTCOS_BL6 **
 * 		** Ancestor revision:	1.2.140.3 **
 * 		** Merge revision:	1.2.140.5 **
 * 	 	** End **
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL3:PTCOS **
 * 		** Ancestor revision:	1.2.140.3 **
 * 		** Merge revision:	1.2.140.6 **
 * 	 	** End **
 * 	merge of PTmin BL6 changes
 * 	[1997/04/24  18:58:25  Dave_Gerson]
 * 
 * Revision 1.2.140.6  1997/04/17  20:58:35  William_Evers
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTBOS_BL4:PTHW1OS_BL3 **
 * 		** Ancestor revision:	1.2.132.7 **
 * 		** Merge revision:	1.2.143.5 **
 * 	 	** End **
 * 	pthw1os merged forward into ptcos
 * 	[1997/04/17  19:38:58  William_Evers]
 * 
 * Revision 1.2.119.14  1997/04/10  19:45:03  Shashi_Mangalat
 * 	Add memory holes support
 * 	[1997/04/10  19:37:54  Shashi_Mangalat]
 * 
 * Revision 1.2.119.13  1997/04/08  18:50:25  Karl_Ebner
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.2.119.10 **
 * 		** Merge revision:	1.2.119.12 **
 * 	 	** End **
 * 	Driver framework hwconfig structure definition created.
 * 	[1997/04/05  20:54:27  Karl_Ebner]
 * 	The initial allocation definitions for the dynamic bus. controller
 * 	and device lists are changed to reflect the maximum hardware
 * 	configurations today. The kernel will automatically bump these
 * 	definitions to larger sizes upon demand from the driver
 * 	configuration framework.
 * 	[1997/03/11  20:18:21  Karl_Ebner]
 * 
 * Revision 1.2.119.12  1997/03/17  16:03:12  Karl_Ebner
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.2.119.10 **
 * 		** Merge revision:	1.2.119.11 **
 * 	 	** End **
 * 	The initial allocation definitions for the dynamic bus. controller
 * 	and device lists are changed to reflect the maximum hardware
 * 	configurations today. The kernel will automatically bump these
 * 	definitions to larger sizes upon demand from the driver
 * 	configuration framework.
 * 	[1997/03/11  20:18:21  Karl_Ebner]
 * 
 * Revision 1.2.119.11  1997/03/12  15:13:42  Theresa_Chin
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.2.119.8 **
 * 		** Merge revision:	1.2.119.10 **
 * 	 	** End **
 * 	Changed "ifdef defined" to "if defined".
 * 	[1997/03/11  21:48:56  Theresa_Chin]
 * 	Merge with latest change in pool.
 * 	[1997/03/06  21:16:20  Theresa_Chin]
 * 	Merge with latest change in the pool.
 * 	[1997/02/21  16:49:52  Theresa_Chin]
 * 	Add data struct. for platform I/O resource init common code.
 * 	[1997/02/13  19:49:15  Theresa_Chin]
 * 
 * Revision 1.2.119.10  1997/03/03  15:38:13  Robin_Miller
 * 	Added function prototype declarations.
 * 	Changed "#ifdef KERNEL" to "#ifdef _KERNEL".
 * 	[1997/03/03  15:05:59  Robin_Miller]
 * 
 * Revision 1.2.140.5  1997/02/27  20:21:45  Dave_Gerson
 * 	Added 2 macros to cover obtaining firmware and palcode revs
 * 	via get_info().
 * 	[1997/02/24  21:19:35  Dave_Gerson]
 * 
 * Revision 1.2.119.9  1997/02/18  18:45:38  William_Freeman
 * 	 	Merge recent changes
 * 	[1997/02/14  22:55:10  William_Freeman]
 * 	Add prototye for promio_dump.
 * 	[1997/01/24  23:15:17  William_Freeman]
 * 
 * Revision 1.2.143.5  1997/02/10  21:17:46  William_Evers
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.2.143.2 **
 * 		** Merge revision:	1.2.143.4 **
 * 	 	** End **
 * 	refine io_resource interface to hal
 * 	[1997/01/22  08:58:30  William_Evers]
 * 
 * Revision 1.2.143.4  1997/02/10  17:28:15  William_Evers
 * 	remove defunct revision in history log
 * 	[1997/02/10  17:23:46  William_Evers]
 * 	new sandbox, couldn't check in with old sandbox
 * 	add data return defines for CHECK_MOTHERBOARD_SLOT get_info.
 * 	this is used by ide code to decide whether to configure an
 * 	on-board ide controller.
 * 	[1997/02/09  19:07:36  William_Evers]
 * 
 * Revision 1.2.119.8  1997/02/04  21:26:34  Jim_Hamel
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTBOS_BL4:PTCOS_BL3 **
 * 		** Ancestor revision:	1.2.132.7 **
 * 		** Merge revision:	1.2.140.3 **
 * 	 	** End **
 * 	merge of PTC BL3 changes
 * 	[1997/02/04  19:44:21  Jim_Hamel]
 * 
 * Revision 1.2.119.7  1997/01/24  14:30:40  Mark_Parenti
 * 	Add definition for ALV_STATIC flag bit.
 * 	[1997/01/22  18:36:24  Mark_Parenti]
 * 
 * Revision 1.2.140.4  1997/01/23  13:12:45  Jim_Hamel
 * 	Add in support for GET_HW_BUGS
 * 	[1997/01/15  18:55:40  Jim_Hamel]
 * 
 * Revision 1.2.143.2  1997/01/08  21:47:06  William_Evers
 * 	add define for getinfo CHECK_MOTHERBOARD_SLOT
 * 	[1997/01/03  18:16:32  William_Evers]
 * 
 * Revision 1.2.119.6  1996/12/11  14:03:29  William_Grava
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTBOS_BL3:PTBOS_BL4 **
 * 		** Ancestor revision:	1.2.132.6 **
 * 		** Merge revision:	1.2.132.7 **
 * 	 	** End **
 * 	merge of PTB BL4 changes
 * 	[1996/12/11  13:53:24  William_Grava]
 * 
 * Revision 1.2.140.3  1996/11/21  23:29:14  Jim_Hamel
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.2.140.2 **
 * 		** Merge revision:	1.2.140.2 **
 * 	 	** End **
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -r1.2.140.2 **
 * 		** Ancestor revision:	1.2.132.7 **
 * 		** Merge revision:	1.2.140.2 **
 * 	 	** End **
 * 	[1996/11/21  23:07:10  Jim_Hamel]
 * 	Add in support for:
 * 	- add GET_SG_FLUSHPTR definition
 * 	- add GET_SGMAP_CTL definition
 * 	[1996/11/20  23:05:48  Jim_Hamel]
 * 
 * Revision 1.2.140.2  1996/11/20  20:18:52  Donald_Dutile
 * 	Add function prototype def. for dma_struct_alloc().
 * 	[1996/11/19  15:50:28  Donald_Dutile]
 * 
 * Revision 1.2.132.7  1996/11/01  16:50:46  Mark_Bozen
 * 	Add define of OS_POWERDOWN to support system powerdown functionality.
 * 	[1996/10/29  04:22:44  Mark_Bozen]
 * 
 * Revision 1.2.119.5  1996/10/31  19:40:56  William_Evers
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTAOS_BL4:PTBOS_BL3 **
 * 		** Ancestor revision:	1.2.125.2 **
 * 		** Merge revision:	1.2.132.6 **
 * 	 	** End **
 * 	merge of PTB BL3 changes
 * 	[1996/10/29  19:40:32  William_Evers]
 * 
 * Revision 1.2.132.6  1996/10/11  15:38:43  William_Evers
 * 	merge while re-targetting to ptbos.nightly
 * 	[1996/10/09  22:20:36  William_Evers]
 * 	implemented fw rev checking for new console env. var. functionaltiy
 * 	[1996/09/29  21:17:20  William_Evers]
 * 
 * Revision 1.2.132.5  1996/09/05  19:14:34  Thomas_Blinn
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.2.132.3 **
 * 		** Merge revision:	1.2.132.4 **
 * 	 	** End **
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rTADPOLE **
 * 		** Ancestor revision:	1.2.132.3 **
 * 		** Merge revision:	1.2.128.6 **
 * 	 	** End **
 * 	propagating tadpole
 * 	[1996/08/31  14:24:58  Thomas_Blinn]
 * 
 * Revision 1.2.132.4  1996/09/03  19:54:17  Mark_Bozen
 * 	Add defines for environmental monitoring get_info function return status
 * 	[1996/08/27  19:36:38  Mark_Bozen]
 * 
 * Revision 1.2.128.6  1996/08/30  14:44:59  Peter_Woods
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.2.128.4 **
 * 		** Merge revision:	1.2.128.5 **
 * 	 	** End **
 * 	Clarify bit definition for PSIOP_810_BURST_DISABLE
 * 	[1996/08/06  18:23:00  Peter_Woods]
 * 
 * Revision 1.2.128.5  1996/08/20  21:25:32  Thomas_Blinn
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTAOS_BL2:PTBOS_BL1 **
 * 		** Ancestor revision:	1.2.125.2 **
 * 		** Merge revision:	1.2.132.3 **
 * 	 	** End **
 * 	[1996/08/20  21:23:25  Thomas_Blinn]
 * 
 * Revision 1.2.132.3  1996/08/06  20:03:02  Mark_Bozen
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.2.125.2 **
 * 		** Merge revision:	1.2.132.2 **
 * 	 	** End **
 * 	Added new get_info functions to support environmental monitoring.
 * 	[1996/08/01  19:41:23  Mark_Bozen]
 * 
 * Revision 1.2.132.2  1996/08/05  21:56:07  William_Evers
 * 	add get_info define MP_EV_NEEDED for determining if
 * 	save_env needs to be executed on all processors.
 * 	[1996/07/26  15:00:12  William_Evers]
 * 
 * Revision 1.2.119.4  1996/07/16  17:46:35  Alex_Malone
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTOS_BL12:PTAOS_BL2 -visual **
 * 		** Ancestor revision:	1.2.82.21 **
 * 		** Merge revision:	1.2.125.2 **
 * 	 	** End **
 * 	merge of PTA BL2 changes
 * 	[1996/07/15  19:24:31  Alex_Malone]
 * 
 * Revision 1.2.128.4  1996/06/25  21:02:12  Peter_Woods
 * 	Add define for PSIOP_810_BURST_DISABLE
 * 	[1996/06/25  20:53:27  Peter_Woods]
 * 
 * Revision 1.2.128.3  1996/05/31  14:25:42  Peter_Woods
 * 	Remove changed from 1.2.128.2
 * 	[1996/05/31  14:18:14  Peter_Woods]
 * 
 * Revision 1.2.128.2  1996/05/30  14:49:03  Peter_Woods
 * 	Add GET_PCMCIA_IRQS request type so that PC Card adapters can
 * 	determined how motherboard PC card adatpeters have their interrupts
 * 	wired. We need this as PCI based PC card adapters may have their
 * 	interrupts sidebanded through the EISA/ISA interrupt logic.  Create
 * 	intr_ret_info structure for returning the above information.
 * 	[1996/05/30  14:48:20  Peter_Woods]
 * 
 * Revision 1.2.125.2  1996/05/15  20:02:00  Frederick_Canter
 * 	Add BYTEWORD_IO_CAPABLE request type. So drivers can
 * 	determine if platform supports byte/word IO.
 * 	[1996/05/15  18:17:54  Frederick_Canter]
 * 
 * Revision 1.2.119.3  1996/04/30  21:18:28  Fred_Knight
 * 	Merge from bravos.bl2
 * 	[1996/04/30  21:01:14  Fred_Knight]
 * 
 * Revision 1.2.121.2  1996/04/01  23:47:05  Donald_Dutile
 * 	hw6 merges:
 * 	 Revision 1.2.116.3  1996/02/12  21:39:45  Donald_Dutile
 * 	  Admit to using DMA_RSVD_4000 in platform DMA support
 * 	  as a platform-specific flag.  It is used by cbus2_pci.c,
 * 	  eb164.c, kn20aa.c, & pcia.c -- and now mcpcia.c.
 * 	  DMA_RSVD_4000 is not removed in HW6os to ensure source
 * 	  code compatibility for now.  To-be-cleaned-up in later
 * 	  release.
 * 	 Revision 1.2.116.2  1995/11/14  20:29:18  Donald_Dutile
 * 	  Add MCBUS entry to busses.
 * 	[1996/03/28  16:45:18  Donald_Dutile]
 * 
 * Revision 1.2.119.2  1996/03/20  21:15:19  Carolyn_Briglia
 * 	Add prototype declaration for invent_geometry().
 * 	[1996/03/15  18:40:58  Carolyn_Briglia]
 * 
 * Revision 1.2.112.5  1996/03/10  15:34:56  Ray_Lanza
 * 	merge of Platinum BL8 to BL11 pass 1 changes
 * 	[1996/03/10  15:11:04  Ray_Lanza]
 * 
 * Revision 1.2.82.21  1996/02/09  20:27:12  Paul_Grist
 * 	Add function protos for saveterm functions needed for graphics
 * 	halt problem
 * 	[1996/02/09  19:27:38  Paul_Grist]
 * 
 * Revision 1.2.82.20  1995/12/15  14:42:43  James_Smart
 * 	Add new "dev_console" structure.
 * 	Add "remoteid" to the dump_request structure.
 * 	[1995/12/11  21:41:32  James_Smart]
 * 
 * Revision 1.2.82.19  1995/12/08  22:06:07  James_Smart
 * 	Back out last mod - dump changes
 * 	[1995/12/08  21:21:52  James_Smart]
 * 
 * Revision 1.2.82.18  1995/12/06  22:56:53  James_Smart
 * 	Add "remoteid" to the dump_request structure.
 * 	[1995/12/05  14:41:15  James_Smart]
 * 
 * Revision 1.2.82.17  1995/11/14  17:58:29  Stuart_Hollander
 * 	Moved #ifdef KERNEL to encompass all of the io_resource allocation code.
 * 	[1995/11/14  16:36:42  Stuart_Hollander]
 * 
 * Revision 1.2.82.16  1995/11/13  19:05:40  Stuart_Hollander
 * 	merged pcmcia to nightly
 * 	[1995/10/26  20:28:57  Stuart_Hollander]
 * 
 * Revision 1.2.112.4  1995/11/10  23:41:24  Ray_Lanza
 * 	Merge of PTOS BL8
 * 	[1995/11/10  23:22:19  Ray_Lanza]
 * 
 * Revision 1.2.112.3  1995/10/31  23:05:04  Ray_Lanza
 * 	DELAY is a macro on intel as well
 * 	[1995/10/31  21:40:00  Ray_Lanza]
 * 	Fixed conflicting function prototypes for write_io_port
 * 	[1995/10/26  21:44:06  Ray_Lanza]
 * 
 * Revision 1.2.112.2  1995/10/25  19:55:41  Ray_Lanza
 * 	Initial __alpha conditional evaluation and changes
 * 	[1995/10/25  19:25:37  Ray_Lanza]
 * 
 * Revision 1.2.82.15  1995/10/24  18:59:27  Karl_Ebner
 * 	Topology structure pointer references eliminiated,
 * 	SS QAR 35141
 * 	[1995/10/24  18:58:12  Karl_Ebner]
 * 
 * Revision 1.2.82.14  1995/10/23  14:27:41  Jim_Hamel
 * 	Add get_info() flag PWRMGR_CAPABLE. This is used to enable
 * 	power management by default on a particular platform.
 * 	[1995/10/19  17:59:18  Jim_Hamel]
 * 
 * Revision 1.2.110.2  1995/10/04  14:55:43  Theresa_Chin
 * 	Add defines for the generic I/O resource management functions.
 * 	The bus_framework structure was modified to add request_resource() and
 * 	release_resource() routine pointers.  This reduced the 'rsvd' array
 * 	size from 5 to 3.
 * 	Add bus type for PCMCIA buses.
 * 
 * Revision 1.2.82.13  1995/09/27  22:32:45  Karl_Ebner
 * 	4.0 defines added/modified for Device Drivers
 * 	[1995/09/27  22:32:10  Karl_Ebner]
 * 
 * Revision 1.2.82.12  1995/08/22  22:23:34  Karl_Ebner
 * 	{** Merge Information **}
 * 		{** Command used:	bsubmit **}
 * 		{** Ancestor revision:	1.2.82.10 **}
 * 		{** Merge revision:	1.2.82.11 **}
 * 	{** End **}
 * 	Define collision fixed (NAME_SIZE)
 * 	[1995/08/20  17:09:56  Karl_Ebner]
 * 
 * Revision 1.2.82.11  1995/08/21  14:13:38  Peter_S_Thompson
 * 	Add get_info() flag SECONDARY_CACHE_SIZE
 * 	[1995/08/18  12:37:13  Peter_S_Thompson]
 * 
 * Revision 1.2.82.10  1995/08/07  17:28:10  Karl_Ebner
 * 	4.0 Hardware Configuration structures created to support
 * 	driver topology registration.
 * 	[1995/08/03  20:39:20  Karl_Ebner]
 * 
 * Revision 1.2.82.9  1995/07/25  18:47:46  William_Grava
 * 	fix PLite BL6 merge (3 #defines wrong)
 * 	[1995/07/25  18:45:41  William_Grava]
 * 
 * Revision 1.2.82.8  1995/07/19  20:48:08  William_Grava
 * 	merge Platinum Lite BL6 changes
 * 	[1995/07/19  20:40:46  William_Grava]
 * 
 * Revision 1.2.82.7  1995/06/29  21:22:27  William_Loeffler
 * 	Added define for PP_NETBOOT.
 * 	[1995/06/29  19:14:00  William_Loeffler]
 * 
 * Revision 1.2.82.6  1995/06/21  17:51:25  Paul_Grist
 * 	Add (pre-merge) CONSOLE_2_CTLR from hw4 pool
 * 	[1995/06/21  17:10:09  Paul_Grist]
 * 
 * Revision 1.2.82.5  1995/05/24  16:13:40  Donald_Dutile
 * 	merge of PTLITEOS-BL4 into PTOS
 * 	[1995/05/23  19:40:45  Donald_Dutile]
 * 
 * Revision 1.2.84.9  1995/05/22  21:11:32  William_Loeffler
 * 	Add define PP_NETBOOT for DMS boots.
 * 	[1995/05/22  19:23:14  William_Loeffler]
 * 
 * Revision 1.2.84.8  1995/05/16  21:18:31  Donald_Dutile
 * 	Merge of HW4OS-BL4 into PTLITEOS.
 * 	[1995/05/16  21:11:36  Donald_Dutile]
 * 
 * Revision 1.2.82.4  1995/04/28  18:44:35  Peter_S_Thompson
 * 	check-in after bmerge
 * 	[1995/04/28  18:41:40  Peter_S_Thompson]
 * 	*** empty log message ***
 * 	[1995/04/28  18:05:54  Peter_S_Thompson]
 * 	Add GET_FLAGS get_info function to return system
 * 	specific flags.  Also, GET_UNIQUE_SYSID to return
 * 	a unique sysid.
 * 	[1995/04/27  14:39:00  Peter_S_Thompson]
 * 	Removed declaration of dma_zones_init() which is no
 * 	longer used.
 * 	[1995/04/26  15:05:54  Peter_S_Thompson]
 * 
 * Revision 1.2.84.7  1995/04/24  20:36:25  Donald_Dutile
 * 	Eliminate dma_misc struct; concat private_data &
 * 	hw_sg_table_control struct into super-sglist struct.
 * 	This eliminates an indirect ref. in sg-mapping code path
 * 	and 1 MALLOC in dma_map_alloc() path.
 * 	Get rid of DMA_* flags for (former) zone-memory.
 * 	[1995/04/24  20:14:10  Donald_Dutile]
 * 
 * Revision 1.2.84.6  1995/04/24  17:22:17  Caroline_Fleming
 * 	Added two new function declarations: drvr_flush() and
 * 	drvr_register_flush().  Used to flush the cache on the
 * 	swxcr controller.
 * 	[1995/04/24  16:34:33  Caroline_Fleming]
 * 
 * Revision 1.2.84.5  1995/04/14  19:23:02  Bruce_Hansen
 * 	Removed 'GET_VIP__INFO'.
 * 	[1995/04/12  20:25:30  Bruce_Hansen]
 * 
 * Revision 1.2.84.4  1995/04/14  18:04:09  Randy_Black
 * 	Added SCLK speed constant for SCSI controllers as used on
 * 	AXPvme 64/160 systems.
 * 	[1995/04/12  14:44:07  Randy_Black]
 * 
 * Revision 1.2.92.2  1995/04/13  19:21:04  Naresh_Dharnidharka
 * 	Added CONSOLE_TO_CTLR so that platform specific getinfo routines
 * 	can return a pointer to the controller struct.
 * 	[1995/04/12  19:14:35  Naresh_Dharnidharka]
 * 
 * Revision 1.2.84.3  1995/03/27  22:24:37  Bruce_Hansen
 * 	Added get_info function 'GET_VIP_INFO' to return platform
 * 	specific handler_* functions and VMEbus IRQ to SPL mapping
 * 	information.
 * 	[1995/03/22  01:50:31  Bruce_Hansen]
 * 
 * Revision 1.2.84.2  1995/03/20  19:58:32  Randy_Black
 * 	Added get_info function 'GET_SLU_SPEED' to return clock  speed
 * 	for SLU devices.  Also added PCLK clock speed constant for SCC
 * 	devices as used on AXPvme-based systems.
 * 	[1995/03/15  18:24:00  Randy_Black]
 * 
 * Revision 1.2.82.3  1995/03/20  19:00:56  James_Smart
 * 	Add prototype declaration for get_def_partitionmap().
 * 	[1995/03/20  19:00:34  James_Smart]
 * 
 * Revision 1.2.82.2  1995/01/25  18:50:38  Thomas_Peterson
 * 	Added extern "C" block around header for C++.  Added alternate struct
 * 	member names for C++ keyword "private" under __cplusplus #ifdefs.
 * 	[1995/01/17  21:10:05  Thomas_Peterson]
 * 
 * Revision 1.2.77.3  1994/10/04  15:31:37  James_Smart
 * 	Add define(s) for known SCLK values - to be used in conjunction
 * 	with GET_810_SPEED.
 * 	[1994/09/21  19:39:00  James_Smart]
 * 
 * Revision 1.2.77.2  1994/09/06  22:17:40  William_Freeman
 * 	BMERGE
 * 	[1994/09/01  21:34:59  William_Freeman]
 * 	Expand dump_request structure for multi-volume dumps.
 * 	[1994/08/03  21:44:31  William_Freeman]
 * 
 * Revision 1.2.76.2  1994/07/14  14:58:19  James_Smart
 * 	Add getinfo function GET_810_SPEED to return clock speed for
 * 	known 810s.
 * 	[1994/06/30  21:04:17  James_Smart]
 * 
 * Revision 1.2.20.17  1994/05/31  19:47:45  Mark_Parenti
 * 	Add definition for boot_protocol_reg flags.
 * 	Increase size of members in protocol structure.
 * 	[1994/05/27  17:28:17  Mark_Parenti]
 * 
 * Revision 1.2.20.16  1994/05/27  20:06:11  William_Burns
 * 	Fix for non-mp safeness of ovrhd structure's private
 * 	field. New dma_misc structure to hold private data and
 * 	hardware scatter/gather resource data pointer.
 * 	[1994/05/26  20:16:39  William_Burns]
 * 
 * Revision 1.2.20.15  1994/04/19  21:57:47  Stuart_Hollander
 * 	merge agoshw2 bl5 to gold bl10
 * 	Revision 1.2.35.11  1994/04/15  21:45:19  Kate_Baumgartner
 * 	moved flags
 * 	[1994/04/15  21:43:10  Kate_Baumgartner]
 * 	Added DMA_CONTIG and DMA_ADDR_LIMIT flags
 * 	[1994/04/13  21:58:54  Kate_Baumgartner]
 * 
 * Revision 1.2.20.14  1994/04/15  16:12:34  Karl_Ebner
 * 	badaddr support added to to the bus framework structure.
 * 	[1994/04/13  16:53:14  Karl_Ebner]
 * 
 * Revision 1.2.20.13  1994/04/11  14:12:00  William_Burns
 * 	merge agoshw2.bl4 to gold
 * 	[1994/04/05  14:39:46  William_Burns]
 * 
 * Revision 1.2.20.12  1994/04/08  14:32:47  Mark_Parenti
 * 	Add extern for get_bus_by_name().
 * 	[1994/04/06  16:51:24  Mark_Parenti]
 * 
 * Revision 1.2.35.10  1994/03/17  20:21:04  William_Burns
 * 	Added dma flag to indicate hardware scatter gather is in use.
 * 	Added hardware scatter gather table control structure.
 * 	[1994/03/15  13:23:01  William_Burns]
 * 
 * Revision 1.2.20.11  1994/03/15  20:19:10  Mark_Parenti
 * 	Define the dev_root structure. This is passed to boot disk drivers in the
 * 	DEVROOT ioctl command.
 * 	[1994/03/12  00:31:25  Mark_Parenti]
 * 
 * Revision 1.2.35.9  1994/03/14  17:54:15  Donald_Dutile
 * 	Add structures and switch table entries for dma_get_maps().
 * 	[1994/03/10  17:38:04  Donald_Dutile]
 * 
 * Revision 1.2.35.8  1994/03/07  17:12:24  Donald_Dutile
 * 	Consume bus struct's rsvd[1,2] for bus_sw & bus_slot ptrs.
 * 	[1994/03/03  20:14:19  Donald_Dutile]
 * 
 * Revision 1.2.20.10  1994/03/03  01:02:21  Ernie_Petrides
 * 	Add missing contents intended to be added in previous revision.
 * 	[1994/03/03  01:00:51  Ernie_Petrides]
 * 
 * Revision 1.2.20.9  1994/03/02  23:07:55  Bryan_Panner
 * 	Add getinfo functions to deal with console string translation
 * 	for finder and mounting root.
 * 	[1994/03/02  18:58:58  Bryan_Panner]
 * 
 * Revision 1.2.20.8  1994/02/25  21:23:50  Stuart_Hollander
 * 	merge agoshw2 bl3 to gold
 * 	[1994/02/21  03:07:53  Stuart_Hollander]
 * 
 * Revision 1.2.35.7  1994/02/17  18:29:42  Donald_Dutile
 * 	Add new DMA_ flags per spec. and for internal (m)alloc
 * 	buffer tagging.
 * 	Change return and calling types of internal DMA support
 * 	interfaces to reduce casting done via callers.
 * 	Changed DMA_DIRECT_MAP flag, per GOLD deliverables.
 * 	[1994/02/11  21:34:42  Donald_Dutile]
 * 
 * Revision 1.2.20.7  1994/02/05  00:34:00  Joseph_Szczypek
 * 	merge of Sterling BL9 changes
 * 	[1994/02/04  23:32:58  Joseph_Szczypek]
 * 
 * Revision 1.2.35.6  1994/02/04  17:02:57  Randy_Arnott
 * 	Removed extern defines for io_bcopy() and get_io_handle().
 * 	[1994/01/27  18:33:20  Randy_Arnott]
 * 
 * Revision 1.2.20.6  1994/01/07  19:06:45  Mark_Parenti
 * 	Add BUS_PCI definition.
 * 	[1994/01/05  15:32:18  Mark_Parenti]
 * 
 * Revision 1.2.17.18  1993/12/21  22:41:57  Karl_Ebner
 * 	DMA Flags define value changed to match documentation
 * 	[1993/12/21  18:35:18  Karl_Ebner]
 * 
 * Revision 1.2.17.17  1993/12/20  21:38:52  Karl_Ebner
 * 	Duplicate READ_BUS... macros using io_handle_t's removed
 * 	[1993/12/18  21:05:46  Karl_Ebner]
 * 
 * Revision 1.2.17.16  1993/12/17  20:55:54  Randy_Arnott
 * 	Changed DENSE to DENSE_MEMORY to avoid conflict with kn15aa.
 * 	[1993/12/16  13:19:31  Randy_Arnott]
 * 	1. Added busphys_to_iohandle() to bus funcs table.
 * 	2. Added DENSE define.
 * 	3. Added busphys_to_iohandle prototype.
 * 	[1993/12/15  19:59:25  Randy_Arnott]
 * 
 * Revision 1.2.20.5  1993/12/16  14:39:38  Stuart_Hollander
 * 	merge of Sterling BL8 changes
 * 	[1993/12/15  17:21:32  Stuart_Hollander]
 * 
 * Revision 1.2.35.4  1993/12/07  18:53:51  William_Burns
 * 	Megre of AGOSHW2 to AGOSMINOR_BL8:
 * 	Revision 1.2.35.3  1993/11/02  16:08:06  William_Burns
 * 	Merge Morgan pool into agoshw2.
 * 	Revision 1.2.35.2  1993/10/26  21:12:27  Donald_Dutile
 * 	Added BUS_PCI (at 19, so it won't conflict w/Sterling's
 * 	use of 18 for BUS_SCSI).
 * 	[1993/10/26  20:58:20  Donald_Dutile]
 * 
 * Revision 1.2.17.15  1993/11/23  22:25:49  Karl_Ebner
 * 	Bus Bridge DMA added for the Turbo Channel
 * 	[1993/11/21  21:02:38  Karl_Ebner]
 * 
 * Revision 1.2.17.14  1993/11/23  21:23:24  Gary_Dupuis
 * 	Merge with top of tree.
 * 	[1993/11/23  21:00:23  Gary_Dupuis]
 * 	Add definition of bus_funcs structure.
 * 	[1993/11/18  19:29:56  Gary_Dupuis]
 * 
 * Revision 1.2.17.13  1993/11/19  14:12:38  Donald_Dutile
 * 	Merge to AGOSMINOR.
 * 	[1993/11/17  15:21:09  Donald_Dutile]
 * 	"Turn on" read_io_port function prototype decl.
 * 	Define new data type for sglist control structure: dma_handle_t;
 * 	change proto-decl's to use it for 3rd party driver clarity.
 * 	[1993/11/11  21:42:26  Donald_Dutile]
 * 
 * Revision 1.2.17.12  1993/11/15  23:11:06  Gary_Dupuis
 * 	Merge with top of AGOSMINOR submit tree.
 * 	[1993/11/15  23:06:57  Gary_Dupuis]
 * 	Remove ifdefed code from bus info structure and add comments
 * 	around bus_info_hdr definition.
 * 	[1993/11/15  22:42:05  Gary_Dupuis]
 * 	Add definition of a generic bus_info structure.
 * 	[1993/11/11  06:51:12  Gary_Dupuis]
 * 
 * Revision 1.2.17.11  1993/11/15  21:09:40  Randy_Arnott
 * 	renamed io macros from READ_D*|WRITE_D* to READ_BUS_D*|WRITE_BUS_D*
 * 	[1993/11/11  12:53:40  Randy_Arnott]
 * 	added prototype for io_zero
 * 	[1993/11/09  17:47:38  Randy_Arnott]
 * 	added READ_D* and WRITE_D* macros
 * 	[1993/11/04  20:00:22  Randy_Arnott]
 * 
 * Revision 1.2.20.4  1993/11/09  02:31:47  Randall_Brown
 * 	merge of Sterling BL7 changes
 * 	[1993/11/08  23:51:09  Randall_Brown]
 * 
 * Revision 1.2.17.10  1993/10/19  21:54:47  Randall_Brown
 * 	Revision 1.2.9.15  1993/09/23  21:16:56  Donald_Dutile
 * 	Add defines for 2 new functions:
 * 	dma_get_sglist_private(), dma_put_sglist_private()
 * 	Remove "bc" from sglist's overhead struct area &
 * 	replace it with "private" storage area.
 * 	Re-org/shuffle sglist struct for optimal comparisons
 * 	between sglist's "index" & "val_ents" values.
 * 	Fully expand/declare dma related function prototypes
 * 	for better compile-time checking.
 * 	Added function prototype decl's for read/write_io_port.
 * 	(but need to fix some other files before read_io_port
 * 	 decl can be "turned on").
 * 	Added READ/WRITE_*_D64 macros to match ALPHA-IO arch.
 * 	[1993/09/23  21:07:37  Donald_Dutile]
 * 	Revision 1.2.9.14  1993/09/17  17:56:00  Donald_Dutile
 * 	Changed bc decl in dma support to unsigned long.
 * 	Changed return value of dma alloc & load to u_long.
 * 	(Put back 1.2.9.12.)
 * 	[1993/09/13  14:09:23  Donald_Dutile]
 * 	Revision 1.2.9.13  1993/08/26  19:34:59  Randall_Brown
 * 	backed out submit 1.2.9.12
 * 	[1993/08/26  19:33:34  Randall_Brown]
 * 
 * Revision 1.2.17.9  1993/10/19  19:55:12  Fred_Knight
 * 	Add GET_TC_SPEED as a valid getinfo requests.
 * 	[1993/10/19  19:46:30  Fred_Knight]
 * 
 * Revision 1.2.17.8  1993/10/14  21:03:43  Donald_Dutile
 * 	Fix typo of io_handle_to_phys to iohandle_to_phys.
 * 	[1993/10/14  20:27:38  Donald_Dutile]
 * 	Change iohandle_to_kseg() to iohandle_to_phys.
 * 	[1993/10/08  19:07:28  Donald_Dutile]
 * 	Add HANDLE_* defines for iohandle_to_kseg function.
 * 	[1993/10/07  21:23:41  Donald_Dutile]
 * 	Add new typedef io_handle_t for io access routines.
 * 	Add function prototypes to help drivers catch
 * 	function misuse.
 * 	[1993/10/07  20:09:32  Donald_Dutile]
 * 
 * Revision 1.2.17.7  1993/09/21  21:54:05  SJ_Lee
 * 	move WBFLUSH()  define here, add <sys/types.h>
 * 	[1993/09/13  14:15:17  SJ_Lee]
 * 
 * Revision 1.2.20.3  1993/09/21  20:48:56  Randall_Brown
 * 	Merge of Maint + Sterling HW Support to Gold [robin]
 * 	[1993/09/14  19:56:57  Randall_Brown]
 * 
 * Revision 1.2.17.6  1993/09/01  16:03:28  Mark_Parenti
 * 	Add definitions and routine declarations for driver shutdown routines.
 * 	[1993/09/01  15:50:18  Mark_Parenti]
 * 
 * Revision 1.2.17.5  1993/07/30  18:31:50  Randall_Brown
 * 	Revision 1.2.9.11  1993/07/20  23:05:23  Gary_Dupuis
 * 	Merge with AGOSHW.
 * 	[1993/07/18  14:36:15  Gary_Dupuis]
 * 	Modified READ_BUSIO_D32() and READ_BUSMEM_D32() to return an
 * 	unsigned int rather than an unsigned long.
 * 	[1993/07/08  08:24:49  Gary_Dupuis]
 * 	Revision 1.2.9.10  1993/07/08  21:30:52  Donald_Dutile
 * 	Modified sglist struct and added overhead structure
 * 	    for "super" sglist.
 * 	Added extern declarations for dma zone memory interfaces
 * 	    and additional get/put sgentry functions.
 * 	[1993/07/07  18:38:10  Donald_Dutile]
 * 	Revision 1.2.9.9  1993/06/30  20:33:18  Donald_Dutile
 * 	Prefix dma_ to get_next_entry() declaration.
 * 	Changed return values of dma alloc & load routines
 * 	to byte-count values instead of ptrs. to sglist structs.
 * 	[1993/06/22  17:30:29  Donald_Dutile]
 * 	Change READ* and WRITE* macros to use the generic
 * 	read_io_port() and write_io_port() routines, not a
 * 	jump through the cpusw table directly.
 * 	Added structure, typedef and defines for the generic
 * 	dma support.
 * 	[1993/06/15  02:23:08  Donald_Dutile]
 * 
 * Revision 1.2.20.2  1993/07/29  21:27:01  Brian_Stevens
 * 	Definition of dump_request.
 * 	[1993/07/29  21:06:27  Brian_Stevens]
 * 
 * Revision 1.2.17.4  1993/07/27  14:39:24  Bryan_Panner
 * 	Added get_info structures.
 * 	[1993/07/23  20:22:58  Bryan_Panner]
 * 
 * Revision 1.2.17.3  1993/06/24  22:37:30  Randall_Brown
 * 	Submit of AGOSHW pool into Sterling
 * 	[1993/06/24  21:19:23  Randall_Brown]
 * 
 * Revision 1.2.9.8  1993/06/15  03:14:46  Gary_Dupuis
 * 	Submitting this for Don Dutile.
 * 	Change READ* and WRITE* macros to use the generic
 * 	read_io_port() and write_io_port() routines, not a
 * 	jump through the cpusw table directly.
 * 	Added structure, typedef and defines for the generic
 * 	dma support.
 * 	[1993/06/15  03:08:19  Gary_Dupuis]
 * 
 * Revision 1.2.17.2  1993/06/10  18:36:49  SJ_Lee
 * 	Add badaddr to bus_ctlr_common.
 * 	[1993/06/02  19:37:09  SJ_Lee]
 * 
 * Revision 1.2.9.7  1993/05/19  19:36:56  Gary_Dupuis
 * 	Merge with Ag maintenance BL3.
 * 	[1993/05/19  19:11:56  Gary_Dupuis]
 * 
 * Revision 1.2.9.6  1993/05/04  21:33:30  Gary_Dupuis
 * 	Remove access width defines (no longer used). Removed BUS_LOCAL
 * 	from access types. Add io access macros.
 * 	[1993/05/04  21:29:02  Gary_Dupuis]
 * 
 * Revision 1.2.12.2  1993/04/08  18:19:19  Bryan_Panner
 * 	Added a structure which collected all the dump device
 * 	info needed to dump to a device via console call backs
 * 	[1993/04/08  11:33:17  Bryan_Panner]
 * 
 * Revision 1.2.9.5  1993/04/06  15:56:17  Gary_Dupuis
 * 	Add IO_ to bus access widths to avoid conflict with other defines
 * 	of WORD. Add BUS_LOCAL to access types. Removed NVRAM from access
 * 	types.
 * 	[1993/04/06  15:18:34  Gary_Dupuis]
 * 
 * Revision 1.2.9.4  1993/03/08  21:13:45  Gary_Dupuis
 * 	Add defines for IO bus access width and access type.
 * 	[1993/03/08  20:23:58  Gary_Dupuis]
 * 
 * Revision 1.2.3.10  1992/11/24  16:31:34  Joseph_Amato
 * 	Revision 1.2.17.6  1993/09/01  16:03:28  Mark_Parenti
 * 
 * Revision 1.2.9.3  93/01/06  15:20:54  Timothy_Burke
 * 	Jensen BL9 to BL11 merge.
 * 	[93/01/06  15:19:53  Timothy_Burke]
 * 
 * Revision 1.2.9.2  92/10/12  07:46:57  Gary_Dupuis
 * 	Tim - Added ISA & EISA bus type defines.
 * 	[92/10/09  10:03:09  Gary_Dupuis]
 * 
 * Revision 1.2.3.9  92/10/07  08:26:23  Joseph_Amato
 * 	increase size of private, conn_priv, rsvd arrays
 * 	[92/10/06  14:14:19  Joseph_Amato]
 * 
 * Revision 1.2.3.8  92/06/03  16:23:24  Peter_Schulter
 * 	merged in Silver BL7
 * 	Revision 1.1.3.9  92/05/21  11:29:55  William_Burns
 * 	Ansify endifs.
 * 	[92/05/15  11:52:13  William_Burns]
 * 
 * Revision 1.2.3.7  92/04/18  16:54:19  Shashi_Mangalat
 * 	Restored bus_hd field lost in BL6 merge.
 * 	[92/04/18  16:53:12  Shashi_Mangalat]
 * 
 * Revision 1.2.3.6  92/04/15  10:18:27  Peter_Schulter
 * 	Put #ifndef __alpha around declarations of external symbols which
 * 	are macros on Alpha.
 * 	[92/04/15  10:10:35  Peter_Schulter]
 * 
 * Revision 1.2.3.5  92/04/14  15:31:47  Peter_Schulter
 * 	merged in Silver BL6
 * 	Revision 1.1.3.8  92/03/24  09:07:08  Jeff_Anuszczyk
 * 	Add MP macros to lock the hardware topology tree.
 * 	[92/03/19  17:42:59  Jeff_Anuszczyk]
 * 	Revision 1.1.3.7  92/03/13  17:28:40  halproject_Donald_Dutile
 * 	Merge to AG from HALPROJECT
 * 	[92/03/13  16:49:00  halproject_Donald_Dutile]
 * 	Added extern statements for BADADDR() & DELAY().
 * 	[92/03/09  22:08:54  Donald_Dutile]
 * 	Revision 1.1.3.6  92/03/12  13:36:37  Timothy_Burke
 * 	Merged to ag.latest.
 * 	[92/03/11  10:57:14  Timothy_Burke]
 * 	Re-integrated MSI & CI bus types.
 * 	[92/03/10  10:38:13  Timothy_Burke]
 * 	Added fields for loadable driver support.
 * 	[92/03/09  19:46:50  Timothy_Burke]
 * 	Revision 1.1.3.5  92/03/10  10:13:48  Joseph_Amato
 * 	fix typo missing ";"
 * 	[92/03/10  10:10:35  Joseph_Amato]
 * 	Revision 1.1.3.4  92/03/09  10:39:26  Joseph_Amato
 * 	add mailbox ptr to keep data structure in synch with alpha
 * 	[92/03/09  08:45:44  Joseph_Amato]
 * 	Revision 1.1.3.3  92/02/24  11:46:36  Peter_Keilty
 * 	bmerge against ag.latest
 * 	[92/02/23  13:35:02  Peter_Keilty]
 * 	Initial checkin of DSA IO subsystem and
 * 	related system files
 * 	[92/02/12  18:37:21  Peter_Keilty]
 * 
 * Revision 1.2.3.4  92/04/06  18:11:01  Jim_Campbell
 * 	Delayed silver BL5 merge. Resolved conflicts between silver and alpha
 * 	bus numbering.
 * 	[92/04/06  18:08:17  Jim_Campbell]
 * 
 * Revision 1.2.3.3  92/03/18  13:48:36  Peter_Schulter
 * 	merged in Silver BL5
 * 	 * Revision 1.1.3.3  92/02/24  11:46:36  Peter_Keilty
 * 	 *    bmerge against ag.latest
 * 	 *    [92/02/23  13:35:02  Peter_Keilty]
 * 	 *
 * 	 *    Initial checkin of DSA IO subsystem and
 * 	 *    related system files
 * 	 *    [92/02/12  18:37:21  Peter_Keilty]
 * 	 *
 * 	[92/03/18  13:47:31  Peter_Schulter]
 * 
 * Revision 1.2.3.2  92/02/02  20:36:01  Joseph_Amato
 * 	Added #defines for LBUS and FBUS
 * 	[92/01/29  17:15:59  Joseph_Amato]
 * 
 * Revision 1.2  92/01/15  01:44:31  devbld_gsf
 * 	Baselevel alpha_bl002
 * 
 * Revision 1.1.6.2  91/12/31  08:29:19  Joseph_Amato
 * 	Changed private, conn_priv and rsvd fields from caddr_t to void *
 * 	Created a new common structure bus_ctlr_common that has the pointers to
 * 	the bus_hd and mbox.
 * 
 * Revision 1.1.3.3  91/12/09  11:34:19  Jim_Campbell
 * 	Included updated bus structure and lsb defines from ODE merge...
 * 	[91/12/09  10:33:38  Jim_Campbell]
 * 
 * Revision 1.1.3.2  91/11/20  13:57:28  Hal_Project
 * 	Moved & derived from dec/machine/common; pool reorg
 * 	[91/11/18  08:39:33  Donald_Dutile]
 * 
 * Revision 4.2  91/09/19  23:17:37  devbld
 * 	Adding ODE Headers
 * 
 * 
 * $EndLog$
 */

/*
 *	@(#)$RCSfile: devdriver.h,v $ $Revision: 1.2.286.6 $ (DEC) $Date: 2008/02/13 05:59:28 $
 */
/*
 * OSF/1 Release 1.0
 */
/* 
 * New in OSF/1
 */

/*
 * Abstract:
 *	This module contains the definitions for the various data structures
 *	used by device drivers and configuration code.
 *
 * Revision History
 *
 *	25-Jan-1991	Mark Parenti (map)
 *		Original Version
 */

#ifndef DEVDRIVER_HDR
#define DEVDRIVER_HDR
#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

/*
 * Declare the DDI/DKI level that this OS rev supports as its base.
 *   DDIDKI_VERSION_MAJOR    : Interface Compatibility Level
 *   DDIDKI_VERSION_MINOR    : Binary Compatibility Level
 *   DDIDKI_VERSION_REV      : Interface Revision Level
 */
#define DDIDKI_VERSION_MAJOR        5
#define DDIDKI_VERSION_MINOR        0
#define DDIDKI_VERSION_REV          2


/* forward declarations for C++ */
#ifdef __cplusplus
struct bus;
struct controller;
struct port;
struct bus_framework;
struct device;
struct driver;
struct proc;
struct tc_info;
#endif

struct bus_ctlr_common {
	u_long *mbox;
	struct bus *bus_hd;
        u_long pad1;
        u_long pad2;
        u_long pad3;
        int    type;
};

typedef struct bus_ctlr_common * bus_ctlr_common_t;

#ifdef _KERNEL
#include <io/common/handler.h>	
#include <sys/proc.h>
#include <mach/machine/vm_types.h>
#include <ksm/ksm.h>
#endif /* _KERNEL */

#ifdef _KERNEL
extern struct bus       *system_bus;    /* Pointer to nexus bus structure */
#endif /* _KERNEL */
/*
 * Define the MP lock macros for the hardware topology tree created
 * with the structures defined in the header file.  This lock is
 * intended to protect the entire topology tree since access to the
 * tree will most likely be very seldom.  Also, static initialization
 * of the tree need not get the lock since we are known to be single
 * threaded (not multi-user).
 */
#ifdef _KERNEL


/* The topology lock */
decl_simple_lock_data(extern, topology_tree_lock)
decl_simple_lock_info(extern, topology_tree_lockinfo)

extern int topology_lock_holder;  /* Which cpu has the lock? 
				   * (-1 means no one has it) */
extern int topology_locks_held;   /* A reference count for the topo.
				     lock */
extern int topology_lock_initialized;


/*
 * Simple Topology Locks (QAR 97736):
 *
 * A simple lock helps prevent topology structure corruption.  The
 * primary goal is to prevent corruption of the linked lists of
 * dynamic structures:
 *	dynamic_bus_list_head
 *	dynamic_ctlr_list_head
 *	dynamic_device_list_head, 
 *	template_bus_list_head,
 *	template_ctlr_list_head  
 *
 * If it goes beyond that and applies coherency to the data structures
 * in the static lists (bus_list, device_list, controller_list), that
 * is good, though it is not likely to be needed there (this type of
 * corruption was not seen in the QAR above)
 *
 * REQUIREMENTS
 * 
 * - Recursive Locking
 *	Because this is a "refurbishment" to a twisted and complex
 *	code base, the locks should be able handle nested locking
 *	calls in an environment where we cannot tell whether the
 *	caller already has the lock or not.  It should be able to
 *	handle both cases.
 *
 * - Early Bird Callers
 *	Since callers can call us before locks are initialized, the
 *	LOCK_TOPOLOGY_TREE macro should checks to see whether the lock
 *	has been initialized before it proceeds.  Of additional
 *	concern is the possibility that a calling thread might have
 *	originated and called LOCK_TOPOLOGY_TREE before the lock was
 *	available, and might have continued executing through the
 *	initialization of the lock (I've no proof that this happens,
 *	its just a thought).  Therefore, the UNLOCK_TOPOLOGY_TREE
 *	macro must make sure the lock is actually held, not just that
 *	the lock was initialized.
 *
 * - SPL Synchronization
 *	Callers can come from interrupt context and at non-zero SPL,
 *	so we have to use simple locks.  We want to raise SPL to at
 *	least 4 to block the calling thread from being taken off the
 *	cpu by the kernel scheduler (SPLBIO blocks preemption and
 *	assures synchronization with interrupt routines).  Since we
 *	have to assume we might be called from even higher than this,
 *	we make sure to check current SPL before setting SPL to
 *	SPLBIO.
 * 
 * - Prevent Regressions With Thread Blocking Code Paths
 *	Also, since we are inserting simple locks in the middle of a
 *	code path, we have to make sure that this code path does not
 *	go on to do things that you cannot do while holding a simple
 *	lock (thread blocking caused by malloc without M_NOWAIT or
 *	trying for complex locks).
 *	Care must be taken to trace each code path that has these new
 *	locks and make sure they would never thread_block while they
 *	have the simple topology lock.
 *
 * 
 * DECLARATION
 *	The caller must use a macro to declare a routine's intent to
 *	use the LOCK and UNLOCK macros.  The declaration takes care of
 *	any data members that need to be declared in the routines
 *	using the LOCK/UNLOCK macros.
 *
 *
 * LOCKING 
 *	To support nested (recursive) locking, the call to
 *	simple_lock() is dependent on this thread not already having
 *	the lock.
 *
 *	First check to see if locks are initialized, then check to see
 *	whether we already have the lock.  If we don't already have
 *	the lock, try to take it.  After we get the lock (or we have
 *	established that we already have the lock), increment a
 *	reference count and mark the global variable indicating that
 *	the current CPU has it.
 *
 *	If our CPU (this routine or one of its callers somewhere up
 *	the stack) has already taken the lock, we will not take the
 *	lock again. Instead, we will just increment a reference count.
 * 
 *
 * UNLOCKING
 *	To support nested (recursive) locking, simple-unlocking is
 *	dependent on a zero reference count...and this thread must
 *	actually have the lock, of course.
 *
 *	Theoretically, there is always a chance that a previous LOCK
 *	macro was called before the lock was available, and we are now
 *	called to unlock after lock becomes available. In this case,
 *	the LOCK macro would not have taken the lock, so the UNLOCK
 *	macro must not attempt to release the lock.  Checking for
 *	simple_lock_holder() will ensure correct behavior.
 *
 */
#define DECL_TOPOLOGY_LOCK \
    int _ss; 

#define LOCK_TOPOLOGY_TREE			\
    if (topology_lock_initialized && !panicstr)	\
    {						\
        _ss = getspl();				\
        if (_ss < SPLHIGH) {			\
            _ss = splhigh();			\
        }					\
        if (topology_lock_holder != mfpr_whami()) {\
            simple_lock(&topology_tree_lock);	\
            topology_lock_holder = mfpr_whami();\
        }					\
        topology_locks_held++;			\
        					\
    }						

/* 
 * If we are the lock holder, and we previously took the lock,
 * decrement our reference counter.
 * 
 * If our reference counter is zero (i.e. we are the last one out),
 * release the lock; if we previously raised SPL, lower it, too.
 *
 * Also, update the topology_lock_holder variable, which keeps track
 * of which cpu holds the topology thread (we put a -1 in there on our
 * way out to say that no one holds it now).  this variable is also
 * protected by the topology lock.
 *
 */
#define UNLOCK_TOPOLOGY_TREE			\
    if (topology_lock_initialized &&		\
        topology_lock_holder == mfpr_whami() &&	\
        !panicstr)				\
    {						\
        topology_locks_held--;			\
        if (topology_locks_held == 0) {		\
            topology_lock_holder = -1;		\
            simple_unlock(&topology_tree_lock);	\
        					\
            if (_ss < SPLHIGH) {		\
                splx(_ss);			\
            }					\
        } 					\
        else if (topology_locks_held < 0) {	\
            panic("topology_locks_held is negative\n"); \
        }					\
    }


#define TOPOLOGY_TREE_LOCK_INIT     					\
    simple_lock_setup(&topology_tree_lock, topology_tree_lockinfo);	\
    topology_lock_initialized = 1;
 
#endif /* _KERNEL */


/* 
 * hwconfig Operation Type Definition 
 *
 *   These flags are looked at by the driver framework common code and 
 * the bus specific support code support in order to execute a hardware 
 * configuration request. 
 *
 * Support Flag Combinations used by driver_framework() kernel interface:
 *
 *
 * HWCONFIG_CONTROLLER_ALL | HWCONFIG_CONFIGURE_REQUEST
 *     Configure all controller instances and load the device driver
 *     if necessary. All here refers to "in the system" or in a specific 
 *     bus instance.
 *
 * HWCONFIG_CONTROLLER_ALL | HWCONFIG_UNCONFIGURE_REQUEST
 *     Unconfigure all contoller instances an leaves the device driver
 *     loaded in the kernel. All here refers to "in the system" or
 *     in a specific bus instance.
 *
 * HWCONFIG_CONTROLLER_ALL | HWCONFIG_UNCONFIGURE_REQUEST | HWCONFIG_UNLOAD_REQUEST
 *     Unconfigure all controller instances and unload the device driver
 *     from kernel memory.
 *
 * HWCONFIG_CONTROLLER_INSTANCE | HWCONFIG_CONFIGURE_REQUEST
 *     Configure a specific controller instance into the kernel and load the
 *     device driver if necessary. This request uses the bus type,
 *     bus instance and the instance info field of the hwconfig struct.
 *
 * HWCONFIG_CONTROLLER_INSTANCE | HWCONFIG_UNCONFIGURE_REQUEST
 *     Unconfigure a specific controller instance from the kernel and leave
 *     the device driver loaded.  This request uses the bus type, 
 *     bus instance and the instance info field of the hwconfig struct.
 *
 * HWCONFIG_BUS | HWCONFIG_CONFIGURE_REQUEST
 *     Configure a specific adapter instance into the kernel and load the device driver
 *     if necessary.
 *
 * HWCONFIG_BUS | HWCONFIG_UNCONFIGURE_REQUEST
 *     Unconfigure a specific adapter instance from the kernel and leave the driver
 *     loaded.
 *
 * HWCONFIG_BUS | HWCONFIG_UNCONFIGURE_REQUEST | HWCONFIG_UNLOAD_REQUEST
 *     Unconfigure a specific adapter instance from the kernel and unload the adapter
 *     driver from the kernel.
 *
 * HWCONFIG_LOAD_MODULE | HWCONFIG_CONFIGURE_REQUEST
 *     Configure all controller instances and load the device driver
 *     if necessary. All here refers to "in the system" or in a specific 
 *     bus instance.
 *
 *   The type field definition above set the scope of the configuration request while
 * the remaining fields of the hwconfig struct help to tailor and define the precise
 * configration request when required.
 *
 */

#define	HWCONFIG_CONTROLLER_ALL		0x001UL	/* Configures all ctlrs in   */
						/*  system */
#define	HWCONFIG_CONTROLLER_INSTANCE	0x002UL	/* Configure/unconfigure ctlr*/
						/*  instance */
#define	HWCONFIG_BUS			0x004UL	/* Configures a bus */
#define	HWCONFIG_BUS_ALL		0x004UL	/* Configures a bus */
#define HWCONFIG_BUS_INSTANCE		0x080UL /* Configure/unconfigure bus */
						/*  instance                 */
#define	HWCONFIG_DEVICE_ALL		0x010UL	/**/
#define	HWCONFIG_DEVICE_INSTANCE	0x020UL	/**/
#define	HWCONFIG_UNLOAD_MODULE		0x040UL	/* Unload a module  */

#define	HWCONFIG_LOAD_MODULE		0x008UL	/* Load an ordinary module   */
#define HWCONFIG_UNLOAD_MODULE		0x040UL /* Unload an ordinary module */
#define	HWCONFIG_TYPE_MASK		0xFFFUL   

/**/
#define	HWCONFIG_CONFIGURE_REQUEST	0x10000000UL
#define	HWCONFIG_UNCONFIGURE_REQUEST	0x20000000UL
#define	HWCONFIG_UNLOAD_REQUEST		0x40000000UL

/* 
 *  Parent Bus Definition
 *
 *  This field is important to the driver framework when the caller want to restrict
 *  or target a configuration request at a specific bus or controller instance.
 *
 *  For example: using driver_framwork() to:
 *
 *  1. configure all xyz contorllers on a Digital UNIX system
 *
 *     A driver_framework() configuration request that wants to configure all xyz ctlrs 
 *  in the system would indicate the type of operation to be HWCONFIG_CONTROLLER_ALL,
 *  the parent bus would be set to HWCONFIG_ALL and the bus instance field would be set
 *  to WILDNUM. This would indicated that all buses in the system would be effected in 
 *  in the system.
 *
 *  2. configure all xyz controllers on pci1000 of a Digital UNIX system
 *
 *     A driver_framework() configuration request that wants to configure all xyz 
 *  ctlrs on the pci1000 would indicate the type of operation to be HWCONFIG_CONTROLLER_ALL,
 *  the parent bus would be set to HWCONFIG_PCI the bus instance field would be set
 *  to 1000.
 *
 *  3. configure a single instance of the xyz controller on pci1000 of a Digital UNIX system
 *
 *     A driver_framework() configration request would set the operation to
 *  HWCONFIG_CONTROLLER_INSTANCE, the parent bus would be set to HWCONFIG_PCI, the bus
 *  instances field would be set to 1000 and the instance_info field would be set to
 *  the pcislot that contains the device to be configured.
 * 
 */
#define	HWCONFIG_PCI 		"pci"   /* PCI bus configuration*/
#define	HWCONFIG_ISA 		"isa"   /* ISA bus configuration*/
#define	HWCONFIG_EISA		"eisa"  /* EISA bus configuration*/
#define	HWCONFIG_VME 		"vme"   /* VME bus configuration*/
#define	HWCONFIG_PCMCIA 	"pcmcia"/* PCMCIA bus configuration*/
#define	HWCONFIG_ALL 		"*"     /* ALL buses*/
 
/* Hardware configuration structure
 *
 *   This structure is used to describe a configuration request to 
 * the driver_framework() kernel interface.
 *
 */

struct hwconfig {
	ulong	type;			/* Type of driver framework support to be configured */
	char	*parent_bus;		/* The bus that contains hardware to be configured   */
	long 	parent_bus_instance; 	/* The bus instance containing hardware to config    */
	char 	*driver_name;		/* The subsystem name of the driver to be configured */
	long	instance_info;		/* Bus specific instance information. Generally Slot 
					 * information but is bus specific.
					 */
 	struct 	driver *driver_struct;  /* Internal rsvd pointer to driver struct            */
	char	*target_name;		/* Internal rsvd name of the target to be unconfigure*/
	int	target_num;		/* Internal rsvd instance of target		     */
	struct bus *bus_ptr;		/* Parent bus pointer				     */
	char	*module_list;		/* Associated subsystem's to be loaded               */
	ulong	rsvd[3];		/* These fields are reserved by the driver framework 
					 * for future non slot bus configuration requirements*/
};

struct module_load {
	struct module_load *nextptr;	/* The next struct in the list    */
	char	*driver_name;		/* The driver module to load      */
	char	*module_list;		/* The list of associated modules */
					/*  to load                       */
	int	type;			/* Type of config requested       */
        char	*parent_bus;		/* Name of parent bus             */
	long	parent_bus_instance;    /* Pointer to the instance on the */
					/*  parent bus                    */
	long	instance_info;		/* Bus specific instance          */
					/*   information. Generally Slot  */
					/*   information but is bus       */
					/*   specific.                    */
	struct bus *bus_ptr;		/* Pointer to the parent bus      */
};


/*
 * Key lookup
 */

struct persistence_request
{
   int		version;		/* The current version		*/
   int		command;		/* The command.  (See below)	*/
   int		instance;		/* Where the instance number	*/
					/*   is returned or passed in	*/
   int		reserved1;		/* Reserved for future use	*/
   char		*name;			/* Name of the driver		*/
   char		*key;			/* Key to lookup or store	*/
   ulong	data_field1;		/* Generic return data field	*/
   ulong	data_field2;		/* Generic return data field	*/
   ulong	data_field3;		/* Generic return data field	*/
   ulong	reserved2;		/* Reserved for future use	*/
};
   
#define  PERSISTENCE_STRUCT_VERSION	0

/*
 * Persistence_request command types
 */
#define  PERSISTENCE_REQUEST_STORE	0
#define  PERSISTENCE_REQUEST_FETCH	1
#define  PERSISTENCE_REQUEST_DELETE	2

#define  PERSISTENCE_STRUCT_MAX_KEY_LENGTH	64

/* bus structure - 
 *
 *	The bus structure is used to describe a bus entity. A bus is an entity
 *	(real or imagined) to which other buses or controllers are logically
 *	attached. All systems have at least one bus, the system bus.
 */

struct	bus {
	u_long		*bus_mbox;
	struct bus	*nxt_bus;	/* next bus			*/
	struct controller *ctlr_list;	/* controllers connected to this bus */
	struct bus	*bus_hd;	/* pointer to bus this bus connected to */
	struct bus	*bus_list;	/* buses connected to this bus */
	int		bus_type;	/* bus type			*/
	char		*bus_name;	/* bus name 			*/
	int		bus_num;	/* bus number			*/
	int		slot;		/* node or slot number		*/
	char		*connect_bus;	/* bus connected to		*/
	int		connect_num;	/* bus num connected to		*/
	int		(*confl1)();	/* Level 1 configuration routine */
	int		(*confl2)();	/* Level 2 configuration routine */
	char		*pname;		/* port name, if needed		*/
	struct port	*port;		/* pointer to port structure	*/
	int		(**intr)();	/* interrupt routine(s) for this bus */
	int		alive;		/* See bit definitions below	*/
	struct bus_framework *framework; /* Bus rtns for loadable drivers*/
	char            *driver_name;   /* Name of controlling driver */
#ifndef __cplusplus
	void		*private[8];	/* Reserved for this bus use	*/
#else
	void		*bprivate[8];	/* "private" is reserved word in C++ */
#endif
	void		*conn_priv[8];	/* Reserved for connected bus use */
        void            *bus_bridge_dma;/* Field used to signify Hardware DMA */  
	void		*bus_sw;	/* Bus-(hw-)specific switch table */
	void		*bus_slot;	/* Bus slot table 		*/
	int		(*unconfl1)();	/* bus unconfiguration routine 	*/
	u_int		phys_bus_num;	/* Physical primary bus number     */
	u_int		phys_subbus_num;/* Physical subordinate bus number */
	void            *bus_ehm_config_ptr;
					/* Pointer to our callback data */
	void		*rsvd[2];	/* Reserved for future expansion   */
};

typedef	unsigned long	io_handle_t;

/* bus info structure
 *
 *	The bus info structure is used to pass certain information between
 *	a bus and another bus or an adapter connected in an hierarchical
 *	manner. The flow of information is from parent to child. 
 *	Typically the bus info structure is parent bus specific, i.e. it
 *	contains information the parent bus knows about and wants to pass
 *	on to its children. It does not contain information specific to
 *	the child. Since the information contained in the structure is
 *	specific to the parent bus its format is defined by that bus
 *	and will most likely vary from bus to bus. However there is a
 *	common set of data that all busses will know and will want to
 *	pass to there children. This information is contained in the
 *	common_bus_info structure defined below. The first element of
 *	every bus info structure should be a pointer to this
 *	common_bus_info structure.
 *	
 *	+----------------------------------------+
 *	|  Pointer to common info block  	 |
 *	|  (this is a struct common_bus_info *)  |
 *	+----------------------------------------|
 *	|  Bus specific data block elements      |
 *	|		    :			 |
 *	|		    :			 |
 *	+----------------------------------------+
 *
 *	Those busses that do not have any bus specific data can use
 *	the bus_info_hdr structure defined below as their bus info
 *	structure.
 */

struct	common_bus_info 
        {
	int		(**intr)();	/* Intr. routine for the child bus */
					/* adapter. 			   */
	io_handle_t	sparse_io_base; /* Base address of child's bus-io */
					/* space.  			  */
	io_handle_t	sparse_mem_base;/* Base address of child's */
					/* bus-memory space.       */ 
	vm_offset_t	dense_mem_base;	/* Base address of child's */
					/* bus-memory  space.      */
	};

struct	bus_info_hdr
   {
   struct  common_bus_info	*common_infop;
   };


typedef	char	*bus_addr_t;

/*
 * DMA window info data structure
 */
struct dma_map_info {
		vm_offset_t    phys_base;  /* phys. mem. window maps to */
		bus_addr_t     ba_base;	   /* base bus addr of DMA window */
		u_int          map_size;   /* size of window in Mbytes */
		u_int	       type;	   /* SG or DIRECT */
		struct dma_map_info *next; /* next in linked list */
};

typedef struct dma_map_info *dma_map_info_t;

#define DMA_WINDOW_TYPE_DIRECT	  0x01
#define DMA_WINDOW_TYPE_SG	  0x02
#define DMA_WINDOW_TYPE_64BIT     0x10

/* bus function table
 *
 *	Table of bus specific functions used by device drivers. This table
 *	is loaded by the bus configuration code and is then attached to the
 *	bus' bus structure at private[0]. The wrapper functions (in
 *	driver_support.c), which all have a device's controller function as
 *	an argument, follow the bus_hd pointer to get to the bus structure
 *	and then to the correct function for the bus they are attached to.
 */

struct	bus_funcs
   {
   void	(*do_config)();		/* Function to initialize option. */
   int	(*get_config)();	/* Function to get config info for option */
   void	(*enable_option)();	/* Function for enabling option interrupts */
   void	(*disable_option)();	/* Function for disabling option interrupts */
   io_handle_t (*busphys_to_iohandle)(); /* Function to generate an io handle
					     from a bus physical address */
   dma_map_info_t (*dma_get_maps)(); /* Function to get dma window info */
   };

/*
 *	Location in ctlr.conn_priv[] where we plug in the pointer to the
 *	bus function table.
 */
#define	busfuncs	private[0]


/* controller structure - 
 *
 *	The controller structure is used to describe a controller entity. A
 *	controller is an entity which connects logically to a bus. A controller
 *	may control devices which are directly connected, such as disks or
 *	tapes, or may perform some other controlling operation such as 
 *	network interface.
 */

struct	controller {
	u_long		*ctlr_mbox;
	struct controller *nxt_ctlr;	/* pointer to next ctlr on this bus */
	struct device	*dev_list;	/* devices connected to this ctlr */
	struct bus	*bus_hd;	/* pointer to bus for this ctlr   */
	struct driver	*driver;	/* pointer to driver structure for */
					/* this controller 		   */
	int		ctlr_type;	/* controller type		*/
	char		*ctlr_name;	/* controller name		*/
	int		ctlr_num;	/* controller number		*/
	char		*bus_name;	/* bus name			*/
	int		bus_num;	/* bus number connected to 	*/
	int		rctlr;		/* remote controller number	*/
					/* e.g. ci node or scsi id	*/
	int		slot;		/* node or slot number		*/
	int		alive;		/* See bit definitions below	*/
	char		*pname;		/* port name			*/
	struct port	*port;		/* port structure		*/
	int		(**intr)();	/* interrupt routine(s) for this ctlr */
	caddr_t		addr;		/* virtual address of controller */
	caddr_t		addr2;		/* virtual address of second ctlr */
					/* register space		  */
	int		flags;		/* flags from config line	*/
	int		bus_priority;	/* bus priority from from config */
	int		ivnum;		/* interrupt vector number	*/
	int		priority;	/* system ipl level		*/
	int		cmd;		/* cmd for go routine		*/
	caddr_t		physaddr;	/* physical address of addr	*/
	caddr_t		physaddr2;	/* physical address of addr2	*/
#ifndef __cplusplus
	void		*private[8];	/* Reserved for ctlr use	*/
#else
	void		*cprivate[8];	/* "private" is reserved word in C++ */
#endif
	void		*conn_priv[8];	/* Reserved for connected bus use */
	void		*rsvd[8];	/* reserved for future expansion */
};

/* device structure -
 *
 *	The device structure is used to describe a device entity. A device
 *	is an entity that connects to, and is controlled by, a controller.
 */

struct	device {
	struct device	*nxt_dev;/* pointer to next dev on this ctlr */
	struct controller *ctlr_hd;	/* pointer to ctlr for this device */
	char		*dev_type;	/* device type			*/
	char		*dev_name;	/* device name			*/
	int		logunit;	/* logical unit	number		*/
	int		unit;		/* physical unit number		*/
	char		*ctlr_name;	/* controller name connected to */
	int		ctlr_num;	/* controller number for this device */
	int		alive;		/* See bit definitions below	*/
#ifndef __cplusplus
	void		*private[8];	/* reserved for device use	*/
#else
	void		*dprivate[8];	/* "private" is reserved word in C++ */
#endif
	void		*conn_priv[8];	/* Reserved for connected controller use */
	void		*rsvd[8];	/* reserved for future expansion */
};

/* Defines for device private structures */
#define dstats		private[1]
#define diskstat_i	private[2]

/* port structure - 
 *
 *	The port structure is used to contain information about a port.  A port
 *	is ??
 */

struct	port {
	int	(*conf)();		/* config routine for this port */
};

/* driver structure - 
 *
 *	The driver structure contains information about driver entry points
 *	and other driver-specific information.
 */

struct	driver {
	int	(*probe)();		/* see if a driver is really there */
	int	(*slave)();		/* see if a slave is there */
	int	(*cattach)();		/* controller attach routine */
	int	(*dattach)();		/* device attach routine */
	int	(*go)();		/* fill csr/ba to start transfer */
	caddr_t	*addr_list;		/* device csr addresses */
	char	*dev_name;		/* name of device which connects to */
					/* this controller		    */
	struct	device **dev_list;	/* backpointers to driver structs */
					/* indexed with device logunit    */
	char	*ctlr_name;		/* name of controller */
	struct	controller **ctlr_list;	/* backptrs to controller structs */
					/* indexed with controller number */
	short	xclu;			/* want exclusive use of bdp's */
	int	addr1_size;		/* size of first csr area */
        int	addr1_atype;	 	/* address space of first csr area */
	int	addr2_size;		/* size of second csr area */
        int	addr2_atype;	 	/* address space of second csr area */
	int	(*ctlr_unattach)();	/* controller unattach routine */
	int	(*dev_unattach)();	/* device unattach routine */
};

struct console_device {
	char	protocol[20];
	int	hose;
	int	slot;
	int	channel;
	int	remote_addr;
	int	unit;
	char	*boot_dev_type;
	char	*ctlr_dev_type;
	caddr_t	srm_suffix;
};

/*
 * The dev_trans_req structure is used within the kernel when calling the
 * device_translate routine to translate a device name from the console to
 * the Digital UNIX information on the device.
 */

typedef struct dev_trans_req {
	int	dt_version;		/* version of this structure = 1 */
	int	dt_flags;		/* flags - all 0 for now */
	int	dt_opcode;		/* operation requested
					   see below for the valid values */
	dev_t	dt_ldevt;		/* local dev_t for this device */
	char	*dt_console_str;	/* pointer to the console name of
					   the device to be translated */
	char	*dt_dsf_name;		/* NULL or pointer to the string for
					   the device special file base name
					   of this device - caller allocates
					   the array of characters - at least
					   BOOTDEVLEN (80) characters long -
					   routine initializes the string */
	long	dt_hw_id;		/* hardware id for this device */
} dev_trans_req_t ;

/*
 * The following symbolic constants are the valid values for the dt_opcode
 * field of the dev_trans_req data structure.
 */

#define DT_GET_INFO		1	/* get information on the device */

/*
 * The dev_ioctl_req structure is used within the kernel when calling the
 * ioctl routine of a driver with the DEVROOT operation code so that the
 * driver can supply us with some information on the device.
 */

typedef struct dev_ioctl_req {
	/* caller initializes these fields */
	struct console_device *consdevice;
	char	*dsf_name;		/* device special file base name of
					   this device - caller allocates the
					   array of characters - at least
					   BOOTDEVLEN (80) characters long -
					   driver initializes the string */
	/* driver initializes/returns the remaining fields */
	long	hw_id;			/* hardware id for this device */
	dev_t	ldevt;			/* local dev_t for this device */
} dev_ioctl_req_t;

#define DEV_CONSPROTO_LEN	40	/* length of console protocol name */
#define DEV_CONSUNIT_LEN	16	/* length of console "unit" name   */

typedef struct dev_console {
    struct device	*device;
    char                protocol[DEV_CONSPROTO_LEN];    /* protocol name */
    char                unitnm[DEV_CONSUNIT_LEN];       /* "unit" name */
    u_int               remoteid;           /* RemoteId specifier        */
    u_int               unit;               /* Unit specifier            */
    caddr_t		srm_suffix;	    /* Suffix to append to SRM string */
} dev_console_t;

/* If num_paths == 0 on input to the ioctl, then the driver will return
 * the number of paths it has to the device without passing back any
 * path information.
 * If num_paths != 0 then the driver will fill in the structures
 * based on the number of paths requested.
 * If num_paths > [number of paths available] then return only as many
 * as are available.
 */
typedef struct dev_console_allp {
    u_int		num_paths;	/* number of paths to this device */
    dev_console_t	(*devcon)[];	/* ptr to an array of dev_console_t */
} dev_console_allp_t;

typedef struct {
    struct controller   *ctlr;
    char                protocol[DEV_CONSPROTO_LEN];    /* protocol name */
    char                unitnm[DEV_CONSUNIT_LEN];       /* "unit" name */
    u_int               remoteid;           /* RemoteId specifier        */
    u_int               unit;               /* Unit specifier            */
} ctlr_console_t;

struct protocol_struct 
{
    char protocol_name[16];		/* Name of protocol (ie. SCSI) */
    char dsf_name[8];			/* Device special file name to pass
					   to caller if we don't get one
					   from the ioctl call */
    uint major;				/* Major number for this device */
    int  flags;				/* Flags */
    struct protocol_struct *next_protocol; /* Next protocol struture that is supported */
    
};

/* Define flags for protocol_struct flags field */

#define	PP_NOIOCTL	0x00000001	/* Device does not have an ioctl routine */
#define	PP_NETBOOT	0x00000002	/* Device used for network booting */

/*
 * Structure argument for xxdump routines.
 */
struct dump_request {
	vm_offset_t	vaddr;		/* Address of data */
	struct	device	*device;	/* Where we get all our device info */
	daddr_t		part_offset;	/* Offset (blocks) into unit of partition start */
	daddr_t		part_size;	/* Size (blocks) of partition */
	dev_t		dev;		/* Current dump device */
	/*
	 * WARNING: Any device placed here must be able to be checked
	 * and opened (with interviening closes) multiple times with
	 * consistant results.  E.g.; if the volume manager functions
	 * substitute into the device field, subsequently opening
	 * either the original dev_t or the substitute must behave the
	 * same way.  On the other hand, such substitutions as can be
	 * made should be made, to aid in detection of multiple
	 * instances of the same partition in the dump list.
	 */
	u_int		count;		/* Number of blocks to write */
	u_int		blk_offset;	/* Offset into the partition at which to write */
	u_int		limit;		/* Max offset for this piece */
	u_int		remoteid;	/* RemoteId specifier for this device */
	u_int		unit;		/* Unit specifier for this device */
	u_short		command;	/* Control and state information */
	u_char		cur_piece;	/* Index in dumpinfo.piece of current partition */
	u_char		pri_piece;	/* Index in dumpinfo.piece of primary swap partition, or -1 */
	char		device_name[80];/* String to pass to prom open */
	char		protocol[40];	/* What type of protocol, SCSI, MSCP, MOP ect */
	caddr_t		srm_suffix;	/* Suffix to append to SRM string */
};
/* dump_request.command values */
#define DUMPREQ_BAD	0x0		/* Raise the alarm if dump_request used without further setup */
#define DUMPREQ_CHECK	0x1		/* Confirm that device is appropriate, alive, etc. */
#define DUMPREQ_OPEN	0x2		/* Device should be opened if device requires such */
#define DUMPREQ_WRITE	0x3		/* Device must have already been opened (in case appropriate) */
#define DUMPREQ_CLOSE	0x4		/* Close the device (if meaningful) */

extern u_int promio_dump(struct dump_request *);   /* Called from several drivers */

/*
 * These are request for info calls through the cpusw function get_info.
 * This allows kernel code that needs system specfic code to request the 
 * info in a generic way without refering to cpu type.
 * CAUTION: documented device driver and kernel API; see comments below.
 */
	
struct item_list {
	u_long		function;		/* Function code for this item; see below for supported codes */
	u_int		out_flags;    		/* Flags for output data */
	u_int		in_flags;		/* Flags for input data */
	u_long		rtn_status;		/* Status for the function code */
	struct item_list *next_function;	/* Pointer to next function request */
	u_long		input_data;		/* Pointer to input data */
	u_long		output_data;		/* Pointer to output data */
};	

/*
 * Type of info that can be requested 
 *
 * CAUTION: documented device driver and kernel API; see comments below.
 */
#define NOT_SUPPORTED   	0x0000		/* This request type is not supported or getinfo call is not */
#define INFO_RETURNED   	0x0001		/* This request type is supported and returned data */
#define IN_LINE			0x0001		/* The data is contained in the item list structure */

/* CAUTION:
 *	get_info is a documented device driver and kernel layered product API.
 *	See comments after the last fucntion code.
 */
#define	TEGC_SWITCH		0x0001	/* return the address of the sw table for the TEGC driver */
#define	FBUS_INTREQ_REG		0x0002	/* return the address of the int request register for the machine */
#define MOP_SYSID		0x0003	/* MOP SYSID for a system */
#define GET_TC_SPEED		0x0004	/* Get the system Turbo-Channel speed */
#define CONSOLE_2_DEV		0X0005	/* Translate console boot device string into controller ect for us */
#define DEV_2_CONSOLE		0x0006	/* Compose dump string for console from our io data structures */
#define DEV_2_USER		0x0007	/* Return a the string a user would enter at the console to boot */
#define GET_810_SPEED		0x0008	/* Return 810 SCLK speed for known 810s */
#define GET_SLU_SPEED		0x0009	/* return clock speed for SLU devices */
#define GET_FLAGS		0x000a	/* Return system specific flags		*/
#define GET_UNIQUE_SYSID	0x000b	/* Return unique sysid			*/
#define CONSOLE_2_CTLR		0x000c	/* return controller struct for console device */
#define SECONDARY_CACHE_SIZE	0x000d	/* return secondary cache size */
#define	PWRMGR_CAPABLE		0x000e	/* return Power Management capable */
#define	BYTEWORD_IO_CAPABLE	0x000f	/* platform supports byte/word IO and it's enabled */
#define MP_EV_NEEDED		0x0010	/* platform needs save_env executed on all processors */
#define GET_SYS_TEMP		0x0011	/* return system operating temperature */
#define GET_FAN_STATUS		0x0012	/* return system fan status */
#define GET_PS_STATUS		0x0013	/* return power supply status */
#define HIGH_TEMP_THRESHOLD	0x0014	/* return upper operating system temperature threshold */
#define VERIFY_CONSOLE_EV	0x0015	/* does this platform explicitly support the console EV you are  trying to access? */
#define OS_POWERDOWN            0x0016	/* perform an o.s. powerdown */
#define	GET_SG_FLUSHPTR		0x0017	/* SG TLB flush function */
#define GET_SGMAP_CTL		0x0018	/* get scatter gather map control struct */
#define GET_HW_BUGS		0x0019	/* return bitmask of hardware bugs */
#define GET_FIRMWARE_REV	0x001a	/* return firmware revision information */
#define GET_PALCODE_REV		0x001b	/* return palcode revision information */
#define CHECK_MOTHERBOARD_SLOT	0x001c	/* on-board legacy ide? */
#define CTLR_2_CONSOLE		0x001d	/* compose dump string for console from out io data structures */
#define PLATFORM_IO_BIT		0x001e	/* return physical address bit used to denote I/O space by a platform */

#define SW_INTERLEAVE_REQUIRED  0x0020	/* platform requires software interleaving */
#define GET_MEM_BANK_COUNT      0x0021	/* return number of memory banks */
#define GET_MEM_BANK_SIZE       0x0022	/* return size (# MB) of a particular memory bank */
#define GET_MEM_BANK_BASE_PA    0x0023	/* return base phys addr of memory bank */

#define GET_BAD_PAGE_LIST	0x0024	/* return list of bad pages,  */
					/* (memory double bit ECC)    */
#define GET_PLATFORM_RESET_PTR	0x0025	/* return pointer to platform */
					/* hardware reset function.   */
#define GET_HALT_AFTER_PANIC	0x0026	/* return hardware platform's */
					/* halt_after_panic flag.     */
#define CHECK_IDE_LIMITS	0x0027	/* check if platform requires */
					/*  IDE speed throttling      */ 
#define ACE_PIC_INT_MODE	0x0028	/* Edge vs Level interrupt    */
					/* for ace pic.               */
#define SAVEENV_FIXUP_REQUIRED  0x0029  /* Calls to the console's saveenv */
                                        /* routine cause hardclock tick loss */
#define CHECK_IDE_CONTROLLER    0x002a  /* specifies IDE controller type */
#define GET_PS_PRESENT		0x002b	/* return power supply present mask */
#define GET_PS_DEFUNCT		0x002c	/* return power supply failed mask */

/************************************************************************/
/* CAUTION: get_info is a documented device driver and kernel API.	*/
/*	Function codes must remain constant across OS releases.		*/
/*	Deleted codes must be marked RESERVED and not re-used.		*/
/*	V4.# stream - use codes 0x000 - 0x0ff.				*/
/*	V5.# stream - use codes 0x100 - 0x???.				*/
/************************************************************************/
#define	GET_NUMA_INFO		0x0100	/* get numa mem. info */
#define PEER_TO_PEER		0x0101	/* is system peer-to-peer capable? */
#define IS_32BIT_CONSOLE	0x0102	/* need 32bit kernel VM? */
#define	TROLLABLE_SYSTEM	0x0103	/* platform supports memory troller */
#define	GET_INTR_TARGET_CPU	0x0104	/* return RAD's interrupt target CPU */
#define GET_SYS_AGP_CAPS        0x0105  /* return the system's agp capabilities */
#define HAL_GET_MEMDSC_INFO	0x0106  /* return a data structure describing 
					   a RAD's memory */
#define HAL_GET_PCI_SLOT_INFO	0x0107	/* HAL info about a PCI slot */
#define GET_XPC_CAPABILITY      0x0108  /* return the system's xpc capabilities */
#define READ_IPRS		0x0109	/* read processor IPRs */
#define GET_MAX_PCI_SLOTS	0x010a	/* max value of PCI slots on primary bus */
#define HAL_HOTSWAP_CAPABLE	0x010b  /* hotswap capabilities */
#define GET_ERR_LOG_CAPS_HDR	0x010c  /* plat spec header data for err log */
#define HAL_OPEN_USB		0x010d  /* The USB driver is about to take 
					   control of the specified host ctlr*/
#define HAL_CLOSE_USB		0x010e  /* The USB driver is about to release 
					   control of the specified host ctlr*/
#define MCHECK_SUBSYS_CAPABLE   0x010f  /* Does the system support the use
                                           sub-systme mcheck handlers */
#define GET_MSI_SCB_INFO	0x0110  /* plat spec header data for err log */
#define DO_DELAY_AFTER_CMD_REG  0x0111  /* Is a delay needed after writing the 
					   PCI command register during probe */

#ifdef _KERNEL
/*
 * defines for PEER_TO_PEER return data
 */
#define READ_PEER2PEER          0x0001 /* Peer-to-Peer supported for reads */
#define WRITE_PEER2PEER         0x0002 /* Peer-to-Peer supported for writes */
#define LOCAL_PEER2PEER         0x0004 /* Peer-to-Peer within hose heirarchy */
#define GLOBAL_PEER2PEER        0x0008 /* Peer-to-Peer globally across system*/
     
/*
 * defines for CHECK_MOTHERBOARD_SLOT return data.
 */
#define CONFIG_PRIMARY_PCI_IDE		2
#define CONFIG_MB_PCI_IDE		1
#define DONT_CONFIG_MB_PCI_IDE		0

/*
 * defines for CHECK_IDE_LIMITS return data
 *
 *      NOTE: These values are chosen to match
 *      the encoding used in sim_ata.h. If new
 *      IDE DMA rate values are added to the sim_ata
 *      driver, then they should also be reflected
 *      in this header file as well.
 */
#define IDE_PIO_0                       0x08
#define IDE_PIO_1                       0x09
#define IDE_PIO_2                       0x0a
#define IDE_PIO_3                       0x0b
#define IDE_PIO_4                       0x0c

#define IDE_SDMA_0                      0x10
#define IDE_SDMA_1                      0x11
#define IDE_SDMA_2                      0x12

#define IDE_MDMA_0                      0x20
#define IDE_MDMA_1                      0x21
#define IDE_MDMA_2                      0x22

#define IDE_UDMA_0                      0x40
#define IDE_UDMA_1                      0x41
#define IDE_UDMA_2                      0x42

/*
 * Macro to verify an input parameter that is
 * supposed to specify a valid IDE DMA rate.
 */
#define CHECK_IDE_DMA_RATE( rate )      \
   ( ((rate >= IDE_PIO_0)  && (rate <= IDE_PIO_4))  || \
     ((rate >= IDE_SDMA_0) && (rate <= IDE_SDMA_2)) || \
     ((rate >= IDE_MDMA_0) && (rate <= IDE_MDMA_2)) || \
     ((rate >= IDE_UDMA_0) && (rate <= IDE_UDMA_2)) )


/*
 * constants defined for BUGS reported by GET_HW_BUGS
 * start at bit 0 (1)  and then is a mask up to bit 63 (0x8000000000000000)
 */
#define HWBUG_NEED_EDGE 		1
#define HWBUG_NO_IO_BYTE_ADDRESSIBILITY (1L<<1)
#define HWBUG_NO_PCI_RD_MLT		(1L<<2)

/*
 * Structure used to return MEM_ADDR_ALIGN information
 * HW node is Wildfire QBB (Quad Building Block) or Marvel
 * SOC (System On a Chip).
 */
typedef struct get_numa_info {
	int	ni_align;		/* memory alignment shift factor      */
	int	ni_nodes;		/* maximum number of nodes (RADs)     */
	int	ni_nodes_per_rad;	/* CPUs per rad                       */
	int	ni_align_mask;
} numa_info_t;
#endif

/*
 * constants related to GET_810_SPEED function
 * (speeds are specified in terms of MHz * 100)
 */

#define PSIOP_810_SCLK_25MHz		2500
#define PSIOP_810_SCLK_32MHz		3200
#define PSIOP_810_SCLK_33MHz		3300
#define PSIOP_810_SCLK_40MHz		4000

/*
 * The PSIOP_810_BURST_DISABLE bit is passed in conjunction with the PSIOP 
 * clock speed as defined above as part of the GET_810_SPEED platform call
 * on certain platforms.  By default, the bit will be clear on platforms
 * that do not need to disable bursting on the on-board 810 device.
 */

#define PSIOP_810_BURST_DISABLE         0x100000000L

/*
 * constants related to GET_SLU_SPEED function
 */

#define SLU_SCC_PCLK_16Mhz		16*1000*1000	/* speed for scc devices clocked via PCLK at 16 Mhz */


#ifdef _KERNEL
/*
 * These routines provide dynamic extensions to bus functionality.  They
 * are used to configure in loadable drivers and to register interrupt
 * handlers.
 */
struct bus_framework {
	int		(*ctlr_configure)();	/* Ctlr configure routine     */
	int		(*ctlr_unconfigure)();	/* Ctlr unconfigure routine   */
	int		(*adp_unattach)();	/* Bus remove adapter routine */
	int		(*config_resolver)();	/* Autoconfig bus resolver    */
        ihandler_id_t   (*adp_handler_add)();	/* Register interrupt	      */
        int             (*adp_handler_del)();   /* De-register interrupt      */
        int             (*adp_handler_enable)();/* Enable interrupt handler   */
        int             (*adp_handler_disable)();/* Disable interrupt handler */
        int             (*badaddr_access)();    /* Bus specific badaddr routine */
        int             (*controller_configure)();      /* 4.0 driver configuration     */
        int             (*controller_unconfigure)();    /* 4.0 driver unconfigure       */
	int		(*request_resource)();	/* Request I/O resource	      */
	int		(*release_resource)();	/* Release I/O resource       */
        int             (*detect_hw)();         /* Bus reports unconfigured hw*/
        int             (*instance_configure)();/* ctlr instance configuration*/
	caddr_t		rsvd[1];		/* RSVD for future expansion  */
	caddr_t		private[8];		/* Reserved for driver use    */
};
#endif /* _KERNEL */

/*
 * Loadable driver configuration data structure:
 *
 * After the stanza entry has been parsed to produce a bus, controller and
 * device lists, the elements of these lists are packaged up and passed down
 * to the kernel via setsysinfo.  In order to have a single form of setsysinfo
 * command the following structure is used to represent all of the different
 * types.  It consists of the structures themselves with an identifying type
 * and name fields.  The name field is needed so that you could have kernel
 * bus, ctlr, dev lists with these entries for different drivers.
 *
 * The bus, controller and device structures conatin pointers to names.  Such
 * as connecting bus name, connecting controller name, or port name.  In order
 * to make it easy to pass this structure to the kernel via setsysinfo, the
 * name fields will be copied into this structure and then the name pointers
 * within the bus/controller/device structures will be setup in the kernel
 * to point to these strings.
 */
#define MAX_NAME        100     	/* Maximum name length          */
struct config_entry {
	struct  config_entry *e_next;	/* Next entry in linked list    */
	char 	e_name[MAX_NAME];	/* Driver name 			*/
	int	e_type;			/* type = bus, ctlr, dev        */
	union {
		struct bus		e_bus;
		struct controller	e_controller;
		struct device		e_device;
	} e_str;
	char 	e_nm_1[MAX_NAME];	/* Name string			*/
	char 	e_nm_2[MAX_NAME];	/* Name string			*/
	char 	e_nm_3[MAX_NAME];	/* Name string			*/
	char 	e_nm_4[MAX_NAME];	/* Name string			*/
};

/* Bus type definitions	*/

#define	BUS_IBUS	1
#define	BUS_TC		2
#define	BUS_XMI		3
#define	BUS_BI		4
#define	BUS_UNIBUS	5
#define	BUS_QBUS	6
#define	BUS_VME	  	7
#define BUS_MSI		8
#define BUS_CI		9
#define BUS_LSB		10		/* laser system bus */
#define BUS_IOP		11		/* laser I/O adapter */
#define BUS_LAMB	12		/* laser to xmi adapter */
#define BUS_FLAG	13		/* laser to future bus adapter */
#define BUS_LBUS	14		/* cobra local I/O bus */
#define BUS_FBUS	15		/* future bus */
#define BUS_ISA		16		/* ISA bus. */
#define BUS_EISA	17		/* EISA bus. */
#define BUS_SCSI	18		/* SCSI buses */
#define BUS_PCI		19		/* PCI bus. */
#define BUS_PCMCIA	20		/* PCMCIA bus */
#define BUS_MCBUS	21		/* DEC4100 System Mem. bus */
#define BUS_USB		22		/* Universal Serial Bus */
#define BUS_I2O		23		/* I2O Subsystem */

/*
 * CTLR_TYPE is a bit field in the controller and bus structure's "type" field.
 * It is used as a flag in the badaddr routines (TC machines) that determines
 * the type of structure that is requesting the probe. Currently, the ptr passed into
 * the kn1xaa_badaddr routines is typecast to a bus or a controller before use.
 *             0 = Bus structure    1 = Controller Structure
 */
#define CTLR_TYPE       0x80000000      /* Not the bus, its a controller */


/* for the ADU */
#define BUS_TV          99


/* Access type definitions used for EISA and PCI bus */
#define	BUS_MEMORY	0
#define BUS_IO		1
#define DENSE_MEMORY    2

/* Alive field bit definitions */
#define	ALV_FREE	0x00000000	/* Device not yet processed      	*/
#define ALV_ALIVE	0x00000001	/* Device present and configured 	*/
#define	ALV_PRES	0x00000002	/* Device present but no configed 	*/
#define	ALV_NOCNFG	0x00000004	/* Device not to be configured		*/
#define	ALV_WONLY	0x00000008	/* Device is write-only			*/
#define	ALV_RONLY	0x00000010	/* Device is read-only			*/
#define ALV_LOADABLE	0x00000020	/* Device resolved by loadable 		*/
#define ALV_NOSIZER	0x00000040	/* Sizer should ignore this item 	*/
#define ALV_STATIC	0x00000080	/* Generate config_driver line 		*/
#define ALV_PERSIST	0x00000100	/* Tell driver framework we want persistance */


/* Type field bit definitions  */
#define ALV_REMAKE      0x00008000	/* Controller available for allocation 	*/

/* Define various constants used in configuring of loadable drivers */

#define	NEXUS_NUMBER		(-1)
#define	NEXUS_BUS_PTR		((struct bus *)(-1L))

/* These are defined to configure 3.0 Loadable drivers */
#define LDBL_WILDNAME	"*"			/* Char field wildcard */
#define LDBL_WILDNUM		(-99)		/* Int field wildcard */

/* These are defined to configure a 1Binary 4.0 device driver */
#define DRIVER_WILDNAME	LDBL_WILDNAME
#define DRIVER_WILDNUM	LDBL_WILDNUM

/*
 * Module types.
 */
#define BOGUS_TYPE	0x0		/* Invalid type			  */
#define BUS_TYPE	0x1		/* Bus type			  */
#define CONTROLLER_TYPE	0x2		/* Controller type		  */
#define DEVICE_TYPE	0x4		/* Device type			  */

/*----------------------------------------------------*/
/* Defines and function prototypes for bus functions. */
/*----------------------------------------------------*/
#define	RES_MEM		0
#define	RES_IRQ		1
#define	RES_DMA		2
#define	RES_PORT	3

extern	void  do_config (struct controller *ctlr_p);
extern	int   get_config(struct controller *ctlr_p, uint_t config_item,
			 char *func_type, void *data_p, int handle);
extern	void  enable_option (struct controller *ctlr_p);
extern	void  disable_option(struct controller *ctlr_p);
extern io_handle_t busphys_to_iohandle(u_long addr, int flags, struct controller *ctlr_p);


/**********************************************/
/* Function prototypes for io access routines */
/**********************************************/

#define HANDLE_BYTE	0x1
#define HANDLE_WORD	0x2
#define HANDLE_LONGWORD 0x4
#define HANDLE_QUADWORD 0x8
#define HANDLE_TRIBYTE  0x10
#define HANDLE_DENSE_SPACE	0x80000000
#define HANDLE_SPARSE_SPACE	0x40000000
#define HANDLE_BUSPHYS_ADDR     0x20000000  
#define HANDLE_LINEAR_SPACE     0x10000000  

extern int io_copyin(io_handle_t src, vm_offset_t dst, u_long length);
extern int io_copyout(vm_offset_t src, io_handle_t dst, u_long length);
extern int io_copyio(io_handle_t src, io_handle_t dst, u_long length);
extern int io_zero(io_handle_t dst, u_long length);

extern int io_blockread(io_handle_t src, vm_offset_t dst, u_long length, u_long size);
extern int io_blockwrite(vm_offset_t src, io_handle_t dst, u_long length, u_long size);
extern int io_blockexchange(io_handle_t src, io_handle_t dst, u_long length, u_long size);
extern int io_blockclear(io_handle_t dst, u_long length, u_long size);

extern u_long iohandle_to_phys(io_handle_t io_handle, long flags);
extern io_handle_t busphys_to_iohandle(u_long addr, int flags, struct controller *ctlr_p);
extern long read_io_port(io_handle_t dev_addr, int width, int type);
extern void write_io_port(io_handle_t dev_addr, int width, int type, long data);

/**********************************************/
/* Function prototypes for read/write_io_port */
/**********************************************/
/* extern	unsigned long read_io_port(vm_offset_t dev_addr, int width, int type); */
/* extern	void write_io_port(vm_offset_t dev_addr, int width, int type, long data); */

/*----------------------*/
/* Macros for io access */
/*----------------------*/

#define READ_BUSIO_D8(a)   ((unsigned char)(read_io_port(a, 1, BUS_IO)))
#define READ_BUSIO_D16(a)  ((unsigned short)(read_io_port(a, 2, BUS_IO)))
#define READ_BUSIO_D32(a)  ((unsigned int)(read_io_port(a, 4, BUS_IO)))
#define READ_BUSIO_D64(a)  ((unsigned long)(read_io_port(a, 8, BUS_IO)))
#define READ_BUSMEM_D8(a)  ((unsigned char)(read_io_port(a, 1, BUS_MEMORY)))
#define READ_BUSMEM_D16(a) ((unsigned short)(read_io_port(a, 2, BUS_MEMORY)))
#define READ_BUSMEM_D32(a) ((unsigned int)(read_io_port(a, 4, BUS_MEMORY)))
#define READ_BUSMEM_D64(a) ((unsigned long)(read_io_port(a, 8, BUS_MEMORY)))
#define WRITE_BUSIO_D8(a,d)   ((void)(write_io_port(a, 1, BUS_IO, d)))
#define WRITE_BUSIO_D16(a,d)  ((void)(write_io_port(a, 2, BUS_IO, d)))
#define WRITE_BUSIO_D32(a,d)  ((void)(write_io_port(a, 4, BUS_IO, d)))
#define WRITE_BUSIO_D64(a,d)  ((void)(write_io_port(a, 8, BUS_IO, d)))
#define WRITE_BUSMEM_D8(a,d)  ((void)(write_io_port(a, 1, BUS_MEMORY, d)))
#define WRITE_BUSMEM_D16(a,d) ((void)(write_io_port(a, 2, BUS_MEMORY, d)))
#define WRITE_BUSMEM_D32(a,d) ((void)(write_io_port(a, 4, BUS_MEMORY, d)))
#define WRITE_BUSMEM_D64(a,d) ((void)(write_io_port(a, 8, BUS_MEMORY, d)))

/* io_handle_t versions */
#define READ_BUS_D8(a)   ((unsigned char) (read_io_port(a, 1, 0)))
#define READ_BUS_D16(a)  ((unsigned short)(read_io_port(a, 2, 0)))
#define READ_BUS_D32(a)  ((unsigned int)  (read_io_port(a, 4, 0)))
#define READ_BUS_D64(a)  ((unsigned long) (read_io_port(a, 8, 0)))
#define WRITE_BUS_D8(a,d)   ((void)(write_io_port(a, 1, 0, d)))
#define WRITE_BUS_D16(a,d)  ((void)(write_io_port(a, 2, 0, d)))
#define WRITE_BUS_D32(a,d)  ((void)(write_io_port(a, 4, 0, d)))
#define WRITE_BUS_D64(a,d)  ((void)(write_io_port(a, 8, 0, d)))


/* DMA SUPPORT -- structures, typedefs, define's	*/

/* bus-address/byte-count pair structure		*/
/* io bus addr. can be up to 64-bits, and byte-specific */
/* the byte count is signed 64-bits 			*/
struct	sg_entry {
	bus_addr_t	ba;	/* bus address                          */
	u_long		bc;	/* byte count from ma that contiguous
				   addresses are valid on the bus 	*/
};

typedef	struct sg_entry	*sg_entry_t;

/*
 * The sglist structure contains the control structure to access a
 * page of bus_address-byte_count pairs. The pointer to this structure
 * is passed back to drivers from dma_map_alloc() & dma_map_load().
 */
/*
 * If hw-sg resources are attached to a DMA transfer, they are found 
 * through the hw_sg_table_control struct.
 * The private field is used to hold the data used by dma_get/put_private. 
 */

 /*
  *	+----------------------------------+
  *	|               sgp		   |
  *	+----------------+-----------------+
  *	|   num_ents     |     val_ents    |   -> each line 64-bits
  *	+----------------+-----------------+   -> 80 bytes cache block
  *	|      flags     |      index      |   -> critical data in 1st
  *	+----------------+--------+--------+   -> 64 bytes (two 32-byte
  *	|		next		   |   -> cache blocks)
  * .---+----------------------------------+------------.
  * |	|		cntrlrp		   |   		V
  * V	+----------------------------------+    this section only added to
  *	|		va		   |	first sglist of babc list.
  *	+----------------+-----------------+      *** a struct ovrhd{} ***
  *	|       num      |      index      | \
  *	+----------------+-----------------+  > hw_sg_table_control struct
  *	|             table_base           | /
  *	+----------------------------------+
  *	|	     private_data   	   |	
  *	+----------------+-----------------+
  *	|		procp		   |
  *	+----------------------------------+
  *
  * So, a page of sglist's (256 structs) with assoc. pages of sg_entry's 
  * (512 per page, 8KB per pair, min.) will be able to describe 1GB (min.).
  */

struct	sglist	{
	sg_entry_t	sgp;	  /* ptr. to ba-bc pair (struct of)	 */
	int		val_ents; /* number of ba-bc pairs in babc list  */
	int		num_ents; /* loaded/valid ba-bc pairs in list    */
	int		index;	  /* last ba-bc pair read		 */
	int		flags;	  /* copy of flags from alloc/load	 */
	struct	sglist	*next;	  /* ptr. to next struct in linked list	 */
};

/*
 * This structure is used to contain information about allocated
 * hardware scatter/gather recources. The address of the table, the
 * index and the number of entries allocated live here. It is placed
 * in the ovrhd struct of a super-sglist structure. (See diagram above).
 */
struct hw_sg_table_control {
	u_int		index;		/* Index of allocated space in hw_sg table */
	u_int		num;		/* number of entries allocated */
	vm_offset_t	table_base;	/* base address of table */
};

struct ovrhd {
	struct  controller *cntrlrp;	/* requesting controller	*/
	vm_offset_t	    va;		/* saved va on dma_map_load	*/
	struct hw_sg_table_control hw_sg; /* hw sg control struct	*/
	u_long private_data;		/* used by dma_put/get_private  */
	struct	proc	   *procp;	/* proc ptr on dma_map_load	*/
};

/* Typedef for return value defs */
typedef	struct	sglist	*sglist_t;
typedef	struct	sglist	*dma_handle_t;

#ifdef _KERNEL
/*
 * The dma_callsw structure contains pointers to the platform-dependent
 * functions that support drivers for DMA devices. The structure
 * is initialized by the platform-specific init function during bootstrap
 * (e.g., kn121_init() on JENSEN).
 * The generic functions are defined in locore.s and uses this jump
 * table (for now) to get to the platform-specific interfaces for these
 * functions.
 */

struct	dma_callsw	{
	u_long	(*hal_dma_map_alloc)();	  /* ptr to HAL's dma_map_alloc    */
	u_long	(*hal_dma_map_load)();	  /* ptr to HAL's dma_map_load     */
	int	(*hal_dma_map_unload)();  /* ptr to HAL's dma_map_unload   */
	int	(*hal_dma_map_dealloc)(); /* ptr to HAL's dma_map_dealloc  */
	int	(*hal_dma_min_bound)();   /* ptr to HAL's dma_min_boundary */
};
/*
 * dma_callsw defined in driver_support.c;
 * need this declaration for cpu-specific init modules-functions 
 */
extern	struct	dma_callsw	dma_callsw;

/*
 * The bus_bridge_dma_callsw structure contains pointers to the
 * bus bridge dma hardware mapping functionality used to do bus
 * mapping.
 */
struct  bus_bridge_dma_callsw      {
   unsigned long    (*dma_alloc)();
   unsigned long    (*dma_load)();
   int              (*dma_unload)();
   int              (*dma_dealloc)();
};

#endif	/* _KERNEL */

/*
 * values for "flags" field in function calls, structures 
 */
#define	DMA_SLEEP	0x0001	/* SLEEP on dma_alloc/load call 	 */
#define DMA_RSVD_0002	0x0002	/* Reserved place holder		 */
#define DMA_RSVD_0004	0x0004  /* Reserved place holder		 */
#define DMA_HW_SG	0x0008  /* Hardware/Scatter gather alloacted	 */
#define DMA_GUARD_UPPER 0x0010  /* Add GUARD page at end of sg list	 */
#define DMA_GUARD_LOWER 0x0020  /* Add GUARD page at beg. of sg list	 */
#define DMA_ALL		0x0040  /* Get all resources req. or rtn failure */
#define DMA_RSVD_0080  	0x0080  /* Reserved place holder		 */
#define DMA_IN		0x0100	/* device to main/system/core data xfer	 */
#define DMA_OUT		0x0200	/* main/system/core mem. to device xfer  */
#define DMA_ADDR_LIMIT  0x0400  /* Address limited dma flag		 */
#define DMA_RSVD_0800   0x0800  /* Reserved place holder		 */
#define DMA_DEALLOC	0x1000	/* dealloc. resources on unload		 */
#define DMA_CONTIG      0x2000  /* Return only contiguous		 */
#define DMA_RSVD_4000   0x4000  /* Reserved place holder		 */
#define DMA_RSVD_PLTFRM 0x4000	/* i.d. that previous flag is used by
				   platform-specific dma code		 */
#define DMA_DIRECT_MAP	0x8000  /* bus bridge flag "sglist chain"        */
#define DMA_64BIT       0x10000 /* 64bit capable                         */

/*
 * Prototype defs for drivers
 */
/* the following are implemented in locore.s (for performance reasons) */
extern	u_long	dma_map_alloc(u_long bc, struct controller *cntrlrp, 
				dma_handle_t *dma_handle_p, int flags);
extern	u_long	dma_map_load(u_long bc, vm_offset_t va, struct proc *procp, 
	struct controller *cntrlrp, dma_handle_t *dma_handle_p, 
			              u_long max_bc, int flags);
extern	int	dma_map_unload(int flags, dma_handle_t dma_handle);
extern	int	dma_map_dealloc(dma_handle_t dma_handle);
extern	int	dma_min_boundary(struct controller *cntrlrp);
/* the following are in driver_support.c */
extern	sg_entry_t	dma_get_next_sgentry(dma_handle_t dma_handle);
extern	sg_entry_t	dma_get_curr_sgentry(dma_handle_t dma_handle);
extern	int		dma_put_prev_sgentry(dma_handle_t dma_handle, sg_entry_t sg_entryp);
extern	int		dma_put_curr_sgentry(dma_handle_t dma_handle, sg_entry_t sg_entryp);
extern	vm_offset_t	dma_kmap_buffer(dma_handle_t dma_handle, u_long offset);
extern	int		dma_get_private(dma_handle_t dma_handle, int index, 
						u_long *data);
extern	int		dma_put_private(dma_handle_t dma_handle, int index,
						u_long data);
extern	dma_map_info_t  dma_get_maps(struct bus *busp);
extern	int		dma_get_sgentry_reset(dma_handle_t dma_handle);
extern	int		dma_get_num_val_sgentrys(dma_handle_t dma_handle);
extern	void		drvr_shutdown(void);
extern	void		drvr_register_shutdown(void (*callback)(), 
					       caddr_t param, 
					       int flags);

extern	void		drvr_saveterm(void);
extern	void		drvr_register_saveterm(void (*callback)(), 
					       caddr_t param, 
					       int flags);
extern	void		drvr_flush(void);
extern	void		drvr_register_flush(void (*callback)(), caddr_t param, 
					       int flags);
extern struct device * get_device_next( struct device *);
extern struct controller * get_controller_next( struct controller *);
extern struct bus * get_bus_next( struct bus *);
extern struct bus * find_bus_config_entry (struct bus *bus,
					   char * driver_name,
					   int slot );
extern struct controller * find_ctlr_config_entry (struct bus *bus,
						   char * driver_name,
						   int slot );


/*
 * DMA Map support macros
 */
#define	DMA_MAP_BUF(A,B,C,D,E,F,G)	((u_long)dma_map_load(A, B, C, D, E, F, G))
#define	DMA_UNMAP_BUF(A)		((int)dma_map_dealloc(A))

#ifdef _KERNEL
/************************************************************************/
/*									*/
/* Generic I/O Resource Management -- structures, typedefs, define's 	*/
/*  									*/
/************************************************************************/

/* 
 * Request/Release  I/O or memory space parameter structure
 */

struct io_mem_req_t {
    io_handle_t		baseaddr;	/* I/O port base address or memory */
					/* space base address		   */
					 
    u_long		numbytes;	/* Number of contiguous bytes	   */ 
					/* requested for I/O or Mem space  */
					 
    u_long		alignment;	/* alignment requirement flag      */

    caddr_t		bus_param;	/* Bus-specific parameter if necessary 	*/

    void		*reserved;	/* Reserved for future expansion	*/
}; 

/* 
 * Request/Release interrupt parameter structure
 */

struct intr_req_t {
    long	       	intr_num;	/* assigned INTR number being returned 	*/

    u_long		req_intr;	/* requested INTR or INTR bit mask 	*/
                                        /* indicating multiple choice INTR 	*/
                                        /* selection				*/
    u_long		intr_flags;	/* Bit flags field to indicate 		*/
                                        /* interrupt request options		*/
    caddr_t		bus_param;	/* Bus-specific parameter if necessary  */
};

/* 
 * Handle type for opaque use with machine dependent I/O resource
 * management routines -- this field is returned by the resource
 * management routine to the client and used as input to the resource
 * release routine to release a particular resource instance.
 */
typedef char * res_handle_t;

/* 
 * This structure is used as an argument/parameter block to be passed to
 * the resource management function interface.  Depending on the resource 
 * type being requested, different fields are utilized.  The beginning 
 * part of the structure is used for common fields for all types.
 */
struct resource_blk {

    /* common fields for all resource types */

    u_long	resource_type;		/* Type of resource requested		*/
    caddr_t	bus_ctlr_p;	    	/* Pointer to bus/controller struct    	*/
    u_int 	caller_type;	    	/* Caller type, BUS or CTLR            	*/
    u_int	flags;		    	/* bit flags field to indicate options 	*/
    struct bus  *busptr;		/* Bus ptr to use in dispatching calls  */

    caddr_t	req_param;		/* Generic pointer to a resource-type	*/
                                        /* specific request structure		*/

    res_handle_t resource_handle;	/* handle ID returned by resource mgmt	*/
                                        /* routine(s)				*/
    void	*reserved[8];	    	/* Reserved for future expansion 	*/
       
};

/* Defines for caller type */
#define RES_BUS_TYPE			0x01
#define RES_CONTROLLER_TYPE		0x02

/* 
 * Defines for "flags" field -- flags field is used to indicate
 * various options for the function call
 */
#define RES_SHARABLE	0x00000001	/* This resource may be shared 		*/

/* 
 * This is a special flag indicating that the resource being requested
 * is a permanent/static one which is never deallocated.
 * This flag is used for I/O resources for static devices that are
 * probed during the boot.
 */
#define RES_PERMANENT	0x80000000	
#define RES_CARDBUS_REQUEST 0x40000000

/*
 * Defines for interrupt request flags field
 */
#define RES_INTR_MASK	0x00000001	/* INTR requested is specified as bit mask */

/*
 * Defines for alignment field 
 */
#define RES_NO_ALIGN		0x0000		/* No alignment requirement */
#define RES_ALIGN_BYTE		0x0001		/* Byte alignment */
#define RES_ALIGN_WORD		0x0002		/* Word alignment */
#define RES_ALIGN_LONGWORD	0x0004		/* Longword alignment */
#define RES_ALIGN_QUADWORD	0x0008		/* Quadword alignment */
#define RES_ALIGN_OCTAWORD	0x0010		/* Octaword alignment */
#define RES_ALIGN_4K		0x1000		/* 4K alignment */
#define RES_ALIGN_8K		0x2000		/* 8K alignment */
#define RES_ALIGN_16K		0x4000		/* 16K alignment */
#define RES_ALIGN_32K		0x8000		/* 32K alignment */
#define RES_ALIGN_64K		0x10000		/* 64K alignment */
#define RES_ALIGN_PAGE		0xffffffff 	/* Alpha-page alignment */


/*
 * Defines for IRQ request bit mask
 */
#define RES_IRQ0		0x0001	
#define RES_IRQ1		0x0002
#define RES_IRQ2		0x0004
#define RES_IRQ3		0x0008
#define RES_IRQ4		0x0010
#define RES_IRQ5		0x0020
#define RES_IRQ6		0x0040
#define RES_IRQ7		0x0080
#define RES_IRQ8		0x0100
#define RES_IRQ9		0x0200
#define RES_IRQ10		0x0400
#define RES_IRQ11		0x0800
#define RES_IRQ12		0x1000
#define RES_IRQ13		0x2000
#define RES_IRQ14		0x4000
#define RES_IRQ15		0x8000

/*
 * Defines for resource types -- use the same defines as the ones
 * defined for bus functions above
 *
 * #define	RES_MEM		0      	 Memory space block 
 * #define	RES_IRQ		1	 Interrupt number 
 * #define	RES_DMA		2	 DMA resource  -- TBD 
 * #define	RES_PORT	3	 I/O space block 
 */

/*
 * Defines for return code
 */
#define RES_SUCCESS		0x00	/* Successful operation */
#define RES_FAILURE		0x01   	/* Failed operation */
#define RES_INV_PARAM		0x02   	/* Invalid parameter passed */
#define RES_IN_USE		0x03   	/* Requested resource already in use */
#define RES_EXHAUSTED		0x04   	/* Out of resource for the specified type */
#define RES_NO_SHARE		0x05   	/* This resource cannot be shared */
#define RES_NOT_SUPPORTED 	0x06	/* This request/feature is not supported */


/*
 * Resource handle ID structure
 *
 * (Note: We may want to put this struct in a separate .h file ????)
 *
 * This structure is allocated when a new I/O resource is reserved via
 * request_resource() call.  The purpose of this structure is to contain
 * all the information needed to dispatch off to the bus specific implementation
 * of release_resource().  The bus pointer is needed to get to the
 * correct routine pointed to by the bus framework.  
 */

struct resource_key {
    struct resource_key	*next;		/* Pointer to next entry */
    struct resource_key *prev;		/* Pointer to prev entry */
    struct bus		*bus;		/* Pointer to bus structure */
    res_handle_t	bus_res_id;	/* Bus specific resource handle */
    lock_data_t		lock;		/* MP lock */
};


/*
 * Function prototypes
 */

extern int request_resource(struct resource_blk *info_ptr);
extern int release_resource(res_handle_t resource_handle);




/*
 * I/O resource linked lists to keep track of used and unused resources
 * in the system at any given time.
 *
 * Each system should declare one global lock for each type of system
 * resources.  Within a linked list of resource elements, there is one
 * lock for each element.
 *
 * Each system should also declare one used list head for each I/O resource type.
 */

struct res_handle_list {
        struct res_handle_list	*next;		/* Pointer to the next resource handle if */
	                                        /* this is a shared resource		  */
	                                        /* NULL if not a shared resource, or if	  */
	                                        /* this is the last shared entry	  */
	caddr_t		resource_ptr;		/* Pointer to this resource's entry in the*/
	                                        /* linked list of resources		  */

	u_long		resource_type;		/* Indicates which resource list to look  */
};

struct io_mem_list {
        struct io_mem_list	*next;		/* Pointer to next I/O or memory element  */
        struct io_mem_list	*prev;		/* Pointer to prev.I/O or memory element */
	io_handle_t		baseaddr;	/* starting address of I/O or memory blk */
	u_long			numbytes;	/* Number of contiguous bytes in this blk */
	u_int			is_shared;	/* 1 if this resource is shared */
	int			count;		/* Number of currently sharing clients, */
	                                        /* defaults to 1			   */
	struct res_handle_list	*res_handle;	/* client handle ID linked list for this resource */ 
        lock_data_t		lock;		/* MP lock 			   */
};

struct intr_list {
       struct intr_list		*next;		/* Pointer to next INTR element 	*/
       struct intr_list		*prev;		/* Pointer to prev. INTR element */
       int			intr;		/* INTR number 			*/
       u_int			is_shared;	/* 1 if this INTR is shared	*/
       int			count;		/* Number of currently sharing clients, */
                                                /* defaults to 1		   */

       int			reserved;	/* place holder for alignment 	*/
       struct res_handle_list	*res_handle;	/* client handle ID linked list for this resource */ 
       lock_data_t		lock;		/* MP lock			*/
};

/*
 * Defines for the "is_shared" field 
 */
/* defined earlier in this file */
/* #define RES_SHARABLE	0x1	*/
/* #define RES_PERMANENT 0x80000000 */

#define RES_IS_SHARED	0x2	/* This resource is shared currently */

/*
 * generic lock MACROs for I/O resource locks
 */
#define LOCK_RSRC(lock)		   lock_write(&lock)
#define UNLOCK_RSRC(lock) 	   lock_done(&lock)

#define LOCK_RSRC_ENTRY(entry)     lock_write(&(entry->lock))
#define UNLOCK_RSRC_ENTRY(entry)   lock_done(&(entry->lock))

#define INIT_RSRC_ENTRY(entry, lockinfo) lock_setup(&(entry->lock),\
					            lockinfo, TRUE)
/*
 * Define the data structures that the platform code fills in which
 * allows the common init code to properly reserve the required space
 * and IRQs for platform.
 */

struct mapout_address
    {
	long start;
	long size;
    };

struct mapout_info
    {
	u_long intr_mask;
	struct mapout_address *mapout_io;
	struct mapout_address *mapout_mem;
    };

/*
 * Define the constants the the platform code uses to tell the common
 * code which bus type the request is being nade for
 */
#define RESOURCE_ISA 0
#define RESOURCE_PCI 1

#endif	/* KERNEL */ 


/* Defines for server management's environmental monitor return status 
** from the platform's get_info() interface
*/
#define ENV_STATUS_OK   0
#define ENV_STATUS_FAIL 1
#define ENV_TEMP_STATUS_OK   -1
#define ENV_TEMP_STATUS_FAIL -2


/* Structure for driver shutdown/flush routine callback */
struct drvr_shut {
	struct drvr_shut	*next;
	void			(*callback)();	/* callback routine */
	caddr_t			param;
};
	
#define	DRVR_REGISTER	0x00000001	/* register a callback routine */
#define	DRVR_UNREGISTER	0x00000002	/* de-register a callback routine */

/*
 * New bus, device, and controller revisions introduced in V5.0 (i.e. V1) 
 * Backward compatibility to the V0 structures must be maintined
 * by any kernel code that manipulates bus_config, controller_config,
 * and device_config structures.
 */

#define BUS_CONFIG_REV_V0	0L
#define BUS_CONFIG_REV_V1	1L
#define BUS_CONFIG_REV_V2	2L
#define CTLR_CONFIG_REV_V0	0L
#define CTLR_CONFIG_REV_V1	1L
#define CTLR_CONFIG_REV_V2	2L
#define DEVICE_CONFIG_REV_V0	0L
#define DEVICE_CONFIG_REV_V1	1L

/*
 * Conditionalize the definitions of BUS_CONFIG_REVISION and
 * CTLR_CONFIG_REVISION upon whether this is an internal kernel
 * build (ode environment) or an external build.
 */
#ifdef _BASE_KERNEL_PRIVATE
#define BUS_CONFIG_REVISION BUS_CONFIG_REV_V2
#define CTLR_CONFIG_REVISION CTLR_CONFIG_REV_V2
#else
#define BUS_CONFIG_REVISION BUS_CONFIG_REV_V1
#define CTLR_CONFIG_REVISION CTLR_CONFIG_REV_V1
#endif
#define DEVICE_CONFIG_REVISION DEVICE_CONFIG_REV_V1

#define NAME_SIZE_REG 30

/*
 * bus_config structure's field definitions
 *
 * Revision		- is the version of the bus_config structure. The
 *			  #define a device driver developer would use here
 *			  are defined in devdriver.h by digital.
 *
 * subsystem_name	- is the configuration name of the driver. This is
 *			  the name that is used to configure identify and
 *			  name the .mod.
 *
 * bus_name		- is the name of the bus this driver can be
 *			  configured into. This will be wild carded in the
 *			  initial design. Since subsystem names of device
 *			  drivers are unique across  busses, bus
 *			  autoconfiguration by definition will not configure
 *			  this bus unless one is found.
 *
 * confl1()		- Pointer to adapter's confl1 configuration interface
 *
 * confl2()		- Pointer to adapter's confl2 configuration interface
 *
 * unconfl1()		- Pointer to adapter's unconfl1 unconfiguration
 *			  interface
 *
 * flags		- Used to pass structure configure informaion to
 *			  create_bus_struct 
 */
struct bus_config {
       long    revision;
       char    subsystem_name[NAME_SIZE_REG];
       char    bus_name[NAME_SIZE_REG];
       int     (*confl1)();
       int     (*confl2)();
       int     (*unconfl1)();
       ulong   flags;
       long    bus_num;         /* preferred bus num  */
       long    slot_num;        /* preferred slot num */
       long    parent_instance; /* parent's instance  */
};


/*
 * device_config structure's field definitions
 *
 * Revision		- is the version of the device_config structure.
 *			  The #define a device driver developer would use
 *			  here are defined in devdriver.h by digital.
 *
 * device_type		- is the configuration type of the device
 *
 * device_name		- is the configuration name of the device
 *
 * controller_name	- is the name of the controller this device is 
 *			  connected to
 *
 * phys_unit_num	- is the devices physical unit
 *
 * logical_unit_num	- is the devices logical unit
 *
 * controller_num	- is the number of the controller this device is
 *			  connected to
 *
 * flags		- Used to pass structure configure information to
 *			  create_device_struct 
 */
struct device_config {
       long    revision;
       char    device_type[NAME_SIZE_REG];
       char    device_name[NAME_SIZE_REG];
       char    controller_name[NAME_SIZE_REG];
       int     phys_unit_num;
       int     logical_unit_number;
       int     controller_num;
       ulong   flags;
};


/*
 * Controller_config structure's field definitions
 *
 * Revision		- is the version of the controller_config structure.
 *			  The #define a device driver developer would use
 *			  here are defined in devdriver.h by digital.
 *
 * subsystem_name	- is the cfgmgr configuration name of the driver.
 *			  This is the name that is used to configure identify
 *			  and name the .mod. This name should match the
 *			  driver name in the option data entry for a
 *			  device driver.
 *
 * bus_name		- is the name of the bus this driver can be
 *			  configured into. This will be wild carded in the
 *			  initial design. Since subsystem names of device
 *			  drivers are unique across  busses, bus
 *			  autoconfiguration by definition will not configure
 *			  this device into a bus unless one is found.
 *
 * devdriver		- is a pointer to the driver's devdriver structure.
 *
 * flags		- Used to pass structure configure information to
 *			  create_controller_struct 
 */
struct controller_config {
       long    revision;
       char    subsystem_name[NAME_SIZE_REG];
       char    bus_name[NAME_SIZE_REG];
       struct  driver * devdriver;
       ulong   flags;
       long    ctlr_num;                /* preferred ctlr number */
       long    slot_num;                /* preferred slot number */
       long    parent_instance;         /* parent's instance     */
};

/*
 * Flag definition for the bus_config, controller_config,
 * and device config structs
 *
 * CONFIG_PERSIST	- The bus/controller should persist
 *			  in the hwconfig persistance database.
 *
 * CONFIG_PREF_BUSNO    - attempt to specify the bus number when
 *                        calling create_bus_struct()
 *
 * CONFIG_PREF_CTLRNO   - attempt to specify the ctlr number when
 *                        calling create_controller_struct()
 *
 * CONFIG_PREF_SLOTNO   - attempt to specify the bus number when
 *                        calling create_{bus|controller}_struct()
 */

#define CONFIG_PERSIST          0x01UL 
#define CONFIG_PREF_BUSNO       0x10UL
#define CONFIG_PREF_CTLRNO      0x10UL
#define CONFIG_PREF_SLOTNO      0x20UL
#define CONFIG_PREF_PBUS_INST   0x40UL /* specifying parent's instance */



#ifdef _KERNEL
/*
 * Output structure for HAL_GET_PCI_SLOT_INFO
 */

typedef struct _hal_slot_info {
    int		version;
    int		flags;

    ulong	hal_flags; 
#define HAL_SLOT_POWERABLE	0x00000001 /* HW may be powered independently */
#define HAL_SLOT_PRESENT	0x00000002 /* HW is present in the slot       */
#define HAL_SLOT_POWER_OFF	0x00000004 /* HW is powered off               */
#define HAL_SLOT_HOTSWAPABLE	0x00000008 /* HW may be hotswapped            */
#define HAL_SLOT_UNAVAILABLE	0x00000010 /* HW unavailable                  */
#define HAL_SLOT_UNHEALTHY	0x00000020 /* HW failed POST                  */
#define HAL_SLOT_RMV_RQST	0x00000040 /* remove rqst pending             */

    void	*hal_indict_handle; 
    int		hal_indict_handle_len; 
    MSS		*mss_ptr;    
    ulong	hal_handle;

} HAL_SLOT_INFO;

#endif	/* _KERNEL */ 

/*
 * Flags 
 */

/* External routine definitions */

#if defined(_KERNEL)
#if defined(_USE_KERNEL_PROTOS)

extern struct hwconfig *create_hwconfig_struct(void);
extern void		free_hwconfig_struct(struct hwconfig *hwconfigptr);

extern int      create_bus_struct(struct bus_config *bus_cnfg);
extern int      create_controller_struct(struct controller_config *ctlr_cnfg);
extern int      create_device_struct(struct device_config *dev_cnfg);
extern int      remove_bus_struct(struct bus_config *bus_cnfg);
extern int      remove_bus_instance(struct bus *bus_ptr);
extern int      remove_controller_struct(struct controller_config *ctlr_cnfg);
extern int      remove_device_struct(struct device_config *dev_cnfg);
extern int      free_device_struct(struct device *devptr);

extern int      driver_persistence(struct persistence_request *req);

extern int      get_template_bus_num(char *bus_name);
extern int      set_template_bus_num(char *bus_name, int bus_no);

extern struct bus *get_sys_bus(char *name);
extern struct bus *get_bus(char *name, int slot, char *bus_name, int num);
extern struct bus *get_bus_by_name(char *bus_name, int bus_num, char *connb_name, int connb_num);
extern struct bus *get_bus_num(char *bus_name, int bus_num);
extern struct bus *get_bus_physical(char *bus_name,
                                    u_int primary_bus_num,
                                    u_int subordinate_bus_num); 
extern struct bus *bus_search(char *busname, int slot);
extern struct controller *get_ctlr(char *ctlr_name, int slot, char *bus_name, int num);
extern struct controller *ctlr_search(int num, char *name);
extern struct device *get_device(struct controller *ctlr);
extern struct controller *get_ctlr_num(char *ctlr_name, int ctlr_num);
extern void conn_ctlr(struct bus *bus, struct controller *ctlr);
extern void conn_device(struct controller *ctlr, struct device *device);
extern void conn_bus(struct bus *hdbus, struct bus *bus);
extern void register_bus_hw (struct bus *);
/* device_driver.c protos */
extern void dstats_init(struct device *device);
extern void boot_protocol_reg(uint major_num, char *protocol, char *dev_name, int flags);
extern int BADADDR(caddr_t addr, int len, struct bus_ctlr_common *ptr);

#else /* !defined(_USE_KERNEL_PROTOS) */

extern struct bus		*get_sys_bus();
extern struct bus		*get_bus();
extern struct bus		*get_bus_by_name();
extern struct bus		*bus_search();
extern struct controller	*get_ctlr();
extern struct controller	*ctlr_search();
extern struct device		*get_device();
extern void			conn_ctlr();
extern void			conn_device();
extern void			conn_bus();
extern void			register_bus_hw ();
/* in Alpha at least, these are macros */
#ifndef __digital__
extern int			BADADDR();
extern int			DELAY();
#endif /* __digital__ */

#endif /* defined(_USE_KERNEL_PROTOS) */

/* DMA memory allocation support routines */
extern	sg_entry_t	dma_alloc(unsigned int size, int flags);
extern	sglist_t	dma_alloc_super_sglist(int flags);
extern	sglist_t	dma_alloc_sglist(int flags);
extern	sglist_t	dma_struct_alloc(long num_ents, int flags);
extern	void		dma_free(unsigned int size, sg_entry_t addr, int flags);
extern	void		dma_free_super_sglist(sglist_t addr);
extern	void		dma_free_sglist(sglist_t addr);

/* Hardware Scatter/Gather support function prototypes */
extern	void *		hw_sg_map_init(vm_offset_t phys_base, u_long size,
				vm_offset_t table_base, u_long prefetch);
extern	u_long		hw_sg_alloc(u_long bc, struct controller *cntrlrp,
				struct sglist *sglistp, int flags,
				void *mapctl);
extern	int		hw_sg_load(u_long bc, vm_offset_t va,
				struct proc *procp, struct sglist *sglistp,
				unsigned long max_bc, void *mapctl);
extern	int		hw_sg_unload(struct sglist *sglistp);
extern	int		hw_sg_dealloc(struct sglist *sglistp);

/* Disk "default" partition map routine */
#include <io/common/devio.h>
#include <sys/disklabel.h>
extern	int		get_def_partitionmap(register DEVGEOMST *geom,
                               register struct pt_tbl *pmap);
extern  int 		invent_geometry(DEVGEOMST *dg);

#if defined(_USE_KERNEL_PROTOS)
extern u_int get_info(struct item_list *request);
extern u_int promio_dump(struct dump_request *dump_req);
#endif /* defined(_USE_KERNEL_PROTOS) */

#endif /* defined(_KERNEL) */

#ifdef __intel__
#define mb()
#endif /* __intel__ */

#ifdef _KERNEL


/*
 * Function prototypes and data structure types      
 * for push/pop queue utility routines               
 *
 * The idea here is tohide the details of queue management from
 * someone who just wants to put a value on a queue for later
 * retrieval.  Using these routines, no data structure has to be
 * defined, its just a simple way to keep track of a series of 64 bit
 * values.
 */
typedef struct qentry {
    queue_chain_t q;
    unsigned long data;
} QENTRY;

typedef QENTRY *QHEAD;

extern QHEAD ds_queue_create();
extern void  ds_queue_destroy(QHEAD );
extern int   ds_queue_push(QHEAD,unsigned long );
extern int   ds_queue_pop(QHEAD, unsigned long *);
#endif /* _KERNEL */


#ifdef __cplusplus
}
#endif
#endif /* DEVDRIVER_HDR */
