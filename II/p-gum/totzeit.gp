# set terminal epslatex size 12.5cm,7cm
# set output "totzeit.tex"

set datafile separator ;

set logscale y

set xl 'Kanal'
set yl 'Intensität'

set xr [0:800]
set yr [1e-1:2e3]

set format y "$10^{%T}$"

set key box left h 1 w 1

a = 0.870159
b = 13.26879
# tn = 16447
tn = 600
tq = 500

plot \
	'messdiener/Cs-15cm.txt' using 2:($3/389) with lines lt 1 lw 1 lc rgb "blue" title '$15\unit{cm}$',\
	'messdiener/Cs-5cm.txt' using 2:($3/349) with lines lt 1 lw 1 lc rgb "orange" title '$5\unit{cm}$',\
	'messdiener/Cs-0cm.txt' using 2:($3/261) with lines lt 1 lw 1 lc rgb "black" title '$0\unit{cm}$',\
	'messdiener/Cs-2,5cm.txt' using 2:($3/201) with lines lt 1 lw 1 lc rgb "green" title '$2.5\unit{cm}$',\
	'messdiener/Cs-10cm.txt' using 2:($3/489) with lines lt 1 lw 1 lc rgb "yellow" title '$10\unit{cm}$',\
	'messdiener/Cs-25cm.txt' using 2:($3/466) with lines lt 1 lw 1 lc rgb "magenta" title '$25\unit{cm}$',\
	'messdiener/nur Eu.txt' using 2:($3/331) with lines lt 1 lw 2 lc rgb "orange" title '---'
	# 'messdiener/Cs-50cm.txt' using 1:($3/467) with lines lt 1 lw 2 lc rgb "red" title '$50\unit{cm}$',\
