#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "../../lib/linalg/qrres.h"

#define MAX(a,b) ((a>b)?a:b)
#define ABS(a) ((a>0)?a:-a)
int main(){
	int m=2000,n,i,j,s;
	double error;
	time_t t0, t1;
	double* matrix = (double*)malloc(m*m*sizeof(double));
	double* b = (double*)malloc(m*sizeof(double));
	double* x = (double*)malloc(m*sizeof(double));
	double*dr = (double*)malloc(m*sizeof(double));
	srand(1234);
	for(s=0;s<m/25;s++){
		n=s*25;
		for(i=0; i<n*n;i++){
			matrix[i]=((double)rand())/RAND_MAX;
		}

		for(i=0; i<n;i++){
			b[i]=0;
			for(j=0; j<n;j++){
				b[i]+=matrix[i+n*j];
			}
		}
		t0=clock();
		qrres (n, n, matrix, dr, b, x);
		t1=clock();
		error=0;

		printf("\n");
		for(i=0;i<n;i++) error=MAX(error, ABS(x[i]-1));

		printf("%d %G %G\n", n, error, ((double)(t1-t0))/CLOCKS_PER_SEC );
	    fprintf(stderr,"%d %G %G\n", n, error, ((double)(t1-t0))/CLOCKS_PER_SEC );
	}
	return 0;
}

#undef MAX
#undef ABS