#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nrutil.h"

#define N 200 // rozmiar macierzy M: NxN

int main(void)
{
    float **M, **b;
    //	Alokacja macierzy
    M = matrix(1, N, 1, N);
    b = matrix(1, N, 1, 1);

    float w = 1.0;
    float v=0.0;
    float a=1.0;
    float h=0.1;
    float zl = w*w*h*h-2.0;   //ponizej srodkowej przekatnej
    // 	Wypelnienie macierzy M i wektora b
    for (int i = 1; i <= N; ++i)
    {
        b[i][1] = 0.0;
        for (int j = 1; j <= N; ++j)
            M[i][j] = 0.0;
    }
    b[1][1] = a;
    b[2][1] = v*h;

    for (int i = 1; i <= N; ++i)
        M[i][i] = 1.0;  //na srodkowej przekatnej
 
    M[2][1] = -1.0;

    for(int i=3; i<=N;++i){
        M[i][i-2] = 1.0; 
        M[i][i-1] = zl;
    }

    //	Rozwiazanie ukladu rownan Mx=b - wywolanie procedury:
    gaussj(M, N, b, 1);

    //	Zapisanie wynikow do pliku.
    FILE *file = fopen("wyniki.txt", "w");
    if(file)
    {
       for (int i = 1; i <= N; ++i)
            fprintf(file, "%f\t%g\n", (i-1)*h, b[i][1]); 
    } 

    fclose(file);

    
    //	Zwolnienie pamieci
    free_matrix(M, 1, N, 1, N);
    free_matrix(b, 1, N, 1, 1);

    return 0;
}