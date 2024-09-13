Int_t DayInYear(Int_t yyyymmdd = 20190628) {
  Int_t year = yyyymmdd/10000;
  return TDatime::GetLegalGlobalDayFromDate(yyyymmdd) - TDatime::GetLegalGlobalDayFromDate(10000*year + 101) + 1;
}
