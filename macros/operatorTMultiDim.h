ostream& operator<<(ostream& os, const TMultiDimFit& f) {
  Int_t i, j;
  // Assignment to coefficients vector.
  os << "  row.PolyType = \t"      << f.GetPolyType() << ";" << endl;
  os << "  row.NVariables = \t"    << f.GetNVariables() << ";" << endl;
  os << "  row.NCoefficients = \t" << f.GetNCoefficients() << ";" << endl;
  for (i = 0; i < f.GetNVariables(); i++) {
    os << Form("  row.XMin[%2i] = %10.5g;", i,f.GetMinVariables()->operator()(i));
  }
  os << endl;
  for (i = 0; i < f.GetNVariables(); i++) {
    os << Form("  row.XMax[%2i] = %10.5g;", i,f.GetMaxVariables()->operator()(i));
  }
  os << endl;
  for (i = 0; i < f.GetNCoefficients(); i++) {
    for (j = 0; j < f.GetNVariables(); j++) {
      os << Form("  row.Power[%2i] = %2i;",i * f.GetNVariables() + j,
		   f.GetPowers()[f.GetPowerIndex()[i] * f.GetNVariables() + j]);
    }
    os << endl;
  }
  os << "  row.DMean = \t"          << f.GetMeanQuantity() << ";" << endl;
  for (i = 0; i < f.GetNCoefficients(); i++) {
    os << Form("  row.Coefficients[%2i]    = %15.5g;", i, f.GetCoefficients()->operator()(i));
    if ((i+1) %2 == 0) os << endl;
  }
  if (f.GetNCoefficients()%2) os << endl;
  for (i = 0; i < f.GetNCoefficients(); i++) {
    os << Form("  row.CoefficientsRMS[%2i] = %15.5g;", i, f.GetCoefficientsRMS()->operator()(i));
    if ((i+1) %2 == 0) os << endl;
  }
  if (f.GetNCoefficients()%2) os << endl;
  return os;  
}
