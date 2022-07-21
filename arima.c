/*Series Autoregresiva InterMedia Movil arima(1,1,1)*/
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
    double phi1,theta1,x[N+1],aleat[N+1];
    double C[M+1],X[N],P[M+1],Q[M+1],pro;
    int i,j,k;
    if(argc<2){printf("Use ./a.out <filename>\n");exit(0);}
    fp=fopen(argv[1],"w+");
    time(&sec);
    srand(sec);
    strcpy(file,argv[1]);
    strcat(file,plt);
    printf("Type: gnuplot %s\n",file);//exit(0);
    for(j=0;j<L;j++){
	pro=0;
	aleat[0]=rnd();x[0]=rnd();
	for(i=1;i<=N+1;i++){
	    if(i==1){
		phi1=rnd();
		theta1=rnd();
	    }
	    aleat[i]=rnd();
	    x[i]=x[i-1]+phi1*x[i-1]+rnd()-theta1*aleat[i-1];
	    //para hallar el promedio
	    pro+=x[i];
	}
	pro/=N;
	//Autocorrelacion C[M+1],x[N]
	for(k=0;k<M+1;k++){
	    C[k]=0;
	    for(i=0;i<N;i++){
		if(i+k<N)
		    C[k]+=((x[i]-pro)*(x[i+k]-pro));}
	    C[k]/=N-k;
	    //Espectro de Potencias P[M+1],C[M]
	    P[k]=0.;
	    for(i=0;i<M+1;i++){
		if(i==0)
		    P[k]+=(0.5*C[i]*cos(PI*i*k/M));
		if(i!=0 && i<M)
		    P[k]+=(C[i]*cos(PI*i*k/M));
		if(i==M)
		    P[k]+=(0.5*C[i]*cos(PI*i*k/M));
		//Alisado P[M+1], Q[M+1]
		if(i==0)
		    Q[i]=0.5*P[i]+0.5*P[i+1];
		if(i!=0 && i<M)
		    Q[i]=0.25*P[i-1]+0.5*P[i]+0.25*P[i+1];
		if(i==M)
		    Q[i]=0.5*P[i]+0.5*P[i-1];
	    } //printf("%d C1=%f\n",k,C1[k]);
	}
	for(k=0;k<M+1;k++)
	    //impresion de valores 4cols
	    fprintf(fp,"%3d %f %f %f \n",
		    k,x[k]+j*4.,C[k]/C[0],fabs(Q[k]));
	fprintf(fp,"\n");
    }
    fclose(fp);
    
    dll=fopen(file,"w+");
    fprintf(dll,"switch=0\nset nokey\n");
    fprintf(dll,"if(switch==1)set t post eps enhanced solid\n");
    fprintf(dll,"if(switch==1)set o \"arima1.eps\"\n");
    fprintf(dll,"plot \"%s\" u 1:2 w l\n",argv[1]);
    fprintf(dll,"pause -1\n");
    fprintf(dll,"if(switch==1)set o \"autocarima1.eps\"\n");
    fprintf(dll,"plot \"%s\" u 1:3 w l\n",argv[1]);    
    fprintf(dll,"pause -1\nset title \"edp arima(1,1,1)\"\n"); 
    fprintf(dll,"set log\nif(switch==1)set o \"edparima1.eps\"\n");
    fprintf(dll,"plot \"%s\" u 1:4 w st\n",argv[1]); 
    fprintf(dll,"pause -1\nexit");
    fclose(dll);
}
