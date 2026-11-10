class StFttDb;


// readTime picks WHICH entry comes back: the DB returns the row with the latest
// beginTime at or before it. The default is the end of Run 22; pass another
// timestamp to read what a later run saw, in MySQL format "YYYY-MM-DD HH:mm:ss".
void readFttDataWindows( TString readTime = "2022-12-31 23:59:59" ){

    //-- load dBase and Table definition libraries
  gSystem->Load("St_base");
  gSystem->Load("StChain");
  gSystem->Load("StUtilities");
  gSystem->Load("St_Tables.so");

  gSystem->Load("StDbLib.so");
  gSystem->Load("libStDb_Tables.so");

  //-- get the singleton manager
  StDbManager* dbManager = StDbManager::Instance();

  //-- connect to the db & get an empty container
  StDbConfigNode* configNode = dbManager->initConfig("Calibrations_ftt");
  printf( "READ-TIME: %s\n", readTime.Data() );
  dbManager->setRequestTime(readTime.Data());

  StDbTable* dataset = configNode->addDbTable("fttDataWindowsB");
  dbManager->fetchDbTable(dataset);

  Int_t rows = dataset->GetNRows();
  printf( "rows = %d\n", rows);

  // Get pointer to the raw table data
  auto table = dataset->GetTable();
  printf("table = %p\n", table);

  // Access as fttDataWindowsB_st pointer
  fttDataWindowsB_st *st = reinterpret_cast<fttDataWindowsB_st*>(table);

  cout << setw(6) << "UUID"
       << setw(6) << "Mode"
       << setw(8) << "Anchor"
       << setw(8) << "Min"
       << setw(8) << "Max"
       << endl;
  cout << "==============================================" << endl;
  // The whole array, not the first 384: uuid runs 0-383 for the VMMs (StFttDb
  // keys it from 0-based plane/quadrant/feb/vmm) and slot 384 carries the run
  // stamp as uuid = -1, which is what gates the windows. Stopping at 384 hides it.
  // 385 is the declared length in StDb/idl/fttDataWindowsB.idl; CINT cannot take
  // sizeof() through the cast pointer, so it is spelled out.
  for (int i = 0; i < 385; i++){
    cout << setw(6) << (int)(st[0].uuid[i])
         << setw(6) << (int)st[0].mode[i]
         << setw(8) << (int)st[0].anchor[i]
         << setw(8) << (int)st[0].min[i]
         << setw(8) << (int)st[0].max[i]
         << endl;
  }



}