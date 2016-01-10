#include <stdio.h>
#include <stdlib.h>
#include "../../lib/edos/rk78.h"
#include "../../lib/fields/rtbp.h"


#define N 2

int main (int argc, char *argv[]) {
   double x[6], T; 
   int i;

   while (scanf("%lf", &T) ){
      for(i=0; i<6;i++) scanf("%lf", x+i);

      double h=1.1E-6;
      double hmin=1E-13;
      double hmax=1E-1;
      double tol=1E-13; 
      double prm[1]={3.040357143E-6};
      double t=0;
      while (t<T) {
         rk78(&t,x,&h,hmin,hmax,tol,6,rtbp,prm);
         printf("%.16G %.16G %.16G %.16G %.16G %.16G %.16G\n", t, 
            x[0], x[1], x[2],x[3], x[4], x[5]);
      }
      printf("\n");
   }
   return 0;
}
