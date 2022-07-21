#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define rnd() (double) (rand()/(RAND_MAX+1.))
time_t sec;

int main(int argc, char *argv[]){
  int i,n;
  double xx[4],rr[4],lambda;
  if(argc!=3){
    printf("use ./a.out number1 number2 \n");
    exit(0);
  }
  n=atoi(argv[1]);
  lambda=atof(argv[2]);
  i=0;
  xx[0]=rnd();rr[0]=rnd();
  while(i<n){
    rr[(i+1)%4]=rnd();
    xx[(i+1)%4]=4*lambda*xx[i%4]*(1.-xx[i%4]);
    if(i>3)
      printf("%d %f %f %f %f %f %f %f %f \n",i,xx[i%4],xx[(i-1)%4],xx[(i-2)%4],xx[(i-3)%4],rr[i%4],rr[(i-1)%4],rr[(i-2)%4],rr[(i-3)%4]);
    i++;
  }
  return(0);
}
