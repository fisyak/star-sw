set plot1V simulation_1V_0000_des 
set plot0V simulation_0V_0000_des 

load_file $plot0V.tdr
create_plot -dataset $plot0V
load_file $plot1V.tdr
create_plot -dataset $plot1V

diff_plots "Plot_$plot1V Plot_$plot0V" -display 
set fo [open "Wfield.txt" "w"]
puts $fo "#x y Ex Ey Potential"
for {set w 0.5} {$w < [expr {3.0*55.0}]} {set w [expr {$w + 0.5}]} {
	incr nx
    for {set h 0.5} {$h < 200.0} {set h [expr {$h + 0.5}]} {
		if {$nx == 1} {
		 incr ny;	
		}
		set pot1 [probe_field -coord "$w $h 0" -field ElectricField-X -plot Plot_Plot_$plot1V-Plot_$plot0V Plot_$plot1V-Plot_$plot0V]
		set pot2 [probe_field -coord "$w $h 0" -field ElectricField-Y -plot Plot_Plot_$plot1V-Plot_$plot0V]
    		set pot3 [probe_field -coord "$w $h 0" -field ElectrostaticPotential -plot Plot_Plot_$plot1V-Plot_$plot0V]
		puts $fo "$w\e-04 $h\e-04 $pot1 $pot2 $pot3"
        }
    }

#puts $fo "nx=$nx, ny =$ny"
close $fo

exit
