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
 * @(#)$RCSfile: cardinfo.h,v $ $Revision: 1.1.18.2 $ (DEC) $Date: 1999/04/05 11:40:34 $
 */

#ifndef _CARDINFO_H_
#define _CARDINFO_H_

/****************************************************************/
/*								*/
/* MODULE NAME: cardinfo.h					*/
/*								*/
/* LOCATION:	/src/kernel/io/dec/pcmcia			*/
/*								*/
/* DESCRIPTION:							*/
/* 	Contains definitions for the PCMCIA Card Services and	*/
/* 	Card Information Structure (CIS) data.			*/
/*	Also includes CardBus PC Card's configuration header.	*/
/*								*/
/* STRUCTURES:							*/
/*	tuple_info	Argument structure to get first/next 	*/
/*			CIS tuples and tuple data		*/
/*								*/
/*	tuple_data_info Argument structure to get the specified */
/*			tuple's data fields			*/
/*								*/
/*	config_info	Argument structure to get info about	*/
/*			the socket and the PC card in it	*/
/*								*/
/****************************************************************/

#include <sys/types.h>	
#include <io/dec/pcmcia/pcmcia.h>
#include <io/common/devdriver.h>


/****************************************************************/
/* Card Services (CS) interface data structure definitions	*/
/*								*/
/* 	The definitions are based on the PC Card Standard       */
/* 	CARD SERVICES SPECIFICATION (1995)			*/
/****************************************************************/


/* Argument structure to get first/next CIS tuples */

struct tuple_info {
   u_short	socket;			/* Logical socket number */
   u_short	attributes;		/* Bit-mapped attributes field */
   u_char	DesiredTuple;		/* Desired tuple code value */
   u_char	reserved;		
   u_short	flags;			/* CS tuple flags data	*/
   u_int	LinkOffset;		/* CS link state information */
   u_int	CISOffset;		/* CS CIS state information */

   u_int	cb_cur_cis_ptr;		/* Current tuple's CIS pointer */
                                        /* used only for CardBus card  */
   u_int	spare1;			/* spare byte for future	*/
   u_char	TupleLinkSave;		/* Current tuple's link value */
   u_char	spare2;			/* spare byte for future	*/

   u_char	TupleCode;		/* Tuple code found */
   u_char	TupleLink;		/* Link value for tuple found */

};   

/* 
 * 'socket' field masks to get at logical socket number and function 
 * value on the PC Card
 */
#define SOCKET_MASK	0x00ff 		/* LSB is logical socket # */
#define FUNC_MASK	0xff00		/* MSB is function #, 0 for single	*/
                                        /* function card, 0 to 7 for multiple	*/
                                        /* function card			*/
#define FUNC_NUM_SHIFT  0x8		/* Shift value to get func number	*/

/* 'attributes' bit-mask field defines */
#define RET_LINK_TPL	0x1		/* Return link tuples (set = true)	*/

/* DesiredTuple field define */
#define ANY_NEXT_TUPLE	0xff		/* requesting any first/next tuple of CIS */

/* Argument structure to get the specified tuple's data */

#define TUPLE_DATA_MAX	0x100		/* max. number of bytes in tuple data */
#define TUPLE_SIZE_MAX  0x108		/* max. number of bytes to get entire tuple */

struct tuple_data_info {
   short	socket;			/* Logical socket number */
   u_short	attributes;		/* Bit-mapped attributes field */
   u_char	DesiredTuple;		/* Desired tuple code value */
   u_char	TupleOffset;		/* Offset into tuple from link byte */		
   u_short	flags;			/* CS tuple flags data	*/
   u_int	LinkOffset;		/* CS link state information */
   u_int	CISOffset;		/* CS CIS state information */

   u_int	cb_cur_cis_ptr;		/* Current tuple's CIS pointer */
                                        /* used only for CardBus card  */
   u_int	spare1;			/* spare byte for future	*/
   u_char	TupleLinkSave;		/* Current tuple's link value */
   u_char	spare2;			/* spare byte for future	*/

   u_short	TupleDataMax;		/* Max. size of tuple data area */
   u_short	TupleDataLen;		/* Number of bytes in tuple body */
   u_char	TupleData[TUPLE_DATA_MAX];   /* Tuple data */
   
};


/*
 * Defines for 'flags' field in tuple_info and tuple_data_info structures 
 */
#define END_OF_CIS	0x0001		/* end of CIS area reached */
#define CORRUPTED_ARG	0x0002		/* data from prior GetFirst/NextTuple is corrupt */
#define NULL_TUPLE	0x0004		/* current tuple is a NULL tuple */

#define LINK_COMMON	0x0010		/* Longlink to Common Memory	 */
#define LINK_ATTR	0x0020		/* Longlink to Attribute Memory  */
#define LINK_MFC	0x0040		/* Longlink to Multifunction 	 */
#define LINK_CB		0x0080		/* Longlink to next chain on CB	 */
#define MFC_ATTR	0x0100		/* MFC link to Attribute Memory  */
#define CIS_ATTR	0x0200		/* CIS in Attribute Memory space */
#define CIS_COMMON	0x0400		/* CIS in Common Memory space 	 */
#define CIS_CB_MEM	0x0800		/* CIS in CardBus memory space	 */
#define CIS_CB_CH	0x1000		/* CIS in CardBus Config. header */
#define	CIS_CB_EXROM	0x2000		/* CIS in CardBus Expansion ROM  */

/*
 * Parsed tuple data structures
 * Individual structures for each tuple type and a union of various tuple
 * data type structures
 */

/* 
 * NOTE: The following structure only allows one set of device info field
 *       to be parsed.  If the device has more than one device info field
 *       in its CISTPL_DEVICE(_A) tuple, it should parse the data on its own.
 */

typedef struct cistpl_device_t {
    u_int	dev_speed;		/* Device speed (16-bit PC Card only) */
                                        /* Address Space indicator if CardBus card */

    u_int	wps;			/* Write Protect Switch flag */
    u_int	dev_type;		/* Device type code */
    u_int	ext_dev_speed;		/* Extended device speed */
    u_int	ext_dev_speed2;		/* Additional extended device speed */
    u_int	ext_dev_type;		/* Extended device type */
    u_int	ext_dev_type2;		/* Additional extended device type */
    u_int	dev_size;		/* Device size code */
    u_int	num_addr_unit;		/* Number of address units - 1 */
} cistpl_device_t;


/*
 * defines for fields in cistpl_device_t
 */
#define CONF_DEV_SPEED	0x07		/* Device Speed mask */
#define CONF_WPS	0x08		/* Write Protect Switch bit */
#define CONF_DEV_TYPE	0xf0		/* Device type mask */
#define CONF_EXT_SPEED	0x07		/* Extended device speed indicator */
#define CONF_EXT_TYPE	0x0e		/* Extended device type indicator */
#define CONF_DEV_SIZE	0x07		/* Device Size mask */
#define CONF_ADDR_UNITS	0xf8		/* (# of address units -1) mask */

#define VERS_1_MAX_PROD_STRLEN  32

#define addr_sp_ind	dev_speed	/* In cistpl_device_t, dev_speed location */
                                        /* is used as Address Space Indicator if  */
                                        /* the card is a CardBus card		  */

/* The Other Conditions Device information tuple */

typedef struct cistpl_device_o_t {
    u_int		other_cond_flag;	/* Other Conditions Info flag */
    cistpl_device_t	device;			/* rest are same as CISTPL_DEVICE info */
} cistpl_device_o_t;

/* defines for 'other_cond_flag' value */
#define DEVICE_MWAIT		0x01		/* 16-bit card only */
#define DEVICE_5VCC		0x00		/* 5V Vcc operation */
#define DEVICE_3VCC		0x02		/* 3.3V Vcc operation */


typedef struct cistpl_vers_1_t {
    u_char	major_ver;		/* Major version number */
    u_char	minor_ver;		/* Minor version number */
    int		num_prodinfo;		/* Number of product info strings in this tuple */

    char	product[4][VERS_1_MAX_PROD_STRLEN+1];
                                        /* 1st string: Name of manufacturer, terminated by NULL */
                                        /* 2nd string: Name of product, terminated by NULL */
                                        /* 3rd string: Additional product info. in text, terminated */
                                        /* by NULL, usually lot number */
                                        /* 4th string: Additional product info. in text, terminated */
                                        /* by NULL, usually programming conditions */
} cistpl_vers_1_t;



typedef struct cistpl_manfid_t {
    u_short	manufact_code;		/* PC Card manufacturer code */
    u_short	manufact_info;		/* part number and/or revision # */
} cistpl_manfid_t;

typedef struct cistpl_funcid_t {
    u_int	func_code;		/* Card function code */
    u_int	sysinit_mask;		/* System initialization bit mask */
} cistpl_funcid_t;


/*
 * Note: Any subtuples within a Configuration Tuple is not parsed
 *       by the generic parse routine.  It will only return indication
 *       as to if there is a subtuple following the standard fields
 */
typedef struct cistpl_config_t {
    u_int	last_conf_index;	/* Configuration Index Number of the last configuration */
                                        /* described in the Card Configuration Table.   */
    u_int	subtuple_flag;		/* Set to 1 if subtuples following the default  */
                                        /* fields					*/

    u_long	conf_reg_base;		/* Configuration Registers Base Address in 	*/
                                        /* an even byte of Attribute Memory Space	*/
    u_long	conf_reg_mask[2];	/* Configuration Register Presence Mask for 	*/
                                        /* Registers 0 to 63 and 64 to 127		*/

} cistpl_config_t;

/*
 * Defines for the Configuration Register Present Mask 
 */
#define COR_PRESENT		0x1
#define CSR_PRESENT		0x2
#define PIN_REPL_PRESENT	0x4
#define SOCKET_COPY_PRESENT	0x8
#define EXT_STATUS_PRESENT	0x10
#define IO_BASE0_PRESENT	0x20
#define IO_BASE1_PRESENT	0x40
#define IO_BASE2_PRESENT	0x80
#define IO_BASE3_PRESENT	0x100
#define IO_LIM_PRESENT		0x200


typedef struct cistpl_config_cb_t {
    u_int	last_conf_index;	/* Configuration Index Number of the last configuration */
    u_int	addr_space;		/* Address Space Indicator for CardBus Status 	*/
                                        /* registers, memory space only			*/
    u_int	addr_offset;		/* Address Space Offset for Status registers 	*/
                                        /* -- 8 byte aligned				*/
    u_int	subtuple_flag;		/* Set to 1 if subtuples follow default fields  */
} cistpl_config_cb_t;


typedef struct conf_power_t {		/* Power description struct in conf. table entry */
    u_int	parameter_select;	/* Parameter Selection byte */
    u_short	power_def[8];		/* Up to 2 bytes of parameter definitions for */
                                        /* each power parameter type		      */
} conf_power_t;

typedef struct conf_timing_t {		/* Configuration Timing struct. */
    u_char	scale;			/* WAIT scale, READY scale, & Reserved Scale 7 	*/
    u_char	wait_speed;		/* wait time	*/
    u_char	ready_speed;		/* max. time in the Busy State for the READY signal */
    u_char	rsv_speed;		/* reserved time     */
} conf_timing_t;

/*
 * defines for scale field in conf_timing_t 
 */
#define CONF_TIMING_WAIT		0x03
#define CONF_TIMING_RDY			0x1c
#define CONF_TIMING_RDY_SHIFT		2
#define CONF_TIMING_RSV			0xe0
#define CONF_TIMING_RSV_SHIFT		5

typedef struct conf_io_t {		/* Configuration I/O space description struct 	*/
    u_char	flags;			/* flags byte including # of address lines	*/
    u_char	range_descriptor;	/* I/O Range Descriptor byte			*/
    u_short	reserved;		/* place holder for alignment			*/
    u_int	base[16];		/* Start of I/O address blocks, up to 16 bases	*/
    int		len[16];		/* Length of I/O address blocks 		*/
} conf_io_t;

/*
 * defines for flags field in conf_io_t
 */
#define CONF_IO_LINES_MASK 	0x1f
#define CONF_IO_8BIT		0x20
#define CONF_IO_16BIT		0x40
#define CONF_IO_RANGE		0x80


typedef struct conf_irq_t {		/* Configuration Interrupt Request description  */
    u_short	num_flags;		/* IRQ number and flags				*/
    u_short	irq_mask;		/* Bit mask of acceptable IRQ numbers 0-15	*/
} conf_irq_t;

/*
 * define for num_flags field in conf_irq_t
 */
#define CONF_IRQ_MASK	0x10		/* Flag indicating IRQ mask present		*/
#define CONF_IRQ_NUM	0x0f		/* Mask to get particular IRQ number 		*/


typedef struct conf_mem_t {		/* Configuration Memory space description       */
    u_short	flag;			/* Memory space feature, part of TPCE_FS byte   */
    u_short	desc;			/* Descriptor byte for up to 8 windows		*/
    u_int	win_length[8];		/* Length of the window in units of 256 bytes   */
    u_int	card_addr[8];		/* Card addresses for the windows		*/
    u_int	host_addr[8];		/* Host addresses for the memory windows	*/	
} conf_mem_t;

/*
 * defines for desc field in conf_mem_t
 */
#define CONF_MEM_NUMWIN		0x07
#define CONF_MEM_LENSIZE	0x18
#define CONF_MEM_CARDADDR	0x60
#define CONF_MEM_HOSTADDR	0x80

/* 
 * defines for flag field in conf_mem_t
 */
#define CONF_MEM_NO		0x00	/* No memory space required             */
#define CONF_MEM_LEN_ONLY	0x01	/* Only single 2-byte length specified  */
#define CONF_MEM_LEN_CARDMEM	0x02	/* Length (2 bytes) and Card Address    */
                                        /* (2 bytes) specified.			*/
#define CONF_MEM_DESC		0x03	/* A memory space descriptor byte exists*/

/*
 * NOTE: Any subtuples and the miscellaneous features fields within a Configuration
 *       Table Entry tuple are not parsed by the generic parse routine.  
 */
    
typedef struct cistpl_cftable_entry_t {
    u_int		index;		/* Configuration Entry Number 	*/
    u_int		Default;	/* Flag indicating this tuple contains default 	*/
                                        /* values/conditions for the conf. fields	*/
    u_int		intf_exist;	/* Flag indicating if the interface description */
                                        /* field was present in the tuple		*/
    u_char		interface;	/* Card interface type, e.g. memory only, 	*/
                                        /* I/O and memory, etc. & status bits		*/
    u_char		features;	/* Feature selection byte, indicates which 	*/
                                        /*   optional fields are present in the tuple   */
    u_short		reserved;	/* space for alignment				*/
    conf_power_t 	power[3];	/* Up to 3 power description structures		*/
    
    conf_timing_t 	timing;		/* Timing-description structure 		*/
    conf_io_t		io;		/* I/O space description structure		*/
    conf_irq_t		irq;		/* Interrupt request description structure	*/
    conf_mem_t		mem;		/* Memory space description structure		*/
    

} cistpl_cftable_entry_t;

/*
 * defines for Feature Selection Byte 
 */
#define CISTPL_CFTABLE_ENTRY_POWER	0x03
#define CISTPL_CFTABLE_ENTRY_TIMING	0x04
#define CISTPL_CFTABLE_ENTRY_IO      	0x08
#define CISTPL_CFTABLE_ENTRY_IRQ	0x10
#define CISTPL_CFTABLE_ENTRY_MEM	0x60
#define CISTPL_CFTABLE_ENTRY_MISC	0x80


/* 
 * CardBus card version of Configuration Table Entry tuple 
*/
typedef struct cistpl_cftable_entry_cb_t {
    u_int		index;		/* Configuration Entry Number 	*/
    u_int		Default;	/* Flag indicating this tuple contains default 	*/
                                        /* values/conditions for the conf. fields	*/
    u_int		features;	/* Feature selection byte, indicates which 	*/
                                        /*   optional fields are present in the tuple   */
    conf_power_t 	power[3];	/* Up to 3 power description structures		*/
    u_int		io_bar_map;	/* Bit map of I/O Base Address Registers	*/
    conf_irq_t		irq;		/* Interrupt request description structure	*/
    u_int		mem_bar_map;	/* Bit map of Memory Base Address Registers	*/
    u_char		misc[2];	/* Miscellaneous Features bytes			*/

} cistpl_cftable_entry_cb_t;

/* Defines for bit map of Base Address Registers fields */
#define CONF_IO_BAR1		0x02	/* BAR1 maps I/O space 		*/
#define CONF_IO_BAR2		0x04	/* BAR2 maps I/O space		*/
#define CONF_IO_BAR3		0x08	/* BAR3 maps I/O space		*/
#define CONF_IO_BAR4		0x10	/* BAR4 maps I/O space		*/
#define CONF_IO_BAR5		0x20	/* BAR5 maps I/O space		*/

#define CONF_IO_BAR_MASK	0x3e	/* I/O BAR used mask		*/

#define CONF_MEM_BAR1		0x02	/* BAR1 maps memory space	*/
#define CONF_MEM_BAR2		0x04	/* BAR2 maps memory space	*/
#define CONF_MEM_BAR3		0x08	/* BAR3 maps memory space	*/
#define CONF_MEM_BAR4		0x10	/* BAR4 maps memory space	*/
#define CONF_MEM_BAR5		0x20	/* BAR5 maps memory space	*/
#define CONF_MEM_BAR6		0x40	/* BAR6 maps memory space	*/
#define CONF_MEM_BAR7		0x80	/* Exp. ROM BAR maps memory space */

#define CONF_MEM_BAR_MASK	0xfe	/* Memory BAR used mask		*/

/* Defines for 'misc' field in CISTPL_CFTABLE_ENTRY_CB */
/* misc[0] */
#define CBMI_BUS_MASTER		0x01	/* Can be a bus master		*/
#define CBMI_MEM_WR_INV		0x02	/* Memory Write and Invalidate	*/
#define CBMI_VGA_PALETTE	0x04	/* VGA palette snoop		*/
#define CBMI_PAR_ERR_RSP	0x08	/* Parity error response	*/
#define CBMI_WAIT_CYCLE		0x10	/* Wait cycle control		*/
#define CBMI_SERR_EN		0x20	/* SERR enable			*/
#define CBMI_FAST_BBE		0x40	/* Fast Back-to-Back capable	*/
/* misc[1] */
#define CBMI_PWM_EN		0x01	/* PWM Audio Enable		*/
#define CBMI_BAM_EN		0x02	/* Binary Audio Enable		*/


typedef struct cistpl_bar_t {
    u_int	addr_space;		/* Address Space Indicator	*/
    u_int	type;			/* 0 = memory, 1 = I/O		*/
    u_int	mem_flag;		/* prefetchable/cacheable flag  */
    u_long	bar_size;		/* # of bytes to map on BARn	*/
} cistpl_bar_t;

#define CISTPL_BAR_MEM			0x00	/* Memory space type	*/
#define CISTPL_BAR_IO			0x01	/* I/O space type 	*/
#define CISTPL_BAR_ADDR_SPACE_MASK	0x7	/* Address Space Indicator mask */
#define CISTPL_BAR_TYPE_MASK		0x10	/* Address type mask */

#define CISTPL_BAR_PREFETCH		0x01	/* Prefetchable, but not cacheable */
#define CISTPL_BAR_PREFETCH_CACHE	0x02	/* Both prefetchable and cacheable */
#define CISTPL_BAR_PREFETCH_MASK	0x60	/* Prefetch flag mask */


typedef struct cistpl_longlink_cb_t {
    u_int	addr_space;		/* Address Space Indicator	*/
    u_int	image_num;		/* Exp ROM image #, valid only for Exp ROM */
    u_long	addr_offset;		/* Address Space Offset -- 8 byte aligned */
} cistpl_longlink_cb_t;



#define CISTPL_MAX_FUNCTIONS	8	/* max. # of functions in a card */
#define CISTPL_MFC_ATTR		0x00	/* function CIS in Attribute Memory */
#define CISTPL_MFC_COMMON	0x01	/* function CIS in Common Memory */

typedef struct cistpl_longlink_mfc_t {
    u_int	num_func;		/* Number of functions in the card */
    struct {
	u_int	space;			/* Attribute or Common Memory space */
	u_long	cis_addr;		/* CIS address for the function n   */
    } func[CISTPL_MAX_FUNCTIONS];	

} cistpl_longlink_mfc_t;


typedef union cisparse_t {
    cistpl_device_t		device;		/* CISTPL_DEVICE tuple data */
    cistpl_device_o_t		device_o;	/* CISTPL_DEVICE_OC or _OA tuple data */
    cistpl_vers_1_t		version_1;	/* CISTPL_VERS_1 tuple data */
    cistpl_manfid_t		manfid;		/* CISTPL_MANFID tuple data */
    cistpl_funcid_t		funcid;		/* CISTPL_FUNCID tuple data */
    cistpl_config_t		config;		/* CISTPL_CONFIG tuple data */
    cistpl_config_cb_t		config_cb;	/* CISTPL_CONFIG_CB tuple data */
    cistpl_cftable_entry_t 	cftable;	/* CISTPL_CFTABLE_ENTRY tuple data */
    cistpl_cftable_entry_cb_t	cftable_cb;	/* CISTPL_CFTABLE_ENTRY_CB tuple data */
    cistpl_bar_t		bar;		/* CISTPL_BAR tuple data */
    cistpl_longlink_cb_t	longlink_cb;	/* CISTPL_LONGLINK_CB tuple data */
    cistpl_longlink_mfc_t	longlink_mfc;	/* CISTPL_LONGLINK_MFC tuple data */

} cisparse_t;



/* Argument structure to get info. about the socket and the PC card conf. */

struct config_info {
   short	socket;			/* Logical socket number */
   u_short	attributes;		/* Bit-mapped attributes field */
   u_char	Vcc;			/* Vcc Setting */
   u_char	Vpp1;			/* Vpp1 Setting */
   u_char	Vpp2;			/* Vpp2 Setting */
   u_char	IntType;		/* Memory or Memory+I/O interface */
   u_int	ConfigBase;		/* Card Base address of config registers */
   u_char	status;			/* Card Status register setting, if present */
   u_char	pin;			/* Card Pin register setting, if present */
   u_char	copy;			/* Card Socket/Copy register setting, if present */
   u_char	option;			/* Card Option register setting, if present */
   u_char	present;		/* Card Configuration registers present */
   u_char	FirstDevType;		/* From Device ID Tuple */
   u_char	FuncCode;		/* From Function ID Tuple */
   u_char	SysInitMask;		/* From Function ID Tuple */
   u_short	ManufCode;		/* From Manufacturer ID Tuple */
   u_short	ManufInfo;		/* From Manufacturer ID Tuple */
   u_char	CardValues;		/* Valid Card Register Values */
   u_char	AssignedIRQ;		/* IRQ assigned to PC Card */
   u_short	IRQAttributes;		/* Attributes for assigned IRQ */
   u_short	BasePort1;		/* Base port address for range */
   u_char	NumPorts1;		/* Number of contiguous ports */
   u_char	Attributes1;		/* Bit-mapped */
   u_short	BasePort2;		/* Base port address for range */
   u_char	NumPorts2;		/* Number of contiguous ports */
   u_char	Attributes2;		/* Bit-mapped */
   u_char	IOAddrLines;		/* Number of IO address lines decoded */
   
};

/****************************************************************/
/* Card Services service code					*/
/****************************************************************/

#define CLOSE_MEMORY		0x00
#define COPY_MEMORY		0x01
#define DEREGISTER_CLIENT	0x02
#define GET_CLIENT_INFO		0x03
#define GET_CONFIG_INFO		0x04
#define GET_FIRST_PARTITION	0x05
#define GET_FIRST_REGION	0x06
#define GET_FIRST_TUPLE		0x07
#define	GET_NEXT_PARTITION	0x08
#define GET_NEXT_REGION		0x09
#define GET_NEXT_TUPLE		0x0a
#define GET_CARD_SERVICES_INFO	0x0b
#define GET_STATUS		0x0c
#define GET_TUPLE_DATA		0x0d
#define GET_FIRST_CLIENT	0x0e
#define REGISTER_ERASE_QUEUE	0x0f
#define REGISTER_CLIENT		0x10
#define RESET_FUNCTION		0x11
#define MAP_LOG_SOCKET		0x12
#define MAP_LOG_WINDOW		0x13
#define MAP_MEM_PAGE		0x14
#define MAP_PHY_SOCKET		0x15
#define MAP_PHY_WINDOW		0x16
#define MODIFY_WINDOW		0x17
#define OPEN_MEMORY		0x18
#define READ_MEMORY		0x19
#define REGISTER_MTD		0x1a
#define RELEASE_IO		0x1b
#define RELEASE_IRQ		0x1c
#define RELEASE_WINDOW		0x1d
#define RELEASE_CONFIGURATION	0x1e
#define REQUEST_IO		0x1f
#define REQUEST_IRQ		0x20
#define REQUEST_WINDOW		0x21
#define REQUEST_SOCKET_MASK	0x22
#define RETURN_SS_ENTRY		0x23
#define WRITE_MEMORY		0x24
#define DEREGISTER_ERASE_QUEUE	0x25
#define CHECK_ERASE_QUEUE	0x26
#define MODIFY_CONFIGURATION	0x27
#define REGISTER_TIMER		0x28
#define SET_REGION		0x29
#define GET_NEXT_CLIENT		0x2a
#define VALIDATE_CIS		0x2b
#define REQUEST_EXCLUSIVE	0x2c
#define RELEASE_EXCLUSIVE	0x2d
#define GET_EVENT_MASK		0x2e
#define RELEASE_SOCKET_MASK	0x2f
#define REQUEST_CONFIGURATION	0x30
#define SET_EVENT_MASK		0x31
#define ADD_SOCKET_SERVICES	0x32
#define REPLACE_SOCKET_SERVICES 0x33
#define VENDOR_SPECIFIC		0x34
#define ADJUST_RESOURCE_INFO	0x35
#define ACCESS_CONFIG_REGISTER	0x36
#define GET_FIRST_WINDOW	0x37
#define GET_NEXT_WINDOW		0x38
#define GET_MEM_PAGE		0x39
#define REQUEST_DMA		0x3a
#define RELEASE_DMA		0x3b



/****************************************************************/
/* Return Codes from Card Services and Socket Services function */
/* calls							*/
/****************************************************************/

#define SUCCESS			0x00	/* The request succeeded */
#define BAD_ADAPTER		0x01	/* Specified adapter is invalid */
#define BAD_ATTRIBUTE		0x02	/* Value specified for attributes field is invalid */
#define BAD_BASE		0x03	/* Specified base system memory address is invalid */
#define BAD_EDC			0x04	/* Specified EDC generator is invalid */

#define BAD_IRQ			0x06	/* Specified IRQ level is invalid */
#define BAD_OFFSET		0x07	/* Specified PC Card memory array offset is invalid */
#define BAD_PAGE		0x08	/* Specified page is invalid */
#define READ_FAILURE		0x09	/* Unable to complete read request */
#define BAD_SIZE		0x0a	/* Specified size is invalid */
#define BAD_SOCKET		0x0b	/* Specified socket is invalid (logical or physical) */

#define BAD_TYPE		0x0d	/* Window or interface type specified is invalid */
#define BAD_VCC			0x0e	/* Specified Vcc power level index is invalid */
#define BAD_VPP			0x0f	/* Specified Vpp1 or Vpp2 power level index is invalid */

#define BAD_WINDOW		0x11	/* Specified window is invalid */
#define WRITE_FAILURE		0x12	/* Unable to complete write request */

#define NO_CARD			0x14	/* No PC Card in socket */
#define UNSUPPORTED_SERVICE	0x15	/* Implementation does not support service */
#define UNSUPPORTED_MODE	0x16	/* Processor mode is not supported */
#define BAD_SPEED		0x17	/* Specified speed is unavailable */
#define BUSY			0x18	/* Unable to process request at this time - retry later */
#define GENERAL_FAILURE		0x19	/* An undefined error has occurred */
#define WRITE_PROTECTED		0x1a	/* Media is write-protected */
#define BAD_ARG_LENGTH		0x1b	/* ArgLength argument is invalid */
#define BAD_ARGS		0x1c	/* Values in Argument Packet are invalid */
#define CONFIGURATION_LOCKED	0x1d	/* A configuration has already been locked */
#define IN_USE			0x1e	/* Requested resource is being used by a client */
#define NO_MORE_ITEMS		0x1f	/* There are no more of the requested item */
#define OUT_OF_RESOURCE		0x20	/* Card Services has exhausted resource */
#define BAD_HANDLE		0x21	/* ClientHandle is invalid */
#define BAD_VERSION		0x22	/* Client version is unsupported */



/****************************************************************/ 
/* Card Information Structure (CIS) fields definitions 		*/
/*								*/
/* 	The definitions are based on the PC Card Standard       */
/*	METAFORMAT SPECIFICATION (1995)				*/
/****************************************************************/

/* Layer 1 Basic Compatibility Tuples */

#define CISTPL_NULL		0x00	/* Null tuple - ignore */
#define CISTPL_DEVICE   	0x01	/* The device information tuple (common memory) */
#define CISTPL_LONGLINK_CB	0x02	/* Longlink to next chain on a CardBus PC Card */
#define CISTPL_CONFIG_CB	0x04	/* Configuration tuple for a CardBus PC Card function */
/* 0x03 reserved */
#define CISTPL_CFTABLE_ENTRY_CB	0x05	/* A Configuration-Table-Entry for a CardBus PC Card function */
#define CISTPL_LONGLINK_MFC	0x06	/* Longlink to next chain on a Multiple Function card */
#define CISTPL_BAR		0x07	/* Base Address Register definition tuple for a CardBus PC Card */
/* 0x08 - 0x0f reserved */
#define CISTPL_CHECKSUM		0x10	/* The checksum control tuple */
#define CISTPL_LONGLINK_A 	0x11	/* The long link control tuple (to Attribute Memory) */
#define CISTPL_LONGLINK_C	0x12	/* The long link control tuple (to Common Memory) */
#define CISTPL_LINKTARGET	0x13	/* Link-target-control */
#define CISTPL_NO_LINK		0x14	/* No-link to Common Memory */
#define CISTPL_VERS_1		0x15	/* Level 1 version/product information tuple */
#define CISTPL_ALTSTR		0x16	/* The alternate language string tuple */
#define CISTPL_DEVICE_A		0x17	/* Attribute Memory device information */
#define CISTPL_JEDEC_C		0x18	/* JEDEC programming information (for Common Memory) */
#define CISTPL_JEDEC_A		0x19	/* JEDEC programming information (for Attribute Memory) */
#define CISTPL_CONFIG		0x1a	/* Configuration tuple for a 16-bit PC Card */
#define CISTPL_CFTABLE_ENTRY	0x1b	/* The Configuration Table Entry tuple */
#define CISTPL_DEVICE_OC	0x1c	/* Other operating conditions device information for Common Memory */
#define CISTPL_DEVCIE_OA	0x1d	/* Other operating conditions device information for Attribute Memory */
#define CISTPL_DEVICEGEO	0x1e	/* Device geometry info for Common Memory devices  */
#define CISTPL_DEVICEGEO_A	0x1f	/* Device geometry info for Attribute Memory devices */
#define CISTPL_MANFID		0x20	/* Manufacturer Identification string */
#define CISTPL_FUNCID		0x21	/* Funtion class identification tuple */
#define CISTPL_FUNCE		0x22	/* Funtion Extensions  */

#define CISTPL_END		0xff	/* The end-of-chain tuple */

/* Layer 2 Data Recording Format Tuples */

#define CISTPL_SWIL		0x23	/* Software interleaving tuple */
/* 0x24 - 0x3f reserved */
#define CISTPL_VERS_2		0x40	/* The level 2 version tuple */
#define CISTPL_FORMAT		0x41	/* Data recording format for Common Memory  */
#define CISTPL_GEOMETRY		0x42	/* Partition geometry tuple */
#define CISTPL_BYTEORDER 	0x43	/* Byte ordering for disk-like partitions */
#define CISTPL_DATE		0x44	/* Card initialization date tuple */
#define CISTPL_BATTERY		0x45	/* Battery replacement date tuple */
#define CISTPL_FORMAT_A		0x47	/* Data recording format for Attribute Memory */

/* Layer 3 Data Organization Tuple */

#define CISTPL_ORG		0x46	/* Partition organization tuple */

/* Layer 4 System-Specific Standard Tuples */

/* 0x80 - 0x8f Vendor unique tuples */
#define CISTPL_SPCL		0x90	/* Special Purpose tuple */
/* 0x91 - 0xfe reserved */



/* Device Speed Codes */

#define DSPEED_NULL  0x00		/* Use when device type = null */
#define DSPEED_250NS 0x01		/* 250 nsec */
#define DSPEED_200NS 0x02		/* 200 nsec */
#define DSPEED_150NS 0x03		/* 150 nsec */
#define DSPEED_100NS 0x04		/* 100 nsec */
#define DSPEED_EXT   0x07		/* Use extended speed byte */

/* Device Type Codes */

#define DTYPE_NULL   	0x00		/* No device */
#define DTYPE_ROM	0x01		/* Masked ROM */
#define DTYPE_OTPROM	0x02		/* One-time programmable PROM */
#define DTYPE_EPROM	0x03		/* UV EPROM */
#define DTYPE_EEPROM	0x04		/* EEPROM */
#define DTYPE_FLASH	0x05		/* Flash EPROM */
#define DTYPE_SRAM	0x06		/* Static RAM (JEIDA has Nonvolatile RAM) */
#define DTYPE_DRAM	0x07		/* Dynamic RAM (JEIDA has Volatile RAM) */
#define DTYPE_FUNCSPEC	0x0d		/* Function-specific memory address range */
#define DTYPE_EXTEND	0x0e		/* Extended type follows */

/* Device Size */

#define SIZE_512B	0x00		/* 512 bytes */
#define SIZE_2K		0x01
#define SIZE_8K		0x02
#define SIZE_32K	0x03
#define SIZE_128K	0x04
#define SIZE_512K	0x05
#define SIZE_2M		0x06

/* PC Card Functions */

#define MULTI_FUNC	0x00		/* Multiple functions PC card */
#define MEMORY		0x01		/* Memory card */
#define SERIAL_PORT	0x02		/* Serial I/O port, includes modem cards */
#define PARALLEL_PORT	0x03		/* Parallel printer port */
#define FIXED_DISK	0x04		/* Fixed drive */
#define VIDEO_ADAPTER	0x05		/* Video interface */
#define NETWORK_LAN	0x06		/* Local Area Network adapter */
#define AIMS		0x07		/* Auto Incrementing Mass Storage card */
#define SCSI_BRIDGE	0x08		/* SCSI bridge */
#define SECURITY_SERV	0x09		/* Security services */
 


/* System Initialization Byte */
#define POST		0x01		/* Power-On Self Test to configure PC card */
#define ROM		0x02		/* PC card cotains a system expansion ROM */


/****************************************************************/
/* 16-bit PC Card's Function Configuration Registers Definition	*/
/*								*/
/* Note that I/O Base Register is mandatory on multiple function*/
/* cards, while it is optional for a single function card.      */
/*								*/
/*	The definitions are based on the PC Card Standard	*/
/*	ELECTRICAL SPECIFICATION (1995)				*/
/****************************************************************/

/* Register offset from Config. Register Base Address in Attribute Memory Space */

#define CONF_OPTION_REG	0x0000		/* Configuration Option Register     */
#define CONF_STATUS_REG 0x0002		/* Configuration and Status Register */
#define PIN_REPL_REG	0x0004		/* Pin Replacement Register	     */
#define SOCKET_COPY_REG 0x0006		/* Socket and Copy Register	     */
#define EXT_STATUS_REG	0x0008		/* Extended Status Register	     */

#define IO_BASE_REG_0	0x000A		/* I/O Base Address Register byte 0  */
#define IO_BASE_REG_1	0x000C		/* I/O Base Address Register byte 1  */
#define IO_BASE_REG_2	0x000E		/* I/O Base Address Register byte 2  */
#define IO_BASE_REG_3	0x0010		/* I/O Base Address Register byte 3  */
#define IO_LIMIT_REG	0x0012		/* I/O Limit Register		     */




/* bit def. for Configuration Option Register */
#define FUNC_CONF_INDEX_MASK	0x3f	/* Function Configuration Index mask */
#define LEVEL_REQ		0x40	/* Level mode interrupt bit	     */
#define SRESET			0x80	/* PC Card reset bit		     */

/* For multiple function 16-bit card, bits 0-2 have following def. */
#define ENABLE_FUNC		0x01	/* The function is enabled 	     */
#define ENABLE_BASE_LIMIT	0x02	/* Enable Base and Limit Registers   */
#define ENABLE_IREQ		0x04	/* Enable IREQ# routing		     */


/* bit def. for Configuration and Status Register */
#define ENABLE_AUDIO		0x08	/* Enables audio on SPKR# 	     */
#define CSR_INTR		0x02	/* Interrupt Request/Acknowlege	bit  */


/****************************************************************/
/* CardBus PC Card's Function Event Registers Definition	*/
/*								*/
/* These 4 32-bit registers are provided in each function of a  */
/* CardBus card for notifying status change.  These registers   */
/* are located in memory space at the location given by the     */
/* CISTPL_CONFIG_CB tuple in the function's CIS.  		*/
/*								*/
/* 	The definitions are based on the PC Card Standard	*/
/*	ELECTRICAL SPECIFICATION (1995)				*/
/****************************************************************/

/* Register offset from Base Address specified in CISTPL_CONFIG_CB */

#define FUNC_EVENT_REG		0x0000		/* Function Event Register 	*/
#define FUNC_EVENT_MASK_REG	0x0004		/* Function Event Mask Register */
#define FUNC_PRESENT_ST_REG	0x0008		/* Function Present State Reg.  */
#define FUNC_FORCE_EVENT_REG	0x000C		/* Function Force Event Register*/

/* common bit def. for Function Event Registers */
#define FUNC_EVENT_WP		0x0001		/* Write Protect		*/
#define FUNC_EVENT_READY	0x0002		/* Ready/Busy			*/
#define FUNC_EVENT_BVD2		0x0004		/* Battery Voltage Detect 2	*/
#define FUNC_EVENT_BVD1		0x0008		/* Battery Voltage Detect 1	*/
#define FUNC_EVENT_GWAKE	0x0010		/* General Wakeup		*/

#define FUNC_EVENT_INTR		0x8000		/* Interrupt			*/


/* bit def. for Function Event Mask Register */
#define FUNC_EVENT_BAM		0x0020		/* Binary Audio Enable		*/
#define FUNC_EVENT_PWM		0x0040		/* PWM Audio Enable		*/
#define FUNC_EVENT_WKUP		0x4000		/* Wakeup			*/

/****************************************************************/
/* CardBus PC Card Function's Configuration Space Definition	*/
/*								*/
/* Each function in a CardBus card has its own configuration	*/
/* space.							*/
/* First 64 bytes are mandatory and predefined.			*/
/* Rest of the space is device-dependent and is optional.	*/
/*								*/
/* Note:  Registers which are marked "Allocated" are ignored	*/
/*	  by all CardBus PC Card software, they are fillers to  */
/*	  be compatible with PCI Configuration Space definitions*/
/*								*/
/* 	The definitions are based on the PC Card Standard	*/
/*	ELECTRICAL SPECIFICATION (1995)				*/
/****************************************************************/

/* 
 * Offsets within a Configuration Space Header 
 */
#define CB_ALLOC1		0x00		/* Allocated	*/
#define CB_ALLOC2		0x02		/* Allocated	*/
#define CB_COMMAND		0x04		
#define CB_STATUS		0x06
#define CB_ALLOC3		0x08		/* Allocated	*/
#define CB_ALLOC4		0x09		/* Allocated	*/
#define CB_CACHE_LINE_SIZE	0x0C
#define CB_LATENCY		0x0D		/* Latency Timer */
#define CB_HEADER		0x0E		/* Header Type	 */
#define CB_BIST			0x0F		/* Built-in Self Test */
#define CB_BASE_REG1		0x10		/* Base Address Reg.  */
#define CB_BASE_REG2		0x14
#define CB_BASE_REG3		0x18
#define CB_BASE_REG4		0x1C
#define CB_BASE_REG5		0x20
#define CB_BASE_REG6		0x24
#define CB_CIS_PTR		0x28		/* CIS Pointer	*/
#define CB_EXP_ROM_BASE_REG	0x30		/* Expansion ROM Base Addr. */
#define CB_ALLOC5		0x3C		/* Allocated 	*/
#define CB_INTR_PIN		0x3D		/* Interrupt Pin */
#define CB_ALLOC6		0x3E		/* Allocated	*/
#define CB_ALLOC7		0x3F		/* Allocated	*/
#define CB_DEV_DEP_START	0x40		/* Beginning of Device	*/
                                                /* Dependent Space	*/


/*
 * CardBus Card Configuration Space Header Register bit definitions
 */

/* Command register */

#define CMD_IO_SPACE	0x1	/* I/O space                   	*/
#define	CMD_MEM_SPACE	0x2	/* Memory space                	*/
#define	CMD_BUS_MASTER	0x4	/* Can be a bus master     	*/
#define	CMD_SPEC_CYCLE	0x8	/* Enable special cycles       	*/
#define	CMD_MEM_WR_INV	0x10	/* Memory Write and Invalidate 	*/
#define	CMD_VGA_PALETTE	0x20	/* VGA palette snoop		*/
#define	CMD_PAR_ERR_RSP	0x40	/* Paritry error response      	*/
#define	CMD_WAIT_CYCLE	0x80	/* Wait cycle control          	*/
#define CMD_SERR_EN	0x100	/* SERR enable                 	*/
#define CMD_FAST_BBE	0x200	/* Fast Back-to-Back Enable	*/

/* Status register */

#define STAT_FAST_BBE		0x80	/* Fast Back-to-Back capable	*/
#define	STAT_DATA_PAR		0x100	/* Data parity detected		*/
#define	STAT_DEVSEL_MASK 	0x600	/* CDEVSEL# Timing mask		*/
#define	STAT_DEVSEL_SLOW 	0x400	/* Device select slow       	*/
#define	STAT_DEVSEL_MED	 	0x200	/* Device select medium     	*/
#define	STAT_DEVSEL_FAST 	0x0	/* Device select fast       	*/
#define	STAT_SIG_TARG_ABRT 	0x800	/* Signaled a target abort  	*/
#define	STAT_RCVD_TARG_ABRT	0x1000	/* Received a target abort  	*/
#define	STAT_RCVD_MSTR_ABRT	0x2000	/* Received a master abort  	*/
#define	STAT_SIG_SYS_ERR	0x4000	/* Received a system error  	*/
#define	STAT_DET_PAR_ERR	0x8000	/* Detected a parity error  	*/

/* 
 * Cache Line Size register -- set by the system software (CS) to inform
 * the card what size is supported in the system
 */
#define CACHE_LINE_SIZE(x)	((int)(x << 2)) /* Cache line size in bytes */

/* Header Type register */

#define HDR_MULTI_FCN	0x80	/* If set, device is multi-function */
#define	HDR_LAYOUT_MASK 0x7F	/* Mask to extract 10h-3Fh config hdr type */
#define HDR_LAYOUT_95	0x00	/* PC Card Std 95 config type for 10h-3Fh  */

/* BIST register */

#define BIST_CAPABLE	0x80	/* BIST capable              */
#define BIST_START	0x40	/* Start BIST                */
#define BIST_STAT_MASK  0X0F	/* BIST completion code mask */
#define BIST_PASSED	0x0	/* BIST passed = 0	     */

/* Base Address register */

#define BAR_MEM_MAP	0x0	/* Register maps into Memory space   */
#define BAR_MEM_MAP_32B 0x0	/* Map in 32-bit addr. space         */
#define BAR_MEM_MAP_1M	0x2	/* Map in below 1 Meg. addr. space   */
#define BAR_MEM_MAP_RSVD 0x6	/* Reserved mapping		     */ 
#define BAR_IO_MAP  	0x1	/* Register maps into I/O space      */
#define BAR_PREFETCH	0x8	/* Prefetchable, No read side effects, etc. */
/* Masks for various bit fields */
#define BAR_SPACE_MASK	0x1	/* Mask Mem/IO bit space indicator   */
#define BAR_MEM_MASK	0x6	/* Mask MEM space bits		     */
#define BAR_PREFETCH_MASK 0x8	/* Mask Prefetchable bit	     */
#define MEM_BAR_SIZE_MASK   0xfffffff0  /* Mask for getting memory BAR size */
#define IO_BAR_SIZE_MASK    0xfffffffc	/* Mask for getting I/O BAR size    */ 

#define CB_MEM_SPACE_END	0x4000000 /* 64MB memory space region 	   */
#define CB_IO_SPACE_END		0x1000000 /* 16 MB I/O space region	   */


/* CIS Pointer register */

#define CISPTR_LOC_MASK		0x00000007	/* CIS location mask		*/
#define CISPTR_LOC_CONFIG	0x0		/* CIS located in device-dependent */
                                                /* configuration space		   */
#define CISPTR_LOC_BAR1		0x1		/* CIS located in bar1 space 	*/
#define CISPTR_LOC_BAR2		0x2		/* CIS located in bar2 space	*/
#define CISPTR_LOC_BAR3		0x3		/* CIS located in bar3 space 	*/
#define CISPTR_LOC_BAR4		0x4		/* CIS located in bar4 space	*/
#define CISPTR_LOC_BAR5		0x5		/* CIS located in bar5 space	*/
#define CISPTR_LOC_BAR6		0x6		/* CIS located in bar6 space	*/
#define CISPTR_LOC_EXPROM	0x7		/* CIS located in Exp. ROM space*/
#define CISPTR_ADDR_OFFSET_MASK 0xfffffff8	/* CIS address space offset mask*/
#define CISPTR_ROM_IMAGE_MASK	0xf0000000	/* Exp. ROM Image # (0x0-0xf)	*/

#define CISPTR_ROM_IMAGE_SHIFT 	28 	/* Shift value for getting ROM image #*/

/* Expansion ROM Base Address register */

#define EXP_ROM_BASE_MASK 0xFFFFF800  	/* Upper 21-bits of ROM addr. */

/* 
 * Note: next bit AND Mem. space bit in Command Reg. 
 *       must be set to enable access to expansion ROM.
 */
#define EXP_ROM_ENABLE	  0x1		/* ROM Addr. decode enable    */

#define EXP_ROM_BASE(x)  ((int)(x >> 11)	/* Macro for getting ROM base */

/* Interrupt Pin register */

#define INTR_PIN_INTA	0x01	/* Device using INTA intr pin */
#define	INTR_PIN_INTB	0x02	/* Device using INTB intr pin */
#define	INTR_PIN_INTC	0x03	/* Device using INTC intr pin */
#define	INTR_PIN_INTD	0x04	/* Device using INTD intr pin */

/********************************/
/* CardBus Expansion ROM Header	*/
/********************************/
/*
 * CardBus Expansion ROM contents
 *
 * ROMs can contain multiple images (to support various architectures).
 * Each image has it's own header.
 */
struct cb_rom_exp_header {
	u_short	rom_sig;	/* Must contain CB_ROM_SIGNATURE = AA55	*/
	u_char	rsvd[22];	/* 2H -> 17H reserved			*/
	u_short	cb_rom_data_off; /* Offset to CardBus Data Structure	*/
};

/***************************************************/
/* CardBus PC Card Data Structure in Expansion ROM */
/***************************************************/
struct cb_rom_data {
	u_int	signature;	/* Signature string "PCIR"	   */
	u_int	alloc1;		/* Allocated space		   */
	u_short	vital_data_off;	/* Offset to vital product data    */
	u_short	struct_len;	/* Size of this structure in bytes */
	u_char  struct_rev;	/* Revision of CardBus PC Card Data Structure  */
	u_char  alloc2[3];	/* Allocated space		   */
	u_short image_length;	/* Length of image, units of 512 bytes 	*/
	u_short	code_revision;	/* ROM code revision level            	*/
	u_char	code_type;	/* Type of code in this ROM segment   	*/
	u_char	indicator;	/* Last image in ROM if bit 7 = 1	*/
	u_short	rsvd;		/* Reserved				*/
};

/* Known defines for ROM data structure */
#define CB_ROM_SIGNATURE	0xAA55	/* Value of CardBus ROM sig. bytes */
#define CB_ROM_DATA_OFFSET	0x18	/* CardBus PC Card Data Structure  */
			                /* offset from image start loc.	   */
#define CB_ROM_IMAGE_LENGTH_OFFSET 0x10 /* ROM image length offset from    */
			                /* the beg. of CardBus Data Struct */


#endif 	/* _CARDINFO_H_ */
