#include <math.h>
#include <stdio.h>
#include "rk78.h"
#include "pendol.h"

#define MIN(a,b) (((a)<(b))?(a):(b)) 
#define MAX(a,b) (((a)>(b))?(a):(b)) 

#define N 2
#define EPSILON 1E-14

int flux (
  double *t, double x[], double *h, double T,
  double pasmin, double pasmax, double tol, int npasmx,
  int n,
  int (*camp)(int n, double t, double x[], double f[], void *prm),
  void *prm
){ 
  
  double Npasmin, Npasmax;
  double diff;
  double i;
  do{
    i++;
    diff=fabs(*t-T);
    Npasmin=MIN(diff, pasmin);
    Npasmax=MIN(diff, pasmax);
    *h=MIN(Npasmax, *h);
    rk78(t,x,h,Npasmin, Npasmax,tol,n,camp,prm);
  }

  while(diff>EPSILON && i<npasmx);
  if(i==npasmx){
    fprintf(stderr, "No ha convergit en %d iteracions, ens rendim.\n", npasmx);
    return 1;
  }
    
  return 0;
}

int main (int argc, char *argv[]) {
   double h0, hmin, hmax, tol, t, x[N], h, T;
   if (argc!=4
         || sscanf(argv[1],"%lf",&hmin)!=1
         || sscanf(argv[2],"%lf",&hmax)!=1
         || sscanf(argv[3],"%lf",&tol)!=1
      ) {
      fprintf(stderr, "./rf_pendol hmin hmax tol\n");
      return -1;
   }
   while (scanf("%lf %lf %lf %lf",&x[0],&x[1],&h0, &T)==4) {

      t=0; h=h0;

      flux(&t,x,&h,T,hmin,hmax,tol,4E2,2,pendol,NULL);

      printf("%.16G %.16G %.16G %G\n", t, x[0], x[1], h);

      printf("\n");
   }
   return 0;
}
