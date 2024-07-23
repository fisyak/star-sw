#! /usr/bin/env perl
use File::Basename;
$debug = 0;
if ($#ARGV >= 0) {
  $debug = $ARGV[0];
}
my @MuList = glob "*/*/*MuDst.root";
print "MuList = @MuList\n" if ($debug);
foreach my $mu (@MuList) {
  my $pico = $mu;
  $pico =~ s/Mu/pico/;
  if (-r $pico) {
    print "$mu => $pico\n" if ($debug);
  } else {
    print "string:$mu\n";
#    last;
  }
}
