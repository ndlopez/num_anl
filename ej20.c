#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

#define rnd() (double) (2.*rand()/(RAND_MAX+1.)-1.)
time_t sec;

void param(double *phi, double fi[], int n)
{
  *phi=rnd();
  fi[0]=2*rnd();
  while (1){
    fi[1]=rnd();
    if (fi[1]<1-fabs(fi[0])) break;
  }
}

int main (int argc, char *argv[])
{
  int i;
  double rho[2], ro[3], phi, fi[2];
  void param(double *, double fi[], int);//Emilio's idea.
  if (argc!=2){
    printf("Use a.out parametro \n");
    exit(0);
  }
  time(&sec);
  srand(sec);
  param(&phi, fi, atoi(argv[1]));
  i=0;
  rho[i%2]=1;
  ro[i%3]=1;
  ro[(i+1)%3]=rnd();
  while (i<atoi(argv[1])){
    rho[(i+1)%2]=phi*rho[i%2];
    ro[(i+2)%3]=fi[0]*ro[(i+1)%3]+fi[1]*ro[i%3];
    printf("%d %f %f \n",i,rho[i%2]+4.,ro[i%3]-4.);
    i++;
  }
  return(0);
}
