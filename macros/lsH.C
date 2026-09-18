#include "Ask.h"
#include "TList.h"
#include "TPRegexp.h"
#include "TDirectory.h"
#include "TIterator.h"
#include "TString.h"
#include "TObject.h"
#include "TKey.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TROOT.h"
#include "TClass.h"
#include "TCanvas.h"
void lsH(const TString reg = "TdEdx*", Bool_t plot = kFALSE) { 
  TPRegexp re(reg); cout << "reg = " << reg.Data() << endl;
  TList *list = gDirectory->GetList(); 
  TObject *obj;
  if (list) {
    cout << "List of objects\t" << list->GetEntries() << endl;
    TIter nextO(list); 
    while ((obj = nextO())) { 
      TString st = obj->GetName(); 
      if (st.Index(re) == kNPOS) continue;
      obj->Print(); 
      if (obj->IsA()->InheritsFrom( "TH1" )) {
	Double_t entries = ((TH1 *) obj)->GetEntries();
	if (entries == 0.0) cout << "================================================================================ Empty" << endl;
      }
    } 
  }
  TList *listOfKey = gDirectory->GetListOfKeys(); 
  if (listOfKey) {
    cout << "List of objects\t" << listOfKey->GetEntries() << endl;
    TIter next(listOfKey);
    TKey *key; 
    while ((key= (TKey*)next())) { 
      TString st = key->GetName(); //cout << "st = " << st.Data() << endl;
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
}
