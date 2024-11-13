#! /usr/bin/env perl
my $def = "Prod.list";
my $debug = 0;
open (In, $def) or die "Can't open $def";
while (my $line = <In>) {
  my @words = split "\'", $line;
  if ($debug) {
    print $line;
    for (my $i = 0; $i <= $#words; $i++) {
      printf("words[%i] = %s\n",$i,$words[$i]);
    }
  }
  my $geom = $words[0]; $geom =~ s/r/y/; $geom =~ s/\.pm://;
  my $trig = $words[3];
  my $field = $words[5];
  my $runf =  $words[7];
  my $datime = $words[13];
  my ($date,$time) = split '\.', $datime; print "$datime => $date, $time\n" if ($debug);
  $time =~ s/^0//g; print "$datime => $date, $time\n" if ($debug);
  printf("  {\"%s\",\t%22i, %6i, \"%s\", \"%s\"}, // 1st run = %s\n",$trig,$date,$time,$geom,$trig,$runf);
}

