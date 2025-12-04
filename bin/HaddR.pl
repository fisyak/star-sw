#! /usr/bin/env perl
use Cwd;
use Env;
my $PWD = cwd();
#my @List = `ls -1d ../R*_*.root | sed -e 's/R//' -e 's/_.*//' -e 's/\.\.\///' | sort -u`;
my @List = `cat Run.list`;
foreach my $run (@List) {
  chomp($run);
  my $out = "R" . $run . ".root";
  if (-r $out) {next;}
  my $script = "R" . $run . ".csh";
  open (OUT, ">$script") or die "Can't open $script";
  my $cmd = "cd " . $PWD . "; /usr/bin/test ! -r ". $out . "&& hadd " . $out . " ../R" . $run . "_*.root >& R" . $run . ".log";
  print OUT "$cmd\n";
  close (OUT);
  `chmod +x $script`;
}
__END__
foreach my $run (@List) {
  chomp($run);
  my $out = "R" . $run . ".root";
  if (-r $out) {next;}
  my $args = $PWD . "/" . $out . " " . $PWD . "/" . "R" . $run . "_*.root >& R" . $run . ".log"";
  my $log = "R" . $run . ".log";
}
  my $err = "R" . $run . ".err";
  my $condor = "R" . $run . ".condor"; print "condor = $condor\n";
  open (Out, ">$condor") or die "Can't open $condor";
  print Out "
Universe         = vanilla
Notification     = never
Executable       = $ROOTSYS/bin/hadd
Arguments        = \"$args\"
Error            = $err
Log              = $log 
Initialdir       = $PWD
kill_sig         = SIGINT
PeriodicRemove   = (NumJobStarts >=1 && JobStatus==1) || (JobStatus == 2 && (CurrentTime - JobCurrentStartDate > (54000)) && ((RemoteUserCpu+RemoteSysCpu)/(CurrentTime-JobCurrentStartDate) < 0.10)) || (((CurrentTime - EnteredCurrentStatus) > (2*24*3600)) && JobStatus == 5) || (JobRunCount >= 1 && JobStatus == 1)
Priority         = +10
requirements = (Microarch == \"x86_64-v4\")
GetEnv          = True

Queue
";
close(Out);
