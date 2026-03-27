//________________________________________________________________________________
Double_t gf4Func(Double_t *x, Double_t *par) {
  // par[0] - norm
  // par[1] - pion position wrt Z_pion (Bichsel prediction)
  // par[2] - sigma 
  // par[3] - proton signal
  // par[4] - Kaon    -"-
  // par[5] - electorn -"-
  // par[6] - deuteron -"-
  // par[7] - Total
  // par[8] - case (-1 all, >-0 hyp no.)
  // par[9] - scale 
  Double_t mu    = par[1];
  Double_t sigma = par[2];
  Double_t scale = par[9];
  Double_t frac[5];
  Int_t i;
  frac[0] = 1;
  for (i = 1; i < 5; i++) {
    frac[i] = TMath::Sin(par[2+i]);
    frac[i] *= frac[i];
    frac[0] -= frac[i];
  }
  if (frac[0] < 0.4 && frac[1] < 0.4) return 0;
  static Double_t parMIP[5][4] = {
    /*   particle          norml,         mu,      sigma,      alpha */
    /*       pion */ {  14.08797,   -0.07141,    0.40063,    2.91620},
    /*     proton */ {  14.12205,    1.13661,    0.29324,    1.93451},
    /*       kaon */ {  14.29133,    0.33162,    0.36903,    2.62903},
    /*   electron */ {  14.33684,    0.21674,    0.36806,    2.60754},
    /*   deuteron */ {  11.63070,    2.17617,    0.15694,    0.53711}
  };
  Double_t Value = 0;
  Int_t icase = (Int_t) par[8];
  Int_t i1 = 0;
  Int_t i2 = 4;
  if (icase >= 0) {i1 = i2 = icase;}
  TF1 *g = GG();
  for (i = i1; i <= i2; i++) { 
    Double_t pars[4] = {0, parMIP[i][1] + mu, parMIP[i][2] + sigma, parMIP[i][3]};
    Value += frac[i]*g->EvalPar(x, pars);
  }
  return par[7]*TMath::Exp(par[0])*Value;
}
//________________________________________________________________________________
TF1 *FitG4F(TH1 *proj, Option_t *opt="") {
  // fit in momentum range p = 0.526 +/- 0.05;
  if (! proj) return 0;
  TString Opt(opt);
  //  Bool_t quet = Opt.Contains("Q",TString::kIgnoreCase);
  TF1 *g2 = (TF1*) gROOT->GetFunction("G4F");
  if (! g2) {
    g2 = new TF1("G4F",gf4Func, -5, 5, 10);
    g2->SetParName(0,"norm"); g2->SetParLimits(0,-80,80);
    g2->SetParName(1,"mu");     g2->SetParLimits(1,-0.5,0.5);
    g2->SetParName(2,"Sigma");  g2->SetParLimits(2,-0.1,0.5);
    g2->SetParName(3,"P");      g2->SetParLimits(3,0,1.5);
    g2->SetParName(4,"K");      g2->SetParLimits(4,0.0,0.5);
    g2->SetParName(5,"e");      g2->SetParLimits(5,0.0,0.5);
    g2->SetParName(6,"d");      g2->SetParLimits(6,0.0,0.5);
    g2->SetParName(7,"Total");
    g2->SetParName(8,"Case");
    g2->SetParName(9,"scale");  g2->FixParameter(9,1.);
    //    g2->SetParName(7,"factor"); g2->SetParLimits(7,-.1,0.1);
  }
  PreSetParameters(proj, g2);
  proj->Fit(g2,Opt.Data());
  g2->ReleaseParameter(3); g2->SetParLimits(3,0.0,1.5);
  g2->ReleaseParameter(4); g2->SetParLimits(4,0.0,0.5);
  g2->ReleaseParameter(5); g2->SetParLimits(5,0.0,0.5);
  g2->ReleaseParameter(6); g2->SetParLimits(6,0.0,0.5);
  //  g2->ReleaseParameter(9); g2->SetParLimits(9,0.5,2.0);
  Int_t iok = proj->Fit(g2,Opt.Data());
  if ( iok < 0) {
    cout << g2->GetName() << " fit has failed with " << iok << " for " 
	 << proj->GetName() << "/" << proj->GetTitle() << " Try one again" << endl; 
    proj->Fit(g2,Opt.Data());
  }
  Opt += "m";
  iok = proj->Fit(g2,Opt.Data());
  if (iok < 0 ) return 0;
  if (! Opt.Contains("q",TString::kIgnoreCase)) {
    Double_t params[10];
    g2->GetParameters(params);
    Double_t X = params[1];
    Double_t Y = TMath::Exp(params[0]);
    TPolyMarker *pm = new TPolyMarker(1, &X, &Y);
    proj->GetListOfFunctions()->Add(pm);
    pm->SetMarkerStyle(23);
    pm->SetMarkerColor(kRed);
    pm->SetMarkerSize(1.3);
    for (int i = 0; i <= 4; i++) {
      TF1 *f = new TF1(*g2);
      f->SetName(Peaks[i].Name);
      f->FixParameter(8,i);
      f->SetLineColor(i+2);
      proj->GetListOfFunctions()->Add(f);
    }
    proj->Draw();
  }
  return g2;
}
