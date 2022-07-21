#include<stdio.h>
#include<math.h>
#define TERM (int)300
#define ABS (int)500
#define PI (double)(atan(1.)*4)
int main(void){
    int i,j;
    double xx,yy;
    FILE *fp;
    fp=fopen("ej5","w+"); 
    for(i=-ABS/2;i<=ABS/2;i++){
	xx=PI*i/ABS*2;
	yy=0;
	for(j=1;j<TERM;j+=2)
	    yy+=1./j*sin(j*xx);
	fprintf(fp,"%f %f \n",xx,yy);
    }
    fclose(fp);
    return(0);
}
