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
 * @(#)$RCSfile: pcmcia.h,v $ $Revision: 1.1.28.1 $ (DEC) $Date: 2002/01/24 18:54:36 $
 */

#ifndef _PCMCIA_H_
#define _PCMCIA_H_

#ifndef __cplusplus

#include <io/common/devdriver.h>

/****************************************************************/
/*								*/
/* MODULE NAME: pcmcia.h					*/
/*								*/
/* LOCATION:  /src/kernel/io/dec/pcmcia				*/
/*								*/
/* DESCRIPTION:							*/
/* 	Contains common definitions for the PCMCIA bus adapter,	*/
/*	socket, and card functions.				*/
/*								*/
/* STRUCTURES:							*/
/*	pcmcia_sw	PCMCIA switch table for hardware 	*/
/*			dependent functions			*/
/*								*/
/*	pcmcia_bus_adapt 	PCMCIA adapter specific 	*/
/*				data structure			*/
/****************************************************************/

#include <sys/types.h>
#include <io/common/handler.h>		/* for handler_* decl's */
#include <io/common/devdriver.h>	/* for I/O resource mgmt decl's */


/************************************************************************/
/* Maximum number of sockets per adapter and adapters per system	*/
/*									*/ 
/* Theoretically, the maximum number of PCMCIA adapters can be 255	*/
/* (byte count size) with 16 sockets per adapter.  We will limit 	*/
/* support to 8 adapters with up to 2 sockets each for now.	 	*/
/*									*/
/* IF WE EVER NEED TO INCREASE THESE NUMBERS, change the definitions	*/
/* below.								*/
/************************************************************************/

#ifdef _KERNEL
#define PCMCIA_MAX_ADAPTERS	8
#define PCMCIA_MAX_SOCKETS	(PCMCIA_MAX_ADAPTERS<<1)
#define PCMCIA_MAX_CARD_FUNCS	8	/* max. # of functions in a card */
#endif /* _KERNEL */

/* Common serial line COM port addresses */

#define COM1	0x3f8
#define COM2	0x2f8
#define COM3	0x3e8
#define COM4	0x2e8
#define COM_IOSIZE 8		/* length of I/O block in COM port */

/* window into attribute memory space to read Card Information Structure data */
#define CFSIZE 4096		/* size of buffer to hold CIS data */

/*
 * common defines for PCMCIA routines
 */
#define PCMCIA_SUCCESS	0
#define PCMCIA_FAILURE	1

/****************************************************************/
/* PC Card option data structure which contains information     */
/* on PC Card options that may be installed on a system.	*/
/* The options are listed in /etc/sysconfigtab database.	*/
/****************************************************************/

#define MANUFACT_NAMELEN    31
#define PRODUCT_NAMELEN	    31
#define DRIVER_NAMELEN	    15

#define CALL_HANDLER 0x1		/* call handler flag */


struct pcmcia_option {
    u_char 	manufact_name[MANUFACT_NAMELEN+1];
                                        /* Manufacturer name string 	*/
    u_char	product_name[PRODUCT_NAMELEN+1];
                                        /* Product name string		*/
    u_short	manufact_ID;		/* Manufacturer ID in Manufacture ID tuple */
    u_short	card_revision;		/* Card's revision/part # found in Manufacture ID tuple */
    u_int	func_code;		/* Card function code, found in Function ID tuple */
    u_char	driver_name[DRIVER_NAMELEN+1];
                                        /* Card driver's name		*/
    u_char	loadable_flag;		/* If set, driver is loadable 	*/
    u_char	unload_flag;		/* If set, driver should be unloaded 	*/
                                        /* when the corresponding PC Card is 	*/
                                        /* ejected from the socket.  This field */
                                        /* is valid only for loadable driver	*/
    u_char	intr_handler_flag;	/* Call interrupt handler flag --       */
                                        /*  No longer used			*/
    char	type;			/* Driver type, C = ctlr, 	*/
                                        /* A = Adapter, D = Device	*/  
    int		(*adpt_config)();	/* Adapter config routine to call */
    
    u_char	man_name_mo_flag;	/* Match-on flag for Manufacturer name field */
    u_char	prd_name_mo_flag;	/* Match-on flag for Product name field */
    u_char	mid_mo_flag;		/* Match-on flag for Manufacturer ID field */
    u_char	card_rev_mo_flag;	/* Match-on flag for Card revision field */

    u_char	multi_func_flag;	/* If set to 1, this is a multifunction card */
    u_char	func_num;		/* Card function number, starts with 0  */
};


#ifdef _KERNEL

/*
 * PCMCIA interrupt handler key structure.  Handler add functions
 * done by the PCMCIA adapter code (pcic, pd6729, ti1130) return to
 * the caller a pointer to this structure below
 */

struct pcmcia_intr_key
{
    ihandler_id_t	hid_ptr;
    void *		info_pointer;	/* bus or controller structure */
    u_int		driver_type;	/* driver type, bus adapter or controller */
};
    
/*********************************************************/
/* PCMCIA Switch Table for hardware dependent functions. */
/*********************************************************/

struct	pcmcia_sw {
    void (*enable_option)();	/* Func for enabling option interrupts  */
    void (*disable_option)();	/* Func for disabling option interrupts */

    io_handle_t sparse_io_base; /* io_handle for sparse io base address */ 
    io_handle_t sparse_mem_base;/* io_handle for sparse memory base address */
    io_handle_t dense_mem_base; /* io_handle for dense memory base address  */
    vm_offset_t (*busphys_to_iohandle)(); /* Fnc to return io handle    */

    int	(*adpt_config)();	/* bus-adapter config routine     	*/
    int (*confl1)();		/* adapter-specific confl1 routine	*/
    int (*confl2)();		/* adapter-specific confl2 routine	*/

    int (*request_resource)();	/* Request I/O resource routine		*/
    int (*release_resource)();	/* Release I/O resource routine		*/
    
    ihandler_id_t (*handler_add)(); /* Function for installing an ISR	*/
    int (*handler_enable)();	/* Function for enabling an interrupt	*/
    int (*handler_disable)();	/* Function for disabling an interrupt	*/
    int (*handler_del)();	/* Function for removing an ISR		*/
    dma_map_info_t (*dma_get_maps)();	/* Function to get dma windows info */

    /* Socket Services Function Entry Points starts here */

    int (*setup_io_window)();		/* Set up I/O window */
    int (*setup_mem_window)();		/* Set up memory window */
    int (*disable_io_window)();		/* Disable I/O window */
    int (*disable_mem_window)();	/* Disable memory window */
    int (*reset_socket)();		/* Reset socket */
    int (*setup_socket)();		/* Set up socket */
    int (*enable_scint)();		/* Enable status change interrupt */
    int (*disable_scint)();		/* Disable status change interrupt */
    int (*enable_fnc_irq)();		/* Enable PC Card functional interrupt */
    int (*disable_fnc_irq)();		/* Disable PC Card functional interrupt */
    int (*read_cis)();			/* Read the card's CIS structure */
    int (*map_attribute_memory)();	/* Map the card's attribute memory */
    int (*get_status)();		/* Read status info from socket */
   
};


/********************************************************/
/* PCMCIA adapter specific data structure -- 		*/
/*							*/
/* 	There is one instance of this structure for 	*/
/*	each PCMCIA adapter.				*/
/*	The bus structure will be pointing to this	*/
/*	structure via 'private[4]' field.		*/
/********************************************************/

#define pcmcia_ptr	private[4]

/*
 * Adapter type definitions 
 */
#define R2_ADAPTER		0
#define CARDBUS_ADAPTER 	1

struct local_map_data {

    struct map *io_resource_map;
    struct map *mem_resource_map;
    struct io_mem_list *io_list_head_ptr;
    struct io_mem_list *mem_list_head_ptr;
};


struct pcmcia_bus_adapt {

    struct bus	*bus;			/* bus struct of this adapter */
    int		adpnum;			/* PCMCIA adapter number */
    int		num_sockets;		/* number of sockets in this adapter */
    struct socket_info *socket_list;	/* pointer to sockets connected to this adapter */

    struct local_map_data local_map_ptr;
					/* Structure to hold bus resourse */ 
					/*  pointers */
    io_handle_t io_addr;                /* I/O base address of the ExCR regs */
    io_handle_t io_base;		/* I/O base address of adapter */ 
    io_handle_t mem_base;		/* dense memory space base address */
    io_handle_t pci_config_base;	/* adapter config space base address */
    
    ihandler_id_t     *handler_key;	/* management interrupt handler key */ 
    void *adp_private[8];		/* adapter private data area */
    void *	handler_ptrs;		/* Holds pointer to our handlers */
    int         irq_info;               /* Holds our IRQ information -- 	*/
                                        /*  Bits 15:0 contain a bitmask of 	*/
                                        /*  EISA/ISA interrupts the adapter has */
                                        /*  the ability to drive.  Bits 31:16   */
                                        /*  are reserved for flags 		*/
    int		adapter_type;		/* R2 or CardBus adapter indication */
};

/*
 * Flag definitions relating to socket and management interrupts
 *
 * There are a total of 16 flags, one will be used for indicating
 * level or edge mode on the IRQs.  The flags are used in 
 * irq_info field in pcmcia_bus_adapt structure and in irq_num field
 * in socket_info structure.
 */

#define PCMCIA_IRQ_MODE	0x10000		/* Bit 16 is set if the IRQs will be	*/
                                        /*  level driven and clear if the IRQ	*/
                                        /*  is edge triggered			*/


#endif /* _KERNEL */



/****************************************************************/
/* Socket information structure --				*/
/*								*/
/*	This structure contains information about a socket	*/
/* 	in a PCMCIA adapter.  					*/
/****************************************************************/
struct pcm_callback {
			struct pcm_callback *next;	/* forward pointer */
			int event;
			void (*function)();
			unsigned long argument;
			int callback_seen; /* facilitates generating card detect callbacks */
					/* for cards which are present when callback */
					/* is registered */
			int is_ccm;	/* registered by the ccm */
			int scanning_flag;	/* 1=callback scanned in current scan */
};

#define	EVENT_LIST_SIZE	20

#define socket_info_ptr	conn_priv[0]		/* in controller or bus structure 	*/
#define handler_id	conn_priv[1]		/* in controller or bus structure 	*/
#define card_info_ptr	conn_priv[2]		/* in controller structure, or in bus   */
                                                /* structure, used to pass   		*/
                                                /* info about the card to card driver   */ 


struct socket_info {

    struct socket_info *nxt_socket;	/* ptr. to next socket on this adapter */
    struct pcmcia_bus_adapt *adapt;	/* ptr. to the adapter structure */
    int		socket_pnum;		/* real socket # unique to this adapter */
    int		socket_vnum;		/* virtual socket # unique to the system */
    int		socket_state;		/* current state of the socket		*/

    int		card_in;		/* a card is in the socket flag */
    int		card_data;		/* Card information:
					        16-bit OR CardBus
						5V or 3V */

    int		num_function;		/* number of functions in the current card */
    u_int	mem_window_in_use;	/* Bit mask of socket memory windows (0-5)  	*/
                                        /* currently in use -- for 16-bit card only	*/
    u_int	io_window_in_use;	/* Bit mask of socket I/O windows (0-1) 	*/
                                        /* currently in use -- for 16-bit card only	*/
    int		irq_num;		/* IRQ # being used for current card	*/
                                        /*  bits 15:0 contain the IRQ #,	*/
                                        /*  bits 31:16 are reserved for flags	*/
    int		socket_irq_count;	/* The number of devices sharing a 	*/
                                        /*  specific socket IRQ.  The multi-	*/
                                        /*  function PC Card case is the only	*/
                                        /*  situation where this number will be */
                                        /*  greater than 1 			*/
    int		socket_irq;		/* IRQ # used for socket mgmt interrupts */
    int		mem_size;		/* Size of the memory space used for CIS data */
    u_long	mem_start_addr;		/* Start of ISA memory space used for this card */
                                        /* Used for mapping CIS data space 	        */

    io_handle_t socket_config_base;	/* socket config space base address */
    io_handle_t socket_io_base;		/* socket I/O space base address */
    io_handle_t socket_mem_base;
					/* socket sparse memory base */
					/*  address */



    res_handle_t irq_resource_key;	/* IRQ resource key returned for this card function */

    ihandler_id_t *handler_key;		/* handler key returned for this card -- not needed */
					/* should be deleted for Steel */

    res_handle_t attr_resource_key;	/* Attribute Memory resource key returned for this socket */
    
    u_char	*cis_data;		/* pointer to the CIS data for current card */
    
    struct card_info *function[8];	/* array of pointers to card function struct */

    decl_simple_lock_data(,cis_window_lock)	/* CIS memory window access lock */
    decl_simple_lock_data(,callback_queue_lock)
    decl_simple_lock_data(,event_queue_lock)
    decl_simple_lock_data(,register_lock)
    struct pcm_callback *callback_queue;	/* event callback requests */
    int next_event_to_process;
    int next_event_to_fill;
    int events[EVENT_LIST_SIZE];	/* event_list is a circular list */
					/* an entry is considered empty iff event # is 0. */
					/* EVENT_LIST_SIZE -1 to 0; */
					/* empty when event[next_process]==0 */
					/* full when event[next_fill] != 0 */
    u_int last_read_status;		/* The last read socket status */
					/*  Used by GetStatus() */
    u_long cb_cis_memory;		/* Used for CIS data on CardBus */
    long cb_cis_mem_size;		/* Used for CIS data on CardBus */
    res_handle_t cb_cis_mem_rsrc_key;	/* Used for CIS data on CardBus */
    u_long cb_tuple_chain_offset;	/* Used for CIS data on CardBus */
};

/*
 * CardBus PC Card's Configuration Header structure
 */
struct cardbus_card_config_hdr {
    u_short	cb_alloc1;		/* Allocated space - filler	*/
    u_short	cb_alloc2;		/* Allocated space - filler	*/
    u_short	cb_command;		/* Command			*/
    u_short	cb_status;		/* Status			*/
    u_int	cb_alloc3_4;		/* Allocated space - filler	*/
    u_char	cb_cache_line_size;	/* System cache-size, in 32-bit words */
    u_char	cb_latency_timer;	/* Bus latency timer		*/
    u_char	cb_hdr_type;		/* Defines type for 10h-3Fh 	*/
    u_char	cb_bist;		/* Built in self test 		*/
    u_int	cb_bar1_info;		/* Base Address reg 1 info	*/
    u_int	cb_bar2_info;		/* Base Address reg 2 info	*/
    u_int	cb_bar3_info;		/* Base Address reg 3 info	*/
    u_int	cb_bar4_info;		/* Base Address reg 4 info	*/
    u_int	cb_bar5_info;		/* Base Address reg 5 info	*/
    u_int	cb_bar6_info;		/* Base Address reg 6 info	*/
    u_int	cb_cis_ptr;		/* CIS Pointer			*/
    u_int	cb_rsvd1;		/* Reserved			*/
    u_int	cb_exp_rom_bar_info;   	/* Expansion ROM base addr info	*/
    u_int	cb_rsvd2;		/* Reserved			*/
    u_int	cb_rsvd3;		/* Reserved			*/
    u_char	cb_alloc5;		/* Allocated space - filler	*/
    u_char	cb_intr_pin;		/* Interrupt pin		*/
    u_char	cb_alloc6;		/* Allocated space - filler	*/
    u_char	cb_alloc7;		/* Allocated space - filler	*/
    io_handle_t	cb_bar1;		/* Base Address reg 1		*/
    io_handle_t	cb_bar2;		/* Base Address reg 2		*/
    io_handle_t	cb_bar3;		/* Base Address reg 3		*/
    io_handle_t	cb_bar4;		/* Base Address reg 4		*/
    io_handle_t	cb_bar5;		/* Base Address reg 5		*/
    io_handle_t	cb_bar6;		/* Base Address reg 6		*/
    io_handle_t	cb_exp_rom_bar;   	/* Expansion ROM base address	*/
    
    /* beginning of device dependent space, location 64 through 255 */

    io_handle_t config_base;		/* function's config space base */

};


/*
 * Data structure passed to the PC Card's driver's probe() via 
 * controller->conn_priv[2] field (== card_info_ptr) or
 * to the PC Card's driver's confl1() via
 * bus->conn_priv[2] field (== card_info_ptr)
 */

struct card_info {
    int		socket_vnum;		/* Virtual socket # unique in the system */
    int		irq_num;		/* IRQ # being used for current card	 */
    int		io_length[2];		/* length of the card's I/O port block	 */
    u_long	io_addr[2];		/* start address of I/O port block	 */
    long	com_mem_size[2];	/* size of the Common Memory Space mapped*/
    u_long	com_mem_start_addr[2];	/* start of the Common Memory Space mapped */
    u_long	config_reg_addr;	/* configuration register base address for      */
                                        /* 16-bit card					*/
    int		io_win_num[2];		/* socket I/O window number reserved for I/O block */
    int		mem_win_num[2];		/* socket memory window number reserved for mem block */

    res_handle_t io_resource_key[2];	/* I/O port resource key returned for this card function */

    res_handle_t mem_resource_key[2];	/* Memory resource key returned for this card function */    

    struct cardbus_card_config_hdr *config_hdr;
                                        /* ptr. to the card function's configuration */
                                        /* header if the card is a CardBus card */
    u_int	reg_addr_space_cb;	/* Address space indicator for CardBus card 	*/
                                        /* function's 4 Status registers		*/
    u_int	reg_addr_offset_cb;	/* Address space offset for CardBus card	*/
                                        /* function's 4 Status registers		*/
    u_int	io_bar_map;		/* CardBus card function's I/O space BAR bit map */
    u_int	mem_bar_map;		/* CardBus card function's Memory space BAR bit map */
    long	bar_size[7];		/* CardBus BAR space size allocated */
    u_long	bar_start_addr[7];	/* CardBus BAR space system addr */
    res_handle_t bar_resource_key[7];	/* CardBus BAR resource key returned for this CardBus function */

    caddr_t	bus_ctlr_p;		/* pointer to bus/controller struct associated  */
                                        /* with this card function driver		*/
    u_int	driver_type;		/* Driver type, bus adapter or controller */
    struct pcmcia_option *card_option;	/* ptr. to the card function option struct. */

    int		card_func;		/* function code of current card function */  
    
};

/*
 * Defines for driver_type field 
 */
#define PC_CONTROLLER_TYPE	0x01
#define PC_BUS_ADAPT_TYPE  	0x03

/*
 * DEFINES for socket info structure fields 
 */
#define CARD_IN		0x1		/* card is in the socket */
#define CARD_OUT	0x0		/* socket is empty */

/* 
 * DEFINES for card data in socket info structure
 */
#define R2_CARD		0x1		/* 16-bit PC Card */
#define CARDBUS_CARD	0x2		/* CardBus PC Card */

#define TYPE_5V_CARD	0x10000		/* Card supports 5V */
#define TYPE_3V_CARD	0x20000		/* Card supports 3V */

/* 
 * DEFINES for socket windows in use bit masks 
 */
#define MEM_WIN_0_IN_USE	0x01
#define MEM_WIN_1_IN_USE	0x02
#define MEM_WIN_2_IN_USE	0x04
#define MEM_WIN_3_IN_USE	0x08
#define MEM_WIN_4_IN_USE	0x10
#define MEM_WIN_IN_USE_MASK	0x1f

#define IO_WIN_0_IN_USE		0x01
#define IO_WIN_1_IN_USE		0x02
#define IO_WIN_IN_USE_MASK	0x03

/*
 * DEFINES for return status from get_status call
 */
#define PC_CARD_PRESENT	0x00000001	/* A card is in the socket */
#define PC_CARD_POWER	0x00000002	/* Power is applied to the socket */
#define WRITE_PROTECT	0x00000004	/* The write protect pin is asserted */
#define BVD1_STATUS	0x00000008	/* The state of BVD1 pin is asserted */
#define BVD2_STATUS	0x00000010	/* The state of BVD2 pin is asserted */
#define PC_CARD_READY	0x00000020	/* The READY bit is asserted */
 

/* 
 * DEFINES for generic IRQ #s
 */
#define PCMCIA_IRQ0	0		/* IRQ 0 */
#define PCMCIA_IRQ1	1		/* IRQ 1 */
#define PCMCIA_IRQ2	2		/* IRQ 2 */
#define PCMCIA_IRQ3	3		/* IRQ 3 */
#define PCMCIA_IRQ4	4		/* IRQ 4 */
#define PCMCIA_IRQ5	5		/* IRQ 5 */
#define PCMCIA_IRQ6	6		/* IRQ 6 */
#define PCMCIA_IRQ7	7		/* IRQ 7 */
#define PCMCIA_IRQ8	8		/* IRQ 8 */
#define PCMCIA_IRQ9	9		/* IRQ 9 */
#define PCMCIA_IRQ10	10		/* IRQ 10 */
#define PCMCIA_IRQ11	11		/* IRQ 11 */
#define PCMCIA_IRQ12	12		/* IRQ 12 */
#define PCMCIA_IRQ13	13		/* IRQ 13 */
#define PCMCIA_IRQ14	14		/* IRQ 14 */
#define PCMCIA_IRQ15	15		/* IRQ 15 */


struct pcmcia_function_switch {
	int (*register_event_callback)();
	int (*unregister_event_callback)();
	int (*get_first_tuple)();
	int (*get_next_tuple)();
	int (*get_tuple_data)();
	int (*tuple_parse)();
	int (*map_common_memory_window)();
	int (*read_configuration_register)();
	int (*write_configuration_register)();
	int (*request_common_memory_window)();
	int (*release_common_memory_window)();
	int (*get_status)();
};


/* PC Card event type definition */

#define CARD_REMOVAL_EVENT 1
#define CARD_INSERTION_EVENT 2
#define CARD_READY_EVENT 3
#define CARD_RESET 4		/* A HW reset has occurred on a */
                                /* function of the PC Card      */
#define CARD_BATTERY_DEAD 5	
#define CARD_BATTERY_LOW  6	


/************************************************************************/
/*									*/
/* EVM (Digital UNIX Event Manager) event definitions for PC Card  	*/
/* events								*/
/*									*/
/************************************************************************/
/* 
 * Event names definition
 */
#define _PC_CARD_EVENT_NAME(x) 		_EvmSYSTEM_EVENT_NAME("pc_card") "." x

#define EVENT_CARD_BATTERY_DEAD		_PC_CARD_EVENT_NAME("battery.dead")
#define EVENT_CARD_BATTERY_LOW		_PC_CARD_EVENT_NAME("battery.low")
#define EVENT_CARD_READY		_PC_CARD_EVENT_NAME("ready")
#define EVENT_CARD_INSERT		_PC_CARD_EVENT_NAME("insert")
#define EVENT_CARD_REMOVE		_PC_CARD_EVENT_NAME("remove")
#define EVENT_CARD_RESET		_PC_CARD_EVENT_NAME("reset")

#endif /* __cplusplus */
#endif	/* _PCMCIA_H_ */
