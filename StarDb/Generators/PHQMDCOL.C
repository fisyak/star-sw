#include "Riostream.h"
#include "TMath.h"
#include "TDatabasePDG.h"
TDataSet *CreateTable() {
  gEnv->SetValue("FixedSigmaX", 0.0250);
  gEnv->SetValue("FixedSigmaY", 0.0250);
  gEnv->SetValue("FixedSigmaZ", 0.0250);
  StarPHQMDPrimaryGenerator *gener = (StarPHQMDPrimaryGenerator *) StarVMCApplication::Instance()->GetPrimaryGenerator();
  if ( gener && ! gener->IsA()->InheritsFrom( "StarMCPrimaryGenerator" ) ) {
    delete gener; gener = 0;
  }
  if (! gener) gener =  new 		 StarPHQMDPrimaryGenerator();
  else         gener->SetGenerator();
  gener->SetVertex(0,0,0);
  gener->SetSpread(0.1,0.1,60);
  StarVMCApplication::Instance()->SetPrimaryGenerator(gener);
  cout << "Set StarPHQMDPrimaryGenerator" << endl;
  TDataSet *tableSet = new TDataSet("StarPHQMDPrimaryGenerator");
  return (TDataSet *)tableSet;
}
