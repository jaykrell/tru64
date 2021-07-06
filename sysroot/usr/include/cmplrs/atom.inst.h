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
 * 
 * 
 */
/*
 * @(#)$RCSfile: atom.inst.h,v $ $Revision: 1.1.23.1 $ (DEC) $Date: 2001/09/12 21:08:28 $
 */

/*
**  atom.inst.h - 	External interface definition for Atom instrumentation
**
**	This file defines the external interfaces for Atom.  These
**	interfaces are used by an Atom tool's instrumentation code.  See
**	<cmplrs/atom.anal.h> for definitions of the analysis-time interfaces.
**	Atom is a general purpose framework for creating sophisticated
**	program analysis tools.
*/

#ifndef _ATOM_INST_H_
#define _ATOM_INST_H_


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
typedef struct object     	Obj;  	/* An executable or a shared library */
typedef struct procedure  	Proc; 	/* A procedure */
typedef struct entry      	Entry; 	/* An entry */		
typedef struct basicblock 	Block;	/* A basic block */
typedef struct instruction	Inst; 	/* An instruction */
typedef struct translate  	Xlate;	/* An address translation structure */


/*
 * Program Information.
 */
typedef enum ProgInfo {
    ProgNumberObjects,         	/* Number of objects in this program */
    				/*	instrumented. */
    ProgNumInstObjects,		/* Number of objects the user requested to */
    				/*	have instrumented. */
    ProgNumErrantShlibs		/* Number of shared libraries that were not */
				/* 	able to be processed */
} ProgInfoType;


/*
 * Object Information.
 */
typedef enum ObjInfo {
    ObjTextStartAddress,      	/* Starting address of text segment */
    ObjTextSize,              	/* Byte size of text segment */
    ObjInitDataStartAddress,  	/* Starting address of data segment */
    ObjInitDataSize,          	/* Byte size of data segment */
    ObjUninitDataStartAddress,	/* Starting address of bss segment */
    ObjUninitDataSize,        	/* Byte size of bss segment */
    ObjNumberBlocks,          	/* Number of basic blocks in object */
    ObjNumberProcs,           	/* Number of procedures in object */
    ObjNumberInsts,           	/* Number of instructions in object */
    ObjID,                    	/* Unique identifier for object */
    ObjModifyHint,             	/* User's preference for instrumenting object */
    ObjSymResolution,		/* Symbol resolution for shared library */
    ObjShared,			/* Shared, sharable or non_shared object */
    ObjNumberEntries          	/* Number of entries in object */ 
} ObjInfoType;


/*
 * Procedure information.
 */
typedef enum ProcInfo {
    ProcFrameSize,            	/* Size of stack frame (fixed portion only) */
    ProcIRegMask,             	/* Saved integer register mask */
    ProcIRegOffset,           	/* Offset of ireg save area (if stack frame) */
                              	/* Saved return reg number (if reg frame) */
    ProcFRegMask,             	/* Saved floating pointer register mask */
    ProcFRegOffset,           	/* Offset of freg save area (if stack frame) */
    ProcgpPrologue,           	/* Byte size of GP prologue */
    ProcgpUsed,               	/* True if procedure uses $gp */
    ProcLocalOffset,          	/* Offset of local variables from vfp */
    ProcFrameReg,             	/* Frame pointer register number */
    ProcPcReg,                	/* Register number with return address */
    ProcNumberBlocks,         	/* Number of basic blocks in procedure */
    ProcNumberInsts,          	/* Number of instructions in procedure */
    ProcID,                   	/* Unique identifier for procedure */
    ProcLineLow,              	/* Lowest source line for procedure */
    ProcLineHigh,             	/* Highest source line for procedure */
    ProcAddrTaken,            	/* True if procedure's address taken */
    ProcIsRegFrame,            	/* True if procedure has a register frame */
    ProcSymRes,			/* Symbol resolution */
    ProcIpBrJmp,		/* True if procedure has interprocedural BRs/JMPs. */
    ProcExceptionFrame,		/* True if proc contains an exception frame */
    ProcHasAltEntries,		/* True if proc has alternate entry points */
    ProcNumberEntries,         	/* Number of entries in procedure */ 
    ProcSpSetOffset,		/* Offset from proc start to sp set inst */
    ProcEntryLengthOffset	/* Offset from proc start to inst after prologue */

} ProcInfoType;


/*
 * Entry information.
 */
typedef enum EntryInfo {
    EntryIsRedundant		/* True if entry point is redundant */
} EntryInfoType;


/*
 * Basic block information.
 */
typedef enum BlockInfo {
    BlockNumberInsts,         	/* Number of instructions in basic block */
    BlockID                   	/* Unique identifier for basic block */
} BlockInfoType;


/*
 * Instruction information.
 */
typedef enum IInfo {
    InstMemDisp,              	/* Memory-format displacement field */
    InstBrDisp,               	/* Branch-format displacement field */
    InstRA,                   	/* Ra (or Fa) register number */
    InstRB,                   	/* Rb (or Fb) register number */
    InstRC,                   	/* Rc (or Fc) register number */
    InstOpcode,               	/* Instruction's opcode field */
    InstBinary,               	/* Binary representation of whole instruction */
    InstAddrTaken,            	/* True if instruction's address is taken */
    InstEntryPoint,            	/* True if instruction is a procedure entry */
    InstIpJmp,			/* True if interprocedural jump (not call) */
    InstIpBr,			/* True if interprocedural branch (not call) */
    InstContext,		/* Reports procedure context */
    InstStackPtrValid,		/* True if stack ptr updated at this point*/
    InstFramePtrValid,		/* True if frame ptr updated at this point*/
    InstRaRegValid		/* True if return addr reg is set at this point*/
} InstInfoType;


/*
 * Instruction classifications (disjoint).
 */
typedef enum IClass {
    ClassLoad,                	/* Integer load */
    ClassFload,               	/* Floating point load*/
    ClassStore,               	/* Integer store data*/
    ClassFstore,              	/* Floating point store data*/
    ClassIbranch,             	/* Integer branch*/
    ClassFbranch,             	/* Floating point branch*/
    ClassSubroutine,          	/* Integer subroutine call*/
    ClassIarithmetic,         	/* Integer arithmetic*/
    ClassImultiplyl,          	/* Integer longword multiply*/
    ClassImultiplyq,          	/* Integer quadword multiply*/
    ClassIlogical,            	/* Logical functions*/
    ClassIshift,              	/* Shift functions*/
    ClassIcondmove,           	/* Conditional move*/
    ClassIcompare,            	/* Integer compare*/
    ClassFpop,                	/* Other floating point operations*/
    ClassFdivs,               	/* Floating point single precision divide*/
    ClassFdivd,               	/* Floating point double precision divide*/
    ClassNull,                 	/* call pal, hw_x etc*/
    ClassMem			/* Miscellaneous insts which access memory*/
} IClassType;


/*
 * Instruction types (overlapping).
 */
typedef enum IType {
    InstTypeLoad,             	/* Integer or floating point load */
    InstTypeStore,            	/* Integer or floating point store */
    InstTypeJump,             	/* Jump, jsr, or return */
    InstTypeFP,               	/* Any floating point instruction */
    InstTypeInt,              	/* Any integer (non-FP) instruction */
    InstTypeDiv,              	/* Single or double precision divide */
    InstTypeMul,              	/* Integer or floating point multiply */
    InstTypeAdd,              	/* Integer or floating point add */
    InstTypeSub,              	/* Integer or floating point subtract */
    InstTypeCondBr,           	/* Integer or FP conditional branch */
    InstTypeUncondBr,          	/* Unconditional branch (not subroutine call) */
    InstTypeMem,		/* Instruction which accesses memory */
    InstTypeNop, 		/* Any type of NOP instruction */
    InstTypeRet 		/* Return instruction */
} ITypeType;


/*
 * Integer and floating point register numbers.
 * (Pass these constants as parameters for a REGV prototype.)
 */
typedef enum Regs {
    /*
     * Integer registers.
     */
    REG_0,  REG_1,  REG_2,  REG_3,  REG_4,  REG_5,  REG_6,  REG_7,  
    REG_8,  REG_9,  REG_10, REG_11, REG_12, REG_13, REG_14, REG_15, 
    REG_16, REG_17, REG_18, REG_19, REG_20, REG_21, REG_22, REG_23, 
    REG_24, REG_25, REG_26, REG_27, REG_28, REG_29, REG_30, REG_31,

    /*
     * Floating point registers.
     */
    FREG_0, FREG_1, FREG_2, FREG_3, FREG_4, FREG_5, FREG_6, FREG_7,
    FREG_8, FREG_9, FREG_10,FREG_11,FREG_12,FREG_13,FREG_14,FREG_15,
    FREG_16,FREG_17,FREG_18,FREG_19,FREG_20,FREG_21,FREG_22,FREG_23,
    FREG_24,FREG_25,FREG_26,FREG_27,FREG_28,FREG_29,FREG_30,FREG_31,

    /*
     * Special registers.
     */
    REG_PC,                	/* Program counter (pure) */
    REG_CC,                	/* 64-bit cycle counter */
    REG_IPC,               	/* Program counter (instrumented) */
    REG_MAX = REG_IPC,      	/* Marks last valid register number */

    /*
     * Special "not used" value returned by 'GetInstRegEnum()'.
     */
    REG_NOTUSED = -1,

    /*
     * Alternate names for some integer registers.
     */
    REG_RA      = REG_26,  	/* Return address register */
    REG_GP      = REG_29,  	/* Global pointer register */
    REG_SP      = REG_30,  	/* Stack pointer register */
    REG_ZERO    = REG_31,  	/* Integer zero register */
    REG_ARG_1   = REG_16,  	/* First integer argument register */
    REG_ARG_2   = REG_17,  	/* Second integer argument register */
    REG_ARG_3   = REG_18,  	/* Third integer argument register */
    REG_ARG_4   = REG_19,  	/* Fourth integer argument register */
    REG_ARG_5   = REG_20,  	/* Fifth integer argument register */
    REG_ARG_6   = REG_21,  	/* Sixth integer argument register */
    REG_RETVAL  = REG_0,   	/* Integer function return register */

    /*
     * Alternate names for some floating point registers.
     */
    FREG_ZERO   = FREG_31, 	/* Floating point zero register */
    FREG_ARG_1  = FREG_16, 	/* First floating point argument register */
    FREG_ARG_2  = FREG_17, 	/* Second floating point argument register */
    FREG_ARG_3  = FREG_18, 	/* Third floating point argument register */
    FREG_ARG_4  = FREG_19, 	/* Fourth floating point argument register */
    FREG_ARG_5  = FREG_20, 	/* Fifth floating point argument register */
    FREG_ARG_6  = FREG_21, 	/* Sixth floating point argument register */
    FREG_RETVAL = FREG_0   	/* Floating point function return register */
} RegvType;


/*
 * Instruction values.  (Pass these constants as parameters for a VALUE
 * prototype.)
 */
typedef enum Value {
    BrCondValue,  	/* Outcome of conditional branch condition (T/F) */
    EffAddrValue,  	/* Effective address of load or store instruction */
    ArgValue,		/* Original argument in a replaced procedure */
    ArgVectorValue,	/* Variable argument vector */
    ReplAddrValue	/* Address of the replaced entry point */
} ValueType;


/*
 * Instrumentation points for user-added procedure calls.
 */
typedef enum Place {
    ProgramBefore,	/* Add call before program execution */
    ProgramAfter, 	/* Add call after program execution */

    ProcBefore,   	/* Add call before procedure */
    ProcAfter,    	/* Add call after procedure */

    BlockBefore,  	/* Add call before basic block */
    BlockAfter,   	/* Add call after basic block */

    InstBefore,   	/* Add call before instruction */
    InstAfter,    	/* Add call after instruction */

    ObjBefore,    	/* Add call before object */
    ObjAfter,      	/* Add call after object */

    EntryBefore		/* Add call before entry point */	
} PlaceType;


/*
 * Type describing the register usage of an instruction.
 * See 'GetInstRegUsage()'.
 */
typedef struct inst_reg_usage {
    unsigned long 	ureg_bitvec[2];
    unsigned long 	dreg_bitvec[2];
} InstRegUsageVec;

#define UseRegBitVec(x)  	((x)->ureg_bitvec)
#define DestRegBitVec(x) 	((x)->dreg_bitvec)


/*
 * Type used to describe a resolved procedure name.
 * See 'ResolveTargetProc()' and 'ResolveNamedProc()'.
 */
typedef struct {
    Obj *       	obj; 	/* Object containing procedure */
    Proc *      	proc;	/* The procedure */
    const char *	name;	/* The procedure's name */
    Inst *      	inst;	/* The procedure's first instruction */
} ProcRes;


/*
 * Constant indicating unknown size for a translation buffer.  Used with
 * CreateXlate() function.
 */
#define XLATE_NOSIZE 	((unsigned)-1)


/*
 * Possible return values from a GetObjInfo(obj, ObjModifyHint) request.
 */
typedef enum {
    OBJ_READONLY,        	/* object is read-only */
    OBJ_WRITEABLE,        	/* object can be instrumented */
    OBJ_AUTOMATIC		/* internal instrumentation points only */
} ObjModifyType;

/*
 * Possible return values from GetObjInfo(obj, ObjSymResolution) request.
 */
typedef enum {
    OBJ_STANDARD,		/* default symbol resolution */
    OBJ_SYMBOLIC		/* object was linked with -B symbolic */
} ObjSymResType;

/*
 * Possible return values from GetObjInfo(obj, ObjShared) request.
 */
typedef enum {
    OBJ_NON_SHARED,		/* object linked non-shared */
    OBJ_CALL_SHARED,		/* executable object linked call-shared */
    OBJ_SHARABLE		/* shared library (.so) */
} ObjSharedType;


/*
 * Possible return values from a GetProcInfo(pres.proc, ProcSymRes) request.
 */
typedef enum {
     SYMRES_NONE,		/* Not found */
     SYMRES_EXPORT,		/* Global */
     SYMRES_EXPORT_WEAK,	/* Weak Global */
     SYMRES_EXTERN, 		/* External */
     SYMRES_STATIC		/* Local */
} ProcSymResType;


/*
 * Possible return values from a GetInstInfo(inst, InstContext) request.
 */
typedef enum {
    IN_CONTEXT,			/* Inst resides in the procedure context */
    NON_CONTEXT,		/* Inst resides outside the context */
    NON_CONTEXT_STACK,          /* Inst resides outside the context, but
				   stack space has been allocated. */
    CONTEXT_UNKNOWN		/* context info is not valid/available */
} InstContextType;


/*
 * Possible thread options.
 */
typedef enum {
    THREAD_PTHREAD=1, 
    THREAD_FORK=2, 
    THREAD_FLOAT=4
} ThreadOptions;


/*
 * Possible errant shared library error types.  These errors prevent
 * the processing of a shared library, which is then ignored during 
 * instrumentation.
 */
typedef enum {
    SHLIB_NOTOPEN,		/* Unable to open shared library, ignored. */
    SHLIB_NOTFOUND,		/* Unable to find shared library, ignored. */
    SHLIB_STRIPPED,		/* Shared library is stripped, ignored. */
    SHLIB_CMRLC_VERSION,	/* Relocation version number is incorrect, */
				/*	ignored. */
    SHLIB_RELOC_NONE,		/* Shared library has no relocation records, */
				/*	ignored. */
    SHLIB_BADMAGIC,		/* Shared library has unknown COFF magic */
    				/*	number, ignored. */
    SHLIB_NO_FINI_EXIT,		/* Shared library must either define _exit() */
				/*	or have .fini section, ignored. */
    SHLIB_NO_INIT,		/* Shared library must have .init section, */
    				/*	ignored. */
    SHLIB_NZMAGIC_AFTER_TIF,	/* Shared library must not have section */
				/* 	immediately after .text/.init/.fini, */
    				/*	ignored. */
    SHLIB_VERSION		/* Unable to find matching version of shared */
				/*	library, ignored. */
} ShlibErrType;


/*
****************************************************************************
**                                                                        **
**                Prototypes for instrumentation routines                 **
**                                                                        **
****************************************************************************
*/

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Routines to navigate through an application.
 */
extern Obj *  	GetFirstObj(void);
extern Obj *  	GetLastObj(void);
extern Obj *  	GetNextObj(Obj *);
extern Obj *  	GetPrevObj(Obj *);

extern Proc * 	GetFirstObjProc(Obj *);
extern Proc * 	GetLastObjProc(Obj *);
extern Proc * 	GetNextProc(Proc *); 
extern Proc * 	GetPrevProc(Proc *);

extern Entry * 	GetFirstEntry(Proc *);		
extern Entry * 	GetLastEntry(Proc *);		
extern Entry * 	GetNextEntry(Entry *); 		
extern Entry * 	GetPrevEntry(Entry *);		

extern Block *	GetFirstBlock(Proc *); 
extern Block *	GetLastBlock(Proc *);
extern Block *	GetNextBlock(Block *); 
extern Block *	GetPrevBlock(Block *);

extern Inst * 	GetFirstInst(Block *); 
extern Inst * 	GetLastInst(Block *);
extern Inst * 	GetNextInst(Inst *); 
extern Inst * 	GetPrevInst(Inst *);

extern Obj *  	GetProcObj(Proc *);
extern Proc * 	GetBlockProc(Block *);
extern Proc *	GetEntryProc(Entry *);		
extern Block *	GetEntryBlock(Entry *);
extern Block *	GetInstBlock(Inst *);

extern Inst * 	GetInstBranchTarget(Inst *);


/*
 * Routines to add instrumentation code.
 */
extern void 	AddCallProto(const char *);
extern void 	AddCallProgram(PlaceType, const char *, ...);
extern void 	AddCallObj(Obj *, PlaceType, const char *, ...);
extern void 	AddCallProc(Proc *, PlaceType, const char *,  ...);
extern void 	AddCallEntry(Entry *, PlaceType, const char *,  ...); 
extern void 	AddCallBlock(Block *, PlaceType, const char *, ...);
extern void 	AddCallInst(Inst *, PlaceType, const char *,  ...);
extern void 	ReplaceProcedure(Proc *, const char *);
extern void 	ReplaceAndRetainEntry(Entry *, const char *); 
extern void 	ReplaceProto(const char *);
extern void 	ReplaceEntry(Entry *, const char *, ...); 


/*
 * Routines to query about the entire program.
 */
extern long                	GetProgInfo(ProgInfoType);
extern const char *        	GetAnalName(void);

/*
 * Routines to query about objects.
 */
extern long                	GetObjInfo(Obj *, ObjInfoType);
extern const char *        	GetObjName(Obj *);
extern const char *        	GetObjOutName(Obj *);
extern const unsigned int *	GetObjInstArray(Obj *);
extern long                	GetObjInstCount(Obj *);

/*
 * Routines to query about procedures.
 */
extern long                	GetProcInfo(Proc *, ProcInfoType);
extern const char *        	ProcName(Proc *);
extern const char *        	ProcFileName(Proc *);
extern long                	ProcPC(Proc *);
extern long                	ProcGP(Proc *);

/*
 * Routines to query about entry points.
 */
extern long			GetEntryInfo(Entry *, EntryInfoType);	
extern const char *        	EntryName(Entry *);	
extern long			EntryPC(Entry *);

/*
 * Routines to query about basic blocks.
 */
extern long                	GetBlockInfo(Block *, BlockInfoType);
extern long                	BlockPC(Block *);
extern unsigned            	IsBranchTarget(Block *);

/*
 * Routines to query about instructions.
 */
extern IClassType          	GetInstClass(Inst *);
extern int                 	IsInstType(Inst *, ITypeType);
extern int                 	GetInstInfo(Inst *, InstInfoType);
extern long                	InstPC(Inst *);
extern long                	InstLineNo(Inst *);
extern int                 	GetInstBinary(long);
extern RegvType            	GetInstRegEnum(Inst *, InstInfoType);
extern void                	GetInstRegUsage(Inst *, InstRegUsageVec *);


/*
 * Routines to query about shared libraries that were not able to 
 * to be processed.
 */
extern const char * 		GetErrantShlibName(int);
extern ShlibErrType 		GetErrantShlibErr(int);


/*
 * New routines to resolve procedure names and call targets.
 */
extern Obj *		FindObj(const char *);
extern Proc *		FindProc(Obj *, const char *);
extern Entry *		FindEntry(Obj *, const char *);
extern Inst *		FindInst(Obj *, const char *);
extern Obj *		FindObjDepthFirst(Obj *, const char *);
extern Obj *		GetTargetObj(Inst *);
extern Proc *		GetTargetProc(Inst *);
extern Entry *		GetTargetEntry(Inst *);
extern Inst *		GetTargetInst(Inst *);
extern const char *	GetTargetName(Inst *);

/*
 * Obsolete routines to resolve procedure names and call targets.
 */
extern void        	ResolveTargetProc(Inst *, ProcRes *);
extern void        	ResolveNamedProc(const char *, ProcRes *);
extern void        	ReResolveProc(ProcRes *);
extern void        	ResolveObjNamedProc(Obj *, const char *, ProcRes *);


/*
 * Advanced routines to manage instrumentation of objects.
 */
extern unsigned    	BuildObj(Obj *);
extern unsigned    	IsObjBuilt(Obj *);
extern void        	WriteObj(Obj *);
extern void        	ReleaseObj(Obj *);


/*
 * Advanced routines to translate addresses between instrumented and
 * uninstrumented code.
 */
extern Xlate *     	CreateXlate(Obj *, unsigned);
extern void        	AddXlateAddress(Xlate *, Inst *);
extern void		AddXlateEntry(Xlate *, Entry *);


/*
 * Routines to help writers of tools for threaded programs.
 */
extern int		ThreadExcludeObj(Obj *,unsigned long);
extern int		ThreadExcludeProc(Obj *,Proc *,unsigned long);
extern Obj *		ThreadCreationObj(void);
extern Proc *		ThreadCreationProc(void);
extern Obj *		ThreadTerminationObj(void);
extern Proc *		ThreadTerminationProc(void);


/*
 * Prototypes for routine written by user instrumentation code.
 */
extern unsigned 	InstrumentAll(int, char **);
extern void     	InstrumentInit(int, char **);
extern void     	InstrumentFini(void);

#ifdef __cplusplus
}
#endif


/*
****************************************************************************
**                                                                        **
**                          Obsolete interfaces                           **
**                                                                        **
****************************************************************************
*/


/*
 * Used with 'GetProgramInfo()'.  This no longer makes sense for programs
 * with multiple objects.  Use ObjInfoType and 'GetObjInfo()' instead.
 */
typedef enum PInfo {
    TextStartAddress,
    TextSize,
    InitDataStartAddress,
    InitDataSize,
    UninitDataStartAddress,
    UninitDataSize,
    ProgramNumberBlocks,
    ProgramNumberProcs,
    ProgramNumberInsts
} PInfoType;


/*
 * Old ProcInfoType identifiers.  Use "Proc" versions instead.
 */
#define FrameSize  	ProcFrameSize
#define IRegMask   	ProcIRegMask
#define IRegOffset 	ProcIRegOffset
#define FRegMask   	ProcFRegMask
#define FRegOffset 	ProcFRegOffset
#define gpPrologue 	ProcgpPrologue
#define gpUsed     	ProcgpUsed
#define LocalOffset	ProcLocalOffset
#define FrameReg   	ProcFrameReg
#define PcReg      	ProcPcReg


#define IInfoType	InstInfoType	/* Use InstInfoType instead */

#define RET_RES_1	REG_RETVAL   	/* Use REG_RETVAL instead */


#ifdef __cplusplus
extern "C" {
#endif
/*
 * The meanings of these routines are not well-defined for programs with
 * multiple objects.  Tools should use equivalent routines that operate on
 * Obj's instead.
 */
extern Proc *              	GetFirstProc(void); 
extern Proc *              	GetLastProc(void);
extern const char *        	GetProgramName(void);
extern char *              	GetOutName(void);
extern long                	GetProgramInfo(PInfoType);
extern const unsigned int *	GetProgramInstArray(void);
extern long                	GetProgramInstCount(void);


/*
 * Use 'ResolveTargetProc()', 'ResolveNamedProc()', and 'ReResolveProc()'
 * instead of these.
 */
extern Proc *              	GetProcCalled(Inst *);
extern Proc *              	GetNamedProc(const char *);
extern Obj *               	GetNamedProcObj(const char *);
extern const char *        	GetInstProcCalled(Inst *);


/*
 * Use ThreadTerminationProc() and pthread_atfork() (with -fork option)
 * instead of these.
 */
extern int		ThreadExitCall(Obj *,unsigned long,const char *);
extern int		ThreadForkCall(Obj *,unsigned long,
				       const char *,const char *);

#ifdef __cplusplus
}
#endif


#endif /* _ATOM_INST_H_ */
