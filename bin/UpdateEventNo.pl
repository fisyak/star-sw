#! /usr/bin/env perl
# add first ; last event no. to file name from Chai.log
use File::Basename;
use Cwd;
use Env;
my $Chain = "Chain.log";
open(In, $Chain) or die "Can't open $Chain";
while (my $line = <In>) {
  if ($line !~ /No.Events =/) {next;}
#  print "$line";
  my ($dummy,$dummy,$mudst,$dummey,$dummy,$dummy,$dummy,$dummy,$NoEvents) = split(' ',$line);
  if (! -r $mudst) {next;}
  my $b = File::Basename::basename($mudst,".MuDst.root");
  my ($dummy,$f,$l) = split(',',$b);
  my $oldN = $f . "," . $l;
  my $ll = $f - 1 + $NoEvents;
  my $newN = $f . "," . $ll;
#  print "$b, No = $NoEvents , $oldN => $newN \n";
  if ($oldN eq $newN) {next;}
  my $n = $b;
  $n =~ s/$oldN/$newN/;
  print "--------------------------------------------------------------------------------\n";
#  if ($b =~ m/\,/) {next;}
  print "$NoEvents events in  $b => $n\n";
  my @files = glob $b . "*";
  foreach my $oldF (@files){
    my $newF = $oldF;
    $newF =~ s/$b/$n/;
#    $newF =~ s/B\.log/.log/;
    my $cmd = "mv $oldF $newF";
    print "$cmd\n";
    my $status = 0xffff & system($cmd);
    if ($status) {die "Can't do $cmd";}
  }
}
close(In);
#st_physics_20180009_raw_1500003,1,5000.MuDst.root     size = 738197504        No.Events = 4893
