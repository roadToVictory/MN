#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//#include "four1.c"
#include "nrutil.h"
//#include "nrutil.c"

float randf() {
    return (float)rand()/RAND_MAX - 0.5;
}


double max(float *f, int Nk){
  double fmax;
  fmax = fabs(f[1]);

  for(int i=1; i<=Nk; i++){
    if(fmax<fabs(f[2*i-1]))
      fmax = fabs(f[2*i-1]);
  }
  return fmax;
}


int main() {
    srand(time(NULL));
    FILE *p1 = fopen("k8.dat", "w");
    FILE *p2 = fopen("k10.dat", "w");
    FILE *p3 = fopen("k12.dat", "w");
    FILE* pliki[] = {p1, p2, p3};
    const int k[] = {8, 10, 12};

    for(int a = 0; a < 3; a++){
         int Nk = pow(2, k[a]);
        float T = 1.0;
        float Tmax = 3*T;
        float dt = Tmax/Nk;
        float sigma = T / 20.0;
        float omega = 2*M_PI/T;

        float* f = vector(1, 2*Nk);
        float* f0 = vector(1, 2*Nk);
        float* g1 = vector(1, 2*Nk);
        float* g2 = vector(1, 2*Nk);

        for(int i = 1; i <= Nk; i++) {
            float ti = dt * (i - 1);
            f[2 * i - 1] = f0[2 * i - 1] = sin(omega * ti) +  sin(2 *omega * ti) + sin(3 *omega * ti) + randf();
	    f[2 * i] = f0[2 * i] =  0.0;
	    g1[2 * i - 1] = g2[2 * i - 1] = (1.0 / (sigma * sqrt(2 * M_PI))) * exp(-(ti * ti) / (2 * sigma * sigma));
      g1[2 * i] = g2[2 * i] = 0.0;
	}
	    
	  four1(f,Nk, 1);
    four1(g1, Nk, 1);
    four1(g2, Nk, -1);  //tylko dla g2 odwrotna

        for (int i = 1; i <= Nk; i++) {
	    float a1 = f[2 * i - 1];
	    float b1 = f[2 * i];
	    float a2 = g1[2 * i - 1] + g2[2 * i - 1];
	    float b2 = g1[2 * i] + g2[2 * i];
	    f[2 * i - 1] = a1 * a2 - b1 * b2;
	    f[2 * i] = a1 * b2 + a2 * b1;
	}

	four1(f, Nk, -1); //odwrotna
  float fmax = max(f,Nk);

        for(int i=1; i<=Nk;i++){
      float ti = dt*(i-1);
      fprintf(pliki[a], "%10f %10f\n", ti, f0[2*i-1]);
    }

        fprintf(pliki[a], "\n\n");

        for (int i = 1; i <= Nk; i++) {
	    float ti = dt * (i - 1);
            fprintf(pliki[a], "%10f %10f\n", ti, f[2 * i - 1] * 2.5 / fmax);
        }

        free_vector(f, 1, 2 * Nk);
	free_vector(f0, 1, 2 * Nk);
	free_vector(g1, 1, 2 * Nk);
	free_vector(g2, 1, 2 * Nk);
        
    }
	fclose(p1); fclose(p2); fclose(p3);
    return 0;
}