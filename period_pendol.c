#include <stdio.h>
#include "lib/period/troba_periodiques.h"
#include "lib/fields/pendol_var.h"

int main(void){


	int m=1;
	double hh=-0.5;
	double xx[3]={4.47,1,1};
	double tol=1E-7;

	int maxit=5;
	double cg[3]={1,0,0};
	double h0rk=1.1E-4;
	double hminrk=1E-6;
	double hmaxrk=1E-2;
	double tolrk=1E-6; 
	
	int npasmxrk=1E-4;

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