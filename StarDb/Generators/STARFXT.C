#include "Riostream.h"
#include "TMath.h"
#include "TDatabasePDG.h"
TDataSet *CreateTable() {
  gEnv->SetValue("FixedSigmaX", 0.0250);
  gEnv->SetValue("FixedSigmaY", 0.0250);
  gEnv->SetValue("FixedSigmaZ", 0.0250);
  StarGenPrimaryGenerator *gener = (StarGenPrimaryGenerator *) StarVMCApplication::Instance()->GetPrimaryGenerator();
  if ( gener && ! gener->IsA()->InheritsFrom( "StarMCPrimaryGenerator" ) ) {
    delete gener; gener = 0;
  }
  if (! gener) gener =  new 		 StarGenPrimaryGenerator();
  else         gener->SetGenerator();
  gener->SetVertex(0,-2.,200.);
  gener->SetSpread(0.1,0.1,0.0025);
  StarVMCApplication::Instance()->SetPrimaryGenerator(gener);
  cout << "Set StarGenPrimaryGenerator" << endl;
  TDataSet *tableSet = new TDataSet("StarGenPrimaryGenerator");
  return (TDataSet *)tableSet;
}
