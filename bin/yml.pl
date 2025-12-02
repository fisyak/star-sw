#! /usr/bin/env perl

use strict;
use warnings;
use 5.010;

use YAML qw(LoadFile DumpFile);
use Data::Dumper qw(Dumper);
my $filename= shift or die "Usage: $0 filename\n";
#____________________________________________________________
sub PrintHash($$) {
  my $env = shift; # print "Call PrintHash\n";
  my $prefix = shift;
  foreach my $key ( sort keys %$env ) {
#     if (ref($env->{$key}) eq "HASH") {
#       PrintHash($env->{$key}, $prefix . $key . "}->{");
#     }
#     else {
      if ($env->{$key}) {
#	print "$env->{$key}\n";
	if (ref($env->{$key}) =~ "^ARRAY") {
	  my @array = @{$env->{$key}};
	  print $prefix, $key, "}= \t@array\n";
	} else {
	  print $prefix, $key, "}= \t$env->{$key}\n";
	}
      }
    }
#  }
}
#________________________________________________________________________________

my $data =  LoadFile($filename);

# foreach my $key ( sort keys %$data ) {
#   print "key = $key\n";
#   my $data1 = $data->{$key};
#   foreach my $key1 (sort keys %$data1) {
#     print "\tkey1 = $key1 =>  @{$data1->{$key1}}\n";
#   }
# }
print Dumper $data;
