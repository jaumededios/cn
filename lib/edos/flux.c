#include <math.h>
#include <stdio.h>
#include "rk78.h"

#define MIN(a,b) (((a)<(b))?(a):(b)) 
#define MAX(a,b) (((a)>(b))?(a):(b)) 

#define EPSILON 1E-14

int flux (
	//Tots els que no estàn marcats amb *** són per al rk78
	double *t,    	//Temps inicial ***
	double x[],   	//Condicions inicials, i posició final
	double *h,    	//Proposta inicial de pas
	double T,     	//Temps final ***
	double pasmin,	//Pas mínim tolerable
	double pasmax,	//Pas màxim tolerable
	double tol,   	//Tolerància màxima acceptable (tol=>dError/dt)
	int npasmx,   	//Màxim nombre de passos acceptats
	int n,        	//Dimensió del sistema
	int (*camp)(int n, double t, double x[], double f[], void *prm),
	void *prm     	//peràmetres per al sistema
){

	double Npasmin, Npasmax;
	double diff;
	double i;

	do{
		i++;
		/*
		La idea és simple:
			-en cada pas posem com a pas màxim el mínim entre
			 el pas màxim donat per l'usuari i el que ens falta
			 per arribar al temps desitjat per l'usuari.

			-Fem el mateix per al pas mínim i per a la proposta 
			 de pas. Així ens assegurem que el rk78 no es passi de
			 llarg. Notem que el més important dels tres és imposar
			 la proposta de pas, ja que la implementació del rk78
			 demana perdó i no permís: [hopper!] fa el pas proposat
			 encara que no quedi dins de la tolerància, i arregla el 
			 següent. 

			-Fem això mentre el temps en el que estem no sigui el 
			 temps al que volem arribar [mòdul errors de cancelacio]
		*/
		diff = fabs(*t - T);
		Npasmin = MIN(diff, pasmin);
		Npasmax = MIN(diff, pasmax);
		*h = MIN(Npasmax, *h);

		rk78(t, x, h, Npasmin, Npasmax, tol, n, camp, prm);
	}

	while(diff > EPSILON  &&  i < npasmx);

	if(i == npasmx){
		fprintf(stderr, 
		        "No ha convergit en %d iteracions, ens rendim.\n", 
		        npasmx);
		return 1;
	}
		
	return 0;
}

#undef MIN
#undef MAX

#undef EPSILON