#include <stdio.h>
/* programa que demuestre el manejo de punteros y de array*/
int main(){
    char arr[]="HOLA";
    for(int i=0;arr[i]!='\0';i++){
        printf("esto es con indices\n");
        printf("%c\n",arr[i]);
        printf("esto es con punteros\n");
        printf("%c\n",*(arr+i));

    }
    return 0;

}
main();