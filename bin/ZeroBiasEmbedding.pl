#! /usr/bin/env perl
use File::Basename;
use Cwd;
my $ZeroBias = "/hlt/cephfs/daq/2023/211/24211048/st_zerobias_adc*.daq";
# -rw-rw---- 1 fisyak rhstar 5.0G Dec  7 14:05 st_zerobias_adc_24211048_raw_0000006.daq  1598
# -rw-rw---- 1 fisyak rhstar 1.1G Dec  7 14:02 st_zerobias_adc_24211048_raw_0000007.daq   355
my $Gen  = "/net/l401/data/scratch2/fisyak/simu/Hijing/AuAu200/hijingAuAu200_*_1000.gener.root"; # 1-100
my $first = 1;
my $last  = -1;
my $step = 20;
my $zerobiasfile1 = "/hlt/cephfs/daq/2023/211/24211048/st_zerobias_adc_24211048_raw_0000006.daq"; my $events1 =  1598;
my $zerobiasfile2 = "/hlt/cephfs/daq/2023/211/24211048/st_zerobias_adc_24211048_raw_0000007.daq"; my $events2 =   355;
my $zerofileNo = 1;
my $zerobiasfile = $zerobiasfile1;
my $events = $events1;
for (my $i = 1; $i <= 100; $i++) {
  my $genfile = "/net/l401/data/scratch2/fisyak/simu/Hijing/AuAu200/hijingAuAu200_" . $i . "_1000.gener.root";
  $last = $first + $step - 1;
  if ($last > $events) {$last = $events;}
  print "string:$first:$last:$zerobiasfile:$genfile\n";
  $first = $last + 1;
  if ($last == $events) {
    if ($zerofileNo == 2) {last;}
    $zerofileNo = 2;
    $zerobiasfile = $zerobiasfile2;
    $events = $events2;
    $first = 1;
  }
}
