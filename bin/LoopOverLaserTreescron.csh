#! /bin/tcsh -f
#cd /net/l404/data/fisyak/Tpc/Lana/2019D 
#cd /net/l404/data/fisyak/Tpc/Lana/2020b
#cd /net/l404/data/fisyak/Tpc/Lana/2021
#cd /net/l404/data/fisyak/Tpc/Lana/2022
#cd /net/l404/data/fisyak/Tpc/Lana/2023
#cd /net/l404/data/fisyak/Tpc/Lana/2023B
cd /net/l404/data/fisyak/Tpc/Lana/2024
LoopOverLaserTrees.pl
if ($?) exit 0;
/net/l402/data/fisyak/STAR/packages/.DEV2/scripts/star-submit ~/xml/LoopOverLaserTrees.xml

