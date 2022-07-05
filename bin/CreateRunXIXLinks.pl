#! /usr/bin/env perl
use File::Basename;
use Cwd;
use Env;
use lib "/net/l402/data/fisyak/STAR/packages/.DEV2/bin";#$ENV{ConstructLocation}; 
use RunXIXDefs;
my $pwd = cwd();
#my $day = File::Basename::basename(File::Basename::dirname($pwd));
#my $run =  File::Basename::basename($pwd);
#my @globs = ("/hlt/cephfs/daq/2020/" . $day . "/" . $run . "*/hlt*.daq");#  print "globs = @globs\n";
my $debug = 1;
my $fNo = 0;
# foreach my $glob (@globs) {
#   my @files = glob $glob;
#   foreach my $file (@files) {# print "file = $file\n";
#     my $b = File::Basename::basename($file,".daq");
#     print "$b\n" if ($debug);
#     my $mufile = $b . ".MuDst.root";
#     if (-r $mufile) {next;}
#     print "string:$file\n";
#     $fNo++;
#   }
# }
#____________________________________________________________
#my $TableName = "TpcZCorrectionB";
my $TableName = "TpcLengthCorrectionMDF";
sub PrintHash($$) {
  my $env = shift; # print "Call PrintHash\n";
  my $prefix = shift;
  my $oldTrig = "";
  foreach my $key (sort keys %$env ) {
#    if ($env->{$key}->{trig} !~ /GeV/) {next;}
#    if ($env->{$key}->{trig} =~ /fixed/) {next;}
    if ($env->{$key}->{trig} =~ /Cosmic/) {next;}
    if ($env->{$key}->{trig} eq $oldTrig) {next;}
    $oldTrig = $env->{$key}->{trig};
#    print "{ $key }\t=> {'$env->{$key}->{trig}', \tfield=>`$env->{$key}->{field}',\tfirst=>'$env->{$key}->{first}', \tlast=>'$env->{$key}->{last}', \tbeginTime=>'$env->{$key}->{beginTime}'\n";
#    printf("%-20s %s\n",$env->{$key}->{trig},$env->{$key}->{beginTime});
#    printf("ln -sf TpcSecRowB.%-40s  TpcSecRowB.%s\n",$env->{$key}->{trig} . "_2019.C",$env->{$key}->{beginTime} . ".C");
#   Add a second
    my ($d,$t) = split /\./, $env->{$key}->{beginTime}; # print "$env->{$key}->{beginTime} ->d = $d, t = $t\n";
    my $s = $t%100;
    my $m = $t/100%100;
    my $h = $t/10000%100;# print "t = $t => h = $h, m = $m, s = $s\n";
    $s++;
    if ($s >= 60) {$s = 0; $m++;}
    if ($m >= 60) {$m = 0; $h++;}
#    printf("ln -sf TpcSecRowB.%-40s  TpcSecRowB.%08i.%06i.C\n",$env->{$key}->{trig} . "_2019.C",$d,$t+1);
    printf("ln -sf TpcSecRowB.%-40s  TpcSecRowB.%08i.%02i%02i%02i.C \# %s \n",$env->{$key}->{trig} . "_2019.C",$d,$h,$m,$s, $env->{$key}->{beginTime});
#      my $fileN = $TableName . "." . $env->{$key}->{trig} . ".C";
#      if (-r $fileN) {
#        my $fileT = $TableName . "." .  $env->{$key}->{beginTime} . ".C";
#        if (-r $fileT) {
# 	 print "file $fileT has already existed\n";
#        } else {
# 	 my $cmd = "ls -s $fileN $fileT";
# 	 print "$cmd\n";
# 	 symlink $fileN, $fileT;
#        }
#      } else {
#        print "$fileN does not exist.\n";
#      }
  }
}
my $def = {@Runs};# print "Runs = @Runs\n";
PrintHash($def,"Runs") if ($debug);



