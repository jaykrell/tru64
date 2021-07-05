/* OSF/1 is missing a few things.
 * uname -srm: OSF1 V5.1 alpha
 *
 * C99 support is incomplete.
 * There is long long, but long is also 64bits so long long is not really neded.
 * Prototypes are behind ifdef *and* sometimes ifndef.
 * It is not obvious if one set of defines
 * will reveal enough, since some defines
 * actually hide prototypes, but let's try.
 *
 * This one file has all the workarounds and
 * is included whenever any of them are needed.
 *
 * Better fixes would involve autoconf
 * and include, however hardcoding here
 * is less disruptive and the system is unlikely
 * to change, and older versions are not very interesting.?
 *
 * And again, some prototypes are actually behind ifndef.
 *
 * Most of these workarounds are for Python3 but some apply to other programs.
 *
 * gcc also defines _LP64 but cc does not.
 */
#if defined(__osf__) && defined(__alpha__) && defined(__arch64__)

#undef _ISO_C_SOURCE
#define _ISO_C_SOURCE 19990
#define _OSF_SOURCE
#undef _XOPEN_SOURCE_EXTENDED
#include <grp.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>
#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
wait4 is in /usr/include/wait.h behind defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)
setegid is in /usr/include/unistd.h behind ifdef _OSF_SOURCE
seteuid ditto
setegid ditto
initgroups is in /usr/include/grp.h unconditionally
NSIG is behind ifndef _XOPEN_SOURCE_EXTENDED in /usr/include/signal.h
copysign prototype is in math.h, disabled by _XOPEN_SOURCE_EXTENDED, yes, disabled
*
* If this does not work out, then try declaring things ourselves:
*union wait;
*struct rusage;
*pid_t wait4 (pid_t, union wait*, int, struct rusage*);
*int seteuid (uid_t);
*int setegid (gid_t);
*int initgroups (char *, gid_t);
*
*#ifndef NSIG
*#define NSIG (SIGMAX+1)
*#endif
*/

/* round is tricky, define _EXTERNAL_INTRINSICS on compiler command line
 * should get its prototype, at least with cc, not gcc
 * see /usr/lib/cmplrs/cc.dtk/EIDF.h.
 */
double round(double);

#define SIZE_MAX 18446744073709551615UL
#define INTMAX_MAX 9223372036854775807L
#define UINTMAX_MAX 18446744073709551615UL
typedef long intmax_t;
typedef unsigned long uintmax_t;

/* C99 printf macros are missing. */
#define PRId64 "ld"
#define PRIi64 "li"
#define PRIo64 "lo"
#define PRIu64 "lu"
#define PRIx64 "lx"
#define PRIdMAX "ld"
#define PRIiMAX "li"
#define PRIoMAX "lo"
#define PRIuMAX "lu"
#define PRIxMAX "lx"

/* C99 integer constant macros are missing */
#define UINT16_C(c) c
#define UINT32_C(c) c ## U
#define UINT64_C(c) c ## UL

/* This version may not work in an .so. Another version is in newer gnulib.
* Place this in getprogname.c as needed. It occurs in many programs.
extern char* __Argv;

char const* last_component (const char*)

char const* getprogname (void)
{
    return last_component (__Argv [0]);
}
*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
