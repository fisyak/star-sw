#ifdef __CLING__
class StBFChain;        

StBFChain * bfc(Int_t First, Int_t Last,const Char_t *Chain = "", // + ",Display",
	 const Char_t *infile=0, const Char_t *outfile=0, const Char_t *TreeFile=0, const Char_t *chainName=0);
StBFChain *bfc(Int_t First, const Char_t *Chain = "MC2016,20Muons,vmc,Rung.1",
 	       const Char_t *infile=0, const Char_t *outfile=0, const Char_t *TreeFile=0, const Char_t *chainName = "");
#endif
void lDb(Int_t N = -1, const Char_t *date = 0, Bool_t TFGflag = kTRUE) {
#ifdef __CLING__ 
  gSystem->Load("St_base");
  gSystem->Load("libmysqlclient");
  gSystem->Load("StStarLogger");
  gSystem->Load("StChain");
  gSystem->Load("StBFChain");
  gROOT->LoadMacro("bfc.C");
#else
  gROOT->LoadMacro("bfc.C");
#endif
  //  TString Chain("mysql,tpcDb,detDb,magF,TpcHitMover,CorrY,LaserIT,nodefault");
  TString Chain("mysql,tpcDb,detDb,magF,CorrY,LaserIT,nodefault");
  if (date) {Chain += ",simu,"; Chain += date;}
  bfc(-1,Chain.Data());
  StMaker *dbMk = chain->Maker("db");
  if (! dbMk) return;
  if (TFGflag) {
    dbMk->SetDebug(1);
    cout << "use TFG DB flavor" << endl;
    dbMk->SetFlavor("TFG","tpcSectorT0offset"); // disable MySQL 
    dbMk->SetFlavor("TFG","TpcPosition"); // disable MySQL 
    dbMk->SetFlavor("TFG","TpcHalfPosition"); // disable MySQL 
    dbMk->SetFlavor("TFG","TpcSuperSectorPositionB"); // disable MySQL 
    dbMk->SetFlavor("TFG","TpcInnerSectorPositionB"); // disable MySQL 
    dbMk->SetFlavor("TFG","TpcOuterSectorPositionB"); // disable MySQL 
  }
  if (N < 0) return;
  chain->Init();
  if (N == 0) return;
#if 0
  TString Tag(date);
  Int_t D = 0, T = 0;
  if (Tag != "") {
    D = StMaker::AliasDate(Tag);
    T = StMaker::AliasTime(Tag);
  } else {
    TDatime dt;
    Int_t i = dt.Convert(kTRUE); // to GMT
    dt.Set(i);
    D = dt.GetDate();
    T = dt.GetTime();
  }
  cout << "date " << D << " time " << T << endl;
  dbMk->SetDateTime(D,T); 
#endif
  chain->Make();
}
