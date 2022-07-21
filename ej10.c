#include<stdio.h>
#include<math.h>

#define PI (double) (atan(1.)*4)

int main(void)
{
  int i,j,k;
  double xx,yy,zz;
  for(i=0;i<=30;i++){
    xx=i;
    for(j=0;j<=60;j+=2){
      yy=j;
      zz=0;
      for(k=1;k<20;k+=2)
	zz+=sin(k*PI/30.*xx)*sinh(k*PI/30.*yy)/k/sinh(k*PI*60./30.);
      printf("%f %f %f \n",xx,yy,100.*4./PI*zz);
    }
    printf("\n");
  }
  return(0);
}
  
