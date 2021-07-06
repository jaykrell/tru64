/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: stat.h,v $
 * Revision 4.3.32.3  2006/03/29  21:06:14  Jim_Owens
 * 	Change default compile for stat structure so st_nlink is
 * 	posix standard and matches previous user binaries.  QAR 99546.
 *
 * Revision 4.3.32.2  2004/10/21  17:54:47  Charlie_Franks
 * 	Added support for >65K links.  QAR 97811.
 *
 * Revision 4.3.32.1  2002/12/18  21:22:57  Jeff_Wiener
 * 	stat.h can become confused if one of the internal temporary #defines is
 * 	already defined before stat.h is processed.  To try to eliminate this,
 * 	add defensive programming code.  The names of internal #define temps
 * 	have been changed to make them more unique.  We also make sure that
 * 	temporary #defines that are going to be used as flags are not currently
 * 	defined.  Qar 95463
 *
 * Revision 4.3.20.1  2001/10/17  17:19:19  Bob_Harris
 * 	QAR 84779
 * 	Change the stat(), fstat(), and lstat() to _F64_xxx() function
 * 	renaming for non-Compaq C compilers (C++, GNU C, other), to use a
 * 	jacket routine instead of #defines as the renaming trick.  It seems
 * 	that in C++ name space the #defines cause name space pollution.  One
 * 	such problem is that the popular open source desktop KDE can not be
 * 	built.
 *
 * Revision 4.3.13.12  1999/02/18  18:26:18  Bob_Harris
 * 	QAR 65209
 * 	Skip the function renaming inside the kernel.  This will allow the
 * 	kernel to name the stat() function stat() instead of the compiler
 * 	changing it to _F64_stat() behind the codes back.
 * 	[1999/02/10  18:39:27  Bob_Harris]
 *
 * Revision 4.3.13.11  1999/01/14  00:40:57  Ernie_Petrides
 * 	Merge from PTFCOS_BL3.
 * 	[1999/01/14  00:30:33  Ernie_Petrides]
 * 
 * Revision 4.3.16.2  1998/09/29  22:25:38  Brian_Haley
 * 	Added isfdtype() prototype for Posix 1003.1g Sockets support.
 * 	[1998/09/28  20:36:40  Brian_Haley]
 * 
 * Revision 4.3.13.10  1998/02/09  14:31:44  Bob_Harris
 * 	QAR 58154 - Remove the test for _SVID3_COMPAT.  _SVID3_COMPAT is
 * 	only valid for the SVVS4 testing environment, but doesn't help the
 * 	SVVS3 test environment.  Instead, a different approach is being
 * 	taken.
 * 
 * 	The reason we fail the SVVS3/SVVS4 test suites is because the tests
 * 	define MACROs of the form "#define xxx Zxxx" for every standard
 * 	UNIX library and system call, then they provide a private library of
 * 	Zxxx functions so that the linker is able to resolve the renamed
 * 	externals.  But our use of the extern_prefix pragma causes the names
 * 	that are created to be of the form _F64_Zxxx and neither libc nor
 * 	the SVVS3/SVVS4 code provides a function with a 'Z' in the middle of
 * 	its name.
 * 
 * 	The approach implemented in this change is to detect that the
 * 	program has provided its own MACRO for our function_name and to
 * 	defer to the program's choice of name by _NOT_ issuing the
 * 	extern_prefix pragma for that function.  However, we still provide
 * 	the new stat structure under the assumption that the program is
 * 	actually providing its own wrapper for our standard function and
 * 	that in the wrapper module the MACRO will _NOT_ be defined allowing
 * 	the wrapper code to call our real stat related function.  In all
 * 	cases the same stat structure would be passed around.  Tom Peterson
 * 	came up with this idea and helped me implement it (Thanks Tom).
 * 
 * 	If the program really wants the old stat structure, then
 * 	__V40_OBJ_COMPAT is still available to force the use of the old API.
 * 
 * 	The alternative was to disable stat features if __SVID__ was
 * 	detected, however, this would have effectively disabled the new stat
 * 	for every program compiled in the System V environment.
 * 	[1998/01/22  16:16:41  Bob_Harris]
 * 
 * Revision 4.3.13.9  1997/12/08  18:39:20  Bob_Harris
 * 	Add yet another condition for triggering __V40_OBJ_COMPAT.  If
 * 	_SVID3_COMPAT is defined, then use the old stat structures.  This
 * 	situation occurs when System V standard is invoked.  The System V
 * 	tests create #defines with a leading 'Z' for all the standard libc
 * 	functions (for example stat becomes Zstat).  The problem is that
 * 	this gets in the way of the extern_prefix pragma, because it then
 * 	generates _F64_Zstat which doesn't exist.  Of course the System V
 * 	standards test provide their own Zstat() function so this is how
 * 	they catch implementations that play renaming games.  Of course
 * 	this puts Digital in a situation were it it is difficult to migrate
 * 	the customers to a new API while maintaining source and binary
 * 	compatibility.  So we are forced into disabling the new stat
 * 	structure if _SVID3_COMPAT is defined.
 * 	[1997/11/26  19:26:44  Bob_Harris]
 * 
 * Revision 4.3.13.8  1997/11/24  14:14:45  Bob_Harris
 * 	Add another condition for triggering __V40_OBJ_COMPAT.  If neither
 * 	_OSF_SOURCE nor _XOPEN_SOURCE_EXTENDED are defined, then use the old
 * 	stat structures.  This situation occurs when the XPG4 standard is
 * 	invoked via -D_XOPEN_SOURCE.  XPG4 does not have an lstat() function
 * 	so we can not have an lstat() function prototype that we could
 * 	rename when using the new stat structure.  To protect ourselves from
 * 	generating bad code, we use the old stat structure when
 * 	-D_XOPEN_SOURCE is defined.
 * 	[1997/11/21  20:39:36  Bob_Harris]
 * 
 * Revision 4.3.13.7  1997/10/30  15:07:49  Bob_Harris
 * 	Do not undef the MACROs used to create the stat structure.  The
 * 	MACROs will be used in routines that need to be able to convert
 * 	between both old and new stat structures.
 * 	[1997/10/22  17:10:43  Bob_Harris]
 * 
 * Revision 4.3.13.6  1997/09/24  14:31:45  Bob_Harris
 * 	(st.vfs.024.UNIX98) Supports files greater than 1 terabyte.
 * 
 * 	When compiled under DECC, an extern_prefix pragma is used to rename
 * 	all stat(), fstat() and lstat() calls to F64_xxx().  #defines are
 * 	used for non-DECC compilers such as the C++ and gnu compilers.
 * 
 * 	If _XOPEN_SOURCE>=500, use blksize_t and blkcnt_t for st_blksize and
 * 	st_blocks otherwise use long for both.
 * 
 * 	Move st_blksize and st_blocks to the end of the structure and
 * 	increase their size to long to allow support for files greater than
 * 	1 terabyte in size.
 * 
 * 	Move st_ino, st_atime, st_mtime and st_ctime to the end of the
 * 	structure on longword alignment boundaries and follow them with
 * 	dummy fields (st_ino_reserved, st_atime_reserved, st_mtime_reserved
 * 	and st_ctime_reserved) that can be used to expand the size of any of
 * 	these fields, if in the future ino_t or time_t is changed from an
 * 	"int" to a "long".
 * 
 * 	Create a 2 byte fields call st_nlink_reserved to explicitly fill
 * 	a hole in the structure and reserve it for possible future st_nlink
 * 	expansion to 32 bits.
 * 
 * 	Add some spare fields to the stat structure.  Expanding the size of
 * 	the stat structure is very painful work.  Having spares makes it
 * 	very easy to add new fields with a minimum of work.
 * 
 * 	These changes force the stat structure to grow in size.  To minimize
 * 	the impact for existing applications and libraries, all the moved or
 * 	resized fields will be shadowed in their original locations at their
 * 	original sizes with field names of st_retired*.  If the value of
 * 	the shadowed field is too large, then the maximum value allowed for
 * 	the type of the original field will be stored (INT_MIN, INT_MAX or
 * 	UINT_MAX depending on the fields original type).  This allows call
 * 	back routines that were compiled on older versions of Digital UNIX,
 * 	which are passed a new larger stat structure, to behave normally
 * 	(for example ftw(3)).
 * 
 * 	__V40_OBJ_COMPAT is provided to allow developers a way to build stat
 * 	structures which are compatible with Digital UNIX V4.0 and earlier
 * 	versions.
 * 	[1997/09/22  19:57:23  Bob_Harris]
 * 
 * Revision 4.3.13.5  1997/08/04  20:40:34  Michael_Gilmore
 * 	Add ldev field to stat struct.
 * 	Removed cstat, fcstat, lcstat functions.
 * 	[1997/08/01  18:06:51  Michael_Gilmore]
 * 
 * Revision 4.3.13.4  1997/07/02  17:10:38  Michael_Gilmore
 * 	Added cstat, fcstat, lcstat for cluster device support.
 * 	[1997/06/30  20:09:45  Michael_Gilmore]
 * 
 * Revision 4.3.13.3  1996/12/09  22:01:35  Neil_Lewis
 * 	Make the mknod() prototype more accessible and
 * 	 change the _AES_SOURCE test to a _OSF_SOURCE test.
 * 	[1996/11/15  20:26:24  Neil_Lewis]
 * 
 * Revision 4.3.13.2  1996/03/25  15:31:24  Tim_Mark
 * 	Changed comment for st_dev.  QAR 42816.
 * 	[1996/03/21  18:25:08  Tim_Mark]
 * 
 * Revision 4.3.11.7  1995/09/07  17:37:43  Blue_Tabor
 * 	Replace obsolete symbol _POSIX_SOURCE with POSIX 1003.1b symbol
 * 	_POSIX_C_SOURCE
 * 	[1995/08/20  23:49:41  Blue_Tabor]
 * 
 * Revision 4.3.11.6  1995/07/28  21:21:16  Geoffrey_Cooper
 * 	Removed the _XOPEN_SOURCE_EXTENDED version of the stat
 * 	structure.  This is as per the permanent waiver for XPG4R2.
 * 
 * 	Cleaned up the prototyping so as to use the standards macro
 * 	__() rather than the _NO_PROTO blocks.  Also single
 * 	bracketed the source file for c++
 * 	[1995/07/06  17:57:28  Geoffrey_Cooper]
 * 
 * Revision 4.3.11.5  1995/06/08  18:47:35  Marcus_Barrow
 * 	Modified for XOPEN_SOURCE_EXTENDED compliance.  When
 * 	XOPEN_SOURCE_EXTENDED is defined the stat struct will have blocksize
 * 	and count represented by longs.  The old struct is available as
 * 	__Ostat.
 * 	[1995/06/08  18:06:56  Marcus_Barrow]
 * 
 * Revision 4.3.11.4  1994/12/20  17:50:01  Christine_Ahrens
 * 	     Changed comment for st_mode component of stat structure.
 * 	[1994/12/14  19:08:31  Christine_Ahrens]
 * 
 * Revision 4.3.11.3  1994/10/06  22:45:24  Deepak_Gupta
 * 	Removed mknod prototype from the DEC OSF/1 name space
 * 	[1994/10/06  22:42:09  Deepak_Gupta]
 * 
 * Revision 4.3.11.2  1994/10/05  19:03:15  Deepak_Gupta
 * 	Merged with platinum .BL1
 * 	[1994/10/05  18:25:45  Deepak_Gupta]
 * 
 * Revision 4.3.9.2  1994/08/05  21:14:04  Deepak_Gupta
 * 	Name space changes for spec1170
 * 	[1994/08/05  21:13:53  Deepak_Gupta]
 * 
 * Revision 4.3.7.3  1994/06/28  19:11:38  Aju_John
 * 	fix for qar 24515
 * 	[1994/06/28  15:13:48  Aju_John]
 * 
 * Revision 4.3.7.2  1994/06/21  14:35:12  Aju_John
 * 	added prototype for fchmod
 * 	[1994/06/21  14:33:56  Aju_John]
 * 
 * Revision 4.3.4.3  1992/04/23  15:36:07  Anton_Verhulst
 * 	Merge in BL6.
 * 	[92/04/23  15:26:59  Anton_Verhulst]
 * 
 * Revision 4.3.4.2  92/04/15  14:12:17  Shashi_Mangalat
 * 	Merged in Silver BL6.
 * 	Added C++ Support.  [Craig_Horman]
 * 	[92/04/15  13:25:36  Shashi_Mangalat]
 * 
 * Revision 4.2.2.3  92/04/10  11:16:13  Stephen_Strange
 * 	POSIX compliance changes for ISO 9945-1 (1990)
 * 	[92/03/30  18:16:22  Stephen_Strange]
 * 
 * Revision 4.2.2.2  92/03/27  15:14:34  Craig_Horman
 * 	Merge with AG
 * 	[92/03/27  13:41:50  Craig_Horman]
 * 
 * 	Merge with BL5
 * 	[92/03/10  12:34:38  Craig_Horman]
 * 
 * 	Added C++ Support
 * 	[92/02/26  18:54:16  Craig_Horman]
 * 
 * Revision 4.3  92/01/15  02:12:23  devbld_gsf
 * 	Baselevel alpha_bl002
 * 
 * Revision 4.2.2.2  91/12/07  16:52:06  Jay_Estabrook
 * 	merge ALPHA with SILVER via ODE
 * 	[91/12/07  16:38:24  Jay_Estabrook]
 * 
 * Revision 4.2  91/09/19  23:00:24  devbld
 * 	Adding ODE Headers
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: stat.h,v $ $Revision: 4.3.32.3 $ (DEC) $Date: 2006/03/29 21:06:14 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */

/*
 * COMPONENT_NAME: SYSLFS - Logical File System
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _SYS_STAT_H_
#define _SYS_STAT_H_

#include <standards.h>
#include <sys/types.h>
#include <sys/mode.h>

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * Defensive programming.  Make sure that temporary #defines that are going
 * to be used as flags are not currently defined.
 */
#if defined(__TMP_EXTERN_PREFIX)
#  undef __TMP_EXTERN_PREFIX
#endif
#if defined(__TMP_V40_OBJ_COMPAT)
#  undef __TMP_V40_OBJ_COMPAT
#endif
#if defined(__TMP_USE_JACKET)
#  undef __TMP_USE_JACKET
#endif

#if defined(_KERNEL) && defined(__V40_OBJ_COMPAT)
#  undef __V40_OBJ_COMPAT  /* The kernel is always built with _F64_ support */
#endif

#if defined(__V40_OBJ_COMPAT) || (!defined(_OSF_SOURCE) && !defined(_XOPEN_SOURCE_EXTENDED))
   /*
    * We are here because either __V40_OBJ_COMPAT is defined, XPG4 standard
    * compliance has been requested, or ISO C or ANSI C standard compliance
    * has been requested. 
    *
    * __V40_OBJ_COMPAT specifies this module is to be compiled so that the
    * stat structure and the stat(), fstat() and lstat() routines used will
    * be compatible with old object modules and libraries generated on
    * Compaq Tru64 UNIX V4.0* (or earlier).  This is useful when old object
    * modules and libraries are linked with newly compiled object modules
    * _AND_ there is a need to pass stat structures between these modules.
    * Otherwise using __V40_OBJ_COMPAT is not recommended. 
    *
    * The XPG4, ISO C and ANSI C standards do not have an lstat() function,
    * so to adhere to the standards we cannot define a function prototype
    * for lstat(), and if we cannot have a function prototype for lstat(),
    * we are forced to use the older stat structures.  If no standards are
    * requested or if a more recent standard is requested (XPG4.2 [UNIX95],
    * XPG5 [UNIX98], etc...), then lstat() is supposed to have a function
    * prototype and we use the new stat structures.  See the "standards" man
    * page. 
    */
#  define __TMP_V40_OBJ_COMPAT
#endif

/*
 * POSIX requires that certain values be included in stat.h.  It also
 * requires that when _POSIX_C_SOURCE is defined >= 1, only those standard
 * specific values are present.  This header includes all the POSIX
 * required entries.
 */

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 1) 

/*
 * Stat structure
 */

#if _XOPEN_SOURCE>=500		/* see the "standards" man page */
#define __BLKSIZE_T blksize_t
#define __BLKCNT_T  blkcnt_t
#else   /* _XOPEN_SOURCE<500 */
#define __BLKSIZE_T long
#define __BLKCNT_T  long
#endif  /* _XOPEN_SOURCE>=500 */

#define st_spare1 st_uatime
#define st_spare2 st_umtime
#define st_spare3 st_uctime

/* The standard filesystem support for Tru64 has a 16-bit link
 * count which permits 65533 links.  Beginning in BL26, the kernel
 * returns a 32-bit link count to work with a larger filesystem.
 * The base Tru64 commands are also compiled for a 32-bit st_nlink
 * to function correctly when filesystems return values > 65535.
 * To retain binary compatibility in other structures, the nlink_t
 * type definition must remain a 16-bit ushort_t.
 *
 * The default compile will produce a 16-bit nlink_t st_nlink and
 * stat structure definition that matches all prior V5.1 releases.
 * User applications can compile with -D_ST_NLINK_UINT to use the
 * 32-bit st_nlink.  On filesystems that have < 65536 link counts
 * and on all older kernels that return 16-bit st_nlink values, a
 * program compiled with either the 16-bit or 32-bit st_nlink will 
 * see the same value returned from the kernel.
 */

/* Must force original 16-bit st_nlink for Tru64 compatibility libraries */
#if defined(__OLD_ST_NLINK_TYPE)
#define __EXPAND_ST_NLINK__                                                   \
        nlink_t   st_nlink;          /* Number of links - 16 bits max */      \
        short     st_nlink_reserved; /* Always 0 before V5.1B BL26 */
/* Tru64 builds and modified user applications see a 32-bit st_nlink */
#elif defined(_KERNEL) || defined(_ST_NLINK_UINT)
#define __EXPAND_ST_NLINK__                                                   \
        uint_t    st_nlink;          /* Number of links  - 32 bits max */
/* All other applications see the original V5.0 nlink_t definition */
#else
#define __EXPAND_ST_NLINK__                                                   \
        nlink_t   st_nlink;          /* Number of links - 16 bits max */      \
        short     st_nlink_reserved; /* link count msw as of V5.1B BL26 */
#endif

#define __F64_STAT                                                      \
        dev_t     st_dev;            /* ID of device containing a directory*/ \
                                     /*   entry for this file.  File serial*/ \
                                     /*   no + device ID + file generation */ \
                                     /*   number uniquely identify the file*/ \
                                     /*   within the system */                \
        int       st_retired1;                                                \
        mode_t    st_mode;           /* File mode; see #define's in */        \
                                     /*   sys/mode.h */                       \
        __EXPAND_ST_NLINK__                                                   \
        uid_t     st_uid;            /* User ID of the file's owner */        \
        gid_t     st_gid;            /* Group ID of the file's group */       \
        dev_t     st_rdev;           /* ID of device */                       \
                                     /*   This entry is defined only for */   \
                                     /*   character or block special files */ \
        dev_t     st_ldev;           /* Local ID of device:  */               \
                                     /*  conversion of Cluster ID (st_rdev)*/ \
                                     /*  This entry is valid only for */      \
                                     /*  character or block special files */  \
        off_t     st_size;           /* File size in bytes */                 \
                                                                              \
        time_t    st_retired2;                                                \
        int       st_uatime;         /* Microseconds of st_atime */           \
        time_t    st_retired3;                                                \
        int       st_umtime;         /* Microseconds of st_mtime */           \
        time_t    st_retired4;                                                \
        int       st_uctime;         /* Microseconds of st_ctime */           \
                                                                              \
        int       st_retired5;                                                \
        int       st_retired6;                                                \
                                                                              \
        uint_t    st_flags;          /* user defined flags for file */        \
        uint_t    st_gen;            /* file generation number */             \
                                                                              \
        long      st_spare[4];                                                \
                                                                              \
        ino_t     st_ino;            /* File serial number */                 \
        int       st_ino_reserved;   /* DO NOT USE - this may go away */      \
                                                                              \
                                     /* Times measured in seconds since */    \
                                     /*   00:00:00 GMT, Jan. 1, 1970 */       \
        time_t    st_atime;          /* Time of last access */                \
        int       st_atime_reserved; /* DO NOT USE - this may go away */      \
        time_t    st_mtime;          /* Time of last data modification */     \
        int       st_mtime_reserved; /* DO NOT USE - this may go away */      \
        time_t    st_ctime;          /* Time of last file status change */    \
        int       st_ctime_reserved; /* DO NOT USE - this may go away */      \
                                                                              \
        __BLKSIZE_T st_blksize;      /* Preferred I/O blk size (typedef) */   \
        __BLKCNT_T  st_blocks;       /* blocks allocated for file (typedef)*/


#define __PRE_F64_STAT \
        dev_t   st_dev;         /* ID of device containing a directory*/      \
                                /*   entry for this file.  File serial*/      \
                                /*   no + device ID uniquely identify */      \
                                /*   the file within the system */            \
        ino_t   st_ino;         /* File serial number */                      \
        mode_t  st_mode;        /* File mode; see #define's in */             \
                                /*   sys/mode.h */                            \
        nlink_t st_nlink;       /* Number of links */                         \
        uid_t   st_uid;         /* User ID of the file's owner */             \
        gid_t   st_gid;         /* Group ID of the file's group */            \
        dev_t   st_rdev;        /* ID of device */                            \
                                /*   This entry is defined only for */        \
                                /*   character or block special files */      \
        off_t   st_size;        /* File size in bytes */                      \
                                                                              \
                                /* Times measured in seconds since */         \
                                /*   00:00:00 GMT, Jan. 1, 1970 */            \
        time_t  st_atime;       /* Time of last access */                     \
        int     st_uatime;                                                    \
        time_t  st_mtime;       /* Time of last data modification */          \
        int     st_umtime;                                                    \
        time_t  st_ctime;       /* Time of last file status change */         \
        int     st_uctime;                                                    \
                                                                              \
        uint_t  st_blksize;     /* Preferred I/O block size */                \
        int     st_blocks;      /* blocks allocated for file */               \
                                                                              \
        uint_t  st_flags;       /* user defined flags for file */             \
        uint_t  st_gen;         /* file generation number */


#if ! defined(__TMP_V40_OBJ_COMPAT)
  struct stat {
        __F64_STAT
  };
#else /* !__TMP_V40_OBJ_COMPAT */
  struct stat {
        __PRE_F64_STAT		/* Old V4.0 Compatible stat structure */
  };
#endif /* __TMP_V40_OBJ_COMPAT */


#if defined(_KERNEL)
  struct  __pre_F64_stat {
	__PRE_F64_STAT	/* supports backward compatibility in kernel builds */
  }; 
#endif /* _KERNEL */


/*
 * The following comments are for kernel developers.  Users should refer
 * to the stat man page and Compaq Tru64 UNIX documentation for proper use
 * of the stat functions. 
 *
 * Transparently to users, rename any references to stat(), fstat() and
 * lstat() so that they call the _F64_xxx() versions of these routines. 
 * The _F64_xxx() versions return the larger stat structure.  This should be
 * transparent to the user.  Users should _NOT_ reference the _F64_xxx()
 * names directly.  Users should call stat(), fstat() and lstat() as usual
 * and allow this stat.h header file to perform the necessary function
 * renaming.  This will allow user code to remain portable. 
 */
#define __STAT__   stat	/* default to old stat */
#define __FSTAT__ fstat	/* default to old fstat */
#define __LSTAT__ lstat	/* default to old lstat */

#if defined(__TMP_V40_OBJ_COMPAT)
  /*
   * We are here because either __V40_OBJ_COMPAT is defined, XPG4
   * standard compliance has been requested, or ISO C or ANSI C standard
   * compliance has been requested.  This path will cause this module to be
   * compiled so that the stat structure and the stat(), fstat() and lstat()
   * routines used will be compatible with old object modules and libraries
   * generated on Compaq Tru64 UNIX V4.0 (or earlier).  This is useful when
   * old object modules and libraries are linked with newly compiled object
   * modules _AND_ there is a need to pass stat structures between these
   * modules.  Otherwise using __V40_OBJ_COMPAT is not recommended. 
   */
# if defined(_KERNEL)
#   error __V40_OBJ_COMPAT must NOT be defined if _KERNEL is defined
# endif
#else  /* ! __TMP_V40_OBJ_COMPAT */
  /*
   * Rename stat(), fstat() and lstat() to the _F64_xxx() family.
   *
   * NOTE:  libc does its own renaming and inside the kernel the renaming 
   *        is not needed.
   */
# if ! defined(_LIBC_POLLUTION_H_) && ! defined(_KERNEL)
#   if defined(__DECC)
      /* 
       * While extern_prefix "_F64_" is in effect, all function prototypes
       * the Compaq C compiler sees will be marked so that any future uses
       * of that function during this compile will generate a call that has
       * "_F64_" as a prefix to its name.
       */ 
#     define __TMP_EXTERN_PREFIX /* rename via #pragma extern_prefix "_F64_" */
#   else  /* ! __DECC */
      /*
       * Non-Compaq C compilers will be given jacket routines to effectively
       * rename stat(), fstat(), and lstat() to their newer _F64_xxx()
       * equivalents (preferably inline jackets that the compiler will
       * optimize away).  The decision to use jackets instead of #define's
       * is because an inline jacket in C++ does not pollute the name space
       * like a #define renaming trick would. 
       *
       * The type of jacket (static or inline) is determined by what type
       * of non-Compaq C compiler is being used and whether C++ style 
       * function prototypes are allowed (_NO_PROTO).
       *
       * Jackets are not generated if it is Compaq C (__DECC) nor are
       * jackets generated if a #define for the function already exists (a
       * common trick used in standards validation test suites).
       */
#     if defined(_NO_PROTO)
#       define __TMP_USE_JACKET static
#     elif defined(__cplusplus)
#       define __TMP_USE_JACKET inline
#     elif defined(__GNUC__)
#       define __TMP_USE_JACKET __inline__ static
#     else
#       define __TMP_USE_JACKET static
#     endif

      /*
       * Setup so that the extern function prototype is given the _F64_xxx()
       * name that the jacket will be calling. 
       *
       * If the function name has a pre-existing #define already renaming
       * it, then do not rename the extern function prototype.  It is
       * assumed that the application either does not want to call stat(),
       * fstat(), or lstat(), or that the renamed function will handle it in
       * a different module (this is a common trick in the standards
       * validation test suites). 
       */
#     if !defined(stat)
#       undef  __STAT__
#       define __STAT__  _F64_stat	/* Add _F64_ prefix */
#     endif
#     if !defined(fstat)
#       undef  __FSTAT__
#       define __FSTAT__ _F64_fstat	/* Add _F64_ prefix */
#     endif
#     if !defined(lstat)
#       undef  __LSTAT__
#       define __LSTAT__ _F64_lstat	/* Add _F64_ prefix */
#     endif
#   endif /* __DECC */
# endif /* _LIBC_POLLUTION_H_ */
#endif /* __TMP_V40_OBJ_COMPAT */
/*
 * Define the function prototypes for stat, fstat and lstat.  The __(())
 * MACRO is used to control whether ANSI C or K&R style function prototypes
 * are declared.  
 *
 * The normal path will have __TMP_EXTERN_PREFIX defined (Compaq C), which
 * will result in the extern_prefix pragma being used when declaring the
 * function prototypes.  This will result in any future use of stat(),
 * fstat(), or lstat() to be renamed inside of the Compaq C compiler to
 * _F64_xxx() names. 
 *
 * If a compiler other than Compaq C is being used then, then jacket
 * functions will be created to provide the renaming.
 *
 * If the program has created its own #define wrapper function MACROs to
 * rename one of the stat, fstat, or lstat functions, then that function
 * will be declared using the name provided by the program's MACRO.  The
 * wrapper function prototypes are declared using the new stat structure
 * (Wrappers that want the old stat structure should be compiled with
 * __V40_OBJ_COMPAT). 
 *
 * Finally if either __V40_OBJ_COMPAT is defined, XPG4 standard compliance
 * has been requested, or ISO C or ANSI C standard compliance has been
 * requested, then the function prototypes will be declared using the names
 * stat, fstat, and lstat (no function renaming will occur).  Calls to these
 * functions will return the old stat structure. 
 *
 * Again, please do not write programs that directly call _F64_xxx named
 * functions.  Use the standard stat, fstat, and lstat function names and
 * allow this header file to perform the necessary renaming as part of the
 * compile.  That way the program will remain portable. 
 */

/*
 * Declare the stat() function prototype.
 */
# if !defined(stat) && defined(__TMP_EXTERN_PREFIX)
#   pragma extern_prefix "_F64_"
# endif
  extern int __STAT__ __((const char *, struct stat *));
# if defined(__TMP_EXTERN_PREFIX)
#   pragma extern_prefix ""
# endif
# if  !defined(_NO_PROTO) && defined(__TMP_USE_JACKET) && !defined(stat)
    __TMP_USE_JACKET int stat(const char *__a, struct stat *__b) {
      return(_F64_stat(__a,__b));
    }
# elif defined(_NO_PROTO) && defined(__TMP_USE_JACKET) && !defined(stat)
    __TMP_USE_JACKET int stat(__a,__b) const char *__a; struct stat *__b; {
      return(_F64_stat(__a,__b));
    }
# endif /* __TMP_USE_JACKET && _NO_PROTO */


/*
 * Declare the fstat() function prototype.
 */
# if !defined(fstat) && defined(__TMP_EXTERN_PREFIX)
#   pragma extern_prefix "_F64_"
# endif
  extern int __FSTAT__ __((int , struct stat *));
# if defined(__TMP_EXTERN_PREFIX)
#   pragma extern_prefix ""
# endif
# if  !defined(_NO_PROTO) && defined(__TMP_USE_JACKET) && !defined(fstat)
    __TMP_USE_JACKET int fstat(int __a, struct stat *__b) {
      return(_F64_fstat(__a,__b));
    }
# elif defined(_NO_PROTO) && defined(__TMP_USE_JACKET) && !defined(fstat)
    __TMP_USE_JACKET int fstat(__a,__b) int __a; struct stat *__b; {
      return(_F64_fstat(__a,__b));
    }
# endif /* __TMP_USE_JACKET && _NO_PROTO */

/*
 * Declare the lstat() function prototype.
 */
# if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)
#   if !defined(lstat) && defined(__TMP_EXTERN_PREFIX)
#     pragma extern_prefix "_F64_"
#   endif
    extern int __LSTAT__ __((const char *, struct stat *));
#   if defined(__TMP_EXTERN_PREFIX)
#     pragma extern_prefix ""
#   endif
#   if  !defined(_NO_PROTO) && defined(__TMP_USE_JACKET) && !defined(lstat)
      __TMP_USE_JACKET int lstat(const char *__a, struct stat *__b) {
        return(_F64_lstat(__a,__b));
      }
#   elif defined(_NO_PROTO) && defined(__TMP_USE_JACKET) && !defined(lstat)
      __TMP_USE_JACKET int lstat(__a,__b) const char *__a; struct stat *__b; {
        return(_F64_lstat(__a,__b));
      }
#   endif /* __TMP_USE_JACKET && _NO_PROTO */
# endif /* _OSF_SOURCE || _XOPEN_SOURCE_EXTENDED */

/*
 * clean up
 */
#if defined(__TMP_EXTERN_PREFIX)
#  undef __TMP_EXTERN_PREFIX
#endif
#if defined(__TMP_V40_OBJ_COMPAT)
#  undef __TMP_V40_OBJ_COMPAT
#endif
#if defined(__TMP_USE_JACKET)
#  undef __TMP_USE_JACKET
#endif
#undef __STAT__
#undef __FSTAT__
#undef __LSTAT__


#ifndef _KERNEL
extern int	mkdir __((const char *, mode_t ));
extern mode_t	umask __((mode_t ));

extern int	chmod __((const char *, mode_t ));
#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)
extern int	fchmod __((int, mode_t ));
#ifdef _XOPEN_SOURCE_EXTENDED
extern int	mknod __((const char *, mode_t, dev_t ));
#else
extern int	mknod __((const char *, mode_t, ... ));
#endif
#endif /* _OSF_SOURCE || _XOPEN_SOURCE_EXTENDED */
extern int	mkfifo __((const char *, mode_t ));
/* This is required for POSIX 1003.1g Sockets compliance */
#ifdef _POSIX_PII
extern int	isfdtype __((int, int));
#endif /* _POSIX_PII */
#endif /* _KERNEL */

#endif /* _POSIX_C_SOURCE */

#ifdef _OSF_SOURCE

#define S_BLKSIZE       512     /* block size used in the stat struct */

#endif /* _OSF_SOURCE */

#if defined(__cplusplus)
}
#endif

#endif /* _SYS_STAT_H_ */
