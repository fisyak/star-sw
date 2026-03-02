#ifndef St_TpcAdcCorrectPromptC_h
#define St_TpcAdcCorrectPromptC_h
#include "St_tpcCorrectionC.h"
class St_TpcAdcCorrectPromptC : public St_tpcCorrectionC {
 public:
  static St_TpcAdcCorrectPromptC* 	instance();
 protected:
  St_TpcAdcCorrectPromptC(St_tpcCorrection *table=0) : St_tpcCorrectionC(table) {}
  virtual ~St_TpcAdcCorrectPromptC() {fgInstance = 0;}
 private:
  static St_TpcAdcCorrectPromptC* fgInstance;
  ClassDef(St_TpcAdcCorrectPromptC,1)
};
#endif
