#! /usr/bin/env perl
use File::Basename;
use Cwd;
if ($#ARGV < 0) {
  print "Usage: $0 no_of_runs\n";
  exit 0;
}
my $rung1 = 1;
my $rung2 = 1;
if ($#ARGV == 0) {
  $rung1 = $ARGV[0];
  $rung2 = $rung1;
}
if ($#ARGV >= 1) {
  $rung1 = $ARGV[0];
  $rung2 = $ARGV[1];
}
my $nevents = 100;
if ($#ARGV >= 2) {
  $nevents = $ARGV[2];
}
my $name .= "," . File::Basename::basename(cwd());
if ($#ARGV >= 3) {
  $name = $ARGV[3];
}
#
for (my $rung = $rung1; $rung <= $rung2; $rung++) {
  my $file = "flux" . $name . $rung . ".root";
#  print "file = $file\n";
  if (! -r $file) {
    print "string:$name:$rung:$nevents\n";
  }
 # last;
}
#endif
