# set terminal epslatex size 12.5cm,7cm
# set output "back-1.tex"

set datafile separator ;

set logscale y

set xl '$E \ [\unit{keV}]$'
set yl 'Counts'

set xr [0:1800]

set format y "$10^%T$"

set key box h 1 w 1

# a = 0.909090909
# b = 11.36
a = 0.876354366
b = 14.015296367

plot 'messdiener/Untergrund langzeit.txt' using (a*$1 + b):3 with lines title 'Messwerte'