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
  row.nrows    =     nrows;
  row.PolyType = 	1;
  row.NVariables =     -4; // cut out of range
  row.NCoefficients = 	20;
  row.XMin[ 0] =        3.5;  row.XMin[ 1] =          2;  row.XMin[ 2] =          0;  row.XMin[ 3] =     3.0153;
  row.XMax[ 0] =         23;  row.XMax[ 1] =       12.5;  row.XMax[ 2] =        210;  row.XMax[ 3] =      9.435;
  row.Power[ 0] =  1;  row.Power[ 1] =  1;  row.Power[ 2] =  1;  row.Power[ 3] =  1;
  row.Power[ 4] =  1;  row.Power[ 5] =  2;  row.Power[ 6] =  1;  row.Power[ 7] =  1;
  row.Power[ 8] =  1;  row.Power[ 9] =  2;  row.Power[10] =  1;  row.Power[11] =  2;
  row.Power[12] =  1;  row.Power[13] =  1;  row.Power[14] =  1;  row.Power[15] =  2;
  row.Power[16] =  1;  row.Power[17] =  1;  row.Power[18] =  1;  row.Power[19] =  4;
  row.Power[20] =  2;  row.Power[21] =  1;  row.Power[22] =  2;  row.Power[23] =  2;
  row.Power[24] =  3;  row.Power[25] =  1;  row.Power[26] =  1;  row.Power[27] =  4;
  row.Power[28] =  3;  row.Power[29] =  2;  row.Power[30] =  1;  row.Power[31] =  3;
  row.Power[32] =  2;  row.Power[33] =  1;  row.Power[34] =  1;  row.Power[35] =  1;
  row.Power[36] =  1;  row.Power[37] =  3;  row.Power[38] =  1;  row.Power[39] =  1;
  row.Power[40] =  3;  row.Power[41] =  1;  row.Power[42] =  1;  row.Power[43] =  2;
  row.Power[44] =  1;  row.Power[45] =  4;  row.Power[46] =  1;  row.Power[47] =  1;
  row.Power[48] =  2;  row.Power[49] =  1;  row.Power[50] =  1;  row.Power[51] =  4;
  row.Power[52] =  2;  row.Power[53] =  2;  row.Power[54] =  2;  row.Power[55] =  2;
  row.Power[56] =  3;  row.Power[57] =  2;  row.Power[58] =  1;  row.Power[59] =  2;
  row.Power[60] =  4;  row.Power[61] =  1;  row.Power[62] =  1;  row.Power[63] =  2;
  row.Power[64] =  2;  row.Power[65] =  2;  row.Power[66] =  1;  row.Power[67] =  4;
  row.Power[68] =  2;  row.Power[69] =  4;  row.Power[70] =  1;  row.Power[71] =  2;
  row.Power[72] =  1;  row.Power[73] =  4;  row.Power[74] =  2;  row.Power[75] =  2;
  row.Power[76] =  4;  row.Power[77] =  1;  row.Power[78] =  1;  row.Power[79] =  3;
  row.DMean = 	0.949212;
  row.Coefficients[ 0]    =          21.821;  row.Coefficients[ 1]    =          41.481;
  row.Coefficients[ 2]    =          107.43;  row.Coefficients[ 3]    =          60.016;
  row.Coefficients[ 4]    =          24.414;  row.Coefficients[ 5]    =         -78.587;
  row.Coefficients[ 6]    =          121.77;  row.Coefficients[ 7]    =         -21.151;
  row.Coefficients[ 8]    =          4.7568;  row.Coefficients[ 9]    =         -9.2988;
  row.Coefficients[10]    =          314.88;  row.Coefficients[11]    =         -14.985;
  row.Coefficients[12]    =           48.54;  row.Coefficients[13]    =          -77.02;
  row.Coefficients[14]    =           90.83;  row.Coefficients[15]    =          38.694;
  row.Coefficients[16]    =          42.413;  row.Coefficients[17]    =          41.872;
  row.Coefficients[18]    =         -10.524;  row.Coefficients[19]    =         -8.7561;
  row.CoefficientsRMS[ 0] =      5.6838e-10;  row.CoefficientsRMS[ 1] =      9.5546e-10;
  row.CoefficientsRMS[ 2] =      3.4638e-10;  row.CoefficientsRMS[ 3] =      3.6178e-10;
  row.CoefficientsRMS[ 4] =      8.5319e-11;  row.CoefficientsRMS[ 5] =      5.4761e-10;
  row.CoefficientsRMS[ 6] =      2.0746e-10;  row.CoefficientsRMS[ 7] =      5.4033e-11;
  row.CoefficientsRMS[ 8] =      3.6794e-11;  row.CoefficientsRMS[ 9] =      5.2601e-10;
  row.CoefficientsRMS[10] =      6.4471e-10;  row.CoefficientsRMS[11] =      1.6916e-10;
  row.CoefficientsRMS[12] =      1.5968e-10;  row.CoefficientsRMS[13] =       6.914e-10;
  row.CoefficientsRMS[14] =      4.1876e-10;  row.CoefficientsRMS[15] =      8.8296e-11;
  row.CoefficientsRMS[16] =      2.0599e-10;  row.CoefficientsRMS[17] =      1.9371e-10;
  row.CoefficientsRMS[18] =      1.0857e-10;  row.CoefficientsRMS[19] =      3.6901e-11;
  tableSet->AddAt(&row); // idx = 1
  memset(&row,0,tableSet->GetRowSize());
  row.idx      =        2;   // mdf4ADCM(1)
  row.nrows    =     nrows;
  row.PolyType = 	1;
  row.NVariables =     -4; // cut out of range
  row.NCoefficients = 	20;
  row.XMin[ 0] =        3.5;  row.XMin[ 1] =          2;  row.XMin[ 2] =          0;  row.XMin[ 3] =      3.699;
  row.XMax[ 0] =         23;  row.XMax[ 1] =       12.5;  row.XMax[ 2] =        210;  row.XMax[ 3] =      9.435;
  row.Power[ 0] =  1;  row.Power[ 1] =  1;  row.Power[ 2] =  1;  row.Power[ 3] =  1;
  row.Power[ 4] =  1;  row.Power[ 5] =  2;  row.Power[ 6] =  1;  row.Power[ 7] =  1;
  row.Power[ 8] =  1;  row.Power[ 9] =  1;  row.Power[10] =  2;  row.Power[11] =  1;
  row.Power[12] =  1;  row.Power[13] =  2;  row.Power[14] =  1;  row.Power[15] =  2;
  row.Power[16] =  1;  row.Power[17] =  3;  row.Power[18] =  1;  row.Power[19] =  1;
  row.Power[20] =  2;  row.Power[21] =  2;  row.Power[22] =  1;  row.Power[23] =  2;
  row.Power[24] =  1;  row.Power[25] =  1;  row.Power[26] =  1;  row.Power[27] =  2;
  row.Power[28] =  1;  row.Power[29] =  4;  row.Power[30] =  1;  row.Power[31] =  1;
  row.Power[32] =  1;  row.Power[33] =  3;  row.Power[34] =  1;  row.Power[35] =  3;
  row.Power[36] =  2;  row.Power[37] =  2;  row.Power[38] =  1;  row.Power[39] =  4;
  row.Power[40] =  2;  row.Power[41] =  4;  row.Power[42] =  1;  row.Power[43] =  2;
  row.Power[44] =  1;  row.Power[45] =  4;  row.Power[46] =  2;  row.Power[47] =  4;
  row.Power[48] =  1;  row.Power[49] =  1;  row.Power[50] =  2;  row.Power[51] =  3;
  row.Power[52] =  4;  row.Power[53] =  1;  row.Power[54] =  1;  row.Power[55] =  1;
  row.Power[56] =  1;  row.Power[57] =  2;  row.Power[58] =  2;  row.Power[59] =  2;
  row.Power[60] =  2;  row.Power[61] =  3;  row.Power[62] =  1;  row.Power[63] =  1;
  row.Power[64] =  2;  row.Power[65] =  2;  row.Power[66] =  1;  row.Power[67] =  3;
  row.Power[68] =  4;  row.Power[69] =  2;  row.Power[70] =  1;  row.Power[71] =  1;
  row.Power[72] =  1;  row.Power[73] =  4;  row.Power[74] =  1;  row.Power[75] =  2;
  row.Power[76] =  1;  row.Power[77] =  2;  row.Power[78] =  2;  row.Power[79] =  4;
  row.DMean = 	2.07932;
  row.Coefficients[ 0]    =          24.965;  row.Coefficients[ 1]    =          43.969;
  row.Coefficients[ 2]    =          38.615;  row.Coefficients[ 3]    =          162.01;
  row.Coefficients[ 4]    =         -91.353;  row.Coefficients[ 5]    =         -34.909;
  row.Coefficients[ 6]    =          57.438;  row.Coefficients[ 7]    =         -5.4887;
  row.Coefficients[ 8]    =         -95.306;  row.Coefficients[ 9]    =         -33.702;
  row.Coefficients[10]    =          -26.77;  row.Coefficients[11]    =          4.4109;
  row.Coefficients[12]    =           57.25;  row.Coefficients[13]    =         -11.765;
  row.Coefficients[14]    =         -102.53;  row.Coefficients[15]    =           8.977;
  row.Coefficients[16]    =           -6.74;  row.Coefficients[17]    =         -11.812;
  row.Coefficients[18]    =          27.618;  row.Coefficients[19]    =         -28.457;
  row.CoefficientsRMS[ 0] =      8.1937e-11;  row.CoefficientsRMS[ 1] =      9.7967e-11;
  row.CoefficientsRMS[ 2] =      5.8907e-10;  row.CoefficientsRMS[ 3] =       7.656e-10;
  row.CoefficientsRMS[ 4] =      3.4943e-10;  row.CoefficientsRMS[ 5] =       2.803e-10;
  row.CoefficientsRMS[ 6] =      5.6664e-10;  row.CoefficientsRMS[ 7] =      6.9698e-11;
  row.CoefficientsRMS[ 8] =      3.1842e-10;  row.CoefficientsRMS[ 9] =      1.7717e-10;
  row.CoefficientsRMS[10] =      1.6377e-10;  row.CoefficientsRMS[11] =      7.6403e-11;
  row.CoefficientsRMS[12] =      5.4824e-10;  row.CoefficientsRMS[13] =      9.4837e-11;
  row.CoefficientsRMS[14] =      1.1503e-09;  row.CoefficientsRMS[15] =      8.4494e-11;
  row.CoefficientsRMS[16] =      7.8501e-11;  row.CoefficientsRMS[17] =      1.1194e-10;
  row.CoefficientsRMS[18] =      2.5648e-10;  row.CoefficientsRMS[19] =      2.3766e-10;
  tableSet->AddAt(&row); // idx = 2
  return (TDataSet *)tableSet;
}
