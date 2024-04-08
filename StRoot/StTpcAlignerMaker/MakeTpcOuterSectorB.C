/*  check TFGflag in LDb.C  
  root.exe 'lDb.C(0)' MakeTpcOuterSectorB.C+

root.exe Results.C+
root.exe Results.root DumpRes2Par.C
Results.h to IOSectorPar.h

*/
//#define __TpcInnerSector__ 
#if !defined(__CINT__) || defined(__MAKECINT__)
#include <stdio.h>
#include <string.h>
#include "Riostream.h"
#include "TString.h"
#include "TMath.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TH1.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TNamed.h"
#include "THStack.h"
#include "StChain.h"
#include "tables/St_Survey_Table.h"
#include "TGeoMatrix.h"
#include "StTpcDb/StTpcDb.h"
#include "StEvent/StEnumerations.h"
#include "StDetectorDbMaker/StTpcSurveyC.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#endif
//#include "StTpcAlignerMaker/IOSectorPar.h"
#include "StTpcAlignerMaker/SurveyPass.h"
const Int_t N = 24;
SurveyPass_t Passes[] = {
  //#include "IOSectorParPass30_Avg.h"
  //#include "IOSectorParPass31_Avg.h"
  //#include "IOSectorParPass32_Avg.h"
  //#include "IOSectorParPass33_Avg.h"
  //#include "IOSectorParPass34_Avg.h"
  //#include "IOSectorParPass36_Avg.h"
  //#include "IOSectorParPass37_Avg.h"
  //#include "IOSectorParPass40_Avg.h"
  //#include "IOSectorParPass41_Avg.h"
  //#include "IOSectorParPass42_Avg.h"
  //#include "IOSectorParPass46_Avg.h" // Global Transort use __No_alpha_beta__
  //#include "IOSectorParPass47_Avg.h" // Global Transort use __No_alpha_beta__, scale = 0.5
  //#include "IOSectorParPass48_Avg.h" // Global Transort use __No_alpha_beta__, scale = 0.5
  //#include "IOSectorParPass49_Avg.h" // Global Transort use __No_alpha_beta__, scale = 1.0
  //#include "IOSectorParPass50_Avg.h" // Global Transort use __No_alpha_beta__, scale = 1.0
  //#include "IOSectorParPass51_Avg.h" // Global Transort use __No_alpha_beta__, scale = 1.0
  //#include "IOSectorParPass87_Avg.h" // Global Transort use __No_alpha_beta__, scale = 1.0
  //#include "IOSectorParPass88_Avg.h" // Global Transort use __No_alpha_beta__, scale = 1.0
  //#include "IOSectorParPass92_Avg.h" // Global Transort use __No_alpha_beta_gamma__, scale = 1.0
  //#include "IOSectorParPass96_Avg.h" // Global Transort use __No_alpha_beta_gamma__, scale = 1.0
  //#include "IOSectorParPass97_Avg.h" // Global Transort use __No_alpha_beta__, scale = 1.0
  //#include "IOSectorParPass98_Avg.h" // Global Transort use __No_alpha_beta__, scale = 1.0
  //#include "IOSectorParPass99_Avg.h" // Global Transort use __No_alpha_beta__, scale = 1.0, Fit on Gating Grid
#include "IOSectorParPass100_Avg.h" // Global Transort use __No_alpha_beta__, scale = 1.0, Fit on Gating Grid
};
#define __No_alpha_beta__
const  Int_t NP = sizeof(Passes)/sizeof(SurveyPass_t);
class St_db_Maker;
class TTable;
StChain *chain = 0;
St_db_Maker *dbMk = 0;
TTable *table = 0;
static Int_t _debug = 1;
//________________________________________________________________________________
void MakeTpcOuterSectorB(const Char_t *opt = 0){
  cout << "NP = " << NP << endl;
  SurveyPass_t Pass[2];// 0 => half sum, 1 => half diff
  Int_t kPass = NP - 1;
  Int_t NR = 0; // NR = 0 no match, NR = 1 only one set, NR = 2 two sets : half sum and half difference
  TString CS, CD;
  if (opt) {
    kPass = -1;
    for (Int_t k = 0; k < NP; k++) {
      TString Name(Passes[k].PassName);
      if (! Name.Contains(opt,TString::kIgnoreCase)) continue;
      kPass = k; 
      Pass[0] = Passes[k];
      NR = 1;
      break;
    }
    if (kPass < 0) {
      cout << "Pass for " << opt << " has not been found" << endl;
      return;
    }
  } else { //default average for two last passes
    if (NP != 2) return;
    Passes[0].Print();
    Passes[1].Print();
    Pass[0] = Passes[0];
    Pass[1] = Passes[0];
    Pass[0] += Passes[1];
    Pass[1] -= Passes[1];
    NR = 2;
  }
  cout << "Pass for " << kPass << " has been found" << endl;
  if (! NR) return;
  Pass[0].Print();
  Pass[1].Print();
#if 0
  gROOT->LoadMacro("bfc.C");
  bfc(0,"mysql,tpcDb,corrX,nodefault");
#else
  chain = (StChain *) StChain::GetChain();
#endif
  StMaker *dbMk = chain->Maker("db");
  if (! dbMk) return;
  dbMk->SetDebug(1);
  StEvtHddr *header = chain->GetEvtHddr();
  header->SetRunNumber(1);
  dbMk->SetDateTime(Pass[0].date,Pass[0].time); 
  header->SetDateTime(Pass[0].date,Pass[0].time);
  chain->MakeEvent();
  dbMk->SetDebug(2);
  dbMk->SetDateTime(Pass[0].date,Pass[0].time); 
  // Outer sector in Inner sector coordinate system
#ifndef  __TpcInnerSector__ 
  St_SurveyC                 *TpcSectorPositionBOld = StTpcOuterSectorPosition::instance();
#else /* __TpcInnerSector__ */
  St_SurveyC                 *TpcSectorPositionBOld = StTpcInnerSectorPosition::instance();
#endif /* !  __TpcInnerSector__ */
  if (! (TpcSectorPositionBOld)) return;
  Int_t NoldRows = TpcSectorPositionBOld->GetNRows();
  Int_t NoSectors = 24;
#ifndef  __TpcInnerSector__ 
  St_Survey      *TpcSectorPositionB = new St_Survey("TpcOuterSectorPositionB",NR*NoSectors);
#else /* __TpcInnerSector__ */
  St_Survey      *TpcSectorPositionB = new St_Survey("TpcInnerSectorPositionB",NR*NoSectors);
#endif /* !  __TpcInnerSector__ */
#if 0
  TGeoHMatrix Flip  = StTpcDb::instance()->Flip(); if (_debug) {cout << "Flip\t"; Flip.Print();}
  TGeoHMatrix FlipI = Flip.Inverse();              if (_debug) {cout << "FlipI\t"; FlipI.Print();}
#endif
  for (Int_t r = 0; r < NR; r++) { // half sum & half diff
    for (Int_t s = 0; s < NoSectors; s++) {
      TGeoHMatrix LSold, LS, dR;
      if (r == 0 ) {
	LSold = TpcSectorPositionBOld->GetMatrix(s);   
      } else {
	if (NoldRows > 24) LSold = TpcSectorPositionBOld->GetMatrix(s+24); 
      }
      if (_debug) {cout << "===================== Sector \t" << s+1 << endl; cout << "\tLSold\t"; LSold.Print();}
      Int_t i = -1; 
      for (Int_t k = 0; k < N; k++) {
	if (TpcSectorPositionBOld->Id(s) ==Pass[r].Data[k].sector) {i = k; break;}
      }
      if (i < 0) {
	cout << "Correction for " << TpcSectorPositionBOld->Id(s) << " is not found" << endl;
      } else {
	cout << "Sector " << TpcSectorPositionBOld->Id(s) << "\ti " << i 
	     << "\talpha " << Pass[r].Data[i].alpha << "+/-" <<Pass[r].Data[i].Dalpha
	     << "\tbeta "  << Pass[r].Data[i].beta  << "+/-" <<Pass[r].Data[i].Dbeta
	     << "\tgamma " << Pass[r].Data[i].gamma << "+/-" <<Pass[r].Data[i].Dgamma
	     << "\tx " << Pass[r].Data[i].x << "+/-" <<Pass[r].Data[i].Dx
	     << "\ty " << Pass[r].Data[i].y << "+/-" <<Pass[r].Data[i].Dy
	     << "\tz " << Pass[r].Data[i].z << "+/-" <<Pass[r].Data[i].Dz << endl;
	Double_t xyz[3] = {0, 0, 0};
	//	Double_t scale = 0.5;
	Double_t scale = 1.0;
#if 1 /* alpha, beta gamma rotations */
#ifndef __No_alpha_beta__
	if (Pass[r].Data[i].Dalpha >= 0) dR.RotateX(scale*TMath::RadToDeg()*Pass[r].Data[i].alpha*1e-3);
	if (Pass[r].Data[i].Dbeta  >= 0) dR.RotateY(scale*TMath::RadToDeg()*Pass[r].Data[i].beta *1e-3);
#endif /* _No__alpha_beta__ */
	if (Pass[r].Data[i].Dgamma >= 0) dR.RotateZ(scale*TMath::RadToDeg()*Pass[r].Data[i].gamma*1e-3);
#endif /* no alpha, beta gamma rotation */
	if (Pass[r].Data[i].Dx >= 0) xyz[0] =  scale*1e-4*Pass[r].Data[i].x;
	if (Pass[r].Data[i].Dy >= 0) xyz[1] =  scale*1e-4*Pass[r].Data[i].y;
	if (Pass[r].Data[i].Dz >= 0) xyz[2] =  scale*1e-4*Pass[r].Data[i].z;
	dR.SetTranslation(xyz);          if (_debug) {	cout << "dR\t"; dR.Print();}
      }
      // Fit on Gating gGrid:  dR' * WHEEL =  WHEEL * dR";  dR" = WHEEL^-1 * dR'* WHEEL 
      enum StBeamDirection {east   = 0,
			    yellow = 0,    // yellow beam is going west -> east
			    west   = 1,
			    blue   = 1};   // blue beam is going east -> west
      StBeamDirection   part = east;
      Int_t sector = s + 1;
      if (sector <= 12) part = west;
      TGeoHMatrix Wheel = StTpcDb::instance()->Wheel(part);
      TGeoHMatrix WheelI = Wheel.Inverse();
      TGeoHMatrix rotA = WheelI * dR * Wheel;
      dR = rotA; if (_debug) {	cout << "Moved to GG dR\t"; dR.Print();}
      
#if 0
      // Flip has been accounted in StTpcAlignerMaker
      //new:  global = Tpc2GlobalMatrix() * SupS2Tpc(sector) * StTpcSuperSectorPosition(sector) * Flip() * {StTpcInnerSectorPosition(sector)} | StTpcOuterSectorPosition(sector)}
      //      TGeoHMatrix dR1 = FlipI * dR * Flip; cout << "F^-1 dR F\t"; dR1.Print();
      //      TGeoHMatrix dRT = FlipI * dRI * Flip; cout << "F^-1 dR^-1 F\t"; dRT.Print();
      //      TGeoHMatrix dRT = FlipI * dR * Flip; cout << "F^-1 dR F\t"; dRT.Print();
      //      TGeoHMatrix dRI = dR1.Inverse(); cout << "dR^-1\t"; dRI.Print();
#endif
#ifndef __TpcInnerSector__
      LS = dR * LSold; if (_debug) {cout << "LS_new\t"; LS.Print();}
#else /* __TpcInnerSector__ */
      //      TGeoHMatrix LSoldI = LSold.Inverse();
      //      LS = LSoldI * dRI; cout << "LS_new\t"; LS.Print();
      TGeoHMatrix dRI = dR.Inverse(); if (_debug) {cout << "dR^-1\t"; dRI.Print();}
      LS = dRI * LSold; if (_debug) {cout << "LS_new\t"; LS.Print();}
#endif /* !  __TpcInnerSector__ */
      Survey_st row; memset (&row, 0, sizeof(Survey_st));
      Double_t *rx = LS.GetRotationMatrix();
      memcpy(&row.r00, rx, 9*sizeof(Double_t));
      row.sigmaRotX =Pass[r].Data[i].Dalpha;
      row.sigmaRotY =Pass[r].Data[i].Dbeta;
      row.sigmaRotZ =Pass[r].Data[i].Dgamma;
      row.sigmaTrX  =Pass[r].Data[i].Dx;
      row.sigmaTrY  =Pass[r].Data[i].Dy;
      row.sigmaTrZ  =Pass[r].Data[i].Dz;
      row.Id = TpcSectorPositionBOld->Id(s);
      Double_t *t = LS.GetTranslation();
      memcpy(&row.t0, t, 3*sizeof(Double_t));
      TpcSectorPositionB->AddAt(&row);
    }
  }
  TpcSectorPositionB->Print(0,48);
  TString fOut =  Form("%s.%8i.%06i.C",TpcSectorPositionB->GetName(),Pass[0].date,Pass[0].time);
  ofstream out;
  cout << "Create " << fOut << endl;
  out.open(fOut.Data());
  out << "#ifndef __CINT__" << endl;
  out << "#include \"tables/St_Survey_Table.h\"" << endl;
  out << "#endif" << endl;

  out << "TDataSet *CreateTable() {" << endl;
  out << "  if (!gROOT->GetClass(\"St_Survey\")) return 0;" << endl;
  out << "  Survey_st row[" << NR*NoSectors << "] = {" << endl; 
  out << "    //               -gamma      beta     gamma              -alpha     -beta     alpha                 x0       y0       z0" << endl;
  Survey_st *SectorPositionBs = TpcSectorPositionB->GetTable(); 
  for (Int_t r = 0; r < NR; r++) {
    for (Int_t i = 0; i < NoSectors; i++, SectorPositionBs++) { 
      out << "    {" << Form("%2i",TpcSectorPositionBOld->Id(i)); 
      Double_t *rx = &(SectorPositionBs->r00);
      for (Int_t j =  0; j <  9; j++) out << Form(",%9.6f",rx[j]);
      for (Int_t j =  9; j < 12; j++) out << Form(",%8.4f",rx[j]);
      for (Int_t j = 12; j < 18; j++) out << Form(",%5.2f",TMath::Min(99.99,rx[j]));
      out << ",\"" <<Pass[r].PassName << "\"}";
      if (24*r + i != NR*NoSectors - 1) out << ",";
      out << endl;
    } 
  }
  out << "  };" << endl;
  out << "  St_Survey *tableSet = new St_Survey(\"" << TpcSectorPositionB->GetName() << "\"," << NR*NoSectors << ");" << endl; 
  out << "  for (Int_t i = 0; i < " << NR*NoSectors << "; i++) tableSet->AddAt(&row[i].Id, i);" << endl; 
  out << "  return (TDataSet *)tableSet;" << endl;
  out << "}" << endl;
  out.close(); 
}

