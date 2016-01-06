int opham_fdf_experimental (
	int m, double hh, double xx[], double cg[], double f[], double df[],
	double h0rk, double hminrk, double hmaxrk, double tolrk, int npasmxrk,
	int (*ham)(double x[], double *h, void *prm),
	int (*camp)(int n, double t, double x[], double f[], void *prm),
	void *prm){

	int i,j;
	int n=m*2;
	double* nf;

	opham_fdf (
	m, hh, xx, cg, f, NULL,
	h0rk, hminrk, hmaxrk, tolrk, npasmxrk,
	ham,
	camp,
	prm);

	for(i=0; i<n+1;i++){

		xx[i]+=EPSILON;
		nf=df+(2+n)*i;
		opham_fdf(
		m, hh, xx, cg, nf, NULL,
		h0rk, hminrk, hmaxrk, tolrk, npasmxrk,
		ham,
		camp,
		prm);
		xx[i]-=EPSILON;

		for(j=0;j<2+n;j++) nf[j]=(nf[j]-f[j])/EPSILON

	}
return 0;

}

