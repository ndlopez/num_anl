#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define PI (double)(atan(1.)*4) 
#define LAST (int)4096
#define rnd() (double)(2.*rand()/(1.+RAND_MAX)-1.)
double xx[LAST+1],y[LAST+1],xi[LAST+1];	/* x, xi fft input, y psd */
time_t sec;
FILE *fp;
void para(double fi[]){
  int i;
  i=0;
  fi[0]=2*rnd();
  while(i>-1){
    fi[1]=rnd();
    if(fi[1]<1-fabs(fi[0]))break;
    i++;
  }
}
double cmplx(double real,double imag){
  return (pow(real,2)+pow(imag,2));
}
void TdF(double phi,double fi[],double theta,double the[],double sigma2,int n){
  int i,j;
  double xi,y1,y2,y3,y4;
  extern double cmplx(double ,double);
  for(i=1;i<=n;i++){
    xi=pow(10.,log10(1./2./n)+log10((double)n)*(i-0)/n);
    y1=2.*sigma2/cmplx(1-phi*cos(2*PI*xi),+phi*sin(2*PI*xi));
    y2=2.*sigma2/cmplx(1-fi[0]*cos(2*PI*xi)-fi[1]*cos(4*PI*xi),
		       +fi[0]*sin(2*PI*xi)+fi[1]*sin(4*PI*xi));
    y3=2.*sigma2*cmplx(1-theta*cos(2*PI*xi),+theta*sin(2*PI*xi));
    y4=2.*sigma2*cmplx(1-the[0]*cos(2*PI*xi)-the[1]*cos(4*PI*xi),
		       +the[0]*sin(2*PI*xi)+the[1]*sin(4*PI*xi));
    fprintf(fp,"%f %f %f %f %f \n",xi,y1,y2,y3,y4);
  }
}
int main(int argc, char *argv[]){
  int i,j,k,mexp;
  double ar1[2],ar2[3],ma1[2],mav1[2],mav2[3],ma2[3];
  double phi,theta,fi[2],the[2];
  double ave;
  double x[4][LAST+1];
  void para(double fi[]);
  void fft(double x[], double xi[], int ,int);
  double cmplx(double ,double);
  void TdF(double,double fi[],double,double the[],double,int);
  if(argc!=2){
    printf("use a.out parameter\n");
    exit(0);
  }
  time(&sec);
  srand(sec);
  para(fi);
  para(the);
  //the models
  i=0;
  phi=rnd();
  theta=rnd();
  ar2[i%3]=rnd();
  ar2[(i+1)%3]=rnd();
  ma2[i%3]=rnd();
  ma2[(i+1)%2]=rnd();
  mav2[i%3]=ma2[i%3];
  mav2[(i+1)%2]=ma2[(i+1)%2];
  ma1[i%2]=rnd();
  mav1[i%2]=ma1[i%2];
  ar1[i%2]=rnd();
  while(i<atoi(argv[1])){
    ma2[(i+2)%3]=rnd();
    ma1[(i+1)%2]=rnd();
    ar2[(i+2)%3]=fi[0]*ar2[(i+1)%3]+fi[1]*ar2[i%3]+rnd();
    ar1[(i+1)%2]=phi*ar1[i%2]+rnd();
    mav1[(i+1)%2]=ma1[(i+1)%2]-theta*ma1[i%2];
    mav2[(i+2)%3]=ma2[(i+2)%3]-the[0]*ma2[(i+1)%3]-the[1]*ma2[i%3];
    printf("%d %f \n",i,ma2[(i+2)%3]-the[0]*ma2[(i+1)%3]-the[1]*ma2[i%3]);
    for(j=0;j<4;j++){
      if(j==0)x[j][i+1]=ar1[i%2];
      if(j==1)x[j][i+1]=ar2[i%3];
      if(j==2)x[j][i+1]=mav1[i%2];
      if(j==3)x[j][i+1]=mav2[i%3];
    }
    i++;
  }
  //fourier Transform
  //p(f)=2*sigma/abs(1-phi*exp(-2pif)) para 0<=f<=0.5, etc.
  fp=fopen("EdP","w+");
  TdF(phi,fi,theta,the,1.,atoi(argv[1]));
  fclose(fp);
  //exit(0);
  //a mano
  mexp=0;
  for(i=0;i<=12;i++)
    if(atoi(argv[1]) == (int)(ldexp(1.,i))){
      mexp=i;
      break;
    }
  if(mexp==0){
    printf("el parametro %d no es correcto\n",atoi(argv[1]));
    exit(0);
  }
  //printf("exponent = %d numero = %d \n",mexp,atoi(argv[1]));exit(0);
  for(j=0;j<4;j++){
    ave=0.;
    for(i=1;i<=atoi(argv[1]);i++)
      ave += x[j][i]/(double)(atoi(argv[1]));
    for(i=1;i<=atoi(argv[1]);i++)
      x[j][i] -= ave;
    for(i=1;i<=atoi(argv[1]);i++){
      xx[i]=x[j][i];
      xi[i]=0;
    }
    fft(xx,xi,atoi(argv[1]),mexp);
    for(i=1;i <= atoi(argv[1])/2;i++)
      y[i]=pow(xx[i],2)+pow(xi[i],2);
    for(i=1;i <= atoi(argv[1])/2;i++){
      if(i==1)
	x[j][i]=0.5*y[i]+0.5*y[i+1];
      else
	x[j][i]=0.25*y[i-1]+0.5*y[i]+0.25*y[i+1];     
    }
  }
  fp=fopen("EdPm","w+");
  for(i=1;i <= atoi(argv[1])/2;i++){
    fprintf(fp,"%f ",(float)i/atoi(argv[1]));
    for(j=0;j<4;j++)
      fprintf(fp,"%f ",x[j][i]);
    fprintf(fp,"\n");
  }
  fclose(fp);
  return(0);
}
void fft(double xreal[], double ximag[],int n,int nu){
  int n2,nu1,ibitr;
  int i,j,j1,j2,k,k1,l,k1n2;
  double p,c,s,arg,treal,timag;
  n2=n/2;
  nu1=nu-1;
  k=0;
  for(l=1;l<=nu;l++){
  one:
    for(i=1;i<=n2;i++){
      j1=k/((int)ldexp(1.,nu1));
      ibitr=0;
      for(j=1;j<=nu;j++){
	j2=j1/2;
	ibitr=ibitr*2+(j1-2*j2);
	j1=j2;
      }
      p=(double)ibitr;
      arg=2.*PI*p/n;
      c=cos(arg);
      s=sin(arg);
      k1=k+1;
      k1n2=k1+n2;
      treal      =xreal[k1n2]*c+ximag[k1n2]*s;
      timag      =ximag[k1n2]*c-xreal[k1n2]*s;
      xreal[k1n2]=xreal[k1]-treal;
      ximag[k1n2]=ximag[k1]-timag;
      xreal[k1]  =xreal[k1]+treal;
      ximag[k1]  =ximag[k1]+timag;
      k++;
    }
    k += n2;
    if(k<n)goto one;
    k=0;
    nu1--;
    n2 /= 2;
  }
  for(k=1;k<=n;k++){
    j1=k-1;
    ibitr=0;
    for(j=1;j<=nu;j++){
      j2=j1/2;
      ibitr=ibitr*2+(j1-2*j2);
      j1=j2;
    }
    i=ibitr+1;
    if(i<=k)goto two;
    treal   =xreal[k];
    timag   =ximag[k];
    xreal[k]=xreal[i];
    ximag[k]=ximag[i];
    xreal[i]=treal;
    ximag[i]=timag;
  two:;
  }
}
