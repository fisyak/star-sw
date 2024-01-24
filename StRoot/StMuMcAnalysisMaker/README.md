The instructions how to run muMc.C :
1. The codes are available in TFG releases :  https://github.com/fisyak/star-sw/tree/TFG
2. How to use TFG release
	starver .DEV2
	source $STAR/setupDEV2.csh
	starver _desired_TFG_version__, from TFG16a to TFG24a, .DEV2 == TFG is check out HEAD from TFG repository, it could be unstable.
for example,
        starver  TFG24a
3. Create directory, which will contain link to embedding MuDst.root files, see for example, /gpfs01/star/subsys-tpc/fisyak/Embed/19GeV_2019_Piminus_200_20214201_P21ic.SL21c
for example, 
        ln -s /star/embed/embedding/production_19GeV_2019/Piminus_200_20214201/P21ic.SL21c/2019/*/*/*MuDst.root .
       
4. mkdir muMc; cd muMc
5. To get access to my macros you can use
   ln -s ~fisyak/.rootrc_noqt .rootrc 
6. root.exe muMc.C
    as results you will have muMc.root file and bunch of *.png files. An example, how to view these *png files you can see at https://www.star.bnl.gov/~fisyak/star/muMc/2020/
7. root.exe muMc.root muMcdpTiR.C
   will produce the plot of momentum resolution for global and primary track versus pT
