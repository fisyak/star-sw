#! /usr/bin/env perl
use File::Basename;
use Cwd;
use Env;
#use lib $STAR . "/bin";#$ENV{ConstructLocation}; 
use lib "/net/l402/data/fisyak/STAR/packages/.DEV2/bin";#$ENV{ConstructLocation}; 
use RunXXIDefs;
my $debug = 0;
if ($#ARGV >= 0) {
  $debug = $ARGV[0]; print "debug $debug\n" if ($debug);
}
my $pwd = cwd();
#my $Day = "*"; #File::Basename::basename(File::Basename::dirname($pwd));
#my $Run =  File::Basename::basename($pwd);
my $Day =  "*"; # File::Basename::basename($pwd);
print "Day = $Day\n" if ($debug);
my $glob;
if (-r "/hlt/cephfs/daq/2021/") {
#  @globs = ("/hlt/cephfs/daq/2021B/" . $Day . "/*/*.daq", );  print "globs = @globs\n" if ($debug);
  @globs = ("/hlt/cephfs/daq/2021/" . $Day . "/*/*.daq", );  print "globs = @globs\n" if ($debug);
}
if (-r "/hlt/cephfs/daq/2021B/") {
#  @globs = ("/hlt/cephfs/daq/2021B/" . $Day . "/*/*.daq", );  print "globs = @globs\n" if ($debug);
  @globs = ("/hlt/cephfs/daq/2021B/" . $Day . "/*/*.daq", );  print "globs = @globs\n" if ($debug);
}
if (-r "/gpfs01/star/daq/2021/") {
#  @globs = ("/gpfs01/star/daq/2021/*/*/st_physics_adc*.daq");  print "globs = @globs\n" if ($debug);11
  @globs = ("/gpfs01/star/daq/2021/*/*/st_physics*.daq");  print "globs = @globs\n" if ($debug);
}
sub PrintHash($$) {
  my $env = shift; # print "Call PrintHash\n";
  my $prefix = shift;
  foreach my $key (sort keys %$env ) {
    print "{ $key }\t=> {'$env->{$key}->{trig}', \tfield=>`$env->{$key}->{field}',\tfirst=>'$env->{$key}->{first}', \tlast=>'$env->{$key}->{last}', \tbeginTime=>'$env->{$key}->{beginTime}'\n";
  }
}
sub GoodRun($$) {
  my $env = shift;
  my $run = shift;
  print "GoodRun:: run = $run\n" if $debug;
  foreach my $key (sort keys %$env ) {
    print "$pwd, trig = $env->{$key}->{trig}, field = $env->{$key}->{field}; first = $env->{$key}->{first}, last = $env->{$key}->{last}" if ($debug);
    if ($pwd !~ /$env->{$key}->{trig}/)  {print ", rejected by trig $env->{$key}->{trig}\n"  if ($debug); next;}
#    if ($pwd !~ /$env->{$key}->{field}/) {print ", rejected by field\n" if ($debug); next;}
    if ($run < $env->{$key}->{first})     {print ", rejected run $run by first\n" if ($debug); next;}
    if ($run > $env->{$key}->{last})      {print ", rejected run $run by last\n"  if ($debug); next;}
#    print "$pwd, trig = $env->{$key}->{trig}, field = $env->{$key}->{field}; first = $env->{$key}->{first}, last = $env->{$key}->{last} accepted\n";
    print " accepted\n" if ($debug); 
    return $run;
  }
  print " rejected\n" if ($debug);
  return -1;
}
my $def = {@Runs};# print "Runs = @Runs\n";
#PrintHash($def,"Runs") if ($debug);
#die;
my %Runs = ();
foreach my $glob (@globs) {
  my @files = glob $glob; print "files = @files\n" if ($debug);
  foreach my $file (@files) {# print "file = $file\n";
    my $run = File::Basename::basename(File::Basename::dirname($file));
    my $b = File::Basename::basename($file,".daq");
    print "$b\n" if ($debug);
    my $picofile = $b . ".picoDst.root";
    if (-r $picofile) {next;}
    $Runs{$run} .= " " . $file; print "Runs{$run} = $Runs{$run}\n" if ($debug);
  }
}
#____________________________________________________________
my @list = ();
my $Numbers = 0;
foreach my $run (sort keys %Runs) {
  my $r = File::Basename::basename($run);
  if (GoodRun($def,$r) < 0) {next;}
  my @ListAll = split ' ', $Runs{$run};
  foreach my $file (@ListAll) {
    print "run = $run. $file\n" if ($debug);
    my $b = File::Basename::basename($file,".daq");
    print "$b\n" if ($debug);
    my $evfile = $b . ".event.root";
    if (-r $evfile) {next;}
    my $mufile = $b . ".MuDst.root";
    if (-r $mufile) {next;}
    my $pifile = $b . ".picoDst.root";
    if (-r $pifile) {next;}
    my $blafile = $b . ".bla.root";
    if (-r $blafile) {next;}
    push @list, $file;
    $Numbers++;
    print "string:$file\n";
  }
}
#print "Numbers = $Numbers\n";
die "Don't have input files = $Numbers\n" if (! $Numbers);
# my $N = $#list;
# my $NT = 20;
# my $step = int ($N / $NT) + 1; 
# $NT = int ($N / $step);
# print "N = $N, NT = $NT, step = $step\n" if ($debug);
# my $i = 0;
# $Numbers = 0;
# foreach my $file (@list) {
#   $i++;
#   if ($i % $step != 1) {next}
#   print "string:$file\n";
#   $Numbers++;
# }
# if (! $Numbers) {die "Don't have input files\n";}
