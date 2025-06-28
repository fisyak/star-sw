TDataSet *CreateTable();
//________________________________________________________________________________
void TopWeight(const Char_t *tag = "y2020") {
  const Double_t lb2kg = 0.45359237;
  //  const Int_t NVolumes = 55;
  //  const Char_t *topVolumeNames[55] = {
  const Char_t *topVolumeNames[] = {
    "HALL","CAVE","PIPE","UPST","SVTT","SFMO","FTPC","SUPO","FTMO",
    "FTCM","BTOF","VPDD","CALB","ECAL","BBCM","FBOX","ZCAL","MAGP","FGMO",
    "PHMD","PXMO","RICH","IBMO","FGMO","GMBO","MGMT","SHLD","MUTD","IGMO",
    "YPXM","ITSP","IBSH","IBSG","IBSF","IBSE","IBSD","IBSC","IBSB","IBSA",
    "IBEM","IBEH","DUMM","ITSP:ITS1","FSMO","TPCE","TPCM","TIFC","TOFC","TPEA",
    "TRDV","TPCW","TWSS","TWGI","TWGI:TWG1",
    "SCON","SCMY","SGRA","SBSP","SAKM","SCKM","SBMM","SBMI","SBMO","SMRD","SBRL","SBRX","SBSR","SBCR","SROD","SROH","SRON","SROI",
    0
  };
  
  if (gClassTable->GetID("TGeoManager") < 0) {
    gSystem->Load("libGeom");
  }
  if (! gGeoManager) {
    TString STAR(gSystem->Getenv("STAR"));
		 gROOT->LoadMacro(Form("%s/StarDb/AgiGeometry/Geometry.%s.C",STAR.Data(),tag));
    CreateTable();
  }
  if (! gGeoManager) return;
  cout << "Geometry " << gGeoManager->GetName() << endl;
  //  for (Int_t i = 0; i < NVolumes; i++) {
  for (Int_t i = 0; topVolumeNames[i]; i++) {
    TGeoVolume *vol = gGeoManager->GetVolume(topVolumeNames[i]);
    if (! vol) continue;
    Double_t WA = vol->Weight();
    cout << vol->GetName() << "\tAnalytical  = " << WA << "[kg]\t" << WA/lb2kg << "[lb]";
#if 1
    Double_t W = vol->Weight(1e-2,"");
    cout << "\tStatistical = " << W << "[kg]\t" << W/lb2kg << "[lb]";
#endif
    cout << endl;
  }
}
/*   
[l409] /net/l402/data/fisyak/STAR/packages/TFG24c $ root.exe -q -b TopWeight.C | grep lb | tee Weight2.txt
Geometry y2019                                                                                          Geometry y2019z												 
HALL    Analytical  = 2.63043e+07[kg]   5.7991e+07[lb]  Statistical = 2.61502e+07[kg]   5.76514e+07[lb]	HALL    Analytical  = 2.63042e+07[kg]   5.79909e+07[lb] Statistical = 2.61598e+07[kg]   5.76726e+07[lb]	 
CAVE    Analytical  = 1.70568e+07[kg]   3.76038e+07[lb] Statistical = 1.70939e+07[kg]   3.76856e+07[lb]	CAVE    Analytical  = 1.70567e+07[kg]   3.76037e+07[lb] Statistical = 1.71033e+07[kg]   3.77062e+07[lb]	 
PIPE    Analytical  = 22.1248[kg]       48.7769[lb]     Statistical = 21.7908[kg]       48.0406[lb]	PIPE    Analytical  = 22.1248[kg]       48.7769[lb]     Statistical = 21.7908[kg]       48.0406[lb]	 
UPST    Analytical  = 11885.7[kg]       26203.6[lb]     Statistical = 11829.7[kg]       26080[lb]	UPST    Analytical  = 11885.7[kg]       26203.6[lb]     Statistical = 11829.7[kg]       26080[lb]	 
BTOF    Analytical  = 3703.05[kg]       8163.82[lb]     Statistical = 3738.67[kg]       8242.35[lb]	BTOF    Analytical  = 3703.05[kg]       8163.82[lb]     Statistical = 3738.67[kg]       8242.35[lb]	 
VPDD    Analytical  = 5.93389[kg]       13.082[lb]      Statistical = 5.87931[kg]       12.9617[lb]	VPDD    Analytical  = 5.93389[kg]       13.082[lb]      Statistical = 5.87931[kg]       12.9617[lb]	 
CALB    Analytical  = 119249[kg]        262898[lb]      Statistical = 119565[kg]        263597[lb]	CALB    Analytical  = 119249[kg]        262898[lb]      Statistical = 119565[kg]        263597[lb]	 
ECAL    Analytical  = 26166.8[kg]       57688[lb]       Statistical = 26274.6[kg]       57925.5[lb]	ECAL    Analytical  = 26152.1[kg]       57655.4[lb]     Statistical = 26294.9[kg]       57970.2[lb]	 
BBCM    Analytical  = 19.1646[kg]       42.2507[lb]     Statistical = 19.2194[kg]       42.3716[lb]	BBCM    Analytical  = 1.14168[kg]       2.51697[lb]     Statistical = 1.13474[kg]       2.50168[lb]	 
ZCAL    Analytical  = 419.814[kg]       925.532[lb]     Statistical = 417.247[kg]       919.872[lb]	ZCAL    Analytical  = 419.814[kg]       925.532[lb]     Statistical = 417.365[kg]       920.132[lb]	 
MAGP    Analytical  = 778401[kg]        1.71608e+06[lb] Statistical = 775053[kg]        1.7087e+06[lb]	MAGP    Analytical  = 778401[kg]        1.71608e+06[lb] Statistical = 777845[kg]        1.71486e+06[lb]	 
SHLD    Analytical  = 65341.4[kg]       144053[lb]      Statistical = 65341.4[kg]       144053[lb]	SHLD    Analytical  = 65341.4[kg]       144053[lb]      Statistical = 65341.4[kg]       144053[lb]	 
MUTD    Analytical  = 387.836[kg]       855.031[lb]     Statistical = 381.089[kg]       840.157[lb]	MUTD    Analytical  = 387.836[kg]       855.031[lb]     Statistical = 381.027[kg]       840.021[lb]	 
IBSH    Analytical  = 0.0514456[kg]     0.113418[lb]    Statistical = 0.0516097[kg]     0.11378[lb]	IBSH    Analytical  = 0.0514456[kg]     0.113418[lb]    Statistical = 0.0515075[kg]     0.113555[lb]	 
IBSG    Analytical  = 0.102891[kg]      0.226836[lb]    Statistical = 0.102991[kg]      0.227057[lb]	IBSG    Analytical  = 0.102891[kg]      0.226836[lb]    Statistical = 0.102803[kg]      0.226642[lb]	 
IBSF    Analytical  = 4.08073[kg]       8.99647[lb]     Statistical = 4.08208[kg]       8.99944[lb]	IBSF    Analytical  = 4.08073[kg]       8.99647[lb]     Statistical = 4.08227[kg]       8.99986[lb]	 
IBSE    Analytical  = 0.134537[kg]      0.296603[lb]    Statistical = 0.134537[kg]      0.296603[lb]	IBSE    Analytical  = 0.134537[kg]      0.296603[lb]    Statistical = 0.134537[kg]      0.296603[lb]	 
IBSD    Analytical  = 0.267561[kg]      0.58987[lb]     Statistical = 0.267561[kg]      0.58987[lb]	IBSD    Analytical  = 0.267561[kg]      0.58987[lb]     Statistical = 0.267561[kg]      0.58987[lb]	 
IBSC    Analytical  = 1.3773[kg]        3.03642[lb]     Statistical = 1.28714[kg]       2.83767[lb]	IBSC    Analytical  = 1.3773[kg]        3.03642[lb]     Statistical = 1.29318[kg]       2.85097[lb]	 
IBSB    Analytical  = 5.5665[kg]        12.272[lb]      Statistical = 5.17306[kg]       11.4046[lb]	IBSB    Analytical  = 5.5665[kg]        12.272[lb]      Statistical = 5.26436[kg]       11.6059[lb]	 
IBSA    Analytical  = 3.28361[kg]       7.23912[lb]     Statistical = 3.09498[kg]       6.82326[lb]	IBSA    Analytical  = 3.28361[kg]       7.23912[lb]     Statistical = 3.09077[kg]       6.81397[lb]	 
IBEM    Analytical  = 11.6868[kg]       25.7649[lb]     Statistical = 11.5289[kg]       25.4168[lb]	IBEM    Analytical  = 11.6868[kg]       25.7649[lb]     Statistical = 11.843[kg]        26.1094[lb]	 
IBEH    Analytical  = 4.46906[kg]       9.8526[lb]      Statistical = 4.46906[kg]       9.8526[lb]	IBEH    Analytical  = 4.46906[kg]       9.8526[lb]      Statistical = 4.46906[kg]       9.8526[lb]	 
TPCE    Analytical  = 6961.14[kg]       15346.7[lb]     Statistical = 5132.4[kg]        11315[lb]	TPCE    Analytical  = 6953.98[kg]       15330.9[lb]     Statistical = 5054.39[kg]       11143[lb]	 
TPCM    Analytical  = 1.25444[kg]       2.76556[lb]     Statistical = 1.25426[kg]       2.76516[lb]	TPCM    Analytical  = 1.25444[kg]       2.76556[lb]     Statistical = 1.25486[kg]       2.76649[lb]	 
TIFC    Analytical  = 64.5094[kg]       142.219[lb]     Statistical = 64.0531[kg]       141.213[lb]	TIFC    Analytical  = 64.5094[kg]       142.219[lb]     Statistical = 63.6324[kg]       140.285[lb]	 
TOFC    Analytical  = 1434.57[kg]       3162.69[lb]     Statistical = 1451.16[kg]       3199.27[lb]	TOFC    Analytical  = 1434.57[kg]       3162.69[lb]     Statistical = 1453.21[kg]       3203.77[lb]	 
																										 
SCON    Analytical  = 18.7847[kg]       41.4132[lb]     Statistical = 18.731[kg]        41.2948[lb]	SCON    Analytical  = 18.7847[kg]       41.4132[lb]     Statistical = 18.7352[kg]       41.3041[lb]	 
SCMY    Analytical  = 5.38041[kg]       11.8618[lb]     Statistical = 5.38272[kg]       11.8669[lb]	SCMY    Analytical  = 5.38041[kg]       11.8618[lb]     Statistical = 5.38173[kg]       11.8647[lb]	 
SGRA    Analytical  = 13.4043[kg]       29.5514[lb]     Statistical = 13.4022[kg]       29.5467[lb]	SGRA    Analytical  = 13.4043[kg]       29.5514[lb]     Statistical = 13.4246[kg]       29.5962[lb]	 
																										 
SBSP    Analytical  = 0.771153[kg]      1.7001[lb]      Statistical = 0.820074[kg]      1.80795[lb]	SBSP    Analytical  = 0.771153[kg]      1.7001[lb]      Statistical = 0.802893[kg]      1.77008[lb]	 
SAKM    Analytical  = 0.647218[kg]      1.42687[lb]     Statistical = 0.680175[kg]      1.49953[lb]	SAKM    Analytical  = 0.647218[kg]      1.42687[lb]     Statistical = 0.680803[kg]      1.50091[lb]	 
SCKM    Analytical  = 0[kg]             0[lb]           Statistical = 0[kg]     0[lb]			SCKM    Analytical  = 0[kg]     0[lb]   Statistical = 0[kg]     0[lb]					 
SBMM    Analytical  = 0.0148457[kg]     0.0327292[lb]   Statistical = 0.0144622[kg]     0.0318837[lb]	SBMM    Analytical  = 0.0148457[kg]     0.0327292[lb]   Statistical = 0.0145212[kg]     0.0320137[lb]	 
SBMI    Analytical  = 0.00664918[kg]    0.0146589[lb]   Statistical = 0.00664918[kg]    0.0146589[lb]	SBMI    Analytical  = 0.00664918[kg]    0.0146589[lb]   Statistical = 0.00664918[kg]    0.0146589[lb]	 
SBMO    Analytical  = 0.00531934[kg]    0.0117271[lb]   Statistical = 0.00531934[kg]    0.0117271[lb]	SBMO    Analytical  = 0.00531934[kg]    0.0117271[lb]   Statistical = 0.00531934[kg]    0.0117271[lb]	 
SMRD    Analytical  = 0.0028772[kg]     0.00634313[lb]  Statistical = 0.00288136[kg]    0.00635231[lb]	SMRD    Analytical  = 0.0028772[kg]     0.00634313[lb]  Statistical = 0.00287406[kg]    0.00633621[lb]	 
SBRL    Analytical  = 0.00155624[kg]    0.00343093[lb]  Statistical = 0.00155235[kg]    0.00342235[lb]	SBRL    Analytical  = 0.00155624[kg]    0.00343093[lb]  Statistical = 0.00155542[kg]    0.00342912[lb]	 
SBRX    Analytical  = 0.001256[kg]      0.002769[lb]    Statistical = 0.0012582[kg]     0.00277385[lb]	SBRX    Analytical  = 0.001256[kg]      0.002769[lb]    Statistical = 0.0012573[kg]     0.00277187[lb]	 
SBSR    Analytical  = 0.0533023[kg]     0.117511[lb]    Statistical = 0.0624558[kg]     0.137691[lb]	SBSR    Analytical  = 0.0533023[kg]     0.117511[lb]    Statistical = 0.0630163[kg]     0.138927[lb]	 
SBCR    Analytical  = 0[kg]             0[lb]           Statistical = 0[kg]     0[lb]			SBCR    Analytical  = 0[kg]     0[lb]   Statistical = 0[kg]     0[lb]					 
SROD    Analytical  = 0.366298[kg]      0.807548[lb]    Statistical = 0.369316[kg]      0.814203[lb]	SROD    Analytical  = 0.366298[kg]      0.807548[lb]    Statistical = 0.36318[kg]       0.800675[lb]	 
SROH    Analytical  = 0[kg]            0[lb]            Statistical = 0[kg]     0[lb]			SROH    Analytical  = 0[kg]     0[lb]   Statistical = 0[kg]     0[lb]					 
SRON    Analytical  = 0.19281[kg]       0.425074[lb]    Statistical = 0.193075[kg]      0.425658[lb]	SRON    Analytical  = 0.19281[kg]       0.425074[lb]    Statistical = 0.194218[kg]      0.428177[lb]	 
SROI    Analytical  = 0.154156[kg]      0.339855[lb]    Statistical = 0.156574[kg]      0.345186[lb]	SROI    Analytical  = 0.154156[kg]      0.339855[lb]    Statistical = 0.15343[kg]       0.338255[lb]     


[l409] /net/l402/data/fisyak/STAR/packages/TFG $ root.exe -q -b 'TopWeight.C("y2019z")'  | grep lb | tee Weight2.txt
Geometry y2019z
HALL    Analytical  = 2.63042e+07[kg]   5.79909e+07[lb] Statistical = 2.61598e+07[kg]   5.76726e+07[lb]
CAVE    Analytical  = 1.70567e+07[kg]   3.76037e+07[lb] Statistical = 1.71033e+07[kg]   3.77062e+07[lb]
PIPE    Analytical  = 22.1248[kg]       48.7769[lb]     Statistical = 21.7908[kg]       48.0406[lb]
UPST    Analytical  = 11885.7[kg]       26203.6[lb]     Statistical = 11829.7[kg]       26080[lb]
BTOF    Analytical  = 3703.05[kg]       8163.82[lb]     Statistical = 3738.67[kg]       8242.35[lb]
VPDD    Analytical  = 5.93389[kg]       13.082[lb]      Statistical = 5.87931[kg]       12.9617[lb]
CALB    Analytical  = 119249[kg]        262898[lb]      Statistical = 119565[kg]        263597[lb]
ECAL    Analytical  = 26152.1[kg]       57655.4[lb]     Statistical = 26294.9[kg]       57970.2[lb]
BBCM    Analytical  = 1.14168[kg]       2.51697[lb]     Statistical = 1.13474[kg]       2.50168[lb]
ZCAL    Analytical  = 419.814[kg]       925.532[lb]     Statistical = 417.365[kg]       920.132[lb]
MAGP    Analytical  = 778401[kg]        1.71608e+06[lb] Statistical = 777845[kg]        1.71486e+06[lb]
SHLD    Analytical  = 65341.4[kg]       144053[lb]      Statistical = 65341.4[kg]       144053[lb]
MUTD    Analytical  = 387.836[kg]       855.031[lb]     Statistical = 381.027[kg]       840.021[lb]
IBSH    Analytical  = 0.0514456[kg]     0.113418[lb]    Statistical = 0.0515075[kg]     0.113555[lb]
IBSG    Analytical  = 0.102891[kg]      0.226836[lb]    Statistical = 0.102803[kg]      0.226642[lb]
IBSF    Analytical  = 4.08073[kg]       8.99647[lb]     Statistical = 4.08227[kg]       8.99986[lb]
IBSE    Analytical  = 0.134537[kg]      0.296603[lb]    Statistical = 0.134537[kg]      0.296603[lb]
IBSD    Analytical  = 0.267561[kg]      0.58987[lb]     Statistical = 0.267561[kg]      0.58987[lb]
IBSC    Analytical  = 1.3773[kg]        3.03642[lb]     Statistical = 1.29318[kg]       2.85097[lb]
IBSB    Analytical  = 5.5665[kg]        12.272[lb]      Statistical = 5.26436[kg]       11.6059[lb]
IBSA    Analytical  = 3.28361[kg]       7.23912[lb]     Statistical = 3.09077[kg]       6.81397[lb]
IBEM    Analytical  = 11.6868[kg]       25.7649[lb]     Statistical = 11.843[kg]        26.1094[lb]
IBEH    Analytical  = 4.46906[kg]       9.8526[lb]      Statistical = 4.46906[kg]       9.8526[lb]
TPCE    Analytical  = 6953.98[kg]       15330.9[lb]     Statistical = 5054.39[kg]       11143[lb]
TPCM    Analytical  = 1.25444[kg]       2.76556[lb]     Statistical = 1.25486[kg]       2.76649[lb]
TIFC    Analytical  = 64.5094[kg]       142.219[lb]     Statistical = 63.6324[kg]       140.285[lb]
TOFC    Analytical  = 1434.57[kg]       3162.69[lb]     Statistical = 1453.21[kg]       3203.77[lb]

SCON    Analytical  = 18.7847[kg]       41.4132[lb]     Statistical = 18.7352[kg]       41.3041[lb]
SCMY    Analytical  = 5.38041[kg]       11.8618[lb]     Statistical = 5.38173[kg]       11.8647[lb]
SGRA    Analytical  = 13.4043[kg]       29.5514[lb]     Statistical = 13.4246[kg]       29.5962[lb]

SBSP    Analytical  = 0.771153[kg]      1.7001[lb]      Statistical = 0.802893[kg]      1.77008[lb]
SAKM    Analytical  = 0.647218[kg]      1.42687[lb]     Statistical = 0.680803[kg]      1.50091[lb]
SCKM    Analytical  = 0[kg]     0[lb]   Statistical = 0[kg]     0[lb]
SBMM    Analytical  = 0.0148457[kg]     0.0327292[lb]   Statistical = 0.0145212[kg]     0.0320137[lb]
SBMI    Analytical  = 0.00664918[kg]    0.0146589[lb]   Statistical = 0.00664918[kg]    0.0146589[lb]
SBMO    Analytical  = 0.00531934[kg]    0.0117271[lb]   Statistical = 0.00531934[kg]    0.0117271[lb]
SMRD    Analytical  = 0.0028772[kg]     0.00634313[lb]  Statistical = 0.00287406[kg]    0.00633621[lb]
SBRL    Analytical  = 0.00155624[kg]    0.00343093[lb]  Statistical = 0.00155542[kg]    0.00342912[lb]
SBRX    Analytical  = 0.001256[kg]      0.002769[lb]    Statistical = 0.0012573[kg]     0.00277187[lb]
SBSR    Analytical  = 0.0533023[kg]     0.117511[lb]    Statistical = 0.0630163[kg]     0.138927[lb]
SBCR    Analytical  = 0[kg]     0[lb]   Statistical = 0[kg]     0[lb]
SROD    Analytical  = 0.366298[kg]      0.807548[lb]    Statistical = 0.36318[kg]       0.800675[lb]
SROH    Analytical  = 0[kg]     0[lb]   Statistical = 0[kg]     0[lb]
SRON    Analytical  = 0.19281[kg]       0.425074[lb]    Statistical = 0.194218[kg]      0.428177[lb]
SROI    Analytical  = 0.154156[kg]      0.339855[lb]    Statistical = 0.15343[kg]       0.338255[lb]          

Geometry y2025z,
HALL    Analytical  = 2.63419e+07[kg]   5.8074e+07[lb]  Statistical = 2.6214e+07[kg]    5.7792e+07[lb]
CAVE    Analytical  = 1.70944e+07[kg]   3.76867e+07[lb] Statistical = 1.71455e+07[kg]   3.77993e+07[lb]
PIPE    Analytical  = 22.1248[kg]       48.7769[lb]     Statistical = 21.7908[kg]       48.0406[lb]
UPST    Analytical  = 11885.7[kg]       26203.6[lb]     Statistical = 11829.7[kg]       26080[lb]
BTOF    Analytical  = 3703.05[kg]       8163.82[lb]     Statistical = 3738.67[kg]       8242.35[lb]
VPDD    Analytical  = 5.93389[kg]       13.082[lb]      Statistical = 5.87931[kg]       12.9617[lb]
CALB    Analytical  = 119249[kg]        262898[lb]      Statistical = 119565[kg]        263597[lb]
ECAL    Analytical  = 26152.1[kg]       57655.4[lb]     Statistical = 26294.9[kg]       57970.2[lb]
BBCM    Analytical  = 1.14168[kg]       2.51697[lb]     Statistical = 1.13474[kg]       2.50168[lb]
ZCAL    Analytical  = 419.814[kg]       925.532[lb]     Statistical = 417.365[kg]       920.132[lb]
MAGP    Analytical  = 778401[kg]        1.71608e+06[lb] Statistical = 777845[kg]        1.71486e+06[lb]
SHLD    Analytical  = 65341.4[kg]       144053[lb]      Statistical = 65341.4[kg]       144053[lb]
MUTD    Analytical  = 387.836[kg]       855.031[lb]     Statistical = 381.027[kg]       840.021[lb]
IBSH    Analytical  = 0.0514456[kg]     0.113418[lb]    Statistical = 0.0515075[kg]     0.113555[lb]
IBSG    Analytical  = 0.102891[kg]      0.226836[lb]    Statistical = 0.102803[kg]      0.226642[lb]
IBSF    Analytical  = 4.08073[kg]       8.99647[lb]     Statistical = 4.08227[kg]       8.99986[lb]
IBSE    Analytical  = 0.134537[kg]      0.296603[lb]    Statistical = 0.134537[kg]      0.296603[lb]
IBSD    Analytical  = 0.267561[kg]      0.58987[lb]     Statistical = 0.267561[kg]      0.58987[lb]
IBSC    Analytical  = 1.3773[kg]        3.03642[lb]     Statistical = 1.29318[kg]       2.85097[lb]
IBSB    Analytical  = 5.5665[kg]        12.272[lb]      Statistical = 5.26436[kg]       11.6059[lb]
IBSA    Analytical  = 3.28361[kg]       7.23912[lb]     Statistical = 3.09077[kg]       6.81397[lb]
IBEM    Analytical  = 11.6868[kg]       25.7649[lb]     Statistical = 11.843[kg]        26.1094[lb]
IBEH    Analytical  = 4.46906[kg]       9.8526[lb]      Statistical = 4.46906[kg]       9.8526[lb]
TPCE    Analytical  = 6953.98[kg]       15330.9[lb]     Statistical = 5054.39[kg]       11143[lb]
TPCM    Analytical  = 1.25444[kg]       2.76556[lb]     Statistical = 1.25486[kg]       2.76649[lb]
TIFC    Analytical  = 64.5094[kg]       142.219[lb]     Statistical = 63.6324[kg]       140.285[lb]
TOFC    Analytical  = 1434.57[kg]       3162.69[lb]     Statistical = 1453.21[kg]       3203.77[lb]

SCON    Analytical  = 18.7847[kg]       41.4132[lb]     Statistical = 18.7352[kg]       41.3041[lb]
SCMY    Analytical  = 5.38041[kg]       11.8618[lb]     Statistical = 5.38173[kg]       11.8647[lb]
SGRA    Analytical  = 13.4043[kg]       29.5514[lb]     Statistical = 13.4246[kg]       29.5962[lb]

SBSP    Analytical  = 0.771153[kg]      1.7001[lb]      Statistical = 0.802893[kg]      1.77008[lb]
SAKM    Analytical  = 0.647218[kg]      1.42687[lb]     Statistical = 0.680803[kg]      1.50091[lb]
SCKM    Analytical  = 0[kg]     0[lb]   Statistical = 0[kg]     0[lb]
SBMM    Analytical  = 0.0148457[kg]     0.0327292[lb]   Statistical = 0.0145212[kg]     0.0320137[lb]
SBMI    Analytical  = 0.00664918[kg]    0.0146589[lb]   Statistical = 0.00664918[kg]    0.0146589[lb]
SBMO    Analytical  = 0.00531934[kg]    0.0117271[lb]   Statistical = 0.00531934[kg]    0.0117271[lb]
SMRD    Analytical  = 0.0028772[kg]     0.00634313[lb]  Statistical = 0.00287406[kg]    0.00633621[lb]
SBRL    Analytical  = 0.00155624[kg]    0.00343093[lb]  Statistical = 0.00155542[kg]    0.00342912[lb]
SBRX    Analytical  = 0.001256[kg]      0.002769[lb]    Statistical = 0.0012573[kg]     0.00277187[lb]
SBSR    Analytical  = 0.0533023[kg]     0.117511[lb]    Statistical = 0.0630163[kg]     0.138927[lb]
SBCR    Analytical  = 0[kg]     0[lb]   Statistical = 0[kg]     0[lb]
SROD    Analytical  = 0.366298[kg]      0.807548[lb]    Statistical = 0.36318[kg]       0.800675[lb]
SROH    Analytical  = 0[kg]     0[lb]   Statistical = 0[kg]     0[lb]
SRON    Analytical  = 0.19281[kg]       0.425074[lb]    Statistical = 0.194218[kg]      0.428177[lb]
SROI    Analytical  = 0.154156[kg]      0.339855[lb]    Statistical = 0.15343[kg]       0.338255[lb]
*/
