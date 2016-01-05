#include <math.h>
#include <stdio.h>
#define N 2

/* A la versio anterior hi havia un error:
   a la definicio de VAR i VARP hi havia n en comptes de N
   Aixo produia segmentation faults (violacions de segment)
 */

int pendol (int n, double t, double *x, double *f, void *prm) {
   f[0]=x[1];
   f[1]=-sin(x[0]);
   int i;
   for(i=0;i<6;i++){
      printf("%lf ",x[6] );
   }
   printf("lelkee\n");
   printf("\n");
   if (n==6) {
      f[2]=x[3];
      f[3]=-x[2]*cos(x[0]);
      f[4]=x[5];
      f[5]=-x[4]*cos(x[0]);
   }
   else
      printf("N no es 6!!\n");
   return 0;
}

int hamPendol(double x[], double *h, void *prm){
   *h = 1/2*x[0]*x[0];
   *h+= cos(x[1]);
   return 0;
}

#undef N
