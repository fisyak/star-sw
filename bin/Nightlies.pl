#! /usr/bin/env perl
use File::Basename;
use Cwd;
use Env;
my $makeList = 0;
my $NoEvents = 100;
my $pwd = cwd();
my $extra = ""; #,picoWrite";
my $noMC = `whcih root4star`;
my $bit64 = 0;
if ($pwd =~ /x8664/) { $bit64 = 1;}
my $opt = 0;
if ($pwd =~ /_opt/)  {$opt = 1;}
if ($pwd =~ /StiCA/) {$extra .= ",StiCA";}
if ($pwd =~ /KF/) {$extra .= ",KFVertex";}
#if ($pwd =~ /x8664/) {$noMC = 1;} #print "noMC = $noMC\n";
#if ($pwd =~ /al9/) {$noMC = 1;} #print "noMC = $noMC\n";
my $file = "/star/u/fisyak/bin/Nightlies.list";
open(In, $file) or die "Can't open $file";
while ( my $it = <In>) {
#  print "$it";
  my ($string,$chain,$DIR,$f,$NoEvents,$ref) = split(":",$it);
  if ($string ne 'string') {next;}
  if ($noMC and $DIR =~ /MC/) {next;}
  if (  $bit64 and $DIR !~ /_64bit/) {next;}
  if (! $bit64 and $DIR =~ /_64bit/) {next;}
  if (  $opt and $DIR !~ /_opt/) {next;}
  if (! $opt and $DIR =~ /_opt/) {next;}
  my $log = $DIR . "/" . $f . ".log"; 
  if (-r $log) {next;}
  print "$string:$chain$extra:$DIR:$f:$NoEvents:$ref";
}

