/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: usb_debug.h,v $
 * Revision 1.1.38.1  2005/10/17  15:02:59  Aaron_Biver
 * 	New debug interface.
 *
 * Revision 1.1.24.2  2002/05/31  18:53:41  Aaron_Biver
 * 	Add usbd_status_strings[] extern.
 * 	[2002/05/16  00:28:31  Aaron_Biver]
 *
 * 	CHange debug printfs to be printfs instead of dprintfs.
 * 	[2002/04/26  20:49:10  Aaron_Biver]
 *
 * Revision 1.1.24.1  2001/10/31  22:59:53  Aaron_Biver
 * 	Change USB_DPRINT to use a sysconfig-tunable.
 *
 * Revision 1.1.14.3  2000/02/24  14:48:51  Janet_Schank
 * 	Changed USB_TRACE_DRIVER to use USB_LOCK() macro.
 *
 * Revision 1.1.14.2  1999/08/03  08:00:53  Janet_Schank
 * 	Added USB_TRACE_DRIVER().
 * 	[1999/07/30  18:39:22  Janet_Schank]
 *
 * Revision 1.1.6.2  1998/07/16  14:20:14  Janet_Schank
 * 	Initial submit to steel
 * 	[1998/07/16  12:28:22  Janet_Schank]
 * 
 * Revision 1.1.2.2  1998/04/27  21:28:48  Janet_Schank
 * 	Created this file
 * 	[1998/04/23  15:41:51  Janet_Schank]
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: usb_debug.h,v $ $Revision: 1.1.38.1 $ (DEC) $Date: 2005/10/17 15:02:59 $
 */

#include <io/dec/usb/usbd.h>
#include <mach/machine/vm_param.h> /* For PAGE_SIZE */

#ifndef _USB_DEBUG_H
#define _USB_DEBUG_H

extern char *usbd_status_strings[];
extern char *usbd_pipe_direction_strings[];


/* Debug routine */
extern void usbd_log(unsigned long, char *, void *, char *, ... );

extern u_int _usb_debug_flag;
extern u_int _usb_debug_print;

/* Severity */
#define USB_DEBUG_INFO		0x00000001
#define USB_DEBUG_WARN		0x00000002
#define USB_DEBUG_ERROR 	0x00000004
#define USB_DEBUG_SEVER_MASK 	0x0000000F

/* Category/Subsystem */
#define USB_DEBUG_THREAD	0x00010000
#define USB_DEBUG_HID		0x00020000
#define USB_DEBUG_HC		0x00040000
#define USB_DEBUG_SUBSYS_MASK   0x0FFF0000

/* Modifier */
#define USB_DEBUG_REQUEST	0x10000000

extern u_int _hid_debug_flag;
#define HID_DEBUG_GENERIC  0x01
#define HID_DEBUG_INTR     0x02

#define usbprintf printf
#define USB_FUNCTION(usb_fn_name) static char *usb_func = "usb_fn_name"
#define USB_DPRINT(...) {						\
    if (_usb_debug_flag & USB_DEBUG_INFO) {				\
        usbd_log(USB_DEBUG_INFO, usb_func, NULL, __VA_ARGS__);		\
    }									\
}


/* 
 * Thread tracing macro 
 */
#define USB_TRACE_THREAD(device, ... )	{				\
    if ((_usb_debug_flag & USB_DEBUG_THREAD) &&				\
	(_usb_debug_flag & USB_DEBUG_INFO))  {				\
        usbd_log(USB_DEBUG_INFO | USB_DEBUG_THREAD,			\
		 usb_func, (device), __VA_ARGS__);			\
    }									\
}
#define USB_WARN_THREAD(device, ... )	{				\
    if ((_usb_debug_flag & USB_DEBUG_THREAD) &&				\
	(_usb_debug_flag & USB_DEBUG_WARN))  {				\
        usbd_log(USB_DEBUG_WARN | USB_DEBUG_THREAD,			\
		 usb_func, (device), __VA_ARGS__);			\
    }									\
}

/* 
 * Device tracing macros 
 */
#define USB_TRACE_DEVICE(device, ... )	{				\
    if (_usb_debug_flag & USB_DEBUG_INFO) {				\
        usbd_log(USB_DEBUG_INFO, usb_func, (USBD_DEVICE *)(device), __VA_ARGS__);	\
    }									\
}
#define USB_WARN_DEVICE(device, ... ) {					\
    if (_usb_debug_flag & USB_DEBUG_WARN) {				\
        usbd_log(USB_DEBUG_WARN, usb_func, (USBD_DEVICE *)(device), __VA_ARGS__);	\
    } 									\
}
#define USB_ERROR_DEVICE(device, ... ) {				\
    if (_usb_debug_flag & USB_DEBUG_ERROR) {				\
        usbd_log(USB_DEBUG_ERROR, usb_func, (USBD_DEVICE *)(device), __VA_ARGS__);	\
    } 									\
}


/* 
 * Request tracing macros 
 */
#define USB_TRACE_REQUEST(request, ...)	{				\
    if ((_usb_debug_flag & USB_DEBUG_INFO)  &&				\
	(_usb_debug_flag & USB_DEBUG_REQUEST)) {			\
        usbd_log(USB_DEBUG_INFO | USB_DEBUG_REQUEST, usb_func,		\
                 (USBD_REQUEST *)(request), __VA_ARGS__);		\
    }									\
}
#define USB_WARN_REQUEST(request, ...)	{				\
    if ((_usb_debug_flag & USB_DEBUG_WARN)  &&				\
	(_usb_debug_flag & USB_DEBUG_REQUEST)) {			\
        usbd_log(USB_DEBUG_WARN | USB_DEBUG_REQUEST, usb_func,		\
                 (USBD_REQUEST *)(request),  __VA_ARGS__);		\
    }									\
}
#define USB_ERROR_REQUEST(request, ...) {				\
    if ((_usb_debug_flag & USB_DEBUG_ERROR) &&				\
	(_usb_debug_flag & USB_DEBUG_REQUEST)) {			\
        usbd_log(USB_DEBUG_ERROR | USB_DEBUG_REQUEST, usb_func,		\
                 (USBD_REQUEST *)(request),  __VA_ARGS__);		\
    }									\
}


/*
 * Driver tracing macros 
 */
#define USB_TRACE_DRIVER(...) {						\
   if (_usb_debug_flag & USB_DEBUG_INFO) {				\
       usbd_log(USB_DEBUG_INFO, usb_func, NULL, __VA_ARGS__);		\
   }									\
}
#define USB_WARN_DRIVER(...) {						\
   if (_usb_debug_flag & USB_DEBUG_WARN) {				\
       usbd_log(USB_DEBUG_WARN, usb_func, NULL, __VA_ARGS__);		\
   }									\
}
#define USB_ERROR_DRIVER(...) {						\
   if (_usb_debug_flag & USB_DEBUG_ERROR) {				\
       usbd_log(USB_DEBUG_ERROR, usb_func, NULL, __VA_ARGS__);		\
   }									\
}






/*
 * Some support data structures and strings for debug.
 */
extern char *port_info_format_string;
extern char *device_flags_format_string;
extern char *device_state_format_string;
extern char *usbd_thread_format_string;

/*
 * A single debug message, indicating current cpu, lbolt, and 
 * debug flags, and a char buffer.
 *
 * Keep this at something like 128 or 256 bytes for now.  
 * This gets us 31 or 63 messages per page, respectively.
 */
struct _usbd_debug_msg_hdr {
    long	time;		/*  8 */
    u_int	cpu;  
    u_int	flags;		/* 16 */
    char	*caller;	/* 24 */
    struct usbd_device *device;	/* 32 */
};
#define USBD_DEBUG_MSG_MAX_LEN 128
#define USBD_DEBUG_MSG_MAX_STRLEN (USBD_DEBUG_MSG_MAX_LEN - sizeof(struct _usbd_debug_msg_hdr)) 

typedef struct _usbd_debug_msg {
    struct _usbd_debug_msg_hdr msg_hdr;
    char string[USBD_DEBUG_MSG_MAX_STRLEN];
} USBD_DEBUG_MSG;


/*
 * A block of debug messages in one chunk of memory.
 * Currently, this size is just under a page.
 */
struct usbd_debug_block_hdr {
    struct usbd_debug_block *flink;
    struct usbd_debug_block *blink;
    USBD_HANDLE_TYPE struct_type; /* USBD_DEBUG_BLOCK_TYPE */
    int sizeof_entries; 
    int num_entries;
    int next_entry;
};

typedef struct usbd_debug_block {
    struct usbd_debug_block_hdr block_hdr;
#define USBD_DEBUG_MSGS_PER_BLOCK ((PAGE_SIZE - sizeof(struct usbd_debug_block_hdr)) / sizeof(struct _usbd_debug_msg)) 
    /*  keep each block size at at page or under */

    USBD_DEBUG_MSG msgs[USBD_DEBUG_MSGS_PER_BLOCK]; 

} USBD_DEBUG_BLOCK;


#endif /* _USB_DEBUG_H */
