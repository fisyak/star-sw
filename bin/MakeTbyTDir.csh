#! /usr/bin/env tcsh
set Old = TFG26d
set New = TFG26f
set cdir = ${PWD}
foreach set (13p5GeV_fixedTarget_2026  8p65GeV_fixedTarget_2026  9p8GeV_fixedTarget_2026)
  set workdir = ${set}_${Old}_${New}
  mkdir ${workdir}
  mkdir ${workdir}/old ${workdir}/new
  cd ${workdir}/old
  ln -s /gpfs01/star/data100/TPC/TPC23/2025/Test/RF/${Old}/${set}/*/*/*event.root .
  cd -
  cd ${workdir}/new
  ln -s /gpfs01/star/data100/TPC/TPC23/2025/Test/RF/${New}/${set}/*/*/*event.root .
  cd -
  MakeTbyT.pl
end
