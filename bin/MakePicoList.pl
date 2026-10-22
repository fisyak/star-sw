#! /usr/bin/env perl
#  ~/work/kfp/2020/19p5GeV_fixedTarget_P25iy $ awk -F\/ '{print $10" "$0}' production_19p5GeV_fixedTarget_2020_P25iy_SL25y_picodst.txt | sort |  tee 19p5GeV_fixedTarget_P25iy.sorted
#  ~/work/kfp/2021/26p5GeV_fixedTarget_2021_P25iy_calib $ awk -F\/ '{print $10" "$0}' production_26p5GeV_fixedTarget_2021_P25iy_calib_picodst.txt | sort | tee 26p5GeV_fixedTarget_2021_P25iy_calib.sorted
#  ~/work/kfp/2020/26p5GeV_fixedTarget_2020_P25iy_calib $ awk -F\/ '{print $10" "$0}' production_26p5GeV_fixedTarget_2020_P25iy_calib_picodst.txt | sort | tee 26p5GeV_fixedTarget_2020_P25iy_calib.sorted
#  ~/work/kfp/2020/7p7GeV_2020_P25iy_calib $ awk -F\/ '{print $10" "$0}' production_7p7GeV_2020_P25iy_calib_picodst.txt | sort | tee 7p7GeV_2020_P25iy_calib.sorted
# [starsub05] ~/work/kfp/2021/7p7GeV_2021_P25iy_calib $ awk -F\/ '{print $10" "$0}' production_7p7GeV_2021_P25iy_calib_picodst.txt | sort | tee 7p7GeV_2021_P25iy_calib.sorted
#  ~/work/kfp/2026/13p5GeV_fixedTarget_2026.TFG26i2 $ ls -1d /gpfs01/star/data100/TPC/reco/TFG26i2/2025/RF/13p5GeV_fixedTarget_2026/*/*/*picoDst.root  |  awk -F\/ '{print $12" "$0}' | tee 13p5GeV_fixedTarget_2026_TFG26i2.sorted
#  ~/work/kfp/2026/8p65GeV_fixedTarget_2026.TFG26i $ ls -1d /gpfs01/star/data100/TPC/reco/TFG26i2/2025/RF/8p65GeV_fixedTarget_2026/*/*/*picoDst.root | awk -F\/ '{print $12" "$0}' | tee 8p65GeV_fixedTarget_2026_TFG26i2.sorted[starsub05] ~/work/kfp/2026/9p8GeV_fixedTarget_2026.TFG26i2 $  ls -1d /gpfs01/star/data100/TPC/reco/TFG26i2/2025/RF/9p8GeV_fixedTarget_2026/*/*/*picoDst.root | awk -F\/ '{print $12" "$0}' | tee 9p8GeV_fixedTarget_2026_TFG26i2.sorted
# ls -1d /gpfs01/star/data100/TPC/reco/TFG26i2/2025/RF/9p8GeV_fixedTarget_2026/*/*/*picoDst.root | awk -F\/ '{print $12" "$0}' | tee list.sorted
# ~/work/kfp/2026/13p5GeV_fixedTarget_2026.TFG26j $ ls -1d /gpfs01/star/data100/TPC/reco/TFG26j/2025/RF/13p5GeV_fixedTarget_2026/*/*/*picoDst.root | awk -F\/ '{print $12" "$0}' | tee list.sorted
# starsub05] ~/work/kfp/2026/13p5GeV_fixedTarget_2026.TFG26k $  ls -1d /gpfs01/star/data100/TPC/reco/TFG26k/2025/RF/13p5GeV_fixedTarget_2026/*/*/*picoDst.root | awk -F\/ '{print $12" "$0}' | tee list.sorted
use File::Basename;
use Cwd;
use File::stat;
use Time::localtime;
use Env;
my @SortedList = glob "*.sorted";
if ($#SortedList < 0) {die "Don't have sorted list";}
my $Njons = 0;
my $step = 1000;
my $OldRun = -1;
my $index = 0;
my $ouput = "";
my $nfiles = 0;
my @capital_letters = ('A' .. 'Z');# print "@capital_letters\n";
foreach my $list (@SortedList) {
  open(IN,$list) or die "Can't open $list";
  while (my $string = <IN>) {
    my ($run,$file) = split(' ',$string); 
    $nfiles++;            #                print "run = $run, file = $file nfiles = $nfiles\n";
    if ($run ne $OldRun or $nfiles > $step) {
      $nfiles = 0;
      if ($output) {close(OUT);}
      if ($run ne $OldRun) {$index = 0; $OldRun = $run;}
      else                  {$index++;}
      $output = $run . $capital_letters[$index] . ".list"; #print "output = $output\n";
      open(OUT,">$output") or die "Can't open $output";
      $Njobs++;
    }
    print OUT "$file\n"; #print "$output $nfiles $file\n";
  }
  close(IN);
}
if (! $Njobs) {die "Don't have input files\n";}
