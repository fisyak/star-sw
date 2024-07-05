#include "Riostream.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TNtuple.h"
#include "TString.h"
struct ZdTPoint_t {
  const Char_t *nameZ;
  Double_t     Z, dZ, sigmaZ, dsigmaZ;
  const Char_t *namedT;
  Double_t    dT, ddT, sigmadT, dsigmadT;
};
ZdTPoint_t Points[48] = {
#if 0
  {"2019/RF/31GeV_fixedTarget_EastOff",       200.42009,  0.00091,    0.08840,  0.00103, "2019/RF/31GeV_fixedTarget_EastOff",            0.07560,  0.00016,    0.01585,  0.00018},	       
  {"2019/RF/31GeV_fixedTarget",               200.43470,  0.00069,    0.07379,  0.00076, "2019/RF/31GeV_fixedTarget",                    0.07822,  0.00012,    0.01325,  0.00013}, 	       
  {"2019/RF/31GeV_fixedTarget_WestOff",       199.63596,  0.01168,    0.55554,  0.01411, "2019/RF/31GeV_fixedTarget_WestOff",           -0.06928,  0.00243,    0.10807,  0.00348},        
  {"2019/RF/3p85GeV_fixedTarget_EastOff",     200.37850,  0.00078,    0.10542,  0.00086, "2019/RF/3p85GeV_fixedTarget_EastOff",          0.06794,  0.00014,    0.01883,  0.00015},        
  {"2019/RF/3p85GeV_fixedTarget",             200.39684,  0.00069,    0.10866,  0.00072, "2019/RF/3p85GeV_fixedTarget",                  0.07125,  0.00012,    0.01948,  0.00013}, 	       
  {"2019/RF/3p85GeV_fixedTarget_WestOff",     199.54150,  0.00315,    0.32850,  0.00372, "2019/RF/3p85GeV_fixedTarget_WestOff",         -0.08265,  0.00055,    0.05703,  0.00062},        
  {"2019/RF/4p59GeV_fixedTarget_EastOff",     200.42266,  0.00058,    0.11433,  0.00055, "2019/RF/4p59GeV_fixedTarget_EastOff",          0.07603,  0.00010,    0.02053,  0.00010},        
  {"2019/RF/4p59GeV_fixedTarget",             200.44493,  0.00061,    0.12440,  0.00056, "2019/RF/4p59GeV_fixedTarget",                  0.08004,  0.00011,    0.02234,  0.00010}, 	       
  {"2019/RF/4p59GeV_fixedTarget_WestOff",     199.60199,  0.00230,    0.33435,  0.00254, "2019/RF/4p59GeV_fixedTarget_WestOff",         -0.07166,  0.00041,    0.05957,  0.00045},        
  {"2019/RF/7.3GeV_fixedTarget_EastOff",      200.38177,  0.00104,    0.11323,  0.00113, "2019/RF/7.3GeV_fixedTarget_EastOff",           0.06864,  0.00019,    0.02025,  0.00020},        
  {"2019/RF/7.3GeV_fixedTarget",              200.40489,  0.00102,    0.12369,  0.00118, "2019/RF/7.3GeV_fixedTarget",                   0.07279,  0.00018,    0.02209,  0.00021}, 	       
  {"2019/RF/7.3GeV_fixedTarget_WestOff",      199.53895,  0.00633,    0.35336,  0.00738, "2019/RF/7.3GeV_fixedTarget_WestOff",          -0.08276,  0.00108,    0.05798,  0.00127},        
  {"2020/RF/13p5GeV_fixedTarget_EastOff",     200.41893,  0.00067,    0.08890,  0.00071, "2020/RF/13p5GeV_fixedTarget_EastOff",          0.07531,  0.00012,    0.01595,  0.00013},        
  {"2020/RF/13p5GeV_fixedTarget",             200.44036,  0.00050,    0.08227,  0.00051, "2020/RF/13p5GeV_fixedTarget",                  0.07917,  0.00009,    0.01477,  0.00009}, 	       
  {"2020/RF/13p5GeV_fixedTarget_WestOff",     199.66791,  0.00837,    0.49952,  0.00979, "2020/RF/13p5GeV_fixedTarget_WestOff",         -0.06010,  0.00150,    0.08608,  0.00191},        
  {"2020/RF/19p5GeV_fixedTarget_EastOff",     200.41397,  0.00059,    0.08450,  0.00068, "2020/RF/19p5GeV_fixedTarget_EastOff",          0.07441,  0.00011,    0.01517,  0.00012},        
  {"2020/RF/19p5GeV_fixedTarget",             200.43224,  0.00041,    0.07243,  0.00045, "2020/RF/19p5GeV_fixedTarget",                  0.07770,  0.00007,    0.01300,  0.00008}, 	       
  {"2020/RF/19p5GeV_fixedTarget_WestOff",     199.66415,  0.00842,    0.55819,  0.00974, "2020/RF/19p5GeV_fixedTarget_WestOff",         -0.05712,  0.00147,    0.09486,  0.00200},        
  {"2020/RF/26p5GeV_fixedTarget_EastOff",     200.49306,  0.00052,    0.10624,  0.00054, "2020/RF/26p5GeV_fixedTarget_EastOff",          0.08885,  0.00009,    0.01914,  0.00010},        
  {"2020/RF/26p5GeV_fixedTarget",             200.50987,  0.00041,    0.10209,  0.00036, "2020/RF/26p5GeV_fixedTarget",                  0.09188,  0.00007,    0.01841,  0.00007}, 	       
  {"2020/RF/26p5GeV_fixedTarget_WestOff",     199.43742,  0.00671,    0.67248,  0.00814, "2020/RF/26p5GeV_fixedTarget_WestOff",         -0.10701,  0.00124,    0.12780,  0.00153},        
  {"2020/RF/31p2GeV_fixedTarget_EastOff",     200.44398,  0.00067,    0.09592,  0.00076, "2020/RF/31p2GeV_fixedTarget_EastOff",          0.07992,  0.00012,    0.01719,  0.00014},        
  {"2020/RF/31p2GeV_fixedTarget",             200.46561,  0.00045,    0.08177,  0.00050, "2020/RF/31p2GeV_fixedTarget",                  0.08378,  0.00008,    0.01471,  0.00009}, 	       
  {"2020/RF/31p2GeV_fixedTarget_WestOff",     199.64161,  0.00740,    0.57313,  0.00806, "2020/RF/31p2GeV_fixedTarget_WestOff",         -0.06404,  0.00130,    0.09839,  0.00151},        
  {"2020/RF/5p75GeV_fixedTarget_EastOff",     200.40683,  0.00051,    0.08235,  0.00059, "2020/RF/5p75GeV_fixedTarget_EastOff",          0.07307,  0.00009,    0.01477,  0.00011},        
  {"2020/RF/5p75GeV_fixedTarget",             200.43074,  0.00046,    0.08534,  0.00050, "2020/RF/5p75GeV_fixedTarget",                  0.07739,  0.00008,    0.01536,  0.00009}, 	       
  {"2020/RF/5p75GeV_fixedTarget_WestOff",     199.69952,  0.00359,    0.33099,  0.00480, "2020/RF/5p75GeV_fixedTarget_WestOff",         -0.05400,  0.00064,    0.05866,  0.00084},        
  {"2020/RF/7p3GeV_fixedTarget_EastOff",      200.42351,  0.00052,    0.08737,  0.00057, "2020/RF/7p3GeV_fixedTarget_EastOff",           0.07610,  0.00009,    0.01565,  0.00010},        
  {"2020/RF/7p3GeV_fixedTarget",              200.44538,  0.00046,    0.08710,  0.00048, "2020/RF/7p3GeV_fixedTarget",                   0.08005,  0.00008,    0.01564,  0.00009}, 	       
  {"2020/RF/7p3GeV_fixedTarget_WestOff",      199.70723,  0.00440,    0.36386,  0.00605, "2020/RF/7p3GeV_fixedTarget_WestOff",          -0.05242,  0.00076,    0.06273,  0.00100},        
  {"2020/RF/9p8GeV_fixedTarget_EastOff",      200.43979,  0.00060,    0.09650,  0.00067, "2020/RF/9p8GeV_fixedTarget_EastOff",           0.07907,  0.00011,    0.01733,  0.00012},        
  {"2020/RF/9p8GeV_fixedTarget",              200.46431,  0.00050,    0.09596,  0.00056, "2020/RF/9p8GeV_fixedTarget",                   0.08347,  0.00009,    0.01722,  0.00010}, 	       
  {"2020/RF/9p8GeV_fixedTarget_WestOff",      199.67862,  0.00550,    0.43440,  0.00702, "2020/RF/9p8GeV_fixedTarget_WestOff",          -0.05805,  0.00100,    0.07681,  0.00131},        
  {"2021/RF/100GeV_fixedTarget_2021_EastOff", 200.49248,  0.00142,    0.09652,  0.00145, "2021/RF/100GeV_fixedTarget_2021_EastOff",    	 0.08875,  0.00025,    0.01695,  0.00025},
  {"2021/RF/100GeV_fixedTarget_2021",         200.52567,  0.00090,    0.08298,  0.00090, "2021/RF/100GeV_fixedTarget_2021",        	 0.09468,  0.00016,    0.01478,  0.00016},       
  {"2021/RF/100GeV_fixedTarget_2021_WestOff", 199.55181,  0.01614,    0.52325,  0.02074, "2021/RF/100GeV_fixedTarget_2021_WestOff",    	-0.08031,  0.00495,    0.13784,  0.01158},
  {"2021/RF/26p5GeV_fixedTarget_2021_EastOff",200.50630,  0.00178,    0.13549,  0.00199, "2021/RF/26p5GeV_fixedTarget_2021_EastOff"   	,0.09119,  0.00032,    0.02402,  0.00034},
  {"2021/RF/26p5GeV_fixedTarget_2021",        200.52481,  0.00186,    0.13319,  0.00218, "2021/RF/26p5GeV_fixedTarget_2021",       	 0.09451,  0.00033,    0.02370,  0.00038},       
  {"2021/RF/26p5GeV_fixedTarget_2021_WestOff",199.60649,  0.01065,    0.56872,  0.01258, "2021/RF/26p5GeV_fixedTarget_2021_WestOff",    -0.07621,  0.00219,    0.10776,  0.00328},   
  {"2021/RF/3p85GeV_fixedTarget_2021_EastOff",200.43736,  0.00046,    0.09927,  0.00042, "2021/RF/3p85GeV_fixedTarget_2021_EastOff",     0.07875,  0.00008,    0.01786,  0.00008},   
  {"2021/RF/3p85GeV_fixedTarget_2021",        200.45973,  0.00043,    0.10711,  0.00038, "2021/RF/3p85GeV_fixedTarget_2021",             0.08277,  0.00008,    0.01926,  0.00007},	       
  {"2021/RF/3p85GeV_fixedTarget_2021_WestOff",199.63542,  0.00187,    0.28954,  0.00216, "2021/RF/3p85GeV_fixedTarget_2021_WestOff",    -0.06564,  0.00034,    0.05183,  0.00038},   
  {"2021/RF/44p5GeV_fixedTarget_2021_EastOff",200.46690,  0.00099,    0.08972,  0.00108, "2021/RF/44p5GeV_fixedTarget_2021_EastOff",     0.08411,  0.00018,    0.01613,  0.00019},   
  {"2021/RF/44p5GeV_fixedTarget_2021",        200.50057,  0.00073,    0.08548,  0.00079, "2021/RF/44p5GeV_fixedTarget_2021",             0.09015,  0.00013,    0.01534,  0.00014},	       
  {"2021/RF/44p5GeV_fixedTarget_2021_WestOff",199.57667,  0.01274,    0.54792,  0.01595, "2021/RF/44p5GeV_fixedTarget_2021_WestOff",    -0.07855,  0.00266,    0.10571,  0.00478},   
  {"2021/RF/70GeV_fixedTarget_2021_EastOff",  200.49456,  0.00124,    0.09109,  0.00127, "2021/RF/70GeV_fixedTarget_2021_EastOff",       0.08899,  0.00022,    0.01628,  0.00022},     
  {"2021/RF/70GeV_fixedTarget_2021",          200.52835,  0.00085,    0.08163,  0.00081, "2021/RF/70GeV_fixedTarget_2021",               0.09518,  0.00015,    0.01460,  0.00014},	       
  {"2021/RF/70GeV_fixedTarget_2021_WestOff",  199.59900,  0.01541,    0.51693,  0.02198, "2021/RF/70GeV_fixedTarget_2021_WestOff",      -0.07468,  0.00399,    0.12018,  0.00786}};    
#else /* 06/28/2024 */
  {"2019/RF/31GeV_fixedTarget_EastOff",     200.01703,  0.00093,    0.08963,  0.00106, "2019/RF/31GeV_fixedTarget_EastOff",       0.00304,  0.00017,    0.01605,  0.00019},
  {"2019/RF/31GeV_fixedTarget",             199.97647,  0.00068,    0.07984,  0.00072, "2019/RF/31GeV_fixedTarget",              -0.00420,  0.00012,    0.01437,  0.00013},
  {"2019/RF/31GeV_fixedTarget_WestOff",     200.03790,  0.01157,    0.56295,  0.01366, "2019/RF/31GeV_fixedTarget_WestOff",       0.00551,  0.00237,    0.10860,  0.00332},
  {"2019/RF/3p85GeV_fixedTarget_EastOff",   200.00670,  0.00076,    0.10531,  0.00085, "2019/RF/3p85GeV_fixedTarget_EastOff",     0.00117,  0.00014,    0.01882,  0.00015},
  {"2019/RF/3p85GeV_fixedTarget",           199.97978,  0.00071,    0.10905,  0.00074, "2019/RF/3p85GeV_fixedTarget",            -0.00367,  0.00013,    0.01950,  0.00013},
  {"2019/RF/3p85GeV_fixedTarget_WestOff",   199.91144,  0.00314,    0.32412,  0.00367, "2019/RF/3p85GeV_fixedTarget_WestOff",    -0.01580,  0.00056,    0.05699,  0.00063},
  {"2019/RF/4p59GeV_fixedTarget_EastOff",   200.00681,  0.00059,    0.11461,  0.00056, "2019/RF/4p59GeV_fixedTarget_EastOff",     0.00123,  0.00011,    0.02059,  0.00010},
  {"2019/RF/4p59GeV_fixedTarget",           199.97860,  0.00062,    0.12583,  0.00055, "2019/RF/4p59GeV_fixedTarget",            -0.00386,  0.00011,    0.02262,  0.00010},
  {"2019/RF/4p59GeV_fixedTarget_WestOff",   200.02034,  0.00232,    0.33698,  0.00259, "2019/RF/4p59GeV_fixedTarget_WestOff",     0.00362,  0.00041,    0.05997,  0.00045},
  {"2019/RF/7.3GeV_fixedTarget_EastOff",    200.00487,  0.00104,    0.11329,  0.00113, "2019/RF/7.3GeV_fixedTarget_EastOff",      0.00087,  0.00019,    0.02022,  0.00020},
  {"2019/RF/7.3GeV_fixedTarget",            199.97852,  0.00104,    0.12710,  0.00112, "2019/RF/7.3GeV_fixedTarget",             -0.00387,  0.00019,    0.02272,  0.00020},
  {"2019/RF/7.3GeV_fixedTarget_WestOff",    199.91990,  0.00607,    0.34681,  0.00679, "2019/RF/7.3GeV_fixedTarget_WestOff",     -0.01540,  0.00108,    0.05895,  0.00128},
  {"2020/RF/13p5GeV_fixedTarget_EastOff",   200.00823,  0.00066,    0.08870,  0.00071, "2020/RF/13p5GeV_fixedTarget_EastOff",     0.00147,  0.00012,    0.01590,  0.00013},
  {"2020/RF/13p5GeV_fixedTarget",           199.97693,  0.00051,    0.08385,  0.00054, "2020/RF/13p5GeV_fixedTarget",            -0.00415,  0.00009,    0.01505,  0.00010},
  {"2020/RF/13p5GeV_fixedTarget_WestOff",   200.08549,  0.00803,    0.50314,  0.00927, "2020/RF/13p5GeV_fixedTarget_WestOff",     0.01456,  0.00146,    0.08779,  0.00186},
  {"2020/RF/19p5GeV_fixedTarget_EastOff",   200.01234,  0.00060,    0.08449,  0.00069, "2020/RF/19p5GeV_fixedTarget_EastOff",     0.00219,  0.00011,    0.01514,  0.00012},
  {"2020/RF/19p5GeV_fixedTarget",           199.97643,  0.00042,    0.07438,  0.00046, "2020/RF/19p5GeV_fixedTarget",            -0.00424,  0.00008,    0.01335,  0.00008},
  {"2020/RF/19p5GeV_fixedTarget_WestOff",   200.05581,  0.00840,    0.58094,  0.01009, "2020/RF/19p5GeV_fixedTarget_WestOff",     0.01420,  0.00142,    0.09599,  0.00178},
  {"2020/RF/26p5GeV_fixedTarget_EastOff",   200.01333,  0.00053,    0.10651,  0.00054, "2020/RF/26p5GeV_fixedTarget_EastOff",     0.00240,  0.00009,    0.01916,  0.00010},
  {"2020/RF/26p5GeV_fixedTarget",           199.97782,  0.00040,    0.10283,  0.00037, "2020/RF/26p5GeV_fixedTarget",            -0.00399,  0.00007,    0.01851,  0.00007},
  {"2020/RF/26p5GeV_fixedTarget_WestOff",   199.89201,  0.00689,    0.71890,  0.00836, "2020/RF/26p5GeV_fixedTarget_WestOff",    -0.02036,  0.00127,    0.12941,  0.00171},
  {"2020/RF/31p2GeV_fixedTarget_EastOff",   200.01205,  0.00067,    0.09552,  0.00077, "2020/RF/31p2GeV_fixedTarget_EastOff",     0.00216,  0.00012,    0.01716,  0.00014},
  {"2020/RF/31p2GeV_fixedTarget",           199.97530,  0.00047,    0.08492,  0.00050, "2020/RF/31p2GeV_fixedTarget",            -0.00444,  0.00009,    0.01526,  0.00009},
  {"2020/RF/31p2GeV_fixedTarget_WestOff",   200.05271,  0.00797,    0.60486,  0.00972, "2020/RF/31p2GeV_fixedTarget_WestOff",     0.01116,  0.00142,    0.10530,  0.00175},
  {"2020/RF/5p75GeV_fixedTarget_EastOff",   200.00636,  0.00052,    0.08233,  0.00060, "2020/RF/5p75GeV_fixedTarget_EastOff",     0.00114,  0.00009,    0.01476,  0.00011},
  {"2020/RF/5p75GeV_fixedTarget",           199.97644,  0.00045,    0.08336,  0.00048, "2020/RF/5p75GeV_fixedTarget",            -0.00424,  0.00008,    0.01496,  0.00009},
  {"2020/RF/5p75GeV_fixedTarget_WestOff",   200.10421,  0.00356,    0.33606,  0.00478, "2020/RF/5p75GeV_fixedTarget_WestOff",     0.01876,  0.00062,    0.05851,  0.00079},
  {"2020/RF/7p3GeV_fixedTarget_EastOff",    200.00771,  0.00053,    0.08689,  0.00056, "2020/RF/7p3GeV_fixedTarget_EastOff",      0.00140,  0.00009,    0.01561,  0.00010},
  {"2020/RF/7p3GeV_fixedTarget",            199.97745,  0.00045,    0.08741,  0.00047, "2020/RF/7p3GeV_fixedTarget",             -0.00406,  0.00008,    0.01569,  0.00008},
  {"2020/RF/7p3GeV_fixedTarget_WestOff",    200.12664,  0.00430,    0.35857,  0.00607, "2020/RF/7p3GeV_fixedTarget_WestOff",      0.02278,  0.00074,    0.06080,  0.00096},
  {"2020/RF/9p8GeV_fixedTarget_EastOff",    200.00624,  0.00060,    0.09651,  0.00068, "2020/RF/9p8GeV_fixedTarget_EastOff",      0.00111,  0.00011,    0.01731,  0.00012},
  {"2020/RF/9p8GeV_fixedTarget",            199.97701,  0.00053,    0.09913,  0.00059, "2020/RF/9p8GeV_fixedTarget",             -0.00415,  0.00010,    0.01781,  0.00011},
  {"2020/RF/9p8GeV_fixedTarget_WestOff",    200.11476,  0.00552,    0.43595,  0.00673, "2020/RF/9p8GeV_fixedTarget_WestOff",      0.02126,  0.00097,    0.07535,  0.00115},
  {"2021/RF/100GeV_fixedTarget_EastOff",    200.00317,  0.00143,    0.09599,  0.00152, "2021/RF/100GeV_fixedTarget_EastOff",      0.00062,  0.00026,    0.01702,  0.00026},
  {"2021/RF/100GeV_fixedTarget",            199.97219,  0.00096,    0.08514,  0.00091, "2021/RF/100GeV_fixedTarget",             -0.00504,  0.00017,    0.01529,  0.00016},
  {"2021/RF/100GeV_fixedTarget_WestOff",    200.05692,  0.01674,    0.55629,  0.02341, "2021/RF/100GeV_fixedTarget_WestOff",      0.00951,  0.00496,    0.14020,  0.01134},
  {"2021/RF/26p5GeV_fixedTarget_EastOff",   200.01499,  0.00176,    0.13580,  0.00197, "2021/RF/26p5GeV_fixedTarget_EastOff",     0.00286,  0.00032,    0.02423,  0.00035},
  {"2021/RF/26p5GeV_fixedTarget",           199.97833,  0.00186,    0.13721,  0.00202, "2021/RF/26p5GeV_fixedTarget",            -0.00389,  0.00033,    0.02419,  0.00035},
  {"2021/RF/26p5GeV_fixedTarget_WestOff",   200.10468,  0.01053,    0.56623,  0.01326, "2021/RF/26p5GeV_fixedTarget_WestOff",     0.02097,  0.00202,    0.10215,  0.00292},
  {"2021/RF/3p85GeV_fixedTarget_EastOff",   200.00923,  0.00046,    0.09987,  0.00043, "2021/RF/3p85GeV_fixedTarget_EastOff",     0.00166,  0.00008,    0.01796,  0.00008},
  {"2021/RF/3p85GeV_fixedTarget",           199.97746,  0.00044,    0.10717,  0.00038, "2021/RF/3p85GeV_fixedTarget",            -0.00405,  0.00008,    0.01928,  0.00007},
  {"2021/RF/3p85GeV_fixedTarget_WestOff",   200.06684,  0.00185,    0.28676,  0.00217, "2021/RF/3p85GeV_fixedTarget_WestOff",     0.01200,  0.00033,    0.05133,  0.00038},
  {"2021/RF/44p5GeV_fixedTarget_EastOff",   200.00383,  0.00102,    0.09107,  0.00112, "2021/RF/44p5GeV_fixedTarget_EastOff",     0.00071,  0.00018,    0.01633,  0.00020},
  {"2021/RF/44p5GeV_fixedTarget",           199.97482,  0.00075,    0.08688,  0.00080, "2021/RF/44p5GeV_fixedTarget",            -0.00453,  0.00013,    0.01561,  0.00014},
  {"2021/RF/44p5GeV_fixedTarget_WestOff",   200.04541,  0.01211,    0.52367,  0.01648, "2021/RF/44p5GeV_fixedTarget_WestOff",     0.00919,  0.00272,    0.10842,  0.00464},
  {"2021/RF/70GeV_fixedTarget_EastOff",     200.00524,  0.00125,    0.09040,  0.00129, "2021/RF/70GeV_fixedTarget_EastOff",       0.00100,  0.00022,    0.01614,  0.00023},
  {"2021/RF/70GeV_fixedTarget",             199.97245,  0.00083,    0.08313,  0.00080, "2021/RF/70GeV_fixedTarget",              -0.00495,  0.00015,    0.01485,  0.00014},
  {"2021/RF/70GeV_fixedTarget_WestOff",     200.08259,  0.01702,    0.58780,  0.02478, "2021/RF/70GeV_fixedTarget_WestOff",       0.01400,  0.00497,    0.14559,  0.01169}
#endif
};
void FXTT0() {
  struct BPoint_t {
    Float_t run; //  0 -> 2019/RF/31GeV_fixedTarget, 15 -> "2021/RF/70GeV_fixedTarget
    Float_t sta; //  0 -> All, 1 -> East Off, 2 -> West Off
    Float_t Z, dZ;
    Float_t sigmaZ, dsigmaZ;
    Float_t dT, ddT;
    Float_t sigmadT, dsigmadT;
  };
  TNtuple *FitP = new TNtuple("FitP","FitP","run:sta:Z:dZ:sigmaZ:dsigmaZ:dT:ddT:sigmadT:dsigmadT");
  BPoint_t B;
  for (Int_t i = 0; i < 48; i++) {
    B.run = i/3;
    TString nameZ(Points[i].nameZ);
    TString namedT(Points[i].namedT);
    if (nameZ != namedT) {
      cout << i << "names " << nameZ.Data() << " & " << namedT.Data() << " does not matched" << endl;
      continue;
    }
    B.sta = 0;
    if      (nameZ.EndsWith("EastOff")) B.sta = 1;
    else if (nameZ.EndsWith("WestOff")) B.sta = 2;
    B.Z = Points[i].Z;
    B.dZ = Points[i].dZ;
    B.sigmaZ = Points[i].sigmaZ;
    B.dsigmaZ = Points[i].dsigmaZ;
    B.dT = Points[i].dT;
    B.ddT = Points[i].ddT;
    B.sigmadT = Points[i].sigmadT;
    B.dsigmadT = Points[i].dsigmadT;
    FitP->Fill(&B.run);
  }
  
}


















































