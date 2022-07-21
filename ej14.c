#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

#define N (int) 500
#define M (int) 100 // Terminos de la a y P
#define rnd() (double) (rand()/(RAND_MAX+1.))
#define PI (double) (atan(1.)*4)

int main()
{
  double x[N],a[M+1],P[M+1],Q[M+1];
  float dato;
  double pro;
  FILE *fp;
  fp=fopen("guaya20.ser","r");
  int i,j,k;
  for(i=0;i<N;i++){
    fscanf(fp,"%*f %f \n",&dato);
    x[i]=dato;
  }
    //x[i]=rnd()+sin(2*PI/22.*i)+0.5*cos(2*PI/35.2*i);
  pro=0;
  for(i=0;i<N;i++)
    pro+=x[i];
  pro/=N;
  //serie temporal <x>=0
  for(i=0;i<N;i++)
    x[i]-=pro;
  // Autocorrelacion
  for(i=0;i<=M;i++){
    a[i]=0;
    for(j=0;j<N;j++)
      if(i+j<N)
	a[i]+=x[j]*x[j+i];
    a[i]/=(N-i);
    //printf("%d %f \n",i,a[i]);
  }
  // FT
  for(i=0;i<=M;i++){
    P[i]=0;
    for(j=0;j<=M;j++)
      P[i]+=a[j]*cos(i*j*PI/M);
  }
  // Smoothing
  for(i=0;i<=M;i++){
    if(i>0 && i<M)
      Q[i]=0.5*P[i]+0.25*P[i+1]+0.25*P[i-1];
    else if(i==0)
      Q[i]=0.5*P[i]+0.5*P[i+1];
    else
      Q[i]=0.5*P[i]+0.5*P[i-1];
    i==0?printf("%f %f \n",(float)(i+1)/M/2,fabs(Q[i])):
      printf("%f %f \n",(float)i/M/2,fabs(Q[i]));
  }
  fclose(fp);
  return(0);  
}
