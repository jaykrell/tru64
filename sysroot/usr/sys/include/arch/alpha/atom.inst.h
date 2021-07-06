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
 * @(#)$RCSfile: atom.inst.h,v $ $Revision: 1.1.8.2 $ (DEC) $Date: 2002/01/08 20:02:23 $
 */
/*
**  alpha/atom.inst.h -  External interface definition for low-level Atom 
**                       instrumentation
**
**	This file defines the Atom Toolkit's external interfaces that support 
**      insertion of specific additional instructions into an application 
**	program.  Use of these interfaces requires considerable understanding 
**	of the Compaq Alpha architecture and Tru64 UNIX object file structure.
**	These interfaces are intended only for analysis code that cannot
**	afford the overhead of calling regular analysis routines.  For 
**	all other kinds of analysis, Atom's high-level instrumentation
**      interfaces provided by <cmplrs/atom.inst.h> are strongly recommended.
*/

#ifndef _ALPHA_ATOM_INST_H_
#define _ALPHA_ATOM_INST_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <cmplrs/atom.inst.h>
#include <alpha/inst.h>

/*
****************************************************************************
**                                                                        **
**         Definitions of types used by instrumentation routines          **
**                                                                        **
****************************************************************************
*/


/*
 * Opaque program structure types visible only as pointers.
 */
typedef struct crosscall        Xcall;         /* A cross-call structure */

/*
 * Possible return values from GetPhase().
 */
typedef enum Phase {
    NONE,
    CALCMAXLEN,
    LAYOUT,
    WRITEOUT
} PhaseType;


/*
****************************************************************************
**                                                                        **
**                Prototypes for instrumentation routines                 **
**                                                                        **
****************************************************************************
*/

/*
 * Routines to add instrumentation code.
 */
extern void 		AddInlineProto(const char *);
extern void 		AddInsertProto(void *, const char *);
extern void 		AddInlineInst(Inst *, PlaceType, void *, ...);
extern Xcall * 		CreateXcall(Inst *, const char *, ...);


/*
 * Routine to get Atom's processing information.  This routine must
 * be called in the insertion routine.
 */
extern PhaseType 	GetPhase(void);


/*
 * Routine to get Atom's processing information.  This routine can only
 * be called in the CALCMAXLEN phase of the insertion routine.
 */
extern int 		GetMaxCallLength(Xcall *);


/*
 * Routine to get Atom's processing information.  This routine can only
 * be called in the LAYOUT or WRITEOUT phase of the insertion routine.
 */
extern int 		GetCallLength(Xcall *, int idx);


/*
 * Routine to get Atom's processing information.  These routines can only
 * be called in the WRITEOUT phase of the insertion routine.
 */
extern unsigned * 	GetIbuf(void);
extern unsigned		AddMemInst(unsigned, RegvType, RegvType, signed);
extern unsigned		AddFuncInst(unsigned, unsigned, RegvType, RegvType);
extern unsigned		AddBrInst(unsigned, RegvType, signed); 
extern unsigned		AddOpInst(unsigned, unsigned, RegvType, 
				RegvType, RegvType);
extern unsigned		AddLitInst(unsigned, unsigned, RegvType, 
				unsigned, RegvType);
extern unsigned		AddFPInst(unsigned, unsigned, RegvType, 
				RegvType, RegvType);
extern unsigned		AddPALInst(unsigned, unsigned);
extern unsigned		AddJsrInst(unsigned, unsigned, RegvType, 
				RegvType, signed);
extern int 		AddAnalysisCall(Xcall *, unsigned *);

/*
 * The following routine names are retained only for compatibility.
 * Using AddPALInst and AddAnalysisCall instead is recommended.
 */
extern unsigned		AddPALFormat(unsigned, unsigned);
extern int 		AddAnalCall(Xcall *, RegvType, unsigned *);

/*
 * Routine to get the offset from an instruction to the GP value
 * for the containing procedure.  This routine can only be called
 * during the WRITEOUT phase.
 */
extern long		GetGPOffset(int);

/*
 * Routine to return the number of bytes between the two given instructions.
 * These instructions must exist in the original application.  They _cannot_ 
 * be inserted instructions.  This routine can only be called in during the
 * WRITEOUT phase.
 */
extern long             GetOffset(Inst *, Inst *);

/*
 * Routine to increase the size of the bss segment.  This routine can only
 * be called before the WRITEOUT phase.
 */
extern long		ExtendBSS(Obj *, int);

/*
 * Routine to replace an object's output file name.  This routine cannot be 
 * called after the instrumented executable has been written.
 */
extern void		ReplaceObjOutputName(Obj *, const char *);

/*
 * Replace the name of an object in an object's liblist.  This routine
 * cannot be called after the instrumented executable has been written.
 */
extern void		UpdateObjLiblist(Obj *, const char *, const char *);

/*
 * Routine to get the first procedure called by an object's .init
 * section.
 */
extern Proc *		GetFirstInitProc(Obj *);

/*
 * Routine to get the last procedure called by an object's .fini
 * section.
 */
extern Proc *		GetLastFiniProc(Obj *);

#ifdef __cplusplus
}
#endif
#endif /* _ATOM_INST_ALPHA_H_ */
