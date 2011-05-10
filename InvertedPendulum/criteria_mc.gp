#Plot showing the differences between the different criteria in the ANIRL algorithm
set term epslatex color
set output 'criteria_mc.eps'
set grid
set xlabel 'Iterations ($j$)'
set key width -100
plot 'criteria_mc.dat' u 1:2 with lines title '$t$' ls 1, 'criteria_mc.dat' u 1:2 w points ls 1 notitle,\
'criteria_mc.dat' u 1:3 with lines title '$||\hat\mu^{\pi^{(j)}}(s_0)-\hat\mu^{\pi_E}(s_0)||_2$' ls 2, 'criteria_mc.dat' u 1:3 w points ls 2 notitle,\
'criteria_mc.dat' u 1:4 with lines title '$||\mu^{\pi^{(j)}}(s_0)-\mu^{\pi_E}(s_0)||_2$' ls 3, 'criteria_mc.dat' u 1:4 w points ls 3 notitle,\
'criteria_mc.dat' u 1:5 with lines title '$||V^{\pi^{(j)}}(s_0)-V^{\pi_E}(s_0)||_2$' ls 4, 'criteria_mc.dat' u 1:5 w points ls 4 notitle