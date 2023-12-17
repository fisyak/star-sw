//________________________________________________________________________________
void PrintPars(Int_t N, Double_t *pars, const Char_t *title = "") {
  cout << "  Double_t pars[" << N << "] = {";
  for (Int_t i = 0; i < N; i++) {
    cout << Form("%10.7g", pars[i]);
    if (i == N - 1) cout << "}; //" << title << endl;
    else            cout << ", ";
  }
}
//________________________________________________________________________________
void PrintPars(TF1 *f = 0, const Char_t *title = "") {
  if (! f) return;
  Int_t nPar = f->GetNpar();
  TArrayD pars(nPar);
  f->GetParameters(pars.GetArray());
  PrintPars(nPar, pars.GetArray(), title);
}
//________________________________________________________________________________
void PrintPars(TMultiGraph *multigraph) {
  if (! multigraph) return;
  TString comment(multigraph->GetName());
  TF1 *func = ((TF1 *) multigraph->GetListOfFunctions()->Last()); 
  if (! func) return;
  func->Print();
  Int_t idx = 0, nrows = 0, type = 0, var = 0, part = -1, ch = 0, pull = 0, det = -1, npar = 0;
  if (comment.Contains("dEdx")) det = 3;
  if (comment.Contains("Pull")) pull = 1;
  if        (comment.BeginsWith("E"))      { part = 0;
  } else if (comment.BeginsWith("Proton")) { part = 1;
  } else if (comment.BeginsWith("Pion"))   { part = 3;
  }
  Double_t off = 0;
  Double_t min = func->GetXaxis()->GetXmin();
  Double_t max = func->GetXaxis()->GetXmax();
  Double_t a[10] = {0};
  npar = func->GetNpar();
  cout << "det = " << det << " npar = " << npar << endl;
  func->GetParameters(a);
  //  Char_t   comment[32];
  comment += " ";
  comment += func->GetName();
  //idx,nrows,type,var,part,ch,pull,det,npar,off,min,max,a[10],comment
  //    {   0,    0,   0,  0,   0, 0,   0,  3,   0, 0., 0., 0.,  0., 0., 0., 0., 0., 0., 0., 0., 0., 0., ""},
  //                   i   n   t   v   p   c   p   d   n     
  cout << Form("    {%4i,%5i,%4i,%3i,%4i,%3i,%3o,%3i,%4i,",
	       idx,nrows,type,var,part,ch,pull,det,npar);
  cout << Form("%3.0f,%5.2f,%5.2f,",off,min,max);
  for (Int_t i = 0; i < 10; i++) if (a[i]) cout << Form("%12g,",a[i]); else cout << a[i] << ",";
  cout << Form("\"%s\"},", comment.Data()) << endl;
}
