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
  {"r2004",       20031220,     0, "y2004c",   "xgeometry"},                   //       {"y2004c",      20031125,     0}
  
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
  {"y2019a",      20181215,     1, "y2019",    "y2019a first production release geometry, AgML,xgeometry"},   
  {"y2019b",      20181215,     2, "y2019",    "y2019a production geometry (FXT @ 200.7cm), AgML,xgeometry"},   
  {"r2019",       20181220,     0, "y2019",    "y2019, iTPC, Jim Thomas 05/31/16, no HFT,xgeometry"}, // 

  {"y2020",       20191115,     0, "y2019",    "y2020 development geometry, AgML,xgeometry"},   
  {"y2020a",      20191115,     1, "y2019",    "y2020 fast-offline geometry, AgML,xgeometry"},   
  {"y2020b",      20191115,     2, "y2019",    "y2020 production geometry (FXT @ 200.7 cm), AgML,xgeometry"},   
  {"r2020",       20191120,180000, "y2019",    "y2019, iTPC, Jim Thomas 05/31/16, no HFT,xgeometry"}, // 
  {"r2020a",      20191120,180001, "y2019",    "y2019, iTPC, Jim Thomas 05/31/16, no HFT,xgeometry"}, // 
 
  {"y2021",       20201215,     0, "y2019",    "y2019 development geometry, AgML,xgeometry"},   
  {"y2021a",      20201215,     1, "y2019",    "y2019a first production release geometry, AgML,xgeometry"},   
  {"r2021",       20201220,     0, "y2019",    "y2019, iTPC, Jim Thomas 05/31/216, no HFT,xgeometry"}, // 
  {"r2021a",      20201220,     1, "y2019",    "y2019, iTPC, Jim Thomas 05/31/16, no HFT,xgeometry"}, // 
//{"dev2022",     20211210,     1, "dev2022",  "development geometry for 2022+ forward program,AgML,xgeometry"},
  {"y2022",       20211015,     0, "y2019",    "y2019 development geometry, AgML,xgeometry"},   
  {"r2022",       20211025,     0, "y2019",    "y2019, iTPC, Jim Thomas 05/31/16, no HFT,xgeometry"}, // 
  {"y2022a",      20211015,     1, "y2019",    "y2019 development geometry, AgML,xgeometry"},   
  {"r2022a",      20211025,     1, "y2019",    "y2019, iTPC, Jim Thomas 05/31/16, no HFT,xgeometry"}, // 
  {"athena",      20301220,     1, "",         "athena"}, // 
  {"epic",        20301221,     1, "",         "epic"}, // 
  {"y2023",       20221215,     0, "y2019",    "y2019 development geometry, AgML,xgeometry"},   
  {"r2023",       20221225,     0, "y2019",    "y2019, iTPC, Jim Thomas 05/31/16, no HFT,xgeometry"}, // 
  {"y2023a",      20221215,     1, "y2019",    "y2019 development geometry, AgML,xgeometry"},   
  {"r2023a",      20221225,     1, "y2019",    "y2019, iTPC, Jim Thomas 05/31/16, no HFT,xgeometry"}, // 
  // Production runs
  {"19GeV_2019",                             20190225, 202320, "y2019", "19GeV_2019"                },
  {"14p5GeV_2019",                           20190404,  94405, "y2019", "14p5GeV_2019"              },
  {"7.3GeV_fixedTarget_2019",                20190417, 133401, "y2019", "7.3GeV_fixedTarget_2019"   },
  {"14p5GeV_2019b",                          20190417, 141246, "y2019", "14p5GeV_2019"              },
  {"7.3GeV_fixedTarget_2019b",               20190423, 155418, "y2019", "7.3GeV_fixedTarget_2019"   },
  {"14p5GeV_2019b",                          20190423, 181158, "y2019", "14p5GeV_2019"              },
  {"7p7GeV_2019",                            20190603, 223655, "y2019", "7p7GeV_2019"               },
  {"3p85GeV_fixedTarget_2019",               20190607, 174702, "y2019", "3p85GeV_fixedTarget_2019"  },
  {"7p7GeV_2019b",                           20190607, 202244, "y2019", "7p7GeV_2019"               },
  {"3p85GeV_fixedTarget_2019b",              20190609, 124528, "y2019", "3p85GeV_fixedTarget_2019"  },
  {"7p7GeV_2019c",                           20190610,  24109, "y2019", "7p7GeV_2019"               },
  {"7.3GeV_fixedTarget_2019c",               20190618, 143658, "y2019", "7.3GeV_fixedTarget_2019"   },
  {"7p7GeV_2019d",                           20190619,  25126, "y2019", "7p7GeV_2019"               },
  {"9p2GeV_2019",                            20190628,  81931, "y2019", "9p2GeV_2019"               },
  {"4p59GeV_fixedTarget_2019",               20190629,  32834, "y2019", "4p59GeV_fixedTarget_2019"  },
  {"9p2GeV_2019b",                           20190702, 144151, "y2019", "9p2GeV_2019"               },
  {"31GeV_fixedTarget_2019",                 20190709,  32312, "y2019", "31GeV_fixedTarget_2019"    },
  {"AuAu200GeV_2019",                        20190710, 110157, "y2019", "AuAu200GeV_2019"           },
  {"9p2GeV_2019",                            20190715,  85141, "y2019", "9p2GeV_2019"               },
  {"11p5GeV_2020",                           20191208,  91308, "y2019", "11p5GeV_2020"              },
  {"5p75GeV_fixedTarget_2020",               20191221, 154021, "y2019", "5p75GeV_fixedTarget_2020"  },
  {"11p5GeV_2020b",                          20191221, 190032, "y2019", "11p5GeV_2020"              },
  {"31p2GeV_fixedTarget_2020",               20200128, 182912, "y2019", "31p2GeV_fixedTarget_2020"  },
  {"9p8GeV_fixedTarget_2020",                20200130,   5840, "y2019", "9p8GeV_fixedTarget_2020"   },
  {"9p2GeV_2020",                            20200131,  12112, "y2019", "9p2GeV_2020"               },
  {"9p8GeV_fixedTarget_2020",                20200131,  50328, "y2019", "9p8GeV_fixedTarget_2020"   },
  {"19p5GeV_fixedTarget_2020",               20200201, 191904, "y2019", "19p5GeV_fixedTarget_2020"  },
  {"13p5GeV_fixedTarget_2020",               20200202, 160409, "y2019", "13p5GeV_fixedTarget_2020"  },
  {"9p2GeV_2020b",                           20200203, 202534, "y2019", "9p2GeV_2020"               },
  {"7p3GeV_fixedTarget_2020",                20200204,  53518, "y2019", "7p3GeV_fixedTarget_2020"   },
  {"9p2GeV_2020c",                           20200205, 144626, "y2019", "9p2GeV_2020"               },
  {"11p5GeV_2020",                           20200210, 220428, "y2019", "11p5GeV_2020"              },
  {"5p75GeV_fixedTarget_2020",               20200213, 152339, "y2019", "5p75GeV_fixedTarget_2020"  },
  {"11p5GeV_2020b",                          20200214, 143742, "y2019", "11p5GeV_2020"              },
  {"9p2GeVb_2020",                           20200224, 230740, "y2019", "9p2GeVb_2020"              },
  {"9p2GeVc_2020",                           20200617, 233208, "y2019", "9p2GeVc_2020"              },
  {"26p5GeV_fixedTarget_2020",               20200730,  15354, "y2019", "26p5GeV_fixedTarget_2020"  },
  {"9p2GeVc_2020b",                          20200730,  42836, "y2019", "9p2GeVc_2020"              },
  {"26p5GeV_fixedTarget_2020b",              20200813, 213251, "y2019", "26p5GeV_fixedTarget_2020"  },
  {"9p2GeVc_2020c",                          20200814,  54357, "y2019", "9p2GeVc_2020"              },
  {"26p5GeV_fixedTarget_2020c",              20200819, 192253, "y2019", "26p5GeV_fixedTarget_2020"  },
  {"9p2GeVc_2020d",                          20200820,  55402, "y2019", "9p2GeVc_2020"              },
  {"26p5GeV_fixedTarget_2020d",              20200827, 143507, "y2019", "26p5GeV_fixedTarget_2020"  },
  {"9p2GeVc_2020e",                          20200828,  64250, "y2019", "9p2GeVc_2020"              },
  {"7p7GeV_2020",                            20200902, 105440, "y2019", "7p7GeV_2020"               },
  {"26p5GeV_fixedTarget_2020e",              20200907, 221141, "y2019", "26p5GeV_fixedTarget_2020"  },
  {"7p7GeV_2020b",                           20200910,  41639, "y2019", "7p7GeV_2020"               },
  {"26p5GeV_fixedTarget_2020f",              20200912, 102033, "y2019", "26p5GeV_fixedTarget_2020"  },
  {"7p7GeV_2021d",                           20210131, 193346, "y2019", "7p7GeV_2021"               },
  {"3p85GeV_fixedTarget_2021",               20210501, 165437, "y2019", "3p85GeV_fixedTarget_2021"  },
  {"3p85GeV_fixedTarget_2021a",              20210501, 165437, "y2019", "3p85GeV_fixedTarget_2021"  },
  {"44p5GeV_fixedTarget_2021",               20210506,  70146, "y2019", "44p5GeV_fixedTarget_2021"  },
  {"70GeV_fixedTarget_2021",                 20210507,  31639, "y2019", "70GeV_fixedTarget_2021"    },
  {"100GeV_fixedTarget_2021",                20210508,  41526, "y2019", "100GeV_fixedTarget_2021"   },
  {"OO_200GeV_2021",                         20210510, 134726, "y2019", "OO_200GeV_2021"            },
  {"ps_OO_200GeV_2021",                      20210513,  83120, "y2019", "ps_OO_200GeV_2021"         },
  {"OO_200GeV_2021b",                        20210513,  84422, "y2019", "OO_200GeV_2021"            },
  {"ps_OO_200GeV_2021b",                     20210513, 175228, "y2019", "ps_OO_200GeV_2021"         },
  {"OO_200GeV_2021c",                        20210513, 182205, "y2019", "OO_200GeV_2021"            },
  {"OO_fcsTiming",                           20210514, 144728, "y2019", "OO_fcsTiming"              },
  {"OO_200GeV_2021d",                        20210514, 150240, "y2019", "OO_200GeV_2021"            },
  {"ps_OO_200GeV_2021",                      20210516, 112015, "y2019", "ps_OO_200GeV_2021"         },
  {"FF_OO_200GeV_2021",                      20210522,  23642, "y2019", "FF_OO_200GeV_2021"         },
  {"17p3GeV_2021",                           20210525, 113236, "y2019", "17p3GeV_2021"              },
  {"26p5GeV_fixedTarget_2021",               20210604,  23045, "y2019", "26p5GeV_fixedTarget_2021"  },
  {"17p3GeV_2021",                           20210604,  81455, "y2019", "17p3GeV_2021"              },
  {"3p85GeV_fixedTarget_2021b",              20210608,   4951, "y2019", "3p85GeV_fixedTarget_2021"  },
  {"26p5GeV_fixedTarget_2021b",              20210617, 222550, "y2019", "26p5GeV_fixedTarget_2021"  },
  {"3p85GeV_fixedTarget_2021c",              20210618,  40935, "y2019", "3p85GeV_fixedTarget_2021"  },
  {"26p5GeV_fixedTarget_2021c",              20210627, 152747, "y2019", "26p5GeV_fixedTarget_2021"  },
  {"3p85GeV_fixedTarget_2021d",              20210628, 115428, "y2019", "3p85GeV_fixedTarget_2021"  },
  {"dAu200_2021",                            20210630,  22849, "y2019", "dAu200_2021"               },
  {"26p5GeV_fixedTarget_2021e",              20210703,  10650, "y2019", "26p5GeV_fixedTarget_2021"  },
  {"dAu200_2021",                            20210703,  53033, "y2019", "dAu200_2021"               },
  {"26p5GeV_fixedTarget_2021f",              20210703, 230657, "y2019", "26p5GeV_fixedTarget_2021"  },
  {"dAu200_2021",                            20210704,  34046, "y2019", "dAu200_2021"               },
  {"pp500_2022",                             20211215,  81702, "y2019", "pp500_2022"                },
  {"zeroFieldAligment_2022",                 20220207, 204123, "y2019", "zeroFieldAligment_2022"    },
  {"pp500_2022",                             20220208,  33747, "y2019", "pp500_2022"                },
  {"zeroFieldAligment_2022",                 20220209, 225511, "y2019", "zeroFieldAligment_2022"    },
  {"pp500_2022b",                            20220210, 112619, "y2019", "pp500_2022"                },
  {"zeroFieldAligment_2022",                 20220304, 185313, "y2019", "zeroFieldAligment_2022"    },
  {"pp500_2022c",                            20220305,  42126, "y2019", "pp500_2022"                },
  {"zeroFieldAligment_2022",                 20220313,  51859, "y2019", "zeroFieldAligment_2022"    },
  {"pp500_2022d",                            20220313, 141508, "y2019", "pp500_2022"                },
  {"AuAu_2023",                              20230520,  23250, "y2019", "AuAu_2023"                 },
  {0,                    0,     0,        0,    0}
};
#endif /*  __GeometryDbAliases__ */
