#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/period/troba_periodiques.h"
#include "lib/fields/rtbp.h"


/*
Programa que troba la continuació d'`orbites peròdiques augmentant
i/o disminuint l'hamiltonià gradualment. 

Primer calculem les condicions de la òrbita en condicions de h molt 
properes, i a partir d'aqui anem avançant a poc a poc utilitzant una
extrapolació lineal a partir dels dos punts anteriors calculats.

El programa funcion practicament igual que el troba periòdiques.c
Amb el programa linker.c es pot fer continue_halo|linker|flux per a

*/
int main(void){
	int iret;
	int i,j;
	double tmp;
	double o_xx[7];

	int m=3;
	double hh=-1.500384;
	double xx[7]={3.051858, 
			      -0.988950,         0, 0.003235, 
			              0, -0.999225, 0};
	double tol=1E-10;

	int maxit=100;
	double cg[7]={0,1,0,
				  0,0,0,
				  0};
	double h0rk=1.1E-6;
	double hminrk=1E-13;
	double hmaxrk=1E-1;
	double tolrk=1E-13; 
	
	int npasmxrk=1E4;

	int (*ham)(double x[], double *h, void *prm)=rtbp_h;
	int (*camp)(int n, double t, double x[], double f[], void *prm)=rtbp;

	double prm[1]={3.040357143E-6};
	opham (
	m, hh, xx, tol, maxit, cg,
	h0rk, hminrk, hmaxrk, tolrk, npasmxrk,
	ham,
	camp,
	prm);
	memcpy(o_xx, xx, 7*sizeof(double));
	double eps=.5E-6;
	for(j=0; j<700;j++){
		hh+=eps;
		if(i==0) hh-=9*eps/10;
		for(i=0; i<7;i++){
			tmp=xx[i];
			xx[i]=2*xx[i]-o_xx[i];
			o_xx[i]=tmp;
		}
		iret=opham (
		m, hh, xx, tol, maxit, cg,
		h0rk, hminrk, hmaxrk, tolrk, npasmxrk,
		ham,
		camp,
		prm);
		if(iret){
			fprintf(stderr,"No s'han pogut continuar els calculs per a j>%d\n",j);
			return -1;
		}
		fprintf(stderr,"Coordenades del resultat:\n");
		fprintf(stderr,"q = (%.10G,\t%.10G,\t%.10G)\n", xx[1],xx[2],xx[3]);
		fprintf(stderr,"p = (%.10G,\t%.10G,\t%.10G)\n", xx[4],xx[5],xx[6]);
		fprintf(stderr,"T =  %G\n", xx[0]);
		fprintf(stderr,"H =  %G\n", hh);
		printf("-----------------------------------\n");
	}
	return 0;

}