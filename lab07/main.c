#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double x_min = -5.0;
double x_max = 5.0;

double fun(double x){
  return exp(-pow(x,2));
}

double czebyszew(int m, int n){
  return 0.5*((x_max - x_min)*cos(M_PI*(2.0*m+1.0)/(2.0*n+2.0)) + (x_max+ x_min)); 
}

double lagrange(double *x, double *y, int n, double x_w){
  double W = 0.0;

  for (int i=0; i<=n; i++){
      double val= 1.0;

    for (int j=0; j<=n; j++) {
      if (j!=i)
        val = val*(x_w- x[j])/(x[i]- x[j]);
      }
      W= W+y[i]*val;
  }
    return W;
}

void licz(int n, FILE* p1, FILE* p2){
  double x[n + 1];
  double y[n + 1];
  double czeb[n + 1];
  double eks[n + 1];
 
  double h=(x_max - x_min) / n;
	double W=0.0;
	
  for(int i=0; i <=n; i++){
    x[i] = y[i] = czeb[i] = eks[i] = 0.0;
    x[i] = x_min + h*i;
    y[i] = fun(x[i]);
    czeb[i] = czebyszew(i, n);
    eks[i] = fun(czeb[i]);
 }

  for(int i=0; i<=1000; i++) {
    double tmp = x_min + 0.01 * i;
    W = lagrange(x, y, n , tmp);
    fprintf(p1, "%g	", tmp);
    fprintf(p1, "%g\n", W);
  }

  for(int i=0; i<=1000; i++) {
    double tmp = x_min + 0.01*i;
    double W = lagrange(czeb, eks, n , tmp);
    fprintf(p2, "%g	", tmp);
    fprintf(p2, "%g\n", W);
  }
}

int main(){

  FILE *p1 = fopen("zad_1.dat", "w");
  FILE *p2 = fopen("zad_2.dat", "w");

  if(p1 && p2){
    for(int n=5; n<=20; n+=5){
      licz(n,p1,p2);
      fprintf(p1,"\n \n");
      fprintf(p2,"\n \n");
    }
  }

  fclose(p1);
  fclose(p2);
 
  return 0;
}