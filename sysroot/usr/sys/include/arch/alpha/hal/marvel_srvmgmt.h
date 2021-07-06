/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: marvel_srvmgmt.h,v $
 * Revision 1.1.6.4  2003/11/14  17:23:17  Aaron_Biver
 * 	Superdome Power Supply (SDI) support: append fields to
 * 	penum_2_name[].
 *
 * Revision 1.1.6.3  2003/06/20  16:33:01  Rajesh_R
 * 	Corrected a typo in penum_2_name data structure.
 *
 * Revision 1.1.6.2  2003/03/12  21:07:45  Rajesh_R
 * 	Added marvel_pe_node struture as a part of reducing the number of console
 * 	callback for updating sensors.
 *
 * Revision 1.1.6.1  2002/11/08  21:17:42  Rajesh_R
 * 	Changed the PE node names to be consistent with the hwmgr convention. Modifed the status variable for airmovers and power supplies from ulong to int.
 *
 * Revision 1.1.2.3  2002/07/17  22:30:51  Rajesh_R
 * 	Modified the defines that find drawer, cabinet id to reflect the changes
 * 	made in the configtree. We use more generic names for sensors to avoid
 * 	having dependency on the hardware naming conventions are they are subject
 * 	to change, hence removed all the sensor name string structures.
 *
 * Revision 1.1.2.2  2002/04/09  00:09:00  Rajesh_R
 * 	Added environmenta support for marvel.
 *
 * Revision 1.1.2.1  2001/10/25  14:55:21  Rajesh_R
 * 	Initial checkin
 *
 * $EndLog$
 */
/* MV_TODOf:
 *	This file is wfsrvmgmt.c hacked just enough to compile for Marvel.
 *	It needs a complete re-write for Marvel Environmental management.
 */
/*
 * @(#)$RCSfile: marvel_srvmgmt.h,v $ $Revision: 1.1.6.4 $ (DEC) $Date: 2003/11/14 17:23:17 $
 */


#ifndef __ARCH_ALPHA_HAL_MARVEL_SRVMGMT_H__
#define __ARCH_ALPHA_HAL_MARVEL_SRVMGMT_H__

#include <hal/cfgtree.h>

/* The following defines are used to determined the cabinet, drawer
 * id's in a given cfgtree node. 
 * 
 * MBM 
 * 	HSBB<32:39>
 * 		DRAWER  ID    <32:33> 
 * 		CABINET ID    <34:39>
 * PBM 
 * 	HSBB<32:39> 
 * 		DRAWER  ID    <32:34> 
 * 		CABINET ID    <35:39>
 */
#define MV_CFGTEXT_PENUM(X)		((X) & 0xFF)
#define MV_CFGTEXT_DRAWER_ID(X)	  	((X >> 32) & 0xFF)	
#define MV_CFGTEXT_CAB_ID(X)	  	((X >> 48) & 0x3F) 
#define MV_CFGTEXT_IODRAWER_ID(X)	((X >> 32) & 0xFF)
#define MV_CFGTEXT_IOCAB_ID(X)		((X >> 48) & 0xFF)
#define MV_CFGTEXT_CPU_MOD_ID	  	(X & 0xF)
#define MV_MAX_SENSOR_NAME 		255


/* marvel_sensor_subpkt defines the layout for the sensor subpkt in the
 * marvel configure tree. The marvel sensor subpkt unlike the generic
 * subpkt also contains the data and thresold values. This structure is 
 * used both for voltage ans temperature sensors.
 *
 *  Volatage 					Temeperature 
 *  --------					------------
 *  data[0] = current reading			data[0] = current_reading
 *  data[1] = nominal reading			data[1] = high warning 
 *  data[2] = high warning threshold		data[2] = high fault
 *  data[3] = low warning threshold
 *  data[4] = high fault threshold
 *  data[5] = low fault threshold
 * 
 *  On marvels the properties field contains the sensor status.
 */

struct marvel_sensor_subpkt {
	struct      sys_res_config_subpkt_hdr subpkt;
	int         fru_count;
	int         reserved;
	u_long      fru;
	long	    console_id;
	int	    sensor_class;
	int	    sensor_status;
	u_int       data[8];
};

/* marvel_pwr_subpkt defines the layout for the power supply subpkt in the
 * marvel configure tree. The power supply subpkt does not contain any actual
 * readings
 * 
 */
struct marvel_pwr_subpkt {
	struct      sys_res_config_subpkt_hdr subpkt;
	int         fru_count;
	int         reserved;
	u_long      fru;
	u_short     ps_type;   /* 0x1 = DC power, 0x2 = AC input controller */
	u_short     ps_id;     /* power supply index in the node */	
	int         ps_status; /* status of the power supply */
};

/* marvel_fan_subpkt defines the layout for the airmover subpkt in the
 * marvel configure tree. The marvel airmover subpkt contains the actual  
 * reading and threshold values.
 * 
 *  Air movers
 *  ------------
 *  data[0] = current reading 
 *  data[1] = low warning 
 *  data[2] = low fault 
 */

struct marvel_fan_subpkt {
	struct      sys_res_config_subpkt_hdr subpkt;
	int         fru_count;
	int         reserved;
	u_long      fru;
	u_short     cool_type;
	u_short     cool_id;
	int         cool_status;
	u_int	    data[8];
};

struct marvel_vrm_subpkt {
	struct      sys_res_config_subpkt_hdr subpkt;
	int         fru_count;
	int         reserved;
	u_long      fru;
	u_short     ps_type;
	u_short     ps_id;
	int         ps_status;
};

/* This data structure basicall encapsulates all the marvel sensor 
 * subpackets. It 's just for convinience.

struct marvel_env_packets_encap {
	struct sys_res_config_subpkt_hdr subpkt;
	struct marvel_sensor_subpkt  sensor_subpkt;
	struct marvel_pwr_subpkt power_subpkt;
	struct marvel_fan_subpkt cool_subpkt;
	struct marvel_vrm_subpkt vrm_subpkt;
};

/* This structure encapsulates the configtree node and information like the
 * last_node_scan that aids in deciding when to update the node. It also
 * has information like the pointer to the first sensor in that node to get to 
 * a sensor data structure quickly.
 */
struct marvel_pe_node {
	int    sensor_count;
	int    penum;
	long   last_node_scan; 
	struct gct_node  *node;
	struct env_sensor_info *first_sensor;
	struct marvel_pe_node   *next_penode;
};

/* The handle data structure is mainly used by sensor access functions
 * to update sensor status and data. On wildfire's this was the shared 
 * RAM offset. On a marvel we use the config tree handles as in the 
 * configree node(contained in the penode structure), the subpkt within
 * that node and the index of that sensor. 
 * NOTE: Prior to the addition of the marvel_update_penode function this
 * data struture had the config tree node instead of the marvel_pe_node
 * struture.
 */

struct marvel_sensor_handle {
	struct sys_res_config_subpkt_hdr *subpkt_node;
	struct marvel_pe_node *penode;
        int index;
};

/* The penum_2_name structure is used to hold the mapping between 
 * between a P&E number to the name 
 */

struct penum_2_name {
       uint penum;
       char *name;
};

#ifdef	MV_INCLUDE_MARVEL_SRVMGMT

struct penum_2_name penum_2_name[] = {
	{0x09, "mbm"},
	{0x0A, "mbm/pbm"},
	{0x0B, ""},
	{0x0C, "powersupply"},
	{0x0D, "fan"},
	{0x0E, ""},
	{0x0F, "cmm0"},
	{0x10, "cmm1"},
	{0x11, "cmm2"},
	{0x12, "cmm3"},
	{0x13, ""},
	{0x14, "vrm0"},
	{0x15, "vrm1"},
	{0x16, "vrm2"},
	{0x17, "vrm3"},
	{0x18, ""},
	{0x19, "pbm"},
	{0x1A, "xshelf"},
	{0x1B, "pcips"},
	{0x1C, "pcifans"},
	{0x32, "sdiclm"},
	{0x33, "sdi0"},
	{0x34, "sdi1"},
	{0x35, "sdi2"},
	{0x36, "sdi3"},
	{0, 	NULL}
};

#endif /* MV_INCLUDE_MARVEL_SRVMGMT */ 

/*
 * mvsrvmgmt.c debugging aid
 *
 * NOTE: since mvcpu.h, mvioa.h, & mvpci.h may be included in
 *	 one .c file, their definitions must not collide.
 */

extern	u_int	mvcpu_developer_debug;

/* To remove/add all debug printfs */
#define __MVSRVMGMTDEBUG

/* 
 * The setting of "flags" in a debug variable will turn on specific 
 * printf() calls within the kernel.  This sysconfigtab variable is called 
 * mvcpu_developer_debug.
 */


/* Bit defines used to turn on debug printfs */

/* The following defines are used for the flag bits in the printf macro. */

#define MVSRVMGMTD_ENVMON	0x00000001
#define MVSRVMGMTD_SYSEVT	0x00000002
#define MVSRVMGMTD_READSTATE	0x00000004
#define MVSRVMGMTD_REGISTER	0x00000008

/* New, testing hw-support debug printfs				*/
#define MVSRVMGMTD_NOT_YET	0x00000010	/* Notyet prints		*/

/*
 * string defines used to reduce number and size of strings
 * used in the kernel (data space) to print debug messages;
 * underscores used to prevent name collision w/existing drivers
 */
extern char * _MVSRVMGMTenvmon;
extern char * _MVSRVMGMTsysevt;
extern char * _MVSRVMGMTread_state;
extern char * _MVSRVMGMTregister;
extern char * _MVSRVMGMTnot_yet;


/*
 * printf expansion that MVSRVMGMTPRINTF (below) eventually expands to
 *
 * Using the following format, data-space for the _MVSRVMGMTxxx strings
 * is significantly reduced, and is made common for all the supported
 * flag/types listed above.
 */

#ifdef __MVSRVMGMTDEBUG
#   define _MVSRVMGMTD_SYSEVT(X)			\
    {						\
	/* NOSTRICT */				\
	/* Yes, mvcpu_xxxx since this printout wants to		\
	 * coincide with sysevt in mvcpu			\
	 */							\
        if( mvcpu_developer_debug & MVSRVMGMTD_SYSEVT)  {	\
	    /* VARARGS */			\
            printf (_MVSRVMGMTsysevt); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVSRVMGMTD_ENVMON(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvsrvmgmt_developer_debug & MVSRVMGMTD_ENVMON)  {	\
	    /* VARARGS */			\
            printf (_MVSRVMGMTenvmon); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVSRVMGMTD_NOTYET(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvsrvmgmt_developer_debug & MVSRVMGMTD_NOTYET)  {	\
	    /* VARARGS */			\
            printf (_MVSRVMGMTnotyet); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVSRVMGMTD_READSTATE(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvsrvmgmt_developer_debug & MVSRVMGMTD_READSTATE)  {	\
	    /* VARARGS */			\
            printf (_MVSRVMGMTread_state); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVSRVMGMTD_REGISTER(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvsrvmgmt_developer_debug & MVSRVMGMTD_REGISTER)  {	\
	    /* VARARGS */			\
            printf (_MVSRVMGMTregister); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }

/* This Macro is an attempt to be able to allow for specific subsets of the 
 * DEBUG statements be printed. The first argument is for tracking particular
 * subsets of the statements.  This first, flag argument is compared with the 
 * mvcpu_developer_debug variable to determine if the develper wants to see the 
 * message. It is not checking for exact matching, ie, "== F.  This allows
 * he same Macro to be used for different settings of the flags, i.e.,
 * MVSRVMGMTD_INOUT | MVSRVMGMTD_CPU
 *
 * The X argument is "ugly" it must be a complete printf argument set 
 * enclosed within "()", this will allow the pre-processor to include
 * it in the final printf statement. 
 */
#define MVSRVMGMTPRINTF(F, X)	_##F(X)

#else  /* !__MVSRVMGMTDEBUG */
#   define MVSRVMGMTPRINTF(F, X)
#endif /* __MVSRVMGMTDEBUG */

#endif /* __ARCH_ALPHA_HAL_MARVEL_SRVMGMT_H__ */

