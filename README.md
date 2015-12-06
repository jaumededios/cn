# Treball final Càlcul numèric
Treball final de la assignatura de càlcul numèric
Jaume de Dios: dec 2015

1) Compilar:

	Per a compilar-ho tot:          "make all"
	Per a recompilar-ho tot:        "make remake"
	Per a netejar de codis objecte: "make clean"

2) Estructura:

	Main folder:

	- 

	- lib/
    	#carpeta amb les llibreries
		- lib/edos
			#fitxers relacionats amb la solucio de edos
			flux.c #té la funció flux, que executa el rk78
		- lib/linalg
			#fitxers relacionats amb àlgebra lineal
		- lib/newton
			#implementació del mètode de Newton en diverses
			 variables utilitzant linalg
