#ifndef StarDetectorMap_h
#define StarDetectorMap_h
/* Instrument block emc => ecal
"bbc","BBCM","BPOL","g2t_ctf_hit","g2t_bbc_hit",  // Bbc POLystyren active scintillator layer
"ctb","BTOF","BXSA","g2t_ctf_hit","g2t_ctb_hit",  // the active trigger scintillator SLAB for ctb
"eem","ECAL","ELGR","g2t_emc_hit","g2t_eem_hit",
"eem","ECAL","EPCT","g2t_emc_hit","g2t_eem_hit",  // the active scintillator (polystyren) layer
"eem","ECAL","ESCI","g2t_emc_hit","g2t_eem_hit",  // the active scintillator (polystyren) layer
"emc","CALB","CSUP","g2t_emc_hit","g2t_emc_hit",  // a super layer with few layers inside
"epd","EPDM","EPAD","g2t_epd_hit","g2t_epd_hit",  // scintillator paddle
"esm","ECAL","EHMS","g2t_emc_hit","g2t_esm_hit",  // the triangular SMD strips
"esm","ECAL","EXSE","g2t_emc_hit","g2t_esm_hit",
"etr","EIDD","TABD","g2t_etr_hit","g2t_etr_hit",
"fgt","FGTD","FGZC","g2t_fgt_hit","g2t_fgt_hit",  // active volume divisions of FGSC
"fgt","FGTD","FGZD","g2t_fgt_hit","g2t_fgt_hit",
"fgt","FGTD","FZCB","g2t_fgt_hit","g2t_fgt_hit",
"fpd","FPDM","FLGR","g2t_emc_hit","g2t_fpd_hit",  // Lead Glass detector
"fpd","FPDM","FLXF","g2t_emc_hit","g2t_fpd_hit",  // Lead Glass detector
"fpd","FPDM","FPSC","g2t_emc_hit","g2t_fpd_hit",
"fsc","FSCE","FSCT","g2t_emc_hit","g2t_fsc_hit",  // a sensitive Tungsten+Sci+Epoxy tower
"fst","FSTD","FDSW","g2t_fst_hit","g2t_fst_hit",  // the Silicon Wafer (all active)
"ftp","FTPC","FSEC","g2t_ftp_hit","g2t_ftp_hit",  // a sensitive gas sector
"fts","FTSD","FTSA","g2t_fts_hit","g2t_fts_hit",  // Active volume for each FTS disk
"gem","GEMB","GMDI","g2t_gem_hit","g2t_gem_hit",  // the sensitive volume of the GEM strip detector, layer 1
"hca","HCAL","BBCB","g2t_emc_hit","g2t_hca_hit",  // Beam Counter front, Back scint paddle 
"hca","HCAL","BBCF","g2t_emc_hit","g2t_hca_hit",  // Beam Counter front, Front scint paddle 
"hca","HCAL","FPSC","g2t_emc_hit","g2t_hca_hit",  // a piece of scintillator in FMS Preshower
"hca","HCAL","HCEL","g2t_emc_hit","g2t_hca_hit",  // 3*3 cell in tower, HCES has 16*16 fibers
"hca","HCAL","HCES","g2t_emc_hit","g2t_hca_hit",  // 3*3 cell in tower, HCES has 16*16 fiber
"hca","HCAL","HSTP","g2t_emc_hit","g2t_hca_hit",  // single strips in pre shower, preshower 
"hca","HCAL","LEDG","g2t_emc_hit","g2t_hca_hit",  // Lead glass
"hpd","HPDT","YPLA","g2t_hpd_hit","g2t_hpd_hit",  // the active layer of the pixel
"igt","IGTD","IGAL","g2t_igt_hit","g2t_igt_hit",
"ist","ISTB","IBSS","g2t_ist_hit","g2t_ist_hit",  // the Silicon Sensor
"mtd","MUTD","MIGG","g2t_mtd_hit","g2t_mtd_hit",  // a single gas gap
"mtd","MUTD","MTTF","g2t_mtd_hit","g2t_mtd_hit",  // the MTD11 5-tray group mother
"mtd","MUTD","MTTT","g2t_mtd_hit","g2t_mtd_hit",  // the MTD11 3-tray group mother
"mwc","TPCE","TMSE","g2t_mwc_hit","g2t_mwc_hit",
"pix","PIXL","PLAC","g2t_pix_hit","g2t_pix_hit",
"pmd","PHMD","PDGS","g2t_pmd_hit","g2t_pmd_hit",  // The inner cell in the PMD module
"rch","RICH","FREO","g2t_rch_hit","g2t_rch_hit",
"rch","RICH","QUAR","g2t_rch_hit","g2t_rch_hit",
"rch","RICH","RCSI","g2t_rch_hit","g2t_rch_hit",
"rch","RICH","RGAP","g2t_rch_hit","g2t_rch_hit",
"smd","CALB","CSDA","g2t_emc_hit","g2t_smd_hit",  // Al block with sensitive gas volume
"ssd","SISD","SFSD","g2t_ssd_hit","g2t_ssd_hit",
"svt","SVTT","SFSD","g2t_svt_hit","g2t_ssd_hit",
"svt","SVTT","SVTD","g2t_svt_hit","g2t_svt_hit",
"tfr","BTOF","BRSG","g2t_ctf_hit","g2t_tfr_hit",  // the sensitive gas layer in the TOFr module
"tof","BTOF","BCSB","g2t_ctf_hit","g2t_tof_hit",  // the active trigger scintillator SLAB for tof
"tpc","TPCE","TPAD',"g2t_tpc_hit","g2t_tpc_hit",
"vpd","VPDD","VRAD","g2t_vpd_hit","g2t_vpd_hit",  // light-producing layer (scintillator or quartz)
"zdc","ZCAL","QSCI","g2t_emc_hit","g2t_zdc_hit",  // sensitive Fiber layer

StVMCMaker:INFO  - 1    HALL[1]/CAVE[1]/TpcRefSys[1]/TPCE[1]/TPGV[2]/TPSS[12]/TPAD[76]
StVMCMaker:INFO  - 2    HALL[1]/CAVE[1]/TpcRefSys[1]/BTOF[1]/BTOH[2]/BSEC[60]/BTRA[1]/BXTR[1]/BRTC[1]/BGMT[1]/BRMD[32]/BRDT[1]/BRSG[6]
StVMCMaker:INFO  - 3    HALL[1]/CAVE[1]/TpcRefSys[1]/BTOF[1]/BTOH[2]/BSEC[48]/BTRA[1]/BXTR[1]/BRTC[1]/BGMT[1]/GMTS[2]/GSBE[1]/GEMG[1]
StVMCMaker:INFO  - 4    HALL[1]/CAVE[1]/ZCAL[2]/QCAL[1]/QDIV[260]/QSCI[1]
StVMCMaker:INFO  - 5    HALL[1]/CAVE[1]/VPDD[2]/VRNG[1]/VDET[19]/VDTI[1]/VCNV[1]/VRAD[1]
StVMCMaker:INFO  - 6    HALL[1]/CAVE[1]/CALB[1]/CHLV[2]/CPHI[60]/CSUP[2]/CSCI[19]
StVMCMaker:INFO  - 7    HALL[1]/CAVE[1]/CALB[1]/CHLV[2]/CPHI[60]/CSUP[2]/CSMD[1]/CSDA[4]/CSME[30]/CSHI[2]
StVMCMaker:INFO  - 8    HALL[1]/CAVE[1]/ECAL[1]/EAGA[2]/EMSS[1]/ECVO[2]/EMOD[6]/ESEC[3]/EMGT[17]/EPER[5]/ETAR[12]/ESCI[1]
StVMCMaker:INFO  - 9    HALL[1]/CAVE[1]/ECAL[1]/EAGA[2]/EMSS[1]/ESHM[1]/ESPL[3]/EXSG[6]/EHMS[288]
StVMCMaker:INFO  - 10   HALL[1]/CAVE[1]/BBCM[2]/BBCA[1]/THXM[6]/SHXT[3]/BPOL[1]
StVMCMaker:INFO  - 11   HALL[1]/CAVE[1]/MUTD[1]/MTTG[28]/MTRA[5]/MIGS[1]/MIGG[5]
StVMCMaker:INFO  - 12   HALL[1]/CAVE[1]/WMOD[2]/WTOW[748]/WSCI[1]
StVMCMaker:INFO  - 13   HALL[1]/CAVE[1]/HMOD[2]/HTOW[260]/HSCI[1]
StVMCMaker:INFO  - 14   HALL[1]/CAVE[1]/FSTM[1]/FSTD[6]/FSTW[12]/FTUS[3]
StVMCMaker:INFO  - 15   HALL[1]/CAVE[1]/STGM[1]/STFM[16]/STMG[2]/STGP[1]
StVMCMaker:INFO  - 16   HALL[1]/CAVE[1]/STGM[1]/STFM[16]/STMG[2]/STGL[1]
StVMCMaker:INFO  - 17   HALL[1]/CAVE[1]/STGM[1]/STFM[16]/STMG[2]/STGS[1]
StVMCMaker:INFO  - 18   HALL[1]/CAVE[1]/ETOF[324]/EGAS[1]/ECOU[3]/EGAP[12]/ECEL[32]
StVMCMaker:INFO  - 19   HALL[1]/CAVE[1]/EPDM[2]/EPSS[12]/EPDT[62]
y2024z
StVMCMaker:INFO  - 1    HALL[1]/CAVE[1]/TpcRefSys[1]/TPCE[1]/TPGV[2]/TPSS[12]/TPAD[76]
StVMCMaker:INFO  - 2    HALL[1]/CAVE[1]/TpcRefSys[1]/BTOF[1]/BTOH[2]/BSEC[60]/BTRA[1]/BXTR[1]/BRTC[1]/BGMT[1]/BRMD[32]/BRDT[1]/BRSG[6]
StVMCMaker:INFO  - 3    HALL[1]/CAVE[1]/TpcRefSys[1]/BTOF[1]/BTOH[2]/BSEC[48]/BTRA[1]/BXTR[1]/BRTC[1]/BGMT[1]/GMTS[2]/GSBE[1]/GEMG[1]
StVMCMaker:INFO  - 4    HALL[1]/CAVE[1]/ZCAL[2]/QCAL[1]/QDIV[260]/QSCI[1]
StVMCMaker:INFO  - 5    HALL[1]/CAVE[1]/VPDD[2]/VRNG[1]/VDET[19]/VDTI[1]/VCNV[1]/VRAD[1]
StVMCMaker:INFO  - 6    HALL[1]/CAVE[1]/CALB[1]/CHLV[2]/CPHI[60]/CSUP[2]/CSCI[19]
StVMCMaker:INFO  - 7    HALL[1]/CAVE[1]/CALB[1]/CHLV[2]/CPHI[60]/CSUP[2]/CSMD[1]/CSDA[4]/CSME[30]/CSHI[2]
StVMCMaker:INFO  - 8    HALL[1]/CAVE[1]/ECAL[1]/EAGA[2]/EMSS[1]/ECVO[2]/EMOD[6]/ESEC[3]/EMGT[17]/EPER[5]/ETAR[12]/ESCI[1]
StVMCMaker:INFO  - 9    HALL[1]/CAVE[1]/ECAL[1]/EAGA[2]/EMSS[1]/ESHM[1]/ESPL[3]/EXSG[6]/EHMS[288]
StVMCMaker:INFO  - 10   HALL[1]/CAVE[1]/BBCM[2]/BBCA[1]/THXM[6]/SHXT[3]/BPOL[1]
StVMCMaker:INFO  - 11   HALL[1]/CAVE[1]/MUTD[1]/MTTG[28]/MTRA[5]/MIGS[1]/MIGG[5]
StVMCMaker:INFO  - 12   HALL[1]/CAVE[1]/WMOD[2]/WTOW[748]/WSCI[1]
StVMCMaker:INFO  - 13   HALL[1]/CAVE[1]/HMOD[2]/HTOW[260]/HSCI[1]
StVMCMaker:INFO  - 14   HALL[1]/CAVE[1]/FSTM[1]/FSTD[6]/FSTW[12]/FTUS[3]
StVMCMaker:INFO  - 15   HALL[1]/CAVE[1]/STGM[1]/STFM[16]/STMG[2]/STGP[1]
StVMCMaker:INFO  - 16   HALL[1]/CAVE[1]/STGM[1]/STFM[16]/STMG[2]/STGL[1]
StVMCMaker:INFO  - 17   HALL[1]/CAVE[1]/STGM[1]/STFM[16]/STMG[2]/STGS[1]
StVMCMaker:INFO  - 18   HALL[1]/CAVE[1]/ETOF[324]/EGAS[1]/ECOU[3]/EGAP[12]/ECEL[32]
StVMCMaker:INFO  - 19   HALL[1]/CAVE[1]/EPDM[2]/EPSS[12]/EPDT[62]
             
 */
#include "StEnumerations.h"
struct StarDetectorMap_t {
  const StDetectorId Id;
  const Char_t*      Csys;
  const Char_t*      set; // empty if use 'simple' numbv => volume_id translation
  const Char_t*      det;
  const Char_t*      G2T_type;
  const Char_t*      G2T_name;
  const Char_t*      Collection; // StEvent hit collection name 
};
static const StarDetectorMap_t Detectors[] = {// missing : hpd, pre
  {kUnknownId            ,"bbc","BBCM","BPOL","g2t_ctf_hit","g2t_bbc_hit","StBbcTriggerDetector"},  // 2*6*3 Bbc POLystyren active scintillator layer
  {kCtbId     	         ,"ctb","BTOF","BXSA","g2t_ctf_hit","g2t_ctb_hit","StCtbTriggerDetector"},  // the active trigger scintillator SLAB for ctb
  {kUnknownId            ,"eem","ECAL","ELGR","g2t_emc_hit","g2t_eem_hit",""},                      // not found
  {kUnknownId            ,"eem","ECAL","EPCT","g2t_emc_hit","g2t_eem_hit",""},                      // the active scintillator (polystyren) layer
  {kEndcapEmcTowerId     ,"eem","ECAL","ESCI","g2t_emc_hit","g2t_eem_hit",""},                      // 2*2*6*3*17*5*12 the active scintillator (polystyren) layer
//{kBarrelEmcTowerId     ,"emc","CALB","CSUP","g2t_emc_hit","g2t_emc_hit","StEmcClusterCollection"},// is a super layer with few layers inside 
  {kBarrelEmcTowerId     ,"emc","CALB","CSCI","g2t_emc_hit","g2t_emc_hit","StEmcClusterCollection"},// 2*60*19 is a super layer with few layers inside 
  {kUnknownId            ,"epd","EPDM","EPAD","g2t_ctf_hit","g2t_epd_hit",""},                      // scintillator paddle
  {kEndcapEmcPreShowerId ,"esm","ECAL","EHMS","g2t_emc_hit","g2t_esm_hit",""},                      // 2*3*6*2888 the triangular SMD strips
  {kEndcapEmcPreShowerId ,"esm","ECAL","EXSE","g2t_emc_hit","g2t_esm_hit",""},                      // SMD section
  {kEpdId                ,"epd","EPDM","EPDT","g2t_ctf_hit","g2t_epd_hit","StEpdCollection"},       // 2*12*62
  {kETofId               ,"eto","ETOF","ECEL","g2t_ctf_hit","g2t_eto_hit","StETofCollection"},      // 324*3*12*32                
  {kUnknownId            ,"etr","EIDD","TABD","g2t_etr_hit","g2t_etr_hit",""},                      // 
  {kFgtId                ,"fgt","FGTD","FGZC","g2t_fgt_hit","g2t_fgt_hit",""},                      // active volume divisions of FGSC
  {kFgtId                ,"fgt","FGTD","FGZD","g2t_fgt_hit","g2t_fgt_hit",""},                      //
  {kFgtId                ,"fgt","FGTD","FZCB","g2t_fgt_hit","g2t_fgt_hit",""},                      //
  {kUnknownId            ,"fpd","FPDM","FLGR","g2t_emc_hit","g2t_fpd_hit",""},                      // Lead Glass detector			   
  {kUnknownId            ,"fpd","FPDM","FLXF","g2t_emc_hit","g2t_fpd_hit",""},  		    // Lead Glass detector			  
  {kUnknownId            ,"fpd","FPDM","FPSC","g2t_emc_hit","g2t_fpd_hit",""}, 			    // a piece of scintillator in FMS Preshower
  {kUnknownId            ,"fsc","FSCE","FSCT","g2t_emc_hit","g2t_fsc_hit",""},                      // a sensitive Tungsten+Sci+Epoxy tower
  {kUnknownId            ,"fst","FSTD","FDSW","g2t_fst_hit","g2t_fst_hit",""},                      // the Silicon Wafer (all active)
  {kFtpcWestId           ,"ftp","FTPC","FSEC","g2t_ftp_hit","g2t_ftp_hit","StFtpcHitCollection"},   // a sensitive gas sector
  {kUnknownId            ,"fts","FTSD","FTSA","g2t_fts_hit","g2t_fts_hit",""},                      // Active volume for each FTS disk
  {kFtsId                ,"fts","FSTH","FTUS","g2t_fts_hit","g2t_fts_hit",""},                      // 6*12*3 Tube segment for FST silicon
  {kUnknownId            ,"gem","GEMB","GMDI","g2t_gem_hit","g2t_gem_hit",""},                      // the sensitive volume of the GEM strip detector, layer 1
  {kGmtId       	 ,"gmt","BTOF","GEMG","g2t_ctf_hit","g2t_gmt_hit",""},                      // 2*48*2 the sensitive gas layer in the GMT  module
  {kUnknownId            ,"hca","HCAL","BBCB","g2t_emc_hit","g2t_hca_hit",""},                      // Beam Counter front, Back scint paddle 
  {kUnknownId            ,"hca","HCAL","BBCF","g2t_emc_hit","g2t_hca_hit",""},                      // Beam Counter front, Front scint paddle 
  {kUnknownId            ,"hca","HCAL","FPSC","g2t_emc_hit","g2t_hca_hit",""},                      // a piece of scintillator in FMS Preshower
  {kUnknownId            ,"hca","HCAL","HCEL","g2t_emc_hit","g2t_hca_hit",""},                      // 3*3 cell in tower, HCES has 16*16 fibers
  {kUnknownId            ,"hca","HCAL","HCES","g2t_emc_hit","g2t_hca_hit",""},                      // 3*3 cell in tower, HCES has 16*16 fiber
  {kUnknownId            ,"hca","HCAL","HSTP","g2t_emc_hit","g2t_hca_hit",""},                      // single strips in pre shower, preshower 
  {kUnknownId            ,"hca","HCAL","LEDG","g2t_emc_hit","g2t_hca_hit",""},                      // Lead glass
  {kFcsHcalId            ,"hca","HCAH","HSCI","g2t_hca_hit","g2t_hca_hit","StFcsCollection"},       // 2*260 FCS HCal tower Scintillator Plate
  {kUnknownId            ,"igt","IGTD","IGAL","g2t_igt_hit","g2t_igt_hit",""},                      //
  {kIstId                ,"ist","ISTB","IBSS","g2t_ist_hit","g2t_ist_hit","StRnDHitCollection"},    // the Silicon Sensor
  {kMtdId                ,"mtd","MUTD","MIGG","g2t_mtd_hit","g2t_mtd_hit",""},                      // 28*5*5 a single gas gap
  {kMtdId		 ,"mtd","MUTD","MTTF","g2t_mtd_hit","g2t_mtd_hit",""},                      // the MTD11 5-tray group mother
  {kMtdId		 ,"mtd","MUTD","MTTT","g2t_mtd_hit","g2t_mtd_hit",""},                      // the MTD11 3-tray group mother
  {kMwpcWestId		 ,"mwc","TPCE","TMSE","g2t_mwc_hit","g2t_mwc_hit",""},                      // single sensitive volume
  {kPxlId                ,"pix","PIXL","PLAC","g2t_pix_hit","g2t_pix_hit","StRnDHitCollection"},    //
  {kPhmdId               ,"pmd","PHMD","PDGS","g2t_pmd_hit","g2t_pmd_hit", ""},                     // The inner cell in the PMD module
  {kUnknownId            ,"rch","RICH","FREO","g2t_rch_hit","g2t_rch_hit",""},
  {kUnknownId            ,"rch","RICH","QUAR","g2t_rch_hit","g2t_rch_hit",""},
  {kUnknownId            ,"rch","RICH","RCSI","g2t_rch_hit","g2t_rch_hit",""},
  {kUnknownId            ,"rch","RICH","RGAP","g2t_rch_hit","g2t_rch_hit",""},
//{kBarrelEmcPreShowerId ,"smd","CALB","CSDA","g2t_emc_hit","g2t_smd_hit",""},                      // Al block with sensitive gas volume
  {kBarrelEmcPreShowerId ,"smd","CALB","CSHI","g2t_emc_hit","g2t_smd_hit",""},                      // 2*60*2*4*30 Al block with sensitive gas volume
  {kSsdId     		 ,"ssd","SISD","sfsd","g2t_ssd_hit","g2t_ssd_hit","StSsdHitCollection"},
  {kSsdId     		 ,"ssd","SISD","SFSD","g2t_ssd_hit","g2t_ssd_hit","StSsdHitCollection"},
  {kSsdId     		 ,"svt","SVTT","SFSD","g2t_svt_hit","g2t_ssd_hit","StSsdHitCollection"},
  {kStgcId               ,"stg","STGH","STGP","g2t_fts_hit","g2t_stg_hit",""},                      // 16*2 pentagon sub shapes for Gas module, pgon triangle
  {kStgcId               ,"stg","STGH","STGL","g2t_fts_hit","g2t_stg_hit",""},                      // 16*2 pentagon sub shapes for Gas module, pgon triangle
  {kStgcId               ,"stg","STGH","STGS","g2t_fts_hit","g2t_stg_hit",""},                      // 16*2 pentagon sub shapes for Gas module, pgon triangle
  {kSvtId                ,"svt","SVTT","svtd","g2t_svt_hit","g2t_svt_hit","StSvtHitCollection"},
  {kSvtId                ,"svt","SVTT","SVTD","g2t_svt_hit","g2t_svt_hit","StSvtHitCollection"},
  {kTofId     		 ,"tfr","BTOF","BRSG","g2t_ctf_hit","g2t_tfr_hit","StBTofCollection"},      // 2*60**32*6 the sensitive gas layer in the TOFr module
  {kTofId     		 ,"tof","BTOF","BCSB","g2t_ctf_hit","g2t_tof_hit","StBTofCollection"},      // the sensitive gas layer in the TOFr module
  {kTpcId     		 ,"tpc","TPCE","tpad","g2t_tpc_hit","g2t_tpc_hit","StTpcHitCollection"},    // 2*12*76 => 100*(12*(n_1-1)+n_2) + n_3
  {kTpcId     		 ,"tpc","TPCE","TPAD","g2t_tpc_hit","g2t_tpc_hit","StTpcHitCollection"},
  {kUnknownId            ,"vpd","VPDD","VRAD","g2t_vpd_hit","g2t_vpd_hit",""},                      // 2*19 light-producing layer (scintillator or quartz) 
  {kFcsWcalId            ,"wca","WCAH","WSCI","g2t_emc_hit","g2t_wca_hit","StFcsCollection"},       // 2*748 FCS ECal tower scintilator layer
  {kZdcWestId            ,"zdc","ZCAL","QSCI","g2t_emc_hit","g2t_zdc_hit",""}                       // 2*260 sensitive Fiber layer 
};
static const Int_t NoDetectors = sizeof(Detectors)/sizeof(StarDetectorMap_t);
#endif
