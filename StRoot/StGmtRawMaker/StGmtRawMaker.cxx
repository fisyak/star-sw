//
// First Cluster Maker
// \class StGmtRawMaker
// \authors K.S. Engle and Richard Witt (witt@usna.edu)
// based on StFgtClusterMaker
#include <string>
#include "StGmtRawMaker.h"
#include "StRoot/StEvent/StEvent.h"
#include "StRoot/StEvent/StGmtCollection.h"
#include "StEvent/StGmtHit.h"
#include "StRtsTable.h"
#include "DAQ_READER/daq_dta.h"
#include "DAQ_FGT/daq_fgt.h"
#include "StGmtGeom.h"
#include "TSystem.h"
#include "StMessMgr.h" 
#include "TFumili.h"
#include "TFile.h"
#include "TAxis.h"
ClassImp(StGmtRawMaker);

const UInt_t         CLUS_BINS = 128;
const Double_t       CLUS_MIN  = 0.0;
const Double_t       CLUS_MAX  = 128*0.08;
const UInt_t         MAX_PEAKS = 8; // from TFumili default no. of parameters = 25
//________________________________________________________________________________
StGmtRawMaker::StGmtRawMaker( const Char_t* name ) :  StRTSBaseMaker( "clustser", name ) {
  memset(mBeg,0,mEnd-mBeg+1);
  SetAttr("gmtCosmics"             ,kFALSE);
  TFile *f = GetTFile();
  for (Int_t ixy = 0; ixy < kGmtNumLayers; ixy++) {
    for (UShort_t module = 0; module < kGmtNumModules; module++) {
      TString name("Pedestal");
      if (! ixy) name += "X";
      else       name += "Y";
      name += "_"; name += module;
      mPedestalXY[ixy][module] = new TProfile(name,name,CLUS_BINS,CLUS_MIN,CLUS_MAX,"s");
      mPedestalXY[ixy][module]->SetDirectory(f);
    }
  }
};
//________________________________________________________________________________
Int_t StGmtRawMaker::InitRun(Int_t /* runumber */) {
   return 0;
}
//________________________________________________________________________________
Int_t StGmtRawMaker::Make() {
  static ULong_t nEvents=0;
  StEvent* event = (StEvent*) (GetInputDS("StEvent"));
  if(!event) {
    LOG_ERROR << "Error getting pointer to StEvent from '" << ClassName() << "'" << endm;
    return kStErr;
  }
  mGmtCollection = event->gmtCollection();
  if(!mGmtCollection)    {
    mGmtCollection = new StGmtCollection();
    if(!mGmtCollection)	{
      LOG_DEBUG <<"::prepareEnvironment could not create StGmtCollection" <<endm;
      return kStFatal;
    }
    event->setGmtCollection(mGmtCollection);
    LOG_DEBUG <<"::prepareEnvironment() has added a non existing StGmtCollection()"<<endm;
  } else  {
    //this should be unncessary if the member clear function is called
    mGmtCollection->Clear();
  }
  if (fillHits()) return kStWarn;
  UInt_t noModWithGMT = 0;
  for(UInt_t module=0; module < kGmtNumModules; module++) {
    if(Debug()) {
      LOG_INFO << "module: " << module << " has strips: \t" <<  mGmtCollection->getNumStrips(module) << endm;
    }
    Int_t nelements = mGmtCollection->getNumStrips(module);
    if(! nelements) {
      if(Debug()) {
	LOG_WARN <<"StClusterMaker::Make(): no data for module " << module << endm;
      }
      continue;
    }
    StGmtHitCollection *hitCollection = mGmtCollection->getHitCollection(module);
    if (ClusterBuilder(nEvents,module,*hitCollection)) noModWithGMT++;
    const StGmtHitCollection *coll = mGmtCollection->getHitCollection(module);
    if (! coll) continue;
    if (Debug()) {
      const StSPtrVecGmtHit &hits = coll->getHitVec();
      UInt_t NoHits = hits.size();
      for (UInt_t l = 0; l < NoHits; l++) {
	const StGmtHit *hit = hits[l];
	if (hit) {
	  hit->Print("");
	}
      }
    }
  }
  if (noModWithGMT) nEvents++;
  
  if(Debug()) {
    LOG_INFO << "End of gmt-clust-maker, print all strips & clusters: " << endm;
    LOG_INFO <<"  gmtCollnumModule=" << kGmtNumModules<<", tot strip=" <<mGmtCollection->getNumStrips()
	     <<"  totClust=" <<  mGmtCollection->getNumHits() <<endm;
  }
  if (! mGmtCollection->getNumHits()) return kStERR;
  return kStOk;
}
//________________________________________________________________________________
 Int_t StGmtRawMaker::Init() {
  if (IAttr("gmtCosmics")) SetAttr(".Privilege",kTRUE);
  if (gFumili) {delete gFumili;}
  new TFumili(MAX_PEAKS*3+1);
  return StMaker::Init();
}
//________________________________________________________________________________
Double_t StGmtRawMaker::MyGaus(Double_t x, Double_t mean, Double_t sigma, Double_t delta) {
  return TMath::Freq((x-mean+delta/2)/sigma)-TMath::Freq((x-mean-delta/2)/sigma);
}
//________________________________________________________________________________
/**
utility function to get the data from the daq file and fill the StEvent structure
*/
Int_t StGmtRawMaker::fillHits() {
  static Int_t mChIdToSeqId[128] = {
    0,16,32,48,64,80,96,112,4,20,36,52,68,84,100,116,8,
    24,40,56,72,88,104,120,12,28,44,60,76,92,108,124,1,
    17,33,49,65,81,97,113,5,21,37,53,69,85,101,117,9,
    25,41,57,73,89,105,121,13,29,45,61,77,93,109,125,2,
    18,34,50,66,82,98,114,6,22,38,54,70,86,102,118,10,
    26,42,58,74,90,106,122,14,0,46,62,78,94,110,126,3,
    19,35,51,67,83,99,115,7,23,39,55,71,87,103,119,11,
    27,43,59,75,91,107,123,15,31,47,63,79,95,111,127
  };
   mGmtCollection->Clear();
  
  Int_t rdo=0;
  Int_t arm=0;
  Int_t apv=0;
  Int_t channel=0;
  Short_t adc=0;
  Short_t timebin=0;
  Short_t moduleIdx=0;
  Short_t coordNum=0;
  Double_t position=0;
  Int_t ok = kStWarn;

//   LOG_INFO << "StGmtRawMaker::fillHits() Trying to find fgt/adc... " << endm;
  LOG_INFO << "StGmtRawMaker::fillHits() Trying to find gmt/adc... " << endm;
  if (Debug() > 2) {
    for (Int_t module = 0; module < kGmtNumModules; module++) {
      for (Int_t ixy = 0; ixy < kGmtNumLayers; ixy++) {
	static const Char_t *XY[2] = {"X", "Y"};
	if (! mAdcTimeBins[ixy][module]) {
	  mAdcTimeBins[ixy][module] = 
	    new TH2F(Form("AdcT%s_%i",XY[ixy],module),Form("Adc versus strip and time %s module %i",XY[ixy],module), 
		     kGmtNumTimeBins, -0.5, kGmtNumTimeBins -0.5, CLUS_BINS, CLUS_MIN, CLUS_MAX);
	} else {
	  mAdcTimeBins[ixy][module]->Reset();
	}
      }
    }
  }
  ////// FIX ME!!!!!!!!!!!!!!!!!!
  //now grab the constants from the header file, loop over the raw data and fill the hits...
  TString query("gmt/adc");
  //  TString query("gmt/zs");
  while(GetNextDaqElement(query.Data()))    {
    StRtsTable* rts_tbl=DaqDta();
    Int_t count = 0;
    for(StRtsTable::iterator it=rts_tbl->begin();it!=rts_tbl->end();it++)	{
      fgt_adc_t *mGmtRawData=(fgt_adc_t*)*it;
      rdo=rts_tbl->Rdo();
      Int_t chanTmp=mGmtRawData->ch;
      channel=mChIdToSeqId[chanTmp];	
      //this is different from rts_example
      timebin=mGmtRawData->tb;
      //look at rts_example for the mapping 
      adc=mGmtRawData->adc;
      arm=rts_tbl->Sector();
      apv=rts_tbl->Pad();
      count++;
      if(Debug() > 3) {
	LOG_INFO << "StGmtRawMaker::fillHits() Got: " <<
	  "rdo: " << rdo <<
	  "  arm: " << arm <<
	  "  apv: " << apv <<
	  "  channel: " << channel <<
	  "  timebin: " << timebin <<
	  "  adc: " << adc <<
	  endm;
      }
      Int_t geoId = StGmtGeom::encodeGeoId( rdo, arm, apv, channel ); // geoId same as elecId for now (RW 3/29/2013)
      Int_t layer=-1;
      Short_t stripNo=-1;
      coordNum = StGmtGeom::getCoordNumFromElecCoord( rdo, arm, apv, channel );
      position = StGmtGeom::getPositionFromElecCoord( rdo, arm, apv, channel );
      // the next segment is needed because of a lack of ARM port information
      StGmtGeom::decodeGeoId( geoId, moduleIdx, layer, stripNo );
      StGmtStripCollection *stripCollection = mGmtCollection->getStripCollection( moduleIdx );
      if( stripCollection )	    {
	geoId =  StGmtGeom::encodeGeoId( rdo, arm, apv, channel );
	StGmtStrip* strip = stripCollection->getStrip( geoId );
	if( coordNum == 999 ) { // these are not connected
	  strip->setAdc( 0, timebin );
	  strip->setCharge( 0 ); // was done in separate maker for FGT (StFgtA2CMaker), assume gain=1 for now
	  strip->setChargeUncert( 0 ); // was done in separate maker for FGT (StFgtA2CMaker), assume gain=1 for now
	  strip->setGeoId( geoId );
	  strip->setModule( moduleIdx );
	  strip->setIsY( layer );
	  strip->setPosition( position );
	  strip->setElecCoords( rdo, arm, apv, channel );
	  strip->setCoordNum( coordNum );
	} else  {// these are connected (mapping in StGmtGeom.cxx)
	  if(layer) {// layer here is just an indicator for either a X ( i.e. strip (=0) ) or Y ( i.e. pad (=1) ) element
	    strip->setCoordNum( coordNum + kGmtNumStrips ); // map Y into 128-255
	    //never returns more certain ids
	    if(channel==100) {LOG_INFO << "Str.=" << channel << "\tLay0\tgeoid=" << geoId<< "\tposition=" << position << endl;}
	  }  else   {
	    strip->setCoordNum( coordNum );  // map X into 0-127
	    if(channel==50) LOG_INFO << "Str.=" << channel << "\tLay0\tgeoid=" << geoId<< "\tposition=" << position << endl;
	  }
	  strip->setAdc( adc, timebin );
	  strip->setCharge( adc ); // was done in separate maker for FGT (StFgtA2CMaker), assume gain=1 for now
	  strip->setChargeUncert( sqrt(adc) ); // was done in separate maker for FGT (StFgtA2CMaker), assume gain=1 for now
	  strip->setGeoId( geoId );
	  strip->setModule( moduleIdx );
	  strip->setIsY( layer );
	  strip->setPosition( position );
	  strip->setElecCoords( rdo, arm, apv, channel );
	  if (Debug() > 2) {
	    mAdcTimeBins[layer][moduleIdx]->Fill(timebin, position, adc);
	  }
	}
      } else { LOG_WARN << "StGmtRawMaker::Make() -- Could not access module " << moduleIdx << endm; }
    }
    if (count) {
      ok = kStOK;
      if (Debug() > 3) {
	for (UShort_t module = 0; module < kGmtNumModules; module++) {
	  StGmtStripCollection *stripCollection = mGmtCollection->getStripCollection( moduleIdx );
	  if (! stripCollection) continue;
	  cout << "Module\t" << module << endl;
	  stripCollection->Print("");
	}
      }
    }
  }
  return ok;
}
//________________________________________________________________________________
Double_t StGmtRawMaker::fpeaks(Double_t *x, Double_t *par) {
  Float_t result=0.0;
  UInt_t nPar=(UInt_t)par[0];
  for (UInt_t p = 0; p < nPar; p++) {
    Double_t norm  = TMath::Exp(par[3*p+1]);
    Double_t mean  = par[3*p+2];
    Double_t sigma = par[3*p+3];
    result += norm*MyGaus(x[0],mean,sigma,0.08); //norm*TMath::Gaus(x[0],mean,sigma,1);
  }
  return result;
}
//________________________________________________________________________________
TF1* StGmtRawMaker::FindPeaks(TH1D* hist) {
  TSpectrum spect(MAX_PEAKS);
  TF1 back("poly","pol0",CLUS_MIN,CLUS_MAX);
  Double_t par[MAX_PEAKS*3+1];
  spect.Search(hist, 2, "", 0.20);
#if  ROOT_VERSION_CODE < 395523
  Float_t* xpeaks=spect.GetPositionX();
  //  Float_t* ypeaks=spect.GetPositionY();
#else
  Double_t* xpeaks=spect.GetPositionX();
  //  Double_t* ypeaks=spect.GetPositionY();
#endif
  hist->Fit(&back,"Q");
  UInt_t npx=0;
  UInt_t nfound = spect.GetNPeaks();
  for(UInt_t i=0; i < nfound; i++) {
    Double_t xp=xpeaks[i];
    Int_t bin=hist->GetXaxis()->FindBin(xp);
    Double_t yp=hist->GetBinContent(bin);
    Double_t err=hist->GetBinError(bin);
    if(err<=0.0) continue;
    if(bin<=1) continue;
    if((yp-err*3) < back.GetParameter(0)) continue;
    Double_t yp_left=hist->GetBinContent(bin-1);
    Double_t yp_right=hist->GetBinContent(bin+1);
    Double_t err_left=hist->GetBinError(bin-1);
    Double_t err_right=hist->GetBinError(bin+1);
    Double_t yp_sum=yp+yp_left+yp_right;
    Double_t err_sum=TMath::Sqrt(err*err+err_left*err_left+err_right*err_right);
    if((yp_sum-3*err_sum) < back.GetParameter(0)) continue;
    
    par[3*npx+1]=TMath::Log(yp);
    par[3*npx+2]=xp;
    par[3*npx+3]=kGmtXPitch; // sigma
    npx++;
  }
  if (Debug()) {LOG_INFO << hist->GetName() << " found " << nfound << " Accpeted " << npx << endm;}
  if (! npx) return 0;
  
  TString funcName=Form("Func%s_%i",hist->GetName(),npx);
  TF1* fitFunc = (TF1*)gROOT->GetListOfFunctions()->FindObject(funcName);
  if (fitFunc) {delete fitFunc;}
  fitFunc = new TF1(funcName,fpeaks,CLUS_MIN,CLUS_MAX,3*npx+1);
  fitFunc->SetParName(0,"nPeaks");
  for(UInt_t i=0; i < npx; i++) {
    fitFunc->SetParName(3*i+1,Form("logNorm_{%i}",i));  
    fitFunc->SetParName(3*i+2,Form("#mu_{%i}",i));  
    fitFunc->SetParLimits(3*i+2,par[3*i+2]-2*kGmtXPitch,par[3*i+2]+2*kGmtXPitch);
    fitFunc->SetParName(3*i+3,Form("#sigma_{%i}",i));  
    fitFunc->SetParLimits(3*i+3,kGmtXPitch*0.1,kGmtXPitch*10);
  }
  fitFunc->SetParameters(par);
  fitFunc->FixParameter(0,(double)npx);
  fitFunc->SetNpx(1000);
  fitFunc->SetLineColor(kGreen);
  
  TVirtualFitter::SetDefaultFitter("Fumili");
  int isOk=hist->Fit(fitFunc);
  if(isOk) isOk=hist->Fit(fitFunc);
  if(isOk) return 0;
  
  return fitFunc;
}
//________________________________________________________________________________
Int_t  StGmtRawMaker::ClusterBuilder(ULong_t events, UInt_t module, StGmtHitCollection& hits) {
  static TCanvas* canv=0;
  static TCanvas* canvAdc=0;
  static TH1D* histXY[2][8] = {0};
  static TH1D dhistXY[2][8];
  static const Char_t *XY[2] = {"X", "Y"};
  
  StGmtStrip* pStrip;
  Float_t position;
  StGmtStripCollection *strips = mGmtCollection->getStripCollection(module);
  if (! strips) return 0;
  if(Debug()) {
    LOG_INFO << "Cluster " << strips->getNumStrips() << "strips\tin module" << strips->getModule() << endm;
  }
  UInt_t stripsNum = strips->getNumStrips();
  Float_t adc, adcRMS;
  TSpectrum spectX(MAX_PEAKS); TSpectrum spectY(MAX_PEAKS);
  if(Debug() > 1) {
    canv = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("GmtClusters");
    if(!canv) canv=new TCanvas("GmtClusters","GmtClusters",800,1200);
    else      canv->Clear();
    if (Debug() > 2) {
      canvAdc = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("GmtTimeStrip");
      if(!canvAdc) canvAdc=new TCanvas("GmtTimeStrip","GmtTimeStrip",800,100,800,600);
      else      canvAdc->Clear();
    }
  }
  UInt_t nClusXY[2] = {0};
  TF1 *fitXY[2] = {0};
  UInt_t idXY[2][MAX_PEAKS] = {0};
  for (Int_t ixy = 0; ixy < 2; ixy++) {
    TString name(Form("Cluster%s_%i",XY[ixy],module));
    if(!histXY[ixy][module]) {histXY[ixy][module] = new TH1D(name,name,CLUS_BINS,CLUS_MIN,CLUS_MAX); histXY[ixy][module]->SetDirectory(0);}
    else                      histXY[ixy][module]->Reset();
    for(UInt_t iStrip = 0; iStrip < stripsNum; iStrip++) {
      pStrip = strips->getSortedStrip(iStrip);
      if (pStrip->isY() != ixy) continue;
      adc = pStrip->getAdcSum();
      adcRMS = pStrip->getAdcSumRMS();
      if (adc <= 0) continue;
      position = pStrip->getPosition();
      if (position < -990) continue;
      Int_t bin = histXY[ixy][module]->Fill(position,adc);
      histXY[ixy][module]->SetBinError(bin,adcRMS);
    }
    if (events >= 0) {
      dhistXY[ixy][module] = *histXY[ixy][module];
      dhistXY[ixy][module].SetName(Form("D%s",histXY[ixy][module]->GetName()));
      dhistXY[ixy][module].Add(mPedestalXY[ixy][module],-1.0); 
      fitXY[ixy] = FindPeaks(&dhistXY[ixy][module]); 
      if(fitXY[ixy]) {
	for(UInt_t i = 0; i < fitXY[ixy]->GetParameter(0); i++) {
	  if (fitXY[ixy]->GetParameter(3*i+3) >= 5*kGmtXPitch) continue;
	  if (fitXY[ixy]->GetParameter(3*i+1) <  5.0) continue;
	  idXY[ixy][nClusXY[ixy]]  =  i;
	  nClusXY[ixy]++;
#if 1
	  // clean peak position
	  Double_t x1 = fitXY[ixy]->GetParameter(3*i+2) - 3*fitXY[ixy]->GetParameter(3*i+3);
	  Double_t x2 = fitXY[ixy]->GetParameter(3*i+2) + 3*fitXY[ixy]->GetParameter(3*i+3);
	  Int_t ix1 = histXY[ixy][module]->GetXaxis()->FindBin(x1);
	  Int_t ix2 = histXY[ixy][module]->GetXaxis()->FindBin(x2);
	  for (Int_t ix = ix1; ix <= ix2; ix++) {
	    histXY[ixy][module]->SetBinContent(ix,0);
	  }
#endif
	}
	if (Debug()) {
	  LOG_INFO << "######" << XY[ixy] << " peaks found  = " << fitXY[ixy]->GetParameter(0) << ", Clusters fitted  = " << nClusXY[ixy] << endm;}
      } 
    }
  }
  for(UInt_t i = 0; i < nClusXY[0]; i++) {
    UInt_t nx = idXY[0][i];
    for(UInt_t j = 0; j < nClusXY[1]; j++) {
      UInt_t ny = idXY[1][j];
      StGmtHit* newCluster = new StGmtHit(
					  hits.getHitVec().size(),
					  module, 
					  TMath::Exp(fitXY[0]->GetParameter(3*nx+1)), // adcX
					  TMath::Exp(fitXY[1]->GetParameter(3*ny+1)), // adcY
					  fitXY[0]->GetParError(3*nx+1),              // error(adcX)
					  fitXY[1]->GetParError(3*ny+1),              // error(adcY)
					  fitXY[0]->GetParameter(3*nx+2), // meanX
					  fitXY[1]->GetParameter(3*ny+2), // meanY
					  fitXY[0]->GetParError(3*nx+2),  // error(meanX)
					  fitXY[1]->GetParError(3*ny+2),  // error(meanY)
					  fitXY[0]->GetParameter(3*nx+3), // sigmaX
					  fitXY[1]->GetParameter(3*ny+3), // sigmaY
					  fitXY[0]->GetParError(3*nx+3),  // error(sigmaX)
					  fitXY[1]->GetParError(3*ny+3)); // error(sigmaY)
      if (Debug()) newCluster->Print();
      hits.getHitVec().push_back(newCluster);
    }
  }
      
  if (Debug() > 1) {
    canv->Clear();
    canv->Divide(2,4);
    if (canvAdc) {
      canvAdc->Clear();
      canvAdc->Divide(2,1);
    }
    if (nClusXY[0] + nClusXY[1] > 0) {
      for (Int_t ixy = 0; ixy < 2 ; ixy++) {
	if (nClusXY[ixy]) {
	  canv->cd(ixy+1);
	  mPedestalXY[ixy][module]->Draw();
	  canv->cd(ixy+3);
	  dhistXY[ixy][module].Draw();
	}
      }	
      canv->Modified();
      canv->Update();
      if (canvAdc) {
	for (Int_t ixy = 0; ixy < 2 ; ixy++) {
	  canvAdc->cd(ixy+1);
	  mAdcTimeBins[ixy][module]->Draw("colz");
	  canvAdc->Modified();
	  canvAdc->Update();
	}
      }
      static Int_t ibreak = 0;
      ibreak++;
    }
    //      return 1;
  }
  for (Int_t ixy = 0; ixy < 2; ixy++) AddPed(histXY[ixy][module],mPedestalXY[ixy][module]);   
  if (Debug() > 1) {
    for (Int_t ixy = 0; ixy < 2 ; ixy++) {
      canv->cd(ixy+5);
      mPedestalXY[ixy][module]->Draw();
      canv->cd(ixy+7);
      histXY[ixy][module]->Draw();
    }
    canv->Modified();
    canv->Update();
    static Int_t ibreak = 0;
    ibreak++;
  }
  return 1;
}
//________________________________________________________________________________
void StGmtRawMaker::AddPed(TH1 *hist, TProfile *Pedestal) {
  TAxis *xax = hist->GetXaxis();
  Int_t nx = xax->GetNbins();
  for (Int_t i = 1; i <= nx; i++) {
    if (hist->GetBinContent(i) <= 0.0) continue;
    if (hist->GetBinContent(i) > 100000.0) continue;
    Pedestal->Fill(xax->GetBinCenter(i), hist->GetBinContent(i));
  }
}
