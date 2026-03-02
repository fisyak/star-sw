#ifndef __CINT__
#include "tables/St_MDFCorrection4_Table.h"
#endif
TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_MDFCorrection4")) return 0;
  Int_t nrows = 2;
  MDFCorrection4_st row;
  St_MDFCorrection4 *tableSet = new St_MDFCorrection4("TpcAdcCorrection6MDF",2);
  memset(&row,0,tableSet->GetRowSize());
  row.idx      =        1;   // mdf4ADCM(2)
  row.nrows    =    nrows;
  row.PolyType = 	1;
  row.NVariables = 	4;
  row.NCoefficients = 	16;
  row.XMin[ 0] =        3.5;  row.XMin[ 1] =          2;  row.XMin[ 2] =          0;  row.XMin[ 3] =     3.0153;
  row.XMax[ 0] =         23;  row.XMax[ 1] =       12.5;  row.XMax[ 2] =        196;  row.XMax[ 3] =      9.435;
  row.Power[ 0] =  1;  row.Power[ 1] =  1;  row.Power[ 2] =  1;  row.Power[ 3] =  1;
  row.Power[ 4] =  1;  row.Power[ 5] =  2;  row.Power[ 6] =  1;  row.Power[ 7] =  1;
  row.Power[ 8] =  1;  row.Power[ 9] =  1;  row.Power[10] =  1;  row.Power[11] =  3;
  row.Power[12] =  1;  row.Power[13] =  2;  row.Power[14] =  1;  row.Power[15] =  2;
  row.Power[16] =  2;  row.Power[17] =  1;  row.Power[18] =  1;  row.Power[19] =  4;
  row.Power[20] =  2;  row.Power[21] =  2;  row.Power[22] =  1;  row.Power[23] =  1;
  row.Power[24] =  1;  row.Power[25] =  1;  row.Power[26] =  1;  row.Power[27] =  2;
  row.Power[28] =  1;  row.Power[29] =  1;  row.Power[30] =  2;  row.Power[31] =  1;
  row.Power[32] =  1;  row.Power[33] =  1;  row.Power[34] =  2;  row.Power[35] =  2;
  row.Power[36] =  2;  row.Power[37] =  1;  row.Power[38] =  1;  row.Power[39] =  3;
  row.Power[40] =  2;  row.Power[41] =  1;  row.Power[42] =  2;  row.Power[43] =  2;
  row.Power[44] =  2;  row.Power[45] =  2;  row.Power[46] =  1;  row.Power[47] =  2;
  row.Power[48] =  1;  row.Power[49] =  1;  row.Power[50] =  2;  row.Power[51] =  4;
  row.Power[52] =  1;  row.Power[53] =  2;  row.Power[54] =  2;  row.Power[55] =  2;
  row.Power[56] =  1;  row.Power[57] =  2;  row.Power[58] =  2;  row.Power[59] =  3;
  row.Power[60] =  2;  row.Power[61] =  1;  row.Power[62] =  2;  row.Power[63] =  1;
  row.DMean = 	0.381119;
  row.Coefficients[ 0]    =          62.233;  row.Coefficients[ 1]    =          18.995;
  row.Coefficients[ 2]    =          56.675;  row.Coefficients[ 3]    =          67.389;
  row.Coefficients[ 4]    =          16.869;  row.Coefficients[ 5]    =        -0.41466;
  row.Coefficients[ 6]    =          54.472;  row.Coefficients[ 7]    =         -7.9555;
  row.Coefficients[ 8]    =         -77.021;  row.Coefficients[ 9]    =          21.872;
  row.Coefficients[10]    =         -23.797;  row.Coefficients[11]    =          44.651;
  row.Coefficients[12]    =         -17.867;  row.Coefficients[13]    =         -24.613;
  row.Coefficients[14]    =          5.4189;  row.Coefficients[15]    =         -2.0618;
  row.CoefficientsRMS[ 0] =      2.1233e-10;  row.CoefficientsRMS[ 1] =      8.3146e-11;
  row.CoefficientsRMS[ 2] =      2.0541e-10;  row.CoefficientsRMS[ 3] =      4.3662e-10;
  row.CoefficientsRMS[ 4] =      1.7995e-10;  row.CoefficientsRMS[ 5] =      1.6085e-10;
  row.CoefficientsRMS[ 6] =      3.5295e-10;  row.CoefficientsRMS[ 7] =      8.0295e-11;
  row.CoefficientsRMS[ 8] =       8.215e-10;  row.CoefficientsRMS[ 9] =      1.1157e-10;
  row.CoefficientsRMS[10] =      2.9395e-10;  row.CoefficientsRMS[11] =      6.2773e-10;
  row.CoefficientsRMS[12] =       2.589e-10;  row.CoefficientsRMS[13] =      4.0052e-10;
  row.CoefficientsRMS[14] =      1.4495e-10;  row.CoefficientsRMS[15] =      8.1238e-11;
  tableSet->AddAt(&row); // idx = 1
  memset(&row,0,tableSet->GetRowSize());
  row.idx      =        2;   // mdf4ADCM(1)
  row.nrows    =    nrows;
  row.PolyType = 	1;
  row.NVariables = 	4;
  row.NCoefficients = 	17;
  row.XMin[ 0] =        3.5;  row.XMin[ 1] =          2;  row.XMin[ 2] =          0;  row.XMin[ 3] =      3.699;
  row.XMax[ 0] =         23;  row.XMax[ 1] =       12.5;  row.XMax[ 2] =        194;  row.XMax[ 3] =      9.435;
  row.Power[ 0] =  1;  row.Power[ 1] =  1;  row.Power[ 2] =  1;  row.Power[ 3] =  1;
  row.Power[ 4] =  1;  row.Power[ 5] =  2;  row.Power[ 6] =  1;  row.Power[ 7] =  1;
  row.Power[ 8] =  1;  row.Power[ 9] =  2;  row.Power[10] =  1;  row.Power[11] =  2;
  row.Power[12] =  2;  row.Power[13] =  1;  row.Power[14] =  1;  row.Power[15] =  2;
  row.Power[16] =  1;  row.Power[17] =  1;  row.Power[18] =  2;  row.Power[19] =  1;
  row.Power[20] =  1;  row.Power[21] =  2;  row.Power[22] =  1;  row.Power[23] =  3;
  row.Power[24] =  2;  row.Power[25] =  1;  row.Power[26] =  1;  row.Power[27] =  4;
  row.Power[28] =  1;  row.Power[29] =  1;  row.Power[30] =  1;  row.Power[31] =  4;
  row.Power[32] =  2;  row.Power[33] =  1;  row.Power[34] =  1;  row.Power[35] =  3;
  row.Power[36] =  1;  row.Power[37] =  1;  row.Power[38] =  2;  row.Power[39] =  3;
  row.Power[40] =  1;  row.Power[41] =  2;  row.Power[42] =  2;  row.Power[43] =  2;
  row.Power[44] =  2;  row.Power[45] =  1;  row.Power[46] =  2;  row.Power[47] =  3;
  row.Power[48] =  2;  row.Power[49] =  2;  row.Power[50] =  1;  row.Power[51] =  3;
  row.Power[52] =  1;  row.Power[53] =  2;  row.Power[54] =  2;  row.Power[55] =  3;
  row.Power[56] =  1;  row.Power[57] =  1;  row.Power[58] =  2;  row.Power[59] =  2;
  row.Power[60] =  2;  row.Power[61] =  1;  row.Power[62] =  2;  row.Power[63] =  2;
  row.Power[64] =  2;  row.Power[65] =  2;  row.Power[66] =  1;  row.Power[67] =  2;
  row.DMean = 	0.0852597;
  row.Coefficients[ 0]    =          14.757;  row.Coefficients[ 1]    =          97.241;
  row.Coefficients[ 2]    =          93.726;  row.Coefficients[ 3]    =          62.685;
  row.Coefficients[ 4]    =          37.811;  row.Coefficients[ 5]    =          64.782;
  row.Coefficients[ 6]    =          54.193;  row.Coefficients[ 7]    =          9.5396;
  row.Coefficients[ 8]    =          2.1521;  row.Coefficients[ 9]    =          55.973;
  row.Coefficients[10]    =         -41.108;  row.Coefficients[11]    =          13.335;
  row.Coefficients[12]    =         -6.4997;  row.Coefficients[13]    =           8.729;
  row.Coefficients[14]    =          8.9482;  row.Coefficients[15]    =         -16.017;
  row.Coefficients[16]    =         -7.6139;
  row.CoefficientsRMS[ 0] =      5.6589e-11;  row.CoefficientsRMS[ 1] =      3.3156e-10;
  row.CoefficientsRMS[ 2] =       4.632e-10;  row.CoefficientsRMS[ 3] =      5.2214e-10;
  row.CoefficientsRMS[ 4] =      3.8424e-10;  row.CoefficientsRMS[ 5] =      3.6194e-10;
  row.CoefficientsRMS[ 6] =      3.1196e-10;  row.CoefficientsRMS[ 7] =      1.6275e-10;
  row.CoefficientsRMS[ 8] =      1.4261e-10;  row.CoefficientsRMS[ 9] =      4.8094e-10;
  row.CoefficientsRMS[10] =      4.9739e-10;  row.CoefficientsRMS[11] =       1.918e-10;
  row.CoefficientsRMS[12] =      3.0754e-10;  row.CoefficientsRMS[13] =       2.574e-10;
  row.CoefficientsRMS[14] =         5.1e-10;  row.CoefficientsRMS[15] =      2.6051e-10;
  row.CoefficientsRMS[16] =      6.1757e-10;
  tableSet->AddAt(&row); // idx = 2
  return (TDataSet *)tableSet;
}
