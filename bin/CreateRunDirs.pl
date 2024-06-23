#! /usr/bin/env perl
use File::Basename;
use Cwd;
use Env;
#print "$0\n";
#use lib dirname $0; # 
use lib "/net/l402/data/fisyak/STAR/packages/.DEV2/bin";
use GetYearFromPWD;
my $debug = 0;
if ($#ARGV >= 0) {
  $debug = $ARGV[0];
}
my $fNoMax = -1;
if ($#ARGV >= 1) {
  $fNoMax = $ARGV[1];
  print "fNoMax = $fNoMax\n";
}
my ($year,$FIELD,$runs,$def,$Day,$Run,$run2) = GetRuns($debug);
print "$0 Year = $year, Field = $FIELD, runs = $runs, def = $def,  Day = $Day, Run = $Run, run2 = $run2\n" if ($debug);
if (! $year || ! $FIELD) {die "wrong directory $pwd";}
#PrintHash($def,"Runs") if ($debug);
my $fNo = 0;
my @AllRuns = ($runs);
if ($run2) {push @AllRuns, $run2;}
foreach my $currentrun (@AllRuns) {
  my @RUNS = glob $currentrun; print "$0 RUNS = @RUNS\n" if ($debug);
  foreach my $run (@RUNS) {
    my $r = File::Basename::basename($run); #print "$0 run = $run, r = $r\n" if ($debug);
#    if (GoodRun($def,$r,$debug) < 0) {next;}
    if (GoodRun($def,$r,0) < 0) {next;}
    #  if ($r < 21040001) {next;}
    #  if ($r < 21042001) {next;} # exclude 9p2GeV
    foreach my $tag (qw(hlt st_physics_)) { # st_physics_2 st_cosmic st_physic)) {
      my $glob = $run . "/" . $tag . "*.daq";
      my @daqfiles = glob $glob; print "$0 $glob => $#daqfiles : @daqfiles\n" if ($debug);
      if ($#daqfiles < 0) {next;}
      $fNo += $#daqfiles + 1; print "fNo = $fNo\n" if ($debug);
      my $day = sprintf("%03i",(int ($r/1000))%1000); print "$0 ru = $r => day = $day\n" if ($debug);
      my $dir = $day . "/" . $r;
      if (-d $dir) {next;}
      my $cmd = "mkdir -p $dir"; print "$0 $cmd\n";
      my $flag = system($cmd);
      if ($flag) {last;}
      if ($fNoMax > 0 &&  $fNo > $fNoMax) {last;}
#      die;
    }
    if ($fNoMax > 0 &&  $fNo > $fNoMax) {last;}
  }
}



