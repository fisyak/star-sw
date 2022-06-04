/***************************************************************************
 *
 * $Id: StTpcRTSHitMaker.cxx,v 1.59 2021/05/10 21:13:19 fisyak Exp $
 *
 * Author: Valeri Fine, BNL Feb 2007
 ***************************************************************************
 *
 * Description:  Make clusters from StTpcRawData and fill the StEvent      */
#include <assert.h>
#include <stdio.h>
#include "StTpcHitMaker.h"
#include "StTpcRTSHitMaker.h"

#include "StTpcRawData.h"
#include "StEvent/StTpcRawData.h"
#include "StEvent/StTpcHit.h"
#include "StEvent/StEvent.h"
#include "StEvent/StTpcHitCollection.h"
#include "StThreeVectorF.hh"
#include "StTpcDb/StTpcDb.h"
#include "StDbUtilities/StCoordinates.hh"
#include "StDetectorDbMaker/St_tss_tssparC.h"
#include "StDetectorDbMaker/St_tpcPadGainT0BC.h"
#include "StDetectorDbMaker/St_tpcAnodeHVavgC.h"
#include "StDetectorDbMaker/St_tpcMaxHitsC.h"
#include "StDetectorDbMaker/StDetectorDbTpcRDOMasks.h"
#include "StDetectorDbMaker/St_tpcPadPlanesC.h"
#include "StDetectorDbMaker/St_itpcPadPlanesC.h"
#include "StDetectorDbMaker/St_tpcPadConfigC.h"
#include "StDetectorDbMaker/St_tpcStatusC.h"
#include "StMessMgr.h" 
#include "StDAQMaker/StDAQReader.h"
#include "StRtsTable.h"
#include "DAQ_TPX/daq_tpx.h"
#include "DAQ_ITPC/daq_itpc.h"
#include "DAQ_READER/daq_dta.h"
#include "DAQ_READER/daq_det.h"
#include "DAQ_READER/daqReader.h"
#include "RTS/src/DAQ_TPX/tpxFCF_flags.h" // for FCF flag definition
#include "RTS/src/DAQ_TPX/daq_tpx.h"
#include "RTS/src/DAQ_TPX/tpxCore.h"
#include "RTS/src/DAQ_TPX/tpxPed.h"
#include "RTS/src/DAQ_TPX/tpxGain.h"
#include "RTS/src/DAQ_TPX/tpxFCF.h"
#include "RTS/src/DAQ_TPX/tpxStat.h"
#include "RTS/src/DAQ_ITPC/itpcFCF.h"
#include "TPC23/tpx23.h"
#include "TPC23/itpc23.h"

#include "TBenchmark.h"
ClassImp(StTpcRTSHitMaker); 
#define __DEBUG__
#ifdef __DEBUG__
#define PrPP(A,B) if (Debug()%10 > 1) {LOG_INFO << "StTpcRTSHitMaker::" << (#A) << "\t" << (#B) << " = \t" << (B) << endm;}
#else
#define PrPP(A,B)
#endif
#if 0
static struct rp_dta_t {
	short adc[512] ;
} rp_dta[46][183] ;
#endif
//________________________________________________________________________________
StTpcRTSHitMaker::~StTpcRTSHitMaker() {
  SafeDelete(fTpx);
  SafeDelete(fiTpc);
  SafeDelete(fTpx23);
  SafeDelete(fiTpc23);
}
//________________________________________________________________________________
Int_t StTpcRTSHitMaker::Init() {
  memset(maxHits,0,sizeof(maxHits));
  maxBin0Hits = 0;
  bin0Hits = 0;
  return StMaker::Init();
}
//________________________________________________________________________________
Int_t StTpcRTSHitMaker::InitRun(Int_t runnumber) {
  SetAttr("minSector",1);
  SetAttr("maxSector",24);
  SetAttr("minRow",1);
  if (IAttr("Cosmics")) StTpcHitMaker::SetCosmics();
  SetAttr("maxRow",St_tpcPadConfigC::instance()->numberOfRows(20));
  SafeDelete(fTpx);
  SafeDelete(fiTpc);
  SafeDelete(fTpx23);
  SafeDelete(fiTpc23);
  if ( IAttr("TPC23")) {
    int log_level = 0 ;
    const char *fname  = "none" ;
    fTpx23  = new tpx23;
    fTpx23->log_level = log_level;
    fTpx23->gains_from_cache(fname) ;	// REQUIRED even if no gain correction
    fTpx23->run_start() ;

    fiTpc23 = new itpc23 ;
    fiTpc23->log_level = log_level;
    fiTpc23->gains_from_cache(fname) ;	// REQUIRED even if no gain correction
    fiTpc23->run_start() ;
  } else {
    fTpx = new daq_tpx() ; 
    if (GetDate() >= 20091215) fTpx->fcf_run_compatibility = 10 ;
    // change default value 2 to 
    fTpx->fcf_do_cuts = 1; // 1 means always, 2 means don't cut edges (for i.e. pulser run), 0 means don't...
    //  if (GetDate() >= 20121215) fTpx->fcf_style = 2 ;  // from online/RTS/src/ESB/tpx.C new for FY13!
    if (GetDate() <= 20090101) fminCharge = 40;
    // Check presence iTPC
    static Bool_t fNoiTPCLu  = IAttr("NoiTPCLu");
    if (! fNoiTPCLu) {
      for(Int_t sector=1;sector<=24;sector++) {
	if (St_tpcPadConfigC::instance()->iTPC(sector)) {
	  fiTpc = new daq_itpc() ;
	  break;
	}
      }
    }
  }
  StMaker* maskMk = GetMakerInheritsFrom("StMtdTrackingMaskMaker");
  unsigned int mask = (maskMk ? maskMk->UAttr("TpcSectorsByMtd") : ~0U); // 24 bit masking for sectors 1..24
  // Load gains
  if (fTpx) {
    // do gains example; one loads them from database but I don't know how...
    daq_dta *dta_Tpx  = fTpx->put("gain"); 
    for(Int_t sector=1;sector<=24;sector++) {
      if (!((1U<<(sector-1)) & mask)) continue; // sector masking
      // Tpx
      Int_t rowMin = 1;
      if (St_tpcPadConfigC::instance()->iTPC(sector)) rowMin = 14; 
      for(Int_t rowO = 1; rowO <= 45; rowO++) {
	Int_t Npads = St_tpcPadPlanesC::instance()->padsPerRow(rowO);
	Int_t padMin = 1;
	Int_t padMax = Npads;
	daq_det_gain *gain = (daq_det_gain *) dta_Tpx->request(Npads+1);    // max pad+1            
	for(Int_t pad = 0; pad <= Npads; pad++) {
	  gain[pad].gain = 0.; // be sure that dead pads are killed
	  gain[pad].t0   = 0.;
	  if (rowO >= rowMin && pad >= padMin && pad <= padMax) {
	    if (St_tpcPadGainT0C::instance()->Gain(sector,rowO,pad) <= 0) continue;
	    gain[pad].gain = St_tpcPadGainT0C::instance()->Gain(sector,rowO,pad);
	    gain[pad].t0   = St_tpcPadGainT0C::instance()->T0(sector,rowO,pad);
	  }
	}
	// daq_dta::finalize(uint32_t obj_cou, int sec, int row, int pad)
	dta_Tpx->finalize(Npads+1,sector,rowO);
      }
    }
  }
  // iTpc
  if (fiTpc) {
    daq_dta * dta_iTpc = fiTpc->put("gain"); // , 0, 40, 0, miTpc_RowLen);
    
    for(Int_t sector=1;sector<=24;sector++) {
      if (! St_tpcPadConfigC::instance()->iTPC(sector)) continue;
      for(Int_t row = 1; row <= 40; row++) {
	Int_t Npads = St_itpcPadPlanesC::instance()->padsPerRow(row);
	daq_det_gain *gain = (daq_det_gain *) dta_iTpc->request(Npads+1);	// max pad+1		
	for(Int_t pad = 0; pad <= Npads; pad++) {
	  gain[pad].gain = 0.; // be sure that dead pads are killed
	  gain[pad].t0   = 0.;
	  if (pad < 1) continue; // kill pad0 just in case..
	  if (St_itpcPadGainT0C::instance()->Gain(sector,row,pad) <= 0) continue;
	  gain[pad].gain = St_itpcPadGainT0C::instance()->Gain(sector,row,pad);
	  gain[pad].t0   = St_itpcPadGainT0C::instance()->T0(sector,row,pad);
	  //#define __DEBUG_GAIN__
#ifdef __DEBUG_GAIN__
	  cout << Form("Gain/T0 s/r/p %3i/%3i/%3i %7.2f %7.2f",sector,row,pad,gain[pad].gain,gain[pad].t0) << endl;
#endif /* __DEBUG_GAIN__ */
	}
	// daq_dta::finalize(uint32_t obj_cou, int sec, int row, int pad)
	dta_iTpc->finalize(Npads+1,sector,row);
      }
    }
  }
  if (fTpx23) {
    // Tpx
    for(Int_t sector=1;sector<=24;sector++) {
      if (!((1U<<(sector-1)) & mask)) continue; // sector masking
      Int_t rowMin = 1;
      if (St_tpcPadConfigC::instance()->iTPC(sector)) rowMin = 14; 
      for(Int_t rowO = 1; rowO <= 45; rowO++) {
	Int_t Npads = St_tpcPadPlanesC::instance()->padsPerRow(rowO);
	Int_t padMin = 1;
	Int_t padMax = Npads;
	for(Int_t pad = 0; pad <= Npads; pad++) {
	  fTpx23->rp_gain[sector-1][rowO][pad].gain = 0.; // be sure that dead pads are killed
	  fTpx23->rp_gain[sector-1][rowO][pad].t0   = 0.;
	  if (rowO >= rowMin && pad >= padMin && pad <= padMax) {
	    if (St_tpcPadGainT0C::instance()->Gain(sector,rowO,pad) <= 0) continue;
	    fTpx23->rp_gain[sector-1][rowO][pad].gain = St_tpcPadGainT0C::instance()->Gain(sector,rowO,pad);
	    fTpx23->rp_gain[sector-1][rowO][pad].t0   = St_tpcPadGainT0C::instance()->T0(sector,rowO,pad);
	  }
	}
      }
    }
  }
  if (fiTpc23) {
    for(Int_t sector=1;sector<=24;sector++) {
      if (!((1U<<(sector-1)) & mask)) continue; // sector masking
      if (! St_tpcPadConfigC::instance()->iTPC(sector)) continue;
      for(Int_t row = 1; row <= 40; row++) {
	Int_t Npads = St_itpcPadPlanesC::instance()->padsPerRow(row);
	for(Int_t pad = 0; pad <= Npads; pad++) {
	  fiTpc23->rp_gain[sector-1][row][pad].gain = 0.; // be sure that dead pads are killed
	  fiTpc23->rp_gain[sector-1][row][pad].t0   = 0.;
	  if (pad < 1) continue; // kill pad0 just in case..
	  if (St_itpcPadGainT0C::instance()->Gain(sector,row,pad) <= 0) continue;
	  fiTpc23->rp_gain[sector-1][row][pad].gain = St_itpcPadGainT0C::instance()->Gain(sector,row,pad);
	  fiTpc23->rp_gain[sector-1][row][pad].t0   = St_itpcPadGainT0C::instance()->T0(sector,row,pad);
	  //#define __DEBUG_GAIN__
#ifdef __DEBUG_GAIN__
	  cout << Form("Gain/T0 s/r/p %3i/%3i/%3i %7.2f %7.2f",sector,row,pad,fiTpc23->rp_gain[sector-1][row][pad].gain,fiTpc23->rp_gain[sector-1][row][pad].t0) << endl;
#endif /* __DEBUG_GAIN__ */
	}
      }
    }
  }
  PrintAttr();
  return kStOK;
}
//________________________________________________________________________________
void StTpcRTSHitMaker::PrintCld(daq_cld *cld, Int_t IdTruth, Int_t quality) {
  if (cld) {
    LOG_INFO << Form("    pad %f[%d:%d], tb %f[%d:%d], cha %d, fla 0x%X, Id %d, Q %d ",
		     cld->pad,
		     cld->p1,
		     cld->p2,
		     cld->tb,
		     cld->t1,
		     cld->t2,
		     cld->charge,
		     cld->flags,
		     IdTruth,
		     quality
		     ) << endm;
  }
}
//________________________________________________________________________________
void StTpcRTSHitMaker::PrintAdc(daq_dta *dta) {
  if (dta) {
    // verify data!
    Int_t sectorOld = -1;
    Int_t rowOld = -1;
    Int_t adcSum = 0;
    while(dta && dta->iterate()) {
      if (sectorOld != dta->sec || rowOld != dta->row) {
	if (sectorOld > 0) {
	  LOG_INFO << Form("*** sec %2d, row %2d, Sum adc = %d",sectorOld,rowOld,adcSum) << endm;
	}
	sectorOld = dta->sec;
        rowOld = dta->row;
	adcSum = 0;
      }
      if (Debug() > 1) {LOG_INFO << Form("*** sec %2d, row %2d, pad %3d: %3d pixels",dta->sec,dta->row,dta->pad,dta->ncontent) << endm;}
      for(UInt_t i=0;i<dta->ncontent;i++) {
	if (Debug() > 1) {
	  LOG_INFO << Form("    %2d: adc %4d, tb %3d: track %4d",i,
			   dta->sim_adc[i].adc,
			   dta->sim_adc[i].tb,
			   dta->sim_adc[i].track_id
			   ) << endm;
	}
	adcSum += dta->sim_adc[i].adc;
      }
    }
    if (sectorOld > 0) {
      LOG_INFO << Form("*** sec %2d, row %2d, Sum adc = %d",sectorOld,rowOld,adcSum) << endm;
    }
  }
}
//________________________________________________________________________________
Int_t StTpcRTSHitMaker::Make() {
#ifdef __BENCHMARK__
  TBenchmark *myBenchmark = new TBenchmark();
  myBenchmark->Reset();
  //  myBenchmark->Start("StTpcRTSHitMaker::Make");
#endif
  if (St_tpcStatusC::instance()->isDead()) {
    LOG_WARN << "TPC status indicates it is unusable for this event. Ignoring hits." << endm;
    return kStOK;
  }
  if (IAttr("TPC23")) return Make23();
  static Short_t ADCs[__MaxNumberOfTimeBins__];
#ifdef __TFG__VERSION__
  static Int_t IDTs[__MaxNumberOfTimeBins__];
#else
  static UShort_t IDTs[__MaxNumberOfTimeBins__];
#endif
  static StTpcCoordinateTransform transform;
  static StThreeVectorF hard_coded_errors;
  StEvent*   rEvent      = (StEvent*)    GetInputDS("StEvent");
  if (! rEvent) {
    LOG_WARN << "There is no StEvent" << endm;
    return kStWarn;
  }
  StTpcHitCollection *hitCollection = rEvent->tpcHitCollection();
  if (! hitCollection )  {
    hitCollection = new StTpcHitCollection();
    rEvent->setTpcHitCollection(hitCollection);
  }
  TDataSet*  tpcRawEvent =               GetInputDS("Event");
  if (! tpcRawEvent) {
    LOG_WARN << "There is not Tpc Raw Event" << endm;
    return kStWarn;
  }
  //  if (Debug()) tpcRawEvent->ls();
  StTpcRawData *tpcRawData = (StTpcRawData *) tpcRawEvent->GetObject();
  if (! tpcRawData) {
    LOG_WARN << "There is not Tpc Raw Data" << endm;
    return kStWarn;
  }
  // create (or reuse) the adc_sim bank...
  // add a bunch of adc data for a specific sector:row:pad
  static Int_t  minSector = IAttr("minSector");
  static Int_t  maxSector = IAttr("maxSector");
  static Int_t  minRow    = IAttr("minRow");
  static Int_t  maxRow    = IAttr("maxRow");
  bin0Hits = 0;
  for (Int_t sector = minSector; sector <= maxSector; sector++) {
    StTpcDigitalSector *digitalSector = tpcRawData->GetSector(sector);
    if (! digitalSector) continue;
    UShort_t Id = 0;
    Int_t hitsAdded = 0;
    for (Int_t iTpcType  = 1; iTpcType >= 0; iTpcType--) {// Tpx iTPC
      daq_dta *dta  = 0;
      tpc23_base *tpc23 = 0;
      Int_t row1 = minRow;
      Int_t row2 = maxRow;
      // Check presense of iTPC and adjust row range
      if (St_tpcPadConfigC::instance()->iTPC(sector)) {
	//  daq_tpx::get(const char *bank="*", int c1=-1, int c2=-1, int c3=-1, void *p1=0, void *p2=0)
	//           put(const char *bank="*", int c1=-1, int c2=-1, int c3=-1, void *p1=0, void *p2=0)
	// daq_itpc::get(const char *bank="*",int c1=-1, int c2=-1, int c3=-1, void *p1=0, void *p2=0)
	//           put(const char *in_bank="*", int sector=-1, int row=-1, int pad=-1, void *p1=0, void *p2=0)
	if (! iTpcType) { // Tpx
	  row1 = TMath::Max(row1, 41); 
	  if (fTpx) dta = fTpx->put("adc_sim"); 
	  else  tpc23 = fTpx23;
	} else { // iTpc           {
	  row2 = TMath::Min(40, row2); 
	  if (fiTpc) dta = fiTpc->put("adc_sim"); 
	  else  tpc23 = fTpx23;
	}
      } else { // no iTPC
	row2 = TMath::Min(45, row2);
	if (fTpx) dta = fTpx->put("adc_sim"); 
	else  tpc23 = fTpx23;
      }
      if (! dta) continue;
      Int_t NoAdcs = 0;
      for (Int_t row = row1; row <= row2; row++) {
	if (! St_tpcPadGainT0BC::instance()->livePadrow(sector,row)) continue;
	Int_t Npads = digitalSector->numberOfPadsInRow(row);
	Int_t rowO = row;
	//	daq_dta *dta  = 0;
	if (! iTpcType) {
	  if (St_tpcPadConfigC::instance()->iTPC(sector) && row > 40) { // Tpx sector with iTPC
	    rowO = row - 40 + 13; // old row count
	  }
	}
	for(Int_t pad = 1; pad <= Npads; pad++) {
	  UInt_t ntimebins = digitalSector->numberOfTimeBins(row,pad);
	  if (! ntimebins) continue;
	  // allocate space for at least 512 pixels (timebins)
	  daq_sim_adc_tb *d = (daq_sim_adc_tb *) dta->request(__MaxNumberOfTimeBins__);
	  // add adc data for this specific sector:row:pad
	  digitalSector->getTimeAdc(row,pad,ADCs,IDTs);
	  UInt_t l = 0;
	  for (UInt_t k = 0; k < __MaxNumberOfTimeBins__; k++) {
	    if (ADCs[k]) {
	      d[l].adc = ADCs[k];
	      d[l].tb  = k;
	      d[l].track_id = IDTs[k];
	      l++;
	    }
	  }
	  if (l > 0) {
#ifdef __BENCHMARK__
	    //	    myBenchmark->Start("StTpcRTSHitMaker::Make::finalize");
#endif
	    // daq_dta::finalize(uint32_t obj_cou, int s=0, int row=0, int pad=0) ;
	    dta->finalize(l,sector,rowO,pad);
#ifdef __BENCHMARK__
	    //	    myBenchmark->Stop("StTpcRTSHitMaker::Make::finalize");
#endif
	    NoAdcs += l;
	  }
	} // pad loop
      } // row loop      
      if (! NoAdcs) continue;
	daq_dta *dtaX = 0;
	if (! iTpcType) {
	  if (fTpx) dtaX = fTpx->get("adc_sim");
	} else {
	  if (fiTpc) dtaX = fiTpc->get("adc_sim");
	}
	dta = dtaX;
	if (Debug()) {
	  PrintAdc(dta);
	}
	dtaX  = 0;
	if (! iTpcType) { //Tpx
	  if (! fTpx) continue;
	  if (IAttr("TpxClu2D")) {
	    dtaX = fTpx->get("cld_2d_sim"); 
	  } else {
	    dtaX = fTpx->get("cld_sim");;   
	  }
	} else { // iTpc
	  if (! fiTpc) continue;
	  dtaX = fiTpc->get("cld_sim"); 
	}
	if (! dtaX) continue;
	daq_dta *dd = dtaX;
#ifndef __TFG__VERSION__
	Double_t ADC2GeV = 0;
	Int_t rowOld = -1;
#endif /* ! __TFG__VERSION__ */
	static Int_t iBreak = 0;
	while(dd && dd->iterate()) {
	  if (Debug()) {
	    LOG_INFO << Form("CLD sec %2d: row %2d: %d clusters",dd->sec, dd->row, dd->ncontent) << endm;
	  }
	  for(UInt_t i=0;i<dd->ncontent;i++) {
	    daq_cld cld;
	    Int_t IdTruth = 0;
	    UShort_t quality  = 0;
	    if (! iTpcType) {
	      daq_sim_cld   &dc   = ((daq_sim_cld   *) dd->Void)[i] ;
	      cld      = dc.cld;
	      IdTruth = dc.track_id;
	      quality  = dc.quality;
	    } else {
	      daq_sim_cld_x &dc_x = ((daq_sim_cld_x *) dd->Void)[i] ;
	      cld      = dc_x.cld;
	      IdTruth = dc_x.track_id;
	      quality  = dc_x.quality;
	    }
	    if (Debug()) {
	      PrintCld(&cld, IdTruth, quality);
	      iBreak++;
	    }
	    if (cld.p1 > cld.p2) continue;
	    if (cld.t1 > cld.t2) continue;
	    if (cld.tb >= __MaxNumberOfTimeBins__) continue;
	    if (cld.charge < fminCharge) continue;
	    if ( ! (cld.pad >  0 && cld.pad <= 182 && 
		    cld.tb  >= 0 && cld.tb  <  512)) continue;
	    /*tpxFCF.h
	      #define FCF_ONEPAD              1
	      #define FCF_DOUBLE_PAD          2       // offline: merged
	      #define FCF_MERGED              2
	      #define FCF_BIG_CHARGE          8
	      #define FCF_ROW_EDGE           16      // 0x10 touched end of row
	      #define FCF_BROKEN_EDGE        32      // 0x20 touches one of the mezzanine edges
	      #define FCF_DEAD_EDGE          64      // 0x40 touches a dead pad 
	    */
	    if ( cld.flags && (cld.flags & ~(FCF_ONEPAD | FCF_MERGED | FCF_BIG_CHARGE))) continue;
	    Int_t rowO = dd->row;
	    Int_t padrow  = rowO;
	    if (! iTpcType && St_tpcPadConfigC::instance()->iTPC(sector) && rowO > 13)  padrow = rowO + 40 - 13;
	    Int_t row = padrow;
	    Float_t pad  = cld.pad;
	    Int_t iRdo    = StDetectorDbTpcRDOMasks::instance()->rdoForPadrow(sector,row,pad);
	    if ( ! StDetectorDbTpcRDOMasks::instance()->isOn(sector,iRdo)) continue;
	    
	    StTpcPadCoordinate Pad(dd->sec, padrow, cld.pad, cld.tb); PrPP(Make,Pad);
	    static StTpcLocalSectorCoordinate LS;
	    static StTpcLocalCoordinate L;
	    transform(Pad,LS,kFALSE,kTRUE); PrPP(Make,LS); // don't useT0, useTau                  
	    transform(LS,L);                                                                             PrPP(Make,L);
	    UInt_t hw = 1;   // detid_tpc
	    //yf        if (isiTpcSector) hw += 1U << 1;
	    hw += dd->sec << 4;     // (padrow/100 << 4);   // sector
	    hw += padrow  << 9;     // (padrow%100 << 9);   // padrow
#ifndef __TFG__VERSION__
	    if (padrow != rowOld) {
	      rowOld = padrow;
	      Double_t gain = St_tpcPadConfigC::instance()->IsRowInner(dd->sec,padrow) ? 
		St_tss_tssparC::instance()->gain_in() : 
		St_tss_tssparC::instance()->gain_out();
	      Double_t wire_coupling = St_tpcPadConfigC::instance()->IsRowInner(dd->sec,padrow) ? 
		St_tss_tssparC::instance()->wire_coupling_in() : 
		St_tss_tssparC::instance()->wire_coupling_out();
	      ADC2GeV = ((Double_t) St_tss_tssparC::instance()->ave_ion_pot() * 
			 (Double_t) St_tss_tssparC::instance()->scale())/(gain*wire_coupling) ;
	    }
	    Double_t q = ADC2GeV*cld.charge;
#else /* used in TFG till 07/31/20 */
	    Double_t q = 0; 
#endif /* ! __TFG__VERSION__ */
	    Id++;
	    StTpcHit *hit = StTpcHitMaker::StTpcHitFlag(L.position(),hard_coded_errors,hw,q
							, (UChar_t ) 0  // counter 
							, IdTruth
							, quality
							, Id                                   // id =0,
							, cld.p1 //  mnpad
							, cld.p2 //  mxpad
							, cld.t1 //  mntmbk
							, cld.t2 //  mxtmbk
							, cld.pad
							, cld.tb 
							, cld.charge
							, cld.flags);
	    if (! hit) continue;
	    hitsAdded++;
	    if (hit->minTmbk() == 0) bin0Hits++;
	    if (Debug() > 1) hit->Print();
	    hitCollection->addHit(hit);
	    if (Debug() > 1) {cout << "Add hit #" << hitCollection->numberOfHits() << endl;}
	  }
	}
    } // end iTpcType loop
    if (maxHits[sector-1] && hitsAdded > maxHits[sector-1]) {
      LOG_ERROR << "Too many hits (" << hitsAdded << ") in one sector ("
                << sector << "). Skipping event." << endm;
      return kStSkip;
    }
  }  // end sec loop
  if (maxBin0Hits && bin0Hits > maxBin0Hits) {
    LOG_ERROR << "Too many hits (" << bin0Hits
              << ") starting at time bin 0. Skipping event." << endm;
    return kStSkip;
  }
  if (! IAttr("NoTpxAfterBurner")) StTpcHitMaker::AfterBurner(hitCollection);
#ifdef __BENCHMARK__
  myBenchmark->Stop("StTpcRTSHitMaker::Make");
  myBenchmark->Show("StTpcRTSHitMaker::Make");
  myBenchmark->Show("StTpcRTSHitMaker::Make::finalize");
  delete myBenchmark;
#endif
  return kStOK;
}
//________________________________________________________________________________
Int_t StTpcRTSHitMaker::Make23() {
  if (! fTpx23 && ! fiTpc23) return kStErr;
#ifdef __BENCHMARK__
  TBenchmark *myBenchmark = new TBenchmark();
  myBenchmark->Reset();
  //  myBenchmark->Start("StTpcRTSHitMaker::Make");
#endif
  if (St_tpcStatusC::instance()->isDead()) {
    LOG_WARN << "TPC status indicates it is unusable for this event. Ignoring hits." << endm;
    return kStOK;
  }
  static Short_t ADCs[__MaxNumberOfTimeBins__];
  static Int_t IDTs[__MaxNumberOfTimeBins__];
  static StTpcCoordinateTransform transform;
  static StThreeVectorF hard_coded_errors;
  StEvent*   rEvent      = (StEvent*)    GetInputDS("StEvent");
  if (! rEvent) {
    LOG_WARN << "There is no StEvent" << endm;
    return kStWarn;
  }
  StTpcHitCollection *hitCollection = rEvent->tpcHitCollection();
  if (! hitCollection )  {
    hitCollection = new StTpcHitCollection();
    rEvent->setTpcHitCollection(hitCollection);
  }
  TDataSet*  tpcRawEvent =               GetInputDS("Event");
  if (! tpcRawEvent) {
    LOG_WARN << "There is not Tpc Raw Event" << endm;
    return kStWarn;
  }
  //  if (Debug()) tpcRawEvent->ls();
  StTpcRawData *tpcRawData = (StTpcRawData *) tpcRawEvent->GetObject();
  if (! tpcRawData) {
    LOG_WARN << "There is not Tpc Raw Data" << endm;
    return kStWarn;
  }
  // create (or reuse) the adc_sim bank...
  // add a bunch of adc data for a specific sector:row:pad
  static Int_t  minSector = IAttr("minSector");
  static Int_t  maxSector = IAttr("maxSector");
  static Int_t  minRow    = IAttr("minRow");
  static Int_t  maxRow    = IAttr("maxRow");
  bin0Hits = 0;
  for (Int_t sector = minSector; sector <= maxSector; sector++) {
    StTpcDigitalSector *digitalSector = tpcRawData->GetSector(sector);
    if (! digitalSector) continue;
    UShort_t Id = 0;
    Int_t hitsAdded = 0;
    //    daq_dta *dta  = 0;
    for (Int_t iTpcType  = 1; iTpcType >= 0; iTpcType--) {// Tpx iTPC
      tpc23_base *tpc23 = 0;
      Int_t row1 = minRow;
      Int_t row2 = maxRow;
      // Check presense of iTPC and adjust row range
      if (St_tpcPadConfigC::instance()->iTPC(sector)) {
	//  daq_tpx::get(const char *bank="*", int c1=-1, int c2=-1, int c3=-1, void *p1=0, void *p2=0)
	//           put(const char *bank="*", int c1=-1, int c2=-1, int c3=-1, void *p1=0, void *p2=0)
	// daq_itpc::get(const char *bank="*",int c1=-1, int c2=-1, int c3=-1, void *p1=0, void *p2=0)
	//           put(const char *in_bank="*", int sector=-1, int row=-1, int pad=-1, void *p1=0, void *p2=0)
	if (! iTpcType) { // Tpx
	  row1 = TMath::Max(row1, 41); 
	  tpc23 = fTpx23;
	} else { // iTpc           {
	  row2 = TMath::Min(40, row2); 
	  tpc23 = fiTpc23;
	}
      } else { // no iTPC
	row2 = TMath::Min(45, row2);
	tpc23 = fTpx23;
      }
      if (! tpc23) continue;
      for (Int_t row = row1; row <= row2; row++) {
	if (! St_tpcPadGainT0BC::instance()->livePadrow(sector,row)) continue;
	tpc23->sim_evt_start(sector) ;	// prepare start of event
	Int_t NoAdcs = 0;
	Int_t Npads = digitalSector->numberOfPadsInRow(row);
	Int_t rowO = row;
	//	daq_dta *dta  = 0;
	if (! iTpcType) {
	  if (St_tpcPadConfigC::instance()->iTPC(sector) && row > 40) { // Tpx sector with iTPC
	    rowO = row - 40 + 13; // old row countx1
	  }
	}
	Double_t gain = St_tpcPadConfigC::instance()->IsRowInner(sector,row) ? 
	  St_tss_tssparC::instance()->gain_in() : 
	  St_tss_tssparC::instance()->gain_out();
	Double_t wire_coupling = St_tpcPadConfigC::instance()->IsRowInner(sector,row) ? 
	  St_tss_tssparC::instance()->wire_coupling_in() : 
	  St_tss_tssparC::instance()->wire_coupling_out();
	Double_t ADC2GeV = ((Double_t) St_tss_tssparC::instance()->ave_ion_pot() * 
			    (Double_t) St_tss_tssparC::instance()->scale())/(gain*wire_coupling) ;

	for(Int_t pad = 1; pad <= Npads; pad++) {
	  UInt_t ntimebins = digitalSector->numberOfTimeBins(row,pad);
	  if (! ntimebins) continue;
	  // allocate space for at least 512 pixels (timebins)
	  //	  daq_sim_adc_tb *d = (daq_sim_adc_tb *) dta->request(__MaxNumberOfTimeBins__);
	  // add adc data for this specific sector:row:pad
	  digitalSector->getTimeAdc(row,pad,ADCs,IDTs);
	  UInt_t l = 0;
	  for (UInt_t k = 0; k < __MaxNumberOfTimeBins__; k++) {
	    if (ADCs[k]) {
	      l++;
	    }
	  }
	  if (l > 0) {
	    Int_t padrow = rowO;
	    tpc23->sim_do_pad(padrow,pad,ADCs,IDTs) ;
	    NoAdcs += l;
	  }
	} // pad loop

	if (NoAdcs) {
	  
	  // Tonko's     ------------------------------------------------------------ 
	  
	  // allocate output storage based upon the count of found sequences
	  const int words_per_cluster = 5 ;       // 5 for simulation, 2 normally

	  tpc23->s2_max_words = tpc23->sequence_cou*words_per_cluster + 2000 ;      // and add a bit more...
	  
	  tpc23->s2_start = (u_int *) malloc(tpc23->s2_max_words*4) ;
	  
	  // this actually runs the clusterfinder
	  tpc23->evt_stop() ;
	  
      
	  if(tpc23->s2_words) {	// if anything found..
	    u_int *p_buff = tpc23->s2_start ;
	    u_int *end_buff = p_buff + tpc23->s2_words ;
	    if (Debug()) {
	      cout << Form("*** sequences found %d",tpc23->sequence_cou) << endl ;
	    }

                       if(tpc23->s2_words >= tpc23->s2_max_words) {
			 LOG_ERROR << "Whoa -- lots of words " << tpc23->s2_words << "/" << tpc23->s2_max_words << "\t"
				   <<  "\tsector " << sector << "\trow " << row << endm;
                       }

	    while(p_buff < end_buff) {
				u_int padrow ;
				u_int version ;
				u_int int_cou ;
				int ints_per_cluster ;
				// TPX and iTPC have slightly different formats; maintained compatibility
				if(tpc23 == fTpx23) {// det==0) {	// TPX
					padrow = *p_buff++ ;
					int_cou = *p_buff++ ;

					version = (padrow>>16) ;

					ints_per_cluster = 5 ;	// 5 for sim, 2 for real
				}
				else {	
					padrow = *p_buff++ ;
					version = *p_buff++ ;
					int_cou = *p_buff++ ;

					ints_per_cluster = (padrow>>16) ;
					
				}
	  
	  padrow &= 0xFFFF ;
	  
	  int clusters = int_cou / ints_per_cluster ;
	  
	  for(int i=0;i<clusters;i++) {
	    daq_sim_cld_x dc ;
	    tpc23->fcf_decode(p_buff,&dc,version) ;
	    
	    // nice flags printout
	    char c_flags[128] ;
	    c_flags[0] = 0 ;
	    
	    if(dc.cld.flags & FCF_ONEPAD) strcat(c_flags,"one+") ;
	    if(dc.cld.flags & FCF_MERGED) strcat(c_flags,"merge+") ;
	    if(dc.cld.flags & FCF_DEAD_EDGE) strcat(c_flags,"dead+") ;
	    if(dc.cld.flags & FCF_ROW_EDGE) strcat(c_flags,"edge+") ;						if(dc.cld.flags & FCF_ONEPAD) strcat(c_flags," one") ;
	    if(dc.cld.flags & FCF_BROKEN_EDGE) strcat(c_flags,"small+") ;
	    if(dc.cld.flags & FCF_BIG_CHARGE) strcat(c_flags,"charge+") ;
	    
	    if(strlen(c_flags)) {
	      c_flags[strlen(c_flags)-1] = 0 ;
	    }
	    if (Debug()) {
	      cout << Form("row %d/%d: %f %d %d %f %d %d %d 0x%02X[%s]",row,rowO,
			   dc.cld.pad,dc.cld.p1,dc.cld.p2,
			   dc.cld.tb,dc.cld.t1,dc.cld.t2,
			   dc.cld.charge,
			   dc.cld.flags,c_flags) << endl;
	      cout << Form("   track_id %u, quality %d, pixels %d, max_adc %d",
			   dc.reserved[0],
			   dc.quality,
			   dc.pixels,               //<<<<<<<<<<   Add to TpcHit ?
			   dc.max_adc) << endl;;    //<<<<<<<<<<
	    }
	    
	    p_buff += ints_per_cluster ;
	    // Tonko's end    ------------------------------------------------------------ 
	    Int_t   IdTruth  = dc.reserved[0];
	    UShort_t quality = dc.quality;
	    // Fill TpcHit
	    if (dc.cld.p1 > dc.cld.p2) continue;
	    if (dc.cld.t1 > dc.cld.t2) continue;
	    if (dc.cld.tb >= __MaxNumberOfTimeBins__) continue;
	    if (dc.cld.charge < fminCharge) continue;
	    if ( ! (dc.cld.pad >  0 && dc.cld.pad <= 182 && 
		    dc.cld.tb  >= 0 && dc.cld.tb  <  512)) continue;
	    /*tpxFCF.h
	      #define FCF_ONEPAD              1
	      #define FCF_DOUBLE_PAD          2       // offline: merged
	      #define FCF_MERGED              2
	      #define FCF_BIG_CHARGE          8
	      #define FCF_ROW_EDGE           16      // 0x10 touched end of row
	      #define FCF_BROKEN_EDGE        32      // 0x20 touches one of the mezzanine edges
	      #define FCF_DEAD_EDGE          64      // 0x40 touches a dead pad 
	    */
	    if ( dc.cld.flags && (dc.cld.flags & ~(FCF_ONEPAD | FCF_MERGED | FCF_BIG_CHARGE))) continue;
	    Float_t pad  = dc.cld.pad;
	    Int_t iRdo    = StDetectorDbTpcRDOMasks::instance()->rdoForPadrow(sector,row,pad);
	    if ( ! StDetectorDbTpcRDOMasks::instance()->isOn(sector,iRdo)) continue;
	    
	    StTpcPadCoordinate Pad(sector, row, dc.cld.pad, dc.cld.tb); PrPP(Make,Pad);
	    static StTpcLocalSectorCoordinate LS;
	    static StTpcLocalCoordinate L;
	    transform(Pad,LS,kFALSE,kTRUE); PrPP(Make,LS); // don't useT0, useTau                  
	    transform(LS,L);                                                                             PrPP(Make,L);
	    UInt_t hw = 1;   // detid_tpc
	    //yf        if (isiTpcSector) hw += 1U << 1;
	    hw += sector << 4;     // (row/100 << 4);   // sector
	    hw += row  << 9;       // (row%100 << 9);   // row
#ifndef __TFG__VERSION__
	    Double_t q = ADC2GeV*dc.cld.charge;
#else /* used in TFG till 07/31/20 */
	    Double_t q = 0; 
#endif /* ! __TFG__VERSION__ */
	    Id++;
	    StTpcHit *hit = StTpcHitMaker::StTpcHitFlag(L.position(),hard_coded_errors,hw,q
							, (UChar_t ) 0  // counter 
							, IdTruth
							, quality
							, Id                                   // id =0,
							, dc.cld.p1 //  mnpad
							, dc.cld.p2 //  mxpad
							, dc.cld.t1 //  mntmbk
							, dc.cld.t2 //  mxtmbk
							, dc.cld.pad
							, dc.cld.tb 
							, dc.cld.charge
							, dc.cld.flags);
	    if (! hit) continue;
	    hitsAdded++;
	    if (hit->minTmbk() == 0) bin0Hits++;
	    if (Debug() > 1) hit->Print();
	    hitCollection->addHit(hit);
	    if (Debug() > 1) {cout << "Add hit #" << hitCollection->numberOfHits() << endl;}
	  }
	}
	tpc23->run_stop() ;	// dumps some statistics...
	
	// free allocated storage
	free(tpc23->s2_start) ;
	tpc23->s2_start = 0 ;
      } // clusters loop
      } // row loop      
      
    } // end of row
      
      
    } // end iTpcType loop
  } // end of sector
  
    
    
  if (! IAttr("NoTpxAfterBurner")) StTpcHitMaker::AfterBurner(hitCollection);
#ifdef __BENCHMARK__
  myBenchmark->Stop("StTpcRTSHitMaker::Make");
  myBenchmark->Show("StTpcRTSHitMaker::Make");
  myBenchmark->Show("StTpcRTSHitMaker::Make::finalize");
  delete myBenchmark;
#endif
  return kStOK;
}
