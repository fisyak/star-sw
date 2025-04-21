#ifndef __GeometryDbAliases__
#define __GeometryDbAliases__
static const DbAlias_t fDbAlias[] = {// geometry  Comment            old 
  {"y1h",         20000614,175430, "y2000",  "xgeometry"}, 
  {"y2000",       20000614,175430, "y2000",  "xgeometry"},                   //       {"y2000",       20000614,175430}

  {"y2001",       20010501,     0, "y2001",  "xgeometry"},
  {"y2001n",      20010615,     0, "y2001",  "xgeometry"}, 

  {"y2003",       20021215,     1, "y2003x", "xgeometry"},  
  {"y2003x",      20021215,     1, "y2003x", "xgeometry"},                   //       {"y2003x",      20021215,     0}
  {"y2003z",      20021215,     2, "y2003z", "xgeometry"},                   //       {"y2003x",      20021215,     0}
  {"r2003",       20021220,     0, "y2003z", "xgeometry"}, 

  {"y2004a",      20031215,     3, "y2004a",   "AgML,xgeometry"},                   //       {"y2004a",      20031120,     0}
  {"y2004",       20031216,     0, "y2004c",   "AgML,xgeometry"},                   //       {"y2004c",      20031125,     0}
  {"y2004c",      20031216,     1, "y2004c",   "AgML,xgeometry"},                   //       {"y2004c",      20031125,     0}
  {"y2004z",      20031216,     2, "y2004z",   "xgeometry"},                   //       {"y2004c",      20031125,     0}
  {"r2004",       20040109,  5425, "y2004z",   ""},                            //       {"y2004c",      20031125,     0}
  {"AuAu200_2004",20040109,  5425, "y2004z", "productionMinBias"}, // 1st run = 5008155
  
  // Dead area in SSD, in version y2005f
  {"y2005b",      20041101,     0, "y2005b",   "xgeometry"},                   //       {"y2005b",      20041101,     0}
  {"y2005",       20041201,     6, "y2005i",   "y2005h + ECALv6  ,AgML,xgeometry"},
  {"y2005i",      20041201,     6, "y2005i",   "y2005h + ECALv6  ,AgML,xgeometry"},
  {"y2005z",      20041201,     7, "y2005z",   "y2005h + ECALv6  ,     xgeometry"},
  {"r2005",       20041220,     0, "y2005z",   "y2005h + ECALv6"},
  {"cu62_2005",	  20050309,200953, "y2005z", "cu62productionMinBias"}, // 1st run = 6068018

  // Dead area in SSD, in version y2006b
  {"y2006",       20051201,     5, "y2006h",   "y2006g + ecal6+tpc2009(JW),AgML,xgeometry"},
  {"y2006h",      20051201,     5, "y2006h",   "y2006g + ecal6+tpc2009(JW),AgML,xgeometry"},
  {"y2006z",      20051201,     6, "y2006z",   "y2006z + ecal6+tpc2009(JW),     xgeometry"},
  {"r2006",       20051220,     0, "y2006z",   "y2006z + ecal6+tpc2009(JW),"},

  // in preparation
  {"y2007g",      20061105,     4, "y2007g",   "y2007b + SVT dead material,AgML,xgeometry"},
  {"y2007",       20061105,     5, "y2007h",   "y2007g + TPC2009,AgML,xgeometry"},
  {"y2007h",      20061105,     5, "y2007h",   "y2007g + TPC2009,AgML,xgeometry"},
  {"y2007z",      20061105,     6, "y2007z",   "y2007g + TPC2009,     xgeometry"},
  {"r2007",       20061220,     0, "y2007z",   "y2007g + TPC2009"},

  // SVT/SSD is out
  {"y2008a",      20071101,     1, "y2008a",   "base for y2008: SVT/SSD out, cone in separate SCON,AgML,xgeometry"},
  {"y2008",       20071101,     5, "y2008e",   "LOW_EM central calorimter cuts,AgML,xgeometry"},
  {"y2008e",      20071101,     5, "y2008e",   "LOW_EM central calorimter cuts,AgML,xgeometry"},
  {"y2008z",      20071101,     6, "y2008z",   "LOW_EM central calorimter cuts,     xgeometry"},
  {"r2008",       20071120,     0, "y2008z",   "LOW_EM central calorimter cuts"},
  {"dAu2008",	  20071130,  54621, "y2008z", "dAu2008"}, // 1st run = 8334001

  {"y2009a",      20081215,     1, "y2009a",   "y2009+ecalgeo6(JW),AgML,xgeometry"},
  {"y2009",       20081215,     4, "y2009d",   "Honey sandwich fix,AgML,xgeometry"},
  {"y2009d",      20081215,     4, "y2009d",   "Honey sandwich fix,AgML,xgeometry"},
  {"y2009z",      20081215,     5, "y2009z",   "Honey sandwich fix,     xgeometry"},
  {"r2009",       20081220,     0, "y2009z",   "Honey sandwich fix"},
  {"pp2009_500GeV",	                     20090320,   4556, "y2009z", "production2009_500GeV"}, // 1st run = 10078069
  {"pp2009_200GeV",	                     20090423,   5903, "y2009z", "production2009_200GeV_Hi"}, // 1st run = 10112099

  {"y2010a",      20091215,     1, "y2010a",   "y2010 production tag,AgML,xgeometry"},
  {"y2010",       20091215,     3, "y2010c",   "Honey sandwich fix,AgML,xgeometry"},
  {"y2010c",      20091215,     3, "y2010c",   "Honey sandwich fix,AgML,xgeometry"},
  {"y2010z",      20091215,     4, "y2010z",   "Honey sandwich fix,     xgeometry"},
  {"r2010",       20091220,     0, "y2010z",   "Honey sandwich fix"},

  {"AuAu200_2010",                           20100103,  24648, "y2010z", "AuAu200"}, // 1st run = 11002120
  {"AuAu62_2010",                            20100318, 203224, "y2010z", "AuAu62"}, // 1st run = 11077027
  {"AuAu39_2010",                            20100408, 205540, "y2010z", "AuAu39"}, // 1st run = 11098073
  {"AuAu7_2010",	          	     20100421, 190639, "y2010z", "AuAu7"}, // 1st run = 11111060 
  {"AuAu39_2010b",	              	     20100421, 205504, "y2010z", "AuAu39"}, // 1st run = 11111064
  {"AuAu7_2010b",	              	     20100423,  24916, "y2010z", "AuAu7"}, // 1st run = 11112066 
  {"AuAu11_2010",	            	     20100528,  33641, "y2010z", "AuAu11"}, // 1st run = 11147048

  {"y2011",       20101215,     2, "y2011b",   "y2011a + new TPC + Extended Cave and tunnel,AgML,xgeometry"},
  {"y2011b",      20101215,     2, "y2011b",   "y2011a + new TPC + Extended Cave and tunnel,AgML,xgeometry"},
  {"y2011z",      20101215,     3, "y2011z",   "y2011a + new TPC + Extended Cave and tunnel,xgeometry"},
  {"r2011",       20101220,     0, "y2011z",   "y2011a + new TPC + Extended Cave and tunnel"},
  {"pp500_2011",	                     20110124,  62856, "y2011z", "pp500_2011"}, // 1st run = 12024005
  {"AuAu18_2011",	                     20110418, 172118, "y2011z", "AuAu18"}, // 1st run = 12108024
  {"AuAu19_2011",	                     20110422, 132801, "y2011z", "AuAu19"}, // 1st run = 12112008
  {"AuAu200_2011",	                     20110504,  25334, "y2011z", "AuAu200_2011"}, // 1st run = 12123006			 

  {"y2012a",      20111215,     1, "y2012a",   "y2012 geometry (MTD missing),AgML,xgeometry"},
  {"y2012b",      20111215,     2, "y2012b",   "y2012 geometry, now with MTD,AgML,xgeometry"},
  {"y2012",       20111215,     3, "y2012b",   "y2012 geometry, now with MTD, Extended Cave and tunnel, new TPC,AgML,xgeometry"},
  {"y2012c",      20111215,     3, "y2012b",   "y2012 geometry, now with MTD, Extended Cave and tunnel, new TPC,AgML,xgeometry"},
  {"y2012z",      20111215,     4, "y2012z",   "y2012 geometry, now with MTD, Extended Cave and tunnel, new TPC     ,xgeometry"},
  {"r2012",       20111220,     0, "y2012z",   "y2012 geometry, now with MTD, Extended Cave and tunnel, new TPC"},
  {"pp200_2012",	              	     20120207, 232951, "y2012z", "pp200_2012"}, // 1st run = 13038144			 
  {"pp500_2012",	              	     20120312, 160952, "y2012z", "pp500_2012"}, // 1st run = 13072028			 
  {"UU_2012",	                      	     20120423, 100915, "y2012z", "UU_2012"}, // 1st run = 13114014			 
  {"cuAu_2012",	                      	     20120516, 192018, "y2012z", "cuAu_2012"}, // 1st run = 13137009			 

  {"y2013",       20121215,     0, "y2013_1c", "y2013 first cut geometry,AgML,xgeometry"},
  {"y2013_1c",    20121215,     4, "y2013_1c", "y2013c, Extended Cave and tunnel,AgML,xgeometry"},
  {"y2013_2c",    20121215,  1004, "y2013_2c", "y2013c, Extended Cave and tunnel,AgML,xgeometry"},
  {"y2013_1z",    20121215,     5, "y2013_1z", "y2013z, Extended Cave and tunnel, [pixel in]     xgeometry"},
  {"y2013_2z",    20121215,  1005, "y2013_2z", "y2013z, Extended Cave and tunnel, [pixel out]    xgeometry"},
  {"r2013",       20121220,     0, "y2013_2z", "y2013z asymptotic geometry sans pixel.  WARNING: Geometry may change between releases"},
  {"r2013_z2",    20121220,     0, "y2013_2z", "y2013z asymptotic geometry sans pixel.  WARNING: Geometry may change between releases"},
  {"pp500_2013",  20130315,150531, "y2013_1z", "pp500_2013"}, // 1st run = 14074055			 
  {"20130509.000001", 20130509, 1, "y2013_1z", "y2013 with pixel, real data"},
  {"r2013_c1",    20130509,     1, "y2013_1z", "y2013x asymptotic geometry with pixel.  WARNING: Geometry may change between releases"},

  {"y2014a",      20131215,     1, "y2014a",   "y2014a 2014 preview geometry,AgML,xgeometry"},
  {"y2014",       20131215,     3, "y2014a",   "y2014c 2014 production geometry,IST overlap correction,AgML,xgeometry"},
  {"y2014c",      20131215,     3, "y2014a",   "y2014c 2014 production geometry,IST overlap correction,AgML,xgeometry"},
  {"y2014z",      20131215,     4, "y2014z",   "y2014z 2014 production geometry,IST overlap correction,     xgeometry"},
  {"r2014",       20131220,     0, "y2014z",   "y2014c new TPC rows"},
  {"15GeV_2014",	              	     20140215, 214336, "y2014z", "15GeV_2014"}, // 1st run = 15046070			 
  {"AuAu_200_2014",	              	     20140315, 190309, "y2014z", "AuAu_200_2014"}, // 1st run = 15074070		 
  {"AuHe3_2014",	              	     20140619, 224357, "y2014z", "AuHe3_2014"}, // 1st run = 15170056			 

  {"y2015b",      20141215,     2, "y2015b",   "y2015b production geometry with MTD radii corrections, AgML,xgeometry"},
  {"y2015c",      20141215,     3, "y2015c",   "y2015c production geometry with MTD revised radii corrections, AgML,xgeometry"},
  {"y2015",       20141215,     4, "y2015d",   "y2015d production geometry with IST overlap correction, AgML,xgeometry"},
  {"y2015d",      20141215,     4, "y2015d",   "y2015d production geometry with IST overlap correction, AgML,xgeometry"},
  {"y2015z",      20141215,     5, "y2015z",   "y2015d production geometry with IST overlap correction,      xgeometry"},
  {"r2015",       20141220,     4, "y2015z",   "y2015z production geometry with IST overlap correction                "},
  {"pp200long_2015",	              	     20150211,  12600, "y2015z", "pp200long_2015"}, // 1st run = 16041202		 
  {"pp200trans_2015",	              	     20150306,  23145, "y2015z", "pp200trans_2015"}, // 1st run = 16064077		 
  {"pp200long2_2015",	              	     20150404,  10123, "y2015z", "pp200long2_2015"}, // 1st run = 16093061		 
  {"pAu200_2015",	              	     20150504, 205203, "y2015z", "pAu200_2015"}, // 1st run = 16124017			 
  {"pAl200_2015",	              	     20150608, 202224, "y2015z", "pAl200_2015"}, // 1st run = 16159031			 
  {"pAu200_2015b",	              	     20150610, 203824, "y2015z", "pAu200_2015"}, // 1st run = 16161034			 
  {"pAl200_2015b",	              	     20150610, 235626, "y2015z", "pAl200_2015"}, // 1st run = 16161036			 

  {"y2016",       20151215,     0, "y2016",    "y2016 development geometry, AgML,xgeometry"},   // dev2016 is deprecated for reco
  {"y2016a",      20151215,     1, "y2016a",   "y2016 production geometry, AgML,xgeometry"},   // dev2016 is deprecated for reco
  {"y2016z",      20151215,     2, "y2016z",   "y2016 production geometry,      xgeometry"},   // dev2016 is deprecated for reco
  {"r2016",       20151220,     0, "y2016z",   "y2016 development geometry,      xgeometry"},   // dev2016 is deprecated for reco
  {"AuAu_200_2016",	              	     20160207, 171305, "y2016z", "AuAu_200_2016"}, // 1st run = 17038050		 

  {"y2017",       20161215,     1, "y2017a",   "y2017 production  geometry, AgML,xgeometry"},   
  {"y2017a",      20161215,     1, "y2017a",   "y2017 production  geometry, AgML,xgeometry"},   
  {"y2017z",      20161215,     2, "y2017z",   "y2017 production  geometry,      xgeometry"},   
  {"r2017a",      20161220,     1, "y2017z",   "y2017 production  geometry, AgML,xgeometry"},   
  {"AuAu54_2017",	              	     20170602, 181634, "y2017z", "AuAu54_2017"}, // 1st run = 18153035			 
  {"pp500_rhicf_2017",	              	     20170624,  23811, "y2017z", "pp500_rhicf_2017"}, // 1st run = 18174051		 
 
  {"y2018",       20171215,     2, "y2018",    "y2018 development geometry, AgML,xgeometry"},   
  {"y2018c",      20171215,     3, "y2018c",   "y2018a physics production geometry version A, AgML,xgeometry"},   
  {"y2018z",      20171215,     4, "y2018z",   "y2018z physics production geometry version A,      xgeometry"},   
  {"r2018",       20171220,     0, "y2018z",   "y2018z, no HFT"}, // 
  {"isobar_2018",	              	     20180312, 162439, "y2018z", "isobar_2018"}, // 1st run = 19071038			 
  {"27GeV_2018",	              	     20180510, 201552, "y2018z", "27GeV_2018"}, // 1st run = 19130060			 x1
  {"27GeV_fixedTarget_2018",	      	     20180518, 231602, "y2018z", "27GeV_fixedTarget_2018"}, // 1st run = 19138032	 
  {"27GeV_2018b",	              	     20180519,  82150, "y2018z", "27GeV_2018"}, // 1st run = 19139022			 
  {"27GeV_2018c",	              	     20180529,  23458, "y2018z", "27GeV_2018"}, // 1st run = 19148050			 
  {"3p85GeV_fixedTarget_2018",	      	     20180531,  71446, "y2018z", "3p85GeV_fixedTarget_2018"}, // 1st run = 19151029	 
  {"27GeV_2018d",	              	     20180605,  31540, "y2018z", "27GeV_2018"}, // 1st run = 19155057			 
  {"26p5GeV_fixedTarget_2018",	      	     20180607, 225853, "y2018z", "26p5GeV_fixedTarget_2018"}, // 1st run = 19158057	 
  {"27GeV_2018e",	              	     20180608,  11358, "y2018z", "27GeV_2018"}, // 1st run = 19158059			 
  {"26p5GeV_fixedTarget_2018b",	      	     20180609,   1349, "y2018z", "26p5GeV_fixedTarget_2018"}, // 1st run = 19159043	 
  {"27GeV_2018f",	              	     20180611,  15329, "y2018z", "27GeV_2018"}, // 1st run = 19161048			 
  {"26p5GeV_fixedTarget_2018c",	      	     20180611, 180125, "y2018z", "26p5GeV_fixedTarget_2018"}, // 1st run = 19162033	 
  {"27GeV_2018g",	              	     20180611, 193656, "y2018z", "27GeV_2018"}, // 1st run = 19162036			 
  {"26p5GeV_fixedTarget_2018d",	      	     20180612,  30705, "y2018z", "26p5GeV_fixedTarget_2018"}, // 1st run = 19162043	 
  {"27GeV_2018h",	              	     20180612,  65304, "y2018z", "27GeV_2018"}, // 1st run = 19163006			 
  {"26p5GeV_fixedTarget_2018e",	      	     20180612, 144931, "y2018z", "26p5GeV_fixedTarget_2018"}, // 1st run = 19163024	 
  {"27GeV_2018i",	              	     20180612, 214626, "y2018z", "27GeV_2018"}, // 1st run = 19163039			 
  {"26p5GeV_fixedTarget_2018f",	      	     20180613,    956, "y2018z", "26p5GeV_fixedTarget_2018"}, // 1st run = 19163042	 
  {"27GeV_2018j",	              	     20180613,  53758, "y2018z", "27GeV_2018"}, // 1st run = 19164004			 
  {"26p5GeV_fixedTarget_2018g",	      	     20180614,   5924, "y2018z", "26p5GeV_fixedTarget_2018"}, // 1st run = 19164022	 
  {"27GeV_2018k",	              	     20180614,  41305, "y2018z", "27GeV_2018"}, // 1st run = 19165002			 
  {"26p5GeV_fixedTarget_2018i",	      	     20180614, 180439, "y2018z", "26p5GeV_fixedTarget_2018"}, // 1st run = 19165030	 
  {"27GeV_2018l",	              	     20180615,  72506, "y2018z", "27GeV_2018"}, // 1st run = 19166006			 
  {"26p5GeV_fixedTarget_2018j",	      	     20180616,  30539, "y2018z", "26p5GeV_fixedTarget_2018"}, // 1st run = 19166019	 
  {"27GeV_2018m",	              	     20180616,  54852, "y2018z", "27GeV_2018"}, // 1st run = 19167003			 
  {"26p5GeV_fixedTarget_2018k",	      	     20180617,  12950, "y2018z", "26p5GeV_fixedTarget_2018"}, // 1st run = 19167050	 
  {"27GeV_2018n",	              	     20180617, 143102, "y2018z", "27GeV_2018"}, // 1st run = 19168025			 
  {"26p5GeV_fixedTarget_2018l",	      	     20180618,  11601, "y2018z", "26p5GeV_fixedTarget_2018"}, // 1st run = 19168041	 

  {"y2019",       20181215,     0, "y2019",    "y2019 development geometry, AgML,xgeometry"},   
  {"y2019a",      20181215,     1, "y2019a",   "y2019a first production release geometry, AgML,xgeometry"},   
  {"y2019b",      20181215,     1, "y2019b",   "y2019a production geometry (FXT @ 200.7cm), AgML,xgeometry"},   
  {"y2019z",      20181215,     2, "y2019z",   "y2019z production geometry (FXT @ 200.7cm),     ,xgeometry"},   
  {"r2019",       20181220,     0, "y2019z",   "y2019z, iTPC, Jim Thomas 05/31/16, no HFT"}, // 
  {"r2019b",      20181220,     0, "y2019z",   "y2019z, iTPC, Jim Thomas 05/31/16, no HFT"}, // 
  {"Cosmic_2019",  			     20190109, 211356, "y2019z", "Cosmic_2019/ZF"}, 
  {"Cosmic_2019/ZF",  			     20190109, 211356, "y2019z", "Cosmic_2019/ZF"}, 
  {"Cosmic_2019/FF",                         20190118, 210113, "y2019z", "Cosmic_2019/FF"}, 
  {"Cosmic_2019/RF",  			     20190204, 205949, "y2019z", "Cosmic_2019/RF"}, 
  {"Cosmic_2019_ZF",  			     20190109, 211356, "y2019z", "Cosmic_2019_ZF"}, 
  {"Cosmic_2019_FF",                         20190118, 210113, "y2019z", "Cosmic_2019_FF"}, 
  {"Cosmic_2019_RF",  			     20190204, 205949, "y2019z", "Cosmic_2019_RF"}, 
  {"19GeV_2019",	              	     20190225, 202320, "y2019z", "19GeV_2019"}, // 1st run = 20056032			 
  {"14p5GeV_2019",	              	     20190404,  94405, "y2019z", "14p5GeV_2019"}, // 1st run = 20094048			 
  {"7.3GeV_fixedTarget_2019",	      	     20190417, 133401, "y2019z", "7.3GeV_fixedTarget_2019"}, // 1st run = 20107029	 
  {"14p5GeV_2019b",	              	     20190417, 141246, "y2019z", "14p5GeV_2019"}, // 1st run = 20107030			 
  {"7.3GeV_fixedTarget_2019b",	      	     20190423, 155418, "y2019z", "7.3GeV_fixedTarget_2019"}, // 1st run = 20113042	 
  {"14p5GeV_2019c",	              	     20190423, 181158, "y2019z", "14p5GeV_2019"}, // 1st run = 20113051			 
  {"7p7GeV_2019",	              	     20190603, 223655, "y2019z", "7p7GeV_2019"}, // 1st run = 20154047			 
  {"3p85GeV_fixedTarget_2019",	      	     20190607, 174702, "y2019z", "3p85GeV_fixedTarget_2019"}, // 1st run = 20158041	 
  {"7p7GeV_2019b",	              	     20190607, 202244, "y2019z", "7p7GeV_2019"}, // 1st run = 20158048			 
  {"3p85GeV_fixedTarget_2019b",	      	     20190609, 130005, "y2019z", "3p85GeV_fixedTarget_2019"}, // 1st run = 20160024	 
  {"7p7GeV_2019c",	              	     20190610,  24109, "y2019z", "7p7GeV_2019"}, // 1st run = 20160036			 
  {"7.3GeV_fixedTarget_2019c",	      	     20190618, 143658, "y2019z", "7.3GeV_fixedTarget_2019"}, // 1st run = 20169028	 
  {"7p7GeV_2019d",	              	     20190619,  25126, "y2019z", "7p7GeV_2019"}, // 1st run = 20169058			 
  {"9p2GeV_2019",	              	     20190628,  81931, "y2019z", "9p2GeV_2019"}, // 1st run = 20179015			 
  {"4p59GeV_fixedTarget_2019",	      	     20190629,  32834, "y2019z", "4p59GeV_fixedTarget_2019"}, // 1st run = 20179039	 
  {"9p2GeV_2019b",	              	     20190704, 210347, "y2019z", "9p2GeV_2019"}, // 1st run = 20185031			 
  {"31GeV_fixedTarget_2019",	      	     20190709,  32312, "y2019z", "31GeV_fixedTarget_2019"}, // 1st run = 20189035	 
  {"AuAu200_2019",	              	     20190710, 110157, "y2019z", "AuAu200_2019"}, // 1st run = 20191005			 
  {"AuAu200GeV_2019",	              	     20190710, 110157, "y2019z", "AuAu200_2019"}, // 1st run = 20191005			 
  {"9p2GeV_2019c",	              	     20190715,  85141, "y2019z", "9p2GeV_2019"}, // 1st run = 20196006			 

  {"y2020",       20191115,     0, "y2020b",    "y2020 development geometry, AgML,xgeometry"},   
  {"y2020a",      20191115,     1, "y2020b",    "y2020 fast-offline geometry, AgML,xgeometry"},   
  {"y2020b",      20191115,     2, "y2020b",    "y2020 production geometry (FXT @ 200.7 cm), AgML,xgeometry"},   
  {"y2020z",      20191115,     3, "y2020z",    "y2020 production geometry (FXT @ 200.7 cm),      xgeometry"},   
  {"r2020",       20191120,180000, "y2020z",    "y2020z, iTPC, Jim Thomas 05/31/16, no HFT"}, // 
  {"r2020a",      20191120,180001, "y2020z",    "y2020z, iTPC, Jim Thomas 05/31/16, no HFT"}, // 
  {"r2020b",      20191120,180001, "y2020z",    "y2020z, iTPC, Jim Thomas 05/31/16, no HFT"}, // 
  {"Cosmic_2020",  			     20191125, 202022, "y2020z", "Cosmic_2020/ZF"}, 
  {"Cosmic_2020/ZF",  			     20191125, 202022, "y2020z", "Cosmic_2020/ZF"}, 
  {"Cosmic_2020/RF",  			     20191128,  51555, "y2020z", "Cosmic_2020/RF"}, 
  {"Cosmic_2020_ZF",  			     20191125, 202022, "y2020z", "Cosmic_2020_ZF"}, 
  {"Cosmic_2020_RF",  			     20191128,  51555, "y2020z", "Cosmic_2020_RF"}, 
  {"11p5GeV_2020",	                     20191208,  91308, "y2020z", "11p5GeV"}, // 1st run = 20342002			 
  {"5p75GeV_fixedTarget_2020",	      	     20191221, 154021, "y2020z", "5p75GeV_fixedTarget"}, // 1st run = 20355020           
  {"11p5GeV_2020b",	                     20191221, 190032, "y2020z", "11p5GeV"}, // 1st run = 20355023
  {"31p2GeV_fixedTarget_2020",	             20200128, 185958, "y2020z", "31p2GeV_fixedTarget"}, // 1st run = 21028013
  {"9p8GeV_fixedTarget_2020",	             20200130,   5840, "y2020z", "9p8GeV_fixedTarget"}, // 1st run = 21029051
  {"9p2GeV_2020",	                     20200131,  12112, "y2020z", "9p2GeV"}, // 1st run = 21030030
  {"9p8GeV_fixedTarget_2020b",	             20200131,  50328, "y2020z", "9p8GeV_fixedTarget"}, // 1st run = 21031001		     
  {"19p5GeV_fixedTarget_2020",	             20200201, 191904, "y2020z", "19p5GeV_fixedTarget"}, // 1st run = 21032046		     
  {"13p5GeV_fixedTarget_2020",	             20200202, 160409, "y2020z", "13p5GeV_fixedTarget"}, // 1st run = 21033026		     
  {"9p2GeV_2020b",	                     20200203, 202534, "y2020z", "9p2GeV"}, // 1st run = 21034022			     
  {"7p3GeV_fixedTarget_2020",	             20200204,  53518, "y2020z", "7p3GeV_fixedTarget"}, // 1st run = 21035003		     
  {"9p2GeV_2020c",	                     20200205, 144626, "y2020z", "9p2GeV"}, // 1st run = 21036017			     
  {"11p5GeV_2020c",	                     20200210, 220428, "y2020z", "11p5GeV"}, // 1st run = 21041025			     
  {"5p75GeV_fixedTarget_2020b",	             20200213, 152339, "y2020z", "5p75GeV_fixedTarget"}, // 1st run = 21044023		     
  {"11p5GeV_2020d",	                     20200214, 143742, "y2020z", "11p5GeV"}, // 1st run = 21045014			     
  {"9p2GeVb_2020",                           20200224, 230740, "y2020z", "9p2GeVb"}, // 1st run = 21055032 
  {"9p2GeVc_2020",	              	     20200617, 233208, "y2020z", "9p2GeVc"}, // 1st run = 21169035			     
  {"9p2GeVc_2020b",	                     20200730,  42836, "y2020z", "9p2GeVc"}, // 1st run = 21212001			     
  {"26p5GeV_fixedTarget_2020",	             20200813, 213251, "y2020z", "26p5GeV_fixedTarget"}, // 1st run = 21226023		     
  {"9p2GeVc_2020c",	                     20200814,  54357, "y2020z", "9p2GeVc"}, // 1st run = 21227004			     
  {"26p5GeV_fixedTarget_2020b",	             20200819, 192253, "y2020z", "26p5GeV_fixedTarget"}, // 1st run = 21232025		     
  {"9p2GeVc_2020d",	                     20200820,  55402, "y2020z", "9p2GeVc"}, // 1st run = 21233002			     
  {"26p5GeV_fixedTarget_2020c",	             20200827, 143507, "y2020z", "26p5GeV_fixedTarget"}, // 1st run = 21240017		     
  {"9p2GeVc_2020e",	                     20200828,  64250, "y2020z", "9p2GeVc"}, // 1st run = 21241005			     
  {"7p7GeV_2020",	                     20200902, 105440, "y2020z", "7p7GeV"}, // 1st run = 21246012			     
  {"26p5GeV_fixedTarget_2020d",	             20200907, 221141, "y2020z", "26p5GeV_fixedTarget"}, // 1st run = 21251020		     
  {"7p7GeV_2020b",	                     20200910,  41639, "y2020z", "7p7GeV"}, // 1st run = 21254001			     
  {"26p5GeV_fixedTarget_2020e",	             20200912, 102033, "y2020z", "26p5GeV_fixedTarget"}, // 1st run = 21256006		     
 
  {"y2021",       20201215,     0, "y2021b",    "y2021b development geometry, AgML,xgeometry"},   
  {"y2021a",      20201215,     1, "y2021b",    "y2021ba first production release geometry, AgML,xgeometry"},   
  {"y2021b",      20201215,     1, "y2021b",    "y2021ba first production release geometry, AgML,xgeometry"},   
  {"y2021z",      20201215,     2, "y2021z",    "y2021za first production release geometry,      xgeometry"},   
  {"r2021",       20201220,     0, "y2021z",    "y2021z, iTPC, Jim Thomas 05/31/216, no HFT"}, // 
  {"r2021a",      20201220,     1, "y2021z",    "y2021z, iTPC, Jim Thomas 05/31/16, no HFT"}, // 
  {"r2021b",      20201220,     1, "y2021z",    "y2021z, iTPC, Jim Thomas 05/31/16, no HFT"}, // 
  {"Cosmic_2021_ZF",  			     20210129,  41915, "y2021z", "Cosmic_2021_ZF"}, 
  {"Cosmic_2021_RF",  			     20210129, 210413, "y2021z", "Cosmic_2021_RF"}, 
  {"7p7GeV_2021",	                     20210131, 194041, "y2021z", "7p7GeV_2021"}, // 1st run = 22031042			     
  {"Cosmic_2021_FF",  			     20210303, 193715, "y2021z", "Cosmic_2021_FF"}, 
  {"3p85GeV_fixedTarget_2021",	             20210501, 165437, "y2021z", "3p85GeV_fixedTarget_2021"}, // 1st run = 22121033	     
  {"44p5GeV_fixedTarget_2021",	             20210506,  70146, "y2021z", "44p5GeV_fixedTarget_2021"}, // 1st run = 22126010	     
  {"70GeV_fixedTarget_2021",	             20210507,  31639, "y2021z", "70GeV_fixedTarget_2021"}, // 1st run = 22126045	     
  {"100GeV_fixedTarget_2021",	             20210508,  41526, "y2021z", "100GeV_fixedTarget_2021"}, // 1st run = 22128001	     
  {"OO_200GeV_2021",	                     20210510, 134726, "y2021z", "OO_200GeV_2021"}, // 1st run = 22130029	  	     
  {"ps_OO_200GeV_2021",	              	     20210513,  83120, "y2021z", "ps_OO_200GeV_2021"}, // 1st run = 22133004	  	     
  {"OO_200GeV_2021b",	              	     20210513,  84422, "y2021z", "OO_200GeV_2021"}, // 1st run = 22133005	  	     
  {"ps_OO_200GeV_2021b",	             20210516, 112015, "y2021z", "ps_OO_200GeV_2021"}, // 1st run = 22136011	  	     
  {"FF_OO_200GeV_2021", 	             20210522,  23642, "y2021z", "FF_OO_200GeV_2021"}, // 1st run = 22141038	  	     
  {"17p3GeV_2021",	              	     20210525, 113236, "y2021z", "17p3GeV_2021"}, // 1st run = 22145017           	     
  {"26p5GeV_fixedTarget_2021",	             20210604,  23045, "y2021z", "26p5GeV_fixedTarget_2021"}, // 1st run = 22154036	     
  {"17p3GeV_2021b",	                     20210604,  81455, "y2021z", "17p3GeV_2021"}, // 1st run = 22155004			     
  {"3p85GeV_fixedTarget_2021b",	             20210608,   4951, "y2021z", "3p85GeV_fixedTarget_2021"}, // 1st run = 22158032	     
  {"26p5GeV_fixedTarget_2021b",	             20210617, 224533, "y2021z", "26p5GeV_fixedTarget_2021"}, // 1st run = 22168039	     
  {"3p85GeV_fixedTarget_2021c",	             20210618,  40935, "y2021z", "3p85GeV_fixedTarget_2021"}, // 1st run = 22169001	     
  {"26p5GeV_fixedTarget_2021c",	             20210627, 152747, "y2021z", "26p5GeV_fixedTarget_2021"}, // 1st run = 22178019	     
  {"3p85GeV_fixedTarget_2021d",	             20210628, 115428, "y2021z", "3p85GeV_fixedTarget_2021"}, // 1st run = 22179020	     
  {"dAu200_2021",	                     20210630,  22849, "y2021z", "dAu200_2021"}, // 1st run = 22180043			     
  {"26p5GeV_fixedTarget_2021d",	             20210703,  10650, "y2021z", "26p5GeV_fixedTarget_2021"}, // 1st run = 22183024	     
  {"dAu200_2021b",	                     20210703,  53033, "y2021z", "dAu200_2021"}, // 1st run = 22184001			     
  {"26p5GeV_fixedTarget_2021e",	             20210703, 230657, "y2021z", "26p5GeV_fixedTarget_2021"}, // 1st run = 22184017	     
  {"dAu200_2021c",	                     20210704,  34046, "y2021z", "dAu200_2021"}, // 1st run = 22184023			     

  {"y2022",       20211015,     0, "y2022b",    "y2022b development geometry, AgML,xgeometry"},   
  {"y2022a",      20211015,     1, "y2022b",    "y2022b development geometry, AgML,xgeometry"},   
  {"y2022b",      20211015,     1, "y2022b",    "y2022b development geometry, AgML,xgeometry"},   
  {"y2022z",      20211015,     2, "y2022z",    "y2022b development geometry,      xgeometry"},   
  {"r2022",       20211025,     0, "y2022z",    "y2022z, iTPC, Jim Thomas 05/31/16, no HFT"}, // 
  {"r2022a",      20211025,     1, "y2022z",    "y2022z, iTPC, Jim Thomas 05/31/16, no HFT"}, // 
  {"r2022b",      20211025,     1, "y2022z",    "y2022z, iTPC, Jim Thomas 05/31/16, no HFT"}, // 
  {"Cosmic_2022_ZF",  			     20211110, 215909, "y2022", "Cosmic_2022/ZF"}, 
  {"Cosmic_2022_RF",  			     20211111,  51637, "y2022", "Cosmic_2022_RF"}, 
  {"Cosmic_2022_FF",  			     20211115, 193307, "y2022", "Cosmic_2022_FF"}, 
  {"pp500_2022",  20211215, 81702, "y2022z",     "pp500_2022"}, // 1st run = 22349011			     

  {"y2023",       20221215,     0, "y2023a",    "y2023a development geometry, AgML,xgeometry"},   
  {"y2023a",      20221215,     1, "y2023a",    "y2023a development geometry, AgML,xgeometry"},   
  {"y2023z",      20221215,     2, "y2023z",    "y2023a development geometry,      xgeometry"},   
  {"r2023",       20221225,     0, "y2023z",    "y2023z"}, // 
  {"r2023a",      20221225,     1, "y2023z",    "y2023z"}, // 
  {"Cosmic_2023",  			     20230507,  55732, "y2023z", "Cosmic_2023/FF"}, 
  {"Cosmic_2023_FF",  			     20230507,  55732, "y2023z", "Cosmic_2023_FF"}, 
  {"Cosmic_2023_ZF",  			     20230508, 195057, "y2023z", "Cosmic_2023_ZF"}, 
  {"Cosmic_2023_RF",  			     20230509, 181952, "y2023z", "Cosmic_2023_RF"}, 
  {"AuAu_2023",	                             20230520,  23250, "y2023z", "AuAu_2023"}, // 1st run = 24139094			     

  {"y2024",       20231210,     0, "y2024a",    "y2019 first cut geometry, AgML,xgeometry"},    
  {"y2024a",      20231210,     0, "y2024a",    "y2019 first cut geometry, AgML,xgeometry"},    
  {"y2024b",      20231210,     1, "y2024b",   "y2019a production geometry, AgML,xgeometry"},    
  {"y2024z",      20231210,     2, "y2024z",   "y2019z production geometry,      xgeometry"},    
  {"r2024",       20231220,     0, "y2024z",    "y2019 first cut geometry, AgML,xgeometry"},    
  {"r2024a",      20231220,     1, "y2024z",   "y2019a production geometry, AgML,xgeometry"},    
  {"r2024b",      20231220,     1, "y2024z",   "y2019a production geometry, AgML,xgeometry"},    
  {"Cosmic_2024_ZF",  			     20240403,  20814, "y2024z", "Cosmic_2024_ZF"}, 
  {"Cosmic_2024_FF",  			     20240407, 125531, "y2024z", "Cosmic_2024_FF"}, 
  {"Cosmic_2024_RF",  			     20240416, 161358, "y2024z", "Cosmic_2024_RF"}, 
  {"Cosmic_2024_RFA", 			     20240416, 161358, "y2024z", "Cosmic_2024/RFA"}, 
  {"pp200_lowlumi",	                     20240430,  70551, "y2024z", "pp200_lowlumi"}, // 1st run = 25121013		     
  {"pp200_LowLuminosity",	             20240430,  74640, "y2024z", "pp200_LowLuminosity"}, // 1st run = 25121016		     
  {"pp200_HighLuminosity",	             20240513, 173321, "y2024z", "pp200_HighLuminosity"}, // 1st run = 25134037		     
  {"pp200_LowLuminosity_b",	             20240514,  11109, "y2024z", "pp200_LowLuminosity"}, // 1st run = 25134054		     
  {"pp200_HighLuminosity_b",	             20240517,  35506, "y2024z", "pp200_HighLuminosity"}, // 1st run = 25137047		     
  {"pp200_radial",	                     20240517, 205711, "y2024z", "pp200_radial"}, // 1st run = 25138053			     
  {"pp200_HighLuminosity_c",	             20240518,  52353, "y2024z", "pp200_HighLuminosity"}, // 1st run = 25139005		     
  {"pp200_radial_a",	                     20240520, 220203, "y2024z", "pp200_radial"}, // 1st run = 25141034			     
  {"Cosmic_2024_RFB", 			     20240521,  84436, "y2024z", "Cosmic_2024/RFB"}, 
  {"pp200_unpolarized",	                     20240529,  22850, "y2024z", "pp200_unpolarized"}, // 1st run = 25149057		     
  {"pp200_HighLuminosity_d",	             20240607,  71454, "y2024z", "pp200_HighLuminosity"}, // 1st run = 25159009		     
  {"pp200_radial_b",	                     20240607, 124232, "y2024z", "pp200_radial"}, // 1st run = 25159020		 	     
  {"pp200_unpolarized_b",	             20240613,  42200, "y2024z", "pp200_unpolarized"}, // 1st run = 25165001	 	     
  {"pp200_radial_d",	              	     20240616, 160307, "y2024z", "pp200_radial"}, // 1st run = 25168022		 	     
  {"pp200_unpolarized_c",	             20240801, 175519, "y2024z", "pp200_unpolarized"}, // 1st run = 25214020	 	     
  {"pp200_radial_e",	              	     20240802,  70632, "y2024z", "pp200_radial"}, // 1st run = 25215009          	     
  {"AuAu_2024",	                             20241006, 124742, "y2024z", "AuAu_2024"}, // 1st run = 25280025                         
  {"y2025",                                  20241210,      0, "y2025",  "y2025 first cut geometry, AgML,xgeometry"},    
  {"y2025z",                                 20241210,      1, "y2025z", "y2025z first cut geometry,      xgeometry"},    
  {"r2025",                                   20241220,     0, "y2025z",  "y2025z first cut geometry"},    
  {"Cosmic_2025",  			     20250318,  81438, "y2025z",  "Cosmic_2025_RF"}, //  itpcPadGainT0 => beginTime =  2025-03-18 08:14:38
  {"Cosmic_2025_RF",  			     20250318,  81438, "y2025z",  "Cosmic_2025_RF"}, //  itpcPadGainT0 => beginTime =  2025-03-18 08:14:38
  {"Cosmic_2025_ZF",  			     20250402,     27, "y2025z",  "Cosmic_2025_ZF"}, 
  {"Cosmic_2025_FF",  			     20250402, 202321, "y2025z",  "Cosmic_2025_FF"}, 

  {"athena",                                 20301220,      1,      "",         "athena"}, // 
  {"epic",                                   20301221,      1,      "",           "epic"}, // 
  {0,                                               0,      0,       0,                0}
};
#endif /*  __GeometryDbAliases__ */
