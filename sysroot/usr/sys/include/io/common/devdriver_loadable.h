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
 * @(#)$RCSfile: devdriver_loadable.h,v $ $Revision: 1.1.8.1 $ (DEC) $Date: 2002/05/30 23:16:36 $
 */
/*
 * The following definitions are used to represent configuration information
 * for loadable drivers.
 */

#ifndef LDBL_DEVDRIVER_HDR
#define LDBL_DEVDRIVER_HDR

#ifndef NULL
#define NULL ((char *) 0)
#endif  /* NULL */

/* Define various constants used in configuring of loadable drivers */

/* Topology Search Options */

#define LDBL_SEARCH_ALL		0x00000000 /* Check all structures		*/
#define LDBL_SEARCH_NOINCLUDE	0x00000001 /* Don't use specified struct	*/

/* Flags field bit definitions */

#define LDBL_AUTOCONFIG		0x00000001 /* Driver supports autoconfiguration  */

/* Define error codes */

#define	MERGE_BUS_INUSE		1	   /* Bus in use error			*/
#define MERGE_BUS_ACTIVE	2	   /* Bus is already active error	*/
#define	MERGE_BUS_NOPARENT	3	   /* No parent bus to connect to error	*/
#define MERGE_BUS_NOSUPPORT	4	   /* Parent bus has no loadable support */

#define	MERGE_CTLR_INUSE	1	   /* Controller in use error		*/
#define	MERGE_CTLR_ACTIVE	2	   /* Controller is already active err.	*/
#define MERGE_CTLR_NOPARENT	3	   /* No parent bus to connect to error */
#define MERGE_CTLR_NOSUPPORT	4	   /* Parent bus has no loadable support */

#define	LDBL_ENOBUS		-10	   /* No bus specified or no loadable	*/
#define	LDBL_ENOPARENT		-11	   /* No parent bus to connect to	*/
#define LDBL_EALIVE		-12	   /* Bus/Ctlr/Device still alive	*/
#define LDBL_ECONFLICT		-13	   /* Stanza entry conflicts with existing active bus/ctlr */

/* Define string compare macros */

#define strcmp_EQL(A,B)		(strcmp (A, B) == 0)
#define strcmp_NEQ(A,B)		(strcmp (A, B) != 0)

#ifdef KERNEL
/*
 * Define the external global variables.
 */

extern struct config_entry	*ldbl_module_list;
extern struct config_entry	*ldbl_devlist;

/*
 * External routine definitions needed mainly for 
 * controller support
 */

extern int			ldbl_ctlr_configure();
extern int			ldbl_ctlr_unconfigure();
extern int			ldbl_stanza_resolver();

/*
 * External routine definitions needed mainly for bus 
 * support
 */

extern struct bus *
ldbl_find_bus(struct bus *bus_ptr, int state, char *bus_name, int bus_num);

extern struct bus *
ldbl_search_bus_local(struct bus *bus_ptr, int state, char *bus_name, 
					int bus_num, int slot);

extern struct controller *
ldbl_find_ctlr(struct controller *ctlr_ptr, int state, char *ctlr_name, 
					int ctlr_num, int slot);
extern int
ldbl_find_devlist_entry(char *driver_name, char *ctlr_name, int ctlr_num,
					struct device **dev_entry, caddr_t *context);
extern void			ldbl_cleanup_devlist(char *driver_name);
extern int			ldbl_enqueue_devlist(struct config_entry *dev_ce);
extern struct bus *		ldbl_get_next_bus(struct bus *bus_ptr);
extern void			ldbl_deallocate_bus(struct bus *bus);
extern void			ldbl_deallocate_ctlr(struct controller *ctlr);
extern void			ldbl_deallocate_dev(struct device *dev);

extern struct config_entry *	get_config_entry(char *name, int type);

#endif /* KERNEL */
/*
 * Now define all of the debugging stuff
 */
#define LDBL_DEBUG
#ifdef LDBL_DEBUG

extern void	print_hardware_topology();
extern void	indent_level();
extern void	print_bus_entry();
extern void	print_ctlr_entry();
extern void	print_dev_entry();

extern int	ldbl_debug;

#define Dprintf if (ldbl_debug) printf
#define Dprint_bus(text, bp) \
	if (ldbl_debug) { \
	   printf ("%s ", text); \
	   print_bus_entry (bp); \
	}
#define Dprint_ctlr(text, cp) \
	if (ldbl_debug) { \
	printf ("%s ", text); \
	print_ctlr_entry (cp); \
	}
#define Dprint_dev(text, dev) \
	if (ldbl_debug) { \
	printf ("%s ", text); \
	print_dev_entry (dev); \
	}

#else	/* LDBL_DEBUG */

#define	Dprintf
#define	Dprint_bus
#define Dprint_ctlr
#define Dprint_dev

#endif	/* LDBL_DEBUG */
#endif  /* LDBL_DEVDRIVER_HDR */
