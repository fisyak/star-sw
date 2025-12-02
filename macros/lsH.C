#include "Ask.h"
void lsH(const TString reg = "TdEdx*", Bool_t plot = kFALSE) { 
  TPRegexp re(reg); cout << "reg = " << reg.Data() << endl;
  TIter nextO(gDirectory->GetList()); 
  while ((obj = nextO())) { 
    TString st = obj->GetName(); 
    if (st.Index(re) == kNPOS) continue;
    obj->Print(); 
  } 
  TIter next(gDirectory->GetListOfKeys()); 
  TKey *key; 
  TObject *obj;
  while ((key= (TKey*)next())) { 
    TString st = key->GetName(); cout << "st = " << st.Data() << endl;
    if (st.Index(re) == kNPOS) continue;
    obj = gDirectory->Get(st);
    if (! obj) continue;
    if (plot && obj->IsA()->InheritsFrom( "TH3" )) {
      TH3 *h3 = (TH3 *) obj;
      TCanvas *c1 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("c1");
      if (! c1) c1 = new TCanvas();
      c1->cd();
      h3->Project3D("zy")->Draw("colz");
      c1->Update();
      cout << h3->GetName() << "\t" << h3->GetTitle()
	<< "\tnx = " << h3->GetXaxis()->GetNbins() <<  "\tmin = " << h3->GetXaxis()->GetXmin() << "\tmax = " << h3->GetXaxis()->GetXmax()
	<< "\tny = " << h3->GetYaxis()->GetNbins() <<  "\tmin = " << h3->GetYaxis()->GetXmin() << "\tmax = " << h3->GetYaxis()->GetXmax()
	<< "\tnz = " << h3->GetZaxis()->GetNbins() <<  "\tmin = " << h3->GetZaxis()->GetXmin() << "\tmax = " << h3->GetZaxis()->GetXmax() << endl;
      if (! gROOT->IsBatch() && Ask()) return;
    } else {
      obj->Print(); 
    }
  }
}
