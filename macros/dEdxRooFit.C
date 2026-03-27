#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooFFTConvPdf.h"
#include "RooPlot.h"
#include "RooCFunction1Binding.h" 
#include "RooCFunction3Binding.h"
#include "RooTFnBinding.h" 
#include "RooDataHist.h"
#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooFit.h"
#include "RooRandom.h"
#include "RooFitResult.h"
#include "RooWorkspace.h"
#include "TArrayI.h"
#include "TArrayF.h"
#include "TArrayD.h"
using namespace RooFit ;

class RooRealVar;

class RooLandauZ : public RooAbsPdf {
public:
  RooLandauZ() {} ;
  RooLandauZ(const char *name, const char *title, RooAbsReal& _x, RooAbsReal& _mean, RooAbsReal& _sigma);
  RooLandauZ(const RooLandauZ& other, const char* name=0);
  virtual TObject* clone(const char* newname) const { return new RooLandauZ(*this,newname); }
  inline virtual ~RooLandauZ() { }

  Int_t getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t staticInitOK=kTRUE) const;
  void generateEvent(Int_t code);
  
protected:
  
  RooRealProxy x ;
  RooRealProxy mean ;
  RooRealProxy sigma ;
  
  Double_t evaluate() const ;
  
private:
  
  ClassDef(RooLandauZ,1) // LandauZ Distribution PDF
};

ClassImp(RooLandauZ)


//_____________________________________________________________________________
RooLandauZ::RooLandauZ(const char *name, const char *title, RooAbsReal& _x, RooAbsReal& _mean, RooAbsReal& _sigma) :
  RooAbsPdf(name,title),
  x("x","Dependent",this,_x),
  mean("mean","Mean",this,_mean),
  sigma("sigma","Width",this,_sigma)
{
}
 

//_____________________________________________________________________________
RooLandauZ::RooLandauZ(const RooLandauZ& other, const char* name) : 
  RooAbsPdf(other,name),
  x("x",this,other.x),
  mean("mean",this,other.mean),
  sigma("sigma",this,other.sigma)
{
} 


//_____________________________________________________________________________
Double_t RooLandauZ::evaluate() const
{
  //  return TMath::Landau(x, mean, sigma);
  const Double_t par[2] = {mean, sigma};
  Double_t xd = x;
  return landauZ(&xd,(Double_t *) par);
  //  return xx*TMath::Landau(xx,mpc,sigmad);
  //  return xx*TMath::Landau(xx,mpc,sigmad) / sigmad;

}


//_____________________________________________________________________________
Int_t RooLandauZ::getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t /*staticInitOK*/) const
{
  if (matchArgs(directVars,generateVars,x)) return 1 ;  
  return 0 ;
}


//_____________________________________________________________________________
void RooLandauZ::generateEvent(Int_t code)
{
  assert(code==1) ;
  Double_t xgen ;
  Double_t mpshift  = -0.22278298; // 1.0844535734 + 0.61417;       // Landau maximum location
  // MP shift correction
  Double_t meand = mean;
  Double_t sigmad = sigma;
  Double_t mpc = TMath::Exp(meand) - mpshift * sigmad; 
  while(1) {    
    xgen = RooRandom::randomGenerator()->Landau(mpc,sigma);
    if (xgen <= 0) continue;
    Double_t xgl = TMath::Log(xgen) ;
    if (xgl<x.max() && xgl>x.min()) {
      x = xgl;
      break;
    }
  }
  return;
}
//_______________________________________________________________________________
///.........................................................................//
//--------------------------B E G I N N I N G ------------------------------//
//------------------------L A N D A U   Z    5  function ------------------//
//---------------------------------------------------------------//
Double_t landauZ5(Double_t *x, Double_t *par) {
  // Double_t Norm = par[0];
  Double_t xd = x[0];
  Double_t meand_pi = par[1];
  Double_t meand_pr = par[1] + Peaks[1].peak;
  Double_t sigmad_pi = par[8];
  Double_t sigmad_pr = sigmad_pi;
  Double_t meand_k = par[1] + Peaks[2].peak;
  Double_t sigmad_k = sigmad_pi;
  Double_t meand_el = par[1] + Peaks[3].peak;
  Double_t sigmad_el = sigmad_pi;
  Double_t meand_d = par[1] + Peaks[4].peak;
  Double_t sigmad_d = sigmad_pi;
  Double_t mpshift  = -0.22278298; // 1.0844535734 + 0.61417;       // LandauZ maximum location
  Double_t frac[5];
  frac[1] = TMath::Power(TMath::Sin(par[3]),2);
  frac[2] = TMath::Power(TMath::Sin(par[4]),2);
  //  frac[3] = 0.;
  //  frac[4] = 0.;
    frac[3] = TMath::Power(TMath::Sin(par[5]),2);
    frac[4] = TMath::Power(TMath::Sin(par[6]),2);

  if( ((par[4]==0.)&&(par[5]==0.)&&(par[6]==0.)&&(par[3]!=0.)) || 
      ((par[3]==0.)&&(par[5]==0.)&&(par[6]==0.)&&(par[4]!=0.)) ||
      ((par[3]==0.)&&(par[4]==0.)&&(par[6]==0.)&&(par[5]!=0.)) ||
      ((par[3]==0.)&&(par[4]==0.)&&(par[5]==0.)&&(par[6]!=0.)) )
    {frac[0]=0.;
    }

  else {frac[0] = 1. - frac[1] - frac[2] - frac[3] - frac[4];}
  // MP shift correction
  Double_t mpc_pi = TMath::Exp(meand_pi) - mpshift * sigmad_pi; 
  Double_t mpc_pr = TMath::Exp(meand_pr) - mpshift * sigmad_pr;
  Double_t mpc_k = TMath::Exp(meand_k)   - mpshift * sigmad_k;
  Double_t mpc_el = TMath::Exp(meand_el) - mpshift * sigmad_el;
  Double_t mpc_d = TMath::Exp(meand_d)   - mpshift * sigmad_d;

  Double_t xx = TMath::Exp(xd);

  return (xx*TMath::Landau(xx,mpc_pi,sigmad_pi)*frac[0] + 
	  xx*TMath::Landau(xx,mpc_pr,sigmad_pr)*frac[1] + 
	  xx*TMath::Landau(xx,mpc_k, sigmad_k) *frac[2] + 
	  xx*TMath::Landau(xx,mpc_el,sigmad_el)*frac[3] + 
	  xx*TMath::Landau(xx,mpc_d, sigmad_d) *frac[4])*par[7];
}


//________________________________________________________________________________

//-------------------------L A N D A U   5   C L A S S --------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

class RooLandauZ5:public RooAbsPdf
{

public:
  RooLandauZ5(){}
  RooLandauZ5(const char *name, const char *title, RooAbsReal& _x, 
	      RooAbsReal& _norm, RooAbsReal& _mean_pi, 
	      RooAbsReal& _sigma_pi, RooAbsReal& _sigma_pr, 
	      RooAbsReal& _sigma_k, RooAbsReal& _sigma_el, 
	      RooAbsReal& _sigma_d, RooAbsReal& _total, RooAbsReal& _width);
  RooLandauZ5(const RooLandauZ5& other, const char* name=0);
  virtual TObject *clone(const char *newname) const 
  {    return new RooLandauZ5(*this,newname);  }
  inline virtual ~RooLandauZ5() {}

protected:
  RooRealProxy x;
  RooRealProxy norm;
  RooRealProxy mu;
  RooRealProxy sigma_pi;
  RooRealProxy sigma_pr;
  RooRealProxy sigma_k;
  RooRealProxy sigma_el;
  RooRealProxy sigma_d;
  RooRealProxy total;
  RooRealProxy width;

  Double_t evaluate() const;

private:
  ClassDef(RooLandauZ5,1)
};

ClassImp(RooLandauZ5)

RooLandauZ5::RooLandauZ5(const char *name, const char *title, RooAbsReal& _x,
			 RooAbsReal& _norm, RooAbsReal& _mu, 
			 RooAbsReal& _sigma_pi, RooAbsReal& _sigma_pr,
			 RooAbsReal& _sigma_k, RooAbsReal& _sigma_el, 
			 RooAbsReal& _sigma_d, RooAbsReal& _total,
			 RooAbsReal& _width): 
  RooAbsPdf(name,title), 
  x("x","Dependent",this,_x), 
  norm("norm","Norm",this,_norm), 
  mu("mu","peak position",this,_mu),
  sigma_pi("sigma_pi","Width pion",this,_sigma_pi), 
  sigma_pr("sigma_pr","Width proton",this,_sigma_pr),
  sigma_k("sigma_k","Width kaon",this,_sigma_k),
  sigma_el("sigma_el","Width electron",this,_sigma_el),
  sigma_d("sigma_d","Width deutron",this,_sigma_d),
  total("total","Total",this,_total),
  width("width","Width",this,_width){}

RooLandauZ5::RooLandauZ5(const RooLandauZ5& other, const char* name): 
  RooAbsPdf(other,name), 
  x("x",this,other.x), 
  norm("norm",this,other.norm), 
  mu("mu",this,other.mu),
  sigma_pi("sigma_pi",this,other.sigma_pi), 
  sigma_pr("sigma_pr",this,other.sigma_pr),
  sigma_k("sigma_k",this,other.sigma_k), 
  sigma_el("sigma_el",this,other.sigma_el),
  sigma_d("sigma_d",this,other.sigma_d), 
  total("total",this,other.total), 
  width("width",this,other.width){} 


Double_t RooLandauZ5::evaluate() const{
  const Double_t par[10] = {norm,mu,sigma_pi,sigma_pr,sigma_k,sigma_el,sigma_d,total,width};
  Double_t xd =x;
  return landauZ5(&xd, (Double_t *)par);
}

//---------------------------------------------------------------------//
//------Global variables needed to create TF1 for particle fraction ----//
TF1 *l5xg_func = 0, *func_pi=0, *func_pr=0, *func_k=0, *func_el=0, *func_de=0;
Double_t frac_pr=0.,frac_k=0.,frac_el=-0.,frac_de=-0., frac_pi=0.;

//-------------Function for scaling TF1 ---------------// 
Double_t func_lz5xg_mult(Double_t *x, Double_t *par) {
  if (! l5xg_func) return 0;
  Double_t xd = x[0];
  Double_t mult = par[7];
  Int_t Case = (int)par[9];
  switch(Case){
  case 0: 
    if (! func_pi) return 0;
    return ((func_pi->Eval(xd))*mult*frac_pi);
    break;
  case 1: 
    if (! func_pr) return 0;
    return ((func_pr->Eval(xd))*mult*frac_pr);
    break;
  case 2: 
    if (! func_k) return 0;
    return ((func_k->Eval(xd))*mult*frac_k);
    break;
  case 3: 
    if (! func_el) return 0;
    return ((func_el->Eval(xd))*mult*frac_el);    
    break;
  case 4: 
    if (! func_de) return 0;
    return ((func_de->Eval(xd))*mult*frac_de);
    break;
  case 5:
    return ((l5xg_func->Eval(xd))*mult);
    break;
  default: 
    return ((l5xg_func->Eval(xd))*mult);
    break;
  }
}

//--------------------Function for creating TF1 for particle fractions -----//
void Sep_func(RooFFTConvPdf *l5xg, RooRealVar *t, RooRealVar *norm, RooRealVar *mu, RooRealVar *sg, RooRealVar *fProton, RooRealVar *fKaon, RooRealVar *fElectron, RooRealVar *fDeuteron, RooRealVar *total, RooRealVar *width, Int_t i )
{
    switch(i){
    case 0://Pion//
      if (func_pi) delete func_pi;
      func_pi = (TF1*)l5xg->asTF(RooArgList(*t), RooArgList(*norm,*mu,*sg,*fProton,*fKaon,*fElectron,*fDeuteron,*total,*width),*t ); 
      func_pi->FixParameter(3,0.);
      func_pi->FixParameter(4,0.);
      func_pi->FixParameter(5,0.);
      func_pi->FixParameter(6,0.);
      break;
    case 1://Proton//
      if (func_pr) delete func_pr;
      func_pr = (TF1*)l5xg->asTF(RooArgList(*t), RooArgList(*norm,*mu,*sg,*fProton,*fKaon,*fElectron,*fDeuteron,*total,*width),*t );
      frac_pr = TMath::Power(TMath::Sin(func_pr->GetParameter(i+2)),2);
      func_pr->FixParameter(4,0.);
      func_pr->FixParameter(5,0.);
      func_pr->FixParameter(6,0.);
      break;
    case 2: //Kaon//
      if (func_k) delete func_k;
      func_k = (TF1*)l5xg->asTF(RooArgList(*t), RooArgList(*norm,*mu,*sg,*fProton,*fKaon,*fElectron,*fDeuteron,*total,*width),*t );
      frac_k = TMath::Power(TMath::Sin(func_k->GetParameter(i+2)),2);
      func_k->FixParameter(3,0.);
      func_k->FixParameter(5,0.);
      func_k->FixParameter(6,0.);
      break;
    case 3: //Elektron//
      if (func_el) delete func_el;
      func_el = (TF1*)l5xg->asTF(RooArgList(*t), RooArgList(*norm,*mu,*sg,*fProton,*fKaon,*fElectron,*fDeuteron,*total,*width),*t );
      frac_el = TMath::Power(TMath::Sin(func_el->GetParameter(i+2)),2);
      func_el->FixParameter(3,0.);
      func_el->FixParameter(4,0.);
      func_el->FixParameter(6,0.);
      break;
    case 4: //Deuteron//
      if (func_de) delete func_de;
      func_de = (TF1*)l5xg->asTF(RooArgList(*t), RooArgList(*norm,*mu,*sg,*fProton,*fKaon,*fElectron,*fDeuteron,*total,*width),*t );
      frac_de = TMath::Power(TMath::Sin(func_de->GetParameter(i+2)),2);
      func_de->FixParameter(3,0.);
      func_de->FixParameter(4,0.);
      func_de->FixParameter(5,0.);
      break;
    default: break;
    }
}

//----------------------------------------------------------------------//

TF1 *FitRL5(TH1 *hist, Bool_t outer = kFALSE)
{
 if(!hist) return 0;
// cout<<"TEST (FUNKCJA): OUTER sector = "<<outer<<", "<<hist->GetName()<<endl;
 l5xg_func = 0; func_pi=0; func_pr=0; func_k=0; func_el=0;func_de=0; frac_pr=0.;frac_k=0.;frac_el=-0.;frac_de=-0.; frac_pi=0.;

 //-------------------------chose Inner or Outer sector----------------//
  Double_t sec_w=0.;
  if(outer) sec_w = 0.0699;//cout<<"!!!!!!!!!!!!WIDTH = "<<sec_w;}
  else sec_w = 0.0762;

  //-------------------------------Variables---------------------------//
  static RooRealVar *t = 0, *norm = 0, *mu = 0, *sigma = 0, *fProton = 0, *fKaon=0, *fElectron = 0, *fDeuteron = 0, *total = 0, *width = 0;
  static RooRealVar *mg = 0, *sg = 0;
  static RooLandauZ5 *landauZ5 = 0;
  static RooGaussian *gauss = 0;
  static RooFFTConvPdf *l5xg = 0;
  static TF1 *l5xg_mult = 0;
 // cout<<"kasowanie"<<endl;
  if (t) delete t;    
  t         = new RooRealVar("t"        ,"t"        ,-2.,5.) ;
                   t->setBins(1000,"cache");
  if (norm) delete norm;
  norm      = new RooRealVar("norm"     ,"norm"     ,0.) ;
  if (mu) delete mu;
  mu        = new RooRealVar("mu"       ,"mu"       ,0.,-1.,1.) ;
  if (sigma) delete sigma;
  sigma     = new RooRealVar("sigma"    ,"sigma"    ,0.) ;
  if (fProton) delete fProton;
  fProton   = new RooRealVar("fProton"  ,"fProton"  ,0.,0.,1.57) ;
  if (fKaon) delete fKaon;
  fKaon     = new RooRealVar("fKaon"    ,"fKaon"    ,0.,0.,1.57) ;
  if (fElectron) delete fElectron;
  fElectron = new RooRealVar("fElectron","fElectron",0.) ;
  if (fDeuteron) delete fDeuteron;
  fDeuteron = new RooRealVar("fDeuteron","fDeuteron",0.) ;
  if (total) delete total;
  total     = new RooRealVar("total"    ,"total"    ,0.,0.,10.);
  if (width) delete width;
  width     = new RooRealVar("width"    ,"width"    ,sec_w);//0.1,0.01,2.5) ;
  *width = sec_w;

  if (mg) delete mg;
  mg = new RooRealVar("mg","mg",0.) ;
  if (sg) delete sg;
  sg = new RooRealVar("sg","sg",0.25,0.01,10.) ;

  if (landauZ5) delete landauZ5;
  landauZ5= new RooLandauZ5("landauZ5","landauZ5",*t,*norm,*mu,*sigma,*fProton,*fKaon,*fElectron,*fDeuteron,*total,*width) ;
  if (gauss) delete gauss;
  gauss = new RooGaussian ("gauss","gauss",*t,*mg,*sg) ;
  if (l5xg) delete l5xg;
  l5xg = new RooFFTConvPdf("l5xg","landauZ5 (X) gauss",*t,*landauZ5,*gauss) ;
  //Import data
  //--------------------------------------------------------------
  RooDataHist data("data","data",*t,Import(*hist));

  //------- Fit to data -----------------------//
  l5xg->fitTo(data,Save());
  //----- Create TF1 -------------//
  if (l5xg_func) delete l5xg_func;
  l5xg_func = (TF1*)l5xg->asTF(RooArgList(*t), RooArgList(*norm,*mu,*sg,*fProton,*fKaon,*fElectron,*fDeuteron,*total,*width),*t );
  l5xg_func->SetParError(0,norm->getError());
  l5xg_func->SetParError(1,mu->getError());
  l5xg_func->SetParError(2,sg->getError());
  l5xg_func->SetParError(3,fProton->getError());
  l5xg_func->SetParError(4,fKaon->getError());
  l5xg_func->SetParError(5,fElectron->getError());
  l5xg_func->SetParError(6,fDeuteron->getError());
  l5xg_func->SetParError(7,total->getError());
  l5xg_func->SetParError(8,width->getError());

  //----- Scale TF1 fit function ------//
  Double_t mult_ev = hist->Integral()*hist->GetBinWidth(5);
  if (l5xg_mult) delete l5xg_mult;
  l5xg_mult = new TF1(Form("mult_%s",hist->GetName()),func_lz5xg_mult,-2.,5.,11);
  l5xg_mult->SetParent(hist);
  l5xg_mult->SetParName(0,"norm");  //l5xg_mult->SetParLimits(0,-80,80);
  l5xg_mult->SetParName(1,"mu");    //l5xg_mult->SetParLimits(1,-1.5,1.5);
  l5xg_mult->SetParName(2,"Sigma"); //l5xg_mult->SetParLimits(2,0.2,0.8);
  l5xg_mult->SetParName(3,"P"); 
  l5xg_mult->SetParName(4,"K");     //l5xg_mult->SetParLimits(4,0.0,0.5);
  l5xg_mult->SetParName(5,"e");     //l5xg_mult->SetParLimits(5,0.0,0.5);
  l5xg_mult->SetParName(6,"d");     //l5xg_mult->SetParLimits(6,0.0,0.5);
  l5xg_mult->SetParName(7,"Total");//l5xg_mult->SetParLimits(7,0.01,2.0);
  l5xg_mult->SetParName(8,"WidthL");
  l5xg_mult->SetParName(9,"case");  
  l5xg_mult->SetParName(10,"Mu");    //l5xg_mult->SetParLimits(1,-1.5,1.5);
  Double_t pars[11], errs[11];
  memset(pars, 0, sizeof(pars));
  memset(errs, 0, sizeof(errs));
  l5xg_func->GetParameters(pars);

  pars[7] = mult_ev; cout<<"MULT_EV = "<<mult_ev<<endl;
  pars[9] = 5;
  pars[10] = pars[1];
  l5xg_mult->SetParameters(pars);

  l5xg_mult->SetLineColor(1);
  //    l5xg_mult->SetLineStyle(2);
  memcpy(errs, l5xg_func->GetParErrors(), 8*sizeof(Double_t));
  errs[10] = errs[1];
  l5xg_mult->SetParErrors(errs);
  hist->GetListOfFunctions()->Add(l5xg_mult);
  l5xg_mult->SetParent(hist);
  //-- Fits for particles: 0.Pion, 1.Proton, 2.Kaon, 3.Elektron, 4.Deuteron --//
  for (Int_t i = 1; i <= 5; i++) {//<=5
    Int_t j = 0;
    if(i==5)j = 0;//i==5
    else j = i;
    //cout<<"(!!:TEST:!!) i = "<<i<<", j = "<<j<<endl;
    Sep_func(l5xg,t,norm,mu,sg,fProton,fKaon,fElectron,fDeuteron,total,width,j);
    TF1 *g0 = new TF1(Form("%s_%s",Peaks[j].Name,hist->GetName()),func_lz5xg_mult,-2.,5.,11);
    Double_t pars0[11], errs0[11];
    memset(pars0, 0, sizeof(pars0));
    memset(errs0, 0, sizeof(errs0));
    g0->GetParameters(pars0);
    g0->SetParameter(7,mult_ev);
    g0->SetParameter(9,j);
    if(i==1)frac_pi+=frac_pr; //cout<<"(!!:TEST:!!) PROTON : frac_pr = "<<frac_pr<<endl;}
    else if(i==2)frac_pi+=frac_k;// cout<<"(!!:TEST:!!) KAON : frac_k = "<<frac_k<<endl;}
    else if(i==3)frac_pi+=frac_el;// cout<<"(!!:TEST:!!) ELEKTRON : frac_el = "<<frac_el<<endl;}
    else if(i==4)frac_pi+=frac_de;// cout<<"(!!:TEST:!!) DEUTERON : frac_de = "<<frac_de<<endl;}
    else if(i==5){//5
      frac_pi=1.-frac_pi;
      //cout<<"(!!:TEST:!!) PION : frac_pi = "<<frac_pi<<endl;
      //cout<<"!!!!!!!!!!!!!!!!!!PEAK POSS = "<<func_pi->GetParameter(1)<<", max"<<func_pi->GetMaximumX()<<endl;
      pars[1] = func_pi->GetMaximumX();
      l5xg_mult->SetParameter(1,pars[1]);
    }
    g0->SetLineColor(j+2);
    g0->SetParent(hist);
    hist->GetListOfFunctions()->Add(g0);
  }
  Double_t X = l5xg_mult->GetParameter(1);
  Double_t Y = 0;
  //  static TPolyMarker *pm = 0;
  //  if (pm) delete pm;
  TPolyMarker *pm = new TPolyMarker(1, &X, &Y);
  hist->GetListOfFunctions()->Add(pm);
  pm->SetMarkerStyle(23);
  pm->SetMarkerColor(kRed);
  pm->SetMarkerSize(1.3);
  hist->Draw();

  return l5xg_mult;
}
//________________________________________________________________________________
TF1 *FitRL5(const Char_t *hName = "f1_1", Bool_t outer = kFALSE) {
  TH1 *hist = (TH1 *) gDirectory->Get(hName);
  if (! hist) return 0;
  return FitRL5(hist,outer);
}
//---------------------------------------------------------------------------//
//----------------------------LANDAU Z 5 END --------------------------------//
//---------------------------------------------------------------------------//

//----- Fit the line to plot width(row) from MC data -----------------------//
//----- Fit is used in FitRL5 as w width for Inner and Outer sector -------//
void pol_fit(TNtuple *FitP)
{
  //fit for MonteCarlo MIP pion function to find landau width
  TString command("a4:y>>hist(");
  command += 47;
  command += ",0,46)";
  FitP->Draw(command, "", "");
  TH1* hist = (TH1*) gDirectory->Get("hist");
  hist->SetDirectory(0);
  hist->GetXaxis()->SetTitle("t");
  hist->GetYaxis()->SetTitle("width");

  hist->Draw();
  
  TF1 *f1 = new TF1("f1","[0]",0.,13.);
  f1->SetParameter(0,0.076); //Inner: 0.0762
  f1->SetLineColor(2);

  TF1 *f2 = new TF1("f2","[0]",13.,50.);
  f2->SetParameter(0,0.07);//Outer: 0.0699
  f2->SetLineColor(2);

  hist->Fit("f1", "R");
  hist->Fit("f2", "R");
  f1->Draw("same");
  f2->Draw("same");  
}


//________________________________________________________________________________
TF1 *FitRL1lxg() {
  static TF1 *flxg = 0;
  if (flxg) return flxg;
  static RooFFTConvPdf *lxg = 0;
  static RooRealVar *t = 0, *ml = 0, *sl = 0, *mg = 0, *sg = 0;
  static RooLandauZ *landauz = 0;
  static RooGaussian *gauss = 0;
  if (! lxg) {
    // S e t u p   c o m p o n e n t   p d f s 
    // ---------------------------------------
    // Construct observable
    t = new RooRealVar("t","t",-2,6) ;
    // Construct landauz(t,ml,sl) ;
    ml = new RooRealVar("ml","log mean landauz",0.0,-20,20) ;
    sl = new RooRealVar("sl","sigma landauz",0.10,0.01,10) ;
    landauz = new RooLandauZ("lx","lx",*t,*ml,*sl) ;
    // Construct gauss(t,mg,sg)
    mg = new RooRealVar("mg","mg",0) ;
    sg = new RooRealVar("sg","sg",0.25,0.01,10) ;
    gauss = new RooGaussian ("gauss","gauss",*t,*mg,*sg) ;
    // C o n s t r u c t   c o n v o l u t i o n   p d f 
    // ---------------------------------------
    // Set #bins to be used for FFT sampling to 10000
    t->setBins(10000,"cache") ; 
    // Construct landauz (x) gauss
    lxg = new RooFFTConvPdf("lxg","landauZ (X) gauss",*t,*landauz,*gauss) ;
  }
  flxg = (TF1*)lxg->asTF(RooArgList(*t), RooArgList(*ml,*sl,*sg),*t );
  return flxg;
}
//________________________________________________________________________________
Double_t gfR5Func(Double_t *x, Double_t *par) {
  // par[0] - norm
  // par[1] - pion position wrt Z_pion (Bichsel prediction)
  // par[2] - sigma 
  // par[3] - proton signal
  // par[4] - Kaon    -"-
  // par[5] - electorn -"-
  // par[6] - deuteron -"-
  // par[7] - Total
  // par[8] - width of Landau
  Double_t sigma = par[2];
  Double_t frac[5];
  Int_t i;
  frac[0] = 1;
  for (i = 1; i < 5; i++) {
    frac[i] = TMath::Sin(par[2+i]);
    frac[i] *= frac[i];
    frac[0] -= frac[i];
  }
  if (frac[0] < 0.4) return 0;
  Double_t Value = 0;
  Int_t i1 = 0;
  Int_t i2 = 4;
  Int_t icase = (Int_t ) par[9];
  if (icase >= 0) {i1 = i2 = icase;}
  //                        MP,  WidthL,   SigmaG
  Double_t parLI[3] = { par[1],  par[8],    0.24};
  TF1 *lxg = FitRL1lxg();
  for (i = i1; i <= i2; i++) { 
    Double_t Sigma = TMath::Sqrt(sigma*sigma + Peaks[i].sigma*Peaks[i].sigma);
    parLI[0] = par[1] + Peaks[i].peak;
    parLI[1] = par[8];
    parLI[2] = Sigma;
    Value += frac[i]*lxg->EvalPar(x,parLI); 
    //    cout << "i\t" << i << "\tx = " << x[0] << " frac " << frac[i] << "\t" << Value << endl;
  }
  return par[7]*TMath::Exp(par[0])*Value;
}
//________________________________________________________________________________
TF1 *FitR5(TH1 *proj, Option_t *opt="", Int_t nhyps = 5) { // fit by 5 landau convoluted with gauss via RooFit
  // fit in momentum range p = 0.45 - 0.50 GeV/c
  TString Opt(opt);
  //  Bool_t quet = Opt.Contains("Q",TString::kIgnoreCase);
  TF1 *g2 = (TF1*) gROOT->GetFunction("R5");
  if (! g2) {
    g2 = new TF1("R5",gfR5Func, -5, 5, 10);
    g2->SetParName(0,"norm"); g2->SetParLimits(0,-80,80);
    g2->SetParName(1,"mu");     //g2->SetParLimits(1,-1.5,1.5);
    g2->SetParName(2,"Sigma");  g2->SetParLimits(2,0.2,0.8);
    g2->SetParName(3,"P"); 
    g2->SetParName(4,"K");      g2->SetParLimits(4,0.0,0.5);
    g2->SetParName(5,"e");      g2->SetParLimits(5,0.0,0.5);
    g2->SetParName(6,"d");      g2->SetParLimits(6,0.0,0.5);
    g2->SetParName(7,"Total");
    g2->SetParName(8,"WidthL"); g2->SetParLimits(8,0.01,2.0);
    g2->SetParName(9,"case");  
    //    g2->SetParName(7,"factor"); g2->SetParLimits(7,-.1,0.1);
  }
  
  Double_t total = proj->Integral()*proj->GetBinWidth(5);
  g2->SetParameters(0, proj->GetMean(), proj->GetRMS(), 0.0, 0.0, 0.0, 0.0,0.0,0.5,-1);
  g2->FixParameter(3,0);
  g2->FixParameter(4,0);
  g2->FixParameter(5,0);
  g2->FixParameter(6,0);
  g2->FixParameter(7,total);
  g2->FixParameter(9,-1);
  if (! proj) return g2;

  Int_t iok = proj->Fit(g2,Opt.Data());
  if (nhyps == 5) {
    g2->ReleaseParameter(3); g2->SetParLimits(3,0.0,TMath::Pi()/2);
    g2->ReleaseParameter(4); g2->SetParLimits(4,0.0,TMath::Pi()/2);
    g2->ReleaseParameter(5); g2->SetParLimits(5,0.0,TMath::Pi()/2);
    g2->ReleaseParameter(6); g2->SetParLimits(6,0.0,TMath::Pi()/2);
    iok = proj->Fit(g2,Opt.Data());
  }
  if ( iok < 0) {
    cout << g2->GetName() << " fit has failed with " << iok << " for " 
	 << proj->GetName() << "/" << proj->GetTitle() << " Try one again" << endl; 
    proj->Fit(g2,Opt.Data());
  }
  Opt += "m";
  iok = proj->Fit(g2,Opt.Data());
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
    if (nhyps == 5) {
      for (int i = 0; i < nhyps; i++) {
	TF1 *f = new TF1(*g2);
	f->SetName(Form("L5%s",Peaks[i].Name));
	f->FixParameter(9,i);
	f->SetLineColor(i+2);
	proj->GetListOfFunctions()->Add(f);
      }
      proj->Draw();
    }
  }
  return g2;
}

//________________________________________________________________________________
//RooFitResult *FitRL1(TH1 *hist) {
TF1 *FitRL1(TH1 *hist) {
  if (! hist) return 0;
  // S e t u p   c o m p o n e n t   p d f s 
  // ---------------------------------------
  // Construct observable
  RooRealVar t("t","t",-2,6) ;
  // Construct landauz(t,ml,sl) ;
  RooRealVar ml("ml","log mean landauz",0.0,-20,20) ;
  RooRealVar sl("sl","sigma landauz",0.10,0.01,10) ;
  RooLandauZ landauz("lx","lx",t,ml,sl) ;
  // Construct gauss(t,mg,sg)
  RooRealVar mg("mg","mg",0) ;
  RooRealVar sg("sg","sg",0.25,0.01,10) ;
  RooGaussian gauss("gauss","gauss",t,mg,sg) ;
  // C o n s t r u c t   c o n v o l u t i o n   p d f 
  // ---------------------------------------
  // Set #bins to be used for FFT sampling to 10000
  t.setBins(10000,"cache") ; 
  // Construct landauz (x) gauss
  RooFFTConvPdf lxg("lxg","landauZ (X) gauss",t,landauz,gauss) ;
  // S a m p l e ,   f i t   a n d   p l o t   c o n v o l u t e d   p d f 
  RooDataHist* data = new RooDataHist("data","data",t,Import(*hist));
  // Fit gxlx to data
  //RooFitResult* r = 
  lxg.fitTo(*data,Save()) ;
  // Plot data, landauz pdf, landauz (X) gauss pdf
  RooPlot* frame = t.frame(Title("landauz (x) gauss convolution")) ;
  data->plotOn(frame) ;
  lxg.plotOn(frame) ;
  //  landauz.plotOn(frame,LineStyle(kDashed)) ;
  // Draw frame on canvas
  TCanvas *ca = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("FitRL1");
  if (! ca) ca = new TCanvas("FitRL1","FitRL1",600,600) ;
  else      ca->Clear();
  //  gPad->SetLeftMargin(0.15) ; frame->GetYaxis()->SetTitleOffset(1.4) ; 
  frame->Draw() ;
  delete data;
  return 0;//r;
}
//________________________________________________________________________________
//RooFitResult *FitRL1(const Char_t *hName = "f1_1") {
TF1 *FitRL1(const Char_t *hName = "f1_1") {
  TH1 *hist = (TH1 *) gDirectory->Get(hName);
  if (! hist) return 0;
  return FitRL1(hist);
}
