#ifndef __TRACK__
#define __TRACK__
#define NSP 1000
#include <string.h>
#include "TObject.h"
#include "TMath.h"
class StGmtPoint;
class GmtTrack : public TObject {
  
 public:
  GmtTrack() { Clear(); }
  virtual ~GmtTrack() {Clear();}
  void          Clear(Option_t *option="") {if (option) {}; memset(&beg, 0, &end - &beg);}
  Double32_t    GetpX()      { return GetpT()*TMath::Cos(fPhi);}
  Double32_t    GetpY()      { return GetpT()*TMath::Sin(fPhi);}
  Double32_t    GetpZ()      { return GetpT()*fTanL;}
  Double32_t    GetInvpT()   { return fInvpT;}
  Double32_t    GetTanL()    { return fTanL;}
  Double32_t    GetDip()     { return TMath::ATan(fTanL);}
  Double32_t    GetPhi()     { return fPhi;}
  Double32_t    GetRho()     { return fRho;}
  Double32_t    GetpT()      { return TMath::Abs(fInvpT) > 1.e-7 ? 1./TMath::Abs(fInvpT): 1e7; }
  Double32_t    GetMomentum(){ return GetpT()*TMath::Sqrt(1. + fTanL*fTanL);}
  UInt_t        GetNpoint()  { return fNpoint; }
  Short_t       GetCharge()  { return (Short_t) TMath::Sign(1., fInvpT); }
  Double32_t    GetLegth()   {return fLength;}
  virtual void SetInvpT(Double32_t p)  {fInvpT = p; }
  virtual void SetDip(Double32_t p)  {fTanL = TMath::Tan(p); }
  virtual void SetTanL(Double32_t p)  {fTanL = p; }
  virtual void SetPhi(Double32_t p)  {fPhi = p; }
  virtual void SetRho(Double32_t p)  {fRho = p; }
  virtual void SetNpoint(UInt_t p)     {fNpoint = p; }
  virtual void SetLength(Double_t L)   {fLength = L;}
  virtual void Print(Option_t *opt="") const;
 private:
  Char_t          beg;
  Double32_t      fInvpT;        //signed
  Double32_t      fTanL;
  Double32_t      fPhi;
  Double32_t      fRho;
  UInt_t          fNpoint;       //Number of fitted points for this track
  Double32_t      fLength;
  Char_t          end;
  ClassDef(GmtTrack,2)
};
#endif
