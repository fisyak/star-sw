#! /usr/bin/env perl
use File::Basename;
my $now = time();
#print "now = $now\n";
foreach my $bla (glob "*/*/*.bla.root") {
  my ($dev, $ino, $mode, $nlink, $uid, $gid, $rdev, $size, $atime, $mtime, $ctime, $blksize, $blocks ) = stat $bla;
  my $dt = $now - $ctime;
#  my @list = `ls -l $bla`;
#  print "@list";
  if ($dt < $dtmin) {$dtmin = $dt;}
#  print "$bla dt = $dt  dtmin = $dtmin\n" if ($debug);
  my $logf = $bla;
  $logf =~ s/.bla.root/B.log/;
  if (-r $logf) {
#    @list = `ls -l $logf`;
#    print "@list";
    my ($dev, $ino, $mode, $nlink, $uid, $gid, $rdev, $size, $atime, $mtime, $ctime, $blksize, $blocks ) = stat $logf;
    my $dt = $now - $ctime;
#    print "ctime = $ctime, dt = $dt\n";
    if ($dt > 600) {
      print "old $dt $logf exist. rm $bla\n";
      `rm $bla`;
    } else {
      print "up to date $dt  $logf exist. keep $bla\n";
    }
  } else {
    print "$logf does not exist. rm $bla\n";
    `rm $bla`;
  }
}

# 183/20183022/st_physics_20183022_raw_5000005,7741,17740B.log
