#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "nrutil.h"
//#include "ludcmp.c"
//#include "lubksb.c"

#define N 4 // rozmiar macierzy M: NxN

int main(void)
{
    float **A;
    float **U;
    float **L;
    float **T;  //A^-1
    float **C;  

    int *indx = ivector(1,N);
    float *b = vector(1,N);
    float d;
    FILE *p = fopen("wyniki.txt","w");
    A = matrix(1,N,1,N);
    U = matrix(1,N,1,N);
    L = matrix(1,N,1,N);
    T = matrix(1,N,1,N);
    C = matrix(1,N,1,N);

    for(int i=1; i<=N;i++){
      for(int j=1;j<=N;j++)
        A[i][j] = 1.0/(i+j); // ostatni parametr jest równy 0
    }

     fprintf(p,"Macierz A: \n");
    for(int i=1; i<=N;i++){
      for(int j=1;j<=N;j++){
        fprintf(p,"%.6f\t", A[i][j]);
      }
      fprintf(p, "\n");
    }

    ludcmp(A,N,indx, &d);
    //ludcmp(float A[n][n], int n, int indx[n], float &d)

    for(int i=1; i<=N;i++){
      for(int j=1;j<=N;j++){
        if(i==j){
          U[i][j] = A[i][j];
          L[i][j] = 1.;
        }
        else if(i<j){
          U[i][j] = A[i][j];
          L[i][j] = 0;
        }
        else{
          U[i][j] = 0;
          L[i][j] = A[i][j];
        }
      }
    }

    fprintf(p,"Macierz L: \n");
    for(int i=1; i<=N;i++){
      for(int j=1;j<=N;j++){
        fprintf(p,"%f\t", L[i][j]);
      }
      fprintf(p, "\n");
    } 

    fprintf(p,"Macierz U: \n");
    for(int i=1; i<=N;i++){
      for(int j=1;j<=N;j++){
        fprintf(p,"%f\t", U[i][j]);
      }
      fprintf(p, "\n");
    }

    

    float wyzn=1.0;
    for(int i=1; i<=N;i++)
      wyzn*=A[i][i];
    fprintf(p, "detA = %g\n",-wyzn);

    for(int i=1; i<=N;i++){
      for(int j=1;j<=N;j++){
        b[j] = 0.0;
      }
      b[i] = 1.0;
      lubksb(A,N, indx, b);

      for(int k=1; k<=N; k++)
        T[k][i] = b[k];
      // lubksb(float **A, int N, int *indx, float b[])
    }
    
    fprintf(p,"Macierz odwrotna A^-1: \n");
    for(int i=1; i<=N;i++){
      for(int j=1;j<=N;j++){
        fprintf(p,"%f\t", T[i][j]);
      }
      fprintf(p, "\n");
    }

    for(int i=1; i<=N;i++){
      for(int j=1;j<=N;j++)
        A[i][j] = 1.0/(i+j); // ostatni parametr jest równy 0
    }
  
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            C[i][j]=0.;
            for(int k=1;k<=N;k++)
                C[i][j]+=A[i][k]*T[k][j];
        }
    }

    fprintf(p,"Macierz  A*A^-1: \n");
    for(int i=1; i<=N;i++){
      for(int j=1;j<=N;j++){
        fprintf(p,"%f\t", C[i][j]);
      }
      fprintf(p, "\n");
    }

    float maxA=fabs(A[1][1]); //macierz A
    float maxT=fabs(T[1][1]); // macierz A^-1
    for(int i=1;i<=N;i++){
      for(int j=1;j<=N;j++){
        if(fabs(A[i][j])>maxA)
          maxA=fabs(A[i][j]);
        if(fabs(T[i][j])>maxT)
           maxT=fabs(T[i][j]);
        }
    }
    float cond = maxA*maxT;
    fprintf(p, "\nA=%f, A^-1 = %f, n=%f", maxA, maxT, cond);

    fclose(p);

  free_vector(b, 1, N);
  free_ivector(indx, 1, N);
  free_matrix(A, 1, N, 1, N);
  free_matrix(U, 1, N, 1, N);
  free_matrix(L, 1, N, 1, N);
  free_matrix(T, 1, N, 1, N);
  free_matrix(C, 1, N, 1, N);

    return 0;
}