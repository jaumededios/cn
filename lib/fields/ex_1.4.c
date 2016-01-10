/*
Camps de l'exercici 1.4
*/

int camp1 (int n, double t, double *x, double *f, void *prm) {
	f[0]=2*x[0]/t;
	return 0;
}

int harmonic (int n, double t, double *x, double *f, void *prm) {
	f[0]=x[1];
	f[1]=-x[0];
	return 0;
}