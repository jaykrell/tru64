// 
// *****************************************************************
// *                                                               *
// *   Copyright 2002 Compaq Information Technologies Group, L.P.  *
// *                                                               *
// *   The software contained on this media  is  proprietary  to   *
// *   and  embodies  the  confidential  technology  of  Compaq    *
// *   Computer Corporation.  Possession, use,  duplication  or    *
// *   dissemination of the software and media is authorized only  *
// *   pursuant to a valid written license from Compaq Computer    *
// *   Corporation.                                                *
// *                                                               *
// *   RESTRICTED RIGHTS LEGEND   Use, duplication, or disclosure  *
// *   by the U.S. Government is subject to restrictions  as  set  *
// *   forth in Subparagraph (c)(1)(ii)  of  DFARS  252.227-7013,  *
// *   or  in  FAR 52.227-19, as applicable.                       *
// *                                                               *
// *****************************************************************
//
// HISTORY
// 
// @(#)$RCSfile: gem_bb.hxx,v $ $Revision: 1.1.12.2 $ (DEC) $Date: 2002/01/02 19:58:06 $
// 
//
//
#if !defined(GEM_BB_HXX)
#define GEM_BB_HXX

// Copyright 1997 Compaq Computer Corporation
//
// COMPAQ Registered in U.S. Patent and Trademark Office.
//
// Confidential computer software.  Valid license from Compaq required for
// possession,  use or  copying.  Consistent  with  FAR 12.211 and 12.212,
// Commercial  Computer  Software,  Computer Software  Documentation,  and
// Technical Data for Commercial Items are licensed to the U.S. Government
// under vendor's standard commercial license.
//

//  Facility:	GEM
//
//  Abstract:
//
//	External interface to basic block database support code.
//
//  Authors:	Gene Albert
//
//  Creation Date:   23 Jul 1997
//
//  Modification History:
//
//  001   15 Aug 1997	ega	Initial coding.
//
//  002    9 Oct 1997	ega	Further development, including
//				Moving type and constant defs to gem_bb_defs.hxx
//
//  003   30 Oct 1997	ega	Further development, including
//				Enum for status codes for gem_bb_read_database
//				Enum for ranking (not yet in use)
//				Copious comments for use as an API
//
//  004   12 Nov 1997	ega	Cleanup API and bbdump interface.
//				Make sure it compiles standalone.
//
//  005   20 Nov 1997	ega	Make use of GEM_BB_RANK
//				widen count paths to GEM__IMAX
//				Add:
//				    gem_bb_dump_invalid_counts
//				    gem_bb_dump_orphans
//
//  006    6 Jan 1998	ega     Added routines for use by om:
//				    gem_bb_rtn_get_obblen
//				    gem_bb_rtn_get_obbs
//				    gem_bb_rtn_get_offset
//				And routines for general use:
//				    gem_bb_obb_has_mappings
//
//  007   18 Feb 1998	ega     Added lots of API documentation.
//				Added GEM_BB_DB abstract data type,
//				and routines to manipulate instances:
//				    gem_bb_close_database
//				    gem_bb_create_database
//				    gem_bb_free_database
//				    gem_bb_open_database
//				    gem_bb_update_database
//				    gem_bb_use_database
//				Added GEM_BB_PROFILE abstract data type,
//				and routines to manipulate instances:
//				    gem_bb_close_profile
//				    gem_bb_read_pixie_profile
//				    gem_bb_use_pixie_profile
//				Added miscellaneous routines:
//				    gem_bb_dump_summary
//				    gem_bb_find_rtn_by_offset
//				    gem_bb_rtn_get_modid
//				    gem_bb_set_dump_flags
//				Modified the interface to:
//				    gem_bb_read_database
//				    gem_bb_find_rtn_by_name
//				    gem_bb_fini
//				    gem_bb_initialize_ranking
//				Split conditionally compiles main() for
//				bbtool into a separate file.
//
//  008    2 Apr 1998	ega	Added support for pseudo SBBs, including
//				    gem_bb_rtn_has_valid_counts
//				    gem_bb_update_mappings
//
//  009   16 Apr 1998	ega	Improve memory management of an in-memory database
//				Changed interfaces to:
//				    gem_bb_init
//				    gem_bb_dump_summary
//
//  010   23 Apr 1998	ega	Changes to better support om, prof, and the driver.
//
//  011    4 Jun 1998	ega	Added gem_bb_rtn_match_obbs
//
//  012   15 Jun 1998	ega	Added dump_dec_offset parameter to gem_bb_set_dump_flags
//
//  012   18 Jun 1998	ega	Make .hxx directly usable by .c files
//
//  013   20 Jul 1998	ega	Added gem_bb_rtn_has_name_collision
//				Moved the typedefs for the enums after the enums.
//
//  014   15 Oct 1998	ega	Added gem_bb_remove_database (for bbtool).
//
//  015   10 Nov 1998	ega 	Added add_counts parameter to gem_bb_obb_merge
//				
//  016   13 Nov 1998	ega	Add gem_bb_obb_remove_mappings
//				
//  017   22 Dec 1998	ega	Add gem_bb_rtn_replace_obbs
//
//  018   18 Dec 1998	kdg	Rename GEM__IADDR/GEM__UADDR/GEM__IMAX/GEM__UMAX
//
//  019    5 Jan 1999	ega	Change gem_bb_rtn_replace_obbs to return success/fail.
//
//  020   12 Aug 1999	ega	To support feedback for opal:
//				   has_counts & counts parameters for gem_bb_rtn_create_sbbs
//				   gem_bb_get_ranking
//				   gem_bb_set_ranking
//
//  021   28 Sep 1999	ega	Fix typo in description of gem_bb_find_rtn_by_offset
//
//  022   13 Jan 2000	ega	Added:
//				   gem_bb_dump_ranking
//				   gem_bb_get_text_size
//				   gem_bb_set_debug_flags (API only)
//				   GEM_BB_DBG bit vector (API only)
//				   GEM_BB_READ bit vector
//				Changed
//				   gem_bb_read_database (2nd arg is now GEM_BB_READ)
//
//  023   28 Feb 2000	ega     bbtool -sbbfil and -obbfil options, and top 6% ranking.
//
//  024   15 Mar 2000	ega     Add routines to allow bbtool to iterate over a database
//
//  025   29 Mar 2000	ega     GB 8672: Add traces for new hash tables
//
//  026   24 May 2000   dkk     Add support for combining profiles.
//
//  027    5 Jun 2000	ega	Added support for deferred (lazy) reading of database:
//				    various new GEM_BB_READ flags
//				    gem_bb_rtn_is_deferred
//				    gem_bb_rtn_evaluate
//				    gem_bb_rtn_dismiss
//				    (see "support for deferred evaluation" in this file)
//				Modified interfaces to:
//				    gem_bb_dump_database
//				    gem_bb_initialize_ranking
//				    gem_bb_compute_sbb_counts
//				    gem_bb_rtn_parse_io_buffer
//				Added GEM_BB_SBB and various interface routines:
//				    gem_bb_rtn_get_sbblen
//				    gem_bb_rtn_get_sbb
//				    gem_bb_sbb_get_line
//				    gem_bb_sbb_get_count
//				Added miscellaneous routines:
//				    gem_bb_rtn_get_filename
//				    gem_bb_rtn_get_linenum
//				    gem_bb_obb_get_seqid
//				    gem_bb_rtn_get_all_counts
// 
//  028    7 Jun 2000	ega	Fix prototypes for gem_bb_sbb_get_{count,line}
// 
//  029   19 Jun 2000	ega	Added support for instruction events (GEM_BB_EVE)
//				Renamed:
//				    gem_bb_dump_rtn  to gem_bb_rtn_dump
//				    gem_bb_dump_obbs to gem_bb_rtn_dump_obbs
//				Added
//				    gem_bb_dump_eve
//				    gem_bb_dump_obb
//				    gem_bb_dump_sbb
// 
//  030   22 Jun 2000	ega	Add support for SBB successors.
//				This includes adding predsuccs[] parameters to:
//				    gem_bb_rtn_create_sbbs
//				    gem_bb_rtn_match_sbbs
// 
//  031    5 Jul 2000	ega	GB 8828: Add support for merging redundant sbbs
// 
//  032    6 Jul 2000	ega	Removing gem_bb_update_mappings
// 
//  033   19 Jul 2000	ega	Add typedef for GEM_BB_EVT (needed to include this
//				from a .c file, as is done by om, prof, and dcpi2bb)
//
//  034   16 Aug 2000	ega	Added:
//				  gem_bb_add_profile (cloned from gem_bb_read_database)
//				  gem_bb_rtn_get_first_obb
//				  gem_bb_obb_get_next_obb
//
//  035    6 Sep 2000	ega	Added support for bbtool & spike:
//				  gem_bb_rtn_get_size
//				  gem_bb_remove_events
//
//  036   27 Sep 2000	ega	Added:
//				  gem_bb_get_version - for versioning
//				  gem_bb_get_successors - for bbtool annotations
//				Change interfaces to:
//				  gem_bb_obb_get_events
//				  gem_bb_init
//				  gem_bb_initialize_ranking
//				  gem_bb_find_rtn_by_name
//				  gem_bb_remove_counts
//				  gem_bb_remove_counts
//				  gem_bb_compute_sbb_counts
//				Changed:
//				  gem_bb_create_database to gem_bb_db_create
//				Made private:
//				  gem_bb_rtn_parse_io_buffer
//
//  037    3 Oct 2000	ega	Add more DCPI events for Spike.
//
//  038   10 Oct 2000	ega	Add support for split procedures
//				    gem_bb_obb_get_size
//				    gem_bb_obb_set_size
//				    gem_bb_rtn_get_split
//				    gem_bb_rtn_set_split
//				Add support for GEM listing annotations
//				    gem_bb_sbb_get_succ_str
//
//  039   17 Oct 2000	ega	Add READ_ADD_SHADOWS option to gem_bb_read_database
//				Add API documentation
//
//  040   24 Oct 2000	ega	Change gem_bb_get_version interface.
//
//  041    5 Dec 2000	ega	Change conditional compilation to make OS
//				build go more smoothly, especially building spike
//  
//  042   12 Feb 2001   dkk	Add gem_bb_rtn_set_src_count
//  
//  043   28 Feb 2001   ega	Reduce in-memory database size:
//				    add READ_NO_SBBS (exclude all SBB info)
//				    gem_bb_remove_sbbs (used by bbtool -rmshadow)
//                              Support for dcpi2bb:
//				    gem_bb_add_profile_start
//				    gem_bb_add_profile_finish
//				    gem_bb_add_missing
//				Support for ProfileMe events
//				    add READ_DO_ESLI (process ESLI information)
//
//  044   31 May 2001   ega	Support for ProfileMe events
//				    make ESLI reading automatic
//					eliminate READ_DO_ESLI
//				        add GEM_BB_ERR_K_NEEDS_ESLI
//				    gem_bb_eve_get_opname
//				    gem_bb_compute_event_totals
//				    gem_bb_eve_dump_list
//				    gem_bb_eve_get_encoding
//				    gem_bb_get_text_offset
//				    gem_bb_rtn_extract_events
//				    gem_bb_rtn_has_insn_events
//
//  045    6 Jun 2001	ega	Added gem_bb_rtn_get_source_count
//
//  046   21 Jun 2001   ega	Support for bbtool -ann pragma:
//				    gem_bb_sbb_get_predecessors 
//				    gem_bb_rtn_create_sbb_preds
//				    gem_bb_sbb_get_annotation
//				    annotations[] arg for
//					gem_bb_rtn_match_sbbs
//					gem_bb_rtn_create_sbbs


// This package can be used in GEM or outside of GEM.  If outside of gem,
// typedefs are needed for things that come from the GEM environment.
//
// We use GEM_ENVIRONMENT and SPIKE_ENVIRONMENT to determine where these
// definitions will come from.  We had previously required that non-gem
// users define NO_GEM.  This is no longer necessary, since NO_GEM is keyed off
// of GEM_ENVIROMENT.  (The libbb build still needs it for the time being, however).
//
// Spike has special requirements because it has one foot in the GEM environment
// and one foot in the ODE environment.

// GEM_ENVIRONMENT is only defined in C++ files in GEM.  We define it here
// for bliss.  (All bliss compiles are within GEM, of course.)
//
#if defined(__bliss__)
%if not %declared(%quote GEM_ENVIRONMENT) %then
macro GEM_ENVIRONMENT = 1 %;
%fi
#endif

// Here we tie NO_GEM to GEM_ENVIRONMENT and SPIKE_ENVIRONMENT.
//
#if defined(SPIKE_ENVIRONMENT) || ! defined(GEM_ENVIRONMENT)
#define NO_GEM 1
#endif

// Spike uses libbb.a, and therefore wants to include gem_bb.hxx with NO_GEM defined,
// but gets GEM definitions from the GEM sources.  (The conditional compilation
// surrounding the include of gem_epilog.h at the end of this file must be the same.)
//
#if defined(SPIKE_ENVIRONMENT) || ! defined(NO_GEM)

#include <gem_prolog.h>

#include <gem_vm.hxx>

#else

typedef short			GEM_BOOLEAN;
typedef signed long		GEM_IMAX;
typedef unsigned long		GEM_UMAX;

typedef int			GEM_INT;
typedef unsigned int		GEM_UINT;

typedef char			GEM_INT8;	/* 8 bit signed integer */
typedef unsigned char		GEM_UINT8;	/* 8 bit unsigned integer */

typedef short			GEM_INT16;	/* 16 bit signed integer */
typedef unsigned short		GEM_UINT16;	/* 16 bit unsigned integer */

typedef int			GEM_INT32;	/* 32 bit signed integer */
typedef unsigned int		GEM_UINT32;	/* 32 bit unsigned integer */

typedef char			*GEM_STR;

typedef int			*GEM_ZONE;

// Boolean support.  (This mimics gem_def.h)

#ifdef true
#undef true
#endif
#define true 1

#ifdef false
#undef false
#endif
#define false 0

#endif


// Description of the GEM_BB package by topics:
//
// The API for this package is described in this header file.  Descriptions
// include:
//
//	constant, enum, and type declarations
//
//	package initialization and shutdown
//
//	manipulating a database (GEM_BB_DB objects):
//
// 		creating a database
//
//		releasing and freeing a database
//
//		reading an existing database
//
// 		writing out a database
//
//		support for deferred evaluation of a database
//
//		support for relative execution counts (ranking)
//
//		visiting the elements of a database
//
//	adding a profile to the database
//
//	manipulating profiles (GEM_BB_PROFILE objects)
//
// 	manipulating routine entries (GEM_BB_RTN objects)
//
//		sorting OBBs (including the concept of a sequence id)
//
//	support for manipulating basic block entries (GEM_BB_OBB objects)
//
//	support for manipulating instruction events (GEM_BB_EVE objects)
//
//	support for manipulating source basic blocks (GEM_BB_SBB objects)
//
//	debugging support (dump and integrity check routines)
//
//	support for database version stamps
//
// Following these descriptions is an alphabetical listing of routines
// with prototypes and detailed descriptions.


// Constant, enum, and type declarations:
//
// The constant and type declarations supplied by this package are:
//
// constants:
//
//	GEM_BB_INVALID	- a constant used for invalid values
//
// enumerations:
//
//	GEM_BB_ERR	- return value for I/O operations
//	GEM_BB_RANK	- relative frequencies
//	GEM_BB_READ	- I/O options
//	GEM_BB_DBG	- debugging options
//	GEM_BB_INIT_FLAGS - package initialization options
//	GEM_BB_EVT	- event types
//
// types:
//
//	GEM_BB_DB	- a database handle
//	GEM_BB_RTN	- a routine handle
//	GEM_BB_SBB	- a source basic block (SBB) handle
//	GEM_BB_OBB	- an object basic block (OBB) handle
//	GEM_BB_EVE	- an instruction event (EVE) handle
//      GEM_BB_PROFILE	- a profile handle
//
// To reduce module recompilation in the GEM environment, some of these
// are defined in gem_bb_defs.hxx.  Outside of the GEM, all of these are
// defined here.

#ifndef NO_GEM
#include <gem_bb_defs.hxx>
#endif


// GEM_BB_INVALID indicates an invalid value.  It is used in places
// where zero is a valid value, such as:
//
//	an invalid execution count
//
//	an invalid array index
//
// Is is not expected to be used for pointer values (including abstract
// handles defined as void *), where NULL indicates and invalid value.

#ifdef NO_GEM
#define GEM_BB_INVALID -1
#endif


// GEM_BB_ERR is an enumeration used to return an error status.
// It is used by various database and profile manipulation routines, 
// including gem_bb_read_database.

enum GEM_BB_ERR {
    GEM_BB_ERR_K_SUCCESS = 1,
	GEM_BB_ERR_K__FIRST = GEM_BB_ERR_K_SUCCESS,

    GEM_BB_ERR_K_NOPROFILE,	// The Count and Addr files are missing
				// (but the database is usable)

    GEM_BB_ERR_K_NOMERGE,	// The database to merge was missing

    GEM_BB_ERR_K_NODBFIL,	// The database, Count, or Addr file
    GEM_BB_ERR_K_NOCNTFIL,	// is missing
    GEM_BB_ERR_K_NOADDRFIL,

    GEM_BB_ERR_K_BADDBTYP,	// The database, Count, or Addr file
    GEM_BB_ERR_K_BADCNTTYP,	// is the wrong type of file
    GEM_BB_ERR_K_BADADDRTYP,

    GEM_BB_ERR_K_BADDBDAT,	// The database, Count, or Addr file
    GEM_BB_ERR_K_BADCNTDAT,	// contains bad data
    GEM_BB_ERR_K_BADADDRDAT,

    GEM_BB_ERR_K_NODBDAT,	// No database in database file
    GEM_BB_ERR_K_NEWDBDAT,	// Database is present, but is newer version

    GEM_BB_ERR_K_DBADDR_MISMATCH, // The database and Addr files
				  // don't match

    GEM_BB_ERR_K_CNTADDR_MISMATCH, // The Count and Addr files
				   // don't match

    GEM_BB_ERR_K_NEEDS_ESLI,	// Special value 

	GEM_BB_ERR_K__COUNT,
	GEM_BB_ERR_K__LAST = GEM_BB_ERR_K__COUNT - 1
};

#ifdef NO_GEM

#ifndef __cplusplus
typedef enum GEM_BB_ERR GEM_BB_ERR;
#endif

#endif


// GEM_BB_INIT_FLAGS is a bit mask passed to gem_bb_init
//
typedef GEM_IMAX GEM_BB_INIT_FLAGS;

enum {

    INIT_NULL = 0,

    INIT_TOLERATE_SKEW = 0x1,		// Tolerate version skew if read is successful
					// (used for testing)

    INIT_WRITE_VP_FORMAT = 0x2,		// Write current version + 1
					// (artificial version skew for testing)

    INIT_WRITE_V1_FORMAT = 0x4		// Write only version 1 attributes

};


// GEM_BB_READ is a bit mask passed to gem_bb_read_database, gem_bb_add_profile,
//
typedef GEM_IMAX GEM_BB_READ;

enum {

    READ_NULL = 0,

    READ_ADD_MISSING = 0x1,	// Add missing entries using symbol table
				//   and, if present, profile

    READ_DB_OPTIONAL = 0x2,	// Continue processing even if no database was found.
    				//   This is used by Spike to process -g0 executables.

    READ_DO_ALTENTS = 0x4,	// Treat alternate entry points like full routines
				//   The main results of this is that each alternate
				//   entry will be apportioned its part of the main
				//   routines basic blocks in adding missing entries.

    COMBINE_OVERRIDE = 0x8,     // -combine option used to override the old data base
                                //   with a new database.

    COMBINE_ADD = 0x10,         // -combine option used to merge to databases by
                                //   adding their counts together. 

    COMBINE_SCALE = 0x20,       // -combine option used to merge a scaled database
                                //   into another one.

    READ_DO_DEFER = 0x40,	// Defer the read of individual routines until they
				//   are looked up with one of the find_rtn_by calls

    READ_ADD_SHADOWS = 0x80,	// Create shadow SBBs for all items without SBBs
				//   (items that were added from libraries)

    READ_NO_SBBS = 0x100	// Do not read any of the SBB information:
				//   sbbs, sbb preds, shadow sbbs, obb->sbb maps
				//   If database is updated, all SBB info will be lost

};


// GEM_BB_DBG is a bit mask passed to gem_bb_set_debug_flags.
//   This is only used by the API, as a replacement for the GEM trace
//   and switch facilities.
//
typedef GEM_IMAX GEM_BB_DBG;

enum {

    DBG_NULL		= 0,	 // Do nothing

    DBG_DUMP_NODEADDR	= 0x1,	 // Dump addresses of bb_rtns, bb_obbs, etc.
    DBG_DUMP_BYTE_OFFSET= 0x2,	 // Dump offsets in byte units (default is instructions)
    DBG_DUMP_DEC_OFFSET = 0x4,	 // Dump offsets in decimal (default is hex)
    DBG_DUMP_COUNTS_ONLY= 0x8,	 // Format dump for diffs

    DBG_TRACE_CHANGE	= 0x10,	 // Trace events which change the database
    DBG_TRACE_CHECK	= 0x20,	 // Perform integrity checks on the database
    DBG_TRACE_COMBINE   = 0x40,  // Trace db combine operations
    DBG_TRACE_IO	= 0x80,	 // Dump persistent format of databases

    DBG_TRACE_MATCH	= 0x100, // Trace db/symtab & db/profile matching
    DBG_TRACE_MERGE	= 0x200, // Trace db merge operations
    DBG_TRACE_RANK	= 0x400, // Trace histogram creation & results
    DBG_TRACE_PROFILE	= 0x800, // Dump the profile in raw form.

    DBG_TRACE_REORDER	= 0x1000, // Trace obb reordering operations
    DBG_LAZY_REFERENCES = 0x2000, // Don't resolve references
    DBG_RANK_N_BLOCKS   = 0x4000, // Use # of basic blocks rather than number of
				  // instructions in generating ranking 
    DBG_IGNORE_SEQID    = 0x8000, // Ignore assertions concerning sequence ids

    DBG_TRACE_WEIGHT	= 0x10000,  //
    DBG_USE_NEW_WEIGHT	= 0x20000,  //
    DBG_TRACE_NAME	= 0x40000,  //
    DBG_TRACE_OFFSET	= 0x80000,  //

    DBG_TRACE_HASH	= 0x100000,  //
    DBG_NO_RECYCLE	= 0x200000,  //
    DBG_TRACE_ALLOC	= 0x400000,  //
    DBG_TRACE_LEAK	= 0x800000,  //

    DBG_TRACE_ESLI	= 0x1000000, //

    DBG_DUMP_TEXTADDR	= 0x2000000  //

};


// GEM_BB_EVT is an enumeration used in the instruction event (GEM_BB_EVE)
// interface.  (The array event_type_name in gem_bb.cxx should be updated
// whenever changes are made to this enumeration.)
//

enum GEM_BB_EVT {
    GEM_BB_EVT_K_RETDELAY = 1,	// Average retire delay for an instruction
				// Taken from the ProfileMe retdelay counter.

	GEM_BB_EVT_K__FIRST = GEM_BB_EVT_K_RETDELAY,

    GEM_BB_EVT_K_MISPREDICT,	// Number of times a conditional branch
				// mispredicts.  Taken from the ProfileMe
				// cbrmispredict bit and mispredict trap bit.

    GEM_BB_EVT_K_MAPSTALL,	// Instruction stalled after it was fetched
				// and before it was mapped.  This indicates
				// a resource shortage (physical registers).
				// Taken from the ProfileMe map_stall bit.

    GEM_BB_EVT_K_NYP,		// Not Yet Prefetched.  This is a useful
				// approximation to i-cache miss.
				// Taken from the ProfileMe NYP bit.

    GEM_BB_EVT_K_REPLAYTRAP,	// Generic replay trap
				// Taken from the replays trab bit.

    GEM_BB_EVT_K_LDSTORDER,	// Replay trap was caused by load store
				// order, troll trap, or simultaneous load
				// and store.  Taken from the ProfileMe
				// ldstorder bit.

    GEM_BB_EVT_K_LOADLATENCY,	// Load latency distribution.  This is a
				// complex attribute, where values are an
				// array ordered pairs: (count, cycle-delay).
				// Values can be clustered to correspond to
				// cache levels, including off-chip memory
				// references for Wildfire.  This information
				// is derived from using DCPI with value
				// profiling.  For a rough approximation of 
				// the average load latency, use RETDELAY. 

    GEM_BB_EVT_K_TAKEN,		// Branch taken. From the ProfileMe taken bit.

    GEM_BB_EVT_K_RETIRED,	// The instruction retired.

    GEM_BB_EVT_K_UNALIGNTRAP,	// The instruction caused an unaligned load or store.

    GEM_BB_EVT_K_DTBMISS,	// The instruction caused a DTB single miss.

    GEM_BB_EVT_K_DTB2MISS3,	// The instruction caused a DTB double miss. (3-level page tables)

    GEM_BB_EVT_K_DTB2MISS4,	// The instruction caused a DTB double miss. (4-level page tables)

    GEM_BB_EVT_K_ITBMISS,	// The instruction caused an Instruction TLB miss.

    GEM_BB_EVT_K_ARITHTRAP,	// The instruction caused an arithmetic trap.

	GEM_BB_EVT_K__COUNT,
	GEM_BB_EVT_K__LAST = GEM_BB_EVT_K__COUNT - 1
};

#ifdef NO_GEM

#ifndef __cplusplus
typedef enum GEM_BB_EVT GEM_BB_EVT;
#endif

#endif


// GEM_BB_RANK is an enumeration used to rank execution counts of basic
// blocks relative to the execution counts of other basic blocks.
//
// It is ordered such that more important ranks are given higher values.

#ifdef NO_GEM

enum GEM_BB_RANK {
    GEM_BB_RANK_K_INVALID = 1,		// Unable to compute a value
	GEM_BB_RANK_K__FIRST = GEM_BB_RANK_K_INVALID,

    GEM_BB_RANK_K_BOTTOM,		// The rest
    GEM_BB_RANK_K_TOP_32_PERCENT,	// Top 32%
    GEM_BB_RANK_K_TOP_16_PERCENT,	// Top 16%
    GEM_BB_RANK_K_TOP_8_PERCENT,	// Top 8%
    GEM_BB_RANK_K_TOP_6_PERCENT,	// Top 6%
    GEM_BB_RANK_K_TOP_4_PERCENT,	// Top 4%
    GEM_BB_RANK_K_TOP_2_PERCENT,	// Top 2%
    GEM_BB_RANK_K_TOP_1_PERCENT,	// Top 1%

	GEM_BB_RANK_K__COUNT,
	GEM_BB_RANK_K__LAST = GEM_BB_RANK_K__COUNT - 1
};

#ifndef __cplusplus
typedef enum GEM_BB_RANK GEM_BB_RANK;
#endif

#endif


// GEM_BB_DB is a opaque handle to a database.  The database can be in various
// states:
//
//     persistent form:
//		on disk   - a valid file name and/or file descriptor
//     		in memory - a valid memory mapped database in persistent form
//
//     in memory form	  - a valid list of routine entries
//
// The various forms are managed by the open_database, read_database,
// remove_database, write_database, and close_database routines.
//
// The in memory form can also be used with various other routines
// (dump_database, check_database, etc.).
//
// The in memory form can have individual routine entries that are still in
// persistent form.  These must be undeferred before they can be accessed.
// (See the section on deferred evaluation.)
//
#ifdef NO_GEM
typedef void	*GEM_BB_DB;
#endif


// GEM_BB_RTN is the opaque handle to routine entries in the basic block
// database.
//
//	Routine entries in the same database are linked together.
//
//	Operations are performed on the database as a whole by
//	passing in the first of these linked entries.  This is
//	either the entry returned by gem_bb_read_database, or the
//	entry returned by the first call to gem_bb_rtn_create.
//
//	Access routines are available for the following GEM_BB_RTN
//	attributes:
//
//	    count - an execution count
//
//	    weight - a weighted version of the execution count
//
//	    is_modified - a flag indicating if a routine entry has
//		been modified since it was read in.
//
//	Access routines are also available for structural components
//	of GEM_BB_RTNs:
//
//	    the reference table
//
//	    the SBB table
//
//	    the OBB table

#ifdef NO_GEM
typedef void	*GEM_BB_RTN;
#endif


// GEM_BB_SBB is the opaque handle to source basic block entries in the 
// basic block database.
//
//	Access routines are available for the following GEM_BB_SBB
//	attributes:
//
//	    count - an execution count
//
//	    line  - the line number of the SBB

#ifdef NO_GEM
typedef void	*GEM_BB_SBB;
#endif


// GEM_BB_OBB is the opaque handle to object basic block entries in the 
// basic block database.
//
//	Access routines are available for the following GEM_BB_OBB
//	attributes:
//
//	    count  - an execution count
//
//	    offset - the instruction offset of the OBB
//
//	    sequence id - the ordinal position of this OBB in the
//		OBB list for this routine.
//
//	    is_weak - a flag used in matching OBBs to other representations
//		of the executable (e.g., a profile).
//
//	    count_fuzz - a fudge-factor used in recreating SBB counts
//		(compiler only)
//	    
//	Access routines are also available for structural components
//	of GEM_BB_OBBs:
//
//	    the mapping table
//
//	    the event list (GEM_BB_EVE)

#ifdef NO_GEM
typedef void	*GEM_BB_OBB;
#endif


// GEM_BB_EVE is the opaque handle to an instruction event in the 
// basic block database.
//
//	Access routines are available for the following GEM_BB_EVE
//	attributes:
//
//	    offset - the offset from the start of the OBB
//
//	    position - the source position
//
//	    type - an element in the GEM_BB_EVT enumeration
//
//	    is_complex - indicates whether the event has a single
//		value or multiple values
//
//	    value - a single value (for simple events)
//
//	    length - the number of values (for complex events)
//
//	    values - the N values (for complex values)
//	    

#ifdef NO_GEM
typedef void	*GEM_BB_EVE;
#endif


// GEM_BB_PROFILE is the opaque handle to profile information to be added to
// a basic block database.
//

#ifdef NO_GEM
typedef void	*GEM_BB_PROFILE;
#endif


// Package initialization and shutdown:
//
//   The routines which support package initialization and shutdown are:
//
//	gem_bb_init	- Initialize the package
//			  call this before any other routine is called 
//
//	gem_bb_fini	- Shutdown the package
//			  call this after the database is no longer needed
//


// Manipulating a database - creating a database:
//
//   The routines which support creation of a new database are:
//
//	gem_bb_create_database - create a new database
//
//	gem_bb_rtn_create - Create a new routine entry
//
//	gem_bb_rtn_create_sbbs - Create a new SBB table
//
//	gem_bb_rtn_create_obbs - Create a new OBB table isomorphic to SBB table
//	
//	gem_bb_obb_create - Create a new OBB


// Manipulating a database - releasing and freeing a database:
//
//	gem_bb_close_database - close a database
//
//	gem_bb_free_database - free a database
//
//  The former routine closes a persistent form of the database.  It closes all
//  file handles and releases memory used for the persistent form.
//
//  The latter routine closes an in-memory form of the database.


// Manipulating a database - reading an existing database:
//
//   The routines which support reading of a database are:
//
//	gem_bb_open_database - open an existing database in persistent form
//
//	gem_bb_use_database - use memory mapped region for database read/write
//
//	gem_bb_read_database - Read in a database from a file
//			       First step in reading in a database
//
//	gem_bb_compute_sbb_counts - Compute SBB counts from OBB counts
//
//	gem_bb_find_rtn_by_name - Lookup a routine in the database by names
//
//	gem_bb_find_rtn_by_offset - Lookup a routine by it's instruction offset
//				    from the start of .text
//
//	gem_bb_rtn_has_name_collision - Recognizes if a bb_rtn was accidentally
//				        matched on multiple occasions
//
//	gem_bb_rtn_match_sbbs - Match the source blocks with the original
//				source, matching line numbers
//
//	gem_bb_rtn_match_obbs - Match the OBBs to the application's view
//				of basic blocks
//
//	gem_bb_rtn_replace_obbs - Replace the OBBs with the application's
//				  view of basic blocks
//
//	gem_bb_rtn_get_obblen - get the number of OBBs in a routine
//
//	gem_bb_rtn_get_obbs - get all of the obbs (and their offsets)
//
//   Note:  there is no separate predicate to test that a file contains
//   a database.  To test this, gem_bb_open_database (or gem_bb_use_database)
//   and gem_bb_read_database must be used.  (The latter must not be called
//   with the READ_ADD_MISSING flag.)
//
//   Reading in a database involves two steps:
//
//   1. Reading the database
//
//	Reading a database is the process of transforming a database
//	from persistent form to in-memory form.
//
//	The first step is to establish the database.  This is done with
//	a call to either gem_bb_open_database() or gem_bb_use_database().
//	The former lets API to handle file I/O.  The latter is used if the
//	application already has the persistent form of the database
//	in memory, in which case a pointer to this container is all that
//	is needed to establish the database.  This is typically the case
//	for executable editors, since the symbol table is the container.
//
//	The second step is to translate the database from persistent form
//	to in-memory form.  This is done by gem_bb_read_database().  Both
//	compilers and executable editors use gem_bb_read_database to read 
//	a database.  This routine has these options:
//
//	    integrating a profile into the database:
//
//		An independent pixie-style profile can be integrated with the
//		database.  This is done by establishing the profile with
//		gem_bb_use_pixie_profile() or gem_bb_read_pixie_profile(), and
//		passing this profile to gem_bb_read_database().  Once this has
//		been done, the profile can be released with
//		gem_bb_close_profile().
//
//	    creating database entries for missing routines:
//
//		Routines that have not been compiled -feedback will not
//		have database entries.  Entries are added for routines
//		in the symbol table but not in the database.  If pixie
//		counts are being integrated, this information will be
//		used to generate OBBs for the routine.
//		
//	    merging counts from one database into another
//
//		Counts may be missing from a new database for a new executable.
//		This option merges counts from an older version of the executable
//		into the newer executables database.  In this case, two databases
//		are established (opened), and passed to gem_bb_read_database.
//		Once this has been done, the merge database can be released and
//		freed with gem_bb_close_database() and gem_bb_free_database().
//
//   2. Establishing a correspondence between the database and the
//	application's internal representation
//
//	Name-based routine correspondence:
//
//	Compilers match routine entries in the database to the source
//	program with gem_bb_find_rtn_by_name. This lookup is string-based,
//      and makes use of a hash table.
//
//	For global routines, routine name and source file name are a unique
//	key.  However, for local routines this is not unique.  For example,
//	the C++ idiom of declaring a local routine in a header file can
//	lead to numerous instantiations of a routine with the same name and
//	source file name.
//	
//	Collisions are resolved with the module id.  [ This is still not
//	unique.  There is a need for an object id too. ]
//
//	Offset-based routine correspondence:
//
//	Executable editors match routine entries in the database to
//	the executable with gem_bb_find_rtn_by_offset.  This routine uses
//	the offset (in instructions) of the start of a routine from the
//	start of the .text section.
//
//	SBB correspondence:
//
//	Compilers match the SBBs to their internal representation of the
//	source program with gem_bb_rtn_match_sbbs(), which uses source line
//	numbers to perform its match.  Before calling the matching routine,
//	compilers first call gem_bb_compute_sbb_counts() to compute the SBB
//	counts from the OBB counts.
//
//	Once a compiler has established a correspondence between its IR and
//	the SBBs, it regenerates the OBBs from the SBBs using
//	gem_bb_rtn_create_obbs().
//
//	OBB correspondence:
//
//	Executable editors match the OBBS to their internal representation
//	of the executable by:
//	   - determining how many basic blocks they have in their representation
//	   - allocating two vectors of this size (offsets and obbs)
//	   - filling in the offsets vector (relative offsets, i.e., first is 0)
//	   - calling gem_bb_rtn_match_obbs
//	   - if this fails, calling gem_bb_rtn_replace_obbs
//	The match can fail for library routines that have not yet been added
//	to the database.  This adds them to the database.
//
//	An alternative method is to call gem_bb_rtn_get_obbs, which returns
//	vectors of OBB handles and a vector of OBB offsets.  The offsets are
//	relative to the start of the routine.  They can be made relative to
//	the start of the text section by adding in the return value of
//	gem_bb_rtn_get_offset().  In order to use gem_bb_rtn_get_obbs,
//	first call gem_bb_rtn_get_obblen() and allocate two vectors (offsets
//	and obbs).


// Manipulating a database - writing out a database:
//
//   The routines which support writing out a database are:
//
//	gem_bb_rtn_reuse_if_unmodified - Has rtn changed since is was read in?
//
//	gem_bb_rtn_populate_io_buffer - Populate IO buffer with persistent
//                                form of routine entry
//
//	gem_bb_rtn_set_fileid	- Set the file descriptor index for the routine
//
//	gem_bb_rtn_set_procid	- Set the symbol table index for the routine
//
//	gem_bb_write_database	- Update the persistent form of a database
//				  (not avaliable in GEM version of API)
//
//	gem_bb_write_database_to_file - Write out a database to a file
//					(API developers only)
//
//   The routine which supports removing a database from a file is:
//
//      gem_bb_remove_database - remove a database from a file
//
//   For both compilers and executable editors, gem_bb_rtn_populate_io_buffer
//   is the means by which persistent forms of routine entries are created.
//
//   Before this routine is called, the fileid and procid must be set for
//   all routine entries in the database, using gem_bb_rtn_set_fileid and
//   gem_bb_rtn_set_procid.
//
//   For executable editors, this process is complicated by the presence
//   of a preexisting database entry for the routine.  As the executable
//   is written out, stale entries must be removed and replaced.
//
//   Entries are stale if any of the following is true:
//
//	1. File descriptor or local symbol table indexes have changed
//
//	   It is up to the user of this package to know if this is true.
//	   If it is true, every fileid and procid must be reset.
//
//	2. gem_bb_rtn_has_changed returns true.
//


// Manipulating a database - support for deferred evaluation of routines:
//
//   A database can be read in with deferred or immediate evaluation of
//   routine entries:
//
//	Immediate evaluation is the default.
//
//	Deferred evaluation is chosen by indicating the READ_DO_DEFER flag
//	in the call to gem_bb_read_database.
//
//   A database which has been read in with READ_DO_DEFER specified has
//   the following operations defined on rtn entries:
//
//	gem_bb_rtn_is_deferred - predicate to ask if a routine is deferred
//	gem_bb_rtn_evaluate    - evaluate a deferred routine
//	gem_bb_rtn_dismiss     - dismiss an active routine (return it to a
//				 deferred state), possibly updating it if
//				 has been changed.
//
//   Finding GEM_BB_RTN entries in a database is supported for deferred
//   rtn entries:
//
//	gem_bb_find_rtn_by_offset - leaves the rtn in a deferred state
//	gem_bb_find_rtn_by_name   - evaluates the rtn
//	gem_bb_get_first_rtn      - leaves the rtn in a deferred state
//	gem_bb_get_next_rtn       - leaves the rtn in a deferred state
//   
//   There are a few operations on rtn entries that will still work on
//   deferred entries:
//
//	gem_bb_rtn_get_offset   - leaves the rtn in a deferred state
//	gem_bb_rtn_get_name     - leaves the rtn in a deferred state
//	gem_bb_rtn_get_filename - leaves the rtn in a deferred state
// 	gem_bb_rtn_get_all_counts - evaluates the routine, but returns
//				    it to a deferred state.
//
//   The last of these is particularly important:
//
//	gem_bb_rtn_get_all_counts - get all of the count and weight
//				    information associated with a rtn
//				    entry.  If the entry were in a
//				    deferred state, it will still be
//				    in a deferred state after this call.
//
//   Nearly all other operations on rtn entries require that the entry be
//   evaluated before the operation can be performed.  They will return
//   silently in production environments, but assert in debug environments.
//
//   The following routines force evaluation of all rtn entries in the
//   database:
//
//	gem_bb_compute_sbb_counts
//	gem_bb_initialize_ranking
//	gem_bb_remove_counts
//
//   In addition, all routines are undeferred if gem_bb_read_database is
//   used to merge two databases or add a profile to a database.
//
//   Other operations which work on the database as a whole, such as
//   gem_bb_resolve_references, will skip deferred routines.


// Manipulating a database - support for relative execution counts (ranking):
//
//   The routines which support relative execution counts are:
//
//      gem_bb_initialize_ranking - Create the execution count histogram
//
//	gem_bb_compute_rank - Compute relative rank from raw count
//
//	gem_bb_rtn_get_weight - get weighted count for a routine
//
//	    compute relative frequencies
//
//   A histogram of frequencies can be created to establish a means
//   of comparing the relative importance of frequencies.  This can
//   be used to answer questions like "is 10000 a lot of executions?".
//
//   There are two routines which can help with preserving the relative ranking
//   across extraordinary barriers.  For example, the compiler uses this to
//   generate an OPAL dump that can later be read in by an opal compiler.
//
//	gem_bb_get_ranking - Return the execution count histogram
//
//	gem_bb_set_ranking - Set the execution count histogram to a given value


// Manipulating a database - visiting the elements of a database
//
//   Given a database object (GEM_BB_DB), one can visit all of the routine
//   objects (GEM_BB_RTN) with these two routines:
//
//	gem_bb_get_first_rtn - get the first routine associated with a database
//	gem_bb_get_next_rtn - get the next routine associated with a database
//
//   Given a routine object (GEM_BB_RTN) one can visit all of the basic block
//   objects (GEM_BB_OBB) with these two routines:
//
//	gem_bb_rtn_get_first_obb - get the first obb associated with a routine
//	gem_bb_obb_get_next_obb - get the next obb associated with a routine
//
//   and all of the source basic block objects (GEM_BB_SBB) with these two
//   routines:
//
//	gem_bb_rtn_get_sbblen - get the number of sbbs associated with a routine
//	gem_bb_rtn_get_sbb - get the Nth sbb associated with a routine
//
//   Given a basic block object (GEM_BB_OBB), one can visit all instruction
//   events (GEM_BB_EVE) associated with that object.  This is described in
//   the section on instruction events.


// Adding a profile to the database
//
// There are three ways to add a profile to a database:
//
//   1. pass a profile object (see next section) to gem_bb_read_database
//
//   2. pass a profile object (see next section) to gem_bb_add_profile
//
//   3. call gem_bb_add_profile_start and gem_bb_add_profile_finish as follows:
//
//	gem_bb_add_profile_start(db)
//
//	    for each rtn
//
//		gem_bb_rtn_set_count(rtn, count)	- sets rtn->object_count
//
//	    for each obb
//
//		gem_bb_obb_set_count(obb,count)	- sets obb->count
//
//	gem_bb_add_profile_finish(db)
//
//   The first two methods support combination rules (adding, scaling, override).
//   The third method always does overriding.


// Manipulating profiles (GEM_BB_PROFILE objects):
//
//   The routines which support manipulation of profiles are:
//
//	gem_bb_use_pixie_profile - use the profile in Addr and Counts vectors
//
//	gem_bb_read_pixie_profile - read a profile from .Addr and .Count files
//
//	gem_bb_close_profile - close a profile handle
//
//   The database API can be used to read in a profile with
//   gem_bb_read_pixie_profile(), or to "import" a profile that has already
//   been read and processed with gem_bb_use_pixie_profile().  The latter is
//   used by prof, which has already created the addr and count vectors.
//
//   Profiles are matched to databases, which causes the counts to be
//   transfered to the database for each routine that matches.  The
//   matching process is done as the database is read by gem_bb_read_database().
//
//   Once a profile is no longer needed (i.e., has been matched), it
//   can be closed with gem_bb_close_profile().


// Manipulating routine entries (GEM_BB_RTN objects):
//
//   The routines which support creation of a new routine entries are:
//
//	gem_bb_rtn_create	- Create a new routine entry
//
//	These are used to create an entirely new database, to recreate stale
//	entries for individual routines, and to reinitialize the database after
//	it has been read and the new compilation is about to begin.  These
//	routines are listed roughly in the order in which they would be used.
//	Currently, only compilers use these routines.
//
//   The routines which manipulate GEM_BB_RTN attributes are:
//
//	gem_bb_rtn_get_count	- Get the execution count of rtn
//
//	gem_bb_rtn_get_weight	- Get weighted count for a routine
//
//	gem_bb_rtn_set_count	- Set the exec_count of rtn to count
//
//   The routines which manipulate GEM_BB_RTN structural components are:
//
//	gem_bb_rtn_create_sbbs	- Create a new SBB table
//				  Called for a new or stale routine entry
//
//	gem_bb_rtn_create_obbs	- Create a new OBB table isomorphic to SBBs
//				  Called to recreate OBB table for a routine
//
//	gem_bb_rtn_remove_obbs	- Delete ALL of the OBBS of a routine
//
//	In addition, routines which create and destroy individual OBBs
//	are, in essence, modifying the structural components of a RTN,
//	Note that these routines are defined in terms of a GEM_BB_RTN,
//	since basic blocks are always manipulated in the context of a
//	routine.
//
// NOTE: deferred routine entries must be evaluated before they can be
// manipulated by these routines.  (See previous section on deferred evaluation.)


// Manipulating routine entries - sorting OBBs using sequence ids
//
//   The routines which manipulate sequence ids are:
//
//	gem_bb_obb_set_seqid	- Set the sequence ids, also used in checking
//
//	gem_bb_rtn_clear_seqids - Clear sequence ids (printing and checking)
//
//	gem_bb_rtn_sort_obbs_by_seqid - Sort the obbs for a routine by
//				sequence id.
//
//   Sorting is needed to get two parallel representations back in sync.
//   For example, the compiler reorders it's representation through
//   optimization, and then reorders the database using sequence ids
//
//   Valid sequence ids run from 0..N-1, where N is the number of OBBs
//   GEM_BB_INVALID indicates an uninitialized or cleared sequence id.
//
//   Here is pseudo-code showing how these routines are used together:
//
//      foreach RTN in object file
//
//	    ! Clear the sequence ids (this is important)
//	    !
//	    gem_bb_rtn_clear_seqids(get_fbinfo(RTN))
//
//	    ! Set the sequence ids
//	    !
//	    dex = 0;
//	    foreach INSTRUCTION in RTN
//
//	        if has_fbinfo(INSTRUCTION)
//		    gem_bb_obb_set_seqid(get_fbinfo(INSTRUCTION), dex++);
//
//	    ! Sort based on sequence id
//	    !		
//	    gem_bb_rtn_sort_obbs_by_seqid(rtn);


// Manipulating basic block entries (GEM_BB_OBB objects)
//
//   The routines which support creation of and destruction of new OBBs are:
//
//	gem_bb_obb_create	- Create a new OBB (no maps, invalid count)
//
//	gem_bb_obb_delete       - Delete ONE of the OBBS of a routine
//
//   The routines which inquire about the current state of an OBB are:
//
//	gem_bb_obb_get_count       - Get the execution count for this OBB
//
//	gem_bb_obb_get_offset      - Get the offset for an OBB
//
//	gem_bb_obb_has_mappings    - Does this OBB have SBB mappings?
//
//   Transformations to the application being processed must be reflected in
//   transformations to the database.  The routines which modify the state
//   of an OBB can be divided into to categories.  Some transformations
//   require specific knowledge about the application transformation.  
//   This is typically true of transformations to OBB->SBB mappings and
//   execution counts:
//
//	gem_bb_obb_add_count_fuzz  - Add to the count_fuzz for an OBB
//
//	gem_bb_obb_copy_count      - Copy execution count from one OBB to another
//
//	gem_bb_obb_set_count       - Set the execution count for this OBB
//
//	gem_bb_obb_copy_mappings   - Copy mappings from one OBB to another
//
//	gem_bb_obb_merge           - Merge two OBBs:  combine maps and count
//
//	gem_bb_obb_move_mappings   - Move mappings from one OBB to another
//
//	gem_bb_obb_remove_mappings - Delete the mappings associated with an OBB
//
//	gem_bb_obb_scale_mappings  - Scale all maps for OBB by a scale factor
//
//	gem_bb_obb_add_count_fuzz  - Add to the count_fuzz for an OBB
//	
//   Other transformations can be performed after the application has been
//   transformed by walking the application's internal representation and
//   recomputing the state of the OBBs.  The routines typically used in
//   this fashion are:
//
//	gem_bb_obb_set_offset      - Set this OBB's offset from routine start
//
//	gem_bb_obb_set_weak	   - Make this OBB optional for matching
//
//   Here is pseudo-code showing how these routines are used:
//
//      foreach RTN in object file
//
//	    offset = 0;
//
//	    ! Set the sequence ids
//	    !
//	    foreach INSTRUCTION in RTN
//
//	        if has_fbinfo(INSTRUCTION)
//		    gem_bb_obb_set_offset(get_fbinfo(INSTRUCTION), offset);
//
//		offset++;
//
//   The routines which support resequencing (sorting) the OBBs also fall
//   in this category.  These are described in the next section, along with
//   some pseudo-code showing how they would be used.


// Manipulating source basic block entries (GEM_BB_SBB objects)
//
//   Source basic blocks are not first-class objects.  Very little is
//   provided by ways of manipulating them.  Once they have been created,
//   they cannot be modified.  These accessor routines are provided:
//
// 	gem_bb_sbb_get_count - Get the SBB execution count
//
//	gem_bb_sbb_get_line - Get the line number associated with a source basic block
//
//	gem_bb_sbb_get_successors - Get the successors associated with this SBB
//
//	gem_bb_sbb_get_predecessors - Get the predecessors associated with this SBB
//
//	gem_bb_sbb_get_succ_str - Get a string representation of the successors
//
// In addition, these routines are provided in order to iterate through the
// SBBs associated with a routine entry:
//
//	gem_bb_rtn_get_sbblen - get the number of sbbs associated with a routine
//
//	gem_bb_rtn_get_sbb - get the Nth sbb associated with a routine


// Manipulating instruction events (GEM_BB_EVE objects)
//
// An event object (GEM_BB_EVE) is created and associated with an OBB by the following
// routine:
//
//	gem_bb_eve_create - create a new simple or complex event
//
// The events associated with an OBB can be navigated using these routines:
//
//	gem_bb_obb_get_events - Get the events associated with an OBB starting at offset
//				(if offset is GEM_BB_INVALID, return the first event)
//
//	gem_bb_eve_get_next - get the next event in an event list
//			      (if same_offset_only is true, stop when offset changes)
//
//      to iterate through all of the events in a block:
//
//	   for (eve = gem_bb_obb_get_events(obb, GEM_BB_INVALID);    // get all events
//		eve != NULL;
//		eve = gem_bb_eve_get_next(eve, false))  // continue when offset changes
//
//      to iterate through all of the events for a particular instruction:
//
//	   for (eve = gem_bb_obb_get_events(obbs, 10);  // start at offset 10
//		eve != NULL;
//		eve = gem_bb_eve_get_next(eve, true))	// stop when offset changes
//
// Event attributes can be accessed using the following routines:
//
//	gem_bb_eve_get_offset - Get the offset (from the start of its OBB) for the event
//	gem_bb_eve_get_position - get the source position (lines, columns) of an event
//	gem_bb_eve_get_opcode - get the opcode of the inst associated with an event
//	gem_bb_eve_get_opname - get the name of the opcode
//	gem_bb_eve_get_type - get the type of an event
//
// Events have one or more values associated with them, depending upon the type of the
// event.  This predicate can be used to determine if the event is simple (single-valued)
// or complex (multi-valued):
//
//	gem_bb_eve_is_complex - indicate if an event is complex (multi-valued)
//
// For simple events, this value is accessed/modified with these routines:
//
//	gem_bb_eve_get_value - get the data associated with an event
//	gem_bb_eve_set_value - set the data associated with an event
//
// For complex events, this value is accessed/modified with these routines:
//
//	gem_bb_eve_get_complex_nelms - get the number of elements associated with an event
//	gem_bb_eve_get_complex_value - get an element of the data associated with an event
//	gem_bb_eve_set_complex_value - set an element of the data associated with an event
// 
// Once created, the only event attributes that can be modified are the values
// associated with the event.


// Debugging support (dumps, and integrity checks):
//
//   The routines which support debugging activities are:
//
//	gem_bb_check_database	- Check integrity of the database (or routine)
//				  Used in conjunction with sequence ids
//
//	gem_bb_dump_database	- Dump the entire database
//
//	gem_bb_dump_invalid_counts - Dump OBBs with invalid counts
//
//	gem_bb_dump_orphans	- Dump SBBs that have been orphaned
//
//	gem_bb_dump_ranking     - Dump the histogram used in ranking counts
//
//	gem_bb_set_trace_flags  - This routine, when linked with a debug library,
//				  sets tracing of various events.  These events
//				  correspond to the events supported by GEM's
//				  event mechanism.  This routine is defined in
//				  the API only.
//
//	gem_bb_rtn_dump	 	- Dump a single routine entry (or only header)
//
//	gem_bb_rtn_dump_obbs	- Dump the OBB table for one routine
//
// Within GEM, the following events can be set for debugging:
//
//	gem_fb_change
//	gem_fb_check
//	gem_fb_io
//	gem_fb_match
//	gem_bb_rank
//	gem_fb_profile
//	gem_fb_reorder
//
//   Outside of GEM, gem_bb_set_trace_flags can be used to set boolean variables
//   that mimic these events.


// Support for database version stamps
//
// The routine gem_bb_get_version can be used to determine:
//
//	the current database version supported by a version of the API
//	(maximal supported, or restricted to lower version on particular OS)
//
//	the version of a particular database (GEM_BB_DB), or
//
//	the version of a particular routine entry (GEM_BB_RTN)
//
// The version ID consists of a major and minor version number.  A version is
// newer if the major version is higher, or if they are equal if the minor
// version is higher (2.15 is higher than 2.2).
//
// A database can have routines with different version ids.  Tools which defer
// the reading of routine entries should only fail if they attempt to evaluate
// a routine with a higher version than they support.
//
// The database version is the highest version of its routine entries.


// Alphabetical listing of routines with prototypes and descriptions:
//

// All routines are defined with a C interface
//
#ifdef __cplusplus
extern "C" {
#endif


// gem_bb_add_missing - synthesize missing entries using the symbol table
//
//			This routine adds bb_rtn entries but does not
//			fill in the obbtbl for that routine, which must
//			be done for each bb_rtn before it is valid.
//			To have that done "automatically," call
//			gem_bb_add_profile instead of this routine.
//
void
gem_bb_add_missing(

    GEM_BB_DB	dbhndl,	// The database handle

    GEM_BB_READ flags);	// Bit vector of flags to control read and write operations
                        // (Only READ_DO_ALTENTS is currently used)


// gem_bb_add_profile - Add a profile to a database
//
GEM_BB_ERR
gem_bb_add_profile(

    GEM_BB_DB	   dbhndl,	// The database handle

    GEM_BB_PROFILE profile,	// A profile in internal form (optional)

    GEM_BB_READ   flags);	// Flags


// gem_bb_add_profile_finish - to finish manually adding profile information
//
void
gem_bb_add_profile_finish(

    GEM_BB_DB	   dbhndl);	// The database handle


// gem_bb_add_profile_start - to start manually adding profile information
//
void
gem_bb_add_profile_start(

    GEM_BB_DB	   dbhndl);	// The database handle


// gem_bb_check_database - Check the integrity of the database (or one routine)
//
// 	Either dbhndl or rtnhndl must be specified.
//
//	This routine is used by compilers only.
// 
GEM_BOOLEAN
gem_bb_check_database(

    GEM_BB_DB	dbhndl,		// The database to be checked (optional)

    GEM_BB_RTN	rtnhndl,	// The routine to be checked (optional)

    GEM_BOOLEAN	check_order,	// Are OBBs in the right order (uses seqids)

    GEM_BOOLEAN	check_coverage,	// Are all OBBs covered (uses seqids)

    GEM_BOOLEAN	check_counts,	// Are SBB counts still reproducible

    GEM_BOOLEAN	check_offsets);	// Are offsets are monotonically increasing?



// gem_bb_close_database - close a database
//
//	This routine will:
//
//	    close file handles associated with a database
//	    release a memory mapped region associated with a database
//		(if that region was opened through gem_bb_open_database)
//	    release temporary data structures used in reading a database
//	        and associating it with the client's view of the application
//	        associated with the database (e.g., a series of calls
//		to gem_bb_find_rtn_by_offset)
//
//	The database can be manipulated by the client after this routine,
//	since this routine does not reclaim an in-memory form of a database.
//	To do this, gem_bb_free_database must be called.
//
void
gem_bb_close_database(
    GEM_BB_DB	dbfilhndl);


// gem_bb_close_profile - close a profile handle
//
//	This routine closes a profile, freeing all memory associated
//	with that profile:
//
//	    If a profile was initialized using gem_bb_use_..._profile, the
//	    caller must free all memory associated with reading the profile,
//	    including the counts and addrs arrays.
//
//	    If the profile was initialized using gem_bb_read_..._profile,
//	    memory used for this process is freed by this call.
//
//	After this routine is called, any further use of the profile handle
//	is invalid.
//
//	If the profile has been associated with a database using
//	gem_bb_match_profile, that connection is not broken.
//
void
gem_bb_close_profile(
    GEM_BB_PROFILE prohndl);


// gem_bb_compute_rank - Compute relative rank from raw count
//
//	Translate an execution count into a relative rank.
//
//	This routine will return GEM_BB_INVALID if gem_bb_initialize_ranking
//	has not been called on the database.
//
GEM_BB_RANK
gem_bb_compute_rank(

    GEM_BB_DB	dbhndl,		// The database

    GEM_IMAX	count);		// The OBB execution count to be ranked


// gem_bb_compute_sbb_counts - Compute SBB counts from OBB counts
//
//	This routine is used by compilers only.
//
//	It returns true if the sbb counts were successfully computed,
//	false if they were already computed or the routine was unsuccessful
//	(e.g., if a deferred read fails due to version skew)
//
GEM_BOOLEAN
gem_bb_compute_sbb_counts(

    GEM_BB_DB	dbhndl,		// The database

    GEM_BOOLEAN	do_recompute,	// Recompute even if already computed

    GEM_STR	cntfil);	// A text file containing override counts (for debugging)
				//   The format is the output of bbtool -sbb -format diff


// gem_bb_compute_event_totals - Compute SBB counts from OBB counts
//
//	This routine is used by compilers only.
//
//	It returns true if the sbb counts were successfully computed,
//	false if they were already computed or the routine was unsuccessful
//	(e.g., if a deferred read fails due to version skew)
//
GEM_BOOLEAN
gem_bb_compute_event_totals(

    GEM_BB_DB	dbhndl,		// The database

    GEM_BOOLEAN	compute_sbbs);	// Boolean indicating whether or not to compute SBB totals
				// or only compute OBB totals

// gem_bb_db_create - create a new database
//
//	Create an new database, used before calling gem_bb_rtn_create
//
GEM_BB_DB
gem_bb_db_create();


// gem_bb_dump_database - Dump the entire database
//
//	When used in GEM, this routine dumps its output to gem_db_g_output.
//	When used in the API, this routine dumps its output to stdout.
//
void
gem_bb_dump_database(

    GEM_BB_DB	dbhndl,		// The database to be dumped

    GEM_BOOLEAN	db_header_only,

    GEM_BOOLEAN	rtn_header_only);


// gem_bb_dump_invalid_counts - Dump OBBs with invalid counts
//
//	When used in GEM, this routine dumps its output to gem_db_g_output.
//	When used in the API, this routine dumps its output to stdout.
//
void
gem_bb_dump_invalid_counts(

    GEM_BB_DB	dbhndl,		// The database to be dumped

    GEM_BB_RTN	rtnhndl);	// The routine of primary interest
				// (NULL to dump the entire database)


// gem_bb_dump_orphans - Dump SBBs that have been orphaned
//
//	When used in GEM, this routine dumps its output to gem_db_g_output.
//	When used in the API, this routine dumps its output to stdout.
//
void
gem_bb_dump_orphans(

    GEM_BB_DB	dbhndl,		// The database to be dumped

    GEM_BB_RTN	rtnhndl);	// The routine of primary interest
				// (NULL to dump the entire database)


// gem_bb_dump_ranking - Dump the histogram associated with a database
//
//	When used in GEM, this routine dumps its output to gem_db_g_output.
//	When used in the API, this routine dumps its output to stdout.
//
void
gem_bb_dump_ranking(

    GEM_BB_DB	dbhndl);	// The database to be dumped


// gem_bb_dump_summary - dump summary information
//
//	When used in GEM, this routine dumps its output to gem_db_g_output.
//	When used in the API, this routine dumps its output to stdout.
//
void
gem_bb_dump_summary(

    GEM_BB_DB	dbhndl,		// the database to summarize

    GEM_BOOLEAN	print_size,	// print the size of the database

    GEM_BOOLEAN	print_memory,	// print memory statistics

    GEM_BOOLEAN	print_totals);	// print total numbers of various objects


// gem_bb_eve_create - create a new simple or complex event
//
GEM_BB_EVE
gem_bb_eve_create(

    GEM_BB_OBB	obbhndl,	// The block containing the event

    GEM_INT	offset,		// The offset of the event in longwords
				//   (identifying the Nth instruction)

    GEM_INT	opcode,		// The opcode of the instruction

    GEM_BB_EVT	type, 		// The event type

    GEM_BOOLEAN	is_complex,	// Single or multi-valued?

    GEM_IMAX	valorlen,	// single value or length of value array

    GEM_IMAX	vals[]);	// NULL or array of values


// gem_bb_eve_dump - dump a single event
//
void
gem_bb_eve_dump(

    GEM_BB_EVE	evehndl);


// gem_bb_eve_dump_list - dump an event list
//
void
gem_bb_eve_dump_list(

    GEM_BB_EVE	evehndl);


// gem_bb_eve_get_encoding 
//
GEM_INT
gem_bb_eve_get_encoding(

    GEM_BB_EVE	evehndl);


// gem_bb_eve_get_next - get the next event in an event list
//
GEM_BB_EVE
gem_bb_eve_get_next(

    GEM_BB_EVE	evehndl,	   // The current event

    GEM_BOOLEAN same_offset_only); // The stop condition:
				   //   true -  stop when offset changes
				   //   false - iterate through entire list


// gem_bb_eve_get_offset - Get the offset (from the start of its OBB) for the event
//
GEM_INT
gem_bb_eve_get_offset(

    GEM_BB_EVE	evehndl);


// gem_bb_eve_get_position - get the source position (lines, columns) of an event
//
void
gem_bb_eve_get_position(

    GEM_BB_EVE	evehndl,	// The event

    GEM_INT	*pline,		// The line number

    GEM_INT	*pcolumn);	// The column number


// gem_bb_eve_get_opcode - get the info about the instruction associated with an event
//
GEM_INT
gem_bb_eve_get_opcode(

    GEM_BB_EVE	evehndl);		// The event


// gem_bb_eve_get_opname
//	Purpose:  Get information associated with an event
//	Returns:  The name of the opcode
//
GEM_STR
gem_bb_eve_get_opname(

    GEM_BB_EVE	evehndl);


// gem_bb_eve_get_type - get the type of an event
//
GEM_BB_EVT
gem_bb_eve_get_type(

    GEM_BB_EVE	evehndl);		// The event


// gem_bb_eve_get_value - get the data associated with an event
//
GEM_IMAX
gem_bb_eve_get_value(

    GEM_BB_EVE	evehndl);

// gem_bb_eve_get_complex_nelms - get the number of elements associated with an event
//
GEM_INT
gem_bb_eve_get_complex_nelms(
    GEM_BB_EVE	evehndl);


// gem_bb_eve_get_complex_value - get an element of the data associated with an event
//
GEM_IMAX
gem_bb_eve_get_complex_value(
    GEM_BB_EVE	evehndl,
    GEM_INT	valdex);

// gem_bb_eve_is_complex - indicate if an event is complex (multi-valued)
//
GEM_BOOLEAN
gem_bb_eve_is_complex(
    GEM_BB_EVE	evehndl);


// gem_bb_eve_set_complex_value - set an element of the data associated with an event
//
void
gem_bb_eve_set_complex_value(

    GEM_BB_EVE	evehndl,

    GEM_INT	valdex,

    GEM_IMAX	val);


// gem_bb_eve_set_value - set the data associated with an event
//
void
gem_bb_eve_set_value(

    GEM_BB_EVE	evehndl,

    GEM_IMAX	val);


// gem_bb_fini - Shutdown the package
//
//	call this after the database API is no longer needed
//
void
gem_bb_fini();


// gem_bb_free_database - free a database
//
//	This routine will free all memory used by a database.
//
//	After this routine has been called, all further operations
//	on a database are invalid.
//
//	This routine will assert if the database was in the process
//	of being written, but was in an inconsistent state.
//
void
gem_bb_free_database(
    GEM_BB_DB	dbfilhndl);


// gem_bb_get_first_rtn - get the first routine associated with a database
//
GEM_BB_RTN
gem_bb_get_first_rtn(

    GEM_BB_DB	dbhndl);


// gem_bb_get_next_rtn - get the next routine associated with a database
//
GEM_BB_RTN
gem_bb_get_next_rtn(
    GEM_BB_RTN	rtnhndl);


// gem_bb_get_ranking - Return the execution count histogram
//
//	This routine is used to write OPAL dumps.
//	Return value is the number of separators.
//
GEM_INT
gem_bb_get_ranking(
    GEM_BB_DB	dbhndl,
    GEM_IMAX	separators[]);


// gem_bb_get_text_offset - Return the start address of the executable's text section
//
//  Return value:
//
//  Notes:
//    This routine should only be called after gem_bb_read_database
//
GEM_IMAX
gem_bb_get_text_offset(
    GEM_BB_DB	dbhndl);


// gem_bb_get_text_size - Return the size of the executable's text section
//
//  Return value:
//    Size of text section or GEM_FB_INVALID if unknown
//
//  Notes:
//    This routine should only be called after gem_bb_read_database
//
//    If the text size is > MAXINT32, MAXINT32 is returned.
//
GEM_INT
gem_bb_get_text_size(
    GEM_BB_DB	dbhndl);


// gem_bb_get_version - Return the current version id or id of a particular db
//
//  Return value:
//    if dbhndl is non-null	the database version (version of highest routine)
//    if rtnhndl is non-null	the routine version
//    if maximum		the maximum supported version
//    else 			the current version supported (OS restrictions)
//
void
gem_bb_get_version(
    GEM_BB_DB	dbhndl,
    GEM_BB_RTN	rtnhndl,
    GEM_BOOLEAN	maximum,
    GEM_INT	*pmajor,
    GEM_INT	*pminor,
    GEM_STR	verstr);


// gem_bb_init - Initialize the package
//
//	call this before any other routine is called 
//
void
gem_bb_init(
    GEM_BB_INIT_FLAGS	flags);


// gem_bb_initialize_ranking - Create the execution count histogram
//
//	This routine is called once per database.  It is used to support
//	the relative frequency API routines.
//
//	Ranking information is not stored in a persistent database.  It must
//	be recreated each time a database is read into memory.
//
//	The database is	expected to have valid count information.  If it
//	does not, this routine will do nothing.
//
//	After this routine is called, the relative frequency API (rank
//	and weight routines) will return valid results.
//
//	It returns true if the sbb counts were successfully computed,
//	false if they were already computed or the routine was unsuccessful
//	(e.g., if a deferred read fails due to version skew)
//
GEM_BOOLEAN
gem_bb_initialize_ranking(

    GEM_BB_DB	dbhndl,

    GEM_BOOLEAN	do_reinitialize,

    GEM_BOOLEAN	exclude_libraries);


// gem_bb_find_rtn_by_name - find a routine entry by name
//
//	This routine depends on an established namespace for the database.
//
//	It will return NULL if gem_bb_create_name_table has not been called.
//
//	For global routines only rtnnam and filnam are needed.
//
//	For local routines, the module id may be needed to disambiguate
//	multiple entries with the same routine and file names.  This will
//	typically happen when a local routine is declared in a header file.
//
//	This routine is used by compilers only.
//
GEM_BB_RTN
gem_bb_find_rtn_by_name(

    GEM_BB_DB	dbhndl,		// The database for the lookup

    GEM_STR	rtnnam,		// the routine name to lookup

    GEM_STR	filnam,     	// the file name to lookup

    GEM_BB_RTN	modhndl,	// routine entry in same module (an objectd
				// file and file scope disambiguator)

    GEM_BB_ERR	*pstatus);	// pointer to status word.  This should be
				// examined if NULL is returned to find out
				// if the lookup failed due to a failed
				// evaluation of a deferred routine.


// gem_bb_find_rtn_by_offset - find a routine entry by offset
//
//	If the lookup fails, NULL is returned.  A match should only
//	fail if the database is somehow out of sync with respect to
//	the editor's internal representation.  This should never happen.
//
//	This routine is used by executable editors only.
//
GEM_BB_RTN
gem_bb_find_rtn_by_offset(

    GEM_BB_DB	dbhndl,		// The database for the lookup

    GEM_INT	offset);	// The offset (in instructions,
				// from the start of the text section)



// gem_bb_obb_add_count_fuzz  - Add to the count_fuzz for an OBB
//
//	Fuzzification is currently used only to relax the contraints
//	used by the database integrity check routine (gem_bb_check_database).
//
//	At some point in the future, fuzz may also be used to identify
//	places where a heuristically determined count is known to fall
//	within a range of values.
//
//	This routine is used by compilers only.
//
void
gem_bb_obb_add_count_fuzz(

    GEM_BB_OBB	obbhndl,	// The OBB

    GEM_INT	fuzz);		// The fuzz factor



// gem_bb_obb_copy_count - Copy execution count from one OBB to another
//
//	This is a shorthand for getting the count from source OBB and
//	then setting the count of the destination OBB.
//
void
gem_bb_obb_copy_count(

    GEM_BB_OBB	dsthndl,	// The destination OBB

    GEM_BB_OBB	srchndl);	// The source OBB



// gem_bb_obb_copy_mappings - Copy mappings from one OBB to another
//
//	OBB->SBB mappings need to be copied whenever a new a block of
//	instructions is duplicated.
//
//	When used for inlining, dst->rtn and src->rtn are different,
//	otherwise they are identical.
//
void
gem_bb_obb_copy_mappings(

    GEM_BB_OBB	dsthndl,	// The destination OBB

    GEM_BB_OBB	srchndl);	// The source OBB



// gem_bb_obb_create - Create a new OBB
//
//	An OBB is always created in the context of a particular routine.
//
//	Initially, an OBB has no mappings and an invalid exec_count.
//
GEM_BB_OBB
gem_bb_obb_create(

    GEM_BB_RTN	rtnhndl);	// The routine to contain the new OBB



// gem_bb_obb_delete - Delete one of the OBBS associated with a routine
//
void
gem_bb_obb_delete(

    GEM_BB_OBB	obbhndl,	// The OBB

    GEM_INT	orphan_count);	// An orphan count for orphaned SBBs


// gem_bb_obb_dump - Dump a single OBB
//
//	When used in GEM, this routine dumps its output to gem_db_g_output.
//	When used in the API, this routine dumps its output to stdout.
//
void
gem_bb_obb_dump(

    GEM_BB_OBB	obbhndl);	// The OBB to be dumped


// gem_bb_obb_get_count - Get the execution count for an OBB
//
GEM_IMAX
gem_bb_obb_get_count(

    GEM_BB_OBB	obbhndl);	// The OBB



// gem_bb_obb_get_events - Get the events associated with an OBB
//
//
GEM_BB_EVE
gem_bb_obb_get_events(

   GEM_BB_OBB	obbhndl,	// The basic block

   GEM_INT	offset);	// The longword offset from the start of the OBB
				//   if GEM_BB_INVALID, return the first event

// gem_bb_obb_get_next_obb - get the next obb associated with a routine
//
GEM_BB_OBB
gem_bb_obb_get_next_obb(

    GEM_BB_OBB obbhndl);


// gem_bb_obb_get_offset - Get the offset for an OBB
//
GEM_INT
gem_bb_obb_get_offset(

    GEM_BB_OBB	obbhndl);	// The OBB


// gem_bb_obb_get_seqid	- Get the sequence id, used in checking and sorting
//
//      The sequence id is the ordinal posision of the obb in the list of
//
//	It may be invalid during the check and sort processes (after the
//	call to gem_bb_rtn_clear_seqids and before the calls to
//	gem_bb_obb_set_seqid).
//
//	After gem_bb_rtn_create_obbs, the sequence ids are identical to
//	their corresponding SBB indexes, and will be visited in order by
//	a traversal of the IL.  At later points in compilation, the seqids
//	will only correspond to traversal order after sorting.
//
GEM_INT
gem_bb_obb_get_seqid(

    GEM_BB_OBB	obbhndl);


// gem_bb_obb_get_size - Get the size of an OBB
//
GEM_INT
gem_bb_obb_get_size(

    GEM_BB_OBB	obbhndl);	// The OBB


// gem_bb_obb_has_mappings - Does this OBB have SBB mappings?
//
GEM_BOOLEAN
gem_bb_obb_has_mappings(

    GEM_BB_OBB	obbhndl);	// The OBB



// gem_bb_obb_merge - Merge two OBBs:  move mappings and reconcile count
//
void
gem_bb_obb_merge(

    GEM_BB_OBB	dsthndl,	// The destination OBB

    GEM_BB_OBB	srchndl,	// The source OBB

    GEM_BOOLEAN add_counts);	// Add counts and weed duplicate mappings



// gem_bb_obb_move_mappings - Move mappings from one OBB to another
//
void
gem_bb_obb_move_mappings(

    GEM_BB_OBB	dsthndl,	// The destination OBB

    GEM_BB_OBB	srchndl);	// The source OBB



// gem_bb_obb_remove_mappings - Remove mappings from an OBB
//
void
gem_bb_obb_remove_mappings(

    GEM_BB_OBB	obbhndl,	// The OBB

    GEM_INT	orphan_count);	// An orphan count for orphaned SBBs



// gem_bb_obb_scale_mappings - Scale all mappings for this OBB by a scale factor
//
void
gem_bb_obb_scale_mappings(

    GEM_BB_OBB	obbhndl,	// The OBB

    GEM_INT	numer,		// numerator of scale factor

    GEM_INT	denom);		// denominator of scale factor



// gem_bb_obb_set_count - Set the execution count for this OBB
//			  Does nothing if obb->rtn->obb_counts_valid is not set
//
void
gem_bb_obb_set_count(

    GEM_BB_OBB	obbhndl,	// The OBB

    GEM_IMAX	count);		// The execution count



// gem_bb_obb_set_offset - Set this OBB's offset from routine start
//
//	The offset is relative to the first instruction of the routine.
//
//	The nops inserted by -pg are ignored by the compiler when
//	it computes the offset.
//
void
gem_bb_obb_set_offset(

    GEM_BB_OBB	obbhndl,	// The OBB

    GEM_INT	offset);	// The offset



// gem_bb_obb_set_seqid	- Set the sequence ids, used in checking and sorting
//
//      It is an error to call this routine if the sequence id has already
//	been set (and not reset).  This is done to catch problems multiple
//	references to the same OBB.
//
//      Used in sorting (described with gem_bb_rtn_sort_obbs_by_seqid)
//
//	Used in integrity checking (compiler only)
//
//	This routine will assertion check if obbhndl is invalid, or if
//	the sequence id is already set to a value (e.g., has been set but
//	not cleared).
//   
void
gem_bb_obb_set_seqid(

    GEM_BB_OBB	obbhndl,	// The OBB

    GEM_INT	seqid);		// The sequence id



// gem_bb_obb_set_size - Set this OBB's size
//
void
gem_bb_obb_set_size(

    GEM_BB_OBB	obbhndl,	// The OBB

    GEM_INT	size);		// The offset (in longwords)


// gem_bb_obb_set_weak - Indicate that this OBB is optional for matching
//
//	This is set on OBBs which may not be recognized by Atom, or
//	which may have had their offsets slightly altered by the linker.
//
void
gem_bb_obb_set_weak(

    GEM_BB_OBB	obbhndl,	// The OBB

    GEM_BOOLEAN	is_weak);	// Boolean used to set or clear weakness


// gem_bb_open_database - open an existing database in persistent form
//
//	The databse can be opened in memory map mode or in file I/O
//	mode.
//
//	Once opened, the database is read using gem_bb_read_database.
//
GEM_BB_ERR
gem_bb_open_database(

    GEM_BB_DB	*pdbfilhndl,

    GEM_STR	filename,

    GEM_BOOLEAN	do_mmap);


// gem_bb_read_database - Read in a database from a file
//
//	Read in a database from a symbol table.
//
//	If the database is successfully read in, a handle for the in-memory
//	representation of the database is returned
//
// 	If a profile is not specified, use the counts in the database.
//	If a profile is specified, match the profile to the database 
//	and replace the counts in the database with the counts from
//	the profile.
//
//	If a profile is read in, discrepancies between weak OBBs and
//	the profile are information are corrected in the database.
//
//	The following GEM_BB_ERR_K_ error conditions can be returned:
//	    
//	    SUCCESS    - the operation completed successfully.
//
//	    NOPROFILE  - the profile data was unusable
//	    NODBDAT    - there was no database to read
//	    BADDBDAT   - the database was not readable
//	    DBADDR_MISMATCH - the database and profile did not match
//
//	If READ_ADD_MISSING is set, the return status will
//	indicate success even if there was no database.
//	Applications which need to recognize this case should call
//	gem_bb_read_database without this flag, and then call
//	gem_bb_add_missing separately.
//
//	If READ_ADD_MISSING is set, but no profile is supplied, the
//	database will be in an incomplete state (bb_rtns with no obblst).
//	These must be added by hand, or by calling gem_bb_add_profile with
//	READ_ADD_MISSING.
//
//	Note:  there is no separate predicate to test that a file contains
//	a database.  To test this, gem_bb_open_database (or gem_bb_use_database)
//	and gem_bb_read_database must be used.  (The latter must not be called
//	with the READ_ADD_MISSING flag.)
//
GEM_BB_ERR
gem_bb_read_database(

    GEM_BB_DB	dbhndl,		// The database (in: persistent; out: memory)

    GEM_BB_READ flags,		// Bit vector of flags to control read and write operations

    GEM_BB_DB	mergehndl,	// The database to merge (in: persistent)

    GEM_BB_PROFILE profile);	// A profile in internal form (optional)


// gem_bb_read_pixie_profile - read a profile from a pair of .Addr and .Count files
//
//	The files are opened and the Addrs and Counts data is read in.
//
//	The handle for the profile data is returned in pprofhndl.
//
//	The following GEM_BB_ERR_K_ error conditions can be returned:
//	    
//	    SUCCESS    - the operation completed successfully.
//
//	    NOADDRFIL  - the addr file couldn't be opened
//	    NOCNTFIL   - the count file couldn't be opened
//	    NOPROFILE  - neither file could be opened
//	    BADADDRTYP - the addr file was the wrong type
//	    BADCNTTYP  - the count file was the wrong type
//	    BADADDRDAT - the addr file contained bad data
//	    BADCNTDAT  - the count file contained bad data
//	    CNTADDR_MISMATCH - the addr and counts files did not match
//
GEM_BB_ERR
gem_bb_read_pixie_profile(
    GEM_BB_PROFILE *pprofhndl,
    GEM_STR	addrfilnam,
    GEM_STR	countfilnam);


// gem_bb_resolve_references - resolve all references in a database
//
void
gem_bb_resolve_references(

    GEM_BB_DB 	dbhndl);	// The database.


// gem_bb_rtn_clear_seqids - Clear sequence ids (sorting and checking)
//
//	Sets all sequence ids to GEM_BB_INVALID.
//	
//	Unless sequence ids are already in an initial state, this routine
//	must be called before any calls to gem_bb_obb_set_seqid are
//	made.
//
void
gem_bb_rtn_clear_seqids(

    GEM_BB_RTN	rtnhndl);	// The routine



// gem_bb_rtn_compute_event_totals -
//
GEM_BOOLEAN
gem_bb_rtn_compute_event_totals(

    GEM_BB_RTN	rtnhndl,	// The routine

    GEM_BOOLEAN	compute_sbbs);	// Boolean indicating whether or not to compute SBB totals
				// or only compute OBB totals


// gem_bb_rtn_create - Create a new routine entry
//
//	This routine is used by compilers only.
//
GEM_BB_RTN
gem_bb_rtn_create(

    GEM_BB_DB 	dbhndl,		// The database

    GEM_STR	rtnnam,		// The routine name

    GEM_STR	filnam,		// The file name

    GEM_INT	sbblen,		// The SBB table length

    GEM_INT	linenum,	// The logical (listing) line number

    GEM_BB_RTN	modhndl,	// Related routine to be used for both
				// Object file and file scope disambiguation.

    GEM_INT     modid);		// File scope disambiguator for plus list compiles


// gem_bb_rtn_create_obbs - Create a new OBB table isomorphic to SBB table
//
//	Old OBBs are discarded and new OBBs are created.  The new OBBS
//	are copied from the SBBs.  In particular, SBB counts are copied to
//	the OBBs.
//
//	This routine is used by compilers only.
//
void
gem_bb_rtn_create_obbs(

    GEM_BB_RTN	rtnhndl,	// The routine

    GEM_BB_OBB	obbhndlvec[]);	// The vector of OBBs


// gem_bb_rtn_create_sbb_preds - Create predecessor tables for all of the SBBs
//				 These are derived from the successor tables
//
void
gem_bb_rtn_create_sbb_preds(
    GEM_BB_RTN	rtnhndl);	// The routine


// gem_bb_rtn_create_sbbs - Create a new SBB table
//
void
gem_bb_rtn_create_sbbs(

    GEM_BB_RTN	rtnhndl,	// The routine

    GEM_INT	nblocks,	// The number of SBBs

    GEM_INT	linenums[],	// A vector of line numbers for the SBBs

    GEM_INT	merged[],       // A vector indicating which blocks were
		       		// merged by examining pred/succ rels
				// Values in this array are:
				//	-nblocks..0    - it was not merged
				//		       - sbb is dex + unmatched[dex] + 1
				//	nblocks	       - unmatched
				//	0..nblocks-1   - unmatched, but the
				//		         count can be derived
				//			 from the sbb at this index

    GEM_INT	annotations[],	// A vector of annotations (basic block type)

    GEM_INT	npredsuccs,	// Number of pred/succ relationships

    GEM_INT	predsuccs[],    // A vector of pred/succ relationships

    GEM_BOOLEAN has_counts,	// Is the counts vector present?

    GEM_IMAX	counts[]);	// Optional vector of initial exec counts



// gem_bb_rtn_dismiss - dismiss an active routine (return it to a deferred state)
//
GEM_BOOLEAN
gem_bb_rtn_dismiss(

    GEM_BB_RTN	rtnhndl,
 
    GEM_BOOLEAN	save_if_changed);


// gem_bb_rtn_dump - Dump a single routine entry (perhaps only the header)
//
//	When used in GEM, this routine dumps its output to gem_db_g_output.
//	When used in the API, this routine dumps its output to stdout.
//
void
gem_bb_rtn_dump(

    GEM_BB_RTN	rtnhndl,	// The routine to be dumped

    GEM_BOOLEAN	header_only);	// Dump a header only (no SBBs or OBBs)


// gem_bb_rtn_dump_obbs - Dump the OBB table for one routine
//
//	When used in GEM, this routine dumps its output to gem_db_g_output.
//	When used in the API, this routine dumps its output to stdout.
//
void
gem_bb_rtn_dump_obbs(

    GEM_BB_RTN	rtnhndl);	// The routine whose OBBS are to be dumped


// gem_bb_rtn_evaluate - evaluate a deferred routine
//
GEM_BB_ERR
gem_bb_rtn_evaluate(

    GEM_BB_RTN	rtnhndl);


// gem_bb_rtn_extract_events - extract events of a particular type, or all events
//
//	Events are:
//	    removed from the routine's OBBS
//	    made into one list
//	    sorted by offset or by esli
//
//	Events outside of the type set are undisturbed.
//
GEM_BB_EVE
gem_bb_rtn_extract_events(

    GEM_BB_RTN	rtnhndl,	// The routine

    GEM_BB_EVT	event_type,	// If zero, all events

    GEM_BOOLEAN	sort_by_offset);// true, sort by offset; false, sort by source location


// gem_bb_rtn_get_all_counts - 
//
//	This routine gets all of the counts from a rtn.
//
//	It will work on a routine in deferred form.
//
//	If an error occurred, GEM_BB_INVALID is returned.
//	   (vectors were too small or evaluation of deferred routine failed)
//
GEM_INT
gem_bb_rtn_get_all_counts(

    GEM_BB_RTN	rtnhndl,	// The handle for the routine

    GEM_IMAX	*prtncount,	// A pointer to a container for the routine count

    GEM_IMAX	*prtnweight,	// A pointer to a container for the routine count

    GEM_INT	*poffsets[],	// A vector of absolute offsets

    GEM_IMAX	*pcounts[]);	// A vector of counts


// gem_bb_rtn_get_count - Get the execution count of rtn
//
GEM_IMAX
gem_bb_rtn_get_count(

    GEM_BB_RTN	rtnhndl);	// The routine


// gem_bb_rtn_get_filename - get the file name associated with a routine
//
GEM_STR
gem_bb_rtn_get_filename(

    GEM_BB_RTN	rtnhndl);


// gem_bb_rtn_get_first_obb - get the first obb associated with a routine
//
GEM_BB_OBB
gem_bb_rtn_get_first_obb(

    GEM_BB_RTN	rtnhndl);


// gem_bb_rtn_get_linenum - 
//
GEM_INT
gem_bb_rtn_get_linenum(

    GEM_BB_RTN	rtnhndl);	// The routine


// gem_bb_rtn_get_name - get the name associated with a routine
//
GEM_STR
gem_bb_rtn_get_name(

    GEM_BB_RTN	rtnhndl);


// gem_bb_rtn_get_obblen - Get the number of OBBS in a routine
//
//	Useful in allocating a vector for gem_bb_rtn_match_obbs
//
GEM_INT
gem_bb_rtn_get_obblen(

    GEM_BB_RTN	rtnhndl);	// The handle for the routine


// gem_bb_rtn_get_obbs - Set vectors for offsets and obbs
//
//	This routine initializes the offsets and obbs vectors
//	with the offsets (relative to the start of the routine)
//	and OBB handles for all of the obbs in this routine.
//
//	If the vectors are too small, GEM_BB_INVALID is returned.
//
GEM_INT
gem_bb_rtn_get_obbs(

    GEM_BB_RTN	rtnhndl,	// The handle for the routine

    GEM_INT	nelms,		// The size of each vector

    GEM_INT	offsets[],	// A vector of absolute offsets

    GEM_BB_OBB  obbs[]);	// A vector of OBB handles [optional]


// gem_bb_rtn_get_offset - Get the offset of this routine from the
//			   start of the text section
//
//	Routine offsets are not stored in the database.  It is
//	recomputed each time the database is read.  It is recomputed
//	automatically from symbol table information.
//
//	Since executable editors use the same information, offset
//	based lookups should never fail.
//
GEM_INT
gem_bb_rtn_get_offset(

    GEM_BB_RTN	rtnhndl);	// The handle for the routine


// gem_bb_rtn_get_sbblen - get the number of sbbs associated with a routine
//
GEM_INT
gem_bb_rtn_get_sbblen(
    GEM_BB_RTN  rtnhndl);


// gem_bb_rtn_get_sbb - get the Nth sbb associated with a routine
//
GEM_BB_SBB
gem_bb_rtn_get_sbb(
    GEM_BB_RTN  rtnhndl,
    GEM_INT	dex);


// gem_bb_rtn_get_size - get the size of a routine, in instructions
//
GEM_INT
gem_bb_rtn_get_size(
    GEM_BB_RTN  rtnhndl);


// gem_bb_rtn_get_split - is this a split procedure?
//
GEM_BOOLEAN
gem_bb_rtn_get_split(

    GEM_BB_RTN	rtnhndl);	// The routine handle


// gem_bb_rtn_get_source_count - Get the source count of rtn
//
GEM_IMAX
gem_bb_rtn_get_source_count(

    GEM_BB_RTN	rtnhndl);


// gem_bb_rtn_get_weight - get weighted count for a routine
//
GEM_IMAX
gem_bb_rtn_get_weight(

    GEM_BB_RTN	rtnhndl);	// The routine



// gem_bb_rtn_has_changed - Has rtn changed since it was read in?
//
//	If true is returned, the old entry has to be replaced in
//      the database.  the database will be inconsistent.
//
//	If false is returned, the old entry is still valid.
//
//	There can be external circumstances that invalidate unchanged
//	entries.  For example, the procid and fileid can be invalidated by
//	changes to the symbol table.  In this case, this routine should not
//	be called (and gem_bb_rtn_populate_io_buffer must be called).
//
//	NOTE:  This is currently a stub, and will always return true.
//
GEM_BOOLEAN
gem_bb_rtn_has_changed(

    GEM_BB_RTN	rtnhndl);	// The routine



// gem_bb_rtn_has_insn_events - Does this routine have instruction events?
//
//
GEM_BOOLEAN
gem_bb_rtn_has_insn_events(

    GEM_BB_RTN	rtnhndl);	// The routine



// gem_bb_rtn_has_name_collision - Was a bb_rtn matched multiple times?
//
//	In order for this to return true:
//
//          a database must have been read in
//
//          name based matching must have been used (w/out module disambiguation)
//
//	    a local entry which is in the database only once accidentally
//	    matched with multiple objects of the same name
//
GEM_BOOLEAN
gem_bb_rtn_has_name_collision(

    GEM_BB_RTN	rtnhndl);	// The routine



// gem_bb_rtn_has_valid_counts - Does this rtn have valid counts
//
//	In order for this to return true:
//
//          a database must have been read in
//
//          that database had counts
//		or
//	    a profile was read in and matched to the database for that routine
//
//	    if a source match was attempted, the source match was successful
//
GEM_BOOLEAN
gem_bb_rtn_has_valid_counts(

    GEM_BB_RTN	rtnhndl);	// The routine



// gem_bb_rtn_is_deferred - predicate to ask if a routine is deferred or not
//
GEM_BOOLEAN
gem_bb_rtn_is_deferred(

    GEM_BB_RTN	rtnhndl);



// gem_bb_rtn_match_obbs - Match the object basic blocks with an executable
//
//	This routine is used by executable editors.
//
//	The obb vector is allocated by the caller.
//
GEM_BOOLEAN
gem_bb_rtn_match_obbs(

    GEM_BB_RTN	rtnhndl,	// in: The handle for the routine

    GEM_INT	nblocks,	// in: The number of object basic blocks to match

    GEM_INT	offsets[],      // in: A vector of relative offsets (ascending)

    GEM_BB_OBB	obbs[]);	// out: If successful, a vector of matched obbs



// gem_bb_rtn_match_sbbs - Match the source blocks with the original source
//
//	This routine is used by compilers only.
//
GEM_BOOLEAN
gem_bb_rtn_match_sbbs(

    GEM_BB_RTN	rtnhndl,	// The handle for the routine

    GEM_INT	nblocks,	// The number of source basic blocks to match

    GEM_INT	linenums[],     // A vector of absolute line numbers

    GEM_INT	weaksets[],     // A vector of weak match indicators

    GEM_INT	unmatched[],    // The match succeeded, but these blocks weren't
				// matched.  Values in this array are:
				//	-nblocks..0    - it was matched
				//		       - sbb is dex + unmatched[dex] + 1
				//	nblocks	       - unmatched
				//	0..nblocks-1   - unmatched, but the
				//		         count can be derived
				//			 from the sbb at this index

    GEM_INT	annotations[],  // A vector of basic block annotations

    GEM_INT	npredsuccs,	// Number of pred/succ relationships

    GEM_INT	predsuccs[]);   // A vector of predecessor / successor relationships


// gem_bb_rtn_populate_io_buffer - Populate IO buffer with persistent form of
// routine entry
//
//	Populate IO buffer with persistent form of routine entry
//
//	A buffer is allocated and populated.
//	The buffer does not include the tag or length fields of
//	the data.  It is the reponsibility of the caller to write
//	the tag and length, and then write the data.
//
//	The return value is the length of the buffer returned.
//	A length of zero indicates that there is no data.
//
//	The buffer may be reused by subsequent calls to this routine.
//	The caller is expected to copy the buffer before the next call to
//	this routine is made.
//
//      The API assumes that the return buffer will be written to the
//	database. If it is not written, the database will be inconsistent.
//
GEM_INT
gem_bb_rtn_populate_io_buffer(

    GEM_BB_RTN	rtnhndl,	// The routine handle

    GEM_INT	*ptag,		// The tag to use in the TLV record

    GEM_STR	*pbuffer);	// The buffer for the persistent form



// gem_bb_rtn_remove_obbs - Delete all of the OBBS associated with a routine
//
void
gem_bb_rtn_remove_obbs(

    GEM_BB_RTN	rtnhndl);	// The routine handle


// gem_bb_rtn_replace_obbs - Replace all of the OBBS associated with a routine
//
//	This routine is used by executable editors.
//
//	The obb vector is allocated by the caller.
//
//	Returns true if the replacement occured.
//
GEM_BOOLEAN
gem_bb_rtn_replace_obbs(

    GEM_BB_RTN	rtnhndl,	// in: The handle for the routine

    GEM_BOOLEAN	keep_compiled,	// in: If true, only replace library routines
				//     (i.e., keep routines compiled with feedback).

    GEM_INT	nblocks,	// in: The number of OBBs 

    GEM_INT	offsets[],      // in: A vector of relative offsets (ascending)

    GEM_BB_OBB	obbs[]);	// out: A vector of replaced obbs


// gem_bb_rtn_set_count - Set the execution count of rtn to count
//			  Does nothing if rtn->obb_counts_valid is not set
//
void
gem_bb_rtn_set_count(

    GEM_BB_RTN	rtnhndl,	// The routine handle

    GEM_IMAX	count);		// The exectution count



// gem_bb_rtn_set_fileid - Set the file descriptor index for the routine
//
//	For Unix, the file id is the file descriptor index.
//
//	It is set by the compiler, and is an index relative to a particular
//	object file.  It is translated to an absolute index using tables
//	produced by the linker.
//
void
gem_bb_rtn_set_fileid(

    GEM_BB_RTN	rtnhndl,	// The routine handle

    GEM_INT	fileid);	// The file id



// gem_bb_rtn_set_procid - Set the symbol table index for the routine
//
//	For Unix, this is the index of the local symbol table entry for the
//	routine (each file descriptor has it's own symbol table).
//
void
gem_bb_rtn_set_procid(

    GEM_BB_RTN	rtnhndl,	// The routine handle

    GEM_INT	procid);	// The procedure id



// gem_bb_rtn_set_split - Indicate that this rtn is a split procedure
//
void
gem_bb_rtn_set_split(

    GEM_BB_RTN	rtnhndl);	// The routine handle



// gem_bb_rtn_set_src_count - Set the source execution count of rtn to count
//
void
gem_bb_rtn_set_src_count(

    GEM_BB_RTN  rtnhndl,        // The routine handle

    GEM_IMAX    count);         // The exectution count



// gem_bb_rtn_set_weight - Set weighted count for a routine
//
//	This is needed when routine counts are modified by inlining.
//
void
gem_bb_rtn_set_weight(

    GEM_BB_RTN	rtnhndl,	// The routine handle

    GEM_IMAX	weight);	// The weighted execution count



// gem_bb_rtn_sort_obbs_by_seqid - Sort the obbs for a routine by sequence id.
//
//	Before calling this routine, gem_bb_bb_set_seqid must be called
//	for each OBB in the routine.
//
//	It is an error for a sequence id to be out of range, including INVALID.
//
void
gem_bb_rtn_sort_obbs_by_seqid(

    GEM_BB_RTN	rtnhndl);	// The routine handle


// gem_bb_sbb_dump - Dump a single SBB
//
//	When used in GEM, this routine dumps its output to gem_db_g_output.
//	When used in the API, this routine dumps its output to stdout.
//
void
gem_bb_sbb_dump(

    GEM_BB_RTN	rtnhndl,

    GEM_BB_SBB	sbbhndl);	// The SBB to be dumped


// gem_bb_sbb_get_annotation - Get the SBB annotation
//
GEM_INT
gem_bb_sbb_get_annotation(
    GEM_BB_SBB  sbbhndl);


// gem_bb_sbb_get_count - Get the SBB execution count
//
GEM_IMAX
gem_bb_sbb_get_count(
    GEM_BB_SBB  sbbhndl);


// gem_bb_sbb_get_line - Get the line number associated with a source basic block
//
GEM_INT
gem_bb_sbb_get_line(
    GEM_BB_SBB  sbbhndl);


// gem_bb_sbb_get_predecessors - Get the predecessors associated with this SBB
//
//  returns the number of predecessors, and an array of sbb indexes (psuccs)
//  returns GEM_BB_INVALID if predecessor information is unavailable
//
//  NOTE: psuccs cannot be safely modified
//
GEM_INT
gem_bb_sbb_get_predecessors(
    GEM_BB_SBB  sbbhndl,    // the sbb
    GEM_INT32   **ppreds);  // a vector of predecessor ids


// gem_bb_sbb_get_successors - Get the successors associated with this SBB
//
//  returns the number of successors, and an array of sbb indexes (psuccs)
//  returns GEM_BB_INVALID if successor information is unavailable
//
//  NOTE: psuccs cannot be safely modified
//
GEM_INT
gem_bb_sbb_get_successors(
    GEM_BB_SBB  sbbhndl,    // the sbb
    GEM_INT32   **psuccs);  // a vector of successor ids


// gem_bb_sbb_get_succ_str - Get a string representation of the successors
//
GEM_INT
gem_bb_sbb_get_succ_str(
    GEM_BB_SBB  sbbhndl,   // the sbb
    GEM_INT32	sbbdex,	   // the index of this sbb
    GEM_STR     succstr);  // a string for representation of successor list


#ifdef NO_GEM

// gem_bb_set_debug_flags - Set 
//
//	This is used to mimic GEM's event and switch facilities in the API.
//
//	It is also used to manipulate non-event options.
//
//	With a debug version of the API, this routine can be used
//	to turn on or off various tracing actions.  With the
//	production version of the API, this routine does nothing.
//
//	This routine is not defined for use in compilers.
//
void
gem_bb_set_debug_flags(
    GEM_BB_DBG	flags);

// gem_bb_set_dump_flags - Set dump flags
//
//	Obsolete, use gem_bb_set_debug_flags instead.
//
void
gem_bb_set_dump_flags(

    GEM_BOOLEAN	dump_addresses,

    GEM_BOOLEAN	dump_counts_valid,

    GEM_BOOLEAN	dump_byte_offset,

    GEM_BOOLEAN	dump_dec_offset,

    GEM_BOOLEAN dump_counts_only);


// gem_bb_set_flags - Set 
//
//	Obsolete, use gem_bb_set_debug_flags instead.
void
gem_bb_set_flags(

    GEM_BOOLEAN	trace_change,	//

    GEM_BOOLEAN	trace_check,	//

    GEM_BOOLEAN	trace_io,	//

    GEM_BOOLEAN	trace_match,	// 

    GEM_BOOLEAN	trace_merge,	// 

    GEM_BOOLEAN	trace_rank,	//

    GEM_BOOLEAN	trace_profile,	//

    GEM_BOOLEAN	trace_reorder,	//

    GEM_BOOLEAN	resolve_references);	//

#endif


// gem_bb_set_ranking - Set the execution count histogram to a given value
//
//	This routine is used to read OPAL dumps.
//
void
gem_bb_set_ranking(
    GEM_BB_DB	dbhndl,
    GEM_INT	nelms,
    GEM_IMAX	separators[]);


// gem_bb_use_database - use memory mapped region for database read/write
//
//	This can be used instead of open_database whenever the user of the
//	API has an independent use of a memory mapped form of the database.
//
GEM_BB_ERR
gem_bb_use_database(
    GEM_BB_DB	*pdbfilhndl,
    GEM_STR	mmaparea,
    GEM_INT	length);


// gem_bb_use_pixie_profile - use the profile info in Addr and Counts vectors
//
//	The addrs and counts arrays cannot be safely deleted until
//	gem_bb_close_profile has been called.
//
//	If naddrs is one greater than ncounts, the last entry in addrs
//	is ignored and naddrs is made to equal ncounts.
//
//	The following GEM_BB_ERR_K_ error conditions can be returned:
//
//	    SUCCESS    - the operation completed successfully.
//
//	    CNTADDR_MISMATCH - naddrs and ncounts are not equal
//		       (after naddrs is canonicalized, if needed).
//
GEM_BB_ERR
gem_bb_use_pixie_profile(
    GEM_BB_PROFILE *pprofhndl,
    GEM_UINT	addrs[],
    GEM_UINT	naddrs,
    GEM_UMAX	counts[],
    GEM_UINT	ncounts);


#ifdef NO_GEM

// gem_bb_remove_counts - Remove counts from a database
//
//	This is not available in the GEM version of the API.
//
GEM_BOOLEAN
gem_bb_remove_counts(

    GEM_BB_DB	dbhndl);	// The database to be cleaned


// gem_bb_remove_events - Remove profile me events
//
//	This is not available in the GEM version of the API.
//
GEM_BOOLEAN
gem_bb_remove_events(

    GEM_BB_DB	dbhndl);	// The database to be cleaned

// gem_bb_remove_database - Remove a database from a file
//
//	This is not available in the GEM version of the API.
//
void
gem_bb_remove_database(

    GEM_BB_DB	dbhndl);	// The database to be removed


// gem_bb_remove_sbbs - Remove all SBBs (or just shadow SBBs) and their mappings
//
//	This is not available in the GEM version of the API.
//
GEM_BOOLEAN
gem_bb_remove_sbbs(

    GEM_BB_DB	dbhndl,		// The database to be cleaned

    GEM_BOOLEAN	shadows_only);	// remove all sbbs or shadows only


// gem_bb_write_database - Update the persistent form of a database
//
//	This is not available in the GEM version of the API.
//
void
gem_bb_write_database(

    GEM_BB_DB	dbhndl);	// The database to be written

#endif


// gem_bb_write_database_to_file - Write out a database to a file
//
//	This routine is used by API developers only.
//
void
gem_bb_write_database_to_file(

    GEM_BB_DB	dbhndl,		// The database to be written

    GEM_STR	txtfile);	// The name of the file to be written

#ifdef __cplusplus
} // extern "C"
#endif


#if defined(SPIKE_ENVIRONMENT) || ! defined(NO_GEM)
#include <gem_epilog.h>
#endif

#endif	// GEM_BB_HXX
