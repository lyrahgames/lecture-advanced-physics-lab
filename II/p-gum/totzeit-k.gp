set terminal epslatex size 12.5cm,7cm
set output "totzeit-k.tex"

set xl 'relative Totzeit$_\skull \ [\unit{\%}]$'
set yl 'Intensität'

set key box left h 1 w 1

set xr [0:65]

set ytics 5

f(x) = a*x + b
fit f(x) 'totzeit-k.txt' using 2:1 via a,b

plot 'totzeit-k.txt' using 2:1 with points pt 13 title '\footnotesize Messwerte', f(x) lc rgb "red" lw 3 title '\footnotesize $f(x) = ax+b$'