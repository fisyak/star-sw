#! /usr/bin/env perl
use File::Basename;
use Cwd;
use Env;
use lib dirname $0; # 
#use lib "/net/l402/data/fisyak/STAR/packages/.DEV2/bin";
use GetYearFromPWD;
$debug = 0;
if ($#ARGV >= 0) {
  $debug = $ARGV[0];
}
my ($year,$FIELD,$runs,$def,$Day,$Run,$run2) = GetRuns($debug);
print "Year = $year, Field = $FIELD, runs = $runs,  Day = $Day, Run = $Run, $run2\n" if ($debug);
if (! $year || ! $FIELD) {die "wrong directory $pwd";}
my $def = {@Runs};# print "Runs = @Runs\n";
PrintHash($def,"Runs") if ($debug);
my $fNo = 0;
my @AllRuns = ($runs);
if ($run2) {push @AllRuns, $run2;}
foreach my $currentrun (@AllRuns) {
  foreach my $run (glob $currentrun) {
    my $r = File::Basename::basename($run); print "$run => run = $r\n" if ($debug);
    if (GoodRun($def,$r,$debug) < 0) {next;}
    print "$run Accepted\n" if ($debug);
#    foreach my $tag (qw(st hlt)) {
    foreach my $tag (qw(hlt st_physics_)) { # st_physics_2
      my @files = glob $run . "/" . $tag . "*.daq"; print "files = @files\n" if ($debug);
# get_file_list.pl -keys 'events' -cond 'filetype=online_daq,filename="st_physics_21044023_raw_2500001.daq"' -limit 1
      if ($#files < 0) {next;}
      #  print "files = @files\n";
      #    my $day = int ($r/1000 - 20000); #print "ru = $r => day = $day\n";
      #    if ($day != / 107 and $day != 113 and $day != 169) {next;}
      #    if ($day !~ m/158|160|179|180|181|182|183/) {next;}
      #  if ($r >= 20100000) {next;}
      my $NF = $#files + 1;
      my $step = 1; #(int $NF);
      print "run = $run. files = $NF, step = $step\n" if ($debug);
      if ($step < 1) {$step = 1;}
      print "run = $run. files = $NF, step = $step\n" if ($debug);
      for (my $i = 0; $i < $NF; $i = $i +  $step) {
	print "i = $i, step = $step \n" if ($debug);
	my $file = $files[$i];
	my $b = File::Basename::basename($file,".daq");
	#    print "$b\n" if ($debug);
	my $evfile = $b . ".event.root";
	if (-r $evfile) {next;}
	my $mufile = $b . ".MuDst.root";
	if (-r $mufile) {next;}
	my $pifile = $b . ".picoDst.root";
	if (-r $pifile) {next;}
	my $blafile = $b . ".bla.root";
	if (-r $blafile) {next;}
	print "string:$file\n";
	$fNo++;
      }
    }
  }
}
if (! $fNo) {die "Don't have input files\n";}

