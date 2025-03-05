#!/usr/bin/env perl
use File::Basename;
my $mount;
my $disk = "";
my $DISK = "";
if ($#ARGV != 0) {
  print "Usage $0 $mount,  valid options: u, tpc, bnl[D]\n";
  $mount = "gpfs01";
} else {
  $mount = $ARGV[0];
}
if    ($mount eq 'u'  ) { $DISK = "/direct/star+u"; $disk = "/direct/star/u";}
elsif ($mount eq 'tpc') { $DISK = "/direct/gpfs01/star/subsys-tpc"; $disk = "/direct/star/subsys/tpc";}
elsif ($mount eq 'bnl') { $DISK = "/gpfs01/star/i_bnl"; $disk = "/direct/star/institutions/bnl";}
elsif ($mount eq 'gpfs01') { $DISK = "/direct/gpfs01"; $disk = "/direct/gpfs01";}
elsif ($mount eq 'gpfs02') { $DISK = "/direct/gpfs02"; $disk = "/direct/gpfs02";}
elsif ($mount eq 'gpfs03') { $DISK = "/direct/gpfs03"; $disk = "/direct/gpfs03";}
elsif ($mount eq 'gpfs04') { $DISK = "/direct/gpfs04"; $disk = "/direct/gpfs04";}
#elsif ($mount eq 'lustre02') { $DISK = "/sdcc/lustre02"; $disk = "/direct/lustre02";}
elsif ($mount eq 'lustre02') { $DISK = "/sdcc/lustre02/star"; $disk = "/direct/lustre02";}
else {
  die "Non valid option";
}
if (! $DISK) {die "mount DISK is not defined";}
if (! $disk) {die "mount point disk is not defined";}
if (! -r $disk ) {
  my $cmd = "mkdir -p $disk";
  my $flag = system($cmd);
  print "$cmd\n";
  if ( $flag) {print "failed \n";}
  print "\n";
}
my $myVolName = $mount; #File::Basename::basename($mount);
# fusermount -u /direct/gpfs01
#$cmd = "sshfs fisyak\@rftpexp02.rhic.bnl.gov:$DISK $disk";
#$cmd = "sshfs fisyak\@rftpexp01.rhic.bnl.gov:$DISK $disk";
#$cmd = "sshfs fisyak\@sftp.sdcc.bnl.gov:$DISK $disk";
$cmd = "sshfs   fisyak\@sftp.sdcc.bnl.gov:$DISK $disk  -o allow_other ";
print "$cmd";
$flag = system($cmd);
if ( $flag) {print " === failed";}
print "\n";


