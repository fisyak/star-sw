//________________________________________________________________________________
#ifndef __FitG4F__
Double_t gfFunc(Double_t *x, Double_t *par) {
#else /* __FitG4F__ */
Double_t gf4Func(Double_t *x, Double_t *par) {
#endif /* __FitG4F__ */
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
#ifdef __FitG4F__
  static Double_t parMIP[5][4] = {
    /*   particle          norml,         mu,      sigma,      alpha */
    /*       pion */ {  14.08797,   -0.07141,    0.40063,    2.91620},
    /*     proton */ {  14.12205,    1.13661,    0.29324,    1.93451},
    /*       kaon */ {  14.29133,    0.33162,    0.36903,    2.62903},
    /*   electron */ {  14.33684,    0.21674,    0.36806,    2.60754},
    /*   deuteron */ {  11.63070,    2.17617,    0.15694,    0.53711}
  };
#endif /* __FitG4F__ */
  Double_t Value = 0;
  Int_t icase = (Int_t) par[8];
  Int_t i1 = 0;
  Int_t i2 = 4;
  if (icase >= 0) {i1 = i2 = icase;}
#ifdef __FitG4F__
  TF1 *g = GG();
#endif /* __FitG4F__ */
  for (i = i1; i <= i2; i++) { 
#ifndef __FitG4F__
    Double_t Sigma = sigma;
    if (Peaks[i].N == 0) {
      Value += frac[i]*TMath::Gaus(x[0],scale*(par[1]+Peaks[i].peak),Sigma,1);
    } else {
      for (Int_t ix = 0; ix < Peaks[i].N; ix++) {
	Value += frac[i]*TMath::Gaus(x[0],scale*(par[1]+Peaks[i].X[ix]),Sigma,1)*Peaks[i].Y[ix];
      }
    }
    //    cout << "i\t" << i << "\tx = " << x[0] << " frac " << frac[i] << "\t" << Value << endl;
#else /* __FitG4F__ */
    Double_t pars[4] = {0, parMIP[i][1] + mu, parMIP[i][2] + sigma, parMIP[i][3]};
    Value += frac[i]*g->EvalPar(x, pars);
#endif /* __FitG4F__ */
  }
  if (fgITH1)         Value *= fgITH1->Interpolate(x[0]);
  return par[7]*TMath::Exp(par[0])*Value;
}
//________________________________________________________________________________
#ifndef __FitG4F__
// fit in momentum range p = 0.45 - 0.50 GeV/c
 TF1 *FitGF
#else /* __FitG4F__ */
// fit in momentum range p = 0.526 +/- 0.05;
 TF1 *FitG4F
#endif /* __FitG4F__ */
   (TH1 *proj, Option_t *opt="", TH1D *proj20 = 0) {
  if (! proj) return 0;
  if (proj20) {
#if 0
    proj20->Fit("gaus");
    TF1 *gaus = (TF1 *) proj20->GetListOfFunctions()->FindObject("gaus");
    if (gaus) {
      mean20 = gaus->GetParameter(1);
      RMS20  = gaus->GetParameter(2);
    }
#endif
    SafeDelete(fgITH1);
    fgITH1 = ITH1(proj20);
  }
  
  TString Opt(opt);
  //  Bool_t quet = Opt.Contains("Q",TString::kIgnoreCase);
#ifndef __FitG4F__
  TF1 *g2 = (TF1*) gROOT->GetFunction("GF");
#else /* __FitG4F__ */
  TF1 *g2 = (TF1*) gROOT->GetFunction("G4F");
#endif /* __FitG4F__ */
  if (! g2) {
#ifndef __FitG4F__
    g2 = new TF1("GF",gfFunc, -5, 5, 10);
#else /* __FitG4F__ */
    g2 = new TF1("G4F",gf4Func, -5, 5, 10);
#endif /* __FitG4F__ */
    g2->SetParName(0,"norm"); g2->SetParLimits(0,-80,80);
    g2->SetParName(1,"mu");     g2->SetParLimits(1,-3.0,0.5);
    g2->SetParName(2,"Sigma");  g2->SetParLimits(2,0.05,0.8);
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
//________________________________________________________________________________
