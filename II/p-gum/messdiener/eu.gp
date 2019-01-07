set datafile separator ;
set logscale y
# set xr [100:300]
plot 'Na-22.txt' using 2:3 with lines
# 'Natürlich1406.txt' using 2:3 with lines
# plot "< paste Eu-152.txt Natürlich1406.txt" using 2:($3-$6) with lines
# plot "tcs/Cs-50cm.txt" using 2:3 with lines
# replot "tcs/Cs-25cm.txt" using 2:3 with lines
# replot "tcs/Cs-10cm.txt" using 2:3 with lines