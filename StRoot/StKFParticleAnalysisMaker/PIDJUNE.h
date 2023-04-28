    //d
#ifdef USETOF
    if(isTofm2 && (m2>3 && m2<4.2))
#endif
    {
      if(p<1.5){
        double lowerParameters[4] = {7.02144e+00,-1.77017e+00,-2.60061e-01,-1.68402e-02};
        double lowerDBound = lowerParameters[0]*TMath::Power(p, lowerParameters[1] + lowerParameters[2]*log(p) + lowerParameters[3]*log(p)*log(p));

        double upperParameters[4] = {1.48953e+01,-1.55755e+00,-2.80406e-01,-5.87432e-02};
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
        double lowerParameters[4] = {1.47794e+01,-1.52798e+00,-1.00490e-01, 9.46116e-03};
        double lowerTBound = lowerParameters[0]*TMath::Power(p, lowerParameters[1] + lowerParameters[2]*log(p) + lowerParameters[3]*log(p)*log(p));
   
        double upperParameters[4] = {2.30993e+01,-1.34625e+00,4.73902e-02,7.94857e-02};
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
      double lowerParameters[4] = { 2.46334e+01,-9.18130e-01, 9.93814e-02, 6.08549e-02};
      double lowerHe3Bound = lowerParameters[0]*TMath::Power(p, lowerParameters[1] + lowerParameters[2]*log(p) + lowerParameters[3]*log(p)*log(p));
      
      double upperParameters[4] = {3.33680e+01,-9.69092e-01, 1.15195e-01, 9.37487e-02};
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
    else if(p>=3.0 && dEdX > 10. && dEdX < 17.)
    {
//       if(dEdXPull[7] < nSigmaCut)
        if( !isTofm2 || (isTofm2 && (m2>1.) && (m2<3.) ) )
          totalPDG.push_back(1000020030*q);
    }
    //He4
    if(p<4.0)
    {
      double lowerParameters[4] = {3.37746e+01,-9.67771e-01, 9.44445e-02, 3.52215e-02};
      double lowerHe4Bound = lowerParameters[0]*TMath::Power(p, lowerParameters[1] + lowerParameters[2]*log(p) + lowerParameters[3]*log(p)*log(p));

      double upperParameters[4] = {4.42988e+01,-1.07999e+00, 1.50885e-01, 6.51833e-02};
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
    else if(p>=4.0 && dEdX > 10. && dEdX < 17.)
    {
//       if(dEdXPull[8] < nSigmaCut) 
        if( !isTofm2 || (isTofm2 && (m2>3) && (m2<4.2) ) )
          totalPDG.push_back(1000020040*q);
    } 
 
  //He6
  if(p<4.5) {
    double loweParameters[4] = {4.94040e+01,-1.03654e+00, 4.80683e-02, 7.45434e-03};
    double lowerHe6Bound = loweParameters[0]*TMath::Power(p, loweParameters[1] + loweParameters[2]*log(p) + loweParameters[3]*log(p)*log(p));

    double upperParameters[4] = {6.71366e+01,-1.20558e+00, 1.63842e-01, 3.51544e-02};
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
  else if(p>=4.5 && dEdX > 10. && dEdX < 17.)
    if(isTofm2 && m2>6.5)
      totalPDG.push_back(1000020060*q);

  //Li6
  if(p<4){
    double loweParameters[4] = {5.79920e+01,-8.01901e-01, 6.66119e-02, 5.34188e-02};
    double lowerLi6Bound = loweParameters[0]*TMath::Power(p, loweParameters[1] + loweParameters[2]*log(p) + loweParameters[3]*log(p)*log(p));

    double upperParameters[4] = {6.66890e+01,-7.82862e-01, 2.14334e-01,-1.15082e-02};
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
  else if(p>=4.0 && dEdX > 22. && dEdX < 30.)
    if( !isTofm2 || (isTofm2 && (m2>2.8) && (m2<4.2)) )
      totalPDG.push_back(1000030060*q);
   
  //Li7
  if(p<4){
    double loweParameters[4] = {6.61051e+01,-7.37484e-01,-5.99112e-02, 5.92928e-02};
    double lowerLi6Bound = loweParameters[0]*TMath::Power(p, loweParameters[1] + loweParameters[2]*log(p) + loweParameters[3]*log(p)*log(p));

    double upperParameters[4] = {8.32337e+01,-7.56362e-01,-5.56798e-02, 8.60781e-02};
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
  else if(p>=4.0 && dEdX > 22. && dEdX < 30.)
    if( !isTofm2 || (isTofm2 && (m2>4) && (m2<6)) )
      totalPDG.push_back(1000030070*q);
    
  //Be7
  if(p<4){
    double loweParameters[4] = { 8.32337e+01,-7.56362e-01,-5.56798e-02, 8.60781e-02};
    double lowerLi6Bound = loweParameters[0]*TMath::Power(p, loweParameters[1] + loweParameters[2]*log(p) + loweParameters[3]*log(p)*log(p));

    double upperParameters[4] = {1.37012e+02,-1.14016e+00, 3.73116e-01,-1.85678e-02};
#if 0
    double upperLi6Bound = upperParameters[0]*TMath::Power(p, upperParameters[1] + upperParameters[2]*log(p) + upperParameters[3]*log(p)*log(p));
#endif    
    if(dEdX > lowerLi6Bound){
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
