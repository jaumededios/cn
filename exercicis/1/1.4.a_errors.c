#include <stdio.h>
#include "../../lib/edos/rk78.h"
#include "../../lib/fields/ex_1.4.h"


#define N 1

int main (int argc, char *argv[]) {
   double h0, hmin, hmax, tol, t, x[N], h;
   int np, i;
   if (argc!=4
         || sscanf(argv[1],"%lf",&hmin)!=1
         || sscanf(argv[2],"%lf",&hmax)!=1
         || sscanf(argv[3],"%lf",&tol)!=1
      ) {
      fprintf(stderr, "./1.4.a_errors.c hmin hmax tol\n");
      return -1;
   }
   while (scanf("%lf %lf %d",&x[0],&h0,&np)==3) {
      t=1; h=h0;
      printf("%.16G %.16G %.16G %G\n", t, x[0], x[0]-t*t, h);
      for (i=0; i<np; i++) {
         rk78(&t,x,&h,hmin,hmax,tol,N,camp1,NULL);
         printf("%.16G %.16G %.16G %G\n", t, x[0], x[0]-t*t, h);
      }
      printf("\n");
   }
   return 0;
}
