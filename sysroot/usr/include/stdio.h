/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: stdio.h,v $
 * Revision 4.2.50.1  2008/03/03  14:49:37  Chilaka_Ravi_Kumar
 * 	Replaced sizeof(_L_tmpnam) with a hardwired value of "6"
 * 	to adhere to the open group standards QAR 100385.
 *
 * Revision 4.2.47.1  2001/09/11  15:17:08  Thomas_Peterson
 * 	Backport from wildcatos (wildcatos-129-bja).
 * 	Revision 4.2.40.1  2001/08/15  15:32:06  Thomas_Peterson
 * 	CLD 117-1-17992 & QAR 85821:
 * 	Correction of renaming conditions for fgetpos() & fsetpos().
 * 	Revision 4.2.33.2  2000/11/30  12:40:58  Barry_Andreasen
 * 	replaced versioned ANSI_C_SOURCE with ISO_C_SOURCE
 *
 * Revision 4.2.36.1  2000/11/30  22:06:20  Barry_Andreasen
 * 	added renaming macros to functions - fixes renaming for non-DECC use.
 *
 * Revision 4.2.33.1  2000/11/22  19:05:43  Barry_Andreasen
 * 	fixed use of va_list to consolidate va_list definition
 * 	[2000/11/21  21:02:18  Barry_Andreasen]
 *
 * 	change to support C99 functionality in snprintf functions
 * 	[2000/11/06  14:08:55  Barry_Andreasen]
 *
 * Revision 4.2.28.5  2000/01/11  18:34:49  Neil_Lewis
 * 	_Efgetpos and fpos_t struct should have same macro conditions.
 * 	qar 75981.
 *
 * Revision 4.2.28.4  1999/09/10  18:28:36  Neil_Lewis
 * Cosmetic fix after the merge..
 *
 * Revision 4.2.28.2  1999/08/25  18:28:06  Barry_Andreasen
 *  fixed broken extern_prefix logic
 *  [1999/07/30  21:58:21  Barry_Andreasen]
 *
 * Revision 4.2.27.3  1999/09/07  22:55:24  Neil_Lewis
 * Merge Information
 *     Merge Revision:  ZULUOS:4.2.28.3
 *     User  Revision:  Neil_Lewis_myzulu:4.2.27.2
 *    Common Ancestor:  1.1
 *
 * Revision 4.2.27.2  1999/08/18  20:36:11  Neil_Lewis
 * 	Fix cuserid() declaration so it's visible for C++. Qar 71054.
 *
 * Revision 4.2.21.14  1999/04/27  18:37:52  Patsy_Franklin
 * 	QAR 60673 - Previous fix missed non-inlined case.
 * 	[1999/04/27  17:14:52  Patsy_Franklin]
 * 
 * Revision 4.2.21.13  1999/03/26  18:36:29  Patsy_Franklin
 * 	The __CFE_putc macro needed to cast the input to _flsbuf
 * 	to unsigned char to match the non-inlined version and fix
 * 	QAR 60673.
 * 	[1999/03/25  20:02:00  Patsy_Franklin]
 * 
 * Revision 4.2.21.12  1999/02/17  20:01:17  Barry_Andreasen
 * 	Added missing prototypes for XSH5 - QAR 59307
 * 	[1999/02/17  19:59:35  Barry_Andreasen]
 * 
 * Revision 4.2.21.11  1998/12/03  22:27:38  John_Ferlan
 * 	Add support for long user names. Changes to L_cuserid and
 * 	changes to cuserid declaration.
 * 	[1998/11/20  20:37:27  John_Ferlan]
 * 
 * Revision 4.2.21.10  1998/02/12  18:52:56  Patsy_Franklin
 * 	Remove references to _STDIO_LOCK_CHAR_IO as it was
 * 	ambiguous and causing I/O to always be unlocked (even
 * 	when _REENTRANT or _THREAD_SAFE were set).
 * 	[1998/01/22  20:09:01  Patsy_Franklin]
 * 
 * Revision 4.2.21.9  1997/07/08  15:52:01  Patsy_Franklin
 * 	 	** Merge Information **
 * 		** Command used:	bmerge **
 * 		** Ancestor revision:	4.2.21.7 **
 * 		** Merge revision:	4.2.21.8 **
 * 	 	** End **
 * 	[1997/07/01  18:18:35  Patsy_Franklin]
 * 
 * 	Added #pragma __nostandard/__standard to eliminate compiler warnings
 * 	when INLINE_INTRINSICS is specified at compile time.
 * 	[1997/06/24  18:42:14  Patsy_Franklin]
 * 
 * Revision 4.2.21.8  1997/06/26  17:44:41  Jeff_Sullivan
 * 	Use __I(()) for intrinsic prototypes. See standards.h.
 * 	[1997/06/25  21:19:09  Jeff_Sullivan]
 * 
 * Revision 4.2.21.7  1997/06/03  19:31:53  Robert_Fontaine
 * 	Back out changes to stdin, stdout, and stderr.
 * 	[1997/06/03  17:21:26  Robert_Fontaine]
 * 
 * Revision 4.2.21.6  1997/05/30  19:15:22  Robert_Fontaine
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	4.2.21.4 **
 * 		** Merge revision:	4.2.21.5 **
 * 	 	** End **
 * 	Merged with latest revision from source pool
 * 	[1997/05/30  17:28:26  Robert_Fontaine]
 * 
 * 	Intial submit of MSE functionality
 * 	[1997/05/27  19:11:50  Robert_Fontaine]
 * 
 * Revision 4.2.21.5  1997/05/29  19:51:56  David_Long
 * 	Added UNIX98 fseeko() and ftello() functions to libc.
 * 	[1997/05/28  22:33:15  David_Long]
 * 
 * Revision 4.2.21.4  1997/04/10  19:10:17  David_Long
 * 	Fixed prototype for vsnprintf when "-std1 -D_POSIX_SOURCE" is used.  Also
 * 	Removed redundant CPLUSPLUS macro usage.
 * 	[1997/04/07  19:24:25  David_Long]
 * 
 * Revision 4.2.21.3  1997/03/30  21:50:34  David_Long
 * 	Turn off stdio intrinsics when building libc.  Added prototypes for UNIX98.
 * 	[1997/03/27  19:58:28  David_Long]
 * 
 * Revision 4.2.21.2  1997/01/17  21:23:29  Jeff_Sullivan
 * 	re-submit mistakenly reverted version of this file
 * 	[1997/01/17  21:20:19  Jeff_Sullivan]
 * 
 * Revision 4.2.19.2  1996/12/09  22:12:14  Neil_Lewis
 * 	Add prototype for fseek_unlocked().
 * 	[1996/11/15  23:04:08  Neil_Lewis]
 * 
 * Revision 4.2.17.5  1995/09/07  17:39:45  Blue_Tabor
 * 	Replace obsolete symbol _POSIX_SOURCE with POSIX 1003.1b symbol
 * 	_POSIX_C_SOURCE
 * 	[1995/08/21  02:02:35  Blue_Tabor]
 * 
 * Revision 4.2.17.4  1995/03/22  14:40:59  Thomas_Peterson
 * 	Changed _NAME_SPACE_WEAK_STRONG #ifdefs to _LIBC_POLLUTION_H_
 * 	#ifdefs so these will be picked up under libc and libext.
 * 	[1995/03/17  20:16:44  Thomas_Peterson]
 * 
 * Revision 4.2.17.3  1995/02/09  15:25:50  David_Lindner
 * 	ISO C Submit
 * 	[1995/01/26  16:38:10  David_Lindner]
 * 
 * Revision 4.2.17.2  1994/11/23  19:27:57  David_Long
 * 	Added _STDIO_LOCK_CHAR_IO.
 * 	[1994/11/23  16:26:02  David_Long]
 * 
 * Revision 4.2.15.2  1994/09/08  21:22:48  Gerry_Feldman
 * 	 Added intrinsics for putc & getc for Joe Mario - DECC.
 * 	[1994/09/08  18:37:51  Gerry_Feldman]
 * 
 * Revision 4.2.12.3  1994/02/14  19:15:35  Chris_Gillett
 * 	Added sprintf to list of intrinsics
 * 	[1994/02/11  19:42:24  Chris_Gillett]
 * 
 * Revision 4.2.12.2  1994/01/07  18:33:31  Thomas_Peterson
 * 	Merged C++ header changes fwd from sterl bl9 to gold bl8
 * 	[1994/01/05  17:26:02  Thomas_Peterson]
 * 
 * Revision 4.2.10.7  1993/12/15  22:14:21  Thomas_Peterson
 * 	Replaced awkward __cplusplus extern "C" ifdef blocks with
 * 	_BEGIN_CPLUSPLUS & _END_CPLUSPLUS macros from <standards.h>.
 * 	Also added these around fileno(), fdopen(), ctermid(), &
 * 	cuserid() which need to be declared this way for C++.  Added
 * 	ifdef around 1st ctermid() declaration so we only get 1 decl
 * 	if both _POSIX_SOURCE and _XOPEN_SOURCE are defined.
 * 	[1993/11/24  18:48:07  Thomas_Peterson]
 * 
 * Revision 4.2.10.6  1993/11/08  21:23:50  Ken_Lesniak
 * 	add ability to inline printf intrinsics
 * 	[1993/11/04  22:08:44  Ken_Lesniak]
 * 
 * Revision 4.2.10.5  1993/06/23  21:23:56  Thomas_Peterson
 * 	Added conditional directives for _NAME_SPACE_WEAK_STRONG (libc only)
 * 	to get rid of numerous warning messages in thread safe version.
 * 	[1993/06/15  16:17:54  Thomas_Peterson]
 * 
 * Revision 4.2.10.4  1993/06/08  20:41:52  Thomas_Peterson
 * 	Added _NONSTD_TYPES versions of fread() and fwrite() needed
 * 	for Ultrix/BSD compatibility.  Also changed libc Makefiles
 * 	to build fread.c and fwrite.c modules with -std1 so they get
 * 	the prototype declarations.
 * 	[1993/06/08  20:34:55  Thomas_Peterson]
 * 
 * Revision 4.2.10.3  1993/06/07  19:42:23  Thomas_Woodburn
 * 	I18N/thread-safe/ANSI-name-space joint submit.
 * 	[1993/06/07  18:31:22  Thomas_Woodburn]
 * 
 * Revision 4.2.9.3  1993/06/03  00:26:38  Thomas_Peterson
 * 	added conditional directives for name space
 * 	[1993/06/02  22:39:11  Thomas_Peterson]
 * 
 * Revision 4.2.10.2  1993/05/11  18:26:47  Sashi_Sashidhar
 * 	Changed getopt prototype to conform to SVID3.
 * 	[1993/04/29  17:52:39  Sashi_Sashidhar]
 * 
 * Revision 4.2.9.2  1993/05/07  20:04:09  Thomas_Peterson
 * 	Merge of OSF 1.2 version.  Moved duplicated items into <va_list.h>,
 * 	<getopt.h>, <sys/seek.h>.  New FILE struct format.
 * 	[1993/05/07  14:20:59  Thomas_Peterson]
 * 
 * Revision 4.2.2.13  1992/11/24  10:17:12  William_Burns
 * 	Removed obsolete sprintf declaration.
 * 	[92/11/13  11:53:23  William_Burns]
 * 
 * Revision 4.2.2.12  92/11/16  16:46:10  Gerry_Feldman
 * 	QAR4432: Added getopt(), optind, opterr, optarg as required by XPG3.
 * 	[92/11/10  12:51:31  Gerry_Feldman]
 * 
 * Revision 4.2.2.11  92/11/06  16:45:14  Brett_Sampson
 * 	added pragma intrinsic(printf, fprintf) which is conditional
 * 	on the _INTRINSICS symbol. This is the last thing that is done in this
 * 	file. The pragma will cause cfe to try to optimize uses of
 * 	printf and fprintf.
 * 	[92/11/04  17:49:27  Brett_Sampson]
 * 
 * Revision 4.2.2.10  92/06/01  13:08:48  Brett_Sampson
 * 	in response to QAR 03834
 * 	removed conditional:
 * 	#if defined(_REENTRANT) || defined(_THREAD_SAFE)
 * 	and its else clause to remove possible padding problems.
 * 	[92/06/01  13:07:54  Brett_Sampson]
 * 
 * Revision 4.2.2.9  92/04/27  14:47:51  Mike_Rickabaugh
 * 	Changed size_t to unsigned long and ptrdiff_t to signed long
 * 	[92/04/27  14:34:40  Mike_Rickabaugh]
 * 
 * Revision 4.2.2.8  92/04/23  14:38:20  Robin_Miller
 * 	Merged in Silver BL6-3 changes.
 * 	Revision 4.2.6.2  92/04/22  08:39:30  devbld_gsf
 * 	First AG_BL6_3 version.  Moved from Ag baselevel delivery tree.
 * 
 * 	Revision 4.2.5.5  92/04/10  11:16:31  Stephen_Strange
 * 	POSIX compliance changes for ISO 9945-1 (1990)
 * 	[92/03/30  18:16:37  Stephen_Strange]
 * 
 * 	Revision 4.2.5.4  92/04/08  11:55:10  David_Metsky
 * 	Added ctermid() definitions for POSIX work
 * 	[92/03/31  18:21:08  David_Metsky]
 * 
 * Revision 4.2.2.7  92/04/14  17:26:23  Robin_Miller
 * 	Merged in Silver BL6 changes.
 * 	Added C++ Support
 * 	[92/02/26  17:20:57  Craig_Horman]
 * 
 * 	Revision 4.2.5.2  92/02/25  11:39:49  Neil_OBrien
 * 	Modified to take advantage of increased open files capability
 * 	[92/02/21  12:44:20  Neil_OBrien]
 * 
 * Revision 4.2.2.6  92/03/30  11:11:26  Ken_Lesniak
 * 	Chris Gillett: fixup va_list declaration to match varargs.h and stdargs.h
 * 	[92/03/30  11:10:43  Ken_Lesniak]
 * 
 * Revision 4.2.2.5  92/03/18  16:13:44  Robin_Miller
 * 	Merged with Silver BL5
 * 	[92/03/18  16:12:25  Robin_Miller]
 * 
 * Revision 4.2.2.4  92/03/17  13:57:59  Mike_Rickabaugh
 * 	Changed size_t to unsigned int rather than unsigned long.
 * 	[92/03/17  13:54:04  Mike_Rickabaugh]
 * 
 * Revision 4.2.2.3  92/02/27  17:57:14  Jin_Chen
 * 	Jon Reeves: Fix dummy va_list type to match the real thing for alpha.
 * 	[92/02/27  17:03:03  Jin_Chen]
 * 
 * Revision 4.2.2.2  92/02/20  17:41:30  Mike_Rickabaugh
 * 	Changed NULL to 0L for 3.10 compiler version.
 * 	[92/02/20  17:39:42  Mike_Rickabaugh]
 * 
 * Revision 4.2  91/09/20  05:19:03  devbld
 * 	Adding ODE Headers
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: stdio.h,v $ $Revision: 4.2.50.1 $ (DEC) $Date: 2008/03/03 14:49:37 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * COMPONENT_NAME: stdio.h
 *                                                                    
 * ORIGIN: IBM
 *
 * Copyright International Business Machines Corp. 1985, 1988
 * All Rights Reserved
 * Licensed Material - Property of IBM
 *
 * stdio.h  1.40  com/inc,3.1,9021 5/12/90 06:54:44
 */                                                                   

#ifndef _STDIO_H_
#define _STDIO_H_

#include <standards.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *
 *      The ANSI and POSIX standards require that certain values be in stdio.h.
 *      It also requires that if _ANSI_C_SOURCE is defined or if 
 *      _POSIX_C_SOURCE is defined >= 1, then ONLY those values are present. 
 *      This header includes all the ANSI and POSIX required entries.
 *
 */

#ifdef _ANSI_C_SOURCE

/*
 *      The following definitions are included in <sys/types.h>.  They
 *      are also included here to comply with ANSI standards.
 */

#ifndef NULL
#define NULL    0L
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long   size_t;
#endif


#ifndef _FPOS_T
#define _FPOS_T
#if (_XOPEN_SOURCE >= 500)

typedef struct {

  void *_mbstate;
  long _fpos;
} fpos_t;

#else

typedef long fpos_t;

#endif
#endif


/*
 *      The definition of TMP_MAX is included in <sys/limits.h>.  It is
 *      also defined here to comply with ANSI standards.
 */

#ifndef TMP_MAX
#define TMP_MAX         16384
#endif

/*
 * Maximum fopens per process - OBSOLETE, sysconf() interface should be
 * used.
 */
#define FOPEN_MAX 	64

#define FILENAME_MAX 	255
#define BUFSIZ		8192

/* 
 * If the definition of _P_tmpdir is changed, then ensure
 * that L_tmpnam is also changed correspondingly.
 */
#define _P_tmpdir       "/tmp/"
#define L_tmpnam	21                  /* replaced  (sizeof(_P_tmpdir) + 15)  with 21 */

/*
 * _IOLBF means that a file's output will be buffered line by line
 * In addition to being flags, _IONBF, _IOLBF and _IOFBF are possible
 * values for "type" in setvbuf.
 */
#define _IOFBF		0000
#define _IOLBF		0200
#define _IONBF		0004


#ifndef EOF
#define EOF		(-1)
#endif

#include <sys/seek.h>

typedef struct {
	int	_cnt;
	unsigned int	_flag2;
 unsigned char	*_ptr;
	unsigned char	*_base;
	int	_bufsiz;
	short	_flag;
	short	_file;

#ifndef	__alpha
	void	*_unused;
#endif	/* __alpha */
	char	*__newbase;
	void	*_lock;			/* lock for thread safe library (or unused2) */
	unsigned char	*_bufendp;
} FILE;

extern FILE     _iob[];

#define _IOEOF		0020
#define _IOERR		0040

#define stdin           (&_iob[0])
#define stdout          (&_iob[1])
#define stderr          (&_iob[2])

#ifdef _NONSTD_TYPES
extern int     fread();
extern int     fwrite();
#else
extern size_t	fread __((void *, size_t, size_t, FILE *));
extern size_t	fwrite __((const void *, size_t, size_t, FILE *));
#endif  /* _NONSTD_TYPES */

extern int	_flsbuf __((int, FILE *));
extern int	_filbuf __((FILE *));
extern int 	ferror __((FILE *));
extern int 	feof __((FILE *));
extern void 	clearerr __((FILE *));
extern int 	putchar __((int));
extern int 	getchar __((void));
extern int 	putc __((int, FILE *));
extern int 	getc __((FILE *));
extern int	remove __((const char *));
extern int	rename __((const char *, const char *));
extern FILE 	*tmpfile __((void));
extern char 	*tmpnam __((char *));
extern int 	fclose __((FILE *));
extern int 	fflush __((FILE *));
extern FILE	*fopen __((const char *, const char *));
extern FILE 	*freopen __((const char *, const char *, FILE *));
extern void 	setbuf __((FILE *, char *));
extern int 	setvbuf __((FILE *, char *, int, size_t));
extern int	fprintf __I((FILE *, const char *, ...));
extern int	fscanf __((FILE *, const char *, ...));
extern int	printf __I((const char *, ...));
extern int	scanf __((const char *, ...));
extern int	sprintf __I((char *, const char *, ...));
extern int	sscanf __((const char *, const char *, ...));

#if defined(_OSF_SOURCE)||_XOPEN_SOURCE>=500 || (_ISO_C_SOURCE>=19990L)
# if (_ISO_C_SOURCE>=19990L) && !defined(_LIBC_POLLUTION_H_)
#  ifdef __DECC
#   pragma extern_prefix "_C"
#  else
/* These definitions are required for GNU or acc compiler use */
#   define snprintf(__a, __b, __c, __d) _Csnprintf(__a, __b, __c, __d)
#  endif
# endif  /* _ISO_C_SOURCE && LIBC_POLLUTION_H */

extern int	__C99(snprintf) __((char *, size_t, const char*, ...));

# if (_ISO_C_SOURCE>=19990L) && !defined(_LIBC_POLLUTION_H_) && defined(__DECC)
#  pragma extern_prefix ""
# endif  /* _ISO_C_SOURCE && LIBC_POLLUTION_H && DECC */
#endif	/* _OSF_SOURCE||XSH5||_ISO_C_SOURCE */

/*
 * Conditionalize va_list definition (see va_list.h)
 */
#ifdef _VA_LIST
# define __VA_LIST__	va_list
#else
# ifdef _XOPEN_SOURCE
#  include <va_list.h>
#  define __VA_LIST__	va_list
# else
#  define _HIDDEN_VA_LIST
#  include <va_list.h>
#  define __VA_LIST__	__va_list
# endif /* _XOPEN_SOURCE */
#endif /* _VA_LIST */

extern int  vfprintf __((FILE *, const char *, __VA_LIST__));
extern int  vprintf __((const char *, __VA_LIST__));
extern int  vsprintf __((char *, const char *, __VA_LIST__));
#if defined(_OSF_SOURCE)||_XOPEN_SOURCE>=500 || (_ISO_C_SOURCE>=19990L)
# if (_ISO_C_SOURCE>=19990L) && !defined(_LIBC_POLLUTION_H_)
#  ifdef __DECC
#   pragma extern_prefix "_C"
#  else
/* These definitions are required for GNU or acc compiler use */
#   define vsnprintf(__a, __b, __c, __d) _Cvsnprintf(__a, __b, __c, __d)
#  endif
# endif  /* _ISO_C_SOURCE && LIBC_POLLUTION_H */

extern int	__C99(vsnprintf) __((char *, size_t, const char*, __VA_LIST__));

# if (_ISO_C_SOURCE>=19990L) && !defined(_LIBC_POLLUTION_H_) && defined(__DECC)
#  pragma extern_prefix ""
# endif  /* _ISO_C_SOURCE && LIBC_POLLUTION_H && DECC */
#endif	/* _OSF_SOURCE||XSH5||_ISO_C_SOURCE */

extern int 	fgetc __((FILE *));
extern char 	*fgets __((char *, int, FILE *));
extern int 	fputc __((int, FILE *));
extern int 	fputs __((const char *, FILE *));
extern char 	*gets __((char *));
extern int 	puts __((const char *));
extern int	ungetc __((int, FILE *));
extern int 	fseek __((FILE *, long, int));

#if _XOPEN_SOURCE>=500
#include <sys/types.h>
extern int	fseeko __((FILE *, off_t, int));
extern off_t	ftello __((FILE *));

extern	int	ftrylockfile(FILE *);
extern	int	getc_unlocked(FILE *);
extern	int	getchar_unlocked(void);
extern	int	putc_unlocked(int, FILE *);
extern	int	putchar_unlocked(int);
#endif	 /* XSH5 */

#if (_XOPEN_SOURCE >=500) && !defined( _LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix "_E"
#else
/* These defs are required for compilers that don't support extern_prefix */
#define fgetpos(__a, __b) _Efgetpos(__a, __b)
#define fsetpos(__a, __b) _Efsetpos(__a, __b)
#endif
#endif /* _XOPEN_SOURCE >=500 && !_LIBC_POLLUTION_H_ */

extern int	__R500(fsetpos) __((FILE *, const fpos_t *));
extern int	__R500(fgetpos) __((FILE *, fpos_t *));

#if (_XOPEN_SOURCE >=500) && !defined( _LIBC_POLLUTION_H_) && defined(__DECC)
#pragma extern_prefix ""
#endif /* _XOPEN_SOURCE >=500 && !_LIBC_POLLUTION_H_ && __DECC */

extern long	ftell __((FILE *));
extern void	rewind __((FILE *));
extern void 	perror __((const char *));
#if defined(_REENTRANT) || defined(_THREAD_SAFE) || (_XOPEN_SOURCE>=500)
extern void	flockfile __((FILE *));
extern void	funlockfile __((FILE *));
#ifdef	_OSF_SOURCE
extern int	fclose_unlocked __((FILE *));
extern int	fflush_unlocked __((FILE *));
extern size_t	fread_unlocked __((void *, size_t, size_t, FILE *));
extern int 	fseek_unlocked __((FILE *, long int, int));
extern size_t	fwrite_unlocked __((const void *, size_t, size_t, FILE *));
#endif	/* _OSF_SOURCE */
#endif	/* _REENTRANT || _THREAD_SAFE || XSH5 */


/* Define commonly used macros here.
 */
#define _GETC_UNLOCKED(p) \
		(--(p)->_cnt < 0 ? _filbuf(p) : (int) *(p)->_ptr++)

#define _PUTC_UNLOCKED(x, p) \
		(--(p)->_cnt < 0 ? \
			_flsbuf((unsigned char) (x), (p)) : \
			(int) (*(p)->_ptr++ = (unsigned char) (x)))

#define _CLEARERR_UNLOCKED(p)	((void) ((p)->_flag &= ~(_IOERR | _IOEOF)))
#define _FEOF_UNLOCKED(p)	((p)->_flag & _IOEOF)
#define _FERROR_UNLOCKED(p)	((p)->_flag & _IOERR)
#define _FILENO_UNLOCKED(p)	((p)->_file)

#ifdef _INLINE_INTRINSICS
#pragma __nostandard
#undef _GETC_UNLOCKED
#define _GETC_UNLOCKED(p) __CFE_getc(p)
static __inline int __CFE_getc( FILE *__f )
{
    int cnt = __f->_cnt - 1;
    unsigned char * ptr = __f->_ptr;
    int c;

    __f->_cnt = cnt;

    if (cnt >= 0) {
        c = *ptr;
        __f->_ptr = ptr + 1;
        return c;
    }
    else {
        return _filbuf(__f);
    }
}

#undef _PUTC_UNLOCKED
#define _PUTC_UNLOCKED(x, p) __CFE_putc(x, p)
static __inline int __CFE_putc( int __c, FILE *__f )
{
    int cnt = __f->_cnt - 1;
    unsigned char * ptr = __f->_ptr;

    __f->_cnt = cnt;

    if (cnt >= 0) {
        *ptr = __c;
        __f->_ptr = ptr + 1;
    } else {
        __c = _flsbuf((unsigned char) (__c),__f);
    }

    return __c;
}
#pragma __standard
#endif

#if defined(_REENTRANT) || defined(_THREAD_SAFE)

#ifdef _LIBC_POLLUTION_H_
#undef getc_unlocked
#undef getchar_unlocked
#undef getc_locked
#undef getchar_locked
#undef putc_unlocked
#undef putchar_unlocked
#undef putc_locked
#undef putchar_locked
#endif
#define getc_unlocked(p)	_GETC_UNLOCKED(p)
#define getchar_unlocked()	getc_unlocked(stdin)
#define getc_locked(p)		fgetc(p)
#define getchar_locked()	getc_locked(stdin)
#define putc_unlocked(x, p)	_PUTC_UNLOCKED(x, p)
#define putchar_unlocked(x)	putc_unlocked(x,stdout)
#define putc_locked(x, p)	fputc(x, p)
#define putchar_locked(x)	putc_locked(x,stdout)

/*
 * At this point, we know that either _REENTRANT or _THREAD_SAFE
 * have been set and we need to check to see if the user has
 * explicitly requested unlocked I/O.
 *
 * The default for getc and putc are locked for compatibility with 
 * POSIX P1003.4a
 * By defining _STDIO_UNLOCK_CHAR_IO before including this
 * file, the default action is changed to unlocked putc and getc.
 * A file lock can still be placed around a block of putc's or getc's
 * regardless of the locking mode, and invoking the locked or
 * unlocked version directly always overrides the default action.
 */

#if defined(_STDIO_UNLOCK_CHAR_IO) 
#define getc(p)			getc_unlocked(p)
#define putc(x, p)		putc_unlocked(x, p)
/*
 * if _STDIO_UNLOCK_CHAR_IO is not defined, these macros will not be defined
 * and become functions.
 */
#define clearerr(p)		clearerr_unlocked(p)
#define feof(p)			feof_unlocked(p)
#define ferror(p)		ferror_unlocked(p)

#else
#define getc(p)			getc_locked(p)
#define putc(x, p)		putc_locked(x, p)
#endif /* _STDIO_UNLOCK_CHAR_IO */

#define clearerr_unlocked(p)	_CLEARERR_UNLOCKED(p)
#define feof_unlocked(p)	_FEOF_UNLOCKED(p)
#define ferror_unlocked(p)	_FERROR_UNLOCKED(p)
#define fileno_unlocked(p)	_FILENO_UNLOCKED(p)

#else /* _REENTRANT || _THREAD_SAFE */

#define getc(p)			_GETC_UNLOCKED(p)
#define putc(x, p)		_PUTC_UNLOCKED(x, p)
#define clearerr(p)		_CLEARERR_UNLOCKED(p)
#define feof(p)			_FEOF_UNLOCKED(p)
#define ferror(p)		_FERROR_UNLOCKED(p)

#endif /* _REENTRANT || _THREAD_SAFE */

#define getchar()		getc(stdin)
#define putchar(x)		putc((x), stdout)
#endif /*_ANSI_C_SOURCE */


/*
 *	The following are values that have historically been in stdio.h.
 *
 *	They are a part of the POSIX defined stdio.h and therefore are
 *	included when _XOPEN_SOURCE is defined and when _POSIX_C_SOURCE
 *      is defined >= 1.
 *
 */

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 1)
#include <sys/types.h>

#define L_ctermid	9

/* 
 * Value to determine the maximum number of bytes allowed in a username. 
 * This support is versioned to allow applications using the previous 
 * value to continue working without fear of overwriting buffer space.
 * The _O_L_cuserid is the value of L_cuserid prior to V5.0 to help
 * applications distinguish between the old and new value.
 */
#define _O_L_cuserid	9	
#if !defined(__V40_OBJ_COMPAT)
#define L_cuserid	64
#else
#define L_cuserid	9
#endif

extern int 	fileno __((FILE *));
extern FILE 	*fdopen __((int, const char *));

#ifndef _XOPEN_SOURCE
extern char *ctermid __((char *));
#endif

/* 
 * All this to define cuserid with prior object support
 */
#ifndef _LIBC_POLLUTION_H_
#if !defined(__V40_OBJ_COMPAT)
#ifdef __DECC
#pragma extern_prefix "_E"
#else
/* These definitions are required for GNU or acc compiler use */
#define cuserid(__a) _Ecuserid(__a)
#endif /* __DECC */
#endif /* __V40_OBJ_COMPAT */
#endif /* _LIBC_POLLUTION_H_ */

extern char *__V40_OC(cuserid) __((char *));

#if !defined(_LIBC_POLLUTION_H_) && !defined(__V40_OBJ_COMPAT) && defined(__DECC)
#pragma extern_prefix ""
#endif

#if !(defined(_REENTRANT) || defined(_THREAD_SAFE)) || defined(_STDIO_UNLOCK_CHAR_IO)
#ifdef _LIBC_POLLUTION_H_
#undef fileno
#endif
#define fileno(p)	_FILENO_UNLOCKED(p)
#endif	/* !(_REENTRANT || _THREAD_SAFE) || _STDIO_UNLOCK_CHAR_IO */

#endif /* _POSIX_C_SOURCE */


#ifdef _XOPEN_SOURCE

/*** To be withdrawn ***/
#include <getopt.h>			/* Also in unistd.h */
/***/

#define P_tmpdir	_P_tmpdir

extern char	*ctermid __((char *));
extern int 	getw __((FILE *));
extern int 	pclose __((FILE *));
extern int 	putw __((int, FILE*));
extern FILE 	*popen __((const char *, const char *));
extern char 	*tempnam __((const char*, const char*));

#endif /* _XOPEN_SOURCE */


#ifdef _OSF_SOURCE

#include <sys/limits.h>	/* limits.h not allowed by POSIX.1a.  Must be here */

/*
 * Maximum open files per process - OBSOLETE, sysconf() interface should 
 * be used
 */
#ifdef OPEN_MAX
#define _NFILE		OPEN_MAX
#else
#define _NFILE		64	/* should be a multiple of _NIOBRW */
#endif

/* buffer size for multi-character output to unbuffered files */
#define _SBFSIZ 8

#define _IOREAD		0001
#define _IOWRT		0002
#define _IOMYBUF	0010
#define _IOSTRG		0100
#define _IONOFD		_IOSTRG		/* strange or no file descriptor */
#define _IORW		0400
#define _IOUNGETC	01000
#define _IOINUSE	02000		/* new flag for _THREAD_SAFE */
#define _IONONSTD	04000
#define _IOCLOSE	010000
#define _IOWINIT	020000
#define _IOWSET		040000

#define _bufend(p)	((p)->_bufendp)
#define _bufsiz(p)	(_bufend(p) - (p)->_base)

extern void 	setbuffer __((FILE *, char*, int));
extern void 	setlinebuf __((FILE *));

#endif /* _OSF_SOURCE */

#ifndef	_LIBC_POLLUTION_H_
#ifdef _INTRINSICS
#pragma intrinsic(printf, fprintf,sprintf)

#ifdef _INLINE_INTRINSICS
#pragma __nostandard
static __inline int __CFE_print_puts( char *x )
{
 return( fputs( x, stdout  ));
}

static __inline int __CFE_print_putc( int x )
{
 putc( x, stdout );
 return( 1 );
}

static __inline int __CFE_print_putc_nl( int x )
{
 putc(x, stdout ); putc( '\n',stdout );
 return( 2 );
}

static __inline int __CFE_fprint_puts_nl( char *x, FILE *f )
{ 
 register int i;
 i = fputs( x, f ); 
 putc( '\n', f  ); 
 return( i+1 );
}

static __inline int __CFE_fprint_putc( int x, FILE *f )
{
 putc( x, f );
 return( 1 );
}

static __inline int __CFE_fprint_putc_nl( int x, FILE *f )
{
 putc( x,f ); putc( '\n', f );
 return(2);
}
#pragma __standard
#endif
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* _STDIO_H_ */

