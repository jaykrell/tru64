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
**++
**  PRODUCT:
***
**	DEC C++ Demangler
**
**  FILE:  
**
**      demangle_string.h
**
**  ABSTRACT:
**
**	Definitions necessary for demangling a string.
**
**  ENVIRONMENT:
**
**	User Mode
**
**  AUTHORS:
**
**
**  MODIFICATION HISTORY:
**
**
**--
**/


#ifndef _DEMANGLE_STRING_H_
#define _DEMANGLE_STRING_H_

/*
**
**  DEMANGLER FLAGS
**
**  The following flags can be passed to the "MLD_demangle_string" 
**  function as the 4th argument "flags".  To combine several flags, 
**  logically OR them together.
**  NOTE:  combining MLD_SHOW_MANGLED_NAME and MLD_SHOW_DEMANGLED_NAME 
**	   will put the mangled name in parens.
** 
*/

#define MLD_SHOW_MANGLED_NAME	0x01	/* mangled name */
#define MLD_SHOW_INFO		0x02	/* e.g. type signatures */
#define MLD_NO_SPACES		0x04	/* no space in output */
#define MLD_SHOW_DEMANGLED_NAME	0x08	/* demangled name */

#define MLD_DUMP		0x10	/* reserved for development */
#define MLD_MEMCHECK		0x20	/* reserved for development */
#define MLD_NO_TEMPLATE_DETAILS	0x40	/* skip template argument details */

/*
**  The routine MLD_demangle_string is in the libmld.a (or libdemangle.a)
*/

/*
**
**  DEMANGLE STRING
**
**  The "MLD_demangle_string" function, demangles mangled names into user
**  friendly names, and return an int of status.
**
**  There are 4 arguments.
**	char* s:	string (characters terminated with a null character)
**			to be demangled, may contain multiple mangled names
**			separated with a "space".
**	char* ds:	tell the MLD_demangle_string where the result string 
**			of demangled names should be stored at.
**	int   ds_max:	tell the MLD_demangle_string about the maximum 
**			available size of ds is.
**	int   flags:	tell MLD_demangle_string what to do.  Details 
**			see above.
**
**  If there are several mangled names, all of the mangled names are replaced
**  with demangled names.  If there are no mangled names or an error occurs,
**  "ds" will be equal to "s".  If ds is not large enough to hold the demangled
**  name, an error will result (and consequently, as just mentioned, "ds" will
**  equal "s").
**
**  NOTE:  This function will return an int, represents the status of 
**	demangling, whose value is one of the following:
**
**	MLD_SOMETHING_RECOGNIZED
**	MLD_NOTHING_RECOGNIZED
**	MLD_ERROR
**	MLD_INADEQUATE_ARRAY_SIZE
*/

/*
**
**  DEMANGLER STATUS
**
*/
#define MLD_SOMETHING_RECOGNIZED 	 1
#define MLD_NOTHING_RECOGNIZED 		 0
#define MLD_ERROR			-1
#define MLD_INADEQUATE_ARRAY_SIZE 	-2

#ifdef __cplusplus
extern "C" {
#endif
int /* status */ 
MLD_demangle_string (const char*,	/* IN:  string to be demangled */
                    char*,		/* OUT: demangled string */
                    int,		/* IN:	maximum size of ds */
                    int);	/* IN:	flags to control string formation */
#ifdef __cplusplus
}
#endif

#endif /* _DEMANGLE_STRING_H_ */
/* DON'T ADD ANYTHING AFTER THIS #endif */
