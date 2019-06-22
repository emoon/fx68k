// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _Vfx68k_H_
#define _Vfx68k_H_

#include "verilated.h"

class Vfx68k__Syms;

//----------

VL_MODULE(Vfx68k) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    // Begin mtask footprint  all: 
    VL_IN8(clk,0,0);
    VL_IN8(extReset,0,0);
    VL_IN8(pwrUp,0,0);
    VL_IN8(enPhi1,0,0);
    VL_IN8(enPhi2,0,0);
    VL_OUT8(eRWn,0,0);
    VL_OUT8(ASn,0,0);
    VL_OUT8(LDSn,0,0);
    VL_OUT8(UDSn,0,0);
    VL_OUT8(E,0,0);
    VL_OUT8(VMAn,0,0);
    VL_OUT8(FC0,0,0);
    VL_OUT8(FC1,0,0);
    VL_OUT8(FC2,0,0);
    VL_OUT8(BGn,0,0);
    VL_OUT8(oRESETn,0,0);
    VL_OUT8(oHALTEDn,0,0);
    VL_IN8(DTACKn,0,0);
    VL_IN8(VPAn,0,0);
    VL_IN8(BERRn,0,0);
    VL_IN8(BRn,0,0);
    VL_IN8(BGACKn,0,0);
    VL_IN8(IPL0n,0,0);
    VL_IN8(IPL1n,0,0);
    VL_IN8(IPL2n,0,0);
    VL_IN16(iEdb,15,0);
    VL_OUT16(oEdb,15,0);
    VL_OUT(eab,23,1);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    // Anonymous structures to workaround compiler member-count bugs
    struct {
	// Begin mtask footprint  all: 
	VL_SIG8(fx68k__DOT__Clks,4,0);
	VL_SIG8(fx68k__DOT__wClk,0,0);
	VL_SIG8(fx68k__DOT__enT1,0,0);
	VL_SIG8(fx68k__DOT__enT2,0,0);
	VL_SIG8(fx68k__DOT__enT3,0,0);
	VL_SIG8(fx68k__DOT__enT4,0,0);
	VL_SIG8(fx68k__DOT__rDtack,0,0);
	VL_SIG8(fx68k__DOT__rBerr,0,0);
	VL_SIG8(fx68k__DOT__rIpl,2,0);
	VL_SIG8(fx68k__DOT__iIpl,2,0);
	VL_SIG8(fx68k__DOT__Vpai,0,0);
	VL_SIG8(fx68k__DOT__BeI,0,0);
	VL_SIG8(fx68k__DOT__BRi,0,0);
	VL_SIG8(fx68k__DOT__BgackI,0,0);
	VL_SIG8(fx68k__DOT__BeiDelay,0,0);
	VL_SIG8(fx68k__DOT__rstUrom,0,0);
	VL_SIG8(fx68k__DOT__Tpend,0,0);
	VL_SIG8(fx68k__DOT__intPend,0,0);
	VL_SIG8(fx68k__DOT__pswT,0,0);
	VL_SIG8(fx68k__DOT__pswS,0,0);
	VL_SIG8(fx68k__DOT__pswI,2,0);
	VL_SIG8(fx68k__DOT__dcr4,0,0);
	VL_SIG8(fx68k__DOT__tvn,3,0);
	VL_SIG8(fx68k__DOT__busAddrErr,0,0);
	VL_SIG8(fx68k__DOT__bgBlock,0,0);
	VL_SIG8(fx68k__DOT__addrOe,0,0);
	VL_SIG8(fx68k__DOT__iStop,0,0);
	VL_SIG8(fx68k__DOT__A0Err,0,0);
	VL_SIG8(fx68k__DOT__excRst,0,0);
	VL_SIG8(fx68k__DOT__BerrA,0,0);
	VL_SIG8(fx68k__DOT__Spuria,0,0);
	VL_SIG8(fx68k__DOT__Avia,0,0);
	VL_SIG8(fx68k__DOT__rAddrErr,0,0);
	VL_SIG8(fx68k__DOT__iBusErr,0,0);
	VL_SIG8(fx68k__DOT__Err6591,0,0);
	VL_SIG8(fx68k__DOT__iAddrErr,0,0);
	VL_SIG8(fx68k__DOT__enErrClk,0,0);
	VL_SIG8(fx68k__DOT__oReset,0,0);
	VL_SIG8(fx68k__DOT__oHalted,0,0);
	VL_SIG8(fx68k__DOT__rFC,2,0);
	VL_SIG8(fx68k__DOT__inl,2,0);
	VL_SIG8(fx68k__DOT__updIll,0,0);
	VL_SIG8(fx68k__DOT__prevNmi,0,0);
	VL_SIG8(fx68k__DOT__iplStable,0,0);
	VL_SIG8(fx68k__DOT__iplComp,0,0);
	VL_SIG8(fx68k__DOT__eCntr,3,0);
	VL_SIG8(fx68k__DOT__rVma,0,0);
	VL_SIG8(fx68k__DOT__irdToCcr_t4,0,0);
	VL_SIG8(fx68k__DOT__ssw,4,0);
	VL_SIG8(fx68k__DOT__tvnLatch,3,0);
	VL_SIG8(fx68k__DOT__inExcept01,0,0);
	VL_SIG8(fx68k__DOT__microToNanoAddr__DOT__orgBase,8,2);
	VL_SIG8(fx68k__DOT__uaddrDecode__DOT__eaCol,3,0);
	VL_SIG8(fx68k__DOT__uaddrDecode__DOT__movEa,3,0);
	VL_SIG8(fx68k__DOT__uaddrDecode__DOT__pla_lined__DOT__illMisc,0,0);
	VL_SIG8(fx68k__DOT__sequencer__DOT__c0c1,1,0);
	VL_SIG8(fx68k__DOT__sequencer__DOT__a0Rst,0,0);
	VL_SIG8(fx68k__DOT__sequencer__DOT__enl,1,0);
	VL_SIG8(fx68k__DOT__sequencer__DOT__ms0,1,0);
	VL_SIG8(fx68k__DOT__sequencer__DOT__m01,3,0);
	VL_SIG8(fx68k__DOT__sequencer__DOT__ccTest,0,0);
	VL_SIG8(fx68k__DOT__sequencer__DOT__rTrace,0,0);
	VL_SIG8(fx68k__DOT__sequencer__DOT__rInterrupt,0,0);
	VL_SIG8(fx68k__DOT__sequencer__DOT__rIllegal,0,0);
    };
    struct {
	VL_SIG8(fx68k__DOT__sequencer__DOT__rPriv,0,0);
	VL_SIG8(fx68k__DOT__sequencer__DOT__rLineA,0,0);
	VL_SIG8(fx68k__DOT__sequencer__DOT__rLineF,0,0);
	VL_SIG8(fx68k__DOT__sequencer__DOT__rExcRst,0,0);
	VL_SIG8(fx68k__DOT__sequencer__DOT__rExcAdrErr,0,0);
	VL_SIG8(fx68k__DOT__sequencer__DOT__rExcBusErr,0,0);
	VL_SIG8(fx68k__DOT__sequencer__DOT__rSpurious,0,0);
	VL_SIG8(fx68k__DOT__sequencer__DOT__rAutovec,0,0);
	VL_SIG8(fx68k__DOT__sequencer__DOT__grp1LatchEn,0,0);
	VL_SIG8(fx68k__DOT__sequencer__DOT__grp0LatchEn,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__abdIsByte,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__Pcl2Dbl,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__Pch2Dbh,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__Pcl2Abl,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__Pch2Abh,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__actualRx,4,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__actualRy,4,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__movemRx,3,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__byteNotSpAlign,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__rxMux,4,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__ryMux,4,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__rxReg,3,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__ryReg,3,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__rxIsSp,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__ryIsSp,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__rxIsAreg,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__ryIsAreg,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__ryl2Abl,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__ryl2Abd,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__ryl2Dbl,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__ryl2Dbd,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__rxl2Abl,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__rxl2Abd,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__rxl2Dbl,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__rxl2Dbd,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__abhIdle,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__ablIdle,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__abdIdle,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__dbhIdle,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__dblIdle,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__dbdIdle,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__dbl2Pcl,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__dbh2Pch,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__abh2Pch,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__abl2Pcl,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__prHbit,3,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__dataIo__DOT__xToDbin,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__dataIo__DOT__xToIrc,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__dataIo__DOT__dbinNoLow,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__dataIo__DOT__dbinNoHigh,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__dataIo__DOT__byteMux,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__dataIo__DOT__isByte_T4,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__dataIo__DOT__byteCycle,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__pswCcr,4,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__ccrCore,4,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__ccrTemp,4,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__coreH,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__subHcarry,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__subCout,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__subOv,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__isArX,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__noCcrEn,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__isByte,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__ccrMask,4,0);
    };
    struct {
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__oper,4,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__cMask,4,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__aluOp,4,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__bcdLatch,7,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__bcdCarry,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__bcdOverf,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__isLong,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__rIrd8,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__isShift,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__shftCin,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__shftRight,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__shftMsb,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__bcdV,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__ccrMasked,4,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__rowDecoder__DOT__size11,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__rowDecoder__DOT__unnamedblk1__DOT__stype,1,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__aluCorf__DOT__hNib,4,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__aluCorf__DOT__lowC,0,0);
	VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT__aluCorf__DOT__highC,0,0);
	VL_SIG8(fx68k__DOT__nDecoder__DOT__ftuCtrl,3,0);
	VL_SIG8(fx68k__DOT__nDecoder__DOT__dobCtrl,1,0);
	VL_SIG8(fx68k__DOT__nDecoder__DOT__isPcRel,0,0);
	VL_SIG8(fx68k__DOT__irdDecode__DOT__isRegShift,0,0);
	VL_SIG8(fx68k__DOT__irdDecode__DOT__unnamedblk1__DOT__eaIsAreg,0,0);
	VL_SIG8(fx68k__DOT__busControl__DOT__rAS,0,0);
	VL_SIG8(fx68k__DOT__busControl__DOT__rLDS,0,0);
	VL_SIG8(fx68k__DOT__busControl__DOT__rUDS,0,0);
	VL_SIG8(fx68k__DOT__busControl__DOT__rRWn,0,0);
	VL_SIG8(fx68k__DOT__busControl__DOT__bcPend,0,0);
	VL_SIG8(fx68k__DOT__busControl__DOT__isWriteReg,0,0);
	VL_SIG8(fx68k__DOT__busControl__DOT__bciByte,0,0);
	VL_SIG8(fx68k__DOT__busControl__DOT__isRmcReg,0,0);
	VL_SIG8(fx68k__DOT__busControl__DOT__wendReg,0,0);
	VL_SIG8(fx68k__DOT__busControl__DOT__addrOeDelay,0,0);
	VL_SIG8(fx68k__DOT__busControl__DOT__isByteT4,0,0);
	VL_SIG8(fx68k__DOT__busControl__DOT__canStart,0,0);
	VL_SIG8(fx68k__DOT__busControl__DOT__bcReset,0,0);
	VL_SIG8(fx68k__DOT__busControl__DOT__busEnding,0,0);
	VL_SIG8(fx68k__DOT__busArbiter__DOT__rGranted,0,0);
	VL_SIG16(fx68k__DOT__microAddr,9,0);
	VL_SIG16(fx68k__DOT__nma,9,0);
	VL_SIG16(fx68k__DOT__nanoAddr,8,0);
	VL_SIG16(fx68k__DOT__psw,15,0);
	VL_SIG16(fx68k__DOT__ftu,15,0);
	VL_SIG16(fx68k__DOT__Irc,15,0);
	VL_SIG16(fx68k__DOT__Ir,15,0);
	VL_SIG16(fx68k__DOT__Ird,15,0);
	VL_SIG16(fx68k__DOT__alue,15,0);
	VL_SIG16(fx68k__DOT__uaddrDecode__DOT__lineBmap,15,0);
	VL_SIG16(fx68k__DOT__uaddrDecode__DOT__pla_lined__DOT__arIll,15,0);
	VL_SIG16(fx68k__DOT__uaddrDecode__DOT__pla_lined__DOT__scA3,9,0);
	VL_SIG16(fx68k__DOT__uaddrDecode__DOT__pla_lined__DOT__a1Misc,9,0);
	VL_SIG16(fx68k__DOT__sequencer__DOT__uNma,9,0);
	VL_SIG16(fx68k__DOT__sequencer__DOT__grp1Nma,9,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__dbin,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__dcrOutput,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__PcL,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__PcH,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__Ath,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__Atl,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__Dbl,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__Dbh,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__Abh,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__Abl,15,0);
    };
    struct {
	VL_SIG16(fx68k__DOT__excUnit__DOT__Abd,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__Dbd,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__dblMux,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__dbhMux,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__abhMux,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__ablMux,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__preAbh,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__preAbl,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__preAbd,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__preDbh,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__preDbl,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__preDbd,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__prenLatch,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__dcrCode,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__alub,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__dobInput,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__dataIo__DOT__dob,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__alu__DOT__aluLatch,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__alu__DOT__result,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__alu__DOT__subResult,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__alu__DOT__row,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__alu__DOT__aOperand,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__alu__DOT__dOperand,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__alu__DOT__cRow,15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__alu__DOT__aluCorf__DOT__htemp,8,0);
	VL_SIG16(fx68k__DOT__irdDecode__DOT__lineOnehot,15,0);
	VL_SIG(fx68k__DOT__tState,31,0);
	VL_SIGW(fx68k__DOT__nanoLatch,67,0,3);
	VL_SIGW(fx68k__DOT__nanoOutput,67,0,3);
	VL_SIG(fx68k__DOT__microLatch,16,0);
	VL_SIG(fx68k__DOT__microOutput,16,0);
	VL_SIG(fx68k__DOT__excUnit__DOT__auReg,31,0);
	VL_SIG(fx68k__DOT__excUnit__DOT__aob,31,0);
	VL_SIG(fx68k__DOT__excUnit__DOT__auInpMux,31,0);
	VL_SIG(fx68k__DOT__excUnit__DOT__aulow,16,0);
	VL_SIG(fx68k__DOT__excUnit__DOT__alu__DOT__shftResult,31,0);
	VL_SIG(fx68k__DOT__excUnit__DOT__alu__DOT__shifter__DOT__tdata,31,0);
	VL_SIG(fx68k__DOT__busControl__DOT__busPhase,31,0);
	VL_SIG(fx68k__DOT__busControl__DOT__next,31,0);
	VL_SIG(fx68k__DOT__busArbiter__DOT__dmaPhase,31,0);
	VL_SIG(fx68k__DOT__busArbiter__DOT__next,31,0);
	VL_SIG64(fx68k__DOT__Nanod,55,0);
	VL_SIG64(fx68k__DOT__Nanod2,48,0);
	VL_SIG64(fx68k__DOT__Irdecod,41,0);
	VL_SIG16(fx68k__DOT__uaddrDecode__DOT__pla_lined__DOT__arA1[16],9,0);
	VL_SIG16(fx68k__DOT__uaddrDecode__DOT__pla_lined__DOT__arA23[16],9,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__regs68L[18],15,0);
	VL_SIG16(fx68k__DOT__excUnit__DOT__regs68H[18],15,0);
    };
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    // Begin mtask footprint  all: 
    VL_SIG8(fx68k__DOT__excUnit__DOT____Vlvbound5,7,0);
    VL_SIG8(fx68k__DOT__excUnit__DOT____Vlvbound9,7,0);
    VL_SIG8(fx68k__DOT__excUnit__DOT__alu__DOT____Vcellinp__shifter__swapWords,0,0);
    VL_SIG8(__Vfunc_fx68k__DOT__uaddrDecode__DOT__eaDecode__0__Vfuncout,3,0);
    VL_SIG8(__Vfunc_fx68k__DOT__uaddrDecode__DOT__eaDecode__0__eaBits,5,0);
    VL_SIG8(__Vfunc_fx68k__DOT__uaddrDecode__DOT__eaDecode__1__Vfuncout,3,0);
    VL_SIG8(__Vfunc_fx68k__DOT__uaddrDecode__DOT__eaDecode__1__eaBits,5,0);
    VL_SIG8(__Vtask_fx68k__DOT__excUnit__DOT__alu__DOT__mySubber__2__cin,0,0);
    VL_SIG8(__Vtask_fx68k__DOT__excUnit__DOT__alu__DOT__mySubber__2__bAdd,0,0);
    VL_SIG8(__Vtask_fx68k__DOT__excUnit__DOT__alu__DOT__mySubber__2__isByte,0,0);
    VL_SIG8(__Vtask_fx68k__DOT__excUnit__DOT__alu__DOT__mySubber__2__cout,0,0);
    VL_SIG8(__Vtask_fx68k__DOT__excUnit__DOT__alu__DOT__mySubber__2__ov,0,0);
    VL_SIG8(__Vtask_fx68k__DOT__excUnit__DOT__alu__DOT__mySubber__2__rm,0,0);
    VL_SIG8(__Vtask_fx68k__DOT__excUnit__DOT__alu__DOT__mySubber__2__sm,0,0);
    VL_SIG8(__Vtask_fx68k__DOT__excUnit__DOT__alu__DOT__mySubber__2__dm,0,0);
    VL_SIG8(__Vtask_fx68k__DOT__excUnit__DOT__alu__DOT__mySubber__2__tsm,0,0);
    VL_SIG8(__Vfunc_fx68k__DOT__excUnit__DOT__alu__DOT__aluCorf__DOT__gt9__3__Vfuncout,0,0);
    VL_SIG8(__Vfunc_fx68k__DOT__excUnit__DOT__alu__DOT__aluCorf__DOT__gt9__3__nib,3,0);
    VL_SIG8(__Vfunc_fx68k__DOT__excUnit__DOT__alu__DOT__aluCorf__DOT__gt9__4__Vfuncout,0,0);
    VL_SIG8(__Vfunc_fx68k__DOT__excUnit__DOT__alu__DOT__aluCorf__DOT__gt9__4__nib,3,0);
    VL_SIG8(__Vtableidx1,7,0);
    VL_SIG8(__Vtableidx4,3,0);
    VL_SIG8(__Vtableidx5,3,0);
    VL_SIG8(__Vtableidx6,3,0);
    VL_SIG8(__Vclklast__TOP__clk,0,0);
    VL_SIG8(__Vchglast__TOP__fx68k__DOT__nDecoder__DOT__isPcRel,0,0);
    VL_SIG16(fx68k__DOT__excUnit__DOT____Vlvbound3,15,0);
    VL_SIG16(fx68k__DOT__excUnit__DOT____Vlvbound4,15,0);
    VL_SIG16(fx68k__DOT__excUnit__DOT____Vlvbound6,15,0);
    VL_SIG16(fx68k__DOT__excUnit__DOT____Vlvbound7,15,0);
    VL_SIG16(fx68k__DOT__excUnit__DOT____Vlvbound8,15,0);
    VL_SIG16(fx68k__DOT__excUnit__DOT____Vlvbound10,15,0);
    VL_SIG16(fx68k__DOT__excUnit__DOT____Vlvbound11,15,0);
    VL_SIG16(fx68k__DOT__excUnit__DOT____Vlvbound12,15,0);
    VL_SIG16(__Vtask_fx68k__DOT__excUnit__DOT__alu__DOT__mySubber__2__inpa,15,0);
    VL_SIG16(__Vtask_fx68k__DOT__excUnit__DOT__alu__DOT__mySubber__2__inpb,15,0);
    VL_SIG16(__Vtask_fx68k__DOT__excUnit__DOT__alu__DOT__mySubber__2__result,15,0);
    VL_SIG16(__Vchglast__TOP__fx68k__DOT__excUnit__DOT__alu__DOT__aluCorf__DOT__htemp,8,0);
    VL_SIG(__Vtask_fx68k__DOT__excUnit__DOT__alu__DOT__mySubber__2__rtemp,16,0);
    VL_SIG64(__Vchglast__TOP__fx68k__DOT__Nanod,55,0);
    VL_SIG64(__Vchglast__TOP__fx68k__DOT__Irdecod,41,0);
    VL_SIG8(__Vtablechg2[512],0,0);
    static VL_ST_SIG8(__Vtable1_fx68k__DOT__microToNanoAddr__DOT__orgBase[256],8,2);
    static VL_ST_SIGW(__Vtable2_fx68k__DOT__nanoOutput[512],67,0,3);
    static VL_ST_SIG(__Vtable3_fx68k__DOT__microOutput[1024],16,0);
    static VL_ST_SIG16(__Vtable4_fx68k__DOT__uaddrDecode__DOT__lineBmap[16],15,0);
    static VL_ST_SIG16(__Vtable5_fx68k__DOT__excUnit__DOT__dcrCode[16],15,0);
    static VL_ST_SIG16(__Vtable6_fx68k__DOT__irdDecode__DOT__lineOnehot[16],15,0);
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vfx68k__Syms* __VlSymsp;  // Symbol table
    
    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vfx68k);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vfx68k(const char* name="TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vfx68k();
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval();
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vfx68k__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vfx68k__Syms* symsp, bool first);
  private:
    static QData _change_request(Vfx68k__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__4(Vfx68k__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset();
  public:
    static void _eval(Vfx68k__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif // VL_DEBUG
  public:
    static void _eval_initial(Vfx68k__Syms* __restrict vlSymsp);
    static void _eval_settle(Vfx68k__Syms* __restrict vlSymsp);
    static void _initial__TOP__3(Vfx68k__Syms* __restrict vlSymsp);
    static void _sequent__TOP__2(Vfx68k__Syms* __restrict vlSymsp);
    static void _settle__TOP__1(Vfx68k__Syms* __restrict vlSymsp);
    static void _settle__TOP__5(Vfx68k__Syms* __restrict vlSymsp);
} VL_ATTR_ALIGNED(128);

#endif // guard
