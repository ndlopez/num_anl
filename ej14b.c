#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
time_t sec;
#define N (int)500
#define M (int)100 //terminos de la a y p//
#define rnd() (double)(2.*rand()/(RAND_MAX+1.)-1.) 
#define PI (double)(atan(1.)*4)
#define lambda (double)0.998
int main()
{
  int i,j,k;
  double x[N],y[N],rr[N],r1[N];
  double r2[N],log[N],a[M+1],p[M+1],p1[M+1];
  double p2[M+1],p3[M+1],p4[M+1],p5[M+1];
  double q[M+1],q1[M+1],q2[M+1],q3[M+1],q4[M+1],q5[M+1];
  double b[M+1],c[M+1],d[M+1],e[M+1],f[M+1];
  double pro,pro1,pro2,pro3,pro4,pro5,phi,phi1,phi2;
  float data,data1;
  time(&sec);
  srand(sec);
  FILE *fp,*fp1;
  fp=fopen("alto20.ser","r");
  pro=0;
  for(i=0;i<N;i++){
    fscanf(fp,"%*f %f \n",&data);
    x[i]=data;
  }
  fp1=fopen("Trini20.ser","r");
  pro5=0;
  for(i=0;i<N;i++){
    fscanf(fp1,"%*f %f \n",&data1);
    y[i]=data1;
  }
  phi=rnd();
  phi1=rnd(); 
  i=0;
  r1[0]=rnd();
  r2[0]=rnd();
  r2[1]=rnd();
  rr[0]=rnd();
  log[0]=rnd();
  while(i>=0){
    phi2=fabs(rnd());
    if(phi2<1.-fabs(phi1))break;
    i++;
 }
 for(i=0;i<N;i++){
    rr[i]=rnd();
    log[i+1]=lambda*log[i]*(1-log[i]);
   r1[i+1]=phi*r1[i]+rnd();
   r2[i+2]=phi1*r2[i+1]+phi2*r2[i]+rnd();
  }
 for(i=0;i<N;i++){
   pro+=x[i];
   pro1+=rr[i];
   pro2+=log[i];
   pro3+=r1[i];
   pro4+=r2[i];
   pro5+=y[i];
 }
 pro/=N;
 pro1/=N;
 pro2/=N;
 pro3/=N;
 pro4/=N;
 pro5/=N;
 //serie temporal<x>=0
 for(i=0;i<N;i++){
   x[i]-=pro;
   y[i]-=pro5;
   rr[i]-=pro1;
   log[i]-=pro2;
   r1[i]-=pro3;
   r2[i]-=pro4;
 }
 //autocorrelacion
 for(i=0;i<=M;i++){
   a[i]=0;
   b[i]=0;
   c[i]=0;
   d[i]=0;
   e[i]=0;
   f[i]=0;
   for(j=0;j<N;j++)
     if(i+j<N){    
       a[i]+=x[j]*x[j+i];
       b[i]+=rr[j]*rr[j+i];
       c[i]+=log[j]*rr[j+i];
       d[i]+=r1[j]*rr[j+i];
       e[i]+=r2[j]*rr[j+i];
       f[i]+=y[j]*y[j+i];
     }
   a[i]/=(N-i);
   b[i]/=(N-i);
   c[i]/=(N-i);
   d[i]/=(N-i);
   e[i]/=(N-i);
   f[i]/=(N-i);  
   //Transformada de Fourier.
 }   
 for(i=0;i<=M;i++){
   p[i]=0;
   p1[i]=0;
   p2[i]=0;
   p3[i]=0;
   p4[i]=0;
   p5[i]=0;
   for(j=0;j<=M;j++){
     p[i]+=a[j]*cos(i*j*PI/M);
     p1[i]+=b[j]*cos(i*j*PI/M);
     p2[i]+=c[j]*cos(i*j*PI/M);
     p3[i]+=d[j]*cos(i*j*PI/M);
     p4[i]+=e[j]*cos(i*j*PI/M);
     p5[i]+=f[j]*cos(i*j*PI/M);
   }
 }
 //smoothing
 for(i=0;i<=M;i++){
   if(i>0&&i<M){
     q[i]=0.5*p[i]+0.25*p[i-1]+0.25*p[i+1];
     q1[i]=0.5*p1[i]+0.25*p1[i-1]+0.25*p1[i+1];
     q2[i]=0.5*p2[i]+0.25*p2[i-1]+0.25*p2[i+1];
     q3[i]=0.5*p3[i]+0.25*p3[i-1]+0.25*p3[i+1];
     q4[i]=0.5*p4[i]+0.25*p4[i-1]+0.25*p4[i+1];
     q5[i]=0.5*p5[i]+0.25*p5[i-1]+0.25*p5[i+1];
   }
   else if(i==0){
     q[i]=0.5*p[i]+0.5*p[i+1];
     q1[i]=0.5*p1[i]+0.5*p1[i+1];
     q2[i]=0.5*p2[i]+0.5*p2[i+1];
     q3[i]=0.5*p3[i]+0.5*p3[i+1];
     q4[i]=0.5*p4[i]+0.5*p4[i+1];
     q5[i]=0.5*p5[i]+0.5*p5[i+1];
   }
   else{
     q[i]=0.5*p[i]+0.5*p[i-1];
     q1[i]=0.5*p1[i]+0.5*p1[i-1];
     q2[i]=0.5*p2[i]+0.5*p2[i-1];
     q3[i]=0.5*p3[i]+0.5*p3[i-1];
     q4[i]=0.5*p4[i]+0.5*p4[i-1];
     q5[i]=0.5*p5[i]+0.5*p5[i-1];
   }
   i==0?printf("%f %f %f %f %f %f %f \n",(float)(i+1)/M/2,fabs(q[i]),fabs(q1[i]),fabs(q2[i]),fabs(q3[i]),fabs(q4[i]),fabs(q5[i])):
     printf("%f %f %f %f %f %f %f \n",(float)i/M/2,fabs(q[i]),fabs(q1[i]),fabs(q2[i]),fabs(q3[i]),fabs(q4[i]),fabs(q5[i]));
 }
 fclose(fp);
 fclose(fp1);
 return(0); 
}
