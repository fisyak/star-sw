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
  if ($debug > 2) {print "line=$line,file=$file,f=$f,l=$l,debug=$debug\n";}
  my $count = 0;
  if ($l - $f >= 0) {# Allow to have error in no. of events in FileCatalog
    my $rootf = $file . "," . $f . "," . $l . ".MuDst.root"; 
    if (-r $rootf) {
      if ($debug) {
	print "rootf = $rootf exists\n";
      }
#      next;
    } else {
      my $blaf  = $file . "," . $f . "," . $l . ".bla.root";
      if (-r $blaf) { 
	if (debug > 0) { 
	  print "$blaf exits\n";
	}  
#	next;
      } else {
	my $f1 = $f;
	for (my $f1 = $f1; $f1 < $l; $f1 += $noEventsPerJob) {
	  my $l1 = $f1 + $noEventsPerJob - 1;
	  if ($l1 > $l) {$l1 = $l;}
	  print "string:$line:$f1:$l1\n";
	  $count++;
	}
      }
    }
  }
  return $count;
}
#--------------------------------------------------------------------------------
sub MuCount($$$$) {# daqName, first, last, 
  if ($debug) {print "================================================================================\n";}
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
  if ($NoMuFiles <= 0) {
    $f = $first;
    $l = $last;
    $no += SPrint($line,$file,$f,$l,$debug);
    return $no;
  }
# sort over first
  if ($debug > 1) {print "NoMuFiles = $NoMuFiles\n";}
  for (my $i = 0; $i < $NoMuFiles - 1; $i++) {
    if ($debug > 1) {print "i = $i, [$F[$i],$L[$i]]\n";}
    for (my $j = $i + 1; $j < $NoMuFiles; $j++) {
      print "orig i = $i : [$F[$i],$L[$i]], j = $j : [$F[$j], $L[$j]]" if ($debug > 1);
      if ($F[$i] > $F[$j]) {
	my $tempF = $F[$i];
	my $tempL = $L[$i];
	$F[$i] = $F[$j]; $L[$i] = $L[$j];
	$F[$j] = $tempF; $L[$j] = $tempL;
	print "\tswap i = $i : [$F[$i],$L[$i]], j = $j : [$F[$j], $L[$j]]\n" if ($debug > 1);
      } else {
	print "\n" if ($debug > 1);
      }
    }
  }
  if ($debug > 1) {
    print "Sorted MuDst files\n";
    for (my $i = 0; $i < $NoMuFiles; $i++) {
      printf("[%05i,%05i]\n", $F[$i], $L[$i]);
    }
  }
  #      print "$NoMuFiles, @F, @L\n";
  for (my $i = 0; $i < $NoMuFiles; $i++) {
    print "sorted : $i $F[$i]  $L[$i]\n" if ($debug > 1);
    if ($i == 0 && $F[$i] > 1) {
      my $f = 1;
      my $l = $F[$i] - 1;
      $no += SPrint($line,$file,$f,$l,$debug);
    } 
    if ($i ==  $NoMuFiles -1) {
      if ($L[$i] < $N) {
	my $f = $L[$i]+1;
	my $l = $NN;
	$no += SPrint($line,$file,$f,$l,$debug);
      }
    } else {
      my $j =  $i + 1;
      print "check limits: [$F[$i],$L[$i]] and  [$F[$j],$L[$j]]\n" if ($debug > 1);
      if ($L[$i] >= $F[$j]) {
	if ($debug) {
	  my $rm = "rm";
	  my $cmd = "ls  -1d  $file*MuDst.root";
	  my @list = `$cmd`; print " @list";
	  for (my $l = 0;  $l < $NoMuFiles; $l++) {
	    for (my $k = 0; $k < $NoMuFiles; $k++) {
	      if ($k == $l) {next;}
	      if ($F[$l] != $F[$k] && $L[$l] != $L[$k]) {next;}
	      my $lfl = $L[$l] - $F[$l];
	      my $kfl = $L[$k] - $F[$k];
#	      print "l = $l: $F[$l] $L[$l], k = $k : $F[$k] $L[$k], lfl = $lfl, kfl = $kfl\n";
	      if ($lfl > $kfl) {
		$rm .= " " . $file . ","  . $F[$k] . "," . $L[$k] . "*"; 
	      }
	    }
	  }
	  if ($rm != "rm") {
	    print "$rm\n";
	    #	  die "died at $file*MuDst.root *$F[$i],$L[$i]* and   *$F[$j],$L[$j]*";
	    open (Out, ">> rm.csh") or die "Can't open rm.csh";
	    print Out "$rm\n";
	    close(Out);
	  }
	}
	`touch Dead`;
	die;
	return 0;
      } else {
	$f = $L[$i] + 1;
	$l = $F[$j] - 1;
	if ($f < $l) {
	  $no += SPrint($line,$file,$f,$l,$debug);
	}
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
PrintHash($def,"Runs") if ($debug > 1);
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

