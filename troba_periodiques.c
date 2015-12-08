#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "lib/newton/newton.h"
#include "lib/fields/3bp.h"
#include "lib/edos/flux.h"

#define N 4
#define IDENITYMATRIX(x,n) for(i=0; i<n*n;i++) (x)[i]= (i/n==i%n?1:0)

int opham_fdf (
	int m, double hh, double xx[], double cg[], double f[], double df[],
	double h0rk, double hminrk, double hmaxrk, double tolrk, int npasmxrk,
	int (*ham)(double x[], double *h, void *prm),
	int (*camp)(int n, double t, double x[], double f[], void *prm),
	void *prm){

	int i,j;
	double*T=xx;
	double*X0=xx+1;
	int n=2*m;
	int tn=(df==NULL)?n:(n*n+n);
	double fdf[tn]	
	double t0=0;

	memcpy(fdf,x0,n*sizeof(double))
	IDENITYMATRIX(fdf+n, n)
	
	flux(*t0,fdf,h0rk,hminrk,hmaxrk,tolrk,npasmxrk,tn,camp,prm);

	//Passem a construir la F:
	ham(xx,f,prm);
	f[0]-=h;

	f[1]=0;
	for(i=0;i<n;i++) f[1]+=cg[i]*xx[i];
	f[1]+=cg[n];

	memcpy(f+2,fdf, n*sizeof(double))

	//passem a construir la dF

	//construim la primera columna!
	if(df==NULL) return 0;

	//primera fila
	df[0]=0;
	df[1]=0;
	camp(n,T,fdf,df+2,prm)


	double*df=df+2+n; // ja m'oblido de la primera columna

	//calcul de dH
	//epic guarrada: em guardo el camp en un tros de df
	//que esta buit encara, i aixi no inicialitzo memoria
	// despres la moc on m'interessa
	camp(n,T,xx,df,prm);
	
	for(i=0; i<m; i++) df[i*(2+n)]=-df[i+m];
	for(i=m; i<n; i++) df[i*(2+n)]=+df[i-m];

	//calcul de dG
	for(i=0; i<n; i++) df[i*(2+n)+1])=cg[i];

	//copia del dF ja calculat abans i resta de la Id

	for(i=0;i<n;i++) memcpy(df+2+(2+n)*i,fdf+n*(i+1), n*sizeof(double));
	for(i=0;i<n;i++) df[2+(3+n)*i]-=1;

	return 0;

}

double norm(double* x, int n){
	int i;
	double nrm=0;
	for(i=0; i<n;i++) nrm+=x[i]*x[i];
	return sqrt(nrm);
}

int opham (
int m, double hh, double xx[], double tol, double maxit, double cg[],
double h0rk, double hminrk, double hmaxrk, double tolrk, int npasmxrk,
int (*ham)(double x[], double *h, void *prm),
int (*camp)(int n, double t, double x[], double f[], void *prm),
void *prm){
	int n=2*m;
	double f[n+2];
	double df[(n+2)*(n+1)];
	double dr[n+2]; 
	double corr[n+1]
	int nits=0;
	do{
		nits++;
		opham_fdf (m, hh, xx, cg, f, df,
				   h0rk, hminrk, hmaxrk, tolrk, npasmxrk,
				   ham, camp,  prm)
		qrres (n+2, n+1, df, dr, f, corr);

		for(i=0; i<n+1;i++) xx[i]-=corr[i];

		if(nits>maxit){
			fprintf(stderr, "Mètode de Newton no ha convergit!\n");
			return -1;
		}
	}
	while(norm(f,n+2)>tol && norm(corr,n+1)>tol);
	return 0;
}