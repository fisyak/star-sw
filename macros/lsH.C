void lsH(const TString reg = "TdEdx*") { 
  TPRegexp re(reg); 
  TIter next(gDirectory->GetListOfKeys()); 
  TKey *key; 
  while ((key= (TKey*)next())) { 
    TString st = key->GetName(); 
    if (st.Index(re) == kNPOS) continue;
    key->Print(); 
  } 
  TObject *obj;
  TIter nextO(gDirectory->GetList()); 
  while ((obj = nextO())) { 
    TString st = obj->GetName(); 
    if (st.Index(re) == kNPOS) continue;
    obj->Print(); 
  } 

}
