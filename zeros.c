#include <stdio.h>
#include <math.h>
#include <float.h>

void biseccio(double a, double b, double tol,
              double *p, double *af, double *bf,
              double (*f)(double, void *), void *prm, int ixrr)
{
    int it = 0;
    double fa = f(a, prm);
    double pm = (a + b) / 2.0;
    double fpm = f(pm, prm);
    if (ixrr > 0 && (b - a) / 2 <= tol)
    {
        fprintf(stderr, "biseccio: No fa falta fer iteracions per cumplir amb la tol\n");
    }
    while ((b - a) / 2 > tol)
    {
        if (fa * fpm <= 0)
        {
            b = pm;
        }
        else
        {
            a = pm;
            fa = fpm;
        }
        pm = (a + b) / 2;
        fpm = f(pm, prm);
        it++;
        if (ixrr > 0)
        {
            fprintf(stderr,
                    "biseccio: Iterat %d: [%.16g, %.16g], p=%.16g, f(p)=%.16g\n", it, a, b, pm, fpm);
        }
    }

    *p = (a + b) / 2.0;

    if (af != NULL)
    {
        *af = a;
    }
    if (bf != NULL)
    {
        *bf = b;
    }
}

double newton(double x0, double tolf, double tolx, int maxit,
              void (*fdf)(double, double *, double *, void *),
              void *prm, int ixrr, int *iret)
{
    double x, fx0, dfx0;
    for (int i = 0; i < maxit; i++)
    {
        fdf(x0, &fx0, &dfx0, prm);
        if (ixrr > 0)
        {
            fprintf(stderr, "Newton: Iterat %d: x = %.16g, f(x) = %.16g\n", i, x0, fx0);
        }
        if (fabs(fx0) <= tolf)
        {
            *iret = i;
            return x0;
        }
        x = x0 - fx0 / dfx0;

        if (fabs(x - x0) <= tolx)
        {
            *iret = i + 1;
            if (ixrr > 0)
            {
                fprintf(stderr, "Newton: Convergència a l'iterat %d: x = %.16g\n", i + 1, x);
            }
            return x;
        }
        x0 = x;
    }
    if (ixrr > 0)
    {
        fprintf(stderr, "Error: No convergència\n");
    }
    *iret = -1;
    return x0;
}
