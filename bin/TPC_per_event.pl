#! /usr/bin/env perl
use File::Basename;
use Cwd;
my $LOG = "*B.log";
if ($#ARGV >= 0) {
  $LOG = $ARGV[0];
#  print "LOG = $LOG\n";
}
my @list = glob $LOG; #print "list = @list\n";
if ($#list < 0) {exit 0;}
my $TOT = 0;
my $CPU = 0;
my $AST = 0;
my $NF = 0;
foreach my $log (@list) {
#  print "log = $log\n";
  open (In, $log) or die "Can't open $log";
  while ($line = <In>) {
#st_physics_adc_24151068_raw_1700008_1_10B.log:QA :INFO  - QAInfo:Run is finished at Date/Time 20251024/132244; Total events processed :10 and not completed: 0
#st_physics_adc_24151068_raw_1700008_1_10B.log:QA :INFO  - QAInfo:Chain              StMaker::tpcChain             Ast =1789.72        Cpu =1789.51 
    chomp($line);
    if ($line =~ "Total events processed :") {
#      print "$line\n";
      my $tot = $line;
      $tot =~ s/.*Total events processed ://;
      $tot =~ s/ and not completed.*//;
      $TOT += $tot;
#      print "tot = $tot, TOT = $TOT\n";
    } elsif ($line =~ "QA :INFO  - QAInfo:Chain              StMaker::tpcChain") {
#      print "$line\n";
#      my @temp = split('=',$line);
#      $line =~ m/.*+Ast =(\d+\.\d+).*+Cpu =(\d+\.\d+)/;
      $line =~ s/.*Ast =//;
      $line =~ s/Cpu =//;
#      print "$line\n";
      my ($ast,$cpu) = split(' ',$line);
      $CPU += $cpu;
      $AST += $ast;
#      print "asp = $ast, cpu = $cpu, AST = $AST, CPU = $CPU\n";
      $NF++;
    } 
  }
  close (In);
}
  my $Cpu = $CPU/$TOT;
  my $Ast = $AST/$TOT;
  print "\tCPU/event = $Cpu (sec) and Total/event = $Ast (sec)  \tfor $TOT events in $NF files\n";
