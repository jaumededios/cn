#include <math.h>
#include <stdio.h>

#include "lib/edos/flux.h"
#include "lib/fields/pendol_var.h"

#define N 6

int main (int argc, char *argv[]) {
   double h0, hmin, hmax, tol, t, x[6], h, T;
   x[2]=1;
   x[3]=0;
   x[4]=0;
   x[5]=1;
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

      flux(&t,x,&h,T,hmin,hmax,tol,4E2,N,pendol,NULL);

      printf("%.16G %.16G %.16G %G\n", t, x[0], x[1], h);

      printf("\n");
      printf("%.2lf %.2lf\n%.2lf %.2lf\n",x[2],x[4],x[3],x[5] );
   }
   return 0;
}

#undef N