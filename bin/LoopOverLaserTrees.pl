#! /usr/bin/env perl
use File::Basename;
use Cwd;
my %runs = ();
my $debug = 0;
my $noRuns = 0;
# mv `grep 'Laser Run' tpc*ofl | awk '{print "LaserPlots.*"$6".root"}' | sort -u | xargs | sed -e 's/\w/\|/'` Done/
#my @list = glob "*.laser.root";
#my @list = glob "/star/data9*/reco/AuAu_200_production_2014/*/P15ib_TPC/2014/*/*/*.laser.root";
#my @list = glob "~/work/Tpc/Laser/LANA.2014/021315/*.laser.root";
#my @list = glob "/gpfs01/star/subsys-tpc/fisyak/Tpc/Laser/LANA.2014/laser/*.laser.root";
my @list = glob "./*.laser.root"; print "list = @list\n" if ($debug);
foreach my $file (@list) {
  my $run = File::Basename::basename($file,".laser.root");
  my $dir = File::Basename::dirname($file);
  $run =~ s/st_laser_//;
  $run =~ s/st_physics_//;
  $run =~ s/adc_//;
  my @words = split('_',$run);
  my $r = $words[0];
  print "$file => $r\n" if ($debug);
  my $outfile = "LaserPlots." . $r . ".root";
  if (-r $outfile) {
    print "\t$outfile is Done $outfile \n" if ($debug);
    next;
  }
  my $outfileDone = "./Done/" . $outfile;
  if (-r $outfileDone) {
    print "\t$outfile is Done $outfileDone \n" if ($debug);
    next;
  }
  my $outfileFailed = "./Failed/" . $outfile;
  if (-r $outfileFailed) {
    print "\t$outfile is Failed $outfileFailed \n" if ($debug);
    next;
  }
  if ($runs{$r}) {next;}
  $runs{$r} = $dir;
  print "r = $r = $runs{$r}\n" if ($debug);
  $noRuns++;
}
print "noRuns = $noRuns\n" if ($debug);
#die;
my $Njobs = 0;
my $now = time();
foreach my $key ( sort keys %runs ) {
  print "$key => $runs{$key}\n" if ($debug);
  my @files = glob "st_*" . $key . "*.root"; print "@files\n" if ($debug);
  my $finished = 1;
  my $dtmin = 999999;
  foreach my $file (@files) {
     my ($dev,$ino,$mode,$nlink,$uid,$gid,$dev, $size, $atime, $mtim, $ctime, $blksize,$blocks) = stat($file);
     my $dt = $now - $ctime;
     if ($dt < $dtmin) {$dtmin = $dt;}
     print "$file dt = $dt  dtmin = $dtmin\n" if ($debug);
  }
  if ($dtmin > 600) {
#  if ($dtmin > 0) {
    print "string:$key:$runs{$key}\n";
    $Njobs++;
  }
}
if (! $Njobs) {die "No jobs";}
