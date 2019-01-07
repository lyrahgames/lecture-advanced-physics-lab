# set terminal epslatex size 12.5cm,7cm
# set output "gauss.tex"

set datafile separator ;

set logscale y

set xl '$E \ [\unit{keV}]$'
set yl 'Intensität'

# set xr [505:520]
set xr [480:540]
# set yr [1e-2:1e2]

# set format y "$10^{%T}$"

set key box h 1 w 1

# a = 0.870159
# b = 13.26879
# tn = 16447
tn = 600
# tq = 595
tq = 721

a = 1.469230769
b = 217.153846154


m = 511
k = 0.1
s = 1

f(x) = c*exp(-0.5*((x-m)/s)**2) + k
fit [480:540] f(x) '< paste messdiener/NaI-Det.txt messdiener/Nix.txt' using (a*$1 + b):($3/tq-$6/tn) via s,c,m,k

plot f(x) lt 2 lc rgb "red" lw 4 title '\footnotesize Gauß-Fit',\
	'< paste messdiener/NaI-Det.txt messdiener/Nix.txt' using (a*$1 + b):($3/tq-$6/tn) with points pt 13 ps 1.1 lc rgb "black" title '\footnotesize Messwerte'
	