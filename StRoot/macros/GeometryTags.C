/*
   root.exe lDb.C  GeometryTags.C
 */
void GeometryTags() {
  if (gClassTable->GetID("StMaker") < 0) {
    gSystem->Load("St_base");
    gSystem->Load("StChain");
  }
  DbAlias_t *db = StMaker::GetDbAliases();
  DbAlias_t *dbTag = db;
    cout << std::setw(26) << "Geoetry Tag"
	 << std::setw(10) << "date"
	 << std::setw(10) << "time" 
	 << std::setw(10) << "geometry" 
	 << std::setw(10) << "comment" << endl;
  for (Int_t i = 0; dbTag->tag; i++, dbTag++) {
    cout << std::setw(26) << dbTag->tag 
	 << std::setw(10) << dbTag->date 
	 << std::setw(10) << dbTag->time 
	 << std::setw(10) << dbTag->geometry 
	 << std::setw(10) << dbTag->comment << endl;
  }
}
