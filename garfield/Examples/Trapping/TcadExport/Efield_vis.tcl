load_file simulation_des.tdr
create_plot -name plot0 -dataset simulation_des
set fo [open "Efield.txt" "w"]
puts $fo "#x y Ex Ey Potential"
set ny 0
set nx 0
for {set w 0.5} {$w < [expr {3.0*55.0}]} {set w [expr {$w + 0.5}]} {
	incr nx
    for {set h 0.5} {$h < 200.0} {set h [expr {$h + 0.5}]} {
		if {$nx == 1} {
		 incr ny;	
		}
		set Field1 [probe_field -coord "$w $h 0" -field ElectricField-X]
		set Field2 [probe_field -coord "$w $h 0" -field ElectricField-Y]
    		set Pot [probe_field -coord "$w $h 0" -field ElectrostaticPotential]
		puts $fo "$w\e-04 $h\e-04 $Field1 $Field2 $Pot" 
        }
    }

#puts $fo "nx=$nx, ny =$ny"
close $fo
exit
