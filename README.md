# Treball final Càlcul numèric
Treball final de la assignatura de càlcul numèric
Jaume de Dios: dec 2015

##1. Compilar:

- Per a compilar-ho tot:          "make all"

- Per a recompilar-ho tot:        "make remake"

- Per a netejar de codis objecte: "make clean"

##2. Utilitzar els programes:

EN la carpeta exercicis hi ha els exercicis fets a classe, cadascuna amb un fitxer bash que genera els resultats.

##3. Estructura:


- lib/
    _carpeta amb les llibreries_
    - lib/fields
    	[_els camps d'exemple, per a utilitzar les llibreries_]
        + pendol.c/h [_camp del pèndol_]
        + pendol_var.c/h [_camp del pèndol amb les variacionals_]
        + lorentz.c/h [_camp de l'atractor de lorentz_]
        + prova_var.c/h [_camp de prova donat, amb les seves variacionals_]
        
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