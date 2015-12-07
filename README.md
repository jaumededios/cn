# Treball final Càlcul numèric
Treball final de la assignatura de càlcul numèric
Jaume de Dios: dec 2015

##1) Compilar:

- Per a compilar-ho tot:          "make all"

- Per a recompilar-ho tot:        "make remake"

- Per a netejar de codis objecte: "make clean"

##2) Estructura:


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
        
		+ flux.c 
        	[_té la funció flux, que executa el rk78 entre temps fixats_]
	- lib/linalg
		[_fitxers relacionats amb àlgebra lineal_]
	- lib/newton
		[_implementació del mètode de Newton en diverses variables utilitzant linalg_] 
