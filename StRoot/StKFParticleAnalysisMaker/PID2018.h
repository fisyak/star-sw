  {
    
    //d
#ifdef USETOF
    if(isTofm2 && (m2>3 && m2<4.2))
#endif
    {
      if(p<1.5){
        double lowerParameters[4] = {7.11737e+00,-1.31428e+00, 1.96720e-01, 6.47905e-02};
        double lowerDBound = lowerParameters[0]*TMath::Power(p, lowerParameters[1] + lowerParameters[2]*log(p) + lowerParameters[3]*log(p)*log(p));
   
        double upperParameters[4] = {1.39824e+01,-1.53919e+00, 1.10899e-01, 9.82910e-02};
        double upperDBound = upperParameters[0]*TMath::Power(p, upperParameters[1] + upperParameters[2]*log(p) + upperParameters[3]*log(p)*log(p));
        
        if(dEdX > lowerDBound && dEdX < upperDBound)
          totalPDG.push_back(1000010020*q); 
      }
      else if(dEdXPull[5] < nSigmaCut && dEdX < 8.) 
        totalPDG.push_back(1000010020*q); 
    }
    
    //t
#ifdef USETOF
    if(isTofm2 && (m2>6.8 && m2<9.1))
#endif
    {
      if(p<2.5) {
        double lowerParameters[4] = {1.38117e+01,-1.67910e+00,-4.52185e-03, 9.21224e-02};
        double lowerTBound = lowerParameters[0]*TMath::Power(p, lowerParameters[1] + lowerParameters[2]*log(p) + lowerParameters[3]*log(p)*log(p));

        double upperParameters[4] = {2.29456e+01,-1.41456e+00, 1.04286e-01, 1.26818e-01};
        double upperTBound = upperParameters[0]*TMath::Power(p, upperParameters[1] + upperParameters[2]*log(p) + upperParameters[3]*log(p)*log(p));
        
        if(dEdX > lowerTBound && dEdX < upperTBound)
          totalPDG.push_back(1000010030*q); 
      }
      else if(dEdXPull[6] < nSigmaCut && dEdX < 8.) 
        totalPDG.push_back(1000010030*q);
    }
    
    //He3   
    if(p<3.0)
    {
      double lowerParameters[4] = {2.27715e+01,-1.36600e+00, 3.01143e-01, 2.38046e-01};
      double lowerHe3Bound = lowerParameters[0]*TMath::Power(p, lowerParameters[1] + lowerParameters[2]*log(p) + lowerParameters[3]*log(p)*log(p));
      
      double upperParameters[4] = {3.33751e+01,-1.22800e+00, 2.98371e-01, 1.82920e-01};
      double upperHe3Bound = upperParameters[0]*TMath::Power(p, upperParameters[1] + upperParameters[2]*log(p) + upperParameters[3]*log(p)*log(p));
      
      if(dEdX > lowerHe3Bound && dEdX < upperHe3Bound) 
      {
//         if(p<1.0)
//         {
//           if( isTofm2 && (m2>1.) && (m2<3.) )
//             totalPDG.push_back(1000020030*q);
//         }
//         else
//         {
          if( !isTofm2 || (isTofm2 && (m2>1.) && (m2<3.) ) )
            totalPDG.push_back(1000020030*q);
//         }
      }
    }
    else if(p>=3.0 && dEdX > 11. && dEdX < 18.)
    {
      if(dEdXPull[7] < nSigmaCut) 
        if( !isTofm2 || (isTofm2 && (m2>1.) && (m2<3.) ) )
          totalPDG.push_back(1000020030*q);
    }
    //He4
    if(p<4.0)
    {
      double lowerParameters[4] = {3.45107e+01, -1.22371e+00,  1.89140e-01,  1.07000e-01};
      double lowerHe4Bound = lowerParameters[0]*TMath::Power(p, lowerParameters[1] + lowerParameters[2]*log(p) + lowerParameters[3]*log(p)*log(p));
      
      double upperParameters[4] = {5.09065e+01, -1.36283e+00,  1.90657e-01,  1.98235e-01};
      double upperHe4Bound = upperParameters[0]*TMath::Power(p, upperParameters[1] + upperParameters[2]*log(p) + upperParameters[3]*log(p)*log(p));
      
      if(dEdX > lowerHe4Bound && dEdX < upperHe4Bound) 
      {
//         if(p<1.0)
//         {
//           if( isTofm2 && (m2>3) && (m2<4.2) )
//             totalPDG.push_back(1000020040*q);
//         }
//         else
//         {
          if( !isTofm2 || (isTofm2 && (m2>3) && (m2<4.2) ) )
            totalPDG.push_back(1000020040*q);
//         }
      }
    }
    else if(p>=4.0 && dEdX > 11. && dEdX < 18.)
    {
      if(dEdXPull[8] < nSigmaCut) 
        if( !isTofm2 || (isTofm2 && (m2>3) && (m2<4.2) ) )
          totalPDG.push_back(1000020040*q);
    } 
// }
  }
  
  //He6
  if(p<4.5) {
    double loweParameters[4] = {5.63562e+01,-1.29479e+00, 2.27883e-01,-4.10513e-02};
    double lowerHe6Bound = loweParameters[0]*TMath::Power(p, loweParameters[1] + loweParameters[2]*log(p) + loweParameters[3]*log(p)*log(p));

    double upperParameters[4] = {7.52605e+01,-1.42948e+00, 5.87043e-01,-2.13013e-01};
    double upperHe6Bound = upperParameters[0]*TMath::Power(p, upperParameters[1] + upperParameters[2]*log(p) + upperParameters[3]*log(p)*log(p));
    
    if(dEdX > lowerHe6Bound && dEdX < upperHe6Bound) {
      if(p>3.0) {
        if(isTofm2 && m2>6.5)
          totalPDG.push_back(1000020060*q);
      }
      else{
        if(!isTofm2 || (isTofm2 && m2>6.5))
          totalPDG.push_back(1000020060*q);
      }
    }
  }
  else if(p>=4.5 && dEdX > 11. && dEdX < 18.)
    if(isTofm2 && m2>6.5)
      totalPDG.push_back(1000020060*q);

  //Li6
  if(p<4){
    double loweParameters[4] = {7.30295e+01,-1.08787e+00, 6.87593e-02, 1.14228e-01};
    double lowerLi6Bound = loweParameters[0]*TMath::Power(p, loweParameters[1] + loweParameters[2]*log(p) + loweParameters[3]*log(p)*log(p));

    double upperParameters[4] = {9.35347e+01,-1.25594e+00, 2.91456e-01, 9.52847e-02};
    double upperLi6Bound = upperParameters[0]*TMath::Power(p, upperParameters[1] + upperParameters[2]*log(p) + upperParameters[3]*log(p)*log(p));
    
    if(dEdX > lowerLi6Bound && dEdX < upperLi6Bound){
      if(p<1.){
        if( isTofm2 && (m2>2.8) && (m2<4.2) )
          totalPDG.push_back(1000030060*q);
      }
      else{
        if( !isTofm2 || (isTofm2 && (m2>2.8) && (m2<4.2) ) )
          totalPDG.push_back(1000030060*q);
      }
    }
  }
  else if(p>=4.0 && dEdX > 25. && dEdX < 37.)
    if( !isTofm2 || (isTofm2 && (m2>2.8) && (m2<4.2)) )
      totalPDG.push_back(1000030060*q);

  //Li7
  if(p<4){
    double loweParameters[4] = {9.30989e+01,-1.22084e+00, 3.73173e-01,-1.12695e-01};
    double lowerLi6Bound = loweParameters[0]*TMath::Power(p, loweParameters[1] + loweParameters[2]*log(p) + loweParameters[3]*log(p)*log(p));

    double upperParameters[4] = {1.14003e+02,-1.33179e+00, 4.19395e-01,-3.20841e-02};
    double upperLi6Bound = upperParameters[0]*TMath::Power(p, upperParameters[1] + upperParameters[2]*log(p) + upperParameters[3]*log(p)*log(p));
    
    if(dEdX > lowerLi6Bound && dEdX < upperLi6Bound){
      if(p<1.){
        if( isTofm2 && (m2>4) && (m2<6) )
          totalPDG.push_back(1000030070*q);
      }
      else{
        if( !isTofm2 || (isTofm2 && (m2>4) && (m2<6) ) )
          totalPDG.push_back(1000030070*q);
      }
    }
  }
  else if(p>=4.0 && dEdX > 25. && dEdX < 37.)
    if( !isTofm2 || (isTofm2 && (m2>4) && (m2<6)) )
      totalPDG.push_back(1000030070*q);
    
  //Be7
  if(p<4){
    double loweParameters[4] = { 1.08163e+02,-1.08057e+00, 2.34159e-01, 1.98949e-02};
    double lowerLi6Bound = loweParameters[0]*TMath::Power(p, loweParameters[1] + loweParameters[2]*log(p) + loweParameters[3]*log(p)*log(p));

    double upperParameters[4] = {1.37012e+02,-1.14016e+00, 3.73116e-01,-1.85678e-02};
    double upperLi6Bound = upperParameters[0]*TMath::Power(p, upperParameters[1] + upperParameters[2]*log(p) + upperParameters[3]*log(p)*log(p));
    
    if(dEdX > lowerLi6Bound && dEdX < upperLi6Bound){
      if(p<1.){
        if( isTofm2 && (m2>2) && (m2<4) )
          totalPDG.push_back(1000040070*q);
      }
      else{
        if( !isTofm2 || (isTofm2 && (m2>2) && (m2<4) ) )
          totalPDG.push_back(1000040070*q);
      }
    }
  }
  else if(p>=4.0 && dEdX > 40. && dEdX < 55.)
    if( !isTofm2 || (isTofm2 && (m2>2) && (m2<4)) )
      totalPDG.push_back(1000040070*q);
