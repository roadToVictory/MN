#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double d_rand(const double min, const double max){
  double r = (double)rand()/RAND_MAX; 
  r = r * (max-min)+min;
  return r;
}

double fun(double x, double y){
  return sin(x)*sin(y) - exp( (-1)*pow((x+M_PI/2),2) - pow((y-M_PI/2),2) );
}

int main(){
  int N=200;
  double xmin = -10.0;
  double xmax = 10.;
  double ymin = -10.0;
  double ymax = 10.0;
  double x0 = 5.0;
  double y0 = 5.0;
  double T=0.0;
  double dx =0.0;
  double dy=0.0;
  double x[N], y[N]; //polozenia
  double fx=0.0;
  double fy = 0.0;
  double fmin = 0.0;

  FILE* w0 = fopen("w0.dat", "w");
  FILE* fT = fopen("T.dat", "w");

  for(int i=0; i<N;i++)
    x[i] = y[i]=5.0; //zerowanie polozen

  for(int it=0; it<=20; it++){
    T = 10./pow(2,it);

    for(int k =0; k<100; k++){
      for(int i=0; i<N;i++){
        dx = d_rand(-1.0, 1.0);
        dy = d_rand(-1.0, 1.0);

//losowanie do skutku poprawnej wartosci niewykraczajacej poza rozwazany obszar
        while( fabs(x[i]+dx) > xmax || fabs(x[i]+dx) < xmin )
          dx = d_rand(-1.0, 1.0);
        while( fabs(y[i]+dy) > ymax || fabs(y[i]+dy) < ymin )
          dy = d_rand(-1.0, 1.0);

        if( fun(x[i]+dx, y[i]+dy) < fun(x[i], y[i]) ){
          x[i] += dx;
          y[i] += dy;
         }
         else if( d_rand(0.0, 1.0) < exp( (-1)* (fun(x[i]+dx, y[i]+dy) - fun(x[i],y[i]))/T  ) ){
           x[i] += dx;
           y[i] += dy;
         }
      }
      fprintf(w0, "%f\n", fun(x[0], y[0]));
    }

    if(it==0 || it==7 || it == 20){
      for(int i=0; i<N; i++)
        fprintf(fT, "%f\t%f\n", x[i], y[i]);
      fprintf(fT, "\n\n");
    }

  }

  /*fx = x[0]; fy = y[0];
  fmin = fun(x[0],y[0]);

  for(int i=1; i<N;i++){
    if( fun(x[i],y[i]) < fmin ){
      fmin = fun(x[i],y[i]);
      fx = x[i];
      fy = y[i];
    }
  }
  printf("min = %f, [%f,%f]\n\n", fmin, fx,fy);
*/
  fclose(w0); fclose(fT);
  return 0;
}