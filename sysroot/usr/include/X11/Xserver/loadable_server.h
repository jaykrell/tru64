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
/****************************************************************************
**                                                                          *
**                 COPYRIGHT (c) 1992 BY            			    *
**              DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS.               *
**			     ALL RIGHTS RESERVED                            *
**                                                                          *
**  THIS SOFTWARE IS FURNISHED UNDER A LICENSE AND MAY BE USED AND  COPIED  *
**  ONLY  IN  ACCORDANCE  WITH  THE  TERMS  OF  SUCH  LICENSE AND WITH THE  *
**  INCLUSION OF THE ABOVE COPYRIGHT NOTICE.  THIS SOFTWARE OR  ANY  OTHER  *
**  COPIES  THEREOF MAY NOT BE PROVIDED OR OTHERWISE MADE AVAILABLE TO ANY  *
**  OTHER PERSON.  NO TITLE TO AND OWNERSHIP OF  THE  SOFTWARE  IS  HEREBY  *
**  TRANSFERRED.                                                            *
**                                                                          *
**  THE INFORMATION IN THIS SOFTWARE IS SUBJECT TO CHANGE  WITHOUT  NOTICE  *
**  AND  SHOULD  NOT  BE  CONSTRUED  AS  A COMMITMENT BY DIGITAL EQUIPMENT  *
**  CORPORATION.                                                            *
**                                                                          *
**  DIGITAL ASSUMES NO RESPONSIBILITY FOR THE USE OR  RELIABILITY  OF  ITS  *
**  SOFTWARE ON EQUIPMENT WHICH IS NOT SUPPLIED BY DIGITAL.                 *
**                                                                          *
****************************************************************************/

/****************************************************************************
 ****
 **** Author: Jim Ludwig
 **** Creation: Aug 1992
 **** Description: loadable.h
 ****	typedefs and externs for loadable server
 ****
 ****************************************************************************/

#ifndef LOADABLE_SERVER_H
#define LOADABLE_SERVER_H

#include <X11/Xserver/loadable.h>
#include "argparse.h"

extern int 	LS_NumDeviceLibraries;
extern int 	LS_NumExtensionsLibraries;
extern int 	LS_NumFontRenderersLibraries;
extern int 	LS_NumInputLibraries;
extern int 	LS_NumAuthProtoLibraries;
extern int 	LS_NumTransportsLibraries;
#ifndef NO_DEC_VALUE_ADDED
extern int	LS_NumDefaultExtLibraries;
#endif


/* Load libraries */
extern int LS_LoadLibraryReqs(
#if NeedFunctionPrototypes
    LS_LibraryReq * 	    	/* pointer to list of libraries     */,
    int		 		/* index into list		    */,
    int	    			/* number of libraries to load	    */,
    Boolean	    	    	/* enforce version checking 	    */
#endif
);

/* unload libraries */
extern void LS_UnLoadLibraryReqs(
#if NeedFunctionPrototypes
    LS_LibraryReq * 	    	/* pointer to list of libraries     */,
    int	    	 		/* index into list		    */,
    int	    			/* number of libraries to load	    */
#endif
);

/* mark libraries for unloading, but defer unloading until 
 * LS_FreeMarkedLibraries is called.
 */
extern void LS_MarkForUnloadLibraryReqs(
#if NeedFunctionPrototypes
    LS_LibraryReq * 		/* pointer to list of libraries 	*/,
    int	    	 		/* index into list			*/,
    int	    			/* number of libraries to load		*/
#endif
);

/* Unload all marked libraries */
extern void LS_FreeMarkedLibraries();

/* for opaque data handling, get the name of the library */
extern char * LS_GetLibName(
#if NeedFunctionPrototypes
    LS_LibraryReq * 		/* pointer to list of libraries 	*/,
    int	    	 		/* index into list			*/
#endif
);

/* for opaque data handling, get the name of the library file */
extern char * LS_GetLibFileName(
#if NeedFunctionPrototypes
    LS_LibraryReq * 		/* pointer to list of libraries 	*/,
    int	    	 		/* index into list			*/
#endif
);

/* for opaque data handling, get the name of the initialization procedure */
extern char * LS_GetInitProcName(
#if NeedFunctionPrototypes
    LS_LibraryReq * 		/* pointer to list of libraries 	*/,
    int	    	 		/* index into list			*/
#endif
);

/* for opaque data handling, get the address of the initialization procedure */
extern LS_InitProcPtr LS_GetInitProc(
#if NeedFunctionPrototypes
    LS_LibraryReq * 		/* pointer to list of libraries 	*/,
    int	    	 		/* index into list			*/
#endif
);

/* for opaque data handling, get the name of the device */
extern char * LS_GetDeviceName(
#if NeedFunctionPrototypes
    LS_LibraryReq * 		/* pointer to list of libraries 	*/,
    int	        		/* index into list			*/
#endif
);

/* for opaque data handling, get the sub library list for an extension */
extern Boolean LS_GetSubLibList(
#if NeedFunctionPrototypes
    LS_LibraryReq * 		/* pointer to list of libraries		*/,
    int	    			/* index into list			*/,
    LS_LibraryReq ** 	    	/* return pointer to sub list	    	*/,
    int		*   	    	/* number in sub list			*/
#endif
);

/* lookup a library by library name */
extern int LS_GetLibraryReqByLibName(
#if NeedFunctionPrototypes
    LS_LibraryReq * 	    	/* pointer to list of libraries		*/,
    int	    	    	    	/* number of entries in list		*/,
    char *  	    	    	/* lib name to search for 		*/
#endif
);

/* lookup a library by device name */
extern int LS_GetLibraryReqByDeviceName(
#if NeedFunctionPrototypes
    LS_LibraryReq * 	    	/* pointer to list of libraries		*/,
    int	    			/* number of entries in list		*/,
    char *  	 		/* lib name to search for 		*/
#endif
);

/* get a symbol by name 
 * This will return the first symbol found with matching name.
 * If the global name space has more than one symbol with the same name
 * the results are undefined 
 */
extern void * LS_GetSymbol(
#if NeedFunctionPrototypes
    char *   	        	/* symbol name to look up		*/
#endif
);

/* get a symbol by name from a particular library. There should be 
 * no name conflicts within a single library.
 */
extern void * LS_GetSymbolInLibrary(
#if NeedFunctionPrototypes
    char *  	    		/* symbol name to look up		*/,
    LS_LibraryReq * 	    	/* pointer to list of libraries		*/,
    int	    			/* index into list			*/
#endif
);

/* Mark a library as being initialized */
extern void LS_MarkLibraryInited(
#if NeedFunctionPrototypes
    LS_LibraryReq * 		/* pointer to list of libraries 	*/,
    int	    	 		/* index into list			*/
#endif
);

/* True if library has been marked initialized */
extern Boolean LS_IsLibraryInited(
#if NeedFunctionPrototypes
    LS_LibraryReq * 		/* pointer to list of libraries 	*/,
    int	    	    	    	/* index into list			*/
#endif
);

/* Force all symbols from all libraries currently loaded to be resolved.
 * This should be called after each independent set of libraries is 
 * loaded to guarentee that there are no unresolved symbols. If there
 * are, the server should exit. Otherwise, the results are undefined
 * and the server will typically seg fault.
 */
extern int LS_ForceSymbolResolution();

/* abort codes to be agreed up with xdm */
#define LS_ABORT_RESOLUTION	2

#endif /* LOADABLE_SERVER_H */
