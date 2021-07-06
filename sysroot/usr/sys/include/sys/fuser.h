/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: fuser.h,v $
 * Revision 1.1.43.1  2004/10/29  16:19:32  Douglas_Frank
 * 	Added bits & structs enabling clusterization.
 *
 * Revision 1.1.40.1  2000/10/24  23:54:23  Ernie_Petrides
 * 	Merge v51supportos-12-ljprokow from Zulu PK2 revision 1.1.38.1.
 *
 * Revision 1.1.38.1  2000/09/13  13:22:21  Lee_Prokowich
 * 	Add option (-p) to ignore parent directories. When fuser -k is
 * 	issued on a directory which has dismounted and a process was running
 * 	from it, fuser will hang in namei since the NFS server went down.
 * 	This is a v5.1ipk forward port of srequest v50asupportos-8-ljprokow
 * 	for v5.1 pk2.
 * 
 * Revision 1.1.10.5  1999/02/09  19:03:48  Ken_Block
 * 	Make header C++ compliant.
 * 	[1998/12/29  20:22:02  Ken_Block]
 * 
 * Revision 1.1.10.4  1998/11/24  16:20:48  Larry_Scott
 * 	Add F_NOLINK flag.
 * 	[1998/11/21  19:28:52  Larry_Scott]
 * 
 * Revision 1.1.10.3  1997/10/09  21:57:14  Stuart_Hollander
 * 	Fix fuser prototype.  2 ints become longs.
 * 	[1997/06/11  18:18:18  Stuart_Hollander]
 * 
 * Revision 1.1.10.2  1997/03/18  23:30:15  Larry_Scott
 * 	Add F_MMAP type to support detecting mmap'ed files
 * 	[1997/03/17  15:38:12  Larry_Scott]
 * 
 * Revision 1.1.5.2  1994/10/13  20:07:25  Jeff_Denham
 * 	Add F_TEXT type to support detecting files "open" for execution.
 * 	[1994/10/07  21:40:57  Jeff_Denham]
 * 
 * Revision 1.1.3.2  1993/05/27  21:37:12  Peter_Lega
 * 	E-type merging
 * 	[1993/05/27  20:53:51  Peter_Lega]
 * 	Etype merge
 * 	[1993/05/26  22:33:47  Peter_Lega]
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: fuser.h,v $ $Revision: 1.1.43.1 $ (DEC) $Date: 2004/10/29 16:19:32 $
 */
#ifndef	_SYS_FUSER_H
#define _SYS_FUSER_H

#include <sys/user.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * fuser() flags
 */
#define F_FILE_ONLY	0x1
#define F_CONTAINED	0x2
#define F_NOLINK	0x4
#define F_IGNPARENT	0x8
#define F_CLUSTER	0x10  /* for HP Use Only */
#define F_VERBOSE	0x20  /* for HP Use Only */
#define F_ESTIMATE	0x40  /* for HP Use Only */

/*
 * Data structure filled in by fuser().
 */
typedef struct f_user {
	pid_t	fu_pid;
	int	fu_flags;
	uid_t	fu_uid;	
} f_user_t;

/*
 * 'Verbose' struct for HP Use Only
 */
typedef struct f_user_verbose {
	pid_t	fu_pid;
	int	fu_flags;
	uid_t	fu_uid;	
	char	fu_comm[MAXCOMLEN+1];
} f_user_verbose_t;


/*
 * fu_flags values
 */
#define F_CDIR		0x0001
#define F_RDIR		0x0002
#define F_PDIR		0x0004
#define F_OPEN		0x0008
#define F_TTY		0x0010
#define F_TRACE		0x0020
#define F_TEXT		0x0040
#define F_MMAP		0x0080

#if	!defined(_KERNEL)

#if	defined(__STDC__) || defined(__cplusplus)
extern int	fuser(const char *, long, struct f_user *, long);
#else	/* !__STDC__ */
extern int	fuser();
#endif	/* !__STDC__ */

#endif	/* !_KERNEL */

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif	/* !_SYS_FUSER_H */
