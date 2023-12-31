#! /usr/bin/env perl
use File::Basename;
use Cwd;
use Env;
my $pwd = cwd();
my $path = "/hlt/cephfs/daq/";
my $year = "2019";
if    ($pwd =~ /2019/) {$year = "2019";}
elsif ($pwd =~ /2020/) {$year = "2020";}
elsif ($pwd =~ /2021/) {$year = "2021";}
elsif ($pwd =~ /2022/) {$year = "2022";}
elsif ($pwd =~ /2023/) {$year = "2023";}
else {
 die;
}
my @words = split('/',$pwd);
my $nw = $#words;
#print "$words[$nw-1] $words[$nw]\n";
$path .= $year . "/" . $words[$nw-1] . "/" . $words[$nw] . "/*.daq"; # print "path = $path\n";
my @list = glob $path;
#print "@list\n";
my $fNo = 0;
foreach my $file (@list) {
  my $rootf = File::Basename::basename($file,".daq") . ".root";
  if (-r $rootf) {next;}
  print "string:$file\n";
  $fNo++;
#  last;
}
if (! $fNo) {die "Don't have input files\n";}
