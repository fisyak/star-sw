#! /usr/bin/env perl
# ~/work/kfp/2021/3p85GeV_fixedTarget_2021_P24iy $ dir -d /star/data*/reco/production_3p85GeV_fixedTarget_2021/ReversedFullField/P24iy/2021/*/* | tee 3p85GeV_fixedTarget_2021_P24iy.list
# awk '{print $9}' 3p85GeV_fixedTarget_2021_P24iy.list | awk -F\/ '{print $9" "$0}' | tee 3p85GeV_fixedTarget_2021_P24iy.sorted 
# List2yml.pl p85GeV_fixedTarget_2021_P24iy.sorted
# dir -d /star/data*/reco/pp200_production_LowLuminosity/ReversedFullField/P24iy/2024/*/* |  awk '{print $9}' | awk -F\/ '{print $10" "$0}' | sort | tee pp200_LowLuminosity_P24iy.list
use File::Basename;
use Cwd;
my $debug = 0;
my $RunSorted = "3p85GeV_fixedTarget_2021_P24iy.sorted";
if ($#ARGV >= 0) {
  $RunSorted = $ARGV[0];
}
my  $dataset = $RunSorted;
$dataset =~ s/list\$//;
my $FileOut = $dataset . ".yml";
open(IN, $RunSorted) or die "Can't open $RunSorted";
open(OUT, ">$FileOut") or die "Can't open $FielOut";
#print OUT "---\n$dataset:\n";
print OUT "---\n";
my $RunOld = -1;
while (my $line = <IN>) {
  print "$line" if $debug;
  chomp($line);
  my @words = split(' ',$line);
  my $Run = $words[0];
  my $path2run = $words[$#words];
  my $run = File::Basename::basename($path2run);
  die if ($run != $Run);
  if ($RunOld != $Run) {
#    print OUT "---\n$run:\n";
    print OUT "$run:\n";
      $RunOld = $Run;
  }
  print "path2rut = $path2run run = $run\n" if $debug;
  my @list = `cd $path2run; ls -1d *picoDst.root`;
  print "list = @list" if $debug;
  if ($#list < 0) {next;}
#  print OUT "  $run $path2run:\n";
  print OUT "   $path2run:\n";
  foreach my $pico (@list) {
    print OUT "     -  $pico";
  }
}
close(IN);
close(OUT);
__END__
---
production_3p85GeV_fixedTarget_2021_P24iy:
  22173033: 
    /star/data58/reco/production_3p85GeV_fixedTarget_2021/ReversedFullField/P24ia/2021/173/22173033/:
      - st_physics_adc_22173033_raw_2000002.picoDst.root 
      - st_physics_adc_22173033_raw_2000002.picoDst.root 
    /star/data84/reco/production_3p85GeV_fixedTarget_2021/ReversedFullField/P24ia/2021/173/22173033/:
      - st_physics_adc_22173033_raw_1500003.picoDst.root 
      - st_physics_adc_22173033_raw_1500003.picoDst.root 
      - st_physics_adc_22173033_raw_1500003.picoDst.root 


