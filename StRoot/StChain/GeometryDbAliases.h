#ifndef __GeometryDbAliases__
#define __GeometryDbAliases__
static const DbAlias_t fDbAlias[] = {// geometry  Comment            old 
//{"sd97",        19970101,     0, "year2000", ""},                   //       {"sd97",        19970101,     0}
//{"sd98",        19980101,     0, "year2000", ""},                   //       {"sd98",        19980101,     0}
//{"y1a",         19990101,     0, "year2000", ""}, 
//{"year_1a",     19990101,     0, "year2000", ""},                   //       {"year_1a",     19990101,     0}
//{"y1b",         19990501,     0, "year2000", ""}, 
//{"year_1b",     19990501,     0, "year2000", ""},                   //       {"year_1b",     19990501,     0}
//{"y1s",         19990501,     0, "year2000", ""}, 
//{"year_1s",     19990501,     0, "year2000", ""}, 
//{"es99",        19990615,     0, "year2000", ""},                   //       {"es99",        19990615,     0}
//{"er99",        19990616,120000, "year2000", ""},                   //       {"er99",        19990616,120000}
//{"year_1c",     19991001,     0, "year2000", ""},                   //       {"year_1c",     19991001,     0}
//{"y1d",         19991101,     0, "year2000", ""}, 
//{"year_1d",     19991101,     0, "year2000", ""},                   //       {"year_1d",     19991101,     0}
//{"y1e",         19991201,     0, "year2000", ""}, 
//{"year_1e",     19991201,     0, "year2000", ""},                   //       {"year_1e",     19991201,     0}
//{"dc99",        19991206, 80000, "year2000", ""},                   //       {"dc99",        19991206, 80000}
  {"y1h",         20000614,175430, "year2000", ""}, 
  {"y2000",       20000614,175430, "year2000", ""},                   //       {"y2000",       20000614,175430}
//{"y2b",         20010501,     0, "year_2b",  ""},
  {"y2001",       20010501,     0, "year2001", "xgeometry"},
//{"year_2b",     20010501,     0, "year_2b",  ""},                   //       {"year_2b",     20010501,     0}
//{"year2002",    20010502,     0, "year2002", ""},
//{"y2a",         20010610,     0, "year_2a",  ""}, 
//{"year_2a",     20010610,     0, "year_2a",  ""},                   //       {"year_2a",     20010610,     0}
  {"y2001n",      20010615,     0, "year2001", "xgeometry"}, 
//{"year2001",    20010615,     0, "year2001", ""},                   //       {"year2001",    20010615,     0}
//{"y2003",       20021215,     0, "year2003", "xgeometry"}, 
//{"year2003",    20021215,     0, "year2003", ""},                   //       {"year2003",    20021215,     0}
  {"y2003",       20021215,     1, "y2003x",   "xgeometry"},  
  {"y2003x",      20021215,     1, "y2003x",   "xgeometry"},                   //       {"y2003x",      20021215,     0}
//{"y2003a",      20021215,     2, "y2003a",   ""},                   //       {"y2003a",      20021215,     0}
//{"y2003b",      20021215,     3, "y2003b",   ""},                   //       {"y2003b",      20021215,     0}
//{"y2003c",      20021215,     4, "y2003c",   "new SVT"}, 
  {"r2003",       20021120,     0, "y2003x", "xgeometry"}, 
//{"y2004",       20031215,     0, "y2004",    "xgeometry"},                   //       {"y2004",       20031120,     0}
//{"y2004x",      20031215,     1, "y2004x",   ""},                   //       {"y2004x",      20031120,     0}
//{"y2004y",      20031215,     2, "y2004y",   "xgeometry"},  
  {"y2004a",      20031215,     3, "y2004a",   "xgeometry"},                   //       {"y2004a",      20031120,     0}
//{"y2004b",      20031215,     4, "y2004b",   ""},                   //       {"y2004b",      20031120,     0}
  {"y2004",       20031216,     0, "y2004c",   "xgeometry"},                   //       {"y2004c",      20031125,     0}
  {"y2004c",      20031216,     0, "y2004c",   "xgeometry"},                   //       {"y2004c",      20031125,     0}
//{"y2004d",      20031216,     1, "y2004d",   "new SVT"},
  {"r2004",       20040109,  5425, "y2004c",   "xgeometry"},                   //       {"y2004c",      20031125,     0}
  
  // Dead area in SSD, in version y2005f
  {"y2005x",      20041030,     0, "y2005x",   "xgeometry"},                   //       {"y2005x",      20041030,     0}
//{"y2005",       20041030,     0, "y2005",    "xgeometry"},                   //       {"y2005",       20041030,     0}
  {"y2005b",      20041101,     0, "y2005b",   "xgeometry"},                   //       {"y2005b",      20041101,     0}
//{"y2005c",      20041201,     0, "y2005c",   ""},                   //       {"y2005c",      20041201,     0}
//{"y2005d",      20041201,     1, "y2005d",   "y2005c + new SVT"},   //       {"y2005d",      20041201,     0}
//{"y2005e",      20041201,     2, "y2005e",   "y2005d + new SSD"},   //       {"y2005e",      20041201,     0}
//{"y2005f",      20041201,     3, "y2005f",   "y2005e + SSD5/CALB2,AgML,xgeometry"},//       {"y2005e",      20041201,     0}
//{"y2005g",      20041201,     4, "y2005g",   "y2005f + SVT dead material,AgML,xgeometry"},//{"y2005e",      20041201,     0}
//{"y2005h",      20041201,     5, "y2005h",   "y2005g + TPC2009 ,AgML,xgeometry"},
  {"y2005",       20041201,     6, "y2005i",   "y2005h + ECALv6  ,AgML,xgeometry"},
  {"y2005i",      20041201,     6, "y2005i",   "y2005h + ECALv6  ,AgML,xgeometry"},
  {"r2005",       20041220,     0, "y2005i",   "y2005h + ECALv6  ,AgML,xgeometry"},

  // Dead area in SSD, in version y2006b
//{"y2006",       20051201,     0, "y2006",    "base for y2006: y2005e+fixed TPC plane,AgML,xgeometry"},
//{"y2006a",      20051201,     1, "y2006a",   "y2006+new FPD"},
//{"y2006b",      20051201,     2, "y2006b",   "y2006+new FPD+SSD5/CALB2"},// code versions indicated
//{"y2006c",      20051201,     3, "y2006c",   "y2006+new FPD+SSD5/CALB2+noPMD,AgML,xgeometry"},// 
//{"y2006g",      20051201,     4, "y2006g",   "y2006c + SVT dead material,AgML,xgeometry"},
  {"y2006",       20051201,     5, "y2006h",   "y2006g + ecal6+tpc2009(JW),AgML,xgeometry"},
  {"y2006h",      20051201,     5, "y2006h",   "y2006g + ecal6+tpc2009(JW),AgML,xgeometry"},
  {"r2006",       20051220,     0, "y2006h",   "y2006g + ecal6+tpc2009(JW),AgML,xgeometry"},

  // in preparation
//{"y2007",       20061105,     0, "y2007",    "base geometry for y2007,AgML,xgeometry"}, // advertized simu 20061101
//{"y2007a",      20061105,     1, "y2007a",    "the material of the water channels is now carbon "}, // advertized simu 20061101
  {"y2007g",      20061105,     4, "y2007g",   "y2007b + SVT dead material,AgML,xgeometry"},
  {"y2007",       20061105,     5, "y2007h",   "y2007g + TPC2009,AgML,xgeometry"},
  {"y2007h",      20061105,     5, "y2007h",   "y2007g + TPC2009,AgML,xgeometry"},
  {"r2007",       20061220,     0, "y2007h",   "y2007g + TPC2009,AgML,xgeometry"},

  // SVT/SSD is out
//{"y2008",       20071101,     0, "y2008",    "base for y2008: SVT/SSD out, cone is lost,AgML,xgeometry"},
  {"y2008a",      20071101,     1, "y2008a",   "base for y2008: SVT/SSD out, cone in separate SCON,AgML,xgeometry"},
//{"y2008b",      20071101,     2, "y2008b",   "base for y2008: SVT/SSD out, latest TPC ECAL CALB,AgML,xgeometry"},
//{"y2008c",      20071101,     3, "y2008c",   "TOF fix & TPCE redused,AgML,xgeometry"},
//{"y2008d",      20071101,     4, "y2008d",   "Honey sandwich fix,AgML,xgeometry"},
  {"y2008",       20071101,     5, "y2008e",   "LOW_EM central calorimter cuts,AgML,xgeometry"},
  {"y2008e",      20071101,     5, "y2008e",   "LOW_EM central calorimter cuts,AgML,xgeometry"},
  {"r2008",       20071220,     0, "y2008e",   "LOW_EM central calorimter cuts,AgML,xgeometry"},
  // 

//{"y2009",       20081215,     0, "y2009",    "based on TGeomanager of YF,AgML,xgeometry"},
  {"y2009a",      20081215,     1, "y2009a",   "y2009+ecalgeo6(JW),AgML,xgeometry"},
//{"y2009b",      20081215,     2, "y2009b",   "y2009+ecalgeo6(JW) w/ old tracking cuts in eemc.,AgML,xgeometry"},
//{"y2009c",      20081215,     3, "y2009c",   "TOF fix & TPCE redused,AgML,xgeometry"},
  {"y2009",       20081215,     4, "y2009d",   "Honey sandwich fix,AgML,xgeometry"},
  {"y2009d",      20081215,     4, "y2009d",   "Honey sandwich fix,AgML,xgeometry"},
  {"r2009",       20081220,     0, "y2009d",   "Honey sandwich fix,AgML,xgeometry"},

//{"y2010x",      20091215,     0, "y2010x",   "Y2010 asymptotic, AgML,xgeometry"},
//{"y2010",       20091215,     0, "y2010",    "y2009+full BTOF,AgML,xgeometry"},
  {"y2010a",      20091215,     1, "y2010a",   "y2010 production tag,AgML,xgeometry"},
//{"y2010b",      20091215,     2, "y2010b",   "TOF fix & TPCE redused,AgML,xgeometry"},
  {"y2010",       20091215,     3, "y2010c",   "Honey sandwich fix,AgML,xgeometry"},
  {"y2010c",      20091215,     3, "y2010c",   "Honey sandwich fix,AgML,xgeometry"},
  {"r2010",       20091220,     0, "y2010c",   "Honey sandwich fix,AgML,xgeometry"},

//{"y2011",       20101215,     0, "y2011",    "y2011 TOF fix & TPCE redused & honey,AgML,xgeometry"},
//{"y2011a",      20101215,     1, "y2011a",   "y2011a == y2011 now ,AgML,xgeometry"},
  {"y2011",       20101215,     2, "y2011b",   "y2011a + new TPC + Extended Cave and tunnel,xgeometry"},
  {"y2011b",      20101215,     2, "y2011b",   "y2011a + new TPC + Extended Cave and tunnel,xgeometry"},
  {"r2011",       20101220,     0, "y2011b",   "y2011a + new TPC + Extended Cave and tunnel,xgeometry"},

//{"y2012",       20111215,     0, "y2012",    "y2012 Very preliminary,AgML,xgeometry"},
  {"y2012a",      20111215,     1, "y2012a",   "y2012 geometry (MTD missing),AgML,xgeometry"},
  {"y2012b",      20111215,     2, "y2012b",   "y2012 geometry, now with MTD,AgML,xgeometry"},
  {"y2012",       20111215,     3, "y2012c",   "y2012 geometry, now with MTD, Extended Cave and tunnel, new TPC,xgeometry"},
  {"y2012c",      20111215,     3, "y2012c",   "y2012 geometry, now with MTD, Extended Cave and tunnel, new TPC,xgeometry"},
  {"r2012",       20111220,     0, "y2012c",   "y2012 geometry, now with MTD, Extended Cave and tunnel, new TPC,xgeometry"},

  {"y2013",       20121215,     0, "y2013_1", "y2013 first cut geometry,AgML,xgeometry"},
//{"y2013_1",     20121215,     1, "y2013_1", "y2013 first cut geometry with pixel,AgML,xgeometry"},
//{"y2013_2",     20121215,  1001, "y2013_2", "y2013 first cut geometry sans pixel,AgML,xgeometry"},

//{"y2013_1a",    20121215,     2, "y2013_1a", "y2013a first prod geometry, Extended Cave and tunnel, AgML,xgeometry"},
//{"y2013_2a",    20121215,  1002, "y2013_2a", "y2013a first prod geometry, Extended Cave and tunnel, sans pixel,AgML,xgeometry"},

//{"y2013_1b",    20121215,     3, "y2013_1b", "y2013b 2nd prod geometry, new TPC,           AgML,xgeometry"},
//{"y2013_2b",    20121215,  1003, "y2013_2b", "y2013b 2nd prod geometry sans pixel,new TPC, AgML,xgeometry"},

  {"y2013_1c",    20121215,     4, "y2013_1c", "y2013c, Extended Cave and tunnel,AgML,xgeometry"},
  {"y2013_2c",    20121215,  1004, "y2013_2c", "y2013c, Extended Cave and tunnel,AgML,xgeometry"},

//{"y2013_1d",    20121215,     5, "y2013_1d", "y2013d, new TPC,  Extended Cave and tunnel,xgeometry"},
//{"y2013_2d",    20121215,  1005, "y2013_2d", "y2013d, new TPC,  Extended Cave and tunnel,xgeometry"},

//{"y2013_1x",   20121215,   2001, "y2013_1x", "y2013x asymptotic geometry.             WARNING: Geometry may change between releases,AgML,xgeometry"},
//{"y2013_2x",   20121215,   3001, "y2013_2x", "y2013x asymptotic geometry sans pixel.  WARNING: Geometry may change between releases,AgML,xgeometry"},

//{"20130509.000000", 20130509, 0, "y2013_1",  "y2013 with pixel, real data,AgML,xgeometry"},
  {"20130509.000001", 20130509, 1, "y2013_1c", "y2013 with pixel, real data,AgML,xgeometry"},
  {"r2013",      20121220,      0, "y2013_2c", "y2013c asymptotic geometry sans pixel.  WARNING: Geometry may change between releases,AgML,xgeometry"},
  {"r2013_c2",   20121220,      0, "y2013_2c", "y2013c asymptotic geometry sans pixel.  WARNING: Geometry may change between releases,AgML,xgeometry"},
  {"r2013_c1",   20130509,      1, "y2013_1c", "y2013x asymptotic geometry with pixel.  WARNING: Geometry may change between releases,AgML,xgeometry"},
    

//{"y2014",       20131215,     0, "y2014",    "y2014 first cut geometry,AgML,xgeometry"},
  {"y2014a",      20131215,     1, "y2014a",   "y2014a 2014 preview geometry,AgML,xgeometry"},
//{"y2014b",      20131215,     2, "y2014b",   "y2014b production plus hcal prototype,AgML,xgeometry"},
  {"y2014",       20131215,     3, "y2014a",   "y2014c 2014 production geometry,IST overlap correction,AgML,xgeometry"},
  {"y2014c",      20131215,     3, "y2014a",   "y2014c 2014 production geometry,IST overlap correction,AgML,xgeometry"},
  {"r2014",       20131220,     0, "y2014a",   "y2014c new TPC rows,xgeometry"},

//{"y2015x",      20141215,     0, "y2015x",   "y2015x asymptotic geometry with IST overlap correction, AgML,xgeometry"},
//{"y2015a",      20141215,     1, "y2015a",   "y2015a production geometry, AgML,xgeometry"},
  {"y2015b",      20141215,     2, "y2015b",   "y2015b production geometry with MTD radii corrections, AgML,xgeometry"},
  {"y2015c",      20141215,     3, "y2015c",   "y2015c production geometry with MTD revised radii corrections, AgML,xgeometry"},
  {"y2015",       20141215,     4, "y2015d",   "y2015d production geometry with IST overlap correction, AgML,xgeometry"},
  {"y2015d",      20141215,     4, "y2015d",   "y2015d production geometry with IST overlap correction, AgML,xgeometry"},
//{"y2015x",      20141215,120000, "y2015x",   "y2015d production geometry with IST overlap correction, AgML,xgeometry"},
  {"r2015",       20141220,     4, "y2015d",   "y2015d production geometry with IST overlap correction, AgML,xgeometry"},

//{"y2016x",      20151215,     0, "y2016x",   "y2016 asymptotic geometry, AgML,xgeometry"},   // dev2016 is deprecated for reco
  {"y2016",       20151215,     0, "y2016",    "y2016 development geometry, AgML,xgeometry"},   // dev2016 is deprecated for reco
  {"y2016a",      20151215,     1, "y2016a",   "y2016 production geometry, AgML,xgeometry"},   // dev2016 is deprecated for reco
//{"y2016x",      20151215,120000, "y2016x",   "y2016 production geometry, AgML,xgeometry"},   // dev2016 is deprecated for reco
  {"r2016",       20151220,     0, "y2016",    "y2016 development geometry, AgML,xgeometry"},   // dev2016 is deprecated for reco
//{"y2017",       20161215,     0, "y2017",    "y2017 development geometry, AgML,xgeometry"},   
//{"r2017",       20161220,     0, "y2017",    "y2017 development geometry, AgML,xgeometry"},   
  {"y2017",       20161215,     1, "y2017a",   "y2017 production  geometry, AgML,xgeometry"},   
  {"y2017a",      20161215,     1, "y2017a",   "y2017 production  geometry, AgML,xgeometry"},   
  {"r2017a",      20161220,     1, "y2017a",   "y2017 production  geometry, AgML,xgeometry"},   
 
//{"y2018x",      20171215,     0, "y2018x",   "y2018x experimental TPC geometry, AgML,xgeometry"},   
  {"y2018",       20171215,     2, "y2018",    "y2018 development geometry, AgML,xgeometry"},   
  {"y2018a",      20171215,     3, "y2018",    "y2018a physics production geometry version A, AgML,xgeometry"},   
//{"y2018b",      20171215,     4, "y2018b",   "y2018b physics production geometry version B, AgML,xgeometry"},   
//{"y2018c",      20171215,     5, "y2018b",   "y2018c physics production geometry version C (FXT @ 200.7 cm), AgML,xgeometry"},   
  {"r2018",       20171220,     0, "y2018",    "y2018, no HFT,xgeometry"}, // 

  {"y2019",       20181215,     0, "y2019",    "y2019 development geometry, AgML,xgeometry"},   
  {"r2019",       20181220,     0, "y2019",    "y2019, iTPC, Jim Thomas 05/31/16, no HFT,xgeometry"}, // 
  {"y2019a",      20181215,     1, "y2019a",   "y2019a first production release geometry, AgML,xgeometry"},   
  {"y2019b",      20181215,     1, "y2019b",   "y2019a production geometry (FXT @ 200.7cm), AgML,xgeometry"},   

  {"y2020",       20191115,     0, "y2019",    "y2020 development geometry, AgML,xgeometry"},   
  {"y2020a",      20191115,     1, "y2019",    "y2020 fast-offline geometry, AgML,xgeometry"},   
  {"y2020b",      20191115,     2, "y2019",    "y2020 production geometry (FXT @ 200.7 cm), AgML,xgeometry"},   
  {"r2020",       20191120,180000, "y2019",    "y2019, iTPC, Jim Thomas 05/31/16, no HFT,xgeometry"}, // 
  {"r2020a",      20191120,180001, "y2019",    "y2019, iTPC, Jim Thomas 05/31/16, no HFT,xgeometry"}, // 
 
  {"y2021",       20201215,     0, "y2019",    "y2019 development geometry, AgML,xgeometry"},   
  {"y2021a",      20201215,     1, "y2019",    "y2019a first production release geometry, AgML,xgeometry"},   
  {"r2021",       20201220,     0, "y2019",    "y2019, iTPC, Jim Thomas 05/31/216, no HFT,xgeometry"}, // 
  {"r2021a",      20201220,     1, "y2019",    "y2019, iTPC, Jim Thomas 05/31/16, no HFT,xgeometry"}, // 
  {"y2021b",      20201215,     2, "y2021b",   "y2021 production geometry (FXT @ 200.7 cm), AgML,xgeometry"},   

  {"y2022",       20211015,     0, "y2019",    "y2019 development geometry, AgML,xgeometry"},   
  {"y2022a",      20211015,     1, "y2019",    "y2019 development geometry, AgML,xgeometry"},   
  {"r2022",       20211025,     0, "y2019",    "y2019, iTPC, Jim Thomas 05/31/16, no HFT,xgeometry"}, // 
  {"r2022a",      20211025,     1, "y2019",    "y2019, iTPC, Jim Thomas 05/31/16, no HFT,xgeometry"}, // 

  {"y2023",       20221215,     0, "y2019",    "y2019 development geometry, AgML,xgeometry"},   
  {"r2023",       20221225,     0, "y2019",    "y2019, iTPC, Jim Thomas 05/31/16, no HFT,xgeometry"}, // 
  {"y2023a",      20221215,     1, "y2019",    "y2019 development geometry, AgML,xgeometry"},   
  {"r2023a",      20221225,     1, "y2019",    "y2019, iTPC, Jim Thomas 05/31/16, no HFT,xgeometry"}, // 

  {"y2024",       20231210,     0, "y2019",    "y2019 first cut geometry, AgML,xgeometry"},    
  {"y2024a",      20231210,     1, "y2019a",   "y2019a production geometry, AgML,xgeometry"},    
  {"r2024",       20231220,     0, "y2019",    "y2019 first cut geometry, AgML,xgeometry"},    
  {"r2024a",      20231220,     1, "y2019a",   "y2019a production geometry, AgML,xgeometry"},    
  // Production runs
  {"AuAu200_2004",	                     20040109,   5425, "y2004", "productionMinBias"}, // 1st run = 5008155
  {"cu62_2005",	                             20050309, 200953, "y2005", "cu62productionMinBias"}, // 1st run = 6068018
  {"dAu2008",	                             20071130,  54621, "y2008", "dAu2008"}, // 1st run = 8334001
  {"pp2009_500GeV",	                     20090320,   4556, "y2009", "production2009_500GeV"}, // 1st run = 10078069
  {"pp2009_200GeV",	                     20090423,   5903, "y2009", "production2009_200GeV_Hi"}, // 1st run = 10112099
  {"AuAu200_2010",                           20100103,  24648, "y2010", "AuAu200"}, // 1st run = 11002120
  {"AuAu62_2010",                            20100318, 203224, "y2010", "AuAu62"}, // 1st run = 11077027
  {"AuAu39_2010",                            20100408, 205540, "y2010", "AuAu39"}, // 1st run = 11098073
  {"AuAu7_2010",	          	     20100421, 190639, "y2010", "AuAu7"}, // 1st run = 11111060 
  {"AuAu39_2010b",	              	     20100421, 205504, "y2010", "AuAu39"}, // 1st run = 11111064
  {"AuAu7_2010b",	              	     20100423,  24916, "y2010", "AuAu7"}, // 1st run = 11112066 
  {"AuAu11_2010",	            	     20100528,  33641, "y2010", "AuAu11"}, // 1st run = 11147048
  {"pp500_2011",	                     20110124,  62856, "y2011", "pp500_2011"}, // 1st run = 12024005
  {"AuAu18_2011",	                     20110418, 172118, "y2011", "AuAu18"}, // 1st run = 12108024
  {"AuAu19_2011",	                     20110422, 132801, "y2011", "AuAu19"}, // 1st run = 12112008
  {"AuAu200_2011",	                     20110504,  25334, "y2011", "AuAu200_2011"}, // 1st run = 12123006			 
  {"pp200_2012",	              	     20120207, 232951, "y2012", "pp200_2012"}, // 1st run = 13038144			 
  {"pp500_2012",	              	     20120312, 160952, "y2012", "pp500_2012"}, // 1st run = 13072028			 
  {"UU_2012",	                      	     20120423, 100915, "y2012", "UU_2012"}, // 1st run = 13114014			 
  {"cuAu_2012",	                      	     20120516, 192018, "y2012", "cuAu_2012"}, // 1st run = 13137009			 
  {"pp500_2013",	              	     20130315, 150531, "y2013", "pp500_2013"}, // 1st run = 14074055			 
  {"15GeV_2014",	              	     20140215, 214336, "y2014", "15GeV_2014"}, // 1st run = 15046070			 
  {"AuAu_200_2014",	              	     20140315, 190309, "y2014", "AuAu_200_2014"}, // 1st run = 15074070		 
  {"AuHe3_2014",	              	     20140619, 224357, "y2014", "AuHe3_2014"}, // 1st run = 15170056			 
  {"pp200long_2015",	              	     20150211,  12600, "y2015", "pp200long_2015"}, // 1st run = 16041202		 
  {"pp200trans_2015",	              	     20150306,  23145, "y2015", "pp200trans_2015"}, // 1st run = 16064077		 
  {"pp200long2_2015",	              	     20150404,  10123, "y2015", "pp200long2_2015"}, // 1st run = 16093061		 
  {"pAu200_2015",	              	     20150504, 205203, "y2015", "pAu200_2015"}, // 1st run = 16124017			 
  {"pAl200_2015",	              	     20150608, 202224, "y2015", "pAl200_2015"}, // 1st run = 16159031			 
  {"pAu200_2015b",	              	     20150610, 203824, "y2015", "pAu200_2015"}, // 1st run = 16161034			 
  {"pAl200_2015b",	              	     20150610, 235626, "y2015", "pAl200_2015"}, // 1st run = 16161036			 
  {"AuAu_200_2016",	              	     20160207, 171305, "y2016", "AuAu_200_2016"}, // 1st run = 17038050		 
  {"AuAu54_2017",	              	     20170602, 181634, "y2017", "AuAu54_2017"}, // 1st run = 18153035			 
  {"pp500_rhicf_2017",	              	     20170624,  23811, "y2017", "pp500_rhicf_2017"}, // 1st run = 18174051		 
  {"isobar_2018",	              	     20180312, 162439, "y2018", "isobar_2018"}, // 1st run = 19071038			 
  {"27GeV_2018",	              	     20180510, 201552, "y2018", "27GeV_2018"}, // 1st run = 19130060			 x1
  {"27GeV_fixedTarget_2018",	      	     20180518, 231602, "y2018", "27GeV_fixedTarget_2018"}, // 1st run = 19138032	 
  {"27GeV_2018b",	              	     20180519,  82150, "y2018", "27GeV_2018"}, // 1st run = 19139022			 
  {"27GeV_2018c",	              	     20180529,  23458, "y2018", "27GeV_2018"}, // 1st run = 19148050			 
  {"3p85GeV_fixedTarget_2018",	      	     20180531,  71446, "y2018", "3p85GeV_fixedTarget_2018"}, // 1st run = 19151029	 
  {"27GeV_2018d",	              	     20180605,  31540, "y2018", "27GeV_2018"}, // 1st run = 19155057			 
  {"26p5GeV_fixedTarget_2018",	      	     20180607, 225853, "y2018", "26p5GeV_fixedTarget_2018"}, // 1st run = 19158057	 
  {"27GeV_2018e",	              	     20180608,  11358, "y2018", "27GeV_2018"}, // 1st run = 19158059			 
  {"26p5GeV_fixedTarget_2018b",	      	     20180609,   1349, "y2018", "26p5GeV_fixedTarget_2018"}, // 1st run = 19159043	 
  {"27GeV_2018f",	              	     20180611,  15329, "y2018", "27GeV_2018"}, // 1st run = 19161048			 
  {"26p5GeV_fixedTarget_2018c",	      	     20180611, 180125, "y2018", "26p5GeV_fixedTarget_2018"}, // 1st run = 19162033	 
  {"27GeV_2018g",	              	     20180611, 193656, "y2018", "27GeV_2018"}, // 1st run = 19162036			 
  {"26p5GeV_fixedTarget_2018d",	      	     20180612,  30705, "y2018", "26p5GeV_fixedTarget_2018"}, // 1st run = 19162043	 
  {"27GeV_2018h",	              	     20180612,  65304, "y2018", "27GeV_2018"}, // 1st run = 19163006			 
  {"26p5GeV_fixedTarget_2018e",	      	     20180612, 144931, "y2018", "26p5GeV_fixedTarget_2018"}, // 1st run = 19163024	 
  {"27GeV_2018i",	              	     20180612, 214626, "y2018", "27GeV_2018"}, // 1st run = 19163039			 
  {"26p5GeV_fixedTarget_2018f",	      	     20180613,    956, "y2018", "26p5GeV_fixedTarget_2018"}, // 1st run = 19163042	 
  {"27GeV_2018j",	              	     20180613,  53758, "y2018", "27GeV_2018"}, // 1st run = 19164004			 
  {"26p5GeV_fixedTarget_2018g",	      	     20180614,   5924, "y2018", "26p5GeV_fixedTarget_2018"}, // 1st run = 19164022	 
  {"27GeV_2018k",	              	     20180614,  41305, "y2018", "27GeV_2018"}, // 1st run = 19165002			 
  {"26p5GeV_fixedTarget_2018i",	      	     20180614, 180439, "y2018", "26p5GeV_fixedTarget_2018"}, // 1st run = 19165030	 
  {"27GeV_2018l",	              	     20180615,  72506, "y2018", "27GeV_2018"}, // 1st run = 19166006			 
  {"26p5GeV_fixedTarget_2018j",	      	     20180616,  30539, "y2018", "26p5GeV_fixedTarget_2018"}, // 1st run = 19166019	 
  {"27GeV_2018m",	              	     20180616,  54852, "y2018", "27GeV_2018"}, // 1st run = 19167003			 
  {"26p5GeV_fixedTarget_2018k",	      	     20180617,  12950, "y2018", "26p5GeV_fixedTarget_2018"}, // 1st run = 19167050	 
  {"27GeV_2018n",	              	     20180617, 143102, "y2018", "27GeV_2018"}, // 1st run = 19168025			 
  {"26p5GeV_fixedTarget_2018l",	      	     20180618,  11601, "y2018", "26p5GeV_fixedTarget_2018"}, // 1st run = 19168041	 
//{"19GeV_2019",                             20190225, 202320, "y2019", "19GeV_2019"},
  {"19GeV_2019",	              	     20190225, 202320, "y2019", "19GeV_2019"}, // 1st run = 20056032			 
//{"14p5GeV_2019",                           20190404,  94405, "y2019", "14p5GeV_2019"},
  {"14p5GeV_2019",	              	     20190404,  94405, "y2019", "14p5GeV_2019"}, // 1st run = 20094048			 
//{"7.3GeV_fixedTarget_2019",                20190417, 133401, "y2019", "7.3GeV_fixedTarget_2019"},
  {"7.3GeV_fixedTarget_2019",	      	     20190417, 133401, "y2019", "7.3GeV_fixedTarget_2019"}, // 1st run = 20107029	 
//{"14p5GeV_2019b",                          20190417, 141246, "y2019", "14p5GeV_2019"},
  {"14p5GeV_2019b",	              	     20190417, 141246, "y2019", "14p5GeV_2019"}, // 1st run = 20107030			 
//{"7.3GeV_fixedTarget_2019b",               20190423, 155418, "y2019", "7.3GeV_fixedTarget_2019"},
  {"7.3GeV_fixedTarget_2019b",	      	     20190423, 155418, "y2019", "7.3GeV_fixedTarget_2019"}, // 1st run = 20113042	 
//{"14p5GeV_2019c",                          20190423, 181158, "y2019", "14p5GeV_2019"},
  {"14p5GeV_2019c",	              	     20190423, 181158, "y2019", "14p5GeV_2019"}, // 1st run = 20113051			 
//{"7p7GeV_2019",                            20190603, 223655, "y2019", "7p7GeV_2019"},
  {"7p7GeV_2019",	              	     20190603, 223655, "y2019", "7p7GeV_2019"}, // 1st run = 20154047			 
//{"3p85GeV_fixedTarget_2019",               20190607, 174702, "y2019", "3p85GeV_fixedTarget_2019"}, // 20190607/174124  run = 20158040	3p85GeV_fixedTarget_2019  V1      1.388 
  {"3p85GeV_fixedTarget_2019",	      	     20190607, 174702, "y2019", "3p85GeV_fixedTarget_2019"}, // 1st run = 20158041	 
//{"7p7GeV_2019b",                           20190607, 202244, "y2019", "7p7GeV_2019"},
  {"7p7GeV_2019b",	              	     20190607, 202244, "y2019", "7p7GeV_2019"}, // 1st run = 20158048			 
//{"3p85GeV_fixedTarget_2019b",              20190609, 124528, "y2019", "3p85GeV_fixedTarget_2019"},
  {"3p85GeV_fixedTarget_2019b",	      	     20190609, 130005, "y2019", "3p85GeV_fixedTarget_2019"}, // 1st run = 20160024	 
//{"7p7GeV_2019c",                           20190610,  24109, "y2019", "7p7GeV_2019"},
  {"7p7GeV_2019c",	              	     20190610,  24109, "y2019", "7p7GeV_2019"}, // 1st run = 20160036			 
//{"7.3GeV_fixedTarget_2019c",               20190618, 143658, "y2019", "7.3GeV_fixedTarget_2019"},
  {"7.3GeV_fixedTarget_2019c",	      	     20190618, 143658, "y2019", "7.3GeV_fixedTarget_2019"}, // 1st run = 20169028	 
//{"7p7GeV_2019d",                           20190619,  25126, "y2019", "7p7GeV_2019"},
  {"7p7GeV_2019d",	              	     20190619,  25126, "y2019", "7p7GeV_2019"}, // 1st run = 20169058			 
//{"9p2GeV_2019",                            20190628,  81931, "y2019", "9p2GeV_2019"},
  {"9p2GeV_2019",	              	     20190628,  81931, "y2019", "9p2GeV_2019"}, // 1st run = 20179015			 
//{"4p59GeV_fixedTarget_2019",               20190629,  32834, "y2019", "4p59GeV_fixedTarget_2019"},
  {"4p59GeV_fixedTarget_2019",	      	     20190629,  32834, "y2019", "4p59GeV_fixedTarget_2019"}, // 1st run = 20179039	 
//{"9p2GeV_2019b",                           20190702, 144151, "y2019", "9p2GeV_2019"},
  {"9p2GeV_2019b",	              	     20190704, 210347, "y2019", "9p2GeV_2019"}, // 1st run = 20185031			 
//{"31GeV_fixedTarget_2019",                 20190709,  32312, "y2019", "31GeV_fixedTarget_2019"},
  {"31GeV_fixedTarget_2019",	      	     20190709,  32312, "y2019", "31GeV_fixedTarget_2019"}, // 1st run = 20189035	 
//{"AuAu200_2019",                           20190710, 110157, "y2019", "AuAu200GeV_2019"},
  {"AuAu200_2019",	              	     20190710, 110157, "y2019", "AuAu200_2019"}, // 1st run = 20191005			 
//{"AuAu200GeV_2019",                        20190710, 110157, "y2019", "AuAu200GeV_2019"},
  {"AuAu200GeV_2019",	              	     20190710, 110157, "y2019", "AuAu200_2019"}, // 1st run = 20191005			 
//{"9p2GeV_2019c",                           20190715,  85141, "y2019", "9p2GeV_2019"},             //20190715/65240   run = 20196004	9p2GeV_2019c              V1      1.617 
  {"9p2GeV_2019c",	              	     20190715,  85141, "y2019", "9p2GeV_2019"}, // 1st run = 20196006			 
//{"11p5GeV_2020",                           20191208,  91308, "y2019", "11p5GeV_2020"},
  {"11p5GeV_2020",	                     20191208,  91308, "y2020", "11p5GeV"}, // 1st run = 20342002			 
//{"5p75GeV_fixedTarget_2020",               20191221, 154021, "y2019", "5p75GeV_fixedTarget_2020"},
  {"5p75GeV_fixedTarget_2020",	      	     20191221, 154021, "y2020", "5p75GeV_fixedTarget"}, // 1st run = 20355020           
//{"11p5GeV_2020b",                          20191221, 190032, "y2019", "11p5GeV_2020"},
  {"11p5GeV_2020b",	                     20191221, 190032, "y2020", "11p5GeV"}, // 1st run = 20355023
//{"31p2GeV_fixedTarget_2020",               20200128, 182912, "y2019", "31p2GeV_fixedTarget_2020"},
  {"31p2GeV_fixedTarget_2020",	             20200128, 185958, "y2020", "31p2GeV_fixedTarget"}, // 1st run = 21028013
//{"9p8GeV_fixedTarget_2020",                20200130,   5840, "y2019", "9p8GeV_fixedTarget_2020"},//20200131/50328   run = 21031001	9p8GeV_fixedTarget_2020b  V1    866.170 
  {"9p8GeV_fixedTarget_2020",	             20200130,   5840, "y2020", "9p8GeV_fixedTarget"}, // 1st run = 21029051
//{"9p2GeV_2020",                            20200131,  12112, "y2019", "9p2GeV_2020"},
  {"9p2GeV_2020",	                     20200131,  12112, "y2020", "9p2GeV"}, // 1st run = 21030030
//{"9p8GeV_fixedTarget_2020b",               20200131,  50328, "y2019", "9p8GeV_fixedTarget_2020"},
  {"9p8GeV_fixedTarget_2020b",	             20200131,  50328, "y2020", "9p8GeV_fixedTarget"}, // 1st run = 21031001		     
//{"19p5GeV_fixedTarget_2020",               20200201, 191904, "y2019", "19p5GeV_fixedTarget_2020"},
  {"19p5GeV_fixedTarget_2020",	             20200201, 191904, "y2020", "19p5GeV_fixedTarget"}, // 1st run = 21032046		     
//{"13p5GeV_fixedTarget_2020",               20200202, 160409, "y2019", "13p5GeV_fixedTarget_2020"},
  {"13p5GeV_fixedTarget_2020",	             20200202, 160409, "y2020", "13p5GeV_fixedTarget"}, // 1st run = 21033026		     
//{"9p2GeV_2020b",                           20200203, 202534, "y2019", "9p2GeV_2020"},
  {"9p2GeV_2020b",	                     20200203, 202534, "y2020", "9p2GeV"}, // 1st run = 21034022			     
//{"7p3GeV_fixedTarget_2020",                20200204,  53518, "y2019", "7p3GeV_fixedTarget_2020"},
  {"7p3GeV_fixedTarget_2020",	             20200204,  53518, "y2020", "7p3GeV_fixedTarget"}, // 1st run = 21035003		     
//{"9p2GeV_2020c",                           20200205, 144626, "y2019", "9p2GeV_2020"},
  {"9p2GeV_2020c",	                     20200205, 144626, "y2020", "9p2GeV"}, // 1st run = 21036017			     
//{"11p5GeV_2020c",                          20200210, 220428, "y2019", "11p5GeV_2020"},
  {"11p5GeV_2020c",	                     20200210, 220428, "y2020", "11p5GeV"}, // 1st run = 21041025			     
//{"5p75GeV_fixedTarget_2020b",              20200213, 152339, "y2019", "5p75GeV_fixedTarget_2020"},
  {"5p75GeV_fixedTarget_2020b",	             20200213, 152339, "y2020", "5p75GeV_fixedTarget"}, // 1st run = 21044023		     
//{"11p5GeV_2020d",                          20200214, 143742, "y2019", "11p5GeV_2020"},
  {"11p5GeV_2020d",	                     20200214, 143742, "y2020", "11p5GeV"}, // 1st run = 21045014			     
//{"9p2GeVb_2020",                           20200224, 230740, "y2019", "9p2GeVb_2020"},
  {"9p2GeVb_2020",                           20200224, 230740, "y2020", "9p2GeVb"}, // 1st run = 21055032 
//{"9p2GeVc_2020",                           20200617, 233208, "y2019", "9p2GeVc_2020"},
  {"9p2GeVc_2020",	              	     20200617, 233208, "y2020", "9p2GeVc"}, // 1st run = 21169035			     
//{"26p5GeV_fixedTarget_2020",               20200730,  15354, "y2019", "26p5GeV_fixedTarget_2020"},
//{"9p2GeVc_2020b",                          20200730,  42836, "y2019", "9p2GeVc_2020"},
  {"9p2GeVc_2020b",	                     20200730,  42836, "y2020", "9p2GeVc"}, // 1st run = 21212001			     
//{"26p5GeV_fixedTarget_2020b",              20200813, 213251, "y2019", "26p5GeV_fixedTarget_2020"},
  {"26p5GeV_fixedTarget_2020",	             20200813, 213251, "y2020", "26p5GeV_fixedTarget"}, // 1st run = 21226023		     
//{"9p2GeVc_2020c",                          20200814,  54357, "y2019", "9p2GeVc_2020"},
  {"9p2GeVc_2020c",	                     20200814,  54357, "y2020", "9p2GeVc"}, // 1st run = 21227004			     
//{"26p5GeV_fixedTarget_2020c",              20200819, 192253, "y2019", "26p5GeV_fixedTarget_2020"},
  {"26p5GeV_fixedTarget_2020b",	             20200819, 192253, "y2020", "26p5GeV_fixedTarget"}, // 1st run = 21232025		     
//{"9p2GeVc_2020d",                          20200820,  55402, "y2019", "9p2GeVc_2020"},
  {"9p2GeVc_2020d",	                     20200820,  55402, "y2020", "9p2GeVc"}, // 1st run = 21233002			     
//{"26p5GeV_fixedTarget_2020d",              20200827, 143507, "y2019", "26p5GeV_fixedTarget_2020"},
  {"26p5GeV_fixedTarget_2020c",	             20200827, 143507, "y2020", "26p5GeV_fixedTarget"}, // 1st run = 21240017		     
//{"9p2GeVc_2020e",                          20200828,  64250, "y2019", "9p2GeVc_2020"},
  {"9p2GeVc_2020e",	                     20200828,  64250, "y2020", "9p2GeVc"}, // 1st run = 21241005			     
//{"7p7GeV_2020",                            20200902, 105440, "y2019", "7p7GeV_2020"},
  {"7p7GeV_2020",	                     20200902, 105440, "y2020", "7p7GeV"}, // 1st run = 21246012			     
//{"26p5GeV_fixedTarget_2020e",              20200907, 221141, "y2019", "26p5GeV_fixedTarget_2020"},
  {"26p5GeV_fixedTarget_2020d",	             20200907, 221141, "y2020", "26p5GeV_fixedTarget"}, // 1st run = 21251020		     
//{"7p7GeV_2020b",                           20200910,  41639, "y2019", "7p7GeV_2020"},
  {"7p7GeV_2020b",	                     20200910,  41639, "y2020", "7p7GeV"}, // 1st run = 21254001			     
//{"26p5GeV_fixedTarget_2020f",              20200912, 102033, "y2019", "26p5GeV_fixedTarget_2020"},//20200912/81816   run = 21256003	26p5GeV_fixedTarget_2020f V1      1.428 
  {"26p5GeV_fixedTarget_2020e",	             20200912, 102033, "y2020", "26p5GeV_fixedTarget"}, // 1st run = 21256006		     
//{"7p7GeV_2021",                            20210131, 193346, "y2019", "7p7GeV_2021"}, 
  {"7p7GeV_2021",	                     20210131, 194041, "y2021", "7p7GeV_2021"}, // 1st run = 22031042			     
//{"FF_7p7GeV_2021",                         20210303, 193715, "y2019", "7p7GeV_2021"               },
//{"7p7GeV_2021b",                           20210304, 213506, "y2019", "7p7GeV_2021"               },
//{"3p85GeV_fixedTarget_2021",               20210501, 165437, "y2019", "3p85GeV_fixedTarget_2021"},
  {"3p85GeV_fixedTarget_2021",	             20210501, 165437, "y2021", "3p85GeV_fixedTarget_2021"}, // 1st run = 22121033	     
//{"44p5GeV_fixedTarget_2021",               20210506,  70146, "y2019", "44p5GeV_fixedTarget_2021"},
  {"44p5GeV_fixedTarget_2021",	             20210506,  70146, "y2021", "44p5GeV_fixedTarget_2021"}, // 1st run = 22126010	     
//{"70GeV_fixedTarget_2021",                 20210507,  31639, "y2019", "70GeV_fixedTarget_2021"},
  {"70GeV_fixedTarget_2021",	             20210507,  31639, "y2021", "70GeV_fixedTarget_2021"}, // 1st run = 22126045	     
//{"100GeV_fixedTarget_2021",                20210508,  41526, "y2019", "100GeV_fixedTarget_2021"},
  {"100GeV_fixedTarget_2021",	             20210508,  41526, "y2021", "100GeV_fixedTarget_2021"}, // 1st run = 22128001	     
//{"OO_200GeV_2021",                         20210510, 134726, "y2019", "OO_200GeV_2021"},
  {"OO_200GeV_2021",	                     20210510, 134726, "y2021", "OO_200GeV_2021"}, // 1st run = 22130029	  	     
//{"ps_OO_200GeV_2021",                      20210513,  83120, "y2019", "ps_OO_200GeV_2021"},
  {"ps_OO_200GeV_2021",	              	     20210513,  83120, "y2021", "ps_OO_200GeV_2021"}, // 1st run = 22133004	  	     
//{"OO_200GeV_2021b",                        20210513,  84422, "y2019", "OO_200GeV_2021"},
  {"OO_200GeV_2021b",	              	     20210513,  84422, "y2021", "OO_200GeV_2021"}, // 1st run = 22133005	  	     
//{"ps_OO_200GeV_2021b",                     20210513, 175228, "y2019", "ps_OO_200GeV_2021"},
  {"ps_OO_200GeV_2021b",	             20210516, 112015, "y2021", "ps_OO_200GeV_2021"}, // 1st run = 22136011	  	     
//{"OO_200GeV_2021c",                        20210513, 182205, "y2019", "OO_200GeV_2021"},
  {"FF_OO_200GeV_2021", 	             20210522,  23642, "y2021", "FF_OO_200GeV_2021"}, // 1st run = 22141038	  	     
//{"ps_OO_200GeV_2021c",                     20210516, 112015, "y2019", "ps_OO_200GeV_2021"},
//{"FF_OO_200GeV_2021",                      20210522,  23642, "y2019", "FF_OO_200GeV_2021"},
//{"17p3GeV_2021",                           20210525, 113236, "y2019", "17p3GeV_2021"},
  {"17p3GeV_2021",	              	     20210525, 113236, "y2021", "17p3GeV_2021"}, // 1st run = 22145017           	     
//{"26p5GeV_fixedTarget_2021",               20210604,  23045, "y2019", "26p5GeV_fixedTarget_2021"},
  {"26p5GeV_fixedTarget_2021",	             20210604,  23045, "y2021", "26p5GeV_fixedTarget_2021"}, // 1st run = 22154036	     
//{"17p3GeV_2021b",                          20210604,  81455, "y2019", "17p3GeV_2021"},
  {"17p3GeV_2021b",	                     20210604,  81455, "y2021", "17p3GeV_2021"}, // 1st run = 22155004			     
//{"3p85GeV_fixedTarget_2021b",              20210608,  43503, "y2019", "3p85GeV_fixedTarget_2021"},//20210608/43159   run = 22159002	3p85GeV_fixedTarget_2021b V1     14.396 
  {"3p85GeV_fixedTarget_2021b",	             20210608,   4951, "y2021", "3p85GeV_fixedTarget_2021"}, // 1st run = 22158032	     
//{"26p5GeV_fixedTarget_2021b",              20210617, 222550, "y2019", "26p5GeV_fixedTarget_2021"},
  {"26p5GeV_fixedTarget_2021b",	             20210617, 224533, "y2021", "26p5GeV_fixedTarget_2021"}, // 1st run = 22168039	     
//{"3p85GeV_fixedTarget_2021c",              20210618,  40935, "y2019", "3p85GeV_fixedTarget_2021"},//20210618/40935   run = 22169001	3p85GeV_fixedTarget_2021c V1     27.581 
  {"3p85GeV_fixedTarget_2021c",	             20210618,  40935, "y2021", "3p85GeV_fixedTarget_2021"}, // 1st run = 22169001	     
//{"26p5GeV_fixedTarget_2021c",              20210627, 152747, "y2019", "26p5GeV_fixedTarget_2021"},
  {"26p5GeV_fixedTarget_2021c",	             20210627, 152747, "y2021", "26p5GeV_fixedTarget_2021"}, // 1st run = 22178019	     
//{"3p85GeV_fixedTarget_2021d",              20210628, 115428, "y2019", "3p85GeV_fixedTarget_2021"},
  {"3p85GeV_fixedTarget_2021d",	             20210628, 115428, "y2021", "3p85GeV_fixedTarget_2021"}, // 1st run = 22179020	     
//{"dAu200_2021",                            20210630,  22849, "y2019", "dAu200GeV_2021"},
//{"dAu200GeV_2021",                         20210630,  22849, "y2019", "dAu200GeV_2021"},
  {"dAu200_2021",	                     20210630,  22849, "y2021", "dAu200_2021"}, // 1st run = 22180043			     
//{"26p5GeV_fixedTarget_2021d",              20210703,  10650, "y2019", "26p5GeV_fixedTarget_2021"},
  {"26p5GeV_fixedTarget_2021d",	             20210703,  10650, "y2021", "26p5GeV_fixedTarget_2021"}, // 1st run = 22183024	     
//{"dAu200GeV_2021b",                        20210703,  53033, "y2019", "dAu200GeV_2021"},
  {"dAu200_2021b",	                     20210703,  53033, "y2021", "dAu200_2021"}, // 1st run = 22184001			     
//{"26p5GeV_fixedTarget_2021e",              20210703, 230657, "y2019", "26p5GeV_fixedTarget_2021"},
  {"26p5GeV_fixedTarget_2021e",	             20210703, 230657, "y2021", "26p5GeV_fixedTarget_2021"}, // 1st run = 22184017	     
//{"dAu200GeV_2021c",                        20210704,  34046, "y2019", "dAu200GeV_2021"},
  {"dAu200_2021c",	                     20210704,  34046, "y2021", "dAu200_2021"}, // 1st run = 22184023			     
 //{"pp500_2022",                             20211215,  81702, "y2019", "pp500_2022"},
  {"pp500_2022",	                     20211215,  81702, "y2021", "pp500_2022"}, // 1st run = 22349011			     
//{"AuAu_2023",                              20230520,  23250, "y2019", "AuAu_2023"},
//{"AuAu200GeV_2023",                        20230520,  23250, "y2019", "AuAu200GeV_2023"},
  {"AuAu_2023",	                             20230520,  23250, "y2021", "AuAu_2023"}, // 1st run = 24139094			     
//{"pp200_lowlumi",                          20240430,  70551, "y2019", "pp200_lowlumi"},
  {"pp200_lowlumi",	                     20240430,  70551, "y2021", "pp200_lowlumi"}, // 1st run = 25121013		     
//{"pp200_LowLuminosity",                    20240430,  74640, "y2019", "pp200_LowLuminosity"},
  {"pp200_LowLuminosity",	             20240430,  74640, "y2021", "pp200_LowLuminosity"}, // 1st run = 25121016		     
//{"pp200_HighLuminosity",                   20240513, 163940, "y2019", "pp200_HighLuminosity"},
  {"pp200_HighLuminosity",	             20240513, 173321, "y2021", "pp200_HighLuminosity"}, // 1st run = 25134037		     
//{"pp200GeV_LowLuminosity_b",               20240514,  11109, "y2019", "pp200GeV_LowLuminosity"},
  {"pp200_LowLuminosity_b",	             20240514,  11109, "y2021", "pp200_LowLuminosity"}, // 1st run = 25134054		     
//{"pp200GeV_HighLuminosity_b",              20240517,  35506, "y2019", "pp200GeV_HighLuminosity"},
  {"pp200_HighLuminosity_b",	             20240517,  35506, "y2021", "pp200_HighLuminosity"}, // 1st run = 25137047		     
//{"pp200_radial",                           20240517, 205711, "y2019", "pp200_radial"},
//{"pp200GeV_radial",                        20240517, 205711, "y2019", "pp200GeV_radial"},
  {"pp200_radial",	                     20240517, 205711, "y2021", "pp200_radial"}, // 1st run = 25138053			     
//{"pp200GeV_HighLuminosity_c",              20240518,  52353, "y2019", "pp200GeV_HighLuminosity"},
  {"pp200_HighLuminosity_c",	             20240518,  52353, "y2021", "pp200_HighLuminosity"}, // 1st run = 25139005		     
//{"pp200GeV_radial_a",                      20240520, 220203, "y2019", "pp200GeV_radial"},
  {"pp200_radial_a",	                     20240520, 220203, "y2021", "pp200_radial"}, // 1st run = 25141034			     
//{"pp200_unpolarized",                      20240529,  22850, "y2019", "pp200_unpolarized"},
  {"pp200_unpolarized",	                     20240529,  22850, "y2021", "pp200_unpolarized"}, // 1st run = 25149057		     
  {"pp200_HighLuminosity_d",	             20240607,  71454, "y2021", "pp200_HighLuminosity"}, // 1st run = 25159009		     
//{"pp200GeV_radial_b",                      20240529, 231051, "y2019", "pp200GeV_radial"},
  {"pp200_radial_b",	                     20240607, 124232, "y2021", "pp200_radial"}, // 1st run = 25159020		 	     
//{"pp200GeV_HighLuminosity_d",              20240607,  71454, "y2019", "pp200GeV_HighLuminosity"},
//{"pp200GeV_radial_c",                      20240607, 124232, "y2019", "pp200GeV_radial"},
//{"pp200GeV_unpolarized_b",                 20240613,  42200, "y2019", "pp200GeV_unpolarized"},
  {"pp200_unpolarized_b",	             20240613,  42200, "y2021", "pp200_unpolarized"}, // 1st run = 25165001	 	     
//{"pp200GeV_radial_d",                      20240616, 160307, "y2019", "pp200GeV_radial"},
  {"pp200_radial_d",	              	     20240616, 160307, "y2021", "pp200_radial"}, // 1st run = 25168022		 	     
//{"pp200GeV_unpolarized_c",                 20240801, 175519, "y2019", "pp200GeV_unpolarized"},
  {"pp200_unpolarized_c",	             20240801, 175519, "y2021", "pp200_unpolarized"}, // 1st run = 25214020	 	     
//{"pp200GeV_radial_e",                      20240802,  70216, "y2019", "pp200GeV_radial"},
  {"pp200_radial_e",	              	     20240802,  70632, "y2021", "pp200_radial"}, // 1st run = 25215009          	     
//{"AuAu_2024",                              20241006, 124742, "y2019", "AuAu_2024"},
  {"AuAu_2024",	                             20241006, 124742, "y2021", "AuAu_2024"}, // 1st run = 25280025                         

  {"Cosmic_2019",  			     20190109, 211356, "y2019", "Cosmic_2019/ZF"}, 
  {"Cosmic_2019/ZF",  			     20190109, 211356, "y2019", "Cosmic_2019/ZF"}, 
  {"Cosmic_2019/FF",                         20190118, 210113, "y2019", "Cosmic_2019/FF"}, 
  {"Cosmic_2019/RF",  			     20190204, 205949, "y2019", "Cosmic_2019/RF"}, 
  {"Cosmic_2019_ZF",  			     20190109, 211356, "y2019", "Cosmic_2019_ZF"}, 
  {"Cosmic_2019_FF",                         20190118, 210113, "y2019", "Cosmic_2019_FF"}, 
  {"Cosmic_2019_RF",  			     20190204, 205949, "y2019", "Cosmic_2019_RF"}, 

  {"Cosmic_2020",  			     20191125, 202022, "y2020", "Cosmic_2020/ZF"}, 
  {"Cosmic_2020/ZF",  			     20191125, 202022, "y2020", "Cosmic_2020/ZF"}, 
  {"Cosmic_2020/RF",  			     20191128,  51555, "y2020", "Cosmic_2020/RF"}, 
  {"Cosmic_2020_ZF",  			     20191125, 202022, "y2020", "Cosmic_2020_ZF"}, 
  {"Cosmic_2020_RF",  			     20191128,  51555, "y2020", "Cosmic_2020_RF"}, 

  {"Cosmic_2021",  			     20210129,  41915, "y2021", "Cosmic_2021/ZF"}, 
  {"Cosmic_2021/ZF",  			     20210129,  41915, "y2021", "Cosmic_2021/ZF"}, 
  {"Cosmic_2021/RF",  			     20210129, 210413, "y2021", "Cosmic_2021/RF"}, 
  {"Cosmic_2021/FF",  			     20210303, 193715, "y2021", "Cosmic_2021/FF"}, 
  {"Cosmic_2021_ZF",  			     20210129,  41915, "y2021", "Cosmic_2021_ZF"}, 
  {"Cosmic_2021_RF",  			     20210129, 210413, "y2021", "Cosmic_2021_RF"}, 
  {"Cosmic_2021_FF",  			     20210303, 193715, "y2021", "Cosmic_2021_FF"}, 

  {"Cosmic_2022",  			     20211110, 215909, "y2022", "Cosmic_2022/ZF"}, 
  {"Cosmic_2022/ZF",  			     20211110, 215909, "y2022", "Cosmic_2022/ZF"}, 
  {"Cosmic_2022/RF",  			     20211111,  51637, "y2022", "Cosmic_2022/RF"}, 
  {"Cosmic_2022/FF",  			     20211115, 193307, "y2022", "Cosmic_2022/FF"}, 
  {"Cosmic_2022_ZF",  			     20211110, 215909, "y2022", "Cosmic_2022_ZF"}, 
  {"Cosmic_2022_RF",  			     20211111,  51637, "y2022", "Cosmic_2022_RF"}, 
  {"Cosmic_2022_FF",  			     20211115, 193307, "y2022", "Cosmic_2022_FF"}, 

  {"Cosmic_2023",  			     20230507,  55732, "y2023", "Cosmic_2023/FF"}, 
  {"Cosmic_2023/FF",  			     20230507,  55732, "y2023", "Cosmic_2023/FF"}, 
  {"Cosmic_2023/ZF",  			     20230508, 195057, "y2023", "Cosmic_2023/ZF"}, 
  {"Cosmic_2023/RF",  			     20230509, 181952, "y2023", "Cosmic_2023/RF"}, 
  {"Cosmic_2023_FF",  			     20230507,  55732, "y2023", "Cosmic_2023_FF"}, 
  {"Cosmic_2023_ZF",  			     20230508, 195057, "y2023", "Cosmic_2023_ZF"}, 
  {"Cosmic_2023_RF",  			     20230509, 181952, "y2023", "Cosmic_2023_RF"}, 

  {"Cosmic_2024",  			     20240403,  20814, "y2024", "Cosmic_2024/ZF"}, 
  {"Cosmic_2024/ZF",  			     20240403,  20814, "y2024", "Cosmic_2024/ZF"}, 
  {"Cosmic_2024/FF",  			     20240407, 125531, "y2024", "Cosmic_2024/FF"}, 
  {"Cosmic_2024/RF",  			     20240416, 161358, "y2024", "Cosmic_2024/RF"}, 
  {"Cosmic_2024_ZF",  			     20240403,  20814, "y2024", "Cosmic_2024_ZF"}, 
  {"Cosmic_2024_FF",  			     20240407, 125531, "y2024", "Cosmic_2024_FF"}, 
  {"Cosmic_2024_RF",  			     20240416, 161358, "y2024", "Cosmic_2024_RF"}, 
  {"Cosmic_2024_RFA", 			     20240416, 161358, "y2024", "Cosmic_2024/RFA"}, 
  {"Cosmic_2024_RFB", 			     20240521,  84436, "y2024", "Cosmic_2024/RFB"}, 
  {"athena",                                 20301220,      1,      "",         "athena"}, // 
  {"epic",                                   20301221,      1,      "",           "epic"}, // 
  {0,                                               0,      0,       0,                0}
};
#endif /*  __GeometryDbAliases__ */
