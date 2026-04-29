#ifndef __StGausSW_h__
#define __StGausSW_h__
#include "TF1.h"
#include "TF2.h"
#include "TMath.h"
#include "TROOT.h"
namespace StGausSW {
  TF1 *Owen_Integrand();
  TF2 *OwenTFunc();
  TF1 *GauswPDF1();
  TF1 *PDF();
  TF1 *CDF();          
};
#endif /* __StGausSW_h__ */
