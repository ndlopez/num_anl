/*10 funciones Bessel*/
#include<stdio.h>
#include<math.h>
int main(){
    int j,ier;
    float bj,x,d=0.01;
    void besj(float,int,float *,float,int *);
    for(x=0.;x<10.;x+=0.01)
	for(j=0;j<10;j++){
	    if(j==0)printf("%f ",x);
	    besj(x,j,&bj,d,&ier);
	    j==9?printf("%f \n",bj):printf("%f ",bj);	
	}
    return(0);
}
void besj(float x, int n, float *bj, float d, int *ier){
    int ntest,n1,ma,mb,mzero,mmax;
    int m,jt,m2,mk,k;
    float bprev,fm,fm1,alpha,bmk,s;
    (*bj)=0.;
    if(n<0){(*ier)=1;return;}
    if(x<=0.){(*ier)=2;return;}
    if(x<=15.){
	ntest=20.+10.*x-pow((double)x,2./3.);
	if(n<ntest)(*ier)=0;
	else{
	    (*ier)=4;return;}
    }
    else{
	ntest=90.+x/2.;
	if(n>=ntest){(*ier)=4;return;}
	else (*ier)=0;
    }
    n1=n+1;
    bprev=0.;
    if(x<5)ma=x+6;
    else
	ma=1.4*x+60./x;
    mb=n+(int)x/4+2;
    mzero=(ma>mb)?ma:mb;
    mmax=ntest;
    for(m=mzero;m<=mmax;m+=3){
	fm1=1.e-28;fm=0.;
	alpha=0;
	if(m==m/2*2)
	    jt=-1;
	else
	    jt=1;
	m2=m-2;
	for(k=1;k<=m2;k++){
	    mk=m-k;
	    bmk=2.*(float)mk*fm1/x-fm;
	    fm=fm1;fm1=bmk;
	    if(mk==n+1)
		(*bj)=bmk;
	    jt=-jt;s=1+jt;
	    alpha+=bmk*s;
	}
	bmk=2.*fm1/x-fm;
	if(n==0)
	    (*bj)=bmk;
	alpha+=bmk;(*bj)/=alpha;
	if(fabs((double)((*bj)-bprev))<=fabs((double)(d*(*bj))))
	    return;
	bprev=(*bj);
    }
    (*ier)=3;
    return;
}
