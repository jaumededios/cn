#include <stdio.h>

#include "lib/period/troba_periodiques.h"
#include "lib/fields/rtbp.h"

int main(void){


	int m=3;
	double hh=-1.500384;
	double xx[7]={3.051858, 
			      -0.988950,         0, 0.003235, 
			              0, -0.999225, 0};
	double tol=1E-6;

	int maxit=30;
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
	return 0;

}