#include <stdio.h>
#include "rtbp.h"
#include "zeros.h"

#define MU 1.215058560962404e-2
#define PMAX .5

struct rtbp_prm {
    double c;
    int isgn;
};

double fnc_bis(double x, void *prm){
    struct rtbp_prm *p = (struct rtbp_prm*)prm;
    double u;
    proptraj(MU,1,p->c,p->isgn,x,&u,NULL,PMAX,NULL);
    return u;
}
void fnc_nwt(double x, double *fx, double *dfx, void *prm){
    struct rtbp_prm *p = (struct rtbp_prm*)prm;
    proptraj(MU,1,p->c,p->isgn,x,fx,dfx,PMAX,NULL);
}
int main (int argc, char *argv[]) {
   double c, xa, xb, tolbis, tolfnwt;
   int isgn, maxitnwt, ixrr;
/*
 * Línia de comandes
   double c int isgn double xa double xb double tolbis double tolfnwt int maxitnwt int ixrr
 */
   if (argc<9
         || sscanf(argv[1], "%lf", &c)!=1
         || sscanf(argv[2], "%d", &isgn)!=1
         || sscanf(argv[3], "%lf", &xa)!=1
         || sscanf(argv[4], "%lf", &xb)!=1
         || sscanf(argv[5], "%lf", &tolbis)!=1
         || sscanf(argv[6], "%lf", &tolfnwt)!=1
         || sscanf(argv[7], "%d", &maxitnwt)!=1
         || sscanf(argv[8], "%d", &ixrr)!=1
      ) {
      fprintf(stderr,"%s c isgn xa xb tolbis tolfnwt maxitnwt ixrr \n", argv[0]);
      return -1;
   }  
   struct rtbp_prm prm = { c, isgn }; 

   int it=0;
   double arrel;
   biseccio(xa, xb, tolbis, &arrel, NULL, NULL, fnc_bis, &prm, ixrr);
   arrel = newton(arrel,tolfnwt,0, maxitnwt, fnc_nwt, &prm, ixrr, &it );

   printf("%.16g\n", arrel);

   return 0;
}