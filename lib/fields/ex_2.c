#include <math.h>
#include <stdio.h>
#define c(a,b) (a+n*b)


int field (int n, double t, double *X, double *f, void *prm) {

	double alpha=0.5;
	double x=X[0];
	double y=X[1];

	double df[4];

	f[0]=-y+alpha*(x-x*x*x-x*y*y);
	f[1]= x+alpha*(y-y*y*y-y*x*x);

	if(n==2)
		return 0;
	

	df[0]=  0 + alpha*(1-3*x*x- y*y ); //df0/dx0
	df[1]=  1 + alpha*(0-  0  -2*x*y);//df1/dx0
	df[2]= -1 + alpha*(0-  0  -2*x*y);//df1/dx0
	df[3]=  0 + alpha*(1-3*y*y- x*x ); //df0/dx0

	f[2]= df[0]*X[2]+df[2]*X[3];
	f[3]= df[1]*X[2]+df[3]*X[3];
	f[4]= df[0]*X[4]+df[2]*X[5];
	f[5]= df[1]*X[4]+df[3]*X[5];
	return 0;
}

#undef c