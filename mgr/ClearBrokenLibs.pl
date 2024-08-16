#!/usr/bin/env perl
use File::Basename;
my $ListOfBrokenLibraries = "";
foreach my $logfile (glob "b*.log") {
  open(In, $logfile) or die "Can't open $logfile";
#  print "logfile = $logfile\n";
  while (my $line = <In>) {
#    if ($line !~ /unrecognized relocation (0x2a) in section/) {next;}
    if ($line !~ /unrecognized relocation/ &&
	$line !~ /file not recognized/ &&
	$line !~ /unable to initialize decompress status for section .debug_info/ &&
	$line !~ /access beyond end of merged section/) {next;}
							 #    print "$line\n";
#    print "$line";
    my ($dummy,$lib) = split(":",$line);
#    print "=> $lib\n";
    my $pkg = "";
    if ($lib =~ /\.a\(/) {$pkg = $lib; $pkg =~ s/a\(.*/a/;}
    else {    $pkg = File::Basename::dirname($lib);}
    if ($pkg eq "\.") {
    } else {
#      print "pkg = |$pkg|\n";
#      $ListOfBrokenLibraries .= " |" . $pkg . "|\n";
      $ListOfBrokenLibraries .= " " . $pkg . "\n";
    }
#    last;
  }
  close(In);
}
print "$ListOfBrokenLibraries";

