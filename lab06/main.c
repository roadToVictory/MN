#include <stdio.h>
#include <math.h>

#define ITMAX 30
#define N 5

double licz_r(double *a, double *b, int n, double x0){
  b[n] = 0;

  for(int k = n-1; k>=0; k--)
    b[k] = a[k+1] + x0 * b[k+1];
    //bk=ak+1+xjbk+1
  
  return a[0]+x0*b[0];
  //Rj=a0+xjb0
}

int main(){

  double a[N+1];
  a[0]=240.0; a[1]=-196.0; a[2]=-92.0; a[3]=33.0; a[4]=14.0; a[5]=1.0;
  double b[N+1];
  double c[N];
  double Rj, Rj_prim, x0,x1;
  int n;
  double m_zerowe[N];

  FILE *p = fopen("wyniki.dat", "w");
  if(p){
    fprintf(p, "\t\tWyniki\n");
    fprintf(p, "\nL\t it\txit\tRit\tRit'\n\n");
  }

  for(int L=1; L<=N; L++){
    n=N-L+1;
    x0=0;

    for(int it=1; it<=ITMAX; it++){
      Rj = licz_r(a,b,n,x0);
      Rj_prim = licz_r(b,c,n-1,x0);
      x1 = x0-(Rj/Rj_prim);

  if(p)
      fprintf(p,"%d%10d\t%10g\t%10g\t%10g\n", L, it, x1, Rj, Rj_prim);

// numer zera, numer iteracji, wartość przybliżeniaxjorazwartość reszty z dzieleniaRjiR′j.
    
      if(fabs(x1-x0)<1.0e-7) break;

      x0=x1;
    }
    fprintf(p, "\n");
    
    for(int i=0; i<=(n-1); i++)
      a[i] = b[i];
  m_zerowe[L-1] = x1;
  }
  
  fprintf(p, "\n\tMiejsca zerowe: ");
  for(int i=0; i<N;i++)
    fprintf(p, "%g, ",m_zerowe[i]);
  fclose(p);
  return 0;
}