#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define frand() ((double)rand())/(RAND_MAX+1.0)

double fun(double x, double x0, double xmin, double xmax, double o){
  return sin( (14*M_PI*x)/(xmax-xmin) )*(exp( (-1)*(pow((x-x0),2))/(2*pow(o,2)) ) + exp( (-1)*(pow((x+x0),2))/(2*pow(o,2)) )  );
}

int main(){
  FILE* gram = fopen("Gram.dat", "wr" );
  FILE* pkt = fopen("pkt.dat", "wr" );
  FILE* approx = fopen("approx.dat", "wr" );

  int N = 201;
  
  double beta=0;
  double xmin = -4.0;
  double xmax = 4.0;
  double o = (xmax-xmin)/16.0;
  double x0 = 2.0;

  double h = (xmax-xmin)/(N-1.0);

  double phi[52][N];
  double x[N]; 
  //double y[N];
  double szum[N];
  double alfa=0;
  double m[3] = {10,30,50};
  double F,c,s;

  for(int i=0; i<N;i++){
    x[i] = xmin + i*h;
    //y[i] = fun(x[i], x0, xmin, xmax, o);
    szum[i] = fun(x[i], x0, xmin, xmax, o);
    fprintf(pkt, "%f\t%f\n", x[i], szum[i]);
  }

  for(int i=0; i<N;i++){
    phi[0][i] = 0.0;
    phi[1][i] = 1.0;
  }

  for(int i=1; i<51; i++){
    double alfa1=.0, alfa2=.0, beta1=.0, beta2=.0;

    for(int j=0; j<N;j++){
      alfa1 += x[j] * phi[i][j] * phi[i][j];
      beta1 += x[j]*phi[i-1][j]*phi[i][j];
      
      alfa2 += phi[i][j]*phi[i][j];
      beta2 += phi[i-1][j]*phi[i-1][j];
    }

    alfa = alfa1/alfa2;
    beta = beta1/beta2;

    if(i==1) beta=.0;

    printf("%g\t%g\n", alfa, beta);

    for(int k=0;k<N;k++)
      phi[i+1][k] = (x[k]-alfa) *phi[i][k]-beta*phi[i-1][k];
    
  }
//W pliku Gram.dat jest 8 kolumn z danymi

  for(int i=0;i<N;i++){
    fprintf(gram, "%g\t", x[i]);

    for(int j=1; j<8; j++)
      fprintf(gram, "%g\t",phi[j][i]/phi[j][0]);
    
    fprintf(gram, "\n");
  }
  
  for (int i = 0; i < 3; i++) {
		for (int j = 0; j < N; j++) {
			F = .0;
			for (int k = 1; k < m[i]+2; k++) {
				c = .0; s = .0;

				for(int l = 0; l < N ; l++) {
					c += szum[l] * phi[k][l];
					s += phi[k][l] * phi[k][l];
				}
				F += (c/s)* phi[k][j];
			}

			fprintf(approx, "%f\t%f\n", x[j], F);
		}
		fprintf(approx, "\n\n");
	}

  
  fclose(gram); fclose(pkt); fclose(approx);

  return 0;
}