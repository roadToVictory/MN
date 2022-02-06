#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "nrutil.h"


void wyzM(float *xw,float *yw, float *w, int n, float alfa, float beta){
  float **A = matrix(1,n,1,n);
  float **d = matrix(1,n,1,n);
  float h = (xw[n] - xw[1])/(n-1); 
  float lambda = 0.5;
  float mii = 0.5; //1-0.5

  for(int i=1; i<=n; i++){
    for(int j=1; j<=n;j++){
      A[i][j]=.0;
      if(i==j)
        A[i][j]=2.0;
      A[1][1] = A[n][n]=1.0;

      if(i==j-1 || i==j+1)
        A[i][j] = lambda; //lambda jest rowne mii
      A[1][2] = A[n][n-1] = .0;
    }
    if(i!=1 &&i!=n)
      d[i][1]=(6.0/(2.0*h))*((yw[i+1]-yw[i])/h - (yw[i]-yw[i-1])/h);
    d[1][1] = alfa;
    d[n][1] = beta;
  }
  gaussj(A,n,d,1);

  for(int i=1; i<=n;i++)
    w[i] = d[i][1];


  //zwolnnienie pamieci
  free_matrix(A,1,n,1,n);
  free_matrix(d,1,n,1,n);
}


float wyzSx(float *xw,float *yw, float *m, int n, float x){
  float wynik=0.0;
  float h = (xw[n] - xw[1])/(n-1);
  float A; //wzor 9
  float B;  //wzor 10

  for(int i=2; i<=n;i++){
    if(xw[i-1]<=x && x<=xw[i]){
      A = (yw[i]-yw[i-1])/h - (h/6.0)*(m[i]-m[i-1]);
      B = yw[i-1] - m[i-1]*((h*h)/6.0);
      wynik = m[i-1]*pow((xw[i]-x),3.0)/(6.0*h) + m[i]*pow((x-xw[i-1]),3.0)/(6.0*h) + A*(x-xw[i-1])+B;
    }
  }
  return wynik;
}

float f1(float x){
  return 1.0/(1.0+x*x);
}

float f2(float x){
  return cos(2.0*x);
}

int main(){
  FILE *p1 = fopen("f1.dat", "wr");
  //FILE *p2 = fopen("f2.dat", "wr");
  int wezly[4] = {5,8,21,10};

  for(int i=0; i<4; i++){
    float xmin = -5.0;
    float xmax= 5.0;
    int n = wezly[i];
    float h = (xmax-xmin)/(n-1.0);
    float alfa = 0.0;
    float beta = 0.0;
    float delta = 0.01;
    float x=0.0;
    

    float *xw = vector(1,n);
    float *yw = vector(1,n);
    float *m = vector(1,n);
    float roz=0.0;

    for(int j=1; j<=n; j++){
      xw[j] = xmin + (j-1)*h;
      yw[j] = f1(xw[j]);    //dla f1

     //yw[j] = f2(wx[j]);   //dla f2
    }

    wyzM(xw,yw,m,n,alfa,beta);

    x=xmin;

    while(xmax>x){  //wypisywanie wartosci co 0.01
      fprintf(p1,"%f\t%f\n", x, wyzSx(xw,yw,m,n,x));

      //fprintf(p2,"%f\t%f\n", x, wyzSx(xw,yw,m,n,x));  //dla f2

      x+=delta;
    }

    fprintf(p1, "\n\n");
    //fprintf(p2, "\n\n");  //dla f2
  

    if(n==10){
      printf("%d\n",n);
      FILE* pochodne = fopen("pochodne.dat","wr");

      for(int j=1; j<=n;j++){
        roz = (f1(xw[j]-delta) -2*f1(xw[j])+f1(xw[j]+delta))/pow(delta,2.0);

        fprintf(pochodne, "%f\t%f\t%f\n", xw[j], m[j], roz);
      }
      fclose(pochodne);
    }
    free_vector(xw,1,n);
    free_vector(yw,1,n);
    free_vector(m,1,n);
  }
  fclose(p1);
  //fclose(p2);
  return 0;
}