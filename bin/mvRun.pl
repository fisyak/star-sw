#! /usr/bin/env perl
use File::Basename;
my @files = glob "*.*";
foreach my $file (@files) {
  my $f =  File::Basename::basename($file);
  (my $ff = $f) =~ s|st_physics_||;
  $dd =~ s|hlt_||;
  $ff =~ s|st_fmsslow_||;
  $ff =~ s|st_minbias_||;
  $ff =~ s|st_hlt_||;
  $ff =~ s|st_mtd_||;
  $ff =~ s|adc_||;
  my ($run) = split("_",$ff);
  if ($run !~ /^2/) {next;}
  if (! -d $run) {`mkdir $run;`}
  print "mv $f  $run\n";
  `mv ${f} $run`;
}
