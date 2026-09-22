#include <stdio.h>
int sumar_pares(int n){
    int suma=0;
    int ejecuciones=0;
    int ejecuciones1 =0;
    for (int i =0; i < n ;i++){
        if (i%2==0){
            suma=suma+i;
            ejecuciones1++;
        }
        ejecuciones++;
    }
    printf("ejecucion del bucle:%d\n",ejecuciones);
    printf("ejecucion de suma:%d\n",ejecuciones1);
    return suma;
}
int main()
{

   int sumar=sumar_pares(10);
   printf("la suma de numeros pares de 1 hasta n :%d",sumar);

    return 0;
}

