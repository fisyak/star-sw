
    //d
#ifdef USETOF
    if(isTofm2 && (m2>3 && m2<4.2))
#endif
    {
      if(p<1.5){
        double lowerParameters[4] = {7.26450e+00,-1.48942e+00,-2.71718e-01,-8.21588e-02};
        double lowerDBound = lowerParameters[0]*TMath::Power(p, lowerParameters[1] + lowerParameters[2]*log(p) + lowerParameters[3]*log(p)*log(p));

        double upperParameters[4] = {1.37151e+01,-1.45881e+00,-3.58669e-02,3.97500e-02};
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
        double lowerParameters[4] = {1.38915e+01,-1.43926e+00,-8.10367e-02,-9.39156e-03};
        double lowerTBound = lowerParameters[0]*TMath::Power(p, lowerParameters[1] + lowerParameters[2]*log(p) + lowerParameters[3]*log(p)*log(p));
   
        double upperParameters[4] = {2.20190e+01,-1.24588e+00,4.34070e-02,3.88409e-02};
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
      double lowerParameters[4] = { 2.23798e+01,-1.09106e+00, 1.35016e-01, 1.72563e-01};
      double lowerHe3Bound = lowerParameters[0]*TMath::Power(p, lowerParameters[1] + lowerParameters[2]*log(p) + lowerParameters[3]*log(p)*log(p));
      
      double upperParameters[4] = {3.09025e+01,-9.75179e-01,1.03354e-01,1.29797e-01};
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
      double lowerParameters[4] = {3.12534e+01,-9.52345e-01,1.63815e-02,2.03462e-02};
      double lowerHe4Bound = lowerParameters[0]*TMath::Power(p, lowerParameters[1] + lowerParameters[2]*log(p) + lowerParameters[3]*log(p)*log(p));
      
      double upperParameters[4] = {4.10331e+01,-1.01056e+00,1.98636e-01,-2.77912e-02};
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
  
  //He6
  if(p<4.5) {
    double loweParameters[4] = {4.59563e+01,-1.05965e+00,3.70239e-02,4.92680e-02};
    double lowerHe6Bound = loweParameters[0]*TMath::Power(p, loweParameters[1] + loweParameters[2]*log(p) + loweParameters[3]*log(p)*log(p));

    double upperParameters[4] = {5.52646e+01,-9.50780e-01,2.14347e-01,-1.03148e-01};
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
    double loweParameters[4] = {5.33123e+01,-7.79828e-01,1.13380e-01,1.39092e-04};
    double lowerLi6Bound = loweParameters[0]*TMath::Power(p, loweParameters[1] + loweParameters[2]*log(p) + loweParameters[3]*log(p)*log(p));

    double upperParameters[4] = {5.81213e+01,-7.88117e-01,5.20665e-01,-2.26597e-01};
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
    double loweParameters[4] = {5.93075e+01,-7.23992e-01,1.22609e-01,-5.17200e-02,};
    double lowerLi6Bound = loweParameters[0]*TMath::Power(p, loweParameters[1] + loweParameters[2]*log(p) + loweParameters[3]*log(p)*log(p));

    double upperParameters[4] = {7.16577e+01,-8.56517e-01,2.48878e-01,-3.66107e-02};
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
    double loweParameters[4] = { 7.16577e+01,-8.56517e-01,2.48878e-01,-3.66107e-02};
    double lowerLi6Bound = loweParameters[0]*TMath::Power(p, loweParameters[1] + loweParameters[2]*log(p) + loweParameters[3]*log(p)*log(p));

    double upperParameters[4] = {1.37012e+02,-1.14016e+00, 3.73116e-01,-1.85678e-02};
    double upperLi6Bound = upperParameters[0]*TMath::Power(p, upperParameters[1] + upperParameters[2]*log(p) + upperParameters[3]*log(p)*log(p));
    
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
