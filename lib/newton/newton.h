int newton(int n, //dim
		   double*x; //proposta I solució
	       int func(double* x, double* fx), //funcio, que ha de tenir F, dF encadenats
		   double tolf, double tolx,
		   int maxit)