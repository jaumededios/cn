set term png
set output "lorentz.png"
set view equal xyz
set ticslevel 0.1

unset key
splot "result.txt" u 2:3:4 w l