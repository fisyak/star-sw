static const Int_t Npart4EY = 6;
TH1D *fgITH1 = 0;
//________________________________________________________________________________
Double_t gf4EYFunc(Double_t *x, Double_t *par) {
  Double_t XX[1] = {x[0]};
  // par[0] - norm
  // par[1] - pion position wrt Z_pion (Bichsel prediction)
  // par[2] - sigma 
  // par[3] - proton signal  1
  // par[4] - Kaon    -"-    2
  // par[5] - electorn -"-   3
  // par[6] - deuteron -"-   4
  // par[7] - muon           5
  // par[8] - triton         6
  // par[9] - He3            7
  // par[10]- alpha          8
  // par[11] - Total
  // par[12] - case (-1 all, >-0 hyp no.)
  // par[13] - occupancy = probability to have 2d hits in the cluster 
  // par[14] - IO
  // par[15] - sign
  // par[16] - eLoss || Scale || mean20
  // par[17] - RMS20
  Double_t mu    = par[1];
  Double_t sigma = par[2];
  Double_t occupancy = par[13];
  Double_t scale = 1;
  //#define __ELOSS__
#ifdef __ELOSS__
  Double_t eLoss = par[16];
#else 
  //#define __SCALE__
#ifdef __SCALE__
  scale = 1 + par[16];
  //  XX[0] *= scale;
#endif /* __SCALE__ */
#endif /* __ELOSS__ */
  Double_t mean20 = par[16];
  Double_t RMS20  = par[17];
  Int_t IO = par[14];
  IO = TMath::Max(0, TMath::Min(1, IO));
  Int_t sign = par[15];
  Double_t frac[9] = {0};
  frac[0] = 1;
  for (Int_t i = 1; i < Npart4EY; i++) {
    frac[i] = TMath::Sin(par[2+i]);
    frac[i] *= frac[i];
      frac[0] -= frac[i];
  }
  if (frac[0] + frac[1] < 0.5) return 0;
  if (frac[0] < 0.4 && frac[1] < 0.4) return 0;
  // 12/08/2022 /hlt/cephfs/fisyak/TpcRS_2021.COL.NoPad/dEdx/Fit
  static MIPFitParX_t parMIPs[27][3][2] = {
    {{ // particle, norml, mu, sigma, alpha
	{ 0,-1, 0, 0,"zIpionN"                       ,   10.55461,   -0.22508,    0.30905,    0.83609},
	{ 0,-1, 0, 1,"zOpionN"                       ,   10.26347,   -0.15703,    0.31314,    0.91502} },{
	{ 0,-1, 1, 0,"zIpionP"                       ,   10.53485,   -0.23162,    0.31448,    0.84487},
	{ 0,-1, 1, 1,"zOpionP"                       ,   10.24889,   -0.16415,    0.31586,    0.90912} },{
	{ 0,-1, 2, 0,"zIpion"                        ,   11.23755,   -0.22710,    0.31246,    0.84902},
	{ 0,-1, 2, 1,"zOpion"                        ,   10.94933,   -0.16031,    0.31469,    0.91410} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 1,-1, 0, 0,"zIprotonN"                     ,   10.35391,    0.97405,    0.26455,    1.08510},
	{ 1,-1, 0, 1,"zOprotonN"                     ,   10.00209,    1.08777,    0.24208,    1.30000} },{
	{ 1,-1, 1, 0,"zIprotonP"                     ,   10.09485,    0.97852,    0.26629,    1.08440},
	{ 1,-1, 1, 1,"zOprotonP"                     ,    9.74937,    1.09336,    0.24376,    1.30000} },{
	{ 1,-1, 2, 0,"zIproton"                      ,   10.92575,    0.97641,    0.26559,    1.09038},
	{ 1,-1, 2, 1,"zOproton"                      ,   10.57697,    1.09026,    0.24291,    1.30000} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 2,-1, 0, 0,"zIkaonN"                       ,   10.50851,    0.19068,    0.29369,    0.87546},
	{ 2,-1, 0, 1,"zOkaonN"                       ,   10.18013,    0.28847,    0.27374,    0.89386} },{
	{ 2,-1, 1, 0,"zIkaonP"                       ,   10.50028,    0.18801,    0.29620,    0.87240},
	{ 2,-1, 1, 1,"zOkaonP"                       ,   10.17363,    0.28766,    0.27686,    0.90140} },{
	{ 2,-1, 2, 0,"zIkaon"                        ,   11.19721,    0.19029,    0.29549,    0.88153},
	{ 2,-1, 2, 1,"zOkaon"                        ,   10.87007,    0.28816,    0.27537,    0.89833} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 3,-1, 0, 0,"zIelectronN"                   ,   10.59759,    0.08103,    0.29449,    0.90390},
	{ 3,-1, 0, 1,"zOelectronN"                   ,   10.24819,    0.17190,    0.27737,    0.93702} },{
	{ 3,-1, 1, 0,"zIelectronP"                   ,   10.59083,    0.07710,    0.29887,    0.90672},
	{ 3,-1, 1, 1,"zOelectronP"                   ,   10.25519,    0.17002,    0.28135,    0.94273} },{
	{ 3,-1, 2, 0,"zIelectron"                    ,   11.28739,    0.07921,    0.29681,    0.90630},
	{ 3,-1, 2, 1,"zOelectron"                    ,   10.94492,    0.17100,    0.27942,    0.94005} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 4,-1, 0, 0,""                              ,    0.00000,    0.00000,    0.00000,    0.00000},
	{ 4,-1, 0, 1,""                              ,    0.00000,    0.00000,    0.00000,    0.00000} },{
	{ 4,-1, 1, 0,"zIdeuteronP"                   ,    9.02019,    1.94398,    0.15482,    1.30000},
	{ 4,-1, 1, 1,"zOdeuteronP"                   ,    7.46098,    1.96957,    0.11494,    1.30000} },{
	{ 4,-1, 2, 0,"zIdeuteron"                    ,    9.02019,    1.94398,    0.15482,    1.30000},
	{ 4,-1, 2, 1,"zOdeuteron"                    ,    7.46098,    1.96957,    0.11494,    1.30000} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 5,-1, 0, 0,"zImuonN"                       ,   10.56192,   -0.21850,    0.30735,    0.83160},
	{ 5,-1, 0, 1,"zOmuonN"                       ,   10.27084,   -0.14855,    0.31129,    0.91524} },{
	{ 5,-1, 1, 0,"zImuonP"                       ,   10.55341,   -0.22201,    0.31463,    0.84945},
	{ 5,-1, 1, 1,"zOmuonP"                       ,   10.26680,   -0.15313,    0.31553,    0.92188} },{
	{ 5,-1, 2, 0,"zImuon"                        ,   11.25054,   -0.21931,    0.31152,    0.84690},
	{ 5,-1, 2, 1,"zOmuon"                        ,   10.96205,   -0.15077,    0.31349,    0.91900} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 0, 0, 0, 0,"zIpionN+zIpionN"               ,   10.55256,    0.52339,    0.23607,    0.77581},
	{ 0, 0, 0, 1,"zOpionN+zOpionN"               ,   10.26244,    0.58828,    0.23988,    0.86941} },{
	{ 0, 0, 1, 0,"zIpionP+zIpionP"               ,   10.53291,    0.51702,    0.23985,    0.78182},
	{ 0, 0, 1, 1,"zOpionP+zOpionP"               ,   10.24813,    0.58261,    0.24241,    0.86378} },{
	{ 0, 0, 2, 0,"zIpion+zIpion"                 ,   11.23537,    0.52091,    0.23808,    0.78677},
	{ 0, 0, 2, 1,"zOpion+zOpion"                 ,   10.94827,    0.58458,    0.24072,    0.86366} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 1, 0, 0, 0,"zIprotonN+zIpionN"             ,   10.35426,    1.27914,    0.22662,    1.01482},
	{ 1, 0, 0, 1,"zOprotonN+zOpionN"             ,   10.00533,    1.37744,    0.21383,    1.23789} },{
	{ 1, 0, 1, 0,"zIprotonP+zIpionP"             ,   10.09468,    1.28051,    0.22806,    1.01764},
	{ 1, 0, 1, 1,"zOprotonP+zOpionP"             ,    9.75295,    1.38098,    0.21493,    1.21916} },{
	{ 1, 0, 2, 0,"zIproton+zIpion"               ,   10.92564,    1.28024,    0.22785,    1.02413},
	{ 1, 0, 2, 1,"zOproton+zOpion"               ,   10.57990,    1.37978,    0.21469,    1.23466} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 1, 1, 0, 0,"zIprotonN+zIprotonN"           ,   10.35474,    1.70744,    0.20477,    1.14079},
	{ 1, 1, 0, 1,"zOprotonN+zOprotonN"           ,   10.00422,    1.80554,    0.18176,    1.30000} },{
	{ 1, 1, 1, 0,"zIprotonP+zIprotonP"           ,   10.09492,    1.71219,    0.20603,    1.13058},
	{ 1, 1, 1, 1,"zOprotonP+zOprotonP"           ,    9.75205,    1.81165,    0.18266,    1.30000} },{
	{ 1, 1, 2, 0,"zIproton+zIproton"             ,   10.92647,    1.71043,    0.20593,    1.14915},
	{ 1, 1, 2, 1,"zOproton+zOproton"             ,   10.57977,    1.80821,    0.18205,    1.30000} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 2, 0, 0, 0,"zIkaonN+zIpionN"               ,   10.50540,    0.75231,    0.23366,    0.82976},
	{ 2, 0, 0, 1,"zOkaonN+zOpionN"               ,   10.17915,    0.83586,    0.22663,    0.89607} },{
	{ 2, 0, 1, 0,"zIkaonP+zIpionP"               ,   10.49819,    0.74787,    0.23510,    0.82107},
	{ 2, 0, 1, 1,"zOkaonP+zOpionP"               ,   10.17248,    0.83401,    0.22919,    0.89659} },{
	{ 2, 0, 2, 0,"zIkaon+zIpion"                 ,   11.19533,    0.74921,    0.23368,    0.82280},
	{ 2, 0, 2, 1,"zOkaon+zOpion"                 ,   10.86932,    0.83329,    0.22745,    0.89017} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 2, 1, 0, 0,"zIkaonN+zIprotonN"             ,   10.50505,    1.39603,    0.21962,    1.03836},
	{ 2, 1, 0, 1,"zOkaonN+zOprotonN"             ,   10.17712,    1.50078,    0.20457,    1.23585} },{
	{ 2, 1, 1, 0,"zIkaonP+zIprotonP"             ,   10.49754,    1.39767,    0.22049,    1.01969},
	{ 2, 1, 1, 1,"zOkaonP+zOprotonP"             ,   10.17014,    1.50488,    0.20683,    1.24065} },{
	{ 2, 1, 2, 0,"zIkaon+zIproton"               ,   11.19345,    1.39857,    0.22104,    1.05567},
	{ 2, 1, 2, 1,"zOkaon+zOproton"               ,   10.86676,    1.50306,    0.20585,    1.23635} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 2, 2, 0, 0,"zIkaonN+zIkaonN"               ,   10.50569,    0.93768,    0.22672,    0.84671},
	{ 2, 2, 0, 1,"zOkaonN+zOkaonN"               ,   10.17806,    1.03683,    0.21707,    0.92871} },{
	{ 2, 2, 1, 0,"zIkaonP+zIkaonP"               ,   10.49791,    0.93482,    0.22831,    0.83579},
	{ 2, 2, 1, 1,"zOkaonP+zOkaonP"               ,   10.17204,    1.03569,    0.21870,    0.92708} },{
	{ 2, 2, 2, 0,"zIkaon+zIkaon"                 ,   11.19458,    0.93742,    0.22803,    0.84844},
	{ 2, 2, 2, 1,"zOkaon+zOkaon"                 ,   10.86863,    1.03655,    0.21867,    0.93270} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 3, 0, 0, 0,"zIelectronN+zIpionN"           ,   10.59556,    0.68641,    0.23180,    0.83071},
	{ 3, 0, 0, 1,"zOelectronN+zOpionN"           ,   10.24824,    0.76519,    0.22816,    0.91655} },{
	{ 3, 0, 1, 0,"zIelectronP+zIpionP"           ,   10.58863,    0.68135,    0.23511,    0.83584},
	{ 3, 0, 1, 1,"zOelectronP+zOpionP"           ,   10.25513,    0.76301,    0.23121,    0.92057} },{
	{ 3, 0, 2, 0,"zIelectron+zIpion"             ,   11.28543,    0.68472,    0.23398,    0.83803},
	{ 3, 0, 2, 1,"zOelectron+zOpion"             ,   10.94476,    0.76362,    0.22876,    0.91204} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 3, 1, 0, 0,"zIelectronN+zIprotonN"         ,   10.59464,    1.36080,    0.22047,    1.05632},
	{ 3, 1, 0, 1,"zOelectronN+zOprotonN"         ,   10.24508,    1.46467,    0.20647,    1.29306} },{
	{ 3, 1, 1, 0,"zIelectronP+zIprotonP"         ,   10.58813,    1.36209,    0.22182,    1.04424},
	{ 3, 1, 1, 1,"zOelectronP+zOprotonP"         ,   10.25086,    1.46852,    0.20856,    1.29285} },{
	{ 3, 1, 2, 0,"zIelectron+zIproton"           ,   11.28361,    1.36257,    0.22193,    1.07091},
	{ 3, 1, 2, 1,"zOelectron+zOproton"           ,   10.94148,    1.46556,    0.20716,    1.28528} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 3, 2, 0, 0,"zIelectronN+zIkaonN"           ,   10.59478,    0.88405,    0.22716,    0.86261},
	{ 3, 2, 0, 1,"zOelectronN+zOkaonN"           ,   10.24665,    0.97864,    0.21766,    0.94142} },{
	{ 3, 2, 1, 0,"zIelectronP+zIkaonP"           ,   10.58855,    0.88180,    0.22993,    0.86233},
	{ 3, 2, 1, 1,"zOelectronP+zOkaonP"           ,   10.25413,    0.97671,    0.22004,    0.94271} },{
	{ 3, 2, 2, 0,"zIelectron+zIkaon"             ,   11.28456,    0.88274,    0.22821,    0.86319},
	{ 3, 2, 2, 1,"zOelectron+zOkaon"             ,   10.94358,    0.97815,    0.21959,    0.94992} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 3, 3, 0, 0,"zIelectronN+zIelectronN"       ,   10.59427,    0.82785,    0.22748,    0.88338},
	{ 3, 3, 0, 1,"zOelectronN+zOelectronN"       ,   10.24639,    0.91782,    0.21888,    0.97102} },{
	{ 3, 3, 1, 0,"zIelectronP+zIelectronP"       ,   10.58801,    0.82371,    0.23016,    0.88167},
	{ 3, 3, 1, 1,"zOelectronP+zOelectronP"       ,   10.25312,    0.91505,    0.22095,    0.96165} },{
	{ 3, 3, 2, 0,"zIelectron+zIelectron"         ,   11.28462,    0.82518,    0.22830,    0.87644},
	{ 3, 3, 2, 1,"zOelectron+zOelectron"         ,   10.94279,    0.91660,    0.21996,    0.96736} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 4, 0, 0, 0,""                              ,    0.00000,    0.00000,    0.00000,    0.00000},
	{ 4, 0, 0, 1,""                              ,    0.00000,    0.00000,    0.00000,    0.00000} },{
	{ 4, 0, 1, 0,"zIdeuteronP+zIpionP"           ,    9.04734,    2.07555,    0.15765,    1.30000},
	{ 4, 0, 1, 1,"zOdeuteronP+zOpionP"           ,    7.50076,    2.10155,    0.12277,    1.30000} },{
	{ 4, 0, 2, 0,"zIdeuteron+zIpion"             ,    9.04677,    2.07582,    0.15787,    1.30000},
	{ 4, 0, 2, 1,"zOdeuteron+zOpion"             ,    7.50208,    2.10231,    0.12379,    1.30000} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 4, 1, 0, 0,""                              ,    0.00000,    0.00000,    0.00000,    0.00000},
	{ 4, 1, 0, 1,""                              ,    0.00000,    0.00000,    0.00000,    0.00000} },{
	{ 4, 1, 1, 0,"zIdeuteronP+zIprotonP"         ,    9.05309,    2.29153,    0.14909,    1.30000},
	{ 4, 1, 1, 1,"zOdeuteronP+zOprotonP"         ,    7.50082,    2.33058,    0.11651,    1.30000} },{
	{ 4, 1, 2, 0,"zIdeuteron+zIproton"           ,    9.05267,    2.29131,    0.14930,    1.30000},
	{ 4, 1, 2, 1,"zOdeuteron+zOproton"           ,    7.49785,    2.32895,    0.11625,    1.30000} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 4, 2, 0, 0,""                              ,    0.00000,    0.00000,    0.00000,    0.00000},
	{ 4, 2, 0, 1,""                              ,    0.00000,    0.00000,    0.00000,    0.00000} },{
	{ 4, 2, 1, 0,"zIdeuteronP+zIkaonP"           ,    9.05210,    2.13143,    0.15677,    1.30000},
	{ 4, 2, 1, 1,"zOdeuteronP+zOkaonP"           ,    7.50611,    2.16374,    0.12366,    1.30000} },{
	{ 4, 2, 2, 0,"zIdeuteron+zIkaon"             ,    9.05078,    2.13119,    0.15614,    1.30000},
	{ 4, 2, 2, 1,"zOdeuteron+zOkaon"             ,    7.50635,    2.16306,    0.12274,    1.30000} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 4, 3, 0, 0,""                              ,    0.00000,    0.00000,    0.00000,    0.00000},
	{ 4, 3, 0, 1,""                              ,    0.00000,    0.00000,    0.00000,    0.00000} },{
	{ 4, 3, 1, 0,"zIdeuteronP+zIelectronP"       ,    9.04467,    2.11231,    0.15347,    1.30000},
	{ 4, 3, 1, 1,"zOdeuteronP+zOelectronP"       ,    7.50228,    2.14324,    0.12038,    1.30000} },{
	{ 4, 3, 2, 0,"zIdeuteron+zIelectron"         ,    9.04539,    2.11153,    0.15365,    1.30000},
	{ 4, 3, 2, 1,"zOdeuteron+zOelectron"         ,    7.50085,    2.14445,    0.12110,    1.30000} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 4, 4, 0, 0,""                              ,    0.00000,    0.00000,    0.00000,    0.00000},
	{ 4, 4, 0, 1,""                              ,    0.00000,    0.00000,    0.00000,    0.00000} },{
	{ 4, 4, 1, 0,"zIdeuteronP+zIdeuteronP"       ,    9.01791,    2.64792,    0.11093,    1.30000},
	{ 4, 4, 1, 1,"zOdeuteronP+zOdeuteronP"       ,    7.40383,    2.65872,    0.10000,    1.30000} },{
	{ 4, 4, 2, 0,"zIdeuteron+zIdeuteron"         ,    9.02260,    2.64905,    0.11221,    1.30000},
	{ 4, 4, 2, 1,"zOdeuteron+zOdeuteron"         ,    7.38714,    2.65772,    0.10000,    1.30000} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 5, 0, 0, 0,"zImuonN+zIpionN"               ,   10.55934,    0.52740,    0.23594,    0.78342},
	{ 5, 0, 0, 1,"zOmuonN+zOpionN"               ,   10.26983,    0.59304,    0.23934,    0.87102} },{
	{ 5, 0, 1, 0,"zImuonP+zIpionP"               ,   10.55147,    0.52215,    0.23977,    0.78675},
	{ 5, 0, 1, 1,"zOmuonP+zOpionP"               ,   10.26585,    0.58848,    0.24227,    0.87475} },{
	{ 5, 0, 2, 0,"zImuon+zIpion"                 ,   11.24799,    0.52655,    0.23864,    0.79379},
	{ 5, 0, 2, 1,"zOmuon+zOpion"                 ,   10.96039,    0.59103,    0.24157,    0.88356} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 5, 1, 0, 0,"zImuonN+zIprotonN"             ,   10.55688,    1.28250,    0.22777,    1.04536},
	{ 5, 1, 0, 1,"zOmuonN+zOprotonN"             ,   10.26603,    1.37928,    0.21298,    1.23480} },{
	{ 5, 1, 1, 0,"zImuonP+zIprotonP"             ,   10.54872,    1.28396,    0.22865,    1.02796},
	{ 5, 1, 1, 1,"zOmuonP+zOprotonP"             ,   10.26093,    1.38312,    0.21478,    1.23380} },{
	{ 5, 1, 2, 0,"zImuon+zIproton"               ,   11.24620,    1.28209,    0.22723,    1.02194},
	{ 5, 1, 2, 1,"zOmuon+zOproton"               ,   10.95606,    1.38156,    0.21388,    1.23328} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 5, 2, 0, 0,"zImuonN+zIkaonN"               ,   10.55885,    0.75411,    0.23259,    0.82105},
	{ 5, 2, 0, 1,"zOmuonN+zOkaonN"               ,   10.26814,    0.83929,    0.22670,    0.90103} },{
	{ 5, 2, 1, 0,"zImuonP+zIkaonP"               ,   10.55012,    0.75019,    0.23445,    0.82040},
	{ 5, 2, 1, 1,"zOmuonP+zOkaonP"               ,   10.26450,    0.83644,    0.22867,    0.90069} },{
	{ 5, 2, 2, 0,"zImuon+zIkaon"                 ,   11.24646,    0.75437,    0.23468,    0.83627},
	{ 5, 2, 2, 1,"zOmuon+zOkaon"                 ,   10.95914,    0.83774,    0.22782,    0.90171} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 5, 3, 0, 0,"zImuonN+zIelectronN"           ,   10.55889,    0.68828,    0.23102,    0.82620},
	{ 5, 3, 0, 1,"zOmuonN+zOelectronN"           ,   10.26777,    0.76840,    0.22698,    0.91332} },{
	{ 5, 3, 1, 0,"zImuonP+zIelectronP"           ,   10.55012,    0.68535,    0.23512,    0.83595},
	{ 5, 3, 1, 1,"zOmuonP+zOelectronP"           ,   10.26374,    0.76570,    0.23030,    0.92331} },{
	{ 5, 3, 2, 0,"zImuon+zIelectron"             ,   11.24747,    0.68819,    0.23401,    0.83689},
	{ 5, 3, 2, 1,"zOmuon+zOelectron"             ,   10.95894,    0.76828,    0.22947,    0.92557} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 5, 4, 0, 0,""                              ,    0.00000,    0.00000,    0.00000,    0.00000},
	{ 5, 4, 0, 1,""                              ,    0.00000,    0.00000,    0.00000,    0.00000} },{
	{ 5, 4, 1, 0,"zImuonP+zIdeuteronP"           ,   10.54118,    2.07672,    0.15731,    1.30000},
	{ 5, 4, 1, 1,"zOmuonP+zOdeuteronP"           ,   10.24482,    2.10209,    0.12281,    1.30000} },{
	{ 5, 4, 2, 0,"zImuon+zIdeuteron"             ,   11.23840,    2.07704,    0.15715,    1.30000},
	{ 5, 4, 2, 1,"zOmuon+zOdeuteron"             ,   10.93962,    2.10251,    0.12262,    1.30000} }},
    {{ // particle, norml, mu, sigma, alpha
	{ 5, 5, 0, 0,"zImuonN+zImuonN"               ,   10.55969,    0.52904,    0.23398,    0.76586},
	{ 5, 5, 0, 1,"zOmuonN+zOmuonN"               ,   10.26928,    0.59728,    0.23943,    0.88069} },{
	{ 5, 5, 1, 0,"zImuonP+zImuonP"               ,   10.55160,    0.52614,    0.24006,    0.78633},
	{ 5, 5, 1, 1,"zOmuonP+zOmuonP"               ,   10.26561,    0.59182,    0.24087,    0.87613} },{
	{ 5, 5, 2, 0,"zImuon+zImuon"                 ,   11.24874,    0.52811,    0.23712,    0.77990},
	{ 5, 5, 2, 1,"zOmuon+zOmuon"                 ,   10.96093,    0.59527,    0.24109,    0.88271} }},
  };
#ifdef __ELOSS__  
  /*
    bgL10min Tcut            bgL10MIP     bg  log(beta)                 dN/dx    scale = -1.13000e-01; alpha = 1.13000e-01/9.27077905202451547e+01 = 1.21888354113372510e-03
    scale = 1/(1 +alpha*dNdx) - 1 
    
    minimu log10(p/m) alpga    -0.7   40 keV          -0.850  0.141 -1.96883836551568292e+00  3.45122406159667935e+03  -0.807
    He3      -0.7   40              -0.727  0.187 -1.69383239941652541e+00  2.13316907245180437e+03  -0.722
    deuteron -1.0    1 keV          -0.552  0.280 -1.31070490640084025e+00  2.70689788452519849e+02  -0.248
    proton   -1.0    1 keV          -0.251  0.561 -7.14846611368781581e-01  9.27077905202451547e+01  -0.101
    kaon     -0.5  100 keV           0.027  1.064 -3.16517375796772749e-01  4.48350287856880172e+01
    pion     -0.4  100 keV  bgL10 =  0.576  3.767 -3.40492423408368661e-02  2.97372112287192998e+01
    e         2.0  100 keV           3.012  1028. -4.73133358730884409e-07  4.03895078708591129e+01
    
  */
  //                                    pi+           p        K+             e+          d       mu+        t      He3     alpha
  static Double_t dNdxMIP[9] = {    29.7388,    93.6498,  45.0091,       40.3891,    273.02,  29.9792, 539.102, 2156.38,  3486.43};
  const Double_t  Masses[9]  = { 0.13956995, 0.93827231, 01.493677, 0.51099907e-3, 0.1056584, 1.875613, 2.80925, 2.80923, 3.727417};
#endif /* __ELOSS__  */
  static Double_t MuShiftIO[3] = {-7.98670e-02, 6.43941e-03, 0}; // Aerage for sectors for 7p7GeV_2021
  Double_t Value = 0;
  Int_t icase = (Int_t) par[12];
  Int_t i1 = 0;
  Int_t i2 = Npart4EY - 1;
  if (icase >= 0) {i1 = i2 = icase;}
  TF1 *g = GausExp();
  static Int_t _debug = 0;
  for (Int_t i = i1; i <= i2; i++) { 
    if (frac[i] <= 0.0) continue;
#ifdef __SCALE__
    //    Double_t Mu = (mu + parMIPs[i][sign][IO].mu - parMIPs[0][sign][IO].mu)/(scale + MuShiftIO[IO]);
    Double_t Mu = (mu + parMIPs[i][sign][IO].mu - parMIPs[0][0][IO].mu)/(scale + MuShiftIO[IO]);
    Double_t Sigma =                  (parMIPs[i][sign][IO].sigma + sigma)/(scale + MuShiftIO[IO]);
#else
    Double_t Mu =    (mu    + parMIPs[i][sign][IO].mu - parMIPs[0][sign][IO].mu);
    //    Double_t Sigma = (sigma + parMIPs[i][sign][IO].sigma                       );
    //    Double_t Sigma = TMath::Sqrt(sigma*sigma + parMIPs[i][sign][IO].sigma*parMIPs[i][sign][IO].sigma                       );
    Double_t sigmaF = sigma*TMath::Exp(Mu-XX[0]);
    Double_t Sigma = TMath::Sqrt(sigmaF*sigmaF + parMIPs[i][sign][IO].sigma*parMIPs[i][sign][IO].sigma                       );
#endif
#ifdef __ELOSS__ 
    Double_t eps = dNdxMIP[i]/dNdxMIP[0] - 1;
    Double_t dMu = eps*eLoss*TMath::Exp(XX[0]);
    if (dMu > 0.1) dMu = 0.1;
    Mu += dMu;
#endif
    //    Double_t pars[4] = {0, Mu, parMIPs[i][sign][IO].sigma*(1 + sigma), parMIPs[i][sign][IO].alpha};
    Double_t pars[4] = {0, Mu, Sigma, parMIPs[i][sign][IO].alpha};
    Value += frac[i]*g->EvalPar(XX, pars);
    if (_debug) {
      cout << "i: " << i << " " << parMIPs[i][sign][IO].Name << " frac[" << i <<"] = " << frac[i] << "\t"; parMIPs[i][sign][IO].Print("",pars);
    }
  }
  if (occupancy > 0) {
    Double_t overlap = 0;
    for (Int_t i = i1; i <= i2; i++) { 
      if (frac[i] <= 0.0) continue;
      Double_t cont = 0;
      for (Int_t j = 0; j < Npart4EY; j++) {
	if (frac[j] <= 0.0) continue;
	Int_t l = (i <= j) ? i + j*(j+1)/2 : j + i*(i+1)/2;
	l += Npart4EY;
	//	Double_t Mu =    (mu    + parMIPs[l][sign][IO].mu     - parMIPs[0][sign][IO].mu)/(scale + MuShiftIO[IO]);
#ifdef __SCALE__
	Double_t Mu =    (mu    + parMIPs[l][sign][IO].mu     - parMIPs[0][0][IO].mu)/(scale + MuShiftIO[IO]);
	Double_t Sigma = (sigma + parMIPs[l][sign][IO].sigma                           )/(scale + MuShiftIO[IO]);
#else
	Double_t Mu =    (mu    + parMIPs[l][sign][IO].mu     - parMIPs[0][sign][IO].mu);
	//	Double_t Sigma = (sigma + parMIPs[l][sign][IO].sigma                            );
	Double_t Sigma = TMath::Sqrt(sigma*sigma + parMIPs[l][sign][IO].sigma*parMIPs[l][sign][IO].sigma);
#endif
	Double_t pars[4] = {0, Mu, Sigma, parMIPs[l][sign][IO].alpha};
	cont += frac[j]*g->EvalPar(XX, pars);
	if (_debug) {
	  cout << "i:" << i << " " << parMIPs[i][sign][IO].Name << "\t+ j:" << j << " " 
	       <<  parMIPs[j][sign][IO].Name << "\t frac[" << j <<"] = " << frac[j] 
	       << "\t l:" << l << " "; parMIPs[l][sign][IO].Print("",pars);
	}
      }
      overlap += frac[i]*cont;
    }
    Value += occupancy*overlap;
  }
  if (fgITH1)         Value *= fgITH1->Interpolate(XX[0]);
  else if (RMS20 > 0) Value *= TMath::Freq((XX[0]-mean20)/RMS20);
  return par[11]*TMath::Exp(par[0])*Value;
}
//________________________________________________________________________________
Bool_t  PreSetParametersY(TH1 *proj, TF1 *g2) { // Fit peak nearest to 0 by gaus
  if (! proj || ! g2) return kFALSE;
  static TSpectrum *fSpectrum = 0;
  if (! fSpectrum) {
    fSpectrum = new TSpectrum(6);
  }
  // Find pion peak
  Int_t nfound = fSpectrum->Search(proj);
  Int_t NN = nfound + 1;
#if  ROOT_VERSION_CODE < ROOT_VERSION(6,0,0)
  TArrayF X(NN,fSpectrum->GetPositionX());
  TArrayF Y(NN,fSpectrum->GetPositionY());
#else
  TArrayD X(NN,fSpectrum->GetPositionX());
  TArrayD Y(NN,fSpectrum->GetPositionY());
#endif
  TArrayI idxT(NN);
  Int_t nP = 0;
  //                             pi,        proton,          kaon,             e,     deuteron, 
  Double_t frac[5] = {           1.,          1e-6,          1e-6,          1e-6,          1e-6};
  Double_t post[5] = {Peaks[0].peak, Peaks[1].peak, Peaks[2].peak, Peaks[3].peak, Peaks[4].peak};
  Double_t T = 0;
  Double_t tots[5] = {0};
  Double_t xpiPd[3] = {0};
  Double_t ypiPd[3] = {0};
  Double_t ppiPd[3] = {Peaks[0].peak, Peaks[1].peak, Peaks[4].peak};
  Double_t shift = 0;
  Double_t total = 0;
  if (nfound > 0) {
    TMath::Sort(nfound,X.GetArray(),idxT.GetArray(),kFALSE);
    for (Int_t i = 0; i < nfound; i++) {
      Int_t p = idxT[i];
      Double_t xp = X[p];
      Int_t bin = proj->GetXaxis()->FindBin(xp);
      Double_t yp = proj->GetBinContent(bin);
      Double_t ep = proj->GetBinError(bin);
      if (yp-5*ep < 0) continue;
      if (nP > 0) {
	if (TMath::Abs(xpiPd[nP-1] - xp) < 0.1*(Peaks[1].peak - Peaks[0].peak)) {
	  xpiPd[nP-1] = 0.5*(xpiPd[nP-1] + xp);
	  ypiPd[nP-1] = 0.5*(ypiPd[nP-1] + yp);
	  continue;
	}
      }
      // take only peak associated with pion, proton and deuteron
      xpiPd[nP] = xp;
      ypiPd[nP] = yp;
      total += yp;
      shift += (xp - ppiPd[nP])*yp; 
      nP++;
      if (nP == 3) break;
    }
    // swap pion and proton peaks
    Int_t i0 = proj->FindFirstBinAbove(1);
    Double_t x0 = proj->GetXaxis()->GetBinCenter(i0);
    if (nP == 1) {// pion peak is missing ?
      if (xpiPd[0] - x0 > 2.5) {
	xpiPd[nP] = xpiPd[0];
	ypiPd[nP] = ypiPd[0];
	xpiPd[0]  = xpiPd[0] - Peaks[1].peak + Peaks[0].peak;
	ypiPd[0]  = 0.1*ypiPd[0];
	nP++;
      }
    } 
  }   
  if (nP > 0) {
    tots[0] = ypiPd[0];
    tots[1] = ypiPd[1];
    tots[5] = ypiPd[2];
    shift = shift/total;
    Double_t xpi = xpiPd[0]; // ppiPd[0] + shift;
    g2->SetParameter(1, xpi);
    g2->SetParLimits(1, xpi-0.5,xpi+0.5);
    for (Int_t l = 1; l < 5; l++) {
      if (tots[l] > 0) {
	frac[l] = tots[l]/total;
      }
      Double_t phi = TMath::ASin(TMath::Sqrt(frac[l]));
      g2->FixParameter(l+2, phi);
    }
  } else {// nP == 0 
    g2->SetParameters(1, proj->GetMean());
  }
  g2->SetParameter(2, 0.01);
  total = proj->Integral()*proj->GetBinWidth(5);
  g2->FixParameter(11, total);
  return kTRUE;
}
//________________________________________________________________________________
TF1 *FitG4EY(TH1D *proj, Option_t *opt, Int_t IO, Int_t Sign, Double_t mean20, Double_t RMS20) {
  // fit in momentum range p = 0.526 +/- 0.05;
  if (! proj) return 0;
  TString Opt(opt);
  //  Bool_t quet = Opt.Contains("Q",TString::kIgnoreCase);
  TF1 *g2 = (TF1*) gROOT->GetFunction("G4EY");
  if (! g2) {
    g2 = new TF1("G4EY",gf4EYFunc, -5, 5, 18);
    g2->SetParName(0,"norm");      g2->SetParLimits(0,-0.6,0.6); // g2->FixParameter(0,0.0); // 
    g2->SetParName(1,"mu");        g2->SetParLimits(1,-2.6,0.6); // g2->SetParLimits(1,-1.2,1.6);  				     
    g2->SetParName(2,"Sigma");     g2->SetParLimits(2, 0.0,0.2); // g2->FixParameter(2,0.0); // 	     
    g2->SetParName(3,"P");         g2->SetParLimits(3,0.0,TMath::Pi()/2);		     
    g2->SetParName(4,"K");         g2->SetParLimits(4,0.0,0.25);// TMath::Pi()/2); 	     
    g2->SetParName(5,"e");         g2->SetParLimits(5,0.0,0.25);//TMath::Pi()/2);			     
    g2->SetParName(6,"d");         g2->FixParameter(6,0.0); //g2->SetParLimits(6,0.0, 1.0); // TMath::Pi()/2);             
    g2->SetParName(7,"muon");      g2->FixParameter(7,0.0); //g2->SetParLimits(7,0.0, 1.0); // TMath::Pi()/2);             
    g2->SetParName(8,"triton");    g2->FixParameter(8,0.0); //g2->SetParLimits(8,0.0, 1.0); // TMath::Pi()/2);             
    g2->SetParName(9,"He3");       g2->FixParameter(9,0.0); //g2->SetParLimits(9,0.0, 1.0); // TMath::Pi()/2);             
    g2->SetParName(10,"alpha");    g2->FixParameter(10,0.0); //g2->SetParLimits(10,0.0, 1.0); // TMath::Pi()/2);             
    g2->SetParName(11,"Total");
    g2->SetParName(12,"Case");
    g2->SetParName(13,"occupancy");g2->FixParameter(13,0); //g2->SetParLimits(13,0.0,0.25);
    g2->SetParName(14,"IO");       g2->FixParameter(14,IO); 
    g2->SetParName(15,"sign");     g2->FixParameter(15,Sign); 
    if (RMS20 > 0) {
      g2->SetParName(16,"mean20");     g2->FixParameter(16,mean20); 
    } else {
#ifdef __ELOSS__
      g2->SetParName(16,"eLoss"); g2->FixParameter(16,0.0); g2->SetParLimits(16,-0.01,0.01);
#else /* ! __ELOSS__ */
#ifdef __SCALE__
      g2->SetParName(16,"Scale"); g2->FixParameter(16,0.0); g2->SetParLimits(16,-0.5,0.5);
#else /* ! __ELOSS__ && ! __SCALE__ */
      g2->SetParName(16,"Dummy"); g2->FixParameter(16,0.0); 
#endif /* __SCALE__ */
#endif /* __ELOSS__ */
      //    g2->SetParName(15,"factor"); g2->SetParLimits(15,-.1,0.1);
    }
    g2->SetParName(17,"RMS20");      g2->FixParameter(17,RMS20); 
  }
  PreSetParametersY(proj, g2);
  //  g2->ReleaseParameter(2);  g2->SetParLimits(2,-0.1,0.1);
  //#define PIONS_ONLY
#ifndef PIONS_ONLY
  g2->ReleaseParameter(3); // g2->SetParLimits(3,0.0,TMath::Pi()/2);
#endif
  g2->FixParameter(4,0.01); 
  g2->FixParameter(5,0.01);
  g2->FixParameter(6,0.00);
  g2->FixParameter(7,0.00);
  g2->FixParameter(8,0.00);
  g2->FixParameter(9,0.00);
  g2->FixParameter(10,0.0);
  g2->FixParameter(12,-1);
  g2->FixParameter(13,0.);
  g2->FixParameter(14,IO); 
  g2->FixParameter(15,Sign); 
  g2->FixParameter(16,mean20); 
  g2->FixParameter(17,RMS20); 
  //  Fit pion + proton 
  Int_t iok = proj->Fit(g2,Opt.Data());
#ifndef PIONS_ONLY
  //  g2->ReleaseParameter(2);
  g2->ReleaseParameter(4);     g2->SetParLimits(4,0.0,0.25); // ,TMath::Pi()/2); 
  g2->ReleaseParameter(5);     g2->SetParLimits(5,0.0,0.25); // ,TMath::Pi()/2);	
  if (Sign > 0) {
    g2->ReleaseParameter(6);     g2->SetParLimits(6,0.0,0.25); // ,TMath::Pi()/2);
  }
  //  Fit pion + proton + K + e + d
  iok = proj->Fit(g2,Opt.Data());
  if ( iok < 0) {
    cout << g2->GetName() << " fit has failed with " << iok << " for " 
	 << proj->GetName() << "/" << proj->GetTitle() << " Try one again" << endl; 
    proj->Fit(g2,Opt.Data());
  }
#if defined(__ELOSS__) || defined(__SCALE__)
  g2->ReleaseParameter(16); g2->SetParLimits(16,-0.5,0.5);
  iok = proj->Fit(g2,Opt.Data());
#endif
  //  g2->ReleaseParameter(7);     g2->SetParLimits(4,0.0,0.6); // TMath::Pi()/2); 
  //  g2->ReleaseParameter(8);     g2->SetParLimits(8,0.0,TMath::Pi()/2);		
  //  g2->ReleaseParameter(9);     g2->SetParLimits(6,0.0, 1.0); // TMath::Pi()/2);
  //  g2->ReleaseParameter(10);     g2->SetParLimits(6,0.0, 1.0); // TMath::Pi()/2);
  //  Fit pion + proton + K + e + d + mu + triton // + He3 + alpha
  //  iok = proj->Fit(g2,Opt.Data());
  // + occupancy
#ifdef __OCCUPANCY__
  g2->ReleaseParameter(13); g2->SetParLimits(13,0.0,0.15);
  iok = proj->Fit(g2,Opt.Data());
  if ( iok < 0) {
    cout << g2->GetName() << " fit has failed with " << iok << " for " 
	 << proj->GetName() << "/" << proj->GetTitle() << " Try one again" << endl; 
    proj->Fit(g2,Opt.Data());
  }
#endif
#endif /* ! PIONS_ONLY */
  Opt += "m";
  iok = proj->Fit(g2,Opt.Data());
  if (iok < 0 ) return 0;
  Int_t fixit = 0;
  for (Int_t p = 3; p <= 10; p++) {
    Double_t par = g2->GetParameter(p);
    if (par != 0) {
      Double_t dpar = g2->GetParError(p);
      if (TMath::Abs(par) < dpar) {
	fixit++;
	g2->FixParameter(p, 0);
      }
    }
  }
  if (fixit) iok = proj->Fit(g2,Opt.Data());
  if (! Opt.Contains("q",TString::kIgnoreCase)) {
    Double_t params[20];
    g2->GetParameters(params);
    Double_t X = params[1];
    Double_t Y = TMath::Exp(params[0]);
    TPolyMarker *pm = new TPolyMarker(1, &X, &Y);
    proj->GetListOfFunctions()->Add(pm);
    pm->SetMarkerStyle(23);
    pm->SetMarkerColor(kRed);
    pm->SetMarkerSize(1.3);
    Double_t occupancy = params[13];
    for (int i = 0; i < Npart4EY; i++) {
      Double_t frac = 1.0;
      if (i > 0) frac = TMath::Power(TMath::Sin(g2->GetParameter(2+i)), 2);
      if (frac < 1e-3) continue;
      TF1 *f = new TF1(*g2);
      static const Char_t *pnames[9] = {"pion", "P", "K", "e", "d", "muon", "t", "He3", "alpha"};
      f->SetName(pnames[i]);
      f->FixParameter(12,i);
      f->SetLineColor(i+2);
      proj->GetListOfFunctions()->Add(f);
      if (occupancy > 0) {
	TF1 *f = new TF1(*g2);
	f->SetName(TString(Peaks[i].Name)+"C");
	f->FixParameter(12,i);
	f->FixParameter(13,0);
	f->SetLineColor(i+2);
	f->SetLineStyle(2);
	proj->GetListOfFunctions()->Add(f);
      }
    }
    proj->Draw();
  }
  return g2;
}
//________________________________________________________________________________
// Make Histogram from Integral of hist
TH1D *ITH1(TH1D *hist) {
  if (! hist) return 0;
  TH1D *ihist = new TH1D(*hist);
  ihist->SetName(Form("I%s",hist->GetName()));
  Int_t nbinsx = ihist->GetNbinsX();
  Double_t *Integral = hist->GetIntegral();
  for (Int_t i = 0; i <= nbinsx+1; i++) {
    ihist->SetBinContent(i,Integral[i]);
  }
  return ihist;
}
//________________________________________________________________________________
TF1 *FitG4EY(TH1D *proj, Option_t *opt="RM", Int_t IO = 0, Int_t Sign = 2, TH1D *proj20 = 0) {
  Double_t mean20 = 0;
  Double_t RMS20 = -1;
  if (proj20) {
    proj20->Fit("gaus");
    TF1 *gaus = (TF1 *) proj20->GetListOfFunctions()->FindObject("gaus");
    if (gaus) {
      mean20 = gaus->GetParameter(1);
      RMS20  = gaus->GetParameter(2);
    }
    SafeDelete(fgITH1);
    fgITH1 = ITH1(proj20);
  }
  return FitG4EY(proj,opt,IO,Sign,mean20,RMS20);
}
