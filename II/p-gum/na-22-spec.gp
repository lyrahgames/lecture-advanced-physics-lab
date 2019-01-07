# set terminal epslatex size 12.5cm,7cm
# set output "na-22-spec-1.tex"

set datafile separator ;

set logscale y

set xl '$E \ [\unit{keV}]$'
set yl 'Counts'

set xr [0:1800]

set format y "$10^%T$"

set key box h 1 w 1

set label '$\curlywedge\beta^+$' at 630,10000
set arrow from 600,10000 to 530,10000

set label '$\curlywedge\prescript{22}{}{\m{Na}}$' at 980,2950
set arrow from 1200,3000 to 1270,2950

set label '$\curlywedge\prescript{40}{}{\m{K}}$' at 1550,350
set arrow from 1550,350 to 1490,350

set label '$\neg\beta^+$' at 300,60
set arrow from 340,100 to 340,350

set label '$\neg\prescript{22}{}{\m{Na}}$' at 1000,10
set arrow from 1060,20 to 1060,80

plot 'messdiener/Na-22.txt' using 1:3 with lines title 'Messwerte'