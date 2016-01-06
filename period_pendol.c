#include <stdio.h>

#include "lib/period/troba_periodiques.h"
#include "lib/fields/var_pendol.h"

int main(void){


	int m=1;
	double hh=-0.8;
	double xx[3]={6.28,0,0.632};
	double tol=1E-6;

	int maxit=30;
	double cg[3]={1,0,0};
	double h0rk=1.1E-6;
	double hminrk=1E-10;
	double hmaxrk=1E-1;
	double tolrk=1E-8; 
	
	int npasmxrk=1E4;

	int (*ham)(double x[], double *h, void *prm)=hamPendol;
	int (*camp)(int n, double t, double x[], double f[], void *prm)=pendol;

	opham (
	m, hh, xx, tol, maxit, cg,
	h0rk, hminrk, hmaxrk, tolrk, npasmxrk,
	ham,
	camp,
	NULL);
	return 0;

}