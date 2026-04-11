#!/usr/bin/env perl
use File::Basename;
use Cwd;
my $daq = "";
my $reduction = 20;
my $pwd = cwd();
my $debug = 0;
# if ($#ARGV < 0) {
#   print "Usage: cd /hlt/cephfs/daq/2021/142; $0 20\n";
#   exit;
# } else {
#   $reduction = $ARGV[0];
# }
if ($reduction <= 1 || $reduction > 100) {die "Illegal reduction factor = $reduction";}
#my @runlist = glob "22*"; #print "\# $#runlist = @runlist\n";
my $input_file = "cosmic_2025_RF.list";
open(IN, $input_file) or die "Can't open $input_file";
my $oldrun = 0;
my $count = 0;
while (my $line = <IN>) {
  chomp($line);
  if ($line =~ /_adc_/) {next;}
#  print "$line\n";
  my @w = split('/',$line);
  my $run = $w[7]; print "run = $run\n" if $debug;
  if ($run == $oldrun) {
    $count++;
  } else {
    $oldrun = $run;
    $count = 1;
  }
  if ($count%$reduction == 1) {
    my $newline = $line;
    $newline =~ s#/home/starsink/raw#/gpfs01/star/data100/TPC#;
      print "take:$count\t$line\n" if $debug;
      print "$line $newline\n";
  } else {
    print "skip:$count\t$line\n" if $debug;
  }
}
close(IN);
