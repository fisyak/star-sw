#ifndef __GePiD__
#define __GePiD__
struct Gpart_t {
  Int_t Id;
  const Char_t *Name;
  Int_t opt;
  Double_t Mass;
  Double_t Charge;
  Double_t lifetime;
  void Print() {cout << Id << "\t" << Name << "\t" << opt << "\t" << Mass << "\t" << Charge << "\t" << lifetime << endl;}
};
static  Gpart_t Parts[173] = {
  {1, "GAMMA",                      1,       0.0000E+00,     0.,    0.10000E+16},
  {2, "POSITRON",                   2,       0.5110E-03,     1.,    0.10000E+16},
  {3, "ELECTRON",                   2,       0.5110E-03,    -1.,    0.10000E+16},
  {4, "NEUTRINO",                   3,       0.0000E+00,     0.,    0.10000E+16},
  {5, "MUON+",                      5,       0.1057E+00,     1.,    0.21970E-05},
  {6, "MUON-",                      5,       0.1057E+00,    -1.,    0.21970E-05},
  {7, "PION0",                      3,       0.1350E+00,     0.,    0.84000E-16},
  {8, "PION+",                      4,       0.1396E+00,     1.,    0.26030E-07},
  {9, "PION-",                      4,       0.1396E+00,    -1.,    0.26030E-07},
  {10, "KAON0_LONG",                3,       0.4977E+00,     0.,    0.51700E-07},
  {11, "KAON+",                     4,       0.4937E+00,     1.,    0.12370E-07},
  {12, "KAON-",                     4,       0.4937E+00,    -1.,    0.12370E-07},
  {13, "NEUTRON",                   3,       0.9396E+00,     0.,    0.88700E+03},
  {14, "PROTON",                    4,       0.9383E+00,     1.,    0.10000E+16},
  {15, "ANTIPROTON",                4,       0.9383E+00,    -1.,    0.10000E+16},
  {16, "KAON0_SHORT",               3,       0.4977E+00,     0.,    0.89260E-10},
  {17, "ETA",                       3,       0.5475E+00,     0.,    0.54850E-18},
  {18, "LAMBDA",                    3,       0.1116E+01,     0.,    0.26320E-09},
  {19, "SIGMA+",                    4,       0.1189E+01,     1.,    0.79900E-10},
  {20, "SIGMA0",                    3,       0.1193E+01,     0.,    0.74000E-19},
  {21, "SIGMA-",                    4,       0.1197E+01,    -1.,    0.14790E-09},
  {22, "XI0",                       3,       0.1315E+01,     0.,    0.29000E-09},
  {23, "XI-",                       4,       0.1321E+01,    -1.,    0.16390E-09},
  {24, "OMEGA-",                    4,       0.1672E+01,    -1.,    0.82200E-10},
  {25, "ANTINEUTRON",               3,       0.9396E+00,     0.,    0.88700E+03},
  {26, "ANTILAMBDA",                3,       0.1116E+01,     0.,    0.26320E-09},
  {27, "ANTISIGMA-",                4,       0.1189E+01,    -1.,    0.79900E-10},
  {28, "ANTISIGMA0",                3,       0.1193E+01,     0.,    0.74000E-19},
  {29, "ANTISIGMA+",                4,       0.1197E+01,     1.,    0.14790E-09},
  {30, "ANTIXI0",                   3,       0.1315E+01,     0.,    0.29000E-09},
  {31, "ANTIXI+",                   4,       0.1321E+01,     1.,    0.16390E-09},
  {32, "ANTIOMEGA+",                4,       0.1672E+01,     1.,    0.82200E-10},
  {33, "OMEGA(782)",                3,       0.7820E+00,     0.,    0.78360E-22},
  {34, "PHI(1020)",                 3,       0.1019E+01,     0.,    0.14860E-21},
  {35, "D+",                        4,       0.1869E+01,     1.,    0.10400E-11},
  {36, "D-",                        4,       0.1869E+01,    -1.,    0.10400E-11},
  {37, "D0",                        3,       0.1865E+01,     0.,    0.41500E-12},
  {38, "ANTID0",                    3,       0.1865E+01,     0.,    0.41500E-12},
  {39, "",                          0,                0,     0,               0},
  {40, "",                          0,                0,     0,               0},
  {41, "",                          0,                0,     0,               0},
  {42, "RHO+",                      4,       0.7680E+00,     1.,    0.43530E-23},
  {43, "RHO-",                      4,       0.7680E+00,    -1.,    0.43530E-23},
  {44, "RHO0",                      3,       0.7680E+00,     0.,    0.43530E-23},
  {45, "DEUTERON",                  8,       0.1876E+01,     1.,    0.10000E+16},
  {46, "TRITON",                    8,       0.2809E+01,     1.,    0.10000E+16},
  {47, "ALPHA",                     8,       0.3727E+01,     2.,    0.10000E+16},
  {48, "GEANTINO",                  6,       0.0000E+00,     0.,    0.10000E+16},
  {49, "HE3",                       8,       0.2809E+01,     2.,    0.10000E+16},
  {50, "Cerenkov",                  7,       0.0000E+00,     0.,    0.10000E+16},
  {51, "FeedbackPhoton",            7,       0.0000E+00,     0.,    0.10000E+21},
  {52, "Lambda_c+",                 4,       0.2286E+01,     1.,    0.20600E-12},
  {53, "Lambda_c-",                 4,       0.2286E+01,    -1.,    0.20600E-12},
  {54, "D_s+",                      4,       0.1968E+01,     1.,    0.49000E-12},
  {55, "D_s-",                      4,       0.1968E+01,    -1.,    0.49000E-12},
  {56, "Tau+",                      5,       0.1777E+01,     1.,    0.29060E-12},
  {57, "Tau-",                      5,       0.1777E+01,    -1.,    0.29060E-12},
  {58, "B0",                        3,       0.5279E+01,     0.,    0.15320E-11},
  {59, "B0bar",                     4,       0.5279E+01,    -0.,    0.15320E-11},
  {60, "B+",                        4,       0.5279E+01,     1.,    0.16380E-11},
  {61, "B-",                        4,       0.5279E+01,    -1.,    0.16380E-11},
  {62, "Bs",                        4,       0.5367E+01,     0.,    0.14660E-11},
  {63, "Bsbar",                     3,       0.5367E+01,    -0.,    0.14660E-11},
  {64, "Lambda_b",                  4,       0.5624E+01,     0.,    0.12400E-11},
  {65, "Lambda_bbar",               3,       0.5624E+01,    -0.,    0.12400E-11},
  {66, "J/Psi",                     3,       0.3097E+01,     0.,    0.76000E-20},
  {67, "PsiPrime",                  3,       0.3686E+01,     0.,    0.00000E+00},
  {68, "Upsilon(1S)",               4,       0.9460E+01,     0.,    0.12185E-19},
  {69, "Upsilon(2S)",               4,       0.1002E+02,     0.,    0.20582E-19},
  {70, "Upsilon(3S)",               4,       0.1036E+02,     0.,    0.32392E-19},
  {71, "AntiNeutrino(e)",           3,       0.0000E+00,     0.,    0.10000E+21},
  {72, "Neutrino(mu)",              3,       0.0000E+00,     0.,    0.10000E+21},
  {73, "AntiNeutrino(mu)",          3,       0.0000E+00,     0.,    0.10000E+21},
  {74, "Neutrino(tau)",             3,       0.0000E+00,     0.,    0.10000E+21},
  {75, "AntiNeutrino(tau)",         3,       0.0000E+00,     0.,    0.10000E+21},
  {76, "Sigma*+",                   4,       0.1383E+01,     1.,    0.18386E-22},
  {77, "Sigma*-",                   4,       0.1387E+01,    -1.,    0.16706E-22},
  {78, "Delta-",                    4,       0.1232E+01,    -1.,    0.54851E-23},
  {79, "Delta0",                    4,       0.1232E+01,     0.,    0.54851E-23},
  {80, "Delta+",                    4,       0.1232E+01,     1.,    0.54851E-23},
  {81, "Delta++",                   4,       0.1232E+01,     2.,    0.54851E-23},
  {82, "Delta-_bar",                4,       0.1232E+01,     1.,    0.54851E-23},
  {83, "Delta0_bar",                4,       0.1232E+01,    -0.,    0.54851E-23},
  {84, "Delta+_bar",                4,       0.1232E+01,    -1.,    0.54851E-23},
  {85, "Delta--",                   4,       0.1232E+01,    -2.,    0.54851E-23},
  {86, "Xi*-",                      4,       0.1535E+01,    -1.,    0.66486E-22},
  {87, "Xi*+",                      4,       0.1535E+01,     1.,    0.66486E-22},
  {88, "Xi*0",                      4,       0.1532E+01,     0.,    0.72331E-22},
  {89, "Xi*0_bar",                  4,       0.1532E+01,    -0.,    0.72331E-22},
  {90, "Lambda0R",                  3,       0.1116E+01,     0.,    0.26320E-19},
  {91, "AntiLambda0R",              3,       0.1116E+01,    -0.,    0.26320E-19},
  {92, "AntiDEUTERON",              8,       0.1876E+01,    -1.,    0.10000E+21},
  {93, "AntiTRITON",                8,       0.2809E+01,    -1.,    0.10000E+21},
  {94, "AntiALPHA",                 8,       0.3727E+01,    -2.,    0.10000E+21},
  {95, "AntiHE3",                   8,       0.2808E+01,    -2.,    0.10000E+21},
  {96, "He3r",                      4,       0.2819E+01,     2.,    0.32911E-20},
  {97, "AntiHe3r",                  4,       0.2819E+01,    -2.,    0.32911E-20},
  {98, "HE6",                       8,       0.5606E+01,     2.,    0.10000E+21},
  {99, "AntiHE6",                   8,       0.5606E+01,    -2.,    0.10000E+21},
  {100, "Li5",                      4,       0.4668E+01,     3.,    0.30413E-21},
  {101, "AntiLi5",                  4,       0.4668E+01,    -3.,    0.30413E-21},
  {102, "Li6",                      8,       0.5602E+01,     3.,    0.10000E+21},
  {103, "AntiLi6",                  8,       0.5602E+01,    -3.,    0.10000E+21},
  {104, "Li7",                      8,       0.6534E+01,     3.,    0.10000E+21},
  {105, "AntiLi7",                  8,       0.6534E+01,    -3.,    0.10000E+21},
  {106, "Be7",                      8,       0.6534E+01,     4.,    0.10000E+21},
  {107, "AntiBe7",                  8,       0.6534E+01,    -4.,    0.10000E+21},
  {108, "Be9",                      8,       0.8395E+01,     4.,    0.10000E+21},
  {109, "AntiBe9",                  8,       0.8395E+01,    -4.,    0.10000E+21},
  {110, "Be10",                     8,       0.9328E+01,     4.,    0.10000E+21},
  {111, "AntiBe10",                 8,       0.9328E+01,    -4.,    0.10000E+21},
  {112, "B11",                      8,       0.1027E+02,     5.,    0.10000E+21},
  {113, "AntiB11",                  8,       0.1027E+02,    -5.,    0.10000E+21},
  {114, "LN",                       4,       0.2050E+01,     0.,    0.26320E-09},
  {115, "AntiLN",                   4,       0.2050E+01,    -0.,    0.26320E-09},
  {116, "LNN",                      4,       0.2993E+01,     0.,    0.26320E-09},
  {117, "AntiLNN",                  4,       0.2993E+01,    -0.,    0.26320E-09},
  {118, "H2L",                      4,       0.2055E+01,     1.,    0.26320E-09},
  {119, "AntiH2L",                  4,       0.2055E+01,    -1.,    0.26320E-09},
  {120, "H2Lr",                     4,       0.2055E+01,     1.,    0.26320E-09},
  {121, "AntiH2Lr",                 4,       0.2055E+01,    -1.,    0.26320E-09},
  {122, "H3L",                      4,       0.2991E+01,     1.,    0.26320E-09},
  {123, "AntiH3L",                  4,       0.2991E+01,    -1.,    0.26320E-09},
  {124, "H3Ldp",                    4,       0.2991E+01,     1.,    0.26320E-09},
  {125, "AntiH3Ldp",                4,       0.2991E+01,    -1.,    0.26320E-09},
  {126, "H3Lr",                     4,       0.2991E+01,     1.,    0.26320E-09},
  {127, "AntiH3Lr",                 4,       0.2991E+01,    -1.,    0.26320E-09},
  {128, "H3RL",                     4,       0.2991E+01,     1.,    0.26320E-09},
  {129, "AntiH3RL",                 4,       0.2991E+01,    -1.,    0.26320E-09},
  {130, "H4L",                      4,       0.3922E+01,     1.,    0.26320E-09},
  {131, "AntiH4L",                  4,       0.3922E+01,    -1.,    0.26320E-09},
  {132, "H4Ltp",                    4,       0.3922E+01,     1.,    0.26320E-09},
  {133, "AntiH4Ltp",                4,       0.3922E+01,    -1.,    0.26320E-09},
  {134, "H4L2d",                    4,       0.3922E+01,     1.,    0.26320E-09},
  {135, "AntiH4L2d",                4,       0.3922E+01,    -1.,    0.26320E-09},
  {136, "H5L",                      4,       0.4864E+01,     1.,    0.26320E-09},
  {137, "AntiH5L",                  4,       0.4864E+01,    -1.,    0.26320E-09},
  {138, "H6L",                      4,       0.5770E+01,     1.,    0.26320E-09},
  {139, "AntiH6L",                  4,       0.5770E+01,    -1.,    0.26320E-09},
  {140, "H6L3",                     4,       0.5770E+01,     1.,    0.26320E-09},
  {141, "AntiH6L3",                 4,       0.5770E+01,    -1.,    0.26320E-09},
  {142, "He4L",                     4,       0.3921E+01,     2.,    0.26320E-09},
  {143, "AntiHe4L",                 4,       0.3921E+01,    -2.,    0.26320E-09},
  {144, "He5L",                     4,       0.4839E+01,     2.,    0.26320E-09},
  {145, "AntiHe5L",                 4,       0.4839E+01,    -2.,    0.26320E-09},
  {146, "He5L3",                    4,       0.4839E+01,     2.,    0.26320E-09},
  {147, "AntiHe5L3",                4,       0.4839E+01,    -2.,    0.26320E-09},
  {148, "He5Li5",                   4,       0.4839E+01,     2.,    0.26320E-09},
  {149, "AntiHe5Li5",               4,       0.4839E+01,    -2.,    0.26320E-09},
  {150, "He6L",                     4,       0.5770E+01,     2.,    0.26320E-09},
  {151, "AntiHe6L",                 4,       0.5770E+01,    -2.,    0.26320E-09},
  {152, "He6L3",                    4,       0.5770E+01,     2.,    0.26320E-09},
  {153, "AntiHe6L3",                4,       0.5770E+01,    -2.,    0.26320E-09},
  {154, "He6L3ad",                  4,       0.5770E+01,     2.,    0.26320E-09},
  {155, "AntiHe6L3ad",              4,       0.5770E+01,    -2.,    0.26320E-09},
  {156, "He7L",                     4,       0.6717E+01,     2.,    0.26320E-09},
  {157, "AntiHe7L",                 4,       0.6717E+01,    -2.,    0.26320E-09},
  {158, "He7L3",                    4,       0.6717E+01,     2.,    0.26320E-09},
  {159, "AntiHe7L3",                4,       0.6717E+01,    -2.,    0.26320E-09},
  {160, "Li6L",                     4,       0.5770E+01,     3.,    0.26320E-09},
  {161, "AntiLi6L",                 4,       0.5770E+01,    -3.,    0.26320E-09},
  {162, "Li7L",                     4,       0.6711E+01,     3.,    0.26320E-09},
  {163, "AntiLi7L",                 4,       0.6711E+01,    -3.,    0.26320E-09},
  {164, "Li7L3",                    4,       0.6711E+01,     3.,    0.26320E-09},
  {165, "AntiLi7L3",                4,       0.6711E+01,    -3.,    0.26320E-09},
  {166, "Li8L",                     4,       0.7650E+01,     3.,    0.26320E-09},
  {167, "AntiLi8L",                 4,       0.7650E+01,    -3.,    0.26320E-09},
  {168, "H5LL",                     4,       0.5047E+01,     1.,    0.26320E-09},
  {169, "AntiH5LL",                 4,       0.5047E+01,    -1.,    0.26320E-09},
  {170, "PQ1730LamK0s",             4,       0.1730E+01,     0.,    0.26320E-19},
  {171, "AntiPQ1730LamK0s",         4,       0.1730E+01,    -0.,    0.26320E-19},
  {172, "PQ1730LamK+",              4,       0.1730E+01,     1.,    0.26320E-19},
  {173, "AntiPQ1730LamK+",          4,       0.1730E+01,    -1.,    0.26320E-19}
};
#endif