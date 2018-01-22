set datafile separator ","
set title "ECG"
set xlabel "time"
set ylabel "data"
set xrange [0:1000]
set yrange [400:600]
plot "data.csv" using 1 with l
pause 100
