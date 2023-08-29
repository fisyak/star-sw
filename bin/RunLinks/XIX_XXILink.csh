#! /usr/local/bin/tcsh -f
set list = "TpcSecRowB TpcAccumulatedQ TpcZCorrectionC TpcPadCorrectionMDF TpcLengthCorrectionMDN"
#set list = "TpcdXCorrectionB"
#set list = "TpcSecRowB"
#set list = "TpcLengthCorrectionMDN"
set list = "TpcZCorrectionC"
#set list = "starTriggerDelay"
#set  list = "tpcT0BX"
#set list = "tpcTimeBucketCor"
foreach p (${list})
 set ext = C
 if (${p} == "TpcSecRowB") set ext = root;
 ln -sf ${p}.19GeV_2019.${ext}                              ${p}.20190225.202320.${ext}
 ln -sf ${p}.14p5GeV_2019.${ext}                            ${p}.20190404.094405.${ext}
 ln -sf ${p}.7.3GeV_fixedTarget_2019.${ext}                 ${p}.20190417.133401.${ext}
 ln -sf ${p}.14p5GeV_2019.${ext}                            ${p}.20190417.141246.${ext}
 ln -sf ${p}.7.3GeV_fixedTarget_2019.${ext}                 ${p}.20190423.155418.${ext}
 ln -sf ${p}.14p5GeV_2019.${ext}                            ${p}.20190423.181158.${ext}
 ln -sf ${p}.7p7GeV_2019.${ext}                             ${p}.20190603.223655.${ext}
 ln -sf ${p}.3p85GeV_fixedTarget_2019.${ext}                ${p}.20190607.174702.${ext}
 ln -sf ${p}.7p7GeV_2019.${ext}                             ${p}.20190607.202244.${ext}
 ln -sf ${p}.3p85GeV_fixedTarget_2019.${ext}                ${p}.20190609.124528.${ext}
 ln -sf ${p}.7p7GeV_2019.${ext}                             ${p}.20190610.024109.${ext}
 ln -sf ${p}.7.3GeV_fixedTarget_2019.${ext}                 ${p}.20190618.143658.${ext}
 ln -sf ${p}.7p7GeV_2019.${ext}                             ${p}.20190619.025126.${ext}
 ln -sf ${p}.9p2GeV_2019.${ext}                             ${p}.20190628.081931.${ext}
 ln -sf ${p}.4p59GeV_fixedTarget_2019.${ext}                ${p}.20190629.032834.${ext}
 ln -sf ${p}.9p2GeV_2019.${ext}                             ${p}.20190702.144151.${ext}
 ln -sf ${p}.31GeV_fixedTarget_2019.${ext}                  ${p}.20190709.032312.${ext}
 ln -sf ${p}.AuAu200_2019.${ext}                            ${p}.20190710.110157.${ext}
 ln -sf ${p}.9p2GeV_2019.${ext}                             ${p}.20190715.085141.${ext}
 ln -sf ${p}.11p5GeV_2020.${ext}                            ${p}.20191208.091308.${ext}
 ln -sf ${p}.5p75GeV_fixedTarget_2020.${ext}                ${p}.20191221.154021.${ext}
 ln -sf ${p}.11p5GeV_2020.${ext}                            ${p}.20191221.190032.${ext}
 ln -sf ${p}.31p2GeV_fixedTarget_2020.${ext}                ${p}.20200128.182912.${ext}
 ln -sf ${p}.9p8GeV_fixedTarget_2020.${ext}                 ${p}.20200130.005840.${ext}
 ln -sf ${p}.9p2GeV_2020.${ext}                             ${p}.20200131.012112.${ext}
 ln -sf ${p}.9p8GeV_fixedTarget_2020.${ext}                 ${p}.20200131.050328.${ext}
 ln -sf ${p}.19p5GeV_fixedTarget_2020.${ext}                ${p}.20200201.191904.${ext}
 ln -sf ${p}.13p5GeV_fixedTarget_2020.${ext}                ${p}.20200202.160409.${ext}
 ln -sf ${p}.9p2GeV_2020.${ext}                             ${p}.20200203.202534.${ext}
 ln -sf ${p}.7p3GeV_fixedTarget_2020.${ext}                 ${p}.20200204.053518.${ext}
 ln -sf ${p}.9p2GeV_2020.${ext}                             ${p}.20200205.144626.${ext}
 ln -sf ${p}.11p5GeV_2020.${ext}                            ${p}.20200210.220428.${ext}
 ln -sf ${p}.5p75GeV_fixedTarget_2020.${ext}                ${p}.20200213.152339.${ext}
 ln -sf ${p}.11p5GeV_2020.${ext}                            ${p}.20200214.143742.${ext}
 ln -sf ${p}.9p2GeVb_2020.${ext}                            ${p}.20200224.230740.${ext}
 ln -sf ${p}.9p2GeVc_2020.${ext}                            ${p}.20200617.233208.${ext}
 ln -sf ${p}.26p5GeV_fixedTarget_2020.${ext}                ${p}.20200730.015354.${ext}
 ln -sf ${p}.9p2GeVc_2020.${ext}                            ${p}.20200730.042836.${ext}
 ln -sf ${p}.26p5GeV_fixedTarget_2020.${ext}                ${p}.20200813.213251.${ext}
 ln -sf ${p}.9p2GeVc_2020.${ext}                            ${p}.20200814.054357.${ext}
 ln -sf ${p}.26p5GeV_fixedTarget_2020.${ext}                ${p}.20200819.192253.${ext}
 ln -sf ${p}.9p2GeVc_2020.${ext}                            ${p}.20200820.055402.${ext}
 ln -sf ${p}.26p5GeV_fixedTarget_2020.${ext}                ${p}.20200827.143507.${ext}
 ln -sf ${p}.9p2GeVc_2020.${ext}                            ${p}.20200828.064250.${ext}
 ln -sf ${p}.7p7GeV_2020.${ext}                             ${p}.20200902.105440.${ext}
 ln -sf ${p}.26p5GeV_fixedTarget_2020.${ext}                ${p}.20200907.221141.${ext}
 ln -sf ${p}.7p7GeV_2020.${ext}                             ${p}.20200910.041639.${ext}
 ln -sf ${p}.26p5GeV_fixedTarget_2020.${ext}                ${p}.20200912.102033.${ext}
 ln -sf ${p}.7p7GeV_2021.${ext}                             ${p}.20210131.193346.${ext}
 ln -sf ${p}.3p85GeV_fixedTarget_2021a.${ext}               ${p}.20210501.165439.${ext} #${p}.20210501.165437.${ext}
 ln -sf ${p}.44p5GeV_fixedTarget_2021.${ext}                ${p}.20210506.070148.${ext} #${p}.20210506.070146.${ext}
 ln -sf ${p}.70GeV_fixedTarget_2021.${ext}                  ${p}.20210507.031641.${ext} #${p}.20210507.031639.${ext}
 ln -sf ${p}.100GeV_fixedTarget_2021.${ext}                 ${p}.20210508.041528.${ext} #${p}.20210508.041526.${ext} 
 ln -sf ${p}.OO_200GeV_2021.${ext}                          ${p}.20210510.134726.${ext}
 ln -sf ${p}.ps_OO_200GeV_2021.${ext}                       ${p}.20210513.083120.${ext}
 ln -sf ${p}.OO_200GeV_2021.${ext}                          ${p}.20210513.084422.${ext}
 ln -sf ${p}.ps_OO_200GeV_2021.${ext}                       ${p}.20210513.175228.${ext}
 ln -sf ${p}.OO_200GeV_2021.${ext}                          ${p}.20210513.182205.${ext}
 ln -sf ${p}.OO_fcsTiming.${ext}                            ${p}.20210514.144728.${ext}
 ln -sf ${p}.OO_200GeV_2021.${ext}                          ${p}.20210514.150240.${ext}
 ln -sf ${p}.ps_OO_200GeV_2021.${ext}                       ${p}.20210516.112015.${ext}
 ln -sf ${p}.FF_OO_200GeV_2021.${ext}                       ${p}.20210522.023642.${ext}
 ln -sf ${p}.17p3GeV_2021.${ext}                            ${p}.20210525.113236.${ext}
 ln -sf ${p}.26p5GeV_fixedTarget_2021.${ext}                ${p}.20210604.023047.${ext} #${p}.20210604.023045.${ext}
 ln -sf ${p}.17p3GeV_2021.${ext}                            ${p}.20210604.081455.${ext}
 ln -sf ${p}.3p85GeV_fixedTarget_2021b.${ext}               ${p}.20210608.004953.${ext} #${p}.20210608.004951.${ext}
 ln -sf ${p}.26p5GeV_fixedTarget_2021.${ext}                ${p}.20210617.222552.${ext} #${p}.20210617.222550.${ext}
 ln -sf ${p}.3p85GeV_fixedTarget_2021b.${ext}               ${p}.20210618.040937.${ext} #${p}.20210618.040935.${ext}
 ln -sf ${p}.26p5GeV_fixedTarget_2021.${ext}                ${p}.20210627.152749.${ext} #${p}.20210627.152747.${ext}
 ln -sf ${p}.3p85GeV_fixedTarget_2021b.${ext}               ${p}.20210628.115430.${ext} #${p}.20210628.115428.${ext}
 ln -sf ${p}.dAu200_2021.${ext}                             ${p}.20210630.022849.${ext}
 ln -sf ${p}.26p5GeV_fixedTarget_2021.${ext}                ${p}.20210703.010652.${ext} #${p}.20210703.010650.${ext}
 ln -sf ${p}.dAu200_2021.${ext}                             ${p}.20210703.053033.${ext}
 ln -sf ${p}.26p5GeV_fixedTarget_2021.${ext}                ${p}.20210703.230659.${ext} #${p}.20210703.230657.${ext}
 ln -sf ${p}.dAu200_2021.${ext}                             ${p}.20210704.034046.${ext}
#    foreach y (2019 2020 2021) 
#	foreach f (`dirc ${p}* | grep '\->' | grep GeV | grep -v fixedTarget | awk '{print $11}'`)
#	    ln -s ${p}.${ext} ${p}.COL_${y}.${ext}
#	    ln -s ${p}.COL_${y}.${ext}  ${f} 
#        end
#	foreach f (`dirc ${p}* | grep '\->' | grep GeV | grep fixedTarget | awk '{print $11}'`)
#	    ln -s ${p}.${ext} ${p}.FXT_${y}.${ext}
#	    ln -s ${p}.FXT_${y}.${ext}  ${f} 
#        end
#    end
end
