#! /usr/bin/env perl
use File::Basename;
use Cwd;
use Env;
my $pwd = cwd(); #print "pwd = $pwd\n";
my $year  = "";
my $FIELD = "";
if    ($pwd =~ /2019/) {$year = "2019";}
elsif ($pwd =~ /2020/) {$year = "2020";}
elsif ($pwd =~ /2021/) {$year = "2021";}
elsif ($pwd =~ /2022/) {$year = "2022";}
elsif ($pwd =~ /2023/) {$year = "2023";}
elsif ($pwd =~ /2024/) {$year = "2024";}
if    ($pwd =~ /FFI/) {$FIELD = "FFI";}
elsif ($pwd =~ /RFI/) {$FIELD = "RFI";}
elsif ($pwd =~ /FF/) {$FIELD = "FF";}
elsif ($pwd =~ /RF/) {$FIELD = "RF";}
elsif ($pwd =~ /ZF/) {$FIELD = "ZF";}
#$ENV{YEAR} = $year;
#$ENV{FIELD} = $FIELD;
print "$year\n";
