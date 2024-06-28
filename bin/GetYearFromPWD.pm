#! /usr/bin/env perl
#package GetYearFromPWD;
use File::Basename;
use Cwd;
use Env;
use strict;
use warnings;
#use Exporter 5.57 'import';
#____________________________________________________________
sub PrintHash($$) {
  my $env = shift; # print "Call PrintHash\n";
  my $prefix = shift;
  foreach my $key (sort keys %$env ) {
    print "{ $key }\t=> {'$env->{$key}->{trig}', \tfield=>`$env->{$key}->{field}',\tfirst=>'$env->{$key}->{first}', \tlast=>'$env->{$key}->{last}', \tbeginTime=>'$env->{$key}->{beginTime}'\n";
  }
}
#____________________________________________________________
sub GoodRun($$$) {
  my $env = shift;
  my $run = shift;
  my $debug = shift;
  print "GoodRun:: run = $run" if $debug;
  my $pwd = cwd(); #print "pwd = $pwd\n";
  foreach my $key (sort keys %$env ) {
    print "$pwd, trig = $env->{$key}->{trig}, field = $env->{$key}->{field}; first = $env->{$key}->{first}, last = $env->{$key}->{last}" if ($debug);
    if ($pwd !~ /$env->{$key}->{trig}/)  {print ", rejected by trig\n"  if ($debug); next;}
    if ($pwd !~ /$env->{$key}->{field}/) {print ", rejected by field\n" if ($debug); next;}
    if ($run < $env->{$key}->{first})     {print ", rejected by first\n" if ($debug); next;}
    if ($run > $env->{$key}->{last})      {print ", rejected by last\n"  if ($debug); next;}
    print " accepted\n" if ($debug);
    return $run;
  }
  print " rejected\n" if ($debug);
  return -1;
}
#__________________________________________________________________________________________
sub GetRuns($) {
  my $debug = shift;
#  print "debug = $debug\n";
  my $pwd = cwd(); #print "pwd = $pwd\n";
  my $year  = "";
  my $FIELD = "";
  my @words = split('/',$pwd);
  my $nw = $#words;
  my $i1 = -1;
   for (my $i = $nw; $i > 0; $i--) {
     print "words[$i] = |$words[$i]|,\t" if ($debug);
     if ($words[$i] =~ /\D/) {last;}
     $i1 = $i;
   }
   print "i1 = $i1\n" if ($debug);
  
#   die;
  my $Day =   "[0-3]??";  my $Run = "[0-9]???????";
  if    ($i1 <  0)   {}
  elsif ($i1 == $nw) {$Day = $words[$i1];   $Run = "[0-9]???????";}
  elsif ($i1 <  $nw) {$Day = $words[$nw-1]; $Run = $words[$nw];}
  if    ($pwd =~ /2019/) {$year = "2019"; require RunXIXDefs;}
  elsif ($pwd =~ /2020/) {$year = "2020"; require RunXXDefs;}
  elsif ($pwd =~ /2021/) {$year = "2021"; require RunXXIDefs;}
  elsif ($pwd =~ /2022/) {$year = "2022"; require RunXXIIDefs;}
  elsif ($pwd =~ /2023/) {$year = "2023"; require RunXXIIIDefs;}
  elsif ($pwd =~ /2024/) {$year = "2024"; require RunXXIVDefs;}
  our @Runs;
  my $def = {@Runs};
#  PrintHash($def,"Runs");
  if    ($pwd =~ /FFI/) {$FIELD = "FFI";}
  elsif ($pwd =~ /RFI/) {$FIELD = "RFI";}
  elsif ($pwd =~ /FF/) {$FIELD = "FF";}
  elsif ($pwd =~ /RF/) {$FIELD = "RF";}
  elsif ($pwd =~ /ZF/) {$FIELD = "ZF";}
  #$ENV{YEAR} = $year;
  #$ENV{FIELD} = $FIELD;
  my $runs = "/hlt/cephfs/daq/" . $year . "/" . $Day . "/" .  $Run;
  my $run2 = "";
  if ($year == "2020") {
    $runs = "/hlt/cephfs/daq/2019/" . $Day . "/" .  $Run;
    $run2 = "/hlt/cephfs/daq/2020/" . $Day . "/" .  $Run;
  } elsif ($year == "2021") {
    $runs = "/hlt/cephfs/daq/2020/" . $Day . "/" .  $Run;
    $run2 = "/hlt/cephfs/daq/2021/" . $Day . "/" .  $Run;
  } elsif ($year == "2022") {
    $runs = "/hlt/cephfs/daq/2021/" . $Day . "/" .  $Run;
    $run2 = "/hlt/cephfs/daq/2022/" . $Day . "/" .  $Run;
  }
  return ($year,$FIELD,$runs,$def,$Day,$Run,$run2);
}
#__________________________________________________________________________________________
sub GetHash() {
  my $pwd = cwd(); print "pwd = $pwd\n";
  my $year;
  if    ($pwd =~ /2019/) {$year = "2019"; require RunXIXDefs;}
  elsif ($pwd =~ /2020/) {$year = "2020"; require RunXXDefs;}
  elsif ($pwd =~ /2021/) {$year = "2021"; require RunXXIDefs;}
  elsif ($pwd =~ /2022/) {$year = "2022"; require RunXXIIDefs;}
  elsif ($pwd =~ /2023/) {$year = "2023"; require RunXXIIIDefs;}
  elsif ($pwd =~ /2024/) {$year = "2024"; require RunXXIVDefs;}
  our @Runs;
  my $def = {@Runs};
  return ($def, $year);
}
1;
