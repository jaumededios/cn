set terminal png
set output 'time.png'
set xlabel "4/3n^3"
set ylabel "T (s)"

set key off

f(x) = m*x 

fit f(x) "result.txt" using (4./3.*($1)**3):($3 ) via m

ti=sprintf("Fit obtingut: %G*x",m);

plot "result.txt" u (4./3.*($1)**3):($3 ) title "Resultats obtinguts", f(x) title ti


set output 'error.png'
set logscale y
set format y "%G";
set xlabel "n"
set ylabel "Error"
plot "result.txt" u 1:($2)