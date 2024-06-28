#! /usr/bin/env perl
use File::Basename;
use Cwd;
use Env;
#print "$0\n";
#use lib dirname $0; # 
use lib "/net/l402/data/fisyak/STAR/packages/.DEV2/bin";
# use  RunXIXDefs;
use GetYearFromPWD;
my $debug = 1;
if ($#ARGV >= 0) {
  $debug = $ARGV[0];
}
my ($year,$FIELD,$runs,$env,$Day,$Run,$run2) = GetRuns(0);
#print "$0 Year = $year, Field = $FIELD, runs = $runs, env = $env,  Day = $Day, Run = $Run, run2 = $run2\n" if ($debug);
#PrintHash($env,"Runs") if ($debug);
# # my $pwd = cwd(); print "pwd = $pwd\n";
# #  my $year;
# #  if    ($pwd =~ /2019/) {$year = "2019"; require RunXIXDefs;}
# #  elsif ($pwd =~ /2020/) {$year = "2020"; require RunXXDefs;}
# #  elsif ($pwd =~ /2021/) {$year = "2021"; require RunXXIDefs;}
# #  elsif ($pwd =~ /2022/) {$year = "2022"; require RunXXIIDefs;}
# #  elsif ($pwd =~ /2023/) {$year = "2023"; require RunXXIIIDefs;}
# #  elsif ($pwd =~ /2024/) {$year = "2024"; require RunXXIVDefs;}
# our @Runs;
# my $env = {@Runs}; print "env = $env\n";
my $N = 0;
foreach my $key (sort keys %$env ) {
#  print "{ $key }\t=> {'$env->{$key}->{trig}', \tfield=>`$env->{$key}->{field}',\tfirst=>'$env->{$key}->{first}', \tlast=>'$env->{$key}->{last}', \tbeginTime=>'$env->{$key}->{beginTime}'\n";
  for (my $run = $env->{$key}->{first}; $run <= $env->{$key}->{last}; $run++) {
    my $cmd = "mysql -h robinson.star.bnl.gov --port=3306 -u \"fisyak\" RunLog_onl -e 'select beginTime,runNumber,blueIntensity,yellowIntensity from beamInfo where runNumber = " . $run . ";'";
#    print "$cmd\n";
    my @list = `$cmd`;
#    print "$list[1]";
    my ($date,$time,$run,$blueIntensity,$yellowIntensity) = split(' ',$list[1]);
#    print "date = $date, time = $time, run = $run, blueIntensity = $blueIntensity, yellowIntensity = $yellowIntensity\n";
    my $max = $blueIntensity;
    if ($max < $yellowIntensity) {$max = $yellowIntensity;}
    my $min = $blueIntensity;
    if ($min > $yellowIntensity) {$min = $yellowIntensity;}
    my $FXT = 0;
    if ($max > 0.5 && $max > 100*$min) {$FXT = 1;}
    if (  $FXT && $env->{$key}->{trig} =~ /fixed/) {next;}
    if (! $FXT && $env->{$key}->{trig} !~ /fixed/) {next;}
    if (  $FXT) {print "Non fixed taget run is marker as fixed,";}
    if (! $FXT) {print "fixed taget run is marker as non fixed,";}
    print "date = $date, time = $time, run = $run, blueIntensity = $blueIntensity, yellowIntensity = $yellowIntensity\n";
    $N++;
#    if ($N > 5) {die;}
  }
}
