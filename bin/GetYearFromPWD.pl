#! /usr/bin/env perl
use File::Basename;
use Cwd;
#use Env;
my $pwd = cwd(); #print "pwd = $pwd\n";
if ($#ARGV >= 0) {
  $pwd = $ARGV[0];
}
my $year  = "";
my $FIELD = "";
if    ($pwd =~ /\/2001\//) {$year = "2001";}
elsif ($pwd =~ /\/2002\//) {$year = "2002";}
elsif ($pwd =~ /\/2003\//) {$year = "2003";}
elsif ($pwd =~ /\/2004\//) {$year = "2004";}
elsif ($pwd =~ /\/2005\//) {$year = "2005";}
elsif ($pwd =~ /\/2006\//) {$year = "2006";}
elsif ($pwd =~ /\/2007\//) {$year = "2007";}
elsif ($pwd =~ /\/2008\//) {$year = "2008";}
elsif ($pwd =~ /\/2009\//) {$year = "2009";}
elsif ($pwd =~ /\/2010\//) {$year = "2010";}
elsif ($pwd =~ /\/2011\//) {$year = "2011";}
elsif ($pwd =~ /\/2012\//) {$year = "2012";}
elsif ($pwd =~ /\/2013\//) {$year = "2013";}
elsif ($pwd =~ /\/2014\//) {$year = "2014";}
elsif ($pwd =~ /\/2015\//) {$year = "2015";}
elsif ($pwd =~ /\/2016\//) {$year = "2016";}
elsif ($pwd =~ /\/2017\//) {$year = "2017";}
elsif ($pwd =~ /\/2018\//) {$year = "2018";}
elsif ($pwd =~ /\/2019\//) {$year = "2019";}
elsif ($pwd =~ /\/2020\//) {$year = "2020";}
elsif ($pwd =~ /\/2021\//) {$year = "2021";}
elsif ($pwd =~ /\/2022\//) {$year = "2022";}
elsif ($pwd =~ /\/2023\//) {$year = "2023";}
elsif ($pwd =~ /\/2024\//) {$year = "2024";}
if    ($pwd =~ /FFI/) {$FIELD = "FFI";}
elsif ($pwd =~ /RFI/) {$FIELD = "RFI";}
elsif ($pwd =~ /FF/) {$FIELD = "FF";}
elsif ($pwd =~ /RF/) {$FIELD = "RF";}
elsif ($pwd =~ /ZF/) {$FIELD = "ZF";}
#$ENV{YEAR} = $year;
#$ENV{FIELD} = $FIELD;
print "$year\n";
