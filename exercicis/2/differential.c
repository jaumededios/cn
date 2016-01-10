#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../lib/edos/flux.h"
#include "../../lib/fields/ex_2.h"


#define N 2

void printMatrix(double * m, int n){
   int i,j;
   for(i=0; i<n;i++){
      for(j=0; j<n;j++)
         printf("%lf, ", m[i+n*j]);
      printf("\b\b\n");
   }
}

/*
Per a estalviar feina, farem que el bruteforcediferential funcioni com el flux :)
*/
void bruteForceDifferential(
   double *t,     //Temps inicial ***
   double x[],    //Condicions inicials, i posició final
   double *h,     //Proposta inicial de pas
   double T,      //Temps final ***
   double pasmin, //Pas mínim tolerable
   double pasmax, //Pas màxim tolerable
   double tol,    //Tolerància màxima acceptable (tol=>dError/dt)
   int npasmx,    //Màxim nombre de passos acceptats
   int n,         //Dimensió del sistema
   int (*camp)(int n, double t, double x[], double f[], void *prm),
   void *prm,
   double f[],
   double epsilon
   ){
   int i,j;
   printf("%d\n", n);
   double xp[n];
   double t0=*t;
   double h0=*h;
   for(i=0; i<n;i++){
      memcpy(xp,x,n*sizeof(double));
      xp[i]-=epsilon;
      memcpy(f+i*n, x, n*sizeof(double));

      f[i*n+i]+=epsilon;
      *t=t0;
      *h=h0;
      flux(t,xp   ,h,T,pasmin,pasmax,tol,npasmx,6,camp,prm);
      *t=t0;
      *h=h0;
      flux(t,f+i*n,h,T,pasmin,pasmax,tol,npasmx,6,camp,prm);

      for(j=0;j<n;j++){
         f[i*n+j]=(f[i*n+j]-xp[j])/(2*epsilon);
      }
   }

   

}


int main (int argc, char *argv[]) {
   double  hmin=1E-10, hmax=1E-2, tol=1E-6, t=0,T=.5, x[20], h=1E-4;
   double pointer[2];
   pointer[0]=0.5;

   x[2]=1;
   x[3]=0;
   x[4]=0;
   x[5]=1;

   h=1E-4;
   t=0;
   x[0]=.1;
   x[1]=.5;


   flux(&t,x,&h,T,hmin,hmax,tol,5E3,6,field,pointer);
   printf("Valor del camp\n");
   printf("%lf %lf\n",x[0],x[1] );
   printf("Diferencial per variacionals\n");

   printMatrix(x+2,2);

   h=1E-4;
   t=0;
   x[0]=.1;
   x[1]=.5;
   bruteForceDifferential(&t,x,&h,T,hmin,hmax,tol,5E3,2,field,pointer,x+2,1E-4);
   printf("Diferencial a força bruta:\n");
   printf("%lf %lf\n",x[0],x[1] );
   printMatrix(x+2,2);

   return 0;
}
