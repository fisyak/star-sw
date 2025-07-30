#! /usr/bin/env perl
# daqList4Pico.pl /gpfs01/star/data14/GRID/NFS_FileList/production_4p59GeV_fixedTarget_2019_P24iy_SL24c_64b.picodst.txt
use File::Basename;
use Cwd;
use Env;
my $file = "";
if ($#ARGV >= 0) {
  $file = $ARGV[0];
} else {
  die if $file == "";
}
open(In, $file) or die "Can't open $file";
while ( my $line = <In>) {
  chomp($line);
  my @words = split('/',$line);
  my $string = "";
  for (my $i = 7; $i < 11;  $i++) {
    if ($words[$i] =~ /root/) {
      $words[$i] =~ s/picoDst\.root/daq/;
      $words[$i] =~ s/MuDst\.root/daq/;
    }
    $string .= "/" . $words[$i];
  }
  print "$string\n";
}
close (in);
