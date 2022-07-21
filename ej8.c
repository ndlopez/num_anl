#include<stdio.h>
#include<math.h>
#define pi (double)(atan(1.)*4)
#define Lo (double)1.
#define kappa (double)0.01
#define nterm (int)300
#define npoint (int)400
#define To (double)100

int main(void){
    int i,j,k;
    double TT,tt,xx;
    for(i=0;i<10;i++){
	tt=(float)i;
	for(j=-npoint/2;j<npoint/2;j++){
	    xx=pi/npoint*2*j;
	    TT=0;
	    for(k=1;k<nterm;k+=2)
		TT+=1./k*sin(k*xx)*exp(-pow(k*pi/Lo,2)*kappa*tt);
	    if(xx>=0.)
		printf("%f %f \n",xx/pi,To*4./pi*TT);
	}
	printf("\n");  
    } 
    return(0);
}
