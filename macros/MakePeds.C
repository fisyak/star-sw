/*
[rcas6005] ~/work/daq $ rts_example -Ditpc st_pedestal_adc_24151013_raw_0000003.daq | mor
...
ITPC ADC 423: sector  1, row  8, pad  26: 421 timebins
        tb   0 =   76 ADC
        tb   1 =   76 ADC
...
[rcas6005] ~/work/daq $ rts_example -Dtpx st_pedestal_adc_24151013_raw_0000003.daq | more
...
TPX: sec 01, row 18, pad 105: 435 pixels
1 18 105 434 64
1 18 105 433 63
...
 rts_example -Dtpx st_pedestal_11003025_raw_1080001.daq > Ped.txt 
 root.exe
 gSystem->Load("libStDb_Tables.so");
 .x MaketpcPeds.C
*/
#if !defined(__CINT__)
// code that should be seen ONLY by the compiler
#else
#if !defined(__CINT__) || defined(__MAKECINT__)
// code that should be seen by the compiler AND rootcint
#else
// code that should always be seen
#endif
#endif

#include <stdio.h>
#if !defined(__CINT__)
#include "tables/St_tpcPedestal_Table.h"
#endif
#include "TFile.h"
#include "Riostream.h"
using namespace std;
//________________________________________________________________________________
void MakeTpcPeds() {
  St_tpcPedestal *tpcPed = new St_tpcPedestal("tpcPedestal",24);
  tpcPedestal_st Ped;
  memset(&Ped, 0, sizeof(tpcPedestal_st));
  for (Int_t sec = 1; sec <=24; sec++) tpcPed->AddAt(&Ped);
  tpcPedestal_st *sped = tpcPed->GetTable();
  Char_t line[121];
  Int_t row, pad, tmbk;
  Float_t ped, rms;
  Int_t i = 0;
  Int_t rowOld = -1;
  TString FileName("Ped.txt");
  tpcPedestal_st *cped = 0;
  while (fgets(&line[0],120,fp)) {
    if (line[0] == '*') continue;
    if (line[0] == 'T') {
      sscanf(&line[0],"TPX: sec %d, row %d, pad %d",&sec,&row,&pad);
      printf("%s",line);
      sec = sec;
      row = row;
      pad = pad;
      cped = sped + sec - 1;
      continue;
    }
    if (! row) continue;
    Int_t n = sscanf(&line[0],"  tb %i: ped %f, rms %f",&tb,&ped,&rms);
    if (n != 3) continue;
    cped->Pedestal[row-1][pad-1][tb] = ped;
  }
  fclose(fp);
  TFile *fOut = new TFile("tpcPedestal.20130215.162616.root","recreate");
  tpcPed->Write();
  delete fOut;
}
