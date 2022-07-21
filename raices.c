#include<stdio.h>
#include<math.h>
#define inicio 49 
#define ta 50
double f(double x){
    return(0.685*x-cos(x));
}
double falsapos(){
  double a,b,R;
  int n;
  printf("\nMETODO DE LA FALSA POSICION\n");
  printf("Introduzca primer intervalo: \t");scanf("%lf",&a);
  printf("Introduzca segundo intervalo:\t");scanf("%lf",&b);
  while(fabs(f(R))>=0.0000001){
      R=(f(b)*a-f(a)*b)/(f(b)-f(a));
      if(f(a)*f(R)<=0)
	  b=R;
      else
	  a=R;
  }
  printf("La Raiz es: %0.9lf\n",R); 
}
double bisec(){
    double fa,fb,fc,a,b,c,r;
    int n;
    printf("\nMETODO DE LA BISECCION\n");
    printf("Introduzca el primer intervalo: \t");scanf("%lf",&a);
    printf("Introduzca el segundo intervalo:\t");scanf("%lf",&c);
    fa=f(a);fc=f(c);
    if(f(a)*f(c)<=0){
	while(fabs(a-c)/2>0.0000001){
	    b=(a+c)/2;fb=f(b);
	    if(f(a)*f(b)<=0){
		c=b;fc=fb;
	    }
	    else{
		a=b;fa=fb;
	    }
	}
    }
    else{
	printf("Cambie Limites\n");
	return(0);
    }
    printf("La Raiz es:\t%0.9lf\n",b);
}
double newtonr(){
    double a,z,dery;
    int n;
    printf("\nMETODO DE NEWTON\n");
    printf("Introduzca aproximacion:\t");scanf("%lf",&a);
    do{
	dery=(-1.5*f(a)+2*f(a+0.0001)-0.5*f(a+0.0002))/0.0001;
	z=a-f(a)/dery;
	a=z;
    }while(fabs(f(z))==0);
    printf("La Raíz es: \t%0.9lf\n",z);
}
double sec(){
    double a,b,r;
    int n;
    printf("Introduzca primer intervalo:\t");scanf("%lf",&a);
    printf("Introduzca segundo intervalo:\t");scanf("%lf",&b);
    do{
	r=b-(f(b)*(b-a))/(f(b)-f(a));
	a=b;b=r;  
    }while(fabs(a-b)<=0.00001);
    printf("La Raiz es:\t%lf\n",r);
}
double sust_suces(){
    int mk,k,j=0;
    double a,b,i,c=0.00001,d=0.0001,z[ta],y[ta],g;
    printf("Metodo de Sustitucion Sucesiva\n");
    printf("Introduce el intervalo en el que se encuentra la raiz\n");
    printf("limite inferior:\t");
    scanf("%lf",&a);
    printf("limite superior:\t");
    scanf("%lf",&b);
    for(i=a;i<=b;i+=c){
	if(-d<f(i) && f(i)<d){z[j]=i;j=j+1;}}
    for(k=0;k<j;k++)y[k]=f(z[k]);
    g=y[0];
    mk=0;
    for(k=0;k<j;k++)if(pow(y[k],2)<pow(g,2)){g=y[k];mk=k;}
    printf("la raiz es:\n%0.6lf\n",z[mk]);
}
int main(void){
    enum 
	{
	    biseccion = inicio,
	    falsap,
	    newton,
	    secante,
	    sustitucion,
	    salir
	};
    char opcion;
    printf("\nSOLUCIÓN DE ECUACIONES NO LINEALES POR DISTINTOS MÉTODOS\n\n");
    printf("1.- Método de la bisección\n");
    printf("2.- Método de la falsa posición\n");
    printf("3.- Método de Newton\n");
    printf("4.- Método de secante\n");
    printf("5.- Método de sustitución sucesiva\n");
    printf("6.- Salir\n");
    printf("\nTeclee opción de 1-6:\t");
    opcion = getchar();
    if (opcion == biseccion) bisec();
    if (opcion == falsap) falsapos();
    if (opcion == newton) newtonr();
    if (opcion == secante) sec();
    if (opcion == sustitucion) sust_suces();
    if (opcion == salir) exit(0);
}
