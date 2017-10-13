//#include <string.h>

#include "Funciones/malloc.c"
int main() {

    char* arreglo=malloc(sizeof(char)*1024);
    char *arr2 = malloc(200);
    char* arr3 = malloc(300);

   // strcpy(arreglo,"lalalalalalalalalalalalalalalalalalala");
    //printf("%s",arreglo);

    free(arr2);
    arr2=malloc(150);
    free(arr3);
    free(arreglo);
}