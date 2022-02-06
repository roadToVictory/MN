#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "nrutil.h"
#include "nrutil.c"
#include "gammln.c"
#include "erff.c"
#include "gammp.c"
#include "gcf.c"
#include "gser.c"

double generator(int a, int c, int m){
  static long int x0 = 10;
  long int m_l = pow(2,m);
  x0 = (a*x0+c)%m_l;

  return (double)x0/(double)(m_l+1.0);
}


int main(){
 FILE *fU = fopen("U.dat", "w");
 FILE *fU_hist = fopen("U_hist.dat", "w");
 FILE *fN_hist = fopen("N_hist.dat", "w");

 int N=10000;
 int k=12;
 double x[N];
 double x1[N];
 int nj[k]; 
 int nj1[k];
 double s= 0.0;
 double ss=0.0;
 double st=0.0;
 double t=0.0;
 int j=0;
 double dx = 1.0/k; //szerokosc przedzialu to 1
 
 for(int i=0; i<k; i++){
   nj[i]=0;
   nj1[i]=0;
 }


 int a = 123; int c=1; int m=15;

 for(int i=0; i<N;i++){
   x[i] = generator(a,c,m);
   if(i)
     fprintf(fU, "%f\t%f\n", x[i-1], x[i]);
   ss+=x[i-1];

   j= (int)(x[i]/dx);
   nj[j]++;
 }

fprintf(fU, "\n\n");
s = ss/N;

for(int i=0; i<N;i++)
  st += pow( (x[i]-s) ,2);

t = sqrt(st/N);

for(int i=0; i<k;i++)
  fprintf(fU_hist, "%f\t%f\n",(j+0.5)*dx, (double)nj[i]/N);

fprintf(fU_hist, "\n\n");

//////////

a=69069;
c=1;
m = 32;
ss = st = 0.0;

for(int i=0; i<N; i++){
  x1[i]=generator(a,c,m);

  if(i)
     fprintf(fU, "%f\t%f\n", x1[i-1], x1[i]);
   ss+=x1[i-1];

  j= (int)(x1[i]/dx);
   nj1[j]++;
}

fprintf(fU, "\n\n");
s = ss/N;

for(int i=0; i<N;i++)
  st += pow( (x1[i]-s) ,2);

t = sqrt(st/N);

for(int i=0; i<k;i++)
  fprintf(fU_hist, "%f\t%f\n",(j+0.5)*dx, (double)nj1[i]/N);


 fclose(fU); fclose(fU_hist); fclose(fN_hist);


 return 0;
}