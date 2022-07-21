#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

#define rnd() (double) (2.*rand()/(RAND_MAX+1.)-1.)
time_t sec;

void param(double *phi, double fi[], int n){
  *phi=rnd();
  fi[0]=2*rnd();
  while(1){
    fi[1]=rnd();
    if (fi[1]<1-fabs(fi[0])) break;
  }
}

int main ()
{
  int i,j,k,N=150,M=50;
  double phi0,x[N+1];
  double C2[M+1];
  double pro1;
  double rho[2], ro[3], phi, fi[2];
  void param(double *, double fi[], int);//Emilio's idea.
  time(&sec);
  srand(sec);
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
  
  param(&phi, fi,M);
  i=0;
  rho[i%2]=1;
  ro[i%3]=1;
  ro[(i+1)%3]=rnd();
  while(i<M){
    rho[(i+1)%2]=phi*rho[i%2];
    ro[(i+2)%3]=fi[0]*ro[(i+1)%3]+fi[1]*ro[i%3];
    printf("%d %f %f %f %f \n",i,rho[i%2],ro[i%3],x[i],C2[i]/C2[0]);
    i++;
  }
  
  return(0);
}
