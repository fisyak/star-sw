#! /usr/bin/env perl
use File::Basename;
use Cwd;
use File::stat;
use Time::localtime;
use Env;
use strict;
use warnings;
use 5.010;

use YAML qw(LoadFile DumpFile);
use Data::Dumper qw(Dumper);

my $Dir  = cwd();
my $year = "y2020";
my $DST = "picoDst";
if    ($Dir =~ /2025/) { $year = "y2025";}
elsif ($Dir =~ /2024/) { $year = "y2024";}
elsif ($Dir =~ /2023/) { $year = "y2023";}
elsif ($Dir =~ /2022/) { $year = "y2022";}
elsif ($Dir =~ /2021/) { $year = "y2021";}
elsif ($Dir =~ /2020/) { $year = "y2020";}
elsif ($Dir =~ /2019/) { $year = "y2019";} 
elsif ($Dir =~ /2018/) { $year = "y2018";} 
elsif ($Dir =~ /2017/) { $year = "y2017";} 
elsif ($Dir =~ /2016/) { $year = "y2016";} 
elsif ($Dir =~ /2015/) { $year = "y2015";} 
elsif ($Dir =~ /2014/) { $year = "y2014";} 
elsif ($Dir =~ /2013/) { $year = "y2013";} 
elsif ($Dir =~ /2012/) { $year = "y2012";} 
elsif ($Dir =~ /2011/) { $year = "y2011";} 
elsif ($Dir =~ /2010/) { $year = "y2010";} 

my $debug = 0;
my $YamlFile = "../" . File::Basename::basename(File::Basename::dirname($Dir)) . ".yml"; print "YamlFile = $YamlFile\n" if $debug;
my $data = LoadFile($YamlFile) or die "Can't load $YamlFile";
my $step = 1;
my $Njobs = 0;
foreach my $run ( sort keys %$data ) {
  print "run = $run\n" if $debug;
  my $data1 = $data->{$run};
  my $part = 0;
  foreach my $path (sort keys %$data1) {
    print "\tpath = $path => files:  @{$data1->{$path}}\n" if ($debug);
    my @listB = @{$data1->{$path}};
    my $NFiles = $#listB;
    if ($NFiles < 0) {next;}
    if (! -d $run) {`mkdir $run`;}
    if ($NFiles < 20) {
      my $ana = "R" . $run . "_" . $part; 
      #  string:/star/data22/reco/production_3p85GeV_fixedTarget_2021/ReversedFullField/P24iy_calib6/2021/160/22160052:22160052/st_physics_22160052_raw_1500002.root:y2021:picoDst:st_physics_22160052_raw_1500002.picoDst.root
      print "string:$run:$ana:$year:$DST:@listB\n";
      $Njobs++;
      $part++;
    } else {
      my @listC = ();
      my $i = 0;
      foreach my $file (@listB) {
	push @listC, $file;
	$i++;
	if ($i == 20) {
	  my $ana = "R" . $run . "_" . $part; 
	  print "string:$run:$ana:$year:$DST:@listC\n";
	  $Njobs++;
	  $part++;
	  @listC = ();
	  $i = 0;
	}
      }
      if ($#listC >= 0) {
	  my $ana = "R" . $run . "_" . $part; 
	  print "string:$run:$ana:$year:$DST:@listC\n";
	  $Njobs++;
	  $part++;
	  @listC = ();
	  $i = 0;
      }
    }
  }
}
