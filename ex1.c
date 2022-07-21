#include<stdio.h>
#include<math.h>

#define TERM (int) 300
#define ABS (int) 500
#define PI (double) (atan(1.)*4)

int main(void)
{
  int i,j;
  double xx,yy;
  for(i=-ABS/2-50;i<=ABS/2+50;i++){
      xx=PI*i/ABS*2;
      yy=0;
      for(j=1;j<TERM;j++)
	yy+=-pow(-1.,j)*(1./j*sin(j*xx));
      printf("%f %f \n",xx,yy);
  }
  return(0);
}
