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
  print "GoodRun:: run = $run" if $debug > 1;
  my $pwd = cwd(); print "pwd = $pwd\n" if ($debug > 2);;
  foreach my $key (sort keys %$env ) {
    print "$pwd, trig = $env->{$key}->{trig}, field = $env->{$key}->{field}; first = $env->{$key}->{first}, last = $env->{$key}->{last}" if ($debug > 1);
    if ($pwd !~ /$env->{$key}->{field}/) {print ", rejected by field\n" if ($debug > 1); next;}
    if ($pwd !~ /$env->{$key}->{trig}/)  {print ", rejected by trig\n"  if ($debug > 1); next;}
    if ($run < $env->{$key}->{first})     {print ", rejected by first\n" if ($debug > 1); next;}
    if ($run > $env->{$key}->{last})      {print ", rejected by last\n"  if ($debug > 1); next;}
    print " accepted\n" if ($debug > 1);
    return $run;
  }
  print " rejected\n" if ($debug > 1);
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
  if    ($pwd =~ /\/2001\//) {die;}
  elsif ($pwd =~ /\/2002\//) {die;}
  elsif ($pwd =~ /\/2003\//) {$year = "2003"; require RunIIIDefs; die;}
  elsif ($pwd =~ /\/2004\//) {$year = "2004"; require RunIVDefs;}
  elsif ($pwd =~ /\/2005\//) {$year = "2005"; require RunVDefs;}
  elsif ($pwd =~ /\/2006\//) {$year = "2006"; require RunVIDefs; die;}
  elsif ($pwd =~ /\/2007\//) {$year = "2007"; require RunVIIDefs; die;}
  elsif ($pwd =~ /\/2008\//) {$year = "2008"; require RunVIIIDefs;}
  elsif ($pwd =~ /\/2009\//) {$year = "2009"; require RunIXDefs;}
  elsif ($pwd =~ /\/2010\//) {$year = "2010"; require RunXDefs;}
  elsif ($pwd =~ /\/2011\//) {$year = "2011"; require RunXIDefs;}
  elsif ($pwd =~ /\/2012\//) {$year = "2012"; require RunXIIDefs;}
  elsif ($pwd =~ /\/2013\//) {$year = "2013"; require RunXIIIDefs;}
  elsif ($pwd =~ /\/2014\//) {$year = "2014"; require RunXIVDefs;}
  elsif ($pwd =~ /\/2015\//) {$year = "2015"; require RunXVDefs;}
  elsif ($pwd =~ /\/2016\//) {$year = "2016"; require RunXVIDefs;}
  elsif ($pwd =~ /\/2017\//) {$year = "2017"; require RunXVIIDefs;}
  elsif ($pwd =~ /\/2018\//) {$year = "2018"; require RunXVIIIDefs;}
  elsif ($pwd =~ /\/2019\//) {$year = "2019"; require RunXIXDefs;}
  elsif ($pwd =~ /\/2020\//) {$year = "2020"; require RunXXDefs;}
  elsif ($pwd =~ /\/2021\//) {$year = "2021"; require RunXXIDefs;}
  elsif ($pwd =~ /\/2022\//) {$year = "2022"; require RunXXIIDefs;}
  elsif ($pwd =~ /\/2023\//) {$year = "2023"; require RunXXIIIDefs;}
  elsif ($pwd =~ /\/2024\//) {$year = "2024"; require RunXXIVDefs;}
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
  my $DAQ_DIR = "";
  if (-r "/hlt/cephfs/daq") {
    $DAQ_DIR =  "/hlt/cephfs/daq";
  } elsif (-r "/gpfs01/star/daq") {
    $DAQ_DIR =  " /gpfs01/star/daq";
  } else {
    die "unknow $DAQ_DIR";
  }
  my $runs = $DAQ_DIR . "/" . $year . "/" . $Day . "/" .  $Run;
  my $run2 = "";
  if ($year eq "2020") {
    $runs = $DAQ_DIR . "/" . "2019/" . $Day . "/" .  $Run;
    $run2 = $DAQ_DIR . "/" . "2020/" . $Day . "/" .  $Run;
  } elsif ($year eq "2021") {
    $runs = $DAQ_DIR . "/" . "2020/" . $Day . "/" .  $Run;
    $run2 = $DAQ_DIR . "/" . "2021/" . $Day . "/" .  $Run;
  } elsif ($year eq "2022") {
    $runs = $DAQ_DIR . "/" . "2021/" . $Day . "/" .  $Run;
    $run2 = $DAQ_DIR . "/" . "2022/" . $Day . "/" .  $Run;
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
