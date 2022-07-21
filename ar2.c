/*Series Autoregresivas ar(1),ar(2)*/
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#define N (int)1024
#define M (int)N/3
#define L (int)1
#define PI (double)(atan(1.)*4)
#define rnd()(double)(2*(rand()/(RAND_MAX+1.))-1)
time_t sec;
FILE *fp;

int main(){
    double phi1,phi2,y[N+1];
    double rho[M+1],nu1[M+1],edp1[M+1],theta0;
    double C2[M+1],P2[M+1],Q2[M+1],pro2;
    int i,k;
    time(&sec);
    srand(sec);
    fp=fopen("ar2","w+");
    pro2=0;
    y[0]=rnd();y[1]=rnd();
    for(i=1;i<=N;i++){
	if(i==1){
	    //para hallar los parametros phi1 phi2
	    for(k=0;k<100;k++){
		phi1=2*rnd();
		phi2=rnd();
		if(phi2<=(1-fabs(phi1)))break;
	    }
	}
	y[i]=rnd()+phi1*y[i]+phi2*y[i-1];
	//para hallar el promedio
	pro2+=y[i+1];
    }
    pro2/=N;
    //Autocorrelacion C{2}[M+1],x{1,2}[N]
    for(k=0;k<M+1;k++){
	C2[k]=0.;
	for(i=0;i<N;i++){
	    if(i+k<N)
		C2[k]+=((y[i]-pro2)*(y[i+k]-pro2));
	}
	C2[k]/=N-k;
	//Espectro de Potencias P[M+1],C[M]
	P2[k]=0.;
	for(i=0;i<M+1;i++){
	    if(i==0)
		P2[k]+=(0.5*C2[i]*cos(PI*i*k/M));
	    if(i!=0 && i<M)
		P2[k]+=(C2[i]*cos(PI*i*k/M));
	    if(i==M)
		P2[k]+=(0.5*C2[i]*cos(PI*i*k/M));
	    //Alisado P[M+1], Q[M+1]
	    if(i==0)
		Q2[i]=0.5*P2[i]+0.5*P2[i+1];
	    if(i!=0 && i<M)
		Q2[i]=0.25*P2[i-1]+0.5*P2[i]+0.25*P2[i+1];
	    if(i==M)
		Q2[i]=0.5*P2[i]+0.5*P2[i-1];
	} printf("%d C2=%f\n",k,C2[k]);
    }
    theta0=rnd();
    rho[0]=1;
    rho[1]=-theta0/(1.+pow(theta0,2));
    for(k=0;k<M+1;k++){
	nu1[k]=(0.5*k)/M;
	edp1[k]=2*pow(fabs(1-theta0*cos(-2*PI*nu1[k])),2);
	//impresion de valores 7cols
	fprintf(fp,"%3d %f %f %f \n",k,y[k],C2[k],fabs(Q2[k]));
    }
    fclose(fp);
    fp=fopen("ar2.plt","w+");
    fprintf(fp,"switch=0\nset nokey\n");
    fprintf(fp,"if(switch==1)set t post eps enhanced solid\n");
    fprintf(fp,"if(switch==1)set o \"ar2.eps\"\n");
    fprintf(fp,"plot \"ar2\" u 1:2 w l\n");
    fprintf(fp,"pause -1\n");
    fprintf(fp,"if(switch==1)set o \"autocar2.eps\"\n");
    fprintf(fp,"plot \"ar2\" u 1:3 w l\n");
    fprintf(fp,"set title \"edp ar(2)\"\nset log\n"); 
    fprintf(fp,"pause -1\nif(switch==1)set o \"edpar2.eps\"\n");
    fprintf(fp,"plot \"ar2\" u 1:4 w st\n"); 
    fprintf(fp,"pause -1\nexit");
    fclose(fp);
    return(0);
}
