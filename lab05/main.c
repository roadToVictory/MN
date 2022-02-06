#include <stdio.h>
#include <math.h>
#include "nrutil.h"
//#include "nrutil.c"
//#include "tred2.c"
//#include "tqli.c"
//#include "pythag.c"


float *multi(float **X, float *vector1, int size){
  float *result = vector(1,size);
  float tmp=0.0;

  for(int i=1; i<=size;i++){
    tmp=0.0;
    for(int j=1;j<=size;j++)
      tmp += X[i][j]*vector1[j];
    result[i] = tmp;
  }

  return result;
}

float multi_scalar(float *vector1, float *vector2, int size){
  float tmp=0.0;
  for(int i=1; i<=size;i++){
    tmp += vector1[i] * vector2[i];
  }

  return tmp;
}



void hotelling(float **A, float lambda, float *x0, int size) {
  for (int i = 1; i <= size; i++) {
    for (int j = 1; j <= size; j++) {
      A[i][j] -= lambda * x0[i] * x0[j];
    }
  } 
}

void vector_cp(float* vector1, float* vector2, int size) {
  for (int i = 1; i <= size; i++) 
    vector2[i] = vector1[i];
}


float vector_norm(float* vector1, int size) {
  float norm = sqrt(fabs(multi_scalar(vector1, vector1, size)));
  for (int i = 1; i <= size; i++)
    vector1[i] /= norm;
}


int main(){
  int n = 7;

  float **A = matrix(1,n,1,n);
  float **X = matrix(1,n,1,n);
  float *d = vector(1,n);
  float *e = vector(1,n);
  float *x0 = vector(1,n);
  float *x = vector(1,n);
  float lambda;


  FILE *p = fopen("wynik.dat","w");
//wypelnienie elementow macierzy A

  for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
      A[i][j] = sqrt(i+j);

//zapisanie macierzy wejsciowej A do pliku
fprintf(p, "\t*****I*****\n");
  for(int i=1; i<=n; i++){
    for(int j=1; j<=n; j++){
      fprintf(p, "%f ", A[i][j]);
    }
    fprintf(p,"\n");
  }

//redukcja do macierzy trójdiagonalnej
  tred2(A,n,d,e);

  
	X = matrix(1,n,1,n);
	for(int i = 1; i <=n; i++){
    	for(int j = 1; j <= n; j++){
    		if(i == j) 
          X[i][j] = 1.0;
    		else X[i][j] = 0.0;
    	}
    }

//diagonalizacja
  tqli(d,e,n,X);

//zapisanie wartosci wlasnych do pliku
fprintf(p, "\n\tWartosci wlasne:\n");
  for(int i=1; i<=n;i++)
    fprintf(p, "%g\n", d[i]);
  fprintf(p,"\n");

///////////////////////REDUKCJA HOTELLINGA///////////////////

//wypelnienie elementow macierzy A

  for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
      A[i][j] = sqrt(i+j);

fprintf(p, "\t*****II HOTELLING*****\n");
for(int i=1; i<=n; i++){
    for(int j=1; j<=n; j++){
      fprintf(p, "%f ", A[i][j]);
    }
    fprintf(p,"\n");
  }


//inicjalizacja wektora startowego x0
  
fprintf(p, "\n\tWartosci wlasne:\n");
  for(int k=1; k<=n; k++){
    for(int i=0; i<=n; i++)
      x0[i] = 1.0;

    for(int i=0; i<=8;i++){  //żądana ilosc iteracji to 8
      x = multi(A,x0,n);
      lambda = multi_scalar(x,x0,n)/multi_scalar(x0,x0,n);
      vector_norm(x,n);
      vector_cp(x,x0,n);
    }
    hotelling(A, lambda, x0,n);
    fprintf(p, "%g\n", lambda);
  }

  fprintf(p,"\n");

      

  fclose(p);

  free_matrix(A,1,n,1,n);

  free_vector(d,1,n);
  free_vector(e,1,n);
  free_vector(x0,1,n);
  free_vector(x,1,n);


  return 0;
}