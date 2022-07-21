#include<stdio.h>
#include<math.h>
double a[]={1,1,2,6,24,120,720,5040,40320,362880,3628800};
double cero[]={1};
double uno[]={1,-1};
double dos[]={2,-4,1};
double tres[]={6,-18,9,-1};
double cuatro[]={24,-96,72,-16,1};
double cinco[]={120,-600,600,-200,25,-1};
double seis[]={720,-4320,5400,-2400,450,-36,1};
double siete[]={5040,-35280,52920,-29400,7350,-882,49,-1};
double ocho[]={40320,-322560,564480,-376320,117680,-18816,1568,-64,1};
double nueve[]={362880,-3265920,6531840,-5080320,1905120,-381024,42336,-2592,81,-1};
double diez[]={3628800,-36288000,81648000,-72576000,31752000,-7620480,1058400,-86400,4050,-100,1};
int main(){
    int i,j;
    double ix, work,f[11],xx[11];
    for(ix=0.;ix<=2;ix+=0.01)
	for(i=0;i<11;i++){
	    for(j=0;j<=i;j++){
		if(i==0)work=cero[j];
		if(i==1)work=uno[j];
		if(i==2)work=dos[j];
		if(i==3)work=tres[j];
		if(i==4)work=cuatro[j];
		if(i==5)work=cinco[j];
		if(i==6)work=seis[j];
		if(i==7)work=siete[j];
		if(i==8)work=ocho[j];
		if(i==9)work=nueve[j];
		if(i==10)work=diez[j];
		xx[j]=work;
	    }
	    f[i]=0;
	    if(i==0)printf("%f ",ix);
	    for(j=0;j<=i;j++)
		f[i]+=xx[j]*pow(ix,i-j);
	    i==10?printf("%f \n",f[i]/a[i]):printf("%f ",f[i]/a[i]);
	}
    return(0);
}
