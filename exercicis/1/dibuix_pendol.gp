set term png
set output "pendol.png"
set xrange [-12.5:12.5]
unset border
set xzeroaxis lt -1
set yzeroaxis lt -1
set xtics axis
set ytics axis
set key off
plot "result.txt" u 2:3  with lines 
