#include <stdio.h>
#include "../../lib/edos/rk78.h"
#include "../../lib/fields/ex_1.4.h"


#define N 2

int main (int argc, char *argv[]) {
   double h0, hmin, hmax, tol, t, x[N], h;
   int np, i;
   if (argc!=4
         || sscanf(argv[1],"%lf",&hmin)!=1
         || sscanf(argv[2],"%lf",&hmax)!=1
         || sscanf(argv[3],"%lf",&tol)!=1
      ) {
      fprintf(stderr, "./harmonic_errors hmin hmax tol\n");
      return -1;
   }
   while (scanf("%lf %lf %lf %d",&x[0],&x[1],&h0,&np)==N+2) {
      t=0; h=h0;

      printf("%.16G %.16G %.16G %G\n", t, x[0], x[1], h);
      for (i=0; i<np; i++) {
         rk78(&t,x,&h,hmin,hmax,tol,N,harmonic,NULL);
         printf("%.16G %.16G %.16G %G\n", t, x[0], x[1], h);
      }
      printf("\n");
   }
   return 0;
}
