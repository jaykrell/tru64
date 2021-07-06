#ifndef __MEDIA_CHANGER_H
#define __MEDIA_CHANGER_H
/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: media_changer.h,v $
 * Revision 1.1.7.1  2003/06/10  13:32:46  Jason_Miller
 * 	Ported file from /sbin/mcutil/include/. QAR 96001.
 *
 * Revision 1.1.10.1  2002/10/08  21:20:41  Jason_Miller
 * 	Add mc error codes for MC_ERROR_CODE and print functions
 * 	to eei_status class to improve error reporting. QAR 90279
 *
 * Revision 1.1.2.1  1999/12/08  16:24:00  Jan_Reimers
 * 	Integration into Base OS
 *
 * Revision 1.1.5.2  1999/04/01  21:32:24  Pat_Tressel
 * 	Add declarations for Extended Error Info support.
 * 	[1999/04/01  21:32:07  Pat_Tressel]
 *
 * Revision 1.1.2.14  1994/05/20  18:52:35  John_Painter
 * 	Fix clash over symbols not correctly resolved in
 * 	the merge phase (of Mike C's and Tjp's code)
 * 	[1994/05/20  18:52:16  John_Painter]
 * 
 * Revision 1.1.2.13  1994/05/19  20:20:28  John_Painter
 * 	move some includes specific to generic_scsi2 to generic_scsi2.h
 * 	modify the behavior of defining the phantom inquiry structure
 * 	[1994/05/19  20:17:34  John_Painter]
 * 
 * Revision 1.1.2.12  1994/03/16  22:19:48  John_Painter
 * 	Support for VIRT_ONLY builds added
 * 	[1994/03/16  22:15:07  John_Painter]
 * 
 * Revision 1.1.2.11  1994/03/08  18:08:23  Mike_Cattolico
 * 	checking for osf2.0 ssb
 * 	[1994/03/08  16:51:24  Mike_Cattolico]
 * 
 * Revision 1.1.2.10  1994/01/14  17:43:31  John_Painter
 * 	Update conditionals to include SunOS SCSIness
 * 	[1994/01/14  17:43:11  John_Painter]
 * 
 * 	Include SunOS specific support to replace rzdisk.h inclusion
 * 	[1994/01/14  00:57:05  John_Painter]
 * 
 * Revision 1.1.2.9  1993/11/26  21:03:49  Mike_Cattolico
 * 	checkin for ssb
 * 	[1993/11/26  21:03:24  Mike_Cattolico]
 * 
 * Revision 1.1.2.8  1993/10/29  17:05:37  Mike_Cattolico
 * 	added stuff to virtual jbox code & start cleanup for memory leaks
 * 	[1993/10/29  17:04:35  Mike_Cattolico]
 * 
 * Revision 1.1.2.7  1993/10/19  18:45:52  Mike_Cattolico
 * 	fix to include file & error stuff
 * 	[1993/10/19  18:39:07  Mike_Cattolico]
 * 
 * 	fix to error system
 * 	[1993/10/19  17:37:09  Mike_Cattolico]
 * 
 * Revision 1.1.2.6  1993/10/19  16:05:24  Mike_Cattolico
 * 	batch checkin, stuff done to error checking & no more inlines
 * 	[1993/10/19  16:02:46  Mike_Cattolico]
 * 
 * 	hold baselevel
 * 	[1993/10/19  00:34:30  Mike_Cattolico]
 * 
 * Revision 1.1.2.5  1993/09/13  21:48:43  Mike_Cattolico
 * 	re-arrange for clarity & remove rezero() functionality, mike
 * 	[1993/09/13  21:41:48  Mike_Cattolico]
 * 
 * Revision 1.1.2.4  1993/08/26  21:25:35  Mike_Cattolico
 * 	fix path to rzdisk for alpha/osf
 * 	[1993/08/26  21:25:12  Mike_Cattolico]
 * 
 * Revision 1.1.2.3  1993/08/20  16:39:47  Mike_Cattolico
 * 	fix BOOL to MC_BOOL
 * 	[1993/08/20  16:38:54  Mike_Cattolico]
 * 
 * Revision 1.1.2.2  1993/08/04  21:31:35  Mike_Cattolico
 * 	checkin of new directory structure
 * 	[1993/08/04  21:15:30  Mike_Cattolico]
 * 
 * $EndLog$
 */

/* Media Changer Header File
 *
 *	This file contains three major sections
 *		1) common header information for C and C++
 *		2) header information for C
 *		3) header information for C++
*/

#ifndef MC_C_CXX_SHARED
#define MC_C_CXX_SHARED

	/* Implementations misc. */
typedef int MC_BOOL;

typedef enum {		/* error return codes */
	MC_NO_ERROR,		/* no error, normal return status */
	MC_UNKNOWN,		/* unknown error */
	MC_ERR_OFFLINE,		/* unit is offline */
	MC_NOT_SUPPORTED,	/* operation is not supported by device */
	MC_ENOMEM,		/* unable to get memory for data structures */
	MC_ENXIO,		/* the device is not answering */
	MC_ENODEV,		/* no such device */
	MC_SRC_EMPTY,		/* source is empty on a move operation */
	MC_DEST_FULL,		/* destination is full on a move operation */
	MC_BAD_ADDR,		/* address or address range is invalid */
	MC_INTERNAL,		/* internal error */
	MC_PERM,		/* not owner */
	MC_ACCES,		/* permission denied, permissions problem */
	MC_BAD_DRIVE_EJECT,	/* the eject command returned an error */
	MC_NO_CHANGER_ENTRY,	/* entry not found in database (mcicap) */
	MC_NO_INTERFACE,	/* can't provide access to requested interface*/
	MC_USAGE_ERROR,		/* incorrect argument(s) passed to function */
	MC_INTERFACE_ERROR,	/* interface specific error */
	MC_BAD_MCICAP,		/* syntax error or infinite "tc" recursion */
	MC_MCICAP_OPEN_FAILED, 
				/* no MCICAP, file permissions, or
				 * too many open files
				*/
	MC_NO_ENTRY,	
				/* cannot find this entry in mcicap file
				 * or $MCICAP
				*/
	MC_EIO,                 /* I/O error */ 
	MC_EFAULT,              /* bad address */
	MC_EINTR,               /* interrupted system call */
	MC_LAST_ERROR
} MC_ERROR_CODE;

#define MC_MAX_ERROR MC_LAST_ERROR

typedef enum {		/* addressable types */
	MC_TRANSPORT_TYPE,	/* transport */
	MC_SLOT_TYPE,		/* slot element */
	MC_PORT_TYPE,		/* import/export port */
	MC_DRIVE_TYPE,		/* data transfer */
	MC_ELEMENT_TYPE,	/* physical element addressing */
	MC_NUM_ADDR_TYPES	/* must be last */
} MC_TYPES;

#define MC_FIRST_ADDR_TYPE MC_TRANSPORT_TYPE

typedef struct element_addr {		/* Element Address */
	int elo_id;			/* element logical address */
	MC_TYPES elo_type;		/* element logical type */
} element_addr_t;	

typedef element_addr_t MC_ELEMENT_OBJ;	/*XXX might want to fix, mike */

typedef struct elist_member {
	int count;			/* number of contiguous elements */
	element_addr_t element;		/* type/logical of first element */
} elist_member_t;

typedef struct elist {
	int size;			/* number of list members */
	elist_member_t *list;		/* list of elements */
} elist_t;

typedef enum TIMEOUT_TYPE {
	TM_INIT_ELEMENT = 0x1,
	TM_STATUS_ELEMENT = 0x2,
	TM_MOVE_MEDIA = 0x4,
	TM_EXCHANGE_MEDIA = 0x8,
	TM_POSITION_TO_ELEMENT = 0x10,
	TM_PREVENT_ALLOW = 0x20,
	TM_RESERVE = 0x40,
	TM_RELEASE = 0x80,
	TM_REQUEST_VOL = 0x100,
	TM_SEND_VOL = 0x200
	} TIMEOUT_FLAG;

#define NUM_TM_ENUM 10

#endif /* MC_C_CXX_SHARED */


#if !defined(__cplusplus) || defined(C_INTERFACE_ONLY)

/* Media Changer Interface Library  C interface */

	/* opaque structure typedefs */
typedef struct mc_map MC_MAP;
typedef struct mc_stat MC_STAT;
typedef struct mc_stat_hdr MC_STAT_HDR;
typedef struct mc_changer MC_CHANGER;
typedef struct mc_diag_entry MC_DIAG_ENT;

extern MC_ERROR_CODE mc_open(const char *name, MC_CHANGER **mc);
extern MC_ERROR_CODE mc_close(MC_CHANGER *mc);

	/* Scsi2_inspired_interface */

MC_ERROR_CODE mc_inquiry(MC_CHANGER *mc, struct inquiry_info *inqbuf);
MC_ERROR_CODE mc_init_element(MC_CHANGER *mc, int start, int num);
MC_ERROR_CODE mc_element_status(MC_CHANGER *mc, MC_STAT_HDR *mcshdr);
MC_ERROR_CODE mc_move_medium(MC_CHANGER *mc,element_addr_t *src_obj,
				element_addr_t *dest_obj,
				element_addr_t *tport_obj, int invert);

MC_ERROR_CODE mc_exchange_medium(MC_CHANGER *mc, element_addr_t *src_id,
			element_addr_t *dest1_id, element_addr_t *dest2_id,
			element_addr_t *tport_elmnt, int invert1, int invert2);

MC_ERROR_CODE mc_position_element(MC_CHANGER *mc, element_addr_t *element_obj);

MC_ERROR_CODE mc_prevent_removal(MC_CHANGER *mc);
MC_ERROR_CODE mc_allow_removal(MC_CHANGER *mc);

MC_ERROR_CODE mc_release_all(MC_CHANGER *mc);
MC_ERROR_CODE mc_release_all_tparty(MC_CHANGER *mc, int tparty);
MC_ERROR_CODE mc_reserve_all(MC_CHANGER *mc);
MC_ERROR_CODE mc_reserve_all_tparty(MC_CHANGER *mc, int tparty);

MC_ERROR_CODE mc_release_element(MC_CHANGER *mc, int elist);
MC_ERROR_CODE mc_release_element_tparty(MC_CHANGER *mc, int elist, int tparty);
MC_ERROR_CODE mc_reserve_element(MC_CHANGER *mc, int elist);
MC_ERROR_CODE mc_reserve_element_tparty(MC_CHANGER *mc, int elist, int tparty);

MC_ERROR_CODE mc_send_volume_tag(MC_CHANGER *mc);
MC_ERROR_CODE mc_voltag_to_element(MC_CHANGER *mc);

MC_BOOL mc_storage_capability(MC_CHANGER *mc, MC_TYPES src);
MC_BOOL mc_move_capability(MC_CHANGER *mc, MC_TYPES src, MC_TYPES dest);
MC_BOOL mc_exchange_capability(MC_CHANGER *mc, MC_TYPES src, MC_TYPES dest);

MC_ERROR_CODE mc_vendor_extension(MC_CHANGER *mc, int argc, char *argv[]);

MC_ERROR_CODE mc_log_list(MC_CHANGER *mc);
MC_ERROR_CODE mc_log_upload(MC_CHANGER *mc);
MC_ERROR_CODE mc_change_definition(MC_CHANGER *mc);
MC_ERROR_CODE mc_log_read(MC_CHANGER *mc);
MC_ERROR_CODE mc_mode(MC_CHANGER *mc);
MC_ERROR_CODE mc_diag_list(MC_CHANGER *mc, MC_DIAG_ENT **diag_list);
MC_ERROR_CODE mc_diag_run(MC_CHANGER *mc, char *diag_str, char *diag_args);


	/* Typed_element_resource(s) */

	/* maps */
MC_MAP *mc_get_map(MC_CHANGER *mc,MC_TYPES type);
MC_ERROR_CODE mc_set_map(MC_CHANGER *mc,MC_TYPES type, MC_MAP *map);
MC_ERROR_CODE mc_alloc_map(MC_CHANGER *mc, MC_TYPES type, MC_MAP **map);
MC_MAP *mc_map_next(MC_MAP *);
MC_ERROR_CODE mc_set_map_next(MC_MAP *map, MC_MAP *next_map);
int mc_map_start(MC_MAP *map);
int mc_set_map_start(MC_MAP *map, int start);
int mc_map_range(MC_MAP *map);
int mc_set_map_range(MC_MAP *map, int range);
MC_ERROR_CODE mc_map_to_virt(MC_CHANGER *mc, element_addr_t *obj, int addr);
MC_ERROR_CODE mc_map_to_phys(MC_CHANGER *mc, element_addr_t *obj, int *addr);
int mc_num_type(MC_CHANGER *mc, MC_TYPES element_type);
int mc_set_num_elements(MC_CHANGER *mc, MC_TYPES element_type, int num);

MC_ERROR_CODE mc_drive_eject(MC_CHANGER *mc, int drive_num);
MC_ERROR_CODE mc_drive_tur(MC_CHANGER *mc, int drive_num);
const char *mc_drive_type(MC_CHANGER *mc);
MC_ERROR_CODE mc_set_drive_type(MC_CHANGER *mc, const char *drive_type);
const char *mc_drive_name(MC_CHANGER *mc, int drive_num);
MC_ERROR_CODE mc_set_drive_name(MC_CHANGER *mc, int drive_num, char *name);

	/* Interface_control_panel */
const char *mc_interface_file(MC_CHANGER *mc);
const char *mc_interface_name(MC_CHANGER *mc);
const char *mc_interface_args(MC_CHANGER *mc);
const char *mc_device_name(MC_CHANGER *mc);
MC_ERROR_CODE mc_set_interface_file(MC_CHANGER *mc, const char *if_file);
MC_ERROR_CODE mc_set_interface_name(MC_CHANGER *mc, const char *if_name);
MC_ERROR_CODE mc_set_interface_args(MC_CHANGER *mc, const char *if_args);
MC_ERROR_CODE mc_set_device_name(MC_CHANGER *mc, const char *dev_name);

const char *mc_error_to_str(const MC_ERROR_CODE mc_err);
const char *mc_extended_error_str(MC_CHANGER *mc, const MC_ERROR_CODE mc_err);

MC_STAT_HDR
   *mc_alloc_element_status(MC_CHANGER *mc,MC_TYPES type,int start,int num);
MC_ERROR_CODE mc_free_element_status(MC_CHANGER *mc, MC_STAT_HDR *mcshdr);

MC_STAT *mc_get_stats(MC_STAT_HDR *mcshdr);
MC_STAT *mc_next_stats(MC_STAT *mc);

void mc_debug_on();
void mc_debug_off();

int mc_fd();

	/* Features_and_options_control_panel */

int mc_has_auto_eject(MC_CHANGER *mc);
int mc_has_display(MC_CHANGER *mc);
int mc_has_barcode(MC_CHANGER *mc);
int mc_has_two_sided(MC_CHANGER *mc);
int mc_has_volumetag(MC_CHANGER *mc);
int mc_has_change_definition(MC_CHANGER *mc);
int mc_has_exchange_medium(MC_CHANGER *mc);
int mc_has_init_element(MC_CHANGER *mc);
int mc_has_log_select_sense(MC_CHANGER *mc);
int mc_has_mode_select_sense(MC_CHANGER *mc);
int mc_has_position_to_element(MC_CHANGER *mc);
int mc_has_prevent_allow(MC_CHANGER *mc);
int mc_has_element_status(MC_CHANGER *mc);
int mc_has_read_diagnostic(MC_CHANGER *mc);
int mc_has_release_reserve(MC_CHANGER *mc);
int mc_has_send_volume_tag(MC_CHANGER *mc);
int mc_has_capabilities_info(MC_CHANGER *mc);

void mc_set_auto_eject(MC_CHANGER *mc, MC_BOOL boolean);
void mc_set_display(MC_CHANGER *mc, MC_BOOL boolean);
void mc_set_barcode(MC_CHANGER *mc, MC_BOOL boolean);
void mc_set_two_sided(MC_CHANGER *mc, MC_BOOL boolean);
void mc_set_volumetag(MC_CHANGER *mc, MC_BOOL boolean);
void mc_set_change_definition(MC_CHANGER *mc, MC_BOOL boolean);
void mc_set_exchange_medium(MC_CHANGER *mc, MC_BOOL boolean);
void mc_set_init_element_status(MC_CHANGER *mc, MC_BOOL boolean);
void mc_set_init_element(MC_CHANGER *mc, MC_BOOL boolean);
void mc_set_log_select_sense(MC_CHANGER *mc, MC_BOOL boolean);
void mc_set_mode_select_sense(MC_CHANGER *mc, MC_BOOL boolean);
void mc_set_position_to_element(MC_CHANGER *mc, MC_BOOL boolean);
void mc_set_prevent_allow(MC_CHANGER *mc, MC_BOOL boolean);
void mc_set_element_status(MC_CHANGER *mc, MC_BOOL boolean);
void mc_set_read_diagnostic(MC_CHANGER *mc, MC_BOOL boolean);
void mc_set_release_reserve(MC_CHANGER *mc, MC_BOOL boolean);
void mc_set_send_volume_tag(MC_CHANGER *mc, MC_BOOL boolean);
void mc_set_capabilities_info(MC_CHANGER *mc, MC_BOOL boolean);

int mc_stat_full(MC_STAT *mc_stat);
int mc_stat_invert(MC_STAT *mc_stat);
int mc_stat_impexp(MC_STAT *mc_stat);
int mc_stat_except(MC_STAT *mc_stat, int *asc, int *ascq);
int mc_stat_access(MC_STAT *mc_stat);
int mc_stat_source(MC_STAT *mc_stat, int *phys_addr);
int mc_stat_pvoltag(MC_STAT *mc_stat, char **pvoltag);
int mc_stat_avoltag(MC_STAT *mc_stat, char **avoltag);
int mc_stat_vendor(MC_STAT *mc_stat, char **vendor);

void mc_stat_set_full(MC_STAT *mc_stat, MC_BOOL full);
void mc_stat_set_invert(MC_STAT *mc_stat, MC_BOOL invert);
void mc_stat_set_impexp(MC_STAT *mc_stat, MC_BOOL impexp);
void mc_stat_set_except(MC_STAT *mc_stat, int asc, int ascq);
void mc_stat_set_access(MC_STAT *mc_stat, int access);
void mc_stat_set_source(MC_STAT *mc_stat, int phys_addr);
void mc_stat_set_pvoltag(MC_STAT *mc_stat, char *pvoltag);
void mc_stat_set_avoltag(MC_STAT *mc_stat, char *avoltag);
void mc_stat_set_vendor(MC_STAT *mc_stat, char *vendor);

#endif /* !defined(__cplusplus) || defined(C_INTERFACE_ONLY) */


#ifndef C_INTERFACE_ONLY

#if defined(__cplusplus)
// TODO:
//	design interface for:
//			send_volume_tag() / voltag_to_element()
//			reserve() / release()
//	- errors
//	- geometry information
//	- diagnostic support
//	- mode sense/select support
//	- timeout / asyncronous interface
//
//	- igm support (serial)
//	- stk support (tcp/ip)
//

		// Media Changer Interface

//  (media_changer)
//	|------------hasa--------> Scsi2_inspired_interface
//	|------------hasa--------> Typed_element_resource(s)
//	|------------hasa--------> Interface_control_panel
//	|------------hasa--------> Features_and_options_control_panel
//
//	(generic_scsi2_changer)	====isa======>	(media_changer)
//	(exb_120_changer)	====isa======>	(generic_scsi2_changer)
//

	// The major players in the Media Changer Game

typedef class media_changer media_changer_t;	// Media Changer ABC
typedef class element_map element_map_t;	// Mapping for Element Address
typedef class element_stat_array element_stat_array_t;	// Element Status Array
typedef class element_stat element_stat_t;	// Element Status

	// Typedefs of interest for media changer class
typedef class media_inquiry media_inquiry_t;	// Inquiry 
typedef void MC_DIAG_ENTRY;			//XXX just for now

// Forward references (looks like that's what the above typedefs are really for)
class eei_status;		// Extended Error Info

#include <string.h>

class mc_error {
public:
	mc_error();
	~mc_error();

	MC_ERROR_CODE error();
	const char *error_string();

	void error(MC_ERROR_CODE e, const char *str = 0, const char *str2 = 0);

	int mc_error_to_unix(MC_ERROR_CODE mc_err);
	MC_ERROR_CODE unix_to_mc_error(int err);

private:
	MC_ERROR_CODE err;
	int err_str_sz;
	char *err_str;
};

	// Media Changer Abstract Base Class

class media_changer {
public:
	media_changer();
	virtual ~media_changer();

// Scsi2_inspired_interface

	virtual MC_ERROR_CODE open() = 0;
	virtual MC_ERROR_CODE close() = 0;

	// mandatory media changer primitives
	virtual MC_ERROR_CODE inquiry(media_inquiry_t *inq) = 0;
	virtual MC_ERROR_CODE init_element();
	virtual MC_ERROR_CODE init_element(const int start,const int num) = 0;
	virtual MC_ERROR_CODE element_status(element_stat_array_t *mcshdr) = 0;
	virtual MC_ERROR_CODE move_medium(element_addr_t *src_obj,
			element_addr_t *dest_obj, element_addr_t *tport_obj,
						const int invert) = 0;

	// media changer optional primitives will return MC_NOT_SUPPORTED
	virtual MC_ERROR_CODE exchange_medium(element_addr_t *src_id,
			element_addr_t *dest1_id, element_addr_t *dest2_id,
			element_addr_t *tport_elmnt,
			const int invert1, const int invert2);

	virtual MC_ERROR_CODE position_element(element_addr_t *element_addr,
					element_addr_t *transport = 0);

	virtual MC_ERROR_CODE prevent_removal();
	virtual MC_ERROR_CODE allow_removal();

	virtual MC_ERROR_CODE release_all();	// release all reservations
	virtual MC_ERROR_CODE release_all(int id);	// release all 3rd party
	virtual MC_ERROR_CODE release_elem(int res_id);
	virtual MC_ERROR_CODE release_elem(int res_id, int id);

	virtual MC_ERROR_CODE reserve_all();	// reserve all
	virtual MC_ERROR_CODE reserve_all(int id);	// reserve all 3rd party
	virtual MC_ERROR_CODE reserve_elem(int res_id, elist_t *elist);
	virtual MC_ERROR_CODE reserve_elem(int res_id, elist_t *elist, int id);

	virtual MC_ERROR_CODE send_volume_tag();
	virtual MC_ERROR_CODE voltag_to_element();

	virtual MC_ERROR_CODE vendor_extension(int argc, char *argv[]);

	virtual MC_BOOL storage_capability(MC_TYPES src);
	virtual MC_BOOL move_capability(MC_TYPES src, MC_TYPES dest);
	virtual MC_BOOL exchange_capability(MC_TYPES src, MC_TYPES dest);

	virtual MC_ERROR_CODE log_list();
	virtual MC_ERROR_CODE log_upload();
	virtual MC_ERROR_CODE change_definition();
	virtual MC_ERROR_CODE log_read();
	virtual MC_ERROR_CODE mode();
	virtual MC_ERROR_CODE diag_list(MC_DIAG_ENTRY **diag_list);
	virtual MC_ERROR_CODE diag_run(const char *diag_str,const char *args);

	// timeout panel
	virtual MC_ERROR_CODE tm_get_timeout(const TIMEOUT_FLAG tentry,
						unsigned long *val) const;
	virtual MC_ERROR_CODE tm_set_timeout(const int flags,
						const unsigned long timeval);

// Non-SCSI Digital Unix interface

	MC_ERROR_CODE get_eei(eei_status *eei);

// Temporary declaration of DEVGETEEI ioctl and EEI_DO_NOT_CLEAR flag, until
// they're included in deveei.h.

#ifndef DEVGETEEI
#define DEVGETEEI	_IOWR('v', 101, DEV_EEI_STATUS)
#endif

#ifndef EEI_DO_NOT_CLEAR
#define EEI_DO_NOT_CLEAR	0x00100000  /* Do not clear the EEI status */
#endif

// Typed_element_resource(s)

	const element_map_t *type_map(const MC_TYPES t) const;
	void type_map(const MC_TYPES t, element_map_t *map);

	MC_ERROR_CODE map_to_phys(const element_addr_t *obj, int *addr) const;
	MC_ERROR_CODE map_to_phys_contiguous(MC_TYPES type, int start, int num,
				int *phys_start, int *lengh);
	MC_ERROR_CODE map_to_virt(element_addr_t *obj, const int addr) const;

	int num_elements(const MC_TYPES t) const;
	void num_elements(const MC_TYPES t, int num);

	// data transfer naming and control

	void drive_name(const int drive_num, const char *drive_name);
	const char *drive_name(const int drive_num) const;

	void drive_type(const char *type);
	const char *drive_type() const;

	MC_ERROR_CODE drive_tur(const int drive_num) const;
	MC_ERROR_CODE drive_eject(const int drive_num) const;

	MC_ERROR_CODE drive_num(const char *drive_name, int *drive_num) const;

// Interface_control_panel

	// names for current configuration
	const char *interface_name() const;
	const char *interface_file() const;
	const char *interface_args() const;
	const char *device_name() const;
	void interface_name(const char *if_name);
	void interface_file(const char *file);
	void interface_args(const char *cp);
	void device_name(const char *dev_name);

	int fd() const;

	mc_error error;		// error string(s) from last error

// Features_and_options_control_panel

	// media changer optional features support
	MC_BOOL has_auto_eject() const;
	MC_BOOL has_display() const;
	MC_BOOL has_barcode() const;
	MC_BOOL has_two_sided() const;
	MC_BOOL has_volumetag() const;
	MC_BOOL has_change_definition() const;
	MC_BOOL has_exchange_medium() const;
	MC_BOOL has_init_element() const;
	MC_BOOL has_log_select_sense() const;
	MC_BOOL has_mode_select_sense() const;
	MC_BOOL has_position_to_element() const;
	MC_BOOL has_prevent_allow() const;
	MC_BOOL has_element_status() const;
	MC_BOOL has_read_diagnostic() const;
	MC_BOOL has_release_reserve() const;
	MC_BOOL has_send_volume_tag() const;
	MC_BOOL has_capabilities_info() const;

	// These functions allow client to set/clear an optional
	void has_auto_eject(const int val);
	void has_display(const int val);
	void has_barcode(const int val);
	void has_two_sided(const int val);
	void has_volumetag(const int val);
	void has_change_definition(const int val);
	void has_exchange_medium(const int val);
	void has_init_element(const int val) ;
	void has_log_select_sense(const int val);
	void has_mode_select_sense(const int val);
	void has_position_to_element(const int val);
	void has_prevent_allow(const int val);
	void has_element_status(const int val);
	void has_read_diagnostic(const int val);
	void has_release_reserve(const int val);
	void has_send_volume_tag(const int val);
	void has_capabilities_info(const int val);

private:
	// don't define these functions
	media_changer& operator=(const media_changer& rhs);
	media_changer(const media_changer& x);

protected:
	int	mc_fd;			// file descriptor for talking to device
	char	*mc_device_name;	// device to open
	char	*mc_interface_name;	// name of this interface type
	char	*mc_interface_file;	// process filter to exec
	char	*mc_interface_args;	// args to pass to process filter

	char	*drive_type_val;	// type of drives
	char	**mcc_drivenames;	// names of data transfer units
	int	named_drives;		// highwater mark of drivenames index

	int num_element[MC_NUM_ADDR_TYPES];	// # of elements per type
	element_map_t *mc_addr_maps[MC_NUM_ADDR_TYPES];	// maps per type

	MC_BOOL capabilities_info;	// is storage / move capacity info valid
	int storage_cap[MC_NUM_ADDR_TYPES];
	int move_cap[MC_NUM_ADDR_TYPES];
	int exchange_cap[MC_NUM_ADDR_TYPES];

	/*XXX need information on transport geometry */

		// configuration information
	int	display : 1,
		barcode : 1,
		auto_eject : 1,
		two_sided : 1,
		volumetag : 1;

	// optional command support booleans
	int	change_definition_op : 1,
		exchange_medium_op : 1,
		init_element_status_op : 1,
		log_select_sense_op : 1,
		mode_select_sense_op : 1,
		position_to_element_op : 1,
		prevent_allow_op : 1,
		read_element_status_op : 1,
		read_diagnostic_op : 1,
		release_reserve_op : 1,
		send_volume_tag_op : 1;

	// Read and display sense data following an error.
	virtual MC_ERROR_CODE cam_get_error(const char *comstr);
};


class element_stat {
public:
	element_stat(const MC_TYPES type = MC_SLOT_TYPE, const int logical = 0);
	~element_stat();
	element_stat& operator=(const element_stat& rhs);

	void clear_all();
	MC_TYPES stat_type() const;

	int stat_logical() const;	// return logical address for element
	int stat_physical() const;	// return physical address for element

	MC_BOOL stat_full() const;	// true, if has media
	MC_BOOL stat_invert() const;	// true, if inverted
	MC_BOOL stat_impexp() const;	// true, if operator inserted
	MC_BOOL stat_access() const;	// true, if changer can access element

	MC_BOOL stat_except(int *asc, int *ascq ) const;
				// true, if valid exception codes

	MC_BOOL stat_source(int *phys_addr) const;
	// true, if valid physical address of last element to contain media

#ifdef not_yet
	MC_BOOL stat_source(element_addr_t *elem_obj) const;
#endif

	MC_BOOL stat_pvoltag(char **pvoltag) const;	// true, if valid tag
	MC_BOOL stat_avoltag(char **avoltag) const;	// true, if valid tag
	MC_BOOL stat_vendor(char **vendor) const;	// true, if valid tag

	// following functions allow client to modify element status
	void stat_logical(const int val);
	void stat_type(const MC_TYPES val);
	void stat_physical(const int val);
	void stat_full(const int val);
	void stat_invert(const int val);
	void stat_impexp(const int val);
	void stat_access(const int val);
	void stat_except(const int except, const int asc, const int ascq);
	void stat_source(const int svalid, const int phys_addr);
	void stat_pvoltag(const char *pvoltag);
	void stat_avoltag(const char *avoltag);
	void stat_vendor(const char *vendor);

private:
	// don't define these functions
	element_stat(const element_stat& x);

protected:
	MC_TYPES	stat_type_val;		// type of element
	int	stat_logical_val;		// logical address of element
	int	stat_physical_val;		// physical address of element
	int	mcs_full : 1,		// contains media
		mcs_impexp : 1,		// inserted by operator
		mcs_except : 1,		// exception qualifier info is valid
		mcs_access : 1,		// transport can access this element
		mcs_svalid : 1,		// source element info is valid
		mcs_invert : 1;		// media is in an inverted state
	int	mcs_source;		// source element for this media
	int	mcs_asc;		// the exception qualifier
	int	mcs_ascq;		// additional exception qualifier
	char	*mcs_pvoltag;		// primary volume tag
	char	*mcs_avoltag;		// alternate volume tag
	char	*mcs_vendor;		// vendor tag
};


class element_stat_array {
public:
	element_stat_array(const MC_TYPES type, const int start, const int num);
	~element_stat_array();

	MC_TYPES mcs_type() const;
	int	mcs_start() const;
	int	mcs_num()   const;
	element_stat_t *mcs_stats() const;

	const element_stat_t& operator[](const int) const;
	element_stat_t& operator[](const int);

private:
	// don't define these functions
	element_stat_array(const element_stat_array& x);
	element_stat_array& operator=(const element_stat_array& rhs);

protected:
	MC_TYPES mcs_type_val;
	int	mcs_start_val;
	int	mcs_num_val;
	element_stat_t *mcs_stats_val;
};


struct emap {		//XXX declare this within the element_map class
	int map_range;
	int map_start;
	struct emap *map_next;
};

class element_map {	// class for simple mapping
public:
	element_map();
	element_map(const char *cp);	//XXX todo: discribe a legal map string
	element_map(const int start,const int end);
	~element_map();

	int virt_to_phys(const int addr, int *mapaddr) const;
	int phys_to_virt(const int addr, int *mapaddr) const;
	int virt_to_phys_contig(const int start,const int num,
					int *phys_start,int *length) const;

	int virt_base() const;
	void virt_base(const int base);

	const struct emap *mapvalue() const;

private:
	int virt_base_value;
	struct emap *map;

	// don't define these functions
	element_map(const element_map& x);
	element_map& operator=(const element_map& rhs);
};


class media_inquiry {
public:
	media_inquiry();
	~media_inquiry();

	int device_type() const;	// scsi2 device type integer
	int device_qulifier() const;
	int removable_medium() const;
	int version() const;
	const char *vendor_id() const;
	const char *product_id() const;
	const char *revision_level() const;

	void device_type(int val);	// scsi2 device type integer
	void device_qulifier(int val);
	void removable_medium(int val);
	void version(int val);

	void vendor_id(char *val);
	void vendor_id(char *val, int len);
	void product_id(char *val);
	void product_id(char *val, const int len);
	void revision_level(char *val);
	void revision_level(char *val, const int len);

protected:
	// don't define these functions
	media_inquiry(const media_inquiry& x);
	media_inquiry& operator=(const media_inquiry& rhs);
private:
	int perfdt;
	int devtq;
	int rmb;
	int version_val;
	char *vndrid;
	char *prodid;
	char *revision;
};

// Holder for the EEI status.
class eei_status {
	friend ostream& operator<<( ostream&, const eei_status& );
public:
	eei_status();
	long version() const;	// Return pieces of the EEI data.
	u_int status() const;
	u_int flags() const;
	u_int cam_status() const;
	u_int scsi_status() const;
	char sense_data(int index) const;
	u_int sense_key() const;
	u_int additional_sense_length() const;
	u_int asc() const;
	u_int ascq() const;

	int sense_data_valid() const;	// Query whether sense data is valid.
	int sense_data_length() const;	// Get length of sense data.

	// Set the EEI_DO_NOT_CLEAR flag that tells driver not to clear the
	// EEI status after it's read.
	void set_do_not_clear_flag();

	// After calling DEVGETEEI from within the media_changer class,
	// this call is used to fill in our data field.
	void store_eei_data(const DEV_EEI_STATUS &newdata);

	// Print functions
	const char *print_eei_status() const;
	const char *print_cam_status() const;
	const char *print_scsi_status() const;
private:
	DEV_EEI_STATUS data;
};

	// output routines are provided for the following types
	// they are linked into the image only if not "redefined"
class ostream;
ostream& operator<<(ostream&, const media_changer_t&);		// Media Changer
ostream& operator<<(ostream&, const media_inquiry_t&);		// Inquiry
ostream& operator<<(ostream&, const element_map_t *);		// Map
ostream& operator<<(ostream&, const element_stat_array_t&);	// Element
ostream& operator<<(ostream&, const MC_TYPES&);			// Address Type 
ostream& operator <<(ostream& s, const elist_t *elist);
ostream& operator<<(ostream&, const eei_status&);		// EEI

extern "C" {
	const char *mc_error_to_str(const MC_ERROR_CODE mc_err);

}

MC_ERROR_CODE show_sense(const char *comstr, const extended_sense *sense,
	mc_error *error, ostream *s);

#endif	/* __cplusplus */
#endif /* C_INTERFACE_ONLY */
#endif /* __MEDIA_CHANGER_H */
