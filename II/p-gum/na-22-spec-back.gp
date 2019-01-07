# set terminal epslatex size 12.5cm,7cm
# set output "na-22-spec-back.tex"

set datafile separator ;

set logscale y

set xl '$E \ [\unit{keV}]$'
set yl 'Intensität'

set xr [0:1800]
set yr [1e-2:1e2]

set format y "$10^{%T}$"

set key box h 1 w 1

a = 0.870159
b = 13.26879
# tn = 16447
tn = 600
tq = 595

set label '\footnotesize Rückstreupeak' at 40,2.6
set arrow from 180,2 to 180,0.8

# plot 'messdiener/Na-22.txt' using 1:3 with lines
plot '< paste messdiener/Na-22.txt messdiener/Nix.txt' using (a*$1 + b):($3/tq-$6/tn) with lines title 'Messwerte'
# plot '< paste messdiener/Na-22.txt messdiener/Untergrund\ langzeit.txt' using ($1):($3/tq-$6/tn) with lines title 'Messwerte'
