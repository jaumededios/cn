# Treball final Càlcul numèric
Treball final de la assignatura de càlcul numèric
Jaume de Dios: dec 2015/jan 2016

## 1. Compilar:

- Per a compilar-ho tot:          "make all"

- Per a recompilar-ho tot:        "make remake"

- Per a netejar de codis objecte: "make clean"

## 2. Utilitzar els programes:

En la carpeta exercicis hi ha els exercicis proposats, fets a partir dels programes que es poden trobar a la llibreria. 
 - L'exercici 1, que te diversos sub-apartats, té un fitxer sh a la seva carpeta que els executa tots de forma adequada
 - L'Exercici 2 tant sols consistia en una comprovació de la diferencial, conté un únic codi executable sense paràmetres
 - L'Exercici 3 consistia en provar el mètode QR en matrius aleatòries, per a veure com evolucionava el temps d'execució i l'error. Cal fer un piping ./qrres_tester>result.txt, i despres utilitzar el plot.gp via gnuplot per a representar-ho.
 - L'exercici 4 conté un primer programa, que troba la òrbita periòdica (period_halo). Aquest programa es pot enviar al programa rtbp_orbit, (./period_halo|./rtbp_orbit>result.txt) per a representar-ho amb gnuplot amb el fitxer dibuix_rtbp.gp
 - L'exercici 5 conté un únic programa que continua les òrbites periòdiques, fent una extrapolació lineal a partir dels dos darrers punts calculats. Fnciona exactament igual que l'anterior (./continue_halo|./../4/rtbp_orbit>result.txt)
## 3. Estructura:


- lib/
    _carpeta amb les llibreries_
    - lib/fields
    	[_els camps d'exemple, per a utilitzar les llibreries_]
        + pendol.c/h [_camp del pèndol_]
        + pendol_var.c/h [_camp del pèndol amb les variacionals_]
        + ex_1.4.c/h [_camps de l'apartat 1.4_]
        + ex_2.c/h [_camps de l'apartat 2_]
        + rtbp.c/h [_camp del problema de tres cossos restringit_]
        + lorentz.c/h [_camp de l'atractor de lorentz_]

        
	- lib/edos
		[_fitxers relacionats amb la solucio de edos_]
        
		+ flux.c/h
        	[_té la funció flux, que executa el rk78 entre temps fixats_]
        + rkf78.c/h
            [_Implementació de Runge-Kutta-Fehlberg amb ordres 7 i 8 _]
            
	- lib/linalg
		[_fitxers relacionats amb àlgebra lineal_]
        
        + qrres.c/h
            [_Resolució de sistemes d'equacions lineals sobredeterminats mitjançant el mètode de Housholder_]

    - lib/newton
        [_implementació del mètode de Newton en diverses variables utilitzant linalg_]

        + newton.c/h
            [_Implementació del mètode de Newton en diverses variables_]

    - lib/period
        [_aplicació del mètode de newton per a trobar òrbites periòdiques en sistemes hamiltonians_]

        + troba_periodiques.c/h
            [_Troba orbites periodiques_]
