TGraphErrors *omegaTau() {
  struct Meas_t {Double_t x, dx, y, dy;};
#ifdef __Y2012__
  Meas_t meas[6] = {  // Inner /Outer
    {0.0,0.01, 521.52 , 0.37}, // #mum    FieldOff_Data :#sigma_{C} =   0.26 +/-   0.00 cm,    #sigma_{D} =
    {1.0,0.01, 198.01 , 0.20}, // #mum	  FullFieldA_DataS :#sigma_{C} =   0.05 +/-   0.00 cm, #sigma_{D} =
    {0.5,0.01, 314.10 , 0.28}, // #mum	  HalfField_DataS :#sigma_{C} =   0.07 +/-   0.00 cm,  #sigma_{D} =
    {0.0,0.01, 650.18 , 0.11}, // #mum	  FieldOff_Data :#sigma_{C} =   0.21 +/-   0.00 cm,    #sigma_{D} =
    {1.0,0.01, 214.41 , 0.17}, // #mum	  FullFieldA_DataS :#sigma_{C} =   0.07 +/-   0.00 cm, #sigma_{D} =
    {0.5,0.01, 331.69 , 0.15}  // #mum	  HalfField_DataS :#sigma_{C} =   0.06 +/-   0.00 cm,  #sigma_{D} =
  };
#else /* Y2023 */
  /*
InnerPad                                                    OuterPad 		
              sigma_c            sigma_d  		    sigma_c             sigma_d
RF            0.2822 +/- 0.0002  0.02905 +/- 0.00001        0.4374 +/- 0.0002   0.03107 +/- 0.0003
RHF           0.2891 +/- 0.0001  0.04392 +/- 0.00001        0.4195 +/- 0.0002   0.04763 +/- 0.0002
ZF            0.2802 +/- 0.0010  0.07816 +/- 0.00010        0.4072 +/- 0.0008   0.08254 +/- 0.0008
TpcRS_RF      0.3153 +/- 0.0002  0.02740 +/- 0.00001        0.4954 +/- 0.0003   0.03138 +/- 0.0004
TpcRS/-_RHF     0.3164 +/- 0.0001  0.04835 +/- 0.00002        0.4751 +/- 0.0001   0.05650 +/- 0.0001 
  */
  Meas_t meas[6] = {  // Inner /Outer
    {1.0,0.01, 0.02905, 0.00001}, // Inner
    {0.5,0.01, 0.04392, 0.00001}, // 
    {0.0,0.01, 0.07816, 0.00010}, // 
    {1.0,0.01, 0.03107, 0.00003}, //  Outer
    {0.5,0.01, 0.04763, 0.00002}, // 
    {0.0,0.01, 0.08254, 0.00008}  // 
  };

#endif
  TGraphErrors *gr = new TGraphErrors();
  for (int i = 0; i < 6; i++) {
#ifdef __Y2012__
    gr->SetPoint(i,5*meas[i].x,meas[i].y);
    gr->SetPointError(i,meas[i].dx,meas[i].dy);
#else
    if (meas[i].x < 0.1) continue;
    gr->SetPoint(i,5*meas[i].x,1e4*meas[i].y);
    gr->SetPointError(i,meas[i].dx,1e4*meas[i].dy);
#endif
  }
  TF1 *W = new TF1("W","[0]*sqrt((1. + [1]**2)/(1.+([1]*x/5)**2))");
  W->SetParName(0,"#sigma_{D} at 5kG"); // (#mum/#sqrt{cm}) 
  W->SetParName(1,"#omega#tau(5kG)");
  W->SetParameters(650.,2.34);
  gr->GetHistogram()->SetXTitle("B(kG)");
  gr->GetHistogram()->SetYTitle("#sigma_{D}(#mum/#sqrt{cm}");
  gr->Fit("W");
  gr->GetHistogram()->Draw();
  gr->Draw("p");
  return gr;
}
