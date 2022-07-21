#include<stdio.h>
#include<math.h>
#define LIM (double)5.
#define N (int)5
int main(){
  int i,j;
  double y[N+1],x;
  void her(double y[],double, int);
  double fact(int);
  for(x=0.;x<=LIM;x+=0.01){
    for(j=0;j<=N;j++){
      if(j==0){
	printf("%2.3f  ",x);
	her(y,x,N);}
      printf("%5.3f  ",y[j]);
    }
    printf("\n");}
  return(0);
}
