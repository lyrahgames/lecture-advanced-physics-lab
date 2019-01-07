set terminal epslatex size 12.5cm,7cm
set output "detektoren.tex"

set datafile separator ;

set logscale y

set xl '$E \ [\unit{keV}]$'
set yl 'Intensität'

# set xr [50:150]
set xr [200:1800]
set yr [1e-2:3e2]

set format y "$10^{%T}$"

set key box h 1 w 1

a = 0.876354366
b = 14.015296367

c = 1.469230769
d = 217.153846154

e = 1.550537634
f = 54.150537634

plot 'messdiener/Na-22.txt' using (a*$1 + b):($3/595) with lines lt 1 lc rgb "black" lw 2 title '\footnotesize HP-Ge-Detektor',\
	'messdiener/NaI-Det.txt' using (c*$1 + d):($3/721) with lines lt 1 lc rgb "red" lw 2 title '\footnotesize NaI(Tl)-Detektor',\
	'messdiener/Plastik Na22.txt' using (e*$1 + f):($3/448) with lines lt 1 lc rgb "blue" lw 2 title '\footnotesize Plastik'
