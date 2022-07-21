//Potencia espectral de ar(1) analiticamente
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

#define rnd() (double) (2.*rand()/(RAND_MAX+1.)-1.)
time_t sec;

void param(double *phi,double fi[],double *theta,double the[],int n){
  *phi=rnd();*theta=rnd();
  fi[0]=rnd();the[0]=rnd();
  while (1){
    fi[1]=rnd();the[1]=rnd();
    if(fi[1]<1-fabs(fi[0]) && the[1]<1-fabs(the[0])) break;
  }
}
double cmplx(double real, double imag){
  return(pow(real,2)+pow(imag,2));
}
int main (int argc, char *argv[]){
  int i;
  double rho[2], ro[3], phi, fi[2],theta,the[2];
  double sigma2=1.,xx, xx1, PI=atan(1.)*4;
  //void param(double *, double fi[],double *,double  int);//Emilio's idea.
  if (argc!=2){
    printf("Use a.out parametro \n");
    exit(0);
  }
  time(&sec);
  srand(sec);
  param(&phi,fi,&theta,the,atoi(argv[1]));
  for(i=1;i<=atoi(argv[1]);i++){
    xx1=(double)i/2./atoi(argv[1]);//escala lineal
    xx=pow(10.,log10(1./2./atoi(argv[1]))+log10((double)atoi(argv[1]))*i/atoi(argv[1]));//escala log
    printf("%f %f %f %f \n",xx1,xx,2.*sigma2/cmplx(1-phi*cos(2*PI*xx1),phi*sin(2*PI*xx1)),2.*sigma2/cmplx(1-phi*cos(2*PI*xx),phi*sin(2*PI*xx)));
  }
  return(0);
}
