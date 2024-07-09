#! /usr/bin/env perl
use File::Basename;
use Cwd;
use Env;
#print "$0\n";
#use lib dirname $0; # 
use lib "/net/l402/data/fisyak/STAR/packages/.DEV2/bin";
use GetYearFromPWD;
my $debug = 0;
if ($#ARGV >= 0) {
  $debug = $ARGV[0];
}
my $fNoMax = -1;
if ($#ARGV >= 1) {
  $fNoMax = $ARGV[1];
  print "fNoMax = $fNoMax\n";
}
my ($year,$FIELD,$runs,$env,$Day,$Run,$run2) = GetRuns($debug);
print "$0 Year = $year, Field = $FIELD, runs = $runs, env = $env,  Day = $Day, Run = $Run, run2 = $run2\n" if ($debug);
if (! $year || ! $FIELD) {die "wrong directory $pwd";}
#PrintHash($env,"Runs") if ($debug);
my $fNo = 0;
my @AllRuns = ($runs);
if ($run2) {push @AllRuns, $run2;}
sub nextkey($$) {
  my $env = shift;
  my $k1 = shift;
  my @keys = sort keys %$env;
  my $N = $#keys; print "N  = $N\n" if ($debug);
  my $pwd = cwd(); #print "pwd = $pwd\n";
  my $k = -1;
  my $key;
  foreach $key (@keys) {
    $k++;
    if ($k < $k1) {next;}
    if ($pwd !~ /$env->{$key}->{trig}/)  {print "$pwd  rejected by trig $env->{$key}->{trig} \n"  if ($debug); next;}
    if ($pwd !~ /$env->{$key}->{field}/) {print "$pwd  rejected by field $env->{$key}->{field}\n" if ($debug); next;}
    print "k = $k, key = $key\n" if ($debug);
    return ($k,$key);
    #    last;
  }
  return (-1,-1);
}
my $k1 = 0;
my ($k,$key) = nextkey($env,$k1); 

my $runMin =   $env->{$key}->{first};
my $runMax =   $env->{$key}->{last};  print "k1 = $k1, k = $k, runMin = $runMin, runMax = $runMax\n" if ($debug);
$k1 = $k + 1;
my $list = "../../../" . $year . "daq.List";
open (In, $list) or die "Can't open $list";
my $line;
while ($line = <In>) {
  if ($line !~ /st_physics_/) {next;}
  my $run =  File::Basename::basename(File::Basename::dirname($line)); #print "run = $run\n" if ($debug);
  if ($run < $runMin) {next;}
  print "line = $line" if ($debug);
  print "run = $run, runMin = $runMin, runMax = $runMax\n" if ($debug);
 LOOP:
  if ($run < $runMin) {
    next;
  } elsif ($run <=  $runMax) {
    print "$line";
#    die;
    next;
  } else {
    ($k,$key)  = nextkey($env,$k1); 
    if ($k < 0) {last;}
    $runMin =   $env->{$key}->{first};
    $runMax =   $env->{$key}->{last};  print "k1 = $k1, k = $k, runMin = $runMin, runmax = $runMax\n" if ($debug);
    $k1 = $k + 1;
    goto LOOP;
  }
} 
close(In);
# 20002001
  20179039 
