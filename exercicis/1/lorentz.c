#include <stdio.h>
#include <stdlib.h>
#include "../../lib/edos/rk78.h"
#include "../../lib/fields/lorentz.h"


#define N 2

int main (int argc, char *argv[]) {
   double h0=1E-4, hmin=1E-10, hmax=1E-2, tol=1E-10, t, x[N], h;
   int np, i;
   double* ptr= (double*)malloc(4*sizeof(double));

   if (argc!=6
         || sscanf(argv[1],"%lf",ptr+1)!=1
         || sscanf(argv[2],"%lf",ptr+2)!=1
         || sscanf(argv[3],"%lf",ptr+3)!=1
         || sscanf(argv[4],"%lf",&tol)!=1
         || sscanf(argv[5],"%d",&np)!=1
      ) {
      fprintf(stderr, "./lorentz sigma rho beta tol np\n");
      return -1;
   }

   while (scanf("%lf %lf %lf",x,x+1,x+2)==3) {
      t=0; h=h0;

      printf("%.16G %.16G %.16G %G\n", t, x[0], x[1], x[2]);
      for (i=0; i<np; i++) {
         rk78(&t,x,&h,hmin,hmax,tol,3,lorentz,ptr);
         printf("%.16G %.16G %.16G %G\n", t, x[0], x[1], x[2]);
      }
      printf("\n");
   }
   return 0;
}
