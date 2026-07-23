#! /usr/bin/env perl
use File::Basename;
use Cwd;
my $list = "9p8GeV_fixedTarget_2026.list";
if ($#ARGV >= 0) {
  $list = $ARGV[0];
}
my $pwd = cwd();
my $DAQ_DIR = "/gpfs01/star/daq/2026";
my $prod = File::Basename::basename($list,".list");
my $RECO_DIR = "/gpfs01/star/data100/TPC/reco/TFG26d/2025/RF/" . $prod;
my $list_sorted = $list . ".sorted";
open(IN,$list_sorted) or die "Can't open $list_sorted";
my $run_old = 0;
my $done = 0;
my $nofiles = 0;
my $daq_list = $list . ".daq";
open(DAQ,">$daq_list") or die "Can't open $daq_list";
while (my $line =  <IN>) {
#  print "$line";
  my @words = split(":",$line);
#  for (my $i = 0; $i < $#words; $i++) {print "words[$i] = $words[$i]\n";}
  my $hpss_path = $words[0];
  my $base_name = $words[2];
  my $noeve     = $words[4];
  my $run_name = $hpss_path;                       # print "run_name  = $run_name \n";
  $run_name =~ s|/home/starsink/raw/daq/2026||; # print "run_name  = $run_name \n";
  my $run_number = File::Basename::basename($run_name); # print "run_number = $run_number\n";
  my $dir_name = $DAQ_DIR . $run_name;             # print "dir_name  = $dir_name \n";
  if ($base_name =~ /st_physics_adc/) {next;}
  if ($base_name !~ /st_physics_/) {next;}
  my $hpss_file = $hpss_path . "/" . $base_name . ".daq";
  my $nfs_file  = $dir_name  . "/" . $base_name . ".daq";
  if (-r $nfs_file) {print "$nfs_file exists\n"; next;}
  my $cmd =  $hpss_file . "   " . $nfs_file;
  my $out_dir = $RECO_DIR  . $run_name;
  if (! -d $out_dir) {
    next; #`mkdir -p $out_dir`;
  }
  if ($run_old != $run_number) {
#    die if $run_old > 0;
    my @list_eve = `ls -1 $out_dir/*.noeve`;
#    print "$run_number -> $#list_eve\n";
    $done = $#list_eve + 1;
    $nofiles = 0;
    $run_old = $run_number;
  }
  if ($run_old == $run_number && $nofiles > 2*$done + 1) {next;}
  my $eve_file = $out_dir  . "/" . $base_name . ".noeve";
  if (-r $eve_file) {print "$eve_file exists\n"; next;}
#  print "$eve_file $noeve\n";
  open(OUT,">$eve_file") or die "Can't open $eve_file";
  print OUT "$noeve";
  close(OUT);
  print DAQ "$cmd\n";
  print "$cmd\n";
  $nofiles++;
}
close(DAQ);
