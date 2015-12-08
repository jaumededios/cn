int newton(int n, //dim
		   double*x, //proposta I solució
	       int func(double* laX, double* guardaF, double* guardaDF, double* params), //funcio, que ha de tenir, donat x: F, dF encadenats
		   double tolf, double tolx,
		   int maxit,
		   double*params)