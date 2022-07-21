/*Series Media Movil ar(1),ar(2)*/
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
char file[50]="";
const char plt[]=".plt";
FILE *fp,*dll;

int main(int argc,char *argv[]){
    double phi0,phi1,phi2,x[N+1],y[N+1];
    double rho[M+1],nu1[M+1],edp1[M+1];
    double C1[M+1],C2[M+1],P1[M+1],P2[M+1],Q1[M+1],Q2[M+1],pro1,pro2;
    int i,j,k;
    if(argc<2){printf("Use ./a.out <filename>\n");exit(0);}
    fp=fopen(argv[1],"w+");
    time(&sec);
    srand(sec);
    strcpy(file,argv[1]);
    strcat(file,plt);
    printf("Type: gnuplot %s\n",file);//exit(0);
    for(j=0;j<L;j++){
	pro1=0;pro2=0;
	x[1]=rnd();y[0]=rnd();y[1]=rnd();
	for(i=1;i<=N;i++){
	    if(i==1){
		phi0=rnd();
                //para hallar los parametros phi1 phi2
		for(k=0;k<100;k++){
		    phi1=2*rnd();
		    phi2=rnd();
		    if(phi2<=(1-fabs(phi1)))
			break;
		}
	    }
	    x[i]=rnd()+phi0*x[i];
	    y[i]=rnd()+phi1*y[i]+phi2*y[i-1];
	    //para hallar el promedio
	    pro1+=x[i+1];
	    pro2+=y[i+1];
	}
	pro1/=N;pro2/=N;
	//Autocorrelacion C{1,2}[M+1],x{1,2}[N]
	for(k=0;k<M+1;k++){
	    C1[k]=0;C2[k]=0;
	    for(i=0;i<N;i++){
		if(i+k<N){
		    C2[k]+=((y[i]-pro2)*(y[i+k]-pro2));
		    C1[k]+=((x[i]-pro1)*(x[i+k]-pro1));}}
	    C1[k]/=N-k;C2[k]/=N-k;
	    //Espectro de Potencias P[M+1],C[M]
	    P1[k]=0.;P2[k]=0.;
	    for(i=0;i<M+1;i++){
		if(i==0){ 
		    P1[k]+=(0.5*C1[i]*cos(PI*i*k/M));
		    P2[k]+=(0.5*C2[i]*cos(PI*i*k/M));}
		if(i!=0 && i<M){
		    P1[k]+=(C1[i]*cos(PI*i*k/M));
		    P2[k]+=(C2[i]*cos(PI*i*k/M));}
		if(i==M){
		    P1[k]+=(0.5*C1[i]*cos(PI*i*k/M));
		    P2[k]+=(0.5*C2[i]*cos(PI*i*k/M));}
		//Alisado P[M+1], Q[M+1]
		if(i==0){
		    Q1[i]=0.5*P1[i]+0.5*P1[i+1];
		    Q2[i]=0.5*P2[i]+0.5*P2[i+1];}
		if(i!=0 && i<M){
		    Q1[i]=0.25*P1[i-1]+0.5*P1[i]+0.25*P1[i+1];
		    Q2[i]=0.25*P2[i-1]+0.5*P2[i]+0.25*P2[i+1];}	  
		if(i==M){
		    Q1[i]=0.5*P1[i]+0.5*P1[i-1];
		    Q2[i]=0.5*P2[i]+0.5*P2[i-1];}
	    } //printf("%d C1=%f\n",k,C1[k]);
	}
	//theta0=rnd();rho[0]=1;rho[1]=-theta0/(1.+pow(theta0,2));
	for(k=0;k<M+1;k++){
	    //rho[k+2]=0;nu1[k]=(0.5*k)/M;
	    //edp1[k]=2*pow(fabs(1-theta0*cos(-2*PI*nu1[k])),2);
	    //impresion de valores 7cols
	    fprintf(fp,"%3d %f %f %f %f %f %f \n",
		    k,x[k]+j*4.,y[k]+j*4.,rho[k],C1[k]/C1[0],C2[k]/C2[0],
		    fabs(Q1[k]),edp1[k],fabs(Q2[k]));}
	fprintf(fp,"\n");
    }
    fclose(fp);
    
    dll=fopen(file,"w+");
    fprintf(dll,"switch=0\nset nokey\n");
    fprintf(dll,"if(switch==1)set t post eps enhanced solid\n");
    fprintf(dll,"if(switch==1)set o \"ar1.eps\"\n");
    fprintf(dll,"plot \"%s\" u 1:2 w l\n",argv[1]);
    fprintf(dll,"pause -1\nif(switch==1)set o \"ar2.eps\"\n");
    fprintf(dll,"plot \"%s\" u 1:3 w l\n",argv[1]);
    fprintf(dll,"pause -1\nif(switch==1)set o \"autocar1.eps\"\n");
    fprintf(dll,"plot \"%s\" u 1:4 w l,\"%s\" u 1:5 w l\n",argv[1],argv[1]);   
    fprintf(dll,"pause -1\nif(switch==1)set o \"autocar2.eps\"\n");
    fprintf(dll,"plot \"%s\" u 1:6 w l\n",argv[1]);
    fprintf(dll,"set title \"edp ar(1)\"\n"); 
    fprintf(dll,"pause -1\nset log\nif(switch==1)set o \"edpar1.eps\"\n");
    fprintf(dll,"plot \"%s\" u 1:7 w st,\"%s\" u 1:8 w st\n",argv[1],argv[1]); 
    fprintf(dll,"set title \"edp ar(2)\"\n"); 
    fprintf(dll,"pause -1\nif(switch==1)set o \"edpar2.eps\"\n");
    fprintf(dll,"plot \"%s\" u 1:9 w st\n",argv[1]); 
    fprintf(dll,"pause -1\nexit");
    fclose(dll);
}
