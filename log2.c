#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define rnd() (double) (rand()/(RAND_MAX+1.))
#define N (int) 4000
#define M (int) 400

time_t sec;

int main()
{
  int i,j;
  double lambda=0.9789;
  double x0=rnd();
  double x1[N],x2[N],a1[M+1],a2[M+1];
  //double x[2000];
  time(&sec);
  srand(sec);
  for(i=0;i<N;i++){
    //printf("%d %f %f \n",i+1,x0,rnd());
    x1[i]=x0;
    x2[i]=rnd();
    x0=4*lambda*x0*(1.-x0);
  }
  //for(i=3;i<2000;i++)
  //printf("%d %f %f %f \n",i-2,x[i],x[i-1],x[i-2]);
  //autocorrelacion
  for(i=0;i<=M;i++){
    a1[i]=0;
    a2[i]=0;
    for(j=0;j<N;j++){
      if(j+i<N){
	a1[i]+=x1[j]*x1[j+i]/(N-i);
	a2[i]+=x2[j]*x2[j+i]/(N-i);
      }}
    printf("%d %f %f \n",i,a1[i],a2[i]);
  }
  return(0);
}

