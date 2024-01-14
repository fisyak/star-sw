#! /usr/bin/env perl
use File::Basename;
use Cwd;
my $pwd = cwd(); #print "pwd = $pwd\n";
my $FIELD = "";
my $year  = "";
my $debug = 0;
if ($#ARGV >= 0) {
  $debug = $ARGV[0];
}
if    ($pwd =~ /2019/) {$year = "2019";}
elsif ($pwd =~ /2020/) {$year = "2020";}
elsif ($pwd =~ /2021/) {$year = "2021";}
elsif ($pwd =~ /2022/) {$year = "2022";}
elsif ($pwd =~ /2023/) {$year = "2023";}
if    ($pwd =~ /FFI/) {$FIELD = "FFI";}
elsif ($pwd =~ /RFI/) {$FIELD = "RFI";}
elsif ($pwd =~ /FF/) {$FIELD = "FF";}
elsif ($pwd =~ /RF/) {$FIELD = "RF";}
elsif ($pwd =~ /ZF/) {$FIELD = "ZF";}
#print "FIELD = $FIELD\n";
if (! $FIELD) {die "Field is not defined";}
#my $glob = "/hlt/cephfs/reco/2019/" . $FIELD . "/*.event.root"; #print "glob = $glob\n";
#my $glob = "/net/l401/data/scratch1/reco/2019/" . $FIELD . "/*.event.root"; #print "glob = $glob\n";
#my $glob = "/hlt/cephfs/reco/" . $year . "/.DEV2/" . $FIELD . "/Cosmic/*.event.root"; #print "glob = $glob\n";
#my $glob = "/hlt/cephfs/reco/" . $year . "/" . $FIELD . "/Cosmic/*/*/*.event.root"; print "glob = $glob\n" if ($debug);
#my $glob = "/hlt/cephfs/reco/" . $year . "/Cosmic/" . $FIELD . "/*/*/*.event.root"; print "glob = $glob\n" if ($debug);
#my $glob = "/hlt/cephfs/reco/Cosmics/" . $year . "/" . $FIELD . "/*/*/*.event.root"; print "glob = $glob\n" if ($debug);
my $glob = "/hlt/cephfs/reco/CosmicsB/" . $year . "/" . $FIELD . "/*/*/*.event.root"; print "glob = $glob\n" if ($debug);
my $glob = "/hlt/cephfs/reco/CosmicsC/" . $year . "/" . $FIELD . "/*/*/*.event.root"; print "glob = $glob\n" if ($debug);
my @Files = glob $glob; print "Files = @Files\n" if $debug;
my $n = 0;
foreach my $file (@Files) {
  my $bf = File::Basename::basename($file,".event.root"); print "bf = $bf\n"  if $debug;
  my $glob = $bf . "*";
  my @list = glob "$glob"; print "list = $#list => @list\n"  if $debug;
  if ($#list > -1) {next;}
#  my ($dev,$ino,$mode,$nlink,$uid,$gid,$dev, $size, $atime, $mtim, $ctime, $blksize,$blocks) = stat($file);
#  my $now = time(); #print "now = $now\n";
#  my $dt = $now - $ctime;# print "now = $now, ctime = $ctime, dt = $dt\n";
#  if ($dt < 3600) {next;}
  
  my $string = "string:" .  $file;
  print "$string\n";
  $n++;
#  if ($n >= 500) {last;}
}
