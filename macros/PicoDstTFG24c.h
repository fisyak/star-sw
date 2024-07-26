//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jul 26 11:06:38 2024 by ROOT version 5.34/39
// from TTree PicoDst/StPicoDst
// found on file: st_physics_20183003_raw_6500008,1,29203.picoDst.root
//////////////////////////////////////////////////////////

#ifndef PicoDstTFG24c_h
#define PicoDstTFG24c_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TClonesArray.h>
#include <utility>


class PicoDstTFG24c {
public :
// Fixed size dimensions of array or collections stored in the TTree if any.
  enum {
   kMaxEvent = 1,
   kMaxTrack = 1265,
   kMaxEmcTrigger = 1,
   kMaxMtdTrigger = 1,
   kMaxBTowHit = 4800,
   kMaxBTofHit = 460,
   kMaxMtdHit = 1,
   kMaxBbcHit = 28,
   kMaxEpdHit = 379,
   kMaxFmsHit = 1,
   kMaxEmcPidTraits = 1,
   kMaxBTofPidTraits = 101,
   kMaxMtdPidTraits = 1,
   kMaxTrackCovMatrix = 1265,
   kMaxBEmcSmdEHit = 1,
   kMaxBEmcSmdPHit = 1,
   kMaxETofHit = 95,
   kMaxETofPidTraits = 27,
   kMaxMcVertex = 1,
   kMaxMcTrack = 1,
   };
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           Event_;
   TString         Event_mProductionVersion[kMaxEvent];
   Int_t           Event_mRunId[kMaxEvent];   //[Event_]
   Int_t           Event_mEventId[kMaxEvent];   //[Event_]
   UShort_t        Event_mFillId[kMaxEvent];   //[Event_]
   Float_t         Event_mBField[kMaxEvent];   //[Event_]
   Int_t           Event_mTime[kMaxEvent];   //[Event_]
   Float_t         Event_mPrimaryVertexX[kMaxEvent];   //[Event_]
   Float_t         Event_mPrimaryVertexY[kMaxEvent];   //[Event_]
   Float_t         Event_mPrimaryVertexZ[kMaxEvent];   //[Event_]
   Float_t         Event_mPrimaryVertexErrorX[kMaxEvent];   //[Event_]
   Float_t         Event_mPrimaryVertexErrorY[kMaxEvent];   //[Event_]
   Float_t         Event_mPrimaryVertexErrorZ[kMaxEvent];   //[Event_]
   Float16_t       Event_mPrimaryVertexCorr[kMaxEvent][3];   //[Event_]
   Float_t         Event_mRanking[kMaxEvent];   //[Event_]
   UShort_t        Event_mNBEMCMatch[kMaxEvent];   //[Event_]
   UShort_t        Event_mNBTOFMatch[kMaxEvent];   //[Event_]
   vector<unsigned int> Event_mTriggerIds[kMaxEvent];
   UShort_t        Event_mRefMultFtpcEast[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMultFtpcWest[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMultNeg[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMultPos[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMult2NegEast[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMult2PosEast[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMult2NegWest[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMult2PosWest[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMult3NegEast[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMult3PosEast[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMult3NegWest[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMult3PosWest[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMult4NegEast[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMult4PosEast[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMult4NegWest[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMult4PosWest[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMultHalfNegEast[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMultHalfPosEast[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMultHalfNegWest[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMultHalfPosWest[kMaxEvent];   //[Event_]
   UShort_t        Event_mGRefMult[kMaxEvent];   //[Event_]
   UShort_t        Event_mNumberOfGlobalTracks[kMaxEvent];   //[Event_]
   UShort_t        Event_mbTofTrayMultiplicity[kMaxEvent];   //[Event_]
   UShort_t        Event_mNHitsHFT[kMaxEvent][4];   //[Event_]
   UChar_t         Event_mNVpdHitsEast[kMaxEvent];   //[Event_]
   UChar_t         Event_mNVpdHitsWest[kMaxEvent];   //[Event_]
   UShort_t        Event_mNTofT0[kMaxEvent];   //[Event_]
   Float_t         Event_mVzVpd[kMaxEvent];   //[Event_]
   UShort_t        Event_mNTofT0Can[kMaxEvent];   //[Event_]
   Int_t           Event_mTStart[kMaxEvent];   //[Event_]
   Int_t           Event_mTCanFirst[kMaxEvent];   //[Event_]
   Int_t           Event_mTCanLast[kMaxEvent];   //[Event_]
   UChar_t         Event_mNVpdEGoodHits[kMaxEvent];   //[Event_]
   UChar_t         Event_mNVpdWGoodHits[kMaxEvent];   //[Event_]
   Int_t           Event_mEarliestVpdEHit[kMaxEvent];   //[Event_]
   Int_t           Event_mEarliestVpdWHit[kMaxEvent];   //[Event_]
   Int_t           Event_mClosestVpdEHit[kMaxEvent];   //[Event_]
   Int_t           Event_mClosestVpdWHit[kMaxEvent];   //[Event_]
   Int_t           Event_mLatestVpdEHit[kMaxEvent];   //[Event_]
   Int_t           Event_mLatestVpdWHit[kMaxEvent];   //[Event_]
   UInt_t          Event_mZDCx[kMaxEvent];   //[Event_]
   UInt_t          Event_mBBCx[kMaxEvent];   //[Event_]
   Float16_t       Event_mBackgroundRate[kMaxEvent];   //[Event_]
   Float16_t       Event_mBbcBlueBackgroundRate[kMaxEvent];   //[Event_]
   Float16_t       Event_mBbcYellowBackgroundRate[kMaxEvent];   //[Event_]
   Float16_t       Event_mBbcEastRate[kMaxEvent];   //[Event_]
   Float16_t       Event_mBbcWestRate[kMaxEvent];   //[Event_]
   Float16_t       Event_mZdcEastRate[kMaxEvent];   //[Event_]
   Float16_t       Event_mZdcWestRate[kMaxEvent];   //[Event_]
   UShort_t        Event_mZdcSumAdcEast[kMaxEvent];   //[Event_]
   UShort_t        Event_mZdcSumAdcWest[kMaxEvent];   //[Event_]
   UShort_t        Event_mZdcSmdEastHorizontal[kMaxEvent][8];   //[Event_]
   UShort_t        Event_mZdcSmdEastVertical[kMaxEvent][8];   //[Event_]
   UShort_t        Event_mZdcSmdWestHorizontal[kMaxEvent][8];   //[Event_]
   UShort_t        Event_mZdcSmdWestVertical[kMaxEvent][8];   //[Event_]
   UShort_t        Event_mBbcAdcEast[kMaxEvent][24];   //[Event_]
   UShort_t        Event_mBbcAdcWest[kMaxEvent][24];   //[Event_]
   UChar_t         Event_mHighTowerThreshold[kMaxEvent][4];   //[Event_]
   UChar_t         Event_mJetPatchThreshold[kMaxEvent][4];   //[Event_]
   UChar_t         Event_mBunchCrossId[kMaxEvent];   //[Event_]
   UShort_t        Event_mETofHitMultiplicity[kMaxEvent];   //[Event_]
   UShort_t        Event_mETofDigiMultiplicity[kMaxEvent];   //[Event_]
   Bool_t          Event_mETofGoodEventFlag[kMaxEvent][1728];   //[Event_]
   Bool_t          Event_mETofHasPulsersFlag[kMaxEvent][108];   //[Event_]
   UShort_t        Event_mNumberOfPrimaryTracks[kMaxEvent];   //[Event_]
   UShort_t        Event_mZdcUnAttenuated[kMaxEvent][2];   //[Event_]
   Int_t           Track_;
   UShort_t        Track_mId[kMaxTrack];   //[Track_]
   UShort_t        Track_mChi2[kMaxTrack];   //[Track_]
   Float_t         Track_mPMomentumX[kMaxTrack];   //[Track_]
   Float_t         Track_mPMomentumY[kMaxTrack];   //[Track_]
   Float_t         Track_mPMomentumZ[kMaxTrack];   //[Track_]
   Float_t         Track_mGMomentumX[kMaxTrack];   //[Track_]
   Float_t         Track_mGMomentumY[kMaxTrack];   //[Track_]
   Float_t         Track_mGMomentumZ[kMaxTrack];   //[Track_]
   Float_t         Track_mOriginX[kMaxTrack];   //[Track_]
   Float_t         Track_mOriginY[kMaxTrack];   //[Track_]
   Float_t         Track_mOriginZ[kMaxTrack];   //[Track_]
   Float16_t       Track_mDedx[kMaxTrack];   //[Track_]
   Float16_t       Track_mDedxError[kMaxTrack];   //[Track_]
   Float_t         Track_mDnDx[kMaxTrack];   //[Track_]
   Float_t         Track_mDnDxError[kMaxTrack];   //[Track_]
   Char_t          Track_mNHitsFit[kMaxTrack];   //[Track_]
   UChar_t         Track_mNHitsMax[kMaxTrack];   //[Track_]
   UChar_t         Track_mNHitsDedx[kMaxTrack];   //[Track_]
   Short_t         Track_mNSigmaPion[kMaxTrack];   //[Track_]
   Short_t         Track_mNSigmaKaon[kMaxTrack];   //[Track_]
   Short_t         Track_mNSigmaProton[kMaxTrack];   //[Track_]
   Short_t         Track_mNSigmaElectron[kMaxTrack];   //[Track_]
   UInt_t          Track_mTopologyMap[kMaxTrack][3];   //[Track_]
   Short_t         Track_mBEmcPidTraitsIndex[kMaxTrack];   //[Track_]
   Short_t         Track_mBTofPidTraitsIndex[kMaxTrack];   //[Track_]
   Short_t         Track_mMtdPidTraitsIndex[kMaxTrack];   //[Track_]
   Short_t         Track_mETofPidTraitsIndex[kMaxTrack];   //[Track_]
   Short_t         Track_mBEmcMatchedTowerIndex[kMaxTrack];   //[Track_]
   Char_t          Track_mStatus[kMaxTrack];   //[Track_]
   UShort_t        Track_mIdTruth[kMaxTrack];   //[Track_]
   UShort_t        Track_mQATruth[kMaxTrack];   //[Track_]
   Char_t          Track_mVertexIndex[kMaxTrack];   //[Track_]
   Int_t           EmcTrigger_;
   UChar_t         EmcTrigger_mFlag[kMaxEmcTrigger];   //[EmcTrigger_]
   UShort_t        EmcTrigger_mId[kMaxEmcTrigger];   //[EmcTrigger_]
   UShort_t        EmcTrigger_mAdc[kMaxEmcTrigger];   //[EmcTrigger_]
   vector<unsigned short> EmcTrigger_mSmdE[kMaxEmcTrigger];
   vector<unsigned short> EmcTrigger_mSmdP[kMaxEmcTrigger];
   Int_t           MtdTrigger_;
   UShort_t        MtdTrigger_mVpdTacSum[kMaxMtdTrigger];   //[MtdTrigger_]
   UInt_t          MtdTrigger_mTHUBtime[kMaxMtdTrigger][2];   //[MtdTrigger_]
   UShort_t        MtdTrigger_mQTtacSum[kMaxMtdTrigger][8][8];   //[MtdTrigger_]
   UShort_t        MtdTrigger_mMT101Tac[kMaxMtdTrigger][8][2];   //[MtdTrigger_]
   UChar_t         MtdTrigger_mMT101Id[kMaxMtdTrigger][8][2];   //[MtdTrigger_]
   UInt_t          MtdTrigger_mTF201TriggerBit[kMaxMtdTrigger];   //[MtdTrigger_]
   Char_t          MtdTrigger_mShouldHaveRejectEvent[kMaxMtdTrigger];   //[MtdTrigger_]
   Int_t           BTowHit_;
   UShort_t        BTowHit_mAdc[kMaxBTowHit];   //[BTowHit_]
   Short_t         BTowHit_mE[kMaxBTowHit];   //[BTowHit_]
   Int_t           BTofHit_;
   Short_t         BTofHit_mId[kMaxBTofHit];   //[BTofHit_]
   Int_t           MtdHit_;
   Short_t         MtdHit_mgChannel[kMaxMtdHit];   //[MtdHit_]
   UChar_t         MtdHit_mTriggerFlag[kMaxMtdHit];   //[MtdHit_]
   Float_t         MtdHit_mLeadingEdgeTime_first[kMaxMtdHit];   //[MtdHit_]
   Float_t         MtdHit_mLeadingEdgeTime_second[kMaxMtdHit];   //[MtdHit_]
   Float_t         MtdHit_mTrailingEdgeTime_first[kMaxMtdHit];   //[MtdHit_]
   Float_t         MtdHit_mTrailingEdgeTime_second[kMaxMtdHit];   //[MtdHit_]
   Int_t           BbcHit_;
   Short_t         BbcHit_mId[kMaxBbcHit];   //[BbcHit_]
   Int_t           BbcHit_mQTdata[kMaxBbcHit];   //[BbcHit_]
   Int_t           EpdHit_;
   Short_t         EpdHit_mId[kMaxEpdHit];   //[EpdHit_]
   Int_t           EpdHit_mQTdata[kMaxEpdHit];   //[EpdHit_]
   Float_t         EpdHit_mnMIP[kMaxEpdHit];   //[EpdHit_]
   Int_t           FmsHit_;
   UShort_t        FmsHit_mChannelDetectorId[kMaxFmsHit];   //[FmsHit_]
   UShort_t        FmsHit_mAdc[kMaxFmsHit];   //[FmsHit_]
   Int_t           EmcPidTraits_;
   Short_t         EmcPidTraits_mTrackIndex[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mBemcId[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mBemcAdc0[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mBemcE0[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mBemcE[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mBemcZDist[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mBemcPhiDist[kMaxEmcPidTraits];   //[EmcPidTraits_]
   UChar_t         EmcPidTraits_mBemcSmdNEta[kMaxEmcPidTraits];   //[EmcPidTraits_]
   UChar_t         EmcPidTraits_mBemcSmdNPhi[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mBtowId[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Char_t          EmcPidTraits_mBtowId23[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mBtowE[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mBtowE2[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mBtowE3[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mBtowEtaDist[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mBtowPhiDist[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Int_t           BTofPidTraits_;
   Short_t         BTofPidTraits_mTrackIndex[kMaxBTofPidTraits];   //[BTofPidTraits_]
   Short_t         BTofPidTraits_mBTofCellId[kMaxBTofPidTraits];   //[BTofPidTraits_]
   UChar_t         BTofPidTraits_mBTofMatchFlag[kMaxBTofPidTraits];   //[BTofPidTraits_]
   Float_t         BTofPidTraits_mBTof[kMaxBTofPidTraits];   //[BTofPidTraits_]
   UShort_t        BTofPidTraits_mBTofBeta[kMaxBTofPidTraits];   //[BTofPidTraits_]
   Short_t         BTofPidTraits_mBTofYLocal[kMaxBTofPidTraits];   //[BTofPidTraits_]
   Short_t         BTofPidTraits_mBTofZLocal[kMaxBTofPidTraits];   //[BTofPidTraits_]
   Short_t         BTofPidTraits_mBTofHitPosX[kMaxBTofPidTraits];   //[BTofPidTraits_]
   Short_t         BTofPidTraits_mBTofHitPosY[kMaxBTofPidTraits];   //[BTofPidTraits_]
   Short_t         BTofPidTraits_mBTofHitPosZ[kMaxBTofPidTraits];   //[BTofPidTraits_]
   Short_t         BTofPidTraits_mNSigmaElectron[kMaxBTofPidTraits];   //[BTofPidTraits_]
   Short_t         BTofPidTraits_mNSigmaPion[kMaxBTofPidTraits];   //[BTofPidTraits_]
   Short_t         BTofPidTraits_mNSigmaKaon[kMaxBTofPidTraits];   //[BTofPidTraits_]
   Short_t         BTofPidTraits_mNSigmaProton[kMaxBTofPidTraits];   //[BTofPidTraits_]
   Int_t           MtdPidTraits_;
   Short_t         MtdPidTraits_mTrackIndex[kMaxMtdPidTraits];   //[MtdPidTraits_]
   Short_t         MtdPidTraits_mMtdHitIndex[kMaxMtdPidTraits];   //[MtdPidTraits_]
   Char_t          MtdPidTraits_mMatchFlag[kMaxMtdPidTraits];   //[MtdPidTraits_]
   Short_t         MtdPidTraits_mDeltaY[kMaxMtdPidTraits];   //[MtdPidTraits_]
   Short_t         MtdPidTraits_mDeltaZ[kMaxMtdPidTraits];   //[MtdPidTraits_]
   Float_t         MtdPidTraits_mDeltaTimeOfFlight[kMaxMtdPidTraits];   //[MtdPidTraits_]
   UShort_t        MtdPidTraits_mBeta[kMaxMtdPidTraits];   //[MtdPidTraits_]
   Short_t         MtdPidTraits_mMtdHitChan[kMaxMtdPidTraits];   //[MtdPidTraits_]
   Int_t           TrackCovMatrix_;
   Float16_t       TrackCovMatrix_mImp[kMaxTrackCovMatrix];   //[TrackCovMatrix_]
   Float16_t       TrackCovMatrix_mZ[kMaxTrackCovMatrix];   //[TrackCovMatrix_]
   Float16_t       TrackCovMatrix_mPsi[kMaxTrackCovMatrix];   //[TrackCovMatrix_]
   Float16_t       TrackCovMatrix_mPti[kMaxTrackCovMatrix];   //[TrackCovMatrix_]
   Float16_t       TrackCovMatrix_mTan[kMaxTrackCovMatrix];   //[TrackCovMatrix_]
   Float16_t       TrackCovMatrix_mCurv[kMaxTrackCovMatrix];   //[TrackCovMatrix_]
   Float16_t       TrackCovMatrix_mSigma[kMaxTrackCovMatrix][5];   //[TrackCovMatrix_]
   Float16_t       TrackCovMatrix_mCorr[kMaxTrackCovMatrix][10];   //[TrackCovMatrix_]
   Float16_t       TrackCovMatrix_mpIn[kMaxTrackCovMatrix];   //[TrackCovMatrix_]
   Float16_t       TrackCovMatrix_mpOut[kMaxTrackCovMatrix];   //[TrackCovMatrix_]
   Int_t           BEmcSmdEHit_;
   Short_t         BEmcSmdEHit_mId[kMaxBEmcSmdEHit];   //[BEmcSmdEHit_]
   Short_t         BEmcSmdEHit_mAdc[kMaxBEmcSmdEHit];   //[BEmcSmdEHit_]
   Float_t         BEmcSmdEHit_mEnergy[kMaxBEmcSmdEHit];   //[BEmcSmdEHit_]
   Int_t           BEmcSmdPHit_;
   Short_t         BEmcSmdPHit_mId[kMaxBEmcSmdPHit];   //[BEmcSmdPHit_]
   Short_t         BEmcSmdPHit_mAdc[kMaxBEmcSmdPHit];   //[BEmcSmdPHit_]
   Float_t         BEmcSmdPHit_mEnergy[kMaxBEmcSmdPHit];   //[BEmcSmdPHit_]
   Int_t           ETofHit_;
   UChar_t         ETofHit_mGeomId[kMaxETofHit];   //[ETofHit_]
   Short_t         ETofHit_mLocalX[kMaxETofHit];   //[ETofHit_]
   Short_t         ETofHit_mLocalY[kMaxETofHit];   //[ETofHit_]
   UChar_t         ETofHit_mClusterSize[kMaxETofHit];   //[ETofHit_]
   Float_t         ETofHit_mLeadingEdgeTime[kMaxETofHit];   //[ETofHit_]
   UShort_t        ETofHit_mTimeOverThreshold[kMaxETofHit];   //[ETofHit_]
   Int_t           ETofPidTraits_;
   Short_t         ETofPidTraits_mTrackIndex[kMaxETofPidTraits];   //[ETofPidTraits_]
   Short_t         ETofPidTraits_mHitIndex[kMaxETofPidTraits];   //[ETofPidTraits_]
   Char_t          ETofPidTraits_mMatchFlag[kMaxETofPidTraits];   //[ETofPidTraits_]
   Float_t         ETofPidTraits_mTimeOfFlight[kMaxETofPidTraits];   //[ETofPidTraits_]
   UShort_t        ETofPidTraits_mBeta[kMaxETofPidTraits];   //[ETofPidTraits_]
   Short_t         ETofPidTraits_mDeltaX[kMaxETofPidTraits];   //[ETofPidTraits_]
   Short_t         ETofPidTraits_mDeltaY[kMaxETofPidTraits];   //[ETofPidTraits_]
   Short_t         ETofPidTraits_mCrossingX[kMaxETofPidTraits];   //[ETofPidTraits_]
   Short_t         ETofPidTraits_mCrossingY[kMaxETofPidTraits];   //[ETofPidTraits_]
   Short_t         ETofPidTraits_mCrossingZ[kMaxETofPidTraits];   //[ETofPidTraits_]
   Int_t           McVertex_;
   Int_t           McVertex_mId[kMaxMcVertex];   //[McVertex_]
   UShort_t        McVertex_mNoDaughters[kMaxMcVertex];   //[McVertex_]
   Int_t           McVertex_mIdParTrk[kMaxMcVertex];   //[McVertex_]
   Int_t           McVertex_mIsInterm[kMaxMcVertex];   //[McVertex_]
   Float_t         McVertex_mTime[kMaxMcVertex];   //[McVertex_]
   Float_t         McVertex_mVx[kMaxMcVertex];   //[McVertex_]
   Float_t         McVertex_mVy[kMaxMcVertex];   //[McVertex_]
   Float_t         McVertex_mVz[kMaxMcVertex];   //[McVertex_]
   Int_t           McTrack_;
   UShort_t        McTrack_mId[kMaxMcTrack];   //[McTrack_]
   Int_t           McTrack_mGePid[kMaxMcTrack];   //[McTrack_]
   Char_t          McTrack_mCharge[kMaxMcTrack];   //[McTrack_]
   UChar_t         McTrack_mHits[kMaxMcTrack][30];   //[McTrack_]
   Float_t         McTrack_mPx[kMaxMcTrack];   //[McTrack_]
   Float_t         McTrack_mPy[kMaxMcTrack];   //[McTrack_]
   Float_t         McTrack_mPz[kMaxMcTrack];   //[McTrack_]
   Float_t         McTrack_mE[kMaxMcTrack];   //[McTrack_]
   Bool_t          McTrack_mIsFromShower[kMaxMcTrack];   //[McTrack_]
   Short_t         McTrack_mIdVtxStart[kMaxMcTrack];   //[McTrack_]
   Short_t         McTrack_mIdVtxStop[kMaxMcTrack];   //[McTrack_]
   Short_t         McTrack_mIdVtxItrmd[kMaxMcTrack];   //[McTrack_]

   // List of branches
   TBranch        *b_Event_;   //!
   TBranch        *b_Event_mProductionVersion;   //!
   TBranch        *b_Event_mRunId;   //!
   TBranch        *b_Event_mEventId;   //!
   TBranch        *b_Event_mFillId;   //!
   TBranch        *b_Event_mBField;   //!
   TBranch        *b_Event_mTime;   //!
   TBranch        *b_Event_mPrimaryVertexX;   //!
   TBranch        *b_Event_mPrimaryVertexY;   //!
   TBranch        *b_Event_mPrimaryVertexZ;   //!
   TBranch        *b_Event_mPrimaryVertexErrorX;   //!
   TBranch        *b_Event_mPrimaryVertexErrorY;   //!
   TBranch        *b_Event_mPrimaryVertexErrorZ;   //!
   TBranch        *b_Event_mPrimaryVertexCorr;   //!
   TBranch        *b_Event_mRanking;   //!
   TBranch        *b_Event_mNBEMCMatch;   //!
   TBranch        *b_Event_mNBTOFMatch;   //!
   TBranch        *b_Event_mTriggerIds;   //!
   TBranch        *b_Event_mRefMultFtpcEast;   //!
   TBranch        *b_Event_mRefMultFtpcWest;   //!
   TBranch        *b_Event_mRefMultNeg;   //!
   TBranch        *b_Event_mRefMultPos;   //!
   TBranch        *b_Event_mRefMult2NegEast;   //!
   TBranch        *b_Event_mRefMult2PosEast;   //!
   TBranch        *b_Event_mRefMult2NegWest;   //!
   TBranch        *b_Event_mRefMult2PosWest;   //!
   TBranch        *b_Event_mRefMult3NegEast;   //!
   TBranch        *b_Event_mRefMult3PosEast;   //!
   TBranch        *b_Event_mRefMult3NegWest;   //!
   TBranch        *b_Event_mRefMult3PosWest;   //!
   TBranch        *b_Event_mRefMult4NegEast;   //!
   TBranch        *b_Event_mRefMult4PosEast;   //!
   TBranch        *b_Event_mRefMult4NegWest;   //!
   TBranch        *b_Event_mRefMult4PosWest;   //!
   TBranch        *b_Event_mRefMultHalfNegEast;   //!
   TBranch        *b_Event_mRefMultHalfPosEast;   //!
   TBranch        *b_Event_mRefMultHalfNegWest;   //!
   TBranch        *b_Event_mRefMultHalfPosWest;   //!
   TBranch        *b_Event_mGRefMult;   //!
   TBranch        *b_Event_mNumberOfGlobalTracks;   //!
   TBranch        *b_Event_mbTofTrayMultiplicity;   //!
   TBranch        *b_Event_mNHitsHFT;   //!
   TBranch        *b_Event_mNVpdHitsEast;   //!
   TBranch        *b_Event_mNVpdHitsWest;   //!
   TBranch        *b_Event_mNTofT0;   //!
   TBranch        *b_Event_mVzVpd;   //!
   TBranch        *b_Event_mNTofT0Can;   //!
   TBranch        *b_Event_mTStart;   //!
   TBranch        *b_Event_mTCanFirst;   //!
   TBranch        *b_Event_mTCanLast;   //!
   TBranch        *b_Event_mNVpdEGoodHits;   //!
   TBranch        *b_Event_mNVpdWGoodHits;   //!
   TBranch        *b_Event_mEarliestVpdEHit;   //!
   TBranch        *b_Event_mEarliestVpdWHit;   //!
   TBranch        *b_Event_mClosestVpdEHit;   //!
   TBranch        *b_Event_mClosestVpdWHit;   //!
   TBranch        *b_Event_mLatestVpdEHit;   //!
   TBranch        *b_Event_mLatestVpdWHit;   //!
   TBranch        *b_Event_mZDCx;   //!
   TBranch        *b_Event_mBBCx;   //!
   TBranch        *b_Event_mBackgroundRate;   //!
   TBranch        *b_Event_mBbcBlueBackgroundRate;   //!
   TBranch        *b_Event_mBbcYellowBackgroundRate;   //!
   TBranch        *b_Event_mBbcEastRate;   //!
   TBranch        *b_Event_mBbcWestRate;   //!
   TBranch        *b_Event_mZdcEastRate;   //!
   TBranch        *b_Event_mZdcWestRate;   //!
   TBranch        *b_Event_mZdcSumAdcEast;   //!
   TBranch        *b_Event_mZdcSumAdcWest;   //!
   TBranch        *b_Event_mZdcSmdEastHorizontal;   //!
   TBranch        *b_Event_mZdcSmdEastVertical;   //!
   TBranch        *b_Event_mZdcSmdWestHorizontal;   //!
   TBranch        *b_Event_mZdcSmdWestVertical;   //!
   TBranch        *b_Event_mBbcAdcEast;   //!
   TBranch        *b_Event_mBbcAdcWest;   //!
   TBranch        *b_Event_mHighTowerThreshold;   //!
   TBranch        *b_Event_mJetPatchThreshold;   //!
   TBranch        *b_Event_mBunchCrossId;   //!
   TBranch        *b_Event_mETofHitMultiplicity;   //!
   TBranch        *b_Event_mETofDigiMultiplicity;   //!
   TBranch        *b_Event_mETofGoodEventFlag;   //!
   TBranch        *b_Event_mETofHasPulsersFlag;   //!
   TBranch        *b_Event_mNumberOfPrimaryTracks;   //!
   TBranch        *b_Event_mZdcUnAttenuated;   //!
   TBranch        *b_Track_;   //!
   TBranch        *b_Track_mId;   //!
   TBranch        *b_Track_mChi2;   //!
   TBranch        *b_Track_mPMomentumX;   //!
   TBranch        *b_Track_mPMomentumY;   //!
   TBranch        *b_Track_mPMomentumZ;   //!
   TBranch        *b_Track_mGMomentumX;   //!
   TBranch        *b_Track_mGMomentumY;   //!
   TBranch        *b_Track_mGMomentumZ;   //!
   TBranch        *b_Track_mOriginX;   //!
   TBranch        *b_Track_mOriginY;   //!
   TBranch        *b_Track_mOriginZ;   //!
   TBranch        *b_Track_mDedx;   //!
   TBranch        *b_Track_mDedxError;   //!
   TBranch        *b_Track_mDnDx;   //!
   TBranch        *b_Track_mDnDxError;   //!
   TBranch        *b_Track_mNHitsFit;   //!
   TBranch        *b_Track_mNHitsMax;   //!
   TBranch        *b_Track_mNHitsDedx;   //!
   TBranch        *b_Track_mNSigmaPion;   //!
   TBranch        *b_Track_mNSigmaKaon;   //!
   TBranch        *b_Track_mNSigmaProton;   //!
   TBranch        *b_Track_mNSigmaElectron;   //!
   TBranch        *b_Track_mTopologyMap;   //!
   TBranch        *b_Track_mBEmcPidTraitsIndex;   //!
   TBranch        *b_Track_mBTofPidTraitsIndex;   //!
   TBranch        *b_Track_mMtdPidTraitsIndex;   //!
   TBranch        *b_Track_mETofPidTraitsIndex;   //!
   TBranch        *b_Track_mBEmcMatchedTowerIndex;   //!
   TBranch        *b_Track_mStatus;   //!
   TBranch        *b_Track_mIdTruth;   //!
   TBranch        *b_Track_mQATruth;   //!
   TBranch        *b_Track_mVertexIndex;   //!
   TBranch        *b_EmcTrigger_;   //!
   TBranch        *b_EmcTrigger_mFlag;   //!
   TBranch        *b_EmcTrigger_mId;   //!
   TBranch        *b_EmcTrigger_mAdc;   //!
   TBranch        *b_EmcTrigger_mSmdE;   //!
   TBranch        *b_EmcTrigger_mSmdP;   //!
   TBranch        *b_MtdTrigger_;   //!
   TBranch        *b_MtdTrigger_mVpdTacSum;   //!
   TBranch        *b_MtdTrigger_mTHUBtime;   //!
   TBranch        *b_MtdTrigger_mQTtacSum;   //!
   TBranch        *b_MtdTrigger_mMT101Tac;   //!
   TBranch        *b_MtdTrigger_mMT101Id;   //!
   TBranch        *b_MtdTrigger_mTF201TriggerBit;   //!
   TBranch        *b_MtdTrigger_mShouldHaveRejectEvent;   //!
   TBranch        *b_BTowHit_;   //!
   TBranch        *b_BTowHit_mAdc;   //!
   TBranch        *b_BTowHit_mE;   //!
   TBranch        *b_BTofHit_;   //!
   TBranch        *b_BTofHit_mId;   //!
   TBranch        *b_MtdHit_;   //!
   TBranch        *b_MtdHit_mgChannel;   //!
   TBranch        *b_MtdHit_mTriggerFlag;   //!
   TBranch        *b_MtdHit_mLeadingEdgeTime_first;   //!
   TBranch        *b_MtdHit_mLeadingEdgeTime_second;   //!
   TBranch        *b_MtdHit_mTrailingEdgeTime_first;   //!
   TBranch        *b_MtdHit_mTrailingEdgeTime_second;   //!
   TBranch        *b_BbcHit_;   //!
   TBranch        *b_BbcHit_mId;   //!
   TBranch        *b_BbcHit_mQTdata;   //!
   TBranch        *b_EpdHit_;   //!
   TBranch        *b_EpdHit_mId;   //!
   TBranch        *b_EpdHit_mQTdata;   //!
   TBranch        *b_EpdHit_mnMIP;   //!
   TBranch        *b_FmsHit_;   //!
   TBranch        *b_FmsHit_mChannelDetectorId;   //!
   TBranch        *b_FmsHit_mAdc;   //!
   TBranch        *b_EmcPidTraits_;   //!
   TBranch        *b_EmcPidTraits_mTrackIndex;   //!
   TBranch        *b_EmcPidTraits_mBemcId;   //!
   TBranch        *b_EmcPidTraits_mBemcAdc0;   //!
   TBranch        *b_EmcPidTraits_mBemcE0;   //!
   TBranch        *b_EmcPidTraits_mBemcE;   //!
   TBranch        *b_EmcPidTraits_mBemcZDist;   //!
   TBranch        *b_EmcPidTraits_mBemcPhiDist;   //!
   TBranch        *b_EmcPidTraits_mBemcSmdNEta;   //!
   TBranch        *b_EmcPidTraits_mBemcSmdNPhi;   //!
   TBranch        *b_EmcPidTraits_mBtowId;   //!
   TBranch        *b_EmcPidTraits_mBtowId23;   //!
   TBranch        *b_EmcPidTraits_mBtowE;   //!
   TBranch        *b_EmcPidTraits_mBtowE2;   //!
   TBranch        *b_EmcPidTraits_mBtowE3;   //!
   TBranch        *b_EmcPidTraits_mBtowEtaDist;   //!
   TBranch        *b_EmcPidTraits_mBtowPhiDist;   //!
   TBranch        *b_BTofPidTraits_;   //!
   TBranch        *b_BTofPidTraits_mTrackIndex;   //!
   TBranch        *b_BTofPidTraits_mBTofCellId;   //!
   TBranch        *b_BTofPidTraits_mBTofMatchFlag;   //!
   TBranch        *b_BTofPidTraits_mBTof;   //!
   TBranch        *b_BTofPidTraits_mBTofBeta;   //!
   TBranch        *b_BTofPidTraits_mBTofYLocal;   //!
   TBranch        *b_BTofPidTraits_mBTofZLocal;   //!
   TBranch        *b_BTofPidTraits_mBTofHitPosX;   //!
   TBranch        *b_BTofPidTraits_mBTofHitPosY;   //!
   TBranch        *b_BTofPidTraits_mBTofHitPosZ;   //!
   TBranch        *b_BTofPidTraits_mNSigmaElectron;   //!
   TBranch        *b_BTofPidTraits_mNSigmaPion;   //!
   TBranch        *b_BTofPidTraits_mNSigmaKaon;   //!
   TBranch        *b_BTofPidTraits_mNSigmaProton;   //!
   TBranch        *b_MtdPidTraits_;   //!
   TBranch        *b_MtdPidTraits_mTrackIndex;   //!
   TBranch        *b_MtdPidTraits_mMtdHitIndex;   //!
   TBranch        *b_MtdPidTraits_mMatchFlag;   //!
   TBranch        *b_MtdPidTraits_mDeltaY;   //!
   TBranch        *b_MtdPidTraits_mDeltaZ;   //!
   TBranch        *b_MtdPidTraits_mDeltaTimeOfFlight;   //!
   TBranch        *b_MtdPidTraits_mBeta;   //!
   TBranch        *b_MtdPidTraits_mMtdHitChan;   //!
   TBranch        *b_TrackCovMatrix_;   //!
   TBranch        *b_TrackCovMatrix_mImp;   //!
   TBranch        *b_TrackCovMatrix_mZ;   //!
   TBranch        *b_TrackCovMatrix_mPsi;   //!
   TBranch        *b_TrackCovMatrix_mPti;   //!
   TBranch        *b_TrackCovMatrix_mTan;   //!
   TBranch        *b_TrackCovMatrix_mCurv;   //!
   TBranch        *b_TrackCovMatrix_mSigma;   //!
   TBranch        *b_TrackCovMatrix_mCorr;   //!
   TBranch        *b_TrackCovMatrix_mpIn;   //!
   TBranch        *b_TrackCovMatrix_mpOut;   //!
   TBranch        *b_BEmcSmdEHit_;   //!
   TBranch        *b_BEmcSmdEHit_mId;   //!
   TBranch        *b_BEmcSmdEHit_mAdc;   //!
   TBranch        *b_BEmcSmdEHit_mEnergy;   //!
   TBranch        *b_BEmcSmdPHit_;   //!
   TBranch        *b_BEmcSmdPHit_mId;   //!
   TBranch        *b_BEmcSmdPHit_mAdc;   //!
   TBranch        *b_BEmcSmdPHit_mEnergy;   //!
   TBranch        *b_ETofHit_;   //!
   TBranch        *b_ETofHit_mGeomId;   //!
   TBranch        *b_ETofHit_mLocalX;   //!
   TBranch        *b_ETofHit_mLocalY;   //!
   TBranch        *b_ETofHit_mClusterSize;   //!
   TBranch        *b_ETofHit_mLeadingEdgeTime;   //!
   TBranch        *b_ETofHit_mTimeOverThreshold;   //!
   TBranch        *b_ETofPidTraits_;   //!
   TBranch        *b_ETofPidTraits_mTrackIndex;   //!
   TBranch        *b_ETofPidTraits_mHitIndex;   //!
   TBranch        *b_ETofPidTraits_mMatchFlag;   //!
   TBranch        *b_ETofPidTraits_mTimeOfFlight;   //!
   TBranch        *b_ETofPidTraits_mBeta;   //!
   TBranch        *b_ETofPidTraits_mDeltaX;   //!
   TBranch        *b_ETofPidTraits_mDeltaY;   //!
   TBranch        *b_ETofPidTraits_mCrossingX;   //!
   TBranch        *b_ETofPidTraits_mCrossingY;   //!
   TBranch        *b_ETofPidTraits_mCrossingZ;   //!
   TBranch        *b_McVertex_;   //!
   TBranch        *b_McVertex_mId;   //!
   TBranch        *b_McVertex_mNoDaughters;   //!
   TBranch        *b_McVertex_mIdParTrk;   //!
   TBranch        *b_McVertex_mIsInterm;   //!
   TBranch        *b_McVertex_mTime;   //!
   TBranch        *b_McVertex_mVx;   //!
   TBranch        *b_McVertex_mVy;   //!
   TBranch        *b_McVertex_mVz;   //!
   TBranch        *b_McTrack_;   //!
   TBranch        *b_McTrack_mId;   //!
   TBranch        *b_McTrack_mGePid;   //!
   TBranch        *b_McTrack_mCharge;   //!
   TBranch        *b_McTrack_mHits;   //!
   TBranch        *b_McTrack_mPx;   //!
   TBranch        *b_McTrack_mPy;   //!
   TBranch        *b_McTrack_mPz;   //!
   TBranch        *b_McTrack_mE;   //!
   TBranch        *b_McTrack_mIsFromShower;   //!
   TBranch        *b_McTrack_mIdVtxStart;   //!
   TBranch        *b_McTrack_mIdVtxStop;   //!
   TBranch        *b_McTrack_mIdVtxItrmd;   //!

   PicoDstTFG24c(TTree *tree=0);
   virtual ~PicoDstTFG24c();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   //   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef PicoDstTFG24c_cxx
PicoDstTFG24c::PicoDstTFG24c(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("st_physics_20183003_raw_6500008,1,29203.picoDst.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("st_physics_20183003_raw_6500008,1,29203.picoDst.root");
      }
      f->GetObject("PicoDst",tree);

   }
   Init(tree);
}

PicoDstTFG24c::~PicoDstTFG24c()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t PicoDstTFG24c::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t PicoDstTFG24c::LoadTree(Long64_t entry)
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

void PicoDstTFG24c::Init(TTree *tree)
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

   fChain->SetBranchAddress("Event", &Event_, &b_Event_);
   fChain->SetBranchAddress("Event.mProductionVersion", Event_mProductionVersion, &b_Event_mProductionVersion);
   fChain->SetBranchAddress("Event.mRunId", Event_mRunId, &b_Event_mRunId);
   fChain->SetBranchAddress("Event.mEventId", Event_mEventId, &b_Event_mEventId);
   fChain->SetBranchAddress("Event.mFillId", Event_mFillId, &b_Event_mFillId);
   fChain->SetBranchAddress("Event.mBField", Event_mBField, &b_Event_mBField);
   fChain->SetBranchAddress("Event.mTime", Event_mTime, &b_Event_mTime);
   fChain->SetBranchAddress("Event.mPrimaryVertexX", Event_mPrimaryVertexX, &b_Event_mPrimaryVertexX);
   fChain->SetBranchAddress("Event.mPrimaryVertexY", Event_mPrimaryVertexY, &b_Event_mPrimaryVertexY);
   fChain->SetBranchAddress("Event.mPrimaryVertexZ", Event_mPrimaryVertexZ, &b_Event_mPrimaryVertexZ);
   fChain->SetBranchAddress("Event.mPrimaryVertexErrorX", Event_mPrimaryVertexErrorX, &b_Event_mPrimaryVertexErrorX);
   fChain->SetBranchAddress("Event.mPrimaryVertexErrorY", Event_mPrimaryVertexErrorY, &b_Event_mPrimaryVertexErrorY);
   fChain->SetBranchAddress("Event.mPrimaryVertexErrorZ", Event_mPrimaryVertexErrorZ, &b_Event_mPrimaryVertexErrorZ);
   fChain->SetBranchAddress("Event.mPrimaryVertexCorr[3]", Event_mPrimaryVertexCorr, &b_Event_mPrimaryVertexCorr);
   fChain->SetBranchAddress("Event.mRanking", Event_mRanking, &b_Event_mRanking);
   fChain->SetBranchAddress("Event.mNBEMCMatch", Event_mNBEMCMatch, &b_Event_mNBEMCMatch);
   fChain->SetBranchAddress("Event.mNBTOFMatch", Event_mNBTOFMatch, &b_Event_mNBTOFMatch);
   fChain->SetBranchAddress("Event.mTriggerIds", Event_mTriggerIds, &b_Event_mTriggerIds);
   fChain->SetBranchAddress("Event.mRefMultFtpcEast", Event_mRefMultFtpcEast, &b_Event_mRefMultFtpcEast);
   fChain->SetBranchAddress("Event.mRefMultFtpcWest", Event_mRefMultFtpcWest, &b_Event_mRefMultFtpcWest);
   fChain->SetBranchAddress("Event.mRefMultNeg", Event_mRefMultNeg, &b_Event_mRefMultNeg);
   fChain->SetBranchAddress("Event.mRefMultPos", Event_mRefMultPos, &b_Event_mRefMultPos);
   fChain->SetBranchAddress("Event.mRefMult2NegEast", Event_mRefMult2NegEast, &b_Event_mRefMult2NegEast);
   fChain->SetBranchAddress("Event.mRefMult2PosEast", Event_mRefMult2PosEast, &b_Event_mRefMult2PosEast);
   fChain->SetBranchAddress("Event.mRefMult2NegWest", Event_mRefMult2NegWest, &b_Event_mRefMult2NegWest);
   fChain->SetBranchAddress("Event.mRefMult2PosWest", Event_mRefMult2PosWest, &b_Event_mRefMult2PosWest);
   fChain->SetBranchAddress("Event.mRefMult3NegEast", Event_mRefMult3NegEast, &b_Event_mRefMult3NegEast);
   fChain->SetBranchAddress("Event.mRefMult3PosEast", Event_mRefMult3PosEast, &b_Event_mRefMult3PosEast);
   fChain->SetBranchAddress("Event.mRefMult3NegWest", Event_mRefMult3NegWest, &b_Event_mRefMult3NegWest);
   fChain->SetBranchAddress("Event.mRefMult3PosWest", Event_mRefMult3PosWest, &b_Event_mRefMult3PosWest);
   fChain->SetBranchAddress("Event.mRefMult4NegEast", Event_mRefMult4NegEast, &b_Event_mRefMult4NegEast);
   fChain->SetBranchAddress("Event.mRefMult4PosEast", Event_mRefMult4PosEast, &b_Event_mRefMult4PosEast);
   fChain->SetBranchAddress("Event.mRefMult4NegWest", Event_mRefMult4NegWest, &b_Event_mRefMult4NegWest);
   fChain->SetBranchAddress("Event.mRefMult4PosWest", Event_mRefMult4PosWest, &b_Event_mRefMult4PosWest);
   fChain->SetBranchAddress("Event.mRefMultHalfNegEast", Event_mRefMultHalfNegEast, &b_Event_mRefMultHalfNegEast);
   fChain->SetBranchAddress("Event.mRefMultHalfPosEast", Event_mRefMultHalfPosEast, &b_Event_mRefMultHalfPosEast);
   fChain->SetBranchAddress("Event.mRefMultHalfNegWest", Event_mRefMultHalfNegWest, &b_Event_mRefMultHalfNegWest);
   fChain->SetBranchAddress("Event.mRefMultHalfPosWest", Event_mRefMultHalfPosWest, &b_Event_mRefMultHalfPosWest);
   fChain->SetBranchAddress("Event.mGRefMult", Event_mGRefMult, &b_Event_mGRefMult);
   fChain->SetBranchAddress("Event.mNumberOfGlobalTracks", Event_mNumberOfGlobalTracks, &b_Event_mNumberOfGlobalTracks);
   fChain->SetBranchAddress("Event.mbTofTrayMultiplicity", Event_mbTofTrayMultiplicity, &b_Event_mbTofTrayMultiplicity);
   fChain->SetBranchAddress("Event.mNHitsHFT[4]", Event_mNHitsHFT, &b_Event_mNHitsHFT);
   fChain->SetBranchAddress("Event.mNVpdHitsEast", Event_mNVpdHitsEast, &b_Event_mNVpdHitsEast);
   fChain->SetBranchAddress("Event.mNVpdHitsWest", Event_mNVpdHitsWest, &b_Event_mNVpdHitsWest);
   fChain->SetBranchAddress("Event.mNTofT0", Event_mNTofT0, &b_Event_mNTofT0);
   fChain->SetBranchAddress("Event.mVzVpd", Event_mVzVpd, &b_Event_mVzVpd);
   fChain->SetBranchAddress("Event.mNTofT0Can", Event_mNTofT0Can, &b_Event_mNTofT0Can);
   fChain->SetBranchAddress("Event.mTStart", Event_mTStart, &b_Event_mTStart);
   fChain->SetBranchAddress("Event.mTCanFirst", Event_mTCanFirst, &b_Event_mTCanFirst);
   fChain->SetBranchAddress("Event.mTCanLast", Event_mTCanLast, &b_Event_mTCanLast);
   fChain->SetBranchAddress("Event.mNVpdEGoodHits", Event_mNVpdEGoodHits, &b_Event_mNVpdEGoodHits);
   fChain->SetBranchAddress("Event.mNVpdWGoodHits", Event_mNVpdWGoodHits, &b_Event_mNVpdWGoodHits);
   fChain->SetBranchAddress("Event.mEarliestVpdEHit", Event_mEarliestVpdEHit, &b_Event_mEarliestVpdEHit);
   fChain->SetBranchAddress("Event.mEarliestVpdWHit", Event_mEarliestVpdWHit, &b_Event_mEarliestVpdWHit);
   fChain->SetBranchAddress("Event.mClosestVpdEHit", Event_mClosestVpdEHit, &b_Event_mClosestVpdEHit);
   fChain->SetBranchAddress("Event.mClosestVpdWHit", Event_mClosestVpdWHit, &b_Event_mClosestVpdWHit);
   fChain->SetBranchAddress("Event.mLatestVpdEHit", Event_mLatestVpdEHit, &b_Event_mLatestVpdEHit);
   fChain->SetBranchAddress("Event.mLatestVpdWHit", Event_mLatestVpdWHit, &b_Event_mLatestVpdWHit);
   fChain->SetBranchAddress("Event.mZDCx", Event_mZDCx, &b_Event_mZDCx);
   fChain->SetBranchAddress("Event.mBBCx", Event_mBBCx, &b_Event_mBBCx);
   fChain->SetBranchAddress("Event.mBackgroundRate", Event_mBackgroundRate, &b_Event_mBackgroundRate);
   fChain->SetBranchAddress("Event.mBbcBlueBackgroundRate", Event_mBbcBlueBackgroundRate, &b_Event_mBbcBlueBackgroundRate);
   fChain->SetBranchAddress("Event.mBbcYellowBackgroundRate", Event_mBbcYellowBackgroundRate, &b_Event_mBbcYellowBackgroundRate);
   fChain->SetBranchAddress("Event.mBbcEastRate", Event_mBbcEastRate, &b_Event_mBbcEastRate);
   fChain->SetBranchAddress("Event.mBbcWestRate", Event_mBbcWestRate, &b_Event_mBbcWestRate);
   fChain->SetBranchAddress("Event.mZdcEastRate", Event_mZdcEastRate, &b_Event_mZdcEastRate);
   fChain->SetBranchAddress("Event.mZdcWestRate", Event_mZdcWestRate, &b_Event_mZdcWestRate);
   fChain->SetBranchAddress("Event.mZdcSumAdcEast", Event_mZdcSumAdcEast, &b_Event_mZdcSumAdcEast);
   fChain->SetBranchAddress("Event.mZdcSumAdcWest", Event_mZdcSumAdcWest, &b_Event_mZdcSumAdcWest);
   fChain->SetBranchAddress("Event.mZdcSmdEastHorizontal[8]", Event_mZdcSmdEastHorizontal, &b_Event_mZdcSmdEastHorizontal);
   fChain->SetBranchAddress("Event.mZdcSmdEastVertical[8]", Event_mZdcSmdEastVertical, &b_Event_mZdcSmdEastVertical);
   fChain->SetBranchAddress("Event.mZdcSmdWestHorizontal[8]", Event_mZdcSmdWestHorizontal, &b_Event_mZdcSmdWestHorizontal);
   fChain->SetBranchAddress("Event.mZdcSmdWestVertical[8]", Event_mZdcSmdWestVertical, &b_Event_mZdcSmdWestVertical);
   fChain->SetBranchAddress("Event.mBbcAdcEast[24]", Event_mBbcAdcEast, &b_Event_mBbcAdcEast);
   fChain->SetBranchAddress("Event.mBbcAdcWest[24]", Event_mBbcAdcWest, &b_Event_mBbcAdcWest);
   fChain->SetBranchAddress("Event.mHighTowerThreshold[4]", Event_mHighTowerThreshold, &b_Event_mHighTowerThreshold);
   fChain->SetBranchAddress("Event.mJetPatchThreshold[4]", Event_mJetPatchThreshold, &b_Event_mJetPatchThreshold);
   fChain->SetBranchAddress("Event.mBunchCrossId", Event_mBunchCrossId, &b_Event_mBunchCrossId);
   fChain->SetBranchAddress("Event.mETofHitMultiplicity", Event_mETofHitMultiplicity, &b_Event_mETofHitMultiplicity);
   fChain->SetBranchAddress("Event.mETofDigiMultiplicity", Event_mETofDigiMultiplicity, &b_Event_mETofDigiMultiplicity);
   fChain->SetBranchAddress("Event.mETofGoodEventFlag[1728]", Event_mETofGoodEventFlag, &b_Event_mETofGoodEventFlag);
   fChain->SetBranchAddress("Event.mETofHasPulsersFlag[108]", Event_mETofHasPulsersFlag, &b_Event_mETofHasPulsersFlag);
   fChain->SetBranchAddress("Event.mNumberOfPrimaryTracks", Event_mNumberOfPrimaryTracks, &b_Event_mNumberOfPrimaryTracks);
   fChain->SetBranchAddress("Event.mZdcUnAttenuated[2]", Event_mZdcUnAttenuated, &b_Event_mZdcUnAttenuated);
   fChain->SetBranchAddress("Track", &Track_, &b_Track_);
   fChain->SetBranchAddress("Track.mId", Track_mId, &b_Track_mId);
   fChain->SetBranchAddress("Track.mChi2", Track_mChi2, &b_Track_mChi2);
   fChain->SetBranchAddress("Track.mPMomentumX", Track_mPMomentumX, &b_Track_mPMomentumX);
   fChain->SetBranchAddress("Track.mPMomentumY", Track_mPMomentumY, &b_Track_mPMomentumY);
   fChain->SetBranchAddress("Track.mPMomentumZ", Track_mPMomentumZ, &b_Track_mPMomentumZ);
   fChain->SetBranchAddress("Track.mGMomentumX", Track_mGMomentumX, &b_Track_mGMomentumX);
   fChain->SetBranchAddress("Track.mGMomentumY", Track_mGMomentumY, &b_Track_mGMomentumY);
   fChain->SetBranchAddress("Track.mGMomentumZ", Track_mGMomentumZ, &b_Track_mGMomentumZ);
   fChain->SetBranchAddress("Track.mOriginX", Track_mOriginX, &b_Track_mOriginX);
   fChain->SetBranchAddress("Track.mOriginY", Track_mOriginY, &b_Track_mOriginY);
   fChain->SetBranchAddress("Track.mOriginZ", Track_mOriginZ, &b_Track_mOriginZ);
   fChain->SetBranchAddress("Track.mDedx", Track_mDedx, &b_Track_mDedx);
   fChain->SetBranchAddress("Track.mDedxError", Track_mDedxError, &b_Track_mDedxError);
   fChain->SetBranchAddress("Track.mDnDx", Track_mDnDx, &b_Track_mDnDx);
   fChain->SetBranchAddress("Track.mDnDxError", Track_mDnDxError, &b_Track_mDnDxError);
   fChain->SetBranchAddress("Track.mNHitsFit", Track_mNHitsFit, &b_Track_mNHitsFit);
   fChain->SetBranchAddress("Track.mNHitsMax", Track_mNHitsMax, &b_Track_mNHitsMax);
   fChain->SetBranchAddress("Track.mNHitsDedx", Track_mNHitsDedx, &b_Track_mNHitsDedx);
   fChain->SetBranchAddress("Track.mNSigmaPion", Track_mNSigmaPion, &b_Track_mNSigmaPion);
   fChain->SetBranchAddress("Track.mNSigmaKaon", Track_mNSigmaKaon, &b_Track_mNSigmaKaon);
   fChain->SetBranchAddress("Track.mNSigmaProton", Track_mNSigmaProton, &b_Track_mNSigmaProton);
   fChain->SetBranchAddress("Track.mNSigmaElectron", Track_mNSigmaElectron, &b_Track_mNSigmaElectron);
   fChain->SetBranchAddress("Track.mTopologyMap[3]", Track_mTopologyMap, &b_Track_mTopologyMap);
   fChain->SetBranchAddress("Track.mBEmcPidTraitsIndex", Track_mBEmcPidTraitsIndex, &b_Track_mBEmcPidTraitsIndex);
   fChain->SetBranchAddress("Track.mBTofPidTraitsIndex", Track_mBTofPidTraitsIndex, &b_Track_mBTofPidTraitsIndex);
   fChain->SetBranchAddress("Track.mMtdPidTraitsIndex", Track_mMtdPidTraitsIndex, &b_Track_mMtdPidTraitsIndex);
   fChain->SetBranchAddress("Track.mETofPidTraitsIndex", Track_mETofPidTraitsIndex, &b_Track_mETofPidTraitsIndex);
   fChain->SetBranchAddress("Track.mBEmcMatchedTowerIndex", Track_mBEmcMatchedTowerIndex, &b_Track_mBEmcMatchedTowerIndex);
   fChain->SetBranchAddress("Track.mStatus", Track_mStatus, &b_Track_mStatus);
   fChain->SetBranchAddress("Track.mIdTruth", Track_mIdTruth, &b_Track_mIdTruth);
   fChain->SetBranchAddress("Track.mQATruth", Track_mQATruth, &b_Track_mQATruth);
   fChain->SetBranchAddress("Track.mVertexIndex", Track_mVertexIndex, &b_Track_mVertexIndex);
   fChain->SetBranchAddress("EmcTrigger", &EmcTrigger_, &b_EmcTrigger_);
   fChain->SetBranchAddress("EmcTrigger.mFlag", &EmcTrigger_mFlag, &b_EmcTrigger_mFlag);
   fChain->SetBranchAddress("EmcTrigger.mId", &EmcTrigger_mId, &b_EmcTrigger_mId);
   fChain->SetBranchAddress("EmcTrigger.mAdc", &EmcTrigger_mAdc, &b_EmcTrigger_mAdc);
   fChain->SetBranchAddress("EmcTrigger.mSmdE", &EmcTrigger_mSmdE, &b_EmcTrigger_mSmdE);
   fChain->SetBranchAddress("EmcTrigger.mSmdP", &EmcTrigger_mSmdP, &b_EmcTrigger_mSmdP);
   fChain->SetBranchAddress("MtdTrigger", &MtdTrigger_, &b_MtdTrigger_);
   fChain->SetBranchAddress("MtdTrigger.mVpdTacSum", MtdTrigger_mVpdTacSum, &b_MtdTrigger_mVpdTacSum);
   fChain->SetBranchAddress("MtdTrigger.mTHUBtime[2]", MtdTrigger_mTHUBtime, &b_MtdTrigger_mTHUBtime);
   fChain->SetBranchAddress("MtdTrigger.mQTtacSum[8][8]", MtdTrigger_mQTtacSum, &b_MtdTrigger_mQTtacSum);
   fChain->SetBranchAddress("MtdTrigger.mMT101Tac[8][2]", MtdTrigger_mMT101Tac, &b_MtdTrigger_mMT101Tac);
   fChain->SetBranchAddress("MtdTrigger.mMT101Id[8][2]", MtdTrigger_mMT101Id, &b_MtdTrigger_mMT101Id);
   fChain->SetBranchAddress("MtdTrigger.mTF201TriggerBit", MtdTrigger_mTF201TriggerBit, &b_MtdTrigger_mTF201TriggerBit);
   fChain->SetBranchAddress("MtdTrigger.mShouldHaveRejectEvent", MtdTrigger_mShouldHaveRejectEvent, &b_MtdTrigger_mShouldHaveRejectEvent);
   fChain->SetBranchAddress("BTowHit", &BTowHit_, &b_BTowHit_);
   fChain->SetBranchAddress("BTowHit.mAdc", BTowHit_mAdc, &b_BTowHit_mAdc);
   fChain->SetBranchAddress("BTowHit.mE", BTowHit_mE, &b_BTowHit_mE);
   fChain->SetBranchAddress("BTofHit", &BTofHit_, &b_BTofHit_);
   fChain->SetBranchAddress("BTofHit.mId", BTofHit_mId, &b_BTofHit_mId);
   fChain->SetBranchAddress("MtdHit", &MtdHit_, &b_MtdHit_);
   fChain->SetBranchAddress("MtdHit.mgChannel", &MtdHit_mgChannel, &b_MtdHit_mgChannel);
   fChain->SetBranchAddress("MtdHit.mTriggerFlag", &MtdHit_mTriggerFlag, &b_MtdHit_mTriggerFlag);
   fChain->SetBranchAddress("MtdHit.mLeadingEdgeTime.first", &MtdHit_mLeadingEdgeTime_first, &b_MtdHit_mLeadingEdgeTime_first);
   fChain->SetBranchAddress("MtdHit.mLeadingEdgeTime.second", &MtdHit_mLeadingEdgeTime_second, &b_MtdHit_mLeadingEdgeTime_second);
   fChain->SetBranchAddress("MtdHit.mTrailingEdgeTime.first", &MtdHit_mTrailingEdgeTime_first, &b_MtdHit_mTrailingEdgeTime_first);
   fChain->SetBranchAddress("MtdHit.mTrailingEdgeTime.second", &MtdHit_mTrailingEdgeTime_second, &b_MtdHit_mTrailingEdgeTime_second);
   fChain->SetBranchAddress("BbcHit", &BbcHit_, &b_BbcHit_);
   fChain->SetBranchAddress("BbcHit.mId", BbcHit_mId, &b_BbcHit_mId);
   fChain->SetBranchAddress("BbcHit.mQTdata", BbcHit_mQTdata, &b_BbcHit_mQTdata);
   fChain->SetBranchAddress("EpdHit", &EpdHit_, &b_EpdHit_);
   fChain->SetBranchAddress("EpdHit.mId", EpdHit_mId, &b_EpdHit_mId);
   fChain->SetBranchAddress("EpdHit.mQTdata", EpdHit_mQTdata, &b_EpdHit_mQTdata);
   fChain->SetBranchAddress("EpdHit.mnMIP", EpdHit_mnMIP, &b_EpdHit_mnMIP);
   fChain->SetBranchAddress("FmsHit", &FmsHit_, &b_FmsHit_);
   fChain->SetBranchAddress("FmsHit.mChannelDetectorId", &FmsHit_mChannelDetectorId, &b_FmsHit_mChannelDetectorId);
   fChain->SetBranchAddress("FmsHit.mAdc", &FmsHit_mAdc, &b_FmsHit_mAdc);
   fChain->SetBranchAddress("EmcPidTraits", &EmcPidTraits_, &b_EmcPidTraits_);
   fChain->SetBranchAddress("EmcPidTraits.mTrackIndex", &EmcPidTraits_mTrackIndex, &b_EmcPidTraits_mTrackIndex);
   fChain->SetBranchAddress("EmcPidTraits.mBemcId", &EmcPidTraits_mBemcId, &b_EmcPidTraits_mBemcId);
   fChain->SetBranchAddress("EmcPidTraits.mBemcAdc0", &EmcPidTraits_mBemcAdc0, &b_EmcPidTraits_mBemcAdc0);
   fChain->SetBranchAddress("EmcPidTraits.mBemcE0", &EmcPidTraits_mBemcE0, &b_EmcPidTraits_mBemcE0);
   fChain->SetBranchAddress("EmcPidTraits.mBemcE", &EmcPidTraits_mBemcE, &b_EmcPidTraits_mBemcE);
   fChain->SetBranchAddress("EmcPidTraits.mBemcZDist", &EmcPidTraits_mBemcZDist, &b_EmcPidTraits_mBemcZDist);
   fChain->SetBranchAddress("EmcPidTraits.mBemcPhiDist", &EmcPidTraits_mBemcPhiDist, &b_EmcPidTraits_mBemcPhiDist);
   fChain->SetBranchAddress("EmcPidTraits.mBemcSmdNEta", &EmcPidTraits_mBemcSmdNEta, &b_EmcPidTraits_mBemcSmdNEta);
   fChain->SetBranchAddress("EmcPidTraits.mBemcSmdNPhi", &EmcPidTraits_mBemcSmdNPhi, &b_EmcPidTraits_mBemcSmdNPhi);
   fChain->SetBranchAddress("EmcPidTraits.mBtowId", &EmcPidTraits_mBtowId, &b_EmcPidTraits_mBtowId);
   fChain->SetBranchAddress("EmcPidTraits.mBtowId23", &EmcPidTraits_mBtowId23, &b_EmcPidTraits_mBtowId23);
   fChain->SetBranchAddress("EmcPidTraits.mBtowE", &EmcPidTraits_mBtowE, &b_EmcPidTraits_mBtowE);
   fChain->SetBranchAddress("EmcPidTraits.mBtowE2", &EmcPidTraits_mBtowE2, &b_EmcPidTraits_mBtowE2);
   fChain->SetBranchAddress("EmcPidTraits.mBtowE3", &EmcPidTraits_mBtowE3, &b_EmcPidTraits_mBtowE3);
   fChain->SetBranchAddress("EmcPidTraits.mBtowEtaDist", &EmcPidTraits_mBtowEtaDist, &b_EmcPidTraits_mBtowEtaDist);
   fChain->SetBranchAddress("EmcPidTraits.mBtowPhiDist", &EmcPidTraits_mBtowPhiDist, &b_EmcPidTraits_mBtowPhiDist);
   fChain->SetBranchAddress("BTofPidTraits", &BTofPidTraits_, &b_BTofPidTraits_);
   fChain->SetBranchAddress("BTofPidTraits.mTrackIndex", BTofPidTraits_mTrackIndex, &b_BTofPidTraits_mTrackIndex);
   fChain->SetBranchAddress("BTofPidTraits.mBTofCellId", BTofPidTraits_mBTofCellId, &b_BTofPidTraits_mBTofCellId);
   fChain->SetBranchAddress("BTofPidTraits.mBTofMatchFlag", BTofPidTraits_mBTofMatchFlag, &b_BTofPidTraits_mBTofMatchFlag);
   fChain->SetBranchAddress("BTofPidTraits.mBTof", BTofPidTraits_mBTof, &b_BTofPidTraits_mBTof);
   fChain->SetBranchAddress("BTofPidTraits.mBTofBeta", BTofPidTraits_mBTofBeta, &b_BTofPidTraits_mBTofBeta);
   fChain->SetBranchAddress("BTofPidTraits.mBTofYLocal", BTofPidTraits_mBTofYLocal, &b_BTofPidTraits_mBTofYLocal);
   fChain->SetBranchAddress("BTofPidTraits.mBTofZLocal", BTofPidTraits_mBTofZLocal, &b_BTofPidTraits_mBTofZLocal);
   fChain->SetBranchAddress("BTofPidTraits.mBTofHitPosX", BTofPidTraits_mBTofHitPosX, &b_BTofPidTraits_mBTofHitPosX);
   fChain->SetBranchAddress("BTofPidTraits.mBTofHitPosY", BTofPidTraits_mBTofHitPosY, &b_BTofPidTraits_mBTofHitPosY);
   fChain->SetBranchAddress("BTofPidTraits.mBTofHitPosZ", BTofPidTraits_mBTofHitPosZ, &b_BTofPidTraits_mBTofHitPosZ);
   fChain->SetBranchAddress("BTofPidTraits.mNSigmaElectron", BTofPidTraits_mNSigmaElectron, &b_BTofPidTraits_mNSigmaElectron);
   fChain->SetBranchAddress("BTofPidTraits.mNSigmaPion", BTofPidTraits_mNSigmaPion, &b_BTofPidTraits_mNSigmaPion);
   fChain->SetBranchAddress("BTofPidTraits.mNSigmaKaon", BTofPidTraits_mNSigmaKaon, &b_BTofPidTraits_mNSigmaKaon);
   fChain->SetBranchAddress("BTofPidTraits.mNSigmaProton", BTofPidTraits_mNSigmaProton, &b_BTofPidTraits_mNSigmaProton);
   fChain->SetBranchAddress("MtdPidTraits", &MtdPidTraits_, &b_MtdPidTraits_);
   fChain->SetBranchAddress("MtdPidTraits.mTrackIndex", &MtdPidTraits_mTrackIndex, &b_MtdPidTraits_mTrackIndex);
   fChain->SetBranchAddress("MtdPidTraits.mMtdHitIndex", &MtdPidTraits_mMtdHitIndex, &b_MtdPidTraits_mMtdHitIndex);
   fChain->SetBranchAddress("MtdPidTraits.mMatchFlag", &MtdPidTraits_mMatchFlag, &b_MtdPidTraits_mMatchFlag);
   fChain->SetBranchAddress("MtdPidTraits.mDeltaY", &MtdPidTraits_mDeltaY, &b_MtdPidTraits_mDeltaY);
   fChain->SetBranchAddress("MtdPidTraits.mDeltaZ", &MtdPidTraits_mDeltaZ, &b_MtdPidTraits_mDeltaZ);
   fChain->SetBranchAddress("MtdPidTraits.mDeltaTimeOfFlight", &MtdPidTraits_mDeltaTimeOfFlight, &b_MtdPidTraits_mDeltaTimeOfFlight);
   fChain->SetBranchAddress("MtdPidTraits.mBeta", &MtdPidTraits_mBeta, &b_MtdPidTraits_mBeta);
   fChain->SetBranchAddress("MtdPidTraits.mMtdHitChan", &MtdPidTraits_mMtdHitChan, &b_MtdPidTraits_mMtdHitChan);
   fChain->SetBranchAddress("TrackCovMatrix", &TrackCovMatrix_, &b_TrackCovMatrix_);
   fChain->SetBranchAddress("TrackCovMatrix.mImp", TrackCovMatrix_mImp, &b_TrackCovMatrix_mImp);
   fChain->SetBranchAddress("TrackCovMatrix.mZ", TrackCovMatrix_mZ, &b_TrackCovMatrix_mZ);
   fChain->SetBranchAddress("TrackCovMatrix.mPsi", TrackCovMatrix_mPsi, &b_TrackCovMatrix_mPsi);
   fChain->SetBranchAddress("TrackCovMatrix.mPti", TrackCovMatrix_mPti, &b_TrackCovMatrix_mPti);
   fChain->SetBranchAddress("TrackCovMatrix.mTan", TrackCovMatrix_mTan, &b_TrackCovMatrix_mTan);
   fChain->SetBranchAddress("TrackCovMatrix.mCurv", TrackCovMatrix_mCurv, &b_TrackCovMatrix_mCurv);
   fChain->SetBranchAddress("TrackCovMatrix.mSigma[5]", TrackCovMatrix_mSigma, &b_TrackCovMatrix_mSigma);
   fChain->SetBranchAddress("TrackCovMatrix.mCorr[10]", TrackCovMatrix_mCorr, &b_TrackCovMatrix_mCorr);
   fChain->SetBranchAddress("TrackCovMatrix.mpIn", TrackCovMatrix_mpIn, &b_TrackCovMatrix_mpIn);
   fChain->SetBranchAddress("TrackCovMatrix.mpOut", TrackCovMatrix_mpOut, &b_TrackCovMatrix_mpOut);
   fChain->SetBranchAddress("BEmcSmdEHit", &BEmcSmdEHit_, &b_BEmcSmdEHit_);
   fChain->SetBranchAddress("BEmcSmdEHit.mId", &BEmcSmdEHit_mId, &b_BEmcSmdEHit_mId);
   fChain->SetBranchAddress("BEmcSmdEHit.mAdc", &BEmcSmdEHit_mAdc, &b_BEmcSmdEHit_mAdc);
   fChain->SetBranchAddress("BEmcSmdEHit.mEnergy", &BEmcSmdEHit_mEnergy, &b_BEmcSmdEHit_mEnergy);
   fChain->SetBranchAddress("BEmcSmdPHit", &BEmcSmdPHit_, &b_BEmcSmdPHit_);
   fChain->SetBranchAddress("BEmcSmdPHit.mId", &BEmcSmdPHit_mId, &b_BEmcSmdPHit_mId);
   fChain->SetBranchAddress("BEmcSmdPHit.mAdc", &BEmcSmdPHit_mAdc, &b_BEmcSmdPHit_mAdc);
   fChain->SetBranchAddress("BEmcSmdPHit.mEnergy", &BEmcSmdPHit_mEnergy, &b_BEmcSmdPHit_mEnergy);
   fChain->SetBranchAddress("ETofHit", &ETofHit_, &b_ETofHit_);
   fChain->SetBranchAddress("ETofHit.mGeomId", ETofHit_mGeomId, &b_ETofHit_mGeomId);
   fChain->SetBranchAddress("ETofHit.mLocalX", ETofHit_mLocalX, &b_ETofHit_mLocalX);
   fChain->SetBranchAddress("ETofHit.mLocalY", ETofHit_mLocalY, &b_ETofHit_mLocalY);
   fChain->SetBranchAddress("ETofHit.mClusterSize", ETofHit_mClusterSize, &b_ETofHit_mClusterSize);
   fChain->SetBranchAddress("ETofHit.mLeadingEdgeTime", ETofHit_mLeadingEdgeTime, &b_ETofHit_mLeadingEdgeTime);
   fChain->SetBranchAddress("ETofHit.mTimeOverThreshold", ETofHit_mTimeOverThreshold, &b_ETofHit_mTimeOverThreshold);
   fChain->SetBranchAddress("ETofPidTraits", &ETofPidTraits_, &b_ETofPidTraits_);
   fChain->SetBranchAddress("ETofPidTraits.mTrackIndex", ETofPidTraits_mTrackIndex, &b_ETofPidTraits_mTrackIndex);
   fChain->SetBranchAddress("ETofPidTraits.mHitIndex", ETofPidTraits_mHitIndex, &b_ETofPidTraits_mHitIndex);
   fChain->SetBranchAddress("ETofPidTraits.mMatchFlag", ETofPidTraits_mMatchFlag, &b_ETofPidTraits_mMatchFlag);
   fChain->SetBranchAddress("ETofPidTraits.mTimeOfFlight", ETofPidTraits_mTimeOfFlight, &b_ETofPidTraits_mTimeOfFlight);
   fChain->SetBranchAddress("ETofPidTraits.mBeta", ETofPidTraits_mBeta, &b_ETofPidTraits_mBeta);
   fChain->SetBranchAddress("ETofPidTraits.mDeltaX", ETofPidTraits_mDeltaX, &b_ETofPidTraits_mDeltaX);
   fChain->SetBranchAddress("ETofPidTraits.mDeltaY", ETofPidTraits_mDeltaY, &b_ETofPidTraits_mDeltaY);
   fChain->SetBranchAddress("ETofPidTraits.mCrossingX", ETofPidTraits_mCrossingX, &b_ETofPidTraits_mCrossingX);
   fChain->SetBranchAddress("ETofPidTraits.mCrossingY", ETofPidTraits_mCrossingY, &b_ETofPidTraits_mCrossingY);
   fChain->SetBranchAddress("ETofPidTraits.mCrossingZ", ETofPidTraits_mCrossingZ, &b_ETofPidTraits_mCrossingZ);
   fChain->SetBranchAddress("McVertex", &McVertex_, &b_McVertex_);
   fChain->SetBranchAddress("McVertex.mId", &McVertex_mId, &b_McVertex_mId);
   fChain->SetBranchAddress("McVertex.mNoDaughters", &McVertex_mNoDaughters, &b_McVertex_mNoDaughters);
   fChain->SetBranchAddress("McVertex.mIdParTrk", &McVertex_mIdParTrk, &b_McVertex_mIdParTrk);
   fChain->SetBranchAddress("McVertex.mIsInterm", &McVertex_mIsInterm, &b_McVertex_mIsInterm);
   fChain->SetBranchAddress("McVertex.mTime", &McVertex_mTime, &b_McVertex_mTime);
   fChain->SetBranchAddress("McVertex.mVx", &McVertex_mVx, &b_McVertex_mVx);
   fChain->SetBranchAddress("McVertex.mVy", &McVertex_mVy, &b_McVertex_mVy);
   fChain->SetBranchAddress("McVertex.mVz", &McVertex_mVz, &b_McVertex_mVz);
   fChain->SetBranchAddress("McTrack", &McTrack_, &b_McTrack_);
   fChain->SetBranchAddress("McTrack.mId", &McTrack_mId, &b_McTrack_mId);
   fChain->SetBranchAddress("McTrack.mGePid", &McTrack_mGePid, &b_McTrack_mGePid);
   fChain->SetBranchAddress("McTrack.mCharge", &McTrack_mCharge, &b_McTrack_mCharge);
   fChain->SetBranchAddress("McTrack.mHits[30]", &McTrack_mHits, &b_McTrack_mHits);
   fChain->SetBranchAddress("McTrack.mPx", &McTrack_mPx, &b_McTrack_mPx);
   fChain->SetBranchAddress("McTrack.mPy", &McTrack_mPy, &b_McTrack_mPy);
   fChain->SetBranchAddress("McTrack.mPz", &McTrack_mPz, &b_McTrack_mPz);
   fChain->SetBranchAddress("McTrack.mE", &McTrack_mE, &b_McTrack_mE);
   fChain->SetBranchAddress("McTrack.mIsFromShower", &McTrack_mIsFromShower, &b_McTrack_mIsFromShower);
   fChain->SetBranchAddress("McTrack.mIdVtxStart", &McTrack_mIdVtxStart, &b_McTrack_mIdVtxStart);
   fChain->SetBranchAddress("McTrack.mIdVtxStop", &McTrack_mIdVtxStop, &b_McTrack_mIdVtxStop);
   fChain->SetBranchAddress("McTrack.mIdVtxItrmd", &McTrack_mIdVtxItrmd, &b_McTrack_mIdVtxItrmd);
   Notify();
}

Bool_t PicoDstTFG24c::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void PicoDstTFG24c::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t PicoDstTFG24c::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef PicoDstTFG24c_cxx
