#include "Riostream.h"
#include "TMath.h"
#include "TDatabasePDG.h"
TDataSet *CreateTable() {
  Int_t iD  = 48;
  Double_t pTlow  =   10;
  Double_t pThigh =   10;
  Double_t Ylow   =  -2.5; 
  Double_t Yhigh  =   2.5;
  Double_t Philow =   0;
  Double_t Phihigh= 2*TMath::Pi();
  Double_t Zlow   =    0; 
  Double_t Zhigh  =    0; 
  Int_t    Npart  =   20;
  gEnv->SetValue("FixedSigmaX", 0);
  gEnv->SetValue("FixedSigmaY", 0);
  gEnv->SetValue("FixedSigmaZ", 0);
  if ( gClassTable->GetID("TGiant3") >= 0) { // root4star
    if (gClassTable->GetID("St_geant_Maker") < 0) {
      cout << "You have to use root4star with St_geant_Maker already loaded" << endl; 
      return 0;
    }
    if (! St_geant_Maker::instance()) return 0;
  } else {
    if (! StVMCMaker::instance()) return 0;
    if (! StarVMCApplication::Instance()) return 0;
    if (! TVirtualMC::GetMC()->IsA()->InheritsFrom("TGeant3TGeo")) return 0;
     StarMCSimplePrimaryGenerator *gener = (StarMCSimplePrimaryGenerator *) StarVMCApplication::Instance()->GetPrimaryGenerator();
    if ( gener && ! gener->IsA()->InheritsFrom( "StarMCSimplePrimaryGenerator" ) ) {
      delete gener; gener = 0;
    }
    if (! gener) gener =  new 
      StarMCSimplePrimaryGenerator( Npart, iD, pTlow,pThigh,Ylow, Yhigh, Philow, Phihigh, Zlow, Zhigh, "G");
    else
      gener->SetGenerator( Npart, iD, pTlow,pThigh,Ylow, Yhigh, Philow, Phihigh, Zlow, Zhigh, "G");
    StarVMCApplication::Instance()->SetPrimaryGenerator(gener);
    cout << "Set StarMCSimplePrimaryGenerator" << endl;
  }
  TDataSet *tableSet = new TDataSet("Geantino");
  return (TDataSet *)tableSet;
}
