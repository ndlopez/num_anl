#include<stdio.h>
#include<math.h>
int main(){
  double x,y,Phi,a,b,Vo,B,pi;
  int i,j,k,px,py,n;
  pi=atan(1.)*4;
  px=50;
  py=50;
  a=15;
  b=10;
  n=320;
  Vo=1500;
  for(i=0;i<=px-1;i+=1){
    x=a/(px-1)*i;
    for(j=0;j<=py-1;j+=1){
      y=b/(py-1)*j;
      Phi=0;
      for(k=1;k<=n;k+=1){
	B=2*Vo/pi*pow(-1,k+1)/(k*sinh(k*pi*b/a));
	Phi=Phi+B*sin(k*pi/a*x)*sinh(k*pi/a*y);
      }            
      printf("%f %f %f\n",x,y,Phi);
    }
    printf("\n");
  }
  return(0);    
}

