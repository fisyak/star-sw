//   /hlt/cephfs/reco/DEV2WE3/2019/RF/14p5GeV $  zgrep laserDriftVelocityWest */*/*.gz | sed -e 's#/#:#g' | awk -F: '{print $2" "$4}' | awk '{print $1" "$4}' | tee DV.list;
//   root.exe MakeDVNTupleFromLog.C

struct BPoint_t {
  Float_t run, DV;
};
BPoint_t BPoint;
void MakeDVNTupleFromLog(Char_t *FileName="DV.list") {
  FILE *fp = fopen(FileName,"r");
  if (! fp) {
    cout << "Can't open" << FileName << endl;
    return;
  }
  TString fName(gSystem->BaseName(FileName));
  //  fName.ReplaceAll(".data",".root");
  fName.ReplaceAll(".list",".root");
  f = new TFile(fName.Data(),"RECREATE");
  FitP = new TNtuple("FitP","DV versus run","run:DV");//:D_l:D_p:D_u:w:a:b:c");
  char line[121];
  Float_t run, DV;
  while (fgets(&line[0],120,fp)) {
    if (line[0] == '#') continue;
    Int_t n = sscanf(&line[0],"%f %f",&run,&DV);
    //    printf("%i %s",n,line);
    //    printf("%2d/%2d/%4d %2d:%2d:%f %f\n",mon,d,y,h,m,s,freq);
    BPoint.run = run;
    BPoint.DV = DV;
    FitP->Fill(&BPoint.run);
    //    if (i > 10) break;
    //    if (i%10 == 1) cout << "i:" << i << "\t" << line;
  }
  fclose(fp);
  f->Write();
}
