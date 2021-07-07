/* OSF/1 is missing a few things.
 * uname -srm: OSF1 V5.1 alpha
 *
 * This is mainly for Python3, so far.
 */
#if defined(__osf__) && defined(__arch64__)

/* various standard facilities require specific request to reveal */
#define __STDC_CONSTANT_MACROS 1
#define __STDC_LIMIT_MACROS 1
#define __STDC_FORMAT_MACROS 1

#undef _ISO_C_SOURCE
#define _ISO_C_SOURCE 199901
#define _OSF_SOURCE 1
#define _ANSI_C_SOURCE 1
#define _XOPEN_SOURCE 700       /* The highest value in OSF1 is 500 but match Python3 */
#define _POSIX_C_SOURCE 200809L /* The highest value in OSF1 is 199506L but match Python3 */
#undef _XOPEN_SOURCE_EXTENDED   /* defining this, hides symbols such as NSIG, copysign */

#include <sys/types.h>
#include <grp.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>
#include <limits.h>

#include "/usr/include.dtk/stdint.h" /* for gcc */
#include "/usr/include.dtk/inttypes.h" /* for gcc */

#ifdef __SIZE_MAX__
#define SIZE_MAX __SIZE_MAX__
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
wait4      is in /usr/include/wait.h behind defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)
setegid    is in /usr/include/unistd.h behind ifdef _OSF_SOURCE
seteuid    ditto
setegid    ditto
initgroups is in /usr/include/grp.h unconditionally
NSIG       is behind ifndef _XOPEN_SOURCE_EXTENDED in /usr/include/signal.h, yes, ifndef
copysign   is in math.h, disabled by _XOPEN_SOURCE_EXTENDED, yes, disabled
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
