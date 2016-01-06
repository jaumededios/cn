#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../edos/flux.h"
#include "../linalg/qrres.h"


#define IDENITYMATRIX(x,n) for(i=0; i<n*n;i++) (x)[i]= (i/n==i%n?1:0)



void printMatrix(int m, int n, double* a){
   int i,j;
   for(i=0; i<m;i++){
      for(j=0;j<n;j++){
         printf("%lf\t", a[i+j*m]);
      }
      printf("\n");
   }
   printf("\n");
   return;
}


void printVector(int n, double*a){
	int i;
	printf("(");
	for(i=0; i<n-1;i++){
		printf("%lf, ", a[i]);
	}
	printf("%lf)\n", a[n-1]);
}

double norm(double* x, int n){
	int i;
	double nrm=0;
	for(i=0; i<n;i++) nrm+=x[i]*x[i];
	return sqrt(nrm);
}

int opham_fdf (
	int m, double hh, double xx[], double cg[], double f[], double df[],
	double h0rk, double hminrk, double hmaxrk, double tolrk, int npasmxrk,
	int (*ham)(double x[], double *h, void *prm),
	int (*camp)(int n, double t, double x[], double f[], void *prm),
	void *prm){

	int i;
	double* T=xx;
	double* x0=xx+1;
	int n=2*m;
	int tn=(df==NULL)?n:(n*n+n);
	double fdf[tn];
	double t0=0;
	int iret;
	memcpy(fdf,x0,n*sizeof(double));
	IDENITYMATRIX(fdf+n, n);


	iret=flux(&t0,fdf,&h0rk,*T,hminrk,hmaxrk,tolrk,npasmxrk,tn,camp,prm);
	if(iret){
		fprintf(stderr, "opham_fdf():: Error en el càlcul del flux\n");
		return iret;
	}
	//Passem a construir la F:
	iret=ham(x0,f,prm);
	if(iret){
		fprintf(stderr, "opham_fdf():: Error en el càlcul del hamiltonià\n");
		return iret;
	}
	f[0]-=hh;

	f[1]=0;
	for(i=0;i<n;i++) f[1]+=cg[i]*x0[i];
	f[1]+=cg[n];

	memcpy(f+2,fdf, n*sizeof(double));
	for(i=0;i<n;i++) f[i+2]-=x0[i];

	//construim la primera columna!
	if(df==NULL) return 0;

	//primera fila
	df[0]=0;
	df[1]=0;
	iret=camp(n,*T,fdf,df+2,prm);
	if(iret){
		fprintf(stderr, "opham_fdf():: Error en el càlcul del camp\n");
		return iret;
	}

	double*df2=df+2+n; // ja m'oblido de la primera columna
	double lloc[n];

	iret=camp(n,0,x0,lloc,prm);
	if(iret){
		fprintf(stderr, "opham_fdf():: Error en el càlcul del camp\n");
		return iret;
	}

	for(i=m; i<n; i++) df2[i*(2+n)]=+lloc[i-m];	
	for(i=0; i<m; i++) df2[i*(2+n)]=-lloc[i+m];


	//calcul de dG
	for(i=0; i<n; i++) df2[i*(2+n)+1]=cg[i];

	//copia del dF ja calculat abans i resta de la Id

	for(i=0;i<n;i++) memcpy(df2+2+(2+n)*i,fdf+n*(i+1), n*sizeof(double));
	for(i=0;i<n;i++) df2[2+(3+n)*i]-=1;


	//memcpy(df,nfdf,(n+2)*(n+1)*sizeof(double));
	return 0;

}








int opham (
int m, double hh, double xx[], double tol, int maxit, double cg[],
double h0rk, double hminrk, double hmaxrk, double tolrk, int npasmxrk,
int (*ham)(double x[], double *h, void *prm),
int (*camp)(int n, double t, double x[], double f[], void *prm),
void *prm){
	int n=2*m;
	int i;
	double iret;
	double f[n+2];
	double df[(n+2)*(n+1)];
	double dr[n+2]; 
	double corr[n+1];
	int nits=0;
	do{
		nits++;
		//printf("========================================\n");
		iret=opham_fdf (m, hh, xx, cg, f, df,
					   h0rk, hminrk, hmaxrk, tolrk, npasmxrk,
					   ham, camp,  prm);
		if(iret){
		fprintf(stderr, "opham_df():: Error en el calcul"
		                "del camp o la diferencial.\n");
		return -1;
		}
		qrres (n+2, n+1, df, dr, f, corr);
/*
		printf("Correccio de (t,x) (xn+1=xn-c):\n");
		printVector(n,corr);

		printf("Valor de x:\n");
		printVector(n,xx+1);
		printf("Periode: %lf\n", xx[0]);

		printf("Norma de f %lf\n", norm(f,n+2));
*/
		for(i=0; i<n+1;i++) xx[i]-=corr[i];



		if(nits>maxit){
			fprintf(stderr, "opham_df():: Mètode de Newton no ha convergit en %d iteracions\n",
				maxit);
			return -1;
		}
	}
	while(norm(f,n+2)>tol && norm(corr,n+1)>tol);
	return 0;
}

#undef IDENITYMATRIX