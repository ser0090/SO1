//
// Created by tincho on 06/10/17.
//
#include "DLList.c"

void * malloc(int size){
    static Nodo* inicio;

    if(inicio==NULL){
        inicio=crearBloque(size);
        if(inicio==NULL){return NULL;}
        inicio->free=false;
        return inicio+1;
    }

    return blockAlloc(size,inicio)+1;
}

void free(void* bloque){
    bloque = (Nodo*)bloque -1 ;

    return blockFree(bloque);

}
