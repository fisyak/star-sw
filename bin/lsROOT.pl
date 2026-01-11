#! /usr/bin/env perl
use File::Basename;
use Cwd;
#my $glob =  "/net/l404/data/fisyak/Pico/BES-I/AuAu19_production/2011/???/*";
#my $glob =  "/net/l401/data/scratch2/kehw/reco/2019/???/*";
#my $glob =  "/net/l401/data/scratch2/kehw/reco/2019/TFG19d/???/*";
#my $glob =  "/net/l401/data/scratch2/kehw/reco/2019/14GeV_2019_StiCA/0??/*";
my $glob; 
if ($#ARGV >= 0) {
  $glob = $ARGV[0];
} else {
  print "$0 path_to_root_files\n";
  exit 0;
}
my $total = 5000;
my $ext = "";
my $extq = "";
my $pwd = cwd();
my $dir = File::Basename::basename($pwd);
if ($dir =~ /,/) {
  my @w = split(',',$dir);
  my $f = int $w[0];
  my $l = int $w[1];
  $ext = ":" . $f . ":" . $l;
  $extq = "," . $f . "," . $l;
#  print "f = $f, l = $l ext = $ext\n";
#  die;
}
my $i = 0;
foreach my $file (glob $glob .  "/*.root") {
  $i++;
  if ($i > $total) {last;}
  my $f = File::Basename::basename($file,".root");
#  print "file = $file => f = $f\n";
  my @list = glob $f . $extq . "*.root";
  if ( $#list >= 0) {next};
  print "string:$file$ext\n";
#  last;
}
