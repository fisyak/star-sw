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
#include "TF1.h"
#include "TEnv.h"
//to obtain error coefficients
#include "StDetectorDbMaker/StiTpcInnerHitErrorCalculator.h"
#include "StDetectorDbMaker/StiTpcOuterHitErrorCalculator.h"
#include "StDetectorDbMaker/StiTPCHitErrorCalculator.h"
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
static Int_t _debug = 1;
#define PrPP(B)  if (_debug)   {cout << (#B) << " = \t" << (B) << endl;}
#define PrPP2(B)  if (_debug)   {cout << (#B) << " = \t" << (*B) << endl;}
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
	fVertexZPlots[i] = new TH1F(Form("VertexZPlot%s",side[i]),Form("z-dca from KFParticle - <Z>  distribution for side = %s",side[i]),400,-20,20);
	fVertexZPlots[i]->SetDirectory(f);
	fVertexZPlots[i]->SetMarkerColor(i-1); 
	fVertexZPlots[i]->SetLineColor(i-1); 
	fVertexZPlots[i]->SetLineWidth(4);
	continue;
      }
      fVertexZPlots[i] = new TH1F(Form("VertexZPlot%s",side[i]),Form("z-dca distribution for side = %s",side[i]),NzBins,zmin,zmax);
      fVertexZPlots[i]->SetDirectory(f);

      fVertexZPlots[i] = new TH1F(Form("VertexZPlot%s",side[i]),Form("z-dca distribution for side = %s",side[i]),NzBins,zmin,zmax);
      fVertexZPlots[i]->SetDirectory(f);
      fVertexXYPlots[i] = new TH2F(Form("VertexXYPlot%s",side[i]),Form("xy-dca distribution for side = %s at Z +/- 10 cm of the 1st peak",side[i]),100,-5,5,100,-5,5);
      fVertexXYPlots[i]->SetDirectory(f);
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
#if 0
      hitc.mMinPad  = tpcHit->minPad();
      hitc.mMaxPad  = tpcHit->maxPad();
      hitc.mMinTmbk = tpcHit->minTmbk();
      hitc.mMaxTmbk = tpcHit->maxTmbk();
#endif
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
  if (_debug) {
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
    if (_debug) {
      cout << "Outer: " << sectorO << "\t"; MakeParticle(tr.OuterParam(), tr.Alpha(), iTr+1).Print();
    }
    ConvertPars( tr.InnerParam(), tr.Alpha(), seed.lastNodePars,  seed.lastNodeErrs);
    if (_debug) {
      cout << "Inner: " << sectorI << "\t"; MakeParticle(tr.InnerParam(), tr.Alpha(), iTr+1).Print();
    }
    fSeeds.push_back(seed);
  }
} // void StiCATpcTrackerInterface::MakeSeeds()
//________________________________________________________________________________
void StiCATpcTrackerInterface::getXYZ(const StiNodePars &pars, const StiNodeErrs &errs, const Float_t &alpha,  Float_t xyzp[6], Float_t CovXyzp[21]) const {
  //  static const Float_t one = 1; // rotate from local Tpc to global <<<<<<<<
#if 0
  static TGeoHMatrix Loc2Glob = StTpcDb::instance()->Tpc2GlobalMatrix();
  static TRMatrix Rot(3,3, Loc2Glob.GetRotationMatrix());
#endif
  Double_t ca = cos(alpha);
  Double_t sa = sin(alpha);
  xyzp[0] = ca*pars.x() - sa*pars.y(); 
  xyzp[1] = sa*pars.x() + ca*pars.y(); 
  xyzp[2] =    pars.z();
  Double_t pT = 1./TMath::Abs(pars.ptin());
  Double_t ce = TMath::Cos(pars.eta()+alpha);
  Double_t se = TMath::Sin(pars.eta()+alpha);
  Double_t px = pT*ce;
  Double_t py = pT*se;
  Double_t pz = pT*pars.tanl();
  xyzp[3] = px;
  xyzp[4] = py;
  xyzp[5] = pz;
  Double_t dpTdPti = -pT*pT*TMath::Sign(1.,pars.ptin());
#if 0
  Double_t fXYZ[9] = {
    //          x,  y,     z,   
    /*  x */  ca, -sa,     0,    
    /*  y */  sa,  ca,     0,    
    /*  z */   0,   0,     1};
  TRMatrix RxyzL(3, 3, fXYZ);
  TRMatrix RxyzG(Rot,TRArray::kAxB, RxyzL);
  Double_t pXYZ[9] = {
    //        eta,               ptin, tanl
    /* px */  -py,         dpTdPti*ce,    0, 
    /* py */   px,         dpTdPti*se,    0,
    /* pz */    0,dpTdPti*pars.tanl(),   pT};
  TRMatrix PxyzL(3, 3, pXYZ);
  TRMatrix PxyzG(Rot,TRArray::kAxB, PxyzL);
  Double_t f[36] = {0};
  for (Int_t i = 0; i < 3; i++)
    for (Int_t j = 0; j < 3; j++) {
      f[6* i    + j  ] = RxyzG[3*i+j];
      f[6*(i+3) + j+3] = PxyzG[3*i+j];
    }
#else
  Double_t f[36] = {
    //          x,  y,     z,     eta,               ptin, tanl
    /*  x */  ca, -sa,     0,       0,                  0,    0, 
    /*  y */  sa,  ca,     0,       0,                  0,    0, 
    /*  z */   0,   0,     1,       0,                  0,    0, 
    /* px */   0,   0,     0,     -py,         dpTdPti*ce,    0, 
    /* py */   0,   0,     0,      px,         dpTdPti*se,    0,
    /* pz */   0,   0,     0,       0,dpTdPti*pars.tanl(),   pT};
#endif
  TRMatrix F(6,6,f);
  TRSymMatrix C(6,errs.G());
  TRSymMatrix Cov(F,TRArray::kAxSxAT,C);

  TCL::ucopy(Cov.GetArray(),CovXyzp,21);
  if (_debug > 1) {
    Double_t xyzp2[6], CovXyzp2[21];
    StiKalmanTrackNode::getXYZ(pars, errs, alpha, xyzp2, CovXyzp2);
    for (Int_t i = 0; i < 6; i++) 
      cout << "getXYZ:  xyzp[" << i << "] = " <<  xyzp[i] << "\txyzp2[" << i << "] = " << xyzp2[i] << endl;
    for (Int_t i = 0; i < 21; i++) 
      cout << "getXYZ:  CovXyzp[" << i << "] = " <<  CovXyzp[i] << "\tCovXyzp2[" << i << "] = " << CovXyzp2[i] << endl;
  }
  return;
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
void StiCATpcTrackerInterface::MakeParticles(std::vector<trackInSector> Tracks, std::vector<int>* pdg) { // init array of particles
  fParticles.clear();
  // create and fill array of tracks to init KFParticleTopoReconstructor
  const int nTracks = Tracks.size(); // tracker->NTracks();
  for ( int iTr = 0; iTr < nTracks; iTr++ ) {
    AliHLTTPCCATrackParam &trParam = Tracks[ iTr ].Track;
    Double_t alpha = Tracks[ iTr ].alpha;
    KFParticle &tempParticle = MakeParticle(trParam, alpha, iTr+1);
    //    PrPP(tempParticle);
    fParticles.push_back(tempParticle);
  }
} // void KFParticleTopoReconstructor::Init(std::vector<AliHLTTPCCATrackParam> tracks, std::vector<int>* pdg=0); // init array of particles
//________________________________________________________________________________
void StiCATpcTrackerInterface::TriggerOffSet() {// Estimate Interaction time wrt Trigger
  KFParticle::SetField(- fTracker->Slice(0).Param().Bz() );
  KFParticleSIMD::SetField(- fTracker->Slice(0).Param().Bz() );
  FindCAWEPrimaryVertices();
    
  StEvent* pEvent = (StEvent*) StMaker::GetChain()->GetInputDS("StEvent");
  StEventSummary *summary = pEvent->summary();
  KFParticleTopoReconstructor  PVEast[2];
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
  if (l4Vx[2]->Ndf > 0) {
    KFVertex PV[2];
    Int_t NTEW[2] = {0};
    Double_t xyzV[2][9] = {0};
    vector<trackInSector> Tracks[2]  = { fTracker->GetLeft(), fTracker->GetRight()};
    static Double_t zFXT = 199.63; // RF/TFG/3p85GeV_fixedTarget_2019B/MuL4Vx.root
    for (UInt_t side = 0; side < 2; side++) {
      vector<trackInSector> tracks;
      for (UInt_t it = 0; it < Tracks[side].size(); it++) {
	//	if (TMath::Abs(l4Vx[side] +  Tracks[side][it].z) > 5) continue; // swap sign og Z for internal sector parameters
	if (TMath::Abs(zFXT +  Tracks[side][it].z) > 20) continue; // swap sign og Z for internal sector parameters
	NTEW[side]++;
	xyzV[side][0] += Tracks[side][it].x;
	xyzV[side][1] -= Tracks[side][it].y;
	xyzV[side][2] -= Tracks[side][it].z;
	
	xyzV[side][3] += Tracks[side][it].x*Tracks[side][it].x;
	xyzV[side][4] += Tracks[side][it].x*Tracks[side][it].y;
	xyzV[side][5] += Tracks[side][it].y*Tracks[side][it].y;
	xyzV[side][6] += Tracks[side][it].x*Tracks[side][it].z;
	xyzV[side][7] += Tracks[side][it].y*Tracks[side][it].z;
	xyzV[side][8] += Tracks[side][it].z*Tracks[side][it].z;
	tracks.push_back(Tracks[side][it]);
      }
      if (tracks.size() < 1) continue;
      for (Int_t i = 0; i < 9; i++) {
	xyzV[side][i] /= NTEW[side];
      }
      for (Int_t i = 0; i < 3; i++)
	for (Int_t j = 0; j <= i; j++) {
	  Int_t ij = 3 + KFParticleBase::IJ(i,j);
	  xyzV[side][ij] -= xyzV[side][i]*xyzV[side][j];
	  xyzV[side][ij] /= NTEW[side] - 1.;
	}
      Float_t xyzF[3] = {0};
#if 0
      Double_t xyzG[3] = {0};
      StTpcDb::instance()->Tpc2GlobalMatrix().LocalToMaster(xyzV[side],xyzG);
      TCL::ucopy(xyzG,xyzF,3);
#else
      TCL::ucopy(xyzV[side],xyzF,3);
#endif
#if 0
      Float_t params[6] = {0};
      Float_t cov[21] = {0};
      TCL::ucopy(xyzG,params,3);
      TCL::ucopy(&xyzV[side][3],cov,6);
      ((KFParticleBase *) &PV[side] )->Initialize(params,cov, 0, 0.);
#else
      static Double_t zFXT = 199.63; // RF/TFG/3p85GeV_fixedTarget_2019B/MuL4Vx.root
      PV[side].Y() = -2.319;
      PV[side].Z() = zFXT;
#endif
      PrPP(PV[side]);
      MakeParticles(tracks);
      UInt_t N = fParticles.size();
      if (!N) continue;
      KFParticle **parts = new KFParticle*[N];
      sort(fParticles.begin(), fParticles.end(), 
	   [](const KFParticle & a, const KFParticle & b)
	   { 
	     //	     return a.GetNDF() > b.GetNDF(); 
	     Float_t pt1, dpt1, pt2, dpt2;
	     a.GetPt(pt1,dpt1);
	     b.GetPt(pt2,dpt2);
	     return pt1/dpt1 > pt2/dpt2;
	   });
      Int_t Np = 0;
      for (UInt_t i = 0; i < N; i++) {
	parts[Np] = &fParticles[i];
	// add time dependence
	if (_debug) {cout << "Before "; PrPP2(parts[Np]);}
	Float_t dsdr[6] = {0};
	Float_t dS = parts[Np]->GetDStoPoint(xyzF, dsdr);
	Double_t dZdS = 1./dsdr[2];
	static Double_t PiMass = TDatabasePDG::Instance()->GetParticle(211)->Mass();
	static Double_t PMass = TDatabasePDG::Instance()->GetParticle(2212)->Mass();
	Float_t P, dP;
	parts[Np]->GetMomentum(P,dP);
	Double_t bgPi = P/PiMass;
	Double_t bgP  = P/PMass;
	Double_t betaPi = bgPi/TMath::Sqrt(1 + bgPi*bgPi); 
	Double_t betaP  = bgP /TMath::Sqrt(1 + bgP *bgP ); 
	Float_t  zPi = parts[Np]->GetZ() + (1. - 2.*side)*dS*DVoveC/betaPi;
	Float_t  zP  = parts[Np]->GetZ() + (1. - 2.*side)*dS*DVoveC/betaP ;
	if (_debug) {
	  cout << "dS = " << dS << "\tdZdS = " << dZdS 
	       << "\tzPi = " << zPi
	       << "\tzP  = " << zP  << endl;
	  parts[Np]->Z() = zPi;
	  cout << "ToF   "; PrPP2(parts[Np]);
	}
	Float_t dSnew = parts[Np]->GetDStoPoint(xyzF, dsdr);
	if (_debug) {cout << "dSnew = " << dSnew << endl;}
	parts[Np]->TransportToDS( dSnew, dsdr );
	if (_debug) {cout << "After  "; PrPP2(parts[Np]);}
	if (TMath::Sqrt(parts[Np]->GetX()*parts[Np]->GetX() + parts[Np]->GetY()*parts[Np]->GetY()) > 4) continue;
	Np++;
      }
      if (Np < 2) continue;
      static Double_t Chi2Cut = 10.25;
      TArrayC Flag(N);
      PV[side].ConstructPrimaryVertex((const KFParticle **) parts, Np, 
				      (Bool_t*) Flag.GetArray(), Chi2Cut/2);
      PrPP(PV[side]);
      DrawKFWEPrimaryVertices(side,PV[side].GetZ());
    }
    DrawKFWEPrimaryVertices(-1);
  }
  // Trigger stuff
  Int_t NoTrigDet = 0;
  enum {kvpd = 0, kbbc, kepd, kzdc, kTAC, kCAV, kTrgTotal};
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
    Double_t dCAVz[2] = { L4VxEast.dMu,  L4VxWest.dMu};
    if (dCAVz[0] < 1e-7 || dCAVz[0] > 0.3) dCAVz[0] = -1e9;
    if (dCAVz[1] < 1e-7 || dCAVz[1] > 0.3) dCAVz[1] = -1e9;
    if (dCAVz[0] > 0 && dCAVz[1] > 0) {
      trgV[kCAV][east] =                   L4VxEast.Mu; trgV[kCAV][west] =                   L4VxWest.Mu;
      Double_t driftVel = StTpcDb::instance()->DriftVelocity()*1e-6;
      trgSum[kCAV] = 0.5*(- trgV[kCAV][east] + trgV[kCAV][west])/driftVel; // in usec, for CAV use difference instead of sum
      NoTrigDet++;
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
void StiCATpcTrackerInterface::DrawKFWEPrimaryVertices(Int_t side, Double_t Z) {
  if (! fSpectrum) return;
  static Double_t PV_z[2] = {0};
  static Double_t zFXT = 199.63; // RF/TFG/3p85GeV_fixedTarget_2019B/MuL4Vx.root
  TCanvas *c1 = 0;
  TString opt("new");
  if (gROOT->IsBatch())  opt = "goff";
  else {
    c1 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("UseKFVxFinder");
    if (c1) c1->Clear();
    else  c1 = new TCanvas("UseKFVxFinder","Fit results for Vertex Z from All, only West and Only East KF racks", 100,700,1000,600);
  }
  if (side < 0 || side > 1) {
    if (c1) {
      Double_t PositionX = PV_z[1], PositionY = 1; 
      TPolyMarker *pm = new TPolyMarker(1, &PositionX, &PositionY);
      fVertexZPlots[4]->GetListOfFunctions()->Add(pm);
      pm->SetMarkerStyle(20);
      pm->SetMarkerColor(3);
      pm->SetMarkerSize(2.3);
      fVertexZPlots[4]->Draw();
      PositionX = PV_z[0];
      pm = new TPolyMarker(1, &PositionX, &PositionY);
      fVertexZPlots[3]->GetListOfFunctions()->Add(pm);
      pm->SetMarkerStyle(20);
      pm->SetMarkerColor(2);
      pm->SetMarkerSize(2.3);
      fVertexZPlots[3]->Draw("][sames");
      c1->Update();
      return;
    }
  }
  PV_z[side] = Z - zFXT;
  for (auto particle : fParticles) {
    FillZHist(fVertexZPlots[3+side], particle.GetZ() - 199.63, TMath::Sqrt(particle.GetCovariance(5)));
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
	gaus->SetLineColor(i-1);
	Double_t mu = gaus->GetParameter(1);
	Double_t sigma = gaus->GetParameter(2);
	fVertexZPlots[i]->Fit(gaus,"er","",mu-3*sigma,mu+3*sigma);
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
} // 

