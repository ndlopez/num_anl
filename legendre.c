#include<stdio.h>
void lep(float y[],float x, int n){
    int i;
    y[0]=1;
    if(n==0)return;
    y[1]=x;
    for(i=2;i<=n;i++)
	y[i]=x*y[i-1]-y[i-2]+x*y[i-1]-(x*y[i-1]-y[i-2])/i;
}
int main(){
    int i;
    float npoints=300,xj,y[10+1];
    void lep(float y[],float,int);
    for(i=0;i<=12;i+=2){
	for(xj=-1.;xj<=1.;xj+=2./300.){
	    lep(y,xj,i);
	    printf("%f  %f \n",xj,y[i]);
	}
	printf("\n");}
    return(0);
}
