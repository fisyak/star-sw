#! /usr/bin/env perl
use File::Basename;
use Cwd;
use Env;
use lib dirname $0; # 
#use lib "/net/l402/data/fisyak/STAR/packages/.DEV2/bin";
use GetYearFromPWD;
if ($#ARGV < 0) {
  print "Usage : $0 year\n";
  exit 0;
}
my $year = $ARGV[0]; print "requested year = $year\n";
if    ($year == "2001") { require RunIDefs; }
elsif ($year == "2002") { require RunIIDefs; }
elsif ($year == "2003") { require RunIIIDefs; }
elsif ($year == "2004") { require RunIVDefs;}
elsif ($year == "2005") { require RunVDefs;}
elsif ($year == "2006") { require RunVIDefs; }
elsif ($year == "2007") { require RunVIIDefs; }
elsif ($year == "2008") { require RunVIIIDefs;}
elsif ($year == "2009") { require RunIXDefs;}
elsif ($year == "2010") { require RunXDefs;}
elsif ($year == "2011") { require RunXIDefs;}
elsif ($year == "2012") { require RunXIIDefs;}
elsif ($year == "2013") { require RunXIIIDefs;}
elsif ($year == "2014") { require RunXIVDefs;}
elsif ($year == "2015") { require RunXVDefs;}
elsif ($year == "2016") { require RunXVIDefs;}
elsif ($year == "2017") { require RunXVIIDefs;}
elsif ($year == "2018") { require RunXVIIIDefs;}
elsif ($year == "2019") { require RunXIXDefs;}
elsif ($year == "2020") { require RunXXDefs;}
elsif ($year == "2021") { require RunXXIDefs;}
elsif ($year == "2022") { require RunXXIIDefs;}
elsif ($year == "2023") { require RunXXIIIDefs;}
elsif ($year == "2024") { require RunXXIVDefs;}
elsif ($year == "2025") { require RunXXVDefs;}
our @Runs;
my $def =  {@Runs}; 
#PrintHash($def,"");
my $nrows = keys %$def; print "def = $def  nrows - $nrows\n";
if ($nrows <= 0) {exit 0;}
my $file = "runConfiguration.y" . $year . ".C";
open (OUT,">$file") or die "Can't open $file";
print OUT '
#ifndef __CINT__
#include "tables/St_runConfiguration_Table.h"
#endif
TDataSet *CreateTable() { 
  // ------  Test whether this table share library was loaded ------
  if (!gROOT->GetClass("St_runConfiguration")) return 0;
';
print OUT "  Int_t nrows = $nrows;\n";
print OUT '
  St_runConfiguration *tableSet = new St_runConfiguration("runConfiguration",nrows);
';
print OUT "
  runConfiguration_st rows[$nrows] = {
";
my $i = 0;
foreach my $key (sort keys %$def ) {
#  print "{ $key }\t=> {'$def->{$key}->{trig}', \tfield=>`$def->{$key}->{field}',\tfirst=>'$def->{$key}->{first}', \tlast=>'$def->{$key}->{last}', \tbeginTime=>'$def->{$key}->{beginTime}'\n";
   $i++;
   my $line = sprintf("    {%5i,%5i,%10i,%10i, \"%s\", \"%s\", \"%s\"},",$i,$nrows,$def->{$key}->{first},  $def->{$key}->{last},$def->{$key}->{trig},$def->{$key}->{field},$def->{$key}->{beginTime});
   print OUT "$line\n";
 };
print OUT '
  };
  for (Int_t i = 0; i < nrows; i++) tableSet->AddAt(&rows[i]);
  return (TDataSet *)tableSet;
}
';
