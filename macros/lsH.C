#include "Ask.h"
void lsH(const TString reg = "TdEdx*") { 
  TPRegexp re(reg); 
  TIter next(gDirectory->GetListOfKeys()); 
  TKey *key; 
  TObject *obj;
  while ((key= (TKey*)next())) { 
    TString st = key->GetName(); 
    if (st.Index(re) == kNPOS) continue;
    obj = gDirectory->Get(st);
    if (obj->IsA()->InheritsFrom( "TH3" )) {
      TH3 *h3 = (TH3 *) obj;
      TCanvas *c1 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("c1");
      if (! c1) c1 = new TCanvas();
      c1->cd();
      h3->Project3D("zy")->Draw("colz");
      c1->Update();
      cout << h3->GetName()
	<< "\tnx = " << h3->GetXaxis()->GetNbins() <<  "\tmin = " << h3->GetXaxis()->GetXmin() << "\tmax = " << h3->GetXaxis()->GetXmax()
	<< "\tny = " << h3->GetYaxis()->GetNbins() <<  "\tmin = " << h3->GetYaxis()->GetXmin() << "\tmax = " << h3->GetYaxis()->GetXmax()
	<< "\tnz = " << h3->GetZaxis()->GetNbins() <<  "\tmin = " << h3->GetZaxis()->GetXmin() << "\tmax = " << h3->GetZaxis()->GetXmax() << endl;
      if (! gROOT->IsBatch() && Ask()) return;
    }
  } else {
    key->Print(); 
  }
#if 0
  TIter nextO(gDirectory->GetList()); 
  while ((obj = nextO())) { 
    TString st = obj->GetName(); 
    if (st.Index(re) == kNPOS) continue;
    obj->Print(); 
  } 
#endif
}
