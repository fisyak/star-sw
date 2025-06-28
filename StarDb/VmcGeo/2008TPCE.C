void 2008TPCE() {
   gSystem->Load("libGeom");
   new TGeoManager("y2008", "y2008");

   Double_t dx,dy,dz;
   Double_t dx1, dx2, dy1, dy2;
   Double_t vert[20], par[20];
   Double_t theta, phi, h1, bl1, tl1, alpha1, h2, bl2, tl2, alpha2;
   Double_t twist;
   Double_t origin[3];
   Double_t rmin, rmax, rmin1, rmax1, rmin2, rmax2;
   Double_t r, rlo, rhi;
   Double_t phi1, phi2;
   Double_t a,b;
   Double_t point[3], norm[3];
   Double_t rin, stin, rout, stout;
   Double_t thx, phx, thy, phy, thz, phz;
   Double_t alpha, theta1, theta2, phi1, phi2, dphi;
   Double_t tr[3], rot[9];
   Double_t z, density, radl, absl, w;
   Double_t lx,ly,lz,tx,ty,tz;
   Double_t xvert[50], yvert[50];
   Double_t zsect,x0,y0,scale0;
   Int_t nel, numed, nz, nedges, nvert;
   TGeoBoolNode *pBoolNode = 0;

   // MATERIALS, MIXTURES AND TRACKING MEDIA
// Mixture: AIR
   nel     = 4;
   density = 0.001214;
   pMat21 = new TGeoMixture("AIR", nel,density);
      a = 14.010000;   z = 7.000000;   w = 0.749400;  // N
   pMat21->DefineElement(0,a,z,w);
      a = 15.999000;   z = 8.000000;   w = 0.236900;  // O
   pMat21->DefineElement(1,a,z,w);
      a = 39.948000;   z = 18.000000;   w = 0.012900;  // AR
   pMat21->DefineElement(2,a,z,w);
      a = 1.007940;   z = 1.000000;   w = 0.000800;  // H
   pMat21->DefineElement(3,a,z,w);
   pMat21->SetIndex(20);
// Medium: TPCE_STANDARD
   numed   = 0;  // medium number
   par[0]  = 0.000000; // isvol
   par[1]  = 1.000000; // ifield
   par[2]  = 20.000000; // fieldm
   par[3]  = 20.000000; // tmaxfd
   par[4]  = 10.000000; // stemax
   par[5]  = 0.248853; // deemax
   par[6]  = 0.010000; // epsil
   par[7]  = 1.150551; // stmin
   pMed56 = new TGeoMedium("TPCE_STANDARD", numed,pMat21, par);
// Mixture: MYLAR
   nel     = 3;
   density = 1.390000;
   pMat24 = new TGeoMixture("MYLAR", nel,density);
      a = 12.000000;   z = 6.000000;   w = 0.625000;  // C
   pMat24->DefineElement(0,a,z,w);
      a = 1.000000;   z = 1.000000;   w = 0.041667;  // H
   pMat24->DefineElement(1,a,z,w);
      a = 16.000000;   z = 8.000000;   w = 0.333333;  // O
   pMat24->DefineElement(2,a,z,w);
   pMat24->SetIndex(23);
// Medium: TPCE_MYLAR
   numed   = 0;  // medium number
   par[0]  = 0.000000; // isvol
   par[1]  = 1.000000; // ifield
   par[2]  = 20.000000; // fieldm
   par[3]  = 20.000000; // tmaxfd
   par[4]  = 10.000000; // stemax
   par[5]  = 0.212557; // deemax
   par[6]  = 0.010000; // epsil
   par[7]  = 0.031138; // stmin
   pMed63 = new TGeoMedium("TPCE_MYLAR", numed,pMat24, par);
// Material: ALUMINIUM
   a       = 26.980000;
   z       = 13.000000;
   density = 2.700000;
   radl    = 8.875105;
   absl    = 38.862232;
   pMat15 = new TGeoMaterial("ALUMINIUM", a,z,density,radl,absl);
   pMat15->SetIndex(14);
// Medium: TPCE_ALUMINIUM
   numed   = 0;  // medium number
   par[0]  = 0.000000; // isvol
   par[1]  = 1.000000; // ifield
   par[2]  = 20.000000; // fieldm
   par[3]  = 20.000000; // tmaxfd
   par[4]  = 10.000000; // stemax
   par[5]  = 0.182960; // deemax
   par[6]  = 0.010000; // epsil
   par[7]  = 0.033442; // stmin
   pMed67 = new TGeoMedium("TPCE_ALUMINIUM", numed,pMat15, par);
// Mixture: TPCE_NOMEX
   nel     = 3;
   density = 0.064000;
   pMat51 = new TGeoMixture("TPCE_NOMEX", nel,density);
      a = 12.000000;   z = 6.000000;   w = 0.600000;  // C
   pMat51->DefineElement(0,a,z,w);
      a = 1.000000;   z = 1.000000;   w = 0.080000;  // H
   pMat51->DefineElement(1,a,z,w);
      a = 16.000000;   z = 8.000000;   w = 0.320000;  // O
   pMat51->DefineElement(2,a,z,w);
   pMat51->SetIndex(50);
// Medium: TPCE_NOMEX
   numed   = 0;  // medium number
   par[0]  = 0.000000; // isvol
   par[1]  = 1.000000; // ifield
   par[2]  = 20.000000; // fieldm
   par[3]  = 20.000000; // tmaxfd
   par[4]  = 10.000000; // stemax
   par[5]  = 0.243085; // deemax
   par[6]  = 0.010000; // epsil
   par[7]  = 0.155955; // stmin
   pMed66 = new TGeoMedium("TPCE_NOMEX", numed,pMat51, par);
// Mixture: TPCE_Adhesive
   nel     = 3;
   density = 1.200000;
   pMat49 = new TGeoMixture("TPCE_Adhesive", nel,density);
      a = 12.000000;   z = 6.000000;   w = 0.625000;  // C
   pMat49->DefineElement(0,a,z,w);
      a = 1.000000;   z = 1.000000;   w = 0.041667;  // H
   pMat49->DefineElement(1,a,z,w);
      a = 16.000000;   z = 8.000000;   w = 0.333333;  // O
   pMat49->DefineElement(2,a,z,w);
   pMat49->SetIndex(48);
// Medium: TPCE_Adhesive
   numed   = 0;  // medium number
   par[0]  = 0.000000; // isvol
   par[1]  = 1.000000; // ifield
   par[2]  = 20.000000; // fieldm
   par[3]  = 20.000000; // tmaxfd
   par[4]  = 10.000000; // stemax
   par[5]  = 0.212557; // deemax
   par[6]  = 0.010000; // epsil
   par[7]  = 0.031138; // stmin
   pMed64 = new TGeoMedium("TPCE_Adhesive", numed,pMat49, par);
// Material: COPPER
   a       = 63.540000;
   z       = 29.000000;
   density = 8.960000;
   radl    = 1.435029;
   absl    = 15.514134;
   pMat17 = new TGeoMaterial("COPPER", a,z,density,radl,absl);
   pMat17->SetIndex(16);
// Medium: TPCE_COPPER
   numed   = 0;  // medium number
   par[0]  = 0.000000; // isvol
   par[1]  = 1.000000; // ifield
   par[2]  = 20.000000; // fieldm
   par[3]  = 20.000000; // tmaxfd
   par[4]  = 10.000000; // stemax
   par[5]  = 0.250000; // deemax
   par[6]  = 0.010000; // epsil
   par[7]  = 0.028139; // stmin
   pMed69 = new TGeoMedium("TPCE_COPPER", numed,pMat17, par);
// Material: NITROGEN_GAS
   a       = 14.010000;
   z       = 7.000000;
   density = 0.001165;
   radl    = 32492.606884;
   absl    = 72462.598655;
   pMat7 = new TGeoMaterial("NITROGEN_GAS", a,z,density,radl,absl);
   pMat7->SetIndex(6);
// Medium: TPCE_NITROGEN_GAS
   numed   = 0;  // medium number
   par[0]  = 0.000000; // isvol
   par[1]  = 1.000000; // ifield
   par[2]  = 20.000000; // fieldm
   par[3]  = 20.000000; // tmaxfd
   par[4]  = 10.000000; // stemax
   par[5]  = 0.248893; // deemax
   par[6]  = 0.010000; // epsil
   par[7]  = 1.145545; // stmin
   pMed68 = new TGeoMedium("TPCE_NITROGEN_GAS", numed,pMat7, par);
// Mixture: TPCE_AL_HONEYCOMB
   nel     = 3;
   density = 0.282000;
   pMat52 = new TGeoMixture("TPCE_AL_HONEYCOMB", nel,density);
      a = 27.000000;   z = 13.000000;   w = 0.010500;  // AL
   pMat52->DefineElement(0,a,z,w);
      a = 14.000000;   z = 7.000000;   w = 0.739500;  // N
   pMat52->DefineElement(1,a,z,w);
      a = 9.000000;   z = 4.500000;   w = 0.250000;  // BE
   pMat52->DefineElement(2,a,z,w);
   pMat52->SetIndex(51);
// Medium: TPCE_AL_HONEYCOMB
   numed   = 0;  // medium number
   par[0]  = 0.000000; // isvol
   par[1]  = 1.000000; // ifield
   par[2]  = 20.000000; // fieldm
   par[3]  = 20.000000; // tmaxfd
   par[4]  = 10.000000; // stemax
   par[5]  = 0.233280; // deemax
   par[6]  = 0.010000; // epsil
   par[7]  = 0.070769; // stmin
   pMed70 = new TGeoMedium("TPCE_AL_HONEYCOMB", numed,pMat52, par);
// Mixture: TPCE_P10
   nel     = 3;
   density = 0.001541;
   pMat47 = new TGeoMixture("TPCE_P10", nel,density);
      a = 40.000000;   z = 18.000000;   w = 0.957447;  // AR
   pMat47->DefineElement(0,a,z,w);
      a = 12.000000;   z = 6.000000;   w = 0.031915;  // C
   pMat47->DefineElement(1,a,z,w);
      a = 1.000000;   z = 1.000000;   w = 0.010638;  // H
   pMat47->DefineElement(2,a,z,w);
   pMat47->SetIndex(46);
// Medium: TPCE_P10
   numed   = 0;  // medium number
   par[0]  = 0.000000; // isvol
   par[1]  = 1.000000; // ifield
   par[2]  = 20.000000; // fieldm
   par[3]  = 20.000000; // tmaxfd
   par[4]  = 10.000000; // stemax
   par[5]  = 0.248174; // deemax
   par[6]  = 0.010000; // epsil
   par[7]  = 1.542206; // stmin
   pMed57 = new TGeoMedium("TPCE_P10", numed,pMat47, par);
// Material: TPCE_SENSITIVE_GAS
   a       = 38.691490;
   z       = 17.436170;
   density = 0.001541;
   radl    = 13017.765562;
   absl    = 75277.751640;
   pMat48 = new TGeoMaterial("TPCE_SENSITIVE_GAS", a,z,density,radl,absl);
   pMat48->SetIndex(47);
// Medium: TPCE_SENSITIVE_GAS
   numed   = 0;  // medium number
   par[0]  = 1.000000; // isvol
   par[1]  = 1.000000; // ifield
   par[2]  = 20.000000; // fieldm
   par[3]  = 20.000000; // tmaxfd
   par[4]  = 2.875000; // stemax
   par[5]  = 0.001826; // deemax
   par[6]  = 0.010000; // epsil
   par[7]  = 0.035988; // stmin
   pMed58 = new TGeoMedium("TPCE_SENSITIVE_GAS", numed,pMat48, par);
// Mixture: TPCE_G10
   nel     = 4;
   density = 1.700000;
   pMat53 = new TGeoMixture("TPCE_G10", nel,density);
      a = 28.080000;   z = 14.000000;   w = 0.280000;  // SI
   pMat53->DefineElement(0,a,z,w);
      a = 16.000000;   z = 8.000000;   w = 0.467126;  // O
   pMat53->DefineElement(1,a,z,w);
      a = 12.000000;   z = 6.000000;   w = 0.220690;  // C
   pMat53->DefineElement(2,a,z,w);
      a = 1.000000;   z = 1.000000;   w = 0.032184;  // H
   pMat53->DefineElement(3,a,z,w);
   pMat53->SetIndex(52);
// Medium: TPCE_G10
   numed   = 0;  // medium number
   par[0]  = 0.000000; // isvol
   par[1]  = 1.000000; // ifield
   par[2]  = 20.000000; // fieldm
   par[3]  = 20.000000; // tmaxfd
   par[4]  = 10.000000; // stemax
   par[5]  = 0.203130; // deemax
   par[6]  = 0.010000; // epsil
   par[7]  = 0.033381; // stmin
   pMed74 = new TGeoMedium("TPCE_G10", numed,pMat53, par);
// Mixture: TPCE_Water_Pipe
   nel     = 3;
   density = 2.321550;
   pMat50 = new TGeoMixture("TPCE_Water_Pipe", nel,density);
      a = 1.000000;   z = 1.000000;   w = 0.010655;  // H
   pMat50->DefineElement(0,a,z,w);
      a = 16.000000;   z = 8.000000;   w = 0.085237;  // O
   pMat50->DefineElement(1,a,z,w);
      a = 26.980000;   z = 13.000000;   w = 0.904108;  // AL
   pMat50->DefineElement(2,a,z,w);
   pMat50->SetIndex(49);
// Medium: TPCE_Water_Pipe
   numed   = 0;  // medium number
   par[0]  = 0.000000; // isvol
   par[1]  = 1.000000; // ifield
   par[2]  = 20.000000; // fieldm
   par[3]  = 20.000000; // tmaxfd
   par[4]  = 10.000000; // stemax
   par[5]  = 0.212557; // deemax
   par[6]  = 0.010000; // epsil
   par[7]  = 0.031138; // stmin
   pMed65 = new TGeoMedium("TPCE_Water_Pipe", numed,pMat50, par);
// Mixture: Cables
   nel     = 4;
   density = 2.680000;
   pMat123 = new TGeoMixture("Cables", nel,density);
      a = 63.540000;   z = 29.000000;   w = 0.586000;  // CU
   pMat123->DefineElement(0,a,z,w);
      a = 12.010000;   z = 6.000000;   w = 0.259000;  // C
   pMat123->DefineElement(1,a,z,w);
      a = 15.999000;   z = 8.000000;   w = 0.138000;  // O
   pMat123->DefineElement(2,a,z,w);
      a = 1.007940;   z = 1.000000;   w = 0.017000;  // H
   pMat123->DefineElement(3,a,z,w);
   pMat123->SetIndex(122);
// Medium: Cables
   numed   = 0;  // medium number
   par[0]  = 0.000000; // isvol
   par[1]  = 0.000000; // ifield
   par[2]  = 20.000000; // fieldm
   par[3]  = 20.000000; // tmaxfd
   par[4]  = 10.000000; // stemax
   par[5]  = 0.248853; // deemax
   par[6]  = 0.010000; // epsil
   par[7]  = 1.150551; // stmin
   pMed255 = new TGeoMedium("Cables", numed,pMat123, par);

   // TRANSFORMATION MATRICES
   // Rotation: R060
   thx = 90.000000;    phx = 60.000000;
   thy = 90.000000;    phy = 150.000000;
   thz = 0.000000;    phz = 0.000000;
   TGeoRotation *pMatrix146 = new TGeoRotation("R060",thx,phx,thy,phy,thz,phz);
   // Combi transformation: 
   dx = 58.850000;
   dy = 0.000000;
   dz = 104.950905;
   // Rotation: Z180
   thx = 90.000000;    phx = 270.000000;
   thy = 90.000000;    phy = 0.000000;
   thz = 0.000000;    phz = 0.000000;
   TGeoRotation *pMatrix11 = new TGeoRotation("Z180",thx,phx,thy,phy,thz,phz);
   pMatrix320 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.998095;
   TGeoTranslation *pMatrix319 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 60.000000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix321 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 61.150000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix322 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 63.650000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix324 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.998095;
   TGeoTranslation *pMatrix323 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 64.800000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix325 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 65.950000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix326 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 68.450000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix328 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.998095;
   TGeoTranslation *pMatrix327 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 69.600000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix329 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 70.750000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix330 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 73.250000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix332 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.998095;
   TGeoTranslation *pMatrix331 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 74.400000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix333 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 75.550000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix334 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 78.050000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix336 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.998095;
   TGeoTranslation *pMatrix335 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 79.200000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix337 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 80.350000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix338 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 82.850000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix340 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.998095;
   TGeoTranslation *pMatrix339 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 84.000000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix341 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 85.150000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix342 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 87.650000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix344 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.998095;
   TGeoTranslation *pMatrix343 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 88.800000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix345 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 89.950000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix346 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 92.450000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix348 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.998095;
   TGeoTranslation *pMatrix347 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 93.600000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix349 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 94.750000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix350 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 97.650000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix352 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.998095;
   TGeoTranslation *pMatrix351 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 98.800000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix353 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 99.950000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix354 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 102.850000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix356 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.998095;
   TGeoTranslation *pMatrix355 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 104.000000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix357 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 105.150000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix358 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 108.050000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix360 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.998095;
   TGeoTranslation *pMatrix359 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 109.200000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix361 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 110.350000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix362 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 113.250000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix364 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.998095;
   TGeoTranslation *pMatrix363 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 114.400000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix365 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 115.550000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix366 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 118.450000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix368 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.998095;
   TGeoTranslation *pMatrix367 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 119.600000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix369 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 120.750000;
   dy = 0.000000;
   dz = 104.950905;
   pMatrix370 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 125.245000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix516 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix515 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 127.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix517 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Combi transformation: 
   dx = 129.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix519 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix518 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 131.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix521 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix520 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 133.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix523 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix522 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 135.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix525 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix524 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 137.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix527 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix526 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 139.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix529 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix528 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 141.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix531 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix530 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 143.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix533 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix532 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 145.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix535 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix534 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 147.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix537 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix536 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 149.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix539 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix538 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 151.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix541 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix540 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 153.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix543 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix542 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 155.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix545 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix544 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 157.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix547 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix546 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 159.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix549 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix548 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 161.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix551 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix550 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 163.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix553 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix552 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 165.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix555 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix554 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 167.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix557 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix556 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 169.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix559 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix558 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 171.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix561 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix560 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 173.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix563 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix562 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 175.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix565 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix564 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 177.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix567 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix566 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 179.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix569 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix568 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 181.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix571 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix570 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 183.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix573 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix572 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 185.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix575 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix574 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 187.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix577 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix576 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 189.195000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix579 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: 
   dx = 0.000000;
   dy = 0.000000;
   dz = 96.798095;
   TGeoTranslation *pMatrix578 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 191.145000;
   dy = 0.000000;
   dz = 105.154105;
   pMatrix580 = new TGeoCombiTrans("", dx,dy,dz,pMatrix11);
   // Translation: InnerShift
   dx = 0.578227;
   dy = 0.000000;
   dz = 0.000000;
   TGeoTranslation *pMatrix371 = new TGeoTranslation("InnerShift",dx,dy,dz);
   // Translation: 
   dx = 115.804673;
   dy = -20.193000;
   dz = 210.556250;
   TGeoTranslation *pMatrix390 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 115.804673;
   dy = -12.115800;
   dz = 210.556250;
   TGeoTranslation *pMatrix392 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 115.804673;
   dy = -4.038600;
   dz = 210.556250;
   TGeoTranslation *pMatrix394 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 115.804673;
   dy = 4.038600;
   dz = 210.556250;
   TGeoTranslation *pMatrix396 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 115.804673;
   dy = 12.115800;
   dz = 210.556250;
   TGeoTranslation *pMatrix398 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 115.804673;
   dy = 20.193000;
   dz = 210.556250;
   TGeoTranslation *pMatrix400 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 111.804173;
   dy = -19.121120;
   dz = 210.556250;
   TGeoTranslation *pMatrix403 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 111.804173;
   dy = -9.560560;
   dz = 210.556250;
   TGeoTranslation *pMatrix405 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 111.804173;
   dy = 0.000000;
   dz = 210.556250;
   TGeoTranslation *pMatrix407 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 111.804173;
   dy = 9.560560;
   dz = 210.556250;
   TGeoTranslation *pMatrix409 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 111.804173;
   dy = 19.121120;
   dz = 210.556250;
   TGeoTranslation *pMatrix411 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 107.803673;
   dy = -18.049240;
   dz = 210.556250;
   TGeoTranslation *pMatrix414 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 107.803673;
   dy = -9.024620;
   dz = 210.556250;
   TGeoTranslation *pMatrix416 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 107.803673;
   dy = 0.000000;
   dz = 210.556250;
   TGeoTranslation *pMatrix418 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 107.803673;
   dy = 9.024620;
   dz = 210.556250;
   TGeoTranslation *pMatrix420 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 107.803673;
   dy = 18.049240;
   dz = 210.556250;
   TGeoTranslation *pMatrix422 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 103.803173;
   dy = -16.977360;
   dz = 210.556250;
   TGeoTranslation *pMatrix425 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 103.803173;
   dy = 16.977360;
   dz = 210.556250;
   TGeoTranslation *pMatrix427 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 99.802673;
   dy = -15.905480;
   dz = 210.556250;
   TGeoTranslation *pMatrix430 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 99.802673;
   dy = -7.952740;
   dz = 210.556250;
   TGeoTranslation *pMatrix432 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 99.802673;
   dy = 0.000000;
   dz = 210.556250;
   TGeoTranslation *pMatrix434 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 99.802673;
   dy = 7.952740;
   dz = 210.556250;
   TGeoTranslation *pMatrix436 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 99.802673;
   dy = 15.905480;
   dz = 210.556250;
   TGeoTranslation *pMatrix438 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 95.802173;
   dy = -14.833600;
   dz = 210.556250;
   TGeoTranslation *pMatrix441 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 95.802173;
   dy = -4.947920;
   dz = 210.556250;
   TGeoTranslation *pMatrix443 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 95.802173;
   dy = 4.947920;
   dz = 210.556250;
   TGeoTranslation *pMatrix445 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 95.802173;
   dy = 14.833600;
   dz = 210.556250;
   TGeoTranslation *pMatrix447 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 91.801673;
   dy = -13.761720;
   dz = 210.556250;
   TGeoTranslation *pMatrix450 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 91.801673;
   dy = -4.589780;
   dz = 210.556250;
   TGeoTranslation *pMatrix452 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 91.801673;
   dy = 4.589780;
   dz = 210.556250;
   TGeoTranslation *pMatrix454 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 91.801673;
   dy = 13.761720;
   dz = 210.556250;
   TGeoTranslation *pMatrix456 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 87.801173;
   dy = -12.688570;
   dz = 210.556250;
   TGeoTranslation *pMatrix459 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 87.801173;
   dy = -4.354830;
   dz = 210.556250;
   TGeoTranslation *pMatrix461 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 87.801173;
   dy = 4.354830;
   dz = 210.556250;
   TGeoTranslation *pMatrix463 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 87.801173;
   dy = 12.688570;
   dz = 210.556250;
   TGeoTranslation *pMatrix465 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 83.800673;
   dy = -12.001500;
   dz = 210.556250;
   TGeoTranslation *pMatrix468 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 83.800673;
   dy = -4.000500;
   dz = 210.556250;
   TGeoTranslation *pMatrix470 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 83.800673;
   dy = 4.000500;
   dz = 210.556250;
   TGeoTranslation *pMatrix472 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 83.800673;
   dy = 12.001500;
   dz = 210.556250;
   TGeoTranslation *pMatrix474 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 79.800173;
   dy = -10.546080;
   dz = 210.556250;
   TGeoTranslation *pMatrix477 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 79.800173;
   dy = 0.000000;
   dz = 210.556250;
   TGeoTranslation *pMatrix479 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 79.800173;
   dy = 10.546080;
   dz = 210.556250;
   TGeoTranslation *pMatrix481 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 75.799673;
   dy = -9.474200;
   dz = 210.556250;
   TGeoTranslation *pMatrix484 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 75.799673;
   dy = 0.000000;
   dz = 210.556250;
   TGeoTranslation *pMatrix486 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 75.799673;
   dy = 9.474200;
   dz = 210.556250;
   TGeoTranslation *pMatrix488 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 71.799173;
   dy = -8.402320;
   dz = 210.556250;
   TGeoTranslation *pMatrix491 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 71.799173;
   dy = 0.000000;
   dz = 210.556250;
   TGeoTranslation *pMatrix493 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 71.799173;
   dy = 8.402320;
   dz = 210.556250;
   TGeoTranslation *pMatrix495 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 67.798673;
   dy = -7.810500;
   dz = 210.556250;
   TGeoTranslation *pMatrix498 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 67.798673;
   dy = 0.000000;
   dz = 210.556250;
   TGeoTranslation *pMatrix500 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 67.798673;
   dy = 7.810500;
   dz = 210.556250;
   TGeoTranslation *pMatrix502 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 63.798173;
   dy = -6.257290;
   dz = 210.556250;
   TGeoTranslation *pMatrix505 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 63.798173;
   dy = 6.257290;
   dz = 210.556250;
   TGeoTranslation *pMatrix507 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 59.797673;
   dy = -5.185410;
   dz = 210.556250;
   TGeoTranslation *pMatrix510 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 59.797673;
   dy = 5.185410;
   dz = 210.556250;
   TGeoTranslation *pMatrix512 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 86.090483;
   dy = -21.264358;
   dz = 214.656250;
   // Rotation: YZXZ
   thx = 90.000000;    phx = 90.000000;
   thy = 90.000000;    phy = 0.000000;
   thz = 180.000000;    phz = 0.000000;
   TGeoRotation *pMatrix104 = new TGeoRotation("YZXZ",thx,phx,thy,phy,thz,phz);
   pMatrix372 = new TGeoCombiTrans("", dx,dy,dz,pMatrix104);
   // Combi transformation: WireMountTRInnerLeft
   dx = 86.090483;
   dy = -23.893145;
   dz = 209.047100;
   pMatrix373 = new TGeoCombiTrans("WireMountTRInnerLeft", dx,dy,dz,pMatrix104);
   // Combi transformation: 
   dx = 86.090483;
   dy = 21.264358;
   dz = 214.656250;
   pMatrix374 = new TGeoCombiTrans("", dx,dy,dz,pMatrix104);
   // Combi transformation: WireMountTRInnerRight
   dx = 86.090483;
   dy = 23.893145;
   dz = 209.047100;
   pMatrix375 = new TGeoCombiTrans("WireMountTRInnerRight", dx,dy,dz,pMatrix104);
   // Combi transformation: 
   dx = 118.987293;
   dy = 0.000000;
   dz = 214.656250;
   // Rotation: 90XD
   thx = 90.000000;    phx = 90.000000;
   thy = 0.000000;    phy = 0.000000;
   thz = 90.000000;    phz = 0.000000;
   TGeoRotation *pMatrix14 = new TGeoRotation("90XD",thx,phx,thy,phy,thz,phz);
   pMatrix376 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Combi transformation: 
   dx = 109.555003;
   dy = 0.000000;
   dz = 214.656250;
   pMatrix377 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Combi transformation: 
   dx = 93.553003;
   dy = 0.000000;
   dz = 214.656250;
   pMatrix378 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Combi transformation: 
   dx = 77.551003;
   dy = 0.000000;
   dz = 214.656250;
   pMatrix379 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Combi transformation: 
   dx = 61.549003;
   dy = 0.000000;
   dz = 214.656250;
   pMatrix380 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Combi transformation: 
   dx = 53.133983;
   dy = 0.000000;
   dz = 214.656250;
   pMatrix381 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 111.390153;
   dy = -14.338300;
   dz = 214.656250;
   TGeoTranslation *pMatrix382 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 111.390153;
   dy = 14.338300;
   dz = 214.656250;
   TGeoTranslation *pMatrix383 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 95.388153;
   dy = -9.893300;
   dz = 214.656250;
   TGeoTranslation *pMatrix384 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 95.388153;
   dy = 9.893300;
   dz = 214.656250;
   TGeoTranslation *pMatrix385 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 56.134993;
   dy = 0.000000;
   dz = 214.656250;
   TGeoTranslation *pMatrix386 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 85.042733;
   dy = -17.280255;
   dz = 220.566000;
   pMatrix387 = new TGeoCombiTrans("", dx,dy,dz,pMatrix104);
   // Combi transformation: 
   dx = 85.042733;
   dy = 17.280255;
   dz = 220.566000;
   pMatrix388 = new TGeoCombiTrans("", dx,dy,dz,pMatrix104);
   // Combi transformation: 
   dx = 115.317561;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix389 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 116.555430;
   dy = -20.193000;
   dz = 219.755359;
   TGeoTranslation *pMatrix391 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = -0.836041;
   dy = 0.000000;
   dz = 0.000000;
   TGeoTranslation *pMatrix317 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 0.410718;
   dy = 0.000000;
   dz = 0.500000;
   TGeoTranslation *pMatrix318 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 116.555430;
   dy = -12.115800;
   dz = 219.755359;
   TGeoTranslation *pMatrix393 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 116.555430;
   dy = -4.038600;
   dz = 219.755359;
   TGeoTranslation *pMatrix395 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 116.555430;
   dy = 4.038600;
   dz = 219.755359;
   TGeoTranslation *pMatrix397 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 116.555430;
   dy = 12.115800;
   dz = 219.755359;
   TGeoTranslation *pMatrix399 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 116.555430;
   dy = 20.193000;
   dz = 219.755359;
   TGeoTranslation *pMatrix401 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 111.317060;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix402 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 112.554929;
   dy = -19.121120;
   dz = 219.755359;
   TGeoTranslation *pMatrix404 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 112.554929;
   dy = -9.560560;
   dz = 219.755359;
   TGeoTranslation *pMatrix406 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 112.554929;
   dy = 0.000000;
   dz = 219.755359;
   TGeoTranslation *pMatrix408 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 112.554929;
   dy = 9.560560;
   dz = 219.755359;
   TGeoTranslation *pMatrix410 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 112.554929;
   dy = 19.121120;
   dz = 219.755359;
   TGeoTranslation *pMatrix412 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 107.316561;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix413 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 108.554429;
   dy = -18.049240;
   dz = 219.755359;
   TGeoTranslation *pMatrix415 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 108.554429;
   dy = -9.024620;
   dz = 219.755359;
   TGeoTranslation *pMatrix417 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 108.554429;
   dy = 0.000000;
   dz = 219.755359;
   TGeoTranslation *pMatrix419 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 108.554429;
   dy = 9.024620;
   dz = 219.755359;
   TGeoTranslation *pMatrix421 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 108.554429;
   dy = 18.049240;
   dz = 219.755359;
   TGeoTranslation *pMatrix423 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 103.316060;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix424 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 104.553929;
   dy = -16.977360;
   dz = 219.755359;
   TGeoTranslation *pMatrix426 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 104.553929;
   dy = 16.977360;
   dz = 219.755359;
   TGeoTranslation *pMatrix428 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 99.315561;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix429 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 100.553429;
   dy = -15.905480;
   dz = 219.755359;
   TGeoTranslation *pMatrix431 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 100.553429;
   dy = -7.952740;
   dz = 219.755359;
   TGeoTranslation *pMatrix433 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 100.553429;
   dy = 0.000000;
   dz = 219.755359;
   TGeoTranslation *pMatrix435 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 100.553429;
   dy = 7.952740;
   dz = 219.755359;
   TGeoTranslation *pMatrix437 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 100.553429;
   dy = 15.905480;
   dz = 219.755359;
   TGeoTranslation *pMatrix439 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 95.315060;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix440 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 96.552929;
   dy = -14.833600;
   dz = 219.755359;
   TGeoTranslation *pMatrix442 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 96.552929;
   dy = -4.947920;
   dz = 219.755359;
   TGeoTranslation *pMatrix444 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 96.552929;
   dy = 4.947920;
   dz = 219.755359;
   TGeoTranslation *pMatrix446 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 96.552929;
   dy = 14.833600;
   dz = 219.755359;
   TGeoTranslation *pMatrix448 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 91.314560;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix449 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 92.552429;
   dy = -13.761720;
   dz = 219.755359;
   TGeoTranslation *pMatrix451 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 92.552429;
   dy = -4.589780;
   dz = 219.755359;
   TGeoTranslation *pMatrix453 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 92.552429;
   dy = 4.589780;
   dz = 219.755359;
   TGeoTranslation *pMatrix455 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 92.552429;
   dy = 13.761720;
   dz = 219.755359;
   TGeoTranslation *pMatrix457 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 87.314060;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix458 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 88.551929;
   dy = -12.688570;
   dz = 219.755359;
   TGeoTranslation *pMatrix460 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 88.551929;
   dy = -4.354830;
   dz = 219.755359;
   TGeoTranslation *pMatrix462 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 88.551929;
   dy = 4.354830;
   dz = 219.755359;
   TGeoTranslation *pMatrix464 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 88.551929;
   dy = 12.688570;
   dz = 219.755359;
   TGeoTranslation *pMatrix466 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 83.313560;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix467 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 84.551429;
   dy = -12.001500;
   dz = 219.755359;
   TGeoTranslation *pMatrix469 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 84.551429;
   dy = -4.000500;
   dz = 219.755359;
   TGeoTranslation *pMatrix471 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 84.551429;
   dy = 4.000500;
   dz = 219.755359;
   TGeoTranslation *pMatrix473 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 84.551429;
   dy = 12.001500;
   dz = 219.755359;
   TGeoTranslation *pMatrix475 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 79.313060;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix476 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 80.550929;
   dy = -10.546080;
   dz = 219.755359;
   TGeoTranslation *pMatrix478 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 80.550929;
   dy = 0.000000;
   dz = 219.755359;
   TGeoTranslation *pMatrix480 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 80.550929;
   dy = 10.546080;
   dz = 219.755359;
   TGeoTranslation *pMatrix482 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 75.312560;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix483 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 76.550429;
   dy = -9.474200;
   dz = 219.755359;
   TGeoTranslation *pMatrix485 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 76.550429;
   dy = 0.000000;
   dz = 219.755359;
   TGeoTranslation *pMatrix487 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 76.550429;
   dy = 9.474200;
   dz = 219.755359;
   TGeoTranslation *pMatrix489 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 71.312060;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix490 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 72.549929;
   dy = -8.402320;
   dz = 219.755359;
   TGeoTranslation *pMatrix492 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 72.549929;
   dy = 0.000000;
   dz = 219.755359;
   TGeoTranslation *pMatrix494 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 72.549929;
   dy = 8.402320;
   dz = 219.755359;
   TGeoTranslation *pMatrix496 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 67.311560;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix497 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 68.549429;
   dy = -7.810500;
   dz = 219.755359;
   TGeoTranslation *pMatrix499 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 68.549429;
   dy = 0.000000;
   dz = 219.755359;
   TGeoTranslation *pMatrix501 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 68.549429;
   dy = 7.810500;
   dz = 219.755359;
   TGeoTranslation *pMatrix503 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 63.311060;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix504 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 64.548929;
   dy = -6.257290;
   dz = 219.755359;
   TGeoTranslation *pMatrix506 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 64.548929;
   dy = 6.257290;
   dz = 219.755359;
   TGeoTranslation *pMatrix508 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 59.310560;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix509 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 60.548429;
   dy = -5.185410;
   dz = 219.755359;
   TGeoTranslation *pMatrix511 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 60.548429;
   dy = 5.185410;
   dz = 219.755359;
   TGeoTranslation *pMatrix513 = new TGeoTranslation("",dx,dy,dz);
   // Translation: OuterShift
   dx = 0.578654;
   dy = 0.000000;
   dz = 0.000000;
   TGeoTranslation *pMatrix581 = new TGeoTranslation("OuterShift",dx,dy,dz);
   // Translation: 
   dx = 187.617526;
   dy = -38.163500;
   dz = 210.962650;
   TGeoTranslation *pMatrix603 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 187.617526;
   dy = -29.479240;
   dz = 210.962650;
   TGeoTranslation *pMatrix605 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 187.617526;
   dy = -20.769580;
   dz = 210.962650;
   TGeoTranslation *pMatrix607 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 187.617526;
   dy = -10.718800;
   dz = 210.962650;
   TGeoTranslation *pMatrix609 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 187.617526;
   dy = 0.000000;
   dz = 210.962650;
   TGeoTranslation *pMatrix611 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 187.617526;
   dy = 10.718800;
   dz = 210.962650;
   TGeoTranslation *pMatrix613 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 187.617526;
   dy = 20.769580;
   dz = 210.962650;
   TGeoTranslation *pMatrix615 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 187.617526;
   dy = 29.479240;
   dz = 210.962650;
   TGeoTranslation *pMatrix617 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 187.617526;
   dy = 38.163500;
   dz = 210.962650;
   TGeoTranslation *pMatrix619 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 183.617026;
   dy = -38.163500;
   dz = 210.962650;
   TGeoTranslation *pMatrix622 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 183.617026;
   dy = -29.479240;
   dz = 210.962650;
   TGeoTranslation *pMatrix624 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 183.617026;
   dy = -20.769580;
   dz = 210.962650;
   TGeoTranslation *pMatrix626 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 183.617026;
   dy = -10.718800;
   dz = 210.962650;
   TGeoTranslation *pMatrix628 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 183.617026;
   dy = 0.000000;
   dz = 210.962650;
   TGeoTranslation *pMatrix630 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 183.617026;
   dy = 10.718800;
   dz = 210.962650;
   TGeoTranslation *pMatrix632 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 183.617026;
   dy = 20.769580;
   dz = 210.962650;
   TGeoTranslation *pMatrix634 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 183.617026;
   dy = 29.479240;
   dz = 210.962650;
   TGeoTranslation *pMatrix636 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 183.617026;
   dy = 38.163500;
   dz = 210.962650;
   TGeoTranslation *pMatrix638 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 179.616526;
   dy = -36.177220;
   dz = 210.962650;
   TGeoTranslation *pMatrix641 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 179.616526;
   dy = -28.138120;
   dz = 210.962650;
   TGeoTranslation *pMatrix643 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 179.616526;
   dy = -16.078200;
   dz = 210.962650;
   TGeoTranslation *pMatrix645 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 179.616526;
   dy = -8.039100;
   dz = 210.962650;
   TGeoTranslation *pMatrix647 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 179.616526;
   dy = 0.000000;
   dz = 210.962650;
   TGeoTranslation *pMatrix649 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 179.616526;
   dy = 8.039100;
   dz = 210.962650;
   TGeoTranslation *pMatrix651 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 179.616526;
   dy = 16.078200;
   dz = 210.962650;
   TGeoTranslation *pMatrix653 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 179.616526;
   dy = 28.138120;
   dz = 210.962650;
   TGeoTranslation *pMatrix655 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 179.616526;
   dy = 36.177220;
   dz = 210.962650;
   TGeoTranslation *pMatrix657 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 175.616026;
   dy = -36.177220;
   dz = 210.962650;
   TGeoTranslation *pMatrix660 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 175.616026;
   dy = -28.138120;
   dz = 210.962650;
   TGeoTranslation *pMatrix662 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 175.616026;
   dy = -16.078200;
   dz = 210.962650;
   TGeoTranslation *pMatrix664 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 175.616026;
   dy = -8.039100;
   dz = 210.962650;
   TGeoTranslation *pMatrix666 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 175.616026;
   dy = 0.000000;
   dz = 210.962650;
   TGeoTranslation *pMatrix668 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 175.616026;
   dy = 8.039100;
   dz = 210.962650;
   TGeoTranslation *pMatrix670 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 175.616026;
   dy = 16.078200;
   dz = 210.962650;
   TGeoTranslation *pMatrix672 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 175.616026;
   dy = 28.138120;
   dz = 210.962650;
   TGeoTranslation *pMatrix674 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 175.616026;
   dy = 36.177220;
   dz = 210.962650;
   TGeoTranslation *pMatrix676 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 171.615526;
   dy = -34.168080;
   dz = 210.962650;
   TGeoTranslation *pMatrix679 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 171.615526;
   dy = -25.458420;
   dz = 210.962650;
   TGeoTranslation *pMatrix681 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 171.615526;
   dy = -16.078200;
   dz = 210.962650;
   TGeoTranslation *pMatrix683 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 171.615526;
   dy = -8.039100;
   dz = 210.962650;
   TGeoTranslation *pMatrix685 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 171.615526;
   dy = 0.000000;
   dz = 210.962650;
   TGeoTranslation *pMatrix687 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 171.615526;
   dy = 8.039100;
   dz = 210.962650;
   TGeoTranslation *pMatrix689 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 171.615526;
   dy = 16.078200;
   dz = 210.962650;
   TGeoTranslation *pMatrix691 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 171.615526;
   dy = 25.458420;
   dz = 210.962650;
   TGeoTranslation *pMatrix693 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 171.615526;
   dy = 34.168080;
   dz = 210.962650;
   TGeoTranslation *pMatrix695 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 167.615026;
   dy = -34.168080;
   dz = 210.962650;
   TGeoTranslation *pMatrix698 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 167.615026;
   dy = -25.458420;
   dz = 210.962650;
   TGeoTranslation *pMatrix700 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 167.615026;
   dy = -16.078200;
   dz = 210.962650;
   TGeoTranslation *pMatrix702 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 167.615026;
   dy = -8.039100;
   dz = 210.962650;
   TGeoTranslation *pMatrix704 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 167.615026;
   dy = 8.039100;
   dz = 210.962650;
   TGeoTranslation *pMatrix706 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 167.615026;
   dy = 16.078200;
   dz = 210.962650;
   TGeoTranslation *pMatrix708 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 167.615026;
   dy = 25.458420;
   dz = 210.962650;
   TGeoTranslation *pMatrix710 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 167.615026;
   dy = 34.168080;
   dz = 210.962650;
   TGeoTranslation *pMatrix712 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 163.614526;
   dy = -32.156400;
   dz = 210.962650;
   TGeoTranslation *pMatrix715 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 163.614526;
   dy = -24.117300;
   dz = 210.962650;
   TGeoTranslation *pMatrix717 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 163.614526;
   dy = -16.078200;
   dz = 210.962650;
   TGeoTranslation *pMatrix719 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 163.614526;
   dy = -5.359400;
   dz = 210.962650;
   TGeoTranslation *pMatrix721 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 163.614526;
   dy = 5.359400;
   dz = 210.962650;
   TGeoTranslation *pMatrix723 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 163.614526;
   dy = 16.078200;
   dz = 210.962650;
   TGeoTranslation *pMatrix725 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 163.614526;
   dy = 24.117300;
   dz = 210.962650;
   TGeoTranslation *pMatrix727 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 163.614526;
   dy = 32.156400;
   dz = 210.962650;
   TGeoTranslation *pMatrix729 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 159.614026;
   dy = -32.156400;
   dz = 210.962650;
   TGeoTranslation *pMatrix732 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 159.614026;
   dy = -24.117300;
   dz = 210.962650;
   TGeoTranslation *pMatrix734 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 159.614026;
   dy = -16.078200;
   dz = 210.962650;
   TGeoTranslation *pMatrix736 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 159.614026;
   dy = -5.359400;
   dz = 210.962650;
   TGeoTranslation *pMatrix738 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 159.614026;
   dy = 5.359400;
   dz = 210.962650;
   TGeoTranslation *pMatrix740 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 159.614026;
   dy = 16.078200;
   dz = 210.962650;
   TGeoTranslation *pMatrix742 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 159.614026;
   dy = 24.117300;
   dz = 210.962650;
   TGeoTranslation *pMatrix744 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 159.614026;
   dy = 32.156400;
   dz = 210.962650;
   TGeoTranslation *pMatrix746 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 155.613526;
   dy = -30.149800;
   dz = 210.962650;
   TGeoTranslation *pMatrix749 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 155.613526;
   dy = -21.437600;
   dz = 210.962650;
   TGeoTranslation *pMatrix751 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 155.613526;
   dy = -13.398500;
   dz = 210.962650;
   TGeoTranslation *pMatrix753 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 155.613526;
   dy = -5.359400;
   dz = 210.962650;
   TGeoTranslation *pMatrix755 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 155.613526;
   dy = 5.359400;
   dz = 210.962650;
   TGeoTranslation *pMatrix757 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 155.613526;
   dy = 13.398500;
   dz = 210.962650;
   TGeoTranslation *pMatrix759 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 155.613526;
   dy = 21.437600;
   dz = 210.962650;
   TGeoTranslation *pMatrix761 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 155.613526;
   dy = 30.149800;
   dz = 210.962650;
   TGeoTranslation *pMatrix763 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 151.613026;
   dy = -30.149800;
   dz = 210.962650;
   TGeoTranslation *pMatrix766 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 151.613026;
   dy = -21.437600;
   dz = 210.962650;
   TGeoTranslation *pMatrix768 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 151.613026;
   dy = -13.398500;
   dz = 210.962650;
   TGeoTranslation *pMatrix770 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 151.613026;
   dy = -5.359400;
   dz = 210.962650;
   TGeoTranslation *pMatrix772 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 151.613026;
   dy = 5.359400;
   dz = 210.962650;
   TGeoTranslation *pMatrix774 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 151.613026;
   dy = 13.398500;
   dz = 210.962650;
   TGeoTranslation *pMatrix776 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 151.613026;
   dy = 21.437600;
   dz = 210.962650;
   TGeoTranslation *pMatrix778 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 151.613026;
   dy = 30.149800;
   dz = 210.962650;
   TGeoTranslation *pMatrix780 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 147.612526;
   dy = -28.138120;
   dz = 210.962650;
   TGeoTranslation *pMatrix783 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 147.612526;
   dy = -19.428460;
   dz = 210.962650;
   TGeoTranslation *pMatrix785 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 147.612526;
   dy = -10.718800;
   dz = 210.962650;
   TGeoTranslation *pMatrix787 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 147.612526;
   dy = 0.000000;
   dz = 210.962650;
   TGeoTranslation *pMatrix789 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 147.612526;
   dy = 10.718800;
   dz = 210.962650;
   TGeoTranslation *pMatrix791 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 147.612526;
   dy = 19.428460;
   dz = 210.962650;
   TGeoTranslation *pMatrix793 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 147.612526;
   dy = 28.138120;
   dz = 210.962650;
   TGeoTranslation *pMatrix795 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 143.612026;
   dy = -28.138120;
   dz = 210.962650;
   TGeoTranslation *pMatrix798 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 143.612026;
   dy = -19.428460;
   dz = 210.962650;
   TGeoTranslation *pMatrix800 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 143.612026;
   dy = -10.718800;
   dz = 210.962650;
   TGeoTranslation *pMatrix802 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 143.612026;
   dy = 0.000000;
   dz = 210.962650;
   TGeoTranslation *pMatrix804 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 143.612026;
   dy = 10.718800;
   dz = 210.962650;
   TGeoTranslation *pMatrix806 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 143.612026;
   dy = 19.428460;
   dz = 210.962650;
   TGeoTranslation *pMatrix808 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 143.612026;
   dy = 28.138120;
   dz = 210.962650;
   TGeoTranslation *pMatrix810 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 139.611526;
   dy = -25.455880;
   dz = 210.962650;
   TGeoTranslation *pMatrix813 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 139.611526;
   dy = -17.419320;
   dz = 210.962650;
   TGeoTranslation *pMatrix815 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 139.611526;
   dy = -8.709660;
   dz = 210.962650;
   TGeoTranslation *pMatrix817 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 139.611526;
   dy = 0.000000;
   dz = 210.962650;
   TGeoTranslation *pMatrix819 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 139.611526;
   dy = 8.709660;
   dz = 210.962650;
   TGeoTranslation *pMatrix821 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 139.611526;
   dy = 17.419320;
   dz = 210.962650;
   TGeoTranslation *pMatrix823 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 139.611526;
   dy = 25.455880;
   dz = 210.962650;
   TGeoTranslation *pMatrix825 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 135.611026;
   dy = -25.455880;
   dz = 210.962650;
   TGeoTranslation *pMatrix828 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 135.611026;
   dy = -17.419320;
   dz = 210.962650;
   TGeoTranslation *pMatrix830 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 135.611026;
   dy = -8.709660;
   dz = 210.962650;
   TGeoTranslation *pMatrix832 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 135.611026;
   dy = 0.000000;
   dz = 210.962650;
   TGeoTranslation *pMatrix834 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 135.611026;
   dy = 8.709660;
   dz = 210.962650;
   TGeoTranslation *pMatrix836 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 135.611026;
   dy = 17.419320;
   dz = 210.962650;
   TGeoTranslation *pMatrix838 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 135.611026;
   dy = 25.455880;
   dz = 210.962650;
   TGeoTranslation *pMatrix840 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 131.610526;
   dy = -24.117300;
   dz = 210.962650;
   TGeoTranslation *pMatrix843 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 131.610526;
   dy = -16.078200;
   dz = 210.962650;
   TGeoTranslation *pMatrix845 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 131.610526;
   dy = -8.039100;
   dz = 210.962650;
   TGeoTranslation *pMatrix847 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 131.610526;
   dy = 0.000000;
   dz = 210.962650;
   TGeoTranslation *pMatrix849 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 131.610526;
   dy = 8.039100;
   dz = 210.962650;
   TGeoTranslation *pMatrix851 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 131.610526;
   dy = 16.078200;
   dz = 210.962650;
   TGeoTranslation *pMatrix853 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 131.610526;
   dy = 24.117300;
   dz = 210.962650;
   TGeoTranslation *pMatrix855 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 127.610026;
   dy = -24.117300;
   dz = 210.962650;
   TGeoTranslation *pMatrix858 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 127.610026;
   dy = -16.078200;
   dz = 210.962650;
   TGeoTranslation *pMatrix860 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 127.610026;
   dy = -8.039100;
   dz = 210.962650;
   TGeoTranslation *pMatrix862 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 127.610026;
   dy = 8.039100;
   dz = 210.962650;
   TGeoTranslation *pMatrix864 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 127.610026;
   dy = 16.078200;
   dz = 210.962650;
   TGeoTranslation *pMatrix866 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 127.610026;
   dy = 24.117300;
   dz = 210.962650;
   TGeoTranslation *pMatrix868 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 156.910196;
   dy = -40.240063;
   dz = 214.859450;
   pMatrix582 = new TGeoCombiTrans("", dx,dy,dz,pMatrix104);
   // Combi transformation: WireMountTROuterLeft
   dx = 156.910196;
   dy = -42.868850;
   dz = 209.453500;
   pMatrix583 = new TGeoCombiTrans("WireMountTROuterLeft", dx,dy,dz,pMatrix104);
   // Combi transformation: 
   dx = 156.910196;
   dy = 40.240063;
   dz = 214.859450;
   pMatrix584 = new TGeoCombiTrans("", dx,dy,dz,pMatrix104);
   // Combi transformation: WireMountTROuterRight
   dx = 156.910196;
   dy = 42.868850;
   dz = 209.453500;
   pMatrix585 = new TGeoCombiTrans("WireMountTROuterRight", dx,dy,dz,pMatrix104);
   // Combi transformation: 
   dx = 190.345486;
   dy = 0.000000;
   dz = 214.859450;
   pMatrix586 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Combi transformation: 
   dx = 181.367856;
   dy = 0.000000;
   dz = 214.859450;
   pMatrix587 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Combi transformation: 
   dx = 173.369396;
   dy = 0.000000;
   dz = 214.859450;
   pMatrix588 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Combi transformation: 
   dx = 165.368396;
   dy = 0.000000;
   dz = 214.859450;
   pMatrix589 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Combi transformation: 
   dx = 157.367396;
   dy = 0.000000;
   dz = 214.859450;
   pMatrix590 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Combi transformation: 
   dx = 149.368936;
   dy = 0.000000;
   dz = 214.859450;
   pMatrix591 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Combi transformation: 
   dx = 141.367936;
   dy = 0.000000;
   dz = 214.859450;
   pMatrix592 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Combi transformation: 
   dx = 133.369476;
   dy = 0.000000;
   dz = 214.859450;
   pMatrix593 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Combi transformation: 
   dx = 123.853366;
   dy = 0.000000;
   dz = 214.859450;
   pMatrix594 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 177.368626;
   dy = 21.907500;
   dz = 214.859450;
   TGeoTranslation *pMatrix595 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 177.368626;
   dy = -21.907500;
   dz = 214.859450;
   TGeoTranslation *pMatrix596 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 161.367896;
   dy = 0.000000;
   dz = 214.859450;
   TGeoTranslation *pMatrix597 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 153.368166;
   dy = 0.000000;
   dz = 214.859450;
   TGeoTranslation *pMatrix598 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 127.842436;
   dy = 0.000000;
   dz = 214.859450;
   TGeoTranslation *pMatrix599 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 156.770726;
   dy = -36.010215;
   dz = 220.566000;
   pMatrix600 = new TGeoCombiTrans("", dx,dy,dz,pMatrix104);
   // Combi transformation: 
   dx = 156.770726;
   dy = 36.010215;
   dz = 220.566000;
   pMatrix601 = new TGeoCombiTrans("", dx,dy,dz,pMatrix104);
   // Combi transformation: 
   dx = 187.130840;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix602 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 188.368709;
   dy = -38.163500;
   dz = 219.755359;
   TGeoTranslation *pMatrix604 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 188.368709;
   dy = -29.479240;
   dz = 219.755359;
   TGeoTranslation *pMatrix606 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 188.368709;
   dy = -20.769580;
   dz = 219.755359;
   TGeoTranslation *pMatrix608 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 188.368709;
   dy = -10.718800;
   dz = 219.755359;
   TGeoTranslation *pMatrix610 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 188.368709;
   dy = 0.000000;
   dz = 219.755359;
   TGeoTranslation *pMatrix612 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 188.368709;
   dy = 10.718800;
   dz = 219.755359;
   TGeoTranslation *pMatrix614 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 188.368709;
   dy = 20.769580;
   dz = 219.755359;
   TGeoTranslation *pMatrix616 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 188.368709;
   dy = 29.479240;
   dz = 219.755359;
   TGeoTranslation *pMatrix618 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 188.368709;
   dy = 38.163500;
   dz = 219.755359;
   TGeoTranslation *pMatrix620 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 183.130340;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix621 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 184.368209;
   dy = -38.163500;
   dz = 219.755359;
   TGeoTranslation *pMatrix623 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 184.368209;
   dy = -29.479240;
   dz = 219.755359;
   TGeoTranslation *pMatrix625 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 184.368209;
   dy = -20.769580;
   dz = 219.755359;
   TGeoTranslation *pMatrix627 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 184.368209;
   dy = -10.718800;
   dz = 219.755359;
   TGeoTranslation *pMatrix629 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 184.368209;
   dy = 0.000000;
   dz = 219.755359;
   TGeoTranslation *pMatrix631 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 184.368209;
   dy = 10.718800;
   dz = 219.755359;
   TGeoTranslation *pMatrix633 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 184.368209;
   dy = 20.769580;
   dz = 219.755359;
   TGeoTranslation *pMatrix635 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 184.368209;
   dy = 29.479240;
   dz = 219.755359;
   TGeoTranslation *pMatrix637 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 184.368209;
   dy = 38.163500;
   dz = 219.755359;
   TGeoTranslation *pMatrix639 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 179.129841;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix640 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 180.367709;
   dy = -36.177220;
   dz = 219.755359;
   TGeoTranslation *pMatrix642 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 180.367709;
   dy = -28.138120;
   dz = 219.755359;
   TGeoTranslation *pMatrix644 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 180.367709;
   dy = -16.078200;
   dz = 219.755359;
   TGeoTranslation *pMatrix646 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 180.367709;
   dy = -8.039100;
   dz = 219.755359;
   TGeoTranslation *pMatrix648 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 180.367709;
   dy = 0.000000;
   dz = 219.755359;
   TGeoTranslation *pMatrix650 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 180.367709;
   dy = 8.039100;
   dz = 219.755359;
   TGeoTranslation *pMatrix652 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 180.367709;
   dy = 16.078200;
   dz = 219.755359;
   TGeoTranslation *pMatrix654 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 180.367709;
   dy = 28.138120;
   dz = 219.755359;
   TGeoTranslation *pMatrix656 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 180.367709;
   dy = 36.177220;
   dz = 219.755359;
   TGeoTranslation *pMatrix658 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 175.129341;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix659 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 176.367210;
   dy = -36.177220;
   dz = 219.755359;
   TGeoTranslation *pMatrix661 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 176.367210;
   dy = -28.138120;
   dz = 219.755359;
   TGeoTranslation *pMatrix663 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 176.367210;
   dy = -16.078200;
   dz = 219.755359;
   TGeoTranslation *pMatrix665 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 176.367210;
   dy = -8.039100;
   dz = 219.755359;
   TGeoTranslation *pMatrix667 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 176.367210;
   dy = 0.000000;
   dz = 219.755359;
   TGeoTranslation *pMatrix669 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 176.367210;
   dy = 8.039100;
   dz = 219.755359;
   TGeoTranslation *pMatrix671 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 176.367210;
   dy = 16.078200;
   dz = 219.755359;
   TGeoTranslation *pMatrix673 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 176.367210;
   dy = 28.138120;
   dz = 219.755359;
   TGeoTranslation *pMatrix675 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 176.367210;
   dy = 36.177220;
   dz = 219.755359;
   TGeoTranslation *pMatrix677 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 171.128840;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix678 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 172.366709;
   dy = -34.168080;
   dz = 219.755359;
   TGeoTranslation *pMatrix680 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 172.366709;
   dy = -25.458420;
   dz = 219.755359;
   TGeoTranslation *pMatrix682 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 172.366709;
   dy = -16.078200;
   dz = 219.755359;
   TGeoTranslation *pMatrix684 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 172.366709;
   dy = -8.039100;
   dz = 219.755359;
   TGeoTranslation *pMatrix686 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 172.366709;
   dy = 0.000000;
   dz = 219.755359;
   TGeoTranslation *pMatrix688 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 172.366709;
   dy = 8.039100;
   dz = 219.755359;
   TGeoTranslation *pMatrix690 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 172.366709;
   dy = 16.078200;
   dz = 219.755359;
   TGeoTranslation *pMatrix692 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 172.366709;
   dy = 25.458420;
   dz = 219.755359;
   TGeoTranslation *pMatrix694 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 172.366709;
   dy = 34.168080;
   dz = 219.755359;
   TGeoTranslation *pMatrix696 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 167.128340;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix697 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 168.366209;
   dy = -34.168080;
   dz = 219.755359;
   TGeoTranslation *pMatrix699 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 168.366209;
   dy = -25.458420;
   dz = 219.755359;
   TGeoTranslation *pMatrix701 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 168.366209;
   dy = -16.078200;
   dz = 219.755359;
   TGeoTranslation *pMatrix703 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 168.366209;
   dy = -8.039100;
   dz = 219.755359;
   TGeoTranslation *pMatrix705 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 168.366209;
   dy = 8.039100;
   dz = 219.755359;
   TGeoTranslation *pMatrix707 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 168.366209;
   dy = 16.078200;
   dz = 219.755359;
   TGeoTranslation *pMatrix709 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 168.366209;
   dy = 25.458420;
   dz = 219.755359;
   TGeoTranslation *pMatrix711 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 168.366209;
   dy = 34.168080;
   dz = 219.755359;
   TGeoTranslation *pMatrix713 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 163.127840;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix714 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 164.365709;
   dy = -32.156400;
   dz = 219.755359;
   TGeoTranslation *pMatrix716 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 164.365709;
   dy = -24.117300;
   dz = 219.755359;
   TGeoTranslation *pMatrix718 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 164.365709;
   dy = -16.078200;
   dz = 219.755359;
   TGeoTranslation *pMatrix720 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 164.365709;
   dy = -5.359400;
   dz = 219.755359;
   TGeoTranslation *pMatrix722 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 164.365709;
   dy = 5.359400;
   dz = 219.755359;
   TGeoTranslation *pMatrix724 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 164.365709;
   dy = 16.078200;
   dz = 219.755359;
   TGeoTranslation *pMatrix726 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 164.365709;
   dy = 24.117300;
   dz = 219.755359;
   TGeoTranslation *pMatrix728 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 164.365709;
   dy = 32.156400;
   dz = 219.755359;
   TGeoTranslation *pMatrix730 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 159.127341;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix731 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 160.365209;
   dy = -32.156400;
   dz = 219.755359;
   TGeoTranslation *pMatrix733 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 160.365209;
   dy = -24.117300;
   dz = 219.755359;
   TGeoTranslation *pMatrix735 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 160.365209;
   dy = -16.078200;
   dz = 219.755359;
   TGeoTranslation *pMatrix737 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 160.365209;
   dy = -5.359400;
   dz = 219.755359;
   TGeoTranslation *pMatrix739 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 160.365209;
   dy = 5.359400;
   dz = 219.755359;
   TGeoTranslation *pMatrix741 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 160.365209;
   dy = 16.078200;
   dz = 219.755359;
   TGeoTranslation *pMatrix743 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 160.365209;
   dy = 24.117300;
   dz = 219.755359;
   TGeoTranslation *pMatrix745 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 160.365209;
   dy = 32.156400;
   dz = 219.755359;
   TGeoTranslation *pMatrix747 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 155.126841;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix748 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 156.364710;
   dy = -30.149800;
   dz = 219.755359;
   TGeoTranslation *pMatrix750 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 156.364710;
   dy = -21.437600;
   dz = 219.755359;
   TGeoTranslation *pMatrix752 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 156.364710;
   dy = -13.398500;
   dz = 219.755359;
   TGeoTranslation *pMatrix754 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 156.364710;
   dy = -5.359400;
   dz = 219.755359;
   TGeoTranslation *pMatrix756 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 156.364710;
   dy = 5.359400;
   dz = 219.755359;
   TGeoTranslation *pMatrix758 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 156.364710;
   dy = 13.398500;
   dz = 219.755359;
   TGeoTranslation *pMatrix760 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 156.364710;
   dy = 21.437600;
   dz = 219.755359;
   TGeoTranslation *pMatrix762 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 156.364710;
   dy = 30.149800;
   dz = 219.755359;
   TGeoTranslation *pMatrix764 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 151.126340;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix765 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 152.364209;
   dy = -30.149800;
   dz = 219.755359;
   TGeoTranslation *pMatrix767 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 152.364209;
   dy = -21.437600;
   dz = 219.755359;
   TGeoTranslation *pMatrix769 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 152.364209;
   dy = -13.398500;
   dz = 219.755359;
   TGeoTranslation *pMatrix771 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 152.364209;
   dy = -5.359400;
   dz = 219.755359;
   TGeoTranslation *pMatrix773 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 152.364209;
   dy = 5.359400;
   dz = 219.755359;
   TGeoTranslation *pMatrix775 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 152.364209;
   dy = 13.398500;
   dz = 219.755359;
   TGeoTranslation *pMatrix777 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 152.364209;
   dy = 21.437600;
   dz = 219.755359;
   TGeoTranslation *pMatrix779 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 152.364209;
   dy = 30.149800;
   dz = 219.755359;
   TGeoTranslation *pMatrix781 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 147.125840;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix782 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 148.363709;
   dy = -28.138120;
   dz = 219.755359;
   TGeoTranslation *pMatrix784 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 148.363709;
   dy = -19.428460;
   dz = 219.755359;
   TGeoTranslation *pMatrix786 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 148.363709;
   dy = -10.718800;
   dz = 219.755359;
   TGeoTranslation *pMatrix788 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 148.363709;
   dy = 0.000000;
   dz = 219.755359;
   TGeoTranslation *pMatrix790 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 148.363709;
   dy = 10.718800;
   dz = 219.755359;
   TGeoTranslation *pMatrix792 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 148.363709;
   dy = 19.428460;
   dz = 219.755359;
   TGeoTranslation *pMatrix794 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 148.363709;
   dy = 28.138120;
   dz = 219.755359;
   TGeoTranslation *pMatrix796 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 143.125340;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix797 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 144.363209;
   dy = -28.138120;
   dz = 219.755359;
   TGeoTranslation *pMatrix799 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 144.363209;
   dy = -19.428460;
   dz = 219.755359;
   TGeoTranslation *pMatrix801 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 144.363209;
   dy = -10.718800;
   dz = 219.755359;
   TGeoTranslation *pMatrix803 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 144.363209;
   dy = 0.000000;
   dz = 219.755359;
   TGeoTranslation *pMatrix805 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 144.363209;
   dy = 10.718800;
   dz = 219.755359;
   TGeoTranslation *pMatrix807 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 144.363209;
   dy = 19.428460;
   dz = 219.755359;
   TGeoTranslation *pMatrix809 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 144.363209;
   dy = 28.138120;
   dz = 219.755359;
   TGeoTranslation *pMatrix811 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 139.124841;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix812 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 140.362709;
   dy = -25.455880;
   dz = 219.755359;
   TGeoTranslation *pMatrix814 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 140.362709;
   dy = -17.419320;
   dz = 219.755359;
   TGeoTranslation *pMatrix816 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 140.362709;
   dy = -8.709660;
   dz = 219.755359;
   TGeoTranslation *pMatrix818 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 140.362709;
   dy = 0.000000;
   dz = 219.755359;
   TGeoTranslation *pMatrix820 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 140.362709;
   dy = 8.709660;
   dz = 219.755359;
   TGeoTranslation *pMatrix822 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 140.362709;
   dy = 17.419320;
   dz = 219.755359;
   TGeoTranslation *pMatrix824 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 140.362709;
   dy = 25.455880;
   dz = 219.755359;
   TGeoTranslation *pMatrix826 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 135.124341;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix827 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 136.362210;
   dy = -25.455880;
   dz = 219.755359;
   TGeoTranslation *pMatrix829 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 136.362210;
   dy = -17.419320;
   dz = 219.755359;
   TGeoTranslation *pMatrix831 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 136.362210;
   dy = -8.709660;
   dz = 219.755359;
   TGeoTranslation *pMatrix833 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 136.362210;
   dy = 0.000000;
   dz = 219.755359;
   TGeoTranslation *pMatrix835 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 136.362210;
   dy = 8.709660;
   dz = 219.755359;
   TGeoTranslation *pMatrix837 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 136.362210;
   dy = 17.419320;
   dz = 219.755359;
   TGeoTranslation *pMatrix839 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 136.362210;
   dy = 25.455880;
   dz = 219.755359;
   TGeoTranslation *pMatrix841 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 131.123840;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix842 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 132.361709;
   dy = -24.117300;
   dz = 219.755359;
   TGeoTranslation *pMatrix844 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 132.361709;
   dy = -16.078200;
   dz = 219.755359;
   TGeoTranslation *pMatrix846 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 132.361709;
   dy = -8.039100;
   dz = 219.755359;
   TGeoTranslation *pMatrix848 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 132.361709;
   dy = 0.000000;
   dz = 219.755359;
   TGeoTranslation *pMatrix850 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 132.361709;
   dy = 8.039100;
   dz = 219.755359;
   TGeoTranslation *pMatrix852 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 132.361709;
   dy = 16.078200;
   dz = 219.755359;
   TGeoTranslation *pMatrix854 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 132.361709;
   dy = 24.117300;
   dz = 219.755359;
   TGeoTranslation *pMatrix856 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 127.123340;
   dy = 0.000000;
   dz = 218.915000;
   pMatrix857 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 128.361209;
   dy = -24.117300;
   dz = 219.755359;
   TGeoTranslation *pMatrix859 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 128.361209;
   dy = -16.078200;
   dz = 219.755359;
   TGeoTranslation *pMatrix861 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 128.361209;
   dy = -8.039100;
   dz = 219.755359;
   TGeoTranslation *pMatrix863 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 128.361209;
   dy = 8.039100;
   dz = 219.755359;
   TGeoTranslation *pMatrix865 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 128.361209;
   dy = 16.078200;
   dz = 219.755359;
   TGeoTranslation *pMatrix867 = new TGeoTranslation("",dx,dy,dz);
   // Translation: 
   dx = 128.361209;
   dy = 24.117300;
   dz = 219.755359;
   TGeoTranslation *pMatrix869 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 140.776220;
   dy = 36.470874;
   dz = 248.760000;
   pMatrix884 = new TGeoCombiTrans("", dx,dy,dz,pMatrix104);
   // Combi transformation: 
   dx = 140.776220;
   dy = -36.470874;
   dz = 248.760000;
   pMatrix885 = new TGeoCombiTrans("", dx,dy,dz,pMatrix104);
   // Combi transformation: 
   dx = 189.740600;
   dy = 0.000000;
   dz = 248.440000;
   pMatrix886 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Combi transformation: 
   dx = 173.740600;
   dy = 0.000000;
   dz = 248.440000;
   pMatrix888 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 175.508410;
   dy = 0.000000;
   dz = 241.210000;
   TGeoTranslation *pMatrix890 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 157.740600;
   dy = 0.000000;
   dz = 248.440000;
   pMatrix891 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 159.508410;
   dy = 0.000000;
   dz = 241.210000;
   TGeoTranslation *pMatrix893 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 141.740600;
   dy = 0.000000;
   dz = 248.440000;
   pMatrix894 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 143.508410;
   dy = 0.000000;
   dz = 241.210000;
   TGeoTranslation *pMatrix896 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 125.040600;
   dy = 0.000000;
   dz = 248.440000;
   pMatrix897 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 126.808410;
   dy = 0.000000;
   dz = 241.210000;
   TGeoTranslation *pMatrix899 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 110.040600;
   dy = 0.000000;
   dz = 248.440000;
   pMatrix900 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 111.808410;
   dy = 0.000000;
   dz = 241.210000;
   TGeoTranslation *pMatrix902 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 106.540600;
   dy = 0.000000;
   dz = 248.440000;
   pMatrix903 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Combi transformation: 
   dx = 92.040600;
   dy = 0.000000;
   dz = 248.440000;
   pMatrix905 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Translation: 
   dx = 93.808410;
   dy = 0.000000;
   dz = 241.210000;
   TGeoTranslation *pMatrix907 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 189.740600;
   dy = 0.000000;
   dz = 248.440000;
   pMatrix887 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Combi transformation: 
   dx = 173.740600;
   dy = 0.000000;
   dz = 248.440000;
   pMatrix889 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Combi transformation: 
   dx = 157.740600;
   dy = 0.000000;
   dz = 248.440000;
   pMatrix892 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Combi transformation: 
   dx = 141.740600;
   dy = 0.000000;
   dz = 248.440000;
   pMatrix895 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Combi transformation: 
   dx = 125.040600;
   dy = 0.000000;
   dz = 248.440000;
   pMatrix898 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Combi transformation: 
   dx = 110.040600;
   dy = 0.000000;
   dz = 248.440000;
   pMatrix901 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Combi transformation: 
   dx = 106.540600;
   dy = 0.000000;
   dz = 248.440000;
   pMatrix904 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Combi transformation: 
   dx = 92.040600;
   dy = 0.000000;
   dz = 248.440000;
   pMatrix906 = new TGeoCombiTrans("", dx,dy,dz,pMatrix14);
   // Combi transformation: 
   dx = 123.943110;
   dy = -30.960456;
   dz = 262.710000;
   pMatrix908 = new TGeoCombiTrans("", dx,dy,dz,pMatrix104);
   // Combi transformation: 
   dx = 123.943110;
   dy = 30.960456;
   dz = 262.710000;
   pMatrix909 = new TGeoCombiTrans("", dx,dy,dz,pMatrix104);
   // Translation: 
   dx = 121.582180;
   dy = 0.000000;
   dz = 223.995000;
   TGeoTranslation *pMatrix871 = new TGeoTranslation("",dx,dy,dz);
   // Combi transformation: 
   dx = 123.012715;
   dy = -31.061158;
   dz = 218.930000;
   pMatrix872 = new TGeoCombiTrans("", dx,dy,dz,pMatrix104);
   // Combi transformation: 
   dx = 123.012715;
   dy = -32.486158;
   dz = 223.995000;
   pMatrix873 = new TGeoCombiTrans("", dx,dy,dz,pMatrix104);
   // Combi transformation: 
   dx = 180.624331;
   dy = -48.398144;
   dz = 223.995000;
   // Rotation: R345
   thx = 90.000000;    phx = 345.000000;
   thy = 90.000000;    phy = 75.000000;
   thz = 0.000000;    phz = 0.000000;
   TGeoRotation *pMatrix203 = new TGeoRotation("R345",thx,phx,thy,phy,thz,phz);
   pMatrix874 = new TGeoCombiTrans("", dx,dy,dz,pMatrix203);
   // Combi transformation: 
   dx = 138.451366;
   dy = -37.097932;
   dz = 223.995000;
   pMatrix875 = new TGeoCombiTrans("", dx,dy,dz,pMatrix203);
   // Combi transformation: 
   dx = 105.824020;
   dy = -28.355461;
   dz = 223.995000;
   pMatrix876 = new TGeoCombiTrans("", dx,dy,dz,pMatrix203);
   // Combi transformation: 
   dx = 66.428620;
   dy = -17.799495;
   dz = 223.995000;
   pMatrix877 = new TGeoCombiTrans("", dx,dy,dz,pMatrix203);
   // Combi transformation: 
   dx = 123.012715;
   dy = 31.061158;
   dz = 218.930000;
   pMatrix878 = new TGeoCombiTrans("", dx,dy,dz,pMatrix104);
   // Combi transformation: 
   dx = 123.012715;
   dy = 32.486158;
   dz = 223.995000;
   pMatrix879 = new TGeoCombiTrans("", dx,dy,dz,pMatrix104);
   // Combi transformation: 
   dx = 180.624331;
   dy = 48.398144;
   dz = 223.995000;
   // Rotation: R015
   thx = 90.000000;    phx = 15.000000;
   thy = 90.000000;    phy = 105.000000;
   thz = 0.000000;    phz = 0.000000;
   TGeoRotation *pMatrix137 = new TGeoRotation("R015",thx,phx,thy,phy,thz,phz);
   pMatrix880 = new TGeoCombiTrans("", dx,dy,dz,pMatrix137);
   // Combi transformation: 
   dx = 138.451366;
   dy = 37.097932;
   dz = 223.995000;
   pMatrix881 = new TGeoCombiTrans("", dx,dy,dz,pMatrix137);
   // Combi transformation: 
   dx = 105.824020;
   dy = 28.355461;
   dz = 223.995000;
   pMatrix882 = new TGeoCombiTrans("", dx,dy,dz,pMatrix137);
   // Combi transformation: 
   dx = 66.428620;
   dy = 17.799495;
   dz = 223.995000;
   pMatrix883 = new TGeoCombiTrans("", dx,dy,dz,pMatrix137);
   // Rotation: R030
   thx = 90.000000;    phx = 30.000000;
   thy = 90.000000;    phy = 120.000000;
   thz = 0.000000;    phz = 0.000000;
   TGeoRotation *pMatrix140 = new TGeoRotation("R030",thx,phx,thy,phy,thz,phz);
   // Rotation: R000
   thx = 90.000000;    phx = 0.000000;
   thy = 90.000000;    phy = 90.000000;
   thz = 0.000000;    phz = 0.000000;
   TGeoRotation *pMatrix134 = new TGeoRotation("R000",thx,phx,thy,phy,thz,phz);
   // Rotation: R330
   thx = 90.000000;    phx = 330.000000;
   thy = 90.000000;    phy = 60.000000;
   thz = 0.000000;    phz = 0.000000;
   TGeoRotation *pMatrix200 = new TGeoRotation("R330",thx,phx,thy,phy,thz,phz);
   // Rotation: R300
   thx = 90.000000;    phx = 300.000000;
   thy = 90.000000;    phy = 30.000000;
   thz = 0.000000;    phz = 0.000000;
   TGeoRotation *pMatrix194 = new TGeoRotation("R300",thx,phx,thy,phy,thz,phz);
   // Rotation: R270
   thx = 90.000000;    phx = 270.000000;
   thy = 90.000000;    phy = 360.000000;
   thz = 0.000000;    phz = 0.000000;
   TGeoRotation *pMatrix188 = new TGeoRotation("R270",thx,phx,thy,phy,thz,phz);
   // Rotation: R240
   thx = 90.000000;    phx = 240.000000;
   thy = 90.000000;    phy = 330.000000;
   thz = 0.000000;    phz = 0.000000;
   TGeoRotation *pMatrix182 = new TGeoRotation("R240",thx,phx,thy,phy,thz,phz);
   // Rotation: R210
   thx = 90.000000;    phx = 210.000000;
   thy = 90.000000;    phy = 300.000000;
   thz = 0.000000;    phz = 0.000000;
   TGeoRotation *pMatrix176 = new TGeoRotation("R210",thx,phx,thy,phy,thz,phz);
   // Rotation: R180
   thx = 90.000000;    phx = 180.000000;
   thy = 90.000000;    phy = 270.000000;
   thz = 0.000000;    phz = 0.000000;
   TGeoRotation *pMatrix170 = new TGeoRotation("R180",thx,phx,thy,phy,thz,phz);
   // Rotation: R150
   thx = 90.000000;    phx = 150.000000;
   thy = 90.000000;    phy = 240.000000;
   thz = 0.000000;    phz = 0.000000;
   TGeoRotation *pMatrix164 = new TGeoRotation("R150",thx,phx,thy,phy,thz,phz);
   // Rotation: R120
   thx = 90.000000;    phx = 120.000000;
   thy = 90.000000;    phy = 210.000000;
   thz = 0.000000;    phz = 0.000000;
   TGeoRotation *pMatrix158 = new TGeoRotation("R120",thx,phx,thy,phy,thz,phz);
   // Rotation: R090
   thx = 90.000000;    phx = 90.000000;
   thy = 90.000000;    phy = 180.000000;
   thz = 0.000000;    phz = 0.000000;
   TGeoRotation *pMatrix152 = new TGeoRotation("R090",thx,phx,thy,phy,thz,phz);
   // Rotation: Y120
   thx = 90.000000;    phx = 120.000000;
   thy = 90.000000;    phy = 30.000000;
   thz = 180.000000;    phz = 0.000000;
   TGeoRotation *pMatrix219 = new TGeoRotation("Y120",thx,phx,thy,phy,thz,phz);
   // Rotation: Y150
   thx = 90.000000;    phx = 150.000000;
   thy = 90.000000;    phy = 60.000000;
   thz = 180.000000;    phz = 0.000000;
   TGeoRotation *pMatrix220 = new TGeoRotation("Y150",thx,phx,thy,phy,thz,phz);
   // Rotation: Y180
   thx = 90.000000;    phx = 180.000000;
   thy = 90.000000;    phy = 90.000000;
   thz = 180.000000;    phz = 0.000000;
   TGeoRotation *pMatrix221 = new TGeoRotation("Y180",thx,phx,thy,phy,thz,phz);
   // Rotation: Y210
   thx = 90.000000;    phx = 210.000000;
   thy = 90.000000;    phy = 120.000000;
   thz = 180.000000;    phz = 0.000000;
   TGeoRotation *pMatrix222 = new TGeoRotation("Y210",thx,phx,thy,phy,thz,phz);
   // Rotation: Y240
   thx = 90.000000;    phx = 240.000000;
   thy = 90.000000;    phy = 150.000000;
   thz = 180.000000;    phz = 0.000000;
   TGeoRotation *pMatrix223 = new TGeoRotation("Y240",thx,phx,thy,phy,thz,phz);
   // Rotation: Y270
   thx = 90.000000;    phx = 270.000000;
   thy = 90.000000;    phy = 180.000000;
   thz = 180.000000;    phz = 0.000000;
   TGeoRotation *pMatrix224 = new TGeoRotation("Y270",thx,phx,thy,phy,thz,phz);
   // Rotation: Y300
   thx = 90.000000;    phx = 300.000000;
   thy = 90.000000;    phy = 210.000000;
   thz = 180.000000;    phz = 0.000000;
   TGeoRotation *pMatrix225 = new TGeoRotation("Y300",thx,phx,thy,phy,thz,phz);
   // Rotation: Y330
   thx = 90.000000;    phx = 330.000000;
   thy = 90.000000;    phy = 240.000000;
   thz = 180.000000;    phz = 0.000000;
   TGeoRotation *pMatrix226 = new TGeoRotation("Y330",thx,phx,thy,phy,thz,phz);
   // Rotation: Y000
   thx = 90.000000;    phx = 0.000000;
   thy = 90.000000;    phy = 270.000000;
   thz = 180.000000;    phz = 0.000000;
   TGeoRotation *pMatrix215 = new TGeoRotation("Y000",thx,phx,thy,phy,thz,phz);
   // Rotation: Y030
   thx = 90.000000;    phx = 30.000000;
   thy = 90.000000;    phy = 300.000000;
   thz = 180.000000;    phz = 0.000000;
   TGeoRotation *pMatrix216 = new TGeoRotation("Y030",thx,phx,thy,phy,thz,phz);
   // Rotation: Y060
   thx = 90.000000;    phx = 60.000000;
   thy = 90.000000;    phy = 330.000000;
   thz = 180.000000;    phz = 0.000000;
   TGeoRotation *pMatrix217 = new TGeoRotation("Y060",thx,phx,thy,phy,thz,phz);
   // Rotation: Y090
   thx = 90.000000;    phx = 90.000000;
   thy = 90.000000;    phy = 360.000000;
   thz = 180.000000;    phz = 0.000000;
   TGeoRotation *pMatrix218 = new TGeoRotation("Y090",thx,phx,thy,phy,thz,phz);
   // Shape: TPCE type: TGeoTube
   rmin = 46.107000;
   rmax = 207.750000;
   dz   = 259.685000;
   TGeoShape *pTPCE_23 = new TGeoTube("TPCE",rmin,rmax,dz);
   // Volume: TPCE
   pTPCE_3ad6520 = new TGeoVolume("TPCE",pTPCE_23, pMed56);
   pTPCE_3ad6520->SetVisibility(kFALSE);
   pTPCE_3ad6520->SetVisLeaves(kTRUE);

   // SET TOP VOLUME OF GEOMETRY
   gGeoManager->SetTopVolume(pTPCE_3ad6520);

   // SHAPES, VOLUMES AND GEOMETRICAL HIERARCHY
   // Shape: TPCM type: TGeoTube
   rmin = 47.969000;
   rmax = 200.000000;
   dz   = 0.003810;
   TGeoShape *pTPCM_24 = new TGeoTube("TPCM",rmin,rmax,dz);
   // Volume: TPCM
   pTPCM_3ad67f0 = new TGeoVolume("TPCM",pTPCM_24, pMed63);
   pTPCM_3ad67f0->SetLineColor(600);
   pTPCM_3ad67f0->SetVisLeaves(kTRUE);
   pTPCE_3ad6520->AddNode(pTPCM_3ad67f0, 1);
   // Shape: TIFC type: TGeoPcon
   phi1  = 0.000000;
   dphi  = 360.000000;
   nz    = 6;
   TGeoPcon *pcon = new TGeoPcon("TIFC",phi1,dphi,nz);
      z     = -230.680000;
      rmin  = 46.600000;
      rmax  = 51.700000;
   pcon->DefineSection(0, z,rmin,rmax);
      z     = -228.140000;
      rmin  = 46.600000;
      rmax  = 51.700000;
   pcon->DefineSection(1, z,rmin,rmax);
      z     = -228.140000;
      rmin  = 46.600000;
      rmax  = 47.969000;
   pcon->DefineSection(2, z,rmin,rmax);
      z     = 228.140000;
      rmin  = 46.600000;
      rmax  = 47.969000;
   pcon->DefineSection(3, z,rmin,rmax);
      z     = 228.140000;
      rmin  = 46.600000;
      rmax  = 51.700000;
   pcon->DefineSection(4, z,rmin,rmax);
      z     = 230.680000;
      rmin  = 46.600000;
      rmax  = 51.700000;
   pcon->DefineSection(5, z,rmin,rmax);
   TGeoShape *pTIFC_25 = pcon;
   // Volume: TIFC
   pTIFC_3ad7710 = new TGeoVolume("TIFC",pTIFC_25, pMed67);
   pTIFC_3ad7710->SetLineColor(600);
   pTIFC_3ad7710->SetVisLeaves(kTRUE);
   pTPCE_3ad6520->AddNode(pTIFC_3ad7710, 1);
   // Shape: TOFC type: TGeoPcon
   phi1  = 0.000000;
   dphi  = 360.000000;
   nz    = 6;
   TGeoPcon *pcon = new TGeoPcon("TOFC",phi1,dphi,nz);
      z     = -223.990000;
      rmin  = 201.000000;
      rmax  = 206.750000;
   pcon->DefineSection(0, z,rmin,rmax);
      z     = -218.280000;
      rmin  = 201.000000;
      rmax  = 206.750000;
   pcon->DefineSection(1, z,rmin,rmax);
      z     = -218.280000;
      rmin  = 200.000000;
      rmax  = 207.731000;
   pcon->DefineSection(2, z,rmin,rmax);
      z     = 218.280000;
      rmin  = 200.000000;
      rmax  = 207.731000;
   pcon->DefineSection(3, z,rmin,rmax);
      z     = 218.280000;
      rmin  = 201.000000;
      rmax  = 206.750000;
   pcon->DefineSection(4, z,rmin,rmax);
      z     = 223.990000;
      rmin  = 201.000000;
      rmax  = 206.750000;
   pcon->DefineSection(5, z,rmin,rmax);
   TGeoShape *pTOFC_29 = pcon;
   // Volume: TOFC
   pTOFC_3ad9270 = new TGeoVolume("TOFC",pTOFC_29, pMed67);
   pTOFC_3ad9270->SetLineColor(600);
   pTOFC_3ad9270->SetVisLeaves(kTRUE);
   pTPCE_3ad6520->AddNode(pTOFC_3ad9270, 1);
   // Shape: TpcSectorWhole type: TGeoPcon
   phi1  = 345.000000;
   dphi  = 30.000000;
   nz    = 8;
   TGeoPcon *pcon = new TGeoPcon("TpcSectorWhole",phi1,dphi,nz);
      z     = 0.003810;
      rmin  = 47.969000;
      rmax  = 200.000000;
   pcon->DefineSection(0, z,rmin,rmax);
      z     = 218.280000;
      rmin  = 47.969000;
      rmax  = 200.000000;
   pcon->DefineSection(1, z,rmin,rmax);
      z     = 218.280000;
      rmin  = 47.969000;
      rmax  = 201.000000;
   pcon->DefineSection(2, z,rmin,rmax);
      z     = 223.990000;
      rmin  = 47.969000;
      rmax  = 201.000000;
   pcon->DefineSection(3, z,rmin,rmax);
      z     = 223.990000;
      rmin  = 47.969000;
      rmax  = 206.750000;
   pcon->DefineSection(4, z,rmin,rmax);
      z     = 228.140000;
      rmin  = 47.969000;
      rmax  = 206.750000;
   pcon->DefineSection(5, z,rmin,rmax);
      z     = 228.140000;
      rmin  = 51.800000;
      rmax  = 206.750000;
   pcon->DefineSection(6, z,rmin,rmax);
      z     = 259.685000;
      rmin  = 51.800000;
      rmax  = 206.750000;
   pcon->DefineSection(7, z,rmin,rmax);
   TGeoShape *pTpcSectorWhole_36 = pcon;
   // Volume: TpcSectorWhole
   pTpcSectorWhole_3adb970 = new TGeoVolume("TpcSectorWhole",pTpcSectorWhole_36, pMed56);
   pTpcSectorWhole_3adb970->SetVisLeaves(kTRUE);
   pTPCE_3ad6520->AddNode(pTpcSectorWhole_3adb970, 1, pMatrix146);
   pTPCE_3ad6520->AddNode(pTpcSectorWhole_3adb970, 2, pMatrix140);
   pTPCE_3ad6520->AddNode(pTpcSectorWhole_3adb970, 3, pMatrix134);
   pTPCE_3ad6520->AddNode(pTpcSectorWhole_3adb970, 4, pMatrix200);
   pTPCE_3ad6520->AddNode(pTpcSectorWhole_3adb970, 5, pMatrix194);
   pTPCE_3ad6520->AddNode(pTpcSectorWhole_3adb970, 6, pMatrix188);
   pTPCE_3ad6520->AddNode(pTpcSectorWhole_3adb970, 7, pMatrix182);
   pTPCE_3ad6520->AddNode(pTpcSectorWhole_3adb970, 8, pMatrix176);
   pTPCE_3ad6520->AddNode(pTpcSectorWhole_3adb970, 9, pMatrix170);
   pTPCE_3ad6520->AddNode(pTpcSectorWhole_3adb970, 10, pMatrix164);
   pTPCE_3ad6520->AddNode(pTpcSectorWhole_3adb970, 11, pMatrix158);
   pTPCE_3ad6520->AddNode(pTpcSectorWhole_3adb970, 12, pMatrix152);
   pTPCE_3ad6520->AddNode(pTpcSectorWhole_3adb970, 13, pMatrix219);
   pTPCE_3ad6520->AddNode(pTpcSectorWhole_3adb970, 14, pMatrix220);
   pTPCE_3ad6520->AddNode(pTpcSectorWhole_3adb970, 15, pMatrix221);
   pTPCE_3ad6520->AddNode(pTpcSectorWhole_3adb970, 16, pMatrix222);
   pTPCE_3ad6520->AddNode(pTpcSectorWhole_3adb970, 17, pMatrix223);
   pTPCE_3ad6520->AddNode(pTpcSectorWhole_3adb970, 18, pMatrix224);
   pTPCE_3ad6520->AddNode(pTpcSectorWhole_3adb970, 19, pMatrix225);
   pTPCE_3ad6520->AddNode(pTpcSectorWhole_3adb970, 20, pMatrix226);
   pTPCE_3ad6520->AddNode(pTpcSectorWhole_3adb970, 21, pMatrix215);
   pTPCE_3ad6520->AddNode(pTpcSectorWhole_3adb970, 22, pMatrix216);
   pTPCE_3ad6520->AddNode(pTpcSectorWhole_3adb970, 23, pMatrix217);
   pTPCE_3ad6520->AddNode(pTpcSectorWhole_3adb970, 24, pMatrix218);
   // Shape: TIKA type: TGeoTube
   rmin = 46.602000;
   rmax = 46.617000;
   dz   = 221.162000;
   TGeoShape *pTIKA_26 = new TGeoTube("TIKA",rmin,rmax,dz);
   // Volume: TIKA
   pTIKA_3ad81e0 = new TGeoVolume("TIKA",pTIKA_26, pMed63);
   pTIKA_3ad81e0->SetLineColor(800);
   pTIKA_3ad81e0->SetVisLeaves(kTRUE);
   pTIFC_3ad7710->AddNode(pTIKA_3ad81e0, 1);
   // Shape: TINX type: TGeoTube
   rmin = 46.617000;
   rmax = 47.887000;
   dz   = 221.162000;
   TGeoShape *pTINX_27 = new TGeoTube("TINX",rmin,rmax,dz);
   // Volume: TINX
   pTINX_3ad8960 = new TGeoVolume("TINX",pTINX_27, pMed66);
   pTINX_3ad8960->SetLineColor(400);
   pTINX_3ad8960->SetVisLeaves(kTRUE);
   pTIFC_3ad7710->AddNode(pTINX_3ad8960, 1);
   // Shape: TIAD type: TGeoTube
   rmin = 47.887000;
   rmax = 47.967000;
   dz   = 221.162000;
   TGeoShape *pTIAD_28 = new TGeoTube("TIAD",rmin,rmax,dz);
   // Volume: TIAD
   pTIAD_3ad8d00 = new TGeoVolume("TIAD",pTIAD_28, pMed64);
   pTIAD_3ad8d00->SetLineColor(400);
   pTIAD_3ad8d00->SetVisLeaves(kTRUE);
   pTIFC_3ad7710->AddNode(pTIAD_3ad8d00, 1);
   // Shape: TOFS type: TGeoTube
   rmin = 200.000000;
   rmax = 200.013000;
   dz   = 211.900000;
   TGeoShape *pTOFS_30 = new TGeoTube("TOFS",rmin,rmax,dz);
   // Volume: TOFS
   pTOFS_3ad9630 = new TGeoVolume("TOFS",pTOFS_30, pMed69);
   pTOFS_3ad9630->SetLineColor(600);
   pTOFS_3ad9630->SetVisLeaves(kTRUE);
   pTOFC_3ad9270->AddNode(pTOFS_3ad9630, 1);
   // Shape: TOKA type: TGeoTube
   rmin = 200.013000;
   rmax = 200.028000;
   dz   = 211.900000;
   TGeoShape *pTOKA_31 = new TGeoTube("TOKA",rmin,rmax,dz);
   // Volume: TOKA
   pTOKA_3ad9ca0 = new TGeoVolume("TOKA",pTOKA_31, pMed63);
   pTOKA_3ad9ca0->SetLineColor(416);
   pTOKA_3ad9ca0->SetVisLeaves(kTRUE);
   pTOFC_3ad9270->AddNode(pTOKA_3ad9ca0, 1);
   // Shape: TONX type: TGeoPcon
   phi1  = 0.000000;
   dphi  = 360.000000;
   nz    = 6;
   TGeoPcon *pcon = new TGeoPcon("TONX",phi1,dphi,nz);
      z     = -211.900000;
      rmin  = 200.781000;
      rmax  = 200.981000;
   pcon->DefineSection(0, z,rmin,rmax);
      z     = -208.020000;
      rmin  = 200.781000;
      rmax  = 200.981000;
   pcon->DefineSection(1, z,rmin,rmax);
      z     = -208.020000;
      rmin  = 200.028000;
      rmax  = 200.981000;
   pcon->DefineSection(2, z,rmin,rmax);
      z     = 208.020000;
      rmin  = 200.028000;
      rmax  = 200.981000;
   pcon->DefineSection(3, z,rmin,rmax);
      z     = 208.020000;
      rmin  = 200.781000;
      rmax  = 200.981000;
   pcon->DefineSection(4, z,rmin,rmax);
      z     = 211.900000;
      rmin  = 200.781000;
      rmax  = 200.981000;
   pcon->DefineSection(5, z,rmin,rmax);
   TGeoShape *pTONX_32 = pcon;
   // Volume: TONX
   pTONX_3ada390 = new TGeoVolume("TONX",pTONX_32, pMed66);
   pTONX_3ada390->SetVisLeaves(kTRUE);
   pTOFC_3ad9270->AddNode(pTONX_3ada390, 1);
   // Shape: TOAD type: TGeoTube
   rmin = 200.981000;
   rmax = 201.031000;
   dz   = 211.900000;
   TGeoShape *pTOAD_33 = new TGeoTube("TOAD",rmin,rmax,dz);
   // Volume: TOAD
   pTOAD_3ada790 = new TGeoVolume("TOAD",pTOAD_33, pMed63);
   pTOAD_3ada790->SetLineColor(880);
   pTOAD_3ada790->SetVisLeaves(kTRUE);
   pTOFC_3ad9270->AddNode(pTOAD_3ada790, 1);
   // Shape: TOIG type: TGeoTube
   rmin = 201.031000;
   rmax = 206.731000;
   dz   = 211.900000;
   TGeoShape *pTOIG_34 = new TGeoTube("TOIG",rmin,rmax,dz);
   // Volume: TOIG
   pTOIG_3adad30 = new TGeoVolume("TOIG",pTOIG_34, pMed68);
   pTOIG_3adad30->SetVisLeaves(kTRUE);
   pTOFC_3ad9270->AddNode(pTOIG_3adad30, 1);
   // Shape: TOHA type: TGeoTube
   rmin = 206.931000;
   rmax = 207.531000;
   dz   = 208.020000;
   TGeoShape *pTOHA_35 = new TGeoTube("TOHA",rmin,rmax,dz);
   // Volume: TOHA
   pTOHA_3adb420 = new TGeoVolume("TOHA",pTOHA_35, pMed70);
   pTOHA_3adb420->SetLineColor(880);
   pTOHA_3adb420->SetVisLeaves(kTRUE);
   pTOFC_3ad9270->AddNode(pTOHA_3adb420, 1);
   // Shape: GasAndSector type: TGeoPcon
   phi1  = 345.000000;
   dphi  = 30.000000;
   nz    = 2;
   TGeoPcon *pcon = new TGeoPcon("GasAndSector",phi1,dphi,nz);
      z     = 0.003810;
      rmin  = 47.969000;
      rmax  = 200.000000;
   pcon->DefineSection(0, z,rmin,rmax);
      z     = 218.280000;
      rmin  = 47.969000;
      rmax  = 200.000000;
   pcon->DefineSection(1, z,rmin,rmax);
   TGeoShape *pGasAndSector_212 = pcon;
   // Shape: InnerSectorItSelf type: TGeoPgon
   phi1    = 345.000143;
   dphi    = 29.999714;
   nedges = 1;
   nz      = 2;
   TGeoPgon *pgon = new TGeoPgon("InnerSectorItSelf",phi1,dphi,nedges,nz);
      z     = 209.898000;
      rmin  = 51.326773;
      rmax  = 120.854193;
   pgon->DefineSection(0, z,rmin,rmax);
      z     = 218.280000;
      rmin  = 51.326773;
      rmax  = 120.854193;
   pgon->DefineSection(1, z,rmin,rmax);
   TGeoShape *pInnerSectorItSelf_67 = pgon;
   // Shape: WireMountInnerLeft type: TGeoPara
   dx    = 0.825500;
   dy    = 34.763710;
   dz    = 1.701800;
   alpha = -14.999857;
   theta = 0.000000;
   phi   = 0.000000;
   TGeoShape *pWireMountInnerLeft_72 = new TGeoPara("WireMountInnerLeft",dx,dy,dz,alpha,theta,phi);
   pBoolNode = new TGeoUnion(pInnerSectorItSelf_67,pWireMountInnerLeft_72,0,pMatrix373);
   // Shape: TGeoCompositeShape type: TGeoCompositeShape
   TGeoShape *pTGeoCompositeShape_76 = new TGeoCompositeShape("TGeoCompositeShape", pBoolNode);
   pTGeoCompositeShape_76->SetTitle("InnerSectorItSelf+WireMountInnerLeft:WireMountTRInnerLeft");
   // Shape: WireMountInnerRight type: TGeoPara
   dx    = 0.825500;
   dy    = 34.763710;
   dz    = 1.701800;
   alpha = 14.999857;
   theta = 0.000000;
   phi   = 0.000000;
   TGeoShape *pWireMountInnerRight_74 = new TGeoPara("WireMountInnerRight",dx,dy,dz,alpha,theta,phi);
   pBoolNode = new TGeoUnion(pTGeoCompositeShape_76,pWireMountInnerRight_74,0,pMatrix375);
   // Shape: InnerSector type: TGeoCompositeShape
   TGeoShape *pInnerSector_75 = new TGeoCompositeShape("InnerSector", pBoolNode);
   pInnerSector_75->SetTitle("InnerSectorItSelf + WireMountInnerLeft:WireMountTRInnerLeft + WireMountInnerRight:WireMountTRInnerRight");
   // Shape: OuterSectorItSelf type: TGeoPgon
   phi1    = 345.000208;
   dphi    = 29.999584;
   nedges = 1;
   nz      = 2;
   TGeoPgon *pgon = new TGeoPgon("OuterSectorItSelf",phi1,dphi,nedges,nz);
      z     = 210.304400;
      rmin  = 121.153346;
      rmax  = 192.667046;
   pgon->DefineSection(0, z,rmin,rmax);
      z     = 218.280000;
      rmin  = 121.153346;
      rmax  = 192.667046;
   pgon->DefineSection(1, z,rmin,rmax);
   TGeoShape *pOuterSectorItSelf_169 = pgon;
   // Shape: WireMountOuterLeft type: TGeoPara
   dx    = 0.825500;
   dy    = 35.756850;
   dz    = 1.701800;
   alpha = -14.999792;
   theta = 0.000000;
   phi   = 0.000000;
   TGeoShape *pWireMountOuterLeft_174 = new TGeoPara("WireMountOuterLeft",dx,dy,dz,alpha,theta,phi);
   pBoolNode = new TGeoUnion(pOuterSectorItSelf_169,pWireMountOuterLeft_174,0,pMatrix583);
   // Shape: TGeoCompositeShape type: TGeoCompositeShape
   TGeoShape *pTGeoCompositeShape_178 = new TGeoCompositeShape("TGeoCompositeShape", pBoolNode);
   pTGeoCompositeShape_178->SetTitle("OuterSectorItSelf+WireMountOuterLeft:WireMountTROuterLeft");
   // Shape: WireMountOuterRight type: TGeoPara
   dx    = 0.825500;
   dy    = 35.756850;
   dz    = 1.701800;
   alpha = 14.999792;
   theta = 0.000000;
   phi   = 0.000000;
   TGeoShape *pWireMountOuterRight_176 = new TGeoPara("WireMountOuterRight",dx,dy,dz,alpha,theta,phi);
   pBoolNode = new TGeoUnion(pTGeoCompositeShape_178,pWireMountOuterRight_176,0,pMatrix585);
   // Shape: OuterSector type: TGeoCompositeShape
   TGeoShape *pOuterSector_177 = new TGeoCompositeShape("OuterSector", pBoolNode);
   pOuterSector_177->SetTitle("OuterSectorItSelf + WireMountOuterLeft:WireMountTROuterLeft + WireMountOuterRight:WireMountTROuterRight");
   pBoolNode = new TGeoUnion(pInnerSector_75,pOuterSector_177,pMatrix371,pMatrix581);
   // Shape: Sectors type: TGeoCompositeShape
   TGeoShape *pSectors_211 = new TGeoCompositeShape("Sectors", pBoolNode);
   pSectors_211->SetTitle("InnerSector:InnerShift + OuterSector:OuterShift");
   pBoolNode = new TGeoSubtraction(pGasAndSector_212,pSectors_211,0,0);
   // Shape: Gas type: TGeoCompositeShape
   TGeoShape *pGas_213 = new TGeoCompositeShape("Gas", pBoolNode);
   pGas_213->SetTitle("GasAndSector - Sectors");
   // Volume: TpcGas
   pTpcGas_3ba8860 = new TGeoVolume("TpcGas",pGas_213, pMed57);
   pTpcGas_3ba8860->SetVisibility(kFALSE);
   pTpcGas_3ba8860->SetVisLeaves(kTRUE);
   pTpcSectorWhole_3adb970->AddNode(pTpcGas_3ba8860, 1);
   // Shape: WheelRegion type: TGeoPcon
   phi1  = 345.000000;
   dphi  = 30.000000;
   nz    = 6;
   TGeoPcon *pcon = new TGeoPcon("WheelRegion",phi1,dphi,nz);
      z     = 218.280000;
      rmin  = 47.969000;
      rmax  = 201.000000;
   pcon->DefineSection(0, z,rmin,rmax);
      z     = 223.990000;
      rmin  = 47.969000;
      rmax  = 201.000000;
   pcon->DefineSection(1, z,rmin,rmax);
      z     = 223.990000;
      rmin  = 47.969000;
      rmax  = 206.750000;
   pcon->DefineSection(2, z,rmin,rmax);
      z     = 228.140000;
      rmin  = 47.969000;
      rmax  = 206.750000;
   pcon->DefineSection(3, z,rmin,rmax);
      z     = 228.140000;
      rmin  = 51.800000;
      rmax  = 206.750000;
   pcon->DefineSection(4, z,rmin,rmax);
      z     = 259.685000;
      rmin  = 51.800000;
      rmax  = 206.750000;
   pcon->DefineSection(5, z,rmin,rmax);
   TGeoShape *pWheelRegion_218 = pcon;
   pBoolNode = new TGeoUnion(pSectors_211,pWheelRegion_218,0,0);
   // Shape: SectorsAndWheel type: TGeoCompositeShape
   TGeoShape *pSectorsAndWheel_219 = new TGeoCompositeShape("SectorsAndWheel", pBoolNode);
   pSectorsAndWheel_219->SetTitle("Sectors + WheelRegion");
   // Volume: TpcSectorAndWheel
   pTpcSectorAndWheel_3baad90 = new TGeoVolume("TpcSectorAndWheel",pSectorsAndWheel_219, pMed56);
   pTpcSectorAndWheel_3baad90->SetLineColor(632);
   pTpcSectorAndWheel_3baad90->SetVisLeaves(kTRUE);
   pTpcSectorWhole_3adb970->AddNode(pTpcSectorAndWheel_3baad90, 1);
   // Assembly: TpcPadPlane
   pTpcPadPlane_3b4e570 = new TGeoVolumeAssembly("TpcPadPlane");
   pTpcPadPlane_3b4e570->SetVisLeaves(kTRUE);
   pTpcGas_3ba8860->AddNode(pTpcPadPlane_3b4e570, 1);
   // Assembly: TpcPadPlane
   pTpcPadPlane_39c34b0 = new TGeoVolumeAssembly("TpcPadPlane");
   pTpcPadPlane_39c34b0->SetVisLeaves(kTRUE);
   pTpcGas_3ba8860->AddNode(pTpcPadPlane_39c34b0, 2);
   // Shape: TpcSectorApronSheetCyl type: TGeoPcon
   phi1  = 345.000000;
   dphi  = 30.000000;
   nz    = 2;
   TGeoPcon *pcon = new TGeoPcon("TpcSectorApronSheetCyl",phi1,dphi,nz);
      z     = 209.290000;
      rmin  = 191.550000;
      rmax  = 198.230000;
   pcon->DefineSection(0, z,rmin,rmax);
      z     = 209.590000;
      rmin  = 191.550000;
      rmax  = 198.230000;
   pcon->DefineSection(1, z,rmin,rmax);
   TGeoShape *pTpcSectorApronSheetCyl_214 = pcon;
   // Shape: TpcSectorApronSheetFlat type: TGeoPgon
   phi1    = 345.000000;
   dphi    = 30.000000;
   nedges = 1;
   nz      = 2;
   TGeoPgon *pgon = new TGeoPgon("TpcSectorApronSheetFlat",phi1,dphi,nedges,nz);
      z     = 209.290000;
      rmin  = 185.023092;
      rmax  = 191.550000;
   pgon->DefineSection(0, z,rmin,rmax);
      z     = 209.590000;
      rmin  = 185.023092;
      rmax  = 191.550000;
   pgon->DefineSection(1, z,rmin,rmax);
   TGeoShape *pTpcSectorApronSheetFlat_215 = pgon;
   pBoolNode = new TGeoSubtraction(pTpcSectorApronSheetCyl_214,pTpcSectorApronSheetFlat_215,0,0);
   // Shape: TpcSectorApronSheet type: TGeoCompositeShape
   TGeoShape *pTpcSectorApronSheet_216 = new TGeoCompositeShape("TpcSectorApronSheet", pBoolNode);
   pTpcSectorApronSheet_216->SetTitle("TpcSectorApronSheetCyl - TpcSectorApronSheetFlat");
   // Volume: TpcSectorApronSheet
   pTpcSectorApronSheet_3ba96b0 = new TGeoVolume("TpcSectorApronSheet",pTpcSectorApronSheet_216, pMed67);
   pTpcSectorApronSheet_3ba96b0->SetLineColor(600);
   pTpcSectorApronSheet_3ba96b0->SetVisLeaves(kTRUE);
   pTpcGas_3ba8860->AddNodeOverlap(pTpcSectorApronSheet_3ba96b0, 1);
   // Shape: TpcSectorApronCylinder type: TGeoPgon
   phi1    = 345.000000;
   dphi    = 30.000000;
   nedges = 1;
   nz      = 2;
   TGeoPgon *pgon = new TGeoPgon("TpcSectorApronCylinder",phi1,dphi,nedges,nz);
      z     = 209.590000;
      rmin  = 191.150000;
      rmax  = 191.550000;
   pgon->DefineSection(0, z,rmin,rmax);
      z     = 218.280000;
      rmin  = 191.150000;
      rmax  = 191.550000;
   pgon->DefineSection(1, z,rmin,rmax);
   TGeoShape *pTpcSectorApronCylinder_217 = pgon;
   // Volume: TpcSectorApronCylinder
   pTpcSectorApronCylinder_3baa0d0 = new TGeoVolume("TpcSectorApronCylinder",pTpcSectorApronCylinder_217, pMed67);
   pTpcSectorApronCylinder_3baa0d0->SetLineColor(600);
   pTpcSectorApronCylinder_3baa0d0->SetVisLeaves(kTRUE);
   pTpcGas_3ba8860->AddNodeOverlap(pTpcSectorApronCylinder_3baa0d0, 1);
   // Shape: tpad type: TGeoBBox
   dx = 14.740000;
   dy = 0.575000;
   dz = 104.947095;
   TGeoShape *ptpad_42 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b503c0 = new TGeoVolume("tpad",ptpad_42, pMed58);
   ptpad_3b503c0->SetVisLeaves(kTRUE);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b503c0, 100001, pMatrix320);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b503c0, 1, pMatrix321);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b503c0, 200001, pMatrix322);
   // Shape: tpad type: TGeoBBox
   dx = 16.080000;
   dy = 0.575000;
   dz = 104.947095;
   TGeoShape *ptpad_44 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b55410 = new TGeoVolume("tpad",ptpad_44, pMed58);
   ptpad_3b55410->SetVisLeaves(kTRUE);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b55410, 100002, pMatrix324);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b55410, 2, pMatrix325);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b55410, 200002, pMatrix326);
   // Shape: tpad type: TGeoBBox
   dx = 17.420000;
   dy = 0.575000;
   dz = 104.947095;
   TGeoShape *ptpad_46 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b55bd0 = new TGeoVolume("tpad",ptpad_46, pMed58);
   ptpad_3b55bd0->SetVisLeaves(kTRUE);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b55bd0, 100003, pMatrix328);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b55bd0, 3, pMatrix329);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b55bd0, 200003, pMatrix330);
   // Shape: tpad type: TGeoBBox
   dx = 18.760000;
   dy = 0.575000;
   dz = 104.947095;
   TGeoShape *ptpad_48 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b56440 = new TGeoVolume("tpad",ptpad_48, pMed58);
   ptpad_3b56440->SetVisLeaves(kTRUE);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b56440, 100004, pMatrix332);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b56440, 4, pMatrix333);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b56440, 200004, pMatrix334);
   // Shape: tpad type: TGeoBBox
   dx = 19.765000;
   dy = 0.575000;
   dz = 104.947095;
   TGeoShape *ptpad_50 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b56cb0 = new TGeoVolume("tpad",ptpad_50, pMed58);
   ptpad_3b56cb0->SetVisLeaves(kTRUE);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b56cb0, 100005, pMatrix336);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b56cb0, 5, pMatrix337);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b56cb0, 200005, pMatrix338);
   // Shape: tpad type: TGeoBBox
   dx = 21.105000;
   dy = 0.575000;
   dz = 104.947095;
   TGeoShape *ptpad_52 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b57520 = new TGeoVolume("tpad",ptpad_52, pMed58);
   ptpad_3b57520->SetVisLeaves(kTRUE);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b57520, 100006, pMatrix340);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b57520, 6, pMatrix341);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b57520, 200006, pMatrix342);
   // Shape: tpad type: TGeoBBox
   dx = 22.445000;
   dy = 0.575000;
   dz = 104.947095;
   TGeoShape *ptpad_54 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b57e30 = new TGeoVolume("tpad",ptpad_54, pMed58);
   ptpad_3b57e30->SetVisLeaves(kTRUE);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b57e30, 100007, pMatrix344);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b57e30, 7, pMatrix345);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b57e30, 200007, pMatrix346);
   // Shape: tpad type: TGeoBBox
   dx = 23.785000;
   dy = 0.575000;
   dz = 104.947095;
   TGeoShape *ptpad_56 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b586a0 = new TGeoVolume("tpad",ptpad_56, pMed58);
   ptpad_3b586a0->SetVisLeaves(kTRUE);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b586a0, 100008, pMatrix348);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b586a0, 8, pMatrix349);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b586a0, 200008, pMatrix350);
   // Shape: tpad type: TGeoBBox
   dx = 25.125000;
   dy = 0.575000;
   dz = 104.947095;
   TGeoShape *ptpad_58 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b58f10 = new TGeoVolume("tpad",ptpad_58, pMed58);
   ptpad_3b58f10->SetVisLeaves(kTRUE);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b58f10, 100009, pMatrix352);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b58f10, 9, pMatrix353);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b58f10, 200009, pMatrix354);
   // Shape: tpad type: TGeoBBox
   dx = 26.465000;
   dy = 0.575000;
   dz = 104.947095;
   TGeoShape *ptpad_60 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b59780 = new TGeoVolume("tpad",ptpad_60, pMed58);
   ptpad_3b59780->SetVisLeaves(kTRUE);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b59780, 100010, pMatrix356);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b59780, 10, pMatrix357);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b59780, 200010, pMatrix358);
   // Shape: tpad type: TGeoBBox
   dx = 27.805000;
   dy = 0.575000;
   dz = 104.947095;
   TGeoShape *ptpad_62 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b59ff0 = new TGeoVolume("tpad",ptpad_62, pMed58);
   ptpad_3b59ff0->SetVisLeaves(kTRUE);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b59ff0, 100011, pMatrix360);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b59ff0, 11, pMatrix361);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b59ff0, 200011, pMatrix362);
   // Shape: tpad type: TGeoBBox
   dx = 29.145000;
   dy = 0.575000;
   dz = 104.947095;
   TGeoShape *ptpad_64 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b5a990 = new TGeoVolume("tpad",ptpad_64, pMed58);
   ptpad_3b5a990->SetVisLeaves(kTRUE);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b5a990, 100012, pMatrix364);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b5a990, 12, pMatrix365);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b5a990, 200012, pMatrix366);
   // Shape: tpad type: TGeoBBox
   dx = 30.485000;
   dy = 0.575000;
   dz = 104.947095;
   TGeoShape *ptpad_66 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b5b1d0 = new TGeoVolume("tpad",ptpad_66, pMed58);
   ptpad_3b5b1d0->SetVisLeaves(kTRUE);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b5b1d0, 100013, pMatrix368);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b5b1d0, 13, pMatrix369);
   pTpcPadPlane_3b4e570->AddNode(ptpad_3b5b1d0, 200013, pMatrix370);
   // Shape: GatingGrid type: TGeoBBox
   dx = 14.740000;
   dy = 0.575000;
   dz = 6.949000;
   TGeoShape *pGatingGrid_41 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b4fb80 = new TGeoVolume("GatingGrid",pGatingGrid_41, pMed57);
   pGatingGrid_3b4fb80->SetVisLeaves(kTRUE);
   ptpad_3b503c0->AddNode(pGatingGrid_3b4fb80, 1, pMatrix319);
   // Shape: GatingGrid type: TGeoBBox
   dx = 16.080000;
   dy = 0.575000;
   dz = 6.949000;
   TGeoShape *pGatingGrid_43 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b4f470 = new TGeoVolume("GatingGrid",pGatingGrid_43, pMed57);
   pGatingGrid_3b4f470->SetVisLeaves(kTRUE);
   ptpad_3b55410->AddNode(pGatingGrid_3b4f470, 1, pMatrix323);
   // Shape: GatingGrid type: TGeoBBox
   dx = 17.420000;
   dy = 0.575000;
   dz = 6.949000;
   TGeoShape *pGatingGrid_45 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b55a60 = new TGeoVolume("GatingGrid",pGatingGrid_45, pMed57);
   pGatingGrid_3b55a60->SetVisLeaves(kTRUE);
   ptpad_3b55bd0->AddNode(pGatingGrid_3b55a60, 1, pMatrix327);
   // Shape: GatingGrid type: TGeoBBox
   dx = 18.760000;
   dy = 0.575000;
   dz = 6.949000;
   TGeoShape *pGatingGrid_47 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b56270 = new TGeoVolume("GatingGrid",pGatingGrid_47, pMed57);
   pGatingGrid_3b56270->SetVisLeaves(kTRUE);
   ptpad_3b56440->AddNode(pGatingGrid_3b56270, 1, pMatrix331);
   // Shape: GatingGrid type: TGeoBBox
   dx = 19.765000;
   dy = 0.575000;
   dz = 6.949000;
   TGeoShape *pGatingGrid_49 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b56ae0 = new TGeoVolume("GatingGrid",pGatingGrid_49, pMed57);
   pGatingGrid_3b56ae0->SetVisLeaves(kTRUE);
   ptpad_3b56cb0->AddNode(pGatingGrid_3b56ae0, 1, pMatrix335);
   // Shape: GatingGrid type: TGeoBBox
   dx = 21.105000;
   dy = 0.575000;
   dz = 6.949000;
   TGeoShape *pGatingGrid_51 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b57350 = new TGeoVolume("GatingGrid",pGatingGrid_51, pMed57);
   pGatingGrid_3b57350->SetVisLeaves(kTRUE);
   ptpad_3b57520->AddNode(pGatingGrid_3b57350, 1, pMatrix339);
   // Shape: GatingGrid type: TGeoBBox
   dx = 22.445000;
   dy = 0.575000;
   dz = 6.949000;
   TGeoShape *pGatingGrid_53 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b57c60 = new TGeoVolume("GatingGrid",pGatingGrid_53, pMed57);
   pGatingGrid_3b57c60->SetVisLeaves(kTRUE);
   ptpad_3b57e30->AddNode(pGatingGrid_3b57c60, 1, pMatrix343);
   // Shape: GatingGrid type: TGeoBBox
   dx = 23.785000;
   dy = 0.575000;
   dz = 6.949000;
   TGeoShape *pGatingGrid_55 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b584d0 = new TGeoVolume("GatingGrid",pGatingGrid_55, pMed57);
   pGatingGrid_3b584d0->SetVisLeaves(kTRUE);
   ptpad_3b586a0->AddNode(pGatingGrid_3b584d0, 1, pMatrix347);
   // Shape: GatingGrid type: TGeoBBox
   dx = 25.125000;
   dy = 0.575000;
   dz = 6.949000;
   TGeoShape *pGatingGrid_57 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b58d40 = new TGeoVolume("GatingGrid",pGatingGrid_57, pMed57);
   pGatingGrid_3b58d40->SetVisLeaves(kTRUE);
   ptpad_3b58f10->AddNode(pGatingGrid_3b58d40, 1, pMatrix351);
   // Shape: GatingGrid type: TGeoBBox
   dx = 26.465000;
   dy = 0.575000;
   dz = 6.949000;
   TGeoShape *pGatingGrid_59 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b595b0 = new TGeoVolume("GatingGrid",pGatingGrid_59, pMed57);
   pGatingGrid_3b595b0->SetVisLeaves(kTRUE);
   ptpad_3b59780->AddNode(pGatingGrid_3b595b0, 1, pMatrix355);
   // Shape: GatingGrid type: TGeoBBox
   dx = 27.805000;
   dy = 0.575000;
   dz = 6.949000;
   TGeoShape *pGatingGrid_61 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b59e20 = new TGeoVolume("GatingGrid",pGatingGrid_61, pMed57);
   pGatingGrid_3b59e20->SetVisLeaves(kTRUE);
   ptpad_3b59ff0->AddNode(pGatingGrid_3b59e20, 1, pMatrix359);
   // Shape: GatingGrid type: TGeoBBox
   dx = 29.145000;
   dy = 0.575000;
   dz = 6.949000;
   TGeoShape *pGatingGrid_63 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b5a820 = new TGeoVolume("GatingGrid",pGatingGrid_63, pMed57);
   pGatingGrid_3b5a820->SetVisLeaves(kTRUE);
   ptpad_3b5a990->AddNode(pGatingGrid_3b5a820, 1, pMatrix363);
   // Shape: GatingGrid type: TGeoBBox
   dx = 30.485000;
   dy = 0.575000;
   dz = 6.949000;
   TGeoShape *pGatingGrid_65 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b5b000 = new TGeoVolume("GatingGrid",pGatingGrid_65, pMed57);
   pGatingGrid_3b5b000->SetVisLeaves(kTRUE);
   ptpad_3b5b1d0->AddNode(pGatingGrid_3b5b000, 1, pMatrix367);
   // Shape: tpad type: TGeoBBox
   dx = 32.830000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_106 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_39c2cf0 = new TGeoVolume("tpad",ptpad_106, pMed58);
   ptpad_39c2cf0->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_39c2cf0, 100014, pMatrix516);
   pTpcPadPlane_39c34b0->AddNode(ptpad_39c2cf0, 14, pMatrix517);
   // Shape: tpad type: TGeoBBox
   dx = 33.500000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_108 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_39c3850 = new TGeoVolume("tpad",ptpad_108, pMed58);
   ptpad_39c3850->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_39c3850, 15, pMatrix519);
   // Shape: tpad type: TGeoBBox
   dx = 34.170000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_110 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b83980 = new TGeoVolume("tpad",ptpad_110, pMed58);
   ptpad_3b83980->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b83980, 16, pMatrix521);
   // Shape: tpad type: TGeoBBox
   dx = 34.840000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_112 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b840d0 = new TGeoVolume("tpad",ptpad_112, pMed58);
   ptpad_3b840d0->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b840d0, 17, pMatrix523);
   // Shape: tpad type: TGeoBBox
   dx = 35.510000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_114 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b84730 = new TGeoVolume("tpad",ptpad_114, pMed58);
   ptpad_3b84730->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b84730, 18, pMatrix525);
   // Shape: tpad type: TGeoBBox
   dx = 35.510000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_116 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b84da0 = new TGeoVolume("tpad",ptpad_116, pMed58);
   ptpad_3b84da0->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b84da0, 19, pMatrix527);
   // Shape: tpad type: TGeoBBox
   dx = 36.180000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_118 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b85410 = new TGeoVolume("tpad",ptpad_118, pMed58);
   ptpad_3b85410->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b85410, 20, pMatrix529);
   // Shape: tpad type: TGeoBBox
   dx = 36.850000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_120 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b85a80 = new TGeoVolume("tpad",ptpad_120, pMed58);
   ptpad_3b85a80->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b85a80, 21, pMatrix531);
   // Shape: tpad type: TGeoBBox
   dx = 37.520000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_122 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b860f0 = new TGeoVolume("tpad",ptpad_122, pMed58);
   ptpad_3b860f0->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b860f0, 22, pMatrix533);
   // Shape: tpad type: TGeoBBox
   dx = 37.520000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_124 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b86760 = new TGeoVolume("tpad",ptpad_124, pMed58);
   ptpad_3b86760->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b86760, 23, pMatrix535);
   // Shape: tpad type: TGeoBBox
   dx = 38.190000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_126 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b86dd0 = new TGeoVolume("tpad",ptpad_126, pMed58);
   ptpad_3b86dd0->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b86dd0, 24, pMatrix537);
   // Shape: tpad type: TGeoBBox
   dx = 38.860000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_128 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b87440 = new TGeoVolume("tpad",ptpad_128, pMed58);
   ptpad_3b87440->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b87440, 25, pMatrix539);
   // Shape: tpad type: TGeoBBox
   dx = 39.530000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_130 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b87ab0 = new TGeoVolume("tpad",ptpad_130, pMed58);
   ptpad_3b87ab0->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b87ab0, 26, pMatrix541);
   // Shape: tpad type: TGeoBBox
   dx = 40.200000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_132 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b88120 = new TGeoVolume("tpad",ptpad_132, pMed58);
   ptpad_3b88120->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b88120, 27, pMatrix543);
   // Shape: tpad type: TGeoBBox
   dx = 40.870000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_134 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b88790 = new TGeoVolume("tpad",ptpad_134, pMed58);
   ptpad_3b88790->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b88790, 28, pMatrix545);
   // Shape: tpad type: TGeoBBox
   dx = 40.870000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_136 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b88e00 = new TGeoVolume("tpad",ptpad_136, pMed58);
   ptpad_3b88e00->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b88e00, 29, pMatrix547);
   // Shape: tpad type: TGeoBBox
   dx = 41.540000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_138 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b89500 = new TGeoVolume("tpad",ptpad_138, pMed58);
   ptpad_3b89500->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b89500, 30, pMatrix549);
   // Shape: tpad type: TGeoBBox
   dx = 42.210000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_140 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b89b70 = new TGeoVolume("tpad",ptpad_140, pMed58);
   ptpad_3b89b70->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b89b70, 31, pMatrix551);
   // Shape: tpad type: TGeoBBox
   dx = 42.880000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_142 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b8a1e0 = new TGeoVolume("tpad",ptpad_142, pMed58);
   ptpad_3b8a1e0->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b8a1e0, 32, pMatrix553);
   // Shape: tpad type: TGeoBBox
   dx = 42.880000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_144 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b8a9e0 = new TGeoVolume("tpad",ptpad_144, pMed58);
   ptpad_3b8a9e0->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b8a9e0, 33, pMatrix555);
   // Shape: tpad type: TGeoBBox
   dx = 43.550000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_146 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b8b0f0 = new TGeoVolume("tpad",ptpad_146, pMed58);
   ptpad_3b8b0f0->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b8b0f0, 34, pMatrix557);
   // Shape: tpad type: TGeoBBox
   dx = 44.220000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_148 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b8b730 = new TGeoVolume("tpad",ptpad_148, pMed58);
   ptpad_3b8b730->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b8b730, 35, pMatrix559);
   // Shape: tpad type: TGeoBBox
   dx = 44.890000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_150 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b8bda0 = new TGeoVolume("tpad",ptpad_150, pMed58);
   ptpad_3b8bda0->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b8bda0, 36, pMatrix561);
   // Shape: tpad type: TGeoBBox
   dx = 45.560000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_152 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b8c410 = new TGeoVolume("tpad",ptpad_152, pMed58);
   ptpad_3b8c410->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b8c410, 37, pMatrix563);
   // Shape: tpad type: TGeoBBox
   dx = 46.230000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_154 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b8ca80 = new TGeoVolume("tpad",ptpad_154, pMed58);
   ptpad_3b8ca80->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b8ca80, 38, pMatrix565);
   // Shape: tpad type: TGeoBBox
   dx = 46.230000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_156 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b8d0f0 = new TGeoVolume("tpad",ptpad_156, pMed58);
   ptpad_3b8d0f0->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b8d0f0, 39, pMatrix567);
   // Shape: tpad type: TGeoBBox
   dx = 46.900000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_158 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b8d760 = new TGeoVolume("tpad",ptpad_158, pMed58);
   ptpad_3b8d760->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b8d760, 40, pMatrix569);
   // Shape: tpad type: TGeoBBox
   dx = 47.570000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_160 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b8ddd0 = new TGeoVolume("tpad",ptpad_160, pMed58);
   ptpad_3b8ddd0->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b8ddd0, 41, pMatrix571);
   // Shape: tpad type: TGeoBBox
   dx = 48.240000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_162 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b8e440 = new TGeoVolume("tpad",ptpad_162, pMed58);
   ptpad_3b8e440->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b8e440, 42, pMatrix573);
   // Shape: tpad type: TGeoBBox
   dx = 48.240000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_164 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b8eab0 = new TGeoVolume("tpad",ptpad_164, pMed58);
   ptpad_3b8eab0->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b8eab0, 43, pMatrix575);
   // Shape: tpad type: TGeoBBox
   dx = 48.240000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_166 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b8f120 = new TGeoVolume("tpad",ptpad_166, pMed58);
   ptpad_3b8f120->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b8f120, 44, pMatrix577);
   // Shape: tpad type: TGeoBBox
   dx = 48.240000;
   dy = 0.975000;
   dz = 105.150295;
   TGeoShape *ptpad_168 = new TGeoBBox("tpad", dx,dy,dz);
   // Volume: tpad
   ptpad_3b8f790 = new TGeoVolume("tpad",ptpad_168, pMed58);
   ptpad_3b8f790->SetVisLeaves(kTRUE);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b8f790, 45, pMatrix579);
   pTpcPadPlane_39c34b0->AddNode(ptpad_3b8f790, 200045, pMatrix580);
   // Shape: GatingGrid type: TGeoBBox
   dx = 32.830000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_105 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_39c39f0 = new TGeoVolume("GatingGrid",pGatingGrid_105, pMed57);
   pGatingGrid_39c39f0->SetVisLeaves(kTRUE);
   ptpad_39c2cf0->AddNode(pGatingGrid_39c39f0, 1, pMatrix515);
   // Shape: GatingGrid type: TGeoBBox
   dx = 33.500000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_107 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_39c3730 = new TGeoVolume("GatingGrid",pGatingGrid_107, pMed57);
   pGatingGrid_39c3730->SetVisLeaves(kTRUE);
   ptpad_39c3850->AddNode(pGatingGrid_39c3730, 1, pMatrix518);
   // Shape: GatingGrid type: TGeoBBox
   dx = 34.170000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_109 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b837b0 = new TGeoVolume("GatingGrid",pGatingGrid_109, pMed57);
   pGatingGrid_3b837b0->SetVisLeaves(kTRUE);
   ptpad_3b83980->AddNode(pGatingGrid_3b837b0, 1, pMatrix520);
   // Shape: GatingGrid type: TGeoBBox
   dx = 34.840000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_111 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b83e20 = new TGeoVolume("GatingGrid",pGatingGrid_111, pMed57);
   pGatingGrid_3b83e20->SetVisLeaves(kTRUE);
   ptpad_3b840d0->AddNode(pGatingGrid_3b83e20, 1, pMatrix522);
   // Shape: GatingGrid type: TGeoBBox
   dx = 35.510000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_113 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b845c0 = new TGeoVolume("GatingGrid",pGatingGrid_113, pMed57);
   pGatingGrid_3b845c0->SetVisLeaves(kTRUE);
   ptpad_3b84730->AddNode(pGatingGrid_3b845c0, 1, pMatrix524);
   // Shape: GatingGrid type: TGeoBBox
   dx = 35.510000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_115 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b84bd0 = new TGeoVolume("GatingGrid",pGatingGrid_115, pMed57);
   pGatingGrid_3b84bd0->SetVisLeaves(kTRUE);
   ptpad_3b84da0->AddNode(pGatingGrid_3b84bd0, 1, pMatrix526);
   // Shape: GatingGrid type: TGeoBBox
   dx = 36.180000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_117 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b85240 = new TGeoVolume("GatingGrid",pGatingGrid_117, pMed57);
   pGatingGrid_3b85240->SetVisLeaves(kTRUE);
   ptpad_3b85410->AddNode(pGatingGrid_3b85240, 1, pMatrix528);
   // Shape: GatingGrid type: TGeoBBox
   dx = 36.850000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_119 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b858b0 = new TGeoVolume("GatingGrid",pGatingGrid_119, pMed57);
   pGatingGrid_3b858b0->SetVisLeaves(kTRUE);
   ptpad_3b85a80->AddNode(pGatingGrid_3b858b0, 1, pMatrix530);
   // Shape: GatingGrid type: TGeoBBox
   dx = 37.520000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_121 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b85f20 = new TGeoVolume("GatingGrid",pGatingGrid_121, pMed57);
   pGatingGrid_3b85f20->SetVisLeaves(kTRUE);
   ptpad_3b860f0->AddNode(pGatingGrid_3b85f20, 1, pMatrix532);
   // Shape: GatingGrid type: TGeoBBox
   dx = 37.520000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_123 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b86590 = new TGeoVolume("GatingGrid",pGatingGrid_123, pMed57);
   pGatingGrid_3b86590->SetVisLeaves(kTRUE);
   ptpad_3b86760->AddNode(pGatingGrid_3b86590, 1, pMatrix534);
   // Shape: GatingGrid type: TGeoBBox
   dx = 38.190000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_125 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b86c00 = new TGeoVolume("GatingGrid",pGatingGrid_125, pMed57);
   pGatingGrid_3b86c00->SetVisLeaves(kTRUE);
   ptpad_3b86dd0->AddNode(pGatingGrid_3b86c00, 1, pMatrix536);
   // Shape: GatingGrid type: TGeoBBox
   dx = 38.860000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_127 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b87270 = new TGeoVolume("GatingGrid",pGatingGrid_127, pMed57);
   pGatingGrid_3b87270->SetVisLeaves(kTRUE);
   ptpad_3b87440->AddNode(pGatingGrid_3b87270, 1, pMatrix538);
   // Shape: GatingGrid type: TGeoBBox
   dx = 39.530000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_129 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b878e0 = new TGeoVolume("GatingGrid",pGatingGrid_129, pMed57);
   pGatingGrid_3b878e0->SetVisLeaves(kTRUE);
   ptpad_3b87ab0->AddNode(pGatingGrid_3b878e0, 1, pMatrix540);
   // Shape: GatingGrid type: TGeoBBox
   dx = 40.200000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_131 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b87f50 = new TGeoVolume("GatingGrid",pGatingGrid_131, pMed57);
   pGatingGrid_3b87f50->SetVisLeaves(kTRUE);
   ptpad_3b88120->AddNode(pGatingGrid_3b87f50, 1, pMatrix542);
   // Shape: GatingGrid type: TGeoBBox
   dx = 40.870000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_133 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b885c0 = new TGeoVolume("GatingGrid",pGatingGrid_133, pMed57);
   pGatingGrid_3b885c0->SetVisLeaves(kTRUE);
   ptpad_3b88790->AddNode(pGatingGrid_3b885c0, 1, pMatrix544);
   // Shape: GatingGrid type: TGeoBBox
   dx = 40.870000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_135 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b88c30 = new TGeoVolume("GatingGrid",pGatingGrid_135, pMed57);
   pGatingGrid_3b88c30->SetVisLeaves(kTRUE);
   ptpad_3b88e00->AddNode(pGatingGrid_3b88c30, 1, pMatrix546);
   // Shape: GatingGrid type: TGeoBBox
   dx = 41.540000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_137 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b89330 = new TGeoVolume("GatingGrid",pGatingGrid_137, pMed57);
   pGatingGrid_3b89330->SetVisLeaves(kTRUE);
   ptpad_3b89500->AddNode(pGatingGrid_3b89330, 1, pMatrix548);
   // Shape: GatingGrid type: TGeoBBox
   dx = 42.210000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_139 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b899a0 = new TGeoVolume("GatingGrid",pGatingGrid_139, pMed57);
   pGatingGrid_3b899a0->SetVisLeaves(kTRUE);
   ptpad_3b89b70->AddNode(pGatingGrid_3b899a0, 1, pMatrix550);
   // Shape: GatingGrid type: TGeoBBox
   dx = 42.880000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_141 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b8a010 = new TGeoVolume("GatingGrid",pGatingGrid_141, pMed57);
   pGatingGrid_3b8a010->SetVisLeaves(kTRUE);
   ptpad_3b8a1e0->AddNode(pGatingGrid_3b8a010, 1, pMatrix552);
   // Shape: GatingGrid type: TGeoBBox
   dx = 42.880000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_143 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b8a680 = new TGeoVolume("GatingGrid",pGatingGrid_143, pMed57);
   pGatingGrid_3b8a680->SetVisLeaves(kTRUE);
   ptpad_3b8a9e0->AddNode(pGatingGrid_3b8a680, 1, pMatrix554);
   // Shape: GatingGrid type: TGeoBBox
   dx = 43.550000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_145 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b8af80 = new TGeoVolume("GatingGrid",pGatingGrid_145, pMed57);
   pGatingGrid_3b8af80->SetVisLeaves(kTRUE);
   ptpad_3b8b0f0->AddNode(pGatingGrid_3b8af80, 1, pMatrix556);
   // Shape: GatingGrid type: TGeoBBox
   dx = 44.220000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_147 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b8b560 = new TGeoVolume("GatingGrid",pGatingGrid_147, pMed57);
   pGatingGrid_3b8b560->SetVisLeaves(kTRUE);
   ptpad_3b8b730->AddNode(pGatingGrid_3b8b560, 1, pMatrix558);
   // Shape: GatingGrid type: TGeoBBox
   dx = 44.890000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_149 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b8bbd0 = new TGeoVolume("GatingGrid",pGatingGrid_149, pMed57);
   pGatingGrid_3b8bbd0->SetVisLeaves(kTRUE);
   ptpad_3b8bda0->AddNode(pGatingGrid_3b8bbd0, 1, pMatrix560);
   // Shape: GatingGrid type: TGeoBBox
   dx = 45.560000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_151 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b8c240 = new TGeoVolume("GatingGrid",pGatingGrid_151, pMed57);
   pGatingGrid_3b8c240->SetVisLeaves(kTRUE);
   ptpad_3b8c410->AddNode(pGatingGrid_3b8c240, 1, pMatrix562);
   // Shape: GatingGrid type: TGeoBBox
   dx = 46.230000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_153 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b8c8b0 = new TGeoVolume("GatingGrid",pGatingGrid_153, pMed57);
   pGatingGrid_3b8c8b0->SetVisLeaves(kTRUE);
   ptpad_3b8ca80->AddNode(pGatingGrid_3b8c8b0, 1, pMatrix564);
   // Shape: GatingGrid type: TGeoBBox
   dx = 46.230000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_155 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b8cf20 = new TGeoVolume("GatingGrid",pGatingGrid_155, pMed57);
   pGatingGrid_3b8cf20->SetVisLeaves(kTRUE);
   ptpad_3b8d0f0->AddNode(pGatingGrid_3b8cf20, 1, pMatrix566);
   // Shape: GatingGrid type: TGeoBBox
   dx = 46.900000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_157 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b8d590 = new TGeoVolume("GatingGrid",pGatingGrid_157, pMed57);
   pGatingGrid_3b8d590->SetVisLeaves(kTRUE);
   ptpad_3b8d760->AddNode(pGatingGrid_3b8d590, 1, pMatrix568);
   // Shape: GatingGrid type: TGeoBBox
   dx = 47.570000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_159 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b8dc00 = new TGeoVolume("GatingGrid",pGatingGrid_159, pMed57);
   pGatingGrid_3b8dc00->SetVisLeaves(kTRUE);
   ptpad_3b8ddd0->AddNode(pGatingGrid_3b8dc00, 1, pMatrix570);
   // Shape: GatingGrid type: TGeoBBox
   dx = 48.240000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_161 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b8e270 = new TGeoVolume("GatingGrid",pGatingGrid_161, pMed57);
   pGatingGrid_3b8e270->SetVisLeaves(kTRUE);
   ptpad_3b8e440->AddNode(pGatingGrid_3b8e270, 1, pMatrix572);
   // Shape: GatingGrid type: TGeoBBox
   dx = 48.240000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_163 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b8e8e0 = new TGeoVolume("GatingGrid",pGatingGrid_163, pMed57);
   pGatingGrid_3b8e8e0->SetVisLeaves(kTRUE);
   ptpad_3b8eab0->AddNode(pGatingGrid_3b8e8e0, 1, pMatrix574);
   // Shape: GatingGrid type: TGeoBBox
   dx = 48.240000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_165 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b8ef50 = new TGeoVolume("GatingGrid",pGatingGrid_165, pMed57);
   pGatingGrid_3b8ef50->SetVisLeaves(kTRUE);
   ptpad_3b8f120->AddNode(pGatingGrid_3b8ef50, 1, pMatrix576);
   // Shape: GatingGrid type: TGeoBBox
   dx = 48.240000;
   dy = 0.975000;
   dz = 6.952200;
   TGeoShape *pGatingGrid_167 = new TGeoBBox("GatingGrid", dx,dy,dz);
   // Volume: GatingGrid
   pGatingGrid_3b8f5c0 = new TGeoVolume("GatingGrid",pGatingGrid_167, pMed57);
   pGatingGrid_3b8f5c0->SetVisLeaves(kTRUE);
   ptpad_3b8f790->AddNode(pGatingGrid_3b8f5c0, 1, pMatrix578);
   // Assembly: TpcInnerSectorAssembly
   pTpcInnerSectorAssembly_3b63fa0 = new TGeoVolumeAssembly("TpcInnerSectorAssembly");
   pTpcInnerSectorAssembly_3b63fa0->SetLineColor(632);
   pTpcInnerSectorAssembly_3b63fa0->SetVisLeaves(kTRUE);
   pTpcSectorAndWheel_3baad90->AddNode(pTpcInnerSectorAssembly_3b63fa0, 1, pMatrix371);
   // Assembly: TpcWheelInnerAssembly
   pTpcWheelInnerAssembly_3b64350 = new TGeoVolumeAssembly("TpcWheelInnerAssembly");
   pTpcWheelInnerAssembly_3b64350->SetVisLeaves(kTRUE);
   pTpcSectorAndWheel_3baad90->AddNode(pTpcWheelInnerAssembly_3b64350, 1);
   // Assembly: TpcOuterSectorAssembly
   pTpcOuterSectorAssembly_3b8ffa0 = new TGeoVolumeAssembly("TpcOuterSectorAssembly");
   pTpcOuterSectorAssembly_3b8ffa0->SetLineColor(632);
   pTpcOuterSectorAssembly_3b8ffa0->SetVisLeaves(kTRUE);
   pTpcSectorAndWheel_3baad90->AddNode(pTpcOuterSectorAssembly_3b8ffa0, 2, pMatrix581);
   // Assembly: TpcWheelOuterAssembly
   pTpcWheelOuterAssembly_3b90270 = new TGeoVolumeAssembly("TpcWheelOuterAssembly");
   pTpcWheelOuterAssembly_3b90270->SetVisLeaves(kTRUE);
   pTpcSectorAndWheel_3baad90->AddNode(pTpcWheelOuterAssembly_3b90270, 2);
   // Shape: WheelBottom type: TGeoPcon
   phi1  = 345.000000;
   dphi  = 30.000000;
   nz    = 4;
   TGeoPcon *pcon = new TGeoPcon("WheelBottom",phi1,dphi,nz);
      z     = 218.280000;
      rmin  = 49.047400;
      rmax  = 54.610000;
   pcon->DefineSection(0, z,rmin,rmax);
      z     = 227.170000;
      rmin  = 49.047400;
      rmax  = 54.610000;
   pcon->DefineSection(1, z,rmin,rmax);
      z     = 227.170000;
      rmin  = 52.647400;
      rmax  = 54.610000;
   pcon->DefineSection(2, z,rmin,rmax);
      z     = 229.710000;
      rmin  = 52.647400;
      rmax  = 54.610000;
   pcon->DefineSection(3, z,rmin,rmax);
   TGeoShape *pWheelBottom_220 = pcon;
   // Volume: WheelBottom
   pWheelBottom_3baba00 = new TGeoVolume("WheelBottom",pWheelBottom_220, pMed67);
   pWheelBottom_3baba00->SetLineColor(600);
   pWheelBottom_3baba00->SetVisLeaves(kTRUE);
   pTpcSectorAndWheel_3baad90->AddNode(pWheelBottom_3baba00, 1);
   // Shape: WheelOuterPcon type: TGeoPcon
   phi1  = 345.000000;
   dphi  = 30.000000;
   nz    = 4;
   TGeoPcon *pcon = new TGeoPcon("WheelOuterPcon",phi1,dphi,nz);
      z     = 218.280000;
      rmin  = 193.276220;
      rmax  = 201.000000;
   pcon->DefineSection(0, z,rmin,rmax);
      z     = 223.990000;
      rmin  = 193.276220;
      rmax  = 201.000000;
   pcon->DefineSection(1, z,rmin,rmax);
      z     = 223.990000;
      rmin  = 193.276220;
      rmax  = 206.750000;
   pcon->DefineSection(2, z,rmin,rmax);
      z     = 229.710000;
      rmin  = 193.276220;
      rmax  = 206.750000;
   pcon->DefineSection(3, z,rmin,rmax);
   TGeoShape *pWheelOuterPcon_221 = pcon;
   // Shape: WheelOuterPgon type: TGeoPgon
   phi1    = 345.000000;
   dphi    = 30.000000;
   nedges = 1;
   nz      = 2;
   TGeoPgon *pgon = new TGeoPgon("WheelOuterPgon",phi1,dphi,nedges,nz);
      z     = 218.280000;
      rmin  = 186.690493;
      rmax  = 193.276220;
   pgon->DefineSection(0, z,rmin,rmax);
      z     = 229.710000;
      rmin  = 186.690493;
      rmax  = 193.276220;
   pgon->DefineSection(1, z,rmin,rmax);
   TGeoShape *pWheelOuterPgon_222 = pgon;
   pBoolNode = new TGeoSubtraction(pWheelOuterPcon_221,pWheelOuterPgon_222,0,0);
   // Shape: WheelOuterRing type: TGeoCompositeShape
   TGeoShape *pWheelOuterRing_223 = new TGeoCompositeShape("WheelOuterRing", pBoolNode);
   pWheelOuterRing_223->SetTitle("WheelOuterPcon - WheelOuterPgon");
   // Volume: WheelOuterRing
   pWheelOuterRing_3baca00 = new TGeoVolume("WheelOuterRing",pWheelOuterRing_223, pMed67);
   pWheelOuterRing_3baca00->SetVisLeaves(kTRUE);
   pTpcSectorAndWheel_3baad90->AddNode(pWheelOuterRing_3baca00, 1);
   // Shape: TpcWheelTopRib type: TGeoPgon
   phi1    = 345.000000;
   dphi    = 30.000000;
   nedges = 1;
   nz      = 2;
   TGeoPgon *pgon = new TGeoPgon("TpcWheelTopRib",phi1,dphi,nedges,nz);
      z     = 218.280000;
      rmin  = 190.426220;
      rmax  = 193.276220;
   pgon->DefineSection(0, z,rmin,rmax);
      z     = 219.580000;
      rmin  = 190.426220;
      rmax  = 193.276220;
   pgon->DefineSection(1, z,rmin,rmax);
   TGeoShape *pTpcWheelTopRib_224 = pgon;
   // Volume: TpcWheelTopRib
   pTpcWheelTopRib_3bad640 = new TGeoVolume("TpcWheelTopRib",pTpcWheelTopRib_224, pMed67);
   pTpcWheelTopRib_3bad640->SetLineColor(600);
   pTpcWheelTopRib_3bad640->SetVisLeaves(kTRUE);
   pTpcSectorAndWheel_3baad90->AddNode(pTpcWheelTopRib_3bad640, 1);
   // Shape: TpcWheelMiddleRib type: TGeoPgon
   phi1    = 345.000000;
   dphi    = 30.000000;
   nedges = 1;
   nz      = 4;
   TGeoPgon *pgon = new TGeoPgon("TpcWheelMiddleRib",phi1,dphi,nedges,nz);
      z     = 218.280000;
      rmin  = 117.782180;
      rmax  = 125.382180;
   pgon->DefineSection(0, z,rmin,rmax);
      z     = 219.580000;
      rmin  = 117.782180;
      rmax  = 125.382180;
   pgon->DefineSection(1, z,rmin,rmax);
      z     = 219.580000;
      rmin  = 120.632180;
      rmax  = 122.532180;
   pgon->DefineSection(2, z,rmin,rmax);
      z     = 229.710000;
      rmin  = 120.632180;
      rmax  = 122.532180;
   pgon->DefineSection(3, z,rmin,rmax);
   TGeoShape *pTpcWheelMiddleRib_225 = pgon;
   // Volume: TpcWheelMiddleRib
   pTpcWheelMiddleRib_3badb80 = new TGeoVolume("TpcWheelMiddleRib",pTpcWheelMiddleRib_225, pMed67);
   pTpcWheelMiddleRib_3badb80->SetLineColor(600);
   pTpcWheelMiddleRib_3badb80->SetVisLeaves(kTRUE);
   pTpcSectorAndWheel_3baad90->AddNode(pTpcWheelMiddleRib_3badb80, 2);
   // Assembly: TpcRDOAssembly
   pTpcRDOAssembly_3bafd70 = new TGeoVolumeAssembly("TpcRDOAssembly");
   pTpcRDOAssembly_3bafd70->SetVisLeaves(kTRUE);
   pTpcSectorAndWheel_3baad90->AddNode(pTpcRDOAssembly_3bafd70, 1);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 48.101613;
   dx2 = 48.580068;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_234 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3bb1fe0 = new TGeoVolume("CoolingTube",pCoolingTube_234, pMed65);
   pCoolingTube_3bb1fe0->SetLineColor(880);
   pCoolingTube_3bb1fe0->SetVisLeaves(kTRUE);
   pTpcSectorAndWheel_3baad90->AddNode(pCoolingTube_3bb1fe0, 3, pMatrix887);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 43.814426;
   dx2 = 44.292881;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_235 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3bb1dd0 = new TGeoVolume("CoolingTube",pCoolingTube_235, pMed65);
   pCoolingTube_3bb1dd0->SetLineColor(880);
   pCoolingTube_3bb1dd0->SetVisLeaves(kTRUE);
   pTpcSectorAndWheel_3baad90->AddNode(pCoolingTube_3bb1dd0, 4, pMatrix889);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 39.527239;
   dx2 = 40.005694;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_236 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3bb2780 = new TGeoVolume("CoolingTube",pCoolingTube_236, pMed65);
   pCoolingTube_3bb2780->SetLineColor(880);
   pCoolingTube_3bb2780->SetVisLeaves(kTRUE);
   pTpcSectorAndWheel_3baad90->AddNode(pCoolingTube_3bb2780, 5, pMatrix892);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 35.240052;
   dx2 = 35.718507;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_237 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3bb2c00 = new TGeoVolume("CoolingTube",pCoolingTube_237, pMed65);
   pCoolingTube_3bb2c00->SetLineColor(880);
   pCoolingTube_3bb2c00->SetVisLeaves(kTRUE);
   pTpcSectorAndWheel_3baad90->AddNode(pCoolingTube_3bb2c00, 6, pMatrix895);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 30.765300;
   dx2 = 31.243756;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_238 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3bb3080 = new TGeoVolume("CoolingTube",pCoolingTube_238, pMed65);
   pCoolingTube_3bb3080->SetLineColor(880);
   pCoolingTube_3bb3080->SetVisLeaves(kTRUE);
   pTpcSectorAndWheel_3baad90->AddNode(pCoolingTube_3bb3080, 7, pMatrix898);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 26.746062;
   dx2 = 27.224518;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_239 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3bb3560 = new TGeoVolume("CoolingTube",pCoolingTube_239, pMed65);
   pCoolingTube_3bb3560->SetLineColor(880);
   pCoolingTube_3bb3560->SetVisLeaves(kTRUE);
   pTpcSectorAndWheel_3baad90->AddNode(pCoolingTube_3bb3560, 8, pMatrix901);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 25.808240;
   dx2 = 26.286695;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_240 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3bb3a40 = new TGeoVolume("CoolingTube",pCoolingTube_240, pMed65);
   pCoolingTube_3bb3a40->SetLineColor(880);
   pCoolingTube_3bb3a40->SetVisLeaves(kTRUE);
   pTpcSectorAndWheel_3baad90->AddNode(pCoolingTube_3bb3a40, 9, pMatrix904);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 21.922977;
   dx2 = 22.401432;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_241 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3bb3e30 = new TGeoVolume("CoolingTube",pCoolingTube_241, pMed65);
   pCoolingTube_3bb3e30->SetLineColor(880);
   pCoolingTube_3bb3e30->SetVisLeaves(kTRUE);
   pTpcSectorAndWheel_3baad90->AddNode(pCoolingTube_3bb3e30, 10, pMatrix906);
   // Shape: Cables type: TGeoPara
   dx    = 2.250000;
   dy    = 69.333110;
   dz    = 4.500000;
   alpha = -15.000000;
   theta = 0.000000;
   phi   = 0.000000;
   TGeoShape *pCables_242 = new TGeoPara("Cables",dx,dy,dz,alpha,theta,phi);
   // Volume: Cables
   pCables_3bb49d0 = new TGeoVolume("Cables",pCables_242, pMed255);
   pCables_3bb49d0->SetLineColor(416);
   pCables_3bb49d0->SetVisLeaves(kTRUE);
   pTpcSectorAndWheel_3baad90->AddNode(pCables_3bb49d0, 1, pMatrix908);
   // Shape: Cables type: TGeoPara
   dx    = 2.250000;
   dy    = 69.333110;
   dz    = 4.500000;
   alpha = 15.000000;
   theta = 0.000000;
   phi   = 0.000000;
   TGeoShape *pCables_243 = new TGeoPara("Cables",dx,dy,dz,alpha,theta,phi);
   // Volume: Cables
   pCables_3bb47c0 = new TGeoVolume("Cables",pCables_243, pMed255);
   pCables_3bb47c0->SetLineColor(416);
   pCables_3bb47c0->SetVisLeaves(kTRUE);
   pTpcSectorAndWheel_3baad90->AddNode(pCables_3bb47c0, 2, pMatrix909);
   // Shape: WheelRibBox type: TGeoBBox
   dx = 3.800000;
   dy = 2.350000;
   dz = 5.715000;
   TGeoShape *pWheelRibBox_226 = new TGeoBBox("WheelRibBox", dx,dy,dz);
   // Volume: WheelRibBox
   pWheelRibBox_3bae000 = new TGeoVolume("WheelRibBox",pWheelRibBox_226, pMed67);
   pWheelRibBox_3bae000->SetLineColor(600);
   pWheelRibBox_3bae000->SetVisLeaves(kTRUE);
   pTpcSectorAndWheel_3baad90->AddNodeOverlap(pWheelRibBox_3bae000, 1, pMatrix871);
   // Shape: TpcWheelRib type: TGeoPara
   dx    = 1.900000;
   dy    = 70.263505;
   dz    = 0.650000;
   alpha = -15.000000;
   theta = 0.000000;
   phi   = 0.000000;
   TGeoShape *pTpcWheelRib_227 = new TGeoPara("TpcWheelRib",dx,dy,dz,alpha,theta,phi);
   // Volume: TpcWheelRib
   pTpcWheelRib_3bae6c0 = new TGeoVolume("TpcWheelRib",pTpcWheelRib_227, pMed67);
   pTpcWheelRib_3bae6c0->SetLineColor(600);
   pTpcWheelRib_3bae6c0->SetVisLeaves(kTRUE);
   pTpcSectorAndWheel_3baad90->AddNodeOverlap(pTpcWheelRib_3bae6c0, 3, pMatrix872);
   // Shape: TpcWheelRib type: TGeoPara
   dx    = 0.475000;
   dy    = 70.263505;
   dz    = 5.715000;
   alpha = -15.000000;
   theta = 0.000000;
   phi   = 0.000000;
   TGeoShape *pTpcWheelRib_228 = new TGeoPara("TpcWheelRib",dx,dy,dz,alpha,theta,phi);
   // Volume: TpcWheelRib
   pTpcWheelRib_3baea40 = new TGeoVolume("TpcWheelRib",pTpcWheelRib_228, pMed67);
   pTpcWheelRib_3baea40->SetLineColor(600);
   pTpcWheelRib_3baea40->SetVisLeaves(kTRUE);
   pTpcSectorAndWheel_3baad90->AddNodeOverlap(pTpcWheelRib_3baea40, 5, pMatrix873);
   pTpcSectorAndWheel_3baad90->AddNodeOverlap(pWheelRibBox_3bae000, 3, pMatrix874);
   pTpcSectorAndWheel_3baad90->AddNodeOverlap(pWheelRibBox_3bae000, 4, pMatrix875);
   pTpcSectorAndWheel_3baad90->AddNodeOverlap(pWheelRibBox_3bae000, 5, pMatrix876);
   pTpcSectorAndWheel_3baad90->AddNodeOverlap(pWheelRibBox_3bae000, 6, pMatrix877);
   // Shape: TpcWheelRib type: TGeoPara
   dx    = 1.900000;
   dy    = 70.263505;
   dz    = 0.650000;
   alpha = 15.000000;
   theta = 0.000000;
   phi   = 0.000000;
   TGeoShape *pTpcWheelRib_229 = new TGeoPara("TpcWheelRib",dx,dy,dz,alpha,theta,phi);
   // Volume: TpcWheelRib
   pTpcWheelRib_3bae4b0 = new TGeoVolume("TpcWheelRib",pTpcWheelRib_229, pMed67);
   pTpcWheelRib_3bae4b0->SetLineColor(600);
   pTpcWheelRib_3bae4b0->SetVisLeaves(kTRUE);
   pTpcSectorAndWheel_3baad90->AddNodeOverlap(pTpcWheelRib_3bae4b0, 4, pMatrix878);
   // Shape: TpcWheelRib type: TGeoPara
   dx    = 0.475000;
   dy    = 70.263505;
   dz    = 5.715000;
   alpha = 15.000000;
   theta = 0.000000;
   phi   = 0.000000;
   TGeoShape *pTpcWheelRib_230 = new TGeoPara("TpcWheelRib",dx,dy,dz,alpha,theta,phi);
   // Volume: TpcWheelRib
   pTpcWheelRib_3baf6b0 = new TGeoVolume("TpcWheelRib",pTpcWheelRib_230, pMed67);
   pTpcWheelRib_3baf6b0->SetLineColor(600);
   pTpcWheelRib_3baf6b0->SetVisLeaves(kTRUE);
   pTpcSectorAndWheel_3baad90->AddNodeOverlap(pTpcWheelRib_3baf6b0, 6, pMatrix879);
   pTpcSectorAndWheel_3baad90->AddNodeOverlap(pWheelRibBox_3bae000, 7, pMatrix880);
   pTpcSectorAndWheel_3baad90->AddNodeOverlap(pWheelRibBox_3bae000, 8, pMatrix881);
   pTpcSectorAndWheel_3baad90->AddNodeOverlap(pWheelRibBox_3bae000, 9, pMatrix882);
   pTpcSectorAndWheel_3baad90->AddNodeOverlap(pWheelRibBox_3bae000, 10, pMatrix883);
   // Shape: TpcSectorAlSupport type: TGeoPgon
   phi1    = 345.000143;
   dphi    = 29.999714;
   nedges = 1;
   nz      = 2;
   TGeoPgon *pgon = new TGeoPgon("TpcSectorAlSupport",phi1,dphi,nedges,nz);
      z     = 210.080000;
      rmin  = 51.326773;
      rmax  = 120.854193;
   pgon->DefineSection(0, z,rmin,rmax);
      z     = 211.032500;
      rmin  = 51.326773;
      rmax  = 120.854193;
   pgon->DefineSection(1, z,rmin,rmax);
   TGeoShape *pTpcSectorAlSupport_68 = pgon;
   // Volume: TpcSectorAlSupport
   pTpcSectorAlSupport_3b64940 = new TGeoVolume("TpcSectorAlSupport",pTpcSectorAlSupport_68, pMed67);
   pTpcSectorAlSupport_3b64940->SetVisLeaves(kTRUE);
   pTpcInnerSectorAssembly_3b63fa0->AddNode(pTpcSectorAlSupport_3b64940, 1);
   // Shape: TpcSectorG10 type: TGeoPgon
   phi1    = 345.000143;
   dphi    = 29.999714;
   nedges = 1;
   nz      = 2;
   TGeoPgon *pgon = new TGeoPgon("TpcSectorG10",phi1,dphi,nedges,nz);
      z     = 209.898000;
      rmin  = 51.326773;
      rmax  = 120.854193;
   pgon->DefineSection(0, z,rmin,rmax);
      z     = 210.080000;
      rmin  = 51.326773;
      rmax  = 120.854193;
   pgon->DefineSection(1, z,rmin,rmax);
   TGeoShape *pTpcSectorG10_69 = pgon;
   // Volume: TpcSectorG10
   pTpcSectorG10_3b65140 = new TGeoVolume("TpcSectorG10",pTpcSectorG10_69, pMed74);
   pTpcSectorG10_3b65140->SetLineColor(400);
   pTpcSectorG10_3b65140->SetVisLeaves(kTRUE);
   pTpcInnerSectorAssembly_3b63fa0->AddNode(pTpcSectorG10_3b65140, 1);
   // Shape: TRIB type: TGeoPara
   dx    = 1.803287;
   dy    = 34.763710;
   dz    = 3.623750;
   alpha = -14.999857;
   theta = 0.000000;
   phi   = 0.000000;
   TGeoShape *pTRIB_71 = new TGeoPara("TRIB",dx,dy,dz,alpha,theta,phi);
   // Volume: TRIB
   pTRIB_3b664d0 = new TGeoVolume("TRIB",pTRIB_71, pMed67);
   pTRIB_3b664d0->SetLineColor(600);
   pTRIB_3b664d0->SetVisLeaves(kTRUE);
   pTpcInnerSectorAssembly_3b63fa0->AddNode(pTRIB_3b664d0, 1, pMatrix372);
   // Volume: WireMount
   pWireMount_3b669f0 = new TGeoVolume("WireMount",pWireMountInnerLeft_72, pMed74);
   pWireMount_3b669f0->SetLineColor(400);
   pWireMount_3b669f0->SetVisLeaves(kTRUE);
   pTpcInnerSectorAssembly_3b63fa0->AddNode(pWireMount_3b669f0, 1, pMatrix373);
   // Shape: TRIB type: TGeoPara
   dx    = 1.803287;
   dy    = 34.763710;
   dz    = 3.623750;
   alpha = 14.999857;
   theta = 0.000000;
   phi   = 0.000000;
   TGeoShape *pTRIB_73 = new TGeoPara("TRIB",dx,dy,dz,alpha,theta,phi);
   // Volume: TRIB
   pTRIB_3b662c0 = new TGeoVolume("TRIB",pTRIB_73, pMed67);
   pTRIB_3b662c0->SetLineColor(600);
   pTRIB_3b662c0->SetVisLeaves(kTRUE);
   pTpcInnerSectorAssembly_3b63fa0->AddNode(pTRIB_3b662c0, 2, pMatrix374);
   // Volume: WireMount
   pWireMount_3b6e1b0 = new TGeoVolume("WireMount",pWireMountInnerRight_74, pMed74);
   pWireMount_3b6e1b0->SetLineColor(400);
   pWireMount_3b6e1b0->SetVisLeaves(kTRUE);
   pTpcInnerSectorAssembly_3b63fa0->AddNode(pWireMount_3b6e1b0, 2, pMatrix375);
   // Shape: TRIB type: TGeoTrd1
   dx1 = 26.124427;
   dx2 = 27.124886;
   dy  = 3.623750;
   dz  = 1.866900;
   TGeoShape *pTRIB_77 = new TGeoTrd1("TRIB", dx1,dx2,dy,dz);
   // Volume: TRIB
   pTRIB_3b75060 = new TGeoVolume("TRIB",pTRIB_77, pMed67);
   pTRIB_3b75060->SetLineColor(600);
   pTRIB_3b75060->SetVisLeaves(kTRUE);
   pTpcInnerSectorAssembly_3b63fa0->AddNode(pTRIB_3b75060, 3, pMatrix376);
   // Shape: TRIB type: TGeoTrd1
   dx1 = 23.969698;
   dx2 = 24.224917;
   dy  = 3.623750;
   dz  = 0.476250;
   TGeoShape *pTRIB_78 = new TGeoTrd1("TRIB", dx1,dx2,dy,dz);
   // Volume: TRIB
   pTRIB_3b74ce0 = new TGeoVolume("TRIB",pTRIB_78, pMed67);
   pTRIB_3b74ce0->SetLineColor(600);
   pTRIB_3b74ce0->SetVisLeaves(kTRUE);
   pTpcInnerSectorAssembly_3b63fa0->AddNode(pTRIB_3b74ce0, 4, pMatrix377);
   // Shape: TRIB type: TGeoTrd1
   dx1 = 19.682018;
   dx2 = 19.937237;
   dy  = 3.623750;
   dz  = 0.476250;
   TGeoShape *pTRIB_79 = new TGeoTrd1("TRIB", dx1,dx2,dy,dz);
   // Volume: TRIB
   pTRIB_3b75150 = new TGeoVolume("TRIB",pTRIB_79, pMed67);
   pTRIB_3b75150->SetLineColor(600);
   pTRIB_3b75150->SetVisLeaves(kTRUE);
   pTpcInnerSectorAssembly_3b63fa0->AddNode(pTRIB_3b75150, 5, pMatrix378);
   // Shape: TRIB type: TGeoTrd1
   dx1 = 15.394338;
   dx2 = 15.649557;
   dy  = 3.623750;
   dz  = 0.476250;
   TGeoShape *pTRIB_80 = new TGeoTrd1("TRIB", dx1,dx2,dy,dz);
   // Volume: TRIB
   pTRIB_3b753d0 = new TGeoVolume("TRIB",pTRIB_80, pMed67);
   pTRIB_3b753d0->SetLineColor(600);
   pTRIB_3b753d0->SetVisLeaves(kTRUE);
   pTpcInnerSectorAssembly_3b63fa0->AddNode(pTRIB_3b753d0, 6, pMatrix379);
   // Shape: TRIB type: TGeoTrd1
   dx1 = 11.106658;
   dx2 = 11.361877;
   dy  = 3.623750;
   dz  = 0.476250;
   TGeoShape *pTRIB_81 = new TGeoTrd1("TRIB", dx1,dx2,dy,dz);
   // Volume: TRIB
   pTRIB_3b756c0 = new TGeoVolume("TRIB",pTRIB_81, pMed67);
   pTRIB_3b756c0->SetLineColor(600);
   pTRIB_3b756c0->SetVisLeaves(kTRUE);
   pTpcInnerSectorAssembly_3b63fa0->AddNode(pTRIB_3b756c0, 7, pMatrix380);
   // Shape: TRIB type: TGeoTrd1
   dx1 = 8.495256;
   dx2 = 9.463727;
   dy  = 3.623750;
   dz  = 1.807210;
   TGeoShape *pTRIB_82 = new TGeoTrd1("TRIB", dx1,dx2,dy,dz);
   // Volume: TRIB
   pTRIB_3b75990 = new TGeoVolume("TRIB",pTRIB_82, pMed67);
   pTRIB_3b75990->SetLineColor(600);
   pTRIB_3b75990->SetVisLeaves(kTRUE);
   pTpcInnerSectorAssembly_3b63fa0->AddNode(pTRIB_3b75990, 8, pMatrix381);
   // Shape: TRIB type: TGeoBBox
   dx = 1.358900;
   dy = 0.952500;
   dz = 3.623750;
   TGeoShape *pTRIB_83 = new TGeoBBox("TRIB", dx,dy,dz);
   // Volume: TRIB
   pTRIB_3b75c00 = new TGeoVolume("TRIB",pTRIB_83, pMed67);
   pTRIB_3b75c00->SetLineColor(600);
   pTRIB_3b75c00->SetVisLeaves(kTRUE);
   pTpcInnerSectorAssembly_3b63fa0->AddNode(pTRIB_3b75c00, 9, pMatrix382);
   // Shape: TRIB type: TGeoBBox
   dx = 1.358900;
   dy = 0.952500;
   dz = 3.623750;
   TGeoShape *pTRIB_84 = new TGeoBBox("TRIB", dx,dy,dz);
   // Volume: TRIB
   pTRIB_3b75ec0 = new TGeoVolume("TRIB",pTRIB_84, pMed67);
   pTRIB_3b75ec0->SetLineColor(600);
   pTRIB_3b75ec0->SetVisLeaves(kTRUE);
   pTpcInnerSectorAssembly_3b63fa0->AddNode(pTRIB_3b75ec0, 10, pMatrix383);
   // Shape: TRIB type: TGeoBBox
   dx = 1.358900;
   dy = 0.952500;
   dz = 3.623750;
   TGeoShape *pTRIB_85 = new TGeoBBox("TRIB", dx,dy,dz);
   // Volume: TRIB
   pTRIB_3b76180 = new TGeoVolume("TRIB",pTRIB_85, pMed67);
   pTRIB_3b76180->SetLineColor(600);
   pTRIB_3b76180->SetVisLeaves(kTRUE);
   pTpcInnerSectorAssembly_3b63fa0->AddNode(pTRIB_3b76180, 11, pMatrix384);
   // Shape: TRIB type: TGeoBBox
   dx = 1.358900;
   dy = 0.952500;
   dz = 3.623750;
   TGeoShape *pTRIB_86 = new TGeoBBox("TRIB", dx,dy,dz);
   // Volume: TRIB
   pTRIB_3b76440 = new TGeoVolume("TRIB",pTRIB_86, pMed67);
   pTRIB_3b76440->SetLineColor(600);
   pTRIB_3b76440->SetVisLeaves(kTRUE);
   pTpcInnerSectorAssembly_3b63fa0->AddNode(pTRIB_3b76440, 12, pMatrix385);
   // Shape: TRIB type: TGeoBBox
   dx = 1.193800;
   dy = 2.540000;
   dz = 3.623750;
   TGeoShape *pTRIB_87 = new TGeoBBox("TRIB", dx,dy,dz);
   // Volume: TRIB
   pTRIB_3b76700 = new TGeoVolume("TRIB",pTRIB_87, pMed67);
   pTRIB_3b76700->SetLineColor(600);
   pTRIB_3b76700->SetVisLeaves(kTRUE);
   pTpcInnerSectorAssembly_3b63fa0->AddNode(pTRIB_3b76700, 13, pMatrix386);
   // Shape: THOLE type: TGeoBBox
   dx = 0.952500;
   dy = 3.333750;
   dz = 0.476250;
   TGeoShape *pTHOLE_70 = new TGeoBBox("THOLE", dx,dy,dz);
   // Volume: THOLE
   pTHOLE_3b65570 = new TGeoVolume("THOLE",pTHOLE_70, pMed56);
   pTHOLE_3b65570->SetVisLeaves(kTRUE);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 1, pMatrix390);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 2, pMatrix392);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 3, pMatrix394);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 4, pMatrix396);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 5, pMatrix398);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 6, pMatrix400);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 10, pMatrix403);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 11, pMatrix405);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 12, pMatrix407);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 13, pMatrix409);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 14, pMatrix411);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 19, pMatrix414);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 20, pMatrix416);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 21, pMatrix418);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 22, pMatrix420);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 23, pMatrix422);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 28, pMatrix425);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 29, pMatrix427);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 37, pMatrix430);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 38, pMatrix432);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 39, pMatrix434);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 40, pMatrix436);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 41, pMatrix438);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 46, pMatrix441);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 47, pMatrix443);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 48, pMatrix445);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 49, pMatrix447);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 55, pMatrix450);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 56, pMatrix452);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 57, pMatrix454);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 58, pMatrix456);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 64, pMatrix459);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 65, pMatrix461);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 66, pMatrix463);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 67, pMatrix465);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 73, pMatrix468);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 74, pMatrix470);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 75, pMatrix472);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 76, pMatrix474);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 82, pMatrix477);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 83, pMatrix479);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 84, pMatrix481);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 91, pMatrix484);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 92, pMatrix486);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 93, pMatrix488);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 100, pMatrix491);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 101, pMatrix493);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 102, pMatrix495);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 109, pMatrix498);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 110, pMatrix500);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 111, pMatrix502);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 118, pMatrix505);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 119, pMatrix507);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 127, pMatrix510);
   pTpcSectorAlSupport_3b64940->AddNode(pTHOLE_3b65570, 128, pMatrix512);
   // Shape: TFEESocket type: TGeoBBox
   dx = 0.310000;
   dy = 2.850000;
   dz = 0.290000;
   TGeoShape *pTFEESocket_37 = new TGeoBBox("TFEESocket", dx,dy,dz);
   // Volume: TFEESocket
   pTFEESocket_3b49990 = new TGeoVolume("TFEESocket",pTFEESocket_37, pMed74);
   pTFEESocket_3b49990->SetVisLeaves(kTRUE);
   pTHOLE_3b65570->AddNode(pTFEESocket_3b49990, 1);
   // Shape: CoolingTube type: TGeoPara
   dx    = 0.635000;
   dy    = 30.761940;
   dz    = 2.286000;
   alpha = -14.901158;
   theta = 0.000000;
   phi   = 0.000000;
   TGeoShape *pCoolingTube_88 = new TGeoPara("CoolingTube",dx,dy,dz,alpha,theta,phi);
   // Volume: CoolingTube
   pCoolingTube_3b77300 = new TGeoVolume("CoolingTube",pCoolingTube_88, pMed65);
   pCoolingTube_3b77300->SetLineColor(880);
   pCoolingTube_3b77300->SetVisLeaves(kTRUE);
   pTpcWheelInnerAssembly_3b64350->AddNode(pCoolingTube_3b77300, 1, pMatrix387);
   // Shape: CoolingTube type: TGeoPara
   dx    = 0.635000;
   dy    = 30.761940;
   dz    = 2.286000;
   alpha = 14.901158;
   theta = 0.000000;
   phi   = 0.000000;
   TGeoShape *pCoolingTube_89 = new TGeoPara("CoolingTube",dx,dy,dz,alpha,theta,phi);
   // Volume: CoolingTube
   pCoolingTube_3b770f0 = new TGeoVolume("CoolingTube",pCoolingTube_89, pMed65);
   pCoolingTube_3b770f0->SetLineColor(880);
   pCoolingTube_3b770f0->SetVisLeaves(kTRUE);
   pTpcWheelInnerAssembly_3b64350->AddNode(pCoolingTube_3b770f0, 2, pMatrix388);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 24.511000;
   dx2 = 24.986155;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_90 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b77e20 = new TGeoVolume("CoolingTube",pCoolingTube_90, pMed65);
   pCoolingTube_3b77e20->SetLineColor(880);
   pCoolingTube_3b77e20->SetVisLeaves(kTRUE);
   pTpcWheelInnerAssembly_3b64350->AddNode(pCoolingTube_3b77e20, 5, pMatrix389);
   // Assembly: FEE
   pFEE_3b4b550 = new TGeoVolumeAssembly("FEE");
   pFEE_3b4b550->SetVisLeaves(kTRUE);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 1, pMatrix391);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 3, pMatrix393);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 5, pMatrix395);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 7, pMatrix397);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 9, pMatrix399);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 11, pMatrix401);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 23.436580;
   dx2 = 23.911735;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_91 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b77800 = new TGeoVolume("CoolingTube",pCoolingTube_91, pMed65);
   pCoolingTube_3b77800->SetLineColor(880);
   pCoolingTube_3b77800->SetVisLeaves(kTRUE);
   pTpcWheelInnerAssembly_3b64350->AddNode(pCoolingTube_3b77800, 7, pMatrix402);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 19, pMatrix404);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 21, pMatrix406);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 23, pMatrix408);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 25, pMatrix410);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 27, pMatrix412);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 22.364700;
   dx2 = 22.839855;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_92 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b79740 = new TGeoVolume("CoolingTube",pCoolingTube_92, pMed65);
   pCoolingTube_3b79740->SetLineColor(880);
   pCoolingTube_3b79740->SetVisLeaves(kTRUE);
   pTpcWheelInnerAssembly_3b64350->AddNode(pCoolingTube_3b79740, 9, pMatrix413);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 37, pMatrix415);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 39, pMatrix417);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 41, pMatrix419);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 43, pMatrix421);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 45, pMatrix423);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 21.292820;
   dx2 = 21.767975;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_93 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b7a3e0 = new TGeoVolume("CoolingTube",pCoolingTube_93, pMed65);
   pCoolingTube_3b7a3e0->SetLineColor(880);
   pCoolingTube_3b7a3e0->SetVisLeaves(kTRUE);
   pTpcWheelInnerAssembly_3b64350->AddNode(pCoolingTube_3b7a3e0, 11, pMatrix424);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 55, pMatrix426);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 57, pMatrix428);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 20.220940;
   dx2 = 20.696095;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_94 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b7ab10 = new TGeoVolume("CoolingTube",pCoolingTube_94, pMed65);
   pCoolingTube_3b7ab10->SetLineColor(880);
   pCoolingTube_3b7ab10->SetVisLeaves(kTRUE);
   pTpcWheelInnerAssembly_3b64350->AddNode(pCoolingTube_3b7ab10, 13, pMatrix429);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 73, pMatrix431);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 75, pMatrix433);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 77, pMatrix435);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 79, pMatrix437);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 81, pMatrix439);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 19.149060;
   dx2 = 19.624215;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_95 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b7b730 = new TGeoVolume("CoolingTube",pCoolingTube_95, pMed65);
   pCoolingTube_3b7b730->SetLineColor(880);
   pCoolingTube_3b7b730->SetVisLeaves(kTRUE);
   pTpcWheelInnerAssembly_3b64350->AddNode(pCoolingTube_3b7b730, 15, pMatrix440);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 91, pMatrix442);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 93, pMatrix444);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 95, pMatrix446);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 97, pMatrix448);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 18.078450;
   dx2 = 18.553605;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_96 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b7c2c0 = new TGeoVolume("CoolingTube",pCoolingTube_96, pMed65);
   pCoolingTube_3b7c2c0->SetLineColor(880);
   pCoolingTube_3b7c2c0->SetVisLeaves(kTRUE);
   pTpcWheelInnerAssembly_3b64350->AddNode(pCoolingTube_3b7c2c0, 17, pMatrix449);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 109, pMatrix451);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 111, pMatrix453);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 113, pMatrix455);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 115, pMatrix457);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 17.005300;
   dx2 = 17.480455;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_97 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b7cd30 = new TGeoVolume("CoolingTube",pCoolingTube_97, pMed65);
   pCoolingTube_3b7cd30->SetLineColor(880);
   pCoolingTube_3b7cd30->SetVisLeaves(kTRUE);
   pTpcWheelInnerAssembly_3b64350->AddNode(pCoolingTube_3b7cd30, 19, pMatrix458);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 127, pMatrix460);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 129, pMatrix462);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 131, pMatrix464);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 133, pMatrix466);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 15.933420;
   dx2 = 16.408575;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_98 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b7d8c0 = new TGeoVolume("CoolingTube",pCoolingTube_98, pMed65);
   pCoolingTube_3b7d8c0->SetLineColor(880);
   pCoolingTube_3b7d8c0->SetVisLeaves(kTRUE);
   pTpcWheelInnerAssembly_3b64350->AddNode(pCoolingTube_3b7d8c0, 21, pMatrix467);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 145, pMatrix469);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 147, pMatrix471);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 149, pMatrix473);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 151, pMatrix475);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 14.864080;
   dx2 = 15.339235;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_99 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b7e330 = new TGeoVolume("CoolingTube",pCoolingTube_99, pMed65);
   pCoolingTube_3b7e330->SetLineColor(880);
   pCoolingTube_3b7e330->SetVisLeaves(kTRUE);
   pTpcWheelInnerAssembly_3b64350->AddNode(pCoolingTube_3b7e330, 23, pMatrix476);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 163, pMatrix478);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 165, pMatrix480);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 167, pMatrix482);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 13.792200;
   dx2 = 14.267355;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_100 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b7ebc0 = new TGeoVolume("CoolingTube",pCoolingTube_100, pMed65);
   pCoolingTube_3b7ebc0->SetLineColor(880);
   pCoolingTube_3b7ebc0->SetVisLeaves(kTRUE);
   pTpcWheelInnerAssembly_3b64350->AddNode(pCoolingTube_3b7ebc0, 25, pMatrix483);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 181, pMatrix485);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 183, pMatrix487);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 185, pMatrix489);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 12.720320;
   dx2 = 13.195475;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_101 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b7f450 = new TGeoVolume("CoolingTube",pCoolingTube_101, pMed65);
   pCoolingTube_3b7f450->SetLineColor(880);
   pCoolingTube_3b7f450->SetVisLeaves(kTRUE);
   pTpcWheelInnerAssembly_3b64350->AddNode(pCoolingTube_3b7f450, 27, pMatrix490);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 199, pMatrix492);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 201, pMatrix494);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 203, pMatrix496);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 11.648440;
   dx2 = 12.123595;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_102 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b7fce0 = new TGeoVolume("CoolingTube",pCoolingTube_102, pMed65);
   pCoolingTube_3b7fce0->SetLineColor(880);
   pCoolingTube_3b7fce0->SetVisLeaves(kTRUE);
   pTpcWheelInnerAssembly_3b64350->AddNode(pCoolingTube_3b7fce0, 29, pMatrix497);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 217, pMatrix499);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 219, pMatrix501);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 221, pMatrix503);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 10.575290;
   dx2 = 11.050445;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_103 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b807a0 = new TGeoVolume("CoolingTube",pCoolingTube_103, pMed65);
   pCoolingTube_3b807a0->SetLineColor(880);
   pCoolingTube_3b807a0->SetVisLeaves(kTRUE);
   pTpcWheelInnerAssembly_3b64350->AddNode(pCoolingTube_3b807a0, 31, pMatrix504);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 235, pMatrix506);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 237, pMatrix508);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 9.503410;
   dx2 = 9.978565;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_104 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b80e20 = new TGeoVolume("CoolingTube",pCoolingTube_104, pMed65);
   pCoolingTube_3b80e20->SetLineColor(880);
   pCoolingTube_3b80e20->SetVisLeaves(kTRUE);
   pTpcWheelInnerAssembly_3b64350->AddNode(pCoolingTube_3b80e20, 33, pMatrix509);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 253, pMatrix511);
   pTpcWheelInnerAssembly_3b64350->AddNode(pFEE_3b4b550, 255, pMatrix513);
   // Shape: FEEPlate type: TGeoBBox
   dx = 0.139700;
   dy = 3.759200;
   dz = 5.905500;
   TGeoShape *pFEEPlate_38 = new TGeoBBox("FEEPlate", dx,dy,dz);
   // Volume: FEEPlate
   pFEEPlate_3b4aab0 = new TGeoVolume("FEEPlate",pFEEPlate_38, pMed67);
   pFEEPlate_3b4aab0->SetLineColor(600);
   pFEEPlate_3b4aab0->SetVisLeaves(kTRUE);
   pFEE_3b4b550->AddNode(pFEEPlate_3b4aab0, 1);
   // Shape: FEERib type: TGeoBBox
   dx = 0.630682;
   dy = 3.272282;
   dz = 0.205359;
   TGeoShape *pFEERib_39 = new TGeoBBox("FEERib", dx,dy,dz);
   // Volume: FEERib
   pFEERib_3b4a840 = new TGeoVolume("FEERib",pFEERib_39, pMed67);
   pFEERib_3b4a840->SetLineColor(600);
   pFEERib_3b4a840->SetVisLeaves(kTRUE);
   pFEE_3b4b550->AddNode(pFEERib_3b4a840, 1, pMatrix317);
   // Shape: FEEitself type: TGeoBBox
   dx = 0.205359;
   dy = 3.683000;
   dz = 8.890000;
   TGeoShape *pFEEitself_40 = new TGeoBBox("FEEitself", dx,dy,dz);
   // Volume: FEEitself
   pFEEitself_3b4b210 = new TGeoVolume("FEEitself",pFEEitself_40, pMed74);
   pFEEitself_3b4b210->SetLineColor(400);
   pFEEitself_3b4b210->SetVisLeaves(kTRUE);
   pFEE_3b4b550->AddNode(pFEEitself_3b4b210, 1, pMatrix318);
   // Shape: TpcSectorAlSupport type: TGeoPgon
   phi1    = 345.000208;
   dphi    = 29.999584;
   nedges = 1;
   nz      = 2;
   TGeoPgon *pgon = new TGeoPgon("TpcSectorAlSupport",phi1,dphi,nedges,nz);
      z     = 210.486400;
      rmin  = 121.153346;
      rmax  = 192.667046;
   pgon->DefineSection(0, z,rmin,rmax);
      z     = 211.438900;
      rmin  = 121.153346;
      rmax  = 192.667046;
   pgon->DefineSection(1, z,rmin,rmax);
   TGeoShape *pTpcSectorAlSupport_170 = pgon;
   // Volume: TpcSectorAlSupport
   pTpcSectorAlSupport_3b90800 = new TGeoVolume("TpcSectorAlSupport",pTpcSectorAlSupport_170, pMed67);
   pTpcSectorAlSupport_3b90800->SetVisLeaves(kTRUE);
   pTpcOuterSectorAssembly_3b8ffa0->AddNode(pTpcSectorAlSupport_3b90800, 1);
   // Shape: TpcSectorG10 type: TGeoPgon
   phi1    = 345.000208;
   dphi    = 29.999584;
   nedges = 1;
   nz      = 2;
   TGeoPgon *pgon = new TGeoPgon("TpcSectorG10",phi1,dphi,nedges,nz);
      z     = 210.304400;
      rmin  = 121.153346;
      rmax  = 192.667046;
   pgon->DefineSection(0, z,rmin,rmax);
      z     = 210.486400;
      rmin  = 121.153346;
      rmax  = 192.667046;
   pgon->DefineSection(1, z,rmin,rmax);
   TGeoShape *pTpcSectorG10_171 = pgon;
   // Volume: TpcSectorG10
   pTpcSectorG10_3b90df0 = new TGeoVolume("TpcSectorG10",pTpcSectorG10_171, pMed74);
   pTpcSectorG10_3b90df0->SetLineColor(400);
   pTpcSectorG10_3b90df0->SetVisLeaves(kTRUE);
   pTpcOuterSectorAssembly_3b8ffa0->AddNode(pTpcSectorG10_3b90df0, 1);
   // Shape: TRIB type: TGeoPara
   dx    = 1.803287;
   dy    = 35.756850;
   dz    = 3.420550;
   alpha = -14.999792;
   theta = 0.000000;
   phi   = 0.000000;
   TGeoShape *pTRIB_173 = new TGeoPara("TRIB",dx,dy,dz,alpha,theta,phi);
   // Volume: TRIB
   pTRIB_3b916c0 = new TGeoVolume("TRIB",pTRIB_173, pMed67);
   pTRIB_3b916c0->SetLineColor(600);
   pTRIB_3b916c0->SetVisLeaves(kTRUE);
   pTpcOuterSectorAssembly_3b8ffa0->AddNode(pTRIB_3b916c0, 1, pMatrix582);
   // Volume: WireMount
   pWireMount_3b919e0 = new TGeoVolume("WireMount",pWireMountOuterLeft_174, pMed74);
   pWireMount_3b919e0->SetLineColor(400);
   pWireMount_3b919e0->SetVisLeaves(kTRUE);
   pTpcOuterSectorAssembly_3b8ffa0->AddNode(pWireMount_3b919e0, 1, pMatrix583);
   // Shape: TRIB type: TGeoPara
   dx    = 1.803287;
   dy    = 35.756850;
   dz    = 3.420550;
   alpha = 14.999792;
   theta = 0.000000;
   phi   = 0.000000;
   TGeoShape *pTRIB_175 = new TGeoPara("TRIB",dx,dy,dz,alpha,theta,phi);
   // Volume: TRIB
   pTRIB_3b914b0 = new TGeoVolume("TRIB",pTRIB_175, pMed67);
   pTRIB_3b914b0->SetLineColor(600);
   pTRIB_3b914b0->SetVisLeaves(kTRUE);
   pTpcOuterSectorAssembly_3b8ffa0->AddNode(pTRIB_3b914b0, 2, pMatrix584);
   // Volume: WireMount
   pWireMount_3b91e30 = new TGeoVolume("WireMount",pWireMountOuterRight_176, pMed74);
   pWireMount_3b91e30->SetLineColor(400);
   pWireMount_3b91e30->SetVisLeaves(kTRUE);
   pTpcOuterSectorAssembly_3b8ffa0->AddNode(pWireMount_3b91e30, 2, pMatrix585);
   // Shape: TRIB type: TGeoTrd1
   dx1 = 45.313117;
   dx2 = 46.176093;
   dy  = 3.420550;
   dz  = 1.610360;
   TGeoShape *pTRIB_179 = new TGeoTrd1("TRIB", dx1,dx2,dy,dz);
   // Volume: TRIB
   pTRIB_3b92fc0 = new TGeoVolume("TRIB",pTRIB_179, pMed67);
   pTRIB_3b92fc0->SetLineColor(600);
   pTRIB_3b92fc0->SetVisLeaves(kTRUE);
   pTpcOuterSectorAssembly_3b8ffa0->AddNode(pTRIB_3b92fc0, 3, pMatrix586);
   // Shape: TRIB type: TGeoTrd1
   dx1 = 43.211482;
   dx2 = 43.466700;
   dy  = 3.420550;
   dz  = 0.476250;
   TGeoShape *pTRIB_180 = new TGeoTrd1("TRIB", dx1,dx2,dy,dz);
   // Volume: TRIB
   pTRIB_3b92ba0 = new TGeoVolume("TRIB",pTRIB_180, pMed67);
   pTRIB_3b92ba0->SetLineColor(600);
   pTRIB_3b92ba0->SetVisLeaves(kTRUE);
   pTpcOuterSectorAssembly_3b8ffa0->AddNode(pTRIB_3b92ba0, 4, pMatrix587);
   // Shape: TRIB type: TGeoTrd1
   dx1 = 41.068333;
   dx2 = 41.323550;
   dy  = 3.420550;
   dz  = 0.476250;
   TGeoShape *pTRIB_181 = new TGeoTrd1("TRIB", dx1,dx2,dy,dz);
   // Volume: TRIB
   pTRIB_3b92e20 = new TGeoVolume("TRIB",pTRIB_181, pMed67);
   pTRIB_3b92e20->SetLineColor(600);
   pTRIB_3b92e20->SetVisLeaves(kTRUE);
   pTpcOuterSectorAssembly_3b8ffa0->AddNode(pTRIB_3b92e20, 5, pMatrix588);
   // Shape: TRIB type: TGeoTrd1
   dx1 = 38.924502;
   dx2 = 39.179720;
   dy  = 3.420550;
   dz  = 0.476250;
   TGeoShape *pTRIB_182 = new TGeoTrd1("TRIB", dx1,dx2,dy,dz);
   // Volume: TRIB
   pTRIB_3b93250 = new TGeoVolume("TRIB",pTRIB_182, pMed67);
   pTRIB_3b93250->SetLineColor(600);
   pTRIB_3b93250->SetVisLeaves(kTRUE);
   pTpcOuterSectorAssembly_3b8ffa0->AddNode(pTRIB_3b93250, 6, pMatrix589);
   // Shape: TRIB type: TGeoTrd1
   dx1 = 36.780672;
   dx2 = 37.035890;
   dy  = 3.420550;
   dz  = 0.476250;
   TGeoShape *pTRIB_183 = new TGeoTrd1("TRIB", dx1,dx2,dy,dz);
   // Volume: TRIB
   pTRIB_3b93540 = new TGeoVolume("TRIB",pTRIB_183, pMed67);
   pTRIB_3b93540->SetLineColor(600);
   pTRIB_3b93540->SetVisLeaves(kTRUE);
   pTpcOuterSectorAssembly_3b8ffa0->AddNode(pTRIB_3b93540, 7, pMatrix590);
   // Shape: TRIB type: TGeoTrd1
   dx1 = 34.637522;
   dx2 = 34.892740;
   dy  = 3.420550;
   dz  = 0.476250;
   TGeoShape *pTRIB_184 = new TGeoTrd1("TRIB", dx1,dx2,dy,dz);
   // Volume: TRIB
   pTRIB_3b93830 = new TGeoVolume("TRIB",pTRIB_184, pMed67);
   pTRIB_3b93830->SetLineColor(600);
   pTRIB_3b93830->SetVisLeaves(kTRUE);
   pTpcOuterSectorAssembly_3b8ffa0->AddNode(pTRIB_3b93830, 8, pMatrix591);
   // Shape: TRIB type: TGeoTrd1
   dx1 = 32.493692;
   dx2 = 32.748910;
   dy  = 3.420550;
   dz  = 0.476250;
   TGeoShape *pTRIB_185 = new TGeoTrd1("TRIB", dx1,dx2,dy,dz);
   // Volume: TRIB
   pTRIB_3b93b20 = new TGeoVolume("TRIB",pTRIB_185, pMed67);
   pTRIB_3b93b20->SetLineColor(600);
   pTRIB_3b93b20->SetVisLeaves(kTRUE);
   pTpcOuterSectorAssembly_3b8ffa0->AddNode(pTRIB_3b93b20, 9, pMatrix592);
   // Shape: TRIB type: TGeoTrd1
   dx1 = 30.350542;
   dx2 = 30.605760;
   dy  = 3.420550;
   dz  = 0.476250;
   TGeoShape *pTRIB_186 = new TGeoTrd1("TRIB", dx1,dx2,dy,dz);
   // Volume: TRIB
   pTRIB_3b93e10 = new TGeoVolume("TRIB",pTRIB_186, pMed67);
   pTRIB_3b93e10->SetLineColor(600);
   pTRIB_3b93e10->SetVisLeaves(kTRUE);
   pTpcOuterSectorAssembly_3b8ffa0->AddNode(pTRIB_3b93e10, 10, pMatrix593);
   // Shape: TRIB type: TGeoTrd1
   dx1 = 27.395459;
   dx2 = 28.461249;
   dy  = 3.420550;
   dz  = 1.988820;
   TGeoShape *pTRIB_187 = new TGeoTrd1("TRIB", dx1,dx2,dy,dz);
   // Volume: TRIB
   pTRIB_3b94100 = new TGeoVolume("TRIB",pTRIB_187, pMed67);
   pTRIB_3b94100->SetLineColor(600);
   pTRIB_3b94100->SetVisLeaves(kTRUE);
   pTpcOuterSectorAssembly_3b8ffa0->AddNode(pTRIB_3b94100, 11, pMatrix594);
   // Shape: TRIB type: TGeoBBox
   dx = 3.522980;
   dy = 1.587500;
   dz = 3.420550;
   TGeoShape *pTRIB_188 = new TGeoBBox("TRIB", dx,dy,dz);
   // Volume: TRIB
   pTRIB_3b943d0 = new TGeoVolume("TRIB",pTRIB_188, pMed67);
   pTRIB_3b943d0->SetLineColor(600);
   pTRIB_3b943d0->SetVisLeaves(kTRUE);
   pTpcOuterSectorAssembly_3b8ffa0->AddNode(pTRIB_3b943d0, 12, pMatrix595);
   // Shape: TRIB type: TGeoBBox
   dx = 3.522980;
   dy = 1.587500;
   dz = 3.420550;
   TGeoShape *pTRIB_189 = new TGeoBBox("TRIB", dx,dy,dz);
   // Volume: TRIB
   pTRIB_3b94690 = new TGeoVolume("TRIB",pTRIB_189, pMed67);
   pTRIB_3b94690->SetLineColor(600);
   pTRIB_3b94690->SetVisLeaves(kTRUE);
   pTpcOuterSectorAssembly_3b8ffa0->AddNode(pTRIB_3b94690, 13, pMatrix596);
   // Shape: TRIB type: TGeoBBox
   dx = 3.524250;
   dy = 0.476250;
   dz = 3.420550;
   TGeoShape *pTRIB_190 = new TGeoBBox("TRIB", dx,dy,dz);
   // Volume: TRIB
   pTRIB_3b949e0 = new TGeoVolume("TRIB",pTRIB_190, pMed67);
   pTRIB_3b949e0->SetLineColor(600);
   pTRIB_3b949e0->SetVisLeaves(kTRUE);
   pTpcOuterSectorAssembly_3b8ffa0->AddNode(pTRIB_3b949e0, 14, pMatrix597);
   // Shape: TRIB type: TGeoBBox
   dx = 3.522980;
   dy = 0.476250;
   dz = 3.420550;
   TGeoShape *pTRIB_191 = new TGeoBBox("TRIB", dx,dy,dz);
   // Volume: TRIB
   pTRIB_3b94ca0 = new TGeoVolume("TRIB",pTRIB_191, pMed67);
   pTRIB_3b94ca0->SetLineColor(600);
   pTRIB_3b94ca0->SetVisLeaves(kTRUE);
   pTpcOuterSectorAssembly_3b8ffa0->AddNode(pTRIB_3b94ca0, 15, pMatrix598);
   // Shape: TRIB type: TGeoBBox
   dx = 2.000250;
   dy = 1.991360;
   dz = 3.420550;
   TGeoShape *pTRIB_192 = new TGeoBBox("TRIB", dx,dy,dz);
   // Volume: TRIB
   pTRIB_3b94f60 = new TGeoVolume("TRIB",pTRIB_192, pMed67);
   pTRIB_3b94f60->SetLineColor(600);
   pTRIB_3b94f60->SetVisLeaves(kTRUE);
   pTpcOuterSectorAssembly_3b8ffa0->AddNode(pTRIB_3b94f60, 16, pMatrix599);
   // Shape: THOLE type: TGeoBBox
   dx = 0.952500;
   dy = 3.175000;
   dz = 0.476250;
   TGeoShape *pTHOLE_172 = new TGeoBBox("THOLE", dx,dy,dz);
   // Volume: THOLE
   pTHOLE_3b91050 = new TGeoVolume("THOLE",pTHOLE_172, pMed56);
   pTHOLE_3b91050->SetVisLeaves(kTRUE);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 1, pMatrix603);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 2, pMatrix605);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 3, pMatrix607);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 4, pMatrix609);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 5, pMatrix611);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 6, pMatrix613);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 7, pMatrix615);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 8, pMatrix617);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 9, pMatrix619);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 10, pMatrix622);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 11, pMatrix624);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 12, pMatrix626);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 13, pMatrix628);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 14, pMatrix630);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 15, pMatrix632);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 16, pMatrix634);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 17, pMatrix636);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 18, pMatrix638);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 19, pMatrix641);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 20, pMatrix643);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 21, pMatrix645);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 22, pMatrix647);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 23, pMatrix649);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 24, pMatrix651);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 25, pMatrix653);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 26, pMatrix655);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 27, pMatrix657);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 28, pMatrix660);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 29, pMatrix662);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 30, pMatrix664);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 31, pMatrix666);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 32, pMatrix668);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 33, pMatrix670);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 34, pMatrix672);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 35, pMatrix674);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 36, pMatrix676);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 37, pMatrix679);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 38, pMatrix681);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 39, pMatrix683);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 40, pMatrix685);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 41, pMatrix687);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 42, pMatrix689);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 43, pMatrix691);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 44, pMatrix693);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 45, pMatrix695);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 46, pMatrix698);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 47, pMatrix700);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 48, pMatrix702);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 49, pMatrix704);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 50, pMatrix706);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 51, pMatrix708);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 52, pMatrix710);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 53, pMatrix712);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 55, pMatrix715);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 56, pMatrix717);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 57, pMatrix719);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 58, pMatrix721);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 59, pMatrix723);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 60, pMatrix725);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 61, pMatrix727);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 62, pMatrix729);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 64, pMatrix732);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 65, pMatrix734);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 66, pMatrix736);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 67, pMatrix738);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 68, pMatrix740);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 69, pMatrix742);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 70, pMatrix744);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 71, pMatrix746);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 73, pMatrix749);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 74, pMatrix751);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 75, pMatrix753);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 76, pMatrix755);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 77, pMatrix757);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 78, pMatrix759);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 79, pMatrix761);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 80, pMatrix763);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 82, pMatrix766);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 83, pMatrix768);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 84, pMatrix770);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 85, pMatrix772);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 86, pMatrix774);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 87, pMatrix776);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 88, pMatrix778);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 89, pMatrix780);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 91, pMatrix783);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 92, pMatrix785);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 93, pMatrix787);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 94, pMatrix789);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 95, pMatrix791);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 96, pMatrix793);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 97, pMatrix795);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 100, pMatrix798);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 101, pMatrix800);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 102, pMatrix802);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 103, pMatrix804);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 104, pMatrix806);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 105, pMatrix808);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 106, pMatrix810);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 109, pMatrix813);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 110, pMatrix815);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 111, pMatrix817);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 112, pMatrix819);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 113, pMatrix821);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 114, pMatrix823);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 115, pMatrix825);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 118, pMatrix828);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 119, pMatrix830);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 120, pMatrix832);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 121, pMatrix834);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 122, pMatrix836);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 123, pMatrix838);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 124, pMatrix840);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 127, pMatrix843);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 128, pMatrix845);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 129, pMatrix847);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 130, pMatrix849);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 131, pMatrix851);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 132, pMatrix853);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 133, pMatrix855);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 136, pMatrix858);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 137, pMatrix860);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 138, pMatrix862);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 139, pMatrix864);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 140, pMatrix866);
   pTpcSectorAlSupport_3b90800->AddNode(pTHOLE_3b91050, 141, pMatrix868);
   pTHOLE_3b91050->AddNode(pTFEESocket_3b49990, 1);
   // Shape: CoolingTube type: TGeoPara
   dx    = 0.635000;
   dy    = 30.846800;
   dz    = 2.286000;
   alpha = -14.809678;
   theta = 0.000000;
   phi   = 0.000000;
   TGeoShape *pCoolingTube_193 = new TGeoPara("CoolingTube",dx,dy,dz,alpha,theta,phi);
   // Volume: CoolingTube
   pCoolingTube_3b954d0 = new TGeoVolume("CoolingTube",pCoolingTube_193, pMed65);
   pCoolingTube_3b954d0->SetLineColor(880);
   pCoolingTube_3b954d0->SetVisLeaves(kTRUE);
   pTpcWheelOuterAssembly_3b90270->AddNode(pCoolingTube_3b954d0, 3, pMatrix600);
   // Shape: CoolingTube type: TGeoPara
   dx    = 0.635000;
   dy    = 30.846800;
   dz    = 2.286000;
   alpha = 14.809678;
   theta = 0.000000;
   phi   = 0.000000;
   TGeoShape *pCoolingTube_194 = new TGeoPara("CoolingTube",dx,dy,dz,alpha,theta,phi);
   // Volume: CoolingTube
   pCoolingTube_3b952c0 = new TGeoVolume("CoolingTube",pCoolingTube_194, pMed65);
   pCoolingTube_3b952c0->SetLineColor(880);
   pCoolingTube_3b952c0->SetVisLeaves(kTRUE);
   pTpcWheelOuterAssembly_3b90270->AddNode(pCoolingTube_3b952c0, 4, pMatrix601);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 42.225296;
   dx2 = 42.697400;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_195 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b95c40 = new TGeoVolume("CoolingTube",pCoolingTube_195, pMed65);
   pCoolingTube_3b95c40->SetLineColor(880);
   pCoolingTube_3b95c40->SetVisLeaves(kTRUE);
   pTpcWheelOuterAssembly_3b90270->AddNode(pCoolingTube_3b95c40, 6, pMatrix602);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 2, pMatrix604);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 4, pMatrix606);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 6, pMatrix608);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 8, pMatrix610);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 10, pMatrix612);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 12, pMatrix614);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 14, pMatrix616);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 16, pMatrix618);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 18, pMatrix620);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 42.206246;
   dx2 = 42.678350;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_196 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b959a0 = new TGeoVolume("CoolingTube",pCoolingTube_196, pMed65);
   pCoolingTube_3b959a0->SetLineColor(880);
   pCoolingTube_3b959a0->SetVisLeaves(kTRUE);
   pTpcWheelOuterAssembly_3b90270->AddNode(pCoolingTube_3b959a0, 8, pMatrix621);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 20, pMatrix623);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 22, pMatrix625);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 24, pMatrix627);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 26, pMatrix629);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 28, pMatrix631);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 30, pMatrix633);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 32, pMatrix635);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 34, pMatrix637);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 36, pMatrix639);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 41.134366;
   dx2 = 41.606470;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_197 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b98420 = new TGeoVolume("CoolingTube",pCoolingTube_197, pMed65);
   pCoolingTube_3b98420->SetLineColor(880);
   pCoolingTube_3b98420->SetVisLeaves(kTRUE);
   pTpcWheelOuterAssembly_3b90270->AddNode(pCoolingTube_3b98420, 10, pMatrix640);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 38, pMatrix642);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 40, pMatrix644);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 42, pMatrix646);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 44, pMatrix648);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 46, pMatrix650);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 48, pMatrix652);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 50, pMatrix654);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 52, pMatrix656);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 54, pMatrix658);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 40.062486;
   dx2 = 40.534590;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_198 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b99790 = new TGeoVolume("CoolingTube",pCoolingTube_198, pMed65);
   pCoolingTube_3b99790->SetLineColor(880);
   pCoolingTube_3b99790->SetVisLeaves(kTRUE);
   pTpcWheelOuterAssembly_3b90270->AddNode(pCoolingTube_3b99790, 12, pMatrix659);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 56, pMatrix661);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 58, pMatrix663);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 60, pMatrix665);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 62, pMatrix667);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 64, pMatrix669);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 66, pMatrix671);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 68, pMatrix673);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 70, pMatrix675);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 72, pMatrix677);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 38.990606;
   dx2 = 39.462710;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_199 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b9ad40 = new TGeoVolume("CoolingTube",pCoolingTube_199, pMed65);
   pCoolingTube_3b9ad40->SetLineColor(880);
   pCoolingTube_3b9ad40->SetVisLeaves(kTRUE);
   pTpcWheelOuterAssembly_3b90270->AddNode(pCoolingTube_3b9ad40, 14, pMatrix678);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 74, pMatrix680);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 76, pMatrix682);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 78, pMatrix684);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 80, pMatrix686);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 82, pMatrix688);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 84, pMatrix690);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 86, pMatrix692);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 88, pMatrix694);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 90, pMatrix696);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 37.918726;
   dx2 = 38.390830;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_200 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b9c110 = new TGeoVolume("CoolingTube",pCoolingTube_200, pMed65);
   pCoolingTube_3b9c110->SetLineColor(880);
   pCoolingTube_3b9c110->SetVisLeaves(kTRUE);
   pTpcWheelOuterAssembly_3b90270->AddNode(pCoolingTube_3b9c110, 16, pMatrix697);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 92, pMatrix699);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 94, pMatrix701);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 96, pMatrix703);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 98, pMatrix705);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 100, pMatrix707);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 102, pMatrix709);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 104, pMatrix711);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 106, pMatrix713);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 36.846846;
   dx2 = 37.318950;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_201 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b9d300 = new TGeoVolume("CoolingTube",pCoolingTube_201, pMed65);
   pCoolingTube_3b9d300->SetLineColor(880);
   pCoolingTube_3b9d300->SetVisLeaves(kTRUE);
   pTpcWheelOuterAssembly_3b90270->AddNode(pCoolingTube_3b9d300, 18, pMatrix714);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 110, pMatrix716);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 112, pMatrix718);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 114, pMatrix720);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 116, pMatrix722);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 118, pMatrix724);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 120, pMatrix726);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 122, pMatrix728);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 124, pMatrix730);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 35.774966;
   dx2 = 36.247070;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_202 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b9e720 = new TGeoVolume("CoolingTube",pCoolingTube_202, pMed65);
   pCoolingTube_3b9e720->SetLineColor(880);
   pCoolingTube_3b9e720->SetVisLeaves(kTRUE);
   pTpcWheelOuterAssembly_3b90270->AddNode(pCoolingTube_3b9e720, 20, pMatrix731);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 128, pMatrix733);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 130, pMatrix735);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 132, pMatrix737);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 134, pMatrix739);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 136, pMatrix741);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 138, pMatrix743);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 140, pMatrix745);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 142, pMatrix747);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 34.703086;
   dx2 = 35.175190;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_203 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b9fb10 = new TGeoVolume("CoolingTube",pCoolingTube_203, pMed65);
   pCoolingTube_3b9fb10->SetLineColor(880);
   pCoolingTube_3b9fb10->SetVisLeaves(kTRUE);
   pTpcWheelOuterAssembly_3b90270->AddNode(pCoolingTube_3b9fb10, 22, pMatrix748);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 146, pMatrix750);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 148, pMatrix752);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 150, pMatrix754);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 152, pMatrix756);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 154, pMatrix758);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 156, pMatrix760);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 158, pMatrix762);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 160, pMatrix764);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 33.631206;
   dx2 = 34.103310;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_204 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3ba0cd0 = new TGeoVolume("CoolingTube",pCoolingTube_204, pMed65);
   pCoolingTube_3ba0cd0->SetLineColor(880);
   pCoolingTube_3ba0cd0->SetVisLeaves(kTRUE);
   pTpcWheelOuterAssembly_3b90270->AddNode(pCoolingTube_3ba0cd0, 24, pMatrix765);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 164, pMatrix767);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 166, pMatrix769);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 168, pMatrix771);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 170, pMatrix773);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 172, pMatrix775);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 174, pMatrix777);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 176, pMatrix779);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 178, pMatrix781);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 32.559326;
   dx2 = 33.031430;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_205 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3ba1ec0 = new TGeoVolume("CoolingTube",pCoolingTube_205, pMed65);
   pCoolingTube_3ba1ec0->SetLineColor(880);
   pCoolingTube_3ba1ec0->SetVisLeaves(kTRUE);
   pTpcWheelOuterAssembly_3b90270->AddNode(pCoolingTube_3ba1ec0, 26, pMatrix782);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 182, pMatrix784);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 184, pMatrix786);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 186, pMatrix788);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 188, pMatrix790);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 190, pMatrix792);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 192, pMatrix794);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 194, pMatrix796);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 31.487446;
   dx2 = 31.959550;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_206 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3ba2ed0 = new TGeoVolume("CoolingTube",pCoolingTube_206, pMed65);
   pCoolingTube_3ba2ed0->SetLineColor(880);
   pCoolingTube_3ba2ed0->SetVisLeaves(kTRUE);
   pTpcWheelOuterAssembly_3b90270->AddNode(pCoolingTube_3ba2ed0, 28, pMatrix797);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 200, pMatrix799);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 202, pMatrix801);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 204, pMatrix803);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 206, pMatrix805);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 208, pMatrix807);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 210, pMatrix809);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 212, pMatrix811);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 30.415566;
   dx2 = 30.887670;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_207 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3ba3ee0 = new TGeoVolume("CoolingTube",pCoolingTube_207, pMed65);
   pCoolingTube_3ba3ee0->SetLineColor(880);
   pCoolingTube_3ba3ee0->SetVisLeaves(kTRUE);
   pTpcWheelOuterAssembly_3b90270->AddNode(pCoolingTube_3ba3ee0, 30, pMatrix812);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 218, pMatrix814);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 220, pMatrix816);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 222, pMatrix818);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 224, pMatrix820);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 226, pMatrix822);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 228, pMatrix824);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 230, pMatrix826);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 29.344956;
   dx2 = 29.817060;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_208 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3ba4ef0 = new TGeoVolume("CoolingTube",pCoolingTube_208, pMed65);
   pCoolingTube_3ba4ef0->SetLineColor(880);
   pCoolingTube_3ba4ef0->SetVisLeaves(kTRUE);
   pTpcWheelOuterAssembly_3b90270->AddNode(pCoolingTube_3ba4ef0, 32, pMatrix827);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 236, pMatrix829);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 238, pMatrix831);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 240, pMatrix833);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 242, pMatrix835);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 244, pMatrix837);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 246, pMatrix839);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 248, pMatrix841);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 28.273076;
   dx2 = 28.745180;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_209 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3b9db90 = new TGeoVolume("CoolingTube",pCoolingTube_209, pMed65);
   pCoolingTube_3b9db90->SetLineColor(880);
   pCoolingTube_3b9db90->SetVisLeaves(kTRUE);
   pTpcWheelOuterAssembly_3b90270->AddNode(pCoolingTube_3b9db90, 34, pMatrix842);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 254, pMatrix844);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 256, pMatrix846);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 258, pMatrix848);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 260, pMatrix850);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 262, pMatrix852);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 264, pMatrix854);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 266, pMatrix856);
   // Shape: CoolingTube type: TGeoTrd1
   dx1 = 27.201196;
   dx2 = 27.673300;
   dy  = 0.635000;
   dz  = 0.892810;
   TGeoShape *pCoolingTube_210 = new TGeoTrd1("CoolingTube", dx1,dx2,dy,dz);
   // Volume: CoolingTube
   pCoolingTube_3ba7450 = new TGeoVolume("CoolingTube",pCoolingTube_210, pMed65);
   pCoolingTube_3ba7450->SetLineColor(880);
   pCoolingTube_3ba7450->SetVisLeaves(kTRUE);
   pTpcWheelOuterAssembly_3b90270->AddNode(pCoolingTube_3ba7450, 36, pMatrix857);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 272, pMatrix859);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 274, pMatrix861);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 276, pMatrix863);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 278, pMatrix865);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 280, pMatrix867);
   pTpcWheelOuterAssembly_3b90270->AddNode(pFEE_3b4b550, 282, pMatrix869);
   // Shape: CoolingTube type: TGeoPara
   dx    = 1.250000;
   dy    = 52.500000;
   dz    = 2.500000;
   alpha = 15.000000;
   theta = 0.000000;
   phi   = 0.000000;
   TGeoShape *pCoolingTube_231 = new TGeoPara("CoolingTube",dx,dy,dz,alpha,theta,phi);
   // Volume: CoolingTube
   pCoolingTube_3bb0880 = new TGeoVolume("CoolingTube",pCoolingTube_231, pMed65);
   pCoolingTube_3bb0880->SetLineColor(880);
   pCoolingTube_3bb0880->SetVisLeaves(kTRUE);
   pTpcRDOAssembly_3bafd70->AddNode(pCoolingTube_3bb0880, 1, pMatrix884);
   // Shape: CoolingTube type: TGeoPara
   dx    = 1.250000;
   dy    = 52.500000;
   dz    = 2.500000;
   alpha = -15.000000;
   theta = 0.000000;
   phi   = 0.000000;
   TGeoShape *pCoolingTube_232 = new TGeoPara("CoolingTube",dx,dy,dz,alpha,theta,phi);
   // Volume: CoolingTube
   pCoolingTube_3bb0c50 = new TGeoVolume("CoolingTube",pCoolingTube_232, pMed65);
   pCoolingTube_3bb0c50->SetLineColor(880);
   pCoolingTube_3bb0c50->SetVisLeaves(kTRUE);
   pTpcRDOAssembly_3bafd70->AddNode(pCoolingTube_3bb0c50, 2, pMatrix885);
   pTpcRDOAssembly_3bafd70->AddNode(pCoolingTube_3bb1fe0, 3, pMatrix886);
   pTpcRDOAssembly_3bafd70->AddNode(pCoolingTube_3bb1dd0, 4, pMatrix888);
   // Shape: RDOCard type: TGeoBBox
   dx = 0.875000;
   dy = 22.500000;
   dz = 8.500000;
   TGeoShape *pRDOCard_233 = new TGeoBBox("RDOCard", dx,dy,dz);
   // Volume: RDOCard
   pRDOCard_3bb1680 = new TGeoVolume("RDOCard",pRDOCard_233, pMed74);
   pRDOCard_3bb1680->SetLineColor(400);
   pRDOCard_3bb1680->SetVisLeaves(kTRUE);
   pTpcRDOAssembly_3bafd70->AddNode(pRDOCard_3bb1680, 1, pMatrix890);
   pTpcRDOAssembly_3bafd70->AddNode(pCoolingTube_3bb2780, 5, pMatrix891);
   pTpcRDOAssembly_3bafd70->AddNode(pRDOCard_3bb1680, 2, pMatrix893);
   pTpcRDOAssembly_3bafd70->AddNode(pCoolingTube_3bb2c00, 6, pMatrix894);
   pTpcRDOAssembly_3bafd70->AddNode(pRDOCard_3bb1680, 3, pMatrix896);
   pTpcRDOAssembly_3bafd70->AddNode(pCoolingTube_3bb3080, 7, pMatrix897);
   pTpcRDOAssembly_3bafd70->AddNode(pRDOCard_3bb1680, 4, pMatrix899);
   pTpcRDOAssembly_3bafd70->AddNode(pCoolingTube_3bb3560, 8, pMatrix900);
   pTpcRDOAssembly_3bafd70->AddNode(pRDOCard_3bb1680, 5, pMatrix902);
   pTpcRDOAssembly_3bafd70->AddNode(pCoolingTube_3bb3a40, 9, pMatrix903);
   pTpcRDOAssembly_3bafd70->AddNode(pCoolingTube_3bb3e30, 10, pMatrix905);
   pTpcRDOAssembly_3bafd70->AddNode(pRDOCard_3bb1680, 6, pMatrix907);

   // CLOSE GEOMETRY
   gGeoManager->CloseGeometry();
}
