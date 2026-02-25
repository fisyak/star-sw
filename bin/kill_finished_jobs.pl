#! /usr/bin/env perl
use File::Basename;
use Cwd;
my $dir =  File::Basename::basename(Cwd::cwd());
my @JobList = `condor_q -wide | grep -w R |  grep $dir`; 
my $debug = 0;
my @ids = ();
foreach my $job (@JobList) {
  print "$job" if ($debug);
  my @words = split(' ',$job);
#  for (my $i = 0; $i <= $#words; $i++) {print "$i @words[$i]\n"}
  my $id = $words[0];
  my $sched = $words[$#words];
  $sched =~ s/\'//g;
  print "id = $id, sched = $sched\n" if ($debug);
  open(IN,$sched) or die "Can'open $sched";
  while ($line = <IN>) {
    if ($line !~ /setenv INPUTFILE0/) { next;}
    print $line if ($debug);
    my ($dum,$run,$dum) = split('"',$line);
    print "run $run\n" if ($debug);
    my $log = $run . "B.log";
    if (! -r $log) {
      if (-r $run) {
	open(RUN,$run) or die "Can't open $run";
	while ($rf = <RUN>) {
	  if ($rf !~ />>&/) {next;}
	  print  "$rf" if ($debug);
	  my @w = split(' ',$rf);
	  if ($debug) {
	    for (my $i = 0; $i <= $#w; $i++) {print "$i @w[$i]\n"}
	  }
	  $log = $w[$#w];
	  $log =~ s/;//;
	  if (! -r $log) {next;}
	  last;
	}	
	close (RUN);
      }
    }
    if (! -r $log) {last;}
    print "log = $log\n" if ($debug);
    #      my $cmd = "grep -l 'Run is finished' $log";
    my $cmd = "grep -l 'This is the end of STAR ROOT -- Goodbye' $log";
    print "$cmd\n" if ($debug);
    my $flag = system($cmd);
    print "flag = $flag\n" if ($debug);
    if ($flag == 0) {
      push @ids, $id;
      last;;
    }
  }
}
if ($#ids > -1) {print "condor_rm  @ids\n";}
##1675128.65  fisyak          1/24 09:31   0+01:42:12 R  12  1465.0 sh -c exec' '/star/u/fisyak/work/dEdx/jobs/schedE2A28C5D5C5FBDF44E58B2DC8FDED8DC_634.csh
