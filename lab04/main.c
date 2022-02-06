#include <stdio.h>
#include <math.h>
#include "nrutil.h"
//#include "nrutil.c"
//#include "tred2.c"
//#include "tqli.c"
//#include "pythag.c"

int main(){

  int nx=20;
  int ny=20;
  int n = ny*nx;
  int m=10;
  float t = -0.021;

//alokacja pamieci
  float **H = matrix(1,n,1,n);
  float **Y = matrix(1,n,1,n);
  float **X = matrix(1,n,1,n);
  float *d = vector(1,n);
  float *e = vector(1,n);
  int *indx = ivector(1,n);


//uzupelnianie macierzy H
  for(int i=1; i<=nx;i++){
    for(int j=1; j<=ny;j++){
      int l = j+(i-1)*ny;

      for(int k=1;k<=n;k++)
        H[l][k]=0.;

        if(i>1)   
          H[l][l-ny]=t;   //dla i=1 nie ma sasiada z lewej strony
        
        if(i<nx)
          H[l][l+ny]=t;   //dla i=nx nie ma sasiada z prawej strony
       
        H[l][l]=-4*t;
        

        if(j>1)   
          H[l][l-1]=t;  //dla j=1 nie ma sasiada ponizej siatki

        if(j<ny)
          H[l][l+1]=t;    //dla j=ny nie ma sasiada powyzej siatki
    }
  }

//uzupelnienie macierzy Y, wartosci 1 na glownej przekatnej
  for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++){
      if(i==j)
        Y[i][j] = 1.0;
      else Y[i][j]= 0.0;
    }

//przeksztalcanie macierzy H do macerzy trojdiagonalnej
  tred2(H,n,d,e);

//diagonalizacja macierzy
  tqli(d, e, n, Y );


//mnozenie macierzy X = H*Y
  for(int i=1; i<=n; i++){
    for(int j=1; j<=n;j++){
      float suma=0.0;
      for(int k=1; k<=n;k++)
        suma +=H[i][k]*Y[k][j];

      X[i][j] = suma;
    }
  }

//sortowanie energii oraz indeksow wektora
  float e1,e2,l1,l2;

  for(int l=1;l<=n;l++) 
    indx[l]=l; // inicjalizacja

  for (int l = 1; l <= (n - 1); l++){
      for (int k = n; k >= l + 1; k--){
        e1 = d[k-1];
        e2 = d[k];
        l1 = indx[k - 1];
        l2 = indx[k];
        if(e2 < e1){ //wymieniamy energie i indeksy wektorów miejscami
          d[k] = e1;
          d[k-1] = e2;
          indx[k] = l1;
          indx[k-1] = l2;
        }
      }
    }

//zapisywanie do pliku
  FILE *fp;
    fp = fopen("dane.dat", "w");
    
    for (int i = 1; i <= nx; i++){
      for (int j = 1; j <= ny; j++){
        int l = j + (i-1) * ny;
        fprintf(fp, "%6d %6d ", i, j);
        for (int k = 1;k <= m; k++)
          fprintf(fp, " %12.6f ", X[l][ indx[k] ]);
        fprintf(fp, "\n");
      }
      fprintf(fp, "\n");
    }
    fclose(fp);

//sprawdzenie wartosci wlasnych
  for (int i = 1; i <= m; i++)
    printf("%.9f\n", d[i]);


//zwalnianie pamieci
  free_matrix(H,1,n,1,n);
  free_matrix(Y,1,n,1,n);
  free_matrix(X,1,n,1,n);
  free_vector(d,1,n);
  free_vector(e,1,n);
  free_ivector(indx,1,n);

  return 0;
}