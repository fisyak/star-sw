void SetHistogramStyle(TH1D* histo, const TString xAxisName, const TString yAxisName)
{
  histo -> GetXaxis()-> SetTitle(xAxisName);
  histo -> GetXaxis()-> SetTitleSize(0.07);
  histo -> GetXaxis()-> SetTitleFont(22);
  histo -> GetXaxis()-> SetTitleColor(kBlack);
  histo -> GetXaxis()-> SetLabelSize(0.07);
  histo -> GetXaxis()-> SetTitleOffset(1);
  histo -> GetXaxis()-> SetLabelFont(22);
  histo -> GetXaxis()-> SetNdivisions(3,5,0);
  histo -> GetYaxis()-> SetTitle(yAxisName);
  histo -> GetYaxis()-> SetTitleSize(0.07);
  histo -> GetYaxis()-> SetTitleFont(22);
  histo -> GetYaxis()-> SetLabelSize(0.07);
  histo -> GetYaxis()-> SetLabelFont(22);
  histo -> GetYaxis()-> SetTitleOffset(1);
  histo -> GetYaxis()-> SetNdivisions(3,5,0);
  histo -> GetYaxis()-> SetRangeUser(0, 1.6*histo->GetMaximum());
}

struct ParticleData {
  TString name;
  int range[4];
  float zoom[2];
  float fit[2];
  float mass;
  float sigma;
  bool isActive;
};

void DalitzMass() 
{
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetTitleColor(0);
//  plain->SetTitleFont(22);
//  plain->SetLabelFont(22);
  gStyle->SetStatColor(0);
  gStyle->SetOptStat(0);
//  plain->SetOptFit(11);
  gStyle->SetOptFit(0);
  gStyle->SetStatW(0.19);
  gStyle->SetStatH(0.7);
  gStyle->SetOptTitle(0);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadTopMargin(0.075);
  gStyle->SetPadBottomMargin(0.18);
  TGaxis::SetMaxDigits(3);
  
  // TString inputFileName = "/home/mzyzak/data/STAR_2024/histo_P23id/all4.root";
  // TString inputFileName = "/home/mzyzak/data/STAR_2024/histo_P23ie/sum/all.root";
  // TString inputFileName = "/home/mzyzak/data/STAR_2024/histo_P23ie/aaa0.root";
  // TString inputFileName = "/home/mzyzak/data/STAR_2024/histo_P23ie/test/2021_old.root";
  // TString inputFileName = "/home/mzyzak/data/STAR_2024/histo_P23ie/test/cand_histos.root";
  // TString inputFileName = "/home/mzyzak/data/STAR_2024/histo_P23ie/test/cand_histos_chiPrimCombined.root";
  // TString inputFileName = "/home/mzyzak/data/STAR_2024/histo_P23ie/test/reference.root";
  
  // TString inputFileName = "/home/mzyzak/data/STAR_2024/p23ie/weakDecay/signal.root";
  TString inputFileName = "/home/mzyzak/data/STAR_2024/p24ia/weakDecay/candidates_0_2021_3AGeV_p24ia_histos.root";

  const int NParticles = 26;
  //                                       name                ctau   pt      zoom        fit
  const ParticleData data[NParticles] = { {"Lambda",          { 0,61, 0,101}, {1.08, 1.25}, {1.1,  1.15}, 1.1159, 0.00142,0 },
                                          {"LN",              {30,61, 0,101}, {2.98, 2.30}, {2.038, 2.055}, 2.0455, 0.0017, 0 },
                                          {"LambdaNN",        {40,61, 0,101}, {2.95, 3.25}, {2.98, 3.02}, 2.990,  0.0013, 0 },
                                          {"H3L",             { 0,61, 0,101}, {2.95, 3.25}, {2.98, 3.02}, 2.9914, 0.0017, 1 },
                                          {"H3Ldppi",         { 0,61, 0,101}, {2.95, 3.25}, {2.975,3.01}, 2.9914, 0.0014, 1 },
                                          {"H4L",             { 0,61, 0,101}, {3.87, 4.17}, {3.902,3.95}, 3.9225, 0.0017, 1 },
                                          {"H4Ltppi",         { 0,61, 0,101}, {3.87, 4.17}, {3.905,3.97}, 3.9225, 0.0012, 1 },
                                          {"H4L_{ddpi}",      {20,61, 0,101}, {3.87, 4.17}, {3.91, 3.96}, 3.9225, 0.0016, 0 },
                                          {"H5L_{tdpi}",      { 0,61, 0,101}, {}, {}, 4.865, 0.002, 0 },
                                          {"H6L_{He6pi}",     {20,61,20,101}, {5.7,  6.0 }, {5.75, 5.79}, 5.763,  0.002,  0 },
                                          {"H6L_{ttpi}",      {20,61, 0,101}, {}, {}, 5.8, 0.002, 0 },
                                          {"He4L",            {10,61, 0,101}, {3.87, 4.17}, {3.905,3.96}, 3.9216, 0.0015, 1 },
                                          {"He5L",            { 0,61, 0,101}, {4.80, 5.10}, {4.82, 4.90}, 4.8398, 0.0015, 1 },
                                          {"He5L_{He3dpi}",   {10,61, 0,101}, {4.80, 5.10}, {4.85, 4.95}, 4.865,  0.0020, 0 },
                                          {"He6L_{Li6pi}",    {20,61,20,101}, {5.7,  6.0 }, {5.75, 5.79}, 5.768,  0.0020, 0 },
                                          {"He6L_{He3tpi}",   { 0,61, 0,101}, {5.7,  6.0 }, {5.76, 5.8 }, 5.778,  0.0020, 0 },
                                          {"He6L_{He4dpi}",   { 0,61, 0,101}, {5.7,  6.0 }, {5.76, 5.8 }, 5.778,  0.0020, 0 },
                                          {"He7L_{He4tpi}",   { 0,61, 0,101}, {6.6,  7.0 }, {6.70, 6.75}, 6.715,  0.0020, 0 },
                                          {"He7L_{Li7pi}",    { 0,61, 0,101}, {6.6,  7.0 }, {6.70, 6.75}, 6.718,  0.0018, 0 },
                                          {"Li6L_{2He3pi}",   {20,60, 0,101}, {}, {}, 5.8, 0.002, 0 },
                                          {"Li7L_{He3He4pi}", {20,61, 0,101}, {6.60, 7.00}, {6.71, 6.77}, 6.735,  0.0025, 0 },
                                          {"Li7L_{Be7pi}",    {20,55, 0,101}, {6.60, 7.00}, {6.69, 6.77}, 6.71,   0.0020, 0 },
                                          {"Li8L_{2He4pi}",   {20,61, 0,101}, {7.55, 7.85}, {7.62, 7.68}, 7.642,  0.0025, 0 },
                                          {"H2L",             {20,60,10,101}, {1.8,  2.8},  {2.035,2.085},2.053,  0.0013, 0 },
                                          {"He3L",            {20,60,10,101}, {2.95, 3.25}, {2.95, 3.25}, 2.990,  0.0013, 0 },
                                          {"LLn",             {20,61,20,101}, {2.95, 3.25}, {2.95, 3.25}, 2.990,  0.0013, 0 }
                                        };
  const TString axisName[NParticles] = { "m_{inv} {p#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {d#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {t#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {^{3}He#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {dp#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {^{4}He#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {tp#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {dd#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {td#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {^{6}He#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {tt#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {^{3}Hep#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {^{4}Hep#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {^{3}Hed#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {^{6}Li#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {^{3}Het#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {^{4}Hed#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {^{4}Het#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {^{7}Li#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {^{3}He^{3}He#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {^{4}He^{3}He#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {^{7}Be#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {^{4}He^{4}He#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {pp#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {ppp#pi^{-}} [GeV/c^{2}]",
                                         "m_{inv} {{}^{3}_{#Lambda}H#pi^{-}} [GeV/c^{2}]"
                                         };
  const TString DecayText[NParticles] = { "#Lambda#rightarrowp#pi^{-}",
                                          "{#Lambdan}#rightarrowd#pi^{-}",
                                          "{#Lambdann}#rightarrowt#pi^{-}",
                                          "{}^{3}_{#Lambda}H#rightarrow^{3}He#pi^{-}",
                                          "{}^{3}_{#Lambda}H#rightarrowdp#pi^{-}",
                                          "{}^{4}_{#Lambda}H#rightarrow^{4}He#pi^{-}",
                                          "{}^{4}_{#Lambda}H#rightarrowtp#pi^{-}",
                                          "{}^{4}_{#Lambda}H#rightarrowdd#pi^{-}",
                                          "{}^{5}_{#Lambda}H#rightarrowtd#pi^{-}",
                                          "{}^{6}_{#Lambda}H#rightarrow^{6}He#pi^{-}",
                                          "{}^{6}_{#Lambda}H#rightarrowtt#pi^{-}",
                                          "{}^{4}_{#Lambda}He#rightarrow^{3}Hep#pi^{-}",
                                          "{}^{5}_{#Lambda}He#rightarrow^{4}Hep#pi^{-}",
                                          "{}^{5}_{#Lambda}He#rightarrow^{3}Hed#pi^{-}",
                                          "{}^{6}_{#Lambda}He#rightarrow^{6}Li#pi^{-}",
                                          "{}^{6}_{#Lambda}He#rightarrow^{3}Het#pi^{-}",
                                          "{}^{6}_{#Lambda}He#rightarrow^{4}Hed#pi^{-}",
                                          "{}^{7}_{#Lambda}He#rightarrow^{4}Het#pi^{-}",
                                          "{}^{7}_{#Lambda}He#rightarrow^{7}Li#pi^{-}",
                                          "{}^{6}_{#Lambda}Li#rightarrow^{3}He^{3}He#pi^{-}",
                                          "{}^{7}_{#Lambda}Li#rightarrow^{4}He^{3}He#pi^{-}",
                                          "{}^{7}_{#Lambda}Li#rightarrow^{7}Be#pi^{-}",
                                          "{}^{8}_{#Lambda}Li#rightarrow^{4}He^{4}He#pi^{-}" ,
                                          "{}^{2}_{#Lambda}H#rightarrowpp#pi^{-}" ,
                                          "{}^{3}_{#Lambda}He#rightarrowppp#pi^{-}",
                                          "#Lambda#LambdaN#rightarrow{}^{3}_{#Lambda}H#pi^{-}"
                                          };
  TString LegendEntry[NParticles][3];
  TLegend *legends[NParticles];
  for(int i=0; i<NParticles; i++) {
    legends[i] = new TLegend(0.35, 0.75, .99, .99);
    legends[i]->SetFillColor(0);
    legends[i]->SetTextSize(0.06);
    legends[i]->SetMargin(0.1);
  }
    
  int nActive=0;
  for(int i=0; i<NParticles; i++)
    nActive += data[i].isActive ? 1 : 0;
  
  TCanvas* c;
  if(nActive == 1) { c = new TCanvas("c", "c", 600, 500); }
  else if(nActive == 2) { c = new TCanvas("c", "c", 1200, 500); c->Divide(2,1); }
  else if(nActive == 3) { c = new TCanvas("c", "c", 1800, 500); c->Divide(3,1); }
  else if(nActive <= 4) { c = new TCanvas("c", "c", 1200, 1000); c->Divide(2,2); }
  else if(nActive <= 6) { c = new TCanvas("c", "c", 1800, 1000); c->Divide(3,2); }
  else if(nActive <= 9) { c = new TCanvas("c", "c", 1800, 1500); c->Divide(3,3); }

  TFile *f1 = new TFile(inputFileName.Data(),"read");  
  
  TH1D* hMass[NParticles];
  TF1* fMass[NParticles];
  
  int nPad = 1;
  for(int i=0; i<NParticles; i++) {
    if(!data[i].isActive) continue;
    
    c->cd(nPad); nPad++;

    TString inputHistoName = "Particles/";
    inputHistoName += data[i].name;
    inputHistoName += "/Total/mother/M";
    std::cout << inputHistoName << std::endl;
    hMass[i] = (TH1D*) f1->Get(inputHistoName);
    hMass[i]->Rebin(4);

    TString bgFunction = "pol5";
    TString fitFunction = "gaus(0)+"; fitFunction+=bgFunction; fitFunction+="(3)"; 
    
    TString nameFit = "massFit"; nameFit += i;
    fMass[i] = new TF1(nameFit.Data(),fitFunction.Data(),data[i].fit[0],data[i].fit[1]);
    fMass[i] -> SetParNames("Const","Mass","Sigma","a0","a1","a2");

    fMass[i] -> SetNpx(1000);
    fMass[i] -> SetLineColor(2);
    fMass[i] -> SetLineWidth(1);
    fMass[i] -> SetParLimits(0, 0, 1000000);
    fMass[i] -> FixParameter(1, data[i].mass);
    fMass[i] -> FixParameter(2, data[i].sigma);
    hMass[i] -> Fit(nameFit.Data(),"QNL","",data[i].fit[0],data[i].fit[1]);
    fMass[i] -> ReleaseParameter(1);
    fMass[i] -> SetParLimits(1, data[i].mass-0.002, data[i].mass+0.002);
    fMass[i] -> ReleaseParameter(2);
    hMass[i] -> Fit(nameFit.Data(),"QNL","",data[i].fit[0],data[i].fit[1]);
    int nParam = fMass[i] -> GetNpar(); 

    for(int j=3; j<nParam; j++)
      fMass[i] -> FixParameter(j,fMass[i]->GetParameter(j));

    hMass[i] -> Fit(nameFit.Data(),"L","",data[i].fit[0],data[i].fit[1]);
//     TFitResultPtr fitParameters = hMass[i] -> Fit(nameFit.Data(),"S","",data[i].fit[0],data[i].fit[1]);
    
    TF1 *fSInt;
    TF1 *fBInt;

    float start = fMass[i]->GetParameter(1) - 3*fMass[i]->GetParameter(2);
    float end   = fMass[i]->GetParameter(1) + 3*fMass[i]->GetParameter(2);
    
//     if(!(fitParameters.Get())) continue;
    
//     std::vector<double> fitCovarianceData(9);
//     TMatrixDSym fitCovariance = fitParameters->GetCovarianceMatrix();
//     for(int iC=0; iC<3; iC++)
//       for(int jC=0; jC<3; jC++)
//         fitCovarianceData[iC*3 + jC] = fitCovariance.GetMatrixArray()[iC*nParam + jC];
//     TMatrixDSym signalCovariance(0,2, &fitCovarianceData[0] );

    nameFit += "int";
    fSInt = new TF1(nameFit.Data(),"gaus",data[i].fit[0],data[i].fit[1]);
    for(int iPar=0; iPar<3; iPar++)
    {
      fSInt -> SetParameter(iPar, fMass[i] -> GetParameter(iPar));
      fSInt -> SetParError(iPar, fMass[i] -> GetParError(iPar));
    }

    nameFit += "BG";

    fBInt = new TF1(nameFit.Data(),bgFunction.Data(),data[i].fit[0],data[i].fit[1]);
    for(int iPar=3; iPar<nParam; iPar++)
    {
      fBInt -> SetParameter(iPar-3, fMass[i] -> GetParameter(iPar));
      fBInt -> SetParError(iPar-3, fMass[i] -> GetParError(iPar));
    }

    double binWidth = hMass[i]->GetXaxis()->GetNbins()/(hMass[i]->GetXaxis()->GetXmax() - hMass[i]->GetXaxis()->GetXmin());
    
    float S = fSInt -> Integral(start,end) * binWidth;
    float B = fBInt -> Integral(start,end) * binWidth;
//     float SError = fSInt -> IntegralError(start,end, fSInt->GetParameters(), signalCovariance.GetMatrixArray())*binWidth;
    
    char tmpString[6];
    sprintf(tmpString,"%1.1f",(fMass[i] -> GetParameter(1)*1000));    
    LegendEntry[i][0] += " M = ";
    LegendEntry[i][0] += tmpString;
    LegendEntry[i][0] += " MeV/c^{2}";
    
    sprintf(tmpString,"%1.1f",(fMass[i] -> GetParameter(2)*1000));    
    LegendEntry[i][1] = "#sigma = ";
    LegendEntry[i][1] += tmpString;
    LegendEntry[i][1] += " MeV/c^{2}  S = ";
    sprintf(tmpString,"%1.1f",S);   
    LegendEntry[i][1] += tmpString;
    
    LegendEntry[i][2] = "S/B = ";
    if((S/B)<10)
    sprintf(tmpString,"%4.2f",(S/B));
    else if((S/B)<100)
    sprintf(tmpString,"%4.1f",(S/B));
    else
    sprintf(tmpString,"%4.0f",(S/B));
    LegendEntry[i][2] += tmpString;
    
    float significance = S/sqrt(S+B);
    
    LegendEntry[i][2] += "  S/#sqrt{S+B} = ";
    if((significance)<10)
    sprintf(tmpString,"%4.2f",(significance));
    else if((significance)<100)
    sprintf(tmpString,"%4.1f",(significance));
    else
    sprintf(tmpString,"%4.0f",(significance));
    LegendEntry[i][2] += tmpString;
    
    std::cout << "S             "  << S << std::endl;
    std::cout << "B             "  << B << std::endl;
    std::cout << "S/B           "  << S/B << std::endl;
    std::cout << "Significance  "  << significance << std::endl;

//     hMass[i]->GetXaxis()->SetRangeUser(data[i].zoom[0], data[i].zoom[1]);
    SetHistogramStyle(hMass[i], axisName[i], "Entries");
    hMass[i]->Draw();
    
    legends[i]->AddEntry(hMass[i], LegendEntry[i][0].Data(),"l");
    legends[i]->AddEntry(hMass[i], LegendEntry[i][1].Data(),"");
    legends[i]->AddEntry(hMass[i], LegendEntry[i][2].Data(),"");
    legends[i]->Draw();
    
    TPaveText *pt = new TPaveText(.7,.65,.7,.65, "brNDC");   
    pt->SetTextSize(0.1);
    pt->SetTextFont(22);
    pt->SetTextColor(2);
    pt->SetFillColor(0);
    pt->SetBorderSize(0);
    pt->AddText(DecayText[i].Data());
    pt->Draw();
      
//     fBInt->Draw("same");
      
//     hMass2->Draw("same");
  }
  
}
