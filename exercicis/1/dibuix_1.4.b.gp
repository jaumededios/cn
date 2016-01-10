set term png
set output "quadratic_errors.png"
plot "result.txt" u 1:($2-$1*$1)  with lines 