#! /usr/bin/env perl
use File::Basename;
use Cwd;
# my %dates   = (
# 	       'pp500_2012'       => '20120324.042916',
#  	       'pp500_2017'       => '20170423.040951',
# 	       'isobar_2018'      => '20180318.041820',
# 	       '3p85_fixedTarget' => '20180603.040439',
# 	       '19GeV'            => '20190302.054050',
# 	       '14p5GeV'          => '20190406.043336');
#              'pp500_2017'       => '20170423.040951'
#	       '14p5GeV'          => '20190406.043336'
#	       '7p7GeV_2021_RF'  => '20210303.052529',
#	       '7p7GeV_2021_FF'  => '20210304.034026'
#	      );
#	       'OO_200GeV_20217'  => '20210510.134727',
#	       'FF_OO_200GeV_2021' => '20210522.024326',
#my %dates   = ( 
#	       'FF_OO_200GeV_2021_Ideal' => '20210523.024326'
#	      );
# my %dates = (
# 	     '2021_RF_ideal' => 'y2021,FieldOn,ReverseField',
# 	     '2021_FF_ideal' => 'y2021,FieldOn'
# 	    );
# my %dates = (
# 	     '2021_RF_real' => 'sdt20210510.134727,FieldOn,ReverseField',
# 	     '2021_FF_real' => 'sdt20210510.134727,FieldOn'
# 	    );
# my %dates = (
# 	     '2021_RF_realCF' => 'sdt20210510.134727,FieldOn,ReverseField,ConstantField',
# 	     '2021_FF_realCF' => 'sdt20210510.134727,FieldOn,ConstantField'
# 	    );
#my %dates = (
#	     '2021_RF_realConstBz' => 'sdt20210510.134727,FieldOn,ReverseField,ConstBz',
#	     '2021_FF_realConstBz' => 'sdt20210510.134727,FieldOn,ConstBz'
#	    );
#+--------+---------------------+--------+-----------+---------------------+--------+----------+----------+--------------------+------------+-----------+------------+------------+------------------------+------------+-------------+-------------------+------------+
#| dataID | entryTime           | nodeID | elementID | beginTime           | flavor | schemaID | deactive | fullFieldB         | halfFieldB | zeroField | halfFieldA | fullFieldA | satRate                | factor     | detector    | offset            | ewratio    |
#+--------+---------------------+--------+-----------+---------------------+--------+----------+----------+--------------------+------------+-----------+------------+------------+------------------------+------------+-------------+-------------------+------------+
#|   2471 | 2021-07-25 00:00:00 |     12 |         1 | 2019-02-21 00:00:11 | ofl    |        6 |        0 |   -0.0000000008378 |          0 |         0 |          0 |          0 | 10000000000.0000000000 | 1.00000000 |  8.00000000 |  -607200.00000000 | 1.00000000 |
#|   2469 | 2021-04-22 23:59:00 |     12 |         1 | 2019-04-04 00:00:11 | ofl    |        6 |        0 |       0.0000004769 |          0 |         0 |          0 |          0 | 10000000000.0000000000 | 1.00000000 | 15.00000000 |     2530.00000000 | 1.00000000 |
#|   2453 | 2021-03-11 22:33:37 |     12 |         1 | 2019-06-03 20:00:10 | ofl    |        6 |        0 |                  0 |          0 |         0 |          0 |          0 | 10000000000.0000000000 | 1.00000000 | -1.00000000 |        0.00000000 | 1.00000000 |
#|   2486 | 2021-12-08 19:50:39 |     12 |         1 | 2019-07-10 00:00:20 | ofl    |        6 |        0 |     -0.00000009689 |          0 |         0 |          0 |          0 | 10000000000.0000000000 | 1.00000000 |  6.00000000 |     2138.00000000 | 1.00000000 |
#|   2472 | 2021-10-22 16:25:11 |     12 |         1 | 2020-01-31 01:20:42 | ofl    |        6 |        0 |       0.0000001661 |          0 |         0 |          0 |          0 | 10000000000.0000000000 | 1.00000000 | 12.00000000 |     2960.00000000 | 1.00000000 |
#|   2491 | 2021-12-30 21:57:48 |     12 |         1 | 2021-01-31 00:00:00 | ofl    |        6 |        0 |      0.00000004319 |          0 |         0 |          0 |          0 | 10000000000.0000000000 | 1.00000000 |  8.00000000 |     6148.00000000 | 1.00000000 |
#|   2501 | 2022-02-02 16:53:16 |     12 |         1 | 2021-05-25 11:30:00 | ofl    |        6 |        0 |      -0.0000000205 |          0 |         0 |          0 |          0 | 10000000000.0000000000 | 1.00000000 |  8.00000000 |   -16410.00000000 | 1.00000000 |
#|   2489 | 2021-12-13 22:13:16 |     12 |         1 | 2021-12-07 00:00:00 | ofl    |        6 |        0 |        0.000000065 |          0 |         0 |          0 |          0 | 10000000000.0000000000 | 1.00000000 | 15.00000000 |   -15170.00000000 | 1.00000000 |
#|   2490 | 2021-12-24 20:45:19 |     12 |         1 | 2021-12-07 00:00:01 | ofl    |        6 |        0 |      0.00000008806 |          0 |         0 |          0 |          0 | 10000000000.0000000000 | 1.00000000 | 14.00000000 |    20440.00000000 | 1.00000000 |
#|   2498 | 2022-01-21 22:27:08 |     12 |         1 | 2021-12-07 00:00:02 | ofl    |        6 |        0 |       0.0000004507 |          0 |         0 |          0 |          0 | 10000000000.0000000000 | 1.00000000 |  0.00000000 |  -161100.00000000 | 1.00000000 |
#+--------+---------------------+--------+-----------+---------------------+--------+----------+----------+--------------------+------------+-----------+------------+------------+------------------------+------------+-------------+-------------------+------------+
# my %dates = (
# 	     '19GeV_2019'              => '20190221.000011', 
# 	     '14p5GeV_2019'            => '20190404.000011',
# 	     '7p7GeV_2019_NoDist'      => '20190603.200010',
# 	     'AuAu200_2019'	       => '20190710.000020',
# 	     '9p8GeV_fixedTarget_2020' => '20200131.012042',
# 	     '7p7GeV_2021'     	       => '20210131.000000',
# 	     '17p3GeV_2021'	       => '20210525.113000',
# 	     'pp500_2022'	       => '20211207.000002'
# 	    );
# my %dates = (
#      '7p7GeV_2021'      => '20210209',
#      '7p7GeV_2021DbV'   => '20210209,DbV20210909',
# );
# my %dates = (
#      'OO_200GeV_2021'      => '20210511.033917',
#      'FF_OO_200GeV_2021'   => '20210522.023642'
# my @dates = qw(
# 		2019/FF
# 		2019/RF
# 		2020/RF
# 		2021/FF
# 		2021/RF
# 		2022/FF
# 		2022/RF
# 		2023/FF
# 		2023/RF
# 		2023/ZF
# 		2024/FF
# 		2024/RF
# 		2024/ZF
# 	     );
#my @DistortionSet = qw(Corr4 Corr3 OBmap2D OTwist OClock Opr13 OIFC OShortR OBmap OSectorAlign);
#my @DistortionSet = qw(CorrY OShortR OBmap  OPr40 OIFC OSectorAlign OSpaceZ2 OGridLeakFull);
# QA :INFO  - ==================                 CorrZ    is ON   : Tpc Alignment 2024
# QA :INFO  - ==================                   ExB    is ON   : Activate ExB correction
# QA :INFO  - ==================                 OBmap    is ON   : ExB shape correction
# QA :INFO  - ==================                 OPr40    is ON   : PadRow 40 distortion
# QA :INFO  - ==================                  OIFC    is ON   : Field Cage correction
# QA :INFO  - ==================              OSpaceZ2    is ON   : Space Charge corrections R2
# QA :INFO  - ==================               OShortR    is ON   : Shorted Ring correction
# QA :INFO  - ==================         OGridLeakFull    is ON   : Full Grid Leak correction
# QA :INFO  - ==================              TFGdbOpt    is ON   : ... uses TFG database flavor for alignemnt tables
my @DistortionSet = qw( CorrZ OBmap  OPr40 OIFC OSpaceZ2 OShortR OGridLeakFull      );
#my @DistortionSet = qw(OBMap); 
print "DistortionSet = @DistortionSet\n";
my @dates = qw(	2021/FF 2021/RF 2022/FF 2022/RF 2023/FF 2023/RF);
#foreach $trig  (sort keys %dates) {
my $pwd = cwd();
foreach $trig  (@dates) {
#  my $datetime = $dates{$trig};  print "$trig => $datetime\n";
  my $datetime = $trig;  print "$trig => $datetime\n";
  if (! -d $trig) {`mkdir -p $trig`;}
  chdir $trig;
  foreach my $corr (@DistortionSet) {
#     my $rootfile = $trig . "/" . $corr . "_" . $datetime . ".root";
#     my $log      = $trig . "/" . $corr . "_" . $datetime . ".log";
    my $rootfile = $corr . ".root";
    my $log      = $corr . ".log";
    my $Corr = $corr;
#    if ($Corr eq 'OPr40' and $datetime < 20181101) {$Corr = "Opr13";}
    if (-r $rootfile) {next;}
#    my $cmd = "root.exe -q 'CheckDistortion.C(\"" . $Corr . ",sdt" . $datetime . ",NewTpcAlignment\",\"" . $rootfile . "\",\"" . $trig . "\")' >& " . $log;
#    my $cmd = "root.exe -q 'CheckDistortion.C(\"" . $Corr . ",sdt" . $datetime . ",NewTpcAlignment\",\"" . $rootfile . "\",\"" . $trig . "\")' >& " . $log;
#    my $cmd = "root.exe -q 'CheckDistortion.C(\"" . $Corr . ",Cosmic_" . $datetime . ",Alignment2024,TFGdbOpt\",\"" . $rootfile . "\",\"" . $trig . "\")' >& " . $log;
    my $cmd = "root.exe -q 'lDb.C(1,\"" . $Corr . ",Cosmic_" . $datetime . ",Alignment2024,TFGdbOpt\")' ";
    $cmd .=  "'DistortionCheck.C+(\"" . $Corr . "\")' >& " . $log;
    print "cmd $cmd\n";
    my $flag = system($cmd);
    if ($flag) {print "flag = $flag\n"; die;}
  }
  chdir $pwd;
}
