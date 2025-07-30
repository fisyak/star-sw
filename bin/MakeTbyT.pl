#!/usr/bin/env perl
use File::Basename;
use Cwd;
my $macro = "RunTbyT";
my $debug = 0;
if ($#ARGV >= 0) {
  $debug = $ARGV[0];
}
my @FilesNew = glob "new/*.event.root"; print "FilesNew @FilesNew\n" if $debug;
my @FilesOld = glob "old/*.event.root"; print "FilesOld @FilesOld\n" if $debug;
my $DIR = cwd();
my $CONDOR = "submit.condor";
open (CONDOR,">$CONDOR") or die "Can't open $CONDOR";
foreach my $newf (@FilesNew) {
  my $nff = File::Basename::basename($newf);  print "$newf => $nff\n" if ($debug >1);
  foreach my $oldf (@FilesOld) {
    my $off = File::Basename::basename($oldf);  print "$oldf => $off\n" if ($debug >1);
    if ($nff ne $off) {next;}
    my $root = $off;
    $root =~ s/.event.root//;
    print "================\n$oldf\n$newf => $root\n";
    my $RootFile = $root . ".root";
    next if -r $RootFile;
    my $SCRIPT = $root . ".csh";
    my $LOG = $root . ".log";
    print "Create $SCRIPT\n";
    open (OUT,">$SCRIPT") or die "Can't open $SCRIPT";
    print OUT "#! /usr/local/bin/tcsh -f\n";
#    print OUT "source /afs/.rhic.bnl.gov/star/group/.starver .DEV2;\n";
    my $cmd = "";
    $cmd .= "test ! -r " . $RootFile  . " && root -l -q -b  '" . $macro;
    $cmd .= ".C(1000000,\"" . $oldf . "\",\"" . $newf . "\",\"" . $RootFile  . "\")\' >& $LOG";
    print OUT "$cmd\n";
    close (OUT);
    chmod 0755, $SCRIPT;
	print CONDOR "
Universe         = vanilla
Notification     = never
Executable       = /bin/csh
Arguments        = \"-c 'exec " . $DIR . "/" . $SCRIPT . "'\"
Output           = " . $DIR . "/" . $SCRIPT . ".log
Log              = " . $DIR . "/" . $SCRIPT . ".condor.log
Error            = " . $DIR . "/" . $SCRIPT . ".condor.err
Initialdir       = " . $DIR . "
kill_sig        = SIGINT
PeriodicRemove   = (NumJobStarts >=1 && JobStatus==1) || (JobStatus == 2 && (CurrentTime - JobCurrentStartDate > (54000)) && ((RemoteUserCpu+RemoteSysCpu)/(CurrentTime-JobCurrentStartDate) < 0.10)) || (((CurrentTime - EnteredCurrentStatus) > (2*24*3600)) && JobStatus == 5) || (JobRunCount >= 1 && JobStatus == 1)
Priority         = +10
requirements = (Microarch == \"x86_64-v4\")
GetEnv          = True
Queue
";
  }
}
close(CONDOR);
