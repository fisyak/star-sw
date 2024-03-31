#include <assert.h>
#include "Riostream.h"
#include "SectorTrack.h"
#include "StTpcDb/StTpcDb.h"
#include "StTpcHit.h"
#include "StTpcDb/StTpcDb.h"
ClassImp(SectorTrack);
Int_t SectorTrack::_debug = 0;
#define PrPPS(B)  if (_debug) {cout  << "SectorTrack::" << (#B) << " = \t" << (B) << endl;}
//________________________________________________________________________________
SectorTrack::SectorTrack(const SectorTrack &v) {// skip TList
  SetName(v.GetName());
  SetTitle(v.GetTitle());
  fRG  = v.fRG ;
  fNG  = v.fNG ;
  fR   = v.fR  ;
  fN   = v.fN  ;
  fCov = v.fCov;
  memcpy(fRefSurface, v.fRefSurface, sizeof(fRefSurface));
  fSector = v.fSector;  // of the first hit
  fRow    = v.fRow;      // -"-
  fStatus = v.fStatus; 
  fHelix  = v.fHelix;  
  fStep   = v.fStep; 
}						
//________________________________________________________________________________
void  SectorTrack::AddHit(StTpcHit *tpcHit) {
  if (! tpcHit) return;
  Int_t sector = tpcHit->sector();
  Int_t row    = tpcHit->padrow();
  if (fSector <= 0) {
    fSector = sector;
    fRow = row;
  } else {
    assert(fSector == sector);
    if (row < fRow) fRow = row;
  }
  List()->Add(tpcHit);
}
//________________________________________________________________________________
void  SectorTrack::Print(Option_t */* option */) const {
  cout << "Segment: " << GetName() << " for sector " << fSector << " rowMin " << fRow<< endl;
  if (_debug > 1) {
    TIter next(&fList);
    Int_t i = 0;
    StTpcHit *tpcHit = 0;
    while ((tpcHit = (StTpcHit *) next())) {
      cout << i++ << "\t" << *tpcHit << endl;
    }
  }
  fHelix.Print();
  if (_debug) {
    cout << "fRG\t"; fRG.Print();
    cout << "fNG\t"; fNG.Print();
    cout << "fR\t"; fR.Print();
    cout << "fN\t"; fN.Print();
  }
}
//________________________________________________________________________________
void SectorTrack::GetTpcHitErrors(StTpcHit *tpcHit, Double_t err2xy[3], Double_t &err2z) {
  Int_t sector = tpcHit->sector();
  Double_t alfa = TMath::DegToRad()*StTpcDb::SectorPhiDeg(sector);
  Double_t c = cos(alfa);
  Double_t s = sin(alfa);
  Double_t sigma2Y = tpcHit->positionError().perp2();
  err2z = tpcHit->positionError().z()*tpcHit->positionError().z();
#if 0
  if (sigma2Y == 0 || err2z == 0) {
    Int_t row = tpcHit->padrow();
    Int_t io = (row <= St_tpcPadConfigC::instance()->numberOfInnerRows(sector)) ? 0 : 1;
    Double_t z = tpcHit->position().z();
    if (! io) StiTpcInnerHitErrorCalculator::instance()->calculateError(200-z, 0., 0., sigma2Y, err2z);
    else      StiTpcOuterHitErrorCalculator::instance()->calculateError(200-z, 0., 0., sigma2Y, err2z);
  }
#endif
  assert(sigma2Y > 0);
  assert(err2z > 0);
  err2xy[0] =  s*s * sigma2Y;
  err2xy[1] = -s*c * sigma2Y;
  err2xy[2] =  c*c * sigma2Y;
  assert(err2xy[0] + err2xy[2] > 0 && err2z> 0);
}
//________________________________________________________________________________
Int_t  SectorTrack::MakeTHelix(Double_t *RefSurfaceG) {
  fStatus = -1;
  if (fList.GetSize() < 5) return fStatus;
  Int_t i = 0;
  StTpcHit *tpcHit = 0;
#if 0
  if (_debug) {
    TIter nextB(&fList);
    cout << "MakeTHelix : before sort" << endl;
    i = 0;
    while ((tpcHit = (StTpcHit *) nextB())) {
      cout << i++ << "\t" << *tpcHit << endl;
    }
  }
#endif
  fList.Sort();
  TIter next(&fList);
  Double_t err2xy[3] = {0},  err2z = 0;
#if 0
  if (_debug) cout << "MakeTHelix : after sort" << endl;
  i = 0;
#endif
  while ((tpcHit = (StTpcHit *) next())) {
    if (_debug) cout << i++ << "\t" << *tpcHit << endl;
    if (fSector < 0) {fSector = tpcHit->sector(); fRow = tpcHit->padrow();}
    else assert(fSector == (Int_t) tpcHit->sector());
    GetTpcHitErrors(tpcHit, err2xy, err2z);
    fHelix.Add(tpcHit->position().xyz());
    fHelix.AddErr(err2xy,err2z);
  }
  Double_t chisq = fHelix.Fit();
  if (chisq > 100.) return fStatus;
  if (fHelix.MakeErrs()) return fStatus;
  if (! RefSurfaceG) {fStatus = 0; return fStatus;}
  Move(RefSurfaceG);
  return fStatus;
}
//________________________________________________________________________________
Int_t  SectorTrack::Move(Double_t *refSurfaceG) {
  assert(refSurfaceG);
  static Double_t stepMX = 1.e3;
  fStatus = -1;
  memcpy(fRefSurface, refSurfaceG, sizeof(fRefSurface));
  Double_t xyzG[3] = {0};
  Double_t dirG[3] = {0};
  fStep = fHelix.Step(stepMX, fRefSurface, 4, xyzG, dirG, 1);
  if (TMath::Abs(fStep) >= stepMX) return fStatus;
  fHelix.Move(fStep);
  fRG = TVector3(fHelix.Pos());
  fNG = TVector3(fHelix.Dir());
  if (fRG.Dot(fNG) < 0) {fHelix.Backward(); fNG = TVector3(fHelix.Dir());}
  Double_t loc[3] = {0};
  fRG.GetXYZ(xyzG);
  fNG.GetXYZ(dirG);
  StTpcDb::instance()->Sup12S2Glob(fSector).MasterToLocal(xyzG, loc);
  fR = TVector3(loc);
  if (fR.z() < -10.0 || fR.z() > 220.0) return fStatus; // acceptable drift distance
  StTpcDb::instance()->Sup12S2Glob(fSector).MasterToLocalVect(dirG, loc);  
  fN = TVector3(loc);
  Double_t cosL  = fN.Perp()/fN.Mag();
  Double_t cosCA = fN.Y()/cosL; // Sup12S => Sti:  x <=>y, z => -z 
  TRSymMatrix StiErr(6);
  fHelix.StiEmx(StiErr.GetArray(), cosCA, cosL);     PrPPS(StiErr);
  TRMatrix S2R = GetSti2G(fN);                       PrPPS(S2R);
  fCov = TRSymMatrix(S2R,TRArray::kAxSxAT,StiErr);  if (_debug) {PrPPS(fCov); TRSymMatrix Cor(fCov, TRArray::kSCor); PrPPS(Cor);}
  if (TMath::Sqrt(fCov(0,0)) > 0.2 || 
      TMath::Sqrt(fCov(1,1)) > 0.2 || 
      TMath::Sqrt(fCov(2,2)) > 0.2 || 
      TMath::Sqrt(fCov(3,3)) > 0.01|| 
      TMath::Sqrt(fCov(4,4)) > 0.01||
      TMath::Sqrt(fCov(5,5)) > 0.01) return fStatus;
  fStatus = 0;
  return fStatus;
}
//________________________________________________________________________________
TRMatrix SectorTrack::GetSti2G(Double_t nx, Double_t ny, Double_t nz) {
  /* StiKalmanTrackNode::getMomentum
     _cosCA = cos(myNode.mFP.eta());
  p[0] = pt*mFP._cosCA;
  p[1] = pt*mFP._sinCA;
  p[2] = pt*mFP.tanl();
  Sti     Sup12S
     x =  y
     y =  x
     z = -z
   */
/*
X(y):= y;
Y(x):= x;
Z(z):= -z;
cosT(Tan) := 1/sqrt(1 + Tan*Tan); 
sinT(Tan) := Tan*cosT(Tan);
nx(Phi,Tan) := cos(Phi)*cosT(Tan);
ny(Phi,Tan) := sin(Phi)*cosT(Tan);
nz(Tan)  := -sinT(Tan);
Sti2G : jacobian([X(y), Y(x), Z(z), nx(Phi, Tan), ny(Phi,Tan), nz(Tan)], [x, y, z, Phi, Ptin, Tan]);
(%i48) Sti2G:jacobian([X(y),Y(x),Z(z),nx(Phi,Tan),ny(Phi,Tan),nz(Tan)],
                      [x,y,z,Phi,Ptin,Tan])
       [ 0  1   0          0          0                0                ]
       [                                                                ]
       [ 1  0   0          0          0                0                ]
       [                                                                ]
       [ 0  0  - 1         0          0                0                ]
       [                                                                ]
       [                 sin(Phi)                 cos(Phi)*Tan          ]
       [ 0  0   0   - --------------  0         - -------------         ]
       [                      2                       2     3/2         ]
       [              sqrt(Tan  + 1)              (Tan  + 1)            ]
(%o48) [                                                                ]
       [                cos(Phi)                  sin(Phi)*Tan          ]
       [ 0  0   0    --------------   0         - -------------         ]
       [                     2                        2     3/2         ]
       [             sqrt(Tan  + 1)               (Tan  + 1)            ]
       [                                                                ]
       [                                        2                       ]
       [                                     Tan               1        ]
       [ 0  0   0          0          0  ------------- - -------------- ]
       [                                     2     3/2           2      ]
       [                                 (Tan  + 1)      sqrt(Tan  + 1) ]
Sti2G[0][1] = 1
Sti2G[1][0] = 1
Sti2G[2][2] = -1
Sti2G[3][3] = -sin(Phi)/sqrt(Tan**2+1)
Sti2G[3][5] = -cos(Phi)*Tan*(Tan**2+1)**((-3.d+0)/2.d+0)
Sti2G[4][3] = cos(Phi)/sqrt(Tan**2+1)
Sti2G[4][5] = -sin(Phi)*Tan*(Tan**2+1)**((-3.d+0)/2.d+0)
Sti2G[5][5] = Tan**2*(Tan**2+1)**((-3.d+0)/2.d+0)-1/sqrt(Tan**2+1)


   nx = cosP * cosL;
   ny = sinP * cosL;
   nz =        sinL;
*/
  Double_t dxy  = TMath::Sqrt(nx*nx + ny*ny);
  Double_t tanL = nz/dxy;
  Double_t cosL = 1./TMath::Sqrt(1+tanL*tanL); // cosL
  Double_t sinL = tanL*cosL;
  //  Double_t cosP = nx/cosL;
  //  Double_t sinP = ny/cosL;
  Double_t Sti2G[6][6] = {0};
  Sti2G[0][1] =   1;
  Sti2G[1][0] =   1;
  Sti2G[2][2] =  -1;
  Sti2G[3][3] = -ny;               // -sin(Phi)/sqrt(tanL**2+1) = -sin(Phi)*cosL = -ny;
  Sti2G[3][5] = -nx * sinL * cosL; // -cos(Phi)*tanL*(tanL**2+1)**((-3.d+0)/2.d+0) = -cos(Phi)*sinL/cosL*cosL**3 = -cos(Phi)*sinL*cosL**2 = -= -nx * sinL * cosL
  Sti2G[4][3] =  nx;               // cos(Phi)*cosL;
  Sti2G[4][5] = -ny * sinL * cosL; // -sin(Phi)*tanL*TMath::Power(cosL,3) = -sin(Phi)*sinL * cosL**2 = -ny * sinL * cosL;
  Sti2G[5][5] =  nz * cosL * cosL; // tanL**2*TMath::Power(cosL,3)-cosL = sinL/cosL *cosL**3 = sinL * cosL**2 = nz * cosL * cosL;
  return TRMatrix(6,6,&Sti2G[0][0]); 
}
