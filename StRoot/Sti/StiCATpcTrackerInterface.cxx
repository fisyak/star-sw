#include <algorithm>
#include "StiCATpcTrackerInterface.h"
#include "TPCCATracker/AliHLTTPCCAGBHit.h"
#include "TPCCATracker/AliHLTTPCCAGBTrack.h"
#include "TPCCATracker/AliHLTTPCCAParam.h"
// need for hits data
#include "StMaker.h"
#include "StMessMgr.h"
#include "StTpcHit.h"                
#include "StTpcDb/StTpcDb.h"
#include "StDbUtilities/StTpcCoordinateTransform.hh"
#include "StDbUtilities/StTpcLocalSectorCoordinate.hh"
// for MCdata
#include "tables/St_g2t_track_Table.h" 
#include "tables/St_g2t_tpc_hit_Table.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TString.h"
#include "TPolyMarker.h"
#include "TDatabasePDG.h"
#include "TEnv.h"
#include "TLegend.h"
#include "THStack.h"
#include "StDetectorDbMaker/St_tpcT0BXC.h"
#include "StDetectorDbMaker/St_beamInfoC.h"
#include "StEvent/StTriggerData.h"
#include "StEvent/StDcaGeometry.h"
#include "Sti/StiKalmanTrackNode.h"
#include "StEvent/StEnumerations.h"
#include "StEvent/StEvent.h"
#include "StEvent/StEventSummary.h"
//to get Magnetic Field
#include "StarMagField/StarMagField.h"
#include "TStopwatch.h"
#include <vector>
#include <algorithm>
#include "KFParticle/KFParticle.h"
#include "KFParticle/KFPTrack.h"
#include "KFParticle/KFParticleSIMD.h"
#include "KFParticle/KFParticleTopoReconstructor.h"
#include "KFParticle/KFParticlePVReconstructor.h"
#include "TRMatrix.h"
#include "TRVector.h"
using std::vector;
StiCATpcTrackerInterface *StiCATpcTrackerInterface::fgStiCATpcTrackerInterface = 0;
Bool_t StiCATpcTrackerInterface::fgUseCAVxFinder = kFALSE;
static Int_t _debug = 0;
#define PrPP(B)  if (_debug)   {cout << (#B) << " = \t" << (B) << endl;}
#define PrPP2(B)  if (_debug)   {cout << (#B) << " = \t" << (*B) << endl;}
#define PrPP3(A,B)  if (_debug)   {cout << (#A) << " = \t" << (A) << "\t" << (#B) << " = \t" << (B) << endl;}
#define PrPP4(A,B)  if (_debug)   {cout << (#A) << " = \t" << (A) << "\t" << (#B) << " = \t" << (*B) << endl;}
//Double_t StiCATpcTrackerInterface::fgzFXT =  199.983; // xyzW_z Fit 3p85GeV_fixedTarget_2019P6; 199.63; // RF/TFG/3p85GeV_fixedTarget_2019B/MuL4Vx.root
Double_t StiCATpcTrackerInterface::fgzFXT =  199.9875; // = (200. - 0.025/2);
//________________________________________________________________________________
StiCATpcTrackerInterface &StiCATpcTrackerInterface::Instance() {
  if (! fgStiCATpcTrackerInterface) fgStiCATpcTrackerInterface = new StiCATpcTrackerInterface(); 
  fgUseCAVxFinder = gEnv->GetValue("UseCAVxFinder", 0);
  return *fgStiCATpcTrackerInterface;
}
//________________________________________________________________________________
void StiCATpcTrackerInterface::SetNewEvent() {
  fSeedFinder = 0; 
  fSeeds.clear(); 
  fSeedHits.clear(); 
  fHitsMap = 0; 
  StTPCCAInterface::SetNewEvent();
  if (! fgUseCAVxFinder) return;
  if (! fSpectrum) {
    TFile *f = 0;
    if (StMaker::GetTopChain()) {
      f = StMaker::GetTopChain()->GetTFile();
      if (f) f->cd();
    }
    Int_t NzBins = 2500;
    Int_t npeaks = 250;
    Double_t zmin = -250;
    Double_t zmax = 250;
    const Char_t *side[5] = {"East","West","All","EastX","WestX"};
    for (Int_t i = 0; i < 5; i++) {
      if (i > 2) {
	if (fVertexZPlots[i]) {
	  fVertexZPlots[i]->Reset();
	} else {
	  fVertexZPlots[i] = new TH1F(Form("VertexZPlot%s",side[i]),Form("z-dca from KFParticle - <Z>  distribution for side = %s",side[i]),400,-20,20);
	  fVertexZPlots[i]->SetDirectory(f);
	  fVertexZPlots[i]->SetMarkerColor(i-1); 
	  fVertexZPlots[i]->SetLineColor(i-1); 
	  fVertexZPlots[i]->SetLineWidth(4);
	}
	continue;
      }
      if (fVertexZPlots[i]) {
	fVertexZPlots[i]->Reset();
      } else {
	fVertexZPlots[i] = new TH1F(Form("VertexZPlot%s",side[i]),Form("z-dca distribution for side = %s",side[i]),NzBins,zmin,zmax);
	fVertexZPlots[i]->SetDirectory(f);
      }
      if (fVertexXYPlots[i]) {
	fVertexXYPlots[i]->Reset();
      } else {
	fVertexXYPlots[i] = new TH2F(Form("VertexXYPlot%s",side[i]),Form("xy-dca distribution for side = %s at Z +/- 10 cm of the 1st peak",side[i]),100,-5,5,100,-5,5);
	fVertexXYPlots[i]->SetDirectory(f);
      }
      if (i != 2) {
	fVertexZPlots[i]->SetMarkerColor(i+2); 
	fVertexZPlots[i]->SetLineColor(i+2); 
	fVertexZPlots[i]->SetLineWidth(4);
	fVertexXYPlots[i]->SetMarkerColor(i+2); 
	fVertexXYPlots[i]->SetLineColor(i+2); 
	fVertexXYPlots[i]->SetLineWidth(4);
      }
    }
    fSpectrum = new TSpectrum(npeaks);
  } else {
    for (Int_t i = 0; i < 5; i++) {
      fVertexZPlots[i]->Reset();  fVertexZPlots[i]->GetXaxis()->SetRange(0,-1);
      if (i > 2) continue;
      fVertexXYPlots[i]->Reset();
    }
  }

  //  StiKalmanTrackNode::SetExternalTriggerOffset(0);
}
//________________________________________________________________________________
void StiCATpcTrackerInterface::MakeHits() {
  for (HitMapToVectorAndEndType::iterator it= fHitsMap->begin(); it!= fHitsMap->end(); ++it){
    vector<StiHit*>& tempvec = (*it).second.hits();
    vector<StiHit*>::iterator  start = tempvec.begin();
    vector<StiHit*>::iterator  stop  = tempvec.end();
    for (vector<StiHit*>::iterator cit = start; cit != stop; cit++) {

        // get local coordinates. take into account distortion
      StiHit *hit = *cit;
      if (! hit->stHit()) 	continue;
      //yf      if (  hit->timesUsed()) 	continue;//VP
      
      const StTpcHit *tpcHit = dynamic_cast<const StTpcHit*>(hit->stHit());
      if ( ! tpcHit) continue;
      Int_t Id = fSeedHits.size();
      StGlobalCoordinate glob(tpcHit->position());
      //      tran(glob,loc,tpcHit->sector(),tpcHit->padrow());
      Int_t sector = tpcHit->sector();
      //      Double_t beta = (sector <= 12) ? (60 - 30*(sector - 1)) : (120 + 30 *(sector - 13));
      Double_t beta = fCaParam[sector-1].Alpha();
      Double_t cb   = TMath::Cos(beta);
      Double_t sb   = TMath::Sin(beta);
      
      // obtain seed Hit
      SeedHit_t hitc;
      hitc.padrow = tpcHit->padrow()-1;
      Double_t xL =  cb*glob.position().x() + sb*glob.position().y();
      Double_t yL = -sb*glob.position().x() + cb*glob.position().y();
      Double_t zL =                              glob.position().z();
      hitc.x = xL;
      hitc.y = yL;
      hitc.z = zL;
      hitc.status=0;
      hitc.taken=0;
      hitc.track_key=tpcHit->idTruth();
      hitc.hit  = hit;
      fSeedHits.push_back(hitc);

      // convert to CA Hit
      AliHLTTPCCAGBHit caHit;
//      caHit.SetX( hit->x() );
      caHit.SetX(   xL ); // take position of the row
      caHit.SetY( - yL );
      caHit.SetZ( - zL );
        // caHit.SetErrX(   );
      caHit.SetErrY( 0.12 );// TODO: read parameters from somewhere 
      caHit.SetErrZ( 0.16 );
      caHit.SetISlice( tpcHit->sector() - 1 );
      caHit.SetIRow( hitc.padrow );
      //      caHit.SetID( fCaHits.size() );
      caHit.SetID( Id );
      fIdTruth.push_back( hitc.track_key );

      fCaHits.push_back(caHit);
    }
  }

} // void StiCATpcTrackerInterface::MakeHits()
//________________________________________________________________________________
void StiCATpcTrackerInterface::ConvertPars(const AliHLTTPCCATrackParam& caPar, double _alpha, StiNodePars& nodePars, StiNodeErrs& nodeErrs)
{
  // set jacobian integral coef
  //                      y   z eta ptin tanl  
  static Double_t JI[5] {-1, -1, -1,   1, -1};
    // get parameters
  nodePars.x()    =         caPar.GetX();
  nodePars.y()    = JI[0] * caPar.GetY();
  nodePars.z()    = JI[1] * caPar.GetZ();
  nodePars.eta()  = JI[2] * asin(caPar.GetSinPhi()); // (signed curvature)*(local Xc of helix axis - X current point on track)
  nodePars.ptin() = JI[3] * caPar.GetQPt();        // signed invert pt [sign = sign(-qB)]
  nodePars.tanl() = JI[4] * caPar.GetDzDs();         // tangent of the track momentum dip angle
  
    // get h & signB
  static const double EC = 2.99792458e-4, ZEROHZ = 2e-6;
// #define USE_CA_FIELD
#ifndef USE_CA_FIELD // use field in the point. Need this because of check in StiTrackNodeHelper::set()
  const double ca = cos(_alpha), sa = sin(_alpha); // code has been taken from StiKalmanTrackNode::getHz()
  double globalXYZ[3] = {
    ca * nodePars.x() - sa * nodePars.y(),
    sa * nodePars.x() + ca * nodePars.y(),
    nodePars.z()
  };

  double h2=ZEROHZ;
  if (! StiKalmanTrackNode::IsLaser()) {
    double b[3];
    StarMagField::Instance()->BField(globalXYZ,b);
    h2 = b[2];
  } 

#else  // these parameters have been obtained with that MF, so let's use it.
  double h2 = - fTracker->Slice(0).Param().Bz(); // change sign because change z
#endif // 1
  h2 *= EC;
  // get parameters. continue
  nodePars.hz() = h2;  // Z component magnetic field in units Pt(Gev) = Hz * RCurv(cm)
  nodePars.ready(); // set cosCA, sinCA & curv
  // set jacobian integral coef
  double J[5]; 
  J[0] = JI[0];                    // y
  J[1] = JI[1];                    // z
  J[2] = JI[2]/cos(nodePars.eta()); // eta
  J[3] = JI[3];                    // ptin
  J[4] = JI[4];                    // tanl
  
  // get cov matrises
  const float *caCov = caPar.GetCov();

  double *A = nodeErrs.G();
  
  nodeErrs._cYY = caCov[ 0];
  nodeErrs._cZY = caCov[ 1]*J[0]*J[1];
  nodeErrs._cZZ = caCov[ 2]*J[0]*J[1];
  nodeErrs._cEY = caCov[ 3]*J[0]*J[2];
  nodeErrs._cEZ = caCov[ 4]*J[1]*J[2];
  nodeErrs._cEE = caCov[ 5]*J[2]*J[2];
  nodeErrs._cTY = caCov[ 6]*J[0]*J[4];
  nodeErrs._cTZ = caCov[ 7]*J[1]*J[4];
  nodeErrs._cTE = caCov[ 8]*J[2]*J[4];    
  nodeErrs._cTT = caCov[ 9]*J[4]*J[4];
  nodeErrs._cPY = caCov[10]*J[0]*J[3];
  nodeErrs._cPZ = caCov[11]*J[1]*J[3];
  nodeErrs._cPE = caCov[12]*J[2]*J[3];
  nodeErrs._cTP = caCov[13]*J[4]*J[3];
  nodeErrs._cPP = caCov[14]*J[3]*J[3];

  A[0] = 1; // don't use parameter X
  A[1] = 0;
  A[3] = 0;
  A[6] = 0;
  A[10] = 0;
  A[15] = 0;
  if (_debug > 1) {
    cout << nodePars << endl;
  }
}
//________________________________________________________________________________
void StiCATpcTrackerInterface::MakeSeeds()
{
  // Save CA results
  const int NRecoTracks = fTracker->NTracks();
  if (fSpectrum) {
    TriggerOffSet();
  }
  for ( int iTr = 0; iTr < NRecoTracks; iTr++ ) {
    // get seed
    const AliHLTTPCCAGBTrack tr = fTracker->Track( iTr );
    Seed_t seed;
    
    const int NHits = tr.NHits();
    for ( int iHit = NHits-1; iHit >= 0; iHit-- ){ 
      const int index = fTracker->TrackHit( tr.FirstHitRef() + iHit );
      const int hId   = fTracker->Hit( index ).ID();
      seed.vhit.push_back(&(fSeedHits[hId]));
    }
    seed.total_hits = seed.vhit.size();
    Int_t sectorI = -1;
    Int_t sectorO = -1;
    Int_t lastRow = -1;
    for (auto  vhit : seed.vhit) {
      auto hit = vhit->hit;
      if (! hit) continue;
      StTpcHit  *sthit = (StTpcHit *) hit->stHit();
      if (! sthit) continue;
      Int_t sector = sthit->sector();
      Int_t row  = sthit->padrow();
      if (lastRow < 0) {sectorI = sectorO = sector;}
      else if (lastRow > row) {sectorI = sector;}
      else                    {sectorO = sector;}
      lastRow = row;
      if (_debug > 1) {
	sthit->Print();
      }
    }
    ConvertPars( tr.OuterParam(), tr.Alpha(), seed.firstNodePars, seed.firstNodeErrs);
    if (_debug > 1) {
      cout << "Outer: " << sectorO << "\t"; MakeParticle(tr.OuterParam(), tr.Alpha(), iTr+1).Print();
    }
    ConvertPars( tr.InnerParam(), tr.Alpha(), seed.lastNodePars,  seed.lastNodeErrs);
    if (_debug > 1) {
      cout << "Inner: " << sectorI << "\t"; MakeParticle(tr.InnerParam(), tr.Alpha(), iTr+1).Print();
    }
    fSeeds.push_back(seed);
  }
} // void StiCATpcTrackerInterface::MakeSeeds()
//________________________________________________________________________________
void StiCATpcTrackerInterface::getXYZ(const StiNodePars &pars, const StiNodeErrs &errs, const Float_t &alpha,  Float_t xyzp[6], Float_t CovXyzp[21]) const {
  //  static const Float_t one = 1; // rotate from local Tpc to global <<<<<<<<
  Double_t xyzp2[6], CovXyzp2[21];
  StiKalmanTrackNode::getXYZ(pars, errs, alpha, xyzp2, CovXyzp2);
  TCL::ucopy(xyzp2, xyzp, 6);
  TCL::ucopy(CovXyzp2, CovXyzp, 21);
}
//________________________________________________________________________________
KFParticle &StiCATpcTrackerInterface::MakeParticle(const AliHLTTPCCATrackParam &trParam, const Double_t &alpha, Int_t kg, Int_t pdg) { // init array of particles
  static KFParticle tempParticle;
  // get track params in local CS
  StiNodePars nodePars; 
  StiNodeErrs nodeErrs;
  ConvertPars(trParam, alpha, nodePars, nodeErrs);
  Int_t q = (nodePars.ptin() > 0) ? -1 : 1;
  Float_t xyzF[6];
  Float_t CovXyzF[21];
  getXYZ(nodePars, nodeErrs, alpha, xyzF, CovXyzF);
  Int_t PDG = pdg;
  if (! pdg) {
    PDG = q*211;
  }
  static KFPTrack track;
  track.SetParameters(xyzF);
  track.SetCovarianceMatrix(CovXyzF);
  track.SetNDF(1);
  track.SetCharge(q);
  tempParticle = KFParticle(track, PDG);
  tempParticle.SetPDG(PDG);
  tempParticle.SetId(kg);
  tempParticle.AddDaughterId(kg);
  tempParticle.Chi2() = trParam.Chi2();
  tempParticle.NDF()  = trParam.NDF();
  return tempParticle;
}
//________________________________________________________________________________
void StiCATpcTrackerInterface::MakeParticles(std::vector<trackInSector> Tracks, std::vector<int>* pdg, Int_t NDFcut, Double_t dpTcut) { // init array of particles
  fParticles.clear();
  // create and fill array of tracks to init KFParticleTopoReconstructor
  const int nTracks = Tracks.size(); // tracker->NTracks();
  for ( int iTr = 0; iTr < nTracks; iTr++ ) {
    AliHLTTPCCATrackParam &trParam = Tracks[ iTr ].Track;
    if (trParam.NDF() < NDFcut) continue;
    Double_t alpha = Tracks[ iTr ].alpha;
    KFParticle &tempParticle = MakeParticle(trParam, alpha, iTr+1);
    Float_t P, dP;
    tempParticle.GetMomentum(P,dP);
    if (dP/P > dpTcut) continue;
    //    PrPP(tempParticle);
    fParticles.push_back(tempParticle);
  }
} // void KFParticleTopoReconstructor::Init(std::vector<AliHLTTPCCATrackParam> tracks, std::vector<int>* pdg=0); // init array of particles
//________________________________________________________________________________
void StiCATpcTrackerInterface::TriggerOffSet() {// Estimate Interaction time wrt Trigger
  if (! gROOT->IsBatch()) {
    TCanvas *c1 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("UseCAVxFinder");
    if (c1) c1->Clear();
  }
  KFParticle::SetField(- fTracker->Slice(0).Param().Bz() );
  KFParticleSIMD::SetField(- fTracker->Slice(0).Param().Bz() );
  FindCAWEPrimaryVertices();
  StEvent* pEvent = (StEvent*) StMaker::GetChain()->GetInputDS("StEvent");
  StEventSummary *summary = pEvent->summary();
  Double_t DVoveC = StTpcDb::instance()->DriftVelocity()/TMath::Ccgs(); // cm/sec
  L4CAVertex *l4Vx[3] = {&summary->L4VxEast, &summary->L4VxWest, &summary->L4Vx};
  for (Int_t i = 0; i < 3; i++) {
    memset (&(l4Vx[i]->Const), 0, sizeof(L4CAVertex));
    TF1 *gaus = (TF1 *) fVertexZPlots[i]->GetListOfFunctions()->FindObject("gaus");
    if (! gaus) continue;
    l4Vx[i]->Const = gaus->GetParameter(0); l4Vx[i]->dConst = gaus->GetParError(0); 
    l4Vx[i]->Mu    = gaus->GetParameter(1); l4Vx[i]->dMu = gaus->GetParError(1); 
    l4Vx[i]->Sigma = gaus->GetParameter(2); l4Vx[i]->dSigma = gaus->GetParError(2); 
    l4Vx[i]->Chisq = gaus->GetChisquare();
    l4Vx[i]->Ndf   = gaus->GetNDF();
    l4Vx[i]->Prob  = gaus->GetProb();
    l4Vx[i]->X     = fVertexXYPlots[i]->GetMean(1);
    l4Vx[i]->Y     = fVertexXYPlots[i]->GetMean(2);
  }
  KFVertex *PV[2] = {&summary->KFVxEast, &summary->KFVxWest};
  if (l4Vx[2]->Ndf > 0) {
    vector<trackInSector> Tracks[2]  = { fTracker->GetLeft(), fTracker->GetRight()};
    for (UInt_t side = 0; side < 2; side++) {
      vector<trackInSector> tracks;
      for (UInt_t it = 0; it < Tracks[side].size(); it++) {
	if (TMath::Abs(l4Vx[side]->Mu +  Tracks[side][it].z) > 20) continue; // swap sign og Z for internal sector parameters
	tracks.push_back(Tracks[side][it]);
      }
      if (tracks.size() < 1) continue;
      PV[side]->Z() = l4Vx[side]->Mu;
      PrPP4(side,PV[side]);
      MakeParticles(tracks);
      UInt_t N = fParticles.size();
      if (!N) continue;
      KFParticle **parts = new KFParticle*[N];
      sort(fParticles.begin(), fParticles.end(), 
	   [](const KFParticle & a, const KFParticle & b)
	   { 
	     //	     return a.GetNDF() > b.GetNDF(); 
	     Float_t pta, dpta, ptb, dptb;
	     a.GetPt(pta,dpta);
	     b.GetPt(ptb,dptb);
	     return pta/dpta*a.NDF() > ptb/dptb*b.NDF();
	   });
      Int_t Np = 0;
      for (UInt_t i = 0; i < N; i++) {
	parts[Np] = &fParticles[i];
	// add time dependence
	if (_debug > 2) {cout << "Before "; PrPP2(parts[Np]);}
	Float_t dsdr[6] = {0};
	Float_t dS = parts[Np]->GetDStoPoint(&PV[side]->X(), dsdr);
	Double_t dZdS = 1./dsdr[2];
	static Double_t PiMass = TDatabasePDG::Instance()->GetParticle(211)->Mass();
	static Double_t PMass = TDatabasePDG::Instance()->GetParticle(2212)->Mass();
	Float_t P, dP;
	parts[Np]->GetMomentum(P,dP);
	Double_t bgPi = P/PiMass;
	Double_t bgP  = P/PMass;
	Double_t betaPi = bgPi/TMath::Sqrt(1 + bgPi*bgPi); 
	Double_t betaP  = bgP /TMath::Sqrt(1 + bgP *bgP ); 
        Double_t ss = 1. - 2.*side; // flip sign because dS < 0
	Float_t  zPi   = parts[Np]->GetZ()  + ss*dS*DVoveC/betaPi;
	Float_t  zP    = parts[Np]->GetZ()  + ss*dS*DVoveC/betaP ;
        Float_t  pzPi  = parts[Np]->GetPz() - ss*P *DVoveC/betaPi;
        Float_t  pzP   = parts[Np]->GetPz() - ss*P *DVoveC/betaP ;
	if (_debug > 2) {
	  cout << "dS = " << dS << "\tdZdS = " << dZdS 
	       << "\tzPi = " << zPi << "\tpZPi = " << pzPi
	       << "\tzP  = " << zP  << "\tpZP  = " << pzP  << endl;
	  cout << "ToF   "; PrPP2(parts[Np]);
	}
	parts[Np]->Z()  = zPi ;
	parts[Np]->Pz() = pzPi;
	Float_t dSnew = parts[Np]->GetDStoPoint(&PV[side]->X(), dsdr);
	if (_debug > 1) {cout << "dSnew = " << dSnew << endl;}
	parts[Np]->TransportToDS( dSnew, dsdr );
	if (_debug > 1) {cout << "After  "; PrPP2(parts[Np]);}
	Double_t dX = parts[Np]->GetX() -  PV[side]->GetX();
	Double_t dY = parts[Np]->GetY() -  PV[side]->GetY();
	Double_t dZ = parts[Np]->GetZ() -  PV[side]->GetZ();
	Double_t dR = TMath::Sqrt(dX*dX + dY*dY);
	if (TMath::Abs(dZ) > 20) continue;
	if (           dR  >  5) continue;
	Np++;
      }
      if (Np < 2) continue;
      TF1 *gaus = DrawKFWEPrimaryVertices(side);
      if (! gaus) continue;
      PV[side]->Z() = gaus->GetParameter(1) + fgzFXT;
      static Double_t Chi2Cut = 10.0;
      TArrayC Flag(N);
      PV[side]->ConstructPrimaryVertex((const KFParticle **) parts, Np, 
				      (Bool_t*) Flag.GetArray(), Chi2Cut/2);
      PrPP4(side,PV[side]);
    }
    DrawKFWEPrimaryVertices(-1, PV);
  }
  // Trigger stuff
  Int_t NoTrigDet = 0;
  enum {kvpd = 0, kbbc, kepd, kzdc, kTAC, kCAV, kZwKFXT, kTrgTotal};
  Double_t trgV[kTrgTotal][2] = {0};
  Double_t trgSum[kTrgTotal] = {0};
  StTriggerData *trigger = pEvent->triggerData();
  if (trigger) {
    trgV[kvpd][east] = trigger->vpdEarliestTDC(east); trgV[kvpd][west] = trigger->vpdEarliestTDC(west);
    trgV[kbbc][east] = trigger->bbcEarliestTDC(east); trgV[kbbc][west] = trigger->bbcEarliestTDC(west);
    trgV[kepd][east] = trigger->epdEarliestTDC(east); trgV[kepd][west] = trigger->epdEarliestTDC(west);
    trgV[kzdc][east] = trigger->zdcEarliestTDC(east); trgV[kzdc][west] = trigger->zdcEarliestTDC(west);
    trgV[kTAC][east] =                            -1; trgV[kTAC][west] =                            -1;
    for (Int_t k = 0; k < kCAV; k++) {
      trgSum[k] = -1;
      if (trgV[k][east] > 0 && trgV[k][west] > 0) {
	trgSum[k] = 0.5*(  trgV[k][east] + trgV[k][west]); NoTrigDet++;
      } else if (trgV[k][east] > 0) {
	trgSum[k] = trgV[k][east]; NoTrigDet++;
      } else if (trgV[k][west] > 0) {
	trgSum[k] = trgV[k][west]; NoTrigDet++;
      }
    }
    // CA
    //  L4CAVertex &L4Vx = summary->L4Vx;
    L4CAVertex &L4VxWest = summary->L4VxWest;
    L4CAVertex &L4VxEast = summary->L4VxEast;
    trgSum[kCAV] = -1e9;
    Double_t driftVel = StTpcDb::instance()->DriftVelocity()*1e-6;
    Double_t dCAVz[2] = { L4VxEast.dMu,  L4VxWest.dMu};
    if (dCAVz[0] < 1e-7 || dCAVz[0] > 0.3) dCAVz[0] = -1e9;
    if (dCAVz[1] < 1e-7 || dCAVz[1] > 0.3) dCAVz[1] = -1e9;
    if (dCAVz[0] > 0 && dCAVz[1] > 0) {
      trgV[kCAV][east] =                   L4VxEast.Mu; trgV[kCAV][west] =                   L4VxWest.Mu;
      trgSum[kCAV] = 0.5*(- trgV[kCAV][east] + trgV[kCAV][west])/driftVel; // in usec, for CAV use difference instead of sum
      NoTrigDet++;
    }
    // KF CA
    KFVertex &PVkfW = summary->KFVxWest; PrPP(PVkfW);
    if (PVkfW.GetNDF() > 10) {
      Double_t dZ = PVkfW.GetZ() - fgzFXT;
      Double_t ddZ = TMath::Sqrt(PVkfW.GetCovariance(2,2));
      if (ddZ > 0 && ddZ < 1.0) { //0.5 && TMath::Abs(dZ/ddZ) > 1.0) {
	trgSum[kZwKFXT] = dZ/driftVel;
	NoTrigDet++;
      }
    }
    if (NoTrigDet) {
      Double_t T0 = - St_tpcT0BXC::instance()->getT0(trgSum);
      StiKalmanTrackNode::SetExternalTriggerOffset(T0);
    } else {
      StiKalmanTrackNode::SetExternalTriggerOffset(0);
    }
  }
}
//________________________________________________________________________________
void StiCATpcTrackerInterface::FindCAWEPrimaryVertices() {
  if (fSpectrum) {
    // --- DCA test ---
    std::cout<<" ------- FindTracks - done - dca test -------\n";
    auto dca_left = fTracker->GetLeft();	// dca_right, GetRight
    //    std::cout<<" - sca_left.size: "<<dca_left.size()<<"\n";
    for( UInt_t i = 0; i < dca_left.size(); i++ ) {
      if (_debug > 1) {
	std::cout<<"left  - > i: "<<i << "\t" << dca_left[i] << std::endl;
      }
      if (TMath::Sqrt(dca_left[i].x*dca_left[i].x + dca_left[i].y*dca_left[i].y) > 4.0) continue;
      FillZHist(fVertexZPlots[0],-dca_left[i].z, fSigmaSmooth);
      FillZHist(fVertexZPlots[2],-dca_left[i].z, fSigmaSmooth);
    }
    auto dca_right = fTracker->GetRight();
    if (_debug > 1) {
      std::cout<<" - sca_right.size: "<<dca_right.size()<<"\n";
    }
    for( UInt_t i = 0; i < dca_right.size(); i++ ) {
      if (_debug > 1) {
	std::cout<<"right - > i: "<<i << "\t" << dca_right[i] << std::endl;
      }
      if (TMath::Sqrt(dca_right[i].x*dca_right[i].x + dca_right[i].y*dca_right[i].y) > 4.0) continue;
      FillZHist(fVertexZPlots[1],-dca_right[i].z, fSigmaSmooth);
      FillZHist(fVertexZPlots[2],-dca_right[i].z, fSigmaSmooth);
    }
    // --- Find Z of primary vertex
    TString opt("new");
    TCanvas *c1 = 0;
    if (gROOT->IsBatch())  opt = "goff";
    else {
      c1 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("UseCAVxFinder");
      if (c1) c1->Clear();
      else  c1 = new TCanvas("UseCAVxFinder","Fit results for Vertex Z from All, only West and Only East CA racks", 100,100,1000,600);
    }
    Double_t zmax =  250;
    Double_t zmin = -250;
    if ( St_beamInfoC::instance()->IsFixedTarget()) {
      zmax = 220;
      zmin = 180;
    }
    for (Int_t i = 2; i >= 0; i--) {
      if (c1) c1->Clear();
      Int_t nfound = fSpectrum->Search(fVertexZPlots[i],-1,opt,0.1); //TMath::Min(0.1,5./nAccepted));
      if (nfound > 0) {
	LOG_INFO << "Found in " << fVertexZPlots[i]->GetName() << "\t" << nfound  << " peaks" << endm;
	Double_t *zOfPeaks = new Double_t[nfound];
	Int_t npeaks = 0;
#if  ROOT_VERSION_CODE < 395523
	Float_t *xpeaks = fSpectrum->GetPositionX();
	Float_t xp = 0;
#else
	Double_t *xpeaks = fSpectrum->GetPositionX();
	Double_t xp = 0;
#endif
	for (Int_t p = 0; p < nfound; p++) {
	  xp = xpeaks[p];
	  Int_t bin = fVertexZPlots[i]->GetXaxis()->FindBin(xp);
	  Double_t yp = fVertexZPlots[i]->GetBinContent(bin);
	  Double_t ep = fVertexZPlots[i]->GetBinError(bin);
	  if (xp < zmin || xp > zmax) continue;
	  if (yp-1.25*ep < 0) continue;
	  zOfPeaks[npeaks] = xp;
	  LOG_INFO << "z = " << xp << " with " << yp << " +/- " << ep << endm;
	  npeaks++;
	}
	if (npeaks > 0) {
	  Double_t rms = fVertexZPlots[i]->GetRMS();
	  if (rms > 3) rms = 3;
	  fVertexZPlots[i]->Fit("gaus","er","",zOfPeaks[0]-3*rms,zOfPeaks[0]+3*rms);
	  TF1 *gaus = (TF1 *) fVertexZPlots[i]->GetListOfFunctions()->FindObject("gaus");
	  if (gaus) {
	    if (i == 2) gaus->SetLineColor(1);
	    else        gaus->SetLineColor(2+i);
	    Double_t mu = gaus->GetParameter(1);
	    Double_t sigma = gaus->GetParameter(2);
	    fVertexZPlots[i]->Fit(gaus,"er","",mu-3*sigma,mu+3*sigma);
	    if (c1) {
	      fVertexZPlots[i]->Draw();
	      c1->Update();
	      TPaveStats *ps2 = (TPaveStats*)fVertexZPlots[i]->GetListOfFunctions()->FindObject("stats");
	      if (ps2) {
		if (i < 2) ps2->SetTextColor(2+i);
		ps2->SetX1NDC(0.1+0.2*i); ps2->SetX2NDC(0.3+0.2*i);
		ps2->SetY1NDC(0.70); ps2->SetY2NDC(0.90);
	      }
	    }
	    mu = gaus->GetParameter(1);
	    sigma = gaus->GetParameter(2);
	    if (i == 0 || i == 2) {
	      for( UInt_t j = 0; j < dca_left.size(); j++ ) {
		Double_t z = -dca_left[j].z;
		if (TMath::Abs(z - mu) < 3*sigma) {
		  fVertexXYPlots[i]->Fill(dca_left[j].x,dca_left[j].y);
		}
	      }
	    }
	    if (i == 1 || i == 2) {
	      for( UInt_t j = 0; j < dca_right.size(); j++ ) {
		Double_t z = -dca_right[j].z;
		if (TMath::Abs(z - mu) < 3*sigma) {
		  fVertexXYPlots[i]->Fill(dca_right[j].x,dca_right[j].y);
		}
	      }
	    }
	  }
	}
      }
    }
    if (c1) {
      fVertexZPlots[2]->Draw();
      fVertexZPlots[0]->Draw("][sames");
      fVertexZPlots[1]->Draw("][sames");
      c1->Update();
    }
  } // end of CA Vertex
}
//________________________________________________________________________________
TF1 *StiCATpcTrackerInterface::DrawKFWEPrimaryVertices(Int_t side, KFVertex **PV) {
  TF1 *gausF = 0;
  if (! fSpectrum) return gausF;
  TCanvas *c1 = 0;
  TString opt("new");
  if (gROOT->IsBatch())  opt = "goff";
  else {
    c1 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("UseKFVxFinder");
    if (c1) c1->Clear();
    else  c1 = new TCanvas("UseKFVxFinder","Fit results for Vertex Z from All, only West and Only East KF racks", 100,800,1000,600);
  }
  if (side < 0 || side > 1) {
    if (c1) {
      static THStack *stack = 0;
      SafeDelete(stack);
      stack = new THStack("stack","CA KFVertex results");
      static TLegend *lwe[2] = {0};
      SafeDelete(lwe[0]);
      SafeDelete(lwe[1]);
      Double_t PositionX = 0, PositionY = 1; 
      TString same;
      for (Int_t k = 0; k < 2; k++) {
	Int_t side = 1 - k;
	PositionX = PV[side]->GetZ() - fgzFXT;
	TPolyMarker *pm = new TPolyMarker(1, &PositionX, &PositionY);
	fVertexZPlots[3+side]->GetListOfFunctions()->Add(pm);
	pm->SetMarkerStyle(20);
	pm->SetMarkerColor(2+side);
	pm->SetMarkerSize(1.5);
	//	fVertexZPlots[3+k]->Draw(same); 
	stack->Add(fVertexZPlots[3+k],same);
	same = "[]sames";
	lwe[side] = new TLegend(0.1 + 0.5*side, 0.6,  0.3 + 0.5*side, 0.7);
	lwe[side]->AddEntry(pm,Form("z = %7.3f +/- %5.3f %6.2f/%3i", 
				    PV[side]->GetZ() - fgzFXT, 
				    TMath::Sqrt(PV[side]->GetCovariance(2,2)),
				    PV[side]->GetChi2(),PV[side]->NDF()));
      }
      //      c1->Update();
      stack->Draw();
      lwe[0]->Draw();
      lwe[1]->Draw();
      c1->Update();
      return gausF;
    }
  }
  for (auto particle : fParticles) {
    FillZHist(fVertexZPlots[3+side], particle.GetZ() - fgzFXT, TMath::Sqrt(particle.GetCovariance(5)));
  }
  // --- Find Z of primary vertex
  Double_t zmax =  20;
  Double_t zmin = -20;
  Int_t i = 3 + side;
  if (c1) c1->Clear();
  Int_t nfound = fSpectrum->Search(fVertexZPlots[i],-1,opt,0.1); //TMath::Min(0.1,5./nAccepted));
  if (nfound > 0) {
    LOG_INFO << "Found in " << fVertexZPlots[i]->GetName() << "\t" << nfound  << " peaks" << endm;
    Double_t *zOfPeaks = new Double_t[nfound];
    Int_t npeaks = 0;
#if  ROOT_VERSION_CODE < 395523
    Float_t *xpeaks = fSpectrum->GetPositionX();
    Float_t xp = 0;
#else
    Double_t *xpeaks = fSpectrum->GetPositionX();
    Double_t xp = 0;
#endif
    Int_t Ppeak = -1;
    Double_t Ypeak = -1;
    Double_t Sig = -1;
    for (Int_t p = 0; p < nfound; p++) {
      xp = xpeaks[p];
      Int_t bin = fVertexZPlots[i]->GetXaxis()->FindBin(xp);
      Double_t yp = fVertexZPlots[i]->GetBinContent(bin);
      Double_t ep = fVertexZPlots[i]->GetBinError(bin);
      if (xp < zmin || xp > zmax) continue;
      if (yp-1.25*ep < 0) continue;
      zOfPeaks[npeaks] = xp;
      LOG_INFO << "z = " << xp << " with " << yp << " +/- " << ep << endm;
      if (yp/ep > Sig) {
	Ppeak = npeaks;
	Ypeak = yp;
	Sig = yp/ep;
      }
      npeaks++;
    }
    if (Ppeak > -1) {
      Double_t rms = fVertexZPlots[i]->GetRMS();
      if (rms > 1) rms = 1;
      gausF = (TF1 *) gROOT->GetListOfFunctions()->FindObject("gaus");
      while (! gausF) {
	TF1::InitStandardFunctions();
	gausF = (TF1 *) gROOT->GetListOfFunctions()->FindObject("gaus");
      }
      gausF->SetParameters(Ypeak, zOfPeaks[Ppeak], rms);
      fVertexZPlots[i]->Fit(gausF,"er","",zOfPeaks[Ppeak]-3*rms,zOfPeaks[Ppeak]+3*rms);
      if (gausF) {
	gausF->SetLineColor(i-1);
	Double_t mu = gausF->GetParameter(1);
	Double_t sigma = gausF->GetParameter(2);
	fVertexZPlots[i]->Fit(gausF,"er","",mu-3*sigma,mu+3*sigma);
	if (c1) {
	  fVertexZPlots[i]->Draw();
	  c1->Update();
	  TPaveStats *ps2 = (TPaveStats*)fVertexZPlots[i]->GetListOfFunctions()->FindObject("stats");
	  if (ps2) {
	    ps2->SetTextColor(i-1);
	    ps2->SetX1NDC(0.1+0.5*(i-3)); ps2->SetX2NDC(0.3+0.5*(i-3));
	    ps2->SetY1NDC(0.70); ps2->SetY2NDC(0.90);
	  }
	  c1->Update();
	}
      }
    }
  }
  return gausF;
} // 

