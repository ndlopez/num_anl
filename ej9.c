#include<stdio.h>
#include<math.h>

#define PI (double) (atan(1.)*4)
#define L0 (double) 1.
#define KAPPA (double) 0.01
#define NTERM (int) 300
#define NPOINT (int) 400
#define T0 (double) 100.

int main(void)
{
	int i,j,k,n;
	double tt,xx,TT;
	for (i=0;i<10;i++){
		tt=(float)i;
		for(j=-NPOINT/2;j<NPOINT/2;j++){
			xx=PI/NPOINT*2*j;
			TT=0;
			for(k=1;k<NTERM;k+=2)
				TT+=-(pow(-1,(k+1)/2))*1./(pow(k,2))*sin(k*xx)*exp(-pow(k*PI/L0,2)*KAPPA*tt);
			if(xx>=0.)
			printf("%f %f \n",xx/PI,T0*4./PI*TT);
		}
		printf("\n");
	}
	return(0);
}




