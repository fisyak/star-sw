#! /usr/bin/env perl
use File::Basename;
use Cwd;
use Env;
my $macro = "dEdx";
my $hist = "";
my $Production = "";
my $scr = "";
my $STAR_LEVEL = ".DEV2";
my $Mode = 2;
my $disk = "*";
my $keep = 0;
my $year = "*";
my $select = "*0";
my $DIR = Cwd::cwd();
my $maxFjob = 1;
my $minDay = 0;
my $maxDay = 366;
my $RECO = "/reco/*/*/";
my $FILE = "/*/st_physics";
my $NEvents = 100000;
my $step = 0;
#================================================================================
#  dir /gpfs01/star/data*/reco/production_7p7GeV_2021/ReversedFullField/P22ia*/2021/*/*/*event.root
#  dir -ltrd /gpfs01/star/data*/reco/production_*/*/*/* | awk -F\/ '{print $6"/"$8}' | sort -u
# production_11p5GeV_2020/P21ib_calib
# production_13p5GeV_fixedTarget_2020/P21ic_calib
# production_13p5GeV_fixedTarget_2020/P21id
# production_14p5GeV_2019/P21ic
# production_19GeV_2019b/P21ic
# production_19GeV_2019/P20ic_calib
# production_19GeV_2019/P21ic
# production_19p5GeV_fixedTarget_2020/P21ic_calib
# production_19p5GeV_fixedTarget_2020/P21id
# production_26p5GeV_fixedTarget_2018/P19ie
# production_26p5GeV_fixedTarget_2020/DEV
# production_26p5GeV_fixedTarget_2020/P21ic_calib
# production_27GeV_fixedTarget_2018/P19ie
# production_27GeV_fixedTarget_2018/P19ie.SL20d
# production_31GeV_fixedTarget_2019/P21ic_calib
# production_31GeV_fixedTarget_2019/P21id
# production_31p2GeV_fixedTarget_2020/P21ic_calib
# production_31p2GeV_fixedTarget_2020/P21id
# production_3p85GeV_fixedTarget_2019/P21ic_calib
# production_3p85GeV_fixedTarget_2019/P21id
# production_4p59GeV_fixedTarget_2019/P21ic_calib
# production_4p59GeV_fixedTarget_2019/P21id
# production_5p75GeV_fixedTarget_2020/P21ic_calib
# production_5p75GeV_fixedTarget_2020/P21id
# production_7.3GeV_fixedTarget_2019/P21ic_calib
# production_7.3GeV_fixedTarget_2019/P21id
# production_7p3GeV_fixedTarget_2020/P21ic_calib
# production_7p3GeV_fixedTarget_2020/P21id
# production_7p7GeV_2021/DEV
# production_7p7GeV_2021/P22ia
# production_9p2GeV_2020b/P21ib_calib
# production_9p2GeV_2020c/P21ib_calib
# production_9p2GeV_2020/P21ib_calib
# production_9p8GeV_fixedTarget_2020/P21ic_calib
# production_9p8GeV_fixedTarget_2020/P21id
# production_AuAu200_2019/P21id
# production_AuAu200_2019/P22ia
# production_dAu200_2021/DEV
# production_isobar_2018/P21id
# production_isobar_2018/P21id.SL21d
# production_isobar_2018/P22ia
# production_OO_200GeV_2021/DEV
# production_pp500_2022/dev
# production_pp500_2022/DEV

# dir -ltrd /gpfs01/star/data*/reco/production_*/*/*/*
# dir -ltrd /gpfs01/star/data*/reco/production_*/*/*/* | awk -F\/ '{print $6}' | sort -u 
# on disks
# production_26p5GeV_fixedTarget_2018
# production_27GeV_fixedTarget_2018
# production_isobar_2018

# production_14p5GeV_2019
# production_19GeV_2019
# production_31GeV_fixedTarget_2019
# production_7.3GeV_fixedTarget_2019
# production_3p85GeV_fixedTarget_2019
# production_4p59GeV_fixedTarget_2019
# production_AuAu200_2019

# production_11p5GeV_2020
# production_13p5GeV_fixedTarget_2020
# production_19p5GeV_fixedTarget_2020
# production_26p5GeV_fixedTarget_2020
# production_31p2GeV_fixedTarget_2020
# production_5p75GeV_fixedTarget_2020
# production_7p3GeV_fixedTarget_2020
# production_9p2GeV_2020
# production_9p2GeV_2020b
# production_9p2GeV_2020c
# production_9p8GeV_fixedTarget_2020

# production_7p7GeV_2021
# production_dAu200_2021
# production_OO_200GeV_2021

# production_pp500_2022
#============================ Final Runs ===================================================
# hist238  for Run I  (2001) 
# RunII08             (2002)
# Hist312  for Run II (2002)
# Hist543  for Run III(2003)
# Hist815  for Run III(2003)
# Hist970  for Run IV (2004)
# Hist032  for Run V  (2005)
# Hist128  for Run VI (2006)
# RunVII69            (2007)
# RunVIII20           (2008)
#================================================================================
#$scr = "/star/rcf/disk1/star/fisyak/hist9/";
#$scr = "/online/evtpool/Data01/Hist11/"; dx correction only pulser
# $scr = "/online/evtpool/Data01/Hist12/"; # no dx correction only pulser
# $scr = "/online/evtpool/Data01/Hist13/"; # fix bug in TpcTransformer, but bug in fee
# $scr = "/online/evtpool/Data01/Hist14/"; # no callibration at all 
# $scr = "/online/evtpool/Data01/Hist15/"; # pulser only
# $scr = "/online/evtpool/Data01/Hist16/"; # pulser + Fee only (based on mean)
# $scr = "/online/evtpool/Data01/Hist17/"; # pulser + Fee only (based on mu), Normolize to 1 for fit
#$scr = "/online/evtpool/Data01/Hist18/"; # 17 + new fit base on x*0.36 low
# ========================== 2001 Run I  =================================
#$hist = "Hist18"; # 17 + new fit base on x*0.36 low
#$hist = "Hist19"; # + time & drift distance correction
#$hist = "Hist20"; # + fix scale for Fit, add scale for I70 and I60
#$hist = "Hist21"; # + new BB parameterization 
#$hist = "Hist22"; # + account shift in cluster shape
#$hist = "Hist23"; # + new cluster shift, fitZ vs length, fitdZ vs length
#$hist = "Hist24"; # remove correction from version 23. Add row to row correlations and Correct Sirrf for length
#$hist = "Hist25"; #  Add row to row correlations and change sign of Correct Sirrf for length
#$hist = "Hist26"; #  exp for length correction, split correlation into Ineer and outer, remove duplicated entries
#$hist = "Hist27"; #  add correlation, remove length correction, remove cluster shape correction.
#$hist = "Hist28"; #  return back to 26, add weighte dcorrelation histos
#$hist = "Hist29"; #  28 + revisited correction for dEdx shape (separated inner and outer sectors)
#$hist = "Hist30"; #  dst production
#$hist = "P00hm"; #  dst production, enlarge cuts, add histograms for uncorrected data
#$hist = "Hist40"; # new pulser correction, Fee correction is switched off
#$hist = "Hist41"; # use global tracks, new pulser table, old Fee Corrections
#$hist = "Hist42"; # use global tracks, new pulser table, with +/2 factor in correction, old Fee Corrections
#$hist = "Hist43"; # use primary tracks, new pulser table, with +/2 factor in correction, old Fee Corrections
#$hist = "Hist44";  # new FreeGain Correction
#$hist = "Hist45";  # new Pulser gains, new FreeGain Correction
#$hist = "Hist46";  # newest Pulser gains from Fabrice 2/13/01, new FreeGain Correction
#$hist = "Hist47";  # 46 + Half Fee corrections, remove row 13 -- something is wrong !
#$hist = "Hist48";  # Correction in tpcdaq, only time correction, use dev01a production
#$hist = "Hist49";  # Correction in tpcdaq, time correction + old Fee correction, use dev01a production
#$hist = "Hist50";   # Correction in tpcdaq, time correction + new Fee correction, use dev01a production
#$hist = "Hist51";   # 50 + new Fee correction (g+pol1), no length dep. in BB, use dev01a production
#$hist = "Hist52";   # 50 + new Fee correction (g+pol1) with no length dep. in BB, use dev01a production
#$hist = "Hist53";   # 52 + drift correction
#$hist = "Hist54";   # 53 +  overshif by 8%
#$hist = "Hist55";   # 54  +  different xscale for inner and outer
#$hist = "Hist56";   # == 55 , use dev01b production
#$hist = "Hist57";   # == 55 , remove 8% offset
#$hist = "Hist58";    # == 57 + shift corrections
#$hist = "Hist59";    # new shape for dEdx fit
#$hist = "Hist60";    # restore BB Length correction
#$hist = "Hist61";    # the same as 60 but with new dsts DEV01b
#$hist = "Hist62";    # add correlation, bad gradient
#$hist = "Hist63";    # remove  correlation, add row 13, add uncorrected secrow
#$hist = "Hist64";    # replace fee correction by sector/row correction, remove drift distance
#$hist = "Hist65";    # add drift correction the same for all inner/outer sectors
#$hist = "Hist66";    # add track length correction
#$hist = "Hist67";    # add track length correction
#$hist = "Hist68";    # add track length correction
#$hist = "Hist69";    # 68 + Trees
#$hist = "Hist70";    # new BB
#$hist = "Hist71";    # shift  BB by 7%
#$hist = "Hist72";    # new BB, clean up dEdxMaker, dst
#$hist = "Hist73";    # correct scale for z, i70, i60
#$hist = "Hist74";    # correct scale for pulls
#$hist = "Hist75";    # change shape 
#$hist = "Hist76";    # one more iteration with shape 
#$hist = "Hist77";    # one more iteration with shape 
#$hist = "Hist78";    # new dst and 15 parameter fit for shape
#$hist = "Hist79";    # fix bug in shape for inner in hist78
#$hist = "Hist80";    # new shape, remove lenth dependence from BB
#$hist = "Hist81";    # bug in new shape fixed, remove lenth dependence from BB
#$hist = "Hist82";    # remove shape correction
#$hist = "Hist83";    # new shift 
#$hist = "Hist84";    # new shape
#$hist = "Hist85";    # new shape
#$hist = "Hist86";    # new shape
#$hist = "Hist87";    # charge dependence
#$hist = "Hist88";    # charge dependence on pad something is wrong
#$hist = "Hist89"; # switch to new production and apply correction from Ipad
#$hist = "Hist90"; # mess with sector/row new + old  production and apply new correction from Ipad
#$hist = "Hist91"; # new + old  production and apply correction from Ipad (87)
#$hist = "Hist92"; # new + old  production no Volume charge corrections 
#$hist = "Hist93"; # new + old  production with Volume charge corrections 
#$hist = "Hist94"; # new + old  production with Volume charge and TimeBuket corrections, RMS 
#$hist = "Hist95"; # new production with NO Volume charge and TimeBuket corrections. 
#$hist = "Hist96"; # new production with both Volume charge and TimeBuket corrections. 
#$hist = "Hist97"; # 96 + extra correction for low dE
#$hist = "Hist98"; # no correction at all (Simu)
#$hist = "Hist99"; # simulation
#$hist = "Hist100"; # restore corrections (97 + i3pad)
#$hist = "Hist101"; # 100 + shape
#$hist = "Hist102"; # new shape
#$hist = "Hist103"; # new shape
#$hist = "Hist104"; # new shape with new length corrrection for BB (wrong)
#$hist = "Hist105"; # new shape with no length corrrection for BB 
#$hist = "Hist106"; # new shape with length corrrection for BB, remove I3pad correction
#$hist = "Hist107"; # new shape with additional length corrrection for BB
#$hist = "Hist108"; # new shape without  length corrrection for BB
#$hist = "Hist109"; # new shape without length corrrection for BB
#$hist = "Hist110"; # new shape with new length corrrection for BB
#$hist = "Hist111"; # remove TH3, correct pull

#$hist = "Hist112"; # 
#$hist = "Hist113"; #3
#$hist = "Hist114"; #3  create flow micro dst
#$hist = "Hist115"; #3  new BB curve + new scale for I70 & I60
#$hist = "Hist116"; #3  BB curve -2% + new scale for I70 & I60 + flow microdst
#$hist = "Hist117"; #3   BB curve at fixed length = 60 cm; new Shape histograms
#$hist = "Hist118"; #3   first order correlation removal
#$hist = "Hist119"; #3   recover after correlation corrections
#$hist = "Hist120"; #3 use library version with scale 560/335 + flow pico 
#$hist = "Hist121"; # use new dst 
#$hist = "Hist122"; # use new dst; + track parameters from global; add dEdx Tree 
#$hist = "Hist123"; # new GEANT base parameterization for BB; no length dependence
#$hist = "Hist124"; # + length dependence
#$hist = "Hist125"; # == hist122 (BB from library) + remove hit selection
#$hist = "Hist127"; # test y2001 corrections for y2000
#$hist = "Hist201"; # 2001data dst 
#$hist = "Hist202"; # 2001data dst  correct time
#$hist = "Hist203"; # 2001data dst from data13
#$hist = "Hist204"; # 2001data dst from data13
#$hist = "Hist205"; # 2001data dst from data13
#$hist = "Hist206"; # 2001 dst for dE/dx time correction
#$hist = "Hist207"; # 2001 dst for dE/dx before time correction new production 
#$hist = "Hist208"; # 2001 dst for dE/dx before time correction new production 
#$hist = "Hist209"; # 2001 dst for dE/dx after time correction new production 
#$hist = "Hist210"; # 209 + SecRow correction === No  SecRow correction
#$hist = "Hist211"; # 209 + SecRow correction === mess with afs 
#$hist = "Hist212"; # 209 + SecRow correction 
#$hist = "Hist213"; # 209 + SecRow correction + clean bad runs, add 3D histograms
#$hist = "Hist214"; # 209 + new SecRow correction (from 3D) + clean bad runs, add 3D histograms
#$hist = "Hist215"; # + ZSector correction, Sirrf with fixed length = 60 cm
#$hist = "Hist216"; # + ZSector correction with bug fix, Sirrf with fixed length = 60 cm
#$hist = "Hist217"; # + add shift for fitted ionization
#$hist = "Hist218"; # restrore track length correction in BB, add pressure dependence, select uniq hyps
#$hist = "Hist219"; # add extra scale for I70 and I60
#$hist = "Hist220"; # add Bichsel histograms. 
#$hist = "Hist221"; # add Bichsel histograms. GeV2keV
#$hist = "Hist222"; # add Bichsel histograms. GeV2keV
#$hist = "Hist223"; # define uniq as 5 sd and remove tpcGas
#$hist = "Hist224";  # use for calibration tracks with p > 200 MeV and trackLength > 40 cm
#$hist = "Hist225";  # add dE/dx histograms for MIP, sec, row
#$hist = "Hist226";  # p > 1.5 GeV/c
#$hist = "Hist227";  # p > 1.5 GeV/c; new SecRow correction, Add Pressure histograms
#$hist = "Hist228";  # p > 1.5 GeV/c; new SecRow correction, Add Pressure corrections, remove TimeScale
#$hist = "Hist229";  # p > 1.5 GeV/c; use Bichsel functions
#$hist = "Hist230";  # p > 1.5 GeV/c; use Bichsel functions; add correction for Inner/Outer; plot norm. in SecRow3Mip
#$hist = "Hist231"; # old version of dEdx (no Bichsel) for pp data
#$hist = "Hist232"; # old version of dEdx (no Bichsel) for pp data with TimeGain Correction
#$hist = "Hist233"; # 232 + new SecRow correction
#$hist = "Hist234"; # 233 + new DriftDistance Correction + track length correction in Sirrf
#$hist = "Hist235"; # 234 + new oveall scale 
#$hist = "Hist236"; #  new code for StEvent,AuAu + pp
#$hist = "Hist237"; #  236 + new Pressure correction + add event monitor histograms
#$hist = "Hist238"; #  237 + new TimeP corrections + add event monitor histograms
#$hist = "Hist239"; #  238 remove drift distance correction
#$hist = "Hist240"; #  run .dev (standard) version of dEdx to check proton run quality
#$hist = "Hist241"; #  run version of dEdx with simu option (no corrections)
#$hist = "Hist242"; #  new tcl no calibration, no length dependence of Bethe Bloch, add histograms for gasMonitor, 1/10 of statistics
#$hist = "Hist243"; #  new tcl no calibration, no length dependence of Bethe Bloch, add histograms for gasMonitor
#$hist = "Hist244"; #  the same as Hist243 but with new production (Deconvolution flag set in tcl)
#$hist = "Hist245"; #  +Pressure Correction (adjust Bichsel to BetheBloch)
#$hist = "Hist246"; #  +additional histograms for gas parameters, remove glob variables from StdEdxMaker, (no yet)TimePressure Correction
#$hist = "Hist247"; # no corrections at all for new production 
#$hist = "Hist248"; # correction for tptPressure and Secrow bug with drift distance
#$hist = "Hist249";
#$hist = "Hist250";# only 1/10 of statistics, no calibration, move calibration point to 0.25 < p < 0.4 Gev/c and Adc histograms
#$hist = "Hist251";# all statistics, only SecRow3B calibration, move calibration point to 0.25 < p < 0.4 Gev/c and Adc histograms
#$hist = "Hist252";# all statistics, add Pressure Correction
#$hist = "Hist253";# all of statistics, calibration based on Primary track with 0.4 < p < 0.5, no calibration applied
#$hist = "Hist254";#09/13/02 calibration based on Primary track with 0.4 < p < 0.5, new Pressure and SecRow callibration applied 
#$hist = "Hist255";#09/14/02 add Dirft*Oxygen corrrection, 
#$hist = "Hist256"; #09/15/02 once again no corrections at all
#$hist = "Hist257"; #09/15/02 SecRow + Pressure correction base on Bichsel
#$hist = "Hist258"; #09/16/02 +DriftDistance correction
#$hist = "Hist259"; #09/16/02 +new Calibration point for fitZ, I60 and I70
#$hist = "Hist260"; #09/16/02 +new new Calibration point for fitZ, I60 and I70, add histograms for linearity; full statistics
#$hist = "Hist261"; #09/17/02 add correction to Drift*Oxygen switch x <=> y in Adc
#$hist = "Hist262"; #09/18/02 add additional correction for SecRowA, split Multiplicity for I/O, set 2*sigma cut for SecRow3Mip
#$hist = "Hist263"; #09/20/02 add nonlinearity correction (bug in nonlinearity)
#$hist = "Hist264"; #09/22/02 add nonlinearity correction
#$hist = "Hist265"; #09/24/02 new SecRowC after  nonlinearity correction 1/5 of statistics
#$hist = "Hist266"; #09/24/02 scale down by a factor of ~1.5
#$hist = "Hist267"; #09/25/02 no correction 1/5 of statistics, try to get nonlinearity for both new and old cluster
#$hist = "Hist268"; #09/26/02 no correction 1/20 of statistics, Inner/Outer correction only
#$hist = "Hist269"; #09/26/02 remove requirement for primary track no correction 1/20 of statistics, Inner/Outer correction only
#$hist = "Hist279"; #09/26/02  set  nonlinearity correction for dER (instead of dE), fix scales for I70,I60 and fitZ
#$hist = "Hist280"; #09/26/02  put nonlinearity correction
#$hist = "Hist281"; #09/27/02  put nonlinearity correction (only linear term)
#$hist = "Hist282"; #09/27/02  put nonlinearity correction (only linear term)
#$hist = "Hist283"; #09/27/02  try log10 parameterization for ADC
#$hist = "Hist284"; #09/27/02  fix bug in TpcAdc table
#$hist = "Hist285"; #09/28/02  Pressure correction
#$hist = "Hist286"; #09/29/02  SecRow correction
#$hist = "Hist287"; #09/30/02  check ADC for +/- separately bug in prediction (1.e6 missing) 
#$hist = "Hist288"; #09/30/02  check ADC for +/- separately (copy to hols StarDb and StdEdxMaker3)
#$hist = "Hist289"; #09/30/02 new ADC correction from Positive/Negatives
#$hist = "Hist290"; #10/01/02 move to old log corrections. add histograms with dependence on Z*OX for differnet charge
#$hist = "Hist291"; #10/04/02  use Adc correction for positive track only taken from Hist290 20% 
#$hist = "Hist292"; #10/05/02  + Pressure correction
#$hist = "Hist293"; #10/07/02  + new Pressure correction + ZO preset dependence 
#$hist = "Hist294"; #10/08/02  + new Pressure correction + ZO preset dependence + SecRow (fix bug in TpcDriftOx and rerun)
#$hist = "Hist2945"; #10/08/02  + zDrift correction
#$hist = "Hist296"; #10/15/02  + dXCorrection 
#$hist = "Hist297"; #10/16/02  + remove overlaping clusters (flag() != 0), remove test on geometry bug with overlap flag
#$hist = "Hist298"; #10/17/02  + remove overlaping clusters (flag() != 0), remove test on geometry 
#$hist = "Hist299"; #10/21/02  new DoFitZ()
#$hist = "Hist300"; #10/22/02  new DoFitZ() ; fit BG
#$hist = "Hist301"; #10/26/02  no DoFitZ() ; add Bichsel Likelyhood
#$hist = "Hist302"; #10/27/02  add track length corrections
#$hist = "Hist303"; #10/30/02  Create FlowPicoDst
#$hist = "Hist304"; #10/31/02  step back with dX correction (very small sample) nof flowpico
#$hist = "Hist305"; #10/31/02  fix dX correction
#$hist = "Hist306"; #10/31/02  new TrackLengthCorrection from 305
#$hist = "Hist307"; #11/04/02  just check what is commmitied
#$hist = "Hist308"; #11/07/02  new production with old tcl, dEdxY2 maker from STAR_LIB
#$hist = "Hist309"; #11/07/02  308 + add shift in ionization from Hist308a Hist309dAu200Min hijing
#$hist = "Hist310"; #12/02/02  Add histograms for N.Smirnov
#$hist = "Hist311"; #12/02/02  Add sumw2 for histograms for N.Smirnov
#$hist = "Hist312"; #01/28/03  reproduction of 2002
# ========================== 2003 Run II  =================================
#$hist = "Hist313"; #01/28/03  2003 run 4027041
#$hist = "Hist401"; #02/11/03  2003 run dAuMinBias
#$hist = "Hist402"; #02/21/03  2003 run dAuMinBias P03ia to check track length correction with old clustering with DoNotCorrectdEdx
#$hist = "Hist403"; #02/23/03  2003 run dAuMinBias P03ia to get SecRow correction, Tracklength correction are turn off
#$hist = "Hist404"; #02/23/03  2003 run dAuMinBias P03ia add new SecRow correction, Tracklength correction are turn off
#$hist = "Hist405"; #02/23/03  2003 run dAuMinBias P03ia add new SecRow correction, new Tracklength bug TpcLengthCorrection Table
#$hist = "Hist406"; #02/23/03  2003 run dAuMinBias P03ia add new SecRow correction, new Tracklength 
#$hist = "Hist407"; #03/09/03  2003 run dAuMinBias P03ia ; 10% of statistics
#$hist = "Hist408"; #03/09/03  2003 run dAuMinBias P03ia no calibration at all; 10% of statistics

#$hist = "Hist409"; #03/10/03  2003 run dAuMinBias P03ia simulation mode (bad stardev); 10% of statistics
#$hist = "Hist410"; #03/31/03  2003 run dAuMinBias P03ia; 20% of statistics to check ADC corrections 
#$hist = "Hist411"; #04/11/03  2003 run dAuMinBias P03ia; whole statistics, calibration from AuAu
#$hist = "Hist412"; #05/18/03  2003 run dAuMinBias P03ia; whole statistics, rearrage Adc Correction histograms; 10% of statistics
#$hist = "Hist413"; #05/19/03  2003 run dAuMinBias P03ia; remove TrackLengthCorrection; 10% of statistics
#$hist = "Hist414"; #05/19/03  2003 run dAuMinBias P03ia; add new TrackLengthCorrection; 10% of  statistics
#$hist = "Hist415"; #05/21/03  2003 run dAuMinBias P03ia; for Adc use prediction with given dX;full statistics
#$hist = "Hist416"; #05/22/03  fix bug in reference for AD calculations
#$hist = "Hist417"; #05/31/03  new TpcSecRowB correction (G2) 10%
#$hist = "Hist418"; #06/01/03  switch off all corrections 
#$hist = "Hist419"; #07/06/03  Corrections are on, spacecharge histograms, ttree for tracklengh > 20 cm (10%) 
#$hist = "Hist501";$Production = "P03if"; #09/023/03  Restart calibration with ToF P03ie; 0-pass no correction, found bug in TofCorrection
#$hist = "Hist502";$Production = "P03if"; #09/024/03  Restart calibration with ToF P03ie
#$hist = "Hist503";$Production = "P03if"; #09/024/03  Restart calibration with ToF P03ie; inverse sign of correction
#$hist = "Hist504";$Production = "P03if"; #09/024/03  Restart calibration with P03if; 
#$hist = "Hist505";$Production = "P03if"; #09/024/03  P03if : Simulation mode: no corrections at all
#$hist = "Hist506";$Production = "P03if"; #09/025/03  P03if :correction from P03ia
#$hist = "Hist507";$Production = "P03if"; #09/025/03  P03if : R corrections only
#$hist = "Hist508";$Production = "P03if"; #10/01/03  P03if : R correction as a scale factor; look for dY dependence
#$hist = "Hist509";$Production = "P03iF";#10/04/03  P03if : default corrections, Fabrice gains
#$hist = "Hist510";$Production = "P03if"; #10/04/03  P03if : default corrections, default gains, the same statics as for 509
#$hist = "Hist511";$Production = "P03iT";#10/05/03  P03iF : default corrections, Tonko gainsfor the pulser run as last Fabrice's ones
#$hist = "Hist512";$Production = "P03iT"; #10/06/03  P03iT : set SecRow = 1, Tonko gains for the pulser run as last Fabrice's ones
#$hist = "Hist513";$Production = "P03iF"; #10/06/03  P03iF : set SecRow = 1, Fabrice gains for the pulser run as last Fabrice's ones
#$hist = "Hist514";$Production = "P03if"; #10/06/03  P03if : corrections AuAu run
#$hist = "Hist515";$Production = "P03if"; #10/07/03  P03if : new TpcSecRowB corrections
#$hist = "Hist516"; $Production = "P03iFT"; #10/08/03  P03iFT : gain Correction TonkoAndMe and SecRowB == 1
#$hist = "Hist517";$Production = "P03if"; #10/08/03  P03if :
#                  new TpcSecRowB corrections; take out DriftDistanceCorrection,Multiplicity,dXCorrection
#                                                                 R+drift+Presure
#$hist = "Hist518";$Production = "P03if"; #10/09/03 : new pressure correction, ad dX histograms
#$hist = "Hist518";$Production = "P03if"; #10/09/03 : new pressure correction, ad dX histograms
#$hist = "Hist519";$Production = "ppP02ge"; $macro = "dEdxN"; # 10/10/03 : no correction pp2001/pp2002 production
#$hist = "Hist520";$Production = "ppP03if"; $macro = "dEdxN"; # 10/10/03 : no correction pp2001/pp2002 production
#$hist = "Hist521";$Production = "P03if"; # 10/10/03 :change MostProbableZ to AverageZ 
#$hist = "Hist522";$Production = "P03if"; # 10/11/03 :SecRowB correction from  AverageZ 
#$hist = "Hist523";$Production = "P03if"; # 10/12/03 no adc nonlinearity, no pressure, no secrowb, no dx, no track length,no Z
#$hist = "Hist524";$Production = "P03if"; # 10/12/03 no adc nonlinearity, +pressure, +secrowb, no dx, no track length,no Z <=== bad normalization in secrow ; redo in 525
#$hist = "Hist525";$Production = "P03if"; # 10/13/03 no adc nonlinearity, +pressure, +secrowb, no dx, no track length,no Z
#$hist = "Hist526";$Production = "P03if"; # 10/13/03 no adc nonlinearity, +pressure, -secrowb, no dx, no track length,no Z
#$hist = "Hist527";$Production = "P03iT2"; $macro = "dEdxN";#10/14/03  P03iT : set SecRow = 1, Tonko gains2 for the pulser run 
#$hist = "Hist528";$Production = "P03if"; # 10/14/03 no adc nonlinearity, +pressure, secrowb ==1, no dx, no track length,no Z
#$hist = "Hist529";$Production = "P03if"; # 10/14/03 no adc nonlinearity, +pressure, +secrowb, no dx, no track length,no Z
#$hist = "Hist530";$Production = "P03if"; # 10/14/03 no adc nonlinearity, +pressure, +secrowb, +new o2*drift; no dx, no track length,no Z
#$hist = "Hist531";$Production = "P03if"; # 10/14/03 no adc nonlinearity, +pressure, +secrowb, +new o2*drift; +z; no dx, no track length
# start over again remvoe ToF correction and set SecRow correction before Pressure, adc = 1;
#$hist = "Hist532";$Production = "P03if"; # 10/15/03 
#$hist = "Hist533";$Production = "P03if"; # 10/15/03 +SecRow
#$hist = "Hist534";$Production = "P03if"; # 10/15/03 +SecRow (correct overall scale)
#$hist = "Hist535";$Production = "P03if"; # 10/16/03 +SecRow+Pressure; add "just after correction histograms", cut drift< 25 cm
#$hist = "Hist536";$Production = "P03if"; # 10/16/03 +SecRow+Pressure; add "just after correction histograms", cut drift< 25 cm, +ZO
#$hist = "Hist537";$Production = "P03if"; # 10/17/03 +SecRow(536)+Pressure+dX(536); cut drift< 25 cm, +ZO
#$hist = "Hist538";$Production = "P03if"; # 10/17/03 +SecRow(536+537)+Pressure+dX(536); cut drift< 25 cm, +ZO
#$hist = "Hist539";$Production = "P03if"; # 10/17/03 +SecRow(536+537)+Pressure+dX(536); cut drift< 25 cm, +ZO+tracklength correction
#$hist = "Hist540";$Production = "P03if"; # 10/18/03 bug in TpcLengthCorrection
#$hist = "Hist541";$Production = "P03if"; # 10/20/03 add ad hoc saturation effect account via TpcdEdxCor.
#$hist = "Hist542";$Production = "P03ih"; $macro = "dEdx102";# 11/03/03 check for new production (use StEvent, nore calculation of dE/dx
#$hist = "Hist543";$Production = "P03ih";# 11/05/03 add correction to correction of tracklength
#$hist = "Hist544";$Production = "P03ih";# 11/06/03 remove track length correction 20% 
#$hist = "Hist545";$Production = "P03ih";# 11/06/03  track length correction from 544 
#$hist = "Hist546";$Production = "P03ih";# 11/08/03  run with version from MySQL
# ========================== 2002 Run II  =================================
#$hist = "RunII01"; $disk = "data47"; $RECO = "/reco/minBias22GeVZDC/ReversedHalfField/"; $Production = "P07id"; $year = "2001/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0;# 11/01/07 first pass 
#$hist = "RunII02"; $disk = "data47"; $RECO = "/reco/minBias22GeVZDC/ReversedHalfField/"; $Production = "P07id"; $year = "2001/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0;# 11/01/07 + TpcSecRowB.20010924.000001 wrong Adc Correction
#$hist = "RunII03"; $disk = "data47"; $RECO = "/reco/minBias22GeVZDC/ReversedHalfField/"; $Production = "P07id"; $year = "2001/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0;# 11/01/07 + TpcSecRowB.20010924.000000.C def
#$hist = "RunII04"; $disk = "data47"; $RECO = "/reco/minBias22GeVZDC/ReversedHalfField/"; $Production = "P07id"; $year = "2001/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0;# 11/02/07 + TpcSecRowB.20010924.000003.root
#$hist = "RunII05"; $disk = "data47"; $RECO = "/reco/minBias22GeVZDC/ReversedHalfField/"; $Production = "P07id"; $year = "2001/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0;# 11/02/07 + TpcLengthCorrectionB.20010924.000004.C
#$hist = "RunII06"; $disk = "data47"; $RECO = "/reco/minBias22GeVZDC/ReversedHalfField/"; $Production = "P07id"; $year = "2001/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0;# 11/03/07 + TpcEdge.20010924.000005.C
#$hist = "RunII07"; $disk = "data47"; $RECO = "/reco/minBias22GeVZDC/ReversedHalfField/"; $Production = "P07id"; $year = "2001/*/"; $FILE = "st_physics"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0;# 11/03/07 + TpcEdge.20010924.000005.C
#$hist = "RunII08"; $disk = "data46"; $RECO = "/reco/minBias22GeVZDC/ReversedHalfField/"; $Production = "P07id"; $year = "2001/*/"; $FILE = "st_physics"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 5; $Mode = 102;# 11/08/07 test results of production
#/star/data*/reco/*/*/P06id_calib/2006
#/star/data*/reco/*/*/P06id_calib/2006/*/st_physics*.event.root
#/star/data46/reco/ppProductionJPsi/FullField/P06id/2006/143/7143026/
# ========================== 2004 Run IV  =================================
#$hist = "Hist601";$Production = "P03ih_daq100"; $macro = "dEdx102"; # 11/01/03 default dE/dx 
#$hist = "Hist601";$Production = "P03ih_tcl"; # 11/01/03 default dE/dx 
#$hist = "Hist601";$Production = "P03ih_tcl"; # 11/01/03 default dE/dx 
#$hist = "Hist602";$Production = "P03ih_daq100"; $macro = "dEdx102"; # 12/01/03 default dE/dx, full test statitistics 
#$hist = "Hist602";$Production = "P03ih_tcl"; $macro = "dEdx102"; # 12/01/03 default dE/dx, full test statitistics
#$Production = "";         # old (March 2002 data)
#$Production = "P02gh1";    # Daq Tcl
#$Production = "P02gh2";    # old Tcl
#$Production = "P02gi1"; # new production with old tcl no flow pico
#$Production = "DEV";
#$Production = "P03ia";
#$Production = "P03ie";
#$Production = "P03iF";# Fabrice
#$Production = "P03iT"; Tonko
#$Production = "dev";
#$Production = "P02gi1C"; # new production with old tcl for Central
#$Production = "P02gi2"; # new production with new tcl
#$Production = "P02gi2C"; # new production with new tcl for Centra
#$Production = "P02gi2A"; # reproduction with new tcl
#$Production = "P02gi2B"; # an other reproduction with new tcl
#$Production = "P02gi3";  # new reproduction with daq tcl 12/03/02
#$Production = "dAu200Min";
#$Production = "AuAu200Min";
#$hist = "Hist701"; $Production = "dev_adc"; $macro = "dEdx102"; # fast offline adc
#$hist = "Hist701"; $Production = "dev_noadc"; $macro = "dEdx102"; # fast offline adc
#$hist = "Hist702"; $Production = "dev_adc";  # fast offline adc
#$hist = "Hist702"; $Production = "dev_noadc";  # fast offline adc
#$hist = "Hist703"; $Production = "dev_noadc";  # fast offline adc check acount of alignment
#$hist = "Hist703"; $Production = "dev_adc";  # fast offline adc check acount of alignment
#$hist = "Hist704"; $Production = "P04ib";  # check alignment
#$hist = "Hist705"; $Production = "P03ih";  # check new interface with old data (10%)
#$hist = "Hist706"; $Production = "P03ih";  # 03/13/04 check new Transformation (10%)
#$hist = "Hist707"; $Production = "P03ih";  # 03/14/04 back to global for dX calculations in StdEdxY2 (10%)
#$hist = "Hist708"; $Production = "P03ih";  # 03/14/04 fix bug in St_tpcCorrection::SumSeries
#$hist = "Hist709"; $Production = "P04ib";  # no calibartion
#$hist = "Hist710"; $Production = "P04ib";  # ADC correction from TrsMini
#$hist = "Hist711"; $Production = "P04ib";  # new ADC correction from TrsMini
#$hist = "Hist712"; $Production = "Fast";  # dev, use fast offline
#$hist = "Hist713"; $Production = "Fast";  # dev, use fast offline, with TpcSecRowB from dAu
#$hist = "Hist714"; $Production = "Fast";  # dev, use fast offline, new TpcSecRowB (from SecRow3A)
#$hist = "Hist715"; $Production = "Fast";  # dev, use fast offline, new TpcSecRowB (from SecRow3)
#$hist = "Hist716"; $Production = "Fast";  # dev, use fast offline, + new TpcZCorrection(no z restriction) + TpcDriftDistOxygen - Pressure
#$hist = "Hist717"; $Production = "Fast";  # 04/05/04 dev, use fast offline, +tpcPressureB
#$hist = "Hist718"; $Production = "Fast";  # 04/05/04 dev, use fast offline, + TpcDriftDistOxygen
#$hist = "Hist719"; $Production = "Fast";  # 04/06/04 dev, use fast offline, new TpcDriftDistOxygen (from Z3OGPHist718Fast)
#$hist = "Hist719"; $Production = "P04id";  # 04/06/04 dev, use P04id, new TpcDriftDistOxygen (from Z3OGPHist718Fast)
#$hist = "Hist720"; $Production = "P04id";  # 04/07/04 dev, use P04id, new TpcDriftDistOxygen (from Z3OGPHist719P04id), no TpcLengthCorrection
#$hist = "Hist721"; $Production = "P04id";  # 04/08/04 dev, use P04id,rescale ~1% TpcAdcCorrection, new TpcLengthCorrection; QA histograms 20%
#$hist = "Hist722"; $Production = "P04id";  # 04/08/04 dev, use P04id, +TpcLengthCorrection; modified QA histograms 25%

#$hist = "Hist801"; $Production = "P04ie"; $STAR_LEVEL = "SL04e";# 05/11/04 check for dAu with SL04e no calibration (just StEvent)
#$hist = "Hist802"; $Production = "P04ie"; $STAR_LEVEL = "SL04e";# 05/11/04 check for dAu with SL04e with Calibration
#$hist = "Hist803"; $Production = "P04ie"; $STAR_LEVEL = "SL04e";# 05/12/04 split bad hits in catagories (no PadSelection)
#$hist = "Hist804"; $Production = "P04ie"; $STAR_LEVEL = "SL04e";# 05/12/04 split bad hits in catagories for comparison with fcf
#$hist = "Hist804"; $Production = "P04ie_tcl"; $STAR_LEVEL = "SL04e";# 05/12/04 split bad hits in catagories for comparison with fcf
#$hist = "Hist805"; $Production = "P04ie"; $STAR_LEVEL = "SL04e";# 05/13/04 new correction for fcf
#$hist = "Hist805"; $Production = "P04ie_tcl"; $STAR_LEVEL = "SL04e";# 05/13/04 new correction for fcf
#$hist = "Hist806"; $Production = "P04ie_tcl"; $Mode = 12; $STAR_LEVEL = "SL04e";# 05/13/04 new correction for fcf
#$hist = "Hist806"; $Production = "P04ie"; $STAR_LEVEL = "SL04e";# 05/13/04 new correction for fcf
#$hist = "Hist807"; $Production = "P04ie"; $STAR_LEVEL = ".DEV2";# 05/15/04 check new code wrt new correction
#$hist = "Hist807"; $Production = "P04ie_tcl"; $STAR_LEVEL = ".DEV2";# 05/15/04 check new code wrt new correction
#$hist = "Hist808"; $Production = "P04ie_tcl"; $STAR_LEVEL = ".DEV2"; $Mode = 10;# 05/17/2004 check wrt new reproduction in dev
#$hist = "Hist808"; $Production = "P04ie"; $STAR_LEVEL = ".DEV2"; $Mode = 0;# 05/17/2004 check wrt new reproduction in dev
#$hist = "Hist809"; $Production = "P04ie"; $STAR_LEVEL = "dev"; $Mode = 102;# 05/18/2004 check wrt new reproduction in dev
#$hist = "Hist809"; $Production = "P04ie_tcl"; $STAR_LEVEL = "dev"; $Mode = 112;# 05/18/2004 check wrt new reproduction in dev
#$hist = "Hist810"; $Production = "P04if"; $STAR_LEVEL = "dev"; $Mode = 112;# 05/24/2004 check wrt new reproduction in dev
#$hist = "Hist810"; $Production = "P04if.ittf"; $STAR_LEVEL = "dev"; $Mode = 112;# 05/24/2004 check wrt new reproduction in dev
#$hist = "Hist811"; $Production = "P04if"; $Mode = 2;# 05/24/2004 check wrt .DEV2#
#$hist = "Hist812"; $Production = "P04if.ittf"; $Mode = 2;# 05/31/2004 check new dEdxY2
#$hist = "Hist813"; $Production = "P04if.ittf"; $Mode = 2;# 06/01/2004 check new dEdxY2 mismatch old new cluster finder
#$hist = "Hist814"; $Production = "P04if.ittf"; $Mode = 2;# 06/01/2004 check new dEdxY2
#$hist = "Hist815"; $Production = "P04if.ittf"; $STAR_LEVEL = "dev"; $Mode = 2;# 06/01/2004 check old dEdxY2
#$hist = "Hist815"; $Production = "P04if"; # 06/02/2004 check old dEdxY2 with tpt no hits

#$hist = "Hist821"; $Production = "P04ifAuAu200"; $Mode = 2;# 05/31/2004 
#$hist = "Hist822"; $Production = "P04ifAuAu200"; $STAR_LEVEL = "dev"; $Mode = 2; $macro = "dEdxOld";# 06/03/2004 
#$hist = "Hist823"; $Production = "P04ifAuAu200"; $Mode = 2;  # 06/03/2004 test with full statistics calibration from AuAu62
#$hist = "Hist824"; $Production = "P04ifAuAu200"; $Mode = 2;  # 06/05/2004 no calibrations at all
#$hist = "Hist825"; $Production = "P04ifAuAu200"; $Mode = 2;  # 06/06/2004 +ADC correction from TrsMini
#$hist = "Hist826"; $Production = "P04ifAuAu200"; $Mode = 2;  # 06/07/2004 +SecRow correction add AuAu62
#$hist = "Hist827"; $Production = "P04ifAuAu200"; $Mode = 2;  # 06/08/2004 +an other SecRow correction
#$hist = "Hist828"; $Production = "P04ifAuAu200"; $Mode = 2;  # 06/09/2004 + Pressure Correction
#$hist = "Hist829"; $Production = "P04ifAuAu200"; $Mode = 2;  # 06/10/2004 + ZO Correction
#$hist = "Hist830"; $Production = "P04ifAuAu200"; # 06/11/2004 rerun with no alignment, add HitsUsage histograms
#$hist = "Hist831"; $Production = "P04ifAuAu200"; # 06/12/2004 +dx correction (no alignment)
#$hist = "Hist832"; $Production = "P04ifAuAu200"; # 06/13/2004 +Water + Methan correction (no alignment) 50%
#$hist = "Hist833"; $Production = "P04ifAuAu200"; # 06/14/2004 +update SecRow correction (alignment)
#$hist = "Hist834"; $Production = "P04ifAuAu200"; # 06/15/2004  +Temperature correction, linear Methan correction, new TpcDriftDistOxygen
#$hist = "Hist835"; $Production = "P04ifAuAu200"; # 06/15/2004  + remove Temperature, Methan, fix dirftO2 to Blair no. 10%
#$hist = "Hist836"; $Production = "P04ifAuAu200"; # 06/16/2004  + remove dXcorrection, remove dX dependence in Bichsel parameterization
#$hist = "Hist837"; $Production = "P04ifAuAu200"; # 06/16/2004  + leave only offset in ADC correction 10%
#$hist = "Hist838"; $Production = "P04ifAuAu200"; # 06/17/2004  switch to GF : new AdcCorrection (offset + scale) + new TpcSecRowb; %20 shut for new dXCor
#$hist = "Hist839"; $Production = "P04ifAuAu200"; # 06/17/2004  switch to GF : +dXCorr 33% bug in dX correction (dX instead of log2(dX)
#$hist = "Hist840"; $Production = "P04ifAuAu200"; # 06/18/2004  switch to GF : +dXCorr 10% 
#$hist = "Hist841"; $Production = "P04ifAuAu200"; # 06/18/2004  switch to GF : -dXCorr, update Pressure, SecRow, restore Bichsel dX dependence 20% 
#$hist = "Hist842"; $Production = "P04ifAuAu200"; # 06/19/2004  switch to GF : driftcorr(Blair), zCorr, adccorrection
#$hist = "Hist842"; $Production = "P04ifAuAu200"; # 06/19/2004  switch to GF : driftcorr(Blair), zCorr, adccorrection
#$hist = "Hist843"; $Production = "P04ifAuAu200"; # 06/20/2004  switch to GF : +dXCorr, driftcorr(Blair), zCorr, adccorrection
#$hist = "Hist844"; $Production = "P04ifAuAu200"; # 06/21/2004 take off zCorrection, dXCorrection, add tpcMethaneIn
#$hist = "Hist845"; $Production = "P04ifAuAu200"; # 06/21/2004  modify TpcSecRowB (zCorrection, dXCorrection, add tpcMethaneIn are off)
#$hist = "Hist846"; $Production = "P04ifAuAu200"; # 06/21/2004  +TpcLength add ZBGX strange bug with D70 calculations
#$hist = "Hist847"; $Production = "P04ifAuAu200"; # 06/22/2004  +TpcLength add ZBGX 
#$hist = "Hist848"; $Production = "P04ifAuAu200"; # 06/25/2004  +remove ZBGX and Pressure/Temperature and Oxygen*Water 10%
#$hist = "Hist849"; $Production = "P04ifAuAu200"; # 06/26/2004  +add ZCorrection , add Npads and Ntbins histograms 40%
#$hist = "Hist850"; $Production = "P04ifAuAu200"; # 06/27/2004  modify TpcSecRowB 20%
#$hist = "Hist851"; $Production = "P04ifAuAu200"; # 06/27/2004  restore Adc correction in full
#$hist = "Hist852"; $Production = "P04ifAuAu200"; # 07/01/2004  update SecRow Correction
#$hist = "Hist853"; $Production = "P04ifAuAu200"; # 07/04/2004  an other update SecRow Correction 50%
#$hist = "Hist854"; $Production = "P04ifAuAu200"; # 07/06/2004  take out zCorrection 20%, new zbgx hitograms accept track with no. fit points > 20 (before requirement was nFitPoinst> 30 and Track length > 40 cm)
#$hist = "Hist855"; $Production = "P04ifAuAu200"; # 07/06/2004 new SecRow Correction
#$hist = "Hist861"; $Production = "P04igAuAu200"; $Mode = 102; # 07/07/2004 new production no calibration
#$hist = "Hist862"; $Production = "P04igAuAu200"; # 07/07/2004 redo SecRow correction, switch off TrackLength Correction, update TpcAdc correction
#$hist = "Hist863"; $Production = "P04igAuAu200"; # 07/08/2004 new SecRow correction (no s/r rejection) 20%
#$hist = "Hist864"; $Production = "P04igAuAu200"; # 07/09/2004 new SecRow correction (add s/r rejection for entires==0) 20%
#$hist = "Hist865"; $Production = "P04igAuAu200"; # 07/11/2004 switch from BichselT => P10T 10%
#$hist = "Hist866"; $Production = "P04igAuAu200"; # 07/13/2004 SecRow with  P10T, remove s/r 5/38-40 20%
#$hist = "Hist867"; $Production = "P04igAuAu200"; # 07/14/2004 SecRow with  P10T, remove s/r 5/38-40 5%
#$hist = "Hist868"; $Production = "P04igAuAu200"; # 07/14/2004 not pad *time correction, change fit to Bichsel version 5%
#$hist = "Hist869"; $Production = "P04igAuAu200"; # 07/17/2004 new Landau function fit, check probobilties 100%
#$hist = "Hist870"; $Production = "P04igAuAu200"; # 07/19/2004 new TpcZCorrection for each row, ue MySql 10% 
#$hist = "Hist871"; $Production = "P04igAuAu200"; # 07/19/2004 +tpcGasTemperature 10% 
#$hist = "Hist872"; $Production = "P04igAuAu200"; # 07/21/2004 +test MySQL 5% 
#$hist = "Hist873"; $Production = "P04igAuAu200"; # 07/21/2004 switch from outputGasTemperature to inputGasTemperature 5%
#$hist = "Hist874"; $Production = "P04igAuAu200"; # 07/21/2004 correct SecRow 20%
#$hist = "Hist875"; $Production = "P04igAuAu200"; # 07/25/2004 check new StTpcdEdxCorrections 5%
#$hist = "Hist876"; $Production = "P04igAuAu200"; # 07/26/2004 SecRowB from MySQL, take off z-Corr, add Charge histos, add ToF  10%
#$hist = "Hist877"; $Production = "P04igAuAu200"; # 07/27/2004 update SecRowB 10%
#$hist = "Hist878"; $Production = "P04igAuAu200"; # 07/27/2004 add dCharge correction 40%
#$hist = "Hist879"; $Production = "P04igAuAu200"; # 07/28/2004 test new tpcDb and dEdxY2 1%
#$hist = "Hist880"; $Production = "P04igAuAu200";  $STAR_LEVEL = ".dev";# 07/29/2004 check commits to dev 2%
#$hist = "Hist881"; $Production = "P04igAuAu200"; # 07/30/2004 add Charge3QdZ, remove dCharge 20%
#$hist = "Hist882"; $Production = "P04igAuAu200"; # 07/30/2004 split TpcSecRowC 33%
#$hist = "Hist884"; $Production = "P04igAuAu200"; # 07/31/2004 new splitted TpcSecRowC 5%
#$hist = "Hist885"; $Production = "P04igAuAu200"; # 07/31/2004 old splitted TpcSecRowC and remove Z 5%
#$hist = "Hist886"; $Production = "P04igAuAu200"; # 08/01/2004 wrong correction sign Adc  25%
#$hist = "Hist887"; $Production = "P04igAuAu200"; # 08/01/2004 fix Adc due to removing multiplicity   25%
#$hist = "Hist888"; $Production = "P04igAuAu200"; # 08/01/2004 check Calibration/tpc before putting it in MySQL 5 files
#$hist = "Hist889"; $Production = "P04igAuAu200"; # 08/01/2004 bug in case statement
#$hist = "Hist890"; $Production = "P04igAuAu200"; # 08/01/2004 check Calibration/tpc after putting it in MySQL whole statistics
#$hist = "Hist891"; $Production = "P04igPP"; # 08/04/2004 check new SecRow Corrections, reduce size of histograms
#$hist = "Hist892"; $Production = "P04igAuAu200"; # 08/06/2004 check TpcSpaceCharge (no really space charge correction) 5%
#$hist = "Hist893"; $Production = "P04igAuAu200"; # 08/07/2004 check TpcSpaceCharge for 5%
#$hist = "Hist894"; $Production = "P04igAuAu62"; # 08/09/2004 check TpcSpaceCharge + SecRow for AuAu 62 25%
#$hist = "Hist895"; $Production = "P04ihAuAu200"; $Mode = 102; # 08/09/2004 check production 5%
#$hist = "Hist896"; $Production = "DEV"; $Mode = 102; # 08/11/2004 check production 
#$hist = "Hist897"; $Production = "DEV"; $Mode = 102; # 08/16/2004 check production 5%
#$hist = "Hist898"; $Production = "DEV"; $Mode = 102; # 08/16/2004 reduce size of histograms,  check production 5%
#$hist = "Hist899"; $Production = "P04ii"; $Mode = 102; # 08/17/2004 reduce size of histograms,  check production 25%

#$hist = "Hist900"; $Production = "P04ii";# 08/22/2004 reduce size of histograms,  check production 5%
#$hist = "Hist901"; $Production = "P04ii";$STAR_LEVEL = "dev";# 08/23/2004 reduce size of histograms,  check production 5%
#$hist = "Hist902"; $Production = "P04ii"; $Mode = 102; # 08/24/2004 rcheck production 25%
#$hist = "Hist903"; $Production = "DEV"; $Mode = 102; # 08/24/2004 rcheck production 25%
#$hist = "Hist904"; $Production = "DEV"; $Mode = 102; # 08/25/2004 rcheck production 25%
#$hist = "Hist905"; $Production = "P04ii"; # 08/25/2004 rcheck production 25%
#$hist = "Hist906"; $Production = "P04ii";# 08/25/2004 check with root fles production 25%
#$hist = "Hist907"; $Production = "P04ig"; # 08/26/2004
#$hist = "Hist911"; $Production = "P04ij"; # 09/11/2004 check once more shift with root files
#$hist = "Hist912"; $Production = "P04ij"; # 09/12/2004 check once more shift with DB
#$hist = "Hist913"; $Production = "P04ii"; # 09/15/2004 new production, change dX calculation based on THelixTrack
#$hist = "Hist914"; $Production = "P04ii"; # 09/17/2004 new production, change dX calculation based on THelixTrack, use outerGeometry 10% 
#$hist = "Hist915"; $Production = "P04ii"; # 09/18/2004 new production, change dX calculation based on THelixTrack, use Geometry 10% 
#$hist = "Hist916"; $Production = "P04ii"; # 09/18/2004 new production, back to standard dX, use Geometry %10
#$hist = "Hist917"; $Production = "P04ii"; $STAR_LEVEL = "adev";# 09/18/2004
#$hist = "Hist918"; $Production = "P04ii"; $STAR_LEVEL = "SL04i";# 09/19/2004
#$hist = "Hist919"; $Production = "P04ii"; $macro = "dEdxD";# 09/19/2004 .DEV2 with ToF 20%
#$hist = "Hist920"; $Production = "P04ii"; $macro = "dEdx";# 09/20/2004 add saturation term to Bichsel 
#$hist = "Hist921"; $Production = "P04ii"; $STAR_LEVEL = "SL04i";# 09/21/2004 add saturation term to Bichsel 10%
#$hist = "Hist922"; $Production = "P04ii"; # 09/22/2004 new production, change dX calculation based on THelixTrack, no SecRow Correction 
#$hist = "Hist923"; $Production = "P04ii"; $disk = "data43";# 09/23/2004 old dX calculation based on StHelix
#$hist = "Hist924"; $Production = "P04ii";# 09/24/2004 new TpcLengthCorrections
#$hist = "Hist925"; $Production = "P04ii"; $disk = "data43";# 09/27/2004 cut edges
#$hist = "Hist926"; $Production = "P04ii"; $disk = "data43";# 09/28/2004 cut more edges, MIP histograms for TpcLength, use Outer geometry
#$hist = "Hist927"; $Production = "P04ij"; $STAR_LEVEL = "SL04j";  $macro = "dEdxj"; $disk = "data4*"; $Mode = 102;# 09/28/2004 check P04ij
#$hist = "Hist928"; $Production = "P04ij"; $disk = "data4*"; $Mode = 102;# 09/29/2004 check new tpcCorrection for 5% (outer geometry)
#$hist = "Hist929"; $Production = "P04ij"; $disk = "data4*";# 09/29/2004 check new tpcCorrection for 20% (outer geometry)
#$hist = "Hist930"; $Production = "P04ij"; $disk = "data4*";# 10/01/2004 fix bug with Phi/Theta, new TpcSecRowC, 10% (outer geometry)
#$hist = "Hist931"; $Production = "P04ij"; $disk = "data4*";# 10/02/2004  10% (inner + outer geometry)
#$hist = "Hist932"; $Production = "P04ij"; $STAR_LEVEL = "SL04j"; $disk = "data4*";# 10/05/2004  test production for full statistics
#$hist = "Hist933"; $Production = "P04ij"; $disk = "data4*";# 10/06/2004  10% (inner + outer geometry, fix bug with s)
#$hist = "Hist934"; $Production = "P04ij"; $disk = "data4*";# 10/06/2004  10% (inner + outer geometry, + ChargeCorrection)
#$hist = "Hist935"; $Production = "P04ij"; $disk = "data4*";# 10/10/2004  10% (inner + outer geometry, + no ChargeCorrection + adjustable pad separation)
#$hist = "Hist936"; $Production = "P04ij"; $disk = "data4*";# 10/11/2004  10% (inner + outer geometry s**3, + ChargeCorrection + adjustable pad separation)
#$hist = "Hist937"; $Production = "P04ij"; $disk = "data4*";# 10/12/2004  10% (inner + outer geometry s**3, + no ChargeCorrection + adjustable pad separation) add dCharge histos
#$hist = "Hist938"; $Production = "P04ij"; $disk = "data4*";# 10/12/2004  10% (inner geometry, + no ChargeCorrection + adjustable pad separation) add dCharge histos One TpcLengthCorrection from TpcLengthCorrectionB.20031120.000000.C  SecRowB.20031120.000000
#$hist = "Hist939"; $Production = "P04ij"; $disk = "data4*";# 10/13/2004  10% (inner geometry, + dCharge One TpcLengthCorrection from TpcLengthCorrectionB.20031120.000000.C  SecRowB.20031120.000000 + I70 for Outer)
#$hist = "Hist940"; $Production = "P04ij"; $disk = "data4*";# 10/13/2004   (inner geometry, + dCharge One TpcLengthCorrection from TpcLengthCorrectionB.20031120.000000.C  SecRowB.20031120.000000 + I70 for Outer)
#$hist = "Hist941"; $Production = "P04ij"; $disk = "data4*";# 10/20/2004   add Edge correction 10%
#$hist = "Hist942"; $Production = "P04ij"; $disk = "data4*";# 10/20/2004   add signed Edge correction 10%
#$hist = "Hist943"; $Production = "P04ik"; $disk = "data4*"; $STAR_LEVEL = "SL04k"; $Mode = 102;# 10/31/2004 check production 
#$hist = "Hist944"; $Production = "P04ik"; $disk = "data4*"; $STAR_LEVEL = "dev"; # 10/31/2004 check dev production 
#$hist = "Hist945"; $Production = "P04ik"; $disk = "data4*"; $STAR_LEVEL = "dev"; # 11/02/2004 check dev production, fit fitz correction
#$hist = "Hist946"; $Production = "P04ik"; $disk = "data*"; $STAR_LEVEL = "SL04k"; $Mode = 12;# 11/12/2004 recheck new production
#$hist = "Hist947"; $Production = "P03if"; $disk = "data*"; $Mode = 12;# 01/04/2005 check pp production 20% very bad dE/dx
#$hist = "Hist948"; $Production = "DEV"; $disk = "data47"; $Mode = 12; $select = "*";# 01/12/2005 check GridLeak correction
#$hist = "Hist949"; $Production = "DEV"; $disk = "data47"; $STAR_LEVEL = "dev"; $Mode = 12; $select = "*";# 01/18/2005 recheck GridLeak correction
#$hist = "Hist950"; $Production = "DEV"; $disk = "data*"; $STAR_LEVEL = "dev"; $Mode = 12; $select = "*"; $keep = 5;# 01/27/2005 recheck GridLeak correction 20%
#$hist = "Hist951"; $Production = "P04ik"; $disk = "data*"; $STAR_LEVEL = "dev"; $Mode = 12; $select = "*"; $keep = 100;# 01/27/2005 no GridLeak correction 1%
#$hist = "Hist952"; $Production = "P05ia_test"; $disk = "data42"; $STAR_LEVEL = "dev"; $Mode = 12; ;# 02/02/2005 Year 2 with new software
#$hist = "Hist953"; $Production = "P05ia_test"; $disk = "data42";;# 02/03/2005 Year 2, try to recalibrate
#$hist = "Hist954"; $Production = "P05ia_test"; $disk = "data40";;# 02/03/2005 Year 2, try to recalibrate
#$hist = "Hist955"; $Production = "P05ia_test"; $disk = "data40";;# 02/07/2005 Year 2, try to recalibrate with tpcAdcCorrection
#$hist = "Hist956"; $Production = "P05ia_test"; $disk = "data40";;# 02/11/2005 Year 2, new TpcSecRowB
#$hist = "Hist957"; $Production = "P05ia_test"; $disk = "data40";;# 02/11/2005 Year 2, new TpcSecRowB 
#                                                                  mv TpcSecRowB.20010924.root TpcSecRowB.20010924.120000.root
#$hist = "Hist961"; $Production = "P05ia_dedx"; $disk = "data*"; $year = 2004;# 02/09/2005 Year 4, try to recalibrate with tpcAdcCorrection
#                                                TpcAdcCorrectionB+TpcSecRowB+tpcPressureB+TpcdCharge+TpcEdge+TpcLengthCorrectionB
#                                                for whole run                                                for whole run
#$hist = "Hist962"; $Production = "P05ia_dedx"; $disk = "data*"; $year = 2004;# 02/11/2005 new TpcSecRowB
#$hist = "Hist963"; $Production = "P05ia_dedx"; $disk = "data*"; $year = 2004;# 02/11/2005 new TpcSecRowB with SecRow3C update
#$hist = "Hist964"; $Production = "P05ia_dedx"; $disk = "data*"; $year = 2004;# 02/12/2005 new TpcLengthCorrectionB
#$hist = "Hist965"; $Production = "P05ia_dedx"; $disk = "data*"; $year = 2004;# 02/12/2005 new TpcLengthCorrectionB + splitted SecRow3C **FINAL** Run 4
#$hist = "Hist966"; $Production = "P05ia_dedx"; $disk = "data*"; $year = 2004; $keep = 10;# 02/14/2005 check from DB 10% withotu Edge and dCharge
#$hist = "Hist967"; $Production = "P05ia_dedx"; $disk = "data*"; $year = 2004; $keep = 10;# 02/14/2005 check from DB 10%
#$hist = "Hist968"; $Production = "P05ia_dedx"; $disk = "data*"; $year = 2004; $keep = 10;# 02/15/2005 check from DB 10% unsetenv Calibrations_tpc
#$hist = "Hist969"; $Production = "P05ia_dedx"; $disk = "data*"; $year = 2004; $Mode = 12; $STAR_LEVEL = "dev";# 02/19/2005 check reproduction
# not run yet
#$hist = "Hist970"; $Production = "P05ic"; $disk = "data*"; $year = 2004; $Mode = 1002; $select ="*"; $maxFjob = 10;# $keep = 100;#  05/20/2005 compare with ToF, add tree
# ========================== 2005 Run V  =================================
# Year 5 CuCu
#$hist = "Hist001"; $Production = "P05id"; $disk = "data47"; $year = 2005; $Mode = 12; $STAR_LEVEL = "dev";# 04/25/2005 check status before calibration
#$hist = "Hist002"; $Production = "P05id"; $disk = "data47"; $year = 2005; ;# 04/25/2005 new TpcSecRowB, no TpcEdge & TpcdCharge
#$hist = "Hist003"; $Production = "P05id"; $disk = "data47"; $year = 2005; ;# 04/26/2005 new new TpcSecRowB, no TpcEdge & TpcdCharge
#$hist = "Hist004"; $Production = "P05id"; $disk = "data47"; $year = 2005;# 04/27/2005 +tpcPressureB
#$hist = "Hist005"; $Production = "P05id"; $disk = "data47"; $year = 2005;# 04/28/2005 + TrackLength + tpcGasTemperature
#$hist = "Hist006"; $Production = "P05id"; $disk = "data47"; $year = 2005; # 05/03/2005 + dXCorrection (one correction for both)
#$hist = "Hist007"; $Production = "P05id"; $disk = "data47"; $year = 2005; $keep = 5;# 05/02/2005 - dXCorrection, new TrackLength
#$hist = "Hist008"; $Production = "P05id"; $disk = "data47"; $year = 2005; # 05/04/2005 + dXCorrection (one correction for both, for Hist006 it did not work because StTpcdEdxCorrection)
#$hist = "Hist009"; $Production = "P05id"; $disk = "data47"; $year = 2005; # 05/04/2005 the same as Hist005 (checking)
#$hist = "Hist010"; $Production = "P05id"; $disk = "data47"; $year = 2005; $keep = 5;# 05/06/2005 revise  TpcSecRowB, add Edge + PhiD
#$hist = "Hist011"; $Production = "P05id"; $disk = "data47"; $year = 2005; $keep = 5;# 05/07/2005 - step back with StdEdxY2Maker 
#$hist = "Hist012"; $Production = "P05id"; $disk = "data47"; $year = 2005;# 05/07-08/2005 - step back with StdEdxY2Make, noEdge
#$hist = "Hist013"; $Production = "P05id"; $disk = "data47"; $year = 2005; $keep = 5;# 05/09/2005 - add Edge, use db
#$hist = "Hist014"; $Production = "P05id"; $disk = "data47"; $year = 2005; $keep = 5;# 05/10/2005 - fix St_tpcCorrection
#$hist = "Hist015"; $Production = "P05id"; $disk = "data47"; $year = 2005; $keep = 20; $STAR_LEVEL = "dev";# 05/11/2005 - test dev
#$hist = "Hist016"; $Production = "P05id"; $disk = "data47"; $keep = 5;# 05/11/2005 - Phi Edge = 085, add drift distance cut [20,207], new Bichsel
#$hist = "Hist017"; $Production = "P05id"; $disk = "data47"; $keep = 5;# 05/11/2005 - no Phi Edge, no drift distance cut [20,207], new Bichsel
#$hist = "Hist018"; $Production = "P05id"; $disk = "data47"; $STAR_LEVEL = "dev";# 05/13/2005 - final check
#$hist = "Hist021"; $Production = "P05ie_calib"; $disk = "data09"; $STAR_LEVEL = ".DEV2";# 06/17/2005 - pp check
#$hist = "Hist022"; $Production = "P05ie_calib"; $disk = "data09"; $STAR_LEVEL = ".DEV2";# 06/18/2005 - correct TpcSecRowB
#$hist = "Hist023"; $Production = "P05ie_calib"; $disk = "data09"; $STAR_LEVEL = ".DEV2";# 06/19/2005 - an other correction for TpcSecRowB
#$hist = "Hist024"; $Production = "P05ie_calib"; $disk = "data09"; $STAR_LEVEL = ".DEV2";# 06/20/2005 - an other correction for TpcSecRowB
#$hist = "Hist025"; $Production = "P05ie_ittf"; $disk = "data08"; $STAR_LEVEL = ".DEV2";# 06/21/2005 - +TpcLength; ittf (noSvt)
#$hist = "Hist026"; $Production = "P05ie_tpt"; $disk = "data09"; $STAR_LEVEL = ".DEV2";# 06/22/2005 - the same as above, but tpt(noSvt)
#$hist = "Hist027"; $Production = "P05ie_ittf"; $disk = "data08"; $STAR_LEVEL = ".DEV2";# 06/25/2005 - TpcSecRowB; ittf (noSvt)
#$hist = "Hist028"; $Production = "P05ie_ittf"; $disk = "data08"; $STAR_LEVEL = ".DEV2";# 06/26/2005 - +TpcLength; ittf (noSvt)
#$hist = "Hist029"; $Production = "P05ie_ittf"; $disk = "data08"; $STAR_LEVEL = ".DEV2";# 06/27/2005 - fix bug in TpcLength; ittf (noSvt)
#$hist = "Hist030"; $Production = "P05ie_ittf"; $disk = "data08"; $STAR_LEVEL = "dev";# 06/29/2005 - check with MySQL **FINAL** for Run V
#$hist = "Hist031"; $Production = "P05if_test"; $disk = "data09"; $STAR_LEVEL = "dev";# 08/17/2005 - check new production
#$hist = "Hist032"; $Production = "P05if_dedx"; $disk = "data43"; $STAR_LEVEL = "SL05f"; $select = "*2";# 01/11/2006 - check CuCu22 run V
# ========================== 2006 Run VI  =================================
# Run V, rerurn
#                                                             20050111.220000
#                                                             20050102.000000
#                                           60
#cuProductionHighTower_ReversedFullField    6029067 - 6046038 2005-01-30 04:42:50 - 2005-02-15 12:51:45                    6029067,                    6031106 - 6036004,                   6036014 - 6036021, 
#cuProductionMinBias_ReversedFullField      6029067 - 6046038 2005-01-30 04:42:50 - 2005-02-15 12:51:45 6014088 - 6029066,          6029068 - 6031039,                    6036005 - 6036013                    6036022 - 6036028
#
#                                                             20050216.000000
#cuProductionMinBias_FullField              6047017 - 6065058 2005-02-16 07:24:31 - 2005-03-07 01:01:38
#cuProductionHighTower_FullField            6047017 - 6065058 2005-02-16 07:24:31 - 2005-03-07 01:01:38
#cuProductionFPD_FullField                  6060055 - 6060078 2005-03-01 19:56:54 - 2005-03-01 23:49:27
#                                                             20050310.000000
#cu62productionMinBias_FullField            6069003 - 6081062 2005-03-10 07:17:44 - 2005-03-22 18:18:36
#	                                                     20050322.220000
#cu22ProductionMinBias_FullField            6081094 - 6083034 2005-03-22 22:53:08 - 2005-03-24 12:53:40 
#                                                             20050401.010000
#RunV201B

#$hist = "RunV201"; $NEvents = 2000; $disk = "data2*/"; $RECO = "reco/cu*/*FullField";  $Production = "/P19ic_calib"; $year = "/2005/*/"; $FILE = "st_"; $STAR_LEVEL = "TFG19g"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 04/24/19 check new production
#$hist = "RunV202"; $NEvents = 2000; $disk = "data2*/"; $RECO = "reco/cu*/*FullField";  $Production = "/P19ic_calib"; $year = "/2005/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/26/19 add ZDC3 histograms
#$hist = "RunV203"; $NEvents = 2000; $disk = "data2*/"; $RECO = "reco/cu*/*FullField";  $Production = "/P19ic_calib"; $year = "/2005/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/27/19 new TpcSecRowB and TpcRowQ
#$hist = "RunV204"; $NEvents = 2000; $disk = "data2*/"; $RECO = "reco/cu*/*FullField";  $Production = "/P19ic_calib"; $year = "/2005/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/28/19 reset TpcSecRowB and TpcRowQ to default, 2005 Distrotions option in dE.dx.C
#$hist = "RunV205"; $NEvents = 2000; $disk = "data2*/"; $RECO = "reco/cu*/*FullField";  $Production = "/P19ic_calib"; $year = "/2005/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/29/19 update TpcSecRowB
#$hist = "RunV206"; $NEvents = 2000; $disk = "data2*/"; $RECO = "reco/cu*/*FullField";  $Production = "/P19ic_calib"; $year = "/2005/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/29/19 update TpcLengthCorrrectionMDF bug in time stamp for TpcLengthCorrectionMDF
#$hist = "RunV207"; $NEvents = 2000; $disk = "data2*/"; $RECO = "reco/cu*/*FullField";  $Production = "/P19ic_calib"; $year = "/2005/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/29/19 update TpcLengthCorrrectionMDF
#$hist = "RunV208"; $NEvents = 2000; $disk = "data2*/"; $RECO = "reco/cu*/*FullField";  $Production = "/P19ic_calib"; $year = "/2005/*/"; $FILE = "st_"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/30/19 check in dev
#$hist = "RunV209"; $NEvents = 2000; $disk = "data2*/"; $RECO = "reco/cu*/*FullField";  $Production = "/P19ic_calib"; $year = "/2005/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/02/19 new tpcPressureB
#$hist = "RunV210"; $NEvents = 2000; $disk = "data2*/"; $RECO = "reco/cu*/*FullField";  $Production = "/P19ic_calib"; $year = "/2005/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/02/19 fix bug  tpcPressureB
# ========================== 2006 Run VI  =================================
### run VI (2006)
#$hist = "Hist101"; $disk = "data09"; $Production = "dev"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*";# 01/11/2006 - check CuCu22 run V
#              /star/data09/reco/ppProduction/FullField/dev/2006/096/7096012/st_physics_7096012_raw_1030006.event.root
#$hist = "Hist102"; $disk = "data*"; $Production = "P06id_calib"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*";# 07/01/2006 -  first pass days 073 - 129 => 096-156 (Gene has calibrated)
#$hist = "Hist103"; $disk = "data*"; $Production = "P06id_calib"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*";# 07/02/2006 - update SecRow3B from scratch 
#$hist = "Hist104"; $disk = "data*"; $Production = "P06id_calib"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 96; $maxDay = 156;# 07/03/2006 - use update SecRowB, turn off tpcGassTemperature, TpcLengthCorrectionB; TpcPhiDirection; TpcPressureB
#$hist = "Hist105"; $disk = "data*"; $Production = "P06id_calib"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 96; $maxDay = 156;# 07/03/2006 - use update SecRowB, turn off tpcGassTemperature, TpcLengthCorrectionB; TpcPhiDirection; TpcPressureB, use IO Geometry
#$hist = "Hist106"; $disk = "data*"; $Production = "P06id_calib"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 96; $maxDay = 156;# 07/12/2006 - use default for run V parameters
#$hist = "Hist107"; $disk = "data*"; $Production = "P06id_calib"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 96; $maxDay = 156;# 07/13/2006 - update SecRowB add Yellow and Blue bbc background histogram
#$hist = "Hist108"; $disk = "data*"; $Production = "P06id_calib"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 96; $maxDay = 156;# 07/18/2006 - split TpcSecRowB into 3 time periods
#$hist = "Hist109"; $disk = "data*"; $Production = "P06id_calib"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 96; $maxDay = 156;# 07/20/2006 - update TpcSecRowB for 3 time periods
#$hist = "Hist110"; $disk = "data*"; $Production = "P06id_calib"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 96; $maxDay = 156;# 07/24/2006 + TpcLengthCorrectionB
#$hist = "Hist111"; $disk = "data*"; $Production = "P06id_calib"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 96; $maxDay = 156;# 07/24/2006 + TpcLengthCorrectionB + add histograms for West and East
#$hist = "Hist112"; $disk = "data*"; $Production = "P06id_calib"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 96; $maxDay = 156;# 07/25/2006 + only one TpcLengthCorrectionB
# Active corrections: TpcAdcCorrectionB,tpcPressureB,TpcDriftDistOxygen,TpcZCorrectionB,tpcGasTemperature,TpcPhiDirection,TpcLengthCorrectionB
#$hist = "Hist113"; $disk = "data*"; $Production = "P06id_calib"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 96; $maxDay = 156;# 07/25/2006 + step back with TpcLengthCorrection, only one TpcSecRowB, add TpcZCorrectionB
#$hist = "Hist114"; $disk = "data*"; $Production = "P06id_calib"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 96; $maxDay = 156;# 07/26/2006 + step back with TpcLengthCorrection, only one TpcSecRowB, remove TpcPhiDirection, add TpcZCorrectionB
#$hist = "Hist115"; $disk = "data*"; $Production = "P06id_calib"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 96; $maxDay = 156;# 07/27/2006  split TpcSecRowB into 4 periods
#$hist = "Hist116"; $disk = "data*"; $Production = "P06id_calib"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 96; $maxDay = 156;# 07/28/2006  add two TpcLengthCorrectionB corrections
#$hist = "Hist117"; $disk = "data*"; $Production = "P06id_calib"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 96; $maxDay = 156;# 07/29/2006  fix npar in TpcZCorrectionB, put in DB, check what is in Db
#$hist = "Hist118"; $disk = "data*"; $Production = "P06id_calib"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 96; $maxDay = 156;# 07/31/2006  redo SecRow
#$hist = "Hist119"; $disk = "data*"; $Production = "P06id"; $year = "2006/*"; $STAR_LEVEL = "dev"; $Mode = 12; $select = "*0"; $minDay = 96; $maxDay = 156;# 08/03/2006  check JPsi production with old constatns
#$hist = "Hist120"; $disk = "data*"; $Production = "P06id_calib"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 96; $maxDay = 156;# 07/31/2006 double truncate mean, Anode currents histograms
#$hist = "Hist121"; $disk = "data*"; $Production = "P06id_calib"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 96; $maxDay = 156;# 08/05/2006 return back to old dE/dx calculation
#$hist = "Hist122"; $disk = "data*"; $Production = "P06id_calib"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 96; $maxDay = 156;# 08/07/2006 fix bug in TpcLengthCorrectionB.20060308.115801.C
#$hist = "Hist123"; $disk = "data*"; $Production = "P06id_calib"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 96; $maxDay = 156; $keep = 10;# 08/08/2006 test MySQL
#$hist = "Hist124"; $disk = "data*"; $Production = "P06id"; $year = "2006/*"; $STAR_LEVEL = "dev"; $Mode = 12; $select = "*0"; $minDay = 96; $maxDay = 156;# 08/11/2006  check JPsi production with old constatns
#$hist = "Hist125"; $disk = "data*"; $Production = "P06id_dedx"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 95; # 08/17/2006 
#$hist = "Hist126"; $disk = "data*"; $Production = "P06id_dedx"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 95; # 08/18/2006 redo TpcSecRowB for begin of Run VI , something happens with Sector 11 rows 1-8
#$hist = "Hist127"; $disk = "data*"; $Production = "P06id_dedx"; $year = "2006/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 95; # 08/18/2006 TpcLengthCorrection
#$hist = "Hist128"; $disk = "data*"; $Production = "P06id_dedx"; $year = "2006/*"; $STAR_LEVEL = "dev"; $select = "*"; $minDay = 0; $maxDay = 95; # 08/20/2006 check Db in dev  **FINAL** for Run VI
# ========================== 2007 Run VII  =================================
# Run VII (2007) /star/data24/reco/2007Production2/FullField/P07id_dedx/2007/095/8095063/
#                /star/data24/reco/*              /*        /P07id_dedx/2007/*  /*/*/st_physics*.event.root
#$hist = "RunVII00"; $disk = "data24"; $Production = "P07id_dedx"; $year = "2007/*"; $STAR_LEVEL = "dev"; $select = "*"; $minDay = 0; $maxDay = 142; $Mode = 102;# FF only, check pass, just check, do not correct dE/dx 08/27/07
#$hist = "RunVII01"; $disk = "data*"; $Production = "P07id_dedx"; $year = "2007/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142;# $keep = 10;# FF TpcSecRowB == 1,  08/28/07 
#$hist = "RunVII02"; $disk = "data*"; $Production = "P07id_dedx"; $year = "2007/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142;# $keep = 10;# FF new TpcSecRowB,  08/29/07 
#$hist = "RunVII03"; $disk = "data*"; $Production = "P07id_dedx"; $year = "2007/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 2;# FF new tpcPressureB,  08/30/07 
#$hist = "RunVII04"; $disk = "data*"; $Production = "P07id_dedx"; $year = "2007/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 2;# FF new update TpcSecRowB, remove TpcZCorrectionB,  08/30/07 
#$hist = "RunVII05"; $disk = "data*"; $Production = "P07id_dedx"; $year = "2007/*"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 2;# FF new update TpcSecRowB.04  08/30/07 
#$hist = "RunVII06"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 2;# 09/15/07 start over again
#$hist = "RunVII07"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; ;# 09/16/07 turn of Adc corrections
#$hist = "RunVII08"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; ;# 09/20/07 undershoot correction
#$hist = "RunVII09"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142;# $keep = 2;# 09/20/07 undershoot correction
#$hist = "RunVII10"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142;# $keep = 2;# 09/20/07 undershoot correction, fix bug
#$hist = "RunVII11"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142;# $keep = 2;# 09/21/07  +TpcSecRowB.20070321.000010.root
#$hist = "RunVII12"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142;# $keep = 2;# 09/22/07  +tpcPressureB.20070321.000011.C
#$hist = "RunVII13"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142;# $keep = 2;# 09/24/07 fix bug in undershoot correction (charge from wrong hit)  
#$hist = "RunVII14"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142;# $keep = 2;# 09/24/07 +TpcSecRowB.20070321.000013.root
#$hist = "RunVII15"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 5;# 09/25/07 step back to Pass 06 with undershoot correction and remove rounding correction
#$hist = "RunVII16"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 5;# 06/26/07 +TpcSecRowB.20070321.000015.root, add Histograms for dCharge = dQ/Q
#$hist = "RunVII17"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 5;# use charge instead of modified charge*bug is not use charge but modified charge), add limitation for dCharge histogram drift > 20 cm, use TpcSecRowB.20070321.000004.root
#$hist = "RunVII18"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 5;# use charge instead of modified charge, add limitation for dCharge histogram drift > 20 cm, use TpcSecRowB.20070321.000004.root
#$hist = "RunVII19"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 5;# start from very beginning
#$hist = "RunVII20"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 5;# start from very beginning
#$hist = "RunVII21"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 5;# add correction for undershoot, 
#$hist = "RunVII22"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 5;# +TpcSecRowB.20070321.000021
#$hist = "RunVII23"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 5;# +TpcrCharge.20070321.000022.C
#$hist = "RunVII24"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 5;# +TpcSecRowB.20070321.000023
#$hist = "RunVII25"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 5;# start from very beginning with Adc corrections
#$hist = "RunVII26"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 5;# +TpcSecRowB.20070321.000025.root
#$hist = "RunVII27"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 5;# - TpcdCharge.20070321.000020.C
#$hist = "RunVII28"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 5;# +TpcSecRowB.20070321.000027.root
#$hist = "RunVII29"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 5;# +Edge cut
#$hist = "RunVII30"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 5;# + TpcdCharge.20070321.000029.C
#$hist = "RunVII31"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 5;# + TpcSecRowB.20070321.000030.root
#$hist = "RunVII32"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 5;# + TpcdCharge.20070321.000031.C
#$hist = "RunVII33"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 0;# + TpcSecRowB.20070321.000032.root
#$hist = "RunVII34"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 5;# + tpcPressureB.20070321.000033.C
#$hist = "RunVII40"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 5;# start from RunVII03 +TpcSecRowB.20070321.000003.root
#$hist = "RunVII41"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 5;# start from RunVII03 +TpcSecRowB.20070321.000040.root
#$hist = "RunVII42"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*"; $minDay = 0; $maxDay = 142; $keep = 5;# start from RunVII03 +TpcLengthCorrectionB.20070321.000041.C
#$hist = "RunVII43"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "RF"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0;# 10/07/07 
#$hist = "RunVII44"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "RF"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0;# 10/07/07 RF
#$hist = "RunVII45"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "RF"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0;# 10/08/07 RF +TpcSecRowB.20070524.000044.root
#$hist = "RunVII46"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 2;# 10/08/07
#$hist = "RunVII47"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "RF"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 2;# 10/08/07
#$hist = "RunVII48"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2;# 10/12/07 check new StdEdxY2 
#$hist = "RunVII49"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2;# 10/17/07 an other check new StdEdxY2 
#$hist = "RunVII50"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "dEdx3"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2;# 10/18/07 an other check new StdEdxY2 fix bug in dimensions
#$hist = "RunVII51"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "RF"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2;# 10/18/07 an other check new StdEdxY2 fix bug in dimensions
#$hist = "RunVII52"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "RF"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".dev"; $select = "*";  $keep = 5;# 10/20/07 an other check new StdEdxY2 fix bug with TrackLength
#$hist = "RunVII53"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "RF"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5;# 10/20/07 an other check new StdEdxY2 fix bug with TrackLength
#$hist = "RunVII54"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "FF"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0;# 10/22/07 comapre dev wrt .DEV2
#$hist = "RunVII55"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "FF"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0;# 10/22/07 comapre dev wrt .DEV2
#$hist = "RunVII56"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "FF"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0;# 10/22/07 comapre dev wrt .DEV2 add EdgePad
#$hist = "RunVII57"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "FF"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0;# 10/23/07 move to dQ and rQ instead of dQ/Q and rQ/Q start from 1 TpcSecRowB.C
#$hist = "RunVII58"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "FF"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0;# 10/23/07 move to dQ and rQ (rescaled), add Edge hitograms, new TpcSecRowB.C
#$hist = "RunVII59"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "FF"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0;# 10/23/07 move to dQ and rQ (rescaled), add Edge hitograms, new TpcSecRowB.C, no edge cut => to define Edge
#$hist = "RunVII60"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "FF"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0;# 10/26/07 move to dQ and rQ (rescaled), add Edge hitograms, new TpcSecRowB.C, no edge cut => to define Edge, redefine edge from data but not from prediction --> strange results redo
#$hist = "RunVII61"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "FF"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2;# 10/26/07 move to dQ and rQ (rescaled), add Edge hitograms, new TpcSecRowB.C, no edge cut => to define Edge, redefine edge from data but not from prediction
#$hist = "RunVII62"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "FF"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2;# 10/27/07 move to dQ and rQ (rescaled), add Edge hitograms, new TpcSecRowB.C, no edge cut => to define Edge, redefine edge from data but not from prediction
#$hist = "RunVII63"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "FF"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0;# 10/28/07 edge cut
#$hist = "RunVII63"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "RF"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0;# 10/28/07 edge cut
#$hist = "RunVII64"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "RF"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0;# 10/28/07 add new TpcSecRowB correction(103)
#$hist = "RunVII64"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "FF"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0;# 10/28/07 add new TpcSecRowB correction(103)
#$hist = "RunVII65"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "FF"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2;# 10/30/07 add new TpcSecRowB correction(104) bug in StTpcdEdxCorrection
#$hist = "RunVII66"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "RF"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2;# 10/30/07 add new TpcSecRowB correction(104)
#$hist = "RunVII67"; $disk = "data48"; $RECO = "/calib/fisyak/"; $Production = "FF"; $year = ""; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2;# 10/31/07 add new TpcSecRowB correction(106)
# ========================== 2007 Run VII  =================================
#/star/data4*/reco/2007Production2/FullField/P07ie/2007/*/*
#/star/data4*/reco/2007Production2/FullField/P07ie/2007/*/*/st_physics*0.event.root
#/star/data48/reco/2007Production2/FullField/P07ie/2007/140/8140042/*0.event.root
#$hist = "RunVII68"; $disk = "data4*"; $RECO = "/reco/2007Production2/FullField/"; $Production = "P07ie"; $year = "2007/*/*/"; $FILE = "st_btag"; $STAR_LEVEL = "dev"; $select = "*0";  $keep = 0; $Mode = 102;# 01/07/08 test results of production
#$hist = "RunVII69"; $disk = "data4*"; $RECO = "/reco/2007Production2/FullField/"; $Production = "P07ie"; $year = "2007/*/*/"; $FILE = "st_btag"; $STAR_LEVEL = ".DEV2"; $select = "*0";  $keep = 0; $Mode = 102;# 01/07/08 test results of production
# ========================== 2008 Run VIII  =================================
#$hist = "RunVIII01"; $disk = "simu"; $RECO = "/fisyak/"; $Production = "production_dAu2008"; $year = ""; $FILE = "st_phys"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2;# 02/14/08 first try tpx
#$hist = "RunVIII02"; $disk = "data*"; $RECO = "/reco/ppProduction2008/ReversedFullField/"; $Production = "P08ic"; $year = "2008/*/*/"; $FILE = "st_fms"; $STAR_LEVEL = ".DEV2"; $select = "*0";  $keep = 0; $Mode = 2;# 06/16/08 
#$hist = "RunVIII80"; $disk = "data4*"; $RECO = "/reco/*/*/"; $Production = "P08ic"; $year = "2008/*/*/"; $FILE = "st_phys"; $STAR_LEVEL = ".DEV2"; $select = "*0";  $keep = 0; $Mode = 2;# 06/03/08 Patricia test 
#$hist = "RunVIII81"; $disk = "data4*"; $RECO = "/reco/*/*/"; $Production = "P08ic"; $year = "2008/*/*/"; $FILE = "st_phys"; $STAR_LEVEL = ".DEV2"; $select = "*0";  $keep = 0; $Mode = 2;# 06/22/08 add TpcSecRowB for pp from Patricia run
#$hist = "RunVIII82"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P08ic"; $year = "2008/*/*/"; $FILE = "st_phys"; $STAR_LEVEL = ".DEV2"; $select = "*0";  $keep = 0; $Mode = 2; # 06/26/08 redo starting from scratch pp and dAu 
#$hist = "RunVIII11"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P08ic"; $year = "2008/*/*/"; $FILE = "st_phys"; $STAR_LEVEL = ".DEV2"; $select = "*0";  $keep = 0; $Mode = 2; # 06/27/08 redo starting from scratch pp and dAu + new TpcSecRowB
#$hist = "RunVIII12"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P08ic"; $year = "2008/*/*/"; $FILE = "st_phys"; $STAR_LEVEL = ".DEV2"; $select = "*0";  $keep = 0; $Mode = 2; # 06/28/08 pp and dAu + new tpcPressureB
#$hist = "RunVIII13"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P08ic"; $year = "2008/*/*/"; $FILE = "st_phys"; $STAR_LEVEL = ".DEV2"; $select = "*0";  $keep = 0; $Mode = 2; # 06/29/08 pp and dAu + new TpcLengthCorrectionB + TpcEdge
#$hist = "RunVIII14"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P08ic"; $year = "2008/*/*/"; $FILE = "st_phys"; $STAR_LEVEL = ".DEV2"; $select = "*0";  $keep = 0; $Mode = 2; # 07/02/08 pp and dAu + redo TpcLengthCorrectionB
#$hist = "RunVIII15"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P08ic"; $year = "2008/*/*/"; $FILE = "st_phys"; $STAR_LEVEL = ".DEV2"; $select = "*0";  $keep = 0; $Mode = 2; # 07/03/08 pp and dAu + add dCor TpcLengthCorrectionB
#$hist = "RunVIII16"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P08ic"; $year = "2008/*/*/"; $FILE = "st_phys"; $STAR_LEVEL = ".DEV2"; $select = "*0";  $keep = 0; $Mode = 2; # 07/04/08 pp and dAu repeat RunVIII15
#$hist = "RunVIII17"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P08ic"; $year = "2008/*/*/"; $FILE = "st_phys"; $STAR_LEVEL = "dev"; $select = "*0";  $keep = 0; $Mode = 2; # 07/05/08 pp and dAu test in dev
#$hist = "RunVIII18"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P08ic"; $year = "2008/*/*/"; $FILE = "st_phys"; $STAR_LEVEL = ".DEV2"; $select = "*0";  $keep = 0; $Mode = 2; # 07/06/08 pp and dAu test in .DEV2 from DB
#$hist = "RunVIII19"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P08ic"; $year = "2008/*/*/"; $FILE = "st_phys"; $STAR_LEVEL = "dev"; $select = "*0";  $keep = 0; $Mode = 2; # 07/08/08 pp and dAu test in dev
#$hist = "RunVIII20"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P08ic"; $year = "2008/*/*/"; $FILE = "st_phys"; $STAR_LEVEL = ".DEV2"; $select = "*0";  $keep = 0; $Mode = 2; # 07/11/08 pp and dAu add TpcZCorrectionB (starting for RunVII18)
# ========================== 2009 Run IX  =================================
# /star/data09/reco/lowLuminosity2009/ReversedFullField/dev/2009/083/10083130/
#$hist = "RunIX01"; $disk = "data*"; $RECO = "/reco/lowLuminosity2009/*/"; $Production = "dev"; $year = "2009/*/*/"; $FILE = "st_phys"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 03/25/09 
#$hist = "RunIX02"; $disk = "data*"; $RECO = "/reco/lowLuminosity2009/*/"; $Production = "dev"; $year = "2009/*/*/"; $FILE = "st_phys"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 03/26/09 +TpcSecRowB
#$hist = "RunIX03"; $disk = "data*"; $RECO = "/reco/lowLuminosity2009/*/"; $Production = "dev"; $year = "2009/*/*/"; $FILE = "st_phys"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/03/09 +TpcLengthCorrectionB
#  /star/data26/reco/lowLuminosity2009/ReversedFullField/DEV/
#$hist = "RunIX04"; $disk = "data26"; $RECO = "/reco/low*/*/"; $Production = "DEV"; $year = "2009/*/*/"; $FILE = "st_phys"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/21/09 new sample
#$hist = "RunIX05"; $disk = "data26"; $RECO = "/reco/low*/*/"; $Production = "DEV"; $year = "2009/*/*/"; $FILE = "st_phys"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/22/09 + TpcSecRowB
#$hist = "RunIX06"; $disk = "data26"; $RECO = "/reco/low*/*/"; $Production = "DEV"; $year = "2009/*/*/"; $FILE = "st_phys"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/25/09 + TpcSecRowB take off Gain Volatage Correction
#$hist = "RunIX07"; $disk = "data26"; $RECO = "/reco/low*/*/"; $Production = "DEV"; $year = "2009/*/*/"; $FILE = "st_phys"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/26/09 + Correct Gain Volatage Correction, TpcSecRowB == 1
#$hist = "RunIX08"; $disk = "data26"; $RECO = "/reco/low*/*/"; $Production = "DEV"; $year = "2009/*/*/"; $FILE = "st_phys"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/27/09 + fix bug in Correct Gain Volatage Correction, TpcSecRowB == 1, new TpcAdcCorrectionB.20090301.000007.C
#$hist = "RunIX09"; $disk = "data26"; $RECO = "/reco/low*/*/"; $Production = "DEV"; $year = "2009/*/*/"; $FILE = "st_phys"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/27/09 + fix bug in Correct Gain Volatage Correction, TpcSecRowB == 1, new TpcAdcCorrectionB.20090301.000007.C + TpcSecRowB
#$hist = "RunIX10"; $disk = "data26"; $RECO = "/reco/low*/*/"; $Production = "DEV"; $year = "2009/*/*/"; $FILE = "st_phys"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/28/09 + run for all tracks (including globals)
#$hist = "RunIX11"; $disk = "data26"; $RECO = "/reco/low*/*/"; $Production = "DEV"; $year = "2009/*/*/"; $FILE = "st_phys"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/29/09 + new TpcSecRowB
#/star/data36/reco/pp2pp_VPDMB/FullField/P09ib_test/2009/*/*
# /star/data36/reco/pp2pp_Production2009/FullField/P09ib_test/2009/*/*/
#$hist = "RunIX12"; $disk = "data36"; $RECO = "/reco/pp2pp*/*/"; $Production = "P09ib_test"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 07/08/09 start
#$hist = "RunIX13"; $disk = "data36"; $RECO = "/reco/pp2pp*/*/"; $Production = "P09ib_test"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 07/08/09 add default tpcAnodeHV
#$hist = "RunIX14"; $disk = "data36"; $RECO = "/reco/pp2pp*/*/"; $Production = "P09ib_test"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 07/09/09 fix  tpcAnodeHV for pad row 13 
#$hist = "RunIX15"; $disk = "data36"; $RECO = "/reco/pp2pp*/*/"; $Production = "P09ib_test"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 07/09/09 fix  new TpcSecRowB
#$hist = "RunIX16"; $disk = "data36"; $RECO = "/reco/pp2pp*/*/"; $Production = "P09ib_test"; $year = "2009/*/*/"; $FILE = "st_minbias_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 07/14/09 only st_minbias
#$hist = "RunIX20"; $disk = "data56"; $RECO = "/reco/pp2pp*/*/"; $Production = "DEV"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/21/09 the first pass with Voltage Scan
#$hist = "RunIX21"; $disk = "data56"; $RECO = "/reco/pp2pp*/*/"; $Production = "DEV"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/25/09 use tpcAnodeHVavg
#$hist = "RunIX22"; $disk = "data56"; $RECO = "/reco/pp2pp*/*/"; $Production = "DEV"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/27/09 Voltage for row*sector
#$hist = "RunIX23"; $disk = "data56"; $RECO = "/reco/pp2pp*/*/"; $Production = "DEV"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 11/09/09 new tpcAnodeHVavg. Voltage for row
#$hist = "RunIX24"; $disk = "data56"; $RECO = "/reco/pp2pp*/*/"; $Production = "DEV"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 11/14/09 use  tpcAnodeHV. Voltage for row
#$hist = "RunIX25"; $disk = "data56"; $RECO = "/reco/pp2pp*/*/"; $Production = "DEV"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 11/15/09 new correction for Gas gain versus Voltage
#$hist = "RunIX26"; $disk = "data56"; $RECO = "/reco/pp2pp*/*/"; $Production = "DEV"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 11/16/09 reverse correction for Gas gain versus Voltage, use average Voltage
#$hist = "RunIX27"; $disk = "data56"; $RECO = "/reco/pp2pp*/*/"; $Production = "DEV"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 11/17/09 reduce size of Voltage histograms, use new TpcSecRowB
#$hist = "RunIX28"; $disk = "data56"; $RECO = "/reco/pp2pp*/*/"; $Production = "DEV"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 11/18/09 use new TpcSecRowB
#$hist = "RunIX29"; $disk = "data56"; $RECO = "/reco/pp2pp*/*/"; $Production = "DEV"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 11/20/09 use new TpcSecRowB
#my @listOfRuns = qw(10183008 10183009 10183011 10183012 10183013 10183014 10183015 10183016 10183017 10183018
#		    10183020 10183021 10183027 10183028 10183030 10183031 10183037 10183038 10183052 10183056
#		    10183058 10183059 10183071 10183072 10184004 10184005 10184008 10184009 10184010 10184011
#		    10184012 10184016 10184017 10184018 10184019 10184020 10184021 10184027 10184028 10184030
#		    10184031 10184032 10184033 10184034 10184052 10184053 10184054 10184068 10185001 10185004 
#		    10185005 10185006 10185013 10185014 10185018 10185019 10185020 10185023);
#my $listOfRuns = join '|', @listOfRuns;
#$hist = "RunIX30"; $disk = "data5*"; $RECO = "/reco/pp2pp*/*/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*050001";  $keep = 0; $Mode = 2; # 11/20/09 use new TpcSecRowB
#$hist = "RunIX31"; $disk = "data5*"; $RECO = "/reco/*/*/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 11/28/09 add AcCharge histograms
#/star/data5*/reco/pp2pp_Production2009/FullField/P09if/2009/*/*
# /star/data5*/reco/pp2pp_VPDMB/FullField/P09if/2009/*/*
# ========================== 2009 Run IX pp500  =================================
#$hist = "RunIX32"; $disk = "data*"; $RECO = "/reco/production2009_500*/ReversedFullField/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/02/09 the first pass, use only ADCcorrections, no primary tracks cut
#$hist = "RunIX33"; $disk = "data*"; $RECO = "/reco/production2009_500*/ReversedFullField/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/03/09, use primary tracks matched with primary vertex with numMatchesWithBEMC, new TpcSecRowB
#$hist = "RunIX34"; $disk = "data*"; $RECO = "/reco/production2009_500*/ReversedFullField/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/03/09, new TpcSecRowB
#$hist = "RunIX35"; $disk = "data*"; $RECO = "/reco/production2009_500*/ReversedFullField/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/04/09, new tpcPressureB
# ________________________________________________________________________________________________
#$hist = "RunIX36"; $disk = "data*"; $RECO = "/reco/production2009_500*/ReversedFullField/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/04/09, new TpcSecRowB
#$hist = "RunIX36B"; $disk = "data*"; $RECO = "/reco/production2009_500*/ReversedFullField/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/04/09, new TpcSecRowB, remove requirement for EMC
#$hist = "RunIX37"; $disk = "data*"; $RECO = "/reco/production2009_500*/ReversedFullField/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/04/09, C remove bad runs
#                 03/31/12:30:00-13:30:00  04/02/07:30:00-12:30:00 04/11/05:30:00-07:30:00 
#my @badruns = (); 
#my @badruns = qw(10090036-10090046        10092021 - 10092048  10101005-10101020);
#my @badruns = qw(10090037 10090038 10090040 10090042 10090046 10090047
#		  10092024 10092028 10092029 10092030 10092036 10092037
#		  10092040 10092042 10092046 10092047 10092048 10100006
#		  10100008 10100013 10100014 10100015 10100016 10100017
#		  10100021 10100028 10100029);
#$hist = "RunIX38"; $disk = "data*"; $RECO = "/reco/production2009_500*/ReversedFullField/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/05/09, C remove bad runs new TpcSecRowB
#my @badruns = qw(10083056 10090037 10090038 10090040 10090042 10090046
#		 10090047 10092024 10092028 10092029 10092030 10092036
#		 10092037 10092040 10092042 10092046 10092047 10092048
#		 10100006 10100008 10100013 10100014 10100015 10100016
#		 10100017 10100018 10100019 10100021 10100028 10100029 
#		 10101008 10101009);
#my @badruns = qw(10083056 10090037 10090038 10090040 10090042 10090046
#		 10090047 10092024 10092028 10092029 10092030 10092036
#		 10092037 10092040 10092042 10092046 10092047 10092048
#		 10100006 10100008 10100013 10100014 10100015 10100016
#		 10100017 10100021 10100028 10100029 10101008 10101009
#		 10101011 10101016 10101018 10101019); 
#$hist = "RunIX39"; $disk = "data*"; $RECO = "/reco/production2009_500*/ReversedFullField/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/05/09, C remove bad runs new TpcSecRowB, TpxZCorrection 
#$hist = "RunIX40"; $disk = "data*"; $RECO = "/reco/production2009_500*/ReversedFullField/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/06/09, new TpxZCorrection $hist = "RunIX40"; $disk = "data*"; $RECO = "/reco/production2009_500*/ReversedFullField/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/06/09, new TpxZCorrection 
#$hist = "RunIX41"; $disk = "data*"; $RECO = "/reco/production2009_500*/ReversedFullField/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/06/09, new Voltage Correction, use anodeHV (not avg)
#my @badruns = ();
#my @badruns = qw( 10083056 10090037 10090038 10090040 10090042 10090046 10090047 10092024 10092028 10092029 10092030 
#		  10092036 10092037 10092040 10092042 10092046 10092047 10092048 10094095 10094096 10094098 10094099 
#		  10095039 10095040 10095047 10095048 10095049 10095052 10096001 10096006 10096008 10096009 10096015 
#		  10096025 10096026 10096027 10097016 10097019 10097021 10097022 10097026 10097040 10097044 10097045 
#		  10097153 10098029 10098035 10098038 10098040 10098045 10098046 10099055 10099057 10099066 10099067 
#		  10099068 10099071 10099073 10099077 10100006 10100008 10100013 10100014 10100015 10100016 10100017 
#		  10100021 10100028 10100029 10101008 10101009 10101011 10101016 10101018 10101019);
#$hist = "RunIX42"; $disk = "data*"; $RECO = "/reco/production2009_500*/ReversedFullField/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/06/09, new Voltage Correction, use anodeHV (not avg)
#my @badruns = qw( 10090037 10090038 10090040 10090042 10092024 10092028 10092029 10092030 10092036 10092037 10092040
#		  10092042 10092046 10092047 10092048 10101008 10101009 10101011 10101016 10101018 10101019 10101074
#		  10101088); 
#$hist = "RunIX43"; $disk = "data*"; $RECO = "/reco/production2009_500*/ReversedFullField/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/08/09 Final pass for pp500 
#$hist = "RunIX44"; $disk = "data*"; $RECO = "/reco/production2009_500*/ReversedFullField/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; # 12/09/09 Final pass for pp500
#my @badruns = ();
# /star/data6*/reco/production2009_200G*/ReversedFullField/P09ig_calib/2009/*/*
#$hist = "RunIX45"; $disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; # 12/21/09 pp500+pp200
#$hist = "RunIX45"; $disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; # 12/21/09 pp500+pp200
#$hist = "RunIX46"; $disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/22/09 pp200 use tpcAnodeHVavg
#$hist = "RunIX46"; $disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/22/09 pp500+pp200
#my @badruns = qw( 10094095 10094096 10094098
#		 10095039 10095040 10095047 10095048 10095049 10095052 10096001 10096006 10096008 10096009 10096015
#		 10096025 10096026 10097016 10097021 10097022 10097026 10097040 10097045
#		 10097153 10098029 10098035 10098038 10098040 10099055 10099057 10099066 10099067
#		 10099068 10099071 10099073 10099077 10100006 10100013 10100014 10100015 10100017
#		 10100021 10100028 10100029
#		 10079079 10079081 10083052 10083056 10086043 10086046 10087035 10087041 10087088 10088024
#		 10088027 10088028 10088030 10088031 10090026 10090027 10090037 10090038 10090040 10090042
#		 10090046 10090047 10090100 10090108 10090109 10090111 10092024 10092028 10092029 10092030
#		 10092036 10092037 10092040 10092042 10092046 10092047 10092048 10093036 10094099 10096027
#		 10097019 10097044 10097045 10097153 10098045 10098046 10099078 10101008 10101009 10101011
#		 10101016 10101018 10101019 10102048 10135024 10138046 10138049 10139024);
#$hist = "RunIX47"; $disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/24/09 pp200 use new TpcSecRowB
#$hist = "RunIX47"; $disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/22/09 pp500 use new TpcSecRowB
#$hist = "RunIX48"; $disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/25/09 pp200 add new TpcSecRowB, remove TpcDriftDistOxygen, add tpcMethaneIn
#$hist = "RunIX48"; $disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/25/09 pp500 
#$hist = "RunIX49"; $disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/26/09 pp200 dropt all corrections
#$hist = "RunIX49"; $disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/26/09 pp500
#$hist = "RunIX50"; $disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/27/09 pp200 add TpcRowB
#$hist = "RunIX50"; $disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/27/09 pp500
#$hist = "RunIX51"; $disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/28/09 pp200 add new TpcRowQ
#$hist = "RunIX51"; $disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/28/09 pp500
#$hist = "RunIX52"; $disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/29/09 pp200 add Z- and Qcm-dependences
#$hist = "RunIX52"; $disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09if"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/29/09 pp500
# /star/data6*/reco/production2009_200G*/FullField/P09ig_calib2/2009/*/*/
#$hist = "RunIX52"; $disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib2"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/13/10 pp200 FF
# take off Qcm and Z corrections
#$hist = "RunIX53"; $disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/29/09 pp200 add Z- and Qcm-dependences
#$hist = "RunIX53"; $disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib2"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/13/10 pp200 FF
#$hist = "RunIX53"; $disk = "data*"; $RECO = "/reco/production2009_500Ge*/*/"; $Production = "P09if_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/29/09 pp500
# add new Z and ZDC corrections
#$hist = "RunIX54"; $disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/16/2010
#$hist = "RunIX54"; $disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib2"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/16/2010
#$hist = "RunIX54"; $disk = "data*"; $RECO = "/reco/production2009_500Ge*/*/"; $Production = "P09if_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/16/2010 pp500
# add remove ZDC corrections
#$hist = "RunIX55"; 
#$disk = "data*"; $RECO = "/reco/production2009_500Ge*/*/"; $Production = "P09if_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/17/2010 pp500
#$disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/17/2010
#$disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib2"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/17/2010
#$hist = "RunIX56";  # new TpcSecRowB correction for 200 GeV only
#$disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/18/2010
#$disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib2"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/18/2010
#$disk = "data*"; $RECO = "/reco/production2009_500Ge*/*/"; $Production = "P09if_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/17/2010 pp500
#$hist = "RunIX57";  # new TpcSecRowB correction for 200 GeV only
#$disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/20/2010
#$disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib2"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/20/2010
#$disk = "data*"; $RECO = "/reco/production2009_500Ge*/*/"; $Production = "P09if_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/17/2010 pp500
#$hist = "RunIX58";  # new TpcSecRowB +  TpcLength
#$disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/20/2010
#$disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib2"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/20/2010
#$disk = "data*"; $RECO = "/reco/production2009_500Ge*/*/"; $Production = "P09if_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/17/2010 pp500
#$hist = "RunIX59";  # new TpcSecRowB +  TpcLength + TpcDriftDistOxygen
#$disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/23/2010
#$disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib2"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/23/2010 500 GeV Final pass
#$disk = "data*"; $RECO = "/reco/production2009_500Ge*/*/"; $Production = "P09if_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/23/2010 pp500
#$hist = "RunIX60";  # new TpcLength 
#$NEvents = 10000; # test run
#$disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/25/2010
#$disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib2"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/25/2010#
#$disk = "data*"; $RECO = "/reco/production2009_500Ge*/*/"; $Production = "P09if_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/23/2010 pp500
#$hist = "RunIX61";  # new TpcSecRowB for pp500  
#$NEvents = 10000; # test run
#$disk = "data*"; $RECO = "/reco/production2009_500Ge*/*/"; $Production = "P09if_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/26/2010 pp500
#$hist = "RunIX62";  # new TpcSecRowB for pp500  ; Final for pp200
#$NEvents = 10000; # test run
#$disk = "data*"; $RECO = "/reco/production2009_500Ge*/*/"; $Production = "P09if_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/27/2010 pp500
#$disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/27/2010
#$disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib2"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/27/2010#
#$hist = "RunIX63";  # new TpcSecRowB for pp500  
#$NEvents = 10000; # test run
#$disk = "data*"; $RECO = "/reco/production2009_500Ge*/*/"; $Production = "P09if_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/27/2010 pp500
#$disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/27/2010
#$disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib2"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/27/2010#
#$hist = "RunIX64";  # new TpcLengthCorrection for pp500  
#$NEvents = 10000; # test run
#$disk = "data*"; $RECO = "/reco/production2009_500Ge*/*/"; $Production = "P09if_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/27/2010 pp500
#$disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/27/2010
#$disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib2"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/27/2010#
#$hist = "RunIX65";  # test run with tables moved in MySQL, zdvx is taken from daq file
#$NEvents = 5000; # test run
#$disk = "data*"; $RECO = "/reco/production2009_500Ge*/*/"; $Production = "P09if_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/16/2010 pp500
#$disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/16/2010
#$disk = "data*"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib2"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/16/2010#
#USATLAS test 
#$hist = "RunIX65";  # test run with tables moved in MySQL, zdvx is taken from daq file
#$NEvents = 5000; # test run
#$disk = "/usatlas/workarea/fisyak/dEdx"; $RECO = "/reco/production2009*/*/"; $Production = "P09ig_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/27/2010#
#$hist = "RunIX66";  # rerun with StTpcHitMaker::AfterBurner
#$NEvents = 9999; # test run
#$disk = "data5[6-8]"; $RECO = "/reco/production2009_200Ge*/*/"; $Production = "DEV_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 03/30/2010 pp200
#$hist = "RunIX67";  # add average current histograms
#$NEvents = 9999; # test run
#$disk = "data5[6-8]"; $RECO = "/reco/production2009_200Ge*/*/"; $Production = "DEV_calib"; $year = "2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/29/2010 pp200
# /star/data*/reco/production2009_200Gev_Single/FullField/P11id_tof_th*/2009/*/*/*.event.root
#$hist = "RunIX71"; $disk = "data*"; $RECO = "/reco/production2009_200Gev_Single/*/"; $Production = "P11id_tof_th*"; $year = "/2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/02/2012 pp200
#$hist = "RunIX72"; $disk = "data*"; $RECO = "/reco/production2009_200Gev_Single/*/"; $Production = "P11id_tof_th*"; $year = "/2009/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/24/2012 pp200 add tof selection
# ========================== 2010 Run X AuAu200  =================================
#my @badruns = ();
#$hist = "RunX01";  # 
#$NEvents = 5000; # 
#$disk = "data61"; $RECO = "/reco/AuAu200_production/*/"; $Production = "DEV_test"; $year = "2010/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 03/08/2010#
#$hist = "RunX02";  # with correct tpcAnodeHVAvg
#$NEvents = 999999999; # 
#$disk = "data61"; $RECO = "/reco/AuAu200_production/*/"; $Production = "DEV_test"; $year = "2010/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 03/15/2010#
#$hist = "RunX03"; # with AfterBurner
#$NEvents = 999999999; # 
#$disk = "data58"; $RECO = "/reco/AuAu200_production/*/"; $Production = "DEV_calib"; $year = "2010/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 03/30/2010#
#$hist = "RunX04"; # with hlt
#$NEvents = 999999999; # 
#$disk = "data6[6-7]"; $RECO = "/reco/AuAu200_production/*/"; $Production = "P10if_calib"; $year = "2010/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/13/2010#
#$hist = "RunX05"; # add average current histograms
#$NEvents = 999999999; # 
#$disk = "data6[6-7]"; $RECO = "/reco/AuAu200_production/*/"; $Production = "P10if_calib"; $year = "2010/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/29/2010#
# /star/data25/reco/AuAu39_production/ReversedFullField/P10ig_calib2/2010/107/11107082/st_physics_11107082_raw_2010001.event.root
#$hist = "RunX05"; # AuAu39
#$disk = "data*"; $RECO = "/reco/AuAu39_production/*/"; $Production = "P10ig_calib2"; $year = "2010/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/11/2010#
#$hist = "RunX06";
#$disk = "data*"; $RECO = "/reco/AuAu*production/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/24/2010#
# ________________________________________________________________________________________________
#$hist = "RunX07";
##$disk = "data*"; $RECO = "/reco/AuAu*production/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/30/2010# start from the begin, leave only Pressure Correction
#$disk = "data*"; $RECO = "/reco/LowLuminosity_2010/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/30/2010# start from the begin, leave only Pressure Correction
#$hist = "RunX08";
#$disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 06/01/2010# add TpcAvCurrent
#$hist = "RunX09";
#$disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 06/04/2010# add TpcSecRowB but keep single TpcRowQ
#$hist = "RunX10";
#$disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 06/14/2010# start with default TpcSecRowB and TpcRowQ, change binning
#$hist = "RunX11";
#$disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; # 06/16/2010# use TpcSecRowB and only one TpcRowQ
#$hist = "RunX12";
#$disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 06/17/2010# use TpcSecRowB and only one TpcRowQ, full statistics
#my @badruns = qw(11018053 11018054 11018056 11019009 11070053
#		 11070054 11070055 11070056 11070057 11071001
#		 11071002 11071003 11071006 11099069 11099070
#		 11099124 11100045 11100055 11101056 11101104
#		 11105011 11117072 11117094 11117102 11126005
#		 11127054 11127067
#		 11144055 11144056
#);
#$hist = "RunX13";
#$disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 06/25/2010# skip bad runs, switch off Av.Current correction.cut off prompt hits, full statistics, new Adc correction
#$hist = "RunX14";
#$disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; # 06/29/2010# fix bug in TpcdEdxCorrection (abs(zg)
#$hist = "RunX15";
#$disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 06/30/2010# new TpcSecRowB and TpcRowQ for whole run.
#$hist = "RunX16";
#$disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; # 07/05/2010# add TpcAvCurrent  1/2 statisitics
#$hist = "RunX17";
#$disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; # 07/08/2010# new TpcSecRowB  1/2 statisitics
#$hist = "RunX18";
#$disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 07/10/2010# step back to padd 15, TpcAvCurrent correction for each run period, full statisitics
#$hist = "RunX19";
#$disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 07/10/2011# add TpcSecRowB for each period, TpcAvCurrent correction for each run period, full statisitics
#$hist = "RunX20";
#$disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 07/17/2010# add TpcRowQ for each ru period, new TpcSecRowB
#$hist = "RunX21"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 07/23/2010# update TpcRowQ & TpcSecRowB, corrected tpcAnodeHVavg, add Voltage histograms versus sector and row
#$hist = "RunX22"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 07/26/2010# update TpcRowQ & TpcSecRowB, corrected tpcAnodeHVavg, fix Voltage histograms versus sector and row, switch off Average Current correction
#$hist = "RunX23"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 07/30/2010# update TpcRowQ & TpcSecRowB, update DB with tpcAnodeHVavg
#$hist = "RunX24"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 08/04/2010# update TpcRowQ & TpcSecRowB, update DB with tpcAnodeHVavg
#$hist = "RunX25"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 08/09/2010# update TpcRowQ & TpcSecRowB, update DB with tpcAnodeHVavg fix AuAu7
#$hist = "RunX26"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 08/12/2010# update TpcRowQ & TpcSecRowB, update DB with tpcAnodeHVavg fix AuAu7, add Zdc
#$hist = "RunX27"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; # 08/16/2010# update TpcRowQ & TpcSecRowB
#$hist = "RunX28"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; # 08/18/2010# remove Outer Voltage outliers, Add TpcZCorrectionB
#$hist = "RunX29"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 08/21/2010# add new TpcSecRow
#$hist = "RunX30"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 08/27/2010# add new TpcSecRow + cut on Z in TpcZCorrection
#$hist = "RunX31"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 08/31/2010# add new TpcSecRow + cut on Z in TpcZCorrection for each run period
#$hist = "RunX32"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 08/31/2010# add new TpcSecRow + cut on Z in TpcZCorrection for each run period, don't understand results for of Run31 (It looks like that Z correction does not work). Try gain.
#$hist = "RunX33"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 09/05/2010# add new TpcSecRow + cut on Z in TpcZCorrection for each run period, don't understand results for of Run31 (It looks like that Z correction does not work). Try gain.
#$hist = "RunX34"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10i"; $year = "2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 09/07/2010# check TpcLengthCorrectionB
#$hist = "RunX35"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10ij_dedx"; $year = "/2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/23/2010# recheck AuAu200 with constants in DB
#$hist = "RunX35"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "P10ij_dedx"; $year = "/2010/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/23/2010# recheck AuAu200 with constants in DB
#$hist = "RunX36"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "dotDEV2"; $year = ""; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/26/2010# update TpcSecRow and TpcRowQ
# ========================== 2011 Run XI AuAu200  =================================
#$hist = "RunXI01"; $disk = "institutions/bnl"; $RECO = "/fisyak/"; $Production = "Cosmic"; $year = "/2011/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 02/04/2011# Cosmics
#$hist = "RunXI02"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "dev"; $year = "/2011/038/120381??/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 02/08/2011# fast offline, runs with Inner Anode HV 1065 and 1100 V 
#$hist = "RunXI02"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "dev"; $year = "/2011/037/12037040/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 02/09/2011# fast offline, runs with Inner Anode HV 1135 V
#$hist = "RunXI02"; $disk = "data*"; $RECO = "/reco/*/*/"; $Production = "dev"; $year = "/2011/037/12037063/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 02/09/2011# fast offline, runs with Inner Anode HV 1135 V
#$hist = "RunXI03"; $disk = "data22"; $RECO = "/reco/TPC_Low_Luminosity/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 02/09/2011# fast offline, runs with Inner Anode HV 1135 V
#/star/data22/reco/pp500_production_2011/ReversedFullField/dev_calib/2011/*/*
#/star/data23/reco/pp500_production_2011/ReversedFullField/dev_calib/2011/*/*
#$hist = "RunXI04"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/16/2011# pp500 check new alignment
#$hist = "RunXI05"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/16/2011# reset TpcSecRowB,tpcPressureB,TpcLengthCorrectionB,tpcAvCurrent
#$hist = "RunXI06"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/17/2011# fix tpcGainCorrection in MySQL and rerun with Liang calibration
#$hist = "RunXI07"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/17/2011# start from zero
#$hist = "RunXI08"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/18/2011# new (102) TpcSecRowB and TpcRowQ
#$hist = "RunXI09"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/20/2011# new (108) TpcSecRowB and TpcRowQ
#$hist = "RunXI10"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/22/2011# new (109) tpcPressureB
# /star/data25/reco/AuAu19_production/ReversedFullField/P11ic_calib/2011/*/*
#$hist = "RunXI11"; $disk = "data25"; $RECO = "/reco/AuAu19_production/ReversedFullField/"; $Production = "P11ic_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 102; # 05/23/2011# default constants
#$hist = "RunXI12"; $disk = "data25"; $RECO = "/reco/AuAu19_production/ReversedFullField/"; $Production = "P11ic_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/23/2011# first iteration wrt pp500
#$hist = "RunXI13"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/24/2011# new TpcZDC correction
#$hist = "RunXI14"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/25/2011# new tpcWaterOut, TpcDriftDistOxygen, TpcSecRowB, TpcRowQ
#$hist = "RunXI15"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/26/2011# take out tpcWaterOut (something is wrong), update TpcDriftDistOxygen
# /star/data*/reco/AuAu19_production/ReversedFullField/P11ic_dedx/2011/*/*
#$hist = "RunXI16AuAu19"; $disk = "data*"; $RECO = "/reco/AuAu19_production/ReversedFullField/"; $Production = "P11ic_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/27/2011# first iteration
#$hist = "RunXI17pp500"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/27/2011 add TpcLengCorrectionB
#$hist = "RunXI18AuAu19"; $disk = "data*"; $RECO = "/reco/AuAu19_production/ReversedFullField/"; $Production = "P11ic_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/27/2011# first iteration repath because of wrong cint 
#$hist = "RunXI19AuAu19"; $disk = "data*"; $RECO = "/reco/AuAu19_production/ReversedFullField/"; $Production = "P11ic_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/28/2011# new TpcSecRow
#$hist = "RunXI20AuAu19"; $disk = "data*"; $RECO = "/reco/AuAu19_production/ReversedFullField/"; $Production = "P11ic_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/29/2011# correct TpcSecRow, TpcLength, TpcDriftDistOxygen, hope to be final.
#$hist = "RunXI21AuAu19"; $disk = "data*"; $RECO = "/reco/AuAu19_production/ReversedFullField/"; $Production = "P11ic_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; # 05/30/2011# check MySQL tables
#$hist = "RunXI22pp500"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; # 05/30/2011 check MySQL values
#$hist = "RunXI23pp500"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/31/2011 check MySQL values with Full statistics 
#$hist = "RunXI24AuAu19"; $disk = "data*"; $RECO = "/reco/AuAu19_production/ReversedFullField/"; $Production = "P11ic_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/31/2011# check MySQL tables with Full statistics 
#$hist = "RunXI25pp500"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/31/2011 check MySQL values with Full statistics 
#$hist = "RunXI26AuAu19"; $disk = "data*"; $RECO = "/reco/AuAu19_production/ReversedFullField/"; $Production = "P11ic_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/31/2011# check MySQL tables with Full statistics 
#__________ new repass with new TpcAdcCorrection _______________
#			 12038110 12038111 12038113 12038114 12038116
#			 12039012 12039036 12040057 12040074 12041007
#			 12042003 12042055 12042058 12042082 12043028
#			 12043089 12044049 12045019 12045022 12045024
#			 12045107 12045109 12045130 12045143 12045147
#			 12046004 12046108 12046109 12046112 12046113
#			 12046120 12046121 12046127 12047021 12047032
#			 12047045 12047072 12047073 12048009 12048039
#			 12048049 12048050 12049096 12049105 12050025
#			 12051017 12051048 12052004 12052006 12052009
#			 12052021 12052042 12053003 12053060 12053061
#			 12053071 12054004 12055039 12055041 12055060
#			 12055061 12055065 12055066 12055067 12056003
#			 12056025 12056042 12056048 12056054 12056059
#			 12056062 12056065 12056068 12056078 12056081
#			 12056083 12056086 12057003 12057024 12057032
#			 12057041 12057042 12057043 12057044 12058001
#			 12058019 12058020 12058025 12058060 12058062
#			 12059003 12059031 12059032 12059033 12059034
#			 12059062 12059063 12059065 12059066 12059067
#			 12059068 12059069 12059070 12059071 12059072
#			 12059077 12059078 12059079 12059080 12059082
#			 12059083 12059084 12060001 12060003 12060007
#			 12060016 12060062 12060070 12060071 12060078
#			 12061009 12061019 12061047 12061048 12061050
#			 12061055 12061058 12062023 12062039 12062040
#			 12063001 12063002 12063008 12064041 12064048
#			 12064058 12064059 12064060 12064061 12064062
#			 12064063 12064064 12064065 12064066 12064067
#			 12064068 12064069 12064070 12064071 12064073
#			 12064074 12064078 12064081 12064083 12065014
#			 12065016 12065038 12065051 12065052 12066003
#			 12066004 12066011 12066013 12066015 12066017
#			 12066019 12066020 12067002 12070002 12070005
#			 12071002 12071003 12071004 12072002 12073002
#			 12073004 12074027 12075004 12075015 12076003
#			 12076050 12076056 12076057 12076062 12077001
#			 12077003 12077004 12078003 12079003 12079004
#			 12079020 12079030 12079031 12079033 12079034
#			 12080005 12080052 12080053 12080054 12080055
#			 12080058 12080059 12080060 12080062 12080065
#			 12080066 12080067 12080068 12080069 12080070
#			 12080072 12080073 12081015 12081016 12081020
#			 12081029 12081039 12082012 12082014 12082028
#			 12082032 12082033 12082035 12082036 12083005
#			 12083009 12083010 12083025 12083030 12083058
#			 12084005 12084008 12084023 12084027 12084031
#			 12085005 12085022 12086008 12086010 12086013
#			 12086025 12086028 12086046 12087007 12087010
#			 12087057 12087076 12088033 12088090 12089014
#			 12089023 12089033 12089054 12089063 12089069
#			 12089070 12089071 12089072 12089073 12089077
#			 12089079 12089084 12090023 12090024 12090028
#			 12090061 12091025 12092010 12092027 12092028
#			 12092029 12093007 12093021 12093022 12093029
#			 12093046 12093048 12094002 12094008 12094028
#			 12094055 12094059 12095027 12095029 12095031
#			 12095037 12095064 12095067 12095068 12096004
#			 12096011 12096035 12096036 12096038 12097024
#			 12098017 12098036 12098051 12098053 12098054
#			 12098055 12099001 12099002 12099003 12099004
#			 12099005 12099006 12099007 12099008 12099009
#			 12099010 12099011 12099012 12099014 12099015
#			 12099016 12099037 12099038 12099039 12099045
#			 12099046 12099049 12100011 12100027 12101002
#			 12101004 12101009 12101010 12101012 12101013
#			 12101014 12101046 12101047 12101052 12101053
#			 12101055 12101059 12102004 12102008 12102009
#			 12102011 12102026 12102027 12103002 12103006
#			 12103008 12103030 12103036 12103040 12104001
#			 12104002 12104049 12104062 12104069 12104070
#			 12104074 12104075 12105018 12105066 12106016
#			 12106058 12106065 12106071 12106072 12106074
#			 12106075 12107004 12107005 12107006 12107012
#			 12107013 12107016 12107026 12107036 12107037
#			 12107039 12108002 12108003 12108020 12109006
#			 12109007 12109023 12109024 12109025 12110007
#  http://www.star.bnl.gov/protected/bulkcorr/yyang/tpc_anode_voltage/run11/pp500GeV/bad.list
#my @badruns   = qw (
#		     12038110 12038111 12038113 12038114 12047021
#		     12050025 12052021 12057035 12058001 12058019
#		     12059031 12059070 12059071 12059077 12059078
#		     12059079 12059080 12059082 12059083 12059084
#		     12060001 12060007 12060012 12064058 12064059
#		     12064060 12064061 12064062 12064063 12064064
#		     12064065 12064066 12064067 12064068 12064069
#		     12064070 12064071 12065016 12079030 12079031
#		     12079033 12080052 12080053 12080054 12080055
#		     12080058 12080059 12080062 12080064 12080066
#		     12080067 12080068 12080069 12080070 12081015
#		     12081016 12081020 12083058 12086046 12087056
#		     12088033 12093007 12098017 12099037 12099045
#		     12100027 12101009 12101013 12101014 12106071
#		     12106074 12107012 12107026 12107037 12107039
#		     12108020 
#		     12111027 12111028 12111030 12112014 12112053
#		     12112054 12112056 12112058 12112063 12112133
#		     12113016 12113032 12113037 12113038 12113039
#		     12113041 12113052 12113053 12113058 12114106
#		     12117038 12120047 12120060 12121055
#		  );
#$hist = "RunXI31AuAu19"; $disk = "data*"; $RECO = "/reco/AuAu19_production/ReversedFullField/"; $Production = "P11ic_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 06/02/2011 start from scratch
#$hist = "RunXI31pp500"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 06/02/2011 start from scratch
#$hist = "RunXI32AuAu19"; $disk = "data*"; $RECO = "/reco/AuAu19_production/ReversedFullField/"; $Production = "P11ic_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 06/03/2011 TpcSecRow
#$hist = "RunXI32pp500"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 06/03/2011 TpcSecRow
#$hist = "RunXI33AuAu19"; $disk = "data*"; $RECO = "/reco/AuAu19_production/ReversedFullField/"; $Production = "P11ic_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 06/06/2011 repass TpcSecRow
#$hist = "RunXI33pp500"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 06/06/2011 repass TpcSecRow
#$hist = "RunXI34AuAu19"; $disk = "data*"; $RECO = "/reco/AuAu19_production/ReversedFullField/"; $Production = "P11ic_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 06/08/11 new tpcPressureB
#$hist = "RunXI34pp500"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 06/08/11 new tpcPressureB
#$hist = "RunXI35AuAu19"; $disk = "data*"; $RECO = "/reco/AuAu19_production/ReversedFullField/"; $Production = "P11ic_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 06/10/11 new TpcSecRow
#$hist = "RunXI35pp500"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 06/10/11 new TpcSecRow
#$hist = "RunXI36AuAu19"; $disk = "data*"; $RECO = "/reco/AuAu19_production/ReversedFullField/"; $Production = "P11ic_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 06/11/11 new TpcZCorrection
#$hist = "RunXI36pp500"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 06/11/11 new TpcZCorrection
#$hist = "RunXI37AuAu19"; $disk = "data*"; $RECO = "/reco/AuAu19_production/ReversedFullField/"; $Production = "P11ic_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 06/12/11 new TpcZCorrection +TpcSecRow
#$hist = "RunXI37pp500"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 06/12/11 new TpcZCorrection + TpcSecRow
#$hist = "RunXI38AuAu19"; $disk = "data*"; $RECO = "/reco/AuAu19_production/ReversedFullField/"; $Production = "P11ic_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 06/14/11 new TpcLengthCorrectionB
#$hist = "RunXI38pp500"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 06/14/11 new TpcLengthCorrectionB + TpcZDC
#$hist = "RunXI39pp500"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 08/11/11 check Yi Guo caliibration
# /star/data11/reco/AuAu19_production/ReversedFullField/P11id_dedx/2011/113/12113029/st_physics_12113029_raw_2010001.event.root
#$hist = "RunXI39AuAu19"; $disk = "data*"; $RECO = "/reco/AuAu19_production/ReversedFullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 08/114/11 check calibration wrt new  production
#$hist = "RunXI40pp500"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 08/15/11 an other check Yi Guo caliibration
#$hist = "RunXI41pp500"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 08/15/11 modify parameterization for sigma
#$hist = "RunXI42AuAu27"; $disk = "data*"; $RECO = "/reco/AuAu27_production_2011/FullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 09/08/11 Check Yi Guo calibration which was put in MySQL
#$hist = "RunXI43pp500"; $disk = "data2[2|3]"; $RECO = "/reco/pp500_production_2011/ReversedFullField/"; $Production = "dev_calib"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 10; $Mode = 2; # 09/26/11 new TpcAvgCurrent
#$hist = "RunXI44AuAu200"; $disk = "data50"; $RECO = "/reco/AuAu200_production_2011/ReversedFullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/27/11 add log2dX in prediction
#$hist = "RunXI45AuAu27"; $disk = "data*"; $RECO = "/reco/AuAu27_production_2011/FullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 8/30 AuAu27 begin with AuAu 19.7 para SecRow correction
#$hist = "RunXI46AuAu27"; $disk = "data*"; $RECO = "/reco/AuAu27_production_2011/FullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 8/30 AuAu27 begin with AuAu 19.7 para SecRow correction split file 12175086
#$hist = "RunXI47AuAu27"; $disk = "data*"; $RECO = "/reco/AuAu27_production_2011/FullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 9/5 AuAu27 begin with AuAu 19.7 para SecRow recorrection split file 12175086
#$hist = "RunXI48AuAu27"; $disk = "data*"; $RECO = "/reco/AuAu27_production_2011/FullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 9/7 AuAu27 SecRow recorrection for 'before' sample split file 12175086 exclude bad runs
#$hist = "RunXI49AuAu27"; $disk = "data*"; $RECO = "/reco/AuAu27_production_2011/FullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 9/7 AuAu27 tracklength recorrection for 'before' sample split file 12175086 exclude bad runs
#$hist = "RunXI50AuAu27"; $disk = "data*"; $RECO = "/reco/AuAu27_production_2011/FullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 9/8 final check result from MySQL.
#$hist = "RunXI51AuAu200RFF"; $disk = "data*"; $RECO = "/reco/AuAu200_production_2011/ReversedFullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 9/23 pass0 for AuAu200GeV RFF.
#$hist = "RunXI52AuAu200RFF"; $disk = "data*"; $RECO = "/reco/AuAu200_production_2011/ReversedFullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 9/24 pass1 with SecRow correction for AuAu200GeV RFF.
#$hist = "RunXI53AuAu200RFF"; $disk = "data*"; $RECO = "/reco/AuAu200_production_2011/ReversedFullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 9/26 additional SecRow correction for AuAu200GeV RFF.
#$hist = "RunXI54AuAu200RFF"; $disk = "data*"; $RECO = "/reco/AuAu200_production_2011/ReversedFullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 9/26 pressure correction for AuAu200GeV RFF.
#$hist = "RunXI55AuAu200FullField"; $disk = "data*"; $RECO = "/reco/AuAu200_production_2011/FullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/03 pass0 for AuAu200GeV FF.
#$hist = "RunXI56AuAu200FF"; $disk = "data*"; $RECO = "/reco/AuAu200_production_2011/FullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/03 SecRow correction for AuAu200GeV FF.
#$hist = "RunXI57AuAu200FF"; $disk = "data*"; $RECO = "/reco/AuAu200_production_2011/FullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/03 Pressure correction for AuAu200GeV FF.
#$hist = "RunXI58AuAu200RFF"; $disk = "data*"; $RECO = "/reco/AuAu200_production_2011/ReversedFullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/06 Prepare AvCurrent and AcChange correction for AuAu200GeV RFF.
#$hist = "RunXI59AuAu200RFF"; $disk = "data*"; $RECO = "/reco/AuAu200_production_2011/ReversedFullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/07 AvCurrent correction for AuAu200GeV RFF.
#$hist = "RunXI60AuAu200RFF"; $disk = "data*"; $RECO = "/reco/AuAu200_production_2011/ReversedFullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/10 Tracklength correction for AuAu200GeV RFF.
#$hist = "RunXI61AuAu200RFF"; $disk = "data*"; $RECO = "/reco/AuAu200_production_2011/ReversedFullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; # 10/12 test for MySQL in dev for AuAu200GeV RFF.
#$hist = "RunXI62AuAu200FF"; $disk = "data*"; $RECO = "/reco/AuAu200_production_2011/FullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/14 TpcDriftDistOxygen correction for AuAu200GeV FF.
#$hist = "RunXI63AuAu200RFF"; $disk = "data*"; $RECO = "/reco/AuAu200_production_2011/ReversedFullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; # 10/14 TpcDriftDistOxygen correction for AuAu200GeV RFF.
#$hist = "RunXI64AuAu200FF"; $disk = "data*"; $RECO = "/reco/AuAu200_production_2011/FullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/17 Additional SecRow after TpcDriftDistOxygen correction for AuAu200GeV FF.
#$hist = "RunXI65AuAu200RFF"; $disk = "data*"; $RECO = "/reco/AuAu200_production_2011/ReversedFullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; # 10/17 Additional SecRow after TpcDriftDistOxygen correction for AuAu200GeV RFF.
#$hist = "RunXI66AuAu200FF"; $disk = "data*"; $RECO = "/reco/AuAu200_production_2011/FullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/18 TrackLength correction after TpcDriftDistOxygen correction for AuAu200GeV FF.
#$hist = "RunXI67AuAu200RFF"; $disk = "data*"; $RECO = "/reco/AuAu200_production_2011/ReversedFullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/18 TrackLength after TpcDriftDistOxygen correction for AuAu200GeV RFF.
#$hist = "RunXI68AuAu200FF"; $disk = "data*"; $RECO = "/reco/AuAu200_production_2011/FullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; # 10/20 check for MySQL AuAu200GeV FF.
#$hist = "RunXI69AuAu200RFF"; $disk = "data*"; $RECO = "/reco/AuAu200_production_2011/ReversedFullField/"; $Production = "P11id_dedx"; $year = "/2011/*/*/"; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; # 10/20 check for AuAu200GeV RFF.
# /star/data50/reco/AuAu200_production_2011/ReversedFullField/P11id_dedx/2011/*/*/*event.root Bad files no primary vertex
# /star/data90/reco/AuAu200_production/FullField/2010/reco_StiCA/st_physics_11003001_raw_3010001.event.root
#$hist = "RunX99AuAu200"; $disk = "data90"; $RECO = "/reco/AuAu200_production/FullField/"; $Production = "2010/reco_StiCA/"; $year = ""; $FILE = "st_[physics|hlt|W]"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/27/11 add log2dX in prediction
# ========================== 2011 Run XII fast offline  =================================
# pp200 2012-01-03 20:28:10 2012-03-13 03:27:20 DB 2012-02-07 10:06:00 ?
# pp500 2012-03-13 14:16:12 2012-04-23 11:23:37    2012-03-13 10:00:00
# UU193 2012-04-29 04:01:43 2012-05-16 19:21:53    2012-04-23 11:24:00
# CuAu  2012-05-18 04:01:02 2012-06-27 16:01:48
#$hist = "RunXII01pp200"; $disk = "data10"; $RECO = "/reco/pp200_production_2012/ReversedFullField/"; $Production = "dev"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = "eval"; $select = "*";  $keep = 0; $Mode = 2; # 03/09/12
#$hist = "RunXII02pp200"; $disk = "data09"; $RECO = "/reco/pp200_production_2012/ReversedFullField/"; $Production = "dev"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 03/09/12
#/star/data*/reco/UU_production_2012/ReversedFullField/P12ic_tof_dedx/2012/*/*
#$hist = "RunXII03UU200"; $disk = "data*"; $RECO = "/reco/UU_production_2012/ReversedFullField/"; $Production = "P12ic_tof_dedx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 03/09/12
#$hist = "RunXII04pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 03/25/13 reset all calibration to zero: TpcRowQ, TpcSecRowB, tpcPressureB, TpcDriftDistOxygen, TpcZCorrectionB, TpcZDC,TpcLengthCorrectionB, keep tpcGainCorrection  
#$hist = "RunXII05pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 03/26/13 first TpcRowQ, TpcSecRowB
#$hist = "RunXII06pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 03/26/13 add tpcPressureB
#$hist = "RunXII07pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 03/31/13 add TpcAvgCurrent
#$hist = "RunXII08pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/02/13 new TpcAvgCurrent
#$hist = "RunXII09pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/03/13 new limits for Accum. Charge histogram
#$hist = "RunXII10pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/04/13 set dX dependence to check Z dependence
#$hist = "RunXII11pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/05/13 use real adc, add <log2(dX)>
#$hist = "RunXII12pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/07/13, new TpcSecRow, and TpcZCorrection
#$hist = "RunXII13pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/07/13, new TpcSecRow, remove TpcZCorrection (?), add TpcAvCurrent
#$hist = "RunXII14pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/09/13, update TpcAvCurrent
#$hist = "RunXII15pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/11/13, update TpcZCorrection, TpcSecRow
#$hist = "RunXII16pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/12/13, update TpcZCorrection, TpcSecRow once again
#$hist = "RunXII17pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/14/13, update TpcCurrentCorrection
#$hist = "RunXII18pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/15/13, fix a bug in  TpcCurrentCorrection 16
#$hist = "RunXII19pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/15/13, fix an other bug in  TpcCurrentCorrection 16, still GOOD
#$hist = "RunXII20pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/16/13 add WateOut, adjust some tables.
#$hist = "RunXII21pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/17/13 take out tpcWaterOut (fake correction)
#$hist = "RunXII22pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/18/13 redo SecRow, still problem
#$hist = "RunXII23pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/19/13 step back to RunXII19pp510
#$hist = "RunXII24pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/19/13 still problem, modify StTpcdEdxCorrection for type = 300
#$hist = "RunXII25pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/20/13 update TpcLengthCorrectionMDF
#$hist = "RunXII26pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/22/13 TpcZCorrection
#$hist = "RunXII27pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/23/13 more TpcZCorrection
#$hist = "RunXII28pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; # 04/25/13 final pass in dev  
#$hist = "RunXII29pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 04/27/13 back to .DEV2
#$hist = "RunXII30pp510"; $disk = "data9*"; $RECO = "/reco/pp500_production_2012/ReversedFullField/"; $Production = "P13ia_dEdx"; $year = "/2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; # 04/27/13 recheck in dev after fixing schema evalution for TpcSecRowB 
#$hist = "RunXII01UU193"; $disk = "data16"; $RECO = "/calib/"; $Production = "2012"; $year = "/UU193/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/23/13 repass in .DEV2 using default calibration
#$hist = "RunXII02UU193"; $disk = "data16"; $RECO = "/calib/"; $Production = "2012"; $year = "/UU193/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/26/13 reset all corrections
#$hist = "RunXII03UU193"; $disk = "data16"; $RECO = "/calib/"; $Production = "2012"; $year = "/UU193/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/27/13 +TpcSecRowB & TpcRowQ
#$hist = "RunXII04UU193"; $disk = "data16"; $RECO = "/calib/"; $Production = "2012"; $year = "/UU193/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/27/13 +tpcPressureB
#$hist = "RunXII05UU193"; $disk = "data16"; $RECO = "/calib/"; $Production = "2012"; $year = "/UU193/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/29/13 + TpcAvCurrent
#$hist = "RunXII06UU193"; $disk = "data16"; $RECO = "/calib/"; $Production = "2012"; $year = "/UU193/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/29/13 + TpcdXCorrectionB
#$hist = "RunXII07UU193"; $disk = "data16"; $RECO = "/calib/"; $Production = "2012"; $year = "/UU193/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/29/13 + TpcSecRowB & TpcRowQ
#$hist = "RunXII08UU193"; $disk = "data16"; $RECO = "/calib/"; $Production = "2012"; $year = "/UU193/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/30/13 + TpcZCorrectionB
#$hist = "RunXII09UU193"; $disk = "data16"; $RECO = "/calib/"; $Production = "2012"; $year = "/UU193/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/31/13 + TpcSecRowB & TpcRowQ
#$hist = "RunXII10UU193"; $disk = "data16"; $RECO = "/calib/"; $Production = "2012"; $year = "/UU193/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 10/31/13 + TpcSecRowB & TpcRowQ
#$hist = "RunXII11UU193"; $disk = "data16"; $RECO = "/calib/"; $Production = "2012"; $year = "/UU193/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 11/01/13 +  TpcZCorrectionB + TpcdXCorrectionB
#$hist = "RunXII12UU193"; $disk = "data16"; $RECO = "/TPC/"; $Production = "2012"; $year = "/UU193/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 11/01/13 + TpcSecRowB & TpcRowQ 
#$hist = "RunXII13UU193"; $disk = "data16"; $RECO = "/TPC/"; $Production = "2012"; $year = "/UU193/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 11/01/13 + TpcZCorrectionB$hist = "RunXII13UU193"; $disk = "data16"; $RECO = "/TPC/"; $Production = "2012"; $year = "/UU193/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 11/01/13 + TpcZCorrectionB
#$hist = "RunXII14UU193"; $disk = "data16"; $RECO = "/TPC/"; $Production = "2012"; $year = "/UU193/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 11/02/13 + TpcSecRowB & TpcRowQ 
#$hist = "RunXII15UU193"; $disk = "data16"; $RECO = "/TPC/"; $Production = "2012"; $year = "/UU193/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 11/03/13 + TpcLengthCorrectionMDF
#$hist = "RunXII16UU193"; $disk = "data16"; $RECO = "/TPC/"; $Production = "2012"; $year = "/UU193/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 11/04/13 + correct TpcLengthCorrectionMDF
#$hist = "RunXII17UU193"; $disk = "data15"; $RECO = "/TPC/"; $Production = "2012"; $year = "/UU193/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 11/07/13 V0CrossCheck
#$hist = "RunXII18UU193"; $disk = "data16"; $RECO = "/TPC/"; $Production = "2012"; $year = "/UU193/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 11/08/13 + check constants in MySQL
#$hist = "RunXII19UU193"; $disk = "data16"; $RECO = "/TPC/"; $Production = "2012"; $year = "/UU193/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 11/11/13 V0CrossCheck
#$hist = "RunXII20UU193"; $disk = "data16"; $RECO = "/TPC/"; $Production = "2012"; $year = "/UU193/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 11/15/13 new histograms
#$hist = "RunXII21UU193"; $disk = "data16"; $RECO = "/TPC/"; $Production = "2012"; $year = "/UU193/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 11/15/13 fix unique key
#$hist = "RunXII22UU193"; $disk = "data16"; $RECO = "/TPC/"; $Production = "2012"; $year = "/UU193/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 11/21/13 new dX calculations
#$hist = "RunXII23UU193"; $disk = "data16"; $RECO = "/TPC/"; $Production = "2012"; $year = "/UU193/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 11/22/13 fix bug in TpcHitMover 
#$hist = "RunXII01AlAu200"; $disk = "data9*"; $RECO = "/reco/cuAu_production_2012/ReversedFullField"; $Production = "/P15ic_TOF_dEdx/"; $year = "2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/07/2015 the first check
#$hist = "RunXII02AlAu200"; $disk = "data9*"; $RECO = "/reco/cuAu_production_2012/ReversedFullField"; $Production = "/P15ic_TOF_dEdx/"; $year = "2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/07/2015 TpcSecRowB
#$hist = "RunXII03AlAu200"; $disk = "data9*"; $RECO = "/reco/cuAu_production_2012/ReversedFullField"; $Production = "/P15ic_TOF_dEdx/"; $year = "2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 05/09/15 TpcLengthCorrectionMDF.20120515.120002.C
#$hist = "RunXII04AlAu200"; $disk = "data9*"; $RECO = "/reco/cuAu_production_2012/ReversedFullField"; $Production = "/P15ic_TOF_dEdx/"; $year = "2012/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; # 05/11/15 test with dev 
# ========================== 2013 Run XIII =================================
#$hist = "RunXIII01pp500p1"; $disk = "subsys"; $RECO = "/tpc/"; $Production = "2013"; $year = "/pp500/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/29/13 pass with ~400 files before filtering, default constants
#$hist = "RunXIII02pp500p1"; $disk = "subsys"; $RECO = "/tpc/"; $Production = "2013"; $year = "/pp500/Filter/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/29/13 pass with ~400 files before filtering, default constants
#$hist = "RunXIII03pp500p1"; $disk = "subsys"; $RECO = "/tpc/"; $Production = "2013"; $year = "/pp500/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 12/31/13 pass with filtering, reset all constants, still missing ~300 runs
#$hist = "RunXIII04pp500p1"; $disk = "subsys"; $RECO = "/tpc/"; $Production = "2013"; $year = "/pp500/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/01/14 +TpcSecRowB
#$hist = "RunXIII05pp500p1"; $disk = "subsys"; $RECO = "/tpc/"; $Production = "2013"; $year = "/pp500/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/01/14 +tpcPressureB
#$hist = "RunXIII06pp500p1"; $disk = "subsys"; $RECO = "/tpc/"; $Production = "2013"; $year = "/pp500/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/02/14 +TpcZCorrectionB
#$hist = "RunXIII07pp500p1"; $disk = "subsys"; $RECO = "/tpc/"; $Production = "2013"; $year = "/pp500/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/02/14 +TpcCurrentCorrection
#$hist = "RunXIII08pp500p1"; $disk = "subsys"; $RECO = "/tpc/"; $Production = "2013"; $year = "/pp500/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/03/14 +TpcSecRowB
#$hist = "RunXIII09pp500p1"; $disk = "subsys"; $RECO = "/tpc/"; $Production = "2013"; $year = "/pp500/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/04/14 +tpcGainCorrection
#$hist = "RunXIII10pp500p1"; $disk = "subsys"; $RECO = "/tpc/"; $Production = "2013"; $year = "/pp500/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/04/14 +tpcPressureB
#$hist = "RunXIII11pp500p1"; $disk = "subsys"; $RECO = "/tpc/"; $Production = "2013"; $year = "/pp500/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/05/14 + TpcZCorrectionB
#$hist = "RunXIII12pp500p1"; $disk = "subsys"; $RECO = "/tpc/"; $Production = "2013"; $year = "/pp500/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/05/14 + TpcSecRowB + TpcCurrentCorrection
#$hist = "RunXIII13pp500p1"; $disk = "subsys"; $RECO = "/tpc/"; $Production = "2013"; $year = "/pp500/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/06/14 + TpcSecRowB
#$hist = "RunXIII14pp500p1"; $disk = "subsys"; $RECO = "/tpc/"; $Production = "2013"; $year = "/pp500/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/06/14 + TpcZCorrectionB + TpcLengthCorrectionMDF
#$hist = "RunXIII15pp500p1"; $disk = "subsys"; $RECO = "/tpc/"; $Production = "2013"; $year = "/pp500/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/07/14 +  TpcSecRowB
#$hist = "RunXIII16pp500p1dev"; $disk = "subsys"; $RECO = "/tpc/"; $Production = "2013"; $year = "/pp500/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/08/14 +  TpcSecRowB
#$hist = "RunXIII17pp500p1"; $disk = "subsys"; $RECO = "/tpc/"; $Production = "2013"; $year = "/pp500/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/09/14 +  test MySQL
#$hist = "RunXIII18pp500p1"; $disk = "subsys"; $RECO = "/tpc/"; $Production = "2013"; $year = "/pp500/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; # 01/11/14 + reset TpcDriftDistOxygen  test MySQL
#$hist = "RunXIII19pp500p1"; $disk = "subsys"; $RECO = "/tpc/"; $Production = "2013"; $year = "/pp500.eval/"; $FILE = "st_physics"; $STAR_LEVEL = "eval"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 01/14/14 + recheck in eval
# ========================== 2014 Run XIV =================================
#trigger                       begin               end 		   
#all                           2014-02-13 12:28:52 2014-07-06 10:57:09
#production_15GeV_2014         2014-02-15 21:58:43 2014-03-11 11:47:38
#production_15GeV_2014_hft     2014-02-22 20:56:02 2014-03-04 21:39:08
#AuAu_200_production_2014      2014-03-15 19:03:09 
#AuAu_200_production_high_2014 2014-03-29 18:50:28 2014-06-16 07:49:16
#AuAu_200_production_mid_2014  2014-04-05 03:28:30 2014-06-16 10:56:35
#AuHe3_production_2014         2014-06-20 03:00:59 2014-07-01 05:20:44

#$hist = "RunXIV00AuAu15"; $disk = "subsys"; $RECO = "/tpc/"; $Production = "2014"; $year = "/AuAu15/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 03/06/14 + check what is going on 
#$hist = "RunXIVAuAu15mtd"; $disk = "subsys"; $RECO = "/tpc/"; $Production = "2014"; $year = "/AuAu15/"; $FILE = "st_mtd"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 03/06/14 + check what is going on 
#$hist = "RunXIV01AuAu15"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 03/25/14  AuAu15 the first pass
#$hist = "RunXIV02AuAu15"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 03/30/14  AuAu15 reset all calibration
#$hist = "RunXIV03AuAu15Old"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 04/04/14  TpcSecRowB
#$hist = "RunXIV04AuAu15Old"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 04/05/14  TpcSecRowB
#$hist = "RunXIV05AuAu15Old"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 04/05/14  tpcPressureB
#$hist = "RunXIV06AuAu15Old"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15B/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 04/05/14  tpcPressureB$hist = "RunXIV05AuAu15Old"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 04/05/14  +TpcZCorrectionB
#$hist = "RunXIV07AuAu15New"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15B/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 04/05/14  tpcPressureB$hist = "RunXIV05AuAu15Old"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 04/05/14  +TpcZCorrectionB +RL5 TpcSecRowB
#$hist = "RunXIV08AuAu15Old"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15B/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 04/07/14  +TpcSecRowB
#$hist = "RunXIV09AuAu15Old"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15B/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 04/07/14  + TpcLengthCorrectionMDF mistyped time stamp 
#$hist = "RunXIV10AuAu15Old"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15B/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 04/08/14  + rerun with fixed TpcLengthCorrectionMDF mtime stamp 
#$hist = "RunXIV11AuAu15Old"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15B/"; $FILE = "st_physics"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 04/10/14 recheck in dev with MySQL in dev does not work
#$hist = "RunXIV12AuAu15Old"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15B/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 04/11/14 recheck in dev with MySQL
#$hist = "RunXIV13AuAu15new"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15B/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 04/14/14 TpcSecRowB RL5 from old 12
#$hist = "RunXIV14AuAu15new"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15B/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 04/14/14 TpcSecRowB RL5 from old 12 (5 LandauZ functions)
#$hist = "RunXIV15AuAu15new"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15B/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 04/14/14 TpcSecRowB RL5 from old 12 + SecRow RL5 (PASS 14) correction
#$hist = "RunXIV16AuAu15new"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15B/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 04/18/14 TpcZ correction
#$hist = "RunXIV17AuAu15new"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15B/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 04/20/14 new SecRow correction
#$hist = "RunXIV19AuAu15new"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15B/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 04/21/14 we reset Sector Row calibration and try to do this again
#$hist = "RunXIV20AuAu15new"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15B/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 04/22/14 Sector Row correction
#$hist = "RunXIV21AuAu15new"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15B/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 04/23/14 second Sector Row correction
#$hist = "RunXIV22AuAu15new"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15B/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 04/26/14 second Sector Row correction
#$hist = "RunXIV23AuAu15new"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15B/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 04/27/14 TpcZCorrection bug in TpcZCorrection, rerun
#$hist = "RunXIV24AuAu15new"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15B/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 04/27/14 TpcZCorrection
#$hist = "RunXIV25AuAu15new"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15B/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 05/01/14 Sector Row correction
#$hist = "RunXIV26AuAu15new"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15B/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 05/03/14 Sector Row correction
#$hist = "RunXIV27AuAu15new"; $disk = "/gpfs01/star/scratch/fisyak"; $RECO = "/reco/"; $Production = "2014"; $year = "/AuAu15B/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 05/04/14 TpcLengthCorrection
#$hist = "RunXIII19pp500p2"; $disk = "data9*"; $RECO = "/reco/pp500_production_2013/ReversedFullField/"; $Production = "P14ig_dEdx/2013/*/"; $year = ""; $FILE = "/st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 01/14/14 +
# /star/data*/reco/*/ReversedFullField/P14ii_TOF_dEdx/2014/*/*/*.event.root
# /star/data*/reco/*/ReversedFullField/P14ii_TOF_dEdx/2014/*/*/st_physics*.event.root
#$hist = "RunXIV30AuAu15new"; $disk = "data*"; $RECO = "/reco/*/ReversedFullField"; $Production = "/P14ii_TOF_dEdx"; $year = "/2014/*/*/"; $FILE = "st_hlt"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 12/10/14 check old calibration
#$hist = "RunXIV31AuAu15new"; $disk = "data*"; $RECO = "/reco/*/ReversedFullField"; $Production = "/P14ii_TOF_dEdx"; $year = "/2014/*/*/"; $FILE = "st_hlt"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 12/11/14 new TpcSecRowB
#$hist = "RunXIV32AuAu15"; $disk = "data*"; $RECO = "/reco/production_15GeV_2014/ReversedFullField"; $Production = "/P14ii_TOF_dEdx"; $year = "/2014/*/*/"; $FILE = "st_hlt"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 12/13/14 new TpcSecRowB from RL fit
#$hist = "RunXIV33AuAu15"; $disk = "data*"; $RECO = "/reco/production_15GeV_2014/ReversedFullField"; $Production = "/P14ii_TOF_dEdx"; $year = "/2014/*/*/"; $FILE = "st_hlt"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 12/14/14 new TpcSecRowB from RL fit
# RL fit does now work. sigma(mu) in SecRow is increased => 2% =>6 % ?
# step back to old scheme (33 => 31). Remove versions 31and 32
#$hist = "RunXIV34AuAu15"; $disk = "data*"; $RECO = "/reco/production_15GeV_2014/ReversedFullField"; $Production = "/P14ii_TOF_dEdx"; $year = "/2014/*/*/"; $FILE = "st_hlt"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 12/15/14 TpcSecRowB from GF (31) fit, take off TpcZCorrectionB
#$hist = "RunXIV35AuAu15"; $disk = "data*"; $RECO = "/reco/production_15GeV_2014/ReversedFullField"; $Production = "/P14ii_TOF_dEdx"; $year = "/2014/*/*/"; $FILE = "st_hlt"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 12/15/14 TpcZCorrectionB
#$hist = "RunXIV36AuAu15"; $disk = "data*"; $RECO = "/reco/production_15GeV_2014/ReversedFullField"; $Production = "/P14ii_TOF_dEdx"; $year = "/2014/*/*/"; $FILE = "st_hlt"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 12/16/14 TpcSecRowB
#$hist = "RunXIV37AuAu15"; $disk = "data*"; $RECO = "/reco/production_15GeV_2014/ReversedFullField"; $Production = "/P14ii_TOF_dEdx"; $year = "/2014/*/*/"; $FILE = "st_hlt"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 12/17/14 TpcSecRowB + TpcZCorrectionB + TpcLengthCorrectionMDF
#$hist = "RunXIV38AuAu15"; $disk = "data*"; $RECO = "/reco/production_15GeV_2014/ReversedFullField"; $Production = "/P14ii_TOF_dEdx"; $year = "/2014/*/*/"; $FILE = "st_hlt"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 12/17/14 test with dev
# /star/data97/reco/AuAu_200_production_2014/ReversedFullField/P15ib_HFT/2014/089/15089045/st_physics_adc_15089045_raw_1500005.event.root
# /star/data9*/reco/reco/AuAu_200_production_*2014/ReversedFullField/P15ib_HFT/2014/*/*/st_physics_adc*.event.root
#$hist = "RunXIV41AuAu200"; $disk = "data9*"; $RECO = "/reco/AuAu_200_production_*2014/ReversedFullField"; $Production = "/P15ib_HFT"; $year = "/2014/*/*/"; $FILE = "st_*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 01/29/15 the first test, No TPC at all
#$hist = "RunXIV42AuAu200"; $disk = "data9*"; $RECO = "/reco/AuAu_200_production_*/*"; $Production = "/P15ib_dEdx"; $year = "/2014/*/*/"; $FILE = "st_*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 02/25/15 the first test, with Db values fom AuAu15
#$hist = "RunXIV43AuAu200"; $NEvents = 500; $disk = "data9*"; $RECO = "/reco/AuAu_200_production_*/*"; $Production = "/P15ib_dEdx"; $year = "/2014/*/*/"; $FILE = "st_*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 02/27/15 update TpcSecRowB, add CorrX,OSpaceZ2,OGridLeak3D to chain
#$hist = "RunXIV44AuAu200"; $NEvents = 500; $disk = "data9*"; $RECO = "/reco/AuAu_200_production_*/*"; $Production = "/P15ib_dEdx"; $year = "/2014/*/*/"; $FILE = "st_*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 02/28/15 update TpcSecRowB, add CorrX,OSpaceZ2,OGridLeak3D to chain, use opt and reduce no.event to 500
#$hist = "RunXIV45AuAu200"; $NEvents = 500; $disk = "data9*"; $RECO = "/reco/AuAu_200_production_*/*"; $Production = "/P15ib_dEdx"; $year = "/2014/*/*/"; $FILE = "st_*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 02/28/15 update TpcSecRowB, add CorrX,OSpaceZ2,OGridLeak3D to chain, use opt and reduce no.event to 500
#$hist = "RunXIV46AuAu200"; $NEvents = 500; $disk = "data9*"; $RECO = "/reco/AuAu_200_production_*/*"; $Production = "/P15ib_dEdx"; $year = "/2014/*/*/"; $FILE = "st_*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 03/01/15 update TpcZCorrectionB
#$hist = "RunXIV47AuAu200"; $NEvents = 500; $disk = "data9*"; $RECO = "/reco/AuAu_200_production_*/*"; $Production = "/P15ib_dEdx"; $year = "/2014/*/*/"; $FILE = "st_*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 03/01/15 update TpcRowQ with log(Qcm) for each row
#$hist = "RunXIV48AuAu200"; $NEvents = 500; $disk = "data9*"; $RECO = "/reco/AuAu_200_production_*/*"; $Production = "/P15ib_dEdx"; $year = "/2014/*/*/"; $FILE = "st_*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 03/02/15 tpcPressureB & TpcCurrentCorrection
#$hist = "RunXIV49AuAu200"; $NEvents = 500; $disk = "data9*"; $RECO = "/reco/AuAu_200_production_*/*"; $Production = "/P15ib_dEdx"; $year = "/2014/*/*/"; $FILE = "st_*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 03/02/15 TpcRowQ
#$hist = "RunXIV50AuAu200"; $NEvents = 500; $disk = "data9*"; $RECO = "/reco/AuAu_200_production_*/*"; $Production = "/P15ib_dEdx"; $year = "/2014/*/*/"; $FILE = "st_*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 03/03/15 fix bug in TpcRowQ
#$hist = "RunXIV51AuAu200"; $NEvents = 500; $disk = "data9*"; $RECO = "/reco/AuAu_200_production_*/*"; $Production = "/P15ib_dEdx"; $year = "/2014/*/*/"; $FILE = "st_*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 03/04/15 fix step back to vers. 46
#$hist = "RunXIV52AuAu200"; $NEvents = 500; $disk = "data9*"; $RECO = "/reco/AuAu_200_production_*/*"; $Production = "/P15ib*"; $year = "/2014/*/*/"; $FILE = "st_*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 03/04/15 TpcLengthCorrectionMDF, use tof data
#$hist = "RunXIV53AuAu200"; $NEvents = 200; $disk = "data9*"; $RECO = "/reco/AuAu_200_production_*/*"; $Production = "/P15ib*"; $year = "/2014/*/*/"; $FILE = "st_*"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 03/05/15 check in dev with calibration from MySQL 
#$hist = "RunXIV54AuAu200"; $NEvents = 200; $disk = "data9*"; $RECO = "/reco/AuAu_200_production_*/*"; $Production = "/P15ib*"; $year = "/2014/*/*/"; $FILE = "st_*"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 03/06/15 recheck in dev with recompiled StdEdxY2Maker from .DEV2
#$hist = "RunXIV55AuAu200"; $NEvents = 500; $disk = "data9*"; $RECO = "/reco/AuAu_200_production_*/*"; $Production = "/P15ib*"; $year = "/2014/*/*/"; $FILE = "st_*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 03/06/15 require rank > 0 for primary vertex
#$hist = "RunXIV56AuAu200"; $NEvents = 500; $disk = "data9*"; $RECO = "/reco/AuAu_200_production_*/*"; $Production = "/P15ib*"; $year = "/2014/*/*/"; $FILE = "st_*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 03/07/15 update TpcSecRowB and TpcRowQ
#$hist = "RunXIV57AuAu200"; $NEvents = 500; $disk = "data9*"; $RECO = "/reco/AuAu_200_production_*/*"; $Production = "/P15ib*"; $year = "/2014/*/*/"; $FILE = "st_*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 03/09/15 update TpcZCorrectionB and TpcLengthCoorectionMDF
#$hist = "RunXIV58AuAu200"; $NEvents = 500; $disk = "data9*"; $RECO = "/reco/AuAu_200_production_*/*"; $Production = "/P15ib*"; $year = "/2014/*/*/"; $FILE = "st_*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 03/10/15 update TpcSecRowB and TpcRowQ
#$hist = "RunXIV59AuAu200"; $NEvents = 200; $disk = "data9*"; $RECO = "/reco/AuAu_200_production_*/*"; $Production = "/P15ib*"; $year = "/2014/*/*/"; $FILE = "st_*"; $STAR_LEVEL = "SL15c"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 03/10/15 check with wrt SL15c
#$hist = "RunXIV60AuAu200"; $NEvents = 5000; $disk = "data9*"; $RECO = "/reco/AuAu_200_production_*/*"; $Production = "/P15ib*"; $year = "/2014/*/*/"; $FILE = "st_*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 03/12/15 check TFile saving
#$hist = "RunXIV60AuAu200"; $NEvents = 5000; $disk = "data9*"; $RECO = "/reco/AuAu_200_production_low*/*"; $Production = "/P15ib*"; $year = "/2014/*/*/"; $FILE = "st_*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 03/12/15 check TFile saving
# /star/data9[6-7]/reco/cuAu_production_2012/ReversedFullField/P15ic_TOF_dEdx/2012/*/*

# ========================== 2015 Run XV =================================
# Trigger     |     start                    | end			
# All         |     2015-01-14 13:46:13 GMT  | 2015-06-25		
# pp200_Long  |     2015-02-11 01:26:00 GMT  | 2015-04-02 03:51:09 GMT
# pp200_trans |     2015-03-06 02:31:45 GMT  | 2015-04-03 13:02:20 GMT
# pp200_Long2 |     2015-04-04 01:01:23 GMT  | 2015-04-27 10:35:51 GMT
# pp200_Long3 |     2015-04-16 15:54:54 GMT  | 2015-04-16 19:16:33 GMT
# pAu200      |     2015-05-04 20:52:03 GMT  | 2015-06-10 20:40:30 GMT
# fixedTarget |     2015-05-20 13:51:02 GMT  | 2015-05-20 15:57:29 GMT 
# pAl200LowLum|     2015-06-09 06:30:45 GMT  | 2015-06-12 22:42:17 GMT
# pAl200      |     2015-06-09 06:30:45 GMT  |
# fixedTarget |     2015-06-18 17:19:01 GMT  | 2015-06-18 18:31:31 GMT
# pAl200      |     2015-06-18 22:00:34 GMT  | 2015-06-21 03:17:21 GMT
#$hist = "RunXV01pp200"; $NEvents = 5000; $disk = "data*"; $RECO = "/reco/production_pp200trans_2015*/*"; $Production = "/dev"; $year = "/2015/*/*/"; $FILE = "st_physics_16*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 04/01/15 check
#/gpfs01/star/subsys-tpc/fisyak/reco/2015/FixedTarget/*.event.root
#$hist = "RunXV02FixedTarget"; $NEvents = 5000; $disk = "subsys/tpc/fisyak"; $RECO = ""; $Production = "/reco"; $year = "/2015/FixedTarget/"; $FILE = "st_physics_16*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 06/15/15 The first check
#$hist = "RunXV03FixedTarget"; $NEvents = 50000; $disk = "subsys/tpc/fisyak"; $RECO = ""; $Production = "/reco"; $year = "/2015/FixedTargetNoGL/"; $FILE = "st_physics_16*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 07/09/15 ReRun with no SC&GL corrections, check
#$hist = "RunXV04FixedTarget"; $NEvents = 50000; $disk = "subsys/tpc/fisyak"; $RECO = ""; $Production = "/reco"; $year = "/2015/FixedTargetNoGL/"; $FILE = "st_physics_16*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 07/10/15 ReRun with no SC&GL corrections, reset TpcSecRowB & TpcRowQ
#$hist = "RunXV05FixedTarget"; $NEvents = 50000; $disk = "subsys/tpc/fisyak"; $RECO = ""; $Production = "/reco"; $year = "/2015/FixedTargetNoGL/"; $FILE = "st_physics_16*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 07/11/15 1-st TpcSecRowB & TpcRowQ
#$hist = "RunXV05FixedTarget"; $NEvents = 50000; $disk = "subsys/tpc/fisyak"; $RECO = ""; $Production = "/reco"; $year = "/2015/FixedTargetNoGL/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 07/12/15 1-st TpcSecRowB & TpcRowQ
#$hist = "RunXV06FixedTarget"; $NEvents = 50000; $disk = "subsys/tpc/fisyak"; $RECO = ""; $Production = "/reco"; $year = "/2015/FixedTargetNoGL/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 07/12/15 1-st TpcSecRowB & TpcRowQ
#$hist = "RunXV07FixedTarget"; $NEvents = 50000; $disk = "subsys/tpc/fisyak"; $RECO = ""; $Production = "/reco"; $year = "/2015/FixedTargetNoGL/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 07/13/15 2-nd TpcSecRowB & TpcRowQ
#$hist = "RunXV08FixedTarget"; $NEvents = 50000; $disk = "subsys/tpc/fisyak"; $RECO = ""; $Production = "/reco"; $year = "/2015/FixedTargetNoGL/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 07/13/15 3rd TpcSecRowB & TpcRowQ
#$hist = "RunXV09FixedTarget"; $NEvents = 50000; $disk = "subsys/tpc/fisyak"; $RECO = ""; $Production = "/reco"; $year = "/2015/FixedTargetNoGL/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 07/14/15 move to old SecRow
#$hist = "RunXV10FixTagVFM"; $NEvents = 50000; $disk = "subsys/tpc/fisyak"; $RECO = ""; $Production = "/reco"; $year = "/2015/FixedTargetGLMinuit/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 07/16/15 reset TpcRowQ & TpcSecRowB
#$hist = "RunXV11FixTagKFV"; $NEvents = 50000; $disk = "subsys/tpc/fisyak"; $RECO = ""; $Production = "/reco"; $year = "/2015/FixedTargetGLKF/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 07/16/15 recheck
#$hist = "RunXV12FixTagVFM"; $NEvents = 50000; $disk = "subsys/tpc/fisyak"; $RECO = ""; $Production = "/reco"; $year = "/2015/FixedTargetGLMinuit/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 07/16/15 old TpcRowQ & TpcSecRowB
#$hist = "RunXV13FixTagKFV"; $NEvents = 50000; $disk = "subsys/tpc/fisyak"; $RECO = ""; $Production = "/reco"; $year = "/2015/FixedTargetGLKF/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 07/16/15 old TpcRowQ & TpcSecRowB
#$hist = "RunXV14FixTagNoGLt"; $NEvents = 50000; $disk = "subsys/tpc/fisyak"; $RECO = ""; $Production = "/reco"; $year = "/2015/FixedTargetNoGL/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 07/16/15 old TpcRowQ & TpcSecRowB
#RunXV10FixTagVFM : #sigma(@76cm) =  8.47%
#RunXV10FixTagVFM : #sigma(@76cm) =  8.41%
#RunXV11FixTagKFV : #sigma(@76cm) =  8.01%
#RunXV11FixTagKFV : #sigma(@76cm) =  7.80%
#RunXV12FixTagVFM : #sigma(@76cm) =  7.66%
#RunXV12FixTagVFM : #sigma(@76cm) =  7.53%
#RunXV13FixTagKFV : #sigma(@76cm) =  7.58% 
#RunXV13FixTagKFV : #sigma(@76cm) =  7.44%
#RunXV14FixTagNoGL : #sigma(@76cm) =  7.53%
#RunXV14FixTagNoGL : #sigma(@76cm) =  7.47%
#$hist = "RunXV15FixTagNoGL"; $NEvents = 50000; $disk = "subsys/tpc/fisyak"; $RECO = ""; $Production = "/reco"; $year = "/2015/FixedTargetNoGL/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 07/19/15 use RunXV14FixTagNoGL
#$hist = "RunXV16FixTagNoGL"; $NEvents = 50000; $disk = "subsys/tpc/fisyak"; $RECO = ""; $Production = "/reco"; $year = "/2015/FixedTargetNoGL/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 07/20/15 2nd iteration with SecRow 
#$hist = "RunXV17FixTagNoGL"; $NEvents = 50000; $disk = "subsys/tpc/fisyak"; $RECO = ""; $Production = "/reco"; $year = "/2015/FixedTargetNoGL/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 07/21/15 2nd iteration with SecRow started from RunXV15
#$hist = "RunXV18FixTagNoGL"; $NEvents = 50000; $disk = "subsys/tpc/fisyak"; $RECO = ""; $Production = "/reco"; $year = "/2015/FixedTargetNoGL/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 07/21/15 3rd iteration with SecRow started from RunXV15
#$hist = "RunXV19FixTagNoGL"; $NEvents = 50000; $disk = "subsys/tpc/fisyak"; $RECO = ""; $Production = "/reco"; $year = "/2015/FixedTargetNoGL/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 07/22/15 4-th iteration with SecRow started from RunXV15
#$hist = "RunXV21FixTagKFV"; $NEvents = 50000; $disk = "subsys/tpc/fisyak"; $RECO = ""; $Production = "/reco"; $year = "/2015/FixedTargetGLKF/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 07/22/15 start from RunXV13FixTagKFV, 1st iteration (20)
#$hist = "RunXV22FixTagKFV"; $NEvents = 50000; $disk = "subsys/tpc/fisyak"; $RECO = ""; $Production = "/reco"; $year = "/2015/FixedTargetGLKF/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 07/23/15 start from RunXV13FixTagKFV, 2nd iteration (20)
#$hist = "RunXV23FixTagKFV"; $NEvents = 50000; $disk = "subsys/tpc/fisyak"; $RECO = ""; $Production = "/reco"; $year = "/2015/FixedTargetGLKF/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 07/23/15 start from RunXV13FixTagKFV, 3rd iteration (20)
#$hist = "RunXV24FixTagKFV"; $NEvents = 50000; $disk = "subsys/tpc/fisyak"; $RECO = ""; $Production = "/reco"; $year = "/2015/FixedTargetGLKF/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 07/23/15 start from RunXV13FixTagKFV, use TpcLengthCorrectionMDF.20150520.135123.C
# Tables used from RunXIV 
# TpcRowQ:    20141220/100
# TpcSecRowB: 20141220/100
# TpcDriftDistOxygen: 20141220/100
# TpcZCorrectionB:    -"-
# TpcZDC:             -"-
# TpcLengthCorrectionB: -"-
# TpcLengthCorrectionMDF: -"-
# tpcGainCorrection: tpcGainCorrection.y2015.C
#my @badruns = qw();   # reset bad rauns 12/05/15
#		  16043086 16043089 16043091 16043092 16043096 16043097 16043098 16043103 16043105 16043106
#		  16043111 16044004 16044023 16044027 16044028 16044029 16044030 16044031 16044033 16044036
#		  16044037 16044044 16044045 16044133 16044138 16044139 16045001 16045047 16045048 16045049
#		  16045054 16045055 16045056 16045067 16045068 16045070 16045102 16045103 16045104 16045105
#		  16045106 16045108 16045109 16045110 16045112 16045113 16045114 16045115 16045118 16045119
#		  16045120 16046012 16046013 16046014 16046015 16046016 16046017 16046018 16046019 16046020
#		  16046021 16046038 16046039 16046040 16046041 16046042 16046043 16046044 16046045 16046046
#		  16046048 16046049 16046050 16046057 16046058 16046059 16046061 16046062 16046064 16046065
#		  16046066 16046067 16046073 16046074 16046075 16046076 16046077 16046078 16046080 16046081
#		  16046082 16046083 16047122 16047124 16047125 16047126 16047131 16047136 16047137
#		  16047138 16048001 16048002 16048003 16048004 16048015 16048016 16048017 16048018 16048019
#		  16048022 16048023 16048024 16048025 16048026 16048027 16048028 16048115 16048116 16048117
#		  16048118 16048119 16048120 16048121 16048122 16048125 16048126 16048127 16048128 16049023
#		  16050041 16050043 16050048 16050049 16050050 16050051 16050052 16050053 16050054 16050066
#		  16050070 16050071 16050072 16050073 16050075 16050076 16062048 16080007 16081004 16108032
#	       );
#$hist = "RunXV01pp200"; $NEvents = 50000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 09/04/15 first pass with old constants 
#$hist = "RunXV02pp200"; $NEvents = 50000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 09/06/15 update TpcSecRowB & TpcRowQ
#$hist = "RunXV03pp200"; $NEvents = 50000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 09/07/15 2nd update TpcSecRowB & TpcRowQ, tpcPresureB
#$hist = "RunXV04pp200"; $NEvents = 50000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 09/08/15 3rd update TpcSecRowB & TpcRowQ
#$hist = "RunXV05pp200"; $NEvents = 50000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 09/09/15 TpcCurrentCorrection
#$hist = "RunXV06pp200"; $NEvents = 50000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 09/10/15  TpcSecRowB & TpcRowQ
#$hist = "RunXV07pp200"; $NEvents = 50000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 09/11/15  TpcSecRowB & TpcRowQ
#$hist = "RunXV08pp200"; $NEvents = 50000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 09/12/15  TpcSecRowB & TpcRowQ
#$hist = "RunXV09pp200"; $NEvents = 50000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 09/13/15  TpcLengthCorrectionMDF
#$hist = "RunXV10pp200"; $NEvents = 50000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 09/14/15  TpcLengthCorrectionB bug 
#$hist = "RunXV11pp200"; $NEvents = 50000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 09/15/15  TpcLengthCorrectionB
#$hist = "RunXV12pp200"; $NEvents = 1000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 09/20/15 check in dev forgot  TpcCurrentCorrection.20150131.000004.C
#$hist = "RunXV13pp200"; $NEvents = 1000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 09/20/15 check in dev 
#$hist = "RunXV14pp200"; $NEvents = 50000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 09/21/15  reset TpcCurrentCorrection
#$hist = "RunXV15pp200"; $NEvents = 50000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 09/22/15  add Qcm dependence in TpcRowQ
#$hist = "RunXV16pp200"; $NEvents = 50000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 09/23/15  update TpcSecRowB and TpcRowQ
#$hist = "RunXV17pp200"; $NEvents = 50000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 09/24/15  update TpcLengthCorrectionB
#$hist = "RunXV18pp200"; $NEvents = 50000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 09/25/15  test wrt dev
#$hist = "RunXV19pp200"; $NEvents = 50000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 10/15/15  check after dE/dx reproduction with new T0
#$hist = "RunXV20pp200"; $NEvents = 500; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 10/15/15  check 
#$hist = "RunXV21pp200"; $NEvents = 50000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 10/18/15  check with full statistics
#$hist = "RunXV22pp200"; $NEvents = 1000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 11/04/15  use new model for dE/dx
#$hist = "RunXV23pp200"; $NEvents = 5000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 11/09/15  use new model for dE/dx Full statistics
#$hist = "RunXV24pp200"; $NEvents = 5000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 11/12/15  revised model for dE/dx test
#$hist = "RunXV25pp200"; $NEvents = 5000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 11/13/15  revised model for dE/dx, fix GeV => keV 
#$hist = "RunXV26pp200"; $NEvents = 5000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 11/14/15  Current "K", new TpcSecRowB remove Current correction in TpcRowQ
#$hist = "RunXV27pp200"; $NEvents = 5000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "/afs/rhic.bnl.gov/star/users/fisyak/macros/dEdx";# 11/14/15  Current "K", new TpcSecRowB (starting from vrs 15) foreinstate Current correction in TpcRowQ
#$hist = "RunXV28pp200"; $NEvents = 5000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";# 11/23/15 new dX histograms and new model
#$hist = "RunXV29pp200"; $NEvents = 1000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/24/15 new dX histograms and new model
#$hist = "RunXV30pp200"; $NEvents = 1000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/26/15 new histograms
#$hist = "RunXV31pp200"; $NEvents = 2000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/29/15 disactivate TpcAvgPowerSupply for runs 16060053-16060065, reset all corrections (except Pressure) to default
#$hist = "RunXV32pp200"; $NEvents = 2000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/29/15 new TpcSecRowB
#$hist = "RunXV33pp200"; $NEvents = 1000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";# 11/30/15 new TpcSecRowB, test run with dX plots
#$hist = "RunXV34pp200"; $NEvents = 1000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";# 12/01/15 check __OLD_dX_Calculation__ 
#$hist = "RunXV35pp200"; $NEvents = 1000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";# 12/02/15 add TpcdXCorrectionB
#$hist = "RunXV36pp200"; $NEvents = 2000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 12/02/15 new dEdxModel.root with reduced no. of bins
#$hist = "RunXV37pp200"; $NEvents = 2000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 12/03/15 restore disactivated (RunXV31pp200) TpcAvgPowerSupply for runs 16060053-16060065
#$hist = "RunXV38pp200"; $NEvents = 2000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 12/03/15 the same but apply dxCorrected for fitN
#$hist = "RunXV39pp200"; $NEvents = 2000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 12/04/15 reset dX and Z corrections, no completed
#$hist = "RunXV40pp200"; $NEvents = 2000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 12/04/15 reset dX and Z corrections, TpcDriftDistOxygen
#$hist = "RunXV41pp200"; $NEvents = 2000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 12/04/15 new TpcRowQ && TpcSecRowB
#$hist = "RunXV42pp200"; $NEvents = 2000; $disk = "data9*"; $RECO = "/reco/production_pp200*_2015/ReversedFullField"; $Production = "/P15ii_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 12/05/15 new TpcdXCorrectionB
#$hist = "RunXV43pp200"; $NEvents = 1000; $disk = "data9*"; $RECO = "/reco/production_*_2015/ReversedFullField"; $Production = "/P15i*_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 12/05/15 new TpcdXCorrectionB (correct correction for outer sectors)
#       79 *  16045082 * 0.0131403 * 0.4123838 *
#       80 *  16045083 * 0.0018921 * 0.4098850 *
#       81 *  16045084 * 0.0026057 * 0.4110295 *
#       82 *  16045085 * -0.008775 * 0.4103426 *
#       83 *  16045086 * 0.0018460 * 0.4088475 *
#       84 *  16045087 * -0.002108 * 0.4120737 *
#       85 *  16045088 * 0.0054678 * 0.4173898 *
#my @badruns = qw(
#		  16045082
#		  16045083
#		  16045084
#		  16045085
#		  16045086
#		  16045087
#		  16045088
#	       );   # reset bad runs 12/11/15 
#$hist = "RunXV44"; $NEvents = 1000; $disk = "data9*"; $RECO = "/reco/production_*_2015/ReversedFullField"; $Production = "/P15i*_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 12/11/15 new TpcRowQ && TpcSecRowB  
#$hist = "RunXV45"; $NEvents = 1000; $disk = "data9*"; $RECO = "/reco/production_*_2015/ReversedFullField"; $Production = "/P15i*_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 12/12/15 new TpcCurrentCorrection no completed
#$hist = "RunXV46"; $NEvents = 1000; $disk = "data9*"; $RECO = "/reco/production_*_2015/ReversedFullField"; $Production = "/P15i*_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 12/12/15 new TpcCurrentCorrection
#$hist = "RunXV47"; $NEvents = 1000; $disk = "data9*"; $RECO = "/reco/production_*_2015/ReversedFullField"; $Production = "/P15i*_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 12/13/15 new TpcZCorrectionB
#$hist = "RunXV48"; $NEvents = 1000; $disk = "data9*"; $RECO = "/reco/production_*_2015/ReversedFullField"; $Production = "/P15i*_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 12/14/15 fix bug TpcZCorrectionB
# pp200  10.9 weeks 2015-01-14 13:46:13 - 2015-05-04 12:46:54 => 2015-01-31 00:00:48
# pAu200  5.1 weeks 2015-05-04 20:52:03 - 2015-06-08 13:46:14 => 2015-05-04 20:00:49
# FXT               2015-05-20 12:35:10 - 2015-05-20 15:57:29 => 2015-05-20 13:51:22 deactive
# pAl200  1.9 weeks 2015-06-09 06:30:45 - 2015-06-24 22:06:17 => 2015-06-09 00:01:02
# FXT               2015-05-20 12:35:10 - 2015-06-18 18:31:31 
#$hist = "RunXV49"; $NEvents = 1000; $disk = "data9*"; $RECO = "/reco/production_*_2015/ReversedFullField"; $Production = "/P15i*_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 12/14/15 new TpcSecRowB
#$hist = "RunXV50"; $NEvents = 1000; $disk = "data9*"; $RECO = "/reco/production_pAu200*_2015/ReversedFullField"; $Production = "/P15i*_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 12/14/15 new TpcSecRowB for pAu200
#$hist = "RunXV51"; $NEvents = 1000; $disk = "data9*"; $RECO = "/reco/production*_2015/ReversedFullField"; $Production = "/P15i*_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 12/14/15 new TpcLengthCorrectionMDF.20150131.000050.C error in TcdEdxTrack correction
#$hist = "RunXV52"; $NEvents = 1000; $disk = "data9*"; $RECO = "/reco/production*_2015/ReversedFullField"; $Production = "/P15i*_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 12/18/15 new TpcLengthCorrectionMDF.20150131.000050.C 
#$hist = "RunXV53"; $NEvents = 1000; $disk = "data9*"; $RECO = "/reco/production*_2015/ReversedFullField"; $Production = "/P15i*_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 12/19/15 fix bug for dNdx StPidStatus
#$hist = "RunXV54"; $NEvents = 1000; $disk = "data9*"; $RECO = "/reco/production*_2015/ReversedFullField"; $Production = "/P15i*_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 12/25/15 check with dev
#/star/data7*/reco/production_pAl200_2015/ReversedFullField/P16ib_TOF_dEdx/2015/*/*
#/star/data7*/reco/production_pAl200_2015_lowlumi/ReversedFullField/P16ib_TOF_dEdx/2015/*/*
#$hist = "RunXV61"; $NEvents = 1000; $disk = "data7*"; $RECO = "/reco/production*_2015*/ReversedFullField"; $Production = "/P16i*_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 03/07/16 the 1-st pass
#$hist = "RunXV62"; $NEvents = 1000; $disk = "data7*"; $RECO = "/reco/production*_2015*/ReversedFullField"; $Production = "/P16i*_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 03/08/16 fix a bug for I70 correction in TpcLengthCorrectionMDF.20150131.000050.C
#$hist = "RunXV103"; $NEvents = 10000; $disk = "data7*"; $RECO = "/reco/production*_2015*/ReversedFullField"; $Production = "/P16i*_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 03/09/16 Update SecRow
#$hist = "RunXV104"; $NEvents = 10000; $disk = "data7*"; $RECO = "/reco/production*_2015*/ReversedFullField"; $Production = "/P16i*_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 03/19/16 check in dev
#$hist = "RunXV105"; $NEvents = 10000; $disk = "data*"; $RECO = "/reco/production*_2015*/ReversedFullField"; $Production = "/P1*_TOF_dEdx"; $year = "/2015/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 03/23/16 check in dev for whole sample
# ========================== 2016 Run XVI =================================
#Trigger      |     start                      | end			
# AuAu200     | 2016-02-07 16:48:17 (17038047) | 2016-05-09 11:55:26 (17130013) 
#  dAu200     | 2016-05-12 03:44:13 (17132063) | 2016-05-20 07:26:26 (17141003)  2016-05-12 03:42:38            | 2016-05-16 04:30:29 (17136051)
#  dAu62      | 2016-05-21 01:13:58 (17141041) | 2016-05-23 05:30:36 (17143048)  2016-05-21 01:13:58 (17141041) ! 2016-05-28 21:08:16 (17149052)
#  dAu20      | 2016-05-29 00:07:34 (17149053) | 2016-05-30 05:02:20 (17150037)  2016-05-29 00:07:34 (17149053) | 2016-06-08 11:50:35 (17160009)
#  dAu39      | 2016-06-09 13:00:26 (17161012) | 2016-06-17 12:47:22 (17169018)  2016-06-09 11:43:52 (17161006) | 2016-06-20 18:12:55 (17172032)
# AuAu200p2   | 2016-06-18 03:05:49 (17169108) | 
#$hist = "RunXVIAuAu200p1"; $NEvents = 10000; $disk = "data9*/"; $RECO = "reco/AuAu_200_production_2016/ReversedFullField"; $Production = "/P16ie_TOF_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 06/20/16 First check
#$hist = "RunXVIAuAu200p2"; $NEvents = 10000; $disk = "data9*/"; $RECO = "reco/AuAu_200_production_2016/ReversedFullField"; $Production = "/P16ie_TOF_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 06/22/16 Fix problem with wrong ranking
#$hist = "RunXVIAuAu200p3"; $NEvents = 3000; $disk = "data9*/"; $RECO = "reco/AuAu_200_production_2016/ReversedFullField"; $Production = "/P16ie_TOF_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 06/22/16 more problem with negative ranking for AuAu
#$hist = "RunXVIAuAu200p4"; $NEvents = 3000; $disk = "data9*/"; $RECO = "reco/AuAu_200_production_2016/ReversedFullField"; $Production = "/P16ie_TOF_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/11/16 overwrite TpcLengthCorrectionB.r2016.C 
#my @badruns = qw( 
#		  17123029 17123029 17123029 17123029 17121005 17119092
#		  17108041 17108024 17107054 17107057 17107052 17105022
#		  17102043 17102016 17100047 17100012 17100011 17100016
#		  17100006 17100007 17100009 17100010 17100005 17099032
#		  17099005 17097039 17097038 17097033 17097034 17097035
#		  17072031 17072022 17067019 17064045 17049068 17050003
#		  17038082 17038082 17038084 17038081 17038081 17058048
#		  17052058 17046012 17039006
#		  17039042 17040050 17040051 17054017 17056007 17057006
#		  17068062 17072041 17104030 17104031 17108048 17110001
#		  17111059 17112041 17115029 17117062
#		  17044004 17049028 17050016 17050033 17053020 17053045
#		  17067004 17068037 17097036 17101035 17108013 17123005
#		  17123006 17123035 17128001 17129044 
#		  17152012 17153058 17155032 17159050 17159056 
#		);
# dAu20-62 bad runs form RunSummary : 17152012 17153058 17155032 17159050 17159056 
#my  bad Runs from PowerSypply:		  17057012 17060037 17075027 17107055 17109059 
# new Bad runs  17044012 (20160213/105923 -----   20160213/130532)  previous (20160213/104848 -----   20160213/105923)
#               17107055 (20160417/25422  -----   20160417/34114)   previous (20160417/24552 -----   20160417/25422) =>)
#  deactive 17044012
#  reset beginTime for 17107056 to beginTime of 17107055
#$hist = "RunXVIAuAu200p5"; $NEvents = 3000; $disk = "data9*/"; $RECO = "reco/AuAu_200_production_2016/ReversedFullField"; $Production = "/P16ie_TOF_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics*"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/12/16 clean bad runs, reset all constants  
#$hist = "RunXVIAuAu200p5"; $NEvents = 3000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/12/16 clean bad runs, reset all constants 
#$hist = "RunXVIAuAu200p6"; $NEvents = 3000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/15/16 new TpcSecRowB
#$hist = "RunXVIAuAu200p7"; $NEvents = 3000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/16/16 new tpcPressureB
#$hist = "RunXVIAuAu200p8"; $NEvents = 3000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/17/16 new TpcZCorrectionB
#$hist = "RunXVIAuAu200p9"; $NEvents = 3000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/18/16 take out TpcZCorrectionB, add VpdZ restriction on primary vertex
#$hist = "RunXVIAuAu200p10"; $NEvents = 3000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/19/16 add TpcdXCorrectionB
#$hist = "RunXVIAuAu200p11"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";# 07/20/16 reset TpcAdcCorrectionB to y2015, test Z dependence
#$hist = "RunXVIAuAu200p12"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";# 07/22/16 remove TpcAdcCorrectionB to test Z dependence
#$hist = "RunXVIAuAu200p13"; $NEvents = 3000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/23/16 Z-dependence exits, step back to RunXVIAuAu200p9 with new TpcAdcCorrectionB correction
#$hist = "RunXVIAuAu200p14"; $NEvents = 3000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/25/16 new TpcSecRowB & TpcRowQ, add TanL histograms
#$hist = "RunXVIAuAu200p15"; $NEvents = 3000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/26/16 add TanL correction
#$hist = "RunXVIAuAu200p16"; $NEvents = 3000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/29/16 new TpcSecRowB & TpcRowQ
#$hist = "RunXVIAuAu200p17"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; $macro = "dEdx";# 07/31/16 step back to RunXVIAuAu200p14 (TanL correction does not work), back to Bichsel model (take CVS version) check retreat
#$hist = "RunXVIAuAu200p18"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/01/16 TpcZCorrectionB.20160207.000017.C
#$hist = "RunXVIAuAu200p19"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/02/16 new TpcSecRowB & TpcRowQ
#$hist = "RunXVIAuAu200p20"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/03/16 TpcCurrentCorrection
#$hist = "RunXVIAuAu200p21"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/04/16 Fix voltages, step back with TpcCurrentCorrection
#$hist = "RunXVIAuAu200p22"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/05/16 use Tpc/Current/2016D/TpcAvgPowerSupply to double check this table
#$hist = "RunXVIAuAu200p23"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/08/16 new TpcAvgPowerSupply from 2016J, new Voltage histograms
#$hist = "RunXVIAuAu200p24"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/10/16 clean mess with Anode Voltage Gain correction
#$hist = "RunXVIAuAu200p25"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/12/16 add hack for gain correction to ignore variation in voltage, switch to SecRow3NN correction
#$hist = "RunXVIAuAu200p26"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/12/16 add hack for gain correction to ignore variation in voltage, switch to SecRow3NN correction, fix a bug in gain
#$hist = "RunXVIAuAu200p27"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/14/16 fix an other bug in gain
#$hist = "RunXVIAuAu200p28"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/14/16 remove hack in gain, remove  tpcGainCorrection.20160207.000024.C, clear TpcAvgPowerSupply 64b
#$hist = "RunXVIAuAu200p29"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField"; $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/15/16 clean up TpcAvgPowerSupply (2016K), new TpcSecRowB, 32b
#$hist = "RunXVIAuAu200p30"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/18/16 TpcLengthCorrectionMDF, 64b
#$hist = "RunXVIAuAu200p31"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/22/16  restore Zdc Histograms
#$hist = "RunXVIAuAu200p32"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/23/16  restore Zdc, forgot to recompile
#$hist = "RunXVIAuAu200p33"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/23/16  ignore out of time TpcAvgPowerSupply
#$hist = "RunXVIAuAu200p34"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/24/16 TpcCurrentCorrection.20160207.000033.C 
#$hist = "RunXVIAuAu200p35"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/25/16 TpcSecRowB.20160207.000034
#$hist = "RunXVIAuAu200p36"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/26/16 TpcSecRowB.20160207.000035 no TpcZCorrectionB
#$hist = "RunXVIAuAu200p37"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/27/16 TpcSecRowB.20160207.000036 + TpcdXCorrection
#$hist = "RunXVIAuAu200p38"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/27/16 
#$hist = "RunXVIAuAu200p39"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/28/16 TpcSecRowB.20160207.000038, reshape StTpcdEdxCorrection.cxx
#$hist = "RunXVIAuAu200p39"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/28/16 TpcSecRowB.20160207.000038, reshape StTpcdEdxCorrection.cxx
#$hist = "RunXVIAuAu200p40"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/30/16 TpcSecRowB.20160207.000038, reshape StTpcdEdxCorrection.cxx
#$hist = "RunXVIAuAu200p41"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/31/16 TpcSecRowB.20160207.000038, reshape StTpcdEdxCorrection.cxx deactivate TpcAvgPowerSupplay  for 17057012 17060037 17075027 17107055 17109059 , take out dX dependence
#$hist = "RunXVIAuAu200p42"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/01/16 TpcSecRowB.20160207.000041, TpcTanL
#$hist = "RunXVIAuAu200p43"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/02/16 TpcSecRowB.20160207.000042
#$hist = "RunXVIAuAu200p44"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/04/16 step back to RunXVIAuAu200p40, TpcLengthCorrectionMDF.20160207.000040.C
#$hist = "RunXVIAuAu200p45"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/05/16 new TpcAdcCorrection
#$hist = "RunXVIAuAu200p46"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/06/16 TpcSecRowB.20160207.000045.root
#$hist = "RunXVIAuAu200p47"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/07/16 TpcTanL.20160207.000046.C
#$hist = "RunXVIAuAu200p48"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/9/16 TpcSecRowB.20160207.000047
#$hist = "RunXVIAuAu200p49"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/10/16 TpcEffectivedX
#$hist = "RunXVIAuAu200p50"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/11/16 fix bug in StTpcdEdxCorrections, 
#$hist = "RunXVIAuAu200p51"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/11/16 fix an other bug in StTpcdEdxCorrections, 
#$hist = "RunXVIAuAu200p52"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/12/16 fix mess in StTpcdEdxCorrection
#$hist = "RunXVIAuAu200p53"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/12/16 debug version
#$hist = "RunXVIAuAu200p54"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/12/16 reset TpcEffectivedX
#$hist = "RunXVIAuAu200p55"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/13/16 new version of StdEdxY2Maker, reset TpcSecRowB and TpcRowQ, use TpcEffectivedX adn TpcTanL
#$hist = "RunXVIAuAu200p56"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/14/16 new version of StdEdxY2Maker, new TpcSecRowB and TpcRowQ
#$hist = "RunXVIAuAu200p57"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/15/16 TpcZCorrectionB
#$hist = "RunXVIAuAu200p58"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/16/16 tpcPressureB and TpcSecRowB and TpcRowQ, stop and add more bad runs
#$hist = "RunXVIAuAu200p59"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/16/16 tpcPressureB and TpcSecRowB and TpcRowQ, more bad runs
#$hist = "RunXVIAuAu200p100"; $NEvents = 500; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/17/16 TpcSecRowB and TpcRowQ, new TpcTanL from GF
#$hist = "RunXVIAuAu200p101"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/17/16 TpcSecRowB and TpcRowQ


#$hist = "RunXVIAuAu200p202"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/16/16 step back Pass 44
#$hist = "RunXVIAuAu200p203"; $NEvents = 500; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/16/16 step back Pass 44. Reset TpcSecRowB to 1

#$hist = "RunXVIAuAu200p102"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/18/16 TpcSecRowB and TpcRowQ based on SecRow3CGFRunXVIAuAu200p101
#$hist = "RunXVIAuAu200p103"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/18/16 update TpcRowQ, tpcPressureB, TpcLengthCorrectionMDF
#$hist = "RunXVIAuAu200p104"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/19/16 fix bug TpcRowQ => TpcEffectivedX
#$hist = "RunXVIAuAu200p105"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/19/16 update TpcRowQ, tpcPressureB
#$hist = "RunXVIAuAu200p106"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = "adev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/20/16 check with adev, run with old Tpc Alignment
#$hist = "RunXVIAuAu200p107"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = "adev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/21/16 check with adev with new TPC alignment, got old TpcAdcCorrection
#$hist = "RunXVIAuAu200p108"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = "adev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/22/16 check with adev with new TPC alignment, disable old TpcAdcCorrection for > 2015-12-00, 
#$hist = "RunXVIAuAu200p109"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/28/16 check with .DEV2 wrt MySQL 

#/star/data9*/reco/dAu200_production_2016/ReversedFullField/P16ii_TOF_dEdx_HFT/2016/*/*
#$hist = "RunXVIdAu200p200"; $NEvents = 1000; $disk = "data9*/"; $RECO = "reco/dAu200_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/22/16 the first pass with AuAu200 constants
#$hist = "RunXVIdAu200p201"; $NEvents = 1000; $disk = "data9*/"; $RECO = "reco/dAu200_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/23/16  TpcRowQ and TpcSecRowB
#$hist = "RunXVIdAu200p202"; $NEvents = 1000; $disk = "data9*/"; $RECO = "reco/dAu200_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/23/16  switch off TpcCurrentCorrection
#$hist = "RunXVIdAu200p203"; $NEvents = 2000; $disk = "data9*/"; $RECO = "reco/dAu200_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/24/16 new TpcCurrentCorrectionX
#$hist = "RunXVIdAu200p204"; $NEvents = 2000; $disk = "data9*/"; $RECO = "reco/dAu200_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/25/16 new TpcCurrentCorrectionX, recompile DetectorDb .sl64_x8664_gcc492/OBJ
#$hist = "RunXVIdAu200p205"; $NEvents = 2000; $disk = "data9*/"; $RECO = "reco/dAu200_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/25/16 new TpcCurrentCorrectionX, recompile DetectorDb .sl64_x8664_gcc492/OBJ, fix missing rows in TpcCurrentCorrectionX
#$hist = "RunXVIdAu200p206"; $NEvents = 2000; $disk = "data9*/"; $RECO = "reco/dAu200_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/26/16 new TpcTanL
#$hist = "RunXVIdAu200p207"; $NEvents = 2000; $disk = "data9*/"; $RECO = "reco/dAu200_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/27/16 TpcLengthCorrectionMDF
#$hist = "RunXVIdAu200p208"; $NEvents = 2000; $disk = "data9*/"; $RECO = "reco/dAu200_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/28/16 fix TpcLengthCorrectionMDF
#$hist = "RunXVIdAu200p209"; $NEvents = 2000; $disk = "data9*/"; $RECO = "reco/dAu200_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/29/16 TpcRowQ and TpcSecRowB
#$hist = "RunXVIdAu200p210"; $NEvents = 2000; $disk = "data9*/"; $RECO = "reco/dAu200_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/30/16 check dev
#$hist = "RunXVIAuAu200p109"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/AuAu_*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx"; $year = "/2016/*/*/"; $FILE = "st_physics"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/28/16 check with .DEV2 wrt MySQL 
#$hist = "RunXVI211"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/*_production2*_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/03/16 check dev AuAu200 + dAu200
#$hist = "RunXVI212"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/*_production2*_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/05/16 correct AuAu200p2 SecRow
#$hist = "RunXVI213"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/*_production2*_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/06/16 test with dev
#$hist = "RunXVI214"; $NEvents = 500; $disk = "data*/"; $RECO = "reco/*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/09/2016 step back to 1.2 TpcAdcCorrectionB.y2016.C 
#$hist = "RunXVI215"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/10/2016 adjust scale TpcAdcCorrectionB
#$hist = "RunXVI216"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/11/2016 update TpcRowQ & TpcSecRowB
#$hist = "RunXVI217"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/12/2016 update TpcLengthCorrectionMDF
#$hist = "RunXVI218"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/13/2016 update TpcTanL
#$hist = "RunXVI219"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/15/2016 check set 216 wrt dev (MySQL)
#$hist = "RunXVI220"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 01/04/2017 recheck in dev
#$hist = "RunXVI221"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 01/04/2017 recheck in .DEV2
#$hist = "RunXVI222"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/*_production*_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 01/13/2017 recheck in .DEV2 after fixing StTpcdEdxCorrection
#/star/data9*/reco/dAu20_production_2016/ReversedFullField/P16ij_TOF_dEdx_HFT/2016/*/*
#/star/data9*/reco/dAu39_production_2016/ReversedFullField/P16ij_TOF_dEdx_HFT/2016/*/*
#/star/data9*/reco/dAu62_production_2016/ReversedFullField/P16ij_TOF_dEdx_HFT/2016/*/*
#$hist = "RunXVI300"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/dAu*_production_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 01/23/2017 recheck with calibration from dAu200
#$hist = "RunXVI301"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/dAu*_production_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 01/27/2017 update TpcRowQ & TpcSecRowB
#$hist = "RunXVI302"; $NEvents = 5000; $disk = "data*/"; $RECO = "reco/dAu*_production_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 01/27/2017 switch off TpcCurrentCorrectionX, TpcEdge
#$hist = "RunXVI303"; $NEvents = 5000; $disk = "data*/"; $RECO = "reco/dAu*_production_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/03/2017 rerun after fix mess with TpcAdcCorrectionB
#$hist = "RunXVI304"; $NEvents = 5000; $disk = "data*/"; $RECO = "reco/dAu*_production_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/04/2017 switch off TpcTanL
#$hist = "RunXVI305"; $NEvents = 5000; $disk = "data*/"; $RECO = "reco/dAu*_production_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/05/2017 update TpcRowQ & TpcSecRowB
#$hist = "RunXVI306"; $NEvents = 5000; $disk = "data*/"; $RECO = "reco/dAu*_production_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/08/2017 add TpcCurrentCorrectionX & TpcTanL
#$hist = "RunXVI307"; $NEvents = 5000; $disk = "data*/"; $RECO = "reco/dAu*_production_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/09/2017  update TpcRowQ & TpcSecRowB
#$hist = "RunXVI308"; $NEvents = 5000; $disk = "data*/"; $RECO = "reco/dAu*_production_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/09/2017  update TpcRowQ & TpcSecRowB
#$hist = "RunXVI309"; $NEvents = 5000; $disk = "data*/"; $RECO = "reco/dAu*_production_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/09/2017  update TpcZCorrectionB, bad runs
#$hist = "RunXVI310"; $NEvents = 5000; $disk = "data*/"; $RECO = "reco/dAu*_production_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/11/2017  restore def. Edge cut, update TpcRowQ & TpcSecRowB
#$hist = "RunXVI311"; $NEvents = 5000; $disk = "data*/"; $RECO = "reco/dAu*_production_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/12/2017 update TpcRowQ & TpcSecRowB, TpcTanL, remove (int) for  pad 
#$hist = "RunXVI312"; $NEvents = 5000; $disk = "data*/"; $RECO = "reco/dAu*_production_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/13/2017 update TpcRowQ & TpcSecRowB, TpcTanL, fix xPar
#$hist = "RunXVI313"; $NEvents = 5000; $disk = "data*/"; $RECO = "reco/dAu*_production_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/13/2017 TpcPadCorrectionMDF
#$hist = "RunXVI314"; $NEvents = 5000; $disk = "data*/"; $RECO = "reco/dAu*_production_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/13/2017 TpcPadCorrectionMDF, fix a bug
#$hist = "RunXVI315"; $NEvents = 5000; $disk = "data*/"; $RECO = "reco/dAu*_production_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/14/2017 TpcLengthCorrectionNDF
#$hist = "RunXVI316"; $NEvents = 5000; $disk = "data*/"; $RECO = "reco/dAu*_production_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/15/2017 check in dev
#$hist = "TpcRS_2016D1.DEV2D"; $NEvents = 50000; $disk = "data*/"; $RECO = "reco/dAu*_production_2016/ReversedFullField";  $Production = "/P16i*_dEdx*"; $year = "/2016/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 03/16/2017 
# /star/data09/reco/AuAu200_production2_2016/ReversedFullField/P16ig_dEdx_HFT/
# Run XVII
# Lanny pointed (04/26/17) 18116002-18116006 run can be bad. 
#/star/data2*/reco/pp500_production_2017/ReversedFullField/P17if_calib/2017/*/*
#/star/data2*/reco/pp500_production_rhicf_2017/ReversedFullField/P17if_calib/2017/*/*
#$hist = "RunXVII01"; $NEvents = 5000; $disk = "data2*/"; $RECO = "reco/pp500_production*_2017/ReversedFullField";  $Production = "/P17if_calib"; $year = "/2017/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/21/2017 check the present status of calibration from RunXVI
#$hist = "RunXVII02"; $NEvents = 5000; $disk = "data2*/"; $RECO = "reco/pp500_production*_2017/ReversedFullField";  $Production = "/P17if_calib"; $year = "/2017/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/21/2017 check the present status of calibration from RunXVI, recheck after fix of StPidStatus
#$hist = "RunXVII03"; $NEvents = 5000; $disk = "data2*/"; $RECO = "reco/pp500_production*_2017/ReversedFullField";  $Production = "/P17if_calib"; $year = "/2017/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/23/2017 reset all corrections to 0
#$hist = "RunXVII04"; $NEvents = 1000; $disk = "data2*/"; $RECO = "reco/pp500_production*_2017/ReversedFullField";  $Production = "/P17if_calib"; $year = "/2017/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/24/2017 TpcRowQ/TpcSecRowB
#$hist = "RunXVII05"; $NEvents = 1000; $disk = "data2*/"; $RECO = "reco/pp500_production*_2017/ReversedFullField";  $Production = "/P17if_calib"; $year = "/2017/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/25/2017 tpcPressureB.20170101.000004.C
# runs with TpcAvgPower problems
# my @badruns = qw( 
#  18053100 18053117 18053121 18055034 18055038 18055046 18056020 18056029 18056030 18056031
#  18056032 18056033 18056037 18056042 18056043 18056046 18056055 18056087 18059024 18059062
#  18059063 18060106 18060107 18060110 18060112 18060114 18060116 18061092 18062040 18063095
#  18063097 18063098 18063099 18063101 18065045 18065083 18067092 18071074 18072018 18076006
#  18077016 18077040 18078066 18080025 18080048 18083041 18084051 18085043 18087037 18089064
#  18090019 18090023 18090058 18091008 18091018 18091025 18092001 18092004 18092005 18092014
#  18093005 18094002 18094003 18094006 18094011 18094012 18094015 18094016 18094019 18094035
#  18094036 18094037 18094061 18094066 18097002 18097004 18097011 18097057 18098034 18099042
#  18101029 18101035 18104021 18105043 18107042 18108036 18109002 18117021 18118004 18118018
#  18119018 18121008 18121009 18121017 18121023 18122019 18123025 18127073 18127079 18128055
#  18131094 18134044 18134045 18134046 18135019 18135020 18135053 18136012 18136013 18147007
#  18175028 18177045 18177048
# ); # short runs 
# extra entries 
#beginTime = "2017-03-15 17:39:28" or beginTime = "2017-03-17 17:22:00" or beginTime = "2017-04-06 22:27:11" or beginTime = "2017-04-09 14:07:23" or beginTime = "2017-04-23 20:38:03" or beginTime = "2017-04-28 13:16:48" or beginTime = "2017-05-03 13:47:37" or beginTime = "2017-05-04 19:41:23" or beginTime = "2017-05-09 12:03:54" or beginTime = "2017-05-18 18:41:52" or beginTime = "2017-05-26 11:58:27" or beginTime = "2017-05-30 14:49:42" or beginTime = "2017-06-03 12:51:09"
#$hist = "RunXVII06"; $NEvents = 1000; $disk = "data2*/"; $RECO = "reco/pp500_production*_2017/ReversedFullField";  $Production = "/P17if_calib"; $year = "/2017/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/27/2017 TpcRowQ.20170101.000005.C & TpcSecRowB.20170101.000005.root
#$hist = "RunXVII07"; $NEvents = 1000; $disk = "data2*/"; $RECO = "reco/pp500_production*_2017/ReversedFullField";  $Production = "/P17if_calib"; $year = "/2017/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/28/2017 TpcTanL.20170101.000006.C
#$hist = "RunXVII08"; $NEvents = 1000; $disk = "data2*/"; $RECO = "reco/pp500_production*_2017/ReversedFullField";  $Production = "/P17if_calib"; $year = "/2017/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/28/2017 TpcZCorrectionB.20170101.000007.C
#$hist = "RunXVII09"; $NEvents = 1000; $disk = "data2*/"; $RECO = "reco/pp500_production*_2017/ReversedFullField";  $Production = "/P17if_calib"; $year = "/2017/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/29/2017 TpcSecRowB.20170101.000008 & TpcRowQ.20170101.000008
#$hist = "RunXVII10"; $NEvents = 1000; $disk = "data2*/"; $RECO = "reco/pp500_production*_2017/ReversedFullField";  $Production = "/P17if_calib"; $year = "/2017/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/30/2017  TpcRowQ.20170101.000009.C
#$hist = "RunXVII11"; $NEvents = 1000; $disk = "data2*/"; $RECO = "reco/pp500_production*_2017/ReversedFullField";  $Production = "/P17if_calib"; $year = "/2017/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/30/2017 TpcCurrentCorrectionX.20170101.00010.C
# pp510  2017-02-23 00:19:42 - 2017-05-30 03:57:46
# AuAu54 2017-06-02 18:16:34 - 2017-06-21 11:22:30
# rhicf  2017-06-23 23:48:04 - 2017-06-27 11:45:51 
#$hist = "RunXVII13"; $NEvents = 1000; $disk = "data2*/"; $RECO = "reco/pp500_production*_2017/ReversedFullField";  $Production = "/P17if_calib"; $year = "/2017/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/31/2017 step back to RunXVII09, split pp510 and rhicf, TpcSecRowB.20170622.000012.root,TpcSecRowB.20170101.000012.root, TpcRowQ.20170622.000012.C, TpcRowQ.20170101.000012.C
#$hist = "RunXVII14"; $NEvents = 1000; $disk = "data2*/"; $RECO = "reco/pp500_production*_2017/ReversedFullField";  $Production = "/P17if_calib"; $year = "/2017/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/01/2017 xyPad
#$hist = "RunXVII15"; $NEvents = 1000; $disk = "data2*/"; $RECO = "reco/pp500_production*_2017/ReversedFullField";  $Production = "/P17if_calib"; $year = "/2017/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/02/2017  TpcLengthCorrectionMDF.20170101.000014
#$hist = "RunXVII16"; $NEvents = 1000; $disk = "data2*/"; $RECO = "reco/pp500_production*_2017/ReversedFullField";  $Production = "/P17if_calib"; $year = "/2017/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/06/2017 recheck with nodebug x8664
#$hist = "RunXVII17"; $NEvents = 1000; $disk = "data2*/"; $RECO = "reco/pp500_production*_2017/ReversedFullField";  $Production = "/P17if_calib"; $year = "/2017/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/07/2017 TpcLengthCorrectionMDF.20170101.000016.C from TPointsFUGPRunXVII16 
#$hist = "RunXVII18"; $NEvents = 1000; $disk = "data2*/"; $RECO = "reco/pp500_production*_2017/ReversedFullField";  $Production = "/P17if_calib"; $year = "/2017/*/*/"; $FILE = "st_"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/09/2017 test in dev
# /star/data2*/reco/AuAu54_production_2017/ReversedFullField/P17ih_calib/2017/*/*
#$hist = "RunXVII20"; $NEvents = 1000; $disk = "data2*/"; $RECO = "reco/AuAu54_production*_2017/ReversedFullField";  $Production = "/P17ih_calib"; $year = "/2017/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/07/2017 The first pass 
#$hist = "RunXVII21"; $NEvents = 5000; $disk = "data2*/"; $RECO = "reco/AuAu54_production*_2017/ReversedFullField";  $Production = "/P17ih_calib"; $year = "/2017/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/13/2017 update TpcSecRowB.20170602.000020 & TpcRowQ.20170602.000020
#$hist = "RunXVII22"; $NEvents = 5000; $disk = "data2*/"; $RECO = "reco/AuAu54_production*_2017/ReversedFullField";  $Production = "/P17ih_calib"; $year = "/2017/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 12/04/17 fit dN/dx with gradient
#$hist = "RunXVII23"; $NEvents = 2000; $disk = "data2*/"; $RECO = "reco/AuAu54_production*_2017/ReversedFullField";  $Production = "/P17ih_calib"; $year = "/2017/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 12/07/17 TpcLengthCorrectionMDF
#$hist = "RunXVII24"; $NEvents = 2000; $disk = "data2*/"; $RECO = "reco/AuAu54_production*_2017/ReversedFullField";  $Production = "/P17ih_calib"; $year = "/2017/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 12/08/17 correct idx in TpcLengthCorrectionMDF
#$hist = "RunXVII25"; $NEvents = 2000; $disk = "data2*/"; $RECO = "reco/AuAu54_production*_2017/ReversedFullField";  $Production = "/P17ih_calib"; $year = "/2017/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 12/09/17 correct correction for Ifit in TpcLengthCorrectionMDF
#?$hist = "RunXVII26"; $NEvents = 2000; $disk = "data2*/"; $RECO = "reco/AuAu54_production*_2017/ReversedFullField";  $Production = "/P17ih_calib"; $year = "/2017/*/*/"; $FILE = "st_"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 12/09/17 test in dev
# Run XVIII
# 19078015/dEdx - dEdx5, problem with loose GG connetctor in sector 19 inner, 03/21/18 - 03/22/18 
# 19086040/dEdx - dEdx3, use default alignment: 
# 19086040B/dEdx4 : switched off dEdx corrections (TpcZCorrectionB, TpcTanL, tpcPressureB), reinstall TPC alignment(no difference ?)  03/29/18 
# 19086040B/dEdx5 : switched off dEdx corrections (TpcZCorrectionB, TpcTanL), switch on  tpcPressureB), add hitograms for iTPC  03/30/18 
# 19086040.DEV2/dEdx11 : switched on dX correction 04/05/18
# AltroThresh2 : runs "0" 19116020(old Altro threshold : 3), "1" 19116021 (new Altro thresold : 4)
# dEdx30 : only dx Correction, Adc correction, no SecRow  05/02/18 => strange bump at pad row 44 ?
# dEdx31 : remove dx and Z correction, back with sockets, 05/03/18
# dEdx40: correct default TpcAdcCorrection, 05/31/18
# dEdx42: add correction to TpcAdcCorrection, 06/01/18
#2018/AltroThresh5/dEdx43 : add ADC histogram 06/02/18
# dEdx46 reset TcpSecRowB to 1, 06/03/18
# Run XVIII
# A.Lebedev, 07/24/18: May 3, 2010, about 19:45 TPC gas system failed and in ~ hour I restored. 
# production_isobar_2018               2018-03-12 16:24:39 GMT - 2018-05-09 11:41:42 GMT days  71 - 129
# Isobar_2018_oldaltro run = 19116020   2018-04-26 12:19:19 GMT - 2018-04-26 12:46:49 GMT day  116
# production_27GeV_fixedTarget_2018    2018-05-18 23:16:02 GMT - 2018-05-29 01:43:36 GMT days 138 - 149
# production_3p85GeV_fixedTarget_2018  2018-05-31 07:14:46 GMT - 2018-06-04 12:11:00 GMT days 151 - 155
# 27GeV_production_2018                2018-06-04 12:11:00 GMT - 2018-06-17 22:40:27 GMT days 155 - 168
# production_26p5GeV_fixedTarget_2018  2018-06-07 22:58:53 GMT - 2018-06-18 11:46:48 GMT days 158 - 169
################################################################################
# #  onl Run18 | SortRun18.pl
# production_isobar_2018                          19071038        19129014        2018-03-12      16:24:39        2018-05-10      20:15:52
# 27GeV_production_2018                           19130060        19138028        2018-05-10      20:15:52        2018-05-18      23:16:02
# production_27GeV_fixedTarget_2018               19138032        19138036        2018-05-18      23:16:02        2018-05-19      08:21:50
# 27GeV_production_2018                           19139022        19148024        2018-05-19      08:21:50        2018-05-28      19:53:50
# production_27GeV_fixedTarget_2018               19148036        19148047        2018-05-28      19:53:50        2018-05-29      02:33:07
# 27GeV_production_2018                           19148049        19150018        2018-05-29      02:33:07        2018-05-31      07:14:46
# production_3p85GeV_fixedTarget_2018             19151029        19155022        2018-05-31      07:14:46        2018-06-05      03:15:40
# 27GeV_production_2018                           19155057        19156033        2018-06-05      03:15:40        2018-06-05      17:42:25
# production_26p5GeV_fixedTarget_2018             19156034        19156039        2018-06-05      17:42:25        2018-06-05      20:51:04
# 27GeV_production_2018                           19156041        19156047        2018-06-05      20:51:04        2018-06-06      03:56:23
# production_26p5GeV_fixedTarget_2018             19156069        19156069        2018-06-06      03:56:23        2018-06-06      05:02:18
# 27GeV_production_2018                           19157002        19157018        2018-06-06      05:02:18        2018-06-06      22:44:00
# production_26p5GeV_fixedTarget_2018             19157033        19157043        2018-06-06      22:44:00        2018-06-07      05:08:35
# 27GeV_production_2018                           19158003        19158020        2018-06-07      05:08:35        2018-06-07      22:22:14
# production_26p5GeV_fixedTarget_2018             19158053        19158057        2018-06-07      22:22:14        2018-06-08      01:13:58
# 27GeV_production_2018                           19158059        19159041        2018-06-08      01:13:58        2018-06-08      23:29:26
# production_26p5GeV_fixedTarget_2018             19159042        19159046        2018-06-08      23:29:26        2018-06-09      04:47:27
# 27GeV_production_2018                           19160002        19160029        2018-06-09      04:47:27        2018-06-09      20:37:47
# production_26p5GeV_fixedTarget_2018             19160032        19161001        2018-06-09      20:37:47        2018-06-10      05:18:27
# 27GeV_production_2018                           19161003        19161019        2018-06-10      05:18:27        2018-06-10      14:04:12
# production_26p5GeV_fixedTarget_2018             19161020        19161042        2018-06-10      14:04:12        2018-06-11      01:53:29
# 27GeV_production_2018                           19161048        19162032        2018-06-11      01:53:29        2018-06-11      18:01:25
# production_26p5GeV_fixedTarget_2018             19162033        19162034        2018-06-11      18:01:25        2018-06-11      19:36:56
# 27GeV_production_2018                           19162036        19162042        2018-06-11      19:36:56        2018-06-12      03:07:05
# production_26p5GeV_fixedTarget_2018             19162043        19163004        2018-06-12      03:07:05        2018-06-12      06:53:04
# 27GeV_production_2018                           19163006        19163020        2018-06-12      06:53:04        2018-06-12      14:49:31
# production_26p5GeV_fixedTarget_2018             19163024        19163036        2018-06-12      14:49:31        2018-06-12      21:46:26
# 27GeV_production_2018                           19163039        19163041        2018-06-12      21:46:26        2018-06-13      00:09:56
# production_26p5GeV_fixedTarget_2018             19163042        19164002        2018-06-13      00:09:56        2018-06-13      05:37:58
# 27GeV_production_2018                           19164004        19164017        2018-06-13      05:37:58        2018-06-14      00:55:20
# production_26p5GeV_fixedTarget_2018             19164021        19164025        2018-06-14      00:55:20        2018-06-14      04:13:05
# 27GeV_production_2018                           19165002        19165029        2018-06-14      04:13:05        2018-06-14      18:04:39
# production_26p5GeV_fixedTarget_2018             19165030        19166004        2018-06-14      18:04:39        2018-06-15      07:25:06
# 27GeV_production_2018                           19166006        19166015        2018-06-15      07:25:06        2018-06-16      03:05:39
# production_26p5GeV_fixedTarget_2018             19166019        19167001        2018-06-16      03:05:39        2018-06-16      05:48:52
# 27GeV_production_2018                           19167003        19167049        2018-06-16      05:48:52        2018-06-17      01:29:50
# production_26p5GeV_fixedTarget_2018             19167050        19168020        2018-06-17      01:29:50        2018-06-17      14:31:02
# 27GeV_production_2018                           19168025        19168040        2018-06-17      14:31:02        2018-06-18      01:16:01
# production_26p5GeV_fixedTarget_2018             19168041        19169017        2018-06-18      01:16:01        2018-09-07      16:11:11
# 27GeV_production_2018                           19267003        19268002        2018-09-07      16:11:11        2018-11-02      16:26:20

# /star/data*/reco/production_isobar_2018/ReversedFullField/P18ie_calib/2018/*/*
#my @badruns = (19116020); # Altro3
#$hist = "RunXVIII01"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/21/18 check 
#$hist = "RunXVIII02"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/22/18  TpcSecRowB.20180312.000001
#$hist = "RunXVIII03"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/23/18  TpcSecRowB.20180312.000002
#$hist = "RunXVIII04"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/27/18  reset TpcdXCorrectionB and TpcAdcCorrectionB
#$hist = "RunXVIII05"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/28/18 TpcSecRowB.20180312.000004
#$hist = "RunXVIII06"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/29/18 TpcZCorrectionB.20180225.000005.C
#$hist = "RunXVIII07"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/29/18 TpcSecTpcSecRowB.20180312.000006.root
#$hist = "RunXVIII08"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/30/18 fix bug in TpcZCorrectionB.20180225.000005.C
#$hist = "RunXVIII09"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/30/18 TpcSecRowB.20180312.000008.root
#$hist = "RunXVIII10"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/31/18 TpcdXCorrectionB.20180225.000009.C
#$hist = "RunXVIII11"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/31/18 TpcSecRowB.20180312.000010.root
#$hist = "RunXVIII12"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/01/18 TpcPadCorrectionMDF.20180312.000011.C
#$hist = "RunXVIII13"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/02/18 redo TpcPadCorrectionMDF.20180312.000011.C without selection
#$hist = "RunXVIII14"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/02/18 add tpcTimeDependenceT, TpcLengthCorrectionMDF.20180312.000013.C, TpcSecRowB.20180312.000013.root
#$hist = "RunXVIII15"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/03/18 fix tpcTimeDependence
#$hist = "RunXVIII16"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/09/18 TpcPadCorrectionMDF.20180312.000015.C 
#$hist = "RunXVIII17"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/10/18 use BEST_VERTEX
#$hist = "RunXVIII18"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/10/18 remove dX,Z and xy
#$hist = "RunXVIII19"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/11/18 TpcSecRowB.20180312.000018.root
#$hist = "RunXVIII20"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/12/18 TpcdXCorrectionB.20180225.000019.C
#$hist = "RunXVIII21"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/12/18 TpcSecRowB.20180312.000020.root$hist = "RunXVIII21"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/12/18 TpcSecRowB.20180312.000020.root
#$hist = "RunXVIII22"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = "TFG18m"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/12/18 TpcSecRowB.20180312.000020.root$hist = "RunXVIII21"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/18/18 check TFG18m
#$hist = "RunXVIII23"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/12/18 TpcZCorrectionB.20180225.000021.C
#$hist = "RunXVIII25"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/13/18 TpcSecRowB.20180312.000022.root
#$hist = "RunXVIII39"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/30/18 test calibration obtained with alignment production
#$hist = "RunXVIII40"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/31/18 cut dX for Outer
#$hist = "RunXVIII41"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/02/18 rechec after merging with RCF
#$hist = "RunXVIII43"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = "DEV"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/18/18 check 2018 isobar calibration  dev (no iTPC, Aug version of code))
#$hist = "RunXVIII44"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = "DEV"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/19/18 check 2018 isobar calibration  dev (with iTPC, October)
#$hist = "RunXVIII45"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = "DEV"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/19/18 check 2018 isobar calibration  dev, add TpcLengthMDF.
#$hist = "RunXVIII46"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = "DEV"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/19/18 check 2018 isobar calibration  dev, add TpcLengthMDF. one moreupdate dor Ifit
#$hist = "RunXVIII47"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = "DEV"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/22/18 check MySQL
#$hist = "RunXVIII48"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/27/18 mv tsspar.y2001.C tsspar.y2001.C.HOLD.112718
#$hist = "RunXVIII49"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/28/18 mv tsspar.y2001.C.HOLD.112718 tsspar.y2018.C
#$hist = "RunXVIII50"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/13/20 test dev versus MySQL
#$hist = "RunXVIII51"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/14/20 compare with .DEV2 
#$hist = "RunXVIII52"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/14/20 update TpcSecRowB 
#$hist = "RunXVIII53"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/14/20 update TpcLengthCorrectionMDF
#$hist = "RunXVIII54"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/15/20 fix bug in h2mdf.C, update TpcLengthCorrectionMDF
#$hist = "RunXVIII55"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/15/20 check wrt dev
#$hist = "RunXVIII56"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/16/20 check wrt MySQL
#$hist = "RunXVIII57"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/18/20 recover StEventClusteringHints streamer
#$hist = "RunXVIII58"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/28/20 remove tpcTimeDependence
#$hist = "RunXVIII59"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/28/20 recover  tpcTimeDependence.*.C
#$hist = "RunXVIII60"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_isobar_2018/ReversedFullField";  $Production = "/P18ie_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/28/20 recover  tpcTimeDependence.*.C


#$hist = "RunXVIII118"; $NEvents = 2000; $disk = "data100/"; $RECO = "reco/27GeV_production_2018/*FullField";  $Production = "/P18if_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/16/18 check dE/dx calibration produced on HLT (with aligned geometry) wrt RCF
#$hist = "RunXVIII119"; $NEvents = 2000; $disk = "data100/"; $RECO = "reco/27GeV_production_2018/*FullField";  $Production = "/P18if_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = "TFG18m"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/18/18 check TFG18m
#$hist = "RunXVIII120"; $NEvents = 2000; $disk = "data100/"; $RECO = "reco/27GeV_production_2018/*FullField";  $Production = "/P18if_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/20/18 back to  TpcAdcCorrectionB.y2018.C.Altro4 as TpcAdcCorrectionB.20180518.000119.C to undestadn difference in sigma for Inner Rows
#$hist = "RunXVIII122"; HLT; # 08/23/18 add Eta hitogram
#$hist = "RunXVIII123"; HLT; # 08/24/18 redo ZCorrection
#$hist = "RunXVIII134"; $NEvents = 2000; $disk = "data100/"; $RECO = "reco/27GeV_production_2018/*FullField";  $Production = "/P18if_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/02/18 recheck after merging with HLT
#$hist = "RunXVIII135"; $NEvents = 2000; $disk = "data100/"; $RECO = "reco/27GeV_production_2018/*FullField";  $Production = "/P18if_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = "DEV"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/19/18 recheck in dev
#$hist = "RunXVIII136"; $NEvents = 2000; $disk = "data100/"; $RECO = "reco/27GeV_production_2018/*FullField";  $Production = "/P18if_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = "DEV"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/19/18 recheck in dev , add TpcLengthMDF
#$hist = "RunXVIII137"; $NEvents = 2000; $disk = "data100/"; $RECO = "reco/27GeV_production_2018/*FullField";  $Production = "/P18if_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = "DEV"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/22/18 check MySQL
#my @badruns = (
# 19132037_2000002
# 19132039_2000002
# 19133010_5500003
# 19134028_2500002
# 19134029_3500002
# 19135012_2500002
# 19135013_1500002
# );
#$hist = "RunXVIII137"; $NEvents = 2000; $disk = "data100/"; $RECO = "reco/27GeV_production_2018/*FullField";  $Production = "/P18if_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = "DEV"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/22/18 check MySQL
################################################################################
# Run XVIII FixedTarget 
# /star/data4X/reco/production_3p85GeV_fixedTarget_2018/ReversedFullField/P19id_calib/2018/*/*
#$hist = "RunXVIII300"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/15/2019 check wrp DB
#$hist = "RunXVIII301"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/17/2019  add West East separation
#$hist = "Run302"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/18/2019  add West East separation
#$hist = "Run303"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/30/2019  reduce pMom interal, do only Negative particles
#$hist = "Run303"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/30/2019  reduce pMom interal, do only Negative particles
#$hist = "Run304"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/31/2019  reset TpcdXCorrection, TpcZCorrectionB, TpcSecRowB
#$hist = "Run305"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/01/2019  new TpcSecRowB
#$hist = "Run306"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/01/2019  new new TpcSecRowB
#$hist = "Run307"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/01/2019  add year to dEdx.C parameters
#$hist = "Run310"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/04/2019 split TpcSecRowB
#$hist = "Run312"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/05/2019  iTpcOnly
#$hist = "Run313"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/05/2019  TpcZCorrection
#$hist = "Run314"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/06/2019  TpcSecRowB*
#$hist = "Run315"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/07/2019 split negative and positive particles in TPoints hisograms
#$hist = "Run316"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/07/2019 TpcLengthCorrectionMDF.20180518.000315.C


################################################################################
# Run XIX
# '461' => {trig=>'19GeV_2019',         	field => 'RF',	first=> '20056040',	 last => '20056040',	 list => '',  beginTime => '20190225.233839'}, # 	2019-02-25	23:38:39	2019-02-26	09:57:02
# '737' => {trig=>'19GeV_2019',         	field => 'RF',	first=> '20093035',	 last => '20093036',	 list => '',  beginTime => '20190403.111220'}, # 	2019-04-03	11:12:20	2019-04-04	09:44:05
# '738' => {trig=>'14p5GeV_2019',       	field => 'RF',	first=> '20094048',	 last => '20094048',	 list => '',  beginTime => '20190404.094405'}, # 	2019-04-04	09:44:05	2019-04-04	10:25:04
#'1081' => {trig=>'14p5GeV_2019',       	field => 'RF',	first=> '20154012',	 last => '20154013',	 list => '',  beginTime => '20190603.113018'}, # 	2019-06-03	11:30:18	2019-06-03	22:36:55
#'1082' => {trig=>'7p7GeV_2019',        	field => 'RF',	first=> '20154047',	 last => '20154052',	 list => '',  beginTime => '20190603.223655'}, # 	2019-06-03	22:36:55	2019-06-04	01:53:10
#'1100' => {trig=>'7p7GeV_2019',        	field => 'RF',	first=> '20158022',	 last => '20158026',	 list => '',  beginTime => '20190607.120916'}, # 	2019-06-07	12:09:16	2019-06-07	17:03:52
#'1101' => {trig=>'7p7GeV_2019',        	field => 'RF',	first=> '20158036',	 last => '20158036',	 list => '',  beginTime => '20190607.170352'}, # 	2019-06-07	17:03:52	2019-06-07	17:47:02
#'1102' => {trig=>'3p85GeV_fixedTarget_2019',	field => 'RF',	first=> '20158041',	 last => '20158042',	 list => '',  beginTime => '20190607.174702'}, # 	2019-06-07	17:47:02	2019-06-07	18:24:43
#'1104' => {trig=>'7p7GeV_2019',        	field => 'RF',	first=> '20158048',	 last => '20158051',	 list => '',  beginTime => '20190607.202244'}, # 	2019-06-07	20:22:44	2019-06-08	04:31:05
#'1112' => {trig=>'7p7GeV_2019',        	field => 'RF',	first=> '20160020',	 last => '20160022',	 list => '',  beginTime => '20190609.102036'}, # 	2019-06-09	10:20:36	2019-06-09	12:45:28
#'1113' => {trig=>'3p85GeV_fixedTarget_2019',	field => 'RF',	first=> '20160023',	 last => '20160027',	 list => '',  beginTime => '20190609.124528'}, # 	2019-06-09	12:45:28	2019-06-10	02:41:09
#'1114' => {trig=>'7p7GeV_2019',        	field => 'RF',	first=> '20160036',	 last => '20160041',	 list => '',  beginTime => '20190610.024109'}, # 	2019-06-10	02:41:09	2019-06-10	04:41:11
#'1163' => {trig=>'7p7GeV_2019',        	field => 'RF',	first=> '20169022',	 last => '20169025',	 list => '',  beginTime => '20190618.113308'}, # 	2019-06-18	11:33:08	2019-06-18	14:36:58
#'1164' => {trig=>'7.3GeV_fixedTarget_2019',	field => 'RF',	first=> '20169028',	 last => '20169045',	 list => '',  beginTime => '20190618.143658'}, # 	2019-06-18	14:36:58	2019-06-18	22:20:09
#'1166' => {trig=>'7.3GeV_fixedTarget_2019',	field => 'RF',	first=> '20169052',	 last => '20169055',	 list => '',  beginTime => '20190619.000404'}, # 	2019-06-19	00:04:04	2019-06-19	02:51:26
#'1167' => {trig=>'7p7GeV_2019',        	field => 'RF',	first=> '20169058',	 last => '20169060',	 list => '',  beginTime => '20190619.025126'}, # 	2019-06-19	02:51:26	2019-06-19	04:18:08
#'1203' => {trig=>'7p7GeV_2019',        	field => 'RF',	first=> '20178009',	 last => '20178014',	 list => '',  beginTime => '20190627.075110'}, # 	2019-06-27	07:51:10	2019-06-28	08:19:31
#'1204' => {trig=>'9p2GeV_2019',        	field => 'RF',	first=> '20179015',	 last => '20179026',	 list => '',  beginTime => '20190628.081931'}, # 	2019-06-28	08:19:31	2019-06-28	14:32:40
#'1205' => {trig=>'9p2GeV_2019',        	field => 'RF',	first=> '20179028',	 last => '20179028',	 list => '',  beginTime => '20190628.143240'}, # 	2019-06-28	14:32:40	2019-06-29	03:28:34
#'1206' => {trig=>'4p59GeV_fixedTarget_2019',	field => 'RF',	first=> '20179039',	 last => '20179041',	 list => '',  beginTime => '20190629.032834'}, # 	2019-06-29	03:28:34	2019-06-29	04:38:17
#'1222' => {trig=>'4p59GeV_fixedTarget_2019',	field => 'RF',	first=> '20183020',	 last => '20183025',	 list => '',  beginTime => '20190702.103243'}, # 	2019-07-02	10:32:43	2019-07-02	14:41:51
#'1223' => {trig=>'9p2GeV_2019',        	field => 'RF',	first=> '20183026',	 last => '20183026',	 list => '',  beginTime => '20190702.144151'}, # 	2019-07-02	14:41:51	2019-07-02	15:03:34
#'1260' => {trig=>'9p2GeV_2019',        	field => 'RF',	first=> '20189012',	 last => '20189017',	 list => '',  beginTime => '20190708.073906'}, # 	2019-07-08	07:39:06	2019-07-09	03:23:12
#'1261' => {trig=>'31GeV_fixedTarget_2019',	field => 'RF',	first=> '20189035',	 last => '20189035',	 list => '',  beginTime => '20190709.032312'}, # 	2019-07-09	03:23:12	2019-07-09	03:36:39
#'1266' => {trig=>'31GeV_fixedTarget_2019',	field => 'RF',	first=> '20190018',	 last => '20190024',	 list => '',  beginTime => '20190709.103011'}, # 	2019-07-09	10:30:11	2019-07-10	11:01:57
#'1267' => {trig=>'AuAu200_2019',       	field => 'RF',	first=> '20191005',	 last => '20191005',	 list => '',  beginTime => '20190710.110157'}, # 	2019-07-10	11:01:57	2019-07-10	11:40:57
#'1276' => {trig=>'AuAu200_2019',       	field => 'RF',	first=> '20193025',	 last => '20193026',	 list => '',  beginTime => '20190712.191209'}, # 	2019-07-12	19:12:09	2019-07-15	08:51:41
#'1277' => {trig=>'9p2GeV_2019',        	field => 'RF',	first=> '20196006',	 last => '20196006',	 list => '',  beginTime => '20190715.085141'}, # 	2019-07-15	08:51:41	2019-07-15	09:28:55
#'1280' => {trig=>'9p2GeV_2019',        	field => 'RF',	first=> '20196015',	 last => '20196017',	 list => '',  beginTime => '20190715.103049'}, # 	2019-07-15	10:30:49	2019-07-15	11:43:38


# 10/31/19 dEdx905 new TcpSecRowB
# 11/01/19 dEdx906 new TpcRowQ, account aging
# 11/01/19 dEdx907 new TcpSecRowB
# 11/01/19 dEdx908 new TcpZCorrection
# 11/02/19 dEdx909 new TcpZCorrection
# 11/03/19 dEdx910 no TcpZCorrection
# 11/04/19 dEdx911 no TcpZCorrection, TpcSecRowB
# 11/05/19 dEdx912 add TcpSecRowB
# 11/07/19 dEdx913 add TcpZCorrection
# 11/08/19 dEdx914 fix bug in TcpZCorrection
# 11/10/19 dEdx917 new update for TpcSecRowB
# 11/11/19 dEdx918 reiterte 19GeV
# 11/13/19 dEdx921 no TcpZCorrection, TpcSecRowB
# 11/14/19 dEdx922 add TpcSecRowB per trigger setup
# 11/15/19 dEdx923 update TpcSecRowB per trigger setup
# 11/17/19 dEdx924 add TpcZCorrecion
# 11/18/19 dEdx925 update TpcSecRowB per trigger setup
# 11/19/19 dEdx926 add TpcPadCorrectionMDF
# 11/20/19 dEdx927 add TpcLengthCorrectionMDF (problems with production_3p85GeV_fixedTarget_2019 and production_7.3GeV_fixedTarget_2019)
# 11/23/19 dEdx928 check constants pt in MySQL
#$hist = "Run303"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/30/2019  reduce pMom interal, do only Negative particles
#$hist = "Run304"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/31/2019  reset TpcdXCorrection, TpcZCorrectionB, TpcSecRowB
#$hist = "Run305"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/01/2019  new TpcSecRowB
#$hist = "Run306"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/01/2019  new new TpcSecRowB
#$hist = "Run307"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/01/2019  add year to dEdx.C parameters
#$hist = "Run310"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/04/2019 split TpcSecRowB
#$hist = "Run312"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/05/2019  iTpcOnly
#$hist = "Run313"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/05/2019  TpcZCorrection
#$hist = "Run314"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/06/2019  TpcSecRowB*
#$hist = "Run315"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/07/2019 split negative and positive particles in TPoints hisograms
#$hist = "Run316"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/07/2019 TpcLengthCorrectionMDF.20180518.000315.C
#$hist = "Run317"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/10/2019 move to MySQL and check in dev
#$hist = "Run318"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/18/2019 move to MySQL and check in dev before code commit
#$hist = "Run319"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/19/2019 move to MySQL and check in dev after code commit
#$hist = "Run320"; $NEvents = 2000; $disk = "data4?/"; $RECO = "reco/production*_2018/*FullField";  $Production = "/P19id_calib"; $year = "/2018/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/28/2019 check option without dN/dx
#$hist = "Run321"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_19GeV_2019/ReversedFullField";  $Production = "/P20ic_calib"; $year = "/2019/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 06/28/20 test calibration
#$hist = "Run322"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_19GeV_2019/ReversedFullField";  $Production = "/P20ic_calib"; $year = "/2019/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 06/29/20 TpcRowQ from channel
#$hist = "Run323"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_19GeV_2019/ReversedFullField";  $Production = "/P20ic_calib"; $year = "/2019/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 06/30/20 TpcRowQ per channel and sector 
#$hist = "Run324"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_19GeV_2019/ReversedFullField";  $Production = "/P20ic_calib"; $year = "/2019/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/01/20 TpcSecRowB
#$hist = "Run325"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_19GeV_2019/ReversedFullField";  $Production = "/P20ic_calib"; $year = "/2019/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/01/20 reset TpcPadCorrectionMDF and TpcPadCorrection
#$hist = "Run326"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_19GeV_2019/ReversedFullField";  $Production = "/P20ic_calib"; $year = "/2019/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/02/20 rerun reset TpcPadCorrectionMDF and TpcPadCorrection
#$hist = "Run327"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_19GeV_2019/ReversedFullField";  $Production = "/P20ic_calib"; $year = "/2019/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/02/20 new TpcPadCorrectionMDF 
#$hist = "Run328"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_19GeV_2019/ReversedFullField";  $Production = "/P20ic_calib"; $year = "/2019/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/03/20 new TpcLengthCorrectionMDF and TcpSecRowB
#$hist = "Run329"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_19GeV_2019/ReversedFullField";  $Production = "/P20ic_calib"; $year = "/2019/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/04/20 new TpcLengthCorrectionMDF and TpcSecRowB bug in Run328
#$hist = "Run330"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_19GeV_2019/ReversedFullField";  $Production = "/P20ic_calib"; $year = "/2019/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/05/20 new TpcSecRowB 
#$hist = "Run331"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/production_19GeV_2019/ReversedFullField";  $Production = "/P20ic_calib"; $year = "/2019/*/*/"; $FILE = "st_"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/08/20 check dev  
#                                           /gpfs01/star/data100/reco/production_19GeV_2019/ReversedFullField/P21ia_calib/2019
#$hist = "RunXIX01"; $NEvents = 2000; $disk = "data*/"; $RECO = "/reco/production_19GeV_2019/ReversedFullField";  $Production = "/P21ia_calib"; $year = "/2019/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 03/18/21 Test production with alignment from Run XX
################## Run XX ##############################################################
# 11p5GeV                 20191208.100905, 20191221.190032, 20200210.220428, 20200214.143742, 20200214.143742
# 5p75GeV_fixedTarget     20191221.154021, 
# 31p2GeV_fixedTarget     20200128.182912
# 9p8GeV_fixedTarget      20200130.005840, 20200131.050328, 20200131.050328
# 9p2GeV                  20200131.012112, 20200131.012112, 20200203.20253
# 19p5GeV_fixedTarget     20200201.191904
# 13p5GeV_fixedTarget     20200202.160409x[
# 7p3GeV_fixedTarget      20200204.053518
# 9p2GeV                  20200205.144626
# 5p75GeV_fixedTarget     20200213.152339, 20200213.152339
# 9p2GeVb                 20200224.230740
#$hist = "RunXX00"; $NEvents = 2000; $disk = "/hlt/cephfs/reco/2020/TFG20b/RF"; $RECO = "/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 03/23/20 check 
#$hist = "RunXX01"; $NEvents = 2000; $disk = "/hlt/cephfs/reco/2020/TFG20b/RF"; $RECO = "/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 03/29/20 check, adjust time limits
#$hist = "RunXX02"; $NEvents = 2000; $disk = "/hlt/cephfs/reco/2020/TFG20b/RF"; $RECO = "/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 03/31/20 reset TpcZCorrectionB, TpcSecRowB, TpcLengthCorrectionMDF
#$hist = "RunXX03"; $NEvents = 2000; $disk = "/hlt/cephfs/reco/2020/TFG20b/RF"; $RECO = "/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 04/01/20 new TpcSecRowB
#$hist = "RunXX04"; $NEvents = 2000; $disk = "/hlt/cephfs/reco/2020/TFG20b/RF"; $RECO = "/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 04/02/20 new TpcSecRowB.20191121.000003.root
#$hist = "RunXX05"; $NEvents = 2000; $disk = "/hlt/cephfs/reco/2020/TFG20b/RF"; $RECO = "/*/";  $Production = "*"; $year = "1/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 04/08/20 new TpcAdcCorrectionMDF.r2020.C (lAdc, npad+ntbkt)
#$hist = "RunXX06"; $NEvents = 2000; $disk = "/hlt/cephfs/reco/2020/TFG20b/RF"; $RECO = "/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 04/09/20 new TpcSecRowB.20191121.000005.root
#$hist = "RunXX07"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20b/RF"; $RECO = "/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 04/10/20 new TpcZCorrectionB.*GeV*.C
#$hist = "RunXX08"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20b/RF"; $RECO = "/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 04/10/20 new TpcSecRowB.20191121.000007.root
#$hist = "RunXX09"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20b/RF"; $RECO = "/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 04/11/20 new TpcLengthCorrectionMDF.*.C
#$hist = "RunXX10"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20b/RF"; $RECO = "/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 06/05/20   AdcCorrection3MDF
#$hist = "RunXX11"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20b/RF"; $RECO = "/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 06/06/20   TpcSecRowB.20191121.000010.root
#$hist = "RunXX12"; $NEvents = 200; $disk = "/hlt/cephfs/reco/2020/TFG20b/RF"; $RECO = "/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 06/07/20   Test TpcZCorrectionB
#$hist = "RunXX13"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20b/RF"; $RECO = "/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 06/07/20   AdcCorrection3MDF
#$hist = "RunXX14"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20b/RF"; $RECO = "/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 06/08/20   Z correction
#$hist = "RunXX15"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20b/RF"; $RECO = "/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 06/08/20   SecRowB  Good enough
#$hist = "RunXX16"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20b/RF"; $RECO = "/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 06/09/20   switch off TpcPadCorrectionMDF
#$hist = "RunXX17"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20b/RF"; $RECO = "/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 06/10/20   new TpcPadCorrectionMDF
#$hist = "RunXX18"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20b/RF"; $RECO = "/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 06/10/20   new TpcLengthCorrectionMDF
#$hist = "RunXX19"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20b/RF"; $RECO = "/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 06/11/20  once again  new TpcLengthCorrectionMDF
#$hist = "RunXX20"; $NEvents = 2000; $disk = "/hlt/cephfs/reco/2020/TFG20b/RF"; $RECO = "/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/26/20  revisit, check statistics
#$hist = "RunXX21"; $NEvents = 2000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 07/26/20  revisit, check statistics
#$hist = "RunXX22"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";# 09/11/20  revisit, check statistics
#$hist = "RunXX23"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20h/RF"; $RECO = "/*/";  $Production = "*"; $year = "/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/27/20  revisit, check adc production
#$hist = "RunXX30"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";# 10/03/20  start from scratch
#$hist = "RunXX31"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";# 10/06/20  add scale to TpcAdcCorrection3MDF.r2020.C
#$hist = "RunXX32"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/07/20  TpcSecRowB.20191121.000031.root

#$hist = "RunXX33"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";# 10/08/20  reset Adc3MDF to zero, reset TpcSecRowB

#$hist = "RunXX34"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";# 10/09/20  TpcSecRowB.20191121.000033.root
#$hist = "RunXX35"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";# 10/09/20  TpcSecRowB.20191121.000033.root
#$hist = "RunXX36"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";# 11/21/20  check status 
#$hist = "RunXX37"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = "TFG20k"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";# 11/29/20  check space charge
#$hist = "RunXX40"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = "TFG20k"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";# 01/20/21 back to RunXX30
#$hist = "RunXX41"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = "TFG20k"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";# 01/21/21 remove  TpcAdcCorrectionMDF.20191120.180000.C and TpcSecRowB.20191121.000033.root
#$hist = "RunXX42"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = "TFG20k"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";# 01/22/21 mv TpcAdcCorrectionMDF.r2020.C TpcAdcCorrectionMDF.r2020.C.HOLD.012221
#$hist = "RunXX43"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = "TFG20k"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";# 01/23/21 restart from .DEV2.081520/StarDb/Calibrations/tpc 
# Problem with secrot 19 row 1-19 ??? TpcAdcCorrection3MDF.y2020.C ???. save StarDb/Calibrations/tpc to  tpc.012521/
# remove  TpcAdcCorrection3MDF.y2020.C and TpcAdcCorrectionMDF.r2020.C i.e. use TpcAdcCorrectionB.y2019.C for Run XX
#$hist = "RunXX50"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = "TFG20k"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";# 01/23/21 restart from express productioon TFG20a h with TpcAdcCorrectionB.y2019.C
#$hist = "RunXX50"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = "TFG20k"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";# 01/25/21 restart from express productioon TFG20a h with TpcAdcCorrectionB.y2019.C
# restore ln -s TpcAdcCorrectionB.y2019.C TpcAdcCorrectionB.y2020.C; mv TpcAdcCorrectionB.r2020.C TpcAdcCorrectionB.r2020.C.HOLD.012621
# TpcAdcCorrectionB.y2020.C
# TpcAvgPowerSupply.y2020.C
# TpcLengthCorrectionB.y2020.C
# TpcLengthCorrectionMDF.20191120.190003.C
# TpcLengthCorrectionMDF.y2020.C
# TpcPadCorrectionMDF.20191120.180016.C
# TpcPadCorrectionMDF.y2020.C
# TpcPadCorrection.y2020.C
# TpcRowQ.y2019.C
# TpcRowQ.y2020.C
# TpcSecRowB.20191120.190002.root
# TpcZCorrectionB.20191120.190001.C
#$hist = "RunXX51"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = "TFG20k"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";# 01/26/21 
# TpcAdcCorrectionB.y2020.C : empty TpcAdcCorrectionMDF.C, TpcAdcCorrection3MDF
# TpcAccumulatedQ Validity:20190225/322 -----   20371231/120000 ??
# TpcSecRowB.20191120.190050.C
# tpcGainCorrection Validity:20181220/0  ??
#$hist = "RunXX52"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG21b/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 01/27/21  repeat with TFG21b
#$hist = "RunXX53"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";# 01/27/21 reset TpcAccumulatedQ
#$hist = "RunXX54"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";# 01/27/21 TpcSecRowB.20191121.000053.root
#$hist = "RunXX55"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";# 01/28/21 TpcZCorrectionB*RunXX054*
#$hist = "RunXX56"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 01/29/21 new TpcSecRowB for COL and FXT
#$hist = "RunXX57"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 01/29/21 split Z3 for negative and positive tracks
#$hist = "RunXX58"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 01/30/21 fix bug for Z3 plots
#$hist = "RunXX59"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 01/31/21 TpcPadCorrectionMDF.20191120.180058.C
# dE/dx Tables               2019 TFG19e            2020 TFG20a     2021  .DEV2
# TpcAccumulatedQ            2019-02-25 00:03:22    default         default
# TpcAdcCorrectionB          y2019                  r2020           r2021-> r2020
# TpcAdcCorrection3MDF       default
# tpcAltroParams             y2019                  y2020           y2021
# tpcGainCorrection          2018-12-20 00:00:00    -"-             -"-
# TpcLengthCorrectionB       default since 2015-01-31 00:00:08
# TpcLengthCorrectionMDF     2019-02-01+ FXT        20191120.190003->y2021
# TpcdXCorrectionB           default                -"-             -"-
# TpcPadCorrection           default                -"-             -"-
# TpcPadCorrectionMDF        2019-02-02 00:03:26    20191120.180058->r2021
# TpcRowQ                    2019-02-25 00:03:21    default         -"- 
# TpcSecRowB                 2019-02-01+ FXT        20191210 +FXT   r2021.root -> TpcSecRowB.20191120.190002.root
# TpcSecRowC                 default
# TpcTanL                    default
# tpcPressureB               2019-02-01 00:07:03    -"-             -"-
# tpcTimeDependence          default
# TpcZCorrectionB            2019-02-01+ FXT        20191210 +FXT   r2021.C -> TpcZCorrectionB.20191120.190001.C
# start from RunXIX
#$hist = "RunXX100"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/03/21 start from extpress production
#$hist = "RunXX101"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/04/21 start from scratch but still use TpcPadCorrectionMDF.20191120.180058.C (by mistake)
#$hist = "RunXX102"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/04/21 TpcSecRowB
#$hist = "RunXX103"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/05/21 TpcZCorrectionB linked
#$hist = "RunXX104"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/06/21 TpcZCorrectionB separated from RunXX102
#$hist = "RunXX105"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/06/21 redo with reset TpcPadCorrectionMDF.20191120.180104.C and TpcZCorrectionB.20191120.190104.C
#$hist = "RunXX106"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/07/21 TpcSecRowB for each trigger set
#$hist = "RunXX107"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/07/21  TpcZCorrectionB for each trigger set
#$hist = "RunXX108"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/07/21  new TpcSecRowB for each trigger set
#$hist = "RunXX109"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/08/21  new TpcPadCorrectionMDF for COL and FXT
#$hist = "RunXX110"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/08/21  new TpcSecRowB for each trigger set
#$hist = "RunXX111"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/08/21  fix bug with nrows = 50 in TpcAdcCorrectionB, fix problem with nrows in TpcAdcCorrectionB.20190201.000817.C
#$hist = "RunXX112"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/09/21 fix problem with nrows in TpcAdcCorrectionB.20190201.000817.C
#$hist = "RunXX113"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/10/21 add TpcPadCorrectionMDF.COL.C & TpcPadCorrectionMDF.FXT.C
#$hist = "RunXX114"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2020/TFG20g/RF"; $RECO = "/*GeV*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  02/11/21 check to respect to MySQL
######################################## Run XIX + XX
#$hist = "P21ib01"; $NEvents = 2000; $disk = "data*/"; $RECO = "reco/*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 04/11/21 Test production with alignment from Run XX and XXI
#$hist = "P21ib02"; $NEvents = 2000; $disk = "data97/"; $RECO = "reco/*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 04/26/21 Test production with alignment from Run XX and XXI
#$hist = "P21ib02_0"; $NEvents = 2000; $disk = "data97/"; $RECO = "reco/*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 04/29/21 Reset TpcAccumulatedQ.20190225.230000.C, TpcLengthCorrectionMDF.20190225.230000.C, TpcPadCorrectionMDF.20190225.230000.C, TpcRowQ.20190225.230000.C, TpcSecRowB.20190225.230000.C, TpcZCorrectionB.20190225.230000.C
#$hist = "P21ib02_2"; $NEvents = 2000; $disk = "data97/"; $RECO = "reco/*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 04/30/21  TpcSecRowB.20190225.230001.root
#$hist = "P21ib02_3"; $NEvents = 2000; $disk = "data97/"; $RECO = "reco/*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 05/01/21 TpcAccumulatedQ.20190225.230002.C
#$hist = "P21ib02_4"; $NEvents = 2000; $disk = "data97/"; $RECO = "reco/*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 05/03/21 TpcSecRowB.20190225.230003.root, TpcSecRowB.20190404.000003.root
#$hist = "P21ib02_5"; $NEvents = 2000; $disk = "data97/"; $RECO = "reco/*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 05/04/21 TpcZCorrectionB.20190225.230004.C
#$hist = "P21ib02_5"; $NEvents = 2000; $disk = "data97/"; $RECO = "reco/*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 05/04/21 TpcZCorrectionB.20190225.230004.C
#$hist = "P21ib02_6"; $NEvents = 2000; $disk = "data97/"; $RECO = "reco/*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 05/05/21 fix bug TpcZCorrectionB.20190225.230004.C
#$hist = "P21ib02_7"; $NEvents = 1000; $disk = "data97/"; $RECO = "reco/*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 05/06/21 TpcSecRowB.20190404.000006.root & TpcSecRowB.20190225.230006.root
#$hist = "P21ib02_8"; $NEvents = 1000; $disk = "data97/"; $RECO = "reco/*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 05/07/21 disable TpcSecRowB.20190404.000006.root & TpcSecRowB.20190225.230006.root, new TpcZCorrectionB.20190225.230004.C
#$hist = "P21ib02_9"; $NEvents = 1000; $disk = "data97/"; $RECO = "reco/*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 05/07/21 TpcSecRowB 20190225.230008.root & 20190404.000008.root
#$hist = "P21ib02_10"; $NEvents = 1000; $disk = "data97/"; $RECO = "reco/*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 05/08/21  TpcPadCorrectionMDF.20190225.230009.C
#$hist = "P21ib02_11"; $NEvents = 1000; $disk = "data97/"; $RECO = "reco/*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 05/08/21  TpcSecRowB.20190225.230010.root  TpcSecRowB.20190404.000010.root
#$hist = "P21ib02_12"; $NEvents = 2000; $disk = "data97/"; $RECO = "reco/*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 05/09/21 TpcLengthCorrectionMDF.20190225.230011.C TpcLengthCorrectionMDF.20190404.000011.C
#$hist = "P21ib02_13"; $NEvents = 2000; $disk = "data97/"; $RECO = "reco/*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 05/10/21 test with cleaned StarDb
#$hist = "P21ib02_14"; $NEvents = 2000; $disk = "data97/"; $RECO = "reco/*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = "adev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 05/11/21 test adev
#$hist = "P21ib02_15"; $NEvents = 2000; $disk = "data97/"; $RECO = "reco/*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 05/14/21 check with dev 
#$hist = "P21ib02_16"; $NEvents = 2000; $disk = "data97/"; $RECO = "reco/*19GeV*/ReversedFullField/";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = "SL21c"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/11/21 check with SL21c
#$hist = "P21ib02_17"; $NEvents = 1000; $disk = "data97/"; $RECO = "reco/*19GeV*/ReversedFullField/";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/12/21 reset TpcAccumulatedQ.20190225.230020.C -> TpcAccumulatedQ.C, TpcSecRowB.20190225.230020.root -> TpcSecRowB.20190225.230010.root.HOLD.ofl, TpcSecRowB.20190404.000020.root -> TpcSecRowB.20190225.230010.root.HOLD.ofl
#$hist = "P21ib02_17"; $NEvents = 1000; $disk = "data97/"; $RECO = "reco/*GeV*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/12/21 reset TpcAccumulatedQ.20190225.230020.C -> TpcAccumulatedQ.C, TpcSecRowB.20190225.230020.root -> TpcSecRowB.20190225.230010.root.HOLD.ofl, TpcSecRowB.20190404.000020.root -> TpcSecRowB.20190225.230010.root.HOLD.ofl => "P21ib02_21
#$hist = "P21ib02_22"; $NEvents = 1000; $disk = "data97/"; $RECO = "reco/*GeV*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/13/21 TpcAccumulatedQ.20190225.230021.C & TpcAccumulatedQ.20190404.000021.C
#$hist = "P21ib02_23"; $NEvents = 1000; $disk = "data97/"; $RECO = "reco/*GeV*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/14/21 TpcSecRowB.20210*.*22.root bug with 2021
#$hist = "P21ib02_24"; $NEvents = 1000; $disk = "data97/"; $RECO = "reco/*GeV*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/14/21 TpcSecRowB.20190*.*22.root
#$hist = "P21ib02_24"; $NEvents = 1000; $disk = "data97/"; $RECO = "reco/*GeV*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/15/21 TpcSecRowB.20190*.*22.root : mv TpcSecRowB.20190129.000022.root TpcSecRowB.20190225.230022.root
#$hist = "P21ib02_25"; $NEvents = 1000; $disk = "data97/"; $RECO = "reco/*GeV*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/16/21  add tpcTimeCorrection
#$hist = "P21ib02_26"; $NEvents = 1000; $disk = "data97/"; $RECO = "reco/*GeV*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/17/21  TpcSecRowB.20190*.*025.root
#$hist = "P21ib02_27"; $NEvents = 1000; $disk = "data97/"; $RECO = "reco/*GeV*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/17/21  TpcLengthCorrectionMDF.2019*26.C
#$hist = "P21ib02_28"; $NEvents = 1000; $disk = "data97/"; $RECO = "reco/*GeV*/ReversedFullField";  $Production = "/P21ib_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = "SL21c"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 08/18/21  check SL21c
# Lidia 09/21/2021 fixedTarget RunXIX and RunXX
#  Run 2019:
#
#/star/data100/reco/production_31GeV_fixedTarget_2019/ReversedFullField/P21ic_calib/2019/*/*
#/star/data100/reco/production_7.3GeV_fixedTarget_2019/ReversedFullField/P21ic_calib/2019/*/*
#/star/data100/reco/production_4p59GeV_fixedTarget_2019/ReversedFullField/P21ic_calib/2019/*/*
#
#  Run 2020 :
#
#/star/data100/reco/production_31p2GeV_fixedTarget_2020/ReversedFullField/P21ic_calib/2020/*/*
#/star/data100/reco/production_26p5GeV_fixedTarget_2020/ReversedFullField/P21ic_calib/2020/*/*
#/star/data100/reco/production_19p5GeV_fixedTarget_2020/ReversedFullField/P21ic_calib/2020/*/*
#/star/data100/reco/production_13p5GeV_fixedTarget_2020/ReversedFullField/P21ic_calib/2020/*/*
#/star/data100/reco/production_9p8GeV_fixedTarget_2020/ReversedFullField/P21ic_calib/2020/*/*
#/star/data100/reco/production_7p3GeV_fixedTarget_2020/ReversedFullField/P21ic_calib/2020/*/*
#/star/data100/reco/production_5p75GeV_fixedTarget_2020/ReversedFullField/P21ic_calib/2020/*/*

#7.3GeV_fixedTarget_2019   2019-04-17      13:34:01
#7.3GeV_fixedTarget_2019   2019-04-23      15:54:1
#31GeV_fixedTarget_2019    
#3p85GeV_fixedTarget_2019
#4p59GeV_fixedTarget_2019
#
#5p75GeV_fixedTarget_2020
#31p2GeV_fixedTarget_2020
#9p8GeV_fixedTarget_2020
#19p5GeV_fixedTarget_2020
#13p5GeV_fixedTarget_2020
#7p3GeV_fixedTarget_2020
#26p5GeV_fixedTarget_2020
#
#
#'0832'=> {trig=>'7.3GeV_fixedTarget',   field => 'RF',  first=> '20107029',      last => '20107029',     list => '',  beginTime => '20190417.133401'}, #        2019-04-17      13:34:01        2019-04-17      14:12:46
#'0865'=> {trig=>'7.3GeV_fixedTarget',   field => 'RF',  first=> '20113042',      last => '20113048',     list => '',  beginTime => '20190423.155418'}, #        2019-04-23      15:54:18        2019-04-23      18:11:58
#'1102'=> {trig=>'3p85GeV_fixedTarget',  field => 'RF',  first=> '20158041',      last => '20158042',     list => '',  beginTime => '20190607.174702'}, #        2019-06-07      17:47:02        2019-06-07      18:24:43
#'1113'=> {trig=>'3p85GeV_fixedTarget',  field => 'RF',  first=> '20160023',      last => '20160027',     list => '',  beginTime => '20190609.124528'}, #        2019-06-09      12:45:28        2019-06-10      02:41:09
#'1164'=> {trig=>'7.3GeV_fixedTarget',   field => 'RF',  first=> '20169028',      last => '20169045',     list => '',  beginTime => '20190618.143658'}, #        2019-06-18      14:36:58        2019-06-18      22:20:09
#'1206'=> {trig=>'4p59GeV_fixedTarget',  field => 'RF',  first=> '20179039',      last => '20179041',     list => '',  beginTime => '20190629.032834'}, #        2019-06-29      03:28:34        2019-06-29      04:38:17
#'1217'=> {trig=>'4p59GeV_fixedTarget',  field => 'RF',  first=> '20182006',      last => '20182018',     list => '',  beginTime => '20190701.081137'}, #        2019-07-01      08:11:37        2019-07-02      03:36:50
#'1261'=> {trig=>'31GeV_fixedTarget',    field => 'RF',  first=> '20189035',      last => '20189035',     list => '',  beginTime => '20190709.032312'}, #        2019-07-09      03:23:12        2019-07-09      03:36:39
#'1267'=> {trig=>'AuAu200',              field => 'RF',	 first=> '20191005',	  last => '20191005',	  list => '',  beginTime => '20190710.110157'}, # 	2019-07-10	11:01:57	2019-07-10	11:40:57
#'1276'=> {trig=>'AuAu200',       	 field => 'RF',	 first=> '20193025',	  last => '20193026',	  list => '',  beginTime => '20190712.191209'}, # 	2019-07-12	19:12:09	2019-07-15	08:51:41
# St_TpcSecRowCorC::instance found table TpcSecRowB with NRows = 24 in db   Validity:20190710/110157 - 20190715/85141
# MySQL [Calibrations_tpc]> select entryTime,elementID,beginTime,flavor,deactive from TpcSecRowB where elementID=1 and deactive = 0 and beginTime > "2019-01-01" order by beginTime limit 40;
# +---------------------+-----------+---------------------+--------+----------+
# | entryTime           | elementID | beginTime           | flavor | deactive |
# +---------------------+-----------+---------------------+--------+----------+
# | 2019-04-16 19:41:11 |         1 | 2019-02-01 00:00:03 | ofl    |        0 |
# | 2019-04-28 20:49:12 |         1 | 2019-02-01 00:07:07 | ofl    |        0 |
# | 2020-07-08 16:59:47 |         1 | 2019-02-25 20:23:29 | ofl    |        0 |
# | 2021-05-10 20:35:27 |         1 | 2019-02-25 23:00:10 | ofl    |        0 |
# | 2021-08-18 13:35:21 |         1 | 2019-02-25 23:00:25 | ofl    |        0 |
# | 2021-05-10 20:35:31 |         1 | 2019-04-04 00:00:10 | ofl    |        0 |
# | 2021-08-18 13:35:24 |         1 | 2019-04-04 00:00:25 | ofl    |        0 |
# | 2021-10-21 17:21:21 |         1 | 2019-04-04 09:44:05 | ofl    |        0 |
# | 2021-11-08 22:09:13 |         1 | 2019-04-17 13:34:01 | FXT    |        0 |
# | 2021-10-21 17:21:24 |         1 | 2019-04-17 14:12:46 | ofl    |        0 |
# | 2021-11-08 22:09:16 |         1 | 2019-04-23 15:54:18 | FXT    |        0 |
# | 2021-10-21 17:21:28 |         1 | 2019-04-23 18:11:58 | ofl    |        0 |
# | 2021-10-21 17:21:32 |         1 | 2019-06-03 22:36:55 | ofl    |        0 |
# | 2021-10-21 17:13:53 |         1 | 2019-06-07 17:47:02 | FXT    |        0 |
# | 2021-10-21 17:21:36 |         1 | 2019-06-07 20:22:44 | ofl    |        0 |
# | 2021-10-21 17:13:57 |         1 | 2019-06-09 12:45:28 | FXT    |        0 |
# | 2021-10-21 17:21:40 |         1 | 2019-06-10 02:41:09 | ofl    |        0 |
# | 2021-11-08 22:09:18 |         1 | 2019-06-18 14:36:58 | FXT    |        0 |
# | 2021-10-21 17:21:43 |         1 | 2019-06-19 02:51:26 | ofl    |        0 |
# | 2021-10-21 17:21:47 |         1 | 2019-06-28 08:19:31 | ofl    |        0 |
# | 2021-10-25 21:01:45 |         1 | 2019-06-29 03:28:34 | FXT    |        0 |
# | 2021-10-21 17:21:51 |         1 | 2019-07-02 14:41:51 | ofl    |        0 |
# | 2021-10-21 17:14:08 |         1 | 2019-07-09 03:23:12 | FXT    |        0 |
# | 2021-10-21 17:21:55 |         1 | 2019-07-10 11:01:57 | ofl    |        0 | AuAu200
# | 2021-10-21 17:21:59 |         1 | 2019-07-15 08:51:41 | ofl    |        0 |
# | 2021-02-11 15:47:50 |         1 | 2019-11-20 19:00:02 | ofl    |        0 |
# | 2021-02-11 15:47:52 |         1 | 2019-11-21 00:00:53 | ofl    |        0 |
# | 2021-02-11 15:47:55 |         1 | 2019-12-08 09:13:08 | ofl    |        0 |
# | 2021-10-21 17:14:12 |         1 | 2019-12-21 15:40:21 | FXT    |        0 |
# | 2021-02-11 15:48:00 |         1 | 2019-12-21 19:00:32 | ofl    |        0 |
#
#'161' => {trig=>'5p75GeV_fixedTarget',  field => 'RF',  first=> '20355020',      last => '20355021',     list => '',  beginTime => '20191221.154021'}, #        2019-12-21      15:40:21        2019-12-21      19:00:32
#'363' => {trig=>'31p2GeV_fixedTarget',  field => 'RF',  first=> '21028011',      last => '21028014',     list => '',  beginTime => '20200128.182912'}, #        2020-01-28      18:29:12        2020-01-28      20:30:12
#'374' => {trig=>'9p8GeV_fixedTarget',   field => 'RF',  first=> '21029051',      last => '21029057',     list => '',  beginTime => '20200130.005840'}, #        2020-01-30      00:58:40        2020-01-30      05:57:48
#'379' => {trig=>'9p8GeV_fixedTarget',   field => 'RF',  first=> '21031001',      last => '21031016',     list => '',  beginTime => '20200131.050328'}, #        2020-01-31      05:03:28        2020-02-01      03:03:39
#'387' => {trig=>'19p5GeV_fixedTarget',  field => 'RF',  first=> '21032046',      last => '21032057',     list => '',  beginTime => '20200201.191904'}, #        2020-02-01      19:19:04        2020-02-02      04:45:46
#'392' => {trig=>'13p5GeV_fixedTarget',  field => 'RF',  first=> '21033026',      last => '21033027',     list => '',  beginTime => '20200202.160409'}, #        2020-02-02      16:04:09        2020-02-02      18:15:15
#'399' => {trig=>'7p3GeV_fixedTarget',   field => 'RF',  first=> '21035003',      last => '21035007',     list => '',  beginTime => '20200204.053518'}, #        2020-02-04      05:35:18        2020-02-04      10:26:17
#'461' => {trig=>'5p75GeV_fixedTarget',  field => 'RF',  first=> '21044023',      last => '21044025',     list => '',  beginTime => '20200213.152339'}, #        2020-02-13      15:23:39        2020-02-13      15:50:47
#'889' => {trig=>'26p5GeV_fixedTarget',  field => 'RF',  first=> '21211028',      last => '21211028',     list => '',  beginTime => '20200730.015354'}, #        2020-07-30      01:53:54        2020-07-30      04:28:36
#'966' => {trig=>'26p5GeV_fixedTarget',  field => 'RF',  first=> '21226023',      last => '21226036',     list => '',  beginTime => '20200813.213251'}, #        2020-08-13      21:32:51        2020-08-14      05:43:57
#'1000' => {trig=>'26p5GeV_fixedTarget', field => 'RF',  first=> '21232025',      last => '21232025',     list => '',  beginTime => '20200819.192253'}, #        2020-08-19      19:22:53        2020-08-20      05:54:02
#'1045' => {trig=>'26p5GeV_fixedTarget', field => 'RF',  first=> '21240017',      last => '21240019',     list => '',  beginTime => '20200827.143507'}, #        2020-08-27      14:35:07        2020-08-27      17:13:37
#'1104' => {trig=>'26p5GeV_fixedTarget', field => 'RF',  first=> '21251020',      last => '21251023',     list => '',  beginTime => '20200907.221141'}, #        2020-09-07      22:11:41        2020-09-08      02:38:05
#'1122' => {trig=>'26p5GeV_fixedTarget', field => 'RF',  first=> '21256006',      last => '21256010',     list => '',  beginTime => '20200912.102033'}, #        2020-09-12      10:20:33        2020-09-12      14:28:50
#'1131' => {trig=>'26p5GeV_fixedTarget', field => 'RF',  first=> '21257029',      last => '21257031',     list => '',  beginTime => '20200913.171430'}, #        2020-09-13      17:14:30        2020-09-13      20:26:47
#
#$hist = "P21ic_calib_30"; $NEvents = 10000; $disk = "data100/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/21/2021 check Run XIX and Run XX fixedTarget
#$hist = "P21ic_calib_31"; $NEvents = 10000; $disk = "data100/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/21/2021 check Run XIX and Run XX fixedTarget
#$hist = "P21ic_calib_32"; $NEvents = 10000; $disk = "data100/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = "TFG21l"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/21/2021 check Run XIX and Run XX fixedTarget
#$hist = "P21ic_calib_33"; $NEvents = 10000; $disk = "data100/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/21/2021 check Run XIX and Run XX fixedTarget
#$hist = "P21ic_calib_34"; $NEvents = 10000; $disk = "data100/"; $RECO = "reco/*GeV_fixedTarget*2019/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/21/2021 check Run XIX and Run XX fixedTarget
#$hist = "P21ic_calib_35"; $NEvents = 10000; $disk = "data100/"; $RECO = "reco/*GeV_fixedTarget*2019/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/21/2021 check Run XIX and Run XX fixedTarget
#$hist = "P21ic_calib_36"; $NEvents = 10000; $disk = "data100/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 09/27/2021 use scheme with usedx2 TRUE
################################################################################
#$hist = "FXT00"; $NEvents = 10000; $disk = "/hlt/cephfs/";  $RECO = "reco/20*/*F"; $Production = "/TFG21l"; $year = "/*fixed*/"; $FILE = ""; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  10/02/2021 recheck 
#$hist = "FXT01"; $NEvents = 10000; $disk = "/hlt/cephfs/";  $RECO = "reco/20*/*F"; $Production = "/TFG21l"; $year = "/*fixed*/"; $FILE = ""; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  10/02/2021 recheck fix histograms
#$hist = "P21ic_calib_37"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/09/21 use scheme with usedx2 TRUE with calib sample
#$hist = "P21ic_calib_40"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/11/21 reset all 
#$hist = "P21ic_calib_41"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/12/21  TpcSecRowB.2020fixedTarget.root & TpcSecRowB.2019fixedTarget.root
#$hist = "P21ic_calib_42"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/12/21  TpcZCorrectionC
#$hist = "P21ic_calib_43"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/13/21  TpcSecRowB.*GeV*fixedTarget*
#$hist = "P21ic_calib_44"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/13/21  TpcLengthCorrectionMD2.fixedTarget_2019.C & TpcLengthCorrectionMD2.fixedTarget_2020.C
#$hist = "P21ic_calib_45"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/14/21  fix bug with correction for kTpcLengthCorrectionMD2
#$hist = "P21ic_calib_46"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/18/21 check MySQL 
#$hist = "P21ic_calib_47"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = "adev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/19/21 check MySQL  with adev
#$hist = "P21ic_calib_48"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/19/21 check MySQL fix TpcSecRowB for fixedTarget Run XX in MySQL
#$hist = "P21ic_calib_49"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = "adev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/19/21 check MySQL  with adev after MySQL fix
#$hist = "P21ic_calib_50"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/19/21 restore cint files from hold.P21ic_calib.45
#$hist = "P21ic_calib_51"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/20/21 restore all cint files from hold.P21ic_calib.45 and set DbV20211017
#$hist = "P21ic_calib_52"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/21/21 check MySQL with DbV DbV20211017
#$hist = "P21ic_calib_53"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/21/21 check MySQL without DbV DbV20211017
#$hist = "P21ic_calib_55"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/21/21 check MySQL fix problem with flavor ="fxt0" only for elementID=1
#$hist = "P21ic_calib_56"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/23/21 update TpcSecRowB for 26p5GeV_fixedTarget_2020 and 4p59GeV_fixedTarget_2019
#$hist = "P21ic_calib_57"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*4p59GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/24/21 TpcSecRowB.20190629.032834.root -> TpcSecRowB.4p59GeV_fixedTarget_2019.root
#$hist = "P21ic_calib_58"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*4p59GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/25/21 TpcSecRowB.20190629.032834.root -> TpcSecRowB.4p59GeV_fixedTarget_2019.root from P51
#$hist = "P21ic_calib_59"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*4p59GeV_fixedTarget*/RxseversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/25/21 TpcZCorrectionC.20190629.032834.C -> /net/l402/data/fisyak/STAR/packages/.DEV2/xchold/StarDb/Calibrations/tpc/P21ic_calib_51/TpcZCorrectionC.20190629.032834.C
#$hist = "P21ic_calib_60"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/25/21 check with MySQL
#$hist = "P21ic_calib_61"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = "adev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/25/21 check with adev
#$hist = "P21ic_calib_62"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*4p59GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/25/21 check with MySQL
#$hist = "P21ic_calib_63"; $NEvents = 10000; $disk = "data100/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/25/21 check with adev
#$hist = "P21ic_calib_64"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/29/21 check MySQL after fixing beamInfo isFixedTarget
#$hist = "P21ic_calib_65"; $NEvents = 10000; $disk = "data100/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/03/21 check with  dev
#$hist = "P21ic_calib_66"; $NEvents = 10000; $disk = "/hlt/cxsephfs/"; $RECO = "reco/*7.3GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/29/21 check MySQL after fixing beamInfo isFixedTarget
#$hist = "P21ic_calib_67"; $NEvents = 10000; $disk = "data100/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/08/21 check with  dev after fix 7.3GeV_fixedTarge_2019

#$hist = "RunXIX68"; $NEvents = 10000; $disk = "data*/"; $RECO = "reco/*GeV*/ReversedFullField";  $Production = "/P2*_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 01/19/22 check whole Run XIX for Alive / Active
#$hist = "RunXIX69"; $NEvents = 10000; $disk = "data*/"; $RECO = "reco/*GeV*/ReversedFullField";  $Production = "/P2*_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 01/30/22 check whole Run XIX for Alive / Active with removed masked out RDOs

#$hist = "RunXIX70"; $NEvents = 10000; $disk = "data*/"; $RECO = "reco/*GeV*/ReversedFullField";  $Production = "/P2*_calib"; $year = "/2019/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/02/22 check new itpcPadGainT0 for Run XIX
#$hist = "RunXIX71"; $NEvents = 10000; $disk = "data*/"; $RECO = "reco/*GeV*/ReversedFullField";  $Production = "/P2*_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/03/22 check new itpcPadGainT0 for Run XIX & XX in DB
#$hist = "RunXIX71"; $NEvents = 10000; $disk = "data*/"; $RECO = "reco/*AuAu200*/ReversedFullField";  $Production = "/P21id"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/17/22 checkAuAu200
#$hist = "RunXIX72"; $NEvents = 10000; $disk = "data*/"; $RECO = "reco/production_AuAu200_2019/ReversedFullField";  $Production = "/P21id"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/17/22 SecRow3C
#$hist = "RunXIX73"; $NEvents = 10000; $disk = "data*/"; $RECO = "reco/production_AuAu200_2019/ReversedFullField";  $Production = "/P21id"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/24/22 TpcZCorrectionC.20190710.110157.C
#$hist = "RunXIX74"; $NEvents = 10000; $disk = "data*/"; $RECO = "reco/production_AuAu200_2019/ReversedFullField";  $Production = "/P21id"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/26/22 +  SecRow3+SecRow3PGFAuAu200_2019.root => TpcSecRowB.20190710.110158.root
#$hist = "RunXIX75"; $NEvents = 20000; $step = 2000; $disk = "data*/"; $RECO = "reco/production_AuAu200_2019/ReversedFullField";  $Production = "/P21id"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/26/22 +  reduce range for TpcZCorrectionC
#$hist = "RunXIX76"; $NEvents = 20000; $step = 1000; $disk = "data*/"; $RECO = "reco/production_AuAu200_2019/ReversedFullField";  $Production = "/P21id"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 03/01/22 +  reduce range for TpcZCorrectionC, activate range 
#$hist = "RunXIX77"; $NEvents = 20000; $step = 1000; $disk = "data*/"; $RECO = "reco/production_AuAu200_2019/ReversedFullField";  $Production = "/P21id"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 03/01/22 new TpcZCorrectionC,RunXIX76 and TpcLengthCorrectionMD2.AuAu200_2019.C
#$hist = "RunXIX78"; $NEvents = 20000; $step = 1000; $disk = "data*/"; $RECO = "reco/production_AuAu200_2019/ReversedFullField";  $Production = "/P21id"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 03/02/22 new TpcZCorrectionC,RunXIX76 and fix bug in  TpcLengthCorrectionMD2.AuAu200_2019.C
#$hist = "RunXIX79"; $NEvents = 20000; $step = 1000; $disk = "data*/"; $RECO = "reco/production_AuAu200_2019/ReversedFullField";  $Production = "/P21id"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 03/02/22 new RunXIX78/TpcSecRowB.20190710.110158.root
#$hist = "RunXIX80"; $NEvents = 20000; $step = 1000; $disk = "data*/"; $RECO = "reco/production_AuAu200_2019/ReversedFullField";  $Production = "/P21id"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 03/04/22 new TpcLengthCorrectionMD2.AuAu200_2019.C
#$hist = "RunXIX81"; $NEvents = 20000; $step = 1000; $disk = "data*/"; $RECO = "reco/production_AuAu200_2019/ReversedFullField";  $Production = "/P21id"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 03/06/22 check wrt dev
#$hist = "RunXIX82"; $NEvents = 1000;  $disk = "data*/"; $RECO = "reco/production_19GeV_2019/ReversedFullField";  $Production = "/P2*calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 03/15/22 switch to TpcAdcCorrection3MDF
#$hist = "RunXIX83"; $NEvents = 1000;  $disk = "data*/"; $RECO = "reco/production_19GeV_2019/ReversedFullField";  $Production = "/P2*calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 03/16/22 TpcSecRowB.20190225.230026.root
#$hist = "RunXIX84"; $NEvents = 1000;  $disk = "data*/"; $RECO = "reco/production_19GeV_2019/ReversedFullField";  $Production = "/P2*calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 03/17/22 TpcZCorrectionC.20190225.0230005.C
#$hist = "RunXIX85"; $NEvents = 1000;  $disk = "data*/"; $RECO = "reco/production_19GeV_2019/ReversedFullField";  $Production = "/P2*calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 03/18/22 TpcZCorrectionC.20190225.0230005.C -> TpcZCorrectionC.19GeV_2019.C
#$hist = "RunXIX86"; $NEvents = 1000;  $disk = "data*/"; $RECO = "reco/production_19GeV_2019/ReversedFullField";  $Production = "/P2*calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 03/18/22 TpcZCorrectionC.20190225.0230005.C -> TpcZCorrectionC.19GeV_2019.C reduce Z range Inner [25,207], Outer [22,207]
#$hist = "RunXIX87"; $NEvents = 1000;  $disk = "data*/"; $RECO = "reco/production_19GeV_2019/ReversedFullField";  $Production = "/P2*calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 03/19/22 TpcSecRowB.20190225.230028.root
#$hist = "RunXIX88"; $NEvents = 1000;  $disk = "data*/"; $RECO = "reco/production_19GeV_2019/ReversedFullField";  $Production = "/P2*calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 03/19/22 TpcLengthCorrectionMD2.20190225.230026.C -> TpcLengthCorrectionMD2.19GeV_2019.C
######################################## Run XXI express calibration ########################################a
#$hist = "P21ic_calib_66"; $NEvents = 10000; $disk = "/hlt/cephfs/"; $RECO = "reco/*7.3GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 10/29/21 check MySQL after fixing beamInfo isFixedTarget
#$hist = "P21ic_calib_67"; $NEvents = 10000; $disk = "data100/"; $RECO = "reco/*GeV_fixedTarget*/ReversedFullField";  $Production = "/P21ic_calib"; $year = "/20*/*/*/"; $FILE = "st_"; $STAR_LEVEL = "dev"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 11/08/21 check with  dev after fix 7.3GeV_fixedTarge_2019
######################################## Run XXI express calibration ########################################
#$hist = "RunXXI01"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2021/RF/DEV2/"; $RECO = "/7p7GeV_2021.C/*/";  $Production = "*"; $year 22= "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/04/21 start from 2020 express production: strong Z dependence, and SecRow3 ~4%, xypad ~ 10%
#$hist = "RunXXI02"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2021/RF/DEV2/"; $RECO = "/7p7GeV_2021.C/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/04/21 reset date 20210129.000001: TpcLengthCorrectionMDF, TpcPadCorrectionMDF, TpcZCorrectionB
#$hist = "RunXXI03"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2021/RF/DEV2/"; $RECO = "/7p7GeV_2021.C/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/05/21 new TpcSecRowB.20210129.000002
#$hist = "RunXXI04"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2021/RF/DEV2/"; $RECO = "/7p7GeV_2021.C/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/05/21 new TpcZCorrectionB.20210129.000003.C
#$hist = "RunXXI05"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2021/RF/DEV2/"; $RECO = "/7p7GeV_2021.C/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/06/21 new TpcSecRowB.20210129.000004.root
#$hist = "RunXXI06"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2021/RF/DEV2/"; $RECO = "/7p7GeV_2021.C/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/06/21 TpcPadCorrectionMDF.20210129.000005.C
#$hist = "RunXXI07"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2021/RF/DEV2/"; $RECO = "/7p7GeV_2021.C/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/06/21 add TpcSecRowB.20210129.000006.root and TpcLengthCorrectionMDF.20210129.000006.C Done with express dE/dx calibration for Run XXI 7p7GeV
# Check effect of no TpcPdaCorrection correction.
######################################## Run XXI ########################################
#$hist = "RunXXI10"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2021/RF/TFG21c.B/"; $RECO = "/7p7GeV_2021/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/06/21 add TpcSecRowB.20210129.000006.root and TpcLengthCorrectionMDF.20210129.000006.C Done with express dE/dx calibration for Run XXI 7p7GeV
#$hist = "RunXXI10FF"; $NEvents = 10000; $disk = "/hlt/cephfs/reco/2021/FF/TFG21c.B"; $RECO = "/7p7GeV_2021/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 02/06/21 add TpcSecRowB.20210129.000006.root and TpcLengthCorrectionMDF.20210129.000006.C Done with express dE/dx calibration for Run XXI 7p7GeV
#$hist = "RunXXI11"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2021/RF/TFG21c.B/"; $RECO = "/7p7GeV_2021/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 04/01/21 recheck Time

#$hist = "RunXXI12"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2021/RF/TFG21e/"; $RECO = "/3p85GeV_fixedTarget_2021/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 05/03/21 recheck Time
#$hist = "RunXXI13"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2021/RF/TFG21e/"; $RECO = "/3p85GeV_fixedTarget_2021/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 05/04/21 TpcSecRowB.20210501.160000.root
#$hist = "RunXXI14"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2021/RF/TFG21e/"; $RECO = "/3p85GeV_fixedTarget_2021/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 05/05/21 TpcZCorrectionB.20210501.16013.C
#$hist = "RunXXI15"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2021/RF/TFG21e/"; $RECO = "/3p85GeV_fixedTarget_2021/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 05/05/21 TpcZCorrectionB.20210501.16013.C => TpcZCorrectionB.20210501.160013.C, default TpcLengthCorrectionMDF.C
#$hist = "RunXXI16"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2021/RF/TFG21e/"; $RECO = "/3p85GeV_fixedTarget_2021/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 05/05/21 TpcZCorrectionB.20210129.000003+20210501.160013.C = 160015, TpcLengthCorrectionMDF.C
#$hist = "RunXXI17"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2021/RF/TFG21e/"; $RECO = "/3p85GeV_fixedTarget_2021/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 05/05/21 TpcSecRowB.20210501.160016.root
#$hist = "RunXXI18"; $NEvents = 1000; $disk = "/hlt/cephfs/reco/2021/RF/TFG21e/"; $RECO = "/3p85GeV_fixedTarget_2021/*/";  $Production = "*"; $year = "/"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";# 05/07/21 reset TpcSecRowB to 7p7GeV, TpcZCorrectionB, TpcLengthCorrectionMDF to zero
#$hist = "RunXXI19"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TFG21e"; $year = "/*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  05/07/21 TpcSecRowB.20210501.160018.root
#$hist = "RunXXI20"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TFG21e"; $year = "/*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  05/07/21 TpcZCorrectionB.20210501.160019.C
#$hist = "RunXXI21"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TFG21e"; $year = "/*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  05/08/21 TpcSecRowB.20210501.160020.root  TpcSecRowB.20210506.000020.root
#$hist = "RunXXI22"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TFG21e"; $year = "/*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  05/08/21 TpcPadCorrectionMDF.20210501.160021.C clush with 2021-01-29 00:00:05
#$hist = "RunXXI23"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TFG21e"; $year = "/*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  05/09/21 disable TpcPadCorrectionMDF.20210501.160021.C
#$hist = "RunXXI24"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TFG21e"; $year = "/*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  05/11/21 TpcSecRowB.20210501.160023.root TpcSecRowB.20210506.000023.root TpcSecRowB.20210507.000023.root TpcSecRowB.20210508.000023.root TpcPadCorrectionMDF.20210501.160023.C
#$hist = "RunXXI25"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TFG21e"; $year = "/*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  05/12/21 TpcSecRowB.202105??.????24.root
#$hist = "RunXXI30"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";#  05/14/21 reset all constants for 2021
#$hist = "RunXXI32"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";#  05/15/21 TpcSecRowB.20210129.000031.root -> TpcSecRowB.20210129.000006.root
#$hist = "RunXXI33"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 10; $Mode = 2; $macro = "dEdx";#  05/18/21 add AdcI3, dZdY3, and dXdY3 histograms
#$hist = "RunXXI34"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";#  05/18/21 split AdcI3, dZdY3, and dXdY3 histograms for positive and negative 
#$hist = "RunXXI35"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/*GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";#  05/19/21 reshape AdcI versus signed row, add npad and ntimebuckets histograms
#$hist = "RunXXI36"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/*GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 10; $Mode = 2; $macro = "dEdx";#  05/20/21 fix npad and ntimebuckets histograms :: buggy
#$hist = "RunXXI37"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/*GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 10; $Mode = 2; $macro = "dEdx";#  05/20/21 fix npad and ntimebuckets histograms 
#$hist = "RunXXI38"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/*GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 5; $Mode = 2; $macro = "dEdx";#  05/21/21 add Tpc AdcI, nPad, and nTbk corrections
#$hist = "RunXXI39"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/*GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; $macro = "dEdx";#  05/23/21 fix mess with new corrections
#$hist = "RunXXI40"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/*GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; $macro = "dEdx";#  05/24/21 reset all correction except TpcSecRowB.20210129.000006.root
#$hist = "RunXXI40"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/ps_OO*GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 20; $Mode = 2; $macro = "dEdx";#  05/24/21 reset all corrections
#$hist = "RunXXI40"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/OO*GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 10; $Mode = 2; $macro = "dEdx";#  05/24/21 reset all corrections
#$hist = "RunXXI40"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/FF_OO*GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; $macro = "dEdx";#  05/24/21 reset all corrections
#$hist = "RunXXI40"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/7p7GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; $macro = "dEdx";#  05/24/21 reset all corrections
#$hist = "RunXXI40"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/*F"; $Production = "/TF*"; $year = "/*GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  05/24/21 reset all corrections
#$hist = "RunXXI41"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/*F"; $Production = "/TF*"; $year = "/7p7GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; $macro = "dEdx";#  05/27/21 reset all corrections __bug__
#$hist = "RunXXI41"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/*F"; $Production = "/TF*"; $year = "/3p85GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; $macro = "dEdx";#  05/27/21 reset all corrections
#$hist = "RunXXI42"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/7p7GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; $macro = "dEdx";#  05/28/21 reset all corrections
#$hist = "RunXXI42"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/3p85GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; $macro = "dEdx";#  05/28/21 reset all corrections
#$hist = "RunXXI43"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/7p7GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; $macro = "dEdx";#  05/29/21 TpcSecRowB.*42.root
#$hist = "RunXXI43"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/3p85GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; $macro = "dEdx";#  05/29/21 TpcSecRowB.*42.root
#$hist = "RunXXI44"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/7p7GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; $macro = "dEdx";#  05/29/21 TpcZCorrectionB.*43.C
#$hist = "RunXXI44"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/3p85GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; $macro = "dEdx";#  05/29/21 -"-
#$hist = "RunXXI45"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/7p7GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; $macro = "dEdx";#  05/30/31 TpcSecRowB.*44.root
#$hist = "RunXXI45"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/3p85GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; $macro = "dEdx";#  05/29/21 -"-
#$hist = "RunXXI46"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/7p7GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; $macro = "dEdx";#  05/30/31 reset to TpcSecRowB.20210129.000006.root
#$hist = "RunXXI46"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/3p85GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; $macro = "dEdx";#  05/30/21 -"-
#$hist = "RunXXI47"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/7p7GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 4; $Mode = 2; $macro = "dEdx";#  05/31/31 update TpcSecRowB.20210129.000046.root
#$hist = "RunXXI47"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/3p85GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; $macro = "dEdx";#  05/31/21 -"-
#$hist = "RunXXI48"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/7p7GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 4; $Mode = 2; $macro = "dEdx";#  05/31/31 update TpcZCorrectionB.*47.
#$hist = "RunXXI48"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/3p85GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; $macro = "dEdx";#  05/31/21 -"-
#$hist = "RunXXI49"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/7p7GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 4; $Mode = 2; $macro = "dEdx";#  06/01/31 update TpcnTbk & nPad*48.
#$hist = "RunXXI49"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/3p85GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; $macro = "dEdx";#  06/01/21 -"-
# TpcnTbk & nPad*48.C  does not work. Switch off 
#$hist = "RunXXI50"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/7p7GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 4; $Mode = 2; $macro = "dEdx";#  06/02/31 disable TpcnTbk & nPad*48. add TpcLengthCorrectionMDF*48.C
#$hist = "RunXXI50"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/3p85GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; $macro = "dEdx";#  06/01/21 -"-
#$hist = "RunXXI51"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/7p7GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 4; $Mode = 2; $macro = "dEdx";#  06/02/31 fix bug with Mask
#$hist = "RunXXI51"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/3p85GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; $macro = "dEdx";#  06/01/21 -"-
#$hist = "RunXXI52"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/7p7GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 4; $Mode = 2; $macro = "dEdx";#  06/03/31 Add TpcdZdY and TpcdXdy for 
#$hist = "RunXXI52"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/3p85GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; $macro = "dEdx";#  06/03/21 -"-
#$hist = "RunXXI53"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/7p7GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 4; $Mode = 2; $macro = "dEdx";#  06/04/31 Add update TpcSecRowB.*52.root
#$hist = "RunXXI53"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/3p85GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 2; $Mode = 2; $macro = "dEdx";#  06/04/21 -"-
#$hist = "RunXXI54"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/7p7GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  06/04/31 TpcPadCorrectionMDF.20210129.000053.C & TpcZCorrectionB.20210129.000053.C & TpcLengthCorrectionMDF.000053.C
#$hist = "RunXXI54"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/3p85GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  06/04/21 TpcdXdY TpcdZdY TpcLengthCorrectionMDF TpcPadCorrectionMDF TpcZCorrectionB 20210129.000053.C
#$hist = "RunXXI55"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/7p7GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  06/04/31 TpcSecRowB.*54.root TpcLengthCorrectionMDF.000054.C
#$hist = "RunXXI55"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/3p85GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  06/04/21 TpcSecRowB.20210501.160054.root ?xf
#$hist = "RunXXI56"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/3p85GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  06/05/21 step back to RunXXI53
#$hist = "RunXXI57"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/RF"; $Production = "/TF*"; $year = "/3p85GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  06/05/21 TpcSecRowB.20210501.160056.root
# $hist = "RunXXI100"
# $hist = "RunXXI101"
# $hist = "RunXXI102"
# $hist = "RunXXI200"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/*F"; $Production = "/TFG21h"; $year = "/*GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  08/07/21 - 08/09/21 Recheck 
# $hist = "RunXXI201"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2021/*F"; $Production = "/TFG21h"; $year = "/*GeV*/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  09/10/21 TpcZCorrectionC.y2021.C
# RunXX production_7p7GeV_2021
#$hist = "RunXXI202"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/production_7p7GeV_2021/ReversedFullField/";  $Production = "P22ia_calib"; $year = "/2021/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  04/25/2022 Check present status 
#$hist = "RunXXI203"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/production_7p7GeV_2021/ReversedFullField/";  $Production = "P22ia_calib"; $year = "/2021/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  04/25/2022 Check present status disable  TpcAdcCorrection3MDF.r2019.C
#$hist = "RunXXI204"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/production_7p7GeV_2021/ReversedFullField/";  $Production = "P22ia_calib"; $year = "/2021/*/*/"; $FILE = "st_"; $STAR_LEVEL = "SL22a"; $select = "*";  $keep = 10; $Mode = 2; $macro = "dEdx";#  04/25/2022 Check present status disable  TpcAdcCorrection3MDF.r2019.C
#$hist = "RunXXI205"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/production_7p7GeV_2021/ReversedFullField/";  $Production = "P22ia_calib"; $year = "/2021/*/*/"; $FILE = "st_"; $STAR_LEVEL = "TFG21l"; $select = "*";  $keep = 10; $Mode = 2; $macro = "dEdx";#  04/25/2022 Check present status disable  TpcAdcCorrection3MDF.r2019.C
#$hist = "RunXXI206"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/production_7p7GeV_2021/ReversedFullField/";  $Production = "P22ia_calib"; $year = "/2021/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  09/11/2022 Check constants obtained on HLT
#$hist = "RunXXI207"; $NEvents = 1000; $disk = "data*/"; $RECO = "reco/production_7p7GeV_2021/ReversedFullField/";  $Production = "P22ia_calib"; $year = "/2021/*/*/"; $FILE = "st_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  09/12/2022 TpcLengthCorrectionMDN TpcSecRowB TpcZCorrectionC
################################################################################
# Run XXII pp510_2022
# $hist = "RunXXII00"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2022/RF"; $Production = "/.DEV2"; $year = "/pp500_2022/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  01/16/22 Check
# $hist = "RunXXII01"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2022/RF"; $Production = "/.DEV2"; $year = "/pp500_2022/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  01/16/22 Check 03/01/22
# $hist = "RunXXII02"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2022/RF"; $Production = "/.DEV2"; $year = "/pp500_2022/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = "TFG22b"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  04/19/22 check whole pp500 sample
# $hist = "RunXXII03"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/2022/RF"; $Production = "/.DEV2"; $year = "/pp500_2022/*/*/*"; $FILE = "hlt_"; $STAR_LEVEL = "TFG22b"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  04/21/22 pcSecRowB.20211110.000002.root
################################################################################
#$hist = "RunXIX_XXII_01"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/20*/*F"; $Production = "/TFG22b"; $year = "/*GeV*/*/*/*"; $FILE = ""; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  05/01/2022 recheck with new calibration scheme  
#$hist = "RunXIX_XXII_02"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/20*/*F"; $Production = "/TFG22b"; $year = "/19GeV_2019/*/*/*"; $FILE = ""; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  05/06/22  reset all ctable to 19GeV_2019
#$hist = "RunXIX_XXII_02"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/20*/*F"; $Production = "/TFG22b"; $year = "/*GeV*/*/*/*"; $FILE = ""; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  05/06/22  reset all ctable to 19GeV_2019
#$hist = "RunXIX_XXII_03"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/20*/*F"; $Production = "/TFG22b"; $year = "/*GeV*/*/*/*"; $FILE = ""; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  05/08/22 TpcSecRowB for all BES-II + RunXXII samples 
#$hist = "RunXIX_XXII_04"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/20*/*F"; $Production = "/TFG22b"; $year = "/*GeV*/*/*/*"; $FILE = ""; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  05/09/22 TpcZCorrectionC for all BES-II + RunXXII samples 
#$hist = "RunXIX_XXII_05"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/20*/*F"; $Production = "/TFG22b"; $year = "/*GeV*/*/*/*"; $FILE = ""; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  05/10/22 new TpcSecRow & TpcLengthCorrectionMDN
#$hist = "RunXIX_XXII_06"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/20*/*F"; $Production = "/TFG22b"; $year = "/*GeV*/*/*/*"; $FILE = ""; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  05/16/22 MySQL versions
#$hist = "RunXIX_XXII_06"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/20*/*F"; $Production = "/TFG22b"; $year = "/*AuAu200*/*/*/*"; $FILE = ""; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  05/16/22 MySQL versions
#$hist = "RunXIX_XXII_07"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/20*/*F"; $Production = "/TFG22b"; $year = "/*GeV*/*/*/*"; $FILE = ""; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  05/24/22 more MySQL versions
$hist = "RunXIX_XXII_08"; $NEvents = 1000; $disk = "/hlt/cephfs/";  $RECO = "reco/20*/*F"; $Production = "/TFG22b"; $year = "/*GeV*/*/*/*"; $FILE = ""; $STAR_LEVEL = ".DEV2"; $select = "*";  $keep = 0; $Mode = 2; $macro = "dEdx";#  05/26/22 Check after fix with SecRow3 +/- and MIP selection

my $Year = $year;
if ($Year eq "/") {$Year = "2020";}
my @badruns = ();
my $prod = $hist; #$Production;
$prod =~ s/\*//g;
$prod =~ s/\//_/g;
print "prod $prod\n";
#$hist .= $prod;
$TOPSW = $Production;#"";#"dEdxA" . $Production; C for Central
my $Total_Size = 0;
my $script = "";
#my $CONDOR = "jobs.condor";
#open (CONDOR,">$CONDOR") or die "Can't open $CONDOR";
#my $XML = "jobs." . $hist . "." . $prod . ".xml";
my $XML = "jobs." . $prod . ".xml";
open (XML,">$XML") or die "Can't open $XML";
print XML '<?xml version="1.0" encoding="utf-8" ?> 
<job name="dEdx" maxFilesPerProcess="1" filesPerHour="1" simulateSubmission="false" fileListSyntax="paths">
	 <command>
         cd ${SUBMITTINGDIRECTORY}
if ($?INPUTFILE0) csh -x $INPUTFILE0
         </command>
';
#if ($?INPUTFILE1) csh -x $INPUTFILE1
#if ($?INPUTFILE2) csh -x $INPUTFILE2
#if ($?INPUTFILE3) csh -x $INPUTFILE3
#if ($?INPUTFILE4) csh -x $INPUTFILE4
#if ($?INPUTFILE5) csh -x $INPUTFILE5
#if ($?INPUTFILE6) csh -x $INPUTFILE6
#if ($?INPUTFILE7) csh -x $INPUTFILE7
#if ($?INPUTFILE8) csh -x $INPUTFILE8
#if ($?INPUTFILE9) csh -x $INPUTFILE9

my @files = ();
$script = $prod;# . "O";
#my $SCR = "/star/institutions/bnl/fisyak/dEdx/";
#my $SCR = "/star/data05/scratch/fisyak/dEdx/";
my $SCR = "/gpfs01/star/subsys-tpc/fisyak/dEdx/";
if (! -r $SCR) {
  $SCR = "/net/l404/data/fisyak/dEdx/";
}
my $hostname = `hostname`; chomp($hostname);
#my $homedir  = "/afs/rhic/star/users/fisyak/public/.dev/dEdx";
#my $homedir  = "/star/institutions/bnl/fisyak/dEdx/jobs/SL04i";
#my $homedir  = "/star/institutions/bnl/fisyak/dEdx/jobs/" .$STAR_LEVEL ;
#my $homedir  = "/star/data07/calib/fisyak/dEdx/jobs/" .$STAR_LEVEL ;
#if ($hostname =~ /^a/) {
#  $SCR = "/usatlas/projects/dc0/deexx/";
#  $homedir = "/usatlas/projects/dc0/deexx/Jobs";
#}
$scr = $SCR . $hist . "/";
print "Production = $Production ==> $hist\n";
my $glb = "";
if ($#ARGV >= 0) {$glb = $ARGV[0];}
else {
  if ($Production) {
    if ($disk !~ /^\//) {
#      $glb =  "/star/" . $disk . $RECO . $Production . "*" . $year . $FILE . $select . ".event.root";
      if (-d "/direct/star") {
	$glb =  "/direct/star/" . $disk . $RECO . $Production . $year . $FILE . $select . ".event.root";
      } else {
	$glb =  "/star/" . $disk . $RECO . $Production . $year . $FILE . $select . ".event.root";
      }
    } else {
      $glb =  $disk . $RECO . $Production . "*" . $year . $FILE . $select . ".event.root";
    }
  } 
#  if ($Production) {$glb =  "/star/" . $disk . $RECO . $Production . "*calib*/" . $year . $FILE . $select . ".event.root";}
  else { die "Production has not been defined";}
}
print "glb = $glb\n";
my @Files = glob "$glb"; 
print "Files $glb:  $#Files\n";
my $count = 0;
my $opened = 0;
my $fileno = 0;
my $badruns = ""; 
my $now = time();
if ($#badruns > -1) {$badruns = join "|", @badruns; print "Badruns: $badruns\n";}
{
  foreach my $file (@Files) {
#    if ($file !~ /3p85GeV_fixedTarget_2021/ && $file !~ /7p7GeV_2021/) {next;}
#    print "file = $file\n";
#    next if $Production !~ 'adc' and $file =~ /adc/; 
#    next if $file !~ /TOF/ and $file !~ /dEdx/;
#    next if $file =~ /FieldOff/; 
#    next if $file =~ /pmdftp/;
    my ($dev, $ino, $mode, $nlink, $uid, $gid, $rdev, $size, $atime, $mtime, $ctime, $blksize, $blocks ) = stat $file;
#    print " dev,  ino,  mode,  nlink,  uid,  gid,  rdev,  size,  atime,  mtime,  ctime,  blksize,  blocks\n";
#    print "$dev, $ino, $mode, $nlink, $uid, $gid, $rdev, $size, $atime, $mtime, $ctime, $blksize, $blocks\n";
    my $dt = $now - $ctime;
    print "$file dt = $dt\n";
#    my $da = $now - $mtime;
#    print "da = $da\n";
#    if ($dt < 3600) {print "$file is too young $dt --- skipped\n"; next};
#    die;
#    next if $size < 1000000000;
    next if $size < 100000000;
    my $dir = File::Basename::dirname($file);
    my $fff = File::Basename::basename($file);
    $fff =~ s/_adc_/_/;
    $fff =~ s/_mtd_/_/;
    my @words = split '_', $fff; #print "fff = $fff => words = @words\n";
    my $Run = $words[2];
#    if ($Run !~ /$listOfRuns/) {next;}
    my @ddd = split '',$Run;
    my $Day = $ddd[2] . $ddd[3] . $ddd[4];
#    my ($Dummy,$Dummy, $Disk, $Dummy, $Dummy, $Dummy, $prod, $Year, $Day, $Run) = split('/', $dir);
#    next  if $Day < $minDay || $Day > $maxDay;
    my $f = File::Basename::basename($file);
#    print "$file\n";    next;
    my $local_file = $f;
    $f =~ s|_raw_|_|; #print "f = $f size = $size\n"; 
    $Total_Size += $size;
    $f =~ s|\.root||;
    foreach my $ff (@files ){goto ENDL if $ff eq $f;}
    push @files, $f; print "push $f\n";
    (my $ff = $f) =~ s|st_physics_||;
    $dd =~ s|hlt_||;
    $ff =~ s|st_fmsslow_||;
    $ff =~ s|st_minbias_||;
    $ff =~ s|st_hlt_||;
    $ff =~ s|st_mtd_||;
    $ff =~ s|adc_||;
#    $ff =~ s|_raw_0001||;
    $ff =~ s/\.(dst|event)//g;
    $ff =~ s/rcf//g; $ff =~ s/evts//;
    $ff =~ s/AuAu200//g;
    if ($badruns and $ff =~ $badruns) {print "============ Bad run $file =============\n"; next;}
#    print "file = $file\n";
    my @words = split '/', $file;# for (my $i = 0; $i < $#words; $i++) {print "$i $words[$i]\n";}
    my $dd = $words[4] . '_' . $words[5];
    if ($dd !~ /GeV/ && $dd !~ /AuAu200/) {
      $dd = $words[7];
    }
    $dd =~ s/production_//;
    $dd =~ s/_ReversedFullField//;
    my $scrr = $scr . $dd . "/"; #print "scrr = $scrr\n";
    if ($step == 0) {$step = $NEvents;}
    for (my $First = 1; $First < $NEvents; $First += $step) {
      my $Last = $First - 1 + $step;
      my $bff = $ff  . "_" . $First . "_" . $Last;# print "$ff => $bff \n";
      my $root = $scrr . $bff  .".root";# print "root = $root\n";
      my $logL = $bff . ".log";
      my $log = $scrr . $logL;
      my $SCRIPT = $script ."_" . $STAR_LEVEL ."_". $bff . ".csh";
      next if   -r $SCRIPT;
      my $LOG    = $script ."_" . $STAR_LEVEL ."_". $bff . ".log";
      my $ERR    = $script ."_" . $STAR_LEVEL ."_". $bff . ".err";
      # switch between all and 1-st one
      my $ffile = $file; $ffile =~ s|0001\.dst|000\*\.dst|;
      my $run   = $Run; #$ff; $run =~ s|_.*||; print "Run = $run\n";
      next if -r $root;
      #    print "file=$file $Disk $prod $Year Day=$Day Run=$Run \n";
      $fileno++;
      if ($keep and $fileno%$keep != 1) {
	open(REM,">>skipped.csh") or die "Can't open skipped.csh";
	print REM "rm $file\n";
	close (REM);
	goto ENDL;
      } # skip all except each "keep"-th file
      if ($opened && $count == $maxFjob ) {
	close (OUT); $opened = 0; $count = 0;
	chmod 0755, $SCRIPT;
      }
      if (! $opened) {
	print "Create $SCRIPT\n";
	print XML "<input URL=\"file:" . $DIR . "/" .  $SCRIPT ."\" />\n";
	open (OUT,">$SCRIPT") or die "Can't open $SCRIPT";
	$opened = 1;
	print OUT "#! /usr/local/bin/tcsh -f\n";
	if ($STAR_LEVEL ne "\.DEV2") {
	  if ($STAR_LEVEL !~ "^\.DEV2" and $STAR_LEVEL !~ "^TFG") {
	    print OUT "source ${GROUP_DIR}/setup gcc;\n";
	  }
	  print OUT "source $GROUP_DIR/.starver $STAR_LEVEL;\n";
	}  else {
	  print OUT "source $GROUP_DIR/.starver $STAR_LEVEL;\n";
	}
	print OUT "/usr/bin/test -d $scrr || mkdir -p $scrr;\n";
      }
      my $cmd = "/usr/bin/test ! -r " . $root . " && root.exe -q -b  '" . $macro;
      $cmd .= ".C(" . $First ."," .$Last. ",\"" . $ffile . "\",\"" . $root . "\"," . $Mode . ")\' >& $log";
      #    $cmd .= "; cp -p $logL $log;";
      print OUT "$cmd\n";
      $count++;
    ENDL:
    }
  }
  if ($opened) {
    close (OUT); $opened = 0;
    chmod 0755, $SCRIPT;
  }
print XML '
<stdout URL="file:./sched$JOBID.log" />
<stderr URL="file:./sched$JOBID.err" />
<!--
 <ResourceUsage>
    <Memory>
      <MinMemory>1500</MinMemory>
    </Memory>
  </ResourceUsage>
-->
</job>
';
close (XML);
#close (CONDOR);
my $GB = $Total_Size/1024/1024/1024;
print "Total size = $GB GB\n"; 
}

