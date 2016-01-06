#include <stdio.h>
#include <math.h>
#include "rtbp.h"

#define SQR(x) ((x)*(x))

#define N RTBP_N
#define NV1 RTBP_NV1

#define X x[0]
#define Y x[1]
#define Z x[2]
#define PX x[3]
#define PY x[4]
#define PZ x[5]
#define MU (*((double *)prm))

int rtbp (int n, double t, double x[], double f[], void *prm) {
   double r1x, r2x, r1x2, r2x2, r1ypz, r12, r22, r13, r23, p13, p23,
	  p123, p15, p25, p125, p15x, p25x, p125x,
	  dxpx, dypx, dzpx, dypy,
	  dzpy, dzpz;
   int j;
/* Equacions */
   f[0]=PX+Y; f[1]=PY-X; f[2]=PZ;
   r1x=X-MU; r2x=r1x+1; r1x2=r1x*r1x; r2x2=r2x*r2x;
   r1ypz=Y*Y+Z*Z;
   r12=r1x2+r1ypz; r22=r2x2+r1ypz;
   r13=r12*sqrt(r12); r23=r22*sqrt(r22);
   p13=(1-MU)/r13; p23=MU/r23;
   f[3]=PY-(p13*r1x+p23*r2x);
   p123=p13+p23;
   f[4]=-PX-Y*p123;
   f[5]=-Z*p123;
   if (n>=NV1) {
   /* Variacionals primeres */
      p15=p13/r12; p25=p23/r22;
      p125=p15+p25;
      p15x=p15*r1x; p25x=p25*r2x;
      p125x=p15x+p25x;
      dxpx=-p123+3*(p15x*r1x+p25x*r2x);
      dzpx=dypx=3*p125x;
      dypx*=Y; dzpx*=Z;
      dzpy=dypy=3*Y*p125;
      dypy=Y*dypy-p123;
      dzpy*=Z;
      dzpz=-p123+3*Z*Z*p125;
  /* Derivada resp var dep del camp per der flux resp c.i. (part de var dep) */
      for (j=0; j<N; j++) {
#define VARF(i,j) f[(1+(j))*N+(i)]
#define VAR(i,j) x[(1+(j))*N+(i)]
	 VARF(0,j)= VAR(1,j)+VAR(3,j);
	 VARF(1,j)=-VAR(0,j)+VAR(4,j);
	 VARF(2,j)= VAR(5,j);
	 VARF(3,j)=dxpx*VAR(0,j)+dypx*VAR(1,j)+dzpx*VAR(2,j)
	           +VAR(4,j);
	 VARF(4,j)=dypx*VAR(0,j)+dypy*VAR(1,j)+dzpy*VAR(2,j)
	           -VAR(3,j);
	 VARF(5,j)=dzpx*VAR(0,j)+dzpy*VAR(1,j)+dzpz*VAR(2,j);
#undef VAR
#undef VARF
      }
   }
   return 0;
}

/*
 * Hamiltonià del restringit "compatible" amb rtbphp()
 */

int rtbp_h (double x[], double *h, void *prm) {
   double mu=*((double *)prm), xmmu=X-mu, xmmup1=xmmu+1,
	  r12=SQR(xmmu)+SQR(Y)+SQR(Z),
	  r22=SQR(xmmup1)+SQR(Y)+SQR(Z),
	  r1=sqrt(r12), r2=sqrt(r22), /*r13=r1*r12, r23=r2*r22,*/
	  p1=(1-mu)/r1, p2=mu/r2;
   /*if (dmu!=NULL) *dmu=1/r1-1/r2-xmmu*p1/r12-xmmup1*p2/r22;*/
   *h=.5*(SQR(PX)+SQR(PY)+SQR(PZ))+Y*PX-X*PY-p1-p2;
   return 0;
}

#undef MU

