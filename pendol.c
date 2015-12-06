#include <math.h>

#define Q x[0]
#define P x[1]
#define QD f[0]
#define PD f[1]

int pendol (int n, double t, double *x, double *f, void *prm) {
/*
 * f[0]=x[1];
 * f[1]=-sin(x[0]);
 */
   QD=P;
   PD=-sin(Q);
   return 0;
}

#undef Q
#undef P
#undef QD
#undef PD

