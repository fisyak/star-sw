#! /usr/bin/env tcsh 
FPE_OFF
set list = "";
set domain = `hostname -d`
switch ($domain) 
  case "*local":
  case "*starp.bnl.gov":
    set list = "gcc gcc631 gcc/12" #"gcc gcc521 gcc631 gcc7 gcc8";
    breaksw
  case "*bnl.gov":
#    set list = "gcc482 gcc492";
    set list = "gcc"
    breaksw
endsw
echo "list = $list}"
foreach gccV (${list}) 
  set opts = "debug opt"
#  if ($gccV == "gcc8" || gccV == "gcc631") set opts = "debug opt opt3"
    echo "opts = ${opts}"
  foreach OPTV ($opts)
    echo "OPTV = ${OPTV}"
#    switch (${OPTV})
#    case "opt3":
#      setup -O3
#      echo "debug: ${opt} => $NODEBUG"
#      breaksw
#    case "nodebug":
#      setup nodebug
#      echo "debug: ${opt} => $NODEBUG"
#      breaksw
#    default:
#      setup debug
#      breaksw
#    endsw
    set bits = "64b";
    if (${gccV} == "gcc") set bits = "32b 64b";
    echo "bits = ${bits}"
    foreach bit (${bits})
#      foreach proc (RC) # XC  RC MC)
        set proc = "RC"
	echo "proc = ${proc}, gcc = ${gccV}, bit = ${bit}, OPTV = ${OPTV}, STAR_LEVEL = ${STAR_LEVEL}"
        set dir = ${proc}_${OPTV}_${STAR_HOST_SYS}_${STAR_LEVEL}; echo "dir = $dir"
	setup ${OPTV}
        setup ${gccV}
        setup ${bit}
        starver ${STAR_LEVEL}
        if (! -d ${dir}) mkdir ${dir}
	ls -1d ${dir}/*B.log
	if (! $?) continue
        cd ${dir}
	switch ($proc)
	case "RC":
#          root.exe -q -b -x 'bfc.C(1000,"P2019a,-hitfilt,mtd,btof,BEmcChkStat,CorrY,OSpaceZ2,OGridLeakFull,evout,NoHistos,noTags,noRunco,StiCA,picoWrite,PicoVtxVpdOrDefault","/net/l401/data/scratch1/daq/2019/083/20083024/hlt_20083024_12_02_000.daq")' >& hlt_20083024_12_02_000B.log &
# /hlt/cephfs/reco/2023/RF/TFG/AuAu_2023/150/24150001/hlt_24150001_11_01_000B.log.gz
	    root.exe -q -b -x 'bfc.C(1000,"p2023a,StiCA,PicoVtxVpdOrDefault,BEmcChkStat,evout,NoHistos,noTags,noRunco,-fcs,-fcsDb,-fcsDat,-fcsWFF,-fcsCluster,-fcsPoint","/hlt/cephfs/daq/2023/150/24150001/hlt_24150001_11_01_000.daq")' >& hlt_24150001_11_01_000B.log &
	  breaksw
	case "XC":
	  root.exe -q -b -x 'bfc.C(1000,"P2019a,-hitfilt,mtd,btof,BEmcChkStat,CorrY,OSpaceZ2,OGridLeakFull,evout,NoHistos,noTags,noRunco,Stx,KFVertex,VFMinuitX,picoWrite,PicoVtxVpdOrDefault","/net/l401/data/scratch1/daq/2019/083/20083024/hlt_20083024_12_02_000.daq")' >& hlt_20083024_12_02_000B.log &
	
	  breaksw
	case "MC":
          root.exe -q -b -x 'bfc.C(100,"genIn,MC.2019,McTpcAna,-bbcSim,StiCA,-hitfilt,geantOut,evout,vmc,VMCAlignment,CorrY,OSpaceZ2,OGridLeakFull,-useXgeom,NoHistos,noTags,noRunco,ZCut5cm,RunG.1","/net/l401/data/scratch2/fisyak/simu/Hijing/AuAu200/hijingAuAu200_1_1000.gener.root",0,"hijingAuAu200_1_1000.root")' >& hijingAuAu200_1_1000B.log &
	  breaksw
	case default:
	  breaksw
        endsw
        cd -;
#      end 
    end
  end
end
