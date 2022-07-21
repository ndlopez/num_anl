#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define N (int)500
#define M (int)50
#define rnd() (double)(2*(rand()/(RAND_MAX+1.))-1)
time_t sec;
int main()
{
  double phi0,x[N+1];
  double C2[M+1];
  double pro1;
  int i,j,k;
  time(&sec);
  srand(sec);
  //printf("%s",file);exit(0);
  pro1=0;
  x[1]=rnd();
  for(i=1;i<=N;i++){
    if(i==1)
      phi0=rnd();
    x[i+1]=phi0*x[i]+rnd();
    pro1+=x[i+1];
  }
  pro1/=N;
  //Autocorrelacion
  for(k=0;k<M+1;k++){
    C2[k]=0;
    for(i=0;i<N;i++){
      if(i+k<N)
	C2[k]+=((x[i]-pro1)*(x[i+k]-pro1));
    }
    C2[k]/=N-k;
  }
  for(k=0;k<M+1;k++)
    printf("%3d %f %f \n",k,x[k],C2[k]/C2[0]);
  return(0);

}
