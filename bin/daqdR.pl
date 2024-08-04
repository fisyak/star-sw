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
#--------------------------------------------------------------------------------
sub SPrint ($$$$$) {
  my $noEventsPerJob = 5000; #10000;
  my ($line,$file,$f,$l,$debug) = @_;
#  print "line=$line,file=$file,f=$f,l=$l,debug=$debug\n";
  my $count = 0;
  if ($l - $f >= 0) {# Allow to have error in no. of events in FileCatalog
    my $rootf = $file . "," . $f . "," . $l . ".MuDst.root"; 
    if (-r $rootf) {
      if ($debug) {
	print "rootf = $rootf\n";
      }
      next;
    }
    my $blaf  = $file . "," . $f . "," . $l . ".bla.root";
    if (-r $blaf) { 
      if (debug > 0) { 
	print "$blaf\n";
      }  
      next;
    }
    my $f1 = $f;
    for (my $f1 = $f1; $f1 < $l; $f1 += $noEventsPerJob) {
      my $l1 = $f1 + $noEventsPerJob - 1;
      if ($l1 > $l) {$l1 = $l;}
      print "string:$line:$f1:$l1\n";
      $count++;
    }
  }
  return $count;
}
#--------------------------------------------------------------------------------
sub MuCount($$$$) {# daqName, first, last, 
  my ($line, $first, $last, $debug)  = @_;
  my $file = File::Basename::basename($line,".daq");
  my $fileDaq = $file . ".daq";
  my $no = 0;
  my $fileN = $file . ".noeve";
  if (! -r $fileN) {
    my $cmd = "get_file_list.pl -keys 'events' -cond 'filetype=online_daq,filename=" . $fileDaq . "' -limit 1  > " . $fileN; print "$cmd\n" if ($debug);
    my $N = `$cmd`; chomp($N); 
  }
  my $N = `cat $fileN`;
  chomp($N);
  print "$file N = $N\n" if ($debug);
  $last = $N;
  my $f = $first;
  my $l = $last;
  my $lC = $f;
  my $fC = $l;
  my @files = glob $file . "*.MuDst.root"; 
  if ($debug) {
    foreach my $file (@files) {print "$file\n";}
  }
#  die;
  # check repeats
  my $f0 = 0;
  my @F = ();
  my @L = ();# print "initialization : $#F\n";
  foreach my $mu (@files) {
    my $b = File::Basename::basename($mu,".MuDst.root");
    $b =~ s/_adc//;
    my ($dummy,$f1,$l1) = split(',',$b); 
    print "$b f1 =$f1 l1 = $l1\n" if ($debug);
    push @F, $f1;
    push @L, $l1;
  }
  my $NoMuFiles = $#F + 1;
  if ($debug) {
    #      print "$NoMuFiles, @F, @L\n";
    for (my $i = 0; $i < $NoMuFiles; $i++) {
      #	print "$F[$i]  $L[$i]\n";
      for (my $j = $i+1; $j < $NoMuFiles; $j++) {
	if ($F[$i] >= $F[$j] && $F[$i] <= $L[$j] ||
	    $L[$i] >= $F[$j] && $L[$i] <= $L[$j]) {
	  print "[$F[$i],$L[$i]] overlap with $F[$j],$L[$j]]\n";
	  die "died at $day/$run";
	}
      }
    }
  }
  if ($NoMuFiles <= 0) {
    $f = $first;
    $l = $last;
    SPrint($line,$file,$f,$l,$debug); $no++;
  } else {
    if ($L[$NoMuFiles-1] < $N) {
      $f = $L[$NoMuFiles-1] + 1;
      $l = $N;
      $no += SPrint($line,$file,$f,$l,$debug); 
    } 
    if ($F[0] > $f) {
      $f = 1;
      $l = $F[0] - 1;
      $no += SPrint($line,$file,$f,$l,$debug);
    } 
    for (my $i = 1; $i < $NoMuFiles; $i++) {
      #	print "$i  : $F[$i]  $L[$i]\n" if ($debug);
      my $f = $L[$i-1]+1;
      my $l = $F[$i]-1;
      # print "f = $f l = $l\n" if ($debug);
      if ($f <= $l) {
	SPrint($line,$file,$f,$l,$debug); $no++;
      }
    }
  }
  return $no;
}
#--------------------------------------------------------------------------------
my ($year,$FIELD,$runs,$def,$Day,$Run,$run2) = GetRuns($debug);
print "Year = $year, Field = $FIELD, runs = $runs,  Day = $Day, Run = $Run, $run2\n" if ($debug);
if (! $year || ! $FIELD) {die "wrong directory $pwd";}
my $def = {@Runs};# print "Runs = @Runs\n";
PrintHash($def,"Runs") if ($debug);
my $fNo = 0;
my @AllRuns = ($runs);
if ($run2) {push @AllRuns, $run2;}
my $first = 1;
my $last = 1000000;
foreach my $currentrun (@AllRuns) {
  foreach my $run (glob $currentrun) {
    my $r = File::Basename::basename($run); print "$run => run = $r\n" if ($debug);
    if (GoodRun($def,$r,$debug) < 0) {next;}
    print "$run Accepted\n" if ($debug);
#    foreach my $tag (qw(st hlt)) {
#    foreach my $tag (qw(hlt st_physics_)) { # st_physics_2
    foreach my $tag (qw(st_physics_)) { # st_physics_2
      my @files = glob $run . "/" . $tag . "*.daq"; print "files = @files\n" if ($debug);
      if ($#files < 0) {next;}
      my $NF = $#files + 1;
      my $step = 1; #(int $NF);
      print "run = $run, files = $NF, step = $step\n" if ($debug);
      if ($step < 1) {$step = 1;}
      print "run = $run. files = $NF, step = $step\n" if ($debug);
      for (my $i = 0; $i < $NF; $i = $i +  $step) {
	print "i = $i, step = $step \n" if ($debug);
	my $file = $files[$i];
	$fNo += MuCount($file,$first,$last,$debug);
      }
    }
  }
}
if (! $fNo) {die "Don't have input files\n";}

