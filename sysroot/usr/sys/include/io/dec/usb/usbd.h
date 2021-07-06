/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: usbd.h,v $
 * Revision 1.1.53.3  2005/10/17  15:03:07  Aaron_Biver
 * 	New debug interface.
 * 	[2005/07/27  19:19:23  Aaron_Biver]
 *
 * Revision 1.1.53.2  2004/10/21  19:49:01  Aaron_Biver
 * 	Compiler clean up.
 *
 * Revision 1.1.53.1  2003/03/10  14:18:38  Aaron_Biver
 * 	Add hub switch so hub routines can be called
 * 	without direct knowledge of usb_hub symbols.
 * 	[2003/02/25  18:01:31  Aaron_Biver]
 * 	Add macros to determine device language.
 * 	Add queue links to USBD_BUS.
 * 	Make USB_[UN]LOCK smarter so it doesn't lower spl.
 * 	Add usbd thread flag bit to signify the usbd
 * 	thread's end-of-life.
 * 	[2003/02/21  14:55:16  Aaron_Biver]
 * 	Add new device flag bits to avoid timing errors
 * 	for some faulty host controllers.
 * 	[2003/02/07  16:15:16  Aaron_Biver]
 * 	Add event to USBD_BUS.
 * 	[2003/01/28  23:47:07  Aaron_Biver]
 *
 * Revision 1.1.40.3  2002/07/17  01:19:50  Aaron_Biver
 * 	Add LIST_ENTRY queue-walking macros.
 *
 * Revision 1.1.40.2  2002/05/31  18:53:48  Aaron_Biver
 * 	Add USBD_POISON_PATTERN.
 * 	Make the busy linked list in USBD_REQUEST a standard request
 * 	feature (not a debug feature).
 *
 * Revision 1.1.40.1  2002/01/07  16:41:48  Aaron_Biver
 * 	Add an error count field to USBD_DEVICE.  This helps us
 * 	know when devices are going out of control, and lets us
 * 	put a stop to it.
 *
 * Revision 1.1.18.5  2000/02/24  14:49:02  Janet_Schank
 * 	Changed complex lock to simple locks.
 * 	Added unique_device_name to USBD_DEVICE.
 * 	Added langid and langid_code_array to
 * 	USBD_DEVICE.  Added bus struct for USBD_HUB.
 * 	Each hub is considered an extension of the
 * 	USB and therefore requires a bus struct.
 *
 * Revision 1.1.18.4  1999/08/03  08:01:07  Janet_Schank
 * 	Added get_request_status() to the usbd_sw struct.
 * 	Added a flags field to the usbd_bus struct to
 * 	signify when the default device address is in use.
 * 	Added a reference count to the usbd_device struct.
 * 	This is mainly used by the hub driver to track
 * 	outstanding requests on a device.  Added
 * 	manufacturer, product, and serial number strings to
 * 	the usbd_device struct to be used in EHM registrations.
 * 	Added status_change_buf to the usbd_hub struct.
 * 	Moved usb_reset_hub_port struct from usbd.c to this
 * 	file.  Added USBD_PIPE_FLAGS_CLEAR_STALL flag to
 * 	usbd_pipe struct.  Added USB_INC/DEC_REF() macros.
 * 	[1999/07/30  18:39:43  Janet_Schank]
 *
 * Revision 1.1.18.3  1999/05/06  18:06:28  James_Woodward
 * 	steel bl23 pass 3 merge
 * 	[1999/05/05  20:35:43  James_Woodward]
 * 
 * Revision 1.1.18.2  1999/04/05  11:40:52  Renny_Shen
 * 	Header file cleanup
 * 	[1999/04/01  22:10:58  Renny_Shen]
 * 
 * Revision 1.1.4.4  1999/03/26  13:03:04  Janet_Schank
 * 	Added config_entries field to USBD_DESCRIPTOR_HEADER.
 * 	[1999/03/24  19:22:31  Janet_Schank]
 * 
 * Revision 1.1.4.3  1998/11/25  23:18:11  Janet_Schank
 * 	Added DEVICE_CONNECT_INPROGRESS define to allow for
 * 	100ms delay after device is first connected.
 * 	Moved USBD_HANDLE_TYPE back to this file.
 * 	Added alternate interface support.
 * 	[1998/11/19  17:50:51  Janet_Schank]
 * 
 * Revision 1.1.4.2  1998/07/16  14:20:46  Janet_Schank
 * 	Initial submit to steel
 * 	[1998/07/16  12:31:20  Janet_Schank]
 * 
 * Revision 1.1.2.3  1998/06/12  17:49:42  Janet_Schank
 * 	Made changes needed for several bug fixes.
 * 	[1998/06/11  18:04:51  Janet_Schank]
 * 
 * Revision 1.1.2.2  1998/04/27  21:29:20  Janet_Schank
 * 	Created this file
 * 	[1998/04/23  15:43:11  Janet_Schank]
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: usbd.h,v $ $Revision: 1.1.53.3 $ (DEC) $Date: 2005/10/17 15:03:07 $
 */
#ifndef _USBD_H_
#define _USBD_H_

#include <kern/lock.h>
#include <sys/malloc.h>
#include <io/common/devdriver.h>
#include <io/dec/usb/usb.h>
#include <io/dec/usb/usbdi.h>

/*
 * This file contains structures and defines used by the USBD, HCI, and HUB
 * modules of the Universal Serial Bus Driver for DIGITAL UNIX.
 * 
 * This file will not be available as source.
 */

/*
 * Forward declarations of structure types
 */
struct usbd_bus;
struct usbd_device;
struct usbd_hub;
union usbd_device_union;
struct usb_reset_hub_port;


/*
 * Allows identificaton of USBDI Handles
 */
typedef enum usbd_handle_type {
    USBD_UNINITIALIZED_HANDLE_TYPE,
    USBD_BUS_HANDLE_TYPE,
    USBD_DEVICE_HANDLE_TYPE,
    USBD_INTERFACE_HANDLE_TYPE,
    USBD_PIPE_HANDLE_TYPE,
    USBD_REQUEST_HANDLE_TYPE,
    USBD_ENDPOINT_HANDLE_TYPE,
    USBD_HUB_HANDLE_TYPE,
    USBD_FUNCTION_HANDLE_TYPE,
    USBD_DEBUG_BLOCK_TYPE
} USBD_HANDLE_TYPE;

/*
 * Doubly linked list
 */
typedef struct list_entry {
    struct list_entry *flink;
    struct list_entry *blink;
} LIST_ENTRY;

/*
 * Generic array descriptor.
 */
typedef struct usbd_array_descriptor {
    int sizeof_struct;
    void **array;
    LIST_ENTRY available;
    LIST_ENTRY used;
    int available_count;
    int used_count;
    int increment_count;
    simple_lock_data_t lock;
} USBD_ARRAY_DESCRIPTOR;

/*
 * usbd_descriptor_header must be included first
 * in all structures which use the usbd_array_descriptor
 * above.
 */
typedef struct usbd_descriptor_header {
    LIST_ENTRY l;
    struct usbd_array_descriptor *array_desc;
    U32 index;
    U32 flags;
#define USBD_DESC_AVAILABLE 0x0
#define USBD_DESC_USED      0x1
    int contig_entries;     /* Descriptor data is allocated in chunks.  How
			     * many entries were allocated in this entries
			     * chunk?
			     */
} USBD_DESCRIPTOR_HEADER;


/*
 * struct usbd_sw - defines the interface between the USBD and the HCI
 */
struct usbd_sw {
    void (*enable_option)();    /* Func for enabling option interrupts  */
    void (*disable_option)();   /* Func for disabling option interrupts */

#ifdef notdef
    io_handle_t sparse_io_base; /* io_handle for sparse io base address */
    io_handle_t sparse_mem_base;/* io_handle for sparse memory base address */
    io_handle_t dense_mem_base; /* io_handle for dense memory base address  */
#endif
    vm_offset_t (*busphys_to_iohandle)(); /* Fnc to return io handle    */

    int (*adpt_config)();       /* bus-adapter config routine           */
    int (*confl1)();            /* adapter-specific confl1 routine      */
    int (*confl2)();            /* adapter-specific confl2 routine      */

    int (*request_resource)();  /* Request I/O resource routine         */
    int (*release_resource)();  /* Release I/O resource routine         */

    ihandler_id_t (*handler_add)(); /* Function for installing an ISR   */
    int (*handler_enable)();    /* Function for enabling an interrupt   */
    int (*handler_disable)();   /* Function for disabling an interrupt  */
    int (*handler_del)();       /* Function for removing an ISR         */
    dma_map_info_t (*dma_get_maps)();   /* Function to get dma windows info */

    USBD_STATUS (*resume_endpoint)(); /* Resume endpoint after an error */
    USBD_STATUS (*start_endpoint)(); /* Start endpoint (after stop_endpoint)*/
    USBD_STATUS (*stop_endpoint)();  /* Stop an endpoint */

    /* Get the state of the endpoint */
    USBD_STATUS (*get_endpoint_state)();

    /* Get the number of bytes remaining on an outstanding request */
    USBD_STATUS (*get_request_status)();

    USBD_STATUS (*abort_request)();  /* Abort a request */
    USBD_STATUS (*abort_pipe)();     /* Abort all requests queued to a pipe */
    USBD_STATUS (*clear_stall)();    /* Clear a stall condition */
    USBD_STATUS (*close_endpoint)(); /* Close an endpoint, remove it from
                                      * the schedule */

    USBD_STATUS (*queue_to_interrupt_endpoint)();
    USBD_STATUS (*queue_to_bulk_endpoint)();
    USBD_STATUS (*queue_to_control_endpoint)();
    USBD_STATUS (*queue_to_isochronous_endpoint)();
};

/*
 * Defines the interface between the USBD and the USB hub
 */
struct usb_hub_sw {
    int version;
#define USB_HUB_SW_VERSION_1 1
    int		(*hub_init)(struct usbd_bus *);
    USBD_STATUS	(*hub_port_feature)(struct usbd_hub *, U16, U8, U8);
    USBD_STATUS (*hub_disable_device)(struct usbd_device *);
    void	(*hub_deconfig_device)(union usbd_device_union *);
    void	(*hub_thread_port_reset)(struct usb_reset_hub_port *);
};


/*
 * Callback queue struct
 */
struct usbd_callback_queue {
    struct usbd_super_request *flink;
    struct usbd_super_request *blink;
    int flags;
    int count;
};

/*
 * struct usbd_bus - One for each USB bus
 */
typedef struct usbd_bus {
    LIST_ENTRY q;

    USBD_HANDLE_TYPE struct_type; /* USBD_BUS_HANDLE_TYPE */

    /*
     * Lock for everything in this structure including the callback
     * thread and the root hub thread.
     */
    simple_lock_data_t lock;

    /*
     * Host Controller Interface softc struct
     */
    void *hci_sc;

    /*
     * Flags associated with this USB.
     */
    int flags;
#define USBD_BUS_DEFAULT_DEVICE_INUSE 1

    /*
     * Callback thread fields
     */
    LIST_ENTRY callback_thread_queue;
    int callback_thread_state;
#define USBD_THREAD_IDLE	0x0000
#define USBD_THREAD_SCHED	0x0001
#define USBD_THREAD_ACTIVE	0x0002
#define USBD_THREAD_TERMINATED	0x8000
    int callback_thread_count;
    thread_t callback_thread;
    event_t callback_thread_event;

    /*
     * Roothub softc
     */
    struct usbd_hub *root_hub;

    /*
     * Hub thread pointers
     */
    LIST_ENTRY hub_thread_queue;
    int hub_thread_state;	/* See defs above for callback_thread_state */
    thread_t hub_thread;

    /*
     * Connected USB devices are allocated a USBD_DEVICE structure
     * (this includes the root hub).  This structure contains the USB address
     * which will be assigned to the device.  This address is also the
     * index into the "device_array" (below) for that structure.  All
     * structures  which have been assigned to a device will be included
     * in the "used" list of the device_array.  All available usbd_device
     * structs will be in the "available" list.  See USBD_ARRAY_DESCRIPTOR
     * in usbd.h
     */
    struct usbd_array_descriptor device_array;

    io_handle_t csr;	/* Address for the HC register base (BAR) */
    struct bus *bus;	/* Bus struct assigned to the root hub */
    int adpnum;		/* Unique bus number */

    /*
     * Store the bus switch table so others may access
     * hub routines.
     */
     struct usb_hub_sw *hub_sw;

} USBD_BUS;

/*
 * The usbd_device structure.  There is one of these for each USB
 * device on the bus.  The usbd_device structure is contained by the
 * usbd_hub struct and the usbd_function struct found below.
 */
typedef struct usbd_device {
    /* Used by the USBD_ARRAY_DESCRIPTOR */
    USBD_DESCRIPTOR_HEADER desc_header;
    USBD_HANDLE_TYPE struct_type; /* USBD_DEVICE_HANDLE_TYPE */

    /*
     * Lock for this structure
     */
    simple_lock_data_t lock;

    U32 device_state;
    U32 next_device_state;
    U8 port_number; /* Upstream port number device is connected to */
    U8 speed;       /* Device speed, zero for full speed, 1 for low speed */
    U8 tier_level;  /* The root hub is at tier zero */
    U8 usb_address; /* USB address of the device, once it has been addressed */
    int ref_count;  /* Reference count for this structure */
    int flags;
#define DEVICE_CONNECT_INPROGRESS  0x00000001 /* Set during 100ms delay after
					       * a connect is detected.
					       */
#define DEVICE_DECONFIG_INPROGRESS		0x00000002
#define DEVICE_READ_DEVICE_DESC1_PENDING	0x00000004
#define DEVICE_READ_DEVICE_DESC1_COMPLETE	0x00000008
#define DEVICE_IS_CONNECTED        0x00000010 /* The device is connected to the bus */
#define DEVICE_NOT_OHCI_COMPLIANT  0x00000080
#define DEVICE_CONFIG_DEVICE       0x00000100 /* Load one driver per device */
#define DEVICE_CONFIG_INTERFACE    0x00000200 /* Load one driver per inter */
    struct usbd_pipe *default_pipe; /* Default pipe for this device */
    struct usbd_bus *usb_bus;       /* Bus this device is connected to */
    struct usbd_hub *upstream_hub;  /* Hub this device is connected to, NULL if
				     * this usbd_device is for the root hub */

    LIST_ENTRY default_pipe_requests; /* Requests queued to the default pipe */

    /*
     * Device driver configuration information.  The following
     * three fields are only used if configuration is per device
     * and not on an interface basis.  Each interface will be 
     * configured using the device_config routine.
     */
    int (*device_config)();
    int (*device_deconfig)();
    char device_driver_name[CFG_ATTR_NAME_SZ];

    /*
     * Hardware manager related fields.
     */
#define USBD_DEVICE_NAME_SZ 512
    char *unique_device_name;

    /*
     * The device descriptor for this device
     */
    const struct usb_device_descriptor device_desc; 

    /*
     * Array of configuration descriptors
     */
    const struct usb_configuration_descriptor **config_desc_array;
    int config_desc_count; /* # of config descriptors */

    /*
     * Pointer to configuration descriptor which the device
     * is currently using.  This may be set before the device
     * driver performs a "set_configuration."
     */
    const struct usb_configuration_descriptor *active_config_desc;

    /*
     * Array of usbd_interface structures.  One for each
     * interface supported by the device.  This includes all
     * default interfaces (AlternateSetting is zero) and all
     * alternate interfaces.
     */
    struct usbd_interface *interface_array;

    /*
     * Array of default usbd_interface structs.  default_interface_count
     * is the number of interfaces with an AlternateSetting of zero.
     */
    struct usbd_interface **default_interface_array;
    int default_interface_count;

    /*
     * Array of usbd_endpoint structures. One for each endoint
     * supported by the device.
     */
    struct usbd_endpoint *endpoint_array;

    /*
     * Number of interface descriptors supplied by the device.  This
     * is also the total number of interfaces.
     */
    int interface_desc_count;

    /*
     * Number of endpoint descriptors supplied by the device.  This
     * is also the total number of endpoints.
     */
    int endpoint_desc_count;

    /*
     * Device's current configuration value.
     */
    U16 config_value;

    /*
     * Strings returned by the device.
     */
    U16 langid;
#define USBD_UNICODE_ENGLISH_US  0x0409
#define USBD_UNICODE_FAMILY_MASK 0x00ff
#define USBD_UNICODE_ENGLISH     0x0009

#define USBD_UNICODE_IS_ENGLISH_VARIANT(lang_id) \
    (((lang_id) & USBD_UNICODE_FAMILY_MASK) == USBD_UNICODE_ENGLISH)

#define USBD_GET_STRING(lang_id, string)			\
    ((char *)((string) && (string)[0]?				\
	      (USBD_UNICODE_IS_ENGLISH_VARIANT(lang_id) ?	\
	       (char *)&(string)[0] :				\
	       (char *)&(string)[2]) :				\
	      "<null>"))

    int num_lang_ids;
    struct usb_string_descriptor *langid_code_array;
    struct usb_string_descriptor *manufacturer_string;
    struct usb_string_descriptor *product_string;
    struct usb_string_descriptor *serial_number_string;
#define USBD_DEFAULT_STRING_DESC_LN 32

    U32 failed_config_tries;
#define USBD_MAX_FAILED_CONFIG_RETRIES 3

    U32 failed_deconfig_tries;
#define USBD_MAX_FAILED_DECONFIG_RETRIES 3

    char *path;

} USBD_DEVICE;

/*
 * struct usbd_hub - One of these is assigned to each hub including the
 * root hub.
 *
 * Note that Hubs have two locks, one within the USBD_DEVICE and one
 * within the USBD_HUB. USBD_HUB lock is only used to lock the
 * "down_stream_devices."
 */
typedef struct usbd_hub {
    USBD_DEVICE device;  /* usbd_device struct above */
    USBD_HANDLE_TYPE struct_type; /* USBD_HUB_HANDLE_TYPE */

    /*
     * Lock for this structure.
     */
    simple_lock_data_t lock;

    struct bus *bus;			/* "Bus" struct associated with
					 * this hub.
					 */
    struct usb_hub_descriptor hub_desc; /* The USB hub descriptor */
    U8 status_change_endpoint;	       /* Endpoint number of the hub's
					* status change endpoint
					*/
    USBD_PIPE_HANDLE status_change_pipe; /* Handle to the Hub's status
					  * change pipe (see USB spec)
					  */
    LIST_ENTRY status_change_requests; /* List of requests outstanding 
					* to the status change pipe
					*/
    int number_of_ports;               /* Number of ports on this hub.  This
					* value is taken from the hub
					* descriptor 
					*/
    char *status_change_buf;	       /* Buffer used for status change pipe */
    U8 status_change_buf_sz;           /* Size of the buffer */

    U8 port_status[255];	       /* Port status (see USB spec) for
					* each port.  JANET - allocate this
					* for the supported ports, get rid
					* of the "255"
					*/
#define USBD_HUB_PORT_NEED_POWER     0x01
    int flags;				/* Hub related flags */
#define USBD_HUB_NEED_REQUEST_STATUS 0x01
    int port_power_count;		/* Count of number of ports with an
					 * outstanding "power port" request.
					 * Used during hub initialization
					 */
    /* 
     * Array of pointers to usb_hub_softc, usb_function_softc, or NULL
     * if nothing is connected to that port.
     */
    union usbd_device_union **down_stream_devices;

} USBD_HUB;

/*
 * usbd_function - One for all devices which aren't hubs
 */
typedef struct usbd_function {
    USBD_DEVICE device;
    USBD_HANDLE_TYPE struct_type; /* USBD_FUNCTION_HANDLE_TYPE */

    /*
     * This structure is locked via the lock in USBD_DEVICE
     */

} USBD_FUNCTION;

/*
 * USBD device union.  A device is a hub or a function.
 */
typedef union usbd_device_union {
    USBD_FUNCTION function;
    USBD_HUB hub;
} USBD_DEVICE_UNION;

/*
 * Used to reset a port after being deconfigured.
 */
struct usb_reset_hub_port {
  USBD_HUB *hub;
  int port;
};

/*
 * struct usbd_interface - One for each interface supported 
 * by the device
 */
typedef struct usbd_interface {
    USBD_HANDLE_TYPE struct_type;  /* USBD_INTERFACE_HANDLE_TYPE */
    int flags; /* Future */
    int state; /* USBD_INTERFACE_ACTIVE, USBD_INTERFACE_STALLED, and
		* USBD_INTERFACE_IDLE defined in usbdi.h */
#define USBD_INTERFACE_CONFIG  0x8000 /* Set when the "device_config" routine
				       * routines TRUE when the interface
				       * has been configured.
				       */
#define USBD_INTERFACE_DECONFIG_INPROG		0x0100
#define USBD_INTERFACE_DECONFIG_COMPLETE	0x0200

    /* Associated device header */
    struct usbd_device *device;

    /* Not used if configuration is per device */
    /* Interface configuration routine */
    int (*interface_config)();
    int (*interface_deconfig)();
    char interface_driver_name[CFG_ATTR_NAME_SZ];

    /*
     * Alternate interface info.  The USBD_INTERFACE struct for the
     * default interface will have the live active_interface value and
     * will also contain an accurate value for interface_count.
     * The active_interface value for alternate interfaces is
     * undefined.  Alternate interfaces may access the default interface
     * via the default_interface pointer.
     */
    struct usbd_interface *default_interface;
    struct usbd_interface *interface_array;
    int interface_count;
    int active_interface; /* AlternateSetting from active interface desc */

    /* Interface descriptor */
    const struct usb_interface_descriptor *interface_desc;

    /* Endpoint(s) associated with this interface */
    struct usbd_endpoint **endpoint_array;
    int endpoint_count;

    /* Field reserved for use by the interface driver */
    USBD_PRIVATE_HANDLE private_handle;

    struct controller *ctlr; /* Controller structure associated
			      * with this interface.  Unused for
			      * hubs.
			      */

    /*
     * Lock for the interface and for all associated usbd_endpoint's
     */
    simple_lock_data_t lock;

} USBD_INTERFACE;

/*
 * struct usbd_pipe - Pipes are allocated dynamically when the
 * interface driver needs to communicate with an endpoint.  A pipe
 * connects the interface to the endpoint.
 */
typedef struct usbd_pipe {
    USBD_HANDLE_TYPE struct_type; /* USBD_PIPE_HANDLE_TYPE */
    U16 usb_address      :7,  /* USB address of the device */
        endpoint_number  :4,  /* From the endpoint's descriptor */
        direction        :2,  /* From the endpoint's descriptor */
        speed            :1,  /* From the endpoint's descriptor */
        sKip             :1,  /* From the endpoint's descriptor */
        Format           :1;  /* From the endpoint's descriptor */

    /*
     * Maximum data transfer size for this pipe.  From the endpoint
     * descriptor
     */
    U16 MaximumPacketSize:11,
                         : 5;
    U32 flags; /* Also see usbd.h */
#define USBD_PIPE_FLAGS_CLEAR_STALL	0x10

    U32 ref_count;  /* Reference count for this pipe */
    U32 open_count; /* Open count, incremented by usbd_open_pipe() */
    U32 state;      /* USBD_PIPE_ACTIVE/STALLED/IDLE */

    struct usbd_bus *usb_bus;       /* Pointer to USBD_BUS */
    struct usbd_device *device;	    /* Pointer to USBD_DEVICE */
    struct usbd_endpoint *endpoint; /* Pointer to the USB_ENDPOINT */

    /* Endpoint type: Isochronous, Interrupt, Control, Bulk */
    U8 type;

    /*
     * OHCI specific data - JANET - Get this out of here, make its own
     * structure and create a union
     */

    /* HCI specific endpoint descriptor which is scheduled. */
    void *ED;

    /* This is the requested polling rate for an interrupt endpoint,
     * the actual rate used is indicated by ListIndex.
     */
    U8 Rate;

    /* For isochronous or interrupt endpoints, this value represents the
     * amount of bandwidth which is required for the endpoint when it's
     * opened.  For control or bulk endpoints, this value represents the
     * maximum packet size to be transferred to or from the endpoint in any
     * one packet.
     */
    U16 Bandwidth;

    /*
     * Lock for this structure
     */
    simple_lock_data_t lock;

} USBD_PIPE;

/*
 * struct usbd_endpoint - One for each endpoint.
 * Modify this structure only if its associated interface
 * is locked.
 */
typedef struct usbd_endpoint {
    USBD_HANDLE_TYPE struct_type; /* USBD_ENDPOINT_HANDLE_TYPE */

    /* Associated device header */
    struct usbd_device *device;

    /* Associated interface softc */
    USBD_INTERFACE *interface;

    /* Associated endpoint descriptor */
    const struct usb_endpoint_descriptor *endpoint_desc;
    U8 endpoint_number;  /* Set from the endpoint_desc */

    /* Handle to the opened pipe, NULL if pipe isn't opened */
    struct usbd_pipe *pipe;

} USBD_ENDPOINT;

/*
 * struct usbd_request - Request structure used to communicate between
 * the Interface drivers/USBD/HCI
 *
 * This structure is contained in the usbd_super_request below.
 */
typedef struct usbd_request {

    USBD_HANDLE_TYPE struct_type; /* USBD_REQUEST_HANDLE_TYPE */

    /*
     * Chained request is used to chain requests which can't be put
     * on the ED all at once.  When a request completes, just before
     * the callback, the chained_request field will be checked.  If
     * this value in not NULL the chained_request will be started
     * just before the callback.
     */
    struct usbd_request *chained_request;

    /* Endpoint handle */
    USBD_PIPE *pipe;

    /* Associated class driver's private handle */
    USBD_PRIVATE_HANDLE private_handle;

    /* Number of times this request has been retried by usbd_retry_request() */
    U8 retry_count;

    /* Saved buffer length for retries */
    U32 start_buflen;

    /* Pointer to data to be transferred */
    char *Buffer;
    sglist_t buffer_sg;

    /* Length of data buffer in bytes */
    U32 BufferLength;

    /* Maximum allowable delay from completion to completion
     * notification to USBD.
     */
    U32 MaxIntDelay;

    /* Data for setup packet (control endpoints only) */
    struct usb_device_request device_request;
    sglist_t device_request_sg;

    /* Callback function to the interface driver */
    void (*usbd_callback)();

    /* 
     * Flags may be USBD_XFER_SETUP, USBD_XFER_OUT, USBD_XFER_IN,
     * USBD_SHORT_XFER_OK, USBD_REQUEST_WAIT (defined in usbdi.h)
     */
    U32 flags;
#define USBD_XFER_MASK			0x003
#define USBD_SETUP_HAS_BEEN_DONE	0x010
#define USBD_STATUS_HAS_BEEN_DONE	0x020
#define USBD_DATA_HAS_BEEN_DONE		0x040
#define USBD_NON_OHCI_COMPLIANT		0x080
#define USBD_CLEAR_STALL		0x100

    /* Completion status from HCD to USBD */
    U32 status;
#define USBD_CALLBACK_COMPLETE	0x80000000

} USBD_REQUEST;

/*
 * If this structure is changed, be sure to change the access macros
 * below.
 */
struct usbd_super_request {
    
    LIST_ENTRY USBDlist;	/* Used by the USBD */
    LIST_ENTRY HCDlist;		/* Used by the HCD */
    USBD_REQUEST request;	/* The request structure which class drivers
				 * work with.
				 */

    /*
     * Functional queue for tracing the request during driver debug.
     */
    LIST_ENTRY busy_list;	/* Used by the USBD to track busy requests */
};

/*
 * Hub request wrapper
 */
typedef struct hub_request {
    LIST_ENTRY l;
    USBD_BUS *usb_bus;
    USBD_REQUEST_HANDLE request_handle;
    void *argument;
    void (*callback)();
    U32 flags;
#define HUB_REQUEST_PENDING	0x0001
#define HUB_REQUEST_WAKEUP_DONE	0x0002
#define HUB_REQUEST_SLEEPING    0x0004
} HUB_REQUEST;

/*
 * Hub thread entry.
 */
struct hub_thread_entry {
    LIST_ENTRY l;
    USBD_BUS *usb;
    U64 argument;
    void (*callback)();
};

#define USB_INC_REF(p) (p)->ref_count++
#ifdef USB_DEBUG
#define USB_DEC_REF(p); { \
     USBD_ASSERT((p)->ref_count != 0); \
     (p)->ref_count--; \
}
#else
#define USB_DEC_REF(p) (p)->ref_count--
#endif

#define USB_REQUEST2SUPER(usbrequest) \
((struct usbd_super_request *)(((char *)(usbrequest)) - (sizeof(LIST_ENTRY) * 2)))

#define USB_REQUEST2HCDlist(usbrequest) \
(&(((struct usbd_super_request *)(((char *)(usbrequest)) - (sizeof(LIST_ENTRY) * 2)))->HCDlist))

#define InsertTailList(list, entry) \
    insque((void *)(entry), (void *)(list)->blink)
#define RemoveListEntry(entry) remque((void *)(entry))
#define IsListEmpty(list) ((list)->flink == (list)->blink ? 1 : 0)

/*
 * Access to the private area of "struct bus"
 */
#define usb_ptr private[4]

#define USB_LOCK_INIT(lk, info); {usimple_lock_setup(&(lk), info);}
#define USB_LOCK_DEINIT(lk) { usimple_lock_terminate(&(lk)); }
#define USB_LOCK(lk, s); \
{                        \
    s = getspl();        \
    if (s < SPLBIO)      \
        (s) = splbio();  \
    usimple_lock(&(lk)); \
}
#define USB_UNLOCK(lk, s); \
{                          \
    usimple_unlock(&(lk)); \
    if (s < SPLBIO)        \
        splx(s);           \
}

#define USB_IS_LIST_EMPTY(list) \
    (((LIST_ENTRY *)list)->flink == (LIST_ENTRY *)(list) ? TRUE : FALSE)
#define USB_LIST_INIT(list) \
    ((LIST_ENTRY *)list)->flink = ((LIST_ENTRY *)list)->blink = (LIST_ENTRY *)list;
#define USB_LIST_INSERT(entry, where) insque((void *)(entry), (void *)(where))
#define USB_LIST_REMOVE(entry) remque((void *)(entry))

#define USB_LIST_FIRST(q) (((LIST_ENTRY *)(q))->flink)
#define USB_LIST_NEXT(q) (((LIST_ENTRY *)(q))->flink)
#define USB_LIST_END(q, qe) (((LIST_ENTRY *)(q)) == ((LIST_ENTRY *)(qe)))

#define USBD_LIST_FIND(qhead, element, status) \
{                                         \
    LIST_ENTRY *_curr;                    \
    status = FALSE;                       \
    for (_curr = USB_LIST_FIRST(qhead);   \
	 !USB_LIST_END(_curr, qhead);     \
	 _curr =  USB_LIST_NEXT(_curr)) { \
        if (_curr == (LIST_ENTRY *)element) { \
	    status = TRUE;                \
            break;                        \
	}                                 \
    }                                     \
}

#define USBD_POISON_ALLOC 0xAAAAAAAAAAAAAAAA
#define USBD_POISON_FREE  0xDDDDDDDDDDDDDDDD

extern int cold;
#define USB_M_WAIT_FLAGS ((AT_INTR_LVL() || SLOCK_COUNT) ? (M_NOWAIT) : (M_WAITOK))

#endif /* _USBD_H_ */
