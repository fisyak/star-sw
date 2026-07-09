#include "Ask.h"
#include "TROOT.h"
#include "TTable.h"
void TestTable(const Char_t *tab = "") {
  gROOT->LoadMacro(tab);
  TTable *t = (TTable*) CreateTable();
  t->Print(0,1);
  Ask();
}
