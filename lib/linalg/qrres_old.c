#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SGN(x) (x>=0?1:-1)
#define C(i,j) (i+j*m)
#define A(i,j) a[C(i,j)]


//Aquests tres defines ens permeten utilitzar 

#define SUM(expr, init, fin, var) var=0;for(i=init; i<fin;i++)var+=expr;

/*
 * Donada la matriu A m x n, fa la seva descomposició QR i,
 * opcionalment, resolt un sistema sobredeterminat associat.
 *
 * Arguments:
 * - m,n (e) : nombre de files i columnes de la matriu A.
 *   Restricció: m>=n.
 * - a (e/s) : En entrar, a[i+j*m], i=0..m-1, j=0..n-1 han de ser els
 *   coeficients de la matriu a (per files). En sortir:
 *   + Dins a[i+j*m], j>i, hi ha la part de sobre la diagonal de la R
 *     de la descomposició QR.
 *   + Dins a[i+k*m], i=k..m-1, hi ha les coordenades de la
 *     k-èsima reflexió de Householder que s'ha aplicat, k=0..n-1.
 * - dr (s) : en sortir conté la diagonal de R (dr[j] és el coeficient
 *   de la fila j, columna j de R, j=0..n-1).
 * - b (e/s) : En entrar: terme independent del sistema lineal
 *   sobredeterminat que es vol resoldre. En sortir: 
 *         P(n-1) P(n-2) ... P(0) b
 *   on P(k) es la k-èsima reflexió de Householder.
 *   Si b==NULL, no es fa servir.
 * - x (s) : Solució del sistema sobredeterminat Ax=b.
 *   Si b==NULL, no es fa servir.
 */

/*
void printMatrix(int m, int n, double* a){
   int i,j;
   for(i=0; i<m;i++){
      for(j=0;j<n;j++)
         printf("%lf\t", A(i,j));
      printf("\n");
   }
   printf("\n");
   return;
}
*/
void qrres (int m, int n, double *a, double *dr, double *b, double *x) {
   
   double s,c,d; //la c es la alpha i la d la beta
   int k,i, j;
   double U[m]; 
   double before[m*n];
   double beforev[m];
   double prod[m];
   memcpy(before, a, m*m*sizeof(double));

   if (b!=NULL)
      for(i=0;i<m;i++){
         prod[i]=0; 
         beforev[i]=b[i];
         }

   for(k=0; k<n;k++){




   		SUM(A(i,k)*A(i,k) , k , m, s);
   		s=SGN(A(k,k))*sqrt(s); 

   		d=1/(s*s+s*A(k,k)); //NO definida a [Alsedà]?

   		// El U+k és per a simplificar el for de baix
   		// estem copiant m-k blocs de memoria des de 
   		// la posició A_kk en columna a U

   		memcpy(U+k,(a+C(k,k)), (m-k)*sizeof(double) );

   		U[k]+=s; //estem sumant dos coses del mateix signe
   		         //per tant MAI es zero si A es no singular
                  //(resposta a la pregunta de classe)
         //printf("Uk:\n");
         //printMatrix(m-k,1,U+k);
   		dr[k]=-s;
   		for(j=k+1;j<n;j++){

   			SUM(d*U[i]*A(i,j) , k , m, c)
   			//printf("alfa: %lf\n", c);
   			for(i=k; i<m; i++){
   				A(i,j)-=c*U[i];
   			}
   		}
         //printf("got here!\n");
         memcpy((a+C(k,k)), U+k, (m-k)*sizeof(double));


         //printf("diagonal:\n");
         //printMatrix(n,1,dr);

   		if(b==NULL) continue;

   		SUM(d*U[i]*b[i] , k , m, c)
   		for(i=k;i<m;i++)
   			b[i]=b[i]-c*U[i];

	}

	if(b==NULL) return;

	// calcul de la solucio
	
	j=n;
 	while(j --> 0){
 		SUM(x[i]*A(j,i), j+1, n, c );
 		x[j]=(b[j]-c)/dr[j];
	}
   
   printf("m,n:%d,%d\n",m,n );
   for(i=0; i<m;i++) for(j=0;j<n;j++)
      prod[i]+=x[j]*before[i+m*j];

   printf("x:\n");
   for(i=0;i<n;i++)
      printf(" ,%.2lf",x[i]);

   printf("\nb:\n");
   for(i=0;i<m;i++)
      printf(" ,%.2lf", beforev[i]);
   printf("\n");
   printf("Ax:\n");
   for(i=0;i<m;i++)
      printf(" ,%.2lf", prod[i]);
   printf("\n");
   //printMatrix(n,1,x);
	return;
}

#undef SGN
#undef A
#undef C
#undef SUM
