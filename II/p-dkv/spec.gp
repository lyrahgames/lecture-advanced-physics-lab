set terminal epslatex size 12.5cm,7cm
set output "spec.tex"

set xl 'Offset - Pixelindex'
set yl '255 - Farbwert'

set key box h 1 w 1

plot 'data/data.txt' using (450-$1):(255-$2) with lines title 'Messwerte'