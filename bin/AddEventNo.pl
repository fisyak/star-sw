#! /usr/bin/env perl
# add first ; last event no. to file name from Chai.log
use File::Basename;
use Cwd;
use Env;
my $Chain = "Chain.log";
open(In, $Chain) or die "Can't open $Chain";
while (my $line = <In>) {
  if ($line !~ /No.Events =/) {next;}
  my ($dummy,$dummy,$mudst,$dummey,$dummy,$dummy,$dummy,$dummy,$NoEvents) = split(' ',$line);
  if (! -r $mudst) {next;}
  my $b = File::Basename::basename($mudst,".MuDst.root");
  if ($b =~ m/\,/) {next;}
  my @files = glob $b . "*";
  print "$file $NoEvents $b => @files\n";
  my $n = $b . ",1," . $NoEvents;
  foreach my $oldF (@files){
#    if ($oldF =~ m/*\d,*\d/) {next;}
#    print "$oldF\n";
    if ($oldF =~ /\,/) {next;}
#    print not "matched\n";
    my $newF = $oldF;
    $newF =~ s/$b/$n/;
    $newF =~ s/B\.log/.log/;
    my $cmd = "mv $oldF $newF";
    print "$cmd\n";
    my $status = 0xffff & system($cmd);
    if ($status) {die "Can't do $cmd";}
  }
}
close(In);
