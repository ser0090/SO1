#include <string.h>
#include <stdio.h>
#include "Funciones/malloc.c"
int main() {
    int j = sizeof(Nodo *);
    char* arreglo=malloc(sizeof(char)*1024);

    strcpy(arreglo,"lalalalalalalalalalalalalalalalalalala");
    printf("%s",arreglo);
    free(arreglo);
}