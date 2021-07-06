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
 * @(#)$RCSfile: prof_header.h,v $ $Revision: 4.2.21.1 $ (DEC) $Date: 2000/02/21 21:14:14 $
 */
/*
 * |-----------------------------------------------------------|
 * | Copyright (c) 1991 MIPS Computer Systems, Inc.            |
 * | All Rights Reserved                                       |
 * |-----------------------------------------------------------|
 * |          Restricted Rights Legend                         |
 * | Use, duplication, or disclosure by the Government is      |
 * | subject to restrictions as set forth in                   |
 * | subparagraph (c)(1)(ii) of the Rights in Technical        |
 * | Data and Computer Software Clause of DFARS 52.227-7013.   |
 * |         MIPS Computer Systems, Inc.                       |
 * |         950 DeGuigne Drive                                |
 * |         Sunnyvale, CA 94086                               |
 * |-----------------------------------------------------------|
 */

/* 
 * prof_header.h - definition of the headers for standard "mon.out",
 *                 ".Addrs", and ".Counts" files.
 *
 *                              NOTE
 *                              ====
 *
 * Since the V4.0 release of Tru64 UNIX, programs compiled with the
 * -p flag have written out a mon.out file in the new, self-describing,
 * extensible Profiling Data format, using <cmplrs/pdf.h> and libpdf.a.
 * Similarly, programs instrumented with the pixie(1) tool or, equivalently,
 * "atom -tool pixie"--see pixie(5)--have written out .Addrs and .Counts
 * files in the new Profiling Data format. The new format allows the prof(1)
 * tool to profile a program's shared libraries, to utilize additional
 * information such as the profiled machine's clock speed, and to
 * represent non-time profile data such as that collected by uprofile(1).
 *
 * Files in the new Profiling Data format can be converted to the standard
 * format with the pdtostd(1) command, and they can be examined with the
 * pddump(1) command. They can be processed using the <cmplrs/pdf.h> API,
 * but tools doing this should be careful to access all records and fields
 * strictly by name, and to allow for new record and field names to be
 * added in future releases. The API makes this easy to achieve.
 */

#ifndef _PROF_HEADER_H_
#define _PROF_HEADER_H_

/* Magic numbers of standard "mon.out", ".Addrs", and ".Counts" files. */

#define BBADDRS_MAGIC 0x0f0e0010
#define BBCOUNTS_MAGIC 0x0f0e0a11
#define BBCOUNTS_MAGIC_EV5 0x0f0e0a33
#define ICOUNTS_MAGIC 0x0f0e0012

#define ADDHASH(v, w) \
	((v) = ((v) << 5) ^ ((v) >> (32-5)) ^ (w))

#define MAGIC 0x0f0e0000
#define HAS_PC_SAMPLES 1
#define HAS_INV_COUNTS 2
#define HAS_BB_COUNTS 4
#define HAS_INT_SAMPLES 8 /* PC-samples are unsigned int, not unsigned short */

/* struct prof_header - header for standard "mon.out" files. */

struct prof_header {
   /* Lower and upper limits of pc values for pc-sampling */
   unsigned long low_pc;
   unsigned long high_pc;
   /* A magic number which tells "mprof" what data to expect in the
     profile output file, using the "define"s above */
   int p_opt_value;
   /* Size of the pc-sampling array, bytes */
   int pc_buf_size;
   /* Size of bb-counting array, bytes. Set to 0 in mon.out files */
   int count_buf_size;
   };

#define BB_SCALE 2	/* bb array is always half the size of text segment */
#define SAMPLE_PERIOD 10.0e-3 /* interval between pc samples in seconds */

/*
PC-sampling profile data:

A standard "mon.out" file consists of:

   struct prof_header the_header;
   unsigned short pc_buffer[the_header.pc_buf_size];
   unsigned int count_buffer[the_header.count_buf_size];

The count_buffer is optional and not generated for programs compiled -p.
By default, the Tru64 UNIX format "mon.out" file contains unsigned int
PC-samples instead of unsigned short. It uses the extensible Profile Data
format, and may contain profiles for multiple object files including 
shared libraries. See NOTE above.
*/

/*
Pixie basic-block profile data:

A standard ".Addrs" file consists of:

   unsigned int magic = BBADDRS_MAGIC;
   unsigned int hash;
   unsigned int addrs[n + 1];

A standard ".Counts" file consists of:

   unsigned int magic = BBCOUNTS_MAGIC;
   unsigned int hash;
   unsigned long count[n];

The Tru64 UNIX formats for these files contain equivalent information, 
but they use the extensible Profile Data format and may contain profiles
for multiple object files including shared libraries. See NOTE above.

To compute the hash, apply ADDHASH(hash, word) to each word of the .text,
.init, and .fini sections of the pre-pixie executable file. The addrs array 
gives the start of each basic block, expressed as a word offset from the 
beginning of the .text section.  These offsets appear in increasing order.
The last element of the array is the size of the section(s) in words. 
The Tru64 implementation of pixie covers only the .text section.

The count array gives the number of times the corresponding basic block was 
executed.  If any basic-block address in the addrs array is the same as the
next address, then the corresponding element of the count array is a count
of calls to the procedure that starts at the address.  If any basic-block 
address in the addrs array is zero, then the corresponding element of the 
count array is a branch-taken count.
*/
#endif /* _PROF_HEADER_H_ */
