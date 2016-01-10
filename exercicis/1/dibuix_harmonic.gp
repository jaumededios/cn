set term png
set output "harmonic_errors.png"
plot "result.txt" u 1:($2-sin($1))  with lines , "result.txt" u 1:($3-cos($1))  with lines 