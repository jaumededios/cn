#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../edos/flux.h"
#include "../linalg/qrres.h"


//Aquest macro et crea una matriu identitat NxN en x
//per a fer-ho tant sols cal notar que els elements
//de la diagonal son aquells en que i/n=i%n
#define IDENITYMATRIX(x,n) for(i=0; i<n*n;i++) (x)[i]= (i/n==i%n?1:0)


//funcionsp per a fer debug vari
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


//Norma d'una matriu, valdria la pena declarar-la com a macro millor?
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

	double* T=xx; //punter a la proposta de periode

	double* x0=xx+1; //punter a la proposta de coordenades

	int n=2*m; //dimensio de (q1..qn, p1..pn)
	int tn=(df==NULL)?n:(n*n+n); //lloc a guardar de memoria, 
								 //n si no hi ha df, n+n**2 si n'hi ha
	double fdf[tn]; //lloc on guardar memoria
	double t0=0; //temps inicial (0 s)
	int iret; //lloc on anar guardant si el programa te problemes

	//inicialitzem x, dx, les condicions inicials per al flux
	memcpy(fdf,x0,n*sizeof(double));
	if(df!=NULL)
		IDENITYMATRIX(fdf+n, n);

	//calcul del flux
	iret=flux(&t0,fdf,&h0rk,*T,hminrk,hmaxrk,tolrk,npasmxrk,tn,camp,prm);

	if(iret){
		fprintf(stderr, "opham_fdf():: Error en el càlcul del flux\n");
		return iret;
	}
	//Passem a construir la F:
	//clcul de l'hamiltonia a la primera posicio (0) de f
	iret=ham(x0,f,prm);
	if(iret){
		fprintf(stderr, "opham_fdf():: Error en el càlcul del hamiltonià\n");
		return iret;
	}
	//li restem la proposta d'hamiltionia al hamiltonia calculat
	f[0]-=hh;

	//calcul del valor de la seccio de poincaré
	f[1]=0;
	for(i=0;i<n;i++) f[1]+=cg[i]*x0[i];
	f[1]+=cg[n];

	//copiem el valor del flux calculat i li restem les coordenades inicials
	memcpy(f+2,fdf, n*sizeof(double));
	for(i=0;i<n;i++) f[i+2]-=x0[i];


	//ara podem passar a consrtruir la diferencial si fa falta

	if(df==NULL) return 0;

	//construim la primera columna!

	//primera fila
	df[0]=0;
	//segona fila
	df[1]=0;

	//la resta de la primera columna es el camp calcualt en T, que
	//el tenim guardat en fdf (el guardem en df+2)
	iret=camp(n,*T,fdf,df+2,prm);
	if(iret){
		fprintf(stderr, "opham_fdf():: Error en el càlcul del camp\n");
		return iret;
	}

	double*df2=df+2+n; // ja m'oblido de la primera columna

	//calculem el camp en x0, el necessitem per a calcular la primera 
	//fila de la diferencial
	double lloc[n];
	iret=camp(n,0,x0,lloc,prm);
	if(iret){
		fprintf(stderr, "opham_fdf():: Error en el càlcul del camp\n");
		return iret;
	}

	// dH/dq=p, dH/dp=-p, a la primera fila
	for(i=m; i<n; i++) df2[i*(2+n)]=+lloc[i-m];	
	for(i=0; i<m; i++) df2[i*(2+n)]=-lloc[i+m];


	//calcul de dG, que son els components de g per que es lineal
	for(i=0; i<n; i++) df2[i*(2+n)+1]=cg[i];

	//copia del dF ja calculat abans

	for(i=0;i<n;i++) memcpy(df2+2+(2+n)*i,fdf+n*(i+1), n*sizeof(double));

	//resem la identitat a dF
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
	double dr[n+2]; //dummy variable, per que la demana el qrres, 
					//on guarda les diagonals que no necessitem
	double corr[n+1];
	int nits=0;
	do{
		nits++;

		iret=opham_fdf (m, hh, xx, cg, f, df,
					   h0rk, hminrk, hmaxrk, tolrk, npasmxrk,
					   ham, camp,  prm);
		if(iret){
		fprintf(stderr, "opham_df():: Error en el calcul"
		                "del camp o la diferencial.\n");
		return -1;
		}
		qrres (n+2, n+1, df, dr, f, corr);

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