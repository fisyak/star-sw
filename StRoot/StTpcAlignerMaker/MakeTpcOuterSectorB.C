/*  check TFGflag in LDb.C  
  root.exe 'lDb.C(0)' MakeTpcOuterSectorB.C+

root.exe Results.C+
root.exe Results.root DumpRes2Par.C
Results.h to IOSectorPar.h

*/
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
  //#include "IOSectorPar2019_2020_2021Pass121_Avg.h"
  //#include "IOSectorPar2022Pass121_Avg.h"
  //#include "IOSectorPar2023_2024Pass121_Avg.h"
  //#include "IOSectorPar2019_2020_2021Pass123_Avg.h"
  //#include "IOSectorPar2022Pass123_Avg.h"
  //#include "IOSectorPar2023_2024Pass123_Avg.h"
  //#include "IO_2019_2020Pass129_Avg.h"
  //#include "IO_2021Pass129_Avg.h"
  //#include "IO_2022Pass129_Avg.h"
  //#include "IO_2023Pass129_Avg.h"
#include "IO_2024Pass129_Avg.h"
};
//#define __ResetdZto0__
//#define __No__gamma__
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
  for (Int_t k = 0; k < NP; k++) {
    Passes[k].FixErrors();
  }
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
    Pass[0] = Passes[0]; Pass[0].Print();
    Pass[1] = Passes[0]; Pass[1].Print();
    Pass[0].Add2(Passes[1]); Pass[0].Print();
    Pass[1].Sub2(Passes[1]); Pass[1].Print();
    NR = 2;
  }
  cout << "Pass for " << kPass << " has been found" << endl;
  if (! NR) return;
  Pass[0].Print();
  Pass[1].Print();
  chain = (StChain *) StChain::GetChain();
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
  St_SurveyC                 *TpcSectorPositionBOld = StTpcOuterSectorPosition::instance();
  if (! (TpcSectorPositionBOld)) return;
  Int_t NoldRows = TpcSectorPositionBOld->GetNRows();
  Int_t NoSectors = 24;
  St_Survey      *TpcSectorPositionB = new St_Survey("TpcOuterSectorPositionB",NR*NoSectors);
  for (Int_t r = 0; r < NR; r++) { // half sum & half diff
    for (Int_t s = 0; s < NoSectors; s++) {
      TGeoHMatrix LSold, LS, dR;
      LSold = TpcSectorPositionBOld->GetMatrix(24*r+s);   
      if (_debug) {cout << "===================== Sector \t" << s+1 << endl; cout << "\tLSold\t"; LSold.Print();}
      Int_t i = -1; 
      for (Int_t k = 0; k < N; k++) {
	if (TpcSectorPositionBOld->Id(24*r+s) == Pass[r].Data[k].sector) {i = k; break;}
      }
      if (i < 0) {
	cout << "Correction for " << TpcSectorPositionBOld->Id(24*r+s) << " is not found" << endl;
      } else {
	cout << "Sector " << TpcSectorPositionBOld->Id(24*r+s) << "\ti " << i 
	     << "\talpha " << Pass[r].Data[i].alpha << "+/-" <<Pass[r].Data[i].Dalpha
	     << "\tbeta "  << Pass[r].Data[i].beta  << "+/-" <<Pass[r].Data[i].Dbeta
	     << "\tgamma " << Pass[r].Data[i].gamma << "+/-" <<Pass[r].Data[i].Dgamma
	     << "\tx " << Pass[r].Data[i].x << "+/-" <<Pass[r].Data[i].Dx
	     << "\ty " << Pass[r].Data[i].y << "+/-" <<Pass[r].Data[i].Dy
	     << "\tz " << Pass[r].Data[i].z << "+/-" <<Pass[r].Data[i].Dz << endl;
	Double_t xyz[3] = {0, 0, 0};
	//	Double_t scale = 0.5;
	Double_t scale = 1.0;
#ifndef __No__gamma__ /* alpha, beta gamma rotations */
	if (Pass[r].Data[i].Dgamma >= 0) dR.RotateZ(scale*TMath::RadToDeg()*Pass[r].Data[i].gamma*1e-3);
#endif /* no alpha, beta gamma rotation */
	if (Pass[r].Data[i].Dx >= 0) xyz[0] =  scale*1e-4*Pass[r].Data[i].x;
	if (Pass[r].Data[i].Dy >= 0) xyz[1] =  scale*1e-4*Pass[r].Data[i].y;
	if (Pass[r].Data[i].Dz >= 0) xyz[2] =  scale*1e-4*Pass[r].Data[i].z;
	dR.SetTranslation(xyz);          if (_debug) {	cout << "dR\t"; dR.Print();}
      }

      LS = dR * LSold; if (_debug) {cout << "LS_new\t"; LS.Print();}
      Survey_st row; memset (&row, 0, sizeof(Survey_st));
      Double_t *rx = LS.GetRotationMatrix();
      memcpy(&row.r00, rx, 9*sizeof(Double_t));
      row.sigmaRotX = Pass[r].Data[i].Dalpha;
      row.sigmaRotY = Pass[r].Data[i].Dbeta;
      row.sigmaRotZ = Pass[r].Data[i].Dgamma;
      row.sigmaTrX  = Pass[r].Data[i].Dx;
      row.sigmaTrY  = Pass[r].Data[i].Dy;
      row.sigmaTrZ  = Pass[r].Data[i].Dz;
      row.Id        = TpcSectorPositionBOld->Id(24*r+s);
      Double_t *t   = LS.GetTranslation();
      memcpy(&row.t0, t, 3*sizeof(Double_t));
      //      strcpy(&row.comment,Pass[r].Data[i].Comment);
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
#ifndef __ResetdZto0__
      for (Int_t j =  9; j < 12; j++) out << Form(",%8.4f",rx[j]);
#else
      for (Int_t j =  9; j < 11; j++) out << Form(",%8.4f",rx[j]);
      static Double_t zero = 0;
      out << Form(",%8.4f",zero);
#endif
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

