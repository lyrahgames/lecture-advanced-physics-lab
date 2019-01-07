set terminal epslatex size 12.5cm,7cm
set output "cs-152-spec-back.tex"

set datafile separator ;

set logscale y

set xl '$E \ [\unit{keV}]$'
set yl 'Intensität'

set xr [0:750]
set yr [1e0:1e3]

set format y "$10^{%T}$"

set key box left h 1 w 1

a = 0.870159
b = 13.26879
# tn = 16447
tn = 331
tq = 349

set label '\footnotesize Rückstreupeak' at 130,40
set arrow from 190,30 to 190,15

# plot 'messdiener/Na-22.txt' using 1:3 with lines
plot '< paste messdiener/Cs-5cm.txt messdiener/nur\ Eu.txt' using (a*$1 + b):($3/tq-$6/tn) with lines title 'Messwerte'
# plot '< paste messdiener/Na-22.txt messdiener/Untergrund\ langzeit.txt' using ($1):($3/tq-$6/tn) with lines title 'Messwerte'
