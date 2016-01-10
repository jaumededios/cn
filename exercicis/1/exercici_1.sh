#Aquesta linea es per a que no faci el tonto des del
#makefile
dir=$(cd -P -- "$(dirname -- "$0")" && pwd -P)

./rf_pendol 1E-6 1E-1 1E-10 <data.txt>result.txt
gnuplot dibuix_pendol.gp

echo 1 1E-6 100| ./1.4.a_errors 1E-6 1E-1 1E-10 >result.txt
gnuplot dibuix_1.4.b.gp

echo 0 1 1E-6 100| ./harmonic_errors 1E-6 1E-1 1E-10 >result.txt
gnuplot dibuix_harmonic.gp


echo -0.4164607449115608 -0.9089362634520914 0.01438311162938695| \
./lorentz 3 26.5 1 1E-10 7000 >result.txt
gnuplot dibuix_lorentz.gp



#rm result.txt