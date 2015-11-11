#include <math.h>

#define VAR(i,j) x[n*(1+(j))+(i)]
#define VARP(i,j) f[n*(1+(j))+(i)]

int pendol (int n, double t, double *x, double *f, void *prm) {
   f[0]=x[1];
   f[1]=-sin(x[0]);
   if (n==6) {
      double df[2][2];
      df[0][0]=0;
      df[0][1]=1;
      df[1][0]=-cos(x[0]);
      df[1][1]=0;
   /* Faig el producte diferencial del camp per VAR */
      for (i=0; i<n; i++) {
         for (j=0; j<n; j++) {
	    VARP(i,j)=0;
	    for (k=0; k<n; k++) VARP(i,j)+=df[i][k]*VAR(k,j);
	 }
      }
   }
   return 0;
}

