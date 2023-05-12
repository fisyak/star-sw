/*
  root.exe 'bfc.C(1,"P2019a,StiCA,evout,NoHistos,noTags,noRunco,PicoVtxVpdOrDefault,TpxRaw,TPC23,TpxRaw,TPC23,USE_GAIN_FROM_FILE,tpxO,NoTpxAfterBurner","/RTS/TONKO/data/st_physics_adc_20192001_raw_5500002.daq","","Plot.root")'
  root.exe 'bfc.C(1,"lana,B2022a,trgd,Tpx,TpxRaw,TPC23,LaserIT,StiCA,CorrY,OGridLeakFull,OSpaceZ2,analysis,NoHistos,NoRunco,-evout,-picoDst,-picoEvt,-picoWrite,tpxO,NoTpxAfterBurner","/hlt/cephfs/daq/2023/125/24125069/st_laser_24125069_raw_0000002.daq","","Plot.root")' PlotSecRowOflOnl.C
 */
TH2F *PlotSecRowOflOnl(Int_t sec = 2, Int_t row = 43) {// plot only and offline cluster per sector row
  TH2F *plot = StTpcRTSHitMaker::instance()->PlotSecRow(sec,row,-1);
  plot->Draw("colz");
  return plot;
}
