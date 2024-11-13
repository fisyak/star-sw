#! /usr/bin/env perl
use File::Basename;
use Cwd;
use Env;
my $TableName = "beamSpot";
if ($#ARGV >= 0) {
  $TableName = $ARGV[0];
}
my $fileIn = $STAR . "/StRoot/StChain/GeometryDbAliases.h";
open (In, $fileIn) or die "Can't open $fileIn";
my @tags = ();
while (my $line = <In>) {
  if ($line !~ /1st ru/) {next;}
#  print $line;
  my ($dum,$tag) = split('\"',$line);
#  print "tag = $tag\n";
  my $found = "";
  foreach my $t (@tags) {
    if ($tag =~ $t) {$found = $t; last;}
  }
  if ($found) { 
    print "ln -s $TableName.$found.C $TableName.$tag.C\n";
  } else {
    print "ln -s $TableName.C $TableName.$tag.C\n";
    push @tags, $tag;
  }
}
close (in);
