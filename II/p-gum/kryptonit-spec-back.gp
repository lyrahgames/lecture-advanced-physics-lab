# set terminal epslatex size 12.5cm,7cm
# set output "kryptonit-spec-back-var.tex"

set datafile separator ;

set logscale y

set xl '$E \ [\unit{keV}]$'
set yl 'Intensität'

set xr [50:150]
# set xr [0:1800]
set yr [7e-1:5e1]

set format y "$10^{%T}$"

set key box h 1 w 1

a = 0.876354366
b = 14.015296367
# tn = 16447
tn = 16447
tq = 105

# plot 'messdiener/Na-22.txt' using 1:3 with lines
plot '< paste messdiener/Kryptonit.txt messdiener/Untergrund\ langzeit.txt' using (a*$1 + b):($3/tq-$6/tn + 1) with lines title 'Messwerte'
# plot '< paste messdiener/Na-22.txt messdiener/Untergrund\ langzeit.txt' using ($1):($3/tq-$6/tn) with lines title 'Messwerte'
