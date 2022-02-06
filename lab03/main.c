#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//wartosci z tresci zadania
#define N 2000
#define h 0.02
#define v0 0
#define x0 1
#define w 1

int main(void)
{
  FILE *file = fopen("wynik.dat", "w");

//do odkomentowywania dla poszczególnego zadania
//zad1
 // double beta =0.0, F0 = 0.0, omega = 0.8; 

//zad2
  //double beta =0.4, F0 = 0.0, omega = 0.8;

//zad3
  double beta =0.4, F0 = 0.1, omega = 0.8; 

//dane z tresci zadania
  double a1 = 1.0;
  double a2 = w*w*h*h-2.0-beta*h;
  double a3 = 1+beta*h;

//wektory tworzace macierz trojprzekatniowa
  double *d0 = malloc((N+1)*sizeof(double));
  double *d1 = malloc((N+1)*sizeof(double));
  double *d2 = malloc((N+1)*sizeof(double));
  d0[0] = d0[1] = 1.0;
  d1[1] = -1.0;
  d1[0] = 0.0;
  d2[0]=d2[1] = 0.0;

//macierz wynikowa b
  double *b = malloc((N+1)*sizeof(double));
  b[0] = 1.0;
  b[1] = 0.0;

//pętla wypełniajaca pozostale wartosci stworzonych wektorow
  for(int i=2; i<=N; ++i){
    b[i] = F0*sin(omega*h*(i-1.0))*h*h;  //F0sin(Ωhi)h2
    d0[i] = a3;
    d1[i] = a2;
    d2[i] = a1;
  }
  
//wektory przechowujace przyblizenie obliczane(xn) i poprzednie(xs)
  double *xn = malloc((N+1)*sizeof(double));
  double *xs = malloc((N+1)*sizeof(double));

  for(int i=0; i<=N;++i)
    xs[i] = 1.0;

  double sn, ss;

  int it=0;
  while(it<100000){
    ++it;
    ss=0; sn=0;

    for(int i=0; i<=N; ++i){
      //zabezpieczenie przed wejściem w ujemne indeksy
      if(i==0)
        xn[0] = (1/d0[0])*b[0];
      else if(i==1)
        xn[1]= (1/d0[1])*(b[1]-d1[1]*xs[0]);
      else
        xn[i]= (1/d0[i])*(b[i]-d1[i]*xs[i-1]-d2[i]*xs[i-2]);

      sn += xn[i]*xn[i]; 
      ss += xs[i]*xs[i];
    }


    /*if(fabs(sn-ss)<1e-6)  //warunek wyjścia pętli jeśli dokładnośc jest wystarczająco blisko 0
      break;
    */

    for(int i=0; i<=N; ++i)
      xs[i] = xn[i];

  }

  /*for(int i=0; i<=N;++i)
    printf("%f\t%f\n", i*h, xn[i]);
  */

  for(int i=0; i<=N;++i)
    fprintf(file,"%f\t%f\n", i*h, xn[i] );
  


  fclose(file);

  
  free(d0);
  free(d1);
  free(d2);
  free(b);
  free(xn);
  free(xs);
  

  return 0;
}