void biseccio (double a, double b, double tol,
    double *p, double *af, double *bf,
    double (*f)(double,void*), void *prm, int ixrr);

double newton (double x0, double tolf, double tolx, int maxit,
    void (*fdf)(double,double*,double*,void*),
    void *prm, int ixrr, int *iret);