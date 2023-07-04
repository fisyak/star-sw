void PrintListOfFunctions(TH1 *hist = 0) {
  TCollection *col = 0;
  if (hist) col = hist->GetListOfFunctions();
  else      col = gROOT->GetListOfFunctions();
  if (! col) return;
  if (hist) {cout << "List of Functions for hist " << hist->GetName() << endl;}
  TIter next(col);
  TObject *obj;
  while ((obj = next())) {
    cout << obj->GetName() << "\t" << obj->GetTitle() << endl;
  }
}
void PrintListOfFunctions(TMultiGraph *mg = 0) {
  TCollection *col = 0;
  if (mg) col = mg->GetListOfFunctions();
  else      col = gROOT->GetListOfFunctions();
  if (! col) return;
  if (mg) {cout << "List of Functions for multi graph " << mg->GetName() << endl;}
  TIter next(col);
  TObject *obj;
  while ((obj = next())) {
    cout << obj->GetName() << "\t" << obj->GetTitle() << endl;
  }
}
