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
 * @(#)$RCSfile: advfs_syscalls.h,v $ $Revision: 1.1.2.3 $ (DEC) $Date: 1998/11/23 23:46:33 $
 */

#include <sys/param.h>
#include <sys/time.h>

#ifndef _ADVFS_SYSCALLS_H
#define _ADVFS_SYSCALLS_H

typedef enum {
  ADVFS_WO_ASYNC_WRITE,		/* synchronous writes not guaranteed */
  ADVFS_WO_RESERVED,		/* reserved */
  ADVFS_WO_DATA_LOGGING,	/* Atomic write data logging */
  ADVFS_WO_SYNC_WRITE		/* synchronous writes guaranteed */
} fileWriteOrderT;

typedef enum {
  XMT_NIL,		/* no extents (allocation) yet */
  XMT_SIMPLE,		/* no special mapping formula */
  XMT_RESERVED,		/* reserved */
  XMT_STRIPE		/* consecutive runs on alternate disks */
} fileXtntMapTypeT;

typedef struct stripeParams {
  int segmentCnt;	/* number of volumes to stripe across */
  int reserved;		/* reserved */
} stripeParamsT;

typedef struct {
  unsigned int num;		/* tag number, 1 based */
  unsigned int seq;		/* sequence number */
} fileTagT;

typedef struct fileAttributes {
  int reserved1;			/* reserved */
  fileWriteOrderT writeOrder;		/* file write synchronicity */
  int reserved2;			/* reserved */
  int reserved3;			/* reserved */
  int reserved4;			/* reserved */
  int reserved5;			/* reserved */
  fileXtntMapTypeT mapType;		/* storage mapping type */
  stripeParamsT stripe;			/* stripe specific parameters */
  int reserved6;			/* reserved */
  int reserved7;			/* reserved */
  int reserved8;			/* reserved */
  int reserved9;			/* reserved */
  int reserved10;			/* reserved */
  int reserved11;			/* reserved */
  int reserved12;			/* reserved */
  int reserved13;			/* reserved */
  int reserved14;			/* reserved */
  int reserved15;			/* reserved */
  int reserved16;			/* reserved */
  int reserved17;			/* reserved */
  int fill1;
  int fill2;
} fileAttributesT;

typedef struct timeval domainIdT;	    /* unique identifier, 64 bits */

typedef struct filesetId {
  domainIdT   domainId;		/* fileset's domain's ID */
  fileTagT    setTag;		/* tag of fileset's tag directory */
} filesetIdT;

#define DOMAIN_NAME_SZ		32
#define FILESET_NAME_SZ		32

typedef struct {
  domainIdT	dmnId;				/* Id for this domain */
  char		dmnName[DOMAIN_NAME_SZ];	/* domain's name */
  int		reserved1;			/* reserved for future use*/
  int		reserved2;			/* reserved for future use*/
  int		reserved3;			/* reserved for future use*/
  int		reserved4;			/* reserved for future use*/
  int		reserved5;			/* reserved for future use*/
  int		reserved6;			/* reserved for future use*/
  int		reserved7;			/* reserved for future use*/
  int		reserved8;			/* reserved for future use*/
} domainInfoT;

typedef struct {
  filesetIdT	filesetId;	/* Id for this fileset */
  unsigned int	cloneId;	/* 0 ==> original; "> 0" ==> clone */
  unsigned int	hasClone;	/* 0 ==> not cloned; "> 0" ==> has clone */
  int		isMounted;	/* 0 ==> not mounted; "> 0" ==> is mounted */
  char		setName[FILESET_NAME_SZ];	/* this fileset's name */
  union {
    char	cloneName[FILESET_NAME_SZ];	/* clone's name */
    char	origName[FILESET_NAME_SZ];	/* original's name, if clone */
  } relatedSet;
  char		mountPath[MAXPATHLEN];		/* mountpoint pathname */
  int		reserved1;			/* reserved for future use*/
  int		reserved2;			/* reserved for future use*/
  int		reserved3;			/* reserved for future use*/
  int		reserved4;			/* reserved for future use*/
  int		reserved5;			/* reserved for future use*/
  int		reserved6;			/* reserved for future use*/
  int		reserved7;			/* reserved for future use*/
  int		reserved8;			/* reserved for future use*/
} filesetInfoT;

typedef struct {
  unsigned long	blkHLimit;	/* maximum quota blocks in fileset */
  unsigned long	blkSLimit;	/* soft limit for fileset blks */
  unsigned long	fileHLimit;	/* maximum number of files in fileset */
  unsigned long	fileSLimit;	/* soft limit for fileset files */
  int		reserved1;			/* reserved for future use*/
  int		reserved2;			/* reserved for future use*/
  int		reserved3;			/* reserved for future use*/
  int		reserved4;			/* reserved for future use*/
  int		reserved5;			/* reserved for future use*/
  int		reserved6;			/* reserved for future use*/
  int		reserved7;			/* reserved for future use*/
  int		reserved8;			/* reserved for future use*/
} filesetQuotasT;


#ifdef __cplusplus
extern "C" {
#endif

int
advfs_clonefset(
	char	*domainName,
	char	*filesetName,
	char	*cloneName
);

int
advfs_rmfset(
	char	*domainName,
	char	*filesetName
);

int
advfs_get_fdmn_list(
	unsigned long	arraySize,
	unsigned long	*offset,
	unsigned long	*numDomains,
	domainInfoT	domainInfo[]
);

int
advfs_get_fset_list(
	char		*domain,
	unsigned long	arraySize,
	unsigned long	*offset,
	unsigned long	*numFilesets,
	filesetInfoT	filesetInfo[]
);

int 
advfs_get_fset_quotas (
	char		*domainName,
	char		*filesetName,
	filesetQuotasT	*filesetQuotas
);

int 
advfs_set_fset_quotas (
	char		*domainName,
	char		*filesetName,
	filesetQuotasT	*filesetQuotas
);

int
advfs_get_file_attributes (
	int		 fd,
	fileAttributesT* fileAttributes
); 

int 
advfs_set_file_attributes (
	int		 fd,
	fileAttributesT* fileAttributes
); 

#ifdef __cplusplus
}
#endif

#endif /* _ADVFS_SYSCALLS_H */

/* end advfs_syscalls.h */
