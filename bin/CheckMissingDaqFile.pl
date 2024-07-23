#! /usr/bin/env perl
use File::Basename;
use Cwd;
use Env;
my $daqFileList = "3p85GeV_fixedTarget.list";
#my $daqFileList = "4p59GeV_fixedTarget.list";
my $recDir = "/gpfs01/star/subsysg/TFG/reco/TFG24c/2019/RF/3p85GeV_fixedTarget";
#y $recDir = "/gpfs01/star/subsysg/TFG/reco/TFG24c/2019/RF/4p59GeV_fixedTarget";
my $debug = 0;
if ($#ARGV >= 0) {
  $daqFileList = $ARGV[0];
  if ($#ARGV >= 1) {
     $recDir = $ARGV[1];
   }
}
print "daqFileList = $daqFileList, recDir = $recDir\n" if ($debug);
open (In,  $daqFileList) or die "Can't open $daqFileList";
my $line;
while ($line = <In>) {
 my ($hpss,$daq) = split(' ', $line);
 print "daq $daq\n" if ($debug);# from $line";
 if (-r $daq) {next;}
 my @words = split('/',$daq);
 my $n = $#words;
 if ($debug) {
   for (my $i = 1; $i <= $n; $i++) {
     print "words[$i] = $words[$i]\n"; 
   }
 }
 my $rec = $recDir . "/" . $words[$n-2] . "/" . $words[$n-1] . "/" .  $words[$n];  print "rec = $rec\n" if ($debug);
 $rec =~ s/.daq/.picoDst.root/; print "rec = $rec\n" if ($debug);
 if (-r $rec) {next;}
 $rec =~ s/picoDst/bla.root/; print "rec = $rec\n" if ($debug);
 if (-r $rec) {next;}
 print "$line";
#die;
}
close(In);
