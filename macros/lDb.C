class StBFChain;        
class StMessMgr;
#if defined(__CLING__)
#pragma cling load("StarRoot")
#pragma cling load("St_base")
#pragma cling load("StChain")
#pragma cling load("libStDbLib")
#pragma cling load("StUtilities")
#pragma cling load("StBFChain")
#pragma cling load("geant3")
#pragma cling load("libmysqlclient")
#endif /* __CLING__ */

#if defined(__CINT__)
StBFChain* chain = 0;
#endif
#ifdef __CLING__
StBFChain * bfc(Int_t First, Int_t Last,const Char_t *Chain = "", // + ",Display",
	 const Char_t *infile=0, const Char_t *outfile=0, const Char_t *TreeFile=0, const Char_t *chainName=0);
StBFChain *bfc(Int_t First, const Char_t *Chain = "MC2016,20Muons,vmc,Rung.1",
 	       const Char_t *infile=0, const Char_t *outfile=0, const Char_t *TreeFile=0, const Char_t *chainName = "");
#endif
void lDb(Int_t Last = -1, const Char_t *date = "r2024,TFGdbOpt,CorrZ") {
  TString Chain("mysql,tpcDb,detDb,StBichsel,magF,ExB,LaserIT,nodefault");
  //  TString Chain("mysql,tpcDb,detDb,magF,TpcHitMover,CorrY,LaserIT,nodefault");
  // TString Chain("mysql,tpcDb,detDb,magF,ExB,LaserIT,nodefault");
  if (date) {Chain += ",simu,"; Chain += date;}
#if !defined(__CLING__)
  gROOT->LoadMacro("bfc.C");
  bfc(-1,Chain.Data());
  if (Last < 0) return;
  StMaker *dbMk = chain->Maker("db");
  if (! dbMk) return;
  chain->Init();
  if (Last == 0) return;
  chain->Make();
#else
  StBFChain* chain = new StBFChain;
  cout << "Create chain " << chain->GetName() << endl;
  chain->cd();
  chain->SetDebug(1);
  if (Last < -3) return;
  chain->SetFlags(Chain);
  if (Last < 0) return;
  chain->Init();
  if (Last <= 0) return;
  chain->Make();
#endif
}
