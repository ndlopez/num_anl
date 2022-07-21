#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define rnd() (double) (2.*rand()/(RAND_MAX+1.)-1.)

time_t sec;
int main(void)
{
  int i;
  time(&sec);
  srand(sec);
  for(i=0;i<10;i++)
    printf("%d %d %f \n",i+1,rand(),rnd());
  return(0);
}
