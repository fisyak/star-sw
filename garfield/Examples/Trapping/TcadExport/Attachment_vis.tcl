load_file simulation_des.tdr
create_plot -name plot0 -dataset simulation_des
set fo [open "Attachment.txt" "w"]
set fluence 4e15
puts $fo "#x y ElectronAttachment HoleAttachment"
set conc1 [expr 4*$fluence]
set crossE1 2.0e-14
set crossH1 1e-14

set conc2 [expr 0.6447*$fluence]
set crossE2 5e-15
set crossH2 1e-14

set conc3 [expr 0.5*$fluence]
set crossE3 1e-14
set crossH3 1e-14


set ny 0
set nx 0
for {set w 0.5} {$w < [expr {3.0*55.0}]} {set w [expr {$w + 0.5}]} {
	incr nx
    for {set h 0.5} {$h < 200.0} {set h [expr {$h + 0.5}]} {
		if {$nx == 1} {
		 incr ny;	
		}
		set Trap1 [probe_field -coord "$w $h 0" -field TrapOccupation_0(Do,Le)]
		set Trap2 [probe_field -coord "$w $h 0" -field TrapOccupation_1(Ac,Le)]
    		set Trap3 [probe_field -coord "$w $h 0" -field TrapOccupation_2(Ac,Le)]
		set elife [expr "(1-$Trap1)*$crossE1*$conc1 + ($Trap2)*$crossE2*$conc2+ ($Trap3)*$crossE3*$conc3"]
		set hlife [expr "$Trap1*$crossH1*$conc1 + (1-$Trap2)*$crossH2*$conc2+ (1-$Trap3)*$crossH3*$conc3"]
		puts $fo "$w\e-04 $h\e-04 $elife $hlife" 
        }
    }

#puts $fo "nx=$nx, ny =$ny"
close $fo
exit
