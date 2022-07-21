#include<stdio.h>
#include<math.h>

#define PI (double)(atan(1.)*4)
#define L0 (double)1.
#define KAPPA (double)0.01
#define NTERM (int)300
#define NPOINT (int)400

int main(void)
{
  int i,j,k;
  double yy,tt,xx;
  for(i=0;i<10;i++){
    tt=(float)i;
    for(j=-NPOINT/2;j<NPOINT/2+1;j++){
      xx=PI/NPOINT*2*j;
      yy=0;
      for(k=1;k<NTERM;k++)
	yy+=-pow(-1.,k)*(1./k*sin(k*xx)*exp(-pow(k*PI/L0,2)*KAPPA*tt));
      printf("%f %f \n",xx,yy);
    }
    printf("\n");  
  } 
  return(0);
}
