#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

#define N (int) 500
#define M (int) 100 // Terminos de la auto y rho
#define rnd() (double) (2.*(rand()/(RAND_MAX+1.))-1.)
#define PI (double) (atan(1.)*4)
time_t sec;

int main(){
  double x[N],a[M+1],aux;
  double rho[M+1],theta1,theta2;
  float dato;
  double pro;
  FILE *fp;
  time(&sec);srand(sec);
  fp=fopen("preg6","r");
  int i,j,k;
  for(i=0;i<N;i++){
    fscanf(fp,"%*d %f \n",&dato);
    x[i]=dato;
  }
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
  fclose(fp);
  //autocorrelacion por formula
  for(i=0;i<100;i++){
    theta1=rnd();theta2=rnd();
    if(theta2<=(1-fabs(theta1)))break;
  }
  for(i=0;i<M+1;i++)
    rho[i]=0;
  aux=1+pow(theta1,2)+pow(theta2,2);
  rho[0]=(-theta1*(1.-theta2))/(1+pow(theta1,2)+pow(theta2,2));
  rho[1]=-theta2/(1+pow(theta1,2)+pow(theta2,2));
  for(i=2;i<M+1;i++)
    rho[i]=0;
  for(i=0;i<M;i++)
    printf("%d %f %f \n",i,rho[i],a[i]);
  
  return(0);  
}
