set terminal epslatex size 12.5cm,7cm
set output "abstand.tex"

a = 0.23757
b = 10.8203

k(x) = b/(a*x + b)

n = -15
p = 0

f(x) = m/((x-n)**2) + p
fit [0:30] f(x) 'totzeit-k.txt' using 3:((k($2)*$4)) via m

set key box h 1 w 1

set xl 'Abstand $d \ [\unit{cm}]$'
set yl 'Intensität'

set ytics 100

plot 'totzeit-k.txt' using 3:((k($2)*$4)) with points pt 13 title '\footnotesize Messwerte', f(x) lc rgb "red" lw 3 title '\footnotesize Fit' 