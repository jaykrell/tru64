/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: console.h,v $
 * Revision 1.1.12.1  2004/08/19  20:13:17  Aaron_Biver
 * 	QAR 97550: Add ctb_type_4 members for eco 130.
 * 	[2004/07/21  19:21:51  Aaron_Biver]
 *
 * Revision 1.1.6.1  1999/11/03  22:40:57  Ernie_Petrides
 * 	Fix build warning.
 *
 * Revision 1.1.4.4  1997/07/21  21:06:50  Alex_Malone
 * 	add support for converting between network ctlr and bootsrings
 * 	[1997/07/10  13:55:47  Alex_Malone]
 *
 * Revision 1.1.4.3  1997/02/27  20:18:35  Dave_Gerson
 * 	Added variation to palcode_rev struct.  Changed membership
 * 	names in palcode_rev struct to coincide with those names
 * 	used in firmware_rev struct.
 * 	[1997/02/24  21:22:14  Dave_Gerson]
 * 
 * Revision 1.1.4.2  1997/01/24  16:19:35  Dave_Gerson
 * 	Added structure type declarations for firmware_rev
 * 	and palcode_rev in support of getsysinfo() cases to
 * 	obtain this information.
 * 	[1997/01/23  14:05:47  Dave_Gerson]
 * 
 * Revision 1.1.2.3  1996/02/07  23:08:43  Paul_Grist
 * 	Move ctb type 4 definition and macros here from console.c
 * 	[1996/02/07  23:01:59  Paul_Grist]
 * 
 * Revision 1.1.2.2  1995/06/21  17:46:45  Paul_Grist
 * 	Move consDev defines here from wsdevice.h
 * 	[1995/06/21  17:03:23  Paul_Grist]
 * 
 * 	Created file for kernel console support definitions
 * 	[1995/06/13  01:17:43  Paul_Grist]
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: console.h,v $ $Revision: 1.1.12.1 $ (DEC) $Date: 2004/08/19 20:13:17 $
 */

#ifndef _ARCH_ALPHA_HAL_CONSOLE_H_
#define _ARCH_ALPHA_HAL_CONSOLE_H_


/*
 * CTB type 4 data structure and macros.
 */

/* CTB Type 4 format structure */
struct ctb_type_4 
{
	unsigned long ctb4_type;
	unsigned long ctb4_unit;
	unsigned long ctb4_rsv1;
	unsigned long ctb4_ddilen;
	unsigned long ctb4_ipl;
	unsigned long ctb4_txiv;
	unsigned long ctb4_rxiv;
	unsigned long ctb4_termtype;
	unsigned long ctb4_kbtype;
	unsigned long ctb4_kbtt;
	unsigned long ctb4_kbmt;
	unsigned long ctb4_kbstate;
	unsigned long ctb4_lastkey;
	unsigned long ctb4_usfont;
	unsigned long ctb4_mcsfont;
	unsigned long ctb4_fwidth;
	unsigned long ctb4_fheight;
	unsigned long ctb4_monwidth;
	unsigned long ctb4_monheight;
	unsigned long ctb4_mondensity;
	unsigned long ctb4_nplanes;
	unsigned long ctb4_curswidth;
	unsigned long ctb4_cursheight;
	unsigned long ctb4_nheads;
	unsigned long ctb4_opwin;
	unsigned long ctb4_hdoffset;
	unsigned long ctb4_putchar;
	unsigned long ctb4_iostate;
	unsigned long ctb4_lstate;
	unsigned long ctb4_xinfo;
	unsigned long ctb4_outslotinfo;
	unsigned long ctb4_srvroff;
	unsigned long ctb4_linepar;
	unsigned long ctb4_inslotinfo;
       /* 
	* SRM ECO 130/QAR 97550:
	* When ctb4_inprotocol == 1, ctb4_inslotinfo and
	* ctb4_inslotinfo_ext contain the USB topology path from root
	* hub to input device
	* The least significant byte contains the root hub port,
	* the next most significant byte contains the port at the 
	* level one hub, etc
	*/
	unsigned long ctb4_inslotinfo_ext;

       /*
	* What type of input/output devices are used for
	* this console?  
	*	0 - No protocol specified
	*	1 - USB 
	*/
	unsigned int  ctb4_inprotocol;
	unsigned int  ctb4_outprotocol;

       /*
	* When ctb4_outprotocol == 1, ctb4_outslotinfo and
	* ctb4_outslotinfo_ext contain the USB topology path from root
	* hub to output device.  
	*
	* Note that at this time, there are no supported USB output
	* devices.
	*/
	unsigned long ctb4_outslotinfo_ext;

};

/*
 * ECO 130:
 * Possible values for ctb4_outprotocol in the ctb_type_4 structure 
 */
#define CONS_PROTOCOL_NONE 0
#define CONS_PROTOCOL_USB  1

/*
 * ECO 130
 * Max number of tries to attempt the PROM_CONSOLE_OPEN and
 * PROM_CONSOLE_CLOSE callbacks, just to keep us from spinning into
 * infinity.
 * This is an arbitrarily high number.
 */
#define CONS_MAX_NUM_CALLBACKS 1000


/**************************************************************************
 *
 *   Alpha SRM  RPB -- CTB Type 4 slotinfo format being used
 *
 *
 *   63                   40 39       32 31     24 23      16 15   8 7    0
 *   +----------------------+-----------+---------+----------+------+-----+
 *   |        Rsvd          | Channel # | Hose #  | Bus Type | Bus# |Slot#|
 *   +----------------------+-----------+---------+----------+------+-----+
 *
 *               Bus Type Field:
 *                               0 = TURBOchannel
 *                               1 = ISA
 *                               2 = EISA
 *                               3 = PCI
 *
 **************************************************************************/

/* macros for extracting subfields from the slotinfo fields */
#define SLOTINFO_TO_CHANNELNO(i)	(((i) >> 32) & 0xff)
#define SLOTINFO_TO_HOSENO(i)	        (((i) >> 24) & 0xff)
#define SLOTINFO_TO_BUSTYPE(i)	        (((i) >> 16) & 0xff)
#define SLOTINFO_TO_BUSNO(i)	        (((i) >>  8) & 0xff)
#define SLOTINFO_TO_SLOTNO(i)	        (((i)      ) & 0xff)

/* constants for slotinfo bus_type subfield */
#define SLOTINFO_TC	0
#define SLOTINFO_ISA	1
#define SLOTINFO_EISA	2
#define SLOTINFO_PCI	3


/*
 *  ctrl structure private field used
 *  for console_attach routine in device
 *  drivers that can be the system console
 *  (graphics and serial drivers).
 *
 */
#define console_attach  private[3]

/*
 *  consDev values
 *
 *  consDev indicates whether system is using 
 *  a graphics or serial console.
 */
extern int consDev;

/*
 *  structure to support acquistion of firmware 
 *  revision information by getsysinfo().
 */

struct firmware_rev {
	long firmware_major;
	long firmware_minor;
	long firmware_variation;
};

/*
 *  structure to support acquistion of palcode 
 *  revision information by getsysinfo().
 */

struct palcode_rev {
	long palcode_os_type;
	long palcode_major;
	long palcode_minor;
	long palcode_variation;
};

#define CONS_DEV      0x01
#define GRAPHIC_DEV   0x02

/*
 *  printstate values
 *  are defined in cpu.h
 */ 

/*
 * definitions needed for translation to and from console network
 * bootstrings.
 */

struct net_console2unix{
   char *driver;
   int bus_type;
};

/* table for the translation is in console.c */
extern struct net_console2unix net_console2unix_table[];

/* Get the Unix driver name for a console network device type */
#define NET_CONSOLE2UNIX(bustype, devtype, unixname) {        \
         int i=0;                                             \
         struct net_console2unix *ptr=net_console2unix_table; \
         while(i<devtype && ptr[i].driver[0] != 0) i++;         \
         strcpy(unixname, ptr[i].driver);                     \
        }

/* Get the Console network device type for a unix driver
 * devtype contains the return value, -1 on failure */
#define NET_UNIX2CONSOLE(ctlrptr, devtype) {                     \
         int i=0;                                                \
         struct net_console2unix *ptr=net_console2unix_table;    \
         devtype=-1;                                             \
         while(ptr[i].driver[0] != 0 ) {                           \
            if (strcmp(ptr[i].driver, ctlrptr->ctlr_name)==0) {  \
               if (ptr[i].bus_type == DRIVER_WILDNUM ||          \
                   ptr[i].bus_type == ctlrptr->bus_hd->bus_type) \
                  devtype=i;                                     \
	    }                                                    \
            i++;                                                 \
         }                                                       \
        }

/*
 * function prototypes 
 */
struct controller;
void hal_pci_cons_ctlrstr(int bus_probe_alg_type, char *device_string,
				 struct controller *ctlr, char *protocol,
				 u_int remoteid, u_int unit);


#endif /*_ARCH_ALPHA_HAL_CONSOLE_H_ */
