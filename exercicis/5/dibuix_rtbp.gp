set term png
set output "rtbp_orbit_q.png"
set view equal xyz
set ticslevel 0.1

unset key
splot "results.txt" u 2:3:4 w l

set output "rtbp_orbit_p.png"
splot "results.txt" u 5:6:7 w l