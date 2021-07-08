/* OSF/1 is missing a few things.
 * uname -srm: OSF1 V5.1 alpha
 *
 * This is mainly for Python3, so far.
 */
#if defined(__osf__) && defined(__arch64__)

/* some standard facilities require specific request to reveal */
#define __STDC_CONSTANT_MACROS 1
#define __STDC_LIMIT_MACROS 1
#define __STDC_FORMAT_MACROS 1

#undef _ISO_C_SOURCE
#define _ISO_C_SOURCE 199901
#define _OSF_SOURCE 1
#define _ANSI_C_SOURCE 1
#define _XOPEN_SOURCE 700       /* The highest value in OSF1 is 500 but match Python3 */
#define _POSIX_C_SOURCE 200809L /* The highest value in OSF1 is 199506L but match Python3 */

/* standards.h typically defines _XOPEN_SOURCE_EXTENDED,
 * which hides symbols, such as NSIG, copysign, yes hides them not reveals them
 */
#include <standards.h>
#undef _XOPEN_SOURCE_EXTENDED

#ifdef __cplusplus
extern "C" {
#endif

/*
wait4      is in /usr/include/wait.h behind defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)
setegid           is in /usr/include/unistd.h behind ifdef _OSF_SOURCE
seteuid    ditto: is in /usr/include/unistd.h behind ifdef _OSF_SOURCE
setegid    ditto: is in /usr/include/unistd.h behind ifdef _OSF_SOURCE
initgroups is in /usr/include/grp.h unconditionally
NSIG       is in /usr/include/signal.h        behind ifndef _XOPEN_SOURCE_EXTENDED, yes ifndef
copysign   similar: is in /usr/include/math.h behind ifndef _XOPEN_SOURCE_EXTENDED, yes ifndef
*/

/* round is tricky, define _EXTERNAL_INTRINSICS on compiler command line
 * should get its prototype, at least with cc, not gcc
 * see /usr/lib/cmplrs/cc.dtk/EIDF.h.
 */
#ifdef __GNUC__
/* These are in /usr/include.dtk/math.h,
 * not necessarily usable with gcc.
 */
double round(double);
int finite(double);

#ifdef __SIZE_MAX__
#define SIZE_MAX __SIZE_MAX__
#endif

/* Not all of these are needed by every program.
 * These are in /usr/include.dtk/inttypes.h,
 * not necessarily usable with gcc.
 */
#define PRId8		"d"
#define PRId16		"d"
#define PRId32		"d"
#define PRId64		"ld"
#define PRIdLEAST8	"d"
#define PRIdLEAST16	"d"
#define PRIdLEAST32	"d"
#define PRIdLEAST64	"ld"
#define PRIdFAST8	"d"
#define PRIdFAST16	"d"
#define PRIdFAST32	"d"
#define PRIdFAST64	"ld"
#define PRIdMAX		"ld"
#define PRIdPTR		"ld"
#define PRIi8		"i"
#define PRIi16		"i"
#define PRIi32		"i"
#define PRIi64		"li"
#define PRIiLEAST8	"i"
#define PRIiLEAST16	"i"
#define PRIiLEAST32	"i"
#define PRIiLEAST64	"li"
#define PRIiFAST8	"i"
#define PRIiFAST16	"i"
#define PRIiFAST32	"i"
#define PRIiFAST64	"li"
#define PRIiMAX		"li"
#define PRIiPTR		"li"
#define PRIo8		"o"
#define PRIo16		"o"
#define PRIo32		"o"
#define PRIo64		"lo"
#define PRIoLEAST8	"o"
#define PRIoLEAST16	"o"
#define PRIoLEAST32	"o"
#define PRIoLEAST64	"lo"
#define PRIoFAST8	"o"
#define PRIoFAST16	"o"
#define PRIoFAST32	"o"
#define PRIoFAST64	"lo"
#define PRIoMAX		"o"
#define PRIoPTR		"lo"
#define PRIu8		"u"
#define PRIu16		"u"
#define PRIu32		"u"
#define PRIu64		"lu"
#define PRIuLEAST8	"u"
#define PRIuLEAST16	"u"
#define PRIuLEAST32	"u"
#define PRIuLEAST64	"lu"
#define PRIuFAST8	"u"
#define PRIuFAST16	"u"
#define PRIuFAST32	"u"
#define PRIuFAST64	"lu"
#define PRIuMAX		"lu"
#define PRIuPTR		"lu"
#define PRIx8		"x"
#define PRIx16		"x"
#define PRIx32		"x"
#define PRIx64		"lx"
#define PRIxLEAST8	"x"
#define PRIxLEAST16	"x"
#define PRIxLEAST32	"x"
#define PRIxLEAST64	"lx"
#define PRIxFAST8	"x"
#define PRIxFAST16	"x"
#define PRIxFAST32	"x"
#define PRIxFAST64	"lx"
#define PRIxMAX		"lx"
#define PRIxPTR		"lx"
#define PRIX8		"X"
#define PRIX16		"X"
#define PRIX32		"X"
#define PRIX64		"X"
#define PRIXLEAST8	"X"
#define PRIXLEAST16	"X"
#define PRIXLEAST32	"X"
#define PRIXLEAST64	"lX"
#define PRIXFAST8	"X"
#define PRIXFAST16	"X"
#define PRIXFAST32	"X"
#define PRIXFAST64	"lX"
#define PRIXMAX		"lX"
#define PRIXPTR		"lX"

#else
/* native cc works sometimes better */
#endif

/* Tru64/OSF1 has no known monotonic time source; fake it poorly for py_get_monotonic_clock */
#define CLOCK_MONOTONIC CLOCK_REALTIME

/* setenv and unsetenv are in ifdef _BSD in /usr/include/stdlib.h
 * Do not at this time try define _BSD
 */
int setenv(const char*, const char*, int);
void unsetenv(const char*);

/* This version may not work in an .so. Another version is in newer gnulib.
* Place this in getprogname.c as needed. It occurs in many programs.
extern char** __Argv;

char const* last_component (const char*);

char const* getprogname (void)
{
    return last_component (__Argv [0]);
}
*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
