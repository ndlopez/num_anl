#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define rnd() (double) (2.*rand()/(RAND_MAX+1.)-1.)

time_t sec;

int main(void)
{
  int i,j,n=200;
  double phi,phi1,phi2,r1[2],r2[3];
  time(&sec);
  srand(sec);
  phi=rnd();
  //for(j=0;j<1000;j++){
    phi1=rnd();
    i=0;
    while(i>=0){
      phi2=fabs(rnd());
      if(phi2<(1.-fabs(phi1))) break;
      i++;
    }
    //printf("%f %f \n",phi1,phi2);
    //}
    i=0;
    r1[0]=rnd();
    r2[0]=rnd();
    r2[1]=rnd();
    while(i<n){
      r1[(i+1)%2]=phi*r1[i%2]+rnd();
      r2[(i+2)%3]=phi1*r2[(i+1)%3]+phi2*r2[i%3]+rnd();
      printf("%d %f %f %f \n",i,r1[i%2],4.+r2[i%3],-4.+rnd());
      i++;
    }
  return(0);
}
