#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

char file[50]="";
const char dat[]=".e";
FILE *fp,*dll;
int main(int argc,char *argv[]){
    int i=0,N;
    double x[N+1],y[N+1],e[N+1];
    double xpro=0.,ypro=0.,sx=0.,sy=0.,sxy=0.,sx2=0.,sy2=0.;
    double D=0.,a,b,db,da,d=0.;
    double work;
    if(argc<3){
	printf("\tR L I N E A L\n\tVersion 1.0 Fri May 06,2005 22:30");
	printf("\n\t****Lineal Regresion by two variables****\n");
	printf("\tCopyright (C) by Diego Lopez\n");
	printf("\tSend comments and requests for help to:\n\t\t\t<ndlopez29@yahoo.de>\n");
	printf("\tTo use type: ./rlineal numdata <data-file>\n");
	printf("\te.g:./rlineal 45 difrac\n");
	exit(0);}
    N=atoi(argv[1]);
    dll=fopen(argv[2],"r");
    strcpy(file,argv[2]);
    strcat(file,dat);
    for(i=1;i<=N;i++){
	if(feof(dll))break;
	fscanf(dll,"%lf       %lf\n",&x[i],&y[i]);
	//printf("%lf       %lf\n",x[i],y[i]);
	xpro +=x[i];ypro +=y[i];
    }
    xpro/=N;ypro/=N;
    fclose(dll);
    //printf("xpro=%lf  ypro=%lf\n",xpro,ypro);
    for(i=1;i<=N;i++){
	sx+=x[i];sy+=y[i];
	sxy+=x[i]*y[i];
	sx2+=pow(x[i],2);sy2+=pow(y[i],2);
	D+=pow((x[i]-xpro),2);
    }
    work=N*sx2-pow(sx,2);
    b=(N*sxy-sx*sy)/work;
    a=(sx2*sy-sx*sxy)/work;
    printf("a=%lf\t b=%lf\n",a,b);
    fp=fopen(file,"w+");
    for(i=1;i<=N;i++){
	d+=pow(y[i]-b*x[i]-a,2);
	e[i]=y[i]-a-b*x[i];
	fprintf(fp,"%2.2f   %2.4f\n",x[i],e[i]);
    }
    fclose(fp);
    db=sqrt(1/D*d/(N-2));da=sqrt((1/N+pow(xpro,2)/D)*d/(N-2));
    printf("Lineal's equation:");
    printf("y(x)=(%4.3f+-%4.3f)x+(%4.3f+-%4.3f)\n",b,db,a,da);
    return(0);
}
