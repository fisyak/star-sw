#! /usr/bin/tcsh -f
  rsync -avrz -h  --include="st_cosmic_adc_*.daq"   /direct/gpfs01/star/daq/2019/ .
