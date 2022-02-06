#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "nrutil.h"
//#include "nrutil.c"
//#include "gammln.c"
//#include "gauher.c"
//#include "gaulag.c"
//#include "gauleg.c"

float c1(float x){
  return 1.0/( x*sqrt(pow(x,2)-1.0) );
}

float c2(float x){
  return log(x)*exp(-pow(x,2));
}

float c22(float x){
  return log(fabs(x))/2.0;
}

float c3(float x){
  return sin(2.*x)*exp(-3.0*x);
}

float c33(float x){
  return sin(2.*x)*exp(-2.0*x);
}

int main(){
 //dokladne wyniki
  float c1a = M_PI/3;
  float c2a = -0.8700577;
  float c3a = 2./13.;
  float result = 0.0;
  FILE *f = fopen("out.dat", "w");
  float *x; float *w;


  //I//
  float x1=1.0; float x2=2.0;   //granice calkowania

  for(int n=2; n<=100; n++){
    x = vector(1,n);
    w = vector(1,n);
    gauleg(x1,x2,x,w,n);
    result = 0.0;
    for(int i=1; i<=n;i++)
      result+=w[i]*c1(x[i]);
    
    fprintf(f, "%d\t%f\n",n, fabs(result-c1a));

    free_vector(x,1,n);
    free_vector(w,1,n);
  }
  fprintf(f, "\n\n");
  printf("Zad1:\n c1 = %f\t blad = %f\n", result, fabs(result-c1a));


  //II//
  x1=0.0; 
  x2=5.0;
  
  for(int n=2; n<=100; n+=2){ //Hermit
    x = vector(1,n);
    w = vector(1,n);
    gauher(x,w,n);
    result=0.0;
    for(int i=1; i<=n; i++)
      result+=w[i]*c22(x[i]);
    
    fprintf(f, "%d\t%f\n",n, fabs(result-c2a));
    free_vector(x,1,n);
    free_vector(w,1,n);
  }
  fprintf(f, "\n\n");
  printf("Zad2:\n c2 = %f\t blad = %f\n", result, fabs(result-c2a));

  
  for(int n=2; n<=100; n++){ //Legandre
    x = vector(1,n);
    w = vector(1,n);
    gauleg(x1,x2,x,w,n);
    result=0.0;
    for(int i=1; i<=n; i++)
      result+=w[i]*c2(x[i]);
    
    fprintf(f, "%d\t%f\n",n, fabs(result-c2a));
    free_vector(x,1,n);
    free_vector(w,1,n);
  }
  fprintf(f, "\n\n");
  printf("Zad2:\n c2 = %f\t blad = %f\n", result, fabs(result-c2a));

  //III//
  for(int n=2; n<=20;n++){
    x = vector(1,n);
    w = vector(1,n);
    gaulag(x,w,n,0.0);
    result=0.0;

    for(int i=1; i<=n; i++)
      result+=w[i]*c33(x[i]);

    fprintf(f, "%d\t%f\n",n, fabs(result-c3a));

    free_vector(x,1,n);
    free_vector(w,1,n);
  }
printf("Zad3:\n c3 = %f\t blad = %f\n", result, fabs(result-c3a));

  fclose(f);
  
  return 0;
}