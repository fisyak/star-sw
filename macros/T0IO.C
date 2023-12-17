#include "TTree.h"
#include "TFile.h"
#include "TString.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1.h"
#include "TGraphErrors.h"
#include "Riostream.h"
#include "TMultiGraph.h"
#include "PrintPars.C"
#include "TLegend.h"
#include "TLine.h"
#include "TMath.h"
void T0IO() {
  TTree *FitP = (TTree *) gDirectory->Get("FitP");
  if (! FitP) return;
  const Char_t *Plot[4][2] = {
    {"MuWO", "(100,1,5)"}, 
    {"MuEO", "(100,1,5)"}, 
    {"MuWI", "(100,7,9.5)"}, 
    {"MuEI", "(100,7,9.5)"}
  };
  const Char_t *Cuts[4] = {"row>40&&sector<=12", "row>40&&sector>12","row<=40&&sector<=12", "row<=40&&sector>12"};
  TCanvas *c1 = new TCanvas();
  c1->Divide(2,2);
  for (Int_t we = 0; we < 4; we++) {
    c1->cd(we+1);
    FitP->Draw(Form("mu>>%s%s",Plot[we][0],Plot[we][1]),Cuts[we]);
    TH1 *Mu = (TH1 *) gDirectory->Get(Plot[we][0]);
    if (! Mu) continue;
    Mu->Fit("gaus");
    TF1 *f = (TF1 *) Mu->GetListOfFunctions()->FindObject("gaus");
    if (f) PrintPars(f,Form("%s %s",Mu->GetName(),gDirectory->GetName()));
  }						  
}
/*
================================================================================
   foreach f (`find . -name "*T.root"`) 
     root.exe ${f} T0IO.C
   end
*/
void DrawT0() {
  struct Par_t {
    Double_t constant, mean, sigma;
    const Char_t *side;
    const Char_t *file;
  };
#if 0
  Par_t Pars[] = {
    //   {  1.004978,    2.92744,   8.098395 "West", "RF/2021/OO_fcsTiming"         },
    //   {  1.075551,   3.097391,   4.242367 "East", "RF/2021/OO_fcsTiming"	 },
   {  255.0117,   3.147689, 0.02287021, "West", "RF/2019/7p7GeV"		 },
   {  153.3495,   3.165697, 0.05265003, "East", "RF/2019/7p7GeV"		 },
   {  267.8023,   3.160431,  0.0211617, "West", "RF/2019/9p2GeV"		 },
   {  161.0222,   3.148741, 0.03245417, "East", "RF/2019/9p2GeV"		 },
   {   310.269,   3.130433,  0.0189115, "West", "RF/2019/14p5GeV"		 },
   {  242.0756,   3.141458, 0.02130946, "East", "RF/2019/14p5GeV"		 },
   {  262.0526,   3.137994, 0.02237738, "West", "RF/2019/19GeV"		 },
   {  225.3951,   3.144458, 0.02299549, "East", "RF/2019/19GeV"		 },
   {  262.0182,   3.095061, 0.02210015, "West", "RF/2019/AuAu200GeV"		 },
   {  208.0415,   3.103631, 0.02562413, "East", "RF/2019/AuAu200GeV"		 },
   {  41.04007,   3.377514,  0.1270849, "West", "RF/2019/3p85GeV_fixedTarget"	 },
   {  122.8665,   3.219118,  0.0493599, "East", "RF/2019/3p85GeV_fixedTarget"	 },
   {  110.9951,   3.279114, 0.05109338, "West", "RF/2019/4p59GeV_fixedTarget"	 },
   {  175.4914,   3.146206, 0.02841125, "East", "RF/2019/4p59GeV_fixedTarget"	 },
   {  72.64506,   3.333408, 0.07788013, "West", "RF/2019/7.3GeV_fixedTarget"	 },
   {  143.4192,   3.133782, 0.04149963, "East", "RF/2019/7.3GeV_fixedTarget"	 },
   {   95.6114,   3.351249, 0.06000689, "West", "RF/2019/31GeV_fixedTarget"	 },
   {  164.1814,   3.138081, 0.03302661, "East", "RF/2019/31GeV_fixedTarget"	 },

   {  233.1601,   3.120758, 0.02796196, "West", "RF/2020/7p7GeV"		 },
   {  146.8942,   3.109967, 0.03377748, "East", "RF/2020/7p7GeV"		 },
   {  288.8749,   3.148626, 0.02123645, "West", "RF/2020/9p2GeV"		 },
   {  203.6812,   3.144536, 0.02611329, "East", "RF/2020/9p2GeV"		 },
   {  309.8087,   3.135887,  0.0195033, "West", "RF/2020/9p2bGeV"		 },
   {  233.3846,   3.140815,  0.0220561, "East", "RF/2020/9p2bGeV"		 },
   {  272.3692,   3.145627, 0.02252355, "West", "RF/2020/9p2cGeV"		 },
   {  223.4609,   3.143949, 0.02362568, "East", "RF/2020/9p2cGeV"		 },
   {  338.7888,   3.169434,  0.0181534, "West", "RF/2020/11p5GeV"		 },
   {  253.9145,   3.179238, 0.01988923, "East", "RF/2020/11p5GeV"		 },
   {  100.6778,   3.359299, 0.05977085, "West", "RF/2020/5p75GeV_fixedTarget"	 },
   {  135.0054,   3.191092, 0.03875909, "East", "RF/2020/5p75GeV_fixedTarget"	 },
   {   110.928,   3.341445, 0.05370213, "West", "RF/2020/7p3GeV_fixedTarget"	 },
   {  188.0561,   3.177835, 0.02673599, "East", "RF/2020/7p3GeV_fixedTarget"	 },
   {  114.7705,   3.264784, 0.05320509, "West", "RF/2020/9p8GeV_fixedTarget"	 },
   {  196.8841,    3.10424, 0.02816639, "East", "RF/2020/9p8GeV_fixedTarget"	 },
   {  129.1341,   3.366228, 0.04665191, "West", "RF/2020/19p5GeV_fixedTarget"	 },
   {  111.4482,   3.351795, 0.05437656, "West", "RF/2020/13p5GeV_fixedTarget"	 },
   {  137.4255,   3.156001, 0.04167376, "East", "RF/2020/13p5GeV_fixedTarget"	 },
   {  187.8706,   3.181502,  0.0270363, "East", "RF/2020/19p5GeV_fixedTarget"	 },
   {  186.3099,   3.306682, 0.03194783, "West", "RF/2020/26p5GeV_fixedTarget"	 },
   {  178.6215,   3.143151, 0.02713066, "East", "RF/2020/26p5GeV_fixedTarget"	 },
   {  142.9321,   3.290447, 0.04241752, "West", "RF/2020/31p2GeV_fixedTarget"	 },
   {  201.6573,   3.108356, 0.02637622, "East", "RF/2020/31p2GeV_fixedTarget"	 },

   {  102.6802,   3.121259, 0.05735074, "West", "FF/2021/7p7GeV"		 },
   {  91.38142,   3.102908, 0.06489057, "East", "FF/2021/7p7GeV"		 },
   {  268.0141,   3.100225,  0.0228613, "West", "RF/2021/7p7GeV"		 },
   {  205.4763,   3.105148, 0.02606395, "East", "RF/2021/7p7GeV"		 },
   {  260.4636,   3.133969, 0.02339815, "West", "RF/2021/17p3GeV"		 },
   {  182.5807,   3.142006,  0.0316124, "East", "RF/2021/17p3GeV"		 },
   {  211.3869,   3.089382, 0.02892572, "West", "RF/2021/OO_200GeV"		 },
   {  154.5608,   3.103422, 0.03836326, "East", "RF/2021/OO_200GeV"		 },
   {  235.0709,   3.087147, 0.02594659, "West", "RF/2021/ps_OO_200GeV"	 },
   {  177.4542,   3.096191, 0.03190923, "East", "RF/2021/ps_OO_200GeV"	 },
   {  216.2541,   3.089258, 0.02813173, "West", "FF/2021/FF_OO_200GeV"	 },
   {  156.4271,   3.101733, 0.03729073, "East", "FF/2021/FF_OO_200GeV"	 },
   {  207.6432,   3.120313, 0.02942408, "West", "RF/2021/dAu200GeV"		 },
   {  151.8846,   3.103271, 0.03825758, "East", "RF/2021/dAu200GeV"		 },
   {  153.2588,   3.247484, 0.03785886, "West", "RF/2021/3p85GeV_fixedTarget"	 },
   {  175.8477,   3.168067, 0.03229201, "East", "RF/2021/3p85GeV_fixedTarget"	 },
   {  106.6232,   3.326399, 0.05560521, "West", "RF/2021/26p5GeV_fixedTarget"	 },
   {  152.4479,   3.120982, 0.03782427, "East", "RF/2021/26p5GeV_fixedTarget"	 },
   {  104.1814,   3.271051, 0.05809575, "West", "RF/2021/44p5GeV_fixedTarget"	 },
   {  148.8667,   3.064479, 0.03919209, "East", "RF/2021/44p5GeV_fixedTarget"	 },
   {  92.12102,   3.268433, 0.06439169, "West", "RF/2021/70GeV_fixedTarget"	 },
   {  154.4135,   3.049639, 0.03747944, "East", "RF/2021/70GeV_fixedTarget"	 },
   {  82.44791,   3.265231, 0.07228665, "West", "RF/2021/100GeV_fixedTarget"	 },
   {  140.2155,    3.05122, 0.04167032, "East", "RF/2021/100GeV_fixedTarget"	 },
     //   {  1.090474,   3.234595,   3.663795, "West", "RF/2022/pp500GeV"		 },
     //   {  1.087494,  0.9568783,   7.525211, "East", "RF/2022/pp500GeV"		 },

   {  209.9267,   3.047919, 0.02834889, "West", "RF/2023/AuAu200GeV"		 },
   {   170.668,   3.077919, 0.03670437, "East", "RF/2023/AuAu200GeV"		 }
  };
  Int_t N = sizeof(Pars)/sizeof(Par_t);
  TArrayD X(N); Double_t *x = X.GetArray();
  TArrayD Y(N); Double_t *y = Y.GetArray();
  TArrayD E(N); Double_t *e = E.GetArray();
  TMultiGraph *mg = new TMultiGraph("T0","T0");
  TString Field;
  TString COLFXT;
  TString WestEast;
  Int_t style = 21;
  Int_t color =  1;
  TLegend *l = new TLegend(0.6,0.6,0.9,0.9);
  Double_t x2019 = -2, x2020 = -2, x2021 = -2, x2022 = -2, x2023 = -2; 
  for (Int_t ff = 0; ff < 2; ff++) { // 0 ->", "FF, 1 ->", "RF
    if (ff == 0) {Field = "FF"; style = 22;}
    else         {Field = "RF"; style = 23;}
    for (Int_t we = 0; we < 2; we++) {// 0 -> West, 1 -> East
      if (we == 0) WestEast = "West";
      else         WestEast = "East";
      for (Int_t cf = 0; cf < 2; cf++) {// 0 -> Collider; 1 -> fixedTarget
	if (cf == 0) COLFXT = "COL";
	else         COLFXT = "FXT";
	color = we + 1 + 2*cf;
	Int_t np = 0;
	for (Int_t i = 0; i < N; i++) {
	  TString side(Pars[i].side);
	  TString trig(Pars[i].file);
	  if (x2019 < -1 && trig.Contains("2019")) {x2019 = i - 0.5;} 
	  if (x2020 < -1 && trig.Contains("2020")) {x2020 = i - 0.5;} 
	  if (x2021 < -1 && trig.Contains("2021")) {x2021 = i - 0.5;} 
	  if (x2022 < -1 && trig.Contains("2022")) {x2022 = i - 0.5;} 
	  if (x2023 < -1 && trig.Contains("2023")) {x2023 = i - 0.5;} 
	  if (! trig.Contains(Field)) continue;
	  if (side != WestEast) continue;
	  if (cf && ! trig.Contains("_fixedTarget")) continue;
	  x[np] = i;
	  y[np] = Pars[i].mean;
	  e[np] = Pars[i].sigma;
	  cout << "i = " << i << " x = " << x[np] << " y = " << y[np] << " e = " << e[np] << "\t" << Pars[i].side << "\t" << Pars[i].file <<  endl;
	  np++;
	}
	if (np) {
	  TGraphErrors *gr = new TGraphErrors(np, x, y, 0, e);
	  gr->SetMarkerStyle(style);
	  gr->SetMarkerColor(color);
	  gr->Draw("axp");
	  mg->Add(gr);
	  l->AddEntry(gr,Form("%s %s %s",Field.Data(), COLFXT.Data(), WestEast.Data()), "p");
	}
      }
    }
  }
#else 
  Par_t Pars[][4] = {
    {
      {  102.6802,   3.121259, 0.05735074, "MuWO", "FF/2021/7p7GeV"},
      {  91.38142,   3.102908, 0.06489057, "MuEO", "FF/2021/7p7GeV"},
      {  59.12153,   8.721166, 0.06516688, "MuWI", "FF/2021/7p7GeV"},
      {  67.51456,   8.724468, 0.05133089, "MuEI", "FF/2021/7p7GeV"}
    }, {
      {  216.2541,   3.089258, 0.02813173, "MuWO", "FF/2021/FF_OO_200GeV"},
      {  156.4271,   3.101733, 0.03729073, "MuEO", "FF/2021/FF_OO_200GeV"},
      {  115.1864,   8.693279, 0.03448275, "MuWI", "FF/2021/FF_OO_200GeV"},
      {  107.5736,     8.7039, 0.03296463, "MuEI", "FF/2021/FF_OO_200GeV"}
    }, {
      {   310.269,   3.130433,  0.0189115, "MuWO", "RF/2019/14p5GeV"},
      {  242.0756,   3.141458, 0.02130946, "MuEO", "RF/2019/14p5GeV"},
      {  151.0147,   8.768648,  0.0262073, "MuWI", "RF/2019/14p5GeV"},
      {  146.0095,   8.772423, 0.02636757, "MuEI", "RF/2019/14p5GeV"}
    }, {
      {  262.0526,   3.137994, 0.02237738, "MuWO", "RF/2019/19GeV"},
      {  225.3951,   3.144458, 0.02299549, "MuEO", "RF/2019/19GeV"},
      {  142.9451,   8.770271, 0.02806051, "MuWI", "RF/2019/19GeV"},
      {   144.602,   8.772194, 0.02675858, "MuEI", "RF/2019/19GeV"}
    }, {
      {   95.6114,   3.351249, 0.06000689, "MuWO", "RF/2019/31GeV_fixedTarget"},
      {  164.1814,   3.138081, 0.03302661, "MuEO", "RF/2019/31GeV_fixedTarget"},
      {  42.85278,   8.847375, 0.08636577, "MuWI", "RF/2019/31GeV_fixedTarget"},
      {  118.0132,   8.729254, 0.03177695, "MuEI", "RF/2019/31GeV_fixedTarget"}
    }, {
      {  41.04007,   3.377514,  0.1270849, "MuWO", "RF/2019/3p85GeV_fixedTarget"}, //
      {  122.8665,   3.219118,  0.0493599, "MuEO", "RF/2019/3p85GeV_fixedTarget"},
      {  29.32793,    8.87609,  0.1245699, "MuWI", "RF/2019/3p85GeV_fixedTarget"}, //
      {  62.61545,   8.891959, 0.06071914, "MuEI", "RF/2019/3p85GeV_fixedTarget"}
    }, {
      {  110.9951,   3.279114, 0.05109338, "MuWO", "RF/2019/4p59GeV_fixedTarget"},
      {  175.4914,   3.146206, 0.02841125, "MuEO", "RF/2019/4p59GeV_fixedTarget"},
      {  77.00757,   8.771029, 0.05091395, "MuWI", "RF/2019/4p59GeV_fixedTarget"},
      {  127.8729,   8.760997, 0.03012788, "MuEI", "RF/2019/4p59GeV_fixedTarget"}
    }, {
      {  72.64506,   3.333408, 0.07788013, "MuWO", "RF/2019/7.3GeV_fixedTarget"},
      {  143.4192,   3.133782, 0.04149963, "MuEO", "RF/2019/7.3GeV_fixedTarget"},
      {  49.05706,    8.79126, 0.07313808, "MuWI", "RF/2019/7.3GeV_fixedTarget"},
      {  115.2363,   8.740567, 0.03443441, "MuEI", "RF/2019/7.3GeV_fixedTarget"}
    }, {
      {  255.0117,   3.147689, 0.02287021, "MuWO", "RF/2019/7p7GeV"},
      {  153.3495,   3.165697, 0.05265003, "MuEO", "RF/2019/7p7GeV"},
      {  150.2271,   8.806047, 0.02654941, "MuWI", "RF/2019/7p7GeV"},
      {  145.8098,   8.812027, 0.02593081, "MuEI", "RF/2019/7p7GeV"}
    }, {
      {  267.8023,   3.160431,  0.0211617, "MuWO", "RF/2019/9p2GeV"},
      {  161.0222,   3.148741, 0.03245417, "MuEO", "RF/2019/9p2GeV"},
      {  136.0441,   8.798936, 0.02922648, "MuWI", "RF/2019/9p2GeV"},
      {  127.7846,   8.798978, 0.02933669, "MuEI", "RF/2019/9p2GeV"}
    }, {
      {  262.0182,   3.095061, 0.02210015, "MuWO", "RF/2019/AuAu200GeV"},
      {  208.0415,   3.103631, 0.02562413, "MuEO", "RF/2019/AuAu200GeV"},
      {  139.2967,   8.712924,  0.0281318, "MuWI", "RF/2019/AuAu200GeV"},
      {  8.236193,    8.32691,  0.5207972, "MuEI", "RF/2019/AuAu200GeV"} // 
    }, {
      {  338.7888,   3.169434,  0.0181534, "MuWO", "RF/2020/11p5GeV"},
      {  253.9145,   3.179238, 0.01988923, "MuEO", "RF/2020/11p5GeV"},
      {  131.0895,   8.800587, 0.03021409, "MuWI", "RF/2020/11p5GeV"},
      {     129.9,   8.803281, 0.02716026, "MuEI", "RF/2020/11p5GeV"}
    }, {
      {  111.4482,   3.351795, 0.05437656, "MuWO", "RF/2020/13p5GeV_fixedTarget"},
      {  137.4255,   3.156001, 0.04167376, "MuEO", "RF/2020/13p5GeV_fixedTarget"},
      {  56.87772,   8.820333, 0.06536143, "MuWI", "RF/2020/13p5GeV_fixedTarget"},
      {  107.0287,   8.756924, 0.03249489, "MuEI", "RF/2020/13p5GeV_fixedTarget"}
    }, {
      {  129.1341,   3.366228, 0.04665191, "MuWO", "RF/2020/19p5GeV_fixedTarget"},
      {  187.8706,   3.181502,  0.0270363, "MuEO", "RF/2020/19p5GeV_fixedTarget"},
      {  51.65459,   8.834379, 0.07429115, "MuWI", "RF/2020/19p5GeV_fixedTarget"},
      {   104.115,   8.774715, 0.03350758, "MuEI", "RF/2020/19p5GeV_fixedTarget"},
    }, {
      {  186.3099,   3.306682, 0.03194783, "MuWO", "RF/2020/26p5GeV_fixedTarget"},
      {  178.6215,   3.143151, 0.02713066, "MuEO", "RF/2020/26p5GeV_fixedTarget"},
      {  69.80663,    8.77704,  0.0546305, "MuWI", "RF/2020/26p5GeV_fixedTarget"},
      {  111.3475,   8.725338, 0.03114574, "MuEI", "RF/2020/26p5GeV_fixedTarget"}
    }, {
      {  142.9321,   3.290447, 0.04241752, "MuWO", "RF/2020/31p2GeV_fixedTarget"},
      {  201.6573,   3.108356, 0.02637622, "MuEO", "RF/2020/31p2GeV_fixedTarget"},
      {  64.13661,   8.766964, 0.06070642, "MuWI", "RF/2020/31p2GeV_fixedTarget"},
      {  115.2904,   8.696495, 0.03111709, "MuEI", "RF/2020/31p2GeV_fixedTarget"}
    }, {
      {  100.6778,   3.359299, 0.05977085, "MuWO", "RF/2020/5p75GeV_fixedTarget"},
      {  135.0054,   3.191092, 0.03875909, "MuEO", "RF/2020/5p75GeV_fixedTarget"},
      {  57.96419,    8.81423, 0.06437654, "MuWI", "RF/2020/5p75GeV_fixedTarget"},
      {  104.1649,   8.800316, 0.03310795, "MuEI", "RF/2020/5p75GeV_fixedTarget"}
    }, {
      {   110.928,   3.341445, 0.05370213, "MuWO", "RF/2020/7p3GeV_fixedTarget"},
      {  188.0561,   3.177835, 0.02673599, "MuEO", "RF/2020/7p3GeV_fixedTarget"},
      {  62.35919,   8.797544, 0.06160593, "MuWI", "RF/2020/7p3GeV_fixedTarget"},
      {  109.5326,   8.776571, 0.03211485, "MuEI", "RF/2020/7p3GeV_fixedTarget"}
    }, {
      {  233.1601,   3.120758, 0.02796196, "MuWO", "RF/2020/7p7GeV"},
      {  146.8942,   3.109967, 0.03377748, "MuEO", "RF/2020/7p7GeV"},
      {  140.5749,   8.736427, 0.02750941, "MuWI", "RF/2020/7p7GeV"},
      {  117.1473,   8.745811, 0.02929181, "MuEI", "RF/2020/7p7GeV"}
    }, {
      {  309.8087,   3.135887,  0.0195033, "MuWO", "RF/2020/9p2bGeV"},
      {  233.3846,   3.140815,  0.0220561, "MuEO", "RF/2020/9p2bGeV"},
      {   130.393,   8.776739, 0.03057199, "MuWI", "RF/2020/9p2bGeV"},
      {  122.2625,   8.773077, 0.02779478, "MuEI", "RF/2020/9p2bGeV"}
    }, {
      {  272.3692,   3.145627, 0.02252355, "MuWO", "RF/2020/9p2cGeV"},
      {  223.4609,   3.143949, 0.02362568, "MuEO", "RF/2020/9p2cGeV"},
      {  126.9799,   8.779243, 0.03161337, "MuWI", "RF/2020/9p2cGeV"},
      {  130.5603,   8.782811, 0.02735698, "MuEI", "RF/2020/9p2cGeV"}
    }, {
      {  288.8749,   3.148626, 0.02123645, "MuWO", "RF/2020/9p2GeV"},
      {  203.6812,   3.144536, 0.02611329, "MuEO", "RF/2020/9p2GeV"},
      {  122.6655,   8.779209, 0.03215757, "MuWI", "RF/2020/9p2GeV"},
      {  121.1067,   8.778081, 0.02917678, "MuEI", "RF/2020/9p2GeV"}
    }, {
      {  114.7705,   3.264784, 0.05320509, "MuWO", "RF/2020/9p8GeV_fixedTarget"},
      {  196.8841,    3.10424, 0.02816639, "MuEO", "RF/2020/9p8GeV_fixedTarget"},
      {   69.1886,    8.73694, 0.05665068, "MuWI", "RF/2020/9p8GeV_fixedTarget"},
      {  118.5827,   8.700129, 0.02966198, "MuEI", "RF/2020/9p8GeV_fixedTarget"}
    }, {
      {  82.44791,   3.265231, 0.07228665, "MuWO", "RF/2021/100GeV_fixedTarget"},
      {  140.2155,    3.05122, 0.04167032, "MuEO", "RF/2021/100GeV_fixedTarget"},
      {  45.23052,   8.783534, 0.08083543, "MuWI", "RF/2021/100GeV_fixedTarget"},
      {  119.5852,   8.636735, 0.02996211, "MuEI", "RF/2021/100GeV_fixedTarget"}
    }, {
      {  260.4636,   3.133969, 0.02339815, "MuWO", "RF/2021/17p3GeV"},
      {  182.5807,   3.142006,  0.0316124, "MuEO", "RF/2021/17p3GeV"},
      {  128.7176,   8.752624, 0.03107439, "MuWI", "RF/2021/17p3GeV"},
      {  122.6977,   8.762817, 0.02807269, "MuEI", "RF/2021/17p3GeV"}
    }, {
      {  106.6232,   3.326399, 0.05560521, "MuWO", "RF/2021/26p5GeV_fixedTarget"},
      {  152.4479,   3.120982, 0.03782427, "MuEO", "RF/2021/26p5GeV_fixedTarget"},
      {  43.39728,   8.802675, 0.08593888, "MuWI", "RF/2021/26p5GeV_fixedTarget"},
      {  109.4585,   8.704796, 0.03222758, "MuEI", "RF/2021/26p5GeV_fixedTarget"}
    }, {
      {  153.2588,   3.247484, 0.03785886, "MuWO", "RF/2021/3p85GeV_fixedTarget"},
      {  175.8477,   3.168067, 0.03229201, "MuEO", "RF/2021/3p85GeV_fixedTarget"},
      {  97.46459,   8.744511, 0.03899805, "MuWI", "RF/2021/3p85GeV_fixedTarget"},
      {  117.1453,   8.766018,   0.030293, "MuEI", "RF/2021/3p85GeV_fixedTarget"}
    }, {
      {  104.1814,   3.271051, 0.05809575, "MuWO", "RF/2021/44p5GeV_fixedTarget"},
      {  148.8667,   3.064479, 0.03919209, "MuEO", "RF/2021/44p5GeV_fixedTarget"},
      {   56.8217,   8.758482,  0.0678011, "MuWI", "RF/2021/44p5GeV_fixedTarget"},
      {  113.7265,   8.652222, 0.03156258, "MuEI", "RF/2021/44p5GeV_fixedTarget"}
    }, {
      {  92.12102,   3.268433, 0.06439169, "MuWO", "RF/2021/70GeV_fixedTarget"},
      {  154.4135,   3.049639, 0.03747944, "MuEO", "RF/2021/70GeV_fixedTarget"},
      {   42.6084,    8.76926, 0.08817814, "MuWI", "RF/2021/70GeV_fixedTarget"},
      {  110.2627,   8.639269, 0.03199599, "MuEI", "RF/2021/70GeV_fixedTarget"}
    }, {
      {  268.0141,   3.100225,  0.0228613, "MuWO", "RF/2021/7p7GeV"},
      {  205.4763,   3.105148, 0.02606395, "MuEO", "RF/2021/7p7GeV"},
      {   143.897,   8.734364, 0.02763977, "MuWI", "RF/2021/7p7GeV"},
      {   134.603,   8.743917, 0.02598443, "MuEI", "RF/2021/7p7GeV"}
    }, {
      {  207.6432,   3.120313, 0.02942408, "MuWO", "RF/2021/dAu200GeV"},
      {  151.8846,   3.103271, 0.03825758, "MuEO", "RF/2021/dAu200GeV"},
      {  77.66852,   8.690533, 0.04763918, "MuWI", "RF/2021/dAu200GeV"},
      {   93.5372,   8.698256, 0.03655092, "MuEI", "RF/2021/dAu200GeV"}
    }, {
      {  211.3869,   3.089382, 0.02892572, "MuWO", "RF/2021/OO_200GeV"},
      {  154.5608,   3.103422, 0.03836326, "MuEO", "RF/2021/OO_200GeV"},
      {  114.3833,   8.696818, 0.03442721, "MuWI", "RF/2021/OO_200GeV"},
      {  95.39799,   8.708639, 0.03769793, "MuEI", "RF/2021/OO_200GeV"}
    }, {
      {  235.0709,   3.087147, 0.02594659, "MuWO", "RF/2021/ps_OO_200GeV"},
      {  177.4542,   3.096191, 0.03190923, "MuEO", "RF/2021/ps_OO_200GeV"},
      {  115.2469,   8.698526, 0.03481188, "MuWI", "RF/2021/ps_OO_200GeV"},
      {  106.3163,   8.707186, 0.03259602, "MuEI", "RF/2021/ps_OO_200GeV"}
    }, {
      {  209.9267,   3.047919, 0.02834889, "MuWO", "RF/2023/AuAu200GeV"},
      {   170.668,   3.077919, 0.03670437, "MuEO", "RF/2023/AuAu200GeV"},
      {  12.36515,   9.743028, 0.02789854, "MuWI", "RF/2023/AuAu200GeV"},
      {  538.5782,   10.01384,  0.1982299, "MuEI", "RF/2023/AuAu200GeV"}
    }
  };
#endif
  Int_t N = sizeof(Pars)/sizeof(Par_t[4]);
  TArrayD X(N); Double_t *x = X.GetArray();
  TArrayD Y(N); Double_t *y = Y.GetArray();
  TArrayD E(N); Double_t *e = E.GetArray();
  TMultiGraph *mg = new TMultiGraph("T0","T0");
  TString Field;
  TString COLFXT;
  TString WestEast;
  Int_t style = 21;
  Int_t color =  1;
  TLegend *l = new TLegend(0.6,0.6,0.9,0.9);
  Double_t x2019 = -2, x2020 = -2, x2021 = -2, x2022 = -2, x2023 = -2; 
  for (Int_t ff = 0; ff < 2; ff++) { // 0 ->", "FF, 1 ->", "RF
    if (ff == 0) {Field = "FF"; style = 22;}
    else         {Field = "RF"; style = 23;}
    for (Int_t io = 0; io < 1; io++) {// 0 -> O, 1 -> I
      for (Int_t we = 0; we < 2; we++) {// 0 -> West, 1 -> East
	if (we == 0) WestEast = "W";
	else         WestEast = "E";
	for (Int_t cf = 0; cf < 2; cf++) {// 0 -> Collider; 1 -> fixedTarget
	  if (cf == 0) COLFXT = "COL";
	  else         COLFXT = "FXT";
	  color = we + 1 + 2*cf;
	  Int_t np = 0;
	  for (Int_t i = 0; i < N; i++) {
	    TString side(Pars[i][we+2*io].side);
	    TString trig(Pars[i][we+2*io].file);
	    if (x2019 < -1 && trig.Contains("2019")) {x2019 = i - 0.5;} 
	    if (x2020 < -1 && trig.Contains("2020")) {x2020 = i - 0.5;} 
	    if (x2021 < -1 && trig.Contains("2021")) {x2021 = i - 0.5;} 
	    if (x2022 < -1 && trig.Contains("2022")) {x2022 = i - 0.5;} 
	    if (x2023 < -1 && trig.Contains("2023")) {x2023 = i - 0.5;} 
	    if (! trig.Contains(Field)) continue;
	    if (! side.Contains(WestEast)) continue;
	    if (cf && ! trig.Contains("_fixedTarget")) continue;
	    x[np] = i;
#if 0	    
	    y[np] = Pars[i][we+2*io].mean;
	    e[np] = Pars[i][we+2*io].sigma;
#else
	    y[np] = Pars[i][we+2].mean - Pars[i][we].mean;
	    e[np] = TMath::Sqrt(Pars[i][we+2].sigma*Pars[i][we+2].sigma + Pars[i][we].sigma*Pars[i][we].sigma);
#endif
	    cout << "i = " << i << " x = " << x[np] << " y = " << y[np] << " e = " << e[np] << "\t" << Pars[i][we+2*io].side << "\t" << Pars[i][we+2*io].file <<  endl;
	    np++;
	  }
	  if (np) {
	    TGraphErrors *gr = new TGraphErrors(np, x, y, 0, e);
	    gr->SetMarkerStyle(style);
	    gr->SetMarkerColor(color);
	    gr->Draw("axp");
	    mg->Add(gr);
	    l->AddEntry(gr,Form("%s %s %s",Field.Data(), COLFXT.Data(), WestEast.Data()), "p");
	  }
	}
      }
    }
  }
  mg->Draw("axp");
  l->Draw();
  if (x2019 > -1) {TLine *line = new TLine(x2019, 0, x2019, 10); line->Draw(); } 
  if (x2020 > -1) {TLine *line = new TLine(x2020, 0, x2020, 10); line->Draw(); } 
  if (x2021 > -1) {TLine *line = new TLine(x2021, 0, x2021, 10); line->Draw(); } 
  if (x2022 > -1) {TLine *line = new TLine(x2022, 0, x2022, 10); line->Draw(); } 
  if (x2023 > -1) {TLine *line = new TLine(x2023, 0, x2023, 10); line->Draw(); } 
}

