void PrintListOfRotations() {
  if (! gGeoManager) return;
  TCollection *col = gGeoManager->GetListOfMatrices();
  if (! col) return;
  TIter next(col);
  TObject *obj;
  while ((obj = next())) {
    TString name(obj->GetName());
    if (! (name.BeginsWith("R") || name.BeginsWith("Y"))) continue;
    cout << obj->GetName() << "\t" << obj->GetTitle() << endl;
  }
}

