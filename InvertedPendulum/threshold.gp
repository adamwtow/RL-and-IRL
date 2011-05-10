#Plot showing the threshold at which LSTDmu starts working
set term epslatex color
set output 'threshold.eps'
set grid
set xlabel 'Number of sub-optimal samples given to LSPI'
set ylabel 'Number of balancing steps for the best policy'
set key width -100
plot 'threshold_lstd.dat' u 1:2 w lines title 'LSTD' ls 1, 'threshold_lstd.dat' u 1:2 w points ls 1 notitle,\
'threshold_mc.dat' u 1:2 w lines title 'MC' ls 2, 'threshold_mc.dat' u 1:2 w points ls 2 notitle