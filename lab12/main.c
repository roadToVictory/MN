#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double fun(double x){
  return log(pow(x,3.0)+ 3.0*pow(x,2.0) + x + 0.1)*sin(18.0*x);
}

void Simpson(double a, double b, unsigned n){
  double D[n+1][n+1];
  FILE *p = fopen("Simpson.dat", "w");
  for(int w=0; w<=n; w++){
    double N = pow(2,w+1);
    double hw = (b-a)/N;
    double tmp =0.0;
    for(int i=0; i<=N/2-1; i++)
      tmp+= hw/3 * ( fun(a+(2*i)*hw) + 4*fun(a+(2*i+1)*hw) +fun(a+(2*i+2)*hw) );
    D[w][0] = tmp;
  }
  
  for(int w=1; w<=n; w++)
    for(int k=1; k<=w; k++)
      D[w][k]=( pow(4,k)*D[w][k-1] - D[w-1][k-1] )/( pow(4,k)-1 );

  for(int w=0; w<=n;w++)
      fprintf(p, "%.10f\t%.10f\n", D[w][0],D[w][w]);
  fprintf(p, "\n");
  for(int w=0; w<=n;w++){
    for(int k=0;k<=w; k++)
      fprintf(p, "%.10f\t",D[w][k]);
    fprintf(p, "\n");
  }

  fclose(p);
}


void Milne(double a, double b, unsigned n){
  double D[n+1][n+1];
  FILE *p = fopen("Milne.dat", "w");
  for(int w=0; w<=n; w++){
    double N = pow(2,w+2);
    double hw = (b-a)/N;
    double tmp =0.0;

    for(int i=0; i<=N/4-1; i++)
      tmp+= 4*hw/90 * ( 7*fun(a+(4*i)*hw) + 32*fun(a+(4*i+1)*hw) +12*fun(a+(4*i+2)*hw)+ 32*fun(a+(4*i+3)*hw) + 7*fun(a+(4*i+4)*hw) );
    D[w][0] = tmp;
  }
  
  for(int w=1; w<=n; w++)
    for(int k=1; k<=w; k++)
      D[w][k]=( pow(4,k)*D[w][k-1] - D[w-1][k-1] )/( pow(4,k)-1 );

  for(int w=0; w<=n;w++)
      fprintf(p, "%.10f\t%.10f\n", D[w][0], D[w][w]);

  fprintf(p, "\n");
  for(int w=0; w<=n;w++){
    for(int k=0;k<=w; k++)
      fprintf(p, "%.10f\t",D[w][k]);
    fprintf(p, "\n");
  }
  fclose(p);
}

int main() {
  unsigned n = 8;
  double a = 0.0, b=1.0;  //granice całkowania

  Simpson(a,b,n);
  Milne(a,b,n);
  return 0;
}