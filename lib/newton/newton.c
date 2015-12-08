#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../linalg/qrres.c"

/*Entrada: h, X(0), tol, maxit
Fer: ∀k = 0, 1, 2, . . . , maxit
Avaluar F(X(k)
), DF(X(k)
)
Si kF(X(k)
)k2 < tol
STOP(`exit)
Trobar ∆X(k)
resolent el sistema lineal
DF(X(k)
)∆X(k) = F(X(k)
)
Trobar el nou iterat X(k+1) mitjan¸cant
X(k+1) := X(k) − ∆X(k)
STOP(frac`as: no converg`encia)
Sortida: X(k)
(en cas d’`exit)*/

double norm(double* x, int n){
	int i;
	double nrm=0;
	for(i=0; i<n;i++) nrm+=x[i]*x[i];
	return sqrt(nrm);
}

int newton(int n, //dim
		   double*x, //proposta I solució
	       int func(double* laX, double* guardaF, double* guardaDF, double* params), //funcio, que ha de tenir, donat x: F, dF encadenats
		   double tolf, double tolx,
		   int maxit,
		   double*params){
	double ef[n*n+n];
	double dr[n];
	double corr[n];
	int i;
	int nits=0;
	do{
		nits++;
		func(x, ef, ef+n);
		qrres (n, n, ef+n, dr, ef, corr);
		for(i=0; i<n;i++) x[i]-=corr[i];

		if(nits>maxit){
			fprintf(stderr, "Mètode de Newton no ha convergit!\n");
			return -1;
		}
	}
	while(norm(ef,n)>tolf && norm(corr,n)>tolx);
	return 0;
}