//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Sep 19 20:32:33 2025 by ROOT version 5.34/39
// from TChain laser/
//////////////////////////////////////////////////////////
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "Riostream.h"
#include <stdio.h>
// Header file for the classes stored in the TTree if any.
#include <TObject.h>
#include "StThreeVector.hh"
#include "TVector3.h"
#include <TH2.h>
#include "TProfile.h"
#include <TStyle.h>
#include <TCanvas.h>
#include "Ask.h"
//       s/2  b  m
TH2F *dXY[12][6][7] = {0};
TH2F *dPT[12][6][7] = {0};
TProfile *pf[4] = {0};
class  corr_t {
public:
  corr_t(Double_t e=0, Double_t x=0, Double_t ex=0, Double_t y=0, Double_t ey=0, Double_t p=0, Double_t ep=0, Double_t t=0, Double_t et=0) :
    entries(e), dX(x), ddX(ex), dY(y), ddY(ey), dPhi(p), ddPhi(ep), dTheta(t), ddTheta(et) {}
  Double_t entries;
  Double_t dX, ddX;        // cm
  Double_t dY, ddY;        // cm
  Double_t dPhi, ddPhi;    // mrad
  Double_t dTheta, ddTheta;// mrad 
};
ostream&  operator<<(ostream& os, const corr_t& v)
{
  return os << Form("corr_t(%10.5g, %8.4f, %8.4f, %8.4f, %8.4f, %8.4f, %8.4f, %8.4f, %8.4f);",v.entries,v.dX,v.ddX,v.dY,v.ddY,v.dPhi,v.ddPhi,v.dTheta,v.ddTheta);
}
corr_t corr[12][6][7];
// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxfVertices = 1;
   const Int_t kMaxfTracks = 264;
   const Int_t kMaxfHits = 8948;
   const Int_t kMaxfFit = 12;

class laser {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //LaserEvent      *event;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           fNtrack;
   Int_t           fNhit;
   Int_t           fNvertex;
   Int_t           fEvtHdr_fEvtNum;
   Int_t           fEvtHdr_fRun;
   Int_t           fEvtHdr_fDate;
   Int_t           fEvtHdr_fTime;
   Float_t         fEvtHdr_ftZero;
   Float_t         fEvtHdr_fDriVel;
   Float_t         fEvtHdr_fDriVelWest;
   Float_t         fEvtHdr_fDriVelEast;
   Float_t         fEvtHdr_fClock;
   Float_t         fEvtHdr_fTrigger;
   Float_t         fEvtHdr_fDriftDistance;
   Float_t         fEvtHdr_fInnerSectorzOffset;
   Float_t         fEvtHdr_fOuterSectorzOffset;
   Float_t         fEvtHdr_ftriggerTimeOffset;
   Float_t         fEvtHdr_fOnlClock;
   Float_t         fEvtHdr_fBField;
   Float_t         fEvtHdr_fScaleY;
   Int_t           fVertices_;
   UInt_t          fVertices_fUniqueID[kMaxfVertices];   //[fVertices_]
   UInt_t          fVertices_fBits[kMaxfVertices];   //[fVertices_]
   Int_t           fVertices_mType[kMaxfVertices];   //[fVertices_]
   Int_t           fVertices_WestEast[kMaxfVertices];   //[fVertices_]
   Double_t        fVertices_Xyz_mX1[kMaxfVertices];   //[fVertices_]
   Double_t        fVertices_Xyz_mX2[kMaxfVertices];   //[fVertices_]
   Double_t        fVertices_Xyz_mX3[kMaxfVertices];   //[fVertices_]
   Double_t        fVertices_XyzL_mX1[kMaxfVertices];   //[fVertices_]
   Double_t        fVertices_XyzL_mX2[kMaxfVertices];   //[fVertices_]
   Double_t        fVertices_XyzL_mX3[kMaxfVertices];   //[fVertices_]
   UInt_t          fVertices_numberOfDaughter[kMaxfVertices];   //[fVertices_]
   Int_t           fTracks_;
   UInt_t          fTracks_fUniqueID[kMaxfTracks];   //[fTracks_]
   UInt_t          fTracks_fBits[kMaxfTracks];   //[fTracks_]
   Int_t           fTracks_Flag[kMaxfTracks];   //[fTracks_]
   Int_t           fTracks_mType[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Vertex_mX1[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Vertex_mX2[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Vertex_mX3[kMaxfTracks];   //[fTracks_]
   Int_t           fTracks_mSector[kMaxfTracks];   //[fTracks_]
   Int_t           fTracks_mKey[kMaxfTracks];   //[fTracks_]
   Short_t         fTracks_mFlag[kMaxfTracks];   //[fTracks_]
   UShort_t        fTracks_mNumberOfPossiblePointsTpc[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_mImpactParameter[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_mLength[kMaxfTracks];   //[fTracks_]
   UShort_t        fTracks_mNumberOfFitPointsTpc[kMaxfTracks];   //[fTracks_]
   UShort_t        fTracks_mPrimaryVertexUsedInFit[kMaxfTracks];   //[fTracks_]
   Int_t           fTracks_fNdEdx[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fdEdx[kMaxfTracks];   //[fTracks_]
   UInt_t          fTracks_fgeoIn_fUniqueID[kMaxfTracks];   //[fTracks_]
   UInt_t          fTracks_fgeoIn_fBits[kMaxfTracks];   //[fTracks_]
   Int_t           fTracks_fgeoIn_mModel[kMaxfTracks];   //[fTracks_]
   Short_t         fTracks_fgeoIn_mCharge[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fgeoIn_mPsi[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fgeoIn_mCurvature[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fgeoIn_mDipAngle[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fgeoIn_mOrigin_mX1[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fgeoIn_mOrigin_mX2[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fgeoIn_mOrigin_mX3[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fgeoIn_mMomentum_mX1[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fgeoIn_mMomentum_mX2[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fgeoIn_mMomentum_mX3[kMaxfTracks];   //[fTracks_]
   Short_t         fTracks_fgeoIn_mHelicity[kMaxfTracks];   //[fTracks_]
   UInt_t          fTracks_fgeoOut_fUniqueID[kMaxfTracks];   //[fTracks_]
   UInt_t          fTracks_fgeoOut_fBits[kMaxfTracks];   //[fTracks_]
   Int_t           fTracks_fgeoOut_mModel[kMaxfTracks];   //[fTracks_]
   Short_t         fTracks_fgeoOut_mCharge[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fgeoOut_mPsi[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fgeoOut_mCurvature[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fgeoOut_mDipAngle[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fgeoOut_mOrigin_mX1[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fgeoOut_mOrigin_mX2[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fgeoOut_mOrigin_mX3[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fgeoOut_mMomentum_mX1[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fgeoOut_mMomentum_mX2[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fgeoOut_mMomentum_mX3[kMaxfTracks];   //[fTracks_]
   Short_t         fTracks_fgeoOut_mHelicity[kMaxfTracks];   //[fTracks_]
   UInt_t          fTracks_fDca_fUniqueID[kMaxfTracks];   //[fTracks_]
   UInt_t          fTracks_fDca_fBits[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fDca_mImp[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fDca_mZ[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fDca_mPsi[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fDca_mPti[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fDca_mTan[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fDca_mCurv[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fDca_mImpImp[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fDca_mZImp[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fDca_mZZ[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fDca_mPsiImp[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fDca_mPsiZ[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fDca_mPsiPsi[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fDca_mPtiImp[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fDca_mPtiZ[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fDca_mPtiPsi[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fDca_mPtiPti[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fDca_mTanImp[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fDca_mTanZ[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fDca_mTanPsi[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fDca_mTanPti[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fDca_mTanTan[kMaxfTracks];   //[fTracks_]
   Double32_t      fTracks_fpTInv[kMaxfTracks];   //[fTracks_]
   Double32_t      fTracks_fTheta[kMaxfTracks];   //[fTracks_]
   Double32_t      fTracks_fPhi[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_XyzP_mX1[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_XyzP_mX2[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_XyzP_mX3[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_XyzPL_mX1[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_XyzPL_mX2[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_XyzPL_mX3[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_XyzPU_mX1[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_XyzPU_mX2[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_XyzPU_mX3[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_XyzPB_mX1[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_XyzPB_mX2[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_XyzPB_mX3[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_XyzPM_mX1[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_XyzPM_mX2[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_XyzPM_mX3[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_dirP_mX1[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_dirP_mX2[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_dirP_mX3[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_dirPL_mX1[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_dirPL_mX2[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_dirPL_mX3[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_dirPU_mX1[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_dirPU_mX2[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_dirPU_mX3[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_dirPB_mX1[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_dirPB_mX2[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_dirPB_mX3[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_dirPM_mX1[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_dirPM_mX2[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_dirPM_mX3[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_dU_mX1[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_dU_mX2[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_dU_mX3[kMaxfTracks];   //[fTracks_]
   Double32_t      fTracks_thePath[kMaxfTracks];   //[fTracks_]
   Int_t           fTracks_Laser_IsValid[kMaxfTracks];   //[fTracks_]
   Int_t           fTracks_Laser_Sector[kMaxfTracks];   //[fTracks_]
   Int_t           fTracks_Laser_Raft[kMaxfTracks];   //[fTracks_]
   Int_t           fTracks_Laser_Bundle[kMaxfTracks];   //[fTracks_]
   Int_t           fTracks_Laser_Mirror[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_XyzG_mX1[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_XyzG_mX2[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_XyzG_mX3[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_XyzL_mX1[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_XyzL_mX2[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_XyzL_mX3[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_XyzS_mX1[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_XyzS_mX2[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_XyzS_mX3[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_XyzU_mX1[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_XyzU_mX2[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_XyzU_mX3[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_XyzB_mX1[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_XyzB_mX2[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_XyzB_mX3[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_dirG_mX1[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_dirG_mX2[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_dirG_mX3[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_dirL_mX1[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_dirL_mX2[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_dirL_mX3[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_dirS_mX1[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_dirS_mX2[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_dirS_mX3[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_dirU_mX1[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_dirU_mX2[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_dirU_mX3[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_dirB_mX1[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_dirB_mX2[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_dirB_mX3[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_Theta[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_Phi[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_ThetaG[kMaxfTracks];   //[fTracks_]
   Double_t        fTracks_Laser_PhiG[kMaxfTracks];   //[fTracks_]
   Double32_t      fTracks_dPhi[kMaxfTracks];   //[fTracks_]
   Double32_t      fTracks_dTheta[kMaxfTracks];   //[fTracks_]
   Double32_t      fTracks_zLastHit[kMaxfTracks];   //[fTracks_]
   Int_t           fHits_;
   UInt_t          fHits_fUniqueID[kMaxfHits];   //[fHits_]
   UInt_t          fHits_fBits[kMaxfHits];   //[fHits_]
   UShort_t        fHits_sector[kMaxfHits];   //[fHits_]
   UShort_t        fHits_row[kMaxfHits];   //[fHits_]
   Float_t         fHits_charge[kMaxfHits];   //[fHits_]
   UInt_t          fHits_flag[kMaxfHits];   //[fHits_]
   Int_t           fHits_usedInFit[kMaxfHits];   //[fHits_]
   Float_t         fHits_xyz_mX1[kMaxfHits];   //[fHits_]
   Float_t         fHits_xyz_mX2[kMaxfHits];   //[fHits_]
   Float_t         fHits_xyz_mX3[kMaxfHits];   //[fHits_]
   Float_t         fHits_xyzL_mX1[kMaxfHits];   //[fHits_]
   Float_t         fHits_xyzL_mX2[kMaxfHits];   //[fHits_]
   Float_t         fHits_xyzL_mX3[kMaxfHits];   //[fHits_]
   Float_t         fHits_xyzS_mX1[kMaxfHits];   //[fHits_]
   Float_t         fHits_xyzS_mX2[kMaxfHits];   //[fHits_]
   Float_t         fHits_xyzS_mX3[kMaxfHits];   //[fHits_]
   Float_t         fHits_xyzTpcL_mX1[kMaxfHits];   //[fHits_]
   Float_t         fHits_xyzTpcL_mX2[kMaxfHits];   //[fHits_]
   Float_t         fHits_xyzTpcL_mX3[kMaxfHits];   //[fHits_]
   Float_t         fHits_pad[kMaxfHits];   //[fHits_]
   Float_t         fHits_tbk[kMaxfHits];   //[fHits_]
   Int_t           fHits_trackKey[kMaxfHits];   //[fHits_]
   Int_t           fHits_adc[kMaxfHits];   //[fHits_]
   Int_t           fFit_;
   UInt_t          fFit_fUniqueID[kMaxfFit];   //[fFit_]
   UInt_t          fFit_fBits[kMaxfFit];   //[fFit_]
   Char_t          fFit_first[kMaxfFit][1];   //[fFit_]
   Int_t           fFit_N[kMaxfFit];   //[fFit_]
   Int_t           fFit_Sector[kMaxfFit];   //[fFit_]
   Int_t           fFit_Bundle[kMaxfFit][42];   //[fFit_]
   Int_t           fFit_Mirror[kMaxfFit][42];   //[fFit_]
   Double32_t      fFit_offset[kMaxfFit];   //[fFit_]
   Double32_t      fFit_slope[kMaxfFit];   //[fFit_]
   Double32_t      fFit_doffset[kMaxfFit];   //[fFit_]
   Double32_t      fFit_dslope[kMaxfFit];   //[fFit_]
   Double32_t      fFit_chisq[kMaxfFit];   //[fFit_]
   Double32_t      fFit_X[kMaxfFit][42];   //[fFit_]
   Double32_t      fFit_Y[kMaxfFit][42];   //[fFit_]
   Double32_t      fFit_Prob[kMaxfFit];   //[fFit_]
   Int_t           fFit_ndf[kMaxfFit];   //[fFit_]
   Int_t           fFit_Flag[kMaxfFit][42];   //[fFit_]
   Char_t          fFit_last[kMaxfFit][1];   //[fFit_]

   // List of branches
   TBranch        *b_event_fUniqueID;   //!
   TBranch        *b_event_fBits;   //!
   TBranch        *b_event_fNtrack;   //!
   TBranch        *b_event_fNhit;   //!
   TBranch        *b_event_fNvertex;   //!
   TBranch        *b_event_fEvtHdr_fEvtNum;   //!
   TBranch        *b_event_fEvtHdr_fRun;   //!
   TBranch        *b_event_fEvtHdr_fDate;   //!
   TBranch        *b_event_fEvtHdr_fTime;   //!
   TBranch        *b_event_fEvtHdr_ftZero;   //!
   TBranch        *b_event_fEvtHdr_fDriVel;   //!
   TBranch        *b_event_fEvtHdr_fDriVelWest;   //!
   TBranch        *b_event_fEvtHdr_fDriVelEast;   //!
   TBranch        *b_event_fEvtHdr_fClock;   //!
   TBranch        *b_event_fEvtHdr_fTrigger;   //!
   TBranch        *b_event_fEvtHdr_fDriftDistance;   //!
   TBranch        *b_event_fEvtHdr_fInnerSectorzOffset;   //!
   TBranch        *b_event_fEvtHdr_fOuterSectorzOffset;   //!
   TBranch        *b_event_fEvtHdr_ftriggerTimeOffset;   //!
   TBranch        *b_event_fEvtHdr_fOnlClock;   //!
   TBranch        *b_event_fEvtHdr_fBField;   //!
   TBranch        *b_event_fEvtHdr_fScaleY;   //!
   TBranch        *b_event_fVertices_;   //!
   TBranch        *b_fVertices_fUniqueID;   //!
   TBranch        *b_fVertices_fBits;   //!
   TBranch        *b_fVertices_mType;   //!
   TBranch        *b_fVertices_WestEast;   //!
   TBranch        *b_fVertices_Xyz_mX1;   //!
   TBranch        *b_fVertices_Xyz_mX2;   //!
   TBranch        *b_fVertices_Xyz_mX3;   //!
   TBranch        *b_fVertices_XyzL_mX1;   //!
   TBranch        *b_fVertices_XyzL_mX2;   //!
   TBranch        *b_fVertices_XyzL_mX3;   //!
   TBranch        *b_fVertices_numberOfDaughter;   //!
   TBranch        *b_event_fTracks_;   //!
   TBranch        *b_fTracks_fUniqueID;   //!
   TBranch        *b_fTracks_fBits;   //!
   TBranch        *b_fTracks_Flag;   //!
   TBranch        *b_fTracks_mType;   //!
   TBranch        *b_fTracks_Vertex_mX1;   //!
   TBranch        *b_fTracks_Vertex_mX2;   //!
   TBranch        *b_fTracks_Vertex_mX3;   //!
   TBranch        *b_fTracks_mSector;   //!
   TBranch        *b_fTracks_mKey;   //!
   TBranch        *b_fTracks_mFlag;   //!
   TBranch        *b_fTracks_mNumberOfPossiblePointsTpc;   //!
   TBranch        *b_fTracks_mImpactParameter;   //!
   TBranch        *b_fTracks_mLength;   //!
   TBranch        *b_fTracks_mNumberOfFitPointsTpc;   //!
   TBranch        *b_fTracks_mPrimaryVertexUsedInFit;   //!
   TBranch        *b_fTracks_fNdEdx;   //!
   TBranch        *b_fTracks_fdEdx;   //!
   TBranch        *b_fTracks_fgeoIn_fUniqueID;   //!
   TBranch        *b_fTracks_fgeoIn_fBits;   //!
   TBranch        *b_fTracks_fgeoIn_mModel;   //!
   TBranch        *b_fTracks_fgeoIn_mCharge;   //!
   TBranch        *b_fTracks_fgeoIn_mPsi;   //!
   TBranch        *b_fTracks_fgeoIn_mCurvature;   //!
   TBranch        *b_fTracks_fgeoIn_mDipAngle;   //!
   TBranch        *b_fTracks_fgeoIn_mOrigin_mX1;   //!
   TBranch        *b_fTracks_fgeoIn_mOrigin_mX2;   //!
   TBranch        *b_fTracks_fgeoIn_mOrigin_mX3;   //!
   TBranch        *b_fTracks_fgeoIn_mMomentum_mX1;   //!
   TBranch        *b_fTracks_fgeoIn_mMomentum_mX2;   //!
   TBranch        *b_fTracks_fgeoIn_mMomentum_mX3;   //!
   TBranch        *b_fTracks_fgeoIn_mHelicity;   //!
   TBranch        *b_fTracks_fgeoOut_fUniqueID;   //!
   TBranch        *b_fTracks_fgeoOut_fBits;   //!
   TBranch        *b_fTracks_fgeoOut_mModel;   //!
   TBranch        *b_fTracks_fgeoOut_mCharge;   //!
   TBranch        *b_fTracks_fgeoOut_mPsi;   //!
   TBranch        *b_fTracks_fgeoOut_mCurvature;   //!
   TBranch        *b_fTracks_fgeoOut_mDipAngle;   //!
   TBranch        *b_fTracks_fgeoOut_mOrigin_mX1;   //!
   TBranch        *b_fTracks_fgeoOut_mOrigin_mX2;   //!
   TBranch        *b_fTracks_fgeoOut_mOrigin_mX3;   //!
   TBranch        *b_fTracks_fgeoOut_mMomentum_mX1;   //!
   TBranch        *b_fTracks_fgeoOut_mMomentum_mX2;   //!
   TBranch        *b_fTracks_fgeoOut_mMomentum_mX3;   //!
   TBranch        *b_fTracks_fgeoOut_mHelicity;   //!
   TBranch        *b_fTracks_fDca_fUniqueID;   //!
   TBranch        *b_fTracks_fDca_fBits;   //!
   TBranch        *b_fTracks_fDca_mImp;   //!
   TBranch        *b_fTracks_fDca_mZ;   //!
   TBranch        *b_fTracks_fDca_mPsi;   //!
   TBranch        *b_fTracks_fDca_mPti;   //!
   TBranch        *b_fTracks_fDca_mTan;   //!
   TBranch        *b_fTracks_fDca_mCurv;   //!
   TBranch        *b_fTracks_fDca_mImpImp;   //!
   TBranch        *b_fTracks_fDca_mZImp;   //!
   TBranch        *b_fTracks_fDca_mZZ;   //!
   TBranch        *b_fTracks_fDca_mPsiImp;   //!
   TBranch        *b_fTracks_fDca_mPsiZ;   //!
   TBranch        *b_fTracks_fDca_mPsiPsi;   //!
   TBranch        *b_fTracks_fDca_mPtiImp;   //!
   TBranch        *b_fTracks_fDca_mPtiZ;   //!
   TBranch        *b_fTracks_fDca_mPtiPsi;   //!
   TBranch        *b_fTracks_fDca_mPtiPti;   //!
   TBranch        *b_fTracks_fDca_mTanImp;   //!
   TBranch        *b_fTracks_fDca_mTanZ;   //!
   TBranch        *b_fTracks_fDca_mTanPsi;   //!
   TBranch        *b_fTracks_fDca_mTanPti;   //!
   TBranch        *b_fTracks_fDca_mTanTan;   //!
   TBranch        *b_fTracks_fpTInv;   //!
   TBranch        *b_fTracks_fTheta;   //!
   TBranch        *b_fTracks_fPhi;   //!
   TBranch        *b_fTracks_XyzP_mX1;   //!
   TBranch        *b_fTracks_XyzP_mX2;   //!
   TBranch        *b_fTracks_XyzP_mX3;   //!
   TBranch        *b_fTracks_XyzPL_mX1;   //!
   TBranch        *b_fTracks_XyzPL_mX2;   //!
   TBranch        *b_fTracks_XyzPL_mX3;   //!
   TBranch        *b_fTracks_XyzPU_mX1;   //!
   TBranch        *b_fTracks_XyzPU_mX2;   //!
   TBranch        *b_fTracks_XyzPU_mX3;   //!
   TBranch        *b_fTracks_XyzPB_mX1;   //!
   TBranch        *b_fTracks_XyzPB_mX2;   //!
   TBranch        *b_fTracks_XyzPB_mX3;   //!
   TBranch        *b_fTracks_XyzPM_mX1;   //!
   TBranch        *b_fTracks_XyzPM_mX2;   //!
   TBranch        *b_fTracks_XyzPM_mX3;   //!
   TBranch        *b_fTracks_dirP_mX1;   //!
   TBranch        *b_fTracks_dirP_mX2;   //!
   TBranch        *b_fTracks_dirP_mX3;   //!
   TBranch        *b_fTracks_dirPL_mX1;   //!
   TBranch        *b_fTracks_dirPL_mX2;   //!
   TBranch        *b_fTracks_dirPL_mX3;   //!
   TBranch        *b_fTracks_dirPU_mX1;   //!
   TBranch        *b_fTracks_dirPU_mX2;   //!
   TBranch        *b_fTracks_dirPU_mX3;   //!
   TBranch        *b_fTracks_dirPB_mX1;   //!
   TBranch        *b_fTracks_dirPB_mX2;   //!
   TBranch        *b_fTracks_dirPB_mX3;   //!
   TBranch        *b_fTracks_dirPM_mX1;   //!
   TBranch        *b_fTracks_dirPM_mX2;   //!
   TBranch        *b_fTracks_dirPM_mX3;   //!
   TBranch        *b_fTracks_dU_mX1;   //!
   TBranch        *b_fTracks_dU_mX2;   //!
   TBranch        *b_fTracks_dU_mX3;   //!
   TBranch        *b_fTracks_thePath;   //!
   TBranch        *b_fTracks_Laser_IsValid;   //!
   TBranch        *b_fTracks_Laser_Sector;   //!
   TBranch        *b_fTracks_Laser_Raft;   //!
   TBranch        *b_fTracks_Laser_Bundle;   //!
   TBranch        *b_fTracks_Laser_Mirror;   //!
   TBranch        *b_fTracks_Laser_XyzG_mX1;   //!
   TBranch        *b_fTracks_Laser_XyzG_mX2;   //!
   TBranch        *b_fTracks_Laser_XyzG_mX3;   //!
   TBranch        *b_fTracks_Laser_XyzL_mX1;   //!
   TBranch        *b_fTracks_Laser_XyzL_mX2;   //!
   TBranch        *b_fTracks_Laser_XyzL_mX3;   //!
   TBranch        *b_fTracks_Laser_XyzS_mX1;   //!
   TBranch        *b_fTracks_Laser_XyzS_mX2;   //!
   TBranch        *b_fTracks_Laser_XyzS_mX3;   //!
   TBranch        *b_fTracks_Laser_XyzU_mX1;   //!
   TBranch        *b_fTracks_Laser_XyzU_mX2;   //!
   TBranch        *b_fTracks_Laser_XyzU_mX3;   //!
   TBranch        *b_fTracks_Laser_XyzB_mX1;   //!
   TBranch        *b_fTracks_Laser_XyzB_mX2;   //!
   TBranch        *b_fTracks_Laser_XyzB_mX3;   //!
   TBranch        *b_fTracks_Laser_dirG_mX1;   //!
   TBranch        *b_fTracks_Laser_dirG_mX2;   //!
   TBranch        *b_fTracks_Laser_dirG_mX3;   //!
   TBranch        *b_fTracks_Laser_dirL_mX1;   //!
   TBranch        *b_fTracks_Laser_dirL_mX2;   //!
   TBranch        *b_fTracks_Laser_dirL_mX3;   //!
   TBranch        *b_fTracks_Laser_dirS_mX1;   //!
   TBranch        *b_fTracks_Laser_dirS_mX2;   //!
   TBranch        *b_fTracks_Laser_dirS_mX3;   //!
   TBranch        *b_fTracks_Laser_dirU_mX1;   //!
   TBranch        *b_fTracks_Laser_dirU_mX2;   //!
   TBranch        *b_fTracks_Laser_dirU_mX3;   //!
   TBranch        *b_fTracks_Laser_dirB_mX1;   //!
   TBranch        *b_fTracks_Laser_dirB_mX2;   //!
   TBranch        *b_fTracks_Laser_dirB_mX3;   //!
   TBranch        *b_fTracks_Laser_Theta;   //!
   TBranch        *b_fTracks_Laser_Phi;   //!
   TBranch        *b_fTracks_Laser_ThetaG;   //!
   TBranch        *b_fTracks_Laser_PhiG;   //!
   TBranch        *b_fTracks_dPhi;   //!
   TBranch        *b_fTracks_dTheta;   //!
   TBranch        *b_fTracks_zLastHit;   //!
   TBranch        *b_event_fHits_;   //!
   TBranch        *b_fHits_fUniqueID;   //!
   TBranch        *b_fHits_fBits;   //!
   TBranch        *b_fHits_sector;   //!
   TBranch        *b_fHits_row;   //!
   TBranch        *b_fHits_charge;   //!
   TBranch        *b_fHits_flag;   //!
   TBranch        *b_fHits_usedInFit;   //!
   TBranch        *b_fHits_xyz_mX1;   //!
   TBranch        *b_fHits_xyz_mX2;   //!
   TBranch        *b_fHits_xyz_mX3;   //!
   TBranch        *b_fHits_xyzL_mX1;   //!
   TBranch        *b_fHits_xyzL_mX2;   //!
   TBranch        *b_fHits_xyzL_mX3;   //!
   TBranch        *b_fHits_xyzS_mX1;   //!
   TBranch        *b_fHits_xyzS_mX2;   //!
   TBranch        *b_fHits_xyzS_mX3;   //!
   TBranch        *b_fHits_xyzTpcL_mX1;   //!
   TBranch        *b_fHits_xyzTpcL_mX2;   //!
   TBranch        *b_fHits_xyzTpcL_mX3;   //!
   TBranch        *b_fHits_pad;   //!
   TBranch        *b_fHits_tbk;   //!
   TBranch        *b_fHits_trackKey;   //!
   TBranch        *b_fHits_adc;   //!
   TBranch        *b_event_fFit_;   //!
   TBranch        *b_fFit_fUniqueID;   //!
   TBranch        *b_fFit_fBits;   //!
   TBranch        *b_fFit_first;   //!
   TBranch        *b_fFit_N;   //!
   TBranch        *b_fFit_Sector;   //!
   TBranch        *b_fFit_Bundle;   //!
   TBranch        *b_fFit_Mirror;   //!
   TBranch        *b_fFit_offset;   //!
   TBranch        *b_fFit_slope;   //!
   TBranch        *b_fFit_doffset;   //!
   TBranch        *b_fFit_dslope;   //!
   TBranch        *b_fFit_chisq;   //!
   TBranch        *b_fFit_X;   //!
   TBranch        *b_fFit_Y;   //!
   TBranch        *b_fFit_Prob;   //!
   TBranch        *b_fFit_ndf;   //!
   TBranch        *b_fFit_Flag;   //!
   TBranch        *b_fFit_last;   //!

   laser(TTree *tree=0);
   virtual ~laser();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};


laser::laser(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("2025/Cosmics/st_laser_adc_26261023_raw_0000001.laser.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("2025/Cosmics/st_laser_adc_26261023_raw_0000001.laser.root");
      }
      f->GetObject("laser",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("laser","");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

laser::~laser()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t laser::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t laser::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void laser::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_event_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_event_fBits);
   fChain->SetBranchAddress("fNtrack", &fNtrack, &b_event_fNtrack);
   fChain->SetBranchAddress("fNhit", &fNhit, &b_event_fNhit);
   fChain->SetBranchAddress("fNvertex", &fNvertex, &b_event_fNvertex);
   fChain->SetBranchAddress("fEvtHdr.fEvtNum", &fEvtHdr_fEvtNum, &b_event_fEvtHdr_fEvtNum);
   fChain->SetBranchAddress("fEvtHdr.fRun", &fEvtHdr_fRun, &b_event_fEvtHdr_fRun);
   fChain->SetBranchAddress("fEvtHdr.fDate", &fEvtHdr_fDate, &b_event_fEvtHdr_fDate);
   fChain->SetBranchAddress("fEvtHdr.fTime", &fEvtHdr_fTime, &b_event_fEvtHdr_fTime);
   fChain->SetBranchAddress("fEvtHdr.ftZero", &fEvtHdr_ftZero, &b_event_fEvtHdr_ftZero);
   fChain->SetBranchAddress("fEvtHdr.fDriVel", &fEvtHdr_fDriVel, &b_event_fEvtHdr_fDriVel);
   fChain->SetBranchAddress("fEvtHdr.fDriVelWest", &fEvtHdr_fDriVelWest, &b_event_fEvtHdr_fDriVelWest);
   fChain->SetBranchAddress("fEvtHdr.fDriVelEast", &fEvtHdr_fDriVelEast, &b_event_fEvtHdr_fDriVelEast);
   fChain->SetBranchAddress("fEvtHdr.fClock", &fEvtHdr_fClock, &b_event_fEvtHdr_fClock);
   fChain->SetBranchAddress("fEvtHdr.fTrigger", &fEvtHdr_fTrigger, &b_event_fEvtHdr_fTrigger);
   fChain->SetBranchAddress("fEvtHdr.fDriftDistance", &fEvtHdr_fDriftDistance, &b_event_fEvtHdr_fDriftDistance);
   fChain->SetBranchAddress("fEvtHdr.fInnerSectorzOffset", &fEvtHdr_fInnerSectorzOffset, &b_event_fEvtHdr_fInnerSectorzOffset);
   fChain->SetBranchAddress("fEvtHdr.fOuterSectorzOffset", &fEvtHdr_fOuterSectorzOffset, &b_event_fEvtHdr_fOuterSectorzOffset);
   fChain->SetBranchAddress("fEvtHdr.ftriggerTimeOffset", &fEvtHdr_ftriggerTimeOffset, &b_event_fEvtHdr_ftriggerTimeOffset);
   fChain->SetBranchAddress("fEvtHdr.fOnlClock", &fEvtHdr_fOnlClock, &b_event_fEvtHdr_fOnlClock);
   fChain->SetBranchAddress("fEvtHdr.fBField", &fEvtHdr_fBField, &b_event_fEvtHdr_fBField);
   fChain->SetBranchAddress("fEvtHdr.fScaleY", &fEvtHdr_fScaleY, &b_event_fEvtHdr_fScaleY);
   fChain->SetBranchAddress("fVertices", &fVertices_, &b_event_fVertices_);
   fChain->SetBranchAddress("fVertices.fUniqueID", &fVertices_fUniqueID, &b_fVertices_fUniqueID);
   fChain->SetBranchAddress("fVertices.fBits", &fVertices_fBits, &b_fVertices_fBits);
   fChain->SetBranchAddress("fVertices.mType", &fVertices_mType, &b_fVertices_mType);
   fChain->SetBranchAddress("fVertices.WestEast", &fVertices_WestEast, &b_fVertices_WestEast);
   fChain->SetBranchAddress("fVertices.Xyz.mX1", &fVertices_Xyz_mX1, &b_fVertices_Xyz_mX1);
   fChain->SetBranchAddress("fVertices.Xyz.mX2", &fVertices_Xyz_mX2, &b_fVertices_Xyz_mX2);
   fChain->SetBranchAddress("fVertices.Xyz.mX3", &fVertices_Xyz_mX3, &b_fVertices_Xyz_mX3);
   fChain->SetBranchAddress("fVertices.XyzL.mX1", &fVertices_XyzL_mX1, &b_fVertices_XyzL_mX1);
   fChain->SetBranchAddress("fVertices.XyzL.mX2", &fVertices_XyzL_mX2, &b_fVertices_XyzL_mX2);
   fChain->SetBranchAddress("fVertices.XyzL.mX3", &fVertices_XyzL_mX3, &b_fVertices_XyzL_mX3);
   fChain->SetBranchAddress("fVertices.numberOfDaughter", &fVertices_numberOfDaughter, &b_fVertices_numberOfDaughter);
   fChain->SetBranchAddress("fTracks", &fTracks_, &b_event_fTracks_);
   fChain->SetBranchAddress("fTracks.fUniqueID", fTracks_fUniqueID, &b_fTracks_fUniqueID);
   fChain->SetBranchAddress("fTracks.fBits", fTracks_fBits, &b_fTracks_fBits);
   fChain->SetBranchAddress("fTracks.Flag", fTracks_Flag, &b_fTracks_Flag);
   fChain->SetBranchAddress("fTracks.mType", fTracks_mType, &b_fTracks_mType);
   fChain->SetBranchAddress("fTracks.Vertex.mX1", fTracks_Vertex_mX1, &b_fTracks_Vertex_mX1);
   fChain->SetBranchAddress("fTracks.Vertex.mX2", fTracks_Vertex_mX2, &b_fTracks_Vertex_mX2);
   fChain->SetBranchAddress("fTracks.Vertex.mX3", fTracks_Vertex_mX3, &b_fTracks_Vertex_mX3);
   fChain->SetBranchAddress("fTracks.mSector", fTracks_mSector, &b_fTracks_mSector);
   fChain->SetBranchAddress("fTracks.mKey", fTracks_mKey, &b_fTracks_mKey);
   fChain->SetBranchAddress("fTracks.mFlag", fTracks_mFlag, &b_fTracks_mFlag);
   fChain->SetBranchAddress("fTracks.mNumberOfPossiblePointsTpc", fTracks_mNumberOfPossiblePointsTpc, &b_fTracks_mNumberOfPossiblePointsTpc);
   fChain->SetBranchAddress("fTracks.mImpactParameter", fTracks_mImpactParameter, &b_fTracks_mImpactParameter);
   fChain->SetBranchAddress("fTracks.mLength", fTracks_mLength, &b_fTracks_mLength);
   fChain->SetBranchAddress("fTracks.mNumberOfFitPointsTpc", fTracks_mNumberOfFitPointsTpc, &b_fTracks_mNumberOfFitPointsTpc);
   fChain->SetBranchAddress("fTracks.mPrimaryVertexUsedInFit", fTracks_mPrimaryVertexUsedInFit, &b_fTracks_mPrimaryVertexUsedInFit);
   fChain->SetBranchAddress("fTracks.fNdEdx", fTracks_fNdEdx, &b_fTracks_fNdEdx);
   fChain->SetBranchAddress("fTracks.fdEdx", fTracks_fdEdx, &b_fTracks_fdEdx);
   fChain->SetBranchAddress("fTracks.fgeoIn.fUniqueID", fTracks_fgeoIn_fUniqueID, &b_fTracks_fgeoIn_fUniqueID);
   fChain->SetBranchAddress("fTracks.fgeoIn.fBits", fTracks_fgeoIn_fBits, &b_fTracks_fgeoIn_fBits);
   fChain->SetBranchAddress("fTracks.fgeoIn.mModel", fTracks_fgeoIn_mModel, &b_fTracks_fgeoIn_mModel);
   fChain->SetBranchAddress("fTracks.fgeoIn.mCharge", fTracks_fgeoIn_mCharge, &b_fTracks_fgeoIn_mCharge);
   fChain->SetBranchAddress("fTracks.fgeoIn.mPsi", fTracks_fgeoIn_mPsi, &b_fTracks_fgeoIn_mPsi);
   fChain->SetBranchAddress("fTracks.fgeoIn.mCurvature", fTracks_fgeoIn_mCurvature, &b_fTracks_fgeoIn_mCurvature);
   fChain->SetBranchAddress("fTracks.fgeoIn.mDipAngle", fTracks_fgeoIn_mDipAngle, &b_fTracks_fgeoIn_mDipAngle);
   fChain->SetBranchAddress("fTracks.fgeoIn.mOrigin.mX1", fTracks_fgeoIn_mOrigin_mX1, &b_fTracks_fgeoIn_mOrigin_mX1);
   fChain->SetBranchAddress("fTracks.fgeoIn.mOrigin.mX2", fTracks_fgeoIn_mOrigin_mX2, &b_fTracks_fgeoIn_mOrigin_mX2);
   fChain->SetBranchAddress("fTracks.fgeoIn.mOrigin.mX3", fTracks_fgeoIn_mOrigin_mX3, &b_fTracks_fgeoIn_mOrigin_mX3);
   fChain->SetBranchAddress("fTracks.fgeoIn.mMomentum.mX1", fTracks_fgeoIn_mMomentum_mX1, &b_fTracks_fgeoIn_mMomentum_mX1);
   fChain->SetBranchAddress("fTracks.fgeoIn.mMomentum.mX2", fTracks_fgeoIn_mMomentum_mX2, &b_fTracks_fgeoIn_mMomentum_mX2);
   fChain->SetBranchAddress("fTracks.fgeoIn.mMomentum.mX3", fTracks_fgeoIn_mMomentum_mX3, &b_fTracks_fgeoIn_mMomentum_mX3);
   fChain->SetBranchAddress("fTracks.fgeoIn.mHelicity", fTracks_fgeoIn_mHelicity, &b_fTracks_fgeoIn_mHelicity);
   fChain->SetBranchAddress("fTracks.fgeoOut.fUniqueID", fTracks_fgeoOut_fUniqueID, &b_fTracks_fgeoOut_fUniqueID);
   fChain->SetBranchAddress("fTracks.fgeoOut.fBits", fTracks_fgeoOut_fBits, &b_fTracks_fgeoOut_fBits);
   fChain->SetBranchAddress("fTracks.fgeoOut.mModel", fTracks_fgeoOut_mModel, &b_fTracks_fgeoOut_mModel);
   fChain->SetBranchAddress("fTracks.fgeoOut.mCharge", fTracks_fgeoOut_mCharge, &b_fTracks_fgeoOut_mCharge);
   fChain->SetBranchAddress("fTracks.fgeoOut.mPsi", fTracks_fgeoOut_mPsi, &b_fTracks_fgeoOut_mPsi);
   fChain->SetBranchAddress("fTracks.fgeoOut.mCurvature", fTracks_fgeoOut_mCurvature, &b_fTracks_fgeoOut_mCurvature);
   fChain->SetBranchAddress("fTracks.fgeoOut.mDipAngle", fTracks_fgeoOut_mDipAngle, &b_fTracks_fgeoOut_mDipAngle);
   fChain->SetBranchAddress("fTracks.fgeoOut.mOrigin.mX1", fTracks_fgeoOut_mOrigin_mX1, &b_fTracks_fgeoOut_mOrigin_mX1);
   fChain->SetBranchAddress("fTracks.fgeoOut.mOrigin.mX2", fTracks_fgeoOut_mOrigin_mX2, &b_fTracks_fgeoOut_mOrigin_mX2);
   fChain->SetBranchAddress("fTracks.fgeoOut.mOrigin.mX3", fTracks_fgeoOut_mOrigin_mX3, &b_fTracks_fgeoOut_mOrigin_mX3);
   fChain->SetBranchAddress("fTracks.fgeoOut.mMomentum.mX1", fTracks_fgeoOut_mMomentum_mX1, &b_fTracks_fgeoOut_mMomentum_mX1);
   fChain->SetBranchAddress("fTracks.fgeoOut.mMomentum.mX2", fTracks_fgeoOut_mMomentum_mX2, &b_fTracks_fgeoOut_mMomentum_mX2);
   fChain->SetBranchAddress("fTracks.fgeoOut.mMomentum.mX3", fTracks_fgeoOut_mMomentum_mX3, &b_fTracks_fgeoOut_mMomentum_mX3);
   fChain->SetBranchAddress("fTracks.fgeoOut.mHelicity", fTracks_fgeoOut_mHelicity, &b_fTracks_fgeoOut_mHelicity);
   fChain->SetBranchAddress("fTracks.fDca.fUniqueID", fTracks_fDca_fUniqueID, &b_fTracks_fDca_fUniqueID);
   fChain->SetBranchAddress("fTracks.fDca.fBits", fTracks_fDca_fBits, &b_fTracks_fDca_fBits);
   fChain->SetBranchAddress("fTracks.fDca.mImp", fTracks_fDca_mImp, &b_fTracks_fDca_mImp);
   fChain->SetBranchAddress("fTracks.fDca.mZ", fTracks_fDca_mZ, &b_fTracks_fDca_mZ);
   fChain->SetBranchAddress("fTracks.fDca.mPsi", fTracks_fDca_mPsi, &b_fTracks_fDca_mPsi);
   fChain->SetBranchAddress("fTracks.fDca.mPti", fTracks_fDca_mPti, &b_fTracks_fDca_mPti);
   fChain->SetBranchAddress("fTracks.fDca.mTan", fTracks_fDca_mTan, &b_fTracks_fDca_mTan);
   fChain->SetBranchAddress("fTracks.fDca.mCurv", fTracks_fDca_mCurv, &b_fTracks_fDca_mCurv);
   fChain->SetBranchAddress("fTracks.fDca.mImpImp", fTracks_fDca_mImpImp, &b_fTracks_fDca_mImpImp);
   fChain->SetBranchAddress("fTracks.fDca.mZImp", fTracks_fDca_mZImp, &b_fTracks_fDca_mZImp);
   fChain->SetBranchAddress("fTracks.fDca.mZZ", fTracks_fDca_mZZ, &b_fTracks_fDca_mZZ);
   fChain->SetBranchAddress("fTracks.fDca.mPsiImp", fTracks_fDca_mPsiImp, &b_fTracks_fDca_mPsiImp);
   fChain->SetBranchAddress("fTracks.fDca.mPsiZ", fTracks_fDca_mPsiZ, &b_fTracks_fDca_mPsiZ);
   fChain->SetBranchAddress("fTracks.fDca.mPsiPsi", fTracks_fDca_mPsiPsi, &b_fTracks_fDca_mPsiPsi);
   fChain->SetBranchAddress("fTracks.fDca.mPtiImp", fTracks_fDca_mPtiImp, &b_fTracks_fDca_mPtiImp);
   fChain->SetBranchAddress("fTracks.fDca.mPtiZ", fTracks_fDca_mPtiZ, &b_fTracks_fDca_mPtiZ);
   fChain->SetBranchAddress("fTracks.fDca.mPtiPsi", fTracks_fDca_mPtiPsi, &b_fTracks_fDca_mPtiPsi);
   fChain->SetBranchAddress("fTracks.fDca.mPtiPti", fTracks_fDca_mPtiPti, &b_fTracks_fDca_mPtiPti);
   fChain->SetBranchAddress("fTracks.fDca.mTanImp", fTracks_fDca_mTanImp, &b_fTracks_fDca_mTanImp);
   fChain->SetBranchAddress("fTracks.fDca.mTanZ", fTracks_fDca_mTanZ, &b_fTracks_fDca_mTanZ);
   fChain->SetBranchAddress("fTracks.fDca.mTanPsi", fTracks_fDca_mTanPsi, &b_fTracks_fDca_mTanPsi);
   fChain->SetBranchAddress("fTracks.fDca.mTanPti", fTracks_fDca_mTanPti, &b_fTracks_fDca_mTanPti);
   fChain->SetBranchAddress("fTracks.fDca.mTanTan", fTracks_fDca_mTanTan, &b_fTracks_fDca_mTanTan);
   fChain->SetBranchAddress("fTracks.fpTInv", fTracks_fpTInv, &b_fTracks_fpTInv);
   fChain->SetBranchAddress("fTracks.fTheta", fTracks_fTheta, &b_fTracks_fTheta);
   fChain->SetBranchAddress("fTracks.fPhi", fTracks_fPhi, &b_fTracks_fPhi);
   fChain->SetBranchAddress("fTracks.XyzP.mX1", fTracks_XyzP_mX1, &b_fTracks_XyzP_mX1);
   fChain->SetBranchAddress("fTracks.XyzP.mX2", fTracks_XyzP_mX2, &b_fTracks_XyzP_mX2);
   fChain->SetBranchAddress("fTracks.XyzP.mX3", fTracks_XyzP_mX3, &b_fTracks_XyzP_mX3);
   fChain->SetBranchAddress("fTracks.XyzPL.mX1", fTracks_XyzPL_mX1, &b_fTracks_XyzPL_mX1);
   fChain->SetBranchAddress("fTracks.XyzPL.mX2", fTracks_XyzPL_mX2, &b_fTracks_XyzPL_mX2);
   fChain->SetBranchAddress("fTracks.XyzPL.mX3", fTracks_XyzPL_mX3, &b_fTracks_XyzPL_mX3);
   fChain->SetBranchAddress("fTracks.XyzPU.mX1", fTracks_XyzPU_mX1, &b_fTracks_XyzPU_mX1);
   fChain->SetBranchAddress("fTracks.XyzPU.mX2", fTracks_XyzPU_mX2, &b_fTracks_XyzPU_mX2);
   fChain->SetBranchAddress("fTracks.XyzPU.mX3", fTracks_XyzPU_mX3, &b_fTracks_XyzPU_mX3);
   fChain->SetBranchAddress("fTracks.XyzPB.mX1", fTracks_XyzPB_mX1, &b_fTracks_XyzPB_mX1);
   fChain->SetBranchAddress("fTracks.XyzPB.mX2", fTracks_XyzPB_mX2, &b_fTracks_XyzPB_mX2);
   fChain->SetBranchAddress("fTracks.XyzPB.mX3", fTracks_XyzPB_mX3, &b_fTracks_XyzPB_mX3);
   fChain->SetBranchAddress("fTracks.XyzPM.mX1", fTracks_XyzPM_mX1, &b_fTracks_XyzPM_mX1);
   fChain->SetBranchAddress("fTracks.XyzPM.mX2", fTracks_XyzPM_mX2, &b_fTracks_XyzPM_mX2);
   fChain->SetBranchAddress("fTracks.XyzPM.mX3", fTracks_XyzPM_mX3, &b_fTracks_XyzPM_mX3);
   fChain->SetBranchAddress("fTracks.dirP.mX1", fTracks_dirP_mX1, &b_fTracks_dirP_mX1);
   fChain->SetBranchAddress("fTracks.dirP.mX2", fTracks_dirP_mX2, &b_fTracks_dirP_mX2);
   fChain->SetBranchAddress("fTracks.dirP.mX3", fTracks_dirP_mX3, &b_fTracks_dirP_mX3);
   fChain->SetBranchAddress("fTracks.dirPL.mX1", fTracks_dirPL_mX1, &b_fTracks_dirPL_mX1);
   fChain->SetBranchAddress("fTracks.dirPL.mX2", fTracks_dirPL_mX2, &b_fTracks_dirPL_mX2);
   fChain->SetBranchAddress("fTracks.dirPL.mX3", fTracks_dirPL_mX3, &b_fTracks_dirPL_mX3);
   fChain->SetBranchAddress("fTracks.dirPU.mX1", fTracks_dirPU_mX1, &b_fTracks_dirPU_mX1);
   fChain->SetBranchAddress("fTracks.dirPU.mX2", fTracks_dirPU_mX2, &b_fTracks_dirPU_mX2);
   fChain->SetBranchAddress("fTracks.dirPU.mX3", fTracks_dirPU_mX3, &b_fTracks_dirPU_mX3);
   fChain->SetBranchAddress("fTracks.dirPB.mX1", fTracks_dirPB_mX1, &b_fTracks_dirPB_mX1);
   fChain->SetBranchAddress("fTracks.dirPB.mX2", fTracks_dirPB_mX2, &b_fTracks_dirPB_mX2);
   fChain->SetBranchAddress("fTracks.dirPB.mX3", fTracks_dirPB_mX3, &b_fTracks_dirPB_mX3);
   fChain->SetBranchAddress("fTracks.dirPM.mX1", fTracks_dirPM_mX1, &b_fTracks_dirPM_mX1);
   fChain->SetBranchAddress("fTracks.dirPM.mX2", fTracks_dirPM_mX2, &b_fTracks_dirPM_mX2);
   fChain->SetBranchAddress("fTracks.dirPM.mX3", fTracks_dirPM_mX3, &b_fTracks_dirPM_mX3);
   fChain->SetBranchAddress("fTracks.dU.mX1", fTracks_dU_mX1, &b_fTracks_dU_mX1);
   fChain->SetBranchAddress("fTracks.dU.mX2", fTracks_dU_mX2, &b_fTracks_dU_mX2);
   fChain->SetBranchAddress("fTracks.dU.mX3", fTracks_dU_mX3, &b_fTracks_dU_mX3);
   fChain->SetBranchAddress("fTracks.thePath", fTracks_thePath, &b_fTracks_thePath);
   fChain->SetBranchAddress("fTracks.Laser.IsValid", fTracks_Laser_IsValid, &b_fTracks_Laser_IsValid);
   fChain->SetBranchAddress("fTracks.Laser.Sector", fTracks_Laser_Sector, &b_fTracks_Laser_Sector);
   fChain->SetBranchAddress("fTracks.Laser.Raft", fTracks_Laser_Raft, &b_fTracks_Laser_Raft);
   fChain->SetBranchAddress("fTracks.Laser.Bundle", fTracks_Laser_Bundle, &b_fTracks_Laser_Bundle);
   fChain->SetBranchAddress("fTracks.Laser.Mirror", fTracks_Laser_Mirror, &b_fTracks_Laser_Mirror);
   fChain->SetBranchAddress("fTracks.Laser.XyzG.mX1", fTracks_Laser_XyzG_mX1, &b_fTracks_Laser_XyzG_mX1);
   fChain->SetBranchAddress("fTracks.Laser.XyzG.mX2", fTracks_Laser_XyzG_mX2, &b_fTracks_Laser_XyzG_mX2);
   fChain->SetBranchAddress("fTracks.Laser.XyzG.mX3", fTracks_Laser_XyzG_mX3, &b_fTracks_Laser_XyzG_mX3);
   fChain->SetBranchAddress("fTracks.Laser.XyzL.mX1", fTracks_Laser_XyzL_mX1, &b_fTracks_Laser_XyzL_mX1);
   fChain->SetBranchAddress("fTracks.Laser.XyzL.mX2", fTracks_Laser_XyzL_mX2, &b_fTracks_Laser_XyzL_mX2);
   fChain->SetBranchAddress("fTracks.Laser.XyzL.mX3", fTracks_Laser_XyzL_mX3, &b_fTracks_Laser_XyzL_mX3);
   fChain->SetBranchAddress("fTracks.Laser.XyzS.mX1", fTracks_Laser_XyzS_mX1, &b_fTracks_Laser_XyzS_mX1);
   fChain->SetBranchAddress("fTracks.Laser.XyzS.mX2", fTracks_Laser_XyzS_mX2, &b_fTracks_Laser_XyzS_mX2);
   fChain->SetBranchAddress("fTracks.Laser.XyzS.mX3", fTracks_Laser_XyzS_mX3, &b_fTracks_Laser_XyzS_mX3);
   fChain->SetBranchAddress("fTracks.Laser.XyzU.mX1", fTracks_Laser_XyzU_mX1, &b_fTracks_Laser_XyzU_mX1);
   fChain->SetBranchAddress("fTracks.Laser.XyzU.mX2", fTracks_Laser_XyzU_mX2, &b_fTracks_Laser_XyzU_mX2);
   fChain->SetBranchAddress("fTracks.Laser.XyzU.mX3", fTracks_Laser_XyzU_mX3, &b_fTracks_Laser_XyzU_mX3);
   fChain->SetBranchAddress("fTracks.Laser.XyzB.mX1", fTracks_Laser_XyzB_mX1, &b_fTracks_Laser_XyzB_mX1);
   fChain->SetBranchAddress("fTracks.Laser.XyzB.mX2", fTracks_Laser_XyzB_mX2, &b_fTracks_Laser_XyzB_mX2);
   fChain->SetBranchAddress("fTracks.Laser.XyzB.mX3", fTracks_Laser_XyzB_mX3, &b_fTracks_Laser_XyzB_mX3);
   fChain->SetBranchAddress("fTracks.Laser.dirG.mX1", fTracks_Laser_dirG_mX1, &b_fTracks_Laser_dirG_mX1);
   fChain->SetBranchAddress("fTracks.Laser.dirG.mX2", fTracks_Laser_dirG_mX2, &b_fTracks_Laser_dirG_mX2);
   fChain->SetBranchAddress("fTracks.Laser.dirG.mX3", fTracks_Laser_dirG_mX3, &b_fTracks_Laser_dirG_mX3);
   fChain->SetBranchAddress("fTracks.Laser.dirL.mX1", fTracks_Laser_dirL_mX1, &b_fTracks_Laser_dirL_mX1);
   fChain->SetBranchAddress("fTracks.Laser.dirL.mX2", fTracks_Laser_dirL_mX2, &b_fTracks_Laser_dirL_mX2);
   fChain->SetBranchAddress("fTracks.Laser.dirL.mX3", fTracks_Laser_dirL_mX3, &b_fTracks_Laser_dirL_mX3);
   fChain->SetBranchAddress("fTracks.Laser.dirS.mX1", fTracks_Laser_dirS_mX1, &b_fTracks_Laser_dirS_mX1);
   fChain->SetBranchAddress("fTracks.Laser.dirS.mX2", fTracks_Laser_dirS_mX2, &b_fTracks_Laser_dirS_mX2);
   fChain->SetBranchAddress("fTracks.Laser.dirS.mX3", fTracks_Laser_dirS_mX3, &b_fTracks_Laser_dirS_mX3);
   fChain->SetBranchAddress("fTracks.Laser.dirU.mX1", fTracks_Laser_dirU_mX1, &b_fTracks_Laser_dirU_mX1);
   fChain->SetBranchAddress("fTracks.Laser.dirU.mX2", fTracks_Laser_dirU_mX2, &b_fTracks_Laser_dirU_mX2);
   fChain->SetBranchAddress("fTracks.Laser.dirU.mX3", fTracks_Laser_dirU_mX3, &b_fTracks_Laser_dirU_mX3);
   fChain->SetBranchAddress("fTracks.Laser.dirB.mX1", fTracks_Laser_dirB_mX1, &b_fTracks_Laser_dirB_mX1);
   fChain->SetBranchAddress("fTracks.Laser.dirB.mX2", fTracks_Laser_dirB_mX2, &b_fTracks_Laser_dirB_mX2);
   fChain->SetBranchAddress("fTracks.Laser.dirB.mX3", fTracks_Laser_dirB_mX3, &b_fTracks_Laser_dirB_mX3);
   fChain->SetBranchAddress("fTracks.Laser.Theta", fTracks_Laser_Theta, &b_fTracks_Laser_Theta);
   fChain->SetBranchAddress("fTracks.Laser.Phi", fTracks_Laser_Phi, &b_fTracks_Laser_Phi);
   fChain->SetBranchAddress("fTracks.Laser.ThetaG", fTracks_Laser_ThetaG, &b_fTracks_Laser_ThetaG);
   fChain->SetBranchAddress("fTracks.Laser.PhiG", fTracks_Laser_PhiG, &b_fTracks_Laser_PhiG);
   fChain->SetBranchAddress("fTracks.dPhi", fTracks_dPhi, &b_fTracks_dPhi);
   fChain->SetBranchAddress("fTracks.dTheta", fTracks_dTheta, &b_fTracks_dTheta);
   fChain->SetBranchAddress("fTracks.zLastHit", fTracks_zLastHit, &b_fTracks_zLastHit);
   fChain->SetBranchAddress("fHits", &fHits_, &b_event_fHits_);
   fChain->SetBranchAddress("fHits.fUniqueID", fHits_fUniqueID, &b_fHits_fUniqueID);
   fChain->SetBranchAddress("fHits.fBits", fHits_fBits, &b_fHits_fBits);
   fChain->SetBranchAddress("fHits.sector", fHits_sector, &b_fHits_sector);
   fChain->SetBranchAddress("fHits.row", fHits_row, &b_fHits_row);
   fChain->SetBranchAddress("fHits.charge", fHits_charge, &b_fHits_charge);
   fChain->SetBranchAddress("fHits.flag", fHits_flag, &b_fHits_flag);
   fChain->SetBranchAddress("fHits.usedInFit", fHits_usedInFit, &b_fHits_usedInFit);
   fChain->SetBranchAddress("fHits.xyz.mX1", fHits_xyz_mX1, &b_fHits_xyz_mX1);
   fChain->SetBranchAddress("fHits.xyz.mX2", fHits_xyz_mX2, &b_fHits_xyz_mX2);
   fChain->SetBranchAddress("fHits.xyz.mX3", fHits_xyz_mX3, &b_fHits_xyz_mX3);
   fChain->SetBranchAddress("fHits.xyzL.mX1", fHits_xyzL_mX1, &b_fHits_xyzL_mX1);
   fChain->SetBranchAddress("fHits.xyzL.mX2", fHits_xyzL_mX2, &b_fHits_xyzL_mX2);
   fChain->SetBranchAddress("fHits.xyzL.mX3", fHits_xyzL_mX3, &b_fHits_xyzL_mX3);
   fChain->SetBranchAddress("fHits.xyzS.mX1", fHits_xyzS_mX1, &b_fHits_xyzS_mX1);
   fChain->SetBranchAddress("fHits.xyzS.mX2", fHits_xyzS_mX2, &b_fHits_xyzS_mX2);
   fChain->SetBranchAddress("fHits.xyzS.mX3", fHits_xyzS_mX3, &b_fHits_xyzS_mX3);
   fChain->SetBranchAddress("fHits.xyzTpcL.mX1", fHits_xyzTpcL_mX1, &b_fHits_xyzTpcL_mX1);
   fChain->SetBranchAddress("fHits.xyzTpcL.mX2", fHits_xyzTpcL_mX2, &b_fHits_xyzTpcL_mX2);
   fChain->SetBranchAddress("fHits.xyzTpcL.mX3", fHits_xyzTpcL_mX3, &b_fHits_xyzTpcL_mX3);
   fChain->SetBranchAddress("fHits.pad", fHits_pad, &b_fHits_pad);
   fChain->SetBranchAddress("fHits.tbk", fHits_tbk, &b_fHits_tbk);
   fChain->SetBranchAddress("fHits.trackKey", fHits_trackKey, &b_fHits_trackKey);
   fChain->SetBranchAddress("fHits.adc", fHits_adc, &b_fHits_adc);
   fChain->SetBranchAddress("fFit", &fFit_, &b_event_fFit_);
   fChain->SetBranchAddress("fFit.fUniqueID", fFit_fUniqueID, &b_fFit_fUniqueID);
   fChain->SetBranchAddress("fFit.fBits", fFit_fBits, &b_fFit_fBits);
   fChain->SetBranchAddress("fFit.first[1]", fFit_first, &b_fFit_first);
   fChain->SetBranchAddress("fFit.N", fFit_N, &b_fFit_N);
   fChain->SetBranchAddress("fFit.Sector", fFit_Sector, &b_fFit_Sector);
   fChain->SetBranchAddress("fFit.Bundle[42]", fFit_Bundle, &b_fFit_Bundle);
   fChain->SetBranchAddress("fFit.Mirror[42]", fFit_Mirror, &b_fFit_Mirror);
   fChain->SetBranchAddress("fFit.offset", fFit_offset, &b_fFit_offset);
   fChain->SetBranchAddress("fFit.slope", fFit_slope, &b_fFit_slope);
   fChain->SetBranchAddress("fFit.doffset", fFit_doffset, &b_fFit_doffset);
   fChain->SetBranchAddress("fFit.dslope", fFit_dslope, &b_fFit_dslope);
   fChain->SetBranchAddress("fFit.chisq", fFit_chisq, &b_fFit_chisq);
   fChain->SetBranchAddress("fFit.X[42]", fFit_X, &b_fFit_X);
   fChain->SetBranchAddress("fFit.Y[42]", fFit_Y, &b_fFit_Y);
   fChain->SetBranchAddress("fFit.Prob", fFit_Prob, &b_fFit_Prob);
   fChain->SetBranchAddress("fFit.ndf", fFit_ndf, &b_fFit_ndf);
   fChain->SetBranchAddress("fFit.Flag[42]", fFit_Flag, &b_fFit_Flag);
   fChain->SetBranchAddress("fFit.last[1]", fFit_last, &b_fFit_last);
   Notify();
}

Bool_t laser::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void laser::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t laser::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

void laser::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L laser.C
//      Root > laser t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      Int_t Ntrack = fNtrack;
      for (Int_t tr = 0; tr < Ntrack; tr++) {
	if (! fTracks_Laser_IsValid[tr]) continue; 
	if (TMath::Abs(fTracks_fDca_mCurv[tr]) > 2e-3) continue;
	if (fTracks_mLength[tr] < 60.0) continue;
	Int_t sector = fTracks_mSector[tr];
        if (sector < 1 || sector > 24) continue;
        Int_t s = fTracks_Laser_Sector[tr]/2;
        Int_t r = fTracks_Laser_Raft[tr];
        Int_t b = fTracks_Laser_Bundle[tr];
	Int_t m = fTracks_Laser_Mirror[tr];
        if (s < 1 || s > 12) continue;
        if (b < 1 || b >  6) continue;
        if (m < 1 || m >  7) continue;
	Double_t sbm = m + 7*(b - 1 + 6*(s - 1));
        TVector3 dU(fTracks_dU_mX1[tr],fTracks_dU_mX2[tr],fTracks_dU_mX3[tr]);
        Double_t dPhi = fTracks_dPhi[tr];
        Double_t dTheta = fTracks_dTheta[tr];
	if (! dXY[s-1][b-1][m-1]) {
	  dXY[s-1][b-1][m-1] = new TH2F(Form("dXY_s%i_b%i_m%i",2*s,b,m),Form("dY versus dX for sector %i, bundle %i, mirror %i ; dX (cm) ; dY (cm)",2*s,b,m), 500, -2.5, 2.5, 500, -2.5, 2.5);
	  dPT[s-1][b-1][m-1] = new TH2F(Form("dPT_s%i_b%i_m%i",2*s,b,m),Form("d#Theta versus d#Phi for sector %i, bundle %i, mirror %i ; d#Phi (mrad); d#Theta (mrad)",2*s,b,m), 500, -25.0, 25.0, 500, -25.0, 25.0);
	}
	dXY[s-1][b-1][m-1]->Fill(dU.X(),dU.Y());
	dPT[s-1][b-1][m-1]->Fill(1e3*dPhi,1e3*dTheta);
	pf[0]->Fill(sbm, dU.X());
	pf[1]->Fill(sbm, dU.Y());
	pf[2]->Fill(sbm, 1e3*dPhi);
	pf[3]->Fill(sbm, 1e3*dTheta);
      }
   }
}

//_________________________________________________________________________________
void LaserT(TChain *tChain=0) {
  if (! tChain) return;
  laser T(tChain);
  TFile *fOut = new TFile("LaserTBP.root","recreate");
  pf[0] = new TProfile("dX","dx versus sbm",504,0.5,504.5,"S");
  pf[1] = new TProfile("dY","dY versus sbm",504,0.5,504.5,"S");
  pf[2] = new TProfile("dPhi","d#Phi (mrad) versus sbm",504,0.5,504.5,"S");
  pf[3] = new TProfile("dTheta","d#Theta (mrad)  versus sbm",504,0.5,504.5,"S");
  T.Loop();
  fOut->Write();
}
//________________________________________________________________________________
void Init() {
  for (Int_t s = 1; s <= 12; s++)
    for (Int_t b = 1; b <= 6; b++)
      for (Int_t m = 1; m <= 7; m++) {
	dXY[s-1][b-1][m-1] = (TH2F *) gDirectory->Get(Form("dXY_s%i_b%i_m%i",2*s,b,m));
	dPT[s-1][b-1][m-1] = (TH2F *) gDirectory->Get(Form("dPT_s%i_b%i_m%i",2*s,b,m));
      }
  pf[0] = (TProfile *) gDirectory->Get("dX");
  pf[1] = (TProfile *) gDirectory->Get("dY");
  pf[2] = (TProfile *) gDirectory->Get("dPhi");
  pf[3] = (TProfile *) gDirectory->Get("dTheta");
}
//________________________________________________________________________________
void PrintH2(TH2 *h2, Int_t s, Int_t b, Int_t m, const Char_t *cdX = "dX", const Char_t *cdY = "dY", Int_t ipf = 0) {
  if (! h2) return;
  Double_t e = h2->GetEntries();
  cout << Form("%s, entries = %10.5g, sector: %2i, bundle: %2i, mirror: %2i",h2->GetName(),e,2*s,b,m);
  corr[s][b][m].entries = e;
  if (e < 1000.) {
    cout << endl;
    return;
  }
  Double_t dX = h2->GetMean(1), ddX = h2->GetRMS(1), ux = dX/ddX;
  Double_t dY = h2->GetMean(2), ddY = h2->GetRMS(2), uy = dY/ddY;
  Double_t cor = h2->GetCorrelationFactor();
  Double_t chi2 = (ux*ux - 2*cor*ux*uy + uy*uy)/(1 - cor*cor);;
  cout << Form(", %s = %8.4f +/- %8.4f, %s = %8.4f +/- %8.4f, corr = %8.4f, chi2 = %10.2f",cdX, dX, ddX, cdY, dY, ddY, cor, chi2);
  Int_t sbm = m + 7*(b - 1 + 6*(s - 1));
  for (Int_t i = ipf; i <= ipf+1; i++) {
    Double_t ent = pf[i]->GetBinEntries(sbm);
    Double_t xm  = pf[i]->GetBinContent(sbm);
    Double_t err = pf[i]->GetBinError(sbm);
    Double_t *XX = &corr[s][b][m].dX;
    XX[2*i]   = xm;
    XX[2*i+1] = err;
    if (i == ipf) {
      cout << "\t" << cdX;
    } else  {
      cout << "\t" << cdY;
    }
    cout << Form("= %8.4f +/- %8.4f", xm, err);
  }
  cout << endl;
}
//________________________________________________________________________________
void Draw() {
  Init();
  TCanvas *c1 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("c1");
  if (! c1) c1 = new TCanvas("c1","c1",1200,800);
  else      c1->Clear();
  c1->Divide(2,1);
  for (Int_t s = 1; s <=12; s++)
    for (Int_t b = 1; b <=6; b++)
      for (Int_t m = 1; m <=7; m++) {
	if (! dXY[s-1][b-1][m-1] && ! dPT[s-1][b-1][m-1]) continue;
	if (dXY[s-1][b-1][m-1]) {
	  c1->cd(1)->SetLogz(1);
	  dXY[s-1][b-1][m-1]->Draw("colz");
	  PrintH2(dXY[s-1][b-1][m-1],s,b,m);
	}
	if (dPT[s-1][b-1][m-1]) {
	  c1->cd(2)->SetLogz(1);
	  dPT[s-1][b-1][m-1]->Draw("colz");
	  PrintH2(dPT[s-1][b-1][m-1],s,b,m,"dP","dT",2);
	}
	
	if (corr[s][b][m].entries > 1000.) {
	  cout << "corr[" << s << "][" << b << "][" << m << "] = " << corr[s][b][m] << endl;
	}
	c1->Update();
	if (! gROOT->IsBatch() && Ask()) return;
      } 
}
//________________________________________________________________________________
