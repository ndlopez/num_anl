/*Aplicacion logistica
para lambda caotico */
#include<stdio.h>
main(){
    double lambda=0.97,x[2000];
    int i;
    FILE *fp,*dll;
    fp=fopen("logist","w+");
    x[0]=0.5;
    for(i=0;i<=100;i++){
	x[i+1]=4*lambda*x[i]*(1-x[i]);
	//printf("%d   %lf\n",i,x[i]);
	fprintf(fp,"%d   %lf\n",i,x[i]);
    }
    //fprintf(fp,"\n");
    //}
    fclose(fp);
    dll=fopen("logist.plt","w+"); 
    fprintf(dll,"set nokey\nswitch=1\n");
    fprintf(dll,"if(switch==1)set t post eps enhanced solid");    
    fprintf(dll,"\nif(switch==1)set o \"logist.eps\"\n");
    fprintf(dll,"plot \"logist\" u 1:2 w l\n");
    fprintf(dll,"pause -1\nexit");
    fclose(dll);
}
