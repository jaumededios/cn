#include <stdio.h>
int lorentz (int n, double t, double *x, double *f, void *prm){
	double* pointer=(double*)prm;
	double sigma = pointer[1];
	double rho = pointer[2];
	double beta = pointer[3];
	f[0] = sigma*(x[1] - x[0]);
	f[1] = -x[0]*x[2] + rho*x[0] - x[1];
	f[2] = x[0]*x[1] - beta*x[2];
	return 0;
}