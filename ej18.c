#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

#define rnd() (double) (2.*rand()/(RAND_MAX+1.)-1.)
time_t sec;

void param(double p[])
{
  p[0]=2*rnd();
  while (1){
    p[1]=rnd();
    if (p[1]<1-fabs(p[0])) break;
  }
}

void serie(double theta, double the[], double ma1[], double ma2[],
	   double phi, double fi[], double ar1[], double ar2[], int last)
{
  double w1, w2;
  int i=0;
  ma1[i%2]=rnd();
  ma2[i%3]=rnd();
  ma2[(i+1)%3]=rnd();
  while (i<last){
    ma2[(i+2)%3]=rnd();
    ma1[(i+1)%2]=rnd();
    w2=ma2[(i+2)%3]-the[0]*ma2[(i+1)%3]-the[1]*ma2[i%3];
    w1=ma1[(i+1)%2]-theta*ma1[i%2];
    printf("%d %f %f \n",i,2+w1,w2-2);
    i++;
  }
}

int main (int argc, char *argv[])
{
  double theta, the[2], ma1[2], ma2[3], phi, fi[2], ar1[2], ar2[3];
  void param(double the[]);
  void serie(double, double the[], double ma1[], double ma2[],
	      double, double phi[], double ar1[], double ar2[], int);
  if (argc!=2){
    printf("Use a.out parametro \n");
    exit(0);
  }
  time(&sec);
  srand(sec);
  theta=rnd();
  param (the);//funcion
  phi=rnd();
  param (fi);//funcion
  serie(theta, the, ma1, ma2, phi, fi, ar1, ar2, atoi(argv[1]));
}
